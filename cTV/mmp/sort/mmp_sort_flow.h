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
 * $RCSfile: mmp_sort_flow.h,v $
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

#ifndef _MMP_SORT_FLOW_H_
#define _MMP_SORT_FLOW_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_img.h"
#include "c_dt.h"
#include "c_sort_search.h"
#include "u_fm.h"
#include "c_fm.h"
    
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/file_filter/mmp_ff.h"
#include "mmp/file_filter/mmp_fid.h"

#include "mmp/mmp_intf_sort.h"
#include "res/mmp/sort/mmp_sort_rc.h"

#include "nav/nav_memory.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
 typedef enum MMP_SORT_ACCESS_TYPE_T
 {
     MMP_SORT_ACCESS_TYPE_REF = 0,
     MMP_SORT_ACCESS_TYPE_NEW
 } MMP_SORT_ACCESS_TYPE_T;
 
 typedef enum MMP_SORT_GROUP_ID_T
 {
     MMP_SORT_GROUP_ID_FILE = 0,
     MMP_SORT_GROUP_ID_FOLDER,
     MMP_SORT_GROUP_ID_COUNT
 } MMP_SORT_GROUP_ID_T;

/*************************************/
typedef INT32 (*mmp_sort_compare_nodes)(
MMP_SORT_GROUP_ID_T   e_group,
UINT32                 ui4_node_index_a,
UINT32                 ui4_node_index_b,
VOID*                  pv_owner);

typedef INT32 (*mmp_sort_swap_items)(
        VOID*                       pv_owner,
        MMP_SORT_GROUP_ID_T         e_group,
        UINT32                      ui4_node_index_a,
        UINT32                      ui4_node_index_b);



/*********Phot sort structure***********************/

/*-----------------------------------------------------------------------------
 * customization default value
 *---------------------------------------------------------------------------*/
#ifndef _MMP_SORT_RC_IS_FREE_DATA_AFTER_SORT
    #define _MMP_SORT_RC_IS_FREE_DATA_AFTER_SORT()      (TRUE)
#endif

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/

extern INT32 mmp_sort_flow_new_inst(SIZE_T z_bytes_file_node, /**file**/
                           UINT32 ui4_nodes_per_file_page,/**file**/
                           SIZE_T z_bytes_folder_node, /**folder**/
                           UINT32 ui4_nodes_per_folder_page,/**folder**/
                           mmp_sort_compare_nodes pf_compare,
                           mmp_sort_swap_items pf_swap,
                           VOID* pv_owner,
                           VOID** ppv_flow);

extern INT32 mmp_sort_flow_free_inst(VOID *pv_flow);

extern INT32 mmp_sort_flow_do_sort(VOID* pv_flow,
                                   MMP_SORT_GROUP_ID_T e_group,
                                   UINT32 ui4_count,
                                   UINT32 ui4_cache_cnt,
                                   UINT32 ui4_mapping_count,
                                   MMP_MAPPING_NODE_T* at_mappings);

extern INT32 mmp_sort_flow_get_node(VOID* pv_flow,
                            MMP_SORT_GROUP_ID_T e_group ,
                            UINT32 ui4_node_idx,
                            MMP_SORT_ACCESS_TYPE_T e_access ,                            
                            VOID** pv_node);

extern INT32 mmp_sort_free_page(VOID *pv_flow);
extern INT32 mmp_sort_get_item_name(VOID* pv_flow,
                                    UINT8 ui1_ff_id,
                                    VOID* pv_data,
                                    VOID* pv_data2,
                                    CHAR** pps_name);

extern INT32 mmp_sort_flow_do_cmd(VOID* pv_flow,
                                  MMP_SORT_CMD_ID_T e_cmd_id,
                                  VOID* pv_param);

extern INT32 mmp_sort_flow_get_group(VOID* pv_flow,
                                     MMP_SORT_GROUP_ID_T *pe_group);

#endif /*_MMP_DATE_SORT_H_*/


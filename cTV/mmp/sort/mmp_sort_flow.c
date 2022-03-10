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
 * $RCSfile: mmp_sort_flow.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_img.h"
#include "c_dt.h"
#include "c_sort_search.h"
#include "u_fm.h"
#include "c_fm.h"
#include "c_dt.h"
#include "c_dbg.h"
 
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/file_filter/mmp_ff.h"
#include "mmp/file_filter/mmp_fid.h"


#include "mmp/util/mmp_util.h"

#include "res/app_util/config/a_cfg_custom.h"

#include "mmp/sort/mmp_sort_flow.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MMP_SORT_RESET_CACHE_INFO(_pt_info)                                          \
{                                                                                    \
    c_memset((_pt_info), 0, sizeof(MMP_SORT_CACHE_INFO_T));                          \
    (_pt_info)->fid = MMP_FID_NULL_REC_IDX;                                          \
    (_pt_info)->pv_data = MMP_SORT_ITEM_INFO_INVALD_DATA;                            \
    (_pt_info)->pv_data2 = MMP_SORT_ITEM_INFO_INVALD_DATA;                           \
}

#ifndef MMP_SORT_SEND_NFY_INTERVAL
#define MMP_SORT_SEND_NFY_INTERVAL      ((UINT32)30)
#endif

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/

typedef struct __MMP_SORT_SORT_REC_T
{
    UINT16                      ui2_what_it_should;
    UINT16                      ui2_what_it_own;
    UINT16                      ui2_where_it_is;
} _MMP_SORT_SORT_REC_T;

typedef struct __MMP_SORT_PAGE_T
{
   UCHAR*                       pt_buf;
   struct __MMP_SORT_PAGE_T*     pt_next;
} _MMP_SORT_PAGE_T;

typedef struct _MMP_SORT_CACHE_INFO_T
{
    VOID*                   pv_data;
    VOID*                   pv_data2;
    FID_T                   fid;
    UINT32                  ui4_ref_ts;/*Local Time Stamp*/
} MMP_SORT_CACHE_INFO_T;

typedef struct __MMP_SORT_GROUP_DATA_T
{
    _MMP_SORT_PAGE_T          *pt_pages;
    UINT32                    ui4_buf_count;
    SIZE_T                    z_node_size;
    SIZE_T                    z_bytes_per_node;
    UINT32                    ui4_nodes_per_page;
    MMP_SORT_CACHE_INFO_T*    at_cache_info;
    UINT32                    ui4_cache_cnt;
    UINT32                    ui4_cache_ref_ts;/*Local Time Stamp*/
} _MMP_SORT_GROUP_DATA_T;

typedef struct _MMP_Sort_Flow
{
    _MMP_SORT_GROUP_DATA_T     at_group[MMP_SORT_GROUP_ID_COUNT];
    MMP_SORT_GROUP_ID_T        e_sorting_group;

    mmp_sort_compare_nodes     pf_compare;
    mmp_sort_swap_items        pf_swap;
    VOID*                      pv_owner;

    BOOL                       b_cancel_sort;
    mmp_sort_status_nfy        pf_status_nfy;
    UINT32                     ui4_compare_cnt;
} MMP_Sort_Flow;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BOOL b_g_right=TRUE; 
#if 0
static UINT8  ui1_new_page_index=0;
#endif
/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_flow_new_page
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_flow_new_page(
    MMP_Sort_Flow *pt_flow,
    MMP_SORT_GROUP_ID_T          e_group,
    UINT32                      ui4_count)
{
    _MMP_SORT_GROUP_DATA_T*       pt_group;
    _MMP_SORT_PAGE_T*             pt_new_page;
    _MMP_SORT_PAGE_T*             pt_tail_page;
    UINT32                        i;

    /**/
    MMP_ASSERT(pt_flow);
    
    MMP_ASSERT(e_group < MMP_SORT_GROUP_ID_COUNT);
    pt_group = &pt_flow->at_group[e_group];

    pt_tail_page = pt_group->pt_pages;
    while(pt_tail_page && pt_tail_page->pt_next)
    {
        pt_tail_page = pt_tail_page->pt_next;
    }
    for(i = 0; i < ui4_count; i++)
    {
#if 0        
        ui1_new_page_index++;
#endif        
        /*alloc resource*/
        pt_new_page = (_MMP_SORT_PAGE_T*)c_mem_alloc(sizeof(_MMP_SORT_PAGE_T));
        if(NULL == pt_new_page)
        {
            DBG_LOG_PRINT(("new_page c_mem_alloc pt_new_page failed\n"));
            MMP_DBG_ERROR(("Fail to alloc memory (size = %d). i4_ret = %d.\r\n", 
               sizeof(_MMP_SORT_PAGE_T)));
            return MMPR_OUT_OF_MEM;
        }
        /*init member*/
        c_memset(pt_new_page, 0, sizeof(_MMP_SORT_PAGE_T));
        
        pt_new_page->pt_buf = (UCHAR*)c_mem_alloc(pt_group->z_node_size*pt_group->ui4_nodes_per_page);
        if(NULL == pt_new_page->pt_buf)
        {
            DBG_LOG_PRINT(("new_page c_mem_alloc pt_buf failed\n"));
            c_mem_free(pt_new_page);
            MMP_DBG_ERROR(("Fail to alloc memory (size = %d). i4_ret = %d.\r\n", 
               pt_group->z_node_size));
            return MMPR_OUT_OF_MEM;
        }
        pt_group->ui4_buf_count += pt_group->ui4_nodes_per_page;
        
        if(pt_tail_page)
        {
            pt_tail_page->pt_next = pt_new_page;
        }
        else
        {
            pt_group->pt_pages = pt_new_page;
        }

        pt_tail_page = pt_new_page;

    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_flow_free_cache_info
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_flow_free_cache_info(MMP_Sort_Flow *pt_flow)
{
    _MMP_SORT_GROUP_DATA_T*     pt_group;
    INT32                       i4_ret;
    UINT32                      i, j;  

    if (NULL == pt_flow)
    {
        return MMPR_INV_ARG;
    }

    for(i = 0; i < MMP_SORT_GROUP_ID_COUNT; i++)
    {
        pt_group = &pt_flow->at_group[i];

        if (NULL == pt_group->at_cache_info || pt_group->ui4_cache_cnt == 0)
        {
            continue;
        }

        for (j = 0; j < pt_group->ui4_cache_cnt; j++)
        {
            if (MMP_FID_NULL_REC_IDX != pt_group->at_cache_info[j].fid)
            {
                i4_ret = mmp_fid_del(pt_group->at_cache_info[j].fid);
                if(MMPR_OK != i4_ret)
                {
                    return MMPR_FAIL;
                }
            }
        }

        c_mem_free(pt_group->at_cache_info);
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_sort_flow_open
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_flow_new_inst(SIZE_T z_bytes_file_node, /**file**/
                           UINT32 ui4_nodes_per_file_page,/**file**/
                           SIZE_T z_bytes_folder_node, /**folder**/
                           UINT32 ui4_nodes_per_folder_page,/**folder**/
                           mmp_sort_compare_nodes pf_compare,
                           mmp_sort_swap_items pf_swap,
                           VOID* pv_owner,
                           VOID** ppv_flow)
                           
{
    MMP_Sort_Flow*      pt_this;
#if 0    
    ui1_new_page_index=0;
#endif
    b_g_right=TRUE;

    /**/
    if(NULL == ppv_flow)
    {
        return MMPR_INV_ARG;
    }

    /*alloc resource*/
    pt_this = (MMP_Sort_Flow*)c_mem_alloc(sizeof(MMP_Sort_Flow));
    if(NULL == pt_this)
    {
        DBG_LOG_PRINT(("mmp_sort_flow_new_inst c_mem_alloc failed\n"));
        MMP_DBG_ERROR(("Fail to alloc memory (size = %d). i4_ret = %d.\r\n", sizeof(MMP_Sort_Flow)));
        return MMPR_OUT_OF_MEM;
    }

    /*init member*/
    c_memset(pt_this, 0, sizeof(MMP_Sort_Flow));
    pt_this->pf_compare = pf_compare;
    pt_this->pf_swap = pf_swap;
    pt_this->pv_owner = pv_owner;
    
    /********file node****************/
    pt_this->at_group[MMP_SORT_GROUP_ID_FILE].z_bytes_per_node =z_bytes_file_node;
    pt_this->at_group[MMP_SORT_GROUP_ID_FILE].ui4_nodes_per_page =ui4_nodes_per_file_page;
    pt_this->at_group[MMP_SORT_GROUP_ID_FILE].z_node_size =(SIZE_T)(z_bytes_file_node + 7 ) & (~0x7);
  

    /********folder node****************/
    pt_this->at_group[MMP_SORT_GROUP_ID_FOLDER].z_bytes_per_node =z_bytes_folder_node;
    pt_this->at_group[MMP_SORT_GROUP_ID_FOLDER].ui4_nodes_per_page =ui4_nodes_per_folder_page;
    pt_this->at_group[MMP_SORT_GROUP_ID_FOLDER].z_node_size =(SIZE_T)(z_bytes_folder_node + 7 ) & (~0x7);

    *ppv_flow = pt_this;
    
    return MMPR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: mmp_sort_free_page
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_free_page(VOID *pv_flow)
{
    MMP_Sort_Flow*             pt_flow=(MMP_Sort_Flow*)pv_flow;
    _MMP_SORT_GROUP_DATA_T*       pt_group;
    _MMP_SORT_PAGE_T              *pt_page, *pt_next;
    INT32                       i;
    
    if(NULL == pt_flow)
    {
        return MMPR_OK;
    }
    
    for(i = 0; i < MMP_SORT_GROUP_ID_COUNT; i++)
    {
        pt_group = &pt_flow->at_group[i];

        pt_page = pt_group->pt_pages;
        while (pt_page)
        {
            /*keep next*/
            pt_next = pt_page->pt_next;

            /*free resource*/
            c_mem_free(pt_page->pt_buf);
            c_mem_free(pt_page);

            pt_page = pt_next;
        }
        
        pt_group->pt_pages = NULL;
        pt_group->ui4_buf_count = 0;
        pt_group->z_node_size = 0;
        pt_group->z_bytes_per_node = 0;
        pt_group->ui4_nodes_per_page = 0;
    }
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_sort_flow_free_inst
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_flow_free_inst(VOID *pv_flow)
{
    INT32 i4_ret=0;
    MMP_Sort_Flow* pt_this=(MMP_Sort_Flow*)pv_flow ;
    if(NULL == pt_this)
    {
        return MMPR_OK;
    }
    /*free pages*/
    i4_ret=mmp_sort_free_page((VOID*)pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*free LRU cache info*/
    i4_ret=_mmp_sort_flow_free_cache_info(pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);
    
    /*free instance*/
    c_mem_free(pt_this);
#if 0
    nav_mem_dump_usage();
#endif    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ds_compare
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_flow_compare(
    const VOID*                 pv_ui2_rec_a,
    const VOID*                 pv_ui2_rec_b,
    VOID*                       pv_this)
{
    MMP_Sort_Flow*             pt_this = (MMP_Sort_Flow*)(pv_this);
    
    _MMP_SORT_SORT_REC_T       *pt_rec_a, *pt_rec_b;
    
    MMP_ASSERT(pt_this);
    
    if (pt_this->pf_status_nfy && FALSE == pt_this->b_cancel_sort)
    {
        pt_this->ui4_compare_cnt++;

        if ((pt_this->ui4_compare_cnt % MMP_SORT_SEND_NFY_INTERVAL) == 0)
        {
            BOOL    b_stop_sort = FALSE;
            INT32   i4_ret;

            i4_ret = pt_this->pf_status_nfy(&b_stop_sort);
            if (MMPR_OK == i4_ret && b_stop_sort)
            {
                pt_this->b_cancel_sort = TRUE;
            }

        }
    }

    /*get node a*/
    pt_rec_a = (_MMP_SORT_SORT_REC_T*)pv_ui2_rec_a;
    
    /*get node b*/
    pt_rec_b = (_MMP_SORT_SORT_REC_T*)pv_ui2_rec_b;
    
    if (pt_this->b_cancel_sort)
    {
        /*Sort operation is canceled, return 0 directly*/
        return 0;
    }
    else
    {
        return pt_this->pf_compare(pt_this->e_sorting_group,
                                   (UINT32)pt_rec_a->ui2_what_it_should,
                                   (UINT32)pt_rec_b->ui2_what_it_should,
                                   pt_this->pv_owner);
    }
}
/*-----------------------------------------------------------------------------
 * Name: mmp_sort_flow_do_sort
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_flow_do_sort(VOID*                   pv_flow,
                            MMP_SORT_GROUP_ID_T     e_group,
                            UINT32                  ui4_count,
                            UINT32                  ui4_cache_cnt,
                            UINT32                  ui4_mapping_count,
                            MMP_MAPPING_NODE_T*     at_mappings) 
{
    MMP_Sort_Flow*             pt_this=(MMP_Sort_Flow*)pv_flow;
    INT32                      i4_ret;
    UINT32                     ui4_index,  ui4_where_target, i;
    _MMP_SORT_SORT_REC_T*      at_sort_buf;
    UINT32                     ui4_what_visited_own;
    _MMP_SORT_GROUP_DATA_T*    pt_group;
    
    /**/
    MMP_ASSERT(pt_this&&e_group < MMP_SORT_GROUP_ID_COUNT);

    if(0==ui4_count)/*needn't sort*/
    {
        return MMPR_OK;
    }

    if(0 != ui4_mapping_count && NULL == at_mappings)
    {
        return MMPR_INV_ARG;
    }

    MMP_TMS_RESET("Before calling mmp_sort_flow_do_sort ");

    /*alloc sort LRU cache*/
    pt_group = &pt_this->at_group[e_group];
    pt_group->ui4_cache_cnt = ui4_cache_cnt;

    pt_group->at_cache_info = (MMP_SORT_CACHE_INFO_T*)c_mem_alloc(ui4_cache_cnt * sizeof(MMP_SORT_CACHE_INFO_T));
    if(NULL == pt_group->at_cache_info)
    {
        MMP_DBG_ERROR(("c_mem_alloc(size = %d) failed. \r\n", ui4_cache_cnt * sizeof(MMP_SORT_CACHE_INFO_T)));
        return MMPR_OUT_OF_MEM;
    }
    for (i = 0; i < ui4_cache_cnt; i++)
    {
        /*Init member*/
        MMP_SORT_RESET_CACHE_INFO(&pt_group->at_cache_info[i]);
    }

    /*alloc sorting buffer*/
    at_sort_buf = (_MMP_SORT_SORT_REC_T*)c_mem_alloc(ui4_count * sizeof(_MMP_SORT_SORT_REC_T));
    if(NULL == at_sort_buf)
    {
        DBG_LOG_PRINT(("do_sort c_mem_alloc failed\n"));
        MMP_DBG_ERROR(("c_mem_alloc(size = %d) failed. \r\n", ui4_count * sizeof(_MMP_SORT_SORT_REC_T)));
        return MMPR_OUT_OF_MEM;
    }

    /*init sorting index*/
    for(ui4_index = 0; ui4_index < ui4_count; ui4_index++)
    {
        (at_sort_buf + ui4_index)->ui2_what_it_should = (UINT16)ui4_index;
    }

    do 
    {    
        /*do sort*/
        pt_this->e_sorting_group = e_group;

        i4_ret = c_qsort(at_sort_buf,
                         ui4_count,
                         sizeof(_MMP_SORT_SORT_REC_T),
                         _mmp_sort_flow_compare,
                         (VOID*)pt_this);
        if(SSR_OK != i4_ret)
        {
            DBG_LOG_PRINT((" c_qsort %d failed\n",ui4_count));
            MMP_DBG_ERROR(("c_qsort(size = %d) failed. \r\n", ui4_count));
            i4_ret = MMPR_FAIL;
            break;
        }

        /*init data index*/
        for(ui4_index = 0; ui4_index < ui4_count; ui4_index++)
        {
            (at_sort_buf + ui4_index)->ui2_what_it_own = (at_sort_buf + ui4_index)->ui2_where_it_is = (UINT16)ui4_index;
        }

        /*move data*/
        i4_ret = MMPR_OK;
        for(ui4_index = 0; ui4_index < ui4_count; ui4_index++)
        {
            /*check index*/
            if(ui4_index == (at_sort_buf + ui4_index)->ui2_what_it_should)    /*don't have to move*/
            {
                continue;
            }
            ui4_where_target = (at_sort_buf + (at_sort_buf + ui4_index)->ui2_what_it_should)->ui2_where_it_is;

          /*swap sort buf*/

          /*backup current node first*/
          ui4_what_visited_own = (UINT32)(at_sort_buf + ui4_index)->ui2_what_it_own;
          
          /*copy target node to current node*/
          (at_sort_buf + ui4_index)->ui2_what_it_own = (at_sort_buf + ui4_where_target)->ui2_what_it_own;
          (at_sort_buf + (at_sort_buf + ui4_index)->ui2_what_it_should)->ui2_where_it_is =(UINT16) ui4_index;
          
          /*copy back the backup data*/
          (at_sort_buf + ui4_where_target)->ui2_what_it_own = (UINT16)ui4_what_visited_own;
          (at_sort_buf + ui4_what_visited_own)->ui2_where_it_is = (UINT16)ui4_where_target;
          
            /***Swap at_sort_buf**/
            i4_ret=pt_this->pf_swap(pt_this->pv_owner,
                    pt_this->e_sorting_group,
                    ui4_index,
                    ui4_where_target);
  
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }

        if(MMPR_OK != i4_ret)
        {
            break;
        }

        for(ui4_index = 0; ui4_index < ui4_mapping_count; ui4_index++)
        {
            if(at_mappings[ui4_index].ui4_idx_before_sort >= ui4_count)
            {
                at_mappings[ui4_index].b_successful = FALSE;
                continue;
            }

            at_mappings[ui4_index].ui4_idx_after_sort = (at_sort_buf + at_mappings[ui4_index].ui4_idx_before_sort)->ui2_where_it_is;
            at_mappings[ui4_index].b_successful = TRUE;
        }

    } while(0);

    c_mem_free(at_sort_buf);

    MMP_TMS_SPLIT("After calling mmp_sort_flow_do_sort ", i4_ret);
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: mmp_sort_flow_get_node
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_flow_get_node(VOID* pv_flow,
                            MMP_SORT_GROUP_ID_T e_group ,
                            UINT32 ui4_node_idx,
                            MMP_SORT_ACCESS_TYPE_T e_access ,                            
                            VOID** pv_node)
{
    MMP_Sort_Flow*              pt_this=(MMP_Sort_Flow*)pv_flow;
    INT32                        i4_ret; 
    _MMP_SORT_GROUP_DATA_T*      pt_group;
    UINT32                       ui4_node_offset;
    UINT32                       ui4_tmp, ui4_needed,ui4_page_nodes;
    UINT32                       ui4_page_idx,ui4_index;
    _MMP_SORT_PAGE_T             *pt_contain_page;
    
    
    MMP_ASSERT(pt_this&&e_group < MMP_SORT_GROUP_ID_COUNT);

    if(!b_g_right)/*Maybe date not ready*/
    {
        return MMPR_OK;
    }

    pt_group = &pt_this->at_group[e_group];

    if(MMP_SORT_ACCESS_TYPE_REF == e_access)
    {
        if(ui4_node_idx >= pt_group->ui4_buf_count)
        {
            b_g_right=FALSE;
            DBG_LOG_PRINT(("get_node fail buf_count %d\n",pt_group->ui4_buf_count));
            return MMPR_INV_ARG;
        }
    }
    else /*_MMP_SORT_ACCESS_TYPE_NEW*/
    {
        if(ui4_node_idx >= pt_group->ui4_buf_count)
        {
            MMP_ASSERT(pt_group->ui4_nodes_per_page!=0);
            
            ui4_page_nodes = pt_group->ui4_nodes_per_page;

            ui4_tmp = ui4_node_idx + 1 - pt_group->ui4_buf_count + ui4_page_nodes - 1;
            ui4_needed = ui4_tmp / ui4_page_nodes;
            
            i4_ret=_mmp_sort_flow_new_page(pt_this, e_group, ui4_needed);
            IS_MMPR_OK(i4_ret);
        }
    }
   
    ui4_node_offset = ui4_node_idx % pt_group->ui4_nodes_per_page;
    ui4_page_idx = ui4_node_idx / pt_group->ui4_nodes_per_page;
    
    pt_contain_page = pt_group->pt_pages;
    for(ui4_index = 0; ui4_index < ui4_page_idx; ui4_index++)
    {
        MMP_ASSERT(pt_contain_page);
        pt_contain_page = (pt_contain_page)->pt_next;
    }
    MMP_ASSERT(pt_contain_page);
    
    *pv_node = pt_contain_page->pt_buf + (ui4_node_offset  * pt_group->z_node_size);

    MMP_ASSERT(pv_node);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_sort_get_item_name
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_get_item_name(VOID* pv_flow,
                             UINT8 ui1_ff_id,
                             VOID* pv_data,
                             VOID* pv_data2,
                             CHAR** pps_name)
{
    MMP_Sort_Flow*              pt_this=(MMP_Sort_Flow*)pv_flow;
    INT32                       i4_ret; 
    _MMP_SORT_GROUP_DATA_T*     pt_group;
    MMP_SORT_CACHE_INFO_T       *pt_found = NULL, *pt_victim = NULL;
    UINT32                      i, ui4_ts_diff = 0;
    FM_DIR_ENTRY_T              t_entry;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }

    if (pt_this->b_cancel_sort)
    {
        return MMPR_FAIL;
    }

    pt_group = &pt_this->at_group[pt_this->e_sorting_group];
    pt_group->ui4_cache_ref_ts++;

    do {
        /*Check if this item falls in cache list*/
        for (i = 0; i < pt_group->ui4_cache_cnt; i++)
        {
            if (pt_group->at_cache_info[i].pv_data == MMP_SORT_ITEM_INFO_INVALD_DATA)
            {
                /*It's a free item*/
                pt_victim = &pt_group->at_cache_info[i];
                break;
            }
            else if (pt_group->at_cache_info[i].pv_data == pv_data &&
                     pt_group->at_cache_info[i].pv_data2 == pv_data2)
            {
                /*Found item in cache*/
                pt_found = &pt_group->at_cache_info[i];
                break;
            }
            
            /*Not Found,Travel To Find One to replace*/
            if (pt_group->ui4_cache_ref_ts - pt_group->at_cache_info[i].ui4_ref_ts > ui4_ts_diff)
            {
                pt_victim = &pt_group->at_cache_info[i];
                ui4_ts_diff = pt_group->ui4_cache_ref_ts - pt_group->at_cache_info[i].ui4_ref_ts;
            }
        }
        if (NULL != pt_found)
        {
            break;
        }

        /*Cache miss, delete oldest item in cache, and replace with reqeusted one*/
        MMP_RET_WITH_ASSERT(NULL != pt_victim, return MMPR_INTERNAL_ERROR);
        if (pt_victim->fid != MMP_FID_NULL_REC_IDX)
        {
            i4_ret = mmp_fid_del(pt_victim->fid);
            if(MMPR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
        }
        MMP_SORT_RESET_CACHE_INFO(pt_victim);

        pt_found = pt_victim;
        pt_found->pv_data = pv_data;
        pt_found->pv_data2 = pv_data2;

        /*Get dir entry from file filter*/
        i4_ret = mmp_ff_get_item_entry(ui1_ff_id, pv_data, pv_data2, &t_entry);
        if(MMPR_OK != i4_ret)
        {
            pt_this->b_cancel_sort = TRUE;
            return MMPR_FAIL;
        }

        i4_ret = mmp_fid_add(t_entry.s_name, &pt_found->fid);
        if(MMPR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }
    } while (0);

    MMP_ASSERT(pt_found);

    pt_found->ui4_ref_ts = pt_group->ui4_cache_ref_ts;
    i4_ret = mmp_fid_get(pt_found->fid, pps_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_fid_get(%d) failed. i4_ret = %d.\r\n", pt_found->fid, i4_ret));
        pt_this->b_cancel_sort = TRUE;
        return i4_ret;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_sort_flow_do_cmd
 * Description: 
 * Inputs:  
 * Outputs: 
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_flow_do_cmd(VOID* pv_flow, MMP_SORT_CMD_ID_T e_cmd_id, VOID* pv_param)
{
    MMP_Sort_Flow*              pt_this=(MMP_Sort_Flow*)pv_flow;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }

    if (MMP_SORT_CMD_ID_REG_STATUS_NFY == e_cmd_id)
    {
        if (NULL == pv_param)
        {
            return MMPR_INV_ARG;
        }

        pt_this->pf_status_nfy = (mmp_sort_status_nfy)pv_param;
    }

    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: mmp_sort_flow_get_group
 * Description: 
 * Inputs:  
 * Outputs: 
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_sort_flow_get_group(VOID* pv_flow,
                            MMP_SORT_GROUP_ID_T *pe_group)
{
    MMP_Sort_Flow*              pt_this=(MMP_Sort_Flow*)pv_flow;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }
    
    *pe_group = pt_this->e_sorting_group;

    return MMPR_OK;
}



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
 * $RCSfile: mmp_sort_audio.c,v $
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
#include "u_minfo.h"
#include "c_minfo.h"
#include "c_dt.h"
#include "c_dbg.h"

#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/file_filter/mmp_ff.h"
#include "mmp/file_filter/mmp_fid.h"

#include "mmp/util/mmp_util.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_memory.h"

#include "mmp/sort/mmp_sort_flow.h"
#include "mmp/sort/a_mmp_sort.h"
#include "mmp/video_engine/video_engine.h"

#include "app_util/splayer/splayer.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef MMP_SORT_AUDIO_MAX_CACHE_SIZE
#define MMP_SORT_AUDIO_MAX_CACHE_SIZE ((UINT32)50)
#endif

//#define MMP_SORT_AUDIO_LOG_ENABLE
#define USE_ID3_DATA
#define MAX_METADATA_STRING_LENGTH  (256)

typedef struct __AUD_NODE_T
{
    VOID*                       pv_data;
    VOID*                       pv_data2;
    UTF16_T                     w2s_file_name[MMP_SORT_RC_INFO_LENG];
    UTF16_T                     w2s_song_name[MMP_SORT_RC_INFO_LENG];
    UTF16_T                     w2s_artist[MMP_SORT_RC_INFO_LENG];
    UTF16_T                     w2s_album[MMP_SORT_RC_INFO_LENG];
    CHAR                        aud_artist[MAX_METADATA_STRING_LENGTH];
    CHAR                        aud_album [MAX_METADATA_STRING_LENGTH];
#ifndef APP_MMP_SORT_WITH_CACHE
    FID_T                       t_fid;
#endif
} _AUD_NODE_T;

typedef struct __MMP_AUD_DATA_MEMBER_T
{
    VOID                       *pv_engine;
    UINT32                     aui4_node_count[MMP_SORT_GROUP_ID_COUNT];
    HANDLE_T                   h_minfo;
    UINT8                      ui1_filter_id;
    MMP_SORT_TYPE_T            e_sort_type;
} _MMP_AUD_DATA_MEMBER_T;
typedef enum
{
    _MMP_VE_ELMT_TYPE_UNKNOWN,
    _MMP_VE_ELMT_TYPE_AUDIO,
    _MMP_VE_ELMT_TYPE_VIDEO
} _MMP_VE_ELMT_TYPE_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
BOOL    b_g_right = TRUE;

/*-----------------------------------------------------------------------------
 * private function declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_is_supported(
        MMP_SORT_TYPE_T         e_sort,
        BOOL*                   pb_is_supported);

static INT32 _mmp_sort_aud_compare(
        MMP_SORT_GROUP_ID_T     e_group,
        UINT32                  ui4_node_index_a,
        UINT32                  ui4_node_index_b,
        VOID*                   pv_owner);

static INT32  _mmp_sort_aud_swap_items(
        VOID*                   pv_this,
        MMP_SORT_GROUP_ID_T     e_group,
        UINT32                  ui4_node_index_a,
        UINT32                  ui4_node_index_b);

/*-----------------------------------------------------------------------------
 * private function implements
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_aud_is_supported
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_is_supported(
        MMP_SORT_TYPE_T         e_sort,
        BOOL*                   pb_is_supported)
{
    if(NULL == pb_is_supported)
    {
        return MMPR_INV_ARG;
    }

    switch(e_sort)
    {
        case MMP_SORT_TYPE_AUD_NAME:
        case MMP_SORT_TYPE_AUDIO_INV_NAME:
        case MMP_SORT_TYPE_AUD_ARTIST:
        case MMP_SORT_TYPE_AUD_INV_ARTIST:
        case MMP_SORT_TYPE_AUD_ALBUM:
        case MMP_SORT_TYPE_AUD_INV_ALBUM:
        case MMP_SORT_TYPE_AUD_TITLE:
        case MMP_SORT_TYPE_AUD_INV_TITLE:
            *pb_is_supported = TRUE;
            break;

        default:
            *pb_is_supported = FALSE;
    }

    return MMPR_OK;
}

#ifndef APP_MMP_SORT_WITH_CACHE
/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_aud_clear_fid
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_clear_fid(_MMP_AUD_DATA_MEMBER_T* pt_this)
{
    UINT8                   ui1_index;
    MMP_SORT_GROUP_ID_T     e_group;
    UINT32                  ui4_node_count, ui4_i;
    _AUD_NODE_T*            pt_node;
    INT32                   i4_ret;

    if (MMP_SORT_TYPE_AUD_NAME       != pt_this->e_sort_type &&
        MMP_SORT_TYPE_AUDIO_INV_NAME != pt_this->e_sort_type)
    {
        return MMPR_OK;
    }

    for(ui1_index=0; ui1_index < (UINT8)MMP_SORT_RC_MAX; ui1_index++)
    {
        MMP_SORT_GROUP_GET(ui1_index,e_group);
        ui4_node_count = pt_this->aui4_node_count[e_group];

        for (ui4_i = 0; ui4_i < ui4_node_count; ui4_i++)
        {
            i4_ret =  mmp_sort_flow_get_node(pt_this->pv_engine,
                                             e_group ,
                                             ui4_i,
                                             MMP_SORT_ACCESS_TYPE_REF,
                                             (VOID*)&pt_node);
            if (MMPR_OK != i4_ret)
            {
                continue;
            }

            if (MMP_FID_NULL_REC_IDX == pt_node->t_fid)
            {
                continue;
            }

            i4_ret = mmp_fid_del(pt_node->t_fid);
            if (MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_fid_del failed. i4_ret = %d.\r\n", i4_ret));
            }

            pt_node->t_fid = MMP_FID_NULL_REC_IDX;
        }
        pt_this->aui4_node_count[e_group] = 0;
    }

    return MMPR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_do_cmd
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_do_cmd(
    VOID*                       pv_inst,
    MMP_SORT_CMD_ID_T           e_id,
    VOID*                       pv_param)
{
    INT32                       i4_ret = MMPR_OK;
    _MMP_AUD_DATA_MEMBER_T*     pt_this = (_MMP_AUD_DATA_MEMBER_T*)pv_inst;
    MMP_SORT_PARAM_T*           pt_sort_param = NULL;
    UINT32                      ui4_mapping_count = 0;
    MMP_MAPPING_NODE_T*         at_mappings = NULL;
    UINT8                       ui1_index = 0;
    MMP_SORT_GROUP_ID_T         e_group = MMP_SORT_GROUP_ID_FILE;
    UINT32                      ui4_cache_size = 0;
    UINT32                      ui4_max_cnt = 0;

    if(MMP_SORT_CMD_ID_SORT == e_id)
    {
        ui4_max_cnt = (MMP_SORT_GROUP_ID_FILE == e_group) ? MMP_FF_FILE_MAX_COUNT : MMP_FF_FOLDER_MAX_COUNT;

        if (0 == pt_this->aui4_node_count[e_group] ||
            pt_this->aui4_node_count[e_group] > ui4_max_cnt)
        {
            return MMPR_OK;
        }

        pt_sort_param = (MMP_SORT_PARAM_T*)pv_param;

        for(ui1_index = 0; ui1_index < (UINT8)MMP_SORT_RC_MAX; ui1_index++)
        {
            MMP_SORT_GROUP_GET(ui1_index,e_group);

            if(pt_sort_param)
            {
                if(0 == ui1_index)
                {
                    ui4_mapping_count = (pt_sort_param->at_file_nodes) ? pt_sort_param->ui4_file_table_count : 0;
                    at_mappings = pt_sort_param->at_file_nodes;
                }
                else if(1 == ui1_index)
                {
                    ui4_mapping_count = (pt_sort_param->at_dir_nodes) ? pt_sort_param->ui4_dir_table_count : 0;
                    at_mappings = pt_sort_param->at_dir_nodes;
                }
                else
                {
                    ui4_mapping_count = 0;
                    at_mappings = NULL;
                }
            }
            else
            {
                ui4_mapping_count = 0;
                at_mappings = NULL;
            }

            /*Check cache size*/
            if (pt_this->aui4_node_count[e_group] > MMP_SORT_AUDIO_MAX_CACHE_SIZE)
            {
                ui4_cache_size = MMP_SORT_AUDIO_MAX_CACHE_SIZE;
            }
            else
            {
                ui4_cache_size = pt_this->aui4_node_count[e_group];
            }

            i4_ret = mmp_sort_flow_do_sort(pt_this->pv_engine,
                                           e_group,
                                           pt_this->aui4_node_count[e_group],
                                           ui4_cache_size,
                                           ui4_mapping_count,
                                           at_mappings);
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
        }

        /*Free page*/
        if(_MMP_SORT_RC_IS_FREE_DATA_AFTER_SORT())
        {
#ifndef APP_MMP_SORT_WITH_CACHE
            i4_ret = _mmp_sort_aud_clear_fid(pt_this);
            MMPR_LOG_ON_FAIL(i4_ret);
#endif
            i4_ret = mmp_sort_free_page(pt_this->pv_engine);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }
    else if (MMP_SORT_CMD_ID_REG_STATUS_NFY == e_id)
    {
        return mmp_sort_flow_do_cmd(pt_this->pv_engine, e_id, pv_param);
    }
    else if (MMP_SORT_CMD_ID_CHANGE == e_id)
    {
        pt_this->e_sort_type = *((MMP_SORT_TYPE_T*)(UINT32*)pv_param);
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_select_audio_sort_type
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_select_sort_type(
        _AUD_NODE_T*            pt_node_a,
        _AUD_NODE_T*            pt_node_b,
        _MMP_AUD_DATA_MEMBER_T* pt_this)
{
    INT32   i4_ret = MMPR_OK;
    CHAR*   ps_filea_name = NULL;
    CHAR*   ps_fileb_name = NULL;

#ifdef MMP_SORT_AUDIO_LOG_ENABLE
    CHAR*  ps_node_a_file_name = NULL;
    CHAR*  ps_node_b_file_name = NULL;
    CHAR*  ps_node_a_album = NULL;
    CHAR*  ps_node_b_album = NULL;
    CHAR*  ps_node_a_artist = NULL;
    CHAR*  ps_node_b_artist = NULL;
#endif

    MMP_SORT_GROUP_ID_T e_group = MMP_SORT_GROUP_ID_FILE;

    i4_ret = mmp_sort_flow_get_group(pt_this->pv_engine, &e_group);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (MMP_SORT_GROUP_ID_FOLDER == e_group)
    {
#ifdef APP_MMP_SORT_WITH_CACHE
        i4_ret = mmp_sort_get_item_name(pt_this->pv_engine,
                                        pt_this->ui1_filter_id,
                                        pt_node_a->pv_data,
                                        pt_node_a->pv_data2,
                                        &ps_filea_name);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_sort_get_item_name failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_OK;
        }

        i4_ret = mmp_sort_get_item_name(pt_this->pv_engine,
                                        pt_this->ui1_filter_id,
                                        pt_node_b->pv_data,
                                        pt_node_b->pv_data2,
                                        &ps_fileb_name);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_sort_get_item_name failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_OK;
        }
#else
        i4_ret = mmp_fid_get(pt_node_a->t_fid, &ps_filea_name);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_get failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_OK;
        }

        i4_ret = mmp_fid_get(pt_node_b->t_fid, &ps_fileb_name);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_get failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_OK;
        }
#endif

        /*Ignore node .. 1 swap, -1 not swap*/
        if(ps_filea_name &&
           0 == c_strcmp(ps_filea_name, ".."))
        {
            return -1;
        }

        if(ps_fileb_name &&
           0 == c_strcmp(ps_fileb_name, ".."))
        {
            return 1;
        }

        return MMPR_OK;
    }
    else
    {
        i4_ret = mmp_fid_get(pt_node_a->t_fid, &ps_filea_name);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_get failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_OK;
        }

        i4_ret = mmp_fid_get(pt_node_b->t_fid, &ps_fileb_name);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_get failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_OK;
        }
    }


    switch(pt_this->e_sort_type)
    {
        case MMP_SORT_TYPE_AUD_NAME:
        case MMP_SORT_TYPE_AUDIO_INV_NAME:
        {
            //i4_ret = c_uc_w2s_strcmp(pt_node_a->w2s_file_name, pt_node_b->w2s_file_name);
            i4_ret = c_strcmp(ps_filea_name, ps_fileb_name);
            MMP_DBG_INFO(("[%s %d]i4_ret == %d\n",__FUNCTION__,__LINE__,i4_ret));

        #ifdef MMP_SORT_AUDIO_LOG_ENABLE
            ps_node_a_file_name = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_a_file_name)
            {
                c_uc_w2s_to_ps(pt_node_a->w2s_file_name, ps_node_a_file_name,100);
            }

            ps_node_b_file_name = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_b_file_name)
            {
                c_uc_w2s_to_ps(pt_node_b->w2s_file_name, ps_node_b_file_name,100);
            }

            //DBG_LOG_PRINT(("\n%s,%s,%d,ps_node_a_file_name=%s,ps_node_b_file_name=%s,i4_ret=%d\n",
              //          __FILE__, __FUNCTION__, __LINE__,
                //        ps_node_a_file_name, ps_node_b_file_name, i4_ret));

            if (ps_node_a_file_name)
            {
                c_mem_free(ps_node_a_file_name);
                ps_node_a_file_name = NULL;
            }

            if (ps_node_b_file_name)
            {
                c_mem_free(ps_node_b_file_name);
                ps_node_b_file_name = NULL;
            }
        #endif

            if (MMP_SORT_TYPE_AUDIO_INV_NAME == pt_this->e_sort_type)
            {
                return i4_ret * (-1) > 0 ? 1: -1;
            }
            else
            {
                return i4_ret > 0 ? 1: -1;
            }
        }
            break;
        case MMP_SORT_TYPE_AUD_ALBUM://9 A-Z
        case MMP_SORT_TYPE_AUD_INV_ALBUM://10 Z-A
        {
            CHAR                        node_aud_album_a [MAX_METADATA_STRING_LENGTH];
            CHAR                        node_aud_album_b [MAX_METADATA_STRING_LENGTH];
            c_memset(node_aud_album_a,0,MAX_METADATA_STRING_LENGTH);
            c_memset(node_aud_album_b,0,MAX_METADATA_STRING_LENGTH);
            c_strncpy(node_aud_album_a, pt_node_a->aud_album, MAX_METADATA_STRING_LENGTH-1);
            c_strncpy(node_aud_album_b, pt_node_b->aud_album, MAX_METADATA_STRING_LENGTH-1);

            i4_ret = c_strcmp(node_aud_album_a,node_aud_album_b);
            if (0 == i4_ret)
            {
                //i4_ret = c_uc_w2s_strcmp(pt_node_a->w2s_file_name, pt_node_b->w2s_file_name);
                i4_ret = c_strcmp(ps_filea_name, ps_fileb_name);
            }

        #ifdef MMP_SORT_AUDIO_LOG_ENABLE
            ps_node_a_album = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_a_album)
            {
                c_uc_w2s_to_ps(pt_node_a->w2s_album, ps_node_a_album,100);
            }

            ps_node_b_album = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_b_album)
            {
                c_uc_w2s_to_ps(pt_node_b->w2s_album, ps_node_b_album,100);
            }

            ps_node_a_file_name = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_a_file_name)
            {
                c_uc_w2s_to_ps(pt_node_a->w2s_file_name, ps_node_a_file_name,100);
            }

            ps_node_b_file_name = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_b_file_name)
            {
                c_uc_w2s_to_ps(pt_node_b->w2s_file_name, ps_node_b_file_name,100);
            }

            DBG_LOG_PRINT(("\n%s,%s,%d,ps_node_a_album=%s,ps_node_b_album=%s,"
                       "ps_node_a_file_name=%s,ps_node_b_file_name=%s,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        ps_node_a_album, ps_node_b_album,
                        ps_node_a_file_name, ps_node_b_file_name, i4_ret));

            if (ps_node_a_album)
            {
                c_mem_free(ps_node_a_album);
                ps_node_a_album = NULL;
            }

            if (ps_node_b_album)
            {
                c_mem_free(ps_node_b_album);
                ps_node_b_album = NULL;
            }

            if (ps_node_a_file_name)
            {
                c_mem_free(ps_node_a_file_name);
                ps_node_a_file_name = NULL;
            }

            if (ps_node_b_file_name)
            {
                c_mem_free(ps_node_b_file_name);
                ps_node_b_file_name = NULL;
            }
        #endif

            if (MMP_SORT_TYPE_AUD_INV_ALBUM == pt_this->e_sort_type)
            {
                return i4_ret * (-1) > 0 ? 1: -1;
            }
            else
            {
                return i4_ret > 0 ? 1: -1;
            }
        }
            break;
        case MMP_SORT_TYPE_AUD_ARTIST:
        case MMP_SORT_TYPE_AUD_INV_ARTIST:
        {
            //i4_ret = c_uc_w2s_strcmp(pt_node_a->w2s_artist, pt_node_b->w2s_artist);
            i4_ret = c_strcmp(pt_node_a->aud_artist,pt_node_b->aud_artist);
            if (0 == i4_ret)
            {
                i4_ret = c_strcmp(ps_filea_name, ps_fileb_name);
            }

        #ifdef MMP_SORT_AUDIO_LOG_ENABLE
            ps_node_a_artist = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_a_artist)
            {
                c_uc_w2s_to_ps(pt_node_a->w2s_artist, ps_node_a_artist,100);
            }

            ps_node_b_artist = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_b_artist)
            {
                c_uc_w2s_to_ps(pt_node_b->w2s_artist, ps_node_b_artist,100);
            }

            ps_node_a_file_name = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_a_file_name)
            {
                c_uc_w2s_to_ps(pt_node_a->w2s_file_name, ps_node_a_file_name,100);
            }

            ps_node_b_file_name = c_mem_alloc(101*sizeof(CHAR));
            if (ps_node_b_file_name)
            {
                c_uc_w2s_to_ps(pt_node_b->w2s_file_name, ps_node_b_file_name,100);
            }

            DBG_LOG_PRINT(("\n%s,%s,%d,ps_node_a_artist=%s,ps_node_b_artist=%s"
                        ",ps_node_a_file_name=%s,ps_node_b_file_name=%s,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        ps_node_a_artist, ps_node_b_artist,
                        ps_node_a_file_name, ps_node_b_file_name, i4_ret));

            if (ps_node_a_artist)
            {
                c_mem_free(ps_node_a_artist);
                ps_node_a_artist = NULL;
            }

            if (ps_node_b_artist)
            {
                c_mem_free(ps_node_b_artist);
                ps_node_b_artist = NULL;
            }

            if (ps_node_a_file_name)
            {
                c_mem_free(ps_node_a_file_name);
                ps_node_a_file_name = NULL;
            }

            if (ps_node_b_file_name)
            {
                c_mem_free(ps_node_b_file_name);
                ps_node_b_file_name = NULL;
            }
        #endif

            if (MMP_SORT_TYPE_AUD_INV_ARTIST == pt_this->e_sort_type)
            {
                return i4_ret * (-1) > 0 ? 1: -1;
            }
            else
            {
                return i4_ret > 0 ? 1: -1;
            }
        }
            break;
        case MMP_SORT_TYPE_AUD_TITLE:
        case MMP_SORT_TYPE_AUD_INV_TITLE:
        {
            i4_ret = c_uc_w2s_strcmp(pt_node_a->w2s_song_name, pt_node_b->w2s_song_name);

            if (0 == i4_ret)
            {
                i4_ret = c_uc_w2s_strcmp(pt_node_a->w2s_file_name, pt_node_b->w2s_file_name);
            }

            if (MMP_SORT_TYPE_AUD_INV_TITLE == pt_this->e_sort_type)
            {
                return i4_ret * (-1) > 0 ? 1: -1;
            }
            else
            {
                return i4_ret > 0 ? 1: -1;
            }
        }
            break;
        default:
            return MMPR_OK;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_aud_compare
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_compare(
        MMP_SORT_GROUP_ID_T     e_group,
        UINT32                  ui4_node_index_a,
        UINT32                  ui4_node_index_b,
        VOID*                   pv_owner)
{
    _MMP_AUD_DATA_MEMBER_T* pt_this = (_MMP_AUD_DATA_MEMBER_T*)pv_owner;
    _AUD_NODE_T*            pt_node_a = NULL;
    _AUD_NODE_T*            pt_node_b = NULL;
    INT32                   i4_ret = MMPR_OK;

    MMP_ASSERT(pv_owner && e_group < MMP_SORT_GROUP_ID_COUNT);

    i4_ret = mmp_sort_flow_get_node(pt_this->pv_engine,
                                    e_group ,
                                    ui4_node_index_a,
                                    MMP_SORT_ACCESS_TYPE_REF,
                                    (VOID*)&pt_node_a);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_sort_aud_get_node(idx = %d) failed. i4_ret = %d.\r\n", ui4_node_index_a, i4_ret));
        return i4_ret;
    }
    i4_ret = mmp_sort_flow_get_node(pt_this->pv_engine,
                                    e_group,
                                    ui4_node_index_b,
                                    MMP_SORT_ACCESS_TYPE_REF,
                                    (VOID*)&pt_node_b);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_sort_aud_get_node(idx = %d) failed. i4_ret = %d.\r\n", ui4_node_index_b, i4_ret));
        return i4_ret;
    }

    i4_ret = _mmp_sort_aud_select_sort_type(pt_node_a,
                                            pt_node_b,
                                            pt_this);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_aud_update_aud_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_update_item(
        VOID*                       pv_inst,
        MMP_ITEM_TYPE_T             e_type,
        UINT32                      ui4_max_count,
        UINT32                      ui4_idx,
        const MMP_SORT_ITEM_INFO_T* pt_info)
{
    INT32                   i4_ret = MMPR_OK;
    _MMP_AUD_DATA_MEMBER_T* pt_this = (_MMP_AUD_DATA_MEMBER_T*)pv_inst;
    _AUD_NODE_T*            pt_node = NULL;
    MMP_SORT_GROUP_ID_T     e_group = MMP_SORT_GROUP_ID_FILE;
    SIZE_T                  z_size = sizeof(MINFO_INFO_T);
    UINT32                  ui4_max_cnt = 0;
    MINFO_INFO_T            t_minfo_info;
#ifdef USE_ID3_DATA
    MINFO_TYPE_ID3_TAG_T*   pt_id3_date = &t_minfo_info.u.t_id3_data;
#else
    MINFO_TYPE_META_DATA_T* pt_meta_date = &t_minfo_info.u.t_meta_data;
#endif
    MEDIA_FORMAT_T          t_format;
    CHAR                    s_item_name[MMP_RC_PATH_MAX_LEN + 1];
    SIZE_T                  z_item_name_size = MMP_RC_PATH_MAX_LEN + 1;
#ifdef MMP_SORT_AUDIO_LOG_ENABLE
    CHAR*                   ps_album = NULL;
    CHAR*                   ps_artist = NULL;
#endif
    APPL_SPLAYER_MEDIA_INFO_T tMediaInfo;

    c_memset(&t_minfo_info,0,sizeof(MINFO_INFO_T));
    c_memset(&t_format,0,sizeof(MEDIA_FORMAT_T));
    c_memset(&tMediaInfo,0,sizeof(APPL_SPLAYER_MEDIA_INFO_T));

    MMP_TMS_RESET("Before calling _mmp_sort_aud_update_item ");

    if (ITEM_TYPE_DIR != e_type &&
        ITEM_TYPE_FILE != e_type)
    {
        return MMPR_OK;
    }

    e_group = (ITEM_TYPE_FILE == e_type) ? MMP_SORT_GROUP_ID_FILE : MMP_SORT_GROUP_ID_FOLDER;

    /*Check if exceed max limit*/
    ui4_max_cnt = (ITEM_TYPE_FILE == e_type) ? MMP_FF_FILE_MAX_COUNT : MMP_FF_FOLDER_MAX_COUNT;
    if((ui4_idx+1) > ui4_max_cnt)
    {
        return MMPR_OK;
    }

    if((ui4_idx+1) > pt_this->aui4_node_count[e_group])
    {
        pt_this->aui4_node_count[e_group]++;
    }

    if(!b_g_right)/*Maybe date not ready*/
    {
        return MMPR_OK;
    }

    /**/
    i4_ret = mmp_sort_flow_get_node(pt_this->pv_engine,
                                    e_group,
                                    ui4_idx,
                                    MMP_SORT_ACCESS_TYPE_NEW,
                                    (VOID*)&pt_node);
    if(MMPR_OK != i4_ret)
    {
        b_g_right = FALSE;
        MMP_DBG_ERROR(("_mmp_sort_aud_get_node(idx = %d) failed. i4_ret = %d.\r\n", ui4_idx, i4_ret));
        return i4_ret;
    }

    //c_memset(pt_node, 0, sizeof(_AUD_NODE_T));

    if (MMP_SORT_ITEM_INFO_FIELD_PATH & pt_info->ui4_field)
    {
        c_strncpy(s_item_name, pt_info->ps_path, z_item_name_size);
        s_item_name[MMP_RC_PATH_MAX_LEN] = 0;
    }
    else
    {
        c_memset(s_item_name, 0, sizeof(s_item_name));
    }

#ifndef APP_MMP_SORT_WITH_CACHE
    pt_node->t_fid = MMP_FID_NULL_REC_IDX;

    if (MMP_SORT_ITEM_INFO_FIELD_PATH & pt_info->ui4_field)
    {
        i4_ret = mmp_fid_add(c_strrchr(s_item_name, MMP_RC_FOLDER_TOKEN) + 1,
                                       &pt_node->t_fid);
    }
    else
    {
        i4_ret = mmp_fid_add("..", &pt_node->t_fid);
    }

    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
#endif
    /*Field pv_data*/
    //pt_node->pv_data = pt_info->pv_data;
    //pt_node->pv_data2 = pt_info->pv_data2;

    if (MMP_SORT_GROUP_ID_FILE == e_group)
    {
#ifdef NEVER
        t_format.e_media_type = MEDIA_TYPE_UNKNOWN;
        t_format.t_media_subtype.u.e_aud_subtype = MEDIA_AUD_SUBTYPE_UNKNOWN;

        i4_ret = c_minfo_fopen_sync(
                            s_item_name,
                            &t_format,
                            &pt_this->h_minfo);
        /*Maybe node..*/
        if (MMPR_OK != i4_ret)
        {
            c_minfo_close(pt_this->h_minfo);
            return MMPR_OK;
        }

        c_uc_ps_to_w2s(c_strrchr(s_item_name, MMP_RC_FOLDER_TOKEN) + 1,
                       pt_node->w2s_file_name,
                       MMP_SORT_RC_INFO_LENG);

    #ifdef USE_ID3_DATA
        /*Field *w2s_song_name*/
        pt_id3_date->pwc_str_id3_title = pt_node->w2s_song_name;
        pt_id3_date->z_id3_title_len = MMP_SORT_RC_INFO_LENG;

        /*Field *w2s_artist*/
        pt_id3_date->pwc_str_id3_artist = pt_node->w2s_artist;
        pt_id3_date->z_id3_artist_len = MMP_SORT_RC_INFO_LENG;

        /*Field *w2s_album*/
        pt_id3_date->pwc_str_id3_album = pt_node->w2s_album;
        pt_id3_date->z_id3_album_len = MMP_SORT_RC_INFO_LENG;

        z_size = sizeof(MINFO_INFO_T);
        i4_ret = c_minfo_get_info(pt_this->h_minfo,
                                  MINFO_INFO_TYPE_ID3_DATA,
                                  1,
                                  (VOID*)(&t_minfo_info),
                                  &z_size);
        if(MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("c_minfo_get_info Line %d Fail\n", __LINE__,i4_ret));
        }
    #else
        /*Field *w2s_song_name*/
        pt_meta_date->pwc_str_title = pt_node->w2s_song_name;
        pt_meta_date->z_title_len = MMP_SORT_RC_INFO_LENG;

        /*Field *w2s_artist*/
        pt_meta_date->pwc_str_artist = pt_node->w2s_artist;
        pt_meta_date->z_artist_len = MMP_SORT_RC_INFO_LENG;

        /*Field *w2s_album*/
        pt_meta_date->pwc_str_album = pt_node->w2s_album;
        pt_meta_date->z_album_len = MMP_SORT_RC_INFO_LENG;

        z_size = sizeof(MINFO_INFO_T);
        i4_ret = c_minfo_get_info(pt_this->h_minfo,
                                  MINFO_INFO_TYPE_META_DATA,
                                  1,
                                  (VOID*)(&t_minfo_info),
                                  &z_size);
        if(MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("c_minfo_get_info Line %d Fail\n", __LINE__,i4_ret));
        }
    #endif

    #ifdef MMP_SORT_AUDIO_LOG_ENABLE
        ps_album = c_mem_alloc(101*sizeof(CHAR));
        if (ps_album)
        {
            c_uc_w2s_to_ps(pt_node->w2s_album, ps_album,100);
        }

        ps_artist = c_mem_alloc(101*sizeof(CHAR));
        if (ps_artist)
        {
            c_uc_w2s_to_ps(pt_node->w2s_artist, ps_artist,100);
        }

        DBG_LOG_PRINT(("\ns_item_name=%s,ps_album=%s,ps_artist=%s\n",
                    s_item_name, ps_album, ps_artist));

        if (ps_album)
        {
            c_mem_free(ps_album);
            ps_album = NULL;
        }

        if (ps_artist)
        {
            c_mem_free(ps_artist);
            ps_artist = NULL;
        }
    #endif

        i4_ret = c_minfo_close(pt_this->h_minfo);
        MMPR_LOG_ON_FAIL (i4_ret);
#else
    //open
    MMP_DBG_INFO(("[%s %d]s_item_name == %s\n",__FUNCTION__,__LINE__,s_item_name));
    i4_ret =_appl_splayer_audio_sort_open(s_item_name,
                                          NULL,
                                          &tMediaInfo,
                                          NULL);
    if(APPL_SPLAYER_SUCCESS != i4_ret)
    {
        MMP_DBG_ERROR(("{MMP}[%s:%d]_appl_splayer_open_info failed. returns: %d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }
    else
    {
        MMP_DBG_INFO(("$ [media open] open file %s...\n", s_item_name));
        MMP_DBG_INFO(("$ [media open] file handle = %08x\n", tMediaInfo.hMm));
        MMP_DBG_INFO(("$ [media open] file u64CallbackId = %08x\n", tMediaInfo.u64CallbackId));
        MMP_DBG_INFO(("$ [media open] file hAout = %08x\n", tMediaInfo.hAout));
        MMP_DBG_INFO(("$ [media open] file hDisp = %08x\n", tMediaInfo.hDisp));
    }

    // Get artist of music
    tMediaInfo.ui2AdID = MMP_VE_INFO_ID_ARTIST;
    i4_ret = a_appl_splayer_get_media_info(tMediaInfo.filePath, &tMediaInfo);
    if(APPL_SPLAYER_SUCCESS != i4_ret)
    {
        MMP_DBG_ERROR(("{MMP}[%s:%d]a_appl_splayer_get_media_info failed. returns: %d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    // Get album of music
    tMediaInfo.ui2AdID = MMP_VE_INFO_ID_ALBUM;
    i4_ret = a_appl_splayer_get_media_info(tMediaInfo.filePath, &tMediaInfo);

    if(APPL_SPLAYER_SUCCESS != i4_ret)
    {
        MMP_DBG_ERROR(("{MMP}[%s:%d]a_appl_splayer_get_media_info failed. returns: %d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }
    else
    {
        if(tMediaInfo.e_type != _MMP_VE_ELMT_TYPE_AUDIO)
        {
            MMP_DBG_INFO(("{MMP}[%s:%d]sort is not audio\r\n", __FUNCTION__, __LINE__));
        }
        else //audio
        {
            if(tMediaInfo.u32AlbumLen == 0)
            {
                MMP_DBG_INFO(("$ %s album is null\n", tMediaInfo.filePath));
                c_strcpy(tMediaInfo.szMetadataAlbum,"N/A");
            }
            if(tMediaInfo.u32ArtistLen == 0)
            {
                MMP_DBG_INFO(("$ %s artist is null\n", tMediaInfo.filePath));
                c_strcpy(tMediaInfo.szMetadataArtist,"N/A");
            }

            MMP_DBG_INFO(("{MMP}[%s:%d]tMediaInfo.szMetadataAlbum == %s\r\n", __FUNCTION__, __LINE__, tMediaInfo.szMetadataAlbum));
            MMP_DBG_INFO(("{MMP}[%s:%d]tMediaInfo.szMetadataArtist == %s\r\n", __FUNCTION__, __LINE__, tMediaInfo.szMetadataArtist));

            c_strcpy(pt_node->aud_album, tMediaInfo.szMetadataAlbum);
            c_strcpy(pt_node->aud_artist, tMediaInfo.szMetadataArtist);
            MMP_DBG_INFO(("[%s,%s,%d],pt_node->aud_album=%s,\n",__FILE__, __FUNCTION__, __LINE__,pt_node->aud_album));
            MMP_DBG_INFO(("[%s,%s,%d],pt_node->aud_artist=%s,\n",__FILE__, __FUNCTION__, __LINE__,pt_node->aud_artist));
        }
    }


    //close
    i4_ret = _appl_splayer_close_info(&tMediaInfo);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}close failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    /*Field pv_data*/
    pt_node->pv_data = pt_info->pv_data;
    pt_node->pv_data2 = pt_info->pv_data2;
#endif
    }

    MMP_TMS_SPLIT("After calling _mmp_sort_aud_update_item ", i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: __mmp_sort_aud_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_open(
        MMP_SORT_TYPE_T             e_sort,
        UINT8                       ui1_ff_id,
        VOID**                      ppv_inst)
{
    _MMP_AUD_DATA_MEMBER_T* pt_this = NULL;
    INT32                   i4_ret = MMPR_OK;
    BOOL                    b_is_supported = FALSE;

    /*check parameter*/
    if(NULL == ppv_inst)
    {
        return MMPR_INV_ARG;
    }

    /*check parameter*/
    i4_ret = _mmp_sort_aud_is_supported(e_sort, &b_is_supported);
    if (MMPR_OK != i4_ret ||
        FALSE == b_is_supported)
    {
        return MMPR_NOT_SUPPORT;
    }

    b_g_right = TRUE;

    /*alloc resource*/
    pt_this = (_MMP_AUD_DATA_MEMBER_T*)c_mem_alloc(sizeof(_MMP_AUD_DATA_MEMBER_T));
    if(NULL == pt_this)
    {
        MMP_DBG_ERROR(("Fail to alloc memory (size = %d). i4_ret = %d.\r\n", sizeof(_MMP_AUD_DATA_MEMBER_T)));
        return MMPR_OUT_OF_MEM;
    }

    /*Inital member*/
    c_memset(pt_this, 0, sizeof(_MMP_AUD_DATA_MEMBER_T));

    pt_this->aui4_node_count[MMP_SORT_GROUP_ID_FILE] = 0;
    pt_this->aui4_node_count[MMP_SORT_GROUP_ID_FOLDER] = 0;
    pt_this->ui1_filter_id = ui1_ff_id;
    pt_this->e_sort_type = e_sort;

    i4_ret = mmp_sort_flow_new_inst(sizeof(_AUD_NODE_T),
                                    (UINT32)MMP_SORT_RC_PAGE_SIZE,
                                    sizeof(_AUD_NODE_T),
                                    (UINT32)MMP_SORT_RC_PAGE_SIZE,
                                    _mmp_sort_aud_compare,
                                    _mmp_sort_aud_swap_items,
                                    pt_this,
                                    &(pt_this->pv_engine));
    if(MMPR_OK != i4_ret)
    {
        c_mem_free(pt_this);
        MMP_DBG_ERROR(("Fail to alloc memory \r\n"));
        return MMPR_OUT_OF_MEM;
    }

    *ppv_inst = pt_this;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: __mmp_sort_aud_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_close(VOID*           pv_inst)
{
    INT32                   i4_ret = MMPR_OK;
    _MMP_AUD_DATA_MEMBER_T* pt_this = (_MMP_AUD_DATA_MEMBER_T*)pv_inst;

    if(NULL == pv_inst)
    {
        return MMPR_OK;
    }

#ifndef APP_MMP_SORT_WITH_CACHE
    i4_ret = _mmp_sort_aud_clear_fid(pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = mmp_sort_free_page(pt_this->pv_engine);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_sort_flow_free_inst(pt_this->pv_engine);
    MMPR_LOG_ON_FAIL(i4_ret);

    pt_this->pv_engine = NULL;

    /**Free this inst**/
    c_mem_free(pt_this);
    pt_this = NULL;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_audio_query_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_sort_aud_query_info(
        VOID*                   pv_inst,
        MMP_SORT_QINFO_ID_T     e_id,
        VOID*                   pv_param)
{
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_sort_aud_swap_items
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _mmp_sort_aud_swap_items(
        VOID*                       pv_this,
        MMP_SORT_GROUP_ID_T         e_group,
        UINT32                      ui4_node_index_a,
        UINT32                      ui4_node_index_b)
{
    INT32                   i4_ret = MMPR_OK;
    _MMP_AUD_DATA_MEMBER_T* pt_this = (_MMP_AUD_DATA_MEMBER_T*)pv_this;
    _AUD_NODE_T*            pt_node_a = NULL;
    _AUD_NODE_T*            pt_node_b = NULL;
    _AUD_NODE_T             t_temp_node;
    MMP_ITEM_TYPE_T         e_item_type;

    MMP_ASSERT(pt_this && e_group < MMP_SORT_GROUP_ID_COUNT);

    e_item_type = (MMP_SORT_GROUP_ID_FILE == e_group) ? ITEM_TYPE_FILE : ITEM_TYPE_DIR;

    i4_ret = mmp_sort_flow_get_node(pt_this->pv_engine,
                                    e_group,
                                    ui4_node_index_a,
                                    MMP_SORT_ACCESS_TYPE_REF,
                                    (VOID*)&pt_node_a);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_sort_photo_get_node(idx = %d) failed. i4_ret = %d.\r\n", ui4_node_index_a, i4_ret));
        return i4_ret;
    }

    i4_ret = mmp_sort_flow_get_node(pt_this->pv_engine,
                                    e_group,
                                    ui4_node_index_b,
                                    MMP_SORT_ACCESS_TYPE_REF,
                                    (VOID*)&pt_node_b);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_sort_photo_get_node(idx = %d) failed. i4_ret = %d.\r\n", ui4_node_index_b, i4_ret));
        return i4_ret;
    }

    /********Swap node *******/
    t_temp_node = *pt_node_a;
    *pt_node_a  = *pt_node_b;
    *pt_node_b  = t_temp_node;

    /*swap data in file filter*/
    i4_ret = mmp_ff_swap_items(pt_this->ui1_filter_id,
                               e_item_type,
                               ui4_node_index_a,
                               ui4_node_index_b);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_ff_swap_items failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_reg_sort_aud
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_reg_sort_audio(VOID)
{
    MMP_SORT_INTF_T     t_intf;
    INT32               i4_ret = MMPR_OK;

    MMP_SORT_INTF_ZERO(t_intf);

    t_intf.pf_open          = _mmp_sort_aud_open;
    t_intf.pf_close         = _mmp_sort_aud_close;
    t_intf.pf_is_supported  = _mmp_sort_aud_is_supported;
    t_intf.pf_update_item   = _mmp_sort_aud_update_item;
    t_intf.pf_do_cmd        = _mmp_sort_aud_do_cmd;
    t_intf.pf_query_info    = _mmp_sort_aud_query_info;

    i4_ret = mmp_mc_reg_sorter(&t_intf);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_mc_reg_sorter() failed. i4_ret = %d.\r\n", i4_ret));
    }
    return i4_ret;
}

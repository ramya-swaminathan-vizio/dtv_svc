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
 * $RCSfile: ocl.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Wencheng zhang $
 * $MD5HEX: 7793009dbc122937a0001b34eec5772f $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include <stdlib.h>
#include "u_device_type.h"
#include "u_gl_nc.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_handle.h"

#include "nav/navigator.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_variant_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_tv.h"

#include "res/nav/nav_dbg.h"
#include "c_svl.h"
#include "app_util/mtktvapi/a_mtktvapi_channellist.h"

#include "ocl.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_CH_ID_LARGER(p1, p2)                                                 \
    (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) >  SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 || (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 &&  SB_ATSC_GET_MINOR_CHANNEL_NUM(p1) >  SB_ATSC_GET_MINOR_CHANNEL_NUM(p2)))

#define IS_CH_ID_SMALLER(p1, p2)                                                \
    (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) <  SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 || (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 &&  SB_ATSC_GET_MINOR_CHANNEL_NUM(p1) <  SB_ATSC_GET_MINOR_CHANNEL_NUM(p2)))

#define IS_CH_ID_EQUAL(p1, p2)                                                  \
    (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 &&  SB_ATSC_GET_MINOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MINOR_CHANNEL_NUM(p2))


/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UINT16    g_ui2_cable_num       = 0;/* cable records number */
static UINT16    g_ui2_antenna_num     = 0;/* antenna records number */
static HANDLE_T  g_h_cable_svl         = NULL_HANDLE;/* cable svl handle */
static HANDLE_T  g_h_antenna_svl       = NULL_HANDLE;/* antenna svl handle */
static HANDLE_T  g_h_cable_tsl         = NULL_HANDLE;/* cable tsl handle */
static HANDLE_T  g_h_antenna_tsl       = NULL_HANDLE;/* antenna tsl handle */
static OCL_SVL_REC_T *g_p_ocl_list     = NULL;/* one(cable+antenna) channel list */
static UINT32 g_ui4_antenna_svl_ver_id = 0;/* antenna svl version ID */
static UINT32 g_ui4_cable_svl_ver_id   = 0;/* cable svl version ID */
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static BOOL _ocl_is_svl_updated(VOID);

/*-----------------------------------------------------------------------------
 * Name
 *      _ocl_get_channel_list
 * Description
 *      The API is used to get the all channel list.
 * Input arguments
 *      h_svl  svl handle
 *      ui2_svl_id svl id
 *      i4_count   channel list count
 * Output arguments
 *      p_list the store channel list
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
static INT32 _ocl_get_channel_list(HANDLE_T h_svl, HANDLE_T h_tsl, UINT16 ui2_svl_id, OCL_SVL_REC_T *p_list, INT32 i4_count)
{
    INT32  i4_ret              = OCLR_OK;
    UINT32 ui4_current_channel = 0;
    SVL_REC_T t_svl_rec_temp   = {0};
    TSL_REC_T t_tsl_rec_tmp    = {0};
    /*---get all svl_rec_id----*/

    i4_ret = c_svl_lock(h_svl);
    if (i4_ret != SVLR_OK)
    {
        DBG_LOG_PRINT(("[OCL]Error:c_svl_lock() line=[%d] \n", __LINE__));
        return i4_ret;
    }

    i4_ret = a_mtktvapi_channellist_get_svl_tsl_recs_by_mask(
                                h_svl,
                                h_tsl,
    							(SB_VNET_ACTIVE | SB_VNET_FAKE),
    							(SB_VNET_ACTIVE),
    							0,
    							0,
    							0,
    							CHLST_ITERATE_DIR_FROM_FIRST,
    							ui4_current_channel,
	   							1,
                                &t_svl_rec_temp,
                                &t_tsl_rec_tmp
                                );

    for (INT32 i4_i = 0; i4_i < i4_count; i4_i ++)
    {

        if(i4_ret < 0 )
        {
            DBG_LOG_PRINT(("[OCL]Error:a_mtktvapi_channellist_get_svl_tsl_recs_by_mask() i4_ret=[%d] \n", i4_ret));
            break;
        }

        DBG_INFO(("[OCL]a_mtktvapi_channellist_get_svl_tsl_recs_by_mask ui4_channel_id=[%d], ui2_svl_id=[%d] \n",
                                        t_svl_rec_temp.uheader.t_rec_hdr.ui4_channel_id,
                                        ui2_svl_id));

        (p_list + i4_i)->ui2_svl_rec_id = t_svl_rec_temp.ui2_svl_rec_id;
        (p_list + i4_i)->ui2_svl_id     = ui2_svl_id;
        (p_list + i4_i)->ui4_channel_id = t_svl_rec_temp.uheader.t_rec_hdr.ui4_channel_id;
        (p_list + i4_i)->e_brdcst_type  = t_svl_rec_temp.uheader.t_rec_hdr.e_brdcst_type;

        ui4_current_channel = t_svl_rec_temp.uheader.t_rec_hdr.ui4_channel_id;

        i4_ret = a_mtktvapi_channellist_get_svl_tsl_recs_by_mask(
                                h_svl,
                                h_tsl,
    							(SB_VNET_ACTIVE | SB_VNET_FAKE),
    							(SB_VNET_ACTIVE),
    							0,
    							0,
    							0,
    							CHLST_ITERATE_DIR_NEXT,
    							ui4_current_channel,
	   							1,
                                &t_svl_rec_temp,
                                &t_tsl_rec_tmp
                                );

    }


    #if 0
    i4_ret = c_svl_iterate_rec(h_svl, ui4_current_channel, (SB_VNET_ACTIVE | SB_VNET_VISIBLE), SVL_CHANNEL_SMALLEST, &t_svl_rec_temp, &ui4_ver_id);

    for (INT32 i4_i = 0; i4_i < i4_count; i4_i ++)
    {
        if(i4_ret == SVLR_END_OF_ITERATION )
        {
            break;
        }

        if(i4_ret != SVLR_OK )
        {
            break;
        }

        DBG_INFO(("[OCL]c_svl_iterate_rec ui4_channel_id=[%d], ui2_svl_id=[%d] \n",
                                        t_svl_rec_temp.uheader.t_rec_hdr.ui4_channel_id,
                                        ui2_svl_id));

        (p_list + i4_i)->ui2_svl_rec_id = t_svl_rec_temp.ui2_svl_rec_id;
        (p_list + i4_i)->ui2_svl_id     = ui2_svl_id;
        (p_list + i4_i)->ui4_channel_id = t_svl_rec_temp.uheader.t_rec_hdr.ui4_channel_id;
        (p_list + i4_i)->e_brdcst_type  = t_svl_rec_temp.uheader.t_rec_hdr.e_brdcst_type;

        ui4_current_channel = t_svl_rec_temp.uheader.t_rec_hdr.ui4_channel_id;
        i4_ret = c_svl_iterate_rec(h_svl, ui4_current_channel, (SB_VNET_ACTIVE | SB_VNET_VISIBLE), SVL_CHANNEL_PLUS, &t_svl_rec_temp, &ui4_ver_id);

    }
    #endif

    i4_ret = c_svl_unlock(h_svl);
    if (i4_ret != SVLR_OK)
    {
        DBG_LOG_PRINT(("[OCL]Error:c_svl_unlock() line=[%d] \n", __LINE__));
        return i4_ret;
    }

    return OCLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ocl_is_priority
 * Description
 *      The API is used to compare with priority of two channels.
 * Input arguments
 *      t_rec_a  the a channel
 *      t_rec_b  the b channel
 * Output arguments
 *      b_is_priority TRUE/FALSE
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
static INT32 _ocl_is_priority(OCL_SVL_REC_T *pt_rec_a, OCL_SVL_REC_T *pt_rec_b, BOOL *pb_is_priority)
{
    /*-----------------------------------------------------------------------------
     * Description
     *      The priority rule follow as:
     *
     *  rule 1:
     *      major number
     *  rule 2:
     *      minor number
     *  rule 3:
     *      analog > antenna digital > cable digital
     *
     *---------------------------------------------------------------------------*/
    DBG_INFO(("t_rec_a.ui4_channel_id=[%d], t_rec_b.ui4_channel_id=[%d] line:[%d] \n",
                    pt_rec_a->ui4_channel_id,
                    pt_rec_b->ui4_channel_id,
                    __LINE__));
    do
    {
        /* rule 1/2 */
        if (IS_CH_ID_SMALLER(pt_rec_a->ui4_channel_id, pt_rec_b->ui4_channel_id))
        {
            *pb_is_priority = TRUE;

            DBG_INFO(("t_rec_a.ui4_channel_id=[%d] IS_CH_ID_SMALLER t_rec_b.ui4_channel_id=[%d] line:[%d] \n",
                            pt_rec_a->ui4_channel_id,
                            pt_rec_b->ui4_channel_id,
                            __LINE__));

            break;
        }
        else if (IS_CH_ID_LARGER(pt_rec_a->ui4_channel_id, pt_rec_b->ui4_channel_id))
        {
            *pb_is_priority = FALSE;

            DBG_INFO(("t_rec_a.ui4_channel_id=[%d] IS_CH_ID_LARGER t_rec_b.ui4_channel_id=[%d] line:[%d] \n",
                            pt_rec_a->ui4_channel_id,
                            pt_rec_b->ui4_channel_id,
                            __LINE__));
            break;
        }
        /* rule 3.a */
        /* define in u_common.h */
        /* #define BRDCST_TYPE_ANALOG   ((BRDCST_TYPE_T) 1)  */
        /* #define BRDCST_TYPE_ATSC     ((BRDCST_TYPE_T) 3)  */
        if (pt_rec_a->e_brdcst_type < pt_rec_b->e_brdcst_type)
        {
            *pb_is_priority = TRUE;
            DBG_INFO(("t_rec_a.e_brdcst_type=[%d] < t_rec_b.e_brdcst_type=[%d] line:[%d] \n",
                        pt_rec_a->e_brdcst_type,
                        pt_rec_b->e_brdcst_type,
                        __LINE__));

            break;
        }
        else if (pt_rec_a->e_brdcst_type > pt_rec_b->e_brdcst_type)
        {
            *pb_is_priority = FALSE;
            DBG_INFO(("t_rec_a.e_brdcst_type=[%d] > t_rec_b.e_brdcst_type=[%d] line:[%d] \n",
                        pt_rec_a->e_brdcst_type,
                        pt_rec_b->e_brdcst_type,
                        __LINE__));
            break;
        }

        /* rule 3.b */
        /* define in ocl.h */
        /* #define ANTENNA_SVL_ID (1) */
        /* #define CABLE_SVL_ID   (2) */
        if (pt_rec_a->ui2_svl_id < pt_rec_b->ui2_svl_id)
        {
            *pb_is_priority = TRUE;
            DBG_INFO(("t_rec_a.ui2_svl_id=[%d] < t_rec_b.ui2_svl_id=[%d] line:[%d] \n",
                    pt_rec_a->ui2_svl_id,
                    pt_rec_b->ui2_svl_id,
                    __LINE__));

            break;
        }

        DBG_INFO(("Default pb_is_priority = FALSE, line:[%d] \n", __LINE__));

        *pb_is_priority = FALSE;

    }while(0);

    return OCLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ocl_get_one_channel_list
 * Description
 *      The API is used to recreate one channel list by list a and list b.
 * Input arguments
 *      pt_list_a   the a channel list
 *      pt_list_b   the b channel list
 *      i4_count_a  the a channel list count
 *      i4_count_a  the b channel list count
 * Output arguments
 *      pt_list_ocl
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
static INT32 _ocl_get_one_channel_list(OCL_SVL_REC_T *pt_list_a,
                                       OCL_SVL_REC_T *pt_list_b,
                                       OCL_SVL_REC_T *pt_list_ocl,
                                       INT32 i4_count_a,
                                       INT32 i4_count_b)
{
    INT32 i4_idx            = 0;
    INT32 i4_index_a        = 0;
    INT32 i4_index_b        = 0;
    BOOL  b_is_priority     = FALSE;

    for (i4_idx = 0; i4_idx < (i4_count_a + i4_count_b); i4_idx ++)
    {
        if (i4_index_a == i4_count_a || i4_index_b == i4_count_b)
        {
            break;
        }

        _ocl_is_priority(pt_list_a+i4_index_a, pt_list_b+i4_index_b, &b_is_priority);
        if (b_is_priority)
        {
            c_memcpy((pt_list_ocl + i4_idx), (pt_list_a + i4_index_a), sizeof(OCL_SVL_REC_T));
            i4_index_a ++;
        }
        else
        {
            c_memcpy((pt_list_ocl + i4_idx), (pt_list_b + i4_index_b), sizeof(OCL_SVL_REC_T));
            i4_index_b ++;
        }
    }

    /* copy the rest of b part */
    if (i4_index_a == i4_count_a && (i4_count_b - i4_index_b) > 0)
    {
        c_memcpy((pt_list_ocl + i4_idx), (pt_list_b + i4_index_b), (i4_count_b - i4_index_b) * sizeof(OCL_SVL_REC_T));
    }
    else if(i4_index_b == i4_count_b && (i4_count_a - i4_index_a) > 0)
    {
        c_memcpy((pt_list_ocl + i4_idx), (pt_list_a + i4_index_a), (i4_count_a - i4_index_a) * sizeof(OCL_SVL_REC_T));
    }

    DBG_INFO(("i4_count_a=[%d], i4_count_b=[%d], i4_index_a=[%d], i4_index_b=[%d], line:[%d] \n",
                                                i4_count_a, i4_count_b, i4_index_a, i4_index_b, __LINE__));
    return OCLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ocl_dump_one_channel_list
 * Description
 *      The API is used to dump one channel list.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
static INT32 _ocl_dump_one_channel_list(VOID)
{
    DBG_INFO(("The one channel list number are:[%d] \n", (g_ui2_antenna_num + g_ui2_cable_num)));

    if (NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]Error:FUNCTION:[%s] line:[%d],The g_p_ocl_list is NULL. \n", __FUNCTION__, __LINE__));
        return OCLR_NOT_INIT;
    }

    for (INT32 i4_i = 0; i4_i < (g_ui2_antenna_num + g_ui2_cable_num); i4_i ++)
    {
        DBG_INFO(("i4_i:[%d], ui2_svl_rec_id:[%d], ui2_svl_id:[%d], ui4_channel_id:[%d], e_brdcst_type:[%d] \n",
                        i4_i,
                        g_p_ocl_list[i4_i].ui2_svl_rec_id,
                        g_p_ocl_list[i4_i].ui2_svl_id,
                        g_p_ocl_list[i4_i].ui4_channel_id,
                        g_p_ocl_list[i4_i].e_brdcst_type));
    }

    return OCLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_get_ocl_svl_by_index
 * Description
 *      The API is used to get the svl record by index.
 * Input arguments
 *      i4_idx The channel index of get
 * Output arguments
 *      pt_svl_rec The matched channel svl record.
 *      pt_ocl_svl_rec The matched one channel list channel svl record.
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_get_ocl_svl_by_index(INT32 i4_idx, SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec)
{
    INT32 i4_ret    = NAVR_OK;

    if (i4_idx < 0 ||
        pt_svl_rec == NULL ||
        pt_ocl_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_ocl_svl_by_index(), the index:[%d] has exceed, ocl total num:[%d] \n",
                        i4_idx, (g_ui2_antenna_num + g_ui2_cable_num)));

        return OCLR_INV_ARG;
    }

    if (NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]FUNCTION:[%s] line:[%d],The g_p_ocl_list is NULL, reinstall it; \n", __FUNCTION__, __LINE__));
        ocl_reinstall();
    }

    if (TRUE == _ocl_is_svl_updated())
    {
        DBG_LOG_PRINT(("[OCL]:_ocl_is_svl_updated == TRUE, line:[%d]. \n", __LINE__));

        ocl_reinstall();
    }

    if (i4_idx > ((g_ui2_antenna_num + g_ui2_cable_num) - 1))
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_ocl_svl_by_index(),index is exceed to total num, the index:[%d] has exceed, ocl total num:[%d] \n",
                        i4_idx, (g_ui2_antenna_num + g_ui2_cable_num)));

        return OCLR_INV_ARG;
    }

    if(g_p_ocl_list != NULL)
        c_memcpy(pt_ocl_svl_rec, g_p_ocl_list + i4_idx, sizeof(OCL_SVL_REC_T));

    #if 0
    HANDLE_T  h_svl = NULL_HANDLE;
    if (g_p_ocl_list[i4_idx].ui2_svl_id == ANTENNA_SVL_ID)
    {
        h_svl = g_h_antenna_svl;
    }
    else
    {
        h_svl = g_h_cable_svl;
    }

    if (NULL_HANDLE == h_svl)
    {
        DBG_LOG_PRINT(("[OCL]Error:FUNCTION:[%s] line:[%d],The SVL handle is NULL. \n", __FUNCTION__, __LINE__));
        return OCLR_FAIL;
    }

    b_found = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                        h_svl,
                        a_tv_get_surfable_svl_rec_check_nw_mask(),
                        a_tv_get_surfable_svl_rec_check_nw_bits(),
                        TV_ITERATE_DIR_CRNT,
                        &ui4_ch_id,
                        pt_svl_rec
                        );
    #endif

    i4_ret = a_mtktvapi_channellist_get_svl_rec_by_channel_id(
                                                    g_p_ocl_list[i4_idx].ui2_svl_id,
                                                    g_p_ocl_list[i4_idx].ui4_channel_id,
                                                    pt_svl_rec);

    DBG_INFO(("[OCL]FUNCTION:[a_mtktvapi_channellist_get_svl_rec_by_channel_id].In parm:svl_id=[%d],ch_id=[%d] line:[%d]. \n",
                                g_p_ocl_list[i4_idx].ui2_svl_id, g_p_ocl_list[i4_idx].ui4_channel_id, __LINE__));
    DBG_INFO(("[OCL]FUNCTION:[a_mtktvapi_channellist_get_svl_rec_by_channel_id]. return records: ui2_svl_rec_id=[%d],ch_id=[%d] line:[%d]. \n",
                                pt_svl_rec->ui2_svl_rec_id, pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id, __LINE__));
    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[OCL]Error:FUNCTION:[a_mtktvapi_channellist_get_svl_rec_by_channel_id],Cannot found the match channel. svl_id=[%d],ch_id=[%d] line:[%d]. \n",
                                g_p_ocl_list[i4_idx].ui2_svl_id, g_p_ocl_list[i4_idx].ui4_channel_id, __LINE__));

        return OCLR_NOT_FOUND;
    }

    return OCLR_OK;

}

/*-----------------------------------------------------------------------------
 * Name
 *      _ocl_is_svl_updated
 * Description
 *      The API is used to compare the svl version id with old.
 * Input arguments
 *      None
 * Output arguments
 *      None.
 * Returns
 *      TRUE/FALSE     is the svl updated or not.
 *
 *---------------------------------------------------------------------------*/
static BOOL _ocl_is_svl_updated(VOID)
{
    INT32   i4_ret                      = NAVR_OK;
    UINT32  ui4_antenna_latest_ver_id   = 0;
    UINT32  ui4_cable_latest_ver_id     = 0;

    do
    {
        if (g_h_antenna_svl)
        {
            i4_ret = c_svl_get_ver_id(g_h_antenna_svl, &ui4_antenna_latest_ver_id);
            if (i4_ret != NAVR_OK)
            {
                DBG_LOG_PRINT(("[OCL]Error:c_svl_get_ver_id(g_h_antenna_svl) ret=[%d] \n", i4_ret));
                g_ui4_antenna_svl_ver_id = 0;

                break;
            }
        }

        if (g_h_cable_svl)
        {
            i4_ret = c_svl_get_ver_id(g_h_cable_svl, &ui4_cable_latest_ver_id);
            if (i4_ret != NAVR_OK)
            {
                DBG_LOG_PRINT(("[OCL]Error:c_svl_get_ver_id(g_h_cable_svl) ret=[%d] \n", i4_ret));
                g_ui4_cable_svl_ver_id = 0;

                break;
            }
        }

        DBG_INFO(("[OCL]The SVL version ID ui4_antenna_latest_ver_id=[%d],g_ui4_antenna_svl_ver_id=[%d],ui4_cable_latest_ver_id=[%d],g_ui4_cable_svl_ver_id=[%d].\n",
                        ui4_antenna_latest_ver_id, g_ui4_antenna_svl_ver_id, ui4_cable_latest_ver_id, g_ui4_cable_svl_ver_id));

        if (ui4_antenna_latest_ver_id == g_ui4_antenna_svl_ver_id
            && ui4_cable_latest_ver_id == g_ui4_cable_svl_ver_id)
        {
            DBG_INFO(("[OCL]The SVL version ID is the same as old, Not updated.\n"));
            return FALSE;
        }
        else
        {
            g_ui4_antenna_svl_ver_id = ui4_antenna_latest_ver_id;
            g_ui4_cable_svl_ver_id   = ui4_cable_latest_ver_id;
        }

    }while(0);

    DBG_INFO(("[OCL]The SVL version ID is not the same as old, Need updated.\n"));

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_get_svl_by_ch_id
 * Description
 *      The API is used to get the svl record by channel id.
 * Input arguments
 *      ui4_ch_id  The channel id
 *      ui2_svl_id The svl id
 * Output arguments
 *      pt_svl_rec The matched channel svl record.
 *      pt_ocl_svl_rec The matched one channel list channel svl record.

 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_get_svl_by_ch_id(UINT16 ui2_svl_id, UINT32 ui4_ch_id, TV_ITERATE_DIR_T t_dir, SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec)
{
    if (pt_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_svl_by_ch_id(),line:[%d] \n",
                        __LINE__));

        return OCLR_INV_ARG;
    }

    if (NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]:FUNCTION:[%s] line:[%d],The g_p_ocl_list is NULL, reinstall it. \n", __FUNCTION__, __LINE__));
        ocl_reinstall();
    }

    if (TRUE == _ocl_is_svl_updated())
    {
        DBG_LOG_PRINT(("[OCL]:_ocl_is_svl_updated == TRUE, line:[%d]. \n", __LINE__));

        ocl_reinstall();
    }

    DBG_INFO(("[OCL]:ocl_get_svl_by_ch_id,ui4_ch_id=[%d],ui2_svl_id:[%d], line:[%d]. \n", ui4_ch_id, ui2_svl_id, __LINE__));

    BOOL b_found    = FALSE;
    INT32 i4_ret    = OCLR_OK;
    INT32 i4_i      = 0;

    for (i4_i = 0; i4_i < (g_ui2_antenna_num + g_ui2_cable_num); i4_i ++)
    {
        /* matched */
        if ((0 == ui4_ch_id) || (g_p_ocl_list!= NULL && (g_p_ocl_list[i4_i].ui4_channel_id == ui4_ch_id) && (g_p_ocl_list[i4_i].ui2_svl_id == ui2_svl_id)))
        {
            DBG_INFO(("[OCL]:Matched,ui4_ch_id=[%d],ui2_svl_id:[%d], line:[%d],The i4_i=[%d]. \n", ui4_ch_id, ui2_svl_id, __LINE__, i4_i));

            b_found = TRUE;
            break;
        }
    }

    if (TRUE != b_found)
    {
        DBG_LOG_PRINT(("[OCL]FUNCTION:[ocl_get_svl_by_ch_id],Cannot found the match channel,get the nearest channel,line:[%d],The ui4_ch_id is[%d]. \n", __LINE__, ui4_ch_id));
        /* Cannot found the match channel, get the nearest channel. */
        for (i4_i = 0; i4_i < (g_ui2_antenna_num + g_ui2_cable_num); i4_i ++)
        {
            /* matched nearest */
            if (ui4_ch_id <= 0 ||
                ((g_p_ocl_list[i4_i].ui4_channel_id >= ui4_ch_id))
               )
            {
                DBG_INFO(("[OCL]:Matched nearest,ui4_ch_id=[%d],ui2_svl_id:[%d], line:[%d],The i4_i=[%d]. \n", ui4_ch_id, ui2_svl_id, __LINE__, i4_i));

                break;
            }
        }
        //return OCLR_NOT_FOUND;
    }

    if (t_dir == TV_ITERATE_DIR_PREV)
    {
        /* previous channel index */
        i4_i --;

        /* the first channel prev channel is the last one */
        if(i4_i < 0)
        {
            for (i4_i = 0; i4_i < (g_ui2_antenna_num + g_ui2_cable_num); i4_i ++)
            {
                ocl_get_ocl_svl_by_index(i4_i, pt_svl_rec, pt_ocl_svl_rec);
                if ((pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE))
                {
                    DBG_INFO(("[OCL]:FUNCTION: ocl_get_svl_by_ch_id some channel is  avaiable \n"));
                    break;
                }
                if(i4_i == ((g_ui2_antenna_num + g_ui2_cable_num) - 1))
                {
                    DBG_INFO(("[OCL]:FUNCTION: ocl_get_svl_by_ch_id all channel is skipped \n"));
                    return OCLR_NOT_FOUND;
                }
            }
            i4_i = (g_ui2_antenna_num + g_ui2_cable_num) - 1;
        }
    }
    else if (t_dir == TV_ITERATE_DIR_NEXT)
    {
        /* Next channel index */
        i4_i ++;

        /* the next channel of last channel is the first one */
        if(i4_i > (g_ui2_antenna_num + g_ui2_cable_num - 1))
        {

            for (i4_i = 0; i4_i < (g_ui2_antenna_num + g_ui2_cable_num); i4_i ++)
            {
                ocl_get_ocl_svl_by_index(i4_i, pt_svl_rec, pt_ocl_svl_rec);
                if ((pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE))
                {
                    DBG_INFO(("[OCL]:FUNCTION: ocl_get_svl_by_ch_id some channel is  avaiable \n"));
                    break;
                }
                if(i4_i == ((g_ui2_antenna_num + g_ui2_cable_num) - 1))
                {
                    DBG_INFO(("[OCL]:FUNCTION: ocl_get_svl_by_ch_id all channel is skipped \n"));
                    return OCLR_NOT_FOUND;
                }

            }

            i4_i = 0;
        }
    }
    DBG_INFO(("[OCL]:FUNCTION:[ocl_get_svl_by_ch_id], line:[%d],The i4_i=[%d]. \n", __LINE__, i4_i));

    i4_ret = ocl_get_ocl_svl_by_index(i4_i, pt_svl_rec, pt_ocl_svl_rec);

    return i4_ret;

}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_get_first_ch_by_svl_id
 * Description
 *      The API is used to get the first svl record by svl id.
 * Input arguments
 *      ui2_svl_id The svl id
 * Output arguments
 *      pt_svl_rec The matched channel svl record.

 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_get_first_ch_by_svl_id(UINT16 ui2_svl_id, SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec)
{
    if (pt_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_first_ch_by_svl_id(),line:[%d] \n",
                        __LINE__));

        return OCLR_INV_ARG;
    }

    if (NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]:FUNCTION:[%s] line:[%d],The g_p_ocl_list is NULL, reinstall it. \n", __FUNCTION__, __LINE__));
        ocl_reinstall();
    }

    if (TRUE == _ocl_is_svl_updated())
    {
        DBG_LOG_PRINT(("[OCL]:_ocl_is_svl_updated == TRUE, line:[%d]. \n", __LINE__));

        ocl_reinstall();
    }

    DBG_INFO(("[OCL]:ocl_get_first_ch_by_svl_id,ui2_svl_id:[%d], line:[%d]. \n", ui2_svl_id, __LINE__));

    BOOL b_found    = FALSE;
    INT32 i4_ret    = OCLR_OK;
    INT32 i4_i      = 0;

    for (i4_i = 0; i4_i < (g_ui2_antenna_num + g_ui2_cable_num); i4_i ++)
    {
        /* matched */
        if (g_p_ocl_list != NULL && g_p_ocl_list[i4_i].ui2_svl_id == ui2_svl_id)
        {
            DBG_INFO(("[OCL]:Matched,ui2_svl_id:[%d], line:[%d],The i4_i=[%d]. \n", ui2_svl_id, __LINE__, i4_i));

            b_found = TRUE;
            break;
        }
    }

    if (TRUE != b_found)
    {
        DBG_LOG_PRINT(("[OCL]FUNCTION:[ocl_get_first_ch_by_svl_id],Cannot found the match channel,get the nearest channel,line:[%d]. \n", __LINE__));
        return OCLR_NOT_FOUND;
    }

    DBG_INFO(("[OCL]:FUNCTION:[ocl_get_svl_by_ch_id], line:[%d],The i4_i=[%d]. \n", __LINE__, i4_i));

    i4_ret = ocl_get_ocl_svl_by_index(i4_i, pt_svl_rec, pt_ocl_svl_rec);

    return i4_ret;

}
/*-----------------------------------------------------------------------------
 * Name
 *      _ocl_get_prev_svl_by_ch_id
 * Description
 *      The API is used to get the previous svl record by channel id.
 * Input arguments
 *      ui2_svl_id The SVL id
 *      ui4_ch_id  The channel id
 * Output arguments
 *      pt_svl_rec The matched channel svl record.
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_get_prev_svl_by_ch_id(UINT16 ui2_svl_id, UINT32 ui4_ch_id, SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec)
{
    if (pt_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_prev_svl_by_ch_id(),line:[%d] \n",
                        __LINE__));

        return OCLR_INV_ARG;
    }

    if (TRUE == _ocl_is_svl_updated())
    {
        DBG_LOG_PRINT(("[OCL]:_ocl_is_svl_updated == TRUE, line:[%d]. \n", __LINE__));

        ocl_reinstall();
    }

    DBG_INFO(("[OCL]:func=[%s],ui4_ch_id=[%d],ui2_svl_id:[%d], line:[%d]. \n",__FUNCTION__, ui4_ch_id, ui2_svl_id, __LINE__));

    INT32 i4_ret    = OCLR_OK;

    i4_ret = ocl_get_svl_by_ch_id(ui2_svl_id, ui4_ch_id, TV_ITERATE_DIR_PREV, pt_svl_rec, pt_ocl_svl_rec);

    return i4_ret;

}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_get_next_svl_by_ch_id
 * Description
 *      The API is used to get the previous svl record by channel id.
 * Input arguments
 *      ui2_svl_id The svl id
 *      ui4_ch_id  The  channel id
 * Output arguments
 *      pt_svl_rec The matched channel svl record.
 * Returns
 *      OCLR_OK      the routine is successfully
 *      Other        the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_get_next_svl_by_ch_id(UINT16 ui2_svl_id, UINT32 ui4_ch_id, SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec)
{
    if (pt_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_next_svl_by_ch_id(),line:[%d] \n",
                        __LINE__));

        return OCLR_INV_ARG;
    }

    if (TRUE == _ocl_is_svl_updated())
    {
        DBG_LOG_PRINT(("[OCL]:_ocl_is_svl_updated == TRUE, line:[%d]. \n", __LINE__));

        ocl_reinstall();
    }

    DBG_INFO(("[OCL]:func=[%s],ui4_ch_id=[%d],ui2_svl_id:[%d], line:[%d]. \n",__FUNCTION__, ui4_ch_id, ui2_svl_id, __LINE__));

    INT32 i4_ret    = OCLR_OK;

    i4_ret = ocl_get_svl_by_ch_id(ui2_svl_id, ui4_ch_id, TV_ITERATE_DIR_NEXT, pt_svl_rec, pt_ocl_svl_rec);

    return i4_ret;

}

INT32 ocl_get_svl_by_ch_num(SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec, UINT32 ui4_major_ch_num, UINT32 ui4_minor_ch_num)
{
    INT32   i4_ret;
    UINT32  ui4_idx;
    UINT32  ui4_total_rec;
    SVL_REC_T  t_svl_rec = {0};
    OCL_SVL_REC_T  *pt_ocl_svl_rec_tmp = NULL;

    if (pt_svl_rec == NULL || pt_ocl_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_svl_by_ch_num(),line:[%d] \n", __LINE__));
        return OCLR_INV_ARG;
    }

    if (TRUE == _ocl_is_svl_updated() || NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]:because of some reason ocl_reinstall, line:[%d]. \n", __LINE__));
        ocl_reinstall();
    }

    if (g_p_ocl_list == NULL)
    {
        DBG_LOG_PRINT(("[OCL]:ocl_reinstall fail, line:[%d]. \n", __LINE__));
        return OCLR_FAIL;
    }

    ui4_total_rec = g_ui2_antenna_num + g_ui2_cable_num;
    for (ui4_idx = 0; ui4_idx < ui4_total_rec; ui4_idx ++)
    {
        pt_ocl_svl_rec_tmp = g_p_ocl_list + ui4_idx;

        if (SB_ATSC_GET_MAJOR_CHANNEL_NUM(pt_ocl_svl_rec_tmp->ui4_channel_id) == ui4_major_ch_num &&
            SB_ATSC_GET_MINOR_CHANNEL_NUM(pt_ocl_svl_rec_tmp->ui4_channel_id) == ui4_minor_ch_num)
        {
            i4_ret = a_mtktvapi_channellist_get_svl_rec_by_channel_id(
                                                    pt_ocl_svl_rec_tmp->ui2_svl_id,
                                                    pt_ocl_svl_rec_tmp->ui4_channel_id,
                                                    &t_svl_rec);
            if (NAVR_OK == i4_ret)
            {
                c_memcpy(pt_svl_rec, &t_svl_rec, sizeof(SVL_REC_T));
                c_memcpy(pt_ocl_svl_rec, pt_ocl_svl_rec_tmp, sizeof(OCL_SVL_REC_T));

                return OCLR_OK;
            }
        }
    }

    return OCLR_FAIL;
}

/*
 *compare to ocl_get_svl_by_ch_num(), this func not only compare major and minor in
 *one step, so if input 'x', and there's no 'x' channel, then go to 'x-1' if there's
 *channel 'x-1'
 *NOTE: because one_channel_list has already been increasing channel merged, so
 *      theorital, get next channel to compare will be work.
 */
INT32 ocl_get_svl_by_ch_num_ex(SVL_REC_T *pt_svl_rec, OCL_SVL_REC_T *pt_ocl_svl_rec, UINT32 ui4_major_ch_num,
                                    UINT32 ui4_minor_ch_num)
{
    INT32   i4_ret;
    UINT32  ui4_idx;
    UINT32  ui4_total_rec;
    SVL_REC_T  t_svl_rec = {0};
    OCL_SVL_REC_T  *pt_ocl_svl_rec_tmp = NULL;

    if (pt_svl_rec == NULL || pt_ocl_svl_rec == NULL)
    {
        DBG_LOG_PRINT(("[OCL]Error:ocl_get_svl_by_ch_num(),line:[%d] \n", __LINE__));
        return OCLR_INV_ARG;
    }

    if (TRUE == _ocl_is_svl_updated() || NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]:because of some reason ocl_reinstall, line:[%d]. \n", __LINE__));
        ocl_reinstall();
    }

    if (g_p_ocl_list == NULL)
    {
        DBG_LOG_PRINT(("[OCL]:ocl_reinstall fail, line:[%d]. \n", __LINE__));
        return OCLR_FAIL;
    }

    ui4_total_rec = g_ui2_antenna_num + g_ui2_cable_num;

    for (ui4_idx = 0; ui4_idx < ui4_total_rec; ui4_idx ++)
    {
        pt_ocl_svl_rec_tmp = g_p_ocl_list + ui4_idx;

        if (SB_ATSC_GET_MAJOR_CHANNEL_NUM(pt_ocl_svl_rec_tmp->ui4_channel_id) == ui4_major_ch_num)
        {
            if(ui4_minor_ch_num == 0)
            {
                i4_ret = a_mtktvapi_channellist_get_svl_rec_by_channel_id(
                                                        pt_ocl_svl_rec_tmp->ui2_svl_id,
                                                        pt_ocl_svl_rec_tmp->ui4_channel_id,
                                                        &t_svl_rec);
                if (NAVR_OK == i4_ret)
                {
                    c_memcpy(pt_svl_rec, &t_svl_rec, sizeof(SVL_REC_T));
                    c_memcpy(pt_ocl_svl_rec, pt_ocl_svl_rec_tmp, sizeof(OCL_SVL_REC_T));

                    return OCLR_OK;
                }
            }
            else
            {
                if(SB_ATSC_GET_MINOR_CHANNEL_NUM(pt_ocl_svl_rec_tmp->ui4_channel_id) >= ui4_minor_ch_num)
                {
                    i4_ret = a_mtktvapi_channellist_get_svl_rec_by_channel_id(
                                            pt_ocl_svl_rec_tmp->ui2_svl_id,
                                            pt_ocl_svl_rec_tmp->ui4_channel_id,
                                            &t_svl_rec);
                    if (NAVR_OK == i4_ret)
                    {
                        c_memcpy(pt_svl_rec, &t_svl_rec, sizeof(SVL_REC_T));
                        c_memcpy(pt_ocl_svl_rec, pt_ocl_svl_rec_tmp, sizeof(OCL_SVL_REC_T));

                        return OCLR_OK;
                    }
                }
            }
        } /*major if*/
    }/* for */

    return OCLR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_get_ocl_num
 * Description
 *      The API is used to get the one channel list svl records number.
 * Input arguments
 *      None
 * Output arguments
 *      None.
 * Returns
 *      num     The one channel list svl records number
 *
 *---------------------------------------------------------------------------*/
UINT16 ocl_get_ocl_num(VOID)
{
    if (NULL == g_p_ocl_list)
    {
        DBG_LOG_PRINT(("[OCL]:FUNCTION:[%s] line:[%d],The g_p_ocl_list is NULL, reinstall it. \n", __FUNCTION__, __LINE__));
        ocl_reinstall();
    }

    if (TRUE == _ocl_is_svl_updated())
    {
        DBG_LOG_PRINT(("[OCL]:_ocl_is_svl_updated == TRUE, line:[%d]. \n", __LINE__));

        ocl_reinstall();
    }

    return (g_ui2_antenna_num + g_ui2_cable_num);
}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_reinstall
 * Description
 *      The API is used to ocl_reinstall one channel list module.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_reinstall(VOID)
{
    INT32 i4_ret            = OCLR_OK;
    OCL_SVL_REC_T *pt_cable_list   = NULL;
    OCL_SVL_REC_T *pt_antenna_list = NULL;
    UINT16         ui2_cable_num = 0;
    UINT16         ui2_antenna_num = 0;

    do
    {
        if (NULL_HANDLE == g_h_cable_svl ||
            NULL_HANDLE == g_h_antenna_svl ||
            NULL_HANDLE == g_h_cable_tsl ||
            NULL_HANDLE == g_h_antenna_tsl)
        {
            DBG_LOG_PRINT(("[OCL]error ocl not init. line=[%d] \n", __LINE__));
            i4_ret = OCLR_NOT_INIT;
            break;
        }

        /* get the cable records count by cable svl handle */
        ui2_cable_num = a_mtktvapi_channellist_get_number_by_mask(
                                g_h_cable_svl,
                                (SB_VNET_ACTIVE | SB_VNET_FAKE),
                                (SB_VNET_ACTIVE),
                                0,
    							0,
    							0);

        DBG_INFO(("[OCL]c_svl_get_num_rec_by_brdcst_type(g_h_cable_svl) g_ui2_cable_num=[%d] \n", ui2_cable_num));

        #if 0
        /* get the antenna records count by antenna svl handle */
        i4_ret = c_svl_get_num_rec_by_brdcst_type(
                          g_h_antenna_svl,
                          BRDCST_TYPE_UNKNOWN,
                          (SB_VNET_ACTIVE | SB_VNET_VISIBLE),
                          &g_ui2_antenna_num,
                          &ui4_ver_id);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:a_tv_mcl_get_svl_rec_num_by_nw_masks(g_h_antenna_svl) ret=[%d] \n", i4_ret));
            g_ui2_antenna_num = 0;

            break;
        }
        #endif
        /* get the antenna records count by cable svl handle */
        ui2_antenna_num = a_mtktvapi_channellist_get_number_by_mask(
                                g_h_antenna_svl,
                                (SB_VNET_ACTIVE | SB_VNET_FAKE),
                                (SB_VNET_ACTIVE),
                                0,
    							0,
    							0);
        DBG_INFO(("[OCL]c_svl_get_num_rec_by_brdcst_type(g_h_antenna_svl) g_ui2_antenna_num=[%d] \n", ui2_antenna_num));

        if (ui2_cable_num > 0)
        {
            /* Create the cable channel list */
            pt_cable_list = (OCL_SVL_REC_T *)c_mem_alloc(ui2_cable_num * sizeof(OCL_SVL_REC_T));
            if (NULL == pt_cable_list)
            {
                DBG_LOG_PRINT(("[OCL]Error:c_mem_alloc(g_ui2_cable_num) \n"));
                i4_ret = OCLR_MEM_ALLOC_FAIL;

                break;
            }

            DBG_INFO(("[OCL]pt_cable_list=[%p] \n", pt_cable_list));

            c_memset(pt_cable_list, 0x0, ui2_cable_num * sizeof(OCL_SVL_REC_T));

            i4_ret = _ocl_get_channel_list(g_h_cable_svl, g_h_cable_tsl, CABLE_SVL_ID, pt_cable_list, ui2_cable_num);
            if (i4_ret != OCLR_OK)
            {
                DBG_LOG_PRINT(("[OCL]Error:_ocl_get_channel_list(g_h_cable_svl) ret=[%d] \n", i4_ret));

                break;
            }
        }

        DBG_INFO(("[OCL]_ocl_get_channel_list(g_h_cable_svl) i4_ret=[%d] \n", i4_ret));

        if (ui2_antenna_num > 0)
        {
            /* Create the antenna channel list */
            pt_antenna_list = (OCL_SVL_REC_T *)c_mem_alloc(ui2_antenna_num * sizeof(OCL_SVL_REC_T));
            if (NULL == pt_antenna_list)
            {
                DBG_LOG_PRINT(("[OCL]Error:c_mem_alloc(g_ui2_antenna_num) \n"));
                i4_ret = OCLR_MEM_ALLOC_FAIL;

                break;
            }

            DBG_INFO(("[OCL]pt_antenna_list=[%p] \n", pt_antenna_list));

            c_memset(pt_antenna_list, 0x0, ui2_antenna_num * sizeof(OCL_SVL_REC_T));

            i4_ret = _ocl_get_channel_list(g_h_antenna_svl, g_h_antenna_tsl, ANTENNA_SVL_ID, pt_antenna_list, ui2_antenna_num);
            if (i4_ret != OCLR_OK)
            {
                DBG_LOG_PRINT(("[OCL]Error:_ocl_get_channel_list(g_h_antenna_svl) ret=[%d] \n", i4_ret));

                break;
            }
        }

        DBG_INFO(("[OCL]_ocl_get_channel_list(g_h_antenna_svl) i4_ret=[%d] \n", i4_ret));


        /* Create the one channel list */
        if ((ui2_antenna_num + ui2_cable_num) > 0)
        {
            OCL_SVL_REC_T *pt_ocl_list_tmp = NULL;

            pt_ocl_list_tmp = (OCL_SVL_REC_T *)c_mem_alloc((ui2_antenna_num + ui2_cable_num) * sizeof(OCL_SVL_REC_T));
            if (NULL == pt_ocl_list_tmp)
            {
                DBG_LOG_PRINT(("[OCL]Error:c_mem_alloc(g_ui2_antenna_num + g_ui2_cable_num) \n"));
                i4_ret = OCLR_MEM_ALLOC_FAIL;

                break;
            }

            DBG_INFO(("[OCL]g_p_ocl_list=[%p] \n", pt_ocl_list_tmp));

            c_memset(pt_ocl_list_tmp, 0x0, (ui2_antenna_num + ui2_cable_num) * sizeof(OCL_SVL_REC_T));

            i4_ret = _ocl_get_one_channel_list(pt_antenna_list, pt_cable_list, pt_ocl_list_tmp, ui2_antenna_num, ui2_cable_num);
            if (i4_ret != OCLR_OK)
            {
                DBG_LOG_PRINT(("[OCL]Error:_ocl_get_one_channel_list() ret=[%d] \n", i4_ret));

                OCL_MEM_FREE(pt_ocl_list_tmp);

                pt_ocl_list_tmp = NULL;

                break;
            }

            OCL_MEM_FREE(g_p_ocl_list);
            g_p_ocl_list = pt_ocl_list_tmp;
            g_ui2_cable_num = ui2_cable_num;
            g_ui2_antenna_num = ui2_antenna_num;
        }

        DBG_INFO(("[OCL]_ocl_dump_one_channel_list()line=[%d] \n", __LINE__));

        i4_ret = _ocl_dump_one_channel_list();

    }while(0);

    OCL_MEM_FREE(pt_antenna_list);
    OCL_MEM_FREE(pt_cable_list);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ocl_init
 * Description
 *      The API is used to init one channel list module.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *---------------------------------------------------------------------------*/
INT32 ocl_init(VOID)
{
    INT32 i4_ret            = OCLR_OK;

    do
    {
        /* get the antenna svl handle */
        i4_ret = c_svl_open(ANTENNA_SVL_ID, NULL, NULL, &g_h_antenna_svl);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:nav_get_svl_handle_by_id(ANTENNA_SVL_ID) ret=[%d] \n", i4_ret));
            g_h_antenna_svl = NULL_HANDLE;

            break;
        }

        DBG_INFO(("[OCL]nav_get_svl_handle_by_id(ANTENNA_SVL_ID) g_h_antenna_svl=[%p] \n", g_h_antenna_svl));

        /* get the cable svl handle */
        i4_ret = c_svl_open(CABLE_SVL_ID, NULL, NULL, &g_h_cable_svl);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:nav_get_svl_handle_by_id(CABLE_SVL_ID) ret=[%d] \n", i4_ret));
            g_h_cable_svl = NULL_HANDLE;

            break;
        }

        DBG_INFO(("[OCL]nav_get_svl_handle_by_id(CABLE_SVL_ID) g_h_cable_svl=[%p] \n", g_h_cable_svl));

        /* get the antenna svl handle */
        i4_ret = c_tsl_open(ANTENNA_SVL_ID, NULL, NULL, &g_h_antenna_tsl);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:c_tsl_open(ANTENNA_SVL_ID) ret=[%d] \n", i4_ret));
            g_h_antenna_tsl = NULL_HANDLE;

            break;
        }
        DBG_INFO(("[OCL]a_mtktvapi_channellist_get_tsl_handle_by_svl_id(CABLE_SVL_ID) g_h_cable_tsll=[%p] \n", g_h_antenna_tsl));

        /* get the antenna svl handle */
        i4_ret = c_tsl_open(CABLE_SVL_ID, NULL, NULL, &g_h_cable_tsl);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:c_tsl_open(ANTENNA_SVL_ID) ret=[%d] \n", i4_ret));
            g_h_cable_tsl = NULL_HANDLE;

            break;
        }

        DBG_INFO(("[OCL]c_tsl_open(ANTENNA_SVL_ID) g_h_antenna_tsl=[%p] \n", g_h_cable_tsl));

        i4_ret = c_svl_get_ver_id(g_h_antenna_svl, &g_ui4_antenna_svl_ver_id);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:c_svl_get_ver_id(g_h_antenna_svl) ret=[%d] \n", i4_ret));
            g_ui4_antenna_svl_ver_id = 0;

            break;
        }

        i4_ret = c_svl_get_ver_id(g_h_cable_svl, &g_ui4_cable_svl_ver_id);
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:c_svl_get_ver_id(g_h_cable_svl) ret=[%d] \n", i4_ret));
            g_ui4_cable_svl_ver_id = 0;

            break;
        }

        i4_ret = ocl_reinstall();
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[OCL]Error:ocl_reinstall ret=[%d] \n", i4_ret));

            break;
        }

    }while(0);

    return i4_ret;
}


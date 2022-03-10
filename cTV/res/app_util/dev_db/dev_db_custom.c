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
 * $RCSfile: app_tv_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "res/app_util/dev_db/devdb_mlm.h"
#include "c_dbg.h"
#include "wizard/wzd_dbg.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define DB_LOCK_FILE_PATH     "/data/DB_LOCK"
#define DB_LOCK_FILE_NAME     "/data/DB_LOCK/DB_LOCK_INFO"
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static DEV_DB_UTIL_T     t_g_dev_db_util = {0};
static BOOL              b_is_wifi_banner_allow_show = FALSE;
static UINT16            aui2_g_predef_lbls[] =
                                            {
                                                MLM_DEVDB_KEY_DEV_TYPE_BLU_RAY,
                                                MLM_DEVDB_KEY_DEV_TYPE_CABLE_BOX,
                                                MLM_DEVDB_KEY_DEV_TYPE_COMPUTER,
                                                MLM_DEVDB_KEY_DEV_TYPE_DVD,
                                                MLM_DEVDB_KEY_DEV_TYPE_DVR,
                                                MLM_DEVDB_KEY_DEV_TYPE_GAME,
                                                MLM_DEVDB_KEY_DEV_TYPE_SATELLITE,
                                                MLM_DEVDB_KEY_DEV_TYPE_VCR,
                                                MLM_DEVDB_KEY_DEV_TYPE_AVR_AMPLIFER_EX,
                                                MLM_DEVDB_KEY_DEV_TYPE_SOUND_BAR,
                                                MLM_DEVDB_KEY_DEV_TYPE_AVR_AUDIO_RECEIVER,
                                                MLM_DEVDB_KEY_DEV_TYPE_AVR_AMP
                                            };
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _dev_db_set_lock_info( DEV_DB_LOCK_T  t_dev_db_lock );
static INT32 _dev_db_get_lock_info( DEV_DB_LOCK_T*  pt_dev_db_lock );
static INT32 _dev_db_get_lock_status( DEV_DB_LOCK_T  t_dev_db_lock, DEV_DB_LOCK_STATUS_T* pe_lock_status );
static INT32 _dev_db_update_lock_cnt( BOOL  b_is_cnt_add );
static INT32 _dev_db_set_lock( VOID );
static INT32 _dev_db_set_unlock( VOID );
static INT32 _dev_db_get_lock_timeout( BOOL* pb_is_timeout );
static INT32 _dev_db_get_unlock_timeout( BOOL* pb_is_timeout );
static INT32 _dev_db_bmc_query_thread_create( VOID );

static VOID  _dev_db_notify_client_data_change(VOID* pv_nfy_param);
static INT32 _dev_db_merge_sort(
    DEV_DB_BRMD_T* pt_array_brmd,
    DEV_DB_BM_T* t_dev_bm_info,
    UINT32* pui4_src_num1,
    UINT32 ui4_src_num2,
    DEV_DB_MERGE_TYPE_T  e_merge_type);
static INT32 _dev_db_reset_model_info(VOID);
static INT32 _dev_db_reset_brand_info(VOID);
static INT32 _dev_db_reset_type_info(VOID);
static INT32 _dev_db_reset_bm_info(DEV_DB_BM_T* t_dev_bm_info);
static INT32 _dev_db_reset_code_info(VOID);
static INT32 _dev_db_reset_codeset_list_info(VOID);
static INT32 _dev_db_clean_codeset_list_info(VOID);
static INT32 _dev_db_reset_thread_query_info(VOID);
static INT32 _dev_db_insert_bmc_query_task_info(DEV_DB_BMC_QUERY_T  t_bm_query_info);
static INT32 _dev_db_get_bmc_query_task(DEV_DB_BMC_QUERY_T* pt_bm_query_info,
                                               UINT32*  pui4_task_idx);
static INT32 _dev_db_update_local_brand(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                                 INT32 i4_type_idx,
                                                 CHAR* s_brd_prefix);
static INT32 _dev_db_update_local_model(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                         INT32 i4_type_idx,
                                         CHAR* s_brd_name,
                                         CHAR* s_mdl_prefix);

static INT32 _dev_db_thread_query_brd(DEV_DB_BMC_QUERY_T       t_bmc_query_info);
static INT32 _dev_db_thread_query_mdl(DEV_DB_BMC_QUERY_T       t_bmc_query_info);
static VOID* _dev_db_bmc_thread_query( VOID* parg );
static INT32 _dev_db_update_online_brand(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                                 INT32 i4_type_idx,
                                                 CHAR* s_brd_prefix);
static INT32 _dev_db_update_online_model(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                                 INT32 i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 CHAR* s_mdl_prefix);
static INT32 _dev_db_thread_query_codeset(DEV_DB_BMC_QUERY_T       t_bmc_query_info);
static INT32 _dev_db_thread_query_codeset_with_brand(DEV_DB_BMC_QUERY_T       t_bmc_query_info);
static VOID _dev_db_reset_merge_data(DEV_DB_BRMD_T* pt_array_brmd);
static INT32  _dev_db_reset_bmc_query_info(DEV_DB_BMC_QUERY_T*                pt_bmc_query_info);
static INT32 _dev_db_free_list(WFRCC_STRING_LIST_T * string_list,
                                  UINT32                ui4_length);
static VOID _dev_db_bm_info_sort(DEV_DB_BM_T* t_dev_bm_info,UINT32 ui4_num);
#ifdef APP_PORTING
static INT32 _dev_db_local_dual_query_mdl_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 CHAR* s_mdl_name,
                                                 INT32* pi4_mdl_idx);

static INT32 _dev_db_online_dual_query_mdl_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 CHAR* s_mdl_name,
                                                 INT32* pi4_mdl_idx);
#endif
static INT32 _dev_db_local_dual_query_brd_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 INT32* pi4_brd_idx);
static INT32 _dev_db_online_dual_query_brd_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 INT32* pi4_brd_idx);
static BOOL  _dev_db_is_need_to_continue_query_online_bm_info( VOID );
static BOOL  _dev_db_is_need_to_notify_client_or_query_online( VOID );
static UINT8 _dev_db_get_mlm_lang_id(
                    VOID
                    );
static INT32 _dev_db_thread_stop_task(DEV_DB_BMC_QUERY_T       t_bmc_query_info);
static INT32 _dev_db_upload_codeset_by_alp_and_num_string(
                                                                CHAR*   s_alp_arr,
                                                                UINT32  ui4_alp_arr_num,
                                                                CHAR*   s_codeset,
                                                                UINT32  ui4_codeset_size
                                                                );
static INT32 _dev_db_cancel_bmc_query(
                    VOID
                    );

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _dev_db_set_lock_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_set_lock_info( DEV_DB_LOCK_T  t_dev_db_lock )
{
    int fd = -1;
    INT32 i4_ret;

    i4_ret = access(DB_LOCK_FILE_PATH, F_OK);
    if (i4_ret != 0)
    {
        if (mkdir(DB_LOCK_FILE_PATH, 0777) == -1)
        {
            DBG_ERROR(("[DEV_DB]Create dir %s fail!!\n",DB_LOCK_FILE_PATH));
            return DEV_DBR_FAIL;
        }
    }

    if ((fd = open(DB_LOCK_FILE_NAME, O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1)
    {
        DBG_ERROR(("[DEV_DB]Create file %s fail!!\n",DB_LOCK_FILE_NAME));
    }
    else
    {
        write(fd,&t_dev_db_lock,( (UINT32)sizeof( DEV_DB_LOCK_T ) ));
        fsync(fd);
        close(fd);
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_get_lock_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_get_lock_info( DEV_DB_LOCK_T*  pt_dev_db_lock )
{
    DEV_DB_LOCK_T      t_dev_db_lock;
    FILE*              pf = 0;
    UINT32             ui4_read_count = 0;
    INT32              i4_ret;
    time_t             t_crt_time = 0;
    struct stat        sDirInfo;

    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));

    if (NULL == pt_dev_db_lock)
    {
        return DEV_DBR_FAIL;
    }

    if ( 0 == stat( DB_LOCK_FILE_NAME, &sDirInfo ))
    {
        pf = fopen(DB_LOCK_FILE_NAME,"r");

        if (pf == 0)
        {
             DBG_ERROR(("[DEV_DB]The file %s open fail !!\n",DB_LOCK_FILE_NAME));
             return DEV_DBR_FAIL;
        }
        else
        {
            ui4_read_count=fread( &t_dev_db_lock, 1, sizeof(DEV_DB_LOCK_T), pf );

            fclose(pf);
        }

        if (ui4_read_count != sizeof(DEV_DB_LOCK_T))
        {
            return DEV_DBR_FAIL;
        }

        c_memcpy(pt_dev_db_lock,
                 &t_dev_db_lock,
                 sizeof(DEV_DB_LOCK_T));

        DBG_INFO( ("[DEV_DB]the db_lock info is:ui4_cnt=%d,b_is_lock=%d,b_time_is_update=%d\n",t_dev_db_lock.ui4_cnt,t_dev_db_lock.b_is_lock,t_dev_db_lock.b_is_time_update));

        return DEV_DBR_OK;
    }
    else
    {
        DBG_INFO(("[DEV_DB]The file %s is not exist,and should create the file !!\n",DB_LOCK_FILE_NAME));

        t_crt_time = time (NULL);

        c_memcpy(&(t_dev_db_lock.t_time_cnt),
                 &t_crt_time,
                 sizeof(time_t));
        i4_ret = _dev_db_set_lock_info( t_dev_db_lock );

        if (DEV_DBR_OK != i4_ret)
        {
            DBG_ERROR(("[DEV_DB]Set the lock info fail !!\n"));
            return DEV_DBR_FAIL;
        }
    }

    return DEV_DBR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_get_lock_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_get_lock_status( DEV_DB_LOCK_T  t_dev_db_lock, DEV_DB_LOCK_STATUS_T* pe_lock_status )
{
    DEV_DB_LOCK_STATUS_T e_lock_status = DEV_DB_LOCK_STATUS_NONE;

    if (t_dev_db_lock.b_is_lock)
    {
        e_lock_status = DEV_DB_LOCK_STATUS_LOCK;
    }
    else if (DEV_DB_NORMAL_EDGE_NUM == t_dev_db_lock.ui4_cnt)
    {
        e_lock_status = DEV_DB_LOCK_STATUS_NORMAL_EDGE;
    }
    else
    {
        e_lock_status = DEV_DB_LOCK_STATUS_NORMAL;
    }

    *pe_lock_status = e_lock_status;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_update_lock_cnt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_update_lock_cnt( BOOL  b_is_cnt_add )
{
    DEV_DB_LOCK_T        t_dev_db_lock;
    time_t               t_crt_time = 0;
    BOOL                 b_is_sys_time_ready = FALSE;
    INT32                i4_ret;

    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));

    i4_ret = _dev_db_get_lock_info( &t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Get the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }

    b_is_sys_time_ready = a_dev_db_is_sys_time_ready();

    if ((b_is_sys_time_ready)
        && (FALSE == t_dev_db_lock.b_is_time_update))
    {

        t_crt_time = time (NULL);

        c_memcpy(&(t_dev_db_lock.t_time_cnt),
                 &t_crt_time,
                 sizeof(time_t));
        t_dev_db_lock.b_is_time_update = TRUE;
    }

    if (b_is_cnt_add)
    {
        t_dev_db_lock.ui4_cnt = t_dev_db_lock.ui4_cnt + 1;
    }

    i4_ret = _dev_db_set_lock_info( t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Set the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_set_lock
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_set_lock( VOID )
{
    DEV_DB_LOCK_T        t_dev_db_lock;
    time_t               t_crt_time = 0;
    BOOL                 b_is_sys_time_ready = FALSE;
    INT32                i4_ret;

    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));

    b_is_sys_time_ready = a_dev_db_is_sys_time_ready();

    if (b_is_sys_time_ready)
    {
        t_crt_time = time (NULL);

        c_memcpy(&(t_dev_db_lock.t_time_lock),
                 &t_crt_time,
                 sizeof(time_t));
        t_dev_db_lock.b_is_time_update = TRUE;
    }
    else
    {
        t_dev_db_lock.b_is_time_update = FALSE;
    }

    t_dev_db_lock.b_is_lock = TRUE;

    i4_ret = _dev_db_set_lock_info( t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Set the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_set_lock
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_set_unlock( VOID )
{
    DEV_DB_LOCK_T        t_dev_db_lock;
    INT32                i4_ret;

    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));

    t_dev_db_lock.ui4_cnt = 0;
    t_dev_db_lock.b_is_time_update = FALSE;

    i4_ret = _dev_db_set_lock_info( t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Set the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_ret = c_reset_query_mode();
#endif
    DBG_INFO(("[DEV_DB]c_reset_query_mode() return value i4_ret=%d !!\n",i4_ret));

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_get_lock_timeout
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_get_lock_timeout( BOOL* pb_is_timeout )
{
    DEV_DB_LOCK_T        t_dev_db_lock;
    time_t               t_crt_time = 0;
    BOOL                 b_is_sys_time_ready = FALSE;
    INT32                i4_ret;

    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));

    if (NULL == pb_is_timeout)
    {
        return DEV_DB_INV_ARG;
    }

    b_is_sys_time_ready = a_dev_db_is_sys_time_ready();

    DBG_INFO(("[DEV_DB]The sys time ready flag is b_is_sys_time_ready=%d !!\n",b_is_sys_time_ready));

    i4_ret = _dev_db_get_lock_info( &t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Get the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }

    if (FALSE == b_is_sys_time_ready)
    {
        DBG_INFO( ("[DEV_DB]The sys time have not ready\n"));
        *pb_is_timeout = FALSE;
        return DEV_DBR_OK;
    }

    t_crt_time = time (NULL);


    if (FALSE == t_dev_db_lock.b_is_time_update)
    {
        DBG_INFO(("[DEV_DB]Time count have not been update !!\n"));

        c_memcpy(&(t_dev_db_lock.t_time_lock),
                 &t_crt_time,
                 sizeof(time_t));

        t_dev_db_lock.b_is_time_update = TRUE;

        i4_ret = _dev_db_set_lock_info( t_dev_db_lock );

        if (DEV_DBR_OK != i4_ret)
        {
            DBG_ERROR(("[DEV_DB]Set the lock info fail !!\n"));
            return DEV_DBR_FAIL;
        }

        *pb_is_timeout = FALSE;
        return DEV_DBR_OK;
    }

    if ((t_crt_time > t_dev_db_lock.t_time_lock)
        && ((t_crt_time - t_dev_db_lock.t_time_lock) >= ((time_t)(DEV_DB_LOCK_TIMEOUT_TIME))))
    {
        *pb_is_timeout = TRUE;
    }
    else
    {
        *pb_is_timeout = FALSE;
    }

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _dev_db_get_unlock_timeout
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_get_unlock_timeout( BOOL* pb_is_timeout )
{
    DEV_DB_LOCK_T        t_dev_db_lock;
    time_t               t_crt_time = 0;
    BOOL                 b_is_sys_time_ready = FALSE;
    INT32                i4_ret;

    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));

    if (NULL == pb_is_timeout)
    {
        return DEV_DB_INV_ARG;
    }

    b_is_sys_time_ready = a_dev_db_is_sys_time_ready();

    DBG_INFO(("[DEV_DB]The sys time ready flag is b_is_sys_time_ready=%d !!\n",b_is_sys_time_ready));

    i4_ret = _dev_db_get_lock_info( &t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Get the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }

    if (FALSE == b_is_sys_time_ready)
    {
        DBG_INFO( ("[DEV_DB]The sys time have not ready\n"));
        *pb_is_timeout = FALSE;
        return DEV_DBR_OK;
    }

    t_crt_time = time (NULL);

    if (FALSE == t_dev_db_lock.b_is_time_update)
    {
        DBG_INFO(("[DEV_DB]Time count have not been update !!\n"));

        c_memcpy(&(t_dev_db_lock.t_time_cnt),
                 &t_crt_time,
                 sizeof(time_t));

        t_dev_db_lock.b_is_time_update = TRUE;

        i4_ret = _dev_db_set_lock_info( t_dev_db_lock );

        if (DEV_DBR_OK != i4_ret)
        {
            DBG_ERROR(("[DEV_DB]Set the lock info fail !!\n"));
            return DEV_DBR_FAIL;
        }

        *pb_is_timeout = FALSE;
        return DEV_DBR_OK;
    }

    if ((t_crt_time > t_dev_db_lock.t_time_cnt)
        && ((t_crt_time - t_dev_db_lock.t_time_cnt) >= ((time_t)(DEV_DB_LOCK_TIMEOUT_TIME))))
    {
        *pb_is_timeout = TRUE;
    }
    else
    {
        *pb_is_timeout = FALSE;
    }

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _dev_db_bmc_query_thread_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_bmc_query_thread_create( VOID )
{
    INT32                 result;
    pthread_attr_t        attr;
    DEV_DB_UTIL_T*        pt_dev_db    = &t_g_dev_db_util;

    /* init the thread attr and will use the default value to create the thread*/
    (void)pthread_attr_init(&attr);

    result =  pthread_create( (pthread_t *)(&(pt_dev_db->h_thread)), &attr, _dev_db_bmc_thread_query, (VOID*) pt_dev_db);
    (void)pthread_attr_destroy(&attr); /* does nothing, could, looks more symmetric */
    if ( 0 != result )
    {
        DBG_ERROR(("[DEV_DB]threads dmc create failed !!"));
        return DEV_DBR_FAIL;
    }

    DBG_INFO(("[DEV_DB]threads dmc create successful !!"));

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name:_dev_db_free_list
 *
 * Description:if the list for dev/brand/model is not use, should free the list
 * otherwise will cause memory leak.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_free_list(WFRCC_STRING_LIST_T * string_list,
                           UINT32                ui4_length)
{
    UINT32          ui4_idx   = 0;

    if ((NULL != string_list->p_list)
        && (ui4_length > 0))
    {
        for(ui4_idx = 0; ui4_idx < ui4_length; ui4_idx++)
        {
            if(string_list->p_list[ui4_idx] != NULL)
            {
                c_mem_free(string_list->p_list[ui4_idx]);
                string_list->p_list[ui4_idx] = NULL;
            }
        }

        c_mem_free((string_list->p_list));
        string_list->p_list = NULL;
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_type_info
 *
 * Description: reset the glob dev type info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_type_info(VOID)
{
    UINT32          ui4_idx   = 0;
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    for (ui4_idx = 0; ui4_idx < DEV_DB_MAX_DEV_TYPE_CONT; ui4_idx ++)
    {
        c_memset(&(pt_dev_db->t_dev_type[ui4_idx]),0,sizeof (DEV_DB_TYPE_T));

        pt_dev_db->t_dev_type[ui4_idx].i4_deva_src_idx  = -1;
        pt_dev_db->t_dev_type[ui4_idx].i4_devb_src_idx  = -1;
    }

    pt_dev_db->ui4_dev_type_num = 0;
    pt_dev_db->e_dev_type_category = DEV_DB_DEV_TYPE_CTGY_NONE;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_brand_info
 *
 * Description: reset the glob brand info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_brand_info(VOID)
{
    UINT32          ui4_idx   = 0;
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the brand info*/
        c_memset(&(pt_dev_db->t_brd_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_dev_db->t_brd_info[ui4_idx].i4_local1_idx  = -1;
        pt_dev_db->t_brd_info[ui4_idx].i4_online1_idx = -1;
        pt_dev_db->t_brd_info[ui4_idx].i4_local2_idx  = -1;
        pt_dev_db->t_brd_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_dev_db->c_brand_prefix[ui4_idx] = '\0';
    }

    /* init the brand num*/
    pt_dev_db->ui4_brd_num   = 0;
    return DEV_DBR_OK;

}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_bm_info
 *
 * Description: reset  the temp brand or model info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_bm_info(DEV_DB_BM_T* t_dev_bm_info)
{
    UINT32          ui4_idx   = 0;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the bm info*/
        c_memset(&(t_dev_bm_info[ui4_idx]),0,sizeof (DEV_DB_BM_T));
        t_dev_bm_info[ui4_idx].i4_idx  = -1;
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_model_info
 *
 * Description: reset the glob model info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_model_info(VOID)
{
    UINT32          ui4_idx   = 0;
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the model info*/
        c_memset(&(pt_dev_db->t_model_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_dev_db->t_model_info[ui4_idx].i4_local1_idx  = -1;
        pt_dev_db->t_model_info[ui4_idx].i4_online1_idx = -1;
        pt_dev_db->t_model_info[ui4_idx].i4_local2_idx  = -1;
        pt_dev_db->t_model_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_dev_db->c_model_prefix[ui4_idx] = '\0';
    }

    /* init the model num*/
    pt_dev_db->ui4_model_num = 0;

    return DEV_DBR_OK;

}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_code_info
 *
 * Description: reset the glob code info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_code_info(VOID)
{
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    /* set the point of the codeset to NULL*/
    pt_dev_db->t_codeset.c_codeset1 = NULL;
    pt_dev_db->t_codeset.c_codeset2 = NULL;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_codeset_list_info
 *
 * Description: reset the glob code info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_codeset_list_info(VOID)
{
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    c_memset(&(pt_dev_db->t_codeset_list),0,sizeof (DEV_DB_CODESET_LIST_T));
    pt_dev_db->t_codeset_list.t_codeset_list1.i4_length = 0;
    pt_dev_db->t_codeset_list.t_codeset_list1.p_list = NULL;


    pt_dev_db->t_codeset_list.t_codeset_list2.i4_length = 0;
    pt_dev_db->t_codeset_list.t_codeset_list2.p_list = NULL;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_clean_codeset_list_info
 *
 * Description: reset the glob codeset list info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_clean_codeset_list_info(VOID)
{
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;


    /* free the first codeset list*/
    _dev_db_free_list(&(pt_dev_db->t_codeset_list.t_codeset_list1),
                      pt_dev_db->t_codeset_list.t_codeset_list1.i4_length);

    pt_dev_db->t_codeset_list.t_codeset_list1.i4_length = 0;


    /* free the second codeset list*/
    _dev_db_free_list(&(pt_dev_db->t_codeset_list.t_codeset_list2),
                      pt_dev_db->t_codeset_list.t_codeset_list2.i4_length);

    pt_dev_db->t_codeset_list.t_codeset_list2.i4_length = 0;

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name:_dev_db_reset_thread_query_info
 *
 * Description: reset the glob thread query info arr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_reset_thread_query_info(VOID)
{
    UINT32          ui4_idx   = 0;
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    for (ui4_idx = 0; ui4_idx < DEV_DB_QUERY_BUFF_LEN; ui4_idx ++)
    {
        /* init the thread query info*/
        _dev_db_reset_bmc_query_info(&(pt_dev_db->t_thread_query_info[ui4_idx]));
    }

    /* init the model num*/
    pt_dev_db->ui4_bm_query_count  = 0;
    pt_dev_db->ui4_bm_task_count   = 0;
    pt_dev_db->ui4_cur_pro_idx     = 0xFF;
    pt_dev_db->ui4_latest_task_idx = 0xFF;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_insert_bmc_query_task_info
 *
 * Description: reset the glob thread query info arr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_insert_bmc_query_task_info(DEV_DB_BMC_QUERY_T  t_bm_query_info)
{
    UINT32          ui4_idx   = 0;
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    a_dev_db_lock();

    /* should insert the task to the query idx is the min and the status of this slot is not procing*/

    /* for the first loop will find the first slot which e_buff_status is not procing*/
    for (ui4_idx = 0; ui4_idx < DEV_DB_QUERY_BUFF_LEN; ui4_idx ++)
    {
        if (DEV_DB_QUERY_BUFF_STATUS_PROCING != pt_dev_db->t_thread_query_info[ui4_idx].e_buff_status)
        {
            /* as find the corresspoding slot should do break here*/
            break;
        }
    }

    if (DEV_DB_QUERY_BUFF_LEN == ui4_idx)
    {
        DBG_ERROR(("\n[DEV_DB] the bm query task buff enter the max and will be overflow !!\n"));

        a_dev_db_unlock();
        return DEV_DBR_FAIL;
    }

    DBG_INFO(("\n[DEV_DB] _dev_db_insert_bmc_query_task_info(slot[%d]) !!\n",ui4_idx));

    /* init the model num*/
    pt_dev_db->ui4_bm_query_count ++;

    pt_dev_db->ui4_latest_task_idx = ui4_idx;


    c_memcpy(&(pt_dev_db->t_thread_query_info[ui4_idx]),&t_bm_query_info,sizeof (DEV_DB_BMC_QUERY_T));
    pt_dev_db->t_thread_query_info[ui4_idx].e_buff_status = DEV_DB_QUERY_BUFF_STATUS_PROC;
    pt_dev_db->t_thread_query_info[ui4_idx].ui4_query_idx = pt_dev_db->ui4_bm_query_count;
    pt_dev_db->t_thread_query_info[ui4_idx].ui4_task_idx = ui4_idx;
    pt_dev_db->t_thread_query_info[ui4_idx].ui4_notify_count = 0;
    pt_dev_db->t_thread_query_info[ui4_idx].b_is_to_clean = FALSE;

#ifdef APP_UEI_SPINNER_SUPPORT
	pt_dev_db->t_thread_query_info[ui4_idx].b_is_brd_online_query_start = FALSE;
	pt_dev_db->t_thread_query_info[ui4_idx].b_is_brd_online_query_complete = FALSE;
#endif

    /* as there is task for the bmc thread to deal with, so this thread should wakeup*/
    pthread_mutex_lock(&(pt_dev_db->mutex));

    if (0 == pt_dev_db->ui4_bm_task_count)
    {
        pt_dev_db->ui4_bm_task_count ++ ;
    }

    /* Cancle bmc query*/
    _dev_db_cancel_bmc_query();

    /* this condition should be always true*/
    if (pt_dev_db->ui4_bm_task_count > 0)
    {
        DBG_INFO( ("\n[dev_db_bmc_thread]the dev db bmc thread should wakeup as there is task for deal with!!!===xxxx\n"));
        pthread_cond_signal(&(pt_dev_db->cond));
    }

    pthread_mutex_unlock(&(pt_dev_db->mutex));

    a_dev_db_unlock();
    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name:_dev_db_get_bmc_query_task
 *
 * Description: reset the glob thread query info arr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_get_bmc_query_task(DEV_DB_BMC_QUERY_T* pt_bm_query_info,
                                               UINT32*  pui4_task_idx)
{
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    if ((NULL == pt_bm_query_info)
        || (NULL == pui4_task_idx))
    {
        DBG_ERROR( ("\n[DEV_DB] get bm task fail for pragram invalid!!"));
        return DEV_DB_INV_ARG;
    }

    a_dev_db_lock();

    if ((0 == pt_dev_db->ui4_bm_query_count)
        || (pt_dev_db->ui4_latest_task_idx >= DEV_DB_QUERY_BUFF_LEN)
        || (pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx].ui4_query_idx != pt_dev_db->ui4_bm_query_count)
        || (DEV_DB_QUERY_BUFF_STATUS_PROC != pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx].e_buff_status))
    {
        a_dev_db_unlock();

        DBG_ERROR( ("[DEV_DB]bm_query_cnt[%d],bm_last_task_idx[%d],"
                    "task_query_index[%d],buff_status[%d]",
                     pt_dev_db->ui4_bm_query_count,
                     pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx].ui4_query_idx,
                     pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx].e_buff_status));
        DBG_ERROR( ("\n[DEV_DB] get bm task fail for threre is not task to deal with!!"));
        return DEV_DBR_FAIL;
    }


    DBG_INFO( ("\n[DEV_DB] _dev_db_get_bmc_query_task(slot[%d])!!",pt_dev_db->ui4_latest_task_idx));

    pt_dev_db->ui4_cur_pro_idx = pt_dev_db->ui4_latest_task_idx;
    *pui4_task_idx   = pt_dev_db->ui4_latest_task_idx;

    pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx].e_buff_status = DEV_DB_QUERY_BUFF_STATUS_PROCING;

    c_memcpy(pt_bm_query_info,&(pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx]),sizeof (DEV_DB_BMC_QUERY_T));

    /* here should modify the task conut num, also this should be protect by the mutex*/
    pthread_mutex_lock(&(pt_dev_db->mutex));

    if (pt_dev_db->ui4_bm_task_count > 0)
    {
        pt_dev_db->ui4_bm_task_count --;
    }

    pthread_mutex_unlock(&(pt_dev_db->mutex));

    a_dev_db_unlock();
    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_notify_client_data_change
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID  _dev_db_notify_client_data_change(VOID* pv_nfy_param)
{
    DEV_DB_UTIL_T*               pt_dev_db     = &t_g_dev_db_util;
    UINT16                       ui2_i         = 0;
    DEV_DB_UTIL_NFY_CLIENT_T*    pt_client     = NULL;

    /* Collect all notify clients in to sort structure. */
    for (ui2_i = 0;
         ui2_i < (UINT16)DEV_DB_MAX_NUM_NOTIFY_CLIENT;
         ui2_i ++)
    {
        /* Load the client/ */
        pt_client =  &(pt_dev_db->at_notify_client[ui2_i]);

        /* Check match the group. */
        if (pt_client->pf_notify == NULL)
        {
            continue;
        }

        pt_client->pf_notify(pt_client->pv_tag,pv_nfy_param);
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_set_bmc_flag_before_notify_to_client
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32  _dev_db_set_bmc_flag_before_notify_to_client(DEV_DB_BMC_QUERY_T*  pt_bmc_query_info, BOOL b_is_to_set_clean_flag)
{
    a_dev_db_lock();
    if (b_is_to_set_clean_flag)
    {
        pt_bmc_query_info->b_is_to_clean = TRUE;
    }
    else
    {
        pt_bmc_query_info->ui4_notify_count ++;
    }

    a_dev_db_unlock();

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_is_need_to_notify_client_or_query_online
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL  _dev_db_is_need_to_notify_client_or_query_online( VOID )
{
    DEV_DB_UTIL_T*               pt_dev_db     = &t_g_dev_db_util;
    BOOL                         b_is_to_notify = TRUE;

    /* here should modify the task conut num, also this should be protect by the mutex*/
    pthread_mutex_lock(&(pt_dev_db->mutex));
    if (pt_dev_db->ui4_bm_task_count > 0)
    {
        b_is_to_notify = FALSE;
    }
    pthread_mutex_unlock(&(pt_dev_db->mutex));

    return b_is_to_notify;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_is_need_to_continue_query_online_bm_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL  _dev_db_is_need_to_continue_query_online_bm_info( VOID )
{
    DEV_DB_UTIL_T*               pt_dev_db      = &t_g_dev_db_util;
    BOOL                         b_is_to_query = TRUE;
    UINT32                       ui4_index = 0;

    /* here will max check 5s*/
    for ( ui4_index = 0; ui4_index < DEV_DB_ONLINE_QUERY_CHEECK_CONT; ui4_index++ )
    {
        pthread_mutex_lock(&(pt_dev_db->mutex));

        if (pt_dev_db->ui4_bm_task_count > 0)
        {
            b_is_to_query = FALSE;

            pthread_mutex_unlock(&(pt_dev_db->mutex));
            break;
        }
        pthread_mutex_unlock(&(pt_dev_db->mutex));

        sleep(1);
    }
    return b_is_to_query;
}
/*-----------------------------------------------------------------------------
 * Name: _dev_db_update_local_brand
 *
 * Description: sync query for brand info and do the brand info merge if necessary
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_update_local_brand(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                                 INT32 i4_type_idx,
                                                 CHAR* s_brd_prefix)
{
    WFRCC_STRING_LIST_T      t_local_brand_list  = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BM_T              t_dev_brand_info[DEV_DB_DUL_OP_MAX];
    BOOL                     b_is_brand_list_valid = FALSE;
    INT32                    i4_local_brand_num;
    INT32                    i4_index            = 0;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    _dev_db_reset_bm_info(t_dev_brand_info);
#ifdef APP_PORTING
    i4_local_brand_num = c_get_brands_with_type(&(t_local_brand_list.p_list), i4_type_idx, s_brd_prefix);
#endif
    if ((i4_local_brand_num <= 0)
        || (i4_local_brand_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_local_brand_list.p_list))
    {
        /* do nothing*/
        b_is_brand_list_valid = FALSE;
        DBG_ERROR(("[DEV_DB] the brand is get fail!\n"));
    }
    else
    {
        for (i4_index = 0; i4_index < i4_local_brand_num; i4_index ++)
        {
            /* temp copy the value of the online query result in the c_online_brand_list for the merge function use*/
            c_strncpy(t_dev_brand_info[i4_index].s_src_name, t_local_brand_list.p_list[i4_index], DEV_DB_NAME_LEN_MAX);
            t_dev_brand_info[i4_index].i4_idx = i4_index;
        }

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_brand_list,
                          i4_local_brand_num);

        b_is_brand_list_valid = TRUE;
    }

    if (b_is_brand_list_valid)
    {
        a_dev_db_lock();
        /*merge the brand1 list to the glob data----> here will just copy data*/
        _dev_db_bm_info_sort(t_dev_brand_info,i4_local_brand_num);

        _dev_db_merge_sort(
            (DEV_DB_BRMD_T*)(pt_dev_db->t_brd_info),
            t_dev_brand_info,
            &(pt_dev_db->ui4_brd_num),
            i4_local_brand_num,
            e_merge_type);

        a_dev_db_unlock();

        return DEV_DBR_OK;
    }
    else
    {
        return DEV_DBR_FAIL;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_update_local_model
 *
 * Description: sync query for model and do brand info merge if necessary
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_update_local_model(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                         INT32 i4_type_idx,
                                         CHAR* s_brd_name,
                                         CHAR* s_mdl_prefix)
{
    WFRCC_STRING_LIST_T      t_local_model_list  = {NULL, 0 , 0};
    WFRCC_STRING_LIST_T      t_local_brd_list    = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BM_T              t_dev_mdl_info[DEV_DB_DUL_OP_MAX];
    INT32                    i4_local_mdl_num;
    INT32                    i4_local_brd_num;
    INT32                    i4_index            = 0;
    INT32                    i4_brd_idx;
    BOOL                     b_is_mdl_list_valid = FALSE;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((NULL == s_brd_name)
         || (c_strcmp(s_brd_name, "") == 0))
    {
        DBG_ERROR(("[DEV_DB] brand name for local model query is invalid!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_local_brd_num = c_get_brands_with_type(&(t_local_brd_list.p_list), i4_type_idx, s_brd_name);
#endif
    if (i4_local_brd_num <= 0)
    {
        DBG_ERROR(("[DEV_DB] brand info get fail for local model query!\n"));
        return DEV_DBR_FAIL;
    }

    for (i4_index = 0; i4_index < i4_local_brd_num; i4_index ++)
    {
        if (c_strcasecmp(t_local_brd_list.p_list[i4_index], s_brd_name) == 0)
        {
            break;
        }
    }

    /* here should free the memory about the dev list*/
    _dev_db_free_list(&t_local_brd_list,
                      i4_local_brd_num);

    if (i4_index >= i4_local_brd_num)
    {
        DBG_ERROR(("[DEV_DB] could not get the brand name %s for local model query!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    _dev_db_reset_bm_info(t_dev_mdl_info);

    i4_brd_idx = i4_index;
    DBG_INFO(("[DEV_DB] i4_brd_idx=%d\n",i4_brd_idx));
#ifdef APP_PORTING
    i4_local_mdl_num = c_get_models_with_brand(&(t_local_model_list.p_list), i4_brd_idx, s_mdl_prefix);
#endif
    if ((i4_local_mdl_num <= 0)
        || (i4_local_mdl_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_local_model_list.p_list))
    {
        /* do nothing*/
        b_is_mdl_list_valid = FALSE;
    }
    else
    {
        for (i4_index = 0; i4_index < i4_local_mdl_num; i4_index ++)
        {
            /* temp copy the value of the online query result in the c_online_brand_list for the merge function use*/
            c_strncpy(t_dev_mdl_info[i4_index].s_src_name, t_local_model_list.p_list[i4_index], DEV_DB_NAME_LEN_MAX);
            t_dev_mdl_info[i4_index].i4_idx = i4_index;
        }

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_model_list,
                          i4_local_mdl_num);

        b_is_mdl_list_valid = TRUE;
    }

    if (b_is_mdl_list_valid)
    {
        //_dev_db_bm_info_sort(t_dev_mdl_info,i4_local_mdl_num);

        /* as here will modify the glob data list of the brand, so should lock here*/
        a_dev_db_lock();
        _dev_db_merge_sort(
            (DEV_DB_BRMD_T*)(pt_dev_db->t_model_info),
            t_dev_mdl_info,
            &(pt_dev_db->ui4_model_num),
            i4_local_mdl_num,
            e_merge_type);

        a_dev_db_unlock();

        return DEV_DBR_OK;
    }
    else
    {
        return DEV_DBR_FAIL;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_thread_stop_task
 *
 * Description: this function only need to clean the bmc query slot
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_thread_stop_task(DEV_DB_BMC_QUERY_T       t_bmc_query_info)
{
    DEV_DB_UTIL_T*           pt_dev_db             = &t_g_dev_db_util;

    a_dev_db_lock();
    _dev_db_reset_bmc_query_info(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx]));
    a_dev_db_unlock();

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _dev_db_thread_query_brd
 *
 * Description: sync query for model and do brand info merge if necessary, and before notify to the
 *                   client, should check if there is new task to do, if yes should discard this task. also
 *                   before query the online task, should check if there is new task to do. as the online
 *                   query will need lot of time to do, so we assum that the user need 5s for input new
 *                   prefex for new task. and we should check max 5s for new task. if there is new task
 *                   at this time, should discard the online query. all the above is to reduce the query time
 *                   for the new task, as the lib is only support single thread query and the fun of the lib
 *                   is in sync operate.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_thread_query_brd(DEV_DB_BMC_QUERY_T       t_bmc_query_info)
{
    BOOL                     b_is_local_brd1_valid = FALSE;
    BOOL                     b_is_local_brd2_valid = FALSE;
    DEV_DB_UTIL_T*           pt_dev_db             = &t_g_dev_db_util;
    INT32                    i4_ret;

    a_dev_db_lock();

    /* as here will modify the gobe data, so should use the lock to protect it.*/
    _dev_db_reset_brand_info();
    c_strncpy(pt_dev_db->c_brand_prefix, t_bmc_query_info.s_brd_prefix, DEV_DB_NAME_LEN_MAX);

    a_dev_db_unlock();

    DBG_INFO(("[DEV_DB] bmc info for brand query: "
               "type_view_idx[%d],brd_prefix[%s] !\n",
               t_bmc_query_info.ui4_type_svidx,
               t_bmc_query_info.s_brd_prefix));

    do
    {
        if (t_bmc_query_info.b_is_dual)
        {
               /* for local party*/
            i4_ret = _dev_db_update_local_brand(DEV_DB_MGE_LOCAL_A,
                                t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                t_bmc_query_info.s_brd_prefix);
            if (DEV_DBR_OK == i4_ret)
            {
                 b_is_local_brd1_valid = TRUE;
            }

               /* for local party*/
            i4_ret = _dev_db_update_local_brand(DEV_DB_MGE_LOCAL_B,
                                t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                                t_bmc_query_info.s_brd_prefix);
            if (DEV_DBR_OK == i4_ret)
            {
                 b_is_local_brd2_valid = TRUE;
            }

            if (b_is_local_brd1_valid || b_is_local_brd2_valid)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/
                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the brand info(LOCAL_A & "
                           "LOCAL_B) to client !\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }

            if (FALSE == _dev_db_is_need_to_continue_query_online_bm_info())
            {
                /* as the client have new task to do, so this task about online query should be discard*/

                DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand query for online !\n"));
                break;
            }

            i4_ret = _dev_db_update_online_brand(DEV_DB_MGE_ONLINE_A,
                             t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                             t_bmc_query_info.s_brd_prefix);

            if (DEV_DBR_OK == i4_ret)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard "
                               "the brand info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the brand info (LOCAL_A & LOCAL_B "
                           "& ONLINE_A) client !\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }

            if (FALSE == _dev_db_is_need_to_continue_query_online_bm_info())
            {
                /* as the client have new task to do, so this task about online query should be discard*/

                DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand query for online !\n"));
                break;
            }

            i4_ret = _dev_db_update_online_brand(DEV_DB_MGE_ONLINE_B,
                             t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                             t_bmc_query_info.s_brd_prefix);

            if (DEV_DBR_OK == i4_ret)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the brand info (LOCAL_A & LOCAL_B & ONLINE_A "
                           "& ONLINE_B) client !\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/

#ifdef APP_UEI_SPINNER_SUPPORT
				 pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx].b_is_brd_online_query_complete = TRUE;
#endif

                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }
        }
        else
        {
               /* for local party*/
            i4_ret = _dev_db_update_local_brand(DEV_DB_MGE_LOCAL_A,
                            t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                            t_bmc_query_info.s_brd_prefix);
            if (DEV_DBR_OK == i4_ret)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the brand info (LOCAL_A ) to client!\n"));

                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));

            }

            if (FALSE == _dev_db_is_need_to_continue_query_online_bm_info())
            {
                /* as the client have new task to do, so this task about online query should be discard*/

                DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand query for online !\n"));
                break;
            }

            i4_ret = _dev_db_update_online_brand(DEV_DB_MGE_ONLINE_A,
                         t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                         t_bmc_query_info.s_brd_prefix);

            if (DEV_DBR_OK == i4_ret)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the brand info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the brand info (LOCAL_A & ONLINE_A) to client!\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/

#ifdef APP_UEI_SPINNER_SUPPORT
				 pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx].b_is_brd_online_query_complete = TRUE;
#endif
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }
        }
    }while(0);

    DBG_INFO(("[DEV_DB] notify the client to clean the brand query slot[%d] !\n", t_bmc_query_info.ui4_task_idx));

    _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), TRUE);
     /* notify the data to the client*/
    _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_thread_query_mdl
 *
 * Description: sync query for model and do brand info merge if necessary and before notify to the
 *                   client, should check if there is new task to do, if yes should discard this task. also
 *                   before query the online task, should check if there is new task to do. as the online
 *                   query will need lot of time to do, so we assum that the user need 5s for input new
 *                   prefex for new task. and we should check max 5s for new task. if there is new task
 *                   at this time, should discard the online query. all the above is to reduce the query time
 *                   for the new task, as the lib is only support single thread query and the fun of the lib
 *                   is in sync operate.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_thread_query_mdl(DEV_DB_BMC_QUERY_T       t_bmc_query_info)
{
    DEV_DB_UTIL_T*           pt_dev_db            = &t_g_dev_db_util;
    BOOL                     b_is_local_mdl1_valid = FALSE;
    BOOL                     b_is_local_mdl2_valid = FALSE;
    INT32                    i4_ret;

    a_dev_db_lock();

    /* as here will modify the gobe data, so should use the lock to protect it.*/
    _dev_db_reset_model_info();

    c_strncpy(pt_dev_db->c_model_prefix, t_bmc_query_info.s_mdl_prefix, DEV_DB_NAME_LEN_MAX);

    a_dev_db_unlock();


    DBG_INFO(("[DEV_DB] bmc info for model query: "
               "type_view_idx[%d],brd_name[%s],mdl_prefix[%s] !\n",
               t_bmc_query_info.ui4_type_svidx,
               t_bmc_query_info.s_brd_name,
               t_bmc_query_info.s_mdl_prefix));

    do
    {

        if (t_bmc_query_info.b_is_dual)
        {
               /* for local party*/
            i4_ret =  _dev_db_update_local_model(DEV_DB_MGE_LOCAL_A,
                                            t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                            t_bmc_query_info.s_brd_name,
                                            t_bmc_query_info.s_mdl_prefix);
            if (DEV_DBR_OK == i4_ret)
            {
                 b_is_local_mdl1_valid = TRUE;
            }

            /* for local party*/
            i4_ret =  _dev_db_update_local_model(DEV_DB_MGE_LOCAL_B,
                                            t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                                            t_bmc_query_info.s_brd_name,
                                            t_bmc_query_info.s_mdl_prefix);
            if (DEV_DBR_OK == i4_ret)
            {
                 b_is_local_mdl2_valid = TRUE;
            }

            if (b_is_local_mdl1_valid || b_is_local_mdl2_valid)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the model info (LOCAL_A & LOCAL_B) to client!\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }

            if (FALSE == _dev_db_is_need_to_continue_query_online_bm_info())
            {
                /* as the client have new task to do, so this task about online query should be discard*/

                DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model query for online !\n"));
                break;
            }

            i4_ret = _dev_db_update_online_model(DEV_DB_MGE_ONLINE_A,
                             t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                             t_bmc_query_info.t_brd_sel_info.s_src_name,
                             t_bmc_query_info.s_mdl_prefix);

            if (DEV_DBR_OK == i4_ret)
            {

                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the model info (LOCAL_A & LOCAL_B & ONLINE_A) to client!\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }

            if (FALSE == _dev_db_is_need_to_continue_query_online_bm_info())
            {
                /* as the client have new task to do, so this task about online query should be discard*/

                DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model query for online !\n"));
                break;
            }

            i4_ret = _dev_db_update_online_model(DEV_DB_MGE_ONLINE_B,
                             t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                             t_bmc_query_info.s_brd_name,
                             t_bmc_query_info.s_mdl_prefix);

            if (DEV_DBR_OK == i4_ret)
            {

                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the model info (LOCAL_A & LOCAL_B & ONLINE_A & ONLINE_B) to client!\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }

        }
        else
        {
           /* for local party*/
            i4_ret =  _dev_db_update_local_model(DEV_DB_MGE_LOCAL_A,
                                           t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                           t_bmc_query_info.s_brd_name,
                                           t_bmc_query_info.s_mdl_prefix);
            if (DEV_DBR_OK == i4_ret)
            {

                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model info notify to client !\n"));
                    break;
                }


                DBG_INFO(("[DEV_DB] notify the model info (LOCAL_A) to client!\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }

            if (FALSE == _dev_db_is_need_to_continue_query_online_bm_info())
            {
                /* as the client have new task to do, so this task about online query should be discard*/

                DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model query for online !\n"));
                break;
            }

            i4_ret = _dev_db_update_online_model(DEV_DB_MGE_ONLINE_A,
                             t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                             t_bmc_query_info.s_brd_name,
                             t_bmc_query_info.s_mdl_prefix);

            if (DEV_DBR_OK == i4_ret)
            {
                if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
                {
                    /* as the client have new task to do, so this task should be discard*/

                    DBG_INFO(("[DEV_DB] as there is new task to do, should discard the model info notify to client !\n"));
                    break;
                }

                DBG_INFO(("[DEV_DB] notify the model info (LOCAL_A & ONLINE_A) to client!\n"));
                _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), FALSE);
                 /* notify the data to the client*/
                _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
            }
        }
    }while (0);

    DBG_INFO(("[DEV_DB] notify the client to clean the model query slot[%d] !\n", t_bmc_query_info.ui4_task_idx));
    _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), TRUE);
     /* notify the data to the client*/
    _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_bmc_thread_query
 *
 * Description: the online query fun for brand/model/codeset
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID* _dev_db_bmc_thread_query( VOID* parg )
{
    DEV_DB_BMC_QUERY_T       t_bmc_query_info;
    DEV_DB_UTIL_T*           pt_dev_db            = &t_g_dev_db_util;
    pthread_t                h_thread;
    UINT32                   ui4_task_idx;
    INT32                    i4_ret;

    h_thread = pthread_self();

    /* set the thread as detachable so storage can be recovered without a join */
    (void)pthread_detach((pthread_t)h_thread);

    do
    {
        /* if there is not bm query task, should pause this thread*/
        pthread_mutex_lock(&(pt_dev_db->mutex));
        if (0 == pt_dev_db->ui4_bm_task_count)
        {
            DBG_INFO(("\n[DEV_DB_BMC_THREAD] thread BMC paused for condition wait!!\n"));
            pthread_cond_wait(&(pt_dev_db->cond),&(pt_dev_db->mutex));
        }
        pthread_mutex_unlock(&(pt_dev_db->mutex));

        i4_ret = _dev_db_get_bmc_query_task(&t_bmc_query_info,&ui4_task_idx);

        if (DEV_DBR_OK != i4_ret)
        {
            /* the task get fail and this would not our expect and should exit the bmc query thread*/
            break;
        }

        if (DEV_DB_THREAD_QUERY_BRAND == t_bmc_query_info.e_query_type)
        {
             _dev_db_thread_query_brd(t_bmc_query_info);
        }
        else if (DEV_DB_THREAD_QUERY_MODEL == t_bmc_query_info.e_query_type)
        {
             _dev_db_thread_query_mdl(t_bmc_query_info);
        }
        else if (DEV_DB_THREAD_QUERY_CODESET == t_bmc_query_info.e_query_type)
        {
            _dev_db_thread_query_codeset(t_bmc_query_info);
        }
        else if (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD == t_bmc_query_info.e_query_type)
        {
            _dev_db_thread_query_codeset_with_brand(t_bmc_query_info);
        }
        else if (DEV_DB_THREAD_QUERY_STOP == t_bmc_query_info.e_query_type)
        {
            /* this is case only need to clean the slot info*/
            _dev_db_thread_stop_task(t_bmc_query_info);
        }
        else
        {
            /* current only support the above three query case*/
            break;
        }

    }while(1);

    /* exit the thread*/
    pthread_exit(NULL);

    /* probably won't return here, but the compiler cares */
    return NULL;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_update_online_brand
 *
 * Description: the online query fun for brand
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_update_online_brand(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                                 INT32 i4_type_idx,
                                                 CHAR* s_brd_prefix)
{
    WFRCC_STRING_LIST_T      t_online_brand_list   = {NULL, 0 , 0};
    DEV_DB_BM_T              t_dev_brd_info[DEV_DB_DUL_OP_MAX];
    DEV_DB_UTIL_T*           pt_dev_db             = &t_g_dev_db_util;
    INT32                    i4_index              = 0;
    INT32                    i4_online_brand_num   = 0;
    BOOL                     b_is_online_valid     = FALSE;

    if ((NULL == s_brd_prefix)
        || (( (UINT32)c_strlen( ( const CHAR * )s_brd_prefix ) ) < 3))
    {
        DBG_ERROR(("[DEV_DB] the len of the prexfix brand should more then three!\n"));
        return DEV_DBR_FAIL;
    }

#ifdef APP_UEI_SPINNER_SUPPORT
    /*indicate brand online query is start*/
	DBG_INFO(("[####DEV_DB%s(%d)] before brd online query start\n",__FUNCTION__,__LINE__));
	pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx].b_is_brd_online_query_start = TRUE;
    _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx])), FALSE);
	_dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[pt_dev_db->ui4_latest_task_idx])));
	DBG_INFO(("[####DEV_DB%s(%d)] after brd online query start\n",__FUNCTION__,__LINE__));
#endif
    #ifdef APP_PORTING
    /* get the on-line brand info*/
    i4_online_brand_num = c_online_get_brands_with_type(&(t_online_brand_list.p_list), i4_type_idx, s_brd_prefix);
    #endif
    if ((i4_online_brand_num > 0)
        && (i4_online_brand_num < DEV_DB_DUL_OP_MAX)
        && (NULL != t_online_brand_list.p_list))
    {
        DBG_INFO(("[DEV_DB] the dev db online brand get successful, and the dev_type=%d,brand_prefix=%s!\n",i4_type_idx,s_brd_prefix));
        /* online query result valid*/
        b_is_online_valid = TRUE;
    }
    else
    {
        DBG_ERROR(("[DEV_DB] the dev db online brand get fail, and the dev_type=%d,brand_prefix=%s!\n",i4_type_idx,s_brd_prefix));
        /* online query result not valid*/
        b_is_online_valid = FALSE;
    }

    if (b_is_online_valid == TRUE)
    {
        _dev_db_reset_bm_info(t_dev_brd_info);

        for (i4_index = 0; i4_index < i4_online_brand_num; i4_index ++)
        {
            /* temp copy the value of the online query result in the c_online_brand_list for the merge function use*/
            c_strncpy(t_dev_brd_info[i4_index].s_src_name, t_online_brand_list.p_list[i4_index], DEV_DB_NAME_LEN_MAX);
            t_dev_brd_info[i4_index].i4_idx = i4_index;
        }

        /* here should free the memory about the online brand list*/
        _dev_db_free_list(&t_online_brand_list,
                          i4_online_brand_num);

        _dev_db_bm_info_sort(t_dev_brd_info,i4_online_brand_num);

        /* as here will modify the glob data, so should lock here first*/
        a_dev_db_lock();
        _dev_db_merge_sort(
            (DEV_DB_BRMD_T*) (pt_dev_db->t_brd_info),
            t_dev_brd_info,
            &(pt_dev_db->ui4_brd_num),
            i4_online_brand_num,
            e_merge_type);
        a_dev_db_unlock();

        return DEV_DBR_OK;
    }
    else
    {
        return DEV_DBR_FAIL;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_update_online_model
 *
 * Description: the online thread query fun for model
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_update_online_model(DEV_DB_MERGE_TYPE_T  e_merge_type,
                                                 INT32 i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 CHAR* s_mdl_prefix)
{
    WFRCC_STRING_LIST_T      t_online_model_list      = {NULL, 0 , 0};
    WFRCC_STRING_LIST_T      t_online_brand_list      = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db                = &t_g_dev_db_util;
    DEV_DB_BM_T              t_dev_mdl_info[DEV_DB_DUL_OP_MAX];
    INT32                    i4_online_brand_num      = -1;
    INT32                    i4_online_model_num      = -1;
    INT32                    i4_online_brand_index    = 0;
    INT32                    i4_index                 = 0;

    if ((NULL == s_mdl_prefix)
        || (( (UINT32)c_strlen( ( const CHAR * )s_mdl_prefix ) ) < 3))
    {
        DBG_ERROR(("[DEV_DB] the len of the prexfix model should more then three!\n"));
        return DEV_DBR_FAIL;
    }

    if ((NULL == s_brd_name)
        || (( (UINT32)c_strlen( ( const CHAR * )s_brd_name ) ) < 3))
    {
        DBG_ERROR(("[DEV_DB] the brand name for model query should more than three!\n"));
        return DEV_DBR_FAIL;
    }

    if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
    {
        /* as the client have new task to do, so this task should be discard*/

        DBG_ERROR(("[DEV_DB] as there is new task to do, should discard the model online query!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_online_brand_num = c_online_get_brands_with_type(&(t_online_brand_list.p_list), i4_type_idx, s_brd_name);
#endif
    if ((i4_online_brand_num <= 0)
        || (i4_online_brand_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_online_brand_list.p_list))
    {
        /* here should free the memory about the online brand list*/
        _dev_db_free_list(&t_online_brand_list,
                          i4_online_brand_num);

        DBG_ERROR(("[DEV_DB] the brand get fail for online model query!\n"));
        return DEV_DBR_FAIL;
    }

    for (i4_index = 0; i4_index < i4_online_brand_num; i4_index ++)
    {
        if (c_strcasecmp(t_online_brand_list.p_list[i4_index], s_brd_name) == 0)
        {
            /* find the online brand index*/
            break;
        }
    }

    /* here should free the memory about the online brand list*/
    _dev_db_free_list(&t_online_brand_list,
                      i4_online_brand_num);

    if (i4_index >= i4_online_brand_num)
    {
        DBG_ERROR(("[DEV_DB] could not get the brand name %s for online model query!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    /*get the online brand index and set the online brand valid flag*/
    i4_online_brand_index = i4_index;
    DBG_INFO(("[DEV_DB] i4_online_brand_index=%d\n",i4_online_brand_index));

    if (FALSE == _dev_db_is_need_to_notify_client_or_query_online())
    {
        /* as the client have new task to do, so this task should be discard*/

        DBG_ERROR(("[DEV_DB] as there is new task to do, should discard the model online query!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    /* if the online brand valid, should query the online mode here and do merge to the glob data*/
    i4_online_model_num = c_online_get_models_with_brand (&(t_online_model_list.p_list), i4_online_brand_index, s_mdl_prefix);
#endif
    if ((i4_online_model_num <= 0)
        || (i4_online_model_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_online_model_list.p_list))
    {
        /* here should free the memory about the online brand list*/
        _dev_db_free_list(&t_online_model_list,
                          i4_online_model_num);

        DBG_INFO(("[DEV_DB] online model query fail!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    _dev_db_reset_bm_info(t_dev_mdl_info);

    /* here only record the result*/
    for (i4_index = 0; i4_index < i4_online_model_num; i4_index ++)
    {
        c_strncpy(t_dev_mdl_info[i4_index].s_src_name, t_online_model_list.p_list[i4_index], DEV_DB_NAME_LEN_MAX);
        t_dev_mdl_info[i4_index].i4_idx = i4_index;
    }

    /* here should free the memory about the online brand list*/
    _dev_db_free_list(&t_online_model_list,
                      i4_online_model_num);

    //_dev_db_bm_info_sort(t_dev_mdl_info,i4_online_model_num);

    /* as will modify the glob data list of the brand, should lock here*/
    a_dev_db_lock();

    /* do data merge*/
    _dev_db_merge_sort(
        (DEV_DB_BRMD_T*) (pt_dev_db->t_model_info),
        t_dev_mdl_info,
        &(pt_dev_db->ui4_model_num),
        i4_online_model_num,
        e_merge_type);

    a_dev_db_unlock();

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_local_dual_query_mdl_idx_by_tb
 *
 * Description: the online thread query fun for model
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
#ifdef APP_PORTING
static INT32 _dev_db_local_dual_query_mdl_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 CHAR* s_mdl_name,
                                                 INT32* pi4_mdl_idx)
{
    WFRCC_STRING_LIST_T      t_local_model_list  = {NULL, 0 , 0};
    WFRCC_STRING_LIST_T      t_local_brd_list    = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db           = &t_g_dev_db_util;
    INT32                    i4_local_mdl_num;
    INT32                    i4_local_brd_num;
    INT32                    i4_index            = 0;
    INT32                    i4_brd_idx;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((NULL == s_brd_name)
         || (c_strcmp(s_brd_name, "") == 0))
    {
        DBG_ERROR(("[DEV_DB] brand name for local codeset query is invalid!\n"));

        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_local_brd_num = c_get_brands_with_type(&(t_local_brd_list.p_list), i4_type_idx, s_brd_name);
#endif
    if (i4_local_brd_num <= 0)
    {
        DBG_ERROR(("[DEV_DB] brand info get fail for local codeset query!\n"));

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_brd_list,
                          i4_local_brd_num);
        return DEV_DBR_FAIL;
    }

    for (i4_index = 0; i4_index < i4_local_brd_num; i4_index ++)
    {
        if (c_strcmp(t_local_brd_list.p_list[i4_index], s_brd_name) == 0)
        {
            break;
        }
    }

    /* here should free the memory about the dev list*/
    _dev_db_free_list(&t_local_brd_list,
                      i4_local_brd_num);

    if (i4_index >= i4_local_brd_num)
    {
        DBG_ERROR(("[DEV_DB] could not get the brand name %s for local codest query!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    i4_brd_idx = i4_index;


    if ((NULL == s_mdl_name)
         || (c_strcmp(s_mdl_name, "") == 0))
    {
        DBG_ERROR(("[DEV_DB] model name for local codeset query is invalid!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_local_mdl_num = c_get_models_with_brand(&(t_local_model_list.p_list), i4_brd_idx, s_mdl_name);
#endif
    if ((i4_local_mdl_num <= 0)
        || (i4_local_mdl_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_local_model_list.p_list))
    {
        DBG_ERROR(("[DEV_DB] model name for local codeset query is invalid!\n"));

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_model_list,
                          i4_local_mdl_num);
        return DEV_DBR_FAIL;
    }
    else
    {
        for (i4_index = 0; i4_index < i4_local_mdl_num; i4_index ++)
        {
            if (c_strcmp(t_local_model_list.p_list[i4_index], s_mdl_name) == 0)
            {
                break;
            }
        }

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_model_list,
                          i4_local_mdl_num);

        if (i4_index >= i4_local_mdl_num)
        {
            DBG_ERROR(("[DEV_DB] could not get the model name %s for local codest query!\n",s_brd_name));
            return DEV_DBR_FAIL;
        }

        *pi4_mdl_idx = i4_index;

        return DEV_DBR_OK;

    }

}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_local_dual_query_mdl_idx_by_tb
 *
 * Description: the online thread query fun for model
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_online_dual_query_mdl_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 CHAR* s_mdl_name,
                                                 INT32* pi4_mdl_idx)
{
    WFRCC_STRING_LIST_T      t_online_model_list      = {NULL, 0 , 0};
    WFRCC_STRING_LIST_T      t_online_brand_list      = {NULL, 0 , 0};
    INT32                    i4_online_brand_num      = -1;
    INT32                    i4_online_model_num      = -1;
    INT32                    i4_online_brand_index    = 0;
    INT32                    i4_index                 = 0;

    if ((NULL == s_brd_name)
        || (( (UINT32)c_strlen( ( const CHAR * )s_brd_name ) ) < 3))
    {
        DBG_ERROR(("[DEV_DB] the len of the prexfix model should more then three!\n"));
        return DEV_DBR_FAIL;
    }

    if ((NULL == s_mdl_name)
        || (( (UINT32)c_strlen( ( const CHAR * )s_mdl_name ) ) < 3))
    {
        DBG_ERROR(("[DEV_DB] the brand name for model query should more than three!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_online_brand_num = c_online_get_brands_with_type(&(t_online_brand_list.p_list), i4_type_idx, s_brd_name);
#endif
    if ((i4_online_brand_num <= 0)
        || (i4_online_brand_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_online_brand_list.p_list))
    {
        /* here should free the memory about the online brand list*/
        _dev_db_free_list(&t_online_brand_list,
                          i4_online_brand_num);

        DBG_ERROR(("[DEV_DB] the brand get fail for online codeset query!\n"));
        return DEV_DBR_FAIL;
    }

    for (i4_index = 0; i4_index < i4_online_brand_num; i4_index ++)
    {
        if (c_strcmp(t_online_brand_list.p_list[i4_index], s_brd_name) == 0)
        {
            /* find the online brand index*/
            break;
        }
    }

    /* here should free the memory about the online brand list*/
    _dev_db_free_list(&t_online_brand_list,
                      i4_online_brand_num);

    if (i4_index >= i4_online_brand_num)
    {
        DBG_ERROR(("[DEV_DB] could not get the brand name %s for online codeset query!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    /*get the online brand index and set the online brand valid flag*/
    i4_online_brand_index = i4_index;
#ifdef APP_PORTING
    /* if the online brand valid, should query the online mode here and do merge to the glob data*/
    i4_online_model_num = c_online_get_models_with_brand (&(t_online_model_list.p_list), i4_online_brand_index, s_mdl_name);
#endif
    if ((i4_online_model_num <= 0)
        || (i4_online_model_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_online_model_list.p_list))
    {
        /* here should free the memory about the online brand list*/
        _dev_db_free_list(&t_online_model_list,
                          i4_online_model_num);

        DBG_ERROR(("[DEV_DB] online model query fail!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    for (i4_index = 0; i4_index < i4_online_model_num; i4_index ++)
    {
        if (c_strcmp(t_online_model_list.p_list[i4_index], s_mdl_name) == 0)
        {
            /* find the online brand index*/
            break;
        }
    }

    /* here should free the memory about the online brand list*/
    _dev_db_free_list(&t_online_model_list,
                      i4_online_model_num);

    if (i4_index >= i4_online_model_num)
    {
        DBG_ERROR(("[DEV_DB] could not get the model name %s for online codeset query!\n",s_mdl_name));
        return DEV_DBR_FAIL;
    }

    *pi4_mdl_idx = i4_index;

    return DEV_DBR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _dev_db_local_dual_query_brd_idx_by_tb
 *
 * Description: the online thread query fun for model
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_local_dual_query_brd_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 INT32* pi4_brd_idx)
{
    WFRCC_STRING_LIST_T      t_local_brd_list    = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db           = &t_g_dev_db_util;
    INT32                    i4_local_brd_num;
    INT32                    i4_index            = 0;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((NULL == s_brd_name)
         || (c_strcmp(s_brd_name, "") == 0))
    {
        DBG_ERROR(("[DEV_DB] brand name for local codeset query is invalid!\n"));

        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_local_brd_num = c_get_brands_with_type(&(t_local_brd_list.p_list), i4_type_idx, s_brd_name);
#endif
    if ((i4_local_brd_num <= 0)
        || (i4_local_brd_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_local_brd_list.p_list))
    {
        DBG_ERROR(("[DEV_DB] brand info for local codeset query is invalid!\n"));

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_brd_list,
                          i4_local_brd_num);
        return DEV_DBR_FAIL;
    }
    else
    {
        for (i4_index = 0; i4_index < i4_local_brd_num; i4_index ++)
        {
            if (c_strcmp(t_local_brd_list.p_list[i4_index], s_brd_name) == 0)
            {
                break;
            }
        }

        /* here should free the memory about the dev list*/
        _dev_db_free_list(&t_local_brd_list,
                          i4_local_brd_num);

        if (i4_index >= i4_local_brd_num)
        {
            DBG_ERROR(("[DEV_DB] could not get the brand name %s for local codest query!\n",s_brd_name));
            return DEV_DBR_FAIL;
        }

        *pi4_brd_idx = i4_index;

        return DEV_DBR_OK;

    }

}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_online_dual_query_brd_idx_by_tb
 * Description: the online thread query fun for model
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_online_dual_query_brd_idx_by_tb(INT32  i4_type_idx,
                                                 CHAR* s_brd_name,
                                                 INT32* pi4_brd_idx)
{
    WFRCC_STRING_LIST_T      t_online_brand_list      = {NULL, 0 , 0};
    INT32                    i4_online_brand_num      = -1;
    INT32                    i4_index                 = 0;

    if ((NULL == s_brd_name)
        || (( (UINT32)c_strlen( ( const CHAR * )s_brd_name ) ) < 3))
    {
        DBG_ERROR(("[DEV_DB] the len of the prexfix model should more then three!\n"));
        return DEV_DBR_FAIL;
    }
#ifdef APP_PORTING
    i4_online_brand_num = c_online_get_brands_with_type(&(t_online_brand_list.p_list), i4_type_idx, s_brd_name);
#endif
    if ((i4_online_brand_num <= 0)
        || (i4_online_brand_num >= DEV_DB_DUL_OP_MAX)
        || (NULL == t_online_brand_list.p_list))
    {
        /* here should free the memory about the online brand list*/
        _dev_db_free_list(&t_online_brand_list,
                          i4_online_brand_num);

        DBG_ERROR(("[DEV_DB] the brand get fail for online codeset query!\n"));
        return DEV_DBR_FAIL;
    }

    for (i4_index = 0; i4_index < i4_online_brand_num; i4_index ++)
    {
        if (c_strcmp(t_online_brand_list.p_list[i4_index], s_brd_name) == 0)
        {
            /* find the online brand index*/
            break;
        }
    }

    /* here should free the memory about the online brand list*/
    _dev_db_free_list(&t_online_brand_list,
                      i4_online_brand_num);

    if (i4_index >= i4_online_brand_num)
    {
        DBG_ERROR(("[DEV_DB] could not get the brand name %s for online codeset query!\n",s_brd_name));
        return DEV_DBR_FAIL;
    }

    *pi4_brd_idx = i4_index;

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _dev_db_thread_query_codeset
 *
 * Description: will set the two codeset point, and if the local model index have been
 *                  got, will only query the local codeset. only the view type if dual only
 *                  need to consider the second dev type.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_thread_query_codeset(DEV_DB_BMC_QUERY_T       t_bmc_query_info)
{
#ifdef APP_PORTING
    DEV_DB_UTIL_T*           pt_dev_db          = &t_g_dev_db_util;
    BOOL                     b_is_dev_type_dul  = t_bmc_query_info.b_is_dual;
    INT32                    i4_ret;
    INT32                    i4_mdl_idx1 = -1;
    INT32                    i4_mdl_idx2 = -1;
    BOOL                     b_is_codeset1_valid = FALSE;
    BOOL                     b_is_codeset2_valid = FALSE;

    a_dev_db_lock();

    if (NULL != pt_dev_db->t_codeset.c_codeset1)
    {
        c_mem_free(pt_dev_db->t_codeset.c_codeset1);
        pt_dev_db->t_codeset.c_codeset1 = NULL;
    }


    if (NULL != pt_dev_db->t_codeset.c_codeset2)
    {
        c_mem_free(pt_dev_db->t_codeset.c_codeset2);
        pt_dev_db->t_codeset.c_codeset2 = NULL;
    }

    if (b_is_dev_type_dul)
    {
        /* local1 codeset query*/
       i4_ret = _dev_db_local_dual_query_mdl_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                             t_bmc_query_info.s_brd_name,
                                             t_bmc_query_info.s_mdl_name,
                                             &i4_mdl_idx1);

        if (DEV_DBR_OK == i4_ret)
        {
            i4_ret = c_get_codeset(&(pt_dev_db->t_codeset.c_codeset1),
                                   i4_mdl_idx1);

            if ((NULL == pt_dev_db->t_codeset.c_codeset1)
                || (0 != i4_ret))
            {
                DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset(c_codeset1) fail, i4_ret[%d]!\n",i4_ret));
                b_is_codeset1_valid = FALSE;
            }
            else
            {
                b_is_codeset1_valid = TRUE;
            }

        }
        else
        {
            b_is_codeset1_valid = FALSE;
        }

        if (FALSE == b_is_codeset1_valid)
        {
            /* online1 codeset query*/
            i4_ret = _dev_db_online_dual_query_mdl_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                                  t_bmc_query_info.s_brd_name,
                                                  t_bmc_query_info.s_mdl_name,
                                                  &i4_mdl_idx1);

            if (DEV_DBR_OK == i4_ret)
            {
            #ifdef APP_PORTING
                i4_ret = c_online_get_codeset(&(pt_dev_db->t_codeset.c_codeset1),
                                       i4_mdl_idx1);
            #endif
                if ((NULL == pt_dev_db->t_codeset.c_codeset1)
                    || (0 != i4_ret))
                {
                    b_is_codeset1_valid = FALSE;
                }
                else
                {
                    b_is_codeset1_valid = TRUE;
                }
            }
            else
            {
                b_is_codeset1_valid = FALSE;
            }
        }

        /* local2 codeset query*/
        i4_ret = _dev_db_local_dual_query_mdl_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                                              t_bmc_query_info.s_brd_name,
                                              t_bmc_query_info.s_mdl_name,
                                              &i4_mdl_idx2);

        if (DEV_DBR_OK == i4_ret)
        {
            i4_ret = c_get_codeset(&(pt_dev_db->t_codeset.c_codeset2),
                                   i4_mdl_idx2);

            if ((NULL == pt_dev_db->t_codeset.c_codeset2)
                || (0 != i4_ret))
            {
                DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset(c_codeset2) fail, i4_ret[%d]!\n",i4_ret));
                b_is_codeset2_valid = FALSE;
            }
            else
            {
                b_is_codeset2_valid = TRUE;
            }

        }
        else
        {
            b_is_codeset2_valid = FALSE;
        }

        if (FALSE == b_is_codeset2_valid)
        {
            /* online2 codeset query*/
            i4_ret = _dev_db_online_dual_query_mdl_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                                                  t_bmc_query_info.s_brd_name,
                                                  t_bmc_query_info.s_mdl_name,
                                                  &i4_mdl_idx2);

            if (DEV_DBR_OK == i4_ret)
            {
            #ifdef APP_PORTING
                i4_ret = c_online_get_codeset(&(pt_dev_db->t_codeset.c_codeset2),
                                       i4_mdl_idx2);
            #endif
                if ((NULL == pt_dev_db->t_codeset.c_codeset2)
                    || (0 != i4_ret))
                {
                    DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset(c_codeset2) fail, i4_ret[%d]!\n",i4_ret));
                    b_is_codeset2_valid = FALSE;
                }
                else
                {
                    b_is_codeset2_valid = TRUE;
                }
            }
            else
            {
                b_is_codeset2_valid = FALSE;
            }
       }

    }
    else
    {
         /* local1 codeset query*/

        i4_ret = _dev_db_local_dual_query_mdl_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                              t_bmc_query_info.s_brd_name,
                                              t_bmc_query_info.s_mdl_name,
                                              &i4_mdl_idx1);

         if (DEV_DBR_OK == i4_ret)
         {
             i4_ret = c_get_codeset(&(pt_dev_db->t_codeset.c_codeset1),
                                    i4_mdl_idx1);

             if ((NULL == pt_dev_db->t_codeset.c_codeset1)
                 || (0 != i4_ret))
             {
                 DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset(c_codeset1) fail, i4_ret[%d]!\n",i4_ret));
                 b_is_codeset1_valid = FALSE;
             }
             else
             {
                 b_is_codeset1_valid = TRUE;
             }

         }
         else
         {
             b_is_codeset1_valid = FALSE;
         }

         if (FALSE == b_is_codeset1_valid)
         {
             /* online1 codeset query*/
             i4_ret = _dev_db_online_dual_query_mdl_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                                   t_bmc_query_info.s_brd_name,
                                                   t_bmc_query_info.s_mdl_name,
                                                   &i4_mdl_idx1);

             if (DEV_DBR_OK == i4_ret)
             {
             #ifdef APP_PORTING
                 i4_ret = c_online_get_codeset(&(pt_dev_db->t_codeset.c_codeset1),
                                        i4_mdl_idx1);
             #endif
                 if ((NULL == pt_dev_db->t_codeset.c_codeset1)
                     || (0 != i4_ret))
                 {
                     b_is_codeset1_valid = FALSE;
                 }
                 else
                 {
                     b_is_codeset1_valid = TRUE;
                 }
             }
             else
             {
                 b_is_codeset1_valid = FALSE;
             }
         }
    }

    a_dev_db_unlock();

    if (FALSE == b_is_codeset1_valid)
    {
        pt_dev_db->t_codeset.c_codeset1 = NULL;
    }

    if (FALSE == b_is_codeset2_valid)
    {
        pt_dev_db->t_codeset.c_codeset2 = NULL;
    }
#if 0
    if ((NULL == pt_dev_db->t_codeset.c_codeset1)
        && (NULL == pt_dev_db->t_codeset.c_codeset2))
    {
        _dev_db_reset_bmc_query_info(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx]));
        /* reset the query info slot*/
        return DEV_DBR_FAIL;
    }
#endif

     /* if codeset get fail should also notify to the client for further deal with*/
     _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), TRUE);
     /* notify the data to the client*/
    _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));
#endif
    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_thread_query_codeset_with_brand
 *
 * Description: this fun will get query codeset list by the brand idx
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_thread_query_codeset_with_brand(DEV_DB_BMC_QUERY_T       t_bmc_query_info)
{
    DEV_DB_UTIL_T*           pt_dev_db          = &t_g_dev_db_util;
    BOOL                     b_is_dev_type_dul  = t_bmc_query_info.b_is_dual;
    INT32                    i4_ret;
    INT32                    i4_brd_idx1 = -1;
    INT32                    i4_brd_idx2 = -1;
    BOOL                     b_is_codeset1_valid = FALSE;
    BOOL                     b_is_codeset2_valid = FALSE;
    INT32                    i4_codeset_list1_num = 0;
    INT32                    i4_codeset_list2_num = 0;

    a_dev_db_lock();

    /* clean the codeset list info*/
    _dev_db_clean_codeset_list_info();

    if (b_is_dev_type_dul)
    {
        /* local1 codeset query*/
       i4_ret = _dev_db_local_dual_query_brd_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                             t_bmc_query_info.s_brd_name,
                                             &i4_brd_idx1);

        if (DEV_DBR_OK == i4_ret)
        {
        #ifdef APP_PORTING
            i4_codeset_list1_num = c_get_codesets_with_brand(&(pt_dev_db->t_codeset_list.t_codeset_list1.p_list),
                                   i4_brd_idx1);
        #endif

            if(i4_codeset_list1_num <= 0 || pt_dev_db->t_codeset_list.t_codeset_list1.p_list == NULL)
            {
                DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset_with_brand(c_codeset_list1) fail!\n"));

                pt_dev_db->t_codeset_list.t_codeset_list1.i4_length = 0;
                pt_dev_db->t_codeset_list.t_codeset_list1.p_list = NULL;

                b_is_codeset1_valid = FALSE;
            }
            else
            {
                pt_dev_db->t_codeset_list.t_codeset_list1.i4_length = i4_codeset_list1_num;
                b_is_codeset1_valid = TRUE;
            }


        }
        else
        {
            b_is_codeset1_valid = FALSE;
        }

        if (FALSE == b_is_codeset1_valid)
        {
            /* online1 codeset query*/
            i4_ret = _dev_db_online_dual_query_brd_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                                  t_bmc_query_info.s_brd_name,
                                                  &i4_brd_idx1);
            /* query the online codeset list*/
#ifdef APP_PORTING
            if (DEV_DBR_OK == i4_ret)
            {
                i4_ret = c_get_codesets_with_brand(&(pt_dev_db->t_codeset_list.t_codeset_model_list1.p_list),
                                       i4_brd_idx1);

                if(i4_codeset_list1_num <= 0 || pt_dev_db->t_codeset_list.t_codeset_model_list1.p_list == NULL)
                {
                    DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset_with_brand(c_codeset_list1) fail!\n"));

                    pt_dev_db->t_codeset_list.t_codeset_model_list1.i4_length = 0;
                    pt_dev_db->t_codeset_list.t_codeset_model_list1.p_list = NULL;

                    b_is_codeset1_valid = FALSE;
                }
                else
                {
                    pt_dev_db->t_codeset_list.t_codeset_model_list1.i4_length = i4_codeset_list1_num;
                    b_is_codeset1_valid = TRUE;
                }
            }
            else
            {
                b_is_codeset1_valid = FALSE;
            }
#endif
        }

        /* local2 codeset query*/
        i4_ret = _dev_db_local_dual_query_brd_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                                              t_bmc_query_info.s_brd_name,
                                              &i4_brd_idx2);

        if (DEV_DBR_OK == i4_ret)
        {
        #ifdef APP_PORTING
            i4_codeset_list2_num = c_get_codesets_with_brand(&(pt_dev_db->t_codeset_list.t_codeset_list2.p_list),
                                   i4_brd_idx2);
        #endif
            if(i4_codeset_list2_num <= 0 || pt_dev_db->t_codeset_list.t_codeset_list2.p_list == NULL)
            {
                DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset_with_brand(c_codeset_list1) fail!\n"));

                pt_dev_db->t_codeset_list.t_codeset_list2.i4_length = 0;
                pt_dev_db->t_codeset_list.t_codeset_list2.p_list = NULL;

                b_is_codeset1_valid = FALSE;
            }
            else
            {
                pt_dev_db->t_codeset_list.t_codeset_list2.i4_length = i4_codeset_list2_num;
                b_is_codeset1_valid = TRUE;
            }

        }
        else
        {
            b_is_codeset2_valid = FALSE;
        }

        if (FALSE == b_is_codeset2_valid)
        {
            /* online2 codeset query*/
            i4_ret = _dev_db_online_dual_query_brd_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_devb_src_idx,
                                                  t_bmc_query_info.s_brd_name,
                                                  &i4_brd_idx2);
            /* query the online codeset list*/
#if 0
            if (DEV_DBR_OK == i4_ret)
            {
                i4_codeset_list2_num = c_online_get_codeset(&(pt_dev_db->t_codeset.c_codeset2),
                                       i4_brd_idx2);

                if ((NULL == pt_dev_db->t_codeset.c_codeset2)
                    || (0 != i4_ret))
                {
                    DBG_INFO(("[DEV_DB] _dev_db_thread_query_codeset(c_codeset2) fail, i4_ret[%d]!\n",i4_ret));
                    b_is_codeset2_valid = FALSE;
                }
                else
                {
                    b_is_codeset2_valid = TRUE;
                }
            }
            else
            {
                b_is_codeset2_valid = FALSE;
            }
#endif
       }

    }
    else
    {
         /* local1 codeset query*/
        i4_ret = _dev_db_local_dual_query_brd_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                              t_bmc_query_info.s_brd_name,
                                              &i4_brd_idx1);

         if (DEV_DBR_OK == i4_ret)
         {
         #ifdef APP_PORTING
             i4_codeset_list1_num = c_get_codesets_with_brand(&(pt_dev_db->t_codeset_list.t_codeset_list1.p_list),
                                    i4_brd_idx1);
         #endif

             if(i4_codeset_list1_num <= 0 || pt_dev_db->t_codeset_list.t_codeset_list1.p_list == NULL)
             {
                 DBG_ERROR(("[DEV_DB] _dev_db_thread_query_codeset_with_brand(c_codeset_list1) fail!\n"));

                 pt_dev_db->t_codeset_list.t_codeset_list1.i4_length = 0;
                 pt_dev_db->t_codeset_list.t_codeset_list1.p_list = NULL;

                 b_is_codeset1_valid = FALSE;
             }
             else
             {
                 pt_dev_db->t_codeset_list.t_codeset_list1.i4_length = i4_codeset_list1_num;
                 b_is_codeset1_valid = TRUE;
             }


         }
         else
         {
             b_is_codeset1_valid = FALSE;
         }

         if (FALSE == b_is_codeset1_valid)
         {
             /* online1 codeset query*/
             i4_ret = _dev_db_online_dual_query_brd_idx_by_tb(t_bmc_query_info.t_type_sel_info.i4_deva_src_idx,
                                                   t_bmc_query_info.s_brd_name,
                                                   &i4_brd_idx1);
#if 0
             if (DEV_DBR_OK == i4_ret)
             {
                 i4_ret = c_online_get_codeset(&(pt_dev_db->t_codeset.c_codeset1),
                                        i4_mdl_idx1);

                 if ((NULL == pt_dev_db->t_codeset.c_codeset1)
                     || (0 != i4_ret))
                 {
                     b_is_codeset1_valid = FALSE;
                 }
                 else
                 {
                     b_is_codeset1_valid = TRUE;
                 }
             }
             else
             {
                 b_is_codeset1_valid = FALSE;
             }
#endif
         }
    }

    a_dev_db_unlock();

     /* if codeset get fail should also notify to the client for further deal with*/
     _dev_db_set_bmc_flag_before_notify_to_client((&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])), TRUE);
     /* notify the data to the client*/
    _dev_db_notify_client_data_change((VOID*)(&(pt_dev_db->t_thread_query_info[t_bmc_query_info.ui4_task_idx])));

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _dev_db_reset_merge_data
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _dev_db_reset_merge_data(DEV_DB_BRMD_T* pt_array_brmd)
{
    UINT32          ui4_index = 0;
    for (ui4_index = 0; ui4_index < DEV_DB_DUL_OP_MAX; ui4_index ++)
    {
        c_memset(&(pt_array_brmd[ui4_index]),0,sizeof (DEV_DB_BRMD_T));
        pt_array_brmd[ui4_index].i4_local1_idx = -1;
        pt_array_brmd[ui4_index].i4_online1_idx = -1;

        pt_array_brmd[ui4_index].i4_local2_idx = -1;
        pt_array_brmd[ui4_index].i4_online2_idx = -1;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_reset_bmc_query_info
 *
 * Description: unregister a dev db notify callback which id is ui4_nfy_id
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32  _dev_db_reset_bmc_query_info(DEV_DB_BMC_QUERY_T*                pt_bmc_query_info)
{
    if (NULL == pt_bmc_query_info)
    {
        return DEV_DB_INV_ARG;
    }

    c_memset(pt_bmc_query_info,0,sizeof(DEV_DB_BMC_QUERY_T));

    /* reset brand query info about type----> idx*/
    pt_bmc_query_info->t_type_sel_info.i4_deva_src_idx = -1;
    pt_bmc_query_info->t_type_sel_info.i4_devb_src_idx = -1;

    /* reset model query info about type and brand ---> idx*/
    pt_bmc_query_info->t_brd_sel_info.i4_local1_idx = -1;
    pt_bmc_query_info->t_brd_sel_info.i4_online1_idx = -1;
    pt_bmc_query_info->t_brd_sel_info.i4_local2_idx = -1;
    pt_bmc_query_info->t_brd_sel_info.i4_online2_idx = -1;


    /* reset model query info about type and brand ---> idx*/
    pt_bmc_query_info->t_mdl_sel_info.i4_local1_idx = -1;
    pt_bmc_query_info->t_mdl_sel_info.i4_online1_idx = -1;
    pt_bmc_query_info->t_mdl_sel_info.i4_local2_idx = -1;
    pt_bmc_query_info->t_mdl_sel_info.i4_online2_idx = -1;


    pt_bmc_query_info->e_buff_status = DEV_DB_QUERY_BUFF_STATUS_NONE;
    pt_bmc_query_info->ui4_task_idx = 0;
    pt_bmc_query_info->ui4_notify_count = 0;
    pt_bmc_query_info->ui4_query_idx = 0;
    pt_bmc_query_info->b_is_to_clean = FALSE;

#ifdef APP_UEI_SPINNER_SUPPORT
	pt_bmc_query_info->b_is_brd_online_query_start = FALSE;
	pt_bmc_query_info->b_is_brd_online_query_complete = FALSE;
#endif

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_bm_info_sort
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _dev_db_bm_info_sort(DEV_DB_BM_T* t_dev_bm_info,UINT32 ui4_num)
{
    UINT32      ui4_ret1 = 0;
    UINT32      ui4_ret2 = 0;
    UINT32      ui4_ret3 = 0;
    DEV_DB_BM_T t_dev_db_info_change ;

    for (ui4_ret1 = 0; ui4_ret1 < ui4_num - 1; ui4_ret1 ++)
    {
        ui4_ret3 = ui4_ret1;

        for (ui4_ret2 = ui4_ret1 + 1; ui4_ret2 < ui4_num; ui4_ret2++)
        {
            if (c_strcasecmp(t_dev_bm_info[ui4_ret3].s_src_name,t_dev_bm_info[ui4_ret2].s_src_name) > 0)
            {
                ui4_ret3 = ui4_ret2;
            }
        }

        if (ui4_ret3 != ui4_ret1)
        {
            c_memcpy(&t_dev_db_info_change,&t_dev_bm_info[ui4_ret1],sizeof (DEV_DB_BM_T));
            c_memcpy(&t_dev_bm_info[ui4_ret1],&t_dev_bm_info[ui4_ret3],sizeof (DEV_DB_BM_T));
            c_memcpy(&t_dev_bm_info[ui4_ret3],&t_dev_db_info_change,sizeof (DEV_DB_BM_T));
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_merge_sort
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_merge_sort(
    DEV_DB_BRMD_T* pt_array_brmd,
    DEV_DB_BM_T* t_dev_bm_info,
    UINT32* pui4_src_num1,
    UINT32 ui4_src_num2,
    DEV_DB_MERGE_TYPE_T  e_merge_type)
{
    UINT32 src_idx1 = 0;
    UINT32 src_idx2 = 0;
    UINT32 des_idx  = 0;
    UINT32 ui4_idx  = 0;
    UINT32 ui4_src_num1 = 0;
    INT32  i4_ret;

    DEV_DB_BRMD_T      t_brmd[DEV_DB_DUL_OP_MAX];

    _dev_db_reset_merge_data(t_brmd);

    if ((0 == ui4_src_num2)
        || (NULL == pt_array_brmd)
        || (NULL == pui4_src_num1))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun _dev_db_merge_sort() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((DEV_DB_MGE_LOCAL_A != e_merge_type)
        &&(DEV_DB_MGE_LOCAL_B != e_merge_type)
        &&(DEV_DB_MGE_ONLINE_A != e_merge_type)
        &&(DEV_DB_MGE_ONLINE_B != e_merge_type))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun _dev_db_merge_sort() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    if (0 == *pui4_src_num1)
    {
        /* as the glob is zoro, and here just copy the data to the corresposding record*/
        for (ui4_idx = 0; ui4_idx < ui4_src_num2; ui4_idx ++)
        {
            if (ui4_idx >= DEV_DB_DUL_OP_MAX)
            {
                DBG_ERROR(("[DEV_DB] the data of the merge info will be over flow! and the limit is [512] !!\n"));
                return DEV_DBR_FAIL;
            }

            c_strncpy(
                pt_array_brmd[ui4_idx].s_src_name,
                t_dev_bm_info[ui4_idx].s_src_name,
                DEV_DB_NAME_LEN_MAX);

            /* here just copy the data of src_array2 according to the e_merge_type*/
            switch (e_merge_type)
            {
                case DEV_DB_MGE_LOCAL_A:
                    pt_array_brmd[ui4_idx].i4_local1_idx  = t_dev_bm_info[ui4_idx].i4_idx;
                    break;
                case DEV_DB_MGE_LOCAL_B:
                    pt_array_brmd[ui4_idx].i4_local2_idx  = t_dev_bm_info[ui4_idx].i4_idx;
                    break;
                case DEV_DB_MGE_ONLINE_A:
                    pt_array_brmd[ui4_idx].i4_online1_idx = t_dev_bm_info[ui4_idx].i4_idx;
                    break;
                case DEV_DB_MGE_ONLINE_B:
                    pt_array_brmd[ui4_idx].i4_online2_idx = t_dev_bm_info[ui4_idx].i4_idx;
                    break;
                default:
                    break;
            }
        }

        *pui4_src_num1 = ui4_src_num2;
        return DEV_DBR_OK;
    }

    /**tmp the copy the data of pt array brand*/
    for (ui4_idx = 0; ui4_idx < *pui4_src_num1; ui4_idx ++)
    {
        c_memcpy(&(t_brmd[ui4_idx]),
                 &(pt_array_brmd[ui4_idx]),
                 sizeof(DEV_DB_BRMD_T));
    }

    /* record the before num to num1*/
    ui4_src_num1 = *pui4_src_num1;

    /*init the pt_array_brand*/
    _dev_db_reset_merge_data(pt_array_brmd);

    while((src_idx1 < ui4_src_num1)&&(src_idx2 < ui4_src_num2))
    {
        i4_ret=c_strcasecmp(t_brmd[src_idx1].s_src_name,t_dev_bm_info[src_idx2].s_src_name);

        if (des_idx >= DEV_DB_DUL_OP_MAX)
        {
            DBG_ERROR(("[DEV_DB] the data of the merge info will be over flow! and the limit is [512] !!\n"));

            return DEV_DBR_FAIL;
        }

        if(i4_ret<0)  /*merge string is only from src_array*/
        {
            c_memcpy(&(pt_array_brmd[des_idx]),
                 &(t_brmd[src_idx1]),
                 sizeof(DEV_DB_BRMD_T));
            src_idx1++;
            des_idx++;
        }
        else if(0 == i4_ret)  /*merge string is from src_array and des_array*/
        {
            c_memcpy(&(pt_array_brmd[des_idx]),
                 &(t_brmd[src_idx1]),
                 sizeof(DEV_DB_BRMD_T));
            switch (e_merge_type)
            {
                case DEV_DB_MGE_LOCAL_A:
                    pt_array_brmd[des_idx].i4_local1_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                case DEV_DB_MGE_LOCAL_B:
                    pt_array_brmd[des_idx].i4_local2_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                case DEV_DB_MGE_ONLINE_A:
                    pt_array_brmd[des_idx].i4_online1_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                case DEV_DB_MGE_ONLINE_B:
                    pt_array_brmd[des_idx].i4_online2_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                default:
                    break;
            }
            src_idx1++;
            src_idx2++;
            des_idx++;
        }
        else    /*merge string is only from des_array*/
        {
            c_strncpy(
                pt_array_brmd[des_idx].s_src_name,
                t_dev_bm_info[src_idx2].s_src_name,
                DEV_DB_NAME_LEN_MAX);

            switch (e_merge_type)
            {
                case DEV_DB_MGE_LOCAL_A:
                    pt_array_brmd[des_idx].i4_local1_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                case DEV_DB_MGE_LOCAL_B:
                    pt_array_brmd[des_idx].i4_local2_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                case DEV_DB_MGE_ONLINE_A:
                    pt_array_brmd[des_idx].i4_online1_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                case DEV_DB_MGE_ONLINE_B:
                    pt_array_brmd[des_idx].i4_online2_idx = t_dev_bm_info[src_idx2].i4_idx;
                    break;
                default:
                    break;
            }
            src_idx2++;
            des_idx++;
        }
    }

    while(src_idx1 < ui4_src_num1)
    {

        if (ui4_idx >= DEV_DB_DUL_OP_MAX)
        {
            DBG_ERROR(("[DEV_DB] the data of the merge info will be over flow! and the limit is [512] !!\n"));

            return DEV_DBR_FAIL;
        }
        c_memcpy(&(pt_array_brmd[des_idx]),
             &(t_brmd[src_idx1]),
             sizeof(DEV_DB_BRMD_T));
        src_idx1++;
        des_idx++;
    }

    while(src_idx2 < ui4_src_num2)
    {
        if (des_idx >= DEV_DB_DUL_OP_MAX)
        {
            DBG_ERROR(("[DEV_DB] the data of the merge info will be over flow! and the limit is [512] !!\n"));

            return DEV_DBR_FAIL;
        }
        c_strncpy(
            pt_array_brmd[des_idx].s_src_name,
            t_dev_bm_info[src_idx2].s_src_name,
            DEV_DB_NAME_LEN_MAX);

        switch (e_merge_type)
        {
            case DEV_DB_MGE_LOCAL_A:
                pt_array_brmd[des_idx].i4_local1_idx = t_dev_bm_info[src_idx2].i4_idx;
                break;
            case DEV_DB_MGE_LOCAL_B:
                pt_array_brmd[des_idx].i4_local2_idx = t_dev_bm_info[src_idx2].i4_idx;
                break;
            case DEV_DB_MGE_ONLINE_A:
                pt_array_brmd[des_idx].i4_online1_idx = t_dev_bm_info[src_idx2].i4_idx;
                break;
            case DEV_DB_MGE_ONLINE_B:
                pt_array_brmd[des_idx].i4_online2_idx = t_dev_bm_info[src_idx2].i4_idx;
                break;
            default:
                break;
        }
        src_idx2++;
        des_idx++;
    }

    *pui4_src_num1 = des_idx;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _dev_db_get_mlm_lang_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *----------------------------------------------------------------------------*/
static UINT8 _dev_db_get_mlm_lang_id(
                    VOID
                    )
{
    ISO_639_LANG_T s639_lang;
    UINT8          ui1_lang_id = 0;
    INT32          i4_ret;

    ui1_lang_id = MLM_DEVDB_LANG_ENG;

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if (i4_ret == APP_CFGR_OK)
    {
#ifdef APP_MLM_S639_TO_LANGIDX_SUPPORT
        ui1_lang_id = (UINT8)mlm_devdb_s639_to_langidx (s639_lang);
#else
        if (c_strcmp (s639_lang, s639_app_cfg_lang_eng) == 0) /* English */
        {
            ui1_lang_id = MLM_DEVDB_LANG_ENG;
        }
        else if ((c_strcmp (s639_lang, s639_app_cfg_lang_esl) == 0) || /* Spanish */
                 (c_strcmp (s639_lang, s639_app_cfg_lang_spa) == 0))
        {
            ui1_lang_id = MLM_DEVDB_LANG_SPA;
        }
        else if ((c_strcmp (s639_lang, s639_app_cfg_lang_fra) == 0) || /* French */
                 (c_strcmp (s639_lang, s639_app_cfg_lang_fre) == 0))
        {
            ui1_lang_id = MLM_DEVDB_LANG_FRE;
        }
#endif /* APP_MLM_S639_TO_LANGIDX_SUPPORT */
    }

    return ui1_lang_id;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _dev_db_cancel_bmc_query
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *----------------------------------------------------------------------------*/
static INT32 _dev_db_cancel_bmc_query(
                    VOID
                    )
{
    INT32 i4_ret = DEV_DB_INV_ARG;
    #ifdef APP_PORTING
    DBG_INFO(("\n[DEV_DB] _dev_db_cancel_bmc_query\n"));
    i4_ret = c_cancel_online_query();
    #endif
    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _dev_db_upload_codeset_by_alp_and_num_string
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *----------------------------------------------------------------------------*/
static INT32 _dev_db_upload_codeset_by_alp_and_num_string(
                                                                CHAR*   s_alp_arr,
                                                                UINT32  ui4_alp_arr_num,
                                                                CHAR*   s_codeset,
                                                                UINT32  ui4_codeset_size
                                                                )
{
    INT32                    i4_ret = DEV_DBR_FAIL;

    /* codeset must be five letters ,1(alphabet)+4(num)*/
    CHAR                     s_tmp_codeset[6];
    UINT32                   ui4_idx;
    UINT32                   ui4_idx_alp;

    if ((NULL == s_alp_arr)
        ||(NULL == s_codeset)
        ||(ui4_codeset_size < DEV_DB_CODESET_LEN_MAX))
    {
        DBG_ERROR(("\n[DEV_DB]_dev_db_upload_codeset_by_alp_and_num_string(parameter invalid)\n"));

        /* here should return DEV_DBR_FAIL*/
        return i4_ret;
    }

    for (ui4_idx_alp = 0; ui4_idx_alp < ui4_alp_arr_num; ui4_idx_alp ++)
    {
        c_memset(s_tmp_codeset, 0, sizeof(s_tmp_codeset));
        s_tmp_codeset[0] = s_alp_arr[ui4_idx_alp];

        /* the num char of the codeset should be 4*/

        for (ui4_idx = 0; ui4_idx < DEV_DB_CODESET_CHAR_NUM_LEN; ui4_idx++)
        {
            s_tmp_codeset[ui4_idx + 1] = s_codeset[ui4_idx];
        }
        #ifdef APP_PORTING
        i4_ret = c_upload_codeset(s_tmp_codeset);
        #endif

        /* the return value zero for the fun: c_upload_codeset()
               *indicate the codeset upload successful
               */
        if (0 == i4_ret)
        {
            i4_ret = DEV_DBR_OK;

            for (ui4_idx = 0; ui4_idx < DEV_DB_CODESET_LEN_MAX; ui4_idx++)
            {
                s_codeset[ui4_idx] = s_tmp_codeset[ui4_idx];
            }

            /* as the codeset upload successful, and do
                     *need to check for the next one
                     */
            break;
        }
        else
        {
            i4_ret = DEV_DBR_FAIL;
        }
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:a_dev_db_resort_bm_list_with_str
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_resort_bm_list_with_str(
                        DEV_DB_BRMD_T* t_bm_list,
                        UINT32         ui4_num,
                        CHAR*          ps_dst_str)
{
    DEV_DB_BRMD_T   t_bm_list_temp;
    INT32           ui4_idx_mark = -1;
    UINT16          ui2_i = 0;

    c_memset(&t_bm_list_temp,0,sizeof (DEV_DB_BRMD_T));
    t_bm_list_temp.i4_local1_idx  = -1;
    t_bm_list_temp.i4_online1_idx = -1;
    t_bm_list_temp.i4_local2_idx  = -1;
    t_bm_list_temp.i4_online2_idx = -1;

    for(ui2_i = 0; ui2_i < ui4_num; ui2_i++)
    {
        if(c_strcasecmp(t_bm_list[ui2_i].s_src_name, ps_dst_str)==0)
        {
            c_memcpy(&t_bm_list_temp,&t_bm_list[ui2_i],sizeof (DEV_DB_BM_T));
            ui4_idx_mark = ui2_i;
            break;
        }
    }

    if ((ui2_i >= ui4_num)
        || (-1 == ui4_idx_mark))
    {
        return DEV_DBR_OK;
    }

    for(ui2_i = ui4_idx_mark; ui2_i > 0; ui2_i--)
    {
        c_memcpy(&t_bm_list[ui2_i],&t_bm_list[ui2_i-1],sizeof (DEV_DB_BM_T));
    }

    c_memcpy(&t_bm_list[0],&t_bm_list_temp,sizeof (DEV_DB_BM_T));

    return DEV_DBR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:a_dev_db_lock
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_lock(VOID)
{
    DEV_DB_UTIL_T* pt_dev_db = &t_g_dev_db_util;
    return c_sema_lock(pt_dev_db->h_sema_mtx, X_SEMA_OPTION_WAIT) == OSR_OK ?
           DEV_DBR_OK :
           DEV_DBR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_unlock
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_unlock(VOID)
{

    DEV_DB_UTIL_T* pt_dev_db = &t_g_dev_db_util;
    return c_sema_unlock(pt_dev_db->h_sema_mtx) == OSR_OK ?
           DEV_DBR_OK :
           DEV_DBR_FAIL;
}


/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _dev_db_set_lock
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_dev_db_check_lock_info( DEV_DB_LOCK_CHECK_COND_T e_check_cond, BOOL* pb_is_lock )
{
    DEV_DB_LOCK_T        t_dev_db_lock;
    DEV_DB_LOCK_STATUS_T e_lock_status = DEV_DB_LOCK_STATUS_NONE;
    BOOL                 b_is_lock = FALSE;
    INT32                i4_ret;
    c_memset(&(t_dev_db_lock),0,sizeof(DEV_DB_LOCK_T));
#ifdef APP_UPG_SUPPORT
    if (FALSE == (nav_updater_is_3rd_rw_part_ready()))
    {
        DBG_ERROR(("[DEV_DB]The partition 3rd_rw is not ready !!\n"));
        return DEV_DBR_FAIL;
    }
#endif
    i4_ret = _dev_db_get_lock_info( &t_dev_db_lock );

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Get the lock info fail !!\n"));
        return DEV_DBR_FAIL;
    }

    i4_ret = _dev_db_get_lock_status( t_dev_db_lock, &e_lock_status );


    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB]Get the lock status fail !!\n"));
        return DEV_DBR_FAIL;
    }

    switch (e_lock_status)
    {
        case DEV_DB_LOCK_STATUS_NORMAL:
            {
                if (DEV_DB_LOCK_CHECK_COND_CODESET == e_check_cond)
                {
                    BOOL b_is_timeout = FALSE;
                    i4_ret = _dev_db_get_unlock_timeout( &b_is_timeout );

                    if (DEV_DBR_OK != i4_ret)
                    {
                        DBG_ERROR(("[DEV_DB]Get unlock timeout fail !!\n"));
                        return DEV_DBR_FAIL;
                    }

                    if (b_is_timeout)
                    {
                        i4_ret = _dev_db_set_unlock();

                        if (DEV_DBR_OK != i4_ret)
                        {
                            DBG_ERROR(("[DEV_DB]reSet lock info fail !!\n"));
                            return DEV_DBR_FAIL;
                        }

                        DBG_INFO(("[DEV_DB]reset lock info successful !!\n"));
                    }

                    i4_ret = _dev_db_update_lock_cnt( TRUE );

                    if (DEV_DBR_OK != i4_ret)
                    {
                        DBG_ERROR(("[DEV_DB]Update the lock cnt fail !!\n"));
                        return DEV_DBR_FAIL;
                    }
                }
            }
            break;
        case DEV_DB_LOCK_STATUS_NORMAL_EDGE:
            {
                if (DEV_DB_LOCK_CHECK_COND_CODESET == e_check_cond)
                {
                    BOOL b_is_timeout = FALSE;
                    i4_ret = _dev_db_get_unlock_timeout( &b_is_timeout );

                    if (DEV_DBR_OK != i4_ret)
                    {
                        DBG_ERROR(("[DEV_DB]Get unlock timeout fail !!\n"));
                        return DEV_DBR_FAIL;
                    }

                    if (b_is_timeout)
                    {
                        i4_ret = _dev_db_set_unlock();

                        if (DEV_DBR_OK != i4_ret)
                        {
                            DBG_ERROR(("[DEV_DB]reSet lock info fail !!\n"));
                            return DEV_DBR_FAIL;
                        }

                        DBG_INFO(("[DEV_DB]reset lock info successful !!\n"));


                        i4_ret = _dev_db_update_lock_cnt( TRUE );

                        if (DEV_DBR_OK != i4_ret)
                        {
                            DBG_ERROR(("[DEV_DB]Update the lock cnt fail !!\n"));
                            return DEV_DBR_FAIL;
                        }
                    }
                    else
                    {
                        i4_ret = _dev_db_set_lock();

                        if (DEV_DBR_OK != i4_ret)
                        {
                            DBG_ERROR(("[DEV_DB]set lock fail !!\n"));
                            return DEV_DBR_FAIL;
                        }

                        DBG_INFO(("[DEV_DB]set lock successful !!\n"));

                        b_is_lock = TRUE;
                    }
                }
            }
            break;
        case DEV_DB_LOCK_STATUS_LOCK:
            {
                if (DEV_DB_LOCK_CHECK_COND_NONE == e_check_cond)
                {
                    BOOL b_is_timeout = FALSE;
                    i4_ret = _dev_db_get_lock_timeout( &b_is_timeout );

                    if (DEV_DBR_OK != i4_ret)
                    {
                        DBG_ERROR(("[DEV_DB]Get lock timeout fail !!\n"));
                        return DEV_DBR_FAIL;
                    }

                    if (b_is_timeout)
                    {
                        i4_ret = _dev_db_set_unlock();

                        if (DEV_DBR_OK != i4_ret)
                        {
                            DBG_ERROR(("[DEV_DB]Set unlock fail !!\n"));
                            return DEV_DBR_FAIL;
                        }

                        DBG_INFO(("[DEV_DB]set unlock successful !!\n"));
                    }
                    else
                    {
                        b_is_lock = TRUE;
                    }
                }
            }
            break;
        default:
            break;
    }

    *pb_is_lock = b_is_lock;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_is_sys_time_ready
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL a_dev_db_is_sys_time_ready( VOID )
{
    time_t t_current_time = 0;
    t_current_time = time (NULL);

    if (t_current_time < ((time_t)(365 * 24 * 60 * 60)))  /* should one year sec to check the time ready*/
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _dev_db_dev_type_mapping_init()
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _dev_db_dev_type_mapping_init( VOID )
{
    DEV_DB_UTIL_T*        pt_dev_db    = &t_g_dev_db_util;

	/*blu-ray*/
	c_strncpy(pt_dev_db->t_type_mapping.blu_ray[0],DEV_DB_TYPE_VIEW_BLU_RAY_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.blu_ray[1],DEV_DB_TYPE_VIEW_BLU_RAY_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*cable box*/
	c_strncpy(pt_dev_db->t_type_mapping.cable_box[0],DEV_DB_TYPE_VIEW_CABLE_BOX_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.cable_box[1],DEV_DB_TYPE_VIEW_CABLE_BOX_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*Computer*/
	c_strncpy(pt_dev_db->t_type_mapping.computer[0],DEV_DB_TYPE_VIEW_COMPUTER_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.computer[1],DEV_DB_TYPE_VIEW_COMPUTER_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*dvd*/
	c_strncpy(pt_dev_db->t_type_mapping.dvd[0],DEV_DB_TYPE_VIEW_DVD_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.dvd[1],DEV_DB_TYPE_VIEW_DVD_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*dvr*/
	c_strncpy(pt_dev_db->t_type_mapping.dvr[0],DEV_DB_TYPE_VIEW_DVR_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.dvr[1],DEV_DB_TYPE_VIEW_DVR_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*game*/
	c_strncpy(pt_dev_db->t_type_mapping.game[0],DEV_DB_TYPE_VIEW_GAME_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.game[1],DEV_DB_TYPE_VIEW_GAME_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*satellite*/
	c_strncpy(pt_dev_db->t_type_mapping.satellite[0],DEV_DB_TYPE_VIEW_SATELLITE_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.satellite[1],DEV_DB_TYPE_VIEW_SATELLITE_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*vcr*/
	c_strncpy(pt_dev_db->t_type_mapping.vcr[0],DEV_DB_TYPE_VIEW_VCR_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.vcr[1],DEV_DB_TYPE_VIEW_VCR_NAME_EX,DEV_DB_NAME_LEN_MAX);

	/*audio*/
	c_strncpy(pt_dev_db->t_type_mapping.audio[0],DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.audio[1],DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME_EX,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.audio[2],DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME_EX1,DEV_DB_NAME_LEN_MAX);

	/*sound bar*/
	c_strncpy(pt_dev_db->t_type_mapping.sound_bar[0],DEV_DB_TYPE_VIEW_SOUND_BAR_NAME,DEV_DB_NAME_LEN_MAX);
	c_strncpy(pt_dev_db->t_type_mapping.sound_bar[1],DEV_DB_TYPE_VIEW_SOUND_BAR_NAME_EX,DEV_DB_NAME_LEN_MAX);

    return DEV_DBR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:a_dev_db_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_init(VOID)
{
    INT32           i4_ret;
    DEV_DB_UTIL_T*  pt_dev_db = &t_g_dev_db_util;

    if (pt_dev_db->b_is_dev_db_init == TRUE)
    {
        DBG_ERROR(("[DEV_DB] the dev db have alread inited!\n"));
        return DEV_DBR_INITED;
    }

    c_memset(pt_dev_db,0,sizeof (DEV_DB_UTIL_T));

    /* Init semaphore (mutex) */
    i4_ret = c_sema_create(&pt_dev_db->h_sema_mtx,
                           X_SEMA_TYPE_MUTEX,
                           X_SEMA_STATE_UNLOCK);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR(("[DEV_DB] the dev db sema init fail!\n"));
        return DEV_DBR_FAIL;
    }

    /*init the cond mutex*/
    pthread_cond_init( &(pt_dev_db->cond), NULL );
    pthread_mutex_init( &(pt_dev_db->mutex), NULL );

    /* reset the type/brand/model info*/
    _dev_db_reset_type_info();
    _dev_db_reset_brand_info();
    _dev_db_reset_model_info();
    _dev_db_reset_code_info();
    _dev_db_reset_codeset_list_info();
    _dev_db_reset_thread_query_info();
#ifdef APP_PORTING
    /* init related sema for local & online db query */
    c_init_db_query_sema();
#endif
    /* create the dev db bmc thread*/
    i4_ret = _dev_db_bmc_query_thread_create();

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_bmc_query_thread_create() fail!\n"));
        return i4_ret;
    }

    /* init the dev mapping type*/
    _dev_db_dev_type_mapping_init();
    /* set the flag to indecate this model have been init*/
    pt_dev_db->b_is_dev_db_init = TRUE;

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name:a_dev_db_get_dev_type
 *
 * Description: before use this fun to get the dev type list, should use the dev type
 *                  update fun to update the dev list
 *
 * Inputs:    pt_dev_info ---->should be a arr buff for dev type list and will get the value
 *                                         for the current dev list.
 *               pui4_dev_type_num----> will get the value for current dev type num
 *
 * Outputs:   return DEV_DBR_OK the get value of the dev type is valid otherwist will be invalid
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_get_dev_type(DEV_DB_TYPE_T* pt_dev_info,
                                   UINT32* pui4_dev_type_num)
{
    DEV_DB_UTIL_T* pt_dev_db  = &t_g_dev_db_util;
    UINT32         ui4_idx    = 0;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    /* check the parameter of this function*/
    if ((NULL == pt_dev_info)
        || (NULL == pui4_dev_type_num))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_get_dev_type() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    a_dev_db_lock();

    /* check the dev arr is valid or not*/
    if (0 == pt_dev_db->ui4_dev_type_num)
    {
        DBG_ERROR(("[DEV_DB] there is no dev type in the dev arr, please update the dev type arr first!\n"));
        a_dev_db_unlock();
        return DEV_DBR_FAIL;
    }

    /* copy the dev type arr to the client part from the glob arr for dev type in dev db*/
    for (ui4_idx = 0; ui4_idx < pt_dev_db->ui4_dev_type_num; ui4_idx ++)
    {
        c_memcpy(&(pt_dev_info[ui4_idx]),
                 &(pt_dev_db->t_dev_type[ui4_idx]),
                 sizeof(DEV_DB_TYPE_T));
    }

    a_dev_db_unlock();

    /* set the dev type num to the client*/
    *pui4_dev_type_num = pt_dev_db->ui4_dev_type_num;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:a_dev_db_is_predef_name
 *
 * Description: this function will get the name of mlm-index.
 *
 * Inputs:      string for any language(eng/spa/fre)
 *
 * Outputs:     return mlm-index, 0xFFFF indicated that it not find the mlm-index
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
UINT16 a_dev_db_get_predef_name_mlm_idx(CHAR *p_name)
{
    UINT16  ui2_mlm_idx = 0xFFFF;
    UINT16  ui2_i = 0;
    UINT16  ui2_j = 0;
    UINT16  ui2_num = 0;
    UTF16_T w2s_name[DEV_DB_NAME_LEN_MAX+1];

    if (NULL == p_name || c_strlen(p_name) == 0)
    {
        return ui2_mlm_idx;
    }

    c_memset(w2s_name, 0, sizeof(w2s_name));
    c_uc_ps_to_w2s(p_name, w2s_name, DEV_DB_NAME_LEN_MAX);

    ui2_num = sizeof(aui2_g_predef_lbls)/sizeof(aui2_g_predef_lbls[0]);

    for (ui2_i = MLM_DEVDB_LANG_ENG; ui2_i <= MLM_DEVDB_LANG_SPA; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < ui2_num; ui2_j++)
        {
            if (c_uc_w2s_strcmp(w2s_name, MLM_DEVDB_TEXT(ui2_i, aui2_g_predef_lbls[ui2_j])) == 0)
            {
                ui2_mlm_idx = aui2_g_predef_lbls[ui2_j];
                break;
            }
        }

        if (ui2_mlm_idx != 0xFFFF)
        {
            break;
        }
    }

    return ui2_mlm_idx;
}

/*-----------------------------------------------------------------------------
 * Name:a_dev_db_dev_type_name_mapping()
 *
 * Description: this fun will support the different dev type spelling for different code version
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:		return DEV_DBR_OK the get value of the dev type is valid otherwist will be invalid
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_dev_type_name_mapping(CHAR* s_type_name)
{
    DEV_DB_UTIL_T* pt_dev_db  = &t_g_dev_db_util;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.blu_ray[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.blu_ray[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.blu_ray[0],DEV_DB_NAME_LEN_MAX);
    }
    else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.cable_box[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.cable_box[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.cable_box[0],DEV_DB_NAME_LEN_MAX);
    }
    else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.computer[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.computer[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.computer[0],DEV_DB_NAME_LEN_MAX);
    }
	else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.dvd[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.dvd[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.dvd[0],DEV_DB_NAME_LEN_MAX);
    }
    else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.dvr[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.dvr[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.dvr[0],DEV_DB_NAME_LEN_MAX);
    }
	else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.game[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.game[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.game[0],DEV_DB_NAME_LEN_MAX);
    }
    else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.satellite[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.satellite[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.satellite[0],DEV_DB_NAME_LEN_MAX);
    }
	else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.vcr[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.vcr[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.vcr[0],DEV_DB_NAME_LEN_MAX);
    }
    else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.audio[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.audio[1]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.audio[2]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.audio[0],DEV_DB_NAME_LEN_MAX);
    }
	else if((c_strcmp(s_type_name, pt_dev_db->t_type_mapping.sound_bar[0]) == 0)||
		(c_strcmp(s_type_name, pt_dev_db->t_type_mapping.sound_bar[1]) == 0))
    {
        c_strncpy(s_type_name,pt_dev_db->t_type_mapping.sound_bar[0],DEV_DB_NAME_LEN_MAX);
    }
    else
    {
        DBG_ERROR(("[####DEV_DB%s(%d)] The DeviceType do not support!\n",__FUNCTION__,__LINE__));
        return DEV_DBR_FAIL;
    }

    return DEV_DBR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:a_dev_db_dev_type_name_ps_to_w2s
 *
 * Description: this fun will support the mul lan for dev type
 *
 * Inputs:
 *
 * Outputs:   return DEV_DBR_OK the get value of the dev type is valid otherwist will be invalid
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_dev_type_name_ps_to_w2s(CHAR* s_type_name,
                                   UTF16_T** ppw2s_type_msg)
{
    DEV_DB_UTIL_T* pt_dev_db  = &t_g_dev_db_util;
    UINT16    ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_BLU_RAY;
	INT32	  i4_ret = DEV_DBR_OK;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

	i4_ret = a_dev_db_dev_type_name_mapping(s_type_name);
	if(i4_ret != DEV_DBR_OK)
	{
		DBG_ERROR(("[####DEV_DB%s(%d)]dev type mapping fail!\n",__FUNCTION__,__LINE__));
	}
    if ((ui2_dev_type_mlm_idx = a_dev_db_get_predef_name_mlm_idx(s_type_name)) == 0xFFFF)
    {
        DBG_ERROR(("[DEV_DB] The DeviceType do not support!\n"));
        return DEV_DBR_FAIL;
    }

#if 0
    if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_BLU_RAY_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_BLU_RAY;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_CABLE_BOX_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_CABLE_BOX;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_COMPUTER_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_COMPUTER;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_DVD_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_DVD;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_DVR_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_DVR;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_GAME_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_GAME;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_SATELLITE_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_SATELLITE;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_VCR_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_VCR;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_AVR_AMP_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_AVR_AMPLIFER;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_VIEW_SOUND_BAR_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_SOUND_BAR;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_AVR_AUDIO_RECEIVER;
    }
    else if(c_strcmp(s_type_name, DEV_DB_TYPE_AMPLIFIER_NAME) == 0)
    {
        ui2_dev_type_mlm_idx = MLM_DEVDB_KEY_DEV_TYPE_AVR_AMP;
    }
    else
    {
        DBG_INFO(("[DEV_DB] The DeviceType do not support!\n");
        return DEV_DBR_FAIL;
    }
#endif

    *ppw2s_type_msg = MLM_DEVDB_TEXT(_dev_db_get_mlm_lang_id(),(UINT16)ui2_dev_type_mlm_idx);

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name:a_dev_db_get_dev_type_category
 *
 * Description: this funtion just used to get the dev type category
 *
 * Inputs:
 * Outputs:  pe_dev_type_category get the current dev type category
 *
 * Returns: return DEV_DBR_OK the get value of the dev type is valid otherwist will be invalid
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_get_dev_type_category(DEV_DB_DEV_TYPE_CTGY_T*   pe_dev_type_category)
{
    DEV_DB_UTIL_T* pt_dev_db  = &t_g_dev_db_util;

    /** this function should not use the mutx lock, as may
          * block the call thread when the bmc thread is runing
          */

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    DBG_INFO(("[DEV_DB] the dev db current dev_type_category[%d]!\n",pt_dev_db->e_dev_type_category));

    *pe_dev_type_category = pt_dev_db->e_dev_type_category;

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_is_dev_type_dul
 *
 * Description: the result of this fun return is config according to the spec info, and can check wether
 *                   config for this item(view index) is have accture two item
 *
 * Inputs:  - ui4_dev_view_type----> the view index of the dev type
 *             - pb_is_dul   ---> this is a point to get the result
 * Outputs: - return DEV_DBR_OK indicate the fun return ok, otherwise the get value is in valid
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32  a_dev_db_is_dev_type_dul(UINT32   ui4_dev_view_type,BOOL* pb_is_dul)
{
    DEV_DB_UTIL_T*        pt_dev_db    = &t_g_dev_db_util;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    /* check the dev type view idx valid or not*/
    if (ui4_dev_view_type > DEV_DB_DEV_TYPE_DEF_NUM)
    {
        return DEV_DBR_FAIL;
    }

    /* check the parameter valid or not */
    if (NULL == pb_is_dul)
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_is_dev_type_dul() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    /* currently only support the dev category dev all and dev tuner*/
    if ((DEV_DB_DEV_TYPE_CTGY_ALL_DEV == pt_dev_db->e_dev_type_category)
        || (DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX== pt_dev_db->e_dev_type_category))
    {
        /* the following case if set just according to the spec, also can refer it to the config to dev type*/
        switch (ui4_dev_view_type)
        {
            case DEV_DB_TYPE_VIEW_BLU_RAY:
            case DEV_DB_TYPE_VIEW_COMPUTER:
            case DEV_DB_TYPE_VIEW_DVD:
            case DEV_DB_TYPE_VIEW_GAME:
            case DEV_DB_TYPE_VIEW_VCR:
            case DEV_DB_TYPE_VIEW_SOUND_BAR:
                *pb_is_dul = FALSE;
                 return DEV_DBR_OK;
            case DEV_DB_TYPE_VIEW_CABLE_BOX:
            case DEV_DB_TYPE_VIEW_DVR:
            case DEV_DB_TYPE_VIEW_SATELLITE:
            case DEV_DB_TYPE_VIEW_AVR_AMP:
                *pb_is_dul = TRUE;
                return DEV_DBR_OK;
            default:
                return DEV_DBR_FAIL;
        }
    }
    else if (DEV_DB_DEV_TYPE_CTGY_TUNER == pt_dev_db->e_dev_type_category)
    {
         /* according to the custom spec the type tuner is not dual so just set the dual to false*/
        *pb_is_dul = FALSE;
        return DEV_DBR_OK;
    }
    else
    {
        return DEV_DBR_FAIL;
    }
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_try_to_stop_bmc_task
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_try_to_stop_bmc_task(VOID)
{
    DEV_DB_UTIL_T*              pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BMC_QUERY_T          t_query_info;
    INT32                       i4_ret;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    i4_ret = _dev_db_reset_bmc_query_info(&t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_reset_bmc_query_info(brand) fail!\n"));
        return i4_ret;
    }

    /* set the brand query info*/
    t_query_info.e_query_type = DEV_DB_THREAD_QUERY_STOP;

    /* inset the query info of brand to the thread task que*/
    i4_ret = _dev_db_insert_bmc_query_task_info(t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_insert_bmc_query_task_info(brand) fail!\n"));
        return i4_ret;
    }

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: a_dev_db_update_brand_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_update_brand_info(UINT32        ui4_type_view_idx,
                                         DEV_DB_TYPE_T t_dev_type,
                                         CHAR*         c_brand_prefix)
{
    DEV_DB_UTIL_T*              pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BMC_QUERY_T          t_query_info;
    BOOL                        b_is_dev_type_dul   = FALSE;
    INT32                       i4_ret;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }


    DBG_INFO(("[DEV_DB] a_dev_db_update_brand_info() type_view_idx[%d],brd_prefix[%s]!\n",
               ui4_type_view_idx,
               c_brand_prefix));

    i4_ret = _dev_db_reset_bmc_query_info(&t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_reset_bmc_query_info(brand) fail!\n"));
        return i4_ret;
    }

    /* here will to query the online brand info*/
    i4_ret = a_dev_db_is_dev_type_dul(ui4_type_view_idx,&b_is_dev_type_dul);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] a_dev_db_is_dev_type_dul() fail!\n"));
        return i4_ret;
    }

    /* set the brand query info*/
    t_query_info.e_query_type = DEV_DB_THREAD_QUERY_BRAND;
    t_query_info.b_is_dual = b_is_dev_type_dul;
    t_query_info.ui4_type_svidx = ui4_type_view_idx;
    c_strncpy(t_query_info.s_brd_prefix, c_brand_prefix, DEV_DB_NAME_LEN_MAX);
    c_memcpy(&(t_query_info.t_type_sel_info),
             &(t_dev_type),
             sizeof(DEV_DB_TYPE_T));

    /* inset the query info of brand to the thread task que*/
    i4_ret = _dev_db_insert_bmc_query_task_info(t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_insert_bmc_query_task_info(brand) fail!\n"));
        return i4_ret;
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_update_model_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_update_model_info(UINT32         ui4_type_view_idx,
                                         DEV_DB_TYPE_T  t_dev_type,
                                         DEV_DB_BRMD_T  t_brd_info,
                                         CHAR*          c_brand_name,
                                         CHAR*          c_model_prefix)
{
    DEV_DB_UTIL_T*            pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BMC_QUERY_T        t_query_info;
    BOOL                      b_is_dev_type_dul   = FALSE;
    INT32                     i4_ret;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    /* assume the brand should have name*/
    if ((NULL == c_brand_name)
        || ('\0' == c_brand_name[0]))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun _dev_db_online_async_update_model_info() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }


    DBG_INFO(("[DEV_DB] a_dev_db_update_model_info() type_view_idx[%d],brd_name[%s],mdl_prefix[%s]!\n",
               ui4_type_view_idx,
               c_brand_name,
               c_model_prefix));

    i4_ret = _dev_db_reset_bmc_query_info(&t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_reset_bmc_query_info(model) fail!\n"));
        return i4_ret;
    }

    i4_ret = a_dev_db_is_dev_type_dul(ui4_type_view_idx,&b_is_dev_type_dul);

    if (DEV_DBR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* set the model query info*/
    t_query_info.e_query_type = DEV_DB_THREAD_QUERY_MODEL;
    t_query_info.b_is_dual = b_is_dev_type_dul;
    c_strncpy(t_query_info.s_mdl_prefix, c_model_prefix, DEV_DB_NAME_LEN_MAX);
    c_strncpy(t_query_info.s_brd_name, c_brand_name, DEV_DB_NAME_LEN_MAX);
    c_memcpy(&(t_query_info.t_type_sel_info),
             &(t_dev_type),
             sizeof(DEV_DB_TYPE_T));
    c_memcpy(&(t_query_info.t_brd_sel_info),
             &(t_brd_info),
             sizeof(DEV_DB_BRMD_T));

    /* insert the query info of model to the thread task que*/
    i4_ret = _dev_db_insert_bmc_query_task_info(t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_insert_bmc_query_task_info(model) fail!\n"));
        return i4_ret;
    }
    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_update_codeset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_update_codeset(UINT32         ui4_type_view_idx,
                                     DEV_DB_TYPE_T  t_dev_type,
                                     DEV_DB_BRMD_T  t_brd_info,
                                     DEV_DB_BRMD_T  t_mdl_info,
                                     CHAR*          c_brand_name,
                                     CHAR*          c_model_name)
{
    DEV_DB_UTIL_T*            pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BMC_QUERY_T        t_query_info;
    BOOL                      b_is_dev_type_dul   = FALSE;
    INT32                     i4_ret;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    /* assume the brand should have name*/
    if ((NULL == c_brand_name)
        || ('\0' == c_brand_name[0]))
    {
        DBG_ERROR(("[DEV_DB] the parameter of brand_name for fun a_dev_db_update_codeset() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    /* assume the brand should have name*/
    if ((NULL == c_model_name)
        || ('\0' == c_model_name[0]))
    {
        DBG_ERROR(("[DEV_DB] the parameter of model_name for fun a_dev_db_update_codeset() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    i4_ret = _dev_db_reset_bmc_query_info(&t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_reset_bmc_query_info(model) fail!\n"));
        return i4_ret;
    }

    i4_ret = a_dev_db_is_dev_type_dul(ui4_type_view_idx,&b_is_dev_type_dul);
    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] a_dev_db_is_dev_type_dul(codeset) fail!\n"));
        return i4_ret;
    }
    DBG_INFO(("[DEV_DB] a_dev_db_update_codeset() type_view_idx[%d],brd_name[%s],mdl_name[%s]!\n",
               ui4_type_view_idx,
               c_brand_name,
               c_model_name));

    t_query_info.e_query_type = DEV_DB_THREAD_QUERY_CODESET;
    t_query_info.b_is_dual = b_is_dev_type_dul;

    c_strncpy(t_query_info.s_brd_name, c_brand_name, DEV_DB_NAME_LEN_MAX);
    c_strncpy(t_query_info.s_mdl_name, c_model_name, DEV_DB_NAME_LEN_MAX);

    c_memcpy(&(t_query_info.t_type_sel_info),
             &(t_dev_type),
             sizeof(DEV_DB_TYPE_T));

    c_memcpy(&(t_query_info.t_brd_sel_info),
             &(t_brd_info),
             sizeof(DEV_DB_BRMD_T));

    c_memcpy(&(t_query_info.t_mdl_sel_info),
             &(t_mdl_info),
             sizeof(DEV_DB_BRMD_T));

    /* insert the query info of codeset to the thread task que*/
    i4_ret = _dev_db_insert_bmc_query_task_info(t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_insert_bmc_query_task_info(codeset) fail!\n"));
        return i4_ret;
    }
    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: a_dev_db_update_codeset_with_brand
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_update_codeset_with_brand(UINT32         ui4_type_view_idx,
                                     DEV_DB_TYPE_T  t_dev_type,
                                     DEV_DB_BRMD_T  t_brd_info,
                                     CHAR*          c_brand_name)
{
    DEV_DB_UTIL_T*            pt_dev_db           = &t_g_dev_db_util;
    DEV_DB_BMC_QUERY_T        t_query_info;
    BOOL                      b_is_dev_type_dul   = FALSE;
    INT32                     i4_ret;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    /* assume the brand should have name*/
    if ((NULL == c_brand_name)
        || ('\0' == c_brand_name[0]))
    {
        DBG_ERROR(("[DEV_DB] the parameter of brand_name for fun a_dev_db_update_codeset() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    i4_ret = _dev_db_reset_bmc_query_info(&t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_reset_bmc_query_info(model) fail!\n"));
        return i4_ret;
    }

    i4_ret = a_dev_db_is_dev_type_dul(ui4_type_view_idx,&b_is_dev_type_dul);
    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] a_dev_db_is_dev_type_dul(codeset) fail!\n"));
        return i4_ret;
    }
    DBG_INFO(("[DEV_DB] a_dev_db_update_codeset_with_brand() type_view_idx[%d],brd_name[%s]!\n",
               ui4_type_view_idx,
               c_brand_name));

    t_query_info.e_query_type = DEV_DB_THREAD_QUERY_CODESET_WITH_BRD;
    t_query_info.b_is_dual = b_is_dev_type_dul;

    c_strncpy(t_query_info.s_brd_name, c_brand_name, DEV_DB_NAME_LEN_MAX);

    c_memcpy(&(t_query_info.t_type_sel_info),
             &(t_dev_type),
             sizeof(DEV_DB_TYPE_T));

    c_memcpy(&(t_query_info.t_brd_sel_info),
             &(t_brd_info),
             sizeof(DEV_DB_BRMD_T));

    /* insert the query info of codeset to the thread task que*/
    i4_ret = _dev_db_insert_bmc_query_task_info(t_query_info);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[DEV_DB] _dev_db_insert_bmc_query_task_info(codeset) fail!\n"));
        return i4_ret;
    }

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_update_dev_type
 *
 * Description:as the dev idx for local and online is
 * the same.  so call this api is ok to get the online dev info.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_update_dev_type( DEV_DB_DEV_TYPE_CTGY_T      e_dev_type_category )
{
    WFRCC_STRING_LIST_T      t_local_dev_list = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db        = &t_g_dev_db_util;
    INT32                    i4_local_dev_num = 0;
    UINT32                   ui4_idx          = 0;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if (DEV_DB_DEV_TYPE_CTGY_NONE != pt_dev_db->e_dev_type_category)
    {
	    pt_dev_db->e_dev_type_category = e_dev_type_category;
	    return DEV_DBR_OK;
    }
#ifdef APP_PORTING
    i4_local_dev_num = c_get_device_types(&(t_local_dev_list.p_list));
#endif
    if ((i4_local_dev_num <= 0)
        || (i4_local_dev_num < DEV_DB_DEV_TYPE_DEF_NUM)
        || (NULL == t_local_dev_list.p_list))
    {
        DBG_ERROR(("[DEV_DB] the dev db updater dev type fail!\n"));
        return DEV_DBR_FAIL;
    }
    else
    {
        a_dev_db_lock();

        /* setting the value of the dev type info arr according to the spec
               * the origina local dev type should be:
               * 0-> TV,1->Cable,IPTV,2->Video Accessory,3->Sattellite/DSS,
               * 4->VCR,5->DVD,6->Receiver,Misc Audio,7->Amplifier,8->CD,
               * 9->Home Control
               * the re-map dev type for view should be:
               * [0]->Blu-ray 5, [1]->Cable box 1, [2]->Computer 2, [3]->DVD 5,
               * [4]->DVR 1+3, [5]->Game 2, [6]-> Satellite 3, [7]->
               * VCR 4, [8]->AVR/Amplifer 6+7, [9]-> Sound bar 6
               */

        _dev_db_reset_type_info();


        DBG_INFO(("[DEV_DB] the dev type num in the list is %d !\n",i4_local_dev_num));

        DBG_INFO(("[DEV_DB] a_dev_db_update_dev_type() category[%d] !\n",e_dev_type_category));

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_BLU_RAY].s_deva_src_name,t_local_dev_list.p_list[5],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_BLU_RAY].i4_deva_src_idx  = DEV_DB_TYPE_DVD;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_BLU_RAY].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_BLU_RAY].s_dev_view_name,DEV_DB_TYPE_VIEW_BLU_RAY_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_CABLE_BOX].s_deva_src_name,t_local_dev_list.p_list[1],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_CABLE_BOX].i4_deva_src_idx  = DEV_DB_TYPE_CABLE_IPTV;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_CABLE_BOX].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_CABLE_BOX].s_dev_view_name,DEV_DB_TYPE_VIEW_CABLE_BOX_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_COMPUTER].s_deva_src_name,t_local_dev_list.p_list[2],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_COMPUTER].i4_deva_src_idx  = DEV_DB_TYPE_VIDEO_ACCESSORY;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_COMPUTER].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_COMPUTER].s_dev_view_name,DEV_DB_TYPE_VIEW_COMPUTER_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVD].s_deva_src_name,t_local_dev_list.p_list[5],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVD].i4_deva_src_idx  = DEV_DB_TYPE_DVD;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVD].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVD].s_dev_view_name,DEV_DB_TYPE_VIEW_DVD_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVR].s_deva_src_name,t_local_dev_list.p_list[1],DEV_DB_NAME_LEN_MAX);
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVR].s_devb_src_name,t_local_dev_list.p_list[3],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVR].i4_deva_src_idx  = DEV_DB_TYPE_CABLE_IPTV;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVR].i4_devb_src_idx  = DEV_DB_TYPE_SATTELLITE_DSS;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_DVR].s_dev_view_name,DEV_DB_TYPE_VIEW_DVR_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_GAME].s_deva_src_name,t_local_dev_list.p_list[2],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_GAME].i4_deva_src_idx  =  DEV_DB_TYPE_VIDEO_ACCESSORY;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_GAME].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_GAME].s_dev_view_name,DEV_DB_TYPE_VIEW_GAME_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SATELLITE].s_deva_src_name,t_local_dev_list.p_list[3],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SATELLITE].i4_deva_src_idx  = DEV_DB_TYPE_SATTELLITE_DSS;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SATELLITE].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SATELLITE].s_dev_view_name,DEV_DB_TYPE_VIEW_SATELLITE_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_VCR].s_deva_src_name,t_local_dev_list.p_list[4],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_VCR].i4_deva_src_idx  =  DEV_DB_TYPE_VCR;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_VCR].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_VCR].s_dev_view_name,DEV_DB_TYPE_VIEW_VCR_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_AVR_AMP].s_deva_src_name,t_local_dev_list.p_list[6],DEV_DB_NAME_LEN_MAX);
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_AVR_AMP].s_devb_src_name,t_local_dev_list.p_list[7],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_AVR_AMP].i4_deva_src_idx  = DEV_DB_TYPE_RECEIVER_MISC_AUDIO;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_AVR_AMP].i4_devb_src_idx  = DEV_DB_TYPE_AMPLIFIER;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_AVR_AMP].s_dev_view_name,DEV_DB_TYPE_VIEW_AVR_AMP_NAME,DEV_DB_NAME_LEN_MAX);

        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SOUND_BAR].s_deva_src_name,t_local_dev_list.p_list[6],DEV_DB_NAME_LEN_MAX);
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SOUND_BAR].i4_deva_src_idx  = DEV_DB_TYPE_RECEIVER_MISC_AUDIO;
        pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SOUND_BAR].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;
        c_strncpy(pt_dev_db->t_dev_type[DEV_DB_TYPE_VIEW_SOUND_BAR].s_dev_view_name,DEV_DB_TYPE_VIEW_SOUND_BAR_NAME,DEV_DB_NAME_LEN_MAX);
        DBG_INFO(("[DEV_DB] update the dev type for dev all !\n"));

        /* updater the dev type num*/
        pt_dev_db->ui4_dev_type_num = DEV_DB_DEV_TYPE_DEF_NUM;
        pt_dev_db->e_dev_type_category = e_dev_type_category;

        /* init the dev type, as the dev type is fixed so here will write the hard code*/
        for (ui4_idx = 0; ui4_idx < DEV_DB_DEV_TYPE_DEF_NUM; ui4_idx ++)
        {
            pt_dev_db->t_dev_type[ui4_idx].pw2s_txt_msg = MLM_DEVDB_TEXT(_dev_db_get_mlm_lang_id(),(UINT16)(MLM_DEVDB_KEY_DEV_TYPE_BLU_RAY + ui4_idx));
        }


        a_dev_db_unlock();
    }

    /* here should free the memory about the dev list*/
    _dev_db_free_list(&t_local_dev_list,
                      i4_local_dev_num);

    return DEV_DBR_OK;
}

INT32 a_dev_db_get_dev_type_ex(DEV_DB_TYPE_T* pt_dev_info,
                                   UINT32* pui4_dev_type_num)
{
    WFRCC_STRING_LIST_T      t_local_dev_list = {NULL, 0 , 0};
    DEV_DB_UTIL_T*           pt_dev_db        = &t_g_dev_db_util;
    INT32                    i4_local_dev_num = 0;
    UINT32                   ui4_idx          = 0;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }
#ifdef APP_PORTING
    i4_local_dev_num = c_get_device_types(&(t_local_dev_list.p_list));
#endif
    if ((i4_local_dev_num <= 0)
        || (i4_local_dev_num < DEV_DB_DEV_TYPE_DEF_NUM)
        || (NULL == t_local_dev_list.p_list))
    {
		/* here should free the memory about the dev list*/
		_dev_db_free_list(&t_local_dev_list,
						  i4_local_dev_num);
        DBG_ERROR(("[DEV_DB] the dev db updater dev type fail!\n"));
        return DEV_DBR_FAIL;
    }
    else
    {
        a_dev_db_lock();

        /* setting the value of the dev type info arr according to the spec
               * the origina local dev type should be:
               * 0-> TV,1->Cable,IPTV,2->Video Accessory,3->Sattellite/DSS,
               * 4->VCR,5->DVD,6->Receiver,Misc Audio,7->Amplifier,8->CD,
               * 9->Home Control
               * the re-map dev type for view should be:
               * [0]->Blu-ray 5, [1]->Cable box 1, [2]->Computer 2, [3]->DVD 5,
               * [4]->DVR 1+3, [5]->Game 2, [6]-> Satellite 3, [7]->
               * VCR 4, [8]->AVR/Amplifer 6+7, [9]-> Sound bar 6
               */
        DBG_INFO(("[DEV_DB] the dev type num in the list is %d !\n",i4_local_dev_num));

        DBG_INFO(("[DEV_DB] a_dev_db_get_dev_type() category[%d] !\n",pt_dev_db->e_dev_type_category));

        switch (pt_dev_db->e_dev_type_category)
        {
            case DEV_DB_DEV_TYPE_CTGY_ALL_DEV:
            {
                /* check the dev arr is valid or not*/
			    if (0 == pt_dev_db->ui4_dev_type_num)
			    {
					/* here should free the memory about the dev list*/
					_dev_db_free_list(&t_local_dev_list,
									  i4_local_dev_num);

			        DBG_ERROR(("[DEV_DB] there is no dev type in the dev arr, please update the dev type arr first!\n"));
			        a_dev_db_unlock();
			        return DEV_DBR_FAIL;
			    }

			    /* copy the dev type arr to the client part from the glob arr for dev type in dev db*/
			    for (ui4_idx = 0; ui4_idx < pt_dev_db->ui4_dev_type_num; ui4_idx ++)
			    {
			        c_memcpy(&(pt_dev_info[ui4_idx]),
			                 &(pt_dev_db->t_dev_type[ui4_idx]),
			                 sizeof(DEV_DB_TYPE_T));
			    }

			     /* set the dev type num to the client*/
				*pui4_dev_type_num = pt_dev_db->ui4_dev_type_num;

			    DBG_INFO(("[DEV_DB] get the dev type for dev all !\n"));

                /* init the dev type, as the dev type is fixed so here will write the hard code*/
                for (ui4_idx = 0; ui4_idx < DEV_DB_DEV_TYPE_DEF_NUM; ui4_idx ++)
                {
                    pt_dev_info[ui4_idx].pw2s_txt_msg = MLM_DEVDB_TEXT(_dev_db_get_mlm_lang_id(),(UINT16)(MLM_DEVDB_KEY_DEV_TYPE_BLU_RAY + ui4_idx));
                }
            }
                break;
            case DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX:
            {

			    if (0 == pt_dev_db->ui4_dev_type_num)
			    {
					/* here should free the memory about the dev list*/
					_dev_db_free_list(&t_local_dev_list,
									  i4_local_dev_num);

			        DBG_ERROR(("[DEV_DB] there is no dev type in the dev arr, please update the dev type arr first!\n"));
			        a_dev_db_unlock();
			        return DEV_DBR_FAIL;
			    }

			    /* copy the dev type arr to the client part from the glob arr for dev type in dev db*/
			    for (ui4_idx = 0; ui4_idx < pt_dev_db->ui4_dev_type_num; ui4_idx ++)
			    {
			        c_memcpy(&(pt_dev_info[ui4_idx]),
			                 &(pt_dev_db->t_dev_type[ui4_idx]),
			                 sizeof(DEV_DB_TYPE_T));
			    }

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_BLU_RAY].s_dev_view_name,DEV_DB_TYPE_VIEW_BLU_RAY_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_CABLE_BOX].s_dev_view_name,DEV_DB_TYPE_VIEW_CABLE_BOX_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_COMPUTER].s_dev_view_name,DEV_DB_TYPE_VIEW_COMPUTER_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_DVD].s_dev_view_name,DEV_DB_TYPE_VIEW_DVD_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_DVR].s_dev_view_name,DEV_DB_TYPE_VIEW_DVR_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_GAME].s_dev_view_name,DEV_DB_TYPE_VIEW_GAME_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_SATELLITE].s_dev_view_name,DEV_DB_TYPE_VIEW_SATELLITE_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_VCR].s_dev_view_name,DEV_DB_TYPE_VIEW_VCR_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_AVR_AMP].s_dev_view_name,DEV_DB_TYPE_VIEW_AVR_AMP_NAME,DEV_DB_NAME_LEN_MAX);

                c_strncpy(pt_dev_info[DEV_DB_TYPE_VIEW_SOUND_BAR].s_dev_view_name,DEV_DB_TYPE_VIEW_SOUND_BAR_NAME,DEV_DB_NAME_LEN_MAX);

                 /* set the dev type num to the client*/
				*pui4_dev_type_num = pt_dev_db->ui4_dev_type_num;

                DBG_INFO(("[DEV_DB] get the dev type for dev_ex all !\n"));

                /* init the dev type, as the dev type is fixed so here will write the hard code*/
                for (ui4_idx = 0; ui4_idx < DEV_DB_DEV_TYPE_DEF_NUM; ui4_idx ++)
                {
                    pt_dev_info[ui4_idx].pw2s_txt_msg = MLM_DEVDB_TEXT(_dev_db_get_mlm_lang_id(),(UINT16)(MLM_DEVDB_KEY_DEV_TYPE_BLU_RAY_EX + ui4_idx));
                }


            }
                break;
            case DEV_DB_DEV_TYPE_CTGY_TUNER:
            {
                c_strncpy(pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX].s_deva_src_name,t_local_dev_list.p_list[1],DEV_DB_NAME_LEN_MAX);
                pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX].i4_deva_src_idx  = DEV_DB_TYPE_CABLE_IPTV;
                pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;

                c_strncpy(pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX].s_dev_view_name,DEV_DB_TYPE_VIEW_CABLE_BOX_NAME,DEV_DB_NAME_LEN_MAX);
                pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX].pw2s_txt_msg = MLM_DEVDB_TEXT(_dev_db_get_mlm_lang_id(),(UINT16)(MLM_DEVDB_KEY_DEV_TYPE_CABLE_BOX));

                c_strncpy(pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_SATELLITE].s_deva_src_name,t_local_dev_list.p_list[3],DEV_DB_NAME_LEN_MAX);
                pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_SATELLITE].i4_deva_src_idx  = DEV_DB_TYPE_SATTELLITE_DSS;
                pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_SATELLITE].i4_devb_src_idx  = DEV_DB_TYPE_INVALID;

                c_strncpy(pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_SATELLITE].s_dev_view_name,DEV_DB_TYPE_VIEW_SATELLITE_NAME,DEV_DB_NAME_LEN_MAX);
                pt_dev_info[DEV_DB_TYPE_TUNER_VIEW_SATELLITE].pw2s_txt_msg = MLM_DEVDB_TEXT(_dev_db_get_mlm_lang_id(),(UINT16)(MLM_DEVDB_KEY_DEV_TYPE_SATELLITE));


                DBG_INFO(("[DEV_DB] get the dev type for tuner all !\n"));

                /* updater the dev type num*/
                *pui4_dev_type_num = DEV_DB_DEV_TYPE_TUNER_NUM;
            }
                break;
            default:
                break;
        }

        a_dev_db_unlock();
    }
    /* here should free the memory about the dev list*/
    _dev_db_free_list(&t_local_dev_list,
                      i4_local_dev_num);

    return DEV_DBR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: a_dev_db_get_brand_list
 *
 * Description: the c_brand_prefix should use the update one about this query
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_get_brand_list(DEV_DB_BRMD_T* pt_brd_info,
                                   UINT32* pui4_brd_num,
                                   CHAR*  c_brand_prefix)
{
    INT32                    i4_index     = 0;
    DEV_DB_UTIL_T*           pt_dev_db    = &t_g_dev_db_util;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((NULL == pt_brd_info)
        || (NULL == pui4_brd_num))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_get_brand_list() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    a_dev_db_lock();

    if (((NULL == c_brand_prefix) && ('\0' != pt_dev_db->c_brand_prefix[0]))
        || ((NULL != c_brand_prefix) && (0 != c_strcmp(pt_dev_db->c_brand_prefix,c_brand_prefix))))
    {
        /* here the query result is not valid and the data is updating*/
        a_dev_db_unlock();

        DBG_ERROR(("[DEV_DB] this query result should be discard!\n"));
        return DEV_DBR_FAIL;
    }

    if (pt_dev_db->ui4_brd_num > 0)
    {
        for (i4_index = 0; i4_index < pt_dev_db->ui4_brd_num; i4_index ++)
        {
            c_memcpy(&(pt_brd_info[i4_index]),
                     &(pt_dev_db->t_brd_info[i4_index]),
                     sizeof(DEV_DB_BRMD_T));
        }

        *pui4_brd_num = pt_dev_db->ui4_brd_num;
    }
    else
    {
        *pui4_brd_num = 0;
    }

    a_dev_db_unlock();

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_get_model_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_get_model_list(DEV_DB_BRMD_T* pt_mdl_info,
                                   UINT32* pui4_mdl_num,
                                   CHAR*  c_mdl_prefix)
{
    INT32                    i4_index     = 0;
    DEV_DB_UTIL_T*           pt_dev_db    = &t_g_dev_db_util;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((NULL == pt_mdl_info) || (NULL == pui4_mdl_num))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_get_brand_list() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    a_dev_db_lock();

    if (((NULL == c_mdl_prefix) && ('\0' != pt_dev_db->c_model_prefix[0]))
        || ((NULL != c_mdl_prefix) && (0 != c_strcmp(pt_dev_db->c_model_prefix,c_mdl_prefix))))
    {
        /* here the query result is not valid and the data is updating*/
        a_dev_db_unlock();
        DBG_ERROR(("[DEV_DB] this query result should be discard!\n"));
        return DEV_DBR_FAIL;
    }

    if (pt_dev_db->ui4_model_num > 0)
    {
        for (i4_index = 0; i4_index < pt_dev_db->ui4_model_num; i4_index ++)
        {
            c_memcpy(&(pt_mdl_info[i4_index]),
                     &(pt_dev_db->t_model_info[i4_index]),
                     sizeof(DEV_DB_BRMD_T));
        }

        *pui4_mdl_num = pt_dev_db->ui4_model_num;
    }
    else
    {
        *pui4_mdl_num = 0;
    }

    a_dev_db_unlock();

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_get_codeset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_get_codeset(DEV_DB_CODESET_T** ppt_codeset)
{
    DEV_DB_UTIL_T*           pt_dev_db                = &t_g_dev_db_util;

    *ppt_codeset =  &(pt_dev_db->t_codeset);

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_get_codeset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_get_codeset_list(DEV_DB_CODESET_LIST_T** ppt_codeset_list)
{
    DEV_DB_UTIL_T*           pt_dev_db                = &t_g_dev_db_util;

    *ppt_codeset_list =  &(pt_dev_db->t_codeset_list);

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_clean_codeset_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_clean_codeset_list(VOID)
{
    a_dev_db_lock();
    _dev_db_clean_codeset_list_info();
    a_dev_db_unlock();

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_manual_upload_codeset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_manual_upload_codeset(UINT32        ui4_type_view_idx,
                                               CHAR*         pt_codeset,
                                               UINT32        ui4_codeset_size)
{
    INT32                    i4_ret = DEV_DBR_FAIL;

    /* codeset must be five letters ,1(alphabet)+4(num)*/
    CHAR                     s_alp_arr[DEV_DB_CODESET_LEN_MAX];
    UINT32                   ui4_alp_arr_num = 0;
    DEV_DB_UTIL_T*           pt_dev_db    = &t_g_dev_db_util;

    /* check the dev db have init or not*/
    if (FALSE == pt_dev_db->b_is_dev_db_init)
    {
        DBG_ERROR(("[DEV_DB] the dev db have not inited please init it first!\n"));
        return DEV_DB_INV_ARG;
    }

    if ((ui4_type_view_idx >= DEV_DB_DEV_TYPE_DEF_NUM)
        || (NULL == pt_codeset)
        || (ui4_codeset_size < DEV_DB_CODESET_LEN_MAX))
    {
        DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_get_brand_list() is invalid!\n"));
        return DEV_DB_INV_ARG;
    }

    c_memset(s_alp_arr, 0, sizeof(s_alp_arr));

    /* currently only support the dev category dev all and dev tuner*/
    if ((DEV_DB_DEV_TYPE_CTGY_ALL_DEV == pt_dev_db->e_dev_type_category)
        || (DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX== pt_dev_db->e_dev_type_category))
    {
        if(ui4_type_view_idx >= DEV_DB_DEV_TYPE_DEF_NUM)
        {
            DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_get_brand_list() is invalid!\n"));
        }
        /* the following case if set just according to the spec, also can refer it to the config to dev type*/
        switch (ui4_type_view_idx)
        {
            case DEV_DB_TYPE_VIEW_BLU_RAY:
                {
                    /* for blu-ray the codeset prefex alphabet will be:'Y' */
                    s_alp_arr[ui4_alp_arr_num] = 'Y';
                    ui4_alp_arr_num ++;

                }
                break;
            case DEV_DB_TYPE_VIEW_COMPUTER:
                {
                    /* for Computer the codeset prefex alphabet will be:'N' */
                    s_alp_arr[ui4_alp_arr_num] = 'N';
                    ui4_alp_arr_num ++;
                }
                break;
            case DEV_DB_TYPE_VIEW_DVD:
                {
                    /* for DVD the codeset prefex alphabet will be:'Y' */

                    s_alp_arr[ui4_alp_arr_num] = 'Y';
                    ui4_alp_arr_num ++;

                }
                break;
            case DEV_DB_TYPE_VIEW_GAME:
                {
                    /* for Game the codeset prefex alphabet will be:'N' */

                    s_alp_arr[ui4_alp_arr_num] = 'N';
                    ui4_alp_arr_num ++;
                }
                break;
            case DEV_DB_TYPE_VIEW_VCR:
                {
                    /* for VCR the codeset prefex alphabet will be:'V' */

                    s_alp_arr[ui4_alp_arr_num] = 'V';
                    ui4_alp_arr_num ++;

                }
                break;
            case DEV_DB_TYPE_VIEW_SOUND_BAR:
                {
                    /* for Sound-Bar the codeset prefex alphabet will be:'R+M' */

                    s_alp_arr[ui4_alp_arr_num] = 'R';
                    ui4_alp_arr_num ++;

                    s_alp_arr[ui4_alp_arr_num] = 'M';
                    ui4_alp_arr_num ++;

                }
                break;
            case DEV_DB_TYPE_VIEW_CABLE_BOX:
                {
                    /* for Cable-Box the codeset prefex alphabet will be:'C' */

                    s_alp_arr[ui4_alp_arr_num] = 'C';
                    ui4_alp_arr_num ++;

                }
                break;
            case DEV_DB_TYPE_VIEW_DVR:
                {
                    /* for DVR the codeset prefex alphabet will be:'C+S' */

                    s_alp_arr[ui4_alp_arr_num] = 'C';
                    ui4_alp_arr_num ++;

                    s_alp_arr[ui4_alp_arr_num] = 'S';
                    ui4_alp_arr_num ++;


                }
                break;
            case DEV_DB_TYPE_VIEW_SATELLITE:
                {
                    /* for Satellite the codeset prefex alphabet will be:'S' */

                    s_alp_arr[ui4_alp_arr_num] = 'S';
                    ui4_alp_arr_num ++;

                }
                break;
            case DEV_DB_TYPE_VIEW_AVR_AMP:
                {
                    /* for AVR/Amplifer the codeset prefex alphabet will be:'R+M+A' */

                    s_alp_arr[ui4_alp_arr_num] = 'R';
                    ui4_alp_arr_num ++;

                    s_alp_arr[ui4_alp_arr_num] = 'M';
                    ui4_alp_arr_num ++;

                    s_alp_arr[ui4_alp_arr_num] = 'A';
                    ui4_alp_arr_num ++;

                }
                break;
            default:
                {
                    ui4_alp_arr_num = 0;
                }
                break;
        }
    }
    else if (DEV_DB_DEV_TYPE_CTGY_TUNER == pt_dev_db->e_dev_type_category)
    {

        if(ui4_type_view_idx >= DEV_DB_DEV_TYPE_TUNER_NUM)
        {
            DBG_ERROR(("[DEV_DB] the parameter of the fun a_dev_db_get_brand_list() is invalid!\n"));
        }
         /* according to the custom spec the type tuner is not dual so just set the dual to false*/

        switch (ui4_type_view_idx)
        {
            case DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX:
                {
                    /* for Cable-Box the codeset prefex alphabet will be:'C' */

                    s_alp_arr[ui4_alp_arr_num] = 'C';
                    ui4_alp_arr_num ++;

                }
                break;

            case DEV_DB_TYPE_TUNER_VIEW_SATELLITE:
                {
                    /* for Satellite the codeset prefex alphabet will be:'S' */

                    s_alp_arr[ui4_alp_arr_num] = 'S';
                    ui4_alp_arr_num ++;

                }
                break;
            default:
                {
                    ui4_alp_arr_num = 0;
                }
                break;
        }

    }
    else
    {
        ui4_alp_arr_num = 0;
    }


    i4_ret = _dev_db_upload_codeset_by_alp_and_num_string(
                                                s_alp_arr,
                                                ui4_alp_arr_num,
                                                pt_codeset,
                                                ui4_codeset_size
                                                );

    DBG_INFO(("\n[DEV_DB]_dev_db_upload_codeset_by_alp_and_num_string() i4_ret=[%d]!!\n",i4_ret));

    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name: a_dev_db_upload_codeset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_upload_codeset(DEV_DB_CODESET_T* pt_codeset)
{
    INT32                    i4_ret = DEV_DBR_FAIL;
#ifdef APP_PORTING
    a_dev_db_lock();

    if (NULL != pt_codeset->c_codeset1)
    {
        i4_ret = c_upload_codeset(pt_codeset->c_codeset1);

        if (0 == i4_ret)
        {
            i4_ret = DEV_DBR_OK;
        }

        c_mem_free(pt_codeset->c_codeset1);
        pt_codeset->c_codeset1 = NULL;
    }

    if (NULL != pt_codeset->c_codeset2)
    {
        i4_ret = c_upload_codeset(pt_codeset->c_codeset2);

        if (0 == i4_ret)
        {
            i4_ret = DEV_DBR_OK;
        }

        c_mem_free(pt_codeset->c_codeset2);
        pt_codeset->c_codeset2 = NULL;
    }

    a_dev_db_unlock();
#endif
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_upload_codeset_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_upload_codeset_ex(CHAR*     c_codeset)
{
    INT32                    i4_ret = DEV_DBR_FAIL;
#ifdef APP_PORTING
    if (NULL != c_codeset)
    {
        i4_ret = c_upload_codeset(c_codeset);

        if (0 == i4_ret)
        {
            i4_ret = DEV_DBR_OK;
        }
        else
        {
            i4_ret = DEV_DBR_FAIL;
        }
    }
#endif
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_save_codeset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_dev_db_save_codeset(CHAR*     c_codeset)
{
    INT32                    i4_ret = DEV_DBR_FAIL;
#if APP_PORTING
    if (NULL != c_codeset)
    {
        i4_ret = c_save_codeset(c_codeset);

        if (0 == i4_ret)
        {
            i4_ret = DEV_DBR_OK;
        }
        else
        {
            i4_ret = DEV_DBR_FAIL;
        }
    }
#endif
    return i4_ret;
}



/*-----------------------------------------------------------------------------
 * Name: _dev_db_reset_bmc_query_info
 *
 * Description: unregister a dev db notify callback which id is ui4_nfy_id
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32  a_dev_db_reset_bmc_query_info(DEV_DB_BMC_QUERY_T*                pt_bmc_query_info)
{
    if (NULL == pt_bmc_query_info)
    {
        return DEV_DB_INV_ARG;
    }

    DBG_INFO(("[DEV_DB] a_dev_db_reset_bmc_query_info(slot[%d])!\n",pt_bmc_query_info->ui4_task_idx));

    a_dev_db_lock();

    c_memset(pt_bmc_query_info,0,sizeof(DEV_DB_BMC_QUERY_T));

    /* reset brand query info about type----> idx*/
    pt_bmc_query_info->t_type_sel_info.i4_deva_src_idx = -1;
    pt_bmc_query_info->t_type_sel_info.i4_devb_src_idx = -1;

    /* reset model query info about type and brand ---> idx*/
    pt_bmc_query_info->t_brd_sel_info.i4_local1_idx = -1;
    pt_bmc_query_info->t_brd_sel_info.i4_online1_idx = -1;
    pt_bmc_query_info->t_brd_sel_info.i4_local2_idx = -1;
    pt_bmc_query_info->t_brd_sel_info.i4_online2_idx = -1;


    /* reset model query info about type and brand ---> idx*/
    pt_bmc_query_info->t_mdl_sel_info.i4_local1_idx = -1;
    pt_bmc_query_info->t_mdl_sel_info.i4_online1_idx = -1;
    pt_bmc_query_info->t_mdl_sel_info.i4_local2_idx = -1;
    pt_bmc_query_info->t_mdl_sel_info.i4_online2_idx = -1;

    pt_bmc_query_info->e_buff_status = DEV_DB_QUERY_BUFF_STATUS_NONE;
    pt_bmc_query_info->ui4_task_idx = 0;
    pt_bmc_query_info->ui4_notify_count = 0;
    pt_bmc_query_info->ui4_query_idx = 0;
    pt_bmc_query_info->b_is_to_clean = FALSE;


    a_dev_db_unlock();

    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_register
 *
 * Description: register the dev db notify callback
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32  a_dev_db_register( dev_db_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id )
{
    DEV_DB_UTIL_T*        pt_dev_db    = &t_g_dev_db_util;
    INT32                 i4_ret   = 0;
    UINT16                ui2_i    = 0;
    BOOL                  b_found  = FALSE;

    DEV_DB_UTIL_NFY_CLIENT_T* pt_client = NULL;

    if (pf_nfy == NULL || pui4_nfy_id == NULL)
    {
        return DEV_DB_INV_ARG;
    }

    a_dev_db_lock();

    do
    {
        /* Find a free slot. */
        for (ui2_i = 0 ;
             ui2_i < (UINT16)DEV_DB_MAX_NUM_NOTIFY_CLIENT ;
             ui2_i++)
        {
            if (pt_dev_db->at_notify_client[ui2_i].pf_notify == NULL)
            {
                b_found = TRUE;
                break;
            }
        }

        /* Not Found */
        if (!b_found)
        {
            i4_ret = DEV_DBR_FAIL;
            break;
        }

        /* Save the information into the slot. */
        pt_client = &(pt_dev_db->at_notify_client[ui2_i]);

        /* usage flag */
        pt_client->pf_notify   = pf_nfy;
        pt_client->pv_tag      = pv_tag;
        pt_client->ui4_nfy_id  = ui2_i;

        /* return out the id */
        *pui4_nfy_id = (UINT32)ui2_i;

        /* Done */
        i4_ret = DEV_DBR_OK;
    } while(0);

    a_dev_db_unlock();

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_unregister
 *
 * Description: unregister a dev db notify callback which id is ui4_nfy_id
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32  a_dev_db_unregister( UINT32 ui4_nfy_id )
{
    DEV_DB_UTIL_T*                 pt_dev_db     = &t_g_dev_db_util;
    INT32                          i4_ret    = 0;
    DEV_DB_UTIL_NFY_CLIENT_T*      pt_client = NULL;

    if(ui4_nfy_id >= (UINT32)DEV_DB_MAX_NUM_NOTIFY_CLIENT)
    {
        return DEV_DB_INV_ARG;
    }

    a_dev_db_lock();

    do
    {
        /* Defeult is fail */
        i4_ret = DEV_DBR_FAIL;

        /* Load the client's information */
        pt_client = &(pt_dev_db->at_notify_client[ui4_nfy_id]);

        /* Check usable. */
        if (pt_client->pf_notify == NULL)
        {
            i4_ret = DEV_DBR_FAIL;
            break;
        }

        /* Set it to unregister */
        pt_client->pf_notify = NULL;

        /* Done */
        i4_ret = DEV_DBR_OK;
    } while(0);

    a_dev_db_unlock();

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_set_wifi_remote_banner_show_flag
 *
 * Description: this api should be call when sys start if the wifi remote have been paired before
 * and befor register the wifi notify,this time should set the flag to false and as wifi notify is wifi remote paired should set the flag to true
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_dev_db_set_wifi_remote_banner_show_flag( BOOL   b_is_allow_show )
{
    b_is_wifi_banner_allow_show = b_is_allow_show;
    return DEV_DBR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_get_wifi_remote_banner_show_flag
 *
 * Description: the banner is to show, should check this flag first
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL a_dev_db_get_wifi_remote_banner_show_flag( VOID )
{
    UINT8   ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
    if(ui1_status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
    {
        return TRUE;
    }

	return b_is_wifi_banner_allow_show;
}

/*-----------------------------------------------------------------------------
 * Name: a_dev_db_show_banner
 *
 * Description: as wifi remote is ok should call it.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_dev_db_show_banner( VOID )
{
    a_nav_show_banner_ex();

    return DEV_DBR_OK;
}



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
 * $RCSfile: ui_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the custom layer header file for UI
 *---------------------------------------------------------------------------*/


#ifndef _A_DEV_DB_CUSTOM_H_
#define _A_DEV_DB_CUSTOM_H_

#include "u_common.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_handle.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "nav/updater/nav_updater.h"
#include "res/nav/banner2/banner_rc.h"

#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "wizard/a_wzd.h"

#include "wfrrc_interface.h"

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/ 

typedef VOID (*dev_db_nfy_fct)(VOID* pv_tag, VOID* pv_nfy_param);
typedef VOID* (*PTHREAD_RUNTING_FUN)(VOID*);


#define DEV_DBR_INITED                              ((INT32) 2)
#define DEV_DBR_NO_ACTION                           ((INT32) 1)
#define DEV_DBR_OK                                  ((INT32) 0)
#define DEV_DBR_FAIL                                ((INT32)-1)
#define DEV_DB_INV_ARG                              ((INT32)-2)

#define DEV_DB_NAME_LEN_MAX                         (32)
#define DEV_DB_MAX_DEV_TYPE_CONT                    (16)
#define DEV_DB_MAX_NUM_NOTIFY_CLIENT                (16)
#define DEV_DB_DUL_OP_MAX                           (512)
#define DEV_DB_DEV_TYPE_DEF_NUM                     (10)
#define DEV_DB_DEV_TYPE_TUNER_NUM                   (2)
#define DEV_DB_NORMAL_EDGE_NUM                      (99)
#define DEV_DB_LOCK_TIMEOUT_TIME                    (30 * 24 * 60 * 60)

/*define the bm query buff len*/
#define DEV_DB_QUERY_BUFF_LEN                       (10)
#define DEV_DB_ONLINE_QUERY_CHEECK_CONT             (5)

#define DEV_DB_CODESET_LEN_MAX                      (6)
#define DEV_DB_CODESET_CHAR_NUM_LEN                 (4)
#define DEV_DB_DEV_TYPE_COMPATIBLE_NUM              (4)



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

/* dev type is for view( this will be for the dev type catagory 
  *dev_all and dev_all_ex) setting according to the custom spec
*/
#define DEV_DB_TYPE_VIEW_BLU_RAY                          ((UINT32)0)
#define DEV_DB_TYPE_VIEW_CABLE_BOX                        ((UINT32)1)
#define DEV_DB_TYPE_VIEW_COMPUTER                         ((UINT32)2)
#define DEV_DB_TYPE_VIEW_DVD                              ((UINT32)3)
#define DEV_DB_TYPE_VIEW_DVR                              ((UINT32)4)
#define DEV_DB_TYPE_VIEW_GAME                             ((UINT32)5)
#define DEV_DB_TYPE_VIEW_SATELLITE                        ((UINT32)6)
#define DEV_DB_TYPE_VIEW_VCR                              ((UINT32)7)
#define DEV_DB_TYPE_VIEW_AVR_AMP                          ((UINT32)8)
#define DEV_DB_TYPE_VIEW_SOUND_BAR                        ((UINT32)9)


/* dev type is for view( this will be for the dev type catagory 
  * tuner) setting according to the custom spec
*/
#define DEV_DB_TYPE_TUNER_VIEW_CABLE_BOX                  ((UINT32)0)
#define DEV_DB_TYPE_TUNER_VIEW_SATELLITE                  ((UINT32)1)

/* the following dev type is the real type*/
#define DEV_DB_TYPE_TV                                    ((INT32)0)
#define DEV_DB_TYPE_CABLE_IPTV                            ((INT32)1)
#define DEV_DB_TYPE_VIDEO_ACCESSORY                       ((INT32)2)
#define DEV_DB_TYPE_SATTELLITE_DSS                        ((INT32)3)
#define DEV_DB_TYPE_VCR                                   ((INT32)4)
#define DEV_DB_TYPE_DVD                                   ((INT32)5)
#define DEV_DB_TYPE_RECEIVER_MISC_AUDIO                   ((INT32)6)
#define DEV_DB_TYPE_AMPLIFIER                             ((INT32)7)
#define DEV_DB_TYPE_CD                                    ((INT32)8)
#define DEV_DB_TYPE_HOME_CONTROL                          ((INT32)9)
#define DEV_DB_TYPE_INVALID                               ((INT32)-1)

#define DEV_DB_TYPE_VIEW_BLU_RAY_NAME                     "Blu-ray"
#define DEV_DB_TYPE_VIEW_CABLE_BOX_NAME                   "Cable Box"
#define DEV_DB_TYPE_VIEW_COMPUTER_NAME                    "Computer"
#define DEV_DB_TYPE_VIEW_DVD_NAME                         "DVD"
#define DEV_DB_TYPE_VIEW_DVR_NAME                         "DVR"
#define DEV_DB_TYPE_VIEW_GAME_NAME                        "Game"
#define DEV_DB_TYPE_VIEW_SATELLITE_NAME                   "Satellite"
#define DEV_DB_TYPE_VIEW_VCR_NAME                         "VCR"
#define DEV_DB_TYPE_VIEW_AVR_AMP_NAME                     "Audio Receiver/Amplifier"
#define DEV_DB_TYPE_VIEW_SOUND_BAR_NAME                   "Sound Bar"
#define DEV_DB_TYPE_VIEW_XBOX_NAME                        "Xbox"

#define DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME              "Audio Receiver"
#define DEV_DB_TYPE_AMPLIFIER_NAME                        "Amplifier"

#define DEV_DB_TYPE_VIEW_BLU_RAY_NAME_EX                     "Blu-Ray"
#define DEV_DB_TYPE_VIEW_CABLE_BOX_NAME_EX                   "Cable box"
#define DEV_DB_TYPE_VIEW_COMPUTER_NAME_EX                    "computer"
#define DEV_DB_TYPE_VIEW_DVD_NAME_EX                         "dvd"
#define DEV_DB_TYPE_VIEW_DVR_NAME_EX                         "dvr"
#define DEV_DB_TYPE_VIEW_GAME_NAME_EX                        "game"
#define DEV_DB_TYPE_VIEW_SATELLITE_NAME_EX                   "satellite"
#define DEV_DB_TYPE_VIEW_VCR_NAME_EX                         "vcr"
#define DEV_DB_TYPE_VIEW_SOUND_BAR_NAME_EX                   "Sound bar"

#define DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME_EX              "Audio Receiver/Amplifier"
#define DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME_EX1             "AVR/Amplifier"

/* discription the dev type category*/
typedef enum
{
    DEV_DB_DEV_TYPE_CTGY_NONE = 0,  
    DEV_DB_DEV_TYPE_CTGY_ALL_DEV,
    DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX,
    DEV_DB_DEV_TYPE_CTGY_TUNER,
    DEV_DB_DEV_TYPE_CTGY_LAST_ENTRY
}   DEV_DB_DEV_TYPE_CTGY_T;

/* discription the query type about the thread*/
typedef enum
{
    DEV_DB_THREAD_QUERY_NONE = 0,  
    DEV_DB_THREAD_QUERY_TYPE ,
    DEV_DB_THREAD_QUERY_BRAND ,
    DEV_DB_THREAD_QUERY_MODEL,
    DEV_DB_THREAD_QUERY_CODESET,
    DEV_DB_THREAD_QUERY_CODESET_WITH_BRD,
    DEV_DB_THREAD_QUERY_STOP,
    DEV_DB_THREAD_QUERY_LAST_ENTRY
}   DEV_DB_QUEYR_TYPE_T;

/* discription the query type about the thread*/
typedef enum
{
    DEV_DB_QUERY_BUFF_STATUS_NONE = 0,  
    DEV_DB_QUERY_BUFF_STATUS_PROC ,
    DEV_DB_QUERY_BUFF_STATUS_PROCING ,
    DEV_DB_QUERY_BUFF_STATUS_PROCED ,
    DEV_DB_QUERY_BUFF_STATUS_LAST_ENTRY
}   DEV_DB_QUEYR_BUFF_STATUS_T;
/* for dev type mapping*/
typedef struct _DEV_DB_TYPE_MAPPING_T
{
	CHAR  blu_ray[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  cable_box[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  computer[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  dvd[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  dvr[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  game[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  satellite[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  vcr[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  audio[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
	CHAR  sound_bar[DEV_DB_DEV_TYPE_COMPATIBLE_NUM][DEV_DB_NAME_LEN_MAX + 1];
}DEV_DB_TYPE_MAPPING_T;

/* the data info for the dev type, current will have to type info merge together
*/
typedef struct _DEV_DB_TYPE_T
{
    /* for dev a information*/
    CHAR      s_deva_src_name[DEV_DB_NAME_LEN_MAX + 1];
    INT32     i4_deva_src_idx;

    /*for dev b information*/
    CHAR      s_devb_src_name[DEV_DB_NAME_LEN_MAX + 1];
    INT32     i4_devb_src_idx;

    CHAR      s_dev_view_name[DEV_DB_NAME_LEN_MAX + 1];
    UTF16_T*  pw2s_txt_msg;
}DEV_DB_TYPE_T;

/* this struce if for the glob result for brand and model query info*/
typedef struct _DEV_DB_BRMD_T
{
    /*for brand or model a information*/
    CHAR      s_src_name[DEV_DB_NAME_LEN_MAX + 1];
    INT32     i4_local1_idx;
    INT32     i4_online1_idx;
    /*for brand or modelb information*/
    INT32     i4_local2_idx;
    INT32     i4_online2_idx;
}DEV_DB_BRMD_T;

/* for brand query info*/
typedef struct _DEV_DB_BRD_QUERY_T
{
    CHAR            s_brd_prefix[DEV_DB_NAME_LEN_MAX + 1];
    UINT32          ui4_type_svidx; /* for type view index*/
    BOOL            b_is_dual;
    DEV_DB_TYPE_T   t_type_sel_info;
}DEV_DB_BRD_QUERY_T;

/* for brand query info*/
typedef struct _DEV_DB_MDL_QUERY_T
{
    CHAR            s_mdl_prefix[DEV_DB_NAME_LEN_MAX + 1];
    CHAR            s_brd_name[DEV_DB_NAME_LEN_MAX + 1];
    BOOL            b_is_dual;
    DEV_DB_TYPE_T   t_type_sel_info;
    DEV_DB_BRMD_T   t_brd_sel_info;
}DEV_DB_MDL_QUERY_T;

/* for brand query info*/
typedef struct _DEV_DB_CDS_QUERY_T
{
    BOOL            b_is_dual;
    DEV_DB_TYPE_T   t_type_sel_info;
    DEV_DB_BRMD_T   t_brd_sel_info;
    DEV_DB_BRMD_T   t_mdl_sel_info;
}DEV_DB_CDS_QUERY_T;

/* for brand query info*/
typedef struct _DEV_DB_BM_QUERY_T
{
    /* for all query will use*/
    DEV_DB_QUEYR_TYPE_T    e_query_type;
    
    UINT32                 ui4_type_svidx; /* for type view index*/
    BOOL                   b_is_dual;
    DEV_DB_TYPE_T          t_type_sel_info;

    /* for brand query will use*/
    CHAR                   s_brd_prefix[DEV_DB_NAME_LEN_MAX + 1];

    /*for model query will use*/ 
    CHAR                   s_mdl_prefix[DEV_DB_NAME_LEN_MAX + 1];

    /* for model or codeset query will use*/
    CHAR                   s_brd_name[DEV_DB_NAME_LEN_MAX + 1];
    CHAR                   s_mdl_name[DEV_DB_NAME_LEN_MAX + 1];
    
    DEV_DB_BRMD_T          t_brd_sel_info; /* this is reserved*/

    /* for codeset query use*/
    DEV_DB_BRMD_T          t_mdl_sel_info;

    /* slot status control info*/
    DEV_DB_QUEYR_BUFF_STATUS_T                   e_buff_status;
    UINT32                 ui4_query_idx;
    UINT32                 ui4_task_idx;
    UINT32                 ui4_notify_count;
    BOOL                   b_is_to_clean;
    
#ifdef APP_UEI_SPINNER_SUPPORT
	/*for brand on line query */
	BOOL				   b_is_brd_online_query_start;
	BOOL 				   b_is_brd_online_query_complete;
#endif

}DEV_DB_BMC_QUERY_T;


/* here will define the merge type*/
typedef enum
{
    DEV_DB_MGE_NONE =0,  
    DEV_DB_MGE_LOCAL_A ,
    DEV_DB_MGE_LOCAL_B ,
    DEV_DB_MGE_ONLINE_A,
    DEV_DB_MGE_ONLINE_B,
    DEV_DB_MGE_LAST_ENTRY
}   DEV_DB_MERGE_TYPE_T;

/* the temp info struct for brand or model merge*/
typedef struct _DEV_DB_BM_T
{
    CHAR      s_src_name[DEV_DB_NAME_LEN_MAX + 1];
    INT32     i4_idx;
}DEV_DB_BM_T;

/* codeset info */
typedef struct _DEV_DB_CODESET_T
{
    CHAR*     c_codeset1;
    CHAR*     c_codeset2;
}DEV_DB_CODESET_T;

/* codeset info */
typedef struct _DEV_DB_CODESET_LIST_T
{
    WFRCC_STRING_LIST_T      t_codeset_list1;
    WFRCC_STRING_LIST_T      t_codeset_list2;
}DEV_DB_CODESET_LIST_T;

/* the client register info for online query result to notify*/
typedef struct _DEV_DB_UTIL_NFY_CLIENT_T
{
    dev_db_nfy_fct               pf_notify;
    VOID*                        pv_tag; 
    UINT32                       ui4_nfy_id; 
} DEV_DB_UTIL_NFY_CLIENT_T;

/* the data info for the mode dev db*/
typedef struct _DEV_DB_UTIL_T
{
    /* the mtx lock handle*/
    HANDLE_T                         h_sema_mtx;
    pthread_mutex_t                  mutex;
    pthread_cond_t                   cond;
    
    /* client info arr*/
    DEV_DB_UTIL_NFY_CLIENT_T         at_notify_client[DEV_DB_MAX_NUM_NOTIFY_CLIENT];

    /* dev db bmc query thread*/
    pthread_t                        h_thread;
    
    /* thread info arr*/
    DEV_DB_BMC_QUERY_T               t_thread_query_info[DEV_DB_QUERY_BUFF_LEN];
    UINT32                           ui4_cur_pro_idx;
    UINT32                           ui4_latest_task_idx;
    UINT32                           ui4_bm_task_count;
    UINT32                           ui4_bm_query_count;
    
    /*current query result about the dev type info include the local and on-line*/
    DEV_DB_TYPE_T                    t_dev_type[DEV_DB_MAX_DEV_TYPE_CONT];
    UINT32                           ui4_dev_type_num;
    DEV_DB_DEV_TYPE_CTGY_T           e_dev_type_category;

    /* brand info of this view*/  
    DEV_DB_BRMD_T                    t_brd_info[DEV_DB_DUL_OP_MAX];
    UINT32                           ui4_brd_num;
    CHAR                             c_brand_prefix[DEV_DB_NAME_LEN_MAX + 1];

    /* model info of view*/
    DEV_DB_BRMD_T                    t_model_info[DEV_DB_DUL_OP_MAX];
    UINT32                           ui4_model_num;
    CHAR                             c_model_prefix[DEV_DB_NAME_LEN_MAX + 1];

    /* codeset info*/
    DEV_DB_CODESET_T                 t_codeset;

    /* the codeset list*/
    DEV_DB_CODESET_LIST_T            t_codeset_list;

    BOOL                             b_is_dev_db_init;
	DEV_DB_TYPE_MAPPING_T			 t_type_mapping;
}DEV_DB_UTIL_T;

/* the lock status type for dev db lock*/
typedef enum
{
    DEV_DB_LOCK_STATUS_NONE =0,    
    DEV_DB_LOCK_STATUS_NORMAL ,
    DEV_DB_LOCK_STATUS_NORMAL_EDGE,
    DEV_DB_LOCK_STATUS_LOCK,
    DEV_DB_LOCK_STATUS_LAST_ENTRY
}   DEV_DB_LOCK_STATUS_T;

/* the lock status query type*/
typedef enum
{
    DEV_DB_LOCK_CHECK_COND_NONE =0,    
    DEV_DB_LOCK_CHECK_COND_CODESET ,
    DEV_DB_LOCK_CHECK_COND_IP_GET,
    DEV_DB_LOCK_CHECK_COND_PARTITION_READY,
    DEV_DB_LOCK_CHECK_COND_LAST_ENTRY
}   DEV_DB_LOCK_CHECK_COND_T;


/* for dev db lock struct information*/
typedef struct _DEV_DB_LOCK_T
{
    time_t     t_time_cnt;
    UINT32     ui4_cnt;
    BOOL       b_is_lock;
    BOOL       b_is_time_update;
    time_t     t_time_lock;
}DEV_DB_LOCK_T;

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/**
*   @brief  this api is for the dev db secure audit use. and will 
*              use this fun to get the dev db lock status. also will 
*              use it to check lock or reset lock.
*   @param [in]   e_check_cond - lock chck option. for normal check
*                       the value for this param should be DEV_DB_LOCK_CHECK_COND_NONE,
*                       and for codeset download the value for this param DEV_DB_LOCK_CHECK_COND_CODESET,
*                       and other value of the enum DEV_DB_LOCK_CHECK_COND_T are reserved.
*   @param [out]   pb_is_lock  - this point will return the dev db lock status.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*/
extern INT32 a_dev_db_check_lock_info( DEV_DB_LOCK_CHECK_COND_T e_check_cond, BOOL* pb_is_lock );

/**
*   @brief  this fun will be used to check whether the sys time is ready.
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern BOOL  a_dev_db_is_sys_time_ready( VOID );

/**
*   @brief  this api is to init the modul of dev db for dev 
*              setup codeset download and upload.
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*/
extern INT32 a_dev_db_init(VOID);

/**
*   @brief  this fun is for the client to register notify functon 
*              to get the brand/model/codeset info.
*   @param [in]   pf_nfy   - the callback fun for client notify
*   @param [in]   pv_tag  - the client tag info
*   @param [out] pui4_nfy_id    -  the notify id for this client
*   @ return return the error code
*   @return value DEV_DBR_OK           - Routing successful
*   @return value DEV_DBR_INITED     - this model alread init
*   @return value DEV_DBR_FAIL         - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_register( dev_db_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id );

/**
*   @brief  this fun is for the client to unregister notify functon 
*              which is used to get the brand/model/codeset info.
*   @param [in]   ui4_nfy_id   - the client callback notify id
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_unregister( UINT32 ui4_nfy_id );

/**
*   @brief  this fun is used to update the dev type,
*              and this update is in sync query.
*   @param [in] e_dev_type_category - dev type update category
*                     currently only support dev all and dev tuner.
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_update_dev_type( DEV_DB_DEV_TYPE_CTGY_T      e_dev_type_category );

/**
*   @brief  this fun is used to update the dev brand info,
*              and input the query task to the task queue. and 
*              the task will be deal with by the bmc thread. the 
*              query result will notify to the client according the
*              callback fun that the client have register. and in
*              the view for the client this update is in async query.
*   @param [in] ui4_type_view_idx - the dev type idx for view
*   @param [in] t_dev_type - the dev type have select info
*   @param [in] c_brand_prefix - the brand prefix for brand query
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_update_brand_info(UINT32        ui4_type_view_idx,
                                         DEV_DB_TYPE_T t_dev_type,
                                         CHAR*         c_brand_prefix);

/**
*   @brief  this fun is used to update the dev model info,
*              and input the query task to the task queue. and 
*              the task will be deal with by the bmc thread. the 
*              query result will notify to the client according the
*              callback fun that the client have register. and in
*              the view for the client this update is in async query.
*   @param [in] ui4_type_view_idx - the dev type idx for view
*   @param [in] t_dev_type - the dev type have select info
*   @param [in] t_brd_info - the brand have been selected info,
*                                       this is for reserved.
*   @param [in] c_brand_name - the brand name for the selected
*                                             info.
*   @param [in] c_model_prefix - the model prefix for model query
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_update_model_info(UINT32         ui4_type_view_idx,
                                         DEV_DB_TYPE_T  t_dev_type,
                                         DEV_DB_BRMD_T  t_brd_info,
                                         CHAR*          c_brand_name,
                                         CHAR*          c_model_prefix);

/**
*   @brief  this fun is used to get the dev type
*   @param [in]   
*   @param [out]  pt_dev_info  - the type arrar point for the dev type.
*   @param [out]  pui4_dev_type_num  - the point for get the dev type num.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_dev_type(DEV_DB_TYPE_T* pt_dev_info,
                                   UINT32* pui4_dev_type_num);
/**
*   @brief  this fun is used to get the dev type_ex
*   @param [in]   
*   @param [out]  pt_dev_info  - the type arrar point for the dev type.
*   @param [out]  pui4_dev_type_num  - the point for get the dev type num.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_dev_type_ex(DEV_DB_TYPE_T* pt_dev_info,
                                   UINT32* pui4_dev_type_num);
/**
*   @brief  this fun is used to get the dev type name
*   @param [in]   dev type name type CHAR*
*   @param [out]  dev type name type UTF16*
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_dev_type_name_ps_to_w2s(CHAR* s_type_name,
                                       UTF16_T** ppw2s_type_msg);
/**
*   @brief  this fun is used to get the dev type category
*   @param [in]   
*   @param [out]  pe_dev_type_category  - the type category point for the dev type.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_dev_type_category(DEV_DB_DEV_TYPE_CTGY_T*   pe_dev_type_category);

/**
*   @brief  this fun is used to get the dev brand
*   @param [in]   c_brand_prefix  -  the brand prefix for brand get.
*   @param [out]  pt_brd_info  - the brand arrar point for the dev brand.
*   @param [out]  pui4_brd_num  - the point for get the dev brand num.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_brand_list(DEV_DB_BRMD_T* pt_brd_info,
                                   UINT32* pui4_brd_num,
                                   CHAR*  c_brand_prefix);

/**
*   @brief  this fun is used to get the dev model
*   @param [in]   c_mdl_prefix  -  the model prefix for model get.
*   @param [out]  pt_mdl_info  - the model arrar point for the dev model.
*   @param [out]  pui4_mdl_num  - the point for get the dev model num.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_model_list(DEV_DB_BRMD_T* pt_mdl_info,
                                   UINT32* pui4_mdl_num,
                                   CHAR*  c_mdl_prefix);

/**
*   @brief  this fun is used to get the codeset
*   @param [in]
*   @param [out]  ppt_codeset  - the point for get codeset.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_codeset(DEV_DB_CODESET_T** ppt_codeset);

/**
*   @brief  this fun is used to upload manual codeset.
*   @param [in]    ui4_type_view_idx   - the dev type index select in the view.
*   @param [in]    pt_codeset   - the point struct for the codeset(manual input num 
*                                             string, and will be get out the full codeset string).
*   @param [in]    ui4_codeset_size   - the buff size for the pt_codeset.
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_manual_upload_codeset(UINT32        ui4_type_view_idx,
                                                      CHAR*         pt_codeset,
                                                      UINT32        ui4_codeset_size);


/**
*   @brief  this fun is used to upload codeset.
*   @param [in]    pt_codeset   - the point struct for the codeset.
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_upload_codeset(DEV_DB_CODESET_T* pt_codeset);


/**
*   @brief  this fun is used to upload codeset.
*   @param [in]    c_codeset   - the point for the codeset.
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_upload_codeset_ex(CHAR*     c_codeset);

/**
*   @brief  this fun is used to save codeset.
*   @param [in]    c_codeset   - the point for the codeset.
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_save_codeset(CHAR*     c_codeset);

/**
*   @brief  this fun is used to update the dev codeset,
*              and input the query task to the task queue. and 
*              the task will be deal with by the bmc thread. the 
*              query result will notify to the client according the
*              callback fun that the client have register. and in
*              the view for the client this update is in async query.
*   @param [in] ui4_type_view_idx - the dev type idx for view
*   @param [in] t_dev_type - the dev type have select info
*   @param [in] t_brd_info - the brand have been selected info,
*                                       this is for reserved.
*   @param [in] t_mdl_info - the model have been selected info,
*   @param [in] c_brand_name - the brand name for the selected
*                                             info.
*   @param [in] c_model_name - the model name for codeset query
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_update_codeset(UINT32         ui4_type_view_idx,
                                     DEV_DB_TYPE_T  t_dev_type,
                                     DEV_DB_BRMD_T  t_brd_info,
                                     DEV_DB_BRMD_T  t_mdl_info,
                                     CHAR*          c_brand_name,
                                     CHAR*          c_model_name);
/**
*   @brief  this fun is used to update the dev codeset list by brand info,
*              and input the query task to the task queue. and 
*              the task will be deal with by the bmc thread. the 
*              query result will notify to the client according the
*              callback fun that the client have register. and in
*              the view for the client this update is in async query.
*   @param [in] ui4_type_view_idx - the dev type idx for view
*   @param [in] t_dev_type - the dev type have select info
*   @param [in] t_brd_info - the brand have been selected info,
*                                       this is for reserved.
*   @param [in] c_brand_name - the brand name for the selected
*                                             info.
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/

extern INT32 a_dev_db_update_codeset_with_brand(UINT32         ui4_type_view_idx,
                                     DEV_DB_TYPE_T  t_dev_type,
                                     DEV_DB_BRMD_T  t_brd_info,
                                     CHAR*          c_brand_name);
/**
*   @brief  this fun is used to get the dev codeset list.
*   @param [in]
*   @param [out] ppt_codeset_list - codeset list info
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_get_codeset_list(DEV_DB_CODESET_LIST_T** ppt_codeset_list);
/**
*   @brief  this fun is used to clean dev codeset list.
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_clean_codeset_list(VOID);
/**
*   @brief  this fun is used to reset bmc query info
*   @param [in]    pt_bmc_query_info  - the bmc slot point
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_reset_bmc_query_info(DEV_DB_BMC_QUERY_T*                pt_bmc_query_info);
/**
*   @brief  this fun is used to stop the bmc task
*   @param [in] 
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_try_to_stop_bmc_task(VOID);

/**
*   @brief  this fun is used to reset bmc query info
*   @param [in]    ui4_dev_view_type  - the dev type idx for view
*   @param [out]  pb_is_dul   - the point for the dual
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_is_dev_type_dul(UINT32   ui4_dev_view_type,BOOL* pb_is_dul);

/**
*   @brief  this fun is used lock the data access for dev db
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_lock(VOID);

/**
*   @brief  this fun is used unlock the data access for dev db
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_unlock(VOID);


/**
*   @brief  this fun is used re-sort the list of bm by puting the 
*              the element with the name ps_dst_str to the first.
*   @param [in]  ui4_num - bm list element num.
*   @param [in]  ps_dst_str - the re-sort base string.
*   @param [in & out] t_bm_list - bm list for re-sort.
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_resort_bm_list_with_str(
                        DEV_DB_BRMD_T* t_bm_list,
                        UINT32         ui4_num,
                        CHAR*          ps_dst_str);

/**
*   @brief  this fun is used to set the flag for banner show or not.
*             the fun only valid when the wifi remote fun enable.
*   @param [in]  b_is_allow_show - bool param, to set the flag for 
*                      banner show or not
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_set_wifi_remote_banner_show_flag( BOOL   b_is_allow_show );

/**
*   @brief  this fun is used to get the flag for banner show or not.
*             if the wifi remote fun have not be enabled, this fun will always 
*             return true, oterwise only return true case is only when the 
*             wifi remote have been ready.
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern BOOL  a_dev_db_get_wifi_remote_banner_show_flag( VOID );

/**
*   @brief  this fun is used to force show banner.
*   @param [in]
*   @param [out]
*   @ return return the error code
*   @return value DEV_DBR_OK       - Routing successful
*   @return value DEV_DBR_INITED - this model alread init
*   @return value DEV_DBR_FAIL     - this model init fail
*   @return value DEV_DB_INV_ARG    - the param is invalid
*/
extern INT32 a_dev_db_show_banner( VOID );

extern UINT16 a_dev_db_get_predef_name_mlm_idx(CHAR *p_name);
extern INT32 a_dev_db_dev_type_name_mapping(CHAR* s_type_name);
#endif /* _A_DEV_DB_CUSTOM_H_ */




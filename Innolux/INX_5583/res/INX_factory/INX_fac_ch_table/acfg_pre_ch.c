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
 * $RCSfile: acfg_pre_ch.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the 
 * application developer. 
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_sb.h"
#include "u_tuner.h"
#include "u_sb_pal_secam_eng.h"

#include "c_cli.h"
#include "c_fm.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "scan_maps/scan_maps.h"

#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/config/_acfg.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "agent/a_agent.h"

#ifdef APP_PRESET_CH_FOR_FAC_SUPPORT
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
extern VOID Printf (const CHAR*  ps_format, ...);

extern INT32 a_cfg_pre_ch_load_preset_channel(VOID);

#define MAX_MACRO_LEN                       (255)
#define MAX_OUTPUT_LEN                      (512) 
#define ATSC_ANA_CH_NUM_AIR                 (68)        
#define ATSC_ANA_CH_NUM_CAB                 (135)
#define FIRST_ANA_CH_NUM_AIR                (2)
#define FIRST_ANA_CH_NUM_CAB                (1)
#define _CHANNEL_INFO_FILE_NAME_            "ch_info.txt"

#define _ACFG_PRE_CH_ANA_INFO_START_AIR_    "\r\nstatic _ACFG_PRE_CH_ANA_INFO at_ana_table_default_air[] =\r\n{" 
#define _ACFG_PRE_CH_DIG_INFO_START_AIR_    "\r\nstatic _ACFG_PRE_CH_DIG_INFO at_dig_table_default_air[] =\r\n{"
#define _ACFG_PRE_CH_ANA_INFO_START_CABLE_  "\r\nstatic _ACFG_PRE_CH_ANA_INFO at_ana_table_default_cable[] =\r\n{" 
#define _ACFG_PRE_CH_DIG_INFO_START_CABLE_  "\r\nstatic _ACFG_PRE_CH_DIG_INFO at_dig_table_default_cable[] =\r\n{"
#define _ACFG_PRE_CH_INFO_END_              "\r\n};\r\n"
#define _ACFG_PRE_CH_ANA_INFO_FMT_          "\r\n\t{%-8d, %-10d, \"%s\", %s, %s} ," 
#define _ACFG_PRE_CH_DIG_INFO_FMT_          "\r\n\t{%-8d, %-10d, %-4d,\"%s\",%s, %-9s, 0x%-04x, 0x%-04x, 0x%-04x, 0x%0-4x, %s} ,"
#define _ACFG_PRE_CH_DEFINED_BY_USER_       ((UINT32)(0xffffffff))      

#define RET_ON_ERR(_expr)      if(_expr != 0){Printf ("<Acfg_pre_ch> ERR: file = %s, line = %d, reason = %d\n\r", __FILE__, __LINE__, _expr); return -1;}
#define BREAK_ON_ERR(_expr)    if(_expr != 0){Printf ("<Acfg_pre_ch> ERR: file = %s, line = %d, reason = %d\n\r", __FILE__, __LINE__, _expr); break ;}
#define CONTINUE_ON_ERR(_expr) if(_expr != 0){Printf ("<Acfg_pre_ch> ERR: file = %s, line = %d, reason = %d\n\r", __FILE__, __LINE__, _expr); continue ;}
#define CHECK_ERR(_expr)       if(_expr != 0){Printf ("<Acfg_pre_ch> ERR: file = %s, line = %d, reason = %d\n\r", __FILE__, __LINE__, _expr);}

typedef struct
{
    UINT32          ui4_ch_val ;    
    UINT32          ui4_freq ;
    CHAR            ps_name [MAX_PROG_NAME_LEN+1] ;
    UINT32          ui4_tv_sys ;
    UINT32          ui4_nw_flag ;
    
} _ACFG_PRE_CH_ANA_INFO;

typedef struct
{
    UINT32          ui4_ch_val ;    
    UINT32          ui4_freq ;
    UINT16          ui2_tsl_rec_id;
    CHAR            ps_name [MAX_PROG_NAME_LEN+1] ;
    TUNER_BANDWIDTH_T   e_bandwidth ;
    TUNER_MODULATION_T  e_mod;
    UINT16          ui2_nw_id ;
    UINT16          ui2_on_id ;
    UINT16          ui2_ts_id ; 
    UINT16          ui2_prog_id ;
    UINT32          ui4_nw_flag ;
    
} _ACFG_PRE_CH_DIG_INFO;

#ifdef CLI_SUPPORT
#define _ACFG_PRE_CH_CLI_REC_MAX_NUM        ((UINT32) 32)

static _ACFG_PRE_CH_ANA_INFO at_g_pre_ch_cli_ana_air_tbl[_ACFG_PRE_CH_CLI_REC_MAX_NUM];
static _ACFG_PRE_CH_DIG_INFO at_g_pre_ch_cli_dig_air_tbl[_ACFG_PRE_CH_CLI_REC_MAX_NUM];
static _ACFG_PRE_CH_ANA_INFO at_g_pre_ch_cli_ana_cab_tbl[_ACFG_PRE_CH_CLI_REC_MAX_NUM];
static _ACFG_PRE_CH_DIG_INFO at_g_pre_ch_cli_dig_cab_tbl[_ACFG_PRE_CH_CLI_REC_MAX_NUM];

static UINT8 ui1_g_pre_ch_cli_ana_air_num = 0;
static UINT8 ui1_g_pre_ch_cli_dig_air_num = 0;
static UINT8 ui1_g_pre_ch_cli_ana_cab_num = 0;
static UINT8 ui1_g_pre_ch_cli_dig_cab_num = 0;


static BOOL  b_g_pre_ch_cli_import = FALSE;
#endif

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
/* air analog channel table for preset channel */
static _ACFG_PRE_CH_ANA_INFO at_ana_table_default_air[] = 
{
    /* channel number / frequency / channel name / tv system / network mask */
    {524416  , 55250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE} ,
    {786560  , 61250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE} ,
    {2621568 , 193250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE} ,
    {2883712 , 199250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE} 
};

/* air digital channel table for preset channel */
static _ACFG_PRE_CH_DIG_INFO at_dig_table_default_air[] = 
{
    /* ch num / requency / tsl rec id / ch name / bandwidth / e_mod / nw id / on id / ts id / prog id / network mask */
    /* this item is not a correct one ,just for passing compair warning ,please replace it with actual data */
    {2359552 , 671000    , 47  ,        "KQED-HD",BW_UNKNOWN, MOD_VSB_8, 0x0   , 0x2f  , 0x17f , 0x3   , SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE}
};

/* cable analog channel table for preset channel */
static _ACFG_PRE_CH_ANA_INFO at_ana_table_default_cable[] = 
{
    /* channel number / frequency / channel name / tv system / network mask */
    /* this item is not a correct one ,just for passing compair warning ,please replace it with actual data */   
    {    0  ,            0     ,        "",    TV_SYS_MASK_NONE , SB_VNET_ALL}
} ;

/* cable digital channel table for preset channel */
static _ACFG_PRE_CH_DIG_INFO at_dig_table_default_cable[] = 
{
    /* ch num / requency / tsl rec id / ch name / bandwidth / e_mod / nw id / on id / ts id / prog id / network mask */
    /* this item is not a correct one ,just for passing compair warning ,please replace it with actual data */   
    {2359552 , 671000    , 47  ,"KQED-HD",BW_UNKNOWN, MOD_VSB_8, 0x0   , 0x2f  , 0x17f , 0x3   , SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE}
} ;

/*-----------------------------------------------------------------------------
                    internal functions declarations
-----------------------------------------------------------------------------*/
static INT32 _open_file         (
    RMV_DEV_OPEN_ID_T*          pe_open_id ,
    HANDLE_T*                   ph_file
    ) ;

static INT32 _save_to_file      (
    HANDLE_T                    h_file ,
    UINT8*                      pui1_file_data ,
    UINT32                      ui4_file_data_len
    ) ;

static INT32 _close_file        (
    RMV_DEV_OPEN_ID_T           e_open_id ,
    HANDLE_T                    h_file
    ) ;

#if 0
/* just for division */
#endif

/*-----------------------------------------------------------------------------
 * Name: _fill_with_fake_ch
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _fill_with_fake_ch (
    BOOL                        b_cable ,
    _ACFG_PRE_CH_ANA_INFO**     ppt_ana_data ,
    UINT16*                     pui2_ana_size
    )
{
#ifndef APP_DVBT_SUPPORT        /* atsc */
    const static _ACFG_PRE_CH_ANA_INFO at_ana_table_templet_cable[ATSC_ANA_CH_NUM_CAB] =
    {
        /* channel id / frequency / channel name / tv system / network mask */
        {262272  , 73250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {524416  , 55250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {786560  , 61250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1048704 , 67250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1310848 , 79250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1572992 , 85250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1835136 , 175250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2097280 , 181250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2359424 , 187250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2621568 , 193250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2883712 , 199250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3145856 , 205250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3408000 , 211250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3670144 , 121250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3932288 , 127250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4194432 , 133250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4456576 , 139250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4718720 , 145250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4980864 , 151250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {5243008 , 157250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {5505152 , 163250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {5767296 , 169250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6029440 , 217250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6291584 , 223250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6553728 , 229250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6815872 , 235250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7078016 , 241250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7340160 , 247250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7602304 , 253250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7864448 , 259250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8126592 , 265250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8388736 , 271250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8650880 , 277250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8913024 , 283250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9175168 , 289250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9437312 , 295250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9699456 , 301250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9961600 , 307250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {10223744, 313250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {10485888, 319250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {10748032, 325250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11010176, 331250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11272320, 337250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11534464, 343250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11796608, 349250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12058752, 355250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12320896, 361250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12583040, 367250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12845184, 373250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13107328, 379250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13369472, 385250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13631616, 391250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13893760, 397250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14155904, 403250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14418048, 409250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14680192, 415250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14942336, 421250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15204480, 427250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15466624, 433250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15728768, 439250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15990912, 445250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {16253056, 451250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {16515200, 457250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {16777344, 463250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17039488, 469250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17301632, 475250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17563776, 481250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17825920, 487250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {18088064, 493250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {18350208, 499250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {18612352, 505250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {18874496, 511250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {19136640, 517250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {19398784, 523250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {19660928, 529250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {19923072, 535250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {20185216, 541250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {20447360, 547250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {20709504, 553250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {20971648, 559250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {21233792, 565250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {21495936, 571250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {21758080, 577250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {22020224, 583250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {22282368, 589250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {22544512, 595250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {22806656, 601250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {23068800, 607250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {23330944, 613250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {23593088, 619250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {23855232, 625250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {24117376, 631250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {24379520, 637250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {24641664, 643250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {24903808, 91250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {25165952, 97250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {25428096, 103250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {25690240, 109250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {25952384, 115250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {26214528, 649250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {26476672, 655250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {26738816, 661250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {27000960, 667250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {27263104, 673250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {27525248, 679250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {27787392, 685250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {28049536, 691250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {28311680, 697250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {28573824, 703250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {28835968, 709250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {29098112, 715250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {29360256, 721250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {29622400, 727250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {29884544, 733250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {30146688, 739250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {30408832, 745250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {30670976, 751250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {30933120, 757250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {31195264, 763250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {31457408, 769250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {31719552, 775250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {31981696, 781250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {32243840, 787250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {32505984, 793250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {32768128, 799250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {33030272, 805250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {33292416, 811250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {33554560, 817250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {33816704, 823250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {34078848, 829250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {34340992, 835250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {34603136, 841250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {34865280, 847250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {35127424, 853250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {35389568, 859250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
    };
    
    /* channel number / frequency / channel name / tv system / set as fake */
    const static _ACFG_PRE_CH_ANA_INFO at_ana_table_templet_air[ATSC_ANA_CH_NUM_AIR] =
    {
        {524416  , 55250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {786560  , 61250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1048704 , 67250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1310848 , 77250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1572992 , 83250     , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {1835136 , 175250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2097280 , 181250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2359424 , 187250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2621568 , 193250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {2883712 , 199250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3145856 , 205250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3408000 , 211250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3670144 , 471250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {3932288 , 477250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4194432 , 483250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4456576 , 489250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4718720 , 495250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {4980864 , 501250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {5243008 , 507250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {5505152 , 513250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {5767296 , 519250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6029440 , 525250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6291584 , 531250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6553728 , 537250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {6815872 , 543250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7078016 , 549250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7340160 , 555250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7602304 , 561250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {7864448 , 567250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8126592 , 573250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8388736 , 579250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8650880 , 585250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {8913024 , 591250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9175168 , 597250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9437312 , 603250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9699456 , 609250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {9961600 , 615250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {10223744, 621250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {10485888, 627250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {10748032, 633250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11010176, 639250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11272320, 645250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11534464, 651250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {11796608, 657250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12058752, 663250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12320896, 669250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12583040, 675250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {12845184, 681250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13107328, 687250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13369472, 693250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13631616, 699250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {13893760, 705250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14155904, 711250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14418048, 717250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14680192, 723250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {14942336, 729250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15204480, 735250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15466624, 741250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15728768, 747250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {15990912, 753250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {16253056, 759250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {16515200, 765250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {16777344, 771250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17039488, 777250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17301632, 783250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17563776, 789250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {17825920, 795250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
        {18088064, 801250    , "", TV_SYS_MASK_NONE, SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_FAKE} ,    /* fake channel info for atsc */
    };

    
    static _ACFG_PRE_CH_ANA_INFO  at_ana_table_temp[ATSC_ANA_CH_NUM_CAB] ;
    UINT32                        ui4_ch_num = 0 ;
    _ACFG_PRE_CH_ANA_INFO*      pt_ana_data = NULL ;
    UINT16                      ui2_ana_size = NULL ;
    UINT32                      ui4_where_to_put = 0 ;

    if (!ppt_ana_data || !pui2_ana_size)
    {
        return APP_CFGR_INV_ARG ;
    }
    
    pt_ana_data = *ppt_ana_data ;
    ui2_ana_size = *pui2_ana_size ;
    
    c_memset (at_ana_table_temp ,0 ,sizeof (at_ana_table_temp)) ;
    
    if (b_cable)
    {   
        c_memcpy (at_ana_table_temp ,at_ana_table_templet_cable ,sizeof (at_ana_table_templet_cable)) ;
    }
    else
    {   
        c_memcpy (at_ana_table_temp ,at_ana_table_templet_air ,sizeof (at_ana_table_templet_air)) ;
    }

    while (ui2_ana_size && pt_ana_data)
    {
        if (_ACFG_PRE_CH_DEFINED_BY_USER_ != pt_ana_data->ui4_nw_flag)
        {
            ui4_ch_num = SB_ATSC_GET_MAJOR_CHANNEL_NUM (pt_ana_data->ui4_ch_val) ;
        }
        else
        {
            ui4_ch_num = pt_ana_data->ui4_ch_val ;
        }
        
        ui4_where_to_put = (b_cable)
                        ? ui4_ch_num - FIRST_ANA_CH_NUM_CAB
                        : ui4_ch_num - FIRST_ANA_CH_NUM_AIR ;

        if (ui4_where_to_put >= ATSC_ANA_CH_NUM_CAB)
        {
            /* out of the range */
            CHECK_ERR (APP_CFGR_INTERNAL_ERR) ;
            continue ;
        }

        c_memcpy (&at_ana_table_temp[ui4_where_to_put] ,pt_ana_data ,sizeof (_ACFG_PRE_CH_ANA_INFO)) ;

        ui2_ana_size -- ;
        pt_ana_data ++ ;
    }

    *ppt_ana_data  = at_ana_table_temp ;
    *pui2_ana_size = (b_cable) ? (UINT16)ATSC_ANA_CH_NUM_CAB : (UINT16)ATSC_ANA_CH_NUM_AIR ;
    
#endif  /* APP_DVBT_SUPPORT */

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _prepare_data
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _prepare_data (
    CHAR*                       ps_area ,
    BOOL                        b_cable ,
    HANDLE_T*                   ph_tsl ,
    HANDLE_T*                   ph_svl ,
    CHAR**                      pps_tsl_path ,
    CHAR**                      pps_svl_path ,
    UINT16*                     pui2_tsl_id ,
    UINT16*                     pui2_svl_id ,
    UINT16*                     pui2_ana_size ,
    UINT16*                     pui2_dig_size ,
    _ACFG_PRE_CH_ANA_INFO**     ppt_ana_data ,
    _ACFG_PRE_CH_DIG_INFO**     ppt_dig_data
    )
{
    if (!ph_tsl        || !ph_svl       || !pps_tsl_path  || 
        !pui2_tsl_id   || !pui2_svl_id  || !pui2_dig_size || 
        !pui2_ana_size || !ppt_dig_data || !ppt_ana_data  || !pps_svl_path)
    {
        return APP_CFGR_INV_ARG ;
    }
    
    /* Area translate and check */
    if (!ps_area)
    {
        if (b_cable)
        {   
            *ph_tsl        = h_g_acfg_tsl_cable ;
            *ph_svl        = h_g_acfg_svl_cable ;
            *pps_tsl_path  = ATSC_CABLE_TSL_FILE;
            *pps_svl_path  = ATSC_CABLE_SVL_FILE ;
            *pui2_tsl_id   = ATSC_CABLE_TSL_ID ;
            *pui2_svl_id   = ATSC_CABLE_SVL_ID ;
#ifdef CLI_SUPPORT
            if (b_g_pre_ch_cli_import)
            {
                *pui2_ana_size = ui1_g_pre_ch_cli_ana_cab_num;
                *pui2_dig_size = ui1_g_pre_ch_cli_dig_cab_num;
                *ppt_ana_data  = at_g_pre_ch_cli_ana_cab_tbl ;
                *ppt_dig_data  = at_g_pre_ch_cli_dig_cab_tbl ;
            }
            else
            {
                if (sizeof(at_ana_table_default_cable) && at_ana_table_default_cable[0].ui4_ch_val)
                {
                    *pui2_ana_size = (UINT16)(sizeof(at_ana_table_default_cable)/sizeof(at_ana_table_default_cable[0])) ;
                }
                else
                {
                    *pui2_ana_size = 0 ;
                }
                
                if (sizeof(at_dig_table_default_cable) && at_dig_table_default_cable[0].ui4_ch_val)
                {
                    *pui2_dig_size = (UINT16)(sizeof(at_dig_table_default_cable)/sizeof(at_dig_table_default_cable[0])) ;
                }
                else
                {
                    *pui2_dig_size = 0 ;
                }

            *ppt_ana_data  = at_ana_table_default_cable ;
            *ppt_dig_data  = at_dig_table_default_cable ;
        }
#else
            if (sizeof(at_ana_table_default_cable) && at_ana_table_default_cable[0].ui4_ch_val)
            {
                *pui2_ana_size = (UINT16)(sizeof(at_ana_table_default_cable)/sizeof(at_ana_table_default_cable[0])) ;
            }
            else
            {
                *pui2_ana_size = 0 ;
            }
            
            if (sizeof(at_dig_table_default_cable) && at_dig_table_default_cable[0].ui4_ch_val)
            {
                *pui2_dig_size = (UINT16)(sizeof(at_dig_table_default_cable)/sizeof(at_dig_table_default_cable[0])) ;
            }
            else
            {
                *pui2_dig_size = 0 ;
            }
            
            *ppt_ana_data  = at_ana_table_default_cable ;
            *ppt_dig_data  = at_dig_table_default_cable ;
#endif
        }
        else
        {   
            *ph_tsl        = h_g_acfg_tsl_air ;
            *ph_svl        = h_g_acfg_svl_air ;
            *pps_tsl_path  = ATSC_TRSTRL_TSL_FILE;
            *pps_svl_path  = ATSC_TRSTRL_SVL_FILE ;
            *pui2_tsl_id   = ATSC_TRSTRL_TSL_ID ;
            *pui2_svl_id   = ATSC_TRSTRL_SVL_ID ;
#ifdef CLI_SUPPORT
            if (b_g_pre_ch_cli_import)
            {
                *pui2_ana_size = ui1_g_pre_ch_cli_ana_air_num;
                *pui2_dig_size = ui1_g_pre_ch_cli_dig_air_num;
                *ppt_ana_data  = at_g_pre_ch_cli_ana_air_tbl ;
                *ppt_dig_data  = at_g_pre_ch_cli_dig_air_tbl ;
            }
            else
            {
                if (sizeof(at_ana_table_default_air) && at_ana_table_default_air[0].ui4_ch_val)
                {
                    *pui2_ana_size = (UINT16)(sizeof(at_ana_table_default_air)/sizeof(at_ana_table_default_air[0])) ;
                }
                else
                {
                    *pui2_ana_size = 0 ;
                }
                
                if (sizeof(at_dig_table_default_air) && at_dig_table_default_air[0].ui4_ch_val)
                {
                    *pui2_dig_size = (UINT16)(sizeof(at_dig_table_default_air)/sizeof(at_dig_table_default_air[0])) ;
                }
                else
                {
                    *pui2_dig_size = 0 ;
                }

                *ppt_ana_data  = at_ana_table_default_air ;
                *ppt_dig_data  = at_dig_table_default_air ;
            }
#else
            if (sizeof(at_ana_table_default_air) && at_ana_table_default_air[0].ui4_ch_val)
            {
                *pui2_ana_size = (UINT16)(sizeof(at_ana_table_default_air)/sizeof(at_ana_table_default_air[0])) ;
            }
            else
            {
                *pui2_ana_size = 0 ;
            }
            
            if (sizeof(at_dig_table_default_air) && at_dig_table_default_air[0].ui4_ch_val)
            {
                *pui2_dig_size = (UINT16)(sizeof(at_dig_table_default_air)/sizeof(at_dig_table_default_air[0])) ;
            }
            else
            {
                *pui2_dig_size = 0 ;
            }
            
            *ppt_ana_data  = at_ana_table_default_air ;
            *ppt_dig_data  = at_dig_table_default_air ;
#endif
        }

        CHECK_ERR (_fill_with_fake_ch (b_cable ,ppt_ana_data ,pui2_ana_size)) ;
    }
    else 
    {
        return APP_CFGR_NOT_SUPPORT ;
    }

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _gen_ch_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT32 _gen_ch_id (
    BOOL                        b_digital ,
    BOOL                        b_defined_by_enduser ,
    UINT32                      ui4_val
    )
{
    if (b_defined_by_enduser)
    {
#ifdef APP_DVBT_SUPPORT
    return (SB_DVB_GEN_CHANNEL_ID (ui4_val,0)) ;
#else
    return ((b_digital) 
            ? SB_ATSC_GEN_CHANNEL_ID(ui4_val ,0 ,0) 
            : SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_val ,0)) ;
#endif
    }
    else
    {
        return ui4_val ;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _gen_nw_mask
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT32 _gen_nw_mask (
    UINT32                      ui4_val
    )
{
    if (_ACFG_PRE_CH_DEFINED_BY_USER_ == ui4_val)
    {
        return (SB_VNET_ALL|SB_VNET_ACTIVE|SB_VNET_EPG|SB_VNET_VISIBLE) ;
    }
    else
    {
        return ui4_val ;
    }
}
#if 0
/*-----------------------------------------------------------------------------
 * Name: _get_tsl_rec_id_by_freq
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_tsl_rec_id_by_freq(UINT32 ui4_freq)
{
    return (UINT16)(ui4_freq  / 6000000) ;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _get_macro_bandwidth
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _get_macro_bandwidth (
    TUNER_BANDWIDTH_T           e_bandwidth, 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return APP_CFGR_INV_ARG ;
    }

    ps_macro[0] = '\0' ;

    switch (e_bandwidth)
    {
    case BW_6_MHz :
        c_strcpy (ps_macro ,"BW_6_MHz") ;
    break ;

    case BW_7_MHz :
        c_strcpy (ps_macro ,"BW_7_MHz") ;
    break ;

    case BW_8_MHz :
        c_strcpy (ps_macro ,"BW_8_MHz") ;
    break ;

    case BW_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"BW_UNKNOWN") ;
    break ;
    }

    return APP_CFGR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name: _get_macro_bandwidth
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _get_macro_tuner_mod (
    TUNER_MODULATION_T          e_mod, 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return APP_CFGR_INV_ARG ;
    }

    ps_macro[0] = '\0' ;

    switch (e_mod)
    {
    case MOD_PSK_8 :
        c_strcpy (ps_macro ,"MOD_PSK_8") ;
    break ;

    case MOD_VSB_8 :
        c_strcpy (ps_macro ,"MOD_VSB_8") ;
    break ;

    case MOD_VSB_16 :
        c_strcpy (ps_macro ,"MOD_VSB_16") ;
    break ;

    case MOD_QAM_16 :
        c_strcpy (ps_macro ,"MOD_QAM_16") ;
    break ;

    case MOD_QAM_32 :
        c_strcpy (ps_macro ,"MOD_QAM_32") ;
    break ;

    case MOD_QAM_64 :
        c_strcpy (ps_macro ,"MOD_QAM_64") ;
    break ;

    case MOD_QAM_80 :
        c_strcpy (ps_macro ,"MOD_QAM_80") ;
    break ;

    case MOD_QAM_96 :
        c_strcpy (ps_macro ,"MOD_QAM_96") ;
    break ;

    case MOD_QAM_112 :
        c_strcpy (ps_macro ,"MOD_QAM_112") ;
    break ;

    case MOD_QAM_128 :
        c_strcpy (ps_macro ,"MOD_QAM_128") ;
    break ;

    case MOD_QAM_160 :
        c_strcpy (ps_macro ,"MOD_QAM_160") ;
    break ;

    case MOD_QAM_192 :
        c_strcpy (ps_macro ,"MOD_QAM_192") ;
    break ;

    case MOD_QAM_224 :
        c_strcpy (ps_macro ,"MOD_QAM_224") ;
    break ;

    case MOD_QAM_256 :
        c_strcpy (ps_macro ,"MOD_QAM_256") ;
    break ;

    case MOD_QAM_320 :
        c_strcpy (ps_macro ,"MOD_QAM_320") ;
    break ;

    case MOD_QAM_384 :
        c_strcpy (ps_macro ,"MOD_QAM_384") ;
    break ;

    case MOD_QAM_448 :
        c_strcpy (ps_macro ,"MOD_QAM_448") ;
    break ;

    case MOD_QAM_512 :
        c_strcpy (ps_macro ,"MOD_QAM_512") ;
    break ;

    case MOD_QAM_640 :
        c_strcpy (ps_macro ,"MOD_QAM_640") ;
    break ;

    case MOD_QAM_768 :
        c_strcpy (ps_macro ,"MOD_QAM_768") ;
    break ;

    case MOD_QAM_896 :
        c_strcpy (ps_macro ,"MOD_QAM_896") ;
    break ;

    case MOD_QAM_1024 :
        c_strcpy (ps_macro ,"MOD_QAM_1024") ;
    break ;

    case MOD_QPSK :
        c_strcpy (ps_macro ,"MOD_QPSK") ;
    break ;

    case MOD_OQPSK :
        c_strcpy (ps_macro ,"MOD_OQPSK") ;
    break ;

    case MOD_BPSK :
        c_strcpy (ps_macro ,"MOD_BPSK") ;
    break ;

    case MOD_VSB_AM :
        c_strcpy (ps_macro ,"MOD_VSB_AM") ;
    break ;

    case MOD_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"MOD_UNKNOWN") ;
    break ;
    }

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_tv_sys
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _get_macro_tv_sys (
    UINT32                      ui4_tv_sys, 
    CHAR*                       ps_macro
    )
{
    UINT8  ui1_idx = 0 ;
    CHAR   ps_tmp[25] = {0} ;
    
    if (!ps_macro)
    {
        return APP_CFGR_INV_ARG ;
    }

    ps_macro[0] = '\0' ;

    for (ui1_idx = 0 ;ui4_tv_sys ;ui1_idx ++ ,ui4_tv_sys >>= 1)
    {
        if (0 == (ui4_tv_sys & 1))
        {
            continue ;
        }
        
        ps_tmp[0] = '\0' ;

        switch (ui1_idx)
        {   
        case TV_SYS_A:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_A|") ;
            break ;
        case TV_SYS_B:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_B|") ;
            break ;
        case TV_SYS_C:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_C|") ;
            break ;
        case TV_SYS_D:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_D|") ;
            break ;
        case TV_SYS_E:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_E|") ;
            break ;
        case TV_SYS_F:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_F|") ;
            break ;
        case TV_SYS_G:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_G|") ;
            break ;
        case TV_SYS_H:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_H|") ;
            break ;
        case TV_SYS_I:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_I|") ;
            break ;
        case TV_SYS_J:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_J|") ;
            break ;
        case TV_SYS_K:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_K|") ;
            break ;
        case TV_SYS_K_PRIME:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_K_PRIME|") ;
            break ;
        case TV_SYS_L:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_L|") ;
            break ;
        case TV_SYS_L_PRIME:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_L_PRIME|") ;
            break ;
        case TV_SYS_M:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_M|") ;
            break ;
        case TV_SYS_N:
            c_strcpy (ps_tmp ,"TV_SYS_MASK_N|") ;
            break ;
        default :
            /* unknown */
            break ;
        }

        if (c_strlen (ps_macro) + c_strlen (ps_tmp) >= MAX_MACRO_LEN)
        {
            /* out of the range */
            break ;
        }

        c_strcat (ps_macro ,ps_tmp) ;
        
    }

    if (ps_macro[0] == '\0')
    {
        /* ui4_tv_sys == 0 || unknown tv sys */
        c_strcpy (ps_macro ,"TV_SYS_MASK_NONE") ;
    }
    else
    {   
        /* remove the last '|' */
        ps_macro[c_strlen (ps_macro) -1] = '\0' ;
    }

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_nw_mask
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _get_macro_nw_mask (
    UINT32                      ui4_nw_mask, 
    CHAR*                       ps_macro
    )
{
    UINT8  ui1_idx = 0 ;
    CHAR   ps_tmp[25] = {0} ;
    
    if (!ps_macro)
    {
        return APP_CFGR_INV_ARG ;
    }

    ps_macro[0] = '\0' ;

    for (ui1_idx = 0 ;ui4_nw_mask ;ui1_idx ++ ,ui4_nw_mask >>= 1)
    {
        if (0 == (ui4_nw_mask & 1))
        {
            continue ;
        }
        
        ps_tmp[0] = '\0' ;

        switch (ui1_idx)
        {   
        case 0:
            c_strcpy (ps_tmp ,"SB_VNET_ALL|") ;
            break ;
        case 1:
            c_strcpy (ps_tmp ,"SB_VNET_ACTIVE|") ;
            break ;
        case 2:
            c_strcpy (ps_tmp ,"SB_VNET_EPG|") ;
            break ;
        case 3:
            c_strcpy (ps_tmp ,"SB_VNET_VISIBLE|") ;
            break ;
        case 4:
            c_strcpy (ps_tmp ,"SB_VNET_FAVORITE1|") ;
            break ;
        case 5:
            c_strcpy (ps_tmp ,"SB_VNET_FAVORITE2|") ;
            break ;
        case 6:
            c_strcpy (ps_tmp ,"SB_VNET_FAVORITE3|") ;
            break ;
        case 7:
            c_strcpy (ps_tmp ,"SB_VNET_FAVORITE4|") ;
            break ;
        case 8:
            c_strcpy (ps_tmp ,"SB_VNET_BLOCKED|") ;
            break ;
        case 9:
            c_strcpy (ps_tmp ,"SB_VNET_OOB_LIST|") ;
            break ;
        case 10:
            c_strcpy (ps_tmp ,"SB_VNET_INB_LIST|") ;
            break ;
        case 11:
            c_strcpy (ps_tmp ,"SB_VNET_SCRAMBLED|") ;
            break ;
        case 12:
            c_strcpy (ps_tmp ,"SB_VNET_BACKUP1|") ;
            break ;
        case 13:
            c_strcpy (ps_tmp ,"SB_VNET_BACKUP2|") ;
            break ;
        case 14:
            c_strcpy (ps_tmp ,"SB_VNET_BACKUP3|") ;
            break ;
        case 15:
            c_strcpy (ps_tmp ,"SB_VNET_FAKE|") ;
            break ;
        case 16:
            c_strcpy (ps_tmp ,"SB_VNET_USER_TMP_UNLOCK|") ;
            break ;
        case 17:
            c_strcpy (ps_tmp ,"SB_VNET_CH_NAME_EDITED|") ;
            break ;
        case 18:
            c_strcpy (ps_tmp ,"SB_VNET_LCN_APPLIED|") ;
            break ;
        case 19:
            c_strcpy (ps_tmp ,"SB_VNET_USE_DECODER|") ;
            break ;
        case 20:
            c_strcpy (ps_tmp ,"SB_VNET_ACTIVE_EPG_EDITED|") ;
            break ;
        case 21:
            c_strcpy (ps_tmp ,"SB_VNET_FREQ_EDITED|") ;
            break ;
        case 22:
            c_strcpy (ps_tmp ,"SB_VNET_REMOVAL|") ;
            break ;
        case 23:
            c_strcpy (ps_tmp ,"SB_VNET_REMOVAL_TO_CONFIRM|") ;
            break ;
        case 24:
            c_strcpy (ps_tmp ,"SB_VNET_USER_INDEX_BGN|") ;
            break ;
        case 31:
            c_strcpy (ps_tmp ,"SB_VNET_USER_INDEX_END|") ;
            break ;
        default :
            /* unknown */
            break ;
        }

        if (c_strlen (ps_macro) + c_strlen (ps_tmp) >= MAX_MACRO_LEN)
        {
            /* out of the range */
            break ;
        }

        c_strcat (ps_macro ,ps_tmp) ;
        
    }

    if (ps_macro[0] == '\0')
    {
        /* ui4_nw_mask == 0 || unknown tv sys */
        c_strcpy (ps_macro ,"SB_VNET_ALL") ;
    }
    else
    {   
        /* remove the last '|' */
        ps_macro[c_strlen (ps_macro) -1] = '\0' ;
    }

    return APP_CFGR_OK ;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name: _get_macro_bcst_medium
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _get_macro_bcst_medium (
    BRDCST_MEDIUM_T             e_bcst_medium , 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return ;
    }

    ps_macro[0] = '\0' ;

    switch (e_bcst_medium)
    {
    case BRDCST_MEDIUM_DIG_TERRESTRIAL :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_DIG_TERRESTRIAL") ;
    break ;
    
    case BRDCST_MEDIUM_DIG_CABLE :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_DIG_CABLE") ;
    break ;

    case BRDCST_MEDIUM_DIG_SATELLITE :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_DIG_SATELLITE") ;
    break ;

    case BRDCST_MEDIUM_ANA_TERRESTRIAL :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_ANA_TERRESTRIAL") ;
    break ;

    case BRDCST_MEDIUM_ANA_CABLE :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_ANA_CABLE") ;
    break ;

    case BRDCST_MEDIUM_ANA_SATELLITE :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_ANA_SATELLITE") ;
    break ;

    case BRDCST_MEDIUM_1394 :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_1394") ;
    break ;

    case BRDCST_MEDIUM_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"BRDCST_MEDIUM_UNKNOWN") ;
    break ;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_pol
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _get_macro_pol (
    TUNER_POLARIZATION_T        e_pol , 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return ;
    }

    ps_macro[0] = '\0' ;

    switch (e_pol)
    {
    case POL_LIN_HORIZONTAL :
        c_strcpy (ps_macro ,"POL_LIN_HORIZONTAL") ;
    break ;
    
    case POL_LIN_VERTICAL :
        c_strcpy (ps_macro ,"POL_LIN_VERTICAL") ;
    break ;

    case POL_CIR_LEFT :
        c_strcpy (ps_macro ,"POL_CIR_LEFT") ;
    break ;

    case POL_CIR_RIGHT :
        c_strcpy (ps_macro ,"POL_CIR_RIGHT") ;
    break ;

    case POL_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"POL_UNKNOWN") ;
    break ;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_mod
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _get_macro_mod (
    TUNER_MODULATION_T          e_mod , 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return ;
    }

    ps_macro[0] = '\0' ;

    switch (e_mod)
    {
    case MOD_PSK_8 :
        c_strcpy (ps_macro ,"MOD_PSK_8") ;
    break ;
    
    case MOD_VSB_8 :
        c_strcpy (ps_macro ,"MOD_VSB_8") ;
    break ;
    
    case MOD_VSB_16 :
        c_strcpy (ps_macro ,"MOD_VSB_16") ;
    break ;
    
    case MOD_QAM_16 :
        c_strcpy (ps_macro ,"MOD_QAM_16") ;
    break ;
    
    case MOD_QAM_32 :
        c_strcpy (ps_macro ,"MOD_QAM_32") ;
    break ;
    
    case MOD_QAM_64 :
        c_strcpy (ps_macro ,"MOD_QAM_64") ;
    break ;
    
    case MOD_QAM_80 :
        c_strcpy (ps_macro ,"MOD_QAM_80") ;
    break ;
    
    case MOD_QAM_96 :
        c_strcpy (ps_macro ,"MOD_QAM_96") ;
    break ;
    
    case MOD_QAM_112 :
        c_strcpy (ps_macro ,"MOD_QAM_112") ;
    break ;
    
    case MOD_QAM_128 :
        c_strcpy (ps_macro ,"MOD_QAM_128") ;
    break ;
    
    case MOD_QAM_160 :
        c_strcpy (ps_macro ,"MOD_QAM_160") ;
    break ;
    
    case MOD_QAM_192 :
        c_strcpy (ps_macro ,"MOD_QAM_192") ;
    break ;
    
    case MOD_QAM_224 :
        c_strcpy (ps_macro ,"MOD_QAM_224") ;
    break ;
    
    case MOD_QAM_256 :
        c_strcpy (ps_macro ,"MOD_QAM_256") ;
    break ;
    
    case MOD_QAM_320 :
        c_strcpy (ps_macro ,"MOD_QAM_320") ;
    break ;
    
    case MOD_QAM_384 :
        c_strcpy (ps_macro ,"MOD_QAM_384") ;
    break ;
    
    case MOD_QAM_448 :
        c_strcpy (ps_macro ,"MOD_QAM_448") ;
    break ;
    
    case MOD_QAM_512 :
        c_strcpy (ps_macro ,"MOD_QAM_512") ;
    break ;
    
    case MOD_QAM_640 :
        c_strcpy (ps_macro ,"MOD_QAM_640") ;
    break ;
    
    case MOD_QAM_768 :
        c_strcpy (ps_macro ,"MOD_QAM_768") ;
    break ;
    
    case MOD_QAM_896 :
        c_strcpy (ps_macro ,"MOD_QAM_896") ;
    break ;
    
    case MOD_QAM_1024 :
        c_strcpy (ps_macro ,"MOD_QAM_1024") ;
    break ;
    
    case MOD_QPSK :
        c_strcpy (ps_macro ,"MOD_QPSK") ;
    break ;
    
    case MOD_OQPSK :
        c_strcpy (ps_macro ,"MOD_OQPSK") ;
    break ;
    
    case MOD_BPSK :
        c_strcpy (ps_macro ,"MOD_BPSK") ;
    break ;
    
    case MOD_VSB_AM :
        c_strcpy (ps_macro ,"MOD_VSB_AM") ;
    break ;
    
    case MOD_QAM_4_NR :
        c_strcpy (ps_macro ,"MOD_QAM_4_NR") ;
    break ;
        
    case MOD_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"MOD_UNKNOWN") ;
    break ;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_bcst_type
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _get_macro_bcst_type (
    BRDCST_TYPE_T               e_bcst_type , 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return ;
    }

    ps_macro[0] = '\0' ;

    switch (e_bcst_type)
    {
    case BRDCST_TYPE_ANALOG :
        c_strcpy (ps_macro ,"BRDCST_TYPE_ANALOG") ;
    break ;
    
    case BRDCST_TYPE_DVB :
        c_strcpy (ps_macro ,"BRDCST_TYPE_DVB") ;
    break ;

    case BRDCST_TYPE_ATSC :
        c_strcpy (ps_macro ,"BRDCST_TYPE_ATSC") ;
    break ;

    case BRDCST_TYPE_SCTE :
        c_strcpy (ps_macro ,"BRDCST_TYPE_SCTE") ;
    break ;

    case BRDCST_TYPE_ISDB :
        c_strcpy (ps_macro ,"BRDCST_TYPE_ISDB") ;
    break ;

    case BRDCST_TYPE_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"BRDCST_TYPE_UNKNOWN") ;
    break ;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_serv_type
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _get_macro_serv_type (
    SVL_SERVICE_TYPE_T          e_serv_type , 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return ;
    }

    ps_macro[0] = '\0' ;

    switch (e_serv_type)
    {
    case SVL_SERVICE_TYPE_TV :
        c_strcpy (ps_macro ,"SVL_SERVICE_TYPE_TV") ;
    break ;
    
    case SVL_SERVICE_TYPE_RADIO :
        c_strcpy (ps_macro ,"SVL_SERVICE_TYPE_RADIO") ;
    break ;

    case SVL_SERVICE_TYPE_APP :
        c_strcpy (ps_macro ,"SVL_SERVICE_TYPE_APP") ;
    break ;

    case SVL_SERVICE_TYPE_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"SVL_SERVICE_TYPE_UNKNOWN") ;
    break ;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _get_macro_colr_sys
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _get_macro_colr_sys (
    COLOR_SYS_T                 e_colr_sys , 
    CHAR*                       ps_macro
    )
{
    if (!ps_macro)
    {
        return ;
    }

    ps_macro[0] = '\0' ;

    switch (e_colr_sys)
    {
    case COLOR_SYS_NTSC :
        c_strcpy (ps_macro ,"COLOR_SYS_NTSC") ;
    break ;
    
    case COLOR_SYS_PAL :
        c_strcpy (ps_macro ,"COLOR_SYS_PAL") ;
    break ;

    case COLOR_SYS_SECAM :
        c_strcpy (ps_macro ,"COLOR_SYS_SECAM") ;
    break ;

    case COLOR_SYS_NTSC_443 :
        c_strcpy (ps_macro ,"COLOR_SYS_NTSC_443") ;
    break ;

    case COLOR_SYS_PAL_M :
        c_strcpy (ps_macro ,"COLOR_SYS_PAL_M") ;
    break ;

    case COLOR_SYS_PAL_N :
        c_strcpy (ps_macro ,"COLOR_SYS_PAL_N,") ;
    break ;

    case COLOR_SYS_PAL_60 :
        c_strcpy (ps_macro ,"COLOR_SYS_PAL_60") ;
    break ;

    case COLOR_SYS_UNKNOWN :
    default :
        c_strcpy (ps_macro ,"COLOR_SYS_UNKNOWN") ;
    break ;
    }

}
#endif

/*-----------------------------------------------------------------------------
 * Name: _output_content
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _output_content (
    HANDLE_T                    h_file ,
    CHAR*                       ps_content
    )
{
    CHAR                        s_buff[MAX_OUTPUT_LEN] = {0} ;

    if (ps_content)
    {
        c_memcpy (s_buff, ps_content, MAX_OUTPUT_LEN -1) ;
    }   

    if (h_file)
    {
        /* write to usb file */
        CHECK_ERR (_save_to_file (h_file ,(UINT8*)s_buff ,c_strlen (s_buff))) ;
    }
    else
    {
        /* output to terminal */
        Printf ("%s",s_buff) ;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _open_file
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _open_file (
    RMV_DEV_OPEN_ID_T*          pe_open_id ,
    HANDLE_T*                   ph_file
    )
{
    /* Check USB applicable. */
    CHAR                        s_mount_point[512]   = {0};
    SIZE_T                      t_mount_point_size   = 511;
    CHAR                        s_filename[512 + 64] = {0};
    UINT32                      ui4_usb_idx = 0 ;

    if (!ph_file || !pe_open_id)
    {
        RET_ON_ERR (APP_CFGR_INV_ARG) ; 
    }
    
    /* Get current active mount point */
    RET_ON_ERR (a_rmv_dev_get_active_mnt_pnt(
                                &ui4_usb_idx, 
                                &t_mount_point_size, 
                                s_mount_point));

    /* Open mount point */
    RET_ON_ERR (a_rmv_dev_open_mnt_point (ui4_usb_idx, pe_open_id)) ;

    /* Determine the final file name */
    c_sprintf(s_filename,"%s/"_CHANNEL_INFO_FILE_NAME_,s_mount_point);

    /* open the target file */
    RET_ON_ERR (c_fm_open(FM_ROOT_HANDLE,
                               (const CHAR*) s_filename,
                               FM_READ_WRITE | FM_OPEN_CREATE | FM_OPEN_TRUNC,
                               0777,
                               FALSE,
                               ph_file)) ;

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _save_to_file
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _save_to_file (
    HANDLE_T                    h_file ,
    UINT8*                      pui1_file_data ,
    UINT32                      ui4_file_data_len
    )
{
    INT32                       i4_ret = 0 ;
    UINT32                      ui4_written = 0 ;
    UINT32                      ui4_n       = 0 ;

    /* write data to file */
    do
    {
        ui4_n = 0;
        i4_ret = c_fm_write(h_file, 
                            pui1_file_data + ui4_written, 
                            ui4_file_data_len ,
                            &ui4_n);
        if(i4_ret == FMR_EOF)
        {
            return APP_CFGR_OK ;
        }
        
        else if(i4_ret != FMR_OK)
        {
            DBG_ERROR(("Can't write: %d", i4_ret));
            RET_ON_ERR (APP_CFGR_INTERNAL_ERR) ;
        }
    
        ui4_written = ui4_written + ui4_n;
        ui4_file_data_len = ui4_file_data_len - ui4_n;
        
    } while(ui4_file_data_len > 0);    

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _close_file
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _close_file (
    RMV_DEV_OPEN_ID_T           e_open_id ,
    HANDLE_T                    h_file
    )
{
    RET_ON_ERR (c_fm_close (h_file)) ;
    RET_ON_ERR (a_rmv_dev_close_mnt_point (e_open_id)) ;

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _dump_one_channel_info
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _dump_one_channel_info (
    BOOL                        b_cable ,
    SVL_REC_T*                  pt_svl_rec ,
    HANDLE_T                    h_file
    )
{   
    TSL_REC_T                   t_tsl_rec ;
    CHAR                        s_buff[MAX_OUTPUT_LEN] = {0} ;
    CHAR                        s_tv_sys[MAX_MACRO_LEN] = {0} ;
    CHAR                        s_bandwidth[MAX_MACRO_LEN] = {0} ;
    CHAR                        s_nw_mask[MAX_MACRO_LEN] = {0} ;
    CHAR                        s_tuner_mod[MAX_MACRO_LEN] = {0} ;

    if (!pt_svl_rec)
    {
        return APP_CFGR_INV_ARG ;
    }

    c_memset (&t_tsl_rec, 0, sizeof (TSL_REC_T)) ;

    RET_ON_ERR (a_tv_get_tsl_rec_by_svl_rec(pt_svl_rec,&t_tsl_rec)) ;
    RET_ON_ERR (_get_macro_tv_sys (pt_svl_rec->u_data.t_analog.ui4_tv_sys ,s_tv_sys)) ;
    RET_ON_ERR (_get_macro_nw_mask (pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask ,s_nw_mask)) ;

    if (!b_cable)
    {   
        RET_ON_ERR (_get_macro_bandwidth (t_tsl_rec.udata.t_ter_dig.e_bandwidth ,s_bandwidth)) ;
        
        RET_ON_ERR (_get_macro_tuner_mod (t_tsl_rec.udata.t_ter_dig.e_mod ,s_tuner_mod)) ;
    }
    else
    {
        c_strcpy (s_bandwidth ,"BW_UNKNOWN") ;
        RET_ON_ERR (_get_macro_tuner_mod (t_tsl_rec.udata.t_cab_dig.e_mod ,s_tuner_mod)) ;
    }

    if (BRDCST_TYPE_FMRDO == pt_svl_rec->uheader.t_rec_hdr.e_brdcst_type)
    {
        /* do not dump fmradio */
        return APP_CFGR_OK ;
    }
    else if (
        BRDCST_TYPE_ANALOG == pt_svl_rec->uheader.t_rec_hdr.e_brdcst_type)
    {
        /* analog */
        c_snprintf (s_buff ,MAX_OUTPUT_LEN -1 ,_ACFG_PRE_CH_ANA_INFO_FMT_ ,
                                pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id ,
                                b_cable ? t_tsl_rec.udata.t_cab_ana.ui4_freq / 1000 : t_tsl_rec.udata.t_ter_ana.ui4_freq / 1000 ,
                                pt_svl_rec->uheader.t_rec_hdr.ac_name ,
                                s_tv_sys ,
                                s_nw_mask) ;
    }
    else
    {
        /* digital */
        c_snprintf (s_buff ,MAX_OUTPUT_LEN -1 ,_ACFG_PRE_CH_DIG_INFO_FMT_,
                                pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id ,
                                b_cable ? t_tsl_rec.udata.t_cab_dig.ui4_freq /1000 : t_tsl_rec.udata.t_ter_dig.ui4_freq / 1000 ,
                                t_tsl_rec.ui2_tsl_rec_id, 
                                pt_svl_rec->uheader.t_rec_hdr.ac_name ,
                                s_bandwidth ,
                                s_tuner_mod ,
                                t_tsl_rec.uheader.t_desc.ui2_nw_id ,
                                t_tsl_rec.uheader.t_desc.ui2_on_id ,
                                t_tsl_rec.uheader.t_desc.ui2_ts_id ,
                                pt_svl_rec->uheader.t_rec_hdr.ui2_prog_id ,
                                s_nw_mask) ;
    }

    _output_content (h_file ,s_buff) ;

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _dump_all_channel_info
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _dump_all_channel_info (
    BOOL                        b_cable ,
    HANDLE_T                    h_dump_to_file 
    )
{
    INT32                       i4_ret;
    UINT32                      ui4_ver_id;
    UINT16                      ui2_svl_rec_id ;
    SVL_REC_T                   t_svl_rec;
    HANDLE_T                    h_tsl = NULL_HANDLE ;
    HANDLE_T                    h_svl = NULL_HANDLE ;
    CHAR*                       ps_ana_info_start_flag = NULL ;
    CHAR*                       ps_dig_info_start_flag = NULL ; 

    if (b_cable)
    {
        h_tsl = h_g_acfg_tsl_cable  ;
        h_svl = h_g_acfg_svl_cable  ;
        ps_ana_info_start_flag = _ACFG_PRE_CH_ANA_INFO_START_CABLE_ ;
        ps_dig_info_start_flag = _ACFG_PRE_CH_DIG_INFO_START_CABLE_ ;
    }
    else
    {
        h_tsl = h_g_acfg_tsl_air  ;
        h_svl = h_g_acfg_svl_air  ;
        ps_ana_info_start_flag = _ACFG_PRE_CH_ANA_INFO_START_AIR_ ;
        ps_dig_info_start_flag = _ACFG_PRE_CH_DIG_INFO_START_AIR_ ;
    }

    CHECK_ERR (c_svl_lock(h_svl)) ;
    CHECK_ERR (c_tsl_lock(h_tsl)) ;

    /* dump analog channel info */
    _output_content (h_dump_to_file ,ps_ana_info_start_flag) ;
    for (ui2_svl_rec_id = 1 ; TRUE ; ui2_svl_rec_id ++)
    {
        ui4_ver_id = SVL_NULL_VER_ID;
        i4_ret = c_svl_get_rec(h_svl ,ui2_svl_rec_id ,&t_svl_rec ,&ui4_ver_id) ;
        if(i4_ret == SVLR_REC_NOT_FOUND)
        {
            break;
        }
        else if(i4_ret != SVLR_OK)
        {
            Printf("<ANAS> Something wrong!!!\n");
            break;
        }
        if (BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
        {
            CHECK_ERR (_dump_one_channel_info (b_cable ,&t_svl_rec ,h_dump_to_file)) ;
        }
    }
    _output_content (h_dump_to_file ,_ACFG_PRE_CH_INFO_END_) ;

    /* dump digital channel info */
    _output_content (h_dump_to_file ,ps_dig_info_start_flag) ;
    for (ui2_svl_rec_id = 1 ; TRUE ; ui2_svl_rec_id ++)
    {
        ui4_ver_id = SVL_NULL_VER_ID;
        i4_ret = c_svl_get_rec(h_svl ,ui2_svl_rec_id ,&t_svl_rec ,&ui4_ver_id) ;
        if(i4_ret == SVLR_REC_NOT_FOUND)
        {
            break;
        }
        else if(i4_ret != SVLR_OK)
        {
            Printf("<ANAS> Something wrong!!!\n");
            break;
        }

        if (BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type
            &&
            BRDCST_TYPE_FMRDO != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)    
        {
            CHECK_ERR (_dump_one_channel_info (b_cable ,&t_svl_rec ,h_dump_to_file)) ;
        }
    }
    _output_content (h_dump_to_file ,_ACFG_PRE_CH_INFO_END_) ;

    CHECK_ERR (c_svl_unlock(h_svl)) ;
    CHECK_ERR (c_tsl_unlock(h_tsl)) ;
    
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _restore_channel
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 _restore_channel (
    BOOL                        b_cable ,
    UINT32*                     pui4_first_channel_id
    )
{
    CHAR*                       ps_area =NULL ;
    UINT16                      ui2_i = 0 ;
    HANDLE_T                    h_svl = NULL_HANDLE ;
    HANDLE_T                    h_tsl = NULL_HANDLE ;
    SVL_REC_T                   t_svl_rec ;
    TSL_REC_T                   t_tsl_rec ;
    UINT16                      ui2_dig_size = 0 ;
    UINT16                      ui2_ana_size = 0 ;
    _ACFG_PRE_CH_DIG_INFO*      pt_dig_info  = NULL ;
    _ACFG_PRE_CH_ANA_INFO*      pt_ana_info  = NULL ;
    CHAR*                       ps_svl_path  = NULL ;
    CHAR*                       ps_tsl_path  = NULL ;
    UINT16                      ui2_svl_id   = 0 ;
    UINT16                      ui2_tsl_id   = 0 ;
    BRDCST_TYPE_T               e_dig_brcst_type = BRDCST_TYPE_UNKNOWN ;
    UINT16                      ui2_tsl_rec_id     = 0xFFFF ;
    UINT16                      ui2_tsl_rec_id_bak = 0xFFFF ;
    UINT16                      ui2_svl_rec_id   = 0xFFFF ;
    BOOL                        b_defined_by_user= FALSE ;

#ifdef  APP_DVBT_SUPPORT
    e_dig_brcst_type = BRDCST_TYPE_DVB ;
#else
    e_dig_brcst_type = BRDCST_TYPE_ATSC ;
#endif  

    if (!pui4_first_channel_id)
    {
        return APP_CFGR_INV_ARG ;
    }
    else
    {
        *pui4_first_channel_id = 0 ;
    }
    
    RET_ON_ERR (_prepare_data ( ps_area ,
                                b_cable ,
                                &h_tsl ,
                                &h_svl ,
                                &ps_tsl_path ,
                                &ps_svl_path ,
                                &ui2_tsl_id ,
                                &ui2_svl_id ,
                                &ui2_ana_size ,
                                &ui2_dig_size ,
                                &pt_ana_info ,
                                &pt_dig_info)) ;

    CHECK_ERR (c_svl_clean(h_svl)) ;
    CHECK_ERR (c_tsl_clean(h_tsl)) ;

    CHECK_ERR (c_svl_lock(h_svl)) ;
    CHECK_ERR (c_tsl_lock(h_tsl)) ;

    ui2_svl_rec_id = 1 ; /* first svl rec id */

    /* load analog channels */
    for( ui2_i = 0; ui2_i < ui2_ana_size; ui2_i++ ,pt_ana_info ++)
    {
        b_defined_by_user = (_ACFG_PRE_CH_DEFINED_BY_USER_ == pt_ana_info->ui4_nw_flag)
                          ? TRUE 
                          : FALSE ;
            
        /* Update the SVL */
        CONTINUE_ON_ERR (c_svl_rec_init(&t_svl_rec)) ;

        t_svl_rec.ui2_svl_rec_id = ui2_svl_rec_id ++ ;
        t_svl_rec.uheader.t_rec_hdr.ui4_channel_id= _gen_ch_id (FALSE ,b_defined_by_user ,pt_ana_info->ui4_ch_val) ;
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask   = _gen_nw_mask (pt_ana_info->ui4_nw_flag) ;
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id    = ui2_tsl_id ;
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id= (UINT16)(SB_MAKE_PAL_SECAM_TSL_REC_ID(ui2_i+1));
        t_svl_rec.uheader.t_rec_hdr.e_brdcst_type = BRDCST_TYPE_ANALOG;
        t_svl_rec.uheader.t_rec_hdr.e_serv_type   = SVL_SERVICE_TYPE_TV;
        c_strcpy(t_svl_rec.uheader.t_rec_hdr.ac_name, pt_ana_info->ps_name) ;
        t_svl_rec.u_data.t_analog.ui4_s_comp_mask = 0;
        t_svl_rec.u_data.t_analog.ui4_tv_sys      = pt_ana_info->ui4_tv_sys;
        t_svl_rec.u_data.t_analog.ui4_audio_sys   = AUDIO_SYS_MASK_FM_MONO | AUDIO_SYS_MASK_NICAM;
        t_svl_rec.u_data.t_analog.e_vid_color_sys = COLOR_SYS_UNKNOWN;
        t_svl_rec.u_data.t_analog.b_valid_src_id  = FALSE;
        CONTINUE_ON_ERR (c_svl_update_rec(h_svl, &t_svl_rec, FALSE)) ;

        /* Update the TSL */
        CONTINUE_ON_ERR (c_tsl_rec_init(&t_tsl_rec)) ;
        t_tsl_rec.ui2_tsl_rec_id                  = (UINT16)(SB_MAKE_PAL_SECAM_TSL_REC_ID(ui2_i+1));
        t_tsl_rec.uheader.t_desc.e_bcst_type      = BRDCST_TYPE_ANALOG;
        t_tsl_rec.uheader.t_desc.e_bcst_medium    = (b_cable) ? BRDCST_MEDIUM_ANA_CABLE : BRDCST_MEDIUM_ANA_TERRESTRIAL;
        if (b_cable)
        {
            t_tsl_rec.udata.t_cab_ana.ui4_freq        = pt_ana_info->ui4_freq * 1000;
            t_tsl_rec.udata.t_cab_ana.e_mod           = MOD_PSK_8;
        }
        else
        {   
            t_tsl_rec.udata.t_ter_ana.ui4_freq        = pt_ana_info->ui4_freq * 1000;
            t_tsl_rec.udata.t_ter_ana.e_pol           = POL_UNKNOWN;
            t_tsl_rec.udata.t_ter_ana.ui2_dir         = 0;
            t_tsl_rec.udata.t_ter_ana.ui2_gain        = 0;
            t_tsl_rec.udata.t_ter_ana.e_mod           = MOD_PSK_8;
            t_tsl_rec.udata.t_ter_ana.b_fine_tune     = FALSE;
        }
        CONTINUE_ON_ERR (c_tsl_update_rec(h_tsl, &t_tsl_rec, FALSE)) ;

        if (0 == *pui4_first_channel_id)
        {
            if( !(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask&SB_VNET_FAKE))                    
            {
                *pui4_first_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id ;
            }
        }
    }

    /* load digital channels */
    for( ui2_i = 0; ui2_i < ui2_dig_size; ui2_i++ ,pt_dig_info ++)
    {
        b_defined_by_user = (_ACFG_PRE_CH_DEFINED_BY_USER_ == pt_dig_info->ui4_nw_flag)
                          ? TRUE 
                          : FALSE ;

        ui2_tsl_rec_id = pt_dig_info->ui2_tsl_rec_id;
        /* Update the SVL */
        CONTINUE_ON_ERR (c_svl_rec_init(&t_svl_rec)) ;
        t_svl_rec.ui2_svl_rec_id                   = ui2_svl_rec_id ++ ;
        t_svl_rec.uheader.t_rec_hdr.ui4_channel_id = _gen_ch_id (TRUE ,b_defined_by_user ,pt_dig_info->ui4_ch_val) ;
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask    = _gen_nw_mask (pt_dig_info->ui4_nw_flag) ;           
        t_svl_rec.uheader.t_rec_hdr.ui2_prog_id    = pt_dig_info->ui2_prog_id ;
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id     = ui2_tsl_id ;
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id = ui2_tsl_rec_id ;
        t_svl_rec.uheader.t_rec_hdr.e_brdcst_type  = e_dig_brcst_type ;
        t_svl_rec.uheader.t_rec_hdr.e_serv_type    = SVL_SERVICE_TYPE_TV ;
        c_strcpy(t_svl_rec.uheader.t_rec_hdr.ac_name, pt_dig_info->ps_name) ;
        CONTINUE_ON_ERR (c_svl_update_rec(h_svl, &t_svl_rec, FALSE)) ;

        /* New TSL record id. Update the TSL */
        if(ui2_tsl_rec_id != ui2_tsl_rec_id_bak)
        {
            CONTINUE_ON_ERR (c_tsl_rec_init(&t_tsl_rec)) ;
            t_tsl_rec.ui2_tsl_rec_id               = ui2_tsl_rec_id ;
            t_tsl_rec.uheader.t_desc.e_bcst_type   = e_dig_brcst_type ;
            t_tsl_rec.uheader.t_desc.ui2_nw_id     = pt_dig_info->ui2_nw_id;
            t_tsl_rec.uheader.t_desc.ui2_on_id     = pt_dig_info->ui2_on_id;
            t_tsl_rec.uheader.t_desc.ui2_ts_id     = pt_dig_info->ui2_ts_id;
            t_tsl_rec.uheader.t_desc.ui1_flags     = 0;

            if (b_cable)
            {   
                t_tsl_rec.uheader.t_desc.e_bcst_medium  = BRDCST_MEDIUM_DIG_CABLE ;
                t_tsl_rec.udata.t_cab_dig.ui4_freq      = pt_dig_info->ui4_freq * 1000;
                t_tsl_rec.udata.t_cab_dig.e_mod         = pt_dig_info->e_mod;
            }
            else
            {
                t_tsl_rec.uheader.t_desc.e_bcst_medium  = BRDCST_MEDIUM_DIG_TERRESTRIAL ;
                t_tsl_rec.udata.t_ter_dig.ui4_freq      = pt_dig_info->ui4_freq * 1000;
                t_tsl_rec.udata.t_ter_dig.e_bandwidth   = pt_dig_info->e_bandwidth;
                t_tsl_rec.udata.t_ter_dig.e_hierarchy_priority = HIR_PRIORITY_NONE;
                t_tsl_rec.udata.t_ter_dig.e_mod         = pt_dig_info->e_mod;;
            }
            
            CONTINUE_ON_ERR (c_tsl_update_rec(h_tsl ,&t_tsl_rec ,FALSE)) ;
            ui2_tsl_rec_id_bak = ui2_tsl_rec_id ;
            
            if (0 == *pui4_first_channel_id)
            {
                if( !(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask&SB_VNET_FAKE))                    
                {
                *pui4_first_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id ;
            }
        }
    }
    }

    CHECK_ERR (c_svl_unlock(h_svl)) ;
    CHECK_ERR (c_tsl_unlock(h_tsl)) ;

    /* Store Default Channel List Directly! */
    if ((h_svl != NULL_HANDLE) && (h_tsl != NULL_HANDLE))
    {
        Printf("\n Store Default Channel List Directly! \n");
        CHECK_ERR (c_svl_fs_store(FM_ROOT_HANDLE, ps_svl_path, ui2_svl_id)) ;
        CHECK_ERR (c_tsl_fs_store(FM_ROOT_HANDLE, ps_tsl_path, ui2_tsl_id)) ;
    }

    return APP_CFGR_OK;
}

#if 0
/* just for division */
#endif

/*----------------------------------------------------------------
                    CLI
-----------------------------------------------------------------*/
#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _pre_ch_atoi
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_atoi( const CHAR* ps )
{
    BOOL   b_hex    = FALSE ;
    INT32  i4_total = 0 ;
    INT16  i2_pow   = 10 ;

    if(!ps)
    {
        return APP_CFGR_INV_ARG ;
    }
    
    if (ps 
        && 
        '0' == ps[0] 
        &&
        ('x' == ps[1] || 'X' == ps[1]) )
    {
        /* is hex */
        b_hex  = TRUE ;
        i2_pow = 16 ;
        ps    += 2 ;
    }
        
    i4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            i4_total = i2_pow * i4_total + (*ps - '0');
        }
        else if (b_hex && (*ps >= 'a' && *ps <='f'))
        {
            i4_total = i2_pow * i4_total + (*ps - 'a' + 10);
        }
        else if (b_hex && (*ps >= 'A' && *ps <='F'))
        {
            i4_total = i2_pow * i4_total + (*ps - 'A' + 10);
        }
        else /* not a digit char */
        {
            return (-1);
        }
        
        /* get next char */
        ps ++ ; 
    }

    return i4_total;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_strtok
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
CHAR* _pre_ch_strtok(register char *s, register char *delim)
{
    register char *spanp;
    int c, sc;
    char *tok;
    static char *last;


    if (s == NULL && (s = last) == NULL)
        return (NULL);

    /*
    * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
    */
cont:
    c = *s++;
    for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
      if (c == sc)
        goto cont;
    }

    if (c == 0) {/* no non-delimiter characters */
      last = NULL;
        return (NULL);
    }
    tok = s - 1;

    /*
    * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
    * Note that delim must have one NUL; we stop if we see that, too.
    */
    for (;;) {
      c = *s++;
      spanp = (char *)delim;
        do {
          if ((sc = *spanp++) == c) {
            if (c == 0)
              s = NULL;
            else
              s[-1] = 0;

            last = s;
            return (tok);
          }
        } while (sc != 0);
    }
    /* NOTREACHED */
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_get_tv_mask
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_get_tv_mask(CHAR* ps_param, UINT32 *p4_val)
{
    if (0 == ps_param || 0 == p4_val)
    {
        return APP_CFGR_INV_ARG;
    }

    if (c_strcmp(ps_param, "TV_SYS_MASK_A") == 0)      { *p4_val |= TV_SYS_MASK_A; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_B") == 0) { *p4_val |= TV_SYS_MASK_B; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_C") == 0) { *p4_val |= TV_SYS_MASK_C; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_D") == 0) { *p4_val |= TV_SYS_MASK_D; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_E") == 0) { *p4_val |= TV_SYS_MASK_E; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_F") == 0) { *p4_val |= TV_SYS_MASK_F; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_G") == 0) { *p4_val |= TV_SYS_MASK_G; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_H") == 0) { *p4_val |= TV_SYS_MASK_H; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_I") == 0) { *p4_val |= TV_SYS_MASK_I; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_J") == 0) { *p4_val |= TV_SYS_MASK_J; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_K") == 0) { *p4_val |= TV_SYS_MASK_K; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_L") == 0) { *p4_val |= TV_SYS_MASK_L; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_M") == 0) { *p4_val |= TV_SYS_MASK_M; }
    else if (c_strcmp(ps_param, "TV_SYS_MASK_N") == 0) { *p4_val |= TV_SYS_MASK_N; }
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_get_nw_mask
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_get_nw_mask(CHAR* ps_param, UINT32 *p4_val)
{
    if (0 == ps_param || 0 == p4_val)
    {
        return APP_CFGR_INV_ARG;
    }

    if (c_strcmp(ps_param, "SB_VNET_ALL") == 0)            { *p4_val |= SB_VNET_ALL; }
    else if (c_strcmp(ps_param, "SB_VNET_ACTIVE") == 0)    { *p4_val |= SB_VNET_ACTIVE; }
    else if (c_strcmp(ps_param, "SB_VNET_EPG") == 0)       { *p4_val |= SB_VNET_EPG;    }
    else if (c_strcmp(ps_param, "SB_VNET_VISIBLE") == 0)   { *p4_val |= SB_VNET_VISIBLE;}
    else if (c_strcmp(ps_param, "SB_VNET_FAVORITE1") == 0) { *p4_val |= SB_VNET_FAVORITE1;}
    else if (c_strcmp(ps_param, "SB_VNET_FAVORITE2") == 0) { *p4_val |= SB_VNET_FAVORITE2;}
    else if (c_strcmp(ps_param, "SB_VNET_FAVORITE3") == 0) { *p4_val |= SB_VNET_FAVORITE3;}
    else if (c_strcmp(ps_param, "SB_VNET_FAVORITE4") == 0) { *p4_val |= SB_VNET_FAVORITE4;}
    else if (c_strcmp(ps_param, "SB_VNET_BLOCKED") == 0)   { *p4_val |= SB_VNET_BLOCKED;}
    else if (c_strcmp(ps_param, "SB_VNET_OOB_LIST") == 0)  { *p4_val |= SB_VNET_OOB_LIST;}
    else if (c_strcmp(ps_param, "SB_VNET_INB_LIST") == 0)  { *p4_val |= SB_VNET_INB_LIST;}
    else if (c_strcmp(ps_param, "SB_VNET_SCRAMBLED") == 0) { *p4_val |= SB_VNET_SCRAMBLED;}
    else if (c_strcmp(ps_param, "SB_VNET_BACKUP1") == 0)   { *p4_val |= SB_VNET_BACKUP1;}
    else if (c_strcmp(ps_param, "SB_VNET_BACKUP2") == 0)   { *p4_val |= SB_VNET_BACKUP2;}
    else if (c_strcmp(ps_param, "SB_VNET_BACKUP3") == 0)   { *p4_val |= SB_VNET_BACKUP3;}
    else if (c_strcmp(ps_param, "SB_VNET_FAKE") == 0)      { *p4_val |= SB_VNET_FAKE;}
    else if (c_strcmp(ps_param, "SB_VNET_USER_TMP_UNLOCK") == 0) { *p4_val |= SB_VNET_USER_TMP_UNLOCK;}
    else if (c_strcmp(ps_param, "SB_VNET_CH_NAME_EDITED") == 0)  { *p4_val |= SB_VNET_CH_NAME_EDITED;}
    else if (c_strcmp(ps_param, "SB_VNET_LCN_APPLIED") == 0)     { *p4_val |= SB_VNET_LCN_APPLIED;}
    else if (c_strcmp(ps_param, "SB_VNET_USE_DECODER") == 0)     { *p4_val |= SB_VNET_USE_DECODER;}
    else if (c_strcmp(ps_param, "SB_VNET_ACTIVE_EPG_EDITED") == 0)  { *p4_val |= SB_VNET_ACTIVE_EPG_EDITED;}
    else if (c_strcmp(ps_param, "SB_VNET_FREQ_EDITED") == 0)        { *p4_val |= SB_VNET_FREQ_EDITED;}
    else if (c_strcmp(ps_param, "SB_VNET_REMOVAL") == 0)            { *p4_val |= SB_VNET_REMOVAL;}
    else if (c_strcmp(ps_param, "SB_VNET_REMOVAL_TO_CONFIRM") == 0) { *p4_val |= SB_VNET_REMOVAL_TO_CONFIRM;}
    else if (c_strcmp(ps_param, "_ACFG_PRE_CH_DEFINED_BY_USER_") == 0) { *p4_val = _ACFG_PRE_CH_DEFINED_BY_USER_; }
    else    {        /* p4_val default USER_DEFINED? */
    }
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_ch_num
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_ch_num(CHAR* ps_param, UINT32 *pui4_val)
{
    if (0 == ps_param)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui4_val = _pre_ch_atoi(ps_param) ;

    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_freq
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_freq(CHAR* ps_param, UINT32 *pui4_freq)
{
    if (0 == ps_param || 0 == pui4_freq)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui4_freq = _pre_ch_atoi(ps_param);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_tsl_rec_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_tsl_rec_id(CHAR* ps_param, UINT16 *pui2_tsl_rec_id)
{
    if (0 == ps_param || 0 == pui2_tsl_rec_id)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui2_tsl_rec_id = (UINT16)_pre_ch_atoi(ps_param);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_nw_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_nw_id(CHAR* ps_param, UINT16 *pui2_nw_id)
{
    if (0 == ps_param || 0 == pui2_nw_id)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui2_nw_id = (UINT16)_pre_ch_atoi(ps_param);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_on_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_on_id(CHAR* ps_param, UINT16 *pui2_on_id)
{
    if (0 == ps_param || 0 == pui2_on_id)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui2_on_id =(UINT16) _pre_ch_atoi(ps_param);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_ts_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_ts_id(CHAR* ps_param, UINT16 *pui2_ts_id)
{
    if (0 == ps_param || 0 == pui2_ts_id)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui2_ts_id = (UINT16)_pre_ch_atoi(ps_param);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_prog_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_prog_id(CHAR* ps_param, UINT16 *pui2_prog_id)
{
    if (0 == ps_param || 0 == pui2_prog_id)
    {
        return APP_CFGR_INV_ARG;
    }

    *pui2_prog_id = (UINT16)_pre_ch_atoi(ps_param);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_ch_name
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_ch_name(CHAR* ps_param, CHAR* ps_name)
{
    if (0 == ps_param || 0 == ps_name)
    {
        return APP_CFGR_INV_ARG;
    }

    c_strncpy(ps_name, ps_param, MAX_PROG_NAME_LEN -1);
    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_tv_sys
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_tv_sys(CHAR* ps_param, UINT32 *pui4_tv_sys)
{
    CHAR as_mask[128] = {0};
    CHAR *ps_token    = 0;

    if (0 == ps_param || 0 == pui4_tv_sys)
    {
        return APP_CFGR_INV_ARG;
    }

    if (c_strlen(ps_param) >= 128)
    {
        return APP_CFGR_INV_ARG;
    }

    c_strcpy(as_mask, ps_param);

    ps_token = _pre_ch_strtok(as_mask, "|");
    while (ps_token)
    {
        _pre_ch_cli_get_tv_mask(ps_token, pui4_tv_sys);
        ps_token = _pre_ch_strtok(NULL, "|");
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_nw_mask
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_nw_mask(CHAR* ps_param, BOOL *pb_usr, UINT32 *pui4_nw_mask)
{
    CHAR as_mask[128] = {0};
    CHAR *ps_token    = 0;

    if (0 == ps_param || 0 == pb_usr || 0 == pui4_nw_mask)
    {
        return APP_CFGR_INV_ARG;
    }

    if (c_strlen(ps_param) >= 128)
    {
        return APP_CFGR_INV_ARG;
    }

    c_strcpy(as_mask, ps_param);

    ps_token = _pre_ch_strtok(as_mask, "|");
    while (ps_token)
    {
        _pre_ch_cli_get_nw_mask(ps_token, pui4_nw_mask);
        ps_token = _pre_ch_strtok(NULL, "|");
    }

    if (_ACFG_PRE_CH_DEFINED_BY_USER_ == (*pui4_nw_mask))
    {
        *pb_usr = TRUE;
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_bandwidth
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_bandwidth(CHAR* ps_param, TUNER_BANDWIDTH_T *pe_band)
{
    if (0 == ps_param || 0 == pe_band)
    {
        return APP_CFGR_INV_ARG;
    }

    if (c_strcmp(ps_param, "BW_6_MHz") == 0)            { *pe_band = BW_6_MHz; }
    else if (c_strcmp(ps_param, "BW_7_MHz") == 0)       { *pe_band = BW_7_MHz; }
    else if (c_strcmp(ps_param, "BW_8_MHz") == 0)       { *pe_band = BW_8_MHz; }
    else
    {
        *pe_band = BW_8_MHz;
    }
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_parse_modulation
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_parse_modulation(CHAR* ps_param, TUNER_MODULATION_T *pe_modulation)
{
    if (0 == ps_param || 0 == pe_modulation)
    {
        return APP_CFGR_INV_ARG;
    }

    if      (c_strcmp(ps_param, "MOD_UNKNOWN") == 0)       { *pe_modulation = MOD_UNKNOWN; }
    else if (c_strcmp(ps_param, "MOD_PSK_8"  ) == 0)       { *pe_modulation = MOD_PSK_8; }
    else if (c_strcmp(ps_param, "MOD_VSB_8"  ) == 0)       { *pe_modulation = MOD_VSB_8; }
    else if (c_strcmp(ps_param, "MOD_VSB_16" ) == 0)       { *pe_modulation = MOD_VSB_16; }
    else if (c_strcmp(ps_param, "MOD_QAM_16" ) == 0)       { *pe_modulation = MOD_QAM_16; }
    else if (c_strcmp(ps_param, "MOD_QAM_32" ) == 0)       { *pe_modulation = MOD_QAM_32; }
    else if (c_strcmp(ps_param, "MOD_QAM_64" ) == 0)       { *pe_modulation = MOD_QAM_64; }
    else if (c_strcmp(ps_param, "MOD_QAM_80" ) == 0)       { *pe_modulation = MOD_QAM_80; }
    else if (c_strcmp(ps_param, "MOD_QAM_96" ) == 0)       { *pe_modulation = MOD_QAM_96; }
    else if (c_strcmp(ps_param, "MOD_QAM_112") == 0)       { *pe_modulation = MOD_QAM_112; }
    else if (c_strcmp(ps_param, "MOD_QAM_128") == 0)       { *pe_modulation = MOD_QAM_128; }
    else if (c_strcmp(ps_param, "MOD_QAM_160") == 0)       { *pe_modulation = MOD_QAM_160; }
    else if (c_strcmp(ps_param, "MOD_QAM_192") == 0)       { *pe_modulation = MOD_QAM_192; }
    else if (c_strcmp(ps_param, "MOD_QAM_224") == 0)       { *pe_modulation = MOD_QAM_224; }
    else if (c_strcmp(ps_param, "MOD_QAM_256") == 0)       { *pe_modulation = MOD_QAM_256; }
    else if (c_strcmp(ps_param, "MOD_QAM_320") == 0)       { *pe_modulation = MOD_QAM_320; }
    else if (c_strcmp(ps_param, "MOD_QAM_384") == 0)       { *pe_modulation = MOD_QAM_384; }
    else if (c_strcmp(ps_param, "MOD_QAM_448") == 0)       { *pe_modulation = MOD_QAM_448; }
    else if (c_strcmp(ps_param, "MOD_QAM_512") == 0)       { *pe_modulation = MOD_QAM_512; }
    else if (c_strcmp(ps_param, "MOD_QAM_640") == 0)       { *pe_modulation = MOD_QAM_640; }
    else if (c_strcmp(ps_param, "MOD_QAM_768") == 0)       { *pe_modulation = MOD_QAM_768; }
    else if (c_strcmp(ps_param, "MOD_QAM_896") == 0)       { *pe_modulation = MOD_QAM_896; }
    else if (c_strcmp(ps_param, "MOD_QAM_1024") == 0)      { *pe_modulation = MOD_QAM_1024; }
    else if (c_strcmp(ps_param, "MOD_QPSK"   ) == 0)       { *pe_modulation = MOD_QPSK; }
    else if (c_strcmp(ps_param, "MOD_OQPSK"  ) == 0)       { *pe_modulation = MOD_OQPSK; }
    else if (c_strcmp(ps_param, "MOD_BPSK"   ) == 0)       { *pe_modulation = MOD_BPSK; }
    else if (c_strcmp(ps_param, "MOD_VSB_AM" ) == 0)       { *pe_modulation = MOD_VSB_AM; }
    else if (c_strcmp(ps_param, "MOD_QAM_4_NR") == 0)      { *pe_modulation = MOD_QAM_4_NR; }
    else if (c_strcmp(ps_param, "MOD_FM_RADIO") == 0)      { *pe_modulation = MOD_FM_RADIO; }
    else
    {
        *pe_modulation = MOD_UNKNOWN;
    }
    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _pre_ch_cli_import_rec
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _pre_ch_cli_import_rec
(
    INT32 i4_argc, 
    const CHAR** pps_argv
)
{
    b_g_pre_ch_cli_import = TRUE;

    a_cfg_pre_ch_load_preset_channel();

    b_g_pre_ch_cli_import = FALSE;
    ui1_g_pre_ch_cli_ana_air_num = 0;
    ui1_g_pre_ch_cli_dig_air_num = 0;
    ui1_g_pre_ch_cli_ana_cab_num = 0;
    ui1_g_pre_ch_cli_dig_cab_num = 0;

    return APP_CFGR_OK;
}

#endif /* CLI_SUPPORT */

/*-----------------------------------------------------------------------------
 * Name: acfg_pre_ch_cli_add_air_ana_rec
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 acfg_pre_ch_cli_add_air_ana_rec
(
    INT32 i4_argc,
    const CHAR * * pps_argv
)
{
#ifdef CLI_SUPPORT

    BOOL b_usr_defined = FALSE;
    INT32 i4_ret = 0;

    if (0 == ui1_g_pre_ch_cli_ana_air_num)
    {
        c_memset(&at_g_pre_ch_cli_ana_air_tbl, 0, sizeof(at_g_pre_ch_cli_ana_air_tbl));
    }
    if ((_ACFG_PRE_CH_CLI_REC_MAX_NUM) <= ui1_g_pre_ch_cli_ana_air_num)
    {
        ui1_g_pre_ch_cli_ana_air_num = _ACFG_PRE_CH_CLI_REC_MAX_NUM - 1;
    }

    i4_ret = _pre_ch_cli_parse_nw_mask((CHAR*)pps_argv[5], &b_usr_defined, &at_g_pre_ch_cli_ana_air_tbl[ui1_g_pre_ch_cli_ana_air_num].ui4_nw_flag);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_num((CHAR*)pps_argv[1], 
                                        b_usr_defined 
                                        ? (&at_g_pre_ch_cli_ana_air_tbl[ui1_g_pre_ch_cli_ana_air_num].ui4_ch_val) 
                                        : (&at_g_pre_ch_cli_ana_air_tbl[ui1_g_pre_ch_cli_ana_air_num].ui4_ch_val) );
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_freq((CHAR*)pps_argv[2], &at_g_pre_ch_cli_ana_air_tbl[ui1_g_pre_ch_cli_ana_air_num].ui4_freq);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_name((CHAR*)pps_argv[3], at_g_pre_ch_cli_ana_air_tbl[ui1_g_pre_ch_cli_ana_air_num].ps_name);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_tv_sys((CHAR*)pps_argv[4], &at_g_pre_ch_cli_ana_air_tbl[ui1_g_pre_ch_cli_ana_air_num].ui4_tv_sys);
    if (CLIR_OK != i4_ret) return i4_ret;

    ui1_g_pre_ch_cli_ana_air_num++;
#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_pre_ch_cli_add_air_dig_rec
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 acfg_pre_ch_cli_add_air_dig_rec
(
    INT32 i4_argc,
    const CHAR * * pps_argv
)
{
#ifdef CLI_SUPPORT

    BOOL b_usr_defined = FALSE;
    INT32 i4_ret = 0;

    if (0 == ui1_g_pre_ch_cli_dig_air_num)
    {
        c_memset(&at_g_pre_ch_cli_dig_air_tbl, 0, sizeof(at_g_pre_ch_cli_dig_air_tbl));
    }
    if ((_ACFG_PRE_CH_CLI_REC_MAX_NUM) <= ui1_g_pre_ch_cli_dig_air_num)
    {
        ui1_g_pre_ch_cli_dig_air_num = _ACFG_PRE_CH_CLI_REC_MAX_NUM - 1;
    }

    i4_ret = _pre_ch_cli_parse_nw_mask((CHAR*)pps_argv[11], &b_usr_defined, &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui4_nw_flag);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_num((CHAR*)pps_argv[1], 
                                        b_usr_defined
                                        ? (&at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui4_ch_val) 
                                        : (&at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui4_ch_val) );
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_freq((CHAR*)pps_argv[2], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui4_freq);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_tsl_rec_id((CHAR*)pps_argv[3], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui2_tsl_rec_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_name((CHAR*)pps_argv[4], at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ps_name);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_bandwidth((CHAR*)pps_argv[5], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].e_bandwidth);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_modulation((CHAR*)pps_argv[6], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].e_mod);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_nw_id((CHAR*)pps_argv[7], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui2_nw_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_on_id((CHAR*)pps_argv[8], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui2_on_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ts_id((CHAR*)pps_argv[9], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui2_ts_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_prog_id((CHAR*)pps_argv[10], &at_g_pre_ch_cli_dig_air_tbl[ui1_g_pre_ch_cli_dig_air_num].ui2_prog_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    ui1_g_pre_ch_cli_dig_air_num++;

#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_pre_ch_cli_add_cab_ana_rec
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 acfg_pre_ch_cli_add_cab_ana_rec
(
    INT32 i4_argc,
    const CHAR * * pps_argv
)
{
#ifdef CLI_SUPPORT

    BOOL b_usr_defined = FALSE;
    INT32 i4_ret = 0;

    if (0 == ui1_g_pre_ch_cli_ana_cab_num)
    {
        c_memset(&at_g_pre_ch_cli_ana_cab_tbl, 0, sizeof(at_g_pre_ch_cli_ana_cab_tbl));
    }
    if ((_ACFG_PRE_CH_CLI_REC_MAX_NUM) <= ui1_g_pre_ch_cli_ana_cab_num)
    {
        ui1_g_pre_ch_cli_ana_cab_num = _ACFG_PRE_CH_CLI_REC_MAX_NUM - 1;
    }

    i4_ret = _pre_ch_cli_parse_nw_mask((CHAR*)pps_argv[5], &b_usr_defined, &at_g_pre_ch_cli_ana_cab_tbl[ui1_g_pre_ch_cli_ana_cab_num].ui4_nw_flag);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_num((CHAR*)pps_argv[1],
                                        b_usr_defined
                                        ? (&at_g_pre_ch_cli_ana_cab_tbl[ui1_g_pre_ch_cli_ana_cab_num].ui4_ch_val) 
                                        : (&at_g_pre_ch_cli_ana_cab_tbl[ui1_g_pre_ch_cli_ana_cab_num].ui4_ch_val) );
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_freq((CHAR*)pps_argv[2], &at_g_pre_ch_cli_ana_cab_tbl[ui1_g_pre_ch_cli_ana_cab_num].ui4_freq);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_name((CHAR*)pps_argv[3], at_g_pre_ch_cli_ana_cab_tbl[ui1_g_pre_ch_cli_ana_cab_num].ps_name);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_tv_sys((CHAR*)pps_argv[4], &at_g_pre_ch_cli_ana_cab_tbl[ui1_g_pre_ch_cli_ana_cab_num].ui4_tv_sys);
    if (CLIR_OK != i4_ret) return i4_ret;

    ui1_g_pre_ch_cli_ana_cab_num++;
#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_pre_ch_cli_add_cab_dig_rec
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 acfg_pre_ch_cli_add_cab_dig_rec
(
    INT32 i4_argc,
    const CHAR * * pps_argv
)
{
#ifdef CLI_SUPPORT

    BOOL b_usr_defined = FALSE;
    INT32 i4_ret = 0;

    if (0 == ui1_g_pre_ch_cli_dig_cab_num)
    {
        c_memset(&at_g_pre_ch_cli_dig_cab_tbl, 0, sizeof(at_g_pre_ch_cli_dig_cab_tbl));
    }
    if ((_ACFG_PRE_CH_CLI_REC_MAX_NUM) <= ui1_g_pre_ch_cli_dig_cab_num)
    {
        ui1_g_pre_ch_cli_dig_cab_num = _ACFG_PRE_CH_CLI_REC_MAX_NUM - 1;
    }

    i4_ret = _pre_ch_cli_parse_nw_mask((CHAR*)pps_argv[11], &b_usr_defined, &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui4_nw_flag);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_num((CHAR*)pps_argv[1], 
                                        b_usr_defined
                                        ? (&at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui4_ch_val) 
                                        : (&at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui4_ch_val) );
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_freq((CHAR*)pps_argv[2], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui4_freq);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_tsl_rec_id((CHAR*)pps_argv[3], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui2_tsl_rec_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ch_name((CHAR*)pps_argv[4], at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ps_name);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_bandwidth((CHAR*)pps_argv[5], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].e_bandwidth);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_modulation((CHAR*)pps_argv[6], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].e_mod);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_nw_id((CHAR*)pps_argv[7], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui2_nw_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_on_id((CHAR*)pps_argv[8], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui2_on_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_ts_id((CHAR*)pps_argv[9], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui2_ts_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    i4_ret = _pre_ch_cli_parse_prog_id((CHAR*)pps_argv[10], &at_g_pre_ch_cli_dig_cab_tbl[ui1_g_pre_ch_cli_dig_cab_num].ui2_prog_id);
    if (CLIR_OK != i4_ret) return i4_ret;

    ui1_g_pre_ch_cli_dig_cab_num++;

#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_pre_ch_cli_import_rec
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 acfg_pre_ch_cli_import_rec
(
    INT32 i4_argc,
    const CHAR * * pps_argv
)
{
#ifdef CLI_SUPPORT

    CLI_IN_AGENT_THREAD(_pre_ch_cli_import_rec);
#endif

    return APP_CFGR_OK;
}
/*-----------------------------------------------------------------------------
                    external functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_cfg_pre_ch_dump_channel_info_2_term
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 a_cfg_pre_ch_dump_channel_info_2_term(VOID)
{
    /* dump cable channel info */
    RET_ON_ERR (_dump_all_channel_info (TRUE ,NULL_HANDLE)) ;

    /* dump air channel info */
    RET_ON_ERR (_dump_all_channel_info (FALSE ,NULL_HANDLE)) ;

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_pre_ch_dump_channel_info_2_usb
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 a_cfg_pre_ch_dump_channel_info_2_usb (VOID)
{
    RMV_DEV_OPEN_ID_T   e_open_id ;
    HANDLE_T            h_file = NULL_HANDLE ;
    
    /* open file */
    RET_ON_ERR (_open_file(&e_open_id ,&h_file)) ;
    Printf("\n-->Open file success.");

    /* dump cable channel info */
    RET_ON_ERR (_dump_all_channel_info (TRUE ,h_file)) ;
    Printf("\n-->Dump channel info(cable) success.");

    /* dump air channel info */
    RET_ON_ERR (_dump_all_channel_info (FALSE ,h_file)) ;
    Printf("\n-->Dump channel info(air) success.");

    /* close file */
    CHECK_ERR (_close_file(e_open_id ,h_file)) ;
    Printf("\n-->Close file success.");

    return APP_CFGR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_pre_ch_restore_channel
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 a_cfg_pre_ch_load_preset_channel (VOID)
{
    UINT32      ui4_jump_to_channel_id   = 0 ;
    UINT32      ui4_first_channel_id_air = 0 ;
    UINT32      ui4_first_channel_id_cab = 0 ;    
    
    /* stop svctx */
    CHECK_ERR (a_tv_stop(h_g_acfg_svctx_main)) ;
    
    /* restore cable */
    RET_ON_ERR (_restore_channel (TRUE ,&ui4_first_channel_id_cab)) ;

    /* restore air */
    RET_ON_ERR (_restore_channel (FALSE ,&ui4_first_channel_id_air)) ;

    /* jump to air channel if exist ,otherwize jump to cable */
    if (ui4_first_channel_id_air)
    {
        RET_ON_ERR (a_cfg_set_tuner_sync_src(ATSC_TRSTRL_SVL_ID, NULL)) ;
        ui4_jump_to_channel_id = ui4_first_channel_id_air ;
    }
    else if (ui4_first_channel_id_cab)
    {
        RET_ON_ERR (a_cfg_set_tuner_sync_src(ATSC_CABLE_SVL_ID, NULL)) ;
        ui4_jump_to_channel_id = ui4_first_channel_id_cab ;
    }
    else
    {
        return APP_CFGR_OK ;
    }

    /* jump to first channel */
    CHECK_ERR (a_tv_change_channel(h_g_acfg_svctx_main, 
                                SVCTX_STRM_MODE_AS_LAST,
                                ui4_jump_to_channel_id ,
                                NULL)) ;

    return APP_CFGR_OK ;
}

#endif /* APP_PRESET_CH_FOR_FAC_SUPPORT */




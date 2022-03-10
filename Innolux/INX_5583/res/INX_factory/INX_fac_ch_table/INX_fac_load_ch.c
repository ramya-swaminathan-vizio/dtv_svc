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
 * $RCSfile: acfg_custom_ch.c,v $
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
#include "u_fm.h"

#include "c_svl.h"
#include "c_tsl.h"
#include "c_svctx.h"

#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/config/_acfg.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "app_util/config/acfg_cust_factory_vizio.h"
//#include "res/nav/factory/fac_menu/nav_fac.h"

#include "c_fm.h"
#include "app_util/rmv_dev/a_rmv_dev.h"

//#include "nav_fac_load_ch.h"
#include "INX_fac_load_ch.h"
#include "INX_factory/a_INX_factory.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
//extern VOID Printf (const CHAR*  ps_format, ...);
#define TSL_DATA_ANTENNA_PREFIX "static TSL_DATA_T    t_tsl_table_antenna[] =\r\n{\r\n"
#define TSL_DATA_CABLE_PREFIX "static TSL_DATA_T    t_tsl_table_cable[] =\r\n{\r\n"
#define SVL_DATA_ANTENNA_PREFIX "static SVL_DATA_T    t_svl_table_antenna[] =\r\n{\r\n"
#define SVL_DATA_CABLE_PREFIX "static SVL_DATA_T    t_svl_table_cable[] =\r\n{\r\n"
#define TSL_INFO_FORMAT "    /* tsl_rec_id, bcst_type, bcst_medium, nw_id, on_id, ts_id,   flags, freq,  bandwidth, mod */\r\n"
#define TSL_INFO "    {0x%-4x,\t%s,\t%s,\t%d,\t%d,\t%d,\t%d,\t%d,\t%s,\t%s},\r\n"
#define SVL_INFO_FORMAT "    /* channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type, ch_name, tv_sys, audio_sys, vid_color_sys*/\r\n"
#define SVL_INFO "    {0x%-8x,\t0x%-8x,\t%d,\t0x%-4x,\t%s,\t%s,\t\"%s\",\t%s,\t%s,\t%s},\r\n"
#define INFO_END  "\r\n};\r\n\r\n"
#define MAX_MACRO_LEN                       (255)


typedef struct _TSL_DATA_T {
    UINT16              ui2_tsl_rec_id;
    BRDCST_TYPE_T       e_bcst_type;
    BRDCST_MEDIUM_T     e_bcst_medium;
    UINT16              ui2_nw_id;
    UINT16              ui2_on_id;
    UINT16              ui2_ts_id;
    UINT8               ui1_flags;
    UINT32              ui4_freq;
    TUNER_BANDWIDTH_T   e_bandwidth;
    TUNER_MODULATION_T  e_mod;
} TSL_DATA_T;

typedef struct _SVL_DATA_T {
    UINT32              ui4_channel_num;
    UINT32              ui4_nw_mask;
    UINT16              ui2_prog_id;
    UINT16              ui2_tsl_rec_id;
    BRDCST_TYPE_T       e_brdcst_type;
    SVL_SERVICE_TYPE_T  e_serv_type;
    CHAR                ac_name[MAX_PROG_NAME_LEN];
    UINT32              ui4_tv_sys;
    UINT32              ui4_audio_sys;
    COLOR_SYS_T         e_vid_color_sys;
} SVL_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
#if defined(APP_DVBT_SUPPORT)
static TSL_DATA_T    t_tsl_table_FuQing_DVBT[] =
{
/* tsl_rec_id, bcst_type,              bcst_medium,        nw_id,  on_id,  ts_id, flags,   freq,   bandwidth,  mod     */
    { 81,  BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL, 12307, 9018, 16384,     0, 490000000, BW_8_MHz, MOD_VSB_8},
    {108,  BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL,     1,      1,     10,     0, 650000000, BW_8_MHz, MOD_VSB_8},
    {109,  BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL, 12293, 9018,  4100,     0, 658000000, BW_8_MHz, MOD_VSB_8},
    {301,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 335250000, BW_8_MHz, MOD_PSK_8},
    {302,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 360250000, BW_8_MHz, MOD_PSK_8},
    {303,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 615250000, BW_8_MHz, MOD_PSK_8},
    {304,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 527250000, BW_8_MHz, MOD_PSK_8},
    {305,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0,  49750000, BW_8_MHz, MOD_PSK_8},
    {306,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 119250000, BW_8_MHz, MOD_PSK_8},
    {307,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 184000000, BW_8_MHz, MOD_PSK_8},
    {308,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 217250000, BW_8_MHz, MOD_PSK_8},
    {309,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 224250000, BW_8_MHz, MOD_PSK_8},
    {310,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 280250000, BW_8_MHz, MOD_PSK_8},
    {311,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 304250000, BW_8_MHz, MOD_PSK_8},
    {312,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 448250000, BW_8_MHz, MOD_PSK_8},
    {313,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 503250000, BW_8_MHz, MOD_PSK_8},
    {314,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 783250000, BW_8_MHz, MOD_PSK_8}
};

static SVL_DATA_T    t_svl_table_FuQing_DVBT[] =
{
/*channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type,     ch_name,   tv_sys,            audio_sys,           vid_color_sys*/
    {  1, 0x0000060F,  16768,  81, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "Moving Picture", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  2, 0x0000060F,  16832,  81, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "Monoscope", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  3, 0x0000060F,  16960,  81, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "Color Bar", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  4, 0x0004060F,   4164, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC ONE", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  5, 0x0004060F,   4228, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC TWO", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  6, 0x0004060F,   4351, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC CHOICE", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  7, 0x0004060F,   4415, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC NEWS 24", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  8, 0x0004060F,   4479, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBCi", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  9, 0x0004060F,   4607, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC Knowledge", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 10, 0x00040A0F,   4543, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_RADIO, "BBC PARLMNT", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 12, 0x0004060F,      1, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 1", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 13, 0x0004060F,      2, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 13", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 14, 0x0004060F,      3, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 20", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 15, 0x0004060F,      4, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 21", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 16, 0x0004060F,      5, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 22", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 17, 0x0004060F,      6, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 23", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 18, 0x0004060F,     21, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 2", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 19, 0x0004060F,     22, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 3", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 20, 0x0004060F,     23, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 4", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 21, 0x0004060F,     24, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 5", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 22, 0x0004060F,     25, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 6", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 23, 0x0004060F,     26, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 7", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 24, 0x0004060F,     27, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 8", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 25, 0x0004060F,     28, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 9", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 26, 0x0004060F,     29, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 10", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 27, 0x0004060F,     30, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 11", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 28, 0x0004060F,     31, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 14", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 29, 0x0004060F,     32, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 15", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 30, 0x0004060F,     33, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 16", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 31, 0x0004060F,     34, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 17", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 32, 0x0004060F,     35, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 18", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 33, 0x0004060F,     36, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 19", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 34, 0x0004060F,     41, 108, BRDCST_TYPE_DVB,    SVL_SERVICE_TYPE_TV, "Service 12", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {900, 0x0000100F,  12339, 301, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {901, 0x0000100F,  14644, 302, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {902, 0x0000100F,  65535, 303, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_I, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {903, 0x0000100F,   1792, 304, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "BBC1", TV_SYS_MASK_I, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {904, 0x0000100F,   1792, 305, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {905, 0x0000100F,  65535, 306, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_FM_A2, COLOR_SYS_UNKNOWN},
    {906, 0x0000100F,  65535, 307, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_L, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {907, 0x0000100F,   4680, 308, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {908, 0x0000100F,   4372, 309, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_FM_A2, COLOR_SYS_UNKNOWN},
    {909, 0x0000100F,  13872, 310, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {910, 0x0000100F,  12849, 311, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {911, 0x0000100F,  13624, 312, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {912, 0x0000100F,  42368, 313, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_I, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {913, 0x0000100F,  65535, 314, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN}
};

static TSL_DATA_T    t_tsl_table_SuZhou_DVBT[] = 
{
/* tsl_rec_id, bcst_type,              bcst_medium,        nw_id,  on_id,  ts_id, flags,   freq,   bandwidth,  mod     */    
    { 96,  BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL, 12293, 9018,  4100,     0, 578000000, BW_8_MHz, MOD_VSB_8},    
    { 108, BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL,     1,    1,     1,     0, 650000000, BW_8_MHz, MOD_VSB_8},    
    { 109, BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL,  1001, 1001,  1000,     0, 658000000, BW_8_MHz, MOD_VSB_8},    
    { 301, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0,  55729000, BW_UNKNOWN, MOD_UNKNOWN},        
    { 302, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0,  64261000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 303, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 119261000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 304, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 184251000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 305, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 209241000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 306, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 223221000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 307, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 343271000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 308, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 471272000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 309, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 495248000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 310, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 527237000, BW_UNKNOWN, MOD_UNKNOWN},        
    { 311, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 548271000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 312, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,     0, 783261000, BW_UNKNOWN, MOD_UNKNOWN},    
    { 313, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,   0x0,	   0, 615300000, BW_8_MHz, MOD_PSK_8}
};

static SVL_DATA_T    t_svl_table_SuZhou_DVBT[] = 
{
    /*channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type,     ch_name,   tv_sys,            audio_sys,           vid_color_sys*/  
    {  1, 0x0000060F,   4164,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC ONE", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    {  2, 0x0000060F,   4228,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC TWO", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {  3, 0x0000060F,   4351,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC THREE", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {  4, 0x0000060F,   4415,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC NEWS 24", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    {  5, 0x0000060F,   4479,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBCi", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {  6, 0x0000060F,   4671,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CBBC Channel", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN}, 
    {  7, 0x0000060F,   1000, 108, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "MPEG2", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    {  8, 0x0000060F,   1001, 108, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "H264_2", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    {  9, 0x0000060F,   1002, 108, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "H264_8", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    { 10, 0x0000060F,   1003, 108, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "H264_12", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},    
    { 11, 0x0000060F,   1004, 108, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "H264_4", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},    
    { 12, 0x0000060F,      2, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "B1", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},    
    { 13, 0x0000060F,      5, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "B4", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    { 14, 0x0000060F,      6, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "B5", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},    
    { 15, 0x0000060F,      1, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "75% colour bars", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {900, 0x0000100F,  12368, 301, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_L_PRIME, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},     
    {901, 0x0000100F,   4424, 302, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_B | TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},    
    {902, 0x0000100F,  30305, 303, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B | TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},    
    {903, 0x0000100F,   2048, 304, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D | TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},    
    {904, 0x0000100F,    256, 305, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B | TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},   
    {905, 0x0000100F,    256, 306, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D | TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},    
    {906, 0x0000100F,    256, 307, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_I , AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},   
    {907, 0x0000100F,   2048, 308, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D | TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN}, 
    {908, 0x0000100F,  12368, 309, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_I , AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},   
    {909, 0x0000100F,  12368, 310, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B | TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},   
    {910, 0x0000100F,    256, 311, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B | TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},  
    {911, 0x0000100F,  30305, 312, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D | TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},   
    {912, 0x0000100F,  30305, 312, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D | TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},  
    {913, 0x0000100F,  58132, 313, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D | TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM | AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN}
};
#endif /* APP_DVBT_SUPPORT */

static TSL_DATA_T    t_tsl_table_Poland[] =
{
/* tsl_rec_id, bcst_type,              bcst_medium,        nw_id,  on_id,  ts_id, flags,   freq,   bandwidth,  mod     */
    { 81,  BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL, 12307, 9018, 16384,     0, 490000000, BW_8_MHz, MOD_VSB_8},
    {109,  BRDCST_TYPE_DVB, BRDCST_MEDIUM_DIG_TERRESTRIAL, 12293, 9018,  4100,     0, 658000000, BW_8_MHz, MOD_VSB_8},
    {301,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 335250000, BW_8_MHz, MOD_PSK_8},
    {302,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 360250000, BW_8_MHz, MOD_PSK_8},
    {303,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 615250000, BW_8_MHz, MOD_PSK_8},
    {304,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 527250000, BW_8_MHz, MOD_PSK_8},
    {305,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0,  49750000, BW_8_MHz, MOD_PSK_8},
    {306,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 119250000, BW_8_MHz, MOD_PSK_8},
    {307,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 184000000, BW_8_MHz, MOD_PSK_8},
    {308,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 217250000, BW_8_MHz, MOD_PSK_8},
    {309,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 224250000, BW_8_MHz, MOD_PSK_8},
    {310,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 280250000, BW_8_MHz, MOD_PSK_8},
    {311,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 304250000, BW_8_MHz, MOD_PSK_8},
    {312,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 448250000, BW_8_MHz, MOD_PSK_8},
    {313,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 503250000, BW_8_MHz, MOD_PSK_8},
    {314,  BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0x0,    0x0,     0, 783250000, BW_8_MHz, MOD_PSK_8}
};

static SVL_DATA_T    t_svl_table_Poland[] =
{
/*channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type,     ch_name,   tv_sys,            audio_sys,           vid_color_sys*/
    {  1, 0x0000060F,  16768,  81, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "Moving Picture", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  2, 0x0000060F,  16832,  81, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "Monoscope", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  3, 0x0000060F,  16960,  81, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "Color Bar", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  4, 0x0004060F,   4164, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC ONE", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  5, 0x0004060F,   4228, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC TWO", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  6, 0x0004060F,   4351, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC CHOICE", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  7, 0x0004060F,   4415, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC NEWS 24", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  8, 0x0004060F,   4479, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBCi", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {  9, 0x0004060F,   4607, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "BBC Knowledge", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    { 10, 0x00040A0F,   4543, 109, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_RADIO, "BBC PARLMNT", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
    {900, 0x0000100F,  12339, 301, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {901, 0x0000100F,  14644, 302, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {902, 0x0000100F,  65535, 303, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "ARD", TV_SYS_MASK_I, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {903, 0x0000100F,   1792, 304, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "BBC1", TV_SYS_MASK_I, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {904, 0x0000100F,   1792, 305, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {905, 0x0000100F,  65535, 306, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_FM_A2, COLOR_SYS_UNKNOWN},
    {906, 0x0000100F,  65535, 307, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_L, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {907, 0x0000100F,   4680, 308, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {908, 0x0000100F,   4372, 309, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_B|TV_SYS_MASK_G, AUDIO_SYS_MASK_FM_A2, COLOR_SYS_UNKNOWN},
    {909, 0x0000100F,  13872, 310, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {910, 0x0000100F,  12849, 311, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {911, 0x0000100F,  13624, 312, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {912, 0x0000100F,  42368, 313, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_I, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN},
    {913, 0x0000100F,  65535, 314, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_D|TV_SYS_MASK_K, AUDIO_SYS_MASK_NICAM|AUDIO_SYS_MASK_FM_MONO, COLOR_SYS_UNKNOWN}
};

#if defined(APP_TWN_SUPPORT)
static TSL_DATA_T    t_tsl_table_TWN[] = 
{	
    /* tsl_rec_id, bcst_type,              bcst_medium,                                        nw_id,  on_id,  ts_id,	 flags,               freq,  bandwidth, mod	  */		
    { 88,  BRDCST_TYPE_DVB,    BRDCST_MEDIUM_DIG_TERRESTRIAL, 13092, 8350,  1,  0, 533000000, BW_6_MHz, MOD_VSB_8},
    { 90,  BRDCST_TYPE_DVB,    BRDCST_MEDIUM_DIG_TERRESTRIAL, 13094, 8350,	1,	0, 545000000, BW_6_MHz, MOD_VSB_8},
    { 92,  BRDCST_TYPE_DVB,    BRDCST_MEDIUM_DIG_TERRESTRIAL, 13096, 8350,	1,	0, 557000000, BW_6_MHz, MOD_VSB_8},
    { 96,  BRDCST_TYPE_DVB,    BRDCST_MEDIUM_DIG_TERRESTRIAL, 13106, 8350,	1,	0, 581000000, BW_6_MHz, MOD_VSB_8},
    { 98,  BRDCST_TYPE_DVB,    BRDCST_MEDIUM_DIG_TERRESTRIAL, 13108, 8350,	1,	0, 593000000, BW_6_MHz, MOD_VSB_8},
};

static SVL_DATA_T    t_svl_table_TWN[] = 
{   
    {  1, 0x0000220f,   100,  88, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CTV1",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    {  2, 0x0000220f,   101,  88, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CTV2",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN}, 
    {  3, 0x0000220f,   102,  88, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CTV3",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {  4, 0x0000220f,   200,  90, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "PTS1",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN}, 
    {  5, 0x0000220f,   201,  90, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "PTS2",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},    
    {  6, 0x0000220f,   202,  90, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "PTS3",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {  7, 0x0000220f,   300,  92, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "MT1",   TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    {  8, 0x0000220f,   301,  92, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "MT2",   TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},     
    {  9, 0x0000220f,   302,  92, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "MT3",   TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    { 10, 0x0000220f,   400,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CCTV1", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    { 11, 0x0000220f,   401,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CCTV2", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    { 12, 0x0000220f,   404,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CCTV Radio", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    { 13, 0x0000220f,   402,  96, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CCTV3", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    { 14, 0x0000220f,   501,  98, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CTS",   TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},   
    { 15, 0x0000220f,   502,  98, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CTS1",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},  
    { 16, 0x0000220f,   503,  98, BRDCST_TYPE_DVB, SVL_SERVICE_TYPE_TV, "CTS2",  TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_UNKNOWN},
};
#endif /* APP_TWN_SUPPORT */

static TSL_DATA_T    t_tsl_table_SuZhou_antenna[] =
{
    /* tsl_rec_id, bcst_type,              bcst_medium,                                        nw_id,  on_id,  ts_id,    flags,               freq,  bandwidth, mod   */
    {      2,   BRDCST_TYPE_ATSC, BRDCST_MEDIUM_DIG_TERRESTRIAL,  0,    2,  2,   0,   57000000, BW_6_MHz, MOD_VSB_8},
    {     22,   BRDCST_TYPE_ATSC, BRDCST_MEDIUM_DIG_TERRESTRIAL,  0,    2,  2,   0,  521000000, BW_6_MHz, MOD_VSB_8},
    {     24,   BRDCST_TYPE_ATSC, BRDCST_MEDIUM_DIG_TERRESTRIAL,  0,    2,  2,   0,  533000000, BW_6_MHz, MOD_VSB_8},
    { 0x800a, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0,  2,   0,  193250000, BW_6_MHz, MOD_PSK_8},
    { 0x800f, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,    0,  2,   0,  477250000, BW_6_MHz, MOD_PSK_8},
    { 0x8045, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_TERRESTRIAL,  0,  0x0,  2,   0,  801250000, BW_6_MHz, MOD_PSK_8}

};


static TSL_DATA_T    t_tsl_table_SuZhou_cable[] =
{
    /* tsl_rec_id, bcst_type,              bcst_medium,        nw_id,  on_id,  ts_id, flags,   freq,   bandwidth,  mod     */
    {     50,   BRDCST_TYPE_ATSC, BRDCST_MEDIUM_DIG_CABLE,  0,   50,      2,     0, 381000000, BW_6_MHz, MOD_QAM_256},
    {      2,   BRDCST_TYPE_ATSC, BRDCST_MEDIUM_DIG_CABLE,  0,    2,      2,     0,  57000000, BW_6_MHz,   MOD_VSB_8},
    {    135,   BRDCST_TYPE_ATSC, BRDCST_MEDIUM_DIG_CABLE,  0,  135,      2,     0, 861000000, BW_6_MHz, MOD_QAM_256},
    { 0x800a, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_CABLE,  0,    0,   0x02,     0, 193250000, BW_6_MHz,   MOD_PSK_8},
    { 0x8042, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_CABLE,  0,    0,   0x02,     0, 474000000, BW_6_MHz,   MOD_PSK_8},
    { 0x807d, BRDCST_TYPE_ANALOG, BRDCST_MEDIUM_ANA_CABLE,  0,    0,   0x02,     0, 799250000, BW_6_MHz,   MOD_PSK_8}
};

static TSL_DATA_T    t_tsl_table_XM_antenna[] =	// Ben 20161206
{
    /* tsl_rec_id, bcst_type, bcst_medium, nw_id, on_id, ts_id,   flags, freq,  bandwidth, mod */
    {0x19  ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	25,	2345,	0,	539000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x8003,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	61250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8009,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	187250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0xd   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0xd   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0xd   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x400d,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x400d,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x400d,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_TERRESTRIAL,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x8010,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	481300000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x801d,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	561250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x801e,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	567250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8025,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	607300000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8026,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	615250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x803f,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_TERRESTRIAL,	0,	0,	0,	0,	765250000,	BW_UNKNOWN,	MOD_PSK_8},

};



static TSL_DATA_T    t_tsl_table_XM_cable[] =	// Ben 20161206
{
    /* tsl_rec_id, bcst_type, bcst_medium, nw_id, on_id, ts_id,   flags, freq,  bandwidth, mod */
    {0x8003,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	61250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x4f  ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	79,	741,	0,	555000000,	BW_UNKNOWN,	MOD_QAM_256},
    {0x4f  ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	79,	741,	0,	555000000,	BW_UNKNOWN,	MOD_QAM_256},
    {0x8009,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	187250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0xd   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0xd   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0xd   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	13,	2083,	0,	213000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x2   ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	2,	1,	0,	57000000,	BW_UNKNOWN,	MOD_VSB_8},
    {0x14  ,	BRDCST_TYPE_ATSC,	BRDCST_MEDIUM_DIG_CABLE,	0,	20,	1,	0,	159000000,	BW_UNKNOWN,	MOD_QAM_64},
    {0x8043,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	481250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8050,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	561250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8051,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	567250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8058,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	607250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8059,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	615250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8062,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	109250000,	BW_UNKNOWN,	MOD_PSK_8},
    {0x8077,	BRDCST_TYPE_ANALOG,	BRDCST_MEDIUM_ANA_CABLE,	0,	0,	0,	0,	765250000,	BW_UNKNOWN,	MOD_PSK_8},

};



static SVL_DATA_T    t_svl_table_XM_antenna[] =	// Ben 20161206
{
    /* channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type, ch_name, tv_sys, audio_sys, vid_color_sys*/
    {0x80100   ,	0x200000f ,	1,	0x19  ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"WCBS-DT",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0xc0080   ,	0x200000f ,	0,	0x8003,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x240080  ,	0x200000f ,	0,	0x8009,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x280100  ,	0x200000f ,	3,	0xd   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"KLVXHD",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x280200  ,	0x200000f ,	4,	0xd   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"KLVXSD1",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x280300  ,	0x200000f ,	5,	0xd   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"KLVXSD2",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0xd000640 ,	0x200000f ,	6,	0x400d,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"RF13-6",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0xd000740 ,	0x200000f ,	7,	0x400d,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"RF13-7",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0xd000840 ,	0x200000f ,	8,	0x400d,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"RF13-8",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380100  ,	0x200000f ,	1,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-1",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380200  ,	0x200000f ,	2,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-2",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380300  ,	0x200000f ,	3,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-3",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380400  ,	0x200000f ,	4,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-4",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380500  ,	0x200000f ,	5,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-5",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380600  ,	0x200000f ,	6,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-6",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x400080  ,	0x200000f ,	0,	0x8010,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"WGBH12",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x740080  ,	0x200000f ,	0,	0x801d,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x780080  ,	0x200000f ,	0,	0x801e,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x940080  ,	0x200000f ,	0,	0x8025,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x980080  ,	0x200000f ,	0,	0x8026,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0xfc0080  ,	0x200000f ,	0,	0x803f,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},

};


static SVL_DATA_T    t_svl_table_XM_cable[] =	// Ben 20161206
{
    /* channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type, ch_name, tv_sys, audio_sys, vid_color_sys*/
    {0xc0080   ,	0x200000f ,	0,	0x8003,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"WGBH12",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x140100  ,	0x200000f ,	3,	0x4f  ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"WAGA-HD",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x140200  ,	0x200000f ,	4,	0x4f  ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"WAGA-SD",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x240080  ,	0x200000f ,	0,	0x8009,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x280100  ,	0x200000f ,	3,	0xd   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"KLVXHD",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x280200  ,	0x200000f ,	4,	0xd   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"KLVXSD1",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x280300  ,	0x200000f ,	5,	0xd   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"KLVXSD2",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380100  ,	0x200000f ,	1,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-1",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380200  ,	0x200000f ,	2,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-2",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380300  ,	0x200000f ,	3,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-3",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380400  ,	0x200000f ,	4,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-4",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380500  ,	0x200000f ,	5,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-5",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x380600  ,	0x200000f ,	6,	0x2   ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"CH-6",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x780200  ,	0x200000f ,	2,	0x14  ,	BRDCST_TYPE_ATSC,	SVL_SERVICE_TYPE_TV,	"Unnamed",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_NTSC},
    {0x10c0080 ,	0x200000f ,	0,	0x8043,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x1400080 ,	0x200000f ,	0,	0x8050,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x1440080 ,	0x200000f ,	0,	0x8051,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x1600080 ,	0x200000f ,	0,	0x8058,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x1640080 ,	0x200000f ,	0,	0x8059,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x1880080 ,	0x200000f ,	0,	0x8062,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},
    {0x1dc0080 ,	0x200000f ,	0,	0x8077,	BRDCST_TYPE_ANALOG,	SVL_SERVICE_TYPE_TV,	"",	TV_SYS_MASK_NONE,	AUDIO_SYS_MASK_NONE,	COLOR_SYS_UNKNOWN},

};

static SVL_DATA_T    t_svl_table_SuZhou_antenna[] =
{
    /*channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type,     ch_name,   tv_sys,            audio_sys,           vid_color_sys*/
    {2, 15, 101,  2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "8-1", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{3, 15, 102,  2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "8-2", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{4, 15, 103,  2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "8-3", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{5, 15, 104,  2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "8-4", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{6, 15, 201,  22, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "28-1", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{7, 15, 202,  22, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "28-2", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{8, 15, 203,  22, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "28-3", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{9, 15, 204,  22, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "28-4", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{10, 15, 301, 24, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-3", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{11, 15, 302,  24, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-4", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{12, 15, 303,  24, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-5", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
	{13, 15, 304,  24, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-6", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
    {10, 15, 0, 0x800a, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_M, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
    {15, 15, 0, 0x800f, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_M, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
    {69, 15, 0, 0x8045, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_M, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC}

};

static SVL_DATA_T    t_svl_table_SuZhou_cable[] =
{
/*channel_num, nw_mask, prog_id, tsl_rec_id, brdcst_type, serv_type,     ch_name,   tv_sys,            audio_sys,           vid_color_sys*/
    {50, 15, 60, 50, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "50-60", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {51, 15, 67, 50, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "50-67", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {52, 15, 68, 50, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "50-68", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {53, 15, 69, 50, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "50-69", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
	{80, 15, 3, 2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-3", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {81, 15, 4, 2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-4", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {82, 15, 5, 2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-5", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {83, 15, 6, 2, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "80-6", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {90, 15, 1, 135, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "90-1", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {91, 15, 2, 135, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "91-2", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {92, 15, 4, 135, BRDCST_TYPE_ATSC, SVL_SERVICE_TYPE_TV, "93-4", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE , COLOR_SYS_NTSC},
    {10, 15, 0, 0x800a, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
    {66, 15, 0, 0x8042, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_NONE, AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC},
    {125, 15, 0, 0x807d, BRDCST_TYPE_ANALOG, SVL_SERVICE_TYPE_TV, "", TV_SYS_MASK_NONE , AUDIO_SYS_MASK_NONE, COLOR_SYS_NTSC}
};
/*-----------------------------------------------------------------------------
                    internal functions declarations
-----------------------------------------------------------------------------*/
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
 * Name: _get_macro_tuner_mod
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
    #if defined (APP_DVBT_SUPPORT) || defined (APP_ISDB_SUPPORT)
        c_strcpy (ps_macro ,"BRDCST_TYPE_UNKNOWN") ;
    #else
        c_strcpy (ps_macro ,"BRDCST_TYPE_ATSC") ;
    #endif
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
 * Name: _dump_atsc_air_channel_table
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _dump_atsc_cable_channel_table (VOID)
{
    SVL_REC_T   t_svl_rec;
    TSL_REC_T   t_tsl_rec;
    UINT32 ui4_ver_id;   
    RMV_DEV_OPEN_ID_T   e_open_id ;
    CHAR                        s_mount_point[512]   = {0};
    SIZE_T                      t_mount_point_size   = 511;
    CHAR                        s_filename[512 + 64] = {0};
    UINT32                      ui4_usb_idx = 0 ;

    HANDLE_T h_fm_dev_svl;
    HANDLE_T h_fm_dev_tsl;
    INT32 i4_ret;
    CHAR s_bandwidth[50];
    CHAR s_tuner_mod[50];

    UINT32 ui4_write;
    UINT32 ui4_count;
    CHAR string_buf[512];
    CHAR s_brdcst_type[50] = {0},
          s_serv_type[50] = {0},
          s_bcst_medium[50] = {0},
          s_tv_sys[50] = {0},
          s_vid_color_sys[50] = {0};

    UINT16 ui2_svl_rec_id;
    UINT16 ui2_num_recs = 0;
    UINT32 ui4_freq = 0;

    UINT32 ui4_mnt_count = 0, ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    
    //ke_vizio_20110330 for clean warning.
    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

    c_svl_lock(h_g_acfg_svl_cable);
    c_tsl_lock(h_g_acfg_tsl_cable);


    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    INX_LOG_ON_FAIL(i4_ret);
    
    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
        {
            continue;
        }
        break;
        
    }
    i4_ret = a_rmv_dev_set_active_mnt_pnt(ui4_mnt_point_idx);
    INX_LOG_ON_FAIL(i4_ret);
    
    /* Get current active mount point */
    i4_ret = a_rmv_dev_get_active_mnt_pnt(
                                &ui4_usb_idx, 
                                &t_mount_point_size, 
                                s_mount_point);
    if(i4_ret == RMVR_NO_DEVICE)
    {
        DBG_LOG_PRINT(("!!!NO DEVICE\n"));
    }
    else if(i4_ret == RMVR_OK)
    {
        DBG_LOG_PRINT(("Dump to USB start\n"));
        /* Open mount point */
        a_rmv_dev_open_mnt_point (ui4_usb_idx, &e_open_id);
        ////////////////////////////////////////////////////////////////////////
    
    
        /* Open svl_table file*/
        c_sprintf(s_filename,"%s/cable_svl_table.txt",s_mount_point);
        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                           s_filename,
                           FM_READ_WRITE | FM_OPEN_CREATE | FM_OPEN_TRUNC,
                           0777,
                           FALSE,
                           &h_fm_dev_svl);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open dev file: %s\n", s_filename));
        }

        /* Open tsl_table file*/
        c_sprintf(s_filename,"%s/cable_tsl_table.txt",s_mount_point);
        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                           s_filename,
                           FM_READ_WRITE | FM_OPEN_CREATE | FM_OPEN_TRUNC,
                           0777,
                           FALSE,
                           &h_fm_dev_tsl);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open dev file: %s\n", s_filename));
        }
    
    
        c_memset(string_buf, 0, sizeof(CHAR)*512);
        c_sprintf(string_buf,"%s%s",SVL_DATA_CABLE_PREFIX, SVL_INFO_FORMAT);
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_svl, string_buf, ui4_count, &ui4_write);

        // Head
        c_memset(string_buf, 0, sizeof(CHAR)*512);
        c_sprintf(string_buf,"%s%s",TSL_DATA_CABLE_PREFIX, TSL_INFO_FORMAT);
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_tsl, string_buf, ui4_count, &ui4_write);
        
        i4_ret = c_svl_get_num_rec_by_brdcst_type (h_g_acfg_svl_cable,
                                                   BRDCST_TYPE_UNKNOWN,
                                                   SB_VNET_ALL,
                                                   &ui2_num_recs,
                                                   &ui4_ver_id);
        //DBG_LOG_PRINT("cable ui2_num_recs: %d\n", ui2_num_recs);

        for (ui2_svl_rec_id = 0 ; TRUE ; ui2_svl_rec_id ++)
        {   
        
            i4_ret = c_svl_get_rec_by_brdcst_type(h_g_acfg_svl_cable,
                                         BRDCST_TYPE_UNKNOWN,
                                         0XFFFF,
                                         ui2_svl_rec_id,
                                         &t_svl_rec,
                                         &ui4_ver_id);
            if(i4_ret == SVLR_REC_NOT_FOUND)
            {
                //DBG_LOG_PRINT("SVLR_REC_NOT_FOUND\n");
                break;
            }
            
            if (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
            {
                /* skip fake channel */
                continue ;
            }
            //DBG_LOG_PRINT("\n\n SVLR_REC_FOUND\n");
            c_memset(string_buf, 0, sizeof(CHAR)*512);
            c_memset(s_brdcst_type, 0, sizeof(CHAR)*50);
            c_memset(s_serv_type, 0, sizeof(CHAR)*50);
            c_memset(s_vid_color_sys, 0, sizeof(CHAR)*50);
            c_memset(s_tv_sys, 0, sizeof(CHAR)*50);
            
            _get_macro_bcst_type(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type, s_brdcst_type);
            //DBG_LOG_PRINT("%s\n", s_brdcst_type);
            
            _get_macro_serv_type(t_svl_rec.uheader.t_rec_hdr.e_serv_type, s_serv_type);
            //DBG_LOG_PRINT("%s\n", s_serv_type);
        
            _get_macro_colr_sys(t_svl_rec.u_data.t_analog.e_vid_color_sys, s_vid_color_sys);
            //DBG_LOG_PRINT("%s\n", s_vid_color_sys);

            _get_macro_tv_sys(t_svl_rec.u_data.t_analog.ui4_tv_sys, s_tv_sys);
            //DBG_LOG_PRINT("%s\n", s_tv_sys);
            
            //Cable SVL Info
            c_snprintf(string_buf, 511, SVL_INFO,
                       t_svl_rec.uheader.t_rec_hdr.ui4_channel_id,
                       t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask,
                       t_svl_rec.uheader.t_rec_hdr.ui2_prog_id,
                       t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                       s_brdcst_type,
                       s_serv_type,
                       t_svl_rec.uheader.t_rec_hdr.ac_name,
                       s_tv_sys,
                       "AUDIO_SYS_MASK_NONE",
                       s_vid_color_sys
                       );
                       
            ui4_count = c_strlen(string_buf);
            c_fm_write(h_fm_dev_svl, string_buf, ui4_count, &ui4_write);
        /////////////////////////////////////////////////////////////////
            //TSL Info
            c_tsl_get_rec(h_g_acfg_tsl_cable,
                         t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                         &t_tsl_rec,
                         &ui4_ver_id);
            

            //DBG_LOG_PRINT("tsl rec id = %d\n",t_tsl_rec.ui2_tsl_rec_id);

            c_memset(s_brdcst_type, 0, sizeof(CHAR)*50);
            c_memset(s_bcst_medium, 0, sizeof(CHAR)*50);
            c_memset(s_bandwidth, 0, sizeof(CHAR)*50);
 
            _get_macro_bcst_type(t_tsl_rec.uheader.t_desc.e_bcst_type, s_brdcst_type);
            //DBG_LOG_PRINT("s_brdcst_type = %s\n", s_brdcst_type);

            _get_macro_bcst_medium(t_tsl_rec.uheader.t_desc.e_bcst_medium, s_bcst_medium);
            //DBG_LOG_PRINT("s_bcst_medium = %s\n", s_bcst_medium);

            _get_macro_bandwidth(t_tsl_rec.udata.t_ter_dig.e_bandwidth, s_bandwidth);  //Only useful for air digital
            //DBG_LOG_PRINT("s_bandwidth = %s\n", s_bandwidth);

            if(t_tsl_rec.uheader.t_desc.e_bcst_type == BRDCST_TYPE_ANALOG)
            {
                _get_macro_tuner_mod(t_tsl_rec.udata.t_cab_ana.e_mod, s_tuner_mod);
                ui4_freq = t_tsl_rec.udata.t_cab_ana.ui4_freq;
            }
            else
            {
                _get_macro_tuner_mod(t_tsl_rec.udata.t_cab_dig.e_mod, s_tuner_mod);
                ui4_freq = t_tsl_rec.udata.t_cab_dig.ui4_freq;
            }

            
            //Cable TSL Info
            c_memset(string_buf, 0, sizeof(CHAR)*512);
            c_snprintf(string_buf, 511, TSL_INFO,
                       t_tsl_rec.ui2_tsl_rec_id,
                       s_brdcst_type,
                       s_bcst_medium,
                       t_tsl_rec.uheader.t_desc.ui2_nw_id,
                       t_tsl_rec.uheader.t_desc.ui2_on_id,
                       t_tsl_rec.uheader.t_desc.ui2_ts_id,
                       t_tsl_rec.uheader.t_desc.ui1_flags,
                       ui4_freq,
                       s_bandwidth,  // Only Aatenna digtal has this item.
                       s_tuner_mod
                       );
                   
            ui4_count = c_strlen(string_buf);
            c_fm_write(h_fm_dev_tsl, string_buf, ui4_count, &ui4_write);
        }
    
        ////////////////////////////////////////////////////////////////    
        c_memset(string_buf, 0, sizeof(CHAR)*512);
        c_sprintf(string_buf,"%s", INFO_END);
        
        //SVL End
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_svl, string_buf, ui4_count, &ui4_write);

        //TSL End
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_tsl, string_buf, ui4_count, &ui4_write);
    
    
        c_fm_close(h_fm_dev_svl);
        c_fm_close(h_fm_dev_tsl);

        a_rmv_dev_close_mnt_point (e_open_id);
    }

    c_svl_unlock(h_g_acfg_svl_cable);
    c_tsl_unlock(h_g_acfg_tsl_cable);
}
/*-----------------------------------------------------------------------------
 * Name: _dump_atsc_antenna_channel_table
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _dump_atsc_antenna_channel_table ()
{
    SVL_REC_T   t_svl_rec;
    TSL_REC_T   t_tsl_rec;
    UINT32 ui4_ver_id;   
    RMV_DEV_OPEN_ID_T   e_open_id ;
    CHAR                        s_mount_point[512]   = {0};
    SIZE_T                      t_mount_point_size   = 511;
    CHAR                        s_filename[512 + 64] = {0};
    UINT32                      ui4_usb_idx = 0 ;

    HANDLE_T h_fm_dev_svl;
    HANDLE_T h_fm_dev_tsl;
    INT32 i4_ret;
    CHAR s_bandwidth[50];
    CHAR s_tuner_mod[50];

    UINT32 ui4_write;
    UINT32 ui4_count;
    CHAR string_buf[512];
    CHAR s_brdcst_type[50] = {0},
          s_serv_type[50] = {0},
          s_bcst_medium[50] = {0},
          s_tv_sys[50] = {0},
          s_vid_color_sys[50] = {0};

    UINT16 ui2_svl_rec_id;
    UINT16 ui2_num_recs = 0;
    UINT32 ui4_freq = 0;

    //ke_vizio_20110330 for clean warning.
    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));
    
    c_svl_lock(h_g_acfg_svl_air);
    c_tsl_lock(h_g_acfg_tsl_air);
    
    /* Get current active mount point */
    i4_ret = a_rmv_dev_get_active_mnt_pnt(
                                &ui4_usb_idx, 
                                &t_mount_point_size, 
                                s_mount_point);
    if(i4_ret == RMVR_NO_DEVICE)
    {
        DBG_LOG_PRINT(("!!!NO DEVICE\n"));
    }
    else if(i4_ret == RMVR_OK)
    {
        DBG_LOG_PRINT(("Dump to USB start\n"));
        /* Open mount point */
        a_rmv_dev_open_mnt_point (ui4_usb_idx, &e_open_id);
        ////////////////////////////////////////////////////////////////////////
    
    
        /* Open svl_table file*/
        c_sprintf(s_filename,"%s/antenna_svl_table.txt",s_mount_point);
        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                           s_filename,
                           FM_READ_WRITE | FM_OPEN_CREATE | FM_OPEN_TRUNC,
                           0777,
                           FALSE,
                           &h_fm_dev_svl);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open dev file: %s\n", s_filename));
        }

        /* Open tsl_table file*/
        c_sprintf(s_filename,"%s/antenna_tsl_table.txt",s_mount_point);
        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                           s_filename,
                           FM_READ_WRITE | FM_OPEN_CREATE | FM_OPEN_TRUNC,
                           0777,
                           FALSE,
                           &h_fm_dev_tsl);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open dev file: %s\n", s_filename));
        }
    
    
        c_memset(string_buf, 0, sizeof(CHAR)*512);
        c_sprintf(string_buf,"%s%s",SVL_DATA_ANTENNA_PREFIX, SVL_INFO_FORMAT);
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_svl, string_buf, ui4_count, &ui4_write);

        // Head
        c_memset(string_buf, 0, sizeof(CHAR)*512);
        c_sprintf(string_buf,"%s%s",TSL_DATA_ANTENNA_PREFIX, TSL_INFO_FORMAT);
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_tsl, string_buf, ui4_count, &ui4_write);
        
        i4_ret = c_svl_get_num_rec_by_brdcst_type (h_g_acfg_svl_air,
                                                   BRDCST_TYPE_UNKNOWN,
                                                   SB_VNET_ALL,
                                                   &ui2_num_recs,
                                                   &ui4_ver_id);
        //DBG_LOG_PRINT("cable ui2_num_recs: %d\n", ui2_num_recs);

        for (ui2_svl_rec_id = 0 ; TRUE ; ui2_svl_rec_id ++)
        {   
        
            //DBG_LOG_PRINT("ui2_svl_rec_id : %d\n", ui2_svl_rec_id);
        
            i4_ret = c_svl_get_rec_by_brdcst_type(h_g_acfg_svl_air,
                                         BRDCST_TYPE_UNKNOWN,
                                         0XFFFF,
                                         ui2_svl_rec_id,
                                         &t_svl_rec,
                                         &ui4_ver_id);
            if(i4_ret == SVLR_REC_NOT_FOUND)
            {
                //DBG_LOG_PRINT("SVLR_REC_NOT_FOUND\n");
                break;
            }
            
            if (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
            {
                /* skip fake channel */
                //DBG_LOG_PRINT("skip fake channel : ui4_nw_mask : 0x%X\n", t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask);
                continue ;
            }
            //DBG_LOG_PRINT("\n\n SVLR_REC_FOUND\n");
            c_memset(string_buf, 0, sizeof(CHAR)*512);
            c_memset(s_brdcst_type, 0, sizeof(CHAR)*50);
            c_memset(s_serv_type, 0, sizeof(CHAR)*50);
            c_memset(s_vid_color_sys, 0, sizeof(CHAR)*50);
            c_memset(s_tv_sys, 0, sizeof(CHAR)*50);
            
            _get_macro_bcst_type(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type, s_brdcst_type);
            //DBG_LOG_PRINT("%s\n", s_brdcst_type);
            
            _get_macro_serv_type(t_svl_rec.uheader.t_rec_hdr.e_serv_type, s_serv_type);
            //DBG_LOG_PRINT("%s\n", s_serv_type);
        
            _get_macro_colr_sys(t_svl_rec.u_data.t_analog.e_vid_color_sys, s_vid_color_sys);
            //DBG_LOG_PRINT("%s\n", s_vid_color_sys);

            _get_macro_tv_sys(t_svl_rec.u_data.t_analog.ui4_tv_sys, s_tv_sys);
            //DBG_LOG_PRINT("%s\n", s_tv_sys);
            
            //Cable SVL Info
            c_snprintf(string_buf, 511, SVL_INFO,
                       t_svl_rec.uheader.t_rec_hdr.ui4_channel_id,
                       t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask,
                       t_svl_rec.uheader.t_rec_hdr.ui2_prog_id,
                       t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                       s_brdcst_type,
                       s_serv_type,
                       t_svl_rec.uheader.t_rec_hdr.ac_name,
                       s_tv_sys,
                       "AUDIO_SYS_MASK_NONE",
                       s_vid_color_sys
                       );
                       
            ui4_count = c_strlen(string_buf);
            c_fm_write(h_fm_dev_svl, string_buf, ui4_count, &ui4_write);
        /////////////////////////////////////////////////////////////////
            //TSL Info
            c_tsl_get_rec(h_g_acfg_tsl_air,
                         t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                         &t_tsl_rec,
                         &ui4_ver_id);
            

            //DBG_LOG_PRINT("tsl rec id = %d\n",t_tsl_rec.ui2_tsl_rec_id);

            c_memset(s_brdcst_type, 0, sizeof(CHAR)*50);
            c_memset(s_bcst_medium, 0, sizeof(CHAR)*50);
            c_memset(s_bandwidth, 0, sizeof(CHAR)*50);
 
            _get_macro_bcst_type(t_tsl_rec.uheader.t_desc.e_bcst_type, s_brdcst_type);
            //DBG_LOG_PRINT("s_brdcst_type = %s\n", s_brdcst_type);

            _get_macro_bcst_medium(t_tsl_rec.uheader.t_desc.e_bcst_medium, s_bcst_medium);
            //DBG_LOG_PRINT("s_bcst_medium = %s\n", s_bcst_medium);

            _get_macro_bandwidth(t_tsl_rec.udata.t_ter_dig.e_bandwidth, s_bandwidth);  //Only useful for air digital
            //DBG_LOG_PRINT("s_bandwidth = %s\n", s_bandwidth);

            if(t_tsl_rec.uheader.t_desc.e_bcst_type == BRDCST_TYPE_ANALOG)
            {
                _get_macro_tuner_mod(t_tsl_rec.udata.t_ter_ana.e_mod, s_tuner_mod);
                ui4_freq = t_tsl_rec.udata.t_ter_ana.ui4_freq;
            }
            else
            {
                _get_macro_tuner_mod(t_tsl_rec.udata.t_ter_dig.e_mod, s_tuner_mod);
                ui4_freq = t_tsl_rec.udata.t_ter_dig.ui4_freq;
            }

            
            //Cable TSL Info
            c_memset(string_buf, 0, sizeof(CHAR)*512);
            c_snprintf(string_buf, 511, TSL_INFO,
                       t_tsl_rec.ui2_tsl_rec_id,
                       s_brdcst_type,
                       s_bcst_medium,
                       t_tsl_rec.uheader.t_desc.ui2_nw_id,
                       t_tsl_rec.uheader.t_desc.ui2_on_id,
                       t_tsl_rec.uheader.t_desc.ui2_ts_id,
                       t_tsl_rec.uheader.t_desc.ui1_flags,
                       ui4_freq,
                       s_bandwidth,  // Only Aatenna digtal has to use this item.
                       s_tuner_mod
                       );
                   
            ui4_count = c_strlen(string_buf);
            c_fm_write(h_fm_dev_tsl, string_buf, ui4_count, &ui4_write);
        }
    
    ////////////////////////////////////////////////////////////////    
        c_memset(string_buf, 0, sizeof(CHAR)*512);
        c_sprintf(string_buf,"%s", INFO_END);
        
        //SVL End
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_svl, string_buf, ui4_count, &ui4_write);

        //TSL End
        ui4_count = c_strlen(string_buf);
        c_fm_write(h_fm_dev_tsl, string_buf, ui4_count, &ui4_write);
        

    ////////////////////////////////////////////////////////
    
        
        c_fm_close(h_fm_dev_svl);
        c_fm_close(h_fm_dev_tsl);

        a_rmv_dev_close_mnt_point (e_open_id);
    }

    c_svl_unlock(h_g_acfg_svl_air);
    c_tsl_unlock(h_g_acfg_tsl_air);
}

/*-----------------------------------------------------------------------------
                    external functions declarations
-----------------------------------------------------------------------------*/
INT32 acfg_INX_dump_channel_info(VOID)
{
    SVL_REC_T   t_svl_rec;
    TSL_REC_T   t_tsl_rec;
	UINT32 ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
	UINT32 ui4_ver_id;
	INT32 channel_ret;
	
    //ke_vizio_20110330 for clean warning.
    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

	/*Printf("[SAC.BM]ui4_channel_id=%ld\n",ui4_channel_id);	*/

    c_svl_lock(h_g_acfg_svl_cable);
    c_tsl_lock(h_g_acfg_tsl_cable);
    
    c_svl_lock(h_g_acfg_svl_air);
    c_tsl_lock(h_g_acfg_tsl_air);

    /* Show the SVL Info*/
    ui4_ver_id = SVL_NULL_VER_ID;
    channel_ret = c_svl_get_rec_by_channel(h_g_acfg_svl_cable,
                                ui4_channel_id,
                                SB_VNET_ALL,
                                0,
                                &t_svl_rec,
                                &ui4_ver_id);
	
	if( channel_ret != SVLR_OK ){//fix mtk warning, zlhuang
        DBG_LOG_PRINT(("%s(), %d: channel_ret=%d\n", __FUNCTION__, __LINE__, channel_ret));
        return APP_CFGR_INV_ARG;
    }

    DBG_LOG_PRINT(("SVL\n"));
    DBG_LOG_PRINT(("nw mask=%ld\n",t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask));
    DBG_LOG_PRINT(("prog id=%ld\n",t_svl_rec.uheader.t_rec_hdr.ui2_prog_id));
    DBG_LOG_PRINT(("tsl id=%ld\n",t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id));
    switch(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
     {
         case BRDCST_TYPE_ANALOG:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ANALOG\n"));
             break;
         case BRDCST_TYPE_DVB:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_DVB=\n"));
             break;
         case BRDCST_TYPE_ATSC:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ATSC\n"));
             break;
         case BRDCST_TYPE_SCTE:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_SCTE=\n"));
             break;
         default:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_UNKNOWN="));
             break;
     }
    switch(t_svl_rec.uheader.t_rec_hdr.e_serv_type)
     {
         case SVL_SERVICE_TYPE_TV:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_TV\n"));
             break;
         case SVL_SERVICE_TYPE_RADIO:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_RADIO=\n"));
             break;
         case SVL_SERVICE_TYPE_APP:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_APP=\n"));
             break;
         default:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_UNKNOWN=\n"));
             break;
     }
    DBG_LOG_PRINT(("%s=",t_svl_rec.uheader.t_rec_hdr.ac_name));
    if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_DVB)
     {
 	    DBG_LOG_PRINT(("TV_SYS_MASK_NONE="));
 	    DBG_LOG_PRINT(("AUDIO_SYS_MASK_NONE="));
 	    DBG_LOG_PRINT(("COLOR_SYS_UNKNOWN"));
     }
     else
     {
 	    DBG_LOG_PRINT(("tv sys =%d\n",t_svl_rec.u_data.t_analog.ui4_tv_sys));
 	    DBG_LOG_PRINT(("audio sys=%d\n",t_svl_rec.u_data.t_analog.ui4_audio_sys));
 	    DBG_LOG_PRINT(("color sys =%d\n",t_svl_rec.u_data.t_analog.e_vid_color_sys));
 	    DBG_LOG_PRINT(("valid	src id =%d\n"  ,t_svl_rec.u_data.t_analog.b_valid_src_id));
        DBG_LOG_PRINT(("src id =%d\n"  ,t_svl_rec.u_data.t_analog.ui2_src_id));
     }

 
     /* Show the TSL Info*/
 	ui4_ver_id = TSL_NULL_VER_ID;
    c_tsl_get_rec(h_g_acfg_tsl_cable,
                  t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                  &t_tsl_rec,
                  &ui4_ver_id);

     DBG_LOG_PRINT(("TSL\n"));
     DBG_LOG_PRINT(("tsl rec id =%ld\n",t_tsl_rec.ui2_tsl_rec_id));
     switch(t_tsl_rec.uheader.t_desc.e_bcst_type)
     {
         case BRDCST_TYPE_ANALOG:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ANALOG\n"));
             break;
         case BRDCST_TYPE_DVB:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_DVB="));
             break;
         case BRDCST_TYPE_ATSC:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ATSC\n"));
             break;
         case BRDCST_TYPE_SCTE:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_SCTE=\n"));
             break;
         default:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_UNKNOWN="));
             break;
     }
     switch(t_tsl_rec.uheader.t_desc.e_bcst_medium)
     {
         case BRDCST_MEDIUM_DIG_TERRESTRIAL:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_DIG_TERRESTRIAL\n"));
             break;
         case BRDCST_MEDIUM_DIG_CABLE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_DIG_CABLE\n"));
             break;
         case BRDCST_MEDIUM_DIG_SATELLITE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_DIG_SATELLITE=\n"));
             break;
         case BRDCST_MEDIUM_ANA_TERRESTRIAL:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_ANA_TERRESTRIAL\n"));
             break;
         case BRDCST_MEDIUM_ANA_CABLE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_ANA_CABLE\n"));
             break;
         case BRDCST_MEDIUM_ANA_SATELLITE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_ANA_SATELLITE=\n"));
             break;
         case BRDCST_MEDIUM_1394:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_1394="));
             break;
         default:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_UNKNOWN="));
             break;
     }
 	DBG_LOG_PRINT(("nw id=%ld\n",t_tsl_rec.uheader.t_desc.ui2_nw_id));
 	DBG_LOG_PRINT(("on id=%ld\n",t_tsl_rec.uheader.t_desc.ui2_on_id));
    DBG_LOG_PRINT(("ts id=%ld\n",t_tsl_rec.uheader.t_desc.ui2_ts_id));
 	DBG_LOG_PRINT(("flags=%ld\n",t_tsl_rec.uheader.t_desc.ui1_flags));
 	DBG_LOG_PRINT(("ter ana mod =%ld\n",t_tsl_rec.udata.t_ter_dig.e_mod));
 	DBG_LOG_PRINT(("cab dig mod =%ld\n",t_tsl_rec.udata.t_cab_dig.e_mod));
 	DBG_LOG_PRINT(("ter dig freq=%ld\n",t_tsl_rec.udata.t_ter_dig.ui4_freq));
 	DBG_LOG_PRINT(("cab dig freq=%ld\n",t_tsl_rec.udata.t_cab_dig.ui4_freq));

    c_svl_unlock(h_g_acfg_svl_cable);
    c_tsl_unlock(h_g_acfg_tsl_cable);

    c_svl_unlock(h_g_acfg_svl_air);
    c_tsl_unlock(h_g_acfg_tsl_air);

    
    _dump_atsc_antenna_channel_table();
    _dump_atsc_cable_channel_table();
    
    return APP_CFGR_OK;
}

INT32 acfg_INX_load_default_channel(CHAR* ui1_area)
{
    UINT16 ui2_i;
    SVL_REC_T t_svl_rec;
    TSL_REC_T t_tsl_rec;
    SVL_DATA_T* t_svl_data=NULL;
    TSL_DATA_T* t_tsl_data=NULL;
    UINT16 ui1_area_id;
    UINT16 ui2_svl_size=0;
    UINT16 ui2_tsl_size=0;
    
    INT32 i4_ret;
    UINT16 ui2_svl_rec_id_temp = 1;

    a_tv_stop(h_g_acfg_svctx_main);

    i4_ret = a_cfg_cust_fac_clear_ch_table();
    if(i4_ret != APP_CFGR_OK){
        return APP_CFGR_INV_ARG;
    }

#ifdef APP_DVBT_SUPPORT
    UINT32 ui4_first_channel_num=1;
    
    /* Area translate and check */
    if(c_strcmp(ui1_area,"FQ")==0)
    {      
        ui1_area_id=0;      
        ui2_tsl_size=sizeof(t_tsl_table_FuQing_DVBT)/sizeof(t_tsl_table_FuQing_DVBT[0]);      
        ui2_svl_size=sizeof(t_svl_table_FuQing_DVBT)/sizeof(t_svl_table_FuQing_DVBT[0]);      
    }    
    else if(c_strcmp(ui1_area,"SZ")==0)      
    {      
        ui1_area_id=1;      
        ui2_tsl_size=sizeof(t_tsl_table_SuZhou_DVBT)/sizeof(t_tsl_table_SuZhou_DVBT[0]);      
        ui2_svl_size=sizeof(t_svl_table_SuZhou_DVBT)/sizeof(t_svl_table_SuZhou_DVBT[0]);      
    }    
    else if(c_strcmp(ui1_area,"POL")==0)      
    {      
        ui1_area_id=2;      
        ui2_tsl_size=sizeof(t_tsl_table_Poland)/sizeof(t_tsl_table_Poland[0]);      
        ui2_svl_size=sizeof(t_svl_table_Poland)/sizeof(t_svl_table_Poland[0]);      
    }    
    else if(c_strcmp(ui1_area,"TWN")==0)      
    {      
        ui1_area_id=3;      
        ui2_tsl_size=sizeof(t_tsl_table_TWN)/sizeof(t_tsl_table_TWN[0]);      
        ui2_svl_size=sizeof(t_svl_table_TWN)/sizeof(t_svl_table_TWN[0]);      
    }    
    else      
    {      
        return APP_CFGR_INV_ARG;      
    }
    
    c_svl_lock(h_g_acfg_svl_air);    
    c_tsl_lock(h_g_acfg_tsl_air);    
    
    /* TSL Table Processing*/    
    for( ui2_i = 0; ui2_i < ui2_tsl_size; ui2_i++)    
    {        
        if(ui1_area_id==0)/* FQ */    	   
        {    	   
            t_tsl_data=&t_tsl_table_FuQing_DVBT[ui2_i];    	   
        }        
        else if(ui1_area_id==1)/* SZ */    	   
        {    	   
            t_tsl_data=&t_tsl_table_SuZhou_DVBT[ui2_i];
        }        
        else if(ui1_area_id==2)/* POL */    	   
        {    	  
            t_tsl_data=&t_tsl_table_Poland[ui2_i];
        }        
        else if(ui1_area_id==3)/* TWN */    	   
        {    	   
            t_tsl_data=&t_tsl_table_TWN[ui2_i];
        } 
        
        /* Update the TSL */
        c_tsl_rec_init(&t_tsl_rec);       
        t_tsl_rec.ui2_tsl_rec_id                = t_tsl_data->ui2_tsl_rec_id;		
        //Header
        t_tsl_rec.uheader.t_desc.e_bcst_type    = t_tsl_data->e_bcst_type;        
        t_tsl_rec.uheader.t_desc.e_bcst_medium  = t_tsl_data->e_bcst_medium;        
        t_tsl_rec.uheader.t_desc.ui2_nw_id = t_tsl_data->ui2_nw_id;        
        t_tsl_rec.uheader.t_desc.ui2_on_id = t_tsl_data->ui2_on_id;        
        t_tsl_rec.uheader.t_desc.ui2_ts_id = t_tsl_data->ui2_ts_id;        
        t_tsl_rec.uheader.t_desc.ui1_flags = t_tsl_data->ui1_flags;		
        
        //Part of Digital by Air
        t_tsl_rec.udata.t_ter_dig.ui4_freq = t_tsl_data->ui4_freq;        
        t_tsl_rec.udata.t_ter_dig.e_bandwidth = t_tsl_data->e_bandwidth;        
        t_tsl_rec.udata.t_ter_dig.e_mod = t_tsl_data->e_mod;        
        t_tsl_rec.udata.t_ter_dig.e_hierarchy_priority = HIR_PRIORITY_NONE;		
        
        //Part of Analog by Air
        t_tsl_rec.udata.t_ter_ana.ui4_freq      = t_tsl_data->ui4_freq;        
        t_tsl_rec.udata.t_ter_ana.e_pol         = POL_UNKNOWN;        
        t_tsl_rec.udata.t_ter_ana.ui2_dir       = 0;        
        t_tsl_rec.udata.t_ter_ana.ui2_gain      = 0;       
        t_tsl_rec.udata.t_ter_ana.e_mod         = t_tsl_data->e_mod;       
        t_tsl_rec.udata.t_ter_ana.b_fine_tune   = FALSE;        
        c_tsl_update_rec(h_g_acfg_tsl_air, &t_tsl_rec, FALSE);    
    }   

    /* SVLTable Processing*/    
    for( ui2_i = 0; ui2_i < ui2_svl_size; ui2_i++)    
    {       
        if(ui1_area_id==0)/* FQ */    	   
        {    	  
            t_svl_data=&t_svl_table_FuQing_DVBT[ui2_i];    	
        }        
        else if(ui1_area_id==1)/* SZ */    	  
        {    	  
            t_svl_data=&t_svl_table_SuZhou_DVBT[ui2_i];    	
        }        
        else if(ui1_area_id==2)/* POL */    
        {    	  
            t_svl_data=&t_svl_table_Poland[ui2_i];    	
        }    
        else if(ui1_area_id==3)/* TWN */    
        {    	  
            t_svl_data=&t_svl_table_TWN[ui2_i];   
        }       
        
        /* Update the SVL */       
        c_svl_rec_init(&t_svl_rec);        
        t_svl_rec.ui2_svl_rec_id = t_svl_data->ui4_channel_num;	
        
        //Header       
        t_svl_rec.uheader.t_rec_hdr.ui4_channel_id= SB_ATSC_GEN_ONE_PART_CHANNEL_ID(t_svl_data->ui4_channel_num, 0); 
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask   = t_svl_data->ui4_nw_mask;    
        t_svl_rec.uheader.t_rec_hdr.ui2_prog_id = t_svl_data->ui2_prog_id;   
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id    = 1;    
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id= t_svl_data->ui2_tsl_rec_id;   
        t_svl_rec.uheader.t_rec_hdr.e_brdcst_type = t_svl_data->e_brdcst_type;        
        t_svl_rec.uheader.t_rec_hdr.e_serv_type   = t_svl_data->e_serv_type;      
        c_strcpy(t_svl_rec.uheader.t_rec_hdr.ac_name,t_svl_data->ac_name);	
        
        //for Analog Only 
        t_svl_rec.u_data.t_analog.ui4_s_comp_mask = 0;     
        t_svl_rec.u_data.t_analog.ui4_tv_sys      = t_svl_data->ui4_tv_sys;    
        t_svl_rec.u_data.t_analog.ui4_audio_sys   = t_svl_data->ui4_audio_sys; 
        t_svl_rec.u_data.t_analog.e_vid_color_sys = t_svl_data->e_vid_color_sys;    
        t_svl_rec.u_data.t_analog.b_valid_src_id  = FALSE;   
        c_svl_update_rec(h_g_acfg_svl_air, &t_svl_rec, FALSE);	
        if(ui2_i==0)      
        {        
            ui4_first_channel_num=t_svl_data->ui4_channel_num;       
        }   
    }   
    
    c_svl_unlock(h_g_acfg_svl_air);   
    c_tsl_unlock(h_g_acfg_tsl_air);
    
    if ((h_g_acfg_svl_air != NULL_HANDLE) && (h_g_acfg_tsl_air != NULL_HANDLE))    
    {     
        c_svl_fs_store(FM_ROOT_HANDLE, ATSC_TRSTRL_SVL_FILE, ATSC_TRSTRL_SVL_ID);   
        c_tsl_fs_store(FM_ROOT_HANDLE, ATSC_TRSTRL_TSL_FILE, ATSC_TRSTRL_TSL_ID);   
    }
    
    a_tv_change_channel(h_g_acfg_svctx_main,    
                          SVCTX_STRM_MODE_AS_LAST,                     
                         SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_first_channel_num, 0),       
                         NULL);	
    nav_enable_ui_root_widget(TRUE);	
    a_amb_pause_app(MENU_NAME);
    
#else /* ATSC */

    UINT32  ui4_first_channel_id = 0,
            ui4_cable_first_channel_id = 0,
            ui4_antenna_first_channel_id = 0;
            
	/* Area translate and check */
    //-----antenna  start -------------------//
    if(c_strcmp(ui1_area,"FQ")==0)
    {
        ui1_area_id=0;
        ui2_tsl_size=sizeof(t_tsl_table_XM_antenna)/sizeof(t_tsl_table_XM_antenna[0]);
        ui2_svl_size=sizeof(t_svl_table_XM_antenna)/sizeof(t_svl_table_XM_antenna[0]);
    }
    else if(c_strcmp(ui1_area,"SZ")==0)
    {
        ui1_area_id=1;
        ui2_tsl_size=sizeof(t_tsl_table_SuZhou_antenna)/sizeof(t_tsl_table_SuZhou_antenna[0]);
        ui2_svl_size=sizeof(t_svl_table_SuZhou_antenna)/sizeof(t_svl_table_SuZhou_antenna[0]);
    }
    else
    {
        return APP_CFGR_INV_ARG;
    }

    c_svl_lock(h_g_acfg_svl_air);
    c_tsl_lock(h_g_acfg_tsl_air);

    /* TSL Table Processing*/
    for( ui2_i = 0; ui2_i < ui2_tsl_size; ui2_i++)
    {
        if(ui1_area_id==0)/* FQ */
        {
            t_tsl_data=&t_tsl_table_XM_antenna[ui2_i];
        }
        else if(ui1_area_id==1)/* SZ */
        {
            t_tsl_data=&t_tsl_table_SuZhou_antenna[ui2_i];
        }

        /* Update the TSL */
        c_tsl_rec_init(&t_tsl_rec);
        t_tsl_rec.ui2_tsl_rec_id                = t_tsl_data->ui2_tsl_rec_id;
		//Header
        t_tsl_rec.uheader.t_desc.e_bcst_type    = t_tsl_data->e_bcst_type;
        t_tsl_rec.uheader.t_desc.e_bcst_medium  = t_tsl_data->e_bcst_medium;
        t_tsl_rec.uheader.t_desc.ui2_nw_id = t_tsl_data->ui2_nw_id;
        t_tsl_rec.uheader.t_desc.ui2_on_id = t_tsl_data->ui2_on_id;
        t_tsl_rec.uheader.t_desc.ui2_ts_id = t_tsl_data->ui2_ts_id;
        t_tsl_rec.uheader.t_desc.ui1_flags = t_tsl_data->ui1_flags;
        
		//Part of Digital by Air (antenna)
        if(t_tsl_rec.uheader.t_desc.e_bcst_type == BRDCST_TYPE_ATSC)
        {
            t_tsl_rec.udata.t_ter_dig.ui4_freq = t_tsl_data->ui4_freq;
            t_tsl_rec.udata.t_ter_dig.e_bandwidth = t_tsl_data->e_bandwidth;
            t_tsl_rec.udata.t_ter_dig.e_mod = t_tsl_data->e_mod;
            t_tsl_rec.udata.t_ter_dig.e_hierarchy_priority = HIR_PRIORITY_NONE;		//kyo_20090826 add
        }
        else{
    		//Part of Analog by Air (antenna)
            t_tsl_rec.udata.t_ter_ana.ui4_freq      = t_tsl_data->ui4_freq;
            t_tsl_rec.udata.t_ter_ana.ui4_central_freq= t_tsl_data->ui4_freq;
            t_tsl_rec.udata.t_ter_ana.e_pol         = POL_UNKNOWN;
            t_tsl_rec.udata.t_ter_ana.ui2_dir       = 0;
            t_tsl_rec.udata.t_ter_ana.ui2_gain      = 0;
            t_tsl_rec.udata.t_ter_ana.e_mod         = t_tsl_data->e_mod;
            t_tsl_rec.udata.t_ter_ana.b_fine_tune   = TRUE;

 	    }
        c_tsl_update_rec(h_g_acfg_tsl_air, &t_tsl_rec, FALSE);
    }

    /* SVL Table Processing*/
    for( ui2_i = 0; ui2_i < ui2_svl_size; ui2_i++)
    {
        if(ui1_area_id==0)/* FQ */
        {
            t_svl_data=&t_svl_table_XM_antenna[ui2_i];
        }
        else if(ui1_area_id==1)/* SZ */
        {
            t_svl_data=&t_svl_table_SuZhou_antenna[ui2_i];
        }

        /* Update the SVL */
        c_svl_rec_init(&t_svl_rec);
        t_svl_rec.ui2_svl_rec_id = ui2_svl_rec_id_temp++;
        
		//Header
        t_svl_rec.uheader.t_rec_hdr.ui4_channel_id= t_svl_data->ui4_channel_num;
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask   = t_svl_data->ui4_nw_mask;
        t_svl_rec.uheader.t_rec_hdr.ui2_prog_id = t_svl_data->ui2_prog_id;
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id    = 1;   //air -> 1
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id= t_svl_data->ui2_tsl_rec_id;
        t_svl_rec.uheader.t_rec_hdr.e_brdcst_type = t_svl_data->e_brdcst_type;
        t_svl_rec.uheader.t_rec_hdr.e_serv_type   = t_svl_data->e_serv_type;
        c_strcpy(t_svl_rec.uheader.t_rec_hdr.ac_name,t_svl_data->ac_name);

		//for Analog Only
        if(t_svl_data->e_brdcst_type == BRDCST_TYPE_ANALOG)
     	{
            t_svl_rec.u_data.t_analog.ui4_s_comp_mask = 0;
            t_svl_rec.u_data.t_analog.ui4_tv_sys      = t_svl_data->ui4_tv_sys;
            t_svl_rec.u_data.t_analog.ui4_audio_sys   = t_svl_data->ui4_audio_sys;
            t_svl_rec.u_data.t_analog.e_vid_color_sys = t_svl_data->e_vid_color_sys;
            t_svl_rec.u_data.t_analog.b_valid_src_id  = FALSE;
        }
		c_svl_update_rec(h_g_acfg_svl_air, &t_svl_rec, FALSE);

        if(ui2_i==0)
        {
            ui4_antenna_first_channel_id = t_svl_data->ui4_channel_num;
        }
    }

    c_svl_unlock(h_g_acfg_svl_air);
    c_tsl_unlock(h_g_acfg_tsl_air);


    if ((h_g_acfg_svl_air != NULL_HANDLE) && (h_g_acfg_tsl_air != NULL_HANDLE))
    {
        c_svl_fs_store(FM_ROOT_HANDLE, ATSC_TRSTRL_SVL_FILE, ATSC_TRSTRL_SVL_ID);
        c_tsl_fs_store(FM_ROOT_HANDLE, ATSC_TRSTRL_TSL_FILE, ATSC_TRSTRL_TSL_ID);
    }

    //-----ATSC cable  start -------------------//
    if(c_strcmp(ui1_area,"FQ")==0)
    {
        ui1_area_id=0;
        ui2_tsl_size=sizeof(t_tsl_table_XM_cable)/sizeof(t_tsl_table_XM_cable[0]);
        ui2_svl_size=sizeof(t_svl_table_XM_cable)/sizeof(t_svl_table_XM_cable[0]);
    }
    else if(c_strcmp(ui1_area,"SZ")==0)
    {
        ui1_area_id=1;
        ui2_tsl_size=sizeof(t_tsl_table_SuZhou_cable)/sizeof(t_tsl_table_SuZhou_cable[0]);
        ui2_svl_size=sizeof(t_svl_table_SuZhou_cable)/sizeof(t_svl_table_SuZhou_cable[0]);
    }
    else if(c_strcmp(ui1_area,"POL")==0)
    {
        ui1_area_id=2;
        ui2_tsl_size=sizeof(t_tsl_table_Poland)/sizeof(t_tsl_table_Poland[0]);
        ui2_svl_size=sizeof(t_svl_table_Poland)/sizeof(t_svl_table_Poland[0]);
    }
    else
    {
        return APP_CFGR_INV_ARG;
    }

    c_svl_lock(h_g_acfg_svl_cable);
    c_tsl_lock(h_g_acfg_tsl_cable);

    /* TSL Table Processing*/
    DBG_LOG_PRINT(("!!!ui2_tsl_size :%d\n", ui2_tsl_size));
    for( ui2_i = 0; ui2_i < ui2_tsl_size; ui2_i++)
    {
        if(ui1_area_id==0)/* FQ */
        {
            t_tsl_data=&t_tsl_table_XM_cable[ui2_i];
        }
        else if(ui1_area_id==1)/* SZ */
        {
            t_tsl_data=&t_tsl_table_SuZhou_cable[ui2_i];
        }
        else if(ui1_area_id==2)/* POL */
        {
            t_tsl_data=&t_tsl_table_Poland[ui2_i];
        }

        /* Update the TSL */
        c_tsl_rec_init(&t_tsl_rec);
        t_tsl_rec.ui2_tsl_rec_id                = t_tsl_data->ui2_tsl_rec_id;
		//Header
        t_tsl_rec.uheader.t_desc.e_bcst_type    = t_tsl_data->e_bcst_type;
        t_tsl_rec.uheader.t_desc.e_bcst_medium  = t_tsl_data->e_bcst_medium;
        t_tsl_rec.uheader.t_desc.ui2_nw_id = t_tsl_data->ui2_nw_id;
        t_tsl_rec.uheader.t_desc.ui2_on_id = t_tsl_data->ui2_on_id;
        t_tsl_rec.uheader.t_desc.ui2_ts_id = t_tsl_data->ui2_ts_id;
        t_tsl_rec.uheader.t_desc.ui1_flags = t_tsl_data->ui1_flags;

        if(t_tsl_rec.uheader.t_desc.e_bcst_type == BRDCST_TYPE_ATSC)
        {
            //Part of Digital by cable
            t_tsl_rec.udata.t_cab_dig.ui4_freq = t_tsl_data->ui4_freq;
            t_tsl_rec.udata.t_cab_dig.e_mod = t_tsl_data->e_mod;
        }
        else{
            //Part of Analog by cable
            t_tsl_rec.udata.t_cab_ana.ui4_freq      = t_tsl_data->ui4_freq;
            t_tsl_rec.udata.t_cab_ana.ui4_central_freq = t_tsl_data->ui4_freq;
            t_tsl_rec.udata.t_cab_ana.e_mod         = t_tsl_data->e_mod;
            t_tsl_rec.udata.t_cab_ana.b_fine_tune   = TRUE;
        }
        c_tsl_update_rec(h_g_acfg_tsl_cable, &t_tsl_rec, FALSE);
    }

    ui2_svl_rec_id_temp = 1;
    /* SVL Table Processing*/
    for( ui2_i = 0; ui2_i < ui2_svl_size; ui2_i++)
    {
        if(ui1_area_id==0)/* FQ */
        {
            t_svl_data=&t_svl_table_XM_cable[ui2_i];
        }
        else if(ui1_area_id==1)/* SZ */
        {
            t_svl_data=&t_svl_table_SuZhou_cable[ui2_i];
        }
        else if(ui1_area_id==2)/* POL */
        {   
            t_svl_data=&t_svl_table_Poland[ui2_i];
        }

        /* Update the SVL */
        c_svl_rec_init(&t_svl_rec);
        t_svl_rec.ui2_svl_rec_id = ui2_svl_rec_id_temp++;
        
		//Header
        t_svl_rec.uheader.t_rec_hdr.ui4_channel_id= t_svl_data->ui4_channel_num;
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask   = t_svl_data->ui4_nw_mask;
        t_svl_rec.uheader.t_rec_hdr.ui2_prog_id = t_svl_data->ui2_prog_id;
        t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id    =2;	//cable -> 2
	    t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id= t_svl_data->ui2_tsl_rec_id;
        t_svl_rec.uheader.t_rec_hdr.e_brdcst_type = t_svl_data->e_brdcst_type;
        t_svl_rec.uheader.t_rec_hdr.e_serv_type   = t_svl_data->e_serv_type;
        c_strcpy(t_svl_rec.uheader.t_rec_hdr.ac_name,t_svl_data->ac_name);
        
		//for Analog Only
        if(t_svl_data->e_brdcst_type != BRDCST_TYPE_ATSC){
            t_svl_rec.u_data.t_analog.ui4_s_comp_mask = 0;
            t_svl_rec.u_data.t_analog.ui4_tv_sys      = t_svl_data->ui4_tv_sys;
            t_svl_rec.u_data.t_analog.ui4_audio_sys   = t_svl_data->ui4_audio_sys;
            t_svl_rec.u_data.t_analog.e_vid_color_sys = t_svl_data->e_vid_color_sys;
            t_svl_rec.u_data.t_analog.b_valid_src_id  = FALSE;
        }
        c_svl_update_rec(h_g_acfg_svl_cable, &t_svl_rec, FALSE);

        if(ui2_i==0)
        {
            ui4_cable_first_channel_id = t_svl_data->ui4_channel_num;
        }
    }

    c_svl_unlock(h_g_acfg_svl_cable);
    c_tsl_unlock(h_g_acfg_tsl_cable);

    if ((h_g_acfg_svl_cable != NULL_HANDLE) && (h_g_acfg_tsl_cable != NULL_HANDLE))
    {
        c_svl_fs_store(FM_ROOT_HANDLE, ATSC_CABLE_SVL_FILE, ATSC_CABLE_SVL_ID);
        c_tsl_fs_store(FM_ROOT_HANDLE, ATSC_CABLE_TSL_FILE, ATSC_CABLE_TSL_ID);
    }

//-------------cable end-------------------------//

    HANDLE_T h_svl;
    h_svl = acfg_get_crnt_svl();
    if(h_svl == h_g_acfg_svl_air)
    {
        ui4_first_channel_id = ui4_antenna_first_channel_id;
    }
    else
    {
        ui4_first_channel_id = ui4_cable_first_channel_id;
    }

    a_tv_change_channel(h_g_acfg_svctx_main,
                        SVCTX_STRM_MODE_AS_LAST,
                        ui4_first_channel_id, //SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_first_channel_num, 0),
                        NULL);

    return APP_CFGR_OK;
#endif /* APP_DVBT_SUPPORT */
}



INT32 acfg_INX_get_channel_freqency(VOID)
{
    SVL_REC_T   t_svl_rec;
    TSL_REC_T   t_tsl_rec;
	UINT32 ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
	UINT32 ui4_ver_id;
    INT32 channel_ret;

    //ke_vizio_20110330 for clean warning.
    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

	/*Printf("[SAC.BM]ui4_channel_id=%ld\n",ui4_channel_id);	*/

    c_svl_lock(h_g_acfg_svl_cable);
    c_tsl_lock(h_g_acfg_tsl_cable);
    
    c_svl_lock(h_g_acfg_svl_air);
    c_tsl_lock(h_g_acfg_tsl_air);

    /* Show the SVL Info*/
    ui4_ver_id = SVL_NULL_VER_ID;
    channel_ret = c_svl_get_rec_by_channel(h_g_acfg_svl_cable,
                                ui4_channel_id,
                                SB_VNET_ALL,
                                0,
                                &t_svl_rec,
                                &ui4_ver_id);
    if( channel_ret != SVLR_OK ){//truedano add : fix mtk warn
        DBG_LOG_PRINT(("c_svl_get_rec_by_channel() fail : %d\n",channel_ret));
        return 0;
    }

    DBG_LOG_PRINT(("SVL\n"));
    DBG_LOG_PRINT(("nw mask=%ld\n",t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask));
    DBG_LOG_PRINT(("prog id=%ld\n",t_svl_rec.uheader.t_rec_hdr.ui2_prog_id));
    DBG_LOG_PRINT(("tsl id=%ld\n",t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id));
    switch(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
     {
         case BRDCST_TYPE_ANALOG:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ANALOG\n"));
             break;
         case BRDCST_TYPE_DVB:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_DVB=\n"));
             break;
         case BRDCST_TYPE_ATSC:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ATSC\n"));
             break;
         case BRDCST_TYPE_SCTE:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_SCTE=\n"));
             break;
         default:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_UNKNOWN="));
             break;
     }
    switch(t_svl_rec.uheader.t_rec_hdr.e_serv_type)
     {
         case SVL_SERVICE_TYPE_TV:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_TV\n"));
             break;
         case SVL_SERVICE_TYPE_RADIO:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_RADIO=\n"));
             break;
         case SVL_SERVICE_TYPE_APP:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_APP=\n"));
             break;
         default:
             DBG_LOG_PRINT(("SVL_SERVICE_TYPE_UNKNOWN=\n"));
             break;
     }
    DBG_LOG_PRINT(("%s=",t_svl_rec.uheader.t_rec_hdr.ac_name));
    if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_DVB)
     {
 	    DBG_LOG_PRINT(("TV_SYS_MASK_NONE="));
 	    DBG_LOG_PRINT(("AUDIO_SYS_MASK_NONE="));
 	    DBG_LOG_PRINT(("COLOR_SYS_UNKNOWN"));
     }
     else
     {
 	    DBG_LOG_PRINT(("tv sys =%d\n",t_svl_rec.u_data.t_analog.ui4_tv_sys));
 	    DBG_LOG_PRINT(("audio sys=%d\n",t_svl_rec.u_data.t_analog.ui4_audio_sys));
 	    DBG_LOG_PRINT(("color sys =%d\n",t_svl_rec.u_data.t_analog.e_vid_color_sys));
 	    DBG_LOG_PRINT(("valid	src id =%d\n"  ,t_svl_rec.u_data.t_analog.b_valid_src_id));
        DBG_LOG_PRINT(("src id =%d\n"  ,t_svl_rec.u_data.t_analog.ui2_src_id));
     }

 
     /* Show the TSL Info*/
 	ui4_ver_id = TSL_NULL_VER_ID;
    c_tsl_get_rec(h_g_acfg_tsl_cable,
                  t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                  &t_tsl_rec,
                  &ui4_ver_id);

     DBG_LOG_PRINT(("TSL\n"));
     DBG_LOG_PRINT(("tsl rec id =%ld\n",t_tsl_rec.ui2_tsl_rec_id));
     switch(t_tsl_rec.uheader.t_desc.e_bcst_type)
     {
         case BRDCST_TYPE_ANALOG:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ANALOG\n"));
             break;
         case BRDCST_TYPE_DVB:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_DVB="));
             break;
         case BRDCST_TYPE_ATSC:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_ATSC\n"));
             break;
         case BRDCST_TYPE_SCTE:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_SCTE=\n"));
             break;
         default:
 	        DBG_LOG_PRINT(("BRDCST_TYPE_UNKNOWN="));
             break;
     }
     switch(t_tsl_rec.uheader.t_desc.e_bcst_medium)
     {
         case BRDCST_MEDIUM_DIG_TERRESTRIAL:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_DIG_TERRESTRIAL\n"));
             break;
         case BRDCST_MEDIUM_DIG_CABLE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_DIG_CABLE\n"));
             break;
         case BRDCST_MEDIUM_DIG_SATELLITE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_DIG_SATELLITE=\n"));
             break;
         case BRDCST_MEDIUM_ANA_TERRESTRIAL:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_ANA_TERRESTRIAL\n"));
             break;
         case BRDCST_MEDIUM_ANA_CABLE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_ANA_CABLE\n"));
             break;
         case BRDCST_MEDIUM_ANA_SATELLITE:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_ANA_SATELLITE=\n"));
             break;
         case BRDCST_MEDIUM_1394:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_1394="));
             break;
         default:
 	        DBG_LOG_PRINT(("BRDCST_MEDIUM_UNKNOWN="));
             break;
     }

 	DBG_LOG_PRINT(("ter dig freq=%ld\n",t_tsl_rec.udata.t_ter_dig.ui4_freq));
 	DBG_LOG_PRINT(("cab dig freq=%ld\n",t_tsl_rec.udata.t_cab_dig.ui4_freq));

    c_svl_unlock(h_g_acfg_svl_cable);
    c_tsl_unlock(h_g_acfg_tsl_cable);

    c_svl_unlock(h_g_acfg_svl_air);
    c_tsl_unlock(h_g_acfg_tsl_air);
      
    return t_tsl_rec.udata.t_cab_dig.ui4_freq;
}

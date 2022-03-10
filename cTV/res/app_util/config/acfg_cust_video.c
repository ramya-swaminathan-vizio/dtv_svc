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
 * $RCSfile: acfg_custom.c,v $
 * $Revision: #4 $
 * $Date: 2015/08/04 $
 * $Author: jg_lizhuwang $
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
#include "c_common.h"
#include "c_svctx.h"
#include "c_scc.h"
#include "c_rm.h"
#include "u_drv_cust.h"
#include "c_sys_config.h"

#include "app_util/a_icl.h"
#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"
#include "app_util/config/acfg_mute_mngr.h"
#include "app_util/a_pre_unmute.h"
#include "app_util/a_common_setting.h"


#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "am/a_am.h"
#include "amb/a_amb.h"

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#endif

#ifdef APP_3D_RETAIL_DEMO_MODE
#include "nav/retail_mode/a_nav_retail_mode.h"
#endif

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "app_util/a_screen_mode.h"
#include "menu2/a_menu.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "wfd/a_wfd.h"
#include "wfd/wfd.h"
#include "app_util/tvstate/smart_dim.h"
#include "a_gluelayer.h"
#include "app_util/config/_acfg.h"
#include "mtvdecex.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#define ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE  1


typedef struct __TIMING_HV_POS_MAP_T
{
    UINT8           ui1_idx;
    DEVICE_TYPE_T   e_video_type;
    UINT32          ui4_height;
    UINT8           ui1_internal_id; // input source number
} _TIMING_HV_POS_MAP_T;

#define ABS(x)              (((x) > 0) ? (x) : (-(x)))

#define scr_NORMAL      0
#define scr_WIDE        1
#define scr_ZOOM        2
#define scr_PANORAMIC   3
#define scr_STRETCH     4
#define scr_END         5
#define PIC_POSITIOIN_DRV_MAX_VALUE     (1000)

BOOL    b_3d_mode_playing = FALSE;

#define VRR_INIT_VAL   255
#if( ACFG_CUST_VRR_SET_DRIVER_BY_PORT )
    INT16   g_ai16_vrr_last[4] = { VRR_INIT_VAL, VRR_INIT_VAL, VRR_INIT_VAL, VRR_INIT_VAL };
#else
    INT16   i2_g_vrr_set = VRR_INIT_VAL;
#endif

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static UINT32 ui4_pq_id = 0;

static _TIMING_HV_POS_MAP_T at_timing_hv_map[] =
{
/* eeprom idx, default v_size, input source, video height, progressive */
    { 0 , DEV_AVC_COMP_VIDEO, 0     , 0},
    { 0 , DEV_AVC_S_VIDEO   , 0     , 0},

    { 1 , DEV_TUNER_TER_ANA , 0     , 0},

    { 2 , DEV_TUNER_TER_DIG , 480   , 0},
    { 3 , DEV_TUNER_TER_DIG , 720   , 0},
    { 4 , DEV_TUNER_TER_DIG , 1080  , 0},

    { 5 , DEV_AVC_Y_PB_PR   , 480   , 0},
    { 6 , DEV_AVC_Y_PB_PR   , 720   , 0},
    { 7 , DEV_AVC_Y_PB_PR   , 1080  , 0},

    { 8 , DEV_AVC_Y_PB_PR      , 480   ,  1},
    { 9 , DEV_AVC_Y_PB_PR      , 720   ,  1},
    { 10, DEV_AVC_Y_PB_PR      , 1080  ,  1},

     /*HDMI-1*/
    { 11, DEV_AVC_HDMI      , 480   , 0},
    { 12, DEV_AVC_HDMI      , 720   , 0},
    { 13, DEV_AVC_HDMI      , 1080  , 0},

    /*HDMI-2*/
    { 14, DEV_AVC_HDMI      , 480   , 1},
    { 15, DEV_AVC_HDMI      , 720   , 1},
    { 16, DEV_AVC_HDMI      , 1080  , 1},

    /*HDMI-3*/
    { 17, DEV_AVC_HDMI      , 480   , 2},
    { 18, DEV_AVC_HDMI      , 720   , 2},
    { 19, DEV_AVC_HDMI      , 1080  , 2},

    /*HDMI-4*/
    { 20, DEV_AVC_HDMI      , 480   , 3},
    { 21, DEV_AVC_HDMI      , 720   , 3},
    { 22, DEV_AVC_HDMI      , 1080  , 3},

    { 23, DEV_UNKNOWN       , 0     , 0}
};

#ifndef APP_CFG_CUSTOM_PQ_DEF_TBL
/* Default PQ table. */
APP_CFG_CUSTOM_PQ_TBL_T at_pq_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM] =
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                 Acfg index              Default value */
#ifdef NEVER
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_DISP_BACK_LIGHT,    60},
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_SHP,             6},
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_CLR_TEMP,            3}, // 3 : Normal
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_FT,              1}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_VID_LUMA,            0}, // 0 : Off
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_CUSTOM_DCR_IDX,      1},  //Support local dimming panel need to set  o.
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_CUSTOM_DIMMING,      0},  // NA NA NA  1 : On
    {ACFG_CUST_PIC_MODE_STANDARD,   IDX_CLEAR_ACTION,        0},
#endif /* NEVER */

    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_DISP_BACK_LIGHT,    38},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SHP,             6},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLR_TEMP,            3}, // 3 : Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_FT,              0}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_LUMA,            0}, // 0 : Off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DCR_IDX,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DIMMING,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_DISP_BACK_LIGHT,    55},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_MPEG_NR,         1},  // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_FT,              2}, // 0 : Off   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_LUMA,            4}, // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_VIVID,      IDX_DISP_BACK_LIGHT,    94},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_BRI,            45},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_CNT,            62},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SAT,            60},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_FT,              2}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_LUMA,            3}, // 2 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLEAR_ACTION,        0},  // 1 : On

    {ACFG_CUST_PIC_MODE_GAME,   IDX_DISP_BACK_LIGHT,    45},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SHP,             5},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_FT,              3}, // 3 : Gm/Flesh   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_LUMA,            2}, // 2 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLEAR_ACTION,        1},  // 1 : On


#ifdef NEVER
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_DISP_BACK_LIGHT,    45},
    {ACFG_CUST_PIC_MODE_COMPUTER ,      IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_FT,              4}, // 4 : Gm/Blue   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_VID_LUMA,            1}, // 1 : Low
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_COMPUTER,       IDX_CLEAR_ACTION,        0},  // 1 : On

    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_DISP_BACK_LIGHT,    45},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_SHP,             5},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_FT,              2}, // 2 : Rich Color   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_VID_LUMA,            2}, // 2 : Medium
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_BASKETBALL, IDX_CLEAR_ACTION,        0},  // 1 : On


    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_DISP_BACK_LIGHT,    45},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_SHP,             5},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_FT,              3}, // 3 : Gm/Flesh   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_VID_LUMA,            1}, // 1 : Low
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_BASEBALL,   IDX_CLEAR_ACTION,        0},  // 1 : On

    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_DISP_BACK_LIGHT,    50},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_SHP,             6},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_3D_NR,           1}, // 1 : Low    /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_FT,              1}, // 1 : Normal   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_VID_LUMA,            0}, // 2 : Medium
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_CUSTOM_DIMMING,      0},
    {ACFG_CUST_PIC_MODE_CUSTOM,     IDX_CLEAR_ACTION,        0},  // 1 : On
#endif /* NEVER */
}
};
/* Default PQ table. */
APP_CFG_CUSTOM_PQ_TBL_T at_pq_hdr_hlg_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM] =
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                 Acfg index              Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SHP,             6},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLR_TEMP,            3}, // 3 : Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_FT,              0}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_LUMA,            0}, // 0 : Off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DCR_IDX,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DIMMING,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_MPEG_NR,         1},  // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_FT,              2}, // 0 : Off   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_LUMA,            4}, // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_VIVID,      IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_BRI,            45},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_CNT,            62},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SAT,            60},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_FT,              2}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_LUMA,            3}, // 2 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLEAR_ACTION,        0},  // 1 : On

    {ACFG_CUST_PIC_MODE_GAME,   IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SHP,             5},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_FT,              3}, // 3 : Gm/Flesh   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_LUMA,            2}, // 2 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLEAR_ACTION,        1},  // 1 : On
}
};
/* Default PQ table. */
APP_CFG_CUSTOM_PQ_TBL_T at_pq_dobly_version_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM] =
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                 Acfg index              Default value */

    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SHP,             6},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLR_TEMP,            3}, // 3 : Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_FT,              0}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_LUMA,            0}, // 0 : Off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DCR_IDX,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DIMMING,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_MPEG_NR,         1},  // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_FT,              2}, // 0 : Off   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_LUMA,            4}, // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_VIVID,      IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_BRI,            45},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_CNT,            62},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SAT,            60},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_FT,              2}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_LUMA,            3}, // 2 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLEAR_ACTION,        0},  // 1 : On

    {ACFG_CUST_PIC_MODE_GAME,   IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SHP,             5},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_FT,              3}, // 3 : Gm/Flesh   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_LUMA,            2}, // 2 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLEAR_ACTION,        1},  // 1 : On
}
};

/* Default PQ table. */
APP_CFG_CUSTOM_PQ_TBL_T at_pq_hlg_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM] =
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                 Acfg index              Default value */

    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_SHP,             6},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLR_TEMP,            3}, // 3 : Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_FT,              0}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_VID_LUMA,            0}, // 0 : Off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DCR_IDX,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CUSTOM_DIMMING,      0},
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,      IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_MPEG_NR,         1},  // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_FT,              2}, // 0 : Off   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_VID_LUMA,            4}, // 0 : Off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_DARK_ROOM,       IDX_CLEAR_ACTION,        0},

    {ACFG_CUST_PIC_MODE_VIVID,      IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_BRI,            45},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_CNT,            62},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SAT,            60},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_SHP,             8},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_FT,              2}, // 1 : On   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_VID_LUMA,            3}, // 2 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_VIVID,      IDX_CLEAR_ACTION,        0},  // 1 : On

    {ACFG_CUST_PIC_MODE_GAME,   IDX_DISP_BACK_LIGHT,    100},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_BRI,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_CNT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SAT,            50},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_HUE,             0},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_SHP,             5},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLR_TEMP,            1}, // 1 : Cool
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_3D_NR,           1}, // 1 : Low   /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_MPEG_NR,         1},  // 1 : Low
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_FT,              3}, // 3 : Gm/Flesh   /* Color Enhancement */
    {ACFG_CUST_PIC_MODE_GAME,   IDX_VID_LUMA,            2}, // 2 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DCR_IDX,      1},
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CUSTOM_DIMMING,      0},  // 1 : On
    {ACFG_CUST_PIC_MODE_GAME,   IDX_CLEAR_ACTION,        1},  // 1 : On
}
};


#endif

#ifndef APP_CFG_CUSTOM_PRO_PQ_DEF_TBL
APP_CFG_CUSTOM_PQ_TBL_T at_pro_pq_def_tbl [][ACFG_CUST_VIDEO_PRO_PQ_DFT_TBL_MAX_NUM] =  //for MG128 & MG138 common pro pq default table
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                  A cfg index              Default value */
    //Standard
#ifdef NEVER
    {ACFG_CUST_PIC_MODE_STANDARD,     IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on
#endif /* NEVER */

    //Calibrated
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated Dark
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Vivid
    {ACFG_CUST_PIC_MODE_VIVID,       IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    ///Game
    {ACFG_CUST_PIC_MODE_GAME,         IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on
}
};
#endif

UINT8 ui1_clr_temp_def[ACFG_CLR_TEMP_ELEM_NUM] = {0};
INT16 ai2_clr_temp_offset_r[ACFG_CLR_OFFSET_ELEM_NUM][APP_CFG_CLR_TEMP_MODE_MAX] = {0};
INT16 ai2_clr_temp_offset_g[ACFG_CLR_OFFSET_ELEM_NUM][APP_CFG_CLR_TEMP_MODE_MAX] = {0};
INT16 ai2_clr_temp_offset_b[ACFG_CLR_OFFSET_ELEM_NUM][APP_CFG_CLR_TEMP_MODE_MAX] = {0};
INT16 ai2_clr_temp_gain_r[ACFG_CLR_GAIN_ELEM_NUM][APP_CFG_CLR_TEMP_MODE_MAX] = {0};
INT16 ai2_clr_temp_gain_g[ACFG_CLR_GAIN_ELEM_NUM][APP_CFG_CLR_TEMP_MODE_MAX] = {0};
INT16 ai2_clr_temp_gain_b[ACFG_CLR_GAIN_ELEM_NUM][APP_CFG_CLR_TEMP_MODE_MAX] = {0};

#ifndef APP_CLR_GAIN_AND_OFFSET_NOT_DIS_2D_3D
static INT16 aai2_3d_clr_gain[][ACFG_3D_CLR_GAIN_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* R,  G,  B*/
    /* Group 0: HDMI1 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */
}
};

static INT16 aai2_3d_clr_offset[][ACFG_3D_CLR_OFFSET_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* R,  G,  B*/
    /* Group 0: HDMI1 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */
}
};

static INT16 aai2_3d_clr_gain_value_0_def[][ACFG_3D_CLR_GAIN_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* R,  G,  B*/
    /* Group 0: HDMI1 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */
}
};

static INT16 aai2_3d_clr_offset_value_0_def[][ACFG_3D_CLR_OFFSET_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* R,  G,  B*/
    /* Group 0: HDMI1 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */
}
};

#endif

static INT16 aai2_clr_gain[][ACFG_CLR_GAIN_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* R,  G,  B*/
    /* Group 0: TV */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 1: CVBS */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 2: YPBPR */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 3: HDMI1 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 4: HDMI2 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 5: HDMI3 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 6: HDMI4 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 7: VGA  */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 8: MMP  */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 9: VTRL  */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */
}
};

static INT16 aai2_clr_offset[][ACFG_CLR_OFFSET_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* Group 0: TV */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 1: CVBS */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 2: YPBPR */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 3: HDMI1 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 4: HDMI2 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 5: HDMI3 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 6: HDMI4 */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 7: VGA  */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 8: MMP  */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */

    /* Group 9: VTRL  */
    {128, 128, 128},  /* Custom */
    {128, 128, 128},  /* Cool */
    {128, 128, 128},  /* PC */
    {128, 128, 128},  /* Noraml */
}
};

static INT16 aai2_clr_gain_value_0_def[][ACFG_CLR_GAIN_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* R,  G,  B*/
    /* Group 0: TV */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 1: CVBS */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 2: YPBPR */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 3: HDMI1 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 4: HDMI2 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 5: HDMI3 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 6: HDMI4 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 7: VGA  */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 8: MMP  */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 9: VTRL  */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */
}
};

static INT16 aai2_clr_offset_value_0_def[][ACFG_CLR_OFFSET_ELEM_NUM][3] =
{
{   /* ui4_pq_id = 0 */
    /* Group 0: TV */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 1: CVBS */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 2: YPBPR */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 3: HDMI1 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 4: HDMI2 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 5: HDMI3 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 6: HDMI4 */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 7: VGA  */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 8: MMP  */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */

    /* Group 9: VTRL  */
    {0, 0, 0},  /* Custom */
    {0, 0, 0},  /* Cool */
    {0, 0, 0},  /* PC */
    {0, 0, 0},  /* Noraml */
}
};

static UINT8     aui1_dcr_def[ACFG_PIC_QLT_ELEM_NUM]={0};
static UINT8     aui1_dimming_onoff[ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8     aui1_light_sensor_def[ACFG_PIC_QLT_ELEM_NUM] = {2,0};
static UINT8     aui1_h_size_def [ACFG_CUSTOM_H_SIZE_ELEM_NUM] = {0};
static UINT8     aui1_v_size_def [ACFG_CUSTOM_V_SIZE_ELEM_NUM] = {0};
static UINT8     ui1_vid_mjc_effect_def  [ACFG_PIC_QLT_ELEM_NUM];
static UINT8     ui1_vid_mjc_mode_def    [ACFG_PIC_QLT_ELEM_NUM];
static CHAR      ps_cust_pic_mode_name_def[ACFG_PIC_MODE_ELEM_NUM][APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = {{0}};
static UINT8     aui1_cust_pic_exist_status_def[APP_CFG_CUST_PIC_EXIST_STUTAS_ELEM_NUM] = {0};
static UINT8     ui1_cust_pic_lock_status_def = 0;
static CHAR      s_pic_mode_unlock_pwd[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = "0000";
static CHAR      s_pre_pic_mode_chg[ACFG_PRE_SET_PIC_MODE_CHG_ELEM_NUM] = {0};

/* as default the cust define pq setting will use this default value*/
static UINT8     aui1_vid_cust_pq_setting_def[ACFG_PIC_QLT_ELEM_NUM]={0};
static UINT8     aui1_vid_reduce_blur_def[ACFG_PIC_QLT_ELEM_NUM]={0};
static UINT8     aui1_vid_cust_gamma[ACFG_VID_CUST_GAMMA_ELEM_NUM]={2};
static UINT8     ui1_vid_cust_full_color_444=0;


static UINT8     aui1_vid_cust_rgb_def[APP_CFG_HRGB_ELEM_NUM]={0};
static UINT8     aui1_vid_cust_hrgb_def[APP_CFG_HRGB_ELEM_NUM]={0};
static UINT8     aui1_vid_2_point_wb_def[APP_CFG_2_POINT_WB_ELEM_NUM]={0};


static UINT8     aui1_vid_11_point_gain_def[APP_CFG_11_POINT_GAIN_ELEM_NUM]={0};
static UINT8     aui1_vid_11_point_gain_rgb_def[APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM]={0};


TIMING_HV_POS_MAP_T at_timing_scr_map[] =
{
   /*idx, input source,        video height, input source number refer to at_reg_grps in Sys_drv_custom.c */
//TV
    { 1 , DEV_TUNER_TER_ANA    , 0     ,  0},
    { 2 , DEV_TUNER_TER_DIG    , 480   ,  0},
    { 3 , DEV_TUNER_TER_DIG    , 720   ,  0},
    { 4 , DEV_TUNER_TER_DIG    , 1080  ,  0},
//AV1
    { 5 , DEV_AVC_COMP_VIDEO   , 0     ,  0},
    { 6 , DEV_AVC_S_VIDEO      , 0     ,  0},
    { 6 , DEV_AVC_COMBI        , 0     ,  0},
//VGA 4:3
    { 7 , DEV_AVC_VGA          , 0     ,  0},
//YPbPr1
    { 8 , DEV_AVC_Y_PB_PR      , 480   ,  0},
    { 9 , DEV_AVC_Y_PB_PR      , 720   ,  0},
    {10 , DEV_AVC_Y_PB_PR      , 1080  ,  0},
//YPbPr2
    {11 , DEV_AVC_Y_PB_PR      , 480   ,  1},
    {12 , DEV_AVC_Y_PB_PR      , 720   ,  1},
    {13 , DEV_AVC_Y_PB_PR      , 1080  ,  1},
//VGA 16:9
    {14, DEV_AVC_VGA           , 0     ,  0},
//HDMI1
    {15, DEV_AVC_HDMI          , 480   ,  0},
    {16, DEV_AVC_HDMI          , 720   ,  0},
    {17, DEV_AVC_HDMI          , 1080  ,  0},
//HDMI2
    {18, DEV_AVC_HDMI          , 480   ,  1},
    {19, DEV_AVC_HDMI          , 720   ,  1},
    {20, DEV_AVC_HDMI          , 1080  ,  1},
//HDMI3
    {21, DEV_AVC_HDMI          , 480   ,  2},
    {22, DEV_AVC_HDMI          , 720   ,  2},
    {23, DEV_AVC_HDMI          , 1080  ,  2},
//HDMI4
    {24, DEV_AVC_HDMI          , 480   ,  3},
    {25, DEV_AVC_HDMI          , 720   ,  3},
    {26, DEV_AVC_HDMI          , 1080  ,  3}
};

static UINT8    aui1_cust_scr_mod_def   [ACFG_SCR_MODE_ELEM_NUM] =
{
    /* Unknow */
    SCC_VID_SCREEN_MODE_NORMAL,

    /* TV */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* AV1 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* VGA 4:3*/
    SCC_VID_SCREEN_MODE_NORMAL,

    /* YPbPr1 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* YPbPr2 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* VGA 16:9*/
    SCC_VID_SCREEN_MODE_NORMAL,

    /* HDMI1 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* HDMI2 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* HDMI3 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /* HDMI4 */
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL,

    /*MMP & Net Video*/
    SCC_VID_SCREEN_MODE_NORMAL, SCC_VID_SCREEN_MODE_NORMAL
};

extern INT32 menu_page_color_tuner_is_scrn_mode(VOID);

static INT16 _acfg_cust_video_get_def_val (
    UINT16  ui2_idx,
    UINT8   ui1_mode);

static INT32 _acfg_cust_video_def_value_append_patch(VOID);
static INT32 _acfg_cust_color_space_value_mapping(UINT8 ui1_color_space);
BOOL acfg_is_backlight_control_enable();

#if 1//(ENABLE_COLOR_444_TO_422_NEW_SPEC)
extern BOOL acfg_cust_FullColor444_IfCanTurnOn(void);
#endif

/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/
VOID acfg_cust_overwrite_hlg_hdr_dover_pq_default(VOID)
{
   // UINT16  ui2_tbl_size = sizeof (at_pq_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    UINT32 ui4_model_id = 0;
    a_cfg_custom_get_model_idx(&ui4_model_id);

    if(ui4_model_id == 1) //add by Amtran Jason
        return;
    else
    {
        c_memcpy(at_pq_hdr_hlg_def_tbl, at_pq_def_tbl, sizeof(at_pq_def_tbl));
        c_memcpy(at_pq_dobly_version_def_tbl, at_pq_def_tbl, sizeof(at_pq_def_tbl));
    }
}

static INT32 _acfg_input_src_pq_dover_default(APP_CFG_CUSTOM_PQ_TBL_T  default_table[][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM],UINT8 ui1_idx)
{
    if(ui1_idx > 2)
        return APP_CFGR_INV_ARG;
    else
    {
        UINT8   ui1_pic_mode;
        UINT8   ui1_inp_src;
        UINT8   ui1_def_val;
        UINT16  ui1_i;
        UINT16  ui2_id;
        UINT16  ui2_hdr_tbl_size = sizeof (default_table[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);

        /* PQ default value for all source */
        for (ui1_i = 0;
             ui1_i < ui2_hdr_tbl_size;
             ui1_i ++)
        {
            ui1_pic_mode = (UINT8) default_table [0][ui1_i].e_pic_mode;
            ui2_id       = (UINT16)default_table [0][ui1_i].ui2_idx;
            ui1_def_val  = (UINT8) default_table [0][ui1_i].i2_def;
#if 0
            DBG_LOG_PRINT(("[ACFG][%s %d] hdr [pic,id,def] => [%d,%d,%d,%d]\n",
                __FUNCTION__,__LINE__,
                ui1_pic_mode,
                ui2_id,
                ui1_def_val));
#endif

            if(ui2_id == 0)
            {
                DBG_LOG_PRINT(("[ACFG]finish full table ! %s:%d,loop %d times \n", __FILE__, __LINE__,ui1_i));
                break;
            }

            /* Apply PQ settings for each input source */
            for (ui1_inp_src = 0;
                 ui1_inp_src < ACFG_INPUT_SRC_NUM;
                 ui1_inp_src ++)
            {
                if((ui1_inp_src * ACFG_PIC_MODE_NUM + ui1_pic_mode) > at_acfg_descr[ui2_id].z_def_size)
                {
                    DBG_LOG_PRINT(("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                    break;
                }

                /* Check array index. */
                if (ui2_id >= IDX_MAX)
                {
                    DBG_ERROR (("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                    break;
                }

                if (acfg_cust_video_is_special_item(ui2_id))
                {
                    if((ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HDR* ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode) >= at_acfg_descr[ui2_id].z_def_size)
                    {
                        break;
                    }

                    /* data store by input sorce * picture mode * dynamic range */
                    //hlg
                    *(((UINT8*)at_acfg_descr[ui2_id].pt_def_value)+
                        ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HLG* ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode) = ui1_def_val;
                }
#if 0
                DBG_LOG_PRINT(("\r\n[ACFG][%s %d]hdr-hlg [id,inp,pic,def] = [%d,%d,%d,%d]\r\n",
                __FUNCTION__,__LINE__,
                ui2_id,
                ui1_inp_src,
                ui1_pic_mode,
                ui1_def_val));
#endif
            }

        }
    }
    return APP_CFGR_INV_ARG;
}

VOID acfg_cust_hdr_hlg_dover_table_default(VOID)
{
    UINT8   ui1_pic_mode;
    UINT8   ui1_inp_src;
    UINT8   ui1_def_val;
    UINT16  ui1_i;
    UINT16  ui2_id;
    UINT16  ui2_hdr_tbl_size = sizeof (at_pq_hdr_hlg_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    UINT8   ui1_odm_id;
    /* PQ default value for all source */

    for (ui1_i = 0;
         ui1_i < ui2_hdr_tbl_size;
         ui1_i ++)
    {
        ui1_pic_mode = (UINT8) at_pq_hdr_hlg_def_tbl [0][ui1_i].e_pic_mode;
        ui2_id       = (UINT16)at_pq_hdr_hlg_def_tbl [0][ui1_i].ui2_idx;
        ui1_def_val  = (UINT8) at_pq_hdr_hlg_def_tbl [0][ui1_i].i2_def;

        if(ui2_id == 0)
        {
            DBG_LOG_PRINT(("[ACFG]finish full table ! %s:%d,loop %d times \n", __FILE__, __LINE__,ui1_i));
            break;
        }

        /* Apply PQ settings for each input source */
        for (ui1_inp_src = 0;
             ui1_inp_src < ACFG_INPUT_SRC_NUM;
             ui1_inp_src ++)
        {
            if((ui1_inp_src * ACFG_PIC_MODE_NUM + ui1_pic_mode) > at_acfg_descr[ui2_id].z_def_size)
            {
                DBG_LOG_PRINT(("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                break;
            }

            /* Check array index. */
            if (ui2_id >= IDX_MAX)
            {
                DBG_ERROR (("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                break;
            }

            if (acfg_cust_video_is_special_item(ui2_id))
            {
                if((ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HDR* ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode) >= at_acfg_descr[ui2_id].z_def_size)
                {
                    DBG_INFO(("[ACFG]at_acfg_descr[ui2_id].z_def_size :%d, %s,%d\r\n",at_acfg_descr[ui2_id].z_def_size,__FUNCTION__,__LINE__));
                    DBG_INFO(("[ACFG] ui2_id %d overflow ui1_pic_mode %d ,ui1_def_val %d ui1_i %d ui1_inp_src %d\n", ui2_id,ui1_pic_mode,ui1_def_val,ui1_i,ui1_inp_src));
                    break;
                }

                /* data store by input sorce * picture mode * dynamic range */
                //hdr10 ,hdr10+
                *(((UINT8*)at_acfg_descr[ui2_id].pt_def_value)+
                    ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HDR* ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode) = ui1_def_val;
                //hlg
                *(((UINT8*)at_acfg_descr[ui2_id].pt_def_value)+
                    ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HLG* ACFG_PRE_SET_PIC_MODE_NUM +  ui1_pic_mode) = ui1_def_val;
            }
#if 0
            DBG_LOG_PRINT(("\r\n[ACFG][%s %d]hdr-hlg [id,inp,pic,def] = [%d,%d,%d,%d]\r\n",
            __FUNCTION__,__LINE__,
            ui2_id,
            ui1_inp_src,
            ui1_pic_mode,
            ui1_def_val));
#endif
        }
    }

    /* need reconver hlg pq setting */
    if(APP_CFGR_OK == a_cfg_custom_get_odm_idx(&ui1_odm_id) && ui1_odm_id == 6)
    {
        ACFG_LOG_ON_FAIL(_acfg_input_src_pq_dover_default(at_pq_hlg_def_tbl,1));
    }

    UINT16  ui2_dover_tbl_size = sizeof (at_pq_dobly_version_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);

    for (ui1_i = 0;
         ui1_i < ui2_dover_tbl_size;
         ui1_i ++)
    {
        ui1_pic_mode = (UINT8) at_pq_dobly_version_def_tbl [0][ui1_i].e_pic_mode;
        ui2_id       = (UINT16)at_pq_dobly_version_def_tbl [0][ui1_i].ui2_idx;
        ui1_def_val  = (UINT8) at_pq_dobly_version_def_tbl [0][ui1_i].i2_def;

        if(ui2_id == 0)
        {
            DBG_LOG_PRINT(("[ACFG]finish full table ! %s:%d,loop %d times \n", __FILE__, __LINE__,ui1_i));
            break;
        }

        /* Apply PQ settings for each input source */
        for (ui1_inp_src = 0;
             ui1_inp_src < ACFG_INPUT_SRC_NUM;
             ui1_inp_src ++)
        {
            if((ui1_inp_src * ACFG_PIC_MODE_NUM + ui1_pic_mode) > at_acfg_descr[ui2_id].z_def_size)
            {
                DBG_LOG_PRINT(("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                break;
            }

            /* Check array index. */
            if (ui2_id >= IDX_MAX)
            {
                DBG_ERROR (("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                break;
            }

            if (acfg_cust_video_is_special_item(ui2_id))
            {
                if((ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_DV* ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode) >= at_acfg_descr[ui2_id].z_def_size)
                {
                    DBG_INFO(("[ACFG]at_acfg_descr[ui2_id].z_def_size :%d, %s,%d\r\n",at_acfg_descr[ui2_id].z_def_size,__FUNCTION__,__LINE__));
                    DBG_INFO(("[ACFG] ui2_id %d overflow ui1_pic_mode %d ,ui1_def_val %d ui1_i %d ui1_inp_src %d\n", ui2_id,ui1_pic_mode,ui1_def_val,ui1_i,ui1_inp_src));
                    break;
                }
                /* data store by input sorce * picture mode * dynamic range */
                //dv
                *(((UINT8*)at_acfg_descr[ui2_id].pt_def_value)+
                    ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_DV* ACFG_PRE_SET_PIC_MODE_NUM +  ui1_pic_mode) = ui1_def_val;
            }
        }
    }
}
#ifdef APP_VIA_PLUS_PORTING
static UINT16 _a_cfg_av_get_screen_mode (VOID)
{
    INT32       i4_ret;
    INT16       i2_app_val;
    do
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
        ACFG_BREAK_ON_FAIL(i4_ret, i4_ret);
    } while (0);
    return (UINT16)i2_app_val;
}
#endif



static UINT32 _get_model_index_pqid()
{
#ifdef APP_CUST_SPEC_TYPE
    INT32 i4_ret = 0;

    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T  z_size = sizeof(UINT32);
    UINT32 ui4Value = 0;


    /* set operation type */
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_PQ_ID;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = &ui4Value;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );

    if(i4_ret < 0)
    {
        return 0;
    }

    return ui4Value;
#else
    return 0;
#endif
}


/*-----------------------------------------------------------------------------
 * Name: _get_hv_pos_idx
 *
 * Description: This function returns the field index in EEPROM.
 *
 * Inputs:  ui1_input_src   Input source index.
 *
 * Outputs: -
 *
 * Returns: field index.
 *
 ----------------------------------------------------------------------------*/
static UINT8 _get_hv_pos_idx(UINT8 ui1_input_src)
{
    CHAR                        s_disp_name[ACFG_MAX_DISP_NAME + 1];
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
    ISL_REC_T t_isl_rec;
    SVL_REC_T t_svl_rec;
    DEVICE_TYPE_T device_type;
    UINT16 ui2_i;
    UINT8  ui1_default_idx;
    BOOL b_svl_found = FALSE;

    /* Get current timing */
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_timing(s_disp_name, &t_timing);
    a_isl_get_rec_by_idx (ui1_input_src, &t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        acfg_get_crnt_svl_rec(&t_svl_rec, &b_svl_found);
        if (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG || b_svl_found==FALSE)
        {
            device_type = DEV_TUNER_TER_ANA;
        }
        else
        {
            device_type = DEV_TUNER_TER_DIG;
        }
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
    {
        device_type = t_isl_rec.t_avc_info.e_video_type;
    }
    else
    {
        device_type = DEV_UNKNOWN;
    }

    if ( a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
    {
        device_type = DEV_UNKNOWN;
    }

    ui1_default_idx = 0;
    for (ui2_i = 0;
         ui2_i < (UINT16)(sizeof (at_timing_hv_map)/sizeof (at_timing_hv_map[0]));
         ui2_i++)
    {
        /* Get default values if video height is not explicitly listed. */
        if (device_type == at_timing_hv_map[ui2_i].e_video_type &&
            at_timing_hv_map[ui2_i].ui4_height == 0)
        {
            ui1_default_idx = at_timing_hv_map[ui2_i].ui1_idx;
        }

        /*
         *  Get proper index if video height is explicitly listed and override
         *  former value.
         */
        if (device_type == at_timing_hv_map[ui2_i].e_video_type &&
            at_timing_hv_map[ui2_i].ui4_height == t_timing.ui4_height &&
            at_timing_hv_map[ui2_i].ui1_internal_id == t_isl_rec.ui1_internal_id)
        {
            ui1_default_idx = at_timing_hv_map[ui2_i].ui1_idx;
            break;
        }
    }

    if((DEV_TUNER_TER_DIG == device_type) && (0 == ui1_default_idx))
    {
        for (ui2_i=0;
             ui2_i < sizeof(at_timing_hv_map)/ sizeof(at_timing_hv_map[0]);
             ui2_i++)
        {
            if (DEV_TUNER_TER_DIG == at_timing_hv_map[ui2_i].e_video_type)
            {
                if( ( (t_timing.ui4_height >= at_timing_hv_map[ui2_i].ui4_height-10) &&
                     (t_timing.ui4_height <= at_timing_hv_map[ui2_i].ui4_height+10) ) &&
                   at_timing_hv_map[ui2_i].ui4_height != 0)
                {
                    ui1_default_idx = at_timing_hv_map[ui2_i].ui1_idx;
                }
            }
        }
    }

    return ui1_default_idx;
}

/*-----------------------------------------------------------------------------
 * Name: _get_input_grp
 *
 * Description:
 *  Used for settings which are stored by input source group
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static UINT8 _get_input_grp(ISL_REC_T* pt_isl_rec)
{
    return acfg_custom_get_input_grp (pt_isl_rec);
}

static INT32 _get_overscan(
                CHAR*                           s_disp_name,
                SCC_VID_OVER_SCAN_CLIPPER_T*    pt_overscan
                )
{
    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} s_disp_name:%s \n",
            __FUNCTION__,__LINE__, s_disp_name ));
    );

    return acfg_video_update_check_overscan(s_disp_name, pt_overscan);
}

static INT32 _get_hv_pos(CHAR* s_disp_name, INT16 *pi2_h, INT16 *pi2_v)
{
    INT32 i4_ret = APP_CFGR_OK;
    INT16 i2_h_pos = 0;
    INT16 i2_v_pos = 0;

    if (NULL == pi2_h || NULL == pi2_v)
    {
        return APP_CFGR_INV_ARG;
    }

    {
        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H), &i2_h_pos);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V), &i2_v_pos);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }

    *pi2_h = i2_h_pos;
    *pi2_v = i2_v_pos;

    return i4_ret;
}

static INT32 _get_hv_size(CHAR* s_disp_name, INT16 *pi2_h, INT16 *pi2_v)
{
    INT32 i4_ret = APP_CFGR_OK;
    INT16 i2_v_size = 0;
    INT16 i2_h_size = 0;
    SIZE_T  z_size = 0;
    UINT8 ui1_input_id;
    ISL_REC_T t_isl_rec = {0};

    if (NULL == pi2_h || NULL == pi2_v)
    {
        return APP_CFGR_INV_ARG;
    }

    if (menu_picture_size_poition_is_hidde() || !menu_picture_position_is_enable())
    {
       *pi2_h = 0;
       *pi2_v = 0;
       return APP_CFGR_OK;   // do nothing
    }

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type
        && DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type
        && a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED
#ifdef APP_MENU_MMP_COEXIST
        && MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status()
        && MMP_MAIN_AP_STATUS_RESUMED != a_mmp_get_ap_status()
#endif
        )
    {
        z_size = sizeof(INT16);
        i4_ret = acfg_get(IDX_CUSTOM_VGA_H_SIZE, &i2_h_size, &z_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        i4_ret = acfg_get(IDX_CUSTOM_VGA_V_SIZE, &i2_v_size, &z_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }
    else
    {
        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE), &i2_h_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE), &i2_v_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }

    *pi2_h = i2_h_size;
    *pi2_v = i2_v_size;

    return i4_ret;
}

INT32 acfg_cust_add_h_v_position_to_overscan(UINT16                                *pui2_up,      /* IN/OUT */
                                        UINT16                                  *pui2_down,    /* IN/OUT */
                                        UINT16                                  *pui2_left,    /* IN/OUT */
                                        UINT16                                  *pui2_right    /* IN/OUT */)
{
    INT16 i2_v_pos = 0;
    INT16 i2_h_pos = 0;
    INT16 i2_variation = 320;
    UINT32 i2_pana =0;
    UINT32 comp_result =0;
    INT16 i2_app_val;
    INT32 i4_ret;
    UINT16 ui2_id_h = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
    UINT16 ui2_id_v = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
    BOOL    b_left = FALSE;
    BOOL    b_up = TRUE;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get(ui2_id_h, &i2_h_pos);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    a_cfg_av_get(ui2_id_v, &i2_v_pos);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (i2_h_pos < 0)
    {
        i2_h_pos = 0 - i2_h_pos;
        b_left = TRUE;
    }

    if (i2_v_pos < 0)
    {
        i2_v_pos = 0 - i2_v_pos;
        b_up = FALSE;
    }

    i2_v_pos *= 10;
    i2_h_pos *= 10;

    if(SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM == i2_app_val)
    {
     if(*pui2_left  >= *pui2_right)
         i2_pana = *pui2_left;
     else
         i2_pana = *pui2_right;
     comp_result = i2_pana + 1000*2 - i2_variation;

     if(comp_result >1880)
         i2_variation = 2000 + i2_pana -1880;
    }

    if (i2_v_pos <= i2_variation)
    {
        if (b_up){*pui2_up += i2_v_pos;}
        else {*pui2_down += i2_v_pos;}
    }
    else
    {
        if (b_up){*pui2_up  += i2_v_pos*2 - i2_variation;}
        else {*pui2_down += i2_v_pos*2 - i2_variation;}
    }

    if (i2_h_pos <= i2_variation)
    {
        if (b_left){*pui2_left += i2_h_pos;}
        else {*pui2_right += i2_h_pos;}
    }
    else
    {
        if (b_left){*pui2_left += i2_h_pos*2 - i2_variation;}
        else {*pui2_right += i2_h_pos*2 - i2_variation;}
    }

    return APP_CFGR_OK;
}


INT32 acfg_cust_add_h_v_size_to_overscan(UINT16                                *pui2_up,      /* IN/OUT */
                                        UINT16                                  *pui2_down,    /* IN/OUT */
                                        UINT16                                  *pui2_left,    /* IN/OUT */
                                        UINT16                                  *pui2_right    /* IN/OUT */)
{
     INT16 i2_v_size = 0;
     INT16 i2_h_size = 0;
     INT16 i2_variation = 320;
     UINT32 i2_pana =0;
     UINT32 comp_result =0;
     INT16 i2_app_val;
     INT32 i4_ret;
     UINT8 ui1_input_id;
     SIZE_T  z_size = 0;
     ISL_REC_T t_isl_rec = {0};
     UINT8   ui1_scr_mode = 0;
     CHAR            s_disp_name[64] = {0};

     if (menu_picture_size_poition_is_hidde() || !menu_picture_position_is_enable())
     {
        return APP_CFGR_OK;   // do nothing
     }

     i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     if (menu_page_color_tuner_is_scrn_mode()
         || a_cfg_custom_chk_freqence_120hz())
     {
         return APP_CFGR_OK;   // do nothing
     }
     z_size = ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE;

     i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                                &ui1_scr_mode, &z_size);
     if ((i4_ret == 0)&&(ui1_scr_mode == 1))
     {
         return APP_CFGR_OK;
     }

     i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type
         && DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type
         && a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED
#ifdef APP_MENU_MMP_COEXIST
         && MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status()
         && MMP_MAIN_AP_STATUS_RESUMED != a_mmp_get_ap_status()
#endif
         )
     {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        z_size = sizeof(INT16);
        i4_ret = acfg_get(IDX_CUSTOM_VGA_H_SIZE, &i2_h_size, &z_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        i4_ret = acfg_get(IDX_CUSTOM_VGA_V_SIZE, &i2_v_size, &z_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
     }
     else
     {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE), &i2_h_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE), &i2_v_size);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
     }
     DBG_LOG_PRINT(("-----------------baozi %s %d i2_h_size= %d, i2_v_size=%d\n",__FUNCTION__,__LINE__, i2_h_size, i2_v_size));

     if (i2_h_size < 0)
     {
         i2_h_size = 0;
     }

     if (i2_v_size < 0)
     {
         i2_v_size = 0;
     }

     if (i2_v_size >= 0)
     {
         i2_v_size *= 10;

         if (i2_v_size <= i2_variation)
         {
             *pui2_up += i2_v_size;
             *pui2_down += i2_v_size;
         }
         else
         {
             *pui2_up  += i2_v_size*2 - i2_variation;
             *pui2_down += i2_v_size*2 - i2_variation;
         }
     }

     if(SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM == i2_app_val)
     {
         if(*pui2_left  >= *pui2_right)
             i2_pana = *pui2_left;
         else
             i2_pana = *pui2_right;
         comp_result = i2_pana + 1000*2 - i2_variation;

         if(comp_result >1880)
             i2_variation = 2000 + i2_pana -1880;
     }

     if (i2_h_size >= 0)
     {
         i2_h_size *= 10;

         if (i2_h_size <= i2_variation)
         {
             *pui2_left += i2_h_size;
             *pui2_right += i2_h_size;
         }
         else
         {
             *pui2_left += i2_h_size*2 - i2_variation;
             *pui2_right += i2_h_size*2 - i2_variation;
         }
     }

     return APP_CFGR_OK;
}


static INT32 _get_overscan_with_h_v_size (CHAR* s_disp_name, SCC_VID_OVER_SCAN_CLIPPER_T* pt_overscan)
{
    INT16 i2_v_size = 0;
    INT16 i2_h_size = 0;
    INT16 i2_variation = 320;
    UINT32 i2_pana =0;
    UINT32 comp_result =0;
    INT16 i2_app_val;
    INT32 i4_ret;
    UINT8 ui1_input_id;
    SIZE_T  z_size = 0;
    ISL_REC_T t_isl_rec = {0};
    UINT8   ui1_scr_mode = 0;



    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} s_disp_name:%s \n",
            __FUNCTION__,__LINE__, s_disp_name ));
    );


    if (!pt_overscan)
    {
        return APP_CFGR_INV_ARG;
    }
    if (menu_page_color_tuner_is_scrn_mode()
        || a_cfg_custom_chk_freqence_120hz())
    {
        pt_overscan->ui4_top      = 0;
        pt_overscan->ui4_bottom   = 0;
        pt_overscan->ui4_left = 0;
        pt_overscan->ui4_right = 0;

        ACFG_DEBUG_OVER_SCAN(
            DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} No OverScan \n",
                __FUNCTION__,__LINE__ ));
        );

        return APP_CFGR_OK;
    }
    z_size = ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                               &ui1_scr_mode, &z_size);

    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} ui1_scr_mode:%d \n",
            __FUNCTION__,__LINE__, ui1_scr_mode ));
    );

    if ((i4_ret==APP_CFGR_OK)&&(ui1_scr_mode == 1))
    {
        pt_overscan->ui4_top      = 0;
        pt_overscan->ui4_bottom   = 0;
        pt_overscan->ui4_left = 0;
        pt_overscan->ui4_right = 0;

        ACFG_DEBUG_OVER_SCAN(
            DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} No OverScan \n",
                __FUNCTION__,__LINE__ ));
        );

        return APP_CFGR_OK;
    }

    i4_ret = _get_overscan(s_disp_name, pt_overscan);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type
        && DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type
        && a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED
#ifdef APP_MENU_MMP_COEXIST
        && MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status()
        && MMP_MAIN_AP_STATUS_RESUMED != a_mmp_get_ap_status()
#endif
        )
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }
    else
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }
    _get_hv_size(s_disp_name, &i2_h_size, &i2_v_size);

    /* Clear over scan */
    if (i2_h_size < 0)
    {
        i2_h_size = 0;
    }

    if (i2_v_size < 0)
    {
        i2_v_size = 0;
    }

    if (i2_v_size >= 0)
    {
        i2_v_size *= 10;

        if (i2_v_size <= i2_variation)
        {
            pt_overscan->ui4_top      += i2_v_size;
            pt_overscan->ui4_bottom   += i2_v_size;
        }
        else
        {
            pt_overscan->ui4_top      += i2_v_size*2 - i2_variation;
            pt_overscan->ui4_bottom   += i2_v_size*2 - i2_variation;
        }
    }

    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} (ui4_top:%d, ui4_bottom:%d) \n",
            __FUNCTION__,__LINE__,
            pt_overscan->ui4_top, pt_overscan->ui4_bottom  ));
    );


    if(SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM == i2_app_val)
    {
        if(pt_overscan->ui4_left  >= pt_overscan->ui4_right )
            i2_pana = pt_overscan->ui4_left ;
        else
            i2_pana = pt_overscan->ui4_right ;
        comp_result = i2_pana + 1000*2 - i2_variation;

        if(comp_result >1880)
            i2_variation = 2000 + i2_pana -1880;
    }

    if (i2_h_size >= 0)
    {
        i2_h_size *= 10;

        if (i2_h_size <= i2_variation)
        {
            pt_overscan->ui4_left     += i2_h_size;
            pt_overscan->ui4_right    += i2_h_size;
        }
        else
        {
            pt_overscan->ui4_left     += i2_h_size*2 - i2_variation;
            pt_overscan->ui4_right    += i2_h_size*2 - i2_variation;
        }
    }

    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} (left:%d, right:%d ) \n",
            __FUNCTION__,__LINE__,
            pt_overscan->ui4_left, pt_overscan->ui4_right  ));
    );

    return APP_CFGR_OK;
}

static INT32 _get_overscan_with_h_v_pos (CHAR* s_disp_name, SCC_VID_OVER_SCAN_CLIPPER_T* pt_overscan)
{
    INT16 i2_v_pos = 0;
    INT16 i2_h_pos = 0;
    INT16 i2_variation = 320;
    UINT32 i2_pana =0;
    UINT32 comp_result =0;
    INT16 i2_app_val;
    INT32 i4_ret;
    BOOL    b_left = FALSE;
    BOOL    b_up = TRUE;

    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} s_disp_name:%s \n",
            __FUNCTION__,__LINE__, s_disp_name ));
    );

    if (!pt_overscan)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    //i4_ret = _get_overscan(s_disp_name, pt_overscan);
    //ACFG_CHK_FAIL(i4_ret, i4_ret);

    _get_hv_pos(s_disp_name, &i2_h_pos, &i2_v_pos);

    /* Clear over scan */
    if (i2_h_pos < 0)
    {
        i2_h_pos = 0 - i2_h_pos;
        b_left = TRUE;
    }

    if (i2_v_pos < 0)
    {
        i2_v_pos = 0 - i2_v_pos;
        b_up = FALSE;
    }

    i2_v_pos *= 10;
    i2_h_pos *= 10;

    if(SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM == i2_app_val)
    {
        if(pt_overscan->ui4_left  >= pt_overscan->ui4_right )
            i2_pana = pt_overscan->ui4_left ;
        else
            i2_pana = pt_overscan->ui4_right ;
        comp_result = i2_pana + 1000*2 - i2_variation;

        if(comp_result >1880)
            i2_variation = 2000 + i2_pana -1880;
    }

    if (i2_v_pos <= i2_variation)
    {
        if (b_up){pt_overscan->ui4_top += i2_v_pos;}
        else {pt_overscan->ui4_bottom += i2_v_pos;}
    }
    else
    {
        if (b_up){pt_overscan->ui4_top += i2_v_pos*2 - i2_variation;}
        else {pt_overscan->ui4_bottom += i2_v_pos*2 - i2_variation;}
    }

    if (i2_h_pos <= i2_variation)
    {
        if (b_left){pt_overscan->ui4_left += i2_h_pos;}
        else {pt_overscan->ui4_right += i2_h_pos;}
    }
    else
    {
        if (b_left){pt_overscan->ui4_left += i2_h_pos*2 - i2_variation;}
        else {pt_overscan->ui4_right += i2_h_pos*2 - i2_variation;}
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _pos_update_custom
 *
 * Description:
 *  update postion h/v under Non-VGA mode
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _pos_update_custom (UINT16 ui2_id)
{
    INT32       i4_ret;
    UINT16      ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    HANDLE_T    h_scc_comp;
    // position range of dirver is [0, 100]
    UINT16      ui2_drv_min_val = 0, ui2_drv_max_val = PIC_POSITIOIN_DRV_MAX_VALUE, ui2_drv_mid_val = 0;
    INT16       i2_app_val, i2_app_min, i2_app_max;
    INT16       i2_pos;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_input_id;
    VSH_SRC_RESOLUTION_INFO_T   t_timing;
    SVL_REC_T                   t_svl_rec;
    BOOL                        b_svl_found = FALSE;

    c_memset (&t_timing, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_timing(s_disp_name, &t_timing);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
        t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO
       )
    {
        /* VGA timing pos should update by APP_CFG_RECID_VGA_POS_H/V */
        //return APP_CFGR_OK;
    }

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        acfg_get_crnt_svl_rec(&t_svl_rec, &b_svl_found);
        if (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG ||
            b_svl_found==FALSE)
        {
            //do nothing
        }
        else
        {
            /* dtv position changed by dst_region&overscan  */
            a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
            return APP_CFGR_OK;
        }
    }

    /* Get SCC handle by display name. */
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                  h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

    /* get the app min max value */
    i4_ret = a_cfg_av_get(ui2_id, &i2_app_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_min_max(ui2_id, &i2_app_min, &i2_app_max);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (i2_app_val > i2_app_max)
    {
        i2_app_val = i2_app_max;
    }
    if (i2_app_val < i2_app_min)
    {
        i2_app_val = i2_app_min;
    }
    DBG_LOG_PRINT(("<ACFG> The min/max pos in driver is[%d,%d].\n", ui2_drv_min_val, ui2_drv_max_val));

    i2_app_val = i2_app_val * 6;

    /* Get middle driver value. */
    ui2_drv_mid_val = (ui2_drv_min_val + ui2_drv_max_val) / 2;

    /* Always set H/V pos to default if updating SUB. */
    if (c_strcmp(s_disp_name, SN_PRES_SUB_DISPLAY) == 0)
    {
        i2_pos = ui2_drv_mid_val;
    }
    else
    {
        if (ui2_cfg_rec == APP_CFG_RECID_VID_POS_H)
        {
            /* AP 1 step = driver 2 step. */
            i2_pos = ui2_drv_mid_val + (i2_app_val - ACFG_VID_POS_H_DEF);
        }
        else
        {
            /* AP 1 step = driver 2 step. */
            i2_pos = ui2_drv_mid_val + (i2_app_val - ACFG_VID_POS_V_DEF);
        }
    }
    if (i2_pos > ui2_drv_max_val)
    {
        DBG_ERROR(("<ACFG> pos exceed max value.\n"));
        i2_pos = ui2_drv_max_val;
    }
    if (i2_pos < ui2_drv_min_val)
    {
        DBG_ERROR(("<ACFG> pos exceed min value.\n"));
        i2_pos = ui2_drv_min_val;
    }

    /* set to driver */
    if (ui2_cfg_rec == APP_CFG_RECID_VID_POS_H)
    {
        i4_ret = c_scc_vid_set_h_position (h_scc_comp, i2_pos);
    }
    else
    {
        i4_ret = c_scc_vid_set_v_position (h_scc_comp, i2_pos);
    }
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
#ifdef ACFG_MM_CUST_VMUTE_CONFIG
/*-----------------------------------------------------------------------------
 * Name: acfg_custom_mm_vmute_config
 *
 * Description:
 *  This function is to configure the video mute behavior
 *
 *
 *                            >   < = pui4_timeout_vsync
 *  ------+-------------------+---+------------
 *        a                   b   c
 *  a = the time when a channel or input source is selected
 *  b = the video format (timing) is ready.
 *  c = internally delay for a monent to wait for 2~3 vsync so that the screen
 *      settings are set to driver.
 *
 *        >    pui4_timeout_chg_svc    <
 *  ------+----------------------------+------------
 *        a                            d
 *  a = the time when a channel or input source is selected
 *  d = if the video format is not ready for a while, we unmute the video to prevent
 *      that maybe we lose the video format change event.
 *
 *
 * Inputs:
 *  e_cond  -   The condition of service change
 *
 * Outputs:
 *  pb_vmute_enabled        -   If we should enable the video mute in app part
 *                              for this service change condition
 *  pui4_timeout_chg_svc    -   The timeout for SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE
 *  pui4_timeout_vsync      -   The timeout for vsync.
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern VOID acfg_custom_mm_vmute_config(
    ACFG_MM_SVC_CHG_COND_T  e_cond,
    BOOL*                   pb_vmute_enabled,
    UINT32*                 pui4_timeout_chg_svc,
    UINT32*                 pui4_timeout_vsync)
{
    *pui4_timeout_vsync = ACFG_MM_DEFAULT_VSYNC_TIMEOUT;

    switch(e_cond)
    {
    case ACFG_MM_SVC_CHG_COND_DTV_FROM_DTV:
        *pb_vmute_enabled = FALSE;
        break;
    case ACFG_MM_SVC_CHG_COND_ATV_FROM_ATV:
    case ACFG_MM_SVC_CHG_COND_ATV_FROM_DTV:
    case ACFG_MM_SVC_CHG_COND_DTV_FROM_ATV:
    case ACFG_MM_SVC_CHG_COND_ATV:
    case ACFG_MM_SVC_CHG_COND_DTV:
    case ACFG_MM_SVC_CHG_COND_HDMI:
    case ACFG_MM_SVC_CHG_COND_VGA:
    case ACFG_MM_SVC_CHG_COND_AV:
    case ACFG_MM_SVC_CHG_COND_MULTIMEDIA:
        *pb_vmute_enabled = TRUE;
        *pui4_timeout_chg_svc = ACFG_MM_DEFAULT_SVC_CHG_TIMEOUT;
        break;
    case ACFG_MM_SVC_CHG_COND_UNKNWON:
    default:
        *pb_vmute_enabled = TRUE;
        *pui4_timeout_chg_svc = ACFG_MM_DEFAULT_SVC_CHG_TIMEOUT;
        break;
    }
}
#endif

static UINT8 _get_hvpos_scrmode_elem_idx(UINT8 ui1_input_src)
{
    CHAR                        s_disp_name[ACFG_MAX_DISP_NAME + 1];
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
    ISL_REC_T                   t_isl_rec;
    SVL_REC_T                   t_svl_rec;
    DEVICE_TYPE_T               e_device_type;
    UINT16                      ui2_i;
    UINT8                       ui1_elem_idx = 0;
    BOOL                        b_svl_found = FALSE;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;

    /* Get current timing */
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_timing(s_disp_name, &t_timing);
    a_isl_get_rec_by_idx (ui1_input_src, &t_isl_rec);

    e_src_asp_ratio = a_sml_get_src_asp_ratio(&t_timing);

    #ifdef Virtual_Port_MMP
        if( a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
        {
            /* get record number */
            a_isl_get_num_rec(&ui1_elem_idx);
            ui1_elem_idx--;//Henry Wang - 01/28/2010 - MMP is true port
            DBG_LOG_PRINT(("Load MMP scrmode_elem_idx= %d\n", ui1_elem_idx));
            return ui1_elem_idx;
        }
    #endif

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        acfg_get_crnt_svl_rec(&t_svl_rec, &b_svl_found);
        if (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG ||
            b_svl_found==FALSE)
        {
            e_device_type = DEV_TUNER_TER_ANA;
        }
        else
        {
            e_device_type = DEV_TUNER_TER_DIG;
        }
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
    {
        #ifdef CC_YPBPR_IN_VGA_SUPPORT
        if( t_isl_rec.t_avc_info.e_video_type==DEV_AVC_VGA && t_timing.e_timing_type==VSH_SRC_TIMING_VIDEO)
        {
            e_device_type = DEV_AVC_Y_PB_PR;
        }
        else
        #endif
        {
            if(C_Get_YPbPr_flag()==TRUE)
                e_device_type = DEV_AVC_Y_PB_PR;
            else
                e_device_type = t_isl_rec.t_avc_info.e_video_type;
        }
    }
    else
    {
        e_device_type = DEV_AVC_COMP_VIDEO;
    }

    ui1_elem_idx = 0;
    for (ui2_i=0;
         ui2_i < sizeof(at_timing_scr_map)/ sizeof(at_timing_scr_map[0]);
         ui2_i++)
    {
        if (at_timing_scr_map[ui2_i].e_video_type != e_device_type)
        {
            continue;
        }

        if (at_timing_scr_map[ui2_i].ui1_internal_id != t_isl_rec.ui1_internal_id)
        {
            continue;
        }

        if( at_timing_scr_map[ui2_i].ui4_height          != t_timing.ui4_height &&
            at_timing_scr_map[ui2_i].ui4_height          != 0)
        {
            continue;
        }

        if( DEV_AVC_VGA == at_timing_scr_map[ui2_i].e_video_type)
        {
            if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_16_9 && at_timing_scr_map[ui2_i].ui1_idx!=14)
            {
                continue;
            }
        }

        ui1_elem_idx = at_timing_scr_map[ui2_i].ui1_idx;
        break;
    }

    // if current heght is not standard (ex. 1088) & Digital TV, set tolerance is -10 to +10.
    if((DEV_TUNER_TER_DIG == e_device_type || DEV_AVC_HDMI == e_device_type)
        && (0 == ui1_elem_idx))
    {
        for (ui2_i=0;
             ui2_i < sizeof(at_timing_scr_map)/ sizeof(at_timing_scr_map[0]);
             ui2_i++)
        {
            if (DEV_TUNER_TER_DIG == e_device_type)
            {
                if (DEV_TUNER_TER_DIG == at_timing_scr_map[ui2_i].e_video_type)
                {
                    if( ( (t_timing.ui4_height >= at_timing_scr_map[ui2_i].ui4_height-10) &&
                         (t_timing.ui4_height <= at_timing_scr_map[ui2_i].ui4_height+10) ) &&
                       at_timing_scr_map[ui2_i].ui4_height != 0)
                    {
                        DBG_LOG_PRINT(("dtv \n"));
                        ui1_elem_idx = at_timing_scr_map[ui2_i].ui1_idx;
                    }
                }
            }
            else if (DEV_AVC_HDMI == e_device_type)
            {
                if (DEV_AVC_HDMI == at_timing_scr_map[ui2_i].e_video_type
                    && (at_timing_scr_map[ui2_i].ui1_internal_id == t_isl_rec.ui1_internal_id))
                {
                    if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_16_9)
                    {
                        ui1_elem_idx = at_timing_scr_map[ui2_i].ui1_idx + 2;
                    }
                    else
                    {
                        ui1_elem_idx = at_timing_scr_map[ui2_i].ui1_idx;
                    }
                    break;
                }
            }
        }
    }

    return ui1_elem_idx;
}
static UINT8 _acfg_cust_source_is_HDR(UINT32 ui4_source_num)
{
    if(
        (ui4_source_num == ACFG_INPUT_SRC_NUM) ||       //HDMI1 HDR
        (ui4_source_num == ACFG_INPUT_SRC_NUM + 3)||    //HDMI2 HDR
        (ui4_source_num == ACFG_INPUT_SRC_NUM + 6)||    //HDMI3 HDR
        (ui4_source_num == ACFG_INPUT_SRC_NUM + 9)||    //HDMI4 HDR
        (ui4_source_num == ACFG_INPUT_SRC_NUM + 12)     //MMP   HDR
        )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
static UINT8 _acfg_cust_HDR_alz_default(UINT8 ui1_pic_mode) //active LED zone HDR source default value
{
    UINT8 ui1_ret = 0;
    if( (ui1_pic_mode == ACFG_CUST_PIC_MODE_STANDARD)||     //picture mode standard
        (ui1_pic_mode == ACFG_CUST_PIC_MODE_DARK_ROOM)||    //picture mode calibrated dark
        (ui1_pic_mode == ACFG_CUST_PIC_MODE_BRIGHT_ROOM)||  //picture mode calibrated
        (ui1_pic_mode == ACFG_CUST_PIC_MODE_GAME))          //picture mode game
    {
        ui1_ret = 2;
    }
    else if(ui1_pic_mode == ACFG_CUST_PIC_MODE_VIVID)      //picture mode VIVID
    {
        ui1_ret = 3;
    }
    else if(ui1_pic_mode == ACFG_CUST_PIC_MODE_COMPUTER)    //picture mode computer
    {
        ui1_ret = 0;
    }

    return ui1_ret;
}

static INT32 _acfg_cust_video_init_def_value(VOID)
{
    UINT32  ui4_gain_offset_id = 0;
    UINT16  ui2_ipt_idx        = 0;
    UINT16  ui2_pic_idx        = 0;
    INT16   i2_value_def       = 0;
    UINT16  ui2_idx            = 0;
    UINT16  ui2_item_idx        = 0;

    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ================================ start \n",
        __FILE__, __FUNCTION__, __LINE__ ));

    ui4_pq_id = _get_model_index_pqid();

    DBG_LOG_PRINT(("\n _acfg_cust_video_init_def_value() pqid[%d]\n",ui4_pq_id));


#ifdef APP_CFG_CUSTOM_OVERWRITE_CLR_GAIN_OFFSET_DEF_TBL
    ui4_gain_offset_id = ui4_pq_id;
#endif

    /* Overwrite the Color gain/offset default value */
    {
        UINT8   ui1_i;
        UINT8   ui1_j;

#ifdef APP_CLR_GAIN_AND_OFFSET_NOT_DIS_2D_3D
        for(ui1_i = 0;
             ui1_i < (UINT8)(ACFG_CLR_GAIN_ELEM_NUM) /* Gain & Offset */;
             ui1_i++)
        {
            for(ui1_j = 0; ui1_j < 3 /*RGB*/; ui1_j++)
            {
                *(((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R + ui1_j].pt_def_value)+ui1_i)
                    = (UINT8)aai2_clr_gain[ui4_gain_offset_id][ui1_i][ui1_j];
                *(((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R + ui1_j].pt_def_value)+ui1_i)
                    = (UINT8)aai2_clr_offset[ui4_gain_offset_id][ui1_i][ui1_j];
            }
        }
#else
        for(ui1_i = 0;
             ui1_i < (UINT8)(ACFG_CLR_GAIN_ELEM_NUM - ACFG_3D_CLR_GAIN_ELEM_NUM) /* Gain & Offset */;
             ui1_i++)
        {
            for(ui1_j = 0; ui1_j < 3 /*RGB*/; ui1_j++)
            {
                *(((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R + ui1_j].pt_def_value)+ui1_i)
                    = (UINT8)aai2_clr_gain[ui4_gain_offset_id][ui1_i][ui1_j];
                *(((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R + ui1_j].pt_def_value)+ui1_i)
                    = (UINT8)aai2_clr_offset[ui4_gain_offset_id][ui1_i][ui1_j];
            }
        }

        /* 3D Color gain/offset default value */
        for(;
             ui1_i < (UINT8)(ACFG_3D_CLR_GAIN_ELEM_NUM) /* Gain & Offset */;
             ui1_i++)
        {
            for(ui1_j = 0; ui1_j < 3 /*RGB*/; ui1_j++)
            {
                *(((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R + ui1_j].pt_def_value)+ui1_i)
                    = (UINT8)aai2_3d_clr_gain[ui4_gain_offset_id][ui1_i][ui1_j];
                *(((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R + ui1_j].pt_def_value)+ui1_i)
                    = (UINT8)aai2_3d_clr_offset[ui4_gain_offset_id][ui1_i][ui1_j];
            }
        }
#endif
    }


    ACFG_DEBUG_NR_DEFAULT(
        DBG_LOG_PRINT(("[ACFG][NR]{%s,%d} at_acfg_descr[IDX_VID_NR].pt_def_value=0x%X \n",
            __FUNCTION__,__LINE__, (UINT32)at_acfg_descr[IDX_VID_NR].pt_def_value ));
    );


    /* overwrite the pq settings default*/
    for (ui2_ipt_idx = 0; ui2_ipt_idx < (ACFG_INPUT_SRC_NUM + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM); ui2_ipt_idx ++)
    {
        for (ui2_pic_idx = 0; ui2_pic_idx < ACFG_PIC_MODE_NUM; ui2_pic_idx ++)
        {
            /*calculate the index*/
            ui2_idx = ui2_ipt_idx*ACFG_PIC_MODE_NUM + ui2_pic_idx;

            /*IDX_DISP_BACK_LIGHT*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_DISP_BACK_LIGHT, ui2_pic_idx);
            if( ((ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 2)||//HDMI1_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 5)||//HDMI2_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 8)||//HDMI3_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 11)||//HDMI4_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 14))//MMP_DOLBY_VISION
                &&((ui2_pic_idx == 1)||(ui2_pic_idx == 2)))
                /* for Dolby version picture mode Calibrated & Calibrated Dark backlight default will set to 50*/
            {
                *(((UINT8*)at_acfg_descr[IDX_DISP_BACK_LIGHT].pt_def_value)+ui2_idx)= (UINT8)50;
            }
            else if(ui2_ipt_idx >= ACFG_INPUT_SRC_NUM)  //for HDR or HLG the backlight will set to 100
            {
                *(((UINT8*)at_acfg_descr[IDX_DISP_BACK_LIGHT].pt_def_value)+ui2_idx)= (UINT8)100;
            }
            else
            {
                *(((UINT8*)at_acfg_descr[IDX_DISP_BACK_LIGHT].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;
            }

            /*IDX_VID_BRI*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_BRI, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_BRI].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_CNT*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_CNT, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_CNT].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_SAT*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_SAT, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_SAT].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_HUE*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_HUE, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_HUE].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_SHP*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_SHP, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_SHP].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_CLR_TEMP*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_CLR_TEMP, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_CLR_TEMP].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_3D_NR*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_3D_NR, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_3D_NR].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_NR*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_NR, ui2_pic_idx);

            if((ui2_ipt_idx >= ACFG_INPUT_SRC_NUM) &&
                ((ui2_pic_idx == 1)||(ui2_pic_idx == 2)))
            {
                ACFG_DEBUG_NR_DEFAULT(
                    DBG_LOG_PRINT(("[ACFG][NR]{%s,%d} (ui2_ipt_idx:%d, ui2_pic_idx:%d, ui2_idx:%d) => i2_value_def:0 !!!!! \n",
                        __FUNCTION__,__LINE__, ui2_ipt_idx, ui2_pic_idx, ui2_idx));
                );

                *(((UINT8*)at_acfg_descr[IDX_VID_NR].pt_def_value)+ui2_idx) = (UINT8)0;
            }
            else
            {
                ACFG_DEBUG_NR_DEFAULT(
                    DBG_LOG_PRINT(("[ACFG][NR]{%s,%d} (ui2_ipt_idx:%d, ui2_pic_idx:%d, ui2_idx:%d) => i2_value_def:%d \n",
                        __FUNCTION__,__LINE__, ui2_ipt_idx, ui2_pic_idx, ui2_idx, i2_value_def));
                );

                *(((UINT8*)at_acfg_descr[IDX_VID_NR].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;
            }

            /*IDX_VID_MPEG_NR*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_MPEG_NR, ui2_pic_idx);
            if((ui2_ipt_idx >= ACFG_INPUT_SRC_NUM) &&
                ((ui2_pic_idx == 1)||(ui2_pic_idx == 2)))
            {
                *(((UINT8*)at_acfg_descr[IDX_VID_MPEG_NR].pt_def_value)+ui2_idx) = (UINT8)0;
            }
            else
            {
                *(((UINT8*)at_acfg_descr[IDX_VID_MPEG_NR].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;
            }

            /*IDX_VID_FT*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_FT, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_FT].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;


            /*IDX_VID_LUMA*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_LUMA, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_LUMA].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_CUSTOM_DCR_IDX*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_CUSTOM_DCR_IDX, ui2_pic_idx);
            aui1_dcr_def[ui2_idx] = (UINT8)i2_value_def;
           // *(((UINT8*)at_acfg_descr[IDX_CUSTOM_DCR_IDX].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_CUSTOM_DIMMING*/
            /* active LED zones */
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_CUSTOM_DIMMING, ui2_pic_idx);
            if (_acfg_cust_source_is_HDR(ui2_ipt_idx))
            {
                aui1_dimming_onoff[ui2_idx] = _acfg_cust_HDR_alz_default(ui2_pic_idx);
            }
            else if((ui2_ipt_idx >= ACFG_INPUT_SRC_NUM) &&
                ((ui2_pic_idx == 1)||(ui2_pic_idx == 2)))
            {
                aui1_dimming_onoff[ui2_idx] = (UINT8)0;
            }
            else
            {
                aui1_dimming_onoff[ui2_idx] = (UINT8)i2_value_def;
            }

            /*IDX_VID_DI_FILM_MODE*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_DI_FILM_MODE, ui2_pic_idx);
            *(((UINT8*)at_acfg_descr[IDX_VID_DI_FILM_MODE].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

             /* game mode*/
            i2_value_def = 0;
            acfg_cust_video_get_game_mode_def_value(ui2_pic_idx,&i2_value_def);
            *(((UINT8*)at_acfg_descr[IDX_VID_GAME_MODE].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_CUSTOM_LIGHT_SENSOR_IDX*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_pic_idx);
            if(ui2_ipt_idx >= ACFG_INPUT_SRC_NUM)  //for HDR or HLG the light_sensor will set to 0
            {
                 aui1_light_sensor_def[ui2_idx] = (UINT8)0;
            }
            else
            {
                aui1_light_sensor_def[ui2_idx] = (UINT8)i2_value_def;
            }
            //*(((UINT8*)at_acfg_descr[IDX_CUSTOM_LIGHT_SENSOR_IDX].pt_def_value)+ui2_idx)= (UINT8)i2_value_def;

            /*IDX_VID_MJC_EFFECT*/
            i2_value_def = 0;
            i2_value_def = _acfg_cust_video_get_def_val (IDX_VID_MJC_EFFECT, ui2_pic_idx);

            ui1_vid_mjc_effect_def[ui2_idx] = (UINT8)i2_value_def;


            /* reduce blur*/
            i2_value_def = 0;
            acfg_cust_video_get_reduce_blur_def_value(ui2_pic_idx,&i2_value_def);

            aui1_vid_reduce_blur_def[ui2_idx] = (UINT8)i2_value_def;

        }
    }

    /* set the gamma def ACFG_CUST_GAMMA_2_1*/
    for (ui2_idx = 0; ui2_idx < ACFG_VID_CUST_GAMMA_ELEM_NUM; ui2_idx ++)
    {
        aui1_vid_cust_gamma[ui2_idx] = ACFG_CUST_GAMMA_2_1;
    }

    /* modify calibrated dark to ACFG_CUST_GAMMA_2_2 */
    for (ui2_ipt_idx = 0;
         ui2_ipt_idx < ACFG_CUST_INPUT_GRP_MAX;
         ui2_ipt_idx ++)
    {
        ui2_item_idx = ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_DV* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_DARK_ROOM;
        if(ui2_item_idx >= ACFG_VID_CUST_GAMMA_ELEM_NUM )
        {
            //DBG_LOG_PRINT((" ui2_item_idx :%d,ACFG_VID_CUST_GAMMA_ELEM_NUM:%d %s,%d\r\n",ui2_item_idx,ACFG_VID_CUST_GAMMA_ELEM_NUM,__FUNCTION__,__LINE__));
            break;
        }
        //sdr
        aui1_vid_cust_gamma[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_DARK_ROOM] = ACFG_CUST_GAMMA_2_2;
        //hdr10 ,hdr10+
        aui1_vid_cust_gamma[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HDR* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_DARK_ROOM] = ACFG_CUST_GAMMA_2_2;
        //hlg
        aui1_vid_cust_gamma[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HLG* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_DARK_ROOM] = ACFG_CUST_GAMMA_2_2;
        //dv
        aui1_vid_cust_gamma[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_DV* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_DARK_ROOM] = ACFG_CUST_GAMMA_2_2;
    }

    /* set the vid rgb def*/
    for (ui2_idx = 0; ui2_idx < ACFG_PIC_QLT_ELEM_NUM; ui2_idx ++)
    {
        aui1_vid_cust_pq_setting_def[ui2_idx] = 0;
    }

    /* set the vid rgb def*/
    for (ui2_idx = 0; ui2_idx < ACFG_PRE_SET_PIC_MODE_CHG_ELEM_NUM; ui2_idx ++)
    {
        s_pre_pic_mode_chg[ui2_idx] = 0;
    }

    /* set the vid hrgb def*/
    for (ui2_idx = 0; ui2_idx < APP_CFG_HRGB_ELEM_NUM; ui2_idx ++)
    {
        aui1_vid_cust_rgb_def[ui2_idx] = ACFG_VID_RGB_ENABLE;
        aui1_vid_cust_hrgb_def[ui2_idx] = 0;
    }

    /* set the 2 point wb def*/
    for (ui2_idx = 0; ui2_idx < APP_CFG_2_POINT_WB_ELEM_NUM; ui2_idx ++)
    {
        aui1_vid_2_point_wb_def[ui2_idx] = 0;
    }

    /* 11point gain def*/
    for (ui2_idx = 0; ui2_idx < APP_CFG_11_POINT_GAIN_ELEM_NUM; ui2_idx ++)
    {
        aui1_vid_11_point_gain_def[ui2_idx] = 0;
    }

    /* 11point gain rgb*/
    for (ui2_idx = 0; ui2_idx < APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM; ui2_idx ++)
    {
        aui1_vid_11_point_gain_rgb_def[ui2_idx] = 0;
    }


    // Overwrite EDID default ...
#if( ACFG_HDMI_DIFF_EDID_DEFALUT )
    // 2021-05-28.MVP-4052: Default HDMI 2.1 Gaming Port For -J 5695
    acfg_cust_HDMI_setup_EDID_default();
#endif


    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} --------------------------- end \n",
        __FILE__, __FUNCTION__, __LINE__ ));

    return APP_CFGR_OK;
}
static INT32 _acfg_cust_video_def_value_0_overwrite_color_gain_offset_def(VOID)
{
    UINT32  ui4_gain_offset_id = 0;
    UINT8   ui1_i = 0;
    UINT8   ui1_j = 0;

    /* Overwrite the Color gain/offset default value */
#ifdef APP_CLR_GAIN_AND_OFFSET_NOT_DIS_2D_3D
    for(ui1_i = 0;
         ui1_i < (UINT8)(ACFG_CLR_GAIN_ELEM_NUM) /* Gain & Offset */;
         ui1_i++)
    {
        for(ui1_j = 0; ui1_j < 3 /*RGB*/; ui1_j++)
        {
            *(((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R + ui1_j].pt_def_value)+ui1_i)
                = (UINT8)aai2_clr_gain_value_0_def[ui4_gain_offset_id][ui1_i][ui1_j];
            *(((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R + ui1_j].pt_def_value)+ui1_i)
                = (UINT8)aai2_clr_offset_value_0_def[ui4_gain_offset_id][ui1_i][ui1_j];
        }
    }
#else
    for(ui1_i = 0;
         ui1_i < (UINT8)(ACFG_CLR_GAIN_ELEM_NUM - ACFG_3D_CLR_GAIN_ELEM_NUM) /* Gain & Offset */;
         ui1_i++)
    {
        for(ui1_j = 0; ui1_j < 3 /*RGB*/; ui1_j++)
        {
            *(((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R + ui1_j].pt_def_value)+ui1_i)
                = (UINT8)aai2_clr_gain_value_0_def[ui4_gain_offset_id][ui1_i][ui1_j];
            *(((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R + ui1_j].pt_def_value)+ui1_i)
                = (UINT8)aai2_clr_offset_value_0_def[ui4_gain_offset_id][ui1_i][ui1_j];
        }
    }

    /* 3D Color gain/offset default value */
    for(;
         ui1_i < (UINT8)(ACFG_3D_CLR_GAIN_ELEM_NUM) /* Gain & Offset */;
         ui1_i++)
    {
        for(ui1_j = 0; ui1_j < 3 /*RGB*/; ui1_j++)
        {
            *(((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R + ui1_j].pt_def_value)+ui1_i)
                = (UINT8)aai2_3d_clr_gain_value_0_def[ui4_gain_offset_id][ui1_i][ui1_j];
            *(((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R + ui1_j].pt_def_value)+ui1_i)
                = (UINT8)aai2_3d_clr_offset_value_0_def[ui4_gain_offset_id][ui1_i][ui1_j];
        }
    }
#endif

    return APP_CFGR_OK;
}

#if 0 // For freesync cert:
    #define ACFG_FORCE_DEFAULT__BACKLIGHT       100 // Max
    #define ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL  0 // Off
    #define ACFG_FORCE_DEFAULT__LOCAL_DIMMING   0 // Off
#endif

#ifdef ACFG_NETFLIX_CERT_PATCH_PQ // For Netflix Cert:
    // File mode = off
    #define ACFG_FORCE_DEFAULT__FILM            0 // Off
    // Backlight control = off
    #define ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL  0 // Off
    // Local dimming = off
    #define ACFG_FORCE_DEFAULT__LOCAL_DIMMING   0 // Off
    // Picture mode
    #define ACFG_FORCE_DEFAULT__PICTURE_MODE_IDX  ACFG_CUST_PIC_MODE_BRIGHT_ROOM //Calibrated => ACFG_CUST_PIC_MODE_BRIGHT_ROOM
    // Black detail = OFF
    #define ACFG_FORCE_DEFAULT__BLACK_DETAIL    0 // Off
    // color/Saturation = 50
    #define ACFG_FORCE_DEFAULT__COLOR           50
    // Local contrast = OFF
    #define ACFG_FORCE_DEFAULT__LOCAL_CONTRAST  0 // Off
    // Judder Reduction
    #define ACFG_FORCE_DEFAULT__JUDDER_REDUCTION    0 // OFF
    // Motion Blur
    #define ACFG_FORCE_DEFAULT__MOTION_BLUR         0 // OFF
#endif

#ifdef ACFG_DV_CERT_PATCH_PQ // For DV Cert:
    // Judder Reduction
    #define ACFG_FORCE_DEFAULT__JUDDER_REDUCTION    0 // OFF
    // Motion Blur
    #define ACFG_FORCE_DEFAULT__MOTION_BLUR         0 // OFF
#endif


void acfg_cust_video_set_DefaultValue_PictureModeIdx(UINT8 u8PictureModeIdx)
{
    // APP_CFG_RECID_PIC_MODE  <==> IDX_PIC_MODE

    //DBG_LOG_PRINT(("[ACFG]{%s} picture_mode: IDX_MAX:%d, IDX_PIC_MODE:%d, \n",  __FUNCTION__, IDX_MAX, IDX_PIC_MODE));
    BUILD_ERROR_IF_TRUE( (IDX_PIC_MODE >= IDX_MAX) );

    if( IDX_PIC_MODE < IDX_MAX )
    {
        DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force picture_mode[0~%d] = %d\n",  __FUNCTION__, ACFG_PIC_MODE_ELEM_NUM, u8PictureModeIdx));
        if( at_acfg_descr[IDX_PIC_MODE].pt_def_value != NULL )
        {
            c_memset( at_acfg_descr[IDX_PIC_MODE].pt_def_value, u8PictureModeIdx, ACFG_PIC_MODE_ELEM_NUM );
        }
    }
}

void acfg_cust_video_set_DefaultValue_BlackDetail(UINT8 u8BlackDetail)
{
    // APP_CFG_RECID_VID_CONTRAST_EN <===> IDX_CUSTOM_CONTRAST_EN
    /* Contrast Enhancement /Adaptive Luma /Black Detail */  //0:off ; 1:low; 2:medim; 3:high
    // Use INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx);

    //DBG_LOG_PRINT(("[ACFG]{%s} Black_detail: IDX_MAX:%d, IDX_CUSTOM_CONTRAST_EN:%d, \n",  __FUNCTION__, IDX_MAX, IDX_CUSTOM_CONTRAST_EN));
    BUILD_ERROR_IF_TRUE( (IDX_CUSTOM_CONTRAST_EN >= IDX_MAX) );

    if( IDX_CUSTOM_CONTRAST_EN < IDX_MAX )
    {
        DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Black_Detail[0~%d]= %d\n",  __FUNCTION__, ACFG_PIC_QLT_ELEM_NUM, u8BlackDetail));
        if( at_acfg_descr[IDX_CUSTOM_CONTRAST_EN].pt_def_value != NULL )
        {
            c_memset( at_acfg_descr[IDX_CUSTOM_CONTRAST_EN].pt_def_value, u8BlackDetail, ACFG_PIC_QLT_ELEM_NUM );
        }
    }
}

void acfg_cust_video_set_DefaultValue_Color(UINT8 u8Color)
{
    // APP_CFG_RECID_VID_SAT  <==> IDX_VID_SAT
    // Use INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx);

    //DBG_LOG_PRINT(("[ACFG]{%s} COLOR: IDX_MAX:%d, IDX_VID_SAT:%d, \n",  __FUNCTION__, IDX_MAX, IDX_VID_SAT));
    BUILD_ERROR_IF_TRUE( (IDX_VID_SAT >= IDX_MAX) );

    if( IDX_VID_SAT < IDX_MAX )
    {
        DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Color[0~%d]= %d\n",  __FUNCTION__, ACFG_PIC_QLT_ELEM_NUM, u8Color));
        if( at_acfg_descr[IDX_VID_SAT].pt_def_value != NULL )
        {
            c_memset( at_acfg_descr[IDX_VID_SAT].pt_def_value, u8Color, ACFG_PIC_QLT_ELEM_NUM );
        }
    }
}

void acfg_cust_video_set_DefaultValue_LocalContrast(UINT8 u8LocalContrast)
{
    // APP_CFG_RECID_VID_LOCAL_CONTRAST <===> IDX_VID_LOCAL_CONTRAST  // /* Local Contrast */  //0:off ; 1:low; 2:medim; 3:high
    // Use INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx);

    //DBG_LOG_PRINT(("[ACFG]{%s} Local_Contrast: IDX_MAX:%d, IDX_VID_LOCAL_CONTRAST:%d, \n",  __FUNCTION__, IDX_MAX, IDX_VID_LOCAL_CONTRAST));
    BUILD_ERROR_IF_TRUE( (IDX_VID_LOCAL_CONTRAST >= IDX_MAX) );

    if( IDX_VID_LOCAL_CONTRAST < IDX_MAX )
    {
        DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Local_Contrast[0~%d]= %d\n",  __FUNCTION__, ACFG_PIC_QLT_ELEM_NUM, u8LocalContrast));
        if( at_acfg_descr[IDX_VID_LOCAL_CONTRAST].pt_def_value != NULL )
        {
            c_memset( at_acfg_descr[IDX_VID_LOCAL_CONTRAST].pt_def_value, u8LocalContrast, ACFG_PIC_QLT_ELEM_NUM );
        }
    }
}

void acfg_cust_video_set_DefaultValue_JudderReduction(UINT8 u8JudderReduction)
{
    // Force judder_reduction default value ...
    // IDX_CUSTOM_JUDDER_REDUCTION /* Judder Reduction */  // 0 ~ 10
    // IDX_CUSTOM_JUDDER_REDUCTION <==> APP_CFG_RECID_VID_JUDDER_REDUCTION
    // Use INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx);

    //DBG_LOG_PRINT(("[ACFG]{%s} JUDDER_REDUCTION: IDX_MAX:%d, IDX_CUSTOM_JUDDER_REDUCTION:%d, \n",  __FUNCTION__, IDX_MAX, IDX_CUSTOM_JUDDER_REDUCTION));
    BUILD_ERROR_IF_TRUE( (IDX_CUSTOM_JUDDER_REDUCTION >= IDX_MAX) );

    if( IDX_CUSTOM_JUDDER_REDUCTION < IDX_MAX )
    {
        DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Judder_Reduction[0~%d]= %d\n",  __FUNCTION__, ACFG_PIC_QLT_ELEM_NUM, u8JudderReduction));
        if( at_acfg_descr[IDX_CUSTOM_JUDDER_REDUCTION].pt_def_value != NULL )
        {
            c_memset( at_acfg_descr[IDX_CUSTOM_JUDDER_REDUCTION].pt_def_value, u8JudderReduction, ACFG_PIC_QLT_ELEM_NUM );
        }
    }
}

void acfg_cust_video_set_DefaultValue_MotionBlur(UINT8 u8MotionBlur)
{
    // Force Motion_Blur default value ...
    // IDX_CUSTOM_MOTION_BLUR_REDUCTION /* Motion Blur Reduction */  // 0: 0 ~ 10
    // IDX_CUSTOM_MOTION_BLUR_REDUCTION <==> APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION
    // Use INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx);

    //DBG_LOG_PRINT(("[ACFG]{%s} MOTION_BLUR: IDX_MAX:%d, IDX_CUSTOM_MOTION_BLUR_REDUCTION:%d, \n",  __FUNCTION__, IDX_MAX, IDX_CUSTOM_MOTION_BLUR_REDUCTION));
    BUILD_ERROR_IF_TRUE( (IDX_CUSTOM_MOTION_BLUR_REDUCTION >= IDX_MAX) );

    if( IDX_CUSTOM_MOTION_BLUR_REDUCTION < IDX_MAX )
    {
        DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Motion_Blur[0~%d]= %d\n",  __FUNCTION__, ACFG_PIC_QLT_ELEM_NUM, u8MotionBlur));
        if( at_acfg_descr[IDX_CUSTOM_MOTION_BLUR_REDUCTION].pt_def_value != NULL )
        {
            c_memset( at_acfg_descr[IDX_CUSTOM_MOTION_BLUR_REDUCTION].pt_def_value, u8MotionBlur, ACFG_PIC_QLT_ELEM_NUM );
        }
    }
}

static INT32 _acfg_cust_video_init_common_field_def_value(VOID)
{
    UINT16  ui2_ipt_idx        = 0;
    UINT16  ui2_pic_idx        = 0;
    UINT16  ui2_idx            = 0;


    DBG_LOG_PRINT(("[ACFG][default]{%s,%d} \n",  __FUNCTION__, __LINE__ ));

    /* overwrite the pq settings default*/
#if 0
    // ACFG_INPUT_SRC_NUM = 10 + 1
    for (ui2_ipt_idx = 0; ui2_ipt_idx < ACFG_INPUT_SRC_NUM; ui2_ipt_idx ++) // 0 ~ 10
    {
        for (ui2_pic_idx = 0; ui2_pic_idx < ACFG_PIC_MODE_NUM; ui2_pic_idx ++)
        {
            /*calculate the index*/
            ui2_idx = ui2_ipt_idx*ACFG_PIC_MODE_NUM + ui2_pic_idx;

            if((ui2_ipt_idx >= ACFG_INPUT_SRC_NUM) &&
                ((ui2_pic_idx == 1)||(ui2_pic_idx == 2)))
            {
                *(((UINT8*)at_acfg_descr[IDX_VID_DI_FILM_MODE].pt_def_value)+ui2_idx)= (UINT8)0;
            }
            else
            {
                *(((UINT8*)at_acfg_descr[IDX_VID_DI_FILM_MODE].pt_def_value)+ui2_idx)= (UINT8)ACFG_CUST_DI_FILM_MODE_AUTO;
            }
        }
    }
#endif


    // Force picture_mode default value ...
#ifdef ACFG_FORCE_DEFAULT__PICTURE_MODE_IDX
    acfg_cust_video_set_DefaultValue_PictureModeIdx(ACFG_FORCE_DEFAULT__PICTURE_MODE_IDX);
#endif

    // Force Black detail ...
#ifdef ACFG_FORCE_DEFAULT__BLACK_DETAIL
    acfg_cust_video_set_DefaultValue_BlackDetail(ACFG_FORCE_DEFAULT__BLACK_DETAIL);
#endif

    // Force color default value ...
#ifdef ACFG_FORCE_DEFAULT__COLOR
    acfg_cust_video_set_DefaultValue_Color(ACFG_FORCE_DEFAULT__COLOR);
#endif

    // Force Local contrast ...
#ifdef ACFG_FORCE_DEFAULT__LOCAL_CONTRAST
    acfg_cust_video_set_DefaultValue_LocalContrast(ACFG_FORCE_DEFAULT__LOCAL_CONTRAST);
#endif

    // Force judder_reduction default value ...
#ifdef ACFG_FORCE_DEFAULT__JUDDER_REDUCTION
    acfg_cust_video_set_DefaultValue_JudderReduction(ACFG_FORCE_DEFAULT__JUDDER_REDUCTION);
#endif

    // Force Motion_Blur default value ...
#ifdef ACFG_FORCE_DEFAULT__MOTION_BLUR
    acfg_cust_video_set_DefaultValue_MotionBlur(ACFG_FORCE_DEFAULT__MOTION_BLUR);
#endif


    /* overwrite some settings default for cert */
    // ACFG_INPUT_SRC_NUM = 10 + 1,
    // ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM = 15
    // Input src: Total= 11 + 15 = 26
    //
    // ACFG_PIC_MODE_NUM = (ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM)= 6+8=14
    // #define ACFG_PRE_SET_PIC_MODE_NUM   (6)
    // #define ACFG_CUST_SET_PIC_MODE_NUM  (8)
    //
    //#define ACFG_PIC_QLT_ELEM_NUM       ((ACFG_INPUT_SRC_NUM + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM)* ACFG_PIC_MODE_NUM)
    // => (11+15)*14=364
    UINT16 u16SrcNum = (ACFG_INPUT_SRC_NUM + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM);
    UINT16 u16PicNum = ACFG_PIC_MODE_NUM;
    UINT16 u16Total = u16SrcNum * u16PicNum;

    DBG_LOG_PRINT(("[ACFG]{%s} u16SrcNum:%d, u16PicNum:%d, u16Total:%d\n",  __FUNCTION__, u16SrcNum, u16PicNum, u16Total));

#ifdef ACFG_FORCE_DEFAULT__BACKLIGHT // IDX_DISP_BACK_LIGHT <==> APP_CFG_RECID_DISP_BACK_LIGHT
    DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Backlight[0~%d]= %d\n",  __FUNCTION__, u16Total, ACFG_FORCE_DEFAULT__BACKLIGHT));
#endif

#ifdef ACFG_FORCE_DEFAULT__LOCAL_DIMMING // IDX_CUSTOM_DIMMING <==> APP_CFG_RECID_VID_CUSTOM_DIMMING
    DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force LocalDimming[0~%d]= %d\n",  __FUNCTION__, u16Total, ACFG_FORCE_DEFAULT__LOCAL_DIMMING));
#endif

#ifdef ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL // IDX_CUSTOM_DCR_IDX <==> APP_CFG_RECID_VID_CUSTOM_DCR
    DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force BacklightCtrl[0~%d]= %d\n",  __FUNCTION__, u16Total, ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL));
#endif

#ifdef ACFG_FORCE_DEFAULT__FILM // IDX_VID_DI_FILM_MODE <==> APP_CFG_RECID_VID_DI_FILM_MODE
    DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force FILM[0~%d]= %d\n",  __FUNCTION__, u16Total, ACFG_FORCE_DEFAULT__FILM));
#endif

    for (ui2_ipt_idx = 0; ui2_ipt_idx < (ACFG_INPUT_SRC_NUM + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM); ui2_ipt_idx ++) // From 0 ~ 25
    {
        for (ui2_pic_idx = 0; ui2_pic_idx < ACFG_PIC_MODE_NUM; ui2_pic_idx ++) // From 0 ~ 13
        {
            /*calculate the index*/
            ui2_idx = ui2_ipt_idx*ACFG_PIC_MODE_NUM + ui2_pic_idx; // From 0 ~ 363

        #ifdef ACFG_FORCE_DEFAULT__BACKLIGHT // IDX_DISP_BACK_LIGHT <==> APP_CFG_RECID_DISP_BACK_LIGHT
            //DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force Backlight[%d]= %d\n",  __FUNCTION__, ui2_idx, ACFG_FORCE_DEFAULT__BACKLIGHT));
            *(((UINT8*)at_acfg_descr[IDX_DISP_BACK_LIGHT].pt_def_value)+ui2_idx)= (UINT8)ACFG_FORCE_DEFAULT__BACKLIGHT;
        #endif

        #ifdef ACFG_FORCE_DEFAULT__LOCAL_DIMMING // IDX_CUSTOM_DIMMING <==> APP_CFG_RECID_VID_CUSTOM_DIMMING
            //DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force LocalDimming[%d]= %d\n",  __FUNCTION__, ui2_idx, ACFG_FORCE_DEFAULT__LOCAL_DIMMING));
            *(((UINT8*)at_acfg_descr[IDX_CUSTOM_DIMMING ].pt_def_value)+ui2_idx)= (UINT8)ACFG_FORCE_DEFAULT__LOCAL_DIMMING;
        #endif

        #ifdef ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL // IDX_CUSTOM_DCR_IDX <==> APP_CFG_RECID_VID_CUSTOM_DCR
            //DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force BacklightCtrl[%d]= %d\n",  __FUNCTION__, ui2_idx, ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL));
            *(((UINT8*)at_acfg_descr[IDX_CUSTOM_DCR_IDX].pt_def_value)+ui2_idx)= (UINT8)ACFG_FORCE_DEFAULT__BACKLIGHT_CTRL;
        #endif
#if 0
        #ifdef ACFG_FORCE_DEFAULT__FILM // IDX_VID_DI_FILM_MODE <==> APP_CFG_RECID_VID_DI_FILM_MODE
            //DBG_LOG_PRINT(("[TEST][ACFG]{%s} Force FILM[%d]= %d\n",  __FUNCTION__, ui2_idx, ACFG_FORCE_DEFAULT__FILM));
            *(((UINT8*)at_acfg_descr[IDX_VID_DI_FILM_MODE].pt_def_value)+ui2_idx)= (UINT8)ACFG_FORCE_DEFAULT__FILM;
        #endif
#endif
        }
    }


#if (0)
    for (ui2_ipt_idx = 0; ui2_ipt_idx < (ACFG_INPUT_SRC_NUM + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM); ui2_ipt_idx ++)
    {
        for (ui2_pic_idx = 0; ui2_pic_idx < ACFG_PIC_MODE_NUM; ui2_pic_idx ++)
        {
            /*calculate the index*/
            ui2_idx = ui2_ipt_idx*ACFG_PIC_MODE_NUM + ui2_pic_idx;

            if( ((ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 2)||//HDMI1_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 5)||//HDMI2_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 8)||//HDMI3_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 11)||//HDMI4_DOLBY_VISION
                (ui2_ipt_idx == ACFG_INPUT_SRC_NUM + 14))//MMP_DOLBY_VISION
                &&((ui2_pic_idx == 1)||(ui2_pic_idx == 2)))
                /* for Dolby version picture mode Calibrated & Calibrated Dark backlight default will set to 50*/
            {
                *(((UINT8*)at_acfg_descr[IDX_DISP_BACK_LIGHT].pt_def_value)+ui2_idx)= (UINT8)50;
            }
            else if(ui2_ipt_idx >= ACFG_INPUT_SRC_NUM)  //for HDR or HLG the backlight will set to 100
            {
                *(((UINT8*)at_acfg_descr[IDX_DISP_BACK_LIGHT].pt_def_value)+ui2_idx)= (UINT8)100;
            }
        }
    }
#endif

    return APP_CFGR_OK;
}

static INT32 _a_cfg_update_all_hdmi_edid_version(VOID)
{
    UINT8 ui1_edid = 0;
    INT32 i4_ret = 0;

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} \n",
            __FUNCTION__, __LINE__ ));
    );

    for (UINT8 ui1_i = 0; ui1_i < 4; ui1_i++)
    {
        i4_ret = inp_lst_get_full_uhd_color_by_hdmi_idx(ui1_i, &ui1_edid);

        //DBG_LOG_PRINT(("-----------------baozi %s %d idx = %d, edid = %d\n",__FUNCTION__,__LINE__, ui1_i, ui1_edid));
        i4_ret = inp_lst_set_edid_by_port(ui1_i, ui1_edid,FALSE);
    }

    return i4_ret;
}

/* get the acture gain offset min & max for app set match*/
static INT32 _acfg_get_acture_clr_gain_offset_minmax(
    UINT16   ui2_cfg_rec,
    INT16*   pi2_odm_min,
    INT16*   pi2_odm_max)
{
    INT16   i2_fac_val = 0;
    switch (ui2_cfg_rec)
    {
        case APP_CFG_RECID_CLR_GAIN_R:
            {
                a_cfg_av_get((UINT16)CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_fac_val);
                DBG_INFO(("\n%s,%d,i2_fac_val %d\n",__FUNCTION__,__LINE__,i2_fac_val));
                acfg_fac_rgb_value_mapping(&i2_fac_val);
                DBG_INFO(("\n%s,%d,i2_fac_val %d,ACFG_MTK_CLR_RGB_MAX_VALUE  %d,ACFG_MTK_CLR_RGB_MIN_VALUE %d\n",
                    __FUNCTION__,__LINE__,i2_fac_val,ACFG_MTK_CLR_RGB_MAX_VALUE,ACFG_MTK_CLR_RGB_MIN_VALUE));
                if ((i2_fac_val- ACFG_MTK_CLR_RGB_MIN_VALUE) > (ACFG_MTK_CLR_RGB_MAX_VALUE - ACFG_MTK_CLR_RGB_MIN_VALUE)/2)
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MAX_VALUE;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MAX_VALUE - (ACFG_MTK_CLR_RGB_MAX_VALUE - i2_fac_val)*2;
                }
                else
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MIN_VALUE + (i2_fac_val - ACFG_MTK_CLR_RGB_MIN_VALUE)*2;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MIN_VALUE;
                }
            }
            break;

        case APP_CFG_RECID_CLR_GAIN_G:
            {
                a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_fac_val);
                DBG_INFO(("\n%s,%d,i2_fac_val %d\n",__FUNCTION__,__LINE__,i2_fac_val));
                acfg_fac_rgb_value_mapping(&i2_fac_val);
                DBG_INFO(("\n%s,%d,i2_fac_val %d,ACFG_MTK_CLR_RGB_MAX_VALUE  %d,ACFG_MTK_CLR_RGB_MIN_VALUE %d\n",
                                        __FUNCTION__,__LINE__,i2_fac_val,ACFG_MTK_CLR_RGB_MAX_VALUE,ACFG_MTK_CLR_RGB_MIN_VALUE));
                if ((i2_fac_val- ACFG_MTK_CLR_RGB_MIN_VALUE) > (ACFG_MTK_CLR_RGB_MAX_VALUE - ACFG_MTK_CLR_RGB_MIN_VALUE)/2)
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MAX_VALUE;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MAX_VALUE - (ACFG_MTK_CLR_RGB_MAX_VALUE - i2_fac_val)*2;
                }
                else
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MIN_VALUE + (i2_fac_val - ACFG_MTK_CLR_RGB_MIN_VALUE)*2;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MIN_VALUE;
                }
             }
            break;
        case APP_CFG_RECID_CLR_GAIN_B:
            {

                a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_fac_val);
                DBG_INFO(("\n%s,%d,i2_fac_val %d\n",__FUNCTION__,__LINE__,i2_fac_val));
                acfg_fac_rgb_value_mapping(&i2_fac_val);
                DBG_INFO(("\n%s,%d,i2_fac_val %d,ACFG_MTK_CLR_RGB_MAX_VALUE  %d,ACFG_MTK_CLR_RGB_MIN_VALUE %d\n",
                                        __FUNCTION__,__LINE__,i2_fac_val,ACFG_MTK_CLR_RGB_MAX_VALUE,ACFG_MTK_CLR_RGB_MIN_VALUE));
                if ((i2_fac_val- ACFG_MTK_CLR_RGB_MIN_VALUE) > (ACFG_MTK_CLR_RGB_MAX_VALUE - ACFG_MTK_CLR_RGB_MIN_VALUE)/2)
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MAX_VALUE;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MAX_VALUE - (ACFG_MTK_CLR_RGB_MAX_VALUE - i2_fac_val)*2;
                }
                else
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MIN_VALUE + (i2_fac_val - ACFG_MTK_CLR_RGB_MIN_VALUE)*2;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MIN_VALUE;
                }
            }
            break;

        case APP_CFG_RECID_CLR_OFFSET_R:
            {

                a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_fac_val);
                acfg_fac_rgb_value_mapping(&i2_fac_val);
                if ((i2_fac_val- ACFG_MTK_CLR_RGB_MIN_VALUE) > (ACFG_MTK_CLR_RGB_MAX_VALUE - ACFG_MTK_CLR_RGB_MIN_VALUE)/2)
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MAX_VALUE;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MAX_VALUE - (ACFG_MTK_CLR_RGB_MAX_VALUE - i2_fac_val)*2;
                }
                else
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MIN_VALUE + (i2_fac_val - ACFG_MTK_CLR_RGB_MIN_VALUE)*2;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MIN_VALUE;
                }
            }
            break;

        case APP_CFG_RECID_CLR_OFFSET_G:
            {
                a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_fac_val);
                acfg_fac_rgb_value_mapping(&i2_fac_val);
                if ((i2_fac_val- ACFG_MTK_CLR_RGB_MIN_VALUE) > (ACFG_MTK_CLR_RGB_MAX_VALUE - ACFG_MTK_CLR_RGB_MIN_VALUE)/2)
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MAX_VALUE;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MAX_VALUE - (ACFG_MTK_CLR_RGB_MAX_VALUE - i2_fac_val)*2;
                }
                else
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MIN_VALUE + (i2_fac_val - ACFG_MTK_CLR_RGB_MIN_VALUE)*2;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MIN_VALUE;
                }
            }
            break;
        case APP_CFG_RECID_CLR_OFFSET_B:
            {
                a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_fac_val);
                acfg_fac_rgb_value_mapping(&i2_fac_val);
                if ((i2_fac_val- ACFG_MTK_CLR_RGB_MIN_VALUE) > (ACFG_MTK_CLR_RGB_MAX_VALUE - ACFG_MTK_CLR_RGB_MIN_VALUE)/2)
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MAX_VALUE;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MAX_VALUE - (ACFG_MTK_CLR_RGB_MAX_VALUE - i2_fac_val)*2;
                }
                else
                {
                    *pi2_odm_max = ACFG_MTK_CLR_RGB_MIN_VALUE + (i2_fac_val - ACFG_MTK_CLR_RGB_MIN_VALUE)*2;
                    *pi2_odm_min = ACFG_MTK_CLR_RGB_MIN_VALUE;
                }
            }
            break;
    }
    return APP_CFGR_OK;
}

INT32 acfg_cust_video_update_pq_def_from_odm(VOID)
{
    INT32 i4_ret = 0;
    UINT8  ui1_odm_id = 0;


    DBG_LOG_PRINT(("[ACFG][NR][default]{%s,%d}\n", __FUNCTION__,__LINE__ ));


    i4_ret = a_cfg_custom_get_odm_idx(&ui1_odm_id);
    if (APP_CFGR_OK == i4_ret)
    {
        if ((ui1_odm_id == 2) || (ui1_odm_id == 4))
        {
            DBG_LOG_PRINT(("\n[ACFG]_acfg_cust_video_def_value_0_overwrite_color_gain_offset_def\n"));
            _acfg_cust_video_def_value_0_overwrite_color_gain_offset_def();
        }
    }
    DBG_LOG_PRINT(("\n %s,odm_idx = %d\n",__FUNCTION__,ui1_odm_id));

    ACFG_DEBUG_NR_DEFAULT(
        DBG_LOG_PRINT(("[ACFG][NR][default]{%s,%d} at_acfg_descr[IDX_VID_NR].pt_def_value=0x%X, z_def_size:%d \n",
            __FUNCTION__,__LINE__, (UINT32)at_acfg_descr[IDX_VID_NR].pt_def_value, at_acfg_descr[IDX_VID_NR].z_def_size));
    );

    ACFG_DEBUG_NR_DEFAULT(
        acfg_cust_video_print_setting_data_u8_all(
            (UINT8*)at_acfg_descr[IDX_VID_NR].pt_def_value, at_acfg_descr[IDX_VID_NR].z_def_size, 0, 0 );
    );

    /* Overwrite PQ default values. */
    acfg_cust_odm_overwrite_pq_default();

    ACFG_DEBUG_NR_DEFAULT(
        DBG_LOG_PRINT(("[ACFG][NR][default]{%s,%d} at_acfg_descr[IDX_VID_NR].pt_def_value=0x%X, z_def_size:%d \n",
            __FUNCTION__,__LINE__, (UINT32)at_acfg_descr[IDX_VID_NR].pt_def_value, at_acfg_descr[IDX_VID_NR].z_def_size));
    );

    ACFG_DEBUG_NR_DEFAULT(
        acfg_cust_video_print_setting_data_u8_all(
            (UINT8*)at_acfg_descr[IDX_VID_NR].pt_def_value, at_acfg_descr[IDX_VID_NR].z_def_size, 0, 0 );
    );

    a_gluelayer_update_default_pq_tbl();

    acfg_cust_overwrite_hlg_hdr_dover_pq_default();//over write HDR HLG dobly version table

    if(ui1_odm_id == 0 || ui1_odm_id == 1 ||  ui1_odm_id == 2 || ui1_odm_id == 3 || ui1_odm_id == 4 || ui1_odm_id == 5 || ui1_odm_id == 6)//Need check ODM index
    {
        a_gluelayer_get_new_table_default_pq_tbl();
    }

    acfg_cust_hdr_hlg_dover_table_default();

    _acfg_cust_video_def_value_append_patch();

    return APP_CFGR_OK;

}
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_pre_init
 *
 * Description:
 *      Pre initialiation. You can do following thing here:
 *  1. Override the default value
 *  2. Put some config in EEPROM
 *  3. Remove some configs by setting them as b_enable=FALSE
 *  4. Change the value in at_acfg_descr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_video_pre_init(VOID)
{
    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ================================ start \n", __FILE__, __FUNCTION__, __LINE__ ));

    _acfg_cust_video_init_def_value();

    DBG_LOG_PRINT(("\nacfg_cust_video_pre_init(1) pqid\n"));

    /* screen mode & h v position related */
    DECLARE_FIELD(IDX_SCR_MODE,                 APP_CFG_GRPID_VIDEO,  APP_CFG_RECID_SCREEN_MODE,
                  CFG_8BIT_T,                   ACFG_SCR_MODE_ELEM_NUM,         aui1_cust_scr_mod_def,      ACFG_SCR_MODE_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_H_SIZE,            APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE,
                  CFG_8BIT_T,                   ACFG_CUSTOM_H_SIZE_ELEM_NUM,   aui1_h_size_def,      ACFG_CUSTOM_H_SIZE_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_V_SIZE,            APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE,
                  CFG_8BIT_T,                          ACFG_CUSTOM_V_SIZE_ELEM_NUM,   aui1_v_size_def,      ACFG_CUSTOM_V_SIZE_ELEM_NUM,
                  NULL,                                NULL,       ACFG_ACCESS_PUBLIC);

    /* pq setting related*/
    DECLARE_FIELD(IDX_CUSTOM_DCR_IDX,           APP_CFG_GRPID_VIDEO,      APP_CFG_RECID_VID_CUSTOM_DCR,
                  CFG_8BIT_T,                   ACFG_PIC_QLT_ELEM_NUM,    aui1_dcr_def,                  ACFG_PIC_QLT_ELEM_NUM,
                  NULL,                         NULL,                     ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_LIGHT_SENSOR_IDX,  APP_CFG_GRPID_VIDEO,       APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR,
                  CFG_8BIT_T,                   ACFG_PIC_QLT_ELEM_NUM,          aui1_light_sensor_def,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_DIMMING,           APP_CFG_GRPID_VIDEO,      APP_CFG_RECID_VID_CUSTOM_DIMMING,
                  CFG_8BIT_T,                   ACFG_PIC_QLT_ELEM_NUM,          aui1_dimming_onoff,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_VID_MJC_EFFECT,           APP_CFG_GRPID_VIDEO,        APP_CFG_RECID_VID_MJC_EFFECT,
                  CFG_8BIT_T,                   ACFG_PIC_QLT_ELEM_NUM,          ui1_vid_mjc_effect_def,  ACFG_PIC_QLT_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_VID_MJC_MODE,             APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_MJC_MODE,
                  CFG_8BIT_T,                   ACFG_PIC_QLT_ELEM_NUM,         ui1_vid_mjc_mode_def,       ACFG_PIC_QLT_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* CUST pq setting related and the following settings default value will be 0*/
    DECLARE_FIELD(IDX_CLR_HUE_R,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_HUE_R,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_HUE_G,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_HUE_G,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_HUE_B,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_HUE_B,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_SAT_R,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_SAT_R,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_SAT_G,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_SAT_G,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_SAT_B,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_SAT_B,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_BRI_R,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_BRI_R,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_BRI_G,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_BRI_G,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_BRI_B,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_BRI_B,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_HUE_C,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_HUE_C,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_HUE_M,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_HUE_M,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_HUE_Y,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_HUE_Y,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_SAT_C,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_SAT_C,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_SAT_M,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_SAT_M,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_SAT_Y,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_SAT_Y,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_BRI_C,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_BRI_C,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_BRI_M,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_BRI_M,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_BRI_Y,                APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_BRI_Y,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_hrgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_REDUCE_BLUR,              APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_REDUCE_BLUR,
                  CFG_8BIT_T,                   ACFG_PIC_QLT_ELEM_NUM,         aui1_vid_reduce_blur_def,       ACFG_PIC_QLT_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* the vid rgb default value will be 1*/
    DECLARE_FIELD(IDX_RED,                      APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_RED,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_rgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_GREEN,                    APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_GREEN,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_rgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_BLUE,                     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_BLUE,
                  CFG_8BIT_T,                   APP_CFG_HRGB_ELEM_NUM,         aui1_vid_cust_rgb_def,       APP_CFG_HRGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /*cust clr gain offset RGB*/
    DECLARE_FIELD(IDX_CUST_CLR_GAIN_R,          APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_CLR_GAIN_R,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,         aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_CLR_GAIN_G,          APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_CLR_GAIN_G,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,         aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_CLR_GAIN_B,          APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_CLR_GAIN_B,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,         aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_CLR_OFFSET_R,        APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_CLR_OFFSET_R,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,         aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_CLR_OFFSET_G,        APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_CLR_OFFSET_G,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,         aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_CLR_OFFSET_B,        APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_CLR_OFFSET_B,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,         aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CLR_TEMP_CHG,             APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CLR_TEMP_CHG,
                  CFG_8BIT_T,                   APP_CFG_2_POINT_WB_ELEM_NUM,          aui1_vid_2_point_wb_def,       APP_CFG_2_POINT_WB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* 11 point*/
    DECLARE_FIELD(IDX_11_POINT_GAIN,            APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_11_POINT_GAIN,
                  CFG_8BIT_T,                   APP_CFG_11_POINT_GAIN_ELEM_NUM,  aui1_vid_11_point_gain_def,       APP_CFG_11_POINT_GAIN_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* 11 point RGB*/
    DECLARE_FIELD(IDX_11_POINT_GAIN_RED,              APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_11_POINT_GAIN_RED,
                  CFG_8BIT_T,                   APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM,         aui1_vid_11_point_gain_rgb_def,       APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_11_POINT_GAIN_GREEN,              APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_11_POINT_GAIN_GREEN,
                  CFG_8BIT_T,                   APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM,         aui1_vid_11_point_gain_rgb_def,       APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_11_POINT_GAIN_BLUE,              APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_11_POINT_GAIN_BLUE,
                  CFG_8BIT_T,                   APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM,         aui1_vid_11_point_gain_rgb_def,       APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* custom pic mode name*/
    DECLARE_FIELD(IDX_CUST_PIC_MODE_0_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_0_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_1_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_1_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_2_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_2_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_3_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_3_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_4_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_4_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_5_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_5_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_6_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_6_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUST_PIC_MODE_7_NAME,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_MODE_7_NAME,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,         ps_cust_pic_mode_name_def,       APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);
    /* cust pic mode exist status*/
    DECLARE_FIELD(IDX_CUST_PIC_EXIST_STATUS,    APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_EXIST_STUTAS_ELEM_NUM,         aui1_cust_pic_exist_status_def,       APP_CFG_CUST_PIC_EXIST_STUTAS_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);
    /*pwd lock status*/
    DECLARE_FIELD(IDX_CUST_PIC_LOCK_STATUS,     APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_LOCK_STATUS,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_LOCK_STUTAS_ELEM_NUM,         &ui1_cust_pic_lock_status_def,       APP_CFG_CUST_PIC_LOCK_STUTAS_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /*pic unlock pwd*/
    DECLARE_FIELD(IDX_CUST_PIC_LOCK_PWD,        APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_PIC_LOCK_PWD,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN,         s_pic_mode_unlock_pwd,       APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /*pre pic mode change status*/
    DECLARE_FIELD(IDX_PRE_PIC_CHG,              APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_PRE_PIC_CHG,
                  CFG_8BIT_T,                   ACFG_PRE_SET_PIC_MODE_CHG_ELEM_NUM,         s_pre_pic_mode_chg,       ACFG_PRE_SET_PIC_MODE_CHG_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* cust pic mode copy base*/
    DECLARE_FIELD(IDX_CUST_PIC_COPY_BASE,       APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_CUST_PIC_COPY_BASE,
                  CFG_8BIT_T,                   APP_CFG_CUST_PIC_EXIST_STUTAS_ELEM_NUM,         aui1_cust_pic_exist_status_def,       APP_CFG_CUST_PIC_EXIST_STUTAS_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* cust pic mode copy base*/
    DECLARE_FIELD(IDX_CUST_GAMMA,               APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_GAMMA,
                  CFG_8BIT_T,                   ACFG_VID_CUST_GAMMA_ELEM_NUM,         aui1_vid_cust_gamma,       ACFG_VID_CUST_GAMMA_ELEM_NUM,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    /* cust full color 444*/
    DECLARE_FIELD(IDX_CUSTOM_FULL_COLOR_444,               APP_CFG_GRPID_VIDEO,            APP_CFG_RECID_VID_CUST_FULL_COLOR_444,
                  CFG_8BIT_T,                   ACFG_VID_CUST_FULL_COLOR_444,         &ui1_vid_cust_full_color_444,       ACFG_VID_CUST_FULL_COLOR_444,
                  NULL,                         NULL,       ACFG_ACCESS_PUBLIC);

    _a_cfg_update_all_hdmi_edid_version();

/*
*  as the eep have not been init ready, here should not do the updater
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    */

    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ------------------------------- end \n", __FILE__, __FUNCTION__, __LINE__ ));

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_post_init
 *
 * Description:
 *      Post initialiation. You can do following thing here:
 *  1. Update the middleware component in accordance with config value.
 *  2. Always set a config to a specific value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_video_post_init(VOID)
{
    /* Defined in sys_asp_ratio.c */
    extern INT32 sys_init_disp_fmt_tbl (VOID* pv_acfg_data, UINT32 ui4_data_len);

    INT32       i4_ret;
    SIZE_T      z_size;
    UINT8       aui1_scr_modes [ACFG_SCR_MODE_ELEM_NUM];


    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ================================ start \n", __FILE__, __FUNCTION__, __LINE__ ));


    /* Set the values of display format to the table in sys_build */
    i4_ret = acfg_get(IDX_SCR_MODE, aui1_scr_modes, &z_size);
    ACFG_LOG_ON_FAIL(i4_ret);
    if(i4_ret == APP_CFGR_OK)
    {
        i4_ret = sys_init_disp_fmt_tbl ((VOID*)aui1_scr_modes, sizeof (aui1_scr_modes));
        ACFG_LOG_ON_FAIL(i4_ret);
    }


    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} call a_cfg_av_update(VRR)\n",
            __FUNCTION__, __LINE__ ));
    );

#if( ACFG_CUST_VRR_SET_DRIVER_BY_PORT )
    g_ai16_vrr_last[0] = VRR_INIT_VAL;
    g_ai16_vrr_last[1] = VRR_INIT_VAL;
    g_ai16_vrr_last[2] = VRR_INIT_VAL;
    g_ai16_vrr_last[3] = VRR_INIT_VAL;
#else
    i2_g_vrr_set = VRR_INIT_VAL;
#endif

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE));
    ACFG_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} call _a_cfg_update_all_hdmi_edid_version()\n",
            __FUNCTION__, __LINE__ ));
    );

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444));
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Update the PQ */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Update Overscan */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    ACFG_LOG_ON_FAIL(i4_ret);

    //i2_g_vrr_set = VRR_INIT_VAL;
    //i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE));
    //ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OLED_PIXEL_SHIFT));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_ETOF));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FILM_MAEKER_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

//    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444));
  //  ACFG_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ------------------------------- end \n", __FILE__, __FUNCTION__, __LINE__ ));

    return APP_CFGR_OK;
}

#ifdef APP_ODM_ONE_IMG_SUPPORT
static INT32 _acfg_cust_video_get_elem_idx_for_fac(
                UINT16          ui2_id,
                UINT8           ui1_input_src,
                UINT16*         pui2_idx
                )
{
    INT32 i4_ret = APP_CFGR_OK;
    UINT16  ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16  ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (a_app_cfg_fac_clr_temp())
    {
        switch (ui2_cfg_grp)
        {
            case APP_CFG_GRPID_VIDEO:
            {
                if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_R
                    || ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_G
                    || ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_B
                    || ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_R
                    || ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_G
                    || ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_B)
                {
                    INT16   i2_clr_tmp = 0;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);
                    switch ((UINT16)i2_clr_tmp)
                    {
                        case 0:
                        {
                            *pui2_idx = ACFG_CUST_CLR_TEMP_WARM;
                        }
                        break;
                        case 1:
                        {
                            *pui2_idx = ACFG_CUST_CLR_TEMP_COOL;
                        }
                        break;
                        case 2:
                        {
                            *pui2_idx = ACFG_CUST_CLR_TEMP_NORMAL;
                        }
                        break;
                        default:
                            *pui2_idx = ACFG_CUST_CLR_TEMP_WARM;
                            break;
                    }
                }
            }
            default:
                break;
        }
    }
    return i4_ret;
}
#endif
/*----------------------------------------------------------------------------
 * Name: acfg_cust_video_is_special_item
 *
 * Description: This function is used for the data store in eeprom by input source * picture mode * dynamic range
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
BOOL acfg_cust_video_is_special_item(UINT16          ui2_id)
{
    BOOL                        b_type = TRUE;

    do
    {
        if(ui2_id == IDX_CUSTOM_GAME_LOW_LATENCY )
        {
            b_type = FALSE;
            break;
        }

        if(ui2_id == IDX_CUSTOM_GAME_HDR )
        {
            b_type = FALSE;
            break;
        }

        if(ui2_id == IDX_CUSTOM_VARIABLE_REFRESH_RATE )
        {
            b_type = FALSE;
            break;
        }


    }while(0);

    return b_type;
}
/*----------------------------------------------------------------------------
 * Name: acfg_cust_video_get_special_item_idx => acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode
 *
 * Description: This function is used for the data store in eeprom by input source * picture mode * dynamic range
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
#define ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR   (APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + 1)

//INT32 acfg_cust_video_get_special_item_idx(UINT8  ui1_input_src, UINT16*  pui2_idx)
INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx)
{
    INT32                       i4_ret = APP_CFGR_OK;
    ISL_REC_T                   t_isl_rec;
    UINT16                      ui2_ipt = 0;
    INT16                       i2_pic_mode = 0;
    UINT8                       ui1_video_type = 0;


#if( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
    if( u16RecId == g_AcfgCust_u16DebugID_CalOffset )
    {
        DBG_LOG_PRINT(("[ACFG]{%s: %d} (id:0x%X, input_src:%d)\n", __FUNCTION__,__LINE__, u16RecId, ui1_input_src ));

// #define VTRL_3D_ELEMENT             (1)
// #define ACFG_INPUT_SRC_NUM          (ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT) ==> 11
        //DBG_LOG_PRINT(("[ACFG] ACFG_CUST_INPUT_GRP_MAX:%d, ACFG_INPUT_SRC_NUM:%d\n", ACFG_CUST_INPUT_GRP_MAX, ACFG_INPUT_SRC_NUM  ));

    // APP_CFG_DYNAMIC_RANGE_NUM = 4
    // ACFG_PRE_SET_PIC_MODE_NUM = 6
    //#define APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC  (ACFG_INPUT_SRC_NUM * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM) ==> 264
        //DBG_LOG_PRINT(("[ACFG] APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC:%d\n", APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC ));
    }
#endif


    c_memset (&t_isl_rec, 0, sizeof (ISL_REC_T));

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);
    ui2_ipt = _get_input_grp(&t_isl_rec);

    // Check ui2_ipt: 0 ~ 10
    if( ui2_ipt >= ACFG_INPUT_SRC_NUM )
    {
        DBG_LOG_PRINT(("[ACFG]{%s: %d} Error: Invalid input_grp(%d)!! (input_src:%d) => Force return %d\n", __FUNCTION__,__LINE__, ui2_ipt, ui1_input_src, ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR ));
        return ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR;
    }


    /* Get video type */
    ui1_video_type = a_acfg_cust_get_dynamic_range();
    // ui1_video_type range: 0 ~ 3


    /* Get picture mode */
    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
    if( (i4_ret != APP_CFGR_OK) )
    {
        DBG_LOG_PRINT(("[ACFG]{%s: %d} (input_src:%d) Error: Get pic_mode fail(ret:%d)!! => Force return %d\n", __FUNCTION__,__LINE__,
                                        ui1_input_src, i4_ret, ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR ));
        return ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR;
    }

    // (0~5) is for pre-set picture mode, (6~11) is for custom picture_mode(Save Picture mode)
    if( (i2_pic_mode < 0)
      ||(i2_pic_mode > 11)
      )
    {
        DBG_LOG_PRINT(("[ACFG]{%s: %d} (input_src:%d) Error: Invalid i2_pic_mode(%d)!! => Force return %d\n", __FUNCTION__,__LINE__,
                                        ui1_input_src, i2_pic_mode, ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR ));
        return ACFG_CUST_SPECIAL_IDX_OFFET_FOR_ERROR;
    }


    if(i2_pic_mode <  ACFG_PRE_SET_PIC_MODE_NUM) // 0 ~ 5
    {
        *pui2_idx = (ui2_ipt * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM)
                  + (ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM)
                  + i2_pic_mode;

    #if( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
        if( u16RecId == g_AcfgCust_u16DebugID_CalOffset )
        {
            DBG_LOG_PRINT(("[ACFG]{%s: %d} (id:0x%X) ui2_ipt:%d, ui1_video_type:%d, i2_pic_mode:%d  => %d\n", __FUNCTION__,__LINE__,
                u16RecId, ui2_ipt, ui1_video_type, i2_pic_mode, *pui2_idx ));
        }
    #endif
    }
    else // only for i2_pic_mode = 6 ~ 11
    {
        //i2_pic_mode = i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;
        UINT16 u16PicMode_Tmp = i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;

    #if(ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE)
        *pui2_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (ui1_video_type * ACFG_CUST_SET_PIC_MODE_NUM) + u16PicMode_Tmp;
    #else
        *pui2_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (0              * ACFG_CUST_SET_PIC_MODE_NUM) + u16PicMode_Tmp;
    #endif

    #if( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
        if( u16RecId == g_AcfgCust_u16DebugID_CalOffset )
        {
            DBG_LOG_PRINT(("[ACFG]{%s: %d} (id:0x%X) i2_pic_mode:%d ==> %d\n", __FUNCTION__,__LINE__, u16RecId, i2_pic_mode, *pui2_idx ));
        }
    #endif
    }

   return APP_CFGR_OK;

}

INT32 acfg_cust_video_get_DataOffset_By_Src_HdrType_PicMode( UINT8 u8SrcIdx, UINT8 u8DHR_type, UINT8 u8PicMode )
{
    INT32 i32_offset = -1;


    if(u8PicMode <  ACFG_PRE_SET_PIC_MODE_NUM) // 0 ~ 5
    {
        i32_offset = (u8SrcIdx   * ACFG_PRE_SET_PIC_MODE_NUM * APP_CFG_DYNAMIC_RANGE_NUM)
                   + (u8DHR_type * ACFG_PRE_SET_PIC_MODE_NUM)
                   + u8PicMode;

#if 0//( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
        if( u16RecId == g_AcfgCust_u16DebugID_CalOffset )
        {
            DBG_LOG_PRINT(("[ACFG]{%s: %d} (id:0x%X) ui2_ipt:%d, ui1_video_type:%d, i2_pic_mode:%d  => %d\n", __FUNCTION__,__LINE__,
                u16RecId, ui2_ipt, ui1_video_type, i2_pic_mode, *pui2_idx ));
        }
#endif
    }
    else // only for i2_pic_mode = 6 ~ 11
    {
        //i2_pic_mode = i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;
        UINT16 u16PicMode_Tmp = u8PicMode - ACFG_PRE_SET_PIC_MODE_NUM;

    #if(ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE)
        i32_offset = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (u8DHR_type * ACFG_CUST_SET_PIC_MODE_NUM) + u16PicMode_Tmp;
    #else
        i32_offset = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (0          * ACFG_CUST_SET_PIC_MODE_NUM) + u16PicMode_Tmp;
    #endif

    #if 0//( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
        if( u16RecId == g_AcfgCust_u16DebugID_CalOffset )
        {
            DBG_LOG_PRINT(("[ACFG]{%s: %d} (id:0x%X) i2_pic_mode:%d ==> %d\n", __FUNCTION__,__LINE__, u16RecId, i2_pic_mode, *pui2_idx ));
        }
    #endif
    }

    return i32_offset;
}

char* acfg_cust_get_input_grp_name(ACFG_CUST_INPUT_GRP_T e_input_grp)
{
    char* pc_name = "Unknown";

    switch(e_input_grp)
    {
        case ACFG_CUST_INPUT_GRP_HDMI1: pc_name = "HDMI1";
            break;
        case ACFG_CUST_INPUT_GRP_HDMI2: pc_name = "HDMI2";
            break;
        case ACFG_CUST_INPUT_GRP_HDMI3: pc_name = "HDMI3";
            break;
        case ACFG_CUST_INPUT_GRP_HDMI4: pc_name = "HDMI4";
            break;
        case ACFG_CUST_INPUT_GRP_VTRL: pc_name = "VTRL";
            break;

        default:
            break;
    }

    return pc_name;
}

void acfg_cust_video_print_setting_data_u8_all(UINT8* pu8Data, UINT16 u16DataSize, BOOL bHDR, BOOL bCusPicMode )
{
    DBG_LOG_PRINT(("[ACFG]{%s,%d} u16DataSize:%d \n",
        __FUNCTION__,__LINE__, u16DataSize ));

    int iDataCount = 0;
    int iSrcIdx = 0;
    int iSrcIdx_end = ACFG_INPUT_SRC_NUM;
    int iHdrType = 0;
    int iHdrType_end = (bHDR)?4:1;
    int iPicMode =0;

    INT32 i32_offset;
    UINT8 u8Data;

#define ACFG_INPUT_SRC_NUM          (ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT)

#define ACFG_PRE_SET_PIC_MODE_NUM   (6)
#define ACFG_CUST_SET_PIC_MODE_NUM  (8)
#define ACFG_PIC_MODE_NUM           (ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM)

#define APP_CFG_DYNAMIC_RANGE_NUM             (4)

#define APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC    (ACFG_INPUT_SRC_NUM * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM)

    //DBG_LOG_PRINT(("[ACFG] ACFG_INPUT_SRC_NUM:%d \n", ACFG_INPUT_SRC_NUM ));
    //DBG_LOG_PRINT(("[ACFG] ACFG_PRE_SET_PIC_MODE_NUM:%d \n", ACFG_PRE_SET_PIC_MODE_NUM ));
    //DBG_LOG_PRINT(("[ACFG] APP_CFG_DYNAMIC_RANGE_NUM:%d \n", APP_CFG_DYNAMIC_RANGE_NUM ));
    if( bCusPicMode )
    {
        DBG_LOG_PRINT(("[ACFG] APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC:%d \n", APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC ));
    }

    // Preset
    for( iSrcIdx = 0; iSrcIdx < iSrcIdx_end ; iSrcIdx += 1)
    {
        for( iHdrType = 0; iHdrType < iHdrType_end ; iHdrType += 1)
        {
            for( iPicMode = 0; iPicMode < ACFG_PRE_SET_PIC_MODE_NUM ; iPicMode += 1) // 0 ~ 5
            {
                //INT32 acfg_cust_video_get_DataOffset_By_Src_HdrType_PicMode( UINT8 u8SrcIdx, UINT8 u8DHR_type, UINT8 u8PicMode )
                i32_offset = acfg_cust_video_get_DataOffset_By_Src_HdrType_PicMode( iSrcIdx, iHdrType, iPicMode );
                if( (i32_offset < 0) || (i32_offset >= u16DataSize) )
                {
                    DBG_LOG_PRINT(("[ACFG]{%s,%d} Error: Invalid i32_offset:%d \n",
                        __FUNCTION__,__LINE__, i32_offset ));
                    return;
                }

                u8Data = pu8Data[i32_offset];

                if( (iPicMode == 5) // sport
                 &&( (iSrcIdx==ACFG_CUST_INPUT_GRP_VTRL)
                   ||( (iSrcIdx>=ACFG_CUST_INPUT_GRP_HDMI1)&&(iSrcIdx<=ACFG_CUST_INPUT_GRP_HDMI4) )
                   )
                )
                {
                    DBG_LOG_PRINT(("[ACFG](%d,%d,%d)[%d]=> %d SPORT %s\n",
                    iSrcIdx, iHdrType, iPicMode, i32_offset, u8Data, acfg_cust_get_input_grp_name(iSrcIdx) ));
                }
                else
                {
                    DBG_LOG_PRINT(("[ACFG](%d,%d,%d)[%d]=> %d \n", iSrcIdx, iHdrType, iPicMode, i32_offset, u8Data ));
                }

                iDataCount += 1;
                if( iDataCount >= u16DataSize )
                {
                    return;
                }

            }
        }
    }

    if( iDataCount >= u16DataSize )
    {
        return;
    }

    if( bCusPicMode )
    {
        // Custom picture from 264
        for( iHdrType = 0; iHdrType < iHdrType_end; iHdrType += 1)
        {
            for( iPicMode = 6; iPicMode < ACFG_PRE_SET_PIC_MODE_NUM+6; iPicMode += 1) // 6 ~ 11
            {
                //INT32 acfg_cust_video_get_DataOffset_By_Src_HdrType_PicMode( UINT8 u8SrcIdx, UINT8 u8DHR_type, UINT8 u8PicMode )
                i32_offset = acfg_cust_video_get_DataOffset_By_Src_HdrType_PicMode( 0, iHdrType, iPicMode );

                if( (i32_offset < 0) || (i32_offset >= u16DataSize) )
                {
                    DBG_LOG_PRINT(("[ACFG]{%s,%d} Error: Invalid i32_offset:%d \n",
                        __FUNCTION__,__LINE__, i32_offset ));
                    return;
                }

                u8Data = pu8Data[i32_offset];

                DBG_LOG_PRINT(("[ACFG](X,%d,%d)[%d]=> %d \n", iHdrType, iPicMode, i32_offset, u8Data ));

                iDataCount += 1;
                if( iDataCount >= u16DataSize)
                {
                    return;
                }
            }
        }
    }
}



/*-----------------------------------------------------------------------------
 * Name: acfg_cust_get_elem_index
 *
 * Description:
 *     the following is the latest spec for the video field:
 *   1. pic mode will by store by input src, and the num of pre-set is six, the num of cust pic mode is six too;
 *   2. pre-set pic mode settings store by input src, and the cust pic mode settings is glob for all input src;
 *   3. clr temp settings will be only by clr temp, and glob for all pic mode & input src
 *     the following is the true layout for each video filed in acfg eeprom:
 *   1. pic mode layout by input src;
 *   2. pic mode settings layout by input_src * pic mode(pre-set + cust pic mode(8));
 *   3. for cust pic mode will use add in input src HDMI1;
 *   4. clr temp settings layout by clr temp only;
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_video_get_elem_idx(
                UINT16          ui2_id,
                UINT8           ui1_input_src,
                UINT16*         pui2_idx
                )
{
    INT32   i4_ret;
    UINT16  ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16  ui2_cfg_rec = CFG_GET_SETTING(ui2_id);


#if( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
    if( ui2_id == g_AcfgCust_u16DebugID_CalOffset )
    {
        DBG_LOG_PRINT(("[ACFG]{%s: %d} (ui2_id:0x%X, input_src:%d)\n", __FUNCTION__,__LINE__, ui2_id, ui1_input_src ));
    }
#endif

    switch(ui2_cfg_grp)
    {
    case APP_CFG_GRPID_VIDEO:
        switch(ui2_cfg_rec)
        {
            case APP_CFG_RECID_PIC_MODE:
            case APP_CFG_RECID_VID_ETOF:
            case APP_CFG_RECID_VID_FILM_MAEKER_MODE:
                {
                    /* pic mode store by input src*/
                    ISL_REC_T                   t_isl_rec = {0};

                    /* Get input group */
                    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);

                    *pui2_idx = _get_input_grp(&t_isl_rec);
                }
                break;
#ifdef NEVER
            case APP_CFG_RECID_CLR_TEMP:
            case APP_CFG_RECID_VID_3D_NR:
            case APP_CFG_RECID_VID_NR:
        #ifdef APP_MPEG_NR_SUPPORT
            case APP_CFG_RECID_VID_MPEG_NR:
        #endif
            case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
            case APP_CFG_RECID_VID_SHP:
            case APP_CFG_RECID_VID_CONTRAST_EN:
            case APP_CFG_RECID_VID_SUPER_RESOLUTION_EX:
            case APP_CFG_RECID_VID_EDGE_ENHANCEMENT:
            case APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION:
            case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
            case APP_CFG_RECID_VID_GAME_HDR:
            case APP_CFG_RECID_VID_EN_VIEW_ANGLE:
            case APP_CFG_RECID_VID_GAME_LOW_LATENCY:
            case APP_CFG_RECID_VID_JUDDER_REDUCTION:
            case APP_CFG_RECID_VID_CONTOUR_SMOTHING:
            case APP_CFG_RECID_VID_CLEAR_ACTION:
            case APP_CFG_RECID_VID_DI_FILM_MODE:
#endif /* NEVER */
            case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
            case APP_CFG_RECID_VID_GAME_LOW_LATENCY:
            case APP_CFG_RECID_VID_GAME_HDR:
                {
                    ISL_REC_T                   t_isl_rec;
                    UINT16                      ui2_ipt = 0;
                    INT16                       i2_pic_mode = 0;

                    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T) );

                    /* Get input group */
                    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);

                    ui2_ipt = _get_input_grp(&t_isl_rec);

                    /* Get picture mode. */
                    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
                    if (i4_ret != APP_CFGR_OK)
                    {
                        i2_pic_mode = 0;
                    }

                    if (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
                    {
                        ui2_ipt = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;
                    }

                    *pui2_idx = ui2_ipt*ACFG_PIC_MODE_NUM + i2_pic_mode;
                }
                break;

            case APP_CFG_RECID_CUST_PIC_COPY_BASE:
               {
                    UINT16                      ui2_ipt = 0;
                    INT16                       i2_pic_mode = 0;
                    ISL_REC_T                   t_isl_rec;

                    /* Get input group */
                    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);
                    ui2_ipt = _get_input_grp(&t_isl_rec);

                    /* Get picture mode. */
                    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
                    if (i4_ret != APP_CFGR_OK)
                    {
                        i2_pic_mode = 0;
                    }

                    if (i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
                    {
                        *pui2_idx = ui2_ipt*ACFG_PRE_SET_PIC_MODE_NUM + i2_pic_mode;
                    }
                    else
                    {
                        ui2_ipt = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;
                        *pui2_idx = ui2_ipt*ACFG_CUST_SET_PIC_MODE_NUM + i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;
                    }
                }
                break;
            case APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS:
                {
                    /*note:
                                   *this filed in acfg layout will be by input src, as the
                                   *cust pic mode is glob, so only use the hdmi1 addr of it;
                                   */

                    /* one value per input source group */
                    UINT16                      ui2_ipt = 0;
                    INT16                       i2_pic_mode = 0;

                    /* will only use hdmi1*/
                    ui2_ipt = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;

                    /* Get picture mode. */
                    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
                    if (i4_ret != APP_CFGR_OK)
                    {
                        i2_pic_mode = 0;
                    }

                    if (i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
                    {
                        DBG_LOG_PRINT(("\nAPP_CFG_RECID_CUST_PIC_COPY_BASE(idx) errro!!!\n"));
                        *pui2_idx = 0;
                    }
                    else
                    {
                        *pui2_idx = ui2_ipt*ACFG_CUST_SET_PIC_MODE_NUM + i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;
                    }
                }
                break;
            case APP_CFG_RECID_VID_11_POINT_GAIN:
                {
                    /*layout by src*clr_temp, and will use the global one*/
                    UINT16                      ui2_ipt = a_acfg_cust_get_dynamic_range();
                    INT16                       i2_clr_tmp = 0;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);
                    *pui2_idx = ui2_ipt * ACFG_CLR_TEMP_NUM + i2_clr_tmp;
                }
                break;

            case APP_CFG_RECID_VID_11_POINT_GAIN_RED:
            case APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:
            case APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:
                {
                    /* layout by src*clr_temp*11_point_gain, and will use the global one*/
                    UINT16                      ui2_ipt = a_acfg_cust_get_dynamic_range();
                    INT16                       i2_11_point_gain = 0;
                    INT16                       i2_clr_tmp = 0;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), &i2_11_point_gain);

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);

                    *pui2_idx = ui2_ipt * ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_clr_tmp*APP_CFG_11_POINT_GAIN_NUM + i2_11_point_gain;
                }
                break;
#ifndef APP_ODM_ONE_IMG_SUPPORT
#ifdef APP_CFG_FAC_CLR_TEMP
            case APP_CFG_RECID_VID_FAC_GAIN_R:
            case APP_CFG_RECID_VID_FAC_GAIN_G:
            case APP_CFG_RECID_VID_FAC_GAIN_B:
            case APP_CFG_RECID_VID_FAC_OFFSET_R:
            case APP_CFG_RECID_VID_FAC_OFFSET_B:
            case APP_CFG_RECID_VID_FAC_OFFSET_G:
            {
                /* layout clr_temp*/
                INT16   i2_clr_tmp = 0;

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);

                *pui2_idx = i2_clr_tmp;
                break;
            }
#endif
#endif
            case APP_CFG_RECID_CLR_TEMP:
            case APP_CFG_RECID_VID_3D_NR:
            case APP_CFG_RECID_VID_NR:
#ifdef APP_MPEG_NR_SUPPORT
            case APP_CFG_RECID_VID_MPEG_NR:
#endif
            case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
            case APP_CFG_RECID_VID_SHP:
            case APP_CFG_RECID_VID_CONTRAST_EN:
            case APP_CFG_RECID_VID_SUPER_RESOLUTION_EX:
            case APP_CFG_RECID_VID_EDGE_ENHANCEMENT:
            case APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION:
            case APP_CFG_RECID_VID_EN_VIEW_ANGLE:
            case APP_CFG_RECID_VID_JUDDER_REDUCTION:
            case APP_CFG_RECID_VID_CONTOUR_SMOTHING:
            case APP_CFG_RECID_VID_CLEAR_ACTION:
            case APP_CFG_RECID_VID_DI_FILM_MODE:
            case APP_CFG_RECID_VID_GAME_MODE:
            case APP_CFG_RECID_VID_MJC_EFFECT:
            case APP_CFG_RECID_VID_MJC_MODE:
            case APP_CFG_RECID_VID_FLESH_TONE:
            case APP_CFG_RECID_VID_LUMA:
            case APP_CFG_RECID_VID_REDUCE_BLUR:
            case APP_CFG_RECID_VID_PRE_PIC_CHG:
            case APP_CFG_RECID_VID_CUST_GAMMA:
            case APP_CFG_RECID_VID_CUSTOM_DCR:
            case APP_CFG_RECID_VID_CUSTOM_DIMMING:
            case APP_CFG_RECID_VID_PEAK_LUMINANCE:
            case APP_CFG_RECID_VID_BRI:
            case APP_CFG_RECID_VID_CNT:
            case APP_CFG_RECID_VID_SAT:
            case APP_CFG_RECID_VID_HUE:
            case APP_CFG_RECID_VID_RED:
            case APP_CFG_RECID_VID_GREEN:
            case APP_CFG_RECID_VID_BLUE:
            case APP_CFG_RECID_VID_CLR_HUE_R:
            case APP_CFG_RECID_VID_CLR_HUE_G:
            case APP_CFG_RECID_VID_CLR_HUE_B:
            case APP_CFG_RECID_VID_CLR_SAT_R:
            case APP_CFG_RECID_VID_CLR_SAT_G:
            case APP_CFG_RECID_VID_CLR_SAT_B:
            case APP_CFG_RECID_VID_CLR_BRI_R:
            case APP_CFG_RECID_VID_CLR_BRI_G:
            case APP_CFG_RECID_VID_CLR_BRI_B:
            case APP_CFG_RECID_VID_CLR_HUE_C:
            case APP_CFG_RECID_VID_CLR_HUE_M:
            case APP_CFG_RECID_VID_CLR_HUE_Y:
            case APP_CFG_RECID_VID_CLR_SAT_C:
            case APP_CFG_RECID_VID_CLR_SAT_M:
            case APP_CFG_RECID_VID_CLR_SAT_Y:
            case APP_CFG_RECID_VID_CLR_BRI_C:
            case APP_CFG_RECID_VID_CLR_BRI_M:
            case APP_CFG_RECID_VID_CLR_BRI_Y:
            case APP_CFG_RECID_VID_LOCAL_CONTRAST:
            {
                //acfg_cust_video_get_special_item_idx(ui1_input_src,pui2_idx);
                acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode(ui2_id, ui1_input_src, pui2_idx);
                break;
            }
            #if 0
            case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
            {
                *pui2_idx = 0;
                break;
            }
            #endif
            case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
            case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
            case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:
            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:
            case APP_CFG_RECID_VID_CLR_TEMP_CHG:
                {
                    /* layout by dynamic_range *clr_tmp and will use the global one*/
                    INT16   i2_clr_tmp = 0;
                    UINT16  ui2_ipt = a_acfg_cust_get_dynamic_range();

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);
                    *pui2_idx = ui2_ipt * ACFG_CLR_TEMP_NUM + i2_clr_tmp;
                }
                break;
            case APP_CFG_RECID_CLR_GAIN_R:
            case APP_CFG_RECID_CLR_GAIN_G:
            case APP_CFG_RECID_CLR_GAIN_B:
            case APP_CFG_RECID_CLR_OFFSET_R:
            case APP_CFG_RECID_CLR_OFFSET_G:
            case APP_CFG_RECID_CLR_OFFSET_B:
            {
                UINT8   ui1_odm_id = 0;
                a_cfg_custom_get_odm_idx(&ui1_odm_id);
              /*
                         1 ---> Amtran;
                         2 ---> TPV
                         3 ---> Wistron;
                         4 ---> Foxconn;
                         5 ---> BOE;
                         6 ---> Innolux;
                     */
                if((ui1_odm_id == 4)||(ui1_odm_id == 6))
                {
                        /* layout clr_temp*/
                    INT16   i2_clr_tmp = 0;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);

                    *pui2_idx = i2_clr_tmp;
                }
                else
                {
                    /* the above field store by ipt_src*clr_tmp */
                    INT16        i2_clr_temp = 0;
                    ISL_REC_T    t_isl_rec;
                    UINT8        ui1_input_grp;

                    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);
                    ui1_input_grp = _get_input_grp(&t_isl_rec);

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

                    *pui2_idx = (UINT16)(ui1_input_grp * ACFG_CLR_TEMP_NUM + i2_clr_temp);

    /* will be for furthre deal with*/
#ifndef APP_CLR_GAIN_AND_OFFSET_NOT_DIS_2D_3D
                    if (b_3d_mode_playing)
                    {
                        *pui2_idx = ACFG_CUST_INPUT_GRP_MAX * ACFG_CLR_TEMP_NUM + i2_clr_temp;
                    }
#endif
                }
                break;
            }
            case APP_CFG_RECID_SCREEN_MODE:
            {
                CHAR                        s_disp_name[ACFG_MAX_DISP_NAME + 1];
                VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
                VSH_SRC_ASPECT_RATIO_T      e_asp_ratio;
                ISL_REC_T                   t_isl_rec;

                /* Get input group */
                a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                if (c_strcmp(s_disp_name, SN_PRES_SUB_DISPLAY) == 0)
                {
                    return APP_CFGR_INV_ARG;
                }

                a_cfg_av_get_timing(s_disp_name, &t_timing);
                e_asp_ratio = a_sml_get_src_asp_ratio(&t_timing);
                a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);

                if ( a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
                {
                    // special case for ACFG_SCR_MODE_ELEM_FOR_MMP. In MMP case,
                    // Screen mode only have 2 kind of setting. 16:9 and 4:3.
                    // The last 2 array elements are for 16:9 and 4:3.
                    if(e_asp_ratio == VSH_SRC_ASPECT_RATIO_16_9)
                    {
                        /* 16:9 */
                        *pui2_idx = ACFG_SCR_MODE_ELEM_NUM-1;
                    }
                    else
                    {
                        /* 4:3 */
                        *pui2_idx = ACFG_SCR_MODE_ELEM_NUM-2;
                    }
                }
                else
                {
                    *pui2_idx = _get_hvpos_scrmode_elem_idx(ui1_input_src);
                }

                break;
            }
            case APP_CFG_RECID_VID_POS_H:
            case APP_CFG_RECID_VID_POS_V:
            case APP_CFG_RECID_VID_CUSTOM_H_SIZE:
            case APP_CFG_RECID_VID_CUSTOM_V_SIZE:
            {
                *pui2_idx = _get_hv_pos_idx (ui1_input_src);
                break;
            }
            case APP_CFG_RECID_VID_YPBPR_PHASE:
            {
                typedef struct __TIMING_IDX_MAP_T
                {
                    UINT8   ui1_idx;
                    UINT32  ui4_width;
                    UINT32  ui4_height;
                    UINT32  ui4_frame_rate;
                    BOOL    b_is_progressive;
                }   _TIMING_IDX_MAP_T;

                _TIMING_IDX_MAP_T           at_timing_idx_map[] =
                {
                    {  0,   0,  480,   0,  FALSE}, /*  480I */
                    {  1,   0,  480,   0,  TRUE},  /*  480P */
                    {  2,   0,  576,   0,  FALSE}, /*  480I */
                    {  3,   0,  576,   0,  TRUE},  /*  480P */
                    {  4,   0,  720,  50,  TRUE},  /*  720P(50) */
                    {  5,   0,  720,  60,  TRUE},  /*  720P(60) */
                    {  6,   0, 1080,  48,  FALSE}, /* 1080I(24) */
                    {  7,   0, 1080,  50,  FALSE}, /* 1080I(25) */
                    {  8,   0, 1080,  60,  FALSE}, /* 1080I(30) */
                    {  9,   0, 1080,  24,  TRUE},  /* 1080P(24) */
                    { 10,   0, 1080,  25,  TRUE},  /* 1080P(25) */
                    { 11,   0, 1080,  30,  TRUE},  /* 1080P(30) */
                    { 12,   0, 1080,  50,  TRUE},  /* 1080P(50) */
                    { 13,   0, 1080,  60,  TRUE},  /* 1080P(60) */
                    { 14,   0,    0,   0,  FALSE}, /* I*/
                    { 14,   0,    0,   0,  TRUE}   /* P*/
                };

                CHAR                        s_disp_name[ACFG_MAX_DISP_NAME + 1];
                VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
                UINT16                      ui2_i;

                /* Get current timing */
                a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                a_cfg_av_get_timing(s_disp_name, &t_timing);

                for(ui2_i=0;
                    ui2_i < (UINT16)(sizeof(at_timing_idx_map)/ sizeof(at_timing_idx_map[0]));
                    ui2_i++)
                {
                    if( (at_timing_idx_map[ui2_i].ui4_width == 0 ||
                         at_timing_idx_map[ui2_i].ui4_width == t_timing.ui4_width) &&

                        (at_timing_idx_map[ui2_i].ui4_height == 0 ||
                         at_timing_idx_map[ui2_i].ui4_height == t_timing.ui4_height) &&

                        (at_timing_idx_map[ui2_i].ui4_frame_rate == 0 ||
                         at_timing_idx_map[ui2_i].ui4_frame_rate == t_timing.ui4_frame_rate) &&

                        (at_timing_idx_map[ui2_i].b_is_progressive == t_timing.b_is_progressive))
                    {
                        *pui2_idx = at_timing_idx_map[ui2_i].ui1_idx;
                        break;
                    }
                }
                break;
            }
            default:
                *pui2_idx = 0;
                break;
        }
        break;

    case APP_CFG_GRPID_DISP:
        switch(ui2_cfg_rec)
        {
            case APP_CFG_RECID_DISP_ADP_BACK_LIGHT:
            case APP_CFG_RECID_DISP_BACK_LIGHT:
            {
                //acfg_cust_video_get_special_item_idx(ui1_input_src,pui2_idx);
                acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode(ui2_id, ui1_input_src, pui2_idx);
                break;
            }
            default:
                *pui2_idx = 0;
                break;
        }
        break;

    default:
        *pui2_idx = 0;
    }

#ifdef APP_ODM_ONE_IMG_SUPPORT
    _acfg_cust_video_get_elem_idx_for_fac(ui2_id, ui1_input_src, pui2_idx);
#endif
    DBG_INFO(("\n[ACFG]PQ item elem index = %d, ui2_cfg_grp = %d, ui2_cfg_rec = %d\n",
                                                *pui2_idx, ui2_cfg_grp, ui2_cfg_rec));

#if( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
    if( ui2_id == g_AcfgCust_u16DebugID_CalOffset )
    {
        DBG_LOG_PRINT(("[ACFG]{%s: %d} (ui2_id:0x%X, input_src:%d) ==> DataOffset:%d\n", __FUNCTION__,__LINE__, ui2_id, ui1_input_src, *pui2_idx ));
    }
#endif

    return APP_CFGR_OK;
}

static INT16 _acfg_cust_video_get_def_val_by_idx (UINT16  ui2_idx,UINT8 ui1_mode, UINT8  ui1_tpye)
{
    UINT16 ui2_i = 0;
    UINT16 ui2_num = sizeof(at_pq_def_tbl[0]) / sizeof(APP_CFG_CUSTOM_PQ_TBL_T);
    UINT16 ui2_hdr_hlg_num = sizeof(at_pq_hdr_hlg_def_tbl[0]) / sizeof(APP_CFG_CUSTOM_PQ_TBL_T);
    UINT16 ui2_dobly_vision_num = sizeof(at_pq_dobly_version_def_tbl[0]) / sizeof(APP_CFG_CUSTOM_PQ_TBL_T);
    UINT16 ui2_pro_num = sizeof(at_pro_pq_def_tbl[0]) / sizeof(APP_CFG_CUSTOM_PQ_TBL_T);

    switch (ui1_tpye)
    {
        case ACFG_CUST_CONTENT_SDR:
            for (ui2_i = 0;ui2_i < ui2_num; ui2_i++)
            {
                if( ((UINT8)at_pq_def_tbl[ui4_pq_id][ui2_i].e_pic_mode == ui1_mode)
                  && (at_pq_def_tbl[ui4_pq_id][ui2_i].ui2_idx == ui2_idx)
                  )
                {
                    return at_pq_def_tbl[ui4_pq_id][ui2_i].i2_def;
                }
            }
            break;
        case ACFG_CUST_CONTENT_HDR:
        case ACFG_CUST_CONTENT_HLG:
            for (ui2_i = 0;ui2_i < ui2_hdr_hlg_num; ui2_i++)
            {
                if (((UINT8)at_pq_hdr_hlg_def_tbl[ui4_pq_id][ui2_i].e_pic_mode == ui1_mode) && (at_pq_hdr_hlg_def_tbl[ui4_pq_id][ui2_i].ui2_idx == ui2_idx))
                {
                    return at_pq_hdr_hlg_def_tbl[ui4_pq_id][ui2_i].i2_def;
                }
            }
            break;
        case ACFG_CUST_CONTENT_DV:
            for (ui2_i = 0;ui2_i < ui2_dobly_vision_num; ui2_i++)
            {
                if (((UINT8)at_pq_dobly_version_def_tbl[ui4_pq_id][ui2_i].e_pic_mode == ui1_mode) && (at_pq_dobly_version_def_tbl[ui4_pq_id][ui2_i].ui2_idx == ui2_idx))
                {
                    return at_pq_dobly_version_def_tbl[ui4_pq_id][ui2_i].i2_def;
                }
            }
            break;
        default :
            break;

    }

    for (ui2_i = 0;ui2_i < ui2_pro_num; ui2_i++)
    {
        if (((UINT8)at_pro_pq_def_tbl[0][ui2_i].e_pic_mode == ui1_mode)
            && (at_pro_pq_def_tbl[0][ui2_i].ui2_idx == ui2_idx))
        {
            return at_pro_pq_def_tbl[0][ui2_i].i2_def;
        }
    }

    return 0;
}

static INT16 _acfg_cust_video_get_def_val (
    UINT16  ui2_idx,
    UINT8   ui1_mode)
{
    UINT8    ui1_video_type = a_acfg_cust_get_dynamic_range();
    return _acfg_cust_video_get_def_val_by_idx(ui2_idx,ui1_mode,ui1_video_type);
}

INT32 acfg_cust_video_get_predef_value_by_idx(
    UINT16  ui2_rec_idx,
    UINT16  ui2_elem_idx,
    INT16*  pi2_val)
{
    INT32   i4_ret;
    CHAR    at_values[ACFG_MAX_REC_SIZE];
    SIZE_T  z_size;
    UINT16  ui2_elem_num;
    INT16   i2_val;
    INT16   i2_min = 0;
    INT16   i2_max = 0;
    BOOL    b_signed = FALSE;
    UINT16  ui2_elem_off;
    UINT16  Ui2_max_offset;

    i4_ret = a_cfg_av_get_min_max(at_acfg_descr[ui2_rec_idx].ui2_id,
                                  &i2_min,
                                  &i2_max);
    if (i4_ret == APP_CFGR_OK &&
        i2_min < 0)
    {
        b_signed = TRUE;
    }
#if (defined(APP_CFG_4BIT_STORE_SUPPORT) && defined(APP_CFG_EEPROM_SUPPORT))

    /* deal with the 4bit case*/
    if (CFG_4BIT_UNSIGNED_T == at_acfg_descr[ui2_rec_idx].e_type)
    {
        b_signed = FALSE;
    }

#ifdef APP_CFG_SIGNED_4BIT_STORE_SUPPORT
    else if (CFG_4BIT_SIGNED_T == at_acfg_descr[ui2_rec_idx].e_type)
    {
        b_signed = TRUE;
    }
#endif
    else
    {
        /* do nothing*/
    }
#endif

    i4_ret = acfg_get_default(ui2_rec_idx, at_values , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        ACFG_DBG_PRINT("acfg_get_default,i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    switch(at_acfg_descr[ui2_rec_idx].e_type)
    {
#if (defined(APP_CFG_4BIT_STORE_SUPPORT) && defined(APP_CFG_EEPROM_SUPPORT))
    case CFG_4BIT_UNSIGNED_T:

#ifdef APP_CFG_SIGNED_4BIT_STORE_SUPPORT
    case CFG_4BIT_SIGNED_T:
#endif
#endif
    case CFG_8BIT_T:
        ui2_elem_num        = (UINT16)z_size;
        ui2_elem_off        =  ui2_elem_idx;
        break;
    case CFG_16BIT_T:
        ui2_elem_num        = (UINT16)(z_size / 2);
        ui2_elem_off        = (UINT16)(ui2_elem_idx * 2);
        break;
    case CFG_32BIT_T:
        ui2_elem_num        = (UINT16)(z_size / 4);
        ui2_elem_off        = (UINT16)(ui2_elem_idx * 4);
        break;
    case CFG_64BIT_T:
        ui2_elem_num        = (UINT16)(z_size / 8);
        ui2_elem_off        = (UINT16)(ui2_elem_idx * 8);
        break;
    default:
        return APP_CFGR_INTERNAL_ERR;
    }

    if (ui2_elem_idx >= ui2_elem_num)
    {
        ACFG_DBG_PRINT("APP_CFGR_INV_ARG \r\n");
        return APP_CFGR_INV_ARG;
    }

    Ui2_max_offset = ACFG_MAX_REC_SIZE - (at_acfg_descr[ui2_rec_idx].e_type == CFG_16BIT_T ?  2 :
                                          at_acfg_descr[ui2_rec_idx].e_type == CFG_32BIT_T ? 4 :
                                          at_acfg_descr[ui2_rec_idx].e_type == CFG_32BIT_T ? 8 : 1);

    if (ui2_elem_off >  Ui2_max_offset)
    {
        ACFG_DBG_PRINT("APP_CFGR_INV_ARG \r\n");
        return APP_CFGR_INV_ARG;
    }

    if(b_signed)
    {
        switch(at_acfg_descr[ui2_rec_idx].e_type)
        {

#if (defined(APP_CFG_4BIT_STORE_SUPPORT) && defined(APP_CFG_EEPROM_SUPPORT))
#ifdef APP_CFG_SIGNED_4BIT_STORE_SUPPORT

        case CFG_4BIT_SIGNED_T:
#endif
#endif
        case CFG_8BIT_T:
            i2_val              = (INT16) *((INT8*)&at_values[ui2_elem_off]);
            break;
        case CFG_16BIT_T:
            i2_val              = (INT16) *((INT16*)&at_values[ui2_elem_off]);
            break;
        case CFG_32BIT_T:
            i2_val              = (INT16) *((INT32*)&at_values[ui2_elem_off]);
            break;
        case CFG_64BIT_T:
            i2_val              = (INT16) *((INT64*)&at_values[ui2_elem_off]);
            break;
        default:
            ACFG_DBG_PRINT("APP_CFGR_INTERNAL_ERR \r\n");
            return APP_CFGR_INTERNAL_ERR;
        }
    }
    else
    {
        switch(at_acfg_descr[ui2_rec_idx].e_type)
        {

#if (defined(APP_CFG_4BIT_STORE_SUPPORT) && defined(APP_CFG_EEPROM_SUPPORT))
        case CFG_4BIT_UNSIGNED_T:
#endif
        case CFG_8BIT_T:
            i2_val              = (INT16) *((UINT8*)&at_values[ui2_elem_off]);
            break;
        case CFG_16BIT_T:
            i2_val              = (INT16) *((UINT16*)&at_values[ui2_elem_off]);
            break;
        case CFG_32BIT_T:
            i2_val              = (INT16) *((UINT32*)&at_values[ui2_elem_off]);
            break;
        case CFG_64BIT_T:
            i2_val              = (INT16) *((UINT64*)&at_values[ui2_elem_off]);
            break;
        default:
            ACFG_DBG_PRINT("APP_CFGR_INTERNAL_ERR \r\n");
            return APP_CFGR_INTERNAL_ERR;
        }
    }

    *pi2_val = i2_val;
    //ACFG_DBG_PRINT("--index = %u, elem_index = %u, value = %d\n",ui2_rec_idx, ui2_elem_idx, (*pi2_val));


    return APP_CFGR_OK;
}

static INT32 _acfg_app2odm(
    INT16   i2_app_min,
    INT16   i2_app_max,
    INT16   i2_app_val,
    INT32   i4_odm_min,
    INT32   i4_odm_max,
    INT32*  pi4_odm_val)
{
    if(pi4_odm_val == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    if(i2_app_min > i2_app_max ||
       i4_odm_min > i4_odm_max ||
       i2_app_min == i2_app_max)
    {
        DBG_LOG_PRINT(("<ACFG> Return APP_CFGR_INV_ARG:%s:%d\n", __FILE__, __LINE__));
        return APP_CFGR_INV_ARG;
    }
    else if (i4_odm_min == i4_odm_max)
    {
        *pi4_odm_val = i4_odm_max;
    }
    else if(i2_app_val < i2_app_min)
    {
        *pi4_odm_val = i4_odm_min;
    }
    else if(i2_app_val > i2_app_max)
    {
        *pi4_odm_val = i4_odm_max;
    }
    else
    {
        /* floor */
        *pi4_odm_val = i4_odm_min +
                       (i4_odm_max - i4_odm_min) *
                       (i2_app_val - i2_app_min) /
                       (i2_app_max - i2_app_min);

    }

    return APP_CFGR_OK;
}

extern INT32 acfg_cust_video_get_predef_value(
    UINT16  ui2_id,
    UINT8   ui1_mode,
    INT16*  pi2_val)
{
    UINT16  ui2_grp_id = CFG_GET_GROUP(ui2_id);
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);

    switch(ui2_grp_id)
    {
    case APP_CFG_GRPID_VIDEO:
    {
        switch(ui2_rec_id)
        {
        case APP_CFG_RECID_VID_BRI:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_BRI, ui1_mode);
            break;
        case APP_CFG_RECID_VID_CNT:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_CNT, ui1_mode);
            break;
        case APP_CFG_RECID_VID_SAT:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_SAT, ui1_mode);
            break;
        case APP_CFG_RECID_VID_HUE:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_HUE, ui1_mode);
            break;
        case APP_CFG_RECID_VID_SHP:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_SHP, ui1_mode);
            break;
        case APP_CFG_RECID_CLR_TEMP:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_CLR_TEMP, ui1_mode);
            break;
        case APP_CFG_RECID_VID_MJC_EFFECT:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_MJC_EFFECT, ui1_mode);
            break;
        case APP_CFG_RECID_VID_MJC_MODE:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_MJC_MODE, ui1_mode);
            break;
        case APP_CFG_RECID_VID_3D_NR:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_3D_NR, ui1_mode);
            break;
        case APP_CFG_RECID_VID_MPEG_NR:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_MPEG_NR, ui1_mode);
            break;
        case APP_CFG_RECID_VID_NR:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_NR, ui1_mode);
            break;
        case APP_CFG_RECID_VID_FLESH_TONE:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_FT, ui1_mode);
            break;
        case APP_CFG_RECID_VID_LUMA:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_LUMA, ui1_mode);
            break;
        case APP_CFG_RECID_VID_DI_FILM_MODE:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_DI_FILM_MODE, ui1_mode);
            break;
        case APP_CFG_RECID_VID_CUSTOM_DCR:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_CUSTOM_DCR_IDX, ui1_mode);
            break;
        case APP_CFG_RECID_VID_CUSTOM_DIMMING:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_CUSTOM_DIMMING, ui1_mode);
            break;
        case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_CUSTOM_LIGHT_SENSOR_IDX, ui1_mode);
            if (a_acfg_cust_get_dynamic_range () != ACFG_CUST_CONTENT_SDR)
            {
                *pi2_val = 0 ;
            }
            break;
        case APP_CFG_RECID_VID_GAME_MODE:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_VID_GAME_MODE, ui1_mode);
            break;
        default:
            *pi2_val =  0;
            break;
        }
    }
        break;
    case APP_CFG_GRPID_DISP:
    {
        switch(ui2_rec_id)
        {
        case APP_CFG_RECID_DISP_BACK_LIGHT:
            if(ui1_mode > ACFG_PIC_MODE_NUM)
            {
                return APP_CFGR_INV_ARG;
            }
            *pi2_val = _acfg_cust_video_get_def_val (IDX_DISP_BACK_LIGHT, ui1_mode);
            break;
        default:
            *pi2_val =  0;
            break;
        }
    }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_video_get_min_max(
    UINT16  ui2_id,
    INT16*  pi2_min,
    INT16*  pi2_max)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (!pi2_min || !pi2_max)
    {
        return APP_CFGR_INV_ARG;
    }

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp){
    case APP_CFG_GRPID_DISP:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    case APP_CFG_GRPID_VIDEO:
    {
        switch(ui2_cfg_rec){
        case APP_CFG_RECID_VID_CUSTOM_H_SIZE:
            *pi2_min = ACFG_CUSTOM_H_SIZE_MIN;
            *pi2_max = ACFG_CUSTOM_H_SIZE_MAX;
            break;
        case APP_CFG_RECID_VID_CUSTOM_V_SIZE:
            *pi2_min = ACFG_CUSTOM_V_SIZE_MIN;
            *pi2_max = ACFG_CUSTOM_V_SIZE_MAX;
            break;
        case APP_CFG_RECID_CLR_TEMP:
            *pi2_min = 0;
            *pi2_max = 2;
            break;

        case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:  /* Color Gain R */
        case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:  /* Color Gain G */
        case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:  /* Color Gain B */
        case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:  /* Color Offset R */
        case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:  /* Color Offset G */
        case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:  /* Color Offset B */
            *pi2_min = ACFG_CUST_CLR_GAIN_OFFSET_MIN;
            *pi2_max = ACFG_CUST_CLR_GAIN_OFFSET_MAX;
            break;
        case APP_CFG_RECID_VID_CLR_HUE_R:  /* Color HUE R */
        case APP_CFG_RECID_VID_CLR_HUE_G:  /* Color HUE G */
        case APP_CFG_RECID_VID_CLR_HUE_B:  /* Color HUE B */
        case APP_CFG_RECID_VID_CLR_SAT_R:  /* Color SAT R */
        case APP_CFG_RECID_VID_CLR_SAT_G:  /* Color SAT G */
        case APP_CFG_RECID_VID_CLR_SAT_B:  /* Color SAT B */
        case APP_CFG_RECID_VID_CLR_BRI_R:  /* Color BRI R */
        case APP_CFG_RECID_VID_CLR_BRI_G:  /* Color BRI G */
        case APP_CFG_RECID_VID_CLR_BRI_B:  /* Color BRI B */
        case APP_CFG_RECID_VID_CLR_HUE_C:  /* Color HUE R */
        case APP_CFG_RECID_VID_CLR_HUE_M:  /* Color HUE M*/
        case APP_CFG_RECID_VID_CLR_HUE_Y:  /* Color HUE Y */
        case APP_CFG_RECID_VID_CLR_SAT_C:  /* Color SAT C */
        case APP_CFG_RECID_VID_CLR_SAT_M:  /* Color SAT G */
        case APP_CFG_RECID_VID_CLR_SAT_Y:  /* Color SAT B */
        case APP_CFG_RECID_VID_CLR_BRI_C:  /* Color BRI C */
        case APP_CFG_RECID_VID_CLR_BRI_M:  /* Color BRI M */
        case APP_CFG_RECID_VID_CLR_BRI_Y:  /* Color BRI Y */
        case APP_CFG_RECID_VID_11_POINT_GAIN_RED: /*11 POINT GAIN READ*/
        case APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:/*11 POINT GAIN GREEN*/
        case APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:/*11 POINT GAIN BLUE*/
            *pi2_min = ACFG_CUST_11_WB_MIN;
            *pi2_max = ACFG_CUST_11_WB_MAX;
            break;
        case APP_CFG_RECID_VID_RED:
        case APP_CFG_RECID_VID_GREEN:
        case APP_CFG_RECID_VID_BLUE:
            *pi2_min = 0;
            *pi2_max = 1;
            break;
        case APP_CFG_RECID_VID_11_POINT_GAIN:
            *pi2_min = ACFG_CUST_11_GAIN_MIN;
            *pi2_max = ACFG_CUST_11_GAIN_MAX;
            break;
        case APP_CFG_RECID_VID_CUST_GAMMA:
            *pi2_min = ACFG_CUST_GAMMA_MIN;
            *pi2_max = ACFG_CUST_GAMMA_MAX;
            break;
        case APP_CFG_RECID_VID_FILM_MAEKER_MODE:
        case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
        case APP_CFG_RECID_VID_GAME_HDR:
        case APP_CFG_RECID_VID_EN_VIEW_ANGLE:
        case APP_CFG_RECID_VID_OLED_PIXEL_SHIFT:
            *pi2_min = ACFG_CUST_COMMON_OFF;
            *pi2_max = ACFG_CUST_COMMON_ON;
            break;
        case APP_CFG_RECID_VID_PEAK_LUMINANCE:
            *pi2_min = 0;
            *pi2_max = 2;
            break;
        case APP_CFG_RECID_VID_CONTRAST_EN:
        case APP_CFG_RECID_VID_SUPER_RESOLUTION_EX:
        case APP_CFG_RECID_VID_EDGE_ENHANCEMENT:
        case APP_CFG_RECID_VID_CONTOUR_SMOTHING:
        case APP_CFG_RECID_VID_LOCAL_CONTRAST:
            *pi2_min = 0;
            *pi2_max = 3;
            break;

        case APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION:
        case APP_CFG_RECID_VID_JUDDER_REDUCTION:
            *pi2_min = ACFG_CUST_COMMON_ZERO;
            *pi2_max = ACFG_CUST_COMMON_TEN;
            break;

        case APP_CFG_RECID_VID_ETOF:
            *pi2_min = ACFG_CUST_EOTF_MIN;
            *pi2_max = ACFG_CUST_EOTF_MAX;
            break;

        case APP_CFG_RECID_VID_GAME_LOW_LATENCY:
            *pi2_min = ACFG_CUST_GAME_LOW_LATENCY_AUTO;
            *pi2_max = ACFG_CUST_GAME_LOW_LATENCY_ON;
            break;

        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    default:
        i4_ret =  APP_CFGR_NOT_SUPPORT;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_video_incr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp){
    case APP_CFG_GRPID_DISP:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    case APP_CFG_GRPID_VIDEO:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    default:
        i4_ret =  APP_CFGR_NOT_SUPPORT;
        break;
    }

    return i4_ret;
}

extern INT32  acfg_cust_video_decr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp){
    case APP_CFG_GRPID_DISP:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    case APP_CFG_GRPID_VIDEO:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    default:
        i4_ret =  APP_CFGR_NOT_SUPPORT;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_video_get(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    UINT16          ui2_elem_idx = 0;
    UINT8           ui1_input = 0;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];

    UINT16  ui2_black_strech_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLACK_STRETCH);
    UINT16  ui2_white_strech_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WHITE_STRETCH);
    UINT16  ui2_luma_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA);

    if (!pi2_val)
    {
        return APP_CFGR_INV_ARG;
    }

    if ((ui2_black_strech_id == ui2_id)
        || (ui2_white_strech_id == ui2_id))
    {
        DBG_LOG_PRINT( ("\n [acfg] black_strech & white_strech should have the same value with luma\n"));

        ui2_id = ui2_luma_id;
        ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
        ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    }
    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 2: Get the index */
    i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_VIDEO:
        {
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_VID_BRI:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_VID_BRI, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        DBG_LOG_PRINT(("[acfg]APP_CFG_RECID_VID_BRI:50 %s,%d\r\n",__FUNCTION__,__LINE__));
                        *pi2_val = 50;
                    }
                }
                    break;
                case APP_CFG_RECID_VID_CNT:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_VID_CNT, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        DBG_LOG_PRINT(("[acfg]APP_CFG_RECID_VID_CNT:50 %s,%d\r\n",__FUNCTION__,__LINE__));
                        *pi2_val = 50;
                    }
                }
                    break;
                case APP_CFG_RECID_VID_SAT:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_VID_SAT, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        DBG_LOG_PRINT(("[acfg]APP_CFG_RECID_VID_SAT:50 %s,%d\r\n",__FUNCTION__,__LINE__));
                        *pi2_val = 50;
                    }
                }
                    break;
                case APP_CFG_RECID_VID_HUE:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_VID_HUE, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        DBG_LOG_PRINT(("[acfg]APP_CFG_RECID_VID_HUE:50 %s,%d\r\n",__FUNCTION__,__LINE__));
                        *pi2_val = 0;
                    }
                }
                    break;
                case APP_CFG_RECID_VID_SHP:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_VID_SHP, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_PIC_MODE:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_CLR_TEMP:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_CLR_TEMP, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_GAIN_R:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_CLR_GAIN_R, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_GAIN_G:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CLR_GAIN_G, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_GAIN_B:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CLR_GAIN_B, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_OFFSET_R:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CLR_OFFSET_R, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_OFFSET_G:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CLR_OFFSET_G, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_OFFSET_B:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CLR_OFFSET_B, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_LUMA:
                {
                    i4_ret = acfg_get_int16_by_idx(IDX_VID_LUMA, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                }
                    break;
                case APP_CFG_RECID_VID_CUSTOM_DIMMING:
                {
                    UINT8   ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;
                    SIZE_T  z_size = ICL_RECID_WIZARD_STATUS_SIZE;

                    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS),
                                           &ui1_wzd_sts, &z_size);

                    if (((i4_ret==APP_CFGR_OK) && (ui1_wzd_sts==ICL_WIZARD_STATUS_RESUME))
                        || a_cfg_custom_get_lcdim_used() == FALSE)
                    {
                        *pi2_val = 0;
                        break;
                    }
                    else
                    {
                        if (a_smart_dim_get_assume_val() == SMART_DIM_AS_OFF)
                        {
                            *pi2_val = 0;
                        }
                        else if (a_smart_dim_get_assume_val() == SMART_DIM_AS_ON)
                        {
                            *pi2_val = 1;
                        }
                        else
                        {

                            i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx, pi2_val);
                            ACFG_CHK_FAIL(i4_ret, i4_ret);
                        }
                    }
                }
                    break;
                case APP_CFG_RECID_VID_CUSTOM_DCR:
                {
                    UINT8   ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;
                    SIZE_T  z_size = ICL_RECID_WIZARD_STATUS_SIZE;

                    if ((FALSE == a_cfg_cust_get_support_local_dimming())
                        &&(a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI))
                    {
                        *pi2_val = 0;
                        break;
                    }

                    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS),
                                               &ui1_wzd_sts, &z_size);

                    if (((i4_ret==APP_CFGR_OK) && (ui1_wzd_sts==ICL_WIZARD_STATUS_RESUME))
                        || a_cfg_custom_get_lcdim_used() == FALSE)
                    {
                        *pi2_val = 0;
                        break;
                    }

                    if (a_smart_dim_get_assume_val() == SMART_DIM_AS_OFF ||
                        FALSE == acfg_is_backlight_control_enable())
                    {
                        *pi2_val = 0;
                    }
                    else if (a_smart_dim_get_assume_val() == SMART_DIM_AS_ON)
                    {
                        *pi2_val = 1;
                    }
                    else
                    {

                        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL(i4_ret, i4_ret);
                    }
                }
                    break;

                case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
                {
                #if 0
                    UINT8   ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;
                    SIZE_T  z_size = ICL_RECID_WIZARD_STATUS_SIZE;
                    UINT8   ui1_blur = 0;
                    BOOL    b_is_support = FALSE;

                    a_cfg_custom_is_reduce_blur_support(&b_is_support);

                    if (b_is_support)
                    {
                        a_cfg_custom_get_reduce_blur(&ui1_blur);
                    }

                    if (ui1_blur != 0)
                    {
                        *pi2_val = 0;
                        break;
                    }

                    if(a_cfg_cust_drv_is_lightsensor_support() == FALSE)
                    {
                        *pi2_val = 0;
                        break;
                    }

                    if(acfg_check_play_content() == ACFG_CUST_RGB_CONTENT_HDR_HLG)
                    {
                        *pi2_val = 0;
                        break;
                    }

            #ifdef APP_RETAIL_MODE_SUPPORT
                    ACFG_RETAIL_MODE_T    t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

                    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
                    {
                        *pi2_val = 0;
                        break;
                    }
            #endif

                    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS),
                                               &ui1_wzd_sts, &z_size);

                    if ((i4_ret==APP_CFGR_OK) && (ui1_wzd_sts==ICL_WIZARD_STATUS_RESUME))
                    {
                        *pi2_val = 0;
                        break;
                    }
                #endif

                    {
                        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL(i4_ret, i4_ret);
                    }
                }
                    break;

                case APP_CFG_RECID_VID_CONTRAST_EN:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_SUPER_RESOLUTION_EX:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_EDGE_ENHANCEMENT:
                     {
                         i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx, pi2_val);
                         ACFG_CHK_FAIL (i4_ret, i4_ret);
                         break;
                     }
                case APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_VARIABLE_REFRESH_RATE, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_GAME_HDR:
                     {
                         i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_GAME_HDR, ui2_elem_idx, pi2_val);
                         ACFG_CHK_FAIL (i4_ret, i4_ret);
                         break;
                     }
                case APP_CFG_RECID_VID_PEAK_LUMINANCE:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_ETOF:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_ETOF, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_FILM_MAEKER_MODE:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_FILM_MAKER_MODE, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_EN_VIEW_ANGLE:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_GAME_LOW_LATENCY:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_JUDDER_REDUCTION:
                    {
                        i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx, pi2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case  APP_CFG_RECID_VID_LOCAL_CONTRAST:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_VID_LOCAL_CONTRAST, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }

                case APP_CFG_RECID_VID_CONTOUR_SMOTHING:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_CLEAR_ACTION:
                {
                    i4_ret = acfg_get_int16_by_idx (IDX_CLEAR_ACTION, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_CUSTOM_H_SIZE:
                    i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_H_SIZE, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                case APP_CFG_RECID_VID_CUSTOM_V_SIZE:
                    i4_ret = acfg_get_int16_by_idx (IDX_CUSTOM_V_SIZE, ui2_elem_idx, pi2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
#ifdef APP_3D_RETAIL_DEMO_MODE
                case APP_CFG_RECID_VID_3D_MODE:
                    if (a_nav_retail_mode_get_play_video_status())
                    {
                        SCC_3D_MODE_T  e_3d_mode;

                        a_nav_retail_mode_get_3d_mode_type(&e_3d_mode);

                        *pi2_val = (UINT16)e_3d_mode;

                        return APP_CFGR_OK;
                    }
                    else
                    {
                        i4_ret = APP_CFGR_NO_ACTION;
                    }
                    break;
#endif
#ifndef APP_ODM_ONE_IMG_SUPPORT
#ifdef APP_CFG_FAC_CLR_TEMP
                case APP_CFG_RECID_VID_FAC_GAIN_R:
                case APP_CFG_RECID_VID_FAC_GAIN_G:
                case APP_CFG_RECID_VID_FAC_GAIN_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_GAIN_R;

                    switch(ui2_cfg_rec)
                    {
                        case APP_CFG_RECID_VID_FAC_GAIN_R:
                            ui2_rec_idx = IDX_CLR_FAC_GAIN_R;
                            break;
                        case APP_CFG_RECID_VID_FAC_GAIN_G:
                            ui2_rec_idx = IDX_CLR_FAC_GAIN_G;
                            break;
                        case APP_CFG_RECID_VID_FAC_GAIN_B:
                            ui2_rec_idx = IDX_CLR_FAC_GAIN_B;
                            break;
                        default:
                            /* not reachable */
                            break;
                    }
                    i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    break;
                }
                case APP_CFG_RECID_VID_FAC_OFFSET_R:
                case APP_CFG_RECID_VID_FAC_OFFSET_G:
                case APP_CFG_RECID_VID_FAC_OFFSET_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_OFFSET_R:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_G:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_B:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }
                    i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    break;
                }
#endif
#endif
                case  APP_CFG_RECID_SCREEN_MODE:
                {
                    UINT8   ui1_scr_mode = 0;
                    SIZE_T  z_size = ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE;

                    i4_ret = APP_CFGR_NO_ACTION;

                    if ((a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                                               &ui1_scr_mode, &z_size)==ICLR_OK))
                    {
                        if(ACFG_TEST_PATTERN_SCRN_MODE_WIDE == ui1_scr_mode)
                        {
                            *pi2_val = (INT16)SCC_VID_SCREEN_MODE_CUSTOM_DEF_1;
                            i4_ret = APP_CFGR_OK;
                        }
                        else if(ACFG_TEST_PATTERN_SCRN_MODE_NORMAL == ui1_scr_mode)
                        {
                            *pi2_val = (INT16)SCC_VID_SCREEN_MODE_NORMAL;
                            i4_ret = APP_CFGR_OK;
                        }
                    }

                    if (a_cfg_custom_chk_freqence_120hz())
                    {
                        *pi2_val = (INT16)SCC_VID_SCREEN_MODE_NORMAL;
                        i4_ret = APP_CFGR_OK;
                    }

                    return i4_ret;
                }

                case  APP_CFG_RECID_VID_CLR_HUE_R:
                case  APP_CFG_RECID_VID_CLR_HUE_G:
                case  APP_CFG_RECID_VID_CLR_HUE_B:
                case  APP_CFG_RECID_VID_CLR_SAT_R:
                case  APP_CFG_RECID_VID_CLR_SAT_G:
                case  APP_CFG_RECID_VID_CLR_SAT_B:
                case  APP_CFG_RECID_VID_CLR_BRI_R:
                case  APP_CFG_RECID_VID_CLR_BRI_G:
                case  APP_CFG_RECID_VID_CLR_BRI_B:
                case  APP_CFG_RECID_VID_CLR_HUE_C:
                case  APP_CFG_RECID_VID_CLR_HUE_M:
                case  APP_CFG_RECID_VID_CLR_HUE_Y:
                case  APP_CFG_RECID_VID_CLR_SAT_C:
                case  APP_CFG_RECID_VID_CLR_SAT_M:
                case  APP_CFG_RECID_VID_CLR_SAT_Y:
                case  APP_CFG_RECID_VID_CLR_BRI_C:
                case  APP_CFG_RECID_VID_CLR_BRI_M:
                case  APP_CFG_RECID_VID_CLR_BRI_Y:
                case  APP_CFG_RECID_VID_REDUCE_BLUR:
                case  APP_CFG_RECID_VID_RED:
                case  APP_CFG_RECID_VID_GREEN:
                case  APP_CFG_RECID_VID_BLUE:
                case  APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS:
                case  APP_CFG_RECID_VID_PRE_PIC_CHG:
                case  APP_CFG_RECID_CUST_PIC_COPY_BASE:
                case  APP_CFG_RECID_VID_11_POINT_GAIN:
                case  APP_CFG_RECID_VID_11_POINT_GAIN_RED:
                case  APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:
                case  APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:
                case  APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                case  APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                case  APP_CFG_RECID_VID_CUST_CLR_GAIN_B:
                case  APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                case  APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                case  APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:
                    {
                        UINT16  ui2_rec_idx = IDX_CLR_HUE_R;
                        switch (ui2_cfg_rec)
                        {
                            case APP_CFG_RECID_VID_CLR_HUE_R:
                                ui2_rec_idx = IDX_CLR_HUE_R;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_G:
                                ui2_rec_idx = IDX_CLR_HUE_G;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_B:
                                ui2_rec_idx = IDX_CLR_HUE_B;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_R:
                                ui2_rec_idx = IDX_CLR_SAT_R;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_G:
                                ui2_rec_idx = IDX_CLR_SAT_G;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_B:
                                ui2_rec_idx = IDX_CLR_SAT_B;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_R:
                                ui2_rec_idx = IDX_CLR_BRI_R;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_G:
                                ui2_rec_idx = IDX_CLR_BRI_G;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_B:
                                ui2_rec_idx = IDX_CLR_BRI_B;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_M:
                                ui2_rec_idx = IDX_CLR_HUE_M;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_C:
                                ui2_rec_idx = IDX_CLR_HUE_C;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_Y:
                                ui2_rec_idx = IDX_CLR_HUE_Y;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_C:
                                ui2_rec_idx = IDX_CLR_SAT_C;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_M:
                                ui2_rec_idx = IDX_CLR_SAT_M;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_Y:
                                ui2_rec_idx = IDX_CLR_SAT_Y;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_C:
                                ui2_rec_idx = IDX_CLR_BRI_C;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_M:
                                ui2_rec_idx = IDX_CLR_BRI_M;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_Y:
                                ui2_rec_idx = IDX_CLR_BRI_Y;
                                break;

                            case APP_CFG_RECID_VID_REDUCE_BLUR:
                                ui2_rec_idx = IDX_REDUCE_BLUR;
                                break;

                            case APP_CFG_RECID_VID_RED:
                                ui2_rec_idx = IDX_RED;
                                break;

                            case APP_CFG_RECID_VID_GREEN:
                                ui2_rec_idx = IDX_GREEN;
                                break;

                            case APP_CFG_RECID_VID_BLUE:
                                ui2_rec_idx = IDX_BLUE;
                                break;

                            case APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS:
                                ui2_rec_idx = IDX_CUST_PIC_EXIST_STATUS;
                                break;

                            case APP_CFG_RECID_VID_PRE_PIC_CHG:
                                ui2_rec_idx = IDX_PRE_PIC_CHG;
                                break;

                            case APP_CFG_RECID_CUST_PIC_COPY_BASE:
                                ui2_rec_idx = IDX_CUST_PIC_COPY_BASE;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN:
                                ui2_rec_idx = IDX_11_POINT_GAIN;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN_RED:
                                ui2_rec_idx = IDX_11_POINT_GAIN_RED;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:
                                ui2_rec_idx = IDX_11_POINT_GAIN_GREEN;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:
                                ui2_rec_idx = IDX_11_POINT_GAIN_BLUE;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                                ui2_rec_idx = IDX_CUST_CLR_GAIN_R;
                                break;
                            case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                                ui2_rec_idx = IDX_CUST_CLR_GAIN_G;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:
                                ui2_rec_idx = IDX_CUST_CLR_GAIN_B;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                                ui2_rec_idx = IDX_CUST_CLR_OFFSET_R;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                                ui2_rec_idx = IDX_CUST_CLR_OFFSET_G;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:
                                ui2_rec_idx = IDX_CUST_CLR_OFFSET_B;
                                break;
                             default:
                                break;

                    }

                    i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_CUST_GAMMA:
                    {
                        UINT16  ui2_rec_idx = IDX_CUST_GAMMA;
                        ui2_rec_idx = IDX_CUST_GAMMA;

                        i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                       ui2_elem_idx,
                                                       pi2_val);
                        ACFG_CHK_FAIL(i4_ret, i4_ret);
                    }
                    break;
                case APP_CFG_RECID_VID_COLOR_SPACE:
                    {
                        a_cfg_cust_get_color_space_value((UINT8 *)pi2_val);
                    }
                    break;
                default:
                {
#ifdef APP_ODM_ONE_IMG_SUPPORT
                    UINT16  ui2_rec_idx = 0;
                    i4_ret = APP_CFGR_OK;

                    if (a_app_cfg_fac_clr_temp() == FALSE)
                    {
                        i4_ret = APP_CFGR_NO_ACTION;
                        break;
                    }

                    if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_R)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_R;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_G)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_G;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_B)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_B;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_R)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_G)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_G;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_B)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_B;
                    }
                    else
                    {
                        i4_ret = APP_CFGR_NO_ACTION;
                        break;
                    }

                    i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
#else
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
#endif
                }
            }
            break;
        }
        case APP_CFG_GRPID_DISP:
        {
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_DISP_GAMMA:
                    i4_ret = acfg_get_int16_by_idx(IDX_DISP_GAMMA,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                case APP_CFG_RECID_DISP_BACK_LIGHT:
                    i4_ret = acfg_get_int16_by_idx(IDX_DISP_BACK_LIGHT,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                case APP_CFG_RECID_DISP_ADP_BACK_LIGHT:
                    i4_ret = acfg_get_int16_by_idx(IDX_DISP_ADP_BACK_LIGHT,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_video_set(
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    UINT16          ui2_elem_idx = 0;
    UINT8           ui1_input;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 2: Get the index */
    i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);


    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_VIDEO:
        {
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_VID_BRI:
                {
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        break;
                    }
                    i4_ret = acfg_set_int16_by_idx(IDX_VID_BRI,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_CNT:
                {
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        break;
                    }
                    i4_ret = acfg_set_int16_by_idx(IDX_VID_CNT,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_SAT:
                {
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        break;
                    }
                    i4_ret = acfg_set_int16_by_idx(IDX_VID_SAT,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_HUE:
                {
                    if(a_cfg_cust_get_pqbypass_status() == 1)
                    {
                        break;
                    }
                    i4_ret = acfg_set_int16_by_idx(IDX_VID_HUE,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_SHP:
                {
                    i4_ret = acfg_set_int16_by_idx(IDX_VID_SHP,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_PIC_MODE:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_PIC_MODE, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_CLR_TEMP:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_TEMP, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_GAIN_R:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_GAIN_R, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_GAIN_G:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_GAIN_G, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_GAIN_B:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_GAIN_B, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_OFFSET_R:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_OFFSET_R, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_OFFSET_G:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_OFFSET_G, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_CLR_OFFSET_B:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CLR_OFFSET_B, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_CUSTOM_DIMMING:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_DIMMING, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_CUSTOM_DCR:
                {
                    if(acfg_is_backlight_control_enable())
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_DCR_IDX, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                    }
                }
                    break;
                case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                }
                    break;
                case APP_CFG_RECID_VID_CONTRAST_EN:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_SUPER_RESOLUTION_EX:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_EDGE_ENHANCEMENT:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_VARIABLE_REFRESH_RATE, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_GAME_HDR:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_GAME_HDR, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_PEAK_LUMINANCE:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_ETOF:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_ETOF, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_FILM_MAEKER_MODE:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_FILM_MAKER_MODE, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_EN_VIEW_ANGLE:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_GAME_LOW_LATENCY:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_JUDDER_REDUCTION:
                    {
                        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx, i2_val);
                        ACFG_CHK_FAIL (i4_ret, i4_ret);
                        break;
                    }
                case APP_CFG_RECID_VID_CONTOUR_SMOTHING:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }

                case APP_CFG_RECID_VID_LOCAL_CONTRAST:
                {
                    i4_ret = acfg_set_int16_by_idx (IDX_VID_LOCAL_CONTRAST, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_CLEAR_ACTION:
                {
                    //DBG_LOG_PRINT(("[ClearAction]{%s: %s: %d} i2_val=%d\n", __FILE__, __FUNCTION__,__LINE__, i2_val));
                    i4_ret = acfg_set_int16_by_idx (IDX_CLEAR_ACTION, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_CUSTOM_H_SIZE:
                    i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_H_SIZE, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    sys_asp_ratio_set_h_size(i2_val);
                    break;
                case APP_CFG_RECID_VID_CUSTOM_V_SIZE:
                    i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_V_SIZE, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL (i4_ret, i4_ret);
                    sys_asp_ratio_set_v_size(i2_val);
                    break;
                case APP_CFG_RECID_VID_POS_H:
                {
                    sys_asp_ratio_set_h_pos(i2_val);
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
                }
                case APP_CFG_RECID_VID_POS_V:
                {
                    sys_asp_ratio_set_v_pos(i2_val);
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
                }
                case  APP_CFG_RECID_VID_CLR_HUE_R:
                case  APP_CFG_RECID_VID_CLR_HUE_G:
                case  APP_CFG_RECID_VID_CLR_HUE_B:
                case  APP_CFG_RECID_VID_CLR_SAT_R:
                case  APP_CFG_RECID_VID_CLR_SAT_G:
                case  APP_CFG_RECID_VID_CLR_SAT_B:
                case  APP_CFG_RECID_VID_CLR_BRI_R:
                case  APP_CFG_RECID_VID_CLR_BRI_G:
                case  APP_CFG_RECID_VID_CLR_BRI_B:
                case  APP_CFG_RECID_VID_CLR_HUE_C:
                case  APP_CFG_RECID_VID_CLR_HUE_M:
                case  APP_CFG_RECID_VID_CLR_HUE_Y:
                case  APP_CFG_RECID_VID_CLR_SAT_C:
                case  APP_CFG_RECID_VID_CLR_SAT_M:
                case  APP_CFG_RECID_VID_CLR_SAT_Y:
                case  APP_CFG_RECID_VID_CLR_BRI_C:
                case  APP_CFG_RECID_VID_CLR_BRI_M:
                case  APP_CFG_RECID_VID_CLR_BRI_Y:
                case  APP_CFG_RECID_VID_REDUCE_BLUR:
                case  APP_CFG_RECID_VID_RED:
                case  APP_CFG_RECID_VID_GREEN:
                case  APP_CFG_RECID_VID_BLUE:
                case  APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS:
                case  APP_CFG_RECID_VID_PRE_PIC_CHG:
                case  APP_CFG_RECID_CUST_PIC_COPY_BASE:
                case  APP_CFG_RECID_VID_11_POINT_GAIN:
                case  APP_CFG_RECID_VID_11_POINT_GAIN_RED:
                case  APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:
                case  APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:
                case  APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                case  APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                case  APP_CFG_RECID_VID_CUST_CLR_GAIN_B:
                case  APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                case  APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                case  APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:
                    {
                        UINT16  ui2_rec_idx = IDX_CLR_HUE_R;
                        switch (ui2_cfg_rec)
                        {
                            case APP_CFG_RECID_VID_CLR_HUE_R:
                                ui2_rec_idx = IDX_CLR_HUE_R;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_G:
                                ui2_rec_idx = IDX_CLR_HUE_G;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_B:
                                ui2_rec_idx = IDX_CLR_HUE_B;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_R:
                                ui2_rec_idx = IDX_CLR_SAT_R;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_G:
                                ui2_rec_idx = IDX_CLR_SAT_G;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_B:
                                ui2_rec_idx = IDX_CLR_SAT_B;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_R:
                                ui2_rec_idx = IDX_CLR_BRI_R;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_G:
                                ui2_rec_idx = IDX_CLR_BRI_G;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_B:
                                ui2_rec_idx = IDX_CLR_BRI_B;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_C:
                                ui2_rec_idx = IDX_CLR_HUE_C;
                                break;

                            case APP_CFG_RECID_VID_CLR_HUE_M:
                                ui2_rec_idx = IDX_CLR_HUE_M;
                                break;
                            #if 0
                            case APP_CFG_RECID_VID_CLR_HUE_C:
                                ui2_rec_idx = IDX_CLR_HUE_C;
                                break;
                            #endif
                            case APP_CFG_RECID_VID_CLR_HUE_Y:
                                ui2_rec_idx = IDX_CLR_HUE_Y;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_C:
                                ui2_rec_idx = IDX_CLR_SAT_C;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_M:
                                ui2_rec_idx = IDX_CLR_SAT_M;
                                break;

                            case APP_CFG_RECID_VID_CLR_SAT_Y:
                                ui2_rec_idx = IDX_CLR_SAT_Y;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_C:
                                ui2_rec_idx = IDX_CLR_BRI_C;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_M:
                                ui2_rec_idx = IDX_CLR_BRI_M;
                                break;

                            case APP_CFG_RECID_VID_CLR_BRI_Y:
                                ui2_rec_idx = IDX_CLR_BRI_Y;
                                break;

                            case APP_CFG_RECID_VID_REDUCE_BLUR:
                                ui2_rec_idx = IDX_REDUCE_BLUR;
                                break;

                            case APP_CFG_RECID_VID_RED:
                                ui2_rec_idx = IDX_RED;
                                break;

                            case APP_CFG_RECID_VID_GREEN:
                                ui2_rec_idx = IDX_GREEN;
                                break;

                            case APP_CFG_RECID_VID_BLUE:
                                ui2_rec_idx = IDX_BLUE;
                                break;

                            case APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS:
                                ui2_rec_idx = IDX_CUST_PIC_EXIST_STATUS;
                                break;

                            case APP_CFG_RECID_VID_PRE_PIC_CHG:
                                ui2_rec_idx = IDX_PRE_PIC_CHG;
                                break;

                            case APP_CFG_RECID_CUST_PIC_COPY_BASE:
                                ui2_rec_idx = IDX_CUST_PIC_COPY_BASE;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN:
                                ui2_rec_idx = IDX_11_POINT_GAIN;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN_RED:
                                ui2_rec_idx = IDX_11_POINT_GAIN_RED;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:
                                ui2_rec_idx = IDX_11_POINT_GAIN_GREEN;
                                break;

                            case APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:
                                ui2_rec_idx = IDX_11_POINT_GAIN_BLUE;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                                ui2_rec_idx = IDX_CUST_CLR_GAIN_R;
                                break;
                            case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                                ui2_rec_idx = IDX_CUST_CLR_GAIN_G;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:
                                ui2_rec_idx = IDX_CUST_CLR_GAIN_B;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                                ui2_rec_idx = IDX_CUST_CLR_OFFSET_R;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                                ui2_rec_idx = IDX_CUST_CLR_OFFSET_G;
                                break;

                            case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:
                                ui2_rec_idx = IDX_CUST_CLR_OFFSET_B;
                                break;
                             default:
                                break;

                    }

                    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                }
                    break;
#ifndef APP_ODM_ONE_IMG_SUPPORT
#ifdef APP_CFG_FAC_CLR_TEMP
                case APP_CFG_RECID_VID_FAC_GAIN_R:
                case APP_CFG_RECID_VID_FAC_GAIN_G:
                case APP_CFG_RECID_VID_FAC_GAIN_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_GAIN_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_GAIN_R:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_GAIN_G:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_GAIN_B:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }

                    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_FAC_OFFSET_R:
                case APP_CFG_RECID_VID_FAC_OFFSET_G:
                case APP_CFG_RECID_VID_FAC_OFFSET_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_OFFSET_R:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_G:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_B:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }

                    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,ui2_elem_idx,i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
#endif
#endif
                case APP_CFG_RECID_VID_CUST_GAMMA:
                    {
                        UINT16  ui2_rec_idx = IDX_CUST_GAMMA;
                        ui2_rec_idx = IDX_CUST_GAMMA;

                        i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,
                                                       ui2_elem_idx,
                                                       i2_val);
                        ACFG_CHK_FAIL(i4_ret, i4_ret);
                    }
                    break;
                case APP_CFG_RECID_VID_COLOR_SPACE:
                    {
                        a_cfg_cust_set_color_space_value(i2_val);
                    }
                    break;
                default:
                {
#ifdef APP_ODM_ONE_IMG_SUPPORT
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_GAIN_R;

                    if (a_app_cfg_fac_clr_temp() == FALSE)
                    {
                        i4_ret = APP_CFGR_NO_ACTION;
                        break;
                    }

                    if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_R)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_R;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_G)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_G;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_B)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_B;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_R)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_G)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_G;
                    }
                    else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_B)
                    {
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_B;
                    }
                    else
                    {
                        i4_ret =  APP_CFGR_NO_ACTION;
                        break;
                    }

                    i4_ret =  APP_CFGR_OK;
                    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
#else
                    i4_ret =  APP_CFGR_NO_ACTION;
                    break;
#endif
                }
            }
            break;
        }
        case APP_CFG_GRPID_DISP:
        {
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_DISP_GAMMA:
                    i4_ret = acfg_set_int16_by_idx(IDX_DISP_GAMMA,
                                                   ui2_elem_idx,
                                                   i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                case APP_CFG_RECID_DISP_BACK_LIGHT:
                    i4_ret = acfg_set_int16_by_idx(IDX_DISP_BACK_LIGHT,
                                                   ui2_elem_idx,
                                                   i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                case APP_CFG_RECID_DISP_ADP_BACK_LIGHT:
                    i4_ret = acfg_set_int16_by_idx(IDX_DISP_ADP_BACK_LIGHT,
                                                   ui2_elem_idx,
                                                   i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        break;
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}

INT32 acfg_cust_video_pos_reset (UINT16 ui2_id)
{
    INT32       i4_ret;
    UINT16      ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    HANDLE_T    h_scc_comp;
    UINT16      ui2_drv_min_val = 0, ui2_drv_max_val = 0, ui2_drv_mid_val = 0;
    INT16       i2_app_val, i2_app_min, i2_app_max;
    INT16       i2_pos;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_input_id;
    VSH_SRC_RESOLUTION_INFO_T   t_timing;

    c_memset (&t_timing, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_timing(s_disp_name, &t_timing);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get SCC handle by display name. */
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                  h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

    if (ui2_cfg_rec == APP_CFG_RECID_VID_POS_H)
    {
        i2_app_val=ACFG_VID_POS_H_DEF;
    }
    else
    {
        i2_app_val=ACFG_VID_POS_V_DEF;
    }
    i4_ret = a_cfg_av_get_min_max(ui2_id, &i2_app_min, &i2_app_max);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (i2_app_val > i2_app_max)
    {
        i2_app_val = i2_app_max;
    }
    if (i2_app_val < i2_app_min)
    {
        i2_app_val = i2_app_min;
    }
    /* Get driver related values. */
    if (ui2_cfg_rec == APP_CFG_RECID_VID_POS_H)
    {
        i4_ret = c_scc_vid_get_h_position (h_scc_comp,
                                           &ui2_drv_min_val,
                                           &ui2_drv_max_val,
                                           NULL);
        if(i4_ret != SMR_OK)
        {
            DBG_LOG_PRINT(("<ACFG> The min/max/pos of h-pos in driver is wrong.\n"));
            return APP_CFGR_INTERNAL_ERR;
        }
    }
    else
    {
        i4_ret = c_scc_vid_get_v_position (h_scc_comp,
                                           &ui2_drv_min_val,
                                           &ui2_drv_max_val,
                                           NULL);
        if(i4_ret != SMR_OK)
        {
            DBG_LOG_PRINT(("<ACFG> The min/max/pos of v-pos in driver is wrong.\n"));
            return APP_CFGR_INTERNAL_ERR;
        }
    }

    /* Get middle driver value. */
    ui2_drv_mid_val = (ui2_drv_min_val + ui2_drv_max_val) / 2;

    /* Always set H/V pos to default if updating SUB. */
    if (c_strcmp(s_disp_name, SN_PRES_SUB_DISPLAY) == 0)
    {
        i2_pos = ui2_drv_mid_val;
    }
    else
    {
        if (ui2_cfg_rec == APP_CFG_RECID_VID_POS_H)
        {
            /* AP 1 step = driver 2 step. */
            i2_pos = ui2_drv_mid_val + (i2_app_val - ACFG_VID_POS_H_DEF);
        }
        else
        {
            /* AP 1 step = driver 2 step. */
            i2_pos = ui2_drv_mid_val + (i2_app_val - ACFG_VID_POS_V_DEF);
        }
    }

    if (i2_pos > ui2_drv_max_val)
    {
        DBG_ERROR(("<ACFG> pos exceed max value.\n"));
        i2_pos = ui2_drv_max_val;
    }
    if (i2_pos < ui2_drv_min_val)
    {
        DBG_ERROR(("<ACFG> pos exceed min value.\n"));
        i2_pos = ui2_drv_min_val;
    }
    /* set to driver */
    if (ui2_cfg_rec == APP_CFG_RECID_VID_POS_H)
    {
        i4_ret = c_scc_vid_set_h_position (h_scc_comp, i2_pos);
    }
    else
    {

        i4_ret = c_scc_vid_set_v_position (h_scc_comp, i2_pos);
    }
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_update_based_pic_mode(VOID)
{
#if 0
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(INT16);
    INT16                        i2_idx = 0;

    INT32       i4_ret;
    INT16       i2_picture_mode;
    INT16       i2_picture_mode_base;

    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_picture_mode);
    ACFG_LOG_ON_FAIL(i4_ret);

    if (i2_picture_mode < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        i2_idx =i2_picture_mode;
    }
    else
    {

        i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE), &i2_picture_mode_base);
        ACFG_LOG_ON_FAIL(i4_ret);
        i2_idx = i2_picture_mode_base;
    }

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_TYPE_COPY_PIC_MODE_NOTIFY;
    t_op_info.u.t_vid_set_info.b_store = TRUE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&i2_idx;
    t_op_info.u.t_vid_set_info.z_size = z_size;

    c_dbg_secure_stmt("\n[ACFG]Base Picture Mode %d\n", i2_idx);

    /* set to driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
#endif
return APP_CFGR_OK;

}


extern INT32 acfg_cust_video_update(
    UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    HANDLE_T        h_scc_comp = NULL_HANDLE;
    INT16           i2_app_val = 0;
    BOOL            b_is_support = FALSE;
    UINT8           ui1_reduce_blur_value = 0;
    INT16           i2_val = 0;
    //TV_WIN_ID_T     e_tv_win_id = 0;

    /* Get SCC handle by display name. */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp){
    case APP_CFG_GRPID_DISP:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    case APP_CFG_GRPID_VIDEO:
    {
        switch(ui2_cfg_rec)
        {
            case APP_CFG_RECID_VID_GAME_MODE:
                ACFG_DBG_INFO(" APP_CFG_RECID_VID_GAME_MODE no need update,will use GAME LOW LATENCY instead\r\n");
                break;

            case APP_CFG_RECID_VID_CLEAR_ACTION:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION), &i2_val);

                //DBG_LOG_PRINT(("[ACFG][ClearAction]{%s: %s: %d} ACFG.i2_val=%d\n", __FILE__, __FUNCTION__,__LINE__, i2_val));

            #if 1
                // If cannot turn on, force off to driver...
                BOOL bClearActionCanTurnOn = a_cfg_cust_ClaerAction_if_can_turn_on();
                //DBG_LOG_PRINT(("[ACFG][ClearAction]{%s: %s: %d} a_cfg_cust_ClaerAction_if_can_turn_on()=> %d\n", __FILE__, __FUNCTION__,__LINE__, bClearActionCanTurnOn ));
                if( FALSE == bClearActionCanTurnOn )
                {
                    DBG_LOG_PRINT(("[ACFG][ClearAction]{%s: %s: %d} Cannot turn on! Force val=0!\n", __FILE__, __FUNCTION__,__LINE__ ));
                    i2_val = 0;
                }

            #else
                if ((a_cfg_cust_is_variable_refresh_rate_support() == TRUE)&&(a_cfg_cust_is_support_progaming_engine() == TRUE))
                {
                    INT16 i2_vrr = 0;
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_vrr);

                    if(i2_vrr == ACFG_CUST_COMMON_ON)
                    {
                        i2_val = 0;
                    }
                }
                //note: no signal need close clear action
                i4_ret = nav_get_focus_id(&e_tv_win_id);
                if((i4_ret == 0) && (TRUE == nav_is_signal_loss(e_tv_win_id)))
                {
                    i2_val = 0;
                }
            #endif

                if( a_cfg_cust_oled_support() == TRUE )
                {
                    a_cfg_cust_drv_set_oled_cmo((UINT8)i2_val);
                }
                else
                {
                    //DBG_LOG_PRINT(("[ACFG][ClearAction]{%s: %s: %d} a_cfg_cust_get_support_clear_aciton() => %d\n", __FILE__, __FUNCTION__,__LINE__, a_cfg_cust_get_support_clear_aciton()));
                    if (a_cfg_cust_get_support_clear_aciton() == TRUE)
                    {
                        //DBG_LOG_PRINT(("[ACFG][ClearAction]{%s: %s: %d} Call driver(%d)\n", __FILE__, __FUNCTION__,__LINE__, i2_val));
                        VIZIO_CLEAR_ACTION_D_SET(i2_val);
                    }
                }
            }
            break;

            case APP_CFG_RECID_VID_CONTRAST_EN:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN), &i2_val);
                a_cfg_cust_drv_set_contrast_enhancement((UINT8)i2_val);
            }
            break;
            case APP_CFG_RECID_VID_SUPER_RESOLUTION_EX:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX), &i2_val);
                a_cfg_cust_drv_set_super_resolution((UINT8)i2_val);
            }
            break;
            case APP_CFG_RECID_VID_EDGE_ENHANCEMENT:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EDGE_ENHANCEMENT), &i2_val);
                a_cfg_cust_drv_set_edge_enhancement((UINT8)i2_val);
            }
                break;
            case APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION), &i2_val);
                a_cfg_cust_drv_set_motion_blur_reduction((UINT8)i2_val);
            }
            break;

            case APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_val);

            #if 0//NEW modefied: MVV-6054
                //When you turn VRR off at the source (but TV says VRR On), Enhanced Viewing Angle should turn On, but currently (f/w v1.10.9.2) it doesn't. Viewing Angle is off.
                if(i2_val == ACFG_CUST_COMMON_OFF)
                {
                    //DBG_LOG_PRINT(("%s_%d ---------------APP_CFG_RECID_VID_EN_VIEW_ANGLE set--------------------\n",__FUNCTION__,__LINE__));
                    //DBG_LOG_PRINT( ("------XXX-----[ACFG]  %s %d  ::APP_CFG_RECID_VID_EN_VIEW_ANGLE:::type:%d  a_acfg_cust_get_video_type():%d\n",__FUNCTION__,__LINE__,a_acfg_cust_get_dynamic_range(),a_acfg_cust_get_video_type()));
                    //a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), (INT16)ACFG_CUST_COMMON_ON);
                    acfg_custom_set_crnt_pic_mode_all_dynamic_en_view_angle_for_on();
                }
            #endif
                //if ( i2_g_vrr_set != i2_val)
                {
                    //i2_g_vrr_set = i2_val;
                    a_cfg_cust_drv_set_variable_refresh_rate((UINT8)i2_val);
                }
            }
            break;

            case APP_CFG_RECID_VID_GAME_HDR:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), &i2_val);
                a_cfg_cust_drv_set_game_hdr((UINT8)i2_val);
            }
            break;

            case APP_CFG_RECID_VID_PEAK_LUMINANCE:
            {
                if(a_cfg_cust_oled_support() == TRUE)
                {
                #if 0 // HDR mode don't need call driver
                    if( FALSE == a_cfg_cust_CheckIfPeakLumiCanAdjust() )
                    {
                        DBG_LOG_PRINT(("[ACFG][OLED][PeakLumi]{%s,%d} HDR => No need to call driver\n", __func__, __LINE__ ));
                        break;
                    }
                #endif


                    //0--Low   1--Middle   2--High
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE), &i2_val);

                    ACFG_DEBUG_OLED_LUMI(
                        DBG_LOG_PRINT(("[ACFG][OLED][BACKLIGHT][PeakLumi]{%s,%d} Val:%d\n", __func__, __LINE__, i2_val ));
                    );

                #if(ACFG_CUST_PEAK_LUMI_NEW_SPEC)
                    a_cfg_cust_drv_set_peak_lunminance((UINT8)i2_val);

                #else

                    //MVP-111 MVP-1341
                    INT16 u2_peak_luminance_backlight_tbl[2][3] = {{84, 127, 255}, // SDR  low/middlw/high
                                                                   {84, 127, 255}};// HDR  low/middlw/high
                    UINT8 ui1_type = a_acfg_cust_get_dynamic_range ();
                    INT32 i4_val = 0;


                    //a_cfg_cust_drv_set_peak_lunminance((UINT8)i2_val);

                    if(ui1_type != ACFG_CUST_CONTENT_HDR && ui1_type != ACFG_CUST_CONTENT_SDR)
                    {
                        ui1_type = ACFG_CUST_CONTENT_HDR;//dv hlg use hdr
                    }

                    i4_val = u2_peak_luminance_backlight_tbl[ui1_type][i2_val<3?i2_val:0];   //0--Low   1--Middle  2--High

                    ACFG_DEBUG_BACKLIGHT(
                        DBG_LOG_PRINT(("[ACFG][OLED][BACKLIGHT][LUMI]{%s: %d} acfg_val:%d, HDR_type:%d => Drv_val:%d\n",
                                                        __FUNCTION__, __LINE__, i2_val, ui1_type, i4_val ));
                    );

                    a_cfg_cust_drv_set_oled_panel_gain((UINT8)i4_val);
                #endif
                }
            }
            break;

            case APP_CFG_RECID_VID_OLED_PIXEL_SHIFT:
            {
                UINT8 ui1_val = 0;
                a_cfg_cust_get_oled_pixel_shift_value(&ui1_val);
                //a_cfg_cust_drv_set_oled_pixel_shift(ui1_val);
                i4_ret = a_cfg_cust_drv_set_oled_orbit((BOOL)ui1_val);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
            break;

            case APP_CFG_RECID_VID_ETOF:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_ETOF), &i2_val);
                a_cfg_cust_drv_set_drv_eotf((UINT8)i2_val);
            }
            break;
            case APP_CFG_RECID_VID_FILM_MAEKER_MODE:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FILM_MAEKER_MODE), &i2_val);
                a_cfg_cust_drv_set_drv_film_maker_mode((UINT8)i2_val);
            }
            break;
            case APP_CFG_RECID_VID_EN_VIEW_ANGLE:
            {
                if( a_cfg_cust_en_view_angle_support() == FALSE )
                {
                    ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG]{%s:%d} Warning: NOT Support enhanced_view_angle!!\n", __FUNCTION__, __LINE__)); );
                    break;
                }

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), &i2_val);

                if( i2_val != 0 ) // Turn on
                {
                    if( a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn() == FALSE )
                    {
                        ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG]{%s:%d} Warning: Cannot turn on enhanced_view_angle!! Force to off\n", __FUNCTION__, __LINE__)); );
                        i2_val = 0;
                    }
                }

                a_cfg_cust_drv_set_enhanced_viewing_angle((UINT8)i2_val);
            }
            break;
            case APP_CFG_RECID_VID_GAME_LOW_LATENCY:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_val);
                a_cfg_cust_drv_set_game_low_latency((UINT8)i2_val);
            }
            break;
            case APP_CFG_RECID_VID_JUDDER_REDUCTION:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION), &i2_val);
                a_cfg_cust_drv_set_judder_reduction((UINT8)i2_val);
            }
            break;

            case APP_CFG_RECID_VID_LOCAL_CONTRAST:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST), &i2_val);
#if !( defined(MT5695_MODEL) && defined(MT5695_FAMILY_S) )
                if (a_acfg_cust_get_dynamic_range () == ACFG_CUST_CONTENT_DV)
                {
                    i2_val = 0;
                }
#endif
                a_cfg_cust_drv_set_local_contrast((UINT8)i2_val);
                break;
            }

            case APP_CFG_RECID_VID_CONTOUR_SMOTHING:
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING), &i2_val);
                if(a_acfg_cust_is_gll_enable() == TRUE)
                {
                    i2_val = 0;
                }
                a_cfg_cust_drv_set_contour_smoothing((UINT8)i2_val);
                break;
            }
            case APP_CFG_RECID_VID_HDMI_MODE:
                return APP_CFGR_OK;

            case APP_CFG_RECID_VID_CUST_FULL_COLOR_444:
            {
                //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s,%d)} \n", __FUNCTION__, __LINE__ )); );

                // Check input_source
                if( FALSE == acfg_cust_Is_CurSrcHDMI() )
                {
                    ACFG_DEBUG_FULL_COLOR444(
                        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Non-HDMI skip call driver\n", __FUNCTION__, __LINE__)); );
                    break;
                }

                // Get setting ...
                UINT8 ui1_full_color_444_value = 0;
                UINT32 i32Ret = a_cfg_cust_get_full_color_444_ForCurHDMI(&ui1_full_color_444_value);
                if( i32Ret != APP_CFGR_OK )
                {
                    DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: a_cfg_cust_get_full_color_444_ForCurHDMI() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
                    //break;
                    ui1_full_color_444_value = 0;
                }

                ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui1_full_color_444_value:%d\n", __FUNCTION__, __LINE__, ui1_full_color_444_value)); );

                if( ui1_full_color_444_value )
                {
                    BOOL bIs_FullColor444_CanTurnOn = acfg_cust_FullColor444_IfCanTurnOn();
                    if( !bIs_FullColor444_CanTurnOn ) // Cannot turn on
                    {
                        ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Can not turn on! Force to off\n", __FUNCTION__, __LINE__)); );
                        ui1_full_color_444_value = 0;
                    }
                }

                //a_cfg_cust_drv_set_full_color_444( (ui1_full_color_444_value ? SCC_VID_HDMI_MODE_GRAPHIC : SCC_VID_HDMI_MODE_AUTO) );
                a_cfg_cust_drv_set_full_color_444( ui1_full_color_444_value );

                break;
            }
            case APP_CFG_RECID_VID_CUST_GAMMA:
            {
                UINT32 ui4_val = 0;
                DRV_CUST_OPERATION_INFO_T t_op_info;

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA), &i2_val);
                ui4_val = i2_val;

                DBG_LOG_PRINT(("\n <ACFG>CUST_GAMMA(update) value[%d]: \n",ui4_val));

                SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

                t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
                t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_REMAP_GAMMA;
                t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(&ui4_val);
                t_op_info.u.t_vid_set_info.z_size = sizeof(UINT32);
                t_op_info.u.t_vid_set_info.b_store = FALSE;

                i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size);
                DBG_LOG_PRINT(("%s_%d i4_ret:%d \n",__FUNCTION__,__LINE__,i4_ret));

               // a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));

            }
            break;
            case APP_CFG_RECID_VID_DI_FILM_MODE:
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE), &i2_val);
                ACFG_LOG_ON_FAIL(i4_ret);
                a_cfg_custom_update_film_mode((UINT8)i2_val);
                break;
            }
        case APP_CFG_RECID_VID_BLACK_STRETCH:
        case APP_CFG_RECID_VID_WHITE_STRETCH:
            {
                ACFG_DBG_INFO("No Need Update BLACK_STRETCH/WHITE_STRETCH \r\n");
                break;
            }
        case APP_CFG_RECID_SHOP_MODE:
        case APP_CFG_RECID_PIC_MODE:
        {
            INT16 i2_pic_base = 0;

            /* Update picture mode to driver */
            h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                         h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

            i4_ret = a_cfg_av_get(ui2_id, &i2_app_val);
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),
                                    &i2_pic_base);
            ACFG_LOG_ON_FAIL(i4_ret);
            ACFG_DBG_PRINT("update PIC_MODE i2_app_val : %d,i2_pic_base :%d \r\n",i2_app_val,i2_pic_base);

            ACFG_DEBUG_PIC_MODE(
                DBG_LOG_PRINT(("[ACFG][PIC_MODE]{%s: %d} i2_app_val:%d, i2_pic_base:%d\n", __FUNCTION__, __LINE__, i2_app_val, i2_pic_base ));
            );


            if(i2_app_val >= ACFG_PRE_SET_PIC_MODE_NUM)
            {
                i2_app_val = i2_pic_base;
            }
            else if(i2_pic_base >= ACFG_CUST_COPY_PIC_MODE_BASE)
            {
                i2_app_val = i2_pic_base - ACFG_CUST_COPY_PIC_MODE_BASE;
            }

            i4_ret = c_scc_vid_set_pic_mode (h_scc_comp, (SCC_VID_PIC_MODE_T)(i2_app_val));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Game Mode */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Film Mode */
        #ifdef APP_DI_SUPPORT
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
            ACFG_LOG_ON_FAIL(i4_ret);
        #endif

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Noise Reduction */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* MPEG NR */
#ifdef APP_MPEG_NR_SUPPORT
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR));
            ACFG_LOG_ON_FAIL(i4_ret);
#endif
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Color Enhancement */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Adaptive Luma */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* as update Luma should also update BLACK_STRETCH & WHITE_STRETCH*/
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLACK_STRETCH));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WHITE_STRETCH));
            ACFG_LOG_ON_FAIL(i4_ret);


            /* DCR and Lightsensor use the same process, so only update dcr. */
            ACFG_DEBUG_BACKLIGHT(
                DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call a_cfg_av_update(APP_CFG_RECID_VID_CUSTOM_DCR)\n", __FUNCTION__, __LINE__ ));
            );
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Smart Dimming */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Smooth Motion Effect */
    #ifdef APP_MJC_SUPPORT
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
            ACFG_LOG_ON_FAIL(i4_ret);
        #if(!ACFG_CUST_MEMC_NEW_METHOD)
            /* Real Cinema Mode */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE));
            ACFG_LOG_ON_FAIL(i4_ret);
        #endif
    #endif

            /* Ambient Light Sensor */
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
            ACFG_LOG_ON_FAIL(i4_ret);

             /* cust gamma */
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA));

            /* clear action */
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));

            /* color space*/
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_COLOR_SPACE));
            i4_ret = a_cfg_custom_is_reduce_blur_support(&b_is_support);
            ACFG_LOG_ON_FAIL(i4_ret);
            if (b_is_support)
            {
                i4_ret = a_cfg_custom_get_reduce_blur(&ui1_reduce_blur_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = a_cfg_custom_update_reduce_blur(ui1_reduce_blur_value);
                ACFG_LOG_ON_FAIL(i4_ret);
            }

            i4_ret = a_cfg_update_based_pic_mode();
            ACFG_LOG_ON_FAIL(i4_ret);

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EDGE_ENHANCEMENT));

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE));

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED));
            ACFG_LOG_ON_FAIL(i4_ret);

            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);

            // MEMC ...
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION));

        }
            break;
        case  APP_CFG_RECID_VID_CLR_HUE_R:
        case  APP_CFG_RECID_VID_CLR_HUE_G:
        case  APP_CFG_RECID_VID_CLR_HUE_B:
        case  APP_CFG_RECID_VID_CLR_HUE_C:
        case  APP_CFG_RECID_VID_CLR_HUE_M:
        case  APP_CFG_RECID_VID_CLR_HUE_Y:
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
            break;
        case  APP_CFG_RECID_VID_CLR_SAT_R:
        case  APP_CFG_RECID_VID_CLR_SAT_G:
        case  APP_CFG_RECID_VID_CLR_SAT_B:
        case  APP_CFG_RECID_VID_CLR_SAT_C:
        case  APP_CFG_RECID_VID_CLR_SAT_M:
        case  APP_CFG_RECID_VID_CLR_SAT_Y:
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
            break;
        case  APP_CFG_RECID_VID_CLR_BRI_R:
        case  APP_CFG_RECID_VID_CLR_BRI_G:
        case  APP_CFG_RECID_VID_CLR_BRI_B:
        case  APP_CFG_RECID_VID_CLR_BRI_C:
        case  APP_CFG_RECID_VID_CLR_BRI_M:
        case  APP_CFG_RECID_VID_CLR_BRI_Y:
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
            break;
#ifdef NEVER
            {
                UINT16  ui2_rec_idx = IDX_CLR_HUE_R;
                UINT8   ui1_offset= ACFG_CLR_TUNER_OFFSET_MID_VALUE;
                UINT8   ui1_color = 0;
                UINT8   ui1_module = 0;
                UINT8   ui1_odm_id = 0;
                a_cfg_custom_get_odm_idx(&ui1_odm_id);
//              if (ui1_odm_id == 2)        //Del Foxconn Tommy 20180408
                if ((ui1_odm_id == 2) || (ui1_odm_id == 4))     //Add Foxconn Tommy 20180408
                {
                    a_cfg_cust_get_color_tune_offset(&ui1_offset);
                }
                switch (ui2_cfg_rec)
                {
                    case APP_CFG_RECID_VID_CLR_HUE_R:
                        ui2_rec_idx = IDX_CLR_HUE_R;
                        ui1_color = CLR_TUNER_COL_RED;
                        ui1_module = CLR_TUNER_ROW_HUE;
                        break;

                    case APP_CFG_RECID_VID_CLR_HUE_G:
                        ui2_rec_idx = IDX_CLR_HUE_G;

                        ui1_color = CLR_TUNER_COL_GREEN;
                        ui1_module = CLR_TUNER_ROW_HUE;
                        break;

                    case APP_CFG_RECID_VID_CLR_HUE_B:
                        ui2_rec_idx = IDX_CLR_HUE_B;

                        ui1_color = CLR_TUNER_COL_BLUE;
                        ui1_module = CLR_TUNER_ROW_HUE;
                        break;

                    case APP_CFG_RECID_VID_CLR_SAT_R:
                        ui2_rec_idx = IDX_CLR_SAT_R;

                        ui1_color = CLR_TUNER_COL_RED;
                        ui1_module = CLR_TUNER_ROW_SATURATION;
                        break;

                    case APP_CFG_RECID_VID_CLR_SAT_G:
                        ui2_rec_idx = IDX_CLR_SAT_G;

                        ui1_color = CLR_TUNER_COL_GREEN;
                        ui1_module = CLR_TUNER_ROW_SATURATION;
                        break;

                    case APP_CFG_RECID_VID_CLR_SAT_B:
                        ui2_rec_idx = IDX_CLR_SAT_B;

                        ui1_color = CLR_TUNER_COL_BLUE;
                        ui1_module = CLR_TUNER_ROW_SATURATION;
                        break;

                    case APP_CFG_RECID_VID_CLR_BRI_R:
                        ui2_rec_idx = IDX_CLR_BRI_R;

                        ui1_color  =  CLR_TUNER_COL_RED;
                        ui1_module =  CLR_TUNER_ROW_BRIGHTNESS;
                        break;

                    case APP_CFG_RECID_VID_CLR_BRI_G:
                        ui2_rec_idx = IDX_CLR_BRI_G;

                        ui1_color  =  CLR_TUNER_COL_GREEN;
                        ui1_module =  CLR_TUNER_ROW_BRIGHTNESS;
                        break;

                    case APP_CFG_RECID_VID_CLR_BRI_B:
                        ui2_rec_idx = IDX_CLR_BRI_B;

                        ui1_color  =  CLR_TUNER_COL_BLUE;
                        ui1_module =  CLR_TUNER_ROW_BRIGHTNESS;
                        break;

                    case APP_CFG_RECID_VID_CLR_HUE_C:
                        ui2_rec_idx = IDX_CLR_HUE_C;

                        ui1_color = CLR_TUNER_COL_CYAN;
                        ui1_module = CLR_TUNER_ROW_HUE;
                        break;

                    case APP_CFG_RECID_VID_CLR_HUE_M:
                        ui2_rec_idx = IDX_CLR_HUE_M;

                        ui1_color = CLR_TUNER_COL_MAGENTA;
                        ui1_module = CLR_TUNER_ROW_HUE;
                        break;
                    case APP_CFG_RECID_VID_CLR_HUE_Y:
                        ui2_rec_idx = IDX_CLR_HUE_Y;

                        ui1_color = CLR_TUNER_COL_YELLOW;
                        ui1_module = CLR_TUNER_ROW_HUE;
                        break;

                    case APP_CFG_RECID_VID_CLR_SAT_C:
                        ui2_rec_idx = IDX_CLR_SAT_C;

                        ui1_color = CLR_TUNER_COL_CYAN;
                        ui1_module = CLR_TUNER_ROW_SATURATION;
                        break;

                    case APP_CFG_RECID_VID_CLR_SAT_M:
                        ui2_rec_idx = IDX_CLR_SAT_M;

                        ui1_color = CLR_TUNER_COL_MAGENTA;
                        ui1_module = CLR_TUNER_ROW_SATURATION;
                        break;

                    case APP_CFG_RECID_VID_CLR_SAT_Y:
                        ui2_rec_idx = IDX_CLR_SAT_Y;

                        ui1_color = CLR_TUNER_COL_YELLOW;
                        ui1_module = CLR_TUNER_ROW_SATURATION;
                        break;

                    case APP_CFG_RECID_VID_CLR_BRI_C:
                        ui2_rec_idx = IDX_CLR_BRI_C;

                        ui1_color  =  CLR_TUNER_COL_CYAN;
                        ui1_module =  CLR_TUNER_ROW_BRIGHTNESS;
                        break;

                    case APP_CFG_RECID_VID_CLR_BRI_M:
                        ui2_rec_idx = IDX_CLR_BRI_M;

                        ui1_color  =  CLR_TUNER_COL_MAGENTA;
                        ui1_module =  CLR_TUNER_ROW_BRIGHTNESS;
                        break;

                    case APP_CFG_RECID_VID_CLR_BRI_Y:
                        ui2_rec_idx = IDX_CLR_BRI_Y;

                        ui1_color  =  CLR_TUNER_COL_YELLOW;
                        ui1_module =  CLR_TUNER_ROW_BRIGHTNESS;
                        break;

                     default:
                        break;

            }
            DBG_INFO(("ui2_rec_idx=%d\n", (int)ui2_rec_idx));

            i4_ret = a_cfg_av_get(ui2_id, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_custom_set_pq_exp_color(ui1_color,
                                          ui1_module,
                                          i2_val,
                                          ui1_offset);

            ACFG_CHK_FAIL(i4_ret, i4_ret);
        }
            break;
#endif /* NEVER */
        case  APP_CFG_RECID_VID_REDUCE_BLUR:
            {

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_REDUCE_BLUR), &i2_val);
                a_cfg_custom_update_reduce_blur(i2_val);
            }
            break;
        case  APP_CFG_RECID_VID_RED:
        case  APP_CFG_RECID_VID_GREEN:
        case  APP_CFG_RECID_VID_BLUE:
            {
                INT16  i2ROnOff = 0;
                INT16  i2GOnOff = 0;
                INT16  i2BOnOff = 0;
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), &i2ROnOff);
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), &i2GOnOff);
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), &i2BOnOff);
                i4_ret = a_cfg_custom_set_rgb_on_off((UINT8)i2ROnOff,(UINT8)i2GOnOff,(UINT8)i2BOnOff);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            break;
        case  APP_CFG_RECID_VID_11_POINT_GAIN:
        case  APP_CFG_RECID_VID_11_POINT_GAIN_RED:
        case  APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:
        case  APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:
            {
                a_cfg_cust_drv_set_20_p_wb();
                //cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
            }
            break;
        case APP_CFG_RECID_CLR_GAIN_R:
        case APP_CFG_RECID_CLR_GAIN_G:
        case APP_CFG_RECID_CLR_GAIN_B:
        case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
        case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
        case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:
            {
                SCC_DISP_COLOR_GAIN_T   t_color_gain;
                SM_COMMAND_T            at_sm_cmds[4];
                UINT32                  ui4_i;
                INT32                   i4_drv_val = 0;
                UINT16                  aui2_scc_val[3];
                INT16                   i2_val = 0;
                INT32                   i4_odm_val = 0;

                INT16                   i2_app_val = 0;
                INT16                   i2_odm_min = 0;
                INT16                   i2_odm_max = 0;
                UINT16                  ui2_cfg_rec = APP_CFG_RECID_CLR_GAIN_R;
                INT16                   i2_fac_min;
                INT16                   i2_fac_max;
                INT16                   i2_fac_val = 0;
                UINT8                   ui1_odm_id = 0;
                a_cfg_custom_get_odm_idx(&ui1_odm_id);
                /*
                           1 ---> Amtran;
                           2 ---> TPV
                           3 ---> Wistron;
                           4 ---> Foxconn;
                           5 ---> BOE;
                           6 ---> Innolux;
                       */

                for(ui4_i  = 0; ui4_i < 3; ui4_i++)
                {
                    ui2_cfg_rec = APP_CFG_RECID_CLR_GAIN_R + ui4_i;
                    if((ui1_odm_id == 2)||(ui1_odm_id == 4)||(ui1_odm_id == 6))
                    {
                        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R + ui4_i), &i2_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_cfg_rec), (INT16)i2_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                    }

                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R + ui4_i), &i2_app_val);
                    ACFG_LOG_ON_FAIL(i4_ret);

                    if(i2_app_val != 0)// when main menu value not 0, sum of factory value and main menu value
                    {
                        _acfg_get_acture_clr_gain_offset_minmax(
                                    ui2_cfg_rec,
                                    &i2_odm_min,
                                    &i2_odm_max);


                         /* convert APP  to odm value */
                        i4_ret = _acfg_app2odm((INT16)ACFG_CUST_CLR_GAIN_OFFSET_MIN,
                                    (INT16)ACFG_CUST_CLR_GAIN_OFFSET_MAX,
                                    (INT16)i2_app_val,
                                    (INT32)i2_odm_min,
                                    (INT32)i2_odm_max,
                                    &i4_odm_val);
                        ACFG_LOG_ON_FAIL(i4_ret);

                        i2_val = i4_odm_val;

                         /* convert to scc value */
                        i4_ret = acfg_app2drv((INT16)ACFG_MTK_CLR_RGB_MIN_VALUE,
                                    (INT16)ACFG_MTK_CLR_RGB_MAX_VALUE,
                                    (INT16)i2_val,
                                    (INT32)0,
                                    (INT32)SCC_ATTRIB_VALUE_MAX,
                                    &i4_drv_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                    }
                    else// when main menu value is 0, only factory value effective
                    {

                        a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, ui2_cfg_rec), &i2_fac_val);
                        acfg_video_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_fac_min, &i2_fac_max);
                        DBG_INFO(("\n%s,%d,i2_fac_val %d,i2_fac_min%d,i2_fac_max %d\n",__FUNCTION__,__LINE__,i2_fac_val,i2_fac_min,i2_fac_max));
                        if((i2_fac_val > i2_fac_max) || (i2_fac_val < i2_fac_min)) //if value abnormal, reset to default value
                        {
                            i2_fac_val = (i2_fac_min + i2_fac_max)/2;
                        }
                        /* convert to scc value */
                        i4_ret = acfg_app2drv((INT16)i2_fac_min,
                                    (INT16)i2_fac_max,
                                    (INT16)i2_fac_val,
                                    (INT32)0,
                                    (INT32)SCC_ATTRIB_VALUE_MAX,
                                    &i4_drv_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                    }
                    DBG_INFO(("CLR_GAIN[%d] ("
                    "i2_app_val = %d, "
                    "i4_odm_val = %d,"
                    "i2_odm_min = %d, "
                    "i2_odm_max = %d, "
                    "i4_drv_val = %d, "
                    ")\r\n",
                    ui2_cfg_rec,
                    i2_app_val,
                    i4_odm_val,
                    i2_odm_min,
                    i2_odm_max,
                    i4_drv_val
                    ));
                    aui2_scc_val[ui4_i] = (UINT16)i4_drv_val;
                }

                t_color_gain.ui2_r_gain = aui2_scc_val[0];
                t_color_gain.ui2_g_gain = aui2_scc_val[1];
                t_color_gain.ui2_b_gain = aui2_scc_val[2];

                at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
                at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_DISP;
                at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
                at_sm_cmds[1].u.ps_text     = s_disp_name;
                at_sm_cmds[2].e_code        = SCC_CMD_CODE_DISP_COLOR_GAIN;
                at_sm_cmds[2].u.pv_data     = &t_color_gain;
                at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
                at_sm_cmds[3].u.ui4_data    = 0;

                i4_ret = c_scc_comp_grp_set(at_sm_cmds);
                ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
            }
            break;
        case APP_CFG_RECID_CLR_OFFSET_R:
        case APP_CFG_RECID_CLR_OFFSET_G:
        case APP_CFG_RECID_CLR_OFFSET_B:
        case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
        case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
        case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:
            {
                SCC_DISP_COLOR_GAIN_T   t_color_offset;
                UINT32                  ui4_i;
                INT32                   i4_drv_val = 0;
                INT32                   i4_odm_val = 0;
                UINT16                  aui2_scc_val[3];
                INT16                   i2_val = 0;
                SM_COMMAND_T            at_sm_cmds[4];

                INT16                   i2_app_val = 0;
                INT16                   i2_odm_min = 0;
                INT16                   i2_odm_max = 0;
                UINT16                  ui2_cfg_rec = APP_CFG_RECID_CLR_OFFSET_R;
                INT16                   i2_fac_min;
                INT16                   i2_fac_max;
                INT16                   i2_fac_val = 0;
                UINT8                   ui1_odm_id = 0;
                a_cfg_custom_get_odm_idx(&ui1_odm_id);
                /*
                           1 ---> Amtran;
                           2 ---> TPV
                           3 ---> Wistron;
                           4 ---> Foxconn;
                           5 ---> BOE;
                           6 ---> Innolux;
                       */
                for(ui4_i  = 0; ui4_i < 3; ui4_i++)
                {
                    ui2_cfg_rec = APP_CFG_RECID_CLR_OFFSET_R + ui4_i;
                    if((ui1_odm_id == 2)||(ui1_odm_id == 4)||(ui1_odm_id == 6))
                    {
                        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R + ui4_i), &i2_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_cfg_rec), (INT16)i2_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                    }
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R + ui4_i), &i2_app_val);
                    ACFG_LOG_ON_FAIL(i4_ret);

                    if(i2_app_val != 0)// when main menu value not 0, sum of factory value and main menu value
                    {
                        _acfg_get_acture_clr_gain_offset_minmax(
                                    ui2_cfg_rec,
                                    &i2_odm_min,
                                    &i2_odm_max);
                          /* convert APP to odm value */
                        i4_ret = _acfg_app2odm((INT16)ACFG_CUST_CLR_GAIN_OFFSET_MIN,
                                    (INT16)ACFG_CUST_CLR_GAIN_OFFSET_MAX,
                                    (INT16)i2_app_val,
                                    (INT32)i2_odm_min,
                                    (INT32)i2_odm_max,
                                    &i4_odm_val);
                        ACFG_LOG_ON_FAIL(i4_ret);

                        i2_val = i4_odm_val;

                         /* convert to scc value */
                        i4_ret = acfg_app2drv((INT16)ACFG_MTK_CLR_RGB_MIN_VALUE,
                                    (INT16)ACFG_MTK_CLR_RGB_MAX_VALUE,
                                    (INT16)i2_val,
                                    (INT32) 0,
                                    (INT32)SCC_ATTRIB_VALUE_MAX,
                                    &i4_drv_val);
                         ACFG_LOG_ON_FAIL(i4_ret);
                    }
                    else// when main menu value is 0, only factory value effective
                    {

                        a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, ui2_cfg_rec), &i2_fac_val);
                        acfg_video_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_fac_min, &i2_fac_max);
                        DBG_INFO(("\n%s,%d,i2_fac_val %d,i2_fac_min%d,i2_fac_max %d\n",__FUNCTION__,__LINE__,i2_fac_val,i2_fac_min,i2_fac_max));
                        if((i2_fac_val > i2_fac_max) || (i2_fac_val < i2_fac_min)) //if value abnormal, reset to default value
                        {
                            i2_fac_val = (i2_fac_min + i2_fac_max)/2;
                        }
                        /* convert to scc value */
                        i4_ret = acfg_app2drv((INT16)i2_fac_min,
                                    (INT16)i2_fac_max,
                                    (INT16)i2_fac_val,
                                    (INT32)0,
                                    (INT32)SCC_ATTRIB_VALUE_MAX,
                                    &i4_drv_val);
                        ACFG_LOG_ON_FAIL(i4_ret);
                    }

                    DBG_INFO(("CLR_OFFSET[%d]("
                                            "i2_app_val = %d, "
                                            "i4_odm_val = %d,"
                                            "i2_odm_min = %d, "
                                            "i2_odm_max = %d, "
                                            "i4_drv_val = %d, "
                                            ")\r\n",
                                            ui2_cfg_rec,
                                            i2_app_val,
                                            i4_odm_val,
                                            i2_odm_min,
                                            i2_odm_max,
                                            i4_drv_val
                                            ));
                    aui2_scc_val[ui4_i] = (UINT16)i4_drv_val;
                }

                t_color_offset.ui2_r_gain = aui2_scc_val[0];
                t_color_offset.ui2_g_gain = aui2_scc_val[1];
                t_color_offset.ui2_b_gain = aui2_scc_val[2];

                at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
                at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_DISP;
                at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
                at_sm_cmds[1].u.ps_text     = s_disp_name;
                at_sm_cmds[2].e_code        = SCC_CMD_CODE_DISP_COLOR_OFFSET;
                at_sm_cmds[2].u.pv_data     = &t_color_offset;
                at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
                at_sm_cmds[3].u.ui4_data    = 0;

                i4_ret = c_scc_comp_grp_set(at_sm_cmds);
                ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
            }
                break;
#ifndef APP_ODM_ONE_IMG_SUPPORT
#ifdef APP_CFG_FAC_CLR_TEMP
            case APP_CFG_RECID_VID_FAC_GAIN_R:
            case APP_CFG_RECID_VID_FAC_GAIN_G:
            case APP_CFG_RECID_VID_FAC_GAIN_B:
            {
                INT16   i2_val = 0;

                switch(ui2_cfg_rec)
                {
                case APP_CFG_RECID_VID_FAC_GAIN_R:
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_R), &i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), (INT16)i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_FAC_GAIN_G:
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_G), &i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), (INT16)i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_FAC_GAIN_B:
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_B), &i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), (INT16)i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                default:
                    /* not reachable */
                    break;
                }
                break;
            }
            case APP_CFG_RECID_VID_FAC_OFFSET_R:
            case APP_CFG_RECID_VID_FAC_OFFSET_G:
            case APP_CFG_RECID_VID_FAC_OFFSET_B:
            {
                INT16   i2_val = 0;

                switch(ui2_cfg_rec)
                {
                case APP_CFG_RECID_VID_FAC_OFFSET_R:
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_R), &i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), (INT16)i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_FAC_OFFSET_G:
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_G), &i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), (INT16)i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_FAC_OFFSET_B:
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_B), &i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), (INT16)i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                default:
                    /* not reachable */
                    break;
                }
                break;
            }
#endif
#endif
        case APP_CFG_RECID_SCREEN_MODE:
        case APP_CFG_RECID_SCREEN_MODE_EX:
        {
            INT16                       i2_h_size = 0;
            INT16                       i2_v_size = 0;
            INT16                       i2_h_pos = 0;
            INT16                       i2_v_pos = 0;
            UINT8                       ui1_input_id = 0;
            HANDLE_T                    h_svctx;
            SCC_VID_SCREEN_MODE_T       e_scr_mode;
            ISL_REC_T                   t_isl_rec;
            SVL_REC_T                   t_svl_rec;
            BOOL                        b_svl_found = FALSE;
            BOOL                        b_dig_tv = FALSE;
            SCC_VID_OVER_SCAN_CLIPPER_T t_overscan = {0,0,0,0};
            UINT16                      ui2_idx;
            SVCTX_ATOMIC_CMD_T          at_cmds[3];
            SIZE_T                      z_size = 0;

#ifdef SYS_OVERRIDE_DISP_REGION_SUPPORT
            extern VOID sys_asp_ratio_set_mmp_status(BOOL b_mmp_full_screen);
            extern BOOL a_mmp_is_video_full_screen(VOID);

            sys_asp_ratio_set_mmp_status(a_mmp_is_video_full_screen());
#endif
            i4_ret = acfg_video_update_check_scr_mode(s_disp_name, &e_scr_mode);
            ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
            if (i4_ret != APP_CFGR_OK) {
                break;
            }

            i4_ret = _get_hv_size(s_disp_name, &i2_h_size, &i2_v_size);
            ACFG_LOG_ON_FAIL(i4_ret);

            sys_asp_ratio_set_h_size(i2_h_size);
            sys_asp_ratio_set_v_size(i2_v_size);

            at_cmds[0].t_type  = SVCTX_COMMON_SET_ATOMIC_SCRN_MODE;
            at_cmds[0].pv_data = (VOID*)((UINT32)e_scr_mode);
            ui2_idx = 1;

            i4_ret = _get_overscan_with_h_v_size (s_disp_name, &t_overscan);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
            {
                acfg_get_crnt_svl_rec(&t_svl_rec, &b_svl_found);
                if (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG ||
                    b_svl_found==FALSE)
                {
                    b_dig_tv = FALSE;
                }
                else
                {
                    b_dig_tv = TRUE;
                }
            }

            if (b_dig_tv)
            {
                _get_hv_pos(s_disp_name,&i2_h_pos, &i2_v_pos);
                h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                              h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);
                i4_ret = c_scc_vid_set_h_position (h_scc_comp, i2_h_pos + PIC_POSITIOIN_DRV_MAX_VALUE / 2);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = c_scc_vid_set_v_position (h_scc_comp, i2_v_pos + PIC_POSITIOIN_DRV_MAX_VALUE / 2);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                sys_asp_ratio_set_h_pos(i2_h_pos);
                sys_asp_ratio_set_v_pos(i2_v_pos);

                i4_ret = _get_overscan_with_h_v_pos(s_disp_name, &t_overscan);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type
                     && DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type)
            {
                acfg_get(IDX_CUSTOM_VGA_POS_H_EXT, &i2_val, &z_size);
                sys_asp_ratio_set_h_pos(i2_val);
                sys_asp_ratio_set_v_pos(0);

                t_overscan.ui4_right += i2_val;
            }
            else
            {
                sys_asp_ratio_set_h_pos(0);
                sys_asp_ratio_set_v_pos(0);
            }

            at_cmds[ui2_idx].t_type    = SVCTX_COMMON_SET_ATOMIC_OVERSCAN;
            at_cmds[ui2_idx++].pv_data = (VOID*)&t_overscan;

            at_cmds[ui2_idx].t_type  = SVCTX_COMMON_SET_ATOMIC_CMD_END;
            at_cmds[ui2_idx].pv_data = NULL;

            i4_ret = acfg_get_svctx(s_disp_name,&h_svctx);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = c_svctx_set(h_svctx, SVCTX_COMMON_SET_ATOMIC_CMD_GRP, at_cmds, 0);
            ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
            break;
        }
        case APP_CFG_RECID_VID_OVERSCAN:
        case APP_CFG_RECID_VID_CUSTOM_H_SIZE:
        case APP_CFG_RECID_VID_CUSTOM_V_SIZE:
        {
            INT16 i2_h_size = 0;
            INT16 i2_v_size = 0;
            SCC_VID_OVER_SCAN_CLIPPER_T     t_overscan = {0,0,0,0};
            SM_COMMAND_T    at_sm_cmds[4];

            if (ui2_cfg_rec == APP_CFG_RECID_VID_OVERSCAN && a_tv_net_get_overscan_enable() == FALSE)
            {
                 DBG_INFO(("\nOverwrite:%s  T=%d    B=%d    L=%d    R=%d    \n" ,
                            s_disp_name,
                            t_overscan.ui4_top,
                            t_overscan.ui4_bottom,
                            t_overscan.ui4_left,
                            t_overscan.ui4_right));

                at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
                at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
                at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
                at_sm_cmds[1].u.ps_text     = s_disp_name;
                at_sm_cmds[2].e_code        = SCC_CMD_CODE_VIDEO_OVERSCAN_CLIPPER;
                at_sm_cmds[2].u.pv_data     = &t_overscan;
                at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
                at_sm_cmds[3].u.ui4_data    = 0;
                i4_ret = c_scc_comp_grp_set(at_sm_cmds);
                ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
                return APP_CFGR_OK;
            }

            i4_ret = _get_hv_size(s_disp_name, &i2_h_size, &i2_v_size);
            ACFG_LOG_ON_FAIL(i4_ret);

            if (i2_h_size < 0 || i2_v_size < 0)
            {
                sys_asp_ratio_set_h_size(i2_h_size);
                sys_asp_ratio_set_v_size(i2_v_size);
                i4_ret = acfg_cust_video_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
                break;
            }

            i4_ret = _get_overscan_with_h_v_size (s_disp_name, &t_overscan);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
            at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text     = s_disp_name;
            at_sm_cmds[2].e_code        = SCC_CMD_CODE_VIDEO_OVERSCAN_CLIPPER;
            at_sm_cmds[2].u.pv_data     = &t_overscan;
            at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
            at_sm_cmds[3].u.ui4_data    = 0;
            i4_ret = c_scc_comp_grp_set(at_sm_cmds);
            ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
            break;
        }
        case APP_CFG_RECID_VID_POS_H:
        case APP_CFG_RECID_VID_POS_V:
            return _pos_update_custom (ui2_id);

        case APP_CFG_RECID_VID_CUSTOM_DCR:
            {
                INT16   i2_dcr_val = 0;
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_dcr_val);

                ACFG_DEBUG_BACKLIGHT(
                    DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call VIZIO_BACKLIGHT_CONTROL_D_SET(%d)\n",
                                                    __FUNCTION__, __LINE__, i2_dcr_val ));
                );

                VIZIO_BACKLIGHT_CONTROL_D_SET(i2_dcr_val);

                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
                ACFG_LOG_ON_FAIL(i4_ret);
                break;
            }

        case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
            {
                INT16   i2_light_sensor = 0;

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_light_sensor);

                // daniel
                ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
                    DBG_LOG_PRINT(("[ACFG_update][LightSensor]{%s: %s: %d} Call VIZIO_AMBIENT_LIGHT_SENSOR_D_SET(%d)\n", __FILE__, __FUNCTION__,__LINE__, i2_light_sensor));
                );

                VIZIO_AMBIENT_LIGHT_SENSOR_D_SET(i2_light_sensor);

                if (i2_light_sensor == 0 )
                {
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
                    ACFG_LOG_ON_FAIL(i4_ret);
                }
                break;
            }
#ifdef NEVER
        {
            INT16   i2_light_sensor = 0;
            INT16   i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_0;
            INT16   i2_dcr_val = 0;
            UINT8   t_retail_mode = 0;

            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

            if ((APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR == ui2_cfg_rec)
                &&(ACFG_RETAIL_MODE_NORMAL == t_retail_mode))
            {
                return APP_CFGR_OK;
            }
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_dcr_val);
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_light_sensor);
           // DBG_LOG_PRINT(("[ACFG][%s %d] APP_CFG_RECID_VID_CUSTOM_DCR = %d,APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR = %d\n",__FUNCTION__,__LINE__,i2_dcr_val,i2_light_sensor));
            if (i2_dcr_val == 0)
            {
                if (i2_light_sensor == 0) /* light sensor = off */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_0;
                }
                else if (i2_light_sensor == 1) /* light sensor = low */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_1;
                }
                else if (i2_light_sensor == 2) /* light sensor = Medium */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_2;
                }
                else   /* light sensor = high */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_3;
                }
            }
            else if(i2_dcr_val == 1)
            {
                if (i2_light_sensor == 0) /* light sensor = off */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_4;
                }
                else if (i2_light_sensor == 1) /* light sensor = low */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_5;
                }
                else if (i2_light_sensor == 2) /* light sensor = Medium */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_6;
                }
                else   /* light sensor = high */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_7;
                }
            }
            else if(i2_dcr_val == 2)  /* OPC */
            {
                if (i2_light_sensor == 0) /* light sensor = off */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_8;
                }
                else if (i2_light_sensor == 1) /* light sensor = low */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_9;
                }
                else if (i2_light_sensor == 2) /* light sensor = Medium */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_10;
                }
                else   /* light sensor = high */
                {
                    i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_11;
                }
            }

            UINT8   ui1_blur = 0;
            BOOL    b_is_support = FALSE;

            a_cfg_custom_is_reduce_blur_support(&b_is_support);

            if (b_is_support)
            {
                a_cfg_custom_get_reduce_blur(&ui1_blur);
            }

            if (ui1_blur != 0)
            {
                i2_adp_back_light = ACFG_CUST_ADP_BACK_LIGHT_0;
            }

            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT), i2_adp_back_light);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
            ACFG_LOG_ON_FAIL(i4_ret);
            break;
        }
#endif /* NEVER */
        case APP_CFG_RECID_VID_CUSTOM_DIMMING:
        {
            i4_ret = a_cfg_cust_update_local_dimming();
            ACFG_LOG_ON_FAIL(i4_ret);
            break;
        }
        case APP_CFG_RECID_VID_LUMA:
        {
            if (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) != 0)
            {
                /* For LUMA, don't need apply sub path luma to driver */
                i4_ret = APP_CFGR_OK;
            }
            else
            {
                i4_ret = APP_CFGR_NO_ACTION;
            }
            break;
        }

        #ifdef APP_3D_RETAIL_DEMO_MODE
        case APP_CFG_RECID_VID_3D_MODE:
            if (a_nav_retail_mode_get_play_video_status())
            {
                i4_ret = a_cfg_av_get(ui2_id,&i2_app_val);
                ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);

                i4_ret = c_scc_vid_set_3d_mode(h_g_acfg_scc_main_vid, (SCC_3D_MODE_T)i2_app_val);
                ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);

                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_FLD_DEPTH));
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_LR_SWITCH));
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_FPR));
                ACFG_LOG_ON_FAIL(i4_ret);

                return APP_CFGR_OK;
            }
            else
            {
                i4_ret = APP_CFGR_NO_ACTION;
            }
            break;
        #endif
        case APP_CFG_RECID_CLR_TEMP:
        {
            INT16 i2_clr_tmp = 0;

            a_cfg_cust_drv_update_panel_nits();
            // update backlight for tone-mapping(panel nits)
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_cust_set_color_temp((UINT8)i2_clr_tmp);
            ACFG_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y));
            ACFG_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

            a_menu_11_point_gain_update();

#ifdef NEVER
             /* updater the value*/
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA), i2_val);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
            ACFG_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */
            return APP_CFGR_OK;
        }
        case APP_CFG_RECID_VID_COLOR_SPACE:
        {
            INT32       i4_ret = APP_CFGR_OK;
            UINT8       ui1_color_space;
            DRV_CUST_OPERATION_INFO_T    t_op_info;

            c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_COLOR_SPACE), (INT16*)&ui1_color_space);
            DBG_LOG_PRINT(("[ACFG][%s %d]ui1_color_space = %d\n",__FUNCTION__,__LINE__,ui1_color_space));
            ui1_color_space = _acfg_cust_color_space_value_mapping(ui1_color_space);
            DBG_LOG_PRINT(("[ACFG][%s %d] mapping ui1_color_space = %d\n",__FUNCTION__,__LINE__,ui1_color_space));
            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
            t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDMI_RANGE;
            t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*)&ui1_color_space;
            t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);

            /*set value to driver*/
            i4_ret = c_rm_set_comp(
                                    DRVT_CUST_DRV,
                                    DRV_CUST_COMP_ID,
                                    FALSE,
                                    ANY_PORT_NUM,
                                    0,
                                    &t_op_info,
                                    sizeof(DRV_CUST_OPERATION_INFO_T)
                                    );
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        break;
        default:
#ifdef APP_ODM_ONE_IMG_SUPPORT
        {
            INT16   i2_val = 0;

            if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_R)
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_R), &i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), (INT16)i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_G)
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_G), &i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), (INT16)i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_B)
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_B), &i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), (INT16)i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_R)
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_R), &i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), (INT16)i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_G)
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_G), &i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), (INT16)i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else if (ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_B)
            {
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_B), &i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), (INT16)i2_val);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            else
            {
                i4_ret = APP_CFGR_NO_ACTION;
                break;
            }

            i4_ret = APP_CFGR_OK;
        }
#else
            i4_ret = APP_CFGR_NO_ACTION;
#endif
            break;
        }
        break;
    }
    default:
        i4_ret =  APP_CFGR_NOT_SUPPORT;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_video_sync(
    UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp){
    case APP_CFG_GRPID_DISP:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    case APP_CFG_GRPID_VIDEO:
    {
        switch(ui2_cfg_rec){
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }
        break;
    }
    default:
        i4_ret = APP_CFGR_NOT_SUPPORT;
        break;
    }

    return i4_ret;
}

/*------------------------------------------------------------------------------
                              External Functions
------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_reset_usr_clr_temp
 * Description:
 *      Reset color temperature date of user mode
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_reset_usr_clr_temp(UINT8   ui1_mask)
{
    UINT16  ui2_elem_idx;
    INT32   i4_ret;
    UINT8   ui1_def_val;
    UINT16  ui2_i;
    UINT8   ui1_input_grp;
    UINT8   ui1_input_src;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T   t_isl_rec;
    UINT8   ui1_reset_clr_number = ACFG_CLR_TEMP_NUM;

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input_src);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input_src, &t_isl_rec);
    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);

    /* Reset all sources color temp */
    if( APP_CFGR_NO_ACTION == a_cfg_reset_clr_tmp_default( ui1_mask))
    {
        for (ui2_i = 0; ui2_i < ui1_reset_clr_number; ui2_i++)
        {
            if (b_3d_mode_playing)
            {
                ui2_elem_idx = ACFG_CUST_INPUT_GRP_MAX * ACFG_CLR_TEMP_NUM + ui2_i;
            }
            else
            {
                ui2_elem_idx = ui1_input_grp * ACFG_CLR_TEMP_NUM + ui2_i;
            }

            ui1_def_val = *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R].pt_def_value + ui2_elem_idx);
            i4_ret = acfg_set_int16_by_idx(IDX_CLR_GAIN_R, ui2_elem_idx, ui1_def_val);
            ACFG_LOG_ON_FAIL(i4_ret);
            ui1_def_val = *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_G].pt_def_value + ui2_elem_idx);
            i4_ret = acfg_set_int16_by_idx(IDX_CLR_GAIN_G, ui2_elem_idx, ui1_def_val);
            ACFG_LOG_ON_FAIL(i4_ret);
            ui1_def_val = *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_B].pt_def_value + ui2_elem_idx);
            i4_ret = acfg_set_int16_by_idx(IDX_CLR_GAIN_B, ui2_elem_idx, ui1_def_val);
            ACFG_LOG_ON_FAIL(i4_ret);
            ui1_def_val = *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R].pt_def_value + ui2_elem_idx);
            i4_ret = acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, ui2_elem_idx, ui1_def_val);
            ACFG_LOG_ON_FAIL(i4_ret);
            ui1_def_val = *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_G].pt_def_value + ui2_elem_idx);
            i4_ret = acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, ui2_elem_idx, ui1_def_val);
            ACFG_LOG_ON_FAIL(i4_ret);
            ui1_def_val = *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_B].pt_def_value + ui2_elem_idx);
            i4_ret = acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, ui2_elem_idx, ui1_def_val);
            ACFG_LOG_ON_FAIL(i4_ret);
        }

        /* Reset 3D color temp mode */
        if (b_3d_mode_playing)
        {
            for (ui2_i = 0; ui2_i < ACFG_3D_PIC_MODE_NUM; ui2_i++)
            {
                ui2_elem_idx = ACFG_CUST_INPUT_GRP_MAX * ACFG_PIC_MODE_NUM + ui2_i;

                i4_ret = acfg_set_int16_by_idx(IDX_CLR_TEMP,
                                               ui2_elem_idx,
                                               _acfg_cust_video_get_def_val(IDX_CLR_TEMP, ui2_i));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
        }
        else
        {
            for (ui2_i = 0; ui2_i < ACFG_PIC_MODE_NUM; ui2_i++)
            {
                ui2_elem_idx = ui1_input_grp * ACFG_PIC_MODE_NUM + ui2_i;

                /* Reset color temp mode */
                i4_ret = acfg_set_int16_by_idx(IDX_CLR_TEMP,
                                               ui2_elem_idx,
                                               _acfg_cust_video_get_def_val(IDX_CLR_TEMP, ui2_i));
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
        }

    }

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_source_remapping(UINT32* pui2_idx)
{
    if((*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI1)||
       (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI2)||
       (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI3)||
       (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI4)||
       (*pui2_idx == ACFG_CUST_INPUT_GRP_MMP))
    {
         switch(a_acfg_cust_get_dynamic_range())
         {
             case ACFG_CUST_CONTENT_HDR:
                 if((*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI1)||
                 (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI2)||
                 (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI3) ||
                 (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI4))
                 {
                     *pui2_idx = ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + (*pui2_idx - ACFG_CUST_INPUT_GRP_HDMI1)*3;
                 }
                 else
                 {
                     *pui2_idx = ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM - 3;
                 }
             break;
             case ACFG_CUST_CONTENT_HLG:
                     if((*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI1)||
                     (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI2)||
                     (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI3)||
                     (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI4))
                     {
                         *pui2_idx = ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + (*pui2_idx - ACFG_CUST_INPUT_GRP_HDMI1)*3+1;
                     }
                     else
                     {
                         *pui2_idx = ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM - 2;
                     }
             break;
            case ACFG_CUST_CONTENT_DV:
                if((*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI1)||
                    (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI2)||
                    (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI3)||
                    (*pui2_idx == ACFG_CUST_INPUT_GRP_HDMI4))
                {
                    *pui2_idx = ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + (*pui2_idx - ACFG_CUST_INPUT_GRP_HDMI1)*3+2;
                }
                else
                {
                    *pui2_idx = ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM -1;
                }
                break;

             default:
             break;
        }

    }
    return *pui2_idx;
}

INT32 a_cfg_custom_reset_pic_settings (VOID)
{
    INT32   i4_ret = 0 ;
    UINT8   ui1_input;
    UINT16  ui2_elem_idx;
    INT16   i2_picture_mode;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_input_grp = 0;
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }


    DBG_LOG_PRINT(("[ACFG][PIC][default]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));


    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);
    //ui1_input_grp = a_cfg_custom_source_remapping(&ui1_input_grp);
    /* Reset picture mode. */
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_PIC_MODE_DEF);
    ACFG_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("[ACFG][%s %d] ui1_input_grp = %d\n",__FUNCTION__,__LINE__,ui1_input_grp));
    for (i2_picture_mode = 0; i2_picture_mode < ACFG_PIC_MODE_NUM; i2_picture_mode++)
    {

        ui2_elem_idx = ui1_input_grp * ACFG_PIC_MODE_NUM + i2_picture_mode;
        /* Reset backlight */
        i4_ret = acfg_set_int16_by_idx(IDX_DISP_BACK_LIGHT,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_DISP_BACK_LIGHT, i2_picture_mode));

        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset brightness */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_BRI,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_BRI, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset contrast */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_CNT,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_CNT, i2_picture_mode));

        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset color */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_SAT,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_SAT, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset tint */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_HUE,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_HUE, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset sharpness */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_SHP,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_SHP, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset noise reduction */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_3D_NR,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_3D_NR, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);


        ACFG_DEBUG_NR_DEFAULT(
            DBG_LOG_PRINT(("[ACFG][NR][default]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));
        );
        i4_ret = acfg_set_int16_by_idx(IDX_VID_NR,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_NR, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

#ifdef APP_MPEG_NR_SUPPORT
        i4_ret = acfg_set_int16_by_idx(IDX_VID_MPEG_NR,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_MPEG_NR, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif
        /* Reset flash tone */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_FT,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_FT, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset adaptive luma */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_LUMA,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_LUMA, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset backlight control */
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DCR_IDX,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_CUSTOM_DCR_IDX, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset custom dimming */
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DIMMING,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_CUSTOM_DIMMING, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset color temp mode */
        i4_ret = acfg_set_int16_by_idx(IDX_CLR_TEMP,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_CLR_TEMP, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        /* Reset Film Mode */
        i4_ret = acfg_set_int16_by_idx(IDX_VID_DI_FILM_MODE,
                                       ui2_elem_idx,
                                       _acfg_cust_video_get_def_val(IDX_VID_DI_FILM_MODE, i2_picture_mode));
        ACFG_CHK_FAIL(i4_ret, i4_ret);

    }

    /* Reset H/V position */
    i4_ret = acfg_set_int16_by_idx(IDX_VID_POS_H,
                                   _get_hv_pos_idx(ui1_input),
                                   ACFG_VID_POS_H_DEF);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_set_int16_by_idx(IDX_VID_POS_V,
                                   _get_hv_pos_idx(ui1_input),
                                   ACFG_VID_POS_V_DEF);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_H_SIZE,
                                   _get_hv_pos_idx(ui1_input),
                                   aui1_h_size_def[ui1_input]);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_V_SIZE,
                                   _get_hv_pos_idx(ui1_input),
                                   aui1_v_size_def[ui1_input]);
    ACFG_CHK_FAIL(i4_ret, i4_ret);


    acfg_set_default(IDX_VID_ETI);
    acfg_set_default(IDX_VID_DEBLOCKING);
    acfg_set_default(IDX_DISP_ADP_BACK_LIGHT);
    #ifdef APP_MJC_SUPPORT
    acfg_set_default(IDX_VID_MJC_EFFECT);
    acfg_set_default(IDX_VID_MJC_MODE);
    #endif

    #ifndef APP_CUST_UNRESET_LIGHT_SENSOR_SETTING_IN_PIC_RESET
    acfg_set_default(IDX_CUSTOM_LIGHT_SENSOR_IDX);
    #endif

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_3D_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_FT));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_LUMA));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_ETI));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_DEBLOCKING));
    #ifdef APP_MJC_SUPPORT
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE));
    #endif

    APPTV_DEBUG_WHO_CALL_MUTE(0, TV_VIDEO_MUTE_MASK_RESET, FALSE);
    A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_ACFG, h_g_acfg_svctx_main, TV_VIDEO_MUTE_MASK_RESET, FALSE);

    APPTV_DEBUG_WHO_CALL_MUTE(1, TV_VIDEO_MUTE_MASK_RESET, FALSE);
    A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_ACFG, h_g_acfg_svctx_sub, TV_VIDEO_MUTE_MASK_RESET, FALSE);

#ifdef APP_RETAIL_MODE_SUPPORT
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        a_cfg_custom_set_pic_mode_vivid();
    }
#endif

    /* VGA settings */
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        i4_ret = acfg_vga_reset();
        ACFG_LOG_ON_FAIL(i4_ret);

        /* Auto */
        i4_ret = a_cfg_vga_auto_clk_phs_pos();
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_reset_pic_mode_setting (VOID)
{
     INT32   i4_ret = 0 ;
     i4_ret = acfg_set_default(IDX_PIC_MODE);
     ACFG_LOG_ON_FAIL(i4_ret);
     DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
     i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
     ACFG_LOG_ON_FAIL(i4_ret);
     return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_pic_mode_vivid (VOID)
{
    INT32   i4_ret;

    i4_ret = a_cfg_custom_set_all_src_pic_mode(ACFG_CUST_PIC_MODE_VIVID);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;

}
INT32 a_cfg_custom_set_all_src_pic_mode(ACFG_CUST_PIC_MODE_T  t_pic_mode)
{
    INT32   i4_ret = 0;
    UINT8   aui1_av_mode[ACFG_PIC_MODE_ELEM_NUM];

    if(t_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
    {
        t_pic_mode = ACFG_CUST_PIC_MODE_VIVID;
    }

    c_memset(aui1_av_mode, (UINT8)t_pic_mode, sizeof(aui1_av_mode));

    /* set pictuer mode to all elements */
    i4_ret = acfg_set(IDX_PIC_MODE,
                      (VOID*)aui1_av_mode,
                      ACFG_PIC_MODE_ELEM_NUM);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

INT32 acfg_cust_video_get_overscan(CHAR * s_disp_name,SCC_VID_OVER_SCAN_CLIPPER_T * pt_overscan)
{
    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} s_disp_name:%s \n",
            __FUNCTION__,__LINE__, s_disp_name ));
    );

    return _get_overscan(s_disp_name, pt_overscan);
}

INT32 acfg_cust_video_get_overscan_with_h_v_size(CHAR * s_disp_name,SCC_VID_OVER_SCAN_CLIPPER_T * pt_overscan)
{
    INT16 i2_v_size = 0;
    INT16 i2_h_size = 0;
    INT32 i4_ret;

    ACFG_DEBUG_OVER_SCAN(
        DBG_LOG_PRINT(("[ACFG][OverScan]{%s,%d} s_disp_name:%s \n",
            __FUNCTION__,__LINE__, s_disp_name ));
    );

    if (!pt_overscan)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = _get_overscan(s_disp_name, pt_overscan);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE), &i2_h_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE), &i2_v_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i2_h_size *= 10;
    i2_v_size *= 10;
    pt_overscan->ui4_top      += i2_v_size;
    pt_overscan->ui4_bottom   += i2_v_size;
    pt_overscan->ui4_left     += i2_h_size;
    pt_overscan->ui4_right    += i2_h_size;

    return APP_CFGR_OK;
}

static INT32 _acfg_cust_video_def_value_append_patch(VOID)
{
    /* overwrite common value*/
    _acfg_cust_video_init_common_field_def_value();
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_color_space_value_mapping(UINT8 ui1_color_space)
{
    switch(ui1_color_space)
    {

        /* this place do remapping value for color space set down to dirver.
                 Stand on dirver point of view
                 0 mean auto
                 1 mean YCbCr
                 2 mean RGB
                 */

        case SCC_VID_COLORSPACE_AUTO:
            ui1_color_space = 0;
            break;
        case SCC_VID_COLORSPACE_FORCE_RGB:
            ui1_color_space = 2;
            break;
        case SCC_VID_COLORSPACE_FORCE_YCBCR:
            ui1_color_space = 1;
            break;
        default:
            ui1_color_space = 0;
            break;
    }

    return ui1_color_space;

}

INT32 acfg_fac_rgb_value_mapping(
    INT16*   pi2_cfg_rec)
{
    /*
        The function of this API do fac rgb value remapping
        The matching rule is from factory to MTK if value exceed the range the value will be set to Zero
           ex: factory range (0 ~ 1023)
           factory value = 512
           *ui2_cfg_rec value will be mapping to 0
         if this value is illegal like -100
         *ui2_cfg_rec will ignore facotry value and set to 0
     */
     INT16  i2_min;
     INT16  i2_max;

     acfg_video_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_min, &i2_max);
    *pi2_cfg_rec = ACFG_MTK_CLR_RGB_MIN_VALUE +
                   (*pi2_cfg_rec - i2_min) *
                   (ACFG_MTK_CLR_RGB_MAX_VALUE   - ACFG_MTK_CLR_RGB_MIN_VALUE) /
                   (i2_max - i2_min);
    if ((*pi2_cfg_rec > ACFG_MTK_CLR_RGB_MAX_VALUE)||(*pi2_cfg_rec < ACFG_MTK_CLR_RGB_MIN_VALUE))
    {
        *pi2_cfg_rec = 0;
    }
    return APP_CFGR_OK;
}

ACFG_CUST_HDMI_COLOR_FORMAT_T acfg_cust_video_get_hdmi_color_space(void)
{
    ACFG_CUST_HDMI_COLOR_FORMAT_T e_color_space = ACFG_CUST_HDMI_COLOR_UNKNOWN;
    ACFG_CUST_HDMI_COLOR_FORMAT_T * pe_color_space = &e_color_space;

    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info  = {0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size     = sizeof(pe_color_space);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_GET_HDMI_COLORSPACE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pe_color_space;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           &z_size_drv
                           );
    if( i4_ret < 0 )
    {
        DBG_LOG_PRINT(("[ACFG] Error %d: {acfg_cust_video_get_hdmi_color_space} Get HDMI color failed!\n", i4_ret ));
        return ACFG_CUST_HDMI_COLOR_UNKNOWN;
    }

    return e_color_space;
}

char* acfg_cust_video_get_hdmi_color_space_string(ACFG_CUST_HDMI_COLOR_FORMAT_T eHdmiColorFormat)
{
    switch(eHdmiColorFormat)
    {
        case ACFG_CUST_HDMI_COLOR_RGB:      return "ACFG_CUST_HDMI_COLOR_RGB";
        case ACFG_CUST_HDMI_COLOR_YUV422:   return "ACFG_CUST_HDMI_COLOR_YUV422";
        case ACFG_CUST_HDMI_COLOR_YUV444:   return "ACFG_CUST_HDMI_COLOR_YUV444";
        case ACFG_CUST_HDMI_COLOR_YUV420:   return "ACFG_CUST_HDMI_COLOR_YUV420";
        default:
            break;
    }

    return "ACFG_CUST_HDMI_COLOR_UNKNOWN";
}

INT32 acfg_cust_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32       i4_ret = 0;
    TV_WIN_ID_T e_win_id = TV_WIN_ID_MAIN;

    i4_ret = a_tv_get_focus_win(&e_win_id);
    if( i4_ret != TVR_OK )
    {
        DBG_LOG_PRINT(("\n[ACFG]{%s:%d} Error: a_tv_get_focus_win() fail! i4_ret:%d\n", __FILE__, __LINE__, i4_ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    i4_ret = a_tv_get_isl_rec_by_win_id(e_win_id, pt_isl_rec);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("\n[ACFG]{%s:%d} Error: a_tv_get_isl_rec_by_win_id() fail! i4_ret:%d\n", __FILE__, __LINE__, i4_ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    return APP_CFGR_OK;
}

ACFG_CUST_INPUT_GRP_T acfg_cust_Get_CurInputGrp(void)
{
    INT32  i4_ret = 0;

    //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d}\n", __FUNCTION__, __LINE__ )); );

    ISL_REC_T  t_isl_rec = {0};
    i4_ret = acfg_cust_get_crnt_isl(&t_isl_rec);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("\n[ACFG][SRC]{%s:%d} Error: acfg_cust_get_crnt_isl() fail! i4_ret:%d\n", __FUNCTION__, __LINE__, i4_ret));
        return ACFG_CUST_INPUT_GRP_MAX;
    }


    UINT8 u8AcfgInputGrp = acfg_custom_get_input_grp(&t_isl_rec);

    // Check ui2_ipt: 0 ~ 10
    if( u8AcfgInputGrp >= ACFG_CUST_INPUT_GRP_MAX )
    {
        DBG_LOG_PRINT(("[ACFG][SRC]{%s: %d} Error: Invalid input_grp(%d)!! => Force return ACFG_CUST_INPUT_GRP_TV\n",
            __FUNCTION__,__LINE__, u8AcfgInputGrp ));

        return ACFG_CUST_INPUT_GRP_MAX;
    }

    return (ACFG_CUST_INPUT_GRP_T)u8AcfgInputGrp;
}


#if 1//(ENABLE_COLOR_444_TO_422_NEW_SPEC)
BOOL acfg_cust_Is_CurSrcHDMI(void)
{
    INT32  i4_ret = 0;

    //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d}\n", __FUNCTION__, __LINE__ )); );

    ISL_REC_T  t_isl_rec = {0};
    i4_ret = acfg_cust_get_crnt_isl(&t_isl_rec);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("\n[ACFG][HDMI]{%s:%d} Error: acfg_cust_get_crnt_isl() fail! i4_ret:%d\n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }


    // Only HDMI support ...
    if( (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
      ||(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI)
      )
    {
        //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][HDMI]{%s:%d} ==> TRUE\n", __FUNCTION__, __LINE__ )); );
        return TRUE;
    }

    //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][HDMI]{%s:%d} ==> FALSE\n", __FUNCTION__, __LINE__ )); );
    return FALSE;
}

BOOL acfg_cust_FullColor444_IfCanTurnOn(void)
{
    //INT32  i4_ret = 0;

    //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG]{%s:%d} \n", __FUNCTION__, __LINE__)); );

    BOOL bIsCurSrcHDMI = acfg_cust_Is_CurSrcHDMI();

    // Only HDMI support ...
    if( !bIsCurSrcHDMI )
    {
        return FALSE;
    }

    //if( menu_is_signal_loss() == TRUE || menu_is_video_block() == TRUE )
    if( (a_common_setting_is_signal_loss() == TRUE) || (a_common_setting_is_video_block() == TRUE) )
    {
        ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} NoSignal or VideoBlock => FALSE\n", __FUNCTION__, __LINE__)); );
        return FALSE;
    }

  #if 0
    if( a_icl_custom_get_dolby_vision_status() == 1 )
    {
        return FALSE;
    }
  #endif

  #if 0
    if (a_cfg_get_hdr_type() != SCC_VID_PQ_SDR)
    {
        return FALSE;
    }
  #endif


    ACFG_CUST_HDMI_COLOR_FORMAT_T eHdmiColorFormat = acfg_cust_video_get_hdmi_color_space();
    //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG]{%s:%d} eHdmiColorFormat:%d\n", __FILE__, __LINE__, eHdmiColorFormat)); );

    switch(eHdmiColorFormat)
    {
        case ACFG_CUST_HDMI_COLOR_RGB:
        case ACFG_CUST_HDMI_COLOR_YUV444:
            ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} eHdmiColorFormat:%d(%s) => rtn TRUE\n",
                __FUNCTION__, __LINE__, eHdmiColorFormat, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorFormat) )); );
            return TRUE;
            break;

        case ACFG_CUST_HDMI_COLOR_YUV422:
        case ACFG_CUST_HDMI_COLOR_YUV420:
            ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} eHdmiColorFormat:%d(%s) => rtn FALSE\n",
                __FUNCTION__, __LINE__, eHdmiColorFormat, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorFormat) )); );
            return FALSE;
            break;

        default:
            break;
    }

  #if 0
    MENU_HDMI_IF_CLR_SPC e_color_space = MENU_HDMI_IF_CLRSPC_UNKNOW;
    INT32  i4_color = 0;
    i4_ret = menu_ope_lst_get_hdmi_color_space(&i4_color);
    if (i4_ret != MENUR_OK)
    {
       return FALSE;
    }
    DBG_LOG_PRINT((" hdmi_color_space : %d, %s,%d\r\n",i4_color,__FUNCTION__,__LINE__));

    e_color_space = (MENU_HDMI_IF_CLR_SPC)i4_color;
    if(menu_ope_lst_hdmi_color_space_is_444(e_color_space) == FALSE )
    {
        return FALSE;
    }
  #endif

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Warning: eHdmiColorFormat:%d(%s) => rtn FALSE\n",
            __FUNCTION__, __LINE__, eHdmiColorFormat, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorFormat) )); );

    return FALSE;
}

extern BOOL g_ACFG_Drv_bCurHdmiModeIsGraphicMode;

BOOL acfg_cust_Is_CurHDMI_PQ_PCMode(void)
{
#if 1 // New to avoid flow issue
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );

    if( (eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON)
      ||(eAcfgFullColor444Status == ACFG_INPUT_YUV444__FULL_COLOR_444_ON)
      )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s,%d} FullColor444 => UI sharpness Hide\n", __FUNCTION__,__LINE__ ));
        return TRUE;
    }

    return FALSE;

#else

    // Check if can turn on ...
    BOOL bIs_FullColor444_CanTurnOn = acfg_cust_FullColor444_IfCanTurnOn();
    if( !bIs_FullColor444_CanTurnOn ) // Cannot turn on
    {
        ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d}  ==> FALSE\n", __FUNCTION__, __LINE__)); );
        return FALSE;
    }


    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d}  ==> %d\n", __FUNCTION__, __LINE__, g_ACFG_Drv_bCurHdmiModeIsGraphicMode)); );

    return g_ACFG_Drv_bCurHdmiModeIsGraphicMode;
#endif
}

EnuAcfgFullColor444Status acfg_cust_get_FullColor444_status(void)
{
    // Check input_source
    if( FALSE == acfg_cust_Is_CurSrcHDMI() )
    {
        ACFG_DEBUG_FULL_COLOR444(
            DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Non-HDMI => YUV422\n", __FUNCTION__, __LINE__)); );
        return ACFG_INPUT_YUV422__FULL_COLOR_444_OFF;
    }


    // Get HDMI color format ...
    ACFG_CUST_HDMI_COLOR_FORMAT_T eHdmiColorFormat = acfg_cust_video_get_hdmi_color_space();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} eHdmiColorFormat:%d(%s)\n",
        __FILE__, __LINE__, eHdmiColorFormat, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorFormat) )); );


    // Get current full_color_444 setting...
    UINT8 ui1_full_color_444_value = 0;
    UINT32 i32Ret = a_cfg_cust_get_full_color_444_ForCurHDMI(&ui1_full_color_444_value);
    if( i32Ret != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: a_cfg_cust_get_full_color_444_ForCurHDMI() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        ui1_full_color_444_value = 0;
    }

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui1_full_color_444_value:%d\n", __FUNCTION__, __LINE__, ui1_full_color_444_value)); );


    EnuAcfgFullColor444Status eAcfgFullColor444Status = ACFG_INPUT_RGB__FULL_COLOR_444_OFF;

    switch(eHdmiColorFormat)
    {
        case ACFG_CUST_HDMI_COLOR_RGB:
            //if( g_ACFG_Drv_bCurHdmiModeIsGraphicMode )
            if(ui1_full_color_444_value)
                eAcfgFullColor444Status = ACFG_INPUT_RGB__FULL_COLOR_444_ON;
            else
                eAcfgFullColor444Status = ACFG_INPUT_RGB__FULL_COLOR_444_OFF;
            break;

        case ACFG_CUST_HDMI_COLOR_YUV444:
            //if( g_ACFG_Drv_bCurHdmiModeIsGraphicMode )
            if(ui1_full_color_444_value)
                eAcfgFullColor444Status = ACFG_INPUT_YUV444__FULL_COLOR_444_ON;
            else
                eAcfgFullColor444Status = ACFG_INPUT_YUV444__FULL_COLOR_444_OFF;
            break;

        case ACFG_CUST_HDMI_COLOR_YUV422:
        case ACFG_CUST_HDMI_COLOR_YUV420:
            eAcfgFullColor444Status = ACFG_INPUT_YUV422__FULL_COLOR_444_OFF;
            break;

        default:
            break;
    }

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG]{%s:%d} eHdmiColorFormat:%d(%s) => eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eHdmiColorFormat, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorFormat), eAcfgFullColor444Status )); );

    return eAcfgFullColor444Status;
}

#endif

BOOL a_cfg_cust_video_is_sdr_hdr_444_content(VOID)
{
    INT32                       i4_ret  = 0;
    UINT8                       ui1_idx = 0 ;
    DRV_CUST_OPERATION_INFO_T   t_op_info  = {0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size     = sizeof(UINT8);


    if((a_acfg_cust_get_dynamic_range() == ACFG_CUST_CONTENT_HDR)
        ||(a_acfg_cust_get_dynamic_range() == ACFG_CUST_CONTENT_SDR))
    {
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_GET_IS_ScalerInputRGB_STATUS;
        t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_idx;
        t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

        /* get from driver */
        i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                               DRV_CUST_COMP_ID,
                               FALSE,
                               ANY_PORT_NUM,
                               0,
                               &t_op_info,
                               &z_size_drv
                               );
        ACFG_LOG_ON_FAIL(i4_ret);

        if(ui1_idx > 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL acfg_is_backlight_control_enable()
{
    return TRUE;
}

INT32 a_cfg_cust_copy_pic_mode_to_pic_mode(INT16 i2_from_pic,INT16 i2_to_pic)
{
    INT32                       i4_ret = 0;
    UINT16                      ui2_from_idx = 0;
    UINT16                      ui2_to_idx = 0;
    INT16                       i2_value = 0;
    ISL_REC_T                   t_isl_rec;
    UINT8                       ui1_input_src = 0;
    UINT16                      ui2_rec_idx = 0;
    CHAR                        s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8                       ui1_input = 0;


    DBG_LOG_PRINT(("[ACFG][PIC_mode]{%s,%d} i2_from_pic:%d ==> i2_to_pic:%d\n", __FUNCTION__,__LINE__, i2_from_pic, i2_to_pic ));

#if 1 // todo
    // Check i2_from_pic: 0 ~ 11
    if( (i2_from_pic < 0) || (i2_from_pic >= (ACFG_PRE_SET_PIC_MODE_NUM+6)) )
    {
        DBG_LOG_PRINT(("\n[ACFG]{%s: %d}Error: Invalid i2_from_pic:%d \n", __FUNCTION__,__LINE__, i2_from_pic ));
        return APP_CFGR_INV_ARG;
    }

    // Check i2_to_pic: 0 ~ 11
    if( (i2_to_pic < 0) || (i2_to_pic >= (ACFG_PRE_SET_PIC_MODE_NUM+6)) )
    {
        DBG_LOG_PRINT(("\n[ACFG]{%s: %d}Error: Invalid i2_to_pic:%d \n", __FUNCTION__,__LINE__, i2_from_pic ));
        return APP_CFGR_INV_ARG;
    }
#endif

    if((i2_from_pic < ACFG_PRE_SET_PIC_MODE_NUM && i2_to_pic < ACFG_PRE_SET_PIC_MODE_NUM)
       || (i2_from_pic >= ACFG_PRE_SET_PIC_MODE_NUM && i2_to_pic >= ACFG_PRE_SET_PIC_MODE_NUM))
    {
        DBG_LOG_PRINT(("** invalid copy picture mode %s,%d\r\n",__FUNCTION__,__LINE__));
        DBG_LOG_PRINT(("copy picture mode from :%d to %d, %s,%d\r\n",i2_from_pic,i2_to_pic,__FUNCTION__,__LINE__));
        return APP_CFGR_INV_ARG;
    }

    /*get current input source*/
    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
    ui1_input_src = acfg_custom_get_input_grp(&t_isl_rec);

    DBG_LOG_PRINT(("[ACFG]{%s: %d} ui1_input_src:%d\n", __FUNCTION__,__LINE__, ui1_input_src ));
    //DBG_LOG_PRINT(("copy picture mode from :%d to %d, %s,%d\r\n",i2_from_pic,i2_to_pic,__FUNCTION__,__LINE__));

    /* for copy base issue, only for custome-> preset picture mode*/
    if(i2_from_pic >= ACFG_PRE_SET_PIC_MODE_NUM) //copy data from custom  to preset picture mode
    {
        ui2_from_idx = ACFG_VID_SETTINS_GLOBAL_IPT_SRC * ACFG_CUST_SET_PIC_MODE_NUM + i2_from_pic - ACFG_PRE_SET_PIC_MODE_NUM;
        ui2_to_idx = ui1_input_src * ACFG_PRE_SET_PIC_MODE_NUM + i2_to_pic;

        i4_ret = acfg_get_int16_by_idx(IDX_CUST_PIC_COPY_BASE,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i2_value = i2_value + ACFG_CUST_COPY_PIC_MODE_BASE;
        i4_ret = acfg_set_int16_by_idx(IDX_CUST_PIC_COPY_BASE,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    /*  copy current picture mode data to destination */
    /* data store in eeprom input source  by picture mode*/
    if(i2_from_pic >= ACFG_PRE_SET_PIC_MODE_NUM) //copy data from custom  to preset picture mode
    {
        ui2_from_idx = ACFG_VID_SETTINS_GLOBAL_IPT_SRC * ACFG_PIC_MODE_NUM + i2_from_pic;
        ui2_to_idx = ui1_input_src * ACFG_PIC_MODE_NUM + i2_to_pic;
    }
    else
    {
        ui2_from_idx =  ui1_input_src * ACFG_PIC_MODE_NUM + i2_from_pic;
        ui2_to_idx = ACFG_VID_SETTINS_GLOBAL_IPT_SRC * ACFG_PIC_MODE_NUM + i2_to_pic;
    }

    DBG_LOG_PRINT((" ui2_from_idx :%d to ui2_to_idx : %d, %s,%d\r\n",ui2_from_idx,ui2_to_idx,__FUNCTION__,__LINE__));

    /*GLL */
    i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY,ui2_from_idx,&i2_value);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY,ui2_to_idx,i2_value);
    ACFG_LOG_ON_FAIL(i4_ret);

    /*Game HDR */
    i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_GAME_HDR,ui2_from_idx,&i2_value);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_GAME_HDR,ui2_to_idx,i2_value);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* data store in eeprom input source  by picture mode by dynamic range*/
    UINT8  ui1_video_type = 0;

#if( !ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE )
    ui1_video_type = a_acfg_cust_get_dynamic_range();
#endif

#if (ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE )
    for (ui1_video_type = 0; ui1_video_type < APP_CFG_DYNAMIC_RANGE_NUM ;  ui1_video_type++)
#endif
    {
        if(i2_from_pic >= ACFG_PRE_SET_PIC_MODE_NUM) //copy data from custom  to preset picture mode
        {
        #if (ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE )
            ui2_from_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (ui1_video_type * ACFG_CUST_SET_PIC_MODE_NUM) + (i2_from_pic - ACFG_PRE_SET_PIC_MODE_NUM);
        #else
            ui2_from_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (0              * ACFG_CUST_SET_PIC_MODE_NUM) + (i2_from_pic - ACFG_PRE_SET_PIC_MODE_NUM);
        #endif

            ui2_to_idx   = ui1_input_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM + i2_to_pic;
        }
        else
        {
            ui2_from_idx =  ui1_input_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM + i2_from_pic;

        #if (ACFG_CUST_SAVE_PIC_MODE_INCLUDE_4_HDR_TYPE )
            ui2_to_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (ui1_video_type * ACFG_CUST_SET_PIC_MODE_NUM) + (i2_to_pic - ACFG_PRE_SET_PIC_MODE_NUM);
        #else
            ui2_to_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + (0 * ACFG_CUST_SET_PIC_MODE_NUM) + (i2_to_pic - ACFG_PRE_SET_PIC_MODE_NUM);
        #endif
        }

        DBG_LOG_PRINT((" ui2_from_idx :%d to ui2_to_idx : %d, %s,%d\r\n",ui2_from_idx,ui2_to_idx,__FUNCTION__,__LINE__));

        /*gamma*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUST_GAMMA,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUST_GAMMA,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*backlight, tone mapping,peak luminace*/
        i4_ret = acfg_get_int16_by_idx(IDX_DISP_BACK_LIGHT,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_DISP_BACK_LIGHT,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*dcr,local diming*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_DCR_IDX,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DCR_IDX,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_DIMMING,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DIMMING,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*brightness,contrast,color,tint*/
        for (ui2_rec_idx = IDX_VID_BRI ; ui2_rec_idx <= IDX_VID_CNT;  ui2_rec_idx++)
        {
            i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,ui2_from_idx,&i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,ui2_to_idx,i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);
        }

        /*hsb(18),rgb*/
        for (ui2_rec_idx = IDX_CLR_HUE_R ; ui2_rec_idx <= IDX_BLUE;  ui2_rec_idx++)
        {
            i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,ui2_from_idx,&i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,ui2_to_idx,i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);

        }

        /*auto backlight control(ambient light sensor)*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*sharpness*/
        i4_ret = acfg_get_int16_by_idx(IDX_VID_SHP,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_SHP,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*supper resolution*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_SUPER_RESOLUTION,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_SUPER_RESOLUTION,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*enhanced viewing angle*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*reduce judder(judder reduction)*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_JUDDER_REDUCTION,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_JUDDER_REDUCTION,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*reduce motion blur*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
        /*variable refresh rate*/
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_VARIABLE_REFRESH_RATE,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_VARIABLE_REFRESH_RATE,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

        /*reduce bolock Noise */
        i4_ret = acfg_get_int16_by_idx(IDX_VID_3D_NR,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_3D_NR,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        ACFG_DEBUG_NR_DEFAULT(
            DBG_LOG_PRINT(("[ACFG][NR][defalut]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));
        );
        i4_ret = acfg_get_int16_by_idx(IDX_VID_NR,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_NR,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

       /*reduce single noise*/
#ifdef APP_MPEG_NR_SUPPORT
        i4_ret = acfg_get_int16_by_idx(IDX_VID_MPEG_NR,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_MPEG_NR,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
#endif

       /*CAR(clear action) */
        i4_ret = acfg_get_int16_by_idx(IDX_CLEAR_ACTION,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CLEAR_ACTION,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*Film mode */
#ifdef APP_DI_SUPPORT
        i4_ret = acfg_get_int16_by_idx(IDX_VID_DI_FILM_MODE,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_DI_FILM_MODE,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
#endif

       /*Contrast Enhancement */
        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_CONTRAST_EN,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_CONTRAST_EN,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /*color tmeperature */
        i4_ret = acfg_get_int16_by_idx(IDX_CLR_TEMP,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CLR_TEMP,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /* new add ,not include pq matrix*/
        i4_ret = acfg_get_int16_by_idx(IDX_VID_LOCAL_CONTRAST,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_LOCAL_CONTRAST,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_PEAK_LUMINANCE,ui2_from_idx,&i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_PEAK_LUMINANCE,ui2_to_idx,i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);


    }

    return APP_CFGR_OK;
}


static INT32 _cfg_mi_mm_get_movie_info (MI_HANDLE   h_MI_MM_Hdl,ACFG_MI_MM_INFO_T    *nav_mi_mm_info)
{
    MI_RESULT                   e_ret               = MI_ERR_FAILED;
    MI_MM_MovieInfo_t           stMovieInfo;
    c_memset(&stMovieInfo,0,sizeof(MI_MM_MovieInfo_t));

    e_ret = MI_MM_GetMovieInfo(h_MI_MM_Hdl,&stMovieInfo);
    if(e_ret != MI_OK)
    {
        DBG_LOG_PRINT(("MI_MM_GetMovieInfo fail ret = %d\n", e_ret));
        return APP_CFGR_NO_ACTION;
    }
    else
    {
        //DBG_LOG_PRINT(("MI_MM_GetMovieInfo h:%d. w:%d\n", stMovieInfo.u32MovieHeight, stMovieInfo.u32MovieWidth));
        //DBG_LOG_PRINT(("FramePerSec:%d.\n",stMovieInfo.u32FramePerSec));
        //DBG_LOG_PRINT(("VideoCodec:%d. AudioCodec:%d\n",stMovieInfo.eVideoCodec, stMovieInfo.eAudioCodec));

        nav_mi_mm_info->MI_U32_FramePerSec = stMovieInfo.u32FramePerSec;
        nav_mi_mm_info->MI_U32_MovieWidth = stMovieInfo.u32MovieWidth;
        nav_mi_mm_info->MI_U32_MovieHeight = stMovieInfo.u32MovieHeight;
        nav_mi_mm_info->eVideoCodec = stMovieInfo.eVideoCodec;
        nav_mi_mm_info->eAudioCodec = stMovieInfo.eAudioCodec;

        return APP_CFGR_OK;
    }

    return APP_CFGR_NO_ACTION;
}


extern INT32 a_cfg_mi_mm_querry(ACFG_MI_MM_INFO_T     *nav_mi_mm_info)
{
    MI_RESULT   e_ret               =   MI_ERR_FAILED;
    MI_HANDLE   h_MI_MM_Hdl         =   NULL_HANDLE;
    UINT32      ui4_handle_count    =   0;
    UINT32      ui4_count           =   0;
    INT32       i4_ret              =   APP_CFGR_NO_ACTION;

    e_ret = MI_MM_QueryHandle(E_MI_MM_MEDIA_MOVIE,E_MI_MM_PLAYSTATE_PLAYING,&ui4_handle_count);

    if(e_ret != MI_OK || ui4_handle_count == 0)
    {
        DBG_INFO(("MI_MM_QueryHandle fail ret = %d,ui4_handle_count = %d\n",
            e_ret,ui4_handle_count));
        return APP_CFGR_NO_ACTION;
    }

    //DBG_LOG_PRINT(("MI_MM_QueryHandle ui4_handle_count = %d\n", ui4_handle_count));

    for(ui4_count = 0;ui4_count < ui4_handle_count;ui4_count++)
    {
        e_ret = MI_MM_GetNextHandle(&h_MI_MM_Hdl);
        if(e_ret == MI_OK)
        {
            i4_ret = _cfg_mi_mm_get_movie_info(h_MI_MM_Hdl,nav_mi_mm_info);
            if(i4_ret == APP_CFGR_OK)
               return APP_CFGR_OK;
        }
    }

    return i4_ret;
}

extern INT32 a_cfg_mi_mm_querry_ex(ACFG_MI_MM_INFO_T     *nav_mi_mm_info, BOOL *pb_interlace)
{
    MI_RESULT   e_ret               =   MI_ERR_FAILED;
    MI_HANDLE   h_MI_MM_Hdl         =   NULL_HANDLE;
    UINT32      ui4_handle_count    =   0;
    UINT32      ui4_count           =   0;
    INT32       i4_ret              =   APP_CFGR_NO_ACTION;
    BOOL        b_interlace         =   FALSE;

    e_ret = MI_MM_QueryHandle(E_MI_MM_MEDIA_MOVIE,E_MI_MM_PLAYSTATE_PLAYING,&ui4_handle_count);

    if(e_ret != MI_OK || ui4_handle_count == 0)
    {
        DBG_INFO(("MI_MM_QueryHandle fail ret = %d,ui4_handle_count = %d\n",
            e_ret,ui4_handle_count));
        return APP_CFGR_NO_ACTION;
    }

    for(ui4_count = 0;ui4_count < ui4_handle_count;ui4_count++)
    {
        e_ret = MI_MM_GetNextHandle(&h_MI_MM_Hdl);
        if(e_ret == MI_OK)
        {
            i4_ret = _cfg_mi_mm_get_movie_info(h_MI_MM_Hdl,nav_mi_mm_info);
            if(i4_ret == APP_CFGR_OK)
            {
                i4_ret = MI_MM_GetAttr(h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_GET_VIDEO_SCAN_TYPE_INTERLACE, NULL, (void *)&b_interlace);
                ACFG_LOG_ON_FAIL(i4_ret);

                *pb_interlace = b_interlace;
                return APP_CFGR_OK;
            }
        }
    }

    return i4_ret;
}

INT32 acfg_cust_video_update_GLL_all(BOOL bUpdateLogo)
{
    DBG_LOG_PRINT(("[ACFG][GLL][GAME]{%s,%d} \n",__FUNCTION__,__LINE__ ));

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));


    //1. Black Detail           // 0:off ; 1:low; 2:medim; 3:high
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN));

    //2. Local contrast         // 0:off ; 1:low; 2:medim; 3:high
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST));

    //3. Signal Noise           // 0:off ; 1:low; 2:medim; 3:high
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR));

    //4. Contour Smoothing      // 0:off ; 1:low; 2:medim; 3:high
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING));

    // MEMC:
    //5. Judder reduction       // 0 - 10
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION));

    //6. Motion blir reduction  // 0 - 10
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION));

    //7. Clear action => Turn Off  // 0: off ; 1 : on
    if (a_cfg_cust_get_support_clear_aciton() == TRUE)
    {
        //VIZIO_CLEAR_ACTION_D_SET(0);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));
    }

    //9. Enhanced Viewing Angle         // 0: off ; 1 : on
    if (a_cfg_cust_en_view_angle_support() == TRUE)
    {
        //a_cfg_cust_drv_set_enhanced_viewing_angle(0);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
    }


    if( bUpdateLogo )
    {
        a_acfg_update_gaming_logo();
    }

    return APP_CFGR_OK;
}


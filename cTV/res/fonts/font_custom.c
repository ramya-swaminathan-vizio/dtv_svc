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
/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "c_fe.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"

#include "fonts/fontdata.h"
#include "res/fonts/a_font_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
#ifdef SYS_FLASH_FONT_SUPPORT
/*
    if SYS_FLASH_FONT_SUPPORT is defined, use the flash font.

    for China region only,
    -ch_font.TTF                   ¡VEnglish, Simplified/Traditional Chinese

    for Asia region,
    -Tiresias.TTF                  ¡VEnglish, Spanish, French, Portuguese, ... etc
    -DejaVuSans.TTF                - Vietnamese, Arabic, Indonesian, Persian font
    -wqy-zenhei.TTF                - Simplified/Traditional Chinese font
    -Kinnari.TTF                   - Thai font
*/
/**/
#ifdef APP_REGION_CHINA_ONLY
#define FONT_FILE_DEFAULT                   (  0)
#else
#define FONT_FILE_DEFAULT                   (  0)
#define FONT_FILE_VIETNAMES                 (  1)
#define FONT_FILE_ARABIC                    (  1)
#define FONT_FILE_INDONESIAN                (  1)
#define FONT_FILE_PERSIAN                   (  1)
#define FONT_FILE_S_CHINESE                 (  2)
#define FONT_FILE_T_CHINESE                 (  2)
#define FONT_FILE_THAI                      (  3)
#endif

/* SN_FONT_DEFAULT */
static FE_INIT_FILE  at_g_fe_init_sn_font_default[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_SMALL, APP_FONT_SIZE_MEDIUM, APP_FONT_SIZE_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_SMALL, APP_FONT_SIZE_MEDIUM, APP_FONT_SIZE_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_SMALL, APP_FONT_SIZE_MEDIUM, APP_FONT_SIZE_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_SMALL, APP_FONT_SIZE_MEDIUM, APP_FONT_SIZE_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_SMALL, APP_FONT_SIZE_MEDIUM, APP_FONT_SIZE_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_sn_font_default_size = sizeof (at_g_fe_init_sn_font_default) / sizeof (at_g_fe_init_sn_font_default[0]);

/* SN_FONT_DEFAULT_BIG */
static FE_INIT_FILE  at_g_fe_init_sn_font_default_big[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_BIG_SMALL, APP_FONT_SIZE_BIG_MEDIUM, APP_FONT_SIZE_BIG_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_BIG_SMALL, APP_FONT_SIZE_BIG_MEDIUM, APP_FONT_SIZE_BIG_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_BIG_SMALL, APP_FONT_SIZE_BIG_MEDIUM, APP_FONT_SIZE_BIG_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_BIG_SMALL, APP_FONT_SIZE_BIG_MEDIUM, APP_FONT_SIZE_BIG_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_BIG_SMALL, APP_FONT_SIZE_BIG_MEDIUM, APP_FONT_SIZE_BIG_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_sn_font_default_big_size = sizeof (at_g_fe_init_sn_font_default_big) / sizeof (at_g_fe_init_sn_font_default_big[0]);

/* SN_FONT_DEFAULT_SMALL */
static FE_INIT_FILE  at_g_fe_init_sn_font_default_small[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_SMALL_SMALL, APP_FONT_SIZE_SMALL_MEDIUM, APP_FONT_SIZE_SMALL_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_SMALL_SMALL, APP_FONT_SIZE_SMALL_MEDIUM, APP_FONT_SIZE_SMALL_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_SMALL_SMALL, APP_FONT_SIZE_SMALL_MEDIUM, APP_FONT_SIZE_SMALL_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_SMALL_SMALL, APP_FONT_SIZE_SMALL_MEDIUM, APP_FONT_SIZE_SMALL_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_SMALL_SMALL, APP_FONT_SIZE_SMALL_MEDIUM, APP_FONT_SIZE_SMALL_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_sn_font_default_small_size = sizeof (at_g_fe_init_sn_font_default_small) / sizeof (at_g_fe_init_sn_font_default_small[0]);

/* APP_FONT_NAV_S_NAME */
static FE_INIT_FILE  at_g_fe_init_app_font_nav_s[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_NAV_S_SMALL, APP_FONT_SIZE_NAV_S_MEDIUM, APP_FONT_SIZE_NAV_S_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_NAV_S_SMALL, APP_FONT_SIZE_NAV_S_MEDIUM, APP_FONT_SIZE_NAV_S_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_NAV_S_SMALL, APP_FONT_SIZE_NAV_S_MEDIUM, APP_FONT_SIZE_NAV_S_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_NAV_S_SMALL, APP_FONT_SIZE_NAV_S_MEDIUM, APP_FONT_SIZE_NAV_S_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_NAV_S_SMALL, APP_FONT_SIZE_NAV_S_MEDIUM, APP_FONT_SIZE_NAV_S_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_app_font_nav_s_size = sizeof (at_g_fe_init_app_font_nav_s) / sizeof (at_g_fe_init_app_font_nav_s[0]);

/* APP_FONT_MENU_NAME */
static FE_INIT_FILE  at_g_fe_init_app_font_menu[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_MENU_SMALL, APP_FONT_SIZE_MENU_MEDIUM, APP_FONT_SIZE_MENU_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_MENU_SMALL, APP_FONT_SIZE_MENU_MEDIUM, APP_FONT_SIZE_MENU_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_MENU_SMALL, APP_FONT_SIZE_MENU_MEDIUM, APP_FONT_SIZE_MENU_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_MENU_SMALL, APP_FONT_SIZE_MENU_MEDIUM, APP_FONT_SIZE_MENU_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_MENU_SMALL, APP_FONT_SIZE_MENU_MEDIUM, APP_FONT_SIZE_MENU_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_app_font_menu_size = sizeof (at_g_fe_init_app_font_menu) / sizeof (at_g_fe_init_app_font_menu[0]);

/* APP_FONT_NPG_NAME */
static FE_INIT_FILE  at_g_fe_init_app_font_npg[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_NPG_SMALL, APP_FONT_SIZE_NPG_MEDIUM, APP_FONT_SIZE_NPG_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_NPG_SMALL, APP_FONT_SIZE_NPG_MEDIUM, APP_FONT_SIZE_NPG_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_NPG_SMALL, APP_FONT_SIZE_NPG_MEDIUM, APP_FONT_SIZE_NPG_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_NPG_SMALL, APP_FONT_SIZE_NPG_MEDIUM, APP_FONT_SIZE_NPG_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_NPG_SMALL, APP_FONT_SIZE_NPG_MEDIUM, APP_FONT_SIZE_NPG_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_app_font_npg_size = sizeof (at_g_fe_init_app_font_npg) / sizeof (at_g_fe_init_app_font_npg[0]);

/* APP_FONT_EPG_NAME */
static FE_INIT_FILE  at_g_fe_init_app_font_epg[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_EPG_SMALL, APP_FONT_SIZE_EPG_MEDIUM, APP_FONT_SIZE_EPG_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_EPG_SMALL, APP_FONT_SIZE_EPG_MEDIUM, APP_FONT_SIZE_EPG_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_EPG_SMALL, APP_FONT_SIZE_EPG_MEDIUM, APP_FONT_SIZE_EPG_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_EPG_SMALL, APP_FONT_SIZE_EPG_MEDIUM, APP_FONT_SIZE_EPG_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_EPG_SMALL, APP_FONT_SIZE_EPG_MEDIUM, APP_FONT_SIZE_EPG_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_app_font_epg_size = sizeof (at_g_fe_init_app_font_epg) / sizeof (at_g_fe_init_app_font_epg[0]);

/* APP_FONT_TTX_NAME */
static FE_INIT_FILE  at_g_fe_init_app_font_ttx[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_TTX_SMALL, APP_FONT_SIZE_TTX_MEDIUM, APP_FONT_SIZE_TTX_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_TTX_SMALL, APP_FONT_SIZE_TTX_MEDIUM, APP_FONT_SIZE_TTX_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_TTX_SMALL, APP_FONT_SIZE_TTX_MEDIUM, APP_FONT_SIZE_TTX_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_TTX_SMALL, APP_FONT_SIZE_TTX_MEDIUM, APP_FONT_SIZE_TTX_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_TTX_SMALL, APP_FONT_SIZE_TTX_MEDIUM, APP_FONT_SIZE_TTX_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_app_font_ttx_size = sizeof (at_g_fe_init_app_font_ttx) / sizeof (at_g_fe_init_app_font_ttx[0]);

/* APP_FONT_WZD_NAME */
static FE_INIT_FILE  at_g_fe_init_app_font_wzd[] =
{
    #ifdef APP_REGION_CHINA_ONLY
    {"/mnt/fonts/ch_font.TTF",              APP_FONT_SIZE_WZD_SMALL, APP_FONT_SIZE_WZD_MEDIUM, APP_FONT_SIZE_WZD_LARGE },
    #else
    {"/mnt/fonts/tiresias.TTF",             APP_FONT_SIZE_WZD_SMALL, APP_FONT_SIZE_WZD_MEDIUM, APP_FONT_SIZE_WZD_LARGE },
    {"/mnt/fonts/DejaVuSans.TTF",           APP_FONT_SIZE_WZD_SMALL, APP_FONT_SIZE_WZD_MEDIUM, APP_FONT_SIZE_WZD_LARGE },
    {"/mnt/fonts/wqy-zenhei.TTF",           APP_FONT_SIZE_WZD_SMALL, APP_FONT_SIZE_WZD_MEDIUM, APP_FONT_SIZE_WZD_LARGE },
    {"/mnt/fonts/Kinnari.TTF",              APP_FONT_SIZE_WZD_SMALL, APP_FONT_SIZE_WZD_MEDIUM, APP_FONT_SIZE_WZD_LARGE },
    #endif
};
static const UINT8 ui1_g_fe_init_app_font_wzd_size = sizeof (at_g_fe_init_app_font_wzd) / sizeof (at_g_fe_init_app_font_wzd[0]);

#endif /* SYS_FLASH_FONT_SUPPORT */

/* Font Handles */
static HANDLE_T  h_g_font_custom_default_small        = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_medium       = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_large        = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_big_small    = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_big_medium   = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_big_large    = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_small_small  = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_small_medium = NULL_HANDLE;
static HANDLE_T  h_g_font_custom_default_small_large  = NULL_HANDLE;
/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    static functions implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _font_custom_add_ttf_mem_font
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _font_custom_add_ttf_mem_font (VOID)
{
    INT32  i4_ret               = 0;
    BOOL   b_success                  = FALSE;
    UINT32 ui4_font_size = GET_UINT32_FROM_PTR_BIG_END (&(font_file_default [0]));
    #ifdef APP_DVBT_SUPPORT
    UINT32 ui4_font_size_ttx20_bdf    = GET_UINT32_FROM_PTR_BIG_END (&(font_file_ttx20_bdf [0]));
    #endif /* APP_DVBT_SUPPORT */

    #ifdef VIZIO_FONTS
    UINT32 ui4_font_size_arialregular  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_arialregular [0]));
    UINT32 ui4_font_size_robotolight   = GET_UINT32_FROM_PTR_BIG_END (&(font_file_robotolight [0]));
    UINT32 ui4_font_size_robotomedium  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_robotomedium [0]));
    UINT32 ui4_font_size_robotoregular = GET_UINT32_FROM_PTR_BIG_END (&(font_file_robotoregular [0]));

    FE_INIT_DATA t_font_data_default[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_SMALL,APP_FONT_SIZE_MEDIUM,APP_FONT_SIZE_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_SMALL,APP_FONT_SIZE_MEDIUM,APP_FONT_SIZE_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_SMALL,APP_FONT_SIZE_MEDIUM,APP_FONT_SIZE_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_SMALL,APP_FONT_SIZE_MEDIUM,APP_FONT_SIZE_LARGE}};

    FE_INIT_DATA t_font_data_default_big[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_BIG_SMALL,APP_FONT_SIZE_BIG_MEDIUM,APP_FONT_SIZE_BIG_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_BIG_SMALL,APP_FONT_SIZE_BIG_MEDIUM,APP_FONT_SIZE_BIG_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_BIG_SMALL,APP_FONT_SIZE_BIG_MEDIUM,APP_FONT_SIZE_BIG_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_BIG_SMALL,APP_FONT_SIZE_BIG_MEDIUM,APP_FONT_SIZE_BIG_LARGE}};

    FE_INIT_DATA t_font_data_default_small[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_SMALL_SMALL,APP_FONT_SIZE_SMALL_MEDIUM,APP_FONT_SIZE_SMALL_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_SMALL_SMALL,APP_FONT_SIZE_SMALL_MEDIUM,APP_FONT_SIZE_SMALL_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_SMALL_SMALL,APP_FONT_SIZE_SMALL_MEDIUM,APP_FONT_SIZE_SMALL_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_SMALL_SMALL,APP_FONT_SIZE_SMALL_MEDIUM,APP_FONT_SIZE_SMALL_LARGE}};

    FE_INIT_DATA t_font_data_nav[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_NAV_S_SMALL,APP_FONT_SIZE_NAV_S_MEDIUM,APP_FONT_SIZE_NAV_S_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_NAV_S_SMALL,APP_FONT_SIZE_NAV_S_MEDIUM,APP_FONT_SIZE_NAV_S_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_NAV_S_SMALL,APP_FONT_SIZE_NAV_S_MEDIUM,APP_FONT_SIZE_NAV_S_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_NAV_S_SMALL,APP_FONT_SIZE_NAV_S_MEDIUM,APP_FONT_SIZE_NAV_S_LARGE}};

    FE_INIT_DATA t_font_data_menu[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_MENU_SMALL,APP_FONT_SIZE_MENU_MEDIUM,APP_FONT_SIZE_MENU_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_MENU_SMALL,APP_FONT_SIZE_MENU_MEDIUM,APP_FONT_SIZE_MENU_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_MENU_SMALL,APP_FONT_SIZE_MENU_MEDIUM,APP_FONT_SIZE_MENU_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_MENU_SMALL,APP_FONT_SIZE_MENU_MEDIUM,APP_FONT_SIZE_MENU_LARGE}};

    FE_INIT_DATA t_font_data_npg[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_NPG_SMALL,APP_FONT_SIZE_NPG_MEDIUM,APP_FONT_SIZE_NPG_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_NPG_SMALL,APP_FONT_SIZE_NPG_MEDIUM,APP_FONT_SIZE_NPG_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_NPG_SMALL,APP_FONT_SIZE_NPG_MEDIUM,APP_FONT_SIZE_NPG_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_NPG_SMALL,APP_FONT_SIZE_NPG_MEDIUM,APP_FONT_SIZE_NPG_LARGE}};

    FE_INIT_DATA t_font_data_epg[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_EPG_SMALL,APP_FONT_SIZE_EPG_MEDIUM,APP_FONT_SIZE_EPG_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_EPG_SMALL,APP_FONT_SIZE_EPG_MEDIUM,APP_FONT_SIZE_EPG_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_EPG_SMALL,APP_FONT_SIZE_EPG_MEDIUM,APP_FONT_SIZE_EPG_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_EPG_SMALL,APP_FONT_SIZE_EPG_MEDIUM,APP_FONT_SIZE_EPG_LARGE}};

    FE_INIT_DATA t_font_data_ttx[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_TTX_SMALL,APP_FONT_SIZE_TTX_MEDIUM,APP_FONT_SIZE_TTX_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_TTX_SMALL,APP_FONT_SIZE_TTX_MEDIUM,APP_FONT_SIZE_TTX_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_TTX_SMALL,APP_FONT_SIZE_TTX_MEDIUM,APP_FONT_SIZE_TTX_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_TTX_SMALL,APP_FONT_SIZE_TTX_MEDIUM,APP_FONT_SIZE_TTX_LARGE}};

    FE_INIT_DATA t_font_data_wzd[4] =
        {{(UINT8*)&(font_file_arialregular[4]),  ui4_font_size_arialregular,  APP_FONT_SIZE_WZD_SMALL,APP_FONT_SIZE_WZD_MEDIUM,APP_FONT_SIZE_WZD_LARGE},
         {(UINT8*)&(font_file_robotolight[4]),   ui4_font_size_robotolight,   APP_FONT_SIZE_WZD_SMALL,APP_FONT_SIZE_WZD_MEDIUM,APP_FONT_SIZE_WZD_LARGE},
         {(UINT8*)&(font_file_robotomedium[4]),  ui4_font_size_robotomedium,  APP_FONT_SIZE_WZD_SMALL,APP_FONT_SIZE_WZD_MEDIUM,APP_FONT_SIZE_WZD_LARGE},
         {(UINT8*)&(font_file_robotoregular[4]), ui4_font_size_robotoregular, APP_FONT_SIZE_WZD_SMALL,APP_FONT_SIZE_WZD_MEDIUM,APP_FONT_SIZE_WZD_LARGE}};

    /* Note:
        vizio fonts.
    */

    if ((c_fe_add_multiple_mem_font(SN_FONT_DEFAULT,         t_font_data_default,       4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(SN_FONT_DEFAULT_BIG,     t_font_data_default_big,   4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(SN_FONT_DEFAULT_SMALL,   t_font_data_default_small, 4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(APP_FONT_NAV_S_NAME,     t_font_data_nav,           4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(APP_FONT_MENU_NAME,      t_font_data_menu,          4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(APP_FONT_NPG_NAME,       t_font_data_npg,           4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(APP_FONT_EPG_NAME,       t_font_data_epg,           4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(APP_FONT_TTX_NAME,       t_font_data_ttx,           4)  == FER_OK)  &&
        (c_fe_add_multiple_mem_font(APP_FONT_WZD_NAME,       t_font_data_wzd,           4)  == FER_OK))
    {
        b_success = TRUE;
    }
    #endif /* VIZIO_FONTS */

    /* if loading region-specific fonts failed, try to load default fonts */
    if (b_success == FALSE)
    {
        if ((c_fe_add_mem_font(SN_FONT_DEFAULT,       &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_SMALL,       APP_FONT_SIZE_MEDIUM,       APP_FONT_SIZE_LARGE)       == FER_OK)  &&
            (c_fe_add_mem_font(SN_FONT_DEFAULT_BIG,   &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_BIG_SMALL,   APP_FONT_SIZE_BIG_MEDIUM,   APP_FONT_SIZE_BIG_LARGE)   == FER_OK)  &&
            (c_fe_add_mem_font(SN_FONT_DEFAULT_SMALL, &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_SMALL_SMALL, APP_FONT_SIZE_SMALL_MEDIUM, APP_FONT_SIZE_SMALL_LARGE) == FER_OK)  &&
            (c_fe_add_mem_font(APP_FONT_NAV_S_NAME,   &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_NAV_S_SMALL, APP_FONT_SIZE_NAV_S_MEDIUM, APP_FONT_SIZE_NAV_S_LARGE) == FER_OK)  &&
            (c_fe_add_mem_font(APP_FONT_MENU_NAME,    &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_MENU_SMALL,  APP_FONT_SIZE_MENU_MEDIUM,  APP_FONT_SIZE_MENU_LARGE)  == FER_OK)  &&
            (c_fe_add_mem_font(APP_FONT_NPG_NAME,     &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_NPG_SMALL,   APP_FONT_SIZE_NPG_MEDIUM,   APP_FONT_SIZE_NPG_LARGE)   == FER_OK)  &&
            (c_fe_add_mem_font(APP_FONT_EPG_NAME,     &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_EPG_SMALL,   APP_FONT_SIZE_EPG_MEDIUM,   APP_FONT_SIZE_EPG_LARGE)   == FER_OK)  &&
            (c_fe_add_mem_font(APP_FONT_TTX_NAME,     &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_TTX_SMALL,   APP_FONT_SIZE_TTX_MEDIUM,   APP_FONT_SIZE_TTX_LARGE)   == FER_OK)  &&
            (c_fe_add_mem_font(APP_FONT_WZD_NAME,     &(font_file_default [4]), ui4_font_size,  APP_FONT_SIZE_WZD_SMALL,   APP_FONT_SIZE_WZD_MEDIUM,   APP_FONT_SIZE_WZD_LARGE)   == FER_OK) )
        {
            /* EU Specific fonts */
            #ifdef APP_DVBT_SUPPORT
            if ((c_fe_add_mem_font("fnt_ttx20_bdf",   &(font_file_ttx20_bdf[4]), ui4_font_size_ttx20_bdf, 20, 20, 20) == FER_OK))
            {
                b_success = TRUE;
            }
            #else
            b_success = TRUE;
            #endif
        }
    }

    /* Font has been initialized. Create the font handle. */
    if (b_success == TRUE)
    {
        do
        {
            i4_ret = c_fe_create_font(SN_FONT_DEFAULT,      FE_FNT_SIZE_SMALL,
                                      FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_small);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT,      FE_FNT_SIZE_MEDIUM,
                                      FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_medium);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT,      FE_FNT_SIZE_LARGE,
                                      FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_large);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT_BIG,  FE_FNT_SIZE_SMALL,
                                      FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_big_small);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT_BIG,  FE_FNT_SIZE_MEDIUM,
                                      FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_big_medium);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT_BIG,  FE_FNT_SIZE_LARGE,
                                      FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_big_large);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT_SMALL, FE_FNT_SIZE_SMALL,
                                      FE_FNT_STYLE_REGULAR,  FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_small_small);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT_SMALL, FE_FNT_SIZE_MEDIUM,
                                      FE_FNT_STYLE_REGULAR,  FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_small_medium);
            if (FER_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_fe_create_font(SN_FONT_DEFAULT_SMALL, FE_FNT_SIZE_LARGE,
                                      FE_FNT_STYLE_REGULAR,  FE_CMAP_ENC_UNICODE,
                                      &h_g_font_custom_default_small_large);
            if (FER_OK != i4_ret)
            {
                break;
            }

        } while(0);

        b_success = TRUE;
    }

    return (b_success);
}

#ifdef SYS_FLASH_FONT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _font_custom_add_flash_ttf_mem_font
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _font_custom_add_flash_ttf_mem_font (VOID)
{
    INT32  i4_ret                  = 0;
    BOOL   b_success               = FALSE;
    #ifdef APP_DVBT_SUPPORT
    UINT32 ui4_font_size_ttx20_bdf = GET_UINT32_FROM_PTR_BIG_END (&(font_file_ttx20_bdf [0]));
    #endif

    do
    {
        /* SN Default */
        i4_ret = c_fe_add_multiple_file_font (SN_FONT_DEFAULT, at_g_fe_init_sn_font_default, ui1_g_fe_init_sn_font_default_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (SN_FONT_DEFAULT, X_FE_OPTION_FORCE);
            break;
        }
        /* SN Default Big */
        i4_ret = c_fe_add_multiple_file_font (SN_FONT_DEFAULT_BIG, at_g_fe_init_sn_font_default_big, ui1_g_fe_init_sn_font_default_big_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (SN_FONT_DEFAULT_BIG, X_FE_OPTION_FORCE);
            break;
        }
        /* SN Default Big */
        i4_ret = c_fe_add_multiple_file_font (SN_FONT_DEFAULT_SMALL, at_g_fe_init_sn_font_default_small, ui1_g_fe_init_sn_font_default_small_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (SN_FONT_DEFAULT_SMALL, X_FE_OPTION_FORCE);
            break;
        }
        /* NAV Small */
        i4_ret = c_fe_add_multiple_file_font (APP_FONT_NAV_S_NAME, at_g_fe_init_app_font_nav_s, ui1_g_fe_init_app_font_nav_s_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (APP_FONT_NAV_S_NAME, X_FE_OPTION_FORCE);
            break;
        }
        /* Menu */
        i4_ret = c_fe_add_multiple_file_font (APP_FONT_MENU_NAME, at_g_fe_init_app_font_menu, ui1_g_fe_init_app_font_menu_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (APP_FONT_MENU_NAME, X_FE_OPTION_FORCE);
            break;
        }
        /* NPG */
        i4_ret = c_fe_add_multiple_file_font (APP_FONT_NPG_NAME, at_g_fe_init_app_font_npg, ui1_g_fe_init_app_font_npg_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (APP_FONT_NPG_NAME, X_FE_OPTION_FORCE);
            break;
        }
        /* EPG */
        i4_ret = c_fe_add_multiple_file_font (APP_FONT_EPG_NAME, at_g_fe_init_app_font_epg, ui1_g_fe_init_app_font_epg_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (APP_FONT_EPG_NAME, X_FE_OPTION_FORCE);
            break;
        }
        /* TTX */
        i4_ret = c_fe_add_multiple_file_font (APP_FONT_TTX_NAME, at_g_fe_init_app_font_ttx, ui1_g_fe_init_app_font_ttx_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (APP_FONT_TTX_NAME, X_FE_OPTION_FORCE);
            break;
        }
        /* Wizard */
        i4_ret = c_fe_add_multiple_file_font (APP_FONT_WZD_NAME, at_g_fe_init_app_font_wzd, ui1_g_fe_init_app_font_wzd_size);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font (APP_FONT_WZD_NAME, X_FE_OPTION_FORCE);
            break;
        }
        #ifdef APP_DVBT_SUPPORT
        /* TTX used by MW */
        i4_ret = c_fe_add_mem_font("fnt_ttx20_bdf", &(font_file_ttx20_bdf[4]), ui4_font_size_ttx20_bdf, 20, 20, 20);
        if (i4_ret != FER_OK)
        {
            c_fe_remove_font ("fnt_ttx20_bdf", X_FE_OPTION_FORCE);
            break;
        }
        #endif

        /* reset to default font file */
        a_font_custom_change_font_resource(s639_app_cfg_lang_eng);

        /**/
        DBG_LOG_PRINT (("<FONT> Init flash font succeeded.\n"));
        b_success = TRUE;

    } while(0);

    if (b_success == FALSE)
    {
        DBG_INFO (("<FONT> Init flash font failed. Load default font.\n"));
        b_success = _font_custom_add_ttf_mem_font();
    }

    return (b_success);
}
#endif /* SYS_FLASH_FONT_SUPPORT */

/*-----------------------------------------------------------------------------
                    extern functions implementation
 ----------------------------------------------------------------------------*/
#ifdef SYS_FLASH_FONT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: a_font_custom_change_font_resource
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_font_custom_change_font_resource(ISO_639_LANG_T s639_lang)
{
    UINT8  ui1_font_file = FONT_FILE_DEFAULT;

    #ifdef APP_REGION_CHINA_ONLY
    /* use default font only */
    #else
    if      (c_strcmp(s639_lang, s639_app_cfg_lang_vie) == 0) { ui1_font_file = FONT_FILE_VIETNAMES; }
    else if (c_strcmp(s639_lang, s639_app_cfg_lang_ara) == 0) { ui1_font_file = FONT_FILE_ARABIC; }
    else if (c_strcmp(s639_lang, s639_app_cfg_lang_ind) == 0) { ui1_font_file = FONT_FILE_INDONESIAN; }
    else if (c_strcmp(s639_lang, s639_app_cfg_lang_per) == 0) { ui1_font_file = FONT_FILE_PERSIAN; }
    else if (c_strcmp(s639_lang, s639_app_cfg_lang_chi) == 0) { ui1_font_file = FONT_FILE_S_CHINESE; }
    else if (c_strcmp(s639_lang, s639_app_cfg_lang_zho) == 0) { ui1_font_file = FONT_FILE_T_CHINESE; }
    else if (c_strcmp(s639_lang, s639_app_cfg_lang_tha) == 0) { ui1_font_file = FONT_FILE_THAI; }
    else                                                      { ui1_font_file = FONT_FILE_DEFAULT; }
    #endif

    c_fe_change_font_resource (SN_FONT_DEFAULT,       ui1_font_file);
    c_fe_change_font_resource (SN_FONT_DEFAULT_BIG,   ui1_font_file);
    c_fe_change_font_resource (SN_FONT_DEFAULT_SMALL, ui1_font_file);
    c_fe_change_font_resource (APP_FONT_NAV_S_NAME,   ui1_font_file);
    c_fe_change_font_resource (APP_FONT_MENU_NAME,    ui1_font_file);
    c_fe_change_font_resource (APP_FONT_NPG_NAME,     ui1_font_file);
    c_fe_change_font_resource (APP_FONT_EPG_NAME,     ui1_font_file);
    c_fe_change_font_resource (APP_FONT_TTX_NAME,     ui1_font_file);
    c_fe_change_font_resource (APP_FONT_WZD_NAME,     ui1_font_file);
}
#endif /* SYS_FLASH_FONT_SUPPORT */

/*-----------------------------------------------------------------------------
 * Name: a_font_custom_init
 *
 * Description: This API initializes the fonts.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE if successfull else FALSE.
 ----------------------------------------------------------------------------*/
BOOL a_font_custom_init (VOID)
{
#ifdef SYS_FLASH_FONT_SUPPORT
    return _font_custom_add_flash_ttf_mem_font();
#else
    return _font_custom_add_ttf_mem_font();
#endif
}

/*-----------------------------------------------------------------------------
 * Name: a_font_custom_enable_unrecognize_char
 *
 * Description:
 *          This API enable unrecognize or not.
 * Inputs:
 *          BOOL        enable or not.
 * Outputs:
 *          None
 * Returns:
 *          0
 ----------------------------------------------------------------------------*/
INT32 a_font_custom_enable_unrecognize_char(BOOL b_enable)
{
    INT32       i4_ret = 0;
    CHAR_CODE   t_code_normal = 0x003F;
    CHAR_CODE   t_code_space  = 0x0020;
    CHAR_CODE   t_code;

    if (b_enable)
    {
        t_code = t_code_normal;
    }
    else
    {
        t_code = t_code_space;
    }

    do
    {
        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_small,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_medium,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_large,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_big_small,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_big_medium,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_big_large,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_small_small,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_small_medium,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

        i4_ret = c_fe_set_unrecognizable_char(h_g_font_custom_default_small_large,
                                              t_code);
        if (FER_OK != i4_ret)
        {
            break;
        }

    }while (0);

    return 0;
}


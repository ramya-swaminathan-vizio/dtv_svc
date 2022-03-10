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
 * $Revision$
 * $Date$
 * $Author$
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
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>

#include "c_common.h"
#include "c_svctx.h"
#include "c_pcl.h"
#include "c_dt.h"
#include "c_iom.h"
#include "c_scc.h"
#include "u_iom.h"
#include "u_irrc_btn_def.h"
#include "u_cecm.h"
#include "u_drv_cust.h"
#include "c_rm.h"
#include "c_fm.h"
#include "c_gl.h"
#include "u_fm.h"
#include "u_drv_cust.h"
#include "c_dbg.h"
#include "am/a_am.h"
#include "amb/a_amb.h"

#include "app_util/a_rating.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/a_common_setting.h"
#include "app_util/mapi_common/mapi_common.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/a_cec.h"
#include "nav/power/a_nav_power.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "menu2/menu_common/menu_common.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "nav/dialog/nav_dialog.h"
#include "nav/input_src/a_input_src.h"
#include "res/nav/banner2/banner_rc.h"
//#include "res/nav/cec2/nav_cec_custom.h"

#ifdef SYS_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif
#include"nav/zoom/nav_zoom.h"
#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#endif
#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT
#include "app_util/download_util/a_download_util.h"
#endif
#endif

#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "wizard_anim/a_wzd.h"
#include "u_wgl_common.h"
#include "wdk/util/wdk_wgl_util.h"

#include "app_util/config/_acfg.h"


#include "mi_common.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"
#include <sys/stat.h>
#include <dirent.h>
#include "mi_fs.h"

#undef MI_IMGDEC_FEATURE_ENABLE
#define MI_IMGDEC_FEATURE_ENABLE 1

#include "mi_imgdec.h"

//==================================================================================================
extern UINT32 nav_cec_custom_get_spd_info(UINT8 port, UINT8* description, UINT8 u8BufSize);
//==================================================================================================

#define ENABLE_TEST_CMD 1


//==================================================================================================


//
//
//
typedef struct _BOOT_LOGO_DATA_MEMBER_T
{
    GL_HSCREEN_T    h_screen;
    GL_HPLANE_T     h_plane;
    GL_HVIEW_T      h_view;
    GL_HSURFACE_T   h_surf;
    UINT32          ui4_viewport;
    HANDLE_T        h_main_frame;
    HANDLE_T        h_logo;
    HANDLE_T        h_canvas;
    BOOL            b_is_init;
}BOOT_LOGO_DATA_MEMBER_T;
static WGL_HIMG_TPL_T      h_logo_icon = NULL_HANDLE;
static BOOT_LOGO_DATA_MEMBER_T st_bootlogo = {NULL_HANDLE,NULL_HANDLE,NULL_HANDLE,NULL_HANDLE,0,FALSE};




#define _CONVERT_COLOR_FORMAT_MI_IMGDEC_TO_MI_OSD(pteOSDColorFmt, eIMGDECColorFmt)      \
{                                                               \
    switch(eIMGDECColorFmt)                                     \
    {                                                           \
        case E_MI_IMGDEC_COLOR_FMT_I1:                          \
        case E_MI_IMGDEC_COLOR_FMT_I2:                          \
        case E_MI_IMGDEC_COLOR_FMT_I4:                          \
        case E_MI_IMGDEC_COLOR_FMT_I8:                          \
        case E_MI_IMGDEC_COLOR_FMT_RGB565:                      \
        case E_MI_IMGDEC_COLOR_FMT_ARGB1555:                    \
        case E_MI_IMGDEC_COLOR_FMT_ARGB4444:                    \
            *pteOSDColorFmt = eIMGDECColorFmt;                  \
            break;                                              \
        case E_MI_IMGDEC_COLOR_FMT_YUV422:                      \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;   \
            break;                                              \
        case E_MI_IMGDEC_COLOR_FMT_ARGB8888:                    \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_ARGB8888;  \
            break;                                              \
        case E_MI_IMGDEC_COLOR_FMT_GENERIC:                     \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_GENERIC;   \
            break;                                              \
        default:                                                \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;   \
    }                                                           \
}                                                               \



#define _GET_MI_OSD_COLOR_FORMAT_BPP(eOSDColorFmt, pu8Bpp)      \
{                                                               \
    switch(eOSDColorFmt)                                        \
    {                                                           \
        case E_MI_OSD_COLOR_FORMAT_ARGB8888:                    \
        case E_MI_OSD_COLOR_FORMAT_ABGR8888:                    \
        case E_MI_OSD_COLOR_FORMAT_RGBA8888:                    \
        case E_MI_OSD_COLOR_FORMAT_BGRA8888:                    \
            *pu8Bpp = 4;                                        \
            break;                                              \
        case E_MI_OSD_COLOR_FORMAT_RGB565:                      \
        case E_MI_OSD_COLOR_FORMAT_BGR565:                      \
        case E_MI_OSD_COLOR_FORMAT_ARGB4444:                    \
        case E_MI_OSD_COLOR_FORMAT_ARGB1555:                    \
        case E_MI_OSD_COLOR_FORMAT_YUV422_YVYU:                 \
        case E_MI_OSD_COLOR_FORMAT_YUV422_UYVY:                 \
        case E_MI_OSD_COLOR_FORMAT_YUV422_YUYV:                 \
        case E_MI_OSD_COLOR_FORMAT_1ABFGBG12355:                \
        case E_MI_OSD_COLOR_FORMAT_FABAFGBG2266:                \
            *pu8Bpp = 2;                                        \
            break;                                              \
        case E_MI_OSD_COLOR_FORMAT_I1:                          \
        case E_MI_OSD_COLOR_FORMAT_I2:                          \
        case E_MI_OSD_COLOR_FORMAT_I4:                          \
        case E_MI_OSD_COLOR_FORMAT_I8:                          \
            *pu8Bpp = 1;                                        \
            break;                                              \
        default:                                                \
            *pu8Bpp = 0;                                        \
    }                                                           \
}                                                               \


#define _GET_IMAGE_FORMAT(u32ReadSign, ptIMG_Format)            \
{                                                               \
    UINT32 u32_temp = 0x0;                                      \
    u32_temp = u32ReadSign;                                     \
    switch(u32_temp & 0x0FFF0)                                  \
    {                                                           \
        case (E_MI_IMGDEC_FORMAT_JPEG & 0x0FFF0):               \
            u32_temp &= 0x0000FFFF;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_PNG & 0x0FFF0):                \
            u32_temp &= 0x00FFFF00;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_GIF & 0x0FFF0):                \
            u32_temp &= 0x00FFFFFF;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_BMP & 0x0FFF0):                \
            u32_temp &= 0x0000FFFF;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_MPO & 0xFFF0):                 \
            u32_temp &= 0x00FFFFFF;                             \
            break;                                              \
        default:                                                \
            u32_temp = 0x00FFFFFF;                              \
            break;                                              \
    }                                                           \
    *ptIMG_Format = u32_temp;                                   \
}                                                               \








#define GET_MQD_LOADING "/dtv_indicator"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define MAX_POSTAL_CODE_NUM (5)

#ifdef APP_EMANUAL_SP6_SUPPORT
typedef struct _APP_CFG_MC_VERSION_INFO_T
{
    CHAR     s_mg[32];
    CHAR     s_model_name[PLF_OPT_MODEL_NAME_LEN];
    CHAR     s_lang[3];
    CHAR     s_version[2];
    CHAR     s_ym[7];
    CHAR     s_status[2];
}APP_CFG_MC_VERSION_INFO_T;
#endif

static BOOL b_g_splash_show = FALSE;
static BOOL b_wake_from_suspend = FALSE;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static const UINT8 aui1_table[11][2] =
{
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE1},
    {APP_CFG_CUSTOM_ANA_CC_CC2, APP_CFG_CUSTOM_DIG_CC_SERVICE2},
    {APP_CFG_CUSTOM_ANA_CC_CC3, APP_CFG_CUSTOM_DIG_CC_SERVICE3},
    {APP_CFG_CUSTOM_ANA_CC_CC4, APP_CFG_CUSTOM_DIG_CC_SERVICE4},
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE5},
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE6},
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE1},
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE1},
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE1},
    {APP_CFG_CUSTOM_ANA_CC_CC1, APP_CFG_CUSTOM_DIG_CC_SERVICE1}
};
#define MAX_HDMI_INPUT 4
static BOOL e_hdmi_name[MAX_HDMI_INPUT]={FALSE};  // TRUE means use device name,FALSE means use user input name

/* SVL/TSL dual bank */
#ifdef APP_SVL_TSL_DUAL_BANK_SUPPORT
#ifdef APP_LST_MNGR_SUPPORT
    /* Notice:
        1. No keep dual bank status.
        2. The dual bank algorithm is provided by MW lst mngr.
        3. The dual bank status is controlled by MW lst mngr.
    */
#else
    static UINT8 ui1_g_svl_tsl_dual_bank = DUAL_BANK_SVL_TSL_INVALID;
#endif
#endif

static UINT8    ui1_timezone_def        = APP_CFG_CUST_TZ_PACIFIC_TIME;
static UINT8    ui1_dcc_def             = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
static UINT8    ui1_acc_def             = APP_CFG_CUSTOM_ANA_CC_CC1;
static BOOL     b_additional_scan_def   = FALSE;
static CHAR     s_inp_name_def [APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
static UINT8    ui1_op_mode_def         = A_CFG_OP_MODE_HOME;
static UINT8    aui1_postal_code[MAX_POSTAL_CODE_NUM] = {0};
static UINT8    ui1_ulpk_flag_def       = 1;
#ifdef APP_RETAIL_MODE_SUPPORT
static UINT8    ui1_retail_mode_def     = 0;
#endif
static UINT8    ui1_wzd_subpage_idx_def =  0;

static UINT8    ui1_cust_updater_completed = 0;

static UINT8 ui1_country_code = 0;
static UINT8 ui1_led_logo_ctrl = 0;

static UINT8    ui1_cust_nw_reg_status = 0;

/* tv name def*/
#ifdef APP_C4TV_SUPPORT
static UINT8    aui1_tv_name[MAX_TV_NAME_LEN] = {0};
#else
static UINT8    aui1_tv_name[MAX_TV_NAME_LEN] = {'V', 'I', 'Z', 'I', 'O', 'T', 'V', 0};
#endif
/* channel scan status */
static UINT8    aui1_cust_ch_scan_status[ACFG_CUST_BS_SRC_NUM] = {0};

/*wzd system upgrade def*/
static UINT8    ui1_cust_wzd_sys_upgrade_status_def = APP_CFG_CUST_WZD_SYS_UPDATE_INIT;

/* cast name def*/
static UINT8    aui1_cast_name_def[MAX_CAST_NAME_LEN] = {0};

/* zoom mode def */
static UINT8    ui1_cust_zoom_mode_def = APP_CFG_CUST_ZOOM_MODE_OFF;
static UINT8    ui1_cust_surround_mode_def = APP_CFG_CUST_SURROUND_VIRTUAL_X;

static UINT8    ui1_cust_bootup_assistant_flag_def = ACFG_BOOTUP_ASSISTANT_FAC_RESET;

static BOOL b_g_is_3rd_exist = FALSE;
static ACFG_INPUT_NAME_LATEST e_ipt_name;

#ifdef APP_EMANUAL_SP6_SUPPORT
static UTF16_T  w2s_test_mc_version[APP_CFG_MC_VERSION_LEN+1] = {0};
static APP_CFG_MC_VERSION_INFO_T t_mc_info;
#endif

static BOOL b_g_sys_pin_passed = FALSE;

static UINT8 ui1_fac_11_point_rgb_def[44] = {0};
static INT8  i1_fac_clr_tuner_def[4] = {0};

extern INT32  a_cfg_set_vchip_us_default(VOID);

//============================================================================================================
#if(ENABLE_TEST_CMD)
void acfg_cust_TestCmd_Init(void);
#endif
//============================================================================================================



/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/
static UINT16 _acfg_custom_misc_get_cc_rec_idx()
{
    ISL_REC_T   t_isl_rec;
    SVL_REC_T   t_svl_rec;
    BOOL        b_found = FALSE;

    acfg_get_crnt_isl_rec(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        acfg_get_crnt_svl_rec(&t_svl_rec, &b_found);
        if (b_found && t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
        {
            return IDX_DCC;
        }
    }

    return IDX_ACC;
}
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
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
extern INT32 acfg_cust_misc_pre_init(VOID)
{
    /* channel scan status */
    c_memset(aui1_cust_ch_scan_status, ACFG_CUST_CH_NOT_SCANED, sizeof(aui1_cust_ch_scan_status));

    /*init the cast name*/
    c_memset(aui1_cast_name_def, 0, sizeof(aui1_cast_name_def));

    DECLARE_FIELD(IDX_CUSTOM_TIMEZONE_IDX, APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_TIMEZONE,
                  CFG_8BIT_T,       1,     &ui1_timezone_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_DCC, APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_DIG_CC,
                  CFG_8BIT_T,       1,     &ui1_dcc_def,       1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_ACC, APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_ANLG_CC,
                  CFG_8BIT_T,       1,     &ui1_acc_def,       1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_ADDITIONAL_SCAN, APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_ADDITIONAL_SCAN,
                  CFG_8BIT_T,       1,     &b_additional_scan_def,      1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_1,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_1,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_2,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_2,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_3,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_3,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_4,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_4,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_5,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_5,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_6,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_6,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_7,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_7,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_8,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_8,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_9,    APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_9,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_INP_NAME_10,   APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_INP_NAME_10,
                  CFG_8BIT_T,       APP_CFG_CUSTOM_INP_NAME_LEN, s_inp_name_def, APP_CFG_CUSTOM_INP_NAME_LEN,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OP_MODE, APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_OP_MODE,
                  CFG_8BIT_T,       1,      &ui1_op_mode_def,        1,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_POSTAL_CODE,   APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_POSTAL_CODE,
                  CFG_8BIT_T, MAX_POSTAL_CODE_NUM, aui1_postal_code, MAX_POSTAL_CODE_NUM,
                  NULL,             NULL,   ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_ULPK_FLAG,     APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_ULPK_FLAG,
                  CFG_8BIT_T,       1,      &ui1_ulpk_flag_def,        1,
                  NULL,             NULL,   ACFG_ACCESS_FACTORY);

#ifdef APP_RETAIL_MODE_SUPPORT
    DECLARE_FIELD(IDX_CUSTOM_RETAIL_MODE,   APP_CFG_GRPID_DISP,        APP_CFG_RECID_DISP_CUSTOM_RETAIL_MODE,
                  CFG_8BIT_T,       1,      &ui1_retail_mode_def,       1,
                  NULL,             NULL,   ACFG_ACCESS_FACTORY);
#endif

    DECLARE_FIELD(IDX_CUSTOM_WZD_SUB_PAGE_IDX,     APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUSTOM_WZD_SUB_IDX,
                  CFG_8BIT_T,       1,      &ui1_wzd_subpage_idx_def,   1,
                  NULL,             NULL,   ACFG_ACCESS_FACTORY);

    DECLARE_FIELD(IDX_CUSTOM_UPDATER_COMPLETED,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUSTOM_UPDATER_COMPLETED,
                  CFG_8BIT_T,   1,      &ui1_cust_updater_completed,  1,
                  NULL,         NULL,   ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_COUNTRY_CODE,           APP_CFG_GRPID_CUSTOM_BASE,       APP_CFG_RECID_CUSTOM_COUNTRY_CODE,
                  CFG_8BIT_T,        1,              &ui1_country_code,               1,
                  NULL,           NULL,              ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_LED_LOGO_CTRL,           APP_CFG_GRPID_CUSTOM_BASE,       APP_CFG_RECID_CUSTOM_LED_LOGO_CTRL,
              CFG_8BIT_T,        1,               &ui1_led_logo_ctrl,               1,
              NULL,           NULL,              ACFG_ACCESS_PUBLIC);


    DECLARE_FIELD(IDX_CUST_NW_REG_STATUS,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_NW_REG_STATUS,
                  CFG_8BIT_T,   1,           &ui1_cust_nw_reg_status,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* FOR TV NAME*/
    DECLARE_FIELD(IDX_CUST_TV_NAME,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_TV_NAME,
                  CFG_8BIT_T,   MAX_TV_NAME_LEN,           aui1_tv_name,  MAX_TV_NAME_LEN,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* channel scan status*/
    DECLARE_FIELD(IDX_CUST_CH_SCAN_STATUS,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_CH_SCAN_STATUS,
                  CFG_8BIT_T,   ACFG_CUST_BS_SRC_NUM,           aui1_cust_ch_scan_status,  ACFG_CUST_BS_SRC_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* wzd system upgrade status*/
    DECLARE_FIELD(IDX_CUST_WZD_SYS_UPGRADE_STATUS,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_WZD_SYS_UPGRADE_STATUS,
                  CFG_8BIT_T,   1,           &ui1_cust_wzd_sys_upgrade_status_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* cast name*/
    DECLARE_FIELD(IDX_CUST_CAST_NAME,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_CAST_NAME,
                  CFG_8BIT_T,   MAX_CAST_NAME_LEN,           aui1_cast_name_def,  MAX_CAST_NAME_LEN,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* Zoom mode */
    DECLARE_FIELD(IDX_CUST_ZOOM_MODE,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_ZOOM_MODE,
                  CFG_8BIT_T,   1,           &ui1_cust_zoom_mode_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* Bootup assistant flag */
    DECLARE_FIELD(IDX_CUST_BOOTUP_ASSISTANT, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_BOOTUP_ASSISTANT_FLAG,
                  CFG_8BIT_T,   1,           &ui1_cust_bootup_assistant_flag_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* factory 11 point R  */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_11_POINT_RED,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_11_POINT_RED,
                  CFG_8BIT_T,   4*11,           ui1_fac_11_point_rgb_def,  4*11,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory 11 point R  */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_11_POINT_GREEN,
                  CFG_8BIT_T,   4*11,           ui1_fac_11_point_rgb_def,  4*11,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory 11 point B  */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_11_POINT_BLUE,
                  CFG_8BIT_T,   4*11,           ui1_fac_11_point_rgb_def,  4*11,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Hue R */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_R,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Hue G */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_G,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Hue B */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_B,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Hue C */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_C,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Hue M */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_M,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Hue Y */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_Y,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Sat R */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_R,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Sat G */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_G,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Sat B */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_B,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Sat C */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_C,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Sat M */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_M,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner Sat Y */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_Y,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner BRI R */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_R,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner BRI G */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_G,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner BRI B */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_B,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner BRI C */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_C,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner BRI M */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_M,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* factory Color Tuner BRI Y */
    DECLARE_FIELD(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y, APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_Y,
                  CFG_8BIT_T,   4,           i1_fac_clr_tuner_def,  4,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);
     /* surrond mode */
    DECLARE_FIELD(IDX_CUST_SURROUND_MODE,   APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_SURROUND_MODE,
                  CFG_8BIT_T,   1,           &ui1_cust_surround_mode_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

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
extern INT32 acfg_cust_misc_post_init(VOID)
{
    /* Update Power on/Power off Timer by Day_Sec */
    ACFG_LOG_ON_FAIL(a_cfg_update_timer_power());
    ACFG_LOG_ON_FAIL(a_cfg_custom_update_dimming_idx());
    //ACFG_LOG_ON_FAIL( a_cfg_custom_draw_logo_init());

#if(ENABLE_TEST_CMD)
    acfg_cust_TestCmd_Init();
#endif

#if(ENABLE_ACFG_HDMI_TASK)
    acfg_cust_HDMI_task_init();
#endif

#if(ENABLE_VIZIO_AUTO_PC)
    acfg_cust_AutoPc_init();
#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_chk_universal_password
 *
 * Description:
 *      Check the universal password. Return true if the passowrd match the
 *  universal password.
 *
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
#ifdef  ACFG_USE_UNIVERSAL_PASSWORD
extern INT32 acfg_custom_chk_universal_password(UTF16_T* w2s_pwd,
                                                BOOL* pb_pass)
{
    UTF16_T* w2s_universal_pwd = (UTF16_T*)(L"5351");

    if(w2s_pwd == NULL || pb_pass == NULL)
    {
        return -1;
    }

    if(c_uc_w2s_strcmp(w2s_pwd, w2s_universal_pwd) == 0)
    {
        *pb_pass = TRUE;
    }
    else
    {
        *pb_pass = FALSE;
    }
    return 0;
}
#endif

#ifndef APP_LST_MNGR_SUPPORT
#ifdef  APP_SVL_TSL_DUAL_BANK_SUPPORT
/*-----------------------------------------------------------------------------
 * Name:
 *      acfg_custom_get_svl_tsl_dual_bank
 * Description:
 *      get the svl tsl dual bank id.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern UINT8 acfg_custom_get_svl_tsl_dual_bank(VOID)
{
    INT32  i4_ret;
    /*  Notice:
            1. Carefully using a_cfg_set_svl_tsl_dual_bank() & a_cfg_get_svl_tsl_dual_bank()
            2. They shall be used in the dual bank customized get/lock/unlock functions only.
            3. The application shall use acfg_custom_get_svl_tsl_dual_bank to determine Main/Sub only.
    */
    if (ui1_g_svl_tsl_dual_bank == DUAL_BANK_SVL_TSL_INVALID)
    {
        /* 1. only get Main/Sub once when TV is powering on.
           2. cache Main/Sub and return Main/Sub directly by cached value after power on.
        */
        i4_ret = a_cfg_get_svl_tsl_dual_bank(& ui1_g_svl_tsl_dual_bank);
        if ((i4_ret != APP_CFGR_OK)
            ||
            (DUAL_BANK_GET_SVL_TSL_MAIN_SUB(ui1_g_svl_tsl_dual_bank) != DUAL_BANK_SVL_TSL_MAIN &&
             DUAL_BANK_GET_SVL_TSL_MAIN_SUB(ui1_g_svl_tsl_dual_bank) != DUAL_BANK_SVL_TSL_SUB))
        {
            ui1_g_svl_tsl_dual_bank = DUAL_BANK_SVL_TSL_MAIN;
        }

        if (DUAL_BANK_IS_SVL_TSL_FLUSHING(ui1_g_svl_tsl_dual_bank))
        {
            /* Notice:
               The flushing precess is broken. The SVL/TSL is not stored successfully.
               Use the other bank to resotre the previous SVL/TSL.
            */
            if (DUAL_BANK_GET_SVL_TSL_MAIN_SUB(ui1_g_svl_tsl_dual_bank) == DUAL_BANK_SVL_TSL_MAIN)
            {
                ui1_g_svl_tsl_dual_bank = DUAL_BANK_SVL_TSL_SUB;
            }
            else
            {
                ui1_g_svl_tsl_dual_bank = DUAL_BANK_SVL_TSL_MAIN;
            }
            ACFG_LOG_ON_FAIL(a_cfg_set_svl_tsl_dual_bank(ui1_g_svl_tsl_dual_bank));
        }
    }

    if (ui1_g_svl_tsl_dual_bank == DUAL_BANK_SVL_TSL_MAIN)
    {
        return DUAL_BANK_SVL_TSL_MAIN;
    }
    else
    {
        /* Notice:
                Make sure the values will be expected. For example: the value got in above
                codes is 255 (same as DUAL_BANK_SVL_TSL_INVALID) and successfully return.
                In this case, the flow of getting values will enter twice instead of once. <- Exception
        */
        ui1_g_svl_tsl_dual_bank = DUAL_BANK_SVL_TSL_SUB;

        return DUAL_BANK_SVL_TSL_SUB;
    }
}
/*-----------------------------------------------------------------------------
 * Name:
 *      acfg_custom_lock_svl_tsl_dual_bank
 * Description:
 *      turn on dirty flag and store with the svl tsl dual bank id.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern VOID acfg_custom_lock_svl_tsl_dual_bank(VOID)
{
    /*  1. Toggle Main/Sub in Config for next power-on
        2. Actually toggle Main/Sub when the SVL/TSL is storing and stored.
    */
    if (ui1_g_svl_tsl_dual_bank == DUAL_BANK_SVL_TSL_INVALID)
    {
        /* 1. Main/Sub ID is reset by acfg_custom_reset_svl_tsl_dual_bank ()
           2. Get current Main/Sub ID.
        */
        ACFG_LOG_ON_FAIL(acfg_custom_get_svl_tsl_dual_bank());
    }

    if (ui1_g_svl_tsl_dual_bank == DUAL_BANK_SVL_TSL_MAIN)
    {
        a_cfg_set_svl_tsl_dual_bank(DUAL_BANK_SVL_TSL_SUB | DUAL_BANK_SVL_TSL_FLUSHING);
    }
    else
    {
        ACFG_LOG_ON_FAIL(a_cfg_set_svl_tsl_dual_bank(DUAL_BANK_SVL_TSL_MAIN | DUAL_BANK_SVL_TSL_FLUSHING));
    }
    /* immediately store dual bank status */
    a_cfg_store();
}
/*-----------------------------------------------------------------------------
 * Name:
 *      acfg_custom_unlock_svl_tsl_dual_bank
 * Description:
 *      turn off dirty flag and store with the svl tsl dual bank id.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern VOID acfg_custom_unlock_svl_tsl_dual_bank(VOID)
{
    /*
        1. Toggle Main/Sub in Config for next power-on
        2. Actually toggle Main/Sub when the SVL/TSL is storing and stored.
    */
    if (ui1_g_svl_tsl_dual_bank == DUAL_BANK_SVL_TSL_INVALID)
    {
        /* 1. Main/Sub ID is reset by acfg_custom_reset_svl_tsl_dual_bank ()
           2. Get current Main/Sub ID.
        */
        ACFG_LOG_ON_FAIL(acfg_custom_get_svl_tsl_dual_bank());
    }

    if (ui1_g_svl_tsl_dual_bank == DUAL_BANK_SVL_TSL_MAIN)
    {
        ACFG_LOG_ON_FAIL(a_cfg_set_svl_tsl_dual_bank(DUAL_BANK_SVL_TSL_SUB));
    }
    else
    {
        ACFG_LOG_ON_FAIL(a_cfg_set_svl_tsl_dual_bank(DUAL_BANK_SVL_TSL_MAIN));
    }
    /* immediately store dual bank status */
    a_cfg_store();
}
/*-----------------------------------------------------------------------------
 * Name:
 *      acfg_custom_reset_svl_tsl_dual_bank
 * Description:
 *      reset dirty flag for next load with the svl tsl dual bank id.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern VOID acfg_custom_reset_svl_tsl_dual_bank(VOID)
{
    /*
        If there are reload request in software, this API shall be invoked
        after all svl/tsl store are successfully finished.
    */
    ui1_g_svl_tsl_dual_bank = DUAL_BANK_SVL_TSL_INVALID;
}
#endif /* APP_SVL_TSL_DUAL_BANK_SUPPORT */
#endif /* APP_LST_MNGR_SUPPORT */

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_timezone_idx (UINT8 ui1_idx)
{
    return acfg_set(IDX_CUSTOM_TIMEZONE_IDX, &ui1_idx, 1);
}

INT32 a_cfg_custom_get_timezone_idx (UINT8* pui1_idx)
{
    SIZE_T  z_size;

    if (!pui1_idx)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_TIMEZONE_IDX, (VOID*)pui1_idx, &z_size);
}
extern HANDLE_T a_nav_get_ui_canvas(VOID);

INT32 a_cfg_custom_set_ipcc_idx(MM_SVC_CC_IDX_INFO_T* pt_cc_info)
{
    INT32                   i4_ret = APP_CFGR_OK;

#ifdef APP_IPCC_SUPPORT
    UINT8                   ui1_enabled = FALSE;
    UINT8                   ui1_idx = 0;
    HANDLE_T                h_svctx = NULL_HANDLE;
    CHAR                    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    MM_SVC_CC_IDX_INFO_T    t_cc_info = {0};
    HANDLE_T                h_handle  = a_nav_get_ui_canvas(); //a_nav_get_cc_canvas();

    if (pt_cc_info != NULL)
    {
        t_cc_info.b_enable = pt_cc_info->b_enable;
        t_cc_info.ui1_idx = pt_cc_info->ui1_idx;
    }
    else
    {
        a_cfg_get_cc_enabled(&ui1_enabled);
        a_cfg_get_dig_cc(&ui1_idx);

        t_cc_info.ui1_idx = ui1_idx;
        t_cc_info.b_enable = (ui1_enabled != 0) ? TRUE : FALSE;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_get_svctx(s_disp_name, &h_svctx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Set IPCC Index */
    i4_ret = c_svctx_generic_set_info(h_svctx,
                                        NULL_HANDLE,
                                        SVCTX_MM_SET_CC_IDX,
                                        (VOID*)(&t_cc_info),
                                        sizeof(MM_SVC_CC_IDX_INFO_T));
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Set IPCC OSD */
    i4_ret = c_svctx_generic_set_info(h_svctx,
                                        NULL_HANDLE,
                                        SVCTX_MM_SET_CC_CANVAS,
                                        (VOID*)(&h_handle),
                                        sizeof(HANDLE_T));
    ACFG_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("<ACFG> %s() Line %d: set ipcc info = [%s, %d]\n\n",
                                __FUNCTION__,
                                __LINE__,
                                t_cc_info.b_enable == TRUE ? "true" : "false",
                                t_cc_info.ui1_idx));
#endif

    return i4_ret;
}

extern INT32  a_cfg_custom_map_cc(VOID)
{
    SIZE_T  z_size;
    INT8    i1_acc = 0;
    INT8    i1_dcc = 0;
    UINT8   ui1_acc_val = 0;
    UINT8   ui1_dcc_val = 0;
    UINT8   ui1_enabled = 0;
    INT32    i4_ret = 0;;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    /*DTV00572633  form older version updates to new version*/
    i4_ret = acfg_get(IDX_ACC, &i1_acc , &z_size);
    ACFG_LOG_ON_FAIL (i4_ret);
    i4_ret = acfg_get(IDX_DCC, &i1_dcc , &z_size);
    ACFG_LOG_ON_FAIL (i4_ret);
    DBG_INFO(("\n==a_cfg_custom_get_anlg_cc=acc==%d,===dcc=%d==%d\n",i1_acc,i1_dcc,__LINE__));

    if((i1_acc == 0) && (i1_dcc == 0))
    {
        ui1_enabled = APP_CFG_CC_OFF;
        acfg_set(IDX_CC_ENABLED, &ui1_enabled , 1);

        ui1_acc_val = APP_CFG_CUSTOM_ANA_CC_CC1;
        acfg_set(IDX_ACC, &ui1_acc_val , 1);

        ui1_dcc_val = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
        acfg_set(IDX_DCC, &ui1_dcc_val , 1);

        DBG_INFO(("\n=a_cfg_custom_get_dig_cc=[ui1_enabled=%d]==[ui1_acc_val=%d]==[ui1_dcc_val=%d]=[line=%d]\n",ui1_enabled,ui1_acc_val,ui1_dcc_val,__LINE__));
        DBG_INFO(("\n=for==[i1_acc=%d]=[i1_dcc=%d]==[line=%d]\n",i1_acc,i1_dcc,__LINE__));

    }

    else
    {
        ui1_enabled = APP_CFG_CC_ON;
        acfg_set(IDX_CC_ENABLED, &ui1_enabled , 1);

        ui1_acc_val = APP_CFG_CUSTOM_ANA_CC_CC1;
        acfg_set(IDX_ACC, &ui1_acc_val , 1);

        ui1_dcc_val = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
        acfg_set(IDX_DCC, &ui1_dcc_val , 1);

        DBG_INFO(("\n=a_cfg_custom_get_dig_cc=[ui1_enabled=%d]==[ui1_acc_val=%d]==[ui1_dcc_val=%d]=[line=%d]\n",ui1_enabled,ui1_acc_val,ui1_dcc_val,__LINE__));
        DBG_INFO(("\n=for==[i1_acc=%d]=[i1_dcc=%d]==[line=%d]\n",i1_acc,i1_dcc,__LINE__));
    }

    return i4_ret;
}

INT32 a_cfg_custom_set_cc_idx (UINT8 ui1_idx)
{
    UINT16 ui2_rec_idx = _acfg_custom_misc_get_cc_rec_idx ();
    INT16 i2_val = ui1_idx;
    INT32   i4_ret = 0;

    i4_ret = acfg_set(ui2_rec_idx, &i2_val, 1);

    if (APP_CFGR_OK == i4_ret)
    {
        a_cfg_custom_plf_opt_set_cc_onoff(ui1_idx);
    }

    if (IDX_DCC == ui2_rec_idx)
    {
        a_cfg_custom_set_ipcc_idx(NULL);
    }

    return i4_ret;
}

INT32 a_cfg_custom_get_cc_idx (UINT8* pui1_idx)
{
    SIZE_T      z_size;
    UINT16 ui2_rec_idx = _acfg_custom_misc_get_cc_rec_idx ();
    INT16 i2_val = 0;
    INT32 i4_ret;

    if (!pui1_idx)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(ui2_rec_idx, (VOID*)&i2_val, &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pui1_idx = (UINT8) i2_val;

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_get_cc_val (UINT8* pui1_acc, UINT8* pui1_dcc)
{
    INT32 i4_ret;
    UINT8 ui1_dcc_idx = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
    UINT8 ui1_acc_idx = APP_CFG_CUSTOM_ANA_CC_CC1;

    if(!pui1_acc || !pui1_dcc)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_get_anlg_cc(&ui1_acc_idx);
    if(i4_ret != APP_CFGR_OK)
    {
       return i4_ret;
    }

    i4_ret = a_cfg_get_dig_cc(&ui1_dcc_idx);
    if(i4_ret != APP_CFGR_OK)
    {
       return i4_ret;
    }

    if(ui1_dcc_idx >= 6)
    {
        ui1_dcc_idx = 0;
    }
    if(ui1_acc_idx >= 4)
    {
        ui1_acc_idx = 0;
    }
    *pui1_acc = aui1_table[ui1_acc_idx][0];
    *pui1_dcc = aui1_table[ui1_dcc_idx][1];

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_set_additional_scan (UINT8 ui1_val)
{
    INT16 i2_val = ui1_val;

    return acfg_set (IDX_CUSTOM_ADDITIONAL_SCAN, &i2_val, 1);
}
INT32 a_cfg_custom_get_additional_scan(UINT8* pui1_val)
{
    INT32 i4_ret;
    INT16 i2_val = 0;
    SIZE_T z_size;

    if (!pui1_val)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get (IDX_CUSTOM_ADDITIONAL_SCAN, &i2_val, &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pui1_val = (UINT8) i2_val;

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_set_ulpk_flag(BOOL b_ulpk_flag)
{
    INT16 i2_val =(INT16)b_ulpk_flag;

    return acfg_set(IDX_CUSTOM_ULPK_FLAG, &i2_val, 1);
}
INT32 a_cfg_custom_get_ulpk_flag(BOOL* b_ulpk_flag)
{
    SIZE_T          z_size;
    INT32 i4_ret;
    INT16 i2_val = 0;

    if (NULL == b_ulpk_flag)
    {
        return APP_CFGR_INV_ARG;
    }
    i4_ret = acfg_get(IDX_CUSTOM_ULPK_FLAG, &i2_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *b_ulpk_flag = (BOOL) i2_val;

    return APP_CFGR_OK;
}

static INT32 _acfg_custom_reset_unrated_setting (VOID)
{
    UINT8   ui1_mpaa        = APP_CFG_VCHIP_US_MPAA_OFF;
    UINT8   ui1_tv_age      = APP_CFG_VCHIP_US_AGE_OFF;
    UINT64  ui8_tv_cnt_map  = 0;
    BOOL    b_mpaa_bu       = FALSE;
    BOOL    b_tv_bu         = FALSE;
    BOOL    b_block         = FALSE;

    a_cfg_lock();

    a_cfg_set_vchip_unrated (b_block);

    a_cfg_get_vchip_us (
                &ui1_mpaa,
                &ui1_tv_age,
                &ui8_tv_cnt_map,
                &b_mpaa_bu,
                &b_tv_bu);

    a_cfg_set_vchip_us (
                ui1_mpaa,
                ui1_tv_age,
                ui8_tv_cnt_map,
                b_block,
                b_block);

    a_cfg_unlock();

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_reset_channel_lock (VOID)
{
    a_rating_atsc_storage(FALSE);

    acfg_set_default (IDX_VCHIP_US);
    a_cfg_set_vchip_us_default();

    acfg_set_default (IDX_VCHIP_CA);
    a_cfg_set_vchip_ca (APP_CFG_VCHIP_CA_EN_OFF, APP_CFG_VCHIP_CA_FR_OFF);

    acfg_set_default (IDX_VCHIP_UNRATED);
    _acfg_custom_reset_unrated_setting ();

    acfg_set_default (IDX_VCHIP_REGION);
    a_cfg_update_vchip_rating_region ();

    acfg_set_default (IDX_RATING_ENABLED);
    a_cfg_update_rating_settings ();

    /* Reset Block Channel */ //added,hank,20110304
    a_cfg_reset_svl_by_mask(h_g_acfg_svl_air,
                           SB_VNET_BLOCKED,
                           0);
    a_cfg_reset_svl_by_mask(h_g_acfg_svl_cable,
                           SB_VNET_BLOCKED,
                           0);
    c_svctx_unblock_svc(h_g_acfg_svctx_main, TRUE);
    a_cfg_ch_lst_store();

    return APP_CFGR_OK;
}


#define         W2S_HDMI_NAME_LEN   32

INT32 a_cfg_custom_set_inp_name (UINT8 ui1_input_id, CHAR* s_inp_name)
{
    UINT16  ui2_cfg_idx;
    UINT16  ui2_mlm_idx = 0xFFFF;
    UINT8   ui1_num;
    INT32   i4_ret;
    UINT8   ui1_val = ICL_RECID_CUSTOM_INPUT_NAME_CHANGE;
    SIZE_T  z_size = ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE;
    ISL_REC_T       t_isl_rec;

    UTF16_T     W2S_HDMI_NAME[W2S_HDMI_NAME_LEN] = {0};

    i4_ret = a_isl_get_num_rec(&ui1_num);
    ACFG_LOG_ON_FAIL(i4_ret);
    if (ui1_input_id >= ui1_num)
    {
        return APP_CFGR_INV_ARG;
    }

    a_isl_get_rec_by_idx(ui1_input_id, &t_isl_rec);
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        i4_ret = get_cec_device_name(t_isl_rec.ui1_internal_id, W2S_HDMI_NAME, W2S_HDMI_NAME_LEN);
        S_HDMI_NAME_T CFG_HDMI_NAME;

        if ((MENUR_OK == i4_ret) && (c_uc_w2s_strlen(W2S_HDMI_NAME) != 0))
        {
            c_uc_w2s_to_ps(W2S_HDMI_NAME, CFG_HDMI_NAME.cec_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            CFG_HDMI_NAME.show_cec_name = FALSE;
            a_nav_ipts_set_cec_name(t_isl_rec.ui1_internal_id, &CFG_HDMI_NAME);
        }
        else
        {
            if (a_nav_ipts_get_cec_name(t_isl_rec.ui1_internal_id, &CFG_HDMI_NAME) == TRUE)
            {
                CFG_HDMI_NAME.show_cec_name = TRUE;
                a_nav_ipts_set_cec_name(t_isl_rec.ui1_internal_id, &CFG_HDMI_NAME);
            }
        }
        DBG_LOG_PRINT(("[%s] show_cec_name: %d \n", __FUNCTION__, CFG_HDMI_NAME.show_cec_name));
        DBG_LOG_PRINT(("default hdmi name [%d]: %s \n", t_isl_rec.ui1_internal_id, CFG_HDMI_NAME.cec_name));
        //e_hdmi_name[t_isl_rec.ui1_internal_id] = FALSE;
        a_cfg_set_the_hdmi_priority_name(t_isl_rec.ui1_internal_id, FALSE);
    }

    a_cfg_custom_set_input_name_flag(ACFG_INPUT_NAME_IPT_LABEL);

    if ((ui2_mlm_idx = menu_page_naming_is_predef_name(s_inp_name)) != 0xFFFF)
    {
        c_uc_w2s_to_ps(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, ui2_mlm_idx),
                       s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }

    ui2_cfg_idx = IDX_CUSTOM_INP_NAME_1 + ui1_input_id;

    i4_ret = acfg_set(ui2_cfg_idx, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    if(i4_ret < 0)
    {
        DBG_INFO(("[%s][%d] acfg_set fail \r\n", __FUNCTION__, __LINE__));
    }

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE,
              ICL_RECID_CUSTOM_FLAG_CHANGE),
              (VOID*) &ui1_val, z_size);

  #if 0 // debug
    {
        UTF16_T     s_inp_name_dbg[W2S_HDMI_NAME_LEN+1] = {0};
        c_uc_w2s_to_ps(s_inp_name, s_inp_name_dbg, W2S_HDMI_NAME_LEN);
        DBG_LOG_PRINT (("<< [%s] s_inp_name: %s \n\n", __FUNCTION__, s_inp_name_dbg));
    }
  #endif

    return i4_ret;

}
INT32 a_cfg_custom_set_cec_name (UINT8 ui1_cec_idx, CHAR* s_cec_name)
{
    UINT16  ui2_cfg_idx;
    UINT8   ui1_num;
    INT32   i4_ret;

    i4_ret = a_isl_get_num_rec(&ui1_num);
    ACFG_LOG_ON_FAIL(i4_ret);

    ui2_cfg_idx = IDX_CUSTOM_INP_NAME_1 + ui1_num + ui1_cec_idx;
    return acfg_set(ui2_cfg_idx, s_cec_name, APP_CFG_CUSTOM_INP_NAME_LEN);
}
INT32 a_cfg_custom_get_cec_name (UINT8 ui1_cec_idx, CHAR* s_cec_name)
{
    UINT16  ui2_cfg_idx;
    SIZE_T  z_size;
    UINT8   ui1_num;
    INT32   i4_ret;

    if (!s_cec_name)
    {
        return APP_CFGR_INV_ARG;
    }
    i4_ret = a_isl_get_num_rec(&ui1_num);
    ACFG_LOG_ON_FAIL(i4_ret);

    ui2_cfg_idx = IDX_CUSTOM_INP_NAME_1 + ui1_num + ui1_cec_idx;
    return acfg_get(ui2_cfg_idx, s_cec_name, &z_size);
}
/**
 * @brief   This function returns the user input label. If current input is HDMI
 *          and user input label is empty, it will return the device OSD name
 *          if available.
 * @param   ISL_REC_T [in]      A pointer to current ISL record.
 * @param   s_inp_name [out]    The input label or the HDMI device name.
 * @retval  APP_CFGR_OK     The function succeded.
 * @retval  Otherwise       The function failed.
 */
INT32 a_cfg_custom_get_inp_name (UINT8 ui1_input_id, CHAR* s_inp_name)
{
    UINT16  ui2_cfg_idx;
    UINT16  ui2_mlm_idx = 0;
    SIZE_T  z_size;
    UINT8   ui1_num;
    INT32   i4_ret = APP_CFGR_OK;
    CHAR    s_tmp_name[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};


    ACFG_DEBUG_INPUT_SRC_NAME( DBG_LOG_PRINT (("[ACFG][INPUT_SRC] {%s,%d} ui1_input_id:%d \n",
        __FUNCTION__, __LINE__, ui1_input_id )); );

    if (!s_inp_name)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_isl_get_num_rec(&ui1_num);
    ACFG_LOG_ON_FAIL(i4_ret);

    if (ui1_input_id >= ui1_num)
    {
        return APP_CFGR_INV_ARG;
    }

    ui2_cfg_idx = IDX_CUSTOM_INP_NAME_1 + ui1_input_id;
    i4_ret = acfg_get(ui2_cfg_idx, s_inp_name, &z_size);

    if (APP_CFGR_OK == i4_ret)
    {
        ui2_mlm_idx = menu_page_naming_is_predef_name(s_inp_name);

        if (ui2_mlm_idx != 0xFFFF)
        {
            c_uc_w2s_to_ps(MENU_TEXT(ui2_mlm_idx), s_tmp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_strcpy(s_inp_name, s_tmp_name);
            s_inp_name[c_strlen(s_tmp_name)] = 0;
        }
    }

    return i4_ret;
}

VOID a_cfg_set_the_hdmi_priority_name(UINT8 ui1_internal_id,BOOL b_use_device_name)
{
    if((ui1_internal_id < MAX_HDMI_INPUT)&&
      (ui1_internal_id >= 0))
    {
        e_hdmi_name[ui1_internal_id] = b_use_device_name;
        DBG_LOG_PRINT (("[%s] set e_hdmi_name[%d] = %d \n", __FUNCTION__, ui1_internal_id, b_use_device_name));
    }
}

extern BOOL a_cfg_cust_cec_get_device_name(UINT8 ui1_hdmi_idx, UTF16_T* w2s_cec_name, UINT8 ui1_str_len)
{
    ACFG_DEBUG_INPUT_SRC_NAME(
        DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} ui1_hdmi_idx:%d, ui1_str_len:%d\n",
            __FUNCTION__, __LINE__, ui1_hdmi_idx, ui1_str_len  ));  );

    if( ui1_hdmi_idx >= 4 )
    {
        DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} Error: ui1_hdmi_idx:%d!!\n", __FUNCTION__, __LINE__, ui1_hdmi_idx ));
        return FALSE;
    }


    HANDLE_T h_cec = acfg_custom_get_cec_handle();
    if( h_cec == NULL_HANDLE )
    {
        DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} Error: CEC handle is NULL!!\n", __FUNCTION__, __LINE__ ));
        return FALSE;
    }

    /* Find CEC name if available. */

    UINT8  ui1_dev_idx;
    INT32 i4_ret;
    CEC_DEV_INFO_T t_dev_info = {0};
    //CEC_DEV_INFO_T t_dev_info_first = {0};
    BOOL bDevice_found = FALSE;

    for( ui1_dev_idx=0; ui1_dev_idx <= 15; ui1_dev_idx++ )
    {
        i4_ret = a_cec_get_dev_info( h_cec, ui1_hdmi_idx, ui1_dev_idx, &t_dev_info);
        if (i4_ret == CECR_OK)
        {
            ACFG_DEBUG_INPUT_SRC_NAME(
                DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} CECR_OK: ui1_hdmi_idx:%d, ui1_dev_idx:%d, LA:0x%X, PA:0x%X, aw2_osd_name:[%s]\n",
                    __FUNCTION__, __LINE__, ui1_hdmi_idx, ui1_dev_idx, t_dev_info.e_la, t_dev_info.ui2_pa,
                    menu_custom_get_char_string(t_dev_info.aw2_osd_name) ));  );

            if( bDevice_found == FALSE )
            {
                bDevice_found = TRUE;
                //t_dev_info_first = t_dev_info;
            }

            /* if cec device link in series, AMP name first. */
            if (t_dev_info.e_la == CECM_LOG_ADDR_AUD_SYS)
            {
                DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} AMP found: ui1_hdmi_idx:%d, ui1_dev_idx:%d, LA:0x%X, PA:0x%X, aw2_osd_name:[%s]\n",
                    __FUNCTION__, __LINE__, ui1_hdmi_idx, ui1_dev_idx, t_dev_info.e_la, t_dev_info.ui2_pa,
                    menu_custom_get_char_string(t_dev_info.aw2_osd_name) ));
                break;
            }

            // continue check for AMP...
        }
        else
        {
            ACFG_DEBUG_INPUT_SRC_NAME(
                DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} No CEC device: i4_ret:%d, ui1_hdmi_idx:%d, ui1_dev_idx:%d \n",
                    __FUNCTION__, __LINE__, i4_ret, ui1_hdmi_idx, ui1_dev_idx )); );
            // Stop checking...
            break;
        }
    }

    if( !bDevice_found )
    {
        ACFG_DEBUG_INPUT_SRC_NAME(
            DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} No CEC Device! ui1_hdmi_idx:%d \n",
                __FUNCTION__, __LINE__, ui1_hdmi_idx )); );
        return FALSE;
    }

    DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} CEC name found: ui1_hdmi_idx:%d, LA:0x%X, PA:0x%X, aw2_osd_name:[%s]\n",
        __FUNCTION__, __LINE__, ui1_hdmi_idx, t_dev_info.e_la, t_dev_info.ui2_pa,
            menu_custom_get_char_string(t_dev_info.aw2_osd_name) ));

    UINT8 ui1_cec_name_len = c_uc_w2s_strlen(t_dev_info.aw2_osd_name);
    if( ui1_cec_name_len == 0 )
    {
        DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} CEC name is empty!! ui1_hdmi_idx:%d \n",
            __FUNCTION__, __LINE__, ui1_hdmi_idx ));
        return FALSE;
    }

    c_uc_w2s_strncpy(w2s_cec_name, t_dev_info.aw2_osd_name, ui1_str_len);

    return TRUE;
}

/**
 * @brief   This function returns the user input label. If current input is HDMI
 *          and user input label is empty, it will return the device OSD name
 *          if available.
 * @param   ISL_REC_T [in]      A pointer to current ISL record.
 * @param   w2s_inp_name [out]  The input label or the HDMI device name.
 * @retval  APP_CFGR_OK     The function succeded.
 * @retval  Otherwise       The function failed.
 */
INT32 a_cfg_custom_get_inp_name_with_cec_name (ISL_REC_T* pt_isl_rec, UTF16_T* w2s_inp_name, UINT8 ui1_str_len)
{
    INT32   i4_ret;


    if (!pt_isl_rec || !w2s_inp_name)
    {
        return APP_CFGR_INV_ARG;
    }

    // Clear string buffer
    c_uc_w2s_strcpy(w2s_inp_name, L"");

    BOOL bIsSrcHDMI = FALSE;
    if( (pt_isl_rec->e_src_type == INP_SRC_TYPE_AV)
      &&(pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI)
      )
    {
        bIsSrcHDMI = TRUE;
    }

    ACFG_DEBUG_INPUT_SRC_NAME(
        DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC] {%s,%d} ui1_id:%d, e_src_type:%d, ui1_internal_id:%d, e_video_type:0x%X, bIsSrcHDMI:%d\n",
        __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->e_src_type,
        pt_isl_rec->ui1_internal_id, pt_isl_rec->t_avc_info.e_video_type, bIsSrcHDMI
        )); );

    // todo: check if need to support other source?
    if( !bIsSrcHDMI )
    {
        DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} ui1_id:%d, not HDMI => inp_name:{}\n",
            __FUNCTION__, __LINE__, pt_isl_rec->ui1_id ));
        return APP_CFGR_OK;
    }

    // Check HDMI internal id ...
    if( bIsSrcHDMI )
    {
        if( pt_isl_rec->ui1_internal_id >= MAX_HDMI_INPUT )
        {
            DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} Error: Invalid HDMI internal_id:%d \n",
                __FUNCTION__, __LINE__, pt_isl_rec->ui1_internal_id ));
            return APP_CFGR_INV_ARG;
        }
    }


    UINT8 ui1_cec_func = APP_CFG_CEC_OFF;
    if( bIsSrcHDMI )
    {
        a_cfg_get_cec_func(&ui1_cec_func);
        ACFG_DEBUG_INPUT_SRC_NAME( DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} ui1_cec_func:%d \n", __FUNCTION__, __LINE__, ui1_cec_func )); );
    }


    // Get CEC name ...
    BOOL b_cec_name_valid = FALSE;
    UTF16_T w2s_cec_name[CECM_OSD_NAME_SIZE+1] = {0};
    if( bIsSrcHDMI && (APP_CFG_CEC_OFF != ui1_cec_func) )
    {
        /* Find CEC name if available. */
        b_cec_name_valid = a_cfg_cust_cec_get_device_name(pt_isl_rec->ui1_internal_id, w2s_cec_name, CECM_OSD_NAME_SIZE);
        if( b_cec_name_valid )
        {
            ACFG_DEBUG_INPUT_SRC_NAME( DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} Got CEC name: ui1_internal_id:%d, w2s_cec_name:[%s]\n",
                __FUNCTION__, __LINE__, pt_isl_rec->ui1_internal_id, menu_custom_get_char_string(w2s_cec_name) )); );
        }
        else
        {
            ACFG_DEBUG_INPUT_SRC_NAME( DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} No CEC name: ui1_internal_id:%d\n",
                __FUNCTION__, __LINE__, pt_isl_rec->ui1_internal_id )); );
        }
    }


    // Get user input name ...
    BOOL b_user_input_name_valid = FALSE;
    CHAR    s_usr_inp_name [APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    i4_ret = a_cfg_custom_get_inp_name(pt_isl_rec->ui1_id, s_usr_inp_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    if( 0 != c_strlen(s_usr_inp_name) )
    {
        b_user_input_name_valid = TRUE;
    }
    ACFG_DEBUG_INPUT_SRC_NAME( DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} ui1_id:%d, inp_name:{%s} \n",
        __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, s_usr_inp_name)); );


    // Get name from spd_info(for XBOX) ...
    BOOL b_spd_info_name_valid = FALSE;
    UINT8  spd_info[30] = {0};
    if( bIsSrcHDMI )
    {
        i4_ret = nav_cec_custom_get_spd_info(pt_isl_rec->ui1_internal_id, spd_info, sizeof(spd_info) );
        if( i4_ret != NAVR_OK )
        {
            //DBG_LOG_PRINT(("[ACFG][CEC] Get spd_info failed!\n" ));
        }
        else
        {
            if( 0 != c_strlen((char*)spd_info) )
            {
            if (c_strcmp(spd_info, "H") == 0 )
            {
                if(APP_CFG_CEC_OFF != ui1_cec_func)
                    b_spd_info_name_valid = FALSE;
                else
                    b_spd_info_name_valid = TRUE;
            }
            else
            {
                b_spd_info_name_valid = TRUE;
            }
            DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} id:%d, ui1_internal_id:%d, spd_info:{%s},b_spd_info_name_valid=%d\n",
                    __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->ui1_internal_id, spd_info,b_spd_info_name_valid));
            }
        }
    }

    //DBG_LOG_PRINT((" e_hdmi_name[%d]: %d \n", pt_isl_rec->ui1_internal_id, e_hdmi_name[pt_isl_rec->ui1_internal_id]));

    // Return name priority:
    // e_hdmi_name[MAX_HDMI_INPUT] // TRUE means use device name,FALSE means use user input name
    // 1. CEC/Spd_info
    // 2. User_input_name
    BOOL b_use_device_name = FALSE;
    if( bIsSrcHDMI )
    {
        if( pt_isl_rec->ui1_internal_id < MAX_HDMI_INPUT )
        {
            if( TRUE == e_hdmi_name[pt_isl_rec->ui1_internal_id] )
            {
                b_use_device_name = TRUE;
            }
        }
    }

    ACFG_DEBUG_INPUT_SRC_NAME( DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} id:%d, ui1_internal_id:%d, b_use_device_name:%d\n",
        __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->ui1_internal_id, b_use_device_name));  );

    if( b_use_device_name )
    {
        if( b_cec_name_valid ) // CEC name valid
        {
            c_uc_w2s_strncpy(w2s_inp_name, w2s_cec_name, ui1_str_len);
        }
        else if(b_spd_info_name_valid) // spd_info name valid
        {
            c_uc_ps_to_w2s((char*)spd_info, w2s_inp_name, ui1_str_len);
        }
        else if(b_user_input_name_valid)// user_input_name
        {
            c_uc_ps_to_w2s(s_usr_inp_name, w2s_inp_name, ui1_str_len);
        }
        else
        {
            c_uc_w2s_strcpy(w2s_inp_name, L"");
        }
    }
    else // Use user_input_name
    {
        if( b_user_input_name_valid ) // user_input_name
        {
            c_uc_ps_to_w2s(s_usr_inp_name, w2s_inp_name, ui1_str_len);
        }
        else if( b_cec_name_valid ) // CEC name valid
        {
            c_uc_w2s_strncpy(w2s_inp_name, w2s_cec_name, ui1_str_len);
        }
        else if(b_spd_info_name_valid) // spd_info name valid
        {
            c_uc_ps_to_w2s((char*)spd_info, w2s_inp_name, ui1_str_len);
        }
        else
        {
            c_uc_w2s_strcpy(w2s_inp_name, L"");
        }
    }
    UINT16 hdmi_internal_id = pt_isl_rec->ui1_internal_id;
    if ( 0 == hdmi_hot_plug_status (hdmi_internal_id))
    {
        c_uc_ps_to_w2s(s_usr_inp_name, w2s_inp_name, ui1_str_len);
    }

#if 0
    if (a_cfg_custom_is_inp_name_empty (s_usr_inp_name))
    {
        if( bIsSrcHDMI )// (pt_isl_rec->e_src_type == INP_SRC_TYPE_AV && pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI)
        {
            /* No custom input label. Use CEC name in HDMI inputs if exists. */

            if ( (i4_ret == CECR_OK) && (pt_isl_rec->ui1_internal_id < MAX_HDMI_INPUT)
               //&& e_hdmi_name[pt_isl_rec->ui1_internal_id]
               )
            {
                ui1_output_str_len = c_uc_w2s_strlen (t_dev_info.aw2_osd_name);

                if (APP_CFG_CEC_OFF == ui1_cec_func)
                {
                    c_uc_w2s_strcpy (w2s_inp_name, L"");
                }
                else if (ui1_output_str_len != 0)
                {
                    if (ui1_str_len < ui1_output_str_len)
                    {
                        c_uc_w2s_strncpy (w2s_inp_name, t_dev_info.aw2_osd_name, ui1_str_len);
                    }
                    else
                    {
                        c_uc_w2s_strcpy (w2s_inp_name, t_dev_info.aw2_osd_name);
                    }
                }
                else if (c_strlen((char*)spd_info) != 0)
                {
                    c_uc_ps_to_w2s((char*)spd_info, w2s_inp_name, ui1_str_len);
                }
                else
                {
                    c_uc_w2s_strcpy (w2s_inp_name, L"");
                }
            }
            else
            {
                if (c_strlen(spd_info) != 0)
                {
                    DBG_LOG_PRINT ((" [%s][%d] copy spd_info \r\n", __FUNCTION__, __LINE__));
                    c_uc_ps_to_w2s(spd_info, w2s_inp_name, ui1_str_len);
                }
                else
                {
                    c_uc_w2s_strcpy (w2s_inp_name, L"");
                }
            }
        }
        else
        {
            c_uc_w2s_strcpy (w2s_inp_name, L"");
        }
    }
    else
    {
        if( bIsSrcHDMI )// (pt_isl_rec->e_src_type == INP_SRC_TYPE_AV && pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI)
        {
            //if menu has rename, use menu name

            /* No custom input label. Use CEC name in HDMI inputs if exists. */
            if ( (i4_ret == CECR_OK) && (pt_isl_rec->ui1_internal_id < MAX_HDMI_INPUT)
               && e_hdmi_name[pt_isl_rec->ui1_internal_id]
               )
            {
                ui1_output_str_len = c_uc_w2s_strlen (t_dev_info.aw2_osd_name);

                if (APP_CFG_CEC_OFF == ui1_cec_func)
                {
                    c_uc_ps_to_w2s (s_usr_inp_name, w2s_inp_name, ui1_str_len);
                }
                else if (ui1_output_str_len != 0)
                {
                    if (ui1_str_len < ui1_output_str_len)
                    {
                        c_uc_w2s_strncpy (w2s_inp_name, t_dev_info.aw2_osd_name, ui1_str_len);
                    }
                    else
                    {
                        c_uc_w2s_strcpy (w2s_inp_name, t_dev_info.aw2_osd_name);
                    }
                }
                else if (c_strlen((char*)spd_info) != 0)
                {
                    c_uc_ps_to_w2s((char*)spd_info, w2s_inp_name, ui1_str_len);
                }
                else
                {
                    c_uc_ps_to_w2s (s_usr_inp_name, w2s_inp_name, ui1_str_len);
                }
            }
            else
            {
                c_uc_ps_to_w2s (s_usr_inp_name, w2s_inp_name, ui1_str_len);
            }
        }
        else
        {
            c_uc_ps_to_w2s (s_usr_inp_name, w2s_inp_name, ui1_str_len);
        }
    }
#endif

    // debug
  #if 1
    {
        CHAR   ac_osd_name_dbg[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
        c_uc_w2s_to_ps(w2s_inp_name, ac_osd_name_dbg, APP_CFG_CUSTOM_INP_NAME_LEN);

        DBG_LOG_PRINT (("[ACFG][INPUT_SRC][CEC]{%s,%d} ui1_id:%d, ui1_internal_id:%d, bIsSrcHDMI:%d => w2s_inp_name:{%s}\n",
            __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->ui1_internal_id,
             bIsSrcHDMI, ac_osd_name_dbg ));
    }
  #endif

    return APP_CFGR_OK;
}

/**
 * @brief   Determine whether the input name is empty or not.
 * @param   s_str [in]  String.
 * @retval  TRUE        The input name string is empty.
 * @retval  FALSE       The input name string is NOT empty.
 */
BOOL a_cfg_custom_is_inp_name_empty (CHAR* s_str)
{
    return (BOOL)(c_strlen(s_str) == 0);
}
INT32 a_cfg_custom_set_opmode (A_CFG_OP_MODE_T e_mode)
{
    INT16 i2_val = (INT16) e_mode;
    return acfg_set(IDX_CUSTOM_OP_MODE, &i2_val, 1);
}

INT32 a_cfg_custom_get_opmode (A_CFG_OP_MODE_T* pe_mode)
{
    SIZE_T  z_size;
    INT16 i2_val = 0;
    INT32 i4_ret;

    if (!pe_mode)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_OP_MODE, (VOID*)&i2_val, &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    *pe_mode = (A_CFG_OP_MODE_T)i2_val;

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_postal_code(UTF16_T *u2s_dst)
{
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#define TIME_LOCAL_SETTING_MAX_LEN 7
    INT32   i4_ret;
    CHAR    s_code[TIME_LOCAL_SETTING_MAX_LEN + 1];
    CHAR    s_code_part1[MAX_POSTAL_CODE_NUM+1];
    CHAR    s_code_part2[TIME_LOCAL_SETTING_MAX_LEN - MAX_POSTAL_CODE_NUM + 1];
    UINT16  ui2_code_ex = 0;
    SIZE_T  z_size = 0;

    c_memset(s_code, 0, sizeof(s_code));
    c_memset(s_code_part1, 0, sizeof(s_code_part1));
    c_memset(s_code_part2, 0, sizeof(s_code_part2));

    if (u2s_dst == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_POSTAL_CODE, s_code_part1, &z_size);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    c_strcpy(s_code, s_code_part1);

    i4_ret = acfg_get(IDX_CUSTOM_RSERVE_UI2_0, &ui2_code_ex, &z_size);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    if (0 != ui2_code_ex && c_strlen(s_code) >= MAX_POSTAL_CODE_NUM)
    {
        s_code_part2[0] = (CHAR)((ui2_code_ex&0xFF00)>>8);
        s_code_part2[1] = (CHAR)(ui2_code_ex&0x00FF);
        c_strcat(s_code, s_code_part2);
    }

    c_uc_ps_to_w2s(s_code,  u2s_dst, c_strlen(s_code));


#else
    INT32   i4_ret;
    char s_code[APP_CFG_MAX_PWD_LEN+1];
    SIZE_T  z_size;


    if (u2s_dst == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    c_memset(s_code, 0, sizeof(s_code));

    i4_ret = acfg_get(IDX_CUSTOM_POSTAL_CODE, s_code, &z_size);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    c_uc_ps_to_w2s(s_code, u2s_dst, c_strlen(s_code));


#endif
    return APP_CFGR_OK;

}

INT32 a_cfg_custom_set_postal_code(UTF16_T *u2s_src)
{
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#define TIME_LOCAL_SETTING_MAX_LEN 7

    INT32   i4_ret = APP_CFGR_OK;
    CHAR    s_code[TIME_LOCAL_SETTING_MAX_LEN + 1];
    CHAR    s_code_part1[MAX_POSTAL_CODE_NUM+1];
    CHAR    s_code_part2[TIME_LOCAL_SETTING_MAX_LEN - MAX_POSTAL_CODE_NUM + 1];
    UINT16  ui2_code_ex = 0;

    c_memset(s_code, 0, sizeof(s_code));
    c_memset(s_code_part1, 0, sizeof(s_code_part1));
    c_memset(s_code_part2, 0, sizeof(s_code_part2));

    if (u2s_src == NULL ||
        c_uc_w2s_strlen(u2s_src) > TIME_LOCAL_SETTING_MAX_LEN )
    {
        return APP_CFGR_INV_ARG;
    }

    c_uc_w2s_to_ps(u2s_src, s_code, TIME_LOCAL_SETTING_MAX_LEN);
    c_strncpy(s_code_part1, s_code, MAX_POSTAL_CODE_NUM);

    i4_ret = acfg_set(IDX_CUSTOM_POSTAL_CODE, s_code_part1, c_strlen(s_code_part1));
    ACFG_CHK_FAIL(i4_ret,i4_ret);

    if (c_strlen(s_code) > MAX_POSTAL_CODE_NUM)
    {
        c_strncpy(s_code_part2, &s_code[MAX_POSTAL_CODE_NUM], 2);

        ui2_code_ex = (UINT8)s_code_part2[0];
        ui2_code_ex = (ui2_code_ex << 8)|((UINT8)s_code_part2[1]);
    }
    else
    {
        ui2_code_ex = 0;
    }

    i4_ret = acfg_set(IDX_CUSTOM_RSERVE_UI2_0, &ui2_code_ex, 1);

    return i4_ret;
#else
    char s_code[MAX_POSTAL_CODE_NUM+1];
    c_memset(s_code, 0, sizeof(s_code));

    if (u2s_src == NULL ||
        c_uc_w2s_strlen(u2s_src) > MAX_POSTAL_CODE_NUM )
    {
        return APP_CFGR_INV_ARG;
    }

    c_uc_w2s_to_ps(u2s_src, s_code, MAX_POSTAL_CODE_NUM);

    return acfg_set(IDX_CUSTOM_POSTAL_CODE, s_code, c_strlen(s_code));
#endif

}

#ifdef APP_RETAIL_MODE_SUPPORT
INT32 a_cfg_custom_get_retail_mode_setting(ACFG_RETAIL_MODE_T* pt_retail_mode)
{
    SIZE_T  z_size;

    if (NULL == pt_retail_mode)
    {
        return APP_CFGR_INV_ARG;
    }
#if 1
    return acfg_get(IDX_CUSTOM_RETAIL_MODE, (VOID*)pt_retail_mode, &z_size);
#else
    *pt_retail_mode = ACFG_RETAIL_MODE_HOME;
    return APP_CFGR_OK;
#endif
}

INT32 a_cfg_custom_set_retail_mode_led_ctrl(BOOL b_enable)
{
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_val = (UINT8)b_enable;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_StoreDemo_LED;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_val;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* save acfg led log status */


    return APP_CFGR_OK;

}


INT32 a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_T e_retail_mode)
{
    UINT8   ui1_val  = (UINT8)e_retail_mode;
    INT32   i4_ret   = 0;

    if(ACFG_RETAIL_MODE_LAST_ENTRY <= e_retail_mode)
    {
        return APP_CFGR_INV_ARG;
    }

    DBG_LOG_PRINT(("[ACFG][%s %d] set retailmode : %d\n", __FUNCTION__, __LINE__, e_retail_mode));

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    a_tv_custom_set_hotkey_wakeup_active( ui1_val > 0 ? WAKEUP_AP_RETAILMODE_SET : WAKEUP_AP_RETAILMODE_CLEAN); /* set wakeup status*/
#endif

    a_cfg_custom_set_retail_mode_led_ctrl(ui1_val);

    a_nav_power_set_component_enable(ACFG_RETAIL_MODE_HOME == e_retail_mode ? TRUE : FALSE);
    i4_ret = acfg_set(IDX_CUSTOM_RETAIL_MODE, (VOID*)&ui1_val, 1);
    a_cfg_store();

    return i4_ret;
}

#endif


INT32 a_cfg_custom_set_oobe_mode(BOOL b_enable)
{
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_val = (UINT8)b_enable;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SAVE_WZD_STATUS;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_val;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* save acfg led log status */
    if(b_enable)
    {
        a_cfg_custom_set_led_logo_ctrl(0);
    }

    return APP_CFGR_OK;

}

INT32 a_cfg_custom_get_wzd_subpage_id( UINT8* pui1_index )
{
    SIZE_T  z_size;

    if( NULL == pui1_index )
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_WZD_SUB_PAGE_IDX, (VOID*)pui1_index, &z_size);
}

INT32 a_cfg_custom_set_wzd_subpage_id( UINT8 ui1_index )
{

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    if (0 == ui1_index) /* resume wzd in TV boot-up*/
    {
        DBG_INFO(("[HOTKEY] set WZD.\n"));
        a_tv_custom_set_hotkey_wakeup_active(WAKEUP_AP_WZD_SET);
    }
#endif

    return acfg_set(IDX_CUSTOM_WZD_SUB_PAGE_IDX, (VOID*)&ui1_index, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_updater_completed_flag
 *
 * Description:
 *
 * Inputs: b_enable:
 *         TRUE  - has upgrade completed.
 *         FALSE - not upgrade be completed.
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_updater_completed_flag(BOOL b_enable)
{
    INT8        i1_val;
    INT32       i4_ret = APP_CFGR_OK;

    i1_val = (b_enable == TRUE) ? 1 : 0;

    i4_ret = acfg_set(IDX_CUSTOM_UPDATER_COMPLETED, &i1_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_updater_completed_flag
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *         TRUE  - has upgrade completed.
 *         FALSE - not upgrade be completed.
 *-----------------------------------------------------------------------------*/
BOOL a_cfg_custom_get_updater_completed_flag(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret;
    SIZE_T  z_size;

    i4_ret = acfg_get(IDX_CUSTOM_UPDATER_COMPLETED, (VOID*)&i2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return ((i2_val == 0) ? FALSE : TRUE);
}

INT32 a_cfg_custom_set_dimming_idx (UINT16 ui2_idx)
{
    return a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)ui2_idx);;
}

INT32 a_cfg_custom_get_dimming_idx (UINT16* pui2_idx)
{
    INT32 i4_ret = 0;
    INT16   i2_val = 0;

    if (!pui2_idx)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING),&i2_val);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pui2_idx = (UINT16) i2_val;

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_country_code(ACFG_COUNTRY_CODE_T* pt_country)
{
    SIZE_T  z_size;
    INT32   i4_ret;
    UINT32  ui2_val = 0;

    if (pt_country == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_COUNTRY_CODE, &ui2_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pt_country = (ACFG_COUNTRY_CODE_T)ui2_val;

    return APP_CFGR_OK;
}


INT32 a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_T e_country)
{
    UINT16  ui2_val = (UINT16)e_country;
    INT32   i4_ret = APP_CFGR_OK;

    a_tv_custom_set_country((UINT16)e_country);

    i4_ret = acfg_set(IDX_CUSTOM_COUNTRY_CODE, &ui2_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    switch (e_country)
    {
        case ACFG_COUNTRY_CODE_CA:
        case ACFG_COUNTRY_CODE_MEX:
        case ACFG_COUNTRY_CODE_UNKNOWN:
            //a_tv_custom_set_viewing_data_accepted_by_oobe_menu(FALSE);
            a_cfg_custom_set_acr(ACFG_ACR_OFF);
            //c_pcl_set_ethernet_wol_ctrl(PCL_ETHERNET_WOL_DISABLE);
            //c_pcl_set_wifi_wol_ctrl(PCL_WIFI_WOL_DISABLE);
            break;

        case ACFG_COUNTRY_CODE_US:
            //c_pcl_set_ethernet_wol_ctrl(PCL_ETHERNET_WOL_ENABLE);
            //c_pcl_set_wifi_wol_ctrl(PCL_WIFI_WOL_ENABLE);
        default:
            //a_cfg_custom_set_acr(ACFG_ACR_ON);
            break;
    }


    return APP_CFGR_OK;
}

INT32 a_cfg_custom_update_dimming_idx(VOID)
{
    return a_cfg_cust_update_local_dimming();
}

#ifdef NEVER
INT32 a_cfg_custom_update_dimming_idx(VOID)
{
    UINT16 i2_val = 0;
    INT32 i4_ret;
    SCC_VID_LOCAL_DIMMING_TYPE_T    e_lcdim_mode = SCC_VID_LOCAL_DIMMING_TYPE_OFF;

#ifdef APP_CFG_DIMMING_OFF_IN_EMANUAL
    UINT8   ui1_val   = ICL_EMANUAL_STATUS_OFF;
    SIZE_T  z_size    = ICL_RECID_EMANUAL_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
                       &ui1_val, &z_size);
    DBG_INFO(("\n===a_cfg_custom_update_dimming_idx, i4_ret:%d ui1_val:%d\n",i4_ret,ui1_val));
    if ((i4_ret==APP_CFGR_OK)&&(ui1_val == ICL_EMANUAL_STATUS_ON))
    {
        return APP_CFGR_OK;
    }
#endif
    i4_ret = a_cfg_custom_get_dimming_idx(&i2_val);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    if (i2_val == 0)
    {
        e_lcdim_mode = SCC_VID_LOCAL_DIMMING_TYPE_OFF;
    }
    else if(i2_val == 1)
    {
        e_lcdim_mode = SCC_VID_LOCAL_DIMMING_TYPE_LOW;
    }
    else if(i2_val == 2)
    {
        e_lcdim_mode = SCC_VID_LOCAL_DIMMING_TYPE_MID;
    }
    else if(i2_val == 3)
    {
        e_lcdim_mode = SCC_VID_LOCAL_DIMMING_TYPE_HIG;
    }

    if(a_wzd_is_oobe_mode() == TRUE)
    {
         DBG_INFO(("[ACFG][%s %d]current is oobe active state should set local dimming to off \n",__FUNCTION__,__LINE__));
        e_lcdim_mode = SCC_VID_LOCAL_DIMMING_TYPE_OFF;
    }
    if(e_lcdim_mode > SCC_VID_LOCAL_DIMMING_TYPE_LOW)
    {
         ACFG_LOG_ON_FAIL(a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT),ACFG_CUST_ADP_BACK_LIGHT_0));
         ACFG_LOG_ON_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT)));
    }

    i4_ret=c_scc_vid_set_local_dimming_mode(h_g_acfg_scc_main_vid,
                                            e_lcdim_mode);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    return APP_CFGR_OK;
}
#endif /* NEVER */

INT32 a_cfg_custom_set_dimming_off(VOID)
{
    INT32 i4_ret;
    i4_ret=c_scc_vid_set_local_dimming_mode(h_g_acfg_scc_main_vid,
                                            SCC_VID_LOCAL_DIMMING_TYPE_OFF);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    return APP_CFGR_OK;
}

#ifdef APP_LED_LOGO_CTRL
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_led_logo_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_led_logo_ctrl(UINT8 ui1_idx)
{
    INT32       i4_ret = APP_CFGR_OK;

    if(ui1_idx > 1)
    {
        ui1_idx = 0;
    }

    i4_ret = acfg_set(IDX_CUSTOM_LED_LOGO_CTRL, &ui1_idx, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_custom_set_led_logo_ctrl_to_drv(ui1_idx);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_led_logo_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
UINT16 a_cfg_custom_get_led_logo_ctrl(VOID)
{
    UINT16  ui2_val = 0;
    INT32   i4_ret;
    SIZE_T  z_size;

    i4_ret = acfg_get(IDX_CUSTOM_LED_LOGO_CTRL, (VOID*)&ui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return ui2_val;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_led_logo_ctrl_to_drv
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_led_logo_ctrl_to_drv(UINT8 ui1_idx)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    if(ui1_idx > 1)
    {
        ui1_idx = 0;
    }

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_INDICATOR_LED ;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    DBG_LOG_PRINT(("[ACFG][%s %d] %s,i4_ret:%d\n",__FUNCTION__,__LINE__,ui1_idx == 0 ? "OFF" : "ON",i4_ret));
    return i4_ret;
}

INT32 a_cfg_custom_set_led_breath_to_drv(UINT8 ui1_second)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LED_BREATH_FROM_LIGHT_TO_DARK ;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_second;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    DBG_LOG_PRINT(("[ACFG][%s %d] %d s,i4_ret:%d\n",__FUNCTION__,__LINE__,ui1_second,i4_ret));
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_update_led_logo_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_update_led_logo_ctrl(VOID)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT16  ui2_val = 0;
    SIZE_T  z_size;

    i4_ret = acfg_get(IDX_CUSTOM_LED_LOGO_CTRL, (VOID*)&ui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return a_cfg_custom_set_led_logo_ctrl_to_drv(ui2_val);
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_usb_power_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_usb_power_ctrl(UINT8 ui1_idx)
{
    INT32       i4_ret = APP_CFGR_OK;

    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    if(ui1_idx > 1)
    {
        ui1_idx = 0;
    }

    i4_ret = acfg_set(IDX_CUSTOM_USB_POWER_CTRL, &ui1_idx, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_USB_POWER_CTRL ;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    if (ui1_idx == 0)
    {
        a_cfg_custom_update_usb_power_ctrl();
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_usb_power_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
UINT16 a_cfg_custom_get_usb_power_ctrl(VOID)
{
    UINT16  ui2_val = 0;
    INT32   i4_ret;
    SIZE_T  z_size;

    i4_ret = acfg_get(IDX_CUSTOM_USB_POWER_CTRL, (VOID*)&ui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return ui2_val;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_update_usb_power_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_update_usb_power_ctrl(VOID)
{
    INT32   i4_ret = APP_CFGR_OK;

    DRV_CUST_OPERATION_INFO_T t_op_info;
    UINT16  ui2_val = 0;
    UINT8   ui1_usb_power = 0;

    SIZE_T  z_size;

    i4_ret = acfg_get(IDX_CUSTOM_USB_POWER_CTRL, (VOID*)&ui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    ui1_usb_power = (UINT8)ui2_val;
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_USB_VIRTUAL_POWER_OFF_CTRL;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_usb_power;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_usb_virtual_power_ctrl
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_usb_virtual_power_ctrl(UINT16  ui2_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    DRV_CUST_OPERATION_INFO_T t_op_info;
    UINT8   ui1_usb_power = 0;
    SIZE_T  z_size;

    z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    ui1_usb_power = (UINT8)ui2_val;
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_USB_VIRTUAL_POWER_OFF_CTRL;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_usb_power;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_led_logo_force_on
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_led_logo_force_on(UINT8 ui1_idx)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    if(ui1_idx > 1)
    {
        ui1_idx = 0;
    }

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_BGM_Cancel ;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_dc_qs_off_start_led
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_dc_qs_off_start_led(void)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8 ui1_idx= 0;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_DC_QS_OFF_START_LED;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_led_logo_lightness
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_led_logo_lightness(UINT8 ui1_lightness)
{
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_quickstart_on_start_led(VOID)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8 ui1_idx= 0;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_QUICKSTART_ON_START_LED;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    return i4_ret;
}
#endif

INT32 a_cfg_reset_svl_by_mask(HANDLE_T h_svl,
                             UINT32 ui4_reset_mask,
                             UINT32 ui4_reset_value)
{
    INT32       i4_result;
    INT32       i4_ret = APP_CFGR_OK;
    UINT32      ui4_lst_mask = SB_VNET_ALL;
    UINT16      ui2_idx;
    UINT16      ui2_rec_num = 0;
    UINT16*     aui2_rec_id;
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    SVL_REC_T   t_svl_rec;

    if (h_svl == NULL_HANDLE)
    {
        return APP_CFGR_INV_ARG;
    }

    /* lock SVL */
    i4_result = c_svl_lock(h_svl);
    if(i4_result != SVLR_OK)
    {
        i4_ret = APP_CFGR_INTERNAL_ERR;
        DBG_ERROR(("<MENU> Can't lock SVL.\r\n"));
    }

    else
    {
        /* get record number */
        i4_result = c_svl_get_num_rec_by_brdcst_type(h_svl,
                                                     BRDCST_TYPE_UNKNOWN,
                                                     ui4_lst_mask,
                                                     &ui2_rec_num,
                                                     &ui4_ver_id);
        if(i4_result != SVLR_OK)
        {
            DBG_ERROR(("<MENU> Can't get record number.\r\n"));
            i4_ret = APP_CFGR_INTERNAL_ERR;
        }
        else
        {
            /* Due to the bug in SVL, we use the two iteration work-around
               solution. In the first iteration, we store the svl record to
               an array; and the second iteration, we make use of these ids
               to update records. */
            aui2_rec_id = (UINT16*) c_mem_alloc(ui2_rec_num * sizeof(UINT16));
            if(aui2_rec_id == NULL)
            {
                i4_ret = APP_CFGR_INTERNAL_ERR;
            }
            else
            {
                /* Iter 1: Get all record id. (readonly iteration) */
                for(ui2_idx=0; ui2_idx<ui2_rec_num; ui2_idx++)
                {
                    i4_result = c_svl_get_rec_by_brdcst_type(h_svl,
                                                             BRDCST_TYPE_UNKNOWN,
                                                             ui4_lst_mask,
                                                             ui2_idx,
                                                             &t_svl_rec,
                                                             &ui4_ver_id);
                    if(i4_result != SVLR_OK)
                    {
                        i4_ret = APP_CFGR_INTERNAL_ERR;
                        DBG_ERROR(("<MENU> Can't iterate service list at idx=%d.\r\n",
                                   ui2_idx));
                        break;
                    }
                    aui2_rec_id[ui2_idx] = t_svl_rec.ui2_svl_rec_id;
                }

                /* Iter 2: Get the record by record id and update it */
                for (ui2_idx=0;
                     ui2_idx<ui2_rec_num && i4_ret == APP_CFGR_OK;
                     ui2_idx++)
                {
                    i4_result = c_svl_get_rec(h_svl,
                                              aui2_rec_id[ui2_idx],
                                              &t_svl_rec,
                                              &ui4_ver_id);
                    if(i4_result != SVLR_OK)
                    {
                        i4_ret = APP_CFGR_INTERNAL_ERR;
                        DBG_ERROR(("<MENU> Can't get record %d.\r\n",
                                   aui2_rec_id[ui2_idx]));
                        break;
                    }


                    t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask =
                        (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & ~ui4_reset_mask) |
                        (ui4_reset_value & ui4_reset_mask);

                    i4_result = c_svl_update_rec(h_svl, &t_svl_rec, TRUE);
                    if (i4_result != SVLR_OK)
                    {
                        DBG_ERROR(("<MENU> Can't update record: %d < %d.\r\n",
                                    t_svl_rec.ui2_svl_rec_id));
                    }
                } /* end of Iteration  */

                c_mem_free(aui2_rec_id);
            } /* c_mem_alloc */
        }/* c_svl_get_num_rec_by_brdcst_type */

        /* Unlock SVL */
        c_svl_unlock(h_svl);
    } /* c_svl_lock */

    return i4_ret;
}

INT32 a_cfg_custom_set_reg_info(CHAR** pps_reg_info, UINT8 ui1_num)
{
    UINT8           ui1_idx = 0;

    FILE * fl ;

    if (0 == access("/data/wzd_reg_info", F_OK))
    {
        AP_SYSTEM_CALL("rm /data/wzd_reg_info;sync");
    }

    fl = fopen ("/data/wzd_reg_info","w+");
    if (fl == NULL)
    {
        DBG_INFO(("\n---Open wzd_reg_info failed!---\n"));
        return APP_CFGR_INV_ARG;
    }

    for(ui1_idx=0; ui1_idx<ui1_num; ui1_idx++)
    {
        fprintf(fl, "%s\n", pps_reg_info[ui1_idx]);
    }
    fclose (fl);

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_get_reg_info(CHAR** pps_reg_info, UINT8 ui1_num)
{
    UINT8           ui1_idx = 0;

    FILE * fl ;

    fl = fopen ("/data/wzd_reg_info","r");
    if (fl == NULL)
    {
        DBG_INFO(("\n---Open wzd_reg_info failed!---\n"));
        return APP_CFGR_INV_ARG;
    }

    for(ui1_idx=0; ui1_idx<ui1_num; ui1_idx++)
    {
        if(NULL == fgets(pps_reg_info[ui1_idx],64,fl))
        {
            break;
        }
    }
    fclose (fl);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_device_info(UINT8 ui1_input_id, CHAR* ps_type_name, CHAR* ps_brd_name, CHAR* ps_model_name, CHAR* ps_codeset)
{
    UINT16  ui2_mlm_idx = 0xFFFF;

    CHAR    s_type[32]   = {0};
    CHAR    s_brand[32]    = {0};
    CHAR    s_model[32]  = {0};
    CHAR    s_code_set[6] = {0};

    FILE * fl ;

    if ((ui2_mlm_idx = menu_page_naming_is_predef_name(ps_type_name)) != 0xFFFF)
    {
        c_uc_w2s_to_ps(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, ui2_mlm_idx),
                       ps_type_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }

    DBG_INFO(("%s() Line %d: device type = [%s]\n", __FUNCTION__, __LINE__, ps_type_name));

    if (b_g_is_3rd_exist == TRUE)
    {
        a_cfg_custom_get_device_info(ui1_input_id, s_type, s_brand, s_model, s_code_set);
        if ((c_strlen(s_type)) != 0)
        {
            a_cfg_custom_delete_device_info(ui1_input_id);
        }
    }

    fl = fopen ("/data/wifi_device_info","a+");
    if (fl == NULL)
    {
        DBG_INFO(("\n---Open wifi_device_info failed!---\n"));
        return APP_CFGR_INV_ARG;
    }
    fprintf(fl, "\n%d\t%s\t%s\t%s\t%s", ui1_input_id, ps_type_name, ps_brd_name, ps_model_name, ps_codeset);
    fclose (fl);

    if (ui1_input_id != 0)
    {
        a_cfg_custom_set_inp_name(ui1_input_id, ps_type_name);
    }

    a_cfg_custom_set_input_name_flag(ACFG_INPUT_NAME_DEV_TYPE);

    return APP_CFGR_OK;
}


INT32 a_cfg_custom_get_device_info(UINT8 ui1_input_id, CHAR* ps_type_name, CHAR* ps_brd_name, CHAR* ps_model_name, CHAR* ps_codeset)
{
    UINT16  ui2_idx = 0;
    UINT16  ui2_count = 0;
    CHAR    str_temp[256] = {0};
    CHAR    ch_inp_id[2] = {0};
    CHAR    s_type_name[32]   = {0};
    CHAR    s_brd_name[32]    = {0};
    CHAR    s_model_name[32]  = {0};
    CHAR    s_codeset[6] = {0};
    UINT16  ui2_mlm_idx      = 0;

    if (b_g_is_3rd_exist == FALSE)
    {
        b_g_is_3rd_exist = (access("/data/wifi_device_info", 0) == 0 ? TRUE : FALSE);
    }

    if (b_g_is_3rd_exist == FALSE)
    {
        if (ui1_input_id == 0)
        {
            a_cfg_custom_get_soundbar_codeset(s_codeset);
        }
        else
        {
            a_cfg_custom_get_current_codeset(s_codeset);
        }
    }
    else
    {
        FILE * fl = fopen ("/data/wifi_device_info","r");

        if (fl == NULL)
        {
            DBG_INFO(("\n---Open wifi_device_info failed!---\n"));

            c_strncpy(ps_type_name, s_type_name, 32);
            c_strncpy(ps_brd_name, s_brd_name, 32);
            c_strncpy(ps_model_name, s_model_name, 32);
            c_strncpy(ps_codeset, s_codeset, 6);

            return APP_CFGR_OK;
        }

        c_sprintf(ch_inp_id, "%d",  ui1_input_id);

        while ((fgets(str_temp, 256, fl) != NULL))
        {
            if (str_temp[0] == ch_inp_id[0])
            {
                c_memset(s_type_name, 0 , 32);
                c_memset(s_brd_name, 0 , 32);
                c_memset(s_model_name, 0 , 32);

                ui2_idx = 0;
                ui2_count = ui2_idx + 2;
                while ((ui2_idx<31) && (str_temp[ui2_count]!='\t'))
                {
                    s_type_name[ui2_idx]=str_temp[ui2_count];
                    ui2_count++;
                    ui2_idx++;
                }

                ui2_idx = 0;
                ui2_count++;

                while ((ui2_idx<31) && (str_temp[ui2_count]!='\t'))
                {
                    s_brd_name[ui2_idx]=str_temp[ui2_count];
                    ui2_count++;
                    ui2_idx++;
                }

                ui2_idx = 0;
                ui2_count++;

                while ((ui2_idx<31) && (str_temp[ui2_count]!='\t'))
                {
                    s_model_name[ui2_idx]=str_temp[ui2_count];
                    ui2_count++;
                    ui2_idx++;
                }

                ui2_idx = 0;
                ui2_count++;

                while ((ui2_idx<5) && (str_temp[ui2_count]!='\n'))
                {
                    s_codeset[ui2_idx]=str_temp[ui2_count];
                    ui2_count++;
                    ui2_idx++;
                }
            }
            c_memset(str_temp, 0 , 256);
        }

        fclose (fl);
    }

    c_strncpy(ps_type_name, s_type_name, 32);
    c_strncpy(ps_brd_name, s_brd_name, 32);
    c_strncpy(ps_model_name, s_model_name, 32);
    c_strncpy(ps_codeset, s_codeset, 6);

    ui2_mlm_idx = menu_page_naming_is_predef_name(ps_type_name);

    if (ui2_mlm_idx != 0xFFFF)
    {
        c_uc_w2s_to_ps(MENU_TEXT(ui2_mlm_idx), ps_type_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_delete_device_info(UINT8 ui1_input_id)
{
    CHAR    str_temp[256] = {0};
    CHAR    ch_inp_id[2] = {0};

    FILE * fl_r = fopen ("/data/wifi_device_info","r");
    FILE * fl_w = fopen ("/data/wifi_device_info_bk","w");

    if ((fl_r == NULL) || (fl_w == NULL))
    {
        if (fl_r) fclose(fl_r);
        if (fl_w) fclose(fl_w);
        DBG_INFO(("\n---Opne wifi_device_info failed!---\n"));
        return APP_CFGR_INV_ARG;
    }

    c_sprintf(ch_inp_id, "%d",  ui1_input_id);
    fputc('\n', fl_w);

    while ((fgets(str_temp, 256, fl_r) != NULL))
    {
        if (str_temp[0] != ch_inp_id[0])
        {
            fputs(str_temp, fl_w);
        }
    }

    remove("/data/wifi_device_info");
    rename("/data/wifi_device_info_bk", "/data/wifi_device_info");

    fclose(fl_r);
    fclose(fl_w);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_clear_device_info(VOID)
{
    FILE * fl = fopen ("/data/wifi_device_info","w");

    if (fl == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    fclose (fl);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_current_codeset(CHAR* s_codeset)
{

    INT32   i4_ret = APP_CFGR_OK;
    UINT32  ui4_written = 0;

    i4_ret = a_cfg_eep_raw_write(EEP_OFFSET_CODESET, (VOID*)s_codeset, 6*sizeof(CHAR), &ui4_written);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_current_codeset(CHAR* s_codeset)
{

    INT32   i4_ret = APP_CFGR_OK;
    UINT32  ui4_read = 0;

    i4_ret = a_cfg_eep_raw_read(EEP_OFFSET_CODESET, (VOID*)s_codeset, 6*sizeof(CHAR), &ui4_read);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_soundbar_codeset(VOID)
{

    INT32       i4_ret            = APP_CFGR_OK;
    CHAR        s_type_name[32]   = {0};
    CHAR        s_brand_name[32]  = {0};
    CHAR        s_model_name[32]  = {0};
    CHAR        s_codeset[6]      = {0};
    UINT32      ui4_written       = 0;

    i4_ret = a_cfg_custom_get_device_info(0, s_type_name, s_brand_name, s_model_name, s_codeset);
    if (i4_ret != APP_CFGR_OK)
    {
        c_memset(s_codeset, 0 , 6);
    }

    i4_ret = a_cfg_eep_raw_write(EEP_OFFSET_SOUNDBAR_CODESET, (VOID*)s_codeset, 6, &ui4_written);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_soundbar_codeset(CHAR* s_codeset)
{

    INT32   i4_ret = APP_CFGR_OK;
    UINT32  ui4_read = 0;

    i4_ret = a_cfg_eep_raw_read(EEP_OFFSET_SOUNDBAR_CODESET, (VOID*)s_codeset, 6, &ui4_read);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_device_type(UINT8 ui1_input_id, CHAR* ps_type_name)
{
    INT32    i4_ret = APP_CFGR_OK;
    UINT16  ui2_mlm_idx = 0xFFFF;

    CHAR    s_brand_name[32] = {0};
    CHAR    s_model_name[32] = {0};
    CHAR    s_codeset[6]     = {0};

    i4_ret = a_cfg_custom_get_device_info(ui1_input_id, ps_type_name,s_brand_name, s_model_name, s_codeset);

    if ((ui2_mlm_idx = menu_page_naming_is_predef_name(ps_type_name)) != 0xFFFF)
    {
        //DBG_INFO(("%s() Line %d: device type = [%s]\n", __FUNCTION__, __LINE__, ps_type_name));
        c_uc_w2s_to_ps(MENU_TEXT(ui2_mlm_idx), ps_type_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }

    return i4_ret;
}

INT32 a_cfg_custom_set_device_type(UINT8 ui1_input_id, CHAR* ps_type_name)
{
    INT32    i4_ret = APP_CFGR_OK;

    CHAR    s_type_name[32] = {0};
    CHAR    s_brand_name[32] = {0};
    CHAR    s_model_name[32] = {0};
    CHAR    s_codeset[6]     = {0};

    i4_ret = a_cfg_custom_get_device_info(ui1_input_id, s_type_name,s_brand_name, s_model_name, s_codeset);
    ACFG_LOG_ON_FAIL(i4_ret);

    if (c_strlen(s_type_name) == 0)
    {
        DBG_INFO(("%s() Line %d: device info is NULL\n", __FUNCTION__, __LINE__));
        //return APP_CFGR_OK;
    }

    i4_ret = a_cfg_custom_delete_device_info(ui1_input_id);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_device_info(ui1_input_id,ps_type_name, s_brand_name, s_model_name, s_codeset);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_inp_name(ui1_input_id, ps_type_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
INT32 a_cfg_custom_3d_brightness_boost(BOOL b_on)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
    INT16    i2_vid_back_light = 0;
    INT16    i2_min = 0;
    INT16    i2_max = 0;
    UINT16    ui2_idx = 0;

    INT32    i4_ret =  0;
    INT32           i4_drv_val;
    UINT16          ui2_scc_val;;
    SM_COMMAND_T    at_sm_cmds [4];


    a_cfg_custom_get_3d_brightness_boost(&ui2_idx);

    if(b_on && ui2_idx)
    {
        a_cfg_av_get(ui2_id, &i2_vid_back_light);
        a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
        DBG_INFO(("\n=a_cfg_custom_3d_brightness_boost=%d  %d =%d==%d\n",i2_vid_back_light,i2_min,i2_max,__LINE__));
        if((i2_vid_back_light * 2) > i2_max)
        {
            i2_vid_back_light = i2_max;
        }
        else
        {
            i2_vid_back_light = i2_vid_back_light*2;
        }

        /* convert to scc value */
        i4_ret = acfg_app2drv(i2_min, i2_max, i2_vid_back_light,
                              0, (INT32)SCC_ATTRIB_VALUE_MAX, &i4_drv_val);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        ui2_scc_val = (UINT16)i4_drv_val;

        at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_DISP;
        at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code        = SCC_CMD_CODE_DISP_BACK_LIGHT;
        at_sm_cmds[2].u.ui4_data    = ui2_scc_val;
        at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
        at_sm_cmds[3].u.ui4_data    = 0;
        i4_ret = c_scc_comp_grp_set(at_sm_cmds);
        ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);
        DBG_INFO(("\n========a_cfg_custom_3d_brightness_boost==%d==%d==%d\n",ui2_scc_val,i4_ret,__LINE__));
    }
    else
    {
        a_cfg_av_get(ui2_id, &i2_vid_back_light);
        DBG_INFO(("\n========a_cfg_custom_3d_brightness_boost====%d==%d\n",i2_vid_back_light,__LINE__));
        a_cfg_av_update(ui2_id);
    }
    return APP_CFGR_OK;
}
#endif

INT32 a_cfg_custom_set_ethernet_connected_status(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_ENTERNET_CONNECTED_STATUS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_ethernet_connected_status(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_ENTERNET_CONNECTED_STATUS, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_start_setup(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_START_SETUP, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_start_setup(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_START_SETUP, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

BOOL a_cfg_custom_get_one_button_support(VOID)
{
    BOOL b_one_button = TRUE;

    if (0 == access("/tmp/disable_panel_one_button", R_OK))
    {
        b_one_button = FALSE;
    }
    else
    {
        b_one_button = TRUE;
    }

    return b_one_button;
}

VOID a_cfg_custom_set_input_name_flag(ACFG_INPUT_NAME_LATEST e_name)
{
    e_ipt_name = e_name;
}

ACFG_INPUT_NAME_LATEST a_cfg_custom_get_input_name_flag(VOID)
{
    return e_ipt_name;
}

INT32 a_cfg_custom_get_dst(UINT16* pui2_value)
{
    SIZE_T  z_size;

    if (NULL == pui2_value)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_DST, (VOID*)pui2_value, &z_size);
}

INT32 a_cfg_custom_set_dst(UINT16 ui2_value)
{
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;

    a_cfg_get_time_zone_data(&t_tz_offset, &b_dls);

    if (ui2_value == 1)
    {
        b_dls = TRUE;
    }
    else
    {
        b_dls = FALSE;
    }

    acfg_set(IDX_CUSTOM_DST, (VOID*)&ui2_value, 1);
    a_cfg_set_time_zone_data(t_tz_offset, b_dls);
    a_cfg_update_time_zone();

    return APP_CFGR_OK;
}

BOOL a_cfg_custom_chk_freqence_120hz(VOID)
{
    BOOL b_ret = FALSE;
    VSH_SRC_RESOLUTION_INFO_T t_timing = {0};

    ACFG_LOG_ON_FAIL(a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_timing));

//    DBG_INFO(("\nCurrent Source is %dHz\n\n", t_timing.ui4_frame_rate));

    if (t_timing.ui4_frame_rate < 1000 && t_timing.ui4_frame_rate >= 120)
    {
        b_ret = TRUE;
    }

    return b_ret;
}

BOOL a_cfg_custom_chk_freqence_24hz(VOID)
{
    BOOL b_ret = FALSE;
    VSH_SRC_RESOLUTION_INFO_T t_timing = {0};

    ACFG_LOG_ON_FAIL(a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_timing));

  //  DBG_INFO(("\nCurrent Source is %dHz\n\n", t_timing.ui4_frame_rate));

    if (t_timing.ui4_frame_rate == 2400)
    {
        b_ret = TRUE;
    }

    return b_ret;
}

BOOL a_cfg_custom_chk_panel_120hz(VOID)
{
    BOOL      b_is_panel_120hz = FALSE;
#if 0// need d_interface support
    DRV_CUST_OPERATION_INFO_T        t_op_info;
    SIZE_T                            z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                            z_size = sizeof(UINT32);
    UINT32                            ui4_model_120hz;
    INT32                            i4_ret = APP_CFGR_OK;
    BOOL                            b_is_panel_120hz = TRUE;

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_SUPPORT_120HZ;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = &ui4_model_120hz;
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

    if (ui4_model_120hz == 0)
    {
        b_is_panel_120hz = FALSE;
    }
    else
    {
        b_is_panel_120hz = TRUE;
    }

#endif
    return b_is_panel_120hz;
}

INT32 a_cfg_custom_service_reset(UINT16  ui2_value,BOOL b_power_on)
{
    INT32           i4_ret       = APP_CFGR_OK;
    HANDLE_T        h_main_svctx = NULL_HANDLE;

    DBG_LOG_PRINT(("[%s %d]ui2_value= %d,b_power_on = %d\n",__FUNCTION__,__LINE__,ui2_value,b_power_on));
    a_cfg_cust_set_force_reboot_up_flag(b_power_on ? ACFG_FORCE_REBOOT_UP_ON : ACFG_FORCE_REBOOT_UP_OFF);

    /*stop all svc(vidio,audio) when do service reset */
    if(ui2_value == 1)
    {
        if(b_power_on && a_cfg_cust_get_support_local_dimming())
        {
            ACFG_CustDrv_Set_Backlight(10000, 0);
        }
        a_cfg_cust_backlight_onoff(FALSE);
        nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_main_svctx);
        a_tv_stop_all_svc(h_main_svctx, NULL_HANDLE);
        a_cfg_store();
    }

    //need d_interface support
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(INT16);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type                    = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_vid_set_info.e_vid_type  = DRV_CUSTOM_CUST_SPEC_TYPE_SERVICE_RESET;
    t_op_info.u.t_vid_set_info.b_store     = FALSE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&ui2_value;
    t_op_info.u.t_vid_set_info.z_size      = z_size;


    /* set to driver */
    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );

    return i4_ret;
}


#if (VIEWPORT_SUPPORT == 1)
VOID a_cfg_custom_set_view_mode_idx(APP_CFG_VIEWPORT_TYPE_T e_viewport)
{
#define _SET_VIEWPORT_REGION(pt_reg, x, y, w, h)               \
    do {                                                   \
        (pt_reg)->ui4_x      = x;                          \
        (pt_reg)->ui4_y      = y;                          \
        (pt_reg)->ui4_width  = w;                          \
        (pt_reg)->ui4_height = h;                          \
    } while (0)

    APP_CFG_VIEWPORT_T      t_next_viewport;
    VSH_REGION_INFO_T       t_disp_region;
    UINT8                   ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;

    if (!a_cfg_is_able_to_apply_viewport ())
    {
        ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;

        a_icl_set(ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                 (VOID *) &ui1_sts,
                 ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);
    }
    else
    {
        ui1_sts = ICL_VIEWPORT_LAST_REQ_SUCCEED;

        a_icl_set(ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                  (VOID *) &ui1_sts,
                  ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);
    }

    switch (e_viewport)
    {
    case APP_CFG_VIEWPORT_TYPE_VIEWPORT:
        _SET_VIEWPORT_REGION (&t_disp_region, 3333, 1666, 6667, (VSH_REGION_MAX_WIDTH-1666*2));
        break;
    case APP_CFG_VIEWPORT_TYPE_CENTER_OVERLAY:
        _SET_VIEWPORT_REGION (&t_disp_region, 1615, 0, VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT);
        break;
    default:
        _SET_VIEWPORT_REGION (&t_disp_region, 0, 0, VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT);
        break;
    }

    t_next_viewport.e_type = e_viewport;
    t_next_viewport.i4_x = (INT32)(t_disp_region.ui4_x*1920/VSH_REGION_MAX_WIDTH);
    t_next_viewport.i4_y = (INT32)(t_disp_region.ui4_y*1080/VSH_REGION_MAX_HEIGHT);
    t_next_viewport.i4_w = (INT32)(t_disp_region.ui4_width*1920/VSH_REGION_MAX_WIDTH);
    t_next_viewport.i4_h = (INT32)(t_disp_region.ui4_height*1080/VSH_REGION_MAX_HEIGHT);

    a_cfg_set_viewport (&t_next_viewport);
    a_cfg_update_viewport ();

    return;
}
#endif

INT32 a_cfg_update_11_point(VOID* pv_GammactrlPts, SIZE_T z_size_val)
{
    INT32 i4_ret = APP_CFGR_OK;
    i4_ret = a_cfg_update_20_point(pv_GammactrlPts, z_size_val);
    return i4_ret;
}

INT32 a_cfg_update_smpte_pattern(UINT8 ui1_val)
{
    INT32 i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_PRE_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(&ui1_val);
    t_op_info.u.t_vid_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size);
    return i4_ret;
}

INT32 a_cfg_update_flat_pattern(DRV_CUSTOM_SCE_PATTERN_T *pCPattern)
{
    INT32 i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    if (NULL == pCPattern)
    {
        return APP_CFGR_INV_ARG;
    }

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_SCE_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = pCPattern;
    t_op_info.u.t_vid_set_info.z_size = sizeof(DRV_CUSTOM_SCE_PATTERN_T);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size);

    return i4_ret;
}

INT32 a_cfg_update_ramp_pattern(UINT8 ui1_val)
{
    INT32 i4_ret = APP_CFGR_OK;

    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_PRE_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(&ui1_val);
    t_op_info.u.t_vid_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size);

    return i4_ret;
}

INT32 a_cfg_custom_set_hotkey_wakeup_active(UINT8 ui1_hotkey_active)
{
    INT32       i4_ret = APP_CFGR_OK;
#if 0
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_HOTKEY_ENABLE_CTRL;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_hotkey_active;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
#endif
#endif
    return i4_ret;
}


INT32 a_cfg_custom_get_hotkey_wakeup_active(UINT8 *pui1_hotkey_active)
{
    INT32       i4_ret = APP_CFGR_OK;
#if 0
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_op_info_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(UINT8);

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_HOTKEY_ENABLE_CTRL;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = pui1_hotkey_active;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_op_info_size
                            );
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif
    return i4_ret;
}

#ifdef APP_EMANUAL_SP6_SUPPORT
INT32 a_cfg_custom_get_rd_version(UTF16_T *pw2s_rd)
{
    CHAR            s_mg[4] = {0};
    CHAR            s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    CHAR            s_mc[128] = {0};

    CHAR            s_lang[3] = {0};
    ISO_639_LANG_T  s639_lang;
    CHAR            s_version[2] = {0};
    CHAR            *p_str = NULL;

    /* Get model group */
    p_str = getenv("SYS_MG");
    c_strcpy(s_mg, (p_str!=NULL? p_str : "000"));
    s_mg[3] = 0;

    /* Get model name */
    a_cfg_custom_plf_opt_get_model_name(s_model_name, PLF_OPT_MODEL_NAME_LEN);

    /* Get language */
    a_cfg_get_gui_lang(s639_lang);

    if (c_strcmp(s639_lang, "spa") == 0)
    {
        s_lang[0] = 'E';
        s_lang[1] = 'S';
        s_lang[2] = 0;
    }
    else
    {
        s_lang[0] = s639_lang[0]-32;
        s_lang[1] = s639_lang[1]-32;
        s_lang[2] = 0;
    }

    /* Get version */
    s_version[0] = 'A';
    s_version[1] = 0;

    if (pw2s_rd != NULL)
    {
        c_snprintf(s_mc,127, "%s_%s_%s_%s", s_mg,
                                             s_model_name,
                                             s_lang,
                                             s_version);
        c_uc_ps_to_w2s(s_mc, pw2s_rd, c_strlen(s_mc));
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_ml_version(UTF16_T *pw2s_mc)
{
    CHAR            s_mg[4] = {0};
    CHAR            s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    CHAR            s_mc[128] = {0};

    CHAR            s_lang[3] = {0};
    ISO_639_LANG_T  s639_lang;
    CHAR            s_version[2] = {0};
    CHAR            s_ym[7] = {0};
    CHAR            s_status[2] = {0};
    CHAR            *p_str = NULL;

    /* Get model group */
    p_str = getenv("SYS_MG");
    c_strcpy(s_mg, (p_str!=NULL ? p_str : "000"));
    s_mg[3] = 0;

    /* Get model name */
    a_cfg_custom_plf_opt_get_model_name(s_model_name, PLF_OPT_MODEL_NAME_LEN);

    /* Get language */
    a_cfg_get_gui_lang(s639_lang);

    if (c_strcmp(s639_lang, "spa") == 0)
    {
        s_lang[0] = 'E';
        s_lang[1] = 'S';
        s_lang[2] = 0;
    }
    else
    {
        s_lang[0] = s639_lang[0]-32;
        s_lang[1] = s639_lang[1]-32;
        s_lang[2] = 0;
    }

    /* Get version */
    s_version[0] = 'A';
    s_version[1] = 0;

    /* Get year month */
    c_strcpy(s_ym, "0000");
    s_ym[6] = 0;

    /* Get status */
    s_status[0] = 'Y';
    s_status[1] = 0;

    if (pw2s_mc != NULL)
    {
        c_snprintf(s_mc, 127, "%s_%s_%s_%s %s %s", s_mg,
                                             s_model_name,
                                             s_lang,
                                             s_version,
                                             s_ym,
                                             s_status);
        c_uc_ps_to_w2s(s_mc, pw2s_mc, c_strlen(s_mc));
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_mc_version(UTF16_T *pw2s_mc)
{
    static CHAR     s_mc[128] = {0};
    CHAR            *p_str = NULL;
    ISO_639_LANG_T  s639_lang;

    /* Get model group */
    if ('\0' == t_mc_info.s_mg[0])
    {
        p_str = getenv("SYS_MG");
        c_strcpy(t_mc_info.s_mg, (p_str!=NULL ? p_str : "000"));
        t_mc_info.s_mg[3] = 0;
    }

    /* Get model name */
    if('\0' == t_mc_info.s_model_name[0])
    {
        a_cfg_custom_plf_opt_get_model_name(t_mc_info.s_model_name, PLF_OPT_MODEL_NAME_LEN);
    }

    /* Get language */
    a_cfg_get_gui_lang(s639_lang);

    if (c_strcmp(s639_lang, "spa") == 0)
    {
        t_mc_info.s_lang[0] = 'E';
        t_mc_info.s_lang[1] = 'S';
        t_mc_info.s_lang[2] = 0;
    }
    else
    {
        t_mc_info.s_lang[0] = s639_lang[0]-32;
        t_mc_info.s_lang[1] = s639_lang[1]-32;
        t_mc_info.s_lang[2] = 0;
    }
    /* Get version */
    t_mc_info.s_version[0] = 'A';
    t_mc_info.s_version[1] = 0;

    /* Get year month */
    c_strcpy(t_mc_info.s_ym, "0000");
    t_mc_info.s_ym[6] = 0;

    /* Get status */
    t_mc_info.s_status[0] = 'Y';
    t_mc_info.s_status[1] = 0;

    if (pw2s_mc != NULL)
    {
        c_snprintf(s_mc, 127, "%s_%s_%s_%s %s %s", t_mc_info.s_mg,
                                         t_mc_info.s_model_name,
                                         t_mc_info.s_lang,
                                         t_mc_info.s_version,
                                         t_mc_info.s_ym,
                                         t_mc_info.s_status);

        c_uc_ps_to_w2s(s_mc, pw2s_mc, c_strlen(s_mc));
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_test_mc_version(UINT16 *pw2s_mc_ver)
{
    if (NULL == pw2s_mc_ver
        || c_uc_w2s_strlen(pw2s_mc_ver) == 0)
    {
        c_memset(w2s_test_mc_version, 0, sizeof(w2s_test_mc_version));
        return APP_CFGR_OK;
    }

    c_uc_w2s_strcpy(w2s_test_mc_version, pw2s_mc_ver);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_test_mc_version(UINT16 *pw2s_mc_ver)
{
    if (NULL == pw2s_mc_ver)
    {
        return APP_CFGR_INV_ARG;
    }

    c_uc_w2s_strcpy(pw2s_mc_ver, w2s_test_mc_version);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_req_mc_version(UTF16_T *pw2s_mc_ver)
{
    CHAR s_mc[APP_CFG_MC_VERSION_LEN+1] = {0};

    if (NULL == pw2s_mc_ver)
    {
        return APP_CFGR_INV_ARG;
    }

    a_cfg_custom_get_test_mc_version(pw2s_mc_ver);
    if (c_uc_w2s_strlen(pw2s_mc_ver) == 0)
    {
        a_cfg_custom_get_mc_version(NULL);

        c_sprintf(s_mc, "%s_%s_%s_%s", t_mc_info.s_mg,
                                       t_mc_info.s_model_name,
                                       t_mc_info.s_lang,
                                       t_mc_info.s_version);
        c_uc_ps_to_w2s(s_mc, pw2s_mc_ver, APP_CFG_MC_VERSION_LEN);
    }

    return APP_CFGR_OK;
}
#endif

INT32 a_cfg_custom_get_wide_mode_enable_change(BOOL *pb_enable)
{
    INT32       i4_ret = APP_CFGR_OK;
    CHAR        s_resume_ap[APP_NAME_MAX_LEN+1] = {0};

    MMP_BE_BROWSER_MEDIA_TYPE   e_mmp_media_type = MMP_BE_BROWSER_MEDIA_TYPE_NONE;
    MMP_BE_BROWSER_STATUS_T     e_mmp_browse_status = MMP_BE_BROWSER_STATUS_NONE;
#ifdef APP_MENU_MMP_COEXIST
    MMP_MAIN_AP_STATUS_T        e_mmp_status = MMP_MAIN_AP_STATUS_DEINITED;
#endif
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_input_id;
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
    UINT32                      ui4_video_height = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Get current timing */
    a_cfg_av_get_timing(s_disp_name, &t_timing);
    c_svctx_get_well_defined_video_heigh(t_timing.ui4_height,&ui4_video_height);
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
    {
        c_svctx_get_well_defined_video_heigh(t_timing.ui2_orig_height,&ui4_video_height);
    }
    else
    {
        c_svctx_get_well_defined_video_heigh(t_timing.ui4_height,&ui4_video_height);
    }

    do {
        /* 120hz */
        if (a_cfg_custom_chk_freqence_120hz())
        {
            DBG_INFO(("%s() %d: freqence_120hz\n",__FUNCTION__,__LINE__));
            *pb_enable = FALSE;
            break;
        }
#ifdef APP_HDR_SUPPORT
        UINT8  ui1_type = a_acfg_cust_get_video_type();
        if ( ui1_type != SCC_VID_PQ_SDR )
        {
            DBG_INFO(("%s() %d: PQ_SDR = 0,PQ_HDR10,PQ_HLG,PQ_DOVI,PQ_TECHNI,PQ_HDR10PLUS = 5. hdr content\n",__FUNCTION__,__LINE__));
            *pb_enable = FALSE;
            break;
        }
#endif
        /* native netflix */
        if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL
            && t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST
            && a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
        {
            DBG_INFO(("%s() %d: native netflix\n",__FUNCTION__,__LINE__));
            *pb_enable = FALSE;
            break;
        }
        /* MMP Select */
        a_am_get_active_app(s_resume_ap);
        e_mmp_status = a_mmp_get_ap_status();
        e_mmp_browse_status = a_mmp_be_get_browser_status();
        /* judge if it's MMP or MMP_MENU_COEXIST */

        if (((c_strcmp(s_resume_ap, MMP_NAME) == 0) && MMP_MAIN_AP_STATUS_PAUSED != e_mmp_status)
#ifdef APP_MENU_MMP_COEXIST
            || MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status
#endif
            )
        {

        /*if mmp lunch by cast .can not change wide mode*/
            if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL &&
                t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
            {
                DBG_INFO(("%s() %d: mmp in cast tv ,return false\n",__FUNCTION__,__LINE__));
                *pb_enable = FALSE;
                 break;
            }

            e_mmp_media_type = a_mmp_be_get_media_type();

            if (MMP_BE_BROWSER_MEDIA_TYPE_AUDIO == e_mmp_media_type||
                MMP_BE_BROWSER_MEDIA_TYPE_PHOTO == e_mmp_media_type)
            {
                DBG_INFO(("%s() %d: MMP_BE_BROWSER_MEDIA_TYPE_AUDIO or MMP_BE_BROWSER_MEDIA_TYPE_PHOTO\n",__FUNCTION__,__LINE__));
                *pb_enable = FALSE;
                break;
            }
            else if ((MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NORMAL_PREVIEW == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_FF_PREVIEW == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_FR_PREVIEW == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NOT_PLAYING == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_LIST_FF_PREVIEW == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_LIST_FR_PREVIEW == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_LIST_NORMAL_PREVIEW == e_mmp_browse_status) ||
                     (MMP_BE_BROWSER_STATUS_VIDEO_LIST_NOT_PLAYING == e_mmp_browse_status))
            {
                DBG_INFO(("%s() %d: error mmp e_mmp_browse_status status %d\n",__FUNCTION__,__LINE__,e_mmp_browse_status));
                *pb_enable = FALSE;
                break;
            }
        }

        if(ui4_video_height == VIDEO_HEIGHT_2160 || (ui4_video_height == VIDEO_HEIGHT_1080 && t_timing.b_is_progressive == TRUE))
        {
            DBG_INFO(("%s() %d:  a_cfg_av_get_timing timing %d\n",__FUNCTION__,__LINE__,t_timing.ui4_height));
            *pb_enable = FALSE;
            break;
        }

        /* cast can not change wide mode*/
        if((t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL) &&
           (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST))
        {
            *pb_enable = FALSE;
             break;
        }

        *pb_enable = TRUE;
    }while(0);

    return i4_ret;
}

INT32 a_cfg_custom_updater_completed_trig_fac(VOID)
{
    INT32 i4_ret = APP_CFGR_OK;

    i4_ret = acfg_cust_odm_clear_fac_setting();

    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name:
*                 a_cfg_custom_get_tuner_name
* Description:
*                         This API is used to get customer tuner name from d-interface.
* Input arguments:
*        pui4_tuner_index      Contains the index of the customer tuner.
*
* Output arguments:
*                   None
* Returns:
*                  None
*---------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_tuner_name(CHAR *s_tuner_name)
{
    c_strcpy(s_tuner_name, "SI12152");
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_power_mode(UINT16 ui2_eco)
{
#ifdef APP_SUPPORT_STR_CORE_OFF
    ACFG_LOG_ON_FAIL(a_cfg_set_fast_boot(ui2_eco == 0 ? APP_CFG_FAST_BOOT_ON : APP_CFG_FAST_BOOT_OFF));
#endif
    ACFG_LOG_ON_FAIL(a_cfg_custom_set_drv_eco_mode(ui2_eco == 0 ? ICL_CUSTOM_POWER_MODE_ECO : ICL_CUSTOM_POWER_MODE_QUICK_START));
    ACFG_LOG_ON_FAIL(a_icl_custom_set_power_mode(ui2_eco == 0 ? ICL_CUSTOM_POWER_MODE_ECO : ICL_CUSTOM_POWER_MODE_QUICK_START));

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_reset_power_mode(VOID)
{
    INT32   i4_ret = APP_CFGR_OK;
#ifdef APP_SUPPORT_STR_CORE_OFF
    i4_ret = a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_ECO);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_icl_custom_set_power_mode(ICL_CUSTOM_POWER_MODE_ECO);
    ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_drv_eco_mode(UINT16 ui2_eco)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_ECO_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_eco;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT16);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_drv_eco_mode(UINT32 *pui4_eco)
{
    INT32                        i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(UINT32);
    UINT32                       ui4_val = 0;

    if (NULL == pui4_eco)
    {
       DBG_ERROR(("{a_cfg_custom_get_eco_mode()INV_ARG!!!}%s,%d\n", __FUNCTION__, __LINE__));
       return APP_CFGR_INV_ARG;
    }

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_ECO_MODE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("{GET ECO MODE}%s i4_ret : %d\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    *pui4_eco = (ui4_val & 0x000000FF);
    return i4_ret;
}

INT32 a_cfg_custom_set_drv_watchdog_flag(UINT8 ui1_watchdog_flag)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_WATCHDOG_FLAG;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_watchdog_flag;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_drv_watchdog_flag(UINT32 *pui4_watchdog_flag)
{
    INT32                        i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(UINT32);
    UINT32                       ui4_val = 0;

    if (NULL == pui4_watchdog_flag)
    {
       DBG_ERROR(("{a_cfg_custom_get_drv_watchdog_flag()INV_ARG!!!}%s,%d\n", __FUNCTION__, __LINE__));
       return APP_CFGR_INV_ARG;
    }

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_WATCHDOG_FLAG;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("{GET WATCHDOG FLAG}%s i4_ret : %d\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    *pui4_watchdog_flag = (ui4_val & 0x000000FF);
    return i4_ret;
}


INT32 a_cfg_custom_set_drv_bgmupdate_flag(UINT8 ui1_bgmupdate_flag)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_BGM_UPDATE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_bgmupdate_flag;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_drv_bgmupdate_flag(UINT32 *pui4_bgmupdate_flag)
{
    INT32                        i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(UINT32);
    UINT32                       ui4_val = 0;

    if (NULL == pui4_bgmupdate_flag)
    {
       DBG_ERROR(("{a_cfg_custom_get_drv_bgmupdate_flag()INV_ARG!!!}%s,%d\n", __FUNCTION__, __LINE__));
       return APP_CFGR_INV_ARG;
    }

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_BGM_UPDATE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("{GET BGMUPDATE FLAG}%s i4_ret : %d\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    *pui4_bgmupdate_flag = (ui4_val & 0x000000FF);
    return i4_ret;
}


INT32 a_cfg_custom_get_sys_pin_passed(BOOL *pb_passed)
{
    if (pb_passed != NULL)
    {
        *pb_passed = b_g_sys_pin_passed;
    }
    else
    {
        DBG_ERROR(("[ACFG] invalid arg!\n"));
        return APP_CFGR_INV_ARG;
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_sys_pin_passed(BOOL b_passed)
{
    DBG_LOG_PRINT(("[ACFG][SYS_PIN]{%s,%d} b_passed:%d, \n", __FUNCTION__, __LINE__, b_passed  ));

    b_g_sys_pin_passed = b_passed;

    return APP_CFGR_OK;
}

BOOL a_cfg_custom_is_hot_key_wakeup(VOID)
{
    BOOL b_hot_key_wakeup = FALSE;

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
    PCL_WAKEUP_KEY_T            t_wakeup_key = {0};
    c_pcl_get_wakeup_reason(&e_wakeup_reason,NULL);
    if (c_pcl_get_hotkey_active()
        && (c_pcl_get_wakeup_irkey(&t_wakeup_key) == PCLR_OK)
        && (PCL_WAKEUP_KEY_HOTKEY == t_wakeup_key.e_key_type)
        && e_wakeup_reason == PCL_WAKE_UP_REASON_IRRC )
    {
        DBG_INFO(("%s() %d Hotkey wakeup\n",__FUNCTION__,__LINE__));
        b_hot_key_wakeup = TRUE;
    }
    else
#endif
    {
        b_hot_key_wakeup = FALSE;
    }

    DBG_INFO(("%s() %d return %d\n",__FUNCTION__,__LINE__,b_hot_key_wakeup));

    return b_hot_key_wakeup;
}

VOID a_cfg_custom_set_wake_from_suspend(BOOL b_val)
{
    DBG_INFO(("Set wake from suspend =%d.\n", b_val));
    b_wake_from_suspend = b_val;
}

BOOL a_cfg_custom_is_wake_from_suspend(VOID)
{
    DBG_INFO(("Wake from suspend=%d.\n", b_wake_from_suspend));
    return b_wake_from_suspend;
}

BOOL a_cfg_custom_is_splash_show(VOID)
{
    DBG_INFO(("Splash show=%d.\n", b_g_splash_show));
    return b_g_splash_show;
}

INT32 a_cfg_custom_show_splash(INDICATOR_MSG *pt_msg)
{
    INDICATOR_MSG msg = {0};

    struct mq_attr g_mqd_attr;
    mqd_t mqd_t = mq_open(GET_MQD_LOADING,O_CREAT|O_RDWR, 0666, NULL);

    if (NULL == pt_msg)
    {
        DBG_ERROR(("<ACFG>%s() Invalid arg\n",__FUNCTION__));
        return APP_CFGR_INV_ARG;
    }

    c_memcpy(&msg, pt_msg, sizeof(INDICATOR_MSG));


    if (mqd_t < 0)
    {
        perror("mq_open fail");
        return APP_CFGR_INTERNAL_ERR;
    }
    if (mq_getattr(mqd_t, &g_mqd_attr) < 0)
    {
        perror("get attr fail");
        return APP_CFGR_INTERNAL_ERR;
    }
    DBG_INFO(("\n%s,%d,mqd_t=%x\n", __FUNCTION__, __LINE__, mqd_t));

    if(mq_send(mqd_t, (char*)pt_msg, sizeof(INDICATOR_MSG) - sizeof(long), 0) == -1)
    {
        DBG_INFO(("[ERROR] a_cfg_custom_show_splash - Send msg to mtk indicator failed!\n"));
        return APP_CFGR_INTERNAL_ERR;
    }

    b_g_splash_show = (INDICATOR_MSG_SPLASH_SHOW == msg.msgType) ? TRUE : FALSE;

    DBG_INFO(("Splash show=%d.\n", b_g_splash_show));

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_bootup_assistant_flag(UINT8 *pui1_flag)
{
    SIZE_T z_size = 0;

    if (NULL == pui1_flag)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_get(IDX_CUST_BOOTUP_ASSISTANT, pui1_flag, &z_size);
}

/*
Added for CR DTV00873058
Currently, this flag used for indicating OOBE entered via factory reset, and clear the flag when exit OOBE
*/
INT32 a_cfg_custom_set_bootup_assistant_flag(UINT8 ui1_flag)
{
    return acfg_set(IDX_CUST_BOOTUP_ASSISTANT, &ui1_flag, 1);
}

INT32 a_cfg_custom_get_factory_11_point_red(UINT8*  pui1_rgb)
{
    SIZE_T  z_size = sizeof(UINT8);

    if (NULL == pui1_rgb)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_RED, (VOID*)pui1_rgb, &z_size);
}

INT32 a_cfg_custom_set_factory_11_point_red(UINT8*  pui1_rgb)
{
    if (NULL == pui1_rgb)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_set(IDX_CUSTOM_FAC_CUST_11_POINT_RED, (VOID*)pui1_rgb, 44);
}

INT32 a_cfg_custom_get_factory_11_point_green(UINT8*  pui1_rgb)
{
    SIZE_T  z_size = sizeof(UINT8);

    if (NULL == pui1_rgb)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN, (VOID*)pui1_rgb, &z_size);
}

INT32 a_cfg_custom_set_factory_11_point_green(UINT8*  pui1_rgb)
{
    if (NULL == pui1_rgb)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_set(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN, (VOID*)pui1_rgb, 44);
}

INT32 a_cfg_custom_get_factory_11_point_blue(UINT8*  pui1_rgb)
{
    SIZE_T  z_size = sizeof(UINT8);

    if (NULL == pui1_rgb)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE, (VOID*)pui1_rgb, &z_size);
}

INT32 a_cfg_custom_set_factory_11_point_blue(UINT8*  pui1_rgb)
{
    if (NULL == pui1_rgb)
    {
        ACFG_CHK_FAIL(APP_CFGR_INV_ARG, APP_CFGR_INV_ARG);
    }
    return acfg_set(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE, (VOID*)pui1_rgb, 44);
}
/*
This api is add for [INX][TMC-4904][SPRINT2.1][D40f-G9]Some back panel keys behavior incorrect
This issue request the long press of power will be ignore for OOBE not complete case
*/
INT32 a_cfg_custom_update_long_press_ignore(VOID)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT16  ui2_status  = 0;
    UINT8   ui1_long_press_ignore = 1;
    a_cfg_get_wzd_status(&ui2_status);
    DRV_CUST_OPERATION_INFO_T t_op_info;
    UINT8       ui1_state   = 0;
    SIZE_T  z_size;
    z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    if(ui1_state == WZD_STATE_RESUME_C4TV)
    {
        ui1_long_press_ignore = 1;
    }
    else
    {
        ui1_long_press_ignore = 0;
    }
    DBG_INFO(("%s_%d ui1_long_press_ignore:%d \n",__FUNCTION__,__LINE__,ui1_long_press_ignore));
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LONG_PRESS_IGNORE ;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_long_press_ignore;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    return i4_ret;
}

INT32 a_cfg_custom_reset_input_src_pic_setting(VOID)
{
    INT32   i4_default = 0;
    SIZE_T  size       = 1;

    ACFG_CUST_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI1_VGA_SETTING,&i4_default,size));
    ACFG_CUST_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI2_VGA_SETTING,&i4_default,size));
    ACFG_CUST_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI3_VGA_SETTING,&i4_default,size));
    ACFG_CUST_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI4_VGA_SETTING,&i4_default,size));
    ACFG_CUST_CHK_FAIL(acfg_set(IDX_CUSTOM_COMP_VGA_SETTING,&i4_default,size));

    return APP_CFGR_OK;
}

INT32 a_cfg_cust_set_dynamic_content_value(UINT8  ui1_value)
{
    if(ui1_value == 1)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",__FILE__, __FUNCTION__, __LINE__));
        AP_SYSTEM_CALL("touch /tmp/cfg_adreplacement_disabled");
    }
    else
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",
            __FILE__, __FUNCTION__, __LINE__));
        ACFG_LOG_ON_FAIL(remove("/tmp/cfg_adreplacement_disabled"));
    }
    return acfg_set(IDX_CUSTOM_DYNAMIC_CONTENT, &ui1_value, 1);
}


INT32 a_cfg_cust_get_dynamic_content_value(UINT8* ui1_value)
{
    SIZE_T   z_size;
    if (ui1_value == NULL)
    {
        DBG_ERROR(("[ACFG][%s]:[%d]This is wrong address\n",__FILE__,__LINE__));
        return FALSE;
    }
    return acfg_get(IDX_CUSTOM_DYNAMIC_CONTENT, ui1_value, &z_size);
}

static UINT8*  g_ps_image_data = NULL;
char    g_bootlogo_file_path[256] = {0};


INT32 _app_logo_callback_fct(
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    return 0;
}

INT32 a_cfg_custom_draw_logo_init(VOID)
{
    INT32               i4_ret      = 0;

    FILE*               pFile       = NULL;

    if(st_bootlogo.b_is_init)
    {
        DBG_ERROR(("[%s] [%d] had init\n", __FUNCTION__,__LINE__));
        return 0;
    }

    do
    {
        i4_ret = MI_SYS_Init(NULL);
        if (i4_ret >= MI_ERR_FAILED)
        {
            DBG_ERROR(("[%s] [%d] MI_SYS_Init init fail!! i4_ret:%d\n", __FUNCTION__,__LINE__,i4_ret));
            break;
        }

        MI_FS_InitParams_t stFsInitParam = {0};
        i4_ret = MI_FS_Init(&stFsInitParam);
        if (i4_ret >= MI_ERR_FAILED)
        {
            DBG_ERROR(("[%s] [%d] MI_FS_Init init fail!! i4_ret:%d\n", __FUNCTION__,__LINE__,i4_ret));
            break;
        }

        //2. init GL pannel and create GL window
        /*open screen*/
        i4_ret = c_gl_screen_open(MMP_RC_DISPLAY_NAME, NULL, NULL, &st_bootlogo.h_screen);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[%s] [%d] c_gl_screen_open fail!! i4_ret:%d\n", __FUNCTION__,__LINE__,i4_ret));
            break;
        }

        /*init logo show plane*/ //index == 0  => use layer 1,index == 1  => use layer 0
#ifdef MT5583_MODEL
        i4_ret = c_gl_plane_open(st_bootlogo.h_screen
#ifdef APP_MERGE_INTO_ONE_OSD
                             , (UINT16)0
#else
                             , (UINT16)1
#endif
                                         , &st_bootlogo.h_plane);
#else
        i4_ret = c_gl_plane_open(st_bootlogo.h_screen, (UINT16)1, &st_bootlogo.h_plane);
#endif
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[%s] [%d] c_gl_plane_open(%d) fail!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, 0, i4_ret));
            break;
        }

        /*link show plane to screen*/
        i4_ret = c_gl_plane_link(st_bootlogo.h_plane, st_bootlogo.h_screen, TRUE);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[%s] [%d] c_gl_plane_link() fail!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        /* get canvas for frame creation */
        i4_ret = c_wgl_get_canvas(st_bootlogo.h_plane,&st_bootlogo.h_canvas);
        if (WGLR_OK != i4_ret)
        {
            DBG_ERROR(("[%s] [%d] c_wgl_get_canvas() fail!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        GL_RECT_T t_rect;
        c_wgl_register(_app_logo_callback_fct);
        SET_RECT_BY_SIZE(&t_rect,0,0,1920,1080);
        i4_ret = c_wgl_create_widget(st_bootlogo.h_canvas,  /* specify the canvas as parent */
                                    HT_WGL_WIDGET_FRAME,    /* the type id of Frame widget */
                                    WGL_CONTENT_FRAME_DEF,  /* the type id of Frame widget's defaultcontent */
                                    WGL_BORDER_NULL,        /* select the Raised border */
                                    &t_rect,                /* the rect of the frame relative to canvas's left-top corner */
                                    c_wgl_default_msg_proc,/* the user-defined widget procedure for the frame */
                                    255,                    /* the translucency of this widget (alpha:0~255) */
                                    (VOID *)WGL_STL_GL_NO_IMG_UI, /* the initial parameter for the frame, turn off Image-UI */
                                    NULL,                   /* attach this pointer as a tag of the main_frame handle, it will be used in notify function */
                                    &(st_bootlogo.h_main_frame));   /* returns the handle of the new frame */
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] [%d] c_wgl_create_widget() h_main_frame fail!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        // Alloc Memory
        g_ps_image_data = malloc(1920*1080*4);

        if(g_bootlogo_file_path[0] == '\0' ||
           NULL == (pFile = MI_FS_Fopen((const MI_U8 *)g_bootlogo_file_path,(const MI_U8 *)"rb")))
        {
            if(NULL == (pFile = MI_FS_Fopen((const MI_U8 *) BOOTLOGO_FILE_HEX_PATH,(const MI_U8 *)"rb")))
            {
                DBG_ERROR(("[%s] [%d] MI_FS_Fopen(%s) failed\r\n", __FUNCTION__,__LINE__, BOOTLOGO_FILE_HEX_PATH));
                break;
            }
        }

        // Read data from file
        if ((i4_ret = MI_FS_Fread((void *)g_ps_image_data, 1, 1080*1920*4, pFile)) <= 0)
        {
            DBG_ERROR(("[%s] [%d] MI_FS_Fread failed  i4_ret:%d \r\n", __FUNCTION__,__LINE__, i4_ret));
            MI_FS_Fclose(pFile);
            break;
        }

        if(pFile != NULL)
        {
            MI_FS_Fclose(pFile);
        }

        WGL_IMG_T tg_logo_image = {0};
        tg_logo_image.ui2_width         = 1920;
        tg_logo_image.ui2_lines         = 1080;
        tg_logo_image.ui1_bits_per_pixel= 32;
        tg_logo_image.ui4_image_type    = WGL_IMG_TYPE_8888_ALIGN;
        tg_logo_image.ui2_table_columns = 0;
        tg_logo_image.pt_table_data     = 0;
        tg_logo_image.ui4_image_size    = 1080*1920*4;
        tg_logo_image.pui1_image_data   = g_ps_image_data;

        /* logo */
        if (WGLR_OK != (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,&tg_logo_image,&h_logo_icon)))
        {
            DBG_ERROR(("[%s] [%d] c_wgl_img_tpl_create failed  i4_ret:%d \r\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        /* create logo show icon */
        WDK_ICON_WIDGET_PARAM_T          t_icon_param;
        t_icon_param.h_parent             = st_bootlogo.h_main_frame;
        t_icon_param.ui1_alpha            = 255;
        t_icon_param.b_visibility         = TRUE;
        t_icon_param.i4_x                 = 0;
        t_icon_param.i4_y                 = 0;
        t_icon_param.i4_w                 = 1920;
        t_icon_param.i4_h                 = 1080;
        t_icon_param.ui4_style            = 0;
        t_icon_param.b_img_bk             = FALSE;
        t_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
        t_icon_param.t_img_param.h_disable  = h_logo_icon;
        t_icon_param.t_img_param.h_enable   = h_logo_icon;
        t_icon_param.t_img_param.h_highlight= h_logo_icon;
        t_icon_param.pt_clr_bk            = NULL;
        t_icon_param.pf_wdgt_proc         = NULL;
        t_icon_param.ph_created_icon      = &st_bootlogo.h_logo;

        if (GLR_OK != (i4_ret = a_wdk_create_icon_widget (t_icon_param)) )
        {
            DBG_ERROR(("[%s] [%d] a_wdk_create_icon_widget() i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }
        c_wgl_set_visibility(st_bootlogo.h_main_frame,WGL_SW_HIDE_RECURSIVE);
        DBG_ERROR(("[%s] [%d] init ok!!!!\r\n", __FUNCTION__,__LINE__));

        st_bootlogo.b_is_init = TRUE;
        return APP_CFGR_OK;
    }while(0);

    if (st_bootlogo.h_view != NULL_HANDLE)
    {
        c_gl_view_delete_viewport(st_bootlogo.h_view, st_bootlogo.ui4_viewport);
    }

    if (st_bootlogo.h_surf != NULL_HANDLE)
    {
        c_gl_obj_free(st_bootlogo.h_surf);
    }

    if (st_bootlogo.h_view != NULL_HANDLE)
    {
        c_gl_obj_free(st_bootlogo.h_view);
    }

    if (st_bootlogo.h_plane != NULL_HANDLE)
    {
        c_gl_plane_link(st_bootlogo.h_plane, NULL_HANDLE, TRUE);
        c_gl_obj_free(st_bootlogo.h_plane);
    }

    if (st_bootlogo.h_screen != NULL_HANDLE)
    {
        c_gl_obj_free(st_bootlogo.h_screen);
    }
    if(g_ps_image_data)
    {
        free(g_ps_image_data);
        g_ps_image_data = NULL;
    }
    return APP_CFGR_NOT_INIT;
}

VOID  a_cfg_custom_draw_logo_deinit(VOID)
{
    st_bootlogo.b_is_init = FALSE;
    //UINT32 ui4_ret = 0;

    if(NULL_HANDLE != h_logo_icon)
    {
        ACFG_LOG_ON_FAIL(c_wgl_img_tpl_destroy(h_logo_icon));
        h_logo_icon = NULL_HANDLE;
    }
    if (st_bootlogo.h_logo != NULL_HANDLE)
    {
        ACFG_LOG_ON_FAIL(c_wgl_destroy_widget_ex(st_bootlogo.h_logo,FALSE));
        st_bootlogo.h_logo = NULL_HANDLE;
    }
    if (st_bootlogo.h_main_frame != NULL_HANDLE)
    {
        ACFG_LOG_ON_FAIL(c_wgl_destroy_widget_ex(st_bootlogo.h_main_frame,FALSE));
        st_bootlogo.h_main_frame = NULL_HANDLE;
    }

    if (st_bootlogo.h_view != NULL_HANDLE)
    {
        c_gl_view_delete_viewport(st_bootlogo.h_view, st_bootlogo.ui4_viewport);
        st_bootlogo.h_view = NULL_HANDLE;
    }

    if (st_bootlogo.h_surf != NULL_HANDLE)
    {
        c_gl_obj_free(st_bootlogo.h_surf);
        st_bootlogo.h_surf = NULL_HANDLE;
    }

    if (st_bootlogo.h_view != NULL_HANDLE)
    {
        c_gl_obj_free(st_bootlogo.h_view);
        st_bootlogo.h_view = NULL_HANDLE;
    }


    if (st_bootlogo.h_plane != NULL_HANDLE)
    {
        c_gl_plane_link(st_bootlogo.h_plane, NULL_HANDLE, TRUE);
        ACFG_LOG_ON_FAIL(c_gl_obj_free(st_bootlogo.h_plane));
        st_bootlogo.h_plane = NULL_HANDLE;
    }

    if (st_bootlogo.h_screen != NULL_HANDLE)
    {
        ACFG_LOG_ON_FAIL(c_gl_obj_free(st_bootlogo.h_screen));
        st_bootlogo.h_screen = NULL_HANDLE;
    }

    if(g_ps_image_data != NULL)
    {
       free(g_ps_image_data);
       g_ps_image_data = NULL;
    }

}

INT32 a_cfg_custom_set_black_pattern(BOOL b_on)
{
    VID_TYPE_MOD_PATTERN_T t_info;

    c_memset(&t_info, 0, sizeof(t_info));
    t_info.b_on_off = b_on ;
    a_cfg_cust_drv_set_mod_pattern(&t_info,sizeof(t_info));
    DBG_LOG_PRINT(("[ACFG] SET BLACK PATTERN %s\n",b_on ? "ON" : "OFF"));
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_draw_logo_image(BOOTLOGO_FLAG_T flag)
{
    if(flag == BOOTLOGO_INIT)
    {
        if(0 != a_cfg_custom_draw_logo_init())
        {
            return APP_CFGR_NOT_INIT;
        }
        a_cfg_custom_set_black_pattern(TRUE);
        //disbale zoom mode
        nav_zoom_mode_disable();
    }
    else if(flag == BOOTLOGO_SHOW)
    {
        c_wgl_set_visibility(st_bootlogo.h_main_frame,WGL_SW_RECURSIVE);
        c_wgl_show(st_bootlogo.h_main_frame,WGL_SW_RECURSIVE);
        c_wgl_repaint(st_bootlogo.h_main_frame,NULL,TRUE);
        a_cfg_custom_set_black_pattern(FALSE);
    }
    else if(flag == BOOTLOGO_HIDE)
    {
        c_wgl_set_visibility(st_bootlogo.h_main_frame,WGL_SW_HIDE_RECURSIVE);
        c_wgl_show(st_bootlogo.h_main_frame,WGL_SW_HIDE_RECURSIVE);
    }
    else if(flag == BOOTLOGO_DEINIT)
    {
        c_wgl_repaint(st_bootlogo.h_main_frame,NULL,TRUE);
        a_cfg_custom_draw_logo_deinit();
    }
    c_gl_plane_enable(st_bootlogo.h_plane, TRUE);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_video_description_status(VOID)
{
    UINT16 ui2_lst = 0;
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TYPE), (INT16 *)&ui2_lst);
    AUD_VID_DES_MODE e_mode = 0;
    if(2 == ui2_lst)
    {
        e_mode = 1;
    }
    else
    {
        e_mode = 0;
    }

    return e_mode;
}

INT32 a_cfg_custom_set_video_description_status(UINT16 ui2_idx)
{
    AUD_VID_DES_MODE e_mode = 0;

    if(1 == ui2_idx)
    {
        e_mode = VID_DES_MODE_ON;
    }
    else
    {
        e_mode = AUD_VID_DES_OFF;
    }

    MENU_CHK_FAIL(a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TYPE), (INT16)e_mode));
    MENU_CHK_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TYPE)));

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_aud_lang_vid_des(UINT16 ui2_idx)
{
    UINT16  ui2_tmp_idx = 0;

    if(ui2_idx == 2)
 //span
    {
        ui2_tmp_idx = 1; //set on
    }
    else
    {
        ui2_tmp_idx = 0; // set off
    }

    MENU_CHK_FAIL(a_cfg_custom_set_video_description_status(ui2_tmp_idx));

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_get_aq_version(CHAR i1_num,CHAR aq_ver[])
{
    /*aq config file path*/
    #define AQ_PATH "/config/aq/AQ_ver.txt"

    if (access(AQ_PATH, F_OK) != -1)
    {
        INT32 file_handle = -1;
        INT32 i4_ret_temp = -1;

        file_handle = open(AQ_PATH,O_RDONLY);
        if(file_handle < 0)
        {
            DBG_INFO(("[ACFG] open fail %d\n",file_handle));
        }

        if( i1_num > 31 || i1_num < 0 )
        {
            DBG_INFO(("[+++] {%s %s() %d}. read size!!! 0~31 byte\n",__FILE__, __FUNCTION__, __LINE__));
            close(file_handle);
            return APP_CFGR_OK;
        }
        i4_ret_temp = read(file_handle, aq_ver, 31);
        if(i4_ret_temp <= 0)
        {
            DBG_INFO(("[ACFG] read fail\n"));
        }
        close(file_handle);
    }
    else
    {
        DBG_INFO(("[+++] {%s %s() %d}. check AQ file or path!!!\n",__FILE__, __FUNCTION__, __LINE__));
        aq_ver[0] = '\0';
    }
    return APP_CFGR_OK;
}

SCC_VID_HDMI_DVI_MODE_T a_cfg_custom_get_hdmi_dvi_signal(VOID)
{
    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    HANDLE_T    h_scc_comp = NULL_HANDLE;
    INT32       i4_res = 0;

    /*is dvi singal,return true, or not false*/
    if (a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name)) == APP_CFGR_OK)
    {
        ISL_REC_T  t_isl_rec = {0};
        SCC_VID_HDMI_DVI_MODE_T  e_hdmi_dvi_mode;

        menu_get_crnt_isl(&t_isl_rec);

        if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
            t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
        {
            return SCC_VID_HDMI_DVI_MODE_NO_SIGNAL;
        }

        h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0) ?
                       h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid;

        i4_res = c_scc_vid_get_hdmi_dvi_mode(h_scc_comp, &e_hdmi_dvi_mode);
        if (i4_res != TVR_OK)
        {
            return SCC_VID_HDMI_DVI_MODE_NO_SIGNAL;
        }

        /*
        i4_res = c_scc_vid_get_hdmi_dvi_mode(h_scc_comp, &e_hdmi_dvi_mode);
        if (i4_res != TVR_OK)
        {
            return SCC_VID_HDMI_DVI_MODE_NO_SIGNAL;
        }
        */

#if 0
        DBG_LOG_PRINT(("[overscan +++] {%s() %d}. 0:dvi,1:hdmi,e_hdmi_dvi_mode = hdmi port:%s\n",__FUNCTION__, __LINE__,
            SCC_VID_HDMI_DVI_MODE_DVI == e_hdmi_dvi_mode?"is dvi mode":"is hdmi mode"));
#endif

        return e_hdmi_dvi_mode;
    }

    return SCC_VID_HDMI_DVI_MODE_NO_SIGNAL;
}

INT32 a_cfg_custom_get_pannel_resolution(SCC_DISP_RESOLUTION_T* t_resolution)
{
    INT32                   i4_ret         = APP_CFGR_OK;
    HANDLE_T                h_scc_disp     = NULL_HANDLE;
    SM_COMMAND_T            at_sm_cmds[10] = {0};

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_DISP;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc_disp);
    if(i4_ret != SMR_OK)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = c_scc_disp_get_resolution(h_scc_disp, t_resolution);
    if (i4_ret != SMR_OK)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = c_scc_comp_close(h_scc_disp);
    if (i4_ret != SMR_OK)
    {
        return APP_CFGR_INV_ARG;
    }

    DBG_LOG_PRINT(("[pannel_resolution +++ ] {%s() %d}. t_resolution.ui2_width = %d,t_resolution.ui2_height = %d\n", __FUNCTION__, __LINE__,
        t_resolution->ui2_width,t_resolution->ui2_height));
    return i4_ret;
}
INT32 a_cfg_custom_update_time_zone_data (VOID)
{
    TIME_T      t_tz_offset       = 0;
    UINT8       ui1_time_zone_idx = 0;
    INT32       i4_ret            = APP_CFGR_OK;

    i4_ret = a_cfg_custom_get_timezone_idx(&ui1_time_zone_idx);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    DBG_LOG_PRINT(("[TIME +++ ] {%s %s() %d}. ui1_time_zone_idx = %d\n",__FILE__, __FUNCTION__, __LINE__,ui1_time_zone_idx));
    switch (ui1_time_zone_idx)
    {
        case 0:
            t_tz_offset = -10  * 3600;      /* Hawaii*/
            break;
        case 1:
            t_tz_offset = -9   * 3600;      /* Alaska */
            break;
        case 2:
            t_tz_offset = -8   * 3600;      /* Pacific*/
            break;
        case 3:
            t_tz_offset = -7   * 3600;      /* Mountain*/
            break;
        case 4:
            t_tz_offset = -7   * 3600;      /* Arizona*/
            break;
        case 5:
            t_tz_offset = -6   * 3600;      /* Central*/
            break;
        case 6:
            t_tz_offset = -5   * 3600;      /* Eastern*/
            break;
        case 7:
            t_tz_offset = -4   * 3600;      /* atlantic*/
            break;
        case 8:
            t_tz_offset = -3.5 * 3600;      /* Newfoundland*/
            break;
        case 9:
            t_tz_offset = -3  * 3600;      /* -3 */
           break;
        case 10:
            t_tz_offset = -2  * 3600;      /* -2 */
            break;
        case 11:
            t_tz_offset = -1   * 3600;      /* -1 */
            break;
        case 12:
            t_tz_offset = 0   * 3600;      /* London */
            break;
        case 13:
            t_tz_offset = 1   * 3600;      /* 1 */
            break;
        case 14:
            t_tz_offset = 2   * 3600;      /* 2 */
            break;
        case 15:
            t_tz_offset = 3   * 3600;      /* 3 */
            break;
        case 16:
            t_tz_offset = 4 * 3600;      /* 4 */
            break;
        case 17:
            t_tz_offset = 5   * 3600;      /* 5 */
            break;
        case 18:
            t_tz_offset = 6   * 3600;      /* 6 */
           break;
        case 19:
            t_tz_offset = 7  * 3600;      /* 7 */
           break;
        case 20:
            t_tz_offset = 8  * 3600;      /* 8 */
            break;
        case 21:
            t_tz_offset = 9   * 3600;      /* 9 */
            break;
        case 22:
            t_tz_offset = 10   * 3600;      /* Guam */
            break;
        case 23:
            t_tz_offset = 11   * 3600;      /* 11 */
            break;
        case 24:
            t_tz_offset = 12   * 3600;      /* 12 */
            break;
        case 25:
            t_tz_offset = -12   * 3600;      /* -12 */
            break;
        case 26:
            t_tz_offset = -11   * 3600;      /* -11 */
            break;
        default:
            t_tz_offset = -8   * 3600;      /* Pacific*/
            break;
    }

    //*pt_tz_offset = t_tz_offset;
    i4_ret = a_cfg_set_time_zone_data(t_tz_offset, FALSE);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    DBG_LOG_PRINT(("[TIME +++ ] {%s %s() %d}. ui1_time_zone_idx = %d,t_tz_offset = %lld\n",__FILE__, __FUNCTION__, __LINE__,ui1_time_zone_idx,t_tz_offset));

    return APP_CFGR_OK;
}


INT32 acfg_cust_HDMI_get_ITC_VIC(UINT8 u8Port, StuHdmiItcVicInfo* pstHdmiItcVicInfo)
{
    INT32   i4_ret;

    DBG_LOG_PRINT(("[ACFG][HDMI][ITC]{%s(u8Port:%d)}\n", __FUNCTION__, u8Port ));

    if( u8Port >= 4 )
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][ITC]{%s,%d} Error: Invalid u8Port:%d\n", __FUNCTION__, __LINE__, u8Port ));
        return APP_CFGR_INV_ARG;
    }

    if( (pstHdmiItcVicInfo == NULL) )
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][ITC]{%s,%d} Error: pstHdmiItcVicInfo == NULL \n", __FUNCTION__, __LINE__ ));
        return APP_CFGR_INV_ARG;
    }


    DRV_CUST_OPERATION_INFO_T    t_op_info={0};

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;

    if(0 == u8Port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_ITC_VIC;
    }
    else if(1 == u8Port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_ITC_VIC;
    }
    else if(2 == u8Port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_ITC_VIC;
    }
    else //if(3 == u8Port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_ITC_VIC;
    }

    //DBG_LOG_PRINT(("[NAV][CEC] e_cust_spec_type:0x%X \n", __FUNCTION__, t_op_info.u.t_cust_spec_get_info.e_cust_spec_type ));

#define HDMI_ITC_DATA_BUF_SIZE   6
    UINT8 au8DataBuf[HDMI_ITC_DATA_BUF_SIZE] = {0};
    SIZE_T                       z_size = HDMI_ITC_DATA_BUF_SIZE;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)au8DataBuf;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][ITC]{%s,%d} Error: c_rm_get_comp return error:%d \n", __FUNCTION__, __LINE__, i4_ret ));
        return APP_CFGR_INTERNAL_ERR;
    }

  #if 0
    DBG_LOG_PRINT(("[ACFG][HDMI][ITC] => DataBuf[%d]={ \n", HDMI_ITC_DATA_BUF_SIZE ));
    int i;
    for( i = 0; i < HDMI_ITC_DATA_BUF_SIZE; i += 1 )
    {
        DBG_LOG_PRINT((" DataBuf[%d]:0x%X \n", i, au8DataBuf[i] ));
    }
  #endif

    memset( (void*)pstHdmiItcVicInfo, 0, sizeof(StuHdmiItcVicInfo) );

    pstHdmiItcVicInfo->bAVI_Info_Valid = au8DataBuf[0];
    if( pstHdmiItcVicInfo->bAVI_Info_Valid )
    {
        pstHdmiItcVicInfo->u8ITC = au8DataBuf[1];
        pstHdmiItcVicInfo->u8CN = au8DataBuf[2];
        pstHdmiItcVicInfo->u8AVI_VIC = au8DataBuf[3];
    }

    DBG_LOG_PRINT(("[ACFG][HDMI][ITC] Port(%d) => AVI_Info:%d, ITC:%d, CN:%d, VIC:%d\n",
            u8Port, pstHdmiItcVicInfo->bAVI_Info_Valid, pstHdmiItcVicInfo->u8ITC, pstHdmiItcVicInfo->u8CN, pstHdmiItcVicInfo->u8AVI_VIC ));

    pstHdmiItcVicInfo->bVSIF_Valid = au8DataBuf[4];
    if( pstHdmiItcVicInfo->bVSIF_Valid )
    {
        pstHdmiItcVicInfo->u8VSIF_VIC = au8DataBuf[5];
    }

    DBG_LOG_PRINT(("[ACFG][HDMI][ITC] Port(%d) => VSIF:%d, VIC:%d\n",
            u8Port, pstHdmiItcVicInfo->bVSIF_Valid, pstHdmiItcVicInfo->u8VSIF_VIC ));

    return APP_CFGR_OK;
}

#if(ENABLE_VIZIO_AUTO_PC)

#define DEBUG_AUTO_PC(x)    x

#define AUTO_PC_DEVICE_NAME_SIZE    32

// User answer ...
typedef enum
{
    AUTO_PC_DEVICE_USER_ANSWER_NONE = 0,
    AUTO_PC_DEVICE_USER_ANSWER_YES  = 1,
    AUTO_PC_DEVICE_USER_ANSWER_NO   = 2,

    AUTO_PC_DEVICE_USER_ANSWER_UNKNOWN = 3,
} EnuAutoPcUserAnswer;

typedef struct
{
    UINT32 u32SerialNum; // For find out the old device

    UINT8 u8InUse;

    UINT8 u8RecIdx;

    char acDeviceName[AUTO_PC_DEVICE_NAME_SIZE];
    UINT8 u8UserAnswer; // User answer: 1->Yes; 2->No

    UINT8 u8DeviceFlag_2;
    UINT8 u8DeviceFlag_3;
    UINT8 u8DeviceFlag_4;

} StruAutoPcDeviceInfo;

#define AUTO_PC_DB_VER      100
#define AUTO_PC_DEVICE_NUM  3
typedef struct
{
    UINT32 u32DB_Size;

    UINT32 u32DB_Ver;

    UINT32 u32LastSerialNum;

    StruAutoPcDeviceInfo astDeviceInfo[AUTO_PC_DEVICE_NUM];

    //UINT8 au8Reserve[64];

    UINT32 u32CRC;
} StruAutoPcDB;

#define AUTO_PC_HDMI_PORT_NUM   4
static StruAutoPcDB g_astAutoPcDB[AUTO_PC_HDMI_PORT_NUM] = {0}; // size=>136Bytes


static UINT8 s_AutoPC_u8CurHdmiIdx = 0;
static char s_AutoPC_au8CurDeviceName[AUTO_PC_DEVICE_NAME_SIZE] = {0};

//StruAutoPcDeviceInfo* g_AutoPC_pstCurDeviceInfo = NULL;

typedef enum
{
    AUTO_PC_STATE_NONE,
    AUTO_PC_STATE_STOP,
    AUTO_PC_STATE_START,
    AUTO_PC_STATE_WAIT_POP_MENU,
    AUTO_PC_STATE_WAIT_USER_ANSWER,

} EnuAutoPcState;

static EnuAutoPcState s_AutoPC_eState = AUTO_PC_STATE_NONE;

#define DEBUG_AUTO_PC_DB(x)  x

static void _acfg_cust_AutoPc_PrintDB(StruAutoPcDB * pstAutoPcDB)
{
    DBG_LOG_PRINT( ("[AutoPc DB] %s()\n", __FUNCTION__ ) );

    //DBG_LOG_PRINT(("[AutoPC DB] sizeof(StruAutoPcDB):%d \n", sizeof(StruAutoPcDB) ));
    //StruAutoPcDB * pstAutoPcDB = &(g_astAutoPcDB[u8HdmiIdx]);

    DBG_LOG_PRINT( ("[AutoPc DB]  u32DB_Size:%d, Ver:%d\n",
        pstAutoPcDB->u32DB_Size, pstAutoPcDB->u32DB_Ver ) );
    //DBG_LOG_PRINT( ("[AutoPc DB] Ver:%d\n", pstAutoPcDB->u32DB_Ver ) );
    DBG_LOG_PRINT( ("[AutoPc DB]  u32LastSerialNum:%d, u32CRC:0x%X\n",
        pstAutoPcDB->u32LastSerialNum, pstAutoPcDB->u32CRC ) );
    //DBG_LOG_PRINT( ("[AutoPc DB] u32CRC:0x%X\n", pstAutoPcDB->u32CRC ) );

    int iDeviceIdx;
    const StruAutoPcDeviceInfo* pstDeviceInfo;

    for( iDeviceIdx = 0; iDeviceIdx < AUTO_PC_DEVICE_NUM; iDeviceIdx += 1)
    {
        //pstDeviceInfo = &(pstAutoPcDB[iHdmiIdx].astDeviceInfo[iDeviceIdx]);
        pstDeviceInfo = &(pstAutoPcDB->astDeviceInfo[iDeviceIdx]);

        if( pstDeviceInfo->u8InUse )
        {
            DBG_LOG_PRINT( ("[AutoPc DB]  iDevice(%d): RecId:%d, Name:{%s} Ans:%d, SN:%d\n",
                    iDeviceIdx, pstDeviceInfo->u8RecIdx,
                    pstDeviceInfo->acDeviceName, pstDeviceInfo->u8UserAnswer,
                    pstDeviceInfo->u32SerialNum ) );
        }
        else
        {
            DBG_LOG_PRINT( ("[AutoPc DB]  iDevice(%d): No Use\n", iDeviceIdx ) );
        }
    }
    DBG_LOG_PRINT( ("\n" ) );

}

static void _acfg_cust_AutoPc_PrintDB_by_HDMI_idx(UINT8 u8HdmiIdx)
{
    DBG_LOG_PRINT( ("[AutoPc DB] %s(u8HdmiIdx:%d)\n", __FUNCTION__, u8HdmiIdx ) );

    StruAutoPcDB * pstAutoPcDB = &(g_astAutoPcDB[u8HdmiIdx]);

    _acfg_cust_AutoPc_PrintDB(pstAutoPcDB);
}

static void _acfg_cust_AutoPc_PrintDB_all(void)
{
    DBG_LOG_PRINT(("[AutoPc DB](%s)\n", __FUNCTION__ ) );

    DBG_LOG_PRINT(("[AutoPC DB] sizeof(StruAutoPcDB):%ld \n", sizeof(StruAutoPcDB) ));

    //DBG_LOG_PRINT( ("[AutoPc DB] Ver:%d\n", pstAutoPcDB->u32DB_Ver ) );

    int iHdmiIdx;

    for( iHdmiIdx = 0; iHdmiIdx < AUTO_PC_HDMI_PORT_NUM; iHdmiIdx += 1)
    {
        _acfg_cust_AutoPc_PrintDB_by_HDMI_idx(iHdmiIdx);

        //DBG_LOG_PRINT(("[AutoPc DB] HDMI_%d:\n", iHdmiIdx ) );
        //StruAutoPcDB * pstAutoPcDB = &(g_astAutoPcDB[iHdmiIdx]);
        //_acfg_cust_AutoPc_PrintDB(pstAutoPcDB);
    }
}

static UINT32 _acfg_cust_AutoPc_DB_CalCRC(const UINT8* pu8Data, UINT32 u32DataSize)
{
#if 0
    return mapi_DB_CalCRC(pu8Data, u32DataSize);
#else
    UINT32 u32CRC = 0x12345678;

    UINT32 i = 0;
    for( i = 0; i < u32DataSize; i += 1 )
    {
        u32CRC = u32CRC + (pu8Data[i]);
    }

    return u32CRC;
#endif
}

#define AUTO_PC_DB_FILE "/data/auto_pc_%d_%d.db"

static StruAutoPcDB _s_stAutoPcDb_tmp_1 = {0};
static StruAutoPcDB _s_stAutoPcDb_tmp_2 = {0};

static UINT8 _s_AutoPcDb_au8CurDbSel[AUTO_PC_HDMI_PORT_NUM] = {0};

static BOOL _s_AutoPcDb_inited = 0;


#define DEBUG_AUTO_PC_DB_SAVE(x)    // x
static BOOL _acfg_cust_AutoPc_DB_save(UINT8 u8HdmiIdx, UINT8 u8DB_sel, StruAutoPcDB* pstAutoPcDB)
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d, u8DB_sel:%d) \n", __FUNCTION__, u8HdmiIdx, u8DB_sel )); );

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d ! \n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }

    if( u8DB_sel >= 2 )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8DB_sel:%d ! \n", __FUNCTION__,__LINE__, u8DB_sel ));
        return FALSE;
    }

    pstAutoPcDB->u32DB_Size = sizeof(StruAutoPcDB);
    pstAutoPcDB->u32DB_Ver = AUTO_PC_DB_VER;
    //pstAutoPcDB->u32LastSerialNum += 1;

    pstAutoPcDB->u32CRC = _acfg_cust_AutoPc_DB_CalCRC( (UINT8*)pstAutoPcDB, sizeof(StruAutoPcDB)-4 );
    DEBUG_AUTO_PC_DB_SAVE( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, CRC:0x%X \n", u8HdmiIdx, pstAutoPcDB->u32CRC )); );

    char ac_DB_FileName[64] = {0};
    sprintf( ac_DB_FileName, AUTO_PC_DB_FILE, u8HdmiIdx, u8DB_sel );
    DEBUG_AUTO_PC_DB_SAVE( DBG_LOG_PRINT(("[AutoPC DB] Save file: %s \n", ac_DB_FileName )); );

    DEBUG_AUTO_PC_DB_SAVE( DBG_LOG_PRINT(("[AutoPC DB] open file: %s \n", ac_DB_FileName )); );
    FILE* pf_auto_pc_db = fopen(ac_DB_FileName, "wb");
    if( pf_auto_pc_db == NULL )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Open file fail! %s \n", __FUNCTION__,__LINE__, ac_DB_FileName ));
        return FALSE;
    }

    DEBUG_AUTO_PC_DB_SAVE( DBG_LOG_PRINT( ("[AutoPC DB] Write data %ld bytes.(sizeof(StruAutoPcDB))\n", sizeof(StruAutoPcDB) ) ); );
    int i_rtn = fwrite( (UINT8*)pstAutoPcDB, sizeof(StruAutoPcDB), 1, pf_auto_pc_db );
    if( i_rtn != 1 )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: fwrite fail! i_rtn:%d, u8HdmiIdx:%d, file:%s\n",
            __FUNCTION__,__LINE__, i_rtn, u8HdmiIdx, ac_DB_FileName ));
        fclose(pf_auto_pc_db);
        return FALSE;
    }

    fclose(pf_auto_pc_db);

    return TRUE;
}

static BOOL _acfg_cust_AutoPc_DB_save_auto_sel_DB(UINT8 u8HdmiIdx, StruAutoPcDB* pstAutoPcDB)
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d) \n", __FUNCTION__, u8HdmiIdx )); );

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d ! \n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }

    UINT8 u8DB_sel = 0;

    if( _s_AutoPcDb_au8CurDbSel[u8HdmiIdx] == 0 )
        u8DB_sel = 1;
    else
        u8DB_sel = 0;
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, auto DB_sel:%d \n", u8HdmiIdx, u8DB_sel )); );

    BOOL b_save_rtn = _acfg_cust_AutoPc_DB_save(u8HdmiIdx, u8DB_sel, pstAutoPcDB);

    if( b_save_rtn )
    {
        // update DB sel
        _s_AutoPcDb_au8CurDbSel[u8HdmiIdx] = u8DB_sel;
        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] Set _s_AutoPcDb_au8CurDbSel[%d]=%d\n", u8HdmiIdx, _s_AutoPcDb_au8CurDbSel[u8HdmiIdx] )); );

        //system("sync");
    }

    return b_save_rtn;
}

static BOOL _acfg_cust_AutoPc_DB_reset_file(UINT8 u8HdmiIdx, UINT8 u8DB_sel)
{
    //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s(u8HdmiIdx:%d, u8DB_sel:%d) \n", __FUNCTION__, u8HdmiIdx, u8DB_sel )); );
    DBG_LOG_PRINT(("[AutoPC DB] %s(u8HdmiIdx:%d, u8DB_sel:%d) \n", __FUNCTION__, u8HdmiIdx, u8DB_sel ));

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d !\n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }

    StruAutoPcDB stAutoPcDb_tmp = {0};

    return _acfg_cust_AutoPc_DB_save( u8HdmiIdx, u8DB_sel, &stAutoPcDb_tmp);
}

static BOOL _acfg_cust_AutoPc_DB_reset(UINT8 u8HdmiIdx)
{
    //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s(u8HdmiIdx:%d) \n", __FUNCTION__, u8HdmiIdx )); );
    DBG_LOG_PRINT(("[AutoPC DB] %s(u8HdmiIdx:%d) \n", __FUNCTION__, u8HdmiIdx ));

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d !\n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }

    c_memset( (UINT8*)&(g_astAutoPcDB[u8HdmiIdx]), 0, sizeof(StruAutoPcDB) );
    g_astAutoPcDB[u8HdmiIdx].u32DB_Ver = AUTO_PC_DB_VER;
    g_astAutoPcDB[u8HdmiIdx].u32DB_Size = sizeof(StruAutoPcDB);

    _acfg_cust_AutoPc_DB_reset_file(u8HdmiIdx, 0);
    _acfg_cust_AutoPc_DB_reset_file(u8HdmiIdx, 1);

    return TRUE;
}

#define DEBUG_AUTO_PC_DB_LOAD(x)    // x
static BOOL _acfg_cust_AutoPc_DB_load(UINT8 u8HdmiIdx, UINT8 u8DB_sel, StruAutoPcDB* pstAutoPcDB)
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d, u8DB_sel:%d) \n",
        __FUNCTION__, u8HdmiIdx, u8DB_sel )); );

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d ! \n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }


    char ac_DB_FileName[64] = {0};
    sprintf( ac_DB_FileName, AUTO_PC_DB_FILE, u8HdmiIdx, u8DB_sel );
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] Load file: %s \n", ac_DB_FileName )); );

    FILE* pfDB = fopen(ac_DB_FileName, "rb");
    if( NULL == pfDB )
    {
        DBG_LOG_PRINT( ("[AutoPC DB]{%s,%d} Error: Open file(%s) failed!\n", __FUNCTION__, __LINE__, ac_DB_FileName) );
        return FALSE;
    }

    StruAutoPcDB stAutoPcDB_tmp = {0};

    DEBUG_AUTO_PC_DB_LOAD( DBG_LOG_PRINT( ("[AutoPC DB] Read %d bytes\n", (unsigned int)sizeof(StruAutoPcDB)) ); );
    int i_fread_rtn = fread( &stAutoPcDB_tmp, sizeof(StruAutoPcDB), 1, pfDB );
    fclose(pfDB);
    //DBG_LOG_PRINT( ("[AutoPC DB] => i_fread_rtn:%d\n", i_fread_rtn ) );
    if( i_fread_rtn != 1 )
    {
        DBG_LOG_PRINT( ("[AutoPC DB]{%s,%d} Error: fread(%s) failed! i_fread_rtn:%d\n",
                __FUNCTION__, __LINE__, ac_DB_FileName, i_fread_rtn ) );
        return FALSE;
    }


    // Check more ...
    DEBUG_AUTO_PC_DB_LOAD( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, u32DB_Size:%d \n",
        u8HdmiIdx, stAutoPcDB_tmp.u32DB_Size )); );
    if( stAutoPcDB_tmp.u32DB_Size != sizeof(StruAutoPcDB) )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Data wrong! u8HdmiIdx:%d, u32DB_Size:%d != %ld \n",
            __FUNCTION__,__LINE__, u8HdmiIdx, stAutoPcDB_tmp.u32DB_Size, sizeof(StruAutoPcDB) ));
        return FALSE;
    }

    DEBUG_AUTO_PC_DB_LOAD( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, u32DB_Ver:%d \n",
        u8HdmiIdx, stAutoPcDB_tmp.u32DB_Ver )); );
    if( stAutoPcDB_tmp.u32DB_Ver != AUTO_PC_DB_VER )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Data wrong! u8HdmiIdx:%d, u32DB_Ver:%d != %d \n",
            __FUNCTION__,__LINE__, u8HdmiIdx, stAutoPcDB_tmp.u32DB_Ver, AUTO_PC_DB_VER ));
        return FALSE;
    }

    UINT32 u32CurDataCRC = _acfg_cust_AutoPc_DB_CalCRC( (UINT8*)&stAutoPcDB_tmp, sizeof(StruAutoPcDB)-4 );
    DEBUG_AUTO_PC_DB_LOAD( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, u32CurDataCRC:0x%X \n", u8HdmiIdx, u32CurDataCRC )); );
    if( stAutoPcDB_tmp.u32CRC != u32CurDataCRC )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Data wrong! u8HdmiIdx:%d, u32CRC:0x%X != 0x%X \n",
            __FUNCTION__,__LINE__, u8HdmiIdx, stAutoPcDB_tmp.u32CRC, u32CurDataCRC ));
        return FALSE;
    }

    *pstAutoPcDB = stAutoPcDB_tmp;

    return TRUE;
}

static BOOL _acfg_cust_AutoPc_DB_init(void)
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s() \n", __FUNCTION__ )); );

    int iHdmiIdx;

    for( iHdmiIdx = 0; iHdmiIdx < AUTO_PC_HDMI_PORT_NUM; iHdmiIdx += 1 )
    {
        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] {%s,%d} iHdmiIdx:%d, Load files\n",
            __FUNCTION__, __LINE__, iHdmiIdx )); );

        c_memset( (UINT8*)&_s_stAutoPcDb_tmp_1, 0, sizeof(StruAutoPcDB) );
        int i_rtn_1 = _acfg_cust_AutoPc_DB_load( iHdmiIdx, 0, &(_s_stAutoPcDb_tmp_1) );
      #if 1
        if(i_rtn_1)
        {
            DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] {%s,%d} iHdmiIdx:%d, DB_0...\n",
                __FUNCTION__, __LINE__, iHdmiIdx )); );
            _acfg_cust_AutoPc_PrintDB(&_s_stAutoPcDb_tmp_1);
        }
      #endif

        c_memset( (UINT8*)&_s_stAutoPcDb_tmp_2, 0, sizeof(StruAutoPcDB) );
        int i_rtn_2 = _acfg_cust_AutoPc_DB_load( iHdmiIdx, 1, &(_s_stAutoPcDb_tmp_2) );
      #if 1
        if(i_rtn_2)
        {
            DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] {%s,%d} iHdmiIdx:%d, DB_1...\n",
                __FUNCTION__, __LINE__, iHdmiIdx )); );
            _acfg_cust_AutoPc_PrintDB(&_s_stAutoPcDb_tmp_2);
        }
      #endif

        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] {%s,%d} iHdmiIdx:%d, i_rtn_1:%d, i_rtn_2:%d \n",
            __FUNCTION__, __LINE__, iHdmiIdx, i_rtn_1, i_rtn_2 )); );

        UINT8 u8DB_Sel;

        if( i_rtn_1 ) // 1 OK
        {
            if( i_rtn_2 ) // 1 OK & 2 OK
            {
                if( _s_stAutoPcDb_tmp_1.u32LastSerialNum > _s_stAutoPcDb_tmp_2.u32LastSerialNum )
                {
                    // Use DB_0
                    u8DB_Sel = 0;
                    g_astAutoPcDB[iHdmiIdx] = _s_stAutoPcDb_tmp_1;
                }
                else
                {
                    // Use DB_1
                    u8DB_Sel = 1;
                    g_astAutoPcDB[iHdmiIdx] = _s_stAutoPcDb_tmp_2;
                }
            }
            else // 1 OK & 2 NG
            {
                u8DB_Sel = 0;
                g_astAutoPcDB[iHdmiIdx] = _s_stAutoPcDb_tmp_1;
            }
        }
        else // 1 NG
        {
            if( i_rtn_2 ) // 1 NG && 2 OK
            {
                u8DB_Sel = 1;
                g_astAutoPcDB[iHdmiIdx] = _s_stAutoPcDb_tmp_2;
            }
            else // 1 NG && 2 NG
            {
                // Create new ...
                u8DB_Sel = 0;
                g_astAutoPcDB[iHdmiIdx].u32DB_Ver = AUTO_PC_DB_VER;
                g_astAutoPcDB[iHdmiIdx].u32DB_Size = sizeof(StruAutoPcDB);
                g_astAutoPcDB[iHdmiIdx].u32LastSerialNum = 0;
                g_astAutoPcDB[iHdmiIdx].u32CRC =
                    _acfg_cust_AutoPc_DB_CalCRC( (UINT8*)&(g_astAutoPcDB[iHdmiIdx]), sizeof(StruAutoPcDB)-4 );

                DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} call _acfg_cust_AutoPc_DB_save(u8HdmiIdx:%d,u8DB_Sel:%d)\n",
                    __FUNCTION__, __LINE__, iHdmiIdx, u8DB_Sel )); );

                BOOL b_save_rtn = _acfg_cust_AutoPc_DB_save(iHdmiIdx, u8DB_Sel, &(g_astAutoPcDB[iHdmiIdx]) );
                if( b_save_rtn != TRUE )
                {
                    DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: _acfg_cust_AutoPc_DB_save(u8HdmiIdx:%d,u8DB_Sel:%d) fail!!!!\n",
                        __FUNCTION__,__LINE__, iHdmiIdx, u8DB_Sel ));
                    return FALSE;
                }
            }
        }

        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] {%s,%d} iHdmiIdx:%d, => u8DB_Sel:%d\n",
            __FUNCTION__, __LINE__, iHdmiIdx, u8DB_Sel )); );
        _s_AutoPcDb_au8CurDbSel[iHdmiIdx] = u8DB_Sel;

        _acfg_cust_AutoPc_PrintDB_by_HDMI_idx(iHdmiIdx);

        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB]---------------------------------------\n" )); );

    }

    _s_AutoPcDb_inited = 1;

    return TRUE;
}

static StruAutoPcDeviceInfo* _acfg_cust_AutoPC_DB_get_device_info( UINT8 u8HdmiIdx, char* pcDeviceName )
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d, Name:%s) \n", __FUNCTION__, u8HdmiIdx, pcDeviceName )); );

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d ! \n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return NULL;
    }

    int iDeviceIdx;
    StruAutoPcDeviceInfo* pstDeviceInfo;

    BOOL bFound = FALSE;
    StruAutoPcDeviceInfo* pstDeviceInfo_return = NULL;

    for( iDeviceIdx = 0; iDeviceIdx < AUTO_PC_DEVICE_NUM; iDeviceIdx += 1 )
    {
        pstDeviceInfo = &(g_astAutoPcDB[u8HdmiIdx].astDeviceInfo[iDeviceIdx]);

        //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] DevIdx:%d, u8InUse:%d \n", iDeviceIdx, pstDeviceInfo->u8InUse )); );
        if( pstDeviceInfo->u8InUse )
        {
            DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] DevIdx:%d, Name:%s, Ans:%d, SN:%d \n",
                iDeviceIdx, pstDeviceInfo->acDeviceName, pstDeviceInfo->u8UserAnswer, pstDeviceInfo->u32SerialNum)); );

            if( c_strncmp( pcDeviceName, pstDeviceInfo->acDeviceName, AUTO_PC_DEVICE_NAME_SIZE) == 0 )
            {
                bFound = TRUE;
                pstDeviceInfo_return = pstDeviceInfo;
                DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] ==> Found DevIdx:%d\n", iDeviceIdx )); );
                //return pstDeviceInfo;
                break;
            }
            else
            {
                //
                //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] ==> Not found\n")); );
            }
        }
        else
        {

        }

    }

    if( bFound )
    {
        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, %s ==> found \n", u8HdmiIdx, pcDeviceName )); );
        return pstDeviceInfo_return;
    }
    else
    {
        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] u8HdmiIdx:%d, %s ==> not found \n", u8HdmiIdx, pcDeviceName )); );
        return NULL;
    }
}

#define DEBUG_AUTO_PC_DB_ADD_DEV(x) // x
static StruAutoPcDeviceInfo* _acfg_cust_AutoPC_DB_add_device_info( UINT8 u8HdmiIdx, StruAutoPcDeviceInfo* pstNewDeviceInfo )
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d,) Name:{%s} Ans:%d \n", __FUNCTION__,
                u8HdmiIdx, pstNewDeviceInfo->acDeviceName, pstNewDeviceInfo->u8UserAnswer )); );

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d ! \n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return NULL;
    }

    //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d,) Name:{%s} Ans:%d \n", __FUNCTION__, u8HdmiIdx, pstDeviceInfo->pcDeviceName )); );

    int iDeviceIdx;
    StruAutoPcDeviceInfo* pstDeviceInfo;

    int iDeviceIdx_empty = -1;

    UINT32 u32SN_min = 0xFFFFFFFF;
    int iSmallSNDeviceIdx = -1;


    // Find empty DevInfo or smallest one
    for( iDeviceIdx = 0; iDeviceIdx < AUTO_PC_DEVICE_NUM; iDeviceIdx += 1 )
    {
        pstDeviceInfo = &(g_astAutoPcDB[u8HdmiIdx].astDeviceInfo[iDeviceIdx]);

        //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] DevIdx:%d, u8InUse:%d \n", iDeviceIdx, pstDeviceInfo->u8InUse )); );
        if( pstDeviceInfo->u8InUse )
        {
            DEBUG_AUTO_PC_DB_ADD_DEV( DBG_LOG_PRINT(("[AutoPC DB] DevIdx:%d, Used, pstDeviceInfo->u32SerialNum:%d, u32SN_min:%d \n",
                iDeviceIdx, pstDeviceInfo->u32SerialNum, u32SN_min)); );
            if( (pstDeviceInfo->u32SerialNum < u32SN_min)
              ||(u32SN_min == 0xFFFFFFFF)
              )
            {
                DEBUG_AUTO_PC_DB_ADD_DEV( DBG_LOG_PRINT(("[AutoPC DB] DevIdx:%d, Small SN found => %d -> %d \n", iDeviceIdx, u32SN_min, pstDeviceInfo->u32SerialNum )); );
                u32SN_min = pstDeviceInfo->u32SerialNum;
                iSmallSNDeviceIdx = iDeviceIdx;
            }
        }
        else
        {
            DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB]{%s} Empty found => DevIdx:%d \n", __FUNCTION__, iDeviceIdx )); );
            iDeviceIdx_empty = iDeviceIdx;
            break;
        }

    }

    if( iDeviceIdx_empty != -1 )
    {
        pstDeviceInfo = &(g_astAutoPcDB[u8HdmiIdx].astDeviceInfo[iDeviceIdx_empty]);
        pstDeviceInfo->u8InUse = TRUE;
        pstDeviceInfo->u8RecIdx = iDeviceIdx_empty;

        c_strncpy(pstDeviceInfo->acDeviceName, pstNewDeviceInfo->acDeviceName, AUTO_PC_DEVICE_NAME_SIZE );

        pstDeviceInfo->u8UserAnswer = pstNewDeviceInfo->u8UserAnswer;

        if( pstNewDeviceInfo->u32SerialNum )
        {
            pstDeviceInfo->u32SerialNum = pstNewDeviceInfo->u32SerialNum;
        }
        else
        {
            g_astAutoPcDB[u8HdmiIdx].u32LastSerialNum += 1;
            pstDeviceInfo->u32SerialNum = g_astAutoPcDB[u8HdmiIdx].u32LastSerialNum;
        }

        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] Add new devInfo => u8HdmiIdx:%d, Dev:%d, Name:%s, Ans:%d, SN:%d\n",
            u8HdmiIdx, iDeviceIdx_empty,
            pstDeviceInfo->acDeviceName, pstDeviceInfo->u8UserAnswer,
            pstDeviceInfo->u32SerialNum)); );

        return pstDeviceInfo;
    }
    else if( iSmallSNDeviceIdx != -1 )
    {
        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] Small SN found => Dev:%d, SN:%d \n", iSmallSNDeviceIdx, u32SN_min )); );

        pstDeviceInfo = &(g_astAutoPcDB[u8HdmiIdx].astDeviceInfo[iSmallSNDeviceIdx]);

        c_strncpy(pstDeviceInfo->acDeviceName, pstNewDeviceInfo->acDeviceName, AUTO_PC_DEVICE_NAME_SIZE );
        pstDeviceInfo->u8UserAnswer = pstNewDeviceInfo->u8UserAnswer;

        if( pstNewDeviceInfo->u32SerialNum )
        {
            pstDeviceInfo->u32SerialNum = pstNewDeviceInfo->u32SerialNum;
        }
        else
        {
            g_astAutoPcDB[u8HdmiIdx].u32LastSerialNum += 1;
            pstDeviceInfo->u32SerialNum = g_astAutoPcDB[u8HdmiIdx].u32LastSerialNum;
        }

        DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] a device modified => u8HdmiIdx:%d, Dev:%d, Name:%s, Ans:%d\n",
            u8HdmiIdx, iSmallSNDeviceIdx, pstDeviceInfo->acDeviceName, pstDeviceInfo->u8UserAnswer )); );

        return pstDeviceInfo;
    }

    return NULL;
}

static EnuAutoPcUserAnswer _acfg_cust_AutoPC_DB_get_user_answer( UINT8 u8HdmiIdx, char* pcDeviceName )
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d, Name:%s) \n", __FUNCTION__, u8HdmiIdx, pcDeviceName )); );

    //DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] sizeof(StruAutoPcDB):%d \n", sizeof(StruAutoPcDB) )); );

    StruAutoPcDeviceInfo* pstDeviceInfo = _acfg_cust_AutoPC_DB_get_device_info( u8HdmiIdx, pcDeviceName );
    if( pstDeviceInfo == NULL )
    {
        //DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] %s( u8HdmiIdx:%d, %s) \n", __FUNCTION__, u8HdmiIdx, pcDeviceName )); );
        return AUTO_PC_DEVICE_USER_ANSWER_NONE;
    }

    if( pstDeviceInfo->u8UserAnswer >= AUTO_PC_DEVICE_USER_ANSWER_UNKNOWN )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8UserAnswer:%d !! Set to NONE~\n", __FUNCTION__,__LINE__, pstDeviceInfo->u8UserAnswer ));
        pstDeviceInfo->u8UserAnswer = AUTO_PC_DEVICE_USER_ANSWER_NONE;
        return AUTO_PC_DEVICE_USER_ANSWER_NONE;
    }

    return (EnuAutoPcUserAnswer)pstDeviceInfo->u8UserAnswer;
}

static BOOL _acfg_cust_AutoPC_DB_set_user_answer( UINT8 u8HdmiIdx, char* pcDeviceName, EnuAutoPcUserAnswer eUserAnswer )
{
    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] %s( u8HdmiIdx:%d, Name:%s, eUserAnswer:%d) \n", __FUNCTION__, u8HdmiIdx, pcDeviceName, eUserAnswer )); );

    if( u8HdmiIdx >= AUTO_PC_HDMI_PORT_NUM )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: Invalid u8HdmiIdx:%d ! \n", __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }

    DEBUG_AUTO_PC_DB( _acfg_cust_AutoPc_PrintDB_by_HDMI_idx(u8HdmiIdx); );

    DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] Find device: u8HdmiIdx:%d, pcDeviceName:{%s}\n", u8HdmiIdx, pcDeviceName )); );
    StruAutoPcDeviceInfo* pstDeviceInfo = _acfg_cust_AutoPC_DB_get_device_info( u8HdmiIdx, pcDeviceName );
    if( pstDeviceInfo != NULL )
    {
        // Exist => Modify device
        if( pstDeviceInfo->u8UserAnswer == eUserAnswer )
        {
            DBG_LOG_PRINT(("[AutoPC DB] => Setting is the same, => skip!!\n" ));
            return TRUE;
        }
        else
        {
            pstDeviceInfo->u8UserAnswer = eUserAnswer;
            g_astAutoPcDB[u8HdmiIdx].u32LastSerialNum += 1;
            pstDeviceInfo->u32SerialNum = g_astAutoPcDB[u8HdmiIdx].u32LastSerialNum;
            DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] => Modify exist device: SN:%d\n", pstDeviceInfo->u32SerialNum )); );
        }
    }
    else
    {
        // Not exist => Add new device
        StruAutoPcDeviceInfo stNewDeviceInfo = {0};

        c_strncpy(stNewDeviceInfo.acDeviceName, pcDeviceName, AUTO_PC_DEVICE_NAME_SIZE );
        stNewDeviceInfo.u8UserAnswer = eUserAnswer;

        StruAutoPcDeviceInfo* pstDeviceInfo = _acfg_cust_AutoPC_DB_add_device_info( u8HdmiIdx, &stNewDeviceInfo );
        if( pstDeviceInfo == NULL )
        {
            DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: _acfg_cust_AutoPC_DB_add_device_info(HDMI:%d) fail !\n",
                __FUNCTION__,__LINE__, u8HdmiIdx ));
            return FALSE;
        }
        else
        {
            DEBUG_AUTO_PC_DB( DBG_LOG_PRINT(("[AutoPC DB] => Device added: SN:%d\n", pstDeviceInfo->u32SerialNum )); );
        }
    }

    DEBUG_AUTO_PC_DB( _acfg_cust_AutoPc_PrintDB_by_HDMI_idx(u8HdmiIdx); );

    BOOL b_save_rtn = _acfg_cust_AutoPc_DB_save_auto_sel_DB(u8HdmiIdx, &(g_astAutoPcDB[u8HdmiIdx]) );
    if( b_save_rtn != TRUE )
    {
        DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} Error: _acfg_cust_AutoPc_DB_save_auto_sel_DB(u8HdmiIdx:%d) fail!!!!\n",
            __FUNCTION__,__LINE__, u8HdmiIdx ));
        return FALSE;
    }

    DBG_LOG_PRINT(("[AutoPC DB]{%s,%d} call system(sync)\n", __FUNCTION__,__LINE__ ));
    AP_SYSTEM_CALL("sync");//system("sync");

    return TRUE;
}

static BOOL _acfg_cust_AutoPC_set_GLL_on(void)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    // Get current GLL setting...
    INT16 i16CurGLL = 0;
    INT32 i32_rtn = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i16CurGLL);
    if(i32_rtn != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Cannot get GLL!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i32_rtn));
        return FALSE;
    }
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} i16CurGLL:%d\n",__FUNCTION__,__LINE__, i16CurGLL )); );

    // If GLL is on, exit
    if( i16CurGLL == ACFG_CUST_GAME_LOW_LATENCY_ON )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} GLL already On~\n",__FUNCTION__,__LINE__ )); );
        return TRUE;
    }

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Set GLL to On\n",__FUNCTION__,__LINE__ )); );
    i32_rtn = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), (INT16)ACFG_CUST_GAME_LOW_LATENCY_ON);
    if(i32_rtn != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Set GLL fail!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i32_rtn));
        return FALSE;
    }

    acfg_cust_video_update_GLL_all(TRUE);

    //a_acfg_update_gaming_logo();

    return TRUE;
}

static VOID _acfg_cust_AutoPC_handle_user_answer(VOID* pv_data, SIZE_T z_data_len)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s(z_data_len:%ld)} PID:%d, TID:%d \n",
                     __FUNCTION__, z_data_len, getpid(), MApi_Sys_get_thread_id() )); );

    if( s_AutoPC_eState != AUTO_PC_STATE_WAIT_USER_ANSWER )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: s_AutoPC_eState != AUTO_PC_STATE_WAIT_USER_ANSWER!! \n", __FUNCTION__,__LINE__ ));
        return;
    }

    if( pv_data == NULL )
    {
        return;
    }

    UINT8 u8UserAnswer = ((UINT8*)pv_data)[0];

    if( (u8UserAnswer >= AUTO_PC_DEVICE_USER_ANSWER_UNKNOWN)
      ||(u8UserAnswer == AUTO_PC_DEVICE_USER_ANSWER_NONE)
    )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Invalid u8UserAnswer:%d \n", __FUNCTION__,__LINE__, u8UserAnswer ));
        return;
    }

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] u8UserAnswer=%d => s_AutoPC_au8CurDeviceName[]:{%s} \n",
        u8UserAnswer, s_AutoPC_au8CurDeviceName )); );
    _acfg_cust_AutoPC_DB_set_user_answer( s_AutoPC_u8CurHdmiIdx, s_AutoPC_au8CurDeviceName, (EnuAutoPcUserAnswer)u8UserAnswer );

    if( u8UserAnswer == AUTO_PC_DEVICE_USER_ANSWER_YES )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Set GLL to ON \n", __FUNCTION__,__LINE__ ));
        _acfg_cust_AutoPC_set_GLL_on();
    }

}

static VOID _acfg_cust_AutoPC_menu_answer_no(VOID)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} PID:%d, TID:%d \n",
                    __FUNCTION__, __LINE__, getpid(), MApi_Sys_get_thread_id() )); );

    nav_dialog_hide();

    if( s_AutoPC_eState != AUTO_PC_STATE_WAIT_USER_ANSWER )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: s_AutoPC_eState != AUTO_PC_STATE_WAIT_USER_ANSWER!! \n", __FUNCTION__,__LINE__ ));
        return;
    }

    //s_AutoPC_eState = AUTO_PC_STATE_STOP;

    UINT8 u8Data = AUTO_PC_DEVICE_USER_ANSWER_NO;

    a_cfg_async_invoke( _acfg_cust_AutoPC_handle_user_answer, &u8Data, 1 );
}

static VOID _acfg_cust_AutoPC_menu_answer_yes(VOID)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} PID:%d, TID:%d \n",
                    __FUNCTION__, __LINE__, getpid(), MApi_Sys_get_thread_id() )); );

    nav_dialog_hide();

    if( s_AutoPC_eState != AUTO_PC_STATE_WAIT_USER_ANSWER )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: s_AutoPC_eState != AUTO_PC_STATE_WAIT_USER_ANSWER!! \n", __FUNCTION__,__LINE__ ));
        return;
    }

    //s_AutoPC_eState = AUTO_PC_STATE_STOP;

    UINT8 u8Data = AUTO_PC_DEVICE_USER_ANSWER_YES;

    a_cfg_async_invoke( _acfg_cust_AutoPC_handle_user_answer, &u8Data, 1 );
}

static VOID _acfg_cust_AutoPC_menu_popup(void)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} PID:%d, TID:%d \n",
            __FUNCTION__, __LINE__, getpid(), MApi_Sys_get_thread_id() )); );

    acfg_cust_AutoPc_stop();
    s_AutoPC_eState = AUTO_PC_STATE_WAIT_USER_ANSWER;

    NAV_DIALOG_INIT_T* pt_init = (NAV_DIALOG_INIT_T*)c_mem_alloc(sizeof(NAV_DIALOG_INIT_T));

    if(pt_init == NULL)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: c_mem_alloc fail!! \n", __FUNCTION__,__LINE__ ));
        return;
    }

    //if(pt_init)
    {
        c_memset(pt_init,0,sizeof(NAV_DIALOG_INIT_T));

        pt_init->e_id = NAV_DIALOG_ID_AUTO_PC_GLL;
        pt_init->p_msg_txt = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_AUTO_PC_DIALOG_GLL);
        pt_init->p_yes_txt = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_YES);
        pt_init->p_no_txt = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_NO);
        pt_init->e_style  = UI_SIMPLE_DIALOG_STYLE_SMALL;
        pt_init->ui2_txt_align_type = WGL_AS_CENTER_CENTER;

        pt_init->b_default_answer = FALSE;
        pt_init->ui4_timeout = 5*60*1000; //5*60*1000;
        pt_init->pf_wdgt_proc = a_ui_simple_dialog_default_msg_proc;

        pt_init->pf_ui_simple_dialog_yes_cb_fct = _acfg_cust_AutoPC_menu_answer_yes;
        pt_init->pf_ui_simple_dialog_no_cb_fct = _acfg_cust_AutoPC_menu_answer_no;

        pt_init->pf_ui_simple_dialog_tts_cb_fct = a_ui_simple_dialog_default_tts_cb_fct;

        nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_DIALOG),
                                  NAV_UI_MSG_REST_NOTIFICATION,
                                  pt_init);

        // pt_init will be free at _nav_dialog_handle_msg()
    }
}

static BOOL _acfg_cust_AutoPC_get_cur_device_name(ISL_REC_T* pst_ISL_REC_T, char* pcDeviceName, UINT8 u8NameBufSize)
{
    UTF16_T a16DeviceName[AUTO_PC_DEVICE_NAME_SIZE+1] = {0};

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} \n", __FUNCTION__,__LINE__ )); );


    INT32 i32_rtn = a_cfg_custom_get_inp_name_with_cec_name(pst_ISL_REC_T, a16DeviceName, AUTO_PC_DEVICE_NAME_SIZE);

    if( APP_CFGR_OK != i32_rtn )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] Get CEC name fail! => Use default=>HDMI_NoName \n" )); );
        c_strncpy( pcDeviceName, "HDMI_NoName", u8NameBufSize-1 );
        return TRUE;
    }

    if( c_uc_w2s_strlen(a16DeviceName) == 0 )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] CEC name len = 0! => Use default=>HDMI_NoName \n" )); );
        c_strncpy( pcDeviceName, "HDMI_NoName", u8NameBufSize-1 );
        return TRUE;
    }

    c_uc_w2s_to_ps( a16DeviceName, pcDeviceName, u8NameBufSize-1);

    return TRUE;
}

UINT16 _acfg_cust_AutoPC_diff( UINT16 u16Val_1, UINT16 u16Val_2 )
{
    if( u16Val_1 > u16Val_2 )
        return (u16Val_1 - u16Val_2);

    return (u16Val_2 - u16Val_1);
}

BOOL _acfg_cust_AutoPC_is_video_timing_by_resolution(UINT16 u16Width, UINT16 u16High)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} u16Width:%d, u16High:%d\n",
        __FUNCTION__, __LINE__, u16Width, u16High )); );

#define VIDEO_TIMING_NUM    5
#define VIDEO_TIMING_OFFSET 10
    UINT16 au16_resolution[VIDEO_TIMING_NUM][2] =
    {
        { 720, 480 },
        { 720, 576 },
        { 1280, 720 },
        { 1920, 1080 },
        { 3840, 2160 },
    };

    int i;
    UINT16 w,h;

    for( i = 0; i < VIDEO_TIMING_NUM; i += 1 )
    {
        w = au16_resolution[i][0];
        h = au16_resolution[i][1];

        //DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} w:%d, h:%d\n", __FUNCTION__, __LINE__, w, h )); );

        if( (_acfg_cust_AutoPC_diff(w, u16Width) < VIDEO_TIMING_OFFSET)
          &&(_acfg_cust_AutoPC_diff(h, u16High) < VIDEO_TIMING_OFFSET)
          )
        {
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} u16Width:%d, u16High:%d => Is video tming\n",
                __FUNCTION__, __LINE__, u16Width, u16High )); );

            return TRUE;
        }
    }

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} u16Width:%d, u16High:%d => Is not video tming\n",
                __FUNCTION__, __LINE__, u16Width, u16High )); );

    return FALSE;
}

char* Nav_get_comp_name(NAV_COMP_ID_T e_COMP_ID)
{
    //DBG_LOG_PRINT(("[AutoPC]%s(%d) \n", __FUNCTION__, e_COMP_ID));
  #if 0
    NAV_COMP_ID_VOL_CTRL:10
    NAV_COMP_ID_INPUT_SRC:13
    NAV_COMP_ID_PICTURE_EFFECT:22
    NAV_COMP_ID_DIALOG:40
    NAV_COMP_ID_BANNER:49
    NAV_COMP_ID_SCREEN_SAVER:50
    NAV_COMP_ID_TEST_PATTERN:60
    NAV_COMP_ID_ZOOM:61
    NAV_COMP_ID_LAST_VALID_ENTRY:64
  #endif
  #if 0
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_VOL_CTRL:%d \n", NAV_COMP_ID_VOL_CTRL));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_INPUT_SRC:%d \n", NAV_COMP_ID_INPUT_SRC));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_PICTURE_EFFECT:%d \n", NAV_COMP_ID_PICTURE_EFFECT));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_DIALOG:%d \n", NAV_COMP_ID_DIALOG));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_BANNER:%d \n", NAV_COMP_ID_BANNER));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_SCREEN_SAVER:%d \n", NAV_COMP_ID_SCREEN_SAVER));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_TEST_PATTERN:%d \n", NAV_COMP_ID_TEST_PATTERN));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_ZOOM:%d \n", NAV_COMP_ID_ZOOM));
    //DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_PPP:%d \n", NAV_COMP_ID_PPP));
    //DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_WEBUI_AGENT:%d \n", NAV_COMP_ID_WEBUI_AGENT));
    DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_LAST_VALID_ENTRY:%d \n", NAV_COMP_ID_LAST_VALID_ENTRY));
  #endif

    char* pcCompName = "Unknown";

  #define _NAV_ID_NAME_PAIR(id,name)  case id:  pcCompName = name;  break

    switch(e_COMP_ID)
    {
        default:  break;

        _NAV_ID_NAME_PAIR(NAV_COMP_ID_VOL_CTRL, "VOL_CTRL");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_INPUT_SRC, "INPUT_SRC");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_PICTURE_EFFECT, "PICTURE_EFFECT"); // Key:PIC => Picture mode
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_DIALOG, "DIALOG");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_BANNER, "BANNER");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_SCREEN_SAVER, "SCREEN_SAVER");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_TEST_PATTERN, "TEST_PATTERN");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_ZOOM, "ZOOM");
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_PPP, "PPP"); //  Picture Mode & Power Mode Popup notification
        _NAV_ID_NAME_PAIR(NAV_COMP_ID_WEBUI_AGENT, "WEBUI_AGENT");

        _NAV_ID_NAME_PAIR(NAV_COMP_ID_LAST_VALID_ENTRY, "LAST_VALID_ENTRY"); /* only for counting purpose */
    }

    return pcCompName;
}

static UINT8 _s_AutoPc_u8Test_force_NeedToTurnOnGLL = 0;
static UINT8 _s_AutoPc_u8Test_force_DB_no_answer = 0;

BOOL b_is_factory_auto_test = FALSE;

static void _acfg_cust_AutoPC_Task(void)
//static void _acfg_cust_AutoPC_Task(VOID* pv_data, SIZE_T z_data_len)
{
    if(b_is_factory_auto_test)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} b_is_factory_auto_test case !!!\n",__FUNCTION__,__LINE__ ));
        acfg_cust_AutoPc_stop();
        return;
    }
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} eState:%d, PID:%d, TID:%d ------------------------------ \n",
        __FUNCTION__, __LINE__, s_AutoPC_eState, getpid(), MApi_Sys_get_thread_id() )); );


    switch( s_AutoPC_eState )
    {
        default:
        case AUTO_PC_STATE_NONE:
            DBG_LOG_PRINT(("[AutoPC]{%s,%d} Invalid s_AutoPC_eState: %d \n", __FUNCTION__, __LINE__, s_AutoPC_eState ));
            acfg_cust_AutoPc_stop();
            break;

        case AUTO_PC_STATE_STOP:
            acfg_cust_AutoPc_stop();
            return;
            break;

        case AUTO_PC_STATE_START:
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} case AUTO_PC_STATE_START \n", __FUNCTION__, __LINE__ )); );
            break;

        case AUTO_PC_STATE_WAIT_POP_MENU:
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} case AUTO_PC_STATE_WAIT_POP_MENU \n", __FUNCTION__, __LINE__ )); );
            break;

        case AUTO_PC_STATE_WAIT_USER_ANSWER:
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} case AUTO_PC_STATE_WAIT_USER_ANSWER \n", __FUNCTION__, __LINE__ )); );
            acfg_cust_AutoPc_stop();
            return;
            break;
    }

    UINT8   ui1_fac_mask = 0;
    a_cfg_get_factory_mode(&ui1_fac_mask);
    if ((ui1_fac_mask & APP_CFG_FAC_MODE_FACTORY_MASK) != 0)
    {
        DBG_LOG_PRINT(("\n%s Line: %d, factory_mode\n", __FUNCTION__, __LINE__));
        acfg_cust_AutoPc_stop();
        return;
    }

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Checking input ... \n", __FUNCTION__, __LINE__ )); );
    INT32 i32_rtn;
    ISL_REC_T stISL_REC = {0};

    i32_rtn = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &stISL_REC);
    if(i32_rtn != TVR_OK)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: a_tv_get_isl_rec_by_snk_name fail!! i4_ret:%d\n", __FUNCTION__,__LINE__, i32_rtn));
        acfg_cust_AutoPc_stop();
        return;
    }

    // Check input_source ...
    if( (stISL_REC.e_src_type != INP_SRC_TYPE_AV) )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Not INP_SRC_TYPE_AV \n", __FUNCTION__, __LINE__ )); );
        acfg_cust_AutoPc_stop();
        return;
    }

    BOOL bIsSrcHDMI = FALSE;
    BOOL bIsSrcDVI = FALSE;

    //if( (stISL_REC.e_src_type == INP_SRC_TYPE_AV) )
    {
        if( stISL_REC.t_avc_info.e_video_type == DEV_AVC_HDMI ) // HDMI
        {
            bIsSrcHDMI = TRUE;
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] Src is HDMI\n" )); );
        }
        else if( stISL_REC.t_avc_info.e_video_type == DEV_AVC_DVI) // DVI
        {
            bIsSrcDVI = TRUE;
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] Src is DVI\n" )); );
            //acfg_cust_AutoPc_stop();
            //return;
        }
        else
        {
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Not HDMI~ \n", __FUNCTION__, __LINE__ )); );
            acfg_cust_AutoPc_stop();
            return;
        }
    }

    // Get HDMI port...
    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    DBG_LOG_PRINT(("[AutoPC]{%s,%d}   u8CurHdmi_UI_Idx:%d \n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx ));
    if( u8CurHdmi_UI_Idx >= 4 )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Invalid u8CurHdmi_UI_Idx:%d\n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx ));
        acfg_cust_AutoPc_stop();
        return ;
    }

    s_AutoPC_u8CurHdmiIdx = u8CurHdmi_UI_Idx;


    // Check has signal ...
    if( (a_common_setting_is_signal_loss() == TRUE) || (a_common_setting_is_video_block() == TRUE) )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s:%d} NoSignal or VideoBlock ~\n", __FUNCTION__, __LINE__)); );
        acfg_cust_AutoPc_stop();
        return ;
    }
    else
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s:%d} Has Signal ~\n", __FUNCTION__, __LINE__)); );
    }


    // Get current GLL setting...
    INT16 i16CurGLL = 0;
    i32_rtn = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i16CurGLL);
    if(i32_rtn != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Cannot get GLL!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i32_rtn));
        acfg_cust_AutoPc_stop();
        return;
    }
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} i16CurGLL:%d\n",__FUNCTION__,__LINE__, i16CurGLL )); );

    // If GLL is on, exit
    if( i16CurGLL == ACFG_CUST_GAME_LOW_LATENCY_ON )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} GLL already On~\n",__FUNCTION__,__LINE__ )); );
        acfg_cust_AutoPc_stop();
        return;
    }


    // Check current device name ...
    c_memset(s_AutoPC_au8CurDeviceName, 0, sizeof(s_AutoPC_au8CurDeviceName));
    if( bIsSrcDVI )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC] DVI => CEC => Use default => DVI_NoName \n" )); );
        c_strncpy( s_AutoPC_au8CurDeviceName, "DVI_NoName", AUTO_PC_DEVICE_NAME_SIZE-1 );
    }
    else
    {
        BOOL bGetNameRtn = _acfg_cust_AutoPC_get_cur_device_name( &stISL_REC, s_AutoPC_au8CurDeviceName, AUTO_PC_DEVICE_NAME_SIZE);
        if( bGetNameRtn == FALSE )
        {
            DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Cannot get device name!! \n", __FUNCTION__,__LINE__));
            acfg_cust_AutoPc_stop();
            return;
        }
    }
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Device name: %s\n", __FUNCTION__,__LINE__, s_AutoPC_au8CurDeviceName )); );

    // Check if current device already checked ...
    EnuAutoPcUserAnswer eUserAnswer = _acfg_cust_AutoPC_DB_get_user_answer( u8CurHdmi_UI_Idx, s_AutoPC_au8CurDeviceName);
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Device name: %s  => eUserAnswer:%d\n", __FUNCTION__,__LINE__, s_AutoPC_au8CurDeviceName, eUserAnswer )); );

    if(_s_AutoPc_u8Test_force_DB_no_answer)
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Test: Force DB no answer!!!\n", __FUNCTION__,__LINE__ )); );
        eUserAnswer = AUTO_PC_DEVICE_USER_ANSWER_NONE;
    }

    // Check user answer - NO
    if( (eUserAnswer == AUTO_PC_DEVICE_USER_ANSWER_NO) )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} User already say NO, stop task\n", __FUNCTION__,__LINE__ )); );
        // Do nothing...
        acfg_cust_AutoPc_stop();
        return;
    }

    // Color format
    ACFG_CUST_HDMI_COLOR_FORMAT_T eHdmiColorForamt = ACFG_CUST_HDMI_COLOR_RGB;

    // Check source PC(Timing) ...
    // Get ITC/VIC
    StuHdmiItcVicInfo stHdmiItcVicInfo = {0};
    BOOL b_ITC_is_1 = FALSE;
    BOOL bIsPCTiming_by_VIC = FALSE;

    if( bIsSrcDVI )
    {
        eHdmiColorForamt = ACFG_CUST_HDMI_COLOR_RGB;
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} bIsSrcDVI:1 => COLOR_RGB\n", __FUNCTION__,__LINE__ )); );
    }
    else //if( bIsSrcHDMI )
    {
        // Get HDMI color format ...
        eHdmiColorForamt = acfg_cust_video_get_hdmi_color_space();
        DBG_LOG_PRINT(("[AutoPC]{%s:%d} Src is HDMI, hdmi_color => %d(%s) \n", __FUNCTION__, __LINE__,
            eHdmiColorForamt, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorForamt) ));

        i32_rtn = acfg_cust_HDMI_get_ITC_VIC(u8CurHdmi_UI_Idx, &stHdmiItcVicInfo);
        if( i32_rtn != APP_CFGR_OK )
        {
            DBG_LOG_PRINT(("[AutoPC]{%s,%d} acfg_cust_HDMI_get_ITC_VIC() fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
            acfg_cust_AutoPc_stop();
            return;
        }
        else
        {
            if( stHdmiItcVicInfo.bAVI_Info_Valid )
            {
                if( stHdmiItcVicInfo.u8ITC )
                {
                    b_ITC_is_1 = TRUE;
                    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} ITC:1, CN:%d\n",__FUNCTION__,__LINE__, stHdmiItcVicInfo.u8CN )); );
                }
            }

            if( (stHdmiItcVicInfo.bAVI_Info_Valid && stHdmiItcVicInfo.u8AVI_VIC)
              ||(stHdmiItcVicInfo.bVSIF_Valid && stHdmiItcVicInfo.u8VSIF_VIC)
              )
            {
                bIsPCTiming_by_VIC = FALSE;
                DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} u8AVI_VIC:%d, u8VSIF_VIC:%d ==> Is Video timing\n",
                        __FUNCTION__,__LINE__, stHdmiItcVicInfo.u8AVI_VIC, stHdmiItcVicInfo.u8VSIF_VIC )); );
            }
            else
            {
                bIsPCTiming_by_VIC = TRUE;
                DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} VIC:0 => Is PC Timing\n", __FUNCTION__,__LINE__ )); );
            }
        }
    }


    // Check timing ...
    VSH_SRC_RESOLUTION_INFO_T t_timing = {0};
    i32_rtn = a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_timing);
    if( i32_rtn != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d}Error: a_cfg_av_get_timing() fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
        acfg_cust_AutoPc_stop();
        return;
    }

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Timing: Width:%d, High:%d, freq:%d\n",
                __FUNCTION__,__LINE__, t_timing.ui4_width, t_timing.ui4_height, t_timing.ui4_frame_rate )); );
    if( (t_timing.ui4_width == 0)
     || (t_timing.ui4_height == 0)
     || (t_timing.ui4_frame_rate == 0)
      )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Error: Invalid timing! Width:%d, High:%d, freq:%d\n",
            __FUNCTION__, __LINE__, t_timing.ui4_width, t_timing.ui4_height, t_timing.ui4_frame_rate ));
        acfg_cust_AutoPc_stop();
        return;
    }

    BOOL bIsVideoTiming_by_resolution = _acfg_cust_AutoPC_is_video_timing_by_resolution(t_timing.ui4_width, t_timing.ui4_height);


    //Does the signal include any of the following:
    //DVI/VGA
    //AV Info Frame ITC = 1
    //Full Range (0-255) RGB signal
    //A PC-only VESA Timing (not including common CEA timings, aka 2160p, 1080p, 720p, 480p, 1080i, 480i)
    //BOOL b_device_could_be_PC = FALSE;

    // Check if need to turn on GLL ...
    BOOL bNeedToTurnOnGLL = FALSE;

    if( bIsSrcDVI )
    {
        bNeedToTurnOnGLL = TRUE;
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} DVI => bNeedToTurnOnGLL=1\n", __FUNCTION__,__LINE__ )); );
    }
    /* customer new spec to remove Full Range (0-255) RGB signal
    else if( bIsSrcHDMI && (eHdmiColorForamt == ACFG_CUST_HDMI_COLOR_RGB) )
    {
        bNeedToTurnOnGLL = TRUE;
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} HDMI color is RGB => no need to rurn on GLL bNeedToTurnOnGLL=0\n", __FUNCTION__,__LINE__ )); );
    }
    */
    else if( b_ITC_is_1 )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} ITC:1, CN:%d ==> bNeedToTurnOnGLL=1\n",
            __FUNCTION__,__LINE__, stHdmiItcVicInfo.u8CN )); );
        bNeedToTurnOnGLL = TRUE;
    }
    else if( !bIsVideoTiming_by_resolution )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Resolution(%d,%d) not video timing => bNeedToTurnOnGLL=1\n",
            __FUNCTION__,__LINE__, t_timing.ui4_width, t_timing.ui4_height )); );
        bNeedToTurnOnGLL = TRUE;
    }
    /*
    else if( bIsPCTiming_by_VIC )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} bIsPCTiming_by_VIC:%d ==> bNeedToTurnOnGLL=1\n",
            __FUNCTION__,__LINE__, bIsPCTiming_by_VIC )); );
        bNeedToTurnOnGLL = TRUE;
    }
    */
    else if( _s_AutoPc_u8Test_force_NeedToTurnOnGLL )
    {
        // daniel test
        bNeedToTurnOnGLL = TRUE;
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} daniel test ==> bNeedToTurnOnGLL=1\n", __FUNCTION__,__LINE__ )); );
    }

    if( !bNeedToTurnOnGLL )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} No need to turn on GLL\n", __FUNCTION__,__LINE__ )); );
        acfg_cust_AutoPc_stop();
        return;
    }

    // Check user answer ...
    if( eUserAnswer == AUTO_PC_DEVICE_USER_ANSWER_YES )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} User already say Yes~\n", __FUNCTION__,__LINE__ )); );
        acfg_cust_AutoPc_stop();
        _acfg_cust_AutoPC_set_GLL_on();
        return;
    }

    // Check if can pop menu...
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Check if can pop menu~\n", __FUNCTION__,__LINE__ )); );

    CHAR s_app_name[APP_NAME_MAX_LEN+1] = {0};
    // Check current app ...
    i32_rtn = a_am_get_active_app(s_app_name);
    if( i32_rtn != AMR_OK)
    {
        DBG_LOG_PRINT(("[AutoPC]{%s:%d} Error: Get app name failed! i32_rtn:%d\n", __FUNCTION__, __LINE__, i32_rtn ));
        acfg_cust_AutoPc_stop();
        return;
    }
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} s_app_name:{%s}\n",__FUNCTION__,__LINE__, s_app_name )); );

    BOOL bNeedPopMenu = FALSE;

    if( c_strcmp(s_app_name, MENU_NAME) == 0 )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} App is Menu => Skip\n",__FUNCTION__,__LINE__ )); );
    }
    else if( c_strcmp(s_app_name, "navigator") == 0 )
    {
        BOOL bSomethingIsShow = FALSE;
    /*
        NAV_COMP_ID_T e_NAV_COMP_ID = nav_get_active_component();
        char* pcCompName = Nav_get_comp_name(e_NAV_COMP_ID);
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} App is NAV, comp_id:%d(%s), visible:%d \n",
            __FUNCTION__,__LINE__, e_NAV_COMP_ID, pcCompName, nav_is_component_visible(e_NAV_COMP_ID) )); );
    */
        //e_NAV_COMP_ID = NAV_COMP_ID_BANNER;
        //pcCompName = Nav_get_comp_name(e_NAV_COMP_ID);
        //DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} comp_id:%d(%s), visible:%d \n", __FUNCTION__,__LINE__, e_NAV_COMP_ID, pcCompName, nav_is_component_visible(e_NAV_COMP_ID) )); );

        {
            int iCompId;
            NAV_COMP_ID_T e_NAV_COMP_ID;

            for( iCompId = 0; iCompId < NAV_COMP_ID_LAST_VALID_ENTRY; iCompId += 1 )
            {
                e_NAV_COMP_ID = (NAV_COMP_ID_T)iCompId;
                if( nav_is_component_visible(e_NAV_COMP_ID) )
                {
                    bSomethingIsShow = TRUE;
                    //pcCompName = Nav_get_comp_name(e_NAV_COMP_ID);
                    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} comp_id:%d(%s), visible:%d \n",
                        __FUNCTION__,__LINE__,
                        e_NAV_COMP_ID, Nav_get_comp_name(e_NAV_COMP_ID),
                        nav_is_component_visible(e_NAV_COMP_ID) ));
                    );
                }
            }
        }

        if( bSomethingIsShow )
        {
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} NAV menu is show => cannot pop menu!!\n", __FUNCTION__,__LINE__ )); );
        }
        else
        {
            DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} NAV menu is not show => can pop menu\n",__FUNCTION__,__LINE__ )); );
            bNeedPopMenu = TRUE;
        }

    }
    else
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} App is unknown => Skip\n",__FUNCTION__,__LINE__ )); );
    }

    if( bNeedPopMenu )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} Pop menu to ask user\n", __FUNCTION__,__LINE__ )); );
        //acfg_cust_AutoPc_stop();
        //s_AutoPC_eState = AUTO_PC_STATE_WAIT_USER_ANSWER;
        _acfg_cust_AutoPC_menu_popup();
    }
    else
    {
        // check at next time => continue task
        s_AutoPC_eState = AUTO_PC_STATE_WAIT_POP_MENU;
    }
}

static void _acfg_cust_AutoPC_Task_async(VOID* pv_data, SIZE_T z_data_len)
{
    _acfg_cust_AutoPC_Task();
}

static VOID _acfg_cust_AutoPc_timer_nfy_fct(HANDLE_T  pt_tm_handle, VOID* pv_tag)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} PID:%d, TID:%d \n",
            __FUNCTION__, __LINE__, getpid(), MApi_Sys_get_thread_id() )); );

    //_acfg_cust_AutoPC_Task(NULL, 0);
    //a_cfg_async_invoke( _acfg_cust_AutoPC_Task, NULL, 0 );

    a_cfg_async_invoke( _acfg_cust_AutoPC_Task_async, NULL, 0 );
}

static HANDLE_T s_h_acfg_cust_AutoPc_task_timer = 0;
#define AUTO_PC_TASK_PERIOD     4000

void acfg_cust_AutoPc_init(void)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} \n",__FUNCTION__,__LINE__ )); );

    s_AutoPC_eState = AUTO_PC_STATE_STOP;

    // Load user setting ...
    if( FALSE == _acfg_cust_AutoPc_DB_init() )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} _acfg_cust_AutoPc_DB_init() fail!!! \n", __FUNCTION__, __LINE__ ));
        return;
    }


    INT32 i32_rtn;

    // Create timer handle
    i32_rtn = c_timer_create(&s_h_acfg_cust_AutoPc_task_timer);
    if( i32_rtn != 0 )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} create timer fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
    }

    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} s_h_acfg_cust_AutoPc_task_timer: 0x%X \n", __FUNCTION__, __LINE__, s_h_acfg_cust_AutoPc_task_timer )); );
}

void acfg_cust_AutoPc_start(void)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} \n",__FUNCTION__,__LINE__ )); );

    //s_AutoPC_eState = AUTO_PC_STATE_CHECK_INPUT_SIGNAL;

    if( s_h_acfg_cust_AutoPc_task_timer == 0 )
    {
        DBG_LOG_PRINT(("[AutoPC]{%s,%d} Invalid timer !\n", __FUNCTION__, __LINE__ ));
        return;
    }

    // Should stop first ??
    acfg_cust_AutoPc_stop();

    // Timer start
    s_AutoPC_eState = AUTO_PC_STATE_START;

    // do job ...
    _acfg_cust_AutoPC_Task();

    //DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} => s_AutoPC_eState:%d \n",__FUNCTION__,__LINE__, s_AutoPC_eState )); );

    if( (s_AutoPC_eState == AUTO_PC_STATE_START)
      ||(s_AutoPC_eState == AUTO_PC_STATE_WAIT_POP_MENU)
      )
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} => s_AutoPC_eState:%d => Task continue\n",
                __FUNCTION__,__LINE__, s_AutoPC_eState )); );

        // continue task ...
        INT32 i32_rtn = c_timer_start(s_h_acfg_cust_AutoPc_task_timer,
                            AUTO_PC_TASK_PERIOD, // 2000ms
                            X_TIMER_FLAG_REPEAT,
                            //X_TIMER_FLAG_ONCE,
                            _acfg_cust_AutoPc_timer_nfy_fct,
                            NULL);
        if( i32_rtn != 0 )
        {
            DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} Start timer fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
            s_AutoPC_eState = AUTO_PC_STATE_STOP;
        }
    }
    else
    {
        DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} => s_AutoPC_eState:%d => Task stop\n",
                __FUNCTION__,__LINE__, s_AutoPC_eState )); );
    }

}

void acfg_cust_AutoPc_stop(void)
{
    DEBUG_AUTO_PC( DBG_LOG_PRINT(("[AutoPC]{%s,%d} \n",__FUNCTION__,__LINE__ )); );

    if( s_h_acfg_cust_AutoPc_task_timer != 0 )
    {
        c_timer_stop(s_h_acfg_cust_AutoPc_task_timer);
    }

    if( s_AutoPC_eState == AUTO_PC_STATE_WAIT_USER_ANSWER )
    {
        if( nav_is_component_visible(NAV_COMP_ID_DIALOG) )
        {
            nav_dialog_hide();
        }
    }

    s_AutoPC_eState = AUTO_PC_STATE_STOP;
}
#endif


#if( ENABLE_ACFG_HDMI_TASK )

static HANDLE_T s_h_acfg_hdmi_task_timer = 0;

#define DEBUG_HDMI_TASK(x)  //x

void acfg_cust_HDMI_task_stop(void)
{
    DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if( s_h_acfg_hdmi_task_timer != 0 )
    {
        c_timer_stop(s_h_acfg_hdmi_task_timer);
    }

#if 0//(ENABLE_VIZIO_AUTO_PC)
    acfg_cust_AutoPc_stop();
#endif
}

#define HDMI_TASK_TIMER_PERIOD  2000

static VOID _acfg_cust_HDMI_task(VOID* pv_data, SIZE_T z_data_len)
{
    DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d}\n", __FUNCTION__, __LINE__ )); );

    static UINT32 s_u32_HDMI_task_count = 0;
    s_u32_HDMI_task_count += HDMI_TASK_TIMER_PERIOD;
    //DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} cnt:%d \n", __FUNCTION__, __LINE__, s_u32_HDMI_task_count )); );


    // Check input_source is HDMI ...
    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    if( u8CurHdmi_UI_Idx >= 4 )
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} Error: Invalid u8CurHdmi_UI_Idx:%d\n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx ));
        acfg_cust_HDMI_task_stop();
        return ;
    }


 #if 0//(ENABLE_VIZIO_AUTO_PC)
    static UINT32 s_u32_AutoPC_Task_count = 0;
    s_u32_AutoPC_Task_count += HDMI_TASK_TIMER_PERIOD;
    DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} AutoPC_Cnt:%d \n", __FUNCTION__, __LINE__, s_u32_AutoPC_Task_count )); );

    if( s_u32_AutoPC_Task_count >= TASK_AUTO_PC_PERIOD )
    {
        DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} Timer_Cnt:%d \n", __FUNCTION__, __LINE__, s_u32_HDMI_task_count )); );
        DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} AutoPC_Cnt:%d \n", __FUNCTION__, __LINE__, s_u32_AutoPC_Task_count )); );

        s_u32_AutoPC_Task_count = 0;

        //_acfg_cust_AutoPC_Task();
        //_acfg_cust_AutoPC_Task(NULL, 0);
        a_cfg_async_invoke( _acfg_cust_AutoPC_Task, NULL, 0 );
    }
 #endif
}

static VOID _acfg_cust_HDMI_task_timer_nfy_fct(HANDLE_T  pt_tm_handle, VOID* pv_tag)
{
    DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d}\n", __FUNCTION__, __LINE__ )); );

    //a_cfg_async_invoke( _acfg_cust_HDMI_task, NULL, 0 );
    _acfg_cust_HDMI_task( NULL, 0 );
}

void acfg_cust_HDMI_task_start(void)
{
    DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if( s_h_acfg_hdmi_task_timer == 0 )
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} Invalid timer !\n", __FUNCTION__, __LINE__ ));
        return;
    }

    acfg_cust_HDMI_task_stop();


    // Check input_source is HDMI
    // Get HDMI port...
    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    if( u8CurHdmi_UI_Idx >= 4 )
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} Invalid u8CurHdmi_UI_Idx: %d\n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx ));
        return;
    }

    //return;

    // Timer start
    INT32 i32_rtn = c_timer_start(s_h_acfg_hdmi_task_timer,
                        HDMI_TASK_TIMER_PERIOD, // 2000ms
                        X_TIMER_FLAG_REPEAT,
                        _acfg_cust_HDMI_task_timer_nfy_fct,
                        NULL);
    if( i32_rtn != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} Start timer fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
    }

}

void acfg_cust_HDMI_task_init(void)
{
    DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    INT32 i32_rtn;

    // Create timer handle
    //if( s_h_acfg_hdmi_task_timer == 0 )
    {
        i32_rtn = c_timer_create(&s_h_acfg_hdmi_task_timer);
        if( i32_rtn != 0 )
        {
            DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} create timer fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
        }
        DEBUG_HDMI_TASK( DBG_LOG_PRINT(("[ACFG][HDMI][task]{%s,%d} s_h_acfg_hdmi_task_timer: 0x%X \n", __FUNCTION__, __LINE__, s_h_acfg_hdmi_task_timer )); );
    }
}

#endif

#if(ENABLE_TEST_CMD)

#include <errno.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define DEBUG_TESTCMD(x)        //x
#define DEBUG_TESTCMD_EXEC(x)   x


static int s_TestCmd_bInited = 0;

#define TEST_CMD_LINE_BUF_SIZE  128
static char s_acLineBuf[TEST_CMD_LINE_BUF_SIZE] = {0};

#define TEST_CMD_PARA_NUM    5
static UINT32 s_au32TestCmd_Para[TEST_CMD_PARA_NUM] = {0};

static void acfg_cust_TestCmd_Exec(UINT32 au32TestCmdPara[TEST_CMD_PARA_NUM])
{
    //if( 0 == s_TestCmd_bInited )
    //    return;

    int i;

#if 0
    for( i = 0; (i < TEST_CMD_PARA_NUM); i += 1 )
    {
        DBG_LOG_PRINT(("[TestCmd] %d:0x%x\n", i, au32TestCmdPara[i] ));
    }
#endif

    DEBUG_TESTCMD_EXEC(
        DBG_LOG_PRINT(("[TestCmd] Para: 0x%x 0x%x 0x%x 0x%x 0x%x\n",
            au32TestCmdPara[0],au32TestCmdPara[1],au32TestCmdPara[2],au32TestCmdPara[3],au32TestCmdPara[4] ));
    );


    UINT32 u32Cmd = au32TestCmdPara[0];
    UINT32 u32Para1 = au32TestCmdPara[1];
    UINT32 u32Para2 = au32TestCmdPara[2];


    switch( u32Cmd )
    {
        case 0:
            DBG_LOG_PRINT(("[TestCmd] Should not use!!\n" ));
            break;

        case 1:
            DBG_LOG_PRINT(("[TestCmd] Help:\n" ));
            break;

        case 2:
            DBG_LOG_PRINT(("Cmd 2\n"));
            for( i = 0; (i < TEST_CMD_PARA_NUM); i += 1 )
            {
                DBG_LOG_PRINT(("[TestCmd] %d:0x%x\n", i, au32TestCmdPara[i] ));
            }
            break;

        case 3:
        {
        #if(ENABLE_VIZIO_AUTO_PC)
            switch(u32Para1)
            {
                case 1: // echo 3 1 > /data/testcmd.txt
                    _acfg_cust_AutoPC_Task();
                    break;
                case 2: // echo 3 2 > /data/testcmd.txt
                    _acfg_cust_AutoPC_menu_popup();
                    break;
                case 3: // echo 3 3 > /data/testcmd.txt
                    acfg_cust_AutoPc_start();
                    break;
                case 4: // echo 3 4 > /data/testcmd.txt
                    _acfg_cust_AutoPc_PrintDB_all();
                    break;
                case 5: // echo 3 5 0 > /data/testcmd.txt
                    {
                        DBG_LOG_PRINT(("[AutoPC]{%s,%d} call _acfg_cust_AutoPc_DB_reset(%d)\n",
                                                __FUNCTION__,__LINE__, u32Para2 ));

                        _acfg_cust_AutoPc_DB_reset(u32Para2);
                    }
                    break;
                case 6: // echo 3 6 3 > /data/testcmd.txt
                    _s_AutoPc_u8Test_force_NeedToTurnOnGLL = (u32Para2&1)?1:0;
                    DBG_LOG_PRINT(("[AutoPC]{%s,%d} _s_AutoPc_u8Test_force_NeedToTurnOnGLL=%d\n",
                        __FUNCTION__,__LINE__, _s_AutoPc_u8Test_force_NeedToTurnOnGLL ));

                    _s_AutoPc_u8Test_force_DB_no_answer = (u32Para2&3)?1:0;
                    DBG_LOG_PRINT(("[AutoPC]{%s,%d} _s_AutoPc_u8Test_force_DB_no_answer=%d\n",
                        __FUNCTION__,__LINE__, _s_AutoPc_u8Test_force_DB_no_answer ));


                    acfg_cust_AutoPc_start();
                    break;
                case 7: // echo 3 7 > /data/testcmd.txt
                    DBG_LOG_PRINT(("[AutoPC]{%s,%d} enter factory auto test !!!\n",__FUNCTION__,__LINE__ ));
                    b_is_factory_auto_test = TRUE;
                    break;
                case 8: // echo 3 8 > /data/testcmd.txt
                    DBG_LOG_PRINT(("[AutoPC]{%s,%d} quit factory auto test !!!\n",__FUNCTION__,__LINE__ ))
                    b_is_factory_auto_test = FALSE;
                    break;
                default:
                    break;
            }
        #endif
        }
            break;

        case 4: // echo 4 > /data/testcmd.txt
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_VOL_CTRL:%d \n", NAV_COMP_ID_VOL_CTRL));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_INPUT_SRC:%d \n", NAV_COMP_ID_INPUT_SRC));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_PICTURE_EFFECT:%d \n", NAV_COMP_ID_PICTURE_EFFECT));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_DIALOG:%d \n", NAV_COMP_ID_DIALOG));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_BANNER:%d \n", NAV_COMP_ID_BANNER));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_SCREEN_SAVER:%d \n", NAV_COMP_ID_SCREEN_SAVER));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_TEST_PATTERN:%d \n", NAV_COMP_ID_TEST_PATTERN));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_ZOOM:%d \n", NAV_COMP_ID_ZOOM));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_PPP:%d \n", NAV_COMP_ID_PPP));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_WEBUI_AGENT:%d \n", NAV_COMP_ID_WEBUI_AGENT));
            DBG_LOG_PRINT(("[AutoPC] NAV_COMP_ID_LAST_VALID_ENTRY:%d \n", NAV_COMP_ID_LAST_VALID_ENTRY));
            break;

        default:
            DBG_LOG_PRINT(("[TestCmd] Unknown command!\n" ));
            break;
    }
}

UINT16 acfg_cust_TestCmd_ReadCmd_1(char acLineBuf[TEST_CMD_LINE_BUF_SIZE])
{
    char pcFullFileName[] = "/data/testcmd.txt";

    // Check file should exist...
    if( access(pcFullFileName, F_OK) == 0 )
    {
        DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd] File(%s) exist\n", pcFullFileName)); );
    }
    else
    {
        DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd] File(%s) not exist\n", pcFullFileName)); );
        return 0;
    }


    FILE* pfIn = fopen(pcFullFileName, "r");
    if(pfIn == NULL)
    {
        DBG_LOG_PRINT(("\n[TestCmd]Error: Open file(%s) failed\n\n", pcFullFileName));
        return 0;
    }


    int iStrLen;

    // Read file ...
    acLineBuf[0] = 0;

    if( NULL == fgets(acLineBuf, TEST_CMD_LINE_BUF_SIZE, pfIn) )
    {
        iStrLen = 0;
    }
    else
    {
        iStrLen = strlen(acLineBuf);
        if(iStrLen)
        {
            char cLast = acLineBuf[iStrLen-1];
            if(cLast=='\n')
            {
                acLineBuf[iStrLen-1]=0;
                iStrLen = strlen(acLineBuf);
            }
        }
    }

    // Remove newline ...
    if( iStrLen > 0 )
    {
        //DBG_LOG_PRINT(("[TestCmd]{%s,%d} iStrLen:%d\n", __FUNCTION__, __LINE__, iStrLen ));

        char cLast = acLineBuf[iStrLen-1];
        if( cLast == '\n' )
        {
            acLineBuf[iStrLen-1] = 0;
            iStrLen = strlen(acLineBuf);
        }
        //printf("buf:{%s}\n", buf);
    }

    fclose(pfIn);

    // Remove file...
    char acCmdBuf[64] = {0};

    // create folder for debug...
    sprintf(acCmdBuf, "rm -vf %s", pcFullFileName);
    DEBUG_TESTCMD( DBG_LOG_PRINT(("acCmdBuf=[%s]\n", acCmdBuf)); );

    int iSysCallRtn = system(acCmdBuf);
    if( 0 != iSysCallRtn )
    {
        DBG_LOG_PRINT(("system(%s) fail => %d\n", acCmdBuf, iSysCallRtn ));
        //return ;
    }

    return iStrLen;
}

#define TEST_CMD_USE_FIFO   0

#if(TEST_CMD_USE_FIFO)
#define TESTCMD_FIFO        "/data/testcmd"

UINT16 acfg_cust_TestCmd_ReadCmd_2(char acLineBuf[TEST_CMD_LINE_BUF_SIZE])
{
    char pcFullFileName[] = TESTCMD_FIFO;

    int fd = open(pcFullFileName, O_RDONLY|O_NONBLOCK);
    //printf("fd:%d\n", fd);
    //DBG_LOG_PRINT(("[TestCmd]{%s,%d} fd:%d \n", __FUNCTION__, __LINE__, fd ));
    if( fd < 0 )
    {
        //printf("\nError: open FIFO failed! fd:%d\n", fd);
        DBG_LOG_PRINT(("[TestCmd]{%s,%d} Error: open FIFO failed! fd:%d \n", __FUNCTION__, __LINE__, fd ));
        //exit(1);
        return 0;
    }

    // Read FIFO ...
    acLineBuf[0] = 0;

    int iStrLen = read(fd, acLineBuf, TEST_CMD_LINE_BUF_SIZE);
    //printf("len:%d\n", len);
    //DBG_LOG_PRINT(("[TestCmd]{%s,%d} iStrLen:%d\n", __FUNCTION__, __LINE__, iStrLen ));

    // Remove newline ...
    if( iStrLen > 0 )
    {
        //DBG_LOG_PRINT(("[TestCmd]{%s,%d} iStrLen:%d\n", __FUNCTION__, __LINE__, iStrLen ));

        char cLast = acLineBuf[iStrLen-1];
        if( cLast == '\n' )
        {
            acLineBuf[iStrLen-1] = 0;
            iStrLen = strlen(acLineBuf);
        }
        //printf("buf:{%s}\n", buf);
    }

    close(fd);

    return iStrLen;
}
#endif

UINT8 acfg_cust_TestCmd_ParseCmd(char acLineBuf[TEST_CMD_LINE_BUF_SIZE], UINT32 au32Cmd_Para[TEST_CMD_PARA_NUM])
{
    int iStrLen = strlen(acLineBuf);

    if( iStrLen == 0 )
    {
        return 0;
    }

    DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd]{%s,%d} iStrLen:%d [%s]\n", __FUNCTION__, __LINE__, iStrLen, acLineBuf )); );

    unsigned int uiVal;
    char acVar_Val[TEST_CMD_PARA_NUM][16] = {0};


    int iParaNum = sscanf( acLineBuf, "%15s %15s %15s %15s %15s", &(acVar_Val[0][0]), &(acVar_Val[1][0]), &(acVar_Val[2][0]), &(acVar_Val[3][0]), &(acVar_Val[4][0]) );
    //printf("iParaNum=%d\n", iParaNum);
    //DBG_LOG_PRINT(("[TestCmd] 11=> iParaNum=%d,\n", iParaNum ));

    if( iParaNum > 0 )
    {
        DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd] => iParaNum=%d,\n", iParaNum )); );

        int i;
        for( i = 0; (i < TEST_CMD_PARA_NUM)&&(i<iParaNum); i += 1 )
        {
            //DBG_LOG_PRINT(("[TestCmd] Str[%d]:%s\n", i, acVar_Val[i] ));

            // Convert acVar_Val to UINT32
            if( (acVar_Val[i][0] == '0') && (acVar_Val[i][1] == 'x') )
            {
                sscanf( acVar_Val[i], "0x%X", &uiVal);
                DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd] Str[%d]:%s ==> uiVal: 0x%x\n", i, acVar_Val[i], uiVal)); );
            }
            else
            {
                sscanf( acVar_Val[i], "%u", &uiVal);
                DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd] Str[%d]:%s ==> uiVal: %d\n", i, acVar_Val[i], uiVal)); );
            }

            au32Cmd_Para[i] = uiVal;
        }
    }

    return iParaNum;
}

//static void acfg_cust_TestCmd_Task(void)
static VOID acfg_cust_TestCmd_Task(VOID* pv_data, SIZE_T z_data_len)
{
    if( 0 == s_TestCmd_bInited )
        return;


    s_acLineBuf[0] = 0;

    // Get cmd ...
    UINT16 u16DataSize = acfg_cust_TestCmd_ReadCmd_1(s_acLineBuf);
    DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd]{%s,%d} u16DataSize:%d\n", __FUNCTION__, __LINE__, u16DataSize )); );
    if( u16DataSize == 0 )
    {
    #if(TEST_CMD_USE_FIFO)
        // Check FIFO ...
        u16DataSize = acfg_cust_TestCmd_ReadCmd_2(s_acLineBuf);
        DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd]{%s,%d} u16DataSize:%d\n", __FUNCTION__, __LINE__, u16DataSize )); );
    #endif
    }

    if( u16DataSize == 0 )
    {
        return;
    }

    //DBG_LOG_PRINT(("[TestCmd]{%s,%d} u16DataSize:%d [%s]\n", __FUNCTION__, __LINE__, u16DataSize, s_acLineBuf ));

    // Convert cmd_line to para ...
    s_au32TestCmd_Para[0] = 0;

    UINT8 u8ParseRtn = acfg_cust_TestCmd_ParseCmd( s_acLineBuf, s_au32TestCmd_Para);
    DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd]{%s,%d} u8ParseRtn:%d\n", __FUNCTION__, __LINE__, u8ParseRtn )); );
    if( u8ParseRtn == 0 )
    {
        DBG_LOG_PRINT(("[TestCmd]{%s,%d} Warning: u8ParseRtn:%d\n", __FUNCTION__, __LINE__, u8ParseRtn ));
        return;
    }


    acfg_cust_TestCmd_Exec(s_au32TestCmd_Para);

    //return 0;
}

static VOID _acfg_cust_TestCmd_task_timer_nfy_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    //DBG_LOG_PRINT(("[TestCmd]{%s,%d}\n", __FUNCTION__, __LINE__ ));

    //a_cfg_async_invoke( acfg_cust_TestCmd_Task, NULL, 0 );
    acfg_cust_TestCmd_Task(NULL, 0);
}


static HANDLE_T s_h_acfg_TestCmd_timer = 0;

void acfg_cust_TestCmd_Init(void)
{
    DBG_LOG_PRINT(("[TestCmd]{%s,%d} \n", __FUNCTION__, __LINE__ ));

    // Create timer handle
    INT32 i32_rtn = c_timer_create(&s_h_acfg_TestCmd_timer);
    if( i32_rtn != 0 )
    {
        DBG_LOG_PRINT(("[TestCmd]{%s,%d} Error: create timer fail! i32_rtn:%d \n", __FUNCTION__, __LINE__, i32_rtn ));
    }

    DEBUG_TESTCMD( DBG_LOG_PRINT(("[TestCmd]{%s,%d} s_h_acfg_TestCmd_timer: 0x%X \n", __FUNCTION__, __LINE__, s_h_acfg_TestCmd_timer )); );

#if(TEST_CMD_USE_FIFO)
    // Create FIFO ...
	char acFifoName[] = TESTCMD_FIFO;

	//printf("Create FIFO ...\n");
    DBG_LOG_PRINT(("[TestCmd]{%s,%d} Create FIFO(%s)...\n", __FUNCTION__, __LINE__, acFifoName ));

	int iRtn = mkfifo(acFifoName, 0777); // O_CREAT|O_RDWR|O_NONBLOCK
	//printf("iRtn:%d\n", iRtn);
	if( ( iRtn < 0) && (errno != EEXIST) )
	{
		//printf("\nError: Can not creat fifo! iRtn:%d, errno:%d\n", iRtn, errno);
		DBG_LOG_PRINT(("[TestCmd]{%s,%d} Error: Can not create fifo(%s)! iRtn:%d, errno:%d\n",
		        __FUNCTION__, __LINE__, acFifoName, iRtn, errno ));
		//exit(1);
		return;
	}
#endif

    // Timer start
    i32_rtn = c_timer_start(s_h_acfg_TestCmd_timer,
                        3000, // 1000ms
                        X_TIMER_FLAG_REPEAT,
                        _acfg_cust_TestCmd_task_timer_nfy_fct,
                        NULL);

    s_TestCmd_bInited = 1;

}

#endif

#if 1//( ENABLE_HDMI_EDID_NEW_METHOD )
char* acfg_cust_get_acfg_edid_name(EnuAcfgEdidIdx e_acfg_edid_idx)
{
    char* pc_ACFG_edid_name = "Unknown";

    switch(e_acfg_edid_idx)
    {
        default: break;
        case ACFG_EDID_IDX_1_4: pc_ACFG_edid_name="ACFG_EDID_1_4";
            break;
        case ACFG_EDID_IDX_2_1: pc_ACFG_edid_name="ACFG_EDID_2_1";
            break;
        case ACFG_EDID_IDX_AUTO: pc_ACFG_edid_name="ACFG_EDID_AUTO";
            break;
    }

    return pc_ACFG_edid_name;
}

char* acfg_cust_get_glue_edid_name(EnuGlueEdidIdx e_glue_edid_idx)
{
    char* pc_glue_edid_name = "Unknown";

    switch(e_glue_edid_idx)
    {
        default: break;
        case GLUE_EDID_IDX_1_4: pc_glue_edid_name="GLUE_EDID_1_4";
            break;
        case GLUE_EDID_IDX_2_0: pc_glue_edid_name="GLUE_EDID_2_0";
            break;
        case GLUE_EDID_IDX_AUTO: pc_glue_edid_name="GLUE_EDID_AUTO";
            break;
        case GLUE_EDID_IDX_2_1: pc_glue_edid_name="GLUE_EDID_2_1";
            break;
    }

    return pc_glue_edid_name;
}

UINT8 acfg_cust_EDID_convert_UI_idx_to_acfg_idx(UINT8 u8_UI_edid_idx)
{
    EnuAcfgEdidIdx e_acfg_edid_idx = ACFG_EDID_IDX_AUTO;

    // UI val to inp_lst val
    switch( u8_UI_edid_idx )
    {
        default:
            DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} Error: Invalid u8_UI_edid_idx:%d !!!\n",
                __FUNCTION__, __LINE__, u8_UI_edid_idx ));
            break;

        case UI_EDID_SEL_AUTO: // 0
            e_acfg_edid_idx = ACFG_EDID_IDX_AUTO; // 2
            break;

    #ifndef MT5583_MODEL
        case UI_EDID_SEL_2_1: // 1
            e_acfg_edid_idx = ACFG_EDID_IDX_2_1; // 1
            break;
    #endif

        case UI_EDID_SEL_1_4: // 5583=>1, 5691=> 2
            e_acfg_edid_idx = ACFG_EDID_IDX_1_4; // 0
            break;
    }

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} UI_EDID_Idx:%d => e_acfg_edid_idx:%d\n",
            __FUNCTION__, __LINE__, u8_UI_edid_idx, e_acfg_edid_idx ));
    );

    return e_acfg_edid_idx;
}

UINT8 acfg_cust_EDID_convert_ACFG_idx_to_UI_idx(UINT8 u8_ACFG_edid_idx)
{
    // Convert ACFG val to UI val
    UINT8 u8_UI_idx = UI_EDID_SEL_AUTO;

    switch(u8_ACFG_edid_idx)
    {
        default:
            DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} Error: Invalid u8_ACFG_edid_idx:%d !!!\n",
                __FUNCTION__, __LINE__, u8_ACFG_edid_idx ));
            break;

        case ACFG_EDID_IDX_AUTO: // 2
            u8_UI_idx = UI_EDID_SEL_AUTO; // 0
            break;

        case ACFG_EDID_IDX_1_4: // 0
            u8_UI_idx = UI_EDID_SEL_1_4; // 5583=>1, 5691=> 2
            break;

    #ifndef MT5583_MODEL
        case ACFG_EDID_IDX_2_1: // 1
            u8_UI_idx = UI_EDID_SEL_2_1; // 1
            break;
    #endif
    }

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} ACFG_EDID_Idx:%d => UI_edid_idx:%d\n",
            __FUNCTION__, __LINE__, u8_ACFG_edid_idx, u8_UI_idx ));
    );

    return u8_UI_idx;
}

//--------------------------------------------------------------------------------------------

// For input source UI idx -> ACFG/driver idx
static UINT8 g_au8_HDMI_Map_UI_to_ACFG[HDMI_PORT_NUM_MAX] =
{
    0, 1, 2, 3,
};
// For input source ACFG idx -> UI idx
static UINT8 g_au8_HDMI_Map_ACFG_to_UI[HDMI_PORT_NUM_MAX] =
{
    0, 1, 2, 3,
};

UINT8 acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(UINT8 u8_UI_hdmi_idx)
{
    if( u8_UI_hdmi_idx >= HDMI_PORT_NUM_MAX )
    {
         DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%s,%s,%d} Error: Invalid u8_UI_hdmi_idx:%d\n",
            __FILE__, __FUNCTION__, __LINE__, u8_UI_hdmi_idx ));
         return 0;
    }

    return g_au8_HDMI_Map_UI_to_ACFG[u8_UI_hdmi_idx];
}

UINT8 acfg_cust_HDMI_convert_ACFG_idx_to_UI_idx(UINT8 u8_ACFG_hdmi_idx)
{
    if( u8_ACFG_hdmi_idx >= HDMI_PORT_NUM_MAX )
    {
         DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%s,%s,%d} Error: Invalid u8_ACFG_hdmi_idx:%d\n",
            __FILE__, __FUNCTION__, __LINE__, u8_ACFG_hdmi_idx ));
         return 0;
    }

    return g_au8_HDMI_Map_ACFG_to_UI[u8_ACFG_hdmi_idx];
}

static UINT8 g_acfg_u8_hdmi_count = 4;
UINT8 acfg_cust_HDMI_get_count(void)
{
    return g_acfg_u8_hdmi_count;
}

#define DEBUG_HDMI_MAP(x)   x

INT32 acfg_cust_get_hdmi_map_ini(VOID)
{
    DBG_LOG_PRINT(("[ACFG][HDMI][MAP][EDID]{%s,%s,%d} \n", __FILE__, __FUNCTION__, __LINE__ ));

    CHAR  ac_file_path[] = "/config/hdmi_map.ini";
    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%s,%d} ac_file_path:%s\n", __FUNCTION__, __LINE__, ac_file_path )); );

    MI_HANDLE   h_hdmi_map_ini = NULL_HANDLE;

    INT32 i4_ret = MI_SYS_OpenConfigFile((MI_U8*)ac_file_path, &h_hdmi_map_ini);
    if (i4_ret != MI_OK)
    {
         DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%s,%s,%d} Error: Open config file(%s) error! i4_ret:%d\n",
            __FILE__, __FUNCTION__, __LINE__, ac_file_path, i4_ret ));
         return APP_CFGR_INTERNAL_ERR;
    }


    CHAR  pc_key[64] = {0};
    MI_SYS_ConfigData_t  t_cfg_data;

    // Get [HDMI_MAP] count  = ?;
    UINT8 u8_HDMI_count = 0;

    c_memset(&t_cfg_data, 0, sizeof(MI_SYS_ConfigData_t));
    t_cfg_data.eDataType = E_MI_SYS_CONFIG_DATA_TYPE_U32;

    c_snprintf(pc_key, 64, "HDMI_MAP:count" );
    i4_ret = MI_SYS_GetConfigData(h_hdmi_map_ini, (const MI_U8 *)pc_key, &t_cfg_data);
    if( i4_ret != MI_OK )
    {
        // Didn't get data
        DBG_LOG_PRINT(("[ACFG][HDMI][MAP] Error: pc_key: %s => MI_SYS_GetConfigData() failed!! i4_ret:%d\n\n",
            pc_key, i4_ret ));

        g_acfg_u8_hdmi_count = HDMI_PORT_NUM_MAX;
        DBG_LOG_PRINT(("[ACFG][HDMI][MAP] force HDMI count=%d\n\n", g_acfg_u8_hdmi_count ));
        //return APP_CFGR_INTERNAL_ERR;
    }
    else
    {
        if( (t_cfg_data.u32Data > HDMI_PORT_NUM_MAX) || (t_cfg_data.u32Data < 0) )
        {
            g_acfg_u8_hdmi_count = HDMI_PORT_NUM_MAX;
            // Get data wrong
            DBG_LOG_PRINT(("[ACFG][HDMI][MAP]Error: pc_key: %s => Invalid t_cfg_data.u32Data:%d, force HDMI count=%d\n\n",
                pc_key, t_cfg_data.u32Data, g_acfg_u8_hdmi_count ));
        }
        else
        {
            g_acfg_u8_hdmi_count = t_cfg_data.u32Data;
            DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] g_acfg_u8_hdmi_count=%d\n",
                g_acfg_u8_hdmi_count )); );
        }
    }


    // For input source UI idx -> ACFG/driver idx
    UINT8 au8_HDMI_Map_UI_to_ACFG[HDMI_PORT_NUM_MAX] =
    {
        0xFF, 0xFF, 0xFF, 0xFF,
    };
    // For input source ACFG idx -> UI idx
    UINT8 au8_HDMI_Map_ACFG_to_UI[HDMI_PORT_NUM_MAX] =
    {
        0xFF, 0xFF, 0xFF, 0xFF,
    };

    UINT8 u8_UI_HDMI_idx;
    UINT8 u8_acfg_hdmi_idx;

    //for(ui1_i=0; ui1_i < HDMI_PORT_NUM_MAX; ui1_i++)
    for(u8_UI_HDMI_idx=0; u8_UI_HDMI_idx < g_acfg_u8_hdmi_count; u8_UI_HDMI_idx++)
    {
        //DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] ui1_i:%d\n", ui1_i )); );

        /*------------------------------------------------------------------------------*/
        /* Get HDMI edid version default value form Customer.ini file */
        c_memset(&t_cfg_data, 0, sizeof(MI_SYS_ConfigData_t));
        t_cfg_data.eDataType = E_MI_SYS_CONFIG_DATA_TYPE_U32;

        c_snprintf(pc_key, 64, "HDMI%d:driverId", u8_UI_HDMI_idx+1);
        //DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] u8_UI_hdmi_idx:%d, pc_key: %s\n", u8_UI_hdmi_idx, pc_key )); );

        i4_ret = MI_SYS_GetConfigData(h_hdmi_map_ini, (const MI_U8 *)pc_key, &t_cfg_data);
        if (i4_ret == MI_OK)
        {
            if( t_cfg_data.u32Data == -1 )
            {
                // Didn't get data
                DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] u8_UI_HDMI_idx:%d, pc_key: %s => Invalid t_cfg_data.u32Data:%d\n",
                    u8_UI_HDMI_idx, pc_key, t_cfg_data.u32Data )); );
            }
            else
            {
                u8_acfg_hdmi_idx = t_cfg_data.u32Data - 1;

                DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] u8_UI_HDMI_idx:%d, pc_key: %s => t_cfg_data.u32Data:%d, u8_acfg_hdmi_idx:%d\n",
                    u8_UI_HDMI_idx, pc_key, t_cfg_data.u32Data, u8_acfg_hdmi_idx )); );

                if( u8_acfg_hdmi_idx >= HDMI_PORT_NUM_MAX )
                {
                    DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%s,%s,%d} Error: Invalid u8_acfg_hdmi_idx:%d\n",
                       __FILE__, __FUNCTION__, __LINE__, u8_acfg_hdmi_idx ));
                }
                else
                {
                    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] UI idx:%d <==> ACFG_idx:%d\n",
                        u8_UI_HDMI_idx, u8_acfg_hdmi_idx )); );

                    // For input source UI idx -> ACFG/driver idx
                    //g_au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx] = u8_acfg_hdmi_idx;
                    au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx] = u8_acfg_hdmi_idx;
                    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] g_au8_HDMI_Map_UI_to_ACFG[%d]=%d\n",
                        u8_UI_HDMI_idx, au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx] )); );

                    // For input source ACFG idx -> UI idx
                    au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] = u8_UI_HDMI_idx;
                    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] g_au8_HDMI_Map_ACFG_to_UI[%d]=%d\n",
                        u8_acfg_hdmi_idx, au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] )); );
                }
            }
        }
        else
        {
            //DBG_LOG_PRINT(("[ACFG_VIDEO]Get HDMI edid ver default value form ini failed! key:%s, i4_ret:%d\n", pc_key, i4_ret));
            DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] u8_UI_HDMI_idx:%d, pc_key: %s => rtn:%d\n", u8_UI_HDMI_idx, pc_key, i4_ret )); );
        }
    }

    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] au8_HDMI_Map_UI_to_ACFG[]={%d,%d,%d,%d}\n",
        au8_HDMI_Map_UI_to_ACFG[0], au8_HDMI_Map_UI_to_ACFG[1],
        au8_HDMI_Map_UI_to_ACFG[2], au8_HDMI_Map_UI_to_ACFG[3] ));
    );

    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP] au8_HDMI_Map_ACFG_to_UI[]={%d,%d,%d,%d}\n",
        au8_HDMI_Map_ACFG_to_UI[0], au8_HDMI_Map_ACFG_to_UI[1],
        au8_HDMI_Map_ACFG_to_UI[2], au8_HDMI_Map_ACFG_to_UI[3] ));
    );

    // Refine mapping and update to global
    for(u8_UI_HDMI_idx=0; u8_UI_HDMI_idx < HDMI_PORT_NUM_MAX; u8_UI_HDMI_idx++)
    {
        //DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} UI:%d\n", __LINE__, u8_UI_HDMI_idx )); );

        if( au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx] == 0xFF )
        {
            //DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} UI:%d => ACFG=0xFF\n", __LINE__, u8_UI_HDMI_idx )); );

            // Find first non-used acfg index.
            for(u8_acfg_hdmi_idx=0; u8_acfg_hdmi_idx < HDMI_PORT_NUM_MAX; u8_acfg_hdmi_idx++)
            {
                //DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} ACFG[%d]:%d\n", __LINE__, u8_acfg_hdmi_idx, au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] ));
                if( au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] == 0xFF )
                {
                    DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} Found UI_%d <==> ACFG_%d\n", __LINE__, u8_UI_HDMI_idx, u8_acfg_hdmi_idx ));

                    // non-used acfg index found~
                    // For input source UI idx -> ACFG/driver idx
                    au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx] = u8_acfg_hdmi_idx;

                    // For input source ACFG idx -> UI idx
                    au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] = u8_UI_HDMI_idx;

                    break;
                }
            }
        }

        u8_acfg_hdmi_idx = au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx];
        if( u8_acfg_hdmi_idx < HDMI_PORT_NUM_MAX )
        {
            // For input source UI idx -> ACFG/driver idx
            g_au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx] = au8_HDMI_Map_UI_to_ACFG[u8_UI_HDMI_idx];

            // For input source ACFG idx -> UI idx
            g_au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] = au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx];

            DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} _UI_to_ACFG[%d]=%d  => UI:%d\n", __LINE__,
                u8_UI_HDMI_idx, u8_acfg_hdmi_idx, au8_HDMI_Map_ACFG_to_UI[u8_acfg_hdmi_idx] )); );
        }
        else
        {
            DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} _UI_to_ACFG[%d]=%d\n", __LINE__,
                u8_UI_HDMI_idx, u8_acfg_hdmi_idx )); );
        }
    }

    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} g_au8_HDMI_Map_UI_to_ACFG[]={%d,%d,%d,%d}\n", __LINE__,
        g_au8_HDMI_Map_UI_to_ACFG[0], g_au8_HDMI_Map_UI_to_ACFG[1],
        g_au8_HDMI_Map_UI_to_ACFG[2], g_au8_HDMI_Map_UI_to_ACFG[3] ));
    );

    DEBUG_HDMI_MAP( DBG_LOG_PRINT(("[ACFG][HDMI][MAP]{%d} g_au8_HDMI_Map_ACFG_to_UI[]={%d,%d,%d,%d}\n", __LINE__,
        g_au8_HDMI_Map_ACFG_to_UI[0], g_au8_HDMI_Map_ACFG_to_UI[1],
        g_au8_HDMI_Map_ACFG_to_UI[2], g_au8_HDMI_Map_ACFG_to_UI[3] ));
    );

    return APP_CFGR_OK;
}

#if ACFG_HDMI_DIFF_EDID_DEFALUT
// 2021-05-28.MVP-4052: Default HDMI 2.1 Gaming Port For -J 5695

extern UINT8 ui1_g_cust_hdmi_mode_def;

void acfg_cust_HDMI_setup_EDID_default(void)
{
    //DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} \n", __FUNCTION__, __LINE__ ));

    if( a_cfg_cust_Is_CurModel_2020() ) // old model no need~
    {
        return;
    }


    //EnuCusModelSeries eCusModel = a_cfg_cust_get_CurModelSeries();
    //ACFG_DEBUG_HDMI_EDID(
    //    DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} eCusModel:%d \n", __FUNCTION__, __LINE__, eCusModel ));  );

    BOOL bNeedToModify = FALSE;
    UINT8 au8_acfg_edid_default_by_UI_hdmi_idx[4]={0};

    if( a_cfg_cust_Is_CurModel_P_series() )
    {
        ACFG_DEBUG_HDMI_EDID(
            DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} Model is P series \n", __FUNCTION__, __LINE__ ));
        );

        // [5695 Pxxx-J series]
        // HDMI1 -> Auto
        // HDMI2 -> Auto
        // HDMI3 -> 2.1
        // HDMI4 -> 2.1
        bNeedToModify = TRUE;
        au8_acfg_edid_default_by_UI_hdmi_idx[0] = ACFG_EDID_IDX_AUTO;
        au8_acfg_edid_default_by_UI_hdmi_idx[1] = ACFG_EDID_IDX_AUTO;
        au8_acfg_edid_default_by_UI_hdmi_idx[2] = ACFG_EDID_IDX_2_1;
        au8_acfg_edid_default_by_UI_hdmi_idx[3] = ACFG_EDID_IDX_2_1;
    }
    else if( a_cfg_cust_Is_CurModel_OLED() /*(eCusModel == CUS_MODEL_2021_95_OLED)*/ ) // 17, OLED**-J*:
    {
        ACFG_DEBUG_HDMI_EDID(
            DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} Model is OLED \n", __FUNCTION__, __LINE__ ));
        );

        // [5695 OLED]
        // HDMI1 -> Auto
        // HDMI2 -> 2.1
        // HDMI3 -> 2.1
        // HDMI4 -> Auto
        bNeedToModify = TRUE;
        au8_acfg_edid_default_by_UI_hdmi_idx[0] = ACFG_EDID_IDX_AUTO;
        au8_acfg_edid_default_by_UI_hdmi_idx[1] = ACFG_EDID_IDX_2_1;
        au8_acfg_edid_default_by_UI_hdmi_idx[2] = ACFG_EDID_IDX_2_1;
        au8_acfg_edid_default_by_UI_hdmi_idx[3] = ACFG_EDID_IDX_AUTO;
    }
    /*else if( (eCusModel == CUS_MODEL_2021_83_2K_D_FHD) ) // 9, D**f*-J**: D24f4-J01/D24f-J09
    {
        bNeedToModify = TRUE;
        au8_acfg_edid_default_by_UI_hdmi_idx[0] = ACFG_EDID_IDX_AUTO;
        au8_acfg_edid_default_by_UI_hdmi_idx[1] = ACFG_EDID_IDX_1_4;
        au8_acfg_edid_default_by_UI_hdmi_idx[2] = ACFG_EDID_IDX_2_1;
        au8_acfg_edid_default_by_UI_hdmi_idx[3] = ACFG_EDID_IDX_2_1;
    }
    */

    if( bNeedToModify )
    {
        UINT8 u8_UI_hdmi_idx;
        UINT8 u8_ACFG_hdmi_idx; // ACFG index is the same as driver(HW) index
        UINT8 u8_acfg_edid_idx;

        ui1_g_cust_hdmi_mode_def = 0;

        //for( u8_UI_hdmi_idx = 0; u8_UI_hdmi_idx < 4; u8_UI_hdmi_idx += 1 )
        for( u8_ACFG_hdmi_idx = 0; u8_ACFG_hdmi_idx < 4; u8_ACFG_hdmi_idx += 1 )
        {
            //u8_ACFG_hdmi_idx = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(u8_UI_hdmi_idx);
            u8_UI_hdmi_idx = acfg_cust_HDMI_convert_ACFG_idx_to_UI_idx(u8_ACFG_hdmi_idx);

            if( u8_UI_hdmi_idx < 4 )
            {
                u8_acfg_edid_idx = au8_acfg_edid_default_by_UI_hdmi_idx[u8_UI_hdmi_idx];

                ui1_g_cust_hdmi_mode_def |= ( (u8_acfg_edid_idx&3) << (u8_ACFG_hdmi_idx*2) );

                ACFG_DEBUG_HDMI_EDID(
                    DBG_LOG_PRINT(("[ACFG][HDMI][EDID] {u8_ACFG_hdmi_idx:%d, u8_UI_hdmi_idx:%d} u8_acfg_edid_idx:%d(%s) => ui1_g_cust_hdmi_mode_def:0x%X\n",
                        u8_ACFG_hdmi_idx, u8_UI_hdmi_idx,
                        u8_acfg_edid_idx, acfg_cust_get_acfg_edid_name((EnuAcfgEdidIdx)u8_acfg_edid_idx),
                        ui1_g_cust_hdmi_mode_def));
                );
            }
        }
    }

}
#endif


#endif

BOOL b_is_detected_spd_info = FALSE;

void acfg_cust_SPD_Info_handler(void)
{
    INT32 i4_ret;
    ISL_REC_T stISL_REC = {0};
    BOOL bIsSrcHDMI = FALSE;
    BOOL bIsSrcDVI = FALSE;
    DRV_CUST_OPERATION_INFO_T t_op_info={0};
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8  spd_info[30] = {0};
    SIZE_T z_size = sizeof(spd_info);
    UINT16  ui2_pic_mode;
    UINT16  ui2_gll_en;
    UINT16  ui2_vrr_en;

    b_is_detected_spd_info = FALSE;

    i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &stISL_REC);
    if(i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("{%s,%d} Error: a_tv_get_isl_rec_by_snk_name fail!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
        return;
    }

    // Check input_source ...
    if( (stISL_REC.e_src_type != INP_SRC_TYPE_AV) )
    {
        DBG_LOG_PRINT(("{%s,%d} Not INP_SRC_TYPE_AV \n", __FUNCTION__, __LINE__ ));
        return;
    }

    if( stISL_REC.t_avc_info.e_video_type == DEV_AVC_HDMI ) // HDMI
    {
        bIsSrcHDMI = TRUE;
    }
    else if( stISL_REC.t_avc_info.e_video_type == DEV_AVC_DVI) // DVI
    {
        bIsSrcDVI = TRUE;
    }
    else
    {
        DBG_LOG_PRINT(("{%s,%d} Not HDMI~ \n", __FUNCTION__, __LINE__ ));
        return;
    }

    // Check has signal ...
    if( (a_common_setting_is_signal_loss() == TRUE) || (a_common_setting_is_video_block() == TRUE) )
    {
        DBG_LOG_PRINT(("{%s:%d} NoSignal or VideoBlock \n", __FUNCTION__, __LINE__));
        return;
    }

    // Get HDMI port...
    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    if( u8CurHdmi_UI_Idx >= 4 )
    {
        DBG_LOG_PRINT(("{%s,%d} u8CurHdmi_UI_Idx >= 4 \n", __FUNCTION__, __LINE__ ));
        return;
    }

    //Get SPD info
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;

    DBG_LOG_PRINT(("{%s,%d} u8CurHdmi_UI_Idx = %d\n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx));
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_SPD_INFO + u8CurHdmi_UI_Idx;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)spd_info;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("{%s,%d} c_rm_get_comp fail, i4_ret : %d \n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    DBG_LOG_PRINT(("{%s,%d} spd_info = {%s}\n",__FUNCTION__, __LINE__, (char*)spd_info));

    if((c_strncmp(spd_info,"NVIDIA\0",8) == 0)   // Vendor Name: "NVIDIA\0x00\0x00"
        && (spd_info[24] == 0x09))               // Source Code: 0x09(PC General)
    {
        b_is_detected_spd_info = TRUE;

        // Set & Update Picture mode
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&ui2_pic_mode);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        if(ui2_pic_mode != APP_CFG_PIC_MODE_GAME)
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),APP_CFG_PIC_MODE_GAME);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        }

        // Set & Update Game Low Latency
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &ui2_gll_en);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        if((a_cfg_cust_is_support_game_low_latency())
           #if(VZO_DV__GLL_CONTROL_BY_DV_GAME)
           && (a_cfg_get_hdr_type() != SCC_VID_PQ_DOVI)
           #endif
           && (ui2_gll_en != ACFG_CUST_GAME_LOW_LATENCY_ON))
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY),ACFG_CUST_GAME_LOW_LATENCY_ON);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = acfg_cust_video_update_GLL_all(TRUE);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        }

        // Set & Update Variable Refresh Rate
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &ui2_vrr_en);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
        if((a_cfg_cust_is_variable_refresh_rate_support())
            && (ui2_vrr_en != ACFG_CUST_COMMON_ON))
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE),ACFG_CUST_COMMON_ON);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE));
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        }

        // Set & Update HDMI Mode : if mt5583--> Auto, else --> hdmi 2.1
        UINT8 u8_UI_Hdmi_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();

        UINT8 u8_acfg_hdmi_idx = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(u8_UI_Hdmi_Idx);
#if( ENABLE_HDMI_EDID_NEW_METHOD )
        INT32 i4_hdmi_idx = u8_acfg_hdmi_idx;
#else
        INT32 i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
#endif
        if( (i4_hdmi_idx < 0) || (i4_hdmi_idx > 3) )
        {
            DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} Error: Invalid i4_hdmi_idx:%d => skip!\n",
                __FUNCTION__, __LINE__, i4_hdmi_idx ));
            return;
        }

        // Convert UI edid to ACFG edid index ...
#if( ENABLE_HDMI_EDID_NEW_METHOD )
  #ifdef MT5583_MODEL
        EnuAcfgEdidIdx e_acfg_edid_idx = acfg_cust_EDID_convert_UI_idx_to_acfg_idx(UI_EDID_SEL_AUTO);
  #else
        EnuAcfgEdidIdx e_acfg_edid_idx = acfg_cust_EDID_convert_UI_idx_to_acfg_idx(UI_EDID_SEL_2_1);
  #endif
        inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, e_acfg_edid_idx);
#else
  #ifdef MT5583_MODEL
        inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, ACFG_EDID_IDX_AUTO);
  #else
        inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, ACFG_EDID_IDX_2_1);
  #endif
#endif
    }
    else
    {
        DBG_LOG_PRINT(("{%s:%d} invalid spd info\n", __FUNCTION__, __LINE__));
        return;
    }
    DBG_LOG_PRINT(("{%s:%d} b_is_detected_spd_info == %d, spd info handler finish!!!\n", __FUNCTION__, __LINE__, b_is_detected_spd_info));
    return;
}


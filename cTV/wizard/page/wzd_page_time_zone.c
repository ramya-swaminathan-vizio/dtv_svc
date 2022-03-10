/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright(C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights(including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights(including without limitation, patent, copyright, and      *
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
 * of certain softwares relating to Receiver's product(s)(the "Services").   *
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
 * then current rules of the International Chamber of Commerce(ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/dst/a_dst_custom.h"

#include "wizard/wzd.h"
#include "wizard/wzd_dbg.h"


/* select box frame. inside the layout frame */
#define WZD_SB_FRM_X                       (0)
#define WZD_SB_FRM_Y                       (10 * WZD_UI_RATIO_W)
#define WZD_SB_FRM_W                       (LAYOUT_FRM_W - 2 * WZD_SB_FRM_X)
#define WZD_SB_FRM_H                       (640 * WZD_UI_RATIO_W)

#define WZD_SB_BTN_GAP                     (-268 * WZD_UI_RATIO_W)

#define WZD_SB_BTN_Y                       (0)
#define WZD_SB_BTN_W                       (410 * WZD_UI_RATIO_W)
#define WZD_SB_BTN_H                       (386 * WZD_UI_RATIO_W)

/* select box buttons */
#define WZD_SB_BTN_MARGINS                 ((WZD_SB_FRM_W - 5 * WZD_SB_BTN_W - 4 * WZD_SB_BTN_GAP)/2)

#define WZD_SB_BTN_01_X                    (WZD_SB_BTN_MARGINS)
#define WZD_SB_BTN_02_X                    (WZD_SB_BTN_01_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_03_X                    (WZD_SB_BTN_02_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_04_X                    (WZD_SB_BTN_03_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_05_X                    (WZD_SB_BTN_04_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_06_X                    (WZD_SB_BTN_MARGINS)
#define WZD_SB_BTN_07_X                    (WZD_SB_BTN_01_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_08_X                    (WZD_SB_BTN_02_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_09_X                    (WZD_SB_BTN_03_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)
#define WZD_SB_BTN_10_X                    (WZD_SB_BTN_04_X + WZD_SB_BTN_W + WZD_SB_BTN_GAP)

#define WZD_SB_BTN_LINE1_Y                 WZD_SB_BTN_Y - 20 * WZD_UI_RATIO_W
#define WZD_SB_BTN_LINE2_Y                 WZD_SB_BTN_Y + WZD_SB_BTN_H - 265 * WZD_UI_RATIO_W

/* select box buttons layout */
#define  WZD_SB_BTN_GET_RECTS()                                                                            	  \
{                                                                                               			  \
    {WZD_SB_BTN_01_X, WZD_SB_BTN_LINE1_Y, WZD_SB_BTN_01_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE1_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_02_X, WZD_SB_BTN_LINE1_Y, WZD_SB_BTN_02_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE1_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_03_X, WZD_SB_BTN_LINE1_Y, WZD_SB_BTN_03_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE1_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_04_X, WZD_SB_BTN_LINE1_Y, WZD_SB_BTN_04_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE1_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_05_X, WZD_SB_BTN_LINE1_Y, WZD_SB_BTN_05_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE1_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_06_X, WZD_SB_BTN_LINE2_Y, WZD_SB_BTN_06_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE2_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_07_X, WZD_SB_BTN_LINE2_Y, WZD_SB_BTN_07_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE2_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_08_X, WZD_SB_BTN_LINE2_Y, WZD_SB_BTN_08_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE2_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_09_X, WZD_SB_BTN_LINE2_Y, WZD_SB_BTN_09_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE2_Y + WZD_SB_BTN_H}, \
    {WZD_SB_BTN_10_X, WZD_SB_BTN_LINE2_Y, WZD_SB_BTN_10_X + WZD_SB_BTN_W, WZD_SB_BTN_LINE2_Y + WZD_SB_BTN_H}, \
}

/* time zone setup manually dlg editbox size */
#define  WZD_MANUALLY_DLG_EB_X                          ((LAYOUT_FRM_W - WZD_MANUALLY_DLG_EB_W)/2)
#define  WZD_MANUALLY_DLG_EB_Y                          ((LAYOUT_FRM_H - WZD_MANUALLY_DLG_EB_H)/2 - 90 * WZD_UI_RATIO_W)
#define  WZD_MANUALLY_DLG_EB_W                          (368 * WZD_UI_RATIO_W)
#define  WZD_MANUALLY_DLG_EB_H                          (85 * WZD_UI_RATIO_W)

/* Enum the box of the select box */
typedef enum _WZD_SB_BTN_INDEX_T
{
    WZD_SB_BTN_01 = 0,
    WZD_SB_BTN_02,
    WZD_SB_BTN_03,
    WZD_SB_BTN_04,
    WZD_SB_BTN_05,
    WZD_SB_BTN_06,
    WZD_SB_BTN_07,
    WZD_SB_BTN_08,
    WZD_SB_BTN_09,
    WZD_SB_BTN_10, 
    WZD_SB_BTN_COUNT  /* 10 */
}WZD_SB_BTN_INDEX_T;

typedef struct _WZD_SB_BTN_T
{
    HANDLE_T            h_sb_btn_frm;
    HANDLE_T            h_sb_icon_1;
    HANDLE_T            h_sb_icon_2;
    HANDLE_T            h_sb_text;  
}WZD_SB_BTN_T;

typedef struct _WZD_TIME_ZONE_PAGE_DATA_T
{
	HANDLE_T                    h_desc_txt;
	HANDLE_T					h_sb_frm; 
    WZD_SB_BTN_T				t_sb_btn[WZD_SB_BTN_COUNT];
	WZD_SB_BTN_INDEX_T          ui1_sb_idx;

	HANDLE_T            		h_manually_dlg;
    HANDLE_T            		h_manually_dlg_eb;
}WZD_TIME_ZONE_PAGE_DATA_T;

static WZD_TIME_ZONE_PAGE_DATA_T t_g_wzd_time_zone_page_data;

/*----------------------------------------------------------------------------
 * Name:    _wzd_time_zone_code_is_valid
 * Description: a number string is valid.
 * Inputs:  ps          A NULL-terminated string.
 * Outputs: -
 * Returns: The number.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_time_zone_code_is_valid (const CHAR* ps)
{
	BOOL b_valid = TRUE;

	if (c_strlen(ps) == 0)
    {
        b_valid = FALSE;
    }
	else if(c_strlen(ps) == 1 && *ps == '-')
	{
		b_valid = FALSE;
	}

    return b_valid;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_time_zone_atoi
 * Description: Convert a number string to a number.
 * Inputs:  ps          A NULL-terminated string.
 * Outputs: -
 * Returns: The number.
 ----------------------------------------------------------------------------*/
static INT32  _wzd_time_zone_atoi (const CHAR* ps)
{
    INT32   i4_total = 0;
	BOOL	b_negative = FALSE;

    while (*ps != 0)
    {
        if(*ps == '-')
        {
        	b_negative = TRUE;
            ps ++; /* get next char */
        }
		else if (*ps >= '0' && *ps <= '9')
        {
            i4_total = 10 * i4_total + (*ps - '0'); /* accumulate digit */
            ps ++; /* get next char */
        }
		else
		{
			return 255;
		}
    }

	if (i4_total > 0 && b_negative)
	{
		i4_total = -1 * i4_total;
	}

    return i4_total;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_set_data_by_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_set_data_by_idx (UINT8 ui1_idx)
{
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;

    a_cfg_get_time_zone_data(&t_tz_offset, &b_dls);

    switch (ui1_idx)
    {
    case APP_CFG_CUST_TZ_ALASKA:		/*Alaska */
        t_tz_offset = -9 * 3600;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_HAWAII:		/*Hawaii */
        t_tz_offset = -10 * 3600;
		b_dls = FALSE;
        break;
    case APP_CFG_CUST_TZ_PACIFIC_TIME:	/*Pacific */
        t_tz_offset = -8 * 3600;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_MOUNTAIN_TIME:	/*Mountain */
        t_tz_offset = -7 * 3600;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_CENTRAL_TIME:	/*Central */
        t_tz_offset = -6 * 3600;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_EASTERN_TIME:	/*Eastern */
        t_tz_offset = -5 * 3600;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_ATLANTIC_TIME:	/*Atlantic */
        t_tz_offset = -4 * 3600;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_NEWFOUNDLAND:	/*Newfounland */
        t_tz_offset = -7 * 3600 / 2;
		b_dls = TRUE;
        break;
    case APP_CFG_CUST_TZ_INDIANA:		/*Indiana */
        t_tz_offset = -5 * 3600;
		b_dls = FALSE;
        break;
    case APP_CFG_CUST_TZ_ARIZONA:		/*Arizona */
        t_tz_offset = -7 * 3600;
		b_dls = FALSE;
        break;
    default:
        ui1_idx     = APP_CFG_CUST_TZ_PACIFIC_TIME;
        t_tz_offset = -8 * 3600;
		b_dls = TRUE;
        break;
    }

	a_cfg_custom_set_timezone_idx(ui1_idx);
    a_cfg_set_time_zone_data(t_tz_offset, b_dls);
	a_cfg_custom_set_dst(DST_AUTO);
	a_cfg_custom_set_tz_select(1);
	a_cfg_update_time_zone();
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_set_data_by_offset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_set_data_by_offset (INT32 i4_offset)
{
    TIME_T      t_tz_offset = 0;
    UINT8       ui1_tz_idx = 0;
    BOOL        b_dls       = TRUE;
    UINT16      ui2_val = DST_OFF;

	if (i4_offset < -12 || i4_offset > 12)
	{
		return;
	}
	
	t_tz_offset = i4_offset * 3600;
	switch (i4_offset)
    {
    case -10:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 0;      /* Hawaii */
        break;
    case -9:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 1;      /* Alaska */
        break;
    case -8:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 2;      /* Pacific */
        break;
    case -7:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 3;      /* Mountain */
        break;
    case -6:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 5;      /* Central */
        break;
    case -5:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 7;      /* Eastern */
        break;
    case -4:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 8;      /* Atlantic */
        break;
    case -3:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 10;      /* -3 */
        break;
    case -2:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 11;      /* -2 */
        break;
    case -1:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 12;      /* -1 */
        break;
    case 0:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 13;      /* London */
        break;
    case 1:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 14;      /* 1 */
        break;
    case 2:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 15;      /* 2 */
        break;
    case 3:
        ui1_tz_idx = 16;      /* 3 */
        break;
    case 4:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 17;      /* 4 */
        break;
    case 5:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 18;      /* 5 */
        break;
    case 6:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 19;      /* 6 */
       break;
    case 7:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 20;      /* 7 */
       break;
    case 8:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 21;      /* 8 */
        break;
    case 9:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 22;      /* 9 */
        break;
    case 10:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 23;      /* Guam */
        break;
    case 11:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 24;      /* 11 */
        break;
    case 12:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 25;      /* 12 */
        break;
    case -12:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 26;      /* -12 */
        break;
    case -11:
        b_dls = FALSE;
        ui2_val = DST_OFF;
        ui1_tz_idx = 27;      /* -11 */
        break;
    default:
        b_dls = TRUE;
        ui2_val = DST_AUTO;
        ui1_tz_idx = 2;      /* Pacific */
        break;

    }

	a_cfg_custom_set_timezone_idx(ui1_tz_idx);
    a_cfg_set_time_zone_data(t_tz_offset, b_dls);
    a_cfg_custom_set_dst(ui2_val);
    a_cfg_update_time_zone();

	a_cfg_custom_set_tz_select(1);
}

#ifdef WZD_TIMEZONE_SORT_WITH_NAME
/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_get_mlm_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static UINT16 _wzd_time_zone_get_mlm_idx(UINT16    ui2_idx)
{
    UINT16 ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_PAC;

	/* sort with name */
	switch (ui2_idx)
    {
    case 0:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ALA; /*Alaska*/
        break;
    case 1:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ARI; /*Arizona */
        break;
    case 2:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ATLA; /*Atlantic */
        break;
    case 3:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_CEN; /*Central */
        break;
    case 4:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_EAS; /*Eastern */
        break;
    case 5:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_HAW; /*Hawaii */
        break;
    case 6:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_IND; /*Indiana */
        break;
    case 7:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_MNT; /*Mountain */
        break;
    case 8:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_NFL; /*Newfounland */
        break;
    case 9:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_PAC; /*Pacific */
        break;
    default:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ALA;
        break;
    }

    return ui2_mlm_key_idx;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_remap_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static UINT8 _wzd_time_zone_remap_idx (UINT8 ui1_idx)
{
    UINT8 ui1_map_idx = 0;

	/* remap */
	switch (ui1_idx)
    {
    case 0:
        ui1_map_idx = APP_CFG_CUST_TZ_ALASKA; /*Alaska*/
        break;
    case 1:
        ui1_map_idx = APP_CFG_CUST_TZ_ARIZONA; /*Arizona */
        break;
    case 2:
        ui1_map_idx = APP_CFG_CUST_TZ_ATLANTIC_TIME; /*Atlantic */
        break;
    case 3:
        ui1_map_idx = APP_CFG_CUST_TZ_CENTRAL_TIME; /*Central */
        break;
    case 4:
        ui1_map_idx = APP_CFG_CUST_TZ_EASTERN_TIME; /*Eastern */
        break;
    case 5:
        ui1_map_idx = APP_CFG_CUST_TZ_HAWAII; /*Hawaii */
        break;
    case 6:
        ui1_map_idx = APP_CFG_CUST_TZ_INDIANA; /*Indiana */
        break;
    case 7:
        ui1_map_idx = APP_CFG_CUST_TZ_MOUNTAIN_TIME; /*Mountain */
        break;
    case 8:
        ui1_map_idx = APP_CFG_CUST_TZ_NEWFOUNDLAND; /*Newfounland */
        break;
    case 9:
        ui1_map_idx = APP_CFG_CUST_TZ_PACIFIC_TIME; /*Pacific */
        break;
    default:
        ui1_map_idx = APP_CFG_CUST_TZ_UNKNOWN;
        break;
    }

    return ui1_map_idx;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_remap_acfg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static UINT8 _wzd_time_zone_remap_acfg (UINT8 ui1_acfg_idx)
{
    UINT8 ui1_idx = 0;

	/* remap */
	switch (ui1_acfg_idx)
    {
    case APP_CFG_CUST_TZ_ALASKA:
        ui1_idx = 0; /*Alaska*/
        break;
    case APP_CFG_CUST_TZ_ARIZONA:
        ui1_idx = 1; /*Arizona */
        break;
    case APP_CFG_CUST_TZ_ATLANTIC_TIME:
        ui1_idx = 2; /*Atlantic */
        break;
    case APP_CFG_CUST_TZ_CENTRAL_TIME:
        ui1_idx = 3; /*Central */
        break;
    case APP_CFG_CUST_TZ_EASTERN_TIME:
        ui1_idx = 4; /*Eastern */
        break;
    case APP_CFG_CUST_TZ_HAWAII:
        ui1_idx = 5; /*Hawaii */
        break;
    case APP_CFG_CUST_TZ_INDIANA:
        ui1_idx = 6; /*Indiana */
        break;
    case APP_CFG_CUST_TZ_MOUNTAIN_TIME:
        ui1_idx = 7; /*Mountain */
        break;
    case APP_CFG_CUST_TZ_NEWFOUNDLAND:
        ui1_idx = 8; /*Newfounland */
        break;
    case APP_CFG_CUST_TZ_PACIFIC_TIME:
        ui1_idx = 9; /*Pacific */
        break;
    default:
        ui1_idx = 10;
        break;
    }

    return ui1_idx;
}
#else
/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_get_mlm_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static UINT16 _wzd_time_zone_get_mlm_idx(UINT16    ui2_idx)
{
    UINT16 ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_PAC;

    switch (ui2_idx)
    {
    case 0:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_PAC; /*Pacific */
        break;
    case 1:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_MNT; /*Mountain */
        break;
    case 2:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ARI; /*Arizona */
        break;
    case 3:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_CEN; /*Central */
        break;
    case 4:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_IND; /*Indiana */
        break;
    case 5:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_EAS; /*Eastern */
        break;
    case 6:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ATLA; /*Atlantic */
        break;
    case 7:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_NFL; /*Newfounland */
        break;
    case 8:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_HAW; /*Hawaii */
        break;
    case 9:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_ALA; /*Alaska*/
        break;
    default:
        ui2_mlm_key_idx = MLM_WZD_KEY_TIME_ZONE_PAC; /*Pacific */
        break;
    }

    return ui2_mlm_key_idx;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_remap_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static UINT8 _wzd_time_zone_remap_idx (UINT8 ui1_idx)
{
    UINT8 ui1_map_idx = 0;

	/* remap */
	switch (ui1_idx)
    {
    case 0:
        ui1_map_idx = APP_CFG_CUST_TZ_PACIFIC_TIME; /*Pacific */
        break;
    case 1:
        ui1_map_idx = APP_CFG_CUST_TZ_MOUNTAIN_TIME; /*Mountain */
        break;
    case 2:
        ui1_map_idx = APP_CFG_CUST_TZ_ARIZONA; /*Arizona */
        break;
    case 3:
        ui1_map_idx = APP_CFG_CUST_TZ_CENTRAL_TIME; /*Central */
        break;
    case 4:
        ui1_map_idx = APP_CFG_CUST_TZ_INDIANA; /*Indiana */
        break;
    case 5:
        ui1_map_idx = APP_CFG_CUST_TZ_EASTERN_TIME; /*Eastern */
        break;
    case 6:
        ui1_map_idx = APP_CFG_CUST_TZ_ATLANTIC_TIME; /*Atlantic */
        break;
    case 7:
        ui1_map_idx = APP_CFG_CUST_TZ_NEWFOUNDLAND; /*Newfounland */
        break;
    case 8:
        ui1_map_idx = APP_CFG_CUST_TZ_HAWAII; /*Hawaii */
        break;
    case 9:
        ui1_map_idx = APP_CFG_CUST_TZ_ALASKA; /*Alaska*/
        break;
    default:
        ui1_map_idx = APP_CFG_CUST_TZ_UNKNOWN;
        break;
    }

    return ui1_map_idx;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_remap_acfg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static UINT8 _wzd_time_zone_remap_acfg (UINT8 ui1_acfg_idx)
{
    UINT8 ui1_idx = 0;

	/* remap */
	switch (ui1_acfg_idx)
    {
    case APP_CFG_CUST_TZ_ALASKA:
        ui1_idx = 9; /*Alaska*/
        break;
    case APP_CFG_CUST_TZ_ARIZONA:
        ui1_idx = 2; /*Arizona */
        break;
    case APP_CFG_CUST_TZ_ATLANTIC_TIME:
        ui1_idx = 6; /*Atlantic */
        break;
    case APP_CFG_CUST_TZ_CENTRAL_TIME:
        ui1_idx = 3; /*Central */
        break;
    case APP_CFG_CUST_TZ_EASTERN_TIME:
        ui1_idx = 5; /*Eastern */
        break;
    case APP_CFG_CUST_TZ_HAWAII:
        ui1_idx = 8; /*Hawaii */
        break;
    case APP_CFG_CUST_TZ_INDIANA:
        ui1_idx = 4; /*Indiana */
        break;
    case APP_CFG_CUST_TZ_MOUNTAIN_TIME:
        ui1_idx = 1; /*Mountain */
        break;
    case APP_CFG_CUST_TZ_NEWFOUNDLAND:
        ui1_idx = 7; /*Newfounland */
        break;
    case APP_CFG_CUST_TZ_PACIFIC_TIME:
        ui1_idx = 0; /*Pacific */
        break;
    default:
        ui1_idx = 10;
        break;
    }

    return ui1_idx;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_create_icon
 *
 * Description: 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_create_icon(HANDLE_T     h_parent,
                                        HANDLE_T*    ph_widget,
                                    	GL_RECT_T*   pt_rect)
{   
    RET_ON_ERR (c_wgl_create_widget(h_parent,
                              HT_WGL_WIDGET_ICON,
                              WGL_CONTENT_ICON_DEF,
                              WGL_BORDER_NULL,
                              pt_rect,
                              NULL,
                              255,
                              (VOID*)WGL_STL_GL_NO_BK,
                              NULL,
                              ph_widget));

    RET_ON_ERR (c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_ICON_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL));

    RET_ON_ERR (c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_create_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_create_text(
                           HANDLE_T                 h_parent,
                           wgl_widget_proc_fct      pf_wdgt_proc,
                           GL_RECT_T*               pt_rect,
                           UINT32                   ui4_style,
                           WGL_FONT_INFO_T*         pt_fnt_info,
                           UINT8                    ui1_align,
                           WGL_COLOR_INFO_T*        pt_color_bk,
                           WGL_COLOR_INFO_T*        pt_color_fg,
                           WGL_INSET_T*             pt_inset,
                           HANDLE_T*                ph_txt)
{
    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_txt));

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (pt_fnt_info),
                              NULL));

    /* set content inset */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (pt_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (pt_color_bk)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_fg)));    

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_txt, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_desc_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/ 
static INT32 _wzd_time_zone_desc_create(HANDLE_T     h_parent)
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
    UINT32              		i4_ret = WZDR_OK;
    UINT32              		ui4_style = 0;
    UINT8               		ui1_align = 0;
	GL_RECT_T   				t_rect;
    WGL_FONT_INFO_T     		t_fnt_info;
    WGL_COLOR_INFO_T    		t_color_info_bg, t_color_info_fg;
    WGL_INSET_T         		t_inset;
    CHAR*               		s_font_name = wzd_view_get_font_name();

    /* description text create */
    c_memset (&t_rect, 0, sizeof (GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      LAYOUT_FRM_W,
                      80 * WZD_UI_RATIO_W);

    /* set font theme */   
    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_begin_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_begin_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_begin_txt);

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = _wzd_time_zone_create_text(
                h_parent,
                NULL,
                &t_rect,
                ui4_style,
                &t_fnt_info,
                ui1_align,
                &t_color_info_bg,
                &t_color_info_fg,
                &t_inset,
                &pt_this->h_desc_txt);           
    RET_ON_ERR (i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_create_sb_frm
 *
 * Description: This function creates a select box frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_create_sb_frm (HANDLE_T  h_parent)
                                              
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
    GL_RECT_T           		t_rect;
    WGL_COLOR_INFO_T    		t_color_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SB_FRM_X,
                      WZD_SB_FRM_Y,
                      WZD_SB_FRM_W,
                      WZD_SB_FRM_H);

    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     NULL,
                                     &pt_this->h_sb_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_sb_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_this->h_sb_frm, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_sb_btns_set_all_unfloat
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_sb_btns_set_all_unfloat(VOID)
{
    WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
	UINT8 						ui1_idx = 0;
   
    for (ui1_idx = 0; ui1_idx < WZD_SB_BTN_COUNT; ui1_idx++)
    {
        RET_ON_ERR (c_wgl_float(pt_this->t_sb_btn[ui1_idx].h_sb_btn_frm, FALSE, FALSE)); 
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_sb_losed_foucs_box_txt_initial
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_sb_losed_foucs_box_txt_initial(VOID)
{
    WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
    HANDLE_T                    h_txt_handle = NULL_HANDLE; 
    WGL_COLOR_INFO_T            t_color_txt;
    WGL_FONT_INFO_T             t_fnt_info;

    h_txt_handle = pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_text;

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));
                                              
    return WZDR_OK;                      
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_sb_losed_foucs_box_txt_hlt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_sb_losed_foucs_box_txt_hlt(VOID)
{
    WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
    HANDLE_T                    h_txt_handle = NULL_HANDLE; 
    WGL_COLOR_INFO_T            t_color_txt;
	WGL_FONT_INFO_T             t_fnt_info;

    h_txt_handle = pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_text;

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

	/* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));

    return WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_set_btn_contents
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_set_btn_contents (VOID)
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
	UINT16      				ui2_mlm_key_idx = 0;
    INT32               		i4_ret = 0;
    UINT8               		ui1_idx = 0;
	GL_RECT_T           		t_rect_text = {0};
    WGL_IMG_INFO_T      		t_img_info;
	WGL_HIMG_TPL_T      		h_checkmark_icon;
	UINT16         				ui2_tz_select_status = 0;

	/* get time zone setup status */
	a_cfg_custom_get_tz_select(&ui2_tz_select_status);
   
    for( ui1_idx = 0 ; ui1_idx < WZD_SB_BTN_COUNT ; ui1_idx ++ )
    {
        /* set select box icon_1 */
		if (0 == ui2_tz_select_status)
		{
			h_checkmark_icon = NULL_HANDLE;
		}
		else
		{
			h_checkmark_icon = (pt_this->ui1_sb_idx == ui1_idx) ? h_g_wzd_img_checkmark_green_small : NULL_HANDLE;
		}

        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_disable   = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

        i4_ret = c_wgl_do_cmd((pt_this->t_sb_btn[ui1_idx]).h_sb_icon_1,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));                 
        RET_ON_ERR(i4_ret);
        
        /* set select box icon_2 */
        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        t_img_info.e_type = WGL_IMG_SET_BASIC;
        t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;

        i4_ret = c_wgl_do_cmd((pt_this->t_sb_btn[ui1_idx]).h_sb_icon_2,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));                 
        RET_ON_ERR(i4_ret);

        /* set select box text */  
		ui2_mlm_key_idx = _wzd_time_zone_get_mlm_idx(ui1_idx);
        i4_ret =  c_wgl_do_cmd (pt_this->t_sb_btn[ui1_idx].h_sb_text,
                                WGL_CMD_TEXT_SET_TEXT,
                                WGL_PACK (WZD_TEXT (ui2_mlm_key_idx)),
                                WGL_PACK (c_uc_w2s_strlen (WZD_TEXT (ui2_mlm_key_idx))));
        RET_ON_ERR (i4_ret);

		if (pt_this->ui1_sb_idx == ui1_idx && h_checkmark_icon != NULL_HANDLE)
		{
			SET_RECT_BY_SIZE (&t_rect_text,
		                      0,
		                      (10 + 125 + (140 - 80)/2) * WZD_UI_RATIO_W,
		                      WZD_SB_BTN_W,
		                      80 * WZD_UI_RATIO_W);
			i4_ret = c_wgl_move(pt_this->t_sb_btn[ui1_idx].h_sb_text,
								&t_rect_text,
								WGL_NO_AUTO_REPAINT);
			RET_ON_ERR (i4_ret);
		}
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_sb_btn_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_sb_btn_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
	UINT8						ui1_time_zone_idx = APP_CFG_CUST_TZ_UNKNOWN;
    
    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
            case BTN_SELECT:
				/* setup time zone and daylight */
				ui1_time_zone_idx = _wzd_time_zone_remap_idx((UINT8)pt_this->ui1_sb_idx);
				_wzd_time_zone_set_data_by_idx(ui1_time_zone_idx);

				if (a_wzd_is_resume_from_menu_setup())
				{
					a_wzd_exit();
				}
				else
				{
					wzd_page_goto(WZD_PAGE_NAVI_NEXT_PAGE);
				}
				
                break;

            case BTN_CURSOR_UP:
                if (pt_this->ui1_sb_idx >= WZD_SB_BTN_06 && pt_this->ui1_sb_idx <= WZD_SB_BTN_10) 
                {
                	RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_initial());
                	pt_this->ui1_sb_idx = pt_this->ui1_sb_idx - WZD_SB_BTN_06;
                    RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_hlt());
                    RET_ON_ERR (_wzd_time_zone_sb_btns_set_all_unfloat());
                    RET_ON_ERR (c_wgl_float(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, TRUE, FALSE));
					RET_ON_ERR (c_wgl_set_focus(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, WGL_NO_AUTO_REPAINT));
                }
                break;

            case BTN_CURSOR_DOWN:
                if (pt_this->ui1_sb_idx >= WZD_SB_BTN_01 && pt_this->ui1_sb_idx <= WZD_SB_BTN_05) 
                {
                	RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_initial());
                	pt_this->ui1_sb_idx = pt_this->ui1_sb_idx + 5;
                    RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_hlt());
                    RET_ON_ERR (c_wgl_set_focus(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, WGL_NO_AUTO_REPAINT));

					RET_ON_ERR (_wzd_time_zone_sb_btns_set_all_unfloat());
                	RET_ON_ERR (c_wgl_float(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, TRUE, FALSE));
                } 
                else if (pt_this->ui1_sb_idx >= WZD_SB_BTN_05 && pt_this->ui1_sb_idx <= WZD_SB_BTN_10)
                {
                    RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_initial());
                    RET_ON_ERR (wzd_view_footer_set_focus (WZD_FOOTER_BTN_01, FALSE));
					RET_ON_ERR (_wzd_time_zone_sb_btns_set_all_unfloat());
                }
                break;
                
            case BTN_CURSOR_RIGHT:
                if (pt_this->ui1_sb_idx >= WZD_SB_BTN_01 && pt_this->ui1_sb_idx <= WZD_SB_BTN_09) 
                {
                	RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_initial());
                	pt_this->ui1_sb_idx = pt_this->ui1_sb_idx + 1;
                    RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_hlt());
					RET_ON_ERR (_wzd_time_zone_sb_btns_set_all_unfloat());
                	RET_ON_ERR (c_wgl_float(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, TRUE, FALSE));
                    RET_ON_ERR (c_wgl_set_focus(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, WGL_NO_AUTO_REPAINT));
                }

                break;
                
            case BTN_CURSOR_LEFT:
                if (pt_this->ui1_sb_idx >= WZD_SB_BTN_02 && pt_this->ui1_sb_idx <= WZD_SB_BTN_10) 
                {
                	RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_initial());
                	pt_this->ui1_sb_idx = pt_this->ui1_sb_idx - 1;
                    RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_hlt());
					RET_ON_ERR (_wzd_time_zone_sb_btns_set_all_unfloat());
                	RET_ON_ERR (c_wgl_float(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, TRUE, FALSE));
					RET_ON_ERR (c_wgl_set_focus(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, WGL_NO_AUTO_REPAINT));
                }
                
                break;
                
            default:
                break;
            }
			wzd_view_main_frm_repaint();
        }
        break;
    default:
        break;
    }
   
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_create_sb_button_widget
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_create_sb_button_widget(
                               HANDLE_T                h_parent,
                               const GL_RECT_T*        pt_rect,
                               wgl_widget_proc_fct     pf_wdgt_proc,
                               HANDLE_T*               ph_btn)
{
    INT32               i4_ret = WZDR_OK;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_info;

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*) WZD_WIDGET_STYLE,
                                  NULL,
                                  ph_btn);
    RET_ON_ERR (i4_ret);                               

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_enable,    &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_disable,   &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_highlight, &t_g_wzd_color_base_frm_bk);

    i4_ret = c_wgl_do_cmd (h_parent,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK), /* background color */
                           WGL_PACK(&t_color_info));
                           
    RET_ON_ERR (i4_ret);
    
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

    i4_ret = c_wgl_do_cmd (*ph_btn,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK (WGL_IMG_BK), /* background image */
                           WGL_PACK (&t_img_info));
                           
    RET_ON_ERR (i4_ret);
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_create_sb_buttons
 *
 * Description: This function creates the select box buttons.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_create_sb_buttons(VOID)
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
    GL_RECT_T           		at_btn_rect[WZD_SB_BTN_COUNT] = WZD_SB_BTN_GET_RECTS();
    UINT8               		ui1_i = 0;
    UINT8               		ui1_align = 0; 
    UINT32              		ui4_style;
    WGL_INSET_T         		t_inset;
    WGL_FONT_INFO_T     		t_fnt_info;
    WGL_IMG_INFO_T      		t_img_info;
    GL_RECT_T           		t_rect_icon_1, t_rect_icon_2, t_rect_text;
    WGL_COLOR_INFO_T    		t_color_info_bg, t_color_info_fg;
    CHAR*               		s_font_name = wzd_view_get_font_name();
	INT32               		i4_ret = WZDR_OK;
                                                                       
    /* icon_1 rect */
    SET_RECT_BY_SIZE (&t_rect_icon_1,
                      0,
                      150 * WZD_UI_RATIO_W,
                      WZD_SB_BTN_W,
                      40 * WZD_UI_RATIO_W);

    /* icon_2 rect */
    SET_RECT_BY_SIZE (&t_rect_icon_2,
                      0,
                      170 * WZD_UI_RATIO_W,
                      WZD_SB_BTN_W,
                      40 * WZD_UI_RATIO_W);
    
    /* set text theme */
	SET_RECT_BY_SIZE (&t_rect_text,
                      0,
                      (125 + (140 - 80)/2) * WZD_UI_RATIO_W,
                      WZD_SB_BTN_W,
                      80 * WZD_UI_RATIO_W);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_128  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;
    
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    /* create buttons */
    for (ui1_i = 0; ui1_i < WZD_SB_BTN_COUNT; ui1_i++)
    { 
        i4_ret = _wzd_time_zone_create_sb_button_widget(
											pt_this->h_sb_frm,
                                            &at_btn_rect[ui1_i],
                                            _wzd_time_zone_sb_btn_nfy_fct,
                                            &pt_this->t_sb_btn[ui1_i].h_sb_btn_frm);
        RET_ON_ERR (i4_ret);

        i4_ret =_wzd_time_zone_create_text (pt_this->t_sb_btn[ui1_i].h_sb_btn_frm,
											NULL,
											&t_rect_text,
                                          	ui4_style,
                                          	&t_fnt_info,
                                          	ui1_align,
                                          	&t_color_info_bg,
                                          	&t_color_info_fg,
                                          	&t_inset,
                                          	&pt_this->t_sb_btn[ui1_i].h_sb_text);
        RET_ON_ERR (i4_ret);

        /* icon_1 create */
        i4_ret = _wzd_time_zone_create_icon (pt_this->t_sb_btn[ui1_i].h_sb_btn_frm,
                                         	&pt_this->t_sb_btn[ui1_i].h_sb_icon_1,
                                            &t_rect_icon_1);
        RET_ON_ERR (i4_ret);
                
        /* icon_2 create */
        i4_ret = _wzd_time_zone_create_icon(pt_this->t_sb_btn[ui1_i].h_sb_btn_frm,
                                            &pt_this->t_sb_btn[ui1_i].h_sb_icon_2,
                                            &t_rect_icon_2);
        RET_ON_ERR (i4_ret);
    }

    /* update background image */
    for (ui1_i = WZD_SB_BTN_06; ui1_i <= WZD_SB_BTN_10; ui1_i++)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

        i4_ret = c_wgl_do_cmd (pt_this->t_sb_btn[ui1_i].h_sb_btn_frm,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_BK), /* background image */
                               WGL_PACK (&t_img_info));
                               
        RET_ON_ERR (i4_ret);
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_sb_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_sb_create(HANDLE_T  h_parent) 
{
    /* select box create */
    RET_ON_ERR (_wzd_time_zone_create_sb_frm(h_parent));
    RET_ON_ERR (_wzd_time_zone_create_sb_buttons());

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_manually_dlg_show (VOID)
{
 	INT32						i4_ret = WZDR_OK;
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;

	i4_ret = wzd_dlg_set_text(pt_this->h_manually_dlg, WZD_TEXT(MLM_WZD_KEY_TIME_ZONE_SETUP_DLG_DESC), FALSE);
	RET_ON_ERR(i4_ret);
    
    i4_ret = wzd_dlg_set_btn_text( pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_01,
                          WZD_TEXT(MLM_WZD_KEY_DLG_OK), FALSE );
	RET_ON_ERR(i4_ret);
                          
    i4_ret = wzd_dlg_set_btn_text( pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_02,
                          WZD_TEXT(MLM_WZD_KEY_HELP_CANCEL), FALSE );
	RET_ON_ERR(i4_ret);

	i4_ret = wzd_dlg_show(pt_this->h_manually_dlg , FALSE);
	RET_ON_ERR(i4_ret);

	/* set editbox to topmost */
    i4_ret = c_wgl_insert (pt_this->h_manually_dlg_eb,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);
    
	i4_ret = c_wgl_set_visibility(pt_this->h_manually_dlg_eb, WGL_SW_NORMAL);
	RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_focus(pt_this->h_manually_dlg_eb, WGL_NO_AUTO_REPAINT);
	RET_ON_ERR(i4_ret);

	i4_ret = wzd_view_main_frm_repaint();
	RET_ON_ERR(i4_ret);

	return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_hide
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_manually_dlg_hide (VOID)
{
	 INT32						i4_ret = WZDR_OK;
	 WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
	 
	 i4_ret = c_wgl_set_visibility(pt_this->h_manually_dlg_eb, WGL_SW_HIDE);
     DBG_INFO(("i4_ret=%d\n",i4_ret));

	 wzd_dlg_hide(pt_this->h_manually_dlg);
	 
	 return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_ok_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_manually_dlg_ok_fct(
									  VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
 	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
	UTF16_T						w2s_text[32+1] = {0};
	CHAR                    	s_buf[32] = {0};
	INT32 						i4_offset = 0;
	BOOL						b_valid = TRUE;
    
	if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_UP == (UINT32)param1 )  
        {
            c_wgl_set_focus(pt_this->h_manually_dlg_eb, WGL_NO_AUTO_REPAINT);
            wzd_view_main_frm_repaint();
        }
        else if( BTN_SELECT == (UINT32)param1 ) 
        {
	        c_wgl_do_cmd(pt_this->h_manually_dlg_eb,
			             WGL_CMD_EB_GET_TEXT,
			             (VOID *) w2s_text,
			             (VOID *)32);
			c_uc_w2s_to_ps(w2s_text, s_buf, 32);

			b_valid = _wzd_time_zone_code_is_valid(s_buf);
			i4_offset = _wzd_time_zone_atoi(s_buf);
			if (!b_valid || i4_offset < -12 || i4_offset > 12)
			{
				DBG_LOG_PRINT(("\n[WZD][TZ] --- WARNING!!! %s %d. OFFSET: %d\n", __FUNCTION__,__LINE__, i4_offset));
				wzd_dlg_set_text( pt_this->h_manually_dlg, WZD_TEXT(MLM_WZD_KEY_TIME_ZONE_SETUP_INVALID_OFFSET), FALSE );
				c_wgl_set_focus(pt_this->h_manually_dlg_eb, WGL_NO_AUTO_REPAINT);
            	wzd_view_main_frm_repaint();
			}
			else
			{
				DBG_LOG_PRINT(("\n[WZD][TZ] --- GOOD. %s %d. OFFSET: %d\n", __FUNCTION__,__LINE__, i4_offset));
				_wzd_time_zone_set_data_by_offset(i4_offset);

				if (a_wzd_is_resume_from_menu_setup())
				{
					a_wzd_exit();
				}
				else
				{
					wzd_page_goto(WZD_PAGE_NAVI_NEXT_PAGE);
				}
			}
        }
    }

    return;
}
 /*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_cancel_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_manually_dlg_cancel_fct(
									  VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{	
 	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_UP == (UINT32)param1 )  
        {
            c_wgl_set_focus(pt_this->h_manually_dlg_eb, WGL_NO_AUTO_REPAINT);
			wzd_view_main_frm_repaint();
        }
		else if( BTN_SELECT == (UINT32)param1 ) 
        {
			_wzd_time_zone_manually_dlg_hide();
			wzd_view_footer_set_focus (WZD_FOOTER_BTN_01, TRUE);
        }
    }
	return;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_manually_dlg_proc_fct(
									  VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
	static wzd_dlg_data_change_nfy_fct  pf_fct = NULL;

	if(WZD_DLG_MSG_BTN_FOCUSED == ui4_msg)
	{
	    WZD_DLG_BTN_TYPE_T  t_btn_id = (WZD_DLG_BTN_TYPE_T)(UINT32)param1;
	    if(WZD_DLG_BTN_TYPE_01 == t_btn_id)
	    {
	        pf_fct = _wzd_time_zone_manually_dlg_ok_fct;
	    }
	    else
	    {
	        pf_fct = _wzd_time_zone_manually_dlg_cancel_fct;
	    }
	}
	else if(pf_fct && WZD_DLG_MSG_KEY_INPUT == ui4_msg)
	{
	    pf_fct(pv_tag, WGL_MSG_KEY_DOWN, param1, param2);
	}

	return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _wzd_time_zone_manually_dlg_eb_handle_number_key
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _wzd_time_zone_manually_dlg_eb_handle_number_key(
                    UINT32                      ui4_key_code
                    )
{
    switch(ui4_key_code) {
    case BTN_DIGIT_0:
    case BTN_DIGIT_1: case BTN_DIGIT_2: case BTN_DIGIT_3:
    case BTN_DIGIT_4: case BTN_DIGIT_5: case BTN_DIGIT_6:
    case BTN_DIGIT_7: case BTN_DIGIT_8: case BTN_DIGIT_9:
        return TRUE;
    default:
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_eb_create
 *
 * Description: create edit box on the manually dlg for enter codeset
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_manually_dlg_eb_fct(
							    HANDLE_T                    h_widget,
							    UINT32                      ui4_msg,
							    VOID*                       param1,
							    VOID*                       param2)
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  				i4_ret = WZDR_OK;
        UTF16_T				w2s_text[32+1] = {0};
	    INT32 				ui4_keycode = (UINT32)param1;

		/* deal with digit key */
		if (_wzd_time_zone_manually_dlg_eb_handle_number_key(ui4_keycode))
        {
	        i4_ret = c_wgl_do_cmd(pt_this->h_manually_dlg_eb,
							              WGL_CMD_EB_GET_TEXT,
							              (VOID *) w2s_text,
							              (VOID *)32);
			RET_ON_ERR(i4_ret);

			if ( c_uc_w2s_strlen(w2s_text) >= 3 )
			{
				wzd_dlg_set_focus_to_btn(pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_01, WGL_SYNC_AUTO_REPAINT);
				return WZDR_OK;
			}
			else if (w2s_text[0] != '-' && c_uc_w2s_strlen(w2s_text) == 2 )
			{
				wzd_dlg_set_focus_to_btn(pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_01, WGL_SYNC_AUTO_REPAINT);
				return WZDR_OK;
			}
			else
			{
				return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);  
			}
        }

        switch (ui4_keycode)
        {
        	case BTN_DIGIT_DOT:
			case BTN_KB_MINUS_SIGN:
			{
				i4_ret = c_wgl_do_cmd(pt_this->h_manually_dlg_eb,
							              WGL_CMD_EB_GET_TEXT,
							              (VOID *) w2s_text,
							              (VOID *)32);
				RET_ON_ERR(i4_ret);

				if (w2s_text[0] != 0)
				{
					return WZDR_OK;
				}
            }
                break;

        	case BTN_SELECT:
            case BTN_CURSOR_DOWN:
            {
				i4_ret = wzd_dlg_set_focus_to_btn(pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_01, WGL_SYNC_AUTO_REPAINT);
				RET_ON_ERR(i4_ret);
            }
                break;
				
            case BTN_CURSOR_LEFT:
            {
                i4_ret = c_wgl_do_cmd(pt_this->h_manually_dlg_eb,
						              WGL_CMD_EB_GET_TEXT,
						              (VOID *) w2s_text,
						              (VOID *)32);
				RET_ON_ERR(i4_ret);

                if ( c_uc_w2s_strlen(w2s_text) > 0 )
                {
                    w2s_text[c_uc_w2s_strlen(w2s_text) - 1] = '\0';

                    i4_ret = c_wgl_do_cmd (pt_this->h_manually_dlg_eb,
                                           WGL_CMD_EB_SET_TEXT,
                                           WGL_PACK (w2s_text),
				                           WGL_PACK (0xFFFF));
                    RET_ON_ERR(i4_ret);

                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    return WZDR_OK;
                }
                else
                {
                	return WZDR_OK;
                }
            }
            	break;
			
            default:
                return WZDR_OK;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);  
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_edit_box_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_manually_edit_box_create (
												HANDLE_T             h_parent,
                                               	GL_RECT_T            t_rect,
                                               	wgl_widget_proc_fct  pf_wdgt_proc,
                                               	HANDLE_T*            ph_widget)
{
    INT32                       i4_ret = WZDR_OK;
    UINT32                      ui4_style;
	WGL_INSET_T         		t_inset;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;

    ui4_style = WGL_STL_EB_MAX_CHAR_256;
    
    /* create editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 240,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

	/* Set Cnt Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left = 25 * WZD_UI_RATIO_W;
	t_inset.i4_right = 25 * WZD_UI_RATIO_W;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_seti_lst_col_dis_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_wzd_color_seti_lst_col_txt;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    RET_ON_ERR(i4_ret);

    /* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable     = h_g_wzd_img_textBox_register;
    t_img_info.u_img_data.t_standard.t_highlight  = h_g_wzd_img_textBox_register_highlight;
    t_img_info.u_img_data.t_standard.t_disable    = h_g_wzd_img_textBox_register;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);
    
    /* Set pos style */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CURSOR_CHAR,
                          (VOID*)WZD_CUSTOM_TEXT("|"),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));
    RET_ON_ERR(i4_ret);

    /* Set Char support */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_CHAR_SUPPORT),
                          WGL_PACK(WGL_EB_CHAR_SUPPORT));
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(4)),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    RET_ON_ERR(i4_ret);
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_eb_create
 *
 * Description: create edit box on the manually dlg for enter codeset
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_manually_dlg_eb_create (HANDLE_T parent)
{
 	WZD_TIME_ZONE_PAGE_DATA_T*		pt_this = &t_g_wzd_time_zone_page_data;
 	GL_RECT_T           			t_rect;
 	INT32							i4_ret = WZDR_OK;
 	
	/* get rectangle size */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    
	SET_RECT_BY_SIZE (& t_rect,
				WZD_MANUALLY_DLG_EB_X,
				WZD_MANUALLY_DLG_EB_Y,
				WZD_MANUALLY_DLG_EB_W,
				WZD_MANUALLY_DLG_EB_H);
				  
    /* create widget */
    i4_ret = _wzd_time_zone_manually_edit_box_create (parent,
                                                      t_rect,
                                                      _wzd_time_zone_manually_dlg_eb_fct,
                                                      &pt_this->h_manually_dlg_eb);
    RET_ON_ERR(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_manually_dlg_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _wzd_time_zone_manually_dlg_create (VOID)
 {
 	WZD_TIME_ZONE_PAGE_DATA_T*		pt_this = &t_g_wzd_time_zone_page_data;
 	WZD_DLG_INIT_T      			t_dlg_init;
 	HANDLE_T            			h_layout_frm = NULL_HANDLE;
    UTF16_T*            			pw2s_dlg_text = NULL;
    UTF16_T*            			pw2s_dlg_btn1_text = NULL;
    UTF16_T*            			pw2s_dlg_btn2_text = NULL;
 	
 	c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;
    t_dlg_init.pf_fct = _wzd_time_zone_manually_dlg_proc_fct;

    t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_WITH_DESC_MUTI_LINE;
	pw2s_dlg_text = WZD_TEXT(MLM_WZD_KEY_TIME_ZONE_SETUP_DLG_DESC);

	/* Set Font */
    c_strcpy (t_dlg_init.t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_dlg_init.t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_dlg_init.t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_dlg_init.t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_dlg_init.t_fnt_info.ui1_custom_size = 18;

	pw2s_dlg_btn1_text = WZD_TEXT(MLM_WZD_KEY_DLG_OK);
    pw2s_dlg_btn2_text = WZD_TEXT(MLM_WZD_KEY_HELP_CANCEL);

    wzd_dlg_create( &t_dlg_init, &pt_this->h_manually_dlg);

    wzd_dlg_set_text( pt_this->h_manually_dlg, pw2s_dlg_text, FALSE );
    
    wzd_dlg_set_btn_text( pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_01,
                          pw2s_dlg_btn1_text, FALSE );
                          
    wzd_dlg_set_btn_text( pt_this->h_manually_dlg, WZD_DLG_BTN_TYPE_02,
                          pw2s_dlg_btn2_text, FALSE );

    _wzd_time_zone_manually_dlg_eb_create (h_layout_frm);

    return WZDR_OK;
 }

/*-----------------------------------------------------------------------------
 * Name: _wzd_time_zone_help_lst_update
 *
 * Description: The function updates help information.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_help_lst_update (BOOL b_repaint)
{
	/* set footer frame visibility */
	SHOW_ON_ERR (wzd_view_footer_set_visibility(TRUE));

	/* set footer button num */
	SHOW_ON_ERR (wzd_view_footer_set_btn_num(1));

	/* update 1st footer button */
	SHOW_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_TIME_ZONE_SETUP_BTN_OTHER_TZ)));
	SHOW_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));

	/* update 2nd footer button */
	SHOW_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));

	/* update footer button navigation */
    SHOW_ON_ERR (wzd_view_footer_update_btn_navigation());

	if (b_repaint)
	{
		SHOW_ON_ERR (wzd_view_footer_frm_repaint());
	}

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_page_return_nfy_cb
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_page_return_nfy_cb(VOID)
{
    wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_page_on_footer_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_time_zone_page_on_footer_nfy( UINT32   ui4_msg,
                                VOID*    pv_param1,
                                VOID*    pv_param2)
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
    switch( ui4_msg )
    {
    	case WZD_FOOTER_MSG_ITEM_FOCUSED:
			break;
        case WZD_FOOTER_MSG_KEY_INPUT:
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
					if( WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )
	                {
	                	_wzd_time_zone_manually_dlg_show();
	                }
                    break;

				case BTN_CURSOR_UP:
					/* set focus to the lasted sb button */
                    _wzd_time_zone_sb_losed_foucs_box_txt_hlt();
                    c_wgl_float(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, TRUE, WGL_NO_AUTO_REPAINT);
					c_wgl_set_focus(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, WGL_NO_AUTO_REPAINT);
					wzd_view_main_frm_repaint();
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_page_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_page_create(VOID)
{
	HANDLE_T h_layout_frm = NULL_HANDLE;

    c_memset(&t_g_wzd_time_zone_page_data, 0, sizeof(WZD_TIME_ZONE_PAGE_DATA_T));

	RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

	RET_ON_ERR (_wzd_time_zone_desc_create(h_layout_frm));
	RET_ON_ERR (_wzd_time_zone_sb_create(h_layout_frm));
	RET_ON_ERR (_wzd_time_zone_manually_dlg_create());
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_page_dsty
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_page_dsty(VOID)
{
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_page_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_page_show (UINT32 ui4_page_id)
{
	WZD_TIME_ZONE_PAGE_DATA_T*	pt_this = &t_g_wzd_time_zone_page_data;
	HANDLE_T 					h_layout_frm = NULL_HANDLE;
	UINT8						ui1_time_zone_idx = APP_CFG_CUST_TZ_UNKNOWN;
	UINT16         				ui2_tz_select_status = 0;

	RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
	RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

	/* show desc text */
	RET_ON_ERR (wzd_view_desc_txt_set_visibility(TRUE));

	/* update footer button */
	RET_ON_ERR (_wzd_time_zone_help_lst_update(FALSE));

	/* reset the lasted focus button theme */
	RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_initial());

	/* get time zone setup status */
	a_cfg_custom_get_tz_select(&ui2_tz_select_status);
	if (0 == ui2_tz_select_status)
	{
		pt_this->ui1_sb_idx = WZD_SB_BTN_01;
	}
	else
	{
		/* restore focus by time zone index */
		a_cfg_custom_get_timezone_idx(&ui1_time_zone_idx);
		if (ui1_time_zone_idx >= APP_CFG_CUST_TZ_HAWAII && 
			ui1_time_zone_idx <= APP_CFG_CUST_TZ_NEWFOUNDLAND)
		{
			pt_this->ui1_sb_idx = _wzd_time_zone_remap_acfg(ui1_time_zone_idx);
		}
		else
		{
			pt_this->ui1_sb_idx = WZD_SB_BTN_COUNT;
		}
	}

	/* show select time zone box */
	RET_ON_ERR (c_wgl_set_visibility (pt_this->h_sb_frm, WGL_SW_RECURSIVE));
    RET_ON_ERR (_wzd_time_zone_set_btn_contents());
	RET_ON_ERR (_wzd_time_zone_sb_btns_set_all_unfloat());

	/* set focus to correct sb button or Other Time Zones button */
	if (WZD_SB_BTN_COUNT == pt_this->ui1_sb_idx)
	{
		RET_ON_ERR (wzd_view_footer_set_focus (WZD_FOOTER_BTN_01, FALSE));
		pt_this->ui1_sb_idx = WZD_SB_BTN_01;
	}
	else
	{
	    RET_ON_ERR (_wzd_time_zone_sb_losed_foucs_box_txt_hlt());
		RET_ON_ERR (c_wgl_float(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, TRUE, WGL_NO_AUTO_REPAINT));
		RET_ON_ERR (c_wgl_set_focus(pt_this->t_sb_btn[pt_this->ui1_sb_idx].h_sb_btn_frm, WGL_NO_AUTO_REPAINT));
	}

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_time_zone_page_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_time_zone_page_hide(UINT32 ui4_page_id)
{
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_time_zone_page_get_page_info_data
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 wzd_time_zone_page_get_page_info_data(WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset(pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T));

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TIME_ZONE_SETUP_TITLE;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_TIME_ZONE_SETUP_DESC;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_time_zone_page_on_footer_nfy;
	pt_info_data->pf_return_nfy_fct        = _wzd_time_zone_page_return_nfy_cb;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_time_zone_page_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_time_zone_page_dsty;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_time_zone_page_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_time_zone_page_hide;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_time_zone_page_nfy_sel
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 wzd_time_zone_page_nfy_sel (UINT16               	ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
   (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

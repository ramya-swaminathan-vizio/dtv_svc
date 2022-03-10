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
 * $RCSfile: npg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "app_util/a_icl.h"
#include "app_util/icl/_icl.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "res/app_util/config/a_cfg_custom.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    private function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    public function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 icl_custom_init(VOID)
{
    INT32 i4_ret = 0;
    UINT32 ui4_val = 0xFFFFFFFF;

    i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS),
                               ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS_SIZE,
                               &ui4_val,
                               NULL);
    ICL_CHK_FAIL(i4_ret);

	ui4_val = 0xFFFFFFFF;
    i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                               ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE,
                               &ui4_val,
                               NULL);
    ICL_CHK_FAIL(i4_ret);

	ui4_val = 0xFFFFFFFF;
    i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_SRC_STATUS),
                               ICL_RECID_CUSTOM_MMP_SRC_STATUS_SIZE,
                               &ui4_val,
                               NULL);
    ICL_CHK_FAIL(i4_ret);

    /* Custom Group  1 */
    i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_SAMPLE_GROUP, ICL_RECID_CUSTOM_SAMPLE_RECORD),
                               ICL_RECID_CUSTOM_SAMPLE_RECORD_SIZE,
                               NULL,
                               NULL);
    ICL_CHK_FAIL(i4_ret);

    /* Custom Group  2 */
    i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_RESET, ICL_RECID_CUSTOM_RESET_TYPE),
                               ICL_RECID_CUSTOM_RESET_TYPE_SIZE,
                               NULL,
                               NULL);
    ICL_CHK_FAIL(i4_ret);

    /* NAV Group. */
    {
        UINT8 ui1_val = ICL_NAV_ENTER_WIDE_SELECTION_NOT_BY_KEY;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NAV, ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY),
                                   ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    #ifdef APP_NAV_CAMERA_PLUG_SUPPORT
        ui1_val = ICL_CUSTOM_CAM_PLUG_OUT;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NAV, ICL_RECID_CUSTOM_NAV_CAM_PLUG_STATUS),
                                   ICL_RECID_CUSTOM_NAV_CAM_PLUG_INFO_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    #endif
    }

    /* Network Widget Group */
    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS),
                                   ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);

        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS),
                                   ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* Co-exist App Group */
    {
        ICL_CUSTOM_RESUME_NEXT_APP_T e_next_app = ICL_CUSTOM_RESUME_NEXT_APP_MMP;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_COEXIST_APP, ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE),
                                   ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE_SIZE,
                                   &e_next_app,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* Rating Enable Group */
    {
        UINT8 ui1_val = RATING_ENABLED_STATUS_ON;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                                   ICL_RECID_RATING_ENABLED_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* E-manual status Group */
    {
        UINT8 ui1_val = ICL_EMANUAL_STATUS_OFF;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
                                   ICL_RECID_EMANUAL_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    if (a_cfg_custom_get_wifi_remote_support())
    {
        /* Wifi remote low battery status Group */
        {
            UINT8 ui1_val = ICL_WIFI_REMOTE_BATTERY_STATUS_NORMAL;
            i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS, ICL_RECID_WIFI_REMOTE_BATTERY_STATUS),
                                       ICL_RECID_WIFI_REMOTE_BATTERYL_STATUS_SIZE,
                                       (VOID*) &ui1_val,
                                       NULL);
            ICL_CHK_FAIL(i4_ret);
        }
    }

  	/* Banner CC item status Group */
    {
        UINT8 ui1_val = ICL_CC_ITEM_STATUS_HIDE;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CC_ITEM_STATUS, ICL_RECID_CC_ITEM_STATUS),
                                   ICL_RECID_CC_ITEM_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

	/* Wizard status Group*/
    {
        UINT8 ui1_val = ICL_WIZARD_STATUS_PAUSE;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS),
                                   ICL_RECID_WIZARD_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* CUSTOM UPDATER Group */
    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_UPDATER, ICL_RECID_CUSTOM_UPDATER_STATUS),
                                   ICL_RECID_CUSTOM_UPDATER_STATUS_SIZES,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* Msgcvt if UI poping up Group */
    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_MSGCVT_UI_POPUP, ICL_RECID_MSGCVT_IS_UI_POPUP),
                                   ICL_RECID_MSGCVT_IS_UI_POPUP_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* Color Tuner Group */
    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN),
                                   ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);

        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_11_POINT),
                                   ICL_RECID_CUSTOM_COLOR_TUNER_11_POINT_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);

        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                                   ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

#ifdef APP_DYNAMIC_TOS_SUPPORT
    /* Group Dyanmic TOS download */
    {
        UINT8 ui1_val = ICL_TOS_DOWNLOAD_ITEM_STOP;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS),
                                   ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);

        ui1_val = ICL_POLICY_DOWNLOAD_ITEM_STOP;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS),
                                   ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }
#endif

    /* Group PQ change status */
    {
        UINT8 ui1_val = ICL_PQ_CHANGE_NOTHING;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_PQ_CHANGE_STATUS, ICL_RECID_PQ_CHANGE_STATUS),
                                   ICL_RECID_PQ_CHANGE_STATUS_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* Group custom flag change */
    {
        UINT8 ui1_val = ICL_RECID_CUSTOM_NOTHING_CHANGE;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_FLAG_CHANGE),
                                   ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);

        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG),
                                   ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG_SIZE,
                                   (VOID*) &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* TVAP TOS Group */
    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_TVAP_TOS_STATUS, ICL_RECID_CUSTOM_TVAP_TOS_STATUS),
                                   ICL_RECID_CUSTOM_TVAP_TOS_STATUS_TYPE_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }
#ifdef APP_BLE_SUPPORT

	{
		int32_t ui1_val = -1000;
		i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_BT_GATTC_SERVER_RSSI, ICL_RECID_BT_GATTC_SERVER_RSSI),
								   ICL_RECID_BT_GATTC_SERVER_RSSI_SIZE,
								   &ui1_val,
								   NULL);
		ICL_CHK_FAIL(i4_ret);
	}
#endif
    /* TVAP POWER MODE Group */
    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CUSTOM_POWER_MODE, ICL_RECID_CUSTOM_POWER_MODE),
                                   ICL_RECID_CUSTOM_POWER_MODE_SIZE,
                                   &ui1_val,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* cast ipts select */
    {
        UINT8 ui1_val = ICL_RECID_CAST_SRC_STATUS_FALSE;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_CAST_SRC_STATUS, ICL_RECID_CAST_SRC_STATUS),
                                    ICL_RECID_CAST_SRC_STATUS_SIZE,
                                    (VOID*) &ui1_val,
                                    NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* test pattern */
    {
        UINT8 ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_TEST_PATTERN_STATUS, ICL_RECID_TEST_PATTERN_STATUS),
                                    ICL_RECID_TEST_PATTERN_STATUS_SIZE,
                                    (VOID*) &ui1_val,
                                    NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_DEMO_STATUS, ICL_RECID_DEMO_STATUS),
                                    ICL_RECID_DEMO_STATUS_SIZE,
                                    (VOID*) &ui1_val,
                                    NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /* tuner setup*/
    {
        UINT8 ui1_val = ICL_RECID_TUNER_SETUP_STATUS_COMPLETE;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_TUNER_SETUP_STATUS, ICL_RECID_TUNER_SETUP_STATUS),
                                    ICL_RECID_TUNER_SETUP_STATUS_SIZE,
                                    (VOID*) &ui1_val,
                                    NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    {
        UINT8 ui1_val = 0;
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_DOLBY_VISION_STATUS, ICL_RECID_DOLBY_VISION_STATUS),
                                    ICL_RECID_DOLBY_VISION_STATUS_SIZE,
                                    (VOID*) &ui1_val,
                                    NULL);
        ICL_CHK_FAIL(i4_ret);
    }
    /* bgm power */
     {
         UINT8 ui1_val = BGM_POWER_DOWN_MODE_NORMAL;
         i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_BGM_POWER, ICL_RECID_BGM_POWER_DOWN_MODE),
                                    ICL_RECID_BGM_POWER_DOWN_MODE_SIZE,
                                    (VOID*) &ui1_val,
                                    NULL);
         ICL_CHK_FAIL(i4_ret);
     }

     /* uli download*/
     {
         i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_ULI_DOWNLOAD_STATUS, ICL_RECID_ULI_DOWNLOAD_STATUS_TYPE),
                                    ICL_RECID_ULI_DOWNLOAD_STATUS_SIZE,
                                    NULL,
                                    NULL);
         ICL_CHK_FAIL(i4_ret);
     }

    /* picture edit page */
    {
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_PICTURE_EDIT_TYPE_STATUS, ICL_RECID_PICTURE_EDIT_TYPE_STATUS),
                                   ICL_RECID_PICTURE_EDIT_TYPE_SIZE,
                                   NULL,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    /*hdr type */
    {
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_HDR_TYPE_STATUS, ICL_RECID_HDR_TYPE_STATUS),
                                   ICL_RECID_HDR_TYPE_SIZE,
                                   NULL,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }
    /*3rd play */
    {
        i4_ret = icl_insert_field (ICL_MAKE_ID(ICL_GRPID_3RD_PLAY_STATUS, ICL_RECID_3RD_PLAY_STATUS),
                                   ICL_RECID_3RD_PLAY_SIZE,
                                   NULL,
                                   NULL);
        ICL_CHK_FAIL(i4_ret);
    }

    return ICLR_OK;
}

/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_icl_get(
    ICL_ID_TYPE          e_id,
    VOID*                pt_values,
    SIZE_T*              pz_size)
{
    return icl_get (e_id, pt_values, pz_size);
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_icl_set(
    ICL_ID_TYPE         e_id,
    VOID*               pt_values,
    SIZE_T              z_size)
{
    return icl_set (e_id, pt_values, z_size);
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_icl_set_multiple(
    UINT16              ui2_count,
    ICL_SET_DATA_T*     pt_set_data         /* The group ID should be the same within all ICL_SET_DATA_T */
)
{
    return icl_set_multiple (ui2_count, pt_set_data);
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_icl_custom_set_reset_type (
    UINT8               ui1_reset_type
    )
{
    return (a_icl_set ( ICL_MAKE_ID (ICL_GRPID_CUSTOM_RESET, ICL_RECID_CUSTOM_RESET_TYPE),
                        (VOID*)&ui1_reset_type,
                        ICL_RECID_CUSTOM_RESET_TYPE_SIZE)) ;
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_icl_custom_get_reset_type (
    UINT8*              pui1_reset_type
    )
{
    SIZE_T              z_size = ICL_RECID_CUSTOM_RESET_TYPE_SIZE;

    if (!pui1_reset_type) { return ICLR_FAIL ; }

    return (a_icl_get ( ICL_MAKE_ID (ICL_GRPID_CUSTOM_RESET, ICL_RECID_CUSTOM_RESET_TYPE),
                        pui1_reset_type ,
                        &z_size)) ;
}


/**
 * @brief   This function set whether the wide mode selection page is entered by hotkey.
 * @param   ui1_val [in]    Enter by hotkey or not.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_enter_wide_selection_by_key (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY_SIZE;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NAV, ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY), (VOID*) &ui1_val, z_size);
}
/**
 * @brief   This function get whether the wide mode selection page is entered by hotkey.
 * @param   pui1_val [out]    Enter by hotkey or not.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_enter_wide_selection_by_key (UINT8* pui1_val)
{
    INT32 i4_ret;
    SIZE_T z_size = ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY_SIZE;
    if (!pui1_val)
    {
        return ICLR_FAIL;
    }
    i4_ret = a_icl_get (ICL_MAKE_ID (ICL_GRPID_CUSTOM_NAV, ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY),
                (VOID*) pui1_val, &z_size);
    ICL_CHK_FAIL(i4_ret);

    return ICLR_OK;
}

#ifdef APP_NAV_CAMERA_PLUG_SUPPORT
/**
 * @brief   This function set the status of the camera pluged in .
 * @param   ui1_val [in]    Enter by hotkey or not.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_camera_plug_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_NAV_CAM_PLUG_INFO_SIZE;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NAV, ICL_RECID_CUSTOM_NAV_CAM_PLUG_STATUS), (VOID*) &ui1_val, z_size);
}
/**
 * @brief   This function set the status of camera plug infomation.
 * @param   pui1_val [out]    Enter by hotkey or not.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_camera_plug_status (UINT8* pui1_val)
{
    INT32 i4_ret;
    SIZE_T z_size = ICL_RECID_CUSTOM_NAV_CAM_PLUG_INFO_SIZE;
    if (!pui1_val)
    {
        return ICLR_FAIL;
    }
    i4_ret = a_icl_get (ICL_MAKE_ID (ICL_GRPID_CUSTOM_NAV, ICL_RECID_CUSTOM_NAV_CAM_PLUG_STATUS),
                (VOID*) pui1_val, &z_size);
    ICL_CHK_FAIL(i4_ret);

    return ICLR_OK;
}
#endif

/**
 * @brief   This function get the status of network widget.
 * @param   e_widget_type [in] network widget type.
 * @param   pui1_status [out] network widget status.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_T e_widget_type, UINT8* pui1_status)
{
    INT32 i4_ret = ICLR_OK;

    if (!pui1_status)
    {
        return ICLR_FAIL;
    }

    if (e_widget_type == ICL_CUSTOM_NW_WIDGET_DOCK)
    {
        SIZE_T z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;
        i4_ret = a_icl_get (ICL_MAKE_ID (ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS),
                    (VOID*) pui1_status, &z_size);
        ICL_CHK_FAIL(i4_ret);
    }
    else if (e_widget_type == ICL_CUSTOM_NW_WIDGET_APP)
    {
        SIZE_T z_size = ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS_SIZE;
        i4_ret = a_icl_get (ICL_MAKE_ID (ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS),
                    (VOID*) pui1_status, &z_size);
        ICL_CHK_FAIL(i4_ret);
    }

    return ICLR_OK;
}

/**
 * @brief   This function set the network widget status.
 * @param   e_widget_type [in] network widget type.
 * @param   ui1_status [in] network widget status show or not:
 *          ui1_status == 0 means hide
 *          ui1_status == 1 means show
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_nw_widget_status(ICL_CUSTOM_NW_WIDGET_T e_widget_type, UINT8 ui1_status)
{
    INT32 i4_ret = ICLR_OK;

    if (e_widget_type == ICL_CUSTOM_NW_WIDGET_DOCK)
    {
        SIZE_T z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;
        i4_ret = a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS), (VOID*) &ui1_status, z_size);
    }
    else if (e_widget_type == ICL_CUSTOM_NW_WIDGET_APP)
    {
        SIZE_T z_size = ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS_SIZE;
        i4_ret = a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS), (VOID*) &ui1_status, z_size);
    }

    return i4_ret;
}

/**
 * @brief   This function get the next resume app when menu paused.
 * @param
 * @param   pe_next_app [out]:
 *          MENU_RESUME_NEXT_APP_MMP:      after menu paused, MMP should be resume.
 *          MENU_RESUME_NEXT_APP_WZD_NW:   after menu paused, WZD network setup should be resume.
 *          MENU_RESUME_NEXT_APP_WZD_RC:   after menu paused, WZD remote control should be resume.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_T *pe_next_app)
{
    INT32 i4_ret = ICLR_OK;

    if (!pe_next_app)
    {
        return ICLR_FAIL;
    }

    SIZE_T z_size = ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE_SIZE;
    i4_ret = a_icl_get (ICL_MAKE_ID (ICL_GRPID_CUSTOM_COEXIST_APP, ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE),
                (VOID*) pe_next_app, &z_size);
    ICL_CHK_FAIL(i4_ret);

    return ICLR_OK;
}

/**
 * @brief   This function set next resume app when menu paused.
 * @param   e_next_app [in]:
 *          MENU_RESUME_NEXT_APP_MMP:      after menu paused, MMP should be resume.
 *          MENU_RESUME_NEXT_APP_WZD_NW:   after menu paused, WZD network setup should be resume.
 *          MENU_RESUME_NEXT_APP_WZD_RC:   after menu paused, WZD remote control should be resume.
 * @param
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_T e_next_app)
{
    INT32 i4_ret = ICLR_OK;

    SIZE_T z_size = ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE_SIZE;
    i4_ret = a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_COEXIST_APP, ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE), (VOID*) &e_next_app, z_size);

    return i4_ret;
}

/**
 * @brief   This function is to set the status for the cust updater.
 * @param   ui1_val [in]    cust updater status.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_cust_updater_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_UPDATER_STATUS_SIZES;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_UPDATER, ICL_RECID_CUSTOM_UPDATER_STATUS), (VOID*) &ui1_val, z_size);
}
/**
 * @brief   This function is to get the status for the cust updater.
 * @param   pui1_val [out]    point to the value cust updater status.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_cust_updater_status (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_UPDATER_STATUS_SIZES;
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_CUSTOM_UPDATER, ICL_RECID_CUSTOM_UPDATER_STATUS), (VOID*) pui1_val, &z_size);
}

/**
 * @brief   This function set whether the wide mode selection page is entered by hotkey.
 * @param   ui1_val [in]    Enter by hotkey or not.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_is_ui_popup (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_MSGCVT_IS_UI_POPUP_SIZE;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_MSGCVT_UI_POPUP, ICL_RECID_MSGCVT_IS_UI_POPUP), (VOID*) &ui1_val, z_size);
}

/**
 * @brief   This function is to set the type for the pq change.
 * @param   ui1_val [in]    pq change type.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_pq_chg_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_PQ_CHANGE_STATUS_SIZE;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_PQ_CHANGE_STATUS, ICL_RECID_PQ_CHANGE_STATUS), (VOID*) &ui1_val, z_size);
}
/**
 * @brief   This function is to get the type for the pq change.
 * @param   pui1_val [out]    point to the value pq change type.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_pq_chg_status (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_PQ_CHANGE_STATUS_SIZE;
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_PQ_CHANGE_STATUS, ICL_RECID_PQ_CHANGE_STATUS), (VOID*) pui1_val, &z_size);
}

/**
 * @brief   This function set TOS info changed.
 * @param   ui1_val [in]
 *          00(tos & privacy are all not set).
 *          01(tos is set).
 *          10(privacy is set).
 *          11(tos & privacy are all set).
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_tos_info (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_TVAP_TOS_STATUS_TYPE_SIZE;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_TVAP_TOS_STATUS, ICL_RECID_CUSTOM_TVAP_TOS_STATUS), (VOID*) &ui1_val, z_size);
}

/**
 * @brief   This function is to get the power mode set by menu.
 * @param   pui1_val [out]    point to the value.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_get_power_mode (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_POWER_MODE_SIZE;
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_CUSTOM_POWER_MODE, ICL_RECID_CUSTOM_POWER_MODE), (VOID*) pui1_val, &z_size);
}

/**
 * @brief   This function set power mode by menu.
 * @param   ui1_val [in]
 *          0(eco mode).
 *          1(quick staart mode).
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_icl_custom_set_power_mode (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_CUSTOM_POWER_MODE_SIZE;
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_CUSTOM_POWER_MODE, ICL_RECID_CUSTOM_POWER_MODE), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_custom_set_cast_src_status(UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_CAST_SRC_STATUS_SIZE;

    if (ui1_val != ICL_RECID_CAST_SRC_STATUS_TRUE &&
        ui1_val != ICL_RECID_CAST_SRC_STATUS_TRUE_REAL &&
        ui1_val != ICL_RECID_CAST_SRC_STATUS_TRUE_VTRL &&
        ui1_val != ICL_RECID_CAST_SRC_STATUS_FALSE)
    {
        return ICLR_FAIL;
    }

    return a_icl_set(ICL_MAKE_ID(ICL_GRPID_CAST_SRC_STATUS, ICL_RECID_CAST_SRC_STATUS), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_custom_get_cast_src_status(UINT8 *pui1_val)
{
    SIZE_T z_size = ICL_RECID_CAST_SRC_STATUS_SIZE;
    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get(ICL_MAKE_ID(ICL_GRPID_CAST_SRC_STATUS, ICL_RECID_CAST_SRC_STATUS), (VOID*) pui1_val, &z_size);
}

INT32 a_icl_custom_set_test_pattern_status(UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_TEST_PATTERN_STATUS_SIZE;

    if (ui1_val != ICL_RECID_TEST_PATTERN_STATUS_DISABLE &&
        ui1_val != ICL_RECID_TEST_PATTERN_STATUS_ENABLE  &&
        ui1_val != ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ )
    {
        return ICLR_FAIL;
    }

    return a_icl_set(ICL_MAKE_ID(ICL_GRPID_TEST_PATTERN_STATUS, ICL_RECID_TEST_PATTERN_STATUS), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_custom_get_test_pattern_status(UINT8 *pui1_val)
{
    SIZE_T z_size = ICL_RECID_TEST_PATTERN_STATUS_SIZE;
    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get(ICL_MAKE_ID(ICL_GRPID_TEST_PATTERN_STATUS, ICL_RECID_TEST_PATTERN_STATUS), (VOID*) pui1_val, &z_size);
}

INT32 a_icl_custom_set_demo_status(UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_DEMO_STATUS_SIZE;
    return a_icl_set(ICL_MAKE_ID(ICL_GRPID_DEMO_STATUS, ICL_RECID_DEMO_STATUS),(VOID*) &ui1_val, z_size);
}

INT32 a_icl_custom_get_demo_status(VOID)
{
    UINT8  ui1_val = 0;
    SIZE_T z_size = ICL_RECID_DEMO_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_DEMO_STATUS, ICL_RECID_DEMO_STATUS), (VOID*)&ui1_val, &z_size);
    return (INT32)ui1_val;
}

INT32 a_icl_custom_set_tuner_setup_status(UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_TUNER_SETUP_STATUS_SIZE;

    if (ui1_val != ICL_RECID_TUNER_SETUP_STATUS_COMPLETE &&
        ui1_val != ICL_RECID_TUNER_SETUP_STATUS_PROGRESS &&
        ui1_val != ICL_RECID_TUNER_SETUP_STATUS_CANCEL   &&
        ui1_val != ICL_RECID_TUNER_SETUP_STATUS_ABORT)
    {
        return ICLR_FAIL;
    }

    return a_icl_set(ICL_MAKE_ID(ICL_GRPID_TUNER_SETUP_STATUS, ICL_RECID_TUNER_SETUP_STATUS), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_custom_get_tuner_setup_status(UINT8 *pui1_val)
{
    SIZE_T z_size = ICL_RECID_TUNER_SETUP_STATUS_SIZE;
    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get(ICL_MAKE_ID(ICL_GRPID_TUNER_SETUP_STATUS, ICL_RECID_TUNER_SETUP_STATUS), (VOID*) pui1_val, &z_size);
}

INT32 a_icl_custom_set_dolby_vision_status(UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_DOLBY_VISION_STATUS_SIZE;
    return a_icl_set(ICL_MAKE_ID(ICL_GRPID_DOLBY_VISION_STATUS, ICL_RECID_DOLBY_VISION_STATUS),(VOID*) &ui1_val, z_size);
}

INT32 a_icl_custom_get_dolby_vision_status(VOID)
{
    UINT8  ui1_val = 0;
    SIZE_T z_size = ICL_RECID_DOLBY_VISION_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_DOLBY_VISION_STATUS, ICL_RECID_DOLBY_VISION_STATUS), (VOID*)&ui1_val, &z_size);
    return (INT32)ui1_val;
}


/******************************************************************************/
/**
 * @brief   This function set app status.
 * @param   ui1_val [in]    Selection type.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_icl_set_bgm_power_down_mode (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_BGM_POWER_DOWN_MODE_SIZE;

    if (ui1_val > BGM_POWER_DOWN_MODE_LAST_ENTRY)
    {
        return ICLR_FAIL;
    }

    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_BGM_POWER, ICL_RECID_BGM_POWER_DOWN_MODE), (VOID*) &ui1_val, z_size);
}

/******************************************************************************/
/**
 * @brief   This function get app status.
 * @param   pui1_val [out]    Selection type.
 * @retval  ICLR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_icl_get_bgm_power_down_mode (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_BGM_POWER_DOWN_MODE_SIZE;
    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }

    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_BGM_POWER, ICL_RECID_BGM_POWER_DOWN_MODE), (VOID*) pui1_val, &z_size);
}


INT32 a_icl_set_uli_download_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_ULI_DOWNLOAD_STATUS_SIZE;

    DBG_LOG_PRINT(("%s,%d \n",__FUNCTION__,__LINE__));

    if ( ui1_val != ICL_ULI_DOWNLOAD_STATUS_NONE && ui1_val != ICL_ULI_DOWNLOAD_STATUS_DONE )
    {
        return ICLR_FAIL;
    }

    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_ULI_DOWNLOAD_STATUS, ICL_RECID_ULI_DOWNLOAD_STATUS_TYPE), (VOID*) &ui1_val, z_size);
}
/*
get cast wakeup ready status
*/
INT32 a_icl_get_uli_download_status (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_ULI_DOWNLOAD_STATUS_SIZE;

    //DBG_LOG_PRINT(("%s,%d \n",__FUNCTION__,__LINE__));

    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_ULI_DOWNLOAD_STATUS, ICL_RECID_ULI_DOWNLOAD_STATUS_TYPE), (VOID*) pui1_val, &z_size);
}

INT32 a_icl_set_picture_edit_type_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_PICTURE_EDIT_TYPE_SIZE;

    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_PICTURE_EDIT_TYPE_STATUS, ICL_RECID_PICTURE_EDIT_TYPE_STATUS), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_get_picture_edit_type_status (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_PICTURE_EDIT_TYPE_SIZE;

    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_PICTURE_EDIT_TYPE_STATUS, ICL_RECID_PICTURE_EDIT_TYPE_STATUS), (VOID*) pui1_val, &z_size);
}

INT32 a_icl_set_hdr_type_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_HDR_TYPE_SIZE;

    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_HDR_TYPE_STATUS, ICL_RECID_HDR_TYPE_STATUS), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_get_hdr_type_status (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_HDR_TYPE_SIZE;

    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_HDR_TYPE_STATUS, ICL_RECID_HDR_TYPE_STATUS), (VOID*) pui1_val, &z_size);
}

INT32 a_icl_set_3rd_play_status (UINT8 ui1_val)
{
    SIZE_T z_size = ICL_RECID_3RD_PLAY_SIZE;

    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_3RD_PLAY_STATUS, ICL_RECID_3RD_PLAY_STATUS), (VOID*) &ui1_val, z_size);
}

INT32 a_icl_get_3rd_play_status (UINT8* pui1_val)
{
    SIZE_T z_size = ICL_RECID_3RD_PLAY_SIZE;

    if (pui1_val == NULL)
    {
        return ICLR_FAIL;
    }
    return a_icl_get (ICL_MAKE_ID(ICL_GRPID_3RD_PLAY_STATUS, ICL_RECID_3RD_PLAY_STATUS), (VOID*) pui1_val, &z_size);
}



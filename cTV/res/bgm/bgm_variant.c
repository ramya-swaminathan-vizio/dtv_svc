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
 * $RCSfile: bgm_variant.c,v $
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "app_util/a_cfg.h"

#include "bgm/bgm.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "bgm/mtk_comp/bgm_power_mgmt/a_bgm_power_mgmt.h"
#include "bgm/mtk_comp/bgm_updater_uli/a_bgm_updater_uli.h"
#include "bgm/mtk_comp/bgm_pre_shutdown/a_bgm_pre_shutdown.h"
#include "bgm/mtk_comp/bgm_oled_compensation/a_bgm_oled_compensation.h"

#ifdef MTK_CAMERA_DPTZ_SUPPORT 
#include "bgm/mtk_comp/bgm_motor/a_bgm_motor.h"
#endif

#ifdef SYS_C4TV_SUPPORT
#include "bgm/mtk_comp/bgm_cast_update/a_bgm_cast_update.h"
#endif

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/simple_logo/a_simple_logo.h"

#ifdef APP_BLUETOOTH_SUPPORT
#include "bluetooth_gatt/bluetooth_gattc_wake.h"
#include "app_util/a_bluetooth.h"
#endif

#include "wizard_anim/a_wzd.h"
#include "app_util/a_icl_common.h"


/*-----------------------------------------------------------------------------
    customizable macros
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    macros, defines
-----------------------------------------------------------------------------*/
/* First/repeat button delay */
#ifdef APP_BT_AC_ON_PATCH
#define  FIRST_KEY_DELAY                 ((UINT16)  600)
#define  NEXT_KEY_DELAY                  ((UINT16)  200)
#else
  #ifdef APP_WIFI_BGM
#define  FIRST_KEY_DELAY                 ((UINT16)  600)
#define  NEXT_KEY_DELAY                  ((UINT16)  200)
  #endif
#endif


/*-----------------------------------------------------------------------------
    typedefs, enums, structures
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    function declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    data, variable declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    private function implementations
-----------------------------------------------------------------------------*/
#ifdef APP_BT_AC_ON_PATCH
static BOOL b_g_enter_bgm = FALSE;
static BOOL b_g_is_watch_dog_reset = FALSE;
#else
   #ifdef APP_WIFI_BGM
static BOOL b_g_enter_bgm = FALSE;
   #endif
#endif

static BOOL  b_is_bgm_reboot_enter_bgm = FALSE;

extern int a_set_is_pin_confirmed(BOOL b_confirm);
extern BOOL a_bgm_oled_compensation_first_setup();

/*-----------------------------------------------------------------------------
    public function implementations
-----------------------------------------------------------------------------*/
static VOID print_wakeup_reason(PCL_WAKE_UP_REASON_T e_wakeup_reason){
    switch(e_wakeup_reason){

    case PCL_WAKE_UP_REASON_UNKNOWN :
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_UNKNOWN]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_VGA:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_VGA]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_RTC:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_RTC]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_FP:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_FP]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_IRRC:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_IRRC]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_UART:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_UART]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_AC_POWER:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_AC_POWER]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_HDMI:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_HDMI]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_FP_INP_SRC:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_FP_INP_SRC]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_DVD:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_DVD]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_RTC_SPECIAL:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_RTC_SPECIAL]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_WATCHDOG:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_WATCHDOG]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_ETHERNET:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_ETHERNET]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_RESUME_FROM_SUSPEND:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_RESUME_FROM_SUSPEND]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_WIFI:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_WIFI]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_BT:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_BT]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_RC_NETFLIX:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_RC_NETFLIX]\n", __FUNCTION__, __LINE__));
        break;
    case PCL_WAKE_UP_REASON_CAST:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=[PCL_WAKE_UP_REASON_CAST]\n", __FUNCTION__, __LINE__));
        break;
    default:
        DBG_LOG_PRINT(("%s() %d: wakeup reason=%d\r\n", __FUNCTION__, __LINE__, e_wakeup_reason));
        break;
    }
}

extern  INT32 a_bgm_updater_dlm_register();
extern  INT32 a_bgm_cast_c4tv_register(VOID);

static INT32 _bgm_toast_wgl_nfy_fct (UINT32    ui4_msg,VOID*  pv_param1,VOID*  pv_param2)
{
    return  0;
}

INT32 bgm_custom_register_component(VOID)
{

#ifdef SYS_C4TV_SUPPORT
       a_bgm_cast_update_register();
#endif

    a_bgm_cast_c4tv_register();

    /* BGM_COMP_ID_POWER_MANAGEMENT */
    a_bgm_power_mgmt_register();

#ifdef APP_ULI_UPG_SUPPORT
    /* BGM_COMP_ID_UPDATER_ULI */
    a_bgm_updater_uli_register();
#endif

#ifdef MTK_CAMERA_DPTZ_SUPPORT
    a_bgm_motor_register();
#endif
    /* BGM_COMP_ID_PRE_SHUTDOWN */
    a_bgm_pre_shutdown_register();

    a_bgm_updater_dlm_register();

#ifdef MT5695_MODEL
   a_bgm_oled_compensation_register();
#endif

   /* Register to Widget Library. */
   c_wgl_register (_bgm_toast_wgl_nfy_fct);

    return BGMR_OK;
}

#ifdef APP_BT_AC_ON_PATCH
static INT32 _bgm_for_bt_disable_key(VOID)
{
    INT32           i4_ret = 0;
    IRRC_SETTING_T  t_irrc_setting;
    HANDLE_T        h_iom = NULL_HANDLE;
    UINT8           ui8_evt_src = 0;
    SIZE_T          z_info_len = sizeof(UINT64) ;

    a_amb_enable_power_key (FALSE);

    /* Register to IOM in order to receive raw data. */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));

    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = (FIRST_KEY_DELAY / 10); /* 10 ms per unit */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = (NEXT_KEY_DELAY / 10);  /* 10 ms per unit */
    t_irrc_setting.b_notify_raw_data        = TRUE;
    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) & t_irrc_setting,
                         NULL,
                         NULL,/* If set notify function, sys will crash*/
                         & h_iom);
    BGM_CHK_FAIL (i4_ret);

    /* Disable Remote control. */
    z_info_len = sizeof (UINT64);
    i4_ret = c_iom_get (h_iom,
                        IOM_GET_IRRC_EVT_SRC_MASK,
                        (VOID*)& ui8_evt_src,
                        & z_info_len);
    BGM_CHK_FAIL( i4_ret);

    ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                     IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL));

    i4_ret = c_iom_set (h_iom,
                        IOM_SET_IRRC_EVT_SRC_MASK,
                        (VOID*)& ui8_evt_src,
                        sizeof (UINT64));
    BGM_CHK_FAIL(i4_ret);

    i4_ret = c_iom_close (h_iom);
    BGM_CHK_FAIL(i4_ret);

    return BGMR_OK;
}
#else

  #ifdef APP_WIFI_BGM
static INT32 _bgm_for_wifi_modul_init_disable_key(VOID)
{
    INT32           i4_ret = 0;
    IRRC_SETTING_T  t_irrc_setting;
    HANDLE_T        h_iom = NULL_HANDLE;
    UINT8           ui8_evt_src = 0;
    SIZE_T          z_info_len = sizeof(UINT64) ;

    a_amb_enable_power_key (FALSE);

    /* Register to IOM in order to receive raw data. */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));

    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = (FIRST_KEY_DELAY / 10); /* 10 ms per unit */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = (NEXT_KEY_DELAY / 10);  /* 10 ms per unit */
    t_irrc_setting.b_notify_raw_data        = TRUE;
    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) & t_irrc_setting,
                         NULL,
                         NULL,/* If set notify function, sys will crash*/
                         & h_iom);
    BGM_CHK_FAIL (i4_ret);

    /* Disable Remote control. */
    z_info_len = sizeof (UINT64);
    i4_ret = c_iom_get (h_iom,
                        IOM_GET_IRRC_EVT_SRC_MASK,
                        (VOID*)& ui8_evt_src,
                        & z_info_len);
    BGM_CHK_FAIL( i4_ret);

    ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                     IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL));

    i4_ret = c_iom_set (h_iom,
                        IOM_SET_IRRC_EVT_SRC_MASK,
                        (VOID*)& ui8_evt_src,
                        sizeof (UINT64));
    BGM_CHK_FAIL(i4_ret);

    i4_ret = c_iom_close (h_iom);
    BGM_CHK_FAIL(i4_ret);

    return BGMR_OK;
}
  #endif
#endif

static INT32 _bgm_custom_nfy_action(
            BGM_ACTION_TYPE_T   e_action_type,
            VOID*               pv_info,
            SIZE_T              z_info_len,
            VOID*               pv_tag )
{
    INT32                   i4_ret = BGMR_OK;
    PCL_WAKE_UP_REASON_T    e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;

    /* Get wake-up reason. */
    i4_ret = c_pcl_get_wakeup_reason (& e_wakeup_reason, NULL);
    if (BGMR_OK != i4_ret)
    {
        DBG_ERROR((BGM_ERROR_HEADER"get wakeup reason failed.\n"));
    }

#ifdef APP_BLUETOOTH_SUPPORT    // bluetooth support
    if ( (BGM_ACTION_PCL_POWER_DOWN == e_action_type)
        && (PCL_WAKE_UP_REASON_RTC == e_wakeup_reason) )
    {
        DBG_LOG_PRINT(( "[BGM]_bgm_custom_nfy_action => %d, Set BT suspend.. \n",e_action_type));
        bluetooth_gatt_wake_on_ble_enable(TRUE);
    }
#endif

    return BGMR_OK;
}

static BOOL _bgm_custom_is_power_on_directly(VOID)
{
    INT32   i4_ret = BGMR_OK;
    BOOL    b_bootup = FALSE;
    UINT8   ui1_force_reboot_flag = ACFG_FORCE_REBOOT_UP_OFF;
    UINT16  ui2_wzd_status = 0;
    UINT8 ui1_value = ACFG_VLOG_OFF;
    UINT32 ui4_watchdog_flag = 0;
    UINT32 ui4_bgmupdate_flag = 0;

    do {
        //odm condition to bootup
        if (a_factory_need_burning_in())
        {
            DBG_LOG_PRINT(("<BGM VARIANT> %d: odm power on\r\n",__LINE__));
            b_bootup = TRUE;
            break;
        }

        //service reset to bootup.
        a_cfg_cust_get_force_reboot_up_flag(&ui1_force_reboot_flag);

        if (ACFG_FORCE_REBOOT_UP_ON == ui1_force_reboot_flag)
        {
            DBG_LOG_PRINT(("<BGM VARIANT> %d: force reboot\r\n",__LINE__));
            b_bootup = TRUE;
            break;
        }

#ifdef APP_RETAIL_MODE_SUPPORT
        //Retail mode to bootup directly.
        ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        if (ACFG_RETAIL_MODE_NORMAL     == t_retail_mode ||
            ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
        {
            DBG_LOG_PRINT(("<BGM VARIANT> %d: retail mode OLED:%d\r\n",__LINE__,a_is_oled_compensation_support()));
            b_bootup = TRUE;
            break;
        }

        a_cfg_custom_set_retail_mode_led_ctrl(FALSE);

#endif
        //Wizard not complete to bootup
        if (APP_CFGR_OK == a_cfg_get_wzd_status(&ui2_wzd_status))
        {
            UINT16   ui2_real_status = APP_CFG_WZD_STATUS_INIT;

            ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_wzd_status );
            if(ui2_real_status == WZD_STATE_RESUME_C4TV ||
               ui2_real_status  & WZD_STATE_START_SETUP ||
               ui2_real_status == APP_CFG_WZD_STATUS_INIT)
            {
                DBG_LOG_PRINT(("<BGM VARIANT> %d: OOBE setup\r\n",__LINE__));
                b_bootup = TRUE;
                break;
            }
        }
    } while (0);
#if !defined(APP_SUPPORT_STR_CORE_OFF)
    b_bootup = TRUE;
#endif
    a_cfg_cust_get_ota_loop_test(&ui1_value);
    if(ui1_value == ACFG_VLOG_ON)
    {
        b_bootup = TRUE;
    }
    a_cfg_custom_get_drv_watchdog_flag(&ui4_watchdog_flag);
    a_cfg_custom_get_drv_bgmupdate_flag(&ui4_bgmupdate_flag);
    DBG_LOG_PRINT(("<BGM VARIANT> %d: ui4_watchdog_flag=0x%x ui4_bgmupdate_flag:%d \r\n",__LINE__,ui4_watchdog_flag,ui4_bgmupdate_flag));
    if(ui4_watchdog_flag == 1)
    {
        if(ui4_bgmupdate_flag == 1)
        {
            b_bootup = FALSE;
        }
        else
        {
            b_bootup = TRUE;
        }
    }
#ifdef MT5695_MODEL
    {
        UINT8 ui1_error_count = 0;
        a_cfg_custom_get_oled_error_detect_count(&ui1_error_count);
        if(ui1_error_count >2)
        {
            DBG_LOG_PRINT(("<BGM VARIANT> oled error more then 3 times block power on \r\n"));
            b_bootup = FALSE;
        }
    }
#endif
    DBG_LOG_PRINT(("<BGM VARIANT> %d: b_bootup=%d \r\n",__LINE__,b_bootup));
    return b_bootup;
}

extern INT32 a_cfg_get_wifi_dongle_type();

VOID _bgm_SetLineOutMute(BOOL b_on)
{
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_idx = (UINT8)b_on;
    DBG_LOG_PRINT(("<BGM VARIANT>%s %d b_on=%d\r\n",__FUNCTION__,__LINE__,ui1_idx));
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LineOutMute ;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size);
    BGM_LOG_ON_FAIL(i4_ret);
    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 bgm_custom_get(BGM_CUSTOM_GET_TYPE_T    e_type,
                     VOID*     pv_get_info,
                     SIZE_T*   pz_get_info_len)
{
    INT32    i4_ret    = BGMR_OK;
    UINT32   ui4_custom_status   = 0;

    if (pv_get_info == NULL ||
        pz_get_info_len == NULL)
    {
        return BGMR_INV_ARG;
    }

    switch (e_type)
    {
        case BGM_CUSTOM_GET_TYPE_PRE_RUNNING_DURATION:
        {
            if (*pz_get_info_len != sizeof(UINT32))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }
        #ifdef APP_BT_AC_ON_PATCH
            if (b_g_enter_bgm)
            {
                if (b_g_is_watch_dog_reset)
                {
                    (*(UINT32 *)pv_get_info) = 22000;   /* wait for bluetooth*/
                }
                else
                {
                    (*(UINT32 *)pv_get_info) = 2 * BGM_PRE_RUNNING_TRANSITION_TO_RUNNING_DURATION + 3000;   /* wait for bluetooth*/
                }
            }
            else
        #endif
            {
                (*(UINT32 *)pv_get_info) = BGM_PRE_RUNNING_TRANSITION_TO_RUNNING_DURATION;
            }
        }
        break;

        case BGM_CUSTOM_GET_TYPE_RUNNING_TIMEOUT_DURATION:
        {
            if (*pz_get_info_len != sizeof(UINT32))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }

            (*(UINT32 *)pv_get_info) = BGM_RUNNING_TIMEOUT_DURATION;
        }
        break;

        case BGM_CUSTOM_GET_TYPE_SERVICE_RESET_SUPPORT:
        {
            if (*pz_get_info_len != sizeof(BOOL))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }

            (*(BOOL *)pv_get_info) = TRUE;
        }
        break;

        case BGM_CUSTOM_GET_TYPE_SERVICE_RESET:
        {
            DBG_LOG_PRINT(("<BGM VARIANT>BGM_CUSTOM_GET_TYPE_SERVICE_RESET\r\n",__LINE__));
            a_cfg_cust_set_force_reboot_up_flag(ACFG_FORCE_REBOOT_UP_OFF);
            a_cfg_store();
            AP_SYSTEM_CALL("reboot");
        }
        break;

        case BGM_CUSTOM_GET_TYPE_BGM_MODE_APPLICABLE:
        {
            BOOL   b_is_bgm_applicable = TRUE;

            if (*pz_get_info_len != sizeof(BOOL))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }

            a_bgm_get_custom_status(& ui4_custom_status);
            DBG_LOG_PRINT(("<BGM VARIANT>bgm_custom_get %d: ui4_custom_status = 0x%x \r\n",__LINE__, ui4_custom_status));
            do
            {
                /* 1. If the OAD Firmware upgraded successfully (and partition is changed.)
                   2. If the USD Upgrade successfully.
                   3. No matter UI is showing or not.
                   "Quiet Boot" is not applicable.
                */
#ifdef APP_BT_AC_ON_PATCH
                if (b_g_enter_bgm)
                {
                    bgm_set_runnable_component_mask(0);
                    b_is_bgm_applicable = TRUE;
                    break;
                }
#else

  #ifdef APP_WIFI_BGM
                if (b_g_enter_bgm)
                {
                    bgm_set_runnable_component_mask(0);
                    b_is_bgm_applicable = TRUE;
                    break;
                }
  #endif
#endif
                if ( (ui4_custom_status & BGM_CUSTOM_STATUS_BIT_OAD_FIRMWARE_UPGRADED) ||
                     (ui4_custom_status & BGM_CUSTOM_STATUS_BIT_USB_UPGRADE_APPLIED))
                {
                    UINT32  ui4_misc_ctrl = 0;

                    /* Clear quiet boot flag to avoid enter the BGM mode when boot-up */
                    c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
                    ui4_misc_ctrl &= ~PCL_MISC_CTRL_QUIET_BOOT;
                    c_pcl_set_misc_ctrl(ui4_misc_ctrl);

                    b_is_bgm_applicable = FALSE;
                    break;
                }

                DBG_LOG_PRINT(("<BGM VARIANT>bgm_custom_get %d: enter condition => %d\r\n",__LINE__,bgm_get_enter_condition()));
                if (bgm_get_enter_condition() == BGM_ENTER_CONDITION_FROM_STANDBY_TO_BGM)
                {
                    if ((ui4_custom_status & BGM_CUSTOM_STATUS_BIT_ACTIVE_STANDBY))
                    {
                        UINT32 ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;

                        a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);

                        DBG_LOG_PRINT(("<BGM VARIANT>bgm_custom_get %d: ui4_drv_power mode = %d\r\n",__LINE__, ui4_drv_eco));

                        if (ICL_CUSTOM_POWER_MODE_ECO != ui4_drv_eco)
                        {
                            /*quick start mode should always  enable all comp to be run*/
                            b_is_bgm_applicable = TRUE;
                            break;
                        }
                        else if (ICL_CUSTOM_POWER_MODE_ECO == ui4_drv_eco)
                        {
                            /* Enter suspend */
                            #ifdef APP_ENABLE_LOOP_TEST
                            if (1)
                            #else
                            if (b_is_bgm_reboot_enter_bgm)
                            #endif
                            {
                                 /*  eco mode bgm reboot up,just enable ULI comp for set the correct RTC Time and quick enter standby */
                                bgm_set_runnable_component_mask(BGM_MAKE_COMP_ID_BIT_MASK(BGM_COMP_ID_UPDATER_ULI));
                            }
                            else
                            {
                                /* this case will just be run only for eco mode & ac on */
                                if(access("/data/bgm_dlm_restart",0) == 0)
                                {
                                    DBG_LOG_PRINT(("<BGM VARIANT> !!!!! dlm restart !!!!!!\r\n"));
                                    AP_SYSTEM_CALL("rm -rf /data/bgm_dlm_restart");
                                    bgm_set_runnable_component_mask(BGM_ALL_COMP_ID_BIT_MASK);
                                }
                                else
                                {
                                    bgm_set_runnable_component_mask(0);
                                }
                                AP_SYSTEM_CALL("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 radio_off");
                                DBG_LOG_PRINT(("Noitfy wlan0 to radio_off.\r\n"));


                            }
                            b_is_bgm_applicable = TRUE;
                            break;
                        }
                    }
                }
                else if (bgm_get_enter_condition() == BGM_ENTER_CONDITION_FROM_NORMAL_TO_BGM) /* Enter BGM mode only the enter condition is Standby to BGM. */
                {
                    UINT8   ui1_force_reboot_flag = ACFG_FORCE_REBOOT_UP_OFF;

                    /* DC off, set pin_confirmed to be false*/
                    DBG_LOG_PRINT(("%s, [%d], a_set_is_pin_confirmed (FALSE)\n",__FUNCTION__, __LINE__));
                    a_set_is_pin_confirmed(FALSE);

                    /*check if it is the force reboot up, just do not allow enter bgm */
                    a_cfg_cust_get_force_reboot_up_flag(&ui1_force_reboot_flag);

                    if (ACFG_FORCE_REBOOT_UP_ON == ui1_force_reboot_flag)
                    {
                        DBG_LOG_PRINT(("\n[BGM] BGM_ENTER_CONDITION_FROM_NORMAL_TO_BGM Reject[ACFG_FORCE_REBOOT_UP_ON]\n"));
                        /* here should clean the force reboot flag*/
                        b_is_bgm_applicable = FALSE;
                        break;
                    }

                    UINT32  ui4_power_mode = 0;
                    i4_ret = a_cfg_custom_get_drv_eco_mode(&ui4_power_mode);

                    DBG_LOG_PRINT(("<BGM VARIANT>bgm_custom_get %d: ui1_power_mode=%d\r\n",__LINE__,ui4_power_mode));
                    if (i4_ret == ICLR_OK && ICL_CUSTOM_POWER_MODE_QUICK_START == ui4_power_mode)
                    {
                        /*quick start normal---> bgm should enable all bgm comp  to be run*/
                        b_is_bgm_applicable = TRUE;
                        break;
                    }

                    /* Default reject Normal to BGM */
                    b_is_bgm_applicable = FALSE;
                    break;
                }

            } while(0);

            (*(BOOL *)pv_get_info) = b_is_bgm_applicable;
        }
        break;

        case BGM_CUSTOM_GET_TYPE_CHECK_QUIET_BOOT_WAKEUP_REASON:
        {
            BGM_CHECK_QUIET_BOOT_WAKEUP_REASON_T*   pt_check = (BGM_CHECK_QUIET_BOOT_WAKEUP_REASON_T*) pv_get_info;

            if (*pz_get_info_len != sizeof(BGM_CHECK_QUIET_BOOT_WAKEUP_REASON_T))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }
            print_wakeup_reason(pt_check->e_wakeup_reason); // PCL_WAKE_UP_REASON_T

            /* Check wakeup reason */
            pt_check->b_quiet_boot_applicable = FALSE;    /* Default is not applicable. */
#ifdef MT5695_MODEL
            {
                UINT8 ui1_error_count = 0;
                a_cfg_custom_get_oled_error_detect_count(&ui1_error_count);
                if(ui1_error_count > 2)
                {
                    DBG_LOG_PRINT(("<BGM VARIANT> oled error more then 3 times block power on \r\n"));
                    a_bgm_get_custom_status(&ui4_custom_status);
                    ui4_custom_status |= BGM_CUSTOM_STATUS_BIT_ACTIVE_STANDBY;
                    a_bgm_set_custom_status(ui4_custom_status);
                    pt_check->b_quiet_boot_applicable = TRUE;
                    i4_ret = BGMR_OK;
                    break;
                }
            }
#endif

#ifdef APP_BT_AC_ON_PATCH
            b_g_enter_bgm = FALSE;

            if ( pt_check->ui4_sub_reason == PCL_WAKE_UP_SUB_REASON_CUSTOM_1)
            {
                b_g_enter_bgm = TRUE;
                if (pt_check->e_wakeup_reason == PCL_WAKE_UP_REASON_IRRC)
                {
                    /*
                     *  A trick here. In pcd_mw.c, if the wakeup reason is watchdog, the wakeup
                     *  reason will be altered to be IRRC. But the sub-wakeup reason will still
                     *  be CUSTOM1.
                     *  Hence, we can determine whether it is watchdog reset by the combination
                     *  of wakeup reason and sub wakeup reason.
                     */
                    b_g_is_watch_dog_reset = TRUE;
                }
                pt_check->b_quiet_boot_applicable = TRUE;  /* Quiet-boot is applicable. */
                bgm_set_runnable_component_mask(0);
                _bgm_for_bt_disable_key();  /* Disable the IR&BT keys and frnot panel keys under BT BGM*/
            }
            else if ( pt_check->e_wakeup_reason == PCL_WAKE_UP_REASON_RTC)         /* Wakeup reason is RTC. */
#else
      #ifdef APP_WIFI_BGM
            b_g_enter_bgm = FALSE;

            if( pt_check->ui4_sub_reason == PCL_WAKE_UP_SUB_REASON_CUSTOM_3)
            {
                b_g_enter_bgm = TRUE;

                pt_check->b_quiet_boot_applicable = TRUE;  /* Quiet-boot is applicable. */
                bgm_set_runnable_component_mask(0);
                _bgm_for_wifi_modul_init_disable_key();  /* Disable the IR&BT keys and frnot panel keys under BT BGM*/
            }
            else if ( pt_check->e_wakeup_reason == PCL_WAKE_UP_REASON_RTC)         /* Wakeup reason is RTC. */
     #else
            if ( pt_check->e_wakeup_reason == PCL_WAKE_UP_REASON_RTC)         /* Wakeup reason is RTC. */
     #endif
#endif
            {
                DBG_LOG_PRINT(("[BGM][%s %d] pt_check->ui4_sub_reason = %d\n",__FUNCTION__,__LINE__,pt_check->ui4_sub_reason));
                if (pt_check->ui4_sub_reason & PCL_WAKE_UP_SUB_REASON_QUIET_BOOT) /* Wakeup sub-reason is QUIET boot. */
                {
                    a_bgm_set_custom_status(0); //clean custom status
                }
                pt_check->b_quiet_boot_applicable = TRUE;  /* Quiet-boot is applicable. */
            }
            else if ((PCL_WAKE_UP_REASON_AC_POWER == pt_check->e_wakeup_reason)||
                     (PCL_WAKE_UP_REASON_CUSTOM_3 == pt_check->e_wakeup_reason))
            {
                UINT8   ui1_drv_eco   = 0;
                UINT8   ui1_exit_code = 0;

                a_cfg_custom_get_oled_status(&ui1_exit_code);
                if(ui1_exit_code > 0 && a_bgm_oled_compensation_first_setup())
                {
                    a_cfg_custom_get_power_mode_save(&ui1_drv_eco);
                    DBG_LOG_PRINT(("[BGM][%s,%d]: need reconvert power mode setting ui2_drv_eco = %d\r\n", __FUNCTION__, __LINE__,ui1_drv_eco));
                    a_cfg_custom_set_power_mode(ui1_drv_eco);
                }

                if (_bgm_custom_is_power_on_directly())
                {
                    pt_check->b_quiet_boot_applicable = FALSE;
//MVP-5276. the case of poower on directly after AC_ON.(not enter STR)
//Keys will be blocked by IR QHB state=1. So clear it.
#ifdef SYS_QUIET_HOT_BOOT_SUPPORT
                    a_bgm_force_clear_quiet_hot_boot();
                    DBG_LOG_PRINT(("[QHB]Clear QHB flag for IR when enter Direct power on... \n"));
#endif
                    a_slogo_hide(0);
                    DBG_LOG_PRINT(("[BGM][%s,%d]: Direct power on...\r\n", __FUNCTION__, __LINE__));
                    break;
                }

                a_bgm_get_custom_status(&ui4_custom_status);
                ui4_custom_status |= BGM_CUSTOM_STATUS_BIT_ACTIVE_STANDBY;
                a_bgm_set_custom_status(ui4_custom_status);
                pt_check->b_quiet_boot_applicable = TRUE;

                if ((TRUE == pt_check->b_quiet_boot_applicable)&&
                    (PCL_WAKE_UP_REASON_CUSTOM_3 == pt_check->e_wakeup_reason))
                {
                    DBG_LOG_PRINT(("\n[BGM_TEST] CHECK_QUIET_BOOT_WAKEUP_REASON b_is_bgm_reboot_enter_bgm[TRUE]\n"));
                    b_is_bgm_reboot_enter_bgm = TRUE;
                }
                else
                {
                    b_is_bgm_reboot_enter_bgm = FALSE;
                }
            }
        }
        break;

        case BGM_CUSTOM_GET_TYPE_NOTIFY_ACTION_ENTRANCE:
        {
            a_cfg_custom_update_usb_power_ctrl();
            BGM_NFY_ACTION_T*   pt_nfy = (BGM_NFY_ACTION_T*) pv_get_info;
            if (*pz_get_info_len != sizeof(BGM_NFY_ACTION_T))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }

            pt_nfy->pf_nfy_action = _bgm_custom_nfy_action;
            pt_nfy->pv_tag = NULL;

        }
        break;
        case BGM_CUSTOM_GET_TYPE_NEED_POWER_CUT_AFTER_TIMEOUT:
        {
            if (*pz_get_info_len != sizeof(BOOL))
            {
                i4_ret = BGMR_INV_ARG;
                break;
            }

            UINT32 ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;

            a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);

            if(ui4_drv_eco == ICL_CUSTOM_POWER_MODE_ECO)
            {
                (*(BOOL *)pv_get_info) = TRUE;
            }
            else
            {
                (*(BOOL *)pv_get_info) = FALSE;
            }
        }
        break;
        case BGM_CUSTOM_GET_TYPE_NEED_RESTART_BGM_COMP:
        {
            if (pv_get_info != NULL
                && pz_get_info_len != NULL
                && sizeof(BOOL) == *pz_get_info_len)
            {
                UINT8 ui1_val = BGM_POWER_DOWN_MODE_NORMAL;

                a_icl_get_bgm_power_down_mode (&ui1_val);
                UINT32 ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;

                a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);
                /* if quick start running, should always restart bgm*/
                if (ui4_drv_eco == ICL_CUSTOM_POWER_MODE_QUICK_START)
                {
                    if (BGM_POWER_DOWN_MODE_FORCE_REBOOT == ui1_val)
                    {
                        /*bgm update have been complete and all bgm comp have been run over,here just need to run the cast c4tv  comp*/
                        DBG_LOG_PRINT(("\n[BGM]BGM_CUSTOM_GET_TYPE_NEED_RESTART_BGM_COMP Force_Reboot[CAST_C4TV]\n"));
                        bgm_set_runnable_component_mask(BGM_MAKE_COMP_ID_BIT_MASK(BGM_COMP_ID_CAST_C4TV));
                    }

                    DBG_LOG_PRINT(("\n[BGM]BGM_CUSTOM_GET_TYPE_NEED_RESTART_BGM_COMP return TRUE.\n"));
                    *(BOOL*)pv_get_info = TRUE;
                }
                else
                {
                    DBG_LOG_PRINT(("\n[BGM] BGM_CUSTOM_GET_TYPE_NEED_RESTART_BGM_COMP return FALSE.\n"));
                    *(BOOL*)pv_get_info = FALSE;
                }
            }
            break;
        }

        default:
                break;

    }

    return i4_ret;
}

BOOL a_bgm_custom_is_power_on_directly_def(VOID)
{
    BOOL    b_power_on = FALSE;
    UINT32  ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;
    UINT8   ui1_mode = 0;
    UINT32  ui4_model_idx = 0;
    UINT16  ui2_status = 0;
    UINT8   ui1_bootup_assist = 0;

#ifdef APP_RETAIL_MODE_SUPPORT
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
#endif

    a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);
    DBG_LOG_PRINT(("%s() %d: ui4_drv_eco=%d\r\n", __FUNCTION__, __LINE__, ui4_drv_eco));

    a_cfg_get_factory_mode(&ui1_mode);
    a_cfg_custom_get_model_idx(&ui4_model_idx);

    DBG_LOG_PRINT(("%s() %d: ui1_mode=%d, ui4_model_idx=%d\r\n", __FUNCTION__, __LINE__, ui1_mode, ui4_model_idx));
    do {
        if((APP_CFG_FAC_MODE_BURNING_MASK & ui1_mode) || 0 == ui4_model_idx)
        {
            b_power_on = TRUE;
            DBG_LOG_PRINT(("<BGM VARIANT> %d Power on for model_idx[%d], fac_mode[%d]\r\n",__LINE__,ui4_model_idx,ui1_mode));
            break;
        }

#ifdef APP_RETAIL_MODE_SUPPORT
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            b_power_on = TRUE;
            DBG_LOG_PRINT(("<BGM VARIANT> %d Power on for retail mode is %d\r\n",__LINE__,t_retail_mode));
            break;
        }
#endif
        if (ICL_CUSTOM_POWER_MODE_ECO == ui4_drv_eco)
        {
            DBG_INFO(("<BGM VARIANT> %d ui2_bootup_assist=%d\n", __LINE__, ui1_bootup_assist));

            if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
            {
                UINT16   ui2_real_status = APP_CFG_WZD_STATUS_INIT;

                ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_status );
                a_cfg_custom_get_bootup_assistant_flag(&ui1_bootup_assist);
               if(((ui2_real_status == WZD_STATE_RESUME_C4TV) && (ACFG_BOOTUP_ASSISTANT_FAC_RESET == ui1_bootup_assist)) ||
                   (ui2_real_status  & WZD_STATE_START_SETUP) ||
                   ui2_real_status == APP_CFG_WZD_STATUS_INIT)
                {
                    DBG_LOG_PRINT(("<BGM VARIANT> %d Power on for oobe \r\n",__LINE__));
                    b_power_on = TRUE;
                    break;
                }
            }
        }
    }while (0);

    DBG_LOG_PRINT(("_bgm_custom_is_power_on_directly return %d\n", b_power_on));
    return b_power_on;
}
/*-----------------------------------------------------------------------------
    export function implementations
-----------------------------------------------------------------------------*/


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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifndef A_NAV_UPDATER_H_
#define A_NAV_UPDATER_H_

/*-----------------------------------------------------------------------------
                    include files
 -----------------------------------------------------------------------------*/

#include "u_common.h"
#include "nav/nav_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 -----------------------------------------------------------------------------*/

struct _UPDATER_VIEW_HDLR_T;

typedef enum
{
    NAV_UPDATER_ULI_COMPLETE = 0,
    NAV_UPDATER_ULI_FAIL,
    NAV_UPDATER_ULI_ABORT
} NAV_UPDATER_ULI_COND_T;

typedef INT32 (*updater_uli_bgm_nfy_fct)
(
    NAV_UPDATER_ULI_COND_T    e_cond,
    VOID*                     pv_data
);

/*The follow struct will be define fill uli rest*/
typedef enum _NAV_UPDATE_ULI_USER_REG_INFO_T
{
    NAV_UPDATE_ULI_REG_INFO_PHONE_NUM = 0,
    NAV_UPDATE_ULI_REG_INFO_FIRST_NAME,
    NAV_UPDATE_ULI_REG_INFO_LAST_NAME,
    NAV_UPDATE_ULI_REG_INFO_ZIP_CODE,
    NAV_UPDATE_ULI_REG_INFO_MAIL,
    NAV_UPDATE_ULI_REG_INFO_COMMIT,
    NAV_UPDATE_ULI_REG_INFO_LAST_ENTRY
}NAV_UPDATE_ULI_USER_REG_INFO_T;

/* Available update info */
typedef struct _NAV_UPDATE_ULI_AVAIL_INFO_T
{
    UINT8 ui1_fw_status;
    UINT8 ui_fw_policy;
    CHAR  s_ver[64];
}NAV_UPDATE_ULI_AVAIL_INFO_T;

/* Update status */
typedef struct _NAV_UPDATE_ULI_UPDATE_STATUS_T
{
    UINT8 ui1_update_status;
    UINT8 ui1_progress;
}NAV_UPDATE_ULI_UPDATE_STATUS_T;


#define NAV_UPDATE_ULI_REG_INFO_GROUP_NUM            (1)
#define NAV_UPDATE_ULI_REG_INFO_STR_MAX_LEN          (64)
#define NAV_UPDATE_ULI_REG_INFO_JSON_TXT_MAX_LEN     (NAV_UPDATE_ULI_REG_INFO_STR_MAX_LEN*4/3 + 4)
#define NAV_UPDATE_ULI_REG_INFO_JSON_TXT_GROUP_MAX_LEN     (1024)
#define NAV_UPDATE_ULI_REG_INFO_SN_LEN                     (32)
#define NAV_UPDATE_ULI_REG_INFO_SN_JSON_LEN                (NAV_UPDATE_ULI_REG_INFO_SN_LEN*4/3 + 4)
#define NAV_UPDATE_ULI_REG_INFO_MAC_LEN                    (20)
#define NAV_UPDATE_ULI_REG_INFO_MAC_JSON_LEN               (NAV_UPDATE_ULI_REG_INFO_MAC_LEN*4/3 + 4)
#define NAV_UPDATE_ULI_REG_INFO_VN_LEN                     (32)
#define NAV_UPDATE_ULI_REG_INFO_VN_JSON_LEN                (NAV_UPDATE_ULI_REG_INFO_VN_LEN*4/3 + 4)
#define NAV_UPDATE_ULI_REG_INFO_DT_LEN                     (32)
#define NAV_UPDATE_ULI_REG_INFO_DT_JSON_LEN                (NAV_UPDATE_ULI_REG_INFO_DT_LEN*4/3 + 4)

#define NAV_UPDATE_ULI_SN_JSON_KEY                           "'SN':'"
#define NAV_UPDATE_ULI_MAC_JSON_KEY                          "RD01,{'MA':'"
#define NAV_UPDATE_ULI_VN_JSON_KEY                           "'VN':'"
#define NAV_UPDATE_ULI_DT_JSON_KEY                           "'DT':'"
#define NAV_UPDATE_ULI_EMAIL_JSON_KEY                        "'EM':'"
#define NAV_UPDATE_ULI_FIRST_NAME_JSON_KEY                   "'FN':'"
#define NAV_UPDATE_ULI_LAST_NAME_JSON_KEY                    "'LN':'"
#define NAV_UPDATE_ULI_PHONE_NUM_JSON_KEY                    "'PH':'"
#define NAV_UPDATE_ULI_ZIP_CODE_JSON_KEY                     "'ZC':'"
#define NAV_UPDATE_ULI_OFFER_CONTACT_JSON_KEY                "'OC':'"

#define NAV_UPDATE_ULI_USER_REGISTER_ACTION_NO                ((UINT8)0)
#define NAV_UPDATE_ULI_USER_REGISTER_ACTION_YES               ((UINT8)1)

#define NAV_UPDATE_ULI_DEVICE_REGISTER_ACTION_NO              ((UINT8)0)
#define NAV_UPDATE_ULI_DEVICE_REGISTER_ACTION_YES             ((UINT8)1)

#define NAV_UPDATE_ULI_UPDATING_ACTION_NO                     ((UINT8)0)
#define NAV_UPDATE_ULI_UPDATING_ACTION_YES                    ((UINT8)1)

#define NAV_UPDATE_FW_AVALIABLE_SATUS_NO                     ((UINT8)0)
#define NAV_UPDATE_FW_AVALIABLE_SATUS_YES                    ((UINT8)1)
#define NAV_UPDATE_FW_AVALIABLE_SATUS_CHECK_BUSY             ((UINT8)2)

#define NAV_UPDATE_FW_POLICY_DEFAULT                         ((UINT8)3)

#define NAV_UPDATE_FW_UPDATE_STATUS_NONE                     ((UINT8)0)
#define NAV_UPDATE_FW_UPDATE_STATUS_DOWNLOADING              ((UINT8)1)
#define NAV_UPDATE_FW_UPDATE_STATUS_APPLYING                 ((UINT8)2)
#define NAV_UPDATE_FW_UPDATE_STATUS_FINISHED                 ((UINT8)3)
#define NAV_UPDATE_FW_UPDATE_STATUS_FAIL                     ((UINT8)4)
#define NAV_UPDATE_FW_UPDATE_STATUS_CHECKING                 ((UINT8)5)
#define NAV_UPDATE_FW_UPDATE_STATUS_FW_FOUND                 ((UINT8)6)

/*update ver string*/
#define NAV_UPDATE_FW_VER_STR_MAX_LEN                (64)
/*-----------------------------------------------------------------------------
                    functions declarations
 -----------------------------------------------------------------------------*/
extern INT32 a_nav_updater_register
(
    struct _UPDATER_VIEW_HDLR_T*    pt_updater_view_hdlr
);

extern INT32 a_nav_updater_is_updating_status(
    BOOL*                         pb_is_updating_status
);
extern INT32 a_nav_updater_iom_lock_power_key(BOOL b_is_to_lock);
extern INT32 updater_reset_log_file( VOID );
extern INT32 updater_log_printf(
    const CHAR *format,
    ...);

extern INT32 a_nav_updater_set_power_on_from_bgm_flag(BOOL b_is_from_bgm);
extern BOOL a_nav_updater_is_power_on_from_bgm( VOID );


#ifdef APP_NET_UPG_SUPPORT
extern INT32 a_nav_updater_network_upg_manual_start(
    VOID
);
#endif

#ifdef APP_ULI_UPG_SUPPORT
extern INT32 a_nav_updater_uli_download_start(
    updater_uli_bgm_nfy_fct    pf_nfy_fct
);

extern INT32 a_nav_updater_uli_download_stop(
    VOID
);

extern INT32 a_nav_updater_uli_get_avail_delay(
    UINT32*    pui4_avail_delay
);
extern BOOL a_nav_updater_is_uli_loop_test( VOID );


/*For Rest Menu*/

/*user info register*/
extern INT32 a_nav_updater_uli_register_user_info(CHAR p_str_user_info[][NAV_UPDATE_ULI_REG_INFO_STR_MAX_LEN],
                                              UINT8 ui1_str_num);

/*user info register new for json data*/
extern INT32 a_nav_updater_uli_register_user_info_new(CHAR p_str_user_info[]);

/*user register status check*/
extern INT32 a_nav_updater_uli_get_user_register_status(UINT8 *pui1_user_register_status);
/*device register status check*/
extern INT32 a_nav_updater_uli_get_device_register_status(UINT8 *pui1_device_register_status);
/*get updating status*/
extern INT32 a_nav_updater_uli_get_updating_status(UINT8 *pui1_updating_status);

/*fw check*/
extern INT32 a_nav_updater_check_fw_avaliable(UINT8 *pui1_fw_status,
                                                   UINT8 *pui_fw_policy);
/*fw download & install*/
extern INT32 a_nav_updater_download_firmware_and_trigger_update(UINT8  *pui1_fw_status);

/**/
extern INT32 a_nav_updater_get_update_status(UINT8  *pui1_update_status,
                                                                UINT8  *pui1_progress);
extern INT32 nav_updater_set_update_ver_string(CHAR *s_ver_str);
extern INT32 nav_updater_get_update_ver_string(CHAR *s_ver_str);

/*Reboot from oobe update*/
INT32 a_nav_updater_uli_set_oobe_update_finished(BOOL   b_oobe_update);

#endif
#endif /* A_NAV_UPG_H_ */


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
 * $RCSfile: a_menu.h,v $
 * $Revision: #1 $
 * $Date: 2015/11/12 $
 * $Author: lin.xu $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: b03a97c1c03188e0d495fb71d27fc7e7 $
 *
 * Description:
 *         This file contains the implementation of the APIs of application
 *         manager.
 *---------------------------------------------------------------------------*/

#ifndef _A_REST_H_
#define _A_REST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "amb/a_amb.h"
#include "rest_cmd.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define REST_NAME                            "rest"    /* max length = 16*/


/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: a_rest_registration
 *
 * Description:
 *      The notification function of menu application. This callbakc function
 *  is used when dtv menu is a SLAVE one in the
 *  ATV/DTV integration solution.
 * Inputs:
 *      e_cond - condition of notification
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern VOID a_rest_registration(
    AMB_REGISTER_INFO_T*   pt_reg
);

extern INT32 rest_get_access_point_by_ssid(CHAR *ps_ssid, REST_DATA_WIFI_AP_T *pt_ap);
extern UINT32 a_rest_get_cast_version_build_number(VOID);
extern INT32 a_rest_ask_session (CHAR* ps_cred, CHAR* ps_session_token, UINT16 ui2_token_size);
extern INT32 a_rest_get_cast_state ();
extern VOID  rest_start_softap_ex(VOID);
extern VOID  rest_stop_softap_ex(VOID);

#define TEST_CODE 1   //Shengbao Xu

/*
{
    "APP_ID": {
        "NAME_SPACE": 3,
        "APP_ID": "1",
        "MESSAGE": null },
    "CNAME": "netflix",  // Canonical name for the virtual input, must be unique across all virtual inputs created. Max 16 characters.
    "NAMES": {  // An object with key/value pairs of language code, ISO 6391, to friendly input display name. Based on the current language of the device use the correct language key to look up the friendly input name. Max 16 characters.
        "en":"NETFLIX",
        "fr":"NETFLIX",
        "es":"NETFLIX" },
    "HIDEABLE": false,  // Boolean value. if false, the virtual input is not hideable by an end user within the settings menu.
    "AFTER_CNAME": "cast"   // References the CNAME of the input this virtual input should follow in the input selector list. If this value is null then the virtual input should appear as the first item in the list.
}
*/
typedef struct _TYPE_APP_VTRL_INPUT
{
    CHAR    s_cname[24];
    CHAR    s_name_en[3][24]; // en, es, fr
    BOOL    b_hideable;
    CHAR    s_position_after[24];
    INT32   i4_launch_name_space;
    CHAR    launch_app_id[16];
    CHAR    launch_msg[1024];
} TYPE_APP_VTRL_INPUT;

#ifdef __cplusplus
}
#endif

#endif /* _A_REST_H_ */

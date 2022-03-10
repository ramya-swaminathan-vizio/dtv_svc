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
 * $RCSfile: a_download_util.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/19 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 7ed3c11a9ed90eba15305b24039bcab7 $
 *
 * Description:
 *      This file contains the implementation of channel lists.
 *---------------------------------------------------------------------------*/
#ifndef __A_DOWNLOAD_UTIL_H__
#define __A_DOWNLOAD_UTIL_H__

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* Return Values */
#define DUR_OK                                              ((INT32) 0)
#define DUR_FAIL                                            ((INT32)-1)
#define DUR_INV_ARG                                         ((INT32)-2)

typedef enum{
    TOS_TYPE_TOS_ENG = 0,
    TOS_TYPE_TOS_FRE,
    TOS_TYPE_TOS_SPA,
    TOS_TYPE_PRIVACY_ENG,
    TOS_TYPE_PRIVACY_FRE,
    TOS_TYPE_PRIVACY_SPA,
    TOS_TYPE_LAST_VALID_ITEM
}TOS_TYPE_T;

typedef enum{
    VIZIO_PRIVACY_POLICY_US_EN = 0,
    VIZIO_PRIVACY_POLICY_US_FR,
    VIZIO_PRIVACY_POLICY_US_SPA,
    VIZIO_PRIVACY_POLICY_CA_EN,
    VIZIO_PRIVACY_POLICY_CA_FR,
    VIZIO_PRIVACY_POLICY_CA_SPA,
    VIZIO_PRIVACY_POLICY_MX_EN,
    VIZIO_PRIVACY_POLICY_MX_FR,
    VIZIO_PRIVACY_POLICY_MX_SPA,
    VIZIO_PRIVACY_POLICY_LAST_VALID_ITEM
}VIZIO_TOS_PRIVACY_POLICY_TYPE_T;


typedef enum{
    VIZIO_POLICY_PRIVACY = 0,
    VIZIO_POLICY_SMARTCAST,
    VIZIO_POLICY_VIEWDATA,
    VIZIO_POLICY_TOS,
    VIZIO_POLICY_GOOGLE_TOS,       /*not use*/
    VIZIO_POLICY_GOOGLE_PRIVACY,   /*not use*/
    VIZIO_POLICY_VIEWDATA_OVERVIEW,
    VIZIO_POLICY_LAST_VALID_ITEM
}VIZIO_POLICY_TYPE_T;


typedef enum{
    VIZIO_COUNTRY_US = 0,
    VIZIO_COUNTRY_CA,
    VIZIO_COUNTRY_MX,
    VIZIO_COUNTRY_LAST_VALID_ITEM
}VIZIO_COUNTRY_TYPE_T;

typedef enum{
    VIZIO_LANG_EN = 0,
    VIZIO_LANG_FR,
    VIZIO_LANG_SPA,
    VIZIO_LANG_LAST_VALID_ITEM
}VIZIO_LANG_TYPE_T;

#define MAKE_ITEM(item,country,lang,policy) do{\
    item = country;\
    item = item<< 8;\
    item |= lang;\
    item = item<< 8;\
    item |= policy;\
}while(0)

#define SPLIT_ITEM(item,country,lang,policy) do{\
     policy = item & 0xff;\
     lang  =  (item & 0xff00)>> 8;\
     country = (item & 0xff0000)>> 16;\
}while(0)

#define GET_POLICY_ITEM_STATE(item,state) do{\
     state = item & 0xff;\
}while(0)

#define GET_POLICY_ITEM(item_status,item) do{\
     item = item_status >> 8;\
}while(0)

/*-----------------------------------------------------------------------------
                    public function declarations
 ----------------------------------------------------------------------------*/
#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT

extern INT32 a_download_util_file(VOID);

extern BOOL a_um_chk_manual_is_up_to_date(VOID);

extern BOOL a_um_get_url_date_info_utc_sec(TIME_T* pt_url_date);

extern BOOL a_um_get_exist_date_info_utc_sec(TIME_T* pt_url_date);

extern BOOL a_is_dld_um_in_flash(VOID);

extern BOOL a_show_dld_um(VOID);

extern BOOL a_um_clear_temp(VOID);

extern VOID a_um_set_opera_start_status(BOOL b_status);

extern BOOL a_um_get_opera_start_status(VOID);

extern VOID a_um_set_opera_exit_status(BOOL b_status);

extern BOOL a_um_get_opera_exit_status(VOID);

extern VOID a_um_set_status_is_displaying(BOOL b_status);

extern BOOL a_um_get_status_is_displaying(VOID);

extern BOOL a_um_is_server_avalible(VOID);

#endif
#endif

/* for Terms of service and Privacy policy download */
#ifdef APP_DYNAMIC_TOS_SUPPORT

extern BOOL a_tos_is_file_exist(TOS_TYPE_T e_type);

extern INT32 a_tos_get_file_path(TOS_TYPE_T e_type, CHAR* ps_buf_path);

extern INT32 a_tos_download_util_file(TOS_TYPE_T e_type);

#endif


extern INT32 a_url_download(VIZIO_COUNTRY_TYPE_T country,VIZIO_LANG_TYPE_T lang,VIZIO_POLICY_TYPE_T policy);
extern BOOL a_is_policy_file_exist(VIZIO_COUNTRY_TYPE_T e_country,VIZIO_LANG_TYPE_T lang,VIZIO_POLICY_TYPE_T e_policy);
extern INT32 a_get_policy_file_path(VIZIO_COUNTRY_TYPE_T e_country,VIZIO_LANG_TYPE_T lang,VIZIO_POLICY_TYPE_T e_policy,CHAR* sz_file_path,INT32 ui4_max_name_len);
#endif /* __A_DOWNLOAD_UTIL_H__ */


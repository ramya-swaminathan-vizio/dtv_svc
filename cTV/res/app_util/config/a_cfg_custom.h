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
 * $RCSfile: a_cfg_custom.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_CFG_CUSTOM_H_
#define _A_CFG_CUSTOM_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_cecm.h"

#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"

#include "app_util/a_cfg_rmdr.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/config/acfg_cust_audio.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/config/acfg_cust_mmp.h"
//#include "res/app_util/config/acfg_cust_factory.h"

#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* Remap the EEP0 offset to EEP3 offset */
#define EEP_OFFSET_REMAP(ui4_offset)  ((ui4_offset) - EEP_OFFSET_EEP0_START)

#undef ACFG_MAX_REC_SIZE
#define ACFG_MAX_REC_SIZE           512 /* cust define the acfg elem max size*/

/* make this feature active */
#ifndef APP_PRESET_CH_FOR_FAC_SUPPORT
#define APP_PRESET_CH_FOR_FAC_SUPPORT
#endif

#ifndef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
#define NEW_TIME_LOCAL_AUTO_DST_SUPPORT
#endif

#define AP_SYSTEM_CALL(shell) \
do{\
    pid_t status;\
    status = system(shell);\
    if(-1 == status)\
    {\
        DBG_ERROR(("[%s %d]system error\n\r",__FUNCTION__,__LINE__));\
    }\
    else\
    {\
        if(WIFEXITED(status))\
        {\
            if(0 != WEXITSTATUS(status))\
            {\
                 DBG_ERROR(("[%s %d]run shell script[%s] fail,script exit code:%d\n\r",__FUNCTION__,__LINE__,shell,WEXITSTATUS(status)));\
            }\
            else\
            {\
                DBG_INFO(("[%s %d]run shell script[%s] successfully.\n\r",__FUNCTION__,__LINE__,shell));\
            }\
        }\
        else\
        {\
            DBG_ERROR(("[%s %d]exit status = [%d]\n\r",__FUNCTION__,__LINE__,WEXITSTATUS(status)));\
        }\
    }\
}while(0)


#define AP_SYSTEM_CALL_EX(shell,ret)  \
do{\
    pid_t status;\
    status = system(shell);\
    if(-1 == status)\
    {\
        DBG_ERROR(("[%s %d]system error\n\r",__FUNCTION__,__LINE__));\
    }\
    else\
    {\
        if(WIFEXITED(status))\
        {\
            if(0 != WEXITSTATUS(status))\
            {\
                 DBG_ERROR(("[%s %d]run shell script[%s] fail,script exit code:%d\n\r",__FUNCTION__,__LINE__,shell,WEXITSTATUS(status)));\
            }\
            else\
            {\
                DBG_INFO(("[%s %d]run shell script[%s] successfully.\n\r",__FUNCTION__,__LINE__,shell));\
            }\
        }\
        else\
        {\
            DBG_ERROR(("[%s %d]exit status = [%d]\n\r",__FUNCTION__,__LINE__,WEXITSTATUS(status)));\
        }\
    }\
    ret = status;\
}while(0)


/*def value define*/
/*SPEC V3.4 change max name len 24*/
#define APP_CFG_CUSTOM_INP_NAME_LEN                     (24)
#define APP_CFG_CUSTOM_RENAME_PIC_MODE_NAME_LEN         (11)

/* retail demo picture mode */
#define ACFG_RETAIL_PIC_MODE_DEF                        (3)

/* value define for tv name*/
#define MAX_TV_NAME_LEN                                (32)
#define APP_CFG_CUSTOM_TV_NAME_DFT                     "VIZIOTV"

/*cast name max length*/
#define MAX_CAST_NAME_LEN                                (32)

/*wzd sys upgrade status*/
#define APP_CFG_CUST_WZD_SYS_UPDATE_INIT           ((UINT8) 0)
#define APP_CFG_CUST_WZD_SYS_UPDATE_COMPLETE       ((UINT8) 1)

/* Zoom mode status */
#define APP_CFG_CUST_ZOOM_MODE_OFF                 ((UINT8) 0)
#define APP_CFG_CUST_ZOOM_MODE_ON                  ((UINT8) 1)

#define APP_CFG_CUST_SURROUND_MODE_OFF                 ((UINT8) 2)
#define APP_CFG_CUST_SURROUND_MODE_ON                  ((UINT8) 1)
#define APP_CFG_CUST_SURROUND_VIRTUAL_X                ((UINT8) 0)

/* acfg field group & recid info*/

/* Group Misc. */
#define APP_CFG_RECID_CUSTOM_TIMEZONE           ((UINT16) 1)
#define APP_CFG_RECID_CUSTOM_ANLG_CC            ((UINT16) 2)
#define APP_CFG_RECID_CUSTOM_DIG_CC             ((UINT16) 3)
#define APP_CFG_RECID_CUSTOM_ADDITIONAL_SCAN    ((UINT16) 4)
#define APP_CFG_RECID_CUSTOM_ANALOG_AUD_OUT     ((UINT16) 5)
#define APP_CFG_RECID_CUSTOM_INP_NAME_1         ((UINT16) 6)
#define APP_CFG_RECID_CUSTOM_INP_NAME_2         ((UINT16) 7)
#define APP_CFG_RECID_CUSTOM_INP_NAME_3         ((UINT16) 8)
#define APP_CFG_RECID_CUSTOM_INP_NAME_4         ((UINT16) 9)
#define APP_CFG_RECID_CUSTOM_INP_NAME_5         ((UINT16)10)
#define APP_CFG_RECID_CUSTOM_INP_NAME_6         ((UINT16)11)
#define APP_CFG_RECID_CUSTOM_INP_NAME_7         ((UINT16)12)
#define APP_CFG_RECID_CUSTOM_INP_NAME_8         ((UINT16)13)
#define APP_CFG_RECID_CUSTOM_INP_NAME_9         ((UINT16)14)
#define APP_CFG_RECID_CUSTOM_INP_NAME_10        ((UINT16)15)
#define APP_CFG_RECID_CUSTOM_OP_MODE            ((UINT16)16)
#define APP_CFG_RECID_CUSTOM_POSTAL_CODE        ((UINT16)17)
#define APP_CFG_RECID_CUSTOM_ULPK_FLAG          ((UINT16)18)
#define APP_CFG_RECID_DISP_CUSTOM_RETAIL_MODE   ((UINT16)19)
#define APP_CFG_RECID_CUSTOM_WZD_SUB_IDX        ((UINT16)20)
#define APP_CFG_RECID_CUSTOM_UPDATER_COMPLETED  ((UINT16)21)
#ifdef CC_DISCRETE_REMOTE_CODE
#define APP_CFG_RECID_CUSTOM_LAST_AV            ((UINT16)22)
#define APP_CFG_RECID_CUSTOM_LAST_COMP          ((UINT16)23)
#define APP_CFG_RECID_CUSTOM_LAST_HDMI          ((UINT16)24)
#endif
#define APP_CFG_RECID_CUSTOM_COUNTRY_CODE       ((UINT16)25)
#define APP_CFG_RECID_CUSTOM_LED_LOGO_CTRL      ((UINT16)26)

/* Reserve Field */
#define APP_CFG_RECID_CUST_RSEV_UI1_0           ((UINT16)38)
#define APP_CFG_RECID_CUST_RSEV_UI1_1           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 1)
#define APP_CFG_RECID_CUST_RSEV_UI1_2           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 2)
#define APP_CFG_RECID_CUST_RSEV_UI1_3           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 3)
#define APP_CFG_RECID_CUST_RSEV_UI1_4           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 4)
#define APP_CFG_RECID_CUST_RSEV_UI1_5           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 5)
#define APP_CFG_RECID_CUST_RSEV_UI1_6           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 6)
#define APP_CFG_RECID_CUST_RSEV_UI1_7           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 7)
#define APP_CFG_RECID_CUST_RSEV_UI1_8           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 8)
#define APP_CFG_RECID_CUST_RSEV_UI1_9           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 9)
#define APP_CFG_RECID_CUST_RSEV_UI1_10          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 10)
#define APP_CFG_RECID_CUST_RSEV_UI1_11          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 11)
#define APP_CFG_RECID_CUST_RSEV_UI1_12          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 12)
#define APP_CFG_RECID_CUST_RSEV_UI1_13          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 13)
#define APP_CFG_RECID_CUST_RSEV_UI1_14          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 14)
#define APP_CFG_RECID_CUST_RSEV_UI1_15          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 15)
#define APP_CFG_RECID_CUST_RSEV_UI1_16          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 16)
#define APP_CFG_RECID_CUST_RSEV_UI1_17          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 17)
#define APP_CFG_RECID_CUST_RSEV_UI1_18          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 18)
#define APP_CFG_RECID_CUST_RSEV_UI1_19          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 19)
#define APP_CFG_RECID_CUST_RSEV_UI1_20          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 20)
#define APP_CFG_RECID_CUST_RSEV_UI1_21          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 21)
#define APP_CFG_RECID_CUST_RSEV_UI1_22          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 22)
#define APP_CFG_RECID_CUST_RSEV_UI1_23          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 23)
#define APP_CFG_RECID_CUST_RSEV_UI1_24          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 24)
#define APP_CFG_RECID_CUST_RSEV_UI1_25          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 25)
#define APP_CFG_RECID_CUST_RSEV_UI1_26          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 26)
#define APP_CFG_RECID_CUST_RSEV_UI1_27          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 27)
#define APP_CFG_RECID_CUST_RSEV_UI1_28          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 28)
#define APP_CFG_RECID_CUST_RSEV_UI1_29          (APP_CFG_RECID_CUST_RSEV_UI1_0 + 29)

#define APP_CFG_RECID_CUST_RSEV_UI2_0           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 30)
#define APP_CFG_RECID_CUST_RSEV_UI2_1           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 31)
#define APP_CFG_RECID_CUST_RSEV_UI2_2           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 32)
#define APP_CFG_RECID_CUST_RSEV_UI2_3           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 33)
#define APP_CFG_RECID_CUST_RSEV_UI2_4           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 34)
#define APP_CFG_RECID_CUST_RSEV_UI2_5           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 35)
#define APP_CFG_RECID_CUST_RSEV_UI2_6           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 36)
#define APP_CFG_RECID_CUST_RSEV_UI2_7           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 37)
#define APP_CFG_RECID_CUST_RSEV_UI2_8           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 38)
#define APP_CFG_RECID_CUST_RSEV_UI2_9           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 39)

#define APP_CFG_RECID_CUST_RSEV_UI4_0           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 40)
#define APP_CFG_RECID_CUST_RSEV_UI4_1           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 41)
#define APP_CFG_RECID_CUST_RSEV_UI4_2           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 42)
#define APP_CFG_RECID_CUST_RSEV_UI4_3           (APP_CFG_RECID_CUST_RSEV_UI1_0 + 43)

#define APP_CFG_RECID_CUST_ACFG_LST_IDX         (APP_CFG_RECID_CUST_RSEV_UI1_0 + 44)

/* reserve field ex UNIT1 8BIT*/
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_0           ((UINT16)100)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_1           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 1)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_2           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 2)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_3           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 3)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_4           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 4)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_5           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 5)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_6           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 6)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_7           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 7)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_8           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 8)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_9           (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 9)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_10          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 10)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_11          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 11)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_12          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 12)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_13          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 13)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_14          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 14)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_15          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 15)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_16          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 16)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_17          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 17)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_18          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 18)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_19          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 19)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_20          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 20)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_21          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 21)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_22          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 22)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_23          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 23)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_24          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 24)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_25          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 25)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_26          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 26)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_27          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 27)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_28          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 28)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_29          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 29)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_30          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 30)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_31          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 31)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_32          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 32)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_33          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 33)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_34          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 34)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_35          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 35)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_36          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 36)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_37          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 37)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_38          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 38)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_39          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 39)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_40          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 40)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_41          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 41)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_42          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 42)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_43          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 43)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_44          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 44)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_45          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 45)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_46          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 46)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_47          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 47)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_48          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 48)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_49          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 49)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_50          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 50)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_51          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 51)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_52          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 52)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_53          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 53)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_54          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 54)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_55          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 55)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_56          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 56)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_57          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 57)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_58          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 58)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_59          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 59)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_60          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 60)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_61          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 61)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_62          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 62)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_63          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 63)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_64          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 64)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_65          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 65)
#define APP_CFG_RECID_CUST_RSEV_UI1_EX_66          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 66)


#define APP_CFG_RECID_CUST_RSEV_UI1_EX_99          (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 99)

/* reserve field ex UNIT1 16BIT  160 bit total*/
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_0            (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 100)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_1            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  1)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_2            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  2)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_3            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  3)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_4            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  4)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_5            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  5)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_6            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  6)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_7            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  7)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_8            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  8)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_9            (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  9)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_10           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 10)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_11           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 11)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_12           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 12)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_13           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 13)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_14           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 14)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_15           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 15)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_16           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 16)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_17           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 17)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_18           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 18)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_19           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 19)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_20           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 20)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_21           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 21)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_22           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 22)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_23           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 23)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_24           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 24)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_25           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 25)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_26           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 26)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_27           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 27)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_28           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 28)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_29           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 29)
#define APP_CFG_RECID_CUST_RSEV_UI2_EX_30           (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 + 30)

#define APP_CFG_RECID_CUST_RSEV_UI2_EX_79          (APP_CFG_RECID_CUST_RSEV_UI2_EX_0 +  79)

/* reserve field ex UNIT1 32BIT 280 bit total*/
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_0            (APP_CFG_RECID_CUST_RSEV_UI1_EX_0 + 180)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_1            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 1)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_2            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 2)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_3            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 3)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_4            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 4)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_5            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 5)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_6            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 6)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_7            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 7)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_8            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 8)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_9            (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 9)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_10           (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 10)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_11           (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 11)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_12           (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 12)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_13           (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 13)
#define APP_CFG_RECID_CUST_RSEV_UI4_EX_14           (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 14)


#define APP_CFG_RECID_CUST_RSEV_UI4_EX_69           (APP_CFG_RECID_CUST_RSEV_UI4_EX_0 + 69)

/* Group plf_opt. */
#define APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE       (APP_CFG_GRPID_CUSTOM_BASE + 1)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_3D_SUPPORT     ((UINT16) 1)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_PIP_SUPPORT    ((UINT16) 2)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_BT_SUPPORT     ((UINT16) 3)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_04             ((UINT16) 4)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_05             ((UINT16) 5)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_06             ((UINT16) 6)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_07             ((UINT16) 7)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_08             ((UINT16) 8)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_09             ((UINT16) 9)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_10             ((UINT16) 10)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_11             ((UINT16) 11)
#define APP_CFG_RECID_CUSTOM_PLF_OPT_12             ((UINT16) 12)

/* Group Video. */
#define APP_CFG_RECID_VID_CUSTOM_DCR            (APP_CFG_RECID_VID_CUSTOM_BASE + 0)
#define APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR   (APP_CFG_RECID_VID_CUSTOM_BASE + 1)
#define APP_CFG_RECID_VID_CUSTOM_H_SIZE         (APP_CFG_RECID_VID_CUSTOM_BASE + 2)
#define APP_CFG_RECID_VID_CUSTOM_V_SIZE         (APP_CFG_RECID_VID_CUSTOM_BASE + 3)
#define APP_CFG_RECID_VID_CUSTOM_DIMMING        (APP_CFG_RECID_VID_CUSTOM_BASE + 4)

/*video new & will begin from 16+APP_CFG_RECID_VID_CUSTOM_BASE*/

/* custom pic mode name should be store by src*/
#define APP_CFG_RECID_VID_CUST_PIC_MODE_0_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 16))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_1_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 17))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_2_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 18))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_3_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 19))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_4_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 20))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_5_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 21))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_6_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 22))  /* Picture Mode Name */
#define APP_CFG_RECID_VID_CUST_PIC_MODE_7_NAME      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 23))  /* Picture Mode Name */

/* Should be by src & pic*/
#define APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS     ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 24))

/* lock status & pwd should be globe*/
#define APP_CFG_RECID_VID_CUST_PIC_LOCK_STATUS      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 25))
#define APP_CFG_RECID_VID_CUST_PIC_LOCK_PWD         ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 26))


/* Video Quality */
/* Color Temp */
#define APP_CFG_RECID_VID_CLR_HUE_R                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 27))  /* Color Gain R */
#define APP_CFG_RECID_VID_CLR_HUE_G                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 28))  /* Color Gain G */
#define APP_CFG_RECID_VID_CLR_HUE_B                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 29))  /* Color Gain B */
#define APP_CFG_RECID_VID_CLR_SAT_R                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 30))  /* Color Offset R */
#define APP_CFG_RECID_VID_CLR_SAT_G                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 31))  /* Color Offset G */
#define APP_CFG_RECID_VID_CLR_SAT_B                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 32))  /* Color Offset B */
#define APP_CFG_RECID_VID_CLR_BRI_R                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 33))  /* Color Offset R */
#define APP_CFG_RECID_VID_CLR_BRI_G                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 34))  /* Color Offset G */
#define APP_CFG_RECID_VID_CLR_BRI_B                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 35))  /* Color Offset B */
#define APP_CFG_RECID_VID_CLR_HUE_C                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 36))  /* Color Gain R */
#define APP_CFG_RECID_VID_CLR_HUE_M                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 37))  /* Color Gain G */
#define APP_CFG_RECID_VID_CLR_HUE_Y                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 38))  /* Color Gain B */
#define APP_CFG_RECID_VID_CLR_SAT_C                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 39))  /* Color Offset R */
#define APP_CFG_RECID_VID_CLR_SAT_M                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 40))  /* Color Offset G */
#define APP_CFG_RECID_VID_CLR_SAT_Y                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 41))  /* Color Offset B */
#define APP_CFG_RECID_VID_CLR_BRI_C                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 42))  /* Color Offset R */
#define APP_CFG_RECID_VID_CLR_BRI_M                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 43))  /* Color Offset G */
#define APP_CFG_RECID_VID_CLR_BRI_Y                 ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 44))  /* Color Offset B */
#define APP_CFG_RECID_VID_REDUCE_BLUR               ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 45))

//#define APP_CFG_RECID_VID_GAMMA                     ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 46))
#define APP_CFG_RECID_VID_RED                       ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 47))
#define APP_CFG_RECID_VID_GREEN                     ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 48))
#define APP_CFG_RECID_VID_BLUE                      ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 49))
#define APP_CFG_RECID_VID_11_POINT_GAIN             ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 50))
#define APP_CFG_RECID_VID_11_POINT_GAIN_RED         ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 51))
#define APP_CFG_RECID_VID_11_POINT_GAIN_GREEN       ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 52))
#define APP_CFG_RECID_VID_11_POINT_GAIN_BLUE        ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 53))
#define APP_CFG_RECID_VID_PRE_PIC_CHG               ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 54))
#define APP_CFG_RECID_CUST_PIC_COPY_BASE            ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 55))

/*cust clr gain offset for app*/
#define APP_CFG_RECID_VID_CUST_CLR_GAIN_R           ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 56))  /* Color Offset B */
#define APP_CFG_RECID_VID_CUST_CLR_GAIN_G           ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 57))  /* Color Offset B */
#define APP_CFG_RECID_VID_CUST_CLR_GAIN_B           ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 58))  /* Color Offset B */
#define APP_CFG_RECID_VID_CUST_CLR_OFFSET_R         ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 59))  /* Color Offset B */
#define APP_CFG_RECID_VID_CUST_CLR_OFFSET_G         ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 60))  /* Color Offset B */
#define APP_CFG_RECID_VID_CUST_CLR_OFFSET_B         ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 61))  /* Color Offset B */
#define APP_CFG_RECID_VID_CLR_TEMP_CHG              ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 63))  /* Color Offset B */
#define APP_CFG_RECID_VID_CUST_GAMMA                ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 64))
#define APP_CFG_RECID_VID_CUST_FULL_COLOR_444       ((UINT16) (APP_CFG_RECID_VID_CUSTOM_BASE + 65))


/* CUST MISC BASE DEFINE*/
#define APP_CFG_GRPID_CUST_MISC_BASE                (APP_CFG_GRPID_CUSTOM_BASE + 4)

#define APP_CFG_RECID_CUST_NW_REG_STATUS            ((UINT16) 2)
#define APP_CFG_RECID_CUST_TV_NAME                  ((UINT16) 3)

/* channel scan status */
#define APP_CFG_RECID_CUST_CH_SCAN_STATUS           ((UINT16) 4)

#define APP_CFG_RECID_CUST_WZD_SYS_UPGRADE_STATUS   ((UINT16) 5)
#define APP_CFG_RECID_CUST_CAST_NAME                ((UINT16) 6)

/* Zoom mode */
#define APP_CFG_RECID_CUST_ZOOM_MODE                ((UINT16) 7)

/* Bootup assistant flag */
#define APP_CFG_RECID_CUST_BOOTUP_ASSISTANT_FLAG       ((UINT16) 8)

/* fac amtran 11 point RGB*/
#define APP_CFG_RECID_CUST_FAC_11_POINT_RED             ((UINT16) 9)
#define APP_CFG_RECID_CUST_FAC_11_POINT_GREEN           ((UINT16) 10)
#define APP_CFG_RECID_CUST_FAC_11_POINT_BLUE            ((UINT16) 11)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_R          ((UINT16) 12)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_G          ((UINT16) 13)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_B          ((UINT16) 14)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_C          ((UINT16) 15)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_M          ((UINT16) 16)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_Y          ((UINT16) 17)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_R          ((UINT16) 18)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_G          ((UINT16) 19)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_B          ((UINT16) 20)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_C          ((UINT16) 21)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_M          ((UINT16) 22)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_Y          ((UINT16) 23)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_R          ((UINT16) 24)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_G          ((UINT16) 25)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_B          ((UINT16) 26)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_C          ((UINT16) 27)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_M          ((UINT16) 28)
#define APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_Y          ((UINT16) 29)

#define APP_CFG_RECID_CUST_SURROUND_MODE                ((UINT16) 30)


/* cust audio*/
#define APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS    ((UINT16) (APP_CFG_RECID_AUD_CUSTOM_BASE + 1))

#ifdef APP_MMP_SUPPORT
#define APP_CFG_GRPID_CUSTOM_MMP_BASE           (APP_CFG_GRPID_CUSTOM_BASE + 2)
#define APP_CFG_RECID_CUSTOM_MMP_PHOTO_SET_INFO         ((UINT16)1)
#define APP_CFG_RECID_CUSTOM_MMP_PHOTO_RECUR_PARSING    ((UINT16)2)
#define APP_CFG_RECID_CUSTOM_MMP_AUDIO_RECUR_PARSING    ((UINT16)3)
#define APP_CFG_RECID_CUSTOM_MMP_VIDEO_RECUR_PARSING    ((UINT16)4)
#define APP_CFG_RECID_CUSTOM_MMP_PHOTO_SORT             ((UINT16)5)
#define APP_CFG_RECID_CUSTOM_MMP_AUDIO_SORT             ((UINT16)6)
#define APP_CFG_RECID_CUSTOM_MMP_VIDEO_SORT             ((UINT16)7)
#endif

/* Group ID and Record DI begin */
#define APP_CFG_GRPID_CUSTOM_BLEGATT        (APP_CFG_GRPID_CUSTOM_BASE + 5)

#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_0     1
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_1     2
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_2     3
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_3     4
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_4     5
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_5     6
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_6     7
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_7     8
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_8     9
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_9     10
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_10    11
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_11    12
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_12    13
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_13    14
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_14    15
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_15    16
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_16    17
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_17    18
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_18    19
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_19    20
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_20    21
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_21    22
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_22    23
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_23    24
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_24    25
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_25    26
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_26    27
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_27    28
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_28    29
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_29    30
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_30    31
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_31    32
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_32    33
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_33    34
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_34    35
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_35    36
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_36    37
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_37    38
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_38    39
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_39    40
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_40    41
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_41    42
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_42    43
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_43    44
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_44    45
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_45    46
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_46    47
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_47    48
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_48    49
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_49    50
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_50    51
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_51    52
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_52    53
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_53    54
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_54    55
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_55    56
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_56    57
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_57    58
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_58    59
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_59    60
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_60    61
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_61    62
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_62    63
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_63    64
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_64    65
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_65    66
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_66    67
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_67    68
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_68    69
#define APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_69    70

/* customer timezone setting */
#define APP_CFG_CUST_TZ_HAWAII                       ((UINT8)   0)
#define APP_CFG_CUST_TZ_ALASKA                       ((UINT8)   1)
#define APP_CFG_CUST_TZ_PACIFIC_TIME                 ((UINT8)   2)
#define APP_CFG_CUST_TZ_MOUNTAIN_TIME                ((UINT8)   3)
#define APP_CFG_CUST_TZ_ARIZONA                      ((UINT8)   4)
#define APP_CFG_CUST_TZ_CENTRAL_TIME                 ((UINT8)   5)
#define APP_CFG_CUST_TZ_INDIANA                      ((UINT8)   6)
#define APP_CFG_CUST_TZ_EASTERN_TIME                 ((UINT8)   7)
#define APP_CFG_CUST_TZ_ATLANTIC_TIME                ((UINT8)   8)
#define APP_CFG_CUST_TZ_NEWFOUNDLAND                 ((UINT8)   9)
#define APP_CFG_CUST_TZ_UNKNOWN                      ((UINT8) 255)

#define APP_CFG_CUSTOM_ANA_CC_CC1                    (0)
#define APP_CFG_CUSTOM_ANA_CC_CC2                    (APP_CFG_CUSTOM_ANA_CC_CC1 + 1)
#define APP_CFG_CUSTOM_ANA_CC_CC3                    (APP_CFG_CUSTOM_ANA_CC_CC1 + 2)
#define APP_CFG_CUSTOM_ANA_CC_CC4                    (APP_CFG_CUSTOM_ANA_CC_CC1 + 3)

#define APP_CFG_CUSTOM_DIG_CC_SERVICE1             (0)
#define APP_CFG_CUSTOM_DIG_CC_SERVICE2             (APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 1)
#define APP_CFG_CUSTOM_DIG_CC_SERVICE3             (APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 2)
#define APP_CFG_CUSTOM_DIG_CC_SERVICE4             (APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 3)
#define APP_CFG_CUSTOM_DIG_CC_SERVICE5             (APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 4)
#define APP_CFG_CUSTOM_DIG_CC_SERVICE6             (APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 5)

#if 1//def APP_WIFI_REMOTE_PARING_SUPPORT
#define APP_CFG_WZD_STATUS_WIFI_UNPAIR             ((UINT16)  128)
#endif


/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                        EEPROM Offset
-----------------------------------------------------------------------------*/
enum
{
    EEP_OFFSET_EEP0_START       = 0x460,

    /* ACFG */
    EEP_OFFSET_ACFG_HEADER      = EEP_OFFSET_EEP0_START,    /* 16 bytes */

    /* Picture Quality settings are defined here.
       These settings should be fixed and don't move */
    EEP_OFFSET_CLR_GAIN_R       = 0x470,                    /* 88 bytes: 11 inputs * 8 bytes */
    EEP_OFFSET_CLR_GAIN_G       = 0x4C8,                    /* 88 bytes: 11 inputs * 8 bytes */
    EEP_OFFSET_CLR_GAIN_B       = 0x520,                    /* 88 bytes: 11 inputs * 8 bytes */

    /* For CEC uP */
    EEP_OFFSET_GUI_LANG         = 0x578,                    /* 4 bytes */
    EEP_OFFSET_CEC_FUNC         = 0x57C,                    /* 1 byte */
    EEP_OFFSET_CEC_AUTO_ON      = 0x57D,                    /* 1 byte */

    /* Platform option bytes. 12 bytes. */
    EEP_OFFSET_PLF_OPT_00       = 0x57E,                    /* 1 byte: 3D support. */
    EEP_OFFSET_PLF_OPT_01       = 0x57F,                    /* 1 byte: PIP support. */
    EEP_OFFSET_PLF_OPT_02       = 0x580,                    /* 1 byte: BT sopport.  */
    EEP_OFFSET_PLF_OPT_03       = 0x591,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_04       = 0x592,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_05       = 0x593,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_06       = 0x594,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_07       = 0x595,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_08       = 0x596,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_09       = 0x597,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_10       = 0x598,                    /* 1 byte */
    EEP_OFFSET_PLF_OPT_11       = 0x599,                    /* 1 byte */

	EEP_OFFSET_RETAIL_MODE      = 0x5FD,					/* 1 byte */
	EEP_OFFSET_LED_CTRL         = 0x5FE,
    EEP_OFFSET_COUNTRY_CODE     = 0x5FF,

    /* Platform Option */
    EEP_OFFSET_PLATFORM_OPTION  = 0x600,                    /* 12 bytes */

    EEP_OFFSET_CLR_OFFSET_R     = 0x610,                    /* 88 bytes: 11 inputs * 8 bytes */
    EEP_OFFSET_CLR_OFFSET_G     = 0x668,                    /* 88 bytes: 11 inputs * 8 bytes */
    EEP_OFFSET_CLR_OFFSET_B     = 0x6C0,                    /* 88 bytes: 11 inputs * 8 bytes */
    EEP_OFFSET_FAC_CLR_GAIN_R   = 0x718,
    EEP_OFFSET_FAC_CLR_GAIN_G   = 0x728,
    EEP_OFFSET_FAC_CLR_GAIN_B   = 0x738,

    EEP_OFFSET_FAC_CLR_OFFSET_R = 0x748,
    EEP_OFFSET_FAC_CLR_OFFSET_G = 0x758,
    EEP_OFFSET_FAC_CLR_OFFSET_B = 0x768,

    EEP_OFFSET_FAC_CUST_0       = 0x778,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_1       = 0x779,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_2       = 0x77A,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_3       = 0x77B,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_4       = 0x77C,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_5       = 0x77D,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_6       = 0x77E,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_7       = 0x77F,                  /* 1 byte */
    EEP_OFFSET_FAC_CUST_8       = 0x780,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_9       = 0x781,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_10      = 0x782,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_11      = 0x783,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_12      = 0x784,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_13      = 0x785,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_14      = 0x786,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_15      = 0x787,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_16      = 0x788,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_17      = 0x789,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_18      = 0x78A,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_19      = 0x78B,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_20      = 0x78C,                   /* 1 byte */
    EEP_OFFSET_FAC_CUST_21      = 0x78D,                   /* 1 byte */

    EEP_OFFSET_FAC_CUST_2_0     = 0x78F,                   /* 2 byte */
    EEP_OFFSET_FAC_CUST_2_1     = 0x791,                   /* 2 byte */
    EEP_OFFSET_FAC_CUST_2_2     = 0x793,                   /* 2 byte */
    EEP_OFFSET_FAC_CUST_2_3     = 0x795,                   /* 2 byte */

    EEP_OFFSET_FAC_CUST_4_0     = 0x797,                   /* 4 byte */
    EEP_OFFSET_FAC_CUST_4_1     = 0x79B,                   /* 4 byte */

    PAIRED_RC_MAC_ADDR_BEGIN    = 0x79F,                   /* 6 byte */
    EEP_OFFSET_CODESET          = 0x7A5,                   /* 6 byte */
    EEP_OFFSET_SOUNDBAR_CODESET = 0x7AB,                   /* 6 byte */

    EEP_OFFSET_WZD_STATUS       = 0x7B1,                   /* 2 byte */
    EEP_OFFSET_BOOTUP_ASSISTANT_FLAG = 0x7B3,              /* 2 byte */

    EEP_OFFSET_FAC_CUST_11_POINT_RED        = 0x7B5,          /* 44 byte */
    EEP_OFFSET_FAC_CUST_11_POINT_GREEN      = 0x7E1,          /* 44 byte */
    EEP_OFFSET_FAC_CUST_11_POINT_BLUE       = 0x80D,          /* 44 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_R     = 0x839,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_G     = 0x83D,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_B     = 0x841,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_C     = 0x845,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_M     = 0x849,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_Y     = 0x84D,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_R     = 0x851,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_G     = 0x855,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_B     = 0x859,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_C     = 0x85D,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_M     = 0x861,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_Y     = 0x865,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_R     = 0x869,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_G     = 0x871,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_B     = 0x875,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_C     = 0x879,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_M     = 0x87D,          /* 4 byte */
    EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_Y     = 0x881,          /* 4 byte */

    /* Here will be the buff 4200 byte for extern */

        /* All Other Settings starts here. */
    EEP_OFFSET_ACFG_MISC        = 0x1800,

    /* this value should be calculated later*/
    /* End */
    EEP_OFFSET_END              = 0x1A000,                   /* 2012/12/04 11:35 */
    EEP_OFFSET_ODM_BEGIN        = EEP_OFFSET_END + 1,   // 4095 byte for ODM USE
    EEP_OFFSET_ODM_END      = EEP_OFFSET_ODM_BEGIN + 4094, // Last byte for ODM use

    EEP_OFFSET_EXT_START = EEP_OFFSET_ODM_END + 1,  // For MTK acfg use
    EEP_OFFSET_EXT_END = EEP_OFFSET_EXT_START + 4095, //

};

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#ifdef APP_PRESET_CH_FOR_FAC_SUPPORT
/* preset for factory */
extern INT32 a_cfg_pre_ch_dump_channel_info_2_usb(VOID);
extern INT32 a_cfg_pre_ch_dump_channel_info_2_term(VOID);
extern INT32 a_cfg_pre_ch_load_preset_channel(VOID) ;
#endif

extern HANDLE_T acfg_custom_get_cec_handle (VOID);

/* Misc. */
extern INT32 a_cfg_custom_set_timezone_idx(
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_timezone_idx(
        UINT8*  pui1_idx);

extern INT32 a_cfg_custom_set_cc_idx(
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_cc_idx(
        UINT8*  pui1_idx);

extern INT32 a_cfg_custom_get_cc_val(
        UINT8*  pui1_acc,
        UINT8*  pui1_dcc);

extern INT32 a_cfg_custom_set_additional_scan(
        UINT8   ui1_val);

extern INT32 a_cfg_custom_get_additional_scan (
        UINT8*  pui1_val);

extern INT32 a_cfg_custom_set_ulpk_flag(
        BOOL    b_ulpk_flag);

extern INT32 a_cfg_custom_get_ulpk_flag(
        BOOL*   b_ulpk_flag);

extern INT32 a_cfg_custom_reset_channel_lock(VOID);

extern INT32 a_cfg_custom_set_inp_name(
        UINT8   ui1_input_id,
        CHAR*   s_inp_name);

extern INT32 a_cfg_custom_get_inp_name(
        UINT8   ui1_input_id,
        CHAR*   s_inp_name);

extern INT32 a_cfg_custom_set_cec_name(
        UINT8   ui1_cec_idx,
        CHAR*   s_cec_name);

extern INT32 a_cfg_custom_get_cec_name(
        UINT8   ui1_cec_idx,
        CHAR*   s_cec_name);
extern INT32 a_cfg_custom_get_inp_name_with_cec_name(
        ISL_REC_T*  pt_isl_rec,
        UTF16_T*    w2s_inp_name,
        UINT8       ui1_str_len);

extern INT32 a_cfg_custom_set_opmode(
        A_CFG_OP_MODE_T     e_mode);

extern INT32 a_cfg_custom_get_opmode(
        A_CFG_OP_MODE_T*    pe_mode);

extern BOOL a_cfg_custom_is_inp_name_empty(
        CHAR*   s_str);

extern INT32 a_cfg_custom_reset_all_eq_settings(VOID);
extern INT32 a_cfg_custom_reset_audio (VOID);

extern INT32 a_cfg_custom_reset_pic_settings (VOID);

extern INT32 a_cfg_custom_reset_pic_mode_setting (VOID);

extern INT32 a_cfg_custom_set_pic_mode_vivid (VOID);

extern INT32 a_cfg_custom_set_all_src_pic_mode(ACFG_CUST_PIC_MODE_T  t_pic_mode);

extern INT32 a_cfg_custom_reset_usr_clr_temp(UINT8   ui1_mask);

extern UINT8 acfg_custom_get_input_grp(
        ISL_REC_T*  pt_isl_rec);

extern INT32 a_cfg_custom_set_ana_audio_out(
        A_CFG_CUSTOM_ANALOG_AUD_OUT_T   e_aud_out);

extern INT32 a_cfg_custom_get_ana_audio_out(
        A_CFG_CUSTOM_ANALOG_AUD_OUT_T*  pe_aud_out);

extern INT32 a_cfg_custom_update_ana_audio_out(VOID);

extern INT32 a_cfg_custom_set_auto_ip_config(
        BOOL    b_enable,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_auto_ip_config(
        BOOL*   pb_enable,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_set_ip_addr(
        UINT32  ui4_address,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_ip_addr(
        UINT32* pui4_address,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_set_subnet_mask(
        UINT32  ui4_netmask,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_subnet_mask(
        UINT32* pui4_netmask,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_set_default_gateway(
        UINT32  ui4_gw,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_default_gateway(
        UINT32* pui4_gw,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_set_1st_dns(
        UINT32  ui4_1st_DNS,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_1st_dns(
        UINT32* pui4_1st_DNS,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_set_2nd_dns(
        UINT32  ui4_2nd_DNS,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_get_2nd_dns(
        UINT32* pui4_2nd_DNS,
        UINT8   ui1_idx);

extern INT32 a_cfg_custom_3D_setting_reset_3D_mode(VOID);


extern INT32 a_cfg_custom_set_dimming_idx(
        UINT16  ui2_idx);

extern INT32 a_cfg_custom_get_dimming_idx(
        UINT16* pui2_idx);

extern INT32 a_cfg_custom_update_dimming_idx(VOID);

extern INT32 a_cfg_custom_set_dimming_off(VOID);

extern INT32 a_cfg_reset_svl_by_mask(
        HANDLE_T    h_svl,
        UINT32      ui4_reset_mask,
        UINT32      ui4_reset_value);

#ifdef APP_LED_LOGO_CTRL
extern INT32 a_cfg_custom_set_led_logo_ctrl(UINT8 ui1_idx);
extern UINT16 a_cfg_custom_get_led_logo_ctrl(VOID);
extern INT32 a_cfg_custom_set_led_logo_ctrl_to_drv(UINT8 ui1_idx);
extern INT32 a_cfg_custom_update_led_logo_ctrl(VOID);
extern INT32 a_cfg_custom_set_led_logo_lightness(UINT8 ui1_lightness);
extern INT32 a_cfg_custom_set_led_logo_force_on(UINT8 ui1_idx);
extern INT32 a_cfg_custom_set_dc_qs_off_start_led(void);
extern INT32 a_cfg_custom_set_led_breath_to_drv(UINT8 ui1_second);

#endif

extern INT32 a_cfg_set_lip_sync(INT16 i2_val);
extern INT32 a_cfg_get_lip_sync(INT16* pi2_val);
extern INT32 a_cfg_set_srs_sorround_hd(INT16 i2_val);
extern INT32 a_cfg_get_srs_sorround_hd(INT16* pi2_val);
extern INT32 a_cfg_get_dcr_def_value(UINT8 *pui1_dcr_def);

extern INT32 a_cfg_custom_reset_public_default(VOID);
extern INT32 a_cfg_custom_set_usb_powersaving(VOID);
extern INT32  a_cfg_chk_lock_pic_mode_password(UTF16_T* w2s_pwd, BOOL* pb_pass);

extern INT32 a_cfg_custom_set_usb_power_ctrl(UINT8 ui1_idx);
extern UINT16 a_cfg_custom_get_usb_power_ctrl(VOID);
extern INT32 a_cfg_custom_update_usb_power_ctrl(VOID);
extern INT32 a_cfg_custom_set_usb_virtual_power_ctrl(UINT16  ui2_val);
extern BOOL acfg_is_backlight_control_enable();

extern INT32 a_cfg_cust_led_blinking_start(UINT32 ui4_time);
extern INT32 a_cfg_cust_led_blinking_stop();

extern INT32 a_cfg_cust_set_oled_off_rs(UINT8 ui1_status);
extern INT32 a_cfg_cust_get_oled_off_rs(UINT8 *pui1_status);

extern INT32 a_cfg_cust_set_oled_jb(UINT8 ui1_status);
extern INT32 a_cfg_cust_get_oled_jb(UINT8 *pui1_status);

#endif /* _A_CFG_CUSTOM_H_ */


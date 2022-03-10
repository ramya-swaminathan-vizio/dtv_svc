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
 * $RCSfile: input_src.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _INPUT_SRC_H_
#define _INPUT_SRC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "nav/input_src/a_input_src.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum _NAV_IPTS_SWITCH_SRC_METHOD_T
{
    NAV_IPTS_SMS_NONE = 0,              /*used for init only*/
    NAV_IPTS_SMS_NEXT,
    NAV_IPTS_SMS_PREV,
    NAV_IPTS_SMS_BY_ID,                 /*ui4_param: UINT8, id of source */
    NAV_IPTS_SMS_TO_TV,
    NAV_IPTS_SMS_NEXT_BY_DEVICE_TYPE    /*ui4_param: UINT32, device type*/
} NAV_IPTS_SWITCH_SRC_METHOD_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_ipts_switch_src(NAV_IPTS_SWITCH_SRC_METHOD_T   e_method,
                                 TV_WIN_ID_T                    e_grp,
                                 UINT32                         ui4_param);

extern VOID* nav_ipts_get_view_context (VOID);
extern BOOL a_nav_input_is_cec_processed(VOID);
extern INT32 a_nav_ipts_get_hdmi_ports(VOID);
extern void a_nav_ipts_cancel_smart_cast_after_n_seconds();
extern BOOL a_nav_ipts_first_input_after_boot();
extern BOOL ipts_enable_this_log (UINT16 ui2_log_type);
extern UINT16 ipts_get_log_type (VOID);
extern VOID ipts_set_log_type (UINT16 ui2_log_type);
extern BOOL a_nav_should_display_messaging(VOID);
extern BOOL a_nav_should_display_no_signal_indication(VOID);
extern VOID a_nav_displaying_no_signal_indication(VOID);
extern BOOL a_power_state_off(VOID);
extern BOOL a_smart_cast_switch_pending(VOID);
extern BOOL a_nav_IsPowerOnInputSelect_Automatic(VOID);
extern BOOL a_nav_ipts_on_smartcast(VOID);
extern BOOL _nav_is_boot_sc_enabled();



#define _ISL_LOG_TYPE_NONE                       (UINT16)0
#define _ISL_LOG_TYPE_FUNC                       MAKE_BIT_MASK_16 (0)

#define ISL_LOG(ui2_log_type, param)                                           \
    {                                                                          \
        if (ipts_enable_this_log(ui2_log_type))                              \
        {                                                                      \
            if (ui2_log_type == _ISL_LOG_TYPE_FUNC)                        \
            {                                                                  \
                DBG_LOG_PRINT (("\t[ISL F]"));                                    \
            }                                                                  \
            else                                                               \
            {                                                                  \
                DBG_LOG_PRINT (("\t[ISL ?]"));                                    \
            }                                                                     \
            DBG_LOG_PRINT (("[%+13s:%s:%-4d]", __FILE__,__FUNCTION__, __LINE__)); \
            c_dbg_stmt param;                                                 \
                                                                               \
        }                                                                      \
    }


#ifdef CLI_SUPPORT
extern INT32 ipts_cli_init (VOID) ;
#endif


#endif /* _INPUT_SRC_H_ */

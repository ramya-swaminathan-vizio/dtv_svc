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
 * $RCSfile: a_sleep_timer.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file exports API's of sleep timer.
 *---------------------------------------------------------------------------*/
#ifndef _A_SLEEP_TIMER_H_
#define _A_SLEEP_TIMER_H_

/*-----------------------------------------------------------------------------
 *  include files
 *---------------------------------------------------------------------------*/
#include "u_common.h"

/* Iteration types. */
typedef UINT8                       STIMER_ITERATE_T;

#define STIMER_ITERATE_DIR_NEXT     ((STIMER_ITERATE_T) 1)
#define STIMER_ITERATE_DIR_PREV     ((STIMER_ITERATE_T) 2)
#define STIMER_ITERATE_DIR_FIRST    ((STIMER_ITERATE_T) 3)
#define STIMER_ITERATE_DIR_LAST     ((STIMER_ITERATE_T) 4)
#define STIMER_ITERATE_DIR_CRNT     ((STIMER_ITERATE_T) 5)

/* Return values */
#define STIMERR_OK                     ((INT32)  0)
#define STIMERR_FAIL                   ((INT32) -1)
#define STIMERR_INV_ARG                ((INT32) -2)

typedef enum
{
    STIMER_REASON_EXPIRE_SOON,
    STIMER_REASON_RESCHEDULE,
    STIMER_REASON_TIMEUP
} STIMER_REASON;

typedef enum
{
    STIMER_NFY_SRC_NAV,
    STIMER_NFY_SRC_AUTO_SLEEP,
    STIMER_NFY_SRC_CNT /*for counting purpose*/
} STIMER_NFY_SRC;

/*-----------------------------------------------------------------------------
 * functions declarations
 *---------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_init(VOID);

extern INT32 a_sleep_timer_iterate(
    STIMER_ITERATE_T    t_iter,         /* in */
    UINT8*              pui1_idx,       /* out */
    UINT32*             pui4_time       /* out */
);

extern INT32 a_sleep_timer_start(
    UINT32      ui4_time                /* in */
);

extern INT32 a_sleep_timer_stop(
    VOID
);

extern INT32 a_sleep_timer_get_num_rec(
    UINT8*      pui1_num_rec            /* out */
);

extern INT32 a_sleep_timer_get_time_by_idx(
    UINT8       ui1_idx,                /* in */
    UINT32*     pui4_time               /* out */
);

extern INT32 a_sleep_timer_get_text(
    UINT32      ui4_time,               /* in */
    UTF16_T*    w2s_str,                /* out */
    SIZE_T      z_size                  /* in */
);

extern INT32 a_sleep_timer_get_remaining_text(
    UINT32      ui4_time,               /* in */
    UTF16_T*    w2s_str,                /* out */
    SIZE_T      z_size                  /* in */
);


extern INT32 a_sleep_timer_get_remaining_time(
    UINT32*   pui4_time                 /* out */
);

typedef VOID (*sleep_prompt_nfy_fct) (VOID* pv_tag1,
                                      VOID* pv_tag2,
                                      VOID* pv_tag3);

extern INT32 a_sleep_timer_reg_prompt_nfy(sleep_prompt_nfy_fct pf_nfy_fct,
                                          x_os_timer_cb_fct pf_timer_cb_fct);

extern INT32 a_sleep_set_auto_sleep_timer(UINT32 ui4_sleep_time);
#endif /* _A_SLEEP_TIMER_H_ */

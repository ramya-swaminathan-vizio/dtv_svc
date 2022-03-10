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
 * $RCSfile: _white_pattern.h,v $
 * $Revision: #1 $
 * $Date: 2013/06/21 $
 * $Author: sin_heyiwang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Chris Kuo $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _WHITE_PATTERN_H_
#define _WHITE_PATTERN_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

typedef struct _WHITE_PATTERN_VIEW_T
{
    HANDLE_T                  h_frame;         /* Frame handle. */
    UINT16                    ui2_idx;         /* Pattern index. */
    UINT16                      ui2_pure_clr_idx; /* pure pattern index, 0 is Off */
}   WHITE_PATTERN_VIEW_T;

typedef struct _WHITE_PATTERN_T
{
    WHITE_PATTERN_VIEW_T       t_view;
    HANDLE_T                  h_timer;
    UINT32                    ui4_delay;
    BOOL                      b_is_running;
    BOOL                      b_stop;
    BOOL                      b_IR_inactivate;
    BOOL                      b_is_pure_pattern_running;
#ifdef WHITE_PATTERN_MODIFICATION
    BOOL                      b_is_fact_cmd; // If White/IRE Pattern is set by factory command
#endif
}   WHITE_PATTERN_T;

#define BTN_WHITE_PATTERN                     BTN_FUNCTION_4
#define BTN_PURE_PATTERN                     BTN_FUNCTION_3

#ifdef WHITE_PATTERN_MODIFICATION
enum
{
    WHITE_IRE_OFF = 0,// Turn off White Pattern and IRE Pattern
    WHITE_IRE_16,
    WHITE_IRE_32,
    WHITE_IRE_48,
    WHITE_IRE_64,
    WHITE_IRE_80,
    WHITE_IRE_96,
    WHITE_IRE_112,
    WHITE_IRE_128,
	WHITE_IRE_144,
	WHITE_IRE_160,
    WHITE_IRE_176,
    WHITE_IRE_192,
    WHITE_IRE_208,
    WHITE_IRE_224,
    WHITE_IRE_240,    
    WHITE_IRE_256,    
    WHITE_IRE_DEF = WHITE_IRE_256, // White Pattern Default
    WHITE_IRE_5,// 5 IRE    
};

#endif


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern VOID  white_pattern_rcu_key_handler(
                    UINT32                      ui4_key_code
                    );
extern INT32 white_pattern_view_init(
                    WHITE_PATTERN_T*             pt_this,
                    HANDLE_T                    h_canvas
                    );
extern INT32 white_pattern_view_deinit(
                    WHITE_PATTERN_VIEW_T*        pt_view
                    );
extern INT32 white_pattern_view_show(
                    WHITE_PATTERN_VIEW_T*        pt_view
                    );
extern INT32 white_pattern_view_hide(
                    WHITE_PATTERN_VIEW_T*        pt_view
                    );
extern INT32 white_pattern_view_update(
                    WHITE_PATTERN_VIEW_T*        pt_view
                    );
extern INT32 a_nav_white_pattern_toggle_pattern (VOID);
extern INT32 a_nav_pure_pattern_toggle_pattern (VOID);
extern UINT16 a_nav_pure_pattern_get_index (VOID);
extern UINT16 a_nav_ire_pattern_get_index (VOID);
extern VOID a_nav_pure_pattern_set_index (UINT16 u2_idx);
extern BOOL nav_pure_pattern_is_running (VOID);
#ifdef WHITE_PATTERN_MODIFICATION
extern BOOL nav_pattern_get_is_fact_cmd(VOID);
extern VOID nav_pattern_set_is_fact_cmd(BOOL b_true);
#endif

extern BOOL nav_white_pattern_is_running (VOID);

extern INT32 pure_pattern_view_update(
                    WHITE_PATTERN_VIEW_T*         pt_view
                    );
#endif /* _WHITE_PATTERN_H_ */

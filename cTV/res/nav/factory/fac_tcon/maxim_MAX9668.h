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
 * $RCSfile: nav_fac_tcon_pat.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_FAC_MAX9668_H_
#define _NAV_FAC_MAX9668_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "nav/nav_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#if 0
typedef struct _NAV_FAC_TCON_DEFAULT_T
{
    UINT32      u4PanelIndex;                         /* Panel Index */
    UINT16      u2GammaDef[8];                        /* Gamma Default Value */
    UINT16      u2VComDef;                            /* VCom Default Value */
} NAV_FAC_TCON_DEFAULT_T;
#endif
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

//extern VOID  a_cfg_custom_factory_disable_all_iic_to_max9668( void );
//extern VOID  a_cfg_custom_factory_set_arm_iic_to_max9668( void );

extern INT32 nav_fac_MAX9668_get_tcon_gamma_reg_val(UINT8 ui1_gamma, UINT16 *pui2_vcom_val );
extern INT32 nav_fac_MAX9668_set_tcon_gamma_reg_val(UINT8 ui1_gamma, UINT16 ui2_vcom_val );
extern INT32 nav_fac_MAX9668_get_vcom_reg_val( UINT16 *pui2_vcom_val );
extern INT32 nav_fac_MAX9668_set_vcom_reg_val(UINT16 ui2_vcom_val);
extern INT32 nav_fac_MAX9668_store_vcom_val ( void );
extern INT32 nav_fac_MAX9668_load_def_gamma_by_panel_id(UINT8 ui1_gamma);
extern INT32 nav_fac_MAX9668_load_def_vcom_by_panel_id(VOID);
extern INT32 nav_fac_MAX9668_write_def_gamma_by_panel_id(UINT8 ui1_gamma);
extern INT32 nav_fac_MAX9668_tcon_write_gamma(UINT8 ui1_gamma);
extern INT32 nav_fac_MAX9668_add_vcom_reg_offset(INT16 i2_offset_vals);
extern INT32 nav_fac_MAX9668_end_vcom_alignment(void);
extern INT32 nav_fac_MAX9668_tcon_check_and_set_def_val(VOID);
extern INT32 nav_fac_MAX9668_get_vcom_max_min_val(UINT16* i2_max, UINT16* i2_min);
extern BOOL nav_fac_MAX9668_tcon_check_panel(VOID);

extern BOOL nav_fac_MAX9668_tcon_is_existed(VOID);

#endif /* _NAV_FAC_MAX9668_H_ */

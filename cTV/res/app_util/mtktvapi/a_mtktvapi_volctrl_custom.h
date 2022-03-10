/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: npg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: xutong.hu $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_MTKTVAPI_VOLCTRL_CUSTOM_H_
#define _A_MTKTVAPI_VOLCTRL_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/



#include "u_cli.h"

#include "app_util/mtktvapi/a_mtktvapi.h"

#include "app_util/mtktvapi/a_mtktvapi_volctrl.h"


#define MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_APP         ((UINT8)0)
#define MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY     ((UINT8)1)

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_mtktvapi_volctrl_custom_reg_callback(mtktvapi_volctrl_callback_fct pf_nfy, VOID * pv_tag);

extern INT32 a_mtktvapi_volctrl_custom_audio_event_register_callback(mtktvapi_volctrl_audio_event_callback_fct pv_fct,
                                            VOID* pv_tag);
extern INT32 a_mtktvapi_volctrl_custom_audio_event_callback_unregister(VOID);

extern INT32 a_mtktvapi_volctrl_custom_incrVolume(INT16 *pi4_return_current_value);

extern INT32 a_mtktvapi_volctrl_custom_incrVolume_by_type(INT16 *pi4_return_current_value,INT32 type);
extern INT32 a_mtktvapi_volctrl_custom_decrVolume(INT16 *pi4_return_current_value);

extern INT32 a_mtktvapi_volctrl_custom_decrVolume_by_type(INT16 *pi4_return_current_value,INT32 type);
extern INT32 a_mtktvapi_volctrl_custom_setVolume(INT16 value);
extern INT32 a_mtktvapi_volctrl_custom_setVolume_by_type(INT32 type,INT16 value);
extern INT32 a_mtktvapi_volctrl_custom_getVolume(INT16 *pi4_return_current_value);
extern INT32 a_mtktvapi_volctrl_custom_getVolume_by_type(INT16 *pi4_return_current_value,INT32 type);
extern INT32 a_mtktvapi_volctrl_custom_setMute(BOOL isMute);
extern INT32 a_mtktvapi_volctrl_custom_setMute_by_type(INT32 type,BOOL isMute);
extern INT32 a_mtktvapi_volctrl_custom_getMute(BOOL *pb_mute_status);
extern INT32 a_mtktvapi_volctrl_custom_getMute_by_type(BOOL *pb_mute_status,INT32 type);
extern INT32 a_mtktvapi_volctrl_custom_init(VOID);

extern INT32 a_mtktvapi_volctrl_set_vol_adjust_reason(UINT8 ui1_reason);
extern INT32 a_mtktvapi_volctrl_get_vol_adjust_reason(UINT8 *pui1_reason);

/*-----------------------------------------------------------------------------
                    functions declarations (called by dtv_svc internally.)
-----------------------------------------------------------------------------*/
#endif /*  */

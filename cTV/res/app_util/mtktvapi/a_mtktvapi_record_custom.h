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
 * $Date: 2015/08/25 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: xutong.hu $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_MTKTVAPI_RECORD_CUSTOM_H_
#define _A_MTKTVAPI_RECORD_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_pal_secam_eng.h"
#include "u_cli.h"
 
#include "u_cli.h"

#include "app_util/mtktvapi/a_mtktvapi.h"
#include "app_util/mtktvapi/a_mtktvapi_record.h"

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
 
#ifdef APP_NAV_REC_PVR_SUPPORT
extern INT32 a_mtktvapi_record_custom_get_error_slot_num(INT32 * pi4_num);
extern INT32 a_mtktvapi_record_custom_get_error_slot_by_index(INT32 index, UINT32 * pui4_slot);
extern INT32 a_mtktvapi_record_custom_update_started_otr_duration(UINT32  ui4_duration);

extern INT32 a_mtktvapi_record_custom_register_hdd(CHAR * pac_mounted_hdd_path);
extern INT32 a_mtktvapi_record_custom_check_hdd_registered(CHAR * pac_mounted_hdd_path, BOOL * pb_registered);
extern INT32 a_mtktvapi_record_custom_get_registered_hdd_num(UINT32* pui4_registered_hdd_num);
extern INT32 a_mtktvapi_record_custom_unreg_hdd_by_index(UINT32  ui4_hdd_index);
extern INT32 a_mtktvapi_record_custom_check_hdd_registered_by_index(UINT32  ui4_hdd_index, BOOL *  pb_registered);
extern INT32 a_mtktvapi_record_custom_get_crnt_pulgged_hdd_index(UINT32* pui4_hdd_index);
extern INT32 a_mtktvapi_record_custom_get_recording_status(UINT32* pui4_recording_status);
extern INT32 a_mtktvapi_record_custom_get_registered_hdd_indexes(UINT16* pui2_idx);
#endif
/*-----------------------------------------------------------------------------
                    functions declarations (called by dtv_svc internally.)
-----------------------------------------------------------------------------*/

#endif /*  */

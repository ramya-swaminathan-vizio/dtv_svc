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
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _MTKTVAPI_BROADCAST_CUSTOM_H_
#define _MTKTVAPI_BROADCAST_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_sb_dvb_eng.h"
#include "app_util/mtktvapi/a_mtktvapi.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 mtktvapi_broadcast_custom_select_channel(
                                    UINT16          ui2_svl_id, 
                                    UINT32          ui4_channel_id,
                                    BOOL            b_check_barker_channel);
extern INT32 mtktvapi_broadcast_custom_select_chan_by_chan_num(
                                    UINT32          ui4_major_number,
                                    UINT32          ui4_minor_number,
                                    BOOL            b_minor_number_valid);
extern INT32 mtktvapi_broadcast_custom_select_channel_by_prog_no(
                                    UINT8           ui1_list_no,
                                    UINT16          ui2_prog_no);
extern INT32 mtktvapi_broadcast_custom_select_channel_silently(
                                    TV_WIN_ID_T     e_focus_win_id,
                                    UINT16          ui2_svl_id, 
                                    UINT32          ui4_channel_id);
extern INT32 mtktvapi_broadcast_custom_set_banner_visibility(
                                    BOOL            b_visible);
extern INT32 mtktvapi_broadcast_custom_get_tuning_status(
                                    UINT32*         pui4_tuning_status);
extern INT32 mtktvapi_broadcast_custom_get_tuning_error(
                                    UINT32*         pui4_tuning_error);
extern INT32 mtktvapi_broadcast_custom_switch_input_to_tv(
                                    VOID);
extern INT32 mtktvapi_broadcast_custom_is_cam_installed(
                                    BOOL*   pb_cam_installed);
extern INT32 mtktvapi_broadcast_custom_is_support_4_digits_input(
                                    BOOL*   pb_support_4_digits);
extern INT32 mtktvapi_broadcast_custom_is_additional_service_available(
                                    BOOL*   pb_available);
extern INT32 mtktvapi_broadcast_custom_is_digits_key_handled(
                                    BOOL*   pb_key_handled);
extern INT32 mtktvapi_broadcast_custom_is_channel_number_valid(
                                    UINT32          ui4_major_number,
                                    UINT32          ui4_minor_number,
                                    BOOL            b_minor_no_valid,
                                    BOOL*           pb_channel_no_valid);
extern INT32 mtktvapi_broadcast_custom_reset_digits_key_handled(
                                    VOID);
extern INT32 mtktvapi_broadcast_custom_select_channel_by_chan_id(
                                    UINT32          ui4_channel_id,
                                    BOOL            b_check_barker_channel);
extern INT32 mtktvapi_broadcast_custom_get_target_region_num(
                                    UINT16          ui2_svl_id,
                                    UINT16*         pui2_region_num);
extern INT32 mtktvapi_broadcast_custom_get_target_regions(
                                    UINT16          ui2_svl_id,
                                    UINT16          ui2_region_num,
                                    UINT16          ui2_index,
                                    SB_DVB_REGION_T* pt_region);
extern UINT32 mtktvapi_broadcast_custom_get_max_possible_major_chan_no(
                                        UINT16          ui2_svl_id);
extern UINT32 mtktvapi_broadcast_custom_get_max_possible_minor_chan_no(
                                        UINT16          ui2_svl_id);
extern UINT32 mtktvapi_broadcast_custom_get_max_possible_major_digits(
                                        UINT16          ui2_svl_id);
extern UINT32 mtktvapi_broadcast_custom_get_max_possible_minor_digits(
                                        UINT16          ui2_svl_id);
extern CHAR* mtktvapi_broadcast_custom_get_cam_operator_name(
                                        VOID);
extern INT32 mtktvapi_broadcast_custom_set_favorite_icon_on_banner(
                                    BOOL            isShown);
extern INT32 mtktvapi_broadcast_custom_get_mheg_input_event_mask(
                                    UINT8           ui1_mask_type,
                                    BOOL*           pb_mask_set);
#endif /* _MTKTVAPI_BROADCAST_CUSTOM_H_ */

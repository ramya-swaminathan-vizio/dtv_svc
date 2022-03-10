#ifndef _A_MTKTVAPI_RECORD_PLAYBACK_CUSTOM_H_
#define _A_MTKTVAPI_RECORD_PLAYBACK_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "svctx/rec_hdlr/u_rec_hdlr.h"

#include "app_util/mtktvapi/a_mtktvapi.h"
#include "app_util/mtktvapi/a_mtktvapi_record_playback.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

#ifdef APP_NAV_REC_PVR_SUPPORT
extern INT32 a_mtktvapi_record_playback_custom_get_record_title_info(
                                                        CHAR*           s_path, 
                                                        MTKTVAPI_PVR_RECORDED_TITLE_T* pt_title);
extern INT32 a_mtktvapi_record_playback_custom_get_pvr_cp_info(
                                                        CHAR*           ps_pvr_file,
                                                        UINT32          ui4_cp_index,
                                                        REC_UTIL_CIPLUS_INFO_T* pt_cp_info);
extern INT32 a_mtktvapi_record_playback_custom_set_protected(
                                                        MTKTVAPI_PVR_RECORDED_TITLE_T* pt_title_info,
                                                        BOOL            b_protect);
extern INT32 a_mtktvapi_record_playback_custom_set_new_mark(
                                                        const CHAR*     ps_path, 
                                                        BOOL            b_newMark);
extern INT32 a_mtktvapi_record_playback_custom_get_current_file(
                                                        CHAR*           ps_file, 
                                                        UINT32          ui4_len);
extern INT32 a_mtktvapi_record_playback_custom_get_description_by_index(
                                                        const CHAR*     ps_file_name, 
                                                        VOID*           pv_out, 
                                                        UINT32*         pui4_out_len, 
                                                        UINT32          ui4_index, 
                                                        INFO_TYPE_T     e_type);
extern INT32 a_mtktvapi_record_playback_custom_get_event_num_in_file(
                                                        const CHAR*     ps_file_name, 
                                                        UINT32*         pui4_num);
#endif 

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
extern INT32 a_mtktvapi_timeshift_custom_get_current_tv_mode(
                                                        UINT32*         pui4_mode);
#endif

#endif /* A_MTKTVAPI_HIGHLEVEL_CUSTOM_H_ */


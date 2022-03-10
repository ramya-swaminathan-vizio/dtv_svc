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
 * $RCSfile: a_input_src.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_INPUT_SRC_H_
#define _A_INPUT_SRC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "app_util/a_common.h"
#include "nav/nav_common.h"
#include "rest/a_rest.h"
#include "rest/a_rest_api.h"
#include "res/app_util/config/a_cfg_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NAV_IPTS_UI_RATING_DESC_LEN         ((UINT32)32)

extern BOOL b_key_front_pannel;

typedef enum _NAV_IPTS_UI_INFO_STATUS_T
{
    NAV_IPTS_UI_IS_NOT_READY = 0,
    NAV_IPTS_UI_IS_WITH,
    NAV_IPTS_UI_IS_WITHOUT
} NAV_IPTS_UI_INFO_STATUS_T;

typedef struct _NAV_IPTS_UI_INPUT_SRC_T
{
    INP_SRC_TYPE_T              e_src_group;                         /*INP_SRC_TYPE_UNKNOWN, INP_SRC_TYPE_TV, INP_SRC_TYPE_AV, INP_SRC_TYPE_1394*/
    DEVICE_TYPE_T               e_video_type;                        /*please refer to u_device_type.h*/
    UTF16_T*                    w2s_name;                            /*display name of a content source*/
    UINT8                       ui1_id;                              /*identification of a content source*/
} NAV_IPTS_UI_INPUT_SRC_T;

typedef struct _NAV_IPTS_UI_INPUT_SRC_INFO_T
{
    NAV_IPTS_UI_INFO_STATUS_T   e_status;                            /*status for t_input_src*/
    NAV_IPTS_UI_INPUT_SRC_T     t_input_src;
} NAV_IPTS_UI_INPUT_SRC_INFO_T;

typedef struct _NAV_IPTS_UI_VIDEO_INFO_T
{
    NAV_IPTS_UI_INFO_STATUS_T           e_status;
    VSH_SRC_RESOLUTION_INFO_T           t_res;
} NAV_IPTS_UI_VIDEO_INFO_T;

typedef struct _NAV_IPTS_UI_RATING_INFO_T
{
    NAV_IPTS_UI_INFO_STATUS_T           e_status;
    UTF16_T                             ws2_rating[NAV_IPTS_UI_RATING_DESC_LEN + 1];
} NAV_IPTS_UI_RATING_INFO_T;

#define NAV_IPTS_UI_RATING_INFO_ZERO(_rating_info)      \
{                                                       \
    (_rating_info).e_status = NAV_IPTS_UI_IS_NOT_READY; \
    (_rating_info).ws2_rating[0] = 0;                   \
}

typedef enum _NAV_IPTS_UI_APP_STATUS_T
{
    NAV_IPTS_UI_AS_OFF = 0,
    NAV_IPTS_UI_AS_ON_PAUSED,
    NAV_IPTS_UI_AS_ON_RESUMED
} NAV_IPTS_UI_APP_STATUS_T;

typedef UINT32                                  NAV_IPTS_CMD_T;
#define NAV_IPTS_CMD_MDL_RELOAD_CRNT_SRC        ((NAV_IPTS_CMD_T) 1)                    /*pv_arg1: not used*/
#define NAV_IPTS_CMD_MDL_INACT_COMP             ((NAV_IPTS_CMD_T) 2)                    /*use under tv svc is disabled condition*/
#define NAV_IPTS_CMD_CHG_SRC_EXTERNAL           ((NAV_IPTS_CMD_T) 3)                    /*change input source by external,not in navigator*/

#define NAV_IPTS_CMD_VIEW_START                 ((NAV_IPTS_CMD_T) 1000)
#define NAV_IPTS_CMD_VIEW_VISIBILITY            (NAV_IPTS_CMD_VIEW_START + 1)           /*pv_arg1: BOOL. TRUE: show, FALSE: hide*/
#define NAV_IPTS_CMD_VIEW_CHG_ACTIVE            (NAV_IPTS_CMD_VIEW_START + 2)

typedef enum _NAV_IPTS_UI_INFO_FIELD_T
{
    NAV_IPTS_UI_IF_EMPTY                = 0,
    NAV_IPTS_UI_IF_CRNT_INPUT           = 0x00000001,
    NAV_IPTS_UI_IF_CRNT_VIDEO           = 0x00000002,
    NAV_IPTS_UI_IF_CRNT_RATING          = 0x00000004,
    NAV_IPTS_UI_IF_PLAY_MODE            = 0x00000008,
    NAV_IPTS_UI_IF_GUI_LANG             = 0x00000010,
    NAV_IPTS_UI_IF_SRC_COUNT            = 0x00000020,
    NAV_IPTS_UI_IF_ACT_COMP             = 0x00000040,
    NAV_IPTS_UI_IF_FOCUS                = 0x00000080,
    NAV_IPTS_UI_IF_APP_STATUS           = 0x00000100,
    NAV_IPTS_UI_IF_LOCK_STATUS          = 0x00000200,
    NAV_IPTS_UI_IF_SWAP_STATUS          = 0x00000400,
    NAV_IPTS_UI_IF_INPUT_CH_NUM_STATUS  = 0x00000800,
    NAV_ITPS_UI_IF_DO_CMD               = 0x00001000,
    NAV_ITPS_UI_IF_RET_RMK_FOCUS        = 0x00002000
} NAV_IPTS_UI_INFO_FIELD_T;


typedef struct _NAV_IPTS_UI_INFO_T
{
    NAV_IPTS_UI_INPUT_SRC_INFO_T    t_crnt_input;
    NAV_IPTS_UI_VIDEO_INFO_T        t_crnt_video;           /*should be removed in the future*/
    NAV_IPTS_UI_RATING_INFO_T       t_crnt_rating;          /*should be removed in the future*/
    TV_MODE_T                       e_play_mode;
    TV_WIN_ID_T                     e_focus;
    NAV_IPTS_UI_APP_STATUS_T        e_app_status;
    LOCKED_STATUS_T                 e_lock_status;
    NAV_IPTS_CMD_T                  e_cmd;
    VOID*                           pv_cmd_arg1;
    VOID*                           pv_cmd_arg2;
    UINT8                           ui1_gui_lang_id;
    UINT8                           ui1_src_count;
    BOOL                            b_is_active_comp;
    BOOL                            b_is_swapping;
    BOOL                            b_is_ch_num_inputting;

} NAV_IPTS_UI_INFO_T;

typedef INT32 (*nav_ipts_view_init_fct)(HANDLE_T            h_canvas,
                                        INT32               i4_frame_x_offset,
                                        INT32               i4_frame_y_offset,
                                        APP_COLOR_TYPE_T    e_color_type,
                                        VOID**              ppv_view);

typedef INT32 (*nav_ipts_view_deinit_fct)(VOID*             pv_view);

typedef INT32 (*nav_ipts_view_data_change_fct)(VOID*                        pv_view,
                                               TV_WIN_ID_T                  e_update_grp,
                                               NAV_IPTS_UI_INFO_FIELD_T     e_update_field,
                                               const NAV_IPTS_UI_INFO_T*    pt_update_data);

typedef BOOL (*nav_ipts_view_is_key_handler_fct)(VOID*                      pv_view,
                                                 TV_WIN_ID_T                e_grp,
                                                 UINT32                     ui4_key_code);

typedef INT32 (*nav_ipts_view_key_handler_fct)(VOID*                        pv_view,
                                               TV_WIN_ID_T                  e_grp,
                                               UINT32                       ui4_key_code);

typedef INT32 (*nav_ipts_view_hide_fct)(VOID*               pv_view);

typedef struct _NAV_IPTS_VIEW_HANDLER_T
{
    nav_ipts_view_init_fct              pf_init;
    nav_ipts_view_deinit_fct            pf_deinit;
    nav_ipts_view_data_change_fct       pf_data_change;
    nav_ipts_view_is_key_handler_fct    pf_is_key_handler;
    nav_ipts_view_key_handler_fct       pf_key_handler;
    nav_ipts_view_hide_fct              pf_hide;
} NAV_IPTS_VIEW_HANDLER_T;

typedef struct _S_HDMI_NAME_T
{
    UINT8 show_cec_name;
    CHAR cec_name[APP_CFG_CUSTOM_INP_NAME_LEN+1];
}S_HDMI_NAME_T;

#define NAV_IPTS_IS_LEGAL_VIEW_HANDLER(_pt_intf)            \
(                                                           \
    (NULL != (_pt_intf)->pf_init) &&                        \
    (NULL != (_pt_intf)->pf_deinit) &&                      \
    (NULL != (_pt_intf)->pf_data_change) &&                 \
    (NULL != (_pt_intf)->pf_is_key_handler) &&              \
    (NULL != (_pt_intf)->pf_key_handler) &&                 \
    (NULL != (_pt_intf)->pf_hide)                           \
)

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_input_src_register(const NAV_IPTS_VIEW_HANDLER_T*    pt_view_handler);

extern INT32 a_input_src_do_cmd(NAV_IPTS_CMD_T                      e_cmd,
                                VOID*                               pv_arg1,
                                VOID*                               pv_arg2);

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
extern VOID nav_ipts_update_current_src(VOID);
extern VOID a_nav_ipts_src_c4tv_apron_custom_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3);
extern VOID a_nav_ipts_src_set_c4tv_apron_exit_status(BOOL b_exit);
extern VOID a_nav_stop_ipts_src_c4tv_apron_custom_nfy_from_link(BOOL b_from_link);
#endif

extern BOOL  a_nav_ipts_crnt_input_is_cast_source(VOID);
extern BOOL  a_nav_ipts_is_cast_source(ISL_REC_T* pt_isl_rec);
extern BOOL  a_nav_ipts_is_usb_source(ISL_REC_T* pt_isl_rec);
extern BOOL  a_nav_ipts_is_tv_source(ISL_REC_T* pt_isl_rec);
extern BOOL  a_nav_ipts_is_comp_source(ISL_REC_T* pt_isl_rec);
extern BOOL  a_nav_ipts_is_hdmi_source(ISL_REC_T* pt_isl_rec);
extern BOOL  a_nav_ipts_is_div_source(ISL_REC_T* pt_isl_rec);
extern BOOL  a_nav_ipts_is_vga_source(ISL_REC_T* pt_isl_rec);

extern INT32 a_nav_ipts_get_crnt_isl_rec(ISL_REC_T* pt_isl_rec);
extern INT32 a_nav_ipts_get_crnt_isl_id(UINT8*  pui1_input_src);

extern INT32 a_nav_ipts_create_virtual_input(TYPE_APP_VTRL_INPUT* pt_vtrl_input);
extern INT32 a_nav_ipts_delete_virtual_input(CHAR* s_cname);
extern INT32 a_nav_ipts_select_virtual_input(const CHAR* s_cname);
extern INT32 a_nav_ipts_clean_virtual_input(VOID);
extern BOOL  a_nav_ipts_vtrl_input_hideable(CHAR* s_cname);
extern INT32 a_nav_ipts_get_hdmi_comp_idx(VOID);
extern INT32 a_nav_ipts_set_cec_name (UINT8 ui1_cec_idx, S_HDMI_NAME_T* s_cec_name);
extern INT32 a_nav_ipts_get_cec_name (UINT8 ui1_cec_idx, S_HDMI_NAME_T* s_cec_name);
extern BOOL a_nav_ipts_not_support_comp_source(VOID);
extern UINT16 nav_get_input_src_dbg_level(
                    VOID
                    );
extern  VOID nav_set_input_src_dbg_level(
                    UINT16                      ui2_db_level
                    );

#define IPTS_SELECT_NULL   ((UINT8)0x0)
#define IPTS_SELECT_HDMI1  ((UINT8)0x1)
#define IPTS_SELECT_HDMI2  ((UINT8)0x2)
#define IPTS_SELECT_HDMI3  ((UINT8)0x4)
#define IPTS_SELECT_COMP   ((UINT8)0x8)

extern BOOL   change_source_way;

#endif /* _A_INPUT_SRC_H_ */

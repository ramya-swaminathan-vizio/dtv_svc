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
 * $RCSfile: stvapi.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    include files
-----------------------------------------------------------------------------*/
#include "a_registry.h"
#include "systemui_visibility.h"
#include "store_demo_status.h"
#include "sidebarmenu_visibility.h"
#include "tts_status.h"
#include "menu2/a_menu.h"
//#include "registry_cli.h"

/*-----------------------------------------------------------------------------
    customizable macros
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    macros, defines
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    typedefs, enums, structures
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    function declarations
-----------------------------------------------------------------------------*/

/*
   AEE lifecycle callback functions.
*/
static INT32 _registry_app_init_fct (const CHAR* ps_name, HANDLE_T h_app);
static INT32 _registry_app_exit_fct (HANDLE_T h_app, APP_EXIT_MODE_T e_exit_mode);
static INT32 _registry_app_pause_fct (HANDLE_T h_app);
static INT32 _registry_app_resume_fct (HANDLE_T h_app);
static INT32 _registry_app_process_msg_fct (HANDLE_T h_app, UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len, BOOL b_paused);

/*-----------------------------------------------------------------------------
 * Name: _registry_app_init_fct
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
//extern INT32 c_dbg_stmt (const CHAR*  ps_format, ...); //registry
extern VOID msg_convert_custom_sytem_ui_state_cb_fct(SystemUIState e_state);
static INT32 _registry_app_init_fct (const CHAR* ps_name, HANDLE_T h_app)
{

    c_dbg_stmt("%s\n", __func__);

    if(!initializeMenuUIState())
    {
        c_dbg_stmt("init MenuUIState failed \n");
        return AEER_FAIL;
    }

    if(!initializeSystemUIState())
    {
        c_dbg_stmt("init SystemUIState failed \n");
        return AEER_FAIL;
    }

    if(!initializeTtsStatus())
    {
        c_dbg_stmt("init TtsStatus failed \n");
        return AEER_FAIL;
    }

    onSystemUIStateChange(msg_convert_custom_sytem_ui_state_cb_fct);
    /* init cli interface, must be the last of all registry modules */
    //registry_cli_init();

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _registry_app_exit_fct
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _registry_app_exit_fct (HANDLE_T h_app, APP_EXIT_MODE_T e_exit_mode)
{
    deinitializeMenuUIState();

    deinitializeSystemUIState();

    deinitializeTtsStatus();

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _registry_app_pause_fct
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _registry_app_pause_fct (HANDLE_T h_app)
{
    /* do nothing */
    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _registry_app_resume_fct
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _registry_app_resume_fct (HANDLE_T h_app)
{
    /* do nothing */
    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _registry_app_process_msg_fct
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _registry_app_process_msg_fct (HANDLE_T h_app, UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len, BOOL b_paused)
{
    return AEER_OK;
}

VOID a_registry_set_menu_ui_state(REG_UI_STATE e_state)
{
    NAV_COMP_ID_T e_active_comp = NAV_COMP_ID_LAST_VALID_ENTRY;
    BOOL b_menu_resume = FALSE;

    if(e_state == REG_UI_STATE_INVISIBLE)
    {
        e_active_comp = nav_get_active_component();
        b_menu_resume = a_menu_is_resume();

        DBG_LOG_PRINT(("[Registry] %s %d, b_menu_resume = %d, e_active_comp = %d !!! \n",__FUNCTION__,__LINE__, b_menu_resume, e_active_comp));

        if( TRUE == b_menu_resume
         || NAV_COMP_ID_PICTURE_EFFECT == e_active_comp
         || NAV_COMP_ID_INPUT_SRC == e_active_comp )
        {
            e_state = REG_UI_STATE_VISIBLE;
        }
    }

    DBG_LOG_PRINT(("[Registry] %s %d, set sidebar menu state = %d !!! \n",__FUNCTION__,__LINE__, e_state));
    setMenuUIState((MenuUIState)e_state);
}

REG_UI_STATE a_registry_get_system_ui_state(VOID)
{
    return (SystemUIState)getCurrentSystemUIState();
}

VOID a_registry_set_store_demo_status(NAV_RETAIL_MODE_STATUS_T status)
{
    setStoreDemoStatus(status);
}

VOID a_registry_set_tts_state(REG_TTS_STATE e_state)
{
    TtsStatus status;
    switch (e_state) {
        case REG_TTS_STATE_OFF: status = TtsStatusOff;     break;
        case REG_TTS_STATE_ON:  status = TtsStatusOn;      break;
        default:                status = TtsStatusUnknown; break;
    };
    setTtsStatus(status);
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID a_registry_init(AMB_REGISTER_INFO_T*  pt_reg)
{

    /* Application can only use middleware's c_ API */
    c_memset(pt_reg->s_name, 0, sizeof(CHAR)*(APP_NAME_MAX_LEN + 1));
    c_strncpy(pt_reg->s_name, REGISTRY_NAME, APP_NAME_MAX_LEN);

    pt_reg->t_fct_tbl.pf_init                   = _registry_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit                   = _registry_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause                  = _registry_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume                 = _registry_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg            = _registry_app_process_msg_fct;
    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 1024 * 4;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 32;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 0;
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 32;
    pt_reg->t_desc.t_max_res.ui8_max_files_size = 1024 * 2;
    pt_reg->t_desc.t_max_res.ui2_max_files      = 2;
    pt_reg->t_desc.t_max_res.ui2_max_handles    = 64;
    pt_reg->t_desc.t_max_res.ui2_max_threads    = 2;
    pt_reg->t_desc.t_max_res.ui2_max_semaphores = 2;
    pt_reg->t_desc.t_max_res.ui2_max_msg_queues = 1;
    pt_reg->t_desc.t_max_res.ui2_max_nb_msgs    = 32*2;
    pt_reg->t_desc.t_max_res.ui2_max_msg_size   = 48;
    pt_reg->t_desc.ui2_msg_count                = 32*2;
    pt_reg->t_desc.ui2_max_msg_size             = 48;
    pt_reg->ui2_key_num                         = 0;

}


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
 * $RCSfile: menu_page_nw_pwd.c,v  $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: jg_lizhuwang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "app_util/a_cfg.h"
#include "app_util/a_drv_interface.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/menu2/menu_custom.h"
#include "res/msgconvert/msgconvert_custom.h"

#include "res/app_util/config/acfg_custom.h"


#ifdef LINUX_AUTO_TEST
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#define save_del_pic_mode_file  "test_save_delete_pic_mode_ok"
#define reset_pic_mode_file  "test_reset_pic_mode_ok"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "res/app_util/icl/a_icl_custom.h"

extern int a_get_is_pin_confirmed(BOOL* b_confirm);

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/

#define PIC_MODE_EDIT_NAME_MAX_LEN            MENU_CUST_PIC_MODE_NAME_MAX_LEN

#define PIC_MODE_EDIT_SAVE_BTN_X                (MENU_ITEM_V_LEFT)
#define PIC_MODE_EDIT_SAVE_BTN_Y                (400)
#define PIC_MODE_EDIT_SAVE_BTN_W                (MENU_ITEM_V_WIDE)
#define PIC_MODE_EDIT_SAVE_BTN_H                (MENU_ITEM_V_HEIGHT)

#define PIC_MODE_EDIT_BTN_INSET_LEFT            (FRAME_LEFT_RIGHT_INTV - 8)

#define PIC_MODE_EDIT_BTN_INSET_RIGHT       10

#define PIC_MODE_EDIT_GUIDE_TEXT_X          (5)
#define PIC_MODE_EDIT_GUIDE_TEXT_Y          (5)
#define PIC_MODE_EDIT_GUIDE_TEXT_W          (CONTENT_W -60)
#define PIC_MODE_EDIT_GUIDE_TEXT_H          (60)

#define PIC_MODE_EDIT_LST_VISIBLE_ELEM             (12)
#define PIC_MODE_EDIT_LST_X                        (0 * GRID_W)
#define PIC_MODE_EDIT_LST_Y                        (0 * GRID_H)
#define PIC_MODE_EDIT_LST_W                        (CONTENT_W)
#define PIC_MODE_EDIT_LST_H                        (PIC_MODE_EDIT_LST_VISIBLE_ELEM * GRID_H)

#define MENU_PAGE_CAP_STL_MAX_ITEM_NUM      (11)
#define LOCK_PIC_MODE_LB_OFFSET             (2)
#define LOCK_PIC_MODE_LB                    (1)

#define COPY_PIC_MODE_LB_OFFSET             (1)
#define COPY_PIC_MODE_LB                    (1)

#define PIC_MODE_EDIT_ITEM_NUM              (4)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct PIC_MODE_EDIT
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_menu_current_focus;
    BOOL         b_finish;
    BOOL         b_this_page_show;
    HANDLE_T     h_dlg;
    BOOL         b_is_dlg_show;
    UINT32       ui4_cur_page_id;
    HANDLE_T     h_pic_mode_list;
    UINT16       ui2_sel_list_idx;
    UINT16       ui2_save_pic_mode_idx;
    CHAR         s_input_buf[MENU_CUST_PIC_MODE_NAME_MAX_LEN+2];
    UTF16_T      w2s_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1];
    HANDLE_T         h_save_pic_mode;
    HANDLE_T         h_copy_pic_mode;
    HANDLE_T         h_lock_pic_mode;//lock pic mode and unlock pic mode share the item
    HANDLE_T         h_lock_pic_mode_lb;
    HANDLE_T         h_unlock_pic_mode;
    HANDLE_T         h_reset_pic_mode;//reset pic mode and delete pic mode share the item
#ifdef NEVER
    HANDLE_T         h_delete_pic_mode;
#endif /* NEVER */
    BOOL             b_is_lock_mode;//lock status
#ifdef NEVER
    BOOL             b_is_lock_enable;
#endif /* NEVER */
    BOOL             b_is_reset_mode;//preset pic mode vs customer pic mode
#ifdef NEVER
    BOOL             b_is_reset_enable;
    BOOL             b_is_save_item_enable;
#endif /* NEVER */
    BOOL             b_item_enable[PIC_MODE_EDIT_ITEM_NUM];
    UINT16           ui2_icl_nfy_id_pic_mode;  /* The icl picture mode notify id */

}PIC_MODE_EDIT;

typedef enum _PIC_MODE_EDIT_BTN_TYPE_T
{
    PIC_MODE_EDIT_BTN_SAVE = 0,
    PIC_MODE_EDIT_BTN_COPY,
    PIC_MODE_EDIT_BTN_LOCK_UNLOCK,
    PIC_MODE_EDIT_BTN_RESET_DELETE,
    PIC_MODE_EDIT_BTN_LAST_ENTRY
}PIC_MODE_EDIT_BTN_TYPE_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_pic_mode_edit;
static  PIC_MODE_EDIT    t_g_pic_mode_edit_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_dlg_create(VOID);
static VOID _pic_mode_edit_dlg_reset_yes_btn(VOID);
static VOID _pic_mode_edit_dlg_reset_no_btn(VOID);
static VOID _pic_mode_edit_dlg_delete_yes_btn(VOID);
static VOID _pic_mode_edit_dlg_delete_no_btn(VOID);
static INT32 _pic_mode_edit_update_ui(VOID);
static INT32 _pic_mode_edit_set_title(VOID);
static INT32 _pic_mode_edit_set_lock_unlock_item(VOID);
static INT32 _pic_mode_edit_set_reset_delete_item(VOID);
static INT32 _pic_mode_edit_set_save_item(VOID);
static INT32 _pic_mode_edit_set_copy_item(VOID);
static BOOL _pic_mode_edit_dlg_reset_back_btn(UINT32 ui4_keycode);
static BOOL _pic_mode_edit_dlg_delete_back_btn(UINT32 ui4_keycode);
static BOOL _lock_pic_mode_check_is_set_sys_pin(VOID);

#ifdef APP_TTS_SUPPORT
static INT32 _pic_mode_edit_save_item_tts_play(VOID);
static INT32 _pic_mode_edit_copy_item_tts_play(VOID);
static INT32 _pic_mode_edit_lock_unlock_item_tts_play(VOID);
static INT32 _pic_mode_edit_reset_delete_item_tts_play(VOID);
#endif
static INT32 _pic_mode_edit_set_lock_unlock_lb_item();
static INT32 _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_TYPE_T e_type,BOOL b_up,BOOL b_backbar);

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
#ifdef NEVER
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    INT32               i4_ret = MENUR_OK;
#endif /* NEVER */

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
        {
            MENU_LOG_ON_FAIL (menu_nav_back ()) ;

            menu_pm_repaint();
            return MENUR_OK;
        }

        case BTN_CURSOR_DOWN:
            _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_LAST_ENTRY,FALSE,TRUE);
#ifdef NEVER
        {
            if(pt_page_data->b_is_save_item_enable)
            {
                c_wgl_set_focus(pt_page_data->h_save_pic_mode, WGL_SYNC_AUTO_REPAINT);
            #ifdef APP_TTS_SUPPORT
                _pic_mode_edit_save_item_tts_play();
            #endif
            }
            else if(pt_page_data->b_is_lock_enable)
            {
                #ifdef LOCK_PIC_MODE_LB
                i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode_lb,WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
                #else
                i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode,WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
                #endif
            #ifdef APP_TTS_SUPPORT
                _pic_mode_edit_lock_unlock_item_tts_play();
            #endif
            }
            else if(pt_page_data->b_is_reset_enable)
            {
                i4_ret = c_wgl_set_focus(pt_page_data->h_reset_pic_mode,WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            #ifdef APP_TTS_SUPPORT
                _pic_mode_edit_reset_delete_item_tts_play();
            #endif
            }
            else
            {
                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                menu_pm_repaint();
            }
        }
#endif /* NEVER */
            break ;
        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;
        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_RETURN:
            menu_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_reset_no_btn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pic_mode_edit_dlg_reset_no_btn(VOID)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    menu_page_pic_mode_edit_dlg_hide();

    i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    _pic_mode_edit_reset_delete_item_tts_play();
#endif

}
/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_reset_back_btn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _pic_mode_edit_dlg_reset_back_btn(UINT32 ui4_keycode)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    if(ui4_keycode == BTN_RETURN)
    {
        menu_page_pic_mode_edit_dlg_hide();

        i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        _pic_mode_edit_reset_delete_item_tts_play();
    #endif

        return TRUE;
    }

    return FALSE;

}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_delete_no_btn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pic_mode_edit_dlg_delete_no_btn(VOID)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    menu_page_pic_mode_edit_dlg_hide();


    i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    _pic_mode_edit_reset_delete_item_tts_play();
#endif

}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_delete_back_btn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _pic_mode_edit_dlg_delete_back_btn(UINT32 ui4_keycode)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    if(ui4_keycode == BTN_RETURN)
    {
        menu_page_pic_mode_edit_dlg_hide();

        i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        _pic_mode_edit_reset_delete_item_tts_play();
    #endif

        return TRUE;
    }

    return FALSE;

}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_reset_yes_btn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pic_mode_edit_dlg_reset_yes_btn(VOID)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = a_cfg_reset_preset_pic_mode();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_pic_mode_edit_dlg_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pic_mode_edit_update_ui();
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pic_energy_change_sepcial_page_set_status(TRUE);

    //i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
    i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    _pic_mode_edit_save_item_tts_play();
#endif

    menu_pm_repaint();

#ifdef LINUX_AUTO_TEST
    DBG_LOG_PRINT(("<MENU>reset pic mode is ok\r\n"));

    DBG_CREATE_TEMP_FILE(reset_pic_mode_file);
#endif
}
/*----------------------------------------------------------------------------
 * Name: _delete_picture_mode
 *
 * Description:_delete_picture_mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/

static VOID _delete_picture_mode(VOID)
{
    INT32   i4_ret = 0;
    INT16   i2_pic_mode = 0;
    INT16   i2_val = 0;
    UINT16  ui2_elem_idx = 0;

    /* get crnt pic mode*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_pic_mode);

    i4_ret = a_cfg_cust_delete_pic_mode();
    if(i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU>Failed to delete pic mode. [i4_ret = %d]\r\n", i4_ret));
    }
    else
    {
        /*After delete is selected, then Bright Room pictrue mode is set for any sources previously assigned to the picture mode*/
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_PIC_MODE_DEF);
        if(i4_ret != MENUR_OK)
        {
            DBG_ERROR(("<MENU>Failed to delete pic mode. [i4_ret = %d]\r\n", i4_ret));
        }
        else
        {
            for(UINT8 ui1_input_src=ACFG_CUST_INPUT_GRP_TV;ui1_input_src<ACFG_CUST_INPUT_GRP_MAX;ui1_input_src++)
            {
                ui2_elem_idx = ui1_input_src;

                i4_ret = acfg_get_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, &i2_val);
                MENU_LOG_ON_FAIL(i4_ret);
                if(i2_val == i2_pic_mode)
                {
                    i4_ret = acfg_set_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, ACFG_PIC_MODE_DEF);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
            /*update rename picture mode / create picture mode /picture mode.*/
            menu_pm_refresh();
            menu_pm_repaint();
        }
    }

}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_delete_yes_btn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pic_mode_edit_dlg_delete_yes_btn(VOID)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    UINT32              ui4_state = 0;

    _delete_picture_mode();

    i4_ret = menu_page_pic_mode_edit_dlg_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pic_energy_change_sepcial_page_set_status(TRUE);

    i4_ret = _pic_mode_edit_update_ui();
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_get_state(pt_page_data->h_menu_current_focus, &ui4_state);

    i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    _pic_mode_edit_save_item_tts_play();
#endif

    menu_pm_repaint();

#ifdef LINUX_AUTO_TEST
    INT16 i2_pic_mode = 0;

    /* get current pic mode*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_pic_mode);
    if(ACFG_PIC_MODE_DEF == i2_pic_mode )
    {
        DBG_LOG_PRINT(("<MENU>save/delete pic mode is ok\r\n"));

        DBG_CREATE_TEMP_FILE(save_del_pic_mode_file);
    }
#endif
}

#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_reset_msg_proc
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_dlg_reset_delete_msg_proc(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2)
{
    UINT32          ui4_keycode = (UINT32)param1;
    UTF16_T         w2s_str[128] = {0};
    PIC_MODE_EDIT*  pt_page_data = &t_g_pic_mode_edit_page_data;

    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        if(pt_page_data->b_is_reset_mode)
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_RESET));
        }
        else
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_DELETE_ITEM_DELETE));
        }
    }
    else if(ui4_keycode == BTN_CURSOR_RIGHT)
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        if(pt_page_data->b_is_reset_mode)
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL));
        }
        else
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_DELETE_ITEM_CANCEL));
        }
    }
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

    return a_ui_simple_dialog_default_msg_proc(h_widget,ui4_msg,param1,param2);

}
#endif

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_dlg_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_dlg_create(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    HANDLE_T        h_parent = NULL_HANDLE;


    i4_ret = menu_pm_get_root_frm(&h_parent);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_parent;
    //t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct    = _pic_mode_edit_dlg_reset_no_btn;
    //t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _pic_mode_edit_dlg_reset_yes_btn;
#ifdef APP_TTS_SUPPORT
    t_simple_dialog_init.pf_wdgt_proc                   = _pic_mode_edit_dlg_reset_delete_msg_proc;
#else
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
#endif
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                                &pt_page_data->h_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show   = FALSE;

    return MENUR_OK;

}
/*----------------------------------------------------------------------------
 * Name: menu_page_pic_mode_edit_dlg_is_show
 *
 * Description: menu_page_pic_mode_edit_dlg_is_show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_pic_mode_edit_dlg_is_show(VOID)
{
    PIC_MODE_EDIT*              pt_page_data = &t_g_pic_mode_edit_page_data;

    return pt_page_data->b_is_dlg_show;
}
/*----------------------------------------------------------------------------
 * Name: menu_page_pic_mode_edit_dlg_show
 *
 * Description: menu_page_pic_mode_edit_dlg_show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_pic_mode_edit_dlg_show(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    PIC_MODE_EDIT*              pt_page_data = &t_g_pic_mode_edit_page_data;
    UTF16_T                     w2s_str[MENU_PIC_MODE_EDIT_DLG_TEXT_LEN+1] = {0};
    CHAR                        s_space[8+1] = {0};
    UTF16_T                     w2s_space[8+1] = {0};

    /*reset pic mode dlg*/
    if(pt_page_data->b_is_reset_mode)
    {
        c_uc_w2s_strncat(w2s_str,MENU_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE1),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE1)));

        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,pt_page_data->w2s_pic_name,c_uc_w2s_strlen(pt_page_data->w2s_pic_name));

        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,MENU_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE2),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE2)));

        i4_ret = a_ui_simple_dialog_set_yes_text(pt_page_data->h_dlg,
                                                      MENU_TEXT(MLM_MENU_KEY_RESET_ITEM_RESET));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_no_text(pt_page_data->h_dlg,
                                                      MENU_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_yes_fct(pt_page_data->h_dlg,_pic_mode_edit_dlg_reset_yes_btn);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_no_fct(pt_page_data->h_dlg,_pic_mode_edit_dlg_reset_no_btn);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_other_key_cb_fct(pt_page_data->h_dlg,_pic_mode_edit_dlg_reset_back_btn);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    /*delete pic mode dlg*/
    else
    {
        c_uc_w2s_strncat(w2s_str,MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1)));

        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,pt_page_data->w2s_pic_name,c_uc_w2s_strlen(pt_page_data->w2s_pic_name));


        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE2),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE2)));

        i4_ret = a_ui_simple_dialog_set_yes_text(pt_page_data->h_dlg,
                                                      MENU_TEXT(MLM_MENU_KEY_DELETE_ITEM_DELETE));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_no_text(pt_page_data->h_dlg,
                                                      MENU_TEXT(MLM_MENU_KEY_DELETE_ITEM_CANCEL));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_yes_fct(pt_page_data->h_dlg,_pic_mode_edit_dlg_delete_yes_btn);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_no_fct(pt_page_data->h_dlg,_pic_mode_edit_dlg_delete_no_btn);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_set_other_key_cb_fct(pt_page_data->h_dlg,_pic_mode_edit_dlg_delete_back_btn);
        MENU_LOG_ON_FAIL(i4_ret);

    }


    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_dlg,
                                                  w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    if(pt_page_data->h_menu_current_focus == NULL_HANDLE)
    {
        i4_ret = c_wgl_get_focus(&pt_page_data->h_menu_current_focus);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = a_ui_simple_dialog_show(pt_page_data->h_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_float(pt_page_data->h_dlg,TRUE,FALSE);
    a_ui_simple_dialog_set_focus(pt_page_data->h_dlg, TRUE);
    /*set focus to cancel*/
    a_ui_simple_dialog_set_answer(pt_page_data->h_dlg,FALSE);
    a_ui_simple_dialog_repaint(pt_page_data->h_dlg);

#ifdef APP_TTS_SUPPORT
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(pt_page_data->b_is_reset_mode)
    {
        c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE1),
                                c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE1)));

        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,pt_page_data->w2s_pic_name,c_uc_w2s_strlen(pt_page_data->w2s_pic_name));

        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE2),
                                c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_RESET_PIC_MODE_TITLE2)));

    }
    else
    {
        c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1),
                                    c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1)));

        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,pt_page_data->w2s_pic_name,c_uc_w2s_strlen(pt_page_data->w2s_pic_name));


        c_sprintf(s_space, " ");
        c_uc_ps_to_w2s(s_space,w2s_space,8);
        c_uc_w2s_strcat(w2s_str,w2s_space);

        c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE2),
                            c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE2)));
    }
    c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL),
                            c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL)));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

    pt_page_data->b_is_dlg_show = TRUE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_pic_mode_edit_dlg_hide
 *
 * Description: menu_page_pic_mode_edit_dlg_hide
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_pic_mode_edit_dlg_hide(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = a_ui_simple_dialog_hide(pt_page_data->h_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show  = FALSE;
    c_wgl_float(pt_page_data->h_dlg,FALSE,FALSE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_item_set_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_item_set_focus(PIC_MODE_EDIT_BTN_TYPE_T e_type)
{
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    DBG_LOG_PRINT(("[MENU] e_type :%d,%s,%d\r\n",e_type,__FUNCTION__,__LINE__));

    switch (e_type)
    {
        case PIC_MODE_EDIT_BTN_SAVE:
        {
            i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_TTS_SUPPORT
            _pic_mode_edit_save_item_tts_play();
#endif
            break;
        }
        case PIC_MODE_EDIT_BTN_COPY:
        {
            i4_ret = c_wgl_set_focus(pt_page_data->h_copy_pic_mode,WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_TTS_SUPPORT
            _pic_mode_edit_copy_item_tts_play();
#endif
            break;
        }
        case PIC_MODE_EDIT_BTN_LOCK_UNLOCK:
        {
#ifdef LOCK_PIC_MODE_LB
            i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode_lb,WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
#else
            i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode,WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
#endif
#ifdef APP_TTS_SUPPORT
          _pic_mode_edit_lock_unlock_item_tts_play();
#endif
            break;
        }
        case PIC_MODE_EDIT_BTN_RESET_DELETE:
        {
            i4_ret = c_wgl_set_focus(pt_page_data->h_reset_pic_mode,WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
            _pic_mode_edit_reset_delete_item_tts_play();
#endif
            break;
        }
        default :
            break;

    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_item_key_up_down
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_TYPE_T e_type,BOOL b_up,BOOL b_backbar)
{
    UINT8               ui1_idx = 0;
    UINT8               ui1_idx_start = 0;
    INT32               i4_ret = MENUR_OK;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    DBG_LOG_PRINT(("[MENU] e_type:%d,b_up:%d,b_backbar:%d, %s,%d\r\n",e_type,b_up,b_backbar,__FUNCTION__,__LINE__));

    if(b_up)
    {
        if(b_backbar)
        {
            DBG_LOG_PRINT(("** not support up key for back bar item %s,%d\r\n",__FUNCTION__,__LINE__));
            return i4_ret;
        }

        if(e_type == PIC_MODE_EDIT_BTN_SAVE)
        {
            MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
            return i4_ret;
        }

        for (ui1_idx = (UINT8)(e_type - 1);ui1_idx >= PIC_MODE_EDIT_BTN_SAVE; ui1_idx --)
        {
            if(pt_page_data->b_item_enable[ui1_idx] == TRUE)
            {
                _pic_mode_edit_item_set_focus((PIC_MODE_EDIT_BTN_TYPE_T)ui1_idx);
                break;
            }

            if(ui1_idx == 0)
            {
                MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                break;
            }

        }

    }
    else
    {
        if(b_backbar)
        {
            ui1_idx_start = 0;
        }
        else
        {
            ui1_idx_start = (UINT8)(e_type + 1);
        }

        if(e_type == PIC_MODE_EDIT_BTN_RESET_DELETE)
        {
            DBG_LOG_PRINT(("** not support down key for last item %s,%d\r\n",__FUNCTION__,__LINE__));
            return i4_ret;
        }

        for (ui1_idx = ui1_idx_start;ui1_idx <= PIC_MODE_EDIT_BTN_RESET_DELETE; ui1_idx ++)
        {
            if(pt_page_data->b_item_enable[ui1_idx] == TRUE)
            {
                _pic_mode_edit_item_set_focus((PIC_MODE_EDIT_BTN_TYPE_T)ui1_idx);
                break;
            }
        }

    }
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _save_pic_mode_btn_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _save_pic_mode_btn_proc_fct(HANDLE_T    h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
#ifdef NEVER
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;
#endif /* NEVER */

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_CREATE_PIC_MODE));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            UINT16  ui2_count = 0;

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    ui2_count = get_cust_picture_mode_num();

                    if(ui2_count < ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX)
                    {

#ifdef LINUX_AUTO_TEST
                        if( !(access((const char*)save_del_pic_mode_file, F_OK)) )
                        {
                            system("rm -rf "save_del_pic_mode_file);
                        }
#endif
                        i4_ret = menu_nav_go(ui4_g_menu_custom_page_create_pic_mode,NULL);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = a_create_pic_mode_warn_dlg_show();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                }
                    break;

                case BTN_CURSOR_DOWN:
                    _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_SAVE,FALSE,FALSE);
#ifdef NEVER
                {
                    if(pt_page_data->b_is_lock_enable)
                    {
                        #ifdef LOCK_PIC_MODE_LB
                        i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode_lb,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                        #else
                        i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                        #endif

                    #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_lock_unlock_item_tts_play();
                    #endif
                    }
                    else if(pt_page_data->b_is_reset_enable)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_reset_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                    #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_reset_delete_item_tts_play();
                    #endif
                    }
                    else
                    {
                        menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                        menu_pm_repaint();
                    }
                }
#endif /* NEVER */
                    break;

                case BTN_RETURN:
                {
                    menu_nav_back();
                }
                    break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _copy_pic_mode_btn_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _copy_pic_mode_btn_proc_fct(HANDLE_T    h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
#ifdef NEVER
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;
#endif /* NEVER */

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_VID_COPY_PIC_MODE_HELP));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                    a_icl_set_picture_edit_type_status(ICL_PICTURE_EDIT_COPY_PIC);
                    menu_nav_go(ui4_g_menu_custom_page_lock_pic_lb2, NULL);
                    break;
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                    break;

                case BTN_CURSOR_UP:
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_COPY,TRUE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    break;

                case BTN_CURSOR_DOWN:
                {
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_COPY,FALSE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    break;
                }
                case BTN_RETURN:
                {
                    menu_nav_back();
                }
                    break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _lock_pic_mode_btn_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _lock_pic_mode_btn_proc_fct(HANDLE_T    h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    BOOL b_is_confirmed = FALSE;
                    BOOL b_is_lock_status = FALSE;

                    a_get_is_pin_confirmed(&b_is_confirmed);
                    ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} b_is_confirmed:%d \n", __FUNCTION__, __LINE__, b_is_confirmed )););

                    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if(!b_is_confirmed)
                    {
                        if((!_lock_pic_mode_check_is_set_sys_pin()) &&
                            (!b_is_lock_status))
                        {
                            /* create system pin */
                            i4_ret = menu_nav_go(ui4_g_menu_custom_page_lock_pic_mode,NULL);
                        }
                        else
                        {
                            /* confirmed system pin */
                            i4_ret = menu_nav_go(ui4_g_menu_custom_page_unlock_pic_mode,NULL);
                        }
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        /* only update pic mode lock status & item UI ,when confirmed system pin in other page */
                        BOOL b_is_set_lock_status = FALSE;
                        if(b_is_lock_status)
                        {
                            b_is_set_lock_status = FALSE;
                        }
                        else
                        {
                            b_is_set_lock_status = TRUE;
                        }

                        a_cfg_cust_set_cust_pic_mode_lock_status(b_is_set_lock_status);
                        set_delay_lock_cust_pic_mode_status(b_is_set_lock_status);
                        pt_page_data->b_is_lock_mode = a_menu_is_picture_locked();
                        _pic_mode_edit_update_ui();

                        menu_pic_energy_change_sepcial_page_set_status(TRUE);

                        #ifdef APP_TTS_SUPPORT

                        UINT16 ui2_hlt_idx = 0;
                        UTF16_T w2s_name_str[128] = {0};

                        i4_ret = c_wgl_do_cmd (h_widget,
                                               WGL_CMD_LB_GET_HLT_INDEX,
                                               WGL_PACK (&ui2_hlt_idx),
                                               NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = c_wgl_do_cmd (h_widget,
                                               WGL_CMD_LB_GET_ITEM_TEXT,
                                               WGL_PACK_2 (ui2_hlt_idx, 0),
                                               WGL_PACK   (w2s_name_str));
                        MENU_LOG_ON_FAIL(i4_ret);

                        c_uc_w2s_strcat(w2s_name_str, L", ");

                        i4_ret = c_wgl_do_cmd (h_widget,
                                               WGL_CMD_LB_GET_ITEM_TEXT,
                                               WGL_PACK_2 (ui2_hlt_idx, 1),
                                               WGL_PACK   (w2s_name_str + c_uc_w2s_strlen(w2s_name_str)));
                        MENU_LOG_ON_FAIL(i4_ret);

                        a_app_tts_play(w2s_name_str, 128);

                        #endif
                    }
                }
                    break;

                case BTN_CURSOR_UP:
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_LOCK_UNLOCK,TRUE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
                {
                    if(pt_page_data->b_is_save_item_enable==TRUE)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                    #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_save_item_tts_play();
                    #endif
                    }
                    else
                    {
                        MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                    }
                }
#endif /* NEVER */
                    break;

                case BTN_CURSOR_DOWN:
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_LOCK_UNLOCK,FALSE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
                {
                    if(pt_page_data->b_is_reset_enable)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_reset_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                    #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_reset_delete_item_tts_play();
                    #endif
                    }
                    else
                    {
                        menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                        menu_pm_repaint();
                    }
                }
#endif /* NEVER */
                    break;

                case BTN_RETURN:
                {
                    menu_nav_back();
                }
                    break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _reset_pic_mode_btn_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _reset_pic_mode_btn_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if(pt_page_data->b_is_reset_mode)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_RESET_PIC_MODE));
            }
            else
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_DELETE_PIC_MODE));
            }
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
#ifdef LINUX_AUTO_TEST
                    if( !(access((const char*)reset_pic_mode_file, F_OK)) )
                    {
                        system("rm -rf "reset_pic_mode_file);
                    }
#endif
                    menu_page_pic_mode_edit_dlg_show();
                }
                    break;

                case BTN_CURSOR_UP:
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_RESET_DELETE,TRUE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
                {
                    if(pt_page_data->b_is_lock_enable)
                    {
                        #ifdef LOCK_PIC_MODE_LB
                        i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode_lb,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                        #else
                        i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                        #endif
                    #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_lock_unlock_item_tts_play();
                    #endif
                    }
                    else if(pt_page_data->b_is_save_item_enable)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_save_item_tts_play();
                    #endif
                    }
                    else
                    {
                        MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                    }
                }
#endif /* NEVER */
                    break;

                case BTN_CURSOR_DOWN:
                {
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    menu_pm_repaint();
                }
                    break;

                case BTN_RETURN:
                {
                    menu_nav_back();
                }
                    break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_btn_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_btn_create(HANDLE_T h_parent,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    PIC_MODE_EDIT_BTN_TYPE_T e_type,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    INT32               i4_top = 0;
    GL_COLOR_T          t_color_txt = t_g_menu_color_white;
    GL_COLOR_T          t_color_txt_disable = { 255, {128}, {128}, {128}};

    if (PIC_MODE_EDIT_BTN_SAVE== e_type)
    {
        i4_top = PIC_MODE_EDIT_SAVE_BTN_H* 0;
    }
    else if (PIC_MODE_EDIT_BTN_COPY== e_type)
    {
        i4_top = PIC_MODE_EDIT_SAVE_BTN_H* 1;
    }
    else if (PIC_MODE_EDIT_BTN_LOCK_UNLOCK== e_type)
    {
        i4_top = PIC_MODE_EDIT_SAVE_BTN_H * 2;
    }
    else if (PIC_MODE_EDIT_BTN_RESET_DELETE== e_type)
    {
        i4_top = PIC_MODE_EDIT_SAVE_BTN_H * 3;
    }

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     PIC_MODE_EDIT_SAVE_BTN_X,
                     i4_top,
                     PIC_MODE_EDIT_SAVE_BTN_W,
                     PIC_MODE_EDIT_SAVE_BTN_H
                     );

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                pf_wdgt_proc,
                                255,
                                NULL,
                                NULL,
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left   = PIC_MODE_EDIT_BTN_INSET_LEFT + 8;
    t_inset.i4_right  = PIC_MODE_EDIT_BTN_INSET_RIGHT;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_common_sidebar_highlight_v2;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_common_sidebar_highlight_v2;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable = t_color_txt;
    t_color_info.u_color_data.t_extend.t_disable = t_color_txt_disable;
    t_color_info.u_color_data.t_extend.t_highlight = t_color_txt;
    t_color_info.u_color_data.t_extend.t_highlight_inactive = t_color_txt;
    t_color_info.u_color_data.t_extend.t_push = t_color_txt;
    t_color_info.u_color_data.t_extend.t_push_unhighlight = t_color_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(& t_color_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_strncpy(t_font_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_font_info.ui1_custom_size = 24;

    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pw2s_str),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static BOOL _lock_pic_mode_check_is_set_sys_pin(VOID)
{
    UTF16_T    u2s_pwd_exist[5] = {0};
    CHAR       str_pwd[5] = {0};
    CHAR       str_pwd_default[5] = {0};
    UINT8      ui1_idx = 0;

    for(ui1_idx=0; ui1_idx < 5; ui1_idx++)
    {
        str_pwd_default[ui1_idx] = '0';
    }


    a_cfg_get_password(u2s_pwd_exist, 5);
    c_uc_w2s_to_ps(u2s_pwd_exist,
                   str_pwd,
                   5);
    DBG_INFO(("\n%s,%d,system pin:%s\n",__FUNCTION__,__LINE__,str_pwd));

    if (c_strncmp(str_pwd, str_pwd_default, 4) == 0)
    {
        return FALSE;
    }

    return TRUE;
}
static INT32 _pic_mode_edit_list_item_create (HANDLE_T h_parent,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    PIC_MODE_EDIT_BTN_TYPE_T e_type,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32                       i4_ret = MENUR_OK;
    INT32                       i4_top = 0;
    UINT16                      ui2_i = 0;
    GL_RECT_T                   t_rect = {0};
    GL_COLOR_T                  t_color_txt = { 255, { 255 }, { 255 }, { 255 }};
    GL_COLOR_T                  t_color_txt_disable = { 255, {128}, {128}, {128}};
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem = {0};
    WGL_LB_INIT_T               t_lb_init = {0};
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_LB_ITEM_T               at_items[2];
    WGL_FONT_INFO_T             t_fnt_info = {0};
    WGL_INSET_T                 t_inset;


    if (PIC_MODE_EDIT_BTN_LOCK_UNLOCK== e_type)
    {
        i4_top = PIC_MODE_EDIT_SAVE_BTN_H * 2;
    }

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     PIC_MODE_EDIT_SAVE_BTN_X,
                     i4_top,
                     PIC_MODE_EDIT_SAVE_BTN_W,
                     PIC_MODE_EDIT_SAVE_BTN_H
                     );

    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width        = 419;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = 219 ;

    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = PIC_MODE_EDIT_SAVE_BTN_H;//MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_LIST_BOX,
                                WGL_CONTENT_LIST_BOX_DEF,
                                WGL_BORDER_NULL,//WGL_BORDER_TRANSP,
                                &t_rect,
                                pf_wdgt_proc,
                                255,
                                &t_lb_init,
                                NULL,
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;

    for (ui2_i=0; ui2_i<2; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(ui2_i),
                           WGL_PACK(&t_fnt_info));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET ,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = PIC_MODE_EDIT_BTN_INSET_LEFT + 8;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set LB colors */
    t_lb_color.t_normal = t_color_txt;
    t_lb_color.t_disable = t_color_txt_disable;
    t_lb_color.t_highlight = t_color_txt;
    t_lb_color.t_highlight_unfocus = t_color_txt;
    t_lb_color.t_pushed = t_color_txt;
    t_lb_color.t_selected = t_color_txt;
    t_lb_color.t_selected_disable = t_color_txt;

    for (ui2_i=0; ui2_i<2; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(ui2_i, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
         MENU_LOG_ON_FAIL(i4_ret);
    }

    /* set img*/
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_common_sidebar_highlight_v2;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = h_g_menu_common_sidebar_highlight_v2;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB elements */
    UTF16_T         w2s_str[128] = {0};
    c_uc_w2s_strcpy(w2s_str,MENU_TEXT(MLM_MENU_KEY_OFF));

    at_items[0].e_col_type       = LB_COL_TYPE_TEXT ;
    at_items[0].data.pw2s_text   = pw2s_str;

    at_items[1].e_col_type       = LB_COL_TYPE_TEXT ;
    at_items[1].data.pw2s_text   = w2s_str;

    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_save_btn_create
 *
 * Description: save pic mode item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _save_pic_mode_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = _pic_mode_edit_btn_create(pt_page_data->h_cnt_frm,
                                        _save_pic_mode_btn_proc_fct,
                                        PIC_MODE_EDIT_BTN_SAVE,
                                        MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE),
                                        &pt_page_data->h_save_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _copy_pic_mode_btn_create
 *
 * Description: lock pic mode item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _copy_pic_mode_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = _pic_mode_edit_btn_create(pt_page_data->h_cnt_frm,
                                        _copy_pic_mode_btn_proc_fct,
                                        PIC_MODE_EDIT_BTN_COPY,
                                        MENU_TEXT(MLM_MENU_KEY_VID_COPY_PIC_MODE),
                                        &pt_page_data->h_copy_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _lock_pic_mode_btn_create
 *
 * Description: lock pic mode item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _lock_pic_mode_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = _pic_mode_edit_list_item_create(pt_page_data->h_cnt_frm,
                                        _lock_pic_mode_btn_proc_fct,
                                        PIC_MODE_EDIT_BTN_LOCK_UNLOCK,
                                        MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_LOCK_PIC_MODE),
                                        &pt_page_data->h_lock_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _lock_pic_mode_lb_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32  i4_ret = MENUR_OK;
    PIC_MODE_EDIT*  pt_page_data = &t_g_pic_mode_edit_page_data;
    BOOL b_is_lock_status = FALSE;
    BOOL b_is_confirmed = FALSE;

    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                    a_icl_set_picture_edit_type_status(ICL_PICTURE_EDIT_LOCK_PIC);
                    menu_nav_go(ui4_g_menu_custom_page_lock_pic_lb2, NULL);
                    break;
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    a_get_is_pin_confirmed(&b_is_confirmed);
                    ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} b_is_confirmed:%d \n", __FUNCTION__, __LINE__, b_is_confirmed )););
                    if (!b_is_confirmed)
                    {
                        a_icl_set_picture_edit_type_status(ICL_PICTURE_EDIT_LOCK_PIC);
                        if (!_lock_pic_mode_check_is_set_sys_pin() && !b_is_lock_status)
                        {
                            /* create system pin */
                            i4_ret = menu_nav_go(ui4_g_menu_custom_page_lock_pic_mode,NULL);
                        }
                        else
                        {
                            /* confirmed system pin */
                            if (b_is_lock_status)
                            {
                                a_menu_set_picture_mode_tmp_lock_status(FALSE);
                            }
                            else
                            {
                                a_menu_set_picture_mode_tmp_lock_status(TRUE);
                            }

                            i4_ret = menu_nav_go(ui4_g_menu_custom_page_unlock_pic_mode,NULL);
                        }
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        b_is_lock_status ^= 1;

                        i4_ret = a_cfg_cust_set_cust_pic_mode_lock_status(b_is_lock_status);
                        MENU_LOG_ON_FAIL(i4_ret);
                        pt_page_data->b_is_lock_mode = a_menu_is_picture_locked();
                        set_delay_lock_cust_pic_mode_status(b_is_lock_status);
                        menu_pic_energy_change_sepcial_page_set_status(TRUE);
                        _pic_mode_edit_set_reset_delete_item();
                        #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_lock_unlock_item_tts_play();
                        #endif
                    }
                    break;
                }
                case BTN_CURSOR_UP:
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_LOCK_UNLOCK,TRUE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
                {
                    if(pt_page_data->b_is_save_item_enable==TRUE)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_save_item_tts_play();
                        #endif
                    }
                    else
                    {
                        MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                    }
                }
#endif /* NEVER */
                    break;
                case BTN_CURSOR_DOWN:
                    i4_ret = _pic_mode_edit_item_key_up_down(PIC_MODE_EDIT_BTN_LOCK_UNLOCK,FALSE,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
                {
                    if(pt_page_data->b_is_reset_enable)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_reset_pic_mode,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        #ifdef APP_TTS_SUPPORT
                        _pic_mode_edit_reset_delete_item_tts_play();
                        #endif
                    }
                    else
                    {
                        menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                        menu_pm_repaint();
                    }
                }
#endif /* NEVER */
                    break;
                case BTN_RETURN:
                    menu_nav_back();
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}
static VOID _pic_mode_edit_refresh_ui_for_reset_ap(VOID *p1, VOID *p2, VOID *p3)
{
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    UINT8               ui1_status = ICL_PQ_CHANGE_NOTHING;
     INT32               i4_ret;
    i4_ret = a_icl_custom_get_pq_chg_status(&ui1_status);
    if (ICLR_OK != i4_ret)
    {
        return ;
    }
    if(!pt_page_data->b_this_page_show)
    {
        return ;
    }
    if (((ICL_PQ_CHANGE_NOTHING == ui1_status)&&(pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_RESET_DELETE]))||
        ((ICL_PQ_CHANGE_NOTHING != ui1_status)&&(!pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_RESET_DELETE])))
    {
        if(ICL_PQ_CHANGE_NOTHING == ui1_status)
        {
            c_wgl_set_focus(pt_page_data->h_save_pic_mode,TRUE);
        }
        _pic_mode_edit_update_ui();
        menu_pm_repaint();
   }
}

static INT32 _pic_mode_edit_pq_change_icl_nfy_cb(UINT16    ui2_nfy_id,
                                              VOID*     pv_tag,
                                              ICL_NOTIFY_DATA_T* pt_notify_data)
{
    menu_request_context_switch(_pic_mode_edit_refresh_ui_for_reset_ap, NULL, NULL, NULL);
    return MENUR_OK;
}

static INT32 _lock_pic_mode_lb_create()
{
    INT32 i4_ret = 0;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = menu_list_create(pt_page_data->h_cnt_frm,
                              LOCK_PIC_MODE_LB_OFFSET,
                              (MLM_MENU_KEY_ON-MLM_MENU_KEY_OFF+1),
                              _lock_pic_mode_lb_proc_fct,
                              &pt_page_data->h_lock_pic_mode_lb);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _lock_pic_mode_btn_create
 *
 * Description: lock pic mode item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _reset_pic_mode_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = _pic_mode_edit_btn_create(pt_page_data->h_cnt_frm,
                                        _reset_pic_mode_btn_proc_fct,
                                        PIC_MODE_EDIT_BTN_RESET_DELETE,
                                        MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_RESET_PIC_MODE),
                                        &pt_page_data->h_reset_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    c_memset(&t_g_pic_mode_edit_page_data, 0, sizeof(PIC_MODE_EDIT));

    pt_page_data->ui4_cur_page_id = ui4_page_id;
    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /*save pic mode item*/
    i4_ret = _save_pic_mode_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*save pic mode item*/
    i4_ret = _lock_pic_mode_lb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _lock_pic_mode_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*save pic mode item*/
    i4_ret = _copy_pic_mode_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*save pic mode item*/
    i4_ret = _reset_pic_mode_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pic_mode_edit_dlg_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_icl_notify_reg(ICL_GRPID_PQ_CHANGE_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _pic_mode_edit_pq_change_icl_nfy_cb,
                              &pt_page_data->ui2_icl_nfy_id_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _update_ui
 *
 * Description:update title
 *          update save pic mode item enable/disable
 *          update lock/unlok pic mode item name
 *          update reset/delete pic mode item name
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_update_ui(VOID)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = _pic_mode_edit_set_title();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pic_mode_edit_set_save_item();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pic_mode_edit_set_copy_item();
    MENU_LOG_ON_FAIL(i4_ret);

    if (LOCK_PIC_MODE_LB)
    {
        i4_ret = _pic_mode_edit_set_lock_unlock_lb_item();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = c_wgl_set_visibility(pt_page_data->h_lock_pic_mode, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _pic_mode_edit_set_lock_unlock_item();
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = _pic_mode_edit_set_reset_delete_item();
    MENU_CHK_FAIL(i4_ret);

    /*Adjust last shadow position*/
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * PIC_MODE_EDIT_ITEM_NUM + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_set_title
 *
 * Description: PICTURE MODE EDIT - pic mode name (current pic mode)
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _pic_mode_edit_set_title(VOID)
{
    INT32               i4_ret = MENUR_OK;;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    INT16               i2_pic_mode = 0;
    UTF16_T             w2s_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    CHAR                s_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    UTF16_T             w2s_str_title[MENU_PRESET_PIC_MODE_NAME_TITLE_LEN+1] = {0};
    UTF16_T             w2s_asterisk[8+1] = {0};
    CHAR                s_asterisk[8+1] = {0};
    BOOL                b_is_chg = FALSE;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);

    DBG_INFO(("\n####%s(%d)i2_pic_mode=%d\n",__FUNCTION__,__LINE__,i2_pic_mode));
    MENU_LOG_ON_FAIL(i4_ret);

    if (i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        pt_page_data->b_is_reset_mode = TRUE;

        c_memset(w2s_pic_name,0,MENU_PRESET_PIC_MODE_NAME_LEN+1);
        c_uc_w2s_strncpy(w2s_pic_name, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+i2_pic_mode),(MENU_PRESET_PIC_MODE_NAME_LEN));

        a_cfg_get_preset_pic_mode_chg_status(i2_pic_mode,&b_is_chg);

        DBG_INFO(("\n####%s(%d)b_is_chg=%d\n",__FUNCTION__,__LINE__,b_is_chg));
        if(b_is_chg)
        {
            c_sprintf(s_asterisk, "*");
            c_uc_ps_to_w2s(s_asterisk,w2s_asterisk,8);
            c_uc_w2s_strncat(w2s_pic_name,w2s_asterisk,8);
        }

    }
    else
    {
        pt_page_data->b_is_reset_mode = FALSE;

        c_memset(w2s_pic_name,0,MENU_PRESET_PIC_MODE_NAME_LEN+1);
        c_memset(pt_page_data->s_input_buf, 0, MENU_CUST_PIC_MODE_NAME_MAX_LEN+2);
        a_cfg_cust_get_cust_pic_mode_name(i2_pic_mode,pt_page_data->s_input_buf,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
        pt_page_data->s_input_buf[MENU_CUST_PIC_MODE_NAME_MAX_LEN +1] = 0;
        DBG_INFO(("\n####%s(%d)pt_page_data->s_input_buf=%s\n",__FUNCTION__,__LINE__,pt_page_data->s_input_buf));
        c_uc_ps_to_w2s (pt_page_data->s_input_buf, w2s_pic_name, MENU_PRESET_PIC_MODE_NAME_LEN);
    }

    c_uc_w2s_set(pt_page_data->w2s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN,0);
    c_uc_w2s_strncpy(pt_page_data->w2s_pic_name,w2s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);

    c_uc_w2s_to_ps(pt_page_data->w2s_pic_name,s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);
    DBG_INFO(("\n####%s(%d)s_pic_name=%s\n",__FUNCTION__,__LINE__,s_pic_name));

    //c_uc_w2s_strncpy(w2s_str_title, MENU_TEXT(MLM_MENU_KEY_PIC_MODE_EDIT_TITLE),MENU_PRESET_PIC_MODE_NAME_TITLE_LEN );

    c_memset(w2s_str_title, 0, MENU_PRESET_PIC_MODE_NAME_TITLE_LEN+1);

    c_uc_w2s_strncpy(w2s_str_title, MENU_TEXT(MLM_MENU_KEY_PIC_MODE_EDIT_ITEM),MENU_PRESET_PIC_MODE_NAME_TITLE_LEN );
    w2s_str_title[MENU_PRESET_PIC_MODE_NAME_TITLE_LEN] = L'\0';

    i4_ret = menu_main_set_title_text(w2s_str_title);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_set_save_item
 *
 * Description: set save pic mode enable/disable
 *          if current pic mode is preset pic mode -> set enable
 *          if current pic mode is custom pic mode -> set disable
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _pic_mode_edit_set_save_item(VOID)
{
    INT32               i4_ret = MENUR_OK;;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    BOOL                b_btn_pushed = FALSE;
    UTF16_T             w2s_str[256] = {0};

    c_uc_w2s_strcpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE));

    i4_ret = c_wgl_do_cmd(pt_page_data->h_save_pic_mode,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(w2s_str),
                              WGL_PACK(c_uc_w2s_strlen(w2s_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_page_data->b_is_reset_mode)
    {
        i4_ret = c_wgl_enable(pt_page_data->h_save_pic_mode,TRUE);
        DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
        pt_page_data->b_is_save_item_enable=TRUE;
#endif /* NEVER */

        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_SAVE] = TRUE;
    }
    else
    {
        i4_ret = c_wgl_do_cmd(pt_page_data->h_save_pic_mode,
                WGL_CMD_BTN_GET_PUSHED,
                WGL_PACK(&b_btn_pushed),
                WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);
        if(b_btn_pushed)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_save_pic_mode,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    WGL_PACK(FALSE),
                                    WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);
        }
        i4_ret = c_wgl_enable(pt_page_data->h_save_pic_mode,FALSE);
        DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
        pt_page_data->b_is_save_item_enable=FALSE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_SAVE] = FALSE;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_set_copy_item
 *
 * Description: set save pic mode enable/disable
 *          if current pic mode is preset pic mode -> set enable
 *          if current pic mode is custom pic mode -> set disable
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _pic_mode_edit_set_copy_item(VOID)
{
    INT32               i4_ret = MENUR_OK;;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    BOOL                b_btn_pushed = FALSE;
    UTF16_T             w2s_str[256] = {0};

    c_uc_w2s_strcpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_VID_COPY_PIC_MODE));

    i4_ret = c_wgl_do_cmd(pt_page_data->h_copy_pic_mode,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(w2s_str),
                              WGL_PACK(c_uc_w2s_strlen(w2s_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    if (!pt_page_data->b_is_reset_mode)
    {
        i4_ret = c_wgl_enable(pt_page_data->h_copy_pic_mode,TRUE);
        DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
        pt_page_data->b_is_save_item_enable=TRUE;
#endif /* NEVER */

        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_COPY] = TRUE;
    }
    else
    {
        i4_ret = c_wgl_do_cmd(pt_page_data->h_copy_pic_mode,
                WGL_CMD_BTN_GET_PUSHED,
                WGL_PACK(&b_btn_pushed),
                WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);
        if(b_btn_pushed)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_copy_pic_mode,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    WGL_PACK(FALSE),
                                    WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);
        }
        i4_ret = c_wgl_enable(pt_page_data->h_copy_pic_mode,FALSE);
        DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
        pt_page_data->b_is_save_item_enable=FALSE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_COPY] = FALSE;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_set_reset_delete_item
 *
 * Description: if(reset mode)  reset picture mode - pic mode name
 *           else                delete picture mode - pic mode name
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _pic_mode_edit_set_reset_delete_item(VOID)
{
    INT32               i4_ret;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    UTF16_T             w2s_str_name[256] = {0};
    CHAR                s_space[8+1] = {0};
    UTF16_T             w2s_space[8+1] = {0};
    CHAR                s_dash[8+1] = {0};
    UTF16_T             w2s_dash[8+1] = {0};
    INT16               i2_pic_mode = 0;
    BOOL                b_is_chg = FALSE;

    CHAR                s_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    BOOL                b_btn_pushed = FALSE;

    DBG_INFO(("\n####%s(%d)reset/delete,pt_page_data->b_is_reset_mode=%d\n",__FUNCTION__,__LINE__,pt_page_data->b_is_reset_mode));

    if(pt_page_data->b_is_reset_mode)
    {
        c_uc_w2s_strncat(w2s_str_name,MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_RESET_PIC_MODE),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_RESET_PIC_MODE)));

    }
    else
    {
        c_uc_w2s_strncat(w2s_str_name,MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_DELETE_PIC_MODE),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_DELETE_PIC_MODE)));
    }

    c_sprintf(s_space, " ");
    c_uc_ps_to_w2s(s_space,w2s_space,8);
    c_uc_w2s_strncat(w2s_str_name,w2s_space,8);

    c_sprintf(s_dash, "-");
    c_uc_ps_to_w2s(s_dash,w2s_dash,8);
    c_uc_w2s_strncat(w2s_str_name,w2s_dash,8);

    c_uc_w2s_strncat(w2s_str_name,w2s_space,8);

    c_uc_w2s_to_ps(pt_page_data->w2s_pic_name,s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);
    DBG_INFO(("\n####%s(%d)s_pic_name=%s\n",__FUNCTION__,__LINE__,s_pic_name));

    c_uc_w2s_strncat(w2s_str_name,pt_page_data->w2s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_pic_mode,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(w2s_str_name),
                              WGL_PACK(c_uc_w2s_strlen(w2s_str_name)));
    MENU_LOG_ON_FAIL(i4_ret);

    /*for reset/delete pic mode item*/
    if(pt_page_data->b_is_reset_mode)
    {
        /*for reset pic mode item*/
#ifndef APP_LARGE_EEPROM_SUPPORT
        i4_ret = acfg_cust_filesys_get(CFG_MAKE_ID(APP_CFG_GRPID_FILESYS_BASE, APP_CFG_RECID_FILESYS_PIC_MODE),
                                                    &i2_pic_mode);
#else
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
#endif
        a_cfg_get_preset_pic_mode_chg_status(i2_pic_mode,&b_is_chg);
        if(b_is_chg)
        {
            c_wgl_enable(pt_page_data->h_reset_pic_mode,TRUE);
#ifdef NEVER
            pt_page_data->b_is_reset_enable = TRUE;
#endif /* NEVER */

            pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_RESET_DELETE] = TRUE;
        }
        else
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_pic_mode,
                               WGL_CMD_BTN_GET_PUSHED,
                               WGL_PACK(&b_btn_pushed),
                               WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);
            if(b_btn_pushed)
            {
                i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_pic_mode,
                                        WGL_CMD_BTN_SET_PUSHED,
                                        WGL_PACK(FALSE),
                                        WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);
            }
            i4_ret = c_wgl_enable(pt_page_data->h_reset_pic_mode,FALSE);
#ifdef NEVER
            pt_page_data->b_is_reset_enable = FALSE;
#endif /* NEVER */
            pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_RESET_DELETE] = FALSE;
        }

    }
    else
    {
        if(pt_page_data->b_is_lock_mode)
        {
            /*for delete pic mode item*/
            c_wgl_enable(pt_page_data->h_reset_pic_mode,FALSE);
#ifdef NEVER
            pt_page_data->b_is_reset_enable = FALSE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_RESET_DELETE] = FALSE;

        }
        else
        {
            /*for delete pic mode item*/
            c_wgl_enable(pt_page_data->h_reset_pic_mode,TRUE);
#ifdef NEVER
            pt_page_data->b_is_reset_enable = TRUE;
#endif /* NEVER */
            pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_RESET_DELETE] = TRUE;

        }

    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_set_lock_unlock_item
 *
 * Description: pic mode is lock: show unlock pic mode; pic mode is unlock: show lock pic mode
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_set_lock_unlock_item(VOID)
{
    INT32               i4_ret = MENUR_OK;
    BOOL                b_is_lock_status = FALSE;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("\n####%s(%d)reset/delete,b_is_lock_status=%d\n",__FUNCTION__,__LINE__,b_is_lock_status));

    UTF16_T         w2s_str[128] = {0};
    c_uc_w2s_strcpy(w2s_str,MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_LOCK_PIC_MODE));

    i4_ret = c_wgl_do_cmd(pt_page_data->h_lock_pic_mode,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(0,0),
                              w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(b_is_lock_status)
    {
        pt_page_data->b_is_lock_mode = TRUE;

        c_uc_w2s_strcpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_ON));
    }
    else
    {
        pt_page_data->b_is_lock_mode = FALSE;

        c_uc_w2s_strcpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF));
    }
    i4_ret = c_wgl_do_cmd(pt_page_data->h_lock_pic_mode,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(0,1),
                              w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    if(pt_page_data->b_is_reset_mode)
    {
        i4_ret = c_wgl_enable(pt_page_data->h_lock_pic_mode,FALSE);
        DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
#ifdef NEVER
        pt_page_data->b_is_lock_enable = FALSE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_LOCK_UNLOCK] = FALSE;

    }
    else
    {
        i4_ret = c_wgl_enable(pt_page_data->h_lock_pic_mode,TRUE);
        DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
#ifdef NEVER
        pt_page_data->b_is_lock_enable = TRUE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_LOCK_UNLOCK] = TRUE;
    }
    return MENUR_OK;

}

static INT32 _pic_mode_edit_set_lock_unlock_lb_item()
{
    INT32 i4_ret = 0;
    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;
    BOOL  b_is_lock_status = FALSE;

    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_list_chg_lang(pt_page_data->h_lock_pic_mode_lb,
                                MLM_MENU_KEY_MENU_ITEM_LOCK_PIC_MODE,
                                MLM_MENU_KEY_OFF,
                                MLM_MENU_KEY_ON
                                );
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(pt_page_data->h_lock_pic_mode_lb);

    menu_list_set_idx(pt_page_data->h_lock_pic_mode_lb, b_is_lock_status ? 1 : 0);

    pt_page_data->b_is_lock_mode = a_menu_is_picture_locked();

    if(pt_page_data->b_is_reset_mode)
    {
        i4_ret = c_wgl_enable(pt_page_data->h_lock_pic_mode_lb,FALSE);
#ifdef NEVER
        pt_page_data->b_is_lock_enable = FALSE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_LOCK_UNLOCK] = FALSE;
    }
    else
    {
        i4_ret = c_wgl_enable(pt_page_data->h_lock_pic_mode_lb,TRUE);
#ifdef NEVER
        pt_page_data->b_is_lock_enable = TRUE;
#endif /* NEVER */
        pt_page_data->b_item_enable[PIC_MODE_EDIT_BTN_LOCK_UNLOCK] = TRUE;
    }

    return i4_ret;
}
#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_save_item_tts_play
 *
 * Description: if(reset mode)  reset picture mode - pic mode name
 *           else                delete picture mode - pic mode name
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_save_item_tts_play(VOID)
{
    UTF16_T w2s_str[128] = {0};

    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_copy_item_tts_play
 *
 * Description: if(reset mode)  reset picture mode - pic mode name
 *           else                delete picture mode - pic mode name
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_copy_item_tts_play(VOID)
{
    UTF16_T w2s_str[128] = {0};

    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_VID_COPY_PIC_MODE));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_lock_unlock_item_tts_play
 *
 * Description: if(reset mode)  reset picture mode - pic mode name
 *           else                delete picture mode - pic mode name
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_lock_unlock_item_tts_play(VOID)
{
    BOOL    b_is_lock_status = FALSE;
    INT32   i4_ret = 0;
    UTF16_T w2s_str[128] = {0};

    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ITEM_LOCK_PIC_MODE));
    c_uc_w2s_strcat(w2s_str, L",");

    if(!b_is_lock_status)
    {
        c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_OFF),c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_OFF)));
    }
    else
    {
        c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_ON),c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_ON)));
    }
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pic_mode_edit_reset_delete_item_tts_play
 *
 * Description: if(reset mode)  reset picture mode - pic mode name
 *           else                delete picture mode - pic mode name
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pic_mode_edit_reset_delete_item_tts_play(VOID)
{
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;
    UTF16_T             w2s_str_name[MENU_PRESET_PIC_MODE_NAME_TITLE_LEN+1] = {0};
    CHAR                s_space[8+1] = {0};
    UTF16_T             w2s_space[8+1] = {0};
    CHAR                s_dash[8+1] = {0};
    UTF16_T             w2s_dash[8+1] = {0};
    CHAR                s_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};

    if(pt_page_data->b_is_reset_mode)
    {
        c_uc_w2s_strncat(w2s_str_name,MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ITEM_RESET_PIC_MODE),c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ITEM_RESET_PIC_MODE)));
    }
    else
    {
        c_uc_w2s_strncat(w2s_str_name,MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ITEM_DELETE_PIC_MODE),c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ITEM_DELETE_PIC_MODE)));
    }

    c_sprintf(s_space, " ");
    c_uc_ps_to_w2s(s_space,w2s_space,8);
    c_uc_w2s_strncat(w2s_str_name,w2s_space,8);

    c_sprintf(s_dash, "-");
    c_uc_ps_to_w2s(s_dash,w2s_dash,8);
    c_uc_w2s_strncat(w2s_str_name,w2s_dash,8);

    c_uc_w2s_strncat(w2s_str_name,w2s_space,8);

    c_uc_w2s_to_ps(pt_page_data->w2s_pic_name,s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);

    c_uc_w2s_strncat(w2s_str_name,pt_page_data->w2s_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);
    a_app_tts_play(w2s_str_name,c_uc_w2s_strlen(w2s_str_name));

    return MENUR_OK;
}
#endif


static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32               i4_ret;
    UINT8               ui1_val      = ICL_PICTURE_EDIT_LOCK_PIC;
    PIC_MODE_EDIT*      pt_page_data = &t_g_pic_mode_edit_page_data;

    /* shit. */
    pt_page_data->b_finish = TRUE;
    pt_page_data->b_this_page_show = TRUE;

    i4_ret = _pic_mode_edit_update_ui();
    MENU_LOG_ON_FAIL(i4_ret);

    a_icl_get_picture_edit_type_status(&ui1_val);
    if(ui1_val == ICL_PICTURE_EDIT_COPY_PIC)
    {
        _pic_mode_edit_item_set_focus(PIC_MODE_EDIT_BTN_COPY);
        a_icl_set_picture_edit_type_status(ICL_PICTURE_EDIT_INVALID);
    }
    else if(ui1_val == ICL_PICTURE_EDIT_LOCK_PIC)
    {
        _pic_mode_edit_item_set_focus(PIC_MODE_EDIT_BTN_LOCK_UNLOCK);
        a_icl_set_picture_edit_type_status(ICL_PICTURE_EDIT_INVALID);
    }
    else
    {
        /* set first focus item*/
        if(pt_page_data->b_is_reset_mode==TRUE)
        {
            i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,
                                     WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        #ifdef APP_TTS_SUPPORT
            _pic_mode_edit_save_item_tts_play();
        #endif

        }
        else
        {
            i4_ret = c_wgl_set_focus(pt_page_data->h_copy_pic_mode,
                                     WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        #ifdef APP_TTS_SUPPORT
            _pic_mode_edit_copy_item_tts_play();
        #endif
        }

    }

#ifdef NEVER
    if(pt_page_data->b_is_save_item_enable==TRUE)
    {
        i4_ret = c_wgl_set_focus(pt_page_data->h_save_pic_mode,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        _pic_mode_edit_save_item_tts_play();
    #endif
    }
    else if(pt_page_data->b_is_lock_enable)
    {
        #ifdef LOCK_PIC_MODE_LB
        i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode_lb,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
        #else
        i4_ret = c_wgl_set_focus(pt_page_data->h_lock_pic_mode,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
        #endif

    #ifdef APP_TTS_SUPPORT
       _pic_mode_edit_lock_unlock_item_tts_play();
    #endif
    }
    else
    {
        i4_ret = c_wgl_set_focus(pt_page_data->h_reset_pic_mode,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        _pic_mode_edit_reset_delete_item_tts_play();
    #endif
    }
#endif /* NEVER */
    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    //INT32 i4_ret = MENUR_OK;

    PIC_MODE_EDIT* pt_page_data = &t_g_pic_mode_edit_page_data;

    if(pt_page_data->b_is_dlg_show)
    {
        menu_page_pic_mode_edit_dlg_hide();
    }

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }
    menu_help_tip_keytip_show(TRUE);

    pt_page_data->b_this_page_show = FALSE;

    pt_page_data->b_finish = TRUE;
    pt_page_data->h_menu_current_focus = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    //INT32   i4_ret = MENUR_OK;

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    //INT32   i4_ret = MENUR_OK;

    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /* stop animation */
    menu_page_animation_stop();

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    //INT32   i4_ret = MENUR_OK;

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_pic_mode_edit_init(VOID)
{
    t_g_menu_page_pic_mode_edit.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_pic_mode_edit.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_pic_mode_edit.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_pic_mode_edit.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_pic_mode_edit.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_pic_mode_edit.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_pic_mode_edit.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

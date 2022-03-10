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
 * $RCSfile: menu_page_simple_dialog.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
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

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_ui.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_device/menu_device.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_dbg.h"
#include "menu2/menu_common/menu_common_simple_dialog.h"


#define SPECIAL_DIALOG_TITLE_LEN  (APP_CFG_CUSTOM_INP_NAME_LEN + 256 +1)
#define SPECIAL_DIALOG_MOBILE_DEV_LEN   64
//extern BOOL   b_is_press_ok_from_check_update;

#ifdef COMMON_SIMPLE_DIALOG_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_simple_dialog;
static BOOL          b_g_dlg_page_show = FALSE;
static UINT32        ui4_g_page_crnt_page;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

static menu_common_page_simple_dialog_yes_fct    pf_dialog_do_yes_fct = NULL;
static menu_common_page_simple_dialog_no_fct     pf_dialog_do_no_fct = NULL;
static menu_common_page_simple_dialog_info_fct     pf_dialog_do_info_fct = NULL;

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
extern INT16 menu_get_gui_lang_idx(VOID);
extern UINT32 ui4_page_menu_language_dialog;
extern UINT16 ui2_menu_language_new_idx;
#endif

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _special_dialog_title
 *
 * Description:  The title may not be  MLM words. Maybe customized
              This function will be extended.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _special_dialog_txt(UINT32 ui4_page_id,HANDLE_T h_simple_dialog, UTF16_T*  pw2s_text)
{
    UTF16_T     w2s_text[SPECIAL_DIALOG_TITLE_LEN] = {0} ;
    UTF16_T     w2s_star_txt[APP_CFG_CUSTOM_INP_NAME_LEN +1] = {0};    /* input text value: UTF16_T */
    CHAR        s_buf[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    INT16       i2_cust_pic_mode = 0;
    INT32       i4_ret = MENUR_OK;

    if(ui4_page_id == ui4_g_menu_custom_page_delete_pic_mode)
    {
        c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));


        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                        &i2_cust_pic_mode);
        MENU_LOG_ON_FAIL(i4_ret);

        if (i2_cust_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
        {
            return ;
        }
        a_cfg_cust_get_cust_pic_mode_name(i2_cust_pic_mode,s_buf,APP_CFG_CUSTOM_INP_NAME_LEN);

        c_uc_ps_to_w2s (s_buf, w2s_star_txt, APP_CFG_CUSTOM_INP_NAME_LEN);

        if((c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1)) + 1) >= SPECIAL_DIALOG_TITLE_LEN)
        {
            DBG_LOG_PRINT(("\n===mlm words exceed=======\n"));
            return;
        }
        else
        {
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1)) ;
            c_uc_w2s_strcat(w2s_text, L" ");
        }
        if(((c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1))) +
            (c_uc_w2s_strlen (w2s_star_txt)) + 1)>= SPECIAL_DIALOG_TITLE_LEN)
        {
            DBG_LOG_PRINT(("\n===mlm words exceed=======\n"));
            return;
        }
        else
        {
            c_uc_w2s_strcat (w2s_text, w2s_star_txt);
            c_uc_w2s_strcat(w2s_text, L" ");
        }
        if(((c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE1))) +
            (c_uc_w2s_strlen (w2s_star_txt)) +
            (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE2))) + 2) >= SPECIAL_DIALOG_TITLE_LEN)
        {
            DBG_LOG_PRINT(("\n===mlm words exceed=======\n"));
            return;
        }
        else
        {
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_DELETE_PIC_MODE_TITLE2));
        }
        c_uc_w2s_strcat (w2s_text, L" \0") ;
    }
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
        else if (ui4_page_id == ui4_page_chg_country_code_dialog)
        {
            UINT16              ui2_country_code;
            UTF16_T             *apw2s_help_info[ACFG_COUNTRY_CODE_LAST_ENTRY] =
                                {
                                    MENU_TEXT(MLM_MENU_KEY_USA_COUNTRY_CODE_HELP_INFO),
                                    MENU_TEXT(MLM_MENU_KEY_MEX_COUNTRY_CODE_HELP_INFO),
                                    MENU_TEXT(MLM_MENU_KEY_CAN_COUNTRY_CODE_HELP_INFO)
                                };

            menu_custom_page_get_tmp_country_code(&ui2_country_code);

            i4_ret = a_ui_simple_dialog_set_text(h_simple_dialog, apw2s_help_info[ui2_country_code]);
            MENU_LOG_ON_FAIL(i4_ret);

            return;
        }
#endif
#endif
#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
        else if (ui4_page_id == ui4_page_menu_language_dialog)
        {
            UINT16              ui2_menu_language;
            UTF16_T             *apw2s_language_help_info[ACFG_COUNTRY_CODE_LAST_ENTRY] =
                                {
                                    MENU_TEXT(MLM_MENU_KEY_ENG_MENU_LANGUAGE_HELP_INFO),
                                    MENU_TEXT(MLM_MENU_KEY_SPA_MENU_LANGUAGE_HELP_INFO),
                                    MENU_TEXT(MLM_MENU_KEY_FRE_MENU_LANGUAGE_HELP_INFO)
                                };

            //menu_custom_page_get_tmp_country_code(&ui2_menu_language);
            ui2_menu_language = ui2_menu_language_new_idx;

            i4_ret = a_ui_simple_dialog_set_text(h_simple_dialog, apw2s_language_help_info[ui2_menu_language]);
            MENU_LOG_ON_FAIL(i4_ret);

            return;
        }
#endif
        else if (ui4_page_id == ui4_mobile_device_delete_dialog_page_id)
        {
            UTF16_T w2s_mobile_device_name[SPECIAL_DIALOG_MOBILE_DEV_LEN] = {0};

            i4_ret = mobile_device_get_mobile_dev_name(w2s_mobile_device_name);
            MENU_LOG_ON_FAIL(i4_ret);

            if((c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_REMOVE_MOBILE_DEVICE_DIALOG))
                + c_uc_w2s_strlen(w2s_mobile_device_name) + 3) >= SPECIAL_DIALOG_TITLE_LEN)
            {
                DBG_LOG_PRINT(("\n===mlm words exceed=======\n"));
                return;
            }
            else
            {
                c_uc_w2s_strncpy(w2s_text, MENU_TEXT(MLM_MENU_KEY_REMOVE_MOBILE_DEVICE_DIALOG), c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_REMOVE_MOBILE_DEVICE_DIALOG)));
                c_uc_w2s_strcat(w2s_text, w2s_mobile_device_name);
                c_uc_w2s_strcat(w2s_text, L"?");
                c_uc_w2s_strcat(w2s_text, L"\0");
                a_ui_simple_dialog_set_text(h_simple_dialog, w2s_text);
                return;
            }
        }

    a_ui_simple_dialog_set_text(h_simple_dialog, w2s_text);
}
/*----------------------------------------------------------------------------
 * Name: _common_dialog_do_yes
 *
 * Description:   Wrapper for "YES callback" to UI Simple Dialog
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _common_dialog_do_yes(VOID)
{       /* Do the original pf_yes */

    if(pf_dialog_do_yes_fct != NULL)
    {
        pf_dialog_do_yes_fct();
    }


    if (ui4_g_page_crnt_page == ui4_g_page_service_rst_dialog)
    {
        DBG_LOG_PRINT(("%s(%d) \n", __FILE__, __LINE__ ));
        return;
    }

    /* Let the menu show */
     menu_main_set_visibility(TRUE);
     menu_nav_back();
     UINT8 ui1_value = SCREEN_REFRESH_START_CANCEL;
     a_cfg_cust_get_oled_panel_refresh_value(&ui1_value);
     if(ui4_g_page_crnt_page == ui4_page_oled_screen_1 &&
        SCREEN_REFRESH_START_AT_POWER_OFF == ui1_value)
     {
         MENU_LOG_ON_FAIL(menu_set_page_hide(FALSE));
         menu_nav_go(ui4_page_oled_screen_2,NULL);
     }
}
/*----------------------------------------------------------------------------
 * Name: _common_dialog_do_no
 *
 * Description:   Wrapper for "NO callback" to UI Simple Dialog
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _common_dialog_do_no(VOID)
{
    /* Do the original pf_no */

    if(pf_dialog_do_no_fct != NULL)
    {
      pf_dialog_do_no_fct();
    }

    /* Let the menu show */
     menu_main_set_visibility(TRUE);
     menu_nav_back();
}


/*----------------------------------------------------------------------------
 * Name: _common_dialog_do_no
 *
 * Description:   Wrapper for "NO callback" to UI Simple Dialog
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _common_dialog_do_info(VOID)
{
    /* Do the original pf_no */

    if(pf_dialog_do_info_fct != NULL)
    {
        pf_dialog_do_info_fct();
    }

    /* Let the menu show */
     menu_main_set_visibility(TRUE);
     menu_nav_back();
}

/*----------------------------------------------------------------------------
 * Name: _ui_simple_dialog_wdgt_proc_fct
 *
 * Description:   Main widget process function of the simple dialog.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static INT32 _ui_simple_dialog_wdgt_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
            {
                UINT32 ui4_keycode = (UINT32)pv_param1;
                switch (ui4_keycode)
                {
                    case BTN_RETURN:
                        /* Let the menu show */
                        menu_main_set_visibility(TRUE);
                        menu_nav_back();
                        return WMPR_DONE;
                    default:
                        break;
                }
            }
        default:
            break;
    }
   return a_ui_simple_dialog_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/


static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32                              i4_ret              = MENUR_FAIL;
    HANDLE_T                           h_frm_root;
    MENU_COMMON_SIMPLE_DIALOG_INIT_T*  pt_menu_dialog_init = (MENU_COMMON_SIMPLE_DIALOG_INIT_T*)pv_create_data;
    MENU_COMMON_SIMPLE_DIALOG_T*       pt_dialog;
    UI_SIMPLE_DIALOG_INIT_T            t_simple_dialog_init;

    pt_dialog = (MENU_COMMON_SIMPLE_DIALOG_T *) c_mem_alloc(sizeof(MENU_COMMON_SIMPLE_DIALOG_T));

    do
    {
        if(pt_dialog == NULL)
        {
           i4_ret = MENUR_OUT_OF_MEMORY;
           break;
        }

        i4_ret = menu_pm_get_root_frm(&h_frm_root);
        MENU_CHK_FAIL(i4_ret);

        c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        /* Initial the UI Simple Dialog */
        t_simple_dialog_init.e_style                        = pt_menu_dialog_init->e_style;
        t_simple_dialog_init.h_parent                       = h_frm_root;
        t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _common_dialog_do_no;
        t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _common_dialog_do_yes;
        t_simple_dialog_init.pf_wdgt_proc                   = _ui_simple_dialog_wdgt_proc_fct;
        t_simple_dialog_init.pf_ui_simple_dialog_tts_cb_fct = a_ui_simple_dialog_default_tts_cb_fct;
        t_simple_dialog_init.pt_begin_offset                = NULL;
        t_simple_dialog_init.ui2_txt_align_type             = pt_menu_dialog_init->ui2_text_alignment;
        t_simple_dialog_init.b_default_answer               = FALSE;
        t_simple_dialog_init.b_info_icon                    = pt_menu_dialog_init->b_info_icon;
        t_simple_dialog_init.b_three_btn_mode               = pt_menu_dialog_init->b_three_btn_mode;
        t_simple_dialog_init.b_one_btn_mode                 = pt_menu_dialog_init->b_one_btn_mode;
        if(t_simple_dialog_init.b_three_btn_mode)
        {
            t_simple_dialog_init.pf_ui_simple_dialog_info_cb_fct = _common_dialog_do_info;
        }
        //Fix Coverity ID : 1392249 Unchecked return value
        i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                  &pt_dialog->h_simple_dialog);
        MENU_CHK_FAIL(i4_ret);

        /* The main dialog structure */
        pt_dialog->ui2_msg_yes         = pt_menu_dialog_init->ui2_msg_yes;
        pt_dialog->ui2_msg_no          = pt_menu_dialog_init->ui2_msg_no;
        pt_dialog->ui2_msg_txt         = pt_menu_dialog_init->ui2_msg_txt;
        pt_dialog->pf_yes              = pt_menu_dialog_init->pf_yes;
        pt_dialog->pf_no               = pt_menu_dialog_init->pf_no;
        pt_dialog->b_default_answer    = pt_menu_dialog_init->b_default_answer;
        pt_dialog->e_default_answer_ex = pt_menu_dialog_init->e_default_answer_ex;

        if(pt_menu_dialog_init->b_three_btn_mode)
        {
            pt_dialog->pf_info            = pt_menu_dialog_init->pf_info;
            pt_dialog->ui2_msg_info       = pt_menu_dialog_init->ui2_msg_info;
            pt_dialog->b_three_btn_mode   = pt_menu_dialog_init->b_three_btn_mode;
        }
        /* Attach the main dialog structure to this page */
        menu_page_set_data(ui4_page_id, pt_dialog);

        i4_ret = MENUR_OK;
    } while(0);

    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i32Rtn;

    MENU_COMMON_SIMPLE_DIALOG_T* pt_dialog;
    //Fix Coverity ID : 1143134 Unchecked return value
    if (menu_page_get_data(ui4_page_id, (VOID *)&pt_dialog) != MENUR_OK)
    {
        DBG_LOG_PRINT(("[MENU] On page show fail"));
    }

    /* Set all correct attributes to the dialog */
    if(ui4_page_id == ui4_g_menu_custom_page_delete_pic_mode
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
       || ui4_page_id == ui4_page_chg_country_code_dialog
#endif
#endif
#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
       || ui4_page_id == ui4_page_menu_language_dialog
#endif
        || ui4_page_id == ui4_mobile_device_delete_dialog_page_id)
    {
        _special_dialog_txt(ui4_page_id,
                              pt_dialog->h_simple_dialog,
                              MENU_TEXT(pt_dialog->ui2_msg_txt));
    }
    else
    {
        a_ui_simple_dialog_set_text(pt_dialog->h_simple_dialog,
                                    MENU_TEXT(pt_dialog->ui2_msg_txt));
    }

    //FIx Coverity ID:4490863 Unchecked return value
    i32Rtn = a_ui_simple_dialog_set_yes_text(pt_dialog->h_simple_dialog,
                                    MENU_TEXT(pt_dialog->ui2_msg_yes));
    if( i32Rtn != APP_UIR_OK )
    {
        DBG_LOG_PRINT(("[MENU]{%s,%d} Error: i32Rtn:%d \n", __func__, __LINE__, i32Rtn ));
    }

    // Fix coverity-4515469: Unchecked return value
    i32Rtn = a_ui_simple_dialog_set_no_text(pt_dialog->h_simple_dialog,
                                          MENU_TEXT(pt_dialog->ui2_msg_no));
    if( i32Rtn != APP_UIR_OK )
    {
        DBG_LOG_PRINT(("[MENU]{%s,%d} Error: i32Rtn:%d \n", __func__, __LINE__, i32Rtn ));
    }



    if(pt_dialog->b_three_btn_mode)
    {
         a_ui_simple_dialog_set_info_text(pt_dialog->h_simple_dialog,
                                MENU_TEXT(pt_dialog->ui2_msg_info));
    }
    if(pt_dialog->b_default_answer)
    {
        a_ui_simple_dialog_set_answer_ex(pt_dialog->h_simple_dialog,
                                        (pt_dialog->e_default_answer_ex ?
                                         pt_dialog->e_default_answer_ex : UI_SIMPLE_DIALOG_ANSWER_YES));
    }
    else
    {
        a_ui_simple_dialog_set_answer_ex(pt_dialog->h_simple_dialog,
                                        (pt_dialog->e_default_answer_ex ?
                                         pt_dialog->e_default_answer_ex : UI_SIMPLE_DIALOG_ANSWER_NO));
    }
    /* The callbacks should be set in the global value */
    pf_dialog_do_yes_fct  = pt_dialog->pf_yes;
    pf_dialog_do_no_fct   = pt_dialog->pf_no;
    pf_dialog_do_info_fct = pt_dialog->pf_info;

#ifndef  APP_MENU_DLG_COEXIST
    /* Hide the main menu */
    menu_main_set_visibility(FALSE);
#endif
    /* Show the dialog */
    c_wgl_float(pt_dialog->h_simple_dialog, TRUE, FALSE);

    a_ui_simple_dialog_show(pt_dialog->h_simple_dialog);

    b_g_dlg_page_show = TRUE;
    ui4_g_page_crnt_page = ui4_page_id;
    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{   MENU_COMMON_SIMPLE_DIALOG_T* pt_dialog;
    //Fix Coverity ID : 1143133 Unchecked return value
    if (menu_page_get_data(ui4_page_id, (VOID *)&pt_dialog) != MENUR_OK)
    {
        DBG_LOG_PRINT(("[MENU] On page hide fail"));
    }

        /* Hide the dialog */
    c_wgl_float(pt_dialog->h_simple_dialog, FALSE, FALSE);
    a_ui_simple_dialog_hide(pt_dialog->h_simple_dialog);

    c_wgl_set_visibility(pt_dialog->h_simple_dialog,WGL_SW_HIDE_RECURSIVE);
    c_wgl_repaint(pt_dialog->h_simple_dialog,NULL,TRUE);
    /* Let the menu show */
    menu_main_set_visibility(TRUE);

    b_g_dlg_page_show = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    MENU_COMMON_SIMPLE_DIALOG_T* pt_dialog;
    //Fix Coverity ID : 1143132 UNchecked return value
    if (menu_page_get_data(ui4_page_id, (VOID *)&pt_dialog) != MENUR_OK)
    {
        DBG_LOG_PRINT(("[MENU] On page get focus fail"));
    }

    a_ui_simple_dialog_set_focus(pt_dialog->h_simple_dialog, TRUE);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

BOOL menu_simple_dialog_page_is_show(VOID)
{
    return b_g_dlg_page_show;
}

extern INT32 menu_common_page_simple_dialog_create(
    UINT16                                     ui2_msg_txt,        /* Messages in the text dialog */
    UINT16                                     ui2_msg_yes,        /* Messages in the [YES] button */
    UINT16                                     ui2_msg_no,         /* Messages in the [NO] button */
    UI_SIMPLE_DIALOG_STYLE_T                   e_style,            /* Dialog Style */
    UINT16                                     ui2_text_alignment, /* Dialog Text Alignment */
    BOOL                                       b_default_answer,   /* Default Answer */
    menu_common_page_simple_dialog_yes_fct     pf_yes,             /* Press Yes to run */
    menu_common_page_simple_dialog_no_fct      pf_no,              /* Press No to run */
    UINT32* pui4_page_id                                           /* Return the page id */
)

{
    MENU_COMMON_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;

    c_memset(&t_simple_dialog_init, 0, sizeof(MENU_COMMON_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.ui2_msg_txt        = ui2_msg_txt;
    t_simple_dialog_init.ui2_msg_yes        = ui2_msg_yes;
    t_simple_dialog_init.ui2_msg_no         = ui2_msg_no;
    t_simple_dialog_init.e_style            = e_style;
    t_simple_dialog_init.ui2_text_alignment = ui2_text_alignment;
    t_simple_dialog_init.b_default_answer   = b_default_answer;
    t_simple_dialog_init.pf_yes             = pf_yes;
    t_simple_dialog_init.pf_no              = pf_no;
    t_simple_dialog_init.b_info_icon        = FALSE;

    if (MLM_MENU_KEY_SERVICE_CHECK_HELP_INFO == ui2_msg_txt||
        MLM_MENU_KEY_RESET_CONFIRM_FAC_SETTINGS == ui2_msg_txt)
    {
        t_simple_dialog_init.b_info_icon = TRUE;
    }

    return menu_pm_page_create(&t_g_menu_common_page_simple_dialog,
                               (VOID*)&t_simple_dialog_init,
                               pui4_page_id);

}


INT32 menu_common_page_simple_dialog_create_ex(
    UINT16                                     ui2_msg_txt,        /* Messages in the text dialog */
    UINT16                                     ui2_msg_yes,        /* Messages in the [YES] button */
    UINT16                                     ui2_msg_no,         /* Messages in the [NO] button */
    UINT16                                     ui2_msg_info,       /* Messages in the [Info] button */
    UI_SIMPLE_DIALOG_STYLE_T                   e_style,            /* Dialog Style */
    UINT16                                     ui2_text_alignment, /* Dialog Text Alignment */
    UI_SIMPLE_DIALOG_ANSWER                    e_default_answer,   /* Default Answer */
    menu_common_page_simple_dialog_yes_fct     pf_yes,             /* Press Yes to run */
    menu_common_page_simple_dialog_no_fct      pf_no,              /* Press No to run */
    menu_common_page_simple_dialog_info_fct    pf_info,            /* Press Info to run */
    UINT32* pui4_page_id                                           /* Return the page id */
)

{
    MENU_COMMON_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;

    c_memset(&t_simple_dialog_init, 0, sizeof(MENU_COMMON_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.ui2_msg_txt         = ui2_msg_txt;
    t_simple_dialog_init.ui2_msg_yes         = ui2_msg_yes;
    t_simple_dialog_init.ui2_msg_no          = ui2_msg_no;
    t_simple_dialog_init.ui2_msg_info        = ui2_msg_info;
    t_simple_dialog_init.e_style             = e_style;
    t_simple_dialog_init.ui2_text_alignment  = ui2_text_alignment;
    t_simple_dialog_init.e_default_answer_ex = e_default_answer;
    t_simple_dialog_init.pf_yes              = pf_yes;
    t_simple_dialog_init.pf_no               = pf_no;
    t_simple_dialog_init.pf_info             = pf_info;
    t_simple_dialog_init.b_info_icon         = FALSE;
    if(pf_info)
    {
        t_simple_dialog_init.b_three_btn_mode = TRUE;
    }
    else if(NULL == pf_no)
    {
        t_simple_dialog_init.b_one_btn_mode = TRUE;
    }

    return menu_pm_page_create(&t_g_menu_common_page_simple_dialog,
                               (VOID*)&t_simple_dialog_init,
                               pui4_page_id);

}


INT32 menu_common_page_simple_dialog_init(VOID)
{

    t_g_menu_common_page_simple_dialog.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_simple_dialog.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_simple_dialog.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_simple_dialog.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_simple_dialog.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_simple_dialog.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_simple_dialog.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_SIMPLE_DIALOG_ENABLE */


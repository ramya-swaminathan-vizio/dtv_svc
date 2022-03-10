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
 * $RCSfile: menu_page_nw_pwd.c,v $
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
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "u_sb_atsc_eng.h"

#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "menu2/menu_dbg.h"
#include "c_wgl.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "wdk/a_digit_pad.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define CHG_PWD_ALARM_DELAY     2000
#define CHG_PWD_SUCCESS_DELAY   5000

#define CHG_PWD_STAT_NPWD       0
#define CHG_PWD_STAT_CPWD       1
#define CHG_PWD_STAT_NUM        2


#define CHG_PWD_SUGGEST_W       MENU_ITEM_V_WIDE
#define CHG_PWD_SUGGEST_H       (MENU_ITEM_V_HEIGHT*3)

#define CHG_PWD_SUGGEST_X       FRAME_LEFT_RIGHT_INTV

#define CHG_PWD_SUGGEST_Y       0

#define CHG_PWD_TXT_NPWD_W      MENU_ITEM_V_WIDE
#define CHG_PWD_TXT_NPWD_H      MENU_ITEM_V_HEIGHT

#define CHG_PWD_TXT_NPWD_X       FRAME_LEFT_RIGHT_INTV

#define CHG_PWD_TXT_NPWD_Y      CHG_PWD_SUGGEST_H

#define CHG_PWD_TXT_CPWD_W      MENU_ITEM_V_WIDE
#define CHG_PWD_TXT_CPWD_H      MENU_ITEM_V_HEIGHT

#define CHG_PWD_TXT_CPWD_X       FRAME_LEFT_RIGHT_INTV


#define CHG_PWD_TXT_CPWD_Y      (CHG_PWD_TXT_NPWD_Y+CHG_PWD_TXT_NPWD_H)

#define CHG_PWD_TXT_ALARM_W     MENU_ITEM_V_WIDE
#define CHG_PWD_TXT_ALARM_H     (MENU_ITEM_V_HEIGHT*2)
#define CHG_PWD_TXT_ALARM_X     0
#define CHG_PWD_TXT_ALARM_Y     (CHG_PWD_TXT_CPWD_Y+CHG_PWD_TXT_CPWD_H + 100)


#define CHG_PWD_BTN_CNL_H       MENU_ITEM_V_HEIGHT

#define CHG_PWD_BTN_CNL_X       FRAME_LEFT_RIGHT_INTV
#define CHG_PWD_BTN_CNL_W       252


#define CHG_PWD_BTN_CNL_Y       (CHG_PWD_TXT_ALARM_Y+CHG_PWD_TXT_ALARM_H)

#define CHG_PWD_BTN_SAVE_W       252
#define CHG_PWD_BTN_SAVE_H       MENU_ITEM_V_HEIGHT
#define CHG_PWD_BTN_SAVE_X       (CHG_PWD_BTN_CNL_X+CHG_PWD_BTN_CNL_W+10)
#define CHG_PWD_BTN_SAVE_Y       CHG_PWD_BTN_CNL_Y





/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum{

  BUTTON_1 = 0,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTON_LAST_ENTRY
} PWD_BUTTON_T;

typedef struct _LOCK_PIC_MODE
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_eb_pwd;
    HANDLE_T     h_guide_text1;
    HANDLE_T     h_guide_text2;
    HANDLE_T     h_error_msg_invalid;
    HANDLE_T     h_pwd_back_button;
    HANDLE_T     h_pwd_back_img;
    HANDLE_T     h_save_button;
    HANDLE_T     h_pwd_button[BUTTON_LAST_ENTRY];
    HANDLE_T     h_cfm_pwd_button[BUTTON_LAST_ENTRY];
    HANDLE_T     h_digit_handle;//new add
    HANDLE_T     h_guide_text3;
    HANDLE_T     h_cancel_button;
    HANDLE_T     h_warning_dlg;
    BOOL         b_warning_dlg_show;
    BOOL         b_this_page_show;
    BOOL         b_delay;
    BOOL         b_entered[BUTTON_LAST_ENTRY];
    BOOL         b_pwd_pass;
    HANDLE_T     h_error_msg;
}LOCK_PIC_MODE;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T     t_g_menu_page_lock_pic_mode;
static BOOL             b_delay_lock_cust_pic_mode_over = FALSE;

//
MENU_PAGE_FCT_TBL_T     t_g_menu_common_page_chg_pwd;
static UINT8            ui1_pwd_stat = CHG_PWD_STAT_NPWD;
static HANDLE_T         h_cnt_frm;
static HANDLE_T         ah_btn_npwd[BUTTON_LAST_ENTRY] = {NULL_HANDLE};
static HANDLE_T         ah_btn_cpwd[BUTTON_LAST_ENTRY] = {NULL_HANDLE};
static HANDLE_T         h_txt_npwd;
static HANDLE_T         h_txt_cpwd;


static HANDLE_T         h_cancle_bt;
static HANDLE_T         h_save_bt;
static CHAR             ac_pwd[CHG_PWD_STAT_NUM][BUTTON_LAST_ENTRY+1] = {{0}};
static UTF16_T          w2s_pwd[5] = {0};

static PWD_BUTTON_T     e_current_button = BUTTON_1;

static HANDLE_T         h_digit_obscure_timer;
static UINT32           ui4_digit_obscure_timeout;
static HANDLE_T         h_digit_handle;
static BOOL             b1_save_state = FALSE;
static HANDLE_T         h_image_no_match;
static HANDLE_T         h_txt_mtip;

extern int a_set_is_pin_confirmed(BOOL b_confirm);
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _page_reset(VOID);
//static INT32 _set_alarm_txt(UINT16 ui2_mlm_idx);

static INT32 _button_set_title(UINT8 ui1_pwd_stat,
                               PWD_BUTTON_T e_button,
                               UTF16_T *pw2s_txt);

static INT32 _button_update_info();
static INT32 _button_update_ui(BOOL b_repaint);

static INT32 _comfirm_error_passwd(VOID);
static INT32 _comfirm_correct_passwd(VOID);

static INT32 _save_error_passwd(VOID);
static INT32 _save_correct_passwd(VOID);

static BOOL _check_new_pwd(VOID);


static INT32 _focus_to_next_pwd_btn(VOID);
static INT32 _focus_to_npwd_btn(PWD_BUTTON_T e_index);
static INT32 _focus_to_cpwd_btn(PWD_BUTTON_T e_index);
static INT32 _focus_to_cancle_btn(VOID);
static INT32 _focus_to_save_btn(VOID);
static INT32 _digit_pad_create( UINT32 ui4_page_id,VOID*  pv_create_data);
static INT32 _update_pin_match_success_ui(VOID);
static INT32 _update_pin_match_error_ui(VOID);
static INT32 _input_no_match_image_create(HANDLE_T h_parent, HANDLE_T* ph_widget);

static INT32 _focus_to_cancle_btn(VOID)
{
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_focus(h_cancle_bt, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
static INT32 _focus_to_save_btn(VOID)
{
    INT32 i4_ret = MENUR_OK;

    if( BUTTON_4 != e_current_button || ui1_pwd_stat != CHG_PWD_STAT_CPWD )
    {
        return MENUR_INV_STATE;
    }
    b1_save_state = TRUE;

    i4_ret = c_wgl_set_focus(h_save_bt, FALSE);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _focus_to_npwd_btn(PWD_BUTTON_T e_index)
{
    INT32 i4_ret = MENUR_OK;
    if(e_index < BUTTON_1 || e_index > BUTTON_4)
    {
        return MENUR_INV_ARG;
    }
    e_current_button = e_index;
    ui1_pwd_stat = CHG_PWD_STAT_NPWD;

//    i4_ret = c_wgl_set_focus(ah_btn_npwd[e_index], WGL_SYNC_AUTO_REPAINT);
//    MENU_CHK_FAIL(i4_ret);

    i4_ret = _button_update_info();
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_0),
    c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_0)));
#endif

    return i4_ret;
}
static INT32 _focus_to_cpwd_btn(PWD_BUTTON_T e_index)
{
    INT32 i4_ret = MENUR_OK;
    if(e_index < BUTTON_1 || e_index > BUTTON_4)
    {
        return MENUR_INV_ARG;
    }

    e_current_button = e_index;
    ui1_pwd_stat = CHG_PWD_STAT_CPWD;

//    i4_ret = c_wgl_set_focus(ah_btn_cpwd[e_index], WGL_SYNC_AUTO_REPAINT);
//    MENU_CHK_FAIL(i4_ret);

    i4_ret = _button_update_info();
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_1),
    c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_1)));
#endif
    return i4_ret;
}
static INT32 _focus_to_back_pwd_btn(VOID)
{
    INT32 i4_ret = MENUR_OK;
    HANDLE_T    *ph_btn = NULL;

    if(e_current_button < BUTTON_2 || e_current_button > BUTTON_4)
    {
        return MENUR_INV_STATE;
    }
    if (e_current_button == BUTTON_4 &&  b1_save_state == TRUE)
    {
        b1_save_state =FALSE;
        e_current_button = BUTTON_LAST_ENTRY;
    }

    switch(ui1_pwd_stat)
    {
    case CHG_PWD_STAT_NPWD:
         {
                ph_btn = ah_btn_npwd;
                break;
         }
    case CHG_PWD_STAT_CPWD:
         {
                ph_btn = ah_btn_cpwd;
                break;
         }
    default:
         return MENUR_INV_STATE;
    }


    e_current_button --;

    /*set new current button*/
//    i4_ret = c_wgl_set_focus(ph_btn[e_current_button],WGL_NO_AUTO_REPAINT);
//    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _button_update_info();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_repaint();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_mtip,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
static INT32 _focus_to_next_pwd_btn(VOID)
{
    INT32 i4_ret = MENUR_OK;
    HANDLE_T    *ph_btn = NULL;

    if(e_current_button < BUTTON_1 || e_current_button > BUTTON_3)
    {
        return MENUR_INV_STATE;
    }

    switch(ui1_pwd_stat)
    {
    case CHG_PWD_STAT_NPWD:
         {
                ph_btn = ah_btn_npwd;
                break;
         }
    case CHG_PWD_STAT_CPWD:
         {
                ph_btn = ah_btn_cpwd;
                break;
         }
    default:
         return MENUR_INV_STATE;
    }

    /*change next  to current */
    e_current_button++;

    /*set new current button*/
//    i4_ret = c_wgl_set_focus(ph_btn[e_current_button],WGL_NO_AUTO_REPAINT);
//    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _button_update_info();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_repaint();
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _focus_to_pwd_btn(VOID)
{
    INT32 i4_ret = MENUR_OK;

    if(e_current_button < BUTTON_1 || e_current_button > BUTTON_4)
    {
        return MENUR_INV_STATE;
    }

    switch(ui1_pwd_stat)
    {
    case CHG_PWD_STAT_NPWD:
         {
                i4_ret = _focus_to_npwd_btn(e_current_button);
                MENU_CHK_FAIL(i4_ret);
                break;
         }
    case CHG_PWD_STAT_CPWD:
         {
                i4_ret =  _focus_to_cpwd_btn(e_current_button);
                MENU_CHK_FAIL(i4_ret);
                break;
         }
    default:
         return MENUR_INV_STATE;
    }

    i4_ret = c_wgl_enable(h_save_bt, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _button_update_info();
    MENU_CHK_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE_DIGIT));

    return i4_ret;
}

static INT32 _comfirm_correct_passwd(VOID)
{
    INT32 i4_ret = MENUR_OK;

    /*update save btn*/
    i4_ret = c_wgl_enable(h_save_bt, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _focus_to_save_btn();
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _comfirm_error_passwd(VOID)
{
    return _save_error_passwd();
}

static INT32 _save_error_passwd(VOID)
{
    INT32 i4_ret = MENUR_OK;
    /* show the alarm info */
    do{
        //"0000" is not be admitted.
        if (c_strncmp(ac_pwd[0],ACFG_PASSWORD_DEF,4) == 0)
        {
//            _set_alarm_txt(MLM_MENU_KEY_NET_INVALID_PIN);

#ifdef APP_TTS_SUPPORT
            a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_NET_INVALID_PIN),
                            c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_NET_INVALID_PIN)));
#endif
            break;
        }
        else
        {
//            _set_alarm_txt(MLM_MENU_KEY_CHG_PWD_FAIL_MSG);

#ifdef APP_TTS_SUPPORT
            a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_FAIL_MSG),
                            c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_FAIL_MSG)));
#endif
            break;
        }
    }while(1);

    c_wgl_repaint(h_cnt_frm, NULL, TRUE);

    /* wait for a while */
    c_thread_delay(CHG_PWD_ALARM_DELAY);

    _page_reset();
    return i4_ret;
}

extern VOID a_set_5351_pin_state(UINT32 ui4_pin_state);
static INT32 _save_correct_passwd(VOID)
{
    INT32 i4_ret = MENUR_OK;

    /* Set the password */
     a_cfg_set_password(w2s_pwd);

    ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} call a_set_is_pin_confirmed(TRUE) \n", __FUNCTION__, __LINE__  )););
    a_set_is_pin_confirmed(TRUE);

     t_g_menu_common.b_cfg_dirty = TRUE;
     a_set_5351_pin_state(0);

     ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} call a_cfg_custom_set_sys_pin_passed(FALSE) \n", __FUNCTION__, __LINE__  )););
     a_cfg_custom_set_sys_pin_passed(FALSE);

     set_delay_lock_cust_pic_mode_status(TRUE);

     a_cfg_cust_set_cust_pic_mode_lock_status(TRUE);

     c_wgl_repaint(h_cnt_frm, NULL, TRUE);
#ifdef APP_TTS_SUPPORT
     a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_SUCCESS_MSG),
                     c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CHG_PWD_SUCCESS_MSG)));
#endif

     /* delay to waiting for completion of repainting editbox. */
     c_thread_delay(CHG_PWD_SUCCESS_DELAY);

     menu_nav_back();
     menu_pm_refresh();

     return MENUR_OK;
}

static INT32 _button_update_ui(BOOL b_repaint)
{
    INT32 i4_ret = MENUR_OK;

    /*update focus*/
    if(e_current_button < BUTTON_1 || e_current_button > BUTTON_4)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = _button_update_info();
    MENU_CHK_FAIL(i4_ret);

    /*update change*/
    if( ui1_pwd_stat == CHG_PWD_STAT_CPWD && e_current_button == BUTTON_1 )
    {
        i4_ret = _focus_to_npwd_btn(BUTTON_4);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if( ui1_pwd_stat == CHG_PWD_STAT_NPWD && e_current_button == BUTTON_4 )
    {
        c_wgl_do_cmd(ah_btn_npwd[BUTTON_3],
                    WGL_CMD_BTN_SET_PUSHED,
                    WGL_PACK(TRUE),
                    NULL);
        _button_set_title(CHG_PWD_STAT_NPWD, BUTTON_3, L"");

        c_wgl_do_cmd(ah_btn_npwd[BUTTON_4],
                    WGL_CMD_BTN_SET_PUSHED,
                    WGL_PACK(TRUE),
                    NULL);
        _button_set_title(CHG_PWD_STAT_NPWD, BUTTON_4, L"");
        i4_ret = _focus_to_cpwd_btn(BUTTON_1);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if( ui1_pwd_stat == CHG_PWD_STAT_CPWD && e_current_button == BUTTON_4 )
    {
        c_wgl_do_cmd(ah_btn_cpwd[BUTTON_3],
                     WGL_CMD_BTN_SET_PUSHED,
                     WGL_PACK(TRUE),
                     NULL);
        _button_set_title(CHG_PWD_STAT_CPWD, BUTTON_3, L"");

        c_wgl_do_cmd(ah_btn_cpwd[BUTTON_4],
                    WGL_CMD_BTN_SET_PUSHED,
                    WGL_PACK(TRUE),
                    NULL);
        _button_set_title(CHG_PWD_STAT_CPWD, BUTTON_4, L"");
        if ( _check_new_pwd() == TRUE )
        {
            /*chg to save*/ //ui1_pwd_stat = CHG_PWD_STAT_CPWD;
            i4_ret = _comfirm_correct_passwd();
            MENU_CHK_FAIL(i4_ret);
        }
        else
        {
            i4_ret =  _comfirm_error_passwd();
            MENU_CHK_FAIL(i4_ret);
        }

    }
    else
    {
        i4_ret = _focus_to_pwd_btn();
        MENU_CHK_FAIL(i4_ret);
    }


    if(b_repaint == TRUE)
    {
        menu_pm_repaint();
    }
    return i4_ret;
}


static VOID _digit_obscure(
                        VOID*                       pv_tag,
                        VOID*                       pv_tag2,
                        VOID*                       pv_tag3
                        )
{
    INT32 i4_ret;
    HANDLE_T    *ph_btn = NULL;

    if (CHG_PWD_STAT_NPWD == ui1_pwd_stat)
    {
        ph_btn = ah_btn_npwd;
    }
    else if (CHG_PWD_STAT_CPWD == ui1_pwd_stat)
    {
        ph_btn = ah_btn_cpwd;
    }
    else
    {
        DBG_LOG_PRINT(("[LockPicMode] Error: {%s %d} Invalid ui1_pwd_stat=%d\n",__FUNCTION__, __LINE__, ui1_pwd_stat));
        return;
    }

    // Fix coverity-4836645: Out-of-bounds read
    if( (e_current_button == 0) || (e_current_button > BUTTON_LAST_ENTRY))
    {
        DBG_LOG_PRINT(("[LockPicMode] Error: {%s %d} Invalid e_current_button=%d\n",__FUNCTION__, __LINE__, e_current_button));
        //DBG_LOG_PRINT(("[LockPicMode] %s %d ph_btn[e_current_button-1]=0x%X\n", __FUNCTION__,__LINE__, ph_btn[e_current_button - 1]));
        return;
    }

    c_wgl_do_cmd(ph_btn[e_current_button - 1],
                WGL_CMD_BTN_SET_PUSHED,
                WGL_PACK(TRUE),
                NULL);
    //_button_set_title(ui1_pwd_stat, e_current_button - 1, L"");
    i4_ret = c_wgl_repaint(h_cnt_frm, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return;
}
static VOID _digit_obscure_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    menu_request_context_switch(_digit_obscure, NULL, NULL, NULL);
}

static VOID _digit_obscure_timer_restart()
{
    INT32 i4_ret;

    /* Stop indicate icon hide timer. */
    i4_ret = c_timer_stop (h_digit_obscure_timer);
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("Stop zoom indicate::c_timer_stop failed!"));
    }

    if (e_current_button == BUTTON_1)
    {
        return;
    }
    /* Start indicate icon hide timer. */
    i4_ret = c_timer_start (h_digit_obscure_timer,
                            ui4_digit_obscure_timeout,
                            X_TIMER_FLAG_ONCE,
                            _digit_obscure_timer_nfy,
                            NULL);
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL (DBG_MOD_NAVIGATOR, ("Start zoom indicate::c_timer_start failed!"));
    }
}

static INT32 _adjust_shadow(GL_RECT_T *pt_rect)
{
    INT32 i4_ret = MENUR_OK;
    HANDLE_T h_last_shadow_item = NULL_HANDLE;

    /*Adjust last shadow position*/
    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret=c_wgl_move(h_last_shadow_item, pt_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:

            MENU_CHK_FAIL(a_digit_pad_focus(h_digit_handle));

            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE_DIGIT));
            break;

        case BTN_CURSOR_UP:
            MENU_CHK_FAIL (menu_set_focus_on_homebar(TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));

           break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT :
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_UP :
            if (CHG_PWD_STAT_NPWD == ui1_pwd_stat)
                {c_wgl_set_focus(ah_btn_npwd[e_current_button], WGL_SYNC_AUTO_REPAINT);}
            else
                {c_wgl_set_focus(ah_btn_cpwd[e_current_button], WGL_SYNC_AUTO_REPAINT);}
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE_DIGIT));
            break ;

        case BTN_CURSOR_DOWN :
            MENU_CHK_FAIL(menu_set_focus_on_backbar (TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));

#ifdef APP_TTS_SUPPORT
            a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG,MLM_MENU_KEY_HELP_BACK),
                            c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG,MLM_MENU_KEY_HELP_BACK)));
#endif
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _button_set_title(UINT8 ui1_pwd_stat,
                               PWD_BUTTON_T e_button,
                               UTF16_T *pw2s_txt)
{
    HANDLE_T    h_btn = NULL_HANDLE;

    if (CHG_PWD_STAT_NPWD == ui1_pwd_stat)
    {
        h_btn = ah_btn_npwd[e_button];
    }
    else if (CHG_PWD_STAT_CPWD == ui1_pwd_stat)
    {
        h_btn = ah_btn_cpwd[e_button];
    }
    else
    {
        return MENUR_INV_ARG;
    }

    if (NULL == pw2s_txt)
    {
        pw2s_txt = L"";
    }
    c_wgl_do_cmd(h_btn,
                 WGL_CMD_BTN_SET_TEXT,
                 WGL_PACK(pw2s_txt),
                 WGL_PACK(c_uc_w2s_strlen(pw2s_txt)));
    return WGLR_OK;

}

static INT32 _button_store_info(UINT8 ui1_input)
{
    if(ui1_input > 9)
    {
        return MENUR_INV_ARG;
    }

    ac_pwd[ui1_pwd_stat][e_current_button] = ui1_input+'0';

    return MENUR_OK;
}

static INT32 _button_update_info()
{
    HANDLE_T    *ph_btn = NULL;
    UTF16_T     w2s_ch[2] = {0};
    CHAR        s_txt[2] = {0};
    INT8        i1_i;
    INT8        i_current_index = e_current_button;

    _digit_obscure_timer_restart();

    if (CHG_PWD_STAT_NPWD == ui1_pwd_stat)
    {
        ph_btn = ah_btn_npwd;
    }
    else if (CHG_PWD_STAT_CPWD == ui1_pwd_stat)
    {
        ph_btn = ah_btn_cpwd;
    }
    else
    {
        DBG_LOG_PRINT(("[LockPicMode] Error: {%s %d} Invalid ui1_pwd_stat=%d\n",__FUNCTION__, __LINE__, ui1_pwd_stat));
        return MENUR_FAIL;
    }

    /*--------------------------
        | ...  |   -2  | -1  |     0        |  ...      |
        |  *  |    *   |  X  |  current   | NULL   |
        ---------------------------*/

    for(i1_i = 0 ; i1_i < BUTTON_LAST_ENTRY; i1_i++)
    {
        if(i_current_index - i1_i >= 2 )
        {
            c_wgl_do_cmd(ph_btn[i1_i],
            WGL_CMD_BTN_SET_PUSHED,
            WGL_PACK(TRUE),
            NULL);
            c_wgl_enable(ph_btn[i1_i], FALSE);
            _button_set_title(ui1_pwd_stat, e_current_button-2, L"");
            continue;
        }
        else if (i_current_index - i1_i == 1 )
        {
            s_txt[0] = ac_pwd[ui1_pwd_stat][i1_i];
            s_txt[1] = 0;

            c_uc_ps_to_w2s(s_txt, w2s_ch, 1);

            c_wgl_do_cmd(ph_btn[i1_i],
                         WGL_CMD_BTN_SET_PUSHED,
                         WGL_PACK(FALSE),
                         NULL);
             c_wgl_enable(ph_btn[i1_i], FALSE);
            _button_set_title(ui1_pwd_stat, i1_i, w2s_ch);
            continue;
        }
        else if ( i_current_index - i1_i <= 0)
        {
             c_wgl_do_cmd(ph_btn[i1_i],
                         WGL_CMD_BTN_SET_PUSHED,
                         WGL_PACK(FALSE),
                         NULL);
              if(i1_i == i_current_index)
              {
                  c_wgl_enable(ph_btn[i1_i], TRUE);
                  if(ph_btn==ah_btn_npwd)
                  {
                      c_wgl_enable(ah_btn_cpwd[BUTTON_1], FALSE);
                  }
              }
              else
              {
                  c_wgl_enable(ph_btn[i1_i], FALSE);
              }
             _button_set_title(ui1_pwd_stat, e_current_button, L"");
             continue;
        }
        else
        {
            MENU_CHK_FAIL(MENUR_FAIL);
        }
    }

    return MENUR_OK;
}


static BOOL _check_new_pwd(VOID)
{
    BOOL b_ret = FALSE;
    INT32   i4_ret = 0;
    UTF16_T w2s_str[5] = {0};

    if (c_strncmp(ac_pwd[0], ac_pwd[1], 4) == 0)
    {
        c_uc_ps_to_w2s(ac_pwd[1],w2s_str,4);
        w2s_str[4] = 0;

#ifdef ACFG_USE_UNIVERSAL_PASSWORD
        if (acfg_custom_chk_universal_password(w2s_str,&b_ret)== 0
                 && b_ret) /*clear user pwd to "0000"*/
        {

            _update_pin_match_success_ui();
            b_ret = TRUE;
            c_uc_ps_to_w2s(ACFG_PASSWORD_DEF, w2s_pwd, 4);
        }
        else
#endif
        if (c_strncmp(ac_pwd[0],ACFG_PASSWORD_DEF,4) != 0)  /*confirm pin need match new pin, and not allow set to "0000"*/
        {

            _update_pin_match_success_ui();
            b_ret = TRUE;
            c_uc_ps_to_w2s(&ac_pwd[1][0], w2s_pwd, 4);
        }
        else
        {

            i4_ret = c_wgl_do_cmd(h_txt_mtip,
                                  WGL_CMD_BTN_SET_TEXT,
                                  WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_INVALID_PIN)),
                                  WGL_PACK(0xFF));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(h_txt_mtip,
                                          WGL_SW_RECURSIVE);
            MENU_CHK_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(h_image_no_match,
            							   WGL_SW_RECURSIVE);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(h_image_no_match, NULL, TRUE);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(h_txt_mtip, NULL, TRUE);
            MENU_CHK_FAIL(i4_ret);

            b_ret = FALSE;

        }
    }
    else
    {
        _update_pin_match_error_ui();
        b_ret = FALSE;
    }

    return b_ret;
}


static INT32 _pwd_btn_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2
                    )
{
    INT32       i4_ret = MENUR_OK;
    UINT32         ui4_keycode = (UINT32)param1;
    HANDLE_T    h_backbar = NULL_HANDLE;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        case WGL_MSG_LOSE_FOCUS:
        {
            break;
        }
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch(ui4_keycode)
            {
                case BTN_KB_BACKSPACE:
                case BTN_CURSOR_LEFT:
                {
                    if(e_current_button == BUTTON_1 )
                    {
                        /*end of btn need to change focus*/
                        i4_ret = _button_update_ui(TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = _focus_to_back_pwd_btn();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    break;
                }
                case BTN_SELECT:
                    return MENUR_OK;
                case BTN_RETURN:
                    menu_nav_back();
                    return MENUR_OK;
                case BTN_DIGIT_0:
                case BTN_DIGIT_1:
                case BTN_DIGIT_2:
                case BTN_DIGIT_3:
                case BTN_DIGIT_4:
                case BTN_DIGIT_5:
                case BTN_DIGIT_6:
                case BTN_DIGIT_7:
                case BTN_DIGIT_8:
                case BTN_DIGIT_9:
                case BTN_KB_0:
                case BTN_KB_1:
                case BTN_KB_2:
                case BTN_KB_3:
                case BTN_KB_4:
                case BTN_KB_5:
                case BTN_KB_6:
                case BTN_KB_7:
                case BTN_KB_8:
                case BTN_KB_9:
                {
                    if(e_current_button < BUTTON_1 || e_current_button > BUTTON_4 )
                    {
                        /*error*/
                        break;
                    }

                    /* update info */
                    _button_store_info(ui4_keycode - BTN_DIGIT_0);

                    /* update ui */
                    if(e_current_button == BUTTON_4 )
                    {
                        /*end of btn need to change focus*/
                        i4_ret = _button_update_ui(TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = _focus_to_next_pwd_btn();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    break;
                }
                case BTN_CURSOR_DOWN:
                {

                    i4_ret = a_digit_pad_focus(h_digit_handle);
                    MENU_LOG_ON_FAIL(i4_ret);


                    break;
                }
                case BTN_CURSOR_UP:
                {
                    menu_get_backbar_handle(&h_backbar);

                    i4_ret = c_wgl_set_focus(h_backbar,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));

#ifdef APP_TTS_SUPPORT
                a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG,MLM_MENU_KEY_HELP_BACK),
                                c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG,MLM_MENU_KEY_HELP_BACK)));
#endif
                    menu_pm_repaint();
                }
                    return MENUR_OK;

                default :
                    break;
            }
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _btn_create(
                            HANDLE_T    h_parent,
                            INT32       i4_index,
                            UINT32      ui4_style,
                            wgl_widget_proc_fct pf_wdgt_proc,
                            HANDLE_T*   ph_widget)
{

    INT32               i4_ret = 0;
    UINT8               ui1_i = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;

    HANDLE_T            h_tmp_btn = NULL_HANDLE;

    ui4_style = WGL_STL_BTN_CHECKBOX;

    for (ui1_i = BUTTON_1; ui1_i < BUTTON_LAST_ENTRY; ui1_i++)
    {
        if (i4_index == 0)
        {
            SET_RECT_BY_SIZE(&t_rect,
                             (CHG_PWD_TXT_NPWD_X + 144 + ui1_i*58),
                             (CHG_PWD_TXT_NPWD_Y -150 + 60),
                             53,
                             53);
        }
        else
        {
            SET_RECT_BY_SIZE(&t_rect,
                             (CHG_PWD_TXT_CPWD_X + 144 + ui1_i*58),
                             (CHG_PWD_TXT_NPWD_Y -55 + 60),
                             53,
                             53);
        }

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_BUTTON,
                                     WGL_CONTENT_BUTTON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &ph_widget[ui1_i]);
        if (i4_ret < 0)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }

        h_tmp_btn = ph_widget[ui1_i];

        /* Set Image */
        t_img_info.e_type = WGL_IMG_SET_EXTEND;
        t_img_info.u_img_data.t_extend.t_disable     = h_g_menu_system_pin_box_inactive_v2;
        t_img_info.u_img_data.t_extend.t_enable  = h_g_menu_system_pin_box_active_v2;
        t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_system_pin_box_highlight_v2;
        t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_system_pin_box_highlight_v2;
        t_img_info.u_img_data.t_extend.t_push = h_g_menu_system_pin_box_pushed_v2;
        t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_system_pin_box_pushed_v2;

        i4_ret = c_wgl_do_cmd(h_tmp_btn,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        MENU_LOG_ON_FAIL(i4_ret);

        _button_set_title(i4_index, ui1_i, L"");

        c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
        t_inset.i4_left     = 10;
        t_inset.i4_right    = 2;
        t_inset.i4_top      = 0;
        t_inset.i4_bottom   = 0;
        i4_ret = c_wgl_do_cmd(h_tmp_btn,
                              WGL_CMD_BTN_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        if(ui1_i == BUTTON_1)
        {
            c_wgl_enable(h_tmp_btn, TRUE);
        }
        else
        {
            c_wgl_enable(h_tmp_btn, FALSE);
        }

        /* Set Alignment */
        i4_ret = c_wgl_do_cmd(h_tmp_btn,
                              WGL_CMD_BTN_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
        t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
        t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (h_tmp_btn,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set txt color */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
        i4_ret = c_wgl_do_cmd(h_tmp_btn,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));

        i4_ret = c_wgl_float(h_tmp_btn, TRUE, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

    }

return MENUR_OK;
}

static INT32 _text_create(
                            HANDLE_T    h_parent,
                            INT32       i4_index,
                            UINT32      ui4_style,
                            wgl_widget_proc_fct pf_wdgt_proc,
                            HANDLE_T*   ph_widget)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     (i4_index == 0 ? CHG_PWD_TXT_NPWD_X+215 : CHG_PWD_TXT_NPWD_X+200) ,
                     (i4_index == 0 ? CHG_PWD_TXT_NPWD_Y-150 : CHG_PWD_TXT_NPWD_Y-55),
                     CHG_PWD_TXT_NPWD_W,
                     CHG_PWD_TXT_NPWD_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 10;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _text_error_create(
                            HANDLE_T    h_parent,
                            UINT32      ui4_style,
                            wgl_widget_proc_fct pf_wdgt_proc,
                            HANDLE_T*   ph_widget)

{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     FRAME_W/3 + 35,
                 	 CHG_PWD_TXT_NPWD_Y/4 - 50,
                     CHG_PWD_TXT_NPWD_W,
                     CHG_PWD_TXT_NPWD_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 10;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


static INT32 _cancle_btn_proc(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2
                    )
{
    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
#ifdef APP_TTS_SUPPORT
            a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CNCL),
                                c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_CNCL)));
#endif
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_CHANGE_PWD_CANCEL));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            INT32       i4_ret;
            UINT32      ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
            case BTN_CURSOR_UP:
            {

                i4_ret = a_digit_pad_focus(h_digit_handle);
                MENU_LOG_ON_FAIL(i4_ret);

                break;
            }
            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_help_tip_keytip_set_focus(h_cancle_bt, 2, FALSE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_pm_repaint();
                break;
            }
            case BTN_CURSOR_RIGHT:
            {
                i4_ret = _focus_to_save_btn();
                MENU_LOG_ON_FAIL(i4_ret);
                menu_pm_repaint();
                break;
            }
            case BTN_SELECT:
                _page_reset();
                menu_nav_back();
                //c_wgl_repaint(h_cnt_frm, NULL, TRUE);
                return WMPR_DONE;
            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            default:
                break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _save_btn_proc(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2
                    )
{
    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
#ifdef APP_TTS_SUPPORT
            a_app_tts_play(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_GAMMA_SAVE),
                                c_uc_w2s_strlen(MLM_MENU_TEXT(MLM_MENU_LANG_ENG, MLM_MENU_KEY_GAMMA_SAVE)));
#endif
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE_DIGIT));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            INT32       i4_ret;
            UINT32      ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
            case BTN_CURSOR_UP:
            {

                MENU_CHK_FAIL(a_digit_pad_focus(h_digit_handle));
                menu_pm_repaint();

                break;
            }
            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_help_tip_keytip_set_focus(h_save_bt, 2, FALSE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_pm_repaint();
                break;
            }
            case BTN_CURSOR_LEFT:
            {
                i4_ret = c_wgl_set_focus(h_cancle_bt, FALSE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_pm_repaint();
                break;
            }
            case BTN_SELECT:
            {
                if (_check_new_pwd())
                {
                    i4_ret = _save_correct_passwd();
                    MENU_LOG_ON_FAIL(i4_ret);
                    return i4_ret;
                }
                else
                {
                    i4_ret = _save_error_passwd();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                menu_pm_repaint();
                return WMPR_DONE;
            }
            case BTN_PREV_PRG:
            case BTN_RETURN:
                _page_reset();
                menu_nav_back();
                return WMPR_DONE;
            default:
                break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _cancle_btn_create(HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    return MENUR_OK;
}

static INT32 _save_cancle_btn_create(HANDLE_T* ph_widget, GL_RECT_T *pt_rec, wgl_widget_proc_fct pf_proc)
{
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    if (pt_rec != NULL)
    {
        c_memcpy((VOID*)&t_rect, (VOID*)pt_rec, sizeof(GL_RECT_T));
    }

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 10;
    t_inset.i4_right    = 2;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_button_save_cancel_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_button_save_cancel_highlight;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_button_save_cancel_v2;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#if 0
static INT32 _set_suggest_txt(VOID)
{
    INT32       i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt_desc,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHANGE_PIN_DESC)),
                        WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}

static INT32 _set_alarm_txt(UINT16 ui2_mlm_idx)
{
    INT32       i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt_alarm,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(MENU_TEXT(ui2_mlm_idx)),
                        WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}

static INT32 _txt_suggest_create(HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     CHG_PWD_SUGGEST_X,
                     CHG_PWD_SUGGEST_Y,
                     CHG_PWD_SUGGEST_W,
                     CHG_PWD_SUGGEST_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE|WGL_STL_GL_NO_BK |WGL_STL_GL_NO_IMG_UI),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    WGL_INSET_T t_inset = {
        MENU_ITEM_V_CNT_INSET_L,
        MENU_ITEM_V_CNT_INSET_R,
        0,
        0};

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_TOP,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_txt_alarm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_txt_alarm(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    UINT32          ui4_style;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI
                | WGL_STL_TEXT_MAX_128
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     CHG_PWD_TXT_ALARM_X,
                     CHG_PWD_TXT_ALARM_Y,
                     CHG_PWD_TXT_ALARM_W,
                     CHG_PWD_TXT_ALARM_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = CHG_PWD_ALARM_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_alarm_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_alarm_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_alarm_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_alarm_bk;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_alarm_bk;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_alarm_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _chg_lang
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _chg_lang()
{
    INT32   i4_ret = 0;
#if 0
    /* Suggest */
    _set_suggest_txt();
#endif
    /* Titles */
    i4_ret = c_wgl_do_cmd(h_txt_npwd,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHG_PWD_0)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt_cpwd,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHG_PWD_1)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt_mtip,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHG_PWD_1)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    /* Alarm */
    i4_ret = c_wgl_do_cmd(h_txt_alarm,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHG_PWD_ALARM)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    /* Save BTN */
    i4_ret = c_wgl_do_cmd(h_save_bt,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SYS_PIN_SAVE)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Cancle BTN */
    i4_ret = c_wgl_do_cmd(h_cancle_bt,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CNCL)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}

static INT32 _page_reset(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UINT8   ui1_i;
    UTF16_T w2w_str[128] = {0};

    e_current_button = BUTTON_1;
    ui1_pwd_stat = CHG_PWD_STAT_NPWD;

    c_memset(ac_pwd, 0, sizeof(ac_pwd));
    c_memset(w2s_pwd, 0, sizeof(w2s_pwd));

    for (ui1_i = 0; ui1_i < BUTTON_LAST_ENTRY; ui1_i++)
    {
        _button_set_title(CHG_PWD_STAT_NPWD, ui1_i, L"");
        i4_ret = c_wgl_do_cmd(ah_btn_npwd[ui1_i],
                                WGL_CMD_BTN_SET_PUSHED,
                                WGL_PACK(FALSE),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        if(ui1_i == BUTTON_1)
        {
            c_wgl_enable(ah_btn_npwd[ui1_i], TRUE);
        }
        else
        {
            c_wgl_enable(ah_btn_npwd[ui1_i], FALSE);
        }
        c_wgl_enable(ah_btn_cpwd[ui1_i], FALSE);
        
        i4_ret = c_wgl_float(ah_btn_npwd[ui1_i], TRUE, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        _button_set_title(CHG_PWD_STAT_CPWD, ui1_i, L"");
        i4_ret = c_wgl_do_cmd(ah_btn_cpwd[ui1_i],
                                WGL_CMD_BTN_SET_PUSHED,
                                WGL_PACK(FALSE),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_float(ah_btn_cpwd[ui1_i], TRUE, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifdef APP_TTS_SUPPORT
    c_memset(w2w_str, 0, sizeof(w2w_str));

    c_uc_w2s_strcpy(w2w_str, MENU_TTS_TEXT(MLM_MENU_KEY_CHANGE_PIN_DESC));
    c_uc_w2s_strcat(w2w_str, L".");
    c_uc_w2s_strcat(w2w_str, MENU_TTS_TEXT(MLM_MENU_KEY_CHG_PWD_0));

    a_app_tts_play(w2w_str, c_uc_w2s_strlen(w2w_str));
#endif

    //i4_ret = c_wgl_enable(h_save_bt, FALSE);
    //MENU_LOG_ON_FAIL(i4_ret);

    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE_DIGIT));

    c_wgl_set_visibility(h_image_no_match,WGL_SW_HIDE);
    i4_ret = c_wgl_set_visibility(h_txt_mtip,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}







/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect = {0};

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    /*PIN dont macth*/
    i4_ret =  _input_no_match_image_create(h_cnt_frm,&h_image_no_match);
    MENU_CHK_FAIL(i4_ret);

    /*PIN dont macth msg*/
    i4_ret = _text_error_create(h_cnt_frm,
                                TRUE,
                                NULL,
                                &h_txt_mtip);
	MENU_CHK_FAIL(i4_ret);


    /* New pwd text */
    i4_ret = _text_create(h_cnt_frm,
                          0,
                          TRUE,
                          NULL,
                          &h_txt_npwd);
    MENU_CHK_FAIL(i4_ret);

    /* Confirm pwd text */
    i4_ret = _text_create(h_cnt_frm,
                          1,
                          TRUE,
                          NULL,
                          &h_txt_cpwd);
    MENU_CHK_FAIL(i4_ret);

    /* password buttons */
    i4_ret = _btn_create(h_cnt_frm,
                          0,
                          TRUE,
                          _pwd_btn_proc_fct,
                          ah_btn_npwd);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _btn_create(h_cnt_frm,
                          1,
                          TRUE,
                          _pwd_btn_proc_fct,
                          ah_btn_cpwd);
    MENU_CHK_FAIL(i4_ret);

    i4_ret =  _digit_pad_create(h_cnt_frm,pv_create_data);
    MENU_CHK_FAIL(i4_ret);

    /* cancle button */
    i4_ret = _cancle_btn_create(h_cnt_frm, &h_cancle_bt);
    MENU_CHK_FAIL(i4_ret);

    /* create the indicate hide timer */
    ui4_digit_obscure_timeout = 5000;
    i4_ret = c_timer_create (&h_digit_obscure_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR(("<MENU> button digit_obscure_timer create failed.\r\n"));
    }

    SET_RECT_BY_SIZE(&t_rect,
                     CHG_PWD_BTN_CNL_X,
                     CHG_PWD_BTN_CNL_Y,
                     CHG_PWD_BTN_CNL_W,
                     CHG_PWD_BTN_CNL_H);
    _save_cancle_btn_create(&h_cancle_bt, &t_rect, _cancle_btn_proc);

    SET_RECT_BY_SIZE(&t_rect,
                     CHG_PWD_BTN_SAVE_X,
                     CHG_PWD_BTN_SAVE_Y,
                     CHG_PWD_BTN_SAVE_W,
                     CHG_PWD_BTN_SAVE_H);
    _save_cancle_btn_create(&h_save_bt,   &t_rect, _save_btn_proc);

    i4_ret = _chg_lang();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i4_ret = MENUR_OK;

    c_wgl_set_visibility(h_cnt_frm, WGL_SW_RECURSIVE);

    i4_ret = _chg_lang();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _page_reset();
    MENU_LOG_ON_FAIL(i4_ret);

    a_digit_pad_focus(h_digit_handle);

    menu_main_set_title(MLM_MENU_KEY_CHG_PWD);

    return MENUR_OK;
}


static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    menu_help_tip_keytip_show(TRUE);
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    GL_RECT_T t_rect= {0};

    menu_set_backbar_proc(_backbar_proc_fct);

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    t_rect.i4_left      = CONTENT_X;
    t_rect.i4_right     = CONTENT_X + CONTENT_W;
    t_rect.i4_top       = CHG_PWD_BTN_CNL_Y + 3*CHG_PWD_BTN_CNL_H - 10;
    t_rect.i4_bottom    = t_rect.i4_top + HELP_TIP_FRAME_H;

    _adjust_shadow(&t_rect);

    menu_set_and_trigger_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE_DIGIT));

    return MENUR_OK;
}


static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /* stop animation */
    menu_page_animation_stop();
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
 #ifdef NEVER
    INT32 i4_ret;

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret = _chg_lang(ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif /* NEVER */
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_lock_new_pic_mode_init(VOID)
{
    t_g_menu_page_lock_pic_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_lock_pic_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_lock_pic_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_lock_pic_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_lock_pic_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_lock_pic_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_lock_pic_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

static VOID _digit_pad_key_event_nfy(DIGIT_PAD_EVENT_TYPE event_type, VOID* pv_param)
{
    INT32           i4_ret;
    CHAR            digit_val ;
    UINT32          ui4_keycode;

    DBG_LOG_PRINT(("[PWD]  %s %d event_type = %d\n",__FUNCTION__,__LINE__, event_type));


    switch(event_type)
    {
        case DIGIT_PAD_DIGIT_KEY:
            digit_val = *((CHAR*)pv_param);
            if (digit_val == '0' || digit_val == '1' || digit_val == '2' ||
                digit_val == '3' || digit_val == '4' || digit_val == '5' ||
                digit_val == '6' || digit_val == '7' || digit_val == '8' ||
                digit_val == '9' )
            {
                a_digit_pad_focus_btn_ok(h_digit_handle);

                ui4_keycode = BTN_DIGIT_0 + (UINT32)(digit_val - '0');

                if(e_current_button < BUTTON_1 || e_current_button > BUTTON_4 )
                {
                    /*error*/
                    break;
                }

                /* update info */
                _button_store_info(ui4_keycode - BTN_DIGIT_0);

                /* update ui */
                if(e_current_button == BUTTON_4 )
                {
                    /*end of btn need to change focus*/
                    i4_ret = _button_update_ui(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = _focus_to_next_pwd_btn();
                    MENU_LOG_ON_FAIL(i4_ret);
                }

            }
            break;

        case DIGIT_PAD_DEL_KEY:
            {
                if(e_current_button == BUTTON_1 )
                {
                    /*end of btn need to change focus*/
                    i4_ret = _button_update_ui(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = _focus_to_back_pwd_btn();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            break;
        case DIGIT_PAD_BUTTON_OK:
            break;
        case DIGIT_PAD_BUTTON_CANCEL:
            break;
        case DIGIT_PAD_NAV_BACK:
            break;
        case DIGIT_PAD_FOCUS_TO_ABOVE_WGL:
            menu_set_focus_on_backbar(TRUE);
            break;
        case DIGIT_PAD_FOCUS_TO_BELOW_WGL:
            i4_ret = _focus_to_cancle_btn();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        default:
            break;
    }
}



static BOOL _digit_pad_recv_key_handle(UINT32 ui4_msg,
                                          VOID* pv_param1,
                                          VOID* pv_param2)
{
    INT32       i4_ret = MENUR_OK;
    UINT32      ui4_keycode = (UINT32)pv_param1;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        case WGL_MSG_LOSE_FOCUS:
        {
            break;
        }
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch(ui4_keycode)
            {
                case BTN_KB_BACKSPACE:
                case BTN_CURSOR_LEFT:
                case BTN_SELECT:
                    return MENUR_OK;
                case BTN_RETURN:
                    menu_nav_back();
                    return MENUR_OK;
                case BTN_DIGIT_0:
                case BTN_DIGIT_1:
                case BTN_DIGIT_2:
                case BTN_DIGIT_3:
                case BTN_DIGIT_4:
                case BTN_DIGIT_5:
                case BTN_DIGIT_6:
                case BTN_DIGIT_7:
                case BTN_DIGIT_8:
                case BTN_DIGIT_9:
                case BTN_KB_0:
                case BTN_KB_1:
                case BTN_KB_2:
                case BTN_KB_3:
                case BTN_KB_4:
                case BTN_KB_5:
                case BTN_KB_6:
                case BTN_KB_7:
                case BTN_KB_8:
                case BTN_KB_9:
                {
                    if(e_current_button < BUTTON_1 || e_current_button > BUTTON_4 )
                    {
                        /*error*/
                        break;
                    }

                    /* update info */
                    _button_store_info(ui4_keycode - BTN_DIGIT_0);

                    /* update ui */
                    if(e_current_button == BUTTON_4 )
                    {
                        /*end of btn need to change focus*/
                        i4_ret = _button_update_ui(TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = _focus_to_next_pwd_btn();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    break;
                }

                default :
                    break;
            }
        }
    default:
        break;
    }
    return MENUR_OK;
}


static INT32 _digit_pad_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{

    DIGIT_PAD_CONFIG cfg;
    a_digit_pad_init_config(&cfg);
    cfg.parent_frame = ui4_page_id;
    cfg.position.ui4_left = CHG_PWD_TXT_NPWD_X+150;
    cfg.position.ui4_top  = CHG_PWD_TXT_NPWD_Y + 90 ;

    cfg.digit_key_event_nfy         = _digit_pad_key_event_nfy;
    cfg.pf_rc_event_default_handle  = _digit_pad_recv_key_handle;
    a_digit_pad_create(cfg, &h_digit_handle);

    return MENUR_OK;
}

extern BOOL get_delay_lock_cust_pic_mode_status(VOID)
{
    return b_delay_lock_cust_pic_mode_over;
}

extern VOID set_delay_lock_cust_pic_mode_status(BOOL b_status)
{
    b_delay_lock_cust_pic_mode_over = b_status;
}

static INT32 _update_pin_match_success_ui(VOID)
{
    INT32   i4_ret = 0;
    i4_ret = c_wgl_do_cmd(h_txt_mtip,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHG_PWD_SUCCESS_MSG)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_mtip,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_txt_mtip, NULL, TRUE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _update_pin_match_error_ui(VOID)
{
    INT32   i4_ret = 0;

    i4_ret = c_wgl_do_cmd(h_txt_mtip,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CHG_PWD_FAIL_MSG)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_mtip,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_image_no_match,
    							   WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_image_no_match, NULL, TRUE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_txt_mtip, NULL, TRUE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


static INT32 _input_no_match_image_create(HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    INT32 i4_ret = WDKR_OK;
    GL_RECT_T t_rect;
    WGL_IMG_INFO_T t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                 FRAME_W/4,
                 CHG_PWD_TXT_NPWD_Y/4 - 50,
                 CHG_PWD_TXT_NPWD_W ,
                 CHG_PWD_TXT_NPWD_H );

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                    HT_WGL_WIDGET_ICON,
                                    WGL_CONTENT_ICON_DEF,
                                    WGL_BORDER_NULL,
                                    & t_rect,
                                    NULL,
                                    255,
                                    (VOID*)(0),
                                    0,
                                    ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_pin_no_match_bkg;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_pin_no_match_bkg;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_pin_no_match_bkg;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));

	i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return  i4_ret;
}


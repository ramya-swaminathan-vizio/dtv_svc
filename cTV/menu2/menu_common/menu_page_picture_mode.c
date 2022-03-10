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
 * $RCSfile: menu_page_inp_lst.c,v $
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

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/menu_dbg.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_page.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define PICTURE_MODE_VISIBLE_ELEM                 (10)
#define PICTURE_MODE_LST_X                        (0 * GRID_W)
#define PICTURE_MODE_LST_Y                        (0 * GRID_H)
#define PICTURE_MODE_LST_W                        (CONTENT_W)
#define PICTURE_MODE_LST_H                        (PICTURE_MODE_VISIBLE_ELEM * GRID_H)
#define MAX_REC                                   16
#define PIC_MODE_NAME_MAX_LEN                     APP_CFG_CUSTOM_RENAME_PIC_MODE_NAME_LEN

#define PIC_MODE_ARROW_WIDTH    (30)
#define PIC_MODE_ARROW_HEIGHT   (10)
#define PIC_MODE_SEP_HEIGHT     (10)
#define PIC_MODE_TOP_GAP        (33)
#define PRESET_PIC_MODE_TXT_LEN (64)


typedef struct _PICTURE_MODE_T
{
    UINT32                          ui4_page_id;
    HANDLE_T                        h_cnt_frm;
    HANDLE_T                        h_pic_mode_lb;
    HANDLE_T                        h_img_down;
    HANDLE_T                        h_img_up;
    HANDLE_T                        h_img_sep_up;
    HANDLE_T                        h_img_sep_down;
    UINT32                          ui4_sel_pic_mode_idx;
    UINT16                          ui2_pic_mode_num;
}PICTURE_MODE_T;



MENU_PAGE_FCT_TBL_T  t_g_menu_page_pic_mode;
static HANDLE_T      h_pic_mode;
static BOOL          b_from_backbar = FALSE;


static  PICTURE_MODE_T    t_pic_mode_page_data;

static VOID _set_vid_pic_mode_idx(UINT16 ui2_idx);
static UINT16 _get_vid_pic_mode_idx(VOID);

static VOID _get_vid_pic_mode_text(UINT16 ui2_idx, UTF16_T* w2s_str, SIZE_T z_len);



/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
#if 0
static INT32 _pic_mode_update_scrollbar(HANDLE_T h_pic_mode_lb,
                                        PICTURE_MODE_T*   pt_pic_mode_page_data,
                                        BOOL  b_repaint)
{
    INT32   i4_ret = WGLR_OK;
    UINT16  ui2_idx = 0;
    UINT16  ui2_hlt = 0;

    if(NULL == pt_pic_mode_page_data)
    {
        return WGLR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(h_pic_mode_lb,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui2_idx <= PICTURE_MODE_VISIBLE_ELEM)
    {
        i4_ret = c_wgl_set_visibility(pt_pic_mode_page_data->h_img_up, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_pic_mode_page_data->h_img_down, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
        if(b_repaint)
        {
             c_wgl_repaint(pt_pic_mode_page_data->h_cnt_frm, NULL,TRUE );
        }
        return WGLR_OK;
    }

    i4_ret = c_wgl_do_cmd(h_pic_mode_lb,
                          WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                          WGL_PACK(&ui2_hlt),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui2_hlt < PICTURE_MODE_VISIBLE_ELEM)
    {
        i4_ret = c_wgl_set_visibility(pt_pic_mode_page_data->h_img_up, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_pic_mode_page_data->h_img_up, WGL_SW_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if (ui2_hlt < (ui2_idx - (ui2_idx%PICTURE_MODE_VISIBLE_ELEM)))
    {
        i4_ret = c_wgl_set_visibility(pt_pic_mode_page_data->h_img_down, WGL_SW_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_pic_mode_page_data->h_img_down, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if(b_repaint)
    {
        c_wgl_repaint(pt_pic_mode_page_data->h_cnt_frm, NULL,TRUE );
    }
    return i4_ret;
}



/*----------------------------------------------------------------------------
 * Name: menu_text_chg_lang
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
        //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
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
#endif
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
    UINT16            ui2_idx = 0;
    INT32             i4_ret = MENUR_OK;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        menu_pm_repaint();
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
            case BTN_RETURN :
            case BTN_SELECT :
            {
                menu_nav_back();
                break;
            }
            case BTN_CURSOR_DOWN:
            {
                b_from_backbar = TRUE;
                i4_ret = c_wgl_set_focus(h_pic_mode, WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);
                break;
            }
            default :
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}



/*----------------------------------------------------------------------------
 * Name: _picture_mode_proc_fct
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
static INT32 _picture_mode_proc_fct(
    HANDLE_T    h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2)
{
    INT32   i4_ret = 0;
    UINT16  ui2_crnt_ht = 0;
    UINT16  ui2_idx = 0;
    UINT32  ui4_keycode = 0;
    UINT16  ui2_elem_num = 0;

    BOOL    b_is_pic_key_press = FALSE;

    if(WGL_MSG_KEY_UP == ui4_msg)
    {
        if((UINT32)pv_param1 == BTN_P_EFFECT)
        {
            b_is_pic_key_press = TRUE;
            ui4_msg = WGL_MSG_KEY_DOWN;
            pv_param1 = BTN_CURSOR_DOWN;
        }
    }

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (b_from_backbar)
        {
            b_from_backbar = FALSE;

            i4_ret=c_wgl_do_cmd(h_pic_mode,
                       WGL_CMD_LB_HLT_ELEM,
                       WGL_PACK(0),
                       NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            if(_get_vid_pic_mode_idx() >= PICTURE_MODE_VISIBLE_ELEM)
            {
                i4_ret=c_wgl_do_cmd(h_pic_mode,
                               WGL_CMD_LB_HLT_ELEM_VISIBLE,
                               WGL_PACK(_get_vid_pic_mode_idx()),
                               WGL_PACK(PICTURE_MODE_VISIBLE_ELEM-1));
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret=c_wgl_do_cmd(h_pic_mode,
                               WGL_CMD_LB_HLT_ELEM,
                               WGL_PACK(_get_vid_pic_mode_idx()),
                               NULL);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            menu_list_arrow_state_update(h_pic_mode, BTN_INVALID, TRUE);
       } 
       menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_PICTURE_MODE_NO_ENERGY_START));
       menu_pm_repaint();
   }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(h_pic_mode,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(h_pic_mode,
                              WGL_CMD_LB_GET_ELEM_NUM,
                              WGL_PACK(&ui2_elem_num),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        ui4_keycode = (UINT32)pv_param1;
        menu_list_arrow_state_update(h_pic_mode, ui4_keycode, TRUE);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT :
                _set_vid_pic_mode_idx(ui2_crnt_ht);
                i4_ret = c_wgl_set_visibility(h_pic_mode, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_nav_back();
                break;
            case BTN_RETURN:
                i4_ret = c_wgl_set_visibility(h_pic_mode, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_nav_back();
                break;

            case BTN_CURSOR_UP:
                if (ui2_crnt_ht == 0)
                {
                    i4_ret = c_wgl_do_cmd(h_pic_mode,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_set_focus_on_backbar(FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                 }
                 break;
            case BTN_CURSOR_DOWN:
                if(ui2_crnt_ht == (ui2_elem_num -1) && ui2_elem_num > PICTURE_MODE_VISIBLE_ELEM)
                {
                    menu_list_arrow_hide(FALSE);
                    menu_list_down_arrow_show(TRUE, FALSE);
                }
                break;
            default :
                break ;
         }
    }
#ifdef APP_TTS_SUPPORT
        else if (WGL_MSG_PAINT==ui4_msg||WGL_MSG_CREATE==ui4_msg)
        {
            UINT32  ui4_crnt_page;
            UTF16_T w2s_str[PRESET_PIC_MODE_TXT_LEN] = {0};
            static   UTF16_T last_w2s_str[PRESET_PIC_MODE_TXT_LEN] = {0};

            if(WGL_MSG_CREATE==ui4_msg)
            {
                memset(last_w2s_str,0,strlen(last_w2s_str));
            }

            i4_ret = menu_nav_get_crnt_page(&ui4_crnt_page);
            MENU_CHK_FAIL(i4_ret);

            if (ui4_crnt_page == ui4_g_menu_custom_page_pic_mode)
            {
                i4_ret = c_wgl_do_cmd(h_pic_mode,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_crnt_ht),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                _get_vid_pic_mode_text(ui2_crnt_ht, w2s_str, PRESET_PIC_MODE_TXT_LEN);


                if(memcmp(last_w2s_str,w2s_str,sizeof(w2s_str))!=0)
                {
                    memset(last_w2s_str,0,strlen(last_w2s_str));
                    memcpy(last_w2s_str,w2s_str,sizeof(w2s_str));
                    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
                }
            }
        }
#endif

    c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

    if(b_is_pic_key_press)
    {
        i4_ret = c_wgl_do_cmd(h_pic_mode,
                      WGL_CMD_LB_GET_HLT_INDEX,
                      WGL_PACK(&ui2_crnt_ht),
                      NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        _set_vid_pic_mode_idx(ui2_crnt_ht);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_pic_mode_text
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
static VOID _get_vid_pic_mode_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)
{
    extern BOOL b_3d_mode_playing;
    UTF16_T             w2s_asterisk[1] = {0};
    BOOL                b_is_chg = 0;


    //DBG_LOG_PRINT(("[MENU][PIC]{%s,%d} ui2_idx:%d, z_len:%d \n", __FILE__, __LINE__, ui2_idx, z_len ));


    ui2_idx = cvt_list_box_idx_2_acfg_idx(ui2_idx);
    if(b_3d_mode_playing)
    {
        if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+ui2_idx /*MLM_MENU_KEY_X_3D_SETTING_3D*/), z_len-2);
            a_cfg_get_preset_pic_mode_chg_status(ui2_idx,&b_is_chg);
            if(b_is_chg)
            {
                c_uc_ps_to_w2s("*",w2s_asterisk,1);
                c_uc_w2s_strncat(w2s_str,w2s_asterisk,1);
            }
            w2s_str[z_len - 1] = 0;
        }

        else
        {
            CHAR    s_pic_mode_name[MENU_CUST_PIC_MODE_NAME_MAX_LEN+2] = {0};
            BOOL    b_is_exist = FALSE;

            a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx,&b_is_exist);

            if(b_is_exist)
            {
                c_memset(s_pic_mode_name,0,MENU_CUST_PIC_MODE_NAME_MAX_LEN+2);
                c_memset(w2s_str,0,z_len);
                a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }

            else
            {
                c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }
        }
    }
    else
    {
        if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+ui2_idx /*MLM_MENU_KEY_X_3D_SETTING_3D*/), z_len-1);
            a_cfg_get_preset_pic_mode_chg_status(ui2_idx,&b_is_chg);
            if(b_is_chg)
            {
                c_uc_ps_to_w2s("*",w2s_asterisk,1);
                c_uc_w2s_strncat(w2s_str,w2s_asterisk,1);
            }
            w2s_str[z_len - 1] = 0;
        }
        else
        {
            CHAR    s_pic_mode_name[MENU_CUST_PIC_MODE_NAME_MAX_LEN+2] = {0};
            BOOL    b_is_exist = FALSE;

            a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx,&b_is_exist);

            if(b_is_exist)
            {
                c_memset(s_pic_mode_name,0,MENU_CUST_PIC_MODE_NAME_MAX_LEN+2);
                c_memset(w2s_str,0,z_len);
                a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }
            else
            {
                c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }
        }

        //DBG_LOG_PRINT(("[MENU][PIC]{%s,%d} w2s_str: [%s] \n", __FILE__, __LINE__, menu_custom_get_char_string( w2s_str ) ));
    }
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_pic_mode_items_text
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
static INT32 _set_vid_pic_mode_items_text(VOID)
{
    UTF16_T   w2s_str[PRESET_PIC_MODE_TXT_LEN] = {0};
    SIZE_T    z_len = 0;
    UINT16    ui2_idx = 0;
    UINT16    ui2_item_num = 0;
    INT32     i4_ret = MENUR_OK;

    c_memset(w2s_str, 0, sizeof(w2s_str));

    ui2_item_num = get_cust_picture_mode_num();

    for(; ui2_idx < ui2_item_num; ui2_idx++)
    {
        z_len = PRESET_PIC_MODE_TXT_LEN;

        _get_vid_pic_mode_text(ui2_idx,w2s_str,z_len);

        i4_ret = c_wgl_do_cmd(h_pic_mode,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(ui2_idx,0),
                              WGL_PACK(w2s_str));
        MENU_CHK_FAIL(i4_ret);
    }
    return i4_ret;
}



/*----------------------------------------------------------------------------
 * Name: _set_vid_pic_mode_idx
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
static VOID _set_vid_pic_mode_idx(UINT16 ui2_idx)
{
    UINT16      ui2_id = 0;
    INT16       i2_old_val = 0;
    INT16       i2_old_picture_mode_base = 0;
    INT16       i2_picture_mode_base = 0;
    UINT32      ui4_game_mode = (MLM_MENU_KEY_VID_PIC_MODE_ITEM_GAME - (MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1));
    BOOL        b_old_base_game = 0;
    BOOL        b_new_base_game = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_old_val);//eg vivi
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),&i2_old_picture_mode_base);

    ui2_idx = cvt_list_box_idx_2_acfg_idx(ui2_idx);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),(INT16)ui2_idx);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),&i2_picture_mode_base);

    b_old_base_game = i2_old_picture_mode_base  == ui4_game_mode ?   TRUE : FALSE;
    b_new_base_game = i2_picture_mode_base      == ui4_game_mode ?   TRUE : FALSE;
    DBG_LOG_PRINT(("[MENU][PIC][%s %d] \
        new idx = %d,\
        old = %d  \
        b_old_base_game:%d  \
        b_new_base_game:%d  \
        i2_picture_mode_base;%d\n",__FUNCTION__,__LINE__,ui2_idx,i2_old_val,b_old_base_game,b_new_base_game,i2_picture_mode_base));

    a_acfg_update_gaming_logo();
#if 0
    //from cust pic mod witch to other picture mode
    //game pic mode, gll default on
    if(b_old_base_game != b_new_base_game || ui2_idx == ui4_game_mode)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY);
        if( (ui4_game_mode == i2_picture_mode_base) || (ui4_game_mode == ui2_idx))
        {
            a_cfg_av_set(ui2_id, ACFG_CUST_GAME_LOW_LATENCY_ON);
            a_cfg_av_update(ui2_id);
        }
        else
        {
            a_cfg_av_set(ui2_id, ACFG_CUST_GAME_LOW_LATENCY_AUTO);
            a_cfg_av_update(ui2_id);
        }
    }

    if(i2_old_val != ui2_idx)
    {
        set_delay_lock_cust_pic_mode_status(TRUE);
    }
#endif
}



/*----------------------------------------------------------------------------
 * Name: _get_vid_pic_mode_idx
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
static UINT16 _get_vid_pic_mode_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);
    i2_val =(INT16) cvt_acfg_idx_2_list_box_idx((UINT16)i2_val);

    return (UINT16)i2_val;
}



/*----------------------------------------------------------------------------
 * Name: _pic_mode_image_create
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
 #if 0
static INT32 _pic_mode_image_create(HANDLE_T    h_parent,
                             INT32       i4_x,
                             INT32       i4_y,
                             INT32       i4_w,
                             INT32       i4_h,
                             PICTURE_MODE_T*    pt_pic_mode_page_data)
{
    INT32       i4_ret = WGLR_OK;
    GL_RECT_T  t_rect;
    WGL_IMG_INFO_T      t_img_info;
    INT32   i4_img_x = i4_x;
    INT32   i4_img_y = i4_y;
    INT32   i4_img_w = i4_w;
    INT32   i4_img_h = i4_h;

    if (NULL == pt_pic_mode_page_data)
    {
        return WGLR_INV_ARG;
    }


    i4_img_h = PIC_MODE_SEP_HEIGHT;
    /* top text seperator */
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_pic_mode_page_data->h_img_sep_up));
    #if 0
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(t_pic_mode_page_data->h_img_sep_up,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    #endif
    /* bottom text seperator */
    i4_img_x = i4_x;
    i4_img_y = i4_y + PIC_MODE_TOP_GAP + (GRID_H * PICTURE_MODE_VISIBLE_ELEM);
    i4_img_h = PIC_MODE_SEP_HEIGHT;
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_pic_mode_page_data->h_img_sep_down));

    #if 0
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(t_pic_mode_page_data->h_img_sep_down,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    #endif

    i4_img_x = i4_x + (i4_w-PIC_MODE_ARROW_WIDTH)/2;
    i4_img_y = i4_y + 1 ;
    i4_img_w = PIC_MODE_ARROW_WIDTH;
    i4_img_h = PIC_MODE_ARROW_HEIGHT;
    /* bottom arrow up */
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_pic_mode_page_data->h_img_up));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_ch_lst_arrow_up;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_ch_lst_arrow_up;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_ch_lst_arrow_up;
    i4_ret = c_wgl_do_cmd(pt_pic_mode_page_data->h_img_up,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    /* bottom arrow down */
    i4_img_x = i4_x + (i4_w-PIC_MODE_ARROW_WIDTH)/2;
    i4_img_y = i4_y + (GRID_H * PICTURE_MODE_VISIBLE_ELEM)+ PIC_MODE_SEP_HEIGHT;
    i4_img_w = PIC_MODE_ARROW_WIDTH;
    i4_img_h = PIC_MODE_ARROW_HEIGHT;
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_pic_mode_page_data->h_img_down));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_ch_lst_arrow_down;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_ch_lst_arrow_down;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_ch_lst_arrow_down;
    i4_ret = c_wgl_do_cmd(pt_pic_mode_page_data->h_img_down,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    return WGLR_OK;
}
#endif


/*----------------------------------------------------------------------------
 * Name: _menu_pic_mode_list_create
 *
 * Description:
 *  Create the listbox of input selection.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_pic_mode_list_create(HANDLE_T h_parent, HANDLE_T*	ph_widt)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = MAX_REC;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      PICTURE_MODE_LST_X,
                      PICTURE_MODE_LST_Y + PIC_MODE_ARROW_HEIGHT,
                      PICTURE_MODE_LST_W,
                      (MENU_ITEM_V_HEIGHT*PICTURE_MODE_VISIBLE_ELEM));

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _picture_mode_proc_fct,
                                &t_lb_init,
                                NULL,
                                ph_widt);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_widt,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(*ph_widt,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_arrow_create(h_parent, &t_rect);

    t_rect.i4_top = CONTENT_Y;
    t_rect.i4_bottom = MENU_ITEM_V_HEIGHT*PICTURE_MODE_VISIBLE_ELEM + CONTENT_Y;

    menu_list_arrow_move(&t_rect, FALSE);

    menu_list_arrow_hide(FALSE);
    return MENUR_OK;
}

static VOID _pic_mode_move_help_tip(UINT8 ui1_row_num)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T  h_last_shadow_item;

    if(ui1_row_num >= PICTURE_MODE_VISIBLE_ELEM)
    {
        /* move help tip text */
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * PICTURE_MODE_VISIBLE_ELEM + CONTENT_Y + 2*PIC_MODE_ARROW_HEIGHT;
        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
    }
    else
    {
        /* move help tip text */
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui1_row_num + CONTENT_Y;
        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
    }

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
#if 0
    PICTURE_MODE_T* pt_page_data = &t_pic_mode_page_data;

    i4_ret = _pic_mode_image_create(pt_page_data->h_cnt_frm,
                                    PICTURE_MODE_LST_X,
                                    PICTURE_MODE_LST_Y,
                                    PICTURE_MODE_LST_W,
                                    PICTURE_MODE_LST_H,
                                    pt_page_data);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_pic_mode_list_create(&pt_page_data->h_pic_mode_lb);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif
    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
#if 0
    INT32 i4_ret;
    PICTURE_MODE_T* pt_page_data = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_page_data);

    if(i4_ret == MENUR_OK)
    {
        if(pt_page_data != NULL)
        {
            c_mem_free(pt_page_data);
        }
    }
#endif
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32  i4_ret;
    HANDLE_T  h_cnt_frm;
    UINT16  ui2_num = 0;
    UINT16  ui2_idx = 0;
    WGL_LB_ITEM_T  at_items[1];

    /* set title */
    menu_main_set_title(MLM_MENU_KEY_VID_PIC_MODE_ITEM);

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_pic_mode_list_create(h_cnt_frm, &h_pic_mode);
    MENU_CHK_FAIL(i4_ret);

    ui2_num = get_cust_picture_mode_num();
    if(ui2_num == 0)
    {
        DBG_LOG_PRINT(("<MENU> get cust picture mode num fail:%s:%d:%d\r\n", __FILE__, __LINE__, ui2_num));
    }

    i4_ret = c_wgl_do_cmd(h_pic_mode,
                      WGL_CMD_LB_SET_ELEM_NUM,
                      WGL_PACK(ui2_num),
                      NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _set_vid_pic_mode_items_text();
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_visibility(h_pic_mode, WGL_SW_NORMAL);
    c_wgl_set_focus(h_pic_mode, WGL_NO_AUTO_REPAINT);

    _pic_mode_move_help_tip(ui2_num);

    i4_ret = menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE_MODE);
    MENU_CHK_FAIL(i4_ret);

    if(a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI )
    {
        i4_ret = menu_doly_vision_logo_show(TRUE);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_doly_vision_logo_show(FALSE);
        MENU_CHK_FAIL(i4_ret);
    }

    menu_pm_repaint();

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32  i4_ret;

    i4_ret = c_wgl_set_visibility(h_pic_mode, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_destroy_widget(h_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_arrow_hide(FALSE);

    h_pic_mode = NULL_HANDLE;
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
#if 0
    c_wgl_set_focus(t_pic_mode_page_data.h_pic_mode_lb,TRUE);

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);
#endif
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
#if 0
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);
#endif
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
INT32 menu_page_pic_mode_init(VOID)
{
    t_g_menu_page_pic_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_pic_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_pic_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_pic_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_pic_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_pic_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_pic_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}




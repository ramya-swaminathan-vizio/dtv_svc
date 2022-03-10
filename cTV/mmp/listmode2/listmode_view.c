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
 * $RCSfile: listmode_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_drv_cust.h"
#include "listmode_view.h"
#include MMP_COM_UI_HEADER_FILE
#include MMP_MLM_HEADER_FILE
#include "listmode.h"
#include "mmp/mmp_mmc_file.h"
#include "mmp/app/mmp_main.h"
#include "c_dbg.h"

#include "res/menu2/menu_clr.h"
#include "res/nav/nav_view.h"
#include "menu2/menu_page.h"
#include "mmp/listmode2/listmode.h"

#include "mmp/sort/a_mmp_sort.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "app_util/option_list/a_optl.h"
#include "res/mmp/file_browser/mmp_file_browser_rc.h"
#include "mmp/file_operator_list/mmp_file_operator_list.h"
#ifdef MMP_GUI_AUTHORING
#include "res/mmp/gen/mmp_lm_custom_layout.h"
#include "res/mmp/gen/mmp_audio_control_layout.h"
#include "res/mmp/gen/mmp_video_control_layout.h"
#endif
#include "mmp/common_ui2/mmp_info_bar.h"
#include "mmp/common_ui2/mmp_common_ui_animation.h"

#include "mmp/common_ui2/mmp_com_ui_info_handler.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/model/model.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "nav/banner2/a_banner.h"
#endif


/*-----------------------------------------------------------------------------
 * variable declarations

 *---------------------------------------------------------------------------*/
#define MMP_LM_VIEW_ATTR_TYPE             UINT8
#define MMP_LM_VIEW_ATTR_DEV_LST_SHOW     (0x01)
#define MMP_LM_VIEW_ATTR_ANIMATION        (0x02)
#define MMP_LM_VIEW_ATTR_VIEW_ACTIVE      (0x04)
#define MMP_LM_VIEW_ATTR_SORT_MODE_SHOW   (0x08)
#define MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW   (0x10)
#define MMP_LM_VIEW_ATTR_PLAY_MODE_SHOW   (0x20)

#define MMP_LM_VIEW_SHOW_TYPE             UINT8
#define MMP_LM_VIEW_SHOW_DEV_LST          (0)
#define MMP_LM_VIEW_SHOW_SORT             (1)
#define MMP_LM_VIEW_SHOW_VIEW             (2)
#define MMP_LM_VIEW_SHOW_PLAY             (3)

#ifdef APP_TTS_SUPPORT
#define MMP_LM_VIEW_OPTL_SORT              (0)
#define MMP_LM_VIEW_OPTL_VIEW              (1)
#define MMP_LM_VIEW_OPTL_USB               (2)
#define MMP_LM_VIEW_OPTL_PLAY              (3)
#endif

//#define MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
#define _LM_MAX_FOCUS_STACK                ((UINT32)8)

/* memorize last focus, for easily restoring. */
#ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
typedef struct _LM_LAST_FOCUS_STACK_T
{
    HANDLE_T       *ph_base;
    HANDLE_T       *ph_top;
    UINT32         ui4_stacksize;
}LM_LAST_FOCUS_STACK_T;
#else
typedef struct _LM_LAST_FOCUS_T
{
    HANDLE_T       ah_focus_stack[_LM_MAX_FOCUS_STACK];
    UINT32         ui4_next_focus_idx;
}LM_LAST_FOCUS_T;
#endif

typedef struct
{
    HANDLE_T        h_canvas;
    HANDLE_T        h_main_frm;
    HANDLE_T        h_side_frm;
    HANDLE_T        h_control_frm;
    HANDLE_T        h_info_frm;
    HANDLE_T        h_list_frm;

    HANDLE_T        h_audio_ctrl_frm;
    HANDLE_T        h_video_ctrl_frm;

    HANDLE_T        h_option_list;

    HANDLE_T        h_file_lb;

    HANDLE_T        h_side_p_focus_item;
    UINT32          ui4_lb_focus_id;

    UINT32          ui4_current_page;
    UINT32          ui4_page_cnt;
    UINT32          ui4_hlt;           //current playing idx
    UINT16          ui2_lang;

#ifdef APP_TTS_SUPPORT
    UINT16          ui2_optl_item;
#endif


    MMP_LM_VIEW_ATTR_TYPE   ui1_attr;
}  LISTMODE_VIEW_T;

static LISTMODE_VIEW_T    t_g_listmode_view;
static UINT32             ui4_g_file_lbw_hlt_idx;
extern UINT32             ui4_g_play_idx;
#ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
static LM_LAST_FOCUS_STACK_T t_g_last_focus_stack;
#else
static LM_LAST_FOCUS_T    t_g_last_focus;
#endif

static UINT32 ui4_g_tag_value = 0;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
#ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
static INT32 _mmp_lm_view_init_focus_stack(VOID);

static INT32 _mmp_lm_view_destroy_focus_stack(VOID);
#endif

static INT32 _mmp_lm_view_push_focus(HANDLE_T    h_focus);

static INT32 _mmp_lm_view_pop_focus(HANDLE_T* ph_focus);

static INT32 _mmp_lm_view_clean_focus_stack(VOID);

static UINT32 _mmp_lm_view_get_item_num(VOID);
static INT32 _mmp_lm_view_set_focus_to_file_lst(UINT8   ui1_repaint);

static INT32 _mmp_lm_view_text_set_txt(HANDLE_T      h_widget,
                                                 UTF16_T*      pw2s_str);

static INT32 _mmp_lm_view_btn_set_txt(HANDLE_T      h_widget,
                                                UTF16_T*      pw2s_str);

static INT32 _mmp_lm_view_lb_set_item_txt(HANDLE_T      h_widget,
                                                     UINT8         ui1_item_idx,
                                                     UTF16_T*      pw2s_str);

static INT32 _mmp_lm_view_frm_main_frm_fct(HANDLE_T    h_widget,
                                                 UINT32      ui4_msg,
                                                 VOID*       pv_param1,
                                                 VOID*       pv_param2);

static INT32 _mmp_lm_view_optl_set_dev_list_item(VOID);

static VOID _mmp_lm_view_file_list_select(VOID*   pv_param1,
                                                    VOID*   pv_param2,
                                                    VOID*   pv_param3,
                                                    VOID*   pv_param4);

static INT32 _mmp_lm_view_lst_file_list_fct (HANDLE_T       h_widget,
                                                     UINT32         ui4_msg,
                                                     VOID*          pv_param1,
                                                     VOID*          pv_param2);

static INT32 _mmp_lm_view_btn_back_to_side_fct(HANDLE_T    h_widget,
                                                             UINT32      ui4_msg,
                                                             VOID*       pv_param1,
                                                             VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_back_to_menu_fct(HANDLE_T    h_widget,
                                                               UINT32      ui4_msg,
                                                               VOID*       pv_param1,
                                                               VOID*       pv_param2);

static INT32 _mmp_lm_view_lst_dev_name_fct(HANDLE_T    h_widget,
                                                        UINT32      ui4_msg,
                                                        VOID*       pv_param1,
                                                        VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_audio_play_fct(HANDLE_T    h_widget,
                                                          UINT32      ui4_msg,
                                                          VOID*       pv_param1,
                                                          VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_audio_back_fct(HANDLE_T    h_widget,
                                                           UINT32      ui4_msg,
                                                           VOID*       pv_param1,
                                                           VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_audio_forward_fct(HANDLE_T    h_widget,
                                                               UINT32      ui4_msg,
                                                               VOID*       pv_param1,
                                                               VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_browse_photo_fct(HANDLE_T    h_widget,
                                                              UINT32      ui4_msg,
                                                              VOID*       pv_param1,
                                                              VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_sort_setting_fct(HANDLE_T    h_widget,
                                                           UINT32      ui4_msg,
                                                           VOID*       pv_param1,
                                                           VOID*       pv_param2);

static INT32 _mmp_lm_view_btn_view_setting_fct(HANDLE_T    h_widget,
                                                             UINT32      ui4_msg,
                                                             VOID*       pv_param1,
                                                             VOID*       pv_param2);

static VOID _mmp_lm_view_optl_proc_fct(VOID*    pv_tag,
                                                  UINT32   ui4_msg,
                                                  VOID*    pv_param1,
                                                  VOID*    pv_param2);
static VOID _mmp_lm_view_lst_file_list_nfy (VOID*         pv_tag_nfy,
                                                     const LBW_NOTIFY_T* pt_nfy);

static INT32 _mmp_lm_view_set_file_list_frm(VOID);
static INT32 _mmp_lm_view_set_device_name(VOID);
static INT32 _mmp_lm_view_set_control_frm(BOOL b_show);
static INT32 _mmp_lm_view_set_audio_control_frm(BOOL b_show);
static INT32 _mmp_lm_view_set_video_control_frm(BOOL b_show);
static INT32 _mmp_lm_view_set_control_btn_txt(VOID);
static INT32 _mmp_lm_view_audio_control_set_nav(VOID);
static INT32 _mmp_lm_view_video_control_set_nav(VOID);
static INT32 _mmp_lm_view_audio_play_first_file(VOID);
static INT32 _mmp_lm_view_optl_dev_list_setting(VOID* pv_tag);
static INT32 _mmp_lm_view_optl_show(MMP_LM_VIEW_SHOW_TYPE e_show_type);
static INT32 _mmp_lm_view_set_sort_mode(MMP_SORT_TYPE_T      e_mode);
static INT32 _mmp_listmode_view_optl_sort_setting(VOID* pv_tag);
static INT32 _mmp_lm_view_optl_set_sort_item (VOID);
static INT32 _mmp_lm_view_set_view_mode(BOOL b_is_recursive);
static INT32 _mmp_lm_view_optl_view_setting(VOID* pv_tag);
static INT32 _mmp_lm_view_optl_set_view_item(VOID);
static VOID _mmp_lm_view_optl_time_out(VOID*      pv_tag1,
                                                  VOID*      pv_tag2,
                                                  VOID*      pv_tag3,
                                                  VOID*      pv_tag4);
static INT32 _mmp_lm_view_create_optl(VOID);
static INT32 _mmp_lm_view_create_file_list(HANDLE_T    h_parent,
                                                    a_lbw_req_data_fct     pf_lbw_req_data_fct,
                                                    HANDLE_T*              ph_lb_handle);
static INT32 _mmp_lm_view_create_main_frame(VOID);
static INT32 _mmp_lm_view_show_side_frm(VOID);
static HANDLE_T _mmp_lm_view_get_wgl_handle(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_ret);
static INT32 _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_rect,
                                                  WGL_SW_CMD_T                e_type);
static INT32 _mmp_lm_view_get_visibility(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_rect,
                                                  BOOL*                       pb_visible);
static INT32 _mmp_lm_view_set_view_sort_mode(VOID);

extern INT32 mmp_mc_browse_fg_key_handler(UINT32 ui4_keycode, UINT32 ui4_keystatus);

static VOID _mmp_lm_view_default_key_handler(UINT32 ui4_key_code, UINT32 ui4_keystatus);
static INT32 _mmp_lm_view_default_key_up_handler(UINT32 ui4_key_code,UINT32 ui4_keystatus);
static INT32 _mmp_lm_view_default_key_down_handler(UINT32 ui4_key_code,UINT32 ui4_keystatus);
static INT32 _mmp_lm_view_optl_set_play_item();
UINT32 mmp_lm_view_show_focus_item_info(UINT32 ui4_focus);
extern BOOL a_is_oled_compensation_support();

#ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_init_focus_stack
 *
 * Description: init last focus widget stack.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_init_focus_stack(VOID)
{
    c_memset(&t_g_last_focus_stack, 0, sizeof(LM_LAST_FOCUS_STACK_T));
    t_g_last_focus_stack.ph_base = (HANDLE_T *)c_mem_alloc(_LM_MAX_FOCUS_STACK*sizeof(HANDLE_T));
    if (!t_g_last_focus_stack.ph_base)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return MMPR_OUT_OF_MEM;
    }

    t_g_last_focus_stack.ph_top = t_g_last_focus_stack.ph_base;
    t_g_last_focus_stack.ui4_stacksize = _LM_MAX_FOCUS_STACK;

#ifdef DEBUG
    DBG_LOG_PRINT(("\n%s,%s,%d,ph_base=%d,ph_top=%d,ui4_stacksize=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                t_g_last_focus_stack.ph_base, t_g_last_focus_stack.ph_top, t_g_last_focus_stack.ui4_stacksize));
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_push_focus
 *
 * Description: push last focus widget's focus to stack.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_push_focus(HANDLE_T    h_focus)
{
    if (NULL_HANDLE == h_focus)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }

#ifdef DEBUG
    DBG_LOG_PRINT(("\n%s,%s,%d,ph_base=%d,ph_top=%d,ui4_stacksize=%d,substractvalue=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                t_g_last_focus_stack.ph_base, t_g_last_focus_stack.ph_top, t_g_last_focus_stack.ui4_stacksize,
                (t_g_last_focus_stack.ph_top-t_g_last_focus_stack.ph_base)));
#endif

    if ((t_g_last_focus_stack.ph_top - t_g_last_focus_stack.ph_base)
        >= t_g_last_focus_stack.ui4_stacksize)
    {
        t_g_last_focus_stack.ph_base = (HANDLE_T *)c_mem_realloc(t_g_last_focus_stack.ph_base,
                                         (t_g_last_focus_stack.ui4_stacksize+1)*sizeof(HANDLE_T));

        if (!t_g_last_focus_stack.ph_base)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d\n",
                        __FILE__, __FUNCTION__, __LINE__));
            return MMPR_OUT_OF_MEM;
        }

        t_g_last_focus_stack.ph_top = t_g_last_focus_stack.ph_base + t_g_last_focus_stack.ui4_stacksize;
        t_g_last_focus_stack.ui4_stacksize++;
    }

    *(t_g_last_focus_stack.ph_top) = h_focus;
    t_g_last_focus_stack.ph_top++;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_pop_focus
 *
 * Description: pop focus from focus stack to mmp.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_pop_focus(HANDLE_T* ph_focus)
{
    if (NULL == ph_focus)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                        __FILE__, __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }

#ifdef DEBUG
    DBG_LOG_PRINT(("\n%s,%s,%d,ph_base=%d,ph_top=%d,ui4_stacksize=%d,substractvalue=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                t_g_last_focus_stack.ph_base, t_g_last_focus_stack.ph_top, t_g_last_focus_stack.ui4_stacksize,
                (t_g_last_focus_stack.ph_top-t_g_last_focus_stack.ph_base)));
#endif

    if (t_g_last_focus_stack.ph_top == t_g_last_focus_stack.ph_base)
    {
        return MMPR_NO_DATA;
    }

    *ph_focus = *(t_g_last_focus_stack.ph_top-1);
    t_g_last_focus_stack.ph_top--;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_clean_focus_stack
 *
 * Description: clean focus stack when exit mmp application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_clean_focus_stack(VOID)
{
    t_g_last_focus_stack.ph_top = t_g_last_focus_stack.ph_base;
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_destroy_focus_stack
 *
 * Description: destroy focus stack when exit mmp application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_destroy_focus_stack(VOID)
{
    UINT32        ui4_i = 0;

    _mmp_lm_view_clean_focus_stack();

    for (ui4_i=t_g_last_focus_stack.ui4_stacksize-1; ui4_i>=0; ui4_i--)
    {
        c_mem_free(t_g_last_focus_stack.ph_base+ui4_i);
    }

    c_memset(&t_g_last_focus_stack, 0, sizeof(LM_LAST_FOCUS_STACK_T));

    return MMPR_OK;
}
#else
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_push_focus
 *
 * Description: push last focus widget's focus to stack.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_push_focus(HANDLE_T    h_focus)
{
    LM_LAST_FOCUS_T*       pt_this = &t_g_last_focus;
    HANDLE_T               h_push_focus = NULL_HANDLE;
    INT32                  i4_ret = MMPR_OK;

    if (pt_this->ui4_next_focus_idx >= _LM_MAX_FOCUS_STACK)
    {
        return MMPR_OUT_OF_LIMIT;
    }

    if (NULL_HANDLE == h_focus)
    {
        i4_ret = c_wgl_get_focus(&h_push_focus);
        if(WGLR_OK != i4_ret)
        {
            i4_ret = MMPR_FAIL;
        }
    }
    else
    {
        h_push_focus = h_focus;
    }

    pt_this->ah_focus_stack[pt_this->ui4_next_focus_idx] = h_push_focus;
    pt_this->ui4_next_focus_idx++;

#ifdef DEBUG
    DBG_LOG_PRINT(("\n<push_focus>%s,%s,%d,ui4_next_focus_idx=%d,h_push_focus=%d,i4_ret=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui4_next_focus_idx, h_push_focus, i4_ret));
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_pop_focus
 *
 * Description: pop focus from focus stack to mmp.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_pop_focus(HANDLE_T* ph_focus)
{
    LM_LAST_FOCUS_T*       pt_this = &t_g_last_focus;
    INT32                  i4_ret = MMPR_OK;

    if (NULL == ph_focus)
    {
        return MMPR_INV_ARG;
    }

    do
    {
        if (0 == pt_this->ui4_next_focus_idx)
        {
            i4_ret = MMPR_NO_DATA;
            break;
        }

        *ph_focus = pt_this->ah_focus_stack[pt_this->ui4_next_focus_idx-1];
        pt_this->ah_focus_stack[pt_this->ui4_next_focus_idx-1] = NULL_HANDLE;
        pt_this->ui4_next_focus_idx--;
        i4_ret = MMPR_OK;
    }while(0);

#ifdef DEBUG
    DBG_LOG_PRINT(("\n<pop_focus>%s,%s,%d,ui4_next_focus_idx=%d,h_push_focus=%d,i4_ret=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui4_next_focus_idx, *ph_focus, i4_ret));
#endif

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_clean_focus_stack
 *
 * Description: clean focus stack when exit mmp application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_clean_focus_stack(VOID)
{
    LM_LAST_FOCUS_T*       pt_this = &t_g_last_focus;

    while(pt_this->ui4_next_focus_idx > 0)
    {
        pt_this->ah_focus_stack[pt_this->ui4_next_focus_idx-1] = NULL_HANDLE;
        pt_this->ui4_next_focus_idx--;
    }

    return MMPR_OK;
}
#endif


INT32 _mmp_lm_set_focus(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_rect, UINT8 ui1_repaint)
{
    HANDLE_T    h_widget = NULL_HANDLE;

    DBG_LOG_PRINT(("[MMP][%s %d] e_repaint_rect = %d,ui1_repaint = %d\n",__FUNCTION__,__LINE__,e_repaint_rect,ui1_repaint));
    h_widget = _mmp_lm_view_get_wgl_handle(e_repaint_rect);

    MMP_ASSERT(NULL_HANDLE != h_widget);
    IS_MMPR_OK(c_wgl_set_focus(h_widget,ui1_repaint));
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_listmode_view_lbw_reload_partial
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_lbw_reload_partial(UINT32               ui4_load_flag,
                                                   UINT32               ui4_idx_start,
                                                   UINT32               ui4_idx_end,
                                                   LBW_RPNT_MODE_T      e_repaint)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    DBG_LOG_PRINT(("\n%s,%s,%d,ui4_idx_start=%d,ui4_idx_end=%d,e_repaint=%d\n",
                 __FILE__, __FUNCTION__, __LINE__, ui4_idx_start, ui4_idx_end, e_repaint));
    mmp_lm_set_load_status((E_MMP_LM_LOAD_STATUS_T)ui4_load_flag);
    MMPR_LOG_ON_FAIL(mmp_be_set_focus_item(ui4_idx_start));
    return a_lbw_reload_partial(pt_this->h_file_lb, ui4_idx_start, ui4_idx_end,LBW_RPNT_MODE_PARTIAL_RPNT);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_get_item_num
 *
 * Description: this function is used to get current folder containt  how many items
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT32 _mmp_lm_view_get_item_num(VOID)
{
    UINT32         ui4_dir_num = 0;
    UINT32         ui4_file_num = 0;

    if(MMPR_OK != mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num))
    {
        return MMPR_FAIL;
    }  
    return ui4_dir_num + ui4_file_num;
}

UINT32 mmp_lm_view_update_focus_item_info()
{
    HANDLE_T h_focus;

    c_wgl_get_focus(&h_focus);

    if (h_focus == t_g_listmode_view.h_file_lb)
    {
        a_lbw_get_hlt_idx(t_g_listmode_view.h_file_lb,&t_g_listmode_view.ui4_lb_focus_id);
        if(ITEM_TYPE_FILE == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,t_g_listmode_view.ui4_lb_focus_id))
            mmp_be_set_focus_item(t_g_listmode_view.ui4_lb_focus_id);
#ifdef APP_TTS_SUPPORT
        {
             UTF16_T*  w2s_str = mmp_lm_get_file_name_by_idx((t_g_listmode_view.ui4_lb_focus_id % LM_LBW_ELEM_NUM_PER_PAGE));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        }
#endif
        return mmp_lm_view_show_focus_item_info(t_g_listmode_view.ui4_lb_focus_id);
    }
    return MMPR_OK;
}

INT32  mmp_lm_view_get_focus_item_full_path(CHAR* p_sz_path)
{
    UINT32         ui4_dir_num  = 0;
    UINT32         ui4_file_num = 0;
    UINT32         ui4_file_idx = 0;
    UINT32         ui4_cnt      = 1;
    UINT32       ui4_lb_focus_id;
    MMP_ITEM_INFO_T  t_item_info;

    /*Get focus file index*/

    if (MMPR_OK != mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num))
    {
        return MMPR_FAIL;
    }
    a_lbw_get_hlt_idx(t_g_listmode_view.h_file_lb,&ui4_lb_focus_id);
    ui4_file_idx = ui4_lb_focus_id - ui4_dir_num;

    /*Get focus file item info*/
    c_memset(&t_item_info, 0, sizeof(MMP_ITEM_INFO_T));
    if(MMPR_OK != mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                  ITEM_TYPE_FILE,
                                  ui4_file_idx,
                                  &ui4_cnt,
                                  &t_item_info))
    {
        return MMPR_FAIL;
    }
    c_sprintf(p_sz_path,"%s/%s",t_item_info.s_parent_name,t_item_info.s_name);

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_focus_to_file_lst
 *
 * Description: this function is used to set focus to file list,
 *                    if file list is empty, never set focus to it,
 *                    otherwise, TV will hang.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_focus_to_file_lst(UINT8   ui1_repaint)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    a_lbw_get_hlt_idx(pt_this->h_file_lb,&pt_this->ui4_lb_focus_id);

    if ( _mmp_lm_view_get_item_num() > 0)
    {
        MMPR_LOG_ON_FAIL( _mmp_lm_set_focus(MMP_LM_RC_REPAINT_RECT_ID_FILE_LB,ui1_repaint));
    }

    return (INT32)mmp_lm_view_update_focus_item_info();
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_text_set_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_text_set_txt(HANDLE_T      h_widget,
                                                 UTF16_T*      pw2s_str)
{
    INT32 i4_ret = MMPR_OK;
    i4_ret = c_wgl_do_cmd (h_widget,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(pw2s_str),
                           WGL_PACK((UINT16)0xFF));
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_set_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_set_txt(HANDLE_T      h_widget,
                                            UTF16_T*      pw2s_str)
{
    INT32 i4_ret = MMPR_OK;
    MMP_ASSERT(NULL_HANDLE != h_widget);
    i4_ret = c_wgl_do_cmd (h_widget,
                           WGL_CMD_BTN_SET_TEXT,
                           WGL_PACK(pw2s_str),
                           WGL_PACK((UINT16)0xFF));
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_lb_set_item_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_lb_set_item_txt(HANDLE_T      h_widget,
                                                 UINT8         ui1_item_idx,
                                                 UTF16_T*      pw2s_str)
{
    INT32 i4_ret = MMPR_OK;
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, ui1_item_idx),
                          WGL_PACK(pw2s_str));
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_file_list_select
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_lm_view_file_list_select(VOID*   pv_param1,
                                                    VOID*   pv_param2,
                                                    VOID*   pv_param3,
                                                    VOID*   pv_param4)
{
    UINT32      ui4_hlt_idx = (UINT32)pv_param1;
    UINT32      ui4_tag_value = (UINT32)pv_param2;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    /* discard expired messages */
    if (ui4_tag_value < ui4_g_tag_value)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,ui4_tag_value=%d,ui4_g_tag_value=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    ui4_tag_value, ui4_g_tag_value));
        return;
    }

    if (FALSE == (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_VIEW_ACTIVE))
    {
        return;
    }

    MMPR_LOG_ON_FAIL(mmp_info_bar_hide());
    MMPR_LOG_ON_FAIL(mmp_listmode_item_selected(ui4_hlt_idx));
    t_g_listmode_view.ui4_hlt = ui4_hlt_idx;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_frm_main_frm_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_frm_main_frm_fct(HANDLE_T    h_widget,
                                             UINT32      ui4_msg,
                                             VOID*       pv_param1,
                                             VOID*       pv_param2)
{
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if ( WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg )
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

extern INT32 a_mmp_audio_show_playback_info(BOOL b_show);

UINT32 mmp_lm_view_show_focus_item_info(UINT32 ui4_focus)
{
    MMP_ITEM_TYPE_T         e_item_type = ITEM_TYPE_NONE;
    MMP_MEDIA_TYPE_T        e_media_type = MMP_MEDIA_TYPE_UNKNOWN;
    /* check the item type */
    e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,ui4_focus);
    DBG_LOG_PRINT(("[MMP][%s %d]ui4_focus = %d, e_item_type = %d\n",__FUNCTION__,__LINE__,ui4_focus,e_item_type));
    MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type));
    if(ITEM_TYPE_FILE == e_item_type)
    {

        MMP_FP_INFO_HDLR_INIT_PARAM_T   t_param       = {0};
        GL_RECT_T                       t_rect        = {0};
        MMP_MEDIA_TYPE_T                e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
        MMP_LM_FILE_STATUS_T            e_file_status = MMP_LM_FILE_STATUS_NONE;

        MMPR_LOG_ON_FAIL(mmp_be_set_focus_item(ui4_focus));
        MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                         (VOID*)&e_filter_type));
        MMPR_LOG_ON_FAIL( mmp_lm_get_file_status_by_idx(ui4_focus,e_filter_type,&e_file_status));
        DBG_LOG_PRINT(("[MMP][%s %d] focus = %d,status = %d\n",__FUNCTION__,__LINE__,ui4_focus,e_file_status));
        if(MMP_MEDIA_TYPE_VIDEO == e_media_type)
        {
            SET_RECT_BY_SIZE (&t_rect,
                          LM_FILE_VIDEO_INFO_HANDLE_X,
                          LM_FILE_VIDEO_INFO_HANDLE_Y,
                          LM_FILE_VIDEO_INFO_HANDLE_W,
                          LM_FILE_VIDEO_INFO_HANDLE_H);
            t_param.h_parent = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_VIDEO_INFO);
            t_param.e_media_type = MMP_MEDIA_TYPE_VIDEO;
        }
        else
        {
            t_param.h_parent = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_AUDIO_INFO);
            t_param.e_media_type = MMP_MEDIA_TYPE_AUDIO;
        }

        t_param.e_ui_type = MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS;
        t_param.pt_rect = &t_rect;

        MMPR_LOG_ON_FAIL(mmp_mc_browse_display_focus_item_info(&t_param));

        if(MMP_MEDIA_TYPE_AUDIO == e_media_type)
        {
            MMPR_LOG_ON_FAIL(a_mmp_audio_show_playback_info((e_file_status == MMP_LM_FILE_IS_PAUSED || e_file_status == MMP_LM_FILE_IS_PLAYING) ? TRUE : FALSE ));
        }
    }
    else
    {
        if(MMP_MEDIA_TYPE_AUDIO == e_media_type)
        {
            _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_INFO,
                                        WGL_SW_NORMAL);
        }
    }
    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_lst_file_list_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_lst_file_list_fct (HANDLE_T       h_widget,
                                                     UINT32         ui4_msg,
                                                     VOID*          pv_param1,
                                                     VOID*          pv_param2)
{
    INT32               i4_ret = MMPR_OK;
    UINT32              ui4_hlt_idx = 0;
    UINT32              ui4_item_num = 0;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    MMP_ITEM_TYPE_T     e_item_type = ITEM_TYPE_NONE;
    MMP_PLAY_STATE_T    e_bk_state = MMP_PLAY_STATE_CLOSED;
    MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

    UINT32 ui4_key_code = (UINT32)pv_param1;

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_REPEAT:
            break;
        case WGL_MSG_KEY_UP:
            {
                switch (ui4_key_code)
                {
                    default:
                    {
                        _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
                    }
                        break;
                }
            }
            break;

        case WGL_MSG_KEY_DOWN:
        {
            MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
            CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
            SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
            BOOL                    b_is_dlna_delay = FALSE;

            i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
            IS_MMPR_OK(i4_ret);

            i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
            IS_MMPR_OK(i4_ret);
            DBG_LOG_PRINT(("[MMP][%s %d] key = 0x%x\n",__FUNCTION__,__LINE__,ui4_key_code));
            /* if source is Net/dlna ,delay key response when loading animation */
            if(((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
               (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type )) &&
               (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_ANIMATION) )
            {
                MMP_DBG_INFO(("delay key response %s,%d\n\r",__FILE__,__LINE__));
                b_is_dlna_delay = TRUE;
            }

            i4_ret = a_lbw_get_elem_num(pt_this->h_file_lb,
                                        &ui4_item_num);
            if ((MMPR_OK != i4_ret)
                ||(0 == ui4_item_num))
            {
                break;
            }

            i4_ret = a_lbw_get_hlt_idx(pt_this->h_file_lb,
                                       &ui4_hlt_idx);
            IS_MMPR_OK(i4_ret);

            switch (ui4_key_code)
            {
                case BTN_CURSOR_UP:
                {
                    if(b_is_dlna_delay || LM_STATUS_LOOP == mmp_lm_get_load_status())
                    {
                        MMP_DBG_ERROR(("BTN_CURSOR_UP key no response %s,%d,load status = %d\n\r",__FUNCTION__,__LINE__,mmp_lm_get_load_status()));
                        break;
                    }
                    if (0 == (ui4_hlt_idx % LM_LBW_ELEM_NUM_PER_PAGE))
                    {
                        IS_MMPR_OK(_mmp_lm_set_focus(MMP_LM_RC_REPAINT_RECT_ID_TO_SIDE_BAR, WGL_SYNC_AUTO_REPAINT));
                        pt_this->ui4_lb_focus_id = ui4_hlt_idx;
                    }
                    else
                    {
                        i4_ret = a_lbw_hlt_elem(pt_this->h_file_lb,
                                                ui4_hlt_idx - 1,
                                                LBW_RPNT_MODE_PARTIAL_RPNT);
                        IS_MMPR_OK(i4_ret);
                    }
                    #ifdef NEVER
                    if((--ui4_hlt_idx) != -1)
                        MMPR_LOG_ON_FAIL(mmp_lm_view_show_focus_item_info(ui4_hlt_idx));
                    #endif
                }
                    break;
                case BTN_RETURN:
                {
                    IS_MMPR_OK(_mmp_lm_set_focus(MMP_LM_RC_REPAINT_RECT_ID_TO_SIDE_BAR,WGL_SYNC_AUTO_REPAINT));
                    pt_this->ui4_lb_focus_id = ui4_hlt_idx;
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                    if(b_is_dlna_delay || LM_STATUS_LOOP == mmp_lm_get_load_status())
                    {
                        MMP_DBG_ERROR(("BTN_CURSOR_DOWN key no response %s,%d,load status = %d\n\r",__FUNCTION__,__LINE__,mmp_lm_get_load_status()));
                        return MMPR_OK;;
                    }

                    if ((ui4_hlt_idx + 1) != ui4_item_num &&
                        (0 != (ui4_hlt_idx + 1) % LM_LBW_ELEM_NUM_PER_PAGE))
                    {
                        i4_ret = a_lbw_hlt_elem(pt_this->h_file_lb,
                                                ui4_hlt_idx + 1,
                                                LBW_RPNT_MODE_PARTIAL_RPNT);
                        IS_MMPR_OK(i4_ret);
                    }
                    #ifdef NEVER
                    MMPR_LOG_ON_FAIL(mmp_lm_view_show_focus_item_info(ui4_hlt_idx + 1));
                    #endif
                }
                    break;
                case AUDIO_PLAYER_BTN_PLAY:
                {
                    e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,
                                                              ui4_hlt_idx);
                    if (ITEM_TYPE_FILE != e_item_type)
                    {
                        break;
                    }

                    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                             (VOID*)&e_media_type);
                    if ((MMPR_OK == i4_ret)
                        &&(MMP_MEDIA_TYPE_AUDIO == e_media_type))
                    {
                        i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                                        &e_bk_state);
                        if (MMPR_OK == i4_ret)
                        {
                            if ((MMP_PLAY_STATE_PLAYING == e_bk_state)
                                ||(MMP_PLAY_STATE_PLAYED == e_bk_state)
                                ||(MMP_PLAY_STATE_FAST_FORWARDING == e_bk_state)
                                ||(MMP_PLAY_STATE_FAST_FORWARDED == e_bk_state)
                                ||(MMP_PLAY_STATE_FAST_REWINDING == e_bk_state)
                                ||(MMP_PLAY_STATE_FAST_REWINDED == e_bk_state)
                                ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_bk_state)
                                ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_bk_state))
                            {
                                _mmp_lm_view_default_key_handler(ui4_key_code,ui4_msg);
                                return MMPR_OK;
                            }
                        }
                    }
                }
                case BTN_SELECT:
                {
                    if(b_is_dlna_delay || LM_STATUS_LOOP == mmp_lm_get_load_status())
                    {
                        MMP_DBG_ERROR(("BTN_SELECT key no response %s,%d,load status = %d\n\r",__FUNCTION__,__LINE__,mmp_lm_get_load_status()));
                        break;
                    }

                    ui4_g_tag_value++;
                    i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                                          _mmp_lm_view_file_list_select,
                                                          (VOID*)ui4_hlt_idx,
                                                          (VOID*)ui4_g_tag_value,
                                                          NULL,
                                                          NULL);
                    IS_MMPR_OK(i4_ret);
                }
                    break;
                case BTN_CURSOR_LEFT:
                {
                    if(b_is_dlna_delay || LM_STATUS_LOOP == mmp_lm_get_load_status())
                    {
                        MMP_DBG_ERROR(("BTN_CURSOR_LEFT key no response %s,%d,load status = %d\n\r",__FUNCTION__,__LINE__,mmp_lm_get_load_status()));
                        return MMPR_OK;
                    }

                    /* 1. left have page;
                       2. in the top of current page. */
                    if ((ui4_hlt_idx > (LM_LBW_ELEM_NUM_PER_PAGE - 1))&&
                        (0 == (ui4_hlt_idx % LM_LBW_ELEM_NUM_PER_PAGE)))
                    {
                        mmp_lm_set_load_status(LM_STATUS_LOOP);
                    }

                }
                    break;
                case BTN_CURSOR_RIGHT:
                {
                    if(b_is_dlna_delay || LM_STATUS_LOOP == mmp_lm_get_load_status())
                    {
                        MMP_DBG_ERROR(("BTN_CURSOR_RIGHT key no response %s,%d,load status = %d\n\r",__FUNCTION__,__LINE__,mmp_lm_get_load_status()));
                        return MMPR_OK;
                    }

                    /* 1. right have page;
                       2. in the bottom of current page. */
                    if ((ui4_hlt_idx < (ui4_item_num - 1)) &&
                        (0 == ((ui4_hlt_idx + 1) % LM_LBW_ELEM_NUM_PER_PAGE)))
                    {
                        mmp_lm_set_load_status(LM_STATUS_LOOP);
                    }
                }
                    break;
                default:
                {
                    _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
                }
                    break;
            }
        }
            break;
        default:
            break;
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_back_to_side_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_back_to_side_fct(HANDLE_T    h_widget,
                                                             UINT32      ui4_msg,
                                                             VOID*       pv_param1,
                                                             VOID*       pv_param2)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T *   pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            case BTN_RETURN:
            {
                HANDLE_T            h_control_widget = NULL_HANDLE;
                MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

                i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                         (VOID*)&e_media_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                switch (e_media_type)
                {
                    case MMP_MEDIA_TYPE_AUDIO:
                    {
                    #ifndef APP_CAST_TV_MMP_FG
                        h_control_widget = pt_this->h_side_p_focus_item;
                    #else
                        if (pt_this->h_side_p_focus_item != NULL_HANDLE)
                        {
                            h_control_widget = pt_this->h_side_p_focus_item;
                        }
                        else
                        {
                            h_control_widget =
                                mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
                        }
                    #endif
                    }
                        break;
                    case MMP_MEDIA_TYPE_VIDEO:
                    {
                    #ifdef APP_NET_DLNA_SUPPORT
                        if (mmp_be_current_is_dlna_device())
                        {
                        #ifdef DEBUG
                            DBG_LOG_PRINT(("\n_mmp_lm_view_btn_back_to_side_fct DLNA device\n"));
                        #endif

                            pt_this->h_side_p_focus_item =
                                      mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);

                            h_control_widget = pt_this->h_side_p_focus_item;
                        }
                        else
                    #endif
                        {
                            if (pt_this->h_side_p_focus_item != NULL_HANDLE)
                            {
                            #ifdef DEBUG
                                DBG_LOG_PRINT(("\nUSB device, same widget\n"));
                            #endif

                                h_control_widget = pt_this->h_side_p_focus_item;
                            }
                            else
                            {
                                h_control_widget =
                                    mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
                            }
                        }
                    }
                        break;
                    default:
                        break;
                }
                MMP_ASSERT(NULL_HANDLE != h_control_widget);
                i4_ret = c_wgl_set_focus(h_control_widget,
                                         WGL_SYNC_AUTO_REPAINT);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
                return MMPR_OK;
            case BTN_CURSOR_DOWN:
            {
                MMPR_LOG_ON_FAIL(_mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT));
            }
                break;
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        UTF16_T         w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    }
#endif

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_back_to_menu_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_back_to_menu_fct(HANDLE_T    h_widget,
                                                               UINT32      ui4_msg,
                                                               VOID*       pv_param1,
                                                               VOID*       pv_param2)
{
    INT32   i4_ret = MMPR_OK;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {


        switch (ui4_key_code)
        {
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = _mmp_lm_view_clean_focus_stack();
                MMPR_LOG_ON_FAIL(i4_ret);

            #ifndef APP_CAST_TV_MMP_FG
            #ifdef APP_TTS_SUPPORT
                /* exit mmp not to read banner tts */
                MMP_DBG_INFO(("mmp set banner tts disable %s,%d\n\r",__FILE__,__LINE__));
                set_banner_tts_enable(FALSE);
            #endif

            #ifdef APP_C4TV_SUPPORT
                /* cast source ,select source before link to menu page fix DTV00845309 */
                ISL_REC_T                   t_isl_rec;
                i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
                {
                    MMP_DBG_INFO(("exit mmp to cast source %s,%d\n\r",__FILE__,__LINE__));
                    mmp_main_set_back_to_menu_page(MENU_SHORT_CUT_MMP_MEDIA_TYPE);

                    i4_ret = mmp_be_pause_mmp();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            #else
                i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
                MMPR_LOG_ON_FAIL(i4_ret);
            #endif
                {
                    UINT32     ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;
                    SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;

                    ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_SHORTCUT_TO_MEDIATYPE;
                    i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                                       (VOID*) &ui4_exit_reason, z_size);
                }
                MMPR_LOG_ON_FAIL(i4_ret);
            #else
                MMP_DBG_INFO(("<mmp> back to fg %s,%d\n\r",__FILE__,__LINE__));
                LISTMODE_VIEW_T *   pt_this = &t_g_listmode_view;
                pt_this->h_side_p_focus_item = NULL_HANDLE;
                pt_this->ui4_lb_focus_id = 0;

                i4_ret = mmp_mc_list_close(MMP_GROUND_MODE_ALL);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_reset();
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_switch_browser(MMP_RC_BROWSER_ID_FOREGROUND,
                                               TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            #endif
            }
                return MMPR_OK;
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        UTF16_T         w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    }
#endif

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_side_btn_tts_play
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_side_btn_tts_play(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    MMP_SORT_TYPE_T         e_old_sort = MMP_SORT_TYPE_NONE;
    BOOL                    b_is_view_revursive = FALSE;
    INT32                   i4_index = 0;
    HANDLE_T                h_widget_sort = NULL_HANDLE;
    HANDLE_T                h_widget_view = NULL_HANDLE;
    HANDLE_T                h_widget_play = NULL_HANDLE;

    UTF16_T                 w2s_str[128] = {0};

    HANDLE_T h_widget_lst_dev = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    MMP_ASSERT(NULL_HANDLE != h_widget_lst_dev);

    if(pt_this->h_side_p_focus_item == h_widget_lst_dev)
    {
        /* sub btn*/
        UTF16_T                     w2s_dev_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
        UTF16_T                     w2s_dev_hint[MMP_DEV_NAME_MAX_LEN + 1] = {0};
        UINT32                      ui4_dir_num = 0;
        UINT32                      ui4_active_idx = 0;

        i4_ret = mmp_mc_device_get_mnt_count(&ui4_dir_num);
        if ((MMPR_OK == i4_ret)
            &&(ui4_dir_num > 0))
        {
            i4_ret = mmp_be_get_activate_device_info(w2s_dev_info,
                                                     w2s_dev_hint,
                                                     &ui4_active_idx);
            UTF16_T         w2s_str_name[256] = {0};
            c_uc_w2s_strcpy(w2s_str_name,w2s_dev_hint);
            c_uc_w2s_strncat(w2s_str_name,w2s_dev_info,MMP_DEV_NAME_MAX_LEN);
            a_app_tts_play(w2s_str_name,c_uc_w2s_strlen(w2s_str_name));
        }
        return MMPR_OK;
    }

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch (e_type)
    {
        case MMP_MEDIA_TYPE_AUDIO:
        {
            HANDLE_T  h_widget_audio_play = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
            MMP_ASSERT(NULL_HANDLE != h_widget_audio_play);

            HANDLE_T  h_widget_audio_forward = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_FORWARD);
            MMP_ASSERT(NULL_HANDLE != h_widget_audio_forward);

            HANDLE_T  h_widget_audio_back = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_BACK);
            MMP_ASSERT(NULL_HANDLE != h_widget_audio_back);

            HANDLE_T  h_widget_browse_phots = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO);
            MMP_ASSERT(NULL_HANDLE != h_widget_browse_phots);

            h_widget_sort = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT);
            MMP_ASSERT(NULL_HANDLE != h_widget_sort);

            h_widget_view = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_VIEW);
            MMP_ASSERT(NULL_HANDLE != h_widget_view);

            if(pt_this->h_side_p_focus_item == h_widget_audio_play)
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_audio_forward)
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_NEXT));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_audio_back)
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PREVIOUS));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_browse_phots)
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_BROWSE_PHOTO_BTN));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_sort)
            {
                /* get current sort type */
                i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                                        (VOID*)&e_old_sort);
                MMPR_LOG_ON_FAIL(i4_ret);

                switch (e_old_sort)
                {
                    case MMP_SORT_TYPE_AUD_ALBUM:
                    {
                        i4_index = 0;
                    }
                        break;
                    case MMP_SORT_TYPE_AUD_INV_ALBUM:
                    {
                        i4_index = 1;
                    }
                        break;
                    case MMP_SORT_TYPE_AUD_ARTIST:
                    {
                        i4_index = 2;
                    }
                        break;
                    case MMP_SORT_TYPE_AUD_INV_ARTIST:
                    {
                        i4_index = 3;
                    }
                        break;
                    case MMP_SORT_TYPE_AUD_NAME:
                    {
                        i4_index = 4;
                    }
                        break;
                    case MMP_SORT_TYPE_AUDIO_INV_NAME:
                    {
                        i4_index = 5;
                    }
                        break;
                    default:
                        break;
                }
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(i4_index + MLM_MMP_KEY_LISMODE_VIEW_SORT_ALBUM_A_Z));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_view)
            {
                /* get current view type */
                i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,
                                        (VOID*)&b_is_view_revursive);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (b_is_view_revursive)
                {
                    i4_index = 0;
                }
                else
                {
                    i4_index = 1;
                }
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(i4_index + MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL));
            }
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        }
            break;

        case MMP_MEDIA_TYPE_VIDEO:
        {
            h_widget_sort = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
            MMP_ASSERT(NULL_HANDLE != h_widget_sort);

            h_widget_view = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW);
            MMP_ASSERT(NULL_HANDLE != h_widget_view);
            h_widget_play = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_PLAY);
        MMP_ASSERT(NULL_HANDLE != h_widget_play);

            if(pt_this->h_side_p_focus_item == h_widget_sort)
            {
                /* get current sort type */
                i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                                        (VOID*)&e_old_sort);
                MMPR_LOG_ON_FAIL(i4_ret);

                switch (e_old_sort)
                {
                    case MMP_SORT_TYPE_VIDEO_INV_DATE:
                    {
                        i4_index = 0;
                    }
                        break;
                    case MMP_SORT_TYPE_VIDEO_DATE:
                    {
                        i4_index = 1;
                    }
                        break;
                    case MMP_SORT_TYPE_VIDEO_NAME:
                    {
                        i4_index = 2;
                    }
                        break;
                    case MMP_SORT_TYPE_VIDEO_INV_NAME:
                    {
                        i4_index = 3;
                    }
                        break;
                    default:
                        break;
                }
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(i4_index + MLM_MMP_KEY_LISMODE_VIEW_SORT_DATE_NEW_OLD));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_view)
            {
               /* get current view type */
                i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,
                                        (VOID*)&b_is_view_revursive);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (b_is_view_revursive)
                {
                    i4_index = 0;
                }
                else
                {
                    i4_index = 1;
                }
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(i4_index + MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL));
            }
            else if(pt_this->h_side_p_focus_item == h_widget_play)
            {
                MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE,&i4_index));
                DBG_LOG_PRINT(("[MMP][%s %d] i4_index = %d\n",__FUNCTION__,__LINE__,i4_index));
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(i4_index == 0 ? MLM_MMP_KEY_LISMODE_PLAY_MODE_ONCE : MLM_MMP_KEY_LISMODE_PLAY_MODE_CONTINUOUSLY));
            }
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        }
            break;

        default:
            break;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_tts_play
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_tts_play(UINT32  ui4_key_code)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    OPTL_ITEM_T             t_optl_item[LM_OPTL_ITEM_MAX_NUM];
    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    UINT16                  ui2_hlt_idx = 0;
    UINT16                  ui2_sub_idx = 0;
    MMP_SORT_TYPE_T         e_crnt_sort = MMP_SORT_TYPE_NONE;
    UTF16_T                 w2s_str[128] = {0};

    c_memset(&t_optl_item, 0, LM_OPTL_ITEM_MAX_NUM*sizeof(OPTL_ITEM_T));

    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_file_src_type(s_curr_path,
                                          &e_src_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set the item about sort type option list */
    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
        (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
    {
            /*  don't show the sort/view type in listmode optl */
    }
    else
    {
        /* Get focus index according to filter type*/
        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                 (VOID*)&e_type);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                                 (VOID*)&e_crnt_sort);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = a_optl_get_hlt_index(pt_this->h_option_list,
                                      &ui2_hlt_idx,
                                      &ui2_sub_idx);
        MMPR_LOG_ON_FAIL(i4_ret);

        if(BTN_CURSOR_DOWN == ui4_key_code)
        {
            ui2_hlt_idx += 1;
        }
        else if(BTN_CURSOR_UP == ui4_key_code)
        {
            ui2_hlt_idx -= 1;
            if((INT16)ui2_hlt_idx < 0)
            {
                /* back btn*/
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                return MMPR_OK;
            }
        }

        if(MMP_LM_VIEW_OPTL_SORT == pt_this->ui2_optl_item)
        {
            switch (e_type)
            {
                case MMP_MEDIA_TYPE_AUDIO:
                {
                    if(ui2_hlt_idx > 5)
                    {
                        break;
                    }
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_SORT_ALBUM_A_Z + ui2_hlt_idx));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                }
                    break;

                case MMP_MEDIA_TYPE_VIDEO:
                {
                    if(ui2_hlt_idx > 3)
                    {
                        break;
                    }
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_SORT_DATE_NEW_OLD + ui2_hlt_idx));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                }
                    break;
                default:
                    return MMPR_OK;
            }
        }
        else if(MMP_LM_VIEW_OPTL_VIEW == pt_this->ui2_optl_item)
        {
           switch (e_type)
            {
                case MMP_MEDIA_TYPE_AUDIO:
                case MMP_MEDIA_TYPE_VIDEO:
                {
                    if(ui2_hlt_idx > 1)
                    {
                        break;
                    }
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL + ui2_hlt_idx));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                }
                    break;
                default:
                    return MMPR_OK;
            }
        }
        else if(MMP_LM_VIEW_OPTL_USB == pt_this->ui2_optl_item)
        {
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_USB));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        }
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_back_to_list_tts_play
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_back_to_list_tts_play(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    UTF16_T                 w2s_str[128] = {0};
    UINT16                  ui2_hlt_idx = 0;
    UINT16                  ui2_sub_idx = 0;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    HANDLE_T                h_widget_sort = NULL_HANDLE;
    HANDLE_T                h_widget_view = NULL_HANDLE;
    HANDLE_T                h_widget_play = NULL_HANDLE;

    i4_ret = a_optl_get_hlt_index(pt_this->h_option_list,
                                      &ui2_hlt_idx,
                                      &ui2_sub_idx);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch (e_type)
    {
    case MMP_MEDIA_TYPE_AUDIO:
    {
        h_widget_sort = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT);
        MMP_ASSERT(NULL_HANDLE != h_widget_sort);

        h_widget_view = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_VIEW);
        MMP_ASSERT(NULL_HANDLE != h_widget_view);

        if(pt_this->h_side_p_focus_item == h_widget_sort)
        {
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(ui2_hlt_idx + MLM_MMP_KEY_LISMODE_VIEW_SORT_ALBUM_A_Z));
        }
        else if(pt_this->h_side_p_focus_item == h_widget_view)
        {
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(ui2_hlt_idx + MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL));
        }
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    }
        break;

    case MMP_MEDIA_TYPE_VIDEO:
    {
        h_widget_sort = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
        MMP_ASSERT(NULL_HANDLE != h_widget_sort);

        h_widget_view = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW);
        MMP_ASSERT(NULL_HANDLE != h_widget_view);

        h_widget_play = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_PLAY);
        MMP_ASSERT(NULL_HANDLE != h_widget_play)

        if(pt_this->h_side_p_focus_item == h_widget_sort)
        {
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(ui2_hlt_idx + MLM_MMP_KEY_LISMODE_VIEW_SORT_DATE_NEW_OLD));
        }
        else if(pt_this->h_side_p_focus_item == h_widget_view)
        {
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(ui2_hlt_idx + MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL));
        }
        else if(pt_this->h_side_p_focus_item == h_widget_play)
        {
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(ui2_hlt_idx + MLM_MMP_KEY_LISMODE_PLAY_MODE_ONCE));
        }
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    }
        break;

    default:
        break;
    }

    return i4_ret;
}

#endif

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_lst_dev_name_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_lst_dev_name_fct(HANDLE_T    h_widget,
                                                        UINT32      ui4_msg,
                                                        VOID*       pv_param1,
                                                        VOID*       pv_param2)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

        switch (ui4_key_code)
        {
            case BTN_SELECT:
            {
                i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                              WGL_SW_HIDE);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_lm_view_optl_show(MMP_LM_VIEW_SHOW_DEV_LST);
                MMPR_LOG_ON_FAIL(i4_ret);

            #ifdef APP_TTS_SUPPORT
                pt_this->ui2_optl_item = MMP_LM_VIEW_OPTL_USB;
            #endif
            }
                return MMPR_OK;
            case BTN_CURSOR_DOWN:
            {
            #ifdef DEBUG
                DBG_LOG_PRINT(("\n_mmp_lm_view_lst_dev_name_fct BTN_CURSOR_DOWN\n"));
            #endif

                i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                         (VOID*)&e_media_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (MMP_MEDIA_TYPE_AUDIO == e_media_type)
                {
                    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
                    MMP_ASSERT(NULL_HANDLE != h_widget);

                    i4_ret = c_wgl_set_focus(h_widget,
                                                    WGL_ASYNC_AUTO_REPAINT);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else if (MMP_MEDIA_TYPE_VIDEO == e_media_type)
                {
                #ifdef APP_NET_DLNA_SUPPORT
                    if (mmp_be_current_is_dlna_device())
                    {
                    #ifdef DEBUG
                        DBG_LOG_PRINT(("\n_mmp_lm_view_btn_browse_photo_fct,DLNA device\n"));
                    #endif
                        /* if current is DLNA source, do nothing. */
                    }
                    else
                #endif
                    {
                    #ifdef DEBUG
                        DBG_LOG_PRINT(("\n_mmp_lm_view_btn_browse_photo_fct,USB device\n"));
                    #endif
                        i4_ret = c_wgl_set_focus(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT),
                                                 WGL_SYNC_AUTO_REPAINT);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                }
            }
                return MMPR_OK;
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,ui4_msg);
            }
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;

        _mmp_lm_view_side_btn_tts_play();
    }
#endif
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_audio_play_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_audio_play_fct(HANDLE_T    h_widget,
                                                          UINT32      ui4_msg,
                                                          VOID*       pv_param1,
                                                          VOID*       pv_param2)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
    DBG_LOG_PRINT(("[MMP][%s %d] key = 0x%x\n",__FUNCTION__,__LINE__,ui4_key_code));
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            {
                _mmp_lm_view_default_key_handler(AUDIO_PLAYER_BTN_PLAY_PAUSE_2,  ui4_msg);
            }
                return MMPR_OK;

            case BTN_CURSOR_RIGHT:
                _mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT);
                return MMPR_OK;

            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;
    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_audio_back_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_audio_back_fct(HANDLE_T    h_widget,
                                                           UINT32      ui4_msg,
                                                           VOID*       pv_param1,
                                                           VOID*       pv_param2)
{
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            case BTN_PREV:
            {
            #ifdef APP_TTS_SUPPORT
                _mmp_lm_view_side_btn_tts_play();
            #endif
                _mmp_lm_view_default_key_handler(AUDIO_PLAYER_BTN_PREV_2,
                                                 WGL_MSG_KEY_DOWN);
            }
                return MMPR_OK;
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;
    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_audio_forward_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_audio_forward_fct(HANDLE_T    h_widget,
                                                               UINT32      ui4_msg,
                                                               VOID*       pv_param1,
                                                               VOID*       pv_param2)
{
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            case BTN_NEXT:
            {
            #ifdef APP_TTS_SUPPORT
                _mmp_lm_view_side_btn_tts_play();
            #endif
                _mmp_lm_view_default_key_handler(AUDIO_PLAYER_BTN_NEXT_2,
                                                 WGL_MSG_KEY_DOWN);
            }
                return MMPR_OK;

            case BTN_CURSOR_RIGHT:
                _mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT);
                return MMPR_OK;

            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;
    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_browse_photo_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_browse_photo_fct(HANDLE_T    h_widget,
                                                              UINT32      ui4_msg,
                                                              VOID*       pv_param1,
                                                              VOID*       pv_param2)
{
    INT32                   i4_ret = MMPR_OK;
    UINT32  ui4_key_code = (UINT32) pv_param1;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;


    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    HANDLE_T                h_focus = NULL_HANDLE;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            {
            #ifdef APP_CAST_TV_MMP_FG
                pt_this->h_side_p_focus_item = NULL_HANDLE;
                pt_this->ui4_lb_focus_id = 0;
            #endif
                /* set the path to root */
                mmp_be_set_curr_path(NULL);
                /* get current path */
                i4_ret = mmp_be_get_curr_path(s_curr_path,
                                              &z_size);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_get_file_src_type(s_curr_path,
                                                  &e_src_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = c_wgl_get_focus(&h_focus);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE,
                                         (VOID*)(MMP_MEDIA_TYPE_PHOTO));
                MMPR_LOG_ON_FAIL(i4_ret);
                mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_RESUMED, (VOID*)MMP_APP_RESUME_INFO_PHOTO_BWR);
            }
                return MMPR_OK;

            case BTN_CURSOR_RIGHT:
                _mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT);
                return MMPR_OK;

            case BTN_CURSOR_DOWN:
            #ifdef APP_NET_DLNA_SUPPORT
                if (mmp_be_current_is_dlna_device())
                {
                    /* if current is DLNA source, do nothing. */
                }
                else
            #endif
                {
                    i4_ret = c_wgl_set_focus(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT),
                                             WGL_SYNC_AUTO_REPAINT);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                return MMPR_OK;

            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;
    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_sort_setting_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_sort_setting_fct(HANDLE_T    h_widget,
                                                           UINT32      ui4_msg,
                                                           VOID*       pv_param1,
                                                           VOID*       pv_param2)
{
    INT32                   i4_ret = MMPR_OK;
    UINT32  ui4_key_code = (UINT32) pv_param1;
    LISTMODE_VIEW_T *       pt_this = &t_g_listmode_view;

    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;


    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            {
            #ifdef APP_TTS_SUPPORT
                pt_this->ui2_optl_item = MMP_LM_VIEW_OPTL_SORT;
            #endif
                /* get current path */
                i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                /* if source is Net, we did not support more feature */
                if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                   (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                {
                    /*  don't show the sort type in listmode optl */
                }
                else
                {
                    i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                                         WGL_SW_HIDE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                                         WGL_SW_HIDE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = _mmp_lm_view_optl_show(MMP_LM_VIEW_SHOW_SORT);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
                return MMPR_OK;

            case BTN_CURSOR_RIGHT:
                _mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT);
                return MMPR_OK;
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;
    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_btn_view_setting_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_btn_view_setting_fct(HANDLE_T    h_widget,
                                                             UINT32      ui4_msg,
                                                             VOID*       pv_param1,
                                                             VOID*       pv_param2)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T *       pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] key = 0x%x\n",__FUNCTION__,__LINE__,ui4_key_code));
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            {
            #ifdef APP_TTS_SUPPORT
                pt_this->ui2_optl_item = MMP_LM_VIEW_OPTL_VIEW;
            #endif
                /* get current path */
                i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                /* if source is Net, we did not support more feature */
                if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                   (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                {
                    /*  don't show the view type in listmode optl */
                }
                else
                {
                    i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                                         WGL_SW_HIDE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                                         WGL_SW_HIDE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = _mmp_lm_view_optl_show(MMP_LM_VIEW_SHOW_VIEW);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
                return MMPR_OK;

            case BTN_CURSOR_RIGHT:
                _mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT);
                return MMPR_OK;

            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;

    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}


static INT32 _mmp_lm_view_btn_play_setting_fct(HANDLE_T    h_widget,
                                                      UINT32      ui4_msg,
                                                      VOID*       pv_param1,
                                                      VOID*       pv_param2)
{
    LISTMODE_VIEW_T *       pt_this = &t_g_listmode_view;
    UINT32  ui4_key_code = (UINT32) pv_param1;

    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] key = 0x%x\n",__FUNCTION__,__LINE__,ui4_key_code));
        switch (ui4_key_code)
        {
            case BTN_SELECT:
            {
            #ifdef APP_TTS_SUPPORT
                pt_this->ui2_optl_item = MMP_LM_VIEW_OPTL_PLAY;
            #endif
                /* get current path */
                MMPR_LOG_ON_FAIL( mmp_be_get_curr_path(s_curr_path, &z_size));
                MMPR_LOG_ON_FAIL( mmp_be_get_file_src_type(s_curr_path, &e_src_type));

                /* if source is Net, we did not support more feature */
                if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                   (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                {
                    /*  don't show the view type in listmode optl */
                }
                else
                {
                    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,WGL_SW_HIDE));
                    MMPR_LOG_ON_FAIL( _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,WGL_SW_HIDE));
                    MMPR_LOG_ON_FAIL(_mmp_lm_view_optl_show(MMP_LM_VIEW_SHOW_PLAY));
                }
            }
                return MMPR_OK;

            case BTN_CURSOR_RIGHT:
                _mmp_lm_view_set_focus_to_file_lst(WGL_SYNC_AUTO_REPAINT);
                return MMPR_OK;

            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code,  ui4_msg);
            }
                break;
        }
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        pt_this->h_side_p_focus_item = h_widget;

    #ifdef APP_TTS_SUPPORT
        _mmp_lm_view_side_btn_tts_play();
    #endif
    }
    else if (WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        switch (ui4_key_code)
        {
            default:
            {
                _mmp_lm_view_default_key_handler(ui4_key_code, ui4_msg);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static VOID _mmp_lm_view_optl_proc_fct(VOID*    pv_tag,
                                                  UINT32   ui4_msg,
                                                  VOID*    pv_param1,
                                                  VOID*    pv_param2)
{
    INT32               i4_ret = MMPR_OK;
    UINT32              ui4_key_code = (UINT32)pv_param1;
    LISTMODE_VIEW_T*    pt_this = (LISTMODE_VIEW_T*)pv_tag;

    switch(ui4_msg)
    {
        case OPTL_MSG_CANCELLED:
        {
            i4_ret = _mmp_lm_view_show_side_frm();
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case OPTL_MSG_KEY_INPUT:
        {
            switch(ui4_key_code)
            {
                case BTN_EXIT:
                case BTN_RED:
                {
                    i4_ret = _mmp_lm_view_show_side_frm();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                    break;

             #ifdef APP_TTS_SUPPORT
                case BTN_CURSOR_DOWN:
                case BTN_CURSOR_UP:
                {
                    _mmp_lm_view_optl_tts_play(ui4_key_code);
                    break;
                }
            #endif
                default:
                    _mmp_lm_view_default_key_handler(ui4_key_code,
                                                     WGL_MSG_KEY_DOWN);
                    break;
            }
        }
            break;
        case OPTL_MSG_HIDE_TIMEOUT:
        {
            mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                        _mmp_lm_view_optl_time_out,
                                        pt_this,
                                        NULL,
                                        NULL,
                                        NULL);
        }
            break;
#ifdef APP_TTS_SUPPORT
    case OPTL_MSG_ITEM_HIGHLIGHT:
    {
        _mmp_lm_view_optl_back_to_list_tts_play();
        break;
    }
#endif
        default:
            break;
    }
    return;
}

static INT32 _mmp_lm_view_focus_file_info_show(BOOL b_repaint)
{
    INT32               i4_ret = MMPR_OK;
    MMP_MEDIA_TYPE_T    e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
    BOOL                b_visible = FALSE;

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_filter_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (MMP_MEDIA_TYPE_VIDEO == e_filter_type)
    {
        MMP_LM_FILE_STATUS_T e_video_file_status = MMP_LM_FILE_STATUS_NONE;
        i4_ret = mmp_lm_get_file_status_by_idx(ui4_g_file_lbw_hlt_idx,
                                               MMP_MEDIA_TYPE_VIDEO,
                                               &e_video_file_status);
        MMPR_LOG_ON_FAIL(i4_ret);
        DBG_LOG_PRINT(("[MMP][%s %d]e_filter_type = %d,e_video_file_status = %d\n",
                       __FUNCTION__,__LINE__,
                       e_filter_type,e_video_file_status));
        if ((MMP_LM_FILE_IS_PLAYING == e_video_file_status)
            ||(MMP_LM_FILE_IS_PAUSED == e_video_file_status))
        {
            i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,
                                                 WGL_SW_NORMAL);
            MMPR_LOG_ON_FAIL(i4_ret);

            if (b_repaint)
            {
                i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,
                                             FALSE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = _mmp_lm_view_get_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,
                                                 &b_visible);
            MMPR_LOG_ON_FAIL(i4_ret);

            if (b_visible)
            {
                i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,
                                                     WGL_SW_HIDE);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (b_repaint)
                {
                    i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,
                                                 FALSE);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
        }
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_lst_file_list_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static VOID _mmp_lm_view_lst_file_list_nfy (VOID*         pv_tag_nfy,
                                                     const LBW_NOTIFY_T* pt_nfy)
{


    switch (pt_nfy->ui4_nc_code)
    {
        case LBW_NC_HLT:
        {
            if(pt_nfy->u.t_elem_hlt.b_is_hlted)
            {
                ui4_g_file_lbw_hlt_idx = pt_nfy->u.t_elem_hlt.ui4_elem_idx;

            #ifdef APP_TTS_SUPPORT
                HANDLE_T            h_focus = NULL_HANDLE;
                INT32               i4_ret = MMPR_OK;
                LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

                i4_ret = c_wgl_get_focus(&h_focus);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (h_focus == pt_this->h_file_lb)
                {
                    UTF16_T*   w2s_str = mmp_lm_get_file_name_by_idx(ui4_g_file_lbw_hlt_idx % LM_LBW_ELEM_NUM_PER_PAGE);

                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                }

            #endif
               DBG_LOG_PRINT(("[MMP][%s %d] ui4_g_file_lbw_hlt_idx = %d\n",__FUNCTION__,__LINE__,ui4_g_file_lbw_hlt_idx));
               if(LM_STATUS_NORMAL == mmp_lm_get_load_status())
               {
                  MMPR_LOG_ON_FAIL(mmp_lm_view_show_focus_item_info(ui4_g_file_lbw_hlt_idx));
               }
            }
        }
            break;

        case LBW_NC_SEL:
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_default_key_handler
 *
 * Description:respond up key for default action
 *             please see _mmp_lm_view_default_key_handler for more detial
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_default_key_up_handler(UINT32 ui4_key_code,UINT32 ui4_keystatus)
{
    INT32 i4_ret = MMPR_OK;

    switch(ui4_key_code)
    {
        case AUDIO_PLAYER_BTN_FF:
        case AUDIO_PLAYER_BTN_FR:
        {
            MMP_MEDIA_TYPE_T    e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
            MMP_PLAY_STATE_T    e_bk_state = MMP_PLAY_STATE_CLOSED;

            i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,  (VOID*)&e_filter_type);
            IS_MMPR_OK(i4_ret);

            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK, &e_bk_state);
            IS_MMPR_OK(i4_ret);

            if (MMP_MEDIA_TYPE_AUDIO == e_filter_type)
            {
                mmp_lm_update_crnt_playing_file();
                i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_UP);
                IS_MMPR_OK(i4_ret);
            }
        }
        break;
        default:
        {
        }
        break;
    }
    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_default_key_down_handler
 *
 * Description: respond down key for default action
 *              please see _mmp_lm_view_default_key_handler for more detial
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_default_key_down_handler(UINT32 ui4_key_code,UINT32 ui4_keystatus)
{
    INT32 i4_ret = MMPR_OK;

    MMP_MEDIA_TYPE_T    e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
    MMP_PLAY_STATE_T    e_bk_state = MMP_PLAY_STATE_CLOSED;

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,  (VOID*)&e_filter_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK, &e_bk_state);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch(ui4_key_code)
    {
        case BTN_RED:
        case BTN_EXIT:
        {
            i4_ret = _mmp_lm_view_clean_focus_stack();
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = mmp_be_pause_mmp();
            MMPR_LOG_ON_FAIL(i4_ret);
            return MMPR_OK;
        }
            break;
        case BTN_INPUT_SRC:
        {
            i4_ret = a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case BTN_RETURN:
        {
            HANDLE_T    h_widget = NULL_HANDLE;
            h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
            MMP_ASSERT(NULL_HANDLE != h_widget);

            i4_ret = c_wgl_set_focus(h_widget, WGL_SYNC_AUTO_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case AUDIO_PLAYER_BTN_FF:
        case AUDIO_PLAYER_BTN_FR:
        {
            {
                if (MMP_MEDIA_TYPE_AUDIO == e_filter_type)
                {
                    mmp_lm_update_crnt_playing_file();

                }
                else if (MMP_MEDIA_TYPE_VIDEO == e_filter_type)
                {
                    MMP_FP_PRESENT_MODE_T   e_present_mode = MMP_FP_PRESENT_MODE_FULL;

                    mmp_mc_list_get_play_present_mode(&e_present_mode);

                    /* FF, FR trick play */
                    if (MMP_FP_PRESENT_MODE_PREVIEW == e_present_mode)
                    {
                        mmp_mc_browse_fg_key_handler(ui4_key_code, ui4_keystatus);
                        return MMPR_OK;
                    }
                }
            }
            i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case AUDIO_PLAYER_BTN_PLAY:
        case AUDIO_PLAYER_BTN_PAUSE:
        case AUDIO_PLAYER_BTN_STOP_2:
        case BTN_PLAY_PAUSE:
        case AUDIO_PLAYER_BTN_PLAY_PAUSE_2:
        case AUDIO_PLAYER_BTN_STOP:
        {
            if (MMP_MEDIA_TYPE_AUDIO == e_filter_type)
            {
                if ((MMP_PLAY_STATE_CLOSING != e_bk_state) &&
                    (MMP_PLAY_STATE_CLOSED != e_bk_state) &&
                    (MMP_PLAY_STATE_STOPPING != e_bk_state) &&
                    (MMP_PLAY_STATE_STOPPED != e_bk_state))
                {
                    i4_ret = mmp_be_set_focus_item(ui4_g_play_idx);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = _mmp_lm_view_audio_play_first_file();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }

                i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
                MMPR_LOG_ON_FAIL(i4_ret);

                /* process key, refresh ui, then return. */
                return MMPR_OK;
            }
            else if (MMP_MEDIA_TYPE_VIDEO == e_filter_type)
            {
                MMP_FP_PRESENT_MODE_T   e_present_mode = MMP_FP_PRESENT_MODE_FULL;
                mmp_mc_list_get_play_present_mode(&e_present_mode);

                if (MMP_FP_PRESENT_MODE_FULL == e_present_mode)
                {
                    if (AUDIO_PLAYER_BTN_PLAY == ui4_key_code)
                    {
                        i4_ret = _mmp_lm_view_audio_play_first_file();
                        MMPR_LOG_ON_FAIL(i4_ret);

                        /* preview the first video file */
                        i4_ret = mmp_be_preview_crnt_file(i4_ret);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                }
                else if (MMP_FP_PRESENT_MODE_PREVIEW == e_present_mode)
                {
                    if (AUDIO_PLAYER_BTN_STOP_2 == ui4_key_code)
                    {
                #ifdef APP_3D_MODE_SUPPORT
                        BOOL                    b_3d_support = FALSE;
                        a_cfg_custom_plf_opt_get_3d_support(&b_3d_support);
                        if(b_3d_support)
                        {
                            a_cfg_custom_3D_setting_reset_3D_mode();
                        }
                #endif

                        i4_ret = mmp_be_stop_preview();
                        MMPR_LOG_ON_FAIL(i4_ret);

                        i4_ret = mmp_be_set_focus_item(ui4_g_play_idx);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                    else if (AUDIO_PLAYER_BTN_PLAY == ui4_key_code)
                    {
                        mmp_mc_browse_fg_key_handler(ui4_key_code, ui4_keystatus);
                        mmp_lm_update_crnt_playing_file();
                    }
                    else if (AUDIO_PLAYER_BTN_PAUSE == ui4_key_code)
                    {
                        i4_ret = mmp_mc_browse_fg_key_handler(ui4_key_code, ui4_keystatus);
                        MMPR_LOG_ON_FAIL(i4_ret);
                        mmp_lm_update_crnt_playing_file();
                    }
                }
                break;
            }
        }
        default:
        {
            i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_default_key_handler
 *
 * Description:respond key for default action
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: none
 *
 ----------------------------------------------------------------------------*/
static VOID _mmp_lm_view_default_key_handler(UINT32 ui4_key_code,UINT32 ui4_keystatus)
{
    INT32       i4_ret = MMPR_OK;

    if (WGL_MSG_KEY_UP == ui4_keystatus)
    {
       i4_ret =  _mmp_lm_view_default_key_up_handler(ui4_key_code,ui4_keystatus);
       MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (WGL_MSG_KEY_DOWN == ui4_keystatus)
    {
       i4_ret =  _mmp_lm_view_default_key_down_handler(ui4_key_code,ui4_keystatus);
       MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        /* not support*/
    }

}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_file_list_frm
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_file_list_frm(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    UINT32                  ui4_idx = 0;
    LM_DISPLAY_ITEM_REG_T   t_display_info;
    HANDLE_T                h_title_list = NULL_HANDLE;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;

    c_memset(&t_display_info, 0, sizeof(t_display_info));
    i4_ret = mmp_lm_get_cur_display_item_info(&t_display_info);
    MMPR_LOG_ON_FAIL(i4_ret);

    h_title_list = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_TITLE_LIST);
    MMP_ASSERT(NULL_HANDLE != h_title_list);

    i4_ret = c_wgl_do_cmd(h_title_list,
                          WGL_CMD_LB_SET_COL_WIDTH,
                          WGL_PACK(LM_FILE_LB_COL_FILE_NUM_IDX),
                          WGL_PACK(LM_FILE_LB_FILE_NUM_COL_W));
    MMPR_LOG_ON_FAIL(i4_ret);

    _mmp_lm_view_lb_set_item_txt(h_title_list,
                                 LM_FILE_LB_COL_FILE_NUM_IDX,
                                 MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_LM_TITLE_NUM));

    i4_ret = c_wgl_do_cmd(h_title_list,
                          WGL_CMD_LB_SET_COL_WIDTH,
                          WGL_PACK(LM_FILE_LB_COL_FILE_NAME_IDX),
                          WGL_PACK(t_display_info.ui4_name_col_width));
    MMPR_LOG_ON_FAIL(i4_ret);

    _mmp_lm_view_lb_set_item_txt(h_title_list,
                                 LM_FILE_LB_COL_FILE_NAME_IDX,
                                 MLM_MMP_TEXT(pt_this->ui2_lang, t_display_info.ui2_name_col_mlm_idx));

    i4_ret = c_wgl_do_cmd(pt_this->h_file_lb,
                          WGL_CMD_LB_SET_COL_WIDTH,
                          WGL_PACK(LM_FILE_LB_COL_FILE_NAME_IDX),
                          WGL_PACK(t_display_info.ui4_name_col_width));
    MMPR_LOG_ON_FAIL(i4_ret);

    for (ui4_idx = 0; (ui4_idx < t_display_info.ui2_item_cnt) && (ui4_idx < LBW_CUSTOM_COL_MAX_NUM); ui4_idx++)
    {
        i4_ret = c_wgl_do_cmd(h_title_list,
                              WGL_CMD_LB_SET_COL_WIDTH,
                              WGL_PACK(ui4_idx + LM_FILE_LB_FIX_COL_NUM),
                              WGL_PACK(t_display_info.at_item_cfg[ui4_idx].ui4_width));
        MMPR_LOG_ON_FAIL(i4_ret);

        _mmp_lm_view_lb_set_item_txt(h_title_list,
                                     ui4_idx + LM_FILE_LB_FIX_COL_NUM,
                                     MLM_MMP_TEXT(pt_this->ui2_lang, t_display_info.at_item_cfg[ui4_idx].ui2_title_mlm_idx));

        i4_ret = c_wgl_do_cmd(pt_this->h_file_lb,
                              WGL_CMD_LB_SET_COL_WIDTH,
                              WGL_PACK(ui4_idx + LM_FILE_LB_FIX_COL_NUM),
                              WGL_PACK(t_display_info.at_item_cfg[ui4_idx].ui4_width));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    for (ui4_idx = t_display_info.ui2_item_cnt + LM_FILE_LB_FIX_COL_NUM;
         ui4_idx < LM_FILE_LB_COL_MAX_NUM;
         ui4_idx++)
    {
        i4_ret = c_wgl_do_cmd(h_title_list,
                              WGL_CMD_LB_SET_COL_WIDTH,
                              WGL_PACK(ui4_idx),
                              WGL_PACK(0));
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_this->h_file_lb,
                              WGL_CMD_LB_SET_COL_WIDTH,
                              WGL_PACK(ui4_idx),
                              WGL_PACK(0));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_device_name
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_device_name(VOID)

{
    INT32                       i4_ret = MMPR_OK;
    UTF16_T                     w2s_dev_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UTF16_T                     w2s_dev_hint[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    HANDLE_T                    h_widget = NULL_HANDLE;
    UINT32                      ui4_dir_num = 0;
    UINT32                      ui4_active_idx = 0;

    i4_ret = mmp_mc_device_get_mnt_count(&ui4_dir_num);
    if ((MMPR_OK == i4_ret)
        &&(ui4_dir_num > 0))
    {
        i4_ret = mmp_be_get_activate_device_info(w2s_dev_info,
                                                 w2s_dev_hint,
                                                 &ui4_active_idx);
        if (MMPR_OK != i4_ret)
        {
        #ifdef APP_NAV_USB_PLD
            a_nav_active_component(NAV_COMP_ID_USB_PLD);
        #endif
            return MMPR_OK;
        }
    }

    h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    MMP_ASSERT(NULL_HANDLE != h_widget);

    _mmp_lm_view_lb_set_item_txt(h_widget,
                                 0,
                                 w2s_dev_hint);

    _mmp_lm_view_lb_set_item_txt(h_widget,
                                 1,
                                 w2s_dev_info);

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_control_frm
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_control_frm(BOOL b_show)
{
    INT32               i4_ret = MMPR_OK;
    MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_media_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch (e_media_type)
    {
        case MMP_MEDIA_TYPE_AUDIO:
            {
                i4_ret = _mmp_lm_view_set_audio_control_frm(b_show);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_MEDIA_TYPE_VIDEO:
            {
                i4_ret = _mmp_lm_view_set_video_control_frm(b_show);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        default:
            return  MMPR_OK;
    }

    /* update button text of control frame */
    i4_ret = _mmp_lm_view_set_control_btn_txt();
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_audio_control_frm
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_audio_control_frm(BOOL b_show)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    WGL_IMG_INFO_T      t_img_info;
    HANDLE_T            h_widget = NULL_HANDLE;
    MMP_PLAY_STATE_T    e_bk_state = MMP_PLAY_STATE_CLOSED;
    HANDLE_T            h_focus = NULL_HANDLE;

    if (b_show)
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,
                                      WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                             WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                             WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,
                                      WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,
                                         WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set music frame background */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                       = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_basic.t_enable  = h_g_mmp_music_bg_template;
    t_img_info.u_img_data.t_basic.t_disable = h_g_mmp_music_bg_template;
    i4_ret = c_wgl_do_cmd(pt_this->h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set button text */
    _mmp_lm_view_btn_set_txt(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU),
                             MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_MEDIA_TYPE_OPTION_MUSIC));

    _mmp_lm_view_btn_set_txt(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO),
                             MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_LISMODE_VIEW_BROWSE_PHOTO_BTN));

    _mmp_lm_view_text_set_txt(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_TXT_AUDIO_SORT_HINT),
                              MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_THU_MODE_SORT));

    _mmp_lm_view_text_set_txt(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_TXT_AUDIO_VIEW_HINT),
                              MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_THU_MODE_VIEW));

    i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                    &e_bk_state);
    if (MMPR_OK == i4_ret)
    {
        /* update play button state */
        i4_ret = mmp_listmode_view_set_play_btn_state(e_bk_state);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    /* set frame navigation */
    i4_ret = _mmp_lm_view_audio_control_set_nav();
    MMPR_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return MMPR_OK;
    }
#endif

    i4_ret = _mmp_lm_view_pop_focus(&h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

#ifndef APP_CAST_TV_MMP_FG
    if (NULL_HANDLE != h_focus)
#else
    if ((NULL_HANDLE != h_focus) &&
        ((mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY) == h_focus) ||
         (mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO) == h_focus)))
#endif
    {
        i4_ret = c_wgl_set_focus(h_focus,
                                 WGL_ASYNC_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        /* focus on play button */
        h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
        MMP_ASSERT(NULL_HANDLE != h_widget);

        i4_ret = c_wgl_set_focus(h_widget,
                                 WGL_ASYNC_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_video_control_frm
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_video_control_frm(BOOL b_show)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this =&t_g_listmode_view;
    WGL_IMG_INFO_T      t_img_info;
    HANDLE_T            h_widget = NULL_HANDLE;
    HANDLE_T            h_focus = NULL_HANDLE;

    if (b_show)
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,
                                             WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                             WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                             WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,
                                             WGL_SW_HIDE_RECURSIVE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,
                                         WGL_SW_HIDE_RECURSIVE);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set video frame background */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                       = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_basic.t_enable  = h_g_mmp_video_outline;
    t_img_info.u_img_data.t_basic.t_disable = h_g_mmp_video_outline;
    i4_ret = c_wgl_do_cmd(pt_this->h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set button text */
    _mmp_lm_view_btn_set_txt(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU),
                             MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_MEDIA_TYPE_OPTION_VIDEO));

    _mmp_lm_view_text_set_txt(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_TXT_VIDEO_SORT_HINT),
                              MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_THU_MODE_SORT));

    _mmp_lm_view_text_set_txt(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_TXT_VIDEO_VIEW_HINT),
                              MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_THU_MODE_VIEW));

    _mmp_lm_view_text_set_txt(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_TXT_VIDEO_PLAY_HINT),
                              MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_LISMODE_PLAY_MODE_TXT));
    /* set frame navigation */
    i4_ret = _mmp_lm_view_video_control_set_nav();
    MMPR_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return MMPR_OK;
    }
#endif

    i4_ret = _mmp_lm_view_pop_focus(&h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

    if ((NULL_HANDLE != h_focus) && (mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO) != h_focus))
    {
    #ifdef APP_CAST_TV_MMP_FG
        if (h_focus == mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU))
        {
            h_focus = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
        }
    #endif

        i4_ret = c_wgl_set_focus(h_focus,
                                 WGL_ASYNC_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
    #ifdef APP_NET_DLNA_SUPPORT
        /* focus on sort button */
        if (mmp_be_current_is_dlna_device())
        {
            h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
            MMP_ASSERT(NULL_HANDLE != h_widget);
        }
        else
    #endif
        {
            h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
            MMP_ASSERT(NULL_HANDLE != h_widget);
        }

        i4_ret = c_wgl_set_focus(h_widget,
                                 WGL_ASYNC_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_set_control_btn_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_control_btn_txt(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    MMP_SORT_TYPE_T         e_old_sort = MMP_SORT_TYPE_NONE;
    BOOL                    b_is_view_revursive = FALSE;
    UINT8                   ui1_video_play_mode = MMP_PLAY_REPEAT_MODE_NONE;
    INT32                   i4_index = 0;

    MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_type));

    switch (e_type)
    {
        case MMP_MEDIA_TYPE_AUDIO:
        {
            /* get current sort type */
           MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,(VOID*)&e_old_sort));

            switch (e_old_sort)
            {
                case MMP_SORT_TYPE_AUD_ALBUM:
                {
                    i4_index = 0;
                }
                    break;
                case MMP_SORT_TYPE_AUD_INV_ALBUM:
                {
                    i4_index = 1;
                }
                    break;
                case MMP_SORT_TYPE_AUD_ARTIST:
                {
                    i4_index = 2;
                }
                    break;
                case MMP_SORT_TYPE_AUD_INV_ARTIST:
                {
                    i4_index = 3;
                }
                    break;
                case MMP_SORT_TYPE_AUD_NAME:
                {
                    i4_index = 4;
                }
                    break;
                case MMP_SORT_TYPE_AUDIO_INV_NAME:
                {
                    i4_index = 5;
                }
                    break;
                default:
                    break;
            }
            _mmp_lm_view_btn_set_txt(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT),
                MLM_MMP_TEXT(pt_this->ui2_lang, i4_index + MLM_MMP_KEY_LISMODE_VIEW_SORT_ALBUM_A_Z));

            /* get current view type */
            i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,
                                    (VOID*)&b_is_view_revursive);
            MMPR_LOG_ON_FAIL(i4_ret);

            if (b_is_view_revursive)
            {
                i4_index = 0;
            }
            else
            {
                i4_index = 1;
            }
            _mmp_lm_view_btn_set_txt(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_VIEW),
                MLM_MMP_TEXT(pt_this->ui2_lang, i4_index + MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL));
        }
            break;

        case MMP_MEDIA_TYPE_VIDEO:
        {
            /* get current sort type */
            i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                                    (VOID*)&e_old_sort);
            MMPR_LOG_ON_FAIL(i4_ret);

            switch (e_old_sort)
            {
                case MMP_SORT_TYPE_VIDEO_INV_DATE:
                    i4_index = 0;
                    break;
                case MMP_SORT_TYPE_VIDEO_DATE:
                    i4_index = 1;
                    break;
                case MMP_SORT_TYPE_VIDEO_NAME:
                    i4_index = 2;
                    break;
                case MMP_SORT_TYPE_VIDEO_INV_NAME:
                    i4_index = 3;
                    break;
                default:
                    break;
            }

            _mmp_lm_view_btn_set_txt(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT),
                                     MLM_MMP_TEXT(pt_this->ui2_lang, i4_index + MLM_MMP_KEY_LISMODE_VIEW_SORT_DATE_NEW_OLD));

            /* get current view type */
            MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,(VOID*)&b_is_view_revursive));

            if (b_is_view_revursive)
                i4_index = 0;
            else
                i4_index = 1;

            _mmp_lm_view_btn_set_txt(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW),
                                     MLM_MMP_TEXT(pt_this->ui2_lang, i4_index + MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL));
            MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE,(VOID*)&ui1_video_play_mode));
            _mmp_lm_view_btn_set_txt(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_PLAY),
                                     MLM_MMP_TEXT(pt_this->ui2_lang, (ui1_video_play_mode == MMP_PLAY_REPEAT_MODE_NONE) ?
                                     MLM_MMP_KEY_LISMODE_PLAY_MODE_ONCE : MLM_MMP_KEY_LISMODE_PLAY_MODE_CONTINUOUSLY));
        }
        break;

    default:
        break;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_audio_control_set_nav
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_audio_control_set_nav(VOID)
{
    HANDLE_T            h_widget = NULL_HANDLE;
    WGL_KEY_LINK_T      at_link[4];

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    at_link[0].ui4_key  = BTN_CURSOR_DOWN;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE);
    at_link[1].ui4_key  = BTN_CURSOR_RIGHT;
    c_wgl_set_navigation(h_widget, 2, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE);
    at_link[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[2].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[2].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_BACK);
    at_link[1].ui4_key  = BTN_CURSOR_DOWN;
    at_link[2].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[2].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_BACK);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_FORWARD);
    at_link[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[2].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_FORWARD);
    at_link[2].ui4_key  = BTN_CURSOR_DOWN;
    at_link[3].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[3].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 4, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_FORWARD);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_BACK);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_BACK);
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    at_link[2].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO);
    at_link[2].ui4_key  = BTN_CURSOR_DOWN;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_FORWARD);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 2, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_VIEW);
    at_link[1].ui4_key  = BTN_CURSOR_DOWN;
    at_link[2].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[2].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_VIEW);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 2, at_link);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_video_control_set_nav
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_video_control_set_nav(VOID)
{
    HANDLE_T            h_widget = NULL_HANDLE;
    WGL_KEY_LINK_T      at_link[4];

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    at_link[0].ui4_key  = BTN_CURSOR_DOWN;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE);
    at_link[1].ui4_key  = BTN_CURSOR_RIGHT;
    c_wgl_set_navigation(h_widget, 2, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE);
    at_link[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[2].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[2].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW);
    at_link[1].ui4_key  = BTN_CURSOR_DOWN;
    at_link[2].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[2].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    at_link[2].h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_PLAY);
    at_link[2].ui4_key  = BTN_CURSOR_DOWN;
    c_wgl_set_navigation(h_widget, 3, at_link);

    c_memset(at_link, 0, 4*sizeof(WGL_KEY_LINK_T));
    h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_PLAY);
    MMP_ASSERT(NULL_HANDLE != h_widget);
    at_link[0].h_widget = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW);
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[1].h_widget = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU);
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    c_wgl_set_navigation(h_widget, 2, at_link);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_audio_play_first_file
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_audio_play_first_file(VOID)
{
    INT32               i4_ret = MMPR_OK;
    INT32               i4_index = 0;
    UINT32              ui4_first_file_num = 0;
    UINT32              ui4_file_num = 0;
    MMP_ITEM_TYPE_T     e_item_type = ITEM_TYPE_NONE;

    i4_ret = mmp_listmode_view_get_first(&ui4_first_file_num);
    MMPR_LOG_ON_FAIL(i4_ret);

    for (i4_index = 0; i4_index < LM_LBW_ELEM_NUM_PER_PAGE; i4_index++)
    {
        ui4_file_num = ui4_first_file_num + i4_index;
        e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,
                                                  ui4_file_num);

        if (ITEM_TYPE_FILE == e_item_type)
        {
            i4_ret = mmp_be_set_focus_item(ui4_file_num);
            MMPR_LOG_ON_FAIL(i4_ret);

            if (MMPR_OK == i4_ret)
            {
                break;
            }
        }
    }

    return ui4_file_num;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_dev_list_setting
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_dev_list_setting(VOID* pv_tag)
{
    INT32               i4_ret = MMPR_OK;
    UINT32              ui4_active_idx = 0;
    SIZE_T              z_size = MMP_DEV_NAME_MAX_LEN;
    CHAR                s_mnt_name[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    BOOL                b_is_recursive = FALSE;

    i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_active_idx,
                                                &z_size,
                                                s_mnt_name);
    MMPR_LOG_ON_FAIL(i4_ret);

    if((UINT32)pv_tag != ui4_active_idx)
    {
        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SET_ACT_MNT_POINT,
                                 (VOID*)pv_tag);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT,
                                MMP_BE_REFRESH_TYPE_ITEM_LST);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,
                                (VOID*)&b_is_recursive);;
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_lm_view_set_view_mode(b_is_recursive);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_lm_view_set_control_btn_txt();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_set_device_name();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_listmode_view_set_folder_path();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_show_side_frm();
    MMPR_LOG_ON_FAIL(i4_ret);

    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_set_dev_list_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_set_dev_list_item(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    UINT32                  ui4_mnt_count = 0;
    UINT32                  ui4_idx = 0;
    UINT32                  ui4_cnt = 0;
    UINT32                  ui4_usb_id = 0;
    UINT32                  ui4_dlna_id = 0;
    OPTL_ITEM_T             t_optl_item[MMP_DEV_LIST_MAX_NUM];
    RMV_DEV_DEVICE_STATUS_T e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    OPTL_ITEM_DEF_T         t_optl_item_def = {0};
    BOOL                    b_next = FALSE;
    UTF16_T*                pw2s_optl_dev_info = NULL;
    UTF16_T*                pw2s_optl_dev_hint = NULL;
    UTF16_T*                pw2s_optl_dev_info_temp = NULL;
    UTF16_T*                pw2s_optl_dev_hint_temp = NULL;

    do
    {
        pw2s_optl_dev_info = (UTF16_T*)c_mem_alloc(
                              MMP_DEV_LIST_MAX_NUM*(MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));
        if (NULL == pw2s_optl_dev_info)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,c_mem_alloc fail\n",
                        __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MMPR_OUT_OF_MEM;
            break;
        }

        pw2s_optl_dev_hint = (UTF16_T*)c_mem_alloc(
                              MMP_DEV_LIST_MAX_NUM*(MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));
        if (NULL == pw2s_optl_dev_hint)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,c_mem_alloc fail\n",
                        __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MMPR_OUT_OF_MEM;
            break;
        }

        c_memset(pw2s_optl_dev_info, 0,
                 MMP_DEV_LIST_MAX_NUM*(MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));
        c_memset(pw2s_optl_dev_hint, 0,
                 MMP_DEV_LIST_MAX_NUM*(MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));

        /* get device number */
        i4_ret = mmp_mc_device_get_mnt_count(&ui4_mnt_count);
        MMPR_LOG_ON_FAIL(i4_ret);

        for (ui4_idx = 0, ui4_cnt = 0;
             (ui4_idx < ui4_mnt_count) && (ui4_idx < MMP_DEV_LIST_MAX_NUM);
             ui4_idx++)
        {
            pw2s_optl_dev_info_temp = pw2s_optl_dev_info + ((MMP_DEV_NAME_MAX_LEN + 1) * ui4_cnt);
            pw2s_optl_dev_hint_temp = pw2s_optl_dev_hint + ((MMP_DEV_NAME_MAX_LEN + 1) * ui4_cnt);

            c_memset(pw2s_optl_dev_info_temp, 0,
                     (MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));
            i4_ret = mmp_be_get_device_info(ui4_idx,
                                            pw2s_optl_dev_info_temp,
                                            &e_dev_status,
                                            &b_next);
            if (MMPR_OK != i4_ret)
            {
                continue;
            }

            if (b_next)
            {
                continue;
            }

            if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
            {
                if (FALSE == a_is_DLNA_enable())
                {
                    continue;
                }

                ui4_dlna_id++;

                c_memset(pw2s_optl_dev_hint_temp, 0,
                         (MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));
                i4_ret = mmp_be_get_dlna_serial_name(ui4_dlna_id,
                                                     pw2s_optl_dev_hint_temp);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                ui4_usb_id++;

                c_memset(pw2s_optl_dev_hint_temp, 0,
                         (MMP_DEV_NAME_MAX_LEN+1)*sizeof(UTF16_T));
                i4_ret = mmp_be_get_usb_serial_name(ui4_idx,
                                                    pw2s_optl_dev_hint_temp);
                MMPR_LOG_ON_FAIL(i4_ret);
            }

            t_optl_item[ui4_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
            t_optl_item[ui4_cnt].pw2s_text = pw2s_optl_dev_info_temp;
            t_optl_item[ui4_cnt].pw2s_label = pw2s_optl_dev_hint_temp;
            t_optl_item[ui4_cnt].b_is_disable = FALSE;
            t_optl_item[ui4_cnt].u.t_action.pv_tag = (VOID*)ui4_idx;
            t_optl_item[ui4_cnt].u.t_action.pf_fct = _mmp_lm_view_optl_dev_list_setting;
            ui4_cnt += 1;
        }

        MMP_ASSERT(ui4_cnt < MMP_DEV_LIST_MAX_NUM);

        t_optl_item_def.pt_opt_item = t_optl_item;
        t_optl_item_def.ui2_num_of_opt_items = (UINT16)ui4_cnt;
        t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_THUMB_LB_SOURCE);

        i4_ret = a_optl_set_option_items(pt_this->h_option_list, &t_optl_item_def);
        MMPR_LOG_ON_FAIL(i4_ret);
    }while(0);

    if (pw2s_optl_dev_info)
    {
        c_mem_free(pw2s_optl_dev_info);
        pw2s_optl_dev_info = NULL;
    }

    if (pw2s_optl_dev_hint)
    {
        c_mem_free(pw2s_optl_dev_hint);
        pw2s_optl_dev_hint = NULL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_show(MMP_LM_VIEW_SHOW_TYPE e_show_type)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    HANDLE_T            h_focus = NULL_HANDLE;

    i4_ret = c_wgl_get_focus(&h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_push_focus(h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch (e_show_type)
    {
        case MMP_LM_VIEW_SHOW_DEV_LST:
        {
            i4_ret = _mmp_lm_view_optl_set_dev_list_item();
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->ui1_attr |= MMP_LM_VIEW_ATTR_DEV_LST_SHOW;
        }
            break;

        case MMP_LM_VIEW_SHOW_SORT:
        {
            i4_ret = _mmp_lm_view_optl_set_sort_item();
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->ui1_attr |= MMP_LM_VIEW_ATTR_SORT_MODE_SHOW;
        }
            break;

        case MMP_LM_VIEW_SHOW_VIEW:
        {
            i4_ret = _mmp_lm_view_optl_set_view_item();
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->ui1_attr |= MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW;
            break;
        }
        case MMP_LM_VIEW_SHOW_PLAY:
        {
           MMPR_LOG_ON_FAIL(_mmp_lm_view_optl_set_play_item());
            pt_this->ui1_attr |= MMP_LM_VIEW_ATTR_PLAY_MODE_SHOW;
        }
            break;

        default:
            break;
    }

    i4_ret = c_wgl_insert (pt_this->h_option_list,
                           pt_this->h_main_frm,
                           WGL_INSERT_AFTER,
                           WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_option_list,
                             WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_show(pt_this->h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_lm_view_set_sort_mode
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_sort_mode(MMP_SORT_TYPE_T      e_mode)
{
    INT32               i4_ret = MMPR_OK;

    i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SORT_TYPE,
                            (VOID*)e_mode);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_set_control_btn_txt();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static VOID _refresh_file_lst(VOID*                       pv_tag1,
                              VOID*                       pv_tag2,
                              VOID*                       pv_tag3,
                              VOID*                       pv_tag4)
{
    MMPR_LOG_ON_FAIL( mmp_be_refresh(MMP_BE_FF_IDX_CRT,
                                     MMP_BE_REFRESH_TYPE_ITEM_LST));
}

/*----------------------------------------------------------------------------
 * Name: _mmp_listmode_view_optl_sort_setting
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_listmode_view_optl_sort_setting(VOID* pv_tag)
{
    MMP_SORT_TYPE_T         e_new_sort = MMP_SORT_TYPE_NONE;
    MMP_SORT_TYPE_T         e_old_sort = MMP_SORT_TYPE_NONE;
    UINT32                  ui4_index = (UINT32)pv_tag;
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    MMP_MSG_XNG_PARAM_T     t_msg_param;

    c_memset(&t_msg_param, 0, sizeof(MMP_MSG_XNG_PARAM_T));

    MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_type));

    MMP_LM_RC_GET_SORT_TYPE(e_type,
                            ui4_index,
                            e_new_sort);

    MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                            (VOID*)&e_old_sort));

    MMP_DBG_INFO(("\n%s,%d,ui4_index=%d,e_new_sort=%d,e_old_sort=%d\n",
                    __FILE__, __LINE__, ui4_index, (UINT32)e_new_sort, (UINT32)e_old_sort));

    if(e_old_sort != e_new_sort)
    {
        MMPR_LOG_ON_FAIL(_mmp_lm_view_set_sort_mode(e_new_sort));
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _refresh_file_lst,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
    }

    MMPR_LOG_ON_FAIL(_mmp_lm_view_show_side_frm());
    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_set_sort_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_set_sort_item(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    OPTL_ITEM_DEF_T         t_optl_item_def = {0};
    OPTL_ITEM_T             t_optl_item[LM_OPTL_ITEM_MAX_NUM];
    UINT8                   ui1_index = 0;
    UINT8                   ui1_cnt = 0;
    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    UINT16                  ui2_hlt_idx = 0;
    MMP_SORT_TYPE_T         e_sort_type = MMP_SORT_TYPE_NONE;
    MMP_SORT_TYPE_T         e_crnt_sort = MMP_SORT_TYPE_NONE;
#ifdef APP_TTS_SUPPORT
    UTF16_T                 w2s_str[128] = {0};
#endif

    c_memset(&t_optl_item, 0, LM_OPTL_ITEM_MAX_NUM*sizeof(OPTL_ITEM_T));

    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_file_src_type(s_curr_path,
                                      &e_src_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* 1. Sort   set the item about sort type option list */
    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
    {
        /*  don't show the sort type in listmode optl */
    }
    else
    {
        /* Get focus index according to filter type*/
        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                 (VOID*)&e_type);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                                 (VOID*)&e_crnt_sort);
        MMPR_LOG_ON_FAIL(i4_ret);

        switch (e_type)
        {
            case MMP_MEDIA_TYPE_AUDIO:
            {
                /*sub item sort mode  */
                for(ui1_index = 0; ui1_index < LM_OPTL_AU_SORT_NUM; ui1_index++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang,
                                                     MLM_MMP_KEY_LISMODE_VIEW_SORT_ALBUM_A_Z + ui1_index);
                    t_optl_item[ui1_cnt].b_is_disable = FALSE;
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_index;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_listmode_view_optl_sort_setting;

                    /*Get highlight index*/
                    MMP_LM_RC_GET_SORT_TYPE(e_type, ui1_cnt, e_sort_type);
                    if (e_sort_type == e_crnt_sort)
                    {
                        ui2_hlt_idx = ui1_cnt;
                    #ifdef APP_TTS_SUPPORT
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_SORT_ALBUM_A_Z + ui2_hlt_idx));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                    }

                    ui1_cnt += 1;
                }
            }
                break;

            case MMP_MEDIA_TYPE_VIDEO:
            {
                /*sub item sort mode  */
                for(ui1_index = 0; ui1_index < LM_OPTL_VD_SORT_NUM; ui1_index++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang,
                                                     MLM_MMP_KEY_LISMODE_VIEW_SORT_DATE_NEW_OLD + ui1_index);
                    t_optl_item[ui1_cnt].b_is_disable = FALSE;
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_index;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_listmode_view_optl_sort_setting;

                    /*Get highlight index*/
                    MMP_LM_RC_GET_SORT_TYPE(e_type, ui1_cnt, e_sort_type);
                    if (e_sort_type == e_crnt_sort)
                    {
                        ui2_hlt_idx = ui1_cnt;
                    #ifdef APP_TTS_SUPPORT
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_SORT_DATE_NEW_OLD + ui2_hlt_idx));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                    }

                    ui1_cnt += 1;
                }
            }
                break;
            default:
                return MMPR_OK;
        }
    }

    MMP_ASSERT(ui1_cnt < LM_OPTL_ITEM_MAX_NUM);

    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui1_cnt;
    t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui2_lang,
                                              MLM_MMP_KEY_THUMB_OPTL_TITLE_SORT);

    i4_ret = a_optl_set_option_items(pt_this->h_option_list,
                                     &t_optl_item_def);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(pt_this->h_option_list,
                                  ui2_hlt_idx,
                                  0);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_lm_view_set_view_mode
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_view_mode(BOOL b_is_recursive)
{
    INT32 i4_ret = MMPR_OK;

#ifdef APP_NET_DLNA_SUPPORT
    if (mmp_be_current_is_dlna_device())
    {
        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,
                                (VOID*)(UINT32)0);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
#endif
    {
        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,
                                (VOID*)(UINT32)b_is_recursive);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_lm_view_set_control_btn_txt();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_view_setting
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_view_setting(VOID* pv_tag)
{
    UINT32                  ui4_index = (UINT32)pv_tag;
    BOOL                    b_new_is_recursive = FALSE;
    BOOL                    b_old_is_recursive = FALSE;

    b_new_is_recursive = (0 == ui4_index) ? TRUE : FALSE;

    MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,
                            (VOID*)&b_old_is_recursive));

    if(b_new_is_recursive != b_old_is_recursive)
    {
        MMPR_LOG_ON_FAIL(_mmp_lm_view_set_view_mode(b_new_is_recursive));

        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _refresh_file_lst,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
    }

    MMPR_LOG_ON_FAIL( _mmp_lm_view_show_side_frm());
    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_set_view_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_optl_set_view_item()
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    OPTL_ITEM_DEF_T         t_optl_item_def = {0};
    OPTL_ITEM_T             t_optl_item[LM_OPTL_ITEM_MAX_NUM] = {{0}};
    UINT8                   ui1_index = 0;
    UINT8                   ui1_cnt = 0;
    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    UINT16                  ui2_hlt_idx = 0;
    BOOL                    b_is_recursive = FALSE;

    /* get current path */
    i4_ret = mmp_be_get_curr_path(s_curr_path,
                                  &z_size);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_file_src_type(s_curr_path,
                                      &e_src_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* 1. Sort   set the item about sort type option list */
    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
    {
        /*  don't show the sort type in listmode optl */
    }
    else
    {
        /* Get focus index according to filter type*/
        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                 (VOID*)&e_type);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,
                                (VOID*)&b_is_recursive);
        MMPR_LOG_ON_FAIL(i4_ret);

        if(b_is_recursive)
        {
            ui2_hlt_idx = 0;
        }
        else
        {
            ui2_hlt_idx = 1;
        }

        switch (e_type)
        {
            case MMP_MEDIA_TYPE_AUDIO:
            {
                /* sub item sort mode  */
                for(ui1_index = 0; ui1_index < LM_OPTL_AU_VIEW_NUM; ui1_index++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang,
                                                     MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL + ui1_index);
                    t_optl_item[ui1_cnt].b_is_disable = FALSE;
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_index;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_lm_view_optl_view_setting;
                    ui1_cnt += 1;
                }
            }
                break;

            case MMP_MEDIA_TYPE_VIDEO:
            {
                /* sub item sort mode  */
                for(ui1_index = 0; ui1_index < LM_OPTL_VD_VIEW_NUM; ui1_index++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang,
                                                     MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL + ui1_index);
                    t_optl_item[ui1_cnt].b_is_disable = FALSE;
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_index;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_lm_view_optl_view_setting;
                    ui1_cnt += 1;
                }
            }
                break;
            default:
                return MMPR_OK;
        }
    }

    MMP_ASSERT(ui1_cnt < LM_OPTL_ITEM_MAX_NUM);

    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui1_cnt;
    t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui2_lang,
                                              MLM_MMP_KEY_THUMB_OPTL_TITLE_VIEW);

    i4_ret = a_optl_set_option_items(pt_this->h_option_list, &t_optl_item_def);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(pt_this->h_option_list, ui2_hlt_idx, 0);
    MMPR_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    c_uc_w2s_strcpy(w2s_str, MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL + ui2_hlt_idx));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

    return MMPR_OK;
}

static INT32 _mmp_lm_view_optl_play_setting(VOID* pv_tag)
{
    UINT32                  ui4_index = (UINT32)pv_tag;
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    UINT8                   ui1_play_mode = 0;


    if(ui4_index < LM_OPTL_VD_PLAY_NUM)
    {
        DBG_LOG_PRINT(("[MMP][%s %d],ui4_index = %d\n",__FUNCTION__,__LINE__,ui4_index));
        MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_type));
        MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE,&ui1_play_mode));
        switch (e_type)
        {
            case MMP_MEDIA_TYPE_AUDIO:
            {
#if 0
                if (0 == ui4_index)
                    b_new_is_recursive = TRUE;
                else
                    b_new_is_recursive = FALSE;
#endif
            }
            break;

            case MMP_MEDIA_TYPE_VIDEO:
            {
                DBG_LOG_PRINT(("[MMP][%s %d],ui4_index = %d",__FUNCTION__,__LINE__,ui4_index));
                {
                    MMP_PL_ATTR_T     at_attr[1];
                    MMP_REPEAT_MODE_T rept = MMP_PLAY_REPEAT_MODE_ONE == ui4_index ? MMP_REPEAT_MODE_ONE :
                                             MMP_PLAY_REPEAT_MODE_ALL == ui4_index ? MMP_REPEAT_MODE_ALL :
                                             MMP_PLAY_REPEAT_MODE_ONE_ONCE == ui4_index ? MMP_REPEAT_MODE_ONE_ONCE : MMP_REPEAT_MODE_NONE;

                    at_attr[0].e_id = MMP_PL_ATTR_ID_VIDEO_REPEAT;
                    at_attr[0].pv_param = (VOID*)rept;
                    mmp_mc_list_set_attr(1, at_attr);
                }
                MMPR_LOG_ON_FAIL( mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SET_VIDEO_PLAY_MODE,(VOID*)ui4_index));
                ui4_index = 0xff;
                MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE,&ui4_index));
                DBG_LOG_PRINT(("[MMP][%s %d]get ui4_index = %d\n",__FUNCTION__,__LINE__,ui4_index));
            }
            break;

            default:
                break;
        }
    }

    MMPR_LOG_ON_FAIL(_mmp_lm_view_show_side_frm());
    return  MMPR_OK;
}

static INT32 _mmp_lm_view_optl_set_play_item()
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    OPTL_ITEM_DEF_T         t_optl_item_def = {0};
    OPTL_ITEM_T             t_optl_item[LM_OPTL_ITEM_MAX_NUM] = {{0}};
    UINT8                   ui1_index = 0;
    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    MMP_MEDIA_TYPE_T        e_type = MMP_MEDIA_TYPE_UNKNOWN;
    UINT16                  ui2_hlt_idx = 0;
    UINT8                   ui1_play_mode = 0;

    DBG_LOG_PRINT(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));

    /* 1. Sort   set the item about sort type option list */
    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
    {
        /*  don't show the sort type in listmode optl */
    }
    else
    {
        /* Get focus index according to filter type*/
        MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                 (VOID*)&e_type));

        MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE, &ui1_play_mode));

        ui2_hlt_idx = ui1_play_mode;

        switch (e_type)
        {
            case MMP_MEDIA_TYPE_AUDIO:
            {//current we not support
#if 0
                /* sub item sort mode  */
                for(ui1_index = 0; ui1_index < LM_OPTL_AU_VIEW_NUM; ui1_index++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang,
                                                     MLM_MMP_KEY_LISMODE_VIEW_VIEW_ALL + ui1_index);
                    t_optl_item[ui1_cnt].b_is_disable = FALSE;
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_index;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_lm_view_optl_view_setting;
                    ui1_cnt += 1;
                }
#endif
            }
                break;

            case MMP_MEDIA_TYPE_VIDEO:
            {
                /* sub item sort mode  */
                for(ui1_index = 0; ui1_index < LM_OPTL_VD_PLAY_NUM; ui1_index++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_index].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang,
                                                     MLM_MMP_KEY_LISMODE_PLAY_MODE_ONCE+ ui1_index);
                    t_optl_item[ui1_index].b_is_disable = FALSE;
                    t_optl_item[ui1_index].u.t_action.pv_tag = (VOID*)(UINT32)ui1_index;
                    t_optl_item[ui1_index].u.t_action.pf_fct = _mmp_lm_view_optl_play_setting;
                }
            }
                break;
            default:
                return MMPR_OK;
        }
    }

    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = LM_OPTL_VD_PLAY_NUM;
    t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui2_lang,
                                              MLM_MMP_KEY_THUMB_OPTL_TITLE_VIEW);
    i4_ret = a_optl_set_option_items(pt_this->h_option_list, &t_optl_item_def);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(pt_this->h_option_list, ui2_hlt_idx, 0);
    MMPR_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    c_uc_w2s_strcpy(w2s_str, MMP_TTS_TEXT(MLM_MMP_KEY_LISMODE_PLAY_MODE_ONCE + ui2_hlt_idx));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_optl_time_out
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_lm_view_optl_time_out(VOID*      pv_tag1,
                                                  VOID*      pv_tag2,
                                                  VOID*      pv_tag3,
                                                  VOID*      pv_tag4)
{
    INT32       i4_ret;
    i4_ret = _mmp_lm_view_show_side_frm();
    MMPR_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_create_optl
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_create_optl(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    OPTL_INIT_T         t_optl_init = {0};

    do
    {
        /* Create option list widget */
        t_optl_init.h_parent         = pt_this->h_main_frm;
        t_optl_init.t_gui_rc.i4_left = 0;
        t_optl_init.t_gui_rc.i4_top  = 0;
        t_optl_init.ui4_style_mask   = OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT;
        t_optl_init.pv_tag           = pt_this;
        t_optl_init.pf_fct           = _mmp_lm_view_optl_proc_fct;
        t_optl_init.ui4_custom_flag  = 0;
        t_optl_init.ui4_sleep_time   = LM_OPTION_LIST_TIMER;

        i4_ret = a_optl_create(&t_optl_init, &pt_this->h_option_list);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;
    }
    while(0);

    i4_ret = a_optl_destroy(pt_this->h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_create_file_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_create_file_list(HANDLE_T    h_parent,
                                                    a_lbw_req_data_fct     pf_lbw_req_data_fct,
                                                    HANDLE_T*              ph_lb_handle)
{
    INT32                       i4_ret = MMPR_OK;
    GL_RECT_T                   t_rc_lb;
    WGL_LB_COL_INIT_T           at_lb_col_init[LM_FILE_LB_COL_MAX_NUM];
    LBW_INIT_T                  t_lbw_init;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem_info;
    UINT32                      ui4_idx;
	GL_COLOR_T                  t_color_txt      = MMP_LM_RC_GET_LISTMODE_TXT();
	GL_COLOR_T                  t_color_txt_oled = MMP_LM_RC_GET_LISTMODE_TXT_OLED();
	
    c_memset(&t_rc_lb, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rc_lb,
                     LM_FILE_LB_X,
                     LM_FILE_LB_Y,
                     LM_FILE_LB_W,
                     LM_FILE_LB_H);

    c_memset(at_lb_col_init, 0, sizeof(at_lb_col_init));

    /* file num column attribute */
    at_lb_col_init[LM_FILE_LB_COL_FILE_NUM_IDX].e_col_type = LB_COL_TYPE_TEXT;
    at_lb_col_init[LM_FILE_LB_COL_FILE_NUM_IDX].ui1_align = WGL_AS_CENTER_CENTER;
    at_lb_col_init[LM_FILE_LB_COL_FILE_NUM_IDX].ui2_width = LM_FILE_LB_FILE_NUM_COL_W;
    at_lb_col_init[LM_FILE_LB_COL_FILE_NUM_IDX].ui2_max_text_len = LM_FILE_LB_FILE_NUM_MAX_BIT + 1;

    /* icon column attribute */
    at_lb_col_init[LM_FILE_LB_COL_ICON_IDX].e_col_type = LB_COL_TYPE_IMG;
    at_lb_col_init[LM_FILE_LB_COL_ICON_IDX].ui1_align  = WGL_AS_CENTER_CENTER;
    at_lb_col_init[LM_FILE_LB_COL_ICON_IDX].ui2_width  = (UINT16)(LM_FILE_LB_ICON_COL_W |
                                                                  WGL_LB_COL_WIDTH_STL_AUTO |
                                                                  WGL_LB_COL_WIDTH_STL_COMPACT);

    at_lb_col_init[LM_FILE_LB_COL_FILE_NAME_IDX].ui1_align        = WGL_AS_LEFT_CENTER;
    at_lb_col_init[LM_FILE_LB_COL_FILE_NAME_IDX].e_col_type       = LB_COL_TYPE_TEXT;
    at_lb_col_init[LM_FILE_LB_COL_FILE_NAME_IDX].ui2_max_text_len = LM_FILE_LB_COL_DEFAULT_LEN;
    at_lb_col_init[LM_FILE_LB_COL_FILE_NAME_IDX].ui2_width        = LM_FILE_LB_COL_DEFAULT_W;

    at_lb_col_init[LM_FILE_LB_COL_NULL_ICON_IDX].e_col_type = LB_COL_TYPE_IMG;
    at_lb_col_init[LM_FILE_LB_COL_NULL_ICON_IDX].ui1_align  = WGL_AS_CENTER_CENTER;
    at_lb_col_init[LM_FILE_LB_COL_NULL_ICON_IDX].ui2_width  = (UINT16)(LM_FILE_LB_ICON_COL_W |
                                                                  WGL_LB_COL_WIDTH_STL_AUTO |
                                                                  WGL_LB_COL_WIDTH_STL_COMPACT);

    for (ui4_idx = LM_FILE_LB_COL_NULL_ICON_IDX + 1; ui4_idx < LM_FILE_LB_COL_MAX_NUM; ui4_idx++)
    {
        /* file info column attribute */
        at_lb_col_init[ui4_idx].ui1_align        = WGL_AS_LEFT_CENTER;
        at_lb_col_init[ui4_idx].e_col_type       = LB_COL_TYPE_TEXT;
        at_lb_col_init[ui4_idx].ui2_max_text_len = LM_FILE_LB_COL_DEFAULT_LEN;
        at_lb_col_init[ui4_idx].ui2_width        = LM_FILE_LB_COL_DEFAULT_W;
    }

    c_memset(&t_lbw_init, 0, sizeof(LBW_INIT_T));
    t_lbw_init.ui4_style                    = LBW_STL_PAGE_MODE |
                                              LBW_STL_NO_WRAP_OVER |
                                              LBW_STL_DISABLE_MULSELE;
    t_lbw_init.pv_tag_req_data              = NULL;
    t_lbw_init.pf_req_data                  = pf_lbw_req_data_fct;
    t_lbw_init.pv_tag_nfy                   = NULL;
    t_lbw_init.pf_nfy                       = _mmp_lm_view_lst_file_list_nfy;
    t_lbw_init.ui1_num_col                  = LM_FILE_LB_COL_MAX_NUM;
    t_lbw_init.at_cols_fmt                  = at_lb_col_init;
    t_lbw_init.ui2_elem_size                = LM_FILE_LB_LBW_ELEM_SIZE;
    t_lbw_init.ui2_elem_distance            = 0;
    t_lbw_init.ui4_num_elem_per_page        = LM_LBW_ELEM_NUM_PER_PAGE;
    t_lbw_init.ui4_hlt_margin               = 0;

    t_lbw_init.t_key_map.ui4_key_next       = 0;
    t_lbw_init.t_key_map.ui4_key_prev       = 0;
    t_lbw_init.t_key_map.ui4_key_select     = 0;
    t_lbw_init.t_key_map.ui4_key_page_up    = BTN_CURSOR_LEFT;
    t_lbw_init.t_key_map.ui4_key_page_down  = BTN_CURSOR_RIGHT;

    i4_ret = a_lbw_create (h_parent,
                           WGL_CONTENT_LIST_BOX_DEF,
                           WGL_BORDER_NULL,
                           &t_rc_lb,
                           _mmp_lm_view_lst_file_list_fct,
                           255,
                           &t_lbw_init,
                           NULL,
                           ph_lb_handle);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set text font and color */
    for (ui4_idx = 0; ui4_idx < LM_FILE_LB_COL_MAX_NUM; ui4_idx++)
    {
        if ((LM_FILE_LB_COL_ICON_IDX == ui4_idx) ||
            (LM_FILE_LB_COL_NULL_ICON_IDX == ui4_idx))
        {
            continue;
        }

        /* set text font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name,
                  SN_FONT_DEFAULT_SMALL,
                  WGL_MAX_FONT_NAME);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (*ph_lb_handle,
                                WGL_CMD_LB_SET_COL_FONT,
                                WGL_PACK(ui4_idx),
                                WGL_PACK(&t_fnt_info));
        MMPR_LOG_ON_FAIL(i4_ret);

        /* set text color */
        c_memset(&t_lb_color, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
		if (a_is_oled_compensation_support())
		{
	        t_lb_color.t_normal            = t_color_txt_oled;
	        t_lb_color.t_disable           = t_color_txt_oled;
	        t_lb_color.t_highlight         = t_color_txt_oled;
	        t_lb_color.t_highlight_unfocus = t_color_txt_oled;
	        t_lb_color.t_pushed            = t_color_txt_oled;
	        t_lb_color.t_selected          = t_color_txt_oled;
	        t_lb_color.t_selected_disable  = t_color_txt_oled;
		}
		else
		{
			t_lb_color.t_normal            = t_color_txt;
	        t_lb_color.t_disable           = t_color_txt;
	        t_lb_color.t_highlight         = t_color_txt;
	        t_lb_color.t_highlight_unfocus = t_color_txt;
	        t_lb_color.t_pushed            = t_color_txt;
	        t_lb_color.t_selected          = t_color_txt;
	        t_lb_color.t_selected_disable  = t_color_txt;
		}

        i4_ret = c_wgl_do_cmd (*ph_lb_handle,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2(ui4_idx, WGL_CLR_TEXT),
                               WGL_PACK(&t_lb_color));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    c_memset(&t_hlt_elem_effect, 0, sizeof(WGL_LB_HLT_ELEM_EFFECT_T));
    t_hlt_elem_effect.ui4_style              = WGL_LB_HEF_STL_ENLARGE_SIZE |
                                               WGL_LB_HEF_STL_PUT_ABOVE_VP;
    t_hlt_elem_effect.t_ex_margin.ui2_left   = 0;
    t_hlt_elem_effect.t_ex_margin.ui2_top    = 0;
    t_hlt_elem_effect.t_ex_margin.ui2_right  = 0;
    t_hlt_elem_effect.t_ex_margin.ui2_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_lb_handle,
                           WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                           WGL_PACK(&t_hlt_elem_effect),
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* set elem background image*/
    c_memset(&t_img_elem_info, 0, sizeof(WGL_LB_IMG_ELEM_SET_T));
    t_img_elem_info.h_normal            = NULL_HANDLE;
    t_img_elem_info.h_selected          = NULL_HANDLE;
    t_img_elem_info.h_disable           = NULL_HANDLE;
    t_img_elem_info.h_highlight         = h_g_mmp_lst_hlt;
    t_img_elem_info.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem_info.h_pushed            = NULL_HANDLE;
    t_img_elem_info.h_selected_disable  = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_lb_handle,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(&t_img_elem_info),
                          NULL);

    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_create_main_frame
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_create_main_frame(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    DBG_LOG_PRINT(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));
    /* register main frame callback function */
    i4_ret = mmp_lm_custom_reg_wgt_cb(WID_MMP_LM_CUSTOM_FRM_LM_MAIN_FRM,
                                     _mmp_lm_view_frm_main_frm_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register back to side frame button callback function */
    i4_ret = mmp_lm_custom_reg_wgt_cb(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE,
                                     _mmp_lm_view_btn_back_to_side_fct);

    /* register back to menu button callback function */
    i4_ret = mmp_lm_custom_reg_wgt_cb(WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU,
                                     _mmp_lm_view_btn_back_to_menu_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register device name showing list box callback function */
    i4_ret = mmp_lm_custom_reg_wgt_cb(WID_MMP_LM_CUSTOM_LB_DEV_NAME,
                                     _mmp_lm_view_lst_dev_name_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* create main frame ui */
    i4_ret = mmp_lm_custom_create_ui(pt_this->h_canvas);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* initializ the main frame variables */
    pt_this->h_main_frm = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_MAIN_FRM);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_main_frm);

    pt_this->h_side_frm = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_SIDE_PANEL);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_side_frm);

    pt_this->h_info_frm = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_INFO_PANEL);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_info_frm);

    pt_this->h_list_frm = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_FILE_LIST);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_list_frm);

    pt_this->h_control_frm = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_CONTROL);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_control_frm);

    /* register audio play button callback function */
    i4_ret = mmp_audio_control_reg_wgt_cb(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY,
                                          _mmp_lm_view_btn_audio_play_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register audio play back button callback function */
    i4_ret = mmp_audio_control_reg_wgt_cb(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_BACK,
                                          _mmp_lm_view_btn_audio_back_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register audio play forward button callback function */
    i4_ret = mmp_audio_control_reg_wgt_cb(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_FORWARD,
                                          _mmp_lm_view_btn_audio_forward_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register browse photo button callback function */
    i4_ret = mmp_audio_control_reg_wgt_cb(WID_MMP_AUDIO_CONTROL_BTN_BROWSER_PHOTO,
                                          _mmp_lm_view_btn_browse_photo_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register sort setting button callback function */
    i4_ret = mmp_audio_control_reg_wgt_cb(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_SORT,
                                          _mmp_lm_view_btn_sort_setting_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register view setting button callback function */
    i4_ret = mmp_audio_control_reg_wgt_cb(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_VIEW,
                                          _mmp_lm_view_btn_view_setting_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* create audio control frame ui */
    i4_ret = mmp_audio_control_create_ui(pt_this->h_control_frm);
    MMPR_LOG_ON_FAIL(i4_ret);

    pt_this->h_audio_ctrl_frm = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_FRM_AUDIO_CONTROL_FRM);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_audio_ctrl_frm);

    /* register sort setting button of video control callback function */
    i4_ret = mmp_video_control_reg_wgt_cb(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT,
                                          _mmp_lm_view_btn_sort_setting_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register view setting button of video control frame callback function */
    i4_ret = mmp_video_control_reg_wgt_cb(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_VIEW,
                                          _mmp_lm_view_btn_view_setting_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register play setting button of video control frame callback function */
    i4_ret = mmp_video_control_reg_wgt_cb(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_PLAY,
                                          _mmp_lm_view_btn_play_setting_fct);
    MMPR_LOG_ON_FAIL(i4_ret);
    /* create video control frame ui */
    i4_ret = mmp_video_control_create_ui(pt_this->h_control_frm);
    MMPR_LOG_ON_FAIL(i4_ret);

    pt_this->h_video_ctrl_frm = mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_FRM_VIDEO_CONTROL_FRM);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_video_ctrl_frm);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_view_show_side_frm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_show_side_frm(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T *   pt_this = &t_g_listmode_view;
    HANDLE_T            h_focus = NULL_HANDLE;
    MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

    MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_media_type));

    MMPR_LOG_ON_FAIL( _mmp_lm_view_set_control_btn_txt());
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                         WGL_SW_NORMAL));

    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                         WGL_SW_NORMAL));

    if (MMP_MEDIA_TYPE_AUDIO == e_media_type)
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,
                                      WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (MMP_MEDIA_TYPE_VIDEO == e_media_type)
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,
                                      WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if ((pt_this->ui1_attr & MMP_LM_VIEW_ATTR_DEV_LST_SHOW) ||
        (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_SORT_MODE_SHOW) ||
        (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW) ||
        (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_PLAY_MODE_SHOW))
    {
        pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_DEV_LST_SHOW;
        pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_SORT_MODE_SHOW;
        pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW;
         pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_PLAY_MODE_SHOW;
        /*Hide option list*/
        i4_ret = a_optl_hide(pt_this->h_option_list);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                     TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_lm_view_pop_focus(&h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (NULL_HANDLE != h_focus)
    {
        c_wgl_set_focus(h_focus,
                        WGL_ASYNC_AUTO_REPAINT);
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    _mmp_lm_view_get_wgl_handle
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static HANDLE_T _mmp_lm_view_get_wgl_handle(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_ret)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    HANDLE_T   h_handle = NULL_HANDLE;

    switch(e_repaint_ret)
    {
        case MMP_LM_RC_REPAINT_RECT_ID_FILE_LB:
            h_handle = pt_this->h_file_lb;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_MAIN_FRM:
            h_handle = pt_this->h_main_frm;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM:
            h_handle = pt_this->h_side_frm;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM:
            h_handle = pt_this->h_control_frm;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_INFO_FRM:
            h_handle = pt_this->h_info_frm;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO:
           h_handle = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_VIDEO_INFO);;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_AUDIO_INFO:
            h_handle = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_AUDIO_INFO);;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_PAGE_INFO_LST:
            h_handle = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_PAGE_INFO_LIST);
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_BTN_AUDIO_PLAY:
            h_handle = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_FOLDER_PATH_TXT:
            h_handle = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_TXT_FOLDER_PATH_TXT);
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_FOLDER_NAME:
            h_handle = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_TXT_FOLDER_NAME);
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM:
            h_handle = pt_this->h_audio_ctrl_frm;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM:
            h_handle = pt_this->h_video_ctrl_frm;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_OPT_LIST:
            h_handle = pt_this->h_option_list;
            break;
        case MMP_LM_RC_REPAINT_RECT_ID_TO_SIDE_BAR:
            h_handle = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE);
            break;
        default: break;
    }

    return h_handle;
}

/*-----------------------------------------------------------------------------
 * Name:    _mmp_lm_view_set_visibility
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_rect,
                                                  WGL_SW_CMD_T                e_type)
{
    HANDLE_T    h_widget = NULL_HANDLE;

    //DBG_LOG_PRINT(("[MMP][%s %d] e_repaint_rect = %d,e_type = %d\n",__FUNCTION__,__LINE__,e_repaint_rect,e_type));

    h_widget = _mmp_lm_view_get_wgl_handle(e_repaint_rect);
    MMP_ASSERT(NULL_HANDLE != h_widget);

    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(h_widget,e_type));
    MMPR_LOG_ON_FAIL(c_wgl_repaint(h_widget,NULL,TRUE));

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    _mmp_lm_view_get_visibility
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_get_visibility(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_rect,
                                                  BOOL*                       pb_visible)
{
    INT32       i4_ret   = MMPR_OK;
    HANDLE_T    h_widget = NULL_HANDLE;

    if (!pb_visible)
    {
        return MMPR_INV_ARG;
    }

    h_widget =  _mmp_lm_view_get_wgl_handle(e_repaint_rect);
    MMP_ASSERT(NULL_HANDLE != h_widget);

    i4_ret = c_wgl_get_visibility(h_widget,
                                  pb_visible);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_lm_view_repaint
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_T e_repaint_ret,
                                   BOOL                        b_sync)
{
    INT32               i4_ret = MMPR_OK;
    HANDLE_T            h_widget = NULL_HANDLE;

    h_widget= _mmp_lm_view_get_wgl_handle(e_repaint_ret);

#ifndef APP_CAST_TV_MMP
    MMP_ASSERT(NULL_HANDLE != h_widget);
#endif

    i4_ret = c_wgl_repaint(h_widget,
                           NULL,
                           b_sync);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_lm_view_set_view_sort_mode
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_view_set_view_sort_mode(VOID)
{
    MMP_MEDIA_TYPE_T    e_type = MMP_MEDIA_TYPE_UNKNOWN;
    INT32               i4_ret = MMPR_OK;
    MMP_SORT_TYPE_T     e_mode = MMP_SORT_TYPE_NONE;
    UINT8               ui1_val = 0;

    i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SET_PATH_FLAG,
                             (VOID*)MMP_FF_SET_PATH_FLAG_EMPTY);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_type);
    MMPR_LOG_ON_FAIL(i4_ret);

#ifdef APP_NET_DLNA_SUPPORT
    if (mmp_be_current_is_dlna_device())
    {
        if (MMP_MEDIA_TYPE_VIDEO == e_type)
        {
            a_cfg_custom_get_mmp_video_sort((UINT8*)&e_mode);
        }
        else
        {
            a_cfg_custom_get_mmp_audio_sort((UINT8*)&e_mode);
        }
    }
    else
#endif
    {
        if (MMP_MEDIA_TYPE_VIDEO == e_type)
        {
            a_cfg_custom_get_mmp_video_recur_parsing(&ui1_val);
            a_cfg_custom_get_mmp_video_sort((UINT8*)&e_mode);
            if ((e_mode < MMP_SORT_TYPE_VIDEO_TYPE)
                ||(e_mode > MMP_SORT_TYPE_VIDEO_INV_NAME))
            {
                e_mode = MMP_SORT_TYPE_VIDEO_INV_DATE;
            }
        }
        else
        {
            a_cfg_custom_get_mmp_audio_recur_parsing(&ui1_val);
            a_cfg_custom_get_mmp_audio_sort((UINT8*)&e_mode);
            if ((e_mode < MMP_SORT_TYPE_AUD_NAME)
                ||(e_mode > MMP_SORT_TYPE_AUDIO_INV_DATE))
            {
                e_mode = MMP_SORT_TYPE_AUD_ALBUM;
            }
        }
    }

    i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,
                            (VOID*)(UINT32)ui1_val);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SORT_TYPE,
                            (VOID*)e_mode);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_pause_lose_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_pause_lose_focus(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    BOOL                b_is_visible = FALSE;
    HANDLE_T            h_focus = NULL_HANDLE;

    i4_ret = c_wgl_get_visibility(pt_this->h_main_frm,
                                  &b_is_visible);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (b_is_visible)
    {
        i4_ret = mmp_listmode_view_hide_animation();
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_get_focus(&h_focus);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_lm_view_push_focus(h_focus);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_resume_get_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_resume_get_focus(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;
    HANDLE_T            h_focus = NULL_HANDLE;

    if ((pt_this->ui1_attr & MMP_LM_VIEW_ATTR_DEV_LST_SHOW)
        ||(pt_this->ui1_attr & MMP_LM_VIEW_ATTR_SORT_MODE_SHOW)
        ||(pt_this->ui1_attr & MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW))
    {
        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                             WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                             WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_lm_view_pop_focus(&h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_media_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch (e_media_type)
    {
        case MMP_MEDIA_TYPE_AUDIO:
        {
            if (NULL_HANDLE != h_focus)
            {
                i4_ret = c_wgl_set_focus(h_focus,
                                         WGL_SYNC_AUTO_REPAINT);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_set_focus(mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY),
                                         WGL_SYNC_AUTO_REPAINT);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
            break;

        case MMP_MEDIA_TYPE_VIDEO:
        {
            if (NULL_HANDLE != h_focus)
            {
                i4_ret = c_wgl_set_focus(h_focus,
                                         WGL_SYNC_AUTO_REPAINT);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            else
            {
            #ifdef APP_NET_DLNA_SUPPORT
                if (mmp_be_current_is_dlna_device())
                {
                    i4_ret = c_wgl_set_focus(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME),
                                             WGL_SYNC_AUTO_REPAINT);
                    MMPR_LOG_ON_FAIL(i4_ret);
                    pt_this->h_side_p_focus_item = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_DEV_NAME);
                }
                else
            #endif
                {
                    i4_ret = c_wgl_set_focus(mmp_video_control_get_wgt_hdl(WID_MMP_VIDEO_CONTROL_BTN_VIDEO_SORT),
                                             WGL_SYNC_AUTO_REPAINT);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
        }
            break;

        default:
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_set_play_btn_state
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_set_play_btn_state(MMP_PLAY_STATE_T   e_bk_state)
{
    INT32                   i4_ret = MMPR_OK;
    WGL_HIMG_TPL_T          h_img_play = NULL_HANDLE;
    HANDLE_T                h_play_btn = NULL_HANDLE;
    WGL_IMG_INFO_T          t_img_info;

    if ((MMP_PLAY_STATE_PLAYING == e_bk_state)||
        (MMP_PLAY_STATE_PLAYED == e_bk_state)||
        (MMP_PLAY_STATE_OPENING == e_bk_state)||
        (MMP_PLAY_STATE_PLAY_NEXTING == e_bk_state)||
        (MMP_PLAY_STATE_FAST_FORWARDED == e_bk_state)||
        (MMP_PLAY_STATE_FAST_REWINDED == e_bk_state))
    {
        i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_LM_PAUSE, &h_img_play);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_LM_PLAY, &h_img_play);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    h_play_btn = mmp_audio_control_get_wgt_hdl(WID_MMP_AUDIO_CONTROL_BTN_AUDIO_PLAY);
    MMP_ASSERT(NULL_HANDLE != h_play_btn);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_play;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_play;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_play;
    i4_ret = c_wgl_do_cmd(h_play_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_listmode_view_set_folder_path
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 mmp_listmode_view_set_folder_path(VOID)
{
    UTF16_T                 w2s_full_path[MMP_BE_MAX_PATH_LEN + 1] = {0};
    UTF16_T*                pw2s_folder_name = NULL;
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    INT32                   i4_ret;
    HANDLE_T                h_folder_name_txt = NULL_HANDLE;
    HANDLE_T                h_full_path_txt = NULL_HANDLE;

    /* get path from browser engine */
    i4_ret = mmp_be_get_curr_path_display(w2s_full_path,
                                          &pw2s_folder_name,
                                          &z_size);
    MMPR_LOG_ON_FAIL(i4_ret);

    h_full_path_txt = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_TXT_FOLDER_PATH_TXT);
    MMP_ASSERT(NULL_HANDLE != h_full_path_txt);

    _mmp_lm_view_text_set_txt(h_full_path_txt,
                              w2s_full_path);

    h_folder_name_txt = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_TXT_FOLDER_NAME);
    MMP_ASSERT(NULL_HANDLE != h_folder_name_txt);

    _mmp_lm_view_text_set_txt(h_folder_name_txt,
                              pw2s_folder_name);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_listmode_view_lbw_reload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_lbw_reload(UINT32   ui4_num_total,
                                   UINT32   ui4_idx_hlt,
                                   BOOL     b_repaint)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    LBW_RLD_VP_INFO_T   t_vp_info;
    UINT32 ui4_total = 0;
    UINT32 ui4_hlt = LBW_NULL_INDEX;

    a_lbw_get_elem_num(pt_this->h_file_lb,&ui4_total);
    a_lbw_get_hlt_idx(pt_this->h_file_lb,&ui4_hlt);
    DBG_LOG_PRINT(("\n%s,%s,%d,ui4_total=%d, ui4_hlt = %d\n",
                     __FILE__, __FUNCTION__, __LINE__,
                     ui4_total,
                     ui4_hlt));

    DBG_LOG_PRINT(("\n%s,%s,%d,ui4_num_total=%d,ui4_idx_hlt=%d,b_repaint=%d\n",
                 __FILE__, __FUNCTION__, __LINE__,
                 ui4_num_total, ui4_idx_hlt, b_repaint));
    if (ui4_num_total > 0)
    {
        t_vp_info.e_hlt_opt = LBW_RLD_HLT_OPT_RESET_IDX;
        t_vp_info.u_hlt_opt.t_reset_hlt_idx.ui4_idx_hlt = (ui4_idx_hlt < ui4_num_total) ? ui4_idx_hlt : 0;
    }
    else
    {
        t_vp_info.e_hlt_opt = LBW_RLD_HLT_OPT_KEEP_IDX;
    }

    return a_lbw_reload (pt_this->h_file_lb, ui4_num_total, &t_vp_info, b_repaint);

}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_dev_num_xng_proc
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_dev_num_xng_proc(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    if (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_DEV_LST_SHOW)
    {
        /* reset device list */
        i4_ret = _mmp_lm_view_optl_set_dev_list_item();
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = a_optl_repaint(pt_this->h_option_list);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_dev_remove_proc
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_dev_remove_proc(VOID)
{
    INT32               i4_ret = MMPR_OK;

    i4_ret = _mmp_lm_view_set_device_name();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_show_side_frm();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_listmode_view_hide_animation();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_dev_mnt_xng_proc
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_dev_mnt_xng_proc(VOID)
{
    INT32               i4_ret = MMPR_OK;

    i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT,
                            MMP_BE_REFRESH_TYPE_ITEM_LST);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_set_device_name();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_listmode_view_set_folder_path();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_lm_view_show_side_frm();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_dev_change_focus
 *
 * Description:when dev changed if current folder is empty then set focus to
 * back_to_side button
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/

INT32 mmp_listmode_view_dev_change_focus(VOID)
{
    HANDLE_T            h_focus = NULL_HANDLE;
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    i4_ret = c_wgl_get_focus(&h_focus);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (h_focus == pt_this->h_file_lb)
    {
        i4_ret = c_wgl_set_focus(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE),
                                 WGL_ASYNC_AUTO_REPAINT);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_do_anim_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static VOID _mmp_lm_do_anim_nfy(VOID*      pv_tag1,
                                          VOID*      pv_tag2,
                                          VOID*      pv_tag3,
                                          VOID*      pv_tag4)
{
    INT32     i4_ret = MMPR_OK;

    i4_ret = mmp_common_ui_animation_start(1, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_anim_cb_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_anim_cb_fct(HANDLE_T                h_widget,
                                          UINT16                  ui2_anim_type,
                                          WGL_ANIM_COND_INF_T     e_anim_cond,
                                          VOID*                   pv_tag)
{
    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_lm_do_anim_nfy,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_show_animation
 *
 * Description: if menu mmp coexist now, no animation.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_show_animation(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return MMPR_OK;
    }
#endif

    i4_ret = mmp_common_ui_animation_start(1, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    pt_this->ui1_attr |= MMP_LM_VIEW_ATTR_ANIMATION;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_hide_animation
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_hide_animation(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    i4_ret = mmp_common_ui_animation_stop();
    MMPR_LOG_ON_FAIL(i4_ret);

    pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_ANIMATION;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_listmode_view_get_first
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 mmp_listmode_view_get_first(UINT32 * pui4_first)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    return a_lbw_vp_get_first(pt_this->h_file_lb, pui4_first);
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_listmode_view_get_last
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 mmp_listmode_view_get_last(UINT32 * pui4_last)
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    return a_lbw_vp_get_last(pt_this->h_file_lb, pui4_last);
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_listmode_view_show_focus_file_info
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 mmp_listmode_view_show_focus_file_info(VOID)
{
    UINT32         ui4_focus_idx = 0;

    MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FOCUS_ITEM_IDX,
                             &ui4_focus_idx));

    MMP_DBG_INFO(("\n%s,%s,%d,ui4_focus_idx=%d\n",
                 __FILE__, __FUNCTION__, __LINE__, ui4_focus_idx));

    MMPR_LOG_ON_FAIL(a_lbw_reload_partial(t_g_listmode_view.h_file_lb,
                                          ui4_focus_idx,
                                          ui4_focus_idx,
                                          LBW_RPNT_MODE_PARTIAL_RPNT));
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_listmode_view_set_play_file_info
 *
 * Description:
 *
 * Input:   -
 *
 * Output:  -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 mmp_listmode_view_set_play_file_info(VOID)
{
    INT32                           i4_ret = MMPR_OK;
    MMP_FP_INFO_HDLR_INIT_PARAM_T   t_param;
    GL_RECT_T                       t_rect = {0};
    MMP_MEDIA_TYPE_T                e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
    HANDLE_T                        h_video_info = NULL_HANDLE;
    HANDLE_T                        h_audio_info = NULL_HANDLE;
    MMP_PLAY_STATE_T                e_bk_state = MMP_PLAY_STATE_CLOSED;

    MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_filter_type));

    if(MMP_MEDIA_TYPE_VIDEO == e_filter_type)
    {
        MMP_PLAY_STATE_T e_fg_state = MMP_PLAY_STATE_CLOSED;
        i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_FORE,&e_fg_state);
        MMPR_LOG_ON_FAIL(i4_ret);
        DBG_LOG_PRINT(("[%s %d] status = %d\n",__FUNCTION__,__LINE__,e_fg_state));
        if(MMP_PLAY_STATE_CLOSED != e_fg_state)
        {
        SET_RECT_BY_SIZE (&t_rect,
                          LM_FILE_VIDEO_INFO_HANDLE_X,
                          LM_FILE_VIDEO_INFO_HANDLE_Y,
                          LM_FILE_VIDEO_INFO_HANDLE_W,
                          LM_FILE_VIDEO_INFO_HANDLE_H);

        h_video_info = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_VIDEO_INFO);
        MMP_ASSERT(NULL_HANDLE != h_video_info);

        c_memset (&t_param, 0, sizeof (MMP_FP_INFO_HDLR_INIT_PARAM_T));
        t_param.e_ui_type = MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS;
        t_param.e_media_type = MMP_MEDIA_TYPE_VIDEO;
        t_param.h_parent = h_video_info;
        t_param.pt_rect = &t_rect;

        {
            BOOL     b_visible = FALSE;

            MMPR_LOG_ON_FAIL( _mmp_lm_view_get_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,&b_visible));
            if (!b_visible)
            {
                MMPR_LOG_ON_FAIL( _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,WGL_SW_NORMAL));
            }
        }

        MMPR_LOG_ON_FAIL( mmp_mc_browse_display_play_item_info(&t_param));
        }
    }
    else
    {
        SET_RECT_BY_SIZE (&t_rect,
                          LM_FILE_INFO_HANDLE_X,
                          LM_FILE_INFO_HANDLE_Y,
                          LM_FILE_INFO_HANDLE_W,
                          LM_FILE_INFO_HANDLE_H);

        h_audio_info = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_AUDIO_INFO);
        MMP_ASSERT(NULL_HANDLE != h_audio_info);

        t_param.e_ui_type = MMP_FP_INFO_HDLR_UI_TYPE_LM_ACT_BK;
        t_param.e_media_type = MMP_MEDIA_TYPE_AUDIO;
        t_param.h_parent = h_audio_info;
        t_param.pt_rect = &t_rect;

        i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_INFO,
                                             WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                        &e_bk_state);
        if ((MMPR_OK == i4_ret) &&
            (MMP_PLAY_STATE_CLOSING != e_bk_state) &&
            (MMP_PLAY_STATE_CLOSED != e_bk_state) &&
            (MMP_PLAY_STATE_STOPPING != e_bk_state) &&
            (MMP_PLAY_STATE_STOPPED != e_bk_state))
        {
            i4_ret = mmp_mc_browse_display_play_item_info(&t_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_listmode_view_set_page_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_set_page_info(BOOL b_repaint)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*        pt_this = &t_g_listmode_view;
    HANDLE_T                h_page_list = NULL_HANDLE;
    UINT32                  ui4_hlt_idx = 0;
    UINT32                  ui4_ele_num = 0;
    UINT32                  ui4_page_num = 0;
    UINT32                  ui4_cur_page = 0;
    HANDLE_T                h_left_img = NULL_HANDLE;
    HANDLE_T                h_right_img = NULL_HANDLE;
    CHAR                    ac_page_info[MMP_BE_MAX_PAGE_INFO_LEN + 1] = {0};
    CHAR                    ac_dest_page_info[MMP_BE_MAX_PAGE_INFO_LEN + 1] = {0};
    UTF16_T                 w2s_page_info[MMP_BE_MAX_PAGE_INFO_LEN + 1] = {0};

    i4_ret = a_lbw_get_elem_num(pt_this->h_file_lb,
                                &ui4_ele_num);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (0 != ui4_ele_num)
    {
        ui4_page_num = (ui4_ele_num + LM_LBW_ELEM_NUM_PER_PAGE-1)/LM_LBW_ELEM_NUM_PER_PAGE;

        i4_ret =  a_lbw_get_hlt_idx(pt_this->h_file_lb, &ui4_hlt_idx);
        MMPR_LOG_ON_FAIL(i4_ret);

        ui4_cur_page = (ui4_hlt_idx + LM_LBW_ELEM_NUM_PER_PAGE)/LM_LBW_ELEM_NUM_PER_PAGE;

        i4_ret = c_uc_w2s_to_ps(MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_MMP_PAGE_INFO_TEMP),
                                ac_page_info,
                                sizeof(ac_page_info));
        MMPR_LOG_ON_FAIL(i4_ret);
        c_snprintf(ac_dest_page_info,(SIZE_T)(MMP_BE_MAX_PAGE_INFO_LEN + 1), ac_page_info, ui4_cur_page, ui4_page_num);
        c_uc_ps_to_w2s(ac_dest_page_info, w2s_page_info, sizeof(w2s_page_info));

        if (ui4_cur_page < ui4_page_num)
        {
            h_right_img = h_g_mmp_pg_next_icon_nr;
        }
        else
        {
            h_right_img = h_g_mmp_pg_next_icon_dim;
        }

        if (ui4_cur_page > 1)
        {
            h_left_img = h_g_mmp_pg_back_icon_nr;
        }
        else
        {
            h_left_img = h_g_mmp_pg_back_icon_dim;
        }
    }

    h_page_list = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_PAGE_INFO_LIST);
    MMP_ASSERT(NULL_HANDLE != h_page_list);

    _mmp_lm_view_lb_set_item_txt(h_page_list,
                                 MMP_LIST_PAGE_TXT_IDX,
                                 w2s_page_info);

    i4_ret = c_wgl_do_cmd (h_page_list,
                           WGL_CMD_LB_SET_ITEM_IMAGE,
                           WGL_PACK_2 (0, MMP_LIST_PAGE_LEFT_IDX),
                           WGL_PACK (h_left_img));
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (h_page_list,
                           WGL_CMD_LB_SET_ITEM_IMAGE,
                           WGL_PACK_2 (0, MMP_LIST_PAGE_RIGHT_IDX),
                           WGL_PACK (h_right_img));
    MMPR_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_PAGE_INFO_LST,
                                     TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_OK;
    }

    if ((ui4_cur_page == pt_this->ui4_current_page)
        &&(ui4_page_num == pt_this->ui4_page_cnt))
    {
        /* do not need to repaint */
        return MMPR_OK;
    }
    else
    {
        pt_this->ui4_current_page = ui4_cur_page;
        pt_this->ui4_page_cnt = ui4_page_num;

        i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_PAGE_INFO_LST,
                                     TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_lm_view_exit_bg_mode
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_exit_bg_mode(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;

    i4_ret = c_wgl_set_focus(pt_this->h_file_lb,
                             WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    return  i4_ret;
}

WGL_HIMG_TPL_T mmp_lm_view_get_image(UINT8  ui1_img_type)
{
    WGL_HIMG_TPL_T      h_img = NULL_HANDLE;

     switch (ui1_img_type)
     {
         case MMP_LM_VIEW_IMG_TYPE_IMG_PLAY:
             MMPR_LOG_ON_FAIL(mmp_img_get_img(MMP_IMG_IMAGE_ID_LM_PLAY,&h_img));
             break;
         case MMP_LM_VIEW_IMG_TYPE_IMG_PAUSE:
             MMPR_LOG_ON_FAIL(mmp_img_get_img(MMP_IMG_IMAGE_ID_LM_PAUSE,&h_img));
             break;
         case MMP_LM_VIEW_IMG_TYPE_IMG_NULL:
             h_img = h_g_mmp_null_icon;
             break;
         case MMP_LM_VIEW_IMG_TYPE_IMG_FOLDER:
             h_img = h_g_mmp_lg_folder_icon_small;
             break;
         case MMP_LM_VIEW_IMG_TYPE_IMG_PRE_FOLDER:
             h_img = h_g_mmp_previous_folder_icon_small;
             break;
         default:
             h_img = NULL_HANDLE;
             break;
     }
     return h_img;
}

/*----------------------------------------------------------------------------
 * Name:
 *          mmp_listmode_view_init
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_init(a_lbw_req_data_fct         pf_file_lb_req_data_fct)
{
    INT32                   i4_ret = MMPR_OK;
    LISTMODE_VIEW_T *       pt_this = &t_g_listmode_view;
    WGL_FONT_INFO_T         t_fnt_info;
    HANDLE_T                h_page_list = NULL_HANDLE;

    c_memset (&t_g_listmode_view, 0, sizeof (LISTMODE_VIEW_T));
#ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
    c_memset(&t_g_last_focus_stack, 0, sizeof(LM_LAST_FOCUS_STACK_T));
#else
    c_memset(&t_g_last_focus, 0, sizeof(LM_LAST_FOCUS_T));
#endif

    /* get canvas */
    pt_this->h_canvas = mmp_main_get_canvas();

	if (a_is_oled_compensation_support())
	{
		t_g_mmp_white = t_g_mmp_white_oled;
	}
	
    do
    {
        /* init image */
        i4_ret = mmp_img_init();
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /* create main frm */
        i4_ret = _mmp_lm_view_create_main_frame();
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /* create file list box */
        i4_ret = _mmp_lm_view_create_file_list(pt_this->h_list_frm,
                                               pf_file_lb_req_data_fct,
                                               &pt_this->h_file_lb);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /* create option list */
        i4_ret = _mmp_lm_view_create_optl();
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /* init Font of page list */
        h_page_list = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_LB_PAGE_INFO_LIST);
        MMP_ASSERT(NULL_HANDLE != h_page_list);

        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name,
                  SN_FONT_DEFAULT_SMALL,
                  WGL_MAX_FONT_NAME);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.ui1_custom_size  = 18;
        i4_ret = c_wgl_do_cmd (h_page_list,
                               WGL_CMD_LB_SET_COL_FONT,
                               WGL_PACK((UINT8)1),
                               WGL_PACK(&t_fnt_info));
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_DEV_LST_SHOW;

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        MMP_MC_BWSR_SETTING_T       t_bwsr_setting;
        t_bwsr_setting.ui4_mask = MMP_MC_BWSR_SETTING_MSK_DEF_FCS_WGT;
        t_bwsr_setting.h_def_focus_widget = pt_this->h_file_lb;

        i4_ret = mmp_mc_set_browser_setting(MMP_RC_BROWSER_ID_LIST,
                                            &t_bwsr_setting);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif

    #ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
        i4_ret = _mmp_lm_view_init_focus_stack();
        if(MMPR_OK != i4_ret)
        {
            break;
        }
    #endif
        t_g_listmode_view.ui4_hlt = MMP_NULL_FILE_IDX;
        return MMPR_OK;
    } while(0);

    mmp_listmode_view_deinit();

    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_listmode_view_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID mmp_listmode_view_deinit(VOID)
{
    INT32                       i4_ret = MMPR_OK;
    LISTMODE_VIEW_T *           pt_this = &t_g_listmode_view;

#ifdef MMP_LM_DYNAMIC_CREATE_FOCUS_STACK
    _mmp_lm_view_destroy_focus_stack();
#endif

    i4_ret = a_lbw_destroy(pt_this->h_file_lb);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_destroy(pt_this->h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(NULL_HANDLE != pt_this->h_main_frm)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->h_main_frm);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_main_frm = NULL_HANDLE;
    }

    i4_ret = mmp_img_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);

    return;
}

INT32 mmp_listmode_view_show_common()
{
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_MAIN_FRM,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_FILE_LB,WGL_SW_RECURSIVE));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_PAGE_INFO_LST,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_FOLDER_PATH_TXT,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_FOLDER_NAME,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_OPT_LIST,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_TO_SIDE_BAR,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_INFO_FRM,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_MAIN_FRM),WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_SIDE_PANEL),WGL_SW_RECURSIVE));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_FILE_LIST),WGL_SW_RECURSIVE));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_ICON_LOGO),WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE),WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_TXT_FOLDER_PATH_TXT),WGL_SW_NORMAL));
    return MMPR_OK;
}

VOID mmp_listmode_view_show_audio()
{
    MMP_PLAY_STATE_T   e_bk_state = MMP_PLAY_STATE_CLOSED;

    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_INFO,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,WGL_SW_RECURSIVE));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_BTN_AUDIO_PLAY,WGL_SW_RECURSIVE));

    if ((MMPR_OK == mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,&e_bk_state)) &&
        (MMP_PLAY_STATE_CLOSING  != e_bk_state) &&
        (MMP_PLAY_STATE_CLOSED   != e_bk_state) &&
        (MMP_PLAY_STATE_STOPPING != e_bk_state) &&
        (MMP_PLAY_STATE_STOPPED  != e_bk_state))
    {
        MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_INFO,WGL_SW_NORMAL));
    }
}

VOID mmp_listmode_view_show_video()
{
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,WGL_SW_RECURSIVE));
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,WGL_SW_NORMAL));
}

/*----------------------------------------------------------------------------
 * Name:
 *          mmp_listmode_view_activate
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_activate(VOID)
{
    INT32              i4_ret = MMPR_OK;
    ISO_639_LANG_T     s639_lang;
    LISTMODE_VIEW_T *  pt_this = &t_g_listmode_view;
    BOOL               b_show = TRUE;
    UINT32     ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;
    SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;

    MMPR_LOG_ON_FAIL(a_cfg_get_gui_lang(s639_lang));

    DBG_LOG_PRINT(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));
    pt_this->ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);

    MMPR_LOG_ON_FAIL(mmp_common_ui_animation_set_callback_fct(_mmp_lm_anim_cb_fct,NULL));

    /* init file list view mode */
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_view_sort_mode());

    /* show current active device name */
    MMPR_LOG_ON_FAIL(_mmp_lm_view_set_device_name());

    mmp_listmode_view_show_common();
    MMP_MEDIA_TYPE_T e_media_type = MMP_MEDIA_TYPE_AUDIO;
    MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type));
    switch(e_media_type)
    {
        case MMP_MEDIA_TYPE_AUDIO:
        {
            mmp_listmode_view_show_audio();
            break;
        }
        case MMP_MEDIA_TYPE_VIDEO:
        {
            mmp_listmode_view_show_video();
            break;
        }
        default:break;
    }

     if (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_DEV_LST_SHOW)
     {
         b_show = FALSE;
         i4_ret = _mmp_lm_view_optl_set_dev_list_item();
         MMPR_LOG_ON_FAIL(i4_ret);
     }
     else if (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_SORT_MODE_SHOW)
     {
         b_show = FALSE;
         i4_ret = _mmp_lm_view_optl_set_sort_item();
         MMPR_LOG_ON_FAIL(i4_ret);
     }
     else if (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW)
     {
         b_show = FALSE;
         i4_ret = _mmp_lm_view_optl_set_view_item();
         MMPR_LOG_ON_FAIL(i4_ret);
     }
     else if(pt_this->ui1_attr & MMP_LM_VIEW_ATTR_PLAY_MODE_SHOW)
     {
        b_show = FALSE;
        MMPR_LOG_ON_FAIL(_mmp_lm_view_optl_set_play_item())
     }
     else
     {
         b_show = TRUE;
         /* hide option list */
         i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_OPT_LIST,
                                              WGL_SW_HIDE);
         MMPR_LOG_ON_FAIL(i4_ret);
     }

     /* update file list frame */
     i4_ret = _mmp_lm_view_set_file_list_frm();
     MMPR_LOG_ON_FAIL(i4_ret);

     /* update control frame */
     i4_ret = _mmp_lm_view_set_control_frm(b_show);
     MMPR_LOG_ON_FAIL(i4_ret);

     if ((pt_this->ui1_attr & MMP_LM_VIEW_ATTR_DEV_LST_SHOW)||
         (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_SORT_MODE_SHOW)||
         (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW))
     {
         i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
                                              WGL_SW_HIDE);
         MMPR_LOG_ON_FAIL(i4_ret);

         i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                              WGL_SW_HIDE);
         MMPR_LOG_ON_FAIL(i4_ret);

         i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,
                                       WGL_SW_HIDE);
         MMPR_LOG_ON_FAIL(i4_ret);

         i4_ret = _mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,
                                       WGL_SW_HIDE);
         MMPR_LOG_ON_FAIL(i4_ret);
     }

     i4_ret = _mmp_lm_view_focus_file_info_show(FALSE);
     MMPR_LOG_ON_FAIL(i4_ret);

     i4_ret = mmp_listmode_view_set_folder_path();
     MMPR_LOG_ON_FAIL(i4_ret);

     i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_MAIN_FRM,TRUE);
     MMPR_LOG_ON_FAIL(i4_ret);

     pt_this->ui1_attr |= MMP_LM_VIEW_ATTR_VIEW_ACTIVE;
     i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                        (VOID*) &ui4_exit_reason, z_size);
     MMPR_LOG_ON_FAIL(i4_ret);

     return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          mmp_listmode_view_inactivate
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_view_inactivate(VOID)
{
    INT32               i4_ret = MMPR_OK;
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    HANDLE_T            h_focus = NULL_HANDLE;

    pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_VIEW_ACTIVE;
    pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_DEV_LST_SHOW;
    pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_SORT_MODE_SHOW;
    pt_this->ui1_attr &= ~MMP_LM_VIEW_ATTR_VIEW_MODE_SHOW;

    MMPR_LOG_ON_FAIL(c_wgl_get_focus(&h_focus));

    MMPR_LOG_ON_FAIL(_mmp_lm_view_push_focus(h_focus));

    /* option list hide */
     MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_OPT_LIST,
                                  WGL_SW_HIDE));

    if (pt_this->ui1_attr & MMP_LM_VIEW_ATTR_ANIMATION)
    {
         MMPR_LOG_ON_FAIL(mmp_listmode_view_hide_animation());
    }

    /* info handle hide */
     MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_INFO_FRM,
                                  WGL_SW_HIDE_RECURSIVE));

    /* contorl frame hide */
     MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
                                  WGL_SW_HIDE_RECURSIVE));

    /* main frame hide */
     MMPR_LOG_ON_FAIL(_mmp_lm_view_set_visibility(MMP_LM_RC_REPAINT_RECT_ID_MAIN_FRM,
                                  WGL_SW_HIDE_RECURSIVE));

     MMPR_LOG_ON_FAIL(mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_MAIN_FRM,
                                 TRUE));
    return  i4_ret;
}

INT32 mmp_listmode_update_item_status(UINT32 ui4_hight_idx)
{
    DBG_LOG_PRINT(("[MMP][%s %d] ui4_hight_idx = %d\n",__FUNCTION__,__LINE__,ui4_hight_idx));

    /* update item status icon*/
    MMPR_LOG_ON_FAIL(mmp_listmode_view_lbw_reload_partial(LM_STATUS_NORMAL,
                                                          ui4_hight_idx,
                                                          ui4_hight_idx,
                                                          LBW_RPNT_MODE_PARTIAL_RPNT));
    return MMPR_OK;
}
INT32 mmp_listmode_play_next()
{
    LISTMODE_VIEW_T*    pt_this = &t_g_listmode_view;
    UINT32              ui4_hlt_old_idx = ui4_g_play_idx;
    UINT32              ui4_item_num;
    UINT32              ui4_select_idx;
    MMP_MEDIA_TYPE_T    e_media_type;
    UINT32              ui4_first      = 0;
    UINT32              ui4_idx_max    = LM_LBW_ELEM_NUM_PER_PAGE;
    MMP_GROUND_MODE_T   e_mode         = MMP_GROUND_MODE_BACK;
    a_lbw_vp_get_first(t_g_listmode_view.h_file_lb, &ui4_first);

    ui4_idx_max = ui4_first + LM_LBW_ELEM_NUM_PER_PAGE - 1 ;

    IS_MMPR_OK(a_lbw_get_elem_num(pt_this->h_file_lb,&ui4_item_num));

    IS_MMPR_OK( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type));
    e_mode = (e_media_type == MMP_MEDIA_TYPE_VIDEO ) ?  MMP_GROUND_MODE_FORE: MMP_GROUND_MODE_BACK ;

    DBG_LOG_PRINT(("[MMP][%s %d] e_mode = %s e_media_type = 0x%x\n",__FUNCTION__,__LINE__,
    e_mode == MMP_GROUND_MODE_BACK ? "MMP_GROUND_MODE_BACK" : "MMP_GROUND_MODE_FORE",
    e_media_type));
    mmp_mc_file_stop(e_mode);
    mmp_listmode_update_item_status(ui4_hlt_old_idx);
    if(0 == ui4_item_num)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] empty play list",__FUNCTION__,__LINE__));
        return MMPR_OK;
    }

    ui4_select_idx = ui4_hlt_old_idx + 1;
    DBG_LOG_PRINT(("[%s %d]ui4_hlt_old_idx == %d\n",__FUNCTION__,__LINE__,ui4_hlt_old_idx));
    DBG_LOG_PRINT(("[%s %d]ui4_select_idx == %d\n",__FUNCTION__,__LINE__,ui4_select_idx));
    if(ui4_select_idx > ui4_idx_max)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] get the last file of page\n",__FUNCTION__,__LINE__));
        MMPR_LOG_ON_FAIL(mmp_listmode_view_lbw_reload_partial(LM_STATUS_LOOP,
                                                              ui4_select_idx,
                                                              ui4_select_idx,
                                                              LBW_RPNT_MODE_PARTIAL_RPNT));
    }
    else if(ui4_hlt_old_idx == ui4_item_num - 1)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] get the last file of play list\n",__FUNCTION__,__LINE__));
        //mmp_listmode_view_lbw_reload(ui4_item_num,0,TRUE);
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _refresh_file_lst,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);

        mmp_lm_update_file_status(0);

        //return MMPR_OK;
    }
    ui4_g_play_idx = ui4_g_play_idx + 1;
   MMP_PL_CMD_NEXT_PARAM_T t_param = { e_mode, TRUE };
   IS_MMPR_OK( mmp_mc_list_next_ex(&t_param));

   {
        UINT32 ui4_dir_num,ui4_file_num;

       MMPR_LOG_ON_FAIL( mmp_mc_list_get_idx(e_mode,MMP_PL_IDX_TYPE_CRNT_PLAY,&t_g_listmode_view.ui4_hlt));
       DBG_LOG_PRINT(("[%s %d]t_g_listmode_view.ui4_hlt == %d\n",__FUNCTION__,__LINE__,t_g_listmode_view.ui4_hlt));
       if( MMPR_OK == mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num) &&
           t_g_listmode_view.ui4_hlt != 0xffffffff)
       {
           t_g_listmode_view.ui4_hlt += ui4_dir_num;
           MMPR_LOG_ON_FAIL(a_lbw_hlt_elem(t_g_listmode_view.h_file_lb,t_g_listmode_view.ui4_hlt,LBW_RPNT_MODE_PARTIAL_RPNT));
       }
   }

   return MMPR_OK;
}

UINT32  mmp_listmode_view_get_current_viewreport(UINT32* pui4_first,UINT32* pui4_last)
{
    if(LBWR_INV_OP == a_lbw_vp_get_first(t_g_listmode_view.h_file_lb,pui4_first))
    {
        DBG_LOG_PRINT(("[MMP][%s %d]total file num is 0\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }
    if(LBWR_INV_OP ==a_lbw_vp_get_last(t_g_listmode_view.h_file_lb, pui4_last))
    {
        DBG_LOG_PRINT(("[MMP][%s %d]total file num is 0\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }
    return MMPR_OK;
}
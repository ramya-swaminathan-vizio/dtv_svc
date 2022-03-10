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
 * $RCSfile: menu_page_net_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

#ifdef APP_DYNAMIC_TOS_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "x_os.h"

#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_txt.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/msgconvert/msgconvert_custom.h"

#ifdef SYS_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif
#include "nav/via_dlg/nav_via_dlg.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_page_animation.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#include "res/app_util/config/a_cfg_custom.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/download_util/a_download_util.h"

#include "menu_network.h"
#include "menu_tos_dialog.h"
#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define  MENU_DLG_BTN_TEXT_CLR                ((GL_COLOR_T){255, {255}, {255}, {255}})

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

#define  UI4_TXT_INVALUED                     0xffffffff

#define TERMS_TOS_TEXT_X                      (0)
#define TERMS_TOS_TEXT_Y                      (0)
#define TERMS_TOS_TEXT_W                      (MENU_ITEM_V_WIDE)
#define TERMS_TOS_TEXT_H                      (550)//500

#define TERMS_TOS_LIST_X                      (TERMS_TOS_TEXT_X)
#define TERMS_TOS_LIST_Y                      (TERMS_TOS_TEXT_Y)
#define TERMS_TOS_LIST_W                      (TERMS_TOS_TEXT_W)
#define TERMS_TOS_LIST_H                      (TERMS_TOS_TEXT_H)

#define TERMS_TOS_TEXT_ICON_W                 (10*4/3)
#define TERMS_TOS_TEXT_ICON_H                 (4*4/3)

#define TERMS_TOS_TEXT_UP_ICON_X              (TERMS_TOS_TEXT_X+TERMS_TOS_TEXT_W)
#define TERMS_TOS_TEXT_UP_ICON_Y              (TERMS_TOS_TEXT_Y)

#define TERMS_TOS_TEXT_DOWN_ICON_X            (TERMS_TOS_TEXT_X+TERMS_TOS_TEXT_W)
#define TERMS_TOS_TEXT_DOWN_ICON_Y            (TERMS_TOS_TEXT_Y+TERMS_TOS_TEXT_H)

#define TERMS_BTN_NEXT_X                       (0)
#define TERMS_BTN_NEXT_Y                       (TERMS_TOS_LIST_Y+TERMS_TOS_LIST_H+10)
#define TERMS_BTN_NEXT_W                       (MENU_ITEM_V_WIDE)
#define TERMS_BTN_NEXT_H                       (MENU_ITEM_V_HEIGHT)
#define MENU_TERMS_ITEM_V_HEIGHT               (MENU_ITEM_V_HEIGHT/2)

#define TERMS_PAGE_TO_NUM(pos)                 ((INT32)(pos + 1))
#define TERMS_NUM_TO_PAGE(num)                 ((INT32)(num - 1))


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/


typedef struct _TERMS_PAGE_TEXT_T
{
    HANDLE_T    h_widget;
    UINT16      ui2_msg_idx;

    HANDLE_T    h_text_widget;
    HANDLE_T    h_text;

    HANDLE_T    h_icon_frm;
    HANDLE_T    h_icon_up;
    HANDLE_T    h_icon_down;
    HANDLE_T    h_scrollbar;
}TERMS_PAGE_TEXT_T;

typedef struct _TERMS_PAGE_DATA_T
{
    HANDLE_T                h_cnt_frm;

    TERMS_PAGE_TEXT_T       t_terms_text;

    HANDLE_T                h_btn_next;
    HANDLE_T                h_btn_sel;//select regions only.
    HANDLE_T                h_btn_vizio_tos;
    HANDLE_T                h_btn_vizio_pri;//vizio privacy policy.
    HANDLE_T                h_btn_google_tos;
    HANDLE_T                h_btn_google_pri;//google privacy policy.

    BOOL                    b_list_state;
    BOOL                    b_terms_selected;
    UINT32                  ui4_pro_total_page;
    MENU_PROTOCOL_SCAN_E    e_scan_text;
    CHAR                    s_file_path[256];
    CHAR                    s_file_tts_path[256];
    BOOL                    b_is_file_opened;    /* download file is be opened successfully*/
    UINT16                  ui2_nty_id;         /*url download notify id*/
    UINT32                  ui4_crnt_downloading;   /* current downing url item */

}TERMS_PAGE_DATA_T;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_terms;
TERMS_PAGE_DATA_T    t_terms_page_data;
extern MENU_NW_TOS_SUB_BASE_DATA_T    t_terms_sub_page_base_data;


GL_COLOR_T           t_g_menu_color_network_frame_bk = {0, {0 }, {0 }, {0 } };
GL_COLOR_T           t_g_menu_color_network_txt_nor = { 255, {200}, {200 }, {200 }}; /* Gray color */
GL_COLOR_T           t_g_menu_color_network_txt_hlt = { 255, {255 }, {255 }, {255}}; /* white color */

static UTF16_T     w2s_g_empty[] = {0};
static WGL_INSET_T t_inset_border = {
    MENU_ITEM_V_CNT_INSET_L + MENU_ITEM_V_TITLE_W,
    0,
    0,
    0};
static GL_RECT_T   t_rect_border_title = {
    65,
    0,
    MENU_ITEM_V_TITLE_W,
    MENU_TERMS_ITEM_V_HEIGHT};

static GL_RECT_T   t_rect_border_btn = {
    0,
    0,
    MENU_ITEM_V_WIDE-20,
    MENU_ITEM_V_HEIGHT};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static VOID _text_show_nfy_cb(
                            HANDLE_T                    h_handle,
                            const VOID*                 pv_pt_txt,
                            TXT_ASYNC_COND_T            e_event,
                            const VOID*                 pv_data);

static INT32 _menu_terms_set_nav(VOID);


static INT32  _text_show_open(const CHAR*     ps_filename,
                              HANDLE_T*       ph_widget,
                              HANDLE_T*       ph_text);

static INT32  _text_show_start_scan(HANDLE_T*    ph_text);

static INT32 _menu_terms_text_set_text(HANDLE_T  h_widget,
                                       UINT32    ui4_msg_id);

static INT32 _menu_terms_btn_update_text(VOID);

static INT32 _set_page_focus(VOID);
static INT32 _text_show_close(HANDLE_T* ph_text);
static INT32 _menu_policy_download_nfy_cb(UINT16             ui2_nfy_id,
                                                  VOID*              pv_tag,
                                                  ICL_NOTIFY_DATA_T* pt_notify_data);
static VOID _menu_back_to_cast_page_from_vizio_policy(VOID);

static INT32 _menu_set_policy_status(MENU_PROTOCOL_SCAN_E status)
{
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

    DBG_LOG_PRINT(("[MENU][VPP][%s %d]e_scan_text = %d\n",__FUNCTION__,__LINE__,t_terms_page_data.e_scan_text));
    switch(status)
    {
        case MENU_PROTOCOL_SCAN_TERMS_VIZIO:
        case MENU_PROTOCOL_SCAN_POLICY_VIZIO:
        case MENU_PROTOCOL_SCAN_TERMS_GOOGLE:
        case MENU_PROTOCOL_SCAN_POLICY_GOOGLE:
        case MENU_PROTOCOL_SCAN_SMART_CAST_POLICY:
        case MENU_PROTOCOL_SCAN_VIEWING_DATA_POLICY:
        {
             c_wgl_set_visibility(pt_page_data->h_btn_google_pri,WGL_SW_HIDE);
             c_wgl_set_visibility(pt_page_data->h_btn_google_tos,WGL_SW_HIDE);
             c_wgl_set_visibility(pt_page_data->h_btn_vizio_pri,WGL_SW_HIDE);
             c_wgl_set_visibility(pt_page_data->h_btn_vizio_tos,WGL_SW_HIDE);
             c_wgl_set_visibility(pt_page_data->t_terms_text.h_widget, WGL_SW_HIDE);
             c_wgl_set_visibility(pt_page_data->t_terms_text.h_text_widget, WGL_SW_RECURSIVE);
             c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm, WGL_SW_RECURSIVE);
             c_wgl_enable(pt_page_data->t_terms_text.h_icon_up, FALSE);
             c_wgl_enable(pt_page_data->t_terms_text.h_icon_down, TRUE);
             c_wgl_set_visibility(pt_page_data->h_btn_next,WGL_SW_HIDE);

             break;
        }
        default:
        {
            pt_page_data->b_list_state = FALSE;
            c_wgl_set_visibility(pt_page_data->h_btn_google_pri,WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_page_data->h_btn_google_tos,WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_page_data->h_btn_vizio_pri,WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_page_data->h_btn_vizio_tos,WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm, WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(pt_page_data->h_btn_next,WGL_SW_NORMAL);
            menu_main_set_title(MLM_MENU_KEY_TERMS_AND_CONDITIONS_TITLE);
           // menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TERMS_OF_SERVICE_HELP));
           // _menu_terms_text_set_text(pt_page_data->t_terms_text.h_widget,MLM_MENU_KEY_TERMS_OF_SERVICE_PROMPT_PART1 /*pt_page_data->t_terms_text.ui2_msg_idx*/);
            c_wgl_set_focus(pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_TERMS_GOOGLE  ? pt_page_data->h_btn_google_tos :
                            pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_POLICY_GOOGLE ? pt_page_data->h_btn_google_pri :
                            pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_TERMS_VIZIO   ? pt_page_data->h_btn_vizio_tos  :
                            pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_POLICY_VIZIO  ? pt_page_data->h_btn_vizio_pri  :
                            pt_page_data->h_btn_next, WGL_SYNC_AUTO_REPAINT);
            menu_set_and_show_help_tip(MENU_TEXT(pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_TERMS_GOOGLE ? MLM_MENU_KEY_HELP_VIZIO_GOOGLE_TOS :
                                                 pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_POLICY_GOOGLE ? MLM_MENU_KEY_HELP_VIZIO_GOOGLE_PRIVACY :
                                                 pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_TERMS_VIZIO ? MLM_MENU_KEY_HELP_VIZIO_TOS :
                                                 pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_POLICY_VIZIO ? MLM_MENU_KEY_HELP_VIZIO_PRIVACY_POLICY
                                                    : MLM_MENU_KEY_EMPTY));
            pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_SELECT;
            break;
        }
    }
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _menu_protocol_text_open
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
INT32 _menu_protocol_text_open(VOID)
{
    INT32    i4_ret;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

    if (0 == c_strlen(pt_page_data->s_file_path) || pt_page_data->b_list_state == FALSE)
    {
        DBG_LOG_PRINT(("[MENU][TOS][%s %d] file path can not be empty or is not list state!!\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    if (MENU_PROTOCOL_SCAN_NULL != pt_page_data->e_scan_text)
    {
        if(pt_page_data->t_terms_text.h_text)
        {
            _text_show_close(&pt_page_data->t_terms_text.h_text);
            pt_page_data->t_terms_text.h_text = NULL_HANDLE;
        }
        DBG_LOG_PRINT(("[MENU][TOS][%s %d] %s!!\n",__FUNCTION__,__LINE__,pt_page_data->s_file_path));
        i4_ret = _text_show_open(pt_page_data->s_file_path,
                                &pt_page_data->t_terms_text.h_text_widget,
                                &pt_page_data->t_terms_text.h_text);
        MENU_LOG_ON_FAIL(i4_ret);

       _menu_set_policy_status(pt_page_data->e_scan_text);

        i4_ret = _text_show_start_scan(&pt_page_data->t_terms_text.h_text);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        return MENUR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_first_page
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

VOID _text_show_first_page(VOID* pv_data,
                                  SIZE_T  z_data_size)
{
    TERMS_PAGE_TEXT_T*    ph_text = (TERMS_PAGE_TEXT_T*)pv_data;
    c_txt_get_page_data(ph_text->h_text,
                        (UINT32)1,
                        _text_show_nfy_cb,
                        NULL);
    return;
}

#ifdef APP_TTS_SUPPORT
static INT32 _get_privacy_policy_tts_content(VOID)
{
    struct stat stat_buf;

    if( strlen(t_terms_page_data.s_file_path) > 0 &&
        NULL != strstr(t_terms_page_data.s_file_path,".txt") &&
        0 == stat(t_terms_page_data.s_file_path,&stat_buf) &&
        stat_buf.st_size > 0)
    {
        INT32 i            = 0;
        FILE  *fp_src      = NULL;
        FILE  *fp_dst      = NULL;
        char tmp[256]      = {0};
        char  *tts_content = NULL;

        strncpy(tmp,t_terms_page_data.s_file_path,strlen(t_terms_page_data.s_file_path)- strlen(".txt"));
        snprintf(t_terms_page_data.s_file_tts_path,sizeof(t_terms_page_data.s_file_tts_path),"%s_tts.txt",tmp);
        DBG_LOG_PRINT(("MENU VPP [%s %d] tts path = %s\n",__FUNCTION__,__LINE__,t_terms_page_data.s_file_tts_path));

        if (NULL == (fp_src = fopen(t_terms_page_data.s_file_path,"r")))
        {
            DBG_LOG_PRINT(("VPP open src file %s fail!!!\n",t_terms_page_data.s_file_path));
            return MENUR_FAIL;
        }
        if (NULL == (tts_content = malloc(stat_buf.st_size + 1)))
        {
            DBG_LOG_PRINT(("VPP automan debug!!!heap memory allocation failed\n"));
            return MENUR_FAIL;
        }
        if (NULL == (fp_dst = fopen(t_terms_page_data.s_file_tts_path,"w+")))
        {
            DBG_LOG_PRINT(("VPP create dst file %s fail!!!\n",t_terms_page_data.s_file_tts_path));
            free(tts_content);
            fclose(fp_src);
            return MENUR_FAIL;
        }

        if(fread(tts_content,stat_buf.st_size,1,fp_src) <= 0)
        {
            DBG_LOG_PRINT(("VPP read dst file %s fail!!!\n",t_terms_page_data.s_file_tts_path));
            free(tts_content);
            fclose(fp_src);
            fclose(fp_dst);
            return MENUR_FAIL;
        }
        tts_content[stat_buf.st_size] = '\0';

        for (;i<strlen(tts_content);i++)
        {
            if (tts_content[i] == '\n')
            {
                tts_content[i] = ' ';
            }
        }

        if(fwrite(tts_content,stat_buf.st_size,1,fp_dst) <= 0)
        {
            DBG_LOG_PRINT(("write dst file %s fail!!!\n",t_terms_page_data.s_file_tts_path));
            free(tts_content);
            fclose(fp_src);
            fclose(fp_dst);
            return MENUR_FAIL;
        }
        DBG_LOG_PRINT(("VPP create dst file %s ok!!!\n",t_terms_page_data.s_file_tts_path));
        fclose(fp_src);
        fclose(fp_dst);
        free(tts_content);
    }
    return MENUR_OK;
}

static VOID _privacy_policy_tts_play(VOID *pv_arg)
{
    struct stat stat_buf;

    _get_privacy_policy_tts_content();
    if(strlen(t_terms_page_data.s_file_path) > 0 &&
       0 == stat(t_terms_page_data.s_file_tts_path,&stat_buf) &&
       stat_buf.st_size > 0)
    {
        a_app_tts_play_file(t_terms_page_data.s_file_tts_path);
    }
}

static VOID _service_cast_creat_tts_thread(VOID)
{
    UINT8    switch_status = APP_CFG_TTS_SWITCH_OFF;
    HANDLE_T tos_ttsthread = NULL_HANDLE;

    a_cfg_get_tts_switch_status(&switch_status);
    if (APP_CFG_TTS_SWITCH_OFF == switch_status ||
        VIZIO_LANG_EN != ui2_g_menu_curr_lang)
    {
        return ;
    }

    MENU_LOG_ON_FAIL(x_thread_create(
                     &tos_ttsthread,
                     "menu_service_cast_tts",
                     8192,
                     128,
                     _privacy_policy_tts_play,
                     0,
                     NULL));
}
#endif

/*----------------------------------------------------------------------------
 * Name: _text_show_nfy_cb
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
static VOID _text_show_nfy_cb(
                              HANDLE_T                    h_handle,
                              const VOID*                 pv_pt_txt,
                              TXT_ASYNC_COND_T            e_event,
                              const VOID*                 pv_data)
{


    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    switch(e_event)
    {
        case TXT_ASYNC_COND_SCANING:
            DBG_LOG_PRINT(("\nscanning...\n"));
            DBG_LOG_PRINT(("<VPP> TXT_ASYNC_COND_SCANING current page idx = %d \n",(UINT32)pv_data));

            if( pt_page_data->t_terms_text.h_text == h_handle && (1 == (UINT32)pv_data))
            {
                 menu_async_invoke(_text_show_first_page,(VOID*)(&pt_page_data->t_terms_text),sizeof(TERMS_PAGE_TEXT_T),TRUE);
            }

             break;
        case TXT_ASYNC_COND_SCAN_FINISH:
            DBG_LOG_PRINT(("\nscan finished!\n"));
            pt_page_data->ui4_pro_total_page = (UINT32)pv_data;
            DBG_LOG_PRINT(("<VPP> ui4_pro_total_page = %d\n",pt_page_data->ui4_pro_total_page));

            if(pt_page_data->ui4_pro_total_page > 1)
           {
                /* Set  scrollbar Range */
                c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                          WGL_CMD_PG_SET_RANGE,
                          WGL_PACK((INT32)0),
                          WGL_PACK((INT32)(pt_page_data->ui4_pro_total_page - 1)));
                c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK((INT32)0),
                          NULL);
                c_wgl_set_visibility(pt_page_data->t_terms_text.h_scrollbar,WGL_SW_NORMAL);
                c_wgl_repaint(pt_page_data->t_terms_text.h_scrollbar,NULL,TRUE);
                #ifdef APP_TTS_SUPPORT
                _service_cast_creat_tts_thread();
                #endif
           }

            break;
        case TXT_ASYNC_COND_GET_DATA:
        {
            INT32 i4_current_page_num = (INT32)pv_data;

              if( pt_page_data->ui4_pro_total_page > 1)
              {
                    DBG_LOG_PRINT(("######[VPP]get data of page(%d/%d)#####\n",i4_current_page_num, pt_page_data->ui4_pro_total_page));
                    c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                                 WGL_CMD_PG_SET_POS,
                                 WGL_PACK(TERMS_NUM_TO_PAGE(i4_current_page_num)),
                                 NULL);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_scrollbar, NULL, TRUE);

                if (i4_current_page_num == 1 )
                {
                    c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,FALSE);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                    c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,TRUE);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);
               }
               else if(i4_current_page_num == pt_page_data->ui4_pro_total_page)
               {
                    c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,TRUE);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                    c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,FALSE);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);
                }
                else
                {
                    c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,TRUE);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                    c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,TRUE);
                    c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);
                }
             }
            else if(pt_page_data->ui4_pro_total_page == 1)
            {
                c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,FALSE);
                c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,FALSE);
                c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);
            }

            if (pt_page_data->t_terms_text.h_text == h_handle)
            {
                c_wgl_repaint(pt_page_data->t_terms_text.h_text_widget,NULL,TRUE);
            }

            }

            break;
        case TXT_ASYNC_COND_GET_DATA_FAIL:
            DBG_ERROR(("\ncget data fail\n"));
            break;
        case TXT_ASYNC_COND_SCAN_ABORT:
            DBG_INFO(("\nscan abort\n"));
            break;
        default:
            break;
    }
    return;
}
/*----------------------------------------------------------------------------
 * Name: _text_show_start_scan
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
static INT32  _text_show_start_scan(HANDLE_T*    ph_text)
{
    INT32   i4_ret;

    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_scan(*ph_text,UI4_TXT_INVALUED,_text_show_nfy_cb,NULL);
        DBG_LOG_PRINT(("c_txt_scan return : %d\n", i4_ret));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        DBG_ERROR(("------h_txt is NULL------------\n"));
        return MENUR_FAIL;
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _text_show_close
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
static INT32 _text_show_close(HANDLE_T* ph_text)
{
    INT32   i4_ret;
    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_close(*ph_text);
        MENU_CHK_FAIL(i4_ret);
        *ph_text = NULL_HANDLE;
    }
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _text_proc_fct
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
static INT32 _text_proc_fct(HANDLE_T   h_widget,
                                 UINT32     ui4_msg,
                                 VOID*      param1,
                                 VOID*      param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }
    }
    case WGL_MSG_GET_FOCUS:

        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TERMS_OF_SERVICE_HELP));
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_str[1024] = {0};
        UINT16      ui2_msg_key = MLM_MENU_KEY_TERMS_AND_CONDITIONS_TEXT;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 1024);
#endif

        break;

    case WGL_MSG_LOSE_FOCUS:
        break;

    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_terms_text_create
 *
 * Description:
 *      The version component show the version information.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_create(HANDLE_T     h_parent,
                                     INT32        i4_left,
                                     INT32        i4_top,
                                     INT32        i4_width,
                                     INT32        i4_height,
                                     FE_FNT_STYLE e_font_style,
                                     HANDLE_T     h_normal_bk,
                                     HANDLE_T     h_highlight_bk,
                                     HANDLE_T*    ph_widget)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height
                       );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _text_proc_fct,
                                 255,
                                 (VOID*)( WGL_STL_TEXT_MAX_2048 |
                                          WGL_STL_TEXT_MULTILINE |
                                          WGL_STL_TEXT_MAX_DIS_40_LINE),
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_LEFT_TOP),//WGL_AS_LEFT_CENTER
                              NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK((INT32)0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_network_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_network_txt_nor);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_set_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_btn_update_text(VOID)
{
    INT32 i4_ret = 0;
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_sel,
                                 MLM_MENU_KEY_TOS_SELECT_REGION,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_vizio_tos,
                                 MLM_MENU_KEY_VIZIO_TOS,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_vizio_pri,
                                 MLM_MENU_KEY_VIZIO_PRIVACY_POLICY,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_google_tos,
                                 MLM_MENU_KEY_GOOGLE_TOS,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_google_pri,
                                 MLM_MENU_KEY_GOOGLE_PRIVACY_POLICY,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_next,
                                 MLM_MENU_KEY_ACCEPT_ALL,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_set_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_set_text(HANDLE_T  h_widget,
                                       UINT32    ui4_msg_id)
{
    INT32 i4_ret = 0;

    UTF16_T    aw2s_text[1024] = {0};

    c_uc_w2s_strcpy(aw2s_text, MENU_TEXT(ui4_msg_id));
    //c_uc_w2s_strcat(aw2s_text, _TEXT("\n\n"));
    //c_uc_w2s_strcat(aw2s_text, MENU_TEXT(ui4_msg_id+1));
    //c_uc_w2s_strcat(aw2s_text, MENU_TEXT(ui4_msg_id+2));

    i4_ret = c_wgl_do_cmd (h_widget,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (aw2s_text),
                      WGL_PACK (c_uc_w2s_strlen (aw2s_text)));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_cancel_scan
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
INT32  _text_show_cancel_scan(HANDLE_T*    ph_text)
{
    INT32   i4_ret;
    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_cancel_scan(*ph_text);
        MENU_CHK_FAIL(i4_ret);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_open
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
static INT32  _text_show_open(const CHAR*     ps_filename,
                              HANDLE_T*       ph_widget,
                              HANDLE_T*       ph_text)
{
    INT32           i4_ret;
    TXT_SET_CMD_T   pt_cmd[1];
    INT16           ui2_idx;

    do
    {
        /*open image*/
        i4_ret = c_txt_open(ps_filename,
                            c_strlen(ps_filename),
                            TXT_RW_FILE_MODE,
                            _text_show_nfy_cb,
                            NULL,
                            ph_text,
                            TXT_FILE_SRC_TYPE);
        if (i4_ret != MENUR_OK)
        {
            DBG_ERROR(("fail to open file return: %d!\n", i4_ret));
            *ph_text = NULL_HANDLE;

            c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_TEXT_SET_TEXT,
                 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                 WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_EMPTY))));
            break;
        }

        /* Set attribute to mw */

        /* Set ecode */
        ui2_idx = 0;
        pt_cmd[ui2_idx].e_set_attr_type   = TXT_SET_ENCODE;
        pt_cmd[ui2_idx].pv_param          = (VOID*)TXT_ECODE_UTF8;
        i4_ret = c_txt_set_attr(*ph_text, 1,pt_cmd);
        if (i4_ret != MENUR_OK)
        {
            DBG_ERROR(("fail to set file encode type!\n"));
            c_txt_close(*ph_text);
            *ph_text = NULL_HANDLE;

            c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_TEXT_SET_TEXT,
                 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                 WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_EMPTY))));
            break;
        }

        /* Set font */
        pt_cmd[ui2_idx].e_set_attr_type   = TXT_SET_WGL_HANDLE;
        pt_cmd[ui2_idx].pv_param          = (VOID*)ph_widget;

        i4_ret = c_txt_set_attr(*ph_text, 1,pt_cmd);
        if (i4_ret != MENUR_OK)
        {
            DBG_ERROR(("fail to set file encode type!\n"));
            c_txt_close(*ph_text);
            *ph_text = NULL_HANDLE;

            c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_TEXT_SET_TEXT,
                 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                 WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_EMPTY))));
            break;
        }
    }while(FALSE);

    return MENUR_OK;
}

static INT32 _text_show_prev_row(HANDLE_T     h_text_widget,
                                 HANDLE_T      h_text)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32 i4_page_min = 0;
    INT32 i4_pos = 0;

    MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                          WGL_CMD_PG_GET_POS,
                          WGL_PACK(&i4_pos),
                          NULL));

    if (h_text != NULL_HANDLE &&
        i4_pos > i4_page_min )
    {
        --i4_pos;
        c_txt_get_page_data(h_text,TERMS_PAGE_TO_NUM(i4_pos),_text_show_nfy_cb,NULL);

    }
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _text_show_next_row
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _text_show_next_row(HANDLE_T     h_text_widget,
                                 HANDLE_T      h_text)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32 i4_pos = 0;
    INT32 i4_page_max = pt_page_data->ui4_pro_total_page - 1;

    MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                          WGL_CMD_PG_GET_POS,
                          WGL_PACK(&i4_pos),
                          NULL));

    if (h_text != NULL_HANDLE &&
        i4_pos < i4_page_max)
    {
        ++i4_pos;
        c_txt_get_page_data(h_text,TERMS_PAGE_TO_NUM(i4_pos),_text_show_nfy_cb,NULL);
    }
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _text_widget_proc_fct
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
static INT32 _text_widget_proc_fct (HANDLE_T   h_widget,
                                    UINT32     ui4_msg,
                                    VOID*      param1,
                                    VOID*      param2)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
              case BTN_CURSOR_UP:
                if(pt_page_data->b_list_state == TRUE)
                {
                     if(h_widget == pt_page_data->t_terms_text.h_text_widget)
                     {
                        INT32 i4_pos = 0;
                        INT32 i4_min = 0;

                        MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                                       WGL_CMD_PG_GET_POS,
                                       WGL_PACK(&i4_pos),
                                       NULL));
                        DBG_LOG_PRINT(("<VPP %s %d> pos = %d min = %d\n",__FUNCTION__,__LINE__,i4_pos,i4_min));
                         /* if current row is first, focus on backbar */
                         if (i4_pos <= i4_min)
                         {
                            c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,FALSE);
                            c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                            menu_set_focus_on_backbar(FALSE);
                            menu_pm_repaint();
                            DBG_LOG_PRINT(("[VPP][%s %d] return to back btn\n",__FUNCTION__,__LINE__));
                            return MENUR_OK;
                         }

                         _text_show_prev_row(pt_page_data->t_terms_text.h_text_widget,
                                             pt_page_data->t_terms_text.h_text);

                     }
                }
                else
                {
                    menu_set_focus_on_backbar(FALSE);
                }
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                if(pt_page_data->b_list_state == TRUE)
                {
                     if(h_widget == pt_page_data->t_terms_text.h_text_widget)
                     {
                        INT32 i4_max = pt_page_data->ui4_pro_total_page - 1;
                        INT32 i4_pos = 0;

                        MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_terms_text.h_scrollbar,
                                       WGL_CMD_PG_GET_POS,
                                       WGL_PACK(&i4_pos),
                                       NULL));
                        DBG_LOG_PRINT(("<VPP %s %d> pos = %d max = %d\n",__FUNCTION__,__LINE__,i4_pos,i4_max));
                         /* if current row is the end-row, focus on helptip */
                         if (i4_pos >= i4_max)
                         {
                             c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,FALSE);
                             c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);

                            // t_terms_sub_page_base_data.e_scan_text = t_terms_page_data.e_scan_text;
                             //_set_page_focus();
                            // DBG_LOG_PRINT(("[VPP][%s %d] return to select btn\n",__FUNCTION__,__LINE__));
                            // menu_pm_repaint();
                             return MENUR_OK;
                         }

                          _text_show_next_row(pt_page_data->t_terms_text.h_text_widget,
                                              pt_page_data->t_terms_text.h_text);

                             c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,TRUE);
                             c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                     }
                }
                else
                {
                    c_wgl_set_focus(pt_page_data->h_btn_vizio_tos, WGL_SYNC_AUTO_REPAINT);
                }
                return MENUR_OK;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[MENU][VPP][%s %d]\n",__FUNCTION__,__LINE__));
                if(pt_page_data->e_scan_text != MENU_PROTOCOL_SCAN_SELECT)
                {
                    //_menu_set_policy_status(MENU_PROTOCOL_SCAN_SELECT);
                    _menu_back_to_cast_page_from_vizio_policy();
                    menu_pm_repaint();
                }
                else
                {
                    _text_show_cancel_scan(&pt_page_data->t_terms_text.h_text);
                    _menu_terms_text_set_text(pt_page_data->t_terms_text.h_text_widget,MLM_MENU_KEY_EMPTY);
                    menu_nav_back();
                }

                return MENUR_OK;
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_terms_icon_frm_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_icon_frm_create(HANDLE_T              h_parent,
                                UINT16                ui2_left,
                                UINT16                ui2_top,
                                UINT16                ui2_width,
                                UINT16                ui2_height,
                                wgl_widget_proc_fct   pf_wgl_nfy_fct,
                                HANDLE_T*             ph_frame)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (& t_rect,
                      ui2_left,
                      ui2_top,
                      ui2_width,
                      ui2_height);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     pf_wgl_nfy_fct,
                                     255,
                                     (VOID*) WGL_STL_GL_NO_IMG_UI,
                                     0,
                                     ph_frame );
    MENU_CHK_FAIL(i4_ret);

    /* set color */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_color_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_color_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd(*ph_frame,
                 WGL_CMD_GL_SET_COLOR,
                 WGL_PACK(WGL_CLR_BK),
                 WGL_PACK(&t_color_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_widget_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_widget_create(HANDLE_T  h_parent,
                                            INT32     i4_left,
                                            INT32     i4_top,
                                            INT32     i4_width,
                                            INT32     i4_height,
                                            FE_FNT_STYLE e_font_style,
                                            HANDLE_T  h_normal_bk,
                                            HANDLE_T  h_highlight_bk,
                                            HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    //WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height
                       );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _text_widget_proc_fct,
                                 255,
                                (VOID*)( WGL_STL_TEXT_MULTISTRING |
                                WGL_STL_TEXT_MAX_DIS_40_LINE   |
                                WGL_STL_TEXT_IGNORE_NEWLINE),
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
   i4_ret = c_wgl_do_cmd (*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK (WGL_AS_LEFT_TOP),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 2*4/3;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_network_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_network_txt_nor);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);
#if 0
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          (INT32)(0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_icon_create(HANDLE_T  h_parent,
                                          INT32     i4_left,
                                          INT32     i4_top,
                                          INT32     i4_width,
                                          INT32     i4_height,
                                          FE_FNT_STYLE e_font_style,
                                          HANDLE_T  h_normal_bk,
                                          HANDLE_T  h_disable_bk,
                                          HANDLE_T* ph_widget)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     i4_left,
                     i4_top,
                     i4_width,
                     i4_height);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("Failed to create icon!\n"));
    }
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_disable_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                 WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nw_confirm_dialog_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _menu_tos_dialog_btn_cb_fct(UINT32 ui4_key_code)
{
    _set_page_focus();

    menu_tos_dialog_hide(TRUE);
}

static INT32 _show_policy(MENU_PROTOCOL_SCAN_E type)
{
    VIZIO_COUNTRY_TYPE_T e_country;
    VIZIO_LANG_TYPE_T    e_lang;
    VIZIO_POLICY_TYPE_T e_policy;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

    switch(type)
    {
        case MENU_PROTOCOL_SCAN_TERMS_VIZIO  : e_policy = VIZIO_POLICY_TOS  ;         t_terms_sub_page_base_data.ui2_title_text = MLM_MENU_KEY_VIZIO_TOS ;break;
        case MENU_PROTOCOL_SCAN_POLICY_VIZIO : e_policy = VIZIO_POLICY_PRIVACY;       t_terms_sub_page_base_data.ui2_title_text = MLM_MENU_KEY_VIZIO_PRIVACY_POLICY ;break;
        case MENU_PROTOCOL_SCAN_TERMS_GOOGLE : e_policy = VIZIO_POLICY_GOOGLE_TOS;    t_terms_sub_page_base_data.ui2_title_text = MLM_MENU_KEY_GOOGLE_TOS ;break;
        case MENU_PROTOCOL_SCAN_POLICY_GOOGLE: e_policy = VIZIO_POLICY_GOOGLE_PRIVACY;t_terms_sub_page_base_data.ui2_title_text = MLM_MENU_KEY_GOOGLE_PRIVACY_POLICY ;break;
        default:
            DBG_LOG_PRINT(("[MENU][TOS][%s %d] error MENU_PROTOCOL_SCAN_E type %d!!!\n",__FUNCTION__,__LINE__,type));
            return MENUR_INV_ARG;
    }

    pt_page_data->e_scan_text = type;
    t_terms_sub_page_base_data.e_scan_text = type;
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    DBG_LOG_PRINT(("[MENU][VPP][%s %d] try to ping www.google.com!!!\n",__FUNCTION__,__LINE__));
    if((MENU_PROTOCOL_SCAN_TERMS_GOOGLE != type && MENU_PROTOCOL_SCAN_POLICY_GOOGLE != type ) && (0 == a_nw_connection_test((CHAR*)"www.google.com")  || 0 == a_nw_connection_test6((CHAR*)"www.google.com")) )
    {
        /*network is connected*/

        ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

        a_cfg_custom_get_country_code(&t_country_code);

        e_country = (t_country_code == ACFG_COUNTRY_CODE_US ? VIZIO_COUNTRY_US :
                     t_country_code == ACFG_COUNTRY_CODE_CA ? VIZIO_COUNTRY_CA : VIZIO_COUNTRY_MX);
        e_lang = (ui2_g_menu_curr_lang == MLM_MENU_LANG_FRE ? VIZIO_LANG_FR :
                  ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA ? VIZIO_LANG_SPA : VIZIO_LANG_EN);
        pt_page_data->b_list_state = TRUE;
        c_wgl_set_focus(pt_page_data->t_terms_text.h_text_widget, WGL_NO_AUTO_REPAINT);
        menu_pm_repaint();
        DBG_LOG_PRINT(("[MENU][VPP][%s %d] network is connected!!!,e_country = %d ,e_lang = %d,e_policy = %d\n",__FUNCTION__,__LINE__,e_country,e_lang,e_policy));
        if(e_policy == VIZIO_POLICY_GOOGLE_TOS || e_policy == VIZIO_POLICY_GOOGLE_PRIVACY)
        {
            DBG_LOG_PRINT(("[[MENU][VPP][%s %d] google pp and tos are not supported !!!,\n",__FUNCTION__,__LINE__));
        }
        _menu_terms_text_set_text(pt_page_data->t_terms_text.h_text_widget,MLM_MENU_KEY_EMPTY);
        if(a_is_policy_file_exist(e_country,e_lang,e_policy))
        {
            a_get_policy_file_path(e_country,e_lang,e_policy,pt_page_data->s_file_path,sizeof(pt_page_data->s_file_path));
            if(0 != _menu_protocol_text_open())
            {
                DBG_LOG_PRINT(("[MENU][TOS][%s %d] failed to show tos content\n",__FUNCTION__,__LINE__));
                return MENUR_FAIL;
            }
        }
        else
        {
             INT32 i4_ret;
             /*to make sure a_icl_notify_reg only succeeed only once */
             if(0 == t_terms_page_data.ui2_nty_id && ICLR_OK != (i4_ret = a_icl_notify_reg(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS,
                                  ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS,
                                  NULL,
                                  NULL,
                                  _menu_policy_download_nfy_cb,
                                  &t_terms_page_data.ui2_nty_id)))
            {
                 DBG_LOG_PRINT(("[MENU][VPP][%s %d]failed to reg icl ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
                 return MENUR_FAIL;
            }
            if(0 != a_url_download(e_country,e_lang,e_policy))
            {
                DBG_LOG_PRINT(("[MENU][TOS][%s %d] failed to start download url item\n",__FUNCTION__,__LINE__));
                return MENUR_FAIL;
            }

            MAKE_ITEM(pt_page_data->ui4_crnt_downloading,e_country,e_lang,e_policy);
        }
        DBG_LOG_PRINT(("[MENU][TOS][%s %d] filepath is %s!!!\n",__FUNCTION__,__LINE__,pt_page_data->s_file_path));
        pt_page_data->b_list_state = TRUE;
    }
    else
    {
        UINT16      ui2_msgid_text;
        UINT16      ui2_title_id;
        ACFG_COUNTRY_CODE_T t_country;
        a_cfg_custom_get_country_code(&t_country);

        if(MENU_PROTOCOL_SCAN_TERMS_GOOGLE == type)
        {
            ui2_msgid_text = MLM_MENU_KEY_GOOGLE_TOS_DLG_TEXT;
            ui2_title_id   = MLM_MENU_KEY_GOOGLE_TOS_DLG_TITLE;
        }
        else if(MENU_PROTOCOL_SCAN_POLICY_GOOGLE == type)
        {
            ui2_msgid_text = MLM_MENU_KEY_GOOGLE_PRI_DLG_TEXT;
            ui2_title_id   = MLM_MENU_KEY_GOOGLE_PRI_DLG_TITLE;
        }
        else if(MENU_PROTOCOL_SCAN_TERMS_VIZIO == type)
        {
            ui2_msgid_text = t_country == ACFG_COUNTRY_CODE_US ? MLM_MENU_KEY_VIZIO_TOS_DLG_TEXT :
                             t_country == ACFG_COUNTRY_CODE_CA ? MLM_MENU_KEY_VIZIO_TOS_DLG_TEXT_CA:
                                MLM_MENU_KEY_VIZIO_TOS_DLG_TEXT_MX;
            ui2_title_id   = MLM_MENU_KEY_VIZIO_TOS_DLG_TITLE;
        }
        else if(MENU_PROTOCOL_SCAN_POLICY_VIZIO == type)
        {
            ui2_msgid_text = t_country == ACFG_COUNTRY_CODE_US ? MLM_MENU_KEY_VIZIO_PRI_DLG_TEXT :
                             t_country == ACFG_COUNTRY_CODE_CA ? MLM_MENU_KEY_VIZIO_PRI_DLG_TEXT_CA:
                                MLM_MENU_KEY_VIZIO_PRI_DLG_TEXT_MX;
            ui2_title_id = MLM_MENU_KEY_VIZIO_PRI_DLG_TITLE;
        }

        menu_tos_dialog_show(ui2_title_id,
                             ui2_msgid_text,
                             MLM_MENU_KEY_OK,
                             _menu_tos_dialog_btn_cb_fct,
                             TRUE);
    }
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _menu_terms_btn_proc_fct
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
static INT32 _menu_terms_btn_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32  i4_ret = 0;
    BOOL b_viewing_data_showed = FALSE;
    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                pt_page_data->b_terms_selected = TRUE;
                a_tv_custom_set_tos(TRUE);
                rest_event_notify("tv_settings/cast/tos_accepted", 1, "");
                a_tv_custom_set_privacy(TRUE);
                /* setup tos version */
                a_tv_custom_set_tos_version();
                a_c4tv_apron_resume_cast();
                a_c4tv_apron_accept_tos();

                t_terms_sub_page_base_data.e_scan_text = MENU_PROTOCOL_SCAN_ACCEPT_ALL;
                t_terms_sub_page_base_data.ui2_title_text = MLM_MENU_KEY_VIZIO_TOS_VIEWING_DATA_TITLE;
                b_viewing_data_showed = a_tv_custom_get_viewing_data_show();
                //check conutry
                a_cfg_custom_get_country_code(&t_country_code);
                if(b_viewing_data_showed || ACFG_COUNTRY_CODE_US != t_country_code)
                {
                    menu_nav_go(ui4_g_menu_page_nw, NULL);
                }
                else
                {
                    menu_nav_go(ui4_g_menu_page_terms_sub, NULL);
                }
            }
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
            default:
                break;
        }
        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
#ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[128] = {0};
        //c_uc_ps_to_w2s("next", w2s_str, 128);
        UINT16      ui2_msg_key = MLM_MENU_KEY_ACCEPT_ALL;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 128);
#endif
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_VIZIO_TOS_PP));
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_terms_sel_proc_fct
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
static INT32 _menu_terms_sel_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32  i4_ret = 0;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                t_terms_sub_page_base_data.e_scan_text = MENU_PROTOCOL_SCAN_SELECT;
                t_terms_sub_page_base_data.ui2_title_text = MLM_MENU_KEY_TOS_SELECT_REGION;
                menu_nav_go(ui4_g_menu_page_terms_sub, NULL);
            }
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
            default:
                break;
        }
        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_str[128] = {0};
        UINT16      ui2_msg_key = MLM_MENU_KEY_TOS_SELECT_REGION;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 128);
#endif
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_vizio_tos_proc_fct
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
static INT32 _menu_vizio_tos_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32  i4_ret = 0;
    //TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    ACFG_COUNTRY_CODE_T             t_country_code = ACFG_COUNTRY_CODE_US;

    a_cfg_custom_get_country_code(&t_country_code);

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
         switch (ui4_keycode)
        {
            case BTN_SELECT:
                _show_policy(MENU_PROTOCOL_SCAN_TERMS_VIZIO);
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
                break;
            case BTN_CURSOR_UP:
                c_wgl_set_focus(t_terms_page_data.t_terms_text.h_text_widget, WGL_NO_AUTO_REPAINT);
                break;
            default:
                break;
        }
        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_str[128] = {0};
        UINT16      ui2_msg_key = MLM_MENU_KEY_VIZIO_TOS;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 128);
#endif
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_VIZIO_TOS));
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_vizio_pri_proc_fct
 *
 * Description: VIZIO Privacy Policy button proc function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_vizio_pri_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32  i4_ret = 0;
    ACFG_COUNTRY_CODE_T             t_country_code = ACFG_COUNTRY_CODE_US;

    a_cfg_custom_get_country_code(&t_country_code);

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
         switch (ui4_keycode)
        {
            case BTN_SELECT:
                _show_policy(MENU_PROTOCOL_SCAN_POLICY_VIZIO);
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
            default:
                break;
        }
        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_str[128] = {0};
        UINT16      ui2_msg_key = MLM_MENU_KEY_VIZIO_PRIVACY_POLICY;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 128);
#endif
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_VIZIO_PRIVACY_POLICY));
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_google_tos_proc_fct
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
static INT32 _menu_google_tos_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32  i4_ret = 0;


    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
         switch (ui4_keycode)
        {
            case BTN_SELECT:
                _show_policy(MENU_PROTOCOL_SCAN_TERMS_GOOGLE);
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
            default:
                break;
        }
        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_str[128] = {0};
        UINT16      ui2_msg_key = MLM_MENU_KEY_GOOGLE_TOS;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 128);
#endif
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_VIZIO_GOOGLE_TOS));
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_google_pri_proc_fct
 *
 * Description: Google Privacy Policy proc function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_google_pri_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32  i4_ret = 0;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
                _show_policy(MENU_PROTOCOL_SCAN_POLICY_GOOGLE);
                break;
            case BTN_RETURN:
                DBG_LOG_PRINT(("[VPP][%s %d] BTN_RETURN\n",__FUNCTION__,__LINE__));
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
            default:
                break;
        }
        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_str[128] = {0};
        UINT16      ui2_msg_key = MLM_MENU_KEY_GOOGLE_PRIVACY_POLICY;
        c_uc_w2s_strcpy(w2s_str, MLM_MENU_TEXT(0, ui2_msg_key));
        a_app_tts_play(w2s_str, 128);
#endif
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_VIZIO_GOOGLE_PRIVACY));
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_set_nav
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_set_nav(VOID)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32              i4_ret;
    WGL_KEY_LINK_T     at_key_lnk[2];
    HANDLE_T           h_backbar;

    menu_get_backbar_handle(&h_backbar);
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_backbar;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_vizio_tos;//pt_page_data->h_btn_sel
    i4_ret = c_wgl_set_navigation(pt_page_data->t_terms_text.h_widget, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    if (0){
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->t_terms_text.h_widget;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_vizio_tos;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_sel, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);
    }

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->t_terms_text.h_widget;//;pt_page_data->h_btn_sel
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_vizio_pri;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_vizio_tos, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_btn_vizio_tos;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_google_tos;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_vizio_pri, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_btn_vizio_pri;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_google_pri;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_google_tos, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_btn_google_tos;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_next;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_google_pri, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_btn_google_pri;

    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_next, 1, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

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
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
#ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[128] = {0};
        c_uc_ps_to_w2s("back", w2s_str, 128);
        a_app_tts_play(w2s_str, 128);
#endif
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
        case BTN_RETURN:
            DBG_LOG_PRINT(("[MENU][VPP][%s %d] t_terms_sub_page_base_data.e_scan_text = %d\n",__FUNCTION__,__LINE__,t_terms_sub_page_base_data.e_scan_text));

            if((pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_TERMS_VIZIO)
             ||(pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_POLICY_VIZIO))
            {
                if(pt_page_data->b_list_state == TRUE)
                {
                     //_menu_set_policy_status(MENU_PROTOCOL_SCAN_SELECT);
                     _menu_back_to_cast_page_from_vizio_policy();
                     menu_pm_repaint();
                     pt_page_data->b_list_state = FALSE;
                }
                else
                {
                    menu_nav_go_home_menu();
                }
                 return MENUR_OK;
            }
            else
            {
                 menu_nav_go_home_menu();
                 return MENUR_OK;
            }
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(pt_page_data->t_terms_text.h_text_widget, WGL_SYNC_AUTO_REPAINT);

            break ;
        case BTN_CURSOR_UP:
            MENU_CHK_FAIL (menu_set_focus_on_homebar(TRUE));
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
        case BTN_RETURN:
            DBG_LOG_PRINT(("[MENU][VPP][%s %d]e_scan_text = %d\n",__FUNCTION__,__LINE__,t_terms_sub_page_base_data.e_scan_text));
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            MENU_CHK_FAIL(menu_set_focus_on_backbar (TRUE));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_action_create
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
INT32 menu_action_btn_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_ITEM_T               at_items[1];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_enter;
    WGL_IMG_INFO_T    t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = MENU_ITEM_V_VALUE_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_TERMS_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_TERMS_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_TERMS_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_white;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_enter, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_enter.h_normal                       = NULL_HANDLE;
    t_img_suit_enter.h_disable                      = NULL_HANDLE;
    t_img_suit_enter.h_highlight                    = NULL_HANDLE;
    t_img_suit_enter.h_highlight_unfocus            = NULL_HANDLE;
    t_img_suit_enter.h_pushed                       = NULL_HANDLE;
    t_img_suit_enter.h_selected                     = NULL_HANDLE;
    t_img_suit_enter.h_selected_disable             = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight           = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight_unfocus   = NULL_HANDLE;
    t_img_suit_enter.h_selected_pushed              = NULL_HANDLE;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_g_empty;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 memu_action_btn_set_align(HANDLE_T h_widget)
{
    INT32                   i4_ret = 0;
    WGL_FONT_INFO_T         t_fnt_info;
    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    /* Set Border Title */
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_btn;
    t_title_info.ui1_align = WGL_AS_CENTER_CENTER;
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


static INT32 _set_page_focus(VOID)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    DBG_LOG_PRINT(("[VPP][%s %d] e_scan_text = %d\n",__FUNCTION__,__LINE__,t_terms_sub_page_base_data.e_scan_text));

    if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_SELECT)
    {
        c_wgl_set_focus(pt_page_data->h_btn_sel, WGL_SYNC_AUTO_REPAINT);
    }
    else if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_TERMS_VIZIO)
    {
        c_wgl_set_focus(pt_page_data->h_btn_vizio_tos, WGL_SYNC_AUTO_REPAINT);
    }
    else if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_POLICY_VIZIO)
    {
        c_wgl_set_focus(pt_page_data->h_btn_vizio_pri, WGL_SYNC_AUTO_REPAINT);
    }
    else if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_TERMS_GOOGLE)
    {
        c_wgl_set_focus(pt_page_data->h_btn_google_tos, WGL_SYNC_AUTO_REPAINT);
    }
    else if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_POLICY_GOOGLE)
    {
        c_wgl_set_focus(pt_page_data->h_btn_google_pri, WGL_SYNC_AUTO_REPAINT);
    }
    else
    {
        c_wgl_set_focus(pt_page_data->h_btn_next, WGL_NO_AUTO_REPAINT);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _menu_create_scrollbar(
        HANDLE_T                    h_parent,
        INT32                       i4_scrl_x,
        INT32                       i4_scrl_y,
        INT32                       i4_scrl_w,
        INT32                       i4_scrl_h,
        HANDLE_T*                   ph_widget)
    {
        INT32                   i4_ret = -1;
        GL_RECT_T               t_rect;
        WGL_IMG_INFO_T          t_img_info;
        WGL_INSET_T             t_inset;

        SET_RECT_BY_SIZE(&t_rect,
                         i4_scrl_x,
                         i4_scrl_y,
                         i4_scrl_w,
                         i4_scrl_h);

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_PROGRESS_BAR,
                                     WGL_CONTENT_PROGRESS_BAR_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_PG_VERTICAL_DOWN | WGL_STL_PG_POINT),
                                     NULL,
                                     ph_widget);
        if(WGLR_OK != i4_ret)
        {
            DBG_INFO(("<VPP> %s_%d  \n",__FUNCTION__,__LINE__));
            return MENUR_FAIL;
        }

        /*set background image*/

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable =    h_g_menu_img_pb_bk;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bk;
        t_img_info.u_img_data.t_standard.t_disable =   h_g_menu_img_pb_bk;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_GL_SET_IMAGE,
                             WGL_PACK(WGL_IMG_BK),
                             WGL_PACK(&t_img_info));
        if (WGLR_OK != i4_ret)
        {
            DBG_INFO(("<Wizard> %s_%d  \n",__FUNCTION__,__LINE__));
            return MENUR_FAIL;
        }

        /* Set progressbar's BAR */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_pb_bar;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bar;
       t_img_info.u_img_data.t_standard.t_disable    = h_g_menu_img_pb_bar;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                             WGL_CMD_GL_SET_IMAGE,
                             WGL_PACK(WGL_IMG_PG_LEVEL_1),
                            WGL_PACK(&t_img_info));
        if (WGLR_OK != i4_ret)
        {
           DBG_INFO(("<VPP> %s_%d  \n",__FUNCTION__,__LINE__));
           return MENUR_FAIL;
       }

        /* Set Insets */
        c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_PG_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        if (WGLR_OK != i4_ret)
        {
            DBG_INFO(("<VPP> %s_%d  \n",__FUNCTION__,__LINE__));
            return MENUR_FAIL;
        }

        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_PG_SET_BAR_INSET,
                              &t_inset,
                              NULL);
        if (WGLR_OK != i4_ret)
        {
            DBG_INFO(("<VPP> %s_%d  \n",__FUNCTION__,__LINE__));
            return MENUR_FAIL;
        }

        /* Set Display Modes */
        i4_ret = c_wgl_do_cmd (*ph_widget,
                               WGL_CMD_PG_SET_DISPLAY_MODE,
                               WGL_PACK(WGL_PG_DM_HIDE_IDR),
                               NULL);
        if (WGLR_OK != i4_ret)
        {
            DBG_INFO(("<VPP> %s_%d  \n",__FUNCTION__,__LINE__));
            return MENUR_FAIL;
        }
        return MENUR_OK;
    }


static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32     i4_ret;

    c_memset(pt_page_data, 0, sizeof(TERMS_PAGE_DATA_T));
    t_g_menu_color_network_txt_hlt = t_g_menu_color_white;
    t_g_menu_color_network_txt_nor = t_g_menu_color_white;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_TOS_TEXT_X,
                         TERMS_TOS_TEXT_Y,
                         TERMS_TOS_TEXT_W,
                         TERMS_TOS_TEXT_H,
                         FE_FNT_SIZE_LARGE,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &pt_page_data->t_terms_text.h_widget);
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->t_terms_text.ui2_msg_idx = MLM_MENU_KEY_TERMS_AND_CONDITIONS_TEXT;

    i4_ret = _menu_terms_text_widget_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_TOS_TEXT_X,
                         TERMS_TOS_TEXT_Y,
                         TERMS_TOS_TEXT_W - TERMS_TOS_TEXT_ICON_W - 4,
                         TERMS_TOS_TEXT_H,
                         FE_FNT_SIZE_LARGE,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_terms_text.h_text_widget);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_icon_frm_create (pt_page_data->h_cnt_frm,
                                 (TERMS_TOS_TEXT_X + TERMS_TOS_TEXT_W - TERMS_TOS_TEXT_ICON_W - 4),
                                 TERMS_TOS_TEXT_Y,
                                 TERMS_TOS_TEXT_ICON_W,
                                 TERMS_TOS_TEXT_H,
                                 NULL,
                                 &pt_page_data->t_terms_text.h_icon_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_terms_text.h_icon_frm,
                         2,
                         2,
                         TERMS_TOS_TEXT_ICON_W,
                         TERMS_TOS_TEXT_ICON_H,
                         FE_FNT_SIZE_LARGE,
                         h_g_menu_terms_arrow_up_on,
                         h_g_menu_terms_arrow_up_off,
                         &pt_page_data->t_terms_text.h_icon_up);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_terms_text.h_icon_frm,
                         2,
                         (TERMS_TOS_TEXT_H-TERMS_TOS_TEXT_ICON_H-2),
                         TERMS_TOS_TEXT_ICON_W,
                         TERMS_TOS_TEXT_ICON_H,
                         FE_FNT_SIZE_LARGE,
                         h_g_menu_terms_arrow_down_on,
                         h_g_menu_terms_arrow_down_off,
                         &pt_page_data->t_terms_text.h_icon_down);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _menu_create_scrollbar(pt_page_data->h_cnt_frm,
                                               (TERMS_TOS_TEXT_X + TERMS_TOS_TEXT_W - TERMS_TOS_TEXT_ICON_W - 2),
                                               (TERMS_TOS_TEXT_Y + TERMS_TOS_TEXT_ICON_H + 4),
                                               TERMS_TOS_TEXT_ICON_W,
                                               TERMS_TOS_TEXT_H - TERMS_TOS_TEXT_ICON_H * 2 - 10,
                                               &pt_page_data->t_terms_text.h_scrollbar);
    MENU_CHK_FAIL(i4_ret);
    if (0){
    /* add select region button */
    i4_ret = menu_action_btn_create(pt_page_data->h_cnt_frm,
                                (INT32)15,//14
                                _menu_terms_sel_proc_fct,
                                &pt_page_data->h_btn_sel);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_sel,
                                 MLM_MENU_KEY_TOS_SELECT_REGION,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);
    }

    //menu_action_create
    i4_ret = menu_action_btn_create(pt_page_data->h_cnt_frm,
                                (INT32)15,
                                _menu_vizio_tos_proc_fct,
                                &pt_page_data->h_btn_vizio_tos);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_vizio_tos,
                                 MLM_MENU_KEY_VIZIO_TOS,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    /* add vizio provacy policy button */
    i4_ret = menu_action_btn_create(pt_page_data->h_cnt_frm,
                                (INT32)16,
                                _menu_vizio_pri_proc_fct,
                                &pt_page_data->h_btn_vizio_pri);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_vizio_pri,
                                 MLM_MENU_KEY_VIZIO_PRIVACY_POLICY,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    /* add google tos button */
    i4_ret = menu_action_btn_create(pt_page_data->h_cnt_frm,
                                (INT32)17,
                                _menu_google_tos_proc_fct,
                                &pt_page_data->h_btn_google_tos);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_google_tos,
                                 MLM_MENU_KEY_GOOGLE_TOS,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);


    /* add google privacy policy button */
    i4_ret = menu_action_btn_create(pt_page_data->h_cnt_frm,
                                (INT32)18,
                                _menu_google_pri_proc_fct,
                                &pt_page_data->h_btn_google_pri);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_google_pri,
                                 MLM_MENU_KEY_GOOGLE_PRIVACY_POLICY,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    /* add accept button */
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)10,
                                _menu_terms_btn_proc_fct,
                                &pt_page_data->h_btn_next);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_btn_next,
                                 MLM_MENU_KEY_ACCEPT_ALL,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    memu_action_btn_set_align(pt_page_data->h_btn_next);

    i4_ret = menu_tos_dialog_init();

    i4_ret = _menu_terms_set_nav();
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->b_terms_selected = FALSE;
    pt_page_data->t_terms_text.h_text = NULL_HANDLE;
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm, WGL_SW_HIDE);
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
    INT32           i4_ret;

    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    menu_main_set_title(MLM_MENU_KEY_TERMS_AND_CONDITIONS_TITLE);
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TERMS_OF_SERVICE_HELP));

    _menu_terms_text_set_text(pt_page_data->t_terms_text.h_widget,
                              pt_page_data->t_terms_text.ui2_msg_idx);

    /* update btn text */
    i4_ret = _menu_terms_btn_update_text();
	MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(pt_page_data->h_cnt_frm,WGL_SW_RECURSIVE);
    c_wgl_set_visibility(pt_page_data->t_terms_text.h_text_widget,WGL_SW_HIDE);
    c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
    c_wgl_set_focus(pt_page_data->h_btn_next, WGL_NO_AUTO_REPAINT);

    menu_help_tip_keytip_show(FALSE);

    /* adjust last shadow position */
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_btn_next,
                    FALSE);

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32       i4_ret;

	i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm, WGL_SW_HIDE);

    menu_tos_dialog_hide(TRUE);

    menu_help_tip_keytip_show(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    //TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;
    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);
    t_terms_sub_page_base_data.e_scan_text = MENU_PROTOCOL_SCAN_ACCEPT_ALL;
    c_wgl_set_focus(t_terms_page_data.h_btn_next, WGL_NO_AUTO_REPAINT);
   // _set_page_focus();

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    /* set callback function for backbar */
    menu_set_backbar_proc(NULL);
    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /*close file handle*/
    _text_show_close(&pt_page_data->t_terms_text.h_text);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

static VOID _menu_policy_download_stop_nfy (VOID*   pv_data,
                                         SIZE_T  z_data_size)
{
    TERMS_PAGE_DATA_T*   pt_page_data = &t_terms_page_data;
    UINT8                ui1_country,ui1_lang,ui1_policy;


    if(pt_page_data->b_list_state == FALSE)
    {
        DBG_LOG_PRINT(("[VPP][%s %d] is not list state return \n",__FUNCTION__,__LINE__));
        return;
    }

    SPLIT_ITEM(pt_page_data->ui4_crnt_downloading,ui1_country,ui1_lang,ui1_policy);
    if (a_is_policy_file_exist( (VIZIO_COUNTRY_TYPE_T)ui1_country, (VIZIO_LANG_TYPE_T)ui1_lang,(VIZIO_POLICY_TYPE_T)ui1_policy))
    {
         if(0 != a_get_policy_file_path((VIZIO_COUNTRY_TYPE_T)ui1_country, (VIZIO_LANG_TYPE_T)ui1_lang,(VIZIO_POLICY_TYPE_T)ui1_policy,pt_page_data->s_file_path,sizeof(pt_page_data->s_file_path)))
         {
            DBG_LOG_PRINT(("[VPP][%s %d] ############# failed to get  policy path !#########\n",__FUNCTION__,__LINE__));
            return;
         }
         DBG_LOG_PRINT(("%s,%d [VPP]file path=%s \r\n",__FUNCTION__,__LINE__,pt_page_data->s_file_path));

       if (MENUR_OK == _menu_protocol_text_open())
       {
           pt_page_data->b_is_file_opened = TRUE;
       }
       else
       {
            DBG_LOG_PRINT(("[VPP][%s %d] ############# failed to open  policy path !#########\n",__FUNCTION__,__LINE__));
            return;
       }
    }
    else
    {
       DBG_LOG_PRINT(("[VPP][%s %d] #############  policy file not exist !#########\n",__FUNCTION__,__LINE__));
       return;
    }

    if (FALSE == pt_page_data->b_is_file_opened)
    {
        DBG_LOG_PRINT(("[VPP] show open failed msg. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));
    }
}

static INT32 _menu_policy_download_nfy_cb(UINT16             ui2_nfy_id,
                                                  VOID*              pv_tag,
                                                  ICL_NOTIFY_DATA_T* pt_notify_data)
{
    SIZE_T       z_size ;
    UINT8        ui1_status;
    UINT32       ui4_download_status = ICL_POLICY_DOWNLOAD_ITEM_STOP;
    UINT32       ui4_nfy_item = 0;

    DBG_LOG_PRINT(("[VPP][%s %d]\n",__FUNCTION__,__LINE__));
    if(NULL == pt_notify_data)
    {
        DBG_LOG_PRINT(("[VPP][%s %d] get a invalid nfy data  %d\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    if (ICL_GET_GROUP (pt_notify_data->pe_id[0]) != ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS || ICL_GET_REC(pt_notify_data->pe_id[0]) != ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS)
    {
        DBG_LOG_PRINT(("[VPP][%s %d] get a invalid nfy id  %d\n",__FUNCTION__,__LINE__,ui2_nfy_id));
        return MENUR_FAIL;
    }

    /* get download status */
    z_size = ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS_SIZE;

    if (ICLR_OK != a_icl_get(ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS),
                       &ui4_download_status,
                       &z_size))
    {
        DBG_LOG_PRINT(("[VPP][%s %d] failed to get nfy data!\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }
    GET_POLICY_ITEM_STATE(ui4_download_status,ui1_status);
    GET_POLICY_ITEM(ui4_download_status,ui4_nfy_item);

    if (ICL_POLICY_DOWNLOAD_ITEM_STOP == ui1_status && ui4_nfy_item == t_terms_page_data.ui4_crnt_downloading  && t_terms_page_data.b_list_state == TRUE)
    {
        menu_async_invoke(_menu_policy_download_stop_nfy, NULL, 0, FALSE);
    }

    DBG_LOG_PRINT(("%s,%d [VPP] tos download status = %d.  nfy item = %x downloading item = %x\n",__FUNCTION__,__LINE__, ui1_status,ui4_nfy_item,t_terms_page_data.ui4_crnt_downloading));

    return MENUR_OK;
}

static VOID _menu_back_to_cast_page_from_vizio_policy(VOID)
{
    INT32           i4_ret;

    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    menu_main_set_title(MLM_MENU_KEY_TERMS_AND_CONDITIONS_TITLE);
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TERMS_OF_SERVICE_HELP));

    _menu_terms_text_set_text(pt_page_data->t_terms_text.h_widget,
                              pt_page_data->t_terms_text.ui2_msg_idx);

    /* update btn text */
    i4_ret = _menu_terms_btn_update_text();
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(pt_page_data->h_cnt_frm,WGL_SW_RECURSIVE);
    c_wgl_set_visibility(pt_page_data->t_terms_text.h_text_widget,WGL_SW_HIDE);
    c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);

    if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_TERMS_VIZIO)
    {
        c_wgl_set_focus(pt_page_data->h_btn_vizio_tos, WGL_SYNC_AUTO_REPAINT);
    }
    else if (t_terms_sub_page_base_data.e_scan_text == MENU_PROTOCOL_SCAN_POLICY_VIZIO)
    {
        c_wgl_set_focus(pt_page_data->h_btn_vizio_pri, WGL_SYNC_AUTO_REPAINT);
    }

    menu_help_tip_keytip_show(FALSE);

    /* adjust last shadow position */
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_btn_next,
                    FALSE);

    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->b_list_state = FALSE;
}

/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_page_terms_init(VOID)
{
    t_g_menu_common_page_nw_terms.pf_menu_page_create   = _on_page_create;
    t_g_menu_common_page_nw_terms.pf_menu_page_destroy  = _on_page_destroy;
    t_g_menu_common_page_nw_terms.pf_menu_page_show     = _on_page_show;
    t_g_menu_common_page_nw_terms.pf_menu_page_hide     = _on_page_hide;
    t_g_menu_common_page_nw_terms.pf_menu_page_get_focus= _on_page_get_focus;
    t_g_menu_common_page_nw_terms.pf_menu_page_lose_focus=_on_page_lose_focus;
    t_g_menu_common_page_nw_terms.pf_menu_page_update   = _on_page_update;
    t_terms_page_data.ui2_nty_id = 0;
    return MENUR_OK;
}

#endif  /* APP_DYNAMIC_TOS_SUPPORT */

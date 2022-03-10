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
#include "menu2/menu_util2.h"

#include "menu2/menu.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/download_util/a_download_util.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "res/app_util/config/a_cfg_custom.h"
#endif
#include "menu2/menu_dbg.h"
#include "menu2/menu_network_phase1/menu_network.h"
#include "menu2/menu_network_phase1/menu_tos_dialog.h"


/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define  MENU_DLG_BTN_TEXT_CLR                ((GL_COLOR_T){255, {255}, {255}, {255}})

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

#define  UI4_TXT_INVALUED                     0xffffffff

#define TERMS_ACR_TEXT_X                       (0)
#define TERMS_ACR_TEXT_Y                       (0)
#define TERMS_ACR_TEXT_W                       (MENU_ITEM_V_WIDE)
#define TERMS_ACR_TEXT_H                       (640)

#define TERMS_ACR_TEXT_X_EX                    (64)

#define TERMS_ACR_TEXT_ICON_W                  (10*4/3)
#define TERMS_ACR_TEXT_ICON_H                  (4*4/3)

#define TERMS_ACR_TEXT_UP_ICON_X               (TERMS_ACR_TEXT_X+TERMS_ACR_TEXT_W)
#define TERMS_ACR_TEXT_UP_ICON_Y               (TERMS_ACR_TEXT_Y)

#define TERMS_ACR_TEXT_DOWN_ICON_X             (TERMS_ACR_TEXT_X+TERMS_ACR_TEXT_W)
#define TERMS_ACR_TEXT_DOWN_ICON_Y             (TERMS_ACR_TEXT_Y+TERMS_ACR_TEXT_H)

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
    HANDLE_T    h_scrollbar;
    HANDLE_T    h_icon_up;
    HANDLE_T    h_icon_down;

}TERMS_PAGE_TEXT_T;

typedef struct _TERMS_PAGE_DATA_T
{
    HANDLE_T                h_cnt_frm;
    TERMS_PAGE_TEXT_T       t_acr_text;
    UINT32                  ui4_pro_total_page;
    BOOL                    b_list_state;
    CHAR                    s_file_path[256];
    CHAR                    s_file_tts_path[256];
    BOOL                    b_is_file_opened;
    UINT16                  ui2_tos_nfy_id;
    UINT32                  ui4_crnt_downloading;
}TERMS_PAGE_DATA_T;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_vizio_tos;

TERMS_PAGE_DATA_T    t_acr_page_data;
GL_COLOR_T           t_g_menu_color_acr_txt_nor = { 255, {200}, {200 }, {200 }}; /* Gray color */
GL_COLOR_T           t_g_menu_color_acr_txt_hlt = { 255, {255 }, {255 }, {255}}; /* white color */
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static VOID _text_show_nfy_cb(
                              HANDLE_T               h_handle,
                              const VOID*            pv_pt_txt,
                              TXT_ASYNC_COND_T       e_event,
                              const VOID*            pv_data);

static VOID _text_show_first_page(VOID*   pv_data,
                                  SIZE_T  z_data_size);

static INT32  _text_show_open(const CHAR*     ps_filename,
                              HANDLE_T*       ph_widget,
                              HANDLE_T*       ph_text);

static INT32 _menu_terms_text_set_text(HANDLE_T  h_widget,
                                       UINT32    ui4_msg_id);
extern INT32 memu_action_btn_set_align(HANDLE_T  h_widget);
extern VOID menu_custom_pp_set_pause_flag(UINT8 flag);
extern BOOL menu_custom_pp_get_pause_flag(VOID);


/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

#ifdef APP_TTS_SUPPORT
static INT32 _get_privacy_policy_tts_content(VOID)
{
    struct stat stat_buf;

    if( strlen(t_acr_page_data.s_file_path) > 0 &&
        NULL != strstr(t_acr_page_data.s_file_path,".txt") &&
        0 == stat(t_acr_page_data.s_file_path,&stat_buf) &&
        stat_buf.st_size > 0)
    {
        INT32 i            = 0;
        FILE  *fp_src      = NULL;
        FILE  *fp_dst      = NULL;
        char tmp[256]      = {0};
        char  *tts_content = NULL;

        strncpy(tmp,t_acr_page_data.s_file_path,strlen(t_acr_page_data.s_file_path)- strlen(".txt"));
        snprintf(t_acr_page_data.s_file_tts_path,sizeof(t_acr_page_data.s_file_tts_path),"%s_tts.txt",tmp);
        DBG_LOG_PRINT(("MENU VPP [%s %d] tts path = %s\n",__FUNCTION__,__LINE__,t_acr_page_data.s_file_tts_path));

        if (NULL == (fp_src = fopen(t_acr_page_data.s_file_path,"r")))
        {
            DBG_LOG_PRINT(("VPP open src file %s fail!!!\n",t_acr_page_data.s_file_path));
            return MENUR_FAIL;
        }
        if (NULL == (tts_content = malloc(stat_buf.st_size + 1)))
        {
            DBG_LOG_PRINT(("VPP automan debug!!!heap memory allocation failed\n"));
            fclose(fp_src);
            return MENUR_FAIL;
        }
        if (NULL == (fp_dst = fopen(t_acr_page_data.s_file_tts_path,"w+")))
        {
            DBG_LOG_PRINT(("VPP create dst file %s fail!!!\n",t_acr_page_data.s_file_tts_path));
            free(tts_content);
            fclose(fp_src);
            return MENUR_FAIL;
        }

        if(fread(tts_content,stat_buf.st_size,1,fp_src) <= 0)
        {
            DBG_LOG_PRINT(("VPP read dst file %s fail!!!\n",t_acr_page_data.s_file_tts_path));
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
            DBG_LOG_PRINT(("write dst file %s fail!!!\n",t_acr_page_data.s_file_tts_path));
            free(tts_content);
            fclose(fp_src);
            fclose(fp_dst);
            return MENUR_FAIL;
        }
        DBG_LOG_PRINT(("VPP create dst file %s ok!!!\n",t_acr_page_data.s_file_tts_path));
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
    if(strlen(t_acr_page_data.s_file_tts_path) > 0 &&
       0 == stat(t_acr_page_data.s_file_tts_path,&stat_buf) &&
       stat_buf.st_size > 0)
    {
        a_app_tts_play_file(t_acr_page_data.s_file_tts_path);
    }
}

static VOID _privacy_policy_creat_tts_thread(VOID)
{
    UINT8    switch_status = APP_CFG_TTS_SWITCH_OFF;
    HANDLE_T tos_ttsthread = NULL_HANDLE;

    a_cfg_get_tts_switch_status(&switch_status);
    if (APP_CFG_TTS_SWITCH_OFF == switch_status ||
        VIZIO_LANG_EN != ui2_g_menu_curr_lang)
    {
        c_wgl_set_focus(t_acr_page_data.t_acr_text.h_text_widget, WGL_SYNC_AUTO_REPAINT);
        menu_pm_repaint();
        return ;
    }

    MENU_LOG_ON_FAIL(x_thread_create(
                     &tos_ttsthread,
                     "menu_tos_tts",
                     8192,
                     128,
                     _privacy_policy_tts_play,
                     0,
                     NULL));
}
#endif

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

static VOID _text_show_first_page(VOID* pv_data,
                                  SIZE_T  z_data_size)
{
    TERMS_PAGE_TEXT_T*    ph_text = (TERMS_PAGE_TEXT_T*)pv_data;
    c_txt_get_page_data(ph_text->h_text,
                        (UINT32)1,
                        _text_show_nfy_cb,
                        NULL);
    return;
}

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
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;

    switch(e_event)
    {
        case TXT_ASYNC_COND_SCANING:
            DBG_LOG_PRINT(("\nscanning...\n"));
            DBG_LOG_PRINT(("<VPP> TXT_ASYNC_COND_SCANING current page idx = %d rows = %d \n",(UINT32)pv_data));

            if( pt_page_data->t_acr_text.h_text == h_handle && (1 == (UINT32)pv_data))
            {
                 menu_async_invoke(_text_show_first_page,(VOID*)(&pt_page_data->t_acr_text),sizeof(TERMS_PAGE_TEXT_T),TRUE);
            }

             break;
        case TXT_ASYNC_COND_SCAN_FINISH:
            DBG_LOG_PRINT(("\nscan finished!\n"));
            pt_page_data->ui4_pro_total_page = (UINT32)pv_data;
            DBG_LOG_PRINT(("<VPP> ui4_pro_total_page = %d\n",pt_page_data->ui4_pro_total_page));

            if(pt_page_data->ui4_pro_total_page > 1)
           {
                /* Set  scrollbar Range */
                c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
                          WGL_CMD_PG_SET_RANGE,
                          WGL_PACK((INT32)0),
                          WGL_PACK((INT32)(pt_page_data->ui4_pro_total_page - 1)));
                c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK((INT32)0),
                          NULL);
                c_wgl_set_visibility(pt_page_data->t_acr_text.h_scrollbar,WGL_SW_NORMAL);
                c_wgl_repaint(pt_page_data->t_acr_text.h_scrollbar,NULL,TRUE);
            #ifdef APP_TTS_SUPPORT
                _privacy_policy_creat_tts_thread();
            #endif
           }

            break;
        case TXT_ASYNC_COND_GET_DATA:
        {
            INT32 i4_current_page_num = (INT32)pv_data;

              if( pt_page_data->ui4_pro_total_page > 1)
              {
                    DBG_LOG_PRINT(("######[VPP]get data of page(%d/%d)#####\n",i4_current_page_num, pt_page_data->ui4_pro_total_page));
                    c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
                                 WGL_CMD_PG_SET_POS,
                                 WGL_PACK(TERMS_NUM_TO_PAGE(i4_current_page_num)),
                                 NULL);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_scrollbar, NULL, TRUE);

                if (i4_current_page_num == 1 )
                {
                    c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,FALSE);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                    c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,TRUE);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
               }
               else if(i4_current_page_num == pt_page_data->ui4_pro_total_page)
               {
                    c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,TRUE);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                    c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,FALSE);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
                }
                else
                {
                    c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,TRUE);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                    c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,TRUE);
                    c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
                }
             }
            else if(pt_page_data->ui4_pro_total_page == 1)
            {
                c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,FALSE);
                c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,FALSE);
                c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
            }

            if (pt_page_data->t_acr_text.h_text == h_handle)
            {
                c_wgl_repaint(pt_page_data->t_acr_text.h_text_widget,NULL,TRUE);
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
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
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

static INT32 _menu_tos_protocol_error_msg_show(VOID)
{
    TERMS_PAGE_DATA_T*  pt_page_data = &t_acr_page_data;

    ACFG_COUNTRY_CODE_T             t_country_code = ACFG_COUNTRY_CODE_US;

    a_cfg_custom_get_country_code(&t_country_code);
    if(ACFG_COUNTRY_CODE_US == t_country_code)
    {
        pt_page_data->t_acr_text.ui2_msg_idx = MLM_MENU_KEY_VPP_US_DOWNLOAD_FAILED;
    }
    else if(ACFG_COUNTRY_CODE_CA == t_country_code)
    {
        pt_page_data->t_acr_text.ui2_msg_idx = MLM_MENU_KEY_VPP_CA_DOWNLOAD_FAILED;
    }
    else
    {
        pt_page_data->t_acr_text.ui2_msg_idx = MLM_MENU_KEY_VPP_MX_DOWNLOAD_FAILED;
    }

    _menu_terms_text_set_text(pt_page_data->t_acr_text.h_widget,
                          pt_page_data->t_acr_text.ui2_msg_idx);

    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(MENU_TTS_TEXT(pt_page_data->t_acr_text.ui2_msg_idx), c_uc_w2s_strlen(MENU_TTS_TEXT(pt_page_data->t_acr_text.ui2_msg_idx)));
    #endif

    c_wgl_repaint(pt_page_data->t_acr_text.h_widget, NULL, TRUE);

    pt_page_data->b_list_state = FALSE;

    c_wgl_set_focus(pt_page_data->t_acr_text.h_widget, WGL_NO_AUTO_REPAINT);

    return MENUR_OK;
}

static INT32 _menu_tos_protocol_text_open(VOID)
{
    INT32               i4_ret;
    UINT32              ui4_cur_page = 0;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_acr_page_data;

    if (0 == c_strlen(pt_page_data->s_file_path) || pt_page_data->b_list_state == FALSE)
    {
        DBG_LOG_PRINT(("%s,%d [VPP] get file path fail or is not list state\r\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    DBG_LOG_PRINT(("%s,%d [VPP] file path=%s \r\n",__FUNCTION__,__LINE__,pt_page_data->s_file_path));
    i4_ret = _text_show_open(pt_page_data->s_file_path,
                             &pt_page_data->t_acr_text.h_text_widget,
                             &pt_page_data->t_acr_text.h_text);
    MENU_LOG_ON_FAIL(i4_ret);
    c_wgl_set_visibility(pt_page_data->h_cnt_frm,WGL_SW_RECURSIVE);
    c_wgl_set_visibility(pt_page_data->t_acr_text.h_widget, WGL_SW_HIDE);
    c_wgl_set_visibility(pt_page_data->t_acr_text.h_scrollbar,WGL_SW_HIDE);
    c_wgl_set_visibility(pt_page_data->t_acr_text.h_icon_frm, WGL_SW_RECURSIVE);

    c_wgl_enable(pt_page_data->t_acr_text.h_icon_up, FALSE);
    c_wgl_enable(pt_page_data->t_acr_text.h_icon_down, FALSE);

    i4_ret = _text_show_start_scan(&pt_page_data->t_acr_text.h_text);
    MENU_LOG_ON_FAIL(i4_ret);

    if (MENUR_OK != menu_nav_get_crnt_page(&ui4_cur_page))
    {
        DBG_LOG_PRINT((" %s,%d [VPP]: get crnt page error!\n", __FUNCTION__, __LINE__));
    }

    if (ui4_page_vizio_tos == ui4_cur_page)
    {
        c_wgl_set_focus(pt_page_data->t_acr_text.h_text_widget, WGL_NO_AUTO_REPAINT);
    }

    return MENUR_OK;
}

static VOID _menu_tos_download_stop_nfy (VOID*   pv_data,
                                         SIZE_T  z_data_size)
{
    VIZIO_COUNTRY_TYPE_T e_country;
    VIZIO_LANG_TYPE_T    e_lang;
    TERMS_PAGE_DATA_T*   pt_page_data = &t_acr_page_data;

    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

	if (menu_custom_pp_get_pause_flag() == TRUE)
    {
    	return;
    }

    a_cfg_custom_get_country_code(&t_country_code);

    e_country = (t_country_code == ACFG_COUNTRY_CODE_US ? VIZIO_COUNTRY_US :
                     t_country_code == ACFG_COUNTRY_CODE_CA ? VIZIO_COUNTRY_CA : VIZIO_COUNTRY_MX);
    e_lang = (ui2_g_menu_curr_lang == MLM_MENU_LANG_FRE ? VIZIO_LANG_FR : ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA ? VIZIO_LANG_SPA : VIZIO_LANG_EN);

    if (a_is_policy_file_exist( e_country, e_lang,VIZIO_POLICY_PRIVACY))
    {
         if(0 != a_get_policy_file_path(e_country,e_lang,VIZIO_POLICY_PRIVACY,pt_page_data->s_file_path,sizeof(pt_page_data->s_file_path)))
         {
            DBG_LOG_PRINT(("[VPP][%s %d] ############# failed to get  policy path !#########\n",__FUNCTION__,__LINE__));
            return;
         }
         DBG_LOG_PRINT(("%s,%d [VPP]file path=%s \r\n",__FUNCTION__,__LINE__,pt_page_data->s_file_path));

       if (MENUR_OK == _menu_tos_protocol_text_open())
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
        DBG_INFO(("[VPP] show open failed msg. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        /* just show error msg */
        _menu_tos_protocol_error_msg_show();
    }
}



static INT32 _menu_tos_download_nfy_cb(UINT16             ui2_nfy_id,
                                       VOID*              pv_tag,
                                       ICL_NOTIFY_DATA_T* pt_notify_data)
{
    SIZE_T       z_size ;
    UINT8        ui1_status;
    UINT32       ui4_download_status = ICL_POLICY_DOWNLOAD_ITEM_STOP;
    UINT32       ui4_nfy_item = 0;

    if (ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS != ICL_GET_GROUP (pt_notify_data->pe_id[0]) ||
        ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS != ICL_GET_REC (pt_notify_data->pe_id[0]) ||
        NULL == pt_notify_data)
    {
        DBG_LOG_PRINT(("[VPP][%s %d] invalid download notify !",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }

    /* get download status */
    z_size = ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS_SIZE;

    if (ICLR_OK != a_icl_get(ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS),
                       &ui4_download_status,
                       &z_size))
    {
         DBG_LOG_PRINT(("[VPP][%s %d] invalid download notify !",__FUNCTION__,__LINE__));
         return MENUR_FAIL;
    }

    GET_POLICY_ITEM_STATE(ui4_download_status,ui1_status);
    GET_POLICY_ITEM(ui4_download_status,ui4_nfy_item);

    if (ICL_POLICY_DOWNLOAD_ITEM_STOP == ui1_status && ui4_nfy_item == t_acr_page_data.ui4_crnt_downloading && t_acr_page_data.b_list_state == TRUE )
    {
        menu_async_invoke(_menu_tos_download_stop_nfy, NULL, 0, FALSE);
    }

    DBG_INFO(("%s,%d [VPP] tos download status = %d.\n",__FUNCTION__,__LINE__, ui4_download_status));

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
    INT32   i4_ret;
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
            {
                menu_set_focus_on_backbar(FALSE);
                menu_pm_repaint();
                break;
            }
            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
                break;
            }
            case BTN_RETURN:
            {
                menu_nav_back();
                menu_pm_repaint();
                break;
            }
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }

        break;
    }
    case WGL_MSG_GET_FOCUS:
    {
        break;
    }
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
                                          WGL_STL_TEXT_MAX_DIS_10_LINE),
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_LEFT_CENTER),
                              NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = 10;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK((INT32)(-5)),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = e_font_style;
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
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_acr_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_acr_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_acr_txt_nor);
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
static INT32 _menu_terms_text_set_text(HANDLE_T  h_widget,
                                       UINT32    ui4_msg_id)
{
    INT32 i4_ret = 0;

    i4_ret = c_wgl_do_cmd (h_widget,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (MENU_TEXT(ui4_msg_id)),
                      WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(ui4_msg_id))));
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
static INT32  _text_show_cancel_scan(HANDLE_T*    ph_text)
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
            DBG_ERROR(("\nfail to open file!\n"));
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
            DBG_ERROR(("\nfail to set file encode type!\n"));
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
            DBG_ERROR(("\nfail to set file encode type!\n"));
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


/*-----------------------------------------------------------------------------
 * Name: _text_show_prev_row
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _text_show_prev_row(HANDLE_T     h_text_widget,
                                 HANDLE_T     h_text)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;
    INT32 i4_page_min = 0;
    INT32 i4_pos = 0;

    MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
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
                                 HANDLE_T     h_text)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;
    INT32 i4_pos = 0;
    INT32 i4_page_max = pt_page_data->ui4_pro_total_page - 1;

    MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
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
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;

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
                     if(h_widget == pt_page_data->t_acr_text.h_text_widget)
                     {
                        INT32 i4_pos = 0;
                        INT32 i4_min = 0;

                        MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
                                       WGL_CMD_PG_GET_POS,
                                       WGL_PACK(&i4_pos),
                                       NULL));
                        DBG_LOG_PRINT(("<VPP %s %d> pos = %d min = %d\n",__FUNCTION__,__LINE__,i4_pos,i4_min));
                         /* if current row is first, focus on backbar */
                         if (i4_pos <= i4_min)
                         {
                            c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,FALSE);
                            c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                            menu_set_focus_on_backbar(FALSE);
                            menu_pm_repaint();

                            return MENUR_OK;
                         }

                         _text_show_prev_row(pt_page_data->t_acr_text.h_text_widget,
                                             pt_page_data->t_acr_text.h_text);

                     }
                }
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                if(pt_page_data->b_list_state == TRUE)
                {
                     if(h_widget == pt_page_data->t_acr_text.h_text_widget)
                     {
                        INT32 i4_max = pt_page_data->ui4_pro_total_page - 1;
                        INT32 i4_pos = 0;

                        MENU_CHK_FAIL( c_wgl_do_cmd(pt_page_data->t_acr_text.h_scrollbar,
                                       WGL_CMD_PG_GET_POS,
                                       WGL_PACK(&i4_pos),
                                       NULL));
                        DBG_LOG_PRINT(("<VPP %s %d> pos = %d max = %d\n",__FUNCTION__,__LINE__,i4_pos,i4_max));
                         /* if current row is the end-row, focus on helptip */
                         if (i4_pos >= i4_max)
                         {
                             c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,FALSE);
                             c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
                          //   c_wgl_set_focus(pt_page_data->h_terms_btn_accept, WGL_SYNC_AUTO_REPAINT);
                             menu_pm_repaint();
                             return MENUR_OK;
                         }

                          _text_show_next_row(pt_page_data->t_acr_text.h_text_widget,
                                              pt_page_data->t_acr_text.h_text);

                             c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,TRUE);
                             c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                     }
                }

                return MENUR_OK;
            case BTN_RETURN:
                t_acr_page_data.b_list_state = FALSE;
                _text_show_cancel_scan(&pt_page_data->t_acr_text.h_text);
                _menu_terms_text_set_text(pt_page_data->t_acr_text.h_text_widget,MLM_MENU_KEY_EMPTY);
                menu_nav_back();
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
static INT32 _menu_terms_text_widget_create(HANDLE_T     h_parent,
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

    t_inset.i4_left     = 5;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 2;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = e_font_style;
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
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_acr_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_acr_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_acr_txt_nor);
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
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          (INT32)(0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

     /* set page scrolling style */
    MENU_CHK_FAIL(c_wgl_do_cmd (*ph_widget,
                WGL_CMD_TEXT_SET_PAGE_SCROL,
                WGL_PACK(WGL_TEXT_PS_TYPE_REPLACE_ALL),
                NULL));
    return MENUR_OK;
}

INT32 _menu_terms_text_scrollbar_create(
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
static INT32 _menu_terms_text_icon_create(HANDLE_T     h_parent,
                                          INT32        i4_left,
                                          INT32        i4_top,
                                          INT32        i4_width,
                                          INT32        i4_height,
                                          FE_FNT_STYLE e_font_style,
                                          HANDLE_T     h_normal_bk,
                                          HANDLE_T     h_disable_bk,
                                          HANDLE_T*    ph_widget)
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
        DBG_ERROR(("\nFailed to create icon!\n"));
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
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;
    INT32              i4_ret;
    WGL_KEY_LINK_T     at_key_lnk[2];
    HANDLE_T           h_backbar;

    menu_get_backbar_handle(&h_backbar);
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_backbar;
    i4_ret = c_wgl_set_navigation(pt_page_data->t_acr_text.h_widget, 1, at_key_lnk);
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
static INT32 _backbar_proc_fct (HANDLE_T   h_widget,
                                UINT32     ui4_msg,
                                VOID*      param1,
                                VOID*      param2
    )
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[64] = {0};
        c_uc_ps_to_w2s("back", w2s_str, 64);
        a_app_tts_play(w2s_str, 64);
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
            t_acr_page_data.b_list_state = FALSE;
            _text_show_cancel_scan(&pt_page_data->t_acr_text.h_text);
            _menu_terms_text_set_text(pt_page_data->t_acr_text.h_text_widget,MLM_MENU_KEY_EMPTY);
            menu_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            if(pt_page_data->b_is_file_opened == TRUE)
            {
                c_wgl_set_focus(pt_page_data->t_acr_text.h_text_widget, WGL_SYNC_AUTO_REPAINT);
            }
            else
            {
                c_wgl_set_focus(pt_page_data->t_acr_text.h_widget, WGL_SYNC_AUTO_REPAINT);
            }
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
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       param1,
                                VOID*       param2
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
            t_acr_page_data.b_list_state = FALSE;
            return MENUR_OK ;
        case BTN_RETURN:
            menu_nav_back();
            t_acr_page_data.b_list_state = FALSE;
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

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;
    INT32     i4_ret;

    c_memset(pt_page_data, 0, sizeof(TERMS_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_ACR_TEXT_X,
                         TERMS_ACR_TEXT_Y,
                         TERMS_ACR_TEXT_W - TERMS_ACR_TEXT_X_EX,
                         TERMS_ACR_TEXT_H,
                         FE_FNT_SIZE_LARGE,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &pt_page_data->t_acr_text.h_widget);
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->t_acr_text.ui2_msg_idx = MLM_MENU_KEY_NETWORK_ACR_TEXT;

    i4_ret = _menu_terms_text_widget_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_ACR_TEXT_X_EX,
                         TERMS_ACR_TEXT_Y,
                         TERMS_ACR_TEXT_W - TERMS_ACR_TEXT_X_EX - 2,
                         TERMS_ACR_TEXT_H,
                         FE_FNT_SIZE_LARGE,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &pt_page_data->t_acr_text.h_text_widget);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_icon_frm_create (pt_page_data->h_cnt_frm,
                                 (TERMS_ACR_TEXT_X + TERMS_ACR_TEXT_W - TERMS_ACR_TEXT_ICON_W - 2),
                                 TERMS_ACR_TEXT_Y,
                                 TERMS_ACR_TEXT_ICON_W,
                                 TERMS_ACR_TEXT_H,
                                 NULL,
                                 &pt_page_data->t_acr_text.h_icon_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_acr_text.h_icon_frm,
                         0,
                         2,
                         TERMS_ACR_TEXT_ICON_W,
                         TERMS_ACR_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_up_on,
                         h_g_menu_terms_arrow_up_off,
                         &pt_page_data->t_acr_text.h_icon_up);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_acr_text.h_icon_frm,
                         0,
                         (TERMS_ACR_TEXT_H-TERMS_ACR_TEXT_ICON_H-2),
                         TERMS_ACR_TEXT_ICON_W,
                         TERMS_ACR_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_down_on,
                         h_g_menu_terms_arrow_down_off,
                         &pt_page_data->t_acr_text.h_icon_down);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_scrollbar_create(pt_page_data->h_cnt_frm,
                                               (TERMS_ACR_TEXT_X + TERMS_ACR_TEXT_W - TERMS_ACR_TEXT_ICON_W - 2),
                                               (TERMS_ACR_TEXT_Y + TERMS_ACR_TEXT_ICON_H + 4),
                                               TERMS_ACR_TEXT_ICON_W,
                                               TERMS_ACR_TEXT_H - TERMS_ACR_TEXT_ICON_H * 2 - 10,
                                               &pt_page_data->t_acr_text.h_scrollbar);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _menu_terms_set_nav();
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->b_list_state = FALSE;

    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    return MENUR_OK;
}


static VOID _menu_tos_dialog_btn_cb_fct(UINT32 ui4_key_code)
{
    menu_tos_dialog_hide(TRUE);
    menu_set_focus_on_backbar(TRUE);
    menu_pm_repaint();
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32   i4_ret;
    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;

    if (pt_page_data->ui2_tos_nfy_id == 0)
    {
        i4_ret = a_icl_notify_reg(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS,
                                  ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS,
                                  NULL,
                                  NULL,
                                  _menu_tos_download_nfy_cb,
                                  &(pt_page_data->ui2_tos_nfy_id));


        if(ICLR_OK != i4_ret)
        {
            pt_page_data->ui2_tos_nfy_id = 0;
            return MENUR_FAIL;
        }
    }
    a_cfg_custom_get_country_code(&t_country_code);
    menu_main_set_title(MLM_MENU_KEY_VIZIO_PRIVACY_POLICY);
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    pt_page_data->t_acr_text.ui2_msg_idx = MLM_MENU_KEY_NETWORK_ACR_TEXT;

    _menu_terms_text_set_text(pt_page_data->t_acr_text.h_widget,
                              pt_page_data->t_acr_text.ui2_msg_idx);
    pt_page_data->b_list_state = FALSE;
    pt_page_data->b_is_file_opened = FALSE;

    if(pt_page_data->b_list_state == FALSE)
    {
        _menu_terms_text_set_text(pt_page_data->t_acr_text.h_widget,MLM_MENU_KEY_EMPTY);
        pt_page_data->b_list_state = TRUE;

        if(0 == a_nw_connection_test((CHAR*)"www.google.com")  || 0 == a_nw_connection_test6((CHAR*)"www.google.com") )
        {
            VIZIO_COUNTRY_TYPE_T e_country;
            VIZIO_LANG_TYPE_T e_lang;

            e_country = (t_country_code == ACFG_COUNTRY_CODE_US ? VIZIO_COUNTRY_US :
                     t_country_code == ACFG_COUNTRY_CODE_CA ? VIZIO_COUNTRY_CA : VIZIO_COUNTRY_MX);
            e_lang = (ui2_g_menu_curr_lang == MLM_MENU_LANG_FRE ? VIZIO_LANG_FR : ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA ? VIZIO_LANG_SPA : VIZIO_LANG_EN);
            a_url_download(e_country, e_lang, VIZIO_POLICY_PRIVACY);
            MAKE_ITEM(t_acr_page_data.ui4_crnt_downloading,e_country, e_lang, VIZIO_POLICY_PRIVACY);
            c_strcpy(pt_page_data->s_file_path, "");
        }
        else
        {
#if 0
            snprintf(pt_page_data->s_file_path,sizeof(pt_page_data->s_file_path),"%s",
                ui2_g_menu_curr_lang == MLM_MENU_LANG_FRE ? "/3rd/tos/vizio_privacy_policy_ca.txt" :
                ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA ? "/3rd/tos/vizio_privacy_policy_mx.txt" : "/3rd/tos/vizio_privacy_policy_usa.txt");
                DBG_LOG_PRINT(("%s,%d [VPP]file path=%s \r\n",__FUNCTION__,__LINE__,pt_page_data->s_file_path));
            i4_ret = _menu_tos_protocol_text_open();
            if (MENUR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] text open fail \r\n",__FUNCTION__,__LINE__));
            }
            else
            {
                pt_page_data->b_is_file_opened = TRUE;
            }
#else
        menu_tos_dialog_show(MLM_MENU_KEY_VIZIO_PRI_DLG_TITLE,
                             t_country_code == ACFG_COUNTRY_CODE_US ? MLM_MENU_KEY_VIZIO_PRI_DLG_TEXT :
                             t_country_code  == ACFG_COUNTRY_CODE_CA ? MLM_MENU_KEY_VIZIO_PRI_DLG_TEXT_CA: MLM_MENU_KEY_VIZIO_PRI_DLG_TEXT_MX,
                             MLM_MENU_KEY_OK,
                             _menu_tos_dialog_btn_cb_fct,
                             TRUE);
#endif
        }
    }
    menu_custom_pp_set_pause_flag(FALSE);
    menu_pm_repaint();
    menu_help_tip_keytip_show(FALSE);
	/* adjust last shadow position */
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->t_acr_text.h_widget,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;
    INT32       i4_ret;

    t_acr_page_data.b_list_state = FALSE;
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm, WGL_SW_HIDE);
    /*clean all string */
    c_wgl_do_cmd(
        pt_page_data->t_acr_text.h_text_widget,
        WGL_CMD_TEXT_STRING_CLEAR,
        NULL,
        NULL);
    DBG_INFO(("i4_ret=%d\n", i4_ret));

    menu_help_tip_keytip_show(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;
    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_acr_page_data;
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL);
    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);
    _text_show_cancel_scan(&pt_page_data->t_acr_text.h_text);
    /*close file handle*/
    _text_show_close(&pt_page_data->t_acr_text.h_text);
#ifdef APP_TTS_SUPPORT
    a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_page_acr_init(VOID)
{
    t_g_menu_common_page_vizio_tos.pf_menu_page_create     = _on_page_create;
    t_g_menu_common_page_vizio_tos.pf_menu_page_destroy    = _on_page_destroy;
    t_g_menu_common_page_vizio_tos.pf_menu_page_show       = _on_page_show;
    t_g_menu_common_page_vizio_tos.pf_menu_page_hide       = _on_page_hide;
    t_g_menu_common_page_vizio_tos.pf_menu_page_get_focus  = _on_page_get_focus;
    t_g_menu_common_page_vizio_tos.pf_menu_page_lose_focus = _on_page_lose_focus;
    t_g_menu_common_page_vizio_tos.pf_menu_page_update     = _on_page_update;

    return MENUR_OK;
}

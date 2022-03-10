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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_timg.h"

#include "u_sb_atsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_cli.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_dt.h"
#include "wfd/wfd.h"
#include "wfd/wfd_dev_list.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_util2.h"
#include "menu_page_input_ope_lst.h"
#include "menu2/menu_device/menu_page_device_setting_no_wifi_remote.h"
#include "menu_device.h"

#include "wizard/a_wzd.h"
#include "app_util/a_isl.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/menu2/menu_custom.h"
#include "app_util/a_cfg.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "mtvdecex.h"
#include "nav/input_src/a_input_src.h"
#include "rest/a_rest_event.h"

#define OPE_LST_INIT_LEN        (7)
#define OPE_LST_IDX_NAME        (0)
#define OPE_LST_IDX_FULL_COLOR  (1)
#define OPE_LST_IDX_FULL_CHROMA (2)
#define OPE_LST_IDX_VGA_AUTO    (3)
#define OPE_LST_IDX_PIC_SZ      (4)
#define OPE_LST_IDX_PIC_POS     (5)
#define OPE_LST_IDX_HIDE        (6)

#define OPE_LST_VIEW_MAX_TITLE_NAME_LEN 63


typedef struct {
    HANDLE_T  h_wgt;
    BOOL      b_is_visibility;
    BOOL      b_is_enable;
} _OPE_LST_T;

#if ENABLE_HDMI_EDID_NEW_METHOD

// For convert ACFG to Glue
static UINT8 driver_edid_table[3] =
{
    GLUE_EDID_IDX_1_4, // ACFG_EDID_SEL_1_4
    GLUE_EDID_IDX_2_1, // ACFG_EDID_SEL_2_1

 #ifdef MT5583_MODEL
    GLUE_EDID_IDX_2_0 // ACFG_EDID_SEL_AUTO
 #else  // #ifdef MT5583_MODEL
    GLUE_EDID_IDX_AUTO // ACFG_EDID_SEL_AUTO
 #endif // #ifdef MT5583_MODEL
};

#else

// Driver means glue
#ifdef MT5583_MODEL
    #define DRIVER_EDID_AUTO (1)
#else  // #ifdef MT5583_MODEL
    #define DRIVER_EDID_AUTO (2)
#endif // #ifdef MT5583_MODEL
#define DRIVER_EDID_1_4  (0)
#define DRIVER_EDID_2_1  (3)

// For convert ACFG to Glue
static UINT8 driver_edid_table[3] =
{
    DRIVER_EDID_1_4,
    DRIVER_EDID_2_1,
    DRIVER_EDID_AUTO
};

#endif


static WGL_INSET_T t_inset_border = {
    MENU_ITEM_V_CNT_INSET_L + MENU_ITEM_V_TITLE_W,
    0,
    0,
    0};
static GL_RECT_T   t_rect_border_title = {
    65,
    0,
    MENU_ITEM_V_TITLE_W,
    MENU_ITEM_V_HEIGHT};

static UINT16 ui2_help_tip_key[OPE_LST_INIT_LEN] = {
                                MLM_MENU_KEY_HELP_NAME_INPUT,
                                MLM_MENU_KEY_FULL_COLOR_HELP,
                                MLM_MENU_KEY_HELP_FULL_CHROMA,
                                MLM_MENU_KEY_HELP_TIP_TV_SETTING_AUTO_SYNC,
                                MLM_MENU_KEY_HELP_SZ_POS,
                                MLM_MENU_KEY_HELP_SZ_POS,
                                MLM_MENU_KEY_HELP_HIDE_INPUT
                                };

static UINT32* pui4_page_id[OPE_LST_INIT_LEN] = {
                                &ui4_g_menu_page_inp_naming,
                                NULL,
                                NULL,
                                &ui4_g_menu_page_vga_auto,
                                &ui4_g_menu_page_pic_size,
                                &ui4_g_menu_page_pic_postion,
                                NULL
                                };

static UINT16 ui2_ope_lst_elem_name[OPE_LST_INIT_LEN] = {
                                MLM_MENU_KEY_NAME_INPUT,
                                MLM_MENU_KEY_FULL_COLOR,
                                MLM_MENU_KEY_FULL_CHROMA,
                                MLM_MENU_KEY_VGA_AUTO,
                                MLM_MENU_KEY_ADJUST_PIC_SIZE,
                                MLM_MENU_KEY_ADJUST_PIC_POS,
                                MLM_MENU_KEY_HIDE_FROM_INPUT_LIST
                                };


static UINT8        ui_hdmi_format = 0;

#define PIC_MODE_COMPUTER  (5)

typedef INT32 (*ope_lb2_proc_fct)(HANDLE_T            h_widget,
                                    UINT32              ui4_msg,
                                    VOID*               pv_param1,
                                    VOID*               pv_param2);
/* should define in menu_paga_input_ope_lst.h better end */

typedef enum _MENU_PAGE_INPUT_OPE_LST_SETTING_FOCUS_PAGE_T
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_UNKNOW = -1,
    MENU_PAGE_INPUT_OPE_LST_SETTING_MAIN = 0,
    MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_CHROMA,
    MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_COLOR,
    MENU_PAGE_INPUT_OPE_LST_SETTING_HIDE_DEVICE,
    MENU_PAGE_INPUT_OPE_LST_SETTING_FOCUS_PAGE_COUNT
} MENU_PAGE_INPUT_OPE_LST_SETTING_FOCUS_PAGE_T;

typedef struct _MENU_PAGE_INPUT_OPE_LST_SETTING_T
{
    /* member */
    HANDLE_T     h_svctx_main;
    HANDLE_T     h_full_clor_timer;

    /* status */
    MENU_PAGE_INPUT_OPE_LST_SETTING_FOCUS_PAGE_T     e_focus_page;
    ISL_REC_T           t_isl_rec_of_dev;
    INT16               i2_hlt_idx;
    BOOL                b_is_444_content;

    /* icl */

    /* acfg */
    UINT16              ui2_cfg_pic_mode_nfy_id;

    /* view */
    HANDLE_T            h_full_chroma_lb2;
    HANDLE_T            h_hide_device_lb2;
    HANDLE_T            h_full_color_lb2;
    _OPE_LST_T          t_ope_lst[OPE_LST_INIT_LEN];

    /*view status*/
    UTF16_T             w2s_input[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1];

    /* function */
} MENU_PAGE_INPUT_OPE_LST_SETTING_T;

static MENU_PAGE_INPUT_OPE_LST_SETTING_T t_this_page;

MENU_PAGE_FCT_TBL_T t_g_menu_input_ope_list;

static VOID  _ope_lst_move_help_tip(UINT8 ui1_row_num);

static INT32 _ope_lst_update_focus(BOOL b_repaint);
static INT32 _ope_lst_set_focus_next(BOOL b_repaint);

static INT32 _ope_lst_page_update_select_isl_status(VOID);
static INT32 _ope_lst_get_dev_inpt_src_idx(UINT8  *pui1_input_src_idx);

static INT32 _ope_lst_main_page_update_v_e(VOID);
static INT32 _ope_lst_main_page_set_v_e(ISL_REC_T t_isl_rec);
static INT32 _ope_lst_main_page_show(VOID);
static INT32 _ope_lst_page_main_page_hide(VOID);
static INT32 _ope_lst_main_page_refresh(BOOL b_repaint);
static INT32 _ope_lst_main_page_move_item(VOID);

static INT32 _ope_lst_hide_device_page_hide(VOID);
static INT32 _ope_lst_hide_device_page_show(VOID);
static INT32 _ope_lst_set_hide_from_input_list(UINT8 ui1_value);
static INT32 _ope_lst_get_hide_from_input_list(UINT8* ui1_value);

static INT32 _ope_lst_full_chroma_page_hide(VOID);
static INT32 _ope_lst_full_chroma_page_show(VOID);

static INT32 _ope_lst_full_color_page_hide(VOID);
static INT32 _ope_lst_full_color_page_show(VOID);


static INT32 _ope_lst_get_full_uhd_color(UINT8* ui1_value);
static INT32 _ope_lst_set_full_uhd_color(UINT8 ui1_value);
static INT32 _full_uhd_clo_info_send_string_to_nav(WDK_TOAST_T *pt_toast);

static VOID _full_clor_timer_nfy( HANDLE_T                    h_timer,
                                        VOID*                       pv_tag
                                        );
static VOID _full_uhd_clo_info_send_string_to_nav_fct(VOID*        pv_tag1,
                                                                    VOID*        pv_tag2,
                                                                    VOID*        pv_tag3);
static BOOL _ope_lst_pic_mode_is_computer_mode(VOID);

static INT32 _ope_lst_page_set_default_status(VOID);

static INT32 _ope_lst_get_hdmi_color_space(MENU_HDMI_IF_CLR_SPC *pe_color_space);

static INT32 _ope_lst_get_hdmi2_0_is_support(UINT8 ui1_hdmi_port,BOOL *pb_support);
static INT32 _atoi_one_char( const CHAR* ps );

static VOID _tts_play(UINT16 fir_mlm_key, UINT16 sec_mlm_key, BOOL b_sec_exist)
{
#ifdef  APP_TTS_SUPPORT
    UTF16_T w2s_str[64+1] = {0};

    c_uc_w2s_strcpy(w2s_str, mlm_menu_get_text(0, fir_mlm_key));
    c_uc_w2s_strcat(w2s_str, (UTF16_T *)L"  ");
    if (b_sec_exist)
    {
        c_uc_w2s_strcat(w2s_str, mlm_menu_get_text(0, sec_mlm_key));
    }
    a_app_tts_play(w2s_str, 64);
#endif
}

static BOOL _check_is_dobly_vision(VOID)
{
    /* dolby vision  */
    UTF16_T              w2s_tmp_str[128] = {0};
    INT32                i4_ret = MENUR_OK;
    UTF16_T              w2s_str[128] = {0};
    SCC_VID_HDR_TYPE_T   t_hdr_type;
    SCC_DOVI_INFO_T      t_dolby_vision;
    /* Get SCC handle by display name. */
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1];
    HANDLE_T h_scc_comp = NULL_HANDLE;

    /* HDR TYPE */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                  h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

    i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("%s,%d, t_hdr_type=%d.\r\n",__FUNCTION__, __LINE__,(UINT32)t_hdr_type));

    c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
    i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
    DBG_LOG_PRINT(("[Dolby Vision]%s,%d, t_dolby_vision.ui1_is_doviHDR=(%d).\r\n",__FUNCTION__, __LINE__,(UINT32)t_dolby_vision.ui1_is_doviHDR));

    if(t_dolby_vision.ui1_is_doviHDR != 0 || t_hdr_type > 0)
    {
        return TRUE ;
    }

    return FALSE;
}


INT32 menu_input_ope_lst_page_set_title(UTF16_T *pw2s_input)
{
    INT32 i4_ret = MENUR_OK;

    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if(pw2s_input == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_uc_w2s_strncpy(pt_this->w2s_input, pw2s_input, MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);

    /* common  setting */
    i4_ret =  _ope_lst_page_set_default_status();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_page_set_default_status(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    i4_ret = _ope_lst_page_update_select_isl_status();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _ope_lst_main_page_update_v_e();
    MENU_CHK_FAIL(i4_ret);

    /* set default page */
    {
        pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_MAIN;
    }

    /* set default focus index */
    {
        INT16 i2_i;
        pt_this->i2_hlt_idx = -1;
        {
            for (i2_i = 0; i2_i < OPE_LST_INIT_LEN; i2_i++)
            {
               if (pt_this->t_ope_lst[i2_i].b_is_visibility == TRUE && pt_this->t_ope_lst[i2_i].b_is_enable == TRUE)
               {
                   pt_this->i2_hlt_idx = (INT16)i2_i;
                   break;
               }
            }
        }
    }

    return MENUR_OK;
}

static INT32 _ope_lst_page_update_select_isl_status()
{
    INT32 i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    /* Get */
    UINT8 ui1_idx;
    i4_ret = _ope_lst_get_dev_inpt_src_idx(&ui1_idx);
    MENU_CHK_FAIL(i4_ret);

    /* set t_isl_rec_of_dev */
    i4_ret = a_isl_get_rec_by_idx(ui1_idx, &pt_this->t_isl_rec_of_dev);
    MENU_CHK_FAIL(i4_ret == ISLR_OK ? MENUR_OK : i4_ret);

    return MENUR_OK;

}

static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32 i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        menu_pm_repaint();
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
            case BTN_RETURN :
            case BTN_SELECT :
            {
                switch(pt_this->e_focus_page )
                {
                    case MENU_PAGE_INPUT_OPE_LST_SETTING_MAIN:
                    {
                        i4_ret = menu_device_page_nav_go_no_wifi_remote(NAV_DEVICE_SETTING_PAGE_FROM_INPUT_OPE_LST_PAGE, NULL);
                        MENU_CHK_FAIL(i4_ret);
                    }
                    break;
                    case MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_CHROMA:
                    {
                        pt_this->i2_hlt_idx = OPE_LST_IDX_FULL_CHROMA;
                        i4_ret = _ope_lst_full_chroma_page_hide();
                        MENU_CHK_FAIL(i4_ret);
                        i4_ret = _ope_lst_main_page_show();
                        MENU_CHK_FAIL(i4_ret);
                    }
                    break;
                    case MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_COLOR:
                    {
                        pt_this->i2_hlt_idx = OPE_LST_IDX_FULL_COLOR;
                        i4_ret = _ope_lst_full_color_page_hide();
                        MENU_CHK_FAIL(i4_ret);
                        i4_ret = _ope_lst_main_page_show();
                        MENU_CHK_FAIL(i4_ret);
                    }
                    break;
                    case MENU_PAGE_INPUT_OPE_LST_SETTING_HIDE_DEVICE:
                    {
                        pt_this->i2_hlt_idx = OPE_LST_IDX_HIDE;
                        i4_ret = _ope_lst_hide_device_page_hide();
                        MENU_CHK_FAIL(i4_ret);
                        i4_ret = _ope_lst_main_page_show();
                        MENU_CHK_FAIL(i4_ret);
                    }
                    break;

                    default:
                    {
                        MENU_CHK_FAIL(MENUR_INV_STATE);
                    }
                    break;
                }
            }
                break;
            case BTN_CURSOR_DOWN:
            {
                pt_this->i2_hlt_idx = 0;
                i4_ret = _ope_lst_update_focus(TRUE);
                MENU_CHK_FAIL(i4_ret);
            }
                break;
            default :
                break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32  _ope_lst_get_dev_inpt_src_idx(UINT8  *pui1_input_src_idx)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info = {0};

    if(pui1_input_src_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    do
    {
        if (a_cfg_custom_get_wifi_remote_support())
        {
            i4_ret = menu_device_get_device_info(&t_device_info);
        }
        else
        {
            i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
        }

        MENU_BREAK_ON_FAIL(i4_ret);

        if (t_device_info.e_current_device_type == MENU_DEVICE_TYPE_INPUT)
        {
            *pui1_input_src_idx = t_device_info.u_device_data.t_input.ui1_input_src_idx;
        }
        else
        {

        }
    }while(0);
    c_mem_free(t_device_info.u_device_data.t_input.pw2s_user_name);
    c_mem_free(t_device_info.u_device_data.t_input.pw2s_disp_name);

    return MENUR_OK;
}

static INT32 _ope_lst_set_focus_prev(BOOL b_repaint)
{
    INT32 i4_ret;
    INT16 i2_i;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    for (i2_i = pt_this->i2_hlt_idx - 1; i2_i >= 0; i2_i--)
    {
        if (pt_this->t_ope_lst[i2_i].b_is_visibility &&
            pt_this->t_ope_lst[i2_i].b_is_enable)
        {
            pt_this->i2_hlt_idx = i2_i;

            i4_ret = c_wgl_set_focus( pt_this->t_ope_lst[i2_i].h_wgt, b_repaint);
            MENU_LOG_ON_FAIL(i4_ret);

            return i4_ret;
        }
    }

    if (i2_i == -1)
    {
        pt_this->i2_hlt_idx = -1;
        i4_ret = menu_set_focus_on_backbar(b_repaint);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_FAIL;
}

static INT32 _ope_lst_set_focus_next(BOOL b_repaint)
{
    INT32 i4_ret;
    UINT16 ui2_i;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    for (ui2_i = pt_this->i2_hlt_idx+1; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
    {
        if (pt_this->t_ope_lst[ui2_i].b_is_visibility &&
            pt_this->t_ope_lst[ui2_i].b_is_enable)
        {
            pt_this->i2_hlt_idx = (INT16)ui2_i;

            i4_ret = c_wgl_set_focus(pt_this->t_ope_lst[ui2_i].h_wgt, b_repaint);
            MENU_LOG_ON_FAIL(i4_ret);

            return i4_ret;
        }
    }

    return MENUR_FAIL;
}

/**/
static INT32 _ope_lst_set_graphic_hdmi_mode(BOOL b_set)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HDMI_MODE);
    INT16 i2_vid_hdmi_mode = SCC_VID_HDMI_MODE_UNKNOWN;
    a_cfg_av_get(ui2_id, &i2_vid_hdmi_mode);

    {
        i2_vid_hdmi_mode = SCC_VID_HDMI_MODE_UNKNOWN;
        if (b_set)
        {
            i2_vid_hdmi_mode = SCC_VID_HDMI_MODE_GRAPHIC;
        }
        else
        {
            i2_vid_hdmi_mode = SCC_VID_HDMI_MODE_AUTO;
        }
    }

    DBG_LOG_PRINT(("< UHD color > %s %d i2_vid_hdmi_mode : %d \n",__FUNCTION__,__LINE__,i2_vid_hdmi_mode));
    a_cfg_av_set(ui2_id, i2_vid_hdmi_mode);
    a_cfg_av_update(ui2_id);

    return MENUR_OK;
}

static INT32 a_cfg_cust_set_full_chroma_by_index(UINT16 ui2_hdmi_idx, BOOL b_on)
{
    UINT8 ui1_chroma_value = 0;

    MENU_CHK_FAIL(a_cfg_cust_get_full_color_444(&ui1_chroma_value));
    DBG_LOG_PRINT(("<FULL CHROMA> file: %s line: %d  %s a_cfg_cust_get_full_chroma_444(%d) ui1_hdmi_index: %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_chroma_value, ui2_hdmi_idx));
    if(b_on)
    {
        ui1_chroma_value |= (UINT8)1 << ui2_hdmi_idx;
    }
    else
    {
        ui1_chroma_value &= ~((UINT8)1 << ui2_hdmi_idx);
    }

    DBG_LOG_PRINT(("<FULL CHROMA> file: %s line: %d  %s a_cfg_cust_set_full_chroma_444(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_chroma_value));

    MENU_CHK_FAIL(a_cfg_cust_set_full_color_444((UINT8)ui1_chroma_value));
    return MENUR_OK;
}

UINT32 a_cfg_cust_set_full_chroma_by_source(UINT8 i2_on_off_idx)
{
    INT32                               i4_ret = MENUR_OK;
    UTF16_T                             w2s_hdmi_index;
    CHAR                                c_hdmi_index;
    MENU_DEVICE_PAGE_DEVICE_INFO_T      t_device_info;
    static UINT32                       ui4_full_chroma_hlt_idx;

    //1, get hdmi index
    c_memset(&t_device_info, 0, sizeof(MENU_DEVICE_PAGE_DEVICE_INFO_T));

    i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
    MENU_CHK_FAIL(i4_ret);

    /*should be HDMI-x*/
    if(c_uc_w2s_strlen(t_device_info.u_device_data.t_input.pw2s_disp_name) > 5)
    {
        w2s_hdmi_index = c_uc_w2s_get(t_device_info.u_device_data.t_input.pw2s_disp_name, 5);
    }
    else
    {
        w2s_hdmi_index = L'1';
    }
    c_uc_w2s_to_ps(&w2s_hdmi_index, &c_hdmi_index, sizeof(CHAR));
    ui4_full_chroma_hlt_idx = _atoi_one_char(&c_hdmi_index);

    //2, set ui1_color_value to acfg
    a_cfg_cust_set_full_chroma_by_index(ui4_full_chroma_hlt_idx - 1, i2_on_off_idx == 1);

    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}
INT32 inp_set_full_chroma_by_hdmi_idx(UINT16 ui2_hidmi_idx, BOOL b_on)
{
    MENU_CHK_FAIL(a_cfg_cust_set_full_chroma_by_index(ui2_hidmi_idx, b_on));
    MENU_CHK_FAIL(_ope_lst_set_graphic_hdmi_mode(!_check_is_dobly_vision() && b_on));
    return MENUR_OK;
}
static INT32 _ope_lst_set_full_chroma(VOID)
{
    INT32                               i4_ret = MENUR_OK;
    UINT16                              ui2_hlt_idx;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if (pt_this->i2_hlt_idx != OPE_LST_IDX_FULL_CHROMA)
    {
        return MENUR_FAIL;
    }

    //2, set ui1_color_value to acfg
    if (menu_list_get_idx(pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].h_wgt, &ui2_hlt_idx) == MENUR_OK)
    {
        ui2_hlt_idx ^= 1;
        a_cfg_cust_set_full_chroma_by_source(ui2_hlt_idx);
    }
    _tts_play(MLM_MENU_KEY_FULL_CHROMA,ui2_hlt_idx == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF,TRUE);

    if (_check_is_dobly_vision() == TRUE)
    {
        ui2_hlt_idx = 0;
    }
    _ope_lst_set_graphic_hdmi_mode((ui2_hlt_idx == 1) ? TRUE : FALSE);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_adjust_rect
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
INT32 _ope_lst_adjust_hide_input_rect(HANDLE_T h_widget, UINT8 ui1_cnt_index)
{
    INT32          i4_ret = MENUR_OK;
    UTF16_T        w2s_str[33]    = {0};
    INT32          i4_width_left  = 0;
    INT32          i4_width_right = 0;
    INT32          i4_hight;
    WGL_INSET_T    t_inset;
    INT32          i4_text_width = 0;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect_temp;
    WGL_INSET_T                 t_inset_temp;

    if(ui1_cnt_index == 0)
    {
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE),
                            c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE)));
    }
    else if(ui1_cnt_index == 1)
    {
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE),
                    c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE)));
    }

     i4_ret = c_fe_get_string_size(menu_page_get_font_h(),
                          w2s_str,
                          c_uc_w2s_strlen(w2s_str),
                          (INT32*)&i4_text_width,
                          (INT32*)&i4_hight);
     if(AEER_OK != i4_ret)
     {
         return MENUR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_get_size(h_g_menu_img_list_item_leftarrow,(UINT32*)&i4_width_left,(UINT32*)&i4_hight);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_img_tpl_get_size(h_g_menu_img_list_item_rightarrow,(UINT32*)&i4_width_right,(UINT32*)&i4_hight);
     MENU_LOG_ON_FAIL(i4_ret);

     c_memset(&t_inset_temp,0, sizeof(WGL_INSET_T));
     c_memcpy(&t_inset_temp,&t_inset_border, sizeof(WGL_INSET_T));

     t_inset_temp.i4_left = MENU_ITEM_V_WIDE - i4_width_left - 15 - i4_text_width - FRAME_LEFT_RIGHT_INTV;

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_GL_SET_INSET,
                           &t_inset_temp,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     /* Set Border Title */
     c_memset(&t_rect_temp, 0, sizeof(GL_RECT_T));
     c_memcpy(&t_rect_temp,&t_rect_border_title, sizeof(GL_RECT_T));

     t_rect_temp.i4_right = t_inset_temp.i4_left - 8;

     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

     c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
     t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
     t_title_info.t_font = t_fnt_info;
     t_title_info.t_rc_ref = t_rect_temp;
     t_title_info.ui1_align = WGL_AS_LEFT_CENTER;                // Dennis           // wording of list select item ex:on/off item
     i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                           &t_title_info,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
     i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_LB_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)0),
                       WGL_PACK(i4_width_left+15));
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(i4_text_width));
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_do_cmd(h_widget,
                      WGL_CMD_LB_SET_COL_WIDTH,
                      WGL_PACK((UINT8)2),
                      WGL_PACK(i4_width_right+15));
     MENU_LOG_ON_FAIL(i4_ret);

         return MENUR_OK;
}

static INT32 _ope_lst_set_hide_input_left_right()
{
    INT32 i4_ret = 0;
    UINT8 ui1_cnt_index = 0;

    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if (pt_this->i2_hlt_idx != OPE_LST_IDX_HIDE)
    {
        return MENUR_FAIL;
    }

    if (_ope_lst_get_hide_from_input_list(&ui1_cnt_index) == MENUR_OK)
    {
        ui1_cnt_index ^= 1;

        i4_ret = _ope_lst_set_hide_from_input_list((UINT8)ui1_cnt_index);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    _tts_play(MLM_MENU_KEY_HIDE_FROM_INPUT_LIST,ui1_cnt_index == 1 ? MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE : MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE,TRUE);

    i4_ret = _ope_lst_adjust_hide_input_rect(pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt, ui1_cnt_index);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ope_lst_set_full_uhd_color_left_right()
{
    INT32 i4_ret = 0;
    UINT8 ui1_cnt_index = 0;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if (pt_this->i2_hlt_idx != OPE_LST_IDX_FULL_COLOR)
    {
        return MENUR_FAIL;
    }
    i4_ret = _ope_lst_get_full_uhd_color(&ui1_cnt_index);
    MENU_CHK_FAIL( i4_ret);

    DBG_LOG_PRINT(("<UHD color> file: %s line: %d  %s get uhd color: %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_cnt_index));
    ui1_cnt_index ^= 1;
    DBG_LOG_PRINT(("<UHD color> file: %s line: %d  %s set full uhd color: %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_cnt_index));
    _tts_play(MLM_MENU_KEY_FULL_COLOR,ui1_cnt_index == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF,TRUE);
    i4_ret = _ope_lst_set_full_uhd_color((UINT8)ui1_cnt_index);
    MENU_CHK_FAIL( i4_ret);

    return i4_ret;
}

static INT32 _ope_lst_menu_nav_go()
{
    INT32 i4_ret;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    switch(pt_this->i2_hlt_idx)
    {
        case OPE_LST_IDX_HIDE:
        {
            /* hide first page */
            i4_ret = _ope_lst_page_main_page_hide();
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _ope_lst_hide_device_page_show();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case OPE_LST_IDX_FULL_COLOR:
        {
            /* hide first page */
            i4_ret = _ope_lst_page_main_page_hide();
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _ope_lst_full_color_page_show();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case OPE_LST_IDX_FULL_CHROMA:
        {
            /* hide first page */
            i4_ret = _ope_lst_page_main_page_hide();
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _ope_lst_full_chroma_page_show();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        default:
        {
            i4_ret = menu_nav_go(*pui4_page_id[pt_this->i2_hlt_idx], NULL);
            MENU_CHK_FAIL(i4_ret);
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _atoi_one_char
 *
 * Description: Convert a number string to a number.
 *
 * Inputs:  ps     null ('\0') terminated character string.
 *
 *
 * Outputs: -
 *
 * Returns: sum of the number string.
 *
 ----------------------------------------------------------------------------*/
static INT32 _atoi_one_char( const CHAR* ps )
{
    INT32  i4_total;

    i4_total = 0;

    if ( *ps >= '0' && *ps <= '9' )
    {
        /* accumulate digit */
        i4_total = (*ps - '0');
    }
    else /* not a digit char */
    {
        return (-1);
    }

    return i4_total;
}

extern VOID menu_input_repaint_hide_input_orig(VOID)
{
    menu_pm_repaint();
}

INT32 ope_lst_set_hide_from_input_list(ISL_REC_T* pt_isl_rec, UINT8 ui1_value)
{
    INT32       i4_ret = MENUR_OK;
    CHAR        c_hdmi_index;
    UINT8       ui1_hdmi_index = 0;
    UINT8       ui1_hide_value = 0;
    SIZE_T      z_size = 0;
    CHAR        s_src_name[32];
    c_uc_w2s_to_ps(a_isl_get_display_name(pt_isl_rec), s_src_name, sizeof(s_src_name));

    if(a_nav_ipts_is_comp_source(pt_isl_rec) == TRUE)
    {
            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui1_value == 1)
            {
                ui1_hide_value |= (UINT8)1 << 5;
            }
            else if(ui1_value == 0)
            {
                ui1_hide_value &= ~((UINT8)1 << 5);
            }
            DBG_LOG_PRINT(("<HIDE INPUT> file: %s line: %d  %s a_cfg_cust_set_hide_from_input_manually(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_hide_value ));

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
            MENU_LOG_ON_FAIL(i4_ret);

    }
    /*TV*/
    else if(a_nav_ipts_is_tv_source(pt_isl_rec) == TRUE)
    {
        i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
        if(ui1_value == 1)
        {
            ui1_hide_value |= (UINT8)1 << 6;
        }
        else if(ui1_value == 0)
        {
            ui1_hide_value &= ~((UINT8)1 << 6);
        }
        i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    /*Vtrl input*/
    else if(a_nav_ipts_is_cast_source(pt_isl_rec) == TRUE)
    {
        /* set hideable */
        i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);

        NAV_LOG_ON_FAIL(i4_ret);
        if(ui1_value == 1)
        {
            ui1_hide_value |= ((UINT8)1 << (pt_isl_rec->ui1_internal_id - 1 )) ;
        }
        else if(ui1_value == 0)
        {
            ui1_hide_value &= ~((UINT8)1 << (pt_isl_rec->ui1_internal_id - 1 ));
        }

        DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s set_hide vtrl(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_hide_value));

        i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);
        NAV_LOG_ON_FAIL(i4_ret);
    }
    /*should be HDMI-x*/
    else if(a_nav_ipts_is_hdmi_source(pt_isl_rec) == TRUE)
    {
        {
            if(c_strlen(s_src_name) > 5)
            {
                c_hdmi_index = s_src_name[5];
            }
            else
            {
                c_hdmi_index = '1';
            }
            ui1_hdmi_index = _atoi_one_char(&c_hdmi_index);

            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
                MENU_LOG_ON_FAIL(i4_ret);

                DBG_LOG_PRINT(("<HIDE INPUT> file: %s line: %d  %s a_cfg_cust_get_hide_from_input_manually(%d) ui1_hdmi_index: %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_hide_value, ui1_hdmi_index));

                if(ui1_value == 1)
                {
                    ui1_hide_value |= (UINT8)1 << (ui1_hdmi_index - 1);
                }
                else if(ui1_value == 0)
                {
                    ui1_hide_value &= ~((UINT8)1 << (ui1_hdmi_index - 1));
                }

                DBG_LOG_PRINT(("<HIDE INPUT> file: %s line: %d  %s a_cfg_cust_set_hide_from_input_manually(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_hide_value));

                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    else
    {
        /* unknow input source */
        MENU_CHK_FAIL(MENUR_INV_STATE);
    }


    if(0 == c_strcmp(s_src_name, "COMP"))
    {
        rest_event_notify("system/input/visible", 0,"comp");
    }
    if(0 == c_strcmp(s_src_name, "HDMI-1"));
    {
        rest_event_notify("system/input/visible", 0,"hdmi1");
    }
    if(0 == c_strcmp(s_src_name, "HDMI-2"))
    {
        rest_event_notify("system/input/visible", 0,"hdmi2");
    }
    if(0 == c_strcmp(s_src_name, "HDMI-3"))
    {
        rest_event_notify("system/input/visible", 0,"hdmi3");
    }
    if(0 == c_strcmp(s_src_name, "HDMI-4"))
    {
        rest_event_notify("system/input/visible", 0,"hdmi4");
    }
    if(0 == c_strcmp(s_src_name, "HDMI-5"))
    {
        rest_event_notify("system/input/visible", 0,"hdmi5");
    }
    if(0 == c_strcmp(s_src_name, "TV"))
    {
        rest_event_notify("system/input/visible", 0,"tuner");
    }

    return i4_ret;
}


static INT32 _ope_lst_set_hide_from_input_list(UINT8 ui1_value)
{
    INT32       i4_ret = MENUR_OK;
    ISL_REC_T   t_isl_rec;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info;
    /*get setting input source info */

    c_memset(&t_device_info, 0, sizeof(MENU_DEVICE_PAGE_DEVICE_INFO_T));

    i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
    MENU_LOG_ON_FAIL( i4_ret );

    i4_ret = a_isl_get_rec_by_idx(t_device_info.u_device_data.t_input.ui1_input_src_idx, &t_isl_rec);
    MENU_LOG_ON_FAIL( i4_ret == ISLR_OK ? MENUR_OK : i4_ret );

    i4_ret = ope_lst_set_hide_from_input_list(&t_isl_rec, ui1_value);

    return i4_ret;
}

static BOOL _ope_lst_get_tv_comp_input(VOID)
{
    INT32   i4_ret = MENUR_OK;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info;
    ISL_REC_T   t_isl_rec;
    c_memset(&t_device_info, 0, sizeof(MENU_DEVICE_PAGE_DEVICE_INFO_T));
    i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
    MENU_CHK_FAIL(i4_ret);

    a_isl_get_rec_by_idx(t_device_info.u_device_data.t_input.ui1_input_src_idx, &t_isl_rec);

    /*setting under COMP*/
    if(!c_uc_w2s_strcmp(t_device_info.u_device_data.t_input.pw2s_disp_name, L"COMP"))
    {
        DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
        return TRUE;
    }
    /*TV*/
    else if(!c_uc_w2s_strcmp(t_device_info.u_device_data.t_input.pw2s_disp_name, L"TV"))
    {
        DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
        return TRUE;
    }
    /*WatchFree*/
    else if(!c_uc_w2s_strcmp(t_device_info.u_device_data.t_input.pw2s_disp_name, L"WatchFree"))
    {
        DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
        return TRUE;
    }
    DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
    return FALSE;
}

UINT8 ope_lst_get_hide_from_input_list(ISL_REC_T* pt_isl_rec)
{
    UINT8       ui1_value = 0;
    INT32       i4_ret = MENUR_OK;
    CHAR        c_hdmi_index;
    UINT8       ui1_hdmi_index;
    UINT8       ui1_hide_value;
    SIZE_T      z_size = 0;
    CHAR        s_src_name[32];

    c_uc_w2s_to_ps(a_isl_get_display_name(pt_isl_rec), s_src_name, sizeof(s_src_name));

    i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
    MENU_CHK_FAIL(i4_ret);

    /*setting under COMP*/
    if(!c_strcmp(s_src_name, "COMP"))
    {
        ui1_value = (UINT8)((ui1_hide_value >> 5) & 0x01);
    }
    /*TV*/
    else if(!c_strcmp(s_src_name, "TV"))
    {
        ui1_value = (UINT8)((ui1_hide_value >> 6) & 0x01);
    }
    /*Vtrl input*/
    else if(INP_SRC_TYPE_VTRL == pt_isl_rec->e_src_type &&
            DEV_VTRL_CAST == pt_isl_rec->t_avc_info.e_video_type &&
            pt_isl_rec->ui1_internal_id > 0)
    {
        i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);
        ui1_value = (UINT8)((ui1_hide_value >> (pt_isl_rec->ui1_internal_id - 1)) & 0x01);
    }
    /* HDMI-x */
    else if (pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        if(c_strlen(s_src_name) > 5)
        {
            /*more than one HDMI port*/
            c_hdmi_index = s_src_name[5];
        }
        else
        {
            /*only one HDMI port*/
            c_hdmi_index = '1';
        }
        ui1_hdmi_index = _atoi_one_char(&c_hdmi_index);

        ui1_value = (UINT8)((ui1_hide_value >> (ui1_hdmi_index - 1)) & 0x01);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        MENU_CHK_FAIL(MENUR_INV_STATE);
    }

    return ui1_value;
}

static INT32 _ope_lst_get_hide_from_input_list(UINT8* ui1_value)
{
    INT32   i4_ret = MENUR_OK;
    UINT8   ui1_hide_value;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info;
    ISL_REC_T   t_isl_rec;
    c_memset(&t_device_info, 0, sizeof(MENU_DEVICE_PAGE_DEVICE_INFO_T));

    i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
    MENU_CHK_FAIL(i4_ret);

    a_isl_get_rec_by_idx(t_device_info.u_device_data.t_input.ui1_input_src_idx, &t_isl_rec);

    *ui1_value = ope_lst_get_hide_from_input_list(&t_isl_rec);

    return MENUR_OK;
}

static UINT32 u4_g_full_color_hlt_hdmi_idx;
static UINT32 i4_tts_id = -1;

static VOID _set_full_color_tts_notify(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag)
{
    if(ui4_tts_play_id == i4_tts_id &&
       e_tts_str_state == TTS_STR_ST_PLAYED )
    {
        DBG_LOG_PRINT(("[%s %d]############# TTS_STR_ST_PLAYED,ui1_hdmi_index = %d,ui_hdmi_format = %d\n",__FUNCTION__,__LINE__,u4_g_full_color_hlt_hdmi_idx,ui_hdmi_format));
        i4_tts_id = -1;

        ACFG_DEBUG_HDMI_EDID(
            DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} call inp_lst_set_edid_by_port(HdmiIdx:%d, Val:%d)\n",
                __FUNCTION__, __LINE__,u4_g_full_color_hlt_hdmi_idx, ui_hdmi_format ));
        );
        MENU_LOG_ON_FAIL(inp_lst_set_edid_by_port(u4_g_full_color_hlt_hdmi_idx,ui_hdmi_format,FALSE));

        a_app_tts_nfy_unreg(_set_full_color_tts_notify);
        /* ps : if tts play slowly show delay longer that other status*/
        MENU_LOG_ON_FAIL(c_timer_start(t_this_page.h_full_clor_timer,
                               3000,
                               X_TIMER_FLAG_ONCE,
                               _full_clor_timer_nfy,
                               NULL));
    }

    if(e_tts_str_state == TTS_STR_ST_PLAYING )
    {
        DBG_LOG_PRINT(("[%s %d]############# TTS_STR_ST_PLAYING ui4_tts_play_id = %d\n",__FUNCTION__,__LINE__,ui4_tts_play_id));
        i4_tts_id = ui4_tts_play_id;
    }
}

/*
AP auto = 2, 2.1 = 1, 1.4 = 0
Driver auto = 1, 2.1 = 3, 1.4 = 2
*/
INT32 inp_lst_set_edid_by_port(UINT16 ui2_hdmi_idx, UINT8 ui1_value,BOOL b_hdmi_mode)
{
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][HDMI][EDID]{%s,%d} ui2_hdmi_idx:%d, ui1_value:%d(%s)\n",
            __FUNCTION__, __LINE__, ui2_hdmi_idx,
            ui1_value, acfg_cust_get_acfg_edid_name((EnuAcfgEdidIdx)ui1_value) ));
    );

    if (ui1_value >= sizeof(driver_edid_table) / sizeof(UINT8))
        return MENUR_INV_ARG;

    UINT8 u8_glue_idx = driver_edid_table[ui1_value];

 #if 0
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][HDMI][EDID]{%s,%d} acfg_idx:%d(%s) <==> glue_Idx:%d(%s))\n",
            __FUNCTION__,__LINE__,
                    ui1_value, acfg_cust_get_acfg_edid_name((EnuAcfgEdidIdx)ui1_value),
                    u8_glue_idx, acfg_cust_get_glue_edid_name((EnuGlueEdidIdx)u8_glue_idx) ));
    );
 #endif

    //DBG_LOG_PRINT(("%s %d ui1_value = %d, driver_edid_table[ui1_value] = %d\n",__FUNCTION__,__LINE__, ui1_value, driver_edid_table[ui1_value]));
    DBG_LOG_PRINT(("[MENU][HDMI][EDID]{%s,%d} Call driver MTVDECEX_HDMI_SetEdidIndexByPort(hdmiIdx:%d, acfg_idx:%d(%s), glue_Idx:%d(%s))\n",
        __FUNCTION__,__LINE__, ui2_hdmi_idx,
            ui1_value, acfg_cust_get_acfg_edid_name((EnuAcfgEdidIdx)ui1_value),
            u8_glue_idx, acfg_cust_get_glue_edid_name((EnuGlueEdidIdx)u8_glue_idx) ));

    return MTVDECEX_HDMI_SetEdidIndexByPort(ui2_hdmi_idx, u8_glue_idx,b_hdmi_mode);
}

INT32 inp_lst_set_full_uhd_color_by_hdmi_idx(UINT16 ui2_hdmi_idx, UINT8 ui1_value)
{
    UINT8   ui1_color_value = 0;
    INT32   i4_ret = MENUR_OK;

    ACFG_DEBUG_HDMI_EDID( DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} ui2_hdmi_idx:%d, ui1_value:%d\n",
        __FUNCTION__, __LINE__, ui2_hdmi_idx, ui1_value )); );

    //1, set ui1_color_value to acfg
    i4_ret = a_cfg_cust_get_full_uhd_color(&ui1_color_value);
    //DBG_LOG_PRINT(("<UHD COLOR> file: %s line: %d  %s a_cfg_cust_get_full_uhd_color(%d) ui1_hdmi_index: %d ui1_value:%d\n", __FILE__, __LINE__, __FUNCTION__, ui1_color_value, ui2_hdmi_idx, ui1_value));
    ACFG_DEBUG_HDMI_EDID( DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} a_cfg_cust_get_full_uhd_color() => ui1_color_value:0x%X \n",
            __FUNCTION__, __LINE__, ui1_color_value)); );
    MENU_CHK_FAIL(i4_ret);

    if (ui1_value >= 3)
        ui1_value = 2;

    ui1_color_value &= ~((UINT8)3 << (ui2_hdmi_idx * 2));
    ui1_color_value |= (UINT8)ui1_value << (ui2_hdmi_idx * 2);

    //DBG_LOG_PRINT(("<UHD COLOR> file: %s line: %d  %s a_cfg_cust_set_full_uhd_color(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_color_value));
    ACFG_DEBUG_HDMI_EDID( DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID] {%s,%d} a_cfg_cust_set_full_uhd_color(0x%X)\n",
            __FUNCTION__, __LINE__, ui1_color_value)); );
    i4_ret = a_cfg_cust_set_full_uhd_color(ui1_color_value);
    MENU_CHK_FAIL(i4_ret);

    //2, set edid to the hdmi index
    {
        WDK_TOAST_T    t_toast          = {0};
        UTF16_T        w2s_tmp_str[512] = {0};
        UTF16_T        *pw2s_text       = NULL;
        INT32          i4_ret;

        pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_HDMI_MODE_SET);

        UINT8  i1_switch = 0;
        a_cfg_get_tts_switch_status(&i1_switch);
        if(1 == i1_switch && MLM_MENU_LANG_ENG == ui2_g_menu_curr_lang)
        {
            u4_g_full_color_hlt_hdmi_idx = ui2_hdmi_idx;
            ui_hdmi_format = ui1_value;
            i4_ret = a_app_tts_nfy_reg(_set_full_color_tts_notify,NULL);
            DBG_LOG_PRINT(("[%s %d]############# tts _set_full_color_tts_notify ret = %d hdmi idx = %d\n",__FUNCTION__,__LINE__,i4_ret,u4_g_full_color_hlt_hdmi_idx));
        }
        c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);
        c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
        t_toast.e_toast_style  = WDK_WARNING_TOAST;
        t_toast.e_string_style = WDK_STRING_STRING;
        t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
        _full_uhd_clo_info_send_string_to_nav(&t_toast);
        if(1 != i1_switch || MLM_MENU_LANG_ENG != ui2_g_menu_curr_lang)
        {
            ACFG_DEBUG_HDMI_EDID(
                DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} call inp_lst_set_edid_by_port(HdmiIdx:%d, Val:%d)\n",
                    __FUNCTION__, __LINE__,ui2_hdmi_idx, ui1_value ));
            );

            i4_ret = inp_lst_set_edid_by_port(ui2_hdmi_idx, ui1_value,TRUE);
            MENU_LOG_ON_FAIL(i4_ret == 0 ? MENUR_OK : i4_ret);
            a_app_tts_nfy_unreg(_set_full_color_tts_notify);
            /* ps : if tts play slowly show delay longer that other status*/
            i4_ret = c_timer_start(t_this_page.h_full_clor_timer,
                                   3000,
                                   X_TIMER_FLAG_ONCE,
                                   _full_clor_timer_nfy,
                                   NULL);
            DBG_LOG_PRINT(("[%s %d]############# tts _set_full_color_tts_notify ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
        }
    }
    return MENUR_OK;
}

static INT32 _ope_lst_set_full_uhd_color(UINT8 ui1_value)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_hdmi_index;
    CHAR    c_hdmi_index;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info;

    //1, get hdmi index
    c_memset(&t_device_info, 0, sizeof(MENU_DEVICE_PAGE_DEVICE_INFO_T));

    i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
    MENU_CHK_FAIL(i4_ret);

    /*should be HDMI-x*/
    if(c_uc_w2s_strlen(t_device_info.u_device_data.t_input.pw2s_disp_name) > 5)
    {
        w2s_hdmi_index = c_uc_w2s_get(t_device_info.u_device_data.t_input.pw2s_disp_name, 5);
    }
    else
    {
        w2s_hdmi_index = L'1';
    }
    c_uc_w2s_to_ps(&w2s_hdmi_index, &c_hdmi_index, sizeof(CHAR));
    u4_g_full_color_hlt_hdmi_idx = _atoi_one_char(&c_hdmi_index);

    i4_ret = inp_lst_set_full_uhd_color_by_hdmi_idx(u4_g_full_color_hlt_hdmi_idx - 1, ui1_value);

    return MENUR_OK;
}
static VOID _full_clor_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
      nav_request_context_switch( _full_uhd_clo_info_send_string_to_nav_fct, pv_tag, NULL, NULL);
}
static VOID _full_uhd_clo_info_send_string_to_nav_fct(VOID*        pv_tag1,
                                                            VOID*        pv_tag2,
                                                            VOID*        pv_tag3)
{
    INT32          i4_ret           = MENUR_OK;
    UTF16_T        *pw2s_text       = NULL;
    WDK_TOAST_T    t_toast          = {0};
    UTF16_T        w2s_tmp_str[512] = {0};
    UINT8          ui1_value        = 0;

    i4_ret = _ope_lst_get_full_uhd_color(&ui1_value);  //Auto: 2    2.1: 1    1.4: 0
    MENU_LOG_ON_FAIL(i4_ret);

    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_HDMI_MODE_SET_OK_1_4 + ui1_value);

    c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);
    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_WARNING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
    i4_ret = _full_uhd_clo_info_send_string_to_nav(&t_toast);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_list_set_idx(t_this_page.t_ope_lst[OPE_LST_IDX_FULL_COLOR].h_wgt, (UINT16) ui_hdmi_format);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_pm_repaint();
    return;
}

static INT32 _full_uhd_clo_info_send_string_to_nav(WDK_TOAST_T *pt_toast)
{
    return menu_send_string_to_nav_toast(pt_toast);
}

static INT32 _ope_lst_get_full_chroma(UINT8* ui1_value)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_hdmi_index;
    CHAR    c_hdmi_index;
    UINT8   ui1_hdmi_index;
    UINT8   ui1_chroma_value;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info;

    c_memset(&t_device_info, 0, sizeof(MENU_DEVICE_PAGE_DEVICE_INFO_T));

    i4_ret = a_cfg_cust_get_full_color_444(&ui1_chroma_value);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("<FULL CHROMA> file: %s line: %d  %s a_cfg_cust_get_full_chroma_444(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_chroma_value));

    i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
    if(i4_ret != MENUR_OK)
    {
        MENU_LOG_ON_FAIL(i4_ret);
        return i4_ret;
    }

    /*should be HDMI-x*/
    if(c_uc_w2s_strlen(t_device_info.u_device_data.t_input.pw2s_disp_name) > 5)
    {
        /*more than one HDMI port*/
        w2s_hdmi_index = c_uc_w2s_get(t_device_info.u_device_data.t_input.pw2s_disp_name, 5);
    }
    else
    {
        /*only one HDMI port*/
        w2s_hdmi_index = L'1';
    }
    c_uc_w2s_to_ps(&w2s_hdmi_index, &c_hdmi_index, sizeof(CHAR));
    ui1_hdmi_index = _atoi_one_char(&c_hdmi_index);

    *ui1_value = (UINT8)((ui1_chroma_value >> (ui1_hdmi_index - 1)) & 0x01);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("<FULL CHROMA> file: %s line: %d  %s ui1_hdmi_index(%d) return(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_hdmi_index,*ui1_value));
    return MENUR_OK;
}

UINT32  a_ope_lst_get_full_chroma(UINT8* ui1_value)
{

    INT32           i4_ret = 0;
    ISL_REC_T       t_isl_rec;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8           ui1_input_id = 0;
    UINT8           ui1_chroma_value;

    c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
     MENU_LOG_ON_FAIL(i4_ret);

     if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type && DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
     {
         i4_ret = a_cfg_cust_get_full_color_444(&ui1_chroma_value);
         MENU_LOG_ON_FAIL(i4_ret);
         DBG_LOG_PRINT(("<FULL CHROMA> %s a_cfg_cust_get_full_chroma_444(%d),t_isl_rec.ui1_internal_id :%d\n", __FUNCTION__, ui1_chroma_value,t_isl_rec.ui1_internal_id));

        *ui1_value = (UINT8)((ui1_chroma_value >> (t_isl_rec.ui1_internal_id)) & 0x01);
         MENU_LOG_ON_FAIL(i4_ret);
     }
     return MENUR_OK;
}

INT32 inp_lst_get_full_uhd_color_by_hdmi_idx(UINT16 ui2_idx, UINT8* pui1_value)
{
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} hdmi_idx:%d \n",
            __FUNCTION__, __LINE__, ui2_idx ));
    );

#if 1
    INT32 i32_rtn = a_cfg_cust_get_full_uhd_color_by_hdmi_idx(ui2_idx, pui1_value);
    if( i32_rtn != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} u8_hdmi_idx:%d: a_cfg_cust_get_full_uhd_color_by_hdmi_idx() failed!! i32_rtn:%d\n",
            __FUNCTION__, __LINE__, ui2_idx, i32_rtn ));

        *pui1_value = 0;
        return MENUR_FAIL;
    }

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} hdmi_idx:%d, => acfg_val:%d(%s)\n",
            __FUNCTION__, __LINE__, ui2_idx, *pui1_value, acfg_cust_get_acfg_edid_name((EnuAcfgEdidIdx)*pui1_value) ));
    );

#else

    INT32   i4_ret = MENUR_OK;
    UINT8   ui1_color_value_acfg;
    UINT8   ui1_mask = 3;


    i4_ret = a_cfg_cust_get_full_uhd_color(&ui1_color_value_acfg);
    MENU_LOG_ON_FAIL(i4_ret);
    //DBG_LOG_PRINT(("<UHD COLOR> file: %s line: %d  %s a_cfg_cust_get_full_uhd_color(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_color_value));

    *pui1_value = (UINT8)((ui1_color_value_acfg >> (ui2_idx * 2)) & ui1_mask);
    MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} hdmi_idx:%d, ui1_color_value_acfg:0x%X => inp_lst val:%d \n",
            __FUNCTION__, __LINE__, ui2_idx, ui1_color_value_acfg, *pui1_value ));
    );

#endif


    //DBG_LOG_PRINT(("<UHD COLOR> file: %s line: %d  %s return(%d)\n", __FILE__, __LINE__, __FUNCTION__, *pui1_value));
    return MENUR_OK;
}

static INT32 _ope_lst_get_full_uhd_color(UINT8* ui1_value)
{
    UINT8 ui1_acfg_hdmi_index;
    UINT8 ui1_ui_hdmi_index;

    ui1_ui_hdmi_index = acfg_cust_get_CurSrcHdmi_UI_Idx();
    ui1_acfg_hdmi_index = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(ui1_ui_hdmi_index);
    DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} UI hdmi idx:%d => ACFG hdmi_idx:%d\n",
            __FUNCTION__, __LINE__, ui1_ui_hdmi_index, ui1_acfg_hdmi_index));

    inp_lst_get_full_uhd_color_by_hdmi_idx(ui1_acfg_hdmi_index, ui1_value);

    return MENUR_OK;
}
static INT32 _ope_lst_general_fct(HANDLE_T h_widget,
                                UINT32 ui4_msg,
                                VOID* pv_param1,
                                VOID* pv_param2
                                )
{
    INT32 i4_ret;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        UINT8     ui1_value = 0;
        UINT16    fir_mlm_key;
        UINT16    sec_mlm_key;
        BOOL      b_sec_exist = FALSE;
        DBG_LOG_PRINT(("<UHD COLOR>  line: %d  %s value\n",__LINE__, __FUNCTION__, (UINT16)ui1_value));
        if(h_widget == pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].h_wgt)
        {
            if (_ope_lst_get_full_chroma(&ui1_value) == APP_CFGR_OK)
            {
                MENU_LOG_ON_FAIL( menu_list_set_idx(pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].h_wgt, (UINT16)ui1_value));
                fir_mlm_key = MLM_MENU_KEY_FULL_CHROMA;
                sec_mlm_key = ui1_value == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF;
                b_sec_exist = TRUE;
            }
        }
        else if(h_widget == pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].h_wgt)
        {
            if (_ope_lst_get_full_uhd_color(&ui1_value) == MENUR_OK)
            {
                MENU_LOG_ON_FAIL( menu_list_set_idx(pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].h_wgt, (UINT16)ui1_value));
                fir_mlm_key = MLM_MENU_KEY_FULL_COLOR;
                sec_mlm_key = ui1_value == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF;
                b_sec_exist = TRUE;
            }
        }
        else if(h_widget == pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt)
        {
            if (_ope_lst_get_hide_from_input_list(&ui1_value) == MENUR_OK)
            {
                MENU_LOG_ON_FAIL(menu_list_set_idx(pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt, (UINT16)ui1_value));
                fir_mlm_key = MLM_MENU_KEY_HIDE_FROM_INPUT_LIST;
                sec_mlm_key = ui1_value == 1 ? MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE : MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE;
                b_sec_exist = TRUE;
            }

            menu_list_adjust_rect(pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt);
        }
        else
        {
            UINT8 i2_idx;
            for(i2_idx = 0;i2_idx < OPE_LST_INIT_LEN;i2_idx++)
            {
                if(h_widget == pt_this->t_ope_lst[i2_idx].h_wgt)
                {
                    fir_mlm_key = ui2_ope_lst_elem_name[i2_idx];
                }
            }
        }
        if((pt_this->i2_hlt_idx == OPE_LST_IDX_HIDE)&&
          _ope_lst_get_tv_comp_input())
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_HIDE_TV_COMP_INPUT));
        }
        else
        {
            menu_set_and_show_help_tip(MENU_TEXT(ui2_help_tip_key[pt_this->i2_hlt_idx]));
        }
        menu_pm_repaint();
    _tts_play(fir_mlm_key,sec_mlm_key,b_sec_exist);
    }
    else if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch ((UINT32)pv_param1)
        {
            case BTN_RETURN:
                {
                    i4_ret = menu_device_page_nav_go_no_wifi_remote(NAV_DEVICE_SETTING_PAGE_FROM_INPUT_OPE_LST_PAGE, NULL);
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_SELECT:
                {
                    i4_ret = _ope_lst_menu_nav_go();
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
                {
                    if(h_widget == pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].h_wgt)
                    {
                        i4_ret = _ope_lst_set_full_chroma();

                        MENU_CHK_FAIL(i4_ret);
                    }
                    else if(h_widget == pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].h_wgt)
                    {
                        i4_ret = _ope_lst_set_full_uhd_color_left_right();
                        MENU_CHK_FAIL(i4_ret);
                    }
                    else if(h_widget == pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt)
                    {
                        i4_ret = _ope_lst_set_hide_input_left_right();
                        MENU_CHK_FAIL(i4_ret);
                    }
                }
                break;
            case BTN_CURSOR_UP:
                {
                    i4_ret = _ope_lst_set_focus_prev(TRUE);
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_CURSOR_DOWN:
                {
                    i4_ret = _ope_lst_set_focus_next(TRUE);
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            default:
                break;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);;
}

static INT32 _ope_lst_chg_lang(VOID)
{
    INT32 i4_ret;
    HANDLE_T h_wgt;
    UINT16 ui2_i;
    UINT8 ui1_value = 0;
    UINT16 ui2_elem_num = 0;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    /* main page */
    {
        for (ui2_i = 0; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
        {
           h_wgt = pt_this->t_ope_lst[ui2_i].h_wgt;

           i4_ret = menu_list_chg_lang(h_wgt,
                                       ui2_ope_lst_elem_name[ui2_i],
                                       MLM_MENU_KEY_ON,
                                       MLM_MENU_KEY_OFF);
           MENU_CHK_FAIL(i4_ret);

           i4_ret = menu_list_adjust_rect(h_wgt);
           MENU_CHK_FAIL(i4_ret);
        }

        {
            h_wgt = pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].h_wgt;
            i4_ret = menu_list_chg_lang(h_wgt,
                               ui2_ope_lst_elem_name[OPE_LST_IDX_FULL_CHROMA],
                               MLM_MENU_KEY_OFF,
                               MLM_MENU_KEY_ON);
            MENU_CHK_FAIL(i4_ret);

            if (_ope_lst_get_full_chroma(&ui1_value) == APP_CFGR_OK)
            {
                i4_ret = menu_list_set_idx(h_wgt, (UINT16)ui1_value);
                MENU_CHK_FAIL(i4_ret);
            }
        }

        {
            h_wgt = pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].h_wgt;
            i4_ret = menu_list_chg_lang(h_wgt,
                              ui2_ope_lst_elem_name[OPE_LST_IDX_FULL_COLOR],
                              MLM_MENU_KEY_MENU_COMMON_OFF,
                              MLM_MENU_KEY_MENU_COMMON_ON);
            MENU_CHK_FAIL(i4_ret);

            if (_ope_lst_get_full_uhd_color(&ui1_value) == APP_CFGR_OK)
            {
               i4_ret = menu_list_set_idx(h_wgt, (UINT16)ui1_value);
               MENU_CHK_FAIL(i4_ret);
            }
        }

        {
            h_wgt = pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt;
            i4_ret = menu_list_chg_lang(h_wgt,
                               ui2_ope_lst_elem_name[OPE_LST_IDX_HIDE],
                               MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE,
                               MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE);
            MENU_CHK_FAIL(i4_ret);

            menu_list_adjust_rect(h_wgt);
            MENU_CHK_FAIL(i4_ret);
        }
    }
    /* chroma */
    {
        ui2_elem_num = MLM_MENU_KEY_ON-MLM_MENU_KEY_OFF+1;
        i4_ret = c_wgl_do_cmd(pt_this->h_full_chroma_lb2,
                            WGL_CMD_LB_SET_ELEM_NUM,
                            WGL_PACK(ui2_elem_num),
                            NULL);
        MENU_CHK_FAIL(i4_ret);

        for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
        {
            i4_ret = c_wgl_do_cmd(pt_this->h_full_chroma_lb2,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (ui2_i, 0),
                            WGL_PACK(MENU_TEXT(MLM_MENU_KEY_OFF + ui2_i)));
            MENU_CHK_FAIL(i4_ret);
        }
    }
    /* color */
    {
        ui2_elem_num = MLM_MENU_KEY_MENU_COMMON_ON - MLM_MENU_KEY_MENU_COMMON_OFF + 1;
        i4_ret = c_wgl_do_cmd(pt_this->h_full_color_lb2,
                            WGL_CMD_LB_SET_ELEM_NUM,
                            WGL_PACK(ui2_elem_num),
                            NULL);
        MENU_CHK_FAIL(i4_ret);

        for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
        {
            i4_ret = c_wgl_do_cmd(pt_this->h_full_color_lb2,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (ui2_i, 0),
                            WGL_PACK(MENU_TEXT(MLM_MENU_KEY_MENU_COMMON_OFF + ui2_i)));
            MENU_CHK_FAIL(i4_ret);
        }
    }

    /* hiden device */
    {
        ui2_elem_num = MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE -  MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE + 1;
        i4_ret = c_wgl_do_cmd(pt_this->h_hide_device_lb2,
                            WGL_CMD_LB_SET_ELEM_NUM,
                            WGL_PACK(ui2_elem_num),
                            NULL);
        MENU_CHK_FAIL(i4_ret);

        for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
        {
            i4_ret = c_wgl_do_cmd(pt_this->h_hide_device_lb2,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (ui2_i, 0),
                            WGL_PACK(MENU_TEXT(MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE + ui2_i)));
            MENU_CHK_FAIL(i4_ret);
        }
    }

    return MENUR_OK;
}

static INT32 _ope_lst_update_title(VOID)
{
    INT32                               i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    UINT32                              ui4_rest_len = 0;
    UTF16_T                             w2s_input_title[OPE_LST_VIEW_MAX_TITLE_NAME_LEN] = {0};

    /* input setting - XXX */
    c_uc_w2s_strcpy(w2s_input_title, MENU_TEXT(MLM_MENU_KEY_DEVICES));
    c_uc_w2s_strcat(w2s_input_title, L" - ");
    ui4_rest_len = OPE_LST_VIEW_MAX_TITLE_NAME_LEN - c_uc_w2s_strlen(w2s_input_title);
    c_uc_w2s_strncat(w2s_input_title,pt_this->w2s_input, ui4_rest_len);

    /* set title */
    i4_ret = menu_main_set_title_text(w2s_input_title);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_lb_degenerate(HANDLE_T h_widget)
{
    INT32  i4_ret;
    WGL_LB_ITEM_T  at_items[3];
    WGL_LB_ITEM_IMG_SUIT_T  t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T  t_img_suit_right;

    i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Hide left/right arrow */
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_left.h_highlight          = NULL_HANDLE;
    t_img_suit_left.h_selected_highlight = NULL_HANDLE;

    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_right.h_highlight          = NULL_HANDLE;
    t_img_suit_right.h_selected_highlight = NULL_HANDLE;

    at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_items[0].data.pt_img_suit = &t_img_suit_left;

    at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text   = MENU_TEXT(MLM_MENU_KEY_EMPTY);

    at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_items[2].data.pt_img_suit = &t_img_suit_right;

    i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

INT32 menu_ope_lst_get_hdmi_color_space(INT32 *pi4_color_space)
{

   return _ope_lst_get_hdmi_color_space((MENU_HDMI_IF_CLR_SPC *) pi4_color_space);
}

INT32 menu_ope_lst_get_hdmi2_0_is_support(UINT8 ui1_hdmi_port,BOOL *pb_support)
{

   return _ope_lst_get_hdmi2_0_is_support(ui1_hdmi_port,pb_support);
}

BOOL menu_ope_lst_hdmi_color_space_is_RGB(MENU_HDMI_IF_CLR_SPC e_color_space)
{
    return e_color_space == MENU_HDMI_IF_CLRSPC_RGB;
}


BOOL menu_ope_lst_hdmi_color_space_is_444(MENU_HDMI_IF_CLR_SPC e_color_space)
{
    return e_color_space == MENU_HDMI_IF_CLRSPC_YUV444;
}

BOOL menu_ope_lst_hdmi_color_space_is_422(MENU_HDMI_IF_CLR_SPC e_color_space)
{
    return e_color_space == MENU_HDMI_IF_CLRSPC_YUV422;
}

BOOL menu_ope_lst_hdmi_color_space_is_420(MENU_HDMI_IF_CLR_SPC e_color_space)
{
    return e_color_space == MENU_HDMI_IF_CLRSPC_YUV420;
}


static INT32 _ope_lst_get_hdmi_color_space(MENU_HDMI_IF_CLR_SPC *pe_color_space)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info  = {0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size     = sizeof(pe_color_space);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_GET_HDMI_COLORSPACE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pe_color_space;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           &z_size_drv
                           );
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_get_hdmi2_0_is_support(UINT8 ui1_hdmi_port,BOOL *pb_support)
{
#if 0
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info  = {0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size     = sizeof(&ui1_hdmi_port);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_GET_HDMI_IS_SUPPORT_6G;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_hdmi_port;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           &z_size_drv
                           );
    MENU_CHK_FAIL(i4_ret);

    *pb_support = (BOOL) ui1_hdmi_port;
#endif
    *pb_support = true;
    return MENUR_OK;
}

static BOOL _ope_lst_pic_mode_is_computer_mode(VOID)
{
    UINT16  ui2_pic_mode_id;
    INT16 i2_vid_pic_mode = 0;

    ui2_pic_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);

    a_cfg_av_get(ui2_pic_mode_id, &i2_vid_pic_mode);
    if (i2_vid_pic_mode != PIC_MODE_COMPUTER)
    {
        return FALSE;
    }
    return TRUE;
}

static INT32 _ope_lst_video_fmt_update(VOID)
{
    INT32      i4_ret = MENUR_OK;
    BOOL       b_set = FALSE;
    INT32      i4_color_space;
    ISL_REC_T  t_isl_rec;
    UINT8      ui1_value = 0;

    i4_ret = a_ope_lst_get_full_chroma(&ui1_value);
    MENU_CHK_FAIL(i4_ret);

    DBG_LOG_PRINT(("-----------------%s %d a_ope_lst_get_full_chroma= %d\n",__FUNCTION__,__LINE__, ui1_value));

    i4_ret = menu_ope_lst_get_hdmi_color_space(&i4_color_space);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("-----------------%s %d menu_ope_lst_get_hdmi_color_space= %d\n",__FUNCTION__,__LINE__, i4_color_space));

    /* get current input source */
    {
        TV_WIN_ID_T  e_focus_id;

        i4_ret = a_tv_get_focus_win(&e_focus_id);
        NAV_CHK_FAIL(i4_ret);

        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
        NAV_CHK_FAIL(i4_ret);
    }

    if( menu_ope_lst_hdmi_color_space_is_444(i4_color_space) == TRUE  && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI )
    {
        if( ui1_value == 1 || _ope_lst_pic_mode_is_computer_mode() == TRUE )
        {
            b_set = TRUE;
        }
    }

    if (_check_is_dobly_vision() == TRUE)
    {
        b_set = FALSE;
    }

    i4_ret = _ope_lst_set_graphic_hdmi_mode(b_set);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _full_chroma_lb2_proc_fct(HANDLE_T            h_widget,
                                           UINT32              ui4_msg,
                                           VOID*               pv_param1,
                                           VOID*               pv_param2)
{
    INT32 i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        _ope_lst_move_help_tip(2);

        MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_chroma_lb2,
                                   WGL_CMD_LB_HLT_ELEM,
                                   WGL_PACK(pt_this->i2_hlt_idx),
                                   NULL));
        menu_set_and_show_help_tip(MENU_TEXT(ui2_help_tip_key[OPE_LST_IDX_FULL_CHROMA]));

        menu_pm_repaint();
        DBG_LOG_PRINT(("[MENU][%s %d]current hlt = %d\n",__FUNCTION__,__LINE__,pt_this->i2_hlt_idx));
        _tts_play(pt_this->i2_hlt_idx == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF,0,FALSE);
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_chroma_lb2,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&pt_this->i2_hlt_idx),
                                  NULL));
        DBG_LOG_PRINT(("[MENU][%s %d]current hlt = %d\n",__FUNCTION__,__LINE__,pt_this->i2_hlt_idx));
        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
           {
                MENU_CHK_FAIL( a_cfg_cust_set_full_chroma_by_source((UINT8)pt_this->i2_hlt_idx));
                MENU_CHK_FAIL( _ope_lst_video_fmt_update());
                pt_this->i2_hlt_idx = OPE_LST_IDX_FULL_CHROMA;
                MENU_CHK_FAIL( _ope_lst_full_chroma_page_hide());
                MENU_CHK_FAIL( _ope_lst_main_page_show());
            }
                break;
            case BTN_RETURN:
            {
                pt_this->i2_hlt_idx = OPE_LST_IDX_FULL_CHROMA;
                MENU_CHK_FAIL(_ope_lst_full_chroma_page_hide());
                MENU_CHK_FAIL( _ope_lst_main_page_show());
            }
                break;
            case BTN_CURSOR_UP:
            {
                if (pt_this->i2_hlt_idx == 0)
                {
                   MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_chroma_lb2,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(pt_this->i2_hlt_idx),
                                              NULL));
                   MENU_CHK_FAIL(menu_set_focus_on_backbar(TRUE));
                   MENU_CHK_FAIL(menu_pm_repaint());
                   return MENUR_OK;
                }
            }
                 break;
            case BTN_CURSOR_DOWN:
            {
                if((++ pt_this->i2_hlt_idx) > 1)
                    pt_this->i2_hlt_idx = 1;

                MENU_CHK_FAIL(menu_pm_repaint());
             }
                break;
            default:
                break;
        }
    }
    else if (WGL_MSG_KEY_UP==ui4_msg && ((UINT32)pv_param1 == BTN_CURSOR_UP || (UINT32)pv_param1 == BTN_CURSOR_DOWN))
    {
            UINT16   ui2_crnt_ht;

            i4_ret = c_wgl_do_cmd(pt_this->h_full_chroma_lb2,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_crnt_ht),
                                  NULL);
            MENU_CHK_FAIL(i4_ret);
            DBG_LOG_PRINT(("[MENU][%s %d]current hlt = %d\n",__FUNCTION__,__LINE__,ui2_crnt_ht));
            _tts_play(ui2_crnt_ht == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF,0,FALSE);
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);

}

static INT32 _full_color_lb2_proc_fct(HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_color_lb2,
                                   WGL_CMD_LB_HLT_ELEM,
                                   WGL_PACK(pt_this->i2_hlt_idx),
                                   NULL));
        _ope_lst_move_help_tip(2);

        menu_set_and_show_help_tip(MENU_TEXT(ui2_help_tip_key[OPE_LST_IDX_FULL_COLOR]));
        DBG_LOG_PRINT(("[MENU][%s %d]current hlt = %d\n",__FUNCTION__,__LINE__,pt_this->i2_hlt_idx));

        _tts_play(pt_this->i2_hlt_idx == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF ,0,FALSE);
        menu_pm_repaint();
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_color_lb2,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&pt_this->i2_hlt_idx),
                                  NULL));
        DBG_LOG_PRINT(("[MENU][%s %d]current hlt = %d\n",__FUNCTION__,__LINE__,pt_this->i2_hlt_idx));
        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
            {
                UINT8 u1_select_item = pt_this->i2_hlt_idx;
                t_this_page.i2_hlt_idx = OPE_LST_IDX_FULL_COLOR;
                MENU_CHK_FAIL(_ope_lst_full_color_page_hide());
                MENU_CHK_FAIL(_ope_lst_main_page_show());
                MENU_CHK_FAIL(_ope_lst_set_full_uhd_color(u1_select_item));
            }
                break;
            case BTN_RETURN:
                {
                    pt_this->i2_hlt_idx = OPE_LST_IDX_FULL_COLOR;
                    MENU_CHK_FAIL( _ope_lst_full_color_page_hide());
                    MENU_CHK_FAIL( _ope_lst_main_page_show());
                }
                break;
            case BTN_CURSOR_UP:
            {
                 if (pt_this->i2_hlt_idx == 0)
                 {
                      MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_color_lb2,
                                                 WGL_CMD_LB_UNHLT_ELEM,
                                                 WGL_PACK(pt_this->i2_hlt_idx),
                                                 NULL));
                      MENU_CHK_FAIL(menu_set_focus_on_backbar(TRUE));
                      MENU_CHK_FAIL(menu_pm_repaint());
                      return MENUR_OK;
                 }
            }
                     break;
            case BTN_CURSOR_DOWN:
            {
                 if((++ pt_this->i2_hlt_idx) > 1)
                     pt_this->i2_hlt_idx = 1;

                    MENU_CHK_FAIL(menu_pm_repaint());
            }
                break;
            default:
                break;
        }
    }
    else if (WGL_MSG_KEY_UP==ui4_msg && ((UINT32)pv_param1 == BTN_CURSOR_UP || (UINT32)pv_param1 == BTN_CURSOR_DOWN))
    {
        UINT16   ui2_crnt_ht;

        MENU_CHK_FAIL(c_wgl_do_cmd(pt_this->h_full_color_lb2,
                                   WGL_CMD_LB_GET_HLT_INDEX,
                                   WGL_PACK(&ui2_crnt_ht),
                                   NULL));
        _tts_play(ui2_crnt_ht == 1 ? MLM_MENU_KEY_ON : MLM_MENU_KEY_OFF,0,FALSE);
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);

}

static INT32 _hide_device_lb2_proc_fct(HANDLE_T            h_widget,
                                        UINT32              ui4_msg,
                                        VOID*               pv_param1,
                                        VOID*               pv_param2)
{
    INT32    i4_ret;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if(WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        UINT16   ui2_crnt_ht;
        i4_ret = c_wgl_do_cmd(pt_this->h_hide_device_lb2,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_this->h_hide_device_lb2,
                              WGL_CMD_LB_UNHLT_ELEM,
                              WGL_PACK(ui2_crnt_ht),
                              NULL);
        MENU_CHK_FAIL(i4_ret);
    }
    else if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_hide_device_lb2,
                              WGL_CMD_LB_HLT_ELEM,
                              WGL_PACK((UINT16)pt_this->i2_hlt_idx),
                              NULL);
        MENU_CHK_FAIL(i4_ret);

        _ope_lst_move_help_tip(2);
        if(_ope_lst_get_tv_comp_input())
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_HIDE_TV_COMP_INPUT));
        }
        else
        {
            menu_set_and_show_help_tip(MENU_TEXT(ui2_help_tip_key[OPE_LST_IDX_HIDE]));
        }
        menu_pm_repaint();
        _tts_play(pt_this->i2_hlt_idx == 1 ? MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE : MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE,0,FALSE);
    }
    else if(WGL_MSG_KEY_DOWN == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_hide_device_lb2,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&pt_this->i2_hlt_idx),
                              NULL);
        MENU_CHK_FAIL(i4_ret);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
                {
                    i4_ret = _ope_lst_set_hide_from_input_list((UINT8)pt_this->i2_hlt_idx);
                    MENU_CHK_FAIL(i4_ret);
                    pt_this->i2_hlt_idx = OPE_LST_IDX_HIDE;
                    i4_ret = _ope_lst_hide_device_page_hide();
                    MENU_CHK_FAIL(i4_ret);
                    i4_ret = _ope_lst_main_page_show();
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_RETURN:
                {
                    pt_this->i2_hlt_idx = OPE_LST_IDX_HIDE;
                    i4_ret = _ope_lst_hide_device_page_hide();
                    MENU_CHK_FAIL(i4_ret);
                    i4_ret = _ope_lst_main_page_show();
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_CURSOR_UP:
                if (pt_this->i2_hlt_idx == 0)
                {
                    pt_this->i2_hlt_idx = -1;
                    i4_ret = _ope_lst_update_focus(TRUE);
                    MENU_CHK_FAIL(i4_ret);

                    return MENUR_OK;
                }
                break;
            case BTN_CURSOR_DOWN:
                break;
            default:
                break;
        }
    }
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
        UINT16 ui2_hlt_idx = 0;

        MENU_CHK_FAIL(c_wgl_do_cmd (h_widget,
                                    WGL_CMD_LB_GET_HLT_INDEX,
                                    WGL_PACK (&ui2_hlt_idx),
                                    NULL));
        MENU_CHK_FAIL(i4_ret);
        _tts_play(ui2_hlt_idx == 1 ? MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE :MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE ,0,FALSE);
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);

}

static INT32 _ope_lst_lb2_create(HANDLE_T h_parent, HANDLE_T *ph_wgt, VOID * pf_proc_fct)
{
    INT32  i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    ope_lb2_proc_fct pf_lb2_proc_fct = NULL;
    GL_RECT_T                 t_rect = {0};

    pf_lb2_proc_fct = (ope_lb2_proc_fct)pf_proc_fct;
    /* Listbox */
    {
        at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
        at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
        at_cols[0].ui2_max_text_len = 64;
        at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

        t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                      WGL_STL_LB_NO_SCROLL;

        t_lb_init.ui2_max_elem_num  = 32;
        t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
        t_lb_init.ui2_elem_distance = 0;
        t_lb_init.ui1_col_num       = 1;
        t_lb_init.at_cols           = at_cols;

        SET_RECT_BY_SIZE (&t_rect,
                          0,
                          0,
                          CONTENT_W,
                          CONTENT_H);

        i4_ret = menu_list2_create(h_parent,
                                   &t_rect,
                                   pf_lb2_proc_fct,
                                   &t_lb_init,
                                   NULL,
                                   ph_wgt);
        MENU_CHK_FAIL(i4_ret);
    }
    /* WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE */
    {
        t_img_elem.h_normal             = h_g_menu_img_item_bk;
        t_img_elem.h_disable            = h_g_menu_img_item_bk;
        t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
        t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
        t_img_elem.h_pushed             = h_g_menu_img_item_bk;
        t_img_elem.h_selected           = h_g_menu_img_item_bk;
        t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
        i4_ret = c_wgl_do_cmd (*ph_wgt,
                               WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                               WGL_PACK(& t_img_elem),
                               NULL);
        MENU_CHK_FAIL(i4_ret);
    }
    /* WGL_CMD_LB_SET_COL_COLOR */
    {
        t_lb_color.t_normal = t_g_menu_color_white;
        t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
        t_lb_color.t_highlight = t_g_menu_color_white;
        t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
        t_lb_color.t_pushed = t_g_menu_color_white;
        t_lb_color.t_selected = t_g_menu_color_white;
        t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

        i4_ret = c_wgl_do_cmd(*ph_wgt,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(0, WGL_CLR_TEXT),
                              WGL_PACK(&t_lb_color) );
        MENU_CHK_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _ope_lst_pic_mode_cfg_nfy_reg()
{
#if 0
    INT32 i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_VIDEO,
                              NULL,
                              _ope_lst_pic_mode_nfy_fct,
                              &pt_this->ui2_cfg_pic_mode_nfy_id);
    MENU_CHK_FAIL(i4_ret);
#endif
    return MENUR_OK;
}

INT32 inp_init_ctx(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    /* ui2_cfg_pic_mode_nfy_id */
    MENU_CHK_FAIL(_ope_lst_pic_mode_cfg_nfy_reg());

    /* h_full_clor_timer */
    MENU_CHK_FAIL(c_timer_create(&pt_this->h_full_clor_timer));

    return MENUR_OK;
}

static INT32 _ope_lst_page_create(UINT32 ui4_page_id,
                                VOID*  pv_create_data)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret;
    HANDLE_T h_cnt_frm;
    UINT16 ui2_i;

    /*init member*/
    {
        c_memset(pt_this, 0, sizeof(MENU_PAGE_INPUT_OPE_LST_SETTING_T));
        pt_this->h_svctx_main = NULL_HANDLE;
        pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_UNKNOW;
        pt_this->b_is_444_content = FALSE;
        pt_this->ui2_cfg_pic_mode_nfy_id = 0;
    }

    /* view init */
    {
        /* main page */
        {
            i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
            MENU_CHK_FAIL(i4_ret);

            c_memset(pt_this->t_ope_lst, 0, sizeof(pt_this->t_ope_lst));

            for (ui2_i = 0; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
            {
                if (ui2_i == OPE_LST_IDX_FULL_CHROMA || ui2_i == OPE_LST_IDX_HIDE || ui2_i == OPE_LST_IDX_FULL_COLOR)
                {
                    i4_ret = menu_list_create(h_cnt_frm, ui2_i, 2, _ope_lst_general_fct, &pt_this->t_ope_lst[ui2_i].h_wgt);
                    MENU_CHK_FAIL(i4_ret);

                    continue;
                }
                else
                {
                    i4_ret = menu_list_create(h_cnt_frm, ui2_i, 1, _ope_lst_general_fct, &pt_this->t_ope_lst[ui2_i].h_wgt);
                    MENU_CHK_FAIL(i4_ret);

                    i4_ret = _ope_lst_lb_degenerate(pt_this->t_ope_lst[ui2_i].h_wgt);
                    MENU_CHK_FAIL(i4_ret);
                }
            }
        }

        /* chorma page */
        {
            i4_ret = _ope_lst_lb2_create(h_cnt_frm, &pt_this->h_full_chroma_lb2, _full_chroma_lb2_proc_fct);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(pt_this->h_full_chroma_lb2, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }

        /* color page */
        {
            i4_ret = _ope_lst_lb2_create(h_cnt_frm, &pt_this->h_full_color_lb2, _full_color_lb2_proc_fct);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(pt_this->h_full_color_lb2, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }
        /* hide input page */
        {
             i4_ret = _ope_lst_lb2_create(h_cnt_frm, &pt_this->h_hide_device_lb2, _hide_device_lb2_proc_fct);
             MENU_CHK_FAIL(i4_ret);

             i4_ret = c_wgl_set_visibility(pt_this->h_hide_device_lb2, WGL_SW_HIDE);
             MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }

    }

#if 0  /* update full chroma 444 when TV init ??? */
    //menu_ope_lst_hdmi_color_space_is_444 == FALSE

    if (!pt_this->b_is_444_content)
    {
        i4_ret = a_cfg_cust_set_full_chroma_444(0);
        MENU_CHK_FAIL(i4_ret == APP_CFGR_OK ? MENUR_OK : i4_ret);
    }
#endif


    /* h_svctx_main */
    // MENU_CHK_FAIL(_ope_lst_svctx_nfy_reg()); // no need, remove it

    /* ui2_cfg_pic_mode_nfy_id */
    MENU_CHK_FAIL(_ope_lst_pic_mode_cfg_nfy_reg());

    /* h_full_clor_timer */
    MENU_CHK_FAIL(c_timer_create(&pt_this->h_full_clor_timer));

    return MENUR_OK;

}

static INT32 _ope_lst_main_page_update_v_e(VOID)
{
    INT32 i4_ret;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    /* reset */
    {
        UINT16 ui2_i;
        /* reset visibility  enable item */
        for (ui2_i = 0; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
        {
           pt_this->t_ope_lst[ui2_i].b_is_visibility = FALSE;
           pt_this->t_ope_lst[ui2_i].b_is_enable = FALSE;
        }
    }
    i4_ret = _ope_lst_main_page_set_v_e(pt_this->t_isl_rec_of_dev);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}



static INT32 _ope_lst_main_page_set_v_e(ISL_REC_T t_isl_rec)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    /* set visibilty */
    if ( t_isl_rec.e_src_type == INP_SRC_TYPE_TV )    /* TV */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_visibility        = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_visibility  = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_visibility = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_visibility    = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_SZ].b_is_visibility      = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_POS].b_is_visibility     = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_visibility        = TRUE;
    }
    else if (pt_this->t_isl_rec_of_dev.e_src_type == INP_SRC_TYPE_VTRL)  /* virtual */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_visibility        = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_visibility  = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_visibility = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_visibility    = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_SZ].b_is_visibility      = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_POS].b_is_visibility     = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_visibility        = TRUE;
    }
    else if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_visibility        = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_visibility    = FALSE;

        {
            UTF16_T     w2s_hdmi_index;
            CHAR        c_hdmi_index;
            UINT8       ui1_hdmi_index = 0;
            MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info = {0};

            if (a_cfg_custom_get_wifi_remote_support())
            {
                i4_ret = menu_device_get_device_info(&t_device_info);
            }
            else
            {
                i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
            }

            /*should be HDMI-x*/
            if(c_uc_w2s_strlen(t_device_info.u_device_data.t_input.pw2s_disp_name) > 5)
            {
              w2s_hdmi_index = c_uc_w2s_get(t_device_info.u_device_data.t_input.pw2s_disp_name, 5);
            }
            else
            {
              w2s_hdmi_index = L'1';
            }
            c_uc_w2s_to_ps(&w2s_hdmi_index, &c_hdmi_index, sizeof(CHAR));
            ui1_hdmi_index = _atoi_one_char(&c_hdmi_index);

            pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_visibility     = menu_full_color_is_enable(ui1_hdmi_index);
        }

        pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_visibility = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_SZ].b_is_visibility      = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_POS].b_is_visibility     = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_visibility        = TRUE;
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))    /* COMP */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_visibility        = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_visibility    = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_visibility  = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_visibility = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_SZ].b_is_visibility      = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_PIC_POS].b_is_visibility     = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_visibility        = TRUE;
    }
    else
    {
        MENU_CHK_FAIL(MENUR_INV_ARG);
    }

    /* check visibilty */
    {
        if ( t_isl_rec.t_avc_info.e_video_type != DEV_AVC_VGA )    /* VGA */
        {
            pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_visibility = FALSE;
        }

        if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
        {
            pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_visibility = TRUE;
        }
    }

    /* set enable */
    if ( t_isl_rec.e_src_type == INP_SRC_TYPE_TV )                   /* TV */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_enable            = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_enable            = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_enable      = FALSE;
    }
    else if (pt_this->t_isl_rec_of_dev.e_src_type == INP_SRC_TYPE_VTRL)    /* virtual */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_enable            = FALSE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_enable            = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_enable      = FALSE;
    }
    else if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_enable            = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_enable            = TRUE;

        {
            UTF16_T     w2s_hdmi_index;
            CHAR        c_hdmi_index;
            UINT8       ui1_hdmi_index = 0;
            MENU_DEVICE_PAGE_DEVICE_INFO_T  t_device_info = {0};

            if (a_cfg_custom_get_wifi_remote_support())
            {
                i4_ret = menu_device_get_device_info(&t_device_info);
            }
            else
            {
                i4_ret = menu_device_get_device_info_no_wifi_remote(&t_device_info);
            }

            /*should be HDMI-x*/
            if(c_uc_w2s_strlen(t_device_info.u_device_data.t_input.pw2s_disp_name) > 5)
            {
              w2s_hdmi_index = c_uc_w2s_get(t_device_info.u_device_data.t_input.pw2s_disp_name, 5);
            }
            else
            {
              w2s_hdmi_index = L'1';
            }
            c_uc_w2s_to_ps(&w2s_hdmi_index, &c_hdmi_index, sizeof(CHAR));
            ui1_hdmi_index = _atoi_one_char(&c_hdmi_index);

            pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_enable      = menu_full_color_is_enable(ui1_hdmi_index);
        }
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))    /* COMP */
    {
        pt_this->t_ope_lst[OPE_LST_IDX_NAME].b_is_enable            = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_HIDE].b_is_enable            = TRUE;
        pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_enable      = FALSE;
    }
    else
    {
        MENU_CHK_FAIL(MENUR_INV_ARG);
    }

    /*  check enable */
    {
        ISL_REC_T t_isl_rec_real;
        i4_ret = menu_get_crnt_isl(&t_isl_rec_real);
        MENU_LOG_ON_FAIL(i4_ret);

        if (t_isl_rec_real.ui1_id == t_isl_rec.ui1_id)
        {
            pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_enable = menu_vga_auto_is_enable();
            pt_this->t_ope_lst[OPE_LST_IDX_PIC_SZ].b_is_enable   = menu_picture_size_is_enable();
            pt_this->t_ope_lst[OPE_LST_IDX_PIC_POS].b_is_enable  = menu_picture_position_is_enable();
            pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_enable = TRUE;
        }
        else
        {
            pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].b_is_enable = FALSE;
            pt_this->t_ope_lst[OPE_LST_IDX_VGA_AUTO].b_is_enable    = FALSE;
            pt_this->t_ope_lst[OPE_LST_IDX_PIC_SZ].b_is_enable      = FALSE;
            pt_this->t_ope_lst[OPE_LST_IDX_PIC_POS].b_is_enable     = FALSE;
            pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].b_is_enable  = FALSE;
        }
    }

    return MENUR_OK;
}

static VOID _ope_lst_move_help_tip(UINT8 ui1_row_num)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T  h_last_shadow_item;

    /* move help tip text */
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui1_row_num + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static INT32 _ope_lst_update_focus(BOOL b_repaint)
{
    INT32                               i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if(pt_this->i2_hlt_idx == -1)
    {
          i4_ret = menu_set_focus_on_backbar(b_repaint);
          MENU_CHK_FAIL(i4_ret);
          return MENUR_OK;
    }

    switch(pt_this->e_focus_page )
    {
        case MENU_PAGE_INPUT_OPE_LST_SETTING_MAIN:
        {
            if (pt_this->t_ope_lst[pt_this->i2_hlt_idx].b_is_visibility && pt_this->t_ope_lst[pt_this->i2_hlt_idx].b_is_enable)
            {
                i4_ret = c_wgl_set_focus(pt_this->t_ope_lst[pt_this->i2_hlt_idx].h_wgt, FALSE);
                MENU_CHK_FAIL(i4_ret);
            }
            else
            {
                i4_ret = _ope_lst_set_focus_next(FALSE);
                MENU_CHK_FAIL(i4_ret);
            }
        }
        break;
        case     MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_COLOR:
        {
            i4_ret = c_wgl_set_focus(pt_this->h_full_color_lb2, WGL_NO_AUTO_REPAINT);
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case     MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_CHROMA:
        {
            i4_ret = c_wgl_set_focus(pt_this->h_full_chroma_lb2, WGL_NO_AUTO_REPAINT);
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case MENU_PAGE_INPUT_OPE_LST_SETTING_HIDE_DEVICE:
        {
           i4_ret = c_wgl_set_focus(pt_this->h_hide_device_lb2, WGL_NO_AUTO_REPAINT);
           MENU_CHK_FAIL(i4_ret);
        }
        break;
        default:
        {
           MENU_CHK_FAIL(MENUR_INV_STATE);
        }
        break;
    }

    if (b_repaint)
    {
        menu_pm_repaint();
    }
    return MENUR_OK;
}


static INT32 _ope_lst_main_page_move_item()
{
    INT32 i4_ret;
    UINT16 ui2_i;
    UINT16 ui2_visible = 0;
    GL_RECT_T t_rect;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    for (ui2_i = 0; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
    {
        if (pt_this->t_ope_lst[ui2_i].b_is_visibility)
        {
            SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_LEFT,
                         MENU_ITEM_V_HEIGHT * ui2_visible,
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);

            i4_ret = c_wgl_move(pt_this->t_ope_lst[ui2_i].h_wgt, &t_rect, WGL_NO_AUTO_REPAINT);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);

            ui2_visible++;
        }
    }

    _ope_lst_move_help_tip(ui2_visible);

    return MENUR_OK;

}


static INT32 _ope_lst_main_page_refresh(BOOL b_repaint)
{
    INT32 i4_ret = MENUR_OK;
    UINT16 ui2_i;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    i4_ret = _ope_lst_main_page_move_item();
    MENU_CHK_FAIL(i4_ret);

    for (ui2_i = 0; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
    {
        if (pt_this->t_ope_lst[ui2_i].b_is_visibility)
        {
            i4_ret = c_wgl_set_visibility(pt_this->t_ope_lst[ui2_i].h_wgt, WGL_SW_NORMAL);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }
        else
        {
            i4_ret = c_wgl_set_visibility(pt_this->t_ope_lst[ui2_i].h_wgt, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);

        }

        if (FALSE == pt_this->t_ope_lst[ui2_i].b_is_enable)
        {
            i4_ret = c_wgl_enable(pt_this->t_ope_lst[ui2_i].h_wgt, FALSE);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }
        else
        {
            i4_ret = c_wgl_enable(pt_this->t_ope_lst[ui2_i].h_wgt, TRUE);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }
    }

    if (b_repaint)
    {
        menu_pm_repaint();
    }

    return MENUR_OK;
}

static INT32 _ope_lst_main_page_show(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;
    UINT8 ui1_value = 0;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_MAIN;

    i4_ret = _ope_lst_main_page_refresh(FALSE);
    MENU_CHK_FAIL(i4_ret);

    /* hiden item */
    i4_ret = _ope_lst_get_hide_from_input_list(&ui1_value);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_list_set_idx(pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt, (UINT16)ui1_value);
    MENU_CHK_FAIL(i4_ret);

    menu_list_adjust_rect(pt_this->t_ope_lst[OPE_LST_IDX_HIDE].h_wgt);
    menu_list_adjust_rect(pt_this->t_ope_lst[OPE_LST_IDX_FULL_CHROMA].h_wgt);
    menu_list_adjust_rect(pt_this->t_ope_lst[OPE_LST_IDX_FULL_COLOR].h_wgt);

    i4_ret = _ope_lst_update_focus(FALSE);
    MENU_CHK_FAIL(i4_ret);

    menu_pm_repaint();

    return MENUR_OK;
}

static INT32 _ope_lst_page_main_page_hide(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;
    UINT16 ui2_i = 0;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_UNKNOW;

    for(ui2_i = 0; ui2_i < OPE_LST_INIT_LEN; ui2_i++)
    {
        if (pt_this->t_ope_lst[ui2_i].b_is_visibility)
        {
            i4_ret = c_wgl_set_visibility(pt_this->t_ope_lst[ui2_i].h_wgt, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);
        }
    }

    return MENUR_OK;
}


static INT32 _ope_lst_full_chroma_page_hide(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_UNKNOW;

    i4_ret = c_wgl_set_visibility(pt_this->h_full_chroma_lb2, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_full_chroma_page_show(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_CHROMA;

    {
        UINT8 ui1_value = 0;
        i4_ret = _ope_lst_get_full_chroma(&ui1_value);
        MENU_CHK_FAIL(i4_ret);
        pt_this->i2_hlt_idx = ui1_value;
        DBG_LOG_PRINT(("[MENU] %s %d value = %d\n",__FUNCTION__,__LINE__,ui1_value));
    }


    i4_ret = c_wgl_set_visibility(pt_this->h_full_chroma_lb2, WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_full_chroma_lb2, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    _ope_lst_move_help_tip(2);

    menu_pm_repaint();

    return MENUR_OK;

}

static INT32 _ope_lst_full_color_page_hide(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_UNKNOW;

    i4_ret = c_wgl_set_visibility(pt_this->h_full_color_lb2, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_full_color_page_show(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_COLOR;

    {
        UINT8 ui1_value = 0;
        i4_ret = _ope_lst_get_full_uhd_color(&ui1_value);
        MENU_CHK_FAIL(i4_ret);
        pt_this->i2_hlt_idx = ui1_value;
        DBG_LOG_PRINT(("[MENU] %s %d value = %d\n",__FUNCTION__,__LINE__,ui1_value));
    }


    i4_ret = c_wgl_set_visibility(pt_this->h_full_color_lb2, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_full_color_lb2, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    _ope_lst_move_help_tip(2);

    menu_pm_repaint();

    return MENUR_OK;

}

static INT32 _ope_lst_hide_device_page_hide(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_UNKNOW;

    i4_ret = c_wgl_set_visibility(pt_this->h_hide_device_lb2, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_hide_device_page_show(VOID)
{
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;
    INT32 i4_ret = MENUR_OK;

    pt_this->e_focus_page = MENU_PAGE_INPUT_OPE_LST_SETTING_HIDE_DEVICE;

    /* update hl index*/
    {
        UINT8 ui1_value = 0;
        i4_ret = _ope_lst_get_hide_from_input_list(&ui1_value);
        MENU_CHK_FAIL(i4_ret);
        pt_this->i2_hlt_idx = ui1_value;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_hide_device_lb2, WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_hide_device_lb2, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    _ope_lst_move_help_tip(2);

    menu_pm_repaint();

    return MENUR_OK;
}

static INT32 _ope_lst_page_show(UINT32 ui4_page_id)
{
    INT32 i4_ret = MENUR_OK;

    /* update language*/
    i4_ret = _ope_lst_chg_lang();
    MENU_CHK_FAIL(i4_ret);

    /* ui update*/
    /* title */
    i4_ret = _ope_lst_update_title();
    MENU_CHK_FAIL(i4_ret);
    /* back */
    i4_ret = menu_set_backbar_proc(_backbar_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _ope_lst_main_page_show();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ope_lst_page_destroy(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    if (pt_this->h_svctx_main != NULL_HANDLE)
    {
        i4_ret = c_svctx_close(pt_this->h_svctx_main);
        MENU_CHK_FAIL(i4_ret);
    }

    if (pt_this->ui2_cfg_pic_mode_nfy_id != 0)
    {
        i4_ret = a_cfg_notify_unreg(pt_this->ui2_cfg_pic_mode_nfy_id);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _ope_lst_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret = MENUR_OK;
    MENU_PAGE_INPUT_OPE_LST_SETTING_T * pt_this = &t_this_page;

    switch(pt_this->e_focus_page)
    {
        case MENU_PAGE_INPUT_OPE_LST_SETTING_MAIN:
        {
            i4_ret = _ope_lst_page_main_page_hide();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_CHROMA:
        {
            i4_ret = _ope_lst_full_chroma_page_hide();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case MENU_PAGE_INPUT_OPE_LST_SETTING_FULL_COLOR:
        {
            i4_ret = _ope_lst_full_color_page_hide();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case MENU_PAGE_INPUT_OPE_LST_SETTING_HIDE_DEVICE:
        {
            i4_ret = _ope_lst_hide_device_page_hide();
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        default:
        {
            MENU_LOG_ON_FAIL(MENUR_INV_STATE);
        }
        break;
    }

    return MENUR_OK;
}


static INT32 _ope_lst_page_get_focus(UINT32 ui4_page_id,
                                     MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _ope_lst_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _ope_lst_page_update(UINT32 ui4_page_id,
                                      UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

extern INT32 menu_input_ope_lst_init(VOID)
{
    MENU_DEBUG_INPUT_SRC(DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    t_g_menu_input_ope_list.pf_menu_page_create =    _ope_lst_page_create;
    t_g_menu_input_ope_list.pf_menu_page_destroy=    _ope_lst_page_destroy;
    t_g_menu_input_ope_list.pf_menu_page_show=       _ope_lst_page_show;
    t_g_menu_input_ope_list.pf_menu_page_hide=       _ope_lst_page_hide;
    t_g_menu_input_ope_list.pf_menu_page_get_focus=  _ope_lst_page_get_focus;
    t_g_menu_input_ope_list.pf_menu_page_lose_focus= _ope_lst_page_lose_focus;
    t_g_menu_input_ope_list.pf_menu_page_update=     _ope_lst_page_update;

    return MENUR_OK;

}

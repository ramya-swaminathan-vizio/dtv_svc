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
#include "menu_page_device_setting_no_wifi_remote.h"
#include "menu_device.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"

#include "wizard/a_wzd.h"
#include "app_util/a_isl.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "res/menu2/menu_custom.h"

#include "wfrrc_interface.h"

#include "mmp/a_mmp.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_CEC_MENU
#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "wfd/wfd_p2p_conn.h"
#include "nav/input_src/a_input_src.h"

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_T          UINT8
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_REMOTE   ((UINT8)0x01)
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_INPUT    ((UINT8)0x02)
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_MIRACAST ((UINT8)0x04)
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_SOUNDBAR ((UINT8)0x08)
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_VTRL     ((UINT8)0x16)
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_UNKNOW   ((UINT8)0x00)


#ifdef APP_CEC_MENU
#define MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_CEC_DEV ((UINT8)0x10)
#endif

#define _INIT_HELP_TXT_ARRAY(ui2_help_text_num,aui2_help_txt)    \
do {\
    MENU_DEVICE_TYPE_IDX_UNPAIR = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_NAME = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_INPUT_SOURCE = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_DEVICE_TYPE = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_DEVICE_BRAND = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_DEVICE_MODEL = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_CONFIRM_IR = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_DEVICE_MIRACAST_NAME_4_DEV = ui2_help_text_num++;\
    MENU_DEVICE_TYPE_IDX_EMPTY = ui2_help_text_num++;\
\
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_UNPAIR]                      = MLM_MENU_KEY_HELP_TIP_DEVICE_UNPAIR;  \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_NAME]                        = MLM_MENU_KEY_HELP_TIP_DEVICE_NAME;    \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_INPUT_SOURCE]                = MLM_MENU_KEY_HELP_TIP_DEVICE_INPUT_SOURCE;    \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_DEVICE_TYPE]                 = MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_TYPE; \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_DEVICE_BRAND]                = MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_BRAND;    \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_DEVICE_MODEL]                = MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_MODEL;    \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_CONFIRM_IR]                  = MLM_MENU_KEY_HELP_TIP_DEVICE_CONFIRM_IR;  \
    aui2_help_txt[MENU_DEVICE_TYPE_IDX_DEVICE_MIRACAST_NAME_4_DEV]  = MLM_MENU_KEY_HELP_TIP_DEVICE_MIRACAST_NAME_4_DEV; \
}while(0)

#define MENU_DEVICE_TYPE_IDX_LAST       ((UINT8)32)
#ifdef DBG_INFO
#undef DBG_INFO
#define DBG_INFO(x) DBG_LOG_PRINT(x)
#endif

typedef struct _MENU_DEVICE_SETTING_PAGE_DATA_T
{
    /* member */
    UINT32       ui4_device_setting_page_id;
    UINT32       ui4_device_status_info_page_id;
    UINT32       ui4_pair_wifi_device_page_id;
    UINT32       ui4_name_input_page_id;
    UINT32       ui4_add_new_device_page_id;

    MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_T e_device_type;

    MENU_DEVICE_PAGE_NAV_TYPE_T e_page_nav_type;

    /* status */
    UINT16       ui2_hlt_idx;
    UINT8        ui1_input_count;

    /* view */
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_device_list;
    HANDLE_T     h_last_focus;

    /* acfg */
    /* icl */

    /* other*/
    UINT16       aui2_help_txt[MENU_DEVICE_TYPE_IDX_LAST];// = {0};
    UINT16       ui2_help_text_num;//= 0;

#ifdef APP_CEC_MENU
    MENU_DEVICE_SETTING_CEC_DEV_DATA_T t_g_menu_device_cec_dev_info;
    UINT8 g_aui1_cec_idx_map[CEC_DEV_LIST_MAX_NUM];//={0};
#endif

    UINT16   aui2_list_idx_2_input_idx[MENU_DEVICE_TYPE_IDX_LAST];

}MENU_DEVICE_SETTING_PAGE_DATA_T;

typedef enum _MENU_DEVICE_SETTING_BTN_TYPE_T
{
    MENU_DEVICE_SETTING_BTN_ADD_REMOTE = 0,
    MENU_DEVICE_SETTING_BTN_ADD_NEW_DEVICE,
    MENU_DEVICE_SETTING_BTN_ADD_MIRACAST_DEVICE,
    MENU_DEVICE_SETTING_BTN_LAST_ENTRY
}MENU_DEVICE_SETTING_BTN_TYPE_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_device_setting;
static MENU_DEVICE_SETTING_PAGE_DATA_T t_g_device_setting_page_data;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _device_listbox_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb);

/*-----------------------------------------------------------------------------
                    function implementations
 ----------------------------------------------------------------------------*/
static VOID _inp_src_get_help_tip_string(UINT8 ui1_isl_id )
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    INT32 i4_ret;
    UINT16 ui2_inp_tip_id = 0;
    ISL_REC_T t_isl_rec = {0};

    i4_ret = a_isl_get_rec_by_id(ui1_isl_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    switch(t_isl_rec.t_avc_info.e_video_type)
    {
        case DEV_TUNER:
                ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_TV;
                break;

        case DEV_AVC_COMBI:
        case DEV_AVC_COMP_VIDEO:
                ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_AV;
                break;

        case DEV_AVC_Y_PB_PR:
                ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_COMP_1 + t_isl_rec.ui1_internal_id;
                break;

        case DEV_AVC_HDMI:
                if (1 == t_isl_rec.ui1_iid_count)
                {
                    ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI;
                }
                else
                {
                    ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI_1 + t_isl_rec.ui1_internal_id;
                    //ui2_inp_tip_id = (t_isl_rec.ui1_iid_count <= 3 &&
                    //                  MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI_3 == ui2_inp_tip_id) ?
                    //                    MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI_SIDE : ui2_inp_tip_id;
                }
                break;

        case DEV_AVC_VGA:
                ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_RGB;
                break;
        case DEV_VTRL_CAST:
                if(c_strncmp(t_isl_rec.s_src_name,"watchfree",9) == 0)
                {
                    ui2_inp_tip_id = MLM_MENU_KEY_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_WATCHFREE;
                }
                break;

        default:
                break;
    }

    /* ??? */
    pt_this->aui2_help_txt[pt_this->ui2_help_text_num++] = ui2_inp_tip_id;
}

static INT32 _menu_page_device_usable_input_calculate(VOID)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    UINT8           ui1_idx = 0;
    ISL_REC_T       t_isl_rec;
    CHAR            ac_disp_name[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};
    CHAR*           ps_disp_name = NULL;
    INT32           i4_ret = MENUR_OK;
    UINT8           ui1_rec_num = 0;
    CHAR            ac_vtrl_cname[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};

    /* ??? */
    if (pt_this->ui1_input_count > 0)
    {
        return MENUR_OK;
    }

    i4_ret = a_isl_get_num_rec(&ui1_rec_num);
    MENU_LOG_ON_FAIL(i4_ret);

    for( ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
    {
        /* get isl */
        {
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
            i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        /* get ac_disp_name */
        {
            UTF16_T         w2s_disp_name[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};

            c_memset(w2s_disp_name, 0, sizeof(w2s_disp_name));
            c_uc_w2s_strncpy(w2s_disp_name, a_isl_get_display_name(&t_isl_rec),
                             MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);

            c_uc_w2s_to_ps(w2s_disp_name, ac_disp_name,
                           MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
        }

        ps_disp_name = c_str_toupper(ac_disp_name);

        if (0 == c_strncmp(ps_disp_name, "AV", 2)
            || 0 == c_strncmp(ps_disp_name, "COMP", 4)
            || 0 == c_strncmp(ps_disp_name, "HDMI", 4)
            || 0 == c_strncmp(ps_disp_name, "CAST", 4)
            || 0 == c_strncmp(ps_disp_name, "RGB", 3)
            || 0 == c_strncmp(ps_disp_name, "TV", 2)
            )
        {
            pt_this->ui1_input_count++;
        }
        a_cfg_get_vtrl_name(ui1_idx, ac_vtrl_cname, APP_CFG_CUSTOM_INP_NAME_LEN);

        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
            && (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)&&
            (t_isl_rec.ui1_internal_id > 0)&&
            (c_strlen(ps_disp_name) != 0)&&
            (c_strlen(ac_vtrl_cname) != 0))
        {
            pt_this->ui1_input_count++;
        }

    }

    return MENUR_OK;
}

extern INT32 a_isl_get_vtrl_input_display_name(ISL_REC_T*    pt_isl_rec,
                                                    CHAR*         s_name);

/*
only append HDMI and COMP source
*/
static INT32 _device_setting_add_input(VOID)
{
    INT32           i4_ret = MENUR_OK;
    UINT8           ui1_rec_num = 0;
    UINT8           ui1_idx = 0;
    UINT16          ui2_list_idx = 0;
    UINT8           ui1_av_idx[3] = {0};
    UINT8           ui1_comp_num = 0;
    UINT8           ui1_input_idx[10] = {0};
    UINT8           ui1_input_num     = 0;
    UINT8           ui1_vtrl_num = 0;
    UINT8           ui1_vtrl_idx[5] = {0};
    ISL_REC_T       t_isl_rec;
    WGL_LB_ITEM_T   at_items[2];
    UTF16_T         w2s_disp_name[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};
    UTF16_T         w2s_user_name[MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN+1] = {0};
    CHAR            ac_disp_name[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};
    CHAR            ac_vtrl_cname[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};
    CHAR            ac_user_name[MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN+1] = {0};
    CHAR            ac_disp_en_name[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    CHAR*           ps_disp_name = NULL;

    i4_ret = _menu_page_device_usable_input_calculate();
    MENU_LOG_ON_FAIL(i4_ret);

    {
        /* get record number */
        i4_ret = a_isl_get_num_rec(&ui1_rec_num);
        MENU_LOG_ON_FAIL(i4_ret);

        /* get input id to aui2_list_idx_2_input_idx */
        {
            for(ui1_idx=0; ui1_idx < ui1_rec_num; ui1_idx++)
            {
                c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
                a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

                /* check virtual input */
                {
                    if(INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type &&
                        DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type &&
                        t_isl_rec.ui1_internal_id > 0)
                    {
                        ui1_vtrl_idx[ui1_vtrl_num++] = ui1_idx;
                        continue;
                    }
                }

                if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)
                {
                    continue;
                }

                /* check comp */
                {
                    c_memset(w2s_disp_name, 0, sizeof(w2s_disp_name));
                    c_uc_w2s_strncpy(w2s_disp_name, a_isl_get_display_name(&t_isl_rec),
                                     MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);

                    c_uc_w2s_to_ps(w2s_disp_name, ac_disp_name,
                                   MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);

                    ps_disp_name = c_str_toupper(ac_disp_name);

                    if (0 == c_strncmp(ps_disp_name, "AV", 2)
                        || 0 == c_strncmp(ps_disp_name, "COMP", 4)
                        || 0 == c_strncmp(ps_disp_name, "RGB", 3))
                    {
                        ui1_av_idx[ui1_comp_num++] = ui1_idx;
                        continue;
                    }
                }
                /* check hdmi number */
                ui1_input_idx[ui1_input_num++] = ui1_idx;
            }
        }
    }

    /* append hdmi input */
    for (ui1_idx = 0; ui1_idx < ui1_input_num; ui1_idx++)
    {
        /*get isl rec */
        {
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
            a_isl_get_rec_by_idx(ui1_input_idx[ui1_idx], &t_isl_rec);
        }

        /* get display name */
        {
            c_memset(w2s_disp_name, 0, sizeof(w2s_disp_name));
            c_uc_w2s_strncpy(w2s_disp_name, a_isl_get_display_name(&t_isl_rec),
                             MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);

            c_uc_w2s_to_ps(w2s_disp_name, ac_disp_name,MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
        }

        /* get user name */
        {
            c_memset(w2s_user_name, 0, sizeof(w2s_user_name));
            a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, ac_user_name);

            /*SPEC v3.4 if name longer than 16, display ... instead of the actual name*/
            //if(c_strlen(ac_user_name)> 16)
            if(0)
            {
                ac_user_name[16] = '\0';

                c_strncat(ac_user_name, "...", 3);
            }

            if (c_strlen(ac_user_name) > 0)
            {
                c_uc_ps_to_w2s(ac_user_name, w2s_user_name,
                               MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN);
            }
        }

        /* add to list view */
        {
            //DBG_LOG_PRINT(("< menu input setting >  %s %d  add input : %s  user name : %s \n",__FUNCTION__,__LINE__,ac_disp_name,ac_user_name));

            c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
            at_items[0].e_col_type = LB_COL_TYPE_TEXT;
            at_items[0].data.pw2s_text = w2s_disp_name;
            at_items[1].e_col_type = LB_COL_TYPE_TEXT;
            at_items[1].data.pw2s_text = w2s_user_name;

            i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                                  WGL_CMD_LB_APPEND_ELEM,
                                  at_items,
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        _inp_src_get_help_tip_string(t_isl_rec.ui1_id);
        pt_this->aui2_list_idx_2_input_idx[ui2_list_idx++] = ui1_input_idx[ui1_idx];
    }


    /* append Comp/AV input */
    for (ui1_idx = 0; ui1_idx < ui1_comp_num; ui1_idx++)
    {
        /*get isl rec */
        {
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
            a_isl_get_rec_by_idx(ui1_av_idx[ui1_idx], &t_isl_rec);
        }

        /* get display name */
        {
            c_memset(w2s_disp_name, 0, sizeof(w2s_disp_name));
            c_uc_w2s_strncpy(w2s_disp_name, a_isl_get_display_name(&t_isl_rec),
                             MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);

            c_uc_w2s_to_ps(w2s_disp_name, ac_disp_name,MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
        }

        /* get user name */
        {
            c_memset(w2s_user_name, 0, sizeof(w2s_user_name));
            a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, ac_user_name);

            //if(c_strlen(ac_user_name)> 16)
            if(0)
            {
                ac_user_name[16] = '\0';

                c_strncat(ac_user_name, "...", 3);
            }

            if (c_strlen(ac_user_name) > 0)
            {
                c_uc_ps_to_w2s(ac_user_name, w2s_user_name, MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN);
            }
        }

        /* add to list view */
        {
            //DBG_LOG_PRINT(("< menu input setting >  %s %d  add input : %s  user name : %s \n",__FUNCTION__,__LINE__,ac_disp_name,ac_user_name));

            c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
            at_items[0].e_col_type = LB_COL_TYPE_TEXT;
            at_items[0].data.pw2s_text = w2s_disp_name;
            at_items[1].e_col_type = LB_COL_TYPE_TEXT;
            at_items[1].data.pw2s_text = w2s_user_name;

            i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                                  WGL_CMD_LB_APPEND_ELEM,
                                  at_items,
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        _inp_src_get_help_tip_string(t_isl_rec.ui1_id);
        pt_this->aui2_list_idx_2_input_idx[ui2_list_idx++] = ui1_av_idx[ui1_idx];
    }

    /* append virtl input */
    for (ui1_idx = 0;ui1_idx < ui1_vtrl_num;ui1_idx++)
    {
        /*get isl rec */
        {
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
            i4_ret = a_isl_get_rec_by_idx(ui1_vtrl_idx[ui1_idx], &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /* get display name */
        {
            a_cfg_get_vtrl_name(ui1_idx, ac_vtrl_cname, APP_CFG_CUSTOM_INP_NAME_LEN);

            a_isl_get_vtrl_input_display_name(&t_isl_rec,ac_disp_name);

            if((c_strlen(ac_disp_name)==0)||(c_strlen(ac_vtrl_cname)==0))
            {
                continue;
            }
            a_cfg_get_name_display(1,t_isl_rec.ui1_internal_id - 1,ac_disp_en_name,APP_CFG_CUSTOM_INP_NAME_LEN);
            DBG_LOG_PRINT(("%s_%d ac_disp_en_name:%s \n",__FUNCTION__,__LINE__,ac_disp_en_name));
            if(!a_nav_ipts_vtrl_input_hideable(ac_disp_en_name))
            {
                continue;
            }
            c_memset(w2s_disp_name, 0, sizeof(w2s_disp_name));
            c_uc_ps_to_w2s(ac_disp_name, w2s_disp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        }

        /* get user name  ps: virtual input should not change input name */
        {
            c_memset(w2s_user_name, 0, sizeof(w2s_user_name));
            c_memset(ac_user_name, 0, sizeof(ac_user_name));
            //a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, ac_user_name);
        }

        /* add to list view */
        {
            //DBG_LOG_PRINT(("< menu input setting >  %s %d  add input : %s  user name : %s \n",__FUNCTION__,__LINE__,ac_disp_name,ac_user_name));

            c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
            at_items[0].e_col_type = LB_COL_TYPE_TEXT;
            at_items[0].data.pw2s_text = w2s_disp_name;
            at_items[1].e_col_type = LB_COL_TYPE_TEXT;
            at_items[1].data.pw2s_text = w2s_user_name;

            i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                                  WGL_CMD_LB_APPEND_ELEM,
                                  at_items,
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        //pt_this->aui2_help_txt[pt_this->ui2_help_text_num++] = MLM_MENU_KEY_EMPTY;
        _inp_src_get_help_tip_string(t_isl_rec.ui1_id);
        pt_this->aui2_list_idx_2_input_idx[ui2_list_idx++] = ui1_vtrl_idx[ui1_idx];
    }

    pt_this->e_device_type |=  MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_INPUT;

    return i4_ret;
}

#ifdef APP_CEC_MENU
/*----------------------------------------------------------------------------
 * Name: menu_device_cec_list_idx_to_cfg_idx_no_wifi_remote
 *
 * Description: menu_device_cec_list_idx_to_cfg_idx_no_wifi_remote
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT8 menu_device_cec_list_idx_to_cfg_idx_no_wifi_remote(UINT8 ui1_idx)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    return pt_this->g_aui1_cec_idx_map[ui1_idx];
}
/*----------------------------------------------------------------------------
 * Name: menu_device_cec_cfg_idx_to_list_idx_no_wifi_remote
 *
 * Description: menu_device_cec_cfg_idx_to_list_idx_no_wifi_remote
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT8 menu_device_cec_cfg_idx_to_list_idx_no_wifi_remote(UINT8 ui1_idx)
{
    UINT8 ui1_i;
    UINT8 ui1_list_idx = 0;
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    for(ui1_i=0;ui1_i<CEC_DEV_LIST_MAX_NUM;ui1_i++)
    {
        if (pt_this->g_aui1_cec_idx_map[ui1_i] == ui1_idx)
        {
            ui1_list_idx = ui1_i;
            break;
        }
    }

    return ui1_list_idx;
}

#endif //APP_CEC_MENU
static INT32 _device_setting_show_device_list(VOID)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    INT32           i4_ret = MENUR_OK;

    /* add item */
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                              WGL_CMD_LB_DEL_ALL,
                              NULL,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _device_setting_add_input();
        MENU_LOG_ON_FAIL(i4_ret);

#if 0
        i4_ret = _device_setting_add_soundbar();
        MENU_LOG_ON_FAIL(i4_ret);

#if APP_CEC_MENU
        i4_ret = _device_setting_add_cec_dev();
        MENU_LOG_ON_FAIL(i4_ret);
#endif

#endif
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_device_list,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    {
        HANDLE_T        h_last_shadow_item = NULL_HANDLE;
        GL_RECT_T       t_rect = {0};
        UINT16          ui2_device_num = 0;

        i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                              WGL_CMD_LB_GET_ELEM_NUM,
                              WGL_PACK (&ui2_device_num),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
        MENU_LOG_ON_FAIL(i4_ret);

        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_device_num + CONTENT_Y;
        t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

        i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _device_listbox_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT8                       ui1_col;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    GL_COLOR_T          t_color_disable = { 255, {128}, {128}, {128}};

//    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    INT32           i4_ret = MENUR_OK;

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_TRANSP,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*)pt_lb_init,
                                  pv_tag,
                                  ph_lb);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK((UINT16)ui1_col),
                                   WGL_PACK(&t_fnt_info));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = MENU_DEVICE_SETTING_LB_INSET_LEFT + 8;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = MENU_DEVICE_SETTING_LB_INSET_RIGHT - 10;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_clr_elem, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
    t_clr_elem.t_normal             = t_g_menu_color_transp;
    t_clr_elem.t_disable            = t_g_menu_color_transp;
    t_clr_elem.t_highlight          = t_g_menu_color_transp;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_transp;
    t_clr_elem.t_pushed             = t_g_menu_color_transp;
    t_clr_elem.t_selected           = t_g_menu_color_transp;
    t_clr_elem.t_selected_disable   = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2(ui1_col, WGL_CLR_BK),
                               WGL_PACK(& t_clr_elem));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_memset(&t_clr_elem, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
    t_clr_elem.t_normal             = t_g_menu_color_white;
    t_clr_elem.t_disable            = t_color_disable;
    t_clr_elem.t_highlight          = t_g_menu_color_white;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_white;
    t_clr_elem.t_pushed             = t_g_menu_color_white;
    t_clr_elem.t_selected           = t_g_menu_color_white;
    t_clr_elem.t_selected_disable   = t_g_menu_color_white;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_COLOR,
                                   WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                   WGL_PACK(& t_clr_elem));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set background image */
    c_memset(&t_img_elem, 0, sizeof(WGL_LB_IMG_ELEM_SET_T));
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set long text scroll effect */
    c_memset(&t_hlt_elem_effect, 0, sizeof(WGL_LB_HLT_ELEM_EFFECT_T));
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _menu_device_setting_device_list_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    INT32  i4_ret = MENUR_OK;
    UINT16 ui2_elem_num = 0;
    UTF16_T w2s_name_str[128] = {0};

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
            {
                /* ui2_hlt_idx */
                {
                    i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_LB_GET_HLT_INDEX,
                                           WGL_PACK (&pt_this->ui2_hlt_idx),
                                           NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                /* hlt text */
                {
                    i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_LB_GET_ITEM_TEXT,
                                           WGL_PACK_2 (pt_this->ui2_hlt_idx, 0),
                                           WGL_PACK   (w2s_name_str));
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_uc_w2s_strncat(w2s_name_str, L" ", c_uc_w2s_strlen(L" "));

                    i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_LB_GET_ITEM_TEXT,
                                           WGL_PACK_2 (pt_this->ui2_hlt_idx, 1),
                                           WGL_PACK   (w2s_name_str + c_uc_w2s_strlen(w2s_name_str)));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                menu_set_help_tip(MENU_TEXT(pt_this->aui2_help_txt[pt_this->ui2_hlt_idx]));
#ifdef APP_TTS_SUPPORT
                a_app_tts_play(w2s_name_str, 128);
#endif
            }
            break;
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
            {
                UINT32 ui4_keycode = (UINT32)param1;
                /* ui2_hlt_idx */
                 {
                     i4_ret = c_wgl_do_cmd (h_widget,
                                            WGL_CMD_LB_GET_HLT_INDEX,
                                            WGL_PACK (&pt_this->ui2_hlt_idx),
                                            NULL);
                     MENU_LOG_ON_FAIL(i4_ret);
                 }
                 /* hlt text */
                 {
                     i4_ret = c_wgl_do_cmd (h_widget,
                                            WGL_CMD_LB_GET_ITEM_TEXT,
                                            WGL_PACK_2 (pt_this->ui2_hlt_idx, 0),
                                            WGL_PACK   (w2s_name_str));
                     MENU_LOG_ON_FAIL(i4_ret);

                     c_uc_w2s_strncat(w2s_name_str, L" ", c_uc_w2s_strlen(L" "));

                     i4_ret = c_wgl_do_cmd (h_widget,
                                            WGL_CMD_LB_GET_ITEM_TEXT,
                                            WGL_PACK_2 (pt_this->ui2_hlt_idx, 1),
                                            WGL_PACK   (w2s_name_str + c_uc_w2s_strlen(w2s_name_str)));
                     MENU_LOG_ON_FAIL(i4_ret);
                 }
                 /* element number */
                 {
                     i4_ret = c_wgl_do_cmd (h_widget,
                                            WGL_CMD_LB_GET_ELEM_NUM,
                                            WGL_PACK (&ui2_elem_num),
                                            NULL);
                     MENU_LOG_ON_FAIL(i4_ret);
                 }

                switch (ui4_keycode)
                {
                    case BTN_CURSOR_UP:
                        {
                            if (pt_this->ui2_hlt_idx > 0)
                            {
                                i4_ret = c_wgl_do_cmd (h_widget,
                                                       WGL_CMD_LB_HLT_PREV_ELEM,
                                                       WGL_PACK (TRUE),
                                                       NULL);
                                MENU_CHK_FAIL(i4_ret);

                                menu_set_and_show_help_tip(MENU_TEXT(pt_this->aui2_help_txt[pt_this->ui2_hlt_idx-1]));
                            }
                            else
                            {
                                i4_ret = menu_set_focus_on_backbar(TRUE);
                                MENU_LOG_ON_FAIL(i4_ret);
                            }
                        }
                        return WGLR_OK;

                    case BTN_CURSOR_DOWN:
                        {
                            if (ui2_elem_num > (pt_this->ui2_hlt_idx+1))
                            {
                                i4_ret = c_wgl_do_cmd (h_widget,
                                                       WGL_CMD_LB_HLT_NEXT_ELEM,
                                                       WGL_PACK (TRUE),
                                                       NULL);
                                MENU_CHK_FAIL(i4_ret);

                                menu_set_and_show_help_tip(MENU_TEXT(pt_this->aui2_help_txt[pt_this->ui2_hlt_idx+1]));
                            }
                            else
                            {
                                i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                                MENU_LOG_ON_FAIL(i4_ret);
                                menu_pm_repaint();
                            }
                        }
                        return WGLR_OK;

                    case BTN_SELECT:
                        {
                            /* title of input naming page should set by input naming page */
                            {
                                UTF16_T  w2s_hlt_item [MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN] = {0};
                                i4_ret = c_wgl_do_cmd (h_widget,
                                                       WGL_CMD_LB_GET_ITEM_TEXT,
                                                       WGL_PACK_2 (pt_this->ui2_hlt_idx, 0),
                                                       WGL_PACK (w2s_hlt_item));
                                MENU_CHK_FAIL(i4_ret);

                                menu_input_ope_lst_page_set_title(w2s_hlt_item);
                                i4_ret = menu_nav_go(ui4_g_page_input, NULL);
                            }

                            MENU_CHK_FAIL(i4_ret);
                        }
                        break;

                    case BTN_RETURN:
                        {
                            i4_ret = menu_device_page_nav_go(NAV_ROOT_MENU_FROM_ANY_PAGE,NULL);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                        break;

                    default:
                        break;
                }
            }
            break;
        case WGL_MSG_KEY_UP:
            {
                UINT32 ui4_keycode = (UINT32)param1;

                if(ui4_keycode == BTN_CURSOR_UP ||
                   ui4_keycode == BTN_CURSOR_DOWN )
                {
                    /* ui2_hlt_idx */
                   {
                       i4_ret = c_wgl_do_cmd (h_widget,
                                              WGL_CMD_LB_GET_HLT_INDEX,
                                              WGL_PACK (&pt_this->ui2_hlt_idx),
                                              NULL);
                       MENU_LOG_ON_FAIL(i4_ret);
                   }
                   /* hlt text */
                   {
                       i4_ret = c_wgl_do_cmd (h_widget,
                                              WGL_CMD_LB_GET_ITEM_TEXT,
                                              WGL_PACK_2 (pt_this->ui2_hlt_idx, 0),
                                              WGL_PACK   (w2s_name_str));
                       MENU_LOG_ON_FAIL(i4_ret);

                       c_uc_w2s_strncat(w2s_name_str, L" ", c_uc_w2s_strlen(L" "));

                       i4_ret = c_wgl_do_cmd (h_widget,
                                              WGL_CMD_LB_GET_ITEM_TEXT,
                                              WGL_PACK_2 (pt_this->ui2_hlt_idx, 1),
                                              WGL_PACK   (w2s_name_str + c_uc_w2s_strlen(w2s_name_str)));
                       MENU_LOG_ON_FAIL(i4_ret);
                   }
#ifdef APP_TTS_SUPPORT
                   a_app_tts_play(w2s_name_str, 128);
#endif
               }
            }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _device_setting_page_device_list_create (VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[2];
    GL_RECT_T           t_rect;
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    c_memset(at_cols, 0, 2*sizeof(WGL_LB_COL_INIT_T));
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = MENU_DEVICE_SETTING_DEV_DISP_NAME_ALIGN;
    at_cols[0].ui2_max_text_len = MENU_DEVICE_SETTING_DEV_DISP_NAME_MAX_TEXT_LEN;
    at_cols[0].ui2_width        = MENU_DEVICE_SETTING_DEV_DISP_NAME_COL_WIDTH;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = MENU_DEVICE_SETTING_DEV_USER_NAME_ALIGN;
    at_cols[1].ui2_max_text_len = MENU_DEVICE_SETTING_DEV_USER_NAME_MAX_TEXT_LEN;
    at_cols[1].ui2_width        = MENU_DEVICE_SETTING_DEV_USER_NAME_COLUMN_WIDTH+120;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = MENU_DEVICE_SETTING_MAX_DEVICE_NUM;
    t_lb_init.ui2_elem_size     = MENU_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_DEVICE_SETTING_DEV_LIST_X,
                     MENU_DEVICE_SETTING_DEV_LIST_Y,
                     MENU_DEVICE_SETTING_DEV_LIST_W,
                     MENU_DEVICE_SETTING_DEV_LIST_H);

    i4_ret = _device_listbox_create(pt_this->h_cnt_frm,
                                    &t_rect,
                                    _menu_device_setting_device_list_proc_fct,
                                    &t_lb_init,
                                    NULL,
                                    &pt_this->h_device_list);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_setting_name_input_page_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    i4_ret = menu_pm_page_create(&t_g_menu_device_page_name_input,
                                 NULL,
                                 &pt_this->ui4_name_input_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_setting_sub_page_create(VOID)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = _device_setting_name_input_page_create();
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_setting_page_backbar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;
        MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_ROOT_MENU_FROM_ANY_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_set_focus(pt_this->h_device_list,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_set_and_show_help_tip(MENU_TEXT(pt_this->aui2_help_txt[pt_this->ui2_hlt_idx]));
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break ;

            case BTN_CURSOR_UP:
            {
                i4_ret = menu_set_focus_on_homebar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _device_setting_page_homebar_proc_fct(
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
        INT32  i4_ret = MENUR_OK;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_ROOT_MENU_FROM_ANY_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32 _device_setting_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T * pt_this = &t_g_device_setting_page_data;
    INT32                             i4_ret = MENUR_OK;

    /*c_mem_alloc*/

    c_memset(pt_this,0,sizeof(MENU_DEVICE_SETTING_PAGE_DATA_T));

    /* init */
    do
    {

        pt_this->ui4_device_setting_page_id = ui4_page_id;
        pt_this->h_last_focus = NULL_HANDLE;
        pt_this->e_device_type = MENU_DEVICE_SETTING_PAGE_DEVICE_TYPE_UNKNOW;

        /*
              pt_this->ui2_hlt_idx = 0;
              pt_this->ui1_input_count = 0;
              pt_this->t_g_menu_device_cec_dev_info;
              c_memset(pt_this->g_aui1_cec_idx_map,0,sizeof(UINT8)*CEC_DEV_LIST_MAX_NUM);
              pt_this->aui2_list_idx_2_input_idx[MENU_DEVICE_TYPE_IDX_LAST];
          */
        pt_this->ui2_help_text_num = 0;
        c_memset(pt_this->aui2_help_txt, 0, sizeof(pt_this->aui2_help_txt));

        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
        MENU_BREAK_ON_FAIL(i4_ret);

        /* h_device_list */
        i4_ret = _device_setting_page_device_list_create();
        MENU_BREAK_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,WGL_SW_HIDE_RECURSIVE);
        MENU_BREAK_ON_FAIL(i4_ret);

        /* ui4_name_input_page_id */
        i4_ret = _device_setting_sub_page_create();
        MENU_BREAK_ON_FAIL(i4_ret);

        return MENUR_OK;
    }while(0);
    /**/
    //_device_setting_page_destroy();
    return i4_ret;
}

static INT32 _device_setting_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _device_setting_page_show(UINT32 ui4_page_id)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T * pt_this = &t_g_device_setting_page_data;
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICES);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_device_setting_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_device_setting_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _device_setting_show_device_list();
    MENU_LOG_ON_FAIL(i4_ret);

    _INIT_HELP_TXT_ARRAY(pt_this->ui2_help_text_num,pt_this->aui2_help_txt);

    return i4_ret;
}

static INT32 _device_setting_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui2_help_text_num = 0;
    c_memset(pt_this->aui2_help_txt, 0, sizeof(pt_this->aui2_help_txt));

    return i4_ret;
}

static INT32 _device_setting_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    /* restore last focus */
    if (NAV_DEVICE_SETTING_PAGE_FROM_NAME_INPUT_PAGE == pt_this->e_page_nav_type)
    {
        if (pt_this->h_last_focus == pt_this->h_device_list)
        {
            i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                                  WGL_CMD_LB_HLT_ELEM,
                                  WGL_PACK(pt_this->ui2_hlt_idx),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_set_help_tip(MENU_TEXT(pt_this->aui2_list_idx_2_input_idx[pt_this->ui2_hlt_idx]));
            MENU_LOG_ON_FAIL(i4_ret);
        }

        i4_ret = c_wgl_set_focus(pt_this->h_last_focus,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_focus(pt_this->h_device_list, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _device_setting_page_lose_focus(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    HANDLE_T    h_focus = NULL_HANDLE;
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;

    /* memorize last focus */
    i4_ret = c_wgl_get_focus(&h_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus = h_focus;

    if (h_focus == pt_this->h_device_list)
    {
        i4_ret = c_wgl_do_cmd (h_focus,
                               WGL_CMD_LB_GET_HLT_INDEX,
                               WGL_PACK (&pt_this->ui2_hlt_idx),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _device_setting_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}

extern INT32 menu_device_page_device_setting_init_no_wifi_remote(VOID)
{
    t_g_menu_device_page_device_setting.pf_menu_page_create =    _device_setting_page_create;
    t_g_menu_device_page_device_setting.pf_menu_page_destroy=    _device_setting_page_destroy;
    t_g_menu_device_page_device_setting.pf_menu_page_show=       _device_setting_page_show;
    t_g_menu_device_page_device_setting.pf_menu_page_hide=       _device_setting_page_hide;
    t_g_menu_device_page_device_setting.pf_menu_page_get_focus=  _device_setting_page_get_focus;
    t_g_menu_device_page_device_setting.pf_menu_page_lose_focus= _device_setting_page_lose_focus;
    t_g_menu_device_page_device_setting.pf_menu_page_update=     _device_setting_page_update;

    return MENUR_OK;
}

INT32 menu_device_page_nav_go_no_wifi_remote(MENU_DEVICE_PAGE_NAV_TYPE_T e_page_nav_type,
                                         MENU_PAGE_HINT_T* pt_hint)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    INT32     i4_ret = MENUR_OK;

    DBG_LOG_PRINT(("\n%s,%s,%d,e_page_nav_type=%d\n", __FILE__, __FUNCTION__, __LINE__, e_page_nav_type));

    switch (e_page_nav_type)
    {
        case NAV_ROOT_MENU_FROM_ANY_PAGE:
        {
            UINT32 aui4_pages[1] = {ui4_g_menu_page_main_menu};
            i4_ret = menu_nav_go_direct(0,
                                        aui4_pages,
                                        sizeof(aui4_pages)/sizeof(aui4_pages[0]),
                                        NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_PREV_PAGE_FROM_CURRENT_PAGE:
        {
            i4_ret = menu_nav_back();
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE:
        {
            pt_this->e_page_nav_type = NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE;
            i4_ret = menu_nav_back();
            MENU_LOG_ON_FAIL(i4_ret);
            pt_this->e_page_nav_type = NAV_TYPE_LAST_ENTRY;
        }
            break;

        case NAV_INFO_STATUS_PAGE_FROM_DEVICE_SETTING_PAGE:
        {
            UINT32    aui4_pages[2] = {0};
            aui4_pages[0] = pt_this->ui4_device_status_info_page_id;
            aui4_pages[1] = pt_this->ui4_device_setting_page_id;
            i4_ret = menu_nav_go_direct(0, aui4_pages,
                                        sizeof(aui4_pages)/sizeof(aui4_pages[0]), NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_DEVICE_SETTING_PAGE_FROM_PAIR_WIFI_DEVICE_PAGE:
        {
            UINT32    aui4_pages[1] = {0};
            aui4_pages[0] = pt_this->ui4_device_setting_page_id;
            i4_ret = menu_nav_go_direct(0, aui4_pages,
                                        sizeof(aui4_pages)/sizeof(aui4_pages[0]), NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_PAIR_WIFI_DEVICE_PAGE_FROM_INFO_STATUS_PAGE:
        {
            DBG_LOG_PRINT(("<menu error> pt_this->ui4_pair_wifi_device_page_id do not creat in this page \n"));
            return MENUR_FAIL;
            i4_ret = menu_nav_back_and_go(pt_this->ui4_pair_wifi_device_page_id, NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_NAME_INPUT_PAGE_FROM_INFO_STATUS_PAGE:
        {
            i4_ret = menu_nav_go(ui4_g_menu_page_inp_naming, NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_ADD_NEW_DEVICE_PAGE_FROM_DEVICE_SETTING_PAGE:
        {
            DBG_LOG_PRINT(("<menu error> pt_this->ui4_add_new_device_page_id do not creat in this page \n"));
            return MENUR_FAIL;
            i4_ret = menu_nav_go(pt_this->ui4_add_new_device_page_id, NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case NAV_DEVICE_SETTING_PAGE_FROM_NAME_INPUT_PAGE:
        case NAV_DEVICE_SETTING_PAGE_FROM_INPUT_OPE_LST_PAGE:
        {
            pt_this->e_page_nav_type = NAV_DEVICE_SETTING_PAGE_FROM_NAME_INPUT_PAGE;
            i4_ret = menu_nav_back();
            MENU_LOG_ON_FAIL(i4_ret);
            pt_this->e_page_nav_type = NAV_TYPE_LAST_ENTRY;

        }
            break;

        default:
            return MENUR_INV_ARG;
    }

    return i4_ret;
}

INT32 menu_device_get_device_info_no_wifi_remote(MENU_DEVICE_PAGE_DEVICE_INFO_T* pt_device_info)
{
    MENU_DEVICE_SETTING_PAGE_DATA_T* pt_this = &t_g_device_setting_page_data;
    INT32     i4_ret = MENUR_OK;
    CHAR      ac_user_name[MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN+1] = {0};
    UINT32    ui4_len = 0;
    ISL_REC_T t_isl_rec;

    if (pt_this->ui2_hlt_idx < pt_this->ui1_input_count)
    {
        pt_device_info->u_device_data.t_input.ui1_input_src_idx = pt_this->aui2_list_idx_2_input_idx[pt_this->ui2_hlt_idx];
        pt_device_info->e_current_device_type = MENU_DEVICE_TYPE_INPUT;

        i4_ret = a_cfg_custom_get_inp_name(pt_device_info->u_device_data.t_input.ui1_input_src_idx,
                                            ac_user_name);
        MENU_LOG_ON_FAIL(i4_ret);

        ui4_len = MENU_DEVICE_NAME_MAX_LEN + 1;
        pt_device_info->u_device_data.t_input.pw2s_user_name =
                                    (UTF16_T*)c_mem_alloc(ui4_len*sizeof(UTF16_T));

        c_uc_ps_to_w2s(ac_user_name, pt_device_info->u_device_data.t_input.pw2s_user_name,
                       MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN);

        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        i4_ret = a_isl_get_rec_by_idx(pt_device_info->u_device_data.t_input.ui1_input_src_idx,
                                      &t_isl_rec);
        MENU_LOG_ON_FAIL(i4_ret);

        ui4_len = MENU_DEVICE_NAME_MAX_LEN + 1;
        pt_device_info->u_device_data.t_input.pw2s_disp_name =
                                  (UTF16_T*)c_mem_alloc(ui4_len*sizeof(UTF16_T));

        c_uc_w2s_strncpy(pt_device_info->u_device_data.t_input.pw2s_disp_name,
                         a_isl_get_display_name(&t_isl_rec),
                         MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
    }
#ifdef APP_CEC_MENU
    else if(pt_this->ui2_hlt_idx < (pt_this->ui1_input_count + pt_this->t_g_menu_device_cec_dev_info.dev_num))
    {
        pt_device_info->u_device_data.t_cec_dev.ui1_cec_dev_idx =
                       pt_this->ui2_hlt_idx - pt_this->ui1_input_count;

        pt_device_info->u_device_data.t_cec_dev.pw2s_cec_osd_name =
                                (UTF16_T*)c_mem_alloc((MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1)*sizeof(UTF16_T));

        c_uc_w2s_strncpy(pt_device_info->u_device_data.t_cec_dev.pw2s_cec_osd_name,
                           pt_this->t_g_menu_device_cec_dev_info.w2s_dev_osd_name[pt_device_info->u_device_data.t_cec_dev.ui1_cec_dev_idx],
                           MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);


        pt_device_info->e_current_device_type = MENU_DEVICE_TYPE_CEC_DEV;
    }

#endif

    DBG_INFO(("\n####%s,%s,%s,%s,%d,ui2_hlt_idx=%d,ui1_input=%d,device_type=%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui2_hlt_idx,
                pt_this->ui1_input_count,
                pt_device_info->e_current_device_type));

    return i4_ret;
}


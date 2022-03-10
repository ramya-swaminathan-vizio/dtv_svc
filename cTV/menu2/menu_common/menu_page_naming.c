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
 * $RCSfile: page_template.c,v $
 * $Revision: #1 $
z * $Date: 2015/05/29 $
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
#include "app_util/a_rating.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_device/menu_device.h"

#include "wdk/a_vkb.h"
#include "wdk/vkb/vkb.h"
#include "res/wdk/a_vkb_custom.h"
#include "nav/input_src/a_input_src.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define INPUT_NAMING_NEED_IPT_SOURCE            0
#define MENU_DLG_BTN_TEXT_CLR                   ((GL_COLOR_T){255, {255}, {255}, {255}})

#define NAME_INPUT_LST_VISIBLE_ELEM             (9)
#define NAME_INPUT_LST_X                        (0 * GRID_W)
#define NAME_INPUT_LST_Y                        (0 * GRID_H)
#define NAME_INPUT_LST_W                        (CONTENT_W)
#define NAME_INPUT_LST_H                        (NAME_INPUT_LST_VISIBLE_ELEM * GRID_H)

#define NAME_INPUT_COL0_W                       (110 )
#define NAME_INPUT_COL1_W                       (NAME_INPUT_LST_W - NAME_INPUT_COL0_W)

#define MAX_INP_REC                             (16)
#define MAX_LBL_REC                             NAME_INPUT_PREDEF_LBL_LAST_ENTRY

/*SPEC V3.4 change max name len 24*/
#define MAX_LBL_NAME_LEN                        APP_CFG_CUSTOM_INP_NAME_LEN
#define VKB_MAX_CHAR_NUM                        (14)
#define PLF_OPT_MODEL_REMOTE_LEN                (20)

#if INPUT_NAMING_NEED_IPT_SOURCE
#define NAME_INPUT_ITEM_IPT_SOURCE_IDX          (0)
#define NAME_INPUT_ITEM_IPT_LABEL_IDX           (1)
#define NAME_INPUT_ITEM_EDIT_BOX_IDX            (2)
#define NAME_INPUT_ITEM_VKB_IDX                 (3)
#else
#define NAME_INPUT_ITEM_IPT_SOURCE_IDX          (0)
#define NAME_INPUT_ITEM_IPT_LABEL_IDX           (0)
#define NAME_INPUT_ITEM_EDIT_BOX_IDX            (1)
#define NAME_INPUT_ITEM_VKB_IDX                 (2)
#endif


typedef enum _NAME_INPUT_PAGE_T
{
    NAME_INPUT_PAGE_NAME_INPUT,
    NAME_INPUT_PAGE_INPUT_SOURCE,
    NAME_INPUT_PAGE_INPUT_LABELS,
    NAME_INPUT_PAGE_LABELS_EDIT,
    NAME_INPUT_PAGE_LAST_ENTRY
}NAME_INPUT_PAGE_T;

typedef enum _NAME_INPUT_PREDEF_LBL_T
{
    NAME_INPUT_PREDEF_LBL_CUSTOM = 0,
    NAME_INPUT_PREDEF_LBL_BLURAY,
    NAME_INPUT_PREDEF_LBL_CABLE,
    NAME_INPUT_PREDEF_LBL_PC,
    NAME_INPUT_PREDEF_LBL_DVD,
    NAME_INPUT_PREDEF_LBL_DVR,
    NAME_INPUT_PREDEF_LBL_GAME,
    NAME_INPUT_PREDEF_LBL_SAT,
    NAME_INPUT_PREDEF_LBL_XBOX,
    NAME_INPUT_PREDEF_LBL_VCR,
    NAME_INPUT_PREDEF_LBL_LAST_ENTRY
}   NAME_INPUT_PREDEF_LBL_T;

static UINT16 aui2_g_predef_lbls[NAME_INPUT_PREDEF_LBL_LAST_ENTRY] =
{
    MLM_MENU_KEY_NAME_INPUT_LABEL_CUSTOM,
    MLM_MENU_KEY_NAME_INPUT_LABEL_BLURAY,
    MLM_MENU_KEY_NAME_INPUT_LABEL_CABLE_BOX,
    MLM_MENU_KEY_NAME_INPUT_LABEL_COMPUTER,
    MLM_MENU_KEY_NAME_INPUT_LABEL_DVD,
    MLM_MENU_KEY_NAME_INPUT_LABEL_DVR,
    MLM_MENU_KEY_NAME_INPUT_LABEL_GAME,
    MLM_MENU_KEY_NAME_INPUT_LABEL_SATELTE,
    MLM_MENU_KEY_NAME_INPUT_LABEL_XBOX,
    MLM_MENU_KEY_NAME_INPUT_LABEL_VCR

};

typedef struct _NAME_INPUT_LBLS_ITEM_T
{
    UINT16      ui2_key;
    UTF16_T     w2s_name_input_lable[APP_CFG_CUSTOM_INP_NAME_LEN+1];

}NAME_INPUT_LBLS_ITEM_T;
typedef struct _NAME_INPUT_LBLS_LANG_T
{
    UINT16      ui2_lang;
    NAME_INPUT_LBLS_ITEM_T     w2s_name_input_item_lable[NAME_INPUT_PREDEF_LBL_LAST_ENTRY];

}NAME_INPUT_LBLS_LANG_T;

static NAME_INPUT_LBLS_LANG_T menu_page_lang_lbls[MLM_MENU_NUM_LANG];

typedef struct _NAME_INPUT_T
{
    /* member */
    CHAR                            s_cust_lbl[APP_CFG_CUSTOM_INP_NAME_LEN + 1]; /*tmp input name*/
    UINT32                          ui4_page_id;
    UINT8                           ui1_src_idx;
    NAME_INPUT_PAGE_T               e_page;
    NAME_INPUT_PREDEF_LBL_T         e_predef_lbl;
    UINT8                           aui1_g_inp_src_idx[256];// = {0};
    UINT8                           ui1_g_valid_src_num;// = 0;
    MENU_DEVICE_PAGE_DEVICE_INFO_T  t_g_device_info;//= {0};
    /* status */
    BOOL            b_select_src;   /* If the source would change while select a source */
    BOOL            b_ok_btn_enable;
    /* view */
    HANDLE_T        h_cnt_frm;

    /* view top page */
    HANDLE_T        h_item_inp_src;
    HANDLE_T        h_item_inp_lbls;
    HANDLE_T        h_item_lbl_edit;

    HANDLE_T        h_page_inp_src;
    HANDLE_T        h_page_inp_lbls;
    /* view Virtual key board */
    HANDLE_T        h_page_lbl_edit;
    HANDLE_T        h_vkb_btn;
    /* acfg */
    /* icl */

    /* other*/
#if INPUT_NAMING_NEED_IPT_SOURCE
    BOOL             b_is_changing;// = FALSE;
    BOOL             b_is_show;// = FALSE;
    HANDLE_T         h_input_changing_timer;// = NULL_HANDLE;
#else
    UTF16_T          *pw2s_ipt_name;// = NULL;
#endif
} NAME_INPUT_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_naming;

static NAME_INPUT_T     t_g_name_input_view;

/* ??? */
HANDLE_T        h_g_page_naming_inp_lable = NULL_HANDLE;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern VOID menu_page_input_async_action(VOID* pv_data, SIZE_T  z_data_size);

static INT32 _name_input_item_input_source_refresh(VOID);
#if INPUT_NAMING_NEED_IPT_SOURCE
static INT32 _name_input_page_input_source_refresh(VOID);
#endif
static INT32 _name_input_item_input_labels_refresh(VOID);
#ifdef APP_CEC_MENU
static INT32 _name_input_item_cec_dev_labels_refresh(VOID);
static INT32 _name_input_page_cec_dev_labels_refresh(VOID);

static INT32 _name_input_item_cec_dev_labels_edit_box_refresh(VOID);
static INT32 _name_input_page_cec_dev_labels_edit_box_refresh(VOID);
#endif
static INT32 _name_input_item_labels_edit_box_refresh(VOID);
static INT32 _name_input_page_labels_edit_box_refresh(VOID);

static INT32 _name_input_page_input_labels_refresh(VOID);

static INT32 _name_input_show_page(NAME_INPUT_PAGE_T  e_page, BOOL b_repaint);
static INT32 _name_input_back(VOID);
static UTF16_T* _inp_src_get_help_tip_string(UINT8 ui1_isl_id );
#ifdef APP_TTS_SUPPORT
static INT32 _name_input_tts_play(HANDLE_T handle, BOOL is_lb);
#endif

static UINT8 _get_ipt_cec_dev_info_from_device_status_page(UINT8* ui1_cec_dev_idx, UTF16_T* pw2s_cec_osd_name);
static UINT8 _get_ipt_src_idx_from_device_status_page(VOID);

static INT32 _name_input_show_name_input_page(BOOL b_repaint);
#if INPUT_NAMING_NEED_IPT_SOURCE
static INT32 _name_input_show_input_source_page(BOOL b_repaint);
#endif
static INT32 _name_input_show_input_labels_page(BOOL b_repaint);
static INT32 _name_input_show_input_edit_page(BOOL b_repaint);

static INT32 _name_input_get_name_from_acfg(CHAR* s_inp_name, SIZE_T len);
static INT32 _name_input_set_name_to_acfg(CHAR* s_inp_name);
static INT32 _name_input_set_name(CHAR* s_inp_name);
static INT32 _name_input_item_update_inp_lbls(VOID);
static INT32 _name_input_cec_dev_show_vkb(VOID);
static INT32 _name_input_show_vkb(VOID);
static BOOL _is_empty_str(CHAR* s_str);
static INT8 _get_input_src_idx(VOID);

static INT32 _name_input_get_current_source_rec(ISL_REC_T*   pt_isl_rec);
static INT32 _name_input_update_e_predef_lbl(VOID);
static INT32 _name_input_get_lable_string(NAME_INPUT_PREDEF_LBL_T e_predef_idx,UTF16_T*  w2s_lable_str);

/*-----------------------------------------------------------------------------
                    function implementation
       This func is used to judge if input name is empty.
 ----------------------------------------------------------------------------*/
static INT32 _name_input_get_lable_max_number(VOID)
{
    UINT8                ui1_max_lbl = MAX_LBL_REC;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    CHAR                 s_disp_name[32] = {0};

    c_uc_w2s_to_ps(pt_this->t_g_device_info.u_device_data.t_input.pw2s_disp_name, s_disp_name, 32);

    if (0 != c_strncasecmp (s_disp_name, "COMP", 4))
    {
        ui1_max_lbl = MAX_LBL_REC - 1;
    }
    return ui1_max_lbl;
}


static INT32 _name_input_get_current_source_rec(ISL_REC_T*   pt_isl_rec)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret  = MENUR_OK;

    INT8                 i1_idx;


    return menu_get_crnt_isl(pt_isl_rec);
#if 0
    if(pt_isl_rec == NULL)
    {
        return MENUR_INV_ARG;
    }

#if INPUT_NAMING_NEED_IPT_SOURCE
    i1_idx= _get_input_src_idx();
    pt_this->ui1_src_idx = pt_this->aui1_g_inp_src_idx[i1_idx];
#else
    pt_this->ui1_src_idx = _get_ipt_src_idx_from_device_status_page();
    if (0xFF == pt_this->ui1_src_idx)
    {
        i1_idx= _get_input_src_idx();
        pt_this->ui1_src_idx = pt_this->aui1_g_inp_src_idx[i1_idx];
    }
#endif

    i4_ret = a_isl_get_rec_by_idx(pt_this->ui1_src_idx, pt_isl_rec);
    MENU_CHK_FAIL(i4_ret == ISLR_OK ? MENUR_OK : i4_ret);
    return MENUR_OK;
#endif
}

static INT32 _name_input_item_update_inp_lbls(VOID)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret  = MENUR_OK;
    UTF16_T              w2s_str[MAX_LBL_NAME_LEN + 1];
    CHAR                 s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};


    menu_list_set_idx(pt_this->h_item_inp_lbls, (UINT16)pt_this->e_predef_lbl);
#if 0
    /* get str */
    i4_ret = _name_input_get_lable_string(pt_this->e_predef_lbl,w2s_str);
    MENU_CHK_FAIL(i4_ret);

    c_uc_w2s_to_ps(w2s_str,s_inp_name, MAX_LBL_NAME_LEN);

    i4_ret = _name_input_set_name_to_acfg(s_inp_name);
    MENU_CHK_FAIL(i4_ret);
#endif
    menu_list_adjust_rect(pt_this->h_item_inp_lbls);

    if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
    {
        i4_ret = _name_input_item_cec_dev_labels_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_item_cec_dev_labels_edit_box_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_cec_dev_show_vkb();
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _name_input_item_input_labels_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_item_labels_edit_box_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_show_vkb();
        MENU_CHK_FAIL(i4_ret);
    }

    c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);

    return MENUR_OK;
}

static INT32 _name_input_get_name_from_acfg(CHAR* s_inp_name, SIZE_T len)
{
     NAME_INPUT_T        *pt_this = &t_g_name_input_view;
     INT32                i4_ret  = MENUR_OK;
     CHAR                 s_name[64] = {0};

     if(s_inp_name == NULL)
     {
         return MENUR_INV_ARG;
     }

     switch(pt_this->t_g_device_info.e_current_device_type)
     {
         case MENU_DEVICE_TYPE_CEC_DEV:
        {
            UINT8        ui1_cec_dev_idx = 0xFF;
            UTF16_T      w2s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};

            i4_ret = _get_ipt_cec_dev_info_from_device_status_page(&ui1_cec_dev_idx, w2s_cec_osd_name);
            MENU_CHK_FAIL(i4_ret);
            a_cfg_custom_get_cec_name(ui1_cec_dev_idx,s_inp_name);

            break;
        }

        default:
        {
            ISL_REC_T   t_isl_rec_crnt;
            UTF16_T     pw2s_str[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};
            c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));
            i4_ret = _name_input_get_current_source_rec(&t_isl_rec_crnt);
            MENU_CHK_FAIL(i4_ret);
            a_cfg_custom_get_device_type(t_isl_rec_crnt.ui1_id, s_inp_name);

            a_isl_get_display_name_ex(&t_isl_rec_crnt, pw2s_str, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(pw2s_str, s_name, 64);
            c_strncpy(s_inp_name, s_name, len);

            break;
        }
     }

     return MENUR_OK;
}

static INT32 _name_input_set_name_to_acfg(CHAR* s_inp_name)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret  = MENUR_OK;

    if(s_inp_name == NULL)
    {
        return MENUR_INV_ARG;
    }

    switch(pt_this->t_g_device_info.e_current_device_type)
    {
        case MENU_DEVICE_TYPE_CEC_DEV:
        {
            UINT8        ui1_cec_dev_idx = 0xFF;
            UTF16_T      w2s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};

            i4_ret = _get_ipt_cec_dev_info_from_device_status_page(&ui1_cec_dev_idx, w2s_cec_osd_name);
            MENU_CHK_FAIL(i4_ret);

            if (_is_empty_str(s_inp_name))
            {
                c_uc_w2s_to_ps(w2s_cec_osd_name,s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            }
            a_cfg_custom_set_cec_name(ui1_cec_dev_idx, s_inp_name);

            break;
        }

        default:
        {
            ISL_REC_T   t_isl_rec_crnt;
            c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));
            i4_ret = _name_input_get_current_source_rec(&t_isl_rec_crnt);
            MENU_CHK_FAIL(i4_ret);
            a_cfg_custom_set_device_type(t_isl_rec_crnt.ui1_id, s_inp_name);
            break;
        }
    }

    i4_ret = _name_input_set_name(s_inp_name);
    MENU_CHK_FAIL(i4_ret);
    DBG_LOG_PRINT(("<MENU> %s %d set name : %s\n",__FUNCTION__,__LINE__,s_inp_name));
    {
        CHAR            s_src_name[32] = {0};
        ISL_REC_T       t_isl_rec;
        INT16           ui2_hdmi_idx;

        i4_ret = menu_get_crnt_isl(&t_isl_rec);
        MENU_CHK_FAIL(i4_ret);

        if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
        {
            ui2_hdmi_idx = t_isl_rec.ui1_internal_id + 1;
            c_sprintf(s_src_name, "hdmi%d",  ui2_hdmi_idx);
            rest_event_notify("system/input/name", 1, s_src_name);
        }
        else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
            && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
            || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO
            || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))    /* COMP */
        {
            rest_event_notify("system/input/name", 1,"comp");
        }
    }

    return MENUR_OK;
}

static INT32 _name_input_set_name(CHAR* s_inp_name)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret  = MENUR_OK;

    if(s_inp_name == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(c_strcasecmp(s_inp_name,pt_this->s_cust_lbl) == 0)
    {
        /* not need to set*/
        MENU_LOG_ON_FAIL(MENUR_INV_ARG);
        return MENUR_OK;
    }

    c_strncpy(pt_this->s_cust_lbl,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
    DBG_LOG_PRINT(("<MENU> %s %d set s_cust_lbl: %s\n",__FUNCTION__,__LINE__,pt_this->s_cust_lbl));

    /* Update pt_this->e_predef_lbl */
    i4_ret = _name_input_update_e_predef_lbl();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static BOOL _name_input_is_space (UTF16_T* w2s_text)
{
    UINT8  ui1_i = 0;
    UINT16 ui2_len = 0;

    if (NULL == w2s_text)
    {
        return TRUE;
    }

    ui2_len = c_uc_w2s_strlen(w2s_text);

    for(ui1_i = 0; ui1_i< ui2_len; ui1_i++)
    {
        if(w2s_text[ui1_i] != 0x20)
        {
            break;
        }
    }

    if(ui1_i<ui2_len)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
#if INPUT_NAMING_NEED_IPT_SOURCE
VOID _timer_cb_fct(HANDLE_T pt_tm_handle, VOID* pv_tag)
{
    BOOL        b_flag = FALSE;
    menu_async_invoke(menu_page_input_async_action, &b_flag, sizeof(BOOL), TRUE);
}

static VOID _is_input_changing_set(BOOL b_flag)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    if (pt_this->b_is_show == TRUE && NAME_INPUT_PAGE_INPUT_SOURCE == pt_this->e_page)
    {
        pt_this->b_is_changing = b_flag;

        if (!b_flag)
        {
            _name_input_show_page(NAME_INPUT_PAGE_NAME_INPUT, TRUE);
        }
        else
        {
            c_timer_start(pt_this->h_input_changing_timer,
                            2000,
                            X_TIMER_FLAG_ONCE,
                            _timer_cb_fct,
                            NULL);
        }
    }
}
#else
static UINT8 _get_ipt_src_idx_from_device_status_page(VOID)
{
    UINT8                ui1_ipt_idx = 0xFF;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    if (pt_this->t_g_device_info.e_current_device_type != MENU_DEVICE_TYPE_INPUT)
    {
        return 0xFF;
    }

    ui1_ipt_idx = pt_this->t_g_device_info.u_device_data.t_input.ui1_input_src_idx;

    return ui1_ipt_idx;
}
#endif

#ifdef APP_CEC_MENU
/*FOR E-Serial*/
static UINT8 _get_ipt_cec_dev_info_from_device_status_page(UINT8* ui1_cec_dev_idx, UTF16_T* pw2s_cec_osd_name)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    do {
        if (pt_this->t_g_device_info.e_current_device_type != MENU_DEVICE_TYPE_CEC_DEV)
        {
            break;
        }
        if (a_cfg_custom_get_wifi_remote_support())
        {
            *ui1_cec_dev_idx = menu_device_cec_list_idx_to_cfg_idx(pt_this->t_g_device_info.u_device_data.t_cec_dev.ui1_cec_dev_idx);
        }
        else
        {
            *ui1_cec_dev_idx = menu_device_cec_list_idx_to_cfg_idx_no_wifi_remote(pt_this->t_g_device_info.u_device_data.t_cec_dev.ui1_cec_dev_idx);
        }
        c_uc_w2s_strncpy(pw2s_cec_osd_name, pt_this->t_g_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name, c_uc_w2s_strlen(pt_this->t_g_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name));
    } while(0);

    return MENUR_OK;
}
#endif/*APP_CEC_MENU*/

/*----------------------------------------------------------------------------
 * Name: _get_input_src_idx
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT8 _get_input_src_idx(VOID)
{
    ISL_REC_T   t_isl_rec;
    ISL_REC_T   t_isl_rec_crnt;
        INT32                   i4_ret;
    UINT8       ui1_idx;
    UINT8       ui1_rec_num;
    UINT8       ui1_av_id = 0;
    CHAR*       ps_disp_name = NULL;
    CHAR        ac_disp_name[32+1] = {0};
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;

    pt_this->ui1_g_valid_src_num = 0;

    c_memset(pt_this->aui1_g_inp_src_idx, 0xFF, sizeof(pt_this->aui1_g_inp_src_idx));
    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));

    /* Get Input Source number */
    i4_ret = a_isl_get_num_rec(&ui1_rec_num);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get the current svl record */
    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
    MENU_LOG_ON_FAIL(i4_ret);
    for(ui1_idx=0; ui1_idx < ui1_rec_num; ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

        c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec),
                        ac_disp_name,
                        32);
        ps_disp_name = c_str_toupper(ac_disp_name);

        if (0 == c_strncmp(ps_disp_name, "AV", 2)
            || 0 == c_strncmp(ps_disp_name, "COMP", 4))
        {
            ui1_av_id = t_isl_rec.ui1_id;
            continue;
        }

        pt_this->aui1_g_inp_src_idx[pt_this->ui1_g_valid_src_num] = t_isl_rec.ui1_id;
        pt_this->ui1_g_valid_src_num ++;
    }

    pt_this->aui1_g_inp_src_idx[pt_this->ui1_g_valid_src_num] = ui1_av_id;
    pt_this->ui1_g_valid_src_num ++;

    /* Iterate the ISL */
    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        i4_ret = a_isl_get_rec_by_idx(pt_this->aui1_g_inp_src_idx[ui1_idx], &t_isl_rec);
        MENU_LOG_ON_FAIL(i4_ret);

        if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
        {
            break;
        }
    }

    if (ui1_idx == ui1_rec_num)
    {
        ui1_idx = 0;
    }

    return ui1_idx;
}

#if INPUT_NAMING_NEED_IPT_SOURCE
/*----------------------------------------------------------------------------
 * Name: _prev_input_src_idx
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT16 _prev_input_src_idx(VOID)
    {
    INT32       i4_ret = 0;
    UINT8       ui1_i;
    UINT8       ui1_num_rec;
    ISL_REC_T   t_isl_rec_crnt;
    ISL_REC_T   t_isl_rec_next;
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;

    a_isl_get_num_rec(&ui1_num_rec);

    /* get the current svl record */
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));
    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);

    for(ui1_i = 0; ui1_i < ui1_num_rec; ui1_i++)
    {
        if(pt_this->aui1_g_inp_src_idx[ui1_i] == t_isl_rec_crnt.ui1_id)
        {
             break;
        }
    }

    if(ui1_i >= ui1_g_valid_src_num )
    {
        ui1_i = 0;
    }
    else if(ui1_i == 0)
    {
        ui1_i = ui1_g_valid_src_num - 1;
    }
    else
    {
        ui1_i -- ;
    }

    i4_ret = a_isl_get_rec_by_idx(pt_this->aui1_g_inp_src_idx[ui1_i], &t_isl_rec_next);
    MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, TV_WIN_ID_MAIN ));
    );

    i4_ret = a_tv_set_input_src_id(TV_WIN_ID_MAIN,t_isl_rec_next.ui1_id);
    MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    i4_ret = a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx,
                                          SVCTX_STRM_MODE_AS_LAST,
                                          &t_isl_rec_next,
                                          NULL);

    MENU_LOG_ON_FAIL(i4_ret);


    if (i4_ret != TVR_OK)
    {
        a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                           (VOID*)(UINT32)TV_WIN_ID_MAIN,
                           (VOID*)(UINT32)t_isl_rec_next.ui1_id);
    }


    return ui1_i;
}

/*----------------------------------------------------------------------------
 * Name: _next_input_src_idx
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT16 _next_input_src_idx(VOID)
            {
    INT32       i4_ret = 0;
    UINT8        ui1_i;
    UINT8        ui1_num_rec;
    ISL_REC_T    t_isl_rec_crnt;
    ISL_REC_T    t_isl_rec_next;

    a_isl_get_num_rec(&ui1_num_rec);
    /* get the current svl record */
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));
    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);

    for(ui1_i = 0; ui1_i < ui1_num_rec; ui1_i++)
    {
        if(pt_this->aui1_g_inp_src_idx[ui1_i] == t_isl_rec_crnt.ui1_id)
        {
            break;
        }
    }

    ui1_i++;

    if(ui1_i >= ui1_g_valid_src_num )
    {
        ui1_i = 0;
    }

    i4_ret = a_isl_get_rec_by_idx(pt_this->aui1_g_inp_src_idx[ui1_i], &t_isl_rec_next);
    MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, TV_WIN_ID_MAIN ));
    );

    i4_ret = a_tv_set_input_src_id(TV_WIN_ID_MAIN,
                          t_isl_rec_next.ui1_id);
    MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    i4_ret = a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx,
                                 SVCTX_STRM_MODE_AS_LAST,
                                 &t_isl_rec_next,
                                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (i4_ret != TVR_OK)
    {
        a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                           (VOID*)(UINT32)TV_WIN_ID_MAIN,
                           (VOID*)(UINT32)t_isl_rec_next.ui1_id);
    }

    return (UINT16)ui1_i;
}
#endif

static UINT8 _is_predef_lable(CHAR* s_str)
{
    UINT8            ui1_ret = 0;
    UINT8            ui1_i = 0;
    UINT8            ui1_max_lbl = MAX_LBL_REC;
    UINT16           w2s_tmp[MAX_LBL_NAME_LEN+1] = {0};

    if (NULL == s_str || c_strlen(s_str) == 0)
    {
        return ui1_ret;
    }

    ui1_max_lbl = _name_input_get_lable_max_number();
    c_uc_ps_to_w2s(s_str,w2s_tmp,MAX_LBL_NAME_LEN+1);

    for(ui1_i = 0; ui1_i <  ui1_max_lbl; ui1_i++)
    {

         if (c_uc_w2s_strcmp(w2s_tmp, MENU_TEXT(aui2_g_predef_lbls[ui1_i])) == 0)
        {
            ui1_ret = ui1_i;
            break;
        }
    }

    return ui1_ret;
}
/*----------------------------------------------------------------------------
 * Name: _is_empty_str
 *
 * Description:
 *  Check if the given string is a empty string or a string filled with space only.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _is_empty_str(CHAR* s_str)
{
    SIZE_T  z_size;
    UINT32  ui4_i;

    z_size = c_strlen(s_str);

    for(ui4_i = 0;
        ui4_i < z_size;
        ui4_i++)
    {
        if(s_str[ui4_i] >= 'a' && s_str[ui4_i] <= 'z')
        {
            return FALSE;
    }

        if(s_str[ui4_i] >= 'A' && s_str[ui4_i] <= 'Z')
        {
            return FALSE;
    }

        if(s_str[ui4_i] >= '0' && s_str[ui4_i] <= '9')
        {
            return FALSE;
        }

        if(s_str[ui4_i] == '-' ||
           s_str[ui4_i] == '_' ||
           s_str[ui4_i] == '.')
        {
            return FALSE;
        }
    }

    return TRUE;
}

static INT32 _name_input_show_vkb(VOID)
{
    INT32               i4_ret = 0;
    UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
    NAME_INPUT_T *      pt_this = &t_g_name_input_view;


    c_memset(w2s_editbox_text, 0, sizeof(w2s_editbox_text));

    // _name_input_get_lable_string(pt_this->e_predef_lbl, w2s_editbox_text);

    i4_ret = c_wgl_set_visibility(pt_this->h_item_lbl_edit, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_vkb_btn, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

     c_uc_ps_to_w2s(pt_this->s_cust_lbl, w2s_editbox_text, MAX_LBL_NAME_LEN);

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) (MAX_LBL_NAME_LEN+1),
                   NULL);

    /* set initial editbox text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_editbox_text,
                  (VOID*) 0xFF);

    /* when enter this page, if name input is empty, then disenable OK button */
    pt_this->b_ok_btn_enable = !_name_input_is_space(w2s_editbox_text);
    a_vkb_enable_ok_btn(pt_this->h_page_lbl_edit, pt_this->b_ok_btn_enable);

    a_vkb_set_visibility (pt_this->h_page_lbl_edit, TRUE);

    return MENUR_OK;
}

static INT32 _name_input_cec_dev_show_vkb(VOID)
{
    INT32               i4_ret = 0;
    UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
    UINT8               ui1_cec_dev_idx = 0xFF;
    UTF16_T             w2s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};
    NAME_INPUT_T    *   pt_this = &t_g_name_input_view;

    c_memset(w2s_editbox_text, 0, sizeof(w2s_editbox_text));

    i4_ret = c_wgl_set_visibility(pt_this->h_item_lbl_edit, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_vkb_btn, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    _get_ipt_cec_dev_info_from_device_status_page(&ui1_cec_dev_idx, w2s_cec_osd_name);

    c_uc_ps_to_w2s(pt_this->s_cust_lbl, w2s_editbox_text, MAX_LBL_NAME_LEN);

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) (MAX_LBL_NAME_LEN+1),
                   NULL);

    /* set initial editbox text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_editbox_text,
                  (VOID*) 0xFF);

    /*update OK button enable/disable state when update lb and show this page first time */
    pt_this->b_ok_btn_enable = !_name_input_is_space(w2s_editbox_text);
    a_vkb_enable_ok_btn(pt_this->h_page_lbl_edit, pt_this->b_ok_btn_enable);

    a_vkb_set_visibility (pt_this->h_page_lbl_edit, TRUE);
    return MENUR_OK;
}

static VOID _name_input_vkb_set_name(VOID)
{
    NAME_INPUT_T    *   pt_this = &t_g_name_input_view;
    UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];

    c_memset(w2s_editbox_text, 0, sizeof(w2s_editbox_text));

    a_vkb_do_cmd(pt_this->h_page_lbl_edit,
                 VKB_CMD_GET_TEXT,
                 (VOID *) w2s_editbox_text,
                 (VOID *) MAX_TV_NAME_LEN);

    c_uc_w2s_to_ps(w2s_editbox_text,pt_this->s_cust_lbl, MAX_LBL_NAME_LEN);

    if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
    {
        _name_input_item_cec_dev_labels_refresh();
        _name_input_cec_dev_show_vkb();
    }
    else
    {
        _name_input_item_input_labels_refresh();
        _name_input_show_vkb();
    }
    _name_input_item_input_source_refresh();
    c_wgl_repaint(pt_this->h_item_inp_src,NULL,TRUE);

}

static VOID _menu_naming_dialog_btn_cb_fct(UINT32 ui4_key_code)
{
    NAME_INPUT_T    *   pt_this = &t_g_name_input_view;
    a_vkb_set_focus(pt_this->h_page_lbl_edit);
    menu_pm_repaint();
}

//#ifdef APP_CUST_SPEC_TYPE
/*----------------------------------------------------------------------------
 * Name: _name_input_cust_lb_vbk_data_change_nfy
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
static INT32 _name_input_cust_lb_vbk_data_change_nfy (
    VOID*    pv_tag,
                                       UINT32   ui4_msg,
                                       VOID*    pv_param1,
                                       VOID*    pv_param2)
{
    INT32               i4_ret       = WDKR_OK;
    NAME_INPUT_T    *   pt_this = &t_g_name_input_view;

    if (ui4_msg == VKB_MSG_DLG_CANCEL)
    {
        /* Back to top page */
        _name_input_show_page(NAME_INPUT_PAGE_NAME_INPUT, TRUE);

    }
    else if (ui4_msg == VKB_MSG_DLG_FINISHED)
    {
        CHAR       s_inp_name[MAX_LBL_NAME_LEN + 1] = {0};
        /* get str */
        {
            UTF16_T    w2s_new_ch_name[MAX_LBL_NAME_LEN + 1] = {0};

            /* retrieve the new channel name. */
            a_vkb_do_cmd(pt_this->h_page_lbl_edit,
                          VKB_CMD_GET_TEXT,
                          (VOID*) w2s_new_ch_name,
                          (VOID*) (UINT32) MAX_LBL_NAME_LEN);

            /* convert to CHAR type */
            c_uc_w2s_to_ps(w2s_new_ch_name,s_inp_name,MAX_LBL_NAME_LEN);
        }

        i4_ret = _name_input_set_name_to_acfg(s_inp_name);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = _name_input_back();
        MENU_CHK_FAIL(i4_ret);
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {
        if (BTN_SELECT == *((UINT32*)pv_param1))
        {
            pt_this->b_ok_btn_enable = FALSE;
            a_vkb_enable_ok_btn(pt_this->h_page_lbl_edit, pt_this->b_ok_btn_enable);
            a_vkb_repaint(pt_this->h_page_lbl_edit);
        }
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        BOOL     b_is_cancel_button = FALSE;
        /* OK button enable */
        VKB_CONTROL_LOGIC_T *pt_vkb_ctrl = NULL;
        UTF16_T  w2s_str[MAX_LBL_NAME_LEN + 1] = {0};
        SIZE_T   z_len=0;

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_RETURN:
                _name_input_back();
                i4_ret = WDKR_OK;
                break;
            /* OK button enable */
            case BTN_KB_BACKSPACE:
            case BTN_CURSOR_LEFT:
            {
                c_wgl_do_cmd(pt_this->h_page_lbl_edit,
                             WGL_CMD_GL_GET_ATTACH_DATA,
                             (VOID *)&pt_vkb_ctrl,
                             NULL);
                if (pt_vkb_ctrl
                    && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_EDIT_BOX)
                {
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    a_vkb_do_cmd(pt_this->h_page_lbl_edit,
                                 VKB_CMD_GET_EB_CONTENT,
                                 (VOID *)w2s_str,
                                 (VOID*)VKB_MAX_CHAR_NUM);

                    z_len = c_uc_w2s_strlen(w2s_str);

                    if (z_len > 0)
                    {
                        w2s_str[z_len-1] = 0;
                        pt_this->b_ok_btn_enable = !_name_input_is_space(w2s_str);

                    }

                    a_vkb_enable_ok_btn(pt_this->h_page_lbl_edit, pt_this->b_ok_btn_enable);
                }
                break;
            }
            case BTN_CURSOR_UP:
                a_vkb_current_is_top_row(pt_this->h_page_lbl_edit,&b_is_top_bottom);
                c_wgl_do_cmd(pt_this->h_page_lbl_edit,
                             WGL_CMD_GL_GET_ATTACH_DATA,
                             (VOID *)&pt_vkb_ctrl,
                             NULL);
                if(i4_ret != WDKR_OK || NULL == pt_vkb_ctrl)
                {
                    return WDKR_OK;
                }

                if ( pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK &&
                     pt_this->b_ok_btn_enable)
                {
                    pt_vkb_ctrl->t_focus_item.e_type = (pt_vkb_ctrl->b_latin_lock && pt_vkb_ctrl->b_latin_expand) ?
                                                         VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY : VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                     a_vkb_set_focus_to_current_btn(pt_this->h_page_lbl_edit, FALSE);
                     i4_ret = WDK_NO_ACTION;
                     menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_INPUT_TEXT_KEYBAORD));

                }
                if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL &&
                    pt_this->b_ok_btn_enable)
                {
                    a_vkb_set_focus_to_ok(pt_this->h_page_lbl_edit);
                    i4_ret = WDK_NO_ACTION;
                }
                if(TRUE == b_is_top_bottom)
                {
                    c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);
                    _name_input_vkb_set_name();
                    i4_ret = WDK_NO_ACTION;
                }
                else if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL &&
                        (!pt_this->b_ok_btn_enable))
                {
                    pt_vkb_ctrl->t_focus_item.e_type = (pt_vkb_ctrl->b_latin_lock && pt_vkb_ctrl->b_latin_expand) ?
                                                        VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY : VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                    a_vkb_set_focus_to_current_btn(pt_this->h_page_lbl_edit, FALSE);
                    i4_ret = WDK_NO_ACTION;
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_INPUT_TEXT_KEYBAORD));
                }
                break;
            case BTN_CURSOR_DOWN:
                {
                    HANDLE_T h_temp = NULL_HANDLE;
                    i4_ret = a_vkb_current_is_bottom_row(pt_this->h_page_lbl_edit,&h_temp,&b_is_top_bottom);
                    c_wgl_do_cmd(pt_this->h_page_lbl_edit,
                                 WGL_CMD_GL_GET_ATTACH_DATA,
                                 (VOID *)&pt_vkb_ctrl,
                                 NULL);
                    if(i4_ret != WDKR_OK || NULL == pt_vkb_ctrl)
                    {
                        return WDKR_OK;
                    }
                    if(i4_ret != WDKR_OK)
                    {
                        return WDKR_OK;
                    }

                    if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK &&
                        pt_this->b_ok_btn_enable)
                    {
                        a_vkb_set_focus_to_cancel(pt_this->h_page_lbl_edit);
                        i4_ret = WDK_NO_ACTION;
                    }
                    if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY &&
                        pt_this->b_ok_btn_enable)
                    {
                        a_vkb_set_focus_to_ok(pt_this->h_page_lbl_edit);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                        i4_ret = WDK_NO_ACTION;
                    }

                    if(TRUE == b_is_top_bottom)
                    {
                        menu_help_tip_keytip_set_focus(h_temp, 0, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                    else if (!pt_this->b_ok_btn_enable)
                    {
                        if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)
                        {
                            a_vkb_set_focus_to_cancel(pt_this->h_page_lbl_edit);
                            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                            i4_ret = WDK_NO_ACTION;
                        }
                    }
                }
                break;
            case BTN_SELECT:
                i4_ret = a_vkb_current_is_cancel_btn(pt_this->h_page_lbl_edit,&b_is_cancel_button);
                MENU_CHK_FAIL(i4_ret == WDKR_OK ? MENUR_OK : i4_ret );

                if(TRUE == b_is_cancel_button)
                {
                    menu_nav_back() ;
                    return WDK_NO_ACTION;
                }

                c_wgl_do_cmd(pt_this->h_page_lbl_edit,
                             WGL_CMD_GL_GET_ATTACH_DATA,
                             (VOID *)&pt_vkb_ctrl,
                             NULL);

                if (pt_vkb_ctrl)
                {
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    a_vkb_do_cmd(pt_this->h_page_lbl_edit,
                                 VKB_CMD_GET_TEXT,
                                 (VOID *) w2s_str,
                                 (VOID *) MAX_TV_NAME_LEN);

                    z_len = c_uc_w2s_strlen(w2s_str);

                    pt_this->b_ok_btn_enable = !_name_input_is_space(w2s_str) ? TRUE : FALSE;

                    if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY
                        && pt_vkb_ctrl->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_DEL_KEY_IDX)
                    {
                        if (pt_this->b_ok_btn_enable && z_len > 0)
                        {
                            w2s_str[z_len-1] = 0;
                            pt_this->b_ok_btn_enable = !_name_input_is_space(w2s_str) ? TRUE : FALSE;
                        }
                    }
                    else if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                    {
                        UINT8 ui1_key_idx = 0;
                        UINT8 ui1_elem_idx = 0;

                        ui1_key_idx = pt_vkb_ctrl->ui1_cur_latin_key_idx;
                        ui1_elem_idx = pt_vkb_ctrl->t_focus_item.t_normal_key.ui1_focus_idx_col
                                        - pt_vkb_ctrl->at_keypad_latin_key[ui1_key_idx].ui1_col_offset;
                        if(z_len >= MAX_LBL_NAME_LEN)
                        {
                            menu_tos_dialog_show(MLM_MENU_KEY_NAME_INPUT,
                                                 MLM_MENU_KEY_INP_MAX_LEN_WARNING,
                                                 MLM_MENU_KEY_OK,
                                                 _menu_naming_dialog_btn_cb_fct,
                                                 TRUE);
                            return WDK_NO_ACTION;
                        }

                        if (TRUE == pt_vkb_ctrl->b_latin_lock
                            && FALSE == pt_vkb_ctrl->b_latin_expand)
                        {
                            //DO Nothing
                        }
                        else if (TRUE == pt_vkb_ctrl->b_latin_lock
                                && TRUE == pt_vkb_ctrl->b_latin_expand
                                && ui1_elem_idx >= pt_vkb_ctrl->at_keypad_latin_key[ui1_key_idx].ui1_elem_num)
                        {
                            //DO Nothing
                        }
                        else
                        {
                            pt_this->b_ok_btn_enable = TRUE;
                        }

                    }

                    a_vkb_enable_ok_btn(pt_this->h_page_lbl_edit, pt_this->b_ok_btn_enable);
                   // a_vkb_repaint(pt_this->h_page_lbl_edit);
                }
                break;
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
                c_memset(w2s_str, 0, sizeof(w2s_str));
                a_vkb_do_cmd(pt_this->h_page_lbl_edit,
                             VKB_CMD_GET_TEXT,
                             (VOID *) w2s_str,
                             (VOID *) MAX_LBL_NAME_LEN);

                z_len = c_uc_w2s_strlen(w2s_str);
                if(z_len >= MAX_LBL_NAME_LEN)
                {
                    menu_tos_dialog_show(MLM_MENU_KEY_NAME_INPUT,
                                         MLM_MENU_KEY_INP_MAX_LEN_WARNING,
                                         MLM_MENU_KEY_OK,
                                         _menu_naming_dialog_btn_cb_fct,
                                         TRUE);
                    return WDK_NO_ACTION;
                }
                break;
            default :
                break;
        }
    }

    return i4_ret;
}
//#endif



/*----------------------------------------------------------------------------
 * Name: _name_input_show_page
 *
 * Description:
 *  This function is used to show a specified page. And the widgets would show
 *  in accordance with the page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_show_input_edit_page(BOOL b_repaint)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;
    INT32              i4_ret = MENUR_OK;

    if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
    {
        i4_ret = _name_input_page_cec_dev_labels_edit_box_refresh();
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _name_input_page_labels_edit_box_refresh();
        MENU_CHK_FAIL(i4_ret);
    }

    a_vkb_set_visibility (pt_this->h_page_lbl_edit, TRUE);
    a_vkb_set_focus(pt_this->h_page_lbl_edit);
    c_wgl_set_visibility(pt_this->h_item_lbl_edit, WGL_SW_HIDE);

    menu_main_set_title(MLM_MENU_KEY_NAME_INPUT);

    if(b_repaint)
    {
        menu_pm_repaint();
    }
     pt_this->e_page = NAME_INPUT_PAGE_LABELS_EDIT;

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _name_input_show_page
 *
 * Description:
 *  This function is used to show a specified page. And the widgets would show
 *  in accordance with the page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_show_input_labels_page(BOOL b_repaint)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;
    INT32              i4_ret = MENUR_OK;

    c_wgl_set_visibility(pt_this->h_page_inp_lbls, WGL_SW_NORMAL);

    if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
    {
        i4_ret = _name_input_page_cec_dev_labels_refresh();
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
       i4_ret = _name_input_page_input_labels_refresh();
       MENU_CHK_FAIL(i4_ret);
    }

    c_wgl_set_focus(pt_this->h_page_inp_lbls, WGL_NO_AUTO_REPAINT);
#if INPUT_NAMING_NEED_IPT_SOURCE
    menu_main_set_title(MLM_MENU_KEY_INPUT_LABELS);
#else
    menu_main_set_title_text(pt_this->pw2s_ipt_name);
#endif
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_INPUT_LABELS));

  //  if(b_repaint)
 //   {
  //      menu_pm_repaint();
  //  }

    pt_this->e_page = NAME_INPUT_PAGE_INPUT_LABELS;

    return MENUR_OK;

}
#if INPUT_NAMING_NEED_IPT_SOURCE
/*----------------------------------------------------------------------------
 * Name: _name_input_show_page
 *
 * Description:
 *  This function is used to show a specified page. And the widgets would show
 *  in accordance with the page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_show_input_source_page(BOOL b_repaint)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;
    INT32              i4_ret = MENUR_OK;

    {
        HANDLE_T           h_last_shadow_item = NULL_HANDLE;
        GL_RECT_T       t_rect={0};

        /*Adjust last shadow position*/
        t_rect.i4_top = GRID_H * NAME_INPUT_PREDEF_LBL_LAST_ENTRY + FRAME_Y + CONTENT_Y;
        t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;

        menu_pm_get_last_shadow_item(&h_last_shadow_item);
        i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_CHK_FAIL( i4_ret == WGLR_OK ? MENUR_OK : i4_ret );
        i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
        MENU_CHK_FAIL( i4_ret == WGLR_OK ? MENUR_OK : i4_ret );
    }

    i4_ret = _name_input_page_input_source_refresh();
    MENU_CHK_FAIL(i4_ret);

    i4_ret =c_wgl_set_visibility(pt_this->h_page_inp_src, WGL_SW_NORMAL);
    MENU_CHK_FAIL( i4_ret == WGLR_OK ? MENUR_OK : i4_ret );
    i4_ret = c_wgl_set_focus(pt_this->h_page_inp_src, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL( i4_ret == WGLR_OK ? MENUR_OK : i4_ret );

    i4_ret =menu_main_set_title(MLM_MENU_KEY_INPUT_SOURCE_SEL);
    MENU_CHK_FAIL(i4_ret);

    if(b_repaint)
    {
       i4_ret =  menu_pm_repaint();
       MENU_CHK_FAIL(i4_ret);
    }

    pt_this->e_page = NAME_INPUT_PAGE_INPUT_SOURCE;

    return MENUR_OK;
}
#endif /* INPUT_NAMING_NEED_IPT_SOURCE */
/*----------------------------------------------------------------------------
 * Name: _name_input_show_page
 *
 * Description:
 *  This function is used to show a specified page. And the widgets would show
 *  in accordance with the page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_show_name_input_page(BOOL b_repaint)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;
    INT32              i4_ret = MENUR_OK;

    NAME_INPUT_PAGE_T  e_page_prev = pt_this->e_page;

    {
        GL_RECT_T          t_rect_tmp = {0};
        HANDLE_T           h_last_shadow_item = NULL_HANDLE;

        i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);

        MENU_CHK_FAIL(i4_ret);

        t_rect_tmp.i4_top = 800;
        t_rect_tmp.i4_bottom = t_rect_tmp.i4_top + MENU_ITEM_V_HEIGHT;
        t_rect_tmp.i4_left = CONTENT_X;
        t_rect_tmp.i4_right = CONTENT_X + CONTENT_H;
        i4_ret=c_wgl_move(h_last_shadow_item, &t_rect_tmp, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* set visibility */
    {
#if INPUT_NAMING_NEED_IPT_SOURCE
        c_wgl_set_visibility(pt_this->h_item_inp_src, WGL_SW_NORMAL);
        i4_ret = menu_list_adjust_rect(pt_this->h_item_inp_src);
        MENU_CHK_FAIL(i4_ret);
#endif

        c_wgl_set_visibility(pt_this->h_item_inp_lbls, WGL_SW_NORMAL);

        //c_wgl_set_visibility(pt_this->h_vkb_btn, WGL_SW_NORMAL);
        //i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
        //MENU_LOG_ON_FAIL(i4_ret);

    }

    /* title */
    i4_ret = menu_main_set_title(MLM_MENU_KEY_NAME_INPUT);
    MENU_CHK_FAIL(i4_ret);

    /* body */
    if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
    {
        i4_ret = _name_input_item_cec_dev_labels_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_item_cec_dev_labels_edit_box_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_cec_dev_show_vkb();
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _name_input_item_input_labels_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_item_labels_edit_box_refresh();
        MENU_CHK_FAIL(i4_ret);
        i4_ret = _name_input_show_vkb();
        MENU_CHK_FAIL(i4_ret);
    }

    _name_input_item_input_source_refresh();

    /* set focus */
    {
        if(e_page_prev == NAME_INPUT_PAGE_INPUT_LABELS)
        {
            c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);
        }
        else if(e_page_prev == NAME_INPUT_PAGE_LABELS_EDIT)
        {
            c_wgl_set_focus(pt_this->h_item_lbl_edit, WGL_SYNC_AUTO_REPAINT);
        }
        else
        {
#if INPUT_NAMING_NEED_IPT_SOURCE
            c_wgl_set_focus(pt_this->h_item_inp_src, WGL_SYNC_AUTO_REPAINT);
#else
            c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);
#endif
        }
    }

    if(b_repaint)
    {
        menu_pm_repaint();
    }

    pt_this->e_page = NAME_INPUT_PAGE_NAME_INPUT;

    return MENUR_OK;

}



/*----------------------------------------------------------------------------
 * Name: _name_input_show_page
 *
 * Description:
 *  This function is used to show a specified page. And the widgets would show
 *  in accordance with the page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_show_page(
    NAME_INPUT_PAGE_T  e_page,
    BOOL b_repaint)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;
    INT32              i4_ret = MENUR_OK;

    /* Set all the UI invisible */
    {
#if INPUT_NAMING_NEED_IPT_SOURCE
        c_wgl_set_visibility(pt_this->h_item_inp_src, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->h_page_inp_src, WGL_SW_HIDE);
#endif
        c_wgl_set_visibility(pt_this->h_item_inp_lbls, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->h_item_lbl_edit, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->h_page_inp_lbls, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->h_vkb_btn, WGL_SW_HIDE);
        a_vkb_set_visibility (pt_this->h_page_lbl_edit, FALSE);
    }
    switch(e_page)
    {
        case NAME_INPUT_PAGE_NAME_INPUT:
        {
           i4_ret = _name_input_show_name_input_page(FALSE);
           MENU_CHK_FAIL(i4_ret);
        }
        break;
#if INPUT_NAMING_NEED_IPT_SOURCE
        case NAME_INPUT_PAGE_INPUT_SOURCE:
        {
            i4_ret = _name_input_show_input_source_page(FALSE);
            MENU_CHK_FAIL(i4_ret);
        }
        break;
#endif
        case NAME_INPUT_PAGE_INPUT_LABELS:
        {
            i4_ret = _name_input_show_input_labels_page(FALSE);
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        case NAME_INPUT_PAGE_LABELS_EDIT:
        {
            i4_ret = _name_input_show_input_edit_page(FALSE);
            MENU_CHK_FAIL(i4_ret);
        }
        break;
        default:
        {
            MENU_CHK_FAIL(MENUR_INV_STATE);
        }
    }

    if(b_repaint)
    {
        menu_pm_repaint();
    }

    pt_this->e_page = e_page;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_back
 *
 * Description:
 *  This function is used to show a specified page. And the widgets would show
 *  in accordance with the page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_back(VOID)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;
    if(pt_this->e_page == NAME_INPUT_PAGE_INPUT_SOURCE ||
       pt_this->e_page == NAME_INPUT_PAGE_INPUT_LABELS ||
       pt_this->e_page == NAME_INPUT_PAGE_LABELS_EDIT)
    {
        return _name_input_show_page(NAME_INPUT_PAGE_NAME_INPUT, TRUE);
    }
    else
    {
        return menu_nav_back () ;
    }
}

/*----------------------------------------------------------------------------
 * Name: _name_input_homebar_proc_fct
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
static INT32 _name_input_homebar_proc_fct (
    HANDLE_T                    h_widget,
                               UINT32      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
{
        UINT32  ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_CURSOR_DOWN :
            menu_set_focus_on_backbar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            return WGLR_OK;
        case BTN_EXIT:
        case BTN_RETURN:
            _name_input_back();
            return WGLR_OK;
        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _name_input_backbar_proc_fct
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
static INT32 _name_input_backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    NAME_INPUT_T    *  pt_this = &t_g_name_input_view;

    if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_keycode = (UINT32)pv_param1;
        INT32              i4_ret = MENUR_OK;

        switch (ui4_keycode)
        {
        case BTN_SELECT :
        case BTN_EXIT:
        case BTN_RETURN:
            _name_input_back();
            return WGLR_OK;
        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar(TRUE);
            return WGLR_OK;
        case BTN_CURSOR_DOWN:
            if(pt_this->e_page == NAME_INPUT_PAGE_NAME_INPUT)
            {
            #if INPUT_NAMING_NEED_IPT_SOURCE
                c_wgl_set_focus(pt_this->h_item_inp_src, WGL_SYNC_AUTO_REPAINT);
            #else
                c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);
            #endif
            }
            else if(pt_this->e_page == NAME_INPUT_PAGE_INPUT_SOURCE)
            {
                c_wgl_set_focus(pt_this->h_page_inp_src, WGL_SYNC_AUTO_REPAINT);

                if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
                {
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                }
                else
                {
                    menu_set_and_show_help_tip(_inp_src_get_help_tip_string(pt_this->aui1_g_inp_src_idx[0]));
                }
            }
            else if(pt_this->e_page == NAME_INPUT_PAGE_INPUT_LABELS)
            {
                i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(0),
                          WGL_PACK(0));
                MENU_LOG_ON_FAIL(i4_ret);
                c_wgl_set_focus(pt_this->h_page_inp_lbls, WGL_SYNC_AUTO_REPAINT);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_INPUT_LABELS));
            }
            else if(pt_this->e_page == NAME_INPUT_PAGE_LABELS_EDIT)
            {
                a_vkb_set_focus(pt_this->h_page_lbl_edit);
            }
            return WGLR_OK;
        default:
            break;
        }

    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

#if INPUT_NAMING_NEED_IPT_SOURCE
/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_source_proc_fct
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
static INT32 _name_input_page_input_source_proc_fct(
    HANDLE_T    h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret = MENUR_OK;
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        if (pt_this->b_is_changing)
        {
            return MENUR_OK;
        }

        UINT32      ui4_key_code = (UINT32)pv_param1;
        UINT16      ui2_idx = 0;

        c_wgl_do_cmd(h_widget,
                     WGL_CMD_LB_GET_HLT_INDEX,
                     WGL_PACK(&ui2_idx),
                     NULL);


        switch (ui4_key_code)
        {
        case BTN_CURSOR_UP :
            {
                if(ui2_idx == 0)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);

                    menu_set_and_show_help_tip(_inp_src_get_help_tip_string(pt_this->aui1_g_inp_src_idx[ui2_idx-1]));
                }
            }
            break;
        case BTN_CURSOR_DOWN :
            {
                UINT8       ui1_num_rec;
                i4_ret = a_isl_get_num_rec(&ui1_num_rec);
                MENU_CHK_FAIL(i4_ret);

                if(ui2_idx == ui1_num_rec - 1)
                {
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_NEXT_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);

                    menu_set_and_show_help_tip(_inp_src_get_help_tip_string(pt_this->aui1_g_inp_src_idx[ui2_idx + 1]));
                }
            }
            break;
        case BTN_SELECT :
        {
            UINT16      ui2_idx = 0;
            ISL_REC_T     t_isl_rec;
            INT32       i4_ret = 0;
            UINT8       ui1_old_src_idx = pt_this->ui1_src_idx;
            BOOL        b_flag = FALSE;

            menu_list_get_idx(h_widget,&ui2_idx);
            if (ui2_idx <= NAME_INPUT_PREDEF_LBL_LAST_ENTRY)
            {
                pt_this->ui1_src_idx = (UINT8)pt_this->aui1_g_inp_src_idx[ui2_idx];

                i4_ret = a_isl_get_rec_by_idx((UINT8)pt_this->aui1_g_inp_src_idx[ui2_idx], &t_isl_rec);

                MENU_LOG_ON_FAIL(i4_ret);
            }

            if(pt_this->b_select_src)
            {
                ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
                    DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
                );

                i4_ret = a_tv_change_input_src_by_rec(menu_get_crnt_svctx(),
                                      SVCTX_STRM_MODE_AS_LAST,
                                      &t_isl_rec,
                                      NULL);

                MENU_LOG_ON_FAIL(i4_ret);


                if (i4_ret != TVR_OK)
                {
                    a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                                       (VOID*)(UINT32)TV_WIN_ID_MAIN,
                                       (VOID*)(UINT32)t_isl_rec.ui1_id);
                }

                b_flag = (ui1_old_src_idx != pt_this->ui1_src_idx) ? TRUE : FALSE;
                _is_input_changing_set(b_flag);

            }
            else
            {
                _name_input_show_page(NAME_INPUT_PAGE_NAME_INPUT, TRUE);
            }

            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_RETURN:
            {
                i4_ret = _name_input_back();
                MENU_CHK_FAIL(i4_ret);
            }
            break;
        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
#endif

#ifdef APP_TTS_SUPPORT
static INT32 _name_input_tts_play(HANDLE_T handle, BOOL is_lb)
{
    UINT16 ui2_hlt_idx;
    UTF16_T  w2s[MAX_LBL_NAME_LEN] = {0};
    UTF16_T *p_w2s = NULL;
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;

    MENU_CHK_FAIL(c_wgl_do_cmd (handle,
                               WGL_CMD_LB_GET_HLT_INDEX,
                               WGL_PACK (&ui2_hlt_idx),
                               NULL));

    if (ui2_hlt_idx ==  0)
    {
        if (c_strlen(pt_this->s_cust_lbl) == 0)
        {
            MENU_CHK_FAIL(c_wgl_do_cmd (handle,
                                        WGL_CMD_LB_GET_ITEM_TEXT,
                                        WGL_PACK_2(ui2_hlt_idx, (is_lb == TRUE)? 0: 1),
                                        (VOID *)w2s));
        }
        else
        {
            c_uc_ps_to_w2s(pt_this->s_cust_lbl, w2s, MAX_LBL_NAME_LEN);
        }
        p_w2s = w2s;
    }
    else
    {
        p_w2s = mlm_menu_get_text(0, aui2_g_predef_lbls[ui2_hlt_idx]);
    }

    if (NULL != p_w2s)
    {
        return a_app_tts_play(p_w2s, c_uc_w2s_strlen(p_w2s));
    }

    return MENUR_FAIL;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_labels_proc_fct
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
static INT32 _name_input_page_input_labels_btn_select(UINT16   ui2_idx)
{
    INT32            i4_ret = MENUR_OK;
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;
    CHAR             s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
#if 0

    /*get hl text*/
    {
        if (ui2_idx == 0)
        {
            UTF16_T     w2s_item_txt[MAX_LBL_NAME_LEN+1];

            c_memset(w2s_item_txt, 0, sizeof(w2s_item_txt));
            c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                           WGL_CMD_LB_GET_ITEM_TEXT,
                           WGL_PACK_2(ui2_idx, 0),
                           w2s_item_txt);

            c_uc_w2s_to_ps(w2s_item_txt, s_inp_name, MAX_LBL_NAME_LEN);
        }
        else
        {
            c_uc_w2s_to_ps(MENU_TEXT(aui2_g_predef_lbls[ui2_idx]), s_inp_name, MAX_LBL_NAME_LEN);
        }
    }


    i4_ret = _name_input_set_name_to_acfg(s_inp_name);
    MENU_CHK_FAIL(i4_ret);
#endif
    // _name_input_item_update_inp_lbls();

    i4_ret = _name_input_show_page(NAME_INPUT_PAGE_NAME_INPUT, TRUE);
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_labels_proc_fct
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
static INT32 _name_input_page_input_labels_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    INT32            i4_ret = MENUR_OK;
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32      ui4_key_code = (UINT32)pv_param1;

        UINT16      ui2_hlt_idx  = 0;
        UINT16      ui2_elem_num = 0;

        c_wgl_do_cmd(h_widget,
                     WGL_CMD_LB_GET_HLT_INDEX,
                     WGL_PACK(&ui2_hlt_idx),
                     NULL);

        c_wgl_do_cmd(h_widget,
                     WGL_CMD_LB_GET_ELEM_NUM,
                     WGL_PACK(&ui2_elem_num),
                     NULL);

        switch (ui4_key_code)
        {
            case BTN_CURSOR_UP :
                {
                    if(ui2_hlt_idx == 0)
                    {
                        i4_ret = menu_set_focus_on_backbar(TRUE);
                        MENU_CHK_FAIL(i4_ret);
                        i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                        MENU_CHK_FAIL(i4_ret);
                        menu_pm_repaint();
                    }
                }
                break;
            case BTN_CURSOR_DOWN :
                {
                    if(ui2_hlt_idx == ui2_elem_num - 1/*(UINT16)(NAME_INPUT_PREDEF_LBL_LAST_ENTRY - 1)*/)
                    {
                        i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                        MENU_CHK_FAIL(i4_ret);
                        menu_pm_repaint();
                    }
                }
                break;
            case BTN_SELECT :
                {
                    UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
                    pt_this->e_predef_lbl = ui2_hlt_idx;
                    _name_input_get_lable_string(pt_this->e_predef_lbl, w2s_editbox_text);
                    c_uc_w2s_to_ps(w2s_editbox_text, pt_this->s_cust_lbl, MAX_LBL_NAME_LEN);
                    i4_ret = _name_input_page_input_labels_btn_select(ui2_hlt_idx);
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_EXIT:
            case BTN_RETURN:
                {
                    i4_ret = _name_input_back();
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            default :
                break ;
        }
    }
    else if (WGL_MSG_KEY_UP== ui4_msg)
    {
#ifdef APP_TTS_SUPPORT
        i4_ret = _name_input_tts_play(h_widget, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
#endif
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
#if INPUT_NAMING_NEED_IPT_SOURCE
/*----------------------------------------------------------------------------
 * Name: _name_input_item_inp_src_proc_fct
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
static INT32 _name_input_item_inp_src_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
            {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if(ui4_key_code == BTN_CURSOR_LEFT)
                {
                    _prev_input_src_idx();
                }
                else
                {
                    _next_input_src_idx();
                }

                _name_input_item_input_source_refresh();
                /* Refresh the label and custom label UI */
                if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
                {
                    _name_input_item_cec_dev_labels_refresh();
                    _name_input_item_cec_dev_labels_edit_box_refresh();
                    _name_input_cec_dev_show_vkb();
                }
                else
                {
                    _name_input_item_input_labels_refresh();
                    _name_input_item_labels_edit_box_refresh();
                    _name_input_show_vkb();
                }
                menu_list_adjust_rect(pt_this->h_item_inp_src);
                menu_list_adjust_rect(pt_this->h_item_inp_lbls);

                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
                return MENUR_OK;
            }
        case BTN_SELECT :
            _name_input_show_page(NAME_INPUT_PAGE_INPUT_SOURCE, TRUE);
            return WGLR_OK;

        case BTN_CURSOR_UP :
            menu_set_focus_on_backbar (TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            return WGLR_OK;

        case BTN_CURSOR_DOWN :
            c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);
            return WGLR_OK;
        case BTN_EXIT:
            case BTN_RETURN:
            _name_input_back();
            return WGLR_OK;
        default :
                break;
        }
    }
    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP));
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
#endif

static INT32 _name_input_item_frm_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    NAME_INPUT_T    *pt_this = &t_g_name_input_view;
    UTF16_T     w2s_str[MAX_LBL_NAME_LEN + 1];

    if (WGL_MSG_NOTIFY == ui4_msg)
    {
        WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)pv_param2;

        if (WGL_NC_EB_CHANGED == pt_nfy_data->ui4_nc_code)
        {
            c_memset(w2s_str, 0, sizeof(w2s_str));

            a_vkb_do_cmd(pt_this->h_page_lbl_edit,
                         VKB_CMD_GET_EB_CONTENT,
                         (VOID *)w2s_str,
                         (VOID*)(MAX_LBL_NAME_LEN+1));

            w2s_str[MAX_LBL_NAME_LEN] = 0;

            pt_this->b_ok_btn_enable = !_name_input_is_space(w2s_str) ? TRUE : FALSE;
            a_vkb_enable_ok_btn(pt_this->h_page_lbl_edit, pt_this->b_ok_btn_enable);

            //menu_pm_repaint();

            return WGLR_OK;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_inp_lbls_proc_fct
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
static INT32 _name_input_item_inp_lbls_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret = MENUR_OK;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT16     ui2_elem_num = MAX_LBL_REC;

        ui2_elem_num = _name_input_get_lable_max_number();

        switch ((UINT32)pv_param1)
        {
        case BTN_CURSOR_LEFT:
            {

                UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
                if(pt_this->e_predef_lbl == (NAME_INPUT_PREDEF_LBL_T)0 /*|| pt_this->e_predef_lbl == (NAME_INPUT_PREDEF_LBL_T)1*/)
                {
                    pt_this->e_predef_lbl = (NAME_INPUT_PREDEF_LBL_T)(ui2_elem_num - 1);
                }
                else
                {
                    pt_this->e_predef_lbl--;
                }
                _name_input_get_lable_string(pt_this->e_predef_lbl, w2s_editbox_text);
                c_uc_w2s_to_ps(w2s_editbox_text, pt_this->s_cust_lbl, MAX_LBL_NAME_LEN);
                i4_ret = _name_input_item_update_inp_lbls();
                MENU_CHK_FAIL(i4_ret);
                /* do not change value by children handle */
                return MENUR_OK;
            }
            break;
        case BTN_CURSOR_RIGHT:
            {
                UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
                if(pt_this->e_predef_lbl == (NAME_INPUT_PREDEF_LBL_T)(ui2_elem_num - 1))
                {
                    pt_this->e_predef_lbl = (NAME_INPUT_PREDEF_LBL_T)0;
                }
                else
                {
                    pt_this->e_predef_lbl++;
                }

                _name_input_get_lable_string(pt_this->e_predef_lbl, w2s_editbox_text);
                c_uc_w2s_to_ps(w2s_editbox_text, pt_this->s_cust_lbl, MAX_LBL_NAME_LEN);

                i4_ret = _name_input_item_update_inp_lbls();
                MENU_CHK_FAIL(i4_ret);

                /* do not change value by children handle */
                return MENUR_OK;
            }
            break;
        case BTN_SELECT :
            {
               i4_ret = _name_input_show_page(NAME_INPUT_PAGE_INPUT_LABELS, TRUE);
               MENU_CHK_FAIL(i4_ret);
            }
            break;
        case BTN_CURSOR_UP :
#if INPUT_NAMING_NEED_IPT_SOURCE
            c_wgl_set_focus(pt_this->h_item_inp_src, WGL_SYNC_AUTO_REPAINT);
#else
            menu_set_focus_on_backbar (TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
#endif
            return WGLR_OK;

        case BTN_CURSOR_DOWN :
        {
            c_wgl_repaint(pt_this->h_item_inp_lbls,NULL,TRUE);
            a_vkb_set_focus_ex(pt_this->h_page_lbl_edit);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_INPUT_TEXT_KEYBAORD));
        }
            return WGLR_OK;
        case BTN_EXIT:
        case BTN_RETURN:
            _name_input_back();
            return WGLR_OK;
        default :
            break ;
        }
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        UINT32    ui4_key_code = (UINT32)pv_param1;
        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            case BTN_SELECT :
            case BTN_CURSOR_UP :
            case BTN_CURSOR_DOWN :
                {
#ifdef APP_TTS_SUPPORT
                    _name_input_tts_play(h_widget, TRUE);
#endif
                }
                break;
            default :
                break ;
        }
    }
    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_INPUT_LABELS));
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_lbl_edit_proc_fct
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
static INT32 _name_input_item_lbl_edit_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    ISL_REC_T   t_isl_rec_crnt;
    CHAR        s_cust_lbl[APP_CFG_CUSTOM_INP_NAME_LEN+1];
    UTF16_T     w2s_str[MAX_LBL_NAME_LEN + 1];
    INT32       i4_ret;
    UINT32      ui4_len;
    CHAR        s_src_name[CONN_SRC_NAME_MAX_STRLEN+1] = {0};

    UINT8       ui1_cec_dev_idx = 0xFF;
    UTF16_T     w2s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};
    CHAR        s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

//#ifdef APP_CUST_SPEC_TYPE
//    CHAR        s_str[PLF_OPT_MODEL_REMOTE_LEN] = {0};
//    UINT8       ui1_len = PLF_OPT_MODEL_REMOTE_LEN;
//#endif
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)pv_param1)
        {
            case BTN_KB_CURSOR_LEFT:
            case BTN_KB_BACKSPACE:
            case BTN_CURSOR_LEFT:
            {
                c_memset(w2s_str, 0, sizeof(UTF16_T)*(MAX_LBL_NAME_LEN+1));

                i4_ret = c_wgl_do_cmd (h_widget,
                                        WGL_CMD_EB_GET_TEXT,
                                        WGL_PACK (w2s_str),
                                        WGL_PACK (MAX_LBL_NAME_LEN));

                ui4_len = c_strlen(pt_this->s_cust_lbl);

                if (ui4_len > 0)
                {
                    UINT32  ui4_len_after;
                    /* delete last character */
                    s_cust_lbl[ui4_len -1] = '\0';

                    c_uc_ps_to_w2s(s_cust_lbl, w2s_str, MAX_LBL_NAME_LEN);
                    i4_ret = c_wgl_do_cmd(h_widget,
                                          WGL_CMD_EB_SET_TEXT,
                                          WGL_PACK(w2s_str),
                                          WGL_PACK(0xFFFF));
                    MENU_LOG_ON_FAIL(i4_ret);
                    ui4_len_after = c_uc_w2s_strlen(w2s_str);
                    i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_EB_SET_CURSOR_POS,
                                           WGL_PACK (ui4_len_after+1),
                                           NULL);
                    menu_pm_repaint();
                }
                return MENUR_OK;
            }
            case BTN_SELECT :
            {
                /* get str */
                {
                    CHAR                     s_cust_lbl[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

                    c_memset(w2s_str, 0, sizeof(UTF16_T)*(MAX_LBL_NAME_LEN+1));

                    i4_ret = c_wgl_do_cmd (h_widget,
                                            WGL_CMD_EB_GET_TEXT,
                                            WGL_PACK (w2s_str),
                                            WGL_PACK (MAX_LBL_NAME_LEN));

                    c_uc_w2s_to_ps(w2s_str, s_cust_lbl, MAX_LBL_NAME_LEN);
                }

                i4_ret = _name_input_set_name(s_cust_lbl);
                MENU_CHK_FAIL(i4_ret);

                i4_ret = _name_input_show_page(NAME_INPUT_PAGE_LABELS_EDIT, TRUE);
                MENU_CHK_FAIL(i4_ret);

                return WGLR_OK;

            }
            case BTN_CURSOR_UP :
                {
                    c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);

                    if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
                    {
                        _name_input_item_cec_dev_labels_refresh();
                    }
                    else
                    {
                        _name_input_item_input_labels_refresh();
                    }

                    return WGLR_OK;
                }
                break;
            case BTN_CURSOR_DOWN :
                {
                    c_wgl_set_focus(pt_this->h_vkb_btn, WGL_SYNC_AUTO_REPAINT);
                    return WGLR_OK;
                }
                break;
            case BTN_EXIT:
            case BTN_RETURN:
                {
                    _name_input_back();
                    return WGLR_OK;
                }
                break;
            default:
                {
                    c_memset(w2s_str, 0, sizeof(UTF16_T)*(MAX_LBL_NAME_LEN+1));
                    c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_GET_TEXT,
                                WGL_PACK (w2s_str),
                                WGL_PACK (MAX_LBL_NAME_LEN));
                    ui4_len = c_uc_w2s_strlen(w2s_str);
                    DBG_INFO(("\n[naming]----------------%d\n", ui4_len));
                    if (ui4_len >= (MAX_LBL_NAME_LEN - 1))
                    {
                        DBG_INFO(("\n[naming]----------------more characters were input\n"));
                        return WGLR_OK;
                    }
                }
                break;
        }
    }
    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_ENABLE_CURSOR_HT,
                                WGL_PACK (TRUE),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _name_input_get_current_source_rec(&t_isl_rec_crnt);
        MENU_CHK_FAIL(i4_ret);

        /* Get the custom label */
        a_cfg_custom_get_inp_name(t_isl_rec_crnt.ui1_id,
                          s_cust_lbl);

        if (_is_empty_str(s_cust_lbl) == TRUE )
        {
            c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec_crnt),
                        s_cust_lbl,
                        MAX_LBL_NAME_LEN);
        }
        ui4_len = c_strlen(s_cust_lbl);
        i4_ret = c_wgl_do_cmd (h_widget,
                  WGL_CMD_EB_SET_CURSOR_POS,
                  WGL_PACK (ui4_len+1),
                  NULL);
        menu_pm_repaint();
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_CUSTOM_LABELS));
    }
    else if(WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        INT32                   i4_ret;

        if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
        {
            i4_ret = _get_ipt_cec_dev_info_from_device_status_page(&ui1_cec_dev_idx, w2s_cec_osd_name);
            c_uc_w2s_to_ps(w2s_cec_osd_name, s_cec_osd_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            DBG_INFO(("\n####%s(%d)s_cec_osd_name=%s,ui1_cec_dev_idx=%d,i4_ret=%d\n",__FUNCTION__,__LINE__,s_cec_osd_name,ui1_cec_dev_idx,i4_ret));
            c_memset(w2s_str, 0, sizeof(UTF16_T)*(MAX_LBL_NAME_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_str),
                                    WGL_PACK (MAX_LBL_NAME_LEN));
            MENU_LOG_ON_FAIL(i4_ret);

            c_memset(pt_this->s_cust_lbl, 0, sizeof(CHAR)*(MAX_LBL_NAME_LEN+1));
            if (i4_ret != MENUR_OK)
            {
                /* Get the custom label */
                a_cfg_custom_get_cec_name(ui1_cec_dev_idx,pt_this->s_cust_lbl);
            }
            else
            {
                c_uc_w2s_to_ps(w2s_str, pt_this->s_cust_lbl, MAX_LBL_NAME_LEN);
            }

            ui4_len = c_strlen(pt_this->s_cust_lbl);
            pt_this->s_cust_lbl[ui4_len] = '\0';

            c_uc_w2s_to_ps(w2s_cec_osd_name, s_src_name, MAX_LBL_NAME_LEN);

            if(0 == c_strcmp(s_src_name, pt_this->s_cust_lbl))
            {
                pt_this->s_cust_lbl[0] = '\0';
            }

            a_cfg_custom_set_cec_name(ui1_cec_dev_idx, pt_this->s_cust_lbl);

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_ENABLE_CURSOR_HT,
                                    WGL_PACK (FALSE),
                                    NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            _name_input_item_cec_dev_labels_refresh();
            _name_input_item_cec_dev_labels_edit_box_refresh();

        }
        else
        {
            c_memset(w2s_str, 0, sizeof(UTF16_T)*(MAX_LBL_NAME_LEN+1));
            c_memset(pt_this->s_cust_lbl, 0, sizeof(CHAR)*(MAX_LBL_NAME_LEN+1));

            i4_ret = _name_input_get_current_source_rec(&t_isl_rec_crnt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_str),
                                    WGL_PACK (MAX_LBL_NAME_LEN));
            MENU_LOG_ON_FAIL(i4_ret);


            if (i4_ret != MENUR_OK)
            {
                a_cfg_custom_get_inp_name(t_isl_rec_crnt.ui1_id, pt_this->s_cust_lbl);
            }
            else
            {
                c_uc_w2s_to_ps(w2s_str, pt_this->s_cust_lbl, MAX_LBL_NAME_LEN);
            }

            ui4_len = c_strlen(pt_this->s_cust_lbl);
            pt_this->s_cust_lbl[ui4_len] = '\0';

            c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec_crnt), s_src_name, MAX_LBL_NAME_LEN);

            if(0 == c_strcmp(s_src_name, pt_this->s_cust_lbl))
            {
                pt_this->s_cust_lbl[0] = '\0';
            }

//            a_cfg_custom_set_inp_name(t_isl_rec_crnt.ui1_id, pt_this->s_cust_lbl);

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_ENABLE_CURSOR_HT,
                                    WGL_PACK (FALSE),
                                    NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            _name_input_item_input_labels_refresh();
            _name_input_item_labels_edit_box_refresh();
        }

        _name_input_item_input_source_refresh();

    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _name_input_top_lbl_create
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
static INT32 _name_input_item_labels_edit_box_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
)
{
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;
    UTF16_T             w2s_cursor =(UTF16_T) 0x005F; /* underline */

    /* create editbox */
    ui4_style = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
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

    /* Set Insets */
    t_inset.i4_left     = 8;
    t_inset.i4_right    = 8;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Cnt Insets */
    t_inset.i4_left     = 2;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_EDIT_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_EDIT_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_EB_ENABLE_CURSOR_HT,
                            WGL_PACK (TRUE),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                             WGL_CMD_EB_SET_CURSOR_CHAR,
                             (VOID*)(&w2s_cursor),/* underline */
                             NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                             WGL_CMD_GL_SET_COLOR,
                             WGL_PACK(WGL_CLR_EB_CURSOR),   /* text color highlighted by cursor */
                             WGL_PACK(& t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set always highlight: this will display cursor even if focus not on editbox. */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK (WGL_EB_ALWAYS_HT | WGL_EB_CHAR_SUPPORT | WGL_EB_EA_AUTO_EDITING | WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK (WGL_EB_ALWAYS_HT | WGL_EB_CHAR_SUPPORT | WGL_EB_EA_AUTO_EDITING | WGL_EB_KEEP_CURSOR_POS));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_menu_img_item_edit;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_menu_img_item_edit;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_menu_img_item_edit;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)MAX_LBL_NAME_LEN),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),  /*Attr mask*/
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING)); /*Attr value*/
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /* Set Border images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_input_source_refresh
 *
 * Description:
 *  Refresh the current available input source.
 *  And disable some input source because of pip/pop
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_item_input_source_refresh(VOID)
{
#if INPUT_NAMING_NEED_IPT_SOURCE
    UINT8       ui1_idx;
    ISL_REC_T   t_isl_rec;

    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32               i4_ret = MENUR_OK;

    menu_list_chg_lang(pt_this->h_item_inp_src,
                        MLM_MENU_KEY_INPUT_SOURCE, 0,0);

    i4_ret = _name_input_get_current_source_rec(&t_isl_rec);
    MENU_CHK_FAIL(i4_ret);

    menu_list_set_text(pt_this->h_item_inp_src, ui1_idx, a_isl_get_display_name(&t_isl_rec));

    menu_list_set_idx(pt_this->h_item_inp_src,ui1_idx);
    menu_list_adjust_rect(pt_this->h_item_inp_src);
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_input_labels_refresh
 *
 * Description:
 *  Refresh the label list in the top page.
 *  It also update the current label index and custom label string.
 *  The function is invoked when
 *  1. Once enter the naming page.
 *  2. The source change.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_update_e_predef_lbl(VOID)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    UINT8               ui1_predef_idx = 0xFF;

    ui1_predef_idx = _is_predef_lable(pt_this->s_cust_lbl);

    pt_this->e_predef_lbl = (NAME_INPUT_PREDEF_LBL_T)ui1_predef_idx;

    return MENUR_OK;
}

static INT32 _name_input_get_lable_string(NAME_INPUT_PREDEF_LBL_T e_predef_idx,UTF16_T*  w2s_lable_str)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32               i4_ret = MENUR_OK;

    ISL_REC_T           t_isl_rec_crnt;

    if(w2s_lable_str == NULL || e_predef_idx >= NAME_INPUT_PREDEF_LBL_LAST_ENTRY)
    {
        return MENUR_INV_ARG;
    }

    if (e_predef_idx == NAME_INPUT_PREDEF_LBL_CUSTOM)
    {

        if(pt_this->t_g_device_info.e_current_device_type == MENU_DEVICE_TYPE_CEC_DEV)
        {
            UINT8        ui1_cec_dev_idx = 0xFF;
            UTF16_T      w2s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};

            i4_ret = _get_ipt_cec_dev_info_from_device_status_page(&ui1_cec_dev_idx, w2s_cec_osd_name);
            MENU_CHK_FAIL(i4_ret);
            c_uc_w2s_strcpy(w2s_lable_str, w2s_cec_osd_name);
        }
        else
        {
            i4_ret = _name_input_get_current_source_rec(&t_isl_rec_crnt);
            MENU_CHK_FAIL(i4_ret);

            c_uc_w2s_strcpy(w2s_lable_str, a_isl_get_display_name(&t_isl_rec_crnt));
        }
    }
    else
    {
         c_uc_w2s_strncpy(w2s_lable_str, MENU_TEXT(aui2_g_predef_lbls[e_predef_idx]), MAX_LBL_NAME_LEN);
    }

    return MENUR_OK;
}

static INT32 _name_input_item_labels_refresh_ex(VOID)
{
    INT32                i4_ret = MENUR_OK;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    UINT8                ui1_i;
    UINT8                ui1_max_lbl = MAX_LBL_REC;

    ui1_max_lbl = _name_input_get_lable_max_number();

    {
        UTF16_T     w2s_lbl_name[MAX_LBL_NAME_LEN+1];
        for(ui1_i = 0; ui1_i < ui1_max_lbl; ui1_i++)
        {
            c_memset(w2s_lbl_name, 0, sizeof(w2s_lbl_name));

            i4_ret = _name_input_get_lable_string((NAME_INPUT_PREDEF_LBL_T )ui1_i, w2s_lbl_name);
            MENU_CHK_FAIL(i4_ret);
            menu_list_set_text(pt_this->h_item_inp_lbls,ui1_i,w2s_lbl_name);
        }
    }
    menu_list_set_idx(pt_this->h_item_inp_lbls,(UINT16)pt_this->e_predef_lbl);

    menu_list_adjust_rect(pt_this->h_item_inp_lbls);

    return MENUR_OK;
}

static INT32 _name_input_item_input_labels_refresh(VOID)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32               i4_ret = MENUR_OK;

    /* set title */
    {
        ISL_REC_T   t_isl_rec_crnt;

        /* Get current source rec */
        i4_ret = _name_input_get_current_source_rec(&t_isl_rec_crnt);
        MENU_CHK_FAIL(i4_ret);

        /* Get the custom lable */
        pt_this->pw2s_ipt_name = a_isl_get_display_name(&t_isl_rec_crnt);
        menu_list_set_title_text(pt_this->h_item_inp_lbls, pt_this->pw2s_ipt_name);
    }

    i4_ret = _name_input_item_labels_refresh_ex();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_cec_dev_labels_refresh
 *
 * Description:
 *  Refresh the label list in the top page.
 *  It also update the current label index and custom label string.
 *  The function is invoked when
 *  1. Once enter the naming page.
 *  2. The source change.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_item_cec_dev_labels_refresh(VOID)
{
    INT32                i4_ret = MENUR_OK;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    /* set title */
    {
        UINT8       ui1_cec_dev_idx = 0xFF;
        UTF16_T     w2s_cec_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]={0};

        i4_ret = _get_ipt_cec_dev_info_from_device_status_page(&ui1_cec_dev_idx, w2s_cec_osd_name);
        MENU_CHK_FAIL(i4_ret);
        menu_list_set_title_text(pt_this->h_item_inp_lbls, w2s_cec_osd_name);
    }

    i4_ret = _name_input_item_labels_refresh_ex();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_labels_edit_box_refresh
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
static INT32 _name_input_item_labels_edit_box_refresh(VOID)
{

    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret  = MENUR_OK;
    UTF16_T              w2s_str[MAX_LBL_NAME_LEN + 1];

    c_memset(w2s_str, 0, sizeof(w2s_str));
    // _name_input_get_lable_string(pt_this->e_predef_lbl, w2s_str);

    c_wgl_set_visibility(pt_this->h_item_lbl_edit, WGL_SW_NORMAL);

    c_uc_ps_to_w2s(pt_this->s_cust_lbl,w2s_str, MAX_LBL_NAME_LEN);

    i4_ret = c_wgl_do_cmd(pt_this->h_item_lbl_edit,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(0xFFFF));
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret );

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_item_cec_dev_labels_edit_box_refresh
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
static INT32 _name_input_item_cec_dev_labels_edit_box_refresh(VOID)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    INT32               i4_ret;
    UTF16_T             w2s_str[MAX_LBL_NAME_LEN + 1];

    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_wgl_set_visibility(pt_this->h_item_lbl_edit, WGL_SW_NORMAL);

    i4_ret = _name_input_get_lable_string(pt_this->e_predef_lbl,w2s_str);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_item_lbl_edit,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(0xFFFF));
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret );
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_page_name_input_create
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
static INT32 _name_input_page_name_input_create(VOID)
{
    INT32   i4_ret;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

#if INPUT_NAMING_NEED_IPT_SOURCE
    UINT8   ui1_num_rec;

    a_isl_get_num_rec(&ui1_num_rec);

    /* Input source selection */
    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              NAME_INPUT_ITEM_IPT_SOURCE_IDX,
                              ui1_num_rec,
                              _name_input_item_inp_src_proc_fct,
                              &pt_this->h_item_inp_src);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_list_chg_lang(pt_this->h_item_inp_src,
                                MLM_MENU_KEY_INPUT_SOURCE,
                                0,
                                0);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    /* Input label selection */
    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              NAME_INPUT_ITEM_IPT_LABEL_IDX,
                              MAX_LBL_REC,
                              _name_input_item_inp_lbls_proc_fct,
                              &pt_this->h_item_inp_lbls);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_list_chg_lang(pt_this->h_item_inp_lbls,
                                MLM_MENU_KEY_INPUT_LABELS,
                                0,
                                0);
    MENU_LOG_ON_FAIL(i4_ret);

    h_g_page_naming_inp_lable = pt_this->h_item_inp_lbls;

    /* Label Edit box */
    i4_ret = _name_input_item_labels_edit_box_create(pt_this->h_cnt_frm,
                                              NAME_INPUT_ITEM_EDIT_BOX_IDX,
                                              _name_input_item_lbl_edit_proc_fct,
                                              &pt_this->h_item_lbl_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_item_lbl_edit,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)MAX_LBL_NAME_LEN),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#if INPUT_NAMING_NEED_IPT_SOURCE
/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_source_create
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
static INT32 _name_input_page_input_source_create(VOID)
{
    INT32                   i4_ret;
    WGL_LB_INIT_T           t_lb_init;
    WGL_LB_COL_INIT_T       at_cols[2];
    GL_RECT_T               t_rect;
    UINT8                   ui1_rec_num = 0;
    WGL_INSET_T             t_inset;
    WGL_LB_IMG_ELEM_SET_T   t_elem_img;
    WGL_FONT_INFO_T         t_fnt_info;
    UINT32                  ui4_col = 0;

    a_isl_get_num_rec(&ui1_rec_num);

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[0].ui2_max_text_len = 16;
    at_cols[0].ui2_width        = NAME_INPUT_COL0_W;

    /* channel name or starting time */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = 16;
    at_cols[1].ui2_width        = NAME_INPUT_COL1_W;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_MULTI_SEL |
                                  WGL_STL_GL_NO_IMG_UI;

    t_lb_init.ui2_max_elem_num  = ui1_rec_num;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      NAME_INPUT_LST_X,
                      NAME_INPUT_LST_Y,
                      NAME_INPUT_LST_W,
                      NAME_INPUT_LST_H);

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                &t_rect,
                                _name_input_page_input_source_proc_fct,
                                &t_lb_init,
                                NULL,
                                &pt_this->h_page_inp_src);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set col Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    for(; ui4_col < t_lb_init.ui1_col_num; ui4_col++)
    {
        if(at_cols[ui4_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            if(ui4_col == 0)
            {
                t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
            }
            else
            {
                t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
            }
            i4_ret = c_wgl_do_cmd (pt_this->h_page_inp_src,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK(ui4_col),
                                   WGL_PACK(&t_fnt_info));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set element insert */
    t_inset.i4_left   = 10;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 8;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (pt_this->h_page_inp_src,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_elem_img.h_normal             = NULL_HANDLE;
    t_elem_img.h_disable            = NULL_HANDLE;
    t_elem_img.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_elem_img.h_highlight_unfocus  = NULL_HANDLE;
    t_elem_img.h_pushed             = NULL_HANDLE;
    t_elem_img.h_selected           = NULL_HANDLE;
    t_elem_img.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (pt_this->h_page_inp_src,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_elem_img),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_labels_create
 *
 * Description:
 *  Create the listbox of label selection.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_page_input_labels_create(VOID)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 16;
    at_cols[0].ui2_width        = NAME_INPUT_LST_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_MULTI_SEL |
                                  WGL_STL_GL_NO_IMG_UI;

    t_lb_init.ui2_max_elem_num  = MAX_LBL_REC;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      NAME_INPUT_LST_X,
                      NAME_INPUT_LST_Y,
                      NAME_INPUT_LST_W,
                      NAME_INPUT_LST_H);

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                &t_rect,
                                _name_input_page_input_labels_proc_fct,
                                & t_lb_init,
                                NULL,
                                &pt_this->h_page_inp_lbls);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    return MENUR_OK;
}

#if INPUT_NAMING_NEED_IPT_SOURCE
/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_source_refresh
 *
 * Description:
 *  Refresh the input page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_page_input_source_refresh(VOID)
{
    INT32       i4_ret;
    UINT8       ui1_i;
    UINT8       ui1_num_rec;
    ISL_REC_T   t_isl_rec;
    UTF16_T     w2s_temp[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    WGL_LB_ITEM_T   at_items[2];
    CHAR        s_cust_lbl[APP_CFG_CUSTOM_INP_NAME_LEN+1];
    CHAR        s_source_lbl[APP_CFG_CUSTOM_INP_NAME_LEN+1];

    UINT8       ui2_hlt_idx = 0;
    UINT8       ui2_hlt_pos = 0;

    a_isl_get_num_rec(&ui1_num_rec);

    /* clear the list */
    c_wgl_do_cmd(pt_this->h_page_inp_src,
                 WGL_CMD_LB_DEL_ALL,
                 NULL,
                 NULL);

    /* Iterate all the input sources */
    for(ui1_i=0; ui1_i<ui1_g_valid_src_num; ui1_i++)
    {
        /* Get the record */
        a_isl_get_rec_by_idx(pt_this->aui1_g_inp_src_idx[ui1_i], &t_isl_rec);

        /* Label name */
        c_memset(w2s_temp, 0, sizeof(w2s_temp));
        c_memset(s_cust_lbl, 0, sizeof(s_cust_lbl));
        c_memset(s_source_lbl, 0, sizeof(s_source_lbl));

        i4_ret = a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, s_cust_lbl);

        /*If the custom name is the same as source name then don't display*/
        c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec),
                       s_source_lbl,
                       MAX_LBL_NAME_LEN);

        if(c_strcmp(s_cust_lbl, s_source_lbl) == 0)
        {
            w2s_temp[0] = 0;
        }
        c_uc_ps_to_w2s(s_cust_lbl, w2s_temp, MAX_LBL_NAME_LEN);

        if (c_strncmp(s_source_lbl, "AV", c_strlen("AV")) == 0)
        {
            at_items[0].data.pw2s_text  = L" AV";
        }
        else
        {
            at_items[0].data.pw2s_text  = a_isl_get_display_name(&t_isl_rec);
        }

        /* Prepare the item data */
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        //at_items[0].data.pw2s_text  = a_isl_get_display_name(&t_isl_rec);
        at_items[1].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text  = w2s_temp;

        /* append item */
        i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_src,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Focus the current one */
    ui2_hlt_idx = (UINT16)_get_input_src_idx();
    ui2_hlt_pos = ui2_hlt_idx >= NAME_INPUT_LST_VISIBLE_ELEM ?
                  (UINT16)(NAME_INPUT_LST_VISIBLE_ELEM - 1) :
                  ui2_hlt_idx;

    i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_src,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_hlt_idx),
                          WGL_PACK(ui2_hlt_pos));
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(_inp_src_get_help_tip_string(pt_this->aui1_g_inp_src_idx[ui2_hlt_idx]));

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _name_input_page_input_labels_refresh
 *
 * Description:
 *  Refresh the label selection page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_page_input_labels_refresh(VOID)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret;
    UINT8                ui1_i;
    UINT8                ui1_max_lbl = MAX_LBL_REC;
    WGL_LB_ITEM_T        at_items[1];
    UINT8                ui2_hlt_idx = 0xFF;
    UTF16_T              w2s_temp[MAX_LBL_NAME_LEN + 1] = {0};

    /* clear the list */
    c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                 WGL_CMD_LB_DEL_ALL,
                 NULL,
                 NULL);

    ui1_max_lbl = _name_input_get_lable_max_number();
    ui2_hlt_idx = pt_this->e_predef_lbl;


    /* Iterate all the input sources */
    for(ui1_i = 0; ui1_i <  ui1_max_lbl; ui1_i++)
    {
        c_memset(w2s_temp, 0, sizeof(w2s_temp));

        i4_ret = _name_input_get_lable_string((NAME_INPUT_PREDEF_LBL_T)ui1_i,w2s_temp);
        MENU_CHK_FAIL(i4_ret);

        /* Prepare the item data */
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = w2s_temp;

        /* append item */
        i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret );
    }

    /* Focus the current one */
    i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_hlt_idx),
                          WGL_PACK(ui2_hlt_idx));
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret );

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _name_input_page_cec_dev_labels_refresh
 *
 * Description:
 *  Refresh the label selection page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_page_cec_dev_labels_refresh(VOID)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret;
    UINT8                ui1_max_lbl = MAX_LBL_REC;
    UINT8                ui2_hlt_idx = 0;
    UTF16_T              w2s_temp[MAX_LBL_NAME_LEN + 1] = {0};
    WGL_LB_ITEM_T        at_items[1];
    UINT8                ui1_i;

    /* clear the list */
    c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                 WGL_CMD_LB_DEL_ALL,
                 NULL,
                 NULL);

    ui1_max_lbl = _name_input_get_lable_max_number();
    ui2_hlt_idx = pt_this->e_predef_lbl;

    /* Iterate all the input sources */
    for(ui1_i = 0; ui1_i <  ui1_max_lbl; ui1_i++)
    {
        c_memset(w2s_temp, 0, sizeof(w2s_temp));
        i4_ret = _name_input_get_lable_string((NAME_INPUT_PREDEF_LBL_T)ui1_i,w2s_temp);
        MENU_CHK_FAIL(i4_ret);

        /* Prepare the item data */
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = w2s_temp;

        /* append item */
        i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret );
    }

    /* Focus the current one */
    i4_ret = c_wgl_do_cmd(pt_this->h_page_inp_lbls,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_hlt_idx),
                          WGL_PACK(ui2_hlt_idx));
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret );

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_page_labels_edit_box_refresh
 *
 * Description:
 *  Update the cust lbl name to the virtual keyboard UI.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_page_labels_edit_box_refresh(VOID)
{
    UTF16_T*            pw2s_ch_name = L"";
    UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
    UTF16_T*            pw2s_ok     = MENU_TEXT(MLM_MENU_KEY_OK);
    UTF16_T*            pw2s_CANCEL = MENU_TEXT(MLM_MENU_KEY_CNCL);
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;


    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) (MAX_LBL_NAME_LEN+1),
                   NULL);

    /* set the label text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_LABEL_TEXT,
                  (VOID*) pw2s_ch_name,
                  (VOID*) 0xFF);

    /* set button OK text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_OK_BTN_TEXT,
                  (VOID*) pw2s_ok,
                  (VOID*) 0xFF);

    /* set button Cancel text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_CANCEL_BTN_TEXT,
                  (VOID*) pw2s_CANCEL,
                  (VOID*) 0xFF);

    /* set initial editbox text */
    c_memset(w2s_editbox_text, 0, sizeof(w2s_editbox_text));

    c_uc_ps_to_w2s(pt_this->s_cust_lbl,w2s_editbox_text,MAX_LBL_NAME_LEN);

    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_editbox_text,
                  (VOID*) 0xFF);

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_page_cec_dev_labels_edit_box_refresh
 *
 * Description:
 *  Update the cust lbl name to the virtual keyboard UI.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _name_input_page_cec_dev_labels_edit_box_refresh(VOID)
{
    UTF16_T*            pw2s_ch_name = L"";
    UTF16_T             w2s_editbox_text[MAX_LBL_NAME_LEN + 1];
    UTF16_T*            pw2s_ok     = MENU_TEXT(MLM_MENU_KEY_OK);
    UTF16_T*            pw2s_CANCEL = MENU_TEXT(MLM_MENU_KEY_CNCL);
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) (MAX_LBL_NAME_LEN+1),
                   NULL);

    /* set the label text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_LABEL_TEXT,
                  (VOID*) pw2s_ch_name,
                  (VOID*) 0xFF);

    /* set button OK text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_OK_BTN_TEXT,
                  (VOID*) pw2s_ok,
                  (VOID*) 0xFF);

    /* set button Cancel text */
    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_CANCEL_BTN_TEXT,
                  (VOID*) pw2s_CANCEL,
                  (VOID*) 0xFF);

    c_memset(w2s_editbox_text, 0, sizeof(w2s_editbox_text));

    c_uc_ps_to_w2s(pt_this->s_cust_lbl,w2s_editbox_text,MAX_LBL_NAME_LEN);

    a_vkb_do_cmd (pt_this->h_page_lbl_edit,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_editbox_text,
                  (VOID*) 0xFF);

    return WDKR_OK;
}

//#ifdef APP_CUST_SPEC_TYPE
/*----------------------------------------------------------------------------
 * Name: _input_naming_vkb_btn_proc_fct
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
static INT32 _input_naming_vkb_btn_proc_fct(HANDLE_T   h_widget,
                                            UINT32     ui4_msg,
                                            VOID*      pv_param1,
                                            VOID*      pv_param2)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;
        switch (ui4_key_code)
        {
            case BTN_SELECT:
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                _name_input_show_page(NAME_INPUT_PAGE_LABELS_EDIT, TRUE);
                return WGLR_OK;
            case BTN_CURSOR_UP :
                c_wgl_set_focus(pt_this->h_item_lbl_edit, WGL_SYNC_AUTO_REPAINT);
                return WGLR_OK;
            case BTN_CURSOR_DOWN :
                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                menu_pm_repaint();
                return WGLR_OK;
            case BTN_RETURN:
                MENU_LOG_ON_FAIL(_name_input_back());
                return WGLR_OK;
            default:
                break;
        }
    }
    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NAME_INPUT_HELP_SHOW_KB));
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _input_naming_vkb_btn_create
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
static INT32 _input_naming_vkb_btn_create(VOID)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     MENU_ITEM_V_HEIGHT*3,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT
                     );

    i4_ret = c_wgl_create_widget(pt_this->h_cnt_frm,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _input_naming_vkb_btn_proc_fct,
                                255,
                                NULL,
                                NULL,
                                &pt_this->h_vkb_btn);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left   = 10; //paulfan,101210 follow BRCM
    t_inset.i4_right  = 10; //paulfan,101210 follow BRCM
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_BTN_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(& t_img_info));
    MENU_CHK_FAIL(i4_ret);

    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_disable = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_highlight = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_highlight_inactive = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_push = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_push_unhighlight = MENU_DLG_BTN_TEXT_CLR;
    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(& t_color_info));
    MENU_CHK_FAIL(i4_ret);

    c_strcpy(t_font_info.a_c_font_name, menu_font_name());
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER), //paulfan,101210 follow BRCM
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NW_SHOW_KB)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_NW_SHOW_KB))));
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}
//#endif

/*----------------------------------------------------------------------------
 *
 *  Page Lifecycle callback functions
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32                i4_ret       = MENUR_FAIL;
    HANDLE_T             h_cnt_frm;
//#ifdef APP_CUST_SPEC_TYPE
    VKB_INIT_T           t_init_data;
    CHAR                 s_str[PLF_OPT_MODEL_REMOTE_LEN] = {0};
//    UINT8                      ui1_len = PLF_OPT_MODEL_REMOTE_LEN;
//#endif
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    c_memset(pt_this, 0, sizeof(NAME_INPUT_T));

    do
    {
        /* h_cnt_frm ui4_page_id*/
        {
            i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
            MENU_BREAK_ON_FAIL(i4_ret);

            pt_this->ui4_page_id = ui4_page_id;
            pt_this->h_cnt_frm   = h_cnt_frm;
        }

        /* top page */
        i4_ret = _name_input_page_name_input_create();
        MENU_BREAK_ON_FAIL(i4_ret);

#if INPUT_NAMING_NEED_IPT_SOURCE
        /*h_page_inp_src*/
        i4_ret= _name_input_page_input_source_create();
        MENU_BREAK_ON_FAIL(i4_ret);
#endif
        /* h_page_inp_lbls */
        i4_ret = _name_input_page_input_labels_create();
        MENU_BREAK_ON_FAIL(i4_ret);

        /*h_vkb_btn*/
        {
            //a_cfg_custom_plf_opt_get_remote_name(s_str,ui1_len);
            c_strcpy(s_str, "XRV1TV");
            if( (c_strcmp(s_str,"XRV1TV")==0)||(c_strcmp(s_str,"XRV1D3")==0))
            {

                i4_ret = _input_naming_vkb_btn_create();
                MENU_BREAK_ON_FAIL(i4_ret);
            }
        }

        /* h_page_lbl_edit */
        {
            t_init_data.h_parent            = h_cnt_frm;
            t_init_data.ui4_style_mask      = VKB_STYLE_MASK_MENU|VKB_STYLE_MASK_WITH_EB_CLEAR;;
            t_init_data.t_gui_rc.i4_left    = FRAME_LEFT_RIGHT_INTV;
#if INPUT_NAMING_NEED_IPT_SOURCE
            t_init_data.t_gui_rc.i4_top     = MENU_ITEM_V_HEIGHT;
#else
            t_init_data.t_gui_rc.i4_top     = CONTENT_Y;
#endif
            t_init_data.pf_data_change_fct  = _name_input_cust_lb_vbk_data_change_nfy;
            t_init_data.pv_tag              = NULL;
            i4_ret = a_vkb_create(&t_init_data,&(pt_this->h_page_lbl_edit));
            MENU_BREAK_ON_FAIL(i4_ret);

            c_wgl_set_widget_proc(pt_this->h_page_lbl_edit,_name_input_item_frm_proc_fct);
            menu_page_set_data(ui4_page_id, &t_g_name_input_view);

            pt_this->b_select_src = TRUE;

            c_wgl_set_visibility(pt_this->h_page_lbl_edit, WGL_SW_HIDE);
        }

#if INPUT_NAMING_NEED_IPT_SOURCE
        /* h_input_changing_timer */
        {
            MENU_LOG_ON_FAIL(c_timer_create(&pt_this->h_input_changing_timer));
        }
#endif

        {

            UINT16  ui2_i = 0;
            UINT16  ui2_j = 0;
            UINT16  ui2_num = 0;
            ui2_num = sizeof(aui2_g_predef_lbls)/sizeof(aui2_g_predef_lbls[0]);

            for (ui2_i = MLM_MENU_LANG_ENG; ui2_i < MLM_MENU_NUM_LANG; ui2_i++)
            {
                for (ui2_j = 0; ui2_j < ui2_num; ui2_j++)
                {
                    menu_page_lang_lbls[ui2_i].ui2_lang = ui2_i;
                    menu_page_lang_lbls[ui2_i].w2s_name_input_item_lable[ui2_j].ui2_key = aui2_g_predef_lbls[ui2_j];
                    c_uc_w2s_strncpy(menu_page_lang_lbls[ui2_i].w2s_name_input_item_lable[ui2_j].w2s_name_input_lable,MLM_MENU_TEXT(ui2_i,aui2_g_predef_lbls[ui2_j]),APP_CFG_CUSTOM_INP_NAME_LEN+1);


                }


            }


        }
    } while(0);

    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    a_vkb_destroy( pt_this->h_page_lbl_edit );

#if INPUT_NAMING_NEED_IPT_SOURCE
    if (NULL_HANDLE != pt_this->h_input_changing_timer)
    {
        MENU_LOG_ON_FAIL(c_timer_delete(pt_this->h_input_changing_timer));
    }
#endif

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    menu_tos_dialog_hide(FALSE);
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;
    INT32                i4_ret = MENUR_OK;

    pt_this->e_page = NAME_INPUT_PAGE_NAME_INPUT;

    /* set callback function bars */
    menu_set_backbar_proc (_name_input_backbar_proc_fct) ;

    menu_set_homebar_proc(_name_input_homebar_proc_fct);

    /* get t_g_device_info */
    {
        if (a_cfg_custom_get_wifi_remote_support())
        {
            menu_device_get_device_info(&pt_this->t_g_device_info);
        }
        else
        {
            menu_device_get_device_info_no_wifi_remote(&pt_this->t_g_device_info);
        }
    }
    /* get s_cust_lbl*/
    {
       CHAR     s_cust_lbl[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
       c_memset(pt_this->s_cust_lbl, 0, sizeof(CHAR)*(MAX_LBL_NAME_LEN+1));

       i4_ret = _name_input_get_name_from_acfg(s_cust_lbl, sizeof(s_cust_lbl));
       MENU_CHK_FAIL(i4_ret);

       i4_ret = _name_input_set_name(s_cust_lbl);
       MENU_CHK_FAIL(i4_ret);
    }


    _name_input_show_page(NAME_INPUT_PAGE_NAME_INPUT, FALSE);

    menu_help_tip_keytip_show(FALSE);

#if INPUT_NAMING_NEED_IPT_SOURCE
    pt_this->b_is_show = TRUE;
    c_wgl_set_focus(pt_this->h_item_inp_src, WGL_SYNC_AUTO_REPAINT);
#else
    c_wgl_set_focus(pt_this->h_item_inp_lbls, WGL_SYNC_AUTO_REPAINT);
#endif

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
#if INPUT_NAMING_NEED_IPT_SOURCE
    _is_input_changing_set(FALSE);
    pt_this->b_is_show = FALSE;
#endif

    /* Clear callback function of backbar */
    menu_set_backbar_proc(NULL);

    /* Clear callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    INT32   i4_ret = MENUR_OK;
    NAME_INPUT_T        *pt_this = &t_g_name_input_view;

    i4_ret = c_wgl_do_cmd(pt_this->h_vkb_btn,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NW_SHOW_KB)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_NW_SHOW_KB))));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _inp_src_get_help_tip_string
 * Description: This API is use to get the help tip string by hlt index.
 * Input: arguments
 * Output: arguments
 * Returns:
 *---------------------------------------------------------------------------*/
UTF16_T* _inp_src_get_help_tip_string(UINT8 ui1_isl_id )
{
#if 1
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
                    ui2_inp_tip_id = (t_isl_rec.ui1_iid_count <= 3 &&
                                      MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI_3 == ui2_inp_tip_id) ?
                                        MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI_SIDE : ui2_inp_tip_id;
                }
                break;

        case DEV_AVC_VGA:
                ui2_inp_tip_id = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_RGB;
                break;

        default:
                break;
    }

    return MENU_TEXT(ui2_inp_tip_id);
#else
    return MENU_TEXT(MLM_MENU_KEY_EMPTY);
#endif
}

/*-----------------------------------------------------------------------------
                        External functions
-----------------------------------------------------------------------------*/
extern INT32 menu_common_create_page_naming(UINT32 *pui4_page_id)
{

    return menu_pm_page_create(&t_g_menu_common_page_naming,
                               (VOID*)&t_g_name_input_view,
                               pui4_page_id);
}

extern INT32 menu_common_page_naming_init(VOID)
{
    t_g_menu_common_page_naming.pf_menu_page_create      = _on_page_create;
    t_g_menu_common_page_naming.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_common_page_naming.pf_menu_page_show        = _on_page_show;
    t_g_menu_common_page_naming.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_common_page_naming.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_common_page_naming.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_common_page_naming.pf_menu_page_update      = _on_page_update;

    return MENUR_OK;
}

extern VOID menu_page_input_async_action(VOID* pv_data, SIZE_T  z_data_size)
{
#if INPUT_NAMING_NEED_IPT_SOURCE
    BOOL b_flag = *(BOOL *)pv_data;
    _is_input_changing_set(b_flag);
#endif
}

extern UINT16 menu_page_naming_is_predef_name(CHAR *p_name)
{
    UINT16  ui2_mlm_idx = 0xFFFF;
    UINT16  ui2_i = 0;
    UINT16  ui2_j = 0;
    UINT16  ui2_num = 0;
    UTF16_T w2s_name[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

    if (NULL == p_name || c_strlen(p_name) == 0)
    {
        return ui2_mlm_idx;
    }

    c_uc_ps_to_w2s(p_name, w2s_name, APP_CFG_CUSTOM_INP_NAME_LEN);

    ui2_num = sizeof(aui2_g_predef_lbls)/sizeof(aui2_g_predef_lbls[0]);

    for (ui2_i = MLM_MENU_LANG_ENG; ui2_i < MLM_MENU_NUM_LANG; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < ui2_num; ui2_j++)
        {
            if  ((menu_page_lang_lbls[ui2_i].w2s_name_input_item_lable[ui2_j].ui2_key == aui2_g_predef_lbls[ui2_j])&&
                (c_uc_w2s_strcmp(w2s_name, menu_page_lang_lbls[ui2_i].w2s_name_input_item_lable[ui2_j].w2s_name_input_lable) == 0))
            {
                ui2_mlm_idx = aui2_g_predef_lbls[ui2_j];
                break;
            }
        }

        if (ui2_mlm_idx != 0xFFFF)
        {
            break;
        }
    }
    return ui2_mlm_idx;
}

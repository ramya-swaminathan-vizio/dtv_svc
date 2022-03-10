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

#include "wizard/a_wzd.h"
#include "app_util/a_isl.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "res/menu2/menu_custom.h"

#include "mmp/a_mmp.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#endif

#include "res/menu2/menu_custom_dialog.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _MENU_PIC_POSITION_PAGE_DATA_T
{
    HANDLE_T h_root_frm;
    HANDLE_T h_main_frm;
    HANDLE_T h_btn_adjust;
    HANDLE_T h_help;
    HANDLE_T h_ok_text;
    UINT32   ui4_nfy_id;
}MENU_PIC_POSITION_PAGE_DATA_T;

#define VID_POSITION_BTN_X ((SCREEN_W-VID_POSITION_BTN_W)/2)
#define VID_POSITION_BTN_Y ((SCREEN_H-VID_POSITION_BTN_H)/2)

#define VID_POSITION_BTN_W (200)
#define VID_POSITION_BTN_H (200)


#define VID_POSITION_HELP_X (100)
#define VID_POSITION_HELP_Y (SCREEN_H - VID_POSITION_HELP_H - 100)
#define VID_POSITION_HELP_W (SCREEN_W - VID_POSITION_HELP_X * 2)
#define VID_POSITION_HELP_H (50)
#define VID_COMP_MAX_H (50)
#define VID_COMP_MIN_H (-50)

enum
{
   INPUT_COMP  = 1,
   INPUT_HDMI1 = 2,
   INPUT_HDMI2 = 3,
   INPUT_HDMI3 = 4,
   INPUT_HDMI4 = 5
};

#define VID_INPUT_SRC_PIC_SIZE_V_SET(input,value) (input = (value << 24) + (input &   0xffffff))
#define VID_INPUT_SRC_PIC_SIZE_H_SET(input,value) (input = (value << 16) + (input & 0xff00ffff))
#define VID_INPUT_SRC_PIC_POS_V_SET(input,value)  (input = (value << 8) +  (input & 0xffff00ff))
#define VID_INPUT_SRC_PIC_POS_H_SET(input,value)  (input =  value +        (input & 0xffffff00))

#define VID_INPUT_SRC_PIC_SIZE_V_GET(input,value) (value = ((input >> 24) & 0xff))
#define VID_INPUT_SRC_PIC_SIZE_H_GET(input,value) (value = ((input >> 16) & 0xff))
#define VID_INPUT_SRC_PIC_POS_V_GET(input,value)  (value = ((input >> 8) & 0xff))
#define VID_INPUT_SRC_PIC_POS_H_GET(input,value)  (value = input & 0xff)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_vid_position;
static MENU_PIC_POSITION_PAGE_DATA_T t_g_pic_position_page_data;
static INT16    i2_g_vga_pos_v_last = 0;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementations
 ----------------------------------------------------------------------------*/


INT32 vid_update_position_info(UINT8 u1_input_id,INT32 i4_value,BOOL b_direction_v)
{
   INT32   i4_crt_save = 0;
    SIZE_T  size;
    DBG_LOG_PRINT(("[MENU][%s %d] u1_input_id = %d i4_value = %d, b_direction_v = %d\n",
                __FUNCTION__,__LINE__,
                u1_input_id,i4_value,b_direction_v));

    /* map it from [-50,50] to [50,150] */
    i4_value += 100;
    switch(u1_input_id)
    {
        case INPUT_COMP:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_COMP_VGA_SETTING,&i4_crt_save,&size));
            if(b_direction_v)
                VID_INPUT_SRC_PIC_POS_V_SET(i4_crt_save,i4_value);
            else
                VID_INPUT_SRC_PIC_POS_H_SET(i4_crt_save,i4_value);
            MENU_CHK_FAIL(acfg_set(IDX_CUSTOM_COMP_VGA_SETTING,&i4_crt_save,size));
            break;
        }
        case INPUT_HDMI1:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI1_VGA_SETTING,&i4_crt_save,&size));
            if(b_direction_v)
                VID_INPUT_SRC_PIC_POS_V_SET(i4_crt_save,i4_value);
            else
                VID_INPUT_SRC_PIC_POS_H_SET(i4_crt_save,i4_value);
            MENU_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI1_VGA_SETTING,&i4_crt_save,size));
            break;
        }
        case INPUT_HDMI2:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI2_VGA_SETTING,&i4_crt_save,&size));
            if(b_direction_v)
                VID_INPUT_SRC_PIC_POS_V_SET(i4_crt_save,i4_value);
            else
                VID_INPUT_SRC_PIC_POS_H_SET(i4_crt_save,i4_value);
            MENU_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI2_VGA_SETTING,&i4_crt_save,size));
            break;
        }
        case INPUT_HDMI3:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI3_VGA_SETTING,&i4_crt_save,&size));
            if(b_direction_v)
                VID_INPUT_SRC_PIC_POS_V_SET(i4_crt_save,i4_value);
            else
                VID_INPUT_SRC_PIC_POS_H_SET(i4_crt_save,i4_value);
            MENU_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI3_VGA_SETTING,&i4_crt_save,size));
            break;
        }
        case INPUT_HDMI4:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI4_VGA_SETTING,&i4_crt_save,&size));
            if(b_direction_v)
                VID_INPUT_SRC_PIC_POS_V_SET(i4_crt_save,i4_value);
            else
                VID_INPUT_SRC_PIC_POS_H_SET(i4_crt_save,i4_value);
            MENU_CHK_FAIL(acfg_set(IDX_CUSTOM_HDMI4_VGA_SETTING,&i4_crt_save,size));
            break;
        }
    }
    DBG_LOG_PRINT(("[MENU][%s %d] current save is 0x%x\n",__FUNCTION__,__LINE__,i4_crt_save));
    return MENUR_OK;
}

INT32 vid_update_current_input_src_position_info()
{
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8       ui1_input                         = 0xFF;
    UINT16      ui2_id = 0;
    ISL_REC_T   t_isl_rec;
    INT32       i4_crt_save = 0;
    SIZE_T      size;
    INT16       i2_v_value = 0;
    INT16       i2_h_value = 0;
    if (menu_picture_size_poition_is_hidde() || !menu_picture_position_is_enable())
    {
       return MENUR_OK;   // do nothing
    }
    /* Step 1: Get target input source */
    MENU_CHK_FAIL(a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name)));
    MENU_CHK_FAIL(a_cfg_av_get_input_src(s_disp_name, &ui1_input));
    MENU_CHK_FAIL(a_isl_get_rec_by_idx (ui1_input, &t_isl_rec));

    DBG_LOG_PRINT(("[MENU][%s %d] ui1_input = %d,t_isl_rec.e_src_type = %d e_video_type = 0x%x\n",
                __FUNCTION__,__LINE__,
                ui1_input,
                t_isl_rec.e_src_type,
                t_isl_rec.t_avc_info.e_video_type));
    switch(ui1_input)
    {
        case INPUT_COMP:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_COMP_VGA_SETTING,&i4_crt_save,&size));
            VID_INPUT_SRC_PIC_POS_V_GET(i4_crt_save,i2_v_value);
            VID_INPUT_SRC_PIC_POS_H_GET(i4_crt_save,i2_h_value);
            break;
        }
        case INPUT_HDMI1:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI1_VGA_SETTING,&i4_crt_save,&size));
            VID_INPUT_SRC_PIC_POS_V_GET(i4_crt_save,i2_v_value);
            VID_INPUT_SRC_PIC_POS_H_GET(i4_crt_save,i2_h_value);
            break;
        }
        case INPUT_HDMI2:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI2_VGA_SETTING,&i4_crt_save,&size));
            VID_INPUT_SRC_PIC_POS_V_GET(i4_crt_save,i2_v_value);
            VID_INPUT_SRC_PIC_POS_H_GET(i4_crt_save,i2_h_value);
            break;
        }
        case INPUT_HDMI3:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI3_VGA_SETTING,&i4_crt_save,&size));
            VID_INPUT_SRC_PIC_POS_V_GET(i4_crt_save,i2_v_value);
            VID_INPUT_SRC_PIC_POS_H_GET(i4_crt_save,i2_h_value);

            break;
        }
        case INPUT_HDMI4:
        {
            MENU_CHK_FAIL(acfg_get(IDX_CUSTOM_HDMI4_VGA_SETTING,&i4_crt_save,&size));
            VID_INPUT_SRC_PIC_POS_V_GET(i4_crt_save,i2_v_value);
            VID_INPUT_SRC_PIC_POS_H_GET(i4_crt_save,i2_h_value);
            break;
        }
        default:
        {
             SVL_REC_T   t_svl_rec;
             BOOL        b_found;
             MENU_CHK_FAIL(menu_get_crnt_svl_rec(&t_svl_rec, &b_found));
             if (b_found && BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
             {
                /*DTV*/
                return MENUR_OK;
             }
             if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
                 t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
             {
                UINT16 u2_default = 0;
                acfg_set(IDX_CUSTOM_VGA_H_SIZE, &u2_default,sizeof(INT16));
                acfg_set(IDX_CUSTOM_VGA_V_SIZE, &u2_default,sizeof(INT16));
                a_cfg_av_update(ui2_id);
             }
             else
             {
                ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
				i2_h_value = 0;
				a_cfg_av_get(ui2_id, &i2_h_value);
                a_cfg_av_set(ui2_id, i2_h_value);
                a_cfg_av_update(ui2_id);
                ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
				i2_v_value = 0;
				a_cfg_av_get(ui2_id, &i2_v_value);
                a_cfg_av_set(ui2_id, i2_v_value);

                a_cfg_av_update(ui2_id);

            }
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
            a_cfg_update_viewport();
            return MENUR_OK;
        }
    }

    DBG_LOG_PRINT(("[MENU][%s %d] current save is 0x%x\n",__FUNCTION__,__LINE__,i4_crt_save));
    /* map  it from  [50,150] to  [-50,50]  if need */
    if(i2_h_value < 50 || i2_h_value > 150)
        i2_h_value = 0;
    else
        i2_h_value -= 100;

    if(i2_v_value < 50 || i2_v_value > 150)
        i2_v_value = 0;
    else
        i2_v_value -= 100;

    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        acfg_set(IDX_CUSTOM_VGA_H_SIZE, &i2_h_value,sizeof(INT16));
        DBG_LOG_PRINT(("[MENU][%s %d] IDX_CUSTOM_VGA_H_SIZE,h => %d\n",__FUNCTION__,__LINE__,i2_h_value));
        acfg_set(IDX_CUSTOM_VGA_V_SIZE, &i2_v_value,sizeof(INT16));
        DBG_LOG_PRINT(("[MENU][%s %d] IDX_CUSTOM_VGA_V_SIZE,v => %d\n",__FUNCTION__,__LINE__,i2_v_value));
    }
    else
    {
         ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
         a_cfg_av_set(ui2_id, i2_h_value);
         DBG_LOG_PRINT(("[MENU][%s %d] APP_CFG_GRPID_VIDEO APP_CFG_RECID_VID_POS_H,h => %d\n",__FUNCTION__,__LINE__,i2_h_value));
         ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
         a_cfg_av_set(ui2_id, i2_v_value);
         DBG_LOG_PRINT(("[MENU][%s %d] APP_CFG_GRPID_VIDEO APP_CFG_RECID_VID_POS_V,v => %d\n",__FUNCTION__,__LINE__,i2_v_value));
     }
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    a_cfg_update_viewport();
    return MENUR_OK;
}

static INT32 _vid_position_help_create(HANDLE_T    h_parent,
                                          HANDLE_T*   ph_widget)
{
    GL_RECT_T                   t_rect;
    INT32                       i4_ret = WZDR_OK;
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    WGL_HTS_PARAG_ATTR_T        t_parag;
    CHAR*                       s_font_name = menu_font_name();
    WGL_COLOR_INFO_T            t_clr_info;

    SET_RECT_BY_SIZE(&t_rect,
                     VID_POSITION_HELP_X,
                     VID_POSITION_HELP_Y,
                     VID_POSITION_HELP_W,
                     VID_POSITION_HELP_H);

    c_memset(&t_init, 0, sizeof(WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  =(UINT16)0;

    /* set default font */
    c_strcpy(t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    /* create hyper text widget */
    i4_ret = c_wgl_create_widget(h_parent,
                                   HT_WGL_WIDGET_HTS,
                                   WGL_CONTENT_HTS_DEF,
                                   WGL_BORDER_NULL,
                                   &t_rect,
                                   NULL,
                                   255,
                                  (VOID*)(&t_init),
                                   NULL,
                                   ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                            WGL_CMD_HTS_SET_CNT_INSET,
                            WGL_PACK(&t_inset),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set justification */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                            WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                            WGL_PACK(WGL_HTS_JUSTIF_CENTER),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_CENTER;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 2;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                            WGL_CMD_HTS_CUR_PARAG_SET,
                           WGL_PACK(&t_parag),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_black;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_black;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_black;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return  i4_ret;
}

static UTF16_T* _vid_position_w2s_sch(UTF16_T*        pw2s_text,
                             const UTF16_T*  pw2s_sub_text)
{
    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;
    if (!pw2s_text ||
        !pw2s_sub_text)
    {
        return (pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if (t_txt_size < t_sub_txt_size)
    {
        return (pw2s_start);
    }

    pw2s_start = pw2s_text;

    while (pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while (t_cmp_offset < t_sub_txt_size)
        {
            if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if (t_cmp_offset == t_sub_txt_size)
        {
            return (pw2s_start);
        }
        pw2s_start++;
    }

    return (NULL);
}

static INT32 _vid_position_set_user_info(UTF16_T* pw2s_text,
                                              WGL_HIMG_TPL_T h_img_1,
                                              WGL_HIMG_TPL_T h_img_2,
                                              WGL_HIMG_TPL_T h_img_3,
                                              WGL_HIMG_TPL_T h_img_4,
                                              WGL_HIMG_TPL_T h_img_5)
{
    INT32                  i4_ret = MENUR_OK;
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    UINT16                 ui2_sec_id = 0;
    UINT16                 ui2_pic_idx = 0;
    WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;
    UTF16_T                w2s_pic_flag[3 + 1];
    UTF16_T*               pw2s_next = NULL;
    UTF16_T*               pw2s_temp = pw2s_text;
    GL_COLOR_T             t_color_desc_txt = {255, {255}, {255}, {255}};
    GL_COLOR_T             t_color_desc_txt_bk = {255, {0}, {0}, {0}};

    c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
    c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

    i4_ret = c_wgl_do_cmd (pt_this->h_help,
                           WGL_CMD_HTS_CLEAR_ALL,
                           WGL_PACK (FALSE),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, menu_font_name());
    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_MEDIUM;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

    /* Set text background color. */
    c_memcpy(&t_hts_txt_info.t_clr_text,
             &t_color_desc_txt,
             sizeof(GL_COLOR_T));
    c_memcpy(&t_hts_txt_info.t_clr_text_bk,
             &t_color_desc_txt_bk,
             sizeof(GL_COLOR_T));

    c_uc_ps_to_w2s("%p", w2s_pic_flag, sizeof(w2s_pic_flag));

    pw2s_next = _vid_position_w2s_sch(pw2s_temp, w2s_pic_flag);
    while (pw2s_next)
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

        i4_ret = c_wgl_do_cmd(pt_this->h_help,
                               WGL_CMD_HTS_APPEND_TEXT_SEC,
                               WGL_PACK (&t_hts_txt_info),
                               WGL_PACK (&ui2_sec_id));
        MENU_LOG_ON_FAIL(i4_ret);

        t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        if (0 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_1;
        }
        else if (1 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_2;
        }
        else if (2 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_3;
        }
        else if (3 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_4;
        }
        else if (4 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_5;
        }

        i4_ret = c_wgl_do_cmd(pt_this->h_help,
                               WGL_CMD_HTS_APPEND_IMG_SEC,
                               WGL_PACK(&t_hts_img_info),
                               WGL_PACK(&ui2_sec_id));
        MENU_LOG_ON_FAIL(i4_ret);
        ui2_pic_idx ++;

        pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
        pw2s_next = _vid_position_w2s_sch(pw2s_temp, w2s_pic_flag);
    }

    if (pw2s_temp < pw2s_text + c_uc_w2s_strlen(pw2s_text))
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

        i4_ret = c_wgl_do_cmd(pt_this->h_help,
                               WGL_CMD_HTS_APPEND_TEXT_SEC,
                               WGL_PACK (&t_hts_txt_info),
                               WGL_PACK (&ui2_sec_id));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _vid_position_center_ok_text(HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     VID_POSITION_BTN_W,
                     VID_POSITION_BTN_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128),
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

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 20;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID *) L"OK",
                          (VOID *) 2);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _vid_position_btn_create(HANDLE_T h_parent,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    GL_COLOR_T          t_color_txt = { 255, { 255 }, { 255 }, { 255 }};
    UINT32              ui4_style = WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_32;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     VID_POSITION_BTN_X,
                     VID_POSITION_BTN_Y,
                     VID_POSITION_BTN_W,
                     VID_POSITION_BTN_H
                     );

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
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_pic_size_pos_remote_arrows_v2;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_pic_size_pos_remote_arrows_v2;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_pic_size_pos_remote_arrows_v2;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_pic_size_pos_remote_arrows_v2;
    t_img_info.u_img_data.t_extend.t_push               = h_g_pic_size_pos_remote_arrows_v2;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_pic_size_pos_remote_arrows_v2;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable = t_color_txt;
    t_color_info.u_color_data.t_extend.t_disable = t_color_txt;
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
    t_font_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _vid_position_set_adjust_btn_bk_image(WGL_HIMG_TPL_T h_image, BOOL b_repaint)
{
    INT32               i4_ret = MENUR_OK;
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    WGL_IMG_INFO_T      t_img_info = {0};

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_image;
    t_img_info.u_img_data.t_extend.t_disable            = h_image;
    t_img_info.u_img_data.t_extend.t_highlight          = h_image;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_image;
    t_img_info.u_img_data.t_extend.t_push               = h_image;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_image;
    i4_ret = c_wgl_do_cmd(pt_this->h_btn_adjust,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_btn_adjust,
                                NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _incr_vga_pos_v
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
static INT32 _incr_vga_pos_v(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_v;

    i4_ret = a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V), &i2_vga_pos_v);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_v_last = i2_vga_pos_v;
    }
    else
    {
        i2_vga_pos_v = i2_g_vga_pos_v_last;
    }

    return i2_vga_pos_v;
}

/*----------------------------------------------------------------------------
 * Name: _decr_vga_pos_v
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
static INT32 _decr_vga_pos_v(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_v;

    i4_ret = a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V), &i2_vga_pos_v);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_v_last = i2_vga_pos_v;
    }
    else
    {
        i2_vga_pos_v = i2_g_vga_pos_v_last;
    }

    return i2_vga_pos_v;
}

static INT32 _vid_position_btn_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
            WGL_HIMG_TPL_T h_image = NULL_HANDLE;
            CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
            UINT8   ui1_input = 0xFF;

            /* Step 1: Get target input source */
            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
            MENU_LOG_ON_FAIL(i4_ret);
            DBG_LOG_PRINT(("[MENU][%s %d] keycode = 0x%x\n",__FUNCTION__,__LINE__,ui4_keycode));
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                case BTN_RETURN:
                {
                    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                                  WGL_SW_NORMAL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_nav_back();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    INT16 i2_vid_pos_h = 0;
                    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
                    INT16   i2_val_min = 0;
                    INT16   i2_val_max = 0;
                    ISL_REC_T                   t_isl_rec;

                    i4_ret = a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                        && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
                    {
                        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H);
                    }

                    a_cfg_av_get(ui2_id, &i2_vid_pos_h);

                    i4_ret = a_cfg_av_get_min_max(
                                ui2_id,
                                &i2_val_min, &i2_val_max);
                    MENU_LOG_ON_FAIL(i4_ret);
                    DBG_LOG_PRINT(("[MENU][%s %d] ui2_id =0x%x i2_val_min = %d i2_val_max = %d\n",__FUNCTION__,__LINE__,ui2_id,i2_val_min,i2_val_max));

                    if (BTN_CURSOR_LEFT == ui4_keycode)
                    {
                        if (i2_val_min == i2_vid_pos_h)
                        {
                            return 0;
                        }

                        i2_vid_pos_h--;
                        h_image = h_g_pic_pos_remote_left_v2;
                    }
                    else
                    {
                        if (i2_val_max == i2_vid_pos_h)
                        {
                            return 0;
                        }

                        i2_vid_pos_h++;
                        h_image = h_g_pic_pos_remote_right_v2;
                    }

                    a_cfg_av_set(ui2_id, i2_vid_pos_h);
                    a_cfg_av_update(ui2_id);
                    vid_update_position_info(ui1_input,i2_vid_pos_h,FALSE);
                    i4_ret = _vid_position_set_adjust_btn_bk_image(h_image, TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_DOWN:
                case BTN_CURSOR_UP:
                {
                    INT16 i2_vid_pos_v = 0;
                    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
                    INT16   i2_val_min = 0;
                    INT16   i2_val_max = 0;
                    ISL_REC_T t_isl_rec;

                    i4_ret = a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                        && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
                    {
                        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V);
                    }

                    a_cfg_av_get(ui2_id, &i2_vid_pos_v);

                    i4_ret = a_cfg_av_get_min_max(
                        ui2_id,
                        &i2_val_min, &i2_val_max);
                    MENU_LOG_ON_FAIL(i4_ret);
                    DBG_LOG_PRINT(("[MENU][%s %d] ui2_id =0x%x e_video_type = %d i2_val_min = %d i2_val_max = %d\n",
                        __FUNCTION__,__LINE__,
                        ui2_id,t_isl_rec.t_avc_info.e_video_type,i2_val_min,i2_val_max));
                    if (BTN_CURSOR_DOWN == ui4_keycode)
                    {
                        if (i2_val_min == i2_vid_pos_v)
                        {
                            return 0;
                        }

                        if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
                            i2_vid_pos_v = _decr_vga_pos_v();
                        else
                            i2_vid_pos_v--;
                        h_image = h_g_pic_pos_remote_down_v2;
                    }
                    else
                    {
                        if (i2_val_max == i2_vid_pos_v)
                        {
                            return 0;
                        }

                        if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                            && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
                            i2_vid_pos_v = _incr_vga_pos_v();
                        else
                            i2_vid_pos_v++;

                        h_image = h_g_pic_pos_remote_up_v2;
                    }
                    
                    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
                        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO
                        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))    /* COMP */
                    {
                        i2_vid_pos_v = i2_vid_pos_v < VID_COMP_MIN_H ? VID_COMP_MIN_H 
                            : (i2_vid_pos_v > VID_COMP_MAX_H ? VID_COMP_MAX_H : i2_vid_pos_v);
                    }

                    a_cfg_av_set(ui2_id, i2_vid_pos_v);
                    a_cfg_av_update(ui2_id);
                    vid_update_position_info(ui1_input,i2_vid_pos_v,TRUE);
                    i4_ret = _vid_position_set_adjust_btn_bk_image(h_image, TRUE);
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
#ifdef  APP_TTS_SUPPORT
            UTF16_T w2s_tts_tmp[64] = {0};
            UINT32 ui4_keycode = (UINT32)param1;

            if(ui4_keycode == BTN_CURSOR_LEFT ||
              ui4_keycode == BTN_CURSOR_RIGHT ||
              ui4_keycode == BTN_CURSOR_DOWN  ||
              ui4_keycode == BTN_CURSOR_UP)
            {
                switch(ui4_keycode)
                {
                    case BTN_CURSOR_UP   :   c_uc_w2s_strcat(w2s_tts_tmp,L"up");      break;
                    case BTN_CURSOR_DOWN :   c_uc_w2s_strcat(w2s_tts_tmp,L"down");    break;
                    case BTN_CURSOR_LEFT :   c_uc_w2s_strcat(w2s_tts_tmp,L"left");    break;
                    case BTN_CURSOR_RIGHT:   c_uc_w2s_strcat(w2s_tts_tmp,L"right");   break;
                    default:
                        break;
                }
                if(c_uc_w2s_strlen(w2s_tts_tmp) != 0)
                {
                    a_app_tts_play(w2s_tts_tmp, c_uc_w2s_strlen(w2s_tts_tmp));
                }
            }
#endif
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _vid_position_w2s_str_replace(
                UTF16_T*  w2s_dst,
                SIZE_T    t_dst_len,
                UTF16_T*  w2s_src[],
                UINT32    ui4_src_sz
                )
{
    if (w2s_dst == NULL ||
        t_dst_len == 0 ||
        w2s_src == NULL ||
        ui4_src_sz == 0
        )
    {
        DBG_LOG_PRINT(("{%s,%d} parameters err. \r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    UTF16_T* buffer = c_mem_alloc(sizeof(UTF16_T)*t_dst_len);
    if (buffer == NULL) {
        DBG_LOG_PRINT(("{%s,%d} c_mem_alloc() failed. \r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }
    c_memset(buffer, 0, sizeof(UTF16_T)*t_dst_len);

    UTF16_T*    p_w2s_dst = w2s_dst;
    UTF16_T     w2s_pattern[] = L"%p";
    SIZE_T      t_pattern_len = c_uc_w2s_strlen(w2s_pattern);
    SIZE_T      t_rest_len = t_dst_len-1;

    for (UINT32 ui4_src_idx = 0; ui4_src_idx < ui4_src_sz; ++ui4_src_idx)
    {
        UTF16_T*    p_w2s_pattern = &w2s_pattern[0];
        INT32       i4_idx = 0;

        while (*(p_w2s_dst+i4_idx) != *p_w2s_pattern)
        {
            if (*(p_w2s_dst+i4_idx) == 0)
                break;
            i4_idx++;
        }
        while (*(p_w2s_dst+i4_idx) == *p_w2s_pattern)
        {
            if (*(p_w2s_dst+i4_idx) ==0)
                break;
            p_w2s_pattern++;
            i4_idx++;
        }

        if (*p_w2s_pattern == 0)  // find  pattern string from  dst string
        {
            if ((i4_idx - t_pattern_len) > 0)
            {
                if ((i4_idx - t_pattern_len) > t_rest_len) {
                    c_mem_free(buffer);
                    return NAVR_FAIL;
                }
                c_uc_w2s_strncat(buffer, p_w2s_dst, i4_idx - t_pattern_len);
                t_rest_len -= (i4_idx - t_pattern_len);
            }

            p_w2s_dst += i4_idx;

            SIZE_T  t_src_len = c_uc_w2s_strlen(w2s_src[ui4_src_idx]);
            if (t_src_len > t_rest_len) {
                c_mem_free(buffer);
                return NAVR_FAIL;
            }
            c_uc_w2s_strncat(buffer, w2s_src[ui4_src_idx], t_src_len);
            t_rest_len -= t_src_len;
        }
    }

    if (p_w2s_dst != w2s_dst)
    {
        SIZE_T  t_dst_r_len = c_uc_w2s_strlen(p_w2s_dst);
        if (t_dst_r_len > t_rest_len) {
            c_mem_free(buffer);
            return NAVR_FAIL;
        }
        c_uc_w2s_strncat(buffer, p_w2s_dst, t_dst_r_len);
        c_uc_w2s_strcpy(w2s_dst, buffer);
        c_mem_free(buffer);
        return NAVR_OK;
    }
    else
    {
        c_mem_free(buffer);
        return NAVR_FAIL;
    }

}

static VOID _loosely_exclusive_callback(VOID* pv_tag, VOID* pv_param)
{
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    UINT32 ui4_nfy_id = (UINT32)pv_param;
    INT32  i4_ret = MENUR_OK;

    if (ui4_nfy_id == pt_this->ui4_nfy_id)
    {
        i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_nav_back();
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static INT32 _vid_position_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    INT32 i4_ret = MENUR_OK;

    c_memset(pt_this, 0, sizeof(MENU_PIC_POSITION_PAGE_DATA_T));

    i4_ret = menu_pm_get_root_frm(&pt_this->h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_get_main_frm(&pt_this->h_main_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _vid_position_btn_create(pt_this->h_root_frm,
                                           _vid_position_btn_proc_fct,
                                           MENU_TEXT(MLM_MENU_KEY_ADJUST_PIC_POS),
                                           &pt_this->h_btn_adjust);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _vid_position_center_ok_text(pt_this->h_btn_adjust, &pt_this->h_ok_text);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = _vid_position_help_create(pt_this->h_root_frm, &pt_this->h_help);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui4_nfy_id = 1024;

    return i4_ret;
}

static INT32 _vid_position_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static VOID _vid_position_page_repaint_tips(VOID)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = c_wgl_repaint(t_g_pic_position_page_data.h_help, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_pic_position_page_data.h_btn_adjust, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

}


static INT32 _vid_position_page_show(UINT32 ui4_page_id)
{
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    INT32 i4_ret = MENUR_OK;

    if (1024 == pt_this->ui4_nfy_id)
    {
        menu_custom_dialog_loosely_exclusive_set_register(_loosely_exclusive_callback,
            NULL,
            &pt_this->ui4_nfy_id);
    }

#ifdef VIEWPORT_SUPPORT
    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
    a_cfg_update_viewport ();
#endif

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_btn_adjust,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_help,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    _vid_position_set_user_info(MENU_TEXT(MLM_MENU_KEY_HELP_TEXT_HV_SIZE),
                            h_g_arrow_up,
                            h_g_arrow_bottom,
                            h_g_arrow_left,
                            h_g_arrow_right,
                            h_g_ok_key_select);

#ifdef APP_TTS_SUPPORT
    do {
        UTF16_T   buffer[256+1] = {0};
        UTF16_T * w2s_src[] = {L"up", L"down", L"left", L"right", L"ok"};
        c_uc_w2s_strncpy(buffer, MENU_TEXT(MLM_MENU_KEY_HELP_TEXT_HV_SIZE), 256);
        _vid_position_w2s_str_replace(buffer, 256, w2s_src, 5);
        a_app_tts_play(buffer, 256);
    } while(0);
#endif
    _vid_position_set_adjust_btn_bk_image(h_g_pic_size_pos_remote_arrows_v2, FALSE);

    i4_ret = c_wgl_set_visibility(pt_this->h_ok_text,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    _vid_position_page_repaint_tips();
    return i4_ret;
}

static INT32 _vid_position_page_hide(UINT32 ui4_page_id)
{
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    INT32 i4_ret = MENUR_OK;

    if (1024 != pt_this->ui4_nfy_id)
    {
        menu_custom_dialog_loosely_exclusive_set_unregister(pt_this->ui4_nfy_id);
        pt_this->ui4_nfy_id = 1024;
    }

#ifdef VIEWPORT_SUPPORT
    if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
    {
        a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
    }
    a_cfg_update_viewport ();
#endif

    i4_ret = c_wgl_set_visibility(pt_this->h_btn_adjust,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_help,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    _vid_position_page_repaint_tips();

    return i4_ret;
}

static INT32 _vid_position_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    MENU_PIC_POSITION_PAGE_DATA_T* pt_this = &t_g_pic_position_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_focus(pt_this->h_btn_adjust,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _vid_position_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _vid_position_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}

extern INT32 menu_page_vid_position_init(VOID)
{
    t_g_menu_page_vid_position.pf_menu_page_create =    _vid_position_page_create;
    t_g_menu_page_vid_position.pf_menu_page_destroy=    _vid_position_page_destroy;
    t_g_menu_page_vid_position.pf_menu_page_show=       _vid_position_page_show;
    t_g_menu_page_vid_position.pf_menu_page_hide=       _vid_position_page_hide;
    t_g_menu_page_vid_position.pf_menu_page_get_focus=  _vid_position_page_get_focus;
    t_g_menu_page_vid_position.pf_menu_page_lose_focus= _vid_position_page_lose_focus;
    t_g_menu_page_vid_position.pf_menu_page_update=     _vid_position_page_update;

 return MENUR_OK;
}

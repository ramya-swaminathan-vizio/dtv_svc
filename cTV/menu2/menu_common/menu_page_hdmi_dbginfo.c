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
 * $RCSfile: menu_page_relevant_information.c,v $
 * $Revision: #1 $
 * $Date:  $
 * $Author:  $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_sm_video_hdlr.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_svctx.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/menu_dbg.h"

#include "u_scc.h"
#include "c_scc.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                         data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_hdmi_dbginfo;

static HANDLE_T     h_hdmidbg_frm;
static HANDLE_T     h_root_frm;
static HANDLE_T     h_dbginfo_lb;

typedef UINT8 SCC_HDMI_Status_Debug_T ;

 static INT32 _hdmi_dbginfo_msg_proc(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    UINT32          ui4_keycode = (UINT32)pv_param1;
    GL_RECT_T       t_rect = {0};
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    UTF16_T w2s_str[256] = {0};

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_RETURN:
                    /* Let the menu show */
                    c_wgl_set_visibility(h_hdmidbg_frm, WGL_SW_HIDE_RECURSIVE);
                    c_wgl_repaint(h_hdmidbg_frm,NULL,TRUE);
                    menu_main_set_visibility(TRUE);
                    menu_nav_back();
                    break;
                default:
                break;
            }
        }
        default:
            break;
    }
    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


static INT32 _hdmi_dbginfo_lb_create( HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_FONT_INFO_T         t_fnt_info;
    WGL_LB_INIT_T                   t_lb_init;
    WGL_LB_COL_INIT_T               at_cols[1];
    UINT8 ui1_row,ui1_col = 0;

    at_cols[0].e_col_type          = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align           = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width           = 1920;
    at_cols[0].ui2_max_text_len    = 800;

    /* listbox init struct */
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_NO_SCROLL |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = 30;
    t_lb_init.ui2_elem_size     = 30;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &at_cols;

    SET_RECT_BY_SIZE(&t_rect, 0, 0, 1920, 900);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                NULL,
                                &t_lb_init,
                                NULL ,
                                ph_widget);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size      = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                        WGL_CMD_LB_SET_COL_FONT,
                        WGL_PACK((UINT16)ui1_col),
                        WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    GL_COLOR_T t_frame_color_bk0 = { 210, {   1 }, {   1 }, {   1 }}; // Black
    WGL_COLOR_INFO_T t_color_info = {0};

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable   = t_frame_color_bk0;
    t_color_info.u_color_data.t_standard.t_disable  = t_frame_color_bk0;
    t_color_info.u_color_data.t_standard.t_highlight= t_frame_color_bk0;

    i4_ret = c_wgl_do_cmd( *ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK), /* background color */
                          WGL_PACK(& t_color_info) );

    WGL_LB_ITEM_T                   at_items[1];

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = L" \0";
    for(ui1_row = 0;ui1_row < 30;ui1_row++)
    {
        i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_APPEND_ELEM,
                        WGL_PACK(at_items),
                        NULL);
    }

    return MENUR_OK;
}

static INT32 _hdmi_dbginfo_getdata(HDMI_STATUS_DEBUG_T* pst_debug_info)
{
    INT32                     i4_ret = MENUR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(HDMI_STATUS_DEBUG_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_DEBUG_INFO;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pst_debug_info;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != RMR_OK)
    {
        DBG_LOG_PRINT(("%s i4_ret : %d\n", __func__, i4_ret));
    }

    return i4_ret;
}

static INT32 _hdmi_dbginfo_lb_update_data(VOID)
{
    WGL_LB_ITEM_T                   at_items[1];
    INT32           i4_ret = MENUR_OK;
    HDMI_STATUS_DEBUG_T st_debug_info;
    CHAR                        s_buffer[256] = {0};
    UTF16_T                     w2s_tmp_str[256];
    UINT8 item_index = 0;
    c_memset(&st_debug_info,0,sizeof(HDMI_STATUS_DEBUG_T));
    _hdmi_dbginfo_getdata(&st_debug_info);

    at_items[0].data.pw2s_text = L"General Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer, "HDMI Port %d,HDMI_5V:%s,HDMI Mode:%s,HDR Type:%s",
        st_debug_info.hdmi_general_info.ui1_cur_port,
        st_debug_info.hdmi_general_info.ui1_hdmi_5V == 0 ? "LOW":"HIGH",
        st_debug_info.hdmi_general_info.ui1_hdmi_mode == 0 ? "HDMI":
        st_debug_info.hdmi_general_info.ui1_hdmi_mode == 1 ? "DVI":
        "MHL",
        st_debug_info.hdmi_hdr_info.ui1_eotf == 0 ? "SDR":
        st_debug_info.hdmi_hdr_info.ui1_eotf == 1 ? "HDR10":
        st_debug_info.hdmi_hdr_info.ui1_eotf == 2 ? "HLG":
        st_debug_info.hdmi_hdr_info.ui1_eotf == 3 ? "DOVI":
        st_debug_info.hdmi_hdr_info.ui1_eotf == 4 ? "TECHNI":
        st_debug_info.hdmi_hdr_info.ui1_eotf == 5 ? "HDR10+":"UNKNOWN"
        );
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer, "%dx%d @ %0.2fHz,%s,%s",
        st_debug_info.hdmi_video_info.ui4_vde,
        st_debug_info.hdmi_video_info.ui4_hde,
        ((float)(st_debug_info.hdmi_video_info.ui4_freq)) / 100,
        st_debug_info.hdmi_avi_info.eColorformat == 0 ? "RGB":
        st_debug_info.hdmi_avi_info.eColorformat == 1 ? "YUV422":
        st_debug_info.hdmi_avi_info.eColorformat == 2 ? "YUV444":"YUV420",
        st_debug_info.hdmi_video_info.ui4_colordepth == 0 ? "8BIT":
        st_debug_info.hdmi_video_info.ui4_colordepth == 1 ? "10BIT":
        st_debug_info.hdmi_video_info.ui4_colordepth == 2 ? "12BIT":
        st_debug_info.hdmi_video_info.ui4_colordepth == 3 ? "16BIT":"UNKNOWN");
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer, "%s,%dHZ,%dBIT",
        st_debug_info.hdmi_audio_info.ui2_ispcm == 0 ? "PCM":"NonPCM",
        st_debug_info.hdmi_audio_info.ui2_freq,
        st_debug_info.hdmi_audio_info.ui2_bitwidth);
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    item_index += 1; //Blank Line
    at_items[0].data.pw2s_text = L"Video Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer, "Active res:%dx%d ,Total res: %dx%d,Freq: %0.2fHz,%s,%s",
        st_debug_info.hdmi_video_info.ui4_vde,
        st_debug_info.hdmi_video_info.ui4_hde,
        st_debug_info.hdmi_video_info.ui4_vtt,
        st_debug_info.hdmi_video_info.ui4_htt,
        ((float)(st_debug_info.hdmi_video_info.ui4_freq)) / 100,
        st_debug_info.hdmi_avi_info.eColorformat == 0 ? "RGB":
        st_debug_info.hdmi_avi_info.eColorformat == 1 ? "YUV422":
        st_debug_info.hdmi_avi_info.eColorformat == 2 ? "YUV444":"YUV420",
        st_debug_info.hdmi_video_info.ui4_colordepth == 0 ? "8BIT":
        st_debug_info.hdmi_video_info.ui4_colordepth == 1 ? "10BIT":
        st_debug_info.hdmi_video_info.ui4_colordepth == 2 ? "12BIT":
        st_debug_info.hdmi_video_info.ui4_colordepth == 3 ? "16BIT":"UNKNOWN");
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    item_index += 1; //Blank Line
    at_items[0].data.pw2s_text = L"PHY Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);

    c_sprintf(s_buffer, "TMDSClockKHz: %d, TMDSBandwidthMbps: %d,"
        " PHYCtleEQMinRage: %d, PHYCtleEQMaxRage: %d,"
        " PHYCtleEQResult: %d, PHYError: %d, lockStatus: %d\n",
        st_debug_info.hdmi_phy_info.u32TMDSClockKHz,
        st_debug_info.hdmi_phy_info.u32TMDSBandwidthMbps,
        st_debug_info.hdmi_phy_info.u32PHYCtleEQMinRage,
        st_debug_info.hdmi_phy_info.u32PHYCtleEQMaxRage,
        st_debug_info.hdmi_phy_info.u32PHYCtleEQResult,
        st_debug_info.hdmi_phy_info.u32PHYError,
        st_debug_info.hdmi_phy_info.blockStatus);
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    item_index += 1; //Blank Line
    at_items[0].data.pw2s_text = L"SCDC Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);

    c_sprintf(s_buffer,"BitRatio: %d, SourceVersion: %d, SinkVersion: %d, "
        "FFELevels: %d, FRLRate: %d, LTPRequest: %d, RSCorrectionCount: %d, "
        "ChErrorCount: %d, RSEDUpdate: %d, FLTUpdate: %d, FRLStart: %d",
        st_debug_info.hdmi_scdc_info.u8BitRatio,
        st_debug_info.hdmi_scdc_info.u8SourceVersion,
        st_debug_info.hdmi_scdc_info.u8SinkVersion,
        st_debug_info.hdmi_scdc_info.u8FFELevels,
        st_debug_info.hdmi_scdc_info.u8FRLRate,
        st_debug_info.hdmi_scdc_info.u8LTPRequest,
        st_debug_info.hdmi_scdc_info.u16RSCorrectionCount,
        st_debug_info.hdmi_scdc_info.u16ChErrorCount,
        st_debug_info.hdmi_scdc_info.bRSEDUpdate,
        st_debug_info.hdmi_scdc_info.bFLTUpdate,
        st_debug_info.hdmi_scdc_info.bFRLStart);
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);

    c_sprintf(s_buffer,"SourceTestUpdate: %d, RRTest: %d, CEDUpdate: %d, StatusUpdate: %d "
        "ScrambleEnable: %d, ScrambleStatus: %d, FLTNoRetrain: %d, RREnable: %d, "
        "DSCDecodeFail: %d, FLTReady: %d",
        st_debug_info.hdmi_scdc_info.bSourceTestUpdate,
        st_debug_info.hdmi_scdc_info.bRRTest,
        st_debug_info.hdmi_scdc_info.bCEDUpdate,
        st_debug_info.hdmi_scdc_info.bStatusUpdate,
        st_debug_info.hdmi_scdc_info.bScrambleEnable,
        st_debug_info.hdmi_scdc_info.bScrambleStatus,
        st_debug_info.hdmi_scdc_info.bFLTNoRetrain,
        st_debug_info.hdmi_scdc_info.bRREnable,
        st_debug_info.hdmi_scdc_info.bDSCDecodeFail,
        st_debug_info.hdmi_scdc_info.bFLTReady);
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);

    c_sprintf(s_buffer,"ClockDetect: %d, RSCorrectionValid: %d, ChLocked: %d, CEDValid: %d",
        st_debug_info.hdmi_scdc_info.bClockDetect,
        st_debug_info.hdmi_scdc_info.bRSCorrectionValid,
        st_debug_info.hdmi_scdc_info.bChLocked,
        st_debug_info.hdmi_scdc_info.bCEDValid);
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    item_index += 1; //Blank Line
    at_items[0].data.pw2s_text = L"HDCP Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer,"Port0_HDCP14: %d, Port0_HDCP22: %d, "
            "Port1_HDCP14: %d, Port1_HDCP22: %d, "
            "Port2_HDCP14: %d, Port2_HDCP22: %d, "
            "Port3_HDCP14: %d, Port3_HDCP22: %d",
            st_debug_info.hdmi_hdcp_info.hdcp_info[0].ui1_hdcp14,
            st_debug_info.hdmi_hdcp_info.hdcp_info[0].ui1_hdcp22,
            st_debug_info.hdmi_hdcp_info.hdcp_info[1].ui1_hdcp14,
            st_debug_info.hdmi_hdcp_info.hdcp_info[1].ui1_hdcp22,
            st_debug_info.hdmi_hdcp_info.hdcp_info[2].ui1_hdcp14,
            st_debug_info.hdmi_hdcp_info.hdcp_info[2].ui1_hdcp22,
            st_debug_info.hdmi_hdcp_info.hdcp_info[3].ui1_hdcp14,
            st_debug_info.hdmi_hdcp_info.hdcp_info[3].ui1_hdcp22);

    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    item_index += 1; //Blank Line
    at_items[0].data.pw2s_text = L"AVI Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer,"ActiveInfo: %d, Afd: %d, BarInfo: %d, Colorformat: %d, "
                "Colorimetry: %d, ContentType: %d, ExtColorimetry: %d, ItContent: %d, PicScale: %d",
                st_debug_info.hdmi_avi_info.eActiveInfo,
                st_debug_info.hdmi_avi_info.eAfd,
                st_debug_info.hdmi_avi_info.eBarInfo,
                st_debug_info.hdmi_avi_info.eColorformat,
                st_debug_info.hdmi_avi_info.eColorimetry,
                st_debug_info.hdmi_avi_info.eContentType,
                st_debug_info.hdmi_avi_info.eExtColorimetry,
                st_debug_info.hdmi_avi_info.eItContent,
                st_debug_info.hdmi_avi_info.ePicScale);

    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer, "PictureAr: %d, RgbQuantRange: %d, ScanInfo: %d, YccQuantRange: %d, "
                "PixelRepeat: %d, VideoIdCode: %d",
                st_debug_info.hdmi_avi_info.ePictureAr,
                st_debug_info.hdmi_avi_info.eRgbQuantRange,
                st_debug_info.hdmi_avi_info.eScanInfo,
                st_debug_info.hdmi_avi_info.eYccQuantRange,
                st_debug_info.hdmi_avi_info.u8PixelRepeat,
                st_debug_info.hdmi_avi_info.u8VideoIdCode);

    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer, "BottomBarStartLineNumber: %d, LeftBarEndPixelNumber: %d, "
                "RightBarStartPixelNumber: %d, TopBarEndLineNumber: %d",
                st_debug_info.hdmi_avi_info.u16BottomBarStartLineNumber,
                st_debug_info.hdmi_avi_info.u16LeftBarEndPixelNumber,
                st_debug_info.hdmi_avi_info.u16RightBarStartPixelNumber,
                st_debug_info.hdmi_avi_info.u16TopBarEndLineNumber);

    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    item_index += 1; //Blank Line
    at_items[0].data.pw2s_text = L"SPD Info\0";
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);

    c_memset(s_buffer,0,sizeof(CHAR)*256);
    c_memset(w2s_tmp_str,0,sizeof(UTF16_T)*256);
    c_sprintf(s_buffer,"SPD InfoFrame : ");
    int i =0;
    UINT8 temp_buffer[10];
    for(i = 0;i < 28; i++)
    {
        c_memset(temp_buffer, 0, sizeof(UINT8) * 10);
        c_sprintf(temp_buffer,"0x%x ",st_debug_info.hdmi_spd_info.ui1_spd_info[i]);
        c_strcat(s_buffer,temp_buffer);
    }

    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
    at_items[0].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(item_index++,0),
                        at_items[0].data.pw2s_text);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,VOID*  pv_create_data)
{
    INT32                   i4_ret;
    GL_RECT_T               t_rect;

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE (& t_rect,0,73,1920,900);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 _hdmi_dbginfo_msg_proc,
                                 255,
                                 NULL,
                                 0,
                                 &h_hdmidbg_frm);

    i4_ret = c_wgl_insert(h_hdmidbg_frm, NULL_HANDLE, WGL_INSERT_TOPMOST, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = _hdmi_dbginfo_lb_create(h_hdmidbg_frm, &h_dbginfo_lb);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_hdmidbg_frm, WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32           i4_ret;
    i4_ret = menu_main_set_visibility(FALSE);
    _hdmi_dbginfo_lb_update_data();

    i4_ret = c_wgl_set_visibility(h_hdmidbg_frm, WGL_SW_RECURSIVE);
    i4_ret = c_wgl_repaint(h_hdmidbg_frm, NULL,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_hdmidbg_frm, WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id, MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id, UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

INT32 menu_page_hdmi_dbginfo_init(VOID)
{
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_hdmi_dbginfo.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

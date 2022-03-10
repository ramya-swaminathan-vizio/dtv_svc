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
 * $RCSfile: menu_atsc.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/23 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 47aa641dbb1c0b2b64f3264199a32d61 $
 *
 * Description:
 *      This file contains the implementation of GUI-related functions of the
 * menu application
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"

#include "c_fm.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_svctx.h"
#include "c_cfg.h"
#include "c_wgl.h"
#ifdef APP_DCR_SUPPORT
    #include "c_pod_hostres.h"
#endif

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"

/* Svl Builder Engine */
#include "u_sb_atsc_eng.h"
#ifdef APP_DCR_SUPPORT
    #include "u_sb_oob_eng.h"
#else
    #include "u_sb_cqam_eng.h"
#endif
#include "u_sb_ntsc_eng.h"

#include "menu2/menu.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_dbg.h"

#if APP_ATSC_SPT
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
MENU_ATSC_T          t_g_menu_atsc;


/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Name: _sb_nfy_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *----------------------------------------------------------------------------*/
static VOID _sb_nfy_fct (HANDLE_T          h_builder,
                         SB_COND_T         e_builder_cond,
                         VOID*             pv_nfy_tag)
{
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_init
 *
 * Description: The initaiting function of ATSC-specific menu
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_init(VOID)
{
    INT32 i4_ret;

    do
    {
        #define NTSC_TRSTRL_SVL_ID              ATSC_TRSTRL_SVL_ID
        #define NTSC_TRSTRL_SVL_NAME            ATSC_TRSTRL_SVL_NAME
        #define NTSC_TRSTRL_SVL_FILE            ATSC_TRSTRL_SVL_FILE
        #define NTSC_TRSTRL_TUNER_NAME          SN_TUNER_GRP_0

        #define NTSC_CABLE_SVL_ID               ATSC_CABLE_SVL_ID
        #define NTSC_CABLE_SVL_NAME             ATSC_CABLE_SVL_NAME
        #define NTSC_CABLE_SVL_FILE             ATSC_CABLE_SVL_FILE
        #define NTSC_CABLE_TUNER_NAME           SN_TUNER_GRP_0

        /* Open SVL Builder */
        MENU_TMS_SPLIT("open sb");

        /* ATSC sb engine */
        {
            SB_COND_T e_atsc_cond;
            SB_ATSC_OPEN_DATA_T t_sb_atsc_open_data;
            c_memset(&t_sb_atsc_open_data, 0, sizeof(SB_ATSC_OPEN_DATA_T));
            t_sb_atsc_open_data.ui2_svl_id    = ATSC_TRSTRL_SVL_ID;
            t_sb_atsc_open_data.ps_svl_name   = ATSC_TRSTRL_SVL_NAME;
            t_sb_atsc_open_data.ps_file_name  = ATSC_TRSTRL_SVL_FILE;
            t_sb_atsc_open_data.ps_tuner_name = ATSC_TRSTRL_TUNER_NAME;
            t_sb_atsc_open_data.b_use_orig =TRUE;
            i4_ret = c_sb_open_builder(SB_TRSTRL_ENG_NAME,
                                       &t_sb_atsc_open_data,
                                       NULL,
                                       _sb_nfy_fct,
                                       &t_g_menu_atsc.h_sb_dig_air,
                                       &e_atsc_cond);
            MENU_CHK_FAIL(i4_ret);
        }

        /* CLRQAM/OOB sb engine */
        {
            SB_COND_T e_cqam_cond;
    #ifdef APP_DCR_SUPPORT
            SB_OOB_OPEN_DATA_T t_sb_cqam_open_data;
            c_memset(&t_sb_cqam_open_data, 0, sizeof(SB_OOB_OPEN_DATA_T));
    #else
            SB_CQAM_OPEN_DATA_T t_sb_cqam_open_data;
            c_memset(&t_sb_cqam_open_data, 0, sizeof(SB_CQAM_OPEN_DATA_T));
    #endif
            t_sb_cqam_open_data.ui2_svl_id    = ATSC_CABLE_SVL_ID;
            t_sb_cqam_open_data.ps_svl_name   = ATSC_CABLE_SVL_NAME;
            t_sb_cqam_open_data.ps_file_name  = ATSC_CABLE_SVL_FILE;
            t_sb_cqam_open_data.ps_tuner_name = ATSC_CABLE_TUNER_NAME;
            t_sb_cqam_open_data.b_use_orig =TRUE;
            i4_ret = c_sb_open_builder(SB_CABLE_ENG_NAME,
                                       &t_sb_cqam_open_data,
                                       NULL,
                                       _sb_nfy_fct,
                                       &t_g_menu_atsc.h_sb_dig_cable,
                                       &e_cqam_cond);
            MENU_CHK_FAIL(i4_ret);
        }

#ifdef APP_537X_SUPPORT
        /* NTSC-Air sb engine */
        {
            SB_COND_T e_ntsc_cond;
            SB_NTSC_OPEN_DATA_T t_sb_ntsc_open_data;

            c_memset(&t_sb_ntsc_open_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
            t_sb_ntsc_open_data.ui2_svl_id    = NTSC_TRSTRL_SVL_ID;
            t_sb_ntsc_open_data.ps_svl_name   = NTSC_TRSTRL_SVL_NAME;
            t_sb_ntsc_open_data.ps_file_name  = NTSC_TRSTRL_SVL_FILE;
            t_sb_ntsc_open_data.ps_tuner_name = NTSC_TRSTRL_TUNER_NAME;
            t_sb_ntsc_open_data.b_use_orig =TRUE;
            i4_ret = c_sb_open_builder(SB_NTSC_TER_ENG_NAME,
                                       &t_sb_ntsc_open_data,
                                       NULL,
                                       _sb_nfy_fct,
                                       &t_g_menu_atsc.h_sb_anlg_air,
                                       &e_ntsc_cond);
            MENU_CHK_FAIL(i4_ret);
        }

        /* NTSC-Cable sb engine */
        {
            SB_COND_T e_ntsc_cond;
            SB_NTSC_OPEN_DATA_T t_sb_ntsc_open_data;

            c_memset(&t_sb_ntsc_open_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
            t_sb_ntsc_open_data.ui2_svl_id    = NTSC_CABLE_SVL_ID;
            t_sb_ntsc_open_data.ps_svl_name   = NTSC_CABLE_SVL_NAME;
            t_sb_ntsc_open_data.ps_file_name  = NTSC_CABLE_SVL_FILE;
            t_sb_ntsc_open_data.ps_tuner_name = NTSC_CABLE_TUNER_NAME;
            t_sb_ntsc_open_data.b_use_orig =TRUE;
            i4_ret = c_sb_open_builder(SB_NTSC_CAB_ENG_NAME,
                                       &t_sb_ntsc_open_data,
                                       NULL,
                                       _sb_nfy_fct,
                                       &t_g_menu_atsc.h_sb_anlg_cable,
                                       &e_ntsc_cond);
            MENU_CHK_FAIL(i4_ret);
        }
#endif /* APP_537X_SUPPORT */

#ifdef ATSC_AUTO_SCAN_ENABLE
        i4_ret = menu_atsc_page_auto_scan_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_AUTO_SCAN2_ENABLE
        i4_ret = menu_atsc_page_auto_scan2_init();
        MENU_CHK_FAIL(i4_ret);
		
		i4_ret = menu_atsc_page_auto_scan2_new_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_MNL_SCAN_ENABLE
        i4_ret = menu_atsc_page_mnl_scan_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_ADV_SCAN_RNG_ENABLE
        i4_ret = menu_atsc_page_adv_scan_rng_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_ADV_SCAN_SGL_ENABLE
        i4_ret = menu_atsc_page_adv_scan_sgl_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_CAP_STL_ENABLE
        i4_ret = menu_atsc_page_cap_stl_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_LCT_CODE_ENABLE
        i4_ret = menu_atsc_page_lct_code_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_VCHIP_ENABLE
        i4_ret = menu_atsc_page_vchip_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_VCHIP_US_TV_ENABLE
        i4_ret = menu_atsc_page_vchip_us_tv_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_VCHIP_US_MOVIE_ENABLE
        i4_ret = menu_atsc_page_vchip_us_movie_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_VCHIP_CA_EN_ENABLE
        i4_ret = menu_atsc_page_vchip_ca_en_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_VCHIP_CA_FR_ENABLE
        i4_ret = menu_atsc_page_vchip_ca_fr_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ATSC_OP_VCHIP_ENABLE
        i4_ret = menu_atsc_page_op_vchip_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_atsc_page_op_vchip_drrt_init();
        MENU_CHK_FAIL(i4_ret);
#endif
        i4_ret = menu_atsc_page_add_analog_scan_init();
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_atsc_settings_init();
        MENU_CHK_FAIL(i4_ret);

#ifdef APP_MENU_VCT_RAW_SUPPORT
        i4_ret = menu_page_vct_raw_init ();
        MENU_CHK_FAIL(i4_ret);
#endif
        i4_ret = menu_page_new_eq_init() ;
        MENU_CHK_FAIL(i4_ret);
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        return AEER_FAIL;
    }
    else
    {
        return AEER_OK;
    }
}


INT32 menu_atsc_pause(VOID)
{
    return AEER_OK;
}

INT32 menu_atsc_resume(VOID)
{
    return AEER_OK;
}

INT32 menu_atsc_exit(VOID)
{
    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_process_msg
 *
 * Description: Process the ATSC-specific menu messages.
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *          pb_processed        Output TRUE if the message has been procesed
 *                              in ATSC-specific function; Otherwise, output
 *                              FALSE.
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_process_msg (
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL*        pb_processed)
{
    *pb_processed = FALSE;

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_common_help_show_back
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_atsc_help_show_scan(VOID)
{
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_help_show_scanning
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_atsc_help_show_scanning(VOID)
{
    /* use help tip instead of menu's help list */

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_rating_lst_create
 *
 * Description:
 *      Create a rating list of the vchip pages. The outlook is as follow.
 *
 *   -----------------------------------
 *   |  P                          [ ] |
 *   |  PG                         [L] |
 *   |  PG13                       [ ] |
 *   |                                 |
 *   -----------------------------------
 *
 *
 * Inputs:
 *      h_parent - paraent widget
 *      ui2_elem_max - max element number
 *      pf_wdget_proc - the listbox widget procedure.*
 * Outputs:
 *      ph_lb - the created listbox.
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_rating_lst_create(
    HANDLE_T            h_parent,
    UINT16              ui2_elem_max,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*           ph_lb)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;

    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = CH_LST2_COL0_W + CH_LST2_COL1_W + CH_LST2_COL2_W;
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width        = CONTENT_W - (CH_LST2_COL0_W + CH_LST2_COL1_W + CH_LST2_COL2_W);

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_NO_WRAP_OVER
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_MULTI_SEL
                                  | WGL_STL_LB_NO_SCROLL;


    t_lb_init.ui2_max_elem_num  = ui2_elem_max;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT * ui2_elem_max);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_lb);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> Fail to create rating list - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = MENU_ITEM_BAR_CNT_INSET_L;
    t_inset.i4_right    = MENU_ITEM_BAR_CNT_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left   =   10;
    t_inset.i4_right  =   0;
    t_inset.i4_top    =   5;
    t_inset.i4_bottom =   0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left   =   0;
    t_inset.i4_right  =   18;
    t_inset.i4_top    =   2;
    t_inset.i4_bottom =   0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_fnt_info));
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_CHK_FAIL(i4_ret);

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
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(1, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    t_clr_elem.t_normal             = t_g_menu_color_bk1_txt;
    t_clr_elem.t_disable            = t_g_menu_color_bk1_txt;
    t_clr_elem.t_highlight          = t_g_menu_color_bk1_txt;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_bk1_txt;
    t_clr_elem.t_pushed             = t_g_menu_color_bk1_txt;
    t_clr_elem.t_selected           = t_g_menu_color_bk1_txt;
    t_clr_elem.t_selected_disable   = t_g_menu_color_bk1_txt;


    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_TEXT),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(&t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next       = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev       = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select     = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_LB_SET_KEY_MAP,
                          &t_lb_key_map,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_rating_lst_create
 *
 * Description:
 *      Create a rating menu_atsc_rating_indicator_create of the vchip pages.
 *   The outlook is as follow.
 *
 *   ----------------------------------------
 *   |[ ]Allowed Rating    [L]Locked Rating |
 *   ----------------------------------------
 *
 *
 * Inputs:
 *      h_parent - paraent widget
 *      pf_wdget_proc - the listbox widget procedure.*
 * Outputs:
 *      ph_lb - the created listbox.
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_rating_indicator_create(
    HANDLE_T            h_parent,
    INT32               i4_idx,
    HANDLE_T*           ph_lb)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[4];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_ITEM_T               at_items[4];
    WGL_FONT_INFO_T             t_fnt_info;

    at_cols[0].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width        = GRID_W * 1 + 10;
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = GRID_W * 7 - 10;
    at_cols[2].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[2].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[2].ui2_width        = GRID_W * 1 + 10;
    at_cols[3].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[3].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[3].ui2_max_text_len = 32;
    at_cols[3].ui2_width        = GRID_W * 7 - 10;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK;
    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     10,
                     GRID_H * i4_idx,
                     MENU_ITEM_V_WIDE,
                     GRID_H * 1);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_lb);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> Fail to create rating list - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 20;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)2),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)3),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_fnt_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)3),
                           WGL_PACK(&t_fnt_info));
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_CHK_FAIL(i4_ret);

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
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(1, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(2, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(3, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    t_clr_elem.t_normal             = t_g_menu_color_bk1_txt;
    t_clr_elem.t_disable            = t_g_menu_color_bk1_txt;
    t_clr_elem.t_highlight          = t_g_menu_color_bk1_txt;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_bk1_txt;
    t_clr_elem.t_pushed             = t_g_menu_color_bk1_txt;
    t_clr_elem.t_selected           = t_g_menu_color_bk1_txt;
    t_clr_elem.t_selected_disable   = t_g_menu_color_bk1_txt;

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(1, WGL_CLR_TEXT),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(3, WGL_CLR_TEXT),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    /*
    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = NULL_HANDLE;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(&t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);
    */

    /* Append element */
    at_items[0].e_col_type          = LB_COL_TYPE_IMG;
    at_items[0].data.h_img          = h_g_menu_img_unlock;
    at_items[1].e_col_type          = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text      = MENU_TEXT(MLM_MENU_KEY_VCHIP_ALLOWED);
    at_items[2].e_col_type          = LB_COL_TYPE_IMG;
    at_items[2].data.h_img          = h_g_menu_img_lock;
    at_items[3].e_col_type          = LB_COL_TYPE_TEXT;
    at_items[3].data.pw2s_text      = MENU_TEXT(MLM_MENU_KEY_VCHIP_BLOCKED);

    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_rating_indicator_chg_lang
 *
 * Description:
 *  Update the multilingual message of the rating indicator
 * Inputs:
 *      h_lb - paraent widget
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_rating_indicator_chg_lang(
    HANDLE_T    h_lb)
{
    INT32   i4_ret;

    i4_ret = c_wgl_do_cmd(h_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0, 1),
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VCHIP_ALLOWED)));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0, 3),
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VCHIP_BLOCKED)));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_atsc_update_sb_snk_name
 *
 * Description:
 *  Update the sink name to svl builder NTSC engine.
 *
 * Inputs:
 *      h_lb - paraent widget
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_update_sb_snk_name(
    HANDLE_T    h_sb,
    HANDLE_T    h_svctx)
{
    INT32   i4_ret;
    CHAR    s_snk_name[SVCTX_SNK_NAME_MAX_SIZE + 1];
    SIZE_T  z_size = SVCTX_SNK_NAME_MAX_SIZE;

    /* get sync name from svctx */
    i4_ret = c_svctx_get(h_svctx,
                         SVCTX_COMMON_GET_TYPE_SNK_NAME,
                         (VOID*)s_snk_name,
                         &z_size);
    MENU_CHK_FAIL(i4_ret);

    /* set sync name to sb */
    i4_ret = c_sb_set(h_sb,
                      SB_KEY_TYPE_SET_TVD_SNK_NAME,
                      NULL,
                      z_size,
                      s_snk_name);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
#endif


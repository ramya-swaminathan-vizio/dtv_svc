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
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: menu_page_add_atv_scan.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *      This scan for add ATV channel.
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
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
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

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_atsc/menu_atsc.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef TIME_MEASUREMENT
#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#endif
#include "menu2/menu_common/menu_page_animation.h"

/* channel scan status */
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _ADD_ATV_SCAN_INFO_T {
	HANDLE_T	h_builder;
	HANDLE_T	h_pb;
	INT32		i4_vir_ch_num;
	INT32		i4_phy_ch_num;
	INT32		i4_phy_ch_ttl;
	BOOL		b_done; 		/* if b_done is TRUE, it means that the builder has
								   sent a SB_REASON_COMPLETE, SB_REASON_CANCEL,
								   SB_REASON_ABORT message */
	HANDLE_T	h_warn_fail_dlg;
	HANDLE_T	h_warn_suc_dlg;
	BOOL	 	b_fail_dlg_show;
	BOOL	 	b_suc_dlg_show;
	HANDLE_T    h_timer;
} ADD_ATV_SCAN_INFO_T;


typedef struct _ADD_ATV_SCAN_NFY_T {
    HANDLE_T    h_builder;
    UINT32      ui4_nfy_reason;
    INT32       i4_nfy_data;
    VOID*       pv_nfy_tag;
} ADD_ATV_SCAN_NFY_T;

#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)

#define INPUT_RESET_DELAY                 ((UINT32) 1500)

#define PHY_TRSTRL_CH_NUM_MIN             ((UINT16)    2)
#define PHY_TRSTRL_CH_NUM_MAX             ((UINT16)   69)

#define PHY_CABLE_CH_NUM_MIN              ((UINT16)    SB_CQAM_SCAN_FIRST_CHANNEL)
#define PHY_CABLE_CH_NUM_MAX              ((UINT16)    SB_CQAM_SCAN_LAST_CHANNEL)

#define SCAN_CHL_SUC_DLG_TIME			  5000

static WGL_INSET_T t_inset_border = {
    MENU_ITEM_V_CNT_INSET_L + MENU_ITEM_V_TITLE_W,
    0,
    0,
    0};

static GL_RECT_T   t_rect_border_title = {
    18,
    0,
    MENU_ITEM_V_TITLE_W,
    MENU_ITEM_V_HEIGHT};

typedef enum {
    _HELP_TIP_TYPE_CH_LST = 0 ,
    _HELP_TIP_TYPE_HOMEBAR ,
    _HELP_TIP_TYPE_BACKBAR ,
    _HELP_TIP_TYPE_LAST_ENTRY

} _HELP_TIP_TYPE_T ;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_add_analog_scan;

static HANDLE_T    h_cnt_frm      = NULL_HANDLE;
static HANDLE_T    h_txt      = NULL_HANDLE;
static HANDLE_T    h_channel_eb   = NULL_HANDLE;
static HANDLE_T    h_start_scan   = NULL_HANDLE;

static ADD_ATV_SCAN_INFO_T   t_scan_info_atv;


static UINT16      ui2_phy_ch_min = 0;
static UINT16      ui2_phy_ch_max = 0;
static UINT16      ui2_crnt_svl_id;
static BOOL        b_scan = FALSE;
static BOOL        b_scan_done = FALSE;
static UINT32      ui4_channel_num = 0;
//static MENU_SCAN_PB_ITEM_T t_scan_pb={0};
static INT32 _analog_channel_suc_dlg_show(VOID);
static INT32 _analog_channel_suc_dlg_show(VOID);
static INT32 _analog_channel_suc_dlg_create(VOID);
static INT32 _analog_channel_fail_dlg_show(VOID);
static VOID _analog_channel_fail_dlg_yes_btn(VOID);
static INT32 _analog_channel_fail_dlg_create(VOID);



/*----------------------------------------------------------------------------
 * Name: _itoa
 *
 * Description: Interger to string utility function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _itoa(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);

	return;
}

/*----------------------------------------------------------------------------
 * Name: _on_scan_stop
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
static INT32 _on_scan_stop(UINT32  ui4_stop_reason)
{
    INT32    i4_ret = 0;

	i4_ret = menu_action_chg_lang(h_start_scan,
        						 MLM_MENU_KEY_SCAN_DONE,
        						 MLM_MENU_KEY_EMPTY);
	MENU_LOG_ON_FAIL(i4_ret);

	b_scan_done = TRUE;

	a_amb_channel_scan_active(FALSE);

    return MENUR_OK;
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _calc_progress
 *
 * Description:
 *  Calculate the progress.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _calc_progress(VOID)
{
    return t_scan_info_atv.i4_phy_ch_num * 100 / t_scan_info_atv.i4_phy_ch_ttl;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _do_scan_nfy
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
static VOID _do_scan_nfy(VOID* pv_data,
                            SIZE_T  z_data_size)
{
    INT32            i4_ret;
    ADD_ATV_SCAN_NFY_T*  pt_scan_nfy = (ADD_ATV_SCAN_NFY_T*)pv_data;
    ADD_ATV_SCAN_INFO_T*   pt_scan_info = (ADD_ATV_SCAN_INFO_T*)pt_scan_nfy->pv_nfy_tag;
    /*INT32            i4_progress;*/
	BOOL 	b_found = FALSE;

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_PROGRESS)
    {
        if (b_scan)
        {
            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data);
            pt_scan_info->i4_phy_ch_num += 1;
            pt_scan_info->i4_phy_ch_ttl  = _GET_PHY_CH_NUM(pt_scan_nfy->i4_nfy_data);

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                DBG_ERROR(("<MENU>ph_ch_num > ph_ch_ttl!:%d,%d\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl));
                pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }
           /*
            i4_progress = _calc_progress();
            i4_ret=c_wgl_do_cmd(t_scan_pb.h_bar,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) i4_progress),
                         NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(t_scan_pb.h_frm, NULL, TRUE);
            */
        }
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE)
    {
        pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_CANCEL)
    {
        /* do nothing */
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_ABORT)
    {
        if(b_scan)
        {
            /* Abort is always triggered by svl-builder internal */
            _on_scan_stop(SB_REASON_ABORT);
            menu_pm_repaint();
    	    b_scan = FALSE;
        }
    }

    /* Check if the builder reach "AVAILABLE" condition */
    if(pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE ||
       pt_scan_nfy->ui4_nfy_reason & SB_REASON_CANCEL   ||
       pt_scan_nfy->ui4_nfy_reason & SB_REASON_ABORT    )
    {
        pt_scan_info->b_done = TRUE;

        /* make sure that both ATV scan complete */
        if(t_scan_info_atv.b_done == TRUE)
        {
            if(b_scan)
            {
                /* Good, the scan complete correctly */
                /*
                i4_ret=c_wgl_do_cmd(t_scan_pb.h_bar,
                             WGL_CMD_PG_SET_POS,
                             WGL_PACK((INT32) 100),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                _on_scan_stop(SB_REASON_COMPLETE);
				menu_pm_repaint();
				*/
			    b_scan = FALSE;
                menu_page_animation_stop();
                //menu_nav_back();
            }

            /* Re-open SVL */
            if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID &&
                t_g_menu_common.h_svl_air == NULL_HANDLE)
            {
                i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID,
                                    NULL,
                                    NULL,
                                    &t_g_menu_common.h_svl_air);
                if (i4_ret != SVLR_OK)
                {
                    DBG_ERROR(("<MENU>Can't open SVL\r\n"));
                    t_g_menu_common.h_svl_air = NULL_HANDLE;
                }
            }
            else if (ui2_crnt_svl_id == ATSC_CABLE_SVL_ID &&
                     t_g_menu_common.h_svl_cable == NULL_HANDLE)
            {
                i4_ret = c_svl_open(ATSC_CABLE_SVL_ID,
                                    NULL,
                                    NULL,
                                    &t_g_menu_common.h_svl_cable);
                if (i4_ret != SVLR_OK)
                {
                    DBG_ERROR(("<MENU>Can't open SVL\r\n"));
                    t_g_menu_common.h_svl_cable = NULL_HANDLE;
                }
            }

            /* Select service if menu is active */
            if(menu_get_cond() == MENU_COND_HIDE ||
               menu_get_cond() == MENU_COND_SHOW)
            {
                menu_add_analog_select_channel(ui4_channel_num,&b_found);
				if(b_found == TRUE)
				{
					i4_ret = _analog_channel_suc_dlg_show();
					MENU_LOG_ON_FAIL(i4_ret);
				}
				else
				{
					i4_ret = _analog_channel_fail_dlg_show();
					MENU_LOG_ON_FAIL(i4_ret);

				}
            }
        }
    }
}


/*----------------------------------------------------------------------------
 * Name: _scan_nfy_fct
 *
 * Description: The callback function of SVL Builder.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _scan_nfy_fct(HANDLE_T          h_builder,
                            UINT32            ui4_nfy_reason,
                            INT32             i4_nfy_data,
                            VOID*             pv_nfy_tag)
{
    INT32              i4_ret;
    ADD_ATV_SCAN_NFY_T t_scan_nfy;

    if (menu_get_cond() != MENU_COND_NOT_INIT)
    {
        t_scan_nfy.h_builder = h_builder;
        t_scan_nfy.ui4_nfy_reason = ui4_nfy_reason;
        t_scan_nfy.i4_nfy_data = i4_nfy_data;
        t_scan_nfy.pv_nfy_tag = pv_nfy_tag;

        i4_ret = menu_async_invoke(_do_scan_nfy,
                                   &t_scan_nfy,
                                   sizeof(ADD_ATV_SCAN_NFY_T),
                                   TRUE);
        if(i4_ret < 0){
            DBG_ERROR(("<MENU>Cannot send scan notify message!\r\n"));
        }
    }
}


/*----------------------------------------------------------------------------
 * Name: _start_scan
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
static INT32 _start_scan(VOID)
{
    INT32       i4_ret;
    SB_COND_T   e_cond;

    if (b_scan)
    {
        DBG_ERROR(("<MENU> It's scanning!\n"));
        return MENUR_FAIL;
    }

    menu_page_animation_start(3,FALSE);
    menu_page_animation_show();

    /* find the start and end physical frequency */


    /* close service context */
    i4_ret = c_svctx_sync_stop_svc(menu_get_crnt_svctx(),
                                   DEFAULT_STOP_SVC_TIMEOUT);
    if (i4_ret == SVCTXR_TIMEOUT)
    {
        DBG_ERROR(("<MENU>Cannot close service context timeout. \r\n"));
        return MENUR_FAIL;
    }
    else if (i4_ret != SVCTXR_OK && i4_ret != SVCTXR_ALREADY_STOPPED)
    {
        DBG_ERROR(("<MENU>Cannot close service context. %d\r\n", i4_ret));
        return MENUR_FAIL;
    }

    /* Start scan the ATV channels*/
    t_scan_info_atv.b_done = FALSE;
    if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
    {
        SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

        DBG_INFO(("<MENU>Scan Mode: NTSC/AIR\r\n"));

        /* udpate the sink name to builder */
        menu_atsc_update_sb_snk_name(t_g_menu_atsc.h_sb_anlg_air,
                                     menu_get_crnt_svctx());

        /* start scan */
        c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
        t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
        t_ntsc_scan_data.ui2_start_idx = ui4_channel_num;
        t_ntsc_scan_data.ui2_end_idx   = ui4_channel_num;

        t_scan_info_atv.h_builder = t_g_menu_atsc.h_sb_anlg_air;

        i4_ret = c_sb_start_scan(t_g_menu_atsc.h_sb_anlg_air,
                                 &t_ntsc_scan_data,
                                 &t_scan_info_atv,
                                 _scan_nfy_fct,
                                 &e_cond);
    }
    else
    {
        SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

        DBG_INFO(("<MENU>Scan Mode: NTSC/CABLE\r\n"));

        /* udpate the sink name to builder */
        menu_atsc_update_sb_snk_name(t_g_menu_atsc.h_sb_anlg_cable,
                                     menu_get_crnt_svctx());

        /* start scan */
        c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
        t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
        t_ntsc_scan_data.ui2_start_idx = ui4_channel_num;
        t_ntsc_scan_data.ui2_end_idx   = ui4_channel_num;

        t_scan_info_atv.h_builder = t_g_menu_atsc.h_sb_anlg_cable;

        i4_ret = c_sb_start_scan(t_g_menu_atsc.h_sb_anlg_cable,
                                 &t_ntsc_scan_data,
                                 &t_scan_info_atv,
                                 _scan_nfy_fct,
                                 &e_cond);
    }

    if (i4_ret != SBR_OK)
    {
        DBG_ERROR(("<MENU>Can't start scan\r\n"));
        return MENUR_FAIL;
    }

    /* set up the dirty flags for storing SVL and TSL */
    if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
    {
        t_g_menu_common.b_svl_air_dirty = TRUE;
        t_g_menu_common.b_tsl_air_dirty = TRUE;
    }
    else
    {
        t_g_menu_common.b_svl_cable_dirty = TRUE;
        t_g_menu_common.b_tsl_cable_dirty = TRUE;
    }

    /* Init the scan relative data */
    b_scan = TRUE;
    t_scan_info_atv.i4_vir_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_ttl = 200;  /* assign a big enough value */

    /* disable the menu timer */
    menu_timer_enable(FALSE);
    menu_timer_stop();

    menu_page_animation_show();

    DBG_INFO(("<MENU>Start to scan\r\n"));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
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
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            if (b_scan)
            {
                switch (ui4_keycode)
                {
                case BTN_EXIT:

                    menu_pm_repaint();
                    return WMPR_DONE;
                }
            }
            else
            {
                switch (ui4_keycode)
                {
                case BTN_SELECT:
                    MENU_LOG_ON_FAIL (c_wgl_set_focus(h_start_scan,WGL_SYNC_AUTO_REPAINT));
                    break;
                    case BTN_RETURN:
                    menu_nav_back();
                    return WMPR_DONE;
                default:
                    break;
                }
            }
        }
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _channel_eb_set_value
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
static INT32 _channel_eb_set_value(HANDLE_T    h_widget,
                                        UINT16      u2_value,
                                        BOOL        b_append)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[10];

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(u2_value),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_channel_num = u2_value;

    c_memset(w2s_buf, 0, 10);

    if(u2_value != 0)
    {
        _itoa(w2s_buf, (INT32)u2_value, 10);
    }
    else
    {
        c_uc_w2s_strcpy(w2s_buf, _TEXT(""));
    }

    if(b_append)
    {
        c_uc_w2s_strncat(w2s_buf, _TEXT("_"),
                         10 - c_uc_w2s_strlen(w2s_buf));
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _channel_eb_get_value
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
static UINT16 _channel_eb_get_value(HANDLE_T    h_widget)
{
    UINT32      u4_value;
    c_wgl_do_cmd(h_widget,
                 WGL_CMD_GL_GET_ATTACH_DATA,
                 WGL_PACK(&u4_value),
                 NULL);

    return (UINT16)u4_value;
}

/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            MENU_LOG_ON_FAIL (menu_nav_go_home_menu ()) ;
            return MENUR_OK ;

        case BTN_RETURN:
            MENU_LOG_ON_FAIL (menu_nav_back ()) ;
            return MENUR_OK ;

        case BTN_CURSOR_UP:
            break ;

        case BTN_CURSOR_DOWN :
            /* focus backbar */
            MENU_LOG_ON_FAIL (menu_set_focus_on_backbar (TRUE)) ;
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));

            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{

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
            MENU_LOG_ON_FAIL (menu_nav_back ()) ;
            return MENUR_OK ;

        case BTN_CURSOR_DOWN:
            /* in scan processing ,dose no allow browse channel list */
            if (b_scan)
            {
                return WMPR_DONE ;
            }

            /* focus ch list */
            MENU_LOG_ON_FAIL (c_wgl_set_focus (h_channel_eb, WGL_SYNC_AUTO_REPAINT));

            break ;

        case BTN_CURSOR_UP :
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar (TRUE)) ;
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));

            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _help_tip_update
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
static INT32 _help_tip_update (
    _HELP_TIP_TYPE_T            e_help_tip_type
    )
{

    switch (e_help_tip_type)
    {

    case _HELP_TIP_TYPE_HOMEBAR :
    case _HELP_TIP_TYPE_BACKBAR :
        break ;

    default :
        MENU_LOG_ON_FAIL (MENUR_INV_ARG) ;
    }

    return MENUR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _channel_eb_fct
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
static INT32 _channel_eb_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        _channel_eb_set_value(h_widget,0,TRUE);
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_ADD_ANALOG_SCAN_EB_HELP));


    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_ADD_ANALOG_SCAN_EB), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_ADD_ANALOG_SCAN_EB)));
    #endif
        break;
    }

    case WGL_MSG_LOSE_FOCUS:
    {
        UINT16 ui2_value = _channel_eb_get_value(h_widget);

        if((ui2_value < ui2_phy_ch_min) || (ui2_value > ui2_phy_ch_max))
        {
            ui2_value = ui2_phy_ch_min;
        }
        _channel_eb_set_value(h_widget,ui2_value,FALSE);

        break;
    }

    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
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
        {
            UINT16 ui2_input = (UINT16)(ui4_keycode - BTN_DIGIT_0);
            UINT16 ui2_value = _channel_eb_get_value(h_widget);

            if(ui2_value<99)
            {
                ui2_value = (UINT16)(ui2_value * 10 + ui2_input);
            }
            else
            {
                ui2_value = ui2_input;
            }

            while(ui2_value > ui2_phy_ch_max)
            {
                if(ui2_value >= 100)
                {
                    ui2_value = ui2_value % 100;
                }
                else
                {
                    ui2_value = ui2_value % 10;
                }
            }

            _channel_eb_set_value(h_widget,ui2_value,TRUE);
            c_wgl_repaint(h_widget, NULL, TRUE);
            return WMPR_DONE;
        }
        case BTN_CURSOR_LEFT:
        {
            UINT16 ui2_value = _channel_eb_get_value(h_widget);
            UINT16 ui_i,ui_j;

            ui_i = ui2_value/100;
            ui_j = (ui2_value%100)/10;

            if(ui_j>0 || ui_i>0)
            {
                ui2_value = ui_i*10+ui_j;
            }
            else
            {
                ui2_value = 0;
            }
            _channel_eb_set_value(h_widget, ui2_value,TRUE);

            c_wgl_repaint(h_widget, NULL, TRUE);

            return WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            return WGLR_OK;
        }
        case BTN_CURSOR_UP:
        {
             MENU_LOG_ON_FAIL (menu_set_focus_on_backbar (TRUE)) ;
             menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        }
        return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
        case BTN_CURSOR_DOWN:
        {
            MENU_LOG_ON_FAIL (c_wgl_set_focus(h_start_scan,WGL_SYNC_AUTO_REPAINT));
        }
        return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
        default:
            break;
        }
    }
    default:
        break;
    }
    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _start_scan_proc_fct
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
static INT32 _start_scan_proc_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    INT32   i4_ret;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_ADD_ANALOG_SCAN_ADD_HELP));

    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_ADD_ANALOG_SCAN_ADD), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_ADD_ANALOG_SCAN_ADD)));
    #endif

        break;
    }
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        if(b_scan)
        {
            return MENUR_OK;
        }

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            if(b_scan_done == TRUE)
            {
                i4_ret = menu_action_chg_lang(h_start_scan,
                                              MLM_MENU_KEY_ADD_ANALOG_SCAN_ADD,
                                              MLM_MENU_KEY_EMPTY);
                MENU_LOG_ON_FAIL(i4_ret);

                b_scan_done = FALSE;
            }
            MENU_LOG_ON_FAIL (c_wgl_set_focus(h_channel_eb, WGL_NO_AUTO_REPAINT));
            menu_pm_repaint();
            return MENUR_OK;
        }
        break;

        case BTN_CURSOR_DOWN:
        {
            i4_ret = menu_help_tip_keytip_set_focus (h_start_scan, 0, FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            menu_pm_repaint();
        }
        break;

        case BTN_CURSOR_RIGHT:
        case BTN_SELECT:
        {
            if(b_scan_done == FALSE)
            {
                 _start_scan();
                 menu_pm_repaint();
                 return WGLR_OK;
            }
            else
            {
                menu_nav_back();
                return WGLR_OK;
            }
        }
        break;

        case BTN_CURSOR_LEFT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default :
        break;
        }
    }
    break;
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: menu_action_chg_lang
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
INT32 _add_analog_ch_dlg_chg_lang(VOID)
{
    INT32   i4_ret;

	i4_ret = a_ui_simple_dialog_set_text(t_scan_info_atv.h_warn_fail_dlg,
												  MENU_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_FAIL_DLG));
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = a_ui_simple_dialog_set_yes_text(t_scan_info_atv.h_warn_fail_dlg, MENU_TEXT( MLM_MENU_KEY_OK));
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = a_ui_simple_dialog_set_text(t_scan_info_atv.h_warn_suc_dlg,
												  MENU_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_SUC_DLG));
	MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _add_analog_ch_suc_dlg_do_timer_nfy
 *
 * Description:
 *		Show the usb popup dialog under menu app.
 * Inputs:
 *		None
 * Outputs:
 *		None
 * Returns:
 *		MENUR_OK		Success
 *		Ohers			Fail
 ----------------------------------------------------------------------------*/
static VOID _add_analog_ch_suc_dlg_do_timer_nfy(VOID* pv_data, SIZE_T  z_data_size)
{
	INT32 i4_ret = 0;

	if(t_scan_info_atv.b_suc_dlg_show)
	{
    #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    #endif

	    i4_ret = a_ui_simple_dialog_hide(t_scan_info_atv.h_warn_suc_dlg);
	    MENU_LOG_ON_FAIL(i4_ret);

		t_scan_info_atv.b_suc_dlg_show = FALSE;
	}

	i4_ret=menu_pm_repaint();
    MENU_LOG_ON_FAIL(i4_ret);
	//MENU_LOG_ON_FAIL( c_wgl_set_focus(h_channel_eb,WGL_NO_AUTO_REPAINT) );
}

/*----------------------------------------------------------------------------
 * Name: _add_analog_ch_suc_dlg_timer_nfy
 *
 * Description:
 *      Show the usb popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static VOID _add_analog_ch_suc_dlg_timer_nfy(HANDLE_T  pt_tm_handle, VOID*   pv_tag)
{
    menu_async_invoke(_add_analog_ch_suc_dlg_do_timer_nfy,
                      		NULL, 0, TRUE);

}


/*----------------------------------------------------------------------------
 * Name: _analog_channel_suc_dlg_show
 *
 * Description:
 *      Show the usb popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _analog_channel_suc_dlg_show(VOID)
{
    INT32                       i4_ret  = MENUR_OK;

	if(!t_scan_info_atv.b_suc_dlg_show)
	{
    i4_ret = a_ui_simple_dialog_show(t_scan_info_atv.h_warn_suc_dlg);
    MENU_LOG_ON_FAIL(i4_ret);
		t_scan_info_atv.b_suc_dlg_show = TRUE;
	}
   	if(t_scan_info_atv.b_fail_dlg_show)
   	{
	i4_ret = a_ui_simple_dialog_hide(t_scan_info_atv.h_warn_fail_dlg);
	MENU_LOG_ON_FAIL(i4_ret);
		t_scan_info_atv.b_fail_dlg_show = FALSE;
   	}

	a_ui_simple_dialog_repaint(t_scan_info_atv.h_warn_suc_dlg);
	//a_ui_simple_dialog_set_focus(t_scan_info_atv.h_warn_suc_dlg, TRUE);

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_SUC_DLG), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_SUC_DLG)));
#endif

    i4_ret = c_timer_start(t_scan_info_atv.h_timer,
                           SCAN_CHL_SUC_DLG_TIME,
                           X_TIMER_FLAG_ONCE,
                           _add_analog_ch_suc_dlg_timer_nfy,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    /* channel scan status */
    /* add analog channel success, case ACFG_CUST_CH_NOT_SCANED: */

    a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_CH_NOT_SCANED);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _analog_channel_suc_dlg_create
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
static INT32 _analog_channel_suc_dlg_create(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
	HANDLE_T		h_parent = NULL_HANDLE;


	i4_ret = menu_pm_get_root_frm(&h_parent);
	MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
    t_simple_dialog_init.h_parent                       = h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = NULL;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;
	t_simple_dialog_init.b_one_btn_mode 				= FALSE;
	t_simple_dialog_init.b_info_icon					=FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                      			&t_scan_info_atv.h_warn_suc_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = a_ui_simple_dialog_set_text(t_scan_info_atv.h_warn_suc_dlg,
												  MENU_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_SUC_DLG));
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}


/*----------------------------------------------------------------------------
 * Name: _analog_channel_fail_dlg_show
 *
 * Description:
 *      Show the usb popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _analog_channel_fail_dlg_show(VOID)
{
    INT32                       i4_ret  = MENUR_OK;

	if (!t_scan_info_atv.b_fail_dlg_show)
    {
        i4_ret = a_ui_simple_dialog_show(t_scan_info_atv.h_warn_fail_dlg);
        MENU_LOG_ON_FAIL(i4_ret);

        t_scan_info_atv.b_fail_dlg_show = TRUE;
    }

    if (t_scan_info_atv.b_suc_dlg_show)
    {
        i4_ret = a_ui_simple_dialog_hide(t_scan_info_atv.h_warn_suc_dlg);
        MENU_LOG_ON_FAIL(i4_ret);

        t_scan_info_atv.b_suc_dlg_show = FALSE;
    }

    a_ui_simple_dialog_repaint(t_scan_info_atv.h_warn_fail_dlg);
    a_ui_simple_dialog_set_focus(t_scan_info_atv.h_warn_fail_dlg, TRUE);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[256] = {0};

    c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_FAIL_DLG));
    c_uc_w2s_strcat(w2s_str, _TEXT("."));
    c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OK));

    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif

    //pt_page_data->b_is_dlg_show = TRUE;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _analog_channel_fail_dlg_yes_btn
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
static VOID _analog_channel_fail_dlg_yes_btn(VOID)
{
	INT32						i4_ret	= MENUR_OK;

	if (t_scan_info_atv.b_fail_dlg_show)
    {
    #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    #endif

        i4_ret = a_ui_simple_dialog_hide(t_scan_info_atv.h_warn_fail_dlg);
        MENU_LOG_ON_FAIL(i4_ret);

        t_scan_info_atv.b_fail_dlg_show = FALSE;
    }

    MENU_LOG_ON_FAIL( c_wgl_set_focus(h_channel_eb, WGL_SYNC_AUTO_REPAINT));

	//menu_nav_back();
}

extern INT32 a_analog_channel_fail_dlg_hide(VOID)
{
	INT32	i4_ret	= MENUR_OK;

    if (t_scan_info_atv.b_fail_dlg_show)
    {
    #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    #endif

        i4_ret = a_ui_simple_dialog_hide(t_scan_info_atv.h_warn_fail_dlg);
        MENU_LOG_ON_FAIL(i4_ret);

        t_scan_info_atv.b_fail_dlg_show = FALSE;
    }

	return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _analog_channel_fail_dlg_create
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
static INT32 _analog_channel_fail_dlg_create(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
	HANDLE_T		h_parent = NULL_HANDLE;


	i4_ret = menu_pm_get_root_frm(&h_parent);
	MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _analog_channel_fail_dlg_yes_btn;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;
	t_simple_dialog_init.b_one_btn_mode 				= TRUE;
	t_simple_dialog_init.b_info_icon					=TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                      			&t_scan_info_atv.h_warn_fail_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = a_ui_simple_dialog_set_text(t_scan_info_atv.h_warn_fail_dlg,
												  MENU_TEXT(MLM_MENU_KEY_MENU_ADD_ANALOG_CH_FAIL_DLG));
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = a_ui_simple_dialog_set_yes_text(t_scan_info_atv.h_warn_fail_dlg, MENU_TEXT( MLM_MENU_KEY_OK));
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _menu_edit_create_ex
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
INT32 _menu_edit_create_ex(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
){
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;

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
    t_inset.i4_left     = t_inset_border.i4_left + 90;
    t_inset.i4_right    = 20;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Cnt Insets */
    t_inset.i4_left     = 2;
    t_inset.i4_right    = 2;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
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
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_menu_img_text_entry_small;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)5),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    c_strcpy(t_title_info.t_font.a_c_font_name, menu_font_name());
    t_title_info.t_font.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_title_info.t_font.e_font_style = MENU_ITEM_FNT_STYLE;
    t_title_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_bk2_txt_disable;
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

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 _ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32             i4_ret = 0;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;

    i4_ret = menu_page_get_cnt_frm(_ui4_page_id,
                                   &h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);
/*
    i4_ret = menu_edit_create(h_cnt_frm,
                              0,
                              FALSE,
                              _channel_eb_fct,
                              &h_channel_eb);
                              */
    i4_ret = _menu_edit_create_ex(h_cnt_frm,
                              0,
                              _channel_eb_fct,
                              &h_channel_eb);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_action_create(h_cnt_frm,
                                1,
                                _start_scan_proc_fct,
                                &h_start_scan);
    MENU_LOG_ON_FAIL(i4_ret);
    /*
	i4_ret = menu_scan_pb_create(h_cnt_frm,2,NULL,&t_scan_pb);
    MENU_LOG_ON_FAIL(i4_ret);
    */
    ui4_style = WGL_STL_TEXT_MAX_128;

    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_RNG_PROG_TXT_W_1,
                     MENU_ITEM_V_HEIGHT*2,
                     ATSC_ADV_SCAN_RNG_PROG_TXT_W_2,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = menu_util_create_txt(h_cnt_frm,
                                  ui4_style,
                                  &t_rect,
                                  WGL_AS_LEFT_CENTER,
                                  &h_txt);

     MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

	c_memset(&t_scan_info_atv, 0, sizeof(ADD_ATV_SCAN_INFO_T));

	i4_ret = _analog_channel_fail_dlg_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _analog_channel_suc_dlg_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_timer_create(&t_scan_info_atv.h_timer);
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
	INT32	 i4_ret = 0;

	 if (NULL_HANDLE != t_scan_info_atv.h_warn_fail_dlg)
	{
		 i4_ret = a_ui_simple_dialog_destory(t_scan_info_atv.h_warn_fail_dlg);
		 MENU_LOG_ON_FAIL(i4_ret);
	}

	 if (NULL_HANDLE != t_scan_info_atv.h_warn_suc_dlg)
	 {
		  i4_ret = a_ui_simple_dialog_destory(t_scan_info_atv.h_warn_suc_dlg);
		  MENU_LOG_ON_FAIL(i4_ret);
	 }

	 if (NULL_HANDLE != t_scan_info_atv.h_timer)
	 {
		 i4_ret = c_timer_delete(t_scan_info_atv.h_timer);
		 MENU_LOG_ON_FAIL(i4_ret);
	 }

    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32           i4_ret=0;
    UINT8           ui1_align=0;
    HANDLE_T        h_menu_animation=NULL_HANDLE;
    GL_RECT_T       t_rect={0};
	GL_RECT_T       t_rect1 = {0};
	HANDLE_T		   h_last_shadow_item = NULL_HANDLE;

    a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    menu_main_set_title(MLM_MENU_KEY_ADD_ANALOG_SCAN_TITLE);

    /* Menu is in scanning status */
    if(ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
    {
        ui2_phy_ch_min  = PHY_TRSTRL_CH_NUM_MIN;
        ui2_phy_ch_max  = PHY_TRSTRL_CH_NUM_MAX;
    }
    else
    {
        ui2_phy_ch_min  = PHY_CABLE_CH_NUM_MIN;
        ui2_phy_ch_max  = PHY_CABLE_CH_NUM_MAX;
    }

    ui4_channel_num = ui2_phy_ch_min;
    b_scan_done = FALSE;

    i4_ret = menu_action_chg_lang(h_start_scan,
                                  MLM_MENU_KEY_ADD_ANALOG_SCAN_ADD,
                                  MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_edit_chg_lang(h_channel_eb, MLM_MENU_KEY_ADD_ANALOG_SCAN_EB);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _add_analog_ch_dlg_chg_lang();
	MENU_LOG_ON_FAIL(i4_ret);

	/*Adjust last shadow position*/
	c_wgl_get_coords(h_start_scan,WGL_COORDS_SCREEN,&t_rect1);
	t_rect.i4_top = t_rect1.i4_bottom;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
	MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_help_tip_keytip_show(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_align = (UINT8)WGL_NO_AUTO_REPAINT;
    i4_ret = c_wgl_insert (h_txt,
                NULL_HANDLE,
                WGL_INSERT_TOPMOST,
                ui1_align);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_scan_type (MENU_SCAN_TYPE_FULL_MODE);

    /* move animation widgets*/
    SET_RECT_BY_SIZE(&t_rect,
                     140*4/3,
                     150*4/3,
                     ICON_ANIMATION_W,
                     ICON_ANIMATION_H);

    i4_ret =  menu_page_animation_get_handle(&h_menu_animation);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_move(h_menu_animation, &t_rect, FALSE);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
	INT32  i4_ret = 0;
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    /* Menu is not in scanning status */
    t_g_menu_is_scanning = FALSE;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);


    MENU_LOG_ON_FAIL (menu_help_tip_keytip_show(TRUE));

    /* Broadcast the message to enable the EAS */
    menu_set_scan_type (MENU_SCAN_TYPE_UNKNOWN);

	/* stop the timer */
	i4_ret = c_timer_stop(t_scan_info_atv.h_timer);
	MENU_LOG_ON_FAIL(i4_ret);

	if(t_scan_info_atv.b_suc_dlg_show)
	{
	i4_ret = a_ui_simple_dialog_hide(t_scan_info_atv.h_warn_suc_dlg);
	MENU_LOG_ON_FAIL(i4_ret);
		t_scan_info_atv.b_suc_dlg_show = FALSE;

	}

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;

    b_scan = FALSE;

	i4_ret= _channel_eb_set_value(h_channel_eb,
                                 (UINT16)ui4_channel_num,
                                 FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set focuse on backbar */
    MENU_LOG_ON_FAIL( c_wgl_set_focus(h_channel_eb,WGL_NO_AUTO_REPAINT) );

    /* update help tip */
    MENU_LOG_ON_FAIL (_help_tip_update (_HELP_TIP_TYPE_BACKBAR));

    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct) ;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    return MENUR_OK;
}
#if 0
static INT32 _chg_lang(VOID)
{
    INT32   i4_ret = 0;

    /*Edite TXT*/
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_GUIDE_TXT)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

	/*Save TXT*/
	i4_ret = c_wgl_do_cmd(h_txt,
						   WGL_CMD_BTN_SET_TEXT,
						   WGL_PACK(MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_SAVE)),
						   WGL_PACK(c_uc_w2s_strlen(
						   MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_SAVE))));
	 MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;

}
#endif
static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    /* stop animation */
    menu_page_animation_stop();

    /* clean callback function of backbar & homebar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;
    MENU_LOG_ON_FAIL (menu_set_homebar_proc (NULL)) ;

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        _add_analog_ch_dlg_chg_lang();
    }
    return MENUR_OK;
}

extern INT32 menu_atsc_page_add_analog_scan_init(VOID)
{
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_add_analog_scan.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

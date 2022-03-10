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
 * $RCSfile: menu_page_inp_src.c,v $
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
#include "c_svctx.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "res/app_util/isl/a_isl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "nav/a_navigator.h"
#include "msgconvert/a_msgconvert.h"
#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_INP_SRC_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* Customizable part */

#ifndef INP_SRC_STL_SCROLL
    #define INP_SRC_STL_SCROLL    0
#endif

#ifndef INP_SRC_STL_WRAP_OVER
    #define INP_SRC_STL_WRAP_OVER 1
#endif

#ifndef INP_SRC_BACK_ON_LEFT
    #define INP_SRC_BACK_ON_LEFT  1
#endif

#ifndef INP_SRC_X
    #define INP_SRC_X            (0 * GRID_W)
#endif

#ifndef INP_SRC_Y
    #define INP_SRC_Y            (0 * GRID_H)
#endif

#ifndef INP_SRC_W
    #define INP_SRC_W           (MENU_ITEM_V_WIDE)
#endif

#ifndef INP_SRC_H
    #define INP_SRC_H           (CONTENT_H)
#endif

#ifndef INP_SRC_COL0_W
    #define INP_SRC_COL0_W       200
#endif

#ifndef INP_SRC_COL1_W
    #define INP_SRC_COL1_W       (INP_SRC_W - INP_SRC_COL0_W - INP_SRC_COL2_W)
#endif

#ifndef INP_SRC_COL2_W
    #define INP_SRC_COL2_W       80
#endif

/* layout */
/*
  +----------------------------------------------------+
  |   1   |    Component 1                 | lock icon |
  +----------------------------------------------------+
   COL0     COL1                            COL2
*/


#ifndef INP_SRC_ELEM_N
    #define INP_SRC_ELEM_N       16
#endif

#ifndef INP_SRC_ELEM_H
    #define INP_SRC_ELEM_H       GRID_H
#endif

#ifndef INP_SRC_COL0_ALIGN
    #define INP_SRC_COL0_ALIGN   WGL_AS_LEFT_CENTER
#endif

#ifndef INP_SRC_COL1_ALIGN
    #define INP_SRC_COL1_ALIGN   WGL_AS_LEFT_CENTER
#endif

#ifndef INP_SRC_COL2_ALIGN
    #define INP_SRC_COL2_ALIGN   WGL_AS_CENTER_CENTER
#endif

#define MAX_INP_NAME_LEN     40
#define MAX_INP_NUM_LEN      15


#define INP_ATTR_BIT_SET            MAKE_BIT_MASK_32(0)
#define INP_ATTR_BIT_SRC            MAKE_BIT_MASK_32(1)
#define INP_ATTR_BIT_PIP            MAKE_BIT_MASK_32(2)
#define INP_ATTR_BIT_SRC_ITEM       MAKE_BIT_MASK_32(3)


typedef enum _HELP_LST_STATE{
    HELP_LST_UP_ONLY = 0,
    HELP_LST_DOWN_ONLY,
    HELP_LST_UP_DOWN,
    HELP_LST_UNKNOWN
} HELP_LST_STATE;

typedef struct _INPUT_LIST_INIT_T{
    UINT16              ui2_msg_title;
    UINT32              ui4_sel_mask;
    WGL_HIMG_TPL_T      h_img_normal;
    WGL_HIMG_TPL_T      h_img_selected;
    WGL_HIMG_TPL_T      h_img_highlight;
    WGL_HIMG_TPL_T      h_img_selected_highlight;
    UINT16              ui2_max_rec_num;
    BOOL                b_scroll;       /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_SCROLL style */
    BOOL                b_wrap_over;    /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_WRAP_OVER */
    BOOL                b_back_on_left; /* Back to previous page by
                                           BTN_CURSOR_LEFT */
}INPUT_LIST_INIT_T;

typedef struct _INPUT_LIST_T
{
    UINT32                  ui4_page_id;
    INPUT_LIST_INIT_T       t_inp_lst_init;
    UINT8*                  pui1_idx_recid_map;
    HANDLE_T                h_lb_inp;
    BOOL                    b_is_refreshing;
}INPUT_LIST_T;

INPUT_LIST_T*      pt_inp_lst_tmp;

#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
typedef struct _INP_SRC_CEC_DEV_T
{
    UINT16            ui2_idx;
    UINT8             ui1_hdmi_idx;
}INP_SRC_CEC_DEV_T;

static INP_SRC_CEC_DEV_T  t_ipt_src_cec_dev[16];

#endif


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_inp_src;

/* use help tip instead of menu's help list */
static UINT16           gui2_lb_elem_num;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _inp_src_get_help_tip_string
 * Description: This API is use to get the help tip string by hlt index.
 * Input: arguments
 * Output: arguments
 * Returns:
 *---------------------------------------------------------------------------*/
UTF16_T* _inp_src_get_help_tip_string(UINT8 ui1_isl_id )
{
    INT32 i4_ret;
    UINT16 ui2_inp_tip_id = 0;
    ISL_REC_T t_isl_rec = {0};
    UINT32 ui4_page_id;

    menu_nav_get_crnt_page(&ui4_page_id);
#if 0
    if (ui4_page_id == ui4_page_inp_set)
    {
        return MENU_TEXT(MLM_MENU_KEY_INPUT_SOURCE_SEL);
    }
#endif
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
                    ui2_inp_tip_id = (t_isl_rec.ui1_iid_count <= 3 && MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP_HDMI_3 == ui2_inp_tip_id) ?
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
}

/*----------------------------------------------------------------------------
 * Name: _inp_src_set_attach_data
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
static INT32 _inp_src_set_attach_data(HANDLE_T            h_lb_inp,
                                      INPUT_LIST_T*     pt_inp_lst)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_inp_lst),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _inp_src_get_attach_data
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
static INT32 _inp_src_get_attach_data(HANDLE_T            h_lb_inp,
                                      INPUT_LIST_T**    ppt_inp_lst)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_inp_lst),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _inp_src_change(
    INPUT_LIST_T*        pt_inp_src)
{
    UINT16      ui2_idx;
    UINT16      ui2_total_num;
    INT32       i4_ret;
    ISL_REC_T   t_orig_src;
    UINT8       ui1_input_src_id = 0;
	UINT8       ui1_index;
	UINT8		ui1_num_rec;

	a_isl_get_num_rec(&ui1_num_rec);
    c_wgl_do_cmd(pt_inp_src->h_lb_inp,
                 WGL_CMD_LB_GET_HLT_INDEX,
                 WGL_PACK(&ui2_idx),
                 WGL_PACK(NULL));

    c_wgl_do_cmd(pt_inp_src->h_lb_inp,
                 WGL_CMD_LB_GET_ELEM_NUM,
                 WGL_PACK(&ui2_total_num),
                 WGL_PACK(NULL));

    c_memset(&t_orig_src, 0, sizeof(ISL_REC_T));

    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_orig_src);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_tv_set_last_input_src_id(TV_WIN_ID_MAIN, t_orig_src.ui1_id);
    MENU_CHK_FAIL(i4_ret);

    if(((pt_inp_src->t_inp_lst_init.ui4_sel_mask) & INP_ATTR_BIT_SRC) &&(ui2_idx == (ui2_total_num - 1)))
    {
        a_amb_resume_app(NAV_NAME);
    }
    else
    {
        if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
        {
            if (ui2_idx == 0)
            {
                return MENUR_OK;
            }
            else
            {
                ui1_input_src_id = (UINT8)ui2_idx - 1;
            }

        }
        else
        {
        	if(ui2_idx >= ui1_num_rec)
			{
				for(ui1_index = 0; ui1_index < 16; ui1_index++)
				{
					if(t_ipt_src_cec_dev[ui1_index].ui2_idx == ui2_idx)
					{
						ui1_input_src_id = t_ipt_src_cec_dev[ui1_index].ui1_hdmi_idx;
					}
				}
			}
			else
			{
            	ui1_input_src_id = (UINT8)ui2_idx;
			}
        }

        ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
            DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_cfg_av_set_input_src()\n", __FUNCTION__,__LINE__ ));
        );

        i4_ret = a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, ui1_input_src_id);

        if (i4_ret != APP_CFGR_OK)
        {
            return MENUR_FAIL;
        }

        if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
        {
            a_msg_convert_resume_navigator();
        }
        else
        {
            a_amb_resume_app(NAV_NAME);
        }
    }
    return MENUR_OK;
}

static INT32 _inp_src_change_in_menu(
    INPUT_LIST_T*        pt_inp_src)
{
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_num_rec;
    UINT16      ui2_idx;
    UINT8       ui1_input_src_id = 0;
	CEC_DEV_LST_T		t_lst;
	UINT8       ui1_index;

	c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
	a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

    c_wgl_do_cmd(pt_inp_src->h_lb_inp,
                 WGL_CMD_LB_GET_HLT_INDEX,
                 WGL_PACK(&ui2_idx),
                 WGL_PACK(NULL));

    a_isl_get_num_rec(&ui1_num_rec);
    if(ui2_idx >=  ui1_num_rec + t_lst.ui1_dev_num)
    {
        return MENUR_OK;
    }

	if(ui2_idx >= ui1_num_rec)
	{
		for(ui1_index = 0; ui1_index < 16; ui1_index++)
		{
			if(t_ipt_src_cec_dev[ui1_index].ui2_idx == ui2_idx)
			{
				ui1_input_src_id = t_ipt_src_cec_dev[ui1_index].ui1_hdmi_idx;
			}
		}
	}
	else
	{
    	ui1_input_src_id = (UINT8)ui2_idx;
	}

    a_isl_get_rec_by_idx(ui1_input_src_id, &t_isl_rec);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx,
                                 SVCTX_STRM_MODE_AS_LAST,
                                 &t_isl_rec,
                                 NULL);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_ch_lst2_on_notify
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
static INT32 _inp_src_on_notify(HANDLE_T    h_lb_inp,
                         WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_HLT:
        {
            INPUT_LIST_T*   pt_inp_lst=NULL;

            _inp_src_get_attach_data(h_lb_inp,
                                     &pt_inp_lst);

            /* If the CH_LIST is refreshing, do nothing */
            if(pt_inp_lst->b_is_refreshing)
            {
                return WMPR_DONE;
            }

            break;
        }
    default:
        break;
    }

    return WMPR_DONE;
}


static INT32 _inp_src_proc_fct(HANDLE_T            h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        {
            INT32           i4_ret;
            UINT16          ui2_hlt_idx;
            INPUT_LIST_T*   pt_inp_lst;
            UINT32          ui4_keycode = (UINT32)pv_param1;
            UINT16          ui2_elem_num;

            /* get the channel list data */
            i4_ret = _inp_src_get_attach_data(h_widget, &pt_inp_lst);
            if(i4_ret != MENUR_OK)
            {
                return WGLR_OK;
            }

            c_wgl_do_cmd(pt_inp_lst->h_lb_inp,
                           WGL_CMD_LB_GET_HLT_INDEX,
                           WGL_PACK(&ui2_hlt_idx),
                           WGL_PACK(NULL));

            c_wgl_do_cmd(pt_inp_lst->h_lb_inp,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&ui2_elem_num),
                         WGL_PACK(NULL));

            switch (ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                    return MENUR_OK;
                #endif
                case BTN_PREV_PRG:
                case BTN_RETURN:
                if(pt_inp_lst->t_inp_lst_init.b_back_on_left)
                {
                    menu_nav_back();
                    return WGLR_OK;
                }
                else
                {
                    /* simulate the page up */
                    pv_param1 = WGL_PACK(BTN_RED);
                }
                break;
                case BTN_CURSOR_RIGHT:
                case BTN_SELECT:
                {
                    UINT32 ui4_page_id;

                    menu_nav_get_crnt_page(&ui4_page_id);

                    if(ui4_page_id == ui4_g_menu_page_inp_src)
                    {
                        _inp_src_change(pt_inp_lst);
                    }
                    else if (ui4_page_id == ui4_page_inp_set)
                    {
                        _inp_src_change_in_menu(pt_inp_lst);
                        menu_nav_back();
                    }
                    else
                    {
                        menu_nav_go(ui4_g_menu_page_inp_naming, NULL);
                    }
                    return WGLR_OK;
                }

                case BTN_CURSOR_UP:
                {
                     if (0 == ui2_hlt_idx)
                     {
                        /* set focuse on backbar */
                        MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                     }
                     else
                     {
                        if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
                        {
                            if (1 == ui2_hlt_idx)
                            {
                                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                            }
                            else
                            {
                                menu_set_and_show_help_tip(_inp_src_get_help_tip_string(ui2_hlt_idx-2));
                            }
                        }
                        else
                        {
                            menu_set_and_show_help_tip(_inp_src_get_help_tip_string(ui2_hlt_idx-1));
                        }
                     }
                     break;
                }
                case BTN_CURSOR_DOWN:
                {
                    ui4_msg = WGL_MSG_KEY_DOWN;

                    if(ui2_hlt_idx == (ui2_elem_num -1))
                    {
                        menu_help_tip_keytip_set_focus(h_widget,
                                                       0,
                                                       FALSE);
                        menu_pm_repaint();
                        return MENUR_OK;
                    }
                    else
                    {
                        if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
                        {
                            menu_set_and_show_help_tip(_inp_src_get_help_tip_string(ui2_hlt_idx));
                        }
                        else
                        {
                            menu_set_and_show_help_tip(_inp_src_get_help_tip_string(ui2_hlt_idx + 1));
                        }
                    }
                    break;
                }

                default:
                    break;
            }
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _inp_src_add_inp
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
static INT32 _inp_src_add_inp(HANDLE_T            h_lb_inp,
                              INPUT_LIST_T*       pt_inp_lst,
                              ISL_REC_T*          pt_isl_rec)
{
   INT32   i4_ret=0;
   UINT16  ui2_idx=0;
   UTF16_T w2s_label[MAX_INP_NAME_LEN+1];
   UTF16_T w2s_name[MAX_INP_NAME_LEN+1];
   WGL_LB_ITEM_T at_items[2];
   CHAR        s_cust_lbl[MAX_INP_NAME_LEN+1];
   CHAR        s_source_lbl[MAX_INP_NAME_LEN+1];

    /* Get the display name of input source*/
    c_memset(w2s_name, 0, sizeof(w2s_name));
    c_uc_w2s_strncpy(w2s_name, a_isl_get_display_name(pt_isl_rec), MAX_INP_NAME_LEN);

    /*Lable*/
    c_memset(w2s_label, 0, sizeof(w2s_label));
    i4_ret = a_cfg_custom_get_inp_name(pt_isl_rec->ui1_id, s_cust_lbl);
    if (i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }

    /*If the custom name is the same as source name don't display*/
    c_uc_w2s_to_ps(a_isl_get_display_name(pt_isl_rec),
                   s_source_lbl,
                   MAX_INP_NAME_LEN);

    if(c_strcmp(s_cust_lbl, s_source_lbl) == 0)
    {
        w2s_label[0] = 0;
    }

    c_uc_ps_to_w2s(s_cust_lbl, w2s_label, MAX_INP_NAME_LEN);

    c_memset(at_items, 0, sizeof(at_items));

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;

    if (c_strncmp(s_source_lbl, "AV", c_strlen("AV")) == 0)
    {
        at_items[0].data.pw2s_text =  L" AV";
    }
    else
    {
        at_items[0].data.pw2s_text = w2s_name;
    }
    /*at_items[0].data.pw2s_text = w2s_name;*/
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_label;

    /* append item */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Get the index */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    ui2_idx -= 1;

    /* mapping */
    pt_inp_lst->pui1_idx_recid_map[ui2_idx] = pt_isl_rec->ui1_id;

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _inp_src_create
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
static INT32 _inp_src_create(HANDLE_T          h_parent,
                      INT32             i4_x,
                      INT32             i4_y,
                      INT32             i4_w,
                      INT32             i4_h,
                      INPUT_LIST_T*     pt_inp_lst,
                      HANDLE_T*         ph_lb_inp)
{
    INT32                   i4_ret;
    WGL_LB_INIT_T           t_lb_init;
    WGL_LB_COL_INIT_T       at_cols[2];
    GL_RECT_T               t_rect;
    WGL_LB_KEY_MAP_T        t_lb_key_map;
    WGL_FONT_INFO_T         t_fnt_info;
    WGL_INSET_T             t_elem_inset;
    WGL_LB_IMG_ELEM_SET_T   t_img_elem;
    UINT32                  ui4_col = 0;

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[0].ui2_max_text_len = MAX_INP_NUM_LEN;
    at_cols[0].ui2_width        = 110*4/3;

    /* channel name or starting time */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = MAX_INP_NAME_LEN;
    at_cols[1].ui2_width        = CONTENT_W - 110*4/3;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL;

    if(!pt_inp_lst->t_inp_lst_init.b_scroll)
    {
        t_lb_init.ui4_style         |= WGL_STL_LB_NO_SCROLL;
    }

    if(!pt_inp_lst->t_inp_lst_init.b_wrap_over)
    {
        t_lb_init.ui4_style         |= WGL_STL_LB_NO_WRAP_OVER;
    }

    t_lb_init.ui2_max_elem_num  = pt_inp_lst->t_inp_lst_init.ui2_max_rec_num;
    t_lb_init.ui2_elem_size     = 44;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      i4_x,
                      i4_y,
                      i4_w,
                      i4_h);

    i4_ret = menu_list2_create(h_parent,
                                &t_rect,
                                _inp_src_proc_fct,
                                & t_lb_init,
                                NULL,
                                ph_lb_inp);
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
            i4_ret = c_wgl_do_cmd (*ph_lb_inp,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK(ui4_col),
                                   WGL_PACK(&t_fnt_info));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set element insert */
    t_elem_inset.i4_left   = 10;
    t_elem_inset.i4_right  = 0;
    t_elem_inset.i4_top    = 15;
    t_elem_inset.i4_bottom = 15;
    i4_ret = c_wgl_do_cmd (*ph_lb_inp,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_elem_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_inp, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set background image */
    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_lb_inp,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* attach data */
    i4_ret = _inp_src_set_attach_data(*ph_lb_inp, pt_inp_lst);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_create_channel_list
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
static INT32   _inp_src_refresh(HANDLE_T   h_lb_inp)
{
    INT32         i4_ret      = MENUR_OK;
    INT32         i4_result;
    INPUT_LIST_T* pt_inp_lst;
    UINT8         ui1_rec_num;
    UINT8         ui1_idx = 0;
    ISL_REC_T     t_isl_rec;
    BOOL          b_skip;
	WGL_LB_ITEM_T at_items[2];
	UINT16  	  ui2_idx=0;

    /* get the channel list data */
    _inp_src_get_attach_data(h_lb_inp, &pt_inp_lst);
    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    /* Set the refreshing flag */
    pt_inp_lst->b_is_refreshing = TRUE;

    /* clear the list */
    i4_result = c_wgl_do_cmd(h_lb_inp,
                             WGL_CMD_LB_DEL_ALL,
                             NULL, NULL);
    MENU_LOG_ON_FAIL(i4_result);

    /* get record number */
    a_isl_get_num_rec(&ui1_rec_num);

    /* check if the record number exceeds the max channel number */
    if((UINT16)ui1_rec_num > pt_inp_lst->t_inp_lst_init.ui2_max_rec_num)
    {
        DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n",
                  ui1_rec_num, pt_inp_lst->t_inp_lst_init.ui2_max_rec_num));

       ui1_rec_num = (UINT8)pt_inp_lst->t_inp_lst_init.ui2_max_rec_num;
    }

    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        WGL_LB_ITEM_T at_items[2];

        c_memset(at_items, 0, sizeof(at_items));

        at_items[0].e_col_type = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text = L"VIA";
        at_items[1].e_col_type = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text = L" ";

        /* append item */
        i4_ret = c_wgl_do_cmd(h_lb_inp,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

    }

    for(ui1_idx = 0; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

        i4_result = _inp_src_add_inp(h_lb_inp,
                                     pt_inp_lst,
                                     &t_isl_rec);
        if (i4_result < 0)
        {
            i4_ret = i4_result;
            DBG_ERROR(("<MENU> Can't add input source to input source list.\r\n"));
            break;
        }
    }
	UINT8				ui1_count;
	UINT8				ui1_index = 0;
	CEC_DEV_LST_T		t_lst;
	UINT16          ui1_hdmi_src;

	c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
	a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

	if (t_lst.ui1_dev_num != 0)
	{
		for (ui1_count = 0; ui1_count < t_lst.ui1_dev_num; ui1_count++)
		{
			UTF16_T w2s_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
			c_uc_w2s_strncpy(w2s_name, L" ", APP_CFG_CUSTOM_INP_NAME_LEN);
			c_memset(at_items, 0, sizeof(at_items));

			at_items[0].e_col_type = LB_COL_TYPE_TEXT;
			at_items[0].data.pw2s_text = t_lst.at_dev_info[ui1_count].aw2_osd_name;
			at_items[1].e_col_type = LB_COL_TYPE_TEXT;
			at_items[1].data.pw2s_text = w2s_name;

			/* append item */
			i4_ret = c_wgl_do_cmd(h_lb_inp,
								  WGL_CMD_LB_APPEND_ELEM,
								  WGL_PACK(at_items),
								  NULL);
			MENU_LOG_ON_FAIL(i4_ret);

			/* Get the index */
			i4_ret = c_wgl_do_cmd(h_lb_inp,
								  WGL_CMD_LB_GET_ELEM_NUM,
								  WGL_PACK(&ui2_idx),
								  NULL);
			MENU_LOG_ON_FAIL(i4_ret);
			ui2_idx -= 1;

			c_memset (&t_isl_rec, 0, sizeof (ISL_REC_T));
            a_isl_get_rec_by_id(0, &t_isl_rec);

            while(t_isl_rec.e_src_type != INP_SRC_TYPE_AV ||
                  t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)
            {
                /* loop until HDMI is found */
                i4_ret = a_isl_iterate_rec(t_isl_rec.ui1_id,
                                  ISL_ITERATE_DIR_NEXT,
                                  &t_isl_rec);
                if( ISLR_OK != i4_ret)
                   return MENUR_FAIL;
            }

            ui1_hdmi_src = t_lst.at_dev_info[ui1_count].ui2_pa;
            ui1_hdmi_src = (ui1_hdmi_src >> 12) + t_isl_rec.ui1_id - 1;

			t_ipt_src_cec_dev[ui1_index].ui2_idx = ui2_idx;
			t_ipt_src_cec_dev[ui1_index].ui1_hdmi_idx = ui1_hdmi_src;
			ui1_index++;

			/* mapping */
			pt_inp_lst->pui1_idx_recid_map[ui2_idx] = ui1_hdmi_src;
		}
    }

    if(pt_inp_lst->t_inp_lst_init.ui4_sel_mask & INP_ATTR_BIT_SRC)
    {

       for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
       {
           a_cfg_get_input_src_skip(ui1_idx, &b_skip);
           if(b_skip){
              c_wgl_do_cmd(h_lb_inp,
                           WGL_CMD_LB_DISABLE_ELEM,
                           (VOID*)(UINT32)ui1_idx,
                           NULL);

           }
      }
   }


    /* Set the refreshing flag */
    pt_inp_lst->b_is_refreshing = FALSE;

    /* Set the total number to global */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&gui2_lb_elem_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _inp_src_hlt_curent_src
 *
 * Description:
 *  Highlight current playing channel
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _inp_src_hlt_curent_src(HANDLE_T h_lb_inp)
{
    INT32           i4_ret;
    INPUT_LIST_T*   pt_inp_lst;
    ISL_REC_T       t_isl_rec;
    ISL_REC_T       t_isl_rec_crnt;
    UINT8           ui1_rec_num;
    UINT8           ui1_idx;
    APP_TV_NET_SVC_STATUS t_svc_state = APP_TV_NET_SVC_STATUS_PAUSED;

    /* get the channel list data */
    _inp_src_get_attach_data(h_lb_inp, &pt_inp_lst);
    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    t_svc_state = a_tv_net_get_tv_svc_status();

    if (APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
    {
        ui1_idx = 0;
    }
    else
    {
        /* Get Input Source number */
        i4_ret = a_isl_get_num_rec(&ui1_rec_num);
        MENU_LOG_ON_FAIL(i4_ret);

        /* get the current svl record */
        i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Iterate the ISL */
        for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
        {
            i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);

            if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
            {
                break;
            }
        }


        if(ui1_idx == ui1_rec_num)
        {
            ui1_idx = 0;
        }
    }
    /* Highlight Element */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui1_idx),
                          WGL_PACK(ui1_idx % (UINT16)(CONTENT_H / GRID_H)));
    MENU_LOG_ON_FAIL(i4_ret);

    //if (ui4_page_inp_set != pt_inp_lst->ui4_page_id)
    {
        if (APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
        }
        else
        {
            menu_set_and_show_help_tip(_inp_src_get_help_tip_string(ui1_idx));
        }
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _frm_proc_fct
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
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{

    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;
            _inp_src_on_notify(h_source, pt_nfy_data);
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    INPUT_LIST_T*   pt_inp_lst = NULL;
    _inp_src_get_attach_data(pt_inp_lst_tmp->h_lb_inp, &pt_inp_lst);

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            /* set highlight of quick_operation & focus on it */
            c_wgl_do_cmd (pt_inp_lst_tmp->h_lb_inp ,
                                WGL_CMD_LB_HLT_ELEM ,
                                WGL_PACK(0) ,
                                NULL);
            c_wgl_set_focus (pt_inp_lst_tmp->h_lb_inp, WGL_SYNC_AUTO_REPAINT);

            if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            }
            else
            {
                menu_set_and_show_help_tip(_inp_src_get_help_tip_string(0));
            }

            break;

        case BTN_CURSOR_UP:
            /* set highlight of homebar & focus on it */
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT:
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32                i4_ret       = MENUR_FAIL;
    INPUT_LIST_T*        pt_inp_lst   = NULL;
    INPUT_LIST_INIT_T*   pt_inp_lst_init = (INPUT_LIST_INIT_T*)pv_create_data;
    HANDLE_T             h_cnt_frm;

    if(pt_inp_lst_init == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* Attach data */
    do
    {
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        pt_inp_lst = c_mem_alloc(sizeof(INPUT_LIST_T));

        if(pt_inp_lst == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        c_memset(pt_inp_lst, 0, sizeof(INPUT_LIST_T));

        c_memcpy(&pt_inp_lst->t_inp_lst_init,
                 pt_inp_lst_init,
                 sizeof(INPUT_LIST_INIT_T));

        pt_inp_lst->ui4_page_id = ui4_page_id;
        pt_inp_lst->pui1_idx_recid_map =
            c_mem_alloc(pt_inp_lst_init->ui2_max_rec_num * sizeof(UINT8));
        if(pt_inp_lst->pui1_idx_recid_map == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        i4_ret = menu_page_set_data(ui4_page_id, pt_inp_lst);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create input list box */
        i4_ret = _inp_src_create(h_cnt_frm,
                    INP_SRC_X,
                    INP_SRC_Y,
                    INP_SRC_W,
                    INP_SRC_H,
                    pt_inp_lst,
                    &pt_inp_lst->h_lb_inp);
        if(i4_ret != MENUR_OK)
        {
            break;
        }


        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }


        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = menu_page_set_proc_func(ui4_page_id,
                                         _cnt_frm_proc_fct);
        if(i4_ret != WGLR_OK)
        {
            break;
        }

    } while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_inp_lst != NULL)
        {
            if(pt_inp_lst->h_lb_inp != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_inp_lst->h_lb_inp);
            }
            if(pt_inp_lst->pui1_idx_recid_map != NULL)
            {
                c_mem_free(pt_inp_lst->pui1_idx_recid_map);
            }
            c_mem_free(pt_inp_lst);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    /* Pending */

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    INPUT_LIST_T* pt_inp_lst = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_lst);
    MENU_LOG_ON_FAIL(i4_ret);

    _inp_src_refresh(pt_inp_lst->h_lb_inp);

    _inp_src_hlt_curent_src(pt_inp_lst->h_lb_inp);

    menu_main_set_title(pt_inp_lst->t_inp_lst_init.ui2_msg_title);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    INPUT_LIST_T* pt_inp_lst = NULL;
    APP_TV_NET_SVC_STATUS t_svc_state;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_lst);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_inp_lst_tmp=pt_inp_lst;

    t_svc_state = a_tv_net_get_tv_svc_status();

    DBG_INFO(("t_svc_state=%d\n", (int)t_svc_state));

    c_wgl_set_focus(pt_inp_lst->h_lb_inp, WGL_NO_AUTO_REPAINT);

    menu_set_backbar_proc (_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    menu_set_backbar_proc(NULL);

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }
    return MENUR_OK;
}

extern INT32 menu_common_create_page_pip_inp_src(UINT32 *pui4_page_id)
{
    INPUT_LIST_INIT_T    t_inp_lst_init;

    c_memset(&t_inp_lst_init, 0, sizeof(INPUT_LIST_INIT_T));
    t_inp_lst_init.ui2_msg_title            = MLM_MENU_KEY_INPUT_SOURCE;
    t_inp_lst_init.ui2_max_rec_num          = INP_SRC_ELEM_N;
    t_inp_lst_init.h_img_normal             = NULL_HANDLE;
    t_inp_lst_init.h_img_highlight          = NULL_HANDLE;
    t_inp_lst_init.h_img_selected           = NULL_HANDLE;
    t_inp_lst_init.h_img_selected_highlight = NULL_HANDLE;
    t_inp_lst_init.ui4_sel_mask             = INP_ATTR_BIT_PIP;
    t_inp_lst_init.b_scroll                 = INP_SRC_STL_SCROLL;
    t_inp_lst_init.b_wrap_over              = INP_SRC_STL_WRAP_OVER;
    t_inp_lst_init.b_back_on_left           = INP_SRC_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_common_page_inp_src,
                               (VOID*)&t_inp_lst_init,
                               pui4_page_id);

}

extern INT32 menu_common_create_page_inp_src(UINT32 *pui4_page_id)
{
    INPUT_LIST_INIT_T    t_inp_lst_init;

    MENU_DEBUG_INPUT_SRC(DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset(&t_inp_lst_init, 0, sizeof(INPUT_LIST_INIT_T));
    t_inp_lst_init.ui2_msg_title            = MLM_MENU_KEY_INPUT_SOURCE_SEL;
    t_inp_lst_init.ui2_max_rec_num          = INP_SRC_ELEM_N;
    t_inp_lst_init.h_img_normal             = NULL_HANDLE;
    t_inp_lst_init.h_img_highlight          = NULL_HANDLE;
    t_inp_lst_init.h_img_selected           = NULL_HANDLE;
    t_inp_lst_init.h_img_selected_highlight = NULL_HANDLE;
    t_inp_lst_init.ui4_sel_mask             = INP_ATTR_BIT_PIP;
    t_inp_lst_init.b_scroll                 = INP_SRC_STL_SCROLL;
    t_inp_lst_init.b_wrap_over              = INP_SRC_STL_WRAP_OVER;
    t_inp_lst_init.b_back_on_left           = INP_SRC_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_common_page_inp_src,
                               (VOID*)&t_inp_lst_init,
                               pui4_page_id);

}

extern INT32 menu_common_create_page_inp_set(UINT32 *pui4_page_id)
{
    INPUT_LIST_INIT_T    t_inp_lst_init;

    MENU_DEBUG_INPUT_SRC(DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset(&t_inp_lst_init, 0, sizeof(INPUT_LIST_INIT_T));
    t_inp_lst_init.ui2_msg_title            = MLM_MENU_KEY_INPUT_SOURCE_SEL;
    t_inp_lst_init.ui2_max_rec_num          = INP_SRC_ELEM_N;
    t_inp_lst_init.h_img_normal             = NULL_HANDLE;
    t_inp_lst_init.h_img_highlight          = NULL_HANDLE;
    t_inp_lst_init.h_img_selected           = NULL_HANDLE;
    t_inp_lst_init.h_img_selected_highlight = NULL_HANDLE;
    t_inp_lst_init.ui4_sel_mask             = INP_ATTR_BIT_SRC_ITEM;
    t_inp_lst_init.b_scroll                 = INP_SRC_STL_SCROLL;
    t_inp_lst_init.b_wrap_over              = INP_SRC_STL_WRAP_OVER;
    t_inp_lst_init.b_back_on_left           = INP_SRC_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_common_page_inp_src,
                               (VOID*)&t_inp_lst_init,
                               pui4_page_id);

}

extern INT32 menu_common_page_inp_src_init(VOID)
{
    MENU_DEBUG_INPUT_SRC(DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    t_g_menu_common_page_inp_src.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_inp_src.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_inp_src.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_inp_src.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_inp_src.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_inp_src.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_inp_src.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_INP_SRC_ENABLE */


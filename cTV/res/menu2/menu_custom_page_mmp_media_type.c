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
#include "u_wgl_tools.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_fm.h"

#include "am/a_am.h"
#include "app_util/ui/_ui.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/a_menu_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "mmp/a_mmp.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"

#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "nav/banner2/a_banner.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN      ((INT32)128)

/* BUTTON */
#define MMP_MEDIA_TYPE_PAGE_BTN_X             (MENU_ITEM_V_LEFT)
#define MMP_MEDIA_TYPE_PAGE_BTN_Y             ((INT32)0*4/3)
#define MMP_MEDIA_TYPE_PAGE_BTN_W             (MENU_ITEM_V_WIDE)
#define MMP_MEDIA_TYPE_PAGE_BTN_H             (MENU_ITEM_V_HEIGHT)


typedef struct _MMP_MEDIA_TYPE_PAGE_DATA_T
{
    HANDLE_T            h_cnt_frm;
    HANDLE_T            h_audio_btn;
    HANDLE_T            h_video_btn;
    HANDLE_T            h_photo_btn;
    BOOL                b_g_is_show;
    UINT32              ui4_rmv_dev_nfy;
	CHAR                s_mnt_point[MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN];
    BOOL                b_g_is_enter;
} MMP_MEDIA_TYPE_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_mmp_media_type;

static MMP_MEDIA_TYPE_PAGE_DATA_T     t_g_mmp_media_type_page_data = {0};

#ifdef APP_TTS_SUPPORT
static UINT32 g_ui4_tts_play_id = 0;
#endif


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_update_title_text(VOID);

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static BOOL _mmp_media_type_page_is_current_device_removed(VOID)
{
	INT32		i4_ret = MENUR_OK;
	UINT32					ui4_idx;
	SIZE_T					z_size = MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN;
	CHAR					s_mnt_point[MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN] = {0};
	MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;

	i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_idx, &z_size, s_mnt_point);
	MENU_LOG_ON_FAIL(i4_ret);

	if (0 == c_strcmp(s_mnt_point, pt_this->s_mnt_point))
	{
		return FALSE;
	}

	return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_media_type_page_rmv_dev_nfy
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_media_type_page_rmv_dev_nfy(
                            VOID*               pv_tag,
                            RMV_DEV_NFY_ID_T    e_nfy_id,
                            VOID*               pv_nfy_param)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32       i4_ret = MENUR_OK;

    if (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
        if (TRUE == pt_this->b_g_is_show)
        {
            if (_mmp_media_type_page_is_current_device_removed())
            {
                if (ui4_g_menu_page_mmp_dev_list == menu_nav_get_pre_page_id_from_nav_stack())
			    {
				    menu_nav_back();
			    }
			    else
			    {
				    i4_ret = menu_nav_back_and_go(ui4_g_menu_page_mmp_dev_list, NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
			    }
                return;
            }
            else
            {
                i4_ret = _mmp_media_type_page_update_title_text();
                if (MENUR_OK != i4_ret)
                {
                    return;
                }
                i4_ret = menu_show_backbar(TRUE, TRUE);
                if (MENUR_OK != i4_ret)
                {
                    return;
                }
            }
        }
    }

    return;
}
/*----------------------------------------------------------------------------
 * Name:
 *      _mmp_media_type_page_homebar_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 ----------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_homebar_proc_fct(
                        HANDLE_T                    h_widget,
                        UINT32                      ui4_msg,
                        VOID*                       param1,
                        VOID*                       param2)
{
    INT32 i4_ret = MENUR_OK;
    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        /* hide old help tip first*/
        menu_hide_help_tip();
        /* trigger help tip */
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_SELECT:
        {
        #if 0 /* fix DTV00840292 exit mmp ui2_nav_stack_top = 0 ,menu_nav_back -> exit menu */
            if (ui4_g_menu_page_mmp_dev_list == menu_nav_get_pre_page_id_from_nav_stack())
			{
				menu_nav_back();
			}
			else
        #endif
			{
                i4_ret = menu_nav_back_and_go(ui4_g_menu_page_mmp_dev_list, NULL);
                MENU_LOG_ON_FAIL(i4_ret);
			}

        }
            break;
        case BTN_RETURN:
        {
        #if 0 /* fix DTV00840292 exit mmp ui2_nav_stack_top = 0 ,menu_nav_back -> exit menu */
			if (ui4_g_menu_page_mmp_dev_list == menu_nav_get_pre_page_id_from_nav_stack())
			{
				menu_nav_back();
			}
			else
        #endif
			{
				i4_ret = menu_nav_back_and_go(ui4_g_menu_page_mmp_dev_list, NULL);
                MENU_LOG_ON_FAIL(i4_ret);
			}
        }
            break;
        case BTN_CURSOR_DOWN:
        {
            i4_ret = menu_set_focus_on_backbar(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
        default :
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name:
 *      _mmp_media_type_page_backbar_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 ----------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_backbar_proc_fct (
                        HANDLE_T                    h_widget,
                        UINT32                      ui4_msg,
                        VOID*                       param1,
                        VOID*                       param2)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32 i4_ret = MENUR_OK;
    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_hide_help_tip();
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
    }

    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_SELECT:
        {
        #if 0 /* fix DTV00840292 exit mmp ui2_nav_stack_top = 0 ,menu_nav_back -> exit menu */
			if (ui4_g_menu_page_mmp_dev_list == menu_nav_get_pre_page_id_from_nav_stack())
			{
				menu_nav_back();
			}
			else
        #endif
			{
				i4_ret = menu_nav_back_and_go(ui4_g_menu_page_mmp_dev_list, NULL);
                MENU_LOG_ON_FAIL(i4_ret);
			}
        }
            break;
        case BTN_RETURN:
        {
        #if 0 /* fix DTV00840292 exit mmp ui2_nav_stack_top = 0 ,menu_nav_back -> exit menu */
			if (ui4_g_menu_page_mmp_dev_list == menu_nav_get_pre_page_id_from_nav_stack())
			{
				menu_nav_back();
			}
			else
        #endif
			{
				i4_ret = menu_nav_back_and_go(ui4_g_menu_page_mmp_dev_list, NULL);
                MENU_LOG_ON_FAIL(i4_ret);
			}
        }
            break;
        case BTN_CURSOR_DOWN:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            i4_ret = c_wgl_set_focus(pt_this->h_audio_btn, WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_MUSIC));
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif
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

/*----------------------------------------------------------------------------
 * Name:
 *      _mmp_media_type_page_homebar_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 ----------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_button_proc_fct(
                        HANDLE_T                    h_widget,
                        UINT32                      ui4_msg,
                        VOID*                       param1,
                        VOID*                       param2)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32 i4_ret = MENUR_OK;
#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        if (h_widget == pt_this->h_photo_btn)
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MMP_SIDER_MENU_PHOTO));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        }
        else if (h_widget == pt_this->h_video_btn)
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MMP_SIDER_MENU_VIDEO));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        }
        else if (h_widget == pt_this->h_audio_btn)
        {
            UTF16_T w2s_str_pause[32]={0};
            c_uc_w2s_strcpy(w2s_str_pause, L",");

            if(pt_this->b_g_is_enter)
            {
                pt_this->b_g_is_enter = FALSE;

                c_memset(w2s_str, 0, sizeof(w2s_str));
                c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MAIN_MENU_MMEDIA));

                c_uc_w2s_strncat(w2s_str,w2s_str_pause,c_uc_w2s_strlen(w2s_str_pause));
                c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC),
                                    c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC)));
            }
            else
            {
                c_memset(w2s_str, 0, sizeof(w2s_str));

                c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC));
                c_uc_w2s_strncat(w2s_str,w2s_str_pause,c_uc_w2s_strlen(w2s_str_pause));
                g_ui4_tts_play_id = a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
            }
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

        }

    }
#endif

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_SELECT :
        {
#ifdef APP_MMP_SUPPORT
            /* set mmp resume flag */
			a_menu_custom_set_resuming_mmp_flag(TRUE);

            if (pt_this->h_audio_btn == h_widget)
            {
                a_mmp_request_operation(MMP_REQ_OP_ENTER_AUDIO_BWR);
            }
#ifdef APP_MMP_VIDEO_PLAYBACK_ENABLE
            else if (pt_this->h_video_btn == h_widget)
            {
                a_mmp_request_operation(MMP_REQ_OP_ENTER_VIDEO_BWR);
            }
#endif
            else if (pt_this->h_photo_btn == h_widget)
            {
                a_mmp_request_operation(MMP_REQ_OP_ENTER_PHOTO_BWR);
            }
#endif
            i4_ret = a_amb_pause_app (MENU_NAME);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
        case BTN_CURSOR_DOWN :
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            if (h_widget == pt_this->h_photo_btn)
            {
                i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if (h_widget == pt_this->h_video_btn)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_PHOTO));
            }
            else if (h_widget == pt_this->h_audio_btn)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_VIDEO));
            }
        }
            break;
        case BTN_CURSOR_UP:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            if (h_widget == pt_this->h_audio_btn)
            {
                i4_ret = menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(h_widget == pt_this->h_video_btn)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_MUSIC));
            }
            else if(h_widget == pt_this->h_photo_btn)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_VIDEO));
            }
        }
            break;
        case BTN_RETURN:
        {
        #if 0 /* fix DTV00840292 exit mmp ui2_nav_stack_top = 0 ,menu_nav_back -> exit menu */
			if (ui4_g_menu_page_mmp_dev_list == menu_nav_get_pre_page_id_from_nav_stack())
			{
				menu_nav_back();
			}
			else
        #endif
			{
				i4_ret = menu_nav_back_and_go(ui4_g_menu_page_mmp_dev_list, NULL);
                MENU_LOG_ON_FAIL(i4_ret);
			}
        }
            break;
        default :
            break ;
        }
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        if (h_widget == pt_this->h_photo_btn)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_PHOTO));
        }
        else if (h_widget == pt_this->h_video_btn)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_VIDEO));
        }
        else if (h_widget == pt_this->h_audio_btn)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_MUSIC));
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_media_type_page_update_title_text
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 ----------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_update_title_text(VOID)
{
    RMV_DEV_DEVICE_STATUS_T  e_dev_status;
    INT32       i4_ret = MENUR_OK;
    CHAR        ac_path[MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN] = {0};
    CHAR        ac_info[MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T     w2s_dev_info[MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN] = {0};
    SIZE_T      z_size = MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN;
    UINT32      ui4_len = MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN;
    UINT32      ui4_idx = 0;

    i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_idx, &z_size, ac_path);
    MENU_LOG_ON_FAIL(i4_ret);

    /*query mount point status*/
    i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                ui4_idx,
                                &e_dev_status);
    MENU_LOG_ON_FAIL(i4_ret);

    if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
    {
        DBG_INFO(("\n%s,%s,%d,ui4_idx=%d,ac_path=%s,e_dev_status=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    ui4_idx, ac_path, e_dev_status));
        return MENUR_FAIL;
    }

    if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
    {
        z_size = MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN;
        i4_ret = a_rmv_dev_get_mnt_point_info(
                                ui4_idx,
                                RMV_DEV_INFO_ID_DESC,
                                &z_size,
                                (VOID*)(ac_info));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                       ac_path,
                                       ac_info,
                                       &ui4_len);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_uc_ps_to_w2s(ac_info, w2s_dev_info, MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_main_set_title_text(w2s_dev_info);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_media_type_page_set_button_text
 * Description:
 *      set button text.
 * Input arguments:
 *      h_button        button handle
 *      ui4_msg_id      language id
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 ----------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_set_button_text(
                    HANDLE_T                h_button,
                    UINT32                  ui4_msg_id)
{
    /*MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;*/
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_do_cmd(h_button,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK (MENU_TEXT(ui4_msg_id)),
                          WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(ui4_msg_id))));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_media_type_page_set_navigation
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_set_navigation(VOID)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32           i4_ret = MENUR_OK;
    WGL_KEY_LINK_T  at_key_lnk[2];
    c_memset(&at_key_lnk, 0 , sizeof(WGL_KEY_LINK_T)*2);

#ifdef APP_MMP_VIDEO_PLAYBACK_ENABLE
    at_key_lnk[0].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[0].h_widget = pt_this->h_video_btn;
    i4_ret = c_wgl_set_navigation(pt_this->h_audio_btn, 1, at_key_lnk);
    MENU_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_this->h_audio_btn;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_this->h_photo_btn;
    i4_ret = c_wgl_set_navigation(pt_this->h_video_btn, 2, at_key_lnk);
    MENU_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_this->h_video_btn;
    i4_ret = c_wgl_set_navigation(pt_this->h_photo_btn, 1, at_key_lnk);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    at_key_lnk[0].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[0].h_widget = pt_this->h_photo_btn;
    i4_ret = c_wgl_set_navigation(pt_this->h_audio_btn, 1, at_key_lnk);
    MENU_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_this->h_audio_btn;
    i4_ret = c_wgl_set_navigation(pt_this->h_photo_btn, 1, at_key_lnk);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_usb_pld_view_create_button
 * Description:
 *      create button.
 * Input arguments:
 *
 * Output arguments:
 *      ph_widget       pointer to button widget
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_media_type_page_create_button(
                    HANDLE_T                h_parent,
                    UINT32                  ui4_idx,
                    HANDLE_T*               ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    UINT32              ui4_style = 0;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_MEDIA_TYPE_PAGE_BTN_X,
                     MMP_MEDIA_TYPE_PAGE_BTN_Y + MMP_MEDIA_TYPE_PAGE_BTN_H * ui4_idx,
                     MMP_MEDIA_TYPE_PAGE_BTN_W,
                     MMP_MEDIA_TYPE_PAGE_BTN_H);

    if (NULL_HANDLE == h_parent)
    {
        return MENUR_FAIL;
    }

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _mmp_media_type_page_button_proc_fct,
                                255,
                                WGL_PACK(ui4_style),
                                WGL_PACK(NULL),
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;

    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set button background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_sidebar_highlight_v2;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set button text color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk2_txt_disable;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set text font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;

    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set button text alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =  c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#ifdef APP_TTS_SUPPORT
static VOID _mmp_media_type_tts_cb_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    DBG_LOG_PRINT(("menu mmp media type set banner tts enable %s,%d\n\r",__FILE__,__LINE__));
    set_banner_tts_enable(TRUE);
}


static VOID _mmp_media_type_tts_nfy(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag)
{
    if (TTS_STR_ST_PLAYED == e_tts_str_state &&
        g_ui4_tts_play_id == ui4_tts_play_id)
    {
        menu_request_context_switch(_mmp_media_type_tts_cb_fct,
                                    NULL,
                                    NULL,
                                    NULL);
    }
}
#endif


/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_create
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_create(
                    UINT32              ui4_page_id,
                    VOID*               pv_create_data)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MMP_VIDEO_PLAYBACK_ENABLE
    i4_ret = _mmp_media_type_page_create_button(
                                pt_this->h_cnt_frm,
                                0,
                                &pt_this->h_audio_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_set_button_text(
                                pt_this->h_audio_btn,
                                MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_create_button(
                                pt_this->h_cnt_frm,
                                1,
                                &pt_this->h_video_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_set_button_text(
                                pt_this->h_video_btn,
                                MLM_MENU_KEY_MMP_SIDER_MENU_VIDEO);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_create_button(
                                pt_this->h_cnt_frm,
                                2,
                                &pt_this->h_photo_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_set_button_text(
                                pt_this->h_photo_btn,
                                MLM_MENU_KEY_MMP_SIDER_MENU_PHOTO);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    i4_ret = _mmp_media_type_page_create_button(
                                pt_this->h_cnt_frm,
                                0,
                                &pt_this->h_audio_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_set_button_text(
                                pt_this->h_audio_btn,
                                MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_create_button(
                                pt_this->h_cnt_frm,
                                1,
                                &pt_this->h_photo_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_set_button_text(
                                pt_this->h_photo_btn,
                                MLM_MENU_KEY_MMP_SIDER_MENU_PHOTO);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = _mmp_media_type_page_set_navigation();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    i4_ret = a_app_tts_nfy_reg(_mmp_media_type_tts_nfy, NULL);
    if (APP_TTSR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[mmp media type] Can't  reg tts nfy"));
    }
#endif


    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_destroy
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_destroy(UINT32        ui4_page_id)
{
#ifdef APP_TTS_SUPPORT
    a_app_tts_nfy_unreg(_mmp_media_type_tts_nfy);
#endif
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_show
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_show(UINT32           ui4_page_id)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T      t_rect={0};
    GL_RECT_T      t_rect1={0};
    HANDLE_T          h_last_shadow_item = NULL_HANDLE;
    UINT32                  ui4_idx;
    SIZE_T                  z_size = MMP_MEDIA_TYPE_PAGE_MAX_NAME_LEN;

	i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_idx, &z_size, pt_this->s_mnt_point);
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_media_type_page_update_title_text();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_audio_btn, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    HANDLE_T        h_back_bar_frm = NULL_HANDLE;
    i4_ret = menu_get_backbar_handle(&h_back_bar_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_back_bar_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_get_coords(pt_this->h_photo_btn, WGL_COORDS_SCREEN, &t_rect);
    t_rect1.i4_top     = t_rect.i4_bottom;
    t_rect1.i4_bottom = t_rect.i4_bottom + MENU_ITEM_V_HEIGHT;
    t_rect1.i4_left    = CONTENT_X;
    t_rect1.i4_right   = CONTENT_X + CONTENT_H;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret=c_wgl_move(h_last_shadow_item, &t_rect1, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);


    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MMEDIA_BROWSE_MUSIC));

    i4_ret = menu_help_tip_keytip_show(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_g_is_show  = TRUE;

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_hide
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_hide(UINT32           ui4_page_id)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32       i4_ret = MENUR_OK;
    HANDLE_T     h_last_shadow_item = NULL_HANDLE;
    HANDLE_T        h_back_bar_frm = NULL_HANDLE;
    i4_ret = menu_get_backbar_handle(&h_back_bar_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_back_bar_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_help_tip_keytip_show(TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_g_is_show  = FALSE;

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_get_focus
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_get_focus(
                    UINT32              ui4_page_id,
                    MENU_PAGE_HINT_T*   pt_hint)
{
    INT32 i4_ret = MENUR_OK;

    /* set callback function for backbar */
    i4_ret = menu_set_backbar_proc(_mmp_media_type_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set callback function for homebar */
    i4_ret = menu_set_homebar_proc(_mmp_media_type_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_lose_focus
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_lose_focus(UINT32           ui4_page_id)
{
    INT32 i4_ret = MENUR_OK;

    /* set callback function for backbar */
    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set callback function for homebar */
    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _on_page_update
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _on_page_update(
                    UINT32              ui4_page_id,
                    UINT32              ui4_update_mask)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T* pt_this = &t_g_mmp_media_type_page_data;
    INT32 i4_ret=0;

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
#ifdef APP_MMP_VIDEO_PLAYBACK_ENABLE
        i4_ret = _mmp_media_type_page_set_button_text(
                                    pt_this->h_audio_btn,
                                    MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = _mmp_media_type_page_set_button_text(
                                    pt_this->h_video_btn,
                                    MLM_MENU_KEY_MMP_SIDER_MENU_VIDEO);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = _mmp_media_type_page_set_button_text(
                                    pt_this->h_photo_btn,
                                    MLM_MENU_KEY_MMP_SIDER_MENU_PHOTO);
        MENU_LOG_ON_FAIL(i4_ret);
#else
        i4_ret = _mmp_media_type_page_set_button_text(
                                    pt_this->h_audio_btn,
                                    MLM_MENU_KEY_MMP_SIDER_MENU_MUSIC);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = _mmp_media_type_page_set_button_text(
                                    pt_this->h_photo_btn,
                                    MLM_MENU_KEY_MMP_SIDER_MENU_PHOTO);
        MENU_LOG_ON_FAIL(i4_ret);
#endif
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      menu_custom_page_mmp_media_type_init
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
extern INT32 menu_custom_page_mmp_media_type_init(VOID)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T*     pt_this = &t_g_mmp_media_type_page_data;
    INT32       i4_ret = MENUR_OK;

    t_g_menu_custom_page_mmp_media_type.pf_menu_page_create      = _on_page_create;
    t_g_menu_custom_page_mmp_media_type.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_custom_page_mmp_media_type.pf_menu_page_show        = _on_page_show;
    t_g_menu_custom_page_mmp_media_type.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_custom_page_mmp_media_type.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_custom_page_mmp_media_type.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_custom_page_mmp_media_type.pf_menu_page_update      = _on_page_update;

    /* register remove device notification function */
    i4_ret = a_rmv_dev_reg_monitor(
                    _mmp_media_type_page_rmv_dev_nfy,
                    NULL,
                    &pt_this->ui4_rmv_dev_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      a_menu_custom_page_mmp_media_set_enter_flag
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
extern INT32 a_menu_custom_page_mmp_media_set_enter_flag(BOOL b_is_enter)
{
    MMP_MEDIA_TYPE_PAGE_DATA_T*     pt_this = &t_g_mmp_media_type_page_data;
    pt_this->b_g_is_enter = b_is_enter;
    return MENUR_OK;
}

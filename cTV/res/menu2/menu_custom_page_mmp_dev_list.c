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
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "mmp/a_mmp.h"
#include "mmp/mmp_mmc_device.h"

#include "app_util/rmv_dev/a_rmv_dev.h"
#include "res/app_util/model/model.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MMP_DEV_LIST_PAGE_MAX_DEV_NUM       ((INT32)100)
#define MMP_DEV_LIST_PAGE_MAX_NAME_LEN      ((INT32)128)

#define MMP_DEV_LIST_PAGE_TITLE_X           ((INT32)0)
#define MMP_DEV_LIST_PAGE_TITLE_Y           ((INT32)0)

#define MMP_DEV_LIST_PAGE_TITLE_W           (MENU_ITEM_V_WIDE)
#define MMP_DEV_LIST_PAGE_TITLE_H           ((INT32)25*4/3)

#define MMP_DEV_LIST_PAGE_MSG_TXT_X         ((INT32)0)
#define MMP_DEV_LIST_PAGE_MSG_TXT_Y         ((INT32)26*4/3)

#define MMP_DEV_LIST_PAGE_MSG_TXT_W         (MENU_ITEM_V_WIDE)
#define MMP_DEV_LIST_PAGE_MSG_TXT_H         (MENU_ITEM_V_HEIGHT)

#define MMP_DEV_LIST_PAGE_LIST_ELEM_H       (MENU_ITEM_V_HEIGHT)

#define MMP_DEV_LIST_PAGE_LIST_ELEM_NUM     ((INT32)8)

#define MMP_DEV_LIST_PAGE_DEV_LIST_X        ((INT32)0)
#define MMP_DEV_LIST_PAGE_DEV_LIST_Y        ((INT32)60*4/3)

#define MMP_DEV_LIST_PAGE_DEV_LIST_W        (MENU_ITEM_V_WIDE)

#define MMP_DEV_LIST_PAGE_DEV_LIST_H        (MMP_DEV_LIST_PAGE_LIST_ELEM_H*MMP_DEV_LIST_PAGE_LIST_ELEM_NUM)

#define MMP_DEV_LIST_PAGE_USB_DEV_NAME_W    (FRAME_LEFT_RIGHT_INTV + (INT32)75*4/3)

#define MMP_DEV_LIST_PAGE_USB_DEV_LABLE_W   (MMP_DEV_LIST_PAGE_DEV_LIST_W       \
                                             - MMP_DEV_LIST_PAGE_USB_DEV_NAME_W)

#ifdef SUPPORT_ONLY_ONE_USB_PORT
#define MMP_DEV_LIST_PAGE_USB_DEV_PREFIX    ("USB:")
#else
#define MMP_DEV_LIST_PAGE_USB_DEV_PREFIX    ("USB%d:")
#endif
#define MMP_DEV_LIST_PAGE_DLNA_DEV_PREFIX   ("DLNA%d:")

typedef enum _MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_T
{
    MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_DEFAULT = 0,
    MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_LAST_ELEM,
	MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_LAST_ENTRY
}MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_T;

typedef struct _MMP_DEV_LIST_PAGE_DATA_T
{
    HANDLE_T            h_cnt_frm;
    HANDLE_T            h_title_bar;
    HANDLE_T            h_title_text;
    HANDLE_T            h_msg_text;
    HANDLE_T            h_dev_list;
    UINT32              ui4_list_elem_num;
    UINT32              ui4_rmv_dev_nfy;
    BOOL                b_g_is_show;
	MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_T e_hlt_status;
} MMP_DEV_LIST_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_mmp_dev_list;

static MMP_DEV_LIST_PAGE_DATA_T     t_g_mmp_dev_list_page_data = {0};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_update_dev_list(VOID);
#ifdef APP_TTS_SUPPORT
static INT32 _mmp_dev_list_page_dev_list_tts_play(UINT16    ui2_elem_hlt_idx );

#endif
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_rmv_dev_nfy
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
static VOID _mmp_dev_list_page_rmv_dev_nfy(
                            VOID*               pv_tag,
                            RMV_DEV_NFY_ID_T    e_nfy_id,
                            VOID*               pv_nfy_param)
{
    MMP_DEV_LIST_PAGE_DATA_T*     pt_this = &t_g_mmp_dev_list_page_data;
    INT32       i4_ret = MENUR_OK;

    if ((RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)||
        (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id))
    {
        if (TRUE == pt_this->b_g_is_show)
        {
            i4_ret = _mmp_dev_list_page_update_dev_list();
            if (MENUR_OK != i4_ret)
            {
                return;
            }

            i4_ret = menu_pm_repaint();
            if (MENUR_OK != i4_ret)
            {
                return;
            }
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_msg_text_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_msg_text_proc_fct(HANDLE_T   h_widget,
                                                  UINT32     ui4_msg,
                                                  VOID*      param1,
                                                  VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }
        break;
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_dev_select_fct
 * Description:
 *      select device handle function
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_dev_list_page_dev_select_fct(VOID*        pv_data,
                                              SIZE_T       z_data_size)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_nav_go(ui4_g_menu_page_mmp_media_type, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_dev_list_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_dev_list_proc_fct(HANDLE_T   h_widget,
                                                  UINT32     ui4_msg,
                                                  VOID*      param1,
                                                  VOID*      param2)
{
    MMP_DEV_LIST_PAGE_DATA_T*     pt_this = &t_g_mmp_dev_list_page_data;
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_elem_hlt_idx = 0;
    UINT32      ui4_idx = 0;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
	{
		if (pt_this->e_hlt_status == MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_LAST_ELEM)
		{
			ui2_elem_hlt_idx =  pt_this->ui4_list_elem_num - 1;
			i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
	                              WGL_CMD_LB_HLT_ELEM,
	                              WGL_PACK(ui2_elem_hlt_idx),
	                              NULL);
		    MENU_LOG_ON_FAIL(i4_ret);
			pt_this->e_hlt_status = MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_DEFAULT;
		}
    #ifdef APP_TTS_SUPPORT
        ui2_elem_hlt_idx = 0;
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_elem_hlt_idx),
                              WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);
        _mmp_dev_list_page_dev_list_tts_play(ui2_elem_hlt_idx);
    #endif
	}
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_elem_hlt_idx),
                                      WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                if(ui2_elem_hlt_idx > pt_this->ui4_list_elem_num - 1)
                {
                    return MENUR_FAIL;
                }
                else
                {
                    i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
                                          WGL_CMD_LB_GET_ELEM_TAG,
                                          WGL_PACK(ui2_elem_hlt_idx),
                                          WGL_PACK(&ui4_idx));
                    MENU_LOG_ON_FAIL(i4_ret);

                    if(MENUR_OK == i4_ret)
                    {
                        i4_ret = a_rmv_dev_set_active_mnt_pnt(ui4_idx);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = menu_async_invoke(_mmp_dev_list_page_dev_select_fct, NULL, 0, TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
            }
                break;
            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_elem_hlt_idx),
                                      WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                if(ui2_elem_hlt_idx == pt_this->ui4_list_elem_num - 1)
                {
                    pt_this->e_hlt_status = MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_LAST_ELEM;
					i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            #ifdef APP_TTS_SUPPORT
                ui2_elem_hlt_idx += 1;
                if(ui2_elem_hlt_idx > pt_this->ui4_list_elem_num)
                {
                    break;
                }
                _mmp_dev_list_page_dev_list_tts_play(ui2_elem_hlt_idx);
            #endif
            }
                break;
        #ifdef APP_TTS_SUPPORT
            case BTN_CURSOR_UP:
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_elem_hlt_idx),
                                      WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_elem_hlt_idx -= 1;
                if((INT16)ui2_elem_hlt_idx < 0)
                {
                    ui2_elem_hlt_idx = pt_this->ui4_list_elem_num - 1;
                }
                _mmp_dev_list_page_dev_list_tts_play(ui2_elem_hlt_idx);
                break;
            }
        #endif
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
 * Name
 *      _mmp_dev_list_page_get_usb_dev_serial_name
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_get_usb_dev_serial_name(
                            UINT32              ui4_idx,
                            UTF16_T*            ws_text)
{
    INT32   i4_ret = MENUR_OK;
    CHAR    ac_temp[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
#ifdef SUPPORT_ONLY_ONE_USB_PORT
    c_strncpy(ac_temp, "USB:", MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
#else
    UINT8   ui1_usb_port_num = a_get_usb_port_num_by_model();
    if (ui1_usb_port_num > 1)
    {
        c_sprintf(ac_temp, MMP_DEV_LIST_PAGE_USB_DEV_PREFIX, ui4_idx + 1);
    }
    else if (1 == ui1_usb_port_num)
    {
        c_strncpy(ac_temp, "USB:", MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
    }
    else
    {
        DBG_INFO(("\n%s,%s,%d,ui1_usb_port_num=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, ui1_usb_port_num));
    }
#endif

    i4_ret = c_uc_ps_to_w2s(ac_temp, ws_text, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_get_dlna_dev_serial_name
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_get_dlna_dev_serial_name(
                            UINT32              ui4_idx,
                            UTF16_T*            ws_text)
{
    INT32   i4_ret = MENUR_OK;
    CHAR    ac_temp[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};

    c_sprintf(ac_temp, MMP_DEV_LIST_PAGE_DLNA_DEV_PREFIX, ui4_idx + 1);

    i4_ret = c_uc_ps_to_w2s(ac_temp, ws_text, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_update_dlna_list
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_update_dlna_list(UINT32         ui4_mnt_point_idx,
                                                              UINT32        ui4_dlna_id,
                                                              UINT32        ui4_not_care_dev_count)

{
    MMP_DEV_LIST_PAGE_DATA_T*     pt_this = &t_g_mmp_dev_list_page_data;
    INT32           i4_ret = MENUR_OK;
    WGL_LB_ITEM_T   at_items[2];
    SIZE_T          z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
    CHAR            ac_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T         w2s_dev_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T         w2s_dev_serial_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};

    i4_ret = _mmp_dev_list_page_get_dlna_dev_serial_name(ui4_dlna_id, w2s_dev_serial_name);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_rmv_dev_get_mnt_point_info(
                            ui4_mnt_point_idx,
                            RMV_DEV_INFO_ID_DESC,
                            &z_size,
                            (VOID*)(ac_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_uc_ps_to_w2s(ac_info, w2s_dev_info, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&at_items, 0 , sizeof(WGL_LB_ITEM_T)*2);
    at_items[0].e_col_type     = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_dev_serial_name;
    at_items[1].e_col_type     = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_dev_info;

    i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
                          WGL_CMD_LB_SET_ELEM_TAG,
                          WGL_PACK(ui4_mnt_point_idx-ui4_not_care_dev_count),
                          WGL_PACK(ui4_mnt_point_idx));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui4_list_elem_num++;

    return MENUR_OK;

}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_update_usb_list
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_update_usb_list(
                            UINT32         ui4_mnt_point_idx,
                            UINT32         ui4_usb_id,
                            UINT32         ui4_not_care_dev_count)

{
    MMP_DEV_LIST_PAGE_DATA_T*     pt_this = &t_g_mmp_dev_list_page_data;
    INT32           i4_ret = MENUR_OK;
    WGL_LB_ITEM_T   at_items[2];
    UTF16_T         w2s_dev_serial_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    CHAR            ac_path[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UINT32          ui4_len = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
    SIZE_T          z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
    CHAR            ac_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T         w2s_dev_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UINT16          ui2_name_len = 0;

    i4_ret = _mmp_dev_list_page_get_usb_dev_serial_name(ui4_mnt_point_idx, w2s_dev_serial_name);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_rmv_dev_get_mnt_point(ui4_mnt_point_idx,
                                     &z_size,
                                     ac_path);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                   ac_path,
                                   ac_info,
                                   &ui4_len);
    MENU_LOG_ON_FAIL(i4_ret);

    /* clean invalid char " . Some USB brand has the invaild char in the last of string.
           This character colud input in the label. */
    ui2_name_len = c_strlen(ac_info);
    if((ui2_name_len < MMP_DEV_LIST_PAGE_MAX_NAME_LEN) && (ui2_name_len > 0))
    {
        if(ac_info[ui2_name_len - 1] == 0x22)
        {
            ac_info[ui2_name_len - 1] = 0;
        }
    }

    i4_ret = c_uc_ps_to_w2s(ac_info, w2s_dev_info, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&at_items, 0 , sizeof(WGL_LB_ITEM_T)*2);
    at_items[0].e_col_type     = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_dev_serial_name;
    at_items[1].e_col_type     = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_dev_info;

    i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
                          WGL_CMD_LB_SET_ELEM_TAG,
                          WGL_PACK(ui4_mnt_point_idx-ui4_not_care_dev_count),
                          WGL_PACK(ui4_mnt_point_idx));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui4_list_elem_num++;

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_update_dev_list
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_update_dev_list(VOID)
{
    MMP_DEV_LIST_PAGE_DATA_T*     pt_this = &t_g_mmp_dev_list_page_data;
    pt_this->ui4_list_elem_num = 0;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    INT32           i4_ret = MENUR_OK;
    UINT32          ui4_mnt_count = 0;
    UINT32          ui4_usb_id = 0;
    UINT32          ui4_dlna_id = 0;
    UINT32          ui4_mnt_point_idx = 0;
    UINT32          ui4_not_care_dev_count = 0;
    CHAR            s_mnt_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN + 1] = {0};
    SIZE_T          z_size = 0;

    /* delete all list elem */
    i4_ret = c_wgl_do_cmd(pt_this->h_dev_list,
                          WGL_CMD_LB_DEL_ALL,
                          WGL_PACK(NULL),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            ui4_not_care_dev_count++;
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            DBG_INFO(("\n%s,%dui4_mnt_point_idx=%d, current is dlna device,\
                       ui4_dlna_id=%d,\
                       ui4_not_care_dev_count=%d\n",
                       __FILE__, __LINE__,
                       ui4_mnt_point_idx,
                       ui4_dlna_id,
                       ui4_not_care_dev_count));
            if (FALSE == a_is_DLNA_enable())
            {
                ui4_not_care_dev_count++;
                DBG_INFO(("\n%s,%dui4_mnt_point_idx=%d, current is do not care\
                           mount point, ui4_not_care_dev_count=%d\n",
                           __FILE__, __LINE__,
                           ui4_mnt_point_idx,
                           ui4_not_care_dev_count));
                continue;
            }

            z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
            i4_ret = a_rmv_dev_get_mnt_point_info(
                                    ui4_mnt_point_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
            MENU_LOG_ON_FAIL(i4_ret);

        #ifdef DEBUG
            DBG_INFO(("\n%s,%s,%d,ui4_mnt_point_idx=%d,s_mnt_name=%s\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        ui4_mnt_point_idx, s_mnt_name));
        #endif

            if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
            {
                DBG_INFO(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                             __FILE__, __FUNCTION__, __LINE__));
                ui4_not_care_dev_count++;
                continue;
            }

            i4_ret = _mmp_dev_list_page_update_dlna_list(ui4_mnt_point_idx,
                                                         ui4_dlna_id,
                                                         ui4_not_care_dev_count);
            if(MENUR_OK != i4_ret)
            {
                continue;
            }
            ui4_dlna_id++;
        }
        else
        {
            i4_ret = _mmp_dev_list_page_update_usb_list(ui4_mnt_point_idx,
                                                        ui4_usb_id,
                                                        ui4_not_care_dev_count);
            if(MENUR_OK != i4_ret)
            {
                continue;
            }
            ui4_usb_id++;
        }
    }

    /* no device */
    if (0 == (ui4_dlna_id+ui4_usb_id))
    {
        i4_ret = c_wgl_enable(pt_this->h_msg_text, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_help_tip_keytip_set_focus(NULL_HANDLE, 0, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        return i4_ret;
    }
    else
    {
        i4_ret = c_wgl_enable(pt_this->h_msg_text, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_focus(pt_this->h_dev_list, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

#ifdef DEBUG
    DBG_INFO(("\ns_mnt_name=%s,size=%d\n",
                s_mnt_name, sizeof(s_mnt_name)));
#endif

    return MENUR_OK;
}
#ifdef APP_TTS_SUPPORT
/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_dev_list_tts_play
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_dev_list_tts_play(UINT16      ui2_elem_hlt_idx )
{
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    INT32           i4_ret = MENUR_OK;
    UINT32          ui4_mnt_count = 0;
    UINT32          ui4_usb_id = 0;
    UINT32          ui4_dlna_id = 0;
    UINT32          ui4_mnt_point_idx = 0;
    UINT32          ui4_not_care_dev_count = 0;
    CHAR            s_mnt_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN + 1] = {0};
    UTF16_T         w2s_dev_serial_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T         w2s_dev_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T         w2s_tts_str[MMP_DEV_LIST_PAGE_MAX_NAME_LEN + MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    SIZE_T          z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            ui4_not_care_dev_count++;
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            DBG_INFO(("\n%s,%dui4_mnt_point_idx=%d, current is dlna device,\
                       ui4_dlna_id=%d,\
                       ui4_not_care_dev_count=%d\n",
                       __FILE__, __LINE__,
                       ui4_mnt_point_idx,
                       ui4_dlna_id,
                       ui4_not_care_dev_count));
            if (FALSE == a_is_DLNA_enable())
            {
                ui4_not_care_dev_count++;
                DBG_INFO(("\n%s,%dui4_mnt_point_idx=%d, current is do not care\
                           mount point, ui4_not_care_dev_count=%d\n",
                           __FILE__, __LINE__,
                           ui4_mnt_point_idx,
                           ui4_not_care_dev_count));
                continue;
            }

            i4_ret = a_rmv_dev_get_mnt_point_info(
                                    ui4_mnt_point_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
            MENU_LOG_ON_FAIL(i4_ret);

            if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
            {
                DBG_INFO(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                             __FILE__, __FUNCTION__, __LINE__));
                ui4_not_care_dev_count++;
                continue;
            }

            if(ui2_elem_hlt_idx == ui4_mnt_point_idx-ui4_not_care_dev_count)
            {
                i4_ret = _mmp_dev_list_page_get_dlna_dev_serial_name(ui4_dlna_id, w2s_dev_serial_name);
                MENU_LOG_ON_FAIL(i4_ret);

                c_uc_w2s_strcpy(w2s_tts_str,w2s_dev_serial_name);
                c_uc_ps_to_w2s(s_mnt_name, w2s_dev_info, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
                c_uc_w2s_strcat(w2s_tts_str,w2s_dev_info);
                a_app_tts_play(w2s_tts_str,c_uc_w2s_strlen(w2s_tts_str));

                break;
            }
            ui4_dlna_id++;

        }
        else
        {
            if(ui2_elem_hlt_idx == ui4_mnt_point_idx-ui4_not_care_dev_count)
            {
                CHAR            ac_path[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
                CHAR            ac_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
                UINT32          ui4_len = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
                UINT16          ui2_name_len = 0;

                i4_ret = _mmp_dev_list_page_get_usb_dev_serial_name(ui4_mnt_point_idx, w2s_dev_serial_name);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = a_rmv_dev_get_mnt_point(ui4_mnt_point_idx,
                                     &z_size,
                                     ac_path);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                               ac_path,
                                               ac_info,
                                               &ui4_len);
                MENU_LOG_ON_FAIL(i4_ret);

                /* clean invalid char " . Some USB brand has the invaild char in the last of string.
                       This character colud input in the label. */
                ui2_name_len = c_strlen(ac_info);
                if((ui2_name_len < MMP_DEV_LIST_PAGE_MAX_NAME_LEN) && (ui2_name_len > 0))
                {
                    if(ac_info[ui2_name_len - 1] == 0x22)
                    {
                        ac_info[ui2_name_len - 1] = 0;
                    }
                }

                i4_ret = c_uc_ps_to_w2s(ac_info, w2s_dev_info, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
                MENU_LOG_ON_FAIL(i4_ret);

                c_uc_w2s_strcpy(w2s_tts_str,w2s_dev_serial_name);
                c_uc_w2s_strcat(w2s_tts_str,w2s_dev_info);
                a_app_tts_play(w2s_tts_str,c_uc_w2s_strlen(w2s_tts_str));

                break;
            }
            ui4_usb_id++;
        }
    }

    return MENUR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_create_title_bar
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_create_title_bar(
                            HANDLE_T                h_parent,
                            HANDLE_T*               ph_widget)
{
    INT32           i4_ret = MENUR_OK;
    UINT32          ui4_style = 0;
    GL_RECT_T       t_rect;
    WGL_IMG_INFO_T  t_img_info;

    if (NULL_HANDLE == h_parent)
    {
        return MENUR_INV_ARG;
    }

    /* create home title*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_DEV_LIST_PAGE_TITLE_X,
                     MMP_DEV_LIST_PAGE_TITLE_Y,
                     MMP_DEV_LIST_PAGE_TITLE_W,
                     MMP_DEV_LIST_PAGE_TITLE_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 (UINT8)255,
                                 WGL_PACK(ui4_style),
                                 WGL_PACK(NULL),
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable      = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =  c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_create_title_text
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_create_title_text(
                        HANDLE_T                h_parent,
                        HANDLE_T*               ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    WGL_INSET_T         t_inset;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    if (NULL_HANDLE == h_parent)
    {
        return MENUR_INV_ARG;
    }

    /* create home title*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_DEV_LIST_PAGE_TITLE_X,
                     MMP_DEV_LIST_PAGE_TITLE_Y,
                     MMP_DEV_LIST_PAGE_TITLE_W,
                     MMP_DEV_LIST_PAGE_TITLE_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 (UINT8)255,
                                 WGL_PACK(WGL_STL_GL_NO_IMG_UI|
                                 WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left   = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set text color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
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

    t_fnt_info.e_font_size  = TITLE_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 28;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =  c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_create_msg_text
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_create_msg_text(
                        HANDLE_T                h_parent,
                        HANDLE_T*               ph_widget)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    WGL_IMG_INFO_T  t_img_info;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_INSET_T t_inset_border =
    {
        0,
        0,
        4*4/3,
        0
    };

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_DEV_LIST_PAGE_MSG_TXT_X,
                     MMP_DEV_LIST_PAGE_MSG_TXT_Y,
                     MMP_DEV_LIST_PAGE_MSG_TXT_W,
                     MMP_DEV_LIST_PAGE_MSG_TXT_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 _mmp_dev_list_page_msg_text_proc_fct,
                                 (UINT8)255,
                                 WGL_PACK(WGL_STL_TEXT_MAX_128 |
                                          WGL_STL_GL_NO_BK),
                                 WGL_PACK(NULL),
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          WGL_PACK(&t_inset_border),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(
                        *ph_widget,
                        WGL_CMD_TEXT_SET_ALIGN,
                        WGL_PACK(WGL_AS_CENTER_CENTER),
                        WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
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

    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_bk2_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_menu_img_text_sep;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_dev_list_page_set_text_text
 * Description:
 *      set text text.
 * Input arguments:
 *      h_button        button handle
 *      ui4_msg_id      language id
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 ----------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_set_text_text(
                    HANDLE_T                h_widget,
                    UINT32                  ui4_msg_id)
{
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (MENU_TEXT(ui4_msg_id)),
                          WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(ui4_msg_id))));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_dev_list_page_create_dev_list
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_dev_list_page_create_dev_list(
                        HANDLE_T                h_parent,
                        HANDLE_T*               ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_LB_COL_INIT_T   at_cols[2];
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      MMP_DEV_LIST_PAGE_DEV_LIST_X,
                      MMP_DEV_LIST_PAGE_DEV_LIST_Y,
                      MMP_DEV_LIST_PAGE_DEV_LIST_W,
                      MMP_DEV_LIST_PAGE_DEV_LIST_H);

    c_memset(&at_cols, 0, sizeof(WGL_LB_COL_INIT_T)*2);

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 128;
    at_cols[0].ui2_width        = MMP_DEV_LIST_PAGE_USB_DEV_NAME_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = 128;
    at_cols[1].ui2_width        = MMP_DEV_LIST_PAGE_USB_DEV_LABLE_W;

    c_memset(&t_lb_init, 0, sizeof(WGL_LB_INIT_T));
    t_lb_init.ui4_style         =  WGL_STL_LB_FORCE_HLT |
                                   WGL_STL_LB_ELEM_NO_PUSH |
                                   WGL_STL_GL_NO_BK;

    t_lb_init.ui2_max_elem_num  = MMP_DEV_LIST_PAGE_MAX_DEV_NUM;
    t_lb_init.ui2_elem_size     = MMP_DEV_LIST_PAGE_LIST_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _mmp_dev_list_page_dev_list_proc_fct,
                                 (UINT8)255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          WGL_PACK(&t_inset),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(1),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(0),
                          WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(1),
                          WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set text color */
    c_memset(&t_lb_color, 0, sizeof(WGL_COLOR_INFO_T));
    t_lb_color.t_normal             = t_g_menu_color_bk2_txt;
    t_lb_color.t_disable            = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight          = t_g_menu_color_bk2_txt;
    t_lb_color.t_pushed             = t_g_menu_color_bk2_txt;
    t_lb_color.t_selected           = t_g_menu_color_bk2_txt;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_bk2_txt;
    t_lb_color.t_selected_disable   = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set text color */
    c_memset(&t_lb_color, 0, sizeof(WGL_COLOR_INFO_T));
    t_lb_color.t_normal             = t_g_menu_color_bk2_txt;
    t_lb_color.t_disable            = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight          = t_g_menu_color_bk2_txt;
    t_lb_color.t_pushed             = t_g_menu_color_bk2_txt;
    t_lb_color.t_selected           = t_g_menu_color_bk2_txt;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_bk2_txt;
    t_lb_color.t_selected_disable   = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_elem, 0 , sizeof(WGL_LB_IMG_ELEM_SET_T));
    t_img_elem.h_normal            = NULL_HANDLE;
    t_img_elem.h_disable           = NULL_HANDLE;
    t_img_elem.h_highlight         = h_g_menu_common_sidebar_highlight_v2;

    t_img_elem.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem.h_pushed            = NULL_HANDLE;
    t_img_elem.h_selected          = NULL_HANDLE;
    t_img_elem.h_selected_disable  = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(&t_img_elem),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set long text scroll effect */
    c_memset(&t_hlt_elem_effect, 0 , sizeof(WGL_LB_HLT_ELEM_EFFECT_T));
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                          WGL_PACK(&t_hlt_elem_effect),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =  c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

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
    MMP_DEV_LIST_PAGE_DATA_T* pt_this = &t_g_mmp_dev_list_page_data;
    INT32       i4_ret;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_dev_list_page_create_title_bar(
                            pt_this->h_cnt_frm,
                            &pt_this->h_title_bar);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_dev_list_page_create_title_text(
                            pt_this->h_title_bar,
                            &pt_this->h_title_text);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_dev_list_page_set_text_text(
                        pt_this->h_title_text,
                        MLM_MENU_KEY_MMP_SIDER_MENU_TITLE_TXT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_dev_list_page_create_msg_text(
                            pt_this->h_cnt_frm,
                            &pt_this->h_msg_text);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_dev_list_page_set_text_text(
                        pt_this->h_msg_text,
                        MLM_MENU_KEY_MMP_SIDER_MENU_MSG_TXT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_dev_list_page_create_dev_list(
                            pt_this->h_cnt_frm,
                            &pt_this->h_dev_list);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

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
    MMP_DEV_LIST_PAGE_DATA_T* pt_this = &t_g_mmp_dev_list_page_data;
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    HANDLE_T        h_last_shadow_item = NULL_HANDLE;

    /* Hide the main menu */
    i4_ret = menu_main_set_visibility(TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X,
                     TITLE_FRM_Y,
                     CONTENT_W,
                     CONTENT_H);

    i4_ret = c_wgl_move(pt_this->h_cnt_frm, &t_rect, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = _mmp_dev_list_page_update_dev_list();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_main_title_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_main_set_title(MLM_MENU_KEY_EMPTY);

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

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
    MMP_DEV_LIST_PAGE_DATA_T* pt_this = &t_g_mmp_dev_list_page_data;
    INT32       i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_main_title_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_help_tip_keytip_show(TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_g_is_show  = FALSE;
	pt_this->e_hlt_status = MMP_DEV_LIST_PAGE_DEV_LIST_HLT_STATUS_DEFAULT;

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
    INT32 i4_ret = MENUR_OK;
    MMP_DEV_LIST_PAGE_DATA_T* pt_this = &t_g_mmp_dev_list_page_data;

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) > 0)
    {
        i4_ret = _mmp_dev_list_page_set_text_text(
                        pt_this->h_title_text,
                        MLM_MENU_KEY_MMP_SIDER_MENU_TITLE_TXT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_dev_list_page_set_text_text(
                        pt_this->h_msg_text,
                        MLM_MENU_KEY_MMP_SIDER_MENU_MSG_TXT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      menu_custom_page_mmp_dev_list_init
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
extern INT32 menu_custom_page_mmp_dev_list_init(VOID)
{
    MMP_DEV_LIST_PAGE_DATA_T*     pt_this = &t_g_mmp_dev_list_page_data;
    INT32       i4_ret = MENUR_OK;

    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_create      = _on_page_create;
    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_show        = _on_page_show;
    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_custom_page_mmp_dev_list.pf_menu_page_update      = _on_page_update;

    /* register remove device notification function */
    i4_ret = a_rmv_dev_reg_monitor(
                    _mmp_dev_list_page_rmv_dev_nfy,
                    NULL,
                    &pt_this->ui4_rmv_dev_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


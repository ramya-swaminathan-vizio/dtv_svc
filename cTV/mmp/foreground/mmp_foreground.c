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
 * $RCSfile:  $
 * $Revision: #2 $
 * $Date: 2015/08/03 $
 * $Author: jg_wanlihong $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "mmp_foreground.h"
#include "amb/a_amb.h"
#include "menu2/a_menu.h"
#include "c_dbg.h"

#include "mmp/common_ui2/mmp_com_ui_info_handler.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/model/model.h"
#include "app_util/rmv_dev/a_rmv_dev.h"

#include "res/mmp/gen/mmp_media_type_bg_layout.h"
#include "res/mmp/gen/mmp_gen_img.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define MMP_DEV_LIST_PAGE_MAX_NAME_LEN      ((INT32)128)
#define MMP_FG_MSG_TXT_MAX_LEN              (256)

#ifdef SUPPORT_ONLY_ONE_USB_PORT
#define MMP_DEV_LIST_PAGE_USB_DEV_PREFIX    ("USB:")
#else
#define MMP_DEV_LIST_PAGE_USB_DEV_PREFIX    ("USB%d:")
#endif

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static MMP_FG_MEMBER_T t_g_fg_member;
//static GL_COLOR_T      t_g_text_color_white = { 255, { 255 }, { 255 }, { 255 }};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_init(VOID);
static INT32 _mmp_foreground_deinit(VOID);
static INT32 _mmp_foreground_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param);
static INT32 _mmp_foreground_cmd_do(MMP_FILE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param);
static INT32 _mmp_foreground_bwr_cmd_do(MMP_BE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param);
static INT32 _mmp_foreground_bwr_data_xng(const MMP_BE_UI_INFO_T* pt_upd_data);
static INT32 _mmp_foreground_activate(UINT32  ui4_idx);
static INT32 _mmp_foreground_inactivate(VOID);

static INT32 _mmp_foreground_view_init(MMP_FG_MEMBER_T* pt_this);
static INT32 _mmp_foreground_view_activate(VOID);
static INT32 _mmp_foreground_view_inactivate(VOID);

static INT32 _mmp_foreground_check_mnt_count(MMP_FG_MEMBER_T*    pt_this);




/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
 /*---------------------------------------------------------------------------*/
/**
 * @brief   a_mmp_foreground_register
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 a_mmp_foreground_register(VOID)
{
    MMP_MC_FILE_BROWSER_PROPERTY_T  t_prop = {0};
    MMP_FILE_BROWSER_INTF_T         t_intf = {0};
    MMP_BE_BROWSER_HDLR_T           t_hdlr = {0};
    MMP_BE_BROWSER_PROPERTY_T       t_be_bwr_prop = {0};
    INT32                           i4_ret;

    t_prop.ui1_id =                 MMP_RC_BROWSER_ID_FOREGROUND;
    t_intf.pf_init =                _mmp_foreground_init;
    t_intf.pf_deinit =              _mmp_foreground_deinit;
    t_intf.pf_handle_msg =          _mmp_foreground_handle_msg;
    t_intf.pf_cmd_do =              _mmp_foreground_cmd_do;
    t_hdlr.pf_cmd_do =              _mmp_foreground_bwr_cmd_do;
    t_hdlr.pf_data_change =         _mmp_foreground_bwr_data_xng;
    t_be_bwr_prop.ui2_flag=     (MMP_BE_BWR_FLAG_SKIP_MNT_PNT_SEL|MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL);
    t_be_bwr_prop.ui2_flag |= MMP_BE_BWR_FLAG_ADD_PARENT_ITEM;
    t_be_bwr_prop.t_range_info.ui1_col_num = 5;
    t_be_bwr_prop.t_range_info.ui1_row_num = 4;

    i4_ret = mmp_be_reg_brower(&t_intf, &t_prop, &t_hdlr, &t_be_bwr_prop);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_be_reg_brower() failed. i4_ret = %d.\r\n", i4_ret));
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   foreground init function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_init(VOID)
{
    MMP_FG_MEMBER_T*                pt_this = &t_g_fg_member;
    INT32                           i4_ret;
    ISO_639_LANG_T                  s639_lang;

    /*init member*/
    c_memset(pt_this, 0, sizeof(MMP_FG_MEMBER_T));

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret == APP_CFGR_OK)
    {
        pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }
    else
    {
        pt_this->ui1_gui_lang_id = 0;
        DBG_ERROR(("<MMP thumbnail >Get gui lanugage failed!, set lang id = 0 \r\n"));
    }

    do {
        i4_ret = _mmp_foreground_view_init(pt_this);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("_mmp_foreground_view_init() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }
        return MMPR_OK;
    } while (0);


    return i4_ret;
}

/*---------------------------------------------------------------------------e*/
/**
 * @brief   foreground deinit function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_deinit(VOID)
{
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;
    INT32               i4_ret = MMPR_OK;

    if(NULL_HANDLE != pt_this->h_main_frm)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->h_main_frm);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_main_frm = NULL_HANDLE;
    }

    i4_ret = mmp_img_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   The message handler of foreground
 * @param   e_msg_id [in]   Message ID
 * @param   pv_msg_param [in]   Message additional information
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param)
{
    MMP_FG_MEMBER_T*        pt_this = &t_g_fg_member;
    BOOL                    b_default_hdlr = FALSE;
    UINT8                   ui1_id ;
    BOOL                    b_is_show;
    ISO_639_LANG_T          s639_lang;
    INT32                   i4_ret = MMPR_OK;

    /* Only process msg when active */
    mmp_mc_browse_get_active(&ui1_id,&b_is_show);
    if (ui1_id != MMP_RC_BROWSER_ID_FOREGROUND)
    {
        MMP_DBG_ERROR(("<mmp> active browse is not foreground %d\n\r",ui1_id));
        return MMPR_OK;
    }

    switch (e_msg_id)
    {
        case MMP_MSG_ID_APP_PAUSED:
        {
            b_default_hdlr = TRUE;
        }
        break;

        case MMP_MSG_ID_BROWSE_FOLDER_XNG:
        {
            b_default_hdlr = TRUE;
        }
        break;

        case MMP_MSG_ID_BROWSE_FILE_INFO_READY:
        {
        }
        break;


        case MMP_MSG_ID_BROWSE_FILE_THUMBNAIL:
        {
        }
        break;


        case MMP_MSG_ID_CUST_APPLY_SORT_CFG:
        {
        }
        break;

        case MMP_MSG_ID_PLAY_FILE_XNG :
        {
        }
        break;
        case MMP_MSD_ID_LOCKED_INP:
        {
        }
        break;

#ifdef APP_MENU_MMP_COEXIST
        case MMP_MSG_ID_APP_STAT_XNG:
        {
        }
        break;
#endif

        case MMP_MSG_ID_GUI_LANG_XNG:

            i4_ret = a_cfg_get_gui_lang(s639_lang);
            if(i4_ret != APP_CFGR_OK)
            {
                MMP_DBG_ERROR(("MMP foreground get language fall \r\n"));
                pt_this->ui1_gui_lang_id =0;
            }
            else
            {
                pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
            }
#if NEVER
            _mmp_foreground_view_activate();
#else
            {
                ISL_REC_T    t_isl_rec = {0};
                TV_WIN_ID_T  e_focus_id = {0};
                a_tv_get_focus_win(&e_focus_id);
                a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);

                if (a_nav_ipts_is_usb_source(&t_isl_rec) == TRUE)
                {
                    i4_ret = _mmp_foreground_view_activate();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
#endif
            break;


        default:
            b_default_hdlr = TRUE;
            break;
    }

    if (b_default_hdlr)
    {
        i4_ret = mmp_be_default_msg_hdlr(e_msg_id, pv_msg_param);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   The command handler of foreground
 * @param   e_cmd_id [in]   Command ID
 * @param   pv_cmd_param [in]   Command additional information
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_cmd_do(MMP_FILE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param)
{
    INT32              i4_ret = MMPR_OK;

    if (MMP_FILE_BROWSER_CMD_ID_ACTIVATE == e_cmd_id)
    {
        i4_ret =_mmp_foreground_activate((UINT32)pv_cmd_param);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (MMP_FILE_BROWSER_CMD_ID_INACTIVATE == e_cmd_id)
    {
        i4_ret = _mmp_foreground_inactivate();
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_foreground_bwr_cmd_do
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_bwr_cmd_do(MMP_BE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param)
{
    switch (e_cmd_id)
    {
    case MMP_BE_BROWSER_CMD_ID_EXIT_BG_MODE:
    {
    }
        break;

    default:
        break;
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_foreground_bwr_data_xng
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_bwr_data_xng(const MMP_BE_UI_INFO_T* pt_upd_data)
{
    MMP_BE_UI_UPD_FIELD_T       e_upd_field = pt_upd_data->e_upd_field;
    MMP_FG_MEMBER_T*            pt_this = &t_g_fg_member;
    INT32                       i4_ret = MMPR_OK;

    MMP_DBG_INFO(("<mmp> data xng %s,%d,field:%d\n\r",__FILE__,__LINE__,e_upd_field));

    if(MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_LST & e_upd_field)
    {
        /* do not support */
    }

    if(MMP_BE_UI_UPD_FIELD_NO_DEVICE & e_upd_field)
    {
        c_wgl_set_visibility(pt_this->h_main_frm,WGL_SW_HIDE_RECURSIVE);
        c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);
    }

    if (MMP_BE_UI_UPD_FIELD_MNT_LST & e_upd_field)
    {
        /* do not support */
    }

    if (MMP_BE_UI_UPD_FIELD_ITEM_LIST & e_upd_field)
    {
        if(!(pt_this->b_is_no_dev))
        {
            i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(0),
                          NULL);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(pt_this->h_list,
                                  WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                                  NULL,
                                  NULL);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(pt_this->h_list,NULL,TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }

    if (MMP_BE_UI_UPD_FIELD_FOLDER_XNG & e_upd_field)
    {

    }

    if (MMP_BE_UI_UPD_FIELD_BK_PLAYER_STOP & e_upd_field)
    {
        /* back player stoped */
    }

    if (MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_XNG & e_upd_field)
    {
        /* do not support */
    }

    if (MMP_BE_UI_UPD_FIELD_PARSE_STATUS_UPD & e_upd_field)
    {

    }


    if (MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO & e_upd_field)
    {

    }

    if (MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT & e_upd_field)
    {

    }

    if (MMP_BE_UI_UPD_FIELD_LIMITED_FLDR & e_upd_field)
    {
        /* do not support */
    }

    if (MMP_BE_UI_UPD_FIELD_OPEN_FLDR_FAIL & e_upd_field)
    {
        /* do not support */
    }

    if (MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG & e_upd_field)
    {
    }

    if (MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID & e_upd_field)
    {
    }

    if (MMP_BE_UI_UPD_FIELD_MNT_DEV_XNG & e_upd_field)
    {
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_foreground_activate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_activate(UINT32  ui4_idx)
{
    INT32                           i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;

    i4_ret = _mmp_foreground_check_mnt_count(pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* Show widget */
    i4_ret = _mmp_foreground_view_activate();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_activate(MMP_RC_BROWSER_ID_FOREGROUND,
                             ui4_idx);
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;

}

/*----------------------------------------------------------------------------
 * Name:    _mmp_foreground_inactivate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_inactivate(VOID)
{
    INT32               i4_ret       = MMPR_OK;

    i4_ret = mmp_be_inactivate();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_foreground_view_inactivate();
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_set_msg_txt
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_read_media_type_tts(UINT16 ui2_focus_idx)
{
#ifdef APP_TTS_SUPPORT
    UTF16_T         w2s_str[128] = {0};
    UINT16          aui_type_mlm[3] = {
                                            MLM_MMP_KEY_MEDIA_TYPE_OPTION_MUSIC,
                                            MLM_MMP_KEY_MEDIA_TYPE_OPTION_VIDEO,
                                            MLM_MMP_KEY_MEDIA_TYPE_OPTION_PHOTO
                                            };
    if(ui2_focus_idx > 2)
    {
        MMP_DBG_ERROR(("<mmp> read tts indx error %s,%d,idx:%d\n\r",__FILE__,__LINE__,ui2_focus_idx));
        return  MMPR_OK;
    }
    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(aui_type_mlm[ui2_focus_idx]));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
    return  MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_foreground_read_dev_list_tts
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_read_dev_list_tts(UINT16      ui2_elem_hlt_idx )
{
#ifdef APP_TTS_SUPPORT
    INT32               i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;
    UTF16_T             w2s_usb_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};

    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(ui2_elem_hlt_idx,0),
                    w2s_usb_name);
    MMPR_LOG_ON_FAIL(i4_ret);

    a_app_tts_play(w2s_usb_name,c_uc_w2s_strlen(w2s_usb_name));
#endif
    return MMPR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _mmp_foreground_read_no_dev_tts
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_foreground_read_no_dev_tts(VOID)
{
#ifdef APP_TTS_SUPPORT
    UTF16_T             w2s_msg[MMP_FG_MSG_TXT_MAX_LEN] = {0};

    c_uc_w2s_strcpy(w2s_msg,MMP_TTS_TEXT(MLM_MMP_KEY_MMP_DEV_MSG_TXT));
    a_app_tts_play(w2s_msg,c_uc_w2s_strlen(w2s_msg));
#endif
    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_set_msg_txt
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_set_msg_txt(MMP_FG_MEMBER_T* pt_this)
{
    if(pt_this->b_is_no_dev)
    {
        INT32           i4_ret = MMPR_OK;
        UTF16_T         w2s_msg[MMP_FG_MSG_TXT_MAX_LEN] = {0};

        c_uc_w2s_strcpy(w2s_msg,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_MMP_DEV_MSG_TXT));
        i4_ret = c_wgl_do_cmd (pt_this->h_msg_text,
                                   WGL_CMD_TEXT_SET_TEXT,
                                   WGL_PACK(w2s_msg),
                                   WGL_PACK(c_uc_w2s_strlen(w2s_msg)));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return  MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_set_help_tip
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_set_help_tip(MMP_FG_MEMBER_T* pt_this,UINT16 ui2_focus_idx)
{
    INT32           i4_ret = MMPR_OK;
    UTF16_T         w2s_help_tip[256] = {0};
    UINT16          aui_type_mlm[3] = {
                                            MLM_MMP_KEY_MMEDIA_BROWSE_MUSIC,
                                            MLM_MMP_KEY_MMEDIA_BROWSE_VIDEO,
                                            MLM_MMP_KEY_MMEDIA_BROWSE_PHOTO
                                            };

    c_uc_w2s_strcpy(w2s_help_tip,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,aui_type_mlm[ui2_focus_idx]));


    i4_ret = c_wgl_do_cmd (pt_this->h_help_tip,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(w2s_help_tip),
                           WGL_PACK(c_uc_w2s_strlen(w2s_help_tip)));
    MMPR_LOG_ON_FAIL(i4_ret);

    return  MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_set_hlt_mnt_name
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_set_hlt_mnt_name(MMP_FG_MEMBER_T* pt_this)
{
    INT32               i4_ret = MMPR_OK;
    UTF16_T             w2s_dev_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UTF16_T             w2s_dev_hint[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UTF16_T             w2s_dev_name[256] = {0};
    UINT32              ui4_dir_num = 0;
    UINT32              ui4_active_idx = 0;

    if(pt_this->b_is_type_list)
    {
        i4_ret = mmp_mc_device_get_mnt_count(&ui4_dir_num);
        if ((MMPR_OK == i4_ret)
            &&(ui4_dir_num > 0))
        {
            i4_ret = mmp_be_get_activate_device_info(w2s_dev_info,
                                                     w2s_dev_hint,
                                                     &ui4_active_idx);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        c_uc_w2s_strcpy(w2s_dev_name,w2s_dev_hint);
        c_uc_w2s_strncat(w2s_dev_name,w2s_dev_info,c_uc_w2s_strlen(w2s_dev_info));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_dev_name,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_MMP_DEV_TITLE_TXT));
    }

    i4_ret = c_wgl_do_cmd (pt_this->h_dev_name,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_this->h_dev_name,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(w2s_dev_name),
                           WGL_PACK(c_uc_w2s_strlen(w2s_dev_name)));
    MMPR_LOG_ON_FAIL(i4_ret);

    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_set_dev_list_name
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_set_dev_list_name(MMP_FG_MEMBER_T* pt_this)
{
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    INT32           i4_ret = MMPR_OK;
    UINT32          ui4_mnt_count = 0;
    UINT32          ui4_usb_id = 0;
    UINT32          ui4_mnt_point_idx = 0;
    UINT32          ui4_not_care_dev_count = 0;
    UINT16          ui2_name_len = 0;

    UTF16_T         w2s_usb_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    UTF16_T         w2s_dev_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    CHAR            ac_temp[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    CHAR            ac_path[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    CHAR            ac_info[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};

    SIZE_T          z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
    UINT32          ui4_len = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;
    WGL_LB_ITEM_T            at_items;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    MMPR_LOG_ON_FAIL(i4_ret);

    MMP_DBG_INFO(("<mmp> get mnt count:%d,%s,%d\n\r",ui4_mnt_count,__FILE__,__LINE__));

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("<mmp> get mnt point status fail :%d,%s,%d\n\r",i4_ret,__FILE__,__LINE__));
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)) ||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)) ||
            (RMV_DEV_DEVICE_STATUS_UNSUPT_DEV & e_dev_status) > 0)
        {
            ui4_not_care_dev_count++;
            MMP_DBG_INFO(("<mmp> no care dev count:%d,%s,%d\n\r",ui4_not_care_dev_count,__FILE__,__LINE__));
            continue;
        }
        ui4_usb_id++;
    #ifdef SUPPORT_ONLY_ONE_USB_PORT
        c_strncpy(ac_temp, "USB:", MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
    #else
        UINT8   ui1_usb_port_num = a_get_usb_port_num_by_model();
        MMP_DBG_INFO(("<mmp> port num:%d,%s,%d\n\r",ui1_usb_port_num,__FILE__,__LINE__));

        if (ui1_usb_port_num > 1)
        {
            c_sprintf(ac_temp, MMP_DEV_LIST_PAGE_USB_DEV_PREFIX, ui4_usb_id);
            MMP_DBG_INFO(("<mmp> port name:%s,%s,%d\n\r",ac_temp,__FILE__,__LINE__));
        }
        else if (1 == ui1_usb_port_num)
        {
            c_strncpy(ac_temp, "USB:", MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
        }
        else
        {
            MMP_DBG_INFO(("\n<mmp>%s,%d,ui1_usb_port_num=%d\n",__FILE__, __LINE__, ui1_usb_port_num));
        }
    #endif

        i4_ret = c_uc_ps_to_w2s(ac_temp, w2s_usb_name, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
        MMPR_LOG_ON_FAIL(i4_ret);

        MMP_DBG_INFO(("<mmp> port name:%s,%s,%d\n\r",ac_temp,__FILE__,__LINE__));

        i4_ret = a_rmv_dev_get_mnt_point(ui4_mnt_point_idx,
                                     &z_size,
                                     ac_path);
        MMPR_LOG_ON_FAIL(i4_ret);

        MMP_DBG_INFO(("<mmp> mnt point path:%s,%s,%d\n\r",ac_path,__FILE__,__LINE__));

        i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                       ac_path,
                                       ac_info,
                                       &ui4_len);
        MMPR_LOG_ON_FAIL(i4_ret);

        MMP_DBG_INFO(("<mmp> mnt point path:%s,%s,%d\n\r",ac_info,__FILE__,__LINE__));

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

        MMP_DBG_INFO(("<mmp> mnt point path:%s,%s,%d\n\r",ac_info,__FILE__,__LINE__));

        i4_ret = c_uc_ps_to_w2s(ac_info, w2s_dev_info, MMP_DEV_LIST_PAGE_MAX_NAME_LEN);
        MMPR_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_usb_name,w2s_dev_info,c_uc_w2s_strlen(w2s_dev_info));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_usb_name;

        i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(&at_items),
                          NULL);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_SET_ELEM_TAG,
                          WGL_PACK(ui4_mnt_point_idx-ui4_not_care_dev_count),
                          WGL_PACK(ui4_mnt_point_idx));
        MMPR_LOG_ON_FAIL(i4_ret);

        c_memset(w2s_usb_name, 0, 128);
        c_memset(w2s_dev_info, 0, 128);
        c_memset(ac_temp, 0, 128);
        c_memset(ac_path, 0, 128);
        c_memset(ac_info, 0, 128);
    }

    return  MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_set_listbox_data
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_set_listbox_data(MMP_FG_MEMBER_T* pt_this)
{
    INT32           i4_ret = MMPR_OK;
    UINT8           ui1_i = 0;
    UTF16_T         w2s_tmp_name[128] = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem_info;
    UINT16          aui_type_mlm[3] = {
                                            MLM_MMP_KEY_MEDIA_TYPE_OPTION_MUSIC,
                                            MLM_MMP_KEY_MEDIA_TYPE_OPTION_VIDEO,
                                            MLM_MMP_KEY_MEDIA_TYPE_OPTION_PHOTO
                                            };
     /* set elem background image*/
    c_memset(&t_img_elem_info, 0, sizeof(WGL_LB_IMG_ELEM_SET_T));
    t_img_elem_info.h_normal            = NULL_HANDLE;
    t_img_elem_info.h_selected          = NULL_HANDLE;
    t_img_elem_info.h_disable           = NULL_HANDLE;
    t_img_elem_info.h_highlight         = h_g_mmp_lst_hlt;
    t_img_elem_info.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem_info.h_pushed            = NULL_HANDLE;
    t_img_elem_info.h_selected_disable  = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(&t_img_elem_info),
                          NULL);

    MMPR_LOG_ON_FAIL(i4_ret);

    /* delete all list elem */
    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_DEL_ALL,
                          NULL,
                          NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(pt_this->b_is_type_list)
    {
        WGL_LB_ITEM_T            at_items;
        for (ui1_i = 0; ui1_i < 3; ui1_i ++)
        {
            c_uc_w2s_strcpy(w2s_tmp_name,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,aui_type_mlm[ui1_i]));

            at_items.e_col_type = LB_COL_TYPE_TEXT;
            at_items.data.pw2s_text = w2s_tmp_name;

            i4_ret = c_wgl_do_cmd(pt_this->h_list,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(&at_items),
                              NULL);
            MMPR_LOG_ON_FAIL(i4_ret);

            c_memset(w2s_tmp_name, 0, 128);
        }
        i4_ret = _mmp_foreground_read_media_type_tts(0);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        if(!(pt_this->b_is_no_dev))
        {
           i4_ret =  _mmp_foreground_set_dev_list_name(pt_this);
           MMPR_LOG_ON_FAIL(i4_ret);

           i4_ret = _mmp_foreground_read_dev_list_tts(0);
           MMPR_LOG_ON_FAIL(i4_ret);
        }
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(0),
                          NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_list,
                                  WGL_SW_NORMAL);
    MMPR_LOG_ON_FAIL(i4_ret);

    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_check_mnt_count
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_check_mnt_count(MMP_FG_MEMBER_T*    pt_this)
{
    INT32       i4_ret = MMPR_OK;
    UINT32      ui4_mnt_num = 0;
    INT32       i4_loop = 0;
    CHAR        dev_name[MMP_DEV_LIST_PAGE_MAX_NAME_LEN] = {0};
    SIZE_T      z_size = MMP_DEV_LIST_PAGE_MAX_NAME_LEN;

    i4_ret = mmp_mc_device_get_mnt_count(&ui4_mnt_num);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("<mmp> get mnt count fail ,i4_ret:%d\n\r",i4_ret));
        return i4_ret;
    }

    DBG_LOG_PRINT(("<mmp> get mnt count:%d\n\r",ui4_mnt_num));

    for (i4_loop = 0; i4_loop < (INT32)ui4_mnt_num; i4_loop++)
    {
        i4_ret = a_rmv_dev_get_mnt_point(i4_loop, &z_size, dev_name);
        if (i4_ret != RMVR_OK)
        {
            continue;
        }
        DBG_LOG_PRINT(("<MMP>[%s %d] get dev[%d] name:%s\n\r",__FUNCTION__,__LINE__,i4_loop,dev_name));
        if (dev_name[0] != '\0' && c_strstr(dev_name, "/sd") != NULL)
        {
            break;
        }
    }

    MMP_DBG_INFO(("<mmp> set active mnt:%d\n\r",i4_loop));
    if ((INT32)ui4_mnt_num == i4_loop)
    {
        pt_this->b_is_type_list = FALSE;
        pt_this->b_is_no_dev = TRUE;
    }
    else
    {
        pt_this->b_is_type_list = TRUE;
        pt_this->b_is_no_dev = FALSE;

        i4_ret = a_rmv_dev_set_active_mnt_pnt(i4_loop);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_view_activate
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_view_activate(VOID)
{
    INT32               i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;
    ISO_639_LANG_T      s639_lang;

    /* Update the UI lang */
    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        MMP_DBG_ERROR(("MMP foreground get language fall \r\n"));
        pt_this->ui1_gui_lang_id =0;
    }
    else
    {
        pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }

    i4_ret = _mmp_foreground_set_hlt_mnt_name(pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_dev_name,
                                  WGL_SW_NORMAL);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(!(pt_this->b_is_no_dev))
    {
        i4_ret = _mmp_foreground_set_listbox_data(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(pt_this->b_is_type_list)
    {
        i4_ret = _mmp_foreground_set_help_tip(pt_this,0);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_help_tip,
                                  WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(pt_this->b_is_no_dev)
    {
        i4_ret = _mmp_foreground_set_msg_txt(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_foreground_read_no_dev_tts();
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_msg_text,
                                  WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                  WGL_SW_RECURSIVE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_list,WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          _mmp_foreground_view_activate
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_view_inactivate(VOID)
{
    INT32               i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;

    i4_ret = c_wgl_set_visibility(pt_this->h_logo,
                                  WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_dev_name,
                                  WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_msg_text,
                                  WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_list,
                                  WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_help_tip,
                                  WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return  MMPR_OK;
}



/*----------------------------------------------------------------------------
 * Name: _mmp_foreground_listbox_fct
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
static INT32 _mmp_foreground_listbox_fct(
                        HANDLE_T    h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2)
{
    UINT16              ui2_idx = 0;
    UINT16              ui2_list_num = 0;
    INT32               i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_list,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_idx),
                                          NULL);
        MMPR_LOG_ON_FAIL(i4_ret);

        MMP_DBG_INFO(("<mmp> get focus %s,%d idnx:%d\n\r",__FILE__,__LINE__,ui2_idx));

        i4_ret = _mmp_foreground_set_help_tip(pt_this,ui2_idx);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(pt_this->h_help_tip,NULL,TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {

        UINT32  ui4_key_code = (UINT32)pv_param1;
        i4_ret = c_wgl_do_cmd(pt_this->h_list,
                              WGL_CMD_LB_GET_ELEM_NUM,
                              WGL_PACK(&ui2_list_num),
                              NULL);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_this->h_list,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_idx),
                              NULL);
        MMPR_LOG_ON_FAIL(i4_ret);

        MMP_DBG_INFO(("<mmp> %s,%d idnx:%d,num:%d\n\r",__FILE__,__LINE__,ui2_idx,ui2_list_num));

        switch (ui4_key_code)
        {
            case BTN_CURSOR_UP :
            {
                if(ui2_idx == 0)
                {
                    ui2_idx = ui2_list_num - 1;
                }
                else
                {
                    ui2_idx = ui2_idx - 1;
                }

                if(pt_this->b_is_type_list)
                {
                    _mmp_foreground_read_media_type_tts(ui2_idx);

                    i4_ret = _mmp_foreground_set_help_tip(pt_this,ui2_idx);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_repaint(pt_this->h_help_tip,NULL,TRUE);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else
                {

                    _mmp_foreground_read_dev_list_tts(ui2_idx);
                }
            }
                break;
            case BTN_CURSOR_DOWN :
            {
                if(ui2_idx == ui2_list_num - 1)
                {
                    ui2_idx = 0;
                }
                else
                {
                    ui2_idx = ui2_idx + 1;
                }

                if(pt_this->b_is_type_list)
                {
                    _mmp_foreground_read_media_type_tts(ui2_idx);

                    i4_ret = _mmp_foreground_set_help_tip(pt_this,ui2_idx);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_repaint(pt_this->h_help_tip,NULL,TRUE);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    _mmp_foreground_read_dev_list_tts(ui2_idx);
                }
            }
                break;
            case BTN_SELECT :
            {
                if(pt_this->b_is_type_list)
                {
                    UINT8               ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR;
                    MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;
                    UINT8               ui1_bwr_id = MMP_RC_BROWSER_ID_LIST;
                    switch (ui2_idx)
                    {
                        case 0:
                        {
                            ui1_bwr_id = MMP_APP_RESUME_INFO_AUDIO_BWR;
                            ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR;
                            e_media_type = MMP_MEDIA_TYPE_AUDIO;
                            break;
                        }
                        case 1:
                        {
                            ui1_bwr_id = MMP_APP_RESUME_INFO_VIDEO_BWR;
                            ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_VIDEO_BWR;
                            e_media_type = MMP_MEDIA_TYPE_VIDEO;
                            break;
                        }
                        case 2:
                        {
                            ui1_bwr_id = MMP_APP_RESUME_INFO_PHOTO_BWR;
                            ui1_req_op = ICL_RECID_MMP_REQ_OP_START_PHOTO_FRM;
                            e_media_type = MMP_MEDIA_TYPE_PHOTO;
                            break;
                        }
                    }

                    c_wgl_set_visibility(pt_this->h_main_frm,WGL_SW_HIDE_RECURSIVE);
                    c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);

                    i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE,(VOID*)e_media_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_RESUMED, (VOID*)((UINT32)ui1_bwr_id));
                    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
                                          &ui1_req_op,
                                          ICL_RECID_MMP_REQUEST_OP_SIZE);
                }
                else
                {
                    UINT32              ui4_active_idx = 0;
                    UINT32              ui4_curr_idx = 0;
                    SIZE_T              z_size = MMP_DEV_NAME_MAX_LEN;
                    CHAR                s_mnt_name[MMP_DEV_NAME_MAX_LEN + 1] = {0};

                    if(pt_this->b_is_no_dev)
                    {
                        break;
                    }

                    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                                          WGL_CMD_LB_GET_ELEM_TAG,
                                          WGL_PACK(ui2_idx),
                                          WGL_PACK(&ui4_curr_idx));
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                  WGL_SW_HIDE_RECURSIVE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    pt_this->b_is_type_list = TRUE;
                    pt_this->b_is_no_dev = FALSE;

                    i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_active_idx,
                                                                &z_size,
                                                                s_mnt_name);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    DBG_LOG_PRINT(("<mmp> %s,%d,idx:%d,active_idx:%d\n\r",__FILE__,__LINE__,ui4_curr_idx,ui4_active_idx));

                    if(ui4_curr_idx != ui4_active_idx)
                    {

                        i4_ret = a_rmv_dev_set_active_mnt_pnt(ui4_curr_idx);
                        MMPR_LOG_ON_FAIL(i4_ret);

                        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SET_ACT_MNT_POINT,(VOID*)ui4_curr_idx);
                        MMPR_LOG_ON_FAIL(i4_ret);

                        i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT,
                                                MMP_BE_REFRESH_TYPE_ITEM_LST);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                    i4_ret = _mmp_foreground_view_activate();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
                break;
            case BTN_EXIT:
            {
                i4_ret = mmp_be_pause_mmp();
                MMPR_LOG_ON_FAIL(i4_ret);
                return MMPR_OK;
            }
            case BTN_RETURN:
            {
                if(pt_this->b_is_type_list)
                {
                    UTF16_T w2s_help_tip[256] = {0};

                    i4_ret = c_wgl_do_cmd (pt_this->h_help_tip,
                                           WGL_CMD_TEXT_SET_TEXT,
                                           WGL_PACK(w2s_help_tip),
                                           WGL_PACK(256));
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_repaint(pt_this->h_help_tip,NULL,TRUE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,
                                  WGL_SW_HIDE_RECURSIVE);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    pt_this->b_is_type_list = FALSE;
                    pt_this->b_is_no_dev = FALSE;

                    i4_ret = _mmp_foreground_view_activate();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }

                return MMPR_OK;
            }
            case BTN_INPUT_SRC:
            {
                i4_ret = a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
                return MMPR_OK;
            }
            default :
            {
                i4_ret = mmp_be_default_key_handle(ui4_key_code,
                                                       WGL_MSG_KEY_DOWN);
                MMPR_LOG_ON_FAIL(i4_ret);
                break ;
            }
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}


/*----------------------------------------------------------------------------
 * Name: _mmp_foreground_main_frm_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_main_frm_fct(HANDLE_T    h_widget,
                                             UINT32      ui4_msg,
                                             VOID*       pv_param1,
                                             VOID*       pv_param2)
{
    INT32       i4_ret = MMPR_OK;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32) pv_param1;

        switch(ui4_key_code)
        {
            case BTN_EXIT:
            {
                i4_ret = mmp_be_pause_mmp();
                MMPR_LOG_ON_FAIL(i4_ret);
                return MMPR_OK;
            }
                break;
            case BTN_INPUT_SRC:
            {
                i4_ret = a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
                break;
            case BTN_RETURN:
            {
            }
                break;

            default:
            {
                i4_ret = mmp_be_default_key_handle(ui4_key_code,
                                                   WGL_MSG_KEY_DOWN);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
                break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

#if 0
/*--------------------------------------------------------------------------
 * Name
 *     _mmp_foreground_main_frm_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _mmp_foreground_main_frm_init(VOID)
{
    INT32             i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*  pt_this = &t_g_fg_member;
    GL_RECT_T         t_rect;
    WGL_IMG_INFO_T    t_img_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    /*create bg*/
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_FOREGROUND_X,
                     MMP_FOREGROUND_Y,
                     MMP_FOREGROUND_WIDTH,
                     MMP_FOREGROUND_HEIGHT);

    i4_ret = c_wgl_create_widget(mmp_main_get_canvas(),
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _mmp_foreground_main_frm_fct,
                                 255,
                                 NULL,
                                 pt_this,
                                 &(pt_this->h_main_frm));
    MMPR_LOG_ON_FAIL(i4_ret);

    //get background img
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_mmp_media_type_bg;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_mmp_media_type_bg;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_mmp_media_type_bg;
    i4_ret = c_wgl_do_cmd(pt_this->h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *     _mmp_foreground_logo_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _mmp_foreground_logo_init(VOID)
{
    INT32             i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*  pt_this = &t_g_fg_member;
    GL_RECT_T         t_rect;
    WGL_IMG_INFO_T    t_img_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    /*create bg*/
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_FG_LOGO_X,
                     MMP_FG_LOGO_Y,
                     MMP_FG_LOGO_WIDTH,
                     MMP_FG_LOGO_HEIGHT);

    i4_ret = c_wgl_create_widget(pt_this->h_main_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)WGL_STL_GL_NO_BK,
                                 NULL,
                                 &(pt_this->h_logo));
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_logo,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    //get background img
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_mmp_vizio_logo;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_mmp_vizio_logo;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_mmp_vizio_logo;
    i4_ret = c_wgl_do_cmd(pt_this->h_logo,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_logo, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *     _mmp_foreground_text_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _mmp_foreground_text_init(
                                               GL_RECT_T*           pt_rect,
                                               HANDLE_T*            ph_widget)
{
    INT32             i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*  pt_this = &t_g_fg_member;
    WGL_COLOR_INFO_T  t_clr_info;
    WGL_FONT_INFO_T   t_fnt_info;

    i4_ret = c_wgl_create_widget(pt_this->h_main_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 NULL,
                                 ph_widget);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 28;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_text_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_text_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_text_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *     _mmp_foreground_listbox_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _mmp_foreground_listbox_init (VOID)
{
    INT32                       i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*            pt_this = &t_g_fg_member;
    GL_RECT_T                   t_rect = {0};
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem = {0};
    WGL_LB_INIT_T               t_lb_init = {0};
    WGL_LB_COL_INIT_T           at_cols;
    WGL_FONT_INFO_T             t_fnt_info = {0};

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MMP_FG_LIST_X,
                     MMP_FG_LIST_Y,
                     MMP_FG_LIST_WIDTH,
                     MMP_FG_LIST_HEIGHT
                     );

    at_cols.e_col_type       = LB_COL_TYPE_TEXT;
    at_cols.ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols.ui2_width        = 562;

    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = 50;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &at_cols;

    i4_ret = c_wgl_create_widget(pt_this->h_main_frm,
                                HT_WGL_WIDGET_LIST_BOX,
                                WGL_CONTENT_LIST_BOX_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _mmp_foreground_listbox_fct,
                                255,
                                &t_lb_init,
                                NULL,
                                &(pt_this->h_list));
    MMPR_LOG_ON_FAIL(i4_ret);

     /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 28;

    i4_ret = c_wgl_do_cmd (pt_this->h_list,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_text_color_white;
    t_lb_color.t_disable = t_g_text_color_white;
    t_lb_color.t_highlight = t_g_text_color_white;
    t_lb_color.t_highlight_unfocus = t_g_text_color_white;
    t_lb_color.t_pushed = t_g_text_color_white;
    t_lb_color.t_selected = t_g_text_color_white;
    t_lb_color.t_selected_disable = t_g_text_color_white;

    i4_ret = c_wgl_do_cmd(pt_this->h_list,
                      WGL_CMD_LB_SET_COL_COLOR,
                      WGL_PACK(WGL_CLR_TEXT),
                      WGL_PACK(&t_lb_color));
     MMPR_LOG_ON_FAIL(i4_ret);

    /* set img*/
    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = h_g_mmp_lst_hlt;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = h_g_mmp_lst_hlt;
    t_img_elem.h_selected           = h_g_mmp_lst_hlt;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (pt_this->h_list,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _mmp_be_media_type_pg_create_main_frame
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_foreground_view_init(MMP_FG_MEMBER_T* pt_this)
{
    INT32               i4_ret = MMPR_OK;

    //pt_this->b_is_type_list = TRUE;
    i4_ret = mmp_img_init();
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register main frm callback function */
    i4_ret = mmp_media_type_bg_reg_wgt_cb(WID_MMP_MEDIA_TYPE_BG_FRM_BG_MAIN_FRM,
                                          _mmp_foreground_main_frm_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* register list callback function */
    i4_ret = mmp_media_type_bg_reg_wgt_cb(WID_MMP_MEDIA_TYPE_BG_LB_LIST,
                                          _mmp_foreground_listbox_fct);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* create main frame ui */
    i4_ret = mmp_media_type_bg_create_ui(mmp_main_get_canvas());
    MMPR_LOG_ON_FAIL(i4_ret);

    /* initializ the main frame variables */
    pt_this->h_main_frm = mmp_media_type_bg_get_wgt_hdl(WID_MMP_MEDIA_TYPE_BG_FRM_BG_MAIN_FRM);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_main_frm);

    pt_this->h_dev_name = mmp_media_type_bg_get_wgt_hdl(WID_MMP_MEDIA_TYPE_BG_TXT_DEV_NAME);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_dev_name);

    pt_this->h_list = mmp_media_type_bg_get_wgt_hdl(WID_MMP_MEDIA_TYPE_BG_LB_LIST);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_list);

    pt_this->h_help_tip = mmp_media_type_bg_get_wgt_hdl(WID_MMP_MEDIA_TYPE_BG_TXT_HELP_TIP);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_help_tip);

    pt_this->h_msg_text = mmp_media_type_bg_get_wgt_hdl(WID_MMP_MEDIA_TYPE_BG_TXT_MSG_TEXT);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_msg_text);

    pt_this->h_logo = mmp_media_type_bg_get_wgt_hdl(WID_MMP_MEDIA_TYPE_BG_ICON_LOGO);
    MMP_ASSERT(NULL_HANDLE != pt_this->h_logo);


    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          mmp_foreground_view_repaint
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_foreground_view_repaint(VOID)
{
    INT32               i4_ret = MMPR_OK;
    MMP_FG_MEMBER_T*    pt_this = &t_g_fg_member;

    if(pt_this->b_is_no_dev)
    {
        MMP_DBG_INFO(("<mmp>  repaint %s,%d\n\r",__FILE__,__LINE__));

        UTF16_T w2s_help_tip[256] = {0};

        i4_ret = c_wgl_do_cmd (pt_this->h_msg_text,
                               WGL_CMD_TEXT_SET_TEXT,
                               WGL_PACK(w2s_help_tip),
                               WGL_PACK(256));
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_foreground_view_inactivate();
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_foreground_check_mnt_count(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _mmp_foreground_view_activate();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *          mmp_foreground_chg_inp_src_to_cast
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/

INT32 mmp_foreground_chg_inp_src_to_cast(VOID)
{
    UINT8  ui1_index = 0, ui1_src_num = 0;
    ISL_REC_T  t_isl_rec;

    MMP_DBG_INFO(("<mmp>  change to cast %s,%d\n\r",__FILE__,__LINE__));
    a_isl_get_num_rec(&ui1_src_num);
    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if ( t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST )
        {
            a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
            return MMPR_OK;
        }
    }

    return MMPR_OK;
}





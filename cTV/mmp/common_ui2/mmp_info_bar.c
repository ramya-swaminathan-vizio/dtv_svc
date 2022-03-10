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
 * $RCSfile: npg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------- 
                    include files 
-----------------------------------------------------------------------------*/ 
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/app/mmp_main.h"
#include "mmp_info_bar.h"
#include "res/mmp/common_ui/mmp_info_bar_rc.h"
#include "wdk/a_wdk.h"
#include "mmp/browse_eng/mmp_browse_eng.h"

#include "c_fe.h"
#include "c_handle.h"
/*----------------------------------------------------------------------------- 
                    customizable macros 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    macros, defines 
----------------------------------------------------------------------------*/ 
#define _MMP_INFO_BAR_IS_SYNC_REPAINT                ((BOOL)TRUE)
#define _MMP_INFO_BAR_TIMER_STOP                     ((BOOL)TRUE)
#define _MMP_INFO_BAR_TIMER_RESET                    ((BOOL)FALSE)
#define _MMP_INFO_BAR_STATUS_MSG_MAX_LEN             ((UINT32) 192)
#define _MMP_INFO_BAR_CHECK_TIMER_DUR                ((UINT32) 50)   /*ms*/
#define _MMP_INFO_BAR_DEFAULT_EDGE_HIDE_DUR          ((UINT32) 5000) /*ms*/

#define _MMP_INFO_BAR_STATUS_RESET_MSG_DATA(_t_data)             \
{                                                               \
    (_t_data).e_class = MMP_IB_MSG_CLASS_NONE;                  \
    (_t_data).e_msg_id = MMP_IB_STATUS_MSG_ID_NONE;             \
    (_t_data).ws_msg[0] = 0;                                    \
}

#define _MMP_INFO_BAR_MAKE_HIDE_TIMER_PARAM(_e_type, _ui2_ver)   \
(                                                               \
    (VOID*)((((UINT32)(_e_type)) << 16) | (_ui2_ver))           \
)

#define _MMP_INFO_BAR_GET_MSG_TYPE(_pv_param)                    \
(                                                               \
    (((UINT32)(_pv_param)) & 0xFFFF0000) >> 16                  \
)

#define _MMP_INFO_BAR_GET_VER(_pv_param)                         \
(                                                               \
    (((UINT32)(_pv_param)) & 0x0000FFFF)                        \
)

/*----------------------------------------------------------------------------- 
                    typedefs, enums, structures 
----------------------------------------------------------------------------*/ 
typedef enum __MMP_INFO_BAR_TRIGGER_TYPE_T
{
    _MMP_INFO_BAR_TT_LEVEL = 0,
    _MMP_INFO_BAR_TT_EDGE,
} _MMP_INFO_BAR_TRIGGER_TYPE_T;

typedef struct __MMP_INFO_BAR_STATUS_MSG_DATA_T
{
    UTF16_T                     ws_msg[_MMP_INFO_BAR_STATUS_MSG_MAX_LEN + 1];
    UINT16                      ui2_ver;
    MMP_IB_STATUS_MSG_ID_T      e_msg_id;
    MMP_IB_MSG_CLASS_T          e_class;
    _MMP_INFO_BAR_TRIGGER_TYPE_T e_trigger;
    BOOL                        b_is_dirty;
    BOOL                        b_disable;
} _MMP_INFO_BAR_STATUS_MSG_DATA_T;

typedef struct __MMP_INFO_BAR_MEMBER_T
{
    _MMP_INFO_BAR_STATUS_MSG_DATA_T  at_status_msg[MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY];

    /*timer*/
    HANDLE_T                    h_status_check_timer;
    HANDLE_T                    h_status_hide_timer;

    /*widget*/
    HANDLE_T                    h_info_frame;
    HANDLE_T                    h_status_frame;
    HANDLE_T                    h_status_text;
    HANDLE_T                    h_status_icon;

    /*font*/
    HANDLE_T                    h_font;

    /*image resource*/
    MMP_INFO_BAR_RC_T            t_rc;
    
    BOOL                        b_init;
    BOOL                        b_is_status_on;
    BOOL                        b_recheck_status;

    INT32                       i4_frm_height;
    
} _MMP_INFO_BAR_MEMBER_T;

/*----------------------------------------------------------------------------- 
                    private function declarations 
----------------------------------------------------------------------------*/ 
static INT32 _mmp_info_bar_resize_frame_by_status_text(VOID);

static INT32 _mmp_info_bar_trigger_type_init(VOID);

static INT32 _mmp_info_bar_ui_init(HANDLE_T  h_canvas);

static INT32 _mmp_info_bar_status_show(VOID);

static INT32 _mmp_info_bar_status_hide(
    BOOL                        b_clean,
    BOOL                        b_to_dirty);

static VOID _mmp_info_bar_status_reset_msg(
    UINT32                      ui4_idx_from,
    BOOL                        b_to_dirty);
    
static INT32 _mmp_info_bar_status_check_msg(
    VOID
    );
    
static UINT32 _mmp_info_bar_query_hide_duration(
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id
    );
#if 0
static BOOL _mmp_info_bar_query_hide_when_svc_chg(
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id
    );
#endif    
static VOID _mmp_info_bar_status_reset_check_timer(
    BOOL                        b_stop_only,
    UINT32                      ui4_dur);
    
static VOID _mmp_info_bar_status_check_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_unused);    
    
static VOID _mmp_info_bar_status_check_timer_hdlr(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3,
    VOID*                       pv_unused4);

static VOID _mmp_info_bar_status_reset_hide_timer(
    BOOL                        b_stop_only,
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id);
    
static VOID _mmp_info_bar_status_hide_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_ver);
    
static VOID _mmp_info_bar_status_hide_timer_hdlr(
    VOID*                       pv_ver,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3);

/*----------------------------------------------------------------------------- 
                    data, variable declarations 
-----------------------------------------------------------------------------*/ 
static _MMP_INFO_BAR_MEMBER_T    t_g_ib_view;

/*----------------------------------------------------------------------------- 
                    private function implementations 
-----------------------------------------------------------------------------*/ 

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _mmp_info_bar_resize_frame_by_status_text(VOID)
{
    _MMP_INFO_BAR_MEMBER_T*       pt_this          = &t_g_ib_view;
    UINT32                       ui2_total_lines  = 0;
    UINT32                       ui4_string_width = 0;
    UINT32                       ui4_string_height= 0;
    INT32                        i4_ret = 0;
    INT32                        i4_frame_height = 0;
    GL_RECT_T                    t_rect;
    UTF16_T                      w2s_text[_MMP_INFO_BAR_STATUS_MSG_MAX_LEN];
    MMP_MEDIA_TYPE_T             e_filter_type = MMP_MEDIA_TYPE_PHOTO;

    /* Get total lines */
    i4_ret = c_wgl_do_cmd(pt_this->h_status_text, 
                          WGL_CMD_TEXT_GET_TOTAL_LINES, (VOID*)&ui2_total_lines, (VOID*)NULL);
    IS_MMPR_OK(i4_ret);

    /* Get current display text */
    i4_ret = c_wgl_do_cmd (pt_this->h_status_text,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (_MMP_INFO_BAR_STATUS_MSG_MAX_LEN));
    IS_MMPR_OK(i4_ret);
    
    /* Get string height. */
    i4_ret = c_wgl_get_string_size(pt_this->h_font,
                                   w2s_text, 
                                   (INT32) c_uc_w2s_strlen(w2s_text), 
                                   (INT32*)&ui4_string_width, 
                                   (INT32*)&ui4_string_height);
    IS_MMPR_OK(i4_ret);
    
    /* There is no any text. */
    if (ui2_total_lines == 0)
    {
        return MMPR_OK;
    }

    /* 
       Note:

       Frame Height =  (1 line)   INSET_TOP + STRING_HEIGHT + INSET_BOTTOM
       Frame Height =  (2 line)   INSET_TOP + STRING_HEIGHT + LINE_GAP + STRING_HEIGHT + INSET_BOTTOM

    */


    /* Frame height calculation */
    i4_frame_height = MMP_INFO_BAR_STATUS_TXT_INSET_TOP;
    i4_frame_height += MMP_INFO_BAR_STATUS_TXT_INSET_BOTTOM;    
    i4_frame_height += (ui2_total_lines-1)*MMP_INFO_BAR_STATUS_TXT_LINE_GAP;
    i4_frame_height += (ui2_total_lines)*ui4_string_height;

    /* Resize the frame */
    SET_RECT_BY_SIZE (&t_rect, 
                      0,
                      0,
                      MMP_INFO_BAR_STATUS_FM_W,
                      i4_frame_height);
                      
    c_wgl_move (pt_this->h_status_frame, &t_rect, WGL_NO_AUTO_REPAINT);
    
    if (i4_frame_height > pt_this->i4_frm_height) 
    {
        pt_this->i4_frm_height = i4_frame_height;
        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_filter_type);
        if(e_filter_type == MMP_MEDIA_TYPE_AUDIO)
        {
            SET_RECT_BY_SIZE (&t_rect, 
                  MMP_INFO_BAR_STATUS_AUDIO_FM_X,
                  MMP_INFO_BAR_STATUS_AUDIO_FM_Y,
                  MMP_INFO_BAR_STATUS_AUDIO_FM_W,
                  MMP_INFO_BAR_STATUS_AUDIO_FM_H);
        }
        else if(e_filter_type == MMP_MEDIA_TYPE_VIDEO)
        {
            SET_RECT_BY_SIZE (&t_rect, 
                  MMP_INFO_BAR_STATUS_VIDEO_FM_X,
                  MMP_INFO_BAR_STATUS_VIDEO_FM_Y,
                  MMP_INFO_BAR_STATUS_VIDEO_FM_W,
                  MMP_INFO_BAR_STATUS_VIDEO_FM_H);
        }
        else
        {
        
            SET_RECT_BY_SIZE (&t_rect, 
                              MMP_INFO_BAR_STATUS_FM_X,
                              MMP_INFO_BAR_STATUS_FM_Y,
                              MMP_INFO_BAR_STATUS_FM_W,
                      pt_this->i4_frm_height);
        }

        c_wgl_move (pt_this->h_info_frame, &t_rect, WGL_NO_AUTO_REPAINT);
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _mmp_info_bar_trigger_type_init(VOID)
{
    _MMP_INFO_BAR_MEMBER_T*       pt_this = &t_g_ib_view;

    pt_this->at_status_msg[MMP_IB_STATUS_MSG_TYPE_DEV_EVENT].e_trigger           = _MMP_INFO_BAR_TT_EDGE;
    pt_this->at_status_msg[MMP_IB_STATUS_MSG_TYPE_DEV_STATUS].e_trigger          = _MMP_INFO_BAR_TT_LEVEL;    
    pt_this->at_status_msg[MMP_IB_STATUS_MSG_TYPE_GENERAL_STATUS].e_trigger      = _MMP_INFO_BAR_TT_LEVEL;
    pt_this->at_status_msg[MMP_IB_STATUS_MSG_TYPE_FLDR_STATUS].e_trigger         = _MMP_INFO_BAR_TT_LEVEL;
    pt_this->at_status_msg[MMP_IB_STATUS_MSG_TYPE_FILE_STATUS].e_trigger         = _MMP_INFO_BAR_TT_LEVEL;

    return MMPR_OK;    
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _mmp_info_bar_ui_init(HANDLE_T  h_canvas)
{
    _MMP_INFO_BAR_MEMBER_T*       pt_this = &t_g_ib_view;
    INT32                        i4_ret  = 0;
    WDK_FRM_WIDGET_PARAM_T       t_frm_param;
    WDK_TXT_WIDGET_PARAM_T       t_txt_param;    
    GL_COLOR_T                   t_txt_clr = {255, {   250 }, {  120 }, { 20 }};;

    c_memset(&t_frm_param, 0, sizeof(WDK_FRM_WIDGET_PARAM_T));

    /* Info frame */
    t_frm_param.h_parent              = h_canvas;
    t_frm_param.ui1_alpha             = MMP_INFO_BAR_DEFAULT_ALPHA;    
    t_frm_param.b_visibility          = FALSE;
    t_frm_param.i4_x                  = MMP_INFO_BAR_STATUS_FM_X;
    t_frm_param.i4_y                  = MMP_INFO_BAR_STATUS_FM_Y;
    t_frm_param.i4_w                  = MMP_INFO_BAR_STATUS_FM_W;    
    t_frm_param.i4_h                  = MMP_INFO_BAR_STATUS_FM_H;        
    t_frm_param.ui4_style             = 0;
    t_frm_param.t_img_bk.h_disable    = NULL_HANDLE;
    t_frm_param.t_img_bk.h_enable     = NULL_HANDLE;
    t_frm_param.t_img_bk.h_highlight  = NULL_HANDLE;    
    t_frm_param.pf_wdgt_proc          = NULL;
    t_frm_param.ph_created_frm        = &pt_this->h_info_frame;

    i4_ret = a_wdk_create_frm_widget (t_frm_param);
    if (i4_ret < WDKR_OK)
    {
        return MMPR_FAIL;
    }

    /* Status frame */
    t_frm_param.h_parent              = pt_this->h_info_frame;
    t_frm_param.ui1_alpha             = 255;    
    t_frm_param.b_visibility          = TRUE;
    t_frm_param.i4_x                  = 0;
    t_frm_param.i4_y                  = 0;
    t_frm_param.i4_w                  = MMP_INFO_BAR_STATUS_FM_W;    
    t_frm_param.i4_h                  = MMP_INFO_BAR_STATUS_FM_H;        
    t_frm_param.ui4_style             = 0;
    t_frm_param.t_img_bk.h_disable    = NULL_HANDLE;
    t_frm_param.t_img_bk.h_enable     = NULL_HANDLE;
    t_frm_param.t_img_bk.h_highlight  = NULL_HANDLE;
    t_frm_param.pf_wdgt_proc          = NULL;
    t_frm_param.ph_created_frm        = &pt_this->h_status_frame;

    i4_ret = a_wdk_create_frm_widget (t_frm_param);
    if (i4_ret < WDKR_OK)
    {
        return MMPR_FAIL;
    }

    /* Status text */
    t_txt_param.h_parent                    = pt_this->h_status_frame;
    t_txt_param.ui1_alpha                   = 255;
    t_txt_param.b_visibility                = TRUE;
    t_txt_param.i4_x                        = MMP_INFO_BAR_STATUS_TXT_X;
    t_txt_param.i4_y                        = MMP_INFO_BAR_STATUS_TXT_Y;
    t_txt_param.i4_w                        = MMP_INFO_BAR_STATUS_TXT_W;
    t_txt_param.i4_h                        = MMP_INFO_BAR_STATUS_TXT_H;
    t_txt_param.ui4_style                   = MMP_INFO_BAR_STATUS_TXT_STYLE;
    t_txt_param.ps_font_name                = MMP_INFO_BAR_STATUS_FONT_NAME;
    t_txt_param.e_font_size                 = MMP_INFO_BAR_STATUS_FONT_SIZE;
    t_txt_param.e_font_style                = MMP_INFO_BAR_STATUS_FONT_STYLE;
    t_txt_param.t_inset.i4_left             = MMP_INFO_BAR_STATUS_TXT_INSET_LEFT;
    t_txt_param.t_inset.i4_right            = MMP_INFO_BAR_STATUS_TXT_INSET_RIGHT;
    t_txt_param.t_inset.i4_top              = MMP_INFO_BAR_STATUS_TXT_INSET_TOP;
    t_txt_param.t_inset.i4_bottom           = MMP_INFO_BAR_STATUS_TXT_INSET_BOTTOM;
    t_txt_param.ui1_align                   = MMP_INFO_BAR_STATUS_TXT_ALIGN;
    t_txt_param.b_img_bk                    = TRUE;
    t_txt_param.t_img_bk.h_disable          = NULL_HANDLE;
    t_txt_param.t_img_bk.h_enable           = NULL_HANDLE;    
    t_txt_param.t_img_bk.h_highlight        = NULL_HANDLE;    
    t_txt_param.pt_clr_txt                  = &t_txt_clr;
    t_txt_param.pt_hlt_clr_txt              = &t_txt_clr;
    t_txt_param.pt_dis_clr_txt              = &t_txt_clr;
    t_txt_param.pf_wdgt_proc                = NULL;
    t_txt_param.ph_created_txt              = &pt_this->h_status_text;

    i4_ret = a_wdk_create_txt_widget (t_txt_param);
    if (i4_ret < WDKR_OK)
    {
        return MMPR_FAIL;
    }

    /* set line gap */
    IS_MMPR_OK (c_wgl_do_cmd (pt_this->h_status_text,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) MMP_INFO_BAR_STATUS_TXT_LINE_GAP),
                              NULL));

    /* font handle */
    i4_ret = c_fe_create_font(MMP_INFO_BAR_STATUS_FONT_NAME,
               MMP_INFO_BAR_STATUS_FONT_SIZE,
               MMP_INFO_BAR_STATUS_FONT_STYLE,                 
               FE_CMAP_ENC_UNICODE, 
               &pt_this->h_font);    
    if (i4_ret < FER_OK)
    {
        return MMPR_FAIL;
    }
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _mmp_info_bar_status_show(VOID)
{
    INT32                          i4_ret;
    _MMP_INFO_BAR_MEMBER_T*        pt_this = &t_g_ib_view;
    MMP_MEDIA_TYPE_T               e_filter_type = MMP_MEDIA_TYPE_PHOTO;
    GL_RECT_T                      t_rect={0};

    if(pt_this->b_is_status_on)
    {
        i4_ret = c_wgl_repaint(pt_this->h_info_frame, NULL, _MMP_INFO_BAR_IS_SYNC_REPAINT);
        if(WGLR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }
    }
    else
    {
        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_filter_type);
        if(e_filter_type == MMP_MEDIA_TYPE_AUDIO)
        {
            SET_RECT_BY_SIZE (&t_rect, 
                  MMP_INFO_BAR_STATUS_AUDIO_FM_X,
                  MMP_INFO_BAR_STATUS_AUDIO_FM_Y,
                  MMP_INFO_BAR_STATUS_AUDIO_FM_W,
                  MMP_INFO_BAR_STATUS_AUDIO_FM_H);

            c_wgl_move (pt_this->h_info_frame, &t_rect, WGL_NO_AUTO_REPAINT);
        }
        else if(e_filter_type == MMP_MEDIA_TYPE_VIDEO)
        {
            SET_RECT_BY_SIZE (&t_rect, 
                  MMP_INFO_BAR_STATUS_VIDEO_FM_X,
                  MMP_INFO_BAR_STATUS_VIDEO_FM_Y,
                  MMP_INFO_BAR_STATUS_VIDEO_FM_W,
                  MMP_INFO_BAR_STATUS_VIDEO_FM_H);

            c_wgl_move (pt_this->h_info_frame, &t_rect, WGL_NO_AUTO_REPAINT);
            c_wgl_float(pt_this->h_info_frame, TRUE, FALSE);
        }
        
        i4_ret = c_wgl_insert(pt_this->h_info_frame, NULL_HANDLE, WGL_INSERT_TOPMOST, WGL_NO_AUTO_REPAINT);
        if(WGLR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }

        i4_ret = c_wgl_show(pt_this->h_info_frame, WGL_SW_RECURSIVE);
        if(WGLR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }

        pt_this->b_is_status_on = TRUE;
    }
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_info_bar_status_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _mmp_info_bar_status_hide(
    BOOL                        b_clean,
    BOOL                        b_to_dirty)
{
    INT32                          i4_ret;
    _MMP_INFO_BAR_MEMBER_T*         pt_this = &t_g_ib_view;    
    
    if(b_clean)
    {
        _mmp_info_bar_status_reset_msg(0, b_to_dirty);
    }

    c_wgl_float(pt_this->h_info_frame, FALSE, FALSE);

    if(FALSE == pt_this->b_is_status_on)
    {
        return MMPR_OK;    
    }

    i4_ret = c_wgl_show(pt_this->h_info_frame, WGL_SW_HIDE_RECURSIVE);
    if(WGLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    pt_this->b_is_status_on = FALSE;
        
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_info_bar_status_reset_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_reset_msg(
    UINT32                      ui4_idx_from,
    BOOL                        b_to_dirty)
{
    _MMP_INFO_BAR_MEMBER_T*         pt_this = &t_g_ib_view;    
    
    for(; ui4_idx_from < MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY; ui4_idx_from++)
    {
        if(MMP_IB_STATUS_MSG_ID_NONE != pt_this->at_status_msg[ui4_idx_from].e_msg_id)
        {
            /*reset message data*/
            _MMP_INFO_BAR_STATUS_RESET_MSG_DATA(pt_this->at_status_msg[ui4_idx_from]);
        }
        
        pt_this->at_status_msg[ui4_idx_from].b_is_dirty = (_MMP_INFO_BAR_TT_EDGE == pt_this->at_status_msg[ui4_idx_from].e_trigger) ? TRUE : b_to_dirty;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _mmp_info_bar_status_check_msg(
    VOID
    )
{
    INT32                       i4_ret, i;
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type = MMP_IB_STATUS_MSG_TYPE_NONE;
    MMP_IB_STATUS_MSG_ID_T      e_msg_id   = MMP_IB_STATUS_MSG_ID_NONE;
    BOOL                        b_is_dirty = FALSE, b_stop_only = _MMP_INFO_BAR_TIMER_STOP;
    BOOL                        b_is_show = FALSE;
    _MMP_INFO_BAR_MEMBER_T*      pt_this = &t_g_ib_view;        


    for(i = 0; i < MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY; i++)
    {
        if(MMP_IB_STATUS_MSG_ID_NONE != pt_this->at_status_msg[i].e_msg_id)
        {           
            /*string*/        
            i4_ret = a_wdk_text_set_text (pt_this->h_status_text, (UTF16_T*) pt_this->at_status_msg[i].ws_msg);

            if(WDKR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }

            /*re-adjust widget*/
            _mmp_info_bar_resize_frame_by_status_text();

            /*set icon image */
			/*
            if(MMP_IB_MSG_CLASS_WARNING == pt_this->at_status_msg[i].e_class)
            {
                i4_ret = a_wdk_set_img_fg (pt_this->h_status_icon,
                                  pt_this->t_rc.h_warning_img,
                                  pt_this->t_rc.h_warning_img,                                  
                                  pt_this->t_rc.h_warning_img);                                  
            }
            else if(MMP_IB_MSG_CLASS_URGENT == pt_this->at_status_msg[i].e_class)
            {
                i4_ret = a_wdk_set_img_fg (pt_this->h_status_icon,
                                  pt_this->t_rc.h_urgent_img,
                                  pt_this->t_rc.h_urgent_img,                                  
                                  pt_this->t_rc.h_urgent_img);                                  
            }
            else
            {
                i4_ret = a_wdk_set_img_fg (pt_this->h_status_icon,
                                  pt_this->t_rc.h_info_img,
                                  pt_this->t_rc.h_info_img,                                  
                                  pt_this->t_rc.h_info_img);               
            }
                
            if(WDKR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
*/
            /* string color */           
            b_is_show = TRUE;
            e_msg_type = (MMP_IB_STATUS_MSG_TYPE_T)i;
            e_msg_id   = (MMP_IB_STATUS_MSG_ID_T)pt_this->at_status_msg[i].e_msg_id;
            
            if(FALSE == b_is_dirty)
            {
                b_is_dirty = pt_this->at_status_msg[i].b_is_dirty;
            }

            /* edge trigger will reset the timer. */
            if(_MMP_INFO_BAR_TT_LEVEL != pt_this->at_status_msg[i].e_trigger)
            {
                b_stop_only = _MMP_INFO_BAR_TIMER_RESET;
            }

            _mmp_info_bar_status_reset_msg((UINT32)(i+1), FALSE);
            
            break; /* processed */
        }
        else
        {
            if(FALSE == b_is_dirty)
            {
                b_is_dirty = pt_this->at_status_msg[i].b_is_dirty;
            }

        }

        /* cleaned. */
        pt_this->at_status_msg[i].b_is_dirty = FALSE;
    }

    if(b_is_dirty)
    {
        if(b_is_show)
        {
            _mmp_info_bar_status_show();
        }
        else
        {
            _mmp_info_bar_status_hide(FALSE, FALSE);
            //nav_hide_component(NAV_COMP_ID_IB);
        }

        _mmp_info_bar_status_reset_hide_timer(b_stop_only, e_msg_type, e_msg_id);

    }
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT32 _mmp_info_bar_query_hide_duration(
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id
    )
{
#if 0
    UINT16   ui2_idx = 0;

    for (ui2_idx = 0;
         ui2_idx < ui2_ib_msg_settings_num ;
         ui2_idx ++)
    {
        if (at_g_ib_msg_settings[ui2_idx].e_msg_type == e_msg_type &&
            at_g_ib_msg_settings[ui2_idx].e_msg_id   == e_msg_id)
        {

            return at_g_ib_msg_settings[ui2_idx].ui4_timeout_duration;
        }
    }
#endif
    return _MMP_INFO_BAR_DEFAULT_EDGE_HIDE_DUR;
}
#if 0
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _mmp_info_bar_query_hide_when_svc_chg(
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id
    )
{
    UINT16   ui2_idx = 0;

    for (ui2_idx = 0;
         ui2_idx < ui2_ib_msg_settings_num ;
         ui2_idx ++)
    {
        if (at_g_ib_msg_settings[ui2_idx].e_msg_type == e_msg_type &&
            at_g_ib_msg_settings[ui2_idx].e_msg_id   == e_msg_id)
        {
            return at_g_ib_msg_settings[ui2_idx].b_hide_when_svc_chg;
        }
    }
    return _MMP_INFO_BAR_DEFAULT_EDGE_HIDE_WHE_SVC_CHG;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_reset_check_timer(
    BOOL                        b_stop_only,
    UINT32                      ui4_dur)
{
    _MMP_INFO_BAR_MEMBER_T*         pt_this = &t_g_ib_view;    
    INT32                          i4_ret;

    i4_ret = c_timer_stop(pt_this->h_status_check_timer);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_stop() failed. i4_ret = %d\r\n", i4_ret));
    }

    if(_MMP_INFO_BAR_TIMER_STOP == b_stop_only)
    {
        return;
    }

    i4_ret = c_timer_start(pt_this->h_status_check_timer,
                           ui4_dur,
                           X_TIMER_FLAG_ONCE,
                           _mmp_info_bar_status_check_timer_cb,
                           NULL);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_start() failed. i4_ret = %d\r\n", i4_ret));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_info_bar_status_check_timer_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_check_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_unused)
{
    /*post a message to itself*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_info_bar_status_check_timer_hdlr,
                                NULL,
                                NULL,
                                NULL,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_info_bar_status_check_timer_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_check_timer_hdlr(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3,
    VOID*                       pv_unused4)
{
    _mmp_info_bar_status_check_msg();
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_reset_hide_timer(
    BOOL                        b_stop_only,
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id)
{
    _MMP_INFO_BAR_MEMBER_T*         pt_this = &t_g_ib_view;    
    INT32                       i4_ret;
    UINT32                      ui4_dur;
    
    i4_ret = c_timer_stop(pt_this->h_status_hide_timer);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_stop() failed. i4_ret = %d\r\n", i4_ret));
    }
    
    if(_MMP_INFO_BAR_TIMER_STOP == b_stop_only)
    {
        return;
    }
    
    /* duration */
    ui4_dur = _mmp_info_bar_query_hide_duration (e_msg_type, e_msg_id);

    i4_ret = c_timer_start(pt_this->h_status_hide_timer,
                           ui4_dur,
                           X_TIMER_FLAG_ONCE,
                           _mmp_info_bar_status_hide_timer_cb,
                           _MMP_INFO_BAR_MAKE_HIDE_TIMER_PARAM(e_msg_type, pt_this->at_status_msg[e_msg_type].ui2_ver));
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_start() failed. i4_ret = %d\r\n", i4_ret));
    }

}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_hide_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_ver)
{
    /*post a message to itself*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_info_bar_status_hide_timer_hdlr,
                                pv_ver,
                                NULL,
                                NULL,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _mmp_info_bar_status_hide_timer_hdlr(
    VOID*                       pv_ver,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    _MMP_INFO_BAR_MEMBER_T*      pt_this = &t_g_ib_view;
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type = (MMP_IB_STATUS_MSG_TYPE_T)_MMP_INFO_BAR_GET_MSG_TYPE(pv_ver);
    UINT16                      ui2_ver = (UINT16) (_MMP_INFO_BAR_GET_VER(pv_ver));

    if (e_msg_type >= MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY)
    {
        /*invalid parameters*/
        return;
    }
    if(ui2_ver != pt_this->at_status_msg[e_msg_type].ui2_ver || FALSE == pt_this->b_init)
    {
        /*out of date*/
        return;
    }

    if(_MMP_INFO_BAR_TT_EDGE == pt_this->at_status_msg[e_msg_type].e_trigger)
    {
        mmp_info_bar_clear_status_msg(e_msg_type, MMP_IB_STATUS_MSG_ID_NONE);
    }

    _mmp_info_bar_status_check_msg();
}

/*----------------------------------------------------------------------------- 
                    public function implementations 
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_init(
    HANDLE_T                     h_canvas,
    INT32                        i4_frame_x_offset,
    INT32                        i4_frame_y_offset)
{
    _MMP_INFO_BAR_MEMBER_T*       pt_this = &t_g_ib_view;
    INT32                        i4_ret  = 0;

    c_memset (&t_g_ib_view, 0, sizeof (_MMP_INFO_BAR_MEMBER_T));

    /* Trigger type init. */
    _mmp_info_bar_trigger_type_init();
    
    /* Resource init */
    i4_ret = mmp_info_bar_rc_init (&pt_this->t_rc);
    if (i4_ret < MMPR_OK)
    {
        return MMPR_FAIL;
    }

    /* UI init */
    i4_ret = _mmp_info_bar_ui_init(h_canvas);
    if (i4_ret < MMPR_OK)
    {
        return MMPR_FAIL;
    }

    /* Timer init */
    /*create status's message timer*/
    i4_ret = c_timer_create(&pt_this->h_status_check_timer);
    if(OSR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }
    
    /*create status's hide timer*/
    i4_ret = c_timer_create(&pt_this->h_status_hide_timer);
    if(OSR_OK != i4_ret)
    {
        return MMPR_FAIL;        
    }

    pt_this->b_init = TRUE;
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_deinit(
    VOID
    )
{
    _MMP_INFO_BAR_MEMBER_T*       pt_this = &t_g_ib_view;

    c_wgl_destroy_widget_ex(pt_this->h_info_frame, FALSE);

    if (NULL_HANDLE != pt_this->h_font) 
    {
        c_handle_free(pt_this->h_font);
        pt_this->h_font = NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_this->h_status_check_timer) 
    {
        c_timer_delete(pt_this->h_status_check_timer);
        pt_this->h_status_check_timer = NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_this->h_status_hide_timer) 
    {
        c_timer_delete(pt_this->h_status_hide_timer);
        pt_this->h_status_hide_timer = NULL_HANDLE;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_flush_msg(
    VOID
    )
{
    INT32                       i4_ret;
    
    i4_ret = _mmp_info_bar_status_check_msg();

    if (i4_ret < MMPR_OK)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_set_status_msg(
    MMP_IB_MSG_CLASS_T          e_msg_class,
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id,
    UTF16_T*                    ws_msg)
{    
    _MMP_INFO_BAR_MEMBER_T*      pt_this = &t_g_ib_view;
    
    if(((INT32)MMP_IB_STATUS_MSG_TYPE_NONE) > ((INT32)e_msg_type) || 
       ((INT32)MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY) <= ((INT32)e_msg_type) ||
       ((INT32)MMP_IB_MSG_CLASS_NONE) > ((INT32)e_msg_class) ||
       ((INT32)MMP_IB_MSG_CLASS_LAST_VALID_ENTRY) <= ((INT32)e_msg_class))
    {
        return MMPR_INV_ARG;
    }
    
    pt_this->at_status_msg[e_msg_type].e_class = e_msg_class;
    pt_this->at_status_msg[e_msg_type].e_msg_id = e_msg_id;
    pt_this->at_status_msg[e_msg_type].b_is_dirty = TRUE;
    pt_this->at_status_msg[e_msg_type].ui2_ver++;
    
    if(ws_msg)
    {
        c_uc_w2s_strncpy(pt_this->at_status_msg[e_msg_type].ws_msg, ws_msg, _MMP_INFO_BAR_STATUS_MSG_MAX_LEN);
        pt_this->at_status_msg[e_msg_type].ws_msg[_MMP_INFO_BAR_STATUS_MSG_MAX_LEN] = 0;
    }
    else
    {
        pt_this->at_status_msg[e_msg_type].ws_msg[0] = 0;
    }
    
    /**/
    _mmp_info_bar_status_reset_check_timer(_MMP_INFO_BAR_TIMER_RESET, _MMP_INFO_BAR_CHECK_TIMER_DUR);
    
    return MMPR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_mmp_info_bar_refresh_msg(UTF16_T* ws_msg,BOOL b_show)
{
	_MMP_INFO_BAR_MEMBER_T* 	 pt_this = &t_g_ib_view;
	INT32	i4_ret = MMPR_OK;

	i4_ret = a_wdk_text_set_text (pt_this->h_status_text,ws_msg);

    if(WDKR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }
	
    if(b_show)
    {
        _mmp_info_bar_status_show();
    }
    else
    {
        _mmp_info_bar_status_hide(FALSE, FALSE);
    }
	return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_clear_status_msg(
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type,
    MMP_IB_STATUS_MSG_ID_T      e_msg_id)
{    
    _MMP_INFO_BAR_MEMBER_T*      pt_this = &t_g_ib_view;
    
    if(((INT32)MMP_IB_STATUS_MSG_TYPE_NONE) > ((INT32)e_msg_type) || 
        ((INT32)MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY) <= ((INT32)e_msg_type))
    {
        return MMPR_INV_ARG;
    }
    
    if(MMP_IB_STATUS_MSG_ID_NONE == e_msg_id ||
        e_msg_id == pt_this->at_status_msg[e_msg_type].e_msg_id)
    {
        _MMP_INFO_BAR_STATUS_RESET_MSG_DATA(pt_this->at_status_msg[e_msg_type]);
        pt_this->at_status_msg[e_msg_type].b_is_dirty = TRUE;
        pt_this->at_status_msg[e_msg_type].ui2_ver++;
        
        /**/
        _mmp_info_bar_status_reset_check_timer(_MMP_INFO_BAR_TIMER_RESET, _MMP_INFO_BAR_CHECK_TIMER_DUR);
    }
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_get_active_status_msg(
    MMP_IB_STATUS_MSG_TYPE_T*   pe_msg_type,
    MMP_IB_STATUS_MSG_ID_T*     pe_msg_id)
{
    _MMP_INFO_BAR_MEMBER_T*      pt_this = &t_g_ib_view;
    INT32                       i;
    
    if(NULL == pe_msg_id || NULL == pe_msg_type)
    {
        return MMPR_INV_ARG;
    }
    
    for(i = 0; i < MMP_IB_STATUS_MSG_TYPE_LAST_VALID_ENTRY; i++)
    {
        if(MMP_IB_STATUS_MSG_ID_NONE != pt_this->at_status_msg[i].e_msg_id)
        {
            switch(pt_this->at_status_msg[i].e_trigger)
            {
            case _MMP_INFO_BAR_TT_LEVEL:
            case _MMP_INFO_BAR_TT_EDGE:
                {
                    *pe_msg_id = pt_this->at_status_msg[i].e_msg_id;
                    *pe_msg_type = (MMP_IB_STATUS_MSG_TYPE_T)i;
                    return MMPR_OK;
                }
                                
            default:
                break;
            }
        }
    }
    
    *pe_msg_type = (MMP_IB_STATUS_MSG_TYPE_T)0;
    *pe_msg_id = MMP_IB_STATUS_MSG_ID_NONE;
    
    return MMPR_NO_DATA;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_hide( 
    VOID
    )
{
    _MMP_INFO_BAR_MEMBER_T*      pt_this    = &t_g_ib_view;
    BOOL                        b_to_dirty = mmp_main_is_ap_resumed_status();

    if(FALSE == pt_this->b_init)
    {
        MMP_ASSERT(0);
        return MMPR_INV_ARG;
    }

    //if(pt_this->b_is_status_on)
    {
        _mmp_info_bar_status_hide(TRUE, b_to_dirty);
    }

    return MMPR_OK;
}





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
 * $RCSfile: epg_view.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains definitions for EPG View. (Actually, the View is
 *         a help function to the Widget Library).
 *---------------------------------------------------------------------------*/

#ifndef _EPG_VIEW_H_
#define _EPG_VIEW_H_

/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "epg/epg_model.h"

/*---------------------------------------------------------------------------
                    macros, defines, typedefs, enums
----------------------------------------------------------------------------*/
#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

/* Maximum length of retrieving data. */
#ifndef EPG_RETRIEVE_MSG_MAX_LEN
    #define  EPG_RETRIEVE_MSG_MAX_LEN        (60)
#endif /* EPG_RETRIEVE_MSG_MAX_LEN */

/* Maximum length of content advisory. */
#ifndef EPG_CA_MSG_MAX_LEN
    #define  EPG_CA_MSG_MAX_LEN              (32)
#endif /* EPG_CA_MSG_MAX_LEN */

/* Maximum length of page index. */
#ifndef EPG_PAGE_MSG_MAX_LEN
    #define  EPG_PAGE_MSG_MAX_LEN            (10)
#endif /* EPG_PAGE_MSG_MAX_LEN */

/* Maximum length of system time. */
#ifndef EPG_DT_TIME_MAX_LEN
    #define  EPG_DT_TIME_MAX_LEN             (80)
#endif /* EPG_DT_TIME_MAX_LEN */

/* Maximum length of date. */
#ifndef EPG_DT_DATE_MAX_LEN
    #define  EPG_DT_DATE_MAX_LEN             (40)
#endif /* EPG_DT_DATE_MAX_LEN */

/* Maximum length of symbols (am, pm, separators). */
#ifndef EPG_DT_SYMBOL_MAX_LEN
    #define  EPG_DT_SYMBOL_MAX_LEN           (20)
#endif /* EPG_DT_SYMBOL_MAX_LEN */

/* Maximum length of hour:minute (AM/PM). */
#ifndef EPG_DT_HOUR_MIN_MAX_LEN
    #define  EPG_DT_HOUR_MIN_MAX_LEN         (20)
#endif /* EPG_DT_HOUR_MIN_MAX_LEN */

/* Maximum length of channel no. */
#ifndef EPG_CHN_NO_MAX_LEN
    #define  EPG_CHN_NO_MAX_LEN              (10)
#endif /* EPG_CHN_NO_MAX_LEN */

/* Maximum length of channel name. */
#ifndef EPG_CHN_NAME_MAX_LEN
    #define  EPG_CHN_NAME_MAX_LEN            MAX_PROG_NAME_LEN
#endif /* EPG_CHN_NAME_MAX_LEN */

/* Maximum lengthof channel info. */
#ifndef EPG_CHN_INFO_MAX_LEN
    #define  EPG_CHN_INFO_MAX_LEN            (EPG_CHN_NO_MAX_LEN + EPG_CHN_NAME_MAX_LEN)
#endif /* EPG_CHN_INFO_MAX_LEN */

/* Scroll delay of long text. */
#ifndef EPG_LONG_TXT_SCRL_DELAY
    #define  EPG_LONG_TXT_SCRL_DELAY         (180)
#endif /* EPG_LONG_TXT_SCROLL_DELAY */

/* EPG background color configuration */
#ifndef EPG_MAIN_FRM_BK_COLOR_BLACK
    #define  EPG_MAIN_FRM_BK_COLOR_BLACK     (APP_COLOR (APP_COLOR_TYPE_BLUE, APP_COLOR_ITEM_BLACK))
#endif /* EPG_LONG_TXT_SCROLL_DELAY */


/*
   View messages.
*/
typedef enum
{
    EPG_MSG_VIEW_BEGIN = EPG_MSG_END,                      /* Begin of view messages. */

    EPG_MSG_VIEW_WGL_GET_FOCUS,                            /* Some widget gets focus. */
    EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT,                     /* Element of program list is highlighted. */
    EPG_MSG_VIEW_WGL_PRG_LST_ELEM_REACH_TOP,               /* Reach top element of program list. */
    EPG_MSG_VIEW_WGL_PRG_LST_ELEM_REACH_BOTTOM,            /* Reach bottom element of program list. */
    EPG_MSG_VIEW_WGL_PASSWD_EDIT_INPUT,                    /* Password edit gets input. */
    EPG_MSG_VIEW_WGL_TYPE_LST_ELEM_HLT,                    /* Element of type list is highlighted. */

    EPG_MSG_VIEW_END                                       /* End of view messages. */

}   EPG_MSG_VIEW_T;


#ifdef APP_IMG_UI
    #define  EPG_WIDGET_STYLE             ((UINT32) 0x00000000)
#else
    #define  EPG_WIDGET_STYLE             WGL_STL_GL_NO_IMG_UI
#endif /* APP_IMG_UI */


/*
   Focused widget types.
*/
typedef enum
{
    EPG_FOCUS_WIDGET_PRG_LST = 0,         /* Program list is focused. */
    EPG_FOCUS_WIDGET_SURF_LST,            /* Surfing list is focused. */
    EPG_FOCUS_WIDGET_PASSWD_EDIT,         /* Password edit is focused. */
    EPG_FOCUS_WIDGET_TYPE_LST,            /* Type list is focused. */
    EPG_FOCUS_WIDGET_SUBTYPE_LST          /* Subtype list is focused. */
}   EPG_FOCUS_WIDGET_T;


/*
   Channel types.
*/
typedef enum
{
    EPG_CHN_TYPE_PREV = 0,                /* Previous channel */
    EPG_CHN_TYPE_CRNT,                    /* Current channel */
    EPG_CHN_TYPE_NEXT                     /* Next channel */
}   EPG_CHN_TYPE_T;


/*
   Description types.
*/
typedef enum
{
    EPG_DESC_TYPE_TIME = 0,               /* Time details */
    EPG_DESC_TYPE_RATING                  /* TV rating */
}   EPG_DESC_TYPE_T;


/*
   Help types.
*/
typedef enum
{
    EPG_HELP_TYPE_BTN_RED = 0,            /* Red button */
    EPG_HELP_TYPE_BTN_GREEN,              /* Green button */
    EPG_HELP_TYPE_BTN_YELLOW,             /* Yellow button */
    EPG_HELP_TYPE_BTN_BLUE                /* Blue button */
}   EPG_HELP_TYPE_T;


/*
   Icon types.
*/
typedef enum
{
    EPG_ICON_TYPE_LOCK = 0,               /* Lock */
    EPG_ICON_TYPE_CC                      /* Closed caption */
}   EPG_ICON_TYPE_T;


/*
   View model commands.
*/
extern INT32  epg_view_init (VOID);
extern INT32  epg_view_set_navigations (EPG_FOCUS_WIDGET_T e_src_widget, UINT32 ui4_key_1, EPG_FOCUS_WIDGET_T e_dst_widget_1, UINT32 ui4_key_2, EPG_FOCUS_WIDGET_T e_dst_widget_2);
extern INT32  epg_view_get_focus_widget (EPG_FOCUS_WIDGET_T* pe_focus_widget);
extern INT32  epg_view_set_focus_widget (EPG_FOCUS_WIDGET_T e_focus_widget);
extern INT32  epg_view_adjust_background_by_config(EPG_CONFIG_T* pt_config);

/*
   Main frame commands.
*/
extern INT32 epg_view_main_frm_set_visibility (BOOL b_show);
extern INT32 epg_view_main_frm_show (VOID);
extern INT32 epg_view_main_frm_hide (VOID);
extern INT32 epg_view_main_frm_repaint (VOID);

/*
   Base frame commands.
*/
extern INT32 epg_view_base_frm_set_visibility (BOOL b_show);

/*
   Description frame commands.
*/
extern INT32 epg_view_desc_frm_set_visibility (BOOL b_show);
extern INT32 epg_view_desc_frm_show (VOID);
extern INT32 epg_view_desc_frm_hide (VOID);
extern INT32 epg_view_desc_frm_repaint (VOID);


/*
   Description background frame commands.
*/
extern INT32 epg_view_desc_bk_frm_set_visibility (BOOL b_show);


/*
   Video frame commands.
*/
extern INT32 epg_view_video_frm_set_visibility (BOOL b_show);
extern INT32 epg_view_video_frm_show (BOOL b_show);


/*
   Password frame commands.
*/
extern INT32 epg_view_passwd_frm_set_visibility (BOOL b_show);
extern INT32 epg_view_passwd_frm_show (VOID);
extern INT32 epg_view_passwd_frm_hide (VOID);


/*
   Password edit commands.
*/
extern INT32 epg_view_passwd_edit_set_visibility (BOOL b_show);
extern INT32 epg_view_passwd_edit_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_passwd_edit_get_text (UTF16_T* pw2s_text, UINT16 ui2_buf_size);
extern INT32 epg_view_passwd_edit_get_text_len (UINT16* pui2_text_len);

/*
   Retrieving icon commands.
*/
extern INT32 epg_view_retrieve_icon_set_visibility (BOOL b_show);
extern INT32 epg_view_retrieve_icon_set_image (HANDLE_T h_img);
extern INT32 epg_view_retrieve_icon_repaint (VOID);

/*
   Program list commands.
*/
extern INT32 epg_view_prg_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_prg_lst_clr_elems (UINT16 ui2_start, UINT16 ui2_end);
extern INT32 epg_view_prg_lst_enable_control_key (BOOL b_enable);
extern INT32 epg_view_prg_lst_get_hlt_idx (UINT16* pui2_idx);
extern INT32 epg_view_prg_lst_hlt_elem (UINT16 ui2_idx);
extern INT32 epg_view_prg_lst_unhlt_elem (UINT16 ui2_idx);
extern INT32 epg_view_prg_lst_set_elem_num (UINT16 ui2_elem_num);
extern INT32 epg_view_prg_lst_get_elem_num (UINT16* pui2_elem_num);
extern INT32 epg_view_prg_lst_set_elem (UINT16 ui2_idx, WGL_LB_ELEM_DATA_T* pt_elem_data);
extern INT32 epg_view_prg_lst_set_elems (UINT16 ui2_start, UINT16 ui2_end, WGL_LB_ELEM_DATA_T* pt_elem_data);
extern INT32 epg_view_prg_lst_set_title (UTF16_T* pw2s_text);
extern INT32 epg_view_prg_lst_set_paging_images (BOOL b_page_up, BOOL b_page_down, BOOL b_repaint);
extern INT32 epg_view_prg_lst_repaint_elems (UINT16 ui2_start, UINT16 ui2_end);
extern INT32 epg_view_prg_lst_reset (BOOL b_repaint);
extern INT32 epg_view_prg_lst_repaint (VOID);


/*
   Surfing list commands.
*/
extern INT32 epg_view_surf_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_surf_lst_clr_elems (UINT16 ui2_start, UINT16 ui2_end);
extern INT32 epg_view_surf_lst_get_hlt_idx (UINT16* pui2_idx);
extern INT32 epg_view_surf_lst_hlt_elem (UINT16 ui2_idx);
extern INT32 epg_view_surf_lst_unhlt_elem (UINT16 ui2_idx);
extern INT32 epg_view_surf_lst_set_elems (UINT16 ui2_start, UINT16 ui2_end, WGL_LB_ELEM_DATA_T* pt_elem_data);
extern INT32 epg_view_surf_lst_set_title (UTF16_T* pw2s_text);
extern INT32 epg_view_surf_lst_set_paging_images (BOOL b_page_up, BOOL b_page_down, BOOL b_repaint);
extern INT32 epg_view_surf_lst_repaint_elems (UINT16 ui2_start, UINT16 ui2_end);
extern INT32 epg_view_surf_lst_reset (BOOL b_repaint);
extern INT32 epg_view_surf_lst_repaint (VOID);


/*
   Channel list commands.
*/
extern INT32 epg_view_chn_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_chn_lst_set_text (EPG_CHN_TYPE_T e_chn_type, UTF16_T* pw2s_text);
extern INT32 epg_view_chn_lst_reset (BOOL b_repaint);
extern INT32 epg_view_chn_lst_repaint (VOID);


/*
   Description list commands.
*/
extern INT32 epg_view_desc_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_desc_lst_set_text (EPG_DESC_TYPE_T e_desc_type, UTF16_T* pw2s_text);
extern INT32 epg_view_desc_lst_reset (BOOL b_repaint);
extern INT32 epg_view_desc_lst_repaint (VOID);


/*
   Help list commands.
*/
extern INT32 epg_view_help_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_help_lst_set_col_width (EPG_HELP_TYPE_T e_help_type, UINT16 ui2_width);
extern INT32 epg_view_help_lst_set_text (EPG_HELP_TYPE_T e_help_type, UTF16_T* pw2s_text);
extern INT32 epg_view_help_lst_set_image (EPG_HELP_TYPE_T e_help_type, WGL_HIMG_TPL_T h_img);
extern INT32 epg_view_help_lst_reset (BOOL b_repaint);
extern INT32 epg_view_help_lst_repaint (VOID);


/*
   Icon list commands.
*/
extern INT32 epg_view_icon_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_icon_lst_set_image (EPG_ICON_TYPE_T e_icon_type, BOOL b_enable);
extern INT32 epg_view_icon_lst_reset (BOOL b_repaint);
extern INT32 epg_view_icon_lst_repaint (VOID);


/*
   Type list commands.
*/
extern INT32 epg_view_type_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_type_lst_set_title (UTF16_T* pw2s_text);
extern INT32 epg_view_type_lst_set_elems (UINT16 ui2_start, UINT16 ui2_end, WGL_LB_ELEM_DATA_T* pt_elem_data);
extern INT32 epg_view_type_lst_get_hlt_idx (UINT16 *pui2_hlt_idx);
extern INT32 epg_view_type_lst_hlt_elem (UINT16 ui2_idx);
extern INT32 epg_view_type_lst_repaint (VOID);


/*
   Subtype list commands.
*/
extern INT32 epg_view_subtype_lst_set_visibility (BOOL b_show);
extern INT32 epg_view_subtype_lst_set_title (UTF16_T* pw2s_text);
extern INT32 epg_view_subtype_lst_set_elems (UINT16 ui2_start, UINT16 ui2_end, WGL_LB_ELEM_DATA_T* pt_elem_data);
extern INT32 epg_view_subtype_lst_set_elem_num (UINT16 ui2_elem_num);
extern INT32 epg_view_subtype_lst_get_hlt_idx (UINT16 *pui2_hlt_idx);
extern INT32 epg_view_subtype_lst_hlt_elem (UINT16 ui2_idx);
extern INT32 epg_view_subtype_lst_repaint (VOID);


/*
   Time text commands.
*/
extern INT32 epg_view_time_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_time_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_time_txt_repaint (VOID);


/*
   Retrieving text commands.
*/
extern INT32 epg_view_retrieve_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_retrieve_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_retrieve_txt_repaint (VOID);


/*
   Direct channel input (DCI) text commands.
*/
extern INT32 epg_view_dci_hts_set_visibility (BOOL b_show);
extern INT32 epg_view_dci_hts_set_text (UTF16_T* pw2s_text, UTF16_T* pw2s_dummy);
extern INT32 epg_view_dci_hts_clear (VOID);
extern INT32 epg_view_dci_hts_repaint (VOID);


/*
   Program info text commands.
*/
extern INT32 epg_view_prg_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_prg_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_prg_txt_repaint (VOID);


/*
   Video text commands.
*/
extern INT32 epg_view_video_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_video_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_video_txt_repaint (VOID);


/*
   Description text commands.
*/
extern INT32 epg_view_desc_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_desc_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_desc_txt_repaint (VOID);
extern INT32 epg_view_desc_txt_page_up (VOID);
extern INT32 epg_view_desc_txt_page_down (VOID);
extern INT32 epg_view_desc_txt_first_page (VOID);
extern INT32 epg_view_desc_txt_get_num_lines (UINT16* pui2_lines);
extern INT32 epg_view_desc_txt_get_num_pages (UINT16* pui2_pages);


/*
   Page text commands.
*/
extern INT32 epg_view_page_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_page_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_page_txt_repaint (VOID);

/*
   Password text commands.
*/
extern INT32 epg_view_passwd_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_passwd_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_passwd_txt_repaint (VOID);

#ifdef APP_EPG_FULL_VIDEO
extern INT32 epg_view_passwd_alarm_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_passwd_alarm_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_passwd_alarm_txt_repaint (VOID);
#endif
/*
   Channel info text commands.
*/
extern INT32 epg_view_chn_txt_set_visibility (BOOL b_show);
extern INT32 epg_view_chn_txt_set_text (UTF16_T* pw2s_text);
extern INT32 epg_view_chn_txt_repaint (VOID);



#endif /* _EPG_VIEW_H_ */

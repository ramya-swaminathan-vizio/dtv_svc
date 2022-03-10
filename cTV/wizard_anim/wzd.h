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
 * $RCSfile: wzd.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/41 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 44fcab2cb57e22ab81550785e74341d2 $
 *
 * Description:
 *         This header file contains Wizard's specific definitions.
 *---------------------------------------------------------------------------*/

#ifndef _WZD_H_
#define _WZD_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_common.h"
#include "c_os.h"
#include "c_dbg.h"
#include "c_handle.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_fe.h"
#include "c_uc_str.h"
#include "c_wgl_image.h"
#include "c_cfg.h"
#include "c_cli.h"
#include "c_sb.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_svctx.h"
#include "c_nwl.h"
#include "c_lol.h"
#include "c_pcl.h"
#include "fonts/fontdata.h"

#include "u_fm.h"
#include "u_fe.h"
#include "u_dbg.h"
#include "u_sys_name.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_sets.h"
#include "u_wgl_bdr_common.h"
#include "u_lnk_list.h"


#include "am/a_am.h"
#include "amb/a_amb.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_dbg_level_app.h"
#include "app_util/a_icl.h"
#include "app_util/a_tv.h"
#include "app_util/lang/a_lang.h"

#include "wizard_anim/a_wzd.h"
#include "wizard_anim/wzd_dbg.h"
#include "wizard_anim/wzd_cli.h"
#include "wizard_anim/wzd_view.h"
#include "wizard_anim/wzd_util.h"
#include "wizard_anim/wzd_anim.h"

#include "res/wizard_anim/wzd_cfg.h"
#include "res/wizard_anim/wzd_img.h"
#include "res/wizard_anim/wzd_clr.h"
#include "res/wizard_anim/wzd_mlm.h"
#include "res/wizard_anim/wzd_img_cust.h"

#include "res/app_util/config/a_cfg_custom.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*
   Macros.
*/
#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))
#define WZD_TEXT(_key) MLM_WZD_TEXT(wzd_get_lang_id () , wzd_get_validate_key ((_key)))

/*
   Defines.
*/
/* maximum delay for widget messages */
#define  WGL_MSG_MAX_DELAY       500

/* maximum number of items of a setting */
#define  SETI_ITEM_MAX_NUM         8

/* maximum length of an Setting text */
#define  SETI_TEXT_MAX_LEN        16

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
/* code input digit box style:
 * lowest 4 bits: separator index. 0: normal input, 1: sep 1, 2: sep 2, etc
 * bit 4:         1 indicates the digit box is fullwidth, otherwise halfwidth
 * bit 5:         1 indicates the digit box is bordered, otherwise unbordered
 */
#define CODE_BOX_STL_SEP_MASK       0x0F
#define CODE_BOX_STL_FULLWIDTH      MAKE_BIT_MASK_8(4)
#define CODE_BOX_STL_NO_BORDER      MAKE_BIT_MASK_8(5)
#define CODE_BOX_STL_INDICATOR      MAKE_BIT_MASK_8(6)
#define CODE_BOX_STL_CUSTOM         MAKE_BIT_MASK_8(7)

/* code input number constant */
#define CODE_NUM_INVALID            ((UINT64) 0xFFFFFFFFFFFFFFFF)
#endif

#define NWL_CANDIDATE_NUM_MAX        (UINT32)30

#define WZD_ASYNC_DATA_THRESHOLD   (60)
#define WZD_MSGQ_RESEND_TIMES      (3)
#define WZD_OOBE_INTERVAL          (2000)

typedef VOID (*wzd_async_func)(VOID*   pv_data,
                               SIZE_T  z_data_size);
typedef VOID (*wzd_context_switch_nfy_fct) (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );


typedef struct _WZD_MSG_ASYNC_INVOKE_T {
    wzd_async_func pf_async_func;
    UINT8           aui1_data[WZD_ASYNC_DATA_THRESHOLD];
} WZD_MSG_ASYNC_INVOKE_T;
/*
   Widget messages.
*/
typedef struct
{
    UINT32              ui4_msg;       /* message type */
    VOID*               pv_param1;     /* key code */
    VOID*               pv_param2;     /* time stamp */
    UINT8               ui1_cur_pg_idx; /* indicate the source of the message */
}   WZD_WIDGET_MSG_T;

typedef struct _WZD_EVN_T
{
    HANDLE_T                    h_obj;
    UINT32                      ui4_data1;
    UINT32                      ui4_data2;
    UINT32                      ui4_data3;
    UINT32                      ui4_data4;
} WZD_EVN_T;

/*
   Message types of Wizard application.
*/
typedef enum
{
    /* Button messages. */
    WZD_MSG_BTN_CURSOR_UP = 0,              /* cursor up */
    WZD_MSG_BTN_CURSOR_DOWN,                /* cursor down */
    WZD_MSG_BTN_CURSOR_LEFT,                /* cursor left */
    WZD_MSG_BTN_CURSOR_RIGHT,               /* cursor right */
    WZD_MSG_BTN_SELECT,                     /* select button */
    WZD_MSG_BTN_EXIT,                       /* exit button */
    WZD_MSG_BTN_RETURN,                     /* return button */
    WZD_MSG_RMK_CLIENT_KEY,                 /* remote client key */

    /* Widget notifications. */
    WZD_MSG_WGL_NFY,                        /* widget library notifications */
    WZD_MSG_WGL_GET_FOCUS,                  /* some widget gets focus */
    WZD_MSG_WGL_SETI_LST_ELEM_SEL,          /* select the element of setting list */
    WZD_MSG_WGL_SETI_LST_ELEM_HLT,          /* highlight the element of setting list */

    /* SB scanning. */
    WZD_MSG_SB_SCAN_START,                  /* scanning start */
    WZD_MSG_SB_SCAN_START_NEXT,             /* scanning start (next) */
    WZD_MSG_SB_SCAN_PROGRESS,               /* scanning progress */
    WZD_MSG_SB_SCAN_END,                    /* resulted from scanning complete, cancel, or abort */
    WZD_MSG_SB_SCAN_ANAS_NFY,               /* ANAS Notify: used for sorting the analog channels */

    WZD_MSG_SCAN_TIMER_EXPIRED,             /* animation scan timer expired. update the scanning text. */

    /* Pause */
    WZD_MSG_PAUSE_ASYNC_STORE,              /* store the config and svl */
    WZD_MSG_PAUSE_TIMER_EXPIRED,            /* auto-pause timer expired */
    WZD_MSG_PAUSE_BY_WZD,                   /* paused by wizard-self -> setup complete */

#ifdef APP_ACI_SUPPORT
    WZD_MSG_SB_SCAN_ACI_NFY,                /* ACI notify from SB PAL&SECAM Engine */
    WZD_MSG_SB_SCAN_ACI_TIMER_EXPIRED,      /* ACI procedure timeout */
    WZD_MSG_ACI_SELECTION,                  /* ACI Selection */
#endif
    WZD_MSG_CLI_CREATE_DLG,                 /* For CLI to test dialog creation. */
    WZD_MSG_CLI_DESTROY_DLG,                /* For CLI to test dialog destruction. */
    WZD_MSG_CLI_CHANGE_PAGE,                /* For CLI to change page,  */
    WZD_REQ_CTX_SWITCH_EVENT,               /* for ctx swith*/
    WZD_MSG_ASYNC_INVOKE
}   WZD_MSG_T;

/*
   Message types of Wizard customization.
*/
typedef enum
{
    /* Customization return messages. */
    WZD_MSG_CUSTOM_NAV_FIRST_PAGE = 0,      /* Go to the first page */
    WZD_MSG_CUSTOM_NAV_LAST_PAGE,           /* Go to the last page */
    WZD_MSG_CUSTOM_NAV_NEXT_PAGE,           /* Go to the next page */
    WZD_MSG_CUSTOM_NAV_PREV_PAGE,           /* Go to the previous page */
    WZD_MSG_CUSTOM_NAV_SKIP_NEXT_PAGE,      /* Go to the next's next page */
    WZD_MSG_CUSTOM_NAV_PAGE_END,            /* Last page -> Pause Wizard */
    WZD_MSG_CUSTOM_SCAN_START,              /* Start scan */
    WZD_MSG_CUSTOM_JUMP_TO_SCAN_PAGE_AND_START_SCAN ,  /* jump to scan page and start scan */
    WZD_MSG_CUSTOM_NAV_ELEM_SEL,            /* Element selected*/
    WZD_MSG_CUSTOM_NAV_ELEM_HLT             /* Element highlight*/

}   WZD_MSG_CUSTOM_T;

typedef enum _WZD_PAGE_NAVI_T
{
    WZD_PAGE_NAVI_FIRST_PAGE = 0,
    WZD_PAGE_NAVI_LAST_PAGE,
    WZD_PAGE_NAVI_NEXT_PAGE,
    WZD_PAGE_NAVI_PREV_PAGE,
    WZD_PAGE_NAVI_LAST_FINISHED_PAGE,
    WZD_PAGE_NAVI_LAST_VALID_ITEM
}WZD_PAGE_NAVI_T;


/*
   Page types. Template Layout.
*/
typedef enum
{
    WZD_PAGE_TYPE_ONLY_DESC = 0,           /* show descriptions only */
    WZD_PAGE_TYPE_DESC_LIST,               /* description and list for selection */
    WZD_PAGE_TYPE_DESC_LIST_WITH_ICON,     /* description, list, and icon for selection */
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    WZD_PAGE_TYPE_CODE_INPUT,              /* digit number input for zipcode etc */
#endif

    WZD_PAGE_TYPE_SCAN,                    /* channel scan */
    WZD_PAGE_TYPE_CUST_PAGE                /* custom page */
}   WZD_PAGE_TYPE_T;


/*
   Double linking lists.
*/
typedef DLIST_T(_WZD_PAGE_INFO_T)           WZD_PAGE_LIST_T;
typedef DLIST_ENTRY_T(_WZD_PAGE_INFO_T)     WZD_PAGE_LINK_T;


/*
   Page list entry.
*/
typedef INT32 (*wzd_page_nfy)(UINT16 ui2_sel_idx, VOID* pv_data, WZD_MSG_CUSTOM_T* pt_ret_msg);
typedef UINT16(*wzd_page_get_elem_num_fct)(VOID);
typedef VOID  (*wzd_page_get_elem_text_fct)(UINT16 ui2_idx, UTF16_T* w2s_str, SIZE_T z_len);
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
typedef VOID  (*wzd_page_get_code_param_fct)(UINT8* pui1_code_elem_num, UINT8* pui1_code_style, UTF16_T* pw2s_code_sep_char, UINT64* pui8_code_num);
#endif

typedef INT32 (*wzd_cust_page_create_fct)(VOID) ;
typedef INT32 (*wzd_cust_page_destory_fct)(VOID) ;
typedef INT32 (*wzd_cust_page_show_fct)(UINT32 ui4_page_id);
typedef INT32 (*wzd_cust_page_hide_fct)(UINT32 ui4_page_id);

/* Footer data change notification*/
#define WZD_FOOTER_MSG_ITEM_FOCUSED   (1)     /* pv1= WZD_FOOTER_BTN_INDEX_T (focused button index) */
#define WZD_FOOTER_MSG_KEY_INPUT      (2)     /* pv1= ui4_key_code; pv2 = WZD_FOOTER_BTN_INDEX_T  (focused button index) */

/* For footer data change */
typedef VOID (*wzd_footer_data_change_nfy_fct)(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2);

/* Wizard page back event callback */
typedef VOID (*wzd_page_return_nfy_fct)(VOID);

/* Wizard page back event callback */
typedef VOID (*wzd_page_exit_nfy_fct)(VOID);

/* Wizard page anim finish event callback */
typedef VOID (*wzd_page_anim_finish_nfy_fct)(VOID);

typedef struct _WZD_PAGE_INFO_DATA_T
{
    WZD_PAGE_TYPE_T             t_page_type;                            /* template layout. page type */
    UINT16                      ui2_title_key;                          /* title text key */
    UINT16                      ui2_desc_text_key;                      /* description text key */
    wzd_page_get_elem_num_fct   pf_get_num;                             /* get number function */
    UINT8                       ui1_elem_num;                           /* 1. element number
                                                                           2. only used when pf_get_num == NULL */
    wzd_page_get_elem_text_fct  pf_get_text;                            /* get text function */
    UINT16                      aui2_elem_text_keys[SETI_LB_ELEM_NUM];  /* 1. element text keys, the size is the same as ui1_elem_num
                                                                           2. only used when pf_get_text == NULL */
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    UINT8                       ui1_code_elem_num;                      /* number of code box elements, incl.
                                                                           input boxes & separators */
    UINT8                       aui1_code_style[CODE_BOX_ELEM_NUM];     /* style definition for each code box */
    UTF16_T                     aw2s_code_sep_char[CODE_SEP_NUM];       /* separator definitions */
    wzd_page_get_code_param_fct pf_get_code_param;                      /* get code box parameter function
                                                                           will override previous 3 parameters */
#endif

    wzd_footer_data_change_nfy_fct  pf_footer_data_change;              /* Footer data change callback function */
    wzd_page_return_nfy_fct         pf_return_nfy_fct;                  /* Wizard page back event callback */
    wzd_page_exit_nfy_fct           pf_exit_nfy_fct;                    /* Wizard page EXIT event callback */
    wzd_page_anim_finish_nfy_fct    pf_anim_finish_nfy_fct;             /* Wizard page anim finish event callback */

    struct
    {
        wzd_cust_page_create_fct    pf_wzd_cust_page_create ;
        wzd_cust_page_destory_fct   pf_wzd_cust_page_destory ;
        wzd_cust_page_show_fct      pf_wzd_cust_page_show ;
        wzd_cust_page_hide_fct      pf_wzd_cust_page_hide ;
    }t_cust_page_fct_tab ;

    VOID*                       pv_data;                                /* reserved. */
}   WZD_PAGE_INFO_DATA_T;


typedef struct _WZD_PAGE_INFO_T
{
    WZD_PAGE_LINK_T         t_page_link;           /* page link */
    UINT8                   ui1_page_idx;          /* the index of this page entry in link */
    WZD_PAGE_INFO_DATA_T*   pt_page_data;          /* customized by customers */
    UINT16                  ui2_sel_idx;           /* selected element index */
    wzd_page_nfy            pf_nfy_sel;            /* callback function when setting items are selected */
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    UINT64                  ui8_code_num;          /* inputed code number */
#endif
}   WZD_PAGE_INFO_T;


/*
   Wizard variables.
*/
typedef struct
{
    /* Application data. */
    HANDLE_T            h_wzd;                 /* wizard handle */
    BOOL                b_pause;               /* paused mode */
    BOOL                b_cfg_dirty;           /* TRUE: store config */
    BOOL                b_svl_dirty;           /* TRUE: store svls */
    HANDLE_T            h_svctx;               /* service context -> used for stop service when start scan */

    /* wizard state */
    UINT8               ui1_state;             /* combined with ui1_page_idx as wzd_status stored in acfg */
    BOOL                b_tv_block;
    BOOL                b_tv_skip;

    /* Timer data. */
    HANDLE_T            h_timer_pause;         /* timer to auto pause Wizard */
    HANDLE_T            h_timer_scan;          /* timer to update the scanning text */
    HANDLE_T            h_timer_dlg;           /* timer to auto hide dialog */
    HANDLE_T            h_timer_oobe;          /* timer to see if OOBE started successfully */

    /* GUI language. */
    UINT16              ui2_lang_id;           /* language id */

    /* Customized page list */
    UINT8               ui1_page_num;          /* the number of page entries of Wizard applications */
    UINT8               ui1_page_idx;          /* catch the index of the latest page entry */
    WZD_PAGE_INFO_T*    pt_page_info;          /* catch the latest setting entry */

    /* Scan-related data */
    HANDLE_T            h_air_svl;             /* the SVL of the Air */
    HANDLE_T            h_air_tsl;             /* the TSL of the Air */
    HANDLE_T            h_air_nwl ;            /* the NWL of the Air */
    HANDLE_T            h_air_lol ;            /* the LOL of the Air */

    HANDLE_T            h_cab_svl;             /* the SVL of the Cable */
    HANDLE_T            h_cab_tsl;             /* the TSL of the Cable */
    HANDLE_T            h_cab_nwl ;            /* the NWL of the Cable */
    HANDLE_T            h_cab_lol ;            /* the LOL of the Cable */

    HANDLE_T            h_satl ;               /* the satellite object handle */
    HANDLE_T            h_sat_svl;             /* the SVL of the Satellite */
    HANDLE_T            h_sat_tsl;             /* the TSL of the Satellite */
    HANDLE_T            h_sat_nwl ;            /* the NWL of the Satellite */
    HANDLE_T            h_sat_lol ;            /* the LOL of the Satellite */

    BOOL                b_scanning;            /* True: Scanning */
    UINT16              ui2_scanning_type;     /* Air or Cable */
    INT32               i4_atv_num;            /* ATV Channel Number */
    INT32               i4_dtv_num;            /* DTV Channel Number */
    BOOL                b_been_cancel;         /* work around: speed up the scanning-cancel task */

    /* WZD applications. */
    WZD_PAGE_LIST_T     t_page_lst;            /* page list of Wizard applications */

    /* button control */
    BOOL                b_btn_select;          /* whether or not enable button select */
    BOOL                b_next_key;            /* whether or not receive the next left, right keys */

#ifdef APP_DVBT_SUPPORT
    UINT16             ui2_nwl_num;
    UINT16             aui2_nwl_candidate_id[NWL_CANDIDATE_NUM_MAX];
#endif
    UINT8              ui1_end_idx;             /* End page index, used when wizard state is WZD_STATE_RESUME */
    BOOL			   b_g_is_vol_key_enable;	/* VOL+/VOL-/MUTE is enable/disable*/
	BOOL			   b_g_is_rf_scan;
	BOOL			   b_g_is_panel_key_long_press;
	BOOL			   b_g_is_oobe_recovery;
}   WZD_T;

extern WZD_T t_g_wzd ;

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
/*
   Application model commands.
*/
extern UINT16   wzd_get_lang_id     (VOID) ;
extern UINT16   wzd_get_validate_key(UINT16 ui2_key) ;
extern INT32    wzd_app_send_msg    (UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len);
extern BOOL     wzd_is_show         (VOID);
extern BOOL     wzd_is_scan_active  (VOID);
extern HANDLE_T wzd_get_crnt_svctx  (VOID);
extern HANDLE_T wzd_get_crnt_svl    (VOID);
extern HANDLE_T wzd_get_crnt_tsl    (VOID);
/*
   Customization APIs
*/

/* AEE lifecycle callback functions */
extern INT32 wzd_custom_prev_init (VOID);
extern INT32 wzd_custom_init (VOID);
extern INT32 wzd_custom_resume (VOID);
extern INT32 wzd_custom_pause (VOID);
extern INT32 wzd_custom_exit (VOID);

#ifdef WZD_REMAPPING_KEY
extern INT32 wzd_custom_remapping_key (WZD_WIDGET_MSG_T*  pt_msg);
#endif

#ifdef WZD_CUSTOM_POWER_SEQ_CB
extern BOOL wzd_custom_power_seq_cb (VOID);
#endif

/* wizard status */
extern INT32 wzd_custom_set_status (UINT8* pui1_state, UINT8* pui1_page_idx);
extern INT32 wzd_custom_get_status (UINT8* pui1_state, UINT8* pui1_page_idx);

/* Customization functions */
extern INT32 wzd_page_lst_add_page(WZD_PAGE_INFO_DATA_T*  pt_page_data, wzd_page_nfy  pf_nfy_sel);
extern INT32 wzd_set_gui_lang (ISO_639_LANG_T s639_lang);

#ifdef APP_ACI_SUPPORT
extern INT32 wzd_set_desc_txt(UINT16 ui2_txt_key,BOOL   b_step,BOOL   b_repaint);
#endif

#ifdef APP_DVBT_SUPPORT
extern UINT16 wzd_get_nwl_num(VOID);
extern VOID wzd_get_nwl_name_text(UINT16 ui2_idx, UTF16_T* w2s_str, SIZE_T z_len);
extern INT32 wzd_get_fav_nwl_rec_id(UINT16* pui2_fav_rec_id);
extern BOOL wzd_is_nwl_page_show_able(VOID);
#endif

extern INT32 wzd_footer_data_change (UINT32    ui4_msg,
                        VOID*    pv_param1,
                        VOID*    pv_param2);
extern INT32 wzd_page_goto( WZD_PAGE_NAVI_T e_navi );

extern INT32 wzd_async_invoke(wzd_async_func  pf_async_func,
                        VOID*            pv_data,
                        SIZE_T           z_data_len,
                        BOOL             b_retry);
extern INT32 wzd_request_context_switch(
                    wzd_context_switch_nfy_fct      pf_fct,
                    VOID*                           pv_tag1,
                    VOID*                           pv_tag2,
                    VOID*                           pv_tag3
                    );
extern INT32 wzd_get_subpage_id( UINT8* pui1_idx );
extern INT32 wzd_set_subpage_id( UINT8 ui1_idx );
extern INT32 wzd_select_crnt_or_first_channel(BOOL b_skip_fake);
extern INT32 wzd_set_stream_play_region(BOOL b_small_video, BOOL b_tv);
extern VOID	 wzd_enable_vol_key(BOOL b_vol_key_enable);
extern VOID  wzd_set_mute_status(BOOL b_mute);
extern BOOL  wzd_get_mute_status(VOID);
extern BOOL  wzd_get_enable_vol_key_status();
extern VOID  wzd_set_power_off_flag(BOOL);
extern INT32 wzd_turn_on_off_analog_audio_by_mute(BOOL   b_on);
extern VOID wzd_set_rf_scan_flag(BOOL b_is_rf_scan);
extern BOOL wzd_panel_key_is_long_press(VOID);
extern INT32 wzd_chg_inp_src_to_hdmi(VOID);
extern INT32 wzd_chg_inp_src_to_hdmi(VOID);
extern VOID  wzd_set_startup_first_time(BOOL b_1st_time);
extern BOOL  wzd_get_startup_first_time(VOID);

extern INT32 a_wzd_exit(VOID);

#endif /* _WZD_H_ */

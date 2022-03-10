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
 * $RCSfile: menu.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 530b5f614fc48ad655af79370de4cf1b $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_H_
#define _MENU_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_sys_name.h"
#include "u_time_msrt.h"

#include "app_util/a_common.h"
#include "menu2/a_menu.h"
#include "res/menu2/menu_mlm.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"
#include "res/menu2/menu_config.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* Menu Return value */
#define MENUR_OK                  0
#define MENUR_FAIL               -1
#define MENUR_INV_ARG            -2
#define MENUR_INV_STATE          -3
#define MENUR_OUT_OF_MEMORY      -4
#define MENUR_CANT_CREATE_WIDGET -5
#define MENUR_PAGE_NOT_FOUND     -6
#define MENUR_PAGE_INIT_FAIL     -7
#define MENUR_PAGE_INV_STATE     -8
#define MENUR_ITEM_NOT_FOUND     -9
#define MENUR_CUSTOM_BASE        -256

/* Debug */
#undef DBG_INIT_LEVEL

/*When error, printf error */
#ifdef DBG_INIT_LEVEL_APP_MENU
#define DBG_INIT_LEVEL              	DBG_LEVEL_ERROR
#else
#define DBG_INIT_LEVEL              	DBG_LEVEL_ERROR
#endif

/* Time measurement (global version) */
#undef TMS_INIT_LEVEL
#ifdef TMS_INIT_LEVEL_APP_MENU
#define TMS_INIT_LEVEL              	TMS_INIT_LEVEL_APP_MENU
#else
#define TMS_INIT_LEVEL              	TMS_LEVEL_NONE
#endif

#undef TMS_MODULE_LEVEL
#define TMS_MODULE_LEVEL                menu_get_tms_level()

/* Time measurement (menu internal version)
   Reset: Reset the time of stopwatch.
   Split: Split the time of stopwatch. The stopwatch is still running in the
          background
*/

#ifdef APP_MENU_TMS_SUPPORT
    #define MENU_TMS_SPLIT(s_str)   menu_watch_split(s_str)
    #define MENU_TMS_RESET(s_str)   menu_watch_reset(s_str)
#else
    #define MENU_TMS_SPLIT(s_str)
    #define MENU_TMS_RESET(s_str)
#endif

/* Assertion.*/
#ifdef DEBUG
    #define MENU_ASSERT(cond)   DBG_ASSERT(cond, DBG_MOD_MENU)
#else
    #define MENU_ASSERT(cond)   if(cond){}
#endif

/* Return on error */
#define MENU_CHK_FAIL(_ret)  \
do{ \
    INT32 ret = _ret;   \
    if (ret < 0)   \
    {   \
        DBG_LOG_PRINT(("<MENU> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
        return MENUR_FAIL;  \
    }   \
}while(FALSE)

#define MENU_LOG_ON_FAIL(_ret)  \
do{ \
    INT32 ret = _ret;   \
    if (ret < 0)   \
    {   \
        DBG_LOG_PRINT(("<MENU> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
    }   \
}while(FALSE)

#define MENU_BREAK_ON_FAIL(_ret)  \
{ \
    INT32 ret = _ret;   \
    if (ret < 0)   \
    {   \
        DBG_LOG_PRINT(("<MENU> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
        break;  \
    } \
}

#define _TEXT(_txt)    ((UTF16_T*)L##_txt)


/* Menu aysnchronous procedure */
typedef VOID (*menu_async_func)(VOID* pv_data,
                                SIZE_T  z_data_size);

/* Menu Messages */
#define MENU_MSG_WGL_NOTIFY      0
#define MENU_MSG_ASYNC_INVOKE    1
#define MENU_MSG_AM_ASYNC_INVOKE 2
#define MENU_MSG_SHOW            3
#define MENU_MSG_FACTORY_KEY     4
#define MENU_REQ_CTX_SWITCH_EVENT 5
#define MENU_MSG_AM_ASYNC_IPCC_CHG  6
#define MENU_MSG_LONG_KEY_PRESS     7
#define MENU_MSG_CUSTOM_BASE     256

/* max message size */
#define MENU_MAX_MSG_COUNT          32
#define MENU_MAX_MSG_SIZE           128  //64
#define MENU_AM_MAX_MSG_SIZE        20

#define MENU_MSGQ_RESEND_TIMES      (3)

#ifndef BTN_EXIT_MENU
#define BTN_EXIT_MENU               BTN_MENU
#endif
/* Menu Messages' structs----------------- */
/* WGL Notify */
typedef struct _MENU_MSG_WGL_NOTIFY_T {
    UINT32      ui4_msg;
    VOID*       pv_param1;
    VOID*       pv_param2;
} MENU_MSG_WGL_NOTIFY_T;

/* Aysnchronous Invokcation */
#define MENU_ASYNC_DATA_THRESHOLD   (MENU_MAX_MSG_SIZE - 4)

typedef struct _MENU_MSG_ASYNC_INVOKE_T {
    menu_async_func pf_async_func;
    UINT8           aui1_data[MENU_ASYNC_DATA_THRESHOLD];
} MENU_MSG_ASYNC_INVOKE_T;

/* Aysnchronous Invokcation over AM */
#define MENU_AM_ASYNC_DATA_THRESHOLD   (MENU_AM_MAX_MSG_SIZE - 4)

typedef struct _MENU_MSG_AM_ASYNC_INVOKE_T {
    menu_async_func pf_async_func;
    UINT8           aui1_data[MENU_AM_ASYNC_DATA_THRESHOLD];
} MENU_MSG_AM_ASYNC_INVOKE_T;

/* Menu Language Map */
typedef struct _MENU_LANGMAP_ENTRY_T {
    ISO_639_LANG_T  s639_lang;
    UINT16          ui2_lang;
} MENU_LANGMAP_ENTRY_T;

/* Auto key repeat */
typedef enum
{
    MENU_AUTO_KEY_REPEAT_OFF,
    MENU_AUTO_KEY_REPEAT_ON,
    MENU_AUTO_KEY_REPEAT_DEFAULT
}   MENU_AUTO_KEY_REPEAT_T;

/* Menu hot key map */
typedef struct _MENU_HOT_KEY_REG_T
{
    UINT32 ui4_key_code;
    UINT32 ui4_page_idx;
}MENU_HOT_KEY_REG_T;

typedef struct _MENU_EVN_T
{
    HANDLE_T                    h_obj;
    UINT32                      ui4_data1;
    UINT32                      ui4_data2;
    UINT32                      ui4_data3;
    UINT32                      ui4_data4;
} MENU_EVN_T;

typedef struct _MENU_MONOTOR_T
{
    UINT32                      ui4_msg_type;
    VOID*                       pv_msg;
} MENU_MONOTOR_T;

typedef VOID (*menu_context_switch_nfy_fct) (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern INT32 menu_timer_start(VOID);
extern INT32 menu_timer_stop(VOID);
extern VOID  menu_timer_enable(BOOL b_enable);
extern BOOL  menu_timer_is_enabled(VOID);
extern VOID  menu_lock(VOID);
extern VOID  menu_unlock(VOID);
extern INT32 menu_enable_auto_key_repeat(MENU_AUTO_KEY_REPEAT_T  e_auto_key_repeat);
extern VOID  menu_leave(BOOL b_back,
                        UINT32 ui4_hide_delay);
extern MENU_COND_T menu_get_cond(VOID);
extern INT32 menu_async_invoke(menu_async_func  pf_async_func,
                               VOID*            pv_data,
                               SIZE_T           z_data_len,
                               BOOL             b_retry);
extern INT32 menu_am_async_invoke(menu_async_func  pf_async_func,
                               VOID*            pv_data,
                               SIZE_T           z_data_len,
                               BOOL             b_retry);
extern VOID menu_idx_to_langcode(UINT16 ui2_idx,
                                 ISO_639_LANG_T s639_lang);
extern VOID menu_langcode_to_idx(ISO_639_LANG_T s639_lang,
                                 UINT16* pui2_idx);
extern INT32 menu_set_langmap(MENU_LANGMAP_ENTRY_T* pt_langmap,
                              UINT16  ui2_langmap_size);

extern VOID menu_set_tms_level(UINT16 ui2_tms_level);
extern UINT16 menu_get_tms_level(VOID);
extern INT32 menu_request_context_switch(
                    menu_context_switch_nfy_fct      pf_fct,
                    VOID*                           pv_tag1,
                    VOID*                           pv_tag2,
                    VOID*                           pv_tag3
                    );

#ifdef CLI_SUPPORT
    extern INT32 menu_attach_cmd_tbl(VOID);
#endif /* CLI_SUPPORT */

#ifdef APP_MENU_TMS_SUPPORT
    extern INT32 menu_watch_reset(const CHAR* s_str);
    extern INT32 menu_watch_split(const CHAR* s_str);
#endif /* APP_MENU_TMS_SUPPORT */

extern BOOL menu_is_slave_mode(VOID);
extern VOID  menu_set_power_off_flag(BOOL);
extern UINT32 menu_get_current_page_id();

extern INT32 menu_reg_hot_key(MENU_HOT_KEY_REG_T* pt_hot_key);
extern INT32 menu_unreg_hot_key(UINT32 ui4_key_code);
extern BOOL  menu_is_hot_key(UINT32 ui4_key_code, UINT32 ui4_key_event);
extern INT32 menu_hot_key_handler(UINT32 ui4_key_code, UINT32 ui4_key_event, VOID* pv_param);
extern INT32 menu_jump_to_hot_key_page(VOID);
BOOL menu_is_picture_mode_item(UINT16 ui2_msgid_txt);

void menu_reset_for_dc_off_on(void);


#endif /* _MENU_H_ */

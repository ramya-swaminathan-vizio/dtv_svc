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
/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "u_wgl_common.h"

#include "c_fe.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"

#include "fonts/a_font.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define FONT_NAME_SIZE              20
#define MAX_FONT_ID_NUM             40

typedef struct 
{
    ISO_639_LANG_T      s639_lang;
    CHAR                s_font_name[20];
    UINT8               ui1_font_id;
} FONT_RESOURCE_DESCR_T;

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
static UINT8  ui1_g_text_dir = WGL_TEXT_DIR_LEFT_TO_RIGHT;

static FONT_RESOURCE_DESCR_T   at_g_font_res_decr_t[MAX_FONT_ID_NUM];
static UINT8                   ui1_g_font_res_decr_num = 0;

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    static functions implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _font_canvas_text_dir_cb
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT8 _font_canvas_text_dir_cb(VOID)
{
    return ui1_g_text_dir;
}
/*-----------------------------------------------------------------------------
                    extern functions implementation
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: a_font_get_font_direction
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
UINT8 a_font_get_font_direction(VOID)
{
    return ui1_g_text_dir;
}

/*-----------------------------------------------------------------------------
 * Name: a_font_change_text_dir
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_font_change_text_dir(
        ISO_639_LANG_T              s639_lang,
        HANDLE_T                    h_container /*reserved*/
        )
{
    UINT8  ui1_idx = 0;

    /**/
    if (c_strcmp(s639_lang, s639_app_cfg_lang_ara) == 0 ||
        c_strcmp(s639_lang, s639_app_cfg_lang_per) == 0)
    {
        ui1_g_text_dir = WGL_TEXT_DIR_RIGHT_TO_LEFT;
    }
    else
    {
        ui1_g_text_dir = WGL_TEXT_DIR_LEFT_TO_RIGHT;
    }

    /**/
    if (ui1_g_font_res_decr_num > 0)
    {
        for (ui1_idx = 0;
             ui1_idx < ui1_g_font_res_decr_num;
             ui1_idx ++)
        {
            if ( (ui1_idx < MAX_FONT_ID_NUM) && c_strcmp(at_g_font_res_decr_t[ui1_idx].s639_lang, s639_lang) == 0)
            {
                c_fe_change_font_resource (at_g_font_res_decr_t[ui1_idx].s_font_name,
                                           at_g_font_res_decr_t[ui1_idx].ui1_font_id);
            }
        }
    }    
    return FONTR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_font_set_default_text_dir_callback
 * Description: 
 *      This API will be invoked once only by nav_model since canvas is shared 
 *      among applications and modules.
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_font_set_default_text_dir_callback(
        HANDLE_T                    h_canvas,
        VOID*                       pv_data     /*reserved*/
        )
{
    INT32           i4_ret;
    ISO_639_LANG_T  s639_lang;

    if (h_canvas == NULL_HANDLE)
    {
        return FONTR_INV_ARG;
    }

    /* sync data between ACFG and cached ui1_g_text_dir */
    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if (i4_ret == APP_CFGR_OK)
    {
        a_font_change_text_dir(s639_lang, NULL_HANDLE);
    }

    /* register callback */
    i4_ret = c_wgl_set_canvas_info_callback(h_canvas, 
                                            WGL_CVS_CB_TXT_DIR,
                                            (VOID*)(_font_canvas_text_dir_cb));
    if (i4_ret != WGLR_OK)
    {
        return FONTR_FAIL;
    }

    return FONTR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: a_font_register_font_resource_id
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_font_register_font_resource_id (
      ISO_639_LANG_T                 s639_lang,
      const CHAR                     *ps_font,
      UINT8                          ui1_font_id)      
{
    UINT8   ui1_idx = 0;

    if (ps_font == NULL)
    {
        return FONTR_INV_ARG;
    }

    if (ui1_g_font_res_decr_num >= MAX_FONT_ID_NUM)
    {
        return FONTR_INV_ARG;
    }

    ui1_idx = ui1_g_font_res_decr_num;

    /* insert a record */
    c_strcpy (at_g_font_res_decr_t[ui1_idx].s639_lang,   s639_lang);
    c_strcpy (at_g_font_res_decr_t[ui1_idx].s_font_name, ps_font);
    at_g_font_res_decr_t[ui1_idx].ui1_font_id = ui1_font_id;

    ui1_g_font_res_decr_num++;
    
    return FONTR_OK;
}

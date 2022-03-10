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
 * $RCSfile: c4tv_apron_custom_view.c,v $
 * $Revision: #1 $
 * $Date: 2016/07/25 $
 * $Author: sin_stevenshan $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the view func used by the NAV application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "u_cli.h"
#include "c_dbg.h"
#include "u_common.h"
#include "u_btn_map.h"
#include "x_os.h"
#include "c_os.h"
#include "c_aee.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "nav/nav_common.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "app_util/toast_widget/a_toast.h"

#include "res/app_util/model/model.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom_view.h"

#define C4TV_CUSTOM_VIEW_LOG_PREFIX "[C4TV_CUST] "

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
static C4TV_APRON_CUST_VIEW_T t_g_c4tv_apron_cust_view;

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
INT32 c4tv_apron_custom_view_init(VOID)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    if (pt_this->b_is_init)
    {
        DBG_WARN((C4TV_CUSTOM_VIEW_LOG_PREFIX" c4tv_apron_custom_view_init already.\n"));
        return NAVR_OK;
    }

    DBG_INFO((C4TV_CUSTOM_VIEW_LOG_PREFIX"%s, %d start.\n", __FUNCTION__, __LINE__));

    pt_this->b_is_on        = FALSE;
    pt_this->h_timer        = NULL_HANDLE;
    pt_this->ui4_timeout    = 0;
    pt_this->ui2_timer_count= 0;
    pt_this->h_toast_view   = NULL_HANDLE;
    pt_this->ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;

    pt_this->b_is_init  = TRUE;

    DBG_INFO((C4TV_CUSTOM_VIEW_LOG_PREFIX"%s, %d end.\n", __FUNCTION__, __LINE__));

    return NAVR_OK;
}

INT32 c4tv_apron_custom_view_deinit(VOID)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    DBG_INFO((C4TV_CUSTOM_VIEW_LOG_PREFIX"%s, %d\n", __FUNCTION__, __LINE__));

    if (!pt_this->b_is_init)
    {
        DBG_WARN((C4TV_CUSTOM_VIEW_LOG_PREFIX" c4tv_apron_custom_view_deinit already.\n"));
        return NAVR_OK;
    }

    if (pt_this->b_is_on)
    {
        c4tv_apron_custom_view_hide();
        pt_this->b_is_on = FALSE;
    }

    pt_this->b_is_init  = FALSE;

    return NAVR_OK;
}

INT32 c4tv_apron_custom_view_show(UTF16_T*  pw2s_string)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    pt_this->b_is_on = TRUE;

    return NAVR_OK;
}

INT32 c4tv_apron_custom_view_hide(VOID)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    DBG_INFO((C4TV_CUSTOM_VIEW_LOG_PREFIX"%s, %d\n", __FUNCTION__, __LINE__));

    if (!pt_this->b_is_on)
    {
        DBG_WARN((C4TV_CUSTOM_VIEW_LOG_PREFIX" c4tv_apron_custom_view_hide already.\n"));
        return NAVR_OK;
    }

    pt_this->b_is_on = FALSE;

    return NAVR_OK;
}

INT32 c4tv_apron_custom_timer_start(C4TV_APRON_CUST_VIEW_TIMER_T    e_timer_status,
                                    UINT32                          ui4_timeout)
{
    return NAVR_OK;
}

INT32 c4tv_apron_custom_timer_stop(VOID)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    pt_this->ui2_timer_count = 0;

    return NAVR_OK;
}

INT32 c4tv_apron_custom_timer_restart(VOID)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    pt_this->ui2_timer_count = 0;

    return NAVR_OK;
}

BOOL c4tv_apron_custom_view_is_on(VOID)
{
    C4TV_APRON_CUST_VIEW_T* pt_this = &t_g_c4tv_apron_cust_view;

    return pt_this->b_is_on;
}


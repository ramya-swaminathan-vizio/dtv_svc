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
 * $RCSfile: network_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "stdlib.h"
#include "string.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"

#include "app_util/a_cli_app.h"
#include "app_util/a_cfg.h"
#include "agent/agent.h"
#include "app_util/tvstate/tvstate.h"
#include "app_util/tvstate/smart_dim.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT

extern INT32 ts_cli_get_smart_dim_method(INT32  i4_argc, const CHAR** pps_argv);
extern INT32 ts_cli_get_tv_state(INT32  i4_argc, const CHAR** pps_argv);
extern INT32 ts_cli_stop_detector(INT32  i4_argc, const CHAR** pps_argv);
extern INT32 ts_cli_start_detector(INT32  i4_argc, const CHAR** pps_argv);

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/
INT32 ts_cli_get_smart_dim_method(INT32 i4_argc,const CHAR * * pps_argv)
{
    BOOL    b_support = FALSE;
	INT16   i2_val = 0;
    UINT16  ui2_idx = 0;
    UINT8   ui1_smart_dim_val = a_smart_dim_get_assume_val();
    CHAR    *s_method[] = {
                            "[Off]",
                            "[On]",
                            "[As menu setting]",
                            "[Invalid]"
                          };
    if (ui1_smart_dim_val > 2)
    {
        ui1_smart_dim_val = 3;
    }

    a_cfg_custom_get_is_support_local_dimming(&b_support);
	if (b_support)
	{
		a_cfg_custom_get_dimming_idx(&ui2_idx);
        DBG_INFO((" The Smart dimming acfg is : %d\r\n", ui2_idx));
	}
    else
	{
		a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
        DBG_INFO((" The Smart dimming acfg is : %d\r\n", i2_val));
	}

    DBG_INFO((" The Smart dimming method is : %s\r\n", s_method[ui1_smart_dim_val]));

    return CLIR_OK;
}

INT32 ts_cli_get_tv_state(INT32  i4_argc, const CHAR** pps_argv)
{
    UINT32  ui4_ts = TV_STATE_UNKNOW;

    a_tv_state_get_state(&ui4_ts);

    DBG_INFO((" The TV State is : 0x%x\r\n", ui4_ts));

    return CLIR_OK;
}

INT32 ts_cli_stop_detector(INT32  i4_argc, const CHAR** pps_argv)
{
    return a_tv_state_detector_stop();
}

INT32 ts_cli_start_detector(INT32  i4_argc, const CHAR** pps_argv)
{
    return a_tv_state_detector_start();
}

#endif /* CLI_SUPPORT */


/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: npg.h,v $
 * $Revision: #1 $
 * $Date: 2015/08/25 $
 * $Author: heyi.wang $
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
#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"
#include "c_aee.h"
#include "c_fm.h"
#include "am/a_am.h"
#include "amb/a_amb.h"
#include "agent/a_agent.h"
#include "app_util/a_common.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_network.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/ch_lst/a_ch_lst.h"

#include "app_util/mtktvapi/a_mtktvapi_pop.h"
#include "res/app_util/mtktvapi/mtktvapi_pop_custom.h"

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

/*----------------------------------------------------------------------------- 
                    data, variable declarations 
-----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    private function implementations 
-----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    public function implementations 
-----------------------------------------------------------------------------*/ 

INT32 mtktvapi_custom_pop_enter_next_tv_mode(VOID)
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Turnkey behavior */
}

INT32 mtktvapi_custom_pop_swap_win()
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Turnkey behavior */
}

INT32 mtktvapi_custom_pop_switch_audio_focus()
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Others use turnkey behavior */
}

INT32 mtktvapi_custom_pop_goto_next_win_size()
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Others use turnkey behavior */
}

INT32 mtktvapi_custom_pop_goto_next_win_pos()
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Others use turnkey behavior */
}

INT32  mtktvapi_custom_pop_get_focus_win_info(INT16 *pi2_x,INT16 *pi2_y,INT16 *pi2_w,INT16 *pi2_h)
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Others use turnkey behavior */
}

INT32 mtktvapi_custom_pop_get_focus_id(BOOL *pb_is_main)
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Others use turnkey behavior */
}

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/

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
#include "res/app_util/mtktvapi/a_mtktvapi_volctrl_custom.h"
//#include "nav/npg/a_nav_npg.h"
#include "c_iom.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "u_common.h"
#include "u_btn_map.h"
#include "amb/a_amb.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
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
#ifdef SYS_C4TV_SUPPORT
static UINT16  ui2_vol_custom_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL);
#endif

static UINT8      ui1_g_vol_adjust_reason = MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY;


/*-----------------------------------------------------------------------------
                    private function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    public function implementations
-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/
#ifdef SYS_C4TV_SUPPORT
static INT32  _mtktvapi_volctrl_custom_send_key(UINT32  ui4_key_code)
{
    INT32   i4_ret =0;
    i4_ret = c_iom_send_evt(ui4_key_code,120);
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("c_iom_send_evt_single i4_ret=%d\r\n",i4_ret));
        return MTKTVAPIR_FAIL;
    }
    return MTKTVAPIR_OK;
}
#endif

INT32 a_mtktvapi_volctrl_custom_reg_callback(mtktvapi_volctrl_callback_fct pf_nfy, VOID * pv_tag)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 a_mtktvapi_volctrl_custom_audio_event_register_callback(mtktvapi_volctrl_audio_event_callback_fct pv_fct,
                                            VOID* pv_tag)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}
INT32 a_mtktvapi_volctrl_custom_audio_event_callback_unregister(VOID)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 a_mtktvapi_volctrl_custom_incrVolume(INT16 *pi4_return_current_value)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 a_mtktvapi_volctrl_custom_incrVolume_by_type(INT16 *pi4_return_current_value,INT32 type)
{
    #ifdef SYS_C4TV_SUPPORT
    INT16  i2_value = 0;
    INT32  i4_ret = MTKTVAPIR_OK;

     MTKTVAPI_PRINTF("type = %d.\n", type);
    if(pi4_return_current_value == NULL)
    {
        return MTKTVAPIR_INV_ARG;
    }
    i4_ret = a_tv_vol_incr (ui2_vol_custom_id, &i2_value);

    if(TVR_OK !=  i4_ret )
    {

        MTKTVAPI_LOG_ON_FAIL(i4_ret);
        return MTKTVAPIR_FAIL;
    }

    MTKTVAPI_PRINTF("Volume = %u\n", i2_value);
    *pi4_return_current_value = i2_value;
    //type:0 not show UI
    //TYPE :>0 show UI
    if(type > 0)
    {
        _mtktvapi_volctrl_custom_send_key(BTN_SHOW_VOL_BAR);
        //a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)BTN_SHOW_VOL_BAR, NULL);
        MTKTVAPI_PRINTF("send key to show vol bar\n");
    }
    return i4_ret;
    #else
    return MTKTVAPIR_NOT_IMPLEMENT;
    #endif
}

INT32 a_mtktvapi_volctrl_custom_decrVolume(INT16 *pi4_return_current_value)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 a_mtktvapi_volctrl_custom_decrVolume_by_type(INT16 *pi4_return_current_value,INT32 type)
{

    #ifdef SYS_C4TV_SUPPORT
    INT16  i2_value = 0;
    INT32  i4_ret    = MTKTVAPIR_OK;

    MTKTVAPI_PRINTF("Enter  : b_show_ui =%u\n",
                    type);
    if(pi4_return_current_value == NULL)
    {
        return MTKTVAPIR_INV_ARG;
    }
    i4_ret = a_tv_vol_decr(ui2_vol_custom_id, &i2_value);

    if(TVR_OK !=  i4_ret)
    {
        MTKTVAPI_PRINTF("Call a_tv_vol_decr ret = %u\n",
                        i4_ret);
        return MTKTVAPIR_FAIL;
    }

    MTKTVAPI_PRINTF("Volume = %u\n", i2_value);
    *pi4_return_current_value = i2_value;

    if(type >0 )
    {
       //a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)BTN_SHOW_VOL_BAR, NULL);
        _mtktvapi_volctrl_custom_send_key(BTN_SHOW_VOL_BAR);
    }

    return i4_ret;

    #else
    return MTKTVAPIR_NOT_IMPLEMENT;
    #endif
}

INT32 a_mtktvapi_volctrl_custom_setVolume(INT16 value)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}
INT32 a_mtktvapi_volctrl_custom_setVolume_by_type(INT32 type,INT16 value)
{
    #ifdef SYS_C4TV_SUPPORT

    INT32  i4_ret  = MTKTVAPIR_OK;
	INT16  i4_crnt_tmp_vol_value = 0;


    MTKTVAPI_PRINTF("Enter  :i2_value = %u, b_show_ui =%u\n",
                     value, type);


    i4_ret = a_tv_get_vol(ui2_vol_custom_id, &i4_crnt_tmp_vol_value);
    if(TVR_OK != i4_ret)
    {
    	DBG_LOG_PRINT(("\n[MTKTVAPI_VOLCTRL] a_mtktvapi_volctrl_custom_setVolume_by_type tmp_vol_value GET Fail\n"));
    }


	DBG_LOG_PRINT(("\n[MTKTVAPI_VOLCTRL] a_mtktvapi_volctrl_custom_setVolume_by_type tmp_vol_value[%d], value[%d]\n",
		                   i4_crnt_tmp_vol_value,value));


    /*Value check*/
    if(value>=0&&value<=100)
    {
        i4_ret = a_tv_set_vol(ui2_vol_custom_id, value);

        if(TVR_OK != i4_ret)
        {
            MTKTVAPI_PRINTF(" call a_tv_set_vol ret = %u\n",
                            i4_ret);
            return MTKTVAPIR_FAIL;
        }
    }
    else
    {
        return MTKTVAPIR_FAIL;
    }

    if((type > 0)
		&& (value != i4_crnt_tmp_vol_value))
    {
        //a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)BTN_SHOW_VOL_BAR, NULL);
        _mtktvapi_volctrl_custom_send_key(BTN_SHOW_VOL_BAR);
    }

    return MTKTVAPIR_OK;
    #else
    return MTKTVAPIR_NOT_IMPLEMENT;
    #endif
}
INT32 a_mtktvapi_volctrl_custom_getVolume(INT16 *pi4_return_current_value)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}
INT32 a_mtktvapi_volctrl_custom_getVolume_by_type(INT16 *pi4_return_current_value,INT32 type)
{
    #ifdef SYS_C4TV_SUPPORT
    INT32  i4_ret  = MTKTVAPIR_OK;

    MTKTVAPI_PRINTF("Enter  :b_show_ui =%u\n",
                     type);

    if(pi4_return_current_value == NULL)
    {
        return MTKTVAPIR_INV_ARG;
    }

    i4_ret = a_tv_get_vol(ui2_vol_custom_id, pi4_return_current_value);
    if(TVR_OK != i4_ret)
    {
        MTKTVAPI_PRINTF(" call a_tv_set_vol ret = %u\n",
                        i4_ret);
        return MTKTVAPIR_FAIL;
    }

    if(type > 0)
    {
        //a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)BTN_SHOW_VOL_BAR, NULL);
        _mtktvapi_volctrl_custom_send_key(BTN_SHOW_VOL_BAR);
    }
    return i4_ret;
    #else
    return MTKTVAPIR_NOT_IMPLEMENT;
    #endif
}

INT32 a_mtktvapi_volctrl_custom_setMute(BOOL isMute)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}
INT32 a_mtktvapi_volctrl_custom_setMute_by_type(INT32 type,BOOL isMute)
{
    #ifdef SYS_C4TV_SUPPORT
    MTKTVAPI_PRINTF("Enter  :b_show_ui =%u isMute=%d\n",
                     type,isMute);

    BOOL b_current_mute_status = FALSE;

    b_current_mute_status = a_tv_get_mute();

    MTKTVAPI_PRINTF("Enter  :b_current_mute_status:%d\n",
                     b_current_mute_status);

    if( b_current_mute_status == isMute)
    {
        MTKTVAPI_PRINTF("The mute = %u status is the same, do nothing!\n", isMute);
        return MTKTVAPIR_OK;
    }

    if(type==0)
    {



        if(0 != nav_set_mute(isMute))
        {
            MTKTVAPI_PRINTF("Call nav_set_mute fail \n");
            return MTKTVAPIR_FAIL;
        }
    }

    if(type > 0)
    {
        //if(b_current_mute_status == isMute)
        //a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)BTN_MUTE, NULL);
        _mtktvapi_volctrl_custom_send_key(BTN_MUTE);
    }

    return MTKTVAPIR_OK;
    #else
    return MTKTVAPIR_NOT_IMPLEMENT;
    #endif
}
INT32 a_mtktvapi_volctrl_custom_getMute(BOOL *pb_mute_status)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 a_mtktvapi_volctrl_custom_getMute_by_type(BOOL *pb_mute_status,INT32 type)
{
    #ifdef SYS_C4TV_SUPPORT
     /*MTKTVAPI_PRINTF("Enter  :b_show_ui =%u isMute=%d\n",
                     type);

    if(pb_mute_status==NULL)
    {
        return MTKTVAPIR_INV_ARG;
    }

   // BOOL b_current_mute_status = FALSE;

    *pb_mute_status = a_tv_get_mute();

    MTKTVAPI_PRINTF("Enter  :b_current_mute_status:%d\n",
                     *pb_mute_status);*/

    return MTKTVAPIR_NOT_IMPLEMENT;
    #else
    return MTKTVAPIR_NOT_IMPLEMENT;
    #endif
}
INT32 a_mtktvapi_volctrl_custom_init(VOID)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 a_mtktvapi_volctrl_set_vol_adjust_reason(UINT8 ui1_reason)
{
	ui1_g_vol_adjust_reason = ui1_reason;

	return MTKTVAPIR_OK;
}

INT32 a_mtktvapi_volctrl_get_vol_adjust_reason(UINT8 *pui1_reason)
{
    if (NULL == pui1_reason)
	{
		return MTKTVAPIR_INV_ARG;
	}

	*pui1_reason = ui1_g_vol_adjust_reason;

	return MTKTVAPIR_OK;
}


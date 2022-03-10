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
 * $RCSfile: si_custom_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_svctx.h"

#include "app_util/a_cfg.h"
#include "app_util/a_icl.h"
#include "app_util/a_network.h"

#include "mmp/a_mmp.h"
#include "am/a_am.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#endif

#include "res/app_util/a_custom_log.h"
#include "res/nav/nav_mlm.h"
#include "nav/info_bar/a_info_bar.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "nav/sys_info/sys_info.h"
#include "res/nav/banner2/banner_rc.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#define CUSTOM_INFO_CHK_FAIL(_ret, _ErrorMsg)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("[SI] ERROR. FUNC:%s at LN:%d.\n", __FUNCTION__, __LINE__));      \
    return _ErrorMsg;  \
}   \
}while(FALSE)

#define CUSTOM_INFO_SHOW_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("[SI] WARNING:%d. FUNC:%s at LN:%d.\n", _ret, __FUNCTION__, __LINE__));      \
}   \
}while(FALSE)

typedef enum
{
    SI_CUSTOM_INFO_TYPE_NETWORK_INFO = 0,
    SI_CUSTOM_INFO_TYPE_SCREEN_MODE
}SI_CUSTOM_INFO_TYPE_T;

/*-----------------------------------------------------------------------------
                    private variables
-----------------------------------------------------------------------------*/
static HANDLE_T         h_g_3rd_svctx_main = NULL_HANDLE;

static UINT16           ui2_cfg_scr_mode_nfy_id = APP_CFG_NOTIFY_NULL_ID;
static UINT16           ui_cfg_cast_nfy_id = APP_CFG_NOTIFY_NULL_ID;
static UINT32           ui4_si_nw_nfy_id  = 0;
static UINT16           ui2_icl_nfy_id = 0;  /* The icl notify id */

/*-----------------------------------------------------------------------------
                    private method implementation
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_set
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_set (TV_WIN_ID_T e_win_id, SI_CUSTOM_INFO_TYPE_T e_info_type, VOID* pvData)
{
    INT32 i4_ret;
    SI_SET_INFO_T t_set_info;
    SI_SET_INFO_ZERO(&t_set_info);

    t_set_info.e_category = SI_CATEGORY_CUSTOM_1;

    switch (e_info_type)
    {
        case SI_CUSTOM_INFO_TYPE_NETWORK_INFO:
            t_set_info.u.t_cust_info_1.ui4_info_mask = SI_CUSTOM_INFO_MASK_NETWORK_INFO;
            c_memcpy(&t_set_info.u.t_cust_info_1.t_network_info, (SI_CUSTOM_INFO_NETWORK_INFO_T *)pvData, sizeof(SI_CUSTOM_INFO_NETWORK_INFO_T));
            break;
        case SI_CUSTOM_INFO_TYPE_SCREEN_MODE:
            t_set_info.u.t_cust_info_1.ui4_info_mask = SI_CUSTOM_INFO_MASK_SCREEN_MODE;
            t_set_info.u.t_cust_info_1.i2_scr_mode = *(INT16*)(pvData);
            break;

        default:
            return NAVR_FAIL;
    }
    i4_ret = a_si_set_item_info_by_win_id (e_win_id,
                                          &t_set_info);
    CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_set_resolution
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_set_resolution (TV_WIN_ID_T e_win_id, VOID* pvData)
{
    INT32 i4_ret;
    SI_SET_INFO_T t_set_info;
    SI_SET_INFO_ZERO(&t_set_info);

    t_set_info.e_category = SI_CATEGORY_TUNING_INFO;
    t_set_info.u.t_tuning_info.ui4_info_mask = SI_TUNING_INFO_MASK_VIDEO_RES;

    c_memcpy(&t_set_info.u.t_tuning_info.t_video_res, (VSH_SRC_RESOLUTION_INFO_T *)pvData, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = a_si_set_item_info_by_win_id (e_win_id, &t_set_info);
    CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_reset_resolution
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_reset_resolution(TV_WIN_ID_T e_win_id)
{
    INT32           i4_ret = 0;
    SI_SET_INFO_T   t_set_info;

    SI_SET_INFO_ZERO(&t_set_info);

    t_set_info.e_category = SI_CATEGORY_TUNING_INFO;
    t_set_info.u.t_tuning_info.ui4_info_mask = SI_TUNING_INFO_MASK_VIDEO_RES;

    i4_ret = a_si_unset_item_info_by_win_id(e_win_id, &t_set_info);
    CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_set_inp_src_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_set_inp_src_info (TV_WIN_ID_T e_win_id, VOID* pvData)
{
    INT32 i4_ret;
    SI_SET_INFO_T t_set_info;
    SI_SET_INFO_ZERO(&t_set_info);

    t_set_info.e_category = SI_CATEGORY_TUNING_INFO;

    t_set_info.u.t_tuning_info.ui4_info_mask = SI_TUNING_INFO_MASK_INPUT_SRC_INFO;
    c_memcpy(&t_set_info.u.t_tuning_info.t_input_src_info,
             (SI_TUNING_INFO_INP_SRC_INFO_T *)pvData,
             sizeof(SI_TUNING_INFO_INP_SRC_INFO_T));

    i4_ret = a_si_set_item_info_by_win_id (e_win_id, &t_set_info);

    CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_update_inp_src_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 _si_custom_info_update_inp_src_info (TV_WIN_ID_T e_win_id)
{
    INT32       i4_ret = 0;
    UTF16_T     *pw2s_name = 0;
    ISL_REC_T   t_isl_rec;

    SI_TUNING_INFO_INP_SRC_INFO_T t_tun_input_src_info;
    TV_WIN_ID_T e_curr_win_id = e_win_id;

    c_memset(&t_tun_input_src_info, 0, sizeof(SI_TUNING_INFO_INP_SRC_INFO_T));

    if (e_curr_win_id >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        e_curr_win_id = TV_WIN_ID_MAIN;
    }

    i4_ret = nav_get_isl_rec(e_curr_win_id, &t_isl_rec);
    CUSTOM_INFO_SHOW_FAIL(i4_ret);

    do{
        /* Priority: alias name > input source name */
    #ifdef APP_SI_NAV_NAME_INPUT_MSG_SUPPORT
        /* get input source lable display name */
        a_isl_get_display_name_ex(&t_isl_rec, t_tun_input_src_info.w2s_input_src_name_alias, CECM_OSD_NAME_SIZE);
        if (c_uc_w2s_strlen(t_tun_input_src_info.w2s_input_src_name_alias) > 0)
        {
            break;
        }
    #endif

        /* get input source display name */
        pw2s_name = a_isl_get_display_name(&t_isl_rec);
        c_uc_w2s_strcpy(t_tun_input_src_info.w2s_input_src_name, pw2s_name);
        t_tun_input_src_info.w2s_input_src_name[MAX_INP_SRC_NAME_LEN] = 0;
    }while (0);

    /* update input source ID */
    t_tun_input_src_info.ui1_input_src_id = t_isl_rec.ui1_id;

    i4_ret = _si_custom_info_set_inp_src_info(e_curr_win_id, (VOID *)&t_tun_input_src_info);
    CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_update_via_src_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_update_via_src_info(VOID)
{
    INT32       i4_ret = 0;
    TV_WIN_ID_T e_win_id = TV_WIN_ID_MAIN;

    SI_TUNING_INFO_INP_SRC_INFO_T t_tun_input_src_info;
    c_memset(&t_tun_input_src_info, 0, sizeof(SI_TUNING_INFO_INP_SRC_INFO_T));

    /* set invalid input source id to represent VIA src */
    t_tun_input_src_info.ui1_input_src_id = 255;

    i4_ret = _si_custom_info_set_inp_src_info(e_win_id, (VOID *)&t_tun_input_src_info);
    CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _si_custom_info_nw_notify_handler
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _si_custom_info_nw_notify_handler(
    VOID*          pv_tag1,
    VOID*          pv_tag2,
    VOID*          pv_tag3
)
{
    NW_NFY_ID_T    e_nfy_id = (NW_NFY_ID_T)((UINT32)pv_tag2);
    switch(e_nfy_id)
    {
        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
        case NW_NFY_ID_ETHERNET_PLUGIN:
        case NW_NFY_ID_ETHERNET_UNPLUG:
        case NW_NFY_ID_WLAN_ASSOCIATE:
        case NW_NFY_ID_WLAN_DRIVER_START_FAILED:
        case NW_NFY_ID_ADDRESS_CHANGED:
        #ifdef APP_UPG_SUPPORT
        case NW_NFY_ID_INTERN_CT_UPG_RESULT:
        #endif
            {
                TV_WIN_ID_T             e_tv_win_id;
                SI_CUSTOM_INFO_NETWORK_INFO_T t_network_info;
                BOOL                     b_is_plug = FALSE;
                UINT8                    ui1_interface = APP_CFG_NET_INTERFACE_ETH0;
                NW_WLAN_STATE_T          e_wlan_state;
                BOOL                     b_is_ip_get = FALSE;
                NET_802_11_BSS_INFO_T    t_bss_info;
                NW_DHCP_STATE_T          e_dhcp_state;

                c_memset(&t_network_info, 0, sizeof(SI_CUSTOM_INFO_NETWORK_INFO_T));
                c_memset(&t_bss_info, 0, sizeof(NET_802_11_BSS_INFO_T));

                nav_get_focus_id(&e_tv_win_id);

                a_nw_get_ethernet_connect_info(&b_is_plug);

                if (b_is_plug)
                {
                    ui1_interface = APP_CFG_NET_INTERFACE_ETH0;
                    t_network_info.ui1_interface_type = ui1_interface;
                    t_network_info.e_nfy_id = e_nfy_id;
                }
                else
                {
                    ui1_interface = APP_CFG_NET_INTERFACE_WIFI;

                    a_nw_wlan_status(&e_wlan_state);
                    b_is_ip_get = a_nw_custom_is_get_ip_addr();
                    a_nw_get_dhcp_status(&e_dhcp_state);
                    a_nw_wlan_get_curr_bss(&t_bss_info);

                    t_network_info.b_is_ip_get = b_is_ip_get;
                    t_network_info.ui1_interface_type = ui1_interface;
                    t_network_info.e_wlan_state = e_wlan_state;
                    t_network_info.e_dhcp_state = e_dhcp_state;
                    t_network_info.e_nfy_id = e_nfy_id;
                    c_memcpy(& (t_network_info.t_bss_info), &t_bss_info, sizeof(NET_802_11_BSS_INFO_T));
                }

                _si_custom_info_set(e_tv_win_id, SI_CUSTOM_INFO_TYPE_NETWORK_INFO, (VOID*)&t_network_info);
            }
            break;
        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _si_custom_info_nw_notify_callback
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _si_custom_info_nw_notify_callback(
    VOID*          pv_tag,
    NW_NFY_ID_T    e_nfy_id,
    VOID*          pv_nfy_param
)
{
    nav_request_context_switch(_si_custom_info_nw_notify_handler,
                              (VOID*)pv_tag,
                              (VOID*)e_nfy_id,
                              (VOID*)pv_nfy_param);
}

/*----------------------------------------------------------------------------
 * Name: _si_custom_info_update_screen_mode
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _si_custom_info_update_screen_mode(VOID)
{
    INT16           i2_scr_mode = 0;
    TV_WIN_ID_T     e_tv_win_id = TV_WIN_ID_MAIN;

    nav_get_focus_id(&e_tv_win_id);
    a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),
                  &i2_scr_mode);

    DBG_LOG_PRINT(("[SI] --- update screen mode.\n"));

    _si_custom_info_set(e_tv_win_id, SI_CUSTOM_INFO_TYPE_SCREEN_MODE, (VOID *)&i2_scr_mode);

    return;
}

/*----------------------------------------------------------------------------
 * Name: _si_custom_info_screen_mode_notify_handler
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _si_custom_info_screen_mode_notify_handler(
    VOID*                               pv_ui2_id,
    VOID*                               pv_unused1,
    VOID*                               pv_unused2)
{
    UINT16          ui2_id = (UINT16)(UINT32)pv_ui2_id;

    if (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE) == ui2_id)
    {
        _si_custom_info_update_screen_mode();
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _si_custom_info_scr_mode_notify_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _si_custom_info_scr_mode_notify_cb(
    UINT16                        ui2_nfy_id,
    VOID*                         pv_tag,
    UINT16                        ui2_id)
{
    if (ui2_cfg_scr_mode_nfy_id != ui2_nfy_id)
    {
        return;
    }

    if (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE) == ui2_id)
    {
        /*post a message to itself*/
        nav_request_context_switch(_si_custom_info_screen_mode_notify_handler,
                                   (VOID*)(UINT32)ui2_id,
                                   NULL,
                                   NULL);
    }

    return;
}

#ifdef APP_C4TV_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_is_cast_source
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _si_custom_info_is_cast_source(VOID)
{
    INT32                       i4_ret = 0;
    TV_WIN_ID_T                 e_focus_id = TV_WIN_ID_MAIN;
    ISL_REC_T                   t_isl_rec;

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type &&
        DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_reset_audio_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_reset_audio_info(
                TV_WIN_ID_T             e_tv_win_id
                )
{
    SI_SET_INFO_T   t_set_info;

    KK_LOG(KK_LOG_LVL_NORMAL, "[SI]", "reset digital audio info.\n");

    c_memset(&t_set_info, 0 , sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;

    #if 0
    t_set_info.u.t_aud_strm_info.ui4_info_mask =
                                SI_AUD_INFO_MASK_SEL_NUM |
                                SI_AUD_INFO_MASK_SEL_IDX |
                                SI_AUD_INFO_MASK_ANA_AUD_MTS |
                                SI_AUD_INFO_MASK_DIG_AUD_STS |
                                SI_AUD_INFO_MASK_DIG_AUD_LANG |
                                SI_AUD_INFO_MASK_DIG_AUD_LANG2 |
                                SI_AUD_INFO_MASK_DIG_AUD_TYPE |
                                SI_AUD_INFO_MASK_DIG_AUD_INFO ;
    #else
    t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_DIG_AUD_INFO;
    #endif

    return a_si_unset_item_info_by_win_id(e_tv_win_id, &t_set_info);
}


/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_update_digital_audio_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_update_digital_audio_info(
                TV_WIN_ID_T             e_grp,
                HANDLE_T                h_svctx
                )
{
    INT32            i4_ret = NAVR_OK;
    ASH_AUDIO_INFO_T t_audio_info;
    SI_SET_INFO_T    t_set_info;

    KK_LOG(KK_LOG_LVL_NORMAL, "[SI]", "update digital audio info.\n");

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    i4_ret = c_svctx_get_audio_info(h_svctx, &t_audio_info);
    if(i4_ret != SVCTXR_OK)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[SI]", "c_svctx_get audio_info failed !!!\n");
        return NAVR_FAIL;
    }

    c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
    t_set_info.u.t_aud_strm_info.ui4_info_mask =
                                SI_AUD_INFO_MASK_DIG_AUD_STS |
                                SI_AUD_INFO_MASK_DIG_AUD_LANG |
                                SI_AUD_INFO_MASK_DIG_AUD_INFO ;
    t_set_info.u.t_aud_strm_info.e_dig_aud_sts = SI_AUD_DIG_AUD_STS_NORMAL;
    t_set_info.u.t_aud_strm_info.t_dig_aud_info = t_audio_info;

    i4_ret = a_si_set_item_info_by_win_id(e_grp, &t_set_info);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _si_custom_info_3rd_svctx_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _si_custom_info_3rd_svctx_msg_hdlr(
    VOID*                               pv_tag1,
    VOID*                               pv_tag2,
    VOID*                               pv_tag3)
{

    CHAR                            s_app_name [APP_NAME_MAX_LEN + 1];
    SVCTX_NTFY_CODE_T               e_code = (SVCTX_NTFY_CODE_T)pv_tag2;
    TV_WIN_ID_T                     e_win_id = TV_WIN_ID_MAIN ;
    VSH_SRC_RESOLUTION_INFO_T       t_video_resolution = {0};
    HANDLE_T                        h_svctx = NULL_HANDLE;
    INT32                           i4_ret;

    i4_ret = nav_get_focus_id (&e_win_id) ;
    if (i4_ret != NAVR_OK) {
        return;
    }

    i4_ret = nav_get_svctx_handle(e_win_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return;
    }

    a_am_get_active_app(s_app_name);

    /* here will only deal with the cast and mmp case*/
    if (TRUE == _si_custom_info_is_cast_source()
        || TRUE == a_c4tv_apron_check_cast_state()
        || (c_strcmp(s_app_name, MMP_NAME) == 0))
    {
        KK_LOG(KK_LOG_LVL_KEY, "[SI]", "need handle SVCTX_NTFY_CODE: [%d].\n", e_code);
    }
    else
    {
        return;
    }

    /* video info */
    if (e_code == SVCTX_NTFY_CODE_SERVICE_CHANGING
        || e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS
        || e_code == SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC
        || e_code == SVCTX_NTFY_CODE_STOPPED
        || e_code == SVCTX_NTFY_CODE_STREAM_STOPPED)
    {
        /* for the above svctx notify should reset the video resolution info*/
        i4_ret = _si_custom_info_reset_resolution(e_win_id);
        if (NAVR_OK != i4_ret)
        {
            return;
        }

        i4_ret = _si_custom_info_reset_audio_info(e_win_id);
        if (NAVR_OK != i4_ret)
        {
            return;
        }
    }
    else if (e_code == SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE ||
        e_code == SVCTX_NTFY_CODE_STREAM_STARTED)
    {
       c_memset (&t_video_resolution, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));
       i4_ret = c_svctx_get_video_src_resolution(h_svctx, &t_video_resolution);

       if (i4_ret == NAVR_OK)
       {
            if (t_video_resolution.e_timing_type == VSH_SRC_TIMING_NOT_SUPPORT)
            {
                /* here should reset the video info*/
                i4_ret = _si_custom_info_reset_resolution(e_win_id);
                if (NAVR_OK != i4_ret)
                {
                    return;
                }
            }
            else
            {
                /* here should updater the video info*/
                i4_ret = _si_custom_info_set_resolution(e_win_id, (VOID*) &t_video_resolution);
                if (NAVR_OK != i4_ret)
                {
                    return;
                }
            }
        }
    }
    else if (e_code == SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE)
    {
        _si_custom_info_update_digital_audio_info(e_win_id, h_svctx);
    }
    else
    {
        /* as here will only deal with the video case , so should do nothing here*/
    }

    return;
}

/*-----------------------------------------------------------------------------
* Name
*      _si_custom_info_3rd_svctx_notify_fct
* Description
* Input arguments
* Output arguments
* Returns  -
*---------------------------------------------------------------------------*/

static VOID _si_custom_info_3rd_svctx_notify_fct(
    HANDLE_T            h_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if(e_nfy_cond == SVCTX_COND_PENDING_SELECT_SAME_REQ ||
       e_nfy_cond == SVCTX_COND_PRESENTING_SELECT_SAME_REQ)
    {
        switch(e_code){
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
            break;
        default:
            return;
        }
    }

    if(e_code == SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE          ||
       e_code == SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE          ||
       e_code == SVCTX_NTFY_CODE_VIDEO_ANA_COLOR_SYSTEM    ||
       e_code == SVCTX_NTFY_CODE_SIGNAL_LOCKED             ||
       e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS               ||
       e_code == SVCTX_NTFY_CODE_SIGNAL_LOCKED_AS_BLOCKED  ||
       e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS_AS_BLOCKED    ||
       e_code == SVCTX_NTFY_CODE_SERVICE_CHANGING          ||
       e_code == SVCTX_NTFY_CODE_SERVICE_BLOCKED           ||
       e_code == SVCTX_NTFY_CODE_STOPPED                   ||
       e_code == SVCTX_NTFY_CODE_INP_SIGNAL_UNKNOWN        ||
       e_code == SVCTX_NTFY_CODE_INTERRUPTED               ||
       e_code == SVCTX_NTFY_CODE_STREAM_STOPPED            ||
       e_code == SVCTX_NTFY_CODE_STREAM_STARTED            ||
       e_code == SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC        ||
       e_code == SVCTX_NTFY_CODE_NORMAL)
    {
        /*post a message to itself*/
        nav_request_context_switch(_si_custom_info_3rd_svctx_msg_hdlr,
                                   (VOID*)e_nfy_cond,
                                   (VOID*)e_code,
                                   (VOID*)e_stream_type);
    }
}

/*----------------------------------------------------------------------------
 * Name: _sys_icl_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _sys_icl_msg_hdlr(
                    VOID*           pv_unused1,
                    VOID*           pv_unused2,
                    VOID*           pv_unused3
                    )
{
    _si_custom_info_update_inp_src_info(TV_WIN_ID_MAIN);
}

/*----------------------------------------------------------------------------
 * Name: _sys_icl_nfy_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _sys_icl_nfy_cb(UINT16     ui2_nfy_id,
                             VOID*      pv_tag,
                             ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32               i4_ret;
    ICL_GRPID_TYPE      e_grp_id;
    UINT8               ui1_status = ICL_RECID_CUSTOM_NOTHING_CHANGE;
    SIZE_T              z_size = ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE;

    e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_CUSTOM_FLAG_CHANGE)
    {
        return NAVR_OK;
    }

    /* get icl custom flag change status */
    i4_ret = a_icl_get (ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_FLAG_CHANGE), &ui1_status, &z_size);
    if (ICLR_OK != i4_ret)
    {
        return NAVR_OK;
    }

    DBG_LOG_PRINT(("[SI] --- icl custom flag change type = %d.\n", ui1_status));

    if (ICL_RECID_CUSTOM_INPUT_NAME_CHANGE == ui1_status)
    {
        /* post a message to itself */
        nav_request_context_switch(_sys_icl_msg_hdlr,
                                   NULL,
                                   NULL,
                                   NULL);
    }

    return NAVR_OK;
}

static VOID _nav_cast_status_acfg_nfy(
                    UINT16     ui2_nfy_id,
                    VOID*      pv_tag,
                    UINT16     ui2_id
                    )
{
    UINT16          ui2_rec_id = CFG_GET_SETTING(ui2_id);
    CHAR            s_disp_name[33] = {0};
    UINT8           ui1_input_id = 0;
    ISL_REC_T       t_isl_rec;

	if (APP_CFG_RECID_INPUT_MAIN == ui2_rec_id)
	{
		a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
		a_cfg_get_input_src(s_disp_name, &ui1_input_id);
		a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);


		if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
		{
            banner_view_clean_av_item();
			if (a_nav_get_show_banner_expecial_btn())
			{
				a_nav_show_banner_ex();
				a_nav_set_show_banner_expecial_btn(FALSE);
			}
		}
	}

}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_init(VOID)
{
    INT32               i4_ret;

    /* register to network utility */
    i4_ret = a_nw_register (_si_custom_info_nw_notify_callback,
                            NULL,
                            &ui4_si_nw_nfy_id);
    if(NWR_OK != i4_ret)
    {
        DBG_ERROR(("<SI_TUNIG>Can't a_nw_register"));
        ui4_si_nw_nfy_id = 0;
        return NAVR_FAIL;
    }

    /* register to ACFG to listen screen mode change notify */
    i4_ret = a_cfg_notify_reg (APP_CFG_GRPID_VIDEO,
                            NULL,
                            _si_custom_info_scr_mode_notify_cb,
                            &ui2_cfg_scr_mode_nfy_id);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR(("<SI_TUNIG>Can't a_cfg_notify_reg APP_CFG_GRPID_VIDEO"));
        ui2_cfg_scr_mode_nfy_id = APP_CFG_NOTIFY_NULL_ID;
        return NAVR_FAIL;
    }

    /* SVCTX */
    i4_ret = c_svctx_open (SVCTX_NAME_MAIN, &h_g_3rd_svctx_main);
    if(i4_ret != SMR_OK)
    {
        DBG_ERROR(("<SI_TUNIG>Can't Open SVCTX handle"));
        h_g_3rd_svctx_main = NULL_HANDLE;
        return NAVR_FAIL;
    }

    i4_ret = c_svctx_set_listener (h_g_3rd_svctx_main,
                            _si_custom_info_3rd_svctx_notify_fct,
                            NULL);
    if(i4_ret != SMR_OK)
    {
        DBG_ERROR(("<SI_TUNIG>Can't c_svctx_set_listener"));
        c_svctx_close (h_g_3rd_svctx_main);
        h_g_3rd_svctx_main = NULL_HANDLE;
        return NAVR_FAIL;
    }

    i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_FLAG_CHANGE,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _sys_icl_nfy_cb,
                              &ui2_icl_nfy_id);


    if(ICLR_OK != i4_ret)
    {
        ui2_icl_nfy_id = 0;
        return NAVR_FAIL;
    }

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_NAV,
                             NULL,
                             _nav_cast_status_acfg_nfy,
                             &ui_cfg_cast_nfy_id);

    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR(("<SI_TUNIG>Can't a_cfg_notify_reg APP_CFG_GRPID_MISC"));
        ui_cfg_cast_nfy_id = APP_CFG_NOTIFY_NULL_ID;
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_deinit(VOID)
{
    INT32  i4_ret;

    if (ui2_icl_nfy_id)
    {
        i4_ret = a_icl_notify_unreg(ui2_icl_nfy_id);
        CUSTOM_INFO_SHOW_FAIL(i4_ret);

        ui2_icl_nfy_id = 0;
    }

    if (ui4_si_nw_nfy_id)
    {
        i4_ret = a_nw_unregister (ui4_si_nw_nfy_id);
        CUSTOM_INFO_SHOW_FAIL(i4_ret);

        ui4_si_nw_nfy_id = 0;
    }

    if (APP_CFG_NOTIFY_NULL_ID != ui2_cfg_scr_mode_nfy_id)
    {
        a_cfg_notify_unreg (ui2_cfg_scr_mode_nfy_id);
        ui2_cfg_scr_mode_nfy_id = APP_CFG_NOTIFY_NULL_ID;
    }

    if (NULL_HANDLE != h_g_3rd_svctx_main)
    {
        c_svctx_close (h_g_3rd_svctx_main);
        h_g_3rd_svctx_main = NULL_HANDLE;
    }

    if (APP_CFG_NOTIFY_NULL_ID != ui_cfg_cast_nfy_id)
    {
        a_cfg_notify_unreg (ui_cfg_cast_nfy_id);
        ui_cfg_cast_nfy_id = APP_CFG_NOTIFY_NULL_ID;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _si_custom_info_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _si_custom_info_handle_msg (NAV_UI_MSG_T   *pt_ui_msg,
                                         VOID           *pv_arg1)
{
    INT32  i4_ret;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_OTHER_APP_RESUMED:
            /* If next APP is MMP, sync info. */
            if (c_strcmp ((CHAR*)pv_arg1, MMP_NAME) == 0)
            {
                i4_ret = _si_custom_info_update_via_src_info();
                CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);
            }
            break;

        case NAV_UI_MSG_OTHER_APP_PAUSED:
            /* If paused APP is MMP, sync info. */
            if (c_strcmp ((CHAR*)pv_arg1, MMP_NAME) == 0)
            {
                i4_ret = _si_custom_info_update_inp_src_info(pt_ui_msg->e_tv_win_id);
                CUSTOM_INFO_CHK_FAIL(i4_ret, NAVR_FAIL);
            }
            break;
        case NAV_UI_MSG_NO_SIGNAL:
            _si_custom_info_update_screen_mode();
            break;

        case NAV_UI_MSG_EMPTY_SVL:
        case NAV_UI_MSG_EMPTY_SPECIFIED_CH_LIST:
            _si_custom_info_update_screen_mode();
            break;

        case NAV_UI_MSG_AS_APP_PAUSED:
#ifdef APP_SI_NAV_PAUSED_MSG_SUPPORT
            switch(pt_ui_msg->e_id_as_paused)
            {
                case NAV_UI_MSG_STREAM_NOTIFY:
                {
                    NAV_STREAM_NOTIFY_DATA_T* pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;

                    switch(pt_nfy_data->e_strm_type)
                    {
                        case ST_VIDEO:
                            if (NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
                            {
                                //_si_custom_info_reset(TV_WIN_ID_MAIN);
                                _si_custom_info_update_screen_mode();
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;

                default:
                    break;
            }
#endif
            break;

        case NAV_UI_MSG_STREAM_NOTIFY:
        {
            NAV_STREAM_NOTIFY_DATA_T* pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;

            switch(pt_nfy_data->e_strm_type)
            {
                case ST_VIDEO:
                    if (NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
                    {
                        _si_custom_info_update_screen_mode();
                    }
                    break;

                default:
                    break;
            }
        }
        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
                    export method implementation
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      si_custom_info_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 si_custom_info_register(VOID)
{
    SI_SUBCOMP_T    t_comp;
    INT32           i4_ret = NAVR_OK;

    c_memset(& t_comp, 0, sizeof(SI_SUBCOMP_T));

    t_comp.t_fct_tbl.pf_init        = _si_custom_info_init;
    t_comp.t_fct_tbl.pf_deinit      = _si_custom_info_deinit;
    t_comp.t_fct_tbl.pf_handle_msg  = _si_custom_info_handle_msg;

    i4_ret = si_register_subcomponent(SI_SUBCOMP_ID_CUSTOM_1, & t_comp);
    if (NAVR_OK != i4_ret) { return i4_ret; }

    return NAVR_OK;
}

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
 * $RCSfile: tvstatus.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_svctx.h"
#include "c_fm.h"

#include "app_util/a_key_seq.h"

#include "menu2/menu.h"
#include "menu2/menu_device/menu_page_device_status_info.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_network_phase1/menu_network.h"
#include "app_util/a_cfg.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"


#include "app_util/a_network.h"
#include "wfrrc_interface.h"

#include "tvstate/tvstatus.h"
#include "mmp/a_mmp.h"

#include "u_xml.h"
#include "c_xml_api.h"

#include "c_dlm.h"
#include "c_fm.h"
#include "c_pcl.h"

#include "res/app_util/updater/a_updater_custom.h"

#include "u_cecm.h"
#include "c_cecm.h"
#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifdef APP_SUPPORT_STATUS_DETECT
BOOL b_g_enable_tvstat = TRUE;
#else
BOOL b_g_enable_tvstat = FALSE;
#endif
/*-----------------------------------------------------------------------------
                    typedefs
-----------------------------------------------------------------------------*/

/*
   TVSTATUS Model data.
*/

struct _TVSTATUS_MODEL_T;
struct _TVSTATUS_UNI_MODEL_T;

/* WGL Notify */
typedef struct _TVSTATUS_MSG_WGL_NOTIFY_T {
    UINT32      ui4_msg;
    VOID*       pv_param1;
    VOID*       pv_param2;
} TVSTATUS_MSG_WGL_NOTIFY_T;

/* CLI */
#ifdef CLI_SUPPORT
typedef struct _TVSTATUS_CLI_DATA_T {
    x_cli_exec_fct pf_cli_func; /* in  */
    INT32        i4_argc;       /* in  */
    const CHAR** pps_argv;      /* in  */
    INT32        i4_ret;        /* out */
} TVSTATUS_CLI_DATA_T;
#endif
/*  Macros */
#define TVSTATUS_MODEL_NAME_LEN             (16 + 1 + 6)
#define TVSTATUS_MODEL_GROUP_LEN            (4)
#define TVSTATUS_SERIAL_NUM_LEN             (64)
#define TVSTATUS_FIRMWARE_VER_LEN           (64)
#define TVSTATUS_ETHERNET_MAC_LEN           (32)
#define TVSTATUS_WIFI_MAC_LEN               (32)
#define TVSTATUS_CHIPSET_LEN                (10)
#define TVSTATUS_ODM_LEN                    (10)
#define TVSTATUS_SCREEN_SIZE_LEN            (3)
#define TVSTATUS_REMOTE_VER_LEN             (5)
#define TVSTATUS_WZD_REG_INFO_LEN           (64+1)
#define TVSTATUS_INPUT_SOURCE_LEN           (12)
#define TVSTATUS_COUNTRY_LEN                (10)
#define TVSTATUS_WIRE_LESS_SECURITY_LEN     (18)
#define TVSTATUS_PIC_MODE_LEN               (32+1)
#define TVSTAUS_PIC_MODE_STANDARD           (0)
#define TVSTAUS_PIC_MODE_CALIBRATED         (1)
#define TVSTAUS_PIC_MODE_CALIBRATED_DARK    (2)
#define TVSTAUS_PIC_MODE_VIVID              (3)
#define TVSTAUS_PIC_MODE_GAME               (4)
#define TVSTAUS_PIC_MODE_COMPUTER           (5)
#define TVSTAUS_PIC_MODE_NUM                (6)
#define TVSTAUS_REG_INFO_MAX_LEN            (64)
#define TVSTAUS_NETWORK_SPEED_LEN           (16)
#define TVSTAUS_DEVICE_TYPE_LEN             (32)
#define TVSTATUS_CAST_APP_ID_LEN            (32)


#define TVSTAUS_STATIC_PATH_LEN             (64)
#define TVSTAUS_DYNAMIC_PATH_LEN            (64)
#define TVSTAUS_CMD_LEN                     (128)


typedef struct _TVSTATUS_UNI_MODEL_T
{
    CHAR                  s_model_group[TVSTATUS_MODEL_GROUP_LEN];
    CHAR                  s_ver[TVSTATUS_FIRMWARE_VER_LEN];
    CHAR                  s_model_name[TVSTATUS_MODEL_NAME_LEN];
    CHAR                  s_modsn[TVSTATUS_SERIAL_NUM_LEN];
    CHAR                  s_mac_estr[TVSTATUS_ETHERNET_MAC_LEN];
    CHAR                  s_mac_wstr[TVSTATUS_WIFI_MAC_LEN];
    CHAR                  s_chipset_id[TVSTATUS_CHIPSET_LEN];
    CHAR                  s_odm[TVSTATUS_ODM_LEN];
    CHAR                  s_screen_size[TVSTATUS_SCREEN_SIZE_LEN];
    CHAR                  s_remote_ver[TVSTATUS_REMOTE_VER_LEN];
    CHAR                  s_email[TVSTATUS_WZD_REG_INFO_LEN];
    CHAR                  s_first_name[TVSTATUS_WZD_REG_INFO_LEN];
    CHAR                  s_last_name[TVSTATUS_WZD_REG_INFO_LEN];
    CHAR                  s_phone_num[TVSTATUS_WZD_REG_INFO_LEN];
    CHAR                  s_zip_code[TVSTATUS_WZD_REG_INFO_LEN];
}TVSTATUS_UNI_MODEL_T;

typedef struct _TVSTATUS_SHI_MODEL_T
{
    CHAR                  s_input_source[TVSTATUS_INPUT_SOURCE_LEN];
    CHAR                  s_device_osd_name[TVSTAUS_DEVICE_TYPE_LEN];
    CHAR                  s_device_vendor_id[TVSTAUS_DEVICE_TYPE_LEN];
    CHAR                  s_third_party_app[TVSTAUS_DEVICE_TYPE_LEN];
    ISO_639_LANG_T        crn_s639_lang;
    CHAR                  s_country[TVSTATUS_COUNTRY_LEN];
    UINT8                 ui1_scan_type;
    UINT8                 ui1_channel_scan_status;
    UINT8                 ui1_parental_ctrl;
    UINT8                 ui1_wfi_enab;
    CHAR                  s_pic_mod[TVSTATUS_PIC_MODE_LEN];
    INT32                 i4_sgnl;
    INT16                 i2_Channel;
    INT16                 i2_Noise;
    BOOL                  b_wf_plug;
    UINT8                 ui1_wirleband;
    CHAR                  s_wire_less_scurity[TVSTATUS_WIRE_LESS_SECURITY_LEN];
    UINT32                ui4_boot_up_times;
    UINT32                ui4_running_time;
    UINT16                ui2_audio_state;
    UINT8                 ui1_network_speed;
    CHAR                  s_network_speed[TVSTAUS_NETWORK_SPEED_LEN];
    CHAR                  s_cast_app_id[TVSTATUS_CAST_APP_ID_LEN];
}TVSTATUS_SHI_MODEL_T;

typedef enum _E_DATA_TYPE
{
    E_DATA_TYPE_UNI_DATA = 0,
    E_DATA_TYPE_SHI_DATA,
    E_DATA_TYPE_LAST
}E_DATA_TYPE;

typedef INT32 (*tvstate_cfg_parse_fw_info_fct) (struct _TVSTATUS_MODEL_T* pt_hdlr);

typedef struct _TVSTATUS_MODEL_T
{
    HANDLE_T               h_tvstatus;         /* tvstatus application handle. */

#ifdef CLI_SUPPORT
    HANDLE_T               h_sema_cli;      /* binary semaphore for CLI */
    BOOL                   b_cli_flag;      /* FALSE= No CLI running in tvstatus thread.
                                               TRUE = CLI running in tvstatus thread */
#endif

    HANDLE_T               h_wait_sema;
    HANDLE_T               h_sync_sema;

    HANDLE_T               h_detect_timer;

    UINT16                 ui2_acfg_nav_nfy;

    XML_T*                             pt_data_xml;
    tvstate_cfg_parse_fw_info_fct      pf_parse_status_info;


}   TVSTATUS_MODEL_T;


#define _SYNCHRONIZED_BEGIN(_h_token)       c_sema_lock(_h_token, X_SEMA_OPTION_WAIT)
#define _SYNCHRONIZED_END(_h_token)         c_sema_unlock(_h_token)
#define _WAIT(_h_token)                     c_sema_lock(_h_token, X_SEMA_OPTION_WAIT)
#define _WAIT_TIMEOUT(_h_token, _delay)     c_sema_lock_timeout(_h_token, _delay)
#define _NOTIFY(_h_token)                   c_sema_unlock(_h_token)
#define _TVSTATUS_TIMEOUT_DUR               ((UINT32)1*60*1000)

#define TVSTATUS_XML_VALUE(pt_xml)          ((pt_xml != NULL) ? XML_Value(pt_xml) : "")

#define TVSTATUS_XML_HDR_SZ                 ((UINT32)(16 * 1024))

#define TVSTATUS_PARTITION_TIMER_DELAY      (UINT32)1000
#define TVSTATUS_PARTITION_TIMER_RUN_TIMES  (UINT16)30

#define TVTSTAUS_TMP_STR_MAX_LEN            (63)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static TVSTATUS_MODEL_T  t_g_model;
static TVSTATUS_UNI_MODEL_T t_g_uni_mode;
static TVSTATUS_SHI_MODEL_T t_g_shi_mode;

/* Timer of get mac addr and tv serial number */
static HANDLE_T                             h_partition_timer = NULL_HANDLE;
static UINT16                               ui2_try_num = 0;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern VOID a_tv_custom_resume_tvis();
extern VOID a_tv_custom_stop_tvis();
extern VOID a_tv_custom_resume_dai();
extern VOID a_tv_custom_resume_bt();

static INT32 _tvstate_parse_status_info(
    TVSTATUS_MODEL_T*         pt_this
);
static INT32 _tvstate_parse_xml_to_status_info(
    E_DATA_TYPE               e_type,
    CHAR*                     ps_path,
    VOID*                     pt_static_info,
    XML_T**                   ppt_xml
);
static INT32 _tvstatus_fill_status_info(
    E_DATA_TYPE               e_type,
    XML_T*                    pt_data_xml,
    VOID*                     pt_static_info
);
static INT32 _tvstate_update_info(
    E_DATA_TYPE               e_type,
    CHAR*                     ps_path,
    XML_T**                   ppt_xml
);
static INT32 _tvstatus_update_info_to_xml(
    E_DATA_TYPE               e_type,
    XML_T*                    pt_data_xml
);
static INT32 _tvstate_print_info(
    TVSTATUS_MODEL_T*         pt_this,
    E_DATA_TYPE               e_type
);

static INT32 _tvstatus_start_partition_timer();

static INT32 _tvstatus_cust_get_serial_num();

static INT32 _tvstatus_cust_get_rj_mac();

static INT32 _tvstatus_dynamic_info_ass(VOID);

static BOOL _tvstatus_get_tmp_folder_xml_exist(VOID)
{
    /* This is tvis work folder*/
    BOOL    b_xml_file_exist = FALSE;
static CHAR s_static_path[TVSTAUS_STATIC_PATH_LEN] = {'\0'};
static CHAR s_dynamic_path[TVSTAUS_DYNAMIC_PATH_LEN] = {'\0'};

    if (c_strlen(s_static_path) == 0 || c_strlen(s_dynamic_path) == 0)
    {
        c_sprintf(s_static_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_STATIC_XML_NAME);
        c_sprintf(s_dynamic_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_DYNAMIC_XML_NAME);
    }

    //tmp xml data
    b_xml_file_exist = ((access(s_static_path, F_OK) == 0 ? TRUE : FALSE)
                         &&
                         (access(s_dynamic_path, F_OK) == 0 ? TRUE : FALSE)
                        );
    DBG_INFO(("%s() %d: %s exist=%d\n",__FUNCTION__,__LINE__,TVSTATE_XML_PATH,b_xml_file_exist));
    return b_xml_file_exist;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_cust_get_serial_num
 *
 * Description:
 *       tvstatus will call this function regularly.
 *       get the serial number.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _tvstatus_cust_get_serial_num(VOID)
{
    INT32           i4_ret;
    CHAR            s_sn[64] = {0};
    CHAR            s_tmn[128] = {0};
    UINT32          ui4_buff_len = sizeof(s_sn);

    i4_ret = a_uli_get_serial_number((UINT8 *)&(s_sn[0]), &ui4_buff_len);

    TVSTATUS_LOG_ON_FAIL(i4_ret);

    if(0 == c_strlen(s_sn))
    {
        c_strcpy(s_sn, "000000000000");

        DBG_INFO(("%s() s_dst=[%s]......\r\n",__FUNCTION__, (char *)s_sn));
        c_snprintf(s_tmn, 128, "echo \"%s\" > /tmp/cfg_tv_sn", (char *)s_sn);

        system(s_tmn);

        return TVSTAR_FAIL;
    }

    c_snprintf(s_tmn, 128, "echo \"%s\" > /tmp/cfg_tv_sn", (char *)s_sn);

    system(s_tmn);

    DBG_INFO(("%s() s_dst=[%s] len:%d......\r\n",__FUNCTION__, (char *)s_sn, c_strlen(s_sn)));

    return TVSTAR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _tvstatus_cust_get_rj_mac
 *
 * Description:
 *       tvstatus will call this function regularly.
 *       get the RJ MAC number.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _tvstatus_cust_get_rj_mac(VOID)
{
    INT32           i4_ret = TVSTAR_OK;
    CHAR            s_mac_str[64];
    CHAR            s_tmn[128] = {0};
    c_memset(s_mac_str,0, sizeof(s_mac_str));

    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    if(0 == c_strlen(s_mac_str))
    {
        DBG_INFO(("%s() s_dst=[%s] ......\r\n",__FUNCTION__, (char *)s_mac_str));

        return TVSTAR_FAIL;
    }

    c_snprintf(s_tmn, 128, "echo \"%s\" > /tmp/rj45_mac", (char *)s_mac_str);

    i4_ret = system(s_tmn);

    DBG_INFO(("%s() s_dst=[%s] ......\r\n",__FUNCTION__, (char *)s_tmn));

    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name: _tvstatus_wgl_event_dispatcher
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _tvstatus_wgl_event_dispatcher(
                    VOID*                       pv_data,
                    SIZE_T                      z_data_len)
{
    TVSTATUS_MSG_WGL_NOTIFY_T*  pt_nfy = (TVSTATUS_MSG_WGL_NOTIFY_T*)pv_data;

    c_wgl_dispatch_event(pt_nfy->ui4_msg,
                         pt_nfy->pv_param1,
                         pt_nfy->pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _tvstate_parse_status_info
 *
 * Description: This func is used to parse the fw info from xml
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _tvstate_parse_status_info(
    TVSTATUS_MODEL_T*      pt_this
)
{
    INT32                i4_ret;

    /* get info from XML */
    i4_ret = _tvstate_parse_xml_to_status_info(E_DATA_TYPE_UNI_DATA,
                                            TVSTATE_XML_PATH "/" TVSTATE_STATIC_XML_NAME,
                                            &t_g_uni_mode,
                                            &(pt_this->pt_data_xml));

    if (TVSTAR_OK != i4_ret)
    {
        return TVSTAR_FAIL;
    }

    i4_ret = _tvstate_parse_xml_to_status_info(E_DATA_TYPE_SHI_DATA,
                                            TVSTATE_XML_PATH "/" TVSTATE_DYNAMIC_XML_NAME,
                                            &t_g_shi_mode,
                                            &(pt_this->pt_data_xml));
    if (TVSTAR_OK != i4_ret)
    {
        return TVSTAR_FAIL;
    }

    return TVSTAR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _tvstate_parse_status_info
 *
 * Description: This func is used to parse xml to fw info.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _tvstate_parse_xml_to_status_info(

    E_DATA_TYPE               e_type,
    CHAR*                     ps_path,
    VOID*                     pt_data_info,
    XML_T**                   ppt_xml
)
{
    INT32                 i4_ret = TVSTAR_OK;
    CHAR*                 ps_buff = NULL;
    SIZE_T                z_buff_len;
    UINT32                ui4_read = 0;
    FILE*                 fp_out = NULL;

    /* check parameters for protecting system's validity */
    if ((NULL == ps_path) || (NULL == pt_data_info))
    {
        return TVSTAR_FAIL;
    }

    /* allocate memory */
    z_buff_len = (sizeof(CHAR) * TVSTATUS_XML_HDR_SZ) - sizeof(Append_DATA_TLV_T);

    ps_buff = (CHAR*)c_mem_alloc(z_buff_len);

    if (ps_buff == NULL)
    {
        DBG_ERROR(("\n out of memory \n"));
        return TVSTAR_OUT_OF_MEMORY;
    }
    c_memset((VOID*)ps_buff, 0, z_buff_len);

    do
    {
        /* open XML file */
        fp_out = fopen(ps_path,"r");

        if (NULL == fp_out)
        {
            DBG_ERROR(("<TVSTATUS>Open file %s error!!!, %d\n",
                                             ps_path,
                                            __LINE__));
            break;
        }

        /* read file */
        i4_ret = fread(ps_buff, sizeof(CHAR), z_buff_len, fp_out);
        if(i4_ret <= 0)
        {
            DBG_ERROR(("<TVSTATUS> read XML file to memory failed! %d\n",__LINE__));
            i4_ret = TVSTAR_FAIL;
            break;
        }
        else
        {
            ui4_read = i4_ret;
        }

        /* parse the buffer */
        i4_ret = c_xml_parse_buffer(ps_buff, ui4_read, ppt_xml);

        if(XML_SUCCESS != i4_ret)
        {
            DBG_ERROR(("<XML>XML parse failed! %d\n",__LINE__));
            i4_ret = TVSTAR_FAIL;
            break;
        }

        i4_ret = _tvstatus_fill_status_info(e_type, *(XML_T**)ppt_xml, pt_data_info);

        if (TVSTAR_OK != i4_ret)
        {
            break;
        }
    }
    while(0);

    /* close file */
    if (fp_out != NULL)
    {
        fclose(fp_out);
        fp_out = NULL;
    }

    if (ps_buff != NULL)
    {
        /* free memory */
        c_mem_free(ps_buff);
        ps_buff = NULL;
    }

    if (TVSTAR_OK != i4_ret)
    {
        return i4_ret;
    }

    return TVSTAR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_fill_sys_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_fill_status_info(
    E_DATA_TYPE               e_type,
    XML_T*                    pt_data_xml,
    VOID*                     pt_data_info
)
{
    INT32                 i4_ret = TVSTAR_OK;
    XML_Element*          pt_ele_sys;
    XML_Element*          pt_ele_temp;
    XML_Element*          pt_con_dev_tmp_ele = NULL;
    XML_Element*          pt_con_dev_ele = NULL;
    TVSTATUS_UNI_MODEL_T* pt_static_info = NULL;
    TVSTATUS_SHI_MODEL_T* pt_dynamic_info = NULL;

    if (NULL == pt_data_info
        || NULL == pt_data_xml
        || e_type >= E_DATA_TYPE_LAST)
    {
        DBG_ERROR(("Argument invalid!!!\n"));
        return TVSTAR_INV_ARG;
    }


    if (E_DATA_TYPE_UNI_DATA == e_type)
    {
        /* judge if xml exist */
        pt_ele_sys = c_xml_get_element(pt_data_xml, "STATIC_INFO");
        if (pt_ele_sys == NULL)
        {
            DBG_ERROR(("pt_ele_sys == NULL!!!\n"));
            return TVSTAR_FAIL;
        }

        pt_static_info = (TVSTATUS_UNI_MODEL_T*)pt_data_info;

        /* TV MODEL GROUP NUM */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_MODEL_GROUP_NUM");
        c_strncpy(pt_static_info->s_model_group, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_MODEL_GROUP_LEN-1);

        /* TV FM VERSION */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_FM_VERSION");
        c_strncpy(pt_static_info->s_ver, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_FIRMWARE_VER_LEN-1);

        /* TV MODEL NUM */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_MODEL_NUM");
        c_strncpy(pt_static_info->s_model_name, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_MODEL_NAME_LEN-1);

        /* TV ETHERNET MAC ADDR */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_ETHERNET_MAC_ADDR");
        c_strncpy(pt_static_info->s_mac_estr, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_ETHERNET_MAC_LEN-1);

        /* TV WIFI MAC ADDR */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_WIFI_MAC_ADDR");
        c_strncpy(pt_static_info->s_mac_wstr, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WIFI_MAC_LEN-1);

        /* TV_SERIAL_NUMBER */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_SERIAL_NUMBER");
        c_strncpy(pt_static_info->s_modsn, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_SERIAL_NUM_LEN-1);

        /* TV_CHIPSET_ID*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_CHIPSET_ID");
        c_strncpy(pt_static_info->s_chipset_id, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_CHIPSET_LEN-1);

        /* TV_ODM*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_ODM");
        c_strncpy(pt_static_info->s_odm, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_ODM_LEN-1);

        /* TV_SCREEN_SIZE*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_SCREEN_SIZE");
        c_strncpy(pt_static_info->s_screen_size, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_SCREEN_SIZE_LEN-1);

        /* TV_REMOTEFIRMWARE*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_REMOTEFIRMWARE");
        c_strncpy(pt_static_info->s_remote_ver, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_REMOTE_VER_LEN-1);

        /* TV_FIRSTNAME*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_FIRSTNAME");
        c_strncpy(pt_static_info->s_first_name, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WZD_REG_INFO_LEN-1);

        /* TV_LASTNAME*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_LASTNAME");
        c_strncpy(pt_static_info->s_last_name, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WZD_REG_INFO_LEN-1);

        /* TV_ZIP_CODE*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_ZIP_CODE");
        c_strncpy(pt_static_info->s_zip_code, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WZD_REG_INFO_LEN-1);

        /* TV_PHONE_NUMBER*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_PHONE_NUMBER");
        c_strncpy(pt_static_info->s_phone_num, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WZD_REG_INFO_LEN-1);

        /* TV_EMAIL*/
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_EMAIL");
        c_strncpy(pt_static_info->s_email, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WZD_REG_INFO_LEN-1);

    }
    else
    {
        /* judge if xml exist */
        pt_ele_sys = c_xml_get_element(pt_data_xml, "DYNAMIC_INFO");
        if (pt_ele_sys == NULL)
        {
            DBG_ERROR(("pt_ele_sys == NULL!!!\n"));
            return TVSTAR_FAIL;
        }

        pt_dynamic_info = (TVSTATUS_SHI_MODEL_T*)pt_data_info;

        /* TV INPUT SOURCE */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_CUR_INPUT_SOURCE");
        c_strncpy(pt_dynamic_info->s_input_source, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_INPUT_SOURCE_LEN-1);

        /*INPUT_SOURCE_ATTRIBUTION_INFO */
        pt_con_dev_ele = c_xml_get_element(pt_ele_sys, "INPUT_SOURCE_ATTRIBUTION_INFO");
        if ( NULL == pt_con_dev_ele )
        {
             DBG_ERROR(("pt_con_dev_ele == NULL!!!\n"));
             return TVSTAR_FAIL;
        }

        /* DEVICE_OSD_NAME */
        pt_con_dev_tmp_ele = c_xml_get_element(pt_con_dev_ele, "DEVICE_OSD_NAME");
        c_strncpy(pt_dynamic_info->s_device_osd_name, TVSTATUS_XML_VALUE(pt_con_dev_tmp_ele), TVSTAUS_DEVICE_TYPE_LEN-1);

        /* DEVICE_VENDOR_ID */
        pt_con_dev_tmp_ele = c_xml_get_element(pt_con_dev_ele, "DEVICE_VENDOR_ID");
        c_strncpy(pt_dynamic_info->s_device_vendor_id, TVSTATUS_XML_VALUE(pt_con_dev_tmp_ele), TVSTAUS_DEVICE_TYPE_LEN-1);

        /* THIRD_PARTY_APPLICATION */
        pt_con_dev_tmp_ele = c_xml_get_element(pt_con_dev_ele, "THIRD_PARTY_APPLICATION");
        c_strncpy(pt_dynamic_info->s_third_party_app, TVSTATUS_XML_VALUE(pt_con_dev_tmp_ele), TVSTAUS_DEVICE_TYPE_LEN-1);

        /* TV LANGUAGE */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_LANGUAGE");
        c_strncpy(pt_dynamic_info->crn_s639_lang, TVSTATUS_XML_VALUE(pt_ele_temp), ISO_639_LANG_LEN-1);

        /* TV COUNTRY */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_COUNTRY");
        //pt_dynamic_info->s_country = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));
        c_strncpy(pt_dynamic_info->s_country, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_COUNTRY_LEN-1);

        /* TV SCAN TYPE */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_SCAN_TYPE");
        pt_dynamic_info->ui1_scan_type = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV CHANNEL SCAN STATUS */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_CHANNEL_SCAN_STATUS");
        pt_dynamic_info->ui1_channel_scan_status = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV PARENTAL CONTROL */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_PARNETAL_CONTROL");
        pt_dynamic_info->ui1_parental_ctrl = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV REMOTEPAIR STATUS */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_REMOTEPAIR_STATUS");
        pt_dynamic_info->ui1_wfi_enab = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV PICTURE MODE */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_PICTURE_MODE");
        //pt_dynamic_info->ui1_pic_mod = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));
        c_strncpy(pt_dynamic_info->s_pic_mod, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_PIC_MODE_LEN-1);

        /* TV WIFI SIGNAL STRENGTH */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_WIFI_SIGNAL_STRENGTH");
        pt_dynamic_info->i4_sgnl = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV WIFI ACCESS POINT CHANNEL */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_WIFI_ACCESS_POINT_CHANNEL");
        pt_dynamic_info->i2_Channel = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV WIFI SIGNAL TO NOISE RATIO */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_WIFI_SIGNAL_TO_NOISE_RATIO");
        pt_dynamic_info->i2_Noise = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV NETWORK CONNECTION TYPE */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_NETWORK_CONNECTION_TYPE");
        pt_dynamic_info->b_wf_plug = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV WIRELESS BAND */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_WIRELESS_BAND");
        pt_dynamic_info->ui1_wirleband = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV WIRELESS SECURITY */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_WIRELESS_SECURITY");
        c_strncpy(pt_dynamic_info->s_wire_less_scurity, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTATUS_WIRE_LESS_SECURITY_LEN-1);

        /* TV POWER CYCLE COUNT */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_POWER_CYCLE_COUNT");
        pt_dynamic_info->ui4_boot_up_times = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV USAGE TIME */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_USAGE_TIME");
        pt_dynamic_info->ui4_running_time = atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV AUDIO STATE */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_AUDIO_STATE");
        pt_dynamic_info->ui2_audio_state= atoi(TVSTATUS_XML_VALUE(pt_ele_temp));

        /* TV NETWORK SPEED */
        pt_ele_temp = c_xml_get_element(pt_ele_sys, "TV_NETWORK_SPEED");
        //pt_dynamic_info->ui1_network_speed= atoi(TVSTATUS_XML_VALUE(pt_ele_temp));
        c_strncpy(pt_dynamic_info->s_network_speed, TVSTATUS_XML_VALUE(pt_ele_temp), TVSTAUS_NETWORK_SPEED_LEN-1);

    }
    return i4_ret;

}

static INT32 _tvstatus_update_info_to_xml(
    E_DATA_TYPE               e_type,
    XML_T*                    pt_data_xml
)
{
    INT32                   i4_ret = TVSTAR_OK;
    CHAR                    s_tmp[TVTSTAUS_TMP_STR_MAX_LEN+1] = {0};

    XML_Element*            pt_ele_sys;
    XML_Element*            pt_tmp_ele = NULL;
    XML_Element*            pt_con_dev_tmp_ele = NULL;
    XML_Element*            pt_con_dev_ele = NULL;
	XML_Element*            pt_con_dev_thd_ele = NULL;
    TVSTATUS_UNI_MODEL_T*   pt_static_info = NULL;
    TVSTATUS_SHI_MODEL_T*   pt_dynamic_info = NULL;

    if ( e_type >= E_DATA_TYPE_LAST || NULL == pt_data_xml)
    {
        DBG_ERROR(("Argument invalid!!!\n"));
        return TVSTAR_INV_ARG;
    }


    if (E_DATA_TYPE_UNI_DATA == e_type)
    {
        /* judge if xml exist */
        pt_ele_sys = c_xml_get_element(pt_data_xml, "STATIC_INFO");
        if (pt_ele_sys == NULL)
        {
            DBG_ERROR(("pt_ele_sys == NULL!!!\n"));
            return TVSTAR_FAIL;
        }

        pt_static_info = &t_g_uni_mode;

        /* modify update info of the corresponding item */
        /* TV MODEL GROUP NUM */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_MODEL_GROUP_NUM");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_MODEL_GROUP_NUM", pt_static_info->s_model_group);

        /* TV FM VERSION */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_FM_VERSION");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_FM_VERSION", pt_static_info->s_ver);

        /* TV MODEL NUM */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_MODEL_NUM");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_MODEL_NUM", pt_static_info->s_model_name);

        /* TV ETHERNET MAC ADDR */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_ETHERNET_MAC_ADDR");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_ETHERNET_MAC_ADDR", pt_static_info->s_mac_estr);

        /* TV WIFI MAC ADDR */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_WIFI_MAC_ADDR");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_WIFI_MAC_ADDR", pt_static_info->s_mac_wstr);

        /* TV_SERIAL_NUMBER*/
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_SERIAL_NUMBER");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_SERIAL_NUMBER", pt_static_info->s_modsn);

        /* TV_CHIPSET_ID */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_CHIPSET_ID");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_CHIPSET_ID", pt_static_info->s_chipset_id);

        /* TV_ODM */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_ODM");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_ODM", pt_static_info->s_odm);

        /* TV_SCREEN_SIZE */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_SCREEN_SIZE");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_SCREEN_SIZE", pt_static_info->s_screen_size);

        /* TV_REMOTEFIRMWARE */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_REMOTEFIRMWARE");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_REMOTEFIRMWARE", pt_static_info->s_remote_ver);

        /* TV_FIRSTNAME */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_FIRSTNAME");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_FIRSTNAME", pt_static_info->s_first_name);

        /* TV_LASTNAME */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_LASTNAME");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_LASTNAME", pt_static_info->s_last_name);

        /* TV_ZIP_CODE */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_ZIP_CODE");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_ZIP_CODE", pt_static_info->s_zip_code);

        /* TV_PHONE_NUMBER */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_PHONE_NUMBER");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_PHONE_NUMBER", pt_static_info->s_phone_num);

        /* TV_EMAIL */
        pt_tmp_ele= c_xml_get_element(pt_ele_sys, "TV_EMAIL");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_EMAIL", pt_static_info->s_email);

    }
    else
    {
        /* judge if xml exist */
        pt_ele_sys = c_xml_get_element(pt_data_xml, "DYNAMIC_INFO");
        if (pt_ele_sys == NULL)
        {
            DBG_ERROR(("pt_ele_sys == NULL!!!\n"));
            return TVSTAR_FAIL;
        }

        pt_dynamic_info = &t_g_shi_mode;

        /* modify update info of the corresponding item */
        /* TV INPUT SOURCE */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_CUR_INPUT_SOURCE");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_CUR_INPUT_SOURCE", pt_dynamic_info->s_input_source);

        	/*INPUT_SOURCE_ATTRIBUTION_INFO */
        pt_con_dev_ele = c_xml_get_element(pt_ele_sys, "INPUT_SOURCE_ATTRIBUTION_INFO");
        if ( NULL == pt_con_dev_ele )
        {
             DBG_ERROR(("pt_con_dev_ele == NULL!!!\n"));
             return TVSTAR_FAIL;
        }
            /*DEVICE_OSD_NAME */
        pt_con_dev_tmp_ele = c_xml_get_element(pt_con_dev_ele, "DEVICE_OSD_NAME");

        if ( NULL != pt_con_dev_tmp_ele )
        {
            c_xml_delete_element(pt_con_dev_tmp_ele);
            c_xml_free(pt_con_dev_tmp_ele);
        }

        /* add */
        c_xml_add_element(pt_con_dev_ele, "DEVICE_OSD_NAME", pt_dynamic_info->s_device_osd_name);

            /*DEVICE_VENDOR_ID */
        pt_con_dev_tmp_ele = c_xml_get_element(pt_con_dev_ele, "DEVICE_VENDOR_ID");

        if ( NULL != pt_con_dev_tmp_ele )
        {
            c_xml_delete_element(pt_con_dev_tmp_ele);
            c_xml_free(pt_con_dev_tmp_ele);
        }

        /* add */
        c_xml_add_element(pt_con_dev_ele, "DEVICE_VENDOR_ID", pt_dynamic_info->s_device_vendor_id);


        /*THIRD_PARTY_APPLICATION */
        pt_con_dev_tmp_ele = c_xml_get_element(pt_con_dev_ele, "THIRD_PARTY_APPLICATION");
		if(pt_con_dev_tmp_ele == NULL) //not exist
		{
            DBG_ERROR(("pt_con_dev_tmp_ele == NULL!!!\n"));
            return TVSTAR_FAIL;
		}
		else	//exist
		{
			//parse namespace, appid
			INT32 len1 = 0;
			INT32 len2 = 0;
			CHAR app_id[16];
			CHAR name_space[16];
			CHAR third_party_app[TVSTAUS_DEVICE_TYPE_LEN];
			CHAR* p = NULL;

			memset(app_id,0,sizeof(app_id));
			memset(name_space,0,sizeof(name_space));
			memset(third_party_app,0,sizeof(third_party_app));

			if(!c_memcmp(pt_dynamic_info->s_third_party_app,"UNKNOWN",c_strlen("UNKNOWN")))	//parse UNKNOWN
			{
				DBG_INFO(("s_third_party_app is UNKNOWN\n"));
				c_xml_delete_element(pt_con_dev_tmp_ele);
				c_xml_free(pt_con_dev_tmp_ele);
				c_xml_add_element(pt_con_dev_ele, "THIRD_PARTY_APPLICATION", pt_dynamic_info->s_third_party_app);
			}
			else
			{
				memcpy(third_party_app,pt_dynamic_info->s_third_party_app,sizeof(third_party_app));
				DBG_INFO(("s_third_party_app is  %s\n",third_party_app,pt_dynamic_info->s_third_party_app));

				p = strtok(third_party_app,",");
				if(p != NULL)
				{
					len1 = c_strlen(p) > sizeof(name_space) ? sizeof(name_space) : c_strlen(p);
					memcpy(name_space,p,len1);

					p = strtok(NULL,",");
					if(p != NULL)
					{
						len2 = c_strlen(p) > sizeof(app_id) ? sizeof(app_id): c_strlen(p);
						memcpy(app_id,p,len2);
					}
				}

				if(len1 != 0 && len2 != 0 )
				{
					//app_id
					pt_con_dev_thd_ele = c_xml_get_element(pt_con_dev_tmp_ele, "NAMESPACE");
					if(pt_con_dev_thd_ele != NULL)
					{
						c_xml_delete_element(pt_con_dev_thd_ele);
						c_xml_free(pt_con_dev_thd_ele);
					}
					c_xml_add_element(pt_con_dev_tmp_ele, "NAMESPACE", name_space);

					//name_space
					pt_con_dev_thd_ele = c_xml_get_element(pt_con_dev_tmp_ele, "APP_ID");
					if(pt_con_dev_thd_ele != NULL)
					{
						c_xml_delete_element(pt_con_dev_thd_ele);
						c_xml_free(pt_con_dev_thd_ele);
					}
					c_xml_add_element(pt_con_dev_tmp_ele, "APP_ID", app_id);

				}
				else
				{
					c_xml_delete_element(pt_con_dev_tmp_ele);
					c_xml_free(pt_con_dev_tmp_ele);
					c_xml_add_element(pt_con_dev_ele, "THIRD_PARTY_APPLICATION", pt_dynamic_info->s_third_party_app);

				}
			}
		}

        /* TV LANGUAGE */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_LANGUAGE");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        //c_memset(s_tmp, 0, sizeof(s_tmp));
        //c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->crn_s639_lang);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_LANGUAGE", pt_dynamic_info->crn_s639_lang);

        /* TV COUNTRY */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_COUNTRY");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        //c_memset(s_tmp, 0, sizeof(s_tmp));
        //c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->s_country);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_COUNTRY", pt_dynamic_info->s_country);


        /* TV SIGN TYPE */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_SCAN_TYPE");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_scan_type);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_SCAN_TYPE", s_tmp);

        /* TV CHANNEL SCAN STATUS */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_CHANNEL_SCAN_STATUS");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_channel_scan_status);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_CHANNEL_SCAN_STATUS", s_tmp);

        /* TV PARENTAL CONTROL */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_PARENTAL_CONTROL");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_parental_ctrl);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_PARENTAL_CONTROL", s_tmp);

        /* TV REMOTEPAIR STATUS */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_REMOTEPAIR_STATUS");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_wfi_enab);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_REMOTEPAIR_STATUS", s_tmp);

        /* TV PICTURE MODE */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_PICTURE_MODE");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        //c_memset(s_tmp, 0, sizeof(s_tmp));
        //c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_pic_mod);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_PICTURE_MODE", pt_dynamic_info->s_pic_mod);

        /* TV WIFI SIGNAL STRENGTH */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_WIFI_SIGNAL_STRENGTH");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->i4_sgnl);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_WIFI_SIGNAL_STRENGTH", s_tmp);

        /* TV WIFI ACCESS POINT CHANNEL */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_WIFI_ACCESS_POINT_CHANNEL");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->i2_Channel);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_WIFI_ACCESS_POINT_CHANNEL", s_tmp);

        /* TV WIFI SIGNAL TO NOISE RATIO */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_WIFI_SIGNAL_TO_NOISE_RATIO");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->i2_Noise);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_WIFI_SIGNAL_TO_NOISE_RATIO", s_tmp);

        /* TV NETWORK CONNECTION TYPE */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_NETWORK_CONNECTION_TYPE");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->b_wf_plug);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_NETWORK_CONNECTION_TYPE", s_tmp);

        /* TV WIRELESS BAND */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_WIRELESS_BAND");
        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_wirleband);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_WIRELESS_BAND", s_tmp);

        /* TV WIRELESS SECURITY */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_WIRELESS_SECURITY");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_WIRELESS_SECURITY", pt_dynamic_info->s_wire_less_scurity);

        /* TV POWER CYCLE COUNT */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_POWER_CYCLE_COUNT");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui4_boot_up_times);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_POWER_CYCLE_COUNT", s_tmp);

         /* TV USAGE TIME */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_USAGE_TIME");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui4_running_time);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_USAGE_TIME", s_tmp);

        /* TV AUDIO STATE */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_AUDIO_STATE");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }

        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui2_audio_state);

        /* add */
        c_xml_add_element(pt_ele_sys, "TV_AUDIO_STATE", s_tmp);

        /* TV NETWORK SPEED */
        pt_tmp_ele = c_xml_get_element(pt_ele_sys, "TV_NETWORK_SPEED");

        if ( NULL != pt_tmp_ele )
        {
            c_xml_delete_element(pt_tmp_ele);
            c_xml_free(pt_tmp_ele);
        }
#if 0
        c_memset(s_tmp, 0, sizeof(s_tmp));
        c_snprintf(s_tmp, TVTSTAUS_TMP_STR_MAX_LEN, "%d", pt_dynamic_info->ui1_network_speed);
#endif
        /* add */
        c_xml_add_element(pt_ele_sys, "TV_NETWORK_SPEED", pt_dynamic_info->s_network_speed);

    }
    return i4_ret;

}

static INT32 _tvstate_update_info(
    E_DATA_TYPE               e_type,
    CHAR*                     ps_path,
    XML_T**                   ppt_xml
)
{
    INT32                 i4_ret = TVSTAR_OK;
    CHAR*                 ps_buff = NULL;
    SIZE_T                z_buff_len;
    UINT32                ui4_read = 0;
    FILE*                 fp_out = NULL;

    /* check parameters for protecting system's validity */
    if (NULL == ps_path || NULL == ppt_xml)
    {
        return TVSTAR_FAIL;
    }

    /* allocate memory */
    z_buff_len = (sizeof(CHAR) * TVSTATUS_XML_HDR_SZ) - sizeof(Append_DATA_TLV_T);

    ps_buff = (CHAR*)c_mem_alloc(z_buff_len);
    if (NULL == ps_buff)
    {
        DBG_ERROR(("\n out of memory \n"));
        return TVSTAR_OUT_OF_MEMORY;
    }
    c_memset((VOID*)ps_buff, 0, z_buff_len);

    do
    {
        /* open XML file */
        fp_out = fopen(ps_path,"r");

        if (NULL == fp_out)
        {
            DBG_ERROR(("<TVSTATUS>Open file %s error!!!, %d\n",
                                             ps_path,
                                            __LINE__));
            break;

        }

        /* read file */
        i4_ret = fread(ps_buff, sizeof(CHAR), z_buff_len, fp_out);
        if(i4_ret <= 0)
        {
            DBG_ERROR(("<TVSTATUS> read XML file to memory failed! %d\n",__LINE__));
            i4_ret = TVSTAR_FAIL;
            break;
        }
        else
        {
            ui4_read = i4_ret;
        }

        /* parse the buffer */
        i4_ret = c_xml_parse_buffer(ps_buff, ui4_read, ppt_xml);

        if(XML_SUCCESS != i4_ret)
        {
            DBG_ERROR(("<XML>XML parse failed! %d\n",__LINE__));

            i4_ret = TVSTAR_FAIL;
            break;
        }

        i4_ret = _tvstatus_update_info_to_xml(e_type, *(XML_T**)ppt_xml);

        if (TVSTAR_OK != i4_ret)
        {
            break;
        }

        DBG_INFO(("<PARSE> can update info! %d\n",__LINE__));

    }while(0);

    /* close file */
    if (fp_out != NULL)
    {
        fclose(fp_out);
        fp_out = NULL;
    }

    if (ps_buff != NULL)
    {
        /* free memory */
        c_mem_free(ps_buff);
        ps_buff = NULL;
    }

    return i4_ret;

}


/*----------------------------------------------------------------------------
 * Name: _tvstate_print_info
 *
 * Description: This func is used to parse xml to fw info.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _tvstate_print_info(
    TVSTATUS_MODEL_T*      pt_this,
    E_DATA_TYPE            e_type
)
{
    CHAR*                ps_buff = NULL;
    INT32                i4_ret = TVSTAR_OK;
    FILE*                fp_out = NULL;
    CHAR                 s_cmd[TVSTAUS_CMD_LEN] = {'\0'};
    CHAR                 s_static_path[TVSTAUS_STATIC_PATH_LEN] = {'\0'};
    CHAR                 s_dynamic_path[TVSTAUS_DYNAMIC_PATH_LEN] = {'\0'};

    if (e_type >= E_DATA_TYPE_LAST)
    {
        DBG_ERROR(("<TVSTATUS>%d:_tvstate_print_info error, Not parse xml file!!!\n", __LINE__));

        return TVSTAR_FAIL;
    }

    c_sprintf(s_static_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_STATIC_XML_NAME);
    c_sprintf(s_dynamic_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_DYNAMIC_XML_NAME);

    if ( E_DATA_TYPE_UNI_DATA == e_type)
    {
        _tvstate_update_info(e_type,
                         TVSTATE_XML_PATH "/" TVSTATE_STATIC_XML_NAME,
                         &(pt_this->pt_data_xml));

        if ( TVSTAR_OK != i4_ret)
        {
            return i4_ret;
        }

        ps_buff = c_xml_print_document(pt_this->pt_data_xml);
        if (pt_this->pt_data_xml != NULL)
        {
            c_xml_free(pt_this->pt_data_xml);
        }
        if (NULL == ps_buff)
        {
            return TVSTAR_FAIL;
        }

        /* delete file */
        c_sprintf(s_cmd,
                  "rm -f %s",
                  s_static_path);

        DBG_INFO(("<TVSTATUS> %s %d\n\n",s_cmd,__LINE__));

        //system(s_cmd);
        //system("sync");
        remove(s_static_path);

        fp_out = fopen(TVSTATE_XML_PATH "/" TVSTATE_STATIC_XML_NAME,
                       "w");

        if (NULL == fp_out)
        {
            DBG_ERROR(("<TVSTATUS>Open file %s error!!!, %d\n",
                                            TVSTATE_XML_PATH "/" TVSTATE_STATIC_XML_NAME,
                                            __LINE__));
            return TVSTAR_FAIL;
        }

        /* write the buff to file */
        fwrite((const CHAR*)ps_buff, sizeof(CHAR), c_strlen(ps_buff), fp_out);

        /* flesh kernel buffer */
        fflush(fp_out);

         /* close file */
        if (fp_out != NULL)
        {
            fclose(fp_out);
            fp_out = NULL;
        }
        c_mem_free(ps_buff);

        return TVSTAR_OK;

    }
    else
    {
        _tvstate_update_info(E_DATA_TYPE_SHI_DATA,
                         TVSTATE_XML_PATH "/" TVSTATE_DYNAMIC_XML_NAME,
                         &(pt_this->pt_data_xml));

         if ( TVSTAR_OK != i4_ret)
        {
            return i4_ret;
        }

        ps_buff = c_xml_print_document(pt_this->pt_data_xml);
        if (pt_this->pt_data_xml != NULL)
        {
            c_xml_free(pt_this->pt_data_xml);
        }
        if (NULL == ps_buff)
        {
            return TVSTAR_FAIL;
        }

        /* delete file */
        c_sprintf(s_cmd,
                  "rm -f %s",
                  s_dynamic_path);

        DBG_INFO(("<TVSTATUS> %s %d\n\n",s_cmd,__LINE__));

        //system(s_cmd);
        //system("sync");
        remove(s_dynamic_path);

        fp_out = fopen(TVSTATE_XML_PATH "/" TVSTATE_DYNAMIC_XML_NAME,
                       "w");

        if (NULL == fp_out)
        {
            DBG_ERROR(("<TVSTATUS>Open file %s error!!!, %d\n",
                                            TVSTATE_XML_PATH "/" TVSTATE_DYNAMIC_XML_NAME,
                                            __LINE__));
            return TVSTAR_FAIL;
        }

        /* write the buff to file */
        fwrite((const CHAR*)ps_buff, sizeof(CHAR), c_strlen(ps_buff), fp_out);

        /* flesh kernel buffer */
        fflush(fp_out);

        /* close file */
        if (fp_out != NULL)
        {
            fclose(fp_out);
            fp_out = NULL;
        }
        c_mem_free(ps_buff);

        return TVSTAR_OK;
    }

}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_wgl_manager_cb_fct
 *
 * Description: The callback funcation is called by Widget Library (directly
 *              using thread conext of IO Manager).
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_wgl_manager_cb_fct(
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2)
{
    TVSTATUS_MSG_WGL_NOTIFY_T  t_nfy;

    t_nfy.ui4_msg   = ui4_msg;
    t_nfy.pv_param1 = pv_param1;
    t_nfy.pv_param2 = pv_param2;

    a_tvstatus_async_invoke (_tvstatus_wgl_event_dispatcher, &t_nfy, sizeof(TVSTATUS_MSG_WGL_NOTIFY_T));

    return 0;
}

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _tvstatus_wgl_event_dispatcher
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _tvstatus_cli_action(
                    VOID*                       pv_data,
                    SIZE_T                      z_data_len)
{
    TVSTATUS_CLI_DATA_T**   ppt_cli_data = (TVSTATUS_CLI_DATA_T**)pv_data;
    TVSTATUS_CLI_DATA_T*    pt_cli_data  = *ppt_cli_data;

    t_g_model.b_cli_flag = TRUE;

    pt_cli_data->i4_ret =
        pt_cli_data->pf_cli_func(
            pt_cli_data->i4_argc,
            pt_cli_data->pps_argv);

    t_g_model.b_cli_flag = FALSE;

    c_sema_unlock(t_g_model.h_sema_cli);
}
#endif

static INT32 _tvstatus_model_group(CHAR* s_mg)
{
    CHAR      *p_mg = NULL;

    if (NULL == s_mg)
    {
       return TVSTAR_FAIL;
    }

    p_mg = getenv("SYS_MG");

    if (p_mg!=NULL)
    {
        c_strncpy (s_mg,p_mg, TVSTATUS_MODEL_GROUP_LEN-1);
    }
    else
    {
        c_strcpy(s_mg, "");
    }
    return  TVSTAR_OK;

}

static INT32 _tvstatus_chipset_id(CHAR* s_chipst_id)
{
    CHAR      *p_chipset_id = NULL;

    if (NULL == s_chipst_id)
    {
       return TVSTAR_FAIL;
    }

    p_chipset_id = getenv("SYS_MODEL_NAME");
    if (p_chipset_id!=NULL)
    {
        c_strncpy (s_chipst_id,p_chipset_id, 6);
    }
    else
    {
        c_strcpy(s_chipst_id, "");
    }

    return  TVSTAR_OK;

}


static INT32 _tvstatus_odm(CHAR* s_odm)
{
    CHAR      *p_odm= NULL;

    if (NULL == s_odm)
    {
       return TVSTAR_FAIL;
    }

    p_odm = getenv("ODM");

    if (p_odm!=NULL)
    {
        c_strncpy (s_odm,p_odm, TVSTATUS_ODM_LEN-1);
    }
    else
    {
        c_strcpy(s_odm, "");
    }
    return  TVSTAR_OK;

}

static INT32 _tvstatus_screen_size(CHAR* s_screen_size)
{
    CHAR      s_tmp_str[24] = {0};
    INT32    i4_ret = 0;

    if (NULL == s_screen_size)
    {
       return TVSTAR_FAIL;
    }

    i4_ret = a_cfg_custom_plf_opt_get_model_name(s_tmp_str, sizeof(s_tmp_str));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    s_screen_size[0] = s_tmp_str[1];
    s_screen_size[1] = s_tmp_str[2];
    s_screen_size[2] = 0;

    return  i4_ret;

}

static INT32 _tvstatus_reg_info(VOID)
{
    INT32    i4_ret = 0;
	UINT8	 ui1_loop = 0;
    CHAR *   pps_reg_info[5];
    TVSTATUS_UNI_MODEL_T *pt_static_info = &t_g_uni_mode;

    for(ui1_loop = 0; ui1_loop < 5; ui1_loop++)
    {
        pps_reg_info[ui1_loop] = (CHAR *)c_mem_alloc((TVSTAUS_REG_INFO_MAX_LEN + 1)*sizeof(CHAR));
        if(NULL == pps_reg_info[ui1_loop])
        {
            return TVSTAR_FAIL;
        }
        c_memset(pps_reg_info[ui1_loop], 0, (TVSTAUS_REG_INFO_MAX_LEN + 1)*sizeof(CHAR));
    }

    i4_ret = a_cfg_custom_get_reg_info(pps_reg_info,5);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    do
    {
        ui1_loop = 0;
        c_strncpy (pt_static_info->s_email,pps_reg_info[ui1_loop++],TVSTAUS_REG_INFO_MAX_LEN);
        c_strncpy (pt_static_info->s_first_name,pps_reg_info[ui1_loop++], TVSTAUS_REG_INFO_MAX_LEN);
        c_strncpy (pt_static_info->s_last_name,pps_reg_info[ui1_loop++], TVSTAUS_REG_INFO_MAX_LEN);
        c_strncpy (pt_static_info->s_phone_num,pps_reg_info[ui1_loop++], TVSTAUS_REG_INFO_MAX_LEN);
        c_strncpy (pt_static_info->s_zip_code,pps_reg_info[ui1_loop], TVSTAUS_REG_INFO_MAX_LEN);
    }
    while(0);


    for(ui1_loop = 0; ui1_loop < 5; ui1_loop++)
    {
        if(NULL != pps_reg_info[ui1_loop])
        {

            c_mem_free(pps_reg_info[ui1_loop]);
        }

    }

    return  i4_ret;

}



static INT32 _tvstatus_static_info_ass(VOID)
{
    INT32    i4_ret = 0;
    TVSTATUS_UNI_MODEL_T *pt_static_info = &t_g_uni_mode;

    c_memset (& t_g_uni_mode, 0, sizeof (TVSTATUS_UNI_MODEL_T));

    i4_ret = _tvstatus_model_group(pt_static_info->s_model_group);

    TVSTATUS_LOG_ON_FAIL(i4_ret);

    c_strcpy(pt_static_info->s_ver, sys_cust_get_usb_upg_version());

    i4_ret = a_cfg_custom_plf_opt_get_model_name( pt_static_info->s_model_name, sizeof(pt_static_info->s_model_name));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    UINT32   ui4_buff_len = sizeof(pt_static_info->s_modsn);
    i4_ret = a_uli_get_serial_number((UINT8 *)&(pt_static_info->s_modsn[0]), &ui4_buff_len);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    a_nw_get_mac_addr_string(NI_ETHERNET_0,pt_static_info->s_mac_estr);
    a_nw_get_mac_addr_string(NI_WIRELESS_0,pt_static_info->s_mac_wstr);
    i4_ret = _tvstatus_odm(pt_static_info->s_odm);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_chipset_id(pt_static_info->s_chipset_id);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_screen_size(pt_static_info->s_screen_size);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    #ifdef APP_WIFI_REMOTE
    i4_ret = c_get_remote_info(WFRCCMsg_DeviceFWVersion, pt_static_info->s_remote_ver);
    TVSTATUS_LOG_ON_FAIL(i4_ret);
    #endif

    i4_ret = _tvstatus_reg_info();
    TVSTATUS_LOG_ON_FAIL(i4_ret);

     /* print static xml info */
    _tvstate_print_info(&t_g_model, E_DATA_TYPE_UNI_DATA);

    return  TVSTAR_OK;


}

static INT32 _tvstat_update_immediately(VOID)
{
    INT32 i4_ret = TVSTAR_OK;

    i4_ret = _tvstatus_dynamic_info_ass();
    if(i4_ret != TVSTAR_OK) {
        DBG_ERROR(("_tvstat_start_immediately failed, i4_ret=%d\r\n", i4_ret));
    }

    return TVSTAR_OK;
}

static VOID _do_input_change(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    BOOL b_update_immediately = FALSE;

    if (NULL == pv_data || 0 == z_data_size)
    {
        b_update_immediately = FALSE;
    }
    else
    {
        b_update_immediately = *(BOOL*)pv_data;
    }

    DBG_INFO(("<TVSTATUS> L%d: receive notifications, update data immediately is (%d).\n", __LINE__,b_update_immediately));
    if (b_update_immediately)
    {
        _tvstat_update_immediately();
    }
    else
    {
        //Do nothing to wait for routine task update.
    }
}

static  VOID _tvstat_chk_input_nfy_fct(
    UINT16     ui2_nfy_id,
    VOID*      pv_tag,
    UINT16     ui2_id)
{
    BOOL    b_update = FALSE;

    b_update = _tvstatus_get_tmp_folder_xml_exist();

    if (CFG_MAKE_ID(APP_CFG_GRPID_NAV, APP_CFG_RECID_INPUT_MAIN) == ui2_id)
    {
        a_tvstatus_async_invoke(_do_input_change, &b_update, sizeof(BOOL));
    }
}

static INT32 _tvstatus_input_source(CHAR*  s_tmp_str)
{
    INT32       i4_ret = 0;
    ISL_REC_T   t_isl_rec;
    SVL_REC_T   t_svl_rec;
    BOOL        b_found = FALSE;
    UTF16_T     *w2s_tmp = NULL;
    CHAR        s_resume_ap[APP_NAME_MAX_LEN+1] = {0};


    c_memset (&t_isl_rec, 0, sizeof (ISL_REC_T));
    c_memset (&t_svl_rec, 0, sizeof (SVL_REC_T));

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

    a_am_get_active_app(s_resume_ap);
    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    TVSTATUS_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    c_memset(s_tmp_str, 0, TVSTATUS_INPUT_SOURCE_LEN);

    if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status()
        || (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type))
    {
        c_strncpy (s_tmp_str,"CAST", 4);

    }
    else if ((c_strcmp(s_resume_ap, MMP_NAME) == 0)
#ifdef APP_MENU_MMP_COEXIST
            ||(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
#endif
            )
    {
        c_strncpy (s_tmp_str,"MMP", 4);
    }
    else if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
    {
        if (b_found && BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
        {
            /*DTV*/
            c_strncpy (s_tmp_str,"DTV", 4);

        }
        else
        {
            /*ATV*/
            c_strncpy (s_tmp_str,"ATV", 4);
        }
    }
    else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type)
    {
        w2s_tmp = a_isl_get_display_name(&t_isl_rec);

        switch(t_isl_rec.t_avc_info.e_video_type)
        {
            case DEV_AVC_COMP_VIDEO:
            case DEV_AVC_S_VIDEO:
            /*case DEV_AVC_COMBI:*/
                /*AV*/
                c_strncpy (s_tmp_str,"AV", 3);
                break;
            case DEV_AVC_COMBI:
            case DEV_AVC_Y_PB_PR:
                /*Composite*/
                c_strncpy (s_tmp_str,"Component", 10);
                break;
            case DEV_AVC_DVI:
                /*DVI*/
                c_strncpy (s_tmp_str,"DVI", 4);
                break;
            case DEV_AVC_HDMI:
                /*HDMI*/
                c_strncpy (s_tmp_str,"HDMI", 5);

                if (w2s_tmp != NULL)
                {
                    c_memset(s_tmp_str, 0, sizeof(TVSTATUS_INPUT_SOURCE_LEN));
                    c_uc_w2s_to_ps(w2s_tmp, s_tmp_str, TVSTATUS_INPUT_SOURCE_LEN-1);
                }
                break;
            case DEV_AVC_VGA:
                /*RGB*/
                c_strncpy (s_tmp_str,"RGB", 4);
                break;
            default:
                c_strncpy (s_tmp_str,"AV", 3);
                break;
        }
    }

    return  TVSTAR_OK;

}

static UINT8 _tvstatus_scan_type(UINT8 * pi1_ret)
{
    UINT8   ui1_bs_src = 0;
    INT32   i4_ret = 0;

    if (NULL == pi1_ret)
    {
       return TVSTAR_FAIL;
    }

    i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, & ui1_bs_src);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    switch (ui1_bs_src)
    {
        case APP_CFG_BS_SRC_CABLE:
            *pi1_ret = APP_CFG_BS_SRC_CABLE;
            break;
        case APP_CFG_BS_SRC_SAT:
            *pi1_ret = APP_CFG_BS_SRC_SAT;
            break;
        default:
            *pi1_ret = APP_CFG_BS_SRC_AIR;
            break;
    }

    return  TVSTAR_OK;
}

static UINT8 _tvstatus_channel_scan_status(UINT8 * pi1_ret)
{
    UINT8      ui1_ch_scan_status = ACFG_CUST_CH_NOT_SCANED;
    INT32      i4_ret = 0;

    if (NULL == pi1_ret)
    {
       return TVSTAR_FAIL;
    }

    i4_ret = a_cfg_cust_get_crnt_ch_scan_status(&ui1_ch_scan_status);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    switch (ui1_ch_scan_status)
    {
        case ACFG_CUST_COMPLETED_SCAN:
        case ACFG_CUST_PARTIAL_SCAN:
        case ACFG_CUST_CH_SCANED_NO_CH:
        *pi1_ret = 1;
        break;
        case ACFG_CUST_CH_NOT_SCANED:
        *pi1_ret = 0;
        break;
        default:
        *pi1_ret = 0;
        break;
    }

    return  i4_ret;
}

static UINT8 _tvstatus_channel_ctrl_enable_idx(VOID)
{
    UINT8   ui1_rating_enabled = 0;
    UINT8   ui1_val = RATING_ENABLED_STATUS_ON;
    SIZE_T  z_size = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                          &ui1_val, &z_size);

    if (RATING_ENABLED_STATUS_OFF == ui1_val)
    {
        ui1_rating_enabled = 0;
    }
    else
    {
        a_cfg_get_rating_enabled(&ui1_rating_enabled);
    }

    return ui1_rating_enabled ? 1 : 0;

}

static BOOL _tvstatus_wifi_remote_pair_status(VOID)
{
    UINT8   ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;
    INT32    i4_ret = 0;

    i4_ret = a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    if(WIFI_REMOTE_PAIR_STATUS_PAIRED == ui1_status)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static UINT8 _tvstatus_wire_less_security(CHAR* s_tmp_str)
{
    INT32    i4_ret = 0;
    NET_802_11_BSS_INFO_T       t_CurrBss;

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    switch(t_CurrBss.e_AuthMode)
    {
        case IEEE_802_11_AUTH_MODE_OPEN:
        case IEEE_802_11_AUTH_MODE_SHARED:
        case IEEE_802_11_AUTH_MODE_WEPAUTO:
        {
            c_strncpy(s_tmp_str, "WEP", 4);
        }
            break;

        case IEEE_802_11_AUTH_MODE_WPA:
        {
            c_strncpy(s_tmp_str, "WPA", 4);
        }
            break;
        case IEEE_802_11_AUTH_MODE_WPA_PSK:
        {

            c_strncpy(s_tmp_str, "WPAPSK", 7);
        }
            break;
        case IEEE_802_11_AUTH_MODE_WPA2:
        {

            c_strncpy(s_tmp_str, "WPA2", 5);
        }
            break;
        case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
        {
            c_strncpy(s_tmp_str, "WPA2PSK", 8);
        }
            break;
        case IEEE_802_11_AUTH_MODE_WPA2_PSK_SHA256_AES:
        {
            c_strncpy(s_tmp_str, "WPA2PSK-SHA256AES", 18);
        }
            break;
        case IEEE_802_11_AUTH_MODE_WPA_SAE:
        case IEEE_802_11_AUTH_MODE_WPA2_SAE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE:
        {
            c_strncpy(s_tmp_str, "SAE", 4);
        }
            break;
        case IEEE_802_11_AUTH_MODE_WPA_OWE:
        case IEEE_802_11_AUTH_MODE_WPA2_OWE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
        {
            c_strncpy(s_tmp_str, "OWE", 4);
        }
            break;
        default:
            c_strncpy(s_tmp_str, "none", 5);
            break;
    }

    return  i4_ret;
}

static UINT8 _tvstatus_wire_less_band(UINT8 *pi1_ret)
{
    INT32    i4_ret = 0;
    NET_802_11_BSS_INFO_T       t_CurrBss;
    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    if (NULL == pi1_ret)
    {
       return TVSTAR_FAIL;
    }

    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.i2_Channel >= 1 && t_CurrBss.i2_Channel <= 14)
    {
        *pi1_ret = 1;
    }
    else if(t_CurrBss.i2_Channel >14 )
    {
        *pi1_ret = 2;
    }
    else
    {
        *pi1_ret = 0;
    }
    return  i4_ret;
}

static UINT8 _tvstatus_current_picmode(CHAR* s_tmp_str)
{
    INT32    i4_ret = 0;
	INT16	 i2_idx = 0;
	CHAR	 s_pic_mode[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

#ifndef APP_LARGE_EEPROM_SUPPORT

    i4_ret = acfg_cust_filesys_get(CFG_MAKE_ID(APP_CFG_GRPID_FILESYS_BASE, APP_CFG_RECID_FILESYS_PIC_MODE),
                                   &i2_idx);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    if(i2_idx < TVSTAUS_PIC_MODE_NUM)
    {
        if (TVSTAUS_PIC_MODE_STANDARD == i2_idx)
        {
            c_strncpy(s_tmp_str, "Standard", 9);
        }
        else if (TVSTAUS_PIC_MODE_CALIBRATED == i2_idx)
        {
            c_strncpy(s_tmp_str, "Calibrated", 11);
        }
        else if (TVSTAUS_PIC_MODE_CALIBRATED_DARK == i2_idx)
        {
            c_strncpy(s_tmp_str, "Calibrated Dark", 16);
        }
        else if (TVSTAUS_PIC_MODE_VIVID == i2_idx)
        {
            c_strncpy(s_tmp_str, "Vivid", 6);
        }
        else if (TVSTAUS_PIC_MODE_GAME == i2_idx)
        {
            c_strncpy(s_tmp_str, "Game", 5);
        }
        else if (TVSTAUS_PIC_MODE_COMPUTER == i2_idx)
        {
            c_strncpy(s_tmp_str, "Computer", 9);
        }
    }
    else
    {
		c_memset(s_pic_mode,0,MENU_PRESET_PIC_MODE_NAME_LEN+1);
		i4_ret = a_cfg_filesys_get_pic_mode_name(i2_idx, s_pic_mode);
        TVSTATUS_LOG_ON_FAIL(i4_ret);
        c_strncpy(s_tmp_str,s_pic_mode,MENU_PRESET_PIC_MODE_NAME_LEN);
    }

#else

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                          &i2_idx);
    TVSTATUS_LOG_ON_FAIL(i4_ret);


    if(i2_idx < TVSTAUS_PIC_MODE_NUM)
    {
        if (TVSTAUS_PIC_MODE_STANDARD == i2_idx)
        {
            c_strncpy(s_tmp_str, "Standard", 9);
        }
        else if (TVSTAUS_PIC_MODE_CALIBRATED == i2_idx)
        {
            c_strncpy(s_tmp_str, "Calibrated", 11);
        }
        else if (TVSTAUS_PIC_MODE_CALIBRATED_DARK == i2_idx)
        {
            c_strncpy(s_tmp_str, "Calibrated Dark", 16);
        }
        else if (TVSTAUS_PIC_MODE_VIVID == i2_idx)
        {
            c_strncpy(s_tmp_str, "Vivid", 6);
        }
        else if (TVSTAUS_PIC_MODE_GAME == i2_idx)
        {
            c_strncpy(s_tmp_str, "Game", 5);
        }
        else if (TVSTAUS_PIC_MODE_COMPUTER == i2_idx)
        {
            c_strncpy(s_tmp_str, "Computer", 9);
        }
    }
    else
    {
        c_memset(s_pic_mode,0,MENU_PRESET_PIC_MODE_NAME_LEN+1);
		i4_ret = a_cfg_cust_get_cust_pic_mode_name(i2_idx, s_pic_mode,MENU_PRESET_PIC_MODE_NAME_LEN);
		TVSTATUS_LOG_ON_FAIL(i4_ret);
        c_strncpy(s_tmp_str,s_pic_mode,MENU_PRESET_PIC_MODE_NAME_LEN);
    }
#endif

    return  i4_ret;

}

static UINT8 _tvstatus_current_country(CHAR* s_tmp_str)
{

    INT32    i4_ret = 0;
    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

    i4_ret = a_cfg_custom_get_country_code(&t_country_code);

    if (ACFG_COUNTRY_CODE_US == t_country_code)
    {
        c_strncpy(s_tmp_str, "US", 3);
    }
    else if (ACFG_COUNTRY_CODE_MEX == t_country_code)
    {
        c_strncpy(s_tmp_str, "Mexico", 7);
    }
    else if (ACFG_COUNTRY_CODE_CA == t_country_code)
    {
        c_strncpy(s_tmp_str, "Canada", 7);
    }
    else if (ACFG_COUNTRY_CODE_UNKNOWN == t_country_code)
    {
        c_strncpy(s_tmp_str, "UNKNOWN", 8);
    }
    else
    {
        c_strncpy(s_tmp_str, "US", 3);
    }

    return  i4_ret;
}

static UINT16 _tvstatus_audio_state(VOID)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask;
    INT16   i2_val = 0;

    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    return (UINT16)((ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) ? 1 : 0);
}

static INT32 _tvstatus_network_speed(CHAR*s_tmp_str)
{
    DOUBLE       u4_nw_speed = 0;
    INT32        i4_speed = 0;
    FLOAT        f_result = 0;

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

    /*kbit/s, middleware return data is bytes/s, so need data*8/1024 */
    u4_nw_speed = nw_custom_get_speed();
    i4_speed = (INT32)(u4_nw_speed*8/1024);

    if(i4_speed == 0)
    {
        c_strncpy(s_tmp_str, "N/A",TVSTAUS_NETWORK_SPEED_LEN-1);
    }
    else
    {
        /*Mbit/s*/
        f_result =((FLOAT)i4_speed)/((FLOAT)1024);
        c_snprintf(s_tmp_str, TVSTAUS_NETWORK_SPEED_LEN-1, "%.2f", f_result) ;
    }
    return  TVSTAR_OK;
}

static INT32 _tvstatus_get_device_osd_name(CHAR*s_tmp_str)
{

    INT32            i4_ret = 0;
    CEC_DEV_LST_T    t_lst;
    UINT8            ui1_loop = 0;
    UTF16_T*         pw2s_dev_osd_name = NULL;
    char             s_hdmi_src[10]={0};
    UINT8            ui1_cec_func = 0;

    c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }
    a_cfg_get_cec_func (&ui1_cec_func);
    if((ui1_cec_func == APP_CFG_CEC_ON)||(ui1_cec_func == APP_CFG_CEC_ARC_ONLY))
    {
        i4_ret = a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);
        TVSTATUS_LOG_ON_FAIL(i4_ret);

        for (ui1_loop = 0;ui1_loop < t_lst.ui1_dev_num;ui1_loop++)
        {

            if (c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name)!=0)
            {
                  c_uc_w2s_to_ps(t_lst.at_dev_info[ui1_loop].pw2s_hdmi_port,s_hdmi_src,9);

                  DBG_INFO(("<TVSTATUS> HDMI SRC = %s,CUR SRC =%s\n",s_hdmi_src,t_g_shi_mode.s_input_source));

                 if( c_strcmp(s_hdmi_src,t_g_shi_mode.s_input_source) == 0)
                 {
                     pw2s_dev_osd_name = t_lst.at_dev_info[ui1_loop].aw2_osd_name;

                     c_uc_w2s_to_ps(pw2s_dev_osd_name, s_tmp_str, TVSTAUS_DEVICE_TYPE_LEN-1);

                     DBG_INFO(("<TVSTATUS> OSD NAME =%s\n",s_tmp_str));

                     return  TVSTAR_OK;
                 }
            }
        }
    }

    c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
    return  TVSTAR_OK;
}

static INT32 _tvstatus_get_device_vendor_id(CHAR*s_tmp_str)
{
    INT32               i4_ret = 0;
    CECM_DEV_T          t_dev_info;
    CECM_CTRL_T         t_cecm_ctrl;
    UINT8               ui1_la = 0;
    UINT8               ui1_cec_func = 0;

    c_memset (&t_dev_info, 0, sizeof (CECM_DEV_T));
    c_memset (&t_cecm_ctrl, 0, sizeof (CECM_CTRL_T));

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

    a_cfg_get_cec_func (&ui1_cec_func);

    if((ui1_cec_func == APP_CFG_CEC_ON)||(ui1_cec_func == APP_CFG_CEC_ARC_ONLY))
    {
        for (ui1_la = CECM_LOG_ADDR_REC_DEV_1;ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST;ui1_la++)
        {
            t_cecm_ctrl.b_sync = FALSE;
            i4_ret = c_cecm_get_dev_info_by_la (
                                        nav_cec_get_mw_handle (),
                                        (CECM_LOG_ADDR_T)ui1_la,
                                        &t_cecm_ctrl,
                                        &t_dev_info);

            if (i4_ret != CECMR_OK)
            {
                continue;
            }
            if ((t_dev_info.e_dev_state != CECM_DEV_STATE_UPDATED) || (t_dev_info.t_report_phy_addr.ui2_pa == CECM_INV_PA))
            {
                continue;
            }
            if (c_uc_w2s_strlen (t_dev_info.aw2_osd_name) != 0)
            {
                DBG_INFO(("<TVSTATUS> GOT VEND ID   %x%x%x\n",
                    t_dev_info.t_dev_vndr_id[0],t_dev_info.t_dev_vndr_id[1],
                    t_dev_info.t_dev_vndr_id[2]));

                c_snprintf(s_tmp_str, TVSTAUS_DEVICE_TYPE_LEN-1, "%x%x%x", t_dev_info.t_dev_vndr_id[0],t_dev_info.t_dev_vndr_id[1],t_dev_info.t_dev_vndr_id[2]);
                return  TVSTAR_OK;
            }

        }

    }
    c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
    return  TVSTAR_OK;

}

static INT32 _tvstatus_get_third_party_app(CHAR*s_tmp_str)
{
    FILE*    fp_out = NULL;
    CHAR     s_buff[20] = {0};
    INT32    i4_ret = 0;
    UINT32   ui4_read_cnt;

    if (NULL == s_tmp_str)
    {
       return TVSTAR_FAIL;
    }

    if( c_strcmp(t_g_shi_mode.s_input_source,"VIA") == 0) //for via+ platform
    {
        /* open file */
        fp_out = fopen("/tmp/am_status","r");

        if (NULL == fp_out)
        {
            DBG_ERROR(("<TVSTATUS>Open file error!!!, %d\n",__LINE__));
            c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
            return  TVSTAR_OK;
        }

        /* read file */
        ui4_read_cnt = fread(s_buff, sizeof(CHAR), sizeof(CHAR)*20, fp_out);

        if( c_strncmp(s_buff,"youtube",ui4_read_cnt-1) == 0)
        {
            c_strncpy(s_tmp_str, "YOUTUBE",TVSTAUS_DEVICE_TYPE_LEN-1);
        }
        else if( c_strncmp(s_buff,"netflix_movie",ui4_read_cnt-1) == 0)
        {
            c_strncpy(s_tmp_str, "NETFLIX",TVSTAUS_DEVICE_TYPE_LEN-1);
        }
        else if( c_strncmp(s_buff,"vudu",ui4_read_cnt-1) == 0)
        {
            c_strncpy(s_tmp_str, "VUDU",TVSTAUS_DEVICE_TYPE_LEN-1);
        }
        else if( c_strncmp(s_buff,"yahoo",ui4_read_cnt-1) == 0)
        {
            c_strncpy(s_tmp_str, "YAHOO",TVSTAUS_DEVICE_TYPE_LEN-1);
        }
        else if( c_strncmp(s_buff,"html_apps",ui4_read_cnt-1) == 0)
        {
            i4_ret = system("ps aux| grep browser > /tmp/html5_app");

            if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
            {
                i4_ret = system("grep \"amazon\" /tmp/html5_app");
                if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
                {
                    c_strncpy(s_tmp_str, "AMAZON", TVSTAUS_DEVICE_TYPE_LEN-1);
                }
                else
                {
                    i4_ret = system("grep \"huluplus\" /tmp/html5_app");
                    if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
                    {
                        c_strncpy(s_tmp_str, "HULUPLUS",TVSTAUS_DEVICE_TYPE_LEN-1);
                    }
                    else
                    {
                        i4_ret = system("grep \"xumo\" /tmp/html5_app");
                        if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
                        {
                            c_strncpy(s_tmp_str, "XUMO",TVSTAUS_DEVICE_TYPE_LEN-1);
                        }
                        else
                        {
                            i4_ret = system("grep \"iheart\" /tmp/html5_app");
                            if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
                            {
                                c_strncpy(s_tmp_str, "IHEARTRADIO",TVSTAUS_DEVICE_TYPE_LEN-1);
                            }
                            else
                            {
                                c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
                            }
                        }
                    }
                }
            }
            else
            {
                c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
            }
        }
        else
        {
            c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
        }
        /* close file */
        if (fp_out != NULL)
        {
            fclose(fp_out);
            fp_out = NULL;
        }
    }
    else if (c_strcmp(t_g_shi_mode.s_input_source,"CAST") == 0) //for cast tv
    {
        c_strncpy(s_tmp_str, t_g_shi_mode.s_cast_app_id, TVSTATUS_CAST_APP_ID_LEN -1);
    }
    else
    {
        c_strncpy(s_tmp_str, "UNKNOWN",TVSTAUS_DEVICE_TYPE_LEN-1);
    }
    return  TVSTAR_OK;
}

static INT32 _tvstatus_dynamic_info_ass(VOID)
{
    INT32    i4_ret = 0;

    t_g_shi_mode.ui4_running_time += _TVSTATUS_TIMEOUT_DUR/1000;

    i4_ret = _tvstatus_input_source(t_g_shi_mode.s_input_source);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_get_device_osd_name(t_g_shi_mode.s_device_osd_name);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_get_device_vendor_id(t_g_shi_mode.s_device_vendor_id);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_get_third_party_app(t_g_shi_mode.s_third_party_app);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_gui_lang(t_g_shi_mode.crn_s639_lang);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_current_country(t_g_shi_mode.s_country);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_scan_type(&(t_g_shi_mode.ui1_scan_type));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_channel_scan_status(&(t_g_shi_mode.ui1_channel_scan_status));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    t_g_shi_mode.ui1_parental_ctrl=
                     _tvstatus_channel_ctrl_enable_idx();

    t_g_shi_mode.ui1_wfi_enab =
                     _tvstatus_wifi_remote_pair_status();

    i4_ret = _tvstatus_current_picmode(t_g_shi_mode.s_pic_mod);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    //a_nw_wlan_get_raw_signal_level(&(t_g_shi_mode.i4_sgnl));
    t_g_shi_mode.i4_sgnl=(UINT8)80;

    NET_802_11_BSS_INFO_T t_CurrBss;
    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    TVSTATUS_LOG_ON_FAIL(i4_ret);
    t_g_shi_mode.i2_Channel = t_CurrBss.i2_Channel;
    t_g_shi_mode.i2_Noise = t_CurrBss.i2_Noise;

    i4_ret = a_nw_get_ethernet_connect_info(&(t_g_shi_mode.b_wf_plug));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_wire_less_band(&(t_g_shi_mode.ui1_wirleband));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_wire_less_security(t_g_shi_mode.s_wire_less_scurity);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    t_g_shi_mode.ui2_audio_state=
                     _tvstatus_audio_state();

    //t_g_shi_mode.ui1_network_speed=(UINT8)100;
    _tvstatus_network_speed(t_g_shi_mode.s_network_speed);

    /* print dynamic xml info */
    _tvstate_print_info(&t_g_model, E_DATA_TYPE_SHI_DATA);

    return  TVSTAR_OK;

}

static VOID _tvstatus_timer_nfy(VOID *pv_data, SIZE_T z_size)
{
    INT32    i4_ret = 0;
    BOOL     b_xml_file_back_up_exist = FALSE;
    BOOL     b_xml_file_exist = FALSE;
    BOOL     b_xml_file_tmp_exist = FALSE;
    CHAR     s_static_back_up_path[TVSTAUS_STATIC_PATH_LEN] = {'\0'};
    CHAR     s_dynamic_back_up_path[TVSTAUS_DYNAMIC_PATH_LEN] = {'\0'};
    CHAR     s_static_path[TVSTAUS_STATIC_PATH_LEN] = {'\0'};
    CHAR     s_dynamic_path[TVSTAUS_DYNAMIC_PATH_LEN] = {'\0'};
    CHAR     s_static_temp_path[TVSTAUS_STATIC_PATH_LEN] = {'\0'};
    CHAR     s_dynamic_temp_path[TVSTAUS_DYNAMIC_PATH_LEN] = {'\0'};
    CHAR     s_cmd[TVSTAUS_CMD_LEN] = {'\0'};

    DBG_INFO(("%s() ......\r\n",__FUNCTION__));

    c_sprintf(s_static_back_up_path, "%s/%s", TVSTATE_XML_BACK_UP_PATH, TVSTATE_STATIC_XML_NAME);
    c_sprintf(s_dynamic_back_up_path, "%s/%s", TVSTATE_XML_BACK_UP_PATH, TVSTATE_DYNAMIC_XML_NAME);
    c_sprintf(s_static_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_STATIC_XML_NAME);
    c_sprintf(s_dynamic_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_DYNAMIC_XML_NAME);
    c_sprintf(s_static_temp_path, "%s/%s", TVSTATE_XML_TEMP_PATH, TVSTATE_STATIC_XML_NAME);
    c_sprintf(s_dynamic_temp_path, "%s/%s", TVSTATE_XML_TEMP_PATH, TVSTATE_DYNAMIC_XML_NAME);

    //3rd_rw  xml data
    b_xml_file_back_up_exist = ((access(s_static_back_up_path, F_OK) == 0 ? TRUE : FALSE)
                                 &&
                                 (access(s_dynamic_back_up_path, F_OK) == 0 ? TRUE : FALSE)
                                );

    //tmp xml data
    b_xml_file_exist = ((access(s_static_path, F_OK) == 0 ? TRUE : FALSE)
                         &&
                         (access(s_dynamic_path, F_OK) == 0 ? TRUE : FALSE)
                        );

    //basic xml data
    b_xml_file_tmp_exist = ((access(s_static_temp_path, F_OK) == 0 ? TRUE : FALSE)
                            &&
                            (access(s_dynamic_temp_path, F_OK) == 0 ? TRUE : FALSE)
                            );

    if (b_xml_file_tmp_exist)
    {
        if (!b_xml_file_exist)
        {
            if (b_xml_file_back_up_exist)
            {
                c_sprintf(s_cmd, "mkdir %s;cp -f %s %s %s",
                      TVSTATE_XML_PATH,
                      s_static_back_up_path, s_dynamic_back_up_path, TVSTATE_XML_PATH);
            }
            else
            {
                c_sprintf(s_cmd, "mkdir %s;cp -f %s %s %s",
                          TVSTATE_XML_PATH,
                          s_static_temp_path, s_dynamic_temp_path, TVSTATE_XML_PATH);
            }

            DBG_INFO(("<TVSTATUS> %s %d\n\n",s_cmd,__LINE__));

            system(s_cmd);
            system("sync");
        }

    }
    else
    {
        i4_ret = c_timer_stop(t_g_model.h_detect_timer);
        DBG_INFO(("<TVSTATUS> Routine timer stopped....\n\n"));
        TVSTATUS_LOG_ON_FAIL(i4_ret);
        return;
    }

    //if (NULL == t_g_model.pt_data_xml)
    //{
    //    DBG_ERROR(("<TVSTATUS>Call pf_parse_status_info !!!, %d \n", __LINE__));
    //    t_g_model.pf_parse_status_info(&t_g_model);
    //}

    DBG_INFO(("<TVSTATUS> parse info end !!!, %d \n", __LINE__));

    i4_ret = a_cfg_cust_get_sys_boot_up_times(&(t_g_shi_mode.ui4_boot_up_times));
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = _tvstatus_static_info_ass();
    if(i4_ret != TVSTAR_OK) {
        DBG_ERROR(("_tvstatus_static_info_ass failed, i4_ret=%d\r\n", i4_ret));
    }

    i4_ret = _tvstatus_dynamic_info_ass();
    if(i4_ret != TVSTAR_OK) {
        DBG_ERROR(("_tvstatus_dynamic_info_ass failed, i4_ret=%d\r\n", i4_ret));
    }
}

static VOID _tvstatus_timer_cb(HANDLE_T  h_timer, VOID *pv_data)
{
    DBG_INFO(("%s() Enter\r\n",__FUNCTION__));

    a_tvstatus_async_invoke(_tvstatus_timer_nfy, (VOID *)&h_timer, sizeof(HANDLE_T));
}

static VOID _tvstatus_partition_timer_nfy(VOID *pv_data, SIZE_T z_size)
{
    DBG_INFO(("%s() Enter\r\n",__FUNCTION__));
    INT32    i4_ret1 = 0;
    INT32    i4_ret2 = 0;
    ui2_try_num++;
    if (ui2_try_num > TVSTATUS_PARTITION_TIMER_RUN_TIMES)
    {
        if (h_partition_timer != NULL_HANDLE)
        {
            c_timer_delete(h_partition_timer);
            h_partition_timer = NULL_HANDLE;
            ui2_try_num = 0;
        }
        return;
    }

    i4_ret1 = _tvstatus_cust_get_serial_num();

    i4_ret2 = _tvstatus_cust_get_rj_mac();

    if((TVSTAR_OK != i4_ret1) || (TVSTAR_OK != i4_ret2))
    {
        _tvstatus_start_partition_timer();

        return;
    }

    if (h_partition_timer != NULL_HANDLE)
    {
        c_timer_delete(h_partition_timer);
        h_partition_timer = NULL_HANDLE;
        ui2_try_num = 0;
    }

    return;
}

static VOID _tv_status_partition_timer_cb (HANDLE_T  h_timer, VOID *pv_data)
{
    DBG_INFO(("%s() Enter\r\n",__FUNCTION__));

    a_tvstatus_async_invoke(_tvstatus_partition_timer_nfy, (VOID *)&h_timer, sizeof(HANDLE_T));
}

static INT32 _tvstatus_start_partition_timer()
{
    if (h_partition_timer != NULL_HANDLE)
    {
        c_timer_start(h_partition_timer,
                      TVSTATUS_PARTITION_TIMER_DELAY,
                      X_TIMER_FLAG_ONCE,
                      _tv_status_partition_timer_cb,
                      NULL);
    }

    return TVSTAR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_partition_ready
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static VOID _tvstatus_partition_ready(
    VOID*   pv_data,
    SIZE_T  z_size)
{
    INT32   i4_ret = TVSTAR_OK;

    DBG_INFO(("\n<TVSTATUS> PARTITION Ready.\n"));
    if (NULL_HANDLE == h_partition_timer)
    {
        i4_ret = c_timer_create(&h_partition_timer);
        TVSTATUS_LOG_ON_FAIL(i4_ret);
    }

    _tvstatus_start_partition_timer();

}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_sys_fm_partition_status_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _tvstatus_sys_fm_partition_status_nfy(
        UINT32             ui4_tag,
        FS_PARTITION_T     e_partition)
{
    if (FS_PARTITION_ALL == e_partition
        || FS_PARTITION_3RD == e_partition)
    {
        DBG_INFO(("\n<TVSTATUS>FS_PARTITION_ALL mounted.\n"));
        a_tvstatus_async_invoke(_tvstatus_partition_ready, NULL, 0);
    }

    return APP_CFGR_OK;
}

static INT32 _tvstatus_app_init_custom()
{
    INT32       i4_ret = TVSTAR_OK;

    i4_ret = c_fm_partition_reg_nfy(_tvstatus_sys_fm_partition_status_nfy, 0);
    TVSTATUS_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_NAV,
                              NULL,
                              _tvstat_chk_input_nfy_fct,
                              &t_g_model.ui2_acfg_nav_nfy);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _tvstatus_app_init_fct
 *
 * Description: This function is called in the context of TVSTATUS application when
 *              it starts.
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_app_init_fct (const CHAR*    ps_name,
                                  HANDLE_T       h_app)
{
    INT32    i4_ret;

    DBG_INFO (("<TVSTATUS> initializing TVSTATUS (application handle = %d)\n\r", (int) h_app));
    /* Reset model data. */
    c_memset (& t_g_model, 0, sizeof (TVSTATUS_MODEL_T));
    c_memset (& t_g_uni_mode, 0, sizeof (TVSTATUS_UNI_MODEL_T));
    c_memset (& t_g_shi_mode, 0, sizeof (TVSTATUS_SHI_MODEL_T));

    /*get system start running time */
    i4_ret = a_cfg_cust_get_sys_total_running_time(&(t_g_shi_mode.ui4_running_time));
    TVSTATUS_LOG_ON_FAIL(i4_ret);


    /* Store TVSTATUS application handle. */
    t_g_model.h_tvstatus = h_app;

    /* parase fw info init */
    t_g_model.pf_parse_status_info = _tvstate_parse_status_info;

    /* CLI in tvstatus relative */
#ifdef CLI_SUPPORT
    i4_ret = c_sema_create(&t_g_model.h_sema_cli,
                           X_SEMA_TYPE_BINARY,
                           X_SEMA_STATE_UNLOCK);
    if ( i4_ret != OSR_OK )
    {
        return TVSTAR_FAIL;
    }
    t_g_model.b_cli_flag = FALSE;

    /* Init CLI. */
    i4_ret = tvstatus_cli_init ();
    TVSTATUS_CHK_FAIL (i4_ret, i4_ret);
#endif

    i4_ret = c_sema_create(
                    &t_g_model.h_sync_sema,
                    X_SEMA_TYPE_MUTEX,
                    X_SEMA_STATE_UNLOCK
                    );
    if(i4_ret != OSR_OK) {
        DBG_ERROR(("create h_sync_sema failed, ret=%d\r\n", i4_ret));
        return TVSTAR_FAIL;
    }

    i4_ret = c_sema_create(
                    &t_g_model.h_wait_sema,
                    X_SEMA_TYPE_BINARY,
                    X_SEMA_STATE_UNLOCK
                    );
    if(i4_ret != OSR_OK) {
        DBG_ERROR(("create h_wait_sema failed, ret=%d\r\n", i4_ret));
        return TVSTAR_FAIL;
    }

    DBG_INFO(("<TVSTATUS> initializing TVSTATUS ((Line = %d)\n\r", __LINE__));

    /* Create and register callback function to widget manager. */
    i4_ret = c_wgl_register (_tvstatus_wgl_manager_cb_fct);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&t_g_model.h_detect_timer);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    if (b_g_enable_tvstat)
    {
        a_tvstat_start(b_g_enable_tvstat);
    }

    DBG_INFO(("<TVSTATUS> initializing TVSTATUS (Line = %d)\n\r", __LINE__));

    i4_ret = a_cfg_cust_get_sys_boot_up_times(&(t_g_shi_mode.ui4_boot_up_times));
    TVSTATUS_LOG_ON_FAIL(i4_ret);
    t_g_shi_mode.ui4_boot_up_times ++;
    i4_ret = a_cfg_cust_set_sys_boot_up_times(t_g_shi_mode.ui4_boot_up_times);
    TVSTATUS_LOG_ON_FAIL(i4_ret);

    _tvstatus_app_init_custom();

    DBG_INFO(("<TVSTATUS> initializing TVSTATUS ((Line = %d)\n\r", __LINE__));

    return  TVSTAR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_app_exit_fct
 *
 * Description: This function is called in the context of TVSTATUS application when
 *              it exits. This API should be responsible for clean-up data, etc.
 *
 * Inputs:  h_app               Contains the application handle.
 *          e_exit_mode         Contains the exit mode.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 _tvstatus_app_exit_fct (HANDLE_T           h_app,
                           APP_EXIT_MODE_T    e_exit_mode)
{
    if (t_g_model.h_detect_timer)
    {
        c_timer_delete(t_g_model.h_detect_timer);
        t_g_model.h_detect_timer = NULL_HANDLE;
    }

#ifdef CLI_SUPPORT
    if (t_g_model.h_sema_cli)
    {
        c_sema_delete(t_g_model.h_sema_cli);
        t_g_model.h_sema_cli = NULL_HANDLE;
    }
#endif

    if (t_g_model.h_wait_sema)
    {
        c_sema_delete(t_g_model.h_wait_sema);
        t_g_model.h_wait_sema = NULL_HANDLE;
    }

    if (t_g_model.h_sync_sema)
    {
        c_sema_delete(t_g_model.h_sync_sema);
        t_g_model.h_sync_sema = NULL_HANDLE;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_app_pause_fct
 *
 * Description: This function is called in the context of the TVSTATUS application
                when it pauses.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_app_pause_fct (HANDLE_T    h_app)
{
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_app_resume_fct
 *
 * Description: This function is called in the context of TVSTATUS application when
 *              it resumes.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_app_resume_fct (HANDLE_T    h_app)
{
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_app_process_msg_fct
 *
 * Description: This function is called in the context of TVSTATUS application
 *              when a message is received.
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_app_process_msg_fct (HANDLE_T       h_app,
                                         UINT32         ui4_type,
                                         const VOID*    pv_msg,
                                         SIZE_T         z_msg_len,
                                         BOOL           b_paused)
{
    INT32    i4_ret = TVSTAR_OK;
    BOOL     b_xml_file_exist = FALSE;
    CHAR     s_static_path[TVSTAUS_STATIC_PATH_LEN] = {'\0'};
    CHAR     s_dynamic_path[TVSTAUS_DYNAMIC_PATH_LEN] = {'\0'};
    CHAR     s_cmd[TVSTAUS_CMD_LEN] = {'\0'};

    switch (ui4_type)
    {
        case TVSTATUS_MSG_CODE_ASYNC_INVOKE:
        case TVSTATUS_MSG_CODE_ASYNC_INVOKE_IN_SYNC:
        {
            TVSTATUS_ASYNC_INVOKE_T* pt_async_invoke = (TVSTATUS_ASYNC_INVOKE_T*) pv_msg;
            DBG_INFO(("%s() Enter\r\n",__FUNCTION__));
            /* Invoke function. */
            if (pt_async_invoke->pf_async_func != NULL)
            {
                pt_async_invoke->pf_async_func ((VOID*) pt_async_invoke->uc_data,
                                                pt_async_invoke->z_data_len);
            }

            if (ui4_type == TVSTATUS_MSG_CODE_ASYNC_INVOKE_IN_SYNC) {
                _NOTIFY(t_g_model.h_wait_sema);
            }

            break;
        }

        default:
            break;
    }

    /* AM Messages */
    switch (ui4_type)
    {
        case AM_BRDCST_MSG_POWER_OFF:
        {

            i4_ret = a_cfg_cust_set_sys_total_running_time(t_g_shi_mode.ui4_running_time);
            TVSTATUS_LOG_ON_FAIL(i4_ret);

            c_sprintf(s_static_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_STATIC_XML_NAME);
            c_sprintf(s_dynamic_path, "%s/%s", TVSTATE_XML_PATH, TVSTATE_DYNAMIC_XML_NAME);

            b_xml_file_exist = ((access(s_static_path, F_OK) == 0 ? TRUE : FALSE)
                                 &&
                                 (access(s_dynamic_path, F_OK) == 0 ? TRUE : FALSE)
                                );

            if (b_xml_file_exist)
            {
                 c_sprintf(s_cmd, "mkdir %s;cp -f %s %s %s",
                          TVSTATE_XML_BACK_UP_PATH,
                          s_static_path,
                          s_dynamic_path,
                          TVSTATE_XML_BACK_UP_PATH);

                DBG_INFO(("<TVSTATUS> %s %d\n\n",s_cmd,__LINE__));
                system(s_cmd);
                system("sync");
            }
            else
            {
                DBG_ERROR(("<TVSTATUS> Save Xml File Failed....\n\n"));
            }

            #ifdef TVIS_SUPPORT
            #ifdef TVIS_AUTO_START
                a_tv_custom_stop_tvis();
            #endif
            #endif
            break;
        }
        case AM_BRDCST_MSG_POWER_ON:
        {
#ifdef TVIS_SUPPORT
#ifdef TVIS_AUTO_START
            //if( a_tv_custom_get_viewing_data_accepted() )
            {
                DBG_LOG_PRINT(("%s L%d user had accepted viewing data.",__FUNCTION__,__LINE__));
                a_tv_custom_resume_tvis();
                a_tv_custom_resume_dai();
//                a_tv_custom_resume_bt();
            }
#endif
#endif
            break;
        }
        default:
            break;
    }

    return  i4_ret;
}

/*-----------------------------------------------------------------------------
                    public functions implemenations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: tvstatus_app_send_msg
 *
 * Description: This API sends a message to the message queue of TVSTATUS application.
 *
 * Inputs:  ui4_type            Contains the type of the data.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 tvstatus_app_send_msg (UINT32         ui4_type,
                          const VOID*    pv_msg,
                          SIZE_T         z_msg_len)
{
    INT32   i4_ret;

    /* Send a message to TVSTATUS application's message queue. */
    i4_ret = c_app_send_msg (t_g_model.h_tvstatus,
                             ui4_type,
                             pv_msg,
                             z_msg_len,
                             NULL,
                             NULL);

    if (i4_ret != AEER_OK)
    {
        DBG_ERROR (("<TVSTATUS> ERR: send message = %d failed = %d\n\r", ui4_type, i4_ret));
    }

    return (i4_ret == AEER_OK) ? TVSTAR_OK : TVSTAR_FAIL;
}

INT32 a_tvstat_start(BOOL b_start)
{
    INT32 i4_ret = TVSTAR_OK;

    if (b_start)
    {
        i4_ret = c_timer_start(t_g_model.h_detect_timer,
                               _TVSTATUS_TIMEOUT_DUR,
                               X_TIMER_FLAG_REPEAT,
                               _tvstatus_timer_cb,
                               NULL);

        DBG_INFO(("<TVSTATUS> Routine timer started....\n\n");
        TVSTATUS_CHK_FAIL(i4_ret,i4_ret));
    }
    else
    {
        i4_ret = c_timer_stop(t_g_model.h_detect_timer);

        DBG_INFO(("<TVSTATUS> Routine timer stopped....\n\n");
        TVSTATUS_CHK_FAIL(i4_ret,i4_ret));
    }

    return TVSTAR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_tvstatus_async_invoke
 *
 * Description: This API requests an async invoke for a given function.
 *
 * Inputs:  pf_async_func        The function to be invoked.
 *          pv_data              Private data.
 *          z_data_len           The length of data.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_tvstatus_async_invoke (tvstatus_async_func   pf_async_func,
                            VOID*              pv_data,
                            SIZE_T             z_data_len)
{
    INT32                   i4_ret;
    TVSTATUS_ASYNC_INVOKE_T    t_async_invoke;

    /* Check arguments. */
    if ((pf_async_func == NULL) ||
        (z_data_len > ASYNC_DATA_MAX_LEN))
    {
        return TVSTAR_INV_ARG;
    }

    /* Copy async invoke data. */
    c_memset (& t_async_invoke, 0, sizeof (TVSTATUS_ASYNC_INVOKE_T));

    t_async_invoke.pf_async_func = pf_async_func;
    t_async_invoke.z_data_len    = z_data_len;
    c_memcpy (t_async_invoke.uc_data, pv_data, z_data_len * sizeof (UCHAR));

    /* Send message to TVSTATUS application's message queue. */
    i4_ret = tvstatus_app_send_msg (TVSTATUS_MSG_CODE_ASYNC_INVOKE,
                                 & t_async_invoke,
                                 sizeof (TVSTATUS_ASYNC_INVOKE_T));

    return (i4_ret == AEER_OK) ? TVSTAR_OK : TVSTAR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: a_tvstatus_async_invoke_in_sync
 *
 * Description: This API requests an async invoke for a given function in synchronous.
 *
 * Inputs:  pf_async_func        The function to be invoked.
 *          pv_data              Private data.
 *          z_data_len           The length of data.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_tvstatus_async_invoke_in_sync (tvstatus_async_func   pf_async_func,
                                    VOID*              pv_data,
                                    SIZE_T             z_data_len,
                                    UINT32             ui4_time)
{
    INT32                   i4_ret;
    TVSTATUS_ASYNC_INVOKE_T    t_async_invoke;

    /* Check arguments. */
    if ((pf_async_func == NULL) ||
        (z_data_len > ASYNC_DATA_MAX_LEN))
    {
        return TVSTAR_INV_ARG;
    }

    _SYNCHRONIZED_BEGIN(t_g_model.h_sync_sema);

    /* Copy async invoke data. */
    c_memset (& t_async_invoke, 0, sizeof (TVSTATUS_ASYNC_INVOKE_T));

    t_async_invoke.pf_async_func = pf_async_func;
    t_async_invoke.z_data_len    = z_data_len;
    c_memcpy (t_async_invoke.uc_data, pv_data, z_data_len * sizeof (UCHAR));

    /* Send message to TVSTATUS application's message queue. */
    do
    {
        i4_ret = tvstatus_app_send_msg (TVSTATUS_MSG_CODE_ASYNC_INVOKE_IN_SYNC,
                                     & t_async_invoke,
                                     sizeof (TVSTATUS_ASYNC_INVOKE_T));
        if (i4_ret < TVSTAR_OK)
        {
            break;
        }

        if (ui4_time != 0) {
            i4_ret = _WAIT_TIMEOUT(t_g_model.h_wait_sema, ui4_time);
            if (i4_ret == OSR_TIMEOUT) {
                i4_ret = TVSTAR_TIMEOUT;
                break;
            }

            if (i4_ret != OSR_OK) {
                i4_ret = TVSTAR_FAIL;
                break;
            }
        }

        i4_ret = TVSTAR_OK;
    } while(0);

    _SYNCHRONIZED_END(t_g_model.h_sync_sema);


    return (i4_ret == AEER_OK) ? TVSTAR_OK : TVSTAR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: a_tvstatus_init
 *
 * Description: This API registers TVSTATUS application to AMB.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_tvstatus_init (AMB_REGISTER_INFO_T*  pt_reg)
{
    /* Application descriptor. */
    APP_DESC_T  t_tvstatus_desc =
                {
                    ~((UINT64)0),   /* ui8_flags */
                    {
                        8 * 1024,   /* z_stack_size */
                        200,        /* ui1_priority */
                        96          /* ui2_num_msgs */
                    },
                    0,              /* ui4_app_group_id */
                    0,              /* ui4_app_id */
                    {
                        0,          /* z_min_memory */
                        100 * 1024, /* z_max_memory */
                        16777216,   /* ui8_max_files_size */
                        1024,       /* ui2_max_files */
                        32,         /* ui2_max_handles */
                        2,          /* ui2_max_threads */
                        16,          /* ui2_max_semaphores */
                        1,          /* ui2_max_msg_queues */
                        32,         /* ui2_max_nb_msgs */
                        32          /* ui2_max_msg_size */
                    },
                    96,             /* ui2_msg_count */
                    32              /* ui2_max_msg_size */
                };

    /* Application name. */
    c_memset (pt_reg->s_name, 0, sizeof (pt_reg->s_name));
    c_strcpy (pt_reg->s_name, TVSTATUS_NAME);

    /* Lifecycle callback functions. */
    pt_reg->t_fct_tbl.pf_init        = _tvstatus_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit        = _tvstatus_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause       = _tvstatus_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume      = _tvstatus_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg = _tvstatus_app_process_msg_fct;

    /* Application descriptor. */
    pt_reg->t_desc                   = t_tvstatus_desc;

    /* System key. */
    pt_reg->ui2_key_num              = 0;
}

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: a_tvstatus_check_cli_flag
 *
 * Description:
 *  This API is used to check if current running CLI function is in CLI thread or
 *  in Agent thread.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *  FALSE: CLI thread
 *  TRUE:  Agnet thread
 ----------------------------------------------------------------------------*/
BOOL  a_tvstatus_check_cli_flag(VOID)
{
    return t_g_model.b_cli_flag;
}

/*-----------------------------------------------------------------------------
 * Name: a_tvstatus_run_cli_in_tvstatus_thread
 *
 * Description:
 *  Async invoke the pf_cli_function in the CLI thread. This function will
 *  wait for the completion of pf_cli_function and then return.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 a_tvstatus_run_cli_in_tvstatus_thread(x_cli_exec_fct pf_cli_func,
                                      INT32          i4_argc,
                                      const CHAR**   pps_argv)
{
    INT32   i4_ret;
    TVSTATUS_CLI_DATA_T    t_data;
    TVSTATUS_CLI_DATA_T*   pt_data;

    t_data.pf_cli_func  = pf_cli_func;
    t_data.i4_argc      = i4_argc;
    t_data.pps_argv     = pps_argv;
    t_data.i4_ret       = -1;
    pt_data             = &t_data;

    i4_ret = a_tvstatus_async_invoke(_tvstatus_cli_action,
                                  (VOID*)&pt_data,
                                  sizeof(pt_data));
    if(i4_ret != TVSTAR_OK)
    {
        DBG_ERROR(("<TVSTATUS> Can't async invoke. \n"));
        return -1;
    }

    i4_ret = c_sema_lock(t_g_model.h_sema_cli,
                         X_SEMA_OPTION_WAIT);
    if(i4_ret != OSR_OK)
    {
        DBG_ERROR(("<TVSTATUS> Can't sema lock \n"));
        return -1;
    }

    return t_data.i4_ret;
}
#endif

INT32 a_tvstatus_set_cast_app_id(CHAR *ps_app_id)
{
    if (NULL == ps_app_id)
    {
        DBG_ERROR(("<TVSTATUS> NULL cast_app_id\n"));
        return TVSTAR_OK;
    }

    c_memset(t_g_shi_mode.s_cast_app_id, 0, sizeof(t_g_shi_mode.s_cast_app_id));
    c_strncpy(t_g_shi_mode.s_cast_app_id, ps_app_id, TVSTATUS_CAST_APP_ID_LEN-1);
    DBG_INFO(("<TVSTATUS> set cast app id=[%s]\n", t_g_shi_mode.s_cast_app_id));

    return TVSTAR_OK;
}


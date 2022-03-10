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
 * $RCSfile: app_tv_custom.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/03 $
 * $Author: hs_chengweishan $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_sb.h"
#include <unistd.h>

#include "c_dbg.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_scc.h"
#include "c_version.h"
#include "c_fm.h"
#include "c_dt.h"
#include "c_pcl.h"

#include "am/a_am.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_icl_common.h"
#include "nav/nav_common.h"
#include "nav/sys_info/a_sys_info.h"
#include "agent/a_agent.h"
#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"
#include "rest/a_rest_api.h"

#include "msgconvert.h"
#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#endif
#include "u_sys_name.h"
#include <unistd.h>
#include "u_irrc_btn_def.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "mi_common.h"
#include "mi_sys.h"
#include "mi_flash.h"



#ifdef APP_HOTKEY_WAKEUP_SUPPORT

#define YAHOO_XML_PATH "/3rd_rw/yahoo_widget/data/Widgets/Installed"
#define IHEARTRADIO_KEYWORD "l4.ihr"

typedef enum
{
    HOT_NETFLIX = 0,
    HOT_VUDU,
    HOT_AMAZON,
    HOT_IHEARTRADIO,
    HOT_MGO,
    HOT_XUMO,
    HOT_WATCHFREE,
    HOT_REDBOX,
    HOT_HAYSTACK,
    HOT_INVALID,
}HOT_KEY_APP_INDEX;

char* s_hot_app_key[HOT_INVALID+1]={"launchnetflix",
                        "launchvudu",
                        "amazon",
                        "iHeartRadio",
                        "mgo",
                        "xumo",
                        "watchfree",
                        "redbox",
                        "haystack",
                        "invalid_key"};

CHAR* ps_app_name[HOT_INVALID+1] = {"netflix",
                        "vudu",
                        "amazon",
                        "iheart radio",
                        "mgo",
                        "xumo",
                        "watchfree",
                        "redbox",
                        "haystack",
                        "invalid"};

#ifdef APP_TTS_SUPPORT
    #define APP_TV_CUSTOM_APP_NAME_MAX_LEN  64
    #define APP_TV_CUSTOM_UTF_APP_NAME_MAX_LEN  128
    #define APP_TV_CUSTOM_PROMPT_STRING         " is launching please wait"
#endif

#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifdef LINUX_TURNKEY_SOLUTION
static BOOL _g_b_overscan_enable = TRUE;
static BOOL b_y_fake_ui_show = FALSE;
#include "cmd_convert.h"
#endif

static BOOL b_banner_allow_visiable = TRUE;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
#ifdef APP_CUSTOMER_DEF_LOCK_CHK_LOGIC
static BOOL b_g_custom_temp_unlock = FALSE;
#endif

#ifdef APP_CUSTOMER_DEF_APP_TV_INIT_LOGIC
static UINT16 ui2_icl_app_statue_nfy_id = 0;
#endif

static IR_MODE_E e_g_ir_mode = IR_MODE_FAKE;

#ifdef APP_TV_NET_CUSTOM_SET_OSD_STATUS
static INT32 i4_g_osd_status = 0;
#endif

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
static HANDLE_T         h_prompt_UI_timer = NULL_HANDLE;
static HANDLE_T         h_send_key_Q_timer = NULL_HANDLE;
static BOOL             b_prompt_UI_timer_enable = FALSE;
static HOTKEY_APP_LAUNCH_INFO   t_hotkey_app_info = {HOTKEY_INVALID,NULL};
#endif

static BOOL             b_is_3rd_rw_ready = FALSE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
#ifdef TVIS_SUPPORT
static unsigned int _check_acr_parentid(void)
{
    FILE* fp = NULL;

    DBG_LOG_PRINT(("[APP TV] _check_acr_parentid \n"));
    fp = fopen("/tmp/inscape/tvispid", "r");
    if (fp == NULL)
    {
        DBG_LOG_PRINT((" get acr_parent pid failed\n"));
        system ("echo 0 > /tmp/inscape/tvispid"); /* prevent fscanf error. */
        {
            CHAR    link_path[64] = "/data/app/inscape";
            CHAR    target_path[64];
            CHAR    p_cmd_buf[256];

            memset(target_path, 0, sizeof(target_path));
            memset(p_cmd_buf, 0, sizeof(p_cmd_buf));

            int linkSize = readlink(link_path, target_path, sizeof(target_path)-1);
            if (linkSize < 0)
            {
                memset(target_path, 0, sizeof(target_path));
                c_sprintf(target_path, "%s", "/3rd/tvis/set_acr_parentid.sh");
            }
            else
            {
                target_path[linkSize]='\0';
                memset(target_path + linkSize, 0, sizeof(target_path)-linkSize);
                c_strncat(target_path, "/set_acr_parentid.sh", sizeof(target_path)-strlen(target_path)-1);
                DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
            }

            sprintf(p_cmd_buf,"sh %s",target_path);
            system(p_cmd_buf);
        }
    }
    else
    {
        unsigned int pid = 0;
        fscanf(fp,"%d",&pid);
        if(pid > 0)
        {
            DBG_LOG_PRINT(("acr pid [%d] \n",pid));
            fclose(fp);
            return pid;
        }
        else
        {
            usleep(10000);
            {
                CHAR    link_path[64] = "/data/app/inscape";
                CHAR    target_path[64];
                CHAR    p_cmd_buf[256];

                memset(target_path, 0, sizeof(target_path));
                memset(p_cmd_buf, 0, sizeof(p_cmd_buf));

                int linkSize = readlink(link_path, target_path, sizeof(target_path)-1);
                if (linkSize < 0)
                {
                    memset(target_path, 0, sizeof(target_path));
                    c_sprintf(target_path, "%s", "/3rd/tvis/set_tvispid.sh");
                }
                else
                {
                    target_path[linkSize]='\0';
                    memset(target_path + linkSize, 0, sizeof(target_path)-linkSize);
                    c_strncat(target_path, "/set_tvispid.sh", sizeof(target_path)-strlen(target_path)-1);
                    DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
                }

                sprintf(p_cmd_buf,"sh %s",target_path);
                system(p_cmd_buf);
            }
            fclose(fp);
        }
    }

    /* add crash state to process the corner case. */
    a_tv_custom_set_tvis_state(TVIS_MAIN_STATE_CRASHED);
    DBG_LOG_PRINT((" get acr_parent pid failed \n"));
    return 0;
}
#endif

 /*-----------------------------------------------------------------------------
 * Name
 *      _tv_custom_is_signal_loss
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _tv_custom_is_signal_loss (VOID)
{
    SIGNAL_STATUS_T e_status = SIGNAL_STATUS_UNKNOWN;
    SIZE_T          z_size;
    INT32           i4_ret;
    HANDLE_T        h_svctx = NULL_HANDLE;
    CHAR            s_disp_name[SYS_NAME_LEN+1];

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    acfg_get_svctx(s_disp_name, &h_svctx);

    z_size = sizeof(SIGNAL_STATUS_T);
    i4_ret = c_svctx_get(
                    h_svctx,
                    SVCTX_COMMON_GET_SIGNAL_STATUS,
                    (VOID*)&e_status,
                    &z_size
                    );
    if (i4_ret != SVCTXR_OK) {
        return FALSE;
    }

    if (e_status == SIGNAL_STATUS_UNKNOWN)
    {
        DBG_INFO(("[IR] --- SIGNAL_STATUS_UNKNOWN : [%d]\n", e_status));
    }
    else if (e_status == SIGNAL_STATUS_LOSS)
    {
        DBG_INFO(("[IR] --- SIGNAL_STATUS_LOSS : [%d]\n", e_status));
    }
    else
    {
        DBG_INFO(("[IR] --- SIGNAL_STATUS : [%d]\n", e_status));
    }

    if (e_status == SIGNAL_STATUS_UNKNOWN   ||
        e_status == SIGNAL_STATUS_LOSS)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_CUSTOMER_DEF_APP_TV_INIT_LOGIC
/*----------------------------------------------------------------------------
 * Name: _tv_custom_update_inp_src_info
 *
 * Description:
 *
 * Inputs:  e_win_id   current focused window id
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _tv_custom_update_inp_src_info(TV_WIN_ID_T e_win_id)
{
    INT32             i4_ret = 0;
    UTF16_T           *pw2s_name = 0;
    ISL_REC_T         t_isl_rec;
    SI_SET_INFO_T     t_set_info = {0};

    SI_TUNING_INFO_INP_SRC_INFO_T t_tun_input_src_info;

#ifdef APP_SI_NAV_NAME_INPUT_MSG_SUPPORT
    /*
    CHAR        s_alias_name[CECM_OSD_NAME_SIZE];
    c_memset (s_alias_name, 0, sizeof(s_alias_name)) ;
    */
#endif
    c_memset(&t_tun_input_src_info, 0, sizeof(SI_TUNING_INFO_INP_SRC_INFO_T));
#ifdef APP_PORTING
    t_tun_input_src_info.b_via_source = FALSE;
#endif
    i4_ret = nav_get_isl_rec(e_win_id, &t_isl_rec);
    if (i4_ret < 0)
    {
        return TVR_FAIL;
    }

    do{
        /* Priority: alias name > input source name */
    #ifdef APP_SI_NAV_NAME_INPUT_MSG_SUPPORT
        /* get input source lable display name */
        /*
        a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, s_alias_name);
        c_uc_ps_to_w2s(s_alias_name, t_tun_input_src_info.w2s_input_src_name_alias, CECM_OSD_NAME_SIZE);
        */
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

    c_memcpy(&t_set_info.u.t_tuning_info.t_input_src_info, (SI_TUNING_INFO_INP_SRC_INFO_T*)&t_tun_input_src_info, sizeof(SI_TUNING_INFO_INP_SRC_INFO_T));

    t_set_info.e_category = SI_CATEGORY_TUNING_INFO;
    t_set_info.u.t_tuning_info.ui4_info_mask = SI_TUNING_INFO_MASK_INPUT_SRC_INFO;

    a_si_set_item_info(&t_set_info);

    return TVR_OK;
}

#ifdef TVIS_SUPPORT
static TVIS_MAIN_STATE_T e_g_tvis_main_state = TVIS_MAIN_STATE_NOT_STARTED;
TVIS_MAIN_STATE_T a_tv_custom_get_tvis_state(VOID)
{
    return e_g_tvis_main_state;
}

VOID a_tv_custom_set_tvis_state(TVIS_MAIN_STATE_T e_state)
{
    e_g_tvis_main_state = e_state;
}

extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);
#ifdef TVIS_AUTO_START
static VOID _stop_tvis(
        VOID*           pv_data,
        SIZE_T          z_data_len)
{
    DBG_INFO(("%s %d _stop_tvis\n",__FUNCTION__,__LINE__));
    //1.kill -9 inscape_acr
    //AP_SYSTEM_CALL("kill -15 `ps -ef| awk '/[i]nscape_acr/{print $2}'`");
    //kill -9 launch_tvis.sh
    AP_SYSTEM_CALL("kill -9 `ps -ef | awk '/[l]aunch_tvis/{print $2}'`");
    pid_t pid=0;
    pid = _check_acr_parentid();
    if (pid > 0)
    {
        DBG_LOG_PRINT(("[APP TV] _stop_tvis send SIGTERM to ACR pid:%ld\n",pid));
        kill(pid,SIGTERM);
    }
    //2.remove related file of inscape_acr in /tmp.
    if(access("/tmp/inscape/tvis_state_started",0) == 0)
    {
        remove("/tmp/inscape/tvis_state_started");
    }

    if(access("/tmp/inscape/tvispid",0) == 0)
    {
        remove("/tmp/inscape/tvispid");
    }

    if(access("/tmp/inscape/crnt_src_cast",0) == 0)
    {
        remove("/tmp/inscape/crnt_src_cast");
    }
}

static VOID _start_tvis(
        VOID*           pv_data,
        SIZE_T          z_data_len)
{
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
    UINT32      ui4_flip_mirror_status = 0;
    UINT8       ui1_chip_version = 2;
    SIZE_T      z_size = sizeof(UINT32);
    UINT16      ui2_val = 0;
    TV_WIN_ID_T e_win_id = TV_WIN_ID_MAIN;
    ISL_REC_T   t_isl_rec = {0};
    INT32       i4_ret;
    UINT8   ui1_val = 0;

    /********************************************************************/
    //Change path for DLM, sepolicy should solved by Vizio
    CHAR    link_path[64] = "/data/app/inscape";
    CHAR    target_path[64];
    if (-1 == readlink(link_path, target_path, sizeof(target_path)))
    {
        memset(target_path, 0, sizeof(target_path));
        c_sprintf(target_path, "%s", "/3rd/tvis/launch_tvis.sh");
    }
    else
    {
        memset(target_path, 0, sizeof(target_path));
        c_strcat(link_path, "/launch_tvis.sh");
        c_sprintf(target_path, "%s", link_path);
        DBG_LOG_PRINT(("tvis symlink path is %s\r\n", target_path));
    }
    /********************************************************************/



    if (a_cfg_custom_get_acr(&ui2_val) != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[APP TV] %d get acr fail!\n",__LINE__));
        return;
    }

    do
    {
        /* SmartInteractivity=off, TOS not accept, set disable flag; */
        if (ACFG_ACR_OFF == ui2_val)
        {
            /*Inscape starting will check the disable flag*/
            AP_SYSTEM_CALL("touch /tmp/inscape/cfg_ACR_disabled");
            DBG_LOG_PRINT(("[APP TV] %d set acr disable.\n",__LINE__));
            break;
        }
    }while(0);
    if (a_cfg_cust_get_limited_ad_tracking(&ui1_val) != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[APP TV] %d get limited_ad_tracking fail!\n",__LINE__));
    }
    a_cfg_cust_set_limited_ad_tracking(ui1_val);

    z_size = sizeof(UINT32);
    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_FLIP_MIRROR;
    t_get_info.pv_get_info = (VOID *)&ui4_flip_mirror_status;
    t_get_info.pz_size = &z_size;
    a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,
                        (VOID*)&t_get_info);

    z_size = sizeof(UINT8);
    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_MTK_CHIP_VERSION;
    t_get_info.pv_get_info = (VOID *)&ui1_chip_version;
    t_get_info.pz_size = &z_size;
    a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,
                        (VOID*)&t_get_info);

    do {
        i4_ret = nav_get_focus_id(&e_win_id);
        if (NAVR_OK != i4_ret)
        {
            break;
        }
        i4_ret = nav_get_isl_rec(e_win_id, &t_isl_rec);
        if (NAVR_OK != i4_ret)
        {
            break;
        }

        if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
        {
            AP_SYSTEM_CALL("touch /tmp/inscape/crnt_src_cast");
        }
    } while (0);

    DBG_LOG_PRINT(("[hongzhao] target_path: %s\r\n",target_path));

//    AP_SYSTEM_CALL("kill -9 `ps -ef | awk '/[l]aunch_tvis/{print $2}'`");
//    AP_SYSTEM_CALL("kill -9 `ps -ef | awk '/[i]nscape_acr/{print $2}'`");
    _stop_tvis(NULL,0);

    {//added by zile.pang
        pid_t pid = 0;
        CHAR *launch_tvis_path = target_path;                       //hongzhao 2020/2/12 add for acr downloadable
        CHAR flip_mirror_status[128] = {0};
        CHAR chip_version[128] = {0};

        c_snprintf(flip_mirror_status, 128, "\"%d\"",ui4_flip_mirror_status);
        c_snprintf(chip_version, 128, "\"%d\"",ui1_chip_version);

        pid = fork();
        if(pid < 0)
        {
            DBG_LOG_PRINT(("\n fork error! %d:%s:%s\n",__LINE__,__FUNCTION__,__FILE__));
        }
        else if(pid == 0)
        {
            #define INSCAPE_UID 0
            #define SYSTEM_GID 0
            //CHAR *argv[] = {"sh",s_tmp_cmd,NULL};
            CHAR *argv[] = {"sh",launch_tvis_path,flip_mirror_status,chip_version,"&",NULL};

            if(setregid(SYSTEM_GID,SYSTEM_GID) < 0)
            {
                DBG_ERROR(("[%s %d] setregid failed\n ",__FUNCTION__,__LINE__));
            }
            if(setreuid(INSCAPE_UID,INSCAPE_UID) < 0)
            {
                DBG_ERROR(("[%s %d] setreuid failed\n ",__FUNCTION__,__LINE__));
            }
            execv("/bin/sh",argv);
        }
    }

}

static VOID _start_dai(
        VOID*           pv_data,
        SIZE_T          z_data_len)
{
    DBG_LOG_PRINT(("[APP TV] _start_dai\n"));
    const CHAR* p_dai_script_path = "/data/app/dai/launch_dai.sh";
    CHAR p_system_cmd[64]={0};

    if(access(p_dai_script_path,R_OK)==0)
    {
        DBG_LOG_PRINT(("[APP TV] Running DAI script\n"));
        sprintf(p_system_cmd,"sh %s &",p_dai_script_path);
        AP_SYSTEM_CALL(p_system_cmd);
    }
    else
   {
        DBG_LOG_PRINT(("[APP TV] _start_dai no dai script %s \n",p_dai_script_path));
   }
}

static VOID _start_bt(
        VOID*           pv_data,
        SIZE_T          z_data_len)
{
    DBG_LOG_PRINT(("[APP TV] _start_bt\n"));
    const CHAR* p_bt_script_path = "/data/app/bluetooth/launch_bluetooth.sh";
    CHAR p_system_cmd[64]={0};

    if(access(p_bt_script_path,R_OK)==0)
    {
        DBG_LOG_PRINT(("[APP TV] Running BLUETOOTH script\n"));
        sprintf(p_system_cmd,"sh %s &",p_bt_script_path);
        AP_SYSTEM_CALL(p_system_cmd);
    }
    else
   {
        DBG_LOG_PRINT(("[APP TV] _start_bt no bt script %s \n",p_bt_script_path));
   }
}

VOID a_tv_custom_resume_tvis()
{
    a_agent_async_invoke(_start_tvis, NULL, 0);
}

VOID a_tv_custom_stop_tvis()
{
    a_agent_async_invoke(_stop_tvis, NULL, 0);
}

VOID a_tv_custom_resume_dai()
{
    a_agent_async_invoke(_start_dai, NULL, 0);
}

VOID a_tv_custom_resume_bt()
{
    a_agent_async_invoke(_start_bt, NULL, 0);
}


#endif
#endif


/***
The command send to am is as:\n:am,am,remote:start=amazon\n
include:
1.s_source:am
2:s_destination:am
3.s_ack:remote
4.s_command:start
5:s_parameter:amazon
Please be noted:The command start/end is \n

*/
INT32 a_tv_net_send_cmd(CHAR* ps_cmd)
{
    CHAR* ps_split_value;
    UINT8 ui1_index = 0;
    CHAR*   ps_long_cmd[2] = {NULL};
    CHAR*   ps_cmd_value[5] = {NULL};
    CHAR    s_cmd[512] = {0};
    MSG_CONVERT_SEND_CMD_T t_send_cmd;
    UINT16  ui2_index = 0;

    DBG_INFO(("%s_%d ps_cmd:%s \n",__FUNCTION__,__LINE__,ps_cmd));
    while(*ps_cmd != '\0')
    {
        if(*ps_cmd != '\n')
        {
            s_cmd[ui2_index++] = *ps_cmd;
        }
        ps_cmd++;
    }
    DBG_INFO(("%s_%d sizeof(s_cmd):%d s_cmd:%s \n",__FUNCTION__,__LINE__,sizeof(s_cmd),s_cmd));
    ui2_index = 0;
    while(s_cmd[ui2_index] != 0)
    {
        s_cmd[ui2_index]=s_cmd[ui2_index+1];
        ui2_index++;
    }
    DBG_INFO(("%s_%d s_cmd:%s \n",__FUNCTION__,__LINE__,s_cmd));

    ps_split_value = strtok(s_cmd,":");
    /**
    split the command by :
    ***/
    while(ps_split_value)
    {
        {
            DBG_INFO(("iindex:%d value is:%s\n",ui1_index,ps_split_value));
            ps_long_cmd[ui1_index] = malloc(strlen(ps_split_value) + 1);
            memset(ps_long_cmd[ui1_index], 0, strlen(ps_split_value) + 1);
            strncpy(ps_long_cmd[ui1_index], ps_split_value, strlen(ps_split_value) + 1);
        }
        ui1_index++;
        ps_split_value = strtok(NULL,":");
    }
    DBG_INFO(("cmd  value is:%s\n",ps_long_cmd[0]));
    DBG_INFO(("cmd  value is:%s\n",ps_long_cmd[1]));

    ps_split_value = strtok(ps_long_cmd[0],",");
    ui1_index=0;
    /**
    split the command1 by "," this command include:s_source,s_destination,s_ack
    **/
    while(ps_split_value)
    {
        DBG_INFO(("iindex:%d value is:%s\n",ui1_index,ps_split_value));
        ps_cmd_value[ui1_index] = malloc(strlen(ps_split_value) + 1);
        memset(ps_cmd_value[ui1_index], 0, strlen(ps_split_value) + 1);
        strncpy(ps_cmd_value[ui1_index], ps_split_value, strlen(ps_split_value) + 1);
        ui1_index++;
        ps_split_value = strtok(NULL,",");
    }
    ui1_index = 3;
    ps_split_value = strtok(ps_long_cmd[1],"=");
        /**
    split the command by "=" this command include:s_command,s_parameter
    be careful the value s_parameter should't inlucde \n
    **/
    while(ps_split_value)
    {
        DBG_INFO(("iindex:%d value is:%s\n",ui1_index,ps_split_value));
        ps_cmd_value[ui1_index] = malloc(strlen(ps_split_value) + 1);
        memset(ps_cmd_value[ui1_index], 0, strlen(ps_split_value) + 1);
        strncpy(ps_cmd_value[ui1_index], ps_split_value, strlen(ps_split_value)+1);

        ui1_index++;

        ps_split_value = strtok(NULL,"=");
    }
    if(ps_cmd_value[0]!= NULL)
        DBG_INFO(("ps_cmd_value1  value is:%s\n",ps_cmd_value[0]));
    if(ps_cmd_value[1]!= NULL)
        DBG_INFO(("ps_cmd_value2  value is:%s\n",ps_cmd_value[1]));
    if(ps_cmd_value[2]!= NULL)
        DBG_INFO(("ps_cmd_value3  value is:%s\n",ps_cmd_value[2]));
    if(ps_cmd_value[3]!= NULL)
        DBG_INFO(("ps_cmd_value4  value is:%s\n",ps_cmd_value[3]));
    if(ps_cmd_value[4]!= NULL)
        DBG_INFO(("ps_cmd_value5  value is:%s\n",ps_cmd_value[4]));
    t_send_cmd.s_source = NULL;
    t_send_cmd.s_destination = NULL;
    t_send_cmd.s_ack = NULL;
    t_send_cmd.s_command = NULL;
    t_send_cmd.s_parameter = NULL;

    if(ps_cmd_value[0]!= NULL)
    {
        t_send_cmd.s_source = ps_cmd_value[0];
        DBG_INFO(("t_send_cmd.s_source:%s\n",t_send_cmd.s_source));
    }
    if(ps_cmd_value[1]!= NULL)
    {
        t_send_cmd.s_destination = ps_cmd_value[1];
        DBG_INFO(("t_send_cmd.s_destination:%s\n",t_send_cmd.s_destination));
    }
    if(ps_cmd_value[2]!= NULL)
    {
        t_send_cmd.s_ack = ps_cmd_value[2];
        DBG_INFO(("t_send_cmd.s_ack:%s\n",t_send_cmd.s_ack));
    }
    if(ps_cmd_value[3]!= NULL)
    {
        t_send_cmd.s_command = ps_cmd_value[3];
        DBG_INFO(("t_send_cmd.s_command:%s\n",t_send_cmd.s_command));
    }
    if(ps_cmd_value[4]!= NULL)
    {
        t_send_cmd.s_parameter = ps_cmd_value[4];
        DBG_INFO(("t_send_cmd.s_parameter:%s\n",t_send_cmd.s_parameter));
    }
    a_msg_convert_send_command(&t_send_cmd);
    return TVR_OK;
}

INT32 cmd_convert_send_cmd(CHAR* ps_cmd)
{
    a_tv_net_send_cmd(ps_cmd);
    return TVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tv_custom_partition_ready
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _tv_custom_partition_ready (
        VOID*           pv_data,
        SIZE_T          z_data_len)
{
    TV_WIN_ID_T         e_focused_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T           t_isl_rec = {0};

    b_is_3rd_rw_ready = TRUE;

    /* update input source info */
    nav_get_focus_id(&e_focused_win_id);
    nav_get_isl_rec(e_focused_win_id, &t_isl_rec);

    if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        _tv_custom_update_inp_src_info (e_focused_win_id);
    }

#ifdef TVIS_SUPPORT
#ifdef TVIS_AUTO_START
    /* start TVIS whenever tos/privacy policy status or ACR on/off status. */
    //if( a_tv_custom_get_viewing_data_accepted() )
    {
        DBG_LOG_PRINT(("%s L%d _start_tvis\n",__FUNCTION__,__LINE__));
//              _start_bt(pv_data, z_data_len); //dolphin 20200119s start bt when partittion ready

    }
#endif
#endif
}

/*-----------------------------------------------------------------------------
 * Name: _tv_custom_fm_partition_status_nfy
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
static INT32 _tv_custom_fm_partition_status_nfy(
        UINT32             ui4_tag,
        FS_PARTITION_T     e_partition)
{
    if (FS_PARTITION_ALL == e_partition)
    {
        DBG_INFO(("[TV] --- FS_PARTITION_ALL mounted. FUNC: %s\n", __FUNCTION__));
        a_agent_async_invoke(_tv_custom_partition_ready, NULL, 0);
    }

    return TVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _tv_custom_icl_app_status_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _tv_custom_icl_app_status_cb (UINT16             ui2_nfy_id,
                                           VOID*              pv_tag,
                                           ICL_NOTIFY_DATA_T* pt_notify_data)
{
    ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_APP_STATUS)
    {
        return TVR_OK;
    }

    DBG_INFO(("[TV] --- icl app status in FUNC: %s.\n", __FUNCTION__));

    if (a_cfg_custom_get_wifi_remote_support())
    {
        a_tv_net_custom_update_ir_mode();
    }

    return TVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_init
 * Description
 *      this API will be invoked after ISL & A_CFG initialized
 * Input arguments
 *      NONE
 * Output arguments
 *      NONE
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *---------------------------------------------------------------------------*/
INT32 a_tv_custom_init(VOID)
{
    INT32           i4_ret = TVR_OK;

    /* register app status callback func */
    i4_ret = a_icl_notify_reg(ICL_GRPID_APP_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _tv_custom_icl_app_status_cb,
                              &ui2_icl_app_statue_nfy_id);
    if(ICLR_OK != i4_ret)
    {
        ui2_icl_app_statue_nfy_id = 0xFFFF;
    }

    /* register app status callback func */
    c_fm_partition_reg_nfy(_tv_custom_fm_partition_status_nfy, 0);

    return TVR_OK;
}
#endif /* end of APP_CUSTOMER_DEF_APP_TV_INIT_LOGIC */
#ifdef APP_CUSTOMER_DEF_LOCK_CHK_LOGIC

/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_unlock_crnt_svc
 * Description
 * Input arguments
 *      h_svctx
 * Output arguments
 *      pt_resulted_isl_rec     the resulted ISL record
 *      pt_resulted_svl_rec     the resulted SVL record
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *---------------------------------------------------------------------------*/
INT32 a_tv_unlock_crnt_svc(
                    HANDLE_T                    h_svctx,
                    ISL_REC_T*                  pt_resulted_isl_rec,
                    SVL_REC_T*                  pt_resulted_svl_rec
                    )
{
    UINT8      ui1_val = 0;
    SIZE_T     z_size = 0;


    ui1_val = RATING_ENABLED_STATUS_OFF;
    z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                       (VOID*)&ui1_val,
                       z_size);

    a_rating_enable(FALSE);

    b_g_custom_temp_unlock = TRUE;
    c_svctx_unblock_svc(h_svctx, FALSE);

    return TVR_NOT_SUPPORT;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_is_temp_unlock
 * Description
 *  Get the temp unlock flag.
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_tv_custom_is_temp_unlock(VOID)
{
    return b_g_custom_temp_unlock;
}

#endif /* end of APP_CUSTOMER_DEF_LOCK_CHK_LOGIC */
#ifdef APP_CUSTOMER_DEF_LAST_INP_SRC_ID
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_set_last_input_src_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_tv_set_last_input_src_id(
                    TV_WIN_ID_T                 e_win_id,
                    UINT8                       ui1_inp_src_id
                    )
{
    return TVR_NOT_SUPPORT;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_get_last_isl_rec_by_win_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_tv_get_last_isl_rec_by_win_id(
                    TV_WIN_ID_T                 e_win_id,
                    ISL_REC_T*                  pt_isl_rec
                    )
{
    return TVR_NOT_SUPPORT;
}
#endif /* end of APP_CUSTOMER_DEF_LAST_INP_SRC_ID */
#ifdef APP_CUSTOMER_DEF_AFTER_SELECT_SVC
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_after_select_svc
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_tv_custom_after_select_svc(
                    HANDLE_T                        h_svctx,
                    ISL_REC_T*                      pt_isl_rec,
                    SVL_REC_T*                      pt_svl_rec
                    )
{
    return TVR_NOT_SUPPORT;
}
#endif /* APP_CUSTOMER_DEF_AFTER_SELECT_SVC */
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_get_scart_output_switch_status
 * Description
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_tv_custom_get_scart_output_switch_status(
                    SCART_OUTPUT_SWITCH_HINT_T*    pt_scart_switch_hint,    /* IN */
                    BOOL*                          pb_tv_scart_enabled,     /* OUT */
                    BOOL*                          pb_monitor_scart_enabled /* OUT */
                    )
{
    /* Default value */
    BOOL    b_tv_scart_enabled      = TRUE;
    BOOL    b_monitor_scart_enabled = TRUE;

    do
    {
        /* Check TV Mode, If it is in PIP/POP mode, must set TV_SCART/Monitor_SCART to TRUE, to let SVCXT behavior correct */
        /* Actually, the TV_SCART/Monitor_SCART are not displayed. */
        if (pt_scart_switch_hint->e_tv_mode == TV_MODE_TYPE_PIP ||
            pt_scart_switch_hint->e_tv_mode == TV_MODE_TYPE_POP)
        {
            b_tv_scart_enabled = TRUE;
            b_monitor_scart_enabled = TRUE;
            break;
        }

#ifdef  APP_TV_CUSTOM_ONLY_ALLOW_ANALOG_SIGNAL_TO_MONITOR_OUT
        /* Analog TV allows monitor out */
        if (pt_scart_switch_hint->pt_isl_rec->e_src_type == INP_SRC_TYPE_TV &&
            pt_scart_switch_hint->e_tv_brdcst_type == BRDCST_TYPE_ANALOG)
        {
            b_tv_scart_enabled = TRUE;
            b_monitor_scart_enabled = TRUE;
            break;
        }
        /* Analog input source (COMP_VIDEO, COMBI, S_VIDEO) allows monitor out */
        else if (pt_scart_switch_hint->pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO ||
                 pt_scart_switch_hint->pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_COMBI      ||
                 pt_scart_switch_hint->pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_S_VIDEO)
        {
            b_tv_scart_enabled = TRUE;
            b_monitor_scart_enabled = TRUE;
            break;
        }

        /* For other cases, no monitor out. */
        else
        {
            b_tv_scart_enabled = FALSE;
            b_monitor_scart_enabled = FALSE;
            break;
        }
#endif  /* APP_TV_CUSTOM_ONLY_ALLOW_ANALOG_SIGNAL_TO_MONITOR_OUT */

        /* For other case, default values are applied. */

    } while(0);

    /* Result */
    *pb_tv_scart_enabled      = b_tv_scart_enabled;
    *pb_monitor_scart_enabled = b_monitor_scart_enabled;

    return TVR_OK;
}


#endif
#ifdef LINUX_TURNKEY_SOLUTION
#if 1 // APP_YAHOO6
/******************************************************************************/
/**
 * @brief   This function gets the yahoo ui status to /tmp folder
 * @param
 * @retval  TRUE      Yahoo ui/video is showing
 * @retval  FALSE      Yahoo ui/video is un-showing
 */
/******************************************************************************/
BOOL a_tv_custom_get_y_fake_ui_status(VOID)
{
    return b_y_fake_ui_show;
}
/******************************************************************************/
/**
 * @brief   This function sets the yahoo ui status to /tmp folder
 * @param   TRUE      Yahoo ui/video is setting to show
 * @param   FALSE      Yahoo ui/video is settting to un-show
 * @retval
 * @retval
 */
/******************************************************************************/
VOID a_tv_custom_set_y_fake_ui_status(BOOL b_show)
{
    b_y_fake_ui_show = b_show;
}
/******************************************************************************/
/**
 * @brief   This function trigger widget key behavior
 * @param
 * @retval
  */
/******************************************************************************/
BOOL a_tv_custom_handle_widget_key(VOID)
{
#if 0
    if (FALSE == b_y_fake_ui_show)
    {
        cmd_convert_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=y_fake_ui\n");
    }else{
        DBG_INFO(("[handle widget event] When yahoo is showing, widget key always sends to yahoo\n"));
        cmd_convert_send_cmd("\n:dtv_app_mtk,yahoo,:click=WIDGET\n");
    }
#endif
#ifndef APP_C4TV_SUPPORT
    cmd_convert_send_cmd("\n:dtv_app_mtk,am,:show=yahoo\n");
    cmd_convert_send_cmd("\n:dtv_app_mtk,am,:focus=yahoo\n");
    cmd_convert_send_cmd("\n:dtv_app_mtk,yahoo,:click=WIDGET\n");
#else
    DBG_LOG_PRINT(("CAST TV WIDGET NO Launch Yahoo but cast instead\r\n"));
#endif
    //a_nav_set_show_banner_expecial_btn(TRUE);
    return TRUE;
}
#endif

/******************************************************************************/
/**
 * @brief   This function sets the model name to /tmp folder
 * @param
 * @retval  TVR_OK      The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_tv_custom_set_model_name (VOID)
{
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    FILE * fl = fopen ("/tmp/cfg_model_name","w");
    if (fl == NULL)
    {
        return 0;
    }

    a_cfg_custom_get_model_name(s_model_name);

    fprintf(fl, "%s", s_model_name);
    fclose (fl);

    return TVR_OK;
}

/******************************************************************************/
/**
 * @brief   This function sets the version to /tmp folder
 * @param
 * @retval  TVR_OK      The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_tv_custom_set_version (VOID)
{
    CHAR s_tmp_buf[128] = {0};
    FILE * fl = fopen ("/tmp/cfg_version","w");
    if (fl == NULL)
    {
        return 0;
    }

    c_snprintf(s_tmp_buf, 128, "%s", c_sys_get_version());

    //fwrite( s_tmp_buf, sizeof(CHAR), strlen(s_tmp_buf), fl);
    fprintf(fl, "%s", s_tmp_buf);
    fclose (fl);

#if 0
    c_snprintf(s_tmp_buf, 128, "echo \"%s\" > /tmp/cfg_version", c_sys_get_version());
    system(s_tmp_buf);
#endif

    return TVR_OK;
}

/******************************************************************************/
/**
 * @brief   This function sets the serial number to /tmp folder
 * @param
 * @retval  TVR_OK      The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_tv_custom_set_serial_number (VOID)
{
    CHAR s_tmp_buf[128] = {0};

    c_snprintf(s_tmp_buf, 128, "echo \"%s\" > /tmp/cfg_firmware_version", c_sys_get_serial_number());
    AP_SYSTEM_CALL(s_tmp_buf);

    return TVR_OK;
}

INT32 a_tv_custom_set_viewing_data_accepted(BOOL b_accept)
{
    if(b_accept)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",
                    __FILE__, __FUNCTION__, __LINE__));
      AP_SYSTEM_CALL("touch /data/viewing_data_accepted");
    }
    else
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return remove("/data/viewing_data_accepted");
    }
    return 0;
}
BOOL a_tv_custom_get_viewing_data_accepted(VOID)
{
    if(access("/data/viewing_data_accepted",0) == 0)
    {
        return TRUE;
    }
    return FALSE;
}

INT32 a_tv_custom_set_viewing_data_accepted_by_oobe_menu(BOOL b_accept)
{
    if(b_accept)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",
                    __FILE__, __FUNCTION__, __LINE__));
        AP_SYSTEM_CALL("touch /data/viewing_data_accepted_by_oobe_menu");
    }
    else
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return remove("/data/viewing_data_accepted_by_oobe_menu");
    }
    return 0;
}
BOOL a_tv_custom_get_viewing_data_accepted_by_oobe_menu(VOID)
{
    if(access("/data/viewing_data_accepted_by_oobe_menu",0) == 0)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return TRUE;
    }
    return FALSE;
}


/******************************************************************************/
/**
 * @brief   This function sets the user selection for Term of Service (TOS) in
 *          on boarding.
 * @param   b_accept [in]   Accept or not.
 * @retval  TVR_OK      The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_tv_custom_set_tos (BOOL b_accept)
{
    if (b_accept == TRUE)
    {
        AP_SYSTEM_CALL("echo 1 > /data/cfg_tos; sync");
        DBG_LOG_PRINT(("[L%d %s]echo 1 > /data/cfg_tos; sync\n", __LINE__, __func__));
    }
    else
    {
        AP_SYSTEM_CALL("echo 0 > /data/cfg_tos; sync");
        DBG_LOG_PRINT(("[L%d %s]echo 0 > /data/cfg_tos; sync\n", __LINE__, __func__));
    }

    a_icl_custom_set_tos_info(ICL_TOS_SET);

    return TVR_OK;
}
/******************************************************************************/
/**
 * @brief   This function sets the user selection for Privacy Policy in
 *          on boarding.
 * @param   b_accept [in]   Accept or not.
 * @retval  TVR_OK      The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 a_tv_custom_set_privacy (BOOL b_accept)
{
    if (b_accept == TRUE)
    {
        AP_SYSTEM_CALL("echo 1 > /data/cfg_privacy; sync");
        DBG_LOG_PRINT(("[L%d %s]echo 1 > /data/cfg_privacy; sync\n", __LINE__, __func__));
    }
    else
    {
        AP_SYSTEM_CALL("echo 0 > /data/cfg_privacy; sync");
        DBG_LOG_PRINT(("[L%d %s]echo 0 > /data/cfg_privacy; sync\n", __LINE__, __func__));
    }

    a_icl_custom_set_tos_info(ICL_PRI_SET);

    return TVR_OK;
}

/******************************************************************************/
/**
 * @brief   This function get the user selection for Term of Service (TOS) in
 *          on boarding.
 * @param
 * @retval  TRUE      TOS is accepted.
 * @retval  FALSE     TOS is not accepted.
 */
/******************************************************************************/
BOOL a_tv_custom_get_tos (VOID)
{
    BOOL b_accept = FALSE;
    CHAR ui1_ch;

    FILE * fl = fopen ("/data/cfg_tos","r");

    if (fl == NULL)
    {
        return b_accept;
    }

    if (fread(&ui1_ch, sizeof(CHAR), 1, fl) == 1)
    {
        if (ui1_ch == '1')
        {
            b_accept = TRUE;
        }
    }

    fclose (fl);

    return b_accept;
}
/******************************************************************************/
/**
 * @brief   This function get the user selection for Privacy Policy in
 *          on boarding.
 * @param
 * @retval  TRUE      Privacy policy is accepted.
 * @retval  FALSE     Privacy policy is not accepted.
 */
/******************************************************************************/
BOOL a_tv_custom_get_privacy (VOID)
{
    BOOL b_accept = FALSE;
    CHAR ui1_ch;

    FILE * fl = fopen ("/data/cfg_privacy","r");

    if (fl == NULL)
    {
        return b_accept;
    }

    if (fread(&ui1_ch, sizeof(CHAR), 1, fl) == 1)
    {
        if (ui1_ch == '1')
        {
            b_accept = TRUE;
        }
    }

    fclose (fl);

    return b_accept;
}

INT32 a_tv_custom_set_conn_type (BOOL b_wired)
{
    if (b_wired)
    {
        AP_SYSTEM_CALL("echo wired > /tmp/cfg_conn");
    }
    else
    {
        AP_SYSTEM_CALL("echo wireless > /tmp/cfg_conn");
    }

    return TVR_OK;
}

/******************************************************************************/
/**
 * @brief   This function set the show status for Viewing Data.
 * @param
 * @retval  TRUE      Viewing Data have showed.
 * @retval  FALSE     Viewing Data have not showed.
 */
/******************************************************************************/
INT32 a_tv_custom_set_viewing_data_show (BOOL b_showed)
{
    if (b_showed == TRUE)
    {
        AP_SYSTEM_CALL("touch /data/cfg_viewing_data");
    }
    else
    {
        AP_SYSTEM_CALL("rm /data/cfg_viewing_data;sync");
    }

    return TVR_OK;
}

/******************************************************************************/
/**
 * @brief   This function get the show status for Viewing Data .
 * @param
 * @retval  TRUE      Viewing Data have showed.
 * @retval  FALSE     Viewing Data have not showed.
 */
/******************************************************************************/
BOOL a_tv_custom_get_viewing_data_show (VOID)
{
    BOOL    b_file_exist = FALSE;
    b_file_exist = (access("/data/cfg_viewing_data", 0) == 0 ? TRUE : FALSE);

    return b_file_exist;
}

INT32 a_tv_custom_set_http_url_status (BOOL b_accept)
{
    if (b_accept == TRUE)
        AP_SYSTEM_CALL("echo 1 > /data/http_url_for_viewing_data_status; sync");
    else
        AP_SYSTEM_CALL("echo 0 > /data/http_url_for_viewing_data_status; sync");
    return TVR_OK;
}

INT32 a_tv_custom_get_http_url_status (BOOL* pb_accept)
{
    BOOL b_accept = FALSE;
    CHAR ui1_ch = '0';
    FILE * fl = fopen ("/data/http_url_for_viewing_data_status","r");
    if (fl == NULL)
    {
        return TVR_NOT_EXIST;
    }
    if (fread(&ui1_ch, sizeof(CHAR), 1, fl) == 1)
    {
        if (ui1_ch == '1')
            b_accept = TRUE;
    }
    fclose (fl);
    *pb_accept = b_accept;
    return TVR_OK;
}

VOID a_tv_custom_clear_http_url_status(VOID)
{
    if ((0 == access("/data/http_url_for_viewing_data_status", F_OK)))
    {
        AP_SYSTEM_CALL("rm /data/http_url_for_viewing_data_status;sync");
    }
}
#endif

#ifdef  APP_CUSTOMER_DEF_TV_LISTABLE_CHECK_NW_MASK_AND_BITS
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_get_listable_svl_rec_check_nw_mask
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT32 a_tv_custom_get_listable_svl_rec_check_nw_mask(VOID)
{
    return (SB_VNET_ACTIVE | SB_VNET_VISIBLE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_get_listable_svl_rec_check_nw_bits
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT32 a_tv_custom_get_listable_svl_rec_check_nw_bits(VOID)
{
    return (SB_VNET_ACTIVE | SB_VNET_VISIBLE);
}
#endif /* APP_CUSTOMER_DEF_TV_LISTABLE_CHECK_NW_MASK_AND_BITS */


VOID a_tv_custom_set_lang(UINT16 ui2_lang)
{
    BOOL b_change = TRUE;
    CHAR ui1_ch[4] = {0};
    FILE * fl = fopen ("/tmp/cfg_lang","r");

    if (fl != NULL)
    {
        if (fread(&ui1_ch, sizeof(CHAR), 3, fl) != 0)
        {
            if ((c_strcmp(ui1_ch,"eng") == 0) && (ui2_lang == 0))
            {
                DBG_INFO(("\nCurren language is eng and same with cfg_lang\n"));
                b_change = FALSE;
            }
            else if ((c_strcmp(ui1_ch,"fre") == 0) && (ui2_lang == 1))
            {
                DBG_INFO(("\nCurren language is fre and same with cfg_lang\n"));
                b_change = FALSE;
            }
            else if ((c_strcmp(ui1_ch,"spa") == 0) && (ui2_lang == 2))
            {
                DBG_INFO(("\nCurren language is spa and same with cfg_lang\n"));
                b_change = FALSE;
            }
        }

        fclose (fl);
    }

    if (b_change == TRUE)
    {
        switch(ui2_lang)
        {
            case 0: /*MLM_MENU_LANG_ENG*/
                AP_SYSTEM_CALL("echo eng > /tmp/cfg_lang");
                a_cfg_set_tts_lan_idx(APP_CFG_TTS_LAN_ENG_IDX);
                break;
            case 1: /*MLM_MENU_LANG_FRE*/
                AP_SYSTEM_CALL("echo fre > /tmp/cfg_lang");
                a_cfg_set_tts_lan_idx(APP_CFG_TTS_LAN_SPA_IDX);
                break;
            case 2: /*MLM_MENU_LANG_SPA*/
                AP_SYSTEM_CALL("echo spa > /tmp/cfg_lang");
                a_cfg_set_tts_lan_idx(APP_CFG_TTS_LAN_SPA_IDX);
                break;
            default:
                AP_SYSTEM_CALL("echo eng > /tmp/cfg_lang");
                a_cfg_set_tts_lan_idx(APP_CFG_TTS_LAN_ENG_IDX);
                break;
        }
        a_cfg_update_tts_lan_idx();
    }
}

VOID a_tv_custom_set_country(UINT16 ui2_country)
{
    BOOL b_change = TRUE;
    CHAR ui1_ch[4] = {0};
    FILE * fl = fopen ("/tmp/cfg_country","r");

    if (fl != NULL)
    {
        if (fread(&ui1_ch, sizeof(CHAR), 3, fl) != 0)
        {
            if ((c_strcmp(ui1_ch,"USA") == 0) && (ui2_country == 0))
            {
                DBG_INFO(("\nCurren country is USA and same with cfg_country\n"));
                b_change = FALSE;
            }
            else if ((c_strcmp(ui1_ch,"MEX") == 0) && (ui2_country == 1))
            {
                DBG_INFO(("\nCurren country is MEX and same with cfg_country\n"));
                b_change = FALSE;
            }
            else if ((c_strcmp(ui1_ch,"CAN") == 0) && (ui2_country == 2))
            {
                DBG_INFO(("\nCurren country is CAN and same with cfg_country\n"));
                b_change = FALSE;
            }
            else if ((c_strcmp(ui1_ch,"XXX") == 0) && (ui2_country == 3))
            {
                DBG_INFO(("\nCurren country is Unknown and same with cfg_country\n"));
                b_change = FALSE;
            }
        }

        fclose (fl);
    }

    if (b_change == TRUE)
    {
        switch(ui2_country)
        {
            case 0: /*ACFG_COUNTRY_CODE_US*/
                AP_SYSTEM_CALL("echo USA > /tmp/cfg_country");
                break;
            case 1: /*ACFG_COUNTRY_CODE_MEX*/
                AP_SYSTEM_CALL("echo MEX > /tmp/cfg_country");
                break;
            case 2: /*ACFG_COUNTRY_CODE_CA*/
                AP_SYSTEM_CALL("echo CAN > /tmp/cfg_country");
                break;
            case 3: /*ACFG_COUNTRY_CODE_UNKNOWN*/
                AP_SYSTEM_CALL("echo XXX > /tmp/cfg_country");
                break;
            default:
                AP_SYSTEM_CALL("echo USA > /tmp/cfg_country");
                break;
        }
    }
}

/******************************************************************************/
/**
 * @brief   This function get TV playing mode is 3D or non-3D
 *
 * @param
 * @retval  TRUE      Current is 3D mode playing
 * @retval  FALSE     Current is non-3D mode playing
 */
/******************************************************************************/
BOOL a_tv_custom_is_3D_mode_playing(VOID)
{
     BOOL                            b_is_3D_content = FALSE;
    INT16                           i2_mode_idx = 0;
    INT16                           i2_3d_to_2d_mode = 0;
    VSH_SRC_RESOLUTION_INFO_T       t_src_res = {0};
    BOOL                            b_is_3d_playing = FALSE;
    INT32       i4_ret = 0;

    HANDLE_T    h_svctx;
    CHAR            s_disp_name[SYS_NAME_LEN+1];

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        BOOL        b_3D_support = FALSE;
        i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
        DBG_INFO(("a_cfg_custom_plf_opt_get_3d_support : [%d]\n", i4_ret));

        if(i4_ret != TVR_OK || !b_3D_support)    /*not support 3D */
        {
            return FALSE;
        }
    }
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    DBG_INFO(("a_cfg_av_get_disp_name : [%d]\n", i4_ret));

    i4_ret = acfg_get_svctx(s_disp_name, &h_svctx);
    DBG_INFO(("acfg_get_svctx : [%d]\n", i4_ret));

    i4_ret = c_svctx_get_video_src_resolution(h_svctx, &t_src_res);
    DBG_INFO(("c_svctx_get_video_src_resolution : [%d]\n", i4_ret));

    if (t_src_res.ui4_height == 0 || t_src_res.ui4_width == 0)
    {
        return FALSE;
    }

    switch (t_src_res.e_src_tag3d_type)
    {
        case VSH_SRC_TAG3D_2D:
            b_is_3D_content = FALSE;
            //return MENUR_OK;
            break;
        case VSH_SRC_TAG3D_MVC:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_FS:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_FP:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_REALD:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_TB:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_SBS:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_SENSIO:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_TTDO:
        case VSH_SRC_TAG3D_NOT_SUPPORT:
        default:
            b_is_3D_content = FALSE;
            break;
    }


    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     &i2_mode_idx);
    DBG_INFO(("APP_CFG_RECID_VID_3D_MODE : [%d] [%d]\n", i4_ret, i2_mode_idx));
    i4_ret =  a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                 &i2_3d_to_2d_mode);
    DBG_INFO(("APP_CFG_RECID_VID_3D_TO_2D : [%d][%d]\n", i4_ret, i2_3d_to_2d_mode));


    DBG_INFO(("b_is_3D_content : [%d] \n", b_is_3D_content));
    if (!b_is_3D_content)
    {

        switch ((UINT16)i2_3d_to_2d_mode)
        {
            case APP_CFG_3D_TO_2D_OFF:
                {
                    switch ((UINT16)i2_mode_idx)
                    {
                        case APP_CFG_3D_MODE_SBS:
                        case APP_CFG_3D_MODE_TAB:
                        case APP_CFG_3D_MODE_SENSIO:
                            b_is_3d_playing = TRUE;
                            break;
                        default:
                            b_is_3d_playing = FALSE;
                            break;
                    }
                }
                break;
            default:
                b_is_3d_playing = FALSE;
                break;
        }

    }
    else
    {
        switch ((UINT16)i2_3d_to_2d_mode)
        {
            case APP_CFG_3D_TO_2D_OFF:
                b_is_3d_playing = TRUE;
                break;
            default:
                b_is_3d_playing = FALSE;
                break;
        }
    }
    return b_is_3d_playing;
}

#ifdef LINUX_TURNKEY_SOLUTION
/*-----------------------------------------------------------------------------
 * Name
 *      a_tv_custom_set_3rd_app_info
 * Description
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_tv_custom_set_3rd_app_info(VOID)
{
    CHAR s_tmp_buf[256] = {0};
    CHAR s_lang[3] = {0};
    ISO_639_LANG_T s639_lang;
    FILE *fl = fopen("/tmp/vizio_3rd_app_info.xml", "w");
    if (NULL == fl)
    {
        return TVR_FAIL;
    }

    a_cfg_get_gui_lang(s639_lang);
    if (0 == c_strncmp(s639_app_cfg_lang_eng, s639_lang, ISO_639_LANG_LEN))
    {
        /* language is en. */
        s_lang[0] = 'e';
        s_lang[1] = 'n';
        s_lang[2] = '\0';
    }
    else if (0 == c_strncmp(s639_app_cfg_lang_spa, s639_lang, ISO_639_LANG_LEN))
    {
        /* language is es. */
        s_lang[0] = 'e';
        s_lang[1] = 's';
        s_lang[2] = '\0';
    }
    else if (0 == c_strncmp(s639_app_cfg_lang_fre, s639_lang, ISO_639_LANG_LEN))
    {
        /* language is fr. */
        s_lang[0] = 'f';
        s_lang[1] = 'r';
        s_lang[2] = '\0';
    }

    c_snprintf(s_tmp_buf,
               256,
                "<?xml version=\"1.0\"?>\n<tvinfo>\n<Language>%s</Language>\n</tvinfo>",
               s_lang);

    fprintf(fl, "%s", s_tmp_buf);

    fclose(fl);

    return TVR_OK;
}
#endif

VOID a_tv_net_set_overscan_enable(BOOL b_overscan_enable)
{
#ifdef LINUX_TURNKEY_SOLUTION
    _g_b_overscan_enable = b_overscan_enable;
#endif
}
BOOL a_tv_net_get_overscan_enable(VOID)
{
#ifdef LINUX_TURNKEY_SOLUTION
    return _g_b_overscan_enable;
#else
    return TRUE;
#endif
}

INT32 a_tv_net_custom_set_codeset(CHAR* s_codeset)
{
    CHAR    s_cmd[128]        = {0};

    DBG_INFO(("[IR] --- set codeset in FUNC: %s.\n", __FUNCTION__));

    if (c_strcmp(s_codeset, "") != 0)
    {
        c_strncat(s_cmd, "\n:am,am,:codeset=", sizeof(s_cmd) - 1);
        c_strncat(s_cmd, s_codeset, sizeof(s_cmd) - 1);
        c_strncat(s_cmd, "\n", sizeof(s_cmd) - 1);
        a_tv_net_send_cmd(s_cmd);

        return TVR_OK;
    }
    else
    {
        return TVR_INV_ARG;
    }
}

VOID a_tv_net_custom_set_ir_mode(IR_MODE_E e_ir_mode)
{
    DBG_INFO(("[IR] --- set ir mode: %d in FUNC: %s.\n", e_ir_mode, __FUNCTION__));

    if (e_g_ir_mode == e_ir_mode)
    {
        return;
    }

    e_g_ir_mode = e_ir_mode;
    switch (e_ir_mode)
    {
    case IR_MODE_PD:
        a_tv_net_send_cmd("\n:am,am,:ir_mode=pd\n");
        break;
    case IR_MODE_3RD:
        a_tv_net_send_cmd("\n:am,am,:ir_mode=app\n");
        break;
    case IR_MODE_DOCK:
        a_tv_net_send_cmd("\n:am,am,:ir_mode=dock\n");
        break;
    case IR_MODE_MENU:
        a_tv_net_send_cmd("\n:am,am,:ir_mode=menu\n");
        break;
    default:
        a_tv_net_send_cmd("\n:am,am,:ir_mode=tv\n");
        break;
    }
}

VOID a_tv_net_custom_update_ir_mode(VOID)
{
    UINT8           ui1_val = APP_STATUS_LAST_ENTRY;
    UINT8           ui1_mw_status_val = 0;
    ISL_REC_T       t_isl_rec = {0};
    CHAR            s_type_name[32] = {0};
    CHAR            s_brand_name[32] = {0};
    CHAR            s_model_name[32] = {0};
    CHAR            s_codeset[6] = {0};
    BOOL            b_tv_or_pd_mode = FALSE;
    BOOL            b_is_signal_loss = FALSE;
    CHAR            s_app_name [APP_NAME_MAX_LEN+1] = {0};
    UINT8           ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;
    IR_MODE_E       e_ir_mode = IR_MODE_FAKE;

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
    if (ui1_status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
    {
        return;
    }

    DBG_INFO(("[IR] --- update ir mode in FUNC: %s.\n", __FUNCTION__));

    a_tv_get_crnt_isl_rec(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        a_tv_net_custom_set_ir_mode(IR_MODE_TV);
        return;
    }
    else if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        a_tv_net_custom_set_ir_mode(IR_MODE_TV);
        return;
    }

    a_cfg_custom_get_device_info(t_isl_rec.ui1_id, s_type_name, s_brand_name, s_model_name, s_codeset);
    if (c_strcmp(s_codeset, "") == 0)
    {
        a_tv_net_custom_set_ir_mode(IR_MODE_TV);
        return;
    }

    a_icl_get_app_status(&ui1_val);
    switch (ui1_val)
    {
        case APP_STATUS_MENU_NOT_WIDE_MODE:
        case APP_STATUS_MENU_WIDE_MODE:
        case APP_CFG_APP_STATUS_MMP_VIDEO_FULL_PLAY:
            e_ir_mode = IR_MODE_MENU;
            break;

        case APP_STATUS_YH_DOCK:
        case APP_STATUS_YH_SIDEBAR:
            a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_mw_status_val);
            if (ui1_mw_status_val == 1)
            {
                e_ir_mode = IR_MODE_DOCK;
            }
            else
            {
                e_ir_mode = IR_MODE_3RD;
            }
            break;

        default:
            b_tv_or_pd_mode = TRUE;
            break;
    }

    if (b_tv_or_pd_mode)
    {
        b_is_signal_loss = _tv_custom_is_signal_loss();

        a_am_get_active_app(s_app_name);

        if ((c_strcmp(s_app_name, NAV_NAME) == 0) &&
            (t_isl_rec.e_src_type == INP_SRC_TYPE_AV) &&
            (b_is_signal_loss == FALSE))
        {
            e_ir_mode = IR_MODE_PD;
        }
        else
        {
            e_ir_mode = IR_MODE_TV;
        }
    }

    a_tv_net_custom_set_ir_mode(e_ir_mode);
}

VOID a_tv_net_custom_set_soundbar_flag(BOOL b_enable)
{
    if (b_enable)
    {
        a_tv_net_send_cmd("\n:am,am,:sb_enable=true\n");
        DBG_INFO(("[IR] --- set soundbar enable in FUNC: %s.\n", __FUNCTION__));
    }
    else
    {
        a_tv_net_send_cmd("\n:am,am,:sb_enable=false\n");
        DBG_INFO(("[IR] --- set soundbar disable in FUNC: %s.\n", __FUNCTION__));
    }
}

INT32 a_tv_net_custom_set_soundbar_codeset(CHAR* s_codeset)
{
    CHAR    s_cmd[128]        = {0};

    DBG_INFO(("[IR] --- set soundbar codeset in FUNC: %s.\n", __FUNCTION__));

    if (c_strcmp(s_codeset, "") != 0)
    {
        c_strncat(s_cmd, "\n:am,am,:sb_codeset=", sizeof(s_cmd) - 1);
        c_strncat(s_cmd, s_codeset, sizeof(s_cmd) - 1);
        c_strncat(s_cmd, "\n", sizeof(s_cmd) - 1);
        a_tv_net_send_cmd(s_cmd);

        return TVR_OK;
    }
    else
    {
        return TVR_INV_ARG;
    }
}

#ifdef APP_TV_NET_CUSTOM_SET_OSD_STATUS
VOID a_tv_net_custom_set_OSD_status(UINT32  ui4_osd_status)
{
    /* store osd status */
    i4_g_osd_status = ui4_osd_status;

    if (a_cfg_custom_get_wifi_remote_support())
    {
        INT32               i4_ret = 0;
        UINT8               ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

        a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
        if (ui1_status == WIFI_REMOTE_PAIR_STATUS_PAIRED)
        {
            CHAR                s_type_name[32]   = {0};
            CHAR                s_brand_name[32]  = {0};
            CHAR                s_model_name[32]  = {0};
            CHAR                s_codeset[6]      = {0};
            ISL_REC_T           t_isl_rec         = {0};

            DBG_INFO(("[TV] --- set OSD status in FUNC: %s.\n", __FUNCTION__));
#if 0
            /* for Sound bar and AVR/Amplifer */
            UINT8   ui1_vol_ctrl_val = 0;
            a_cfg_custom_get_vol_control(&ui1_vol_ctrl_val);

            i4_ret = a_cfg_custom_get_device_info(0, s_type_name, s_brand_name, s_model_name, s_codeset);
            if (i4_ret != APP_CFGR_OK)
            {
                return;
            }
            if (c_strcmp(s_codeset, "") != 0 && ui1_vol_ctrl_val > 0)
            {
                a_tv_net_custom_set_soundbar_codeset(s_codeset);
                a_tv_net_custom_set_soundbar_flag(TRUE);
            }
            else
            {
                a_tv_net_custom_set_soundbar_flag(FALSE);
            }
#endif
            /* for cable box device */
            c_memset(s_type_name, 0 , 32);
            c_memset(s_brand_name, 0 , 32);
            c_memset(s_model_name, 0 , 32);
            c_memset(s_codeset, 0 , 6);

            a_tv_get_crnt_isl_rec(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            i4_ret = a_cfg_custom_get_device_info(t_isl_rec.ui1_id, s_type_name, s_brand_name, s_model_name, s_codeset);
            if (i4_ret != APP_CFGR_OK)
            {
                return;
            }

            if (c_strcmp(s_codeset, "") != 0)
            {
                a_tv_net_custom_set_codeset(s_codeset);
            }
            else
            {
                /* if current source unpaired device, set codeset C0105 and set ir mode to TV */
                a_tv_net_send_cmd("\n:am,am,:codeset=C0105\n");
                a_tv_net_custom_set_ir_mode(IR_MODE_TV);

                return;
            }

            /* update ir mode */
            if (a_cfg_get_app_status () != APP_CFG_APP_STATUS_LAST_ENTRY)
            {
                /* _tv_custom_icl_app_status_cb deal with this situation */
                DBG_INFO(("[IR] --- MENU or 3rd APP in FUNC: %s.\n", __FUNCTION__));
                return;
            }

            if (ui4_osd_status == 0)
            {
                DBG_INFO(("[IR] --- update ir mode in FUNC: %s.\n", __FUNCTION__));
                a_tv_net_custom_update_ir_mode();
            }
            else
            {
                DBG_INFO(("[IR] --- set ir mode force to TV mode in FUNC: %s.\n", __FUNCTION__));
                a_tv_net_custom_set_ir_mode(IR_MODE_TV);
            }
        }
    }
    return ;
}

INT32 a_tv_net_custom_get_OSD_status(VOID)
{
    return i4_g_osd_status;
}
#endif

#if defined(LINUX_TURNKEY_SOLUTION) && defined(TVIS_SUPPORT)
INT32 a_tv_custom_reload_tvis_wrapper(VOID)
{
    /********************************************************************/
    //hongzhao 2020/2/12 add for acr downloadable
    CHAR    target_path[64] = "/data/app/inscape";
    CHAR    link_path[64];
    CHAR    p_cmd_buf[256];
    if (-1 == readlink(target_path, link_path, sizeof(link_path)))
    {
        memset(target_path, 0, sizeof(target_path));
        c_sprintf(target_path, "%s", "/3rd/tvis/reload_tvis_wrapper.sh");
    }
    else
    {
        c_strcat(target_path, "/reload_tvis_wrapper.sh");
        DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
    }

    sprintf(p_cmd_buf,"sh %s",target_path);
    AP_SYSTEM_CALL(p_cmd_buf);
    /********************************************************************/

    return TVR_OK;
}
#endif

/* set info banner visiable allow flag */
BOOL a_tv_custom_get_banner_visiable_allow(VOID)
{
    return b_banner_allow_visiable;
}

VOID a_tv_custom_set_banner_visiable_allow(BOOL b_allow)
{
    b_banner_allow_visiable = b_allow;
}

INT32 a_tv_custom_set_tos_version(VOID)
{
    FILE*              pf = NULL;

    if(access("/data/tvis", F_OK))
    {
        AP_SYSTEM_CALL("mkdir /data/tvis;sync");
    }
    pf = fopen("/data/tvis/tos_version","wr");
    if(pf == NULL)
    {
        DBG_ERROR(("\n####%s(%d)The file /data/tvis/tos_version open fail !!\n",__FUNCTION__,__LINE__));
        return TVR_FAIL;
    }

    AP_SYSTEM_CALL("echo 105 > /data/tvis/tos_version; sync; sync; sync");

    fclose(pf);

    return TVR_OK;
}
#ifdef APP_IPCC_SUPPORT
#define IPCC_LINE_MAX   32
INT32 a_tv_net_get_ipcc_property(APP_TV_NET_IPCC_PROPERTY* pt_ipcc)
{
    CHAR   s_buf[IPCC_LINE_MAX+1];
    c_memset(s_buf, 0, sizeof(s_buf));

    if (pt_ipcc == NULL)
    {
        return AEER_INV_ARG;
    }

#ifdef LINUX_TURNKEY_SOLUTION
    FILE * fl = fopen("/tmp/3rd_property","r");
    if (fl == NULL)
    {
        return AEER_FAIL;
    }

    while(fgets(s_buf, IPCC_LINE_MAX, fl))
    {
        if(c_strncmp(s_buf, "CC=", 3) == 0)
        {
            pt_ipcc->b_running = ((c_strncmp(&s_buf[3], "SMPTE-TT", 8) == 0) ? TRUE : FALSE);
            break;
        }
    }
    fclose(fl);
#endif

    return AEER_OK;
}
#endif

VOID a_tv_custom_clear_tos_version(VOID)
{
    if ((0 == access("/data/tvis/tos_version", F_OK)))
    {
        AP_SYSTEM_CALL("rm /data/tvis/tos_version;sync");
    }
}

VOID a_tv_custom_set_hotkey_wakeup_active(WAKEUP_START_AP_STATUS e_ap_status)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    UINT8       ui1_status = 0;
    BOOL        b_is_AP_NONE = FALSE;

    a_tv_custom_get_hotkey_wakeup_active(&ui1_status);
    DBG_LOG_PRINT(("[HOTKEY]old=0x%x,set_type=%d.\n",ui1_status,e_ap_status));

    if (TV_HOTKEY_WAKEUP_START_AP_NONE == ui1_status)
    {
        b_is_AP_NONE = TRUE;
    }
    else if (ui1_status > (TV_HOTKEY_WAKEUP_START_AP_WZD | TV_HOTKEY_WAKEUP_START_AP_RETAILMODE) )
    {
        ui1_status = 0x0;   // invalid value ,reset
    }

    switch (e_ap_status)
    {
    case WAKEUP_AP_NONE:
        ui1_status = TV_HOTKEY_WAKEUP_START_AP_NONE;
        if (b_is_AP_NONE)
        {
            return; // donot need set again. SKIP
        }
        break;

    case WAKEUP_AP_RETAILMODE_SET:
        if ((ui1_status & TV_HOTKEY_WAKEUP_START_AP_RETAILMODE))
        {
            return;
        }
        else
        {
            ui1_status |= TV_HOTKEY_WAKEUP_START_AP_RETAILMODE;

        }
        break;

    case WAKEUP_AP_RETAILMODE_CLEAN:
        if ((ui1_status & TV_HOTKEY_WAKEUP_START_AP_RETAILMODE))
        {
            ui1_status &= ~TV_HOTKEY_WAKEUP_START_AP_RETAILMODE;
        }
        else
        {
            return;

        }

        break;

    case WAKEUP_AP_WZD_SET:
        if ((ui1_status & TV_HOTKEY_WAKEUP_START_AP_WZD))
        {
            return;
        }
        else
        {
            ui1_status |= TV_HOTKEY_WAKEUP_START_AP_WZD;

        }
        break;

    case WAKEUP_AP_WZD_CLEAN:
        ui1_status = TV_HOTKEY_WAKEUP_START_AP_NONE;
        break;

    default:
        break;
    }

    DBG_LOG_PRINT(("[HOTKEY]new status=0x%x.\n",ui1_status));
    a_cfg_custom_set_hotkey_wakeup_active(ui1_status);
#endif
}

VOID a_tv_custom_get_hotkey_wakeup_active(UINT8* pui1_ap_status)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT

    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = a_cfg_custom_get_hotkey_wakeup_active(pui1_ap_status);
    if (APP_CFGR_OK != i4_ret)
    {
        *pui1_ap_status = 0xFF;
    }
#endif
}

BOOL a_tv_custom_is_YAHOO_hotkey(UINT32 ui4_key_code)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT

    if (BTN_AMAZON == ui4_key_code
        || BTN_IHEART_RADIO == ui4_key_code)
    {
        return TRUE;
    }
#endif

    return FALSE;
}

VOID* _hotkey_wakeup_wait_4_network_ready(void* pv_data)
{
    NW_IP_INFO_T    t_net_ip_info;
    UINT8           ui1_count = 0;
#ifndef SYS_C4TV_SUPPORT
    HOTKEY_APP_LAUNCH_INFO*     pt_app_info = NULL;
#endif
    CHAR                        s_cmd[1024] = {0};
    UINT32                      ui4_key_code = (UINT32)pv_data;
    struct      timeval tv;
    struct      timezone tz;
    DTG_T       t_loc_dtg;
    INT64       sec;

    pthread_detach(pthread_self());

    c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));

    /* Wait for network connection ready*/
    do{

        ui1_count ++;

        c_memset(&t_loc_dtg, 0, sizeof(DTG_T));
        if ( (gettimeofday(&tv, &tz) == 0) && a_nw_custom_is_get_ip_addr() )
        {

            sec = (INT64)tv.tv_sec;
            c_dt_utc_sec_to_loc_dtg(sec, &t_loc_dtg);

            DBG_LOG_PRINT(("[HOTKEY]====[year,mon,day,hour,min] =[%d-%d-%d-%d-%d] .\n ",
                     t_loc_dtg.ui2_yr,
                     t_loc_dtg.ui1_mo,
                     t_loc_dtg.ui1_day,
                     t_loc_dtg.ui1_hr,
                     t_loc_dtg.ui1_min));

            if (((t_loc_dtg.ui2_yr == 0) && (t_loc_dtg.ui1_mo == 0)) ||
                (t_loc_dtg.ui2_yr == 1970))
            {
                DBG_LOG_PRINT(("\n [HOTKEY]=== Network-invalid.\n"));
            }
            else
            {
                DBG_LOG_PRINT(("\n [HOTKEY,is_get_ip=%d]=== Network-valid.\n",a_nw_custom_is_get_ip_addr()));

                break;
            }
        }
        sleep(1);
    }while( ui1_count < 24 );

    cmd_convert_send_cmd(":dtv_app_mtk,am,:started=dtv_app_mtk\n");

    return NULL;
}

VOID a_tv_custom_reset_hotkey_parameter()
{
    DBG_LOG_PRINT(("a_tv_custom_reset_hotkey_parameter \n"));
    PCL_WAKEUP_KEY_T t_wakeup_irkey = {0};
    t_hotkey_app_info.e_hotkey_app_type = HOTKEY_INVALID;
    t_hotkey_app_info.s_launch_args     = NULL;
    c_pcl_set_wakeup_irkey(&t_wakeup_irkey);
    return;
}

VOID a_tv_custom_hotkey_wakeup(UINT32 ui4_key_code)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    CHAR   s_cmd[1024] = {0};

#ifdef APP_TTS_SUPPORT
    {
        CHAR      s_app_name[APP_TV_CUSTOM_APP_NAME_MAX_LEN+1]       = {0};
        UTF16_T   w2s_app_name[APP_TV_CUSTOM_UTF_APP_NAME_MAX_LEN+1] = {0};

        UINT8      ui1_key_idx   = 0;

        c_thread_delay(100);
        switch (ui4_key_code)
        {
            case BTN_NETFLIX:
                ui1_key_idx = HOT_NETFLIX;
                break;

            case BTN_VUDU:
                ui1_key_idx = HOT_VUDU;
                break;

            case BTN_AMAZON:
                ui1_key_idx = HOT_AMAZON;
                break;

            case BTN_IHEART_RADIO:
                ui1_key_idx = HOT_IHEARTRADIO;
                break;
            case BTN_WATCHFREE:
                ui1_key_idx = HOT_WATCHFREE;
                break;
            case BTN_REDBOX:
                ui1_key_idx = HOT_REDBOX;
                break;
            case BTN_HAYSTACK:
                ui1_key_idx = HOT_HAYSTACK;
                break;

            case BTN_MGO:
                ui1_key_idx = HOT_MGO;
            break;
#ifdef BTN_XUMO
            case BTN_XUMO:
                ui1_key_idx = HOT_XUMO;
                break;
#endif
            default:
                ui1_key_idx = HOT_INVALID;
                break;
        }

        if( HOT_INVALID != ui1_key_idx )
        {
            c_strncat(s_app_name,ps_app_name[ui1_key_idx],APP_TV_CUSTOM_APP_NAME_MAX_LEN);
            c_strncat(s_app_name,APP_TV_CUSTOM_PROMPT_STRING,APP_TV_CUSTOM_APP_NAME_MAX_LEN);
            DBG_LOG_PRINT(("s_app_name=%s \n",s_app_name));
            c_uc_ps_to_w2s(s_app_name,w2s_app_name,APP_TV_CUSTOM_UTF_APP_NAME_MAX_LEN);
            a_app_tts_play(w2s_app_name,c_uc_w2s_strlen(w2s_app_name));
        }
    }
#endif

    if ( 0 == access("/data/upgrade/upgrade_integrity_ok.pkg", F_OK) )    /* upgrade */
    {
        c_pcl_set_hotkey_active(FALSE);     //inactive hotkey

        c_memset(s_cmd,0,64);
        c_sprintf(s_cmd, ":am,am,:hide_prompt_UI\n");
        cmd_convert_send_cmd(s_cmd);

        c_memset(s_cmd,0,64);
        c_sprintf(s_cmd, ":dtv_app_mtk,am,:hotkey=0x%x\n", BTN_POWER);
        cmd_convert_send_cmd(s_cmd);
        return ;
    }

    {
        int           ret = 0;
        pthread_t     h_thread = {0};

        ret = pthread_create(&h_thread,NULL,_hotkey_wakeup_wait_4_network_ready, (VOID*)ui4_key_code);
        if (ret != 0)
        {
            DBG_LOG_PRINT(("\n [HOTKEY] create thread error!  \n",__LINE__));
            c_memset(s_cmd,0,64);
            c_sprintf(s_cmd, ":am,am,:hide_prompt_UI\n");
            cmd_convert_send_cmd(s_cmd);

            c_memset(s_cmd,0,64);
            c_sprintf(s_cmd, ":dtv_app_mtk,am,:hotkey=0x%x\n", BTN_POWER);
            cmd_convert_send_cmd(s_cmd);
        }
        else
        {
            return;
        }
    }
    cmd_convert_send_cmd(":dtv_app_mtk,am,:started=dtv_app_mtk\n");

#endif
}

#ifdef APP_HOTKEY_WAKEUP_SUPPORT

static INT32 _get_hotkey_APP_xml_file(UINT32  ui4_key_code, CHAR*   ps_app_xml_path)
{

//    INT32           i4_ret = TVR_OK;
    struct dirent*  ptr = NULL;
    DIR*            dir = NULL;
    BOOL            b_find_app_xml = FALSE;
    CHAR*           s_keyword = NULL;
    UINT8           ui1_key_idx = 0;

    switch (ui4_key_code)
    {
    case BTN_NETFLIX:
        ui1_key_idx = HOT_NETFLIX;
        break;

    case BTN_VUDU:
        ui1_key_idx = HOT_VUDU;
        break;

    case BTN_AMAZON:
        ui1_key_idx = HOT_AMAZON;
        break;

    case BTN_IHEART_RADIO:
        ui1_key_idx = HOT_IHEARTRADIO;
        break;

    case BTN_MGO:
        ui1_key_idx = HOT_MGO;
        break;
    case BTN_WATCHFREE:
        ui1_key_idx = HOT_WATCHFREE;
        break;
    case BTN_REDBOX:
        ui1_key_idx = HOT_REDBOX;
        break;
    case BTN_HAYSTACK:
        ui1_key_idx = HOT_HAYSTACK;
        break;

    default:
        ui1_key_idx = HOT_INVALID;
        break;
    }

    s_keyword = s_hot_app_key[ui1_key_idx];

    /* Makesure 3rd_rw is available */
    if ((dir = opendir("/data")) == NULL)
    {
        return TVR_FAIL;
    }
    closedir(dir);
    dir = NULL;

    /* Makesure Yahoo XML DIR is available */
    if ((dir = opendir(YAHOO_XML_PATH)) == NULL)
    {
        return TVR_FAIL;
    }

    /* Loop read DIR to get HOTKEY APP's DIR */
    while ( NULL != (ptr = readdir(dir)) )
    {
        if (NULL != c_strstr(ptr->d_name, s_keyword)) /* Find hotkey APP keyword*/
        {
            b_find_app_xml = TRUE;

            snprintf(ps_app_xml_path,256,"%s/%s/%s",YAHOO_XML_PATH,ptr->d_name,"Contents/widget.xml");
            break;
        }
    }

    closedir(dir);
    dir = NULL;

    if ( !b_find_app_xml )
    {
        return TVR_FAIL;
    }
    return TVR_OK;
}

static INT32 _get_hotkey_APP_setting(CHAR*   ps_app_xml_path,CHAR*  ps_app_setting)
{
    INT32           i4_ret = TVR_OK;
    struct stat     st;
    CHAR*           s_begin = NULL;
    CHAR*           s_end = NULL;
    FILE*           fl = NULL;
    CHAR            s_xml_str[512] = {0};

    UINT8           ui1_len = 0;
    BOOL            b_muti_seg = FALSE;

    if(stat(ps_app_xml_path,&st) == 0)
    {
        DBG_INFO(("[HOKKEY] find APP xml file.\n"));
    }
    else
    {
        return TVR_FAIL;
    }

    fl = fopen(ps_app_xml_path,"r");
    if (NULL == fl)
    {
        return TVR_FAIL;
    }

    while( !feof(fl) )
    {
        c_memset(s_xml_str, 0 , 512);
        s_begin = NULL;
        s_end = NULL;

        if(fgets(s_xml_str,512,fl) == NULL)
        {
            i4_ret = TVR_FAIL;
            break;
        }

        if ((s_begin=c_strstr(s_xml_str, "<native-app-launch-string>")) != NULL)
        {
            s_end = c_strstr(s_xml_str, "</native-app-launch-string>");

            if (NULL == s_end)  /* maybe split into muti segements */
            {
                b_muti_seg = TRUE;

                c_memcpy(ps_app_setting, s_begin+c_strlen("<native-app-launch-string>"),(512-ui1_len));
                ui1_len = c_strlen(ps_app_setting);

                do
                {
                    while ((0x0d == ps_app_setting[ui1_len-1]) || (0x0a == ps_app_setting[ui1_len-1]))  /* CR-LF*/
                    {
                        ps_app_setting[ui1_len-1] = 0;
                        ui1_len --;
                    }

                    c_memset(s_xml_str, 0 , 512);
                    if(fgets(s_xml_str,512,fl) == NULL)
                    {
                        i4_ret = TVR_FAIL;
                        break;
                    }
#if 1
                    s_end = c_strstr(s_xml_str, "</native-app-launch-string>");
                    if (NULL == s_end)
                    {
                        c_memcpy(ps_app_setting+ui1_len, s_xml_str,(512-ui1_len));
                        ui1_len = c_strlen(ps_app_setting);
                    }
                    else
                    {
                        c_memcpy(ps_app_setting+ui1_len, s_xml_str,(s_end-s_xml_str));
                        ui1_len = c_strlen(ps_app_setting);

                        break; /* find END string*/
                    }
#endif
                }while(!feof(fl));

            }

        }

        if (b_muti_seg)
        {
            i4_ret = TVR_OK;
            break;
        }
        else if ((s_begin!=NULL && s_end!=NULL) &&
            (s_end>s_begin) &&
            (s_end-s_begin)<256)
        {
            c_memcpy(ps_app_setting, s_begin+c_strlen("<native-app-launch-string>"), (s_end-(s_begin+c_strlen("<native-app-launch-string>"))));

            i4_ret = TVR_OK;
            break;
        }

    }

    if (feof(fl))
    {
        i4_ret = TVR_FAIL;
    }

    fclose(fl);

    return i4_ret;
}

static void _parse_html5_app_args(CHAR*     s_buf,CHAR*     s_app_args)
{

    CHAR*           s_begin = NULL;
    CHAR*           s_end = NULL;
    CHAR            s_resolution[16] = {0};
    CHAR*           ps_x = NULL;
    CHAR            s_width[8] = {0};
    CHAR            s_height[8] = {0};

    CHAR            s_app_type[16] = {0};
    CHAR            s_URL[256] = {0};
    UINT8           ui1_cp_len = 0;

    /*resolution*/
    s_begin = c_strstr(s_buf,"&lt;SIZE=");
    if (NULL != s_begin)
    {
        s_end = c_strstr(s_begin,"&gt;");
    }

    if ((NULL != s_begin) && (NULL != s_end))
    {
        ui1_cp_len = (s_end - (s_begin+c_strlen("&lt;SIZE=")));
        if (ui1_cp_len > 16)
        {
            return ;
        }

        c_memcpy(s_resolution, s_begin+c_strlen("&lt;SIZE="), ui1_cp_len);
    }
    else
    {
    }

    /* width*/
    ps_x = c_strstr(s_resolution,"x");
    ui1_cp_len = (ps_x-s_resolution);
    if (ui1_cp_len > 8)
    {
        return ;
    }
    c_memcpy(s_width, s_resolution, ui1_cp_len);

    /* height*/
    ui1_cp_len = (c_strlen(s_resolution)-c_strlen(s_width)-1);
    if (ui1_cp_len > 8)
    {
        return ;
    }
    c_memcpy(s_height, ps_x+1, ui1_cp_len);

    /* APP-type */
    s_begin = c_strstr(s_buf,"&lt;APP=");
    if (NULL != s_begin)
    {
        s_end = c_strstr(s_begin,"&gt;");
    }

    if ((NULL != s_begin) && (NULL != s_end))
    {
        ui1_cp_len = (s_end - (s_begin+c_strlen("&lt;APP=")));
        if (ui1_cp_len > 16)
        {
            return ;
        }
        c_memcpy(s_app_type, s_begin+c_strlen("&lt;APP="), ui1_cp_len);
    }
    else
    {
    }

    /* URL */
    s_begin = c_strstr(s_buf,"&lt;URL=");
    if (NULL != s_begin)
    {
        s_end = c_strstr(s_begin,"&gt;");
    }

    if ((NULL != s_begin) && (NULL != s_end))
    {
        ui1_cp_len =  (s_end - (s_begin+c_strlen("&lt;URL=")));
        if (ui1_cp_len > 256)
        {
            return ;
        }
        c_memcpy(s_URL, s_begin+c_strlen("&lt;URL="), ui1_cp_len);
    }
    else
    {
    }

    if ( 0 == c_strcmp("AMAZON",s_app_type) )
    {
        //need remove this when clear amazon url!!
        snprintf(s_app_args, 1024,"-w %d -h %d -x %s -m NO -u https://atv-ext.amazon.com/blast-app-hosting/html5/index.html?deviceTypeID=A2UR2YSPXNPPBQ",atoi(s_width),atoi(s_height),"amazon");
    }
    else
    {
        snprintf(s_app_args, 1024,"-w %d -h %d -x %s -m NO -u %s",atoi(s_width),atoi(s_height),"redirect_app",s_URL);
    }

}
#endif

HOTKEY_APP_LAUNCH_INFO* a_tv_custom_get_APP_info_from_yahoo_XML(UINT32 ui4_key_code)
{

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    CHAR*           ps_app_xml_path = NULL;
    CHAR*           ps_app_setting = NULL;
    BOOL            b_get_info = FALSE;

    if (HOTKEY_INVALID != t_hotkey_app_info.e_hotkey_app_type)  /* APP has been parsed*/
    {
        return  &t_hotkey_app_info;
    }

    do
    {
        ps_app_xml_path = c_mem_alloc(256);
        if (NULL == ps_app_xml_path)
        {
            break;
        }

        ps_app_setting = c_mem_alloc(512);
        if (NULL == ps_app_setting)
        {
            break;
        }

        c_memset(ps_app_xml_path,0,sizeof(ps_app_xml_path));
        c_memset(ps_app_setting,0,sizeof(ps_app_setting));

        if (TVR_OK != _get_hotkey_APP_xml_file(ui4_key_code,ps_app_xml_path))
        {
            break;
        }

        if (TVR_OK != _get_hotkey_APP_setting(ps_app_xml_path,ps_app_setting))
        {
            break;
        }

        b_get_info = TRUE;

    }while(0);


    if (b_get_info)
    {
        if (NULL != c_strstr(ps_app_setting,"flash:"))
        {
            t_hotkey_app_info.e_hotkey_app_type = HOTKEY_NATIVE_APP;
        }
        else if (NULL != c_strstr(ps_app_setting,"TYPE=html5"))
        {
            t_hotkey_app_info.s_launch_args = c_mem_alloc(1024);
            c_memset( t_hotkey_app_info.s_launch_args, 0, sizeof(t_hotkey_app_info.s_launch_args));

            _parse_html5_app_args(ps_app_setting,t_hotkey_app_info.s_launch_args);
            t_hotkey_app_info.e_hotkey_app_type = HOTKEY_HTML5_APP;
        }
        else
        {
            t_hotkey_app_info.e_hotkey_app_type = HOTKEY_YAHOO_APP;
        }
    }
    else
    {
        t_hotkey_app_info.e_hotkey_app_type = HOTKEY_UNKNOWN_APP;
    }

    if (NULL != ps_app_xml_path)
    {
        c_mem_free(ps_app_xml_path);
        ps_app_xml_path = NULL;
    }

    if (NULL != ps_app_setting)
    {
        c_mem_free(ps_app_setting);
        ps_app_setting = NULL;
    }
    return &t_hotkey_app_info;
#else
    return NULL;
#endif

}

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
static VOID _send_hotkey_timer_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    UINT32      ui4_key_code = (UINT32)pv_tag;
    CHAR        s_cmd[64] = {0};

    if (!a_tv_custom_get_tos() || !a_tv_custom_get_privacy())
    {
        c_sprintf(s_cmd, ":dtv_app_mtk,dtv_app_mtk,hotkey:click=NETWORK\n");
    }
    else
    {
        if ( BTN_AMAZON == ui4_key_code)
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=AMAZON\n");
        }
        else if ( BTN_IHEART_RADIO == ui4_key_code)
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=IHEART_RADIO\n");
        }
        else if ( BTN_MGO == ui4_key_code)
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=MGO\n");
        }
        else if ( BTN_WATCHFREE == ui4_key_code)
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=watchfree\n");
        }
        else if ( BTN_REDBOX == ui4_key_code)
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=redbox\n");
        }
        else if ( BTN_HAYSTACK == ui4_key_code)
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=haystack\n");
        }
        else
        {
            c_sprintf(s_cmd, ":am,dtv_app_mtk,hotkey:click=WIDGET\n");
        }
    }
    cmd_convert_send_cmd(s_cmd);

    h_send_key_Q_timer = FALSE;
    if (NULL_HANDLE != h_send_key_Q_timer)
    {
        c_timer_stop(h_send_key_Q_timer);
        c_timer_delete(h_send_key_Q_timer);
        h_send_key_Q_timer = NULL_HANDLE;
    }
}

static VOID _prompt_UI_timer_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    CHAR        s_cmd[64] = {0};

    if (b_prompt_UI_timer_enable)
    {
        b_prompt_UI_timer_enable = FALSE;

        c_pcl_set_hotkey_active(FALSE);

        c_memset(s_cmd,0,sizeof(s_cmd));
        c_sprintf(s_cmd, ":dtv_app_mtk,dtv_app_mtk,:resume=navigator\n");
        cmd_convert_send_cmd(s_cmd);

        c_memset(s_cmd,0,sizeof(s_cmd));
        c_sprintf(s_cmd, ":am,am,:hide_prompt_UI\n");
        cmd_convert_send_cmd(s_cmd);

        a_tv_custom_set_yahoo_hotkey_timer(FALSE);

        a_tv_custom_start_send_hotkey_Q_timer(BTN_WIDGET);
    }
}
#endif

INT32 a_tv_custom_start_send_hotkey_Q_timer(UINT32 ui4_keycode)
{
    INT32       i4_ret = TVR_OK;

#ifdef APP_HOTKEY_WAKEUP_SUPPORT

    c_timer_create(&h_send_key_Q_timer);
    if (TVR_OK != i4_ret)
    {
        h_send_key_Q_timer = NULL_HANDLE;
    }

    if (h_send_key_Q_timer)
    {
        i4_ret=c_timer_start(h_send_key_Q_timer,
                            3000,
                            X_TIMER_FLAG_ONCE,
                            _send_hotkey_timer_fct,
                            (VOID*)ui4_keycode);
    }
#endif

    return i4_ret;

}

INT32 a_tv_custom_set_yahoo_hotkey_timer(BOOL      b_set_timer)
{
    INT32           i4_ret = TVR_OK;

#ifdef APP_HOTKEY_WAKEUP_SUPPORT

    if (b_set_timer)
    {
        if (NULL_HANDLE == h_prompt_UI_timer)
        {
            i4_ret = c_timer_create(&h_prompt_UI_timer);
            if (TVR_OK != i4_ret)
            {
                h_prompt_UI_timer = NULL_HANDLE;
            }
        }

        if (NULL_HANDLE != h_prompt_UI_timer)
        {
            b_prompt_UI_timer_enable = TRUE;

            i4_ret=c_timer_start(h_prompt_UI_timer,
                                30000,
                                X_TIMER_FLAG_ONCE,
                                _prompt_UI_timer_fct,
                                NULL);
            if (TVR_OK != i4_ret)
            {
                b_prompt_UI_timer_enable = FALSE;
            }
        }
    }
    else
    {
        b_prompt_UI_timer_enable = FALSE;
        if (NULL_HANDLE != h_prompt_UI_timer)
        {
            c_timer_stop(h_prompt_UI_timer);
            c_timer_delete(h_prompt_UI_timer);
            h_prompt_UI_timer = NULL_HANDLE;
        }
    }
#endif

    return i4_ret;
}

BOOL a_tv_custom_get_yahoo_hotkey_timer(VOID)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    return b_prompt_UI_timer_enable;
#else
    return FALSE;
#endif
}

BOOL a_tv_custom_is_3rd_rw_ready(VOID)
{
    /* 3rd_rw should always ready before tos download */
    return TRUE;
}

INT32 a_tv_custom_launch_retail_mode_by_hotkey(VOID)
{
#ifdef APP_RETAIL_MODE_SUPPORT
    INT32           i4_ret = TVR_OK;
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_HOME;

    DBG_LOG_PRINT(("[HOTKEY] [%s][%d] recv RETAIL MODE key \n", __FUNCTION__, __LINE__));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        DBG_LOG_PRINT(("[HOTKEY] [%s][%d] current in retail mode \n",__FUNCTION__, __LINE__));
        return TVR_OK;
    }

    a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);

    RETAIL_MODE_PARAM_T t_param;
    c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_HOTKEY;
    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
    t_param.t_launch_info.ui2_count = 15;

    i4_ret = a_nav_retail_mode_start(&t_param);
    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[HOTKEY] [%s] a_nav_retail_mode start failed. ret: %d \n", __FUNCTION__, i4_ret));
        return TVR_FAIL;
    }
#endif

    return TVR_OK;
}

INT32 a_tv_custom_launch_link_by_hotkey(VOID)
{
    INT32 i4_ret = TVR_OK;
    i4_ret = a_amb_default_key_handler (WGL_MSG_KEY_DOWN,(VOID*) (BTN_LINK),NULL);
    if (AMBR_OK != i4_ret)
    {
        DBG_ERROR(("[HOTKEY] launch link mode ERROR @LINE: %d.\n", __LINE__));
    }
    DBG_LOG_PRINT(("[HOTKEY] a_tv_custom_launch_link_by_hotkey. file:%s,LINE: %d \n", __FILE__,__LINE__));
    return TVR_OK;
}
INT32 a_tv_custom_launch_input_and_voldown_hotkey(VOID)
{
    INT32 i4_ret = TVR_OK;
    i4_ret = a_amb_default_key_handler (WGL_MSG_KEY_DOWN,(VOID*) (BTN_LONG_INPUT_VOL_DOWN),NULL);
    if (AMBR_OK != i4_ret)
    {
        DBG_ERROR(("[HOTKEY] launch input and vol_down ERROR @LINE: %d.\n", __LINE__));
    }
    DBG_LOG_PRINT(("[HOTKEY] a_tv_custom_launch_input_and_voldown_hotkey. file:%s,LINE: %d \n", __FILE__,__LINE__));
    return TVR_OK;
}
INT32 a_tv_rest_version(CHAR * restVerStr)
{
    return a_rest_get_Rest_Version(restVerStr);
}

INT32 a_tv_exit_oobe(VOID)
{
    return a_rest_app_cancel_oobe();
}
static INT32 _app_tv_get_mi_flash_handle_and_type(MI_HANDLE* phFlash, MI_FLASH_Type_e* peFlashType)
{
    MI_FLASH_Type_e              eType          = E_MI_FLASH_TYPE_SPI;
    MI_FLASH_QueryHandleParams_t stQueryParams;
    MI_FLASH_OpenParams_t        stOpenParams;

    INT32 i4_ret = TVR_OK;

    if (phFlash == NULL)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> invalid argument\n", __FILE__, __LINE__));
        return TVR_INV_HANDLE;
    }

    i4_ret = MI_FLASH_GetAttr(MI_HANDLE_NULL, E_MI_FLASH_ATTR_TYPE_ENV_LOCATION, NULL, (void *)&eType);
    if (i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> get MI flash type failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
        return TVR_FAIL;
    }

    if (peFlashType != NULL)
    {
        *peFlashType = eType;
    }

    c_memset(&stQueryParams, 0, sizeof(MI_FLASH_QueryHandleParams_t));
    stQueryParams.eType = eType;
    i4_ret = MI_FLASH_GetHandle(&stQueryParams, phFlash);
    if (i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> get MI flash handle failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));

        c_memset(&stOpenParams, 0, sizeof(MI_FLASH_OpenParams_t));
        stOpenParams.eType = eType;
        i4_ret = MI_FLASH_Open(&stOpenParams, phFlash);
        if (i4_ret != TVR_OK)
        {
            DBG_LOG_PRINT(("[TVAPI] <%s:%4d> open MI flash handle failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
            return TVR_FAIL;
        }
    }

    return TVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: a_tv_set_env_to_mpool
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_tv_set_env_to_mpool(CHAR* ps_name, CHAR* ps_value)
{
    INT32 i4_ret = TVR_OK;

    MI_HANDLE                    hFlash         = MI_HANDLE_NULL;
    MI_FLASH_EnvInfo_t*          pstEnvInfo     = NULL;
    MI_FLASH_SetEnvVar_t         stSetEnvParams;

    if (ps_name == NULL || ps_value == NULL || c_strlen(ps_name) == 0)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> invalid argument\n", __FILE__, __LINE__));
        return NAVR_INV_ARG;
    }

    c_memset(&stSetEnvParams, 0, sizeof(MI_FLASH_SetEnvVar_t));
    stSetEnvParams.pstCurEnv = pstEnvInfo;
    stSetEnvParams.pszName   = (MI_U8*) ps_name;
    stSetEnvParams.pszValue  = (MI_U8*) ps_value;

    i4_ret = _app_tv_get_mi_flash_handle_and_type(&hFlash, NULL);
    if (i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> get flash handle failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
        return TVR_FAIL;
    }

    pstEnvInfo = (MI_FLASH_EnvInfo_t*)c_mem_alloc(sizeof(MI_FLASH_EnvInfo_t));
    if (pstEnvInfo == NULL)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> allocate memory failed\n", __FILE__, __LINE__));
        return NAVR_OUT_OF_MEM;
    }
    c_memset(pstEnvInfo, 0, sizeof(MI_FLASH_EnvInfo_t));
    i4_ret = MI_FLASH_LoadEnv(hFlash, pstEnvInfo);
    if (i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> load current env data failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
        i4_ret = TVR_FAIL;
        goto THE_END;
    }

    stSetEnvParams.pstCurEnv = pstEnvInfo;
    i4_ret = MI_FLASH_SetEnvVar(hFlash, &stSetEnvParams);
    if (i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> set new env failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
        i4_ret = TVR_FAIL;
        goto THE_END;
    }

    i4_ret = MI_FLASH_StoreEnv(hFlash, pstEnvInfo);
    if (i4_ret != TVR_OK)
    {
        DBG_LOG_PRINT(("[TVAPI] <%s:%4d> store env failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
        i4_ret = TVR_FAIL;
        goto THE_END;
    }

THE_END:
    if (pstEnvInfo != NULL)
    {
        c_mem_free(pstEnvInfo);
        pstEnvInfo = NULL;
    }

    /*  No close mi flash handle is intentional */

    return i4_ret;
}


#define PARSE_DBG_FILE_LINE_BUF_LEN   256

int AppTV_ParseDgbFile( char* pcFullFileName, TypParseFileSetVar* pFuncParseFileSetVar )
{
    FILE* pfIn = fopen(pcFullFileName, "r");

    if(pfIn == NULL)
    {
        DBG_LOG_PRINT(("\n\nError: Open file(%s) failed\n\n", pcFullFileName));
        return -1;
    }

    char acLineBuf[PARSE_DBG_FILE_LINE_BUF_LEN] = {0};
    int iLineNO = 0;
    int iStrLen = 0;
    char cLast = 0;

    char acVarName[64] = {0};
    char acVar_Val[16] = {0};
    //int iVarVal;
    unsigned int uiVal;

    while( iLineNO < 100 )
    {
        if( NULL == fgets(acLineBuf, PARSE_DBG_FILE_LINE_BUF_LEN, pfIn) )
        {
            break;
        }

        iLineNO += 1;

        iStrLen = strlen(acLineBuf);
        if(iStrLen)
        {
            cLast = acLineBuf[iStrLen-1];
            if(cLast=='\n')
            {
                acLineBuf[iStrLen-1]=0;
                iStrLen = strlen(acLineBuf);
            }
        }

        //DBG_LOG_PRINT(("(%d) len=%d, [%s]\n", iLineNO, iStrLen, acLineBuf));

        if( iStrLen == 0 )
            continue;

        //int iParaNum = sscanf( acLineBuf, "%127s %u", acVarName, &uiVal);
        int iParaNum = sscanf( acLineBuf, "%63s %15s", acVarName, acVar_Val);
        //printf("iParaNum=%d\n", iParaNum);

        if( iParaNum == 2 )
        {
            //DBG_LOG_PRINT(("=> iParaNum=%d,  VarName:%s, acVar_Val:%s\n", iParaNum, acVarName, acVar_Val));

            // Convert acVar_Val to UINT32
            if( (acVar_Val[0] == '0') && (acVar_Val[1] == 'x') )
            {
                sscanf(acVar_Val, "0x%X", &uiVal);
                //DBG_LOG_PRINT(("==> uiVal: 0x%x\n", uiVal));
            }
            else
            {
                sscanf(acVar_Val, "%u", &uiVal);
                //DBG_LOG_PRINT(("==> uiVal: %d\n", uiVal));
            }

            if(pFuncParseFileSetVar)
            {
                pFuncParseFileSetVar(acVarName, uiVal);
            }
        }
        else
        {
            //DBG_LOG_PRINT(("=> iParaNum=%d\n", iParaNum));
        }
        //printf("\n");
    }

    fclose(pfIn);
    return 0;
}

void a_tv_custom_pause( const char* pcStr, int iNum )
{
    const char* pcPauseName = "Unknown";

    if(pcStr)
    {
        pcPauseName = pcStr;
    }

    printf("\n\nPause(%s, %d) - start\n", pcPauseName, iNum);

    char  acCmdBuf[128] = {0};
    char* pc_debug_folder  = "/data/pause";
    //char* pc_debug_folder  = "./menu_debug";

    // create folder for debug...
    sprintf(acCmdBuf, "mkdir -p %s", pc_debug_folder);
    printf("acCmdBuf=[%s]\n", acCmdBuf);
    int iSysCallRtn = system(acCmdBuf);
    if( 0 != iSysCallRtn )
    {
        printf("system(%s) fail => %d\n", acCmdBuf, iSysCallRtn );
        return;
    }

    // Create file ...
    char acFilePath[128] = {0};
    sprintf(acFilePath, "%s/pause_%s_%d", pc_debug_folder, pcPauseName, iNum);
    printf("acFilePath=[%s]\n", acFilePath);

    sprintf(acCmdBuf, "echo 1 > %s", acFilePath);
    printf("acCmdBuf=[%s]\n", acCmdBuf);

    iSysCallRtn = system(acCmdBuf);
    if( 0 != iSysCallRtn )
    {
        printf("system(%s) fail => %d\n", acCmdBuf, iSysCallRtn );
        return;
    }

    // Check file should exist...
    if( access(acFilePath, F_OK) == 0 )
    {
        printf("File(%s) created\n", acFilePath);
    }
    else
    {
        printf("File(%s) created failed!\n", acFilePath);
        return;
    }

    // Wait file delete ...
    printf("=> Wait file delete => %s\n", acFilePath);

    int iTime = 0;
    while(1)
    {
        sleep(2);
        if( access(acFilePath, F_OK) == 0 )
        {
            //printf("File(%s) is exist\n", acFilePath);
        }
        else
        {
            break;
        }

        iTime += 1;

        if( iTime >= 5 )
        {
            printf("File(%s) is exist\n", acFilePath);
            iTime = 0;
        }
    }

    printf("\n==> Pause(%s, %d) - end\n", pcPauseName, iNum);
}



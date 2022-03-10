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
 * $RCSfile: menu_page_log_to_usb,v $
 * $Revision: #1 $
 * $Date: 2015/06/18 $
 * $Author: jg_wenchengzhang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

#ifdef APP_LOG2USB_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
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
#include "c_tsl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "app_util/a_cfg.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/rmv_dev/a_rmv_evt.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"


typedef struct _PAGE_LOG2USB_HIDE_T
{
    HANDLE_T    h_cnt_frm;
    HANDLE_T    h_log2usb;
    HANDLE_T    h_signal_lvl_dlg;
    HANDLE_T    h_usb_start_dlg;
    HANDLE_T    h_signal_lvl_timer;
    HANDLE_T    h_rmv_dev_nfy;

    BOOL        b_enable_log2usb;
}PAGE_LOG2USB_HIDE_T;

#define  BUF_SIZE              (1024)
#define  LOG_TO_USB_SWITCH_OFF ((UINT8) 0)
#define  LOG_TO_USB_SWITCH_ON  ((UINT8) 1)
#define  L2U_ON "kill -s 10 `/openbox/bin/ps -ef | grep log2usb | grep -v grep | awk '{print $2}'`"
#define  L2U_OFF "kill -s 12 `/openbox/bin/ps -ef | grep log2usb | grep -v grep | awk '{print $2}'`"
#define  LOGCAT_OFF "kill `/openbox/bin/ps -ef | grep logcat | grep -v grep | awk '{print $2}'`"
#define  DIALOG_START    (0)
#define  DIALOG_WARNNING (1)
#define  DELAY_TIME  ((UINT32) 500) /* 500ms */
#define  DELAY_COUNT ((INT32) 30)

#define DBG_LOG  0

#define LOG_FOLDER "__log2usb"

/*data declaration*/
MENU_PAGE_FCT_TBL_T             t_g_menu_common_log_to_usb;
static PAGE_LOG2USB_HIDE_T      t_page_log_to_usb_hide;
static CHAR s_log_path[BUF_SIZE]       =  "/tmp/l2u_usb_touch_file";
static CHAR s_enable_file[BUF_SIZE]    =  {0};
static CHAR s_seq_file[BUF_SIZE]       =  "seq.txt";
static CHAR s_usb_file_path[BUF_SIZE]  =  "default";
static INT32 i4_current_count          =  0;
static INT32 _log_to_usb_refresh(VOID);
static INT32 _log_to_usb_is_enable_log2usb(BOOL *enable_log2usb);
static INT32 _log_to_usb_create_file_path(VOID);

/*----------------------------------------------------------------------------
 * Name: _log_to_usb_check_enable_log2usb
 *
 * Description:
 *      check is enable log2usb or not.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static VOID _log_to_usb_check_enable_log2usb(VOID)
{
    INT32                    i4_ret           = MENUR_OK;
    PAGE_LOG2USB_HIDE_T*     pt_page_data     = &t_page_log_to_usb_hide;
    BOOL                     b_enable_log2usb = FALSE;

    i4_ret = _log_to_usb_is_enable_log2usb(&b_enable_log2usb);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_enable_log2usb = b_enable_log2usb;
    /* self_add the count */
    i4_current_count ++;

#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, is enable log2usb?,b_enable_log2usb:%d,current_count:%d.\n",
                       __func__, b_enable_log2usb, i4_current_count));
#endif

    /*if log2usb enable or time out(30*500ms = 15s), stop the timer */
    if (pt_page_data->b_enable_log2usb || (i4_current_count > DELAY_COUNT))
    {
        /* reset the count */
        i4_current_count = 0;
        /* stop repeat timer */
        i4_ret = c_timer_stop(pt_page_data->h_signal_lvl_timer);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if (pt_page_data->b_enable_log2usb)
    {
        #if 0
        char cmd[100] = {0};
        DBG_LOG_PRINT(("[LOG2USB] %s, stop logging client and enable log2usb.\n", __func__));

        c_snprintf(cmd, 100, "kill -9 `ps | grep %s | awk \'{print $1}\'`", "S3Logging");
        system(cmd);
        system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib kill -9 `/linux_rootfs/bin/ps -Af |grep LoggingClient | awk '{print $2;}'`");
        #endif

        /* create the path file of save the log */
        i4_ret = _log_to_usb_create_file_path();

        if (MENUR_OK == i4_ret)
        {
            /* send message to process */
            //system(L2U_ON);
        }
    }

    return ;
}
#ifdef MT5695_MODEL
static INT32 _usb_get_root_path(
    CHAR*   s_path,
    SIZE_T  z_size);


static VOID _log_to_usb_clean_oled_error_count(VOID)
{
    INT32   i4_ret = 0;
    CHAR    s_usb_path[BUF_SIZE]  = {'\0'};
    CHAR 	s_file_path[128] = {0};
    UINT8	ui1_val = 0;

    if (MENUR_OK != a_cfg_custom_get_oled_error_detect_count(&ui1_val))
    {
        return;
    }
    if(ui1_val < 3)
    {
        return;
    }

    i4_ret = _usb_get_root_path(s_usb_path, sizeof(s_usb_path));
    if (MENUR_OK != i4_ret)
    {
        return;
    }

    c_snprintf(s_file_path, 128, "%s/PanelUnlock", s_usb_path);

    DBG_LOG_PRINT(("[LOG2USB] check file:%s\n",s_file_path));

    if (access(s_file_path, F_OK) == 0) 
    {
        //file exist
        {
            //clean oled err count
            //clean oled err count
            a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
	        a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_ECO);  //just set to eco then reboot
            i4_ret = a_cfg_custom_set_oled_error_detect_count(0);
            i4_ret = a_tv_set_env_to_mpool("oled_block", "0");
            a_cfg_store();
            AP_SYSTEM_CALL("sync");
            AP_SYSTEM_CALL("sync");
            DBG_LOG_PRINT(("OLED PanelUnlock done TV will reboot \n"));
            AP_SYSTEM_CALL("reboot");

            return;
        }
    }

    return ;
}
#endif

static VOID _log_to_usb_signal_level(VOID* pv_data,
                                       SIZE_T  z_data_size)
{
    _log_to_usb_check_enable_log2usb();
#ifdef MT5695_MODEL
    _log_to_usb_clean_oled_error_count();
#endif
}

/*----------------------------------------------------------------------------
 * Name: _timer_signal_nfy_fct
 *
 * Description:
 *      async invoke the fuction.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static VOID _timer_signal_nfy_fct(HANDLE_T h_timer,
                                  VOID* pv_tag)
{
    menu_async_invoke(_log_to_usb_signal_level, NULL, 0, FALSE);
}
/*----------------------------------------------------------------------------
 * Name: _usb_get_root_path
 *
 * Description: get the usb path
 *
 * Inputs:
 *
 * Outputs: s_path
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _usb_get_root_path(
    CHAR*   s_path,
    SIZE_T  z_size)
{
    INT32   i4_ret= -1;
    UINT32  ui4_mnt_count = 0;
    UINT32  ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;

    a_rmv_dev_lock();

    i4_ret = a_rmv_dev_get_mnt_count (& ui4_mnt_count);
    if (i4_ret != RMVR_OK)
    {
        DBG_LOG_PRINT(("[LOG2USB] %s, No usb disk found, Line:%d.\n", __func__, __LINE__));
        a_rmv_dev_unlock();
        return -1;
    }

    if (ui4_mnt_count == 0)
    {
        DBG_LOG_PRINT(("[LOG2USB] %s, No usb disk found, Line:%d.\n", __func__, __LINE__));
        a_rmv_dev_unlock();
        return -1;
    }

    for(ui4_mnt_point_idx = 0;
        ui4_mnt_point_idx < ui4_mnt_count;
        ui4_mnt_point_idx ++)
    {
        /* Get the mount point status */
        i4_ret= a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx,
                                                          &t_rmv_dev_status);

        if (i4_ret != RMVR_OK)
        {
            continue;
        }

        /* Check the mount point status */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(t_rmv_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(t_rmv_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(t_rmv_dev_status)))
        {
            continue;
        }

        i4_ret = a_rmv_dev_get_mnt_point(ui4_mnt_point_idx,
                                 &z_size,
                                 s_path);
        break;

    }

    a_rmv_dev_unlock();

    DBG_INFO(("\n<log2usb, %d, %s, %s>: Find USB Device:path:%s!\n\r", __LINE__, __func__, __FILE__, s_path));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _get_usb_count
 *
 * Description: get count number of usb
 *
 * Inputs:
 *
 * Outputs: s_path
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT32 _get_usb_count()
{
    INT32   i4_ret            = -1;
    UINT32  ui4_mnt_count     = 0;
    UINT32  ui4_usb_dev_count = 0;
    UINT32  ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;

    /* get counts of mount devices (USB removable device, wifi module, DLNA dms...) */
    i4_ret = a_rmv_dev_get_mnt_count (& ui4_mnt_count);
    if (i4_ret != RMVR_OK)
    {
        DBG_LOG_PRINT(("[LOG2USB] %s, No removable device found.i4_ret:%d != RMVR_OK \n", __func__, i4_ret));
        return 0;
    }

    if (ui4_mnt_count == 0)
    {
        DBG_LOG_PRINT(("[LOG2USB] %s, No removable device found.ui4_mnt_count == 0\n", __func__));
        return 0;
    }

    for (ui4_mnt_point_idx = 0;
         ui4_mnt_point_idx < ui4_mnt_count;
         ui4_mnt_point_idx ++)
    {
        /* get information of each device */
        a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx, &e_dev_status);

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
        {
            continue;
        }

        /* if the device is USB removable device, count++ */
        if( e_dev_status == RMV_DEV_DEVICE_STATUS_EMPTY )
        {
            ui4_usb_dev_count ++;
        }

    }
    return ui4_usb_dev_count;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_pld_module_leave
 * Description:
 *
 * Input arguments:
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _log_to_usb_pld_module_leave()
{
    PAGE_LOG2USB_HIDE_T*    pt_page_data = &t_page_log_to_usb_hide;
    BOOL                    b_file_exist = FALSE;

    b_file_exist = (access(s_usb_file_path, F_OK) == 0 ? TRUE : FALSE);
#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, have a usb pop,s_path:%s.\n", __func__, s_usb_file_path));
#endif

    if (FALSE == b_file_exist)
    {
        if (pt_page_data->b_enable_log2usb)
        {
            /* disable the log2usb */
            pt_page_data->b_enable_log2usb = FALSE;
            if(access("/bin/log2usb.sh", F_OK) == 0)
            {
                UINT8 ui1_log_level = 0;
                AP_SYSTEM_CALL("/bin/log2usb.sh stop");
                DBG_LOG_PRINT(("[LOG2USB] %s, usb is exsit ,cmd === /bin/log2usb.sh stop .\r\n", __func__));
                a_cfg_cust_get_log_level(&ui1_log_level);
                a_cfg_cust_set_log_level(ui1_log_level);
            }
            DBG_LOG_PRINT(("[LOG2USB] %s, usb is not exsit ,turn off switch.\n", __func__));
        }
    }
    else
    {
        /* the usb path is exsit, do noting */
    }

#if 0
    c_snprintf(cmd, sizeof(cmd), "ls -l %s", s_usb_file_path);
    i4_status = system(cmd);

    /* fork error */
    if (-1 == i4_status)
    {
        /* do noting*/
        return;
    }
    else
    {
        if ( WIFEXITED(i4_status) )
        {
            if ( 0 == WEXITSTATUS(i4_status) )
            {
                /* the usb path is exsit, do noting */
                c_dbg_stmt("[LOG2USB] usb is exsit ,do noting.\n");
                return;
            }
            /* if the usb path is not exsit*/
            else
            {

                #if 0
                /* turn off the switch */
                menu_list_set_idx(pt_page_data->h_log2usb,
                             (UINT16)0);
                /* repaint */
                c_wgl_repaint(pt_page_data->h_log2usb, NULL, TRUE);

                /* set to acfg */
                _set_log_to_usb_status(LOG_TO_USB_SWITCH_OFF);
                #endif

                if (pt_page_data->b_enable_log2usb)
                {
                    /* disable the log2usb */
                    pt_page_data->b_enable_log2usb = FALSE;

                    /* send message to process */
                    system(L2U_OFF);
                    /* rm the log_path file */
                    c_snprintf(cmd, sizeof(cmd), "rm -f %s",  s_log_path);
                    system(cmd);
                    c_dbg_stmt("[LOG2USB] usb is not exsit ,turn off switch.\n");

                }
                c_dbg_stmt("[LOG2USB] pt_page_data->b_enable_log2usb is false.\n");

            }

        }

    }
#endif /* if 0 */

}

/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_pld_rmv_dev_nfy_handler
 * Description:
 *
 * Input arguments:
 *      pv_data
 *      z_data_size
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _log_to_usb_pld_rmv_dev_nfy_handler(
                    VOID*        pv_data,
                    SIZE_T       z_data_size)
{
    if (*(RMV_DEV_NFY_ID_T *)pv_data == RMV_DEV_NFY_ID_DEVICE_REMOVED)
    {
        /* go to the module leave */
        _log_to_usb_pld_module_leave();
        AP_SYSTEM_CALL(LOGCAT_OFF);
    }
    else if (*(RMV_DEV_NFY_ID_T *)pv_data == RMV_DEV_NFY_ID_DEVICE_INSERTED)
    {
        if (_get_usb_count() > 0)
        {
            /* do refesh when there is a USB inserted */
            MENU_LOG_ON_FAIL( _log_to_usb_refresh() );
        }
    }
    else
    {
        /* do nothing */
    }
    AP_SYSTEM_CALL("sync");
    return;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_pld_rmv_dev_nfy
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _log_to_usb_pld_rmv_dev_nfy(
                    VOID*               pv_tag,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param)
{

    if ((RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id) || (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id))
    {
        if (pv_nfy_param != NULL)
        {
            RMV_DEV_NFY_REC_T t_usb_info;
            c_memset (&t_usb_info, 0, sizeof(RMV_DEV_NFY_REC_T));
            c_memcpy (&t_usb_info,(RMV_DEV_NFY_REC_T*)(UINT32)pv_nfy_param,
                        sizeof(RMV_DEV_NFY_REC_T));

            if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(t_usb_info.e_status))||
                (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(t_usb_info.e_status))||
                (TRUE == RMV_DEV_DEVICE_IS_REMOVED(t_usb_info.e_status))||
                (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(t_usb_info.e_status)))
            {
                return;
            }

            /* if the device is not USB removable device, return */
            if(RMV_DEV_DEVICE_STATUS_EMPTY != t_usb_info.e_status)
            {
                return;
            }

        }

        DBG_LOG_PRINT(("[LOG2USB] %s, USB device insert/remove.\n", __func__));
        /* switch to the menu thread */
        menu_async_invoke(
                    _log_to_usb_pld_rmv_dev_nfy_handler,
                    (void *)&e_nfy_id,
                    sizeof(RMV_DEV_NFY_ID_T),
                    FALSE);

    }

    return;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _log_to_usb_is_enable_network
 * Description
       The API is used to is enable network
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _log_to_usb_is_enable_network (VOID)
{
    INT32                       i4_ret = MENUR_OK;
    BOOL                        b_is_plug = FALSE;
    BOOL                        b_is_ip_get = FALSE;
    NW_WLAN_STATE_T             e_wlan_state;
    time_t                      t_time;
    struct  tm                  *pt_local_time    = NULL;
    INT32                       i4_current_year   = 2015;


    /* get the current local time */
    time(&t_time);
    pt_local_time = localtime(&t_time);
#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, local_time->tm_year + 1900:%d\n", __func__, pt_local_time->tm_year + 1900));
#endif

    /* if get the year below current year, consider the network as diable */
    if ((pt_local_time->tm_year + 1900) < i4_current_year)
    {
        return FALSE;
    }

    a_nw_get_ethernet_connect_info(&b_is_plug);
#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, b_is_plug:%d\n", __func__, b_is_plug));
#endif

    if (b_is_plug)
    {
        return TRUE;
    }

    i4_ret = a_nw_wlan_status(&e_wlan_state);
#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, e_wlan_state:%d,i4_ret:%d\n", __func__, e_wlan_state, i4_ret));
#endif

    if (NWR_OK != i4_ret)
    {
        return FALSE;
    }

    b_is_ip_get = a_nw_custom_is_get_ip_addr();
#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, b_is_ip_get:%d,\n", __func__, b_is_ip_get));
#endif

    /* has associate with wifi */
    if (e_wlan_state == NW_WLAN_ASSOCIATE && b_is_ip_get)
    {
        return TRUE;
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_is_enable_log2usb
 * Description:
 *      The API is check the "s_enable_file" file is or not exsit.
 * Input arguments:
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _log_to_usb_is_enable_log2usb(BOOL *pb_enable_log2usb)
{
    BOOL    b_file_exist = FALSE;
    BOOL    b_bin_file_exist = FALSE;
	
    INT32   i4_ret = 0;
    CHAR    s_usb_path[BUF_SIZE]  = {'\0'};

    i4_ret = _usb_get_root_path(s_usb_path, sizeof(s_usb_path));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    #ifdef APP_LOG2USB_SUPPORT
    {
        CHAR s_auto_test_script[128] = {0};
        CHAR s_auto_test_cmd[256] = {0};
        static CHAR s_last_test_script[128] = {0};

        c_snprintf(s_auto_test_script, 128, "%s/vizio_auto_test_script.sh", s_usb_path);
        if (access(s_auto_test_script, F_OK) == 0) {
            if(strncmp(s_last_test_script, s_auto_test_script,strlen(s_auto_test_script)) == 0) {
                DBG_LOG_PRINT(("[LOG2USB] %s, same script[%s], bypass\n", __func__, s_auto_test_script));
            } else {
                strncpy(s_last_test_script, s_auto_test_script, strlen(s_auto_test_script));
                DBG_LOG_PRINT(("[LOG2USB] %s, find [%s] run it\n", __func__, s_auto_test_script));
                c_snprintf(s_auto_test_cmd, "PATH=/bin:/sbin:/system/bin:/system/sbin LD_LIBRARY_PATH=/lib:/system/lib /bin/sh %s &", s_auto_test_script);
                DBG_LOG_PRINT(("[LOG2USB] %s, run [%s]\n", __func__, s_auto_test_cmd));
                AP_SYSTEM_CALL(s_auto_test_cmd);
            }
        }
    }
    #endif
    c_snprintf(s_enable_file, BUF_SIZE,"%s/enable_log2usb", s_usb_path);

    b_file_exist = (access(s_enable_file, F_OK) == 0 ? TRUE : FALSE);

    b_bin_file_exist = (access("/bin/log2usb.sh", F_OK) == 0 ? TRUE : FALSE);

    DBG_INFO(("[LOG2USB] %s,b_file_exist=%d,true.\n", __func__,b_file_exist));

    if (NULL == pb_enable_log2usb)
    {
        /* error do noting*/
        return MENUR_FAIL;
    }

#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, _log_to_usb_is_enable_log2usb.\n", __func__));
#endif

    /* the file is exsit, enable log2usb */
    if ((TRUE == b_file_exist) && (TRUE == b_bin_file_exist))
    {
        *pb_enable_log2usb = TRUE;

        #if DBG_LOG
        DBG_LOG_PRINT(("[LOG2USB] %s, true.\n", __func__));
        #endif
    }
    /* if the file is not exsit, disable log2usb */
    else
    {
        *pb_enable_log2usb = FALSE;

    #if DBG_LOG
        DBG_LOG_PRINT(("[LOG2USB] %s, false.\n", __func__));
    #endif

    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_seq_file_is_exsit
 * Description:
 *      The API is check the seq file is or not exsit,
 *          then output the seq file path.
 * Input arguments:
 * Output arguments:
 *      the seq file path
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static BOOL _log_to_usb_seq_file_is_exsit(CHAR *s_seq_path, INT32 i4_len)
{
    CHAR      s_usb_path[BUF_SIZE]  = {'\0'};
    CHAR      s_path[BUF_SIZE]      = {'\0'};
    BOOL      b_file_exist          = FALSE;
    DIR* dir = NULL;

    if (NULL == s_seq_path)
    {
        /* error do noting*/
        return FALSE;
    }

    /* get the usb path */
    MENU_LOG_ON_FAIL( _usb_get_root_path(s_usb_path, sizeof(s_usb_path)) );

    // add LOG_FOLDER behind the original usb path
    c_snprintf(s_usb_path, sizeof(s_usb_path), "%s/%s", s_usb_path, LOG_FOLDER);
    dir = opendir(s_usb_path);
    if (NULL == dir)
    {
        if (-1 == mkdir(s_usb_path, 0777))
        {
            DBG_LOG_PRINT(("[LOG2USB] %s, mkdir %s error.\r\n", __func__, s_usb_path));
        }
    }
    else
    {
        closedir(dir);
    }

    c_snprintf(s_path, sizeof(s_path), "%s/%s", s_usb_path, s_seq_file);
    /* copy the seq file path to "s_seq_path" */
    c_strncpy(s_seq_path, s_path,
                 (i4_len < c_strlen(s_path) ? i4_len : c_strlen(s_path)));

    b_file_exist = (access(s_path, F_OK) == 0 ? TRUE : FALSE);

    /* the file is exsit, copy path */
    if ( TRUE == b_file_exist )
    {
        return TRUE;
    }
    /* else if the file is not exsit*/
    else
    {
        return FALSE;
    }

#if 0
    /* is the file exsit? */
    c_snprintf(s_cmd, sizeof(s_cmd), "ls -l %s", s_path);
    i4_status = system(s_cmd);

    c_dbg_stmt("[LOG2USB] %s, s_path:%s,_log_to_usb_seq_file_is_exsit.\n", __func__, s_path);

    /* fork error */
    if (-1 == i4_status)
    {
        /* error do noting*/
        return MENUR_FAIL;
    }
    else
    {
        if ( WIFEXITED(i4_status) )
        {
            /* the file is exsit, copy path */
            if ( 0 == WEXITSTATUS(i4_status) )
            {
                c_strncpy(s_seq_path, s_path,
                         (i4_len < c_strlen(s_path) ? i4_len : c_strlen(s_path)));
                return TRUE;
            }
            /* if the file is not exsit*/
            else
            {
                c_strncpy(s_seq_path, s_path,
                         (i4_len < c_strlen(s_path) ? i4_len : c_strlen(s_path)));

                return FALSE;
            }

        }

    }

    c_strncpy(s_seq_path, s_path,
             (i4_len < c_strlen(s_path) ? i4_len : c_strlen(s_path)));
#endif

    return  FALSE;
}
/*----------------------------------------------------------------------------
 * Name: _log_to_usb_get_log_file_name
 *
 * Description: get the log file name
 *
 * Inputs:
 *
 * Outputs: s_name:the log file name
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _log_to_usb_get_log_file_name(
    CHAR*   s_name,
    INT32   i4_len)
{
    INT32   i4_count              = 0;
    CHAR    s_file_name[BUF_SIZE] = {'\0'};
    CHAR    s_seq_path[BUF_SIZE]  = {'\0'};
    CHAR    s_count[8]            = {'\0'};
    time_t  t_time;
    FILE*   fp_out                = NULL;
    struct  tm  *pt_local_time       = NULL;
    INT32   i4_WriteSize = 0;
    INT32   i4_ReadSize           = 0;

    /* the network is enable*/
    if ( _log_to_usb_is_enable_network() )
    {
        /* get the local time */
        time(&t_time);

        pt_local_time = localtime(&t_time);
        c_snprintf(s_file_name, sizeof(s_file_name), "L_%d_%d_%d_%d_%d_%d.txt", pt_local_time->tm_year + 1900,
                                                      pt_local_time->tm_mon + 1,
                                                      pt_local_time->tm_mday,
                                                      pt_local_time->tm_hour,
                                                      pt_local_time->tm_min,
                                                      pt_local_time->tm_sec);


    }
    /* else if the network is diable */
    else
    {
        /* if the seq.txt is exsit, then read it and self_add it's num. */
        if ( _log_to_usb_seq_file_is_exsit(s_seq_path, sizeof(s_seq_path)) )
        {
            fp_out = fopen(s_seq_path, "r");
            if(fp_out == NULL)
            {
                DBG_LOG_PRINT(("\n[LOG2USB] %s, open usb file fail: %s!\n\r", __func__, s_seq_path));
                return MENUR_FAIL;
            }

            /* read file */
            i4_ReadSize = fread(s_count, 1, sizeof(s_count), fp_out); //coverity 4514934

            /* string to int */
            i4_count = atoi(s_count);

            /* close the FILE pointer, ready to next use */
            fclose(fp_out);
            fp_out = NULL;

            /* self_add */
            i4_count ++;
            c_snprintf(s_file_name, sizeof(s_file_name), "L%d.txt", i4_count);

            /* int to string */
            i4_WriteSize = c_snprintf(s_count, sizeof(s_count), "%d", i4_count);
            fp_out = fopen(s_seq_path, "w+");
            if(fp_out == NULL)
            {
                DBG_LOG_PRINT(("\n[LOG2USB] %s, open usb file fail: %s!\n\r", __func__, s_seq_path));
                return MENUR_FAIL;
            }
            if (i4_WriteSize >= 0)
            {
                /* write to file */
                fwrite(s_count, 1, i4_WriteSize, fp_out);
            }            

            fclose(fp_out);
            fp_out = NULL;
        }
        /* there is no file */
        else
        {
            fp_out = fopen(s_seq_path, "w+");
            if(fp_out == NULL)
            {
                DBG_LOG_PRINT(("\n[LOG2USB] %s, open usb file fail: %s!\n\r",
                                __func__, s_seq_path));
                return MENUR_FAIL;
            }
            /* create the first log file */
            i4_count = 1;
            c_snprintf(s_file_name, sizeof(s_file_name), "L%d.txt",  i4_count);

            /* int to string */
            i4_WriteSize = c_snprintf(s_count, sizeof(s_count), "%d",  i4_count);

            /* write to file */
            if (i4_WriteSize >= 0)
            {
                fwrite(s_count, 1, sizeof(s_count), fp_out);
            }

            /* close the FILE pointer */
            fclose(fp_out);
            fp_out = NULL;

        }
    }
#if DBG_LOG
    DBG_LOG_PRINT(("\n[LOG2USB] %s, s_file_name:%s!\n\r", __func__, s_file_name));
#endif
    c_strncpy(s_name, s_file_name,
             (i4_len < c_strlen(s_file_name) ? i4_len : c_strlen(s_file_name)));

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_create_file_path
 * Description:
 *      create "s_log_path" file that content is absolute path.
 * Input arguments:
 * Output arguments:
 * NONE
 * Returns:
 *      i4_ret  == MENUR_FAIL,create file path fail
 *      i4_ret  == MENUR_OK,create file path success
 *---------------------------------------------------------------------------*/
static INT32 _log_to_usb_create_file_path(VOID)
{
    UINT32      ui4_usb_count = 0;
    INT32       i4_ret        = MENUR_FAIL;
    CHAR        s_usb_path[BUF_SIZE]   = {'\0'};
    CHAR        s_log_name[BUF_SIZE]   = {'\0'};
#if 0
    CHAR        s_logcat_log_name[BUF_SIZE]   = {'\0'};
    CHAR        s_logcat_cmd[BUF_SIZE] = {'\0'};
#else
    CHAR        s_log2usb_log_name[BUF_SIZE]   = {'\0'};
    CHAR        s_log2usb_cmd[BUF_SIZE] = {'\0'};
#endif

    FILE*       fp_out        = NULL;

    PAGE_LOG2USB_HIDE_T*     pt_this = &t_page_log_to_usb_hide;

    /* get usb dev count */
    ui4_usb_count = _get_usb_count();
#if DBG_LOG
    DBG_LOG_PRINT(("[LOG2USB] %s, ui4_usb_count:%d\n", __func__, ui4_usb_count));
#endif

    /* if enable log2usb and there is a usb, then write usb path and send message */
    if ((TRUE == pt_this->b_enable_log2usb) &&  (ui4_usb_count > 0))
    {

        /* get the log file name */
        i4_ret = _log_to_usb_get_log_file_name(s_log_name, sizeof(s_log_name));
        if (MENUR_OK != i4_ret)
        {
            return i4_ret;
        }

        /* get the usb root path */
        i4_ret = _usb_get_root_path(s_usb_path, sizeof(s_usb_path));
        if (MENUR_OK != i4_ret)
        {
            return i4_ret;
        }
        else
        {
            DIR* dir = NULL;
            // add LOG_FOLDER behind the original usb path
            c_snprintf(s_usb_path, sizeof(s_usb_path), "%s/%s", s_usb_path, LOG_FOLDER);
            dir = opendir(s_usb_path);
            if (NULL == dir)
            {
                if (-1 == mkdir(s_usb_path, 0777))
                {
                    DBG_LOG_PRINT(("[LOG2USB] %s, mkdir %s error.\r\n", __func__, s_usb_path));
                    return -1;
                }
            }
            else
            {
                closedir(dir);
            }
        }

        #if 1
        // check sh /bin/log2usb.sh exsit?
        if(access("/bin/log2usb.sh", F_OK) != 0)
        {
            /* the file is not exsit, return*/
            DBG_LOG_PRINT(("[LOG2USB] ========================================================================\r\n"));
            DBG_LOG_PRINT(("[LOG2USB] /bin/log2usb.sh no exsit !!!!!!!!!!!!!\r\n"));
            DBG_LOG_PRINT(("[LOG2USB] ========================================================================\r\n"));
            return MENUR_FAIL;
        }
        #endif




#if DBG_LOG
        DBG_LOG_PRINT(("[LOG2USB] ========================================================================\r\n"));
        DBG_LOG_PRINT(("[LOG2USB] _log_to_usb_create_log_file_name,s_log_name:%s,s_usb_path:%s line:%d.\n", s_log_name,s_usb_path ,__LINE__));
        DBG_LOG_PRINT(("[LOG2USB] ========================================================================\r\n"));
#endif
        #if 0
        c_snprintf(s_usb_file_path, sizeof(s_usb_file_path), "%s/%s", s_usb_path, s_log_name);

        fp_out = fopen(s_log_path, "w");
        if(fp_out == NULL)
        {
            DBG_LOG_PRINT(("[LOG2USB] %s, %s \n", __func__, strerror(errno)));
            DBG_LOG_PRINT(("\n[LOG2USB] %s, open usb file fail: %s!\n\r",
                            __func__, s_log_path));

            return MENUR_FAIL;
        }

        /* write the usb path to file */
        fwrite((const CHAR*)s_usb_file_path, 1, c_strlen((const CHAR*)s_usb_file_path), fp_out);

        /* flesh kernel buffer */
        fflush(fp_out);
        c_snprintf(s_logcat_log_name, sizeof(s_logcat_log_name), "%s_%s", "logcat", s_log_name);
        c_snprintf(s_logcat_cmd, sizeof(s_logcat_cmd), "%s%s/%s &", "LD_LIBRARY_PATH=/lib:/system/lib /bin/logcat -v threadtime -f ", s_usb_path, s_logcat_log_name);
        DBG_LOG_PRINT(("[LOG2USB] %s, s_logcat_cmd:[%s]\n", __func__, s_logcat_cmd));
        system(s_logcat_cmd);

        /* write to disk */
        fsync(fp_out->_fileno);

        fclose(fp_out);
        fp_out = NULL;


        #else
        AP_SYSTEM_CALL("echo 0 > /proc/sys/kernel/printk");
        c_snprintf(s_log2usb_log_name, sizeof(s_log2usb_log_name), "%s_%s", "log2usb", s_log_name);
        c_snprintf(s_log2usb_cmd, sizeof(s_log2usb_cmd), "%s%s/%s", "/bin/log2usb.sh start ", s_usb_path, s_log2usb_log_name);
        DBG_LOG_PRINT(("[LOG2USB] %s, s_log2usb_cmd:[%s]\n", __func__, s_log2usb_cmd));
        AP_SYSTEM_CALL(s_log2usb_cmd);
        #endif
    }
    else
    {
        /* do noting*/
        i4_ret = MENUR_FAIL;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _log_to_usb_refresh
 * Description:
 *      check the "s_enable_file" file, then refresh the enable flag and start
 *          to capture log.
 * Input arguments:
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _log_to_usb_refresh(VOID)
{
    INT32                   i4_ret           = MENUR_FAIL;
    PAGE_LOG2USB_HIDE_T*    pt_page_data     = &t_page_log_to_usb_hide;
    /* start repeat timer */
    i4_ret = c_timer_start(pt_page_data->h_signal_lvl_timer,
                      DELAY_TIME,
                      X_TIMER_FLAG_REPEAT,
                      _timer_signal_nfy_fct,
                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                                VOID * pv_create_data)
{
    INT32                    i4_ret = MENUR_FAIL;
    PAGE_LOG2USB_HIDE_T*     pt_page_data = &t_page_log_to_usb_hide;

    c_memset(pt_page_data, 0, sizeof(PAGE_LOG2USB_HIDE_T));
    /* init */
    i4_current_count = 0;
#if 0
    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &(pt_page_data->h_cnt_frm));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _subpage_item_create();
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = c_timer_create(&pt_page_data->h_signal_lvl_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    /* register remove device notification function */
    i4_ret = a_rmv_dev_reg_monitor(
                    _log_to_usb_pld_rmv_dev_nfy,
                    NULL,
                    &pt_page_data->h_rmv_dev_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_destroy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    PAGE_LOG2USB_HIDE_T* pt_this = &t_page_log_to_usb_hide;
    INT32                i4_ret = MENUR_OK;

    /* unregister remove device notification function */
    i4_ret = a_rmv_dev_unreg_monitor(pt_this->h_rmv_dev_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    if (NULL_HANDLE != pt_this->h_signal_lvl_timer)
    {
        /* delete the timer handle */
        i4_ret = c_timer_delete(pt_this->h_signal_lvl_timer);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_show(UINT32 ui4_page_id)
{

#if 0
    INT32                    i4_ret = MENUR_OK;
    PAGE_LOG2USB_HIDE_T*     pt_page_data = &t_page_log_to_usb_hide;
    HANDLE_T                 h_last_shadow_item = NULL_HANDLE;
    GL_RECT_T                t_rect = {0};

    /* Change the page title */
    menu_main_set_title(MLM_MENU_KEY_MENU_LOG_TO_USB_TITLE);

    /* show the subpage */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);
#if 0
    //i4_ret = _get_log_to_usb_status(&i1_idx);
    //MENU_LOG_ON_FAIL(i4_ret);

    //c_dbg_stmt("_get_log_to_usb_status,line:%d, i1_idx: %d", __LINE__, i1_idx);

    if (1 == i1_idx)
    {
        menu_list_set_idx(pt_page_data->h_log2usb,
                 (UINT16)1);
    }
    else
    {
        menu_list_set_idx(pt_page_data->h_log2usb,
                 (UINT16)0);
    }
#endif
    /* show the item */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_log2usb,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Adjust last shadow position */
    t_rect.i4_top = 0;
    t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_hide
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_hide(UINT32 ui4_page_id)
{

#if 0
    INT32                    i4_ret;
    PAGE_LOG2USB_HIDE_T*     pt_page_data = &t_page_log_to_usb_hide;
    HANDLE_T                 h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_get_last_shadow_item(&h_last_shadow_item);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_get_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_get_focus(
                                    UINT32 ui4_page_id,
                                    MENU_PAGE_HINT_T* pt_hint)
{
#if 0
    PAGE_LOG2USB_HIDE_T*     pt_page_data = &t_page_log_to_usb_hide;

    /* set callback function for backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc(_backbar_proc_fct));

    /* set callback function for homebar */
    MENU_LOG_ON_FAIL (menu_set_homebar_proc(_homebar_proc_fct));

    MENU_LOG_ON_FAIL (c_wgl_set_focus (pt_page_data->h_log2usb, WGL_NO_AUTO_REPAINT));
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_lose_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_lose_focus(
                                    UINT32 ui4_page_id)
{

#if 0
    /* clean callback function of backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc(NULL));

    /* set callback function for homebar */
    MENU_LOG_ON_FAIL (menu_set_homebar_proc(NULL));
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_update(
                                UINT32 ui4_page_id,
                                UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_common_page_nw_hide_init
 *
 * Description: init the callback function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_common_page_log_to_usb_init(VOID)
{
    t_g_menu_common_log_to_usb.pf_menu_page_create     = _on_page_create;
    t_g_menu_common_log_to_usb.pf_menu_page_destroy    = _on_page_destroy;
    t_g_menu_common_log_to_usb.pf_menu_page_show       = _on_page_show;
    t_g_menu_common_log_to_usb.pf_menu_page_hide       = _on_page_hide;
    t_g_menu_common_log_to_usb.pf_menu_page_get_focus  = _on_page_get_focus;
    t_g_menu_common_log_to_usb.pf_menu_page_lose_focus = _on_page_lose_focus;
    t_g_menu_common_log_to_usb.pf_menu_page_update     = _on_page_update;

    return MENUR_OK;
}

#endif /* end APP_LOG2USB_SUPPORT*/


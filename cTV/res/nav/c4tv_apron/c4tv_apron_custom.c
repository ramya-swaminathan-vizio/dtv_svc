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
 * $RCSfile: audio_info_view_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/08/25 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_cli.h"
#include "c_dbg.h"
#include "u_common.h"
#include "u_btn_map.h"
#include "x_os.h"
#include "c_os.h"
#include "c_aee.h"
#include "c_svctx.h"
#include "c_pcl.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "nav/nav_common.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom_view.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom.h"
#include "nav/c4tv_apron/c4tv_cast_control_if.h"

#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "rest/a_rest_api.h"
#include "nav/link_mode/link_mode.h"
#include "nav/input_src/a_input_src.h"
#include "wdk/vkb/vkb.h"
#include "wizard_anim/a_wzd.h"
#include "securestorage/include/SecureStorage.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/revolt/revolt_settings_mlm.h"
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "rest/a_rest_event.h"
#include "mtosd.h"
#include "bgm/bgm.h"
#define C4TV_CUSTOM_LOG_PREFIX "[c4tv_apron_custom] "
#define C4TV_CUSTOM_ULI_PROVISION_MAX_NUM       ((UINT8)8)
#define C4TV_CUSTOM_POLLING_ULI_THREAD_NAME     "c4tv_customer_thread"
#define C4TV_CUSTOM_POLLING_ULI_THREAD_PRIORITY 200
#define C4TV_CUSTOM_POLLING_ULI_STACK_SIZE      (8 * 1024)

#define APP_GCASTDU                "GCASTDU"
#define KEY_GCASTDU_CERT           "GCASTDU_CERT"
#define KEY_GCASTDU_KEY            "GCASTDU_KEY"

#define GCASTDU_CERT_ID_BUFF_SIZE                         (1024)
#define GCASTDU_CERT_CONTENT_BUFF_SIZE                    (1024 * 6)

#define GCASTDU_KEY_ID_BUFF_SIZE                          (1024)
#define GCASTDU_KEY_CONTENT_BUFF_SIZE                     (1024 * 2)

#ifdef APP_TTS_SUPPORT
#define C4TV_TTS_TEXT(key)   MLM_SETTINGS_TEXT(0, (key))  /* 0:english   */
#endif

#define APP_AMAZONIOT                "IOT"
#define KEY_AMAZONIOT_CERT           "IOT_CERT"
#define KEY_AMAZONIOT_KEY            "IOT_KEY"
#define KEY_AMAZONIOT_TRUSTSTORE     "IOT_TRUSTSTORE"

#define AMAZONIOT_ID_BUFF_SIZE                         (1024)
#define AMAZONIOT_CONTENT_BUFF_SIZE                    (1024 * 4)

static SECURESTORAGE_USERKEY_T t_secret_key = {{0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff}};

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
//static BOOL b_will_do_play = FALSE;//true ,will do play;FALSE,will do pause.

static HANDLE_T h_c4tv_customer_thread = 0;
static UINT16 ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;

static INT8  i1_g_pre_input = -1;

extern C4TV_APRON_T  t_g_c4tv_apron;
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static VOID _c4tv_customer_get_cast_cert()
{
    INT32            i4_ret = 0;
    CHAR             s_obj_content[GCASTDU_CERT_CONTENT_BUFF_SIZE] = {0};
    unsigned long    ui4_obj_sz = 0;

    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s Enter\n", __FUNCTION__));

    if(0 != access("/data/factory", 0))
    {
        i4_ret = mkdir("/data/factory", S_IRWXU|S_IRWXG|S_IRWXO);

        if (0 != i4_ret)
        {
            DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"mkdir /data/factory failed!\n"));
            return;
        }
    }
#ifdef ULI_USE_ODL_LIB
    CHAR             s_owner_name[16] = {0};
    CHAR             s_object_name[16] = {0};
    CHAR             s_obj_id[GCASTDU_CERT_ID_BUFF_SIZE] = {0};
    unsigned long    ui4_encrypt_type = 0;

    i4_ret = utv_project_get_owner(APP_GCASTDU, (char *)&(s_owner_name[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_owner() failed, %d\n", i4_ret));
        return;
    }

    i4_ret = utv_project_get_name(KEY_GCASTDU_CERT, (char *)&(s_object_name[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_name() failed, %d\n", i4_ret));
        return;
    }

    i4_ret = utv_project_on_obj_req((char *)&(s_owner_name[0]),
                                    (char *)&(s_object_name[0]),
                                    &(s_obj_id[0]),
                                    GCASTDU_CERT_ID_BUFF_SIZE,
                                    (unsigned char*)s_obj_content,
                                    GCASTDU_CERT_CONTENT_BUFF_SIZE,
                                    &ui4_obj_sz,
                                    &ui4_encrypt_type);
#endif
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_on_obj_req() failed, %d\n", i4_ret));
        return;
    }

    FILE* fp_wv = fopen("/data/factory/mediatek_tv_dev_test_chain.pem", "wb");
    if (NULL != fp_wv)
    {
        fwrite(s_obj_content, ui4_obj_sz, 1, fp_wv);
        fclose(fp_wv);
    }
    else
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"open /data/factory/mediatek_tv_dev_test_chain.pem failed!\n"));
        return;
    }
}


static void _c4tv_customer_get_cast_key()
{
    INT32            i4_ret = 0;
    CHAR             s_obj_content[GCASTDU_KEY_CONTENT_BUFF_SIZE] = {0};
    unsigned long    ui4_obj_sz = 0;

    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s Enter\n", __FUNCTION__));

    if(0 != access("/data/factory", 0))
    {
        i4_ret = mkdir("/data/factory", S_IRWXU|S_IRWXG|S_IRWXO);

        if (0 != i4_ret)
        {
            DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"mkdir /data/factory failed!\n"));
            return;
        }
    }
#ifdef ULI_USE_ODL_LIB
    CHAR             s_owner_name[16] = {0};
    CHAR             s_object_name[16] = {0};
    CHAR             s_obj_id[GCASTDU_KEY_ID_BUFF_SIZE] = {0};
    unsigned long    ui4_encrypt_type = 0;

    i4_ret = utv_project_get_owner(APP_GCASTDU, (char *)&(s_owner_name[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_owner() failed, %d\n", i4_ret));
        return;
    }

    i4_ret = utv_project_get_name(KEY_GCASTDU_KEY, (char *)&(s_object_name[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_name() failed, %d\n", i4_ret));
        return;
    }

    i4_ret = utv_project_on_obj_req((char *)&(s_owner_name[0]),
                                    (char *)&(s_object_name[0]),
                                    &(s_obj_id[0]),
                                    GCASTDU_KEY_ID_BUFF_SIZE,
                                    (unsigned char*)s_obj_content,
                                    GCASTDU_KEY_CONTENT_BUFF_SIZE,
                                    &ui4_obj_sz,
                                    &ui4_encrypt_type);
#endif
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_on_obj_req() failed, %d\n", i4_ret));
        return;
    }

    i4_ret = x_tee_secure_storage_mem2file_encryption(s_obj_content,
                                             (long)ui4_obj_sz,
                                             (const char*)"/data/factory/mediatek_tv_dev_test.key.pem",
                                             &t_secret_key);

    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"x_tee_secure_storage_mem2file_encryption Failed: %d\n", i4_ret));
        return;
    }
    else
    {
        DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"x_tee_secure_storage_mem2file_encryption Success\n"));
    }
}

VOID c4tv_customer_get_amazon_iot_cert_key_truststore()
{
    INT32            i4_ret = 0;
    CHAR             s_obj_content_cert[AMAZONIOT_CONTENT_BUFF_SIZE] = {0};
    CHAR             s_obj_content_key[AMAZONIOT_CONTENT_BUFF_SIZE] = {0};
    unsigned long    ui4_obj_sz_cert = 0;
    unsigned long    ui4_obj_sz_key = 0;
    unsigned long    ui4_obj_sz_truststore = 0;
    CHAR             s_obj_content_truststore[AMAZONIOT_CONTENT_BUFF_SIZE] = {0};

    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s Enter\n", __FUNCTION__));

    if (0 != access("/data/amazon_iot", 0))
    {
        i4_ret = mkdir("/data/amazon_iot", S_IRWXU|S_IRWXG|S_IRWXO);
        if (0 != i4_ret)
        {
            DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"mkdir /data/factory failed!\n"));
            return;
        }
    }
#ifdef ULI_USE_ODL_LIB

    unsigned long    ui4_encrypt_type_key = 0;
    unsigned long    ui4_encrypt_type_cert = 0;
    unsigned long    ui4_encrypt_type_truststore = 0;
    CHAR             s_obj_id_cert[AMAZONIOT_ID_BUFF_SIZE] = {0};
    CHAR             s_obj_id_key[AMAZONIOT_ID_BUFF_SIZE] = {0};
    CHAR             s_obj_id_truststore[AMAZONIOT_ID_BUFF_SIZE] = {0};
    CHAR             s_object_name_cert[16] = {0};
    CHAR             s_object_name_key[16] = {0};
    CHAR             s_object_name_truststore[16] = {0};
    CHAR             s_owner_name[16] = {0};

    i4_ret = utv_project_get_owner(APP_AMAZONIOT, (char *)&(s_owner_name[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_owner() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_owner_name size %d\n\r", c_strlen(s_owner_name)));
    }*/

    // get cert
    i4_ret = utv_project_get_name(KEY_AMAZONIOT_CERT, (char *)&(s_object_name_cert[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_name() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_object_name_cert size %d\n\r", c_strlen(s_object_name_cert)));
    }*/
    i4_ret = utv_project_on_obj_req((char *)&(s_owner_name[0]),
                                    (char *)&(s_object_name_cert[0]),
                                    &(s_obj_id_cert[0]),
                                    GCASTDU_CERT_ID_BUFF_SIZE,
                                    (unsigned char*)s_obj_content_cert,
                                    GCASTDU_CERT_CONTENT_BUFF_SIZE,
                                    &ui4_obj_sz_cert,
                                    &ui4_encrypt_type_cert);
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_on_obj_req() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_obj_id_cert size %d\n\r", c_strlen(s_obj_id_cert)));
        DBG_LOG_PRINT(("[chris] s_obj_content_cert size %d\n\r", c_strlen(s_obj_content_cert)));
    }*/

    // get key
    i4_ret = utv_project_get_name(KEY_AMAZONIOT_KEY, (char *)&(s_object_name_key[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_name() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_object_name_key size %d\n\r", c_strlen(s_object_name_key)));
    }*/
    i4_ret = utv_project_on_obj_req((char *)&(s_owner_name[0]),
                                    (char *)&(s_object_name_key[0]),
                                    &(s_obj_id_key[0]),
                                    GCASTDU_CERT_ID_BUFF_SIZE,
                                    (unsigned char*)s_obj_content_key,
                                    GCASTDU_CERT_CONTENT_BUFF_SIZE,
                                    &ui4_obj_sz_key,
                                    &ui4_encrypt_type_key);
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_on_obj_req() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_obj_id_key size %d\n\r", c_strlen(s_obj_id_key)));
        DBG_LOG_PRINT(("[chris] s_obj_content_key size %d\n\r", c_strlen(s_obj_content_key)));
    }*/

    // get truse store
    i4_ret = utv_project_get_name(KEY_AMAZONIOT_TRUSTSTORE, (char *)&(s_object_name_truststore[0]));
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_get_name() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_object_name_truststore size %d\n\r", c_strlen(s_object_name_truststore)));
    }*/
    i4_ret = utv_project_on_obj_req((char *)&(s_owner_name[0]),
                                    (char *)&(s_object_name_truststore[0]),
                                    &(s_obj_id_truststore[0]),
                                    GCASTDU_CERT_ID_BUFF_SIZE,
                                    (unsigned char*)s_obj_content_truststore,
                                    GCASTDU_CERT_CONTENT_BUFF_SIZE,
                                    &ui4_obj_sz_truststore,
                                    &ui4_encrypt_type_truststore);
#endif
    if (0 != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"utv_project_on_obj_req() failed, %d\n", i4_ret));
        return;
    }
    /*else
    {
        DBG_LOG_PRINT(("[chris] s_obj_id_truststore size %d\n\r", c_strlen(s_obj_id_truststore)));
        DBG_LOG_PRINT(("[chris] s_obj_content_truststore size %d\n\r", c_strlen(s_obj_content_truststore)));
    }*/

    FILE* fp_iot_cert = fopen("/data/amazon_iot/certificate.pem.crt", "wb");
    if (NULL != fp_iot_cert)
    {
        fwrite(s_obj_content_cert, ui4_obj_sz_cert, 1, fp_iot_cert);
        fclose(fp_iot_cert);
    }
    else
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"open /data/amazon_iot/cert failed!\n"));
        return;
    }

    FILE* fp_iot_key = fopen("/data/amazon_iot/private.key.pem", "wb");
    if (NULL != fp_iot_key)
    {
        fwrite(s_obj_content_key, ui4_obj_sz_key, 1, fp_iot_key);
        fclose(fp_iot_key);
    }
    else
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"open /data/amazon_iot/cert failed!\n"));
        return;
    }

    FILE* fp_iot_truststore = fopen("/data/amazon_iot/CA.pem", "wb");
    if (NULL != fp_iot_truststore)
    {
        fwrite(s_obj_content_truststore, ui4_obj_sz_truststore, 1, fp_iot_truststore);
        fclose(fp_iot_truststore);
    }
    else
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"open /data/amazon_iot/truststore failed!\n"));
        return;
    }
}

VOID _c4tv_customer_apron_cb_main (VOID*  pv_arg)
{
    DBG_LOG_PRINT((C4TV_CUSTOM_LOG_PREFIX"%s \n", __FUNCTION__));

    UINT16  ui2_status     = 0;
    UINT8   ui1_state      = 0;
    UINT8   ui1_val        = 0;

    a_wzd_set_privision_update(TRUE);

    while(1)
    {
        a_cfg_get_wzd_status(&ui2_status);
        ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);

        a_icl_get_uli_download_status(&ui1_val);

        if( WZD_STATE_RESUME_C4TV_END == ui1_state )
        {
            if( ui1_val == 1 )
            {
                DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s,key had downloaded done and OOBE end,delete orignial key,delay 0 \n", __FUNCTION__));
                AP_SYSTEM_CALL("mount -o remount -o rw /perm");
                AP_SYSTEM_CALL("rm -rf /perm/cast_tv/mediatek_tv_dev*");
                AP_SYSTEM_CALL("mount -o remount -o ro /perm");
                AP_SYSTEM_CALL("rm -rf /data/factory/mediatek_tv_dev*");
                _c4tv_customer_get_cast_cert();
                _c4tv_customer_get_cast_key();
#ifndef SYS_C4TV_TWO_WORLDS
                AP_SYSTEM_CALL("chmod +x /AP_SYSTEM_CALL/etc/service/cast_stop.sh");
                AP_SYSTEM_CALL("/AP_SYSTEM_CALL/etc/service/cast_stop.sh");
                AP_SYSTEM_CALL("start cast_receiver");
#else
                a_c4tv_apron_enable_cast_shell(FALSE);
                a_c4tv_apron_enable_cast_shell(TRUE);
#endif
                c4tv_customer_get_amazon_iot_cert_key_truststore();
                break;
            }
        }

        c_thread_delay(300);
    }

    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s main thread exit \n", __FUNCTION__));
    x_thread_exit();
}


static INT32 _c4tv_custom_icl_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32 i4_ret  = 0;
    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX" %s \n",__FUNCTION__));

    i4_ret = c_aee_thread_create(&h_c4tv_customer_thread,
                                  C4TV_CUSTOM_POLLING_ULI_THREAD_NAME,
                                  C4TV_CUSTOM_POLLING_ULI_STACK_SIZE,
                                  C4TV_CUSTOM_POLLING_ULI_THREAD_PRIORITY,
                                  _c4tv_customer_apron_cb_main,
                                  0,
                                  NULL);
    if (OSR_OK != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"create thread failed !!!!\n"));
        return C4TV_APRON_INV_ARG;
    }

    return ICLR_OK;
}

static VOID _c4tv_apron_clean_preselect_info()
{
    HANDLE_T h_main_svctx = NULL_HANDLE;
    INT32    i4_ret =0;
    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_main_svctx);
    C4TV_APRON_RET_ONLY_ON_ERR(i4_ret);
    /* clean pre-select info*/
    i4_ret = c_svctx_set(
               h_main_svctx,
               SVCTX_COMMON_SET_CLEAN_PRE_SELECT_INFO,
               NULL,
               0);
    C4TV_APRON_RET_ONLY_ON_ERR(i4_ret);
}

static VOID _c4tv_apron_cfg_nfy_func(UINT16 ui2_nfy_id, VOID* pv_tag, UINT16 ui2_id)
{
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_nfy_id != ui2_nfy_id)
    {
        return;
    }

    if (APP_CFG_RECID_INPUT_MAIN == ui2_rec_id)
    {
        UINT8 ui1_input_src = 0;
        CHAR  s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
        ISL_REC_T t_isl_rec = {0};

        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        a_cfg_av_get_input_src(s_disp_name, &ui1_input_src);
        a_isl_get_rec_by_id(ui1_input_src, &t_isl_rec);

        if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
        {
            if (i1_g_pre_input != t_isl_rec.ui1_internal_id)
            {
                i1_g_pre_input = t_isl_rec.ui1_internal_id;
                acfg_custom_update_all(ACFG_UPDATE_REASON_CHG_INPUT, s_disp_name);
                _c4tv_apron_clean_preselect_info();
            }
            i1_g_pre_input = t_isl_rec.ui1_internal_id;
        }
        else
        {
            i1_g_pre_input = -1;
        }
    }
}

INT32 c4tv_apron_custom_is_key_handler(UINT32 ui4_key_code,BOOL *pb_handle)
{
    C4TV_APRON_T  *pt_this    = &t_g_c4tv_apron;

//    DBG_LOG_PRINT(("%s,%d [c4tv_apron_custom]e_state= %d,key= %d \r\n",__FUNCTION__,__LINE__, pt_this->e_c4tv_state, ui4_key_code));
    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s, press key %d, e_state= %d\n",__FUNCTION__, ui4_key_code, pt_this->e_c4tv_state));

    if (pt_this->e_c4tv_state != C4TV_APRON_STATE_UNKNOWN &&
        pt_this->e_c4tv_state != C4TV_APRON_STATE_WATCHING_TV)
    {
        c4tv_apron_custom_handle_key(ui4_key_code);
    }
    if (pt_this->e_c4tv_state == C4TV_APRON_STATE_WATCHING_TV)
    {
        a_rest_app_handle_key_for_browser_control(ui4_key_code);
    }

    *pb_handle = FALSE;

    return C4TV_APRON_OK;
}

VOID c4tv_apron_custom_flush_cast_osd(VOID)
{
    int fd;
    void *bits;

    DBG_INFO(("[c4tv_apron][chris] ClearNativeWindowByFb\n"));

    struct fb_fix_screeninfo fi;
    struct fb_var_screeninfo vi;

    printf("EglPlatformMtk::ClearNativeWindowByFb() called \n");

    fd = open("/dev/graphics/fb1", O_RDWR);
    if (fd < 0)
    {
        perror("cannot open fb");
        return ;
    }

    if (ioctl(fd, FBIOGET_FSCREENINFO, &fi) < 0)
    {
        perror("failed to get fb info");
        close(fd);
        return ;
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &vi) < 0)
    {
        perror("failed to get fb info");
        close(fd);
        return ;
    }

    bits = mmap(0, fi.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (bits == MAP_FAILED)
    {
        perror("failed to mmap framebuffer");
        close(fd);
        return ;
    }

    memset(bits, 0, fi.smem_len);

    munmap(bits, fi.smem_len);
    close(fd);

    return ;
}

static BOOL _c4tv_apron_custom_retail_mode_is_on(VOID)
{
    ACFG_RETAIL_MODE_T      t_retail_mode   = ACFG_RETAIL_MODE_HOME;

#ifdef APP_RETAIL_MODE_SUPPORT
    INT32                   i4_ret          = 0;
    i4_ret = a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"acfg get_retail_mode_setting failed !!!!\n"));
        return FALSE;
    }
#endif

    if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

INT32 c4tv_apron_custom_handle_key_delegate(UINT32 ui4_keycode)
{
    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s, delegate key %d.\n",__FUNCTION__, ui4_keycode));

    C4TV_APRON_T *pt_this = &t_g_c4tv_apron;
    UINT8 ui1_icl_val = ICL_RECID_CAST_SRC_STATUS_FALSE;

    switch (ui4_keycode)
    {
        case BTN_SELECT:    //IR ok button has select/paly/pause function
        {
            /*get media state in order to know the state of video through the tablet's control*/
#ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
#endif
            DBG_INFO(("%s,%d [c4tv_apron_custom] e_state= %d \r\n",__FUNCTION__,__LINE__,
                                pt_this->t_media_status.t_player.e_state));

            if (pt_this->t_media_status.t_player.e_state == C4TV_APRON_PLAYER_STATUS_PAUSED)
            {
#ifdef APP_TTS_SUPPORT
                c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PLAY));
                a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
                C4tvNotifyUserAction(kC4tvUserActionPlay);
            }
            else if (pt_this->t_media_status.t_player.e_state == C4TV_APRON_PLAYER_STATUS_PLAYING )
            {
#ifdef APP_TTS_SUPPORT
                c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PAUSE));
                a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
                C4tvNotifyUserAction(kC4tvUserActionPause);

                a_icl_custom_get_cast_src_status(&ui1_icl_val);
                if (ICL_RECID_CAST_SRC_STATUS_FALSE == ui1_icl_val)
                {
                    nav_rcu_key_handler(ui4_keycode);
                    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"not cast src, dispatch keycode.\n"));
                }
            }
            //else if (C4TV_APRON_PLAYER_STATUS_IDLE == pt_this->t_media_status.t_player.e_state &&
            //         BTN_SELECT == ui4_keycode)
            //{
            //    rest_event_notify("key_command", ui4_keycode, "");
            //}
            else
            {
                DBG_INFO(("%s,%d media don't in pause or play status \r\n",__FUNCTION__,__LINE__));
            }
            break;
        }
        case BTN_PAUSE:
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"[c4tv_apron_custom] c4tv_apron_custom_handle_key_delegate- BTN_PAUSE\n\r"));
#ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PAUSE));
            a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
            C4tvNotifyUserAction(kC4tvUserActionPause);
            break;
        }
        case BTN_PLAY:
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"[c4tv_apron_custom] c4tv_apron_custom_handle_key_delegate- BTN_PLAY\n\r"));
#ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PLAY));
            a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
            C4tvNotifyUserAction(kC4tvUserActionPlay);
            break;
        }
        case BTN_STOP:
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"[c4tv_apron_custom] c4tv_apron_custom_handle_key_delegate- BTN_STOP\n\r"));
#ifdef APP_TTS_SUPPORT
            //UTF16_T w2s_str[128] = {0};
            //c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PLAY));
            //a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
            C4tvNotifyUserAction(kC4tvUserActionStop);
            break;
        }
        case BTN_NEXT:
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"[c4tv_apron_custom] c4tv_apron_custom_handle_key_delegate- BTN_NEXT\n\r"));
#ifdef APP_TTS_SUPPORT
            //UTF16_T w2s_str[128] = {0};
            //c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PLAY));
            //a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
            C4tvNotifyUserAction(kC4tvUserActionNext);
            break;
        }
        case BTN_PREV:
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"[c4tv_apron_custom] c4tv_apron_custom_handle_key_delegate- BTN_PREV\n\r"));
#ifdef APP_TTS_SUPPORT
            //UTF16_T w2s_str[128] = {0};
            //c_uc_w2s_strcpy(w2s_str, C4TV_TTS_TEXT(MLM_SETTINGS_KEY_TTS_PLAY));
            //a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
            C4tvNotifyUserAction(kC4tvUserActionPrevious);
            break;
        }
        default:
            break;
    }

    return C4TV_APRON_OK;
}

INT32 c4tv_apron_custom_handle_key(UINT32 ui4_keycode)
{
    BOOL    b_is_processed = FALSE;

    /* if in oobe mode or retail mode, handle key with iom cb function */
    if (a_wzd_is_oobe_mode() || _c4tv_apron_custom_retail_mode_is_on())
    {
        DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s, %d, %u key handle in retail mode.\n\r",__FUNCTION__, __LINE__, ui4_keycode));
#if 0
		if (BTN_CC == ui4_keycode)
        {
            nav_rcu_key_handler(ui4_keycode);
        }
#endif
        return C4TV_APRON_OK;
    }
    else
    {
        DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"%s, press key %d.\n",__FUNCTION__, ui4_keycode));
        switch (ui4_keycode)
        {
            case BTN_PRG_INFO:
            {
                DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"banner is received %d \n", ui4_keycode));
                nav_rcu_key_handler(ui4_keycode);
                b_is_processed = TRUE;
                break;
            }
            case BTN_EXIT:
            {
                DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"BTN_EXIT, not handle.\n"));
                b_is_processed = TRUE;
#ifdef APP_TTS_SUPPORT
                a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif
                break;
            }
            case BTN_BLUE:
            case BTN_YELLOW:
            case BTN_RED:
            case BTN_GREEN:
            {
                DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"not handle color key.\n"));
                b_is_processed = TRUE;
                break;
            }
            default:
                b_is_processed = FALSE;
                break;
        }

        if (ui4_keycode != BTN_WIDGET && ui4_keycode != BTN_NETFLIX && ui4_keycode != BTN_VUDU
            && ui4_keycode != BTN_AMAZON && ui4_keycode != BTN_XUMO && ui4_keycode != BTN_CRACKLE
            && ui4_keycode != BTN_HULU && ui4_keycode != BTN_IHEART_RADIO && ui4_keycode != BTN_CC
            && ui4_keycode != BTN_VOL_UP && ui4_keycode != BTN_VOL_DOWN &&ui4_keycode != BTN_WATCHFREE
            && ui4_keycode != BTN_REDBOX && ui4_keycode != BTN_HAYSTACK)
        {
            //prog key only useful when TV source
            if(ui4_keycode == BTN_PRG_UP||ui4_keycode == BTN_PRG_DOWN||ui4_keycode == BTN_PREV_PRG)
            {
                ISL_REC_T   t_isl_rec       ={0};
                UINT8       ui1_input_id    = 0;
                CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};

                a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                DBG_LOG_PRINT((C4TV_CUSTOM_LOG_PREFIX"%s %d failed!\n",__FUNCTION__,__LINE__));
                a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                DBG_LOG_PRINT((C4TV_CUSTOM_LOG_PREFIX"%s %d failed!\n",__FUNCTION__,__LINE__));
                a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                DBG_LOG_PRINT((C4TV_CUSTOM_LOG_PREFIX"%s %d failed!\n",__FUNCTION__,__LINE__));

                if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type || INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)
                {
                    DBG_LOG_PRINT(("Pass keycode %d to rest ap.\n", ui4_keycode));
                    rest_event_notify("key_command", ui4_keycode, "");
                }
                else
                    DBG_LOG_PRINT(("No need pass keycode %d to rest ap when TV.\n", ui4_keycode));
            }
            else
            {
                DBG_LOG_PRINT(("Pass keycode %d to rest ap.\n", ui4_keycode));
                rest_event_notify("key_command", ui4_keycode, "");
            }
        }

        // if a_rest_app_is_key_handler() return TRUE, means cut off the key routing flow here
        if (a_rest_app_is_key_handler(ui4_keycode) == 0)
        {
            DBG_INFO(("No need to further pass the key.\n", ui4_keycode));
            b_is_processed = TRUE;
        }
    }

    if (b_is_processed)
    {
        return C4TV_APRON_OK;
    }
    else
    {
        return C4TV_APRON_NOT_IMPLEMENT;
    }
}

INT32 c4tv_apron_custom_update_timezone_when_connect()
{
    //a_cfg_custom_get_timezone_idx(UINT8 * pui1_idx)
    return C4TV_APRON_OK;
}

INT32 c4tv_apron_custom_accept_tos()
{
    INT32 i4_ret = 0;

    if (a_tv_custom_get_tos()) {
        i4_ret = a_c4tv_apron_accept_tos();
    } else {
        i4_ret = C4TV_APRON_INV_STATE;
    }

    return i4_ret;
}

INT32 c4tv_apron_custom_update_time_format_when_connect()
{
    INT32 i4_ret = 0;
    UINT8 ui1_time_format = 0;
    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX" c4tv_apron_custom_update_time_format_when_connect \n"));
    i4_ret = a_cfg_cust_get_time_format(&ui1_time_format);
    if(i4_ret == 0)
    {

        if(ui1_time_format == USE_TIME_12H)
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX" SET AS 12h TIME format \n"));
            i4_ret = a_c4tv_apron_set_time_format(TRUE);

        }
        else if(ui1_time_format == USE_TIME_24H)
        {
             DBG_INFO((C4TV_CUSTOM_LOG_PREFIX" SET AS 24h TIME format \n"));
            i4_ret = a_c4tv_apron_set_time_format(FALSE);
        }
        else
        {
            i4_ret = C4TV_APRON_INTERNAL_ERROR;
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX" ui1_time_format:%d unkown time format,do nothing \n",ui1_time_format));
        }
    }
    else
    {
        DBG_INFO(("a_cfg_cust_get_time_format i4_ret=%d\r\n",i4_ret));
        i4_ret = C4TV_APRON_INTERNAL_ERROR;
    }
    return i4_ret;
}
VOID _c4tv_apron_custom_set_timezone(C4TV_APRON_CAST_STATUS *pt_cast_status)
{
    //BOOL b_timezone_idx_found = FALSE;
    INT32 index = 0, i = 0;
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;
    BOOL b_timezone_idx_found = FALSE;

    /* Timezone in Menu */
    /*
        "Hawaii (-10)", //0
        "Alaska (-9)",
        "Pacific (-8)",
        "Mountain (-7)",
        "Arizona (-7)",
        "Central (-6)",
        "Indiana (-5)",
        "Eastern (-5)",
        "Atlantic (-4)",
        "Newfoundland (-3.5)",
        "-3",
        "-2",
        "-1",
        "London (0)",
        "+1",
        "+2",
        "+3",
        "+4",
        "+5",
        "+6",
        "+7",
        "+8",
        "+9",
        "Guam (+10)",
        "+11",
        "+12",
        "-12",
        "-11", //27
    */

    struct cast_zone_map {
        CHAR *ps_cast_zone;
        INT32 i4_idx;
    } cast_zone_maps[] = {
        {"Pacific/Midway", 23},                 /* IDLW */ //change for new time zone standard
        {"Pacific/Honolulu", 0},                /* HST */
        {"America/Anchorage", 1},               /* AKST */
        {"America/Los_Angeles", 2},             /* PST */
        {"America/Vancouver", 2},               /* PST */
        {"America/Tijuana", 2},                 /* PST */
        {"America/Phoenix", 3},                 /* MST */
        {"America/Denver", 3},                  /* MST */
        {"America/Edmonton", 3},                /* MST */
        {"America/Chihuahua", 3},               /* MST */
        {"America/Regina", 4},                  /* CST */
        {"America/Costa_Rica", 4},              /* CST */
        {"America/Chicago", 4},                 /* CST */
        {"America/Mexico_City", 4},             /* CST */
        {"America/Winnipeg", 4},                /* CST */
        //{"America/Bogota", 5},
        {"America/New_York", 5},                /* EST */
        {"America/Toronto", 5},                 /* EST */
        {"America/Caracas", 6},                 /* AST */
        {"America/Barbados", 6},                /* AST */
        {"America/Halifax", 6},                 /* AST */
        {"America/Manaus", 6},                  /* AST */
        {"America/Santiago", 6},                /* AST */
        //{"America/St_Johns", 7},              /* GMT-3.5*/ remove for vizio spec change 5.4.1 
        {"America/Sao_Paulo", 7},               /* ART */
        {"America/Araguaina", 7},               /* ART */
        {"America/Argentina/Buenos_Aires", 7},  /* ART */
        {"America/Argentina/San_Luis", 7},      /* ART */
        {"America/Montevideo", 7},              /* ART */
        {"America/Godthab", 7},                 /* ART */
        {"Atlantic/South_Georgia", 8},          /* AT */
        {"Atlantic/Cape_Verde", 9},             /* WAT */
        {"Atlantic/Azores", 9},                 /* WAT */
        {"Africa/Casablanca", 10},              /* GMT */
        {"Europe/London", 10},                  /* GMT */
        {"Europe/Dublin", 10},                  /* GMT */
        {"Europe/Amsterdam", 11},               /* CET */
        {"Europe/Belgrade", 11},                /* CET */
        {"Europe/Berlin", 11},                  /* CET */
        {"Europe/Brussels", 11},                /* CET */
        {"Europe/Copenhagen", 11},              /* CET */
        {"Europe/Lisbon", 11},                  /* CET */
        {"Europe/Madrid", 11},                  /* CET */
        {"Europe/Oslo", 12},                    /* EET */
        {"Europe/Paris", 11},                   /* CET */
        {"Europe/Rome", 11},                    /* CET */
        {"Europe/Stockholm", 11},               /* CET */
        {"Europe/Sarajevo", 11},                /* CET */
        {"Europe/Vienna", 11},                  /* CET */
        {"Europe/Warsaw", 11},                  /* CET */
        {"Europe/Zurich", 11},                  /* CET */
        {"Africa/Windhoek", 12},                /* EET */
        {"Africa/Lagos", 11},                   /* CET */
        {"Africa/Brazzaville", 11},             /* CET */
        {"Africa/Cairo", 12},                   /* EET */
        {"Africa/Harare", 12},                  /* EET */
        {"Africa/Maputo", 12},                  /* EET */
        {"Africa/Johannesburg", 12},            /* EET */
        {"Europe/Helsinki", 12},                /* EET */
        {"Europe/Athens", 12},                  /* EET */
        {"Asia/Amman", 12},                     /* EET */
        {"Asia/Beirut", 12},                    /* EET */
        {"Asia/Jerusalem", 12},                 /* EET */
        {"Europe/Minsk", 13},                   /* MSK */
        {"Asia/Baghdad", 13},                   /* MSK */
        {"Asia/Riyadh", 13},                    /* MSK */
        {"Asia/Kuwait", 13},                    /* MSK */
        {"Africa/Nairobi", 13},                 /* MSK */
        {"Asia/Tehran", 13},                    /* MSK */
        {"Europe/Moscow", 13},                  /* MSK */
        {"Asia/Dubai", 14},                     /* AMT */
        {"Asia/Tbilisi", 14},                   /* AMT */
        {"Indian/Mauritius", 14},               /* AMT */
        {"Asia/Baku", 14},                      /* AMT */
        {"Asia/Yerevan", 14},                   /* AMT */
        {"Asia/Kabul", 14},                     /* AMT */
        {"Asia/Karachi", 15},                   /* PKT */
        {"Asia/Ashgabat", 15},                  /* PKT */
        {"Asia/Oral", 15},                      /* PKT */
        {"Asia/Kolkata", 15},                   /* PKT */
        {"Asia/Colombo", 15},                   /* PKT */
        {"Asia/Kathmandu", 15},                 /* PKT */
        {"Asia/Yekaterinburg", 15},             /* PKT */
        {"Asia/Almaty", 16},                    /* OMSK */
        {"Asia/Dhaka", 16},                     /* OMSK */
        {"Asia/Rangoon", 16},                   /* OMSK */
        {"Asia/Bangkok", 17},                   /* KRAT */
        {"Asia/Jakarta", 17},                   /* KRAT */
        {"Asia/Omsk", 16},                      /* OMSK */
        {"Asia/Novosibirsk", 17},               /* KRAT */
        {"Asia/Shanghai", 18},                  /* CST */
        {"Asia/Hong_Kong", 18},                 /* CST */
        {"Asia/Kuala_Lumpur", 18},              /* CST */
        {"Asia/Singapore", 18},                 /* CST */
        {"Asia/Manila", 18},                    /* CST */
        {"Asia/Taipei", 18},                    /* CST */
        {"Asia/Makassar", 18},                  /* CST */
        {"Asia/Krasnoyarsk", 17},               /* KRAT */
        {"Australia/Perth", 18},                /* CST */
        {"Australia/Eucla", 18},                /* CST */
        {"Asia/Irkutsk", 18},                   /* CST */
        {"Asia/Seoul", 19},                     /* JST */
        {"Asia/Tokyo", 19},                     /* JST */
        {"Asia/Jayapura", 19},                  /* JST */
        {"Australia/Adelaide", 19},             /* JST */
        {"Australia/Darwin", 19},               /* JST */
        {"Australia/Brisbane", 20},             /* AEST */
        {"Australia/Hobart", 20},               /* AEST */
        {"Australia/Sydney", 20},               /* AEST */
        {"Asia/Yakutsk", 19},                   /* JST */
        {"Pacific/Guam", 20},                   /* AEST */
        {"Pacific/Port_Moresby", 20},           /* AEST */
        {"Asia/Vladivostok", 20},               /* AEST */
        {"Asia/Sakhalin", 21},                  /* SAKT */
        {"Asia/Magadan", 21},                   /* SAKT */
        {"Pacific/Auckland", 22},               /* NZST */
        {"Pacific/Fiji", 22},                   /* NZST */
        {"Pacific/Majuro", 22},                 /* NZST */
        {"Pacific/Tongatapu", 23},              /* IDLW */
        {"Pacific/Apia", 23},                   /* IDLW */
        {"Pacific/Kiritimati", 24}              /* NT */
    };
    CHAR *str_cast_zone_wo_dst[]={
        "Etc/GMT+10",
        "Etc/GMT+9",
        "Etc/GMT+8",
        "Etc/GMT+7",
        //"Etc/GMT+7",
        "Etc/GMT+6",
        //"Etc/GMT+5",
        "Etc/GMT+5",
        "Etc/GMT+4",
        //"Etc/GMT+3.5",
        "Etc/GMT+3",
        "Etc/GMT+2",
        "Etc/GMT+1",
        "Etc/GMT",
        "Etc/GMT-1",
        "Etc/GMT-2",
        "Etc/GMT-3",
        "Etc/GMT-4",
        "Etc/GMT-5",
        "Etc/GMT-6",
        "Etc/GMT-7",
        "Etc/GMT-8",
        "Etc/GMT-9",
        "Etc/GMT-10",
        "Etc/GMT-11",
        "Etc/GMT-12",
        "Etc/GMT+12",
        "Etc/GMT+11",
    };
    DBG_INFO(("%s,%d num:%d \r\n",__FUNCTION__, __LINE__,sizeof(cast_zone_maps)/sizeof(cast_zone_maps[0])));
    for(i = 0;i<sizeof(cast_zone_maps)/sizeof(cast_zone_maps[0]);i++)
    {
        if(c_strncmp(pt_cast_status->e_setup_status.ps_timezone, cast_zone_maps[i].ps_cast_zone, 32) == 0)
        {
            b_timezone_idx_found = TRUE;
            index = cast_zone_maps[i].i4_idx;
            break;
        }
    }
    if(!b_timezone_idx_found)
    {
    		return;
    }
    else
    {
        for(i = 0;i<sizeof(str_cast_zone_wo_dst)/sizeof(str_cast_zone_wo_dst[0]);i++)
        {
            if(c_strncmp(pt_cast_status->e_setup_status.ps_timezone, str_cast_zone_wo_dst[i], 32) == 0)
            {
                b_timezone_idx_found = TRUE;
                index = i;
                break;
            }

        }
    }

    DBG_INFO(("%s,%d index:%d \r\n",__FUNCTION__, __LINE__,index));
    a_cfg_get_time_zone_data(&t_tz_offset,&b_dls);
    switch (index)
    {
    case 0:
        t_tz_offset = -10  * 3600;      /* HST */  //change for new time zone standard (DTV02194418)
        break;
    case 1:
        t_tz_offset = -9   * 3600;      /* AKST */
        break;
    case 2:
        t_tz_offset = -8   * 3600;      /* PST(default)*/
        break;
    case 3:
        t_tz_offset = -7   * 3600;      /* MST */
        break;
    case 4:
        t_tz_offset = -6   * 3600;      /* CST */
        break;
    case 5:
        t_tz_offset = -5   * 3600;      /* EST */
        break;
    case 6:
        t_tz_offset = -4   * 3600;      /* AST */
        break;
    case 7:
        t_tz_offset = -3  * 3600;      /* ART */
       break;
    case 8:
        t_tz_offset = -2  * 3600;      /* AT */
        break;
    case 9:
        t_tz_offset = -1   * 3600;      /* WAT */
        break;
    case 10:
        t_tz_offset = 0   * 3600;      /* GMT */
        break;
    case 11:
        t_tz_offset = 1   * 3600;      /* CET */
        break;
    case 12:
        t_tz_offset = 2   * 3600;      /* EET */
        break;
    case 13:
        t_tz_offset = 3   * 3600;      /* MSK */
        break;
    case 14:
        t_tz_offset = 4   * 3600;      /* AMT */
        break;
    case 15:
        t_tz_offset = 5   * 3600;      /* PKT */
        break;
    case 16:
        t_tz_offset = 6   * 3600;      /* OMSK */
       break;
    case 17:
        t_tz_offset = 7  * 3600;       /* KRAT */
       break;
    case 18:
        t_tz_offset = 8  * 3600;       /* CST */
        break;
    case 19:
        t_tz_offset = 9   * 3600;      /* JST */
        break;
    case 20:
        t_tz_offset = 10   * 3600;     /* AEST */
        break;
    case 21:
        t_tz_offset = 11   * 3600;     /* SAKT */
        break;
    case 22:
        t_tz_offset = 12   * 3600;     /* NZST */
        break;
    case 23:
        t_tz_offset = -12   * 3600;    /* IDLW */
        break;
    case 24:
        t_tz_offset = -11   * 3600;     /* NT */
        break;
    default:
        index  = 2;
        t_tz_offset = -8   * 3600;      /* PST(default) */
        break;
    }

    a_cfg_set_time_zone_data(t_tz_offset, b_dls);
    a_cfg_custom_set_timezone_idx(index);
    a_cfg_update_time_zone();

}
INT32 c4tv_apron_custom_copy_cast_status(C4TV_APRON_CAST_STATUS *pt_cast_status)
{
    INT32       i4_len = 0, i4_ret = 0;;
    CHAR        s_cast_name[25+1]={0};
    CHAR        s_cast_name_ex[32+1]={0};
    UINT32      ui4_cast_name_len = 32+1;
    UINT8       time_format;
    CHAR        *ps_locale;
    ISO_639_LANG_T*  ps639_lang;
    ISO_639_LANG_T s639_crnt_lang;
    if(pt_cast_status != NULL)
    {
        i4_len = a_cfg_custom_get_cast_name(s_cast_name_ex, &ui4_cast_name_len);
        if(i4_len != 0)
        {
            DBG_INFO(("%s,%d [get cast name fail] \r\n",__FUNCTION__, __LINE__ ));
        }

        if(c_strncmp(s_cast_name_ex, pt_cast_status->ps_cast_name, 32) != 0)
        {
            i4_len = c_strlen(pt_cast_status->ps_cast_name);
            if(i4_len <= 21)
            {
                c_strncpy(s_cast_name, pt_cast_status->ps_cast_name, c_strlen(pt_cast_status->ps_cast_name));
                a_cfg_custom_set_cast_name(s_cast_name);
            }
            else
            {
                c_strncpy(s_cast_name, pt_cast_status->ps_cast_name, 25);
                a_cfg_custom_set_cast_name(s_cast_name);
            }
        }
               /*GUI language*/
        ps_locale = pt_cast_status->e_setup_status.ps_locale;
        if(c_strncmp(ps_locale, s639_app_cfg_lang_fra, 2) == 0)
        {
            ps639_lang = &s639_app_cfg_lang_fre;
        }
        else if (c_strncmp(ps_locale, s639_app_cfg_lang_esl, 2) == 0 ||
                 c_strncmp(ps_locale, s639_app_cfg_lang_spa, 2) == 0)
        {
            ps639_lang = &s639_app_cfg_lang_spa;
        }
        else
        {
            ps639_lang = &s639_app_cfg_lang_eng;
        }
        a_cfg_get_gui_lang(s639_crnt_lang);
        if (c_strncmp(s639_crnt_lang, *ps639_lang, ISO_639_LANG_LEN) != 0)
        {
            a_cfg_set_gui_lang(*ps639_lang);
        }
        /* Time format */
        i4_ret = a_cfg_cust_get_time_format(&time_format); /* time_format=0(12hr), time_format=1(24hr) */
        if(i4_ret == 0)
        {
            if((!time_format) != pt_cast_status->e_setup_status.b_time_in_12_hour_format)
            {
                if(pt_cast_status->e_setup_status.b_time_in_12_hour_format)
                {
                    a_cfg_cust_set_time_format((UINT8)0);
                }
                else
                {
                    a_cfg_cust_set_time_format((UINT8)1);
                }
            }
        }
        /* Timezone */
        _c4tv_apron_custom_set_timezone(pt_cast_status);
        DBG_INFO(("%s,%d b_time_in_12_hour_format:%d \r\n",__FUNCTION__, __LINE__,pt_cast_status->e_setup_status.b_time_in_12_hour_format ));
        DBG_INFO(("%s,%d ps_timezone:%s \r\n",__FUNCTION__, __LINE__,pt_cast_status->e_setup_status.ps_timezone ));
    }

    return C4TV_APRON_OK;
}

VOID c4tv_apron_custom_notify_after_grant_resource()
{
    DBG_INFO(("[C4TV_APRON] c4tv_apron_custom_notify_after_grant_resource\r\n"));
    a_rest_notify_after_grant_resource();
    return;
}

VOID c4tv_apron_custom_notify_on_receiving_grant_resource()
{
    DBG_INFO(("[C4TV_APRON] c4tv_apron_custom_notify_on_receiving_grant_resource\r\n"));
    a_rest_notify_on_receiving_request_resource();
    return;
}

INT32 c4tv_apron_custom_handle_force_update_finish()
{
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;

    a_cfg_get_wzd_status(&ui2_status);
    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);

    if (WZD_STATE_RESUME_C4TV == ui1_state)
    {
        DBG_INFO(("[C4TV_APRON_TEST] c4tv_apron_custom_handle_force_update_finish Resume wzd"));
        /* resume wizard*/
        a_wzd_resume_c4tv(ui1_state,ui1_page_idx);
    }

    /*check enter wizad*/
    return C4TV_APRON_OK;
}

BOOL c4tv_apron_custom_check_current_can_enter_cast_status()
{
    PCL_WAKEUP_KEY_T        t_wakeup_key = {0};
    PCL_WAKE_UP_REASON_T    e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
    INT32                   i4_ret = PCLR_OK;

    if (a_wzd_is_oobe_mode()) {
        return FALSE;
    }

    do {
        i4_ret = c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);
        if (PCLR_OK != i4_ret || PCL_WAKE_UP_REASON_IRRC != e_wakeup_reason)
        {
            break;
        }

        i4_ret = c_pcl_get_wakeup_irkey(&t_wakeup_key);
        if (PCLR_OK != i4_ret)
        {
            break;
        }
        if (PCL_WAKEUP_KEY_HOTKEY == t_wakeup_key.e_key_type && BTN_NETFLIX == t_wakeup_key.ui4_wakeupkey)
        {
            return FALSE;
        }
    } while (0);

    if (PCL_WAKE_UP_REASON_CAST == e_wakeup_reason)
    {
        return TRUE;
    }

    if (a_rest_app_get_current_app_need_cast_shell() != 0) {
        DBG_INFO(("[c4tv_apron] Not allow auto grant resource to cast_shell triggered by control connected bcuz current app does not need\n\r"));
        return FALSE;
    }
#if 0
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;

    a_cfg_get_wzd_status(&ui2_status);
    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    if (WZD_STATE_RESUME_C4TV == ui1_state)
    {
        DBG_LOG_PRINT(("[C4TV_APRON_TEST] c4tv_apron_custom_check_current_can_enter_cast_status Reject[WZD]"));
        return FALSE;
    }
    else
    {
    return TRUE;
}
#endif
    return TRUE;
}

BOOL c4tv_apron_custom_check_current_status_allow_change_channel()
{
   //return TRUE; will allow change channel/source in cast status,and cast exit.
   //return FALSE;will not allow change channel/source in cast status.keep in cast.

    INT32   i4_ret        = 0;
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_index     = 0;

    i4_ret = a_cfg_get_wzd_status(&ui2_status);
    if (APP_CFGR_OK != i4_ret)
    {
        return TRUE;
    }
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_index = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    if (WZD_STATE_RESUME_C4TV == ui1_state && ui1_index != WZD_PAGE_INDEX_C4TV_STORE_DEMO) /*OOBE can't allow change channel */
    {
        return FALSE;
    }

    if (a_rest_app_avoid_revoke_resource() == 0)
    {
        return FALSE;
    }

    return TRUE;
}

INT32 c4tv_apron_custom_exit_cast_default_handle(C4TV_APRON_T *pt_c4tv_apron)
{
    ISL_REC_T   t_isl_rec = {0};
    INT32       i4_ret;

    pt_c4tv_apron->e_type = C4TV_APRON_TYPE_UNKNOWN;
    pt_c4tv_apron->b_is_cec_one_touch = FALSE; //CEC one touch,just play the orgn svc;

    //restart orign svc
    i4_ret =  nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
    if (NAVR_OK != i4_ret) {
        return C4TV_APRON_NOT_IMPLEMENT;
    }

    if (nav_is_channel_scan_active() == FALSE)
    {
        if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
        {
            DBG_INFO(("[c4tv_apron] c4tv_apron_custom_exit_cast_default_handle() will not change inp because of current source is cast\n\r"));
        }
        else if (FALSE == a_wzd_is_resume() ||_c4tv_apron_custom_retail_mode_is_on())
        {
            nav_change_av_inp_by_rec(TV_WIN_ID_MAIN, &t_isl_rec, NULL);
        }
        else
        {
            DBG_INFO((C4TV_CUSTOM_LOG_PREFIX"a_wzd_is_resume. do nothing\n"));
        }
    }
    else
    {
        DBG_INFO(("[c4tv_apron] c4tv_apron_custom_exit_cast_default_handle() will not select crnt_channel because of scan\n\r"));
    }

    return C4TV_APRON_OK;
}

VOID c4tv_apron_custom_enter_cast_custom_handle(VOID)
{
    MTOSD_PLA_Enable(0, FALSE);
    DBG_LOG_PRINT(("[c4tv_apron] c4tv_apron_custom_enter_cast_custom_handle- DISABLE OSD1\n\r"));
    //MTOSD_PLA_Enable(2, TRUE);
    //DBG_LOG_PRINT(("[c4tv_apron] c4tv_apron_custom_enter_cast_custom_handle- ENABLE OSD3\n\r"));
    return;
}

VOID c4tv_apron_custom_exit_cast_custom_handle(VOID)
{
    DBG_LOG_PRINT(("[c4tv_apron] c4tv_apron_custom_enter_cast_custom_handle- call custom ClearNativeWindowByFb\n"));
    c4tv_apron_custom_flush_cast_osd();

    MTOSD_PLA_Enable(2, FALSE);
    DBG_LOG_PRINT(("[c4tv_apron] c4tv_apron_custom_enter_cast_custom_handle- DISABLE OSD3\n"));
    MTOSD_PLA_Enable(0, TRUE);
    DBG_LOG_PRINT(("[c4tv_apron] c4tv_apron_custom_enter_cast_custom_handle- ENABLE OSD1\n\r"));
    return;
}

INT32 c4tv_apron_custom_init()
{

    DBG_INFO((C4TV_CUSTOM_LOG_PREFIX" c4tv_apron_custom_init \n"));

    INT32  i4_ret = 0;
    UINT16 ui2_icl_nfy_id = 0;

    i4_ret = a_icl_notify_reg(ICL_GRPID_ULI_DOWNLOAD_STATUS,
                              128,
                              NULL,
                              NULL,
                              _c4tv_custom_icl_nfy_func,
                              &ui2_icl_nfy_id);
    if ( ICLR_OK != i4_ret )
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"a_icl_notify_reg failed !!!!\n"));
    }


    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_NAV,
                              NULL,
                              _c4tv_apron_cfg_nfy_func,
                              &ui2_cfg_nfy_id);

    if ( ICLR_OK != i4_ret )
    {
        ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"a_cfg_notify_reg failed !!!!\n"));
    }

    i4_ret = c4tv_apron_custom_view_init();
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((C4TV_CUSTOM_LOG_PREFIX"c4tv_apron_custom_view_init failed !!!!\n"));
    }

    return C4TV_APRON_OK;
}

extern INT32 a_bgm_exit_active_standby_with_wakeup_reason(PCL_WAKE_UP_REASON_T e_wakeup_reason);

//wake_up_reason:
//PCL_WAKE_UP_REASON_CUSTOM_1: wakeup TV for endpoint "app/launch"
//PCL_WAKE_UP_REASON_CUSTOM_4: wakeup TV for endpoint "pairing/start"
INT32 c4tv_arpon_wakeup_tv(PCL_WAKE_UP_REASON_T wake_up_reason)
{
    DBG_LOG_PRINT(("c4tv_arpon_wakeup_tv %d\r\n", wake_up_reason));
    BGM_STATE_T state = bgm_get_state();
    DBG_INFO(("wake up tv current state = %d\r\n",state));
    if(BGM_STATE_PRE_RUNNING == state ||
       BGM_STATE_RUNNING     == state ||
       BGM_STATE_COMPLETE    == state)
    {
        return a_bgm_exit_active_standby_with_wakeup_reason(wake_up_reason);
    }
    return C4TV_APRON_OK;
}


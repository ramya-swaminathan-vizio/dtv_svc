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
 * $RCSfile: download_util.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  Xuan Zhang$
 * $MD5HEX:  $
 *
 * Description:
 *         download utility
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#ifdef APP_DYNAMIC_TOS_SUPPORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cJSON.h>


#include "u_common.h"
#include "c_os.h"
#include "c_dbg.h"
#include "c_fm.h"

#include "curl/curl.h"
#include "curl/easy.h"

#include "app_util/download_util/a_download_util.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#define MAX_CONN_TIMEOUT        30
#define MAX_DOWNLOAD_TIMEOUT    300

#define MIN_DOWNLOAD_FILE_SIZE  (1024)

#undef  DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE DBG_LEVEL_ALL

/*Example:
  /3rd/bin/wget --no-check-certificate \
  http://api.digitalhomeservices.yahoo.com/V0_3/legaldocs?doctype=tos&region=US&language=en&format=text */

CHAR* ps_doctype_tos        = "tos";
CHAR* ps_doctype_privacy    = "privacy";

CHAR* ps_lang_eng           = "en";
CHAR* ps_lang_fre           = "fr-CA";
CHAR* ps_lang_spa           = "es-MX";

CHAR* ps_tos_url_prefix     = "http://api.digitalhomeservices.yahoo.com";
CHAR* ps_tos_url_ver        = "V0_3";
CHAR* ps_tos_url_format     = "text";

CHAR* ps_tos_dir            = "/data/tos";
CHAR* ps_vpp_dir            = "/data/vpp";
CHAR* ps_policy_dir         = "/data/vizio-policy";
//CHAR* ps_tos_dir          = "/tmp/tos";
CHAR* ps_tos_contert_temp   = "/tmp/convert_tos.txt";


static SIZE_T _write_data(VOID *pv_data, SIZE_T z_size, SIZE_T z_nmemb, FILE *pf_stream);
static VOID*  _tos_download_util_thread(VOID * pv_data);

static pthread_t gh_tos_download_util_thread = 0 ;
static pthread_t g_h_download_util_thread = 0;

/* before download should clear env after power on */
static BOOL     b_is_need_clean_env = TRUE ;
static BOOL     b_is_need_clean_env_ex = TRUE ;

static INT32 _get_tos_download_url (const TOS_TYPE_T e_type, CHAR* ps_cmd)
{
    CHAR    s_doctype[8] = {0};
    CHAR    s_language[6] = {0};

    if (!ps_cmd || TOS_TYPE_LAST_VALID_ITEM == e_type)
    {
        DBG_ERROR(("[TOS][ERROR]INVALID ITEM: FUNC:%s LINE:%d.\n",__FUNCTION__,__LINE__));
        return DUR_INV_ARG;
    }

    switch (e_type)
    {
        case TOS_TYPE_TOS_ENG:
            c_strcpy(s_doctype, ps_doctype_tos);
            c_strcpy(s_language, ps_lang_eng);
            break;
        case TOS_TYPE_TOS_FRE:
            c_strcpy(s_doctype, ps_doctype_tos);
            c_strcpy(s_language, ps_lang_fre);
            break;
        case TOS_TYPE_TOS_SPA:
            c_strcpy(s_doctype, ps_doctype_tos);
            c_strcpy(s_language, ps_lang_spa);
            break;
        case TOS_TYPE_PRIVACY_ENG:
            c_strcpy(s_doctype, ps_doctype_privacy);
            c_strcpy(s_language, ps_lang_eng);
            break;
        case TOS_TYPE_PRIVACY_FRE:
            c_strcpy(s_doctype, ps_doctype_privacy);
            c_strcpy(s_language, ps_lang_fre);
            break;
        case TOS_TYPE_PRIVACY_SPA:
            c_strcpy(s_doctype, ps_doctype_privacy);
            c_strcpy(s_language, ps_lang_spa);
            break;
        default:
            break;
    }

    c_sprintf(ps_cmd, "%s/%s/legaldocs?doctype=%s&region=US&language=%s&format=%s",
              ps_tos_url_prefix, ps_tos_url_ver,
              s_doctype, s_language,
              ps_tos_url_format);


    DBG_INFO(("[TOS][INFO] Get TOS download CMD: %s\n", ps_cmd));

    return DUR_OK;
}

static INT32 _get_tos_download_buf_file_path(const TOS_TYPE_T e_type, CHAR* ps_buf_path)
{
    CHAR    s_tos_name[128] = {0};

    /*
        yahoo_tos_in_eng.txt.buf
        yahoo_privacy_policy_in_eng.txt.buf
    */

    if (!ps_buf_path || TOS_TYPE_LAST_VALID_ITEM == e_type)
    {
        DBG_ERROR(("[TOS][ERROR]INVALID ITEM: FUNC:%s LINE:%d.\n",__FUNCTION__,__LINE__));
        return DUR_INV_ARG;
    }

    switch (e_type)
    {
        case TOS_TYPE_TOS_ENG:
            c_strcpy(s_tos_name, "yahoo_tos_in_eng.txt");
            break;
        case TOS_TYPE_TOS_FRE:
            c_strcpy(s_tos_name, "yahoo_tos_in_fre.txt");
            break;
        case TOS_TYPE_TOS_SPA:
            c_strcpy(s_tos_name, "yahoo_tos_in_spa.txt");
            break;
        case TOS_TYPE_PRIVACY_ENG:
            c_strcpy(s_tos_name, "yahoo_privacy_policy_in_eng.txt");
            break;
        case TOS_TYPE_PRIVACY_FRE:
            c_strcpy(s_tos_name, "yahoo_privacy_policy_in_fre.txt");
            break;
        case TOS_TYPE_PRIVACY_SPA:
            c_strcpy(s_tos_name, "yahoo_privacy_policy_in_spa.txt");
            break;
        default:
            break;
    }

    c_sprintf(ps_buf_path, "/tmp/%s.buf", s_tos_name);

    DBG_INFO(("[TOS][INFO] Get TOS download buffer path. %s %s\n",
                __FUNCTION__, ps_buf_path));

    return DUR_OK;
}

static INT32 _get_tos_download_target_file_path(const TOS_TYPE_T e_type, CHAR* ps_buf_path)
{
    CHAR    s_tos_name[128] = {0};

    /*
        yahoo_tos_in_eng.txt
        yahoo_privacy_policy_in_eng.txt
    */

    if (!ps_buf_path || TOS_TYPE_LAST_VALID_ITEM == e_type)
    {
        DBG_ERROR(("[TOS][ERROR]INVALID ITEM: FUNC:%s LINE:%d.\n",__FUNCTION__,__LINE__));
        return DUR_INV_ARG;
    }

    switch (e_type)
    {
        case TOS_TYPE_TOS_ENG:
            c_strcpy(s_tos_name, "yahoo_tos_in_eng.txt");
            break;
        case TOS_TYPE_TOS_FRE:
            c_strcpy(s_tos_name, "yahoo_tos_in_fre.txt");
            break;
        case TOS_TYPE_TOS_SPA:
            c_strcpy(s_tos_name, "yahoo_tos_in_spa.txt");
            break;
        case TOS_TYPE_PRIVACY_ENG:
            c_strcpy(s_tos_name, "yahoo_privacy_policy_in_eng.txt");
            break;
        case TOS_TYPE_PRIVACY_FRE:
            c_strcpy(s_tos_name, "yahoo_privacy_policy_in_fre.txt");
            break;
        case TOS_TYPE_PRIVACY_SPA:
            c_strcpy(s_tos_name, "yahoo_privacy_policy_in_spa.txt");
            break;
        default:
            break;
    }

    c_sprintf(ps_buf_path, "%s/%s", ps_tos_dir, s_tos_name);

    DBG_INFO(("[TOS][INFO] Get TOS download target path. %s %s\n",
                __FUNCTION__, ps_buf_path));

    return DUR_OK;
}

static INT32 _set_tos_download_icl_flag (const BOOL b_flag)
{
    UINT8   ui1_val = b_flag ? ICL_TOS_DOWNLOAD_ITEM_RUNNING : ICL_TOS_DOWNLOAD_ITEM_STOP;
    SIZE_T  z_size  = ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS_SIZE;

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS),
              &ui1_val, z_size);

    return DUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:  _write_data
 *
 * Description: callback function for download
 *
 * Inputs:  pv_data: the data for write
 *          ui4_size: block size
 *          ui4_nmemb: block number
 *          pv_stream: pointer to my handle
 *
 * Outputs: received data bytes
 *
 * Returns: received data bytes
 ----------------------------------------------------------------------------*/
static SIZE_T _write_data(VOID *pv_data, SIZE_T z_size, SIZE_T z_nmemb, FILE *pf_stream)
{
    SIZE_T written = fwrite(pv_data, z_size, z_nmemb, pf_stream);
    DBG_LOG_PRINT(("[VPP][%s,%d ] ####write len = %d data:\n ####%s####\n",__FUNCTION__,__LINE__, written,(CHAR*)pv_data));
    return (z_size*z_nmemb);
}

/*-----------------------------------------------------------------------------
 * Name:  _progress_download_func
 *
 * Description: callback function for tos download progress
 *
 * Inputs:  pv_data:
 *          d_total: the total number of bytes libcurl expects to download in this transfer.
 *          d_now: 	 the numbers of bytes downloaded so far.
 *          u_total: the total number of bytes liccurl expects to upload in this transfer.
 *			u_now:   the number of bytes uploaded so far.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static int _progress_download_func(VOID *pv_data,
                                   DOUBLE d_total, /* dltotal */
                                   DOUBLE d_now,   /* dlnow */
                                   DOUBLE u_total,
                                   DOUBLE u_now)
{
	DBG_LOG_PRINT(("\n[TOS][INFO]%s(%d) d_total = %lf, d_now = %lf\n",__FUNCTION__,__LINE__, d_total, d_now));
    return 0;
}

static VOID* _tos_download_util_thread(VOID* pv_data)
{
    CURL*       pt_curl = NULL;
    CURLcode    e_res ;
    DOUBLE      ui8_speed = 0;
    DOUBLE      ui8_time = 0;
    DOUBLE      ui8_size = 0;
    CHAR        s_url[255] = {0};
    CHAR        s_buf_path[255] = {0};
    CHAR        s_target_path[255] = {0};
    CHAR        s_cmd[255] = {0};
    FILE*       fl = NULL;
    BOOL        b_ret = FALSE;
    INT32       i4_file_len = 0, i4_pre_file_len = 0;
    INT32       i4_ret = 0;

    TOS_TYPE_T  e_tos_type = (TOS_TYPE_T)pv_data;

    DBG_LOG_PRINT(("[TOS][INFO] %s start! %d   e_tos_type: %d.\n", __FUNCTION__, __LINE__, e_tos_type));

    do
    {
    	pthread_detach(pthread_self());

        /* get download url with tos type */
        i4_ret = _get_tos_download_url(e_tos_type, s_url);
        if (DUR_OK != i4_ret)
        {
            break;
        }

        /* get download file path with tos type*/
        i4_ret = _get_tos_download_buf_file_path(e_tos_type, s_buf_path);
        if (DUR_OK != i4_ret)
        {
            break;
        }

        /* get download file path with tos type*/
        i4_ret = _get_tos_download_target_file_path(e_tos_type, s_target_path);
        if (DUR_OK != i4_ret)
        {
            break;
        }

        /* check the tmp path is exist or not */
        if (0 == access(ps_tos_dir, 0))
        {
            if (b_is_need_clean_env)
            {
                b_is_need_clean_env = FALSE;

                c_sprintf(s_cmd, "rm %s/* ", ps_tos_dir);
                AP_SYSTEM_CALL(s_cmd);

                DBG_LOG_PRINT(("[TOS][INFO] Cleanup environment.\n"));

                AP_SYSTEM_CALL("sync");
            }
        }
        else
        {
            c_sprintf(s_cmd, "%s %s", "mkdir -p ", ps_tos_dir);
            AP_SYSTEM_CALL_EX(s_cmd,i4_ret);

            DBG_LOG_PRINT(("\n%s Make temp dir: %s, i4_ret=%d\n", __FUNCTION__, s_cmd, i4_ret));
            DBG_LOG_PRINT(("\n%s WIFEXITED=%d\n", __FUNCTION__, s_cmd, WIFEXITED(i4_ret)));
            DBG_LOG_PRINT(("\n%s WEXITSTATUS=%d\n", __FUNCTION__, s_cmd, WEXITSTATUS(i4_ret)));

            if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
            {
                /* do nothing */
            }
            else
            {
                DBG_LOG_PRINT(("\n%s Make temp dir FAIL!\n", __FUNCTION__));
                break;
            }

            /* do not need to clean up anymore */
            b_is_need_clean_env = FALSE;
        }

        /* check the tos file is exist or not and check the file size */
        fl = fopen(s_target_path, "r");
        if (fl != NULL)
        {
            /* check file size, if exist and file size > 0, skip download */
            i4_ret = fseek(fl, 0, SEEK_END);
            i4_pre_file_len = ftell(fl);

            fclose(fl);
            fl = NULL;

            DBG_LOG_PRINT(("[TOS][INFO] File size = %ld Return : %d.\n", i4_pre_file_len, i4_ret));

            if (i4_ret == 0 && i4_pre_file_len > MIN_DOWNLOAD_FILE_SIZE)
            {
                b_ret = TRUE;
                break;
            }
        }

        /* start to create and download tos file */
        fl = fopen(s_buf_path, "w+");
        if (fl == NULL)
        {
            DBG_ERROR(("download file handle open error."));
            break;
        }

        pt_curl = curl_easy_init();
        if (pt_curl == NULL)
        {
            DBG_ERROR(("curl_easy_init fail"));
            break;
        }
        else
        {
            /* broadcast file download start */
            _set_tos_download_icl_flag(TRUE);

            /* First set the URL that is about to receive our POST. This URL can
               just as well be a https:// URL if that is what should receive the
               data. */
            e_res = curl_easy_setopt(pt_curl, CURLOPT_URL, s_url);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set URL fail! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_SSL_VERIFYPEER, 0L);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set NO verification failed! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_SSL_VERIFYHOST, 0L);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set NO check host failed! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_MAXREDIRS, 5);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set NO verification failed! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_FOLLOWLOCATION, 1);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set NO check host failed! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_PROGRESSFUNCTION, _progress_download_func);
    	    if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set progress function fail! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_CONNECTTIMEOUT, MAX_CONN_TIMEOUT);
    	    if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set connect timeout function fail! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_TIMEOUT, MAX_DOWNLOAD_TIMEOUT);
    	    if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set progress function fail! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_WRITEFUNCTION, _write_data);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set write function fail! res = %d", e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_WRITEDATA, fl);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set write data fail! res = %d", e_res));
                break;
            }

    		e_res = curl_easy_setopt(pt_curl, CURLOPT_NOPROGRESS, 0L);
    	    if (CURLE_OK != e_res)
            {
                DBG_ERROR(("set no progress fail! res = %d", e_res));
                break;
            }

            /* Perform the request, res will get the return code */
            e_res = curl_easy_perform(pt_curl);

            DBG_LOG_PRINT(("\n####%s(%d)download return code: %d.\n",__FUNCTION__,__LINE__,e_res));

            if (CURLE_WRITE_ERROR == e_res)
            {
                DBG_ERROR(("CURLE_WRITE_ERROR %s\n", __FUNCTION__));
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_SIZE_DOWNLOAD , &ui8_size);
            if  (CURLE_OK != e_res)
            {
                DBG_ERROR(("get download size fail! res = %d\n", e_res));
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_TOTAL_TIME , &ui8_time);
            if  (CURLE_OK != e_res)
            {
                DBG_ERROR(("get download size fail! res = %d\n", e_res));
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_SPEED_DOWNLOAD , &ui8_speed);
            if  (CURLE_OK != e_res)
            {
                DBG_ERROR(("get download speed fail! res = %d\n", e_res));
                break;
            }

            fflush(fl);

            /* check file size, if exist and file size > 0, skip download */
            i4_ret = fseek(fl, 0, SEEK_END);
            i4_file_len = ftell(fl);

            DBG_LOG_PRINT(("download time  = %.3f sec.\n", ui8_time));
            DBG_LOG_PRINT(("download speed = %.3f bytes/sec.\n", ui8_speed));
            DBG_LOG_PRINT(("download size  = %.0f bytes.\n", ui8_size));
            DBG_LOG_PRINT(("download file  = %ld bytes.\n", i4_file_len));

            b_ret = TRUE;
        }
    }while(0);


    if (b_ret)
    {
        if (i4_file_len > MIN_DOWNLOAD_FILE_SIZE)
        {
            DBG_LOG_PRINT(("[TOS][INFO] Start fomart json to text.\n"));

            /* open txt file with UTF-8, add three char to DOM */
            c_sprintf(s_cmd, "echo \"  \" > %s", ps_tos_contert_temp);
            AP_SYSTEM_CALL(s_cmd);

            /* get tos title */
            c_sprintf(s_cmd, "sed -e \':label;N;s/\\n/LOOOOOK/;b label\' %s | awk -F\"<title>|</title>\" \'{print $2}\' | sed -e \'s/LOOOOOK/\\n/g\' >> %s", s_buf_path, ps_tos_contert_temp);
            AP_SYSTEM_CALL(s_cmd);

            /* add a new blank line after TITLE */
            c_sprintf(s_cmd, "echo \" \" >> %s", ps_tos_contert_temp);
            AP_SYSTEM_CALL(s_cmd);

            /* get tos content */
            c_sprintf(s_cmd, "sed -e \':label;N;s/\\n/LOOOOOK/;b label\' %s | awk -F\"<answer>|</answer>\" \'{print $2}\' | sed -e \'s/LOOOOOK/\\n/g\' >> %s", s_buf_path, ps_tos_contert_temp);
            AP_SYSTEM_CALL(s_cmd);

            /* save file to target path */
            c_sprintf(s_cmd, "mv %s %s", ps_tos_contert_temp, s_target_path);
            AP_SYSTEM_CALL(s_cmd);

            AP_SYSTEM_CALL("sync; sync; sync");
        }
        else if (i4_pre_file_len > MIN_DOWNLOAD_FILE_SIZE)
        {
            DBG_LOG_PRINT(("[TOS][INFO] File is already exist! \n"));
        }
        else
        {
            DBG_LOG_PRINT(("[TOS][INFO]%s(%d)download file failed.\n", __FUNCTION__,__LINE__));
        }
    }
    else
    {
        DBG_LOG_PRINT(("[TOS][INFO]%s(%d)download file failed.\n", __FUNCTION__,__LINE__));
    }

    /* cleanup buffer file */
    c_sprintf(s_cmd, "rm %s", s_buf_path);
    AP_SYSTEM_CALL(s_cmd);

    /* always cleanup */
    if (pt_curl != NULL)
    {
        curl_easy_cleanup(pt_curl);
    }

    /* close file handle */
    if (fl != NULL)
    {
        fclose(fl);
    }

    /* broadcast file download finish */
    _set_tos_download_icl_flag(FALSE);

    /* exit the thread*/
    pthread_exit(NULL);

    return NULL;
}

/*-----------------------------------------------------------------------------
 * Name:  a_tos_get_file_path
 *
 * Description: get the tos file path by type
 *
 * Inputs:  e_type          TOS type
 *
 * Outputs: ps_path         target file path
 *
 * Returns: DUR_OK          success
 ----------------------------------------------------------------------------*/
INT32 a_tos_get_file_path(TOS_TYPE_T e_type, CHAR* ps_path)
{
    return _get_tos_download_target_file_path(e_type, ps_path);
}

/*-----------------------------------------------------------------------------
 * Name:  a_tos_is_file_exist
 *
 * Description: check tos file is exist or not
 *
 * Inputs:  TOS type
 *
 * Outputs: -
 *
 * Returns: TRUE
 ----------------------------------------------------------------------------*/
BOOL a_tos_is_file_exist(TOS_TYPE_T e_type)
{
    INT32       i4_ret = 0;
    FILE*       fl = NULL;
    CHAR        s_cmd[255] = {0};
    CHAR        s_target_path[255] = {0};
    INT32       i4_file_len = 0;

    /* get download file path with tos type*/
    i4_ret = _get_tos_download_target_file_path(e_type, s_target_path);
    if (DUR_OK != i4_ret)
    {
        return FALSE;
    }

    /* check the tos file is exist or not and check the file size */
    fl = fopen(s_target_path, "r");
    if (fl == NULL)
    {
        return FALSE;
    }
    else
    {
        /* if file is exist, need clean env after power on */
        if (b_is_need_clean_env)
        {
            b_is_need_clean_env = FALSE;

            c_sprintf(s_cmd, "rm %s/* ", ps_tos_dir);
            AP_SYSTEM_CALL(s_cmd);

            DBG_LOG_PRINT(("[TOS][INFO] Cleanup environment. i4_ret: %d.\n", i4_ret));

            AP_SYSTEM_CALL("sync");

            return FALSE;
        }

        /* check file size, if exist and file size > 0, skip download */
        i4_ret = fseek(fl, 0, SEEK_END);
        if (i4_ret != 0)
        {
            fclose(fl);
            return FALSE;
        }

        i4_file_len = ftell(fl);
        fclose(fl);

        DBG_LOG_PRINT(("[TOS][INFO] TOS File size = %ld.\n", i4_file_len));

        if (i4_file_len <= MIN_DOWNLOAD_FILE_SIZE)
        {
            c_sprintf(s_cmd, "rm %s", s_target_path);
            AP_SYSTEM_CALL(s_cmd);
            DBG_LOG_PRINT(("[TOS][INFO] Remove fake file %s. \n", s_target_path));

            return FALSE;
        }
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name:  a_tos_download_util_file
 *
 * Description: download tos files from specified url address
 *
 * Inputs:  TOS type
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_tos_download_util_file(TOS_TYPE_T e_type)
{
    int         ret = 0;
    TOS_TYPE_T  e_type_tmp = e_type;

    /* Create read-request control thread */
    ret = pthread_create(&gh_tos_download_util_thread, NULL, _tos_download_util_thread, (VOID*)e_type_tmp);
    if (ret != 0)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,%d\n", __FILE__, __FUNCTION__, __LINE__, ret));
    }

    return DUR_OK;
}

static INT32 _set_policy_download_icl_flag ( UINT32 item,const BOOL b_flag)
{
    INT32   i4_ret;
    UINT8   ui1_val = b_flag ? ICL_POLICY_DOWNLOAD_ITEM_RUNNING : ICL_POLICY_DOWNLOAD_ITEM_STOP;
    DBG_LOG_PRINT(("[VPP][%s %d] item status 0x%04x\n",__FUNCTION__,__LINE__,item));
    item = item << 8;
    item |= ui1_val;

    DBG_LOG_PRINT(("[VPP][%s %d] item status 0x%04x\n",__FUNCTION__,__LINE__,item));
    if(0 != (i4_ret = a_icl_set(ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS),
              &item, sizeof(UINT32))))
   {
      DBG_LOG_PRINT(("[VPP][%s %d] failed to set icl item status ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
      return DUR_FAIL;
   }

    return DUR_OK;
}


static CHAR* get_lang_name(VIZIO_LANG_TYPE_T e_lang)
{
    switch(e_lang)
    {
         case VIZIO_LANG_FR:return "fr";
         case VIZIO_LANG_EN:return "en";
         case VIZIO_LANG_SPA:return "es";
         default:return NULL;
    }
}

static CHAR* get_region_name(VIZIO_LANG_TYPE_T e_lang)
{
  return (VIZIO_LANG_FR == e_lang ? "CA" : VIZIO_LANG_SPA == e_lang ? "MX" : "US");
}

static CHAR* get_document_type_name(VIZIO_POLICY_TYPE_T e_policy)
{
    switch(e_policy)
    {
         case VIZIO_POLICY_PRIVACY:           return "privacy-policy";
         case VIZIO_POLICY_SMARTCAST:         return "smartcast-supplement";
         case VIZIO_POLICY_VIEWDATA:          return "viewing-data";
         case VIZIO_POLICY_TOS:               return "terms-of-service";
         case VIZIO_POLICY_VIEWDATA_OVERVIEW: return "viewing-data-overview";
         default:return NULL;
    }
}

static CHAR* get_policy_name(VIZIO_POLICY_TYPE_T e_policy)
{
    switch(e_policy)
    {
         case VIZIO_POLICY_PRIVACY:           return "vizio_privacy_policy";
         case VIZIO_POLICY_SMARTCAST:         return "vizio_smaercast_policy";
         case VIZIO_POLICY_VIEWDATA:          return "vizio_viewdata_policy";
         case VIZIO_POLICY_TOS:               return "vizio_tos_policy";
         case VIZIO_POLICY_VIEWDATA_OVERVIEW: return "vizio_viewdata_overview";
         default:return NULL;
    }
}

static CHAR* get_lang_save_name(VIZIO_COUNTRY_TYPE_T e_country,VIZIO_LANG_TYPE_T e_lang)
{
    switch(e_country)
    {
         case VIZIO_COUNTRY_US:
            {
                if(VIZIO_LANG_FR == e_lang)
                    return "us_fre";
                else if(VIZIO_LANG_SPA == e_lang)
                    return "us_spa";
                else
                    return "us_eng";
            }
         case VIZIO_COUNTRY_CA:
            {
                if(VIZIO_LANG_FR == e_lang)
                    return "ca_fre";
                else if(VIZIO_LANG_SPA == e_lang)
                    return "ca_spa";
                else
                    return "ca_eng";
            }
         case VIZIO_COUNTRY_MX:
                {
                    if(VIZIO_LANG_FR == e_lang)
                        return "mx_fre";
                    else if(VIZIO_LANG_SPA == e_lang)
                        return "mx_spa";
                    else
                        return "mx_eng";
                }
         default:return NULL;
    }
}

static CHAR* make_file_name(VIZIO_COUNTRY_TYPE_T e_country,VIZIO_LANG_TYPE_T e_lang,VIZIO_POLICY_TYPE_T e_policy,CHAR* sz_filename,INT32 i4_max_len)
{
    memset(sz_filename,0,i4_max_len);
    c_snprintf(sz_filename,i4_max_len,"%s_%s.txt",get_policy_name(e_policy),get_lang_save_name(e_country,e_lang));
    return sz_filename;
}

BOOL a_is_policy_file_exist(VIZIO_COUNTRY_TYPE_T e_country,VIZIO_LANG_TYPE_T lang,VIZIO_POLICY_TYPE_T e_policy)
{
    CHAR sz_file_path[512] = {0};
    CHAR sz_file_name[128] = {0};

   c_snprintf(sz_file_path,255,"%s/%s",ps_policy_dir,make_file_name(e_country,lang,e_policy,sz_file_name,128));

   struct stat stat_buf;

   if(0 != stat(sz_file_path,&stat_buf) || stat_buf.st_size <= 0)
   {
     DBG_LOG_PRINT(("[VPP][%s %d] %s not  exist !\n",__FUNCTION__,__LINE__,sz_file_path));
      return FALSE;
   }
   else
   {
       DBG_LOG_PRINT(("[VPP][%s %d] %s exist ! size => %d\n",__FUNCTION__,__LINE__,sz_file_path,stat_buf.st_size));
   }
    return TRUE;
}

INT32 a_get_policy_file_path(VIZIO_COUNTRY_TYPE_T e_country,VIZIO_LANG_TYPE_T e_lang,VIZIO_POLICY_TYPE_T e_policy,CHAR* sz_file_path,INT32 ui4_max_name_len)
{
   CHAR sz_file_name[128] = {0};
   c_snprintf(sz_file_path,ui4_max_name_len,"%s/%s",ps_policy_dir,make_file_name(e_country,e_lang,e_policy,sz_file_name,128));
   return 0;
}

static VOID* _download_util_thread(VOID* pv_data)
{
    CURL*       pt_curl = NULL;
    CURLcode    e_res ;
    DOUBLE      ui8_speed = 0;
    DOUBLE      ui8_time = 0;
    DOUBLE      ui8_size = 0;
    CHAR        sz_filename[128] = {0};
    CHAR        s_url[255] = {0};
    CHAR        s_buf_path[255] = {0};
    CHAR        s_target_path[255] = {0};
    CHAR        s_cmd[255] = {0};
    FILE*       fl = NULL;

    INT32       i4_file_len = 0;
    INT32       i4_ret = 0;
    UINT8       ui1_country,ui1_lang,ui1_policy;
    UINT32      ui4_arg = (UINT32)pv_data;
    INT32       ui4_read_cnt;


    SPLIT_ITEM(ui4_arg,ui1_country,ui1_lang,ui1_policy);
    DBG_LOG_PRINT(("[VPP][%s %d] ui4_arg = 0x%x,ui1_country = %d,ui1_lang = %d,ui1_policy = %d\n",__FUNCTION__,__LINE__,ui4_arg,ui1_country,ui1_lang,ui1_policy));
    c_snprintf(s_url,255,"https://legal.vizio.com/api/documents?region=%s&language=%s&document_type=%s",
        get_region_name((VIZIO_LANG_TYPE_T) ui1_lang),
        get_lang_name((VIZIO_LANG_TYPE_T) ui1_lang),
        get_document_type_name((VIZIO_POLICY_TYPE_T) ui1_policy));

    DBG_LOG_PRINT(("[VPP][INFO][%s %d]   start! s_url=> %s.\n",__FUNCTION__, __LINE__, s_url));

    do
    {
        pthread_detach(pthread_self());

        c_snprintf(s_buf_path,255,"%s/%s","/tmp",make_file_name(
                      (VIZIO_COUNTRY_TYPE_T) ui1_country,
                      (VIZIO_LANG_TYPE_T) ui1_lang,
                      (VIZIO_POLICY_TYPE_T)ui1_policy,
                      sz_filename,128));

        DBG_LOG_PRINT(("[VPP][INFO][%s %d]   start! tmp path => %s.\n",__FUNCTION__, __LINE__, s_buf_path));

        c_snprintf(s_target_path,255,"%s/%s",ps_policy_dir,sz_filename);
        DBG_LOG_PRINT(("[VPP][INFO][%s %d]   start! target path => %s.\n",__FUNCTION__, __LINE__, s_target_path));

        /* check the tmp path is exist or not */
        if (0 == access(ps_policy_dir, 0))
        {
            if (b_is_need_clean_env_ex)
            {
                b_is_need_clean_env_ex = FALSE;

                c_sprintf(s_cmd, "rm %s/* ", ps_policy_dir);
                AP_SYSTEM_CALL(s_cmd);

                DBG_LOG_PRINT(("%s,%d [VPP] Cleanup environment.\n",__FUNCTION__, __LINE__));

                AP_SYSTEM_CALL("sync");
            }
        }
        else
        {
            c_sprintf(s_cmd, "%s %s", "mkdir -p ", ps_policy_dir);
            AP_SYSTEM_CALL_EX(s_cmd,i4_ret);

            DBG_LOG_PRINT(("\n%s [VPP] Make  dir: %s, i4_ret=%d\n", __FUNCTION__, s_cmd, i4_ret));
            DBG_LOG_PRINT(("\n%s [VPP] WIFEXITED=%d\n", __FUNCTION__, s_cmd, WIFEXITED(i4_ret)));
            DBG_LOG_PRINT(("\n%s [VPP] WEXITSTATUS=%d\n", __FUNCTION__, s_cmd, WEXITSTATUS(i4_ret)));

            if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
            {
                /* do nothing */
            }
            else
            {
                DBG_LOG_PRINT(("\n%s,%d [VPP] Make temp dir FAIL!\n",__FUNCTION__,__LINE__));
                break;
            }

            /* do not need to clean up anymore */
            b_is_need_clean_env_ex = FALSE;
        }

        /* start to create and download tos file */
        fl = fopen(s_buf_path, "w+");
        if (fl == NULL)
        {
            DBG_LOG_PRINT(("%s,%d [VPP] download file handle open error.",__FUNCTION__,__LINE__));
            break;
        }

        pt_curl = curl_easy_init();
        if (pt_curl == NULL)
        {
            DBG_LOG_PRINT(("%s,%d [VPP] curl_easy_init fail",__FUNCTION__,__LINE__));
            break;
        }
        else
        {
             cJSON      *root,*pc_type,*pc_lang,*pc_txt,*pc_country;
             FILE*       fp_target     = NULL;
             CHAR*       ps_policy_buf = NULL;

             DBG_LOG_PRINT(("%s,%d [VPP] download file %s  open ok.\n",__FUNCTION__,__LINE__,s_buf_path));
            _set_policy_download_icl_flag(ui4_arg,TRUE);

            DBG_LOG_PRINT(("%s,%d [VPP] Get url= %s \n",__FUNCTION__,__LINE__, s_url));
            e_res = curl_easy_setopt(pt_curl, CURLOPT_URL, s_url);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set URL fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_SSL_VERIFYPEER, 0L);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set NO verification failed! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_SSL_VERIFYHOST, 0L);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set NO check host failed! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_MAXREDIRS, 5);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set NO verification failed! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_FOLLOWLOCATION, 1);
            if (CURLE_OK != e_res)
            {
                DBG_ERROR(("%s,%d [VPP] set NO check host failed! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_PROGRESSFUNCTION, _progress_download_func);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set progress function fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_CONNECTTIMEOUT, MAX_CONN_TIMEOUT);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set connect timeout function fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_TIMEOUT, MAX_DOWNLOAD_TIMEOUT);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set progress function fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_WRITEFUNCTION, _write_data);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set write function fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_WRITEDATA, fl);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set write data fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_NOPROGRESS, 0L);
            if (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] set no progress fail! res = %d",__FUNCTION__,__LINE__, e_res));
                break;
            }

            /* Perform the request, res will get the return code */
            e_res = curl_easy_perform(pt_curl);

            DBG_LOG_PRINT(("\n####%s %d [VPP] download return code: %d.\n",__FUNCTION__,__LINE__,e_res));

            if (CURLE_WRITE_ERROR == e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] CURLE_WRITE_ERROR %s\n",__FUNCTION__,__LINE__));
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_SIZE_DOWNLOAD , &ui8_size);
            if  (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] get download size fail! res = %d\n",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_TOTAL_TIME , &ui8_time);
            if  (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] get download size fail! res = %d\n",__FUNCTION__,__LINE__, e_res));
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_SPEED_DOWNLOAD , &ui8_speed);
            if  (CURLE_OK != e_res)
            {
                DBG_LOG_PRINT(("%s,%d [VPP] get download speed fail! res = %d\n",__FUNCTION__,__LINE__, e_res));
                break;
            }

            fflush(fl);

            /* check file size, if exist and file size > 0, skip download */
            i4_ret = fseek(fl, 0, SEEK_END);
            i4_file_len = ftell(fl);
            if(NULL ==( ps_policy_buf = (CHAR*)c_mem_alloc(i4_file_len + 1)))
            {
                DBG_LOG_PRINT(("[VPP][%s %d] failed to memalloc memory!\n",__FUNCTION__,__LINE__));
                break;
            }
            DBG_LOG_PRINT((" [VPP] download time  = %.3f sec.\n", ui8_time));
            DBG_LOG_PRINT((" [VPP] download speed = %.3f bytes/sec.\n", ui8_speed));
            DBG_LOG_PRINT((" [VPP] download size  = %.0f bytes.\n", ui8_size));
            DBG_LOG_PRINT((" [VPP] download file  = %ld bytes.\n", i4_file_len));
            fseek(fl, 0, SEEK_SET);
            c_memset(ps_policy_buf,0,i4_file_len + 1);
            ui4_read_cnt = fread(ps_policy_buf,i4_file_len,1,fl);
            if(ui4_read_cnt <= 0)
            {
                DBG_LOG_PRINT(("[VPP][%s %d] failed to read content!\n",__FUNCTION__,__LINE__));
                break;
            }
            //DBG_LOG_PRINT(("[VPP][%s %d]! ################ %s #########################\n",__FUNCTION__,__LINE__,ps_policy_buf));
            if(NULL == (root = cJSON_Parse(ps_policy_buf)))
            {
                DBG_LOG_PRINT(("[VPP][%s %d] failed to parse json date ###%s###\n",__FUNCTION__,__LINE__,ps_policy_buf));
                break;
            }

            pc_type = cJSON_GetObjectItem(root,get_document_type_name((VIZIO_POLICY_TYPE_T)ui1_policy));
            //DBG_LOG_PRINT(("[VPP][%s %d]!\n",__FUNCTION__,__LINE__));
            if(pc_type)
            {
                pc_country = cJSON_GetObjectItem(pc_type,get_region_name((VIZIO_COUNTRY_TYPE_T)ui1_lang));
                //DBG_LOG_PRINT(("[VPP][%s %d]!\n",__FUNCTION__,__LINE__));
                if(pc_country)
                {
                   pc_lang = cJSON_GetObjectItem(pc_country,get_lang_name((VIZIO_COUNTRY_TYPE_T)ui1_lang));
                  //DBG_LOG_PRINT(("[VPP][%s %d]!\n",__FUNCTION__,__LINE__));
                     pc_txt = cJSON_GetObjectItem(pc_lang,"text");
                    // DBG_LOG_PRINT(("[VPP][%s %d]!\n",__FUNCTION__,__LINE__));
                     if(pc_txt)
                     {
                        // DBG_LOG_PRINT(("[VPP][%s %d] %s! %s\n",__FUNCTION__,__LINE__,pc_txt->string,pc_txt->valuestring));
                         if(pc_txt->valuestring && NULL != (fp_target = fopen(s_target_path, "w+")))
                         {
                            // DBG_LOG_PRINT(("[VPP][%s %d] fopen %s succeed \n",__FUNCTION__,__LINE__,s_target_path));
                             if(fwrite(pc_txt->valuestring,strlen(pc_txt->valuestring),1,fp_target) > 0)
                             {
                                DBG_LOG_PRINT(("[VPP][%s %d] fwrite  %s succeed.data len = %d \n",__FUNCTION__,__LINE__,s_target_path,strlen(pc_txt->valuestring)+1));
                             }
                             else
                             {
                                DBG_LOG_PRINT(("[VPP][%s %d] fwrite %s failed \n",__FUNCTION__,__LINE__,s_target_path));
                             }
                             fclose(fp_target);
                         }
                         else
                         {
                              DBG_LOG_PRINT(("[VPP][%s %d] fopen %s failed \n",__FUNCTION__,__LINE__,s_target_path));
                              break;
                         }
                     }
                  }
                }

                if(root)
                {
                    cJSON_Delete(root);
                }

                if(ps_policy_buf)
                {
                   c_mem_free(ps_policy_buf);
                }
            }
    }while(0);

    /* cleanup buffer file */
    if((access(s_cmd, 0) == 0))
    {
        c_sprintf(s_cmd, "rm %s", s_buf_path);
        AP_SYSTEM_CALL(s_cmd);
    }

    /* always cleanup */
    if (pt_curl != NULL)
    {
        curl_easy_cleanup(pt_curl);
    }

    /* close file handle */
    if (fl != NULL)
    {
        fclose(fl);
    }

    /* broadcast file download finish */
    _set_policy_download_icl_flag(ui4_arg,FALSE);

    /* exit the thread*/
    pthread_exit(NULL);

    return NULL;
}

INT32 a_url_download(VIZIO_COUNTRY_TYPE_T country,VIZIO_LANG_TYPE_T lang,VIZIO_POLICY_TYPE_T policy)
{
   UINT32 ui4_arg;

   MAKE_ITEM(ui4_arg,country,lang,policy);
   DBG_LOG_PRINT(("\n [VPP] %s,%s,%d create thread item 0x%04x!!!\n", __FILE__, __FUNCTION__, __LINE__,ui4_arg));
   if(0 != pthread_create(&g_h_download_util_thread, NULL, _download_util_thread, (VOID*)ui4_arg))
   {
      DBG_LOG_PRINT(("\n [VPP] %s,%s,%d create thread failed!!!\n", __FILE__, __FUNCTION__, __LINE__));
      return DUR_FAIL;
   }
   return DUR_OK;
}

#endif  /* APP_DYNAMIC_TOS_SUPPORT */

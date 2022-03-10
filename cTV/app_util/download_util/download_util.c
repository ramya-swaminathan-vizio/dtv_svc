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
#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/stat.h>
#include <unistd.h>

#include "curl/curl.h"
#include "curl/easy.h"

#include "u_common.h"
#include "c_os.h"
#include "c_dbg.h"
#include "c_fm.h"
#include "c_dt.h"
#include "c_uc_str.h"

#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/menu2/menu_custom.h"

#undef  DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE DBG_LEVEL_ALL

//#define DEVICE_MODEL_GROUP_LEN 5 /* MGXXX */
//#define DEVICE_CLASS_LEN       20
#define MAX_HEADER_LINE 100
#define MAX_HEADER_LINE_SIZE 255
#define MODIFIED_DATE_PREFIX 17 /* "  Last-Modified: " */
#define MODIFIED_DATE_LEN 29 /* "Tue, 31 Dec 1997 23:59:59 GMT" */
#define MAX_BUF           255
//CHAR* ps_default_url        = "http://manuals.oui-0x00199d.com/124_M401i-B3_EN_A.html.tgz.gpg";
CHAR* ps_url_prefix         = "http://manuals.oui-0x00199d.com";
CHAR* ps_staging_url_prefix = "http://manuals.oui-0x00199d.com/staging";
CHAR* ps_url_suffix         = ".tgz.gpg";

CHAR* ps_manual_location_prefix = "/data/manual";
CHAR* ps_manual_date  = "date.txt";
CHAR* ps_manual_temp  = "/data/manual/temp";
CHAR* ps_url_header   = "/data/manual/temp/header.txt";
CHAR* ps_modify_date  = "  Last-Modified:";

BOOL         gb_um_is_staging_mode = FALSE;
static BOOL  gb_um_opera_start     = FALSE;
static BOOL  gb_um_opera_exit      = FALSE;
static BOOL  gb_um_is_displaying   = FALSE;
static CHAR  s_tmp[MAX_BUF*2]      = {0};


static SIZE_T    write_data(VOID *pv_data, SIZE_T z_size, SIZE_T z_nmemb, FILE *pf_stream);
static VOID*     _download_util_thread(VOID * pv_data);
static pthread_t  gh_download_util_thread      = 0 ;

#ifdef LINUX_TURNKEY_SOLUTION
extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
#endif

/*-----------------------------------------------------------------------------
 * Name:  write_data
 *
 * Description: callback function for speedtest
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
static SIZE_T write_data(VOID *pv_data, SIZE_T z_size, SIZE_T z_nmemb, FILE *pf_stream)
{
    SIZE_T written = fwrite(pv_data, z_size, z_nmemb, pf_stream);

    return (written);
}

static BOOL _um_clear_temp(VOID)
{
    DBG_INFO(("\n%s(%d) start\n",__FUNCTION__,__LINE__));

    system("rm -rf /data/manual/temp");
    system("sync;sync;sync");

    return TRUE;
}

static VOID _um_set_opera_start_status(BOOL b_status)
{
    gb_um_opera_start = b_status;
}

static BOOL _um_get_opera_start_status(VOID)
{
    return gb_um_opera_start;
}

static VOID _um_set_opera_exit_status(BOOL b_status)
{
    gb_um_opera_exit = b_status;
}

static BOOL _um_get_opera_exit_status(VOID)
{
    return gb_um_opera_exit;
}

static VOID _um_set_status_is_displaying(BOOL b_status)
{
    gb_um_is_displaying = b_status;
}

static BOOL _um_get_status_is_displaying(VOID)
{
    return gb_um_is_displaying;
}

static BOOL _get_mc_version (CHAR* ps_mc_ver)
{
    UTF16_T  w2s_mc_ver[255] = {0};
    INT32    i4_ret = 0;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_mc_ver)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    i4_ret = a_cfg_custom_get_req_mc_version(w2s_mc_ver);
    if (0 != i4_ret)
    {
        DBG_INFO(("\n\t\t%s a_cfg_custom_get_req_mc_version fail: %d\n", __FUNCTION__, i4_ret));
        return FALSE;
    }

    c_uc_w2s_to_ps(w2s_mc_ver, ps_mc_ver, 31);

    if (NULL == ps_mc_ver)
    {
        DBG_INFO(("\n\t\t%s Get manual cloud version FAIL\n", __FUNCTION__));
        return FALSE;
    }
    else
    {
        DBG_INFO(("\n\t\t%s Get manual cloud version: %s\n", __FUNCTION__, ps_mc_ver));
    }

    return TRUE;

}

static BOOL _get_download_url(CHAR* ps_url)
{
    CHAR    s_mc_ver[255] = {0};
    BOOL    b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_url)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_mc_version(s_mc_ver);

    if (FALSE == b_ret)
    {
        DBG_INFO(("\n\t\t%s _get_mc_version: %d\n", __FUNCTION__, b_ret));
        return FALSE;
    }

    if (gb_um_is_staging_mode)
    {
        c_sprintf(ps_url, "%s/%s%s", ps_staging_url_prefix, s_mc_ver, ps_url_suffix);
    }
    else
    {
        c_sprintf(ps_url, "%s/%s%s", ps_url_prefix, s_mc_ver, ps_url_suffix);
    }

    DBG_INFO(("\n\t\t%s Get download URL: %s\n", __FUNCTION__, ps_url));

    return TRUE;
}

static BOOL _get_manual_dir(CHAR* ps_manual_dir)
{
    ISO_639_LANG_T  s639_lang = {0};
    CHAR            s_mc_ver[255] = {0};
    BOOL            b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_manual_dir)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_mc_version(s_mc_ver);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    a_cfg_get_gui_lang(s639_lang);
    DBG_INFO(("\n\t\t%s Get GUI lang: %s\n", __FUNCTION__,s639_lang));

    c_sprintf(ps_manual_dir, "%s/%s/%s", ps_manual_location_prefix, s639_lang, s_mc_ver);
    DBG_INFO(("\n\t\t%s Get manual save location: %s\n", __FUNCTION__, ps_manual_dir));

    return TRUE;
}

static BOOL _get_manual_temp_um(CHAR* ps_temp_um)
{
    CHAR  s_mc_ver[255] = {0};
    BOOL  b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_temp_um)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_mc_version(s_mc_ver);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    c_sprintf(ps_temp_um, "%s/%s%s", ps_manual_temp, s_mc_ver, ".tgz.gpg");
    DBG_INFO(("\n\t\t%s Get temp UM name: %s\n", __FUNCTION__, ps_temp_um));

    return TRUE;
}

static BOOL _get_manual_temp_um_tgz(CHAR* ps_temp_um_tgz)
{
    CHAR              s_mc_ver[255] = {0};
    BOOL              b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_temp_um_tgz)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_mc_version(s_mc_ver);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    c_sprintf(ps_temp_um_tgz, "%s/%s%s", ps_manual_temp, s_mc_ver, ".tgz");
    DBG_INFO(("\n\t\t%s Get temp UM name: %s\n", __FUNCTION__, ps_temp_um_tgz));

    return TRUE;
}

static BOOL _get_exist_date_info_dir(CHAR* ps_date_dir)
{
    CHAR  s_manual_dir[255] = {0};
    BOOL  b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_date_dir)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_manual_dir(s_manual_dir);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    c_sprintf(ps_date_dir, "%s/%s", s_manual_dir, ps_manual_date);
    DBG_INFO(("\n\t\t%s Get date info location: %s\n", __FUNCTION__, ps_date_dir));

    return TRUE;
}

static BOOL _get_exist_date_info(CHAR* ps_date_info)
{
    CHAR  s_location[255] = {0};
    FILE* p_date_file = NULL;
    BOOL  b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == ps_date_info)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_exist_date_info_dir(s_location);
    if (FALSE == b_ret)
    {
        DBG_ERROR(("\n\t\t%s _get_exist_date_info_dir fail!\n", __FUNCTION__));
        return FALSE;
    }

    if (0 != (access(s_location, 0)))
    {
        DBG_INFO(("\n\t\t%s No such file: %s!\n", __FUNCTION__, s_location));
        return FALSE;
    }
    p_date_file = fopen(s_location, "rb");

    if (NULL == fgets(ps_date_info, MAX_HEADER_LINE_SIZE, p_date_file))
    {
        DBG_ERROR(("\n\t\t%s fgets fail!\n", __FUNCTION__));
        return FALSE;
    }
    else
    {
        DBG_INFO(("\n\t\t%s Get date: %s\n", __FUNCTION__, ps_date_info))
    }

    fclose(p_date_file);

    return TRUE;
}

static BOOL _get_exist_date_info_utc_sec(TIME_T* pt_utc_sec)
{
    CHAR  s_date_info[MAX_HEADER_LINE_SIZE] = {0};
    BOOL  b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == pt_utc_sec)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_exist_date_info(s_date_info);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    *pt_utc_sec = (TIME_T) c_strtoull(s_date_info, NULL, 10);

    return TRUE;

}

static BOOL _get_url_header(VOID)
{
    CHAR  s_cmd[255] = {0};
    CHAR  s_url[255] = {0};
    BOOL  b_ret = FALSE;
    INT32 i4_ret = 0;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (0 == access(ps_url_header, 0))
    {
        DBG_INFO(("\n\t\t%s URL header has been saved\n", __FUNCTION__));
        return TRUE;
    }

    if (0 != access(ps_manual_temp, 0))
    {
        c_sprintf(s_cmd, "%s %s", "mkdir -p ", ps_manual_temp);
        DBG_INFO(("\n\t\t%s Make temp dir: %s\n", __FUNCTION__, s_cmd));
        system(s_cmd);
    }

    b_ret = _get_download_url(s_url);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    c_sprintf(s_cmd, "%s %s %s %s", "/3rd/bin/wget -o", ps_url_header, "-S --spider", s_url);
    DBG_INFO(("\n\t\t%s Get url header: %s\n", __FUNCTION__, s_cmd));
    i4_ret = system(s_cmd);
    if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
    {
        return TRUE;
    }
    else
    {
        DBG_INFO(("\n%s\t\t Get URL header FAIL\n", __FUNCTION__));
        return FALSE;
    }
}

static BOOL _get_utc_dtg_from_date(CHAR* ps_date_info, DTG_T* pt_utc_dtg)
{
    //Last-Modified: Tue, 31 Dec 1997 23:59:59 GMT (15+29)
    //BOOL b_ret = FALSE;
    CHAR   s_temp[5];
    UINT32 index = 0;
    UINT32 i = 0;

#define DOW 3
#define DAY 2
#define MON 3
#define YEAR 4
#define HMS 2
#define GMT 3

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (
         (NULL == ps_date_info)                                              ||
         (c_strlen(ps_date_info) < (MODIFIED_DATE_PREFIX+MODIFIED_DATE_LEN)) ||
         (NULL == pt_utc_dtg)
       )
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    index += MODIFIED_DATE_PREFIX;
    for (i=0; i<DOW; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Week: %s\n", __FUNCTION__, s_temp));

    if (c_strncasecmp(s_temp, "SUN", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)0;
    }
    else if (c_strncasecmp(s_temp, "MON", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)1;
    }
    else if (c_strncasecmp(s_temp, "TUE", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)2;
    }
    else if (c_strncasecmp(s_temp, "WED", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)3;
    }
    else if (c_strncasecmp(s_temp, "THU", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)4;
    }
    else if (c_strncasecmp(s_temp, "FRI", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)5;
    }
    else if (c_strncasecmp(s_temp, "SAT", DOW) == 0)
    {
        pt_utc_dtg->ui1_dow = (UINT8)6;
    }
    else
    {
        return FALSE;
    }

    index += DOW+1+1; /* + "," + " "*/
    for (i=0; i<DAY; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Day in string: %s\n", __FUNCTION__, s_temp));

    pt_utc_dtg->ui1_day = (UINT8) c_strtoull(s_temp, NULL, 10);

    DBG_INFO(("\n\t\t%s Day: %d\n", __FUNCTION__, pt_utc_dtg->ui1_day));

    index += DAY+1;
    for (i=0; i<MON; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Month: %s\n", __FUNCTION__, s_temp));

    if (c_strncasecmp(s_temp, "JAN", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)1;
    }
    else if (c_strncasecmp(s_temp, "FEB", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)2;
    }
    else if (c_strncasecmp(s_temp, "MAR", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)3;
    }
    else if (c_strncasecmp(s_temp, "APR", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)4;
    }
    else if (c_strncasecmp(s_temp, "MAY", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)5;
    }
    else if (c_strncasecmp(s_temp, "JUN", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)6;
    }
    else if (c_strncasecmp(s_temp, "JUL", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)7;
    }
    else if (c_strncasecmp(s_temp, "AUG", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)8;
    }
    else if (c_strncasecmp(s_temp, "SEP", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)9;
    }
    else if (c_strncasecmp(s_temp, "OCT", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)10;
    }
    else if (c_strncasecmp(s_temp, "NOV", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)11;
    }
    else if (c_strncasecmp(s_temp, "DEC", MON) == 0)
    {
        pt_utc_dtg->ui1_mo = (UINT8)12;
    }
    else
    {
        return FALSE;
    }

    index += MON+1;
    for (i=0; i<YEAR; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Year in string: %s\n", __FUNCTION__, s_temp));

    pt_utc_dtg->ui2_yr = (UINT16) c_strtoull(s_temp, NULL, 10);

    DBG_INFO(("\n\t\t%s Year: %d\n", __FUNCTION__, pt_utc_dtg->ui2_yr));

    index += YEAR+1;
    for (i=0; i<HMS; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Hour in string: %s\n", __FUNCTION__, s_temp));

    pt_utc_dtg->ui1_hr = (UINT8) c_strtoull(s_temp, NULL, 10);

    DBG_INFO(("\n\t\t%s Hour: %d\n", __FUNCTION__, pt_utc_dtg->ui1_hr));

    index += HMS+1;
    for (i=0; i<HMS; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Minute in string: %s\n", __FUNCTION__, s_temp));

    pt_utc_dtg->ui1_min = (UINT8) c_strtoull(s_temp, NULL, 10);

    DBG_INFO(("\n\t\t%s Minute: %d\n", __FUNCTION__, pt_utc_dtg->ui1_min));

    index += HMS+1;
    for (i=0; i<HMS; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s Second in string: %s\n", __FUNCTION__, s_temp));

    pt_utc_dtg->ui1_sec = (UINT8) c_strtoull(s_temp, NULL, 10);

    DBG_INFO(("\n\t\t%s Minute: %d\n", __FUNCTION__, pt_utc_dtg->ui1_sec));

    index += HMS+1;
    for (i=0; i<GMT; i++)
    {
        s_temp[i] = ps_date_info[index+i];
    }
    s_temp[i] = '\0';

    DBG_INFO(("\n\t\t%s GMT: %s\n", __FUNCTION__, s_temp));

    if (c_strncmp(s_temp, "GMT", GMT) != 0)
    {
        DBG_INFO(("\n\t\t%s GMT Match fail\n", __FUNCTION__));
        return FALSE;
    }
    pt_utc_dtg->b_gmt = TRUE;

    pt_utc_dtg->b_dst = FALSE;

    return TRUE;
}

static BOOL _get_url_date_info_utc_sec(TIME_T* pt_utc_sec)
{
    BOOL    b_ret = FALSE;
    FILE*   headerfile = NULL;
    CHAR*   ps_line[MAX_HEADER_LINE];
    CHAR    s_date_info[MAX_HEADER_LINE_SIZE] = {0};
    DTG_T   t_utc_dtg = {0};
    UINT32  i = 0;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == pt_utc_sec)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_url_header();
    if (FALSE == b_ret)
    {
        //_um_clear_temp();
        return FALSE;
    }

    headerfile = fopen(ps_url_header, "rb");
    for (i=0; i<MAX_HEADER_LINE; i++)
    {
        ps_line[i] = (CHAR*) c_mem_alloc(MAX_HEADER_LINE_SIZE* sizeof(CHAR));
    }

    i=0;
    while (NULL != fgets(ps_line[i], MAX_HEADER_LINE_SIZE, headerfile))
    {
        DBG_INFO(("\t\tLine %d: %s\n", i, ps_line[i]));
        i++;
    }

    fclose(headerfile);

    for (i=0; i<MAX_HEADER_LINE; i++)
    {
        if (NULL != c_strstr(ps_line[i], ps_modify_date))
        {
            c_strcpy(s_date_info, ps_line[i]);
            DBG_INFO(("\n\t\t%s s_date_info: %s\n", __FUNCTION__, s_date_info));
            break;
        }
    }

    for (i=0; i<MAX_HEADER_LINE; i++)
    {
        c_mem_free(ps_line[i]);
    }

    if (0 == c_strlen(s_date_info))
    {
        DBG_INFO(("\n\t\t%s %d Cannot find date info\n", __FUNCTION__, __LINE__));
        return FALSE;
    }

    b_ret = _get_utc_dtg_from_date(s_date_info, &t_utc_dtg);
    if (FALSE == b_ret)
    {
        DBG_INFO(("\n\t\t%s %d _get_utc_dtg_from_date fail\n", __FUNCTION__, __LINE__));
        return FALSE;
    }

    DBG_INFO(("\n\t\t%s %d _get_utc_dtg_from_date Year: %d\n", __FUNCTION__, __LINE__, t_utc_dtg.ui2_yr));

    *pt_utc_sec = c_dt_dtg_to_sec(&t_utc_dtg);

    DBG_INFO(("\n\t\t%s %d Get url date info: %lld\n", __FUNCTION__, __LINE__, *pt_utc_sec));

    return TRUE;
}

static BOOL _save_url_date_to_file(TIME_T t_utc_sec)
{
    CHAR   s_cmd[255] = {0};
    CHAR   s_date_info[255] = {0};
    FILE*  datefile = NULL;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (0 != (access(ps_manual_temp, 0)))
    {
        c_sprintf(s_cmd, "mkdir -p %s", ps_manual_temp);
        system(s_cmd);
    }

    c_sprintf(s_cmd, "%s/%s", ps_manual_temp, ps_manual_date);

    datefile = fopen(s_cmd, "wb");

    DBG_INFO(("\n\t\t%s %d URL date info integer: %lld\n", __FUNCTION__, __LINE__, t_utc_sec));

    c_sprintf(s_date_info, "%lld", t_utc_sec);

    DBG_INFO(("\n\t\t%s s_date_info: %s\n", __FUNCTION__, s_date_info));

    fputs(s_date_info, datefile);

    fclose(datefile);

    return TRUE;
}

static BOOL _is_dld_um_in_flash(VOID)
{
    CHAR s_um_dir[255] = {0};
    CHAR s_cmd[255] = {0};
    BOOL b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    b_ret = _get_manual_dir(s_um_dir);

    if (FALSE == b_ret)
    {
        return FALSE;
    }

    c_sprintf(s_cmd, "%s/%s", s_um_dir, "index.htm");

    DBG_INFO(("\n\t\t%s %d s_cmd:%s\n", __FUNCTION__, __LINE__, s_cmd));

    b_ret = ((access(s_cmd, 0) == 0) ? TRUE : FALSE);

    return b_ret;
}

/*-----------------------------------------------------------------------------
 * Name:  _progress_func
 *
 * Description: callback function for download progress
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

static int _progress_func(VOID *pv_data,
                          DOUBLE d_total, /* dltotal */
                          DOUBLE d_now, /* dlnow */
                          DOUBLE u_total,
                          DOUBLE u_now)
{
    //Do nothing
	DBG_INFO(("\n####%s(%d)_progress_func d_total = %lf, d_now = %lf\n",__FUNCTION__,__LINE__, d_total, d_now));

    if (TRUE == _um_get_opera_exit_status())
    {
        DBG_INFO(("\n\t\t%s(%d) Opera has exited, return CURL_WRITEFUNC_PAUSE.\n",__FUNCTION__,__LINE__));

        return CURL_WRITEFUNC_PAUSE;
    }

    return 0;
}

static VOID* _download_util_thread(VOID* pv_data)
{
    CURL*          pt_curl            = NULL;
    CURLcode       e_res;
    DOUBLE         ui8_speed          = 0;
    DOUBLE         ui8_size           = 0;
    CHAR           s_url[255]         = {0};
    CHAR           s_temp_um[255]     = {0};
    CHAR           s_temp_um_tgz[255] = {0};
    CHAR           s_um_dir[255]      = {0};
    CHAR           s_cmd[255]         = {0};
    ISO_639_LANG_T s639_lang          = {0};
    TIME_T         t_url_date         = 0;
    FILE*          fl                 = NULL;
    BOOL           b_ret              = TRUE;
    INT32          i4_ret             = 0;
    UINT8          ui1_retry_cnt      = 10;
    struct stat buf;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    do
    {
    	pthread_detach(pthread_self());

        b_ret = _get_download_url(s_url);
        if (FALSE == b_ret)
        {
            break;
        }

        if (0 != (access(ps_manual_temp, 0)))
        {
            c_sprintf(s_cmd, "%s %s", "mkdir -p", ps_manual_temp);
            i4_ret = system(s_cmd);
            DBG_INFO(("\n\t\t%s Make temp dir: %s, i4_ret=%d\n", __FUNCTION__, s_cmd, i4_ret));

            DBG_INFO(("\n\t\t%s WIFEXITED=%d\n", __FUNCTION__, WIFEXITED(i4_ret)));

            DBG_INFO(("\n\t\t%s WEXITSTATUS=%d\n", __FUNCTION__, WEXITSTATUS(i4_ret)));

            if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
            {
                b_ret=TRUE;
            }
            else
            {
                DBG_INFO(("\n\t\t%s Make temp dir FAIL!\n", __FUNCTION__));
                b_ret=FALSE;
                break;
            }
        }

        c_sprintf(s_cmd, "%s/%s", ps_manual_temp, ps_manual_date);
        if (0 != (access(s_cmd, 0)))
        {
            b_ret = _get_url_date_info_utc_sec(&t_url_date);
            DBG_INFO(("\n\t\t%s Get url date in sec: %lld\n", __FUNCTION__, t_url_date));

            if (TRUE == b_ret)
            {
                _save_url_date_to_file(t_url_date);
            }

        }

        b_ret = _get_manual_temp_um(s_temp_um);
        if (FALSE == b_ret)
        {
            break;
        }

        fl = fopen (s_temp_um,"wb");

        pt_curl = curl_easy_init();
        if (pt_curl == NULL) {
            fprintf(stderr, "curl_easy_init fail");
            b_ret = FALSE;
            break;
        }

        if(pt_curl)
        {
            /* First set the URL that is about to receive our POST. This URL can
               just as well be a https:// URL if that is what should receive the
               data. */
            e_res = curl_easy_setopt(pt_curl, CURLOPT_URL, s_url);
            if (CURLE_OK != e_res)
            {
                fprintf(stderr, "set URL fail! res = %d", e_res);
                b_ret = FALSE;
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_WRITEFUNCTION, write_data);
            if (CURLE_OK != e_res)
            {
                fprintf(stderr, "set write function fail! res = %d", e_res);
                b_ret = FALSE;
                break;
            }

            e_res = curl_easy_setopt(pt_curl, CURLOPT_WRITEDATA, fl);
            if (CURLE_OK != e_res)
            {
                fprintf(stderr, "set write data fail! res = %d", e_res);
                b_ret = FALSE;
                break;
            }

    		e_res = curl_easy_setopt(pt_curl, CURLOPT_NOPROGRESS, 0L);
    	    if (CURLE_OK != e_res)
            {
                fprintf(stderr, "set no progress fail! res = %d", e_res);
                b_ret = FALSE;
                break;
            }

    		e_res = curl_easy_setopt(pt_curl, CURLOPT_PROGRESSFUNCTION, _progress_func);
    	    if (CURLE_OK != e_res)
            {
                fprintf(stderr, "set progress function fail! res = %d", e_res);
                b_ret = FALSE;
                break;
            }

            DBG_INFO(("\n\t\t####%s(%d)Set opera start/exit status to be false at beginning.\n",__FUNCTION__,__LINE__));
            _um_set_opera_exit_status(FALSE);
            _um_set_opera_start_status(FALSE);

            DBG_INFO(("\n\t\t####%s(%d)download not start/complete\n",__FUNCTION__,__LINE__));

            //Change picture to step1 UI & use translations
            a_cfg_get_gui_lang(s639_lang);
            DBG_INFO(("\n\t\t####%s(%d) show step1 download gif in %s\n",__FUNCTION__,__LINE__,s639_lang));

            if (0 == c_strcmp(s639_lang, "fre"))
            {
                //Show step1 UI in FRE
                i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_download_step1_FR.html");
                DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            }
            else if (0 == c_strcmp(s639_lang, "spa"))
            {
                //Show step1 UI in SPA
                i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_download_step1_SP.html");
                DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            }
            else
            {
                //Show step1 UI in ENG
                i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_download_step1_EN.html");
                DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            }

            DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be true after send command.\n",__FUNCTION__,__LINE__));
            _um_set_status_is_displaying(TRUE);

            DBG_INFO(("\n\t\t####%s(%d)s_cmd:%s\n",__FUNCTION__,__LINE__,s_cmd));
            cmd_convert_send_cmd(s_cmd);

            /* Perform the request, res will get the return code */
            e_res = curl_easy_perform(pt_curl);
            if (CURLE_OK != e_res)
            {
                fprintf(stderr, "curl_easy_perform fail = %d, %s\n", e_res, __FUNCTION__);
                b_ret = FALSE;
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_SIZE_DOWNLOAD , &ui8_size);
            if  (CURLE_OK != e_res)
            {
                fprintf(stderr, "get download size fail! res = %d\n", e_res);
                b_ret = FALSE;
                break;
            }

            e_res = curl_easy_getinfo(pt_curl, CURLINFO_SPEED_DOWNLOAD , &ui8_speed);
            if  (CURLE_OK != e_res)
            {
                fprintf(stderr, "get download speed fail! res = %d\n", e_res);
                b_ret = FALSE;
                break;
            }

            fprintf(stderr, "speed=%.3f\n", ui8_speed);
            fprintf(stderr, "download size = %.0f\n", ui8_size);

            /* always cleanup */
            fflush(fl);
        }

        /*
        /basic/gpg/gpg_arm -d /data/manual/e-manual.tgz.gpg > /data/manual/e-manual.tgz
        cd ../../data/manual
        tar -xzf e-manual.tgz
        sync
        */

        b_ret = _get_manual_temp_um_tgz(s_temp_um_tgz);
        if (FALSE == b_ret)
        {
            break;
        }

        c_sprintf(s_cmd, "%s %s %s %s", "/basic/gpg/gpg_arm -d", s_temp_um, ">", s_temp_um_tgz);
        DBG_INFO(("\n\t\t####%s(%d)decrypt s_cmd:%s\n",__FUNCTION__,__LINE__,s_cmd));
        i4_ret = system(s_cmd);

        stat(s_temp_um_tgz, &buf);
        if ((0 != access(s_temp_um_tgz, 0)) ||
            (buf.st_size < 1))
        {
            DBG_INFO(("\n\t\t####%s(%d) Decrypt FAIL!\n",__FUNCTION__,__LINE__));
            b_ret=FALSE;
            break;
        }

        if (TRUE == _um_get_opera_exit_status())
        {
            DBG_INFO(("\n\t\t%s(%d) Opera has exited, just exit thread.\n",__FUNCTION__,__LINE__));

            DBG_INFO(("\n\t\t####%s(%d)Set opera start/exit status to be false at beginning.\n",__FUNCTION__,__LINE__));
            _um_set_opera_exit_status(FALSE);
            _um_set_opera_start_status(FALSE);

            DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be FALSE after exit opera.\n",__FUNCTION__,__LINE__));
            _um_set_status_is_displaying(FALSE);

            curl_easy_cleanup(pt_curl);
            fclose(fl);

            _um_clear_temp();

            /* exit the thread*/
            pthread_exit(NULL);

            return NULL;
        }

        //Show step2 UI & use translations
        a_cfg_get_gui_lang(s639_lang);
        DBG_INFO(("\n\t\t####%s(%d) show step2 download gif in %s\n",__FUNCTION__,__LINE__,s639_lang));

        if(0 == c_strcmp(s639_lang, "fre"))
        {
            //Show step2 UI in FRE
            i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_download_step2_FR.html");
            DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        }
        else if(0 == c_strcmp(s639_lang, "spa"))
        {
            //Show step2 UI in SPA
            i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_download_step2_SP.html");
            DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        }
        else
        {
            //Show step2 UI in ENG
            i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_download_step2_EN.html");
            DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        }

        DBG_INFO(("\n\t\t####%s(%d)s_cmd:%s\n",__FUNCTION__,__LINE__,s_cmd));
        cmd_convert_send_cmd(s_cmd);

        c_sprintf(s_cmd, "%s %s -C %s", "tar -xzf", s_temp_um_tgz, ps_manual_temp);
        DBG_INFO(("\n\t\t####%s(%d)untar s_cmd:%s\n",__FUNCTION__,__LINE__,s_cmd));
        i4_ret = system(s_cmd);
        if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
        {
            b_ret=TRUE;
        }
        else
        {
            DBG_INFO(("\n\t\t####%s(%d)Decompress fail!\n",__FUNCTION__,__LINE__));
            b_ret=FALSE;
            break;
        }

        i4_ret = system("sync;sync;sync");
        if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
        {
            b_ret=TRUE;
        }
        else
        {
            b_ret=FALSE;
            break;
        }

        c_sprintf(s_cmd, "%s/%s", ps_manual_temp, "index.htm");

        if (0 != (access(s_cmd, 0)))
        {
            DBG_INFO(("\n\t\t%s %d No index.htm in UM, just break to show error.\n", __FUNCTION__, __LINE__));
            b_ret=FALSE;
            break;
        }

        b_ret = _get_manual_dir(s_um_dir);
        if (FALSE == b_ret)
        {
            break;
        }

        c_sprintf(s_cmd, "%s %s", "rm -rf", s_um_dir);
        i4_ret = system(s_cmd);
        if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
        {
            b_ret=TRUE;
        }
        else
        {
            b_ret=FALSE;
            break;
        }

        if (0 != (access(s_um_dir, 0)))
        {
            c_sprintf(s_cmd, "%s %s", "mkdir -p ", s_um_dir);
            system(s_cmd);
            DBG_INFO(("\n\t\t%s Make dest dir: %s\n", __FUNCTION__, s_cmd));
        }

        c_sprintf(s_cmd, "%s %s%s %s", "mv -f", ps_manual_temp, "/*", s_um_dir);
        i4_ret = system(s_cmd);
        if ((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
        {
            b_ret=TRUE;
        }
        else
        {
            b_ret=FALSE;
            break;
        }

    }while(0);

    if (TRUE == _um_get_opera_exit_status())
    {
        DBG_INFO(("\n\t\t%s(%d) Opera has exited, just exit thread.\n",__FUNCTION__,__LINE__));

        DBG_INFO(("\n\t\t####%s(%d)Set opera start/exit status to be false in the end.\n",__FUNCTION__,__LINE__));
        _um_set_opera_exit_status(FALSE);
        _um_set_opera_start_status(FALSE);

        DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be FALSE after exit opera.\n",__FUNCTION__,__LINE__));
        _um_set_status_is_displaying(FALSE);

        curl_easy_cleanup(pt_curl);
        fclose(fl);

        _um_clear_temp();

        /* exit the thread*/
        pthread_exit(NULL);

        return NULL;
    }

    DBG_INFO(("\n\t\t%s(%d) Delay some time to avoid conflict.\n",__FUNCTION__,__LINE__));
    sleep(5);

    if (TRUE == _um_get_opera_exit_status())
    {
        DBG_INFO(("\n\t\t%s(%d) Opera has exited, just exit thread.\n",__FUNCTION__,__LINE__));

        DBG_INFO(("\n\t\t####%s(%d)Set opera start/exit status to be false at beginning.\n",__FUNCTION__,__LINE__));
        _um_set_opera_exit_status(FALSE);
        _um_set_opera_start_status(FALSE);

        DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be FALSE after exit opera.\n",__FUNCTION__,__LINE__));
        _um_set_status_is_displaying(FALSE);

        curl_easy_cleanup(pt_curl);
        fclose(fl);

        _um_clear_temp();

        /* exit the thread*/
        pthread_exit(NULL);

        return NULL;
    }

    if (FALSE == b_ret)
    {
        do
        {
            if (TRUE == _um_get_opera_start_status())
            {
                DBG_INFO(("\n\t\t%s(%d) Opera has started, just show error page.\n",__FUNCTION__,__LINE__));
                break;
            }

            DBG_INFO(("\n\t\t%s(%d) Opera not started, just waiting:%d.\n",__FUNCTION__,__LINE__, ui1_retry_cnt));
            usleep(300);

        }while (ui1_retry_cnt --);

        if (TRUE == _um_get_opera_exit_status())
        {
            DBG_INFO(("\n\t\t%s(%d) Opera has exited, just exit thread.\n",__FUNCTION__,__LINE__));

            DBG_INFO(("\n\t\t####%s(%d)Set opera start/exit status to be false at beginning.\n",__FUNCTION__,__LINE__));
            _um_set_opera_exit_status(FALSE);
            _um_set_opera_start_status(FALSE);

            DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be FALSE after exit opera.\n",__FUNCTION__,__LINE__));
            _um_set_status_is_displaying(FALSE);

            curl_easy_cleanup(pt_curl);
            fclose(fl);

            _um_clear_temp();

            /* exit the thread*/
            pthread_exit(NULL);

            return NULL;
        }

        a_cfg_get_gui_lang(s639_lang);
        DBG_INFO(("\n\t\t####%s(%d) Something wrong when downloading, show error gif in %s\n",__FUNCTION__,__LINE__,s639_lang));

        if (0 == c_strcmp(s639_lang, "fre"))
        {
            //Show error UI in FRE
            i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_Error_Page_720_FR.html");
            DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            cmd_convert_send_cmd(s_cmd);
        }
        else if (0 == c_strcmp(s639_lang, "spa"))
        {
            //Show error UI in SPA
            i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_Error_Page_720_SP.html");
            DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            cmd_convert_send_cmd(s_cmd);
        }
        else
        {
            //Show error UI in ENG
            i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/UM_Error_Page_720_EN.html");
            DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            cmd_convert_send_cmd(s_cmd);
        }
    }
    else
    {
        // Close blur
        DBG_INFO(("\n\t\t%s(%d)Close MBR\n",__FUNCTION__,__LINE__));
        a_cfg_custom_set_reduce_blur(0);
        a_cfg_custom_update_reduce_blur(0);

        // Show UM
        DBG_INFO(("\n\t\t%s(%d)Download Success! Show UM\n",__FUNCTION__,__LINE__));
        i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s%s\"]\n", s_um_dir, "/index.htm");
        DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        cmd_convert_send_cmd(s_cmd);
    }

    DBG_INFO(("\n\t\t####%s(%d)Set opera start/exit status to be false at end.\n",__FUNCTION__,__LINE__));
    _um_set_opera_exit_status(FALSE);
    _um_set_opera_start_status(FALSE);

    curl_easy_cleanup(pt_curl);
    fclose(fl);

    _um_clear_temp();

    /* exit the thread*/
    pthread_exit(NULL);

    return NULL;
}

/*-----------------------------------------------------------------------------
 * Name:  x_speedtest
 *
 * Description: do speedtest from specified url address
 *
 * Inputs:  url address
 *
 * Outputs: data download speed
 *
 * Returns: data download speed
 ----------------------------------------------------------------------------*/
INT32 a_download_util_file(VOID)
{
    INT32 i4_ret = 0;
    /**
     * Create read-request control thread
     */
    i4_ret = pthread_create(&gh_download_util_thread, NULL, _download_util_thread, (VOID *)NULL);
    if(i4_ret != 0)
    {
        DBG_INFO(("\n%s,%s,%d,%d\n",
                   __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }

    return (0);
}

BOOL a_um_chk_manual_is_up_to_date(VOID)
{
    BOOL   b_ret = FALSE;
    TIME_T t_exist_date = 0;
    TIME_T t_url_date = 0;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    b_ret = _get_exist_date_info_utc_sec(&t_exist_date);

    if (FALSE == b_ret)
    {
        DBG_INFO(("\n\t\t%s Get exist date info fail!\n", __FUNCTION__));
        return FALSE;
    }

    DBG_INFO(("\n\t\t%s %d Exist date info: %lld\n", __FUNCTION__, __LINE__, t_exist_date));

    b_ret = _get_url_date_info_utc_sec(&t_url_date);

    if (FALSE == b_ret)
    {
        DBG_INFO(("\n\t\t%s Get url date info fail!\n", __FUNCTION__));
        _um_clear_temp();
        return TRUE;
    }

    DBG_INFO(("\n\t\t%s %d URL date info: %lld\n", __FUNCTION__, __LINE__, t_url_date));

    _save_url_date_to_file(t_url_date);

    if (t_exist_date < t_url_date)
    {
        return FALSE;
    }

    _um_clear_temp();

    return TRUE;
}

BOOL a_um_get_url_date_info_utc_sec(TIME_T* pt_url_date)
{
    BOOL b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == pt_url_date)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_url_date_info_utc_sec(pt_url_date);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL a_um_get_exist_date_info_utc_sec(TIME_T* pt_url_date)
{
    BOOL b_ret = FALSE;

    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    if (NULL == pt_url_date)
    {
        DBG_ERROR(("\n\t\t%s INVALID argument!\n", __FUNCTION__));
        return FALSE;
    }

    b_ret = _get_exist_date_info_utc_sec(pt_url_date);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL a_is_dld_um_in_flash(VOID)
{
    return _is_dld_um_in_flash();
}

BOOL a_show_dld_um(VOID)
{
    CHAR  s_um_dir[255] = {0};
    CHAR  s_cmd[255] = {0};
    INT32 i4_ret = 0;

    DBG_INFO(("\n%s(%d)Show downloaded UM\n",__FUNCTION__,__LINE__));

    if (_is_dld_um_in_flash())
    {
        _get_manual_dir(s_um_dir);
        i4_ret = c_sprintf(s_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s%s\"]\n", s_um_dir, "/index.htm");
        DBG_INFO(("\n\t\t####%s(%d)c_sprintf i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        cmd_convert_send_cmd(s_cmd);

        DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be TRUE after send command.\n",__FUNCTION__,__LINE__));
        _um_set_status_is_displaying(TRUE);

        return TRUE;
    }
    else
    {
        DBG_INFO(("\n\t\t%s(%d)Something wrong!\n",__FUNCTION__,__LINE__));
        //return FALSE;
    }

    return TRUE;
}

BOOL a_um_clear_temp(VOID)
{
    DBG_INFO(("\n%s start! %d\n", __FUNCTION__, __LINE__));

    return _um_clear_temp();
}

VOID a_um_set_opera_start_status(BOOL b_status)
{
    _um_set_opera_start_status(b_status);
}

BOOL a_um_get_opera_start_status(VOID)
{
    return _um_get_opera_start_status();
}

VOID a_um_set_opera_exit_status(BOOL b_status)
{
    _um_set_opera_exit_status(b_status);
}

BOOL a_um_get_opera_exit_status(VOID)
{
    return _um_get_opera_exit_status();
}
VOID a_um_set_status_is_displaying(BOOL b_status)
{
    _um_set_status_is_displaying(b_status);
}

BOOL a_um_get_status_is_displaying(VOID)
{
    return _um_get_status_is_displaying();
}

/*-----------------------------------------------------------------------------
 * Name:  a_um_is_server_avalible
 *
 * Description: do speedtest from specified url address
 *
 * Inputs:  NULL
 *
 * Outputs: TRUE  server connect avalible
 *          other server connect disable
 *
 * Returns: TRUE  server connect avalible
 *          other server connect disable
 ----------------------------------------------------------------------------*/

BOOL a_um_is_server_avalible(VOID)
{
    CHAR  s_cmd[MAX_BUF]   = {0};
    CHAR  s_url[MAX_BUF]   = {0};
    BOOL  b_ret            = FALSE;
    FILE  *pf_fl           = NULL;

    /* get URL */
    b_ret = _get_download_url(s_url);
    if (FALSE == b_ret)
    {
        return FALSE;
    }

    /* test server is avalible or not. */
    /* -T 10:timeout 10s */
    c_sprintf(s_cmd, "/3rd/bin/wget -T 10 --spider %s 2>&1", s_url);
    DBG_INFO(("\n\t\t%s Get url header: %s\n", __FUNCTION__, s_cmd));
    /* open a process  */
    pf_fl = popen(s_cmd, "r");
    if (NULL == pf_fl)
    {
        DBG_INFO(("[UM]\n\t\t%s popen fail! \n", __FUNCTION__));
        return FALSE;
    }

    /* reset b_ret */
    b_ret = FALSE;
    c_memset(s_tmp, 0, MAX_BUF*2*sizeof(CHAR));
    /* get data from pf_fl */
    while (fgets(s_tmp, MAX_BUF*2*sizeof(CHAR), pf_fl) != NULL && !feof(pf_fl))
    {
        DBG_INFO(("[UM]\n\t\t%s open! buf: %s\n", __FUNCTION__, s_tmp));
        /* connect to server success */
        if (c_strstr(s_tmp, "OK") != NULL)
        {
            DBG_INFO(("[UM]\n\t\t%s connect to server success! buf: %s\n", __FUNCTION__, s_tmp));
            b_ret = TRUE;
            break;
        }
    }
    /* release */
    if (NULL != pf_fl)
    {
        pclose(pf_fl);
    }
    DBG_INFO(("[UM]\n\t\t%s end,b_ret:%d! \n", __FUNCTION__, (INT32)b_ret));
    return b_ret;

}
#endif
#endif

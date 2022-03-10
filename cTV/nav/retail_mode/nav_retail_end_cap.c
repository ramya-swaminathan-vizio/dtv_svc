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
 * $RCSfile: nav_fav_lst.c,v $
 * $Revision: #3 $
 * $Date: 2015/06/22 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/118 $
 * $SWAuthor: $
 * $MD5HEX: 74c34b81b9b0a7ed0de302079c3cacb3 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_3D_RETAIL_DEMO_MODE
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "u_fm.h"
#include "c_fm.h"
#include "c_fm_mfw.h"
#include "c_scc.h"

#include "am/a_am.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_ui.h"
#include "app_util/rmv_dev/a_rmv_dev.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/a_custom_log.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "mmp/a_mmp.h"
#include "mmp/video_engine/a_video_engine.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"

#include "res/nav/pic_mode/pic_mode_custom.h"

#include "nav_retail_mode.h"
#include "wizard_anim/a_wzd.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define NAV_PLAY_FILE_NAME_MAX_LEN  (128)
#define NAV_PLAY_FILE_PATH_MAX_LEN  (128)
#define NAV_PLAY_FILE_MAX_NUM       (16)
#define NAV_USB_ACTIVE_MAX_NUM      (16)
#define NAV_FILE_TXT_LEN            (4)
#define NAV_USB_ACTIVE_MAX_INDEX    (15)

#define NAV_INTERNAL_VIDEO_ROOT     "/demo/retail_demo"

#define NAV_REM_TXT_FILE_NAME       "vizio_demo.txt"
#define NAV_PLAY_DELAY_TIME         (2000)/* ms */



#define ONE_LINE_MAX_LEN            (512)

#define CMD_INDEX_KEY_CODE          ((UINT8)(0))
#define CMD_INDEX_FILE_PATH         ((UINT8)(1))
#define CMD_INDEX_NUM_LOOPS         ((UINT8)(2))
#define CMD_INDEX_PAUSE_DURATION    ((UINT8)(3))
#define CMD_INDEX_DEMO              ((UINT8)(4))
#define CMD_INDEX_PIC_MODE          ((UINT8)(5))

//#define ONE_LINE_CMD_MAX_NUM        (CMD_INDEX_PIC_MODE+1)
#define ONE_LINE_CMD_MAX_NUM        ((UINT8)(21))

typedef struct
{
    CHAR        s_file_path[NAV_PLAY_FILE_PATH_MAX_LEN];    /* Path of the video file on the USB stick */
    UINT32      ui4_num_loops;       /* Number of times to play, 1-100, or 0 for infinite */
    UINT32      ui4_pause_duration;  /* Number of seconds to pause between each loop, 1-999, or 0 for no delay */
    UINT8       ui1_demo;            /* Internal Retail Demo slideshow (Flash or HTML5) overlays the video coming from the current input, 0 for off */
    CHAR        s_pic_mode[32];      /* Select the Picture Mode to be used for this demo file, default is Vivid */
    UINT32      ui4_key_code;        /* Hex code for the desired Key_Trigger, 0x0-0xFFFF */
	UINT32      ui4_backlight;       /* Backlight(SDR) or Tone Mapping(HDR), 0-100 ,default is 100 */
	UINT32      ui4_brightness;      /* Brghtness ,0-100 ,default is 50*/
	UINT32      ui4_contrast;        /* Contrast ,0-100 ,default is 50*/
	UINT32      ui4_color;           /* Color , 0-100 , default is 75*/
	INT32       i4_tint;             /* Tint ,-50-50 or -32-32 ,default is 0 */
	UINT32      ui4_sharpness;       /* Sharpness ,0-100 ,Vivsid default */
	CHAR        s_black_detail[32];  /* Black Detail ,Off Low Medium or High ,default is OFF */
	CHAR        s_active_array[32];  /* Active Full Array ,Off Low Medium or High ,default is High */
	UINT32      ui4_reduce_judder;   /* Reduce Judder ,0-10 , defualt is 5 */
	UINT32      ui4_reduce_motion_blur;  /* Reduce Motion Blur ,0-10 ,default is 5 */
	float       f4_gamma;                /* Gamma ,1.8 2.0 2.1 2.2 2.4 ,default is 2.1 */
	CHAR        s_super_resolution[32];
	CHAR        s_local_contrast[32];
	CHAR        s_contour_smoothing[32];
} _DEMO_PARAM_T;

typedef struct __NAV_REM_USB_ACTIVE_INFO_T
{
    RMV_DEV_OPEN_ID_T           t_rmv_dev_open_id;
    CHAR                        s_play_file_name[NAV_PLAY_FILE_MAX_NUM][NAV_PLAY_FILE_NAME_MAX_LEN];
    CHAR                        s_play_file_path[NAV_PLAY_FILE_MAX_NUM][NAV_PLAY_FILE_PATH_MAX_LEN];
    UINT8                       ui1_mode[NAV_PLAY_FILE_MAX_NUM];
    UINT8                       ui1_3d_fmt[NAV_PLAY_FILE_MAX_NUM];
    UINT8                       ui1_play_file_list_count;
    UINT8                       ui1_play_file_count;
    BOOL                        b_is_usb_file_playing;

    BOOL                        b_is_internal_video;
    _DEMO_PARAM_T               t_param[NAV_PLAY_FILE_MAX_NUM];
    UINT8                       ui1_file_count;
} _NAV_REM_USB_ACTIVE_INFO_T;
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
typedef struct
{
	UINT16		ui2_need_backup_pq;
	UINT16 		ui2_mmp_pq;
	UINT32      ui4_backlight;
	UINT32      ui4_brightness;
	UINT32      ui4_contrast;
	UINT32      ui4_color;
	INT32       i4_tint;
	UINT32      ui4_sharpness;
	UINT32      ui4_black_detail;
	UINT32      ui4_active_array;
	UINT32      ui4_reduce_judder;
	UINT32      ui4_reduce_motion_blur;
	UINT32      ui4_gamma;
	UINT32      ui4_super_resolution;
	UINT32      ui4_local_contrast;
	UINT32      ui4_contour_smoothing;
}_BACKUP_MMP_PQ_VALUE;
#endif

extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
extern RETAIL_MODE_RUNNING_TYPE_T a_nav_retail_mode_check_running_type(VOID);
extern VOID msg_convert_custom_resume_nav();
extern VOID msg_convert_custom_stop_native();


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _NAV_REM_USB_ACTIVE_INFO_T*   pt_active_info_tmp = NULL;
static _NAV_REM_USB_ACTIVE_INFO_T   t_internal_active_info;
static _NAV_REM_USB_ACTIVE_INFO_T   t_usb_active_info[NAV_USB_ACTIVE_MAX_NUM];
static UINT32                       ui4_g_usb_active_index = NAV_USB_ACTIVE_MAX_INDEX;
static UINT32                       ui4_g_nfy_id = RMV_DEV_NULL_NFY_ID;
static CHAR                         s_mnt_path[NAV_PLAY_FILE_PATH_MAX_LEN];
static UINT32                       ui4_pt_mnt_count = 0;
static BOOL                         b_g_is_playing = FALSE;
static CHAR                         as_eng_name[16] = "retail_mode_eng";
static BOOL                         b_mmp_has_init = FALSE;
static BOOL                         b_need_rescan_internal_video = FALSE;
static UINT8                        ui1_g_current_play_file_idx = 0;
static UINT8                        ui1_g_play_video_count = 0;
SCC_3D_MODE_T                       e_g_3d_mode_type = SCC_3D_MODE_OFF;
RMV_DEV_NFY_REC_T                   t_g_usb_info_in_out;
static HANDLE_T                     h_play_timer;
static HANDLE_T                     h_play_video_timer;
static UINT32                       played_time = 0;
static CHAR                         s_pic_mode[ACFG_PRE_SET_PIC_MODE_NUM+ACFG_CUST_SET_PIC_MODE_NUM][64];
static BOOL                         b_video_paused = FALSE;

#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
static _BACKUP_MMP_PQ_VALUE         t_mmp_pq_value;
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _retail_mode_apply_3d_setting(VOID);
static INT32 _retail_mode_stop_curt_channel(VOID);
static VOID _retail_mode_video_engine_sc_nfy_fct(
                    VOID* pv_tag1,
                    VOID* pv_tag2,
                    VOID* pv_tag3
                    );
static VOID _retail_mode_video_engine_nfy_fct(
                    MMP_VE_NFY_CODE_T e_nfy_code,       /* out  */
                    VOID*             pv_param          /* out  */
                    );
static INT32 _retail_mode_play_video(CHAR*   as_play_path);
static INT32 _retail_mode_stop_video(VOID);
static INT32 _nav_rem_usb_info_clean_mem(_NAV_REM_USB_ACTIVE_INFO_T* pt_usb_active_info);
static INT32 _nav_retail_mode_stop_movie_play(_NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info);
static INT32 _nav_retail_mode_search_play_movie(_NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info,
                                                 UINT32*  pui4_usb_active_index,
                                                 BOOL*  pb_is_playing);
static INT32 _nav_retail_mode_play_movie(_NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info);
/*
static INT32 _rem_check_txt_file(const CHAR* ps_file_path);
static INT32 _rem_check_cma_num(CHAR* ps_file_name,
                                UINT8* pui1_num);
static INT32 _rem_check_play_file(_NAV_REM_USB_ACTIVE_INFO_T* pt_usb_active_info,
                                  const CHAR* ps_file_path);
static INT32 _rem_check_one_dir(_NAV_REM_USB_ACTIVE_INFO_T* pt_usb_active_info,
                                  const CHAR* ps_dir_name,
                                  BOOL b_is_to_ser_txt);
*/
static VOID _rem_usb_process (VOID* pv_arg1, VOID* pv_arg2, VOID* pv_arg3);
static VOID _rem_usb_nfy_cb(
                    VOID*               pv_unused,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param
                    );

static UINT16 _nav_retail_mode_get_pq_idx(VOID);
static UINT16 _nav_retail_mode_get_next_pq_idx(CHAR* s_pic_mode_name);
static VOID _nav_retail_mode_get_pic_mode(VOID);
static VOID _nav_retail_mode_set_pic_mode(UINT16 ui2_idx);
static VOID _nav_retail_mode_check_pic_mode(VOID);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static int _is_file_exist(const char* ps_file_path)
{
    if (ps_file_path == NULL)
    {
        return -1;
    }
    if (access(ps_file_path, F_OK) == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

static void _del_char(char* buf, char ch, int size)
{
    int i,j;
    int quote_num = 0;

    if (buf == NULL)
    {
        return;
    }

    for (i = 0, j = 0; i < size && j < size; i++)
    {
        if (buf[i] == '\"')
        {
            if (i == 0 || buf[i-1] != '\\')
            {
                quote_num ++;
            }
        }
        if (quote_num % 2 != 0 || buf[i] != ch)
        {
            buf[j++] = buf[i];
        }
    }
    buf[j] = 0;
}

BOOL usb_file_is_playing(VOID)
{
	return t_usb_active_info->b_is_usb_file_playing;
}
static int _tok_demo_syntax(char* ps_syntax, _NAV_REM_USB_ACTIVE_INFO_T* pt_active_info)
{
    char*   syntax = NULL;
    char*   token = NULL;
    char*   cmd[ONE_LINE_CMD_MAX_NUM] = {NULL};
    size_t  len = 0, len_max = 0;
    int     count = 0;
    int     i = 0, j = 0;
    int     has_key_code = 0;
    int     ret = 0;

    _DEMO_PARAM_T*  pt_param = NULL;

    if (ps_syntax == NULL || pt_active_info == NULL)
    {
        return -1;
    }

    pt_param = &(pt_active_info->t_param[pt_active_info->ui1_file_count]);

    len = strlen(ps_syntax);
    len_max = len + 1 + ONE_LINE_CMD_MAX_NUM;

    /* insert ' ' between ',' and ',' */
    syntax = malloc(len_max);
    if (NULL == syntax)
    {
        return -1;
    }
    memset(syntax, 0, len_max);

    for (i = 0, j = 0; i < len && j < len_max; i++, j++)
    {
        syntax[j] = ps_syntax[i];

        /* need insert ' ' */
        if (ps_syntax[i] == ',' && i+1 < len && ps_syntax[i+1] == ',')
        {
            j++;
            syntax[j] = ' ';
        }
    }

    //printf("[%lu] %s\n", strlen(syntax), syntax);

    /* tok synatx */
    token = strtok(syntax, ",");

    while (token != NULL && count < ONE_LINE_CMD_MAX_NUM)
    {
        if (token == NULL)
        {
            ret = -1;
            goto out;
        }

        cmd[count] = malloc(strlen(token) + 1);
        if (NULL == cmd[count])
        {
            ret = -1;
            goto out;
        }
        memset(cmd[count], 0, strlen(token) + 1);
        strncpy(cmd[count], token, strlen(token) + 1);

        //printf("[%d] %s\n", count, cmd[count]);

        count++;
        token = strtok(NULL, ",");
    }

    if (cmd[0] == NULL || strlen(cmd[0]) < 3)  /* 0x42 or x.mp4 */
    {
        ret = -1;
        goto out;
    }

    /* get cmd */

    //key trigger 0x0-0xFFFF
    if (strncmp(cmd[0], "0x", 2) == 0)
    {
        sscanf(cmd[0], "0x%4x", &(pt_param->ui4_key_code));
        has_key_code = 1;

        //printf("--> key_code: [%s - %u].\n", cmd[0], pt_param->ui4_key_code);
    }
    else if (strncmp(cmd[0], "0X", 2) == 0)
    {
        sscanf(cmd[0], "0X%4x", &(pt_param->ui4_key_code));
        has_key_code = 1;

        //printf("--> key_code: [%s - %u].\n", cmd[0], pt_param->ui4_key_code);
    }
    else
    {
        has_key_code = 0;
    }


    //file path
    if (0+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[0+has_key_code] == NULL || strlen(cmd[0+has_key_code]) < 4)  /* x.mp4 */
    {
        ret = -1;
        goto out;
    }
    if (pt_active_info->b_is_internal_video)
    {
        c_snprintf(pt_param->s_file_path, NAV_PLAY_FILE_PATH_MAX_LEN, "%s/%s", NAV_INTERNAL_VIDEO_ROOT, cmd[0+has_key_code]);
    }
    else
    {
        c_snprintf(pt_param->s_file_path, NAV_PLAY_FILE_PATH_MAX_LEN, "%s/%s", s_mnt_path, cmd[0+has_key_code]);
    }

    // check file is exist or not
    if (_is_file_exist(pt_param->s_file_path) != 0)
    {
        pt_param->s_file_path[0] = '\0';
        ret = -1;
        goto out;
    }
    //printf("--> file_path: [%s].\n", pt_param->s_file_path);

    if (1)
    {
        strncpy(pt_active_info->s_play_file_name[pt_active_info->ui1_file_count], cmd[0+has_key_code], 127);
        strncpy(pt_active_info->s_play_file_path[pt_active_info->ui1_file_count], pt_param->s_file_path, 127);
        pt_active_info->ui1_mode[pt_active_info->ui1_file_count] = 0;
        pt_active_info->ui1_3d_fmt[pt_active_info->ui1_file_count] = 16;
    }


    //num_loops
    if (1+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[1+has_key_code] == NULL)
    {
        pt_param->ui4_num_loops = 0;
    }
    else
    {
        pt_param->ui4_num_loops = atoi(cmd[1+has_key_code]);
    }

    if (pt_param->ui4_num_loops > 100)
    {
        pt_param->ui4_num_loops = 100;
    }
    //printf("--> num_loops: [%u].\n", pt_param->ui4_num_loops);


    //pause_duration
    if (2+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[2+has_key_code] == NULL)
    {
        pt_param->ui4_pause_duration = 0;
    }
    else
    {
        pt_param->ui4_pause_duration = atoi(cmd[2+has_key_code]);
    }

    if (pt_param->ui4_pause_duration > 999)
    {
        pt_param->ui4_pause_duration = 999;
    }
    //printf("--> pause_duration: [%u].\n", pt_param->ui4_pause_duration);


    //pause_duration
    if (3+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[3+has_key_code] == NULL)
    {
        pt_param->ui1_demo = 0;
    }
    else
    {
        pt_param->ui1_demo = atoi(cmd[3+has_key_code]);
    }

    if (pt_param->ui1_demo > 1)
    {
        pt_param->ui1_demo = 1;
    }
    //printf("--> demo: [%u].\n", pt_param->ui1_demo);


    //pic_mode
    if (4+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[4+has_key_code] == NULL)
    {
		strcpy(pt_param->s_pic_mode, "Vivid");
    }
	else if(c_strcmp(cmd[4+has_key_code]," ")==0)
	{
		strcpy(pt_param->s_pic_mode, "Vivid");
	}
    else
    {

        strncpy(pt_param->s_pic_mode, cmd[4+has_key_code], 31);
    }

    //printf("--> pic_mode: [%s].\n\n", pt_param->s_pic_mode);

	//Backlight/ton e_mapping
	 if (5+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[5+has_key_code] == NULL)
	{
		 pt_param->ui4_backlight = 100;
	}
	else if(c_strcmp(cmd[5+has_key_code]," ")==0)
	{
		pt_param->ui4_backlight = 100;
	}
	else
	{
		pt_param->ui4_backlight = atoi(cmd[5+has_key_code]);

		if (pt_param->ui4_backlight > 100)
		{
			pt_param->ui4_backlight = 100;
		}
	}

	//printf("--> backlight: [%d].\n\n",  pt_param->ui4_backlight);

	//brightness
	if (6+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[6+has_key_code] == NULL)
	{
		pt_param->ui4_brightness = 50;
	}
	else if(c_strcmp(cmd[6+has_key_code]," ")==0)
	{
		pt_param->ui4_brightness = 50;
	}
	else
	{
		pt_param->ui4_brightness = atoi(cmd[6+has_key_code]);

		if (pt_param->ui4_brightness > 100)
		{
			 pt_param->ui4_brightness = 100;
		}
	}
	//printf("--> brightness: [%d].\n\n",  pt_param->ui4_brightness);

	//contrast
	if (7+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[7+has_key_code] == NULL)
	{
		pt_param->ui4_contrast = 50;
	}
	else if(c_strcmp(cmd[7+has_key_code]," ")==0)
	{
		pt_param->ui4_contrast = 50;
	}
	else
	{
		pt_param->ui4_contrast = atoi(cmd[7+has_key_code]);

		if (pt_param->ui4_contrast > 100)
		{
			 pt_param->ui4_contrast = 100;
		}

	}
	//printf("--> contrast: [%d].\n\n",  pt_param->ui4_contrast);

	//color
	if (8+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[8+has_key_code] == NULL)
	{
		pt_param->ui4_color = 75;
	}
	else if(c_strcmp(cmd[8+has_key_code]," ")==0)
	{
		pt_param->ui4_color = 75;
	}
	else
	{
		pt_param->ui4_color = atoi(cmd[8+has_key_code]);

		if (pt_param->ui4_color > 100)
		{
			 pt_param->ui4_color = 100 ;
		}
	}
	//printf("--> color: [%d].\n\n",  pt_param->ui4_color);

	//tint
	if (9+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[9+has_key_code] == NULL)
	{
		pt_param->i4_tint = 0;
	}
	else if(c_strcmp(cmd[9+has_key_code]," ")==0)
	{
		pt_param->i4_tint = 0;
	}
	else
	{
		pt_param->i4_tint = atoi(cmd[9+has_key_code]);
		if (pt_param->i4_tint < -50)
		{
			pt_param->i4_tint = -50;
		}
		else if (pt_param->i4_tint > 50)
		{
			 pt_param->i4_tint = 50 ;
		}
	}
	//printf("--> tint: [%d].\n\n",  pt_param->i4_tint);

	//sharpness
	if (10+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[10+has_key_code] == NULL)
	{
		pt_param->ui4_sharpness = 30;
	}
	else if(c_strcmp(cmd[10+has_key_code]," ")==0)
	{
		pt_param->ui4_sharpness = 30;
	}
	else
	{
		pt_param->ui4_sharpness = atoi(cmd[10+has_key_code]);

		if (pt_param->ui4_sharpness > 100)
		{
			pt_param->ui4_sharpness = 100;
		}
	}
	//printf("--> sharpness: [%d].\n\n",  pt_param->ui4_sharpness);

	//black detail
	if (11+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[11+has_key_code] == NULL)
	{
		strcpy(pt_param->s_black_detail, "Off");
	}
	else if(c_strcmp(cmd[11+has_key_code]," ")==0)
	{
		strcpy(pt_param->s_black_detail, "Off");
	}
	else
	{
		strcpy(pt_param->s_black_detail,cmd[11+has_key_code]);
	}
	//printf("--> black detail: [%s].\n\n",  pt_param->s_black_detail);

	//active array
	if (12+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[12+has_key_code] == NULL)
	{
		strcpy(pt_param->s_active_array, "High");
	}
	else if(c_strcmp(cmd[12+has_key_code]," ")==0)
	{
		strcpy(pt_param->s_active_array, "High");
	}
	else
	{
		strcpy(pt_param->s_active_array, cmd[12+has_key_code]);
	}
	//printf("--> active array: [%s].\n\n",  pt_param->s_active_array);

	//reduce judder
	if (13+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[13+has_key_code] == NULL)
	{
		pt_param->ui4_reduce_judder = 5;
	}
	else if(c_strcmp(cmd[13+has_key_code]," ")==0)
	{
		pt_param->ui4_reduce_judder = 5;
	}
	else
	{
		pt_param->ui4_reduce_judder = atoi(cmd[13+has_key_code]);

		if (pt_param->ui4_reduce_judder > 10)
		{
			pt_param->ui4_reduce_judder = 10;
		}
	}
	//printf("--> reduce judder: [%d].\n\n",  pt_param->ui4_reduce_judder);

	//reduce motion
	if (14+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[14+has_key_code] == NULL)
	{
		pt_param->ui4_reduce_motion_blur = 5;
	}
	else if(c_strcmp(cmd[14+has_key_code]," ")==0)
	{
		pt_param->ui4_reduce_motion_blur = 5;
	}
	else
	{
		pt_param->ui4_reduce_motion_blur = atoi(cmd[14+has_key_code]);

		if (pt_param->ui4_reduce_motion_blur > 10)
		{
			pt_param->ui4_reduce_motion_blur = 10;
		}
	}
	//printf("--> reduce motion: [%d].\n\n",  pt_param->ui4_reduce_motion_blur);

	//gamma
	if (15+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[15+has_key_code] == NULL)
	{
		pt_param->f4_gamma = 2.1;
	}
	else if(c_strcmp(cmd[15+has_key_code]," ")==0)
	{
		pt_param->f4_gamma = 2.1;
	}
	else
	{
		if ( c_strcmp(cmd[15+has_key_code],"1.8") == 0
		   || c_strcmp(cmd[15+has_key_code],"2.0") == 0
		   || c_strcmp(cmd[15+has_key_code],"2.1") == 0
		   || c_strcmp(cmd[15+has_key_code],"2.2") == 0
		   || c_strcmp(cmd[15+has_key_code],"2.4") == 0)
		{
			  pt_param->f4_gamma = atof(cmd[15+has_key_code]);
		}
		else
		{
			 pt_param->f4_gamma = 2.1;
		}
	}
	//super resolution
	if (16+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[16+has_key_code] == NULL)
	{
		strcpy(pt_param->s_super_resolution, "High");
	}
	else if(c_strcmp(cmd[16+has_key_code]," ")==0)
	{
		strcpy(pt_param->s_super_resolution, "High");
	}
	else
	{
		strcpy(pt_param->s_super_resolution, cmd[16+has_key_code]);
	}

	//local contrast
	if (17+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[17+has_key_code] == NULL)
	{
		strcpy(pt_param->s_local_contrast, "High");
	}
	else if(c_strcmp(cmd[17+has_key_code]," ")==0)
	{
		strcpy(pt_param->s_local_contrast, "High");
	}
	else
	{
		strcpy(pt_param->s_local_contrast, cmd[17+has_key_code]);
	}

	//contour smoothing
	if (18+has_key_code >= ONE_LINE_CMD_MAX_NUM || cmd[18+has_key_code] == NULL)
	{
		strcpy(pt_param->s_contour_smoothing, "High");

	}
	else if(c_strcmp(cmd[18+has_key_code]," ")==0)
	{
		strcpy(pt_param->s_contour_smoothing, "High");
	}
	else
	{
		strcpy(pt_param->s_contour_smoothing, cmd[18+has_key_code]);
	}

	//printf("--> gamma: [%f].\n\n",  pt_param->f4_gamma);


    //count++
    pt_active_info->ui1_file_count++;

out:
    for (i = 0;i < count;i++)
    {
        if (cmd[i] != NULL)
        {
            free(cmd[i]);
            cmd[i] = NULL;
        }
    }
    if (syntax != NULL)
    {
        free(syntax);
        syntax = NULL;
    }

    return ret;

}

/* Read a file, parse, etc. */
static INT32 _do_demo(CHAR *ps_file_path, _NAV_REM_USB_ACTIVE_INFO_T* pt_active_info)
{
    FILE*   f;
    int     line = 0;
    size_t  len = 0;
    char    buf[ONE_LINE_MAX_LEN] = {0};
    int     ret = 0;

    if (ps_file_path == NULL || pt_active_info == NULL)
    {
        return NAVR_INV_ARG;
    }

    pt_active_info->ui1_file_count = 0;

    if (strncmp(ps_file_path, NAV_INTERNAL_VIDEO_ROOT, c_strlen(NAV_INTERNAL_VIDEO_ROOT)) == 0)
    {
        pt_active_info->b_is_internal_video = TRUE;
    }
    else
    {
        pt_active_info->b_is_internal_video = FALSE;
    }

    if ((f = fopen(ps_file_path, "rb")) == NULL)
    {
        DBG_LOG_PRINT(("[retail_mode] error:fail to read.\n"));
        return NAVR_FAIL;
    }

    /* read and parse line by line */
    while(fgets(buf, ONE_LINE_MAX_LEN, f) != NULL)
    {
        if (pt_active_info->ui1_file_count >= NAV_PLAY_FILE_MAX_NUM)
        {
            break;
        }

        line++;
        len = strlen(buf);

        if (buf[len-1] == '\n')
        {
            buf[len-1]='\0';
        }
        //printf("[%d, %ld] %s\n", line, strlen(buf), buf);

        /* 1. delete all empty character */
        _del_char(buf, '\n', strlen(buf));
        _del_char(buf, '\r', strlen(buf));
        _del_char(buf, '\t', strlen(buf));
        //_del_char(buf, ' ', strlen(buf));

        len = strlen(buf);

        /* 2. skip empty line */
        if (len == 0)
        {
            //printf("--> EMPTY line.\n");
            continue;
        }

        /* 3. skip comment line */
        if (buf[0] == '#')
        {
            //printf("--> # comment line.\n");
            continue;
        }

        DBG_LOG_PRINT(("%s\n", buf));

        /* 4. skip incorrect syntax format */
        if (len == strcspn (buf, ",") && len == strcspn (buf, "."))
        {
            //printf("--> should has '.' at least \n");
            continue;
        }

        /* 5. parse syntax */
        ret = _tok_demo_syntax(buf, pt_active_info);
        if (ret == 0)
        {
            //printf("--> parse %d line done.\n\n", line);
        }

    }

    fclose(f);

    pt_active_info->ui1_play_file_list_count = pt_active_info->ui1_file_count;
    pt_active_info->ui1_play_file_count = pt_active_info->ui1_file_count;

    DBG_LOG_PRINT(("[retail_mode]line:%d,count:%d.\n",__LINE__,pt_active_info->ui1_file_count));
	/* dump */
   if (1)
   {
	   int idx = 0;

	   for (idx = 0; idx < pt_active_info->ui1_file_count; idx++)
		{
			DBG_LOG_PRINT(("\n[retail_mode]--> idx: [%d].\n", idx));
			if (pt_active_info->t_param[idx].ui4_key_code != 0)
			{
				DBG_LOG_PRINT(("[retail_mode]--> key_code: [%u].\n", pt_active_info->t_param[idx].ui4_key_code));
			}
			DBG_LOG_PRINT(("[retail_mode]--> file_path: [%s].\n", pt_active_info->t_param[idx].s_file_path));
			DBG_LOG_PRINT(("[retail_mode]--> num_loops: [%u].\n", pt_active_info->t_param[idx].ui4_num_loops));
			DBG_LOG_PRINT(("[retail_mode]--> pause_duration: [%u].\n", pt_active_info->t_param[idx].ui4_pause_duration));
			DBG_LOG_PRINT(("[retail_mode]--> demo: [%u].\n", pt_active_info->t_param[idx].ui1_demo));
			DBG_LOG_PRINT(("[retail_mode]--> pic_mode: [%s].\n", pt_active_info->t_param[idx].s_pic_mode));
			DBG_LOG_PRINT(("[retail_mode]--> backlight: [%u].\n", pt_active_info->t_param[idx].ui4_backlight));
			DBG_LOG_PRINT(("[retail_mode]--> brightness: [%u].\n", pt_active_info->t_param[idx].ui4_brightness));
			DBG_LOG_PRINT(("[retail_mode]--> contrast: [%u].\n", pt_active_info->t_param[idx].ui4_contrast));
			DBG_LOG_PRINT(("[retail_mode]--> color: [%u].\n", pt_active_info->t_param[idx].ui4_color));
			DBG_LOG_PRINT(("[retail_mode]--> tint: [%u].\n", pt_active_info->t_param[idx].i4_tint));
			DBG_LOG_PRINT(("[retail_mode]--> sharpness: [%u].\n", pt_active_info->t_param[idx].ui4_sharpness));
			DBG_LOG_PRINT(("[retail_mode]--> black_detail: [%s].\n", pt_active_info->t_param[idx].s_black_detail));
			DBG_LOG_PRINT(("[retail_mode]--> active_array: [%s].\n", pt_active_info->t_param[idx].s_active_array));
			DBG_LOG_PRINT(("[retail_mode]--> reduce_judder: [%u].\n", pt_active_info->t_param[idx].ui4_reduce_judder));
			DBG_LOG_PRINT(("[retail_mode]--> reduce_motion_blur: [%u].\n", pt_active_info->t_param[idx].ui4_reduce_motion_blur));
			DBG_LOG_PRINT(("[retail_mode]--> gamma: [%.1f].\n", pt_active_info->t_param[idx].f4_gamma));
			DBG_LOG_PRINT(("[retail_mode]--> super resolution: [%s].\n", pt_active_info->t_param[idx].s_super_resolution));
			DBG_LOG_PRINT(("[retail_mode]--> local contrast: [%s].\n", pt_active_info->t_param[idx].s_local_contrast));
			DBG_LOG_PRINT(("[retail_mode]--> contour smoothing: [%s].\n", pt_active_info->t_param[idx].s_contour_smoothing));

		}

   }

    return NAVR_OK;
}

static INT32 _do_demo_for_usb(char *ps_mnt_path, _NAV_REM_USB_ACTIVE_INFO_T* pt_active_info)
{
    CHAR    s_path_txt[NAV_PLAY_FILE_PATH_MAX_LEN] = {0};
    INT32   i4_ret = NAVR_OK;

    if (ps_mnt_path == NULL || pt_active_info == NULL)
    {
        return NAVR_INV_ARG;
    }

    c_snprintf(s_path_txt, NAV_PLAY_FILE_PATH_MAX_LEN, "%s/%s", ps_mnt_path, NAV_REM_TXT_FILE_NAME);

    if (_is_file_exist(s_path_txt) != 0)
    {
        DBG_LOG_PRINT(("[Retail] file isn't exist.\r\n"));
        return NAVR_NOT_EXIST;
    }

    i4_ret = _do_demo(s_path_txt, pt_active_info);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;

}

static INT32 _do_demo_for_internal(_NAV_REM_USB_ACTIVE_INFO_T* pt_active_info)
{
    CHAR    s_path_txt[NAV_PLAY_FILE_PATH_MAX_LEN] = {0};
    INT32   i4_ret = NAVR_OK;

    if (pt_active_info == NULL)
    {
        return NAVR_INV_ARG;
    }

    c_snprintf(s_path_txt, NAV_PLAY_FILE_PATH_MAX_LEN, "%s/%s", NAV_INTERNAL_VIDEO_ROOT, NAV_REM_TXT_FILE_NAME);

    if (_is_file_exist(s_path_txt) != 0)
    {
        DBG_LOG_PRINT(("[Retail] file isn't exist.\r\n"));
        return NAVR_FAIL;
    }

    i4_ret = _do_demo(s_path_txt, pt_active_info);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
UINT16  _get_mmp_cur_pq_mode(VOID)
{
	INT16	          i2_pre_val = 0;

	/*picture mode*/
	if (t_mmp_pq_value.ui2_need_backup_pq == FALSE)
	{
		a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
				&i2_pre_val);
		t_mmp_pq_value.ui2_mmp_pq = i2_pre_val;
		t_mmp_pq_value.ui2_need_backup_pq = TRUE;
	}
	return 0;
}

static UINT16  _get_mmp_cur_pq_value(VOID)
{
	INT16	          i2_pre_val = 0;


/*backlight*/
	 a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT),
	 	           			  &i2_pre_val);
	t_mmp_pq_value.ui4_backlight = i2_pre_val;

/*backlight*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI),
				 	          &i2_pre_val);
	t_mmp_pq_value.ui4_brightness = i2_pre_val;

/*Contrast*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT),
				             &i2_pre_val);
	t_mmp_pq_value.ui4_contrast = i2_pre_val;

/*Color*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT),
				 	          &i2_pre_val);
	t_mmp_pq_value.ui4_color = i2_pre_val;

/*Tint*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE),
				 	          &i2_pre_val);
	t_mmp_pq_value.i4_tint = i2_pre_val;

/*Sharpness*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP),
					 	       &i2_pre_val);
	t_mmp_pq_value.ui4_sharpness = i2_pre_val;

/*Black Detail*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN),
				         &i2_pre_val);
	t_mmp_pq_value.ui4_black_detail = i2_pre_val;


/*Active Full Array*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING),
                         &i2_pre_val);
    t_mmp_pq_value.ui4_active_array = i2_pre_val;


/*Reduce Judder*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION),
                         &i2_pre_val);
    t_mmp_pq_value.ui4_reduce_judder = i2_pre_val;


/* Reduce Motion Blur*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION),
                         &i2_pre_val);
    t_mmp_pq_value.ui4_reduce_motion_blur = i2_pre_val;


/*Gamma*/
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA),
			 	           &i2_pre_val);
	t_mmp_pq_value.ui4_gamma = i2_pre_val;

//super resolution
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX),
			 	           &i2_pre_val);
	t_mmp_pq_value.ui4_super_resolution = i2_pre_val;

//local contrast
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST),
			 	           &i2_pre_val);
	t_mmp_pq_value.ui4_local_contrast = i2_pre_val;


//contour smoothing
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING),
			 	           &i2_pre_val);
	t_mmp_pq_value.ui4_contour_smoothing = i2_pre_val;


	return 0;
}


VOID a_set_mmp_cur_pq_value(UINT16 ui2_is_cur_exit)
{

	UINT16			  ui2_id ;
	INT16			  i2_new_val;
	UINT16   		  pui2_idx = 0;
  	UINT16   		  ui2_pq_idx = 0;

	ui2_pq_idx = _nav_retail_mode_get_pq_idx();
	pui2_idx = ACFG_CUST_INPUT_GRP_MMP*ACFG_PIC_MODE_NUM + ui2_pq_idx;

/*backlight*/
	i2_new_val = t_mmp_pq_value.ui4_backlight;
	if (i2_new_val <= 100)
	{
		acfg_set_int16_by_idx(IDX_DISP_BACK_LIGHT,
									   pui2_idx,
									   i2_new_val);
	}

/*Brghtness*/
	i2_new_val = t_mmp_pq_value.ui4_brightness;
	if (i2_new_val <= 100)
	{
		acfg_set_int16_by_idx(IDX_VID_BRI,
									   pui2_idx,
									   i2_new_val);
	}

/*Contrast*/
	i2_new_val = t_mmp_pq_value.ui4_contrast;
	if (i2_new_val <= 100)
	{
		acfg_set_int16_by_idx(IDX_VID_CNT,
									   pui2_idx,
									   i2_new_val);
	}

/*Color*/
	i2_new_val = t_mmp_pq_value.ui4_color;
	if (i2_new_val <= 100)
	{
		acfg_set_int16_by_idx(IDX_VID_SAT,
									   pui2_idx,
									   i2_new_val);
	}


/*Tint*/
	i2_new_val = t_mmp_pq_value.i4_tint;
	if (i2_new_val >= -50 && i2_new_val <= 50)
	{
		acfg_set_int16_by_idx(IDX_VID_HUE,
									   pui2_idx,
									   i2_new_val);
	}

/*Sharpness*/
	i2_new_val = t_mmp_pq_value.ui4_sharpness;
	if (i2_new_val <= 100)
	{
		acfg_set_int16_by_idx(IDX_VID_SHP,
									   pui2_idx,
									   i2_new_val);
	}

/*Black Detail*/
	i2_new_val = t_mmp_pq_value.ui4_black_detail;
	acfg_set_int16_by_idx(IDX_VID_LUMA,
								   pui2_idx,
								   i2_new_val);

/*Active Full Array*/
    i2_new_val = t_mmp_pq_value.ui4_active_array;
    acfg_set_int16_by_idx(IDX_CUSTOM_DIMMING,
                                   pui2_idx,
                                   i2_new_val);


/*Reduce Judder*/
    i2_new_val = t_mmp_pq_value.ui4_reduce_judder;
    acfg_set_int16_by_idx(IDX_CUSTOM_JUDDER_REDUCTION,
                                   pui2_idx,
                                   i2_new_val);

/* Reduce Motion Blur*/
    i2_new_val = t_mmp_pq_value.ui4_reduce_motion_blur;
    acfg_set_int16_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION,
                                   pui2_idx,
                                   i2_new_val);

/*Gamma*/
	i2_new_val = t_mmp_pq_value.ui4_gamma;
	acfg_set_int16_by_idx(IDX_CUST_GAMMA,
								   pui2_idx,
								   i2_new_val);

//super resolution
	i2_new_val = t_mmp_pq_value.ui4_super_resolution;
	acfg_set_int16_by_idx(IDX_CUSTOM_SUPER_RESOLUTION,
								   pui2_idx,
								   i2_new_val);
//local contrast
	i2_new_val = t_mmp_pq_value.ui4_local_contrast;
	acfg_set_int16_by_idx(IDX_VID_LOCAL_CONTRAST,
								   pui2_idx,
								   i2_new_val);


//contour smoothing
	i2_new_val = t_mmp_pq_value.ui4_contour_smoothing;
	acfg_set_int16_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING,
								   pui2_idx,
								   i2_new_val);


/*Picture Mode*/
	if (ui2_is_cur_exit == TRUE)
	{
		i2_new_val = t_mmp_pq_value.ui2_mmp_pq;
		ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
		a_cfg_av_set(ui2_id, (INT16)i2_new_val);
		a_cfg_av_update(ui2_id);
		t_mmp_pq_value.ui2_need_backup_pq = FALSE;
	}
}
#endif
static INT16 _refresh_new_pic_mode_paremeter( _NAV_REM_USB_ACTIVE_INFO_T* pt_active_info,UINT8 ui1_current_play_file_idx)
{
	UINT16	          ui2_id ;
	INT16	          i2_pre_val = 0;
	INT16             i2_new_val;


	/*backlight*/
	i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_backlight;

	if (i2_new_val >= 0 && i2_new_val <= 100)
	{
		 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);

		 a_cfg_av_get(ui2_id, &i2_pre_val);

		 if (i2_new_val != i2_pre_val)
		 {
			a_cfg_av_set(ui2_id, (INT16)i2_new_val);
			a_cfg_av_update(ui2_id);

		 }
	}

	/*Brghtness*/
	i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_brightness;

	if (i2_new_val >= 0 && i2_new_val <= 100)
	{
		 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);
		 a_cfg_av_get(ui2_id, &i2_pre_val);

		 if (i2_new_val != i2_pre_val)
		 {
			a_cfg_av_set(ui2_id, (INT16)i2_new_val);
			a_cfg_av_update(ui2_id);

		 }
	}

	/*Contrast*/
	i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_contrast;

	if (i2_new_val >= 0 && i2_new_val <= 100)
	{
		 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);
		 a_cfg_av_get(ui2_id, &i2_pre_val);

		 if (i2_new_val != i2_pre_val)
		 {
			 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
			 a_cfg_av_update(ui2_id);
		 }
	}


	/*Color*/
	i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_color;

	if (i2_new_val >= 0 && i2_new_val <= 100)
	{
		 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT);
		 a_cfg_av_get(ui2_id, &i2_pre_val);

		 if (i2_new_val != i2_pre_val)
		 {
			 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
			 a_cfg_av_update(ui2_id);
		 }
	}



	/*Tint*/
	i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].i4_tint;

	if (i2_new_val >= -50 && i2_new_val <= 50)
	{
		 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE);
		 a_cfg_av_get(ui2_id, &i2_pre_val);

		 if (i2_new_val != i2_pre_val)
		 {
			 a_cfg_av_set(ui2_id, i2_new_val);
			 a_cfg_av_update(ui2_id);
		 }
	}



	/*Sharpness*/
	i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_sharpness;

	if (i2_new_val >= 0 && i2_new_val <= 100)
	{
		 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP);

		 if (i2_new_val != i2_pre_val)
		 {
			 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
			 a_cfg_av_update(ui2_id);
		 }
	}


	/*Black Detail*/
	char s_black_detail[32];

	c_strncpy(s_black_detail,pt_active_info->t_param[ui1_current_play_file_idx].s_black_detail,32);

	if (c_strcmp(s_black_detail,"Off") == 0)
	{
		i2_new_val = 0;
	}
	else if (c_strcmp(s_black_detail,"Low") == 0)
	{
		i2_new_val = 1;
	}
	else if (c_strcmp(s_black_detail,"Medium") == 0)
	{
		i2_new_val = 2;
	}
	else if (c_strcmp(s_black_detail,"High") == 0)
	{
		i2_new_val = 3;
	}
	else
	{
		i2_new_val = 0;
	}

	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN);
	a_cfg_av_get(ui2_id, &i2_pre_val);
	if (i2_new_val != i2_pre_val)
	{
		 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
		 a_cfg_av_update(ui2_id);
	}

    /*Active Full Array*/
    char s_active_array[32];
    BOOL b_support = a_cfg_cust_get_support_local_dimming();
    if (b_support)
    {
        c_strncpy(s_active_array,pt_active_info->t_param[ui1_current_play_file_idx].s_active_array,32);
        
        if (c_strcmp(s_active_array,"Off") == 0)
        {
            i2_new_val = 0;
        }
        else if (c_strcmp(s_active_array,"Low") == 0)
        {
            i2_new_val = 1;
        }
        else if (c_strcmp(s_active_array,"Medium") == 0)
        {
            i2_new_val = 2;
        }
        else if (c_strcmp(s_active_array,"High") == 0)
        {
            i2_new_val = 3;
        }
        else
        {
            i2_new_val = 3;
        }
        
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING);
        a_cfg_av_get(ui2_id, &i2_pre_val);
        if (i2_new_val != i2_pre_val)
        {
             a_cfg_av_set(ui2_id, (INT16)i2_new_val);
             a_cfg_av_update(ui2_id);
        }

    }

#ifdef APP_SUPPPORT_FRC

    /*Reduce Judder*/
    i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_reduce_judder;

    if (i2_new_val >= 0 && i2_new_val <= 10)
    {
         ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION);

         if (i2_new_val != i2_pre_val)
         {
             a_cfg_av_set(ui2_id, (INT16)i2_new_val);
             a_cfg_av_update(ui2_id);
         }
    }


    /* Reduce Motion Blur*/
    i2_new_val = pt_active_info->t_param[ui1_current_play_file_idx].ui4_reduce_motion_blur;

    if (i2_new_val >= 0 && i2_new_val <= 10)
    {
         ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION);

         if (i2_new_val != i2_pre_val)
         {
             a_cfg_av_set(ui2_id, (INT16)i2_new_val);
             a_cfg_av_update(ui2_id);
         }
    }

#endif

	/*Gamma*/
	float f4_new_val= pt_active_info->t_param[ui1_current_play_file_idx].f4_gamma;
	char s_gamma_value[16];

	c_sprintf(s_gamma_value,"%.1f",f4_new_val);

	if (c_strcmp(s_gamma_value,"1.8") == 0)
	{
		i2_new_val = 0;
	}
	else if (c_strcmp(s_gamma_value,"2.0") == 0)
	{
		i2_new_val = 1;
	}
	else if (c_strcmp(s_gamma_value,"2.1") == 0)
	{
		i2_new_val = 2;
	}
	else if (c_strcmp(s_gamma_value,"2.2") == 0)
	{
		i2_new_val = 3;
	}
	else if (c_strcmp(s_gamma_value,"2.4") == 0)
	{
		i2_new_val = 4;
	}
	else
	{
		i2_new_val = 2;
	}

	 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA);
	 a_cfg_av_get(ui2_id, &i2_pre_val);

	 if (i2_new_val != i2_pre_val)
	 {
		 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
		 a_cfg_av_update(ui2_id);
	}


	/*Super Resolution*/
	char s_super_resolution[32];
	c_strncpy(s_super_resolution,pt_active_info->t_param[ui1_current_play_file_idx].s_super_resolution,32);

	if (c_strcmp(s_super_resolution,"Off") == 0)
	{
		i2_new_val = 0;
	}
	else if (c_strcmp(s_super_resolution,"Low") == 0)
	{
		i2_new_val = 1;
	}
	else if (c_strcmp(s_super_resolution,"Medium") == 0)
	{
		i2_new_val = 2;
	}
	else if (c_strcmp(s_super_resolution,"High") == 0)
	{
		i2_new_val = 3;
	}
	else
	{
		i2_new_val = 3;
	}

	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX);
	a_cfg_av_get(ui2_id, &i2_pre_val);
	if (i2_new_val != i2_pre_val)
	{
		 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
		 a_cfg_av_update(ui2_id);
	}



	/*Local Contrast*/
	char s_local_contrast[32];
	c_strncpy(s_local_contrast,pt_active_info->t_param[ui1_current_play_file_idx].s_local_contrast,32);

	if (c_strcmp(s_local_contrast,"Off") == 0)
	{
		i2_new_val = 0;
	}
	else if (c_strcmp(s_local_contrast,"Low") == 0)
	{
		i2_new_val = 1;
	}
	else if (c_strcmp(s_local_contrast,"Medium") == 0)
	{
		i2_new_val = 2;
	}
	else if (c_strcmp(s_local_contrast,"High") == 0)
	{
		i2_new_val = 3;
	}
	else
	{
		i2_new_val = 3;
	}

	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST);
	a_cfg_av_get(ui2_id, &i2_pre_val);
	if (i2_new_val != i2_pre_val)
	{
		 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
		 a_cfg_av_update(ui2_id);
	}


	/*Contour Smoothing*/
	char s_contour_smoothing[32];
	c_strncpy(s_contour_smoothing,pt_active_info->t_param[ui1_current_play_file_idx].s_contour_smoothing,32);

	if (c_strcmp(s_contour_smoothing,"Off") == 0)
	{
		i2_new_val = 0;
	}
	else if (c_strcmp(s_contour_smoothing,"Low") == 0)
	{
		i2_new_val = 1;
	}
	else if (c_strcmp(s_contour_smoothing,"Medium") == 0)
	{
		i2_new_val = 2;
	}
	else if (c_strcmp(s_contour_smoothing,"High") == 0)
	{
		i2_new_val = 3;
	}
	else
	{
		i2_new_val = 3;
	}

	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING);
	a_cfg_av_get(ui2_id, &i2_pre_val);
	if (i2_new_val != i2_pre_val)
	{
		 a_cfg_av_set(ui2_id, (INT16)i2_new_val);
		 a_cfg_av_update(ui2_id);
	}


	return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _retail_mode_apply_3d_setting
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _retail_mode_apply_3d_setting(VOID)
{
    SCC_3D_MODE_T  e_3d_mode_type = SCC_3D_MODE_OFF;

    if (pt_active_info_tmp->ui1_mode[ui1_g_current_play_file_idx])
    {
        /* current is 3D file */
        switch (pt_active_info_tmp->ui1_3d_fmt[ui1_g_current_play_file_idx])
        {
            case 0:
                e_3d_mode_type = SCC_3D_MODE_FRM_SEQ;
                break;

            case 1:
                e_3d_mode_type = SCC_3D_MODE_SIDE_SIDE;
                break;

            case 2:
                e_3d_mode_type = SCC_3D_MODE_TOP_AND_BTM;
                break;

            case 3:
                e_3d_mode_type = SCC_3D_MODE_REALD;
                break;

            case 4:
                e_3d_mode_type = SCC_3D_MODE_SENSIO;
                break;

            default:
                e_3d_mode_type = SCC_3D_MODE_OFF;
                break;
        }
    }
    else
    {
        e_3d_mode_type = SCC_3D_MODE_OFF;
    }
    e_g_3d_mode_type = e_3d_mode_type;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _retail_mode_stop_curt_channel
 * Description  This function disable the video.
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _retail_mode_stop_curt_channel(VOID)
{
    INT32    i4_ret  = NAVR_OK;
    HANDLE_T h_svctx = NULL_HANDLE;

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN,
                                  &h_svctx);
    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_stop(h_svctx);
    if (TVR_OK != i4_ret)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _retail_mode_play_video_delay_fct
 * Description:
 *      nav amp/audio plugin mute TV Speaker timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _retail_mode_play_video_delay_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    if (1 == ui1_g_play_video_count)
    {
   		 _refresh_new_pic_mode_paremeter(pt_active_info_tmp,ui1_g_current_play_file_idx);
        a_mmp_video_engine_play(as_eng_name);
    }
    else
    {
        a_mmp_video_engine_close(as_eng_name);
        a_mmp_video_engine_open(as_eng_name,
               pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path);
		a_mmp_video_engine_play(as_eng_name);
    }
    c_timer_stop(h_play_video_timer);

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _retail_mode_play_video_delay_nfy
 * Description:
 *      nav usb plugin detection mute TV Speaker timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _retail_mode_play_video_delay_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_retail_mode_play_video_delay_fct, NULL, NULL, NULL);

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _retail_mode_play_video_delay_start
 * Description:
 *      start nav amp/audio plugin mute TV Speaker timer
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _retail_mode_play_video_delay_start(UINT32 ui4_pause_duration)
{
    INT32                       i4_ret = NAVR_OK;
    //NAV_CEC_CUSTOM_AMP_DLG_T*       pt_this = &t_g_nav_cec_custom_amp_dlg;

    c_timer_stop(h_play_video_timer);
    if (NULL_HANDLE != h_play_video_timer)
    {
        i4_ret = c_timer_start(h_play_video_timer,
                               ui4_pause_duration,
                               X_TIMER_FLAG_ONCE,
                               _retail_mode_play_video_delay_nfy,
                               NULL);
        if (OSR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _retail_mode_video_engine_sc_nfy_fct
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static VOID _retail_mode_video_engine_sc_nfy_fct(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    MMP_VE_NFY_CODE_T   e_nfy_code = (MMP_VE_NFY_CODE_T)(UINT32)pv_tag1;
    BOOL                b_media_error_notify = (BOOL)(UINT32)pv_tag2;
    UINT32              ui4_pause_duration = 0;

    if (a_nav_retail_mode_check_running_type() == RETAIL_MODE_TYPE_VIDEO)
    {
        pt_active_info_tmp = &t_usb_active_info[ui4_g_usb_active_index];
    }
    else if(a_nav_retail_mode_check_running_type() == RETAIL_MODE_TYPE_VIDEO_INTERNAL)
    {
        pt_active_info_tmp = &t_internal_active_info;
    }
    else
    {
        NAV_LOG_ON_FAIL(NAVR_FAIL);
        return ;
    }

    if (MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK == e_nfy_code)
    {
        pt_active_info_tmp->b_is_usb_file_playing = TRUE;
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
		_get_mmp_cur_pq_mode();
#endif
        _nav_retail_mode_check_pic_mode();
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
		_get_mmp_cur_pq_value();
#endif
        _retail_mode_apply_3d_setting();
		_refresh_new_pic_mode_paremeter(pt_active_info_tmp,ui1_g_current_play_file_idx);
        a_mmp_video_engine_play(as_eng_name);
    }
    else if (MMP_VE_NFY_CODE_MEDIA_OPEN_ERR == e_nfy_code)
    {
        ui1_g_current_play_file_idx++;
        ui1_g_current_play_file_idx %= ui1_g_play_video_count;

        a_mmp_video_engine_open(as_eng_name,
                   pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path);
		a_mmp_video_engine_play(as_eng_name);
    }
    else if (MMP_VE_NFY_CODE_MEDIA_STOP_EOS == e_nfy_code)
    {
        if (1 == ui1_g_play_video_count)
        {
            if (pt_active_info_tmp->t_param[0].ui4_pause_duration > 0)
            {
                ui4_pause_duration = 1000 * pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].ui4_pause_duration;
                DBG_LOG_PRINT(("[retail_mode]line:%d,delay:%dms.\n",__LINE__,ui4_pause_duration));
                _retail_mode_play_video_delay_start(ui4_pause_duration);
            }
            else
            {
                a_mmp_video_engine_close(as_eng_name);
                a_mmp_video_engine_open(as_eng_name,
                       pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path);
				a_mmp_video_engine_play(as_eng_name);
            }
        }
        else if (ui1_g_play_video_count > 1)
        {
            if (pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].ui4_pause_duration > 0)
            {
                ui4_pause_duration = 1000 * pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].ui4_pause_duration;
                DBG_LOG_PRINT(("[retail_mode]line:%d,delay:%dms.\n",__LINE__,ui4_pause_duration));
            }
            if(pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].ui4_num_loops > 0)
            {
                played_time++;
                DBG_LOG_PRINT(("[retail_mode]line:%d,file:%s,played:%d.\n",__LINE__,pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path,played_time));
                if (pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].ui4_num_loops == played_time)
                {
                    played_time = 0;
                    ui1_g_current_play_file_idx++;
                    ui1_g_current_play_file_idx %= ui1_g_play_video_count;

                    /*check pic mode.*/
                    _nav_retail_mode_check_pic_mode();
                }
            }
            if (ui4_pause_duration > 0)
            {
                _retail_mode_play_video_delay_start(ui4_pause_duration);
            }
            else
            {
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
            	a_set_mmp_cur_pq_value(FALSE);
#endif
                a_mmp_video_engine_close(as_eng_name);
                a_mmp_video_engine_open(as_eng_name,
                       pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path);
				a_mmp_video_engine_play(as_eng_name);
            }

        }
    }
    else if ((MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT == e_nfy_code) && (FALSE == b_media_error_notify))
    {
        /* not surpport file */
        DBG_LOG_PRINT(("This file:[%s] not to be support, SHOW NOT SUPPORT DIALOG\n",
            pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path));
            //t_usb_active_info[ui4_g_usb_active_index].s_play_file_path[ui1_g_current_play_file_idx]));


        a_mmp_video_engine_close(as_eng_name);
        nav_retail_mode_show_warning_dialog();

        if (ui1_g_play_video_count > 1)
        {
            ui1_g_current_play_file_idx++;
            ui1_g_current_play_file_idx %= ui1_g_play_video_count;

            DBG_LOG_PRINT(("\nui1_g_current_play_file_idx=%d, ui1_g_play_video_count=%d, now togo file:[%s]\n",
                        ui1_g_current_play_file_idx, ui1_g_play_video_count,
                        pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_file_path));
            //t_usb_active_info[ui4_g_usb_active_index].s_play_file_path[ui1_g_current_play_file_idx]));
        }
    }

    return ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _retail_mode_video_engine_nfy_fct
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static VOID _retail_mode_video_engine_nfy_fct(
                    MMP_VE_NFY_CODE_T   e_nfy_code,       /* out  */
                    VOID*               pv_param          /* out  */
                    )
{
    if((MMP_VE_NFY_CODE_MEDIA_OPEN_ERR == e_nfy_code) ||
       (MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK == e_nfy_code) ||
       (MMP_VE_NFY_CODE_MEDIA_STOP_EOS == e_nfy_code) ||
       (MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT == e_nfy_code)
      )
    {
        nav_request_context_switch(
                    _retail_mode_video_engine_sc_nfy_fct,
                    (VOID*)e_nfy_code,
                    (VOID*)pv_param,
                    NULL
                    );
        return;
    }
}

static VOID _nav_retail_mode_stop_wzd(
                    VOID*                    pv_param1,
                    VOID*                    pv_param2,
                    VOID*                    pv_param3
                    )
{
    static UINT8 ui1_crnt_input_src = 0;

    if ((BOOL)(UINT32)pv_param1)
    {
        UINT8  ui1_isl_num = 0;
        ISL_REC_T  t_isl_rec = {0};

        a_isl_get_num_rec(&ui1_isl_num);

        for (UINT8 ui1_idx = 0; ui1_idx < ui1_isl_num; ++ui1_idx)
        {
            a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            if ((INP_SRC_TYPE_VTRL  == t_isl_rec.e_src_type) && (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type))
            {
                a_cfg_av_get_input_src(SN_PRES_MAIN_DISPLAY, &ui1_crnt_input_src);
                a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
                break;
            }
        }
    }
    else
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, ui1_crnt_input_src);
        a_amb_enable_system_key(FALSE);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _retail_mode_play_video
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _retail_mode_play_video(CHAR*   as_play_path)
{
    INT32         i4_ret = NAVR_OK;

    if (NULL == as_play_path)
    {
        NAV_CHK_FAIL( NAVR_INV_ARG );
    }

    DBG_LOG_PRINT(("[Retail] start play: %s.\n\r", as_play_path));

    a_cfg_custom_3D_setting_reset_3D_mode();

    if(FALSE == b_g_is_playing)
    {
        i4_ret = _retail_mode_stop_curt_channel();
        NAV_CHK_FAIL( i4_ret );
    }
    else
    {

        a_mmp_video_engine_close(as_eng_name);

        i4_ret = a_mmp_video_engine_destroy(as_eng_name);
        NAV_CHK_FAIL( AMBR_OK == i4_ret ? NAVR_OK : i4_ret);

    }

    /* Disable SCART bypass assocation */
    a_tv_set_scart_bypass_association(FALSE, FALSE);

    i4_ret = a_mmp_init_working_resource();
    NAV_CHK_FAIL( i4_ret );


    {
        UINT8 ui1_status = 0;
        a_icl_custom_get_cast_src_status(&ui1_status);
    }

    {
        UINT16 ui2_status = 0;
        a_cfg_get_wzd_status(&ui2_status);

        if ((WZD_UTIL_GET_STATUS_STATE(ui2_status) == WZD_STATE_RESUME_C4TV)
            && a_c4tv_apron_check_cast_state())
        {
            _nav_retail_mode_stop_wzd((VOID *)(UINT32)TRUE, NULL, NULL);
            a_wzd_stop_c4tv(_nav_retail_mode_stop_wzd);
        }
    }

    i4_ret = a_mmp_video_engine_create(as_eng_name,_retail_mode_video_engine_nfy_fct);
    NAV_CHK_FAIL( i4_ret == MMPR_OK ? NAVR_OK : i4_ret );

    i4_ret = a_mmp_video_engine_open(as_eng_name,
                                     as_play_path);
    NAV_CHK_FAIL( i4_ret == MMPR_OK ? NAVR_OK : i4_ret );

	i4_ret = a_mmp_video_engine_play(as_eng_name);
    NAV_CHK_FAIL( i4_ret == MMPR_OK ? NAVR_OK : i4_ret );

    b_g_is_playing = TRUE;
    b_video_paused = FALSE;

    a_tv_net_disable_keyroute(TRUE);
    a_amb_enable_system_key(FALSE);

    a_scrn_svr_set_enable(FALSE);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _retail_mode_stop_video
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _retail_mode_stop_video(VOID)
{
    a_mmp_video_engine_close(as_eng_name);
    a_mmp_video_engine_destroy(as_eng_name);

    b_g_is_playing  = FALSE;

    a_tv_net_disable_keyroute(FALSE);
    a_amb_enable_system_key(TRUE);

    a_scrn_svr_set_enable(TRUE);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_rem_usb_info_clean_mem
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_rem_usb_info_clean_mem(
                    _NAV_REM_USB_ACTIVE_INFO_T*     pt_usb_active_info
                    )
{
    UINT32                      ui4_i;
    //UINT32                      ui4_j;

    pt_usb_active_info->b_is_usb_file_playing = FALSE;
    for (ui4_i =0; ui4_i < NAV_PLAY_FILE_MAX_NUM; ui4_i++)
    {
        c_memset(pt_usb_active_info->t_param[ui4_i].s_file_path, 0, NAV_PLAY_FILE_PATH_MAX_LEN);
    }
    pt_usb_active_info->t_rmv_dev_open_id = RMV_DEV_NULL_OPEN_ID;
    pt_usb_active_info->ui1_play_file_count = 0;
    pt_usb_active_info->ui1_play_file_list_count = 0;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_stop_movie_play
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_stop_movie_play(
                    _NAV_REM_USB_ACTIVE_INFO_T* pt_usb_active_info
                    )
{
    _retail_mode_stop_video();
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_search_play_movie
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_search_play_movie(
                    _NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info,
                    UINT32*         pui4_usb_active_index,
                    BOOL*           pb_is_playing
                    )
{
    UINT32  ui4_j;

    /* update usb already play*/
    for (ui4_j =0; ui4_j<NAV_USB_ACTIVE_MAX_NUM; ui4_j++)
    {
        pt_usb_active_info = &t_usb_active_info[ui4_j];
        if(pt_usb_active_info->t_rmv_dev_open_id == RMV_DEV_NULL_OPEN_ID || pt_usb_active_info->b_is_usb_file_playing == FALSE)
        {
            continue;
        }

        *pb_is_playing = pt_usb_active_info->b_is_usb_file_playing;
        *pui4_usb_active_index = ui4_j;
        DBG_LOG_PRINT(("[Retail mode] %s :usb file already playing \n",__FUNCTION__));
        return NAVR_OK;
    }

    /* check play file count */
    for (ui4_j =0; ui4_j < NAV_USB_ACTIVE_MAX_NUM; ui4_j++)
    {
        pt_usb_active_info = &t_usb_active_info[ui4_j];
        if (pt_usb_active_info->t_rmv_dev_open_id == RMV_DEV_NULL_OPEN_ID || pt_usb_active_info->ui1_play_file_count == 0)
        {
            continue;
        }

        *pb_is_playing = pt_usb_active_info->b_is_usb_file_playing;
        *pui4_usb_active_index = ui4_j;
        return NAVR_OK;
    }

    /*  not search  */
    if (ui4_j >= NAV_USB_ACTIVE_MAX_NUM)
    {
        *pb_is_playing = FALSE;
        *pui4_usb_active_index = -1;
        DBG_LOG_PRINT(("[Retail mode] %s can not search play movie \n",__FUNCTION__));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 *      _nav_retail_mode_play_movie
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_play_movie(
					_NAV_REM_USB_ACTIVE_INFO_T* pt_usb_active_info
					)
{
	ui1_g_current_play_file_idx = 0;

	ui1_g_play_video_count = pt_usb_active_info->ui1_file_count;

	_retail_mode_play_video(pt_usb_active_info->t_param[ui1_g_current_play_file_idx].s_file_path);

	return NAVR_OK;
}

static VOID _nav_retail_mode_clean_usb_device(VOID)
{
    UINT16  ui2_i;

    for (ui2_i = 0; ui2_i < NAV_USB_ACTIVE_MAX_NUM; ui2_i++)
    {
        _nav_rem_usb_info_clean_mem(&t_usb_active_info[ui2_i]);
    }
}

VOID a_nav_retail_mode_clean_usb_device(VOID)
{
	_nav_retail_mode_clean_usb_device();
}

static INT32 _retail_rmv_device_scan (VOID)
{
    INT32   i4_ret;
    UINT32  ui4_i;
    UINT32  ui4_j;
    //UINT32  ui4_tmp;
    //UINT32  ui4_tmp_count;
    SIZE_T  z_size;
    UINT32  ui4_mnt_count = 0;
    RMV_DEV_DEVICE_STATUS_T     t_rmv_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    _NAV_REM_USB_ACTIVE_INFO_T  t_tmp_usb_active_info;


    /* Check all the mount point */
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if (i4_ret != RMVR_OK)
    {
        ui4_pt_mnt_count = 0;
        _nav_retail_mode_clean_usb_device();
        return NAVR_FAIL;
    }

    ui4_pt_mnt_count = ui4_mnt_count;
    if (ui4_mnt_count == 0)
    {
        _nav_retail_mode_clean_usb_device();
        return NAVR_OK;
    }
    for(ui4_j = 0 ;ui4_j < NAV_USB_ACTIVE_MAX_NUM; ui4_j++)
    {
         if((t_usb_active_info[ui4_j].t_rmv_dev_open_id != RMV_DEV_NULL_OPEN_ID)&&
            _is_file_exist(t_usb_active_info[ui4_j].s_play_file_path[0]) != 0)
         {
            DBG_LOG_PRINT(("%s_%d t_rmv_dev_open_id:%d  \n",__FUNCTION__,__LINE__,t_usb_active_info[ui4_j].t_rmv_dev_open_id));
            DBG_LOG_PRINT(("%s_%d s_play_file_path:%s  \n",__FUNCTION__,__LINE__,t_usb_active_info[ui4_j].s_play_file_path));
             _nav_rem_usb_info_clean_mem(&t_usb_active_info[ui4_j]);

         }
    }

    for (ui4_i = 0; ui4_i < ui4_mnt_count; ui4_i++)
    {
        /* Get the mount point status */
        i4_ret= a_rmv_dev_get_mnt_point_status_by_idx(ui4_i, &t_rmv_dev_status);
        if(i4_ret != RMVR_OK)
        {
            continue;
        }

        /* Check the mount point status */
        if(RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status) ||
           RMV_DEV_DEVICE_IS_UNSUPPORT(t_rmv_dev_status))
        {
            continue;
        }
        if (RMV_DEV_DEVICE_IS_DLNA_DMS(t_rmv_dev_status) ||
            RMV_DEV_DEVICE_IS_NET_NEIGHBOR(t_rmv_dev_status))
        {
            continue;
        }

        _nav_rem_usb_info_clean_mem(&t_tmp_usb_active_info);

        /* Open mount point */
        i4_ret = a_rmv_dev_open_mnt_point(ui4_i,&t_tmp_usb_active_info.t_rmv_dev_open_id);
        if(i4_ret != RMVR_OK)
        {
            continue;
        }

        /*search usb active info*/
        for(ui4_j = 0 ;ui4_j < NAV_USB_ACTIVE_MAX_NUM; ui4_j++)
        {
            if(t_tmp_usb_active_info.t_rmv_dev_open_id == t_usb_active_info[ui4_j].t_rmv_dev_open_id)
            {
                /*not need to update*/
                break;
            }
        }

        if(ui4_j < NAV_USB_ACTIVE_MAX_NUM)
        {
            /*not need to update*/
            continue;
        }

        /* Get the mount path */
        z_size = NAV_PLAY_FILE_PATH_MAX_LEN;
        i4_ret = a_rmv_dev_get_mnt_point(ui4_i, &z_size, s_mnt_path);
        if(i4_ret != RMVR_OK)
        {
            continue;
        }

        i4_ret = _do_demo_for_usb(s_mnt_path, &t_tmp_usb_active_info);
        if (t_tmp_usb_active_info.ui1_file_count == 0)
        {
            /*NOT_EXIST*/
            continue;
        }

        /*add active info*/
        for(ui4_j = 0 ;ui4_j < NAV_USB_ACTIVE_MAX_NUM; ui4_j++)
        {
             if(t_usb_active_info[ui4_j].t_rmv_dev_open_id == RMV_DEV_NULL_OPEN_ID)
             {
                  c_memcpy(&t_usb_active_info[ui4_j],&t_tmp_usb_active_info,sizeof(_NAV_REM_USB_ACTIVE_INFO_T));
                  break;
             }
        }

        if(ui4_j >= NAV_USB_ACTIVE_MAX_NUM)
        {
           NAV_LOG_ON_FAIL(NAVR_OUT_OF_MEM);
        }


    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name     _nav_retail_end_cap_usb_unplug_nfy
 * Description
 * Input
 * Output   -
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_retail_end_cap_usb_unplug_nfy_fct (
                    VOID*           pv_arg1,
                    VOID*           pv_arg2,
                    VOID*           pv_arg3
                    )
{
    INT32 i4_ret = NAVR_OK;
    i4_ret = a_nav_retail_mode_update_running_type();
    NAV_LOG_ON_FAIL(i4_ret);
    a_start_retail_mode_in_no_overlay();
}


/*-----------------------------------------------------------------------------
 * Name     _rem_usb_process
 * Description
 * Input
 * Output   -
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _rem_usb_process (
                    VOID*           pv_arg1,
                    VOID*           pv_arg2,
                    VOID*           pv_arg3
                    )
{
    RMV_DEV_NFY_ID_T e_nfy_id = (RMV_DEV_NFY_ID_T)(UINT32)pv_arg1;
    INT32 i4_ret = NAVR_OK;

    if(RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
        if (nav_retail_check_end_cap() == TRUE)
        {
            NAV_RETAIL_MODE_STATUS_T e_retail_status = NAV_RETAIL_MODE_ERROR;

            i4_ret = a_nav_retail_mode_get_status(&e_retail_status);
            NAV_LOG_ON_FAIL(i4_ret);
            /* if not ready to play video, just return */
            if( NAV_RETAIL_MODE_RUNNING != e_retail_status )
            {
                return;
            }
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
			nav_recover_mmp_pq_value_in_exit();
#endif
            i4_ret = a_nav_retail_mode_update_running_type();
            NAV_LOG_ON_FAIL(i4_ret);

			a_start_retail_mode_in_no_overlay();

        }
    }
    else if(RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
        UINT32  ui4_j;
        _NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info = NULL;
        RMV_DEV_NFY_REC_T*           pt_usb_info = NULL;
        RMV_DEV_OPEN_ID_T*           pt_rmv_dev_open_id = NULL;

        if(NULL == pv_arg2)
        {
            return;
        }
        pt_usb_info     = (RMV_DEV_NFY_REC_T*)(UINT32)pv_arg2;
        pt_rmv_dev_open_id = &(pt_usb_info->t_open_id);
        ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        for (ui4_j =0; ui4_j<NAV_USB_ACTIVE_MAX_NUM; ui4_j++)
        {
            pt_usb_active_info = &t_usb_active_info[ui4_j];
            /*remove active info*/
            if (pt_usb_active_info->t_rmv_dev_open_id == *pt_rmv_dev_open_id)
            {
                if (pt_usb_active_info->b_is_usb_file_playing)
                {
                    _nav_rem_usb_info_clean_mem(pt_usb_active_info);
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
					nav_recover_mmp_pq_value_in_exit();
#endif
                    /************stop the playing******************/
                    _nav_retail_mode_stop_movie_play (pt_usb_active_info);
                    ui4_g_usb_active_index = NAV_USB_ACTIVE_MAX_INDEX;
					a_nav_retail_mode_get_running_type();

                    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
                    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
                    {
                        TV_WIN_ID_T   e_tv_win_id;
                        ISL_REC_T   t_isl_rec;

                        nav_get_focus_id(&e_tv_win_id);
                        nav_get_isl_rec(e_tv_win_id, &t_isl_rec);

                        extern INT32 a_icl_custom_set_demo_status(UINT8 ui1_val);
                        a_icl_custom_set_demo_status(0);

                        nav_change_av_inp_by_rec(
                                    e_tv_win_id,
                                    &t_isl_rec,
                                    NULL
                                    );

						nav_request_context_switch (_nav_retail_end_cap_usb_unplug_nfy_fct,
													NULL,
													NULL,
													NULL);

                        break;
                    }
                }
                else
                {
                    _nav_rem_usb_info_clean_mem(pt_usb_active_info);
                    break;
                }
            }
        }

        if (*pt_rmv_dev_open_id != RMV_DEV_NULL_OPEN_ID)
        {
            RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;

            /* If the mount point has been opened, try if the device is still
               avaiable */
            a_rmv_dev_get_mnt_point_status(*pt_rmv_dev_open_id,
                                           &t_rmv_dev_status);

            if(RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status))
            {
                /* Free the resources */
                a_rmv_dev_close_mnt_point(*pt_rmv_dev_open_id);
                *pt_rmv_dev_open_id = RMV_DEV_NULL_OPEN_ID;
            }
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _rem_usb_nfy_cb
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static VOID _rem_usb_nfy_cb(
                    VOID*               pv_unused,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param
                    )
{
    if (pv_nfy_param != NULL)
    {
        c_memset (&t_g_usb_info_in_out, 0, sizeof(RMV_DEV_NFY_REC_T));
        c_memcpy (&t_g_usb_info_in_out,(RMV_DEV_NFY_REC_T*)(UINT32)pv_nfy_param,
                    sizeof(RMV_DEV_NFY_REC_T));

        /* Context switch to Navigator's thread. */
        nav_request_context_switch (_rem_usb_process,
                                    (VOID*)(UINT32)e_nfy_id,
                                    (VOID*)(UINT32)(&t_g_usb_info_in_out),
                                    NULL);
    }
    else
    {
        /* Context switch to Navigator's thread. */
        nav_request_context_switch (_rem_usb_process,
                                    (VOID*)(UINT32)e_nfy_id,
                                    NULL,
                                    NULL);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_get_pq_idx
 *
 * Description: Return the index of picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 _nav_retail_mode_get_pq_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_get_next_pq_idx
 * Description:Get pic mode id of the mode name.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _nav_retail_mode_get_next_pq_idx(CHAR* s_pic_mode_name)
{
    INT16      ui2_idx = 0;

    for (ui2_idx = 0; ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM+ACFG_CUST_SET_PIC_MODE_NUM; ui2_idx++)
    {
        if (c_strcmp(s_pic_mode[ui2_idx], s_pic_mode_name) == 0)
        {
            return (UINT16)ui2_idx;
        }
    }
    /*default mode is Vivid.*/
    ui2_idx = 0;
    DBG_LOG_PRINT(("[retail_mode]line:%d,check pic mode,idx_n:%d.\n",__LINE__,ui2_idx));

    return (UINT16)ui2_idx;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_get_pic_mode
 * Description:Get all pic modes.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_get_pic_mode(VOID)
{
    UINT16      ui2_idx = 0;
    CHAR        s_pic_mode_name[64] = {0};//MENU_CUST_PIC_MODE_NAME_MAX_LEN+2
    UTF16_T    w2s_str[64] = {0};
    c_memset(w2s_str,0,64);
    c_memset(s_pic_mode_name,0,32);

    for (ui2_idx = 0; ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM+ACFG_CUST_SET_PIC_MODE_NUM; ui2_idx++)
    {
        nav_pic_mode_get_elem_text_for_demo(ui2_idx, w2s_str);
        c_uc_w2s_to_ps((const UTF16_T*)w2s_str, s_pic_mode_name, 64);
        c_strcpy(s_pic_mode[ui2_idx],s_pic_mode_name);
        DBG_LOG_PRINT(("[retail_mode]line:%d,mode:%s.\n",__LINE__,s_pic_mode[ui2_idx]));
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_set_pic_mode
 * Description:Get set pic mode.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_set_pic_mode(UINT16 ui2_idx)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 (INT16)ui2_idx);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_check_pic_mode
 * Description:check pic mode.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_check_pic_mode(VOID)
{
    UINT16 idx;
    UINT16 next_idx;
    idx = _nav_retail_mode_get_pq_idx();
    next_idx = _nav_retail_mode_get_next_pq_idx(pt_active_info_tmp->t_param[ui1_g_current_play_file_idx].s_pic_mode);
    DBG_LOG_PRINT(("[retail_mode]line:%d,check pic mode,idx:%d,idx_n:%d.\n",__LINE__,idx,next_idx));

	if(idx != next_idx)
    {
        _nav_retail_mode_set_pic_mode(next_idx);
    }

    return;
}


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: a_nav_retail_mode_get_play_video_status
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL a_nav_retail_mode_get_play_video_status(VOID)
{
    return nav_retail_mode_get_is_play();
}

BOOL nav_retail_mode_get_is_play(VOID)
{
    return b_g_is_playing;
}

BOOL nav_retail_mode_get_is_video_paused(VOID)
{
    if(nav_retail_mode_get_is_play() == FALSE)
    {
       DBG_LOG_PRINT(("[Retail] Retail mode is not playing video\r\n"));

    }
    return b_video_paused;
}

/*----------------------------------------------------------------------------
 * Name: a_nav_retail_mode_get_3d_mode_type
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 a_nav_retail_mode_get_3d_mode_type(SCC_3D_MODE_T*  pe_3d_mode_type)
{
    *pe_3d_mode_type = e_g_3d_mode_type;
    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
  * Name
  * 	 _retail_mode_mmp_init
  * Description  -
  * Input		 -
  * Output		 -
  * Returns 	 -
  *---------------------------------------------------------------------------*/
 static VOID _retail_mode_mmp_init(VOID)
{
    HANDLE_T      h_mmp;
    INT32         i4_ret = NAVR_OK;

    if(FALSE == b_mmp_has_init)
    {
        i4_ret = c_aee_get_handle(MMP_NAME,
                                  &h_mmp);
        if(AEER_OK != i4_ret)
        {
            i4_ret = a_amb_start_app(MMP_NAME);
            NAV_CHK_FAIL( i4_ret );
        }
        b_mmp_has_init = TRUE;
    }

}



/*----------------------------------------------------------------------------
 * Name: nav_retail_end_cap_init
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 nav_retail_end_cap_init(VOID)
{
    UINT16  ui2_i;
    INT32   i4_ret;

    for (ui2_i = 0; ui2_i < NAV_USB_ACTIVE_MAX_NUM; ui2_i++)
    {
        _nav_rem_usb_info_clean_mem(&t_usb_active_info[ui2_i]);
    }
    _nav_rem_usb_info_clean_mem(&t_internal_active_info);

    /* monitor the usb device*/
    if(RMV_DEV_NULL_NFY_ID == ui4_g_nfy_id)
    {
        a_rmv_dev_reg_monitor( _rem_usb_nfy_cb,
                               NULL,
                               &ui4_g_nfy_id);
    }
    i4_ret = c_timer_create(&h_play_timer);
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = c_timer_create(&h_play_video_timer);
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }

	_retail_mode_mmp_init();

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_retail_end_cap_deinit
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_retail_end_cap_deinit(VOID)
{
    if (c_handle_valid(h_play_timer) == TRUE)
    {
        c_timer_delete(h_play_timer);
        h_play_timer = NULL_HANDLE;
    }
    if (c_handle_valid(h_play_video_timer) == TRUE)
    {
        c_timer_delete(h_play_video_timer);
        h_play_video_timer = NULL_HANDLE;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_retail_check_end_cap
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL nav_retail_check_end_cap(VOID)
{
    INT32                       i4_ret = NAVR_OK;
    UINT32                      ui4_usb_active_index = NAV_USB_ACTIVE_MAX_NUM;
    BOOL                        b_is_playing = FALSE;
    _NAV_REM_USB_ACTIVE_INFO_T  t_usb_active_info;
    BOOL                        b_ret = TRUE;

    i4_ret = _retail_rmv_device_scan();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_search_play_movie(
                                    &t_usb_active_info,
                                    &ui4_usb_active_index,
                                    &b_is_playing);


    if (i4_ret == NAVR_FAIL || ui4_usb_active_index == -1 || ui4_usb_active_index >= NAV_USB_ACTIVE_MAX_NUM)
    {
        DBG_LOG_PRINT(("[Retail] %s", (b_ret ? "b_ret: TRUE\r\n" : "b_ret: FALSE\r\n")));
        return FALSE;
    }

    DBG_LOG_PRINT(("[Retail] ", (b_is_playing ? "b_is_playing: TRUE\r\n" : "b_is_playing: FALSE\r\n")));

    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name: nav_retail_start_end_cap
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_retail_start_end_cap(VOID)
{
    INT32               i4_ret;
    UINT32              ui4_usb_active_index;
    BOOL                b_is_playing = FALSE;
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    CHAR                s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;

    _NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info = NULL;
    _NAV_REM_USB_ACTIVE_INFO_T   t_usb_active_info_tmp;
    DBG_LOG_PRINT(("[STORE] Enter.\n\r"));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
    {
        return NAVR_OK;
    }
    /*do not play in other active app*/
    {
        a_am_get_active_app (s_active_app);
        DBG_LOG_PRINT(("[Retail mode]current active app:%s\n", s_active_app));

        if (0 != c_strcmp(s_active_app, NAV_NAME) && a_nav_retail_mode_check_is_resume_nav())
        {
            c_dbg_dump_stack();
//            return NAVR_FAIL;
        }
    }

    /* Get all pic modes */
    c_memset(s_pic_mode, 0, sizeof(s_pic_mode));
    _nav_retail_mode_get_pic_mode();

    i4_ret = _nav_retail_mode_search_play_movie(
                                    &t_usb_active_info_tmp,
                                    &ui4_usb_active_index,
                                    &b_is_playing);
    NAV_CHK_FAIL(i4_ret);

    if(b_is_playing == TRUE)
    {
        DBG_LOG_PRINT(("[STORE] retail is playing.\n\r"));
        return NAVR_OK;
    }

    if (ui4_usb_active_index >= NAV_USB_ACTIVE_MAX_NUM)
    {
        return NAVR_FAIL;
    }
    ui4_g_usb_active_index = ui4_usb_active_index;

    pt_usb_active_info = &t_usb_active_info[ui4_usb_active_index];

    /* stop the flash playing */
    if (nav_retail_mode_is_flash_playing())
    {
        nav_retail_mode_send_cmd(FALSE);
        c_thread_delay(500);
    }

    _nav_retail_mode_play_movie(pt_usb_active_info);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_retail_stop_end_cap
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_retail_stop_end_cap(VOID)
{
    UINT8               ui1_i;

    DBG_LOG_PRINT(("[STORE] Enter.\n\r"));

    /* reset playing status */
    for (ui1_i =0; ui1_i<NAV_USB_ACTIVE_MAX_NUM; ui1_i++)
    {
        t_usb_active_info[ui1_i].b_is_usb_file_playing = FALSE;
    }

    _retail_mode_stop_video();

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_retail_end_cap_play_next_video
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_retail_end_cap_play_next_video(VOID)
{
    INT32 i4_ret;

    /* if the number of files  is greater than 1 ,play next */
    if (1 < ui1_g_play_video_count)
    {
        i4_ret = a_mmp_video_engine_open(as_eng_name,
                    t_usb_active_info[ui4_g_usb_active_index].s_play_file_path[ui1_g_current_play_file_idx]);
		i4_ret = a_mmp_video_engine_play(as_eng_name);

        if (MMPR_OK != i4_ret)
        {
            a_mmp_video_engine_close(as_eng_name);

            return NAVR_FAIL;
        }

        return NAVR_OK;
    }
    else
    {
        return NAVR_FAIL;
    }
}



/*----------------------------------------------------------------------------
 * Name: nav_retail_start_internal_video
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_retail_start_internal_video(VOID)
{
    //INT32               i4_ret;
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    CHAR                s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;

    _NAV_REM_USB_ACTIVE_INFO_T*  pt_usb_active_info = NULL;

    DBG_LOG_PRINT(("[STORE] Enter.\n\r"));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
    {
        return NAVR_OK;
    }

    /*do not play in other active app*/
    {
       a_am_get_active_app (s_active_app);
       DBG_LOG_PRINT(("[Retail mode]current active app:%s\n", s_active_app));

       if (0 != c_strcmp(s_active_app, NAV_NAME) && a_nav_retail_mode_check_is_resume_nav())
       {
           c_dbg_dump_stack();
 //          return NAVR_FAIL;
       }
    }

    /* Get all pic modes */
    c_memset(s_pic_mode, 0, sizeof(s_pic_mode));
    _nav_retail_mode_get_pic_mode();

    if (b_need_rescan_internal_video)
    {
        nav_retail_internal_demo_scan();
    }

    DBG_LOG_PRINT(("[Retail mode]retail_mode.line %d,cnt:%d!\n", __LINE__,t_internal_active_info.ui1_file_count));
    //if (ui4_usb_active_index >= NAV_USB_ACTIVE_MAX_NUM)
    if (t_internal_active_info.ui1_file_count == 0)
    {
        return NAVR_FAIL;
    }
    if (t_internal_active_info.b_is_usb_file_playing)
    {
        return NAVR_OK;
    }

    pt_usb_active_info = &t_internal_active_info;

    /* stop the flash playing */
    if (nav_retail_mode_is_flash_playing())
    {
        nav_retail_mode_send_cmd(FALSE);
        c_thread_delay(500);
    }

    _nav_retail_mode_play_movie(pt_usb_active_info);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_retail_stop_internal_video
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_retail_stop_internal_video(VOID)
{
    DBG_LOG_PRINT(("[STORE] Enter.\n\r"));

    /* reset playing status */
    t_internal_active_info.b_is_usb_file_playing = FALSE;

    b_need_rescan_internal_video = TRUE;

    _retail_mode_stop_video();

    return NAVR_OK;
}

INT32 nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_CTRL e_ctrl)
{
    DBG_LOG_PRINT(("[STORE] Enter.\n\r"));

    if (b_g_is_playing == FALSE)
    {
        DBG_LOG_PRINT(("[STORE] video is not playing\n\r"));
        return NAVR_NOT_ALLOW;
    }

    switch(e_ctrl)
    {
        case NAV_RETAIL_END_CAP_PAUSE:
        {
            if (b_video_paused == TRUE)
            {
                DBG_LOG_PRINT(("[STORE] video already pause\n\r"));
                return NAVR_NOT_ALLOW;
             }

            DBG_LOG_PRINT(("%s:%d,nav_retail_end_cap_ctrl_video pause video.\r\n",__FILE__,__LINE__));
            a_mmp_video_engine_pause(as_eng_name);
            b_video_paused = TRUE;
        }
        break;
        case NAV_RETAIL_END_CAP_PLAY:
        {
            if (b_video_paused == FALSE)
            {
                DBG_LOG_PRINT(("[STORE] video already play\n\r"));
                return NAVR_NOT_ALLOW;
            }
            DBG_LOG_PRINT(("%s:%d,nav_retail_end_cap_ctrl_video play video.\r\n",__FILE__,__LINE__));
			_refresh_new_pic_mode_paremeter(pt_active_info_tmp,ui1_g_current_play_file_idx);
            a_mmp_video_engine_play(as_eng_name);
            b_video_paused = FALSE;
        }
        break;
        default:
        {
            DBG_LOG_PRINT(("[STORE] video no action\n\r"));
            return NAVR_NO_ACTION;
        }
    }

    return NAVR_OK;
}

INT32 nav_retail_internal_demo_scan (VOID)
{
    INT32    i4_ret  = NAVR_OK;

    c_memset(&t_internal_active_info, 0, sizeof(t_internal_active_info));

    i4_ret = _do_demo_for_internal(&t_internal_active_info);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

BOOL nav_retail_internal_demo_check(VOID)
{
    INT32    i4_ret  = NAVR_OK;

    i4_ret = nav_retail_internal_demo_scan();

    if (i4_ret == NAVR_OK && t_internal_active_info.ui1_file_count > 0)
    {
        return TRUE;
    }

    return FALSE;
}
CHAR* nav_retail_get_internal_demo_file_name(VOID)
{

	if (t_internal_active_info.ui1_file_count > 0 )
	{
		return t_internal_active_info.s_play_file_name[ui1_g_current_play_file_idx];
	}

    return NULL;
}

#endif /* APP_3D_RETAIL_DEMO_MODE */

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
 * $RCSfile: zoom_mode.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Zoom mode is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "c_common.h"

#include "u_device_type.h"

#include "app_util/a_isl.h"
#include "app_util/a_tv.h"

#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"


#include "mapi_common.h"

//====================================================================================================

long long int MApi_Time_get_time_us(void)
{
	struct timeval now = {0};

	gettimeofday(&now, NULL);

	return (long long int)(now.tv_sec * 1000000LL + now.tv_usec);
}

long long int MApi_Time_get_time_ms(void)
{
	struct timeval now = {0};

	gettimeofday(&now, NULL);

	return (long long int)(now.tv_sec * 1000LL + (now.tv_usec/1000));
}

//======================================================================================================
/*
typedef enum
{
    ACFG_CUST_INPUT_GRP_TV = 0,
    ACFG_CUST_INPUT_GRP_CVBS,
    ACFG_CUST_INPUT_GRP_COMPONENT,
    ACFG_CUST_INPUT_GRP_HDMI1,
    ACFG_CUST_INPUT_GRP_HDMI2,
    ACFG_CUST_INPUT_GRP_HDMI3,
    ACFG_CUST_INPUT_GRP_HDMI4,
    ACFG_CUST_INPUT_GRP_VGA,
    ACFG_CUST_INPUT_GRP_MMP,
    ACFG_CUST_INPUT_GRP_VTRL,
    ACFG_CUST_INPUT_GRP_MAX
}   ACFG_CUST_INPUT_GRP_T;
UINT8 acfg_custom_get_input_grp(ISL_REC_T* pt_isl_rec);
*/

/*
typedef enum
{
    E_SYS_INPUT_SRC_UNKNOWN,

    E_SYS_INPUT_SRC_HDMI_1,
    E_SYS_INPUT_SRC_HDMI_2,
    E_SYS_INPUT_SRC_HDMI_3,
    E_SYS_INPUT_SRC_HDMI_4,

    E_SYS_INPUT_SRC_YPBPR,
    E_SYS_INPUT_SRC_CVBS,

    E_SYS_INPUT_SRC_TV,
    E_SYS_INPUT_SRC_MM,
    E_SYS_INPUT_SRC_VTRL,
} EnuSysInputSrc;
*/
#define MAP_INPUT_SRC_NAME(e, str) case e: pcSysInputSrcString = str; break
char* MApi_Sys_Get_CurInputSrcString(EnuSysInputSrc eSysInputSrc)
{
    char* pcSysInputSrcString = "NoName";

    switch(eSysInputSrc)
    {
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_UNKNOWN, "Unknown");

        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_HDMI_1,  "HDMI_1");
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_HDMI_2,  "HDMI_2");
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_HDMI_3,  "HDMI_3");
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_HDMI_4,  "HDMI_4");

        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_YPBPR,   "YPbPr");
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_CVBS,    "CVBS");
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_TV,      "TV");

        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_MM,      "MM");
        MAP_INPUT_SRC_NAME(E_SYS_INPUT_SRC_VTRL,    "VTRL");

        default:
            break;
    }

    return pcSysInputSrcString;
}


/* System names for presentation group names. */
#define SN_PRES_MAIN_DISPLAY  "snk_MainDisp"
//#define SN_PRES_AUX_DISPLAY   "snk_AuxDisp"
//#define SN_PRES_SUB_DISPLAY   "snk_SubDisp"


#define DEBUG_CUR_INPUT_SRC(x)  //x
EnuSysInputSrc MApi_Sys_Get_CurInputSrc(UINT8 u8WinIdx)
{
    if( u8WinIdx > 0 )
    {
        return E_SYS_INPUT_SRC_UNKNOWN;
    }

    //CHAR ac_curr_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    //a_cfg_av_get_disp_name(ac_curr_disp_name, sizeof(ac_curr_disp_name));
    //DEBUG_CUR_INPUT_SRC( DBG_LOG_PRINT(("[INPUT_SRC]{%s,%d} ac_curr_disp_name:{%s}\n", __FUNCTION__, __LINE__, ac_curr_disp_name)); );

    EnuSysInputSrc eSysInputSrc = E_SYS_INPUT_SRC_UNKNOWN;

    INT32 i4_ret = 0;
    ISL_REC_T t_isl_rec = {0};
    i4_ret = a_tv_get_crnt_isl_rec(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("\n[INPUT_SRC]{%s:%d} Error: a_tv_get_crnt_isl_rec() fail! i4_ret:%d\n", __FILE__, __LINE__, i4_ret));
        return E_SYS_INPUT_SRC_UNKNOWN;
    }

  #if 0
    UINT8 u8AcfgInputGrp = acfg_custom_get_input_grp(&t_isl_rec);
    DBG_LOG_PRINT(("[INPUT_SRC]{%s,%d} u8AcfgInputGrp:%d\n", __FUNCTION__, __LINE__, u8AcfgInputGrp));
  #endif

    DEBUG_CUR_INPUT_SRC( DBG_LOG_PRINT(("[INPUT_SRC]{%s,%d} ui1_id:%d, e_src_type:%d\n", __FUNCTION__, __LINE__, t_isl_rec.ui1_id, t_isl_rec.e_src_type)); );

    /* HDMI */
    //BOOL bIsSrcHDMI = FALSE;
    switch(t_isl_rec.e_src_type)
    {
        case INP_SRC_TYPE_AV:
          {
            DEBUG_CUR_INPUT_SRC( DBG_LOG_PRINT(("[INPUT_SRC]{%s,%d} INP_SRC_TYPE_AV: e_video_type:0x%X\n", __FUNCTION__, __LINE__, t_isl_rec.t_avc_info.e_video_type)); );
            switch(t_isl_rec.t_avc_info.e_video_type)
            {
                case DEV_AVC_HDMI:
                case DEV_AVC_DVI:
                    {
                        DEBUG_CUR_INPUT_SRC( DBG_LOG_PRINT(("[INPUT_SRC]{%s,%d} DEV_AVC_HDMI: ui1_internal_id:%d \n", __FUNCTION__, __LINE__, t_isl_rec.ui1_internal_id )); );

                        if( t_isl_rec.ui1_internal_id > 3 )
                        {
                            DBG_LOG_PRINT(("\n[INPUT_SRC]{%s:%d} Error: Invalid t_isl_rec.ui1_internal_id:%d\n", __FILE__, __LINE__, t_isl_rec.ui1_internal_id));
                            return E_SYS_INPUT_SRC_UNKNOWN;
                            break;
                        }
                        eSysInputSrc = (EnuSysInputSrc)(E_SYS_INPUT_SRC_HDMI_1 + t_isl_rec.ui1_internal_id);

                        if( t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI ) // HDMI
                        {
                            //bIsSrcHDMI = TRUE;
                            // Get HDMI color format ...
                        #if 0
                            ACFG_CUST_HDMI_COLOR_FORMAT_T eHdmiColorForamt = acfg_cust_video_get_hdmi_color_space();
                            DBG_LOG_PRINT(("[INPUT_SRC] Src is HDMI, hdmi_color => %d(%s)\n", eHdmiColorForamt, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorForamt) ));
                        #else
                            DEBUG_CUR_INPUT_SRC( DBG_LOG_PRINT(("[INPUT_SRC] Src is HDMI\n" )); );
                        #endif
                        }
                        else //if( t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI) // DVI
                        {
                            DEBUG_CUR_INPUT_SRC( DBG_LOG_PRINT(("[INPUT_SRC] Src is DVI\n" )); );
                        }
                    }
                    break;

                case DEV_AVC_Y_PB_PR:
                    eSysInputSrc = E_SYS_INPUT_SRC_YPBPR;
                    break;

                case DEV_AVC_COMP_VIDEO:
                case DEV_AVC_S_VIDEO:
                case DEV_AVC_COMBI:
                case DEV_AVC_SCART:
                    eSysInputSrc = E_SYS_INPUT_SRC_CVBS;
                    break;

                default:
                    eSysInputSrc = E_SYS_INPUT_SRC_UNKNOWN;
                    break;
            }
          }
            break;

        case INP_SRC_TYPE_TV:
            eSysInputSrc = E_SYS_INPUT_SRC_TV;
            break;
        case INP_SRC_TYPE_MM:
            eSysInputSrc = E_SYS_INPUT_SRC_MM;
            break;
        case INP_SRC_TYPE_VTRL:
            eSysInputSrc = E_SYS_INPUT_SRC_VTRL;
            break;

        case INP_SRC_TYPE_1394:
            eSysInputSrc = E_SYS_INPUT_SRC_1394;
            break;

        default:
            eSysInputSrc = E_SYS_INPUT_SRC_UNKNOWN;
            break;
    }

    return eSysInputSrc;
}

//====================================================================================================
unsigned int MApi_Sys_get_thread_id(void)
{
    pthread_t         self;

    self = pthread_self();

    return (unsigned int)self;

    //pthread_id_np_t   tid;
    //pthread_getunique_np(&self, &tid);
    //return (unsigned int)tid;
}
//====================================================================================================



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
 * $RCSfile: sml_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "res/app_util/config/acfg_custom.h"
#include "app_util/a_screen_mode.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "res/app_util/screen_mode/sml_mlm.h"
#include "c_svctx.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*
   Screen mode.
*/
#define SCREEN_MODE_SRC_VGA         (0)      /* VGA index. */
#define SCREEN_MODE_SRC_NON_VGA     (1)      /* Non-VGA index. */
#define SCREEN_MODE_SRC_NUM         (2)      /* Total number of classified input sources. */

#define SCREEN_MODE_ASP_4_3         (0)      /* 4:3 index. */
#define SCREEN_MODE_ASP_16_9        (1)      /* 16:9 index. */
#define SCREEN_MODE_ASP_ALL         (2)      /* Union of 4:3 and 16:9. */
#define SCREEN_MODE_ASP_1080P_120HZ (3)      /* 1080P 120HZ index. */
#define SCREEN_MODE_ASP_NUM         (4)      /* Total number of classified aspect ratios. Include 1080p 120hz stream */

#define SCREEN_MODE_MAX_NUM         (32)     /* Maximum number of screen modes for a specific group. */
#define SCREEN_MODE_LAST_ENTRY      (SCC_VID_SCREEN_MODE_T) SCREEN_MODE_MAX_NUM

#define INVALID_SCREEN_MODE         SCREEN_MODE_MAX_NUM
#define INVALID_INPUT_SRC           SCREEN_MODE_SRC_NUM
#define INVALID_ASP_RATIO           SCREEN_MODE_ASP_NUM

/*
   Zoom & Pan.
*/
#define ZOOM_STEP_NUM               (1)
#define ZOOM_IN_STEP_SIZE           7 / 10   /* 2 times.      */
#define ZOOM_OUT_STEP_SIZE          10 / 7   /* 1/2 times.    */
#define ZOOM_SIZE_MIN               (4)      /* in percent/10 */

#define PAN_STEP_SIZE               (10)     /* in percent/10 */

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/* Screen mode table. */
static const SCC_VID_SCREEN_MODE_T    ae_screen_mode [SCREEN_MODE_SRC_NUM * SCREEN_MODE_ASP_NUM][SCREEN_MODE_MAX_NUM] =
                                      {
                                          /* VGA (4:3) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,           /* Normal */
                                              SCC_VID_SCREEN_MODE_LETTERBOX,        /* Stretch */

                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* VGA (16:9) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,           /* Normal */
                                              SCC_VID_SCREEN_MODE_LETTERBOX,        /* Stretch */

                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* VGA (all) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,           /* Normal */
                                              SCC_VID_SCREEN_MODE_LETTERBOX,        /* Stretch */

                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* VGA (1080p 120hz) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,           /* Normal */
                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* Non-VGA (4:3) */
                                          {        
                                              SCC_VID_SCREEN_MODE_NORMAL,            /* Normal */
                                              SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM,   /* Panorama */
                                              SCC_VID_SCREEN_MODE_CUSTOM_DEF_1,      /* Wide */
                                              SCC_VID_SCREEN_MODE_CUSTOM_DEF_0,      /* Zoom */

                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* Non-VGA (16:9) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,            /* Normal */
                                              SCC_VID_SCREEN_MODE_LETTERBOX,         /* Stretch */
                                              SCC_VID_SCREEN_MODE_CUSTOM_DEF_1,      /* Wide */
                                              SCC_VID_SCREEN_MODE_CUSTOM_DEF_0,      /* Zoom */

                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* Non-VGA (all) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,            /* Normal */
                                              SCC_VID_SCREEN_MODE_LETTERBOX,         /* Stretch */
                                              SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM,   /* Panorama */
                                              SCC_VID_SCREEN_MODE_CUSTOM_DEF_1,      /* Wide */
                                              SCC_VID_SCREEN_MODE_CUSTOM_DEF_0,      /* Zoom */
                                                     
                                              SCREEN_MODE_LAST_ENTRY
                                          },

                                          /* Non-VGA (1080p 120hz) */
                                          {
                                              SCC_VID_SCREEN_MODE_NORMAL,           /* Normal */
                                              SCREEN_MODE_LAST_ENTRY
                                          }
                                      };

/*-----------------------------------------------------------------------------
 * screen mode methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _sml_get_src_idx
 *
 * Description
 *      This function gets input source index for focused window.
 *
 * Input arguments
 *      -
 *
 * Output arguments
 *      pui1_src_idx             Source index.
 *
 * Returns
 *      -
 *---------------------------------------------------------------------------*/
VOID _sml_get_src_idx (UINT8*    pui1_src_idx)
{
    INT32              i4_res;
    CHAR               s_disp_name[SYS_NAME_LEN+1];
    ISL_REC_T          t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
    
    *pui1_src_idx = INVALID_INPUT_SRC;

    do
    {
        if( a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
        {
            *pui1_src_idx = SCREEN_MODE_SRC_NON_VGA;
            break;
        }

        /* Get current ISL record. */
        i4_res = a_cfg_av_get_disp_name (s_disp_name, sizeof(s_disp_name));

        if (i4_res != TVR_OK)
        {
            break;
        }

        i4_res = a_tv_get_isl_rec_by_snk_name (s_disp_name, & t_isl_rec);
        if (i4_res != TVR_OK)
        {
            break;
        }

        i4_res = a_cfg_av_get_timing (s_disp_name, &t_timing);
        if (i4_res != TVR_OK)
        {
            break;
        }

        /* Get input source index. */
        switch (t_isl_rec.t_avc_info.e_video_type)
        {
            case DEV_AVC_VGA: /* VGA */
            {
                *pui1_src_idx = SCREEN_MODE_SRC_VGA;
            }
            break;
            case DEV_AVC_DVI:  /* dvi */
            case DEV_AVC_HDMI: /* hdmi */
            if(SCC_VID_HDMI_DVI_MODE_DVI == a_cfg_custom_get_hdmi_dvi_signal())
            {
                *pui1_src_idx = SCREEN_MODE_SRC_VGA;/*dvi*/
            }
            else
            {
                *pui1_src_idx = SCREEN_MODE_SRC_NON_VGA;/*hdmi*/
            }
            break;
            default: /* Non-VGA */
            {
#if 0
                VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};

                i4_res = a_cfg_av_get_timing (s_disp_name, &t_timing);
                if (APP_CFGR_OK == i4_res && VSH_SRC_TIMING_GRAPHIC == t_timing.e_timing_type)
                {
                    *pui1_src_idx = SCREEN_MODE_SRC_VGA;
                }
                else
#endif
                {
                    *pui1_src_idx = SCREEN_MODE_SRC_NON_VGA;
                }
            }
            break;
        }

    } while (0);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _sml_get_asp_idx
 *
 * Description
 *      This function gets aspect ratio index for a given video source.
 *
 * Input arguments
 *      e_src_asp_ratio          Aspect ratio of video source.
 *
 * Output arguments
 *      pui1_asp_idx             Aspect index.
 *
 * Returns
 *      -
 *---------------------------------------------------------------------------*/
VOID _sml_get_asp_idx (VSH_SRC_ASPECT_RATIO_T    e_src_asp_ratio,
                       UINT8*                    pui1_asp_idx)
{
    *pui1_asp_idx = INVALID_ASP_RATIO;
    BOOL    b_enable = TRUE;

    a_cfg_custom_get_wide_mode_enable_change(&b_enable);

    if (!b_enable)
    {
        DBG_LOG_PRINT((" need check later SCREEN_MODE_ASP_1080P_120HZ %s,%d\r\n",__FUNCTION__,__LINE__));
//#ifdef NEVER
        *pui1_asp_idx = SCREEN_MODE_ASP_1080P_120HZ;
        return;
//#endif /* NEVER */
    }

    switch (e_src_asp_ratio)
    {
        case VSH_SRC_ASPECT_RATIO_4_3:
        {
            *pui1_asp_idx = SCREEN_MODE_ASP_4_3;
        }
        break;

        case VSH_SRC_ASPECT_RATIO_16_9:
        case VSH_SRC_ASPECT_RATIO_2_21_1:
        {
            *pui1_asp_idx = SCREEN_MODE_ASP_16_9;

            if (a_cfg_custom_chk_freqence_120hz() == TRUE)
            {
                *pui1_asp_idx = SCREEN_MODE_ASP_1080P_120HZ;
            }
        }
        break;

        case VSH_SRC_ASPECT_RATIO_ALL:
        {
            *pui1_asp_idx = SCREEN_MODE_ASP_ALL;
        }
        break;

        default:
            break;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _sml_is_valid_screen_mode
 *
 * Description
 *      This function checks if the screen mode is valid for current TV mode.
 *
 * Input arguments
 *      e_screen_mode            Screen mode.
 *
 * Output arguments
 *      -
 *
 * Returns
 *      TRUE                     Valid.
 *      FALSE                    Invalid.
 *---------------------------------------------------------------------------*/
BOOL _sml_is_valid_screen_mode (SCC_VID_SCREEN_MODE_T    e_screen_mode)
{
    INT32                       i4_ret;
    BOOL                        b_valid;
    TV_MODE_T                   e_tv_mode;
    CHAR                        s_disp_name [SYS_NAME_LEN+1];
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};

    b_valid = TRUE;

    /* Get current TV mode. */
    i4_ret = a_tv_get_mode (& e_tv_mode);

    if (i4_ret == TVR_OK)
    {
        if (e_tv_mode != TV_MODE_TYPE_NORMAL)
        {
            /* Non-linear-zoom and dot-by-dot are disabled in PIP/POP mode. */
            if ((e_screen_mode == SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM) ||
                (e_screen_mode == SCC_VID_SCREEN_MODE_DOT_BY_DOT))
            {
                b_valid = FALSE;
            }
        }
        else /* Normal TV mode. */
        {
            if (e_screen_mode == SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM) /* Panoramic */
            {
                b_valid = FALSE;

                do
                {
                    i4_ret = a_cfg_av_get_disp_name (s_disp_name, sizeof(s_disp_name));

                    if (i4_ret != APP_CFGR_OK)
                    {
                        break;
                    }

                    i4_ret = a_cfg_av_get_timing (s_disp_name, & t_timing);

                    if (i4_ret != APP_CFGR_OK)
                    {
                        break;
                    }

                    /* Must enable Panoramic for all sd content for streaming video */
                    {
                        b_valid = TRUE;
                    }

                } while (0);
            }
            else
            {
                b_valid = TRUE;
            }
        }


        /* Disable pan-scan and dot-by-dot if no zoom operation is allowed. */
        if ((e_screen_mode == SCC_VID_SCREEN_MODE_PAN_SCAN) ||
            (e_screen_mode == SCC_VID_SCREEN_MODE_DOT_BY_DOT))
        {
#ifdef APP_DISABLE_ZOOM
            b_valid = FALSE;
#elif defined(APP_SML_ENABLE_ZOOM_FOR_HD)
            b_valid = TRUE;
#else
            HANDLE_T                        h_svctx = NULL_HANDLE;
            VSH_REGION_CAPABILITY_INFO_T    t_info;
            SIZE_T                          z_size;
            CHAR                            s_disp_name[SYS_NAME_LEN+1];

            b_valid = FALSE;

            /* Only check display mode on Main window */
            i4_ret = a_cfg_av_get_disp_name (s_disp_name, sizeof(s_disp_name));
            if (i4_ret == APP_CFGR_OK &&
                c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) != 0 &&
                e_tv_mode == TV_MODE_TYPE_PIP)
            {
                return b_valid;
            }

            if (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0)
            {
                i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_svctx);
            }
            else
            {
                i4_ret = c_svctx_open(SVCTX_NAME_SUB, &h_svctx);
            }

            if (i4_ret != SVCTXR_OK)
            {
                return b_valid;
            }

            /* Check display mode*/
            z_size = sizeof(VSH_REGION_CAPABILITY_INFO_T);
            t_info.e_get_type = SM_VSH_GET_TYPE_DISP_REGION;
            i4_ret = c_svctx_get_stream_attr(h_svctx,
                                             ST_VIDEO,
                                             SM_VSH_GET_TYPE_REGION_CAPABILITY,
                                             &t_info,
                                             &z_size);
            if (i4_ret != SVCTXR_OK)
            {
                c_svctx_close(h_svctx);
                return b_valid;
            }

            if ((t_info.b_is_enable == TRUE) && (e_screen_mode == SCC_VID_SCREEN_MODE_DOT_BY_DOT))
            {
                b_valid = TRUE;
            }
            else if (e_screen_mode == SCC_VID_SCREEN_MODE_PAN_SCAN)
            {
                VSH_SRC_ASPECT_RATIO_T e_src_asp_ratio;

                i4_ret = a_cfg_av_get_timing (s_disp_name, & t_timing);
                if (i4_ret == APP_CFGR_OK)
                {
                    e_src_asp_ratio = a_sml_get_src_asp_ratio(&t_timing);
                    if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_16_9)
                    {
                        if (t_info.ui4_width_min <= 7500 && t_info.ui4_height_min <= 7500)
                        {
                            b_valid = TRUE;
                        }
                    }
                    else if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3)
                    {
                        if (t_info.ui4_width_min <= 10000 && t_info.ui4_height_min <= 7500)
                        {
                            b_valid = TRUE;
                        }
                    }
                }
            }
            c_svctx_close(h_svctx);
#endif /* APP_DISABLE_ZOOM */
        }
    }

    return b_valid;
}


/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_get_src_asp_ratio
 *
 * Description
 *      This API gets the aspect ratio for video source. Currently, either
 *      VSH_SRC_ASPECT_RATIO_4_3 or VSH_SRC_ASPECT_RATIO_16_9 will be returned.
 *
 * Input arguments
 *      pt_src_res             Video source resolution.
 *
 * Output arguments
 *
 * Returns
 *      Aspect ratio for video source.
 *---------------------------------------------------------------------------*/
VSH_SRC_ASPECT_RATIO_T a_sml_get_src_asp_ratio (VSH_SRC_RESOLUTION_INFO_T*     pt_src_res)
{
    UINT32                  ui4_asp_ratio;
    VSH_SRC_ASPECT_RATIO_T  e_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;
    INT16                   i2_3d_to_2d_mode = 0;
    INT16                   i2_mode_idx = 0;
    UINT32                  ui4_width;
    UINT32                  ui4_height;

    if ((pt_src_res->ui4_width != 0) && (pt_src_res->ui4_height != 0))
    {
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     &i2_mode_idx);
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                     &i2_3d_to_2d_mode);
        if (i2_3d_to_2d_mode == APP_CFG_3D_TO_2D_LEFT && i2_mode_idx == APP_CFG_3D_MODE_SBS)
        {
            /* in 2D SBS, video width get from VSH_SRC_RESOLUTION_INFO_T need x 2 */
            ui4_width = pt_src_res->ui4_width * 2;
            ui4_height = pt_src_res->ui4_height;
        }
        else if (i2_3d_to_2d_mode == APP_CFG_3D_TO_2D_LEFT && i2_mode_idx == APP_CFG_3D_MODE_TAB)
        {
            /* in 2D SBS, video height get from VSH_SRC_RESOLUTION_INFO_T need x 2 */
            ui4_width = pt_src_res->ui4_width;
            ui4_height = pt_src_res->ui4_height * 2;
        }
        else
        {
            ui4_width = pt_src_res->ui4_width;
            ui4_height = pt_src_res->ui4_height;
        }

        /* Calcuate aspect ratio according to the ratio between height and width. */
        ui4_asp_ratio = ui4_width * 100 / ui4_height;

        if (ui4_asp_ratio <= 133) /* Less than 4:3 */
        {
            e_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
        }
        else if (ui4_asp_ratio >= 178) /* Greater than 16:9 */
        {
            e_asp_ratio = VSH_SRC_ASPECT_RATIO_16_9;
        }
        else /* In the medium. */
        {
            e_asp_ratio = (133 * 100 / ui4_asp_ratio) > (ui4_asp_ratio * 100 / 178) ?
                          VSH_SRC_ASPECT_RATIO_4_3 : VSH_SRC_ASPECT_RATIO_16_9;
        }
    }

    return  e_asp_ratio;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_get_num_rec
 *
 * Description
 *      This API gets the number of records for a specifc video resolution.
 *
 * Input arguments
 *      e_src_asp_ratio       Aspect ratio of source video.
 *
 * Output arguments
 *      pui1_num_recs         The number of screen modes.
 *
 * Returns
 *      SMR_OK                Successful.
 *---------------------------------------------------------------------------*/
INT32 a_sml_get_num_rec (VSH_SRC_ASPECT_RATIO_T    e_src_asp_ratio,
                         UINT8*                    pui1_num_recs)
{
    UINT8                        ui1_i;
    UINT8                        ui1_num_recs;
    UINT8                        ui1_type;
    UINT8                        ui1_src_idx;
    UINT8                        ui1_asp_idx;
    SCC_VID_SCREEN_MODE_T        e_screen_mode;

    *pui1_num_recs = 0;

    do
    {
        /* Get input source index. */
        _sml_get_src_idx (& ui1_src_idx);

        if (ui1_src_idx == INVALID_INPUT_SRC)
        {
            break;
        }

        /* Get aspect ratio index. */
        _sml_get_asp_idx (e_src_asp_ratio, & ui1_asp_idx);

        if (ui1_asp_idx == INVALID_ASP_RATIO)
        {
            break;
        }

        /* Count the number of records. */
        ui1_num_recs = 0;

        for (ui1_i = 0; ui1_i < SCREEN_MODE_MAX_NUM; ui1_i ++)
        {
            ui1_type = (UINT8)(ui1_src_idx * SCREEN_MODE_ASP_NUM + ui1_asp_idx);

            if (ui1_type < (UINT8)(SCREEN_MODE_SRC_NUM * SCREEN_MODE_ASP_NUM)) /* validate index */
            {
                e_screen_mode = ae_screen_mode [ui1_type][ui1_i];

                if (e_screen_mode == SCREEN_MODE_LAST_ENTRY) /* Last entry. */
                {
                    break;
                }

                /* Check if the screen mode is valid. */
                if (_sml_is_valid_screen_mode (e_screen_mode))
                {
                    /* Accumulate records. */
                    ui1_num_recs ++;
                }
            }
        }

        /* Set the number of records. */
        *pui1_num_recs = ui1_num_recs;

    } while (0);

    return SMLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_iterate_rec
 *
 * Description
 *      This API iterates the record for a specifc video resolution.
 *
 * Input arguments
 *      e_src_asp_ratio       Aspect ratio of source video.
 *      e_iter_dir            Iteration mode.
 *      pe_screen_mode        Current screen mode.

 * Output arguments
 *      pe_screen_mode        Screen mode after iteration.
 *
 * Returns
 *      SMR_OK                Successful.
 *      SMR_INV_ARG           Invalid arguments.
 *      SMR_NOT_SUPPORTED     Iteration to current screen mode is not available.
 *---------------------------------------------------------------------------*/
INT32 a_sml_iterate_rec (VSH_SRC_ASPECT_RATIO_T    e_src_asp_ratio,
                         SML_ITERATE_T             e_iter_dir,
                         SCC_VID_SCREEN_MODE_T*    pe_screen_mode)
{
    INT32                           i4_res;
    UINT8                           ui1_i;
    UINT8                           ui1_num_recs;
    UINT8                           ui1_crnt_idx;
    UINT8                           ui1_src_idx;
    UINT8                           ui1_asp_idx;
    UINT8                           ui1_type;
    BOOL                            b_valid;
    SCC_VID_SCREEN_MODE_T           e_screen_mode;
    const SCC_VID_SCREEN_MODE_T*    pe_screen_modes;

    /* Get input source index. */
    _sml_get_src_idx (& ui1_src_idx);

    if (ui1_src_idx == INVALID_INPUT_SRC)
    {
        return SMLR_FAIL;
    }

    /* Get aspect ratio index. */
    _sml_get_asp_idx (e_src_asp_ratio, & ui1_asp_idx);

    if (ui1_asp_idx == INVALID_ASP_RATIO)
    {
        return SMLR_FAIL;
    }

    /* Validate type index */
    ui1_type = (UINT8)(ui1_src_idx * SCREEN_MODE_ASP_NUM + ui1_asp_idx);

    if (ui1_type >= (UINT8)(SCREEN_MODE_SRC_NUM * SCREEN_MODE_ASP_NUM))
    {
        return SMLR_FAIL; /* Invalid index */
    }

    /* Get screen mode array. */
    pe_screen_modes = ae_screen_mode [ui1_type];

    /* Count the number of records. */
    ui1_num_recs = 0;

    for (ui1_i = 0; ui1_i < SCREEN_MODE_MAX_NUM; ui1_i ++)
    {
        e_screen_mode = ae_screen_mode [ui1_type][ui1_i];

        if (e_screen_mode == SCREEN_MODE_LAST_ENTRY) /* Last entry. */
        {
            break;
        }

        /* Accumulate records. */
        ui1_num_recs ++;
    }

    /* Check if current screen mode is valid. */
    b_valid      = FALSE;
    ui1_crnt_idx = 0;

    for (ui1_i = 0; ui1_i < ui1_num_recs; ui1_i ++)
    {
        if (*pe_screen_mode == pe_screen_modes [ui1_i])
        {
            ui1_crnt_idx = ui1_i;
            b_valid      = TRUE;

            break;
        }
    }

    i4_res = SMLR_OK;

    if (b_valid) /* Current screen mode is valid. */
    {
        /* Get screen mode by iteration mode. */
        switch (e_iter_dir)
        {
            case SML_ITERATE_DIR_FIRST:
            {
                *pe_screen_mode = pe_screen_modes[0];

                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get next available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_NEXT, pe_screen_mode);
                }
            }
            break;

            case SML_ITERATE_DIR_LAST:
            {
                *pe_screen_mode = pe_screen_modes[ui1_num_recs-1];

                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get previous available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_PREV, pe_screen_mode);
                }
            }
            break;

            case SML_ITERATE_DIR_THIS:
            {
                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get next available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_FIRST, pe_screen_mode);
                }
            }
            break;

            case SML_ITERATE_DIR_NEXT:
            {
                *pe_screen_mode = (ui1_crnt_idx == (UINT8)(ui1_num_recs-1)) ? pe_screen_modes[0] : pe_screen_modes[ui1_crnt_idx+1];

                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get next available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_NEXT, pe_screen_mode);
                }
            }
            break;

            case SML_ITERATE_DIR_PREV:
            {
                *pe_screen_mode = (ui1_crnt_idx == 0) ? pe_screen_modes[ui1_num_recs-1] : pe_screen_modes[ui1_crnt_idx-1];

                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get previous available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_PREV, pe_screen_mode);
                }
            }
            break;

            default: /* Unknown iteration type. */
            {
                i4_res = SMLR_INV_ARG;
            }
            break;
        }
    }
    else /* Invalid screen mode. */
    {
        /* Get screen mode by iteration mode. */
        switch (e_iter_dir)
        {
            case SML_ITERATE_DIR_FIRST: /* Iterate first record is ok. */
            case SML_ITERATE_DIR_THIS:  /* Iterate this is to iterate first record
                                           if it is a invalid screen mode */
            {
                *pe_screen_mode = pe_screen_modes[0];

                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get next available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_NEXT, pe_screen_mode);
                }
            }
            break;

            case SML_ITERATE_DIR_LAST: /* Iterate last record is ok. */
            {
                *pe_screen_mode = pe_screen_modes[ui1_num_recs-1];

                /* Check if screen mode is valid. */
                if (! _sml_is_valid_screen_mode (*pe_screen_mode))
                {
                    /* Get previous available record. */
                    return a_sml_iterate_rec (e_src_asp_ratio, SML_ITERATE_DIR_PREV, pe_screen_mode);
                }
            }
            break;

            default: /* Other iterations will fail. */
            {
                i4_res = SMLR_NOT_SUPPORTED;
            }
            break;
        }
    }

    return i4_res;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_get_disp_name
 *
 * Description
 *      This API gets the name for display given the aspect ratio of source video
 *      and the screen mode.
 *
 * Input arguments
 *      e_src_asp_ratio       Aspect ratio of source video.
 *      e_screen_mode         Screen mode.
 *
 * Output arguments
 *      pui2_text             Text string to be displayed.
 *
 * Returns
 *      SMR_OK                Successful.
 *      SMR_INV_ARG           Invalid arguments.
 *---------------------------------------------------------------------------*/
UTF16_T* a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_T    e_src_asp_ratio,
                              SCC_VID_SCREEN_MODE_T     e_screen_mode)
{
    INT32              i4_res;
    ISO_639_LANG_T     s639_lang;
    UINT8              ui1_lang_id;
    UINT8              ui1_idx;

    ui1_lang_id = (UINT8)MLM_SML_LANG_ENG;

    /* Get current gui language. */
    i4_res = a_cfg_get_gui_lang (s639_lang);

    if (i4_res == APP_CFGR_OK)
    {
#ifdef APP_MLM_S639_TO_LANGIDX_SUPPORT
        ui1_lang_id = (UINT8)mlm_sml_s639_to_langidx (s639_lang);
#else
        if (c_strcmp (s639_lang, s639_app_cfg_lang_eng) == 0) /* English */
        {
            ui1_lang_id = 0;
        }
        else if ((c_strcmp (s639_lang, s639_app_cfg_lang_esl) == 0) || /* Spanish */
                 (c_strcmp (s639_lang, s639_app_cfg_lang_spa) == 0))
        {
            ui1_lang_id = 1;
        }
        else if ((c_strcmp (s639_lang, s639_app_cfg_lang_fra) == 0) || /* French */
                 (c_strcmp (s639_lang, s639_app_cfg_lang_fre) == 0))
        {
            ui1_lang_id = 2;
        }
#endif /* APP_MLM_S639_TO_LANGIDX_SUPPORT */
    }

    /* Get display name. */
    switch (e_screen_mode)
    {
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:    /* Zoom */
            ui1_idx = (UINT8)MLM_SML_KEY_MSG_ZOOM;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:    /* Wide */
            ui1_idx = (UINT8)MLM_SML_KEY_MSG_WIDE;
            break;

        case SCC_VID_SCREEN_MODE_NORMAL:          /* Normal */
            ui1_idx = (UINT8)MLM_SML_KEY_MSG_NORMAL;
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:       /* Stretch */
            ui1_idx = (UINT8)MLM_SML_KEY_MSG_STRETCH;
            break;

        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM: /* Panoramic */
            ui1_idx = (UINT8)MLM_SML_KEY_MSG_PANORAMA;
            break;

        default:                                  /* unknown screen mode? */
            ui1_idx = (UINT8)INVALID_SCREEN_MODE;
            break;
    }

    return (ui1_idx == (UINT8)INVALID_SCREEN_MODE) ? NULL : MLM_SML_TEXT (ui1_lang_id, ui1_idx);
}

/*-----------------------------------------------------------------------------
 * zoom & pan methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _sml_adjust_vertical_pos
 *
 * Description
 *      This function gets the region after vertical position adjustment. The adjust
 *      level could be:
 *
 *       - a minus (UP),
 *       - a plus (DOWN), or
 *       - 0 (no adjustment).
 *
 * Input arguments
 *      i1_level              The level to be adjusted
 *      pt_src_region         The source region to be adjusted.
 *
 * Output arguments
 *      pt_src_region         The source region after adjustment.
 *
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _sml_adjust_vertical_pos (INT8                  i1_level,
                                      VSH_REGION_INFO_T*    pt_src_region)
{
    if ((pt_src_region->ui4_y == 0) && (pt_src_region->ui4_height == VSH_REGION_MAX_HEIGHT))
    {
        /* Do nothing to source region. */
        ;
    }
    else
    {
        if (i1_level < 0) /* Level < 0 => Adjust UP */
        {
            /* Convert level to a positive value. */
            i1_level *= (-1);

            if ((UINT32)(i1_level * PAN_STEP_SIZE) > pt_src_region->ui4_y) /* too small */
            {
                pt_src_region->ui4_y = 0;
            }
            else
            {
                pt_src_region->ui4_y -= i1_level * PAN_STEP_SIZE;
            }
        }
        else /* Level >= 0 => Adjust DOWN */
        {
            if (pt_src_region->ui4_y + pt_src_region->ui4_height + i1_level * PAN_STEP_SIZE > VSH_REGION_MAX_HEIGHT) /* too large */
            {
                pt_src_region->ui4_y = VSH_REGION_MAX_HEIGHT - pt_src_region->ui4_height;
            }
            else
            {
                pt_src_region->ui4_y += i1_level * PAN_STEP_SIZE;
            }
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _sml_adjust_horizontal_pos
 *
 * Description
 *      This function gets the region after horizontal position adjustment. The adjust
 *      level could be:
 *
 *       - a minus (LEFT),
 *       - a plus (RIGHT), or
 *       - 0 (no adjustment).
 *
 * Input arguments
 *      i1_level              The level to be adjusted
 *      pt_src_region         The source region to be adjusted.
 *
 * Output arguments
 *      pt_src_region         The source region after adjustment.
 *
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _sml_adjust_horizontal_pos (INT8                  i1_level,
                                        VSH_REGION_INFO_T*    pt_src_region)
{
    if ((pt_src_region->ui4_x == 0) && (pt_src_region->ui4_width == VSH_REGION_MAX_WIDTH))
    {
        /* Do nothing to source region. */
        ;
    }
    else
    {
        if (i1_level < 0) /* Level < 0 => Adjust LEFT */
        {
            /* Convert level to a positive value. */
            i1_level *= (-1);

            if ((UINT32)(i1_level * PAN_STEP_SIZE) > pt_src_region->ui4_x) /* too small */
            {
                pt_src_region->ui4_x = 0;
            }
            else
            {
                pt_src_region->ui4_x -= i1_level * PAN_STEP_SIZE;
            }
        }
        else /* Level >= 0 => Adjust RIGHT */
        {
            if (pt_src_region->ui4_x + pt_src_region->ui4_width + i1_level * PAN_STEP_SIZE > VSH_REGION_MAX_WIDTH) /* too large */
            {
                pt_src_region->ui4_x = VSH_REGION_MAX_WIDTH - pt_src_region->ui4_width;
            }
            else
            {
                pt_src_region->ui4_x += i1_level * PAN_STEP_SIZE;
            }
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _sml_finetune_region
 *
 * Description
 *      This function fine-tune regions for adjustment. The fine-tuning ensures
 *      the regions are valid.
 *
 * Input arguments
 *      pt_wnd_region         Window region (boundary region).
 *      pt_vid_region         Video region to be fine-tuned.
 *      pt_dsp_region         Display region to be fine-tuned.
 *
 * Output arguments
 *      pt_vid_region         Video region after fine-tuning.
 *      pt_dsp_region         Display region after fine-tuning.
 *
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _sml_finetune_region (VSH_REGION_INFO_T*    pt_wnd_region,
                                  VSH_REGION_INFO_T*    pt_vid_region,
                                  VSH_REGION_INFO_T*    pt_dsp_region)
{
    /* Fine-tune width. */
    if (pt_vid_region->ui4_width < ZOOM_SIZE_MIN)
    {
        pt_vid_region->ui4_width = ZOOM_SIZE_MIN;
        pt_vid_region->ui4_x     = (VSH_REGION_MAX_WIDTH - ZOOM_SIZE_MIN) / 2;
    }
    else if (pt_vid_region->ui4_width > VSH_REGION_MAX_WIDTH)
    {
        pt_vid_region->ui4_width = VSH_REGION_MAX_WIDTH;
        pt_vid_region->ui4_x     = 0;
    }

    if (pt_dsp_region->ui4_width < ZOOM_SIZE_MIN)
    {
        pt_dsp_region->ui4_width  = ZOOM_SIZE_MIN;
        pt_dsp_region->ui4_x      = (VSH_REGION_MAX_WIDTH - ZOOM_SIZE_MIN) / 2;
    }
    else if (pt_dsp_region->ui4_width > pt_wnd_region->ui4_width)
    {
        pt_dsp_region->ui4_width = pt_wnd_region->ui4_width;
        pt_dsp_region->ui4_x     = pt_wnd_region->ui4_x;
    }

    /* Fine-tune height. */
    if (pt_vid_region->ui4_height < ZOOM_SIZE_MIN)
    {
        pt_vid_region->ui4_height = ZOOM_SIZE_MIN;
        pt_vid_region->ui4_y      = (VSH_REGION_MAX_HEIGHT - ZOOM_SIZE_MIN) / 2;
    }
    else if (pt_vid_region->ui4_height > VSH_REGION_MAX_HEIGHT)
    {
        pt_vid_region->ui4_height = VSH_REGION_MAX_HEIGHT;
        pt_vid_region->ui4_y      = 0;
    }

    if (pt_dsp_region->ui4_height < ZOOM_SIZE_MIN)
    {
        pt_dsp_region->ui4_height = ZOOM_SIZE_MIN;
        pt_dsp_region->ui4_y      = (VSH_REGION_MAX_HEIGHT - ZOOM_SIZE_MIN) / 2;
    }
    else if (pt_dsp_region->ui4_height > pt_wnd_region->ui4_height)
    {
        pt_dsp_region->ui4_height = pt_wnd_region->ui4_height;
        pt_dsp_region->ui4_y      = pt_wnd_region->ui4_y;
    }

    /* Fine-tune X-axle. */
    if (pt_vid_region->ui4_x + pt_vid_region->ui4_width > VSH_REGION_MAX_WIDTH)
    {
        pt_vid_region->ui4_x = VSH_REGION_MAX_WIDTH - pt_vid_region->ui4_width;
    }

    if (pt_dsp_region->ui4_x + pt_dsp_region->ui4_width > VSH_REGION_MAX_WIDTH)
    {
        pt_dsp_region->ui4_x = VSH_REGION_MAX_WIDTH - pt_dsp_region->ui4_width;
    }

    /* Fine-tune Y-axle. */
    if (pt_vid_region->ui4_y + pt_vid_region->ui4_height > VSH_REGION_MAX_HEIGHT)
    {
        pt_vid_region->ui4_y = VSH_REGION_MAX_HEIGHT - pt_vid_region->ui4_height;
    }

    if (pt_dsp_region->ui4_y + pt_dsp_region->ui4_height > VSH_REGION_MAX_HEIGHT)
    {
        pt_dsp_region->ui4_y = VSH_REGION_MAX_HEIGHT - pt_dsp_region->ui4_height;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _sml_adjust_vertical_size
 *
 * Description
 *      This function gets the region after vertical size adjustment. The adjust
 *      level could be:
 *
 *       - a minus (ZOOM_OUT),
 *       - a plus (ZOOM_IN), or
 *       - 0 (no adjustment).
 *
 * Input arguments
 *      i1_level              The level to be adjusted
 *      pt_wnd_region         Window region (boundary region).
 *      pt_vid_region         Video region to be adjusted.
 *      pt_dsp_region         Display region to be adjusted.
 *
 * Output arguments
 *      pt_vid_region         Video region after adjustment.
 *      pt_dsp_region         Display region after adjustment.
 *
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _sml_adjust_vertical_size (INT8                  i1_level,
                                       VSH_REGION_INFO_T*    pt_wnd_region,
                                       VSH_REGION_INFO_T*    pt_vid_region,
                                       VSH_REGION_INFO_T*    pt_dsp_region)
{
    INT8      i1_i;
    UINT32    ui4_delta;
    UINT32    ui4_temp;

    if (i1_level == 0) /* Original size. */
    {
        /* Do nothing. */
    }
    else if (i1_level < 0) /* Level < 0 => Vertical ZOOM_OUT */
    {
        /* Convert level to a positive value. */
        i1_level *= (-1);

        for (i1_i = 0; i1_i < i1_level; i1_i ++)
        {
            if (pt_vid_region->ui4_height == VSH_REGION_MAX_HEIGHT)
            {
                /* Zoom in display region. */
                ui4_temp = pt_dsp_region->ui4_height;
                pt_dsp_region->ui4_height = pt_dsp_region->ui4_height * ZOOM_IN_STEP_SIZE;
                ui4_delta = (ui4_temp - pt_dsp_region->ui4_height) / 2;
                pt_dsp_region->ui4_y += ui4_delta;
            }
            else
            {
                /* Zoom out video region. */
                ui4_temp = pt_vid_region->ui4_height;
                pt_vid_region->ui4_height = pt_vid_region->ui4_height * ZOOM_OUT_STEP_SIZE;
                ui4_delta = (pt_vid_region->ui4_height - ui4_temp) / 2;
                pt_vid_region->ui4_y = (pt_vid_region->ui4_y >= ui4_delta) ?
                                       (pt_vid_region->ui4_y - ui4_delta) : 0;
            }

            /* Fine-tune regions. */
            _sml_finetune_region (pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
    }
    else /* Level > 0 => Vertical ZOOM_IN */
    {
        for (i1_i = 0; i1_i < i1_level; i1_i ++)
        {
            if (pt_dsp_region->ui4_height == pt_wnd_region->ui4_height)
            {
                /* Zoom in video region. */
                ui4_temp = pt_vid_region->ui4_height;
                pt_vid_region->ui4_height = pt_vid_region->ui4_height * ZOOM_IN_STEP_SIZE + 1;
                ui4_delta = (ui4_temp - pt_vid_region->ui4_height) / 2;
                pt_vid_region->ui4_y += ui4_delta;
            }
            else
            {
                /* Zoom out display region. */
                ui4_temp = pt_dsp_region->ui4_height;
                pt_dsp_region->ui4_height = pt_dsp_region->ui4_height * ZOOM_OUT_STEP_SIZE + 1;
                ui4_delta = (pt_dsp_region->ui4_height - ui4_temp) / 2;
                pt_dsp_region->ui4_y = (pt_dsp_region->ui4_y >= ui4_delta) ?
                                       (pt_dsp_region->ui4_y - ui4_delta) : 0;
            }

            /* Fine-tune regions. */
            _sml_finetune_region (pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _sml_adjust_horizontal_size
 *
 * Description
 *      This function gets the region after horizontal size adjustment. The adjust
 *      level could be:
 *
 *       - a minus (ZOOM_OUT),
 *       - a plus (ZOOM_IN), or
 *       - 0 (no adjustment).
 *
 * Input arguments
 *      i1_level              The level to be adjusted
 *      pt_wnd_region         Window region (boundary region).
 *      pt_vid_region         Video region to be adjusted.
 *      pt_dsp_region         Display region to be adjusted.
 *
 * Output arguments
 *      pt_vid_region         Video region after adjustment.
 *      pt_dsp_region         Display region after adjustment.
 *
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _sml_adjust_horizontal_size (INT8                  i1_level,
                                         VSH_REGION_INFO_T*    pt_wnd_region,
                                         VSH_REGION_INFO_T*    pt_vid_region,
                                         VSH_REGION_INFO_T*    pt_dsp_region)
{
    INT8      i1_i;
    UINT32    ui4_delta;
    UINT32    ui4_temp;

    if (i1_level == 0) /* Original size. */
    {
        /* Do nothing. */
    }
    else if (i1_level < 0) /* Level < 0 => Vertical ZOOM_OUT */
    {
        /* Convert level to a positive value. */
        i1_level *= (-1);

        for (i1_i = 0; i1_i < i1_level; i1_i ++)
        {
            if (pt_vid_region->ui4_width == VSH_REGION_MAX_WIDTH)
            {
                /* Zoom in display region. */
                ui4_temp = pt_dsp_region->ui4_width;
                pt_dsp_region->ui4_width = pt_dsp_region->ui4_width * ZOOM_IN_STEP_SIZE;
                ui4_delta = (ui4_temp - pt_dsp_region->ui4_width) / 2;
                pt_dsp_region->ui4_x += ui4_delta;
            }
            else
            {
                /* Zoom out video region. */
                ui4_temp = pt_vid_region->ui4_width;
                pt_vid_region->ui4_width = pt_vid_region->ui4_width * ZOOM_OUT_STEP_SIZE;
                ui4_delta = (pt_vid_region->ui4_width - ui4_temp) / 2;
                pt_vid_region->ui4_x = (pt_vid_region->ui4_x >= ui4_delta) ?
                                       (pt_vid_region->ui4_x - ui4_delta) : 0;
            }

            /* Fine-tune regions. */
            _sml_finetune_region (pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
    }
    else /* Level > 0 => Vertical ZOOM_IN */
    {
        for (i1_i = 0; i1_i < i1_level; i1_i ++)
        {
            if (pt_dsp_region->ui4_width == VSH_REGION_MAX_WIDTH)
            {
                /* Zoom in source region. */
                ui4_temp = pt_vid_region->ui4_width;
                pt_vid_region->ui4_width = pt_vid_region->ui4_width * ZOOM_IN_STEP_SIZE + 1;
                ui4_delta = (ui4_temp - pt_vid_region->ui4_width) / 2;
                pt_vid_region->ui4_x += ui4_delta;
            }
            else
            {
                /* Zoom out display region. */
                ui4_temp = pt_dsp_region->ui4_width;
                pt_dsp_region->ui4_width = pt_dsp_region->ui4_width * ZOOM_OUT_STEP_SIZE + 1;
                ui4_delta = (pt_dsp_region->ui4_width - ui4_temp) / 2;
                pt_dsp_region->ui4_x = (pt_dsp_region->ui4_x >= ui4_delta) ?
                                       (pt_dsp_region->ui4_x - ui4_delta) : 0;
            }

            /* Fine-tune regions. */
            _sml_finetune_region (pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_get_adjust_range
 *
 * Description
 *      This API gets adjustable range for a specific source region. The minimum
 *      level indicates the minimum level for LEFT or DOWN direction, or the minimum
 *      zoom level. Whereas,the maximum level indicates the maximum level for UP or
 *      RIGHT direction, or the maximum zoom level.
 *
 * Input arguments
 *      pt_vid_region         Video region.
 *      e_adjust_dir          Adjust mode. Either vertical or horizontal.
 *
 * Output arguments
 *      pi1_level_min         The minimum level for LEFT or DOWN direction. Note
 *                            that this value could be 0 or a negative value.
 *      pi1_level_max         The maximum level for UP or RIGHT direction. Note
 *                            that this value could be 0 or a positive value.
 *
 * Returns
 *      SMR_OK                Successful.
 *      SMR_INV_ARG           Invalid arguments.
 *---------------------------------------------------------------------------*/
INT32 a_sml_get_adjust_range (VSH_REGION_INFO_T*    pt_vid_region,
                              SML_ADJUST_T          e_adjust_dir,
                              INT8*                 pi1_level_min,
                              INT8*                 pi1_level_max)
{
    INT32           i4_res;
    UINT8           ui1_step_num;

    i4_res = SMLR_OK;

    switch (e_adjust_dir)
    {
        case SML_ADJUST_POS_VERTICAL: /* Get adjustable range of vertical position. */
        {
            if ((pt_vid_region->ui4_y == 0) && (pt_vid_region->ui4_height == VSH_REGION_MAX_HEIGHT))
            {
                /* Not adjustable. */
                *pi1_level_min = 0;
                *pi1_level_max = 0;
            }
            else
            {
                /* Calculate step number. */
                ui1_step_num = (UINT8) ((VSH_REGION_MAX_HEIGHT - pt_vid_region->ui4_height) / 2 / PAN_STEP_SIZE);

                *pi1_level_min = (-1) * ui1_step_num;
                *pi1_level_max = (INT8)ui1_step_num;
            }
        }
        break;

        case SML_ADJUST_POS_HORIZONTAL: /* Get adjustable range of horizontal position. */
        {
            if ((pt_vid_region->ui4_x == 0) && (pt_vid_region->ui4_width == VSH_REGION_MAX_WIDTH))
            {
                /* Not adjustable. */
                *pi1_level_min = 0;
                *pi1_level_max = 0;
            }
            else
            {
                /* Calculate step number. */
                ui1_step_num = (UINT8) ((VSH_REGION_MAX_WIDTH - pt_vid_region->ui4_width) / 2 / PAN_STEP_SIZE);

                *pi1_level_min = (-1) * ui1_step_num;
                *pi1_level_max = (INT8)ui1_step_num;
            }
        }
        break;

        case SML_ADJUST_SIZE_VERTICAL:
        case SML_ADJUST_SIZE_HORIZONTAL:
        case SML_ADJUST_SIZE_BOTH:
        {
            *pi1_level_min = (-1) * ZOOM_STEP_NUM;
            *pi1_level_max = ZOOM_STEP_NUM;
        }
        break;

        default:
        {
            i4_res = SMLR_INV_ARG;
        }
        break;
    }

    return i4_res;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_get_adjust_region
 *
 * Description
 *      This API gets the source region after adjustment. The adjust level could
 *      be:
 *
 *       - a minus (which will result in a move on LEFT or UP, or ZOOM_OUT),
 *       - a plus (which will result in a move on RIGHT or DOWN, or ZOOM_IN), or
 *       - 0 (no adjustment).
 *
 * Input arguments
 *      e_adjust_dir          Adjust mode. Either vertical or horizontal.
 *      i1_level              The level to be adjusted. Could be a minus, a plus,
 *                            or 0.
 *      pt_wnd_region         Window region (boundary region).
 *      pt_vid_region         Video region to be adjusted.
 *      pt_dsp_region         Display region to be adjusted.
 *
 * Output arguments
 *      pt_vid_region         Video region after adjustment.
 *      pt_dsp_region         Display region after adjustment.
 *
 * Returns
 *      SMR_OK                Successful.
 *      SMR_INV_ARG           Invalid arguments.
 *---------------------------------------------------------------------------*/
INT32 a_sml_get_adjust_region (SML_ADJUST_T          e_adjust_dir,
                               INT8                  i1_level,
                               VSH_REGION_INFO_T*    pt_wnd_region,
                               VSH_REGION_INFO_T*    pt_vid_region,
                               VSH_REGION_INFO_T*    pt_dsp_region)
{
    INT32           i4_res;

    i4_res = SMLR_OK;

    switch (e_adjust_dir)
    {
        case SML_ADJUST_POS_VERTICAL: /* Adjust vertical position. */
        {
            _sml_adjust_vertical_pos    (i1_level, pt_vid_region);
        }
        break;

        case SML_ADJUST_POS_HORIZONTAL: /* Adjust horizontal position. */
        {
            _sml_adjust_horizontal_pos  (i1_level, pt_vid_region);
        }
        break;

        case SML_ADJUST_SIZE_VERTICAL: /* Vertical zoom in/out. */
        {
            _sml_adjust_vertical_size   (i1_level, pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
        break;

        case SML_ADJUST_SIZE_HORIZONTAL: /* Horizontal zoom in/out. */
        {
            _sml_adjust_horizontal_size (i1_level, pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
        break;

        case SML_ADJUST_SIZE_BOTH: /* Zoom in/out in both dimensions. */
        {
            _sml_adjust_vertical_size   (i1_level, pt_wnd_region, pt_vid_region, pt_dsp_region);
            _sml_adjust_horizontal_size (i1_level, pt_wnd_region, pt_vid_region, pt_dsp_region);
        }
        break;

        default:
        {
            i4_res = SMLR_INV_ARG;
        }
        break;
    }

    return i4_res;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_sml_is_zoom_enable
 *
 * Description
 *      This API is used to check if zoom operation is allowed for current screen mode
 * Input arguments
 * Output arguments
 * Returns
 *      TRUE                  Zoom operation is allowed.
 *      FALSE                 Zoom operation is not allowed.
 *---------------------------------------------------------------------------*/
BOOL a_sml_is_zoom_enable(VOID)
{
    INT16                   i2_scr_mode;
    SCC_VID_SCREEN_MODE_T   e_scr_mode;
    BOOL                    b_result = FALSE;
    INT32                   i4_ret;

    do {
        /* Check screen mode. */
        i4_ret = a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),
                               &i2_scr_mode);
        if (i4_ret != APP_CFGR_OK)
        {
            break;
        }

        e_scr_mode = (SCC_VID_SCREEN_MODE_T) i2_scr_mode;

        if ((e_scr_mode == SCC_VID_SCREEN_MODE_DOT_BY_DOT) ||
            (e_scr_mode == SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM))
        {
            break;
        }

        b_result = TRUE;
    } while (0);

    return b_result;
}

#if 0
BOOL a_zoom_pan_is_enable(VOID)
{
    return a_sml_is_zoom_enable();
}
#endif

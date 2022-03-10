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
 * $RCSfile: isl_custom.c,v $
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
#include "app_util/a_tv.h"
#include "app_util/a_common.h"
#include "app_util/a_isl.h"
#include "app_util/isl/isl.h"
#include "res/app_util/isl/isl_mlm.h"
#include "res/app_util/config/a_cfg_custom.h"

#ifdef APP_VTRL_INP_SRC_SUPPORT
#include "mmp/a_mmp.h"
#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define ISL_DEBUG_NAME(x)   //x


#ifdef APP_VTRL_INP_SRC_SUPPORT
#define ISL_VTRL_INPUT_SRC_ID_BASE                  ((UINT8)  200)
#define ISL_VTRL_MMP_ALIKE_ID                       ( 6)

#define ISL_VTRL_CAST_ALIKE_ID                      ( 7)
#define ISL_VTRL_CUSTOM_ALIKE_ID                      ( 8)

#endif


static UTF16_T          g_w2s_cast_tv_name[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
static UTF16_T          g_w2s_usb_tv_name[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
static UTF16_T          g_w2s_vtrl_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
#ifdef APP_VTRL_INP_SRC_SUPPORT
static ISL_REC_T t_g_isl_vtrl_recs[] =
{
#ifdef ISL_VTRL_INP_SRC_MMP
#ifdef ISL_VTRL_INP_SRC_MMP_BY_MEDIA_TYPE
    {
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+0, 0, 3, ISL_VTRL_MMP_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_0),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_MMP_PHOTO, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_MMP_PHOTO, DEV_UNKNOWN, SRC_AVC_HINT_NONE)
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    },
    {
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+1, 1, 3, ISL_VTRL_MMP_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_1),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_MMP_AUDIO, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_MMP_AUDIO, DEV_UNKNOWN, SRC_AVC_HINT_NONE)
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    },
    {
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+2, 2, 3, ISL_VTRL_MMP_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_2),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_MMP_VIDEO, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_MMP_VIDEO, DEV_UNKNOWN, SRC_AVC_HINT_NONE)
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
#else
#if 0
    {
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+0, 0, 1, ISL_VTRL_MMP_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_0),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_MMP, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_MMP, DEV_UNKNOWN, SRC_AVC_HINT_NONE)
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
#endif
#endif /* ISL_VTRL_INP_SRC_MMP_BY_MEDIA_TYPE */
#endif /* ISL_VTRL_INP_SRC_MMP */

#ifdef ISL_VTRL_INP_SRC_MMP
#endif
#ifdef ISL_VTRL_INP_SRC_CAST

    {
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+0/*1*/, 0, 1, ISL_VTRL_MMP_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_0),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_MMP, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_MMP, DEV_UNKNOWN, SRC_AVC_HINT_NONE)
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui4_attr_bits        */
        0,
        NULL                  /* pb_groupships        */
    }

    ,{
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+1/*0*/, 0, 1, ISL_VTRL_CAST_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_1),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            AVC_HANDLER_SCART_MODE_UNKNOWN,
            SRC_AVC_CHG_MANUAL
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui1_custom_data */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
    ,{
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+2/*0*/, 1, 2, ISL_VTRL_CAST_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_2),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            AVC_HANDLER_SCART_MODE_UNKNOWN,
            SRC_AVC_CHG_MANUAL
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui1_custom_data */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
    ,{
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+3/*0*/, 2, 3, ISL_VTRL_CAST_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_3),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            AVC_HANDLER_SCART_MODE_UNKNOWN,
            SRC_AVC_CHG_MANUAL
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui1_custom_data */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
    ,{
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+4/*0*/, 3, 4, ISL_VTRL_CAST_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_4),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            AVC_HANDLER_SCART_MODE_UNKNOWN,
            SRC_AVC_CHG_MANUAL
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui1_custom_data */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
    ,{
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+5/*0*/, 4, 5, ISL_VTRL_CAST_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_5),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            AVC_HANDLER_SCART_MODE_UNKNOWN,
            SRC_AVC_CHG_MANUAL
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui1_custom_data */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
    ,{
        MAKE_INP_SRC_DESC(ISL_VTRL_INPUT_SRC_ID_BASE+6/*0*/, 5, 6, ISL_VTRL_CAST_ALIKE_ID, INP_SRC_TYPE_VTRL, SN_VTRL_INP_6),
        {
            MAKE_INP_VIDEO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            MAKE_INP_AUDIO_DESC(DEV_VTRL_CAST, DEV_UNKNOWN, SRC_AVC_HINT_NONE),
            AVC_HANDLER_SCART_MODE_UNKNOWN,
            SRC_AVC_CHG_MANUAL
        },
        INVALID_INPUT_SRC_ID, /* ui1_scart_bundled_id */
        0,                    /* ui1_custom_data */
        0,                    /* ui4_attr_bits        */
        NULL                  /* pb_groupships        */
    }
#endif
};

static UINT8                ui1_g_num_of_isl_vtrl_rec  = (UINT8)(sizeof(t_g_isl_vtrl_recs)/sizeof(t_g_isl_vtrl_recs[0]));
static ISL_REC_T*           pt_g_isl_vtrl_rec_table    = t_g_isl_vtrl_recs;
#endif

const VIDEO_DEVICE_ALIKE_MAPPING at_g_video_alike_mapping_table[] =
{
    {DEV_AVC_COMBI     , DEV_AVC_S_VIDEO, 0}
   ,{DEV_AVC_COMP_VIDEO, DEV_UNKNOWN,     0}
   ,{DEV_AVC_S_VIDEO   , DEV_UNKNOWN,     0}
   ,{DEV_AVC_Y_PB_PR   , DEV_UNKNOWN,     1}
   ,{DEV_AVC_VGA       , DEV_UNKNOWN,     2}
   ,{DEV_AVC_DVI       , DEV_UNKNOWN,     3}
   ,{DEV_AVC_HDMI      , DEV_UNKNOWN,     3}
   ,{DEV_TUNER         , DEV_UNKNOWN,     4}
   ,{DEV_AVC_SCART     , DEV_UNKNOWN,     5}
#ifdef APP_VTRL_INP_SRC_SUPPORT
   ,{DEV_VTRL_MMP      , DEV_UNKNOWN,     ISL_VTRL_MMP_ALIKE_ID}
   ,{DEV_VTRL_MMP_PHOTO, DEV_UNKNOWN,     ISL_VTRL_MMP_ALIKE_ID}
   ,{DEV_VTRL_MMP_AUDIO, DEV_UNKNOWN,     ISL_VTRL_MMP_ALIKE_ID}
   ,{DEV_VTRL_MMP_VIDEO, DEV_UNKNOWN,     ISL_VTRL_MMP_ALIKE_ID}
   ,{DEV_VTRL_CAST,      DEV_UNKNOWN,     ISL_VTRL_CAST_ALIKE_ID}
   ,{DEV_VTRL_CAST,    DEV_UNKNOWN,     ISL_VTRL_CUSTOM_ALIKE_ID}
#endif
};
const UINT8 ui1_g_video_alike_mapping_table_size = (UINT8)(sizeof(at_g_video_alike_mapping_table)/sizeof(VIDEO_DEVICE_ALIKE_MAPPING));
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _isl_get_hdmi_dvi_mlm_key
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT8 _isl_get_hdmi_dvi_mlm_key(
                    ISL_REC_T*                  pt_isl_rec
                    )
{
    DEVICE_TYPE_T e_video_type = pt_isl_rec->t_avc_info.e_video_type;

    if (e_video_type == DEV_AVC_HDMI) {
        do {
#ifdef APP_CUSTOM_DYNAMIC_HDMI_SRC_NAME
            INT32 i4_ret;
            BOOL  b_result;

            /* Only when video connection is connected, middleware::CM can know the
             * connection with audio stream or not (with audio stream = HDMI, without
             * audio stream = DVI). Otherwise, middleware doesn't know the video content
             * is from DVI or HDMI. weider chang 6/9/2007
             */
            i4_ret = a_tv_is_dvi_source_by_isl_rec(pt_isl_rec, &b_result);
            if (i4_ret == TVR_OK && b_result == TRUE) {
                e_video_type = DEV_AVC_DVI;
                break;
            }
#endif
    #ifdef MLM_ISL_KEY_MSG_HDMI
            if (pt_isl_rec->ui1_iid_count == 1) {
                return MLM_ISL_KEY_MSG_HDMI;
            }
    #endif
    #ifdef MLM_ISL_KEY_MSG_HDMI_0
            return (UINT8)(MLM_ISL_KEY_MSG_HDMI_0 + pt_isl_rec->ui1_internal_id);
    #endif
        } while (0);
    }

    if (e_video_type == DEV_AVC_DVI) {
    #ifdef MLM_ISL_KEY_MSG_DVI
        if (pt_isl_rec->ui1_iid_count == 1) {
            return MLM_ISL_KEY_MSG_DVI;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_DVI_0
        return (UINT8)(MLM_ISL_KEY_MSG_DVI_0 + pt_isl_rec->ui1_internal_id);
    #endif
    }

    return MLM_ISL_KEY_MSG_UNKNOWN;
}
static INT32 _isl_set_vtrl_inp_hidden()
{
    INT32   i4_ret;
    UINT8   ui1_hide_value = 0;
    UINT16  ui2_i;
    //UINT16  ui2_cfg_idx;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
    //SIZE_T  z_size;

    i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT((" file: %s line: %d  %s,fail\n", __FILE__, __LINE__, __FUNCTION__));
    }

    for(ui2_i=0;ui2_i<5;ui2_i++)//Find del id
    {
        //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + ui2_i;
        //i4_ret = acfg_get(ui2_cfg_idx, s_inp_name, &z_size);
        i4_ret = a_cfg_get_vtrl_name(ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        if(i4_ret < 0)
        {
            DBG_LOG_PRINT(("%s,%d acfg_get fail \r\n",__FUNCTION__,__LINE__));
        }
        if(c_strlen(s_inp_name) == 0)
        {
            ui1_hide_value |= (UINT8)1 << (7 + ui2_i);
        }
    }

    DBG_LOG_PRINT(("<VTRL INPUT>[%s][%d] a_cfg_cust_set_hide_from_input_manually(%d)\n", __FUNCTION__, __LINE__, ui1_hide_value));

    i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT((" [%s][%d] fail\n", __FUNCTION__, __LINE__));
    }

    return i4_ret;

}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      isl_get_alike_id
 * Description
 *      This API is use to get device alike type
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT8 isl_get_alike_id(
                    DEVICE_TYPE_T               e_dev_type,
                    DEVICE_TYPE_T               e_combi_preferred_dev_type
                    )
{
    UINT8 ui1_idx;

    for (ui1_idx = 0; ui1_idx < ui1_g_video_alike_mapping_table_size; ui1_idx++) {
        if (e_dev_type != at_g_video_alike_mapping_table[ui1_idx].e_dev_type) {
            continue;
        }

        if (e_dev_type == DEV_AVC_COMBI) {
            if (e_combi_preferred_dev_type != at_g_video_alike_mapping_table[ui1_idx].e_combi_preferred_dev_type) {
                continue;
            }
        }

        return at_g_video_alike_mapping_table[ui1_idx].ui1_alike_id;
    }

    return UNCLASSIFIED_ALIKE_TYPE;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_VTRL_INP_SRC_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      a_isl_init_vtrl_inp_rec
 * Description
 *      This API is used to init and config virtual input source records.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_isl_init_vtrl_inp_rec (
                    ISL_REC_T*                  pt_isl_rec_table,
                    UINT8                       ui1_num_of_rec
                    )
{

    INT32       i4_ret;
    UINT8       ui1_num_of_vtrl_inp = a_isl_get_num_of_vtrl_inp();
    UINT8       ui1_rec_idx;
    ISL_REC_T*  pt_isl_rec = NULL;
    UINT8       ui1_id;

    if (pt_isl_rec_table == NULL || ui1_num_of_rec == 0) {
        return ISLR_INV_ARG;
    }
    if (ui1_num_of_rec > MAX_NUM_OF_ISL_REC) {
        return ISLR_INV_ARG;
    }
    if (ui1_num_of_vtrl_inp >= ui1_num_of_rec) {
        return ISLR_INV_ARG;
    }

    if (ui1_num_of_vtrl_inp == 0) {
        /* no action */
        return ISLR_OK;
    }

    a_isl_lock();
    do {
        i4_ret = ISLR_OK;

        for (ui1_rec_idx = 0; ui1_rec_idx < ui1_num_of_vtrl_inp; ui1_rec_idx++) {
            /* find record for add virtual input source */
            for (ui1_id = 0; ui1_id < ui1_num_of_rec; ui1_id++) {
                pt_isl_rec = &(pt_isl_rec_table[ui1_id]);
                if (IS_ISL_REC_EMPTY(pt_isl_rec)) {
                    break;
                }
            }
            if (ui1_id >= ui1_num_of_rec) {
                i4_ret = ISLR_CANNOT_ADD;
                break;
            }

            /* overrite hardcoded configuration */
            pt_g_isl_vtrl_rec_table[ui1_rec_idx].ui1_id = ui1_id;

            /* add virtual input source */
            c_memcpy(pt_isl_rec,
                     &(pt_g_isl_vtrl_rec_table[ui1_rec_idx]),
                     sizeof(ISL_REC_T));
        }
    } while (0);
    a_isl_unlock();
    _isl_set_vtrl_inp_hidden();

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_isl_get_num_of_vtrl_inp
 * Description
 *      This API is used to caculate the total virtual input source number.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT8 a_isl_get_num_of_vtrl_inp(
                    VOID
                    )
{
    DBG_LOG_PRINT(("%s() %d: ui1_g_num_of_isl_vtrl_rec=%d\r\n",__FUNCTION__,__LINE__,ui1_g_num_of_isl_vtrl_rec));
    return ui1_g_num_of_isl_vtrl_rec;
}
#endif /* APP_VTRL_INP_SRC_SUPPORT */

INT32 a_isl_get_vtrl_input_display_name(ISL_REC_T*   pt_isl_rec,
                                            CHAR*         s_name)
{
    //SIZE_T  z_size;
    //UINT16  ui2_cfg_idx;
    INT32   i4_ret;
    CHAR    s_inp_dsp_name[APP_CFG_CUSTOM_INP_NAME_LEN] ={0};
    ISO_639_LANG_T s639_lang;

    //DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s (pt_isl_rec->ui1_id:%d)\n", __FILE__, __LINE__, __FUNCTION__, pt_isl_rec->ui1_id));

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    //DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s (lang:%s)\n", __FILE__, __LINE__, __FUNCTION__, s639_lang));
    if(i4_ret != APP_CFGR_OK)
    {
        return 0;
    }
    if(c_strncmp(s639_lang,"eng",3) ==0)
    {
        i4_ret = a_cfg_get_name_display(1,pt_isl_rec->ui1_internal_id - 1,s_inp_dsp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
    }
    else if(c_strncmp(s639_lang,"fre",3) ==0)
    {
        i4_ret = a_cfg_get_name_display(2,pt_isl_rec->ui1_internal_id - 1,s_inp_dsp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
    }
    else if(c_strncmp(s639_lang,"spa",3) ==0)
    {
        i4_ret = a_cfg_get_name_display(3,pt_isl_rec->ui1_internal_id - 1,s_inp_dsp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
    }


    if(c_strlen(s_inp_dsp_name)!=0)
    {
        //DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s s_inp_dsp_name %s)\n", __FILE__, __LINE__, __FUNCTION__, s_inp_dsp_name));
        c_strncpy(s_name,s_inp_dsp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        return 0;
    }
    else
    {
        //c_strncpy(s_name,"SMARTCAST",12);
        c_strncpy(s_name,"ISL_No_Name",12);
        return 0;
    }

}
/*-----------------------------------------------------------------------------
 * Name
 *      a_isl_get_display_name
 * Description
 *      This API is use to get display for each input source
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UTF16_T* a_isl_get_display_name(
                    ISL_REC_T*                  pt_isl_rec
                    )
{
    UINT8 ui_idx = MLM_ISL_KEY_MSG_UNKNOWN;

    if (pt_isl_rec == NULL) {
        return NULL;
    }

    BOOL bIsSrcHDMI = FALSE;
    if( (pt_isl_rec->e_src_type == INP_SRC_TYPE_AV)
      &&(pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI)
      )
    {
        bIsSrcHDMI = TRUE;
    }

    ISL_DEBUG_NAME(
        DBG_LOG_PRINT (("[ISL][INPUT_SRC]{%s,%d} ui1_id:%d, e_src_type:%d, ui1_internal_id:%d, e_video_type:0x%X, bIsSrcHDMI:%d\n",
        __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->e_src_type,
        pt_isl_rec->ui1_internal_id, pt_isl_rec->t_avc_info.e_video_type, bIsSrcHDMI
        )); );


    /* DVD bundled source */
    if (pt_isl_rec->ui4_attr_bits & ISL_ATTR_BIT_DVD_BUNDLE) {
    #ifdef MLM_ISL_KEY_MSG_DVD
        if (pt_isl_rec->ui1_iid_count == 1) {
            return MLM_ISL_TEXT(MLM_ISL_LANG_ENG, MLM_ISL_KEY_MSG_DVD);
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_DVD_0
        if ((MLM_ISL_KEY_MSG_DVD_0 + pt_isl_rec->ui1_internal_id) < MLM_ISL_NUM_KEY) {
            return MLM_ISL_TEXT(MLM_ISL_LANG_ENG, (MLM_ISL_KEY_MSG_DVD_0 + pt_isl_rec->ui1_internal_id));
        } else {
            return NULL;
        }
    #else
        return NULL;
    #endif
    }

    switch(pt_isl_rec->t_avc_info.e_video_type) {
    case DEV_TUNER:
    #ifdef MLM_ISL_KEY_MSG_TV
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_TV;
            break;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_TV_0
        ui_idx = MLM_ISL_KEY_MSG_TV_0 + pt_isl_rec->ui1_internal_id;
    #endif
        break;

    case DEV_AVC_COMP_VIDEO:
#if 0
    #ifdef MLM_ISL_KEY_MSG_CVBS
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_CVBS;
            break;
        }
    #endif
#else
    #ifdef MLM_ISL_KEY_MSG_COMBI
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_COMBI;
            break;
        }
    #endif
#endif
    #ifdef MLM_ISL_KEY_MSG_CVBS_0
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_CVBS_0 + pt_isl_rec->ui1_internal_id);
    #endif
        break;

    case DEV_AVC_S_VIDEO:
    #ifdef MLM_ISL_KEY_MSG_S_VIDEO
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_S_VIDEO;
            break;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_S_VIDEO_0
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_S_VIDEO_0 + pt_isl_rec->ui1_internal_id);
    #endif
        break;

    case DEV_AVC_Y_PB_PR:
    #ifdef MLM_ISL_KEY_MSG_YPBPR
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_YPBPR;
            break;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_YPBPR_0
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_YPBPR_0 + pt_isl_rec->ui1_internal_id);
    #endif
        break;

    case DEV_AVC_VGA:
    #ifdef MLM_ISL_KEY_MSG_VGA
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_VGA;
            break;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_VGA_0
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_VGA_0 + pt_isl_rec->ui1_internal_id);
    #endif
        break;

    case DEV_AVC_SCART:
    #ifdef MLM_ISL_KEY_MSG_SCART
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_SCART;
            break;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_SCART_0
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_SCART_0 + pt_isl_rec->ui1_internal_id);
    #endif
        break;

    case DEV_AVC_HDMI:
    case DEV_AVC_DVI:
        ui_idx = _isl_get_hdmi_dvi_mlm_key(pt_isl_rec);
        break;

    case DEV_AVC_COMBI:
    #ifdef MLM_ISL_KEY_MSG_COMBI
        if (pt_isl_rec->ui1_iid_count == 1) {
            ui_idx = MLM_ISL_KEY_MSG_COMBI;
            break;
        }
    #endif
    #ifdef MLM_ISL_KEY_MSG_COMBI_0
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_COMBI_0 + pt_isl_rec->ui1_internal_id);
    #endif
        break;

#ifdef APP_VTRL_INP_SRC_SUPPORT
    case DEV_VTRL_MMP:
    #ifndef MLM_ISL_KEY_MSG_MMP
        ui_idx = MLM_ISL_KEY_MSG_MMP;
        break;
    #else
        if (c_uc_w2s_strlen(g_w2s_usb_tv_name) == 0)
        {
            c_uc_ps_to_w2s(ISL_USB_TV_DEFAULT_NAME,g_w2s_usb_tv_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        }
        return g_w2s_usb_tv_name;
      /*  return NULL;*/
    #endif

    case DEV_VTRL_MMP_PHOTO:
    #ifdef MLM_ISL_KEY_MSG_MMP_0
        ui_idx = MLM_ISL_KEY_MSG_MMP_0;
        break;
    #else
        return NULL;
    #endif

    case DEV_VTRL_MMP_AUDIO:
    #ifdef MLM_ISL_KEY_MSG_MMP_1
        ui_idx = MLM_ISL_KEY_MSG_MMP_1;
        break;
    #else
        return NULL;
    #endif

    case DEV_VTRL_MMP_VIDEO:
    #ifdef MLM_ISL_KEY_MSG_MMP_2
        ui_idx = MLM_ISL_KEY_MSG_MMP_2;
        break;
    #else
        return NULL;
    #endif
#endif /* APP_VTRL_INP_SRC_SUPPORT */

    case DEV_VTRL_CAST:
    {
        ISL_DEBUG_NAME( DBG_LOG_PRINT (("[ISL][INPUT_SRC]{%s,%d} case DEV_VTRL_CAST: pt_isl_rec->ui1_id:%d, pt_isl_rec->ui1_internal_id:%d \n",
            __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->ui1_internal_id )); );

        if(pt_isl_rec->ui1_internal_id == 0) // SMARTCAST
        {
        #ifdef MLM_ISL_KEY_MSG_CAST_TV
            ui_idx = MLM_ISL_KEY_MSG_CAST_TV;
        #else
            if (c_uc_w2s_strlen(g_w2s_cast_tv_name) == 0)
            {
                c_uc_ps_to_w2s(ISL_CAST_TV_DEFAULT_NAME,g_w2s_cast_tv_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            }
            return g_w2s_cast_tv_name;
        #endif
        }
        else // WatchFree
        {
            CHAR    s_inp_dsp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
            //DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s (pt_isl_rec->ui1_id:%d)\n", __FILE__, __LINE__, __FUNCTION__, pt_isl_rec->ui1_id));

            a_isl_get_vtrl_input_display_name(pt_isl_rec,s_inp_dsp_name);

            c_uc_ps_to_w2s(s_inp_dsp_name,g_w2s_vtrl_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);


            return g_w2s_vtrl_inp_name;
        }
    }
    break;
/*
    case DEV_VTRL_USB:
    {
        if (c_uc_w2s_strlen(g_w2s_usb_tv_name) == 0)
        {
            c_uc_ps_to_w2s(ISL_USB_TV_DEFAULT_NAME,g_w2s_usb_tv_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        }
        return g_w2s_usb_tv_name;
        break;
    }
  */
    default:
    #ifdef MLM_ISL_KEY_MSG_AUDIO_0
        if (pt_isl_rec->t_avc_info.e_audio_type == DEV_UNKNOWN) {
            return NULL;
        }
        ui_idx = (UINT8)(MLM_ISL_KEY_MSG_AUDIO_0 + pt_isl_rec->ui1_internal_id);
        break;
    #else
        return NULL;
    #endif
    }

    if (ui_idx >= MLM_ISL_KEY_MSG_UNKNOWN) {
        return NULL;
    }

    return MLM_ISL_TEXT(MLM_ISL_LANG_ENG, ui_idx);
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_isl_get_display_name_ex
 * Description
 *      This API is use to get display for each input source. This API takes
 *      "Skip" into account.
 * Input arguments
 *      pt_isl_rec      ISL record.
 *      ui1_str_len     Length of pw2s_str.
 * Output arguments
 *      pw2s_str        String memory.
 * Returns
 *      ISLR_OK         Function succeeded.
 *      Otherwise       Function failed.
 *---------------------------------------------------------------------------*/
INT32 a_isl_get_display_name_ex (
                    ISL_REC_T*                  pt_isl_rec,
                    UTF16_T*                    pw2s_str,
                    UINT8                       ui1_str_len
                    )
{
    INT32 i4_ret;
    UTF16_T w2s_usr_inp_name [APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    CHAR s_usr_inp_name [APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    //UINT8 ui1_output_str_len = 0;
    UTF16_T w2s_token [] = L"Skip";

    if (pt_isl_rec == NULL || pw2s_str == NULL)
    {
        return ISLR_INV_ARG;
    }

    BOOL bIsSrcHDMI = FALSE;
    if( (pt_isl_rec->e_src_type == INP_SRC_TYPE_AV)
      &&(pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI)
      )
    {
        bIsSrcHDMI = TRUE;
    }

    ISL_DEBUG_NAME(
        DBG_LOG_PRINT (("[ISL][INPUT_SRC]{%s,%d} ui1_id:%d, e_src_type:%d, ui1_internal_id:%d, e_video_type:0x%X, bIsSrcHDMI:%d\n",
        __FUNCTION__, __LINE__, pt_isl_rec->ui1_id, pt_isl_rec->e_src_type,
        pt_isl_rec->ui1_internal_id, pt_isl_rec->t_avc_info.e_video_type, bIsSrcHDMI
        )); );

    if( bIsSrcHDMI )
    {
        i4_ret = a_cfg_custom_get_inp_name_with_cec_name (pt_isl_rec, w2s_usr_inp_name, ui1_str_len);
        if (i4_ret != APP_CFGR_OK)
        {
            return ISLR_FAIL;
        }
        c_uc_w2s_to_ps (w2s_usr_inp_name, s_usr_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }
    else
    {
        i4_ret = a_cfg_custom_get_inp_name(pt_isl_rec->ui1_id, s_usr_inp_name);
        if (i4_ret != APP_CFGR_OK)
        {
            return ISLR_FAIL;
        }
        c_uc_ps_to_w2s(s_usr_inp_name,w2s_usr_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
    }


    if (a_cfg_custom_is_inp_name_empty (s_usr_inp_name))
    {
        ISL_DEBUG_NAME( DBG_LOG_PRINT (("[ISL][INPUT_SRC][CEC]{%s,%d} s_usr_inp_name is empty~ => Use display_name \n", __FUNCTION__, __LINE__ )); );

        /* No custom input label. Use actual input name instead. */

        UTF16_T* pw2s_display_name = a_isl_get_display_name(pt_isl_rec);

      #if 1
        c_uc_w2s_strncpy(pw2s_str, pw2s_display_name, ui1_str_len);
      #else

        ui1_output_str_len = c_uc_w2s_strlen(pw2s_display_name);
        if (ui1_str_len < ui1_output_str_len)
        {
            c_uc_w2s_strncpy (pw2s_str, pw2s_display_name, ui1_str_len);
        }
        else
        {
            c_uc_w2s_strcpy (pw2s_str, pw2s_display_name);
        }
      #endif
    }
    else
    {
        UTF16_T w2s_inp_name [50] = {0};

        /* Custom label exists. Check whether it is "Skip". */
        if (c_uc_w2s_strcmp (w2s_token, w2s_usr_inp_name) == 0)
        {
            UTF16_T* pw2s_display_name = a_isl_get_display_name(pt_isl_rec);

            c_uc_w2s_strcpy (w2s_inp_name, pw2s_display_name );
            c_uc_w2s_strcat (w2s_inp_name, L":Skip");

            ISL_DEBUG_NAME( DBG_LOG_PRINT (("[ISL][INPUT_SRC][CEC]{%s,%d} Use display_name+Skip \n", __FUNCTION__, __LINE__ )); );

          #if 1
            c_uc_w2s_strncpy (pw2s_str, w2s_inp_name, ui1_str_len);
          #else
            if( ui1_str_len < c_uc_w2s_strlen(w2s_inp_name) )
            {
                c_uc_w2s_strncpy (pw2s_str, w2s_inp_name, ui1_str_len);
            }
            else
            {
                c_uc_w2s_strcpy (pw2s_str, w2s_inp_name);
            }
          #endif

        }
        else
        {
            ISL_DEBUG_NAME( DBG_LOG_PRINT (("[ISL][INPUT_SRC][CEC]{%s,%d} Use name from CEC\n",
                __FUNCTION__, __LINE__ )); );

          #if 1
            c_uc_w2s_strncpy (pw2s_str, w2s_usr_inp_name, ui1_str_len);
          #else
            ui1_output_str_len = c_uc_w2s_strlen (w2s_usr_inp_name);
            if (ui1_str_len < ui1_output_str_len)
            {
                c_uc_w2s_strncpy (pw2s_str, w2s_usr_inp_name, ui1_str_len);
            }
            else
            {
                c_uc_w2s_strcpy (pw2s_str, w2s_usr_inp_name);
            }
          #endif
        }
    }

 #if 0
    // MUSC-7759/TMC-8522: Change "WatchFree" to "WatchFree+"
    // e_src_type:4, ui1_internal_id:1, e_video_type:0x4000005
    if( (pt_isl_rec->e_src_type == INP_SRC_TYPE_VTRL)
      &&(pt_isl_rec->t_avc_info.e_video_type == DEV_VTRL_CAST)
      &&(pt_isl_rec->ui1_internal_id == 1)
      )
    {
        if( c_uc_w2s_strcmp( pw2s_str, L"WatchFree" ) == 0 )
        {
            ISL_DEBUG_NAME( DBG_LOG_PRINT (("[ISL][INPUT_SRC]{%s,%d} Change \"WatchFree\" to \"WatchFree+\" \n",
                __FUNCTION__, __LINE__ )); );
            c_uc_w2s_strcpy( pw2s_str, L"WatchFree+" );
        }
    }
 #endif

    return ISLR_OK;
}

#ifdef APP_VTRL_INP_SRC_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      a_isl_get_app_name_of_vtrl_inp
 * Description
 *      1. This API is use to get application name of virtual input resources.
 *         The application name will be used in _tv_select_vtrl_svc in app_tv.c
 *         if APP_VTRL_INP_SRC_SUPPORT is defined.
 *      2. It is a customization API, and it is recommend to implement in
 *         customer's res/app_util/isl/isl_custom.c
 * Input arguments
 *      -
 * Output arguments
 *      -
 * Returns
 *      ISLR_OK                 The routine is OK.
 *      ISLR_FAIL               The routine is failed
 *---------------------------------------------------------------------------*/
INT32 a_isl_get_app_name_of_vtrl_inp(
                    ISL_REC_T*                  pt_isl_rec,
                    CHAR*                       ps_name
                    )
{
    if (pt_isl_rec == NULL || ps_name == NULL) {
        return ISLR_INV_ARG;
    }

    if (pt_isl_rec->e_src_type != INP_SRC_TYPE_VTRL) {
        return ISLR_INV_ARG;
    }

    switch (pt_isl_rec->t_avc_info.e_video_type)
    {
    case DEV_VTRL_MMP:
    case DEV_VTRL_MMP_PHOTO:
    case DEV_VTRL_MMP_AUDIO:
    case DEV_VTRL_MMP_VIDEO:
        c_strcpy (ps_name, MMP_NAME);
        return ISLR_OK;
    case DEV_VTRL_CAST:
        c_strcpy (ps_name, ISL_CAST_TV_DEFAULT_NAME);
        return ISLR_OK;
        /*
    case DEV_VTRL_USB:
        c_strcpy (ps_name, ISL_USB_TV_DEFAULT_NAME);
        return ISLR_OK;
        */
    default:
        break;
    }

    return ISLR_NOT_EXIST;
}
#endif /* APP_VTRL_INP_SRC_SUPPORT */

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
 * $RCSfile: listmode.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: heyi.wang $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *          This is the src file for listmode.
 *---------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_dbg.h"
#include "listmode.h"
#include "listmode_view.h"

#include "time.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "u_minfo.h"

#include "agent/a_agent.h"

#include "mmp/thumbnailmode2/thumbnailmode.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "mmp/sort/a_mmp_sort.h"
#ifdef APP_MENU_MMP_COEXIST
#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"
#endif

#include "amb/a_amb.h"
#include "mmp/a_mmp.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/mmp/gen/mmp_lm_custom_layout.h"

#include "mmp/file_filter/mmp_ff.h"
#include "app_util/lbw/_lbw.h"

#include <time.h>
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static MMP_LM_ITEM_REG_INFO_T   t_g_item_reg_info;
static MMP_LM_ITEM_INFO_T       t_g_item_info[LM_LBW_ELEM_NUM_PER_PAGE];
static UINT32                   ui4_g_show_start_idx;
UINT32                          ui4_g_play_idx   = 0;
static E_MMP_LM_LOAD_STATUS_T   e_g_load_status = LM_STATUS_NORMAL;
static UINT8                    ui1_g_loaded_file_num = 0;
static BOOL                     b_g_use_cache = FALSE;

typedef struct {
UINT32     ui4_file_num;
UINT32     ui4_dir_num;
BOOL       b_reload;
CHAR       s_curr_path[MMP_BE_MAX_PATH_LEN];
}PLAYLIST;
static CHAR*                    ptr_g_last_file = NULL;

static PLAYLIST               t_g_playlist_crnt = {0};      //current playing list

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT
extern INT32 mmp_lm_cli_init(VOID);
#endif
VOID mmp_lm_update_file_status(UINT32 ui4_file_idx);

VOID mmp_lm_update_crnt_playing_file()
{
    MMP_MEDIA_TYPE_T     e_media_type;
    UINT32               ui4_play_idx;

    if( MMPR_OK == mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type) &&
        MMPR_OK == mmp_mc_list_get_idx((e_media_type & MMP_MEDIA_TYPE_AUDIO) ?  MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE,MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_play_idx) &&
        MMP_INV_FILE_IDX != ui4_play_idx &&
        MMPR_OK == mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &t_g_playlist_crnt.ui4_dir_num, &t_g_playlist_crnt.ui4_file_num))
    {
        ui4_play_idx += t_g_playlist_crnt.ui4_dir_num;
        mmp_be_set_focus_item(ui4_play_idx);
    }
}

inline VOID mmp_lm_fill_listbox_item_txt(LBW_DATA_REQ_PACK_T* pt_drp,
                                             UINT32               ui4_idx,
                                             UINT8                ui1_col,
                                             const UTF16_T*       w2s_text,
                                             UINT16               ui2_len_text)
{
    UINT16 ui2_len_text_eff = MIN (ui2_len_text, pt_drp->at_cols_fmt[ui1_col].ui2_max_text_len);

    c_uc_w2s_strncpy (pt_drp->at_elems_buf[ui4_idx].at_items[ui1_col].pw2s_text,
                      w2s_text,
                      ui2_len_text_eff);

    c_uc_w2s_set (pt_drp->at_elems_buf[ui4_idx].at_items[ui1_col].pw2s_text,
                  (UINT32) ui2_len_text_eff,
                  (UTF16_T) 0);
}

inline VOID mmp_lm_fill_listbox_item_img(LBW_DATA_REQ_PACK_T* pt_drp,
                                              UINT32               ui4_idx,
                                              UINT8                ui1_col,
                                              HANDLE_T             h_img)
{
    pt_drp->at_elems_buf[ui4_idx].at_items[ui1_col].h_img = h_img;
}

inline VOID mmp_lm_fill_listbox_item_custom_info(LBW_DATA_REQ_PACK_T* pt_drp,
                                                       UINT32               ui4_idx)
{
    UINT8 ui1_col = LM_FILE_LB_FIX_COL_NUM;
    for(;ui1_col < LM_FILE_LB_COL_MAX_NUM;ui1_col++)
        mmp_lm_fill_listbox_item_txt(pt_drp,ui4_idx,ui1_col,L"",0);
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_normal_list_clear_custom_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32  _mmp_lm_item_num_to_str(UINT32          ui4_idx,
                                                 UTF16_T*        pw2s_text,
                                                 SIZE_T*         pt_size)
{
    CHAR    sz_num[LM_FILE_LB_FILE_NUM_MAX_BIT] = {0};
    UINT32  ui4_disp_idx = 0;

    if (!pw2s_text ||
        0 == *pt_size)
    {
        return MMPR_INV_ARG;
    }

    ui4_disp_idx = ui4_idx + 1;

    if (0 == ui4_disp_idx)
    {
        ui4_disp_idx = LM_LBW_ELEM_NUM_PER_PAGE;
    }

    c_snprintf(sz_num, sizeof(sz_num), MMP_LBW_NUM_TXT_TPML, ui4_disp_idx);

    if (c_strlen(sz_num) * sizeof(UTF16_T) > *pt_size)
    {
        *pt_size = c_strlen(sz_num) * sizeof(UTF16_T);
        return MMPR_OUT_OF_MEM;
    }

    c_uc_ps_to_w2s(sz_num, pw2s_text, *pt_size);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_normal_list_update_basic_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_normal_list_update_basic_info(UINT32        ui4_start,
                                                            UINT32        ui4_end,
                                                            VOID*         pv_elems_data,
                                                            BOOL*         ab_elems_sel)
{
    UINT32                  ui4_cnt = 1;
    UINT32                  ui4_vp_idx;
    UINT32                  ui4_idx        = ui4_start;
    UINT32                  ui4_item_idx   = 0;
    CHAR*                   s_new_name     = NULL;
    MMP_ITEM_TYPE_T         item_type;
    SIZE_T                  t_num_w2s_size = sizeof(UTF16_T) * LM_FILE_LB_FILE_NUM_MAX_BIT;
    MMP_MEDIA_TYPE_T        e_filter_type  = MMP_MEDIA_TYPE_UNKNOWN;
    MMP_LM_FILE_STATUS_T    e_file_status  = MMP_LM_FILE_STATUS_NONE;
    MMP_ITEM_INFO_T         t_item         = {0};
    LBW_DATA_REQ_PACK_T*    pt_drp         = (LBW_DATA_REQ_PACK_T *) pv_elems_data;

    for(ui4_idx = ui4_start;ui4_idx <= ui4_end;ui4_idx++)
    {
        ui4_item_idx = ui4_idx - ui4_g_show_start_idx;
        ui4_vp_idx   = ui4_idx - pt_drp->ui4_elem_start;
        if(!b_g_use_cache)
        {
            if(MMPR_OK != mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                               ITEM_TYPE_NONE,
                                               ui4_idx,
                                               &ui4_cnt,
                                               &t_item) ||
                                               NULL == t_item.s_name ||
                                               NULL == t_item.s_parent_name)
            {
                /* refresh */
                MMPR_LOG_ON_FAIL( mmp_be_refresh(MMP_BE_FF_IDX_CRT,MMP_BE_REFRESH_TYPE_ITEM_LST));
                return MMPR_FAIL;
            }

            if(0 == c_strcmp(t_item.s_name, "..") ||
               0 == c_strcmp(t_item.s_name, "\\"))
            {
                s_new_name = t_item.s_name;
            }
            else
            {
                s_new_name = mmp_be_get_filtered_item_name(t_item.s_name);
            }
            MMP_DBG_INFO(("[MMP][%s %d]vp = %d file[%d] name: %s\n",__FUNCTION__,__LINE__,(ui4_idx - pt_drp->ui4_elem_start) ,ui4_vp_idx,s_new_name));
            c_uc_ps_to_w2s (s_new_name,t_g_item_info[ui4_item_idx].ws_name, MMP_BE_MAX_PATH_LEN);
            c_uc_ps_to_w2s(t_item.s_parent_name,t_g_item_info[ui4_item_idx].ws_parent_name,MMP_BE_MAX_PATH_LEN);
            /* set item num */
           MMPR_LOG_ON_FAIL( _mmp_lm_item_num_to_str(ui4_idx,t_g_item_info[ui4_item_idx].w2s_num,&t_num_w2s_size));
        }

        mmp_lm_fill_listbox_item_txt(pt_drp,ui4_vp_idx,LM_FILE_LB_COL_FILE_NUM_IDX,t_g_item_info[ui4_item_idx].w2s_num,(UINT16)c_uc_w2s_strlen(t_g_item_info[ui4_item_idx].w2s_num));

        item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT, ui4_idx);

        /* set item folder icon */
        if (ITEM_TYPE_DIR == item_type)
        {
            t_g_item_info[ui4_vp_idx].e_item_type = ITEM_TYPE_DIR;

            mmp_lm_fill_listbox_item_img(pt_drp,
                                         ui4_vp_idx,
                                         LM_FILE_LB_COL_ICON_IDX,
                                         mmp_lm_view_get_image(( 0 != c_strcmp(t_item.s_name, "..") && \
                                                                0 != c_strcmp(t_item.s_name, "\\") ) ? \
                                         MMP_LM_VIEW_IMG_TYPE_IMG_FOLDER : MMP_LM_VIEW_IMG_TYPE_IMG_PRE_FOLDER));
        }
        else if (ITEM_TYPE_FILE == item_type)
        {
            CHAR  ps[MMP_BE_MAX_PATH_LEN + 1] = {0};
            t_g_item_info[ui4_item_idx].e_item_type = ITEM_TYPE_FILE;

            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_filter_type);

            MMPR_LOG_ON_FAIL( mmp_lm_get_file_status_by_idx(ui4_idx,e_filter_type,&e_file_status));
            c_uc_w2s_to_ps(t_g_item_info[ui4_item_idx].ws_name,ps,sizeof(ps));
            s_new_name = ps;
            DBG_LOG_PRINT(("[MMP][%s %d] update list[%2d] file[%2d][%s] e_file_status = %d\n",
                __FUNCTION__,__LINE__,
                ui4_vp_idx,
                ui4_idx,
                s_new_name,
                e_file_status));

            switch(e_file_status)
            {
                case MMP_LM_FILE_IS_PLAYING:
                    ui4_g_play_idx = ui4_idx;
                    ab_elems_sel[ui4_vp_idx] = TRUE;
                    mmp_lm_fill_listbox_item_img(pt_drp,ui4_vp_idx,LM_FILE_LB_COL_ICON_IDX,mmp_lm_view_get_image(MMP_LM_VIEW_IMG_TYPE_IMG_PLAY));
                    break;
                case MMP_LM_FILE_IS_PAUSED:
                    ui4_g_play_idx = ui4_idx;
                    ab_elems_sel[ui4_vp_idx] = TRUE;
                    mmp_lm_fill_listbox_item_img(pt_drp,ui4_vp_idx,LM_FILE_LB_COL_ICON_IDX,mmp_lm_view_get_image(MMP_LM_VIEW_IMG_TYPE_IMG_PAUSE));
                    break;
                default:
                    ab_elems_sel[ui4_vp_idx] = TRUE;
                    mmp_lm_fill_listbox_item_img(pt_drp,ui4_vp_idx,LM_FILE_LB_COL_ICON_IDX,mmp_lm_view_get_image(MMP_LM_VIEW_IMG_TYPE_IMG_NULL));
                    break;
            }
        }

        mmp_lm_fill_listbox_item_txt(pt_drp,
                                     ui4_vp_idx,
                                     LM_FILE_LB_COL_FILE_NAME_IDX,
                                     t_g_item_info[ui4_item_idx].ws_name,
                                     (UINT16) c_uc_w2s_strlen (t_g_item_info[ui4_item_idx].ws_name));
        mmp_lm_fill_listbox_item_custom_info(pt_drp,ui4_vp_idx);
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_update_item_custom_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_update_item_custom_info(UINT32    ui4_idx,
                                             VOID*     pv_elems_data)
{
    LM_DISPLAY_ITEM_REG_T   t_display_item;
    MMP_ITEM_INFO_T         t_item_info;
    DTG_T                   t_loc_dtg;
    UTF16_T                 w2s_text[MMP_FB_LM_FILE_INFO_LENG + 1] = {0};
    UINT32                  ui4_i = 0;
    SIZE_T                  t_size = 0;
    UINT32                  ui4_temp_idx = ui4_idx % LM_LBW_ELEM_NUM_PER_PAGE;
    UINT32                  ui4_cnt = 1;
    CHAR                    sz_info[128] = {0};
    LBW_DATA_REQ_PACK_T*    pt_drp  = (LBW_DATA_REQ_PACK_T *) pv_elems_data;
    FM_FILE_INFO_T          t_info;
    CHAR                    s_full_path[MMP_BE_MAX_PATH_LEN]={0};

    ui4_idx -= pt_drp->ui4_elem_start;

    c_memset(&t_display_item, 0, sizeof(LM_DISPLAY_ITEM_REG_T));

    MMPR_LOG_ON_FAIL(mmp_lm_get_cur_display_item_info(&t_display_item));

    if (ITEM_TYPE_DIR == t_g_item_info[ui4_temp_idx].e_item_type)
    {
        /* directory, has no custom info, return directly. */
        return MMPR_OK;
    }
    MMP_DBG_INFO(("[MMP][%s %d] ui4_idx = %d, ui4_temp_idx = %d,b_g_use_cache = %d\n",__FUNCTION__,__LINE__,ui4_idx,ui4_temp_idx,b_g_use_cache));

    if (b_g_use_cache)
    {
        for (ui4_i = 0;
             (ui4_i < t_display_item.ui2_item_cnt) && (ui4_i < LBW_CUSTOM_COL_MAX_NUM);
             ui4_i++)
        {
            if (MMP_MEDIA_TYPE_AUDIO == t_display_item.e_media_type)
            {
                if (MMP_LM_AUDIO_COL_ALBUM == ui4_i)
                {
                    c_memcpy(w2s_text,
                             t_g_item_info[ui4_temp_idx].u_extend_info.t_audio.w2s_album,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
                else if (MMP_LM_AUDIO_COL_ARTIST == ui4_i)
                {
                    c_memcpy(w2s_text,
                             t_g_item_info[ui4_temp_idx].u_extend_info.t_audio.w2s_artist,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
                else if (MMP_LM_AUDIO_COL_DUEATION == ui4_i)
                {
                    c_memcpy(w2s_text,
                             t_g_item_info[ui4_temp_idx].u_extend_info.t_audio.w2s_duration,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
            }
            else if (MMP_MEDIA_TYPE_VIDEO == t_display_item.e_media_type)
            {
                if (MMP_LM_VIDEO_COL_DATE == ui4_i)
                {
                    c_memcpy(w2s_text,
                             t_g_item_info[ui4_temp_idx].u_extend_info.t_video.w2s_date,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
                else if (MMP_LM_VIDEO_COL_DURATION == ui4_i)
                {
                    c_memcpy(w2s_text,
                             t_g_item_info[ui4_temp_idx].u_extend_info.t_video.w2s_duration,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
            }

            mmp_lm_fill_listbox_item_txt(pt_drp,
                                         ui4_idx,
                                         ui4_i + LM_FILE_LB_FIX_COL_NUM,
                                         w2s_text,
                                         (UINT16)c_uc_w2s_strlen(w2s_text));
        }
    }
    else
    {
        for (ui4_i = 0; (ui4_i < t_display_item.ui2_item_cnt) && (ui4_i < LBW_CUSTOM_COL_MAX_NUM); ui4_i++)
        {
            t_size = sizeof(w2s_text);
            c_memset(w2s_text,0,sizeof(w2s_text));
            MMPR_LOG_ON_FAIL(t_display_item.at_item_cfg[ui4_i].pf_item_get_info(ui4_idx,
                                                                                w2s_text,
                                                                                &t_size));
            if (MMP_MEDIA_TYPE_AUDIO == t_display_item.e_media_type)
            {
                if (MMP_LM_AUDIO_COL_ALBUM == ui4_i)
                {
                    c_memcpy(t_g_item_info[ui4_temp_idx].u_extend_info.t_audio.w2s_album,
                             w2s_text,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
                else if (MMP_LM_AUDIO_COL_ARTIST == ui4_i)
                {
                    c_memcpy(t_g_item_info[ui4_temp_idx].u_extend_info.t_audio.w2s_artist,
                             w2s_text,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
                else if (MMP_LM_AUDIO_COL_DUEATION == ui4_i)
                {
                    c_memcpy(t_g_item_info[ui4_temp_idx].u_extend_info.t_audio.w2s_duration,
                             w2s_text,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
            }
            else if (MMP_MEDIA_TYPE_VIDEO == t_display_item.e_media_type)
            {
                if (MMP_LM_VIDEO_COL_DATE == ui4_i)
                {
                    //if (0 == c_uc_w2s_strcmp(w2s_text, L"-"))
                    //{
                        c_memset(&t_item_info, 0, sizeof(t_item_info));
                        MMPR_LOG_ON_FAIL( mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                                               ITEM_TYPE_NONE,
                                                               pt_drp->ui4_elem_start,
                                                               &ui4_cnt,
                                                               &t_item_info));
                        //Jundi add for getting the date
                        MMP_DBG_INFO(("[%s %d]pt_drp->ui4_elem_start == %d\n",__FUNCTION__,__LINE__,pt_drp->ui4_elem_start));
                        MMP_DBG_INFO(("[%s %d]t_item_info.s_name == %s, t_item_info.s_name == %s\n",__FUNCTION__,__LINE__,t_item_info.s_parent_name,t_item_info.s_name));
                        c_sprintf(s_full_path,"%s/%s",t_item_info.s_parent_name,t_item_info.s_name);
                        MMP_DBG_INFO(("[%s %d]s_full_path == %s\n",__FUNCTION__,__LINE__,s_full_path));
                        // Get file date
                        MMPR_LOG_ON_FAIL(c_fm_get_info_by_name(NULL_HANDLE, s_full_path, &t_info));

                        c_memset(&t_loc_dtg, 0, sizeof(DTG_T));
                        c_dt_utc_sec_to_loc_dtg(t_info.ui8_create_time, &t_loc_dtg);
                        //c_dt_utc_sec_to_loc_dtg(t_item_info.ui8_create_time, &t_loc_dtg);
                        c_sprintf(sz_info, "%04u-%02u-%02u %02u:%02u:%02u",
                                  t_loc_dtg.ui2_yr, t_loc_dtg.ui1_mo, t_loc_dtg.ui1_day,
                                  t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min, t_loc_dtg.ui1_sec);
                        MMP_DBG_INFO(("[%s %d]sz_info == %s\n",__FUNCTION__,__LINE__,sz_info));

                        c_uc_ps_to_w2s(sz_info, w2s_text, sizeof(w2s_text)/sizeof(UTF16_T));
                    //}

                    c_memcpy(t_g_item_info[ui4_temp_idx].u_extend_info.t_video.w2s_date,
                             w2s_text,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
                else if (MMP_LM_VIDEO_COL_DURATION == ui4_i)
                {
                    c_memcpy(t_g_item_info[ui4_temp_idx].u_extend_info.t_video.w2s_duration,
                             w2s_text,
                             EXTEND_INFO_LENGTH*sizeof(UTF16_T));
                }
            }

            mmp_lm_fill_listbox_item_txt(pt_drp,
                                         ui4_idx,
                                         ui4_i + LM_FILE_LB_FIX_COL_NUM,
                                         w2s_text,
                                         (UINT16)c_uc_w2s_strlen(w2s_text));
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_normal_list_update_custom_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_normal_list_update_custom_info(UINT32        ui4_start,
                                                             UINT32        ui4_end,
                                                             VOID*         pv_elems_data,
                                                             BOOL*         ab_elems_sel)
{
    UINT32 ui4_vp_first,ui4_vp_last;
    UINT32 ui4_page_num = LM_LBW_ELEM_NUM_PER_PAGE;

    IS_MMPR_OK(mmp_listmode_view_get_current_viewreport(&ui4_vp_first,&ui4_vp_last));

    DBG_LOG_PRINT(("[MMP][%s %d] %d in  (%d~%d),load_status = %d ui1_g_loaded_file_num = %d,ui4_page_num = %d\n",
        __FUNCTION__,__LINE__,
        ui4_start,ui4_vp_first,ui4_vp_last,
        mmp_lm_get_load_status(),
        ui1_g_loaded_file_num,
        ui4_page_num));

    MMPR_LOG_ON_FAIL(_mmp_lm_update_item_custom_info(ui4_start,pv_elems_data));

    if(LM_STATUS_LOOP == mmp_lm_get_load_status())
    {
        ui1_g_loaded_file_num ++;
        /*check if we need load the next file info*/
        if(ui4_start == ui4_vp_last)
        {
            DBG_LOG_PRINT(("[MMP][%s %d] ########## load page data end #######\n",__FUNCTION__,__LINE__));
            mmp_lm_set_load_status(LM_STATUS_NORMAL);
            mmp_lm_update_crnt_playing_file();
            mmp_lm_view_update_focus_item_info();
        }
        else if(ui4_start < ui4_vp_last)
             mmp_be_set_focus_item(++ui4_start);
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_list_req_data_cb
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL _mmp_lm_list_req_data_cb(VOID*           pv_tag_req_data,
                                           UINT32          ui4_start,
                                           UINT32          ui4_end,
                                           VOID*           pv_elems_data,
                                           BOOL*           ab_elems_sel,
                                           UINT32*         pui4_num_avail)
{
    MMP_BE_STATUS_T     e_status     = MMP_BE_STATUS_NONE;
    UINT32              ui4_dir_num  = 0;
    UINT32              ui4_file_num = 0;

    if(MMPR_OK != mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS,(VOID*)&e_status))
    {
        DBG_LOG_PRINT(("[MMP][%s %d] get info status failed \n",__FUNCTION__,__LINE__));
        return FALSE;
    }

    if(MMP_BE_STATUS_NORMAL == e_status)
    {
        MMPR_LOG_ON_FAIL(mmp_listmode_view_get_first(&ui4_g_show_start_idx));
        if( MMPR_OK != mmp_be_get_item_num (MMP_BE_FF_IDX_CRT,
                                            &ui4_dir_num,
                                            &ui4_file_num))
        {
            DBG_LOG_PRINT(("[MMP][%s %d] get item num failed\n",__FUNCTION__,__LINE__));
            pui4_num_avail = 0;
            return FALSE;
        }
        /* tell them it get item number*/
        *pui4_num_avail = (ui4_end - ui4_start) + 1 ;

        DBG_LOG_PRINT(("[MMP][%s,%d][%s]ui4_dir_num = %d,ui4_file_num = %d,ui4_start=%d,ui4_end=%d\n",
                     __FUNCTION__, __LINE__,
                     t_g_playlist_crnt.s_curr_path,
                     ui4_dir_num,ui4_file_num,
                     ui4_start, ui4_end));

        if(MMPR_OK != _mmp_lm_normal_list_update_basic_info(ui4_start,
                                                            ui4_end,
                                                            pv_elems_data,
                                                            ab_elems_sel))
        {
            DBG_LOG_PRINT(("[MMP][%s %d] get item basic info failed\n",__FUNCTION__,__LINE__));
            return FALSE;
        }

        /* update page info. */
        mmp_listmode_view_set_page_info(FALSE);
        if(ui4_dir_num > 0)
        {
            if( ui4_file_num == 0 ||  ui4_end <= (ui4_dir_num - 1) )
            {
                mmp_lm_set_load_status(LM_STATUS_NORMAL);
                return TRUE;
            }
            else if(ui4_start <= (ui4_dir_num - 1))
            {
                 mmp_be_set_focus_item(ui4_dir_num);
                 ui1_g_loaded_file_num += ui4_dir_num;
                DBG_LOG_PRINT(("[MMP][%s %d]######## start to load file info#########\n",__FUNCTION__,__LINE__));
                return TRUE;
            }
        }
        else if(ui4_dir_num == 0 && ui4_end != ui4_start && ui4_start == 0)
        {
            mmp_be_set_focus_item(0);
            return TRUE;
        }
        if(MMPR_OK != _mmp_lm_normal_list_update_custom_info(ui4_start,
                                                             ui4_end,
                                                             pv_elems_data,
                                                             ab_elems_sel))
        {
            DBG_LOG_PRINT(("[MMP][%s %d] get item custom info failed\n",__FUNCTION__,__LINE__));
            return FALSE;
        }
    }
    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_bk_player_change_hdlr
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_bk_player_change_hdlr(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    UINT32                  ui4_i = 0;
    UINT32                  ui4_first = 0;
    UINT32                  ui4_last  = 0;
    BOOL                    b_is_found = FALSE;
    MMP_LM_FILE_STATUS_T    e_audio_file_status = MMP_LM_FILE_STATUS_NONE;
    UINT32                  ui4_play_file_idx = 0;
    UINT32                  ui4_dir_num = 0;
    UINT32                  ui4_file_num = 0;
    BOOL                    b_page_change = FALSE;

    i4_ret = mmp_listmode_view_get_first(&ui4_first);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_listmode_view_get_last(&ui4_last);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret =mmp_mc_list_get_idx(MMP_GROUND_MODE_BACK,
                        MMP_PL_IDX_TYPE_CRNT_PLAY,
                        &ui4_play_file_idx);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT,
                                 &ui4_dir_num,
                                 &ui4_file_num);
    MMPR_LOG_ON_FAIL(i4_ret);

    do
    {
        /* get current page's folder number. */
        ui4_dir_num = ui4_dir_num % LM_LBW_ELEM_NUM_PER_PAGE;
        if ((ui4_dir_num+ui4_file_num) <= LM_LBW_ELEM_NUM_PER_PAGE)
        {
            break;
        }

        if ((0 == ui4_first)
            &&(ui4_file_num == (ui4_play_file_idx+1)))
        {
            b_page_change = TRUE;
        }
        else if (((ui4_dir_num+ui4_file_num-1) == ui4_last)
                  &&(0 == ui4_play_file_idx))
        {
            b_page_change = TRUE;
        }
        else if((ui4_dir_num+ui4_play_file_idx-1) == ui4_last)
        {
            b_page_change = TRUE;
        }
        else if ((ui4_dir_num+ui4_play_file_idx+1) == ui4_first)
        {
            b_page_change = TRUE;
        }

        if (b_page_change)
        {
            ui4_g_play_idx = ui4_dir_num+ui4_play_file_idx;
            mmp_lm_set_load_status(LM_STATUS_LOOP);

            i4_ret = mmp_listmode_view_lbw_reload(ui4_dir_num+ui4_file_num,
                                                  ui4_dir_num+ui4_play_file_idx,
                                                  TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);

            return MMPR_OK;
        }
    }while(0);

    for(ui4_i = ui4_first; ui4_i <= ui4_last; ui4_i++)
    {
        i4_ret = mmp_lm_get_file_status_by_idx(ui4_i,
                                               MMP_MEDIA_TYPE_AUDIO,
                                               &e_audio_file_status);
        MMPR_LOG_ON_FAIL(i4_ret);

        if ((MMP_LM_FILE_IS_PLAYING == e_audio_file_status)
            ||(MMP_LM_FILE_IS_PAUSED == e_audio_file_status))
        {
            /* update file info from last select file to page end when file change */

            i4_ret = mmp_listmode_view_lbw_reload_partial(LM_STATUS_LOOP,
                                                          ui4_first,
                                                          ui4_first,
                                                          LBW_RPNT_MODE_PARTIAL_RPNT);
            MMPR_LOG_ON_FAIL(i4_ret);

            ui4_g_play_idx = ui4_i;

            b_is_found = TRUE;
            break;
        }
    }

    /* the playing file is not in the current page. */
    if (!b_is_found)
    {
        ui4_g_play_idx = ui4_dir_num+ui4_play_file_idx;
        i4_ret = mmp_listmode_view_show_focus_file_info();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_bk_player_stop_hdlr
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_bk_player_stop_hdlr(VOID)
{
    INT32   i4_ret = MMPR_OK;

    i4_ret = mmp_listmode_view_show_focus_file_info();
    MMPR_LOG_ON_FAIL(i4_ret);

    ui4_g_play_idx = 0;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_lm_ch_folder
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_ch_folder(UINT32 ui4_hlt_idx)
{
    UTF16_T*                ws_hlt_item_name;

    ws_hlt_item_name = t_g_item_info[ui4_hlt_idx - ui4_g_show_start_idx].ws_name;

    if(c_uc_w2s_strlen(ws_hlt_item_name))
    {
        /*change to farther dir */
        if(0 == c_uc_w2s_strcmp(ws_hlt_item_name, L".."))
        {
            if(!mmp_be_is_root_path())
            {
                MMPR_LOG_ON_FAIL( mmp_be_cd_parent());
            }
        }
        /* change to root path */
        else if(0 == c_uc_w2s_strcmp(ws_hlt_item_name, L"\\"))
        {
            if(mmp_be_is_root_path())
            {
                /* do nothing */
            }
            else
            {
                /* Change to root path  */
                /* TODO */
            }
        }
        /*change to sub dir */
        else
        {
            MMPR_LOG_ON_FAIL(mmp_be_cd_child(ui4_hlt_idx));
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_activate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_activate(UINT32  ui4_idx)
{
    INT32                           i4_ret = MMPR_OK;
    MMP_FP_PREVIEW_INFO_T           t_preview_info = {{0}};
    MMP_MEDIA_TYPE_T   e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
    UINT8   ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR;

    MMP_ASSERT(MMP_MEDIA_TYPE_PHOTO != e_filter_type);

    MMPR_LOG_ON_FAIL( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_filter_type));

    if (MMP_MEDIA_TYPE_AUDIO == e_filter_type)
    {
        ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR;
    }
    else if (MMP_MEDIA_TYPE_VIDEO == e_filter_type)
    {
        ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_VIDEO_BWR;
    }

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
              &ui1_req_op,
              ICL_RECID_MMP_REQUEST_OP_SIZE);

    mmp_lm_set_load_status(LM_STATUS_LOOP);
    mmp_listmode_view_lbw_reload(0,0, TRUE);
    /* Show widget */
    MMPR_LOG_ON_FAIL( mmp_listmode_view_activate());

    /* update the playing file info */
    i4_ret = mmp_listmode_view_set_play_file_info();
    MMPR_LOG_ON_FAIL(i4_ret);
    mmp_mc_list_set_play_present_mode(MMP_FP_PRESENT_MODE_PREVIEW);
    t_preview_info.e_coords = MMP_FP_THUMB_COORDS_CANVAS;
    SET_RECT_BY_SIZE(&t_preview_info.t_preview_rect,
                     LM_FILE_PREVIEW_X,
                     LM_FILE_PREVIEW_Y,
                     LM_FILE_PREVIEW_W,
                     LM_FILE_PREVIEW_H);

    MMPR_LOG_ON_FAIL(mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_PREVIEW_INFO,
                                     (VOID*)&t_preview_info));

    IS_MMPR_OK( mmp_be_activate(MMP_RC_BROWSER_ID_LIST,ui4_idx));

    return MMPR_OK;

}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_inactivate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_inactivate(VOID)
{
    INT32               i4_ret       = MMPR_OK;

    mmp_lm_set_load_status(LM_STATUS_NORMAL);

    i4_ret = mmp_be_inactivate();
    MMPR_LOG_ON_FAIL(i4_ret);

    /* Hide List Mode View */
    i4_ret = mmp_listmode_view_inactivate();
    MMPR_LOG_ON_FAIL(i4_ret);

    c_memset(t_g_item_info,
             0,
             LM_LBW_ELEM_NUM_PER_PAGE*sizeof(MMP_LM_ITEM_INFO_T));
    ui4_g_show_start_idx    = 0;
    c_memset(&t_g_playlist_crnt,0,sizeof(t_g_playlist_crnt));
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_init(VOID)
{
    INT32       i4_ret = MMPR_OK;

    c_memset(&t_g_item_reg_info, 0, sizeof(t_g_item_reg_info));

    i4_ret = mmp_lm_custom_col_register();
    MMPR_LOG_ON_FAIL(i4_ret);

    /* init view */
    i4_ret = mmp_listmode_view_init(_mmp_lm_list_req_data_cb);
    MMPR_LOG_ON_FAIL(i4_ret);
#ifdef CLI_SUPPORT
    i4_ret = mmp_lm_cli_init();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_lm_cli_init() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_deinit(VOID)
{
    /* deinit list mode view */
    mmp_listmode_view_deinit();

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_handle_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_handle_msg(MMP_MSG_ID_T     e_msg_id,
                                              VOID*            pv_msg_param)
{
    INT32           i4_ret = MMPR_OK;
    UINT8           ui1_id = 0;
    BOOL            b_is_show = FALSE;
    BOOL            b_default_hdlr = FALSE;
    MMP_BE_STATUS_T e_status = MMP_BE_STATUS_NONE;
    MMP_PLAY_STATE_T   e_bk_state = MMP_PLAY_STATE_CLOSED;
    MMP_MEDIA_TYPE_T   e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                             (VOID*)&e_filter_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS,
                             (VOID*)&e_status);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* Only process msg when active */
    i4_ret = mmp_mc_browse_get_active(&ui1_id,
                                      &b_is_show);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (ui1_id != MMP_RC_BROWSER_ID_LIST)
    {
        return MMPR_OK;
    }
    //MMP_DBG_INFO(("[mmp] %s %d msg id = %d\n,",__FUNCTION__,__LINE__,e_msg_id));
    switch (e_msg_id)
    {

#ifdef APP_MENU_MMP_COEXIST
        case MMP_MSG_ID_APP_STAT_XNG:
        {
            if (MMP_BE_STATUS_NORMAL == e_status)
            {
                MMP_STAT_XNG_INFO_T* pt_mmp_stat_info = (MMP_STAT_XNG_INFO_T*)pv_msg_param;

                if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == pt_mmp_stat_info->e_mmp_stat_new)
                {
                    i4_ret = mmp_listmode_view_pause_lose_focus();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else if (MMP_MAIN_AP_STATUS_RESUMED == pt_mmp_stat_info->e_mmp_stat_new)

                {
                    i4_ret = mmp_listmode_view_resume_get_focus();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
        }
        break;
#endif

        case MMP_MSG_ID_BROWSE_FILE_INFO_READY:
        {
            if (MMP_MEDIA_TYPE_VIDEO == e_filter_type )
            {
                i4_ret = mmp_listmode_view_set_play_file_info();
                MMPR_LOG_ON_FAIL(i4_ret);
            }

            MMPR_LOG_ON_FAIL(mmp_listmode_view_show_focus_file_info());
        }
            break;

        case MMP_MSG_ID_GUI_LANG_XNG:
        {
            if ((MMP_BE_STATUS_NORMAL == e_status)
                &&((MMP_MEDIA_TYPE_AUDIO == e_filter_type)
                   ||(MMP_MEDIA_TYPE_VIDEO == e_filter_type)))
            {
                mmp_listmode_view_activate();
                mmp_listmode_view_set_page_info(TRUE);
            }
        }
            break;

        case MMP_MSG_ID_BK_PLAYER_STATUS_XNG:
        {
            if ((MMP_BE_STATUS_NORMAL == e_status)
                &&(MMP_MEDIA_TYPE_AUDIO == e_filter_type))
            {
                i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                                &e_bk_state);
                MMPR_LOG_ON_FAIL(i4_ret);

                /* when the STOP key has been pressed, to refresh the item. */
                if (MMP_PLAY_STATE_STOPPING == e_bk_state)
                {
                    i4_ret = mmp_listmode_view_show_focus_file_info();
                    MMPR_LOG_ON_FAIL(i4_ret);
                }

                i4_ret = mmp_listmode_view_set_play_btn_state(e_bk_state);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_BTN_AUDIO_PLAY,
                                             TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
            break;

        case MMP_MSG_ID_AUDIO_PLAYED:
        {
             if(MMPR_OK == mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE,MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_g_play_idx))
             {
                 mmp_lm_update_file_status(ui4_g_play_idx);
             }
        }
            break;
        case MMP_MSG_ID_APP_PAUSED:
        case MMP_MSG_ID_BROWSE_FOLDER_XNG:
        case MMP_MSG_ID_MEDIA_INSERTED:
        case MMP_MSG_ID_MEDIA_REMOVED:

        case MMP_MSG_ID_CUST_SORT_CFG_XNG:
        {
            b_default_hdlr = TRUE;
             break;
        }
        case MMP_MSG_ID_PLAY_FILE_XNG :
        {
            /* back ground audio file changed */
            if (MMP_GROUND_MODE_BACK == (MMP_GROUND_MODE_T)(INT32)pv_msg_param)
            {
                return _mmp_lm_bk_player_change_hdlr();
            }
        }
            break;

        case MMP_MSG_ID_END_OF_PLAYLIST:
        {
            /* back ground audio file stopped */
            if (MMP_GROUND_MODE_BACK == (MMP_GROUND_MODE_T)(INT32)pv_msg_param)
            {
                return _mmp_lm_bk_player_stop_hdlr();
            }
        }
            break;
        case MMP_MSG_ID_CUSTOM_SET_CRNT_PLAY_MODE :
            {
                DBG_LOG_PRINT(("[MMP][%s %d]MMP_MSG_ID_CUSTOM_SET_CRNT_PLAY_MODE \n",__FUNCTION__,__LINE__));
                break;
            }
        case MMP_MSG_ID_CUSTOM_PLAY_NEXT:
            {
                UINT32              ui4_crnt_playing_idx;
                UINT32              ui4_next_playing_idx;
                MMP_MEDIA_TYPE_T    e_media_type;

                IS_MMPR_OK( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type));
                MMPR_LOG_ON_FAIL( mmp_mc_list_get_idx((e_media_type & MMP_MEDIA_TYPE_AUDIO ?  MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE),MMP_PL_IDX_TYPE_NEXT_PLAY,&ui4_next_playing_idx));
                MMPR_LOG_ON_FAIL( mmp_mc_list_get_idx((e_media_type & MMP_MEDIA_TYPE_AUDIO ?  MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE),MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_crnt_playing_idx));

                if(ui4_next_playing_idx != 0)
                    MMPR_LOG_ON_FAIL( mmp_listmode_play_next());
                break;
            }
        default:
        #ifdef APP_CAST_TV_MMP
            b_default_hdlr = TRUE;
        #endif
            break;
    }

    if (b_default_hdlr)
    {
        mmp_be_default_msg_hdlr(e_msg_id, pv_msg_param);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_cmd_do(MMP_FILE_BROWSER_CMD_ID_T    e_cmd_id,
                                  VOID*                        pv_cmd_param)
{
    INT32           i4_ret = MMPR_OK;

    switch (e_cmd_id)
    {
        case MMP_FILE_BROWSER_CMD_ID_ACTIVATE:
        {
            i4_ret = _mmp_listmode_activate((UINT32)pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_FILE_BROWSER_CMD_ID_INACTIVATE:
        {
            i4_ret = _mmp_listmode_inactivate();
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        default:
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_bwr_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_bwr_cmd_do(MMP_BE_BROWSER_CMD_ID_T   e_cmd_id,
                                      VOID*                     pv_cmd_param)
{
    if (MMP_BE_BROWSER_CMD_ID_EXIT_BG_MODE == e_cmd_id)
    {
        return mmp_listmode_view_exit_bg_mode();
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _mmp_listmode_bwr_data_xng
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_listmode_bwr_data_xng(const MMP_BE_UI_INFO_T*    pt_upd_data)
{
#ifdef APP_CAST_TV_MMP
    return MMPR_OK;
#endif
    MMP_BE_UI_UPD_FIELD_T           e_upd_field = pt_upd_data->e_upd_field;
    MMP_DBG_INFO(("[%s %d]e_upd_field == %d\n",__FUNCTION__,__LINE__,e_upd_field));
    MMP_ITEM_TYPE_T         e_item_type = ITEM_TYPE_NONE;
    MMP_MEDIA_TYPE_T        e_media_type = MMP_MEDIA_TYPE_UNKNOWN;


    if(MMP_BE_UI_UPD_FIELD_NO_DEVICE & e_upd_field)
    {
#ifndef APP_CAST_TV_MMP
#ifdef APP_NAV_USB_PLD
        a_nav_active_component(NAV_COMP_ID_USB_PLD);
#endif
#endif
    }

    if (MMP_BE_UI_UPD_FIELD_ITEM_LIST & e_upd_field)
    {
        UINT32    ui4_num_total = 0;
        UINT32   ui4_hlt = 0;

        ui4_num_total = pt_upd_data->ui4_file_num + pt_upd_data->ui4_dir_num;
        ui4_hlt       = pt_upd_data->ui4_focus_idx;
        DBG_LOG_PRINT(("[MMP][%s %d] ui4_dir_num = %d ui4_file_num = %d,ui4_focus_idx = %d\n",
            __FUNCTION__,__LINE__,
            pt_upd_data->ui4_dir_num,
            pt_upd_data->ui4_file_num,
            ui4_hlt));
        /* hide animation */
        MMPR_LOG_ON_FAIL( mmp_listmode_view_hide_animation());

        /* List the items */
        if (0 == pt_upd_data->ui4_dir_num + pt_upd_data->ui4_file_num)
        {
            /* clean the list page */
            MMPR_LOG_ON_FAIL(mmp_listmode_view_lbw_reload(0, 0, TRUE));
            MMPR_LOG_ON_FAIL( mmp_listmode_view_dev_change_focus());
        }
        else
        {
            /* check the item type */
            e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,ui4_hlt);
            DBG_LOG_PRINT(("[MMP][%s %d] ui4_hlt_idx = %d type = %d\n",__FUNCTION__,__LINE__,ui4_hlt,e_item_type));
            if(ITEM_TYPE_DIR != e_item_type)
            {
                MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                             (VOID*)&e_media_type));

                if (MMP_MEDIA_TYPE_VIDEO == e_media_type || MMP_MEDIA_TYPE_AUDIO == e_media_type)
                {
                    ui4_hlt = ui4_g_play_idx;
                }
            }
            mmp_lm_set_load_status(LM_STATUS_LOOP);
            ui4_g_show_start_idx = 0;
            MMPR_LOG_ON_FAIL(mmp_listmode_view_get_first(&ui4_g_show_start_idx));
            //if(0 == pt_upd_data->ui4_dir_num)
            //   MMPR_LOG_ON_FAIL(mmp_be_set_focus_item(ui4_g_show_start_idx));

            /*  reload lbw */
            MMPR_LOG_ON_FAIL( mmp_listmode_view_lbw_reload(ui4_num_total,ui4_hlt,TRUE));
        }
    }

    if (MMP_BE_UI_UPD_FIELD_FOLDER_XNG & e_upd_field)
    {
        c_memset(t_g_item_info,0,LM_LBW_ELEM_NUM_PER_PAGE*sizeof(MMP_LM_ITEM_INFO_T));

    #ifndef APP_CAST_TV_MMP
        /* show animation */
        MMPR_LOG_ON_FAIL(mmp_listmode_view_show_animation());
    #endif

        /* Set current path */
        MMPR_LOG_ON_FAIL( mmp_listmode_view_set_folder_path());
        MMPR_LOG_ON_FAIL(mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_FOLDER_PATH_TXT,TRUE));
        MMPR_LOG_ON_FAIL( mmp_lm_view_repaint(MMP_LM_RC_REPAINT_RECT_ID_FOLDER_NAME,TRUE));
    }

    if (MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO & e_upd_field)
    {
        /* update the playing file info */
        MMPR_LOG_ON_FAIL( mmp_listmode_view_set_play_file_info());
    }

    if (MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT & e_upd_field)
    {
        MMPR_LOG_ON_FAIL(mmp_listmode_view_hide_animation());
    }

    if (MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG & e_upd_field)
    {
        /* system mount device num has been changed */
        MMPR_LOG_ON_FAIL(mmp_listmode_view_dev_num_xng_proc());
    }

    if (MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID & e_upd_field)
    {
        /* active mount device is invalid */
        MMPR_LOG_ON_FAIL(mmp_listmode_view_dev_remove_proc());
    }

    if (MMP_BE_UI_UPD_FIELD_MNT_DEV_XNG & e_upd_field)
    {
        /* active mount device has been changed */
        MMPR_LOG_ON_FAIL(mmp_listmode_view_dev_mnt_xng_proc());
    }

    if(MMP_BE_UI_UPD_FIELD_CRNT_PATH_CHANGE & e_upd_field)
    {
         SIZE_T z_size = MMP_BE_MAX_PATH_LEN;
         MMPR_LOG_ON_FAIL( mmp_be_get_curr_path(t_g_playlist_crnt.s_curr_path, &z_size));
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    a_mmp_listmode_register
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 *---------------------------------------------------------------------------*/
INT32 a_mmp_listmode_register(VOID)
{
    MMP_MC_FILE_BROWSER_PROPERTY_T  t_prop = {0};
    MMP_FILE_BROWSER_INTF_T         t_intf = {0};
    MMP_BE_BROWSER_HDLR_T           t_hdlr = {0};
    MMP_BE_BROWSER_PROPERTY_T       t_be_bwr_prop = {0};
    INT32                           i4_ret;


    t_prop.ui1_id           = MMP_RC_BROWSER_ID_LIST;
    t_intf.pf_init          = _mmp_listmode_init;
    t_intf.pf_deinit        = _mmp_listmode_deinit;
    t_intf.pf_handle_msg    = _mmp_listmode_handle_msg;
    t_intf.pf_cmd_do        = _mmp_listmode_cmd_do;

    t_hdlr.pf_cmd_do        = _mmp_listmode_bwr_cmd_do;
    t_hdlr.pf_data_change   = _mmp_listmode_bwr_data_xng;

    t_be_bwr_prop.ui2_flag  = MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL |
                              MMP_BE_BWR_FLAG_SKIP_MNT_PNT_SEL |
                              MMP_BE_BWR_FLAG_ADD_PARENT_ITEM  |
                              MMP_BE_BWR_FLAG_ENABLE_FILE_PREVIEW;

    t_be_bwr_prop.t_range_info.ui1_col_num = 1;
    t_be_bwr_prop.t_range_info.ui1_row_num = LM_LBW_ELEM_NUM_PER_PAGE;

    i4_ret = mmp_be_reg_brower(&t_intf, &t_prop, &t_hdlr, &t_be_bwr_prop);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_be_reg_brower() failed. i4_ret = %d.\r\n", i4_ret));
    }

    return i4_ret;

}

/*-----------------------------------------------------------------------------
 * Name: mmp_lm_set_load_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 ----------------------------------------------------------------------------*/
VOID mmp_lm_set_load_status(E_MMP_LM_LOAD_STATUS_T e_load_status)
{
    if(LM_STATUS_LAST_ENTRY == e_load_status)
        return ;
    ui1_g_loaded_file_num = LM_STATUS_LOOP == e_load_status ? 0 : LM_LBW_ELEM_NUM_PER_PAGE;
    b_g_use_cache         = LM_STATUS_LOOP == e_load_status ? FALSE : TRUE;
    e_g_load_status       = e_load_status;

    MMP_DBG_INFO(("[MMP][%s %d] e_load_status = %d,ui1_g_loaded_file_num = %d,b_g_use_cache = %d\n",__FUNCTION__,__LINE__,e_load_status,ui1_g_loaded_file_num,b_g_use_cache));
}

/*-----------------------------------------------------------------------------
 * Name: mmp_lm_get_load_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 ----------------------------------------------------------------------------*/
E_MMP_LM_LOAD_STATUS_T mmp_lm_get_load_status(VOID)
{
    return e_g_load_status;
}

/*----------------------------------------------------------------------------
 * Name:    mmp_listmode_media_item_info_register
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_media_item_info_register(LM_DISPLAY_ITEM_REG_T* pt_item)
{
    MMP_LM_ITEM_REG_INFO_T*  pt_this = &t_g_item_reg_info;
    if (!pt_item)
    {
        return MMPR_INV_ARG;
    }

    if (pt_this->ui4_cnt >= LM_MAX_MEIDA_TYPE_CNT)
    {
        return MMPR_OUT_OF_MEM;
    }

    c_memcpy(&pt_this->at_item_reg[pt_this->ui4_cnt], pt_item, sizeof(LM_DISPLAY_ITEM_REG_T));
    pt_this->ui4_cnt++;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    mmp_lm_get_cur_display_item_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_lm_get_cur_display_item_info(LM_DISPLAY_ITEM_REG_T* pt_item)
{
    MMP_MEDIA_TYPE_T         e_media_type = MMP_MEDIA_TYPE_UNKNOWN;
    UINT32                   ui4_i = 0;
    MMP_LM_ITEM_REG_INFO_T*  pt_this = &t_g_item_reg_info;
    if (!pt_item)
    {
        return MMPR_INV_ARG;
    }

    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                    (VOID*)&e_media_type);

    for (ui4_i = 0; ui4_i < pt_this->ui4_cnt; ui4_i++)
    {
        if (e_media_type == pt_this->at_item_reg[ui4_i].e_media_type)
        {
            c_memcpy(pt_item, pt_this->at_item_reg + ui4_i, sizeof(LM_DISPLAY_ITEM_REG_T));
            return MMPR_OK;
        }
    }

    return MMPR_FAIL;
}

static INT32 _mmp_lm_get_current_hlt_file_name(UINT32 ui4_hlt_idx,char** pp_filepath)
{
    MMP_ITEM_INFO_T         t_item_info;
    UINT32                  ui4_cnt = 1;
    INT32                   i4_len;

    mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                  ITEM_TYPE_NONE,
                  ui4_hlt_idx,
                  &ui4_cnt,
                  &t_item_info);
    MMP_DBG_INFO(("[MMP][%s %d] current playing file:%s/%s\n",
    __FUNCTION__,__LINE__,
    t_item_info.s_parent_name,
    t_item_info.s_name));
    i4_len = strlen(t_item_info.s_parent_name) + strlen(t_item_info.s_name) + 2;
    *pp_filepath = (CHAR*)c_mem_alloc(i4_len);
    if(*pp_filepath)
        c_sprintf(*pp_filepath,"%s/%s",t_item_info.s_parent_name,t_item_info.s_name);
    else
        return MMPR_FAIL;
    return MMPR_OK;
}

static INT32 _mmp_reload_play_list()
{
    UINT32            ui4_idx   = 0;
    UINT32            ui4_count = 1;
    CHAR              s_full_path[MMP_BE_MAX_PATH_LEN]={0};
    MMP_ITEM_INFO_T   item;
    SIZE_T            z_size = MMP_BE_MAX_PATH_LEN;
    MMP_MEDIA_TYPE_T  e_media_type;
    UINT32            ui4_playing_idx;

    IS_MMPR_OK( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type));
    MMPR_LOG_ON_FAIL( mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE,MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_playing_idx));

    mmp_lm_update_file_status(ui4_playing_idx);
    mmp_mc_list_remove_all((e_media_type & MMP_MEDIA_TYPE_AUDIO) ? MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE);
    MMPR_LOG_ON_FAIL(mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &t_g_playlist_crnt.ui4_dir_num, &t_g_playlist_crnt.ui4_file_num));
    MMP_DBG_INFO(("[MMP][%s %d] ui4_dir_num = %d, ui4_file_num = %d \n",__FUNCTION__,__LINE__,t_g_playlist_crnt.ui4_dir_num,t_g_playlist_crnt.ui4_file_num));
    if(MMPR_OK == mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &t_g_playlist_crnt.ui4_dir_num, &t_g_playlist_crnt.ui4_file_num) &&
       t_g_playlist_crnt.ui4_file_num > 0 )
    {
        for(;ui4_idx < t_g_playlist_crnt.ui4_file_num;ui4_idx++)
        {
            IS_MMPR_OK(mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                            ITEM_TYPE_FILE,
                                            ui4_idx,
                                            &ui4_count,
                                            &item));

            c_sprintf(s_full_path,"%s/%s",item.s_parent_name,item.s_name);
            MMP_DBG_INFO(("[MMP][%s %d] ui4_idx = %d file[%s]\n",
                            __FUNCTION__,__LINE__,
                            ui4_idx,
                            s_full_path));
            MMPR_LOG_ON_FAIL(mmp_mc_list_add_file(MMP_GROUND_MODE_FORE, s_full_path));
        }
    }

    MMPR_LOG_ON_FAIL( mmp_be_get_curr_path(t_g_playlist_crnt.s_curr_path, &z_size));
    return MMPR_OK;
}
static INT32 _mmp_lm_video_selected(UINT32   ui4_hlt_idx)
{
    INT32                   i4_ret = MMPR_OK;
    MMP_FP_PRESENT_MODE_T   e_present_mode = MMP_FP_PRESENT_MODE_FULL;
    MMP_LM_FILE_STATUS_T    e_video_file_status = MMP_LM_FILE_STATUS_NONE;
    UINT32                  ui4_sel_idx = 0xfffff;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;

    MMPR_LOG_ON_FAIL( mmp_be_get_curr_path(s_curr_path, &z_size));
    MMPR_LOG_ON_FAIL( mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE,MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_sel_idx));
    MMPR_LOG_ON_FAIL( mmp_mc_list_get_play_present_mode(&e_present_mode));

    DBG_LOG_PRINT(("[MMP][%s %d] e_present_mode %d ui4_hlt_idx = %d,playing idx = 0x%x,path=>%s,playing path=>%s\n",
        __FUNCTION__,__LINE__,
        e_present_mode,
        ui4_hlt_idx,
        ui4_sel_idx,
        s_curr_path,
        t_g_playlist_crnt.s_curr_path));
    if( 0 == c_strlen(t_g_playlist_crnt.s_curr_path) ||
        c_strlen(s_curr_path) != c_strlen(t_g_playlist_crnt.s_curr_path) ||
        0 != c_strncmp(t_g_playlist_crnt.s_curr_path,s_curr_path,c_strlen(s_curr_path)))
       {
           _mmp_reload_play_list();
       }
 DBG_LOG_PRINT(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));
    if (MMP_FP_PRESENT_MODE_FULL == e_present_mode)
    {
#ifdef APP_CAST_TV_MMP
        i4_ret = _mmp_lm_ch_folder(ui4_hlt_idx);
        MMPR_LOG_ON_FAIL(i4_ret);
        return i4_ret;
#endif
        if (MMPR_OK != mmp_be_preview_crnt_file(ui4_hlt_idx))
        {
            mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_PLAYER,
                MMP_MSG_ID_VEDIO_FILE_NOT_SUPPORT, NULL);
            return MMPR_OK;
        }

        //MMPR_LOG_ON_FAIL( mmp_lm_reload_current_page());
    }
    else if (MMP_FP_PRESENT_MODE_PREVIEW == e_present_mode)
    {
        MMPR_LOG_ON_FAIL(mmp_lm_get_file_status_by_idx(ui4_hlt_idx,
                                                       MMP_MEDIA_TYPE_VIDEO,
                                                       &e_video_file_status));
        MMP_DBG_INFO(("[MMP][%s %d] e_video_file_status = %d\n",
        __FUNCTION__,__LINE__,
        e_video_file_status));
        if ((MMP_LM_FILE_IS_PLAYING == e_video_file_status) ||
            (MMP_LM_FILE_IS_PAUSED == e_video_file_status))
        {
			_mmp_video_equal_proportion_zoom();
            MMPR_LOG_ON_FAIL(_mmp_lm_ch_folder(ui4_hlt_idx));
            {
                CHAR*  file_path = NULL;
                MMPR_LOG_ON_FAIL( _mmp_lm_get_current_hlt_file_name(ui4_hlt_idx,&file_path));
                DBG_LOG_PRINT(("[MMP][%s %d] file path is %s\n",__FUNCTION__,__LINE__,file_path));
                if(0 == c_strncmp(ptr_g_last_file,file_path,strlen(ptr_g_last_file)))
                    MMPR_LOG_ON_FAIL( mmp_be_stop_preview());
            }
        }
        else
        {
            if (MMPR_OK != (i4_ret = mmp_be_preview_crnt_file(ui4_hlt_idx)))
			{
			    DBG_LOG_PRINT(("[MMP][%s %d] failed to preview current file\n",__FUNCTION__,__LINE__));
				mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_PLAYER,MMP_MSG_ID_VEDIO_FILE_NOT_SUPPORT, NULL);
				return MMPR_OK;
			}
            {
                if(ptr_g_last_file)
                {
                    c_mem_free(ptr_g_last_file);
                }
               MMPR_LOG_ON_FAIL( _mmp_lm_get_current_hlt_file_name(ui4_hlt_idx,&ptr_g_last_file));
               MMP_DBG_INFO(("[MMP][%s %d] current playing file is %s\n",__FUNCTION__,__LINE__,ptr_g_last_file));
            }
        }
      // mmp_lm_reload_current_page();
    }

    ui4_g_play_idx = ui4_hlt_idx;

    return i4_ret;
}

static INT32 _mmp_lm_audio_selected(UINT32   ui4_hlt_idx)
{
    MMP_LM_FILE_STATUS_T  e_audio_file_status = MMP_LM_FILE_STATUS_NONE;
    MMPR_LOG_ON_FAIL(mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &t_g_playlist_crnt.ui4_dir_num, &t_g_playlist_crnt.ui4_file_num));
    MMPR_LOG_ON_FAIL(mmp_lm_get_file_status_by_idx(ui4_hlt_idx,
                                           MMP_MEDIA_TYPE_AUDIO,
                                           &e_audio_file_status));

    if ((MMP_LM_FILE_IS_PLAYING == e_audio_file_status)
        ||(MMP_LM_FILE_IS_PAUSED == e_audio_file_status))
    {
        MMPR_LOG_ON_FAIL( mmp_be_default_key_handle(AUDIO_PLAYER_BTN_PLAY_PAUSE_2,WGL_MSG_KEY_DOWN));
    }
    else
    {
        MMPR_LOG_ON_FAIL(_mmp_lm_ch_folder(ui4_hlt_idx));
    }

    return MMPR_OK;//mmp_lm_reload_current_page();;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_listmode_item_selected
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_listmode_item_selected(UINT32   ui4_hlt_idx)
{
    MMP_ITEM_TYPE_T         e_item_type = ITEM_TYPE_NONE;
    MMP_MEDIA_TYPE_T        e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

    /* check the item type */
    e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,ui4_hlt_idx);
    DBG_LOG_PRINT(("[MMP][%s %d] ui4_hlt_idx = %d type = %d\n",__FUNCTION__,__LINE__,ui4_hlt_idx,e_item_type));

    mmp_lm_set_load_status(LM_STATUS_NORMAL);
    /* change folder */
    if(ITEM_TYPE_DIR == e_item_type)
    {
        MMPR_LOG_ON_FAIL(_mmp_lm_ch_folder(ui4_hlt_idx));
    }
    else
    {
        MMPR_LOG_ON_FAIL(mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                                         (VOID*)&e_media_type));

        if (MMP_MEDIA_TYPE_VIDEO == e_media_type)
        {
            MMPR_LOG_ON_FAIL(_mmp_lm_video_selected(ui4_hlt_idx));
        }
        else if (MMP_MEDIA_TYPE_AUDIO == e_media_type)
        {
            MMPR_LOG_ON_FAIL(_mmp_lm_audio_selected(ui4_hlt_idx));
        }
       //mmp_lm_reload_current_page();
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_lm_get_file_status_by_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns  MMPR_OK         The function executes successfully.
 *          Otherwise       The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_lm_get_file_status_by_idx(UINT32               ui4_sel_idx,
                                          MMP_MEDIA_TYPE_T      e_meida_type,
                                          MMP_LM_FILE_STATUS_T* pe_status)
{
    UINT8                   ui1_browse_id = 0;
    BOOL                    b_is_show = FALSE;
    UINT32                  ui4_sel_in_page = ui4_sel_idx - ui4_g_show_start_idx;
    MMP_PLAY_STATE_T        e_state = MMP_PLAY_STATE_CLOSED;
    CHAR                    s_path_full[MMP_BE_MAX_PATH_LEN] = {0};
    UTF16_T                 ws_tmp[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    CHAR                    s_curr_playing[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_GROUND_MODE_T       e_mode = MMP_GROUND_MODE_BACK;

    *pe_status = MMP_LM_FILE_STATUS_NONE;

    /* 1.  get browser type (listmode & visible ) */
    if(!(MMPR_OK == mmp_mc_browse_get_active(&ui1_browse_id, &b_is_show)&&
       MMP_RC_BROWSER_ID_LIST == ui1_browse_id &&
       ITEM_TYPE_FILE == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,ui4_sel_idx) &&
       (MMP_MEDIA_TYPE_AUDIO == e_meida_type || MMP_MEDIA_TYPE_VIDEO == e_meida_type)))
    {
        MMP_DBG_ERROR(("[MMP][%s,%d] failed to check condition\n", __FUNCTION__, __LINE__));
        return MMPR_FAIL;
    }

    e_mode = (e_meida_type == MMP_MEDIA_TYPE_AUDIO) ? MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE;

    if(!(MMPR_OK == mmp_mc_list_get_idx(e_mode, MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_sel_idx) &&
         MMPR_OK == mmp_mc_list_get_item(e_mode,ui4_sel_idx,&z_size,s_curr_playing)))
    {
        MMP_DBG_ERROR(("[MMP][%s,%d] failed to get current playing file,ui4_sel_idx=%d\n",__FUNCTION__, __LINE__, ui4_sel_idx));
        return MMPR_OK;
    }

    c_uc_w2s_strcat(ws_tmp,t_g_item_info[ui4_sel_in_page].ws_parent_name);
    c_uc_w2s_strcat(ws_tmp,L"/");
    c_uc_w2s_strcat(ws_tmp,t_g_item_info[ui4_sel_in_page].ws_name);
    c_uc_w2s_to_ps(ws_tmp,s_path_full,MMP_BE_MAX_PATH_LEN);
    DBG_LOG_PRINT(("[MMP][%s %d] sel file is %s,playing is %s\n",__FUNCTION__,__LINE__,s_path_full,s_curr_playing));
    if(0 == c_strcmp(s_path_full, s_curr_playing) &&
       MMPR_OK == mmp_mc_file_get_status(e_mode,&e_state))
    {
        MMP_DBG_INFO(("\n%s,%d,e_mode=%d,e_state=%d\n",
                __FUNCTION__, __LINE__,e_mode, e_state));

        if ((MMP_PLAY_STATE_PLAYING         == e_state)||
            (MMP_PLAY_STATE_PLAYED          == e_state)||
            (MMP_PLAY_STATE_FAST_FORWARDING == e_state)||
            (MMP_PLAY_STATE_FAST_FORWARDED  == e_state)||
            (MMP_PLAY_STATE_FAST_REWINDING  == e_state)||
            (MMP_PLAY_STATE_FAST_REWINDED   == e_state)||
            (MMP_PLAY_STATE_SLOW_FORWARDING == e_state)||
            (MMP_PLAY_STATE_SLOW_FORWARDED  == e_state)||
            (MMP_PLAY_STATE_VIEW_NEXTING  == e_state))
        {
            *pe_status = MMP_LM_FILE_IS_PLAYING;
            return MMPR_OK;
        }
        else if ((MMP_PLAY_STATE_PAUSING == e_state)
            ||(MMP_PLAY_STATE_PAUSED == e_state))
        {
            *pe_status = MMP_LM_FILE_IS_PAUSED;
            return MMPR_OK;
        }
    }

    *pe_status = MMP_LM_FILE_STATUS_NONE;
    return MMPR_OK;
}

#ifdef APP_TTS_SUPPORT
UTF16_T* mmp_lm_get_file_name_by_idx(UINT32  ui4_sel_idx)
{
    if((ui4_sel_idx > LM_LBW_ELEM_NUM_PER_PAGE - 1) ||
       0 == c_uc_w2s_strlen(t_g_item_info[ui4_sel_idx].ws_name)||
       0 == c_uc_w2s_strcmp(t_g_item_info[ui4_sel_idx].ws_name,L"..")||
       0 == c_uc_w2s_strcmp(t_g_item_info[ui4_sel_idx].ws_name,L"\\"))
    {
        MMP_DBG_ERROR(("idx out of range. idx = %d.\r\n", ui4_sel_idx));
        return L"";
    }

    return t_g_item_info[ui4_sel_idx].ws_name;
}
#endif

VOID mmp_lm_update_file_status(UINT32 ui4_file_idx)
{
    if(MMPR_OK == mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &t_g_playlist_crnt.ui4_dir_num, &t_g_playlist_crnt.ui4_file_num) &&
       t_g_playlist_crnt.ui4_file_num > 0)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] argv = 0x%x ui4_g_total_dir_count = %d\n",__FUNCTION__,__LINE__,ui4_file_idx,t_g_playlist_crnt.ui4_dir_num));
        ui4_file_idx += t_g_playlist_crnt.ui4_dir_num;
        if(LM_STATUS_NORMAL == mmp_lm_get_load_status())
            MMPR_LOG_ON_FAIL(mmp_listmode_update_item_status(ui4_file_idx));
    }
}

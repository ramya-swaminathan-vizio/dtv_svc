/*----------------------------------------------------------------------------*
o * Copyright Statement:                                                       *
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
 * $RCSfile:  $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "mmp_browse_eng.h"
#include "amb/a_amb.h"
#include "mmp/a_mmp.h"
#include "mmp/disp_res_ctrler/mmp_drc.h"
#ifdef MMP_FILE_OP_SUPPORT
#include "mmp/file_operator_list/mmp_file_operator_list.h"
#include "mmp/file_operator/mmp_file_operator.h"
#endif

#include "c_dbg.h"

#include "res/nav/nav_variant.h"
#include "am/a_am.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "res/app_util/config/acfg_cust_mmp.h"
#include "res/app_util/model/model.h"
#include MMP_MLM_HEADER_FILE
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/banner2/banner_rc.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "rest/tv/tv_settings/a_picture_ex.h"
#endif
#include "nav/vol_ctrl/a_vol_ctrl.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "nav/banner2/a_banner.h"
#endif

#include "nav/banner2/banner.h"
#include "mmp/foreground/mmp_foreground.h"
#include "menu2/a_menu.h"
#include "mmp/playlist/mmp_lst_eng.h"
#include "mmp/playlist/_mmp_lst_eng.h"
#include "res/app_util/config/a_cfg_custom.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

      
#define DBG_INFO_DIRECT(fmt, args...) \
	do{																		\
		if(0)																\
		{																	\
			fprintf(stderr,fmt,##args );									\
			fflush(stderr);													\
		}																	\
		else																\
		{																	\
			MMP_DBG_INFO((fmt, args));										\
		}																	\
	}while(0)																\




/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct _MMP_BE_FF_INST_T
{
    CHAR                s_pname[MMP_BE_MAX_PATH_LEN];
    UINT8               ui1_ff_id;
    BOOL                b_traverse_done;
    UINT32              ui4_traverse_depth;
    /*BOOL                b_read_only;*/
} MMP_BE_FF_INST_T;

/*File filter index*/
#define _MMP_BE_FF_INST_IDX_T           UINT8
#define _MMP_BE_FF_INST_IDX_0           ((_MMP_BE_FF_INST_IDX_T) 0)
#define _MMP_BE_FF_INST_IDX_1           ((_MMP_BE_FF_INST_IDX_T) 1)
#define _MMP_BE_FF_INST_IDX_BK          ((_MMP_BE_FF_INST_IDX_T) 2)
#define _MMP_BE_FF_INST_IDX_CNT         ((_MMP_BE_FF_INST_IDX_T) 3)

#define _MMP_BE_MNT_POINT_MAX_PATH_LEN  (50)

typedef struct _MMP_BE_BROWSER_T
{
    MMP_BE_BROWSER_HDLR_T       t_bwr_hdlr;
    MMP_BE_BROWSER_PROPERTY_T   t_bwr_prop;
} MMP_BE_BROWSER_T;

typedef enum _MMP_BE_TIMER_ID_T
{
    MMP_BE_TIMER_ID_PARSING_ITEM,
    MMP_BE_TIMER_ID_FILE_PREVEW,
    MMP_BE_TIMER_ID_CB_CHECK,
    MMP_BE_TIMER_ID_COUNT
} MMP_BE_TIMER_ID_T;

typedef enum _MMP_BE_TIMER_STATUS
{
    MMP_BE_TIMER_STATUS_NONE = 0,
    MMP_BE_TIMER_STATUS_LISTEN,
    MMP_BE_TIMER_STATUS_EXPIRED
} MMP_BE_TIMER_STATUS;

typedef struct _MMP_BE_DATA_MEMBER_T
{
    MMP_BE_BROWSER_T    at_browser[MMP_MC_RC_FILE_BROWSER_MAX_COUNT];
    MMP_BE_BROWSER_T*   pt_act_bwr;
    UINT8               ui1_act_bwr_id;
    MMP_BE_STATUS_T     e_status;
    MMP_BE_FF_INST_T    at_ff_inst[_MMP_BE_FF_INST_IDX_CNT];
    _MMP_BE_FF_INST_IDX_T   e_crt_inst_idx;
    CHAR                s_curr_path[MMP_BE_MAX_PATH_LEN];
    CHAR                s_curr_focus_path[MMP_BE_MAX_PATH_LEN];
    mmp_func_filter_fct pf_filter_fct;
    UINT32              ui4_focus_item_idx;
    UINT32              ui4_focus_file_idx;
    MMP_SORT_TYPE_T     e_sort;
    MMP_MEDIA_TYPE_T    e_filter_type;

    UINT32              ui4_traverse_depth;
    UINT32              ui4_traverse_history[MMP_RC_MAX_FOLDER_DEPTH]; /*default value of each item is 0xFFFFFFFF)*/
    MMP_FB_MODE         e_fb_mode;
    BOOL                b_recursive_read;
    mmp_sort_status_nfy pf_sort_status_nfy;
    BOOL                b_playlist_only;
    UINT8               ui1_vp_row_num;
    UINT8               ui1_vp_col_num;
    UINT8               ui1_video_play_mode;
    BOOL                b_add_parent;

    HANDLE_T            ah_timer[MMP_BE_TIMER_ID_COUNT];
    MMP_BE_TIMER_STATUS ae_timer_status[MMP_BE_TIMER_ID_COUNT];
    UINT32              aui4_timer_delay[MMP_BE_TIMER_ID_COUNT];

    MMP_BE_UI_INFO_T    t_last_notify;
    MMP_MEDIA_TYPE_T    e_preview_type;
    MMP_FP_PREVIEW_INFO_T t_preview_info;
    MMP_FF_SET_PATH_FLAG_T  e_set_path_flag;
    UINT32              ui4_preview_item_idx;
    HANDLE_T            h_transparent_list;

#ifdef APP_CAST_TV_MMP
    BOOL                b_is_exit_cast;
#endif
    BOOL                b_need_reload_playlist;
    RMV_DEV_CUSTOM_CURRENT_STATUS_T e_rmv_dev_current_status;
    RMV_DEV_CUSTOM_CURRENT_STATUS_T e_rmv_dev_previous_status;
} MMP_BE_DATA_MEMBER_T;


/*-----------------------------------------------------------------------------
 * customization declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static MMP_BE_DATA_MEMBER_T t_g_browse_eng;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_be_ff_cb_fct(UINT32 ui4_cur_dir_num,
                               UINT32 ui4_cur_file_num,
                               MMP_FF_PARSE_STATUS_T e_status,
                               VOID* pv_param);
static INT32 _mmp_be_set_path(MMP_BE_FF_INST_T* pt_inst, CHAR* ps_pname);
INT32 mmp_be_set_curr_path(CHAR* ps_pname);
static INT32 _mmp_be_set_traverse_done(MMP_BE_FF_INST_T* pt_inst, BOOL b_done);
static INT32 _mmp_be_reset(VOID);
static INT32 _mmp_be_clone_ff_inst(MMP_BE_FF_INST_T* pt_inst_to, MMP_BE_FF_INST_T* pt_inst_from);
static INT32 _mmp_be_act_dev_invalid_handler(MMP_BE_DATA_MEMBER_T* pt_this);
static INT32 _mmp_be_choose_media_type(MMP_BE_DATA_MEMBER_T* pt_this);
static INT32 _mmp_be_choose_mnt_pnt(MMP_BE_DATA_MEMBER_T* pt_this);
static INT32 _mmp_be_get_item_list(MMP_BE_DATA_MEMBER_T* pt_this,
                                   MMP_BE_FF_INST_T* pt_inst,
                                   CHAR* s_curr_path);
static INT32 _mmp_be_reload_data(MMP_BE_DATA_MEMBER_T* pt_this,
                                 MMP_BE_FF_INST_T* pt_inst,
                                 UINT32 ui4_dir_num,
                                 UINT32 ui4_file_num);
static INT32 _mmp_be_is_mnt_state_avail(MMP_BE_DATA_MEMBER_T* pt_this,
                                        UINT32* pui4_count,
                                        BOOL* pb_is_avail);
static INT32 _mmp_be_get_ff_inst_by_idx(MMP_BE_DATA_MEMBER_T* pt_this,
                                        MMP_BE_FF_IDX e_ff_idx,
                                        MMP_BE_FF_INST_T** ppt_inst);
static INT32 _mmp_be_play_crnt_folder(MMP_BE_DATA_MEMBER_T* pt_this,
                                      UINT32 ui4_focus_idx,
                                      BOOL   b_is_active_op,
                                      BOOL b_view_only);
static INT32 _mmp_be_bk_player_stop_hdlr(MMP_BE_DATA_MEMBER_T* pt_this);
static INT32 _mmp_be_clean_all_traverse_done(VOID);
static VOID _mmp_be_traverse_done_stack_push (UINT32 ui4_user_sel);
static UINT32 _mmp_be_traverse_done_stack_pop (VOID);
static VOID _mmp_be_traverse_done_stack_reset (VOID);
static INT32 _mmp_be_reset_timer(MMP_BE_DATA_MEMBER_T* pt_this,
                                 MMP_BE_TIMER_ID_T e_id,
                                 BOOL b_stop);

static VOID _mmp_be_timer_nfy(HANDLE_T h_timer, VOID* pv_tag);

static VOID _mmp_be_do_timer_nfy(VOID* pv_param1,
                                            VOID* pv_param2,
                                            VOID* pv_param3,
                                            VOID* pv_param4);
static INT32 _mmp_be_stop_preview(MMP_BE_DATA_MEMBER_T* pt_this);

#ifdef MMP_FILE_OP_SUPPORT
static INT32 _mmp_be_enter_bg_mode(VOID);
static INT32 _mmp_be_exit_bg_mode(VOID);
#endif

static INT32 _mmp_be_select_file(MMP_BE_FF_IDX e_ff_idx, UINT32 ui4_file_idx);
static INT32 _mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_T e_list_type,
                                   MMP_BE_FF_IDX e_ff_idx,
                                   UINT32 ui4_file_idx,
                                   BOOL* pb_exists);
//static INT32 _mmp_be_clone_to_copy_list(MMP_BE_FF_IDX e_ff_idx);

//static VOID _mmp_be_fo_nfy_cb(MMP_FO_MSG_ID_T e_msg_id, VOID* pv_param);
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
static VOID _mmp_be_locked_inp_hdlr(VOID* pv_param1,
                                    VOID* pv_param2,
                                    VOID* pv_param3,
                                    VOID* pv_param4);
#endif
static INT32 _mmp_be_upd_res_mode(MMP_BE_DATA_MEMBER_T* pt_this);
static UINT32 _mmp_be_get_media_type_count(VOID);
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

#ifdef APP_CAST_TV_MMP
/*---------------------------------------------------------------------------*/
/**
* @brief   _mmp_be_c4tv_apron_custom_nfy
* @param
* @retval
* @retval
*/
/*---------------------------------------------------------------------------*/

static VOID _mmp_be_c4tv_apron_custom_nfy(
                        VOID*   pv_param1,
                        VOID*   pv_param2,
                        VOID*   pv_param3)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;

    if ((MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type) &&
        (TRUE == pt_this->b_is_exit_cast))
    {
        mmp_be_cd_child(0);
    }
    return;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_chg_inp_src_to_cast
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_chg_inp_src_to_cast(VOID)
{
    ISL_REC_T       t_isl_rec = {0};
    INT32           i4_ret = 0;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_HOME;
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;

    /*change to cast */
    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if (APP_CFGR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }

        if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
        {
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }
    /*If retail mode, exit it */
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        DBG_LOG_PRINT(("mmp be exit retail mode %s,%d\n\r",__FILE__,__LINE__));
        a_nav_retail_mode_exit_from_mmp(_mmp_be_c4tv_apron_custom_nfy);
        a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
        pt_this->b_is_exit_cast = TRUE;
        //a_c4tv_apron_sync_exit_cast();
    }
    else if(ACFG_RETAIL_MODE_HOME == t_retail_mode)
    {
        if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
        {
            DBG_LOG_PRINT(("mmp be exit cast resource %s,%d\n\r",__FILE__,__LINE__));
            a_c4tv_apron_sync_exit_cast();
        }
    }
    return MMPR_OK;
}
#endif

static VOID _mmp_playlist_reflash(VOID*      pv_tag1,
                                     VOID*      pv_tag2,
                                     VOID*      pv_tag3,
                                     VOID*      pv_tag4)
{
    UINT32                      ui4_cur_file_num,ui4_cur_dir_num;
    MMP_BE_DATA_MEMBER_T*       pt_this          = &t_g_browse_eng;

    if(pt_this->b_need_reload_playlist &&
       MMPR_OK ==  mmp_be_get_item_num(MMP_BE_FF_IDX_CRT,&ui4_cur_dir_num,&ui4_cur_file_num) &&
       ui4_cur_file_num > 0 )
    {
#if 0
         MMP_ITEM_INFO_T*       items;
         UINT32                 ui4_start = 0;

        DBG_LOG_PRINT(("[MMP][%s %d][%s]ui4_file_num = %d\n",__FUNCTION__,__LINE__,pt_this->s_curr_path,ui4_cur_file_num));

        items = (MMP_ITEM_INFO_T*)c_mem_alloc(sizeof(MMP_ITEM_INFO_T) * ui4_cur_file_num);

        if(items && MMPR_OK == mmp_ff_get_item_info(pt_this->at_ff_inst[pt_this->e_crt_inst_idx].ui1_ff_id,
                                                    ITEM_TYPE_FILE,
                                                    ui4_start,
                                                    &ui4_cur_file_num,
                                                    items))
        {
            mmp_lst_eng_item_update((items[0].e_flag & MMP_FF_ITEM_FLAG_MEDIA_TYPE_VIDEO) > 0 ? MMP_GROUND_MODE_FORE : MMP_GROUND_MODE_BACK,items,ui4_cur_file_num);
        }
        if(items)
           c_mem_free(items);
#else
        UINT32                              ui4_idx = 0;
        MMP_ITEM_INFO_T                     items;
        _MMP_LST_ENG_PLAY_INST_T*           pt_this_obj;
        UINT32                              ui4_count = 1;
        INT32                               i4_ret;
        CHAR                                s_full_path[MMP_BE_MAX_PATH_LEN]={0};
        MMP_MEDIA_TYPE_T                    e_media_type;
        CHAR                                sz_crnt_playing[MMP_RC_PATH_MAX_LEN * sizeof(CHAR) + 1] = {0};
        SIZE_T                              z_max_size = MMP_RC_PATH_MAX_LEN * sizeof(CHAR);
        MMP_GROUND_MODE_T                   e_mode;
        UINT32                              ui4_last_file = _MMP_LST_ENG_INV_FILE_IDX;

        DBG_LOG_PRINT(("[MMP][%s %d][%s]ui4_file_num = %d\n",__FUNCTION__,__LINE__,pt_this->s_curr_path,ui4_cur_file_num));

        IS_MMPR_OK(mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                        ITEM_TYPE_FILE,
                                        ui4_idx,
                                        &ui4_count,
                                        &items));

        e_mode = (items.e_flag & MMP_FF_ITEM_FLAG_MEDIA_TYPE_AUDIO) > 0 ? MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE;


        /*get active list instance*/
        i4_ret = mmp_mc_list_get_select(NULL, (VOID**)&pt_this_obj);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("[MMP][%s %d] mmp_mc_list_get_select() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret));
        }

        /*get filename*/
        if(MMPR_OK != (i4_ret = mmp_lst_eng_item_get(pt_this_obj,
                                                    e_mode,
                                                    pt_this_obj->t_ground[e_mode ==  MMP_GROUND_MODE_FORE ?  _MMP_LST_ENG_GROUND_IDX_FG : _MMP_LST_ENG_GROUND_IDX_BK].ui4_crnt_file,
                                                    &z_max_size,
                                                    sz_crnt_playing)))
        {
            MMP_DBG_ERROR(("[MMP][%s %d] mmp_mc_list_get_select() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret));
        }


        /*update item one by one*/
        IS_MMPR_OK( mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,(VOID*)&e_media_type));
        mmp_mc_list_remove_all((e_media_type & MMP_MEDIA_TYPE_AUDIO) ? MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE);
        for(ui4_idx = 0; ui4_idx < ui4_cur_file_num; ui4_idx++)
        {
            IS_MMPR_OK(mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                            ITEM_TYPE_FILE,
                                            ui4_idx,
                                            &ui4_count,
                                            &items));

            c_sprintf(s_full_path,"%s/%s",items.s_parent_name,items.s_name);
            /*
            MP_DBG_INFO(("[MMP][%s %d] ui4_idx = %d file[%s]\n",
                        _FUNCTION__,__LINE__,
                        i4_idx,
                        _full_path));
            */
            MMPR_LOG_ON_FAIL(mmp_mc_list_add_file((e_media_type & MMP_MEDIA_TYPE_AUDIO) ? MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE, s_full_path));
            //DBG_LOG_PRINT(("[MMP][%s %d] file [%d]%s ##!\n",__FUNCTION__,__LINE__,ui4_idx,s_full_path));

            if(0 == c_strcmp(sz_crnt_playing,s_full_path))
            {
                ui4_last_file = ui4_idx;
            }

        }
        /*save the crnt_file's index and the next_file's index*/
        if(MMP_GROUND_MODE_FORE == e_mode)
        {
            pt_this_obj->t_ground[_MMP_LST_ENG_GROUND_IDX_FG].ui4_crnt_file = ui4_last_file;
            pt_this_obj->t_ground[_MMP_LST_ENG_GROUND_IDX_FG].ui4_next_file = ui4_last_file + 1;
        }
        else
        {
            pt_this_obj->t_ground[_MMP_LST_ENG_GROUND_IDX_BK].ui4_crnt_file = ui4_last_file;
            pt_this_obj->t_ground[_MMP_LST_ENG_GROUND_IDX_BK].ui4_next_file = ui4_last_file + 1;
        }
        /*update the selected item's status*/
        //mmp_lm_update_file_status(ui4_last_file);
        mmp_lm_update_file_status(0);
#endif
    }
    else
    {
        MMP_DBG_ERROR(("[MMP][ %s %s %d] reflash  failed \n",__FILE__,__FUNCTION__,__LINE__));
    }
    pt_this->b_need_reload_playlist = FALSE;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_ff_cb_fct
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_ff_cb_fct(UINT32 ui4_cur_dir_num,
                               UINT32 ui4_cur_file_num,
                               MMP_FF_PARSE_STATUS_T e_status,
                               VOID* pv_param)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;
    MMP_BE_FF_INST_T*           pt_inst = (MMP_BE_FF_INST_T*)pv_param;
    INT32                       i4_ret;
    MMP_BE_FILE_SRC_TYPE_T      e_src_type = MMP_BE_FILE_SRC_UNKNOWN;

    if((pt_this->e_status == MMP_BE_STATUS_CHOOSE_FF) ||
       (pt_this->e_status == MMP_BE_STATUS_CHOOSE_MNT)||
       (pt_inst->ui4_traverse_depth != pt_this->ui4_traverse_depth))
    {
        /* if it have left  the current folder, when traverse done this folder, don't loading thumbnail  */
        MMP_DBG_INFO(( "[mmp] %s %d Current status is %d \n,"
                    "pt_inst->ui4_traverse_depth=%d,"
                    "pt_this->ui4_traverse_depth=%d",
                    __FUNCTION__,__LINE__,
                    pt_this->e_status,
                    pt_inst->ui4_traverse_depth,
                    pt_this->ui4_traverse_depth));
        /* Parsing over Stop timer */
        _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_CB_CHECK, TRUE);

        return MMPR_OK;
    }

    if (MMP_FF_PARSE_STATUS_DONE == e_status)
    {
        MMP_DBG_INFO(("[mmp] %s %d return from file filter MMP_FF_PARSE_STATUS_DONE "
                      "ui4_cur_dir_num=%d, ui4_cur_file_num=%d\n",
                      __FUNCTION__,__LINE__,
                      ui4_cur_dir_num,
                      ui4_cur_file_num));

        #ifdef APP_CAST_TV_MMP
            TV_WIN_ID_T     e_focus_id = TV_WIN_ID_MAIN;
            ISL_REC_T       t_last_isl_rec = {0};
             /*save currt source*/
            a_tv_get_focus_win(&e_focus_id);
            i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_last_isl_rec);
            if(TVR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("a_tv_get_isl_rec_by_win_id() failed. i4_ret = %d.\r\n", i4_ret));
            }
            mmp_main_set_last_isl_rec(&t_last_isl_rec);
            if(ui4_cur_file_num == 0)
            {
                a_mmp_set_is_parse_null_ff_state(TRUE);
                SIZE_T  z_size = ICL_RECID_MMP_DISABLE_MASK_SIZE;
                UINT32  ui4_disable_mask = 0;

                i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_DISABLE_MASK),
                                   &ui4_disable_mask,
                                   &z_size);

                if(ui4_disable_mask == 8)  //c4tv_apron  init set  0 | ICL_RECID_MMP_DISABLE_MASK_CAST_TV
                {
                    ui4_disable_mask = 0;
                    i4_ret = a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_DISABLE_MASK),
                                       &ui4_disable_mask,
                                       z_size);
                }

                UINT8   ui1_resume_cond = ICL_RECID_MMP_RESUME_COND_FAILED;
                z_size = ICL_RECID_MMP_RESUME_COND_SIZE;

                a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_RESUME_COND),
                            &ui1_resume_cond,
                            z_size);
                a_amb_clean_stack();
                return a_amb_pause_app(MMP_NAME);
            }
            else
            {
                a_mmp_set_is_parse_null_ff_state(FALSE);

                /*if no cast ,change to cast && exit cast resource*/
                _mmp_chg_inp_src_to_cast();

                a_rest_set_test_patterns_turn_off();

                UINT8   ui1_resume_cond = ICL_RECID_MMP_RESUME_COND_OK;
                SIZE_T  z_size = ICL_RECID_MMP_RESUME_COND_SIZE;

                a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_RESUME_COND),
                            &ui1_resume_cond,
                            z_size);

                mmp_main_free_video_resource();
                /*add for info banner will pop up when insert USB to play mp4 file automatically*/
                a_nav_show_banner_ex();
            }
        #endif

        /* Parsing over Stop timer */
        _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_CB_CHECK, TRUE);

        _mmp_be_set_traverse_done(pt_inst, TRUE);
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_playlist_reflash,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
        return _mmp_be_reload_data(pt_this, pt_inst, ui4_cur_dir_num, ui4_cur_file_num);
    }
    else if (MMP_FF_PARSE_STATUS_ERROR == e_status)
    {
        MMP_DBG_INFO(("[mmp] %s %d return from file filter MMP_FF_PARSE_STATUS_ERROR\n",__FUNCTION__,__LINE__));
        /* Parsing over Stop timer */
        _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_CB_CHECK, TRUE);

        _mmp_be_set_traverse_done(pt_inst, TRUE);
        return _mmp_be_reload_data(pt_this, pt_inst, 0, 0);
    }
    
    /* Parsing case */
    MMP_DBG_INFO(("[mmp] %s %d return from file filter MMP_FF_PARSE_STATUS_PARSING "
                  "ui4_cur_dir_num=%d, ui4_cur_file_num=%d\n",__FUNCTION__,__LINE__,
                  ui4_cur_dir_num,
                  ui4_cur_file_num));

    /* reset timer again */
    _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_CB_CHECK, FALSE);

    pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PARSE_STATUS_UPD;
    pt_this->t_last_notify.e_parse_status = e_status;
    pt_this->t_last_notify.ui4_dir_num = ui4_cur_dir_num;
    pt_this->t_last_notify.ui4_file_num = ui4_cur_file_num;
    pt_this->t_last_notify.ui4_focus_idx = pt_this->ui4_focus_item_idx;


    /* if it's dlna, it'll show the first page, so not stop parsing timer */
    if(pt_this->ae_timer_status[MMP_BE_TIMER_ID_PARSING_ITEM] == MMP_BE_TIMER_STATUS_LISTEN)
    {
        i4_ret = mmp_be_get_file_src_type (pt_this->s_curr_path, &e_src_type);
        if (MMPR_OK == i4_ret && MMP_BE_FILE_SRC_DLNA == e_src_type)
        {
            /* List items, this notify is send when browse_eng begin load items or show empty message */
            _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, TRUE);
        }
    }


    pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_set_path
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_set_path(MMP_BE_FF_INST_T* pt_inst, CHAR* ps_pname)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;
    MMP_FF_SET_PATH_PARAM_T     t_param;
    INT32                       i4_ret;
#ifdef APP_NETWORK_SUPPORT
    MMP_BE_FILE_SRC_TYPE_T      e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    i4_ret =  mmp_be_get_file_src_type(ps_pname, &e_src_type);
    MMPR_LOG_ON_FAIL(i4_ret);
#endif

    if ((ps_pname == NULL) || (c_strlen(ps_pname) >= MMP_BE_MAX_PATH_LEN))
    {
        return MMPR_INV_ARG;
    }

    c_memset(&t_param, 0, sizeof(MMP_FF_SET_PATH_PARAM_T));

    c_strcpy(pt_inst->s_pname, ps_pname);
    pt_inst->b_traverse_done    = FALSE;
    pt_inst->ui4_traverse_depth = pt_this->ui4_traverse_depth;

    t_param.ps_dir_name         = MMP_BE_IS_EMPTY_PATH(ps_pname) ? NULL : ps_pname;
    t_param.pf_filter_fct       = pt_this->pf_filter_fct;
    t_param.pf_ff_cb_fct        = _mmp_be_ff_cb_fct;
    t_param.pv_tag              = (VOID*)pt_inst;
    t_param.b_force_flush       = TRUE;
    t_param.b_add_parent        = pt_this->b_add_parent;
    t_param.ui1_row_num         = pt_this->ui1_vp_row_num;
    t_param.ui1_col_num         = pt_this->ui1_vp_col_num;
    t_param.pf_sort_status_nfy  = pt_this->pf_sort_status_nfy;
    t_param.b_playlist_only     = pt_this->b_playlist_only;

#ifdef APP_NETWORK_SUPPORT
    if((e_src_type == MMP_BE_FILE_SRC_DLNA) ||
       (e_src_type == MMP_BE_FILE_SRC_NET_NEIGHBOR))
    {
        t_param.e_sort              = MMP_SORT_TYPE_NONE;
        t_param.b_recursive         = FALSE;
    }
    else
    {
        t_param.b_recursive         = pt_this->b_recursive_read;
        t_param.e_sort              = pt_this->e_sort;
    }
#else
    t_param.b_recursive         = pt_this->b_recursive_read;
    t_param.e_sort              = pt_this->e_sort;
#endif

    t_param.e_set_path_flag     = pt_this->e_set_path_flag;

    i4_ret = mmp_ff_set_path_ex(pt_inst->ui1_ff_id,&t_param);
    if(i4_ret != MMPR_OK)
    {
        _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, TRUE);

        /* mmp_ff_set_path_ex fail printf inputs t_param */
        DBG_LOG_PRINT(("fb call mmp_ff_set_path_ex i4_ret=%d\n t_param.ps_dir_name=%s\n t_param.e_sort=%d\n t_param.b_force_flush=%d\n",
                    i4_ret,
                    t_param.ps_dir_name,
                    t_param.e_sort,
                    t_param.b_force_flush));
        DBG_LOG_PRINT(("t_param.b_add_parent=%d\n t_param.ui1_row_num=%d\n t_param.ui1_col_num=%d\n t_param.pf_sort_status_nfy=%d\n",
                    t_param.b_add_parent,
                    t_param.ui1_row_num,
                    t_param.ui1_col_num,
                    t_param.pf_sort_status_nfy));
        DBG_LOG_PRINT(("t_param.b_recursive=%d\n t_param.b_playlist_only=%d\n",
                    t_param.b_recursive,
                    t_param.b_playlist_only));

        pt_this->t_last_notify.e_upd_field = (MMPR_SPACE_NOT_ENOUGH == i4_ret) ? MMP_BE_UI_UPD_FIELD_LIMITED_FLDR : MMP_BE_UI_UPD_FIELD_OPEN_FLDR_FAIL;
        pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
    }

    /* begin the test timer */
    _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_CB_CHECK, FALSE);

    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_set_curr_path
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_set_curr_path(CHAR* ps_pname)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    if ( NULL == ps_pname || c_strlen(ps_pname) == 0)
    {
        c_memset (pt_this->s_curr_path, 0, sizeof(pt_this->s_curr_path));
    }
    else if (c_strlen(ps_pname) >= MMP_BE_MAX_PATH_LEN)
    {
        return MMPR_INV_ARG;
    }
    else
    {
        c_strcpy(pt_this->s_curr_path, ps_pname);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_set_traverse_done
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_set_traverse_done(MMP_BE_FF_INST_T* pt_inst, BOOL b_done)
{
    pt_inst->b_traverse_done = b_done;
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief    _mmp_be_clean_all_traverse_done

 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_clean_all_traverse_done(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT8                   ui1_i;

    for (ui1_i = 0; ui1_i < _MMP_BE_FF_INST_IDX_CNT; ui1_i ++)
    {
        _mmp_be_set_traverse_done(&pt_this->at_ff_inst[ui1_i], FALSE);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_reset
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_reset(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT8                   i;

    pt_this->e_status = MMP_BE_STATUS_NONE;
    c_memset(&pt_this->t_last_notify, 0, sizeof(MMP_BE_UI_INFO_T));

    mmp_be_set_curr_path("");

    /*reset file filter*/
    for (i = 0; i < _MMP_BE_FF_INST_IDX_CNT; i++)
    {
        _mmp_be_set_path(&pt_this->at_ff_inst[i], MMP_BE_EMPTY_PATH);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_clone_ff_inst
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_clone_ff_inst(MMP_BE_FF_INST_T* pt_inst_to, MMP_BE_FF_INST_T* pt_inst_from)
{
    IS_MMPR_OK (mmp_ff_clone(pt_inst_to->ui1_ff_id, pt_inst_from->ui1_ff_id));

    pt_inst_to->b_traverse_done = pt_inst_from->b_traverse_done;
    c_strcpy(pt_inst_to->s_pname, pt_inst_from->s_pname);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_act_dev_invalid_handler
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_act_dev_invalid_handler(MMP_BE_DATA_MEMBER_T* pt_this)
{
    INT32                   i4_ret = MMPR_OK;
    UINT32                  ui4_cnt;
    BOOL                    b_is_avail = FALSE;

    /* if current device has been removed, exit to browser mode */
    if (MMP_BE_STATUS_PLAYER_ACT == pt_this->e_status)
    {
        i4_ret = mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_OK;
    }

    do
    {
        /* unplug device ,then plug it again. It'll use the cacah data, it maybe error by data having changed in device. */
        /* reset the active data */
        c_strcpy(pt_this->s_curr_path, MMP_BE_EMPTY_PATH);

        /* change the sort type, so reset traverse done to false */
        _mmp_be_clean_all_traverse_done();

        /* reset focus index */
        pt_this->ui4_focus_item_idx = 0;

        /* Reset history index */
        _mmp_be_traverse_done_stack_reset();

        /*Close preview if needed*/
        _mmp_be_stop_preview(pt_this);

        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID;
        i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

        if(pt_this->e_status != MMP_BE_STATUS_CHOOSE_FF)
        {
            /* if there is not FF page, is need to change to chooose mount page. */
            break;
        }

        /* if there is FF page, reset the data and return only.  */
        return MMPR_OK;
    }
    while(0);

    i4_ret = _mmp_be_is_mnt_state_avail(pt_this, &ui4_cnt, &b_is_avail);
    if (MMPR_OK != i4_ret || ui4_cnt == 0)
    {
        /* List items, this notify is send when browse_eng begin load items or show empty message */
        _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, TRUE);

        /*No any devicel, change status to MMP_BE_STATUS_CHOOSE_MNT*/
        pt_this->e_status = MMP_BE_STATUS_CHOOSE_MNT;
        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_NO_DEVICE;
        i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
    }
    else if (b_is_avail && MMP_BE_STATUS_NORMAL == pt_this->e_status)
    {
        UINT32  ui4_active_idx = 0;
        UTF16_T w2s_dev_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
        UTF16_T w2s_dev_hint[MMP_DEV_NAME_MAX_LEN + 1] = {0};

        i4_ret = mmp_be_get_activate_device_info(w2s_dev_info,
                                                 w2s_dev_hint,
                                                 &ui4_active_idx);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SET_ACT_MNT_POINT, (VOID*)ui4_active_idx);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_MNT_DEV_XNG;
        i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
    }
    else if (b_is_avail || MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status)
    {
        /*Multiple device*/
        i4_ret = _mmp_be_choose_mnt_pnt(pt_this);
    }
    else
    {
        SIZE_T  z_size = MMP_BE_MAX_PATH_LEN;
        UINT32  ui4_idx;

        /*Remain only one device*/
        i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_idx, &z_size, pt_this->s_curr_path);
        if (MMPR_OK != i4_ret || MMP_BE_IS_EMPTY_PATH(pt_this->s_curr_path))
        {
            return MMPR_FAIL;
        }

        /*klocwork*/
        MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

        i4_ret = _mmp_be_get_item_list(pt_this, &pt_this->at_ff_inst[pt_this->e_crt_inst_idx], pt_this->s_curr_path);
    }
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_choose_media_type
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_choose_media_type(MMP_BE_DATA_MEMBER_T* pt_this)
{

    pt_this->e_status = MMP_BE_STATUS_CHOOSE_FF;

    /* Reset history index */
    _mmp_be_traverse_done_stack_reset();

    /* Rest Copy List & Delete List*/
#ifdef MMP_FILE_OP_SUPPORT
    mmp_fo_flush_list(MMP_FF_ITEM_LIST_TYPE_COPY_LIST);
    mmp_fo_flush_list(MMP_FF_ITEM_LIST_TYPE_DEL_LIST);
#endif

    DBG_INFO_DIRECT("[mmp be] %s %d e_filter_type:%d \r\n",__FUNCTION__,__LINE__,pt_this->e_filter_type);

    switch (pt_this->e_filter_type)
    {
        case MMP_MEDIA_TYPE_PHOTO:
            pt_this->ui4_focus_item_idx = 0;

            break;
        case MMP_MEDIA_TYPE_AUDIO:
            pt_this->ui4_focus_item_idx  = 1;

            break;
        case MMP_MEDIA_TYPE_VIDEO:
            pt_this->ui4_focus_item_idx  = 2;

            break;
        case MMP_MEDIA_TYPE_TEXT:
            pt_this->ui4_focus_item_idx  = 3;

            break;
        default:
            pt_this->ui4_focus_item_idx  = 0;
    }

    /* List items, this notify is send when browse_eng begin load items or show empty message */
    _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, TRUE);

    pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_LST;
    pt_this->t_last_notify.ui4_dir_num = _mmp_be_get_media_type_count();
    pt_this->t_last_notify.ui4_file_num = 0;
    pt_this->t_last_notify.ui4_focus_idx = pt_this->ui4_focus_item_idx ;
    pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

    return MMPR_OK;
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_choose_mnt_pnt
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_choose_mnt_pnt(MMP_BE_DATA_MEMBER_T* pt_this)
{
    INT32                   i4_ret;
    CHAR                    s_mnt_name [MMP_BE_MAX_PATH_LEN] = { 0 };
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    MMP_BE_STATUS_T         e_status_old;
    UINT32                  ui4_dir_num;
    
    DBG_INFO_DIRECT("\031[mmp be] %s %d \r\n",__FUNCTION__,__LINE__);

    e_status_old = pt_this->e_status;

    pt_this->e_status = MMP_BE_STATUS_CHOOSE_MNT;

    /* Reset history index */
    _mmp_be_traverse_done_stack_reset();

    /*Get mount point count*/
    i4_ret = mmp_mc_device_get_mnt_count(&ui4_dir_num);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    if(ui4_dir_num == 0)
    {
        /* Notify the no device to browser  */

        if(pt_this->t_last_notify.ui4_dir_num == 0)
        {
            /* The last case, has send no device , not send again */
            return MMPR_OK;
        }

        /* If there is no device, don't get the active point index, because it'll return Error -1; */

        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_NO_DEVICE;
        pt_this->t_last_notify.ui4_dir_num = ui4_dir_num;
        pt_this->t_last_notify.ui4_file_num = 0;
        return pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

    }
    else
    {
        pt_this->t_last_notify.ui4_dir_num = ui4_dir_num;
    }

    /*Get active mount point*/
    i4_ret = mmp_mc_device_get_active_mnt_point(&pt_this->t_last_notify.ui4_focus_idx,
                                                &z_size,
                                                s_mnt_name);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    if((MMP_BE_STATUS_CHOOSE_FF == e_status_old) ||
       (MMP_BE_STATUS_NONE == e_status_old))
    {
        pt_this->ui4_focus_item_idx  = 0;

        pt_this->t_last_notify.ui4_focus_idx = 0;
    }
    else
    {
        pt_this->ui4_focus_item_idx  = pt_this->t_last_notify.ui4_focus_idx;
    }

    /* List items, this notify is send when browse_eng begin load items or show empty message */
    _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, TRUE);

    pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_MNT_LST;
    pt_this->t_last_notify.ui4_file_num = 0;
    pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_get_item_list
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_get_item_list(MMP_BE_DATA_MEMBER_T* pt_this,
                                   MMP_BE_FF_INST_T* pt_inst,
                                   CHAR* s_path)
{
    BOOL                    b_flush = FALSE;
    INT32                   i4_ret;
    UINT32                  ui4_dir_num, ui4_file_num;
#ifdef APP_NETWORK_SUPPORT
    MMP_BE_FILE_SRC_TYPE_T  e_src_type;
#endif


    /*klocwork*/
    MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

    /*Notify current traversed folder*/
    if (pt_inst == &pt_this->at_ff_inst[pt_this->e_crt_inst_idx])
    {
        //_mmp_be_stop_preview(pt_this);

        /* Folder exchange, it'll reset timer to listen for item list .
           it'll reset to none, when send following notify:  ff page mount page, list item ,no device */
        _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, FALSE);

        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME;
        pt_this->t_last_notify.e_upd_field |= MMP_BE_UI_UPD_FIELD_FOLDER_XNG;
        DBG_INFO_DIRECT("[mmp be] %s %d pf_data_change readly in <MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME> & <MMP_BE_UI_UPD_FIELD_FOLDER_XNG> \r\n",__FUNCTION__,__LINE__);
        pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

        /*pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO;*/
        //pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
    }

    /*Check if reuse previous result*/
    if (c_strcmp(pt_inst->s_pname, s_path) != 0 ||
        FALSE == pt_inst->b_traverse_done)
    {
        b_flush = TRUE;
    }

#ifdef APP_NETWORK_SUPPORT
    /*Check DLNA folder change case*/
    if (FALSE == b_flush)
    {
        i4_ret = mmp_be_get_file_src_type (s_path, &e_src_type);
        if (MMPR_OK == i4_ret && MMP_BE_FILE_SRC_DLNA == e_src_type &&
            c_fm_dlna_is_folder_changed(s_path))
        {
            b_flush = TRUE;
        }

        /*Check NEIGHBOR folder change case*/
        if(MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type)
        {
            b_flush = TRUE;
        }
    }
#endif

    if (b_flush)
    {
        i4_ret = _mmp_be_set_path(pt_inst, s_path);
    }
    else
    {
        i4_ret = mmp_ff_get_item_num(pt_inst->ui1_ff_id, &ui4_dir_num, &ui4_file_num);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_be_get_item_num() failed. i4_ret = %d.\r\n", i4_ret));
            return i4_ret;
        }
        
        //DBG_INFO_DIRECT("[mmp be] %s %d _mmp_be_reload_data() readly in  ui4_dir_num:%d ui4_file_num:%d\r\n",__FUNCTION__,__LINE__,ui4_dir_num,ui4_file_num);
        i4_ret = _mmp_be_reload_data(pt_this, pt_inst, ui4_dir_num, ui4_file_num);
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_reload_data
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_reload_data(MMP_BE_DATA_MEMBER_T* pt_this,
                                 MMP_BE_FF_INST_T* pt_inst,
                                 UINT32 ui4_dir_num,
                                 UINT32 ui4_file_num)
{
    /* List items, this notify is send when browse_eng begin load items or show empty message */
    _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_PARSING_ITEM, TRUE);

    pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_ITEM_LIST;
    pt_this->t_last_notify.e_parse_status = MMP_FF_PARSE_STATUS_DONE;
    pt_this->t_last_notify.ui4_dir_num = ui4_dir_num;
    pt_this->t_last_notify.ui4_file_num = ui4_file_num;
    pt_this->t_last_notify.ui4_focus_idx = pt_this->ui4_focus_item_idx;
#ifdef APP_CAST_TV_MMP
    if (MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
    {
        if(!pt_this->b_is_exit_cast)  //no retail mode
        {
            mmp_be_cd_child(0);
        }
        else
        {
            return MMPR_OK;
        }

    }
#else
    pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
#endif

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_is_mnt_state_avail
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_is_mnt_state_avail(MMP_BE_DATA_MEMBER_T* pt_this,
                                        UINT32* pui4_count,
                                        BOOL* pb_is_avail)
{
    INT32                       i4_ret;
    MMP_MC_DEV_UNSUPPORT_TYPE_T e_unsupt;
    SIZE_T                      z_size = MMP_BE_MAX_PATH_LEN;
    UINT32                      ui4_idx;
    MMP_BE_FILE_SRC_TYPE_T      e_src_type;

    i4_ret = mmp_mc_device_get_mnt_count(pui4_count);
    if(MMPR_OK != i4_ret)
    {
        *pui4_count = 0;
        return i4_ret;
    }

    switch(*pui4_count)
    {
        case 0:
            *pb_is_avail = FALSE;
            break;

        case 1:
        {
            z_size = sizeof(MMP_MC_DEV_UNSUPPORT_TYPE_T);
            i4_ret = mmp_mc_device_get_mnt_point_info(0,
                                                      MMP_MC_DEV_INFO_ID_UNSUPT_TYPE,
                                                      &z_size,
                                                      (VOID*)&e_unsupt); /*not support --> available*/
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }

            /* check the source type */
            /*Remain only one device*/
            z_size = MMP_BE_MAX_PATH_LEN;
            i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_idx, &z_size, pt_this->s_curr_path);
            i4_ret = mmp_be_get_file_src_type (pt_this->s_curr_path, &e_src_type);
            if (MMPR_OK == i4_ret && MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type)
            {
                /* net neighbor */
                *pb_is_avail = TRUE;
            }
            else
            {
                /* not neighbor */
                *pb_is_avail = (MMP_MC_DEV_UNSUPT_TYPE_NONE != e_unsupt) ? TRUE : FALSE;
            }

        }
        break;

        default: /* >= 2*/
            *pb_is_avail = TRUE;
            break;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_get_ff_inst_by_idx
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_get_ff_inst_by_idx(MMP_BE_DATA_MEMBER_T* pt_this,
                                        MMP_BE_FF_IDX e_ff_idx,
                                        MMP_BE_FF_INST_T** ppt_inst)
{
    switch (e_ff_idx)
    {
        case MMP_BE_FF_IDX_CRT:
            /*klocwork*/
            MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

            *ppt_inst = &pt_this->at_ff_inst[pt_this->e_crt_inst_idx];
            break;
        case MMP_BE_FF_IDX_CHILD:
            *ppt_inst = (_MMP_BE_FF_INST_IDX_0 == pt_this->e_crt_inst_idx) ?
                        &pt_this->at_ff_inst[_MMP_BE_FF_INST_IDX_1] :
                        &pt_this->at_ff_inst[_MMP_BE_FF_INST_IDX_0];
            break;
        default:
            return MMPR_INV_ARG;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_play_crnt_folder
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_play_crnt_folder(MMP_BE_DATA_MEMBER_T* pt_this,
                                      UINT32 ui4_focus_idx,
                                      BOOL   b_is_active_op,
                                      BOOL b_view_only)
{
    INT32                   i4_ret;
    MMP_GROUND_MODE_T       e_mode;
    UINT32                  ui4_cnt = 1;
    MMP_ITEM_INFO_T         t_item_info;
    CHAR                    s_full_path[MMP_BE_MAX_PATH_LEN]={0};
    UINT8                   ui1_ff_id;
    UINT32                  ui4_dir_num, ui4_file_num, ui4_file_idx, ui4_target_idx;
    MMP_PL_PLAY_CMD_PARAM_ITEM_T    t_play_param;

    /*klocwork*/
    MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

    ui1_ff_id = pt_this->at_ff_inst[pt_this->e_crt_inst_idx].ui1_ff_id;

    if (ITEM_TYPE_DIR == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT, ui4_focus_idx))
    {
        return MMPR_NOT_SUPPORT;
    }

    /*  Set mmp play mode */
    IS_MMPR_OK( mmp_mc_list_set_play_present_mode((MMP_MEDIA_TYPE_AUDIO == pt_this->e_filter_type) ? MMP_FP_PRESENT_MODE_PREVIEW : MMP_FP_PRESENT_MODE_FULL));

    e_mode = (MMP_MEDIA_TYPE_AUDIO == pt_this->e_filter_type) ?
             MMP_GROUND_MODE_BACK : MMP_GROUND_MODE_FORE;

    /* Remove last playlist item */
    mmp_mc_list_remove_all(e_mode);

    /*Get focus file index*/
    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    ui4_file_idx = ui4_focus_idx - ui4_dir_num;

    /*Get focus file item info*/
    c_memset(&t_item_info, 0, sizeof(MMP_ITEM_INFO_T));
    i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                  ITEM_TYPE_FILE,
                                  ui4_file_idx,
                                  &ui4_cnt,
                                  &t_item_info);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    MMP_DBG_INFO(("[MMP][%s %d] file name %s,ui4_file_idx = %d  query_list_type:%d  b_view_only:%d   e_filter_type:%d  b_is_active_op:%d\n",__FUNCTION__,__LINE__,\
        t_item_info.s_name,\
        ui4_file_idx,\
        mmp_mc_browse_query_list_type(t_item_info.s_name, NULL),\
        b_view_only,\
        pt_this->e_filter_type,\
        b_is_active_op));
    if (MMPR_OK == mmp_mc_browse_query_list_type(t_item_info.s_name, NULL))
    {
        /*It's playlist file*/
        MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);
        IS_MMPR_OK(mmp_mc_list_add_parser(e_mode, s_full_path));
        IS_MMPR_OK(mmp_mc_list_play(e_mode, ui4_file_idx));
    }
    else
    {
        /*It's normal file*/
        /*If it's backgounrd player, clone to BK FF inst*/
        if (MMP_GROUND_MODE_BACK == e_mode)
        {
            i4_ret = _mmp_be_clone_ff_inst(&pt_this->at_ff_inst[_MMP_BE_FF_INST_IDX_BK],
                                           &pt_this->at_ff_inst[pt_this->e_crt_inst_idx]);
            if (MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
            ui1_ff_id = pt_this->at_ff_inst[_MMP_BE_FF_INST_IDX_BK].ui1_ff_id;
        }

        IS_MMPR_OK(mmp_ff_apply_flag_filter(ui1_ff_id,
                                            MMP_FF_ITEM_FLAG_NORMAL_FILE));

        IS_MMPR_OK(mmp_ff_convert_adv_filter_idx(ui1_ff_id,
                                                 TRUE,
                                                 ui4_file_idx,
                                                 &ui4_target_idx));

        c_sprintf(s_full_path, "%s%d", MMP_FF_FILE_PSR_TOKEN, ui1_ff_id);
        IS_MMPR_OK(mmp_mc_list_add_parser(e_mode, s_full_path));

        if (b_view_only && MMP_MEDIA_TYPE_PHOTO == pt_this->e_filter_type)
        {
            mmp_mc_list_view(e_mode, ui4_target_idx);
        }
        else
        {
            c_memset(&t_play_param, 0, sizeof(MMP_PL_PLAY_CMD_PARAM_ITEM_T));
            t_play_param.e_mode = e_mode;
            t_play_param.ui4_idx = ui4_target_idx;
            if(b_is_active_op)
            {
                t_play_param.e_act_op = MMP_PL_PLAY_ACTIVE_OP_AUTO;
            }
            else
            {
                t_play_param.e_act_op = MMP_PL_PLAY_ACTIVE_OP_OFF;
            }
            t_play_param.z_size = sizeof(MMP_PL_PLAY_CMD_PARAM_ITEM_T);

            IS_MMPR_OK(mmp_mc_list_play_ex(MMP_PL_PLAY_CMD_PARAM_ID_0, (VOID*)&t_play_param));
        }
    }

    if(!b_is_active_op)
    {
        /* Update the browse, playing file info */
        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO;
        pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
    }

    if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
    {
        pt_this->e_status = MMP_BE_STATUS_PLAYER_ACT;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_preview_crnt_file
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_preview_crnt_file(MMP_BE_DATA_MEMBER_T* pt_this,
                                       UINT32 ui4_focus_idx)
{
    INT32                   i4_ret = MMPR_OK;
    UINT32                  ui4_cnt = 1;
    MMP_ITEM_INFO_T         t_item_info;
    CHAR                    s_full_path[MMP_BE_MAX_PATH_LEN]={0};
    UTF16_T                 w2s_str[128] = {0};

    c_memset(&t_item_info, 0, sizeof(MMP_ITEM_INFO_T));

    /* disable viewport function in MMP/video preview mode,
                  must to enable viewport in any other cases. */
    a_cfg_set_skip_viewport_func(TRUE);

    /*Get media_type of current focus item*/
    i4_ret = mmp_mc_browse_get_focus_type(&pt_this->e_preview_type);

    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    switch (pt_this->e_preview_type)
    {
        case MMP_MEDIA_TYPE_AUDIO:
            mmp_mc_browse_load_file_thumbnail(&pt_this->t_preview_info.t_preview_rect, MMP_FP_THUMB_COORDS_CANVAS);
            break;
        case MMP_MEDIA_TYPE_PHOTO:
        case MMP_MEDIA_TYPE_VIDEO:
        case MMP_MEDIA_TYPE_TEXT:
            /*Get focus file item info*/
            IS_MMPR_OK(mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                             ITEM_TYPE_NONE,
                                             ui4_focus_idx,
                                             &ui4_cnt,
                                             &t_item_info));
#ifdef APP_TTS_SUPPORT
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
            MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);

            MMPR_LOG_ON_FAIL(c_wgl_set_transparent_list(pt_this->h_transparent_list,
                                       &pt_this->t_preview_info.t_preview_rect,
                                       1));

            MMPR_LOG_ON_FAIL(c_wgl_enable_transparent_list(pt_this->h_transparent_list, TRUE, TRUE));
            MMPR_LOG_ON_FAIL(c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_preview_info.t_preview_rect, TRUE));

            MMPR_LOG_ON_FAIL(mmp_mc_list_set_preview_info(MMP_BROWSE_ID_LAST, &pt_this->t_preview_info));
            if(MMP_MEDIA_TYPE_TEXT  == pt_this->e_preview_type ||
               MMP_MEDIA_TYPE_PHOTO == pt_this->e_preview_type )
            {
                mmp_mc_list_remove_all(MMP_GROUND_MODE_FORE);
                mmp_mc_list_add_file(MMP_GROUND_MODE_FORE, s_full_path);
                i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE, 0);
            }
            else
            {
                UINT32 ui4_dir_num,ui4_file_num;
                    /*Get focus file index*/
                 if( MMPR_OK == mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num))
                    ui4_focus_idx -= ui4_dir_num;
                 mmp_mc_file_stop(MMP_GROUND_MODE_FORE);
                i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE, ui4_focus_idx);
            }
            DBG_LOG_PRINT(("<MMP> %s %d try to play file %s,ui4_focus_idx = %d\n\r",__FILE__,__LINE__,s_full_path,ui4_focus_idx));
            break;

        default:
            return MMPR_NOT_SUPPORT;
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_bk_player_stop_hdlr
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_bk_player_stop_hdlr(MMP_BE_DATA_MEMBER_T* pt_this)
{
    mmp_mc_list_remove_all(MMP_GROUND_MODE_BACK);

    pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_BK_PLAYER_STOP;
    pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

    return MMPR_OK;
}
/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_set_sort_type_to_acfg
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_set_sort_type_to_acfg(MMP_SORT_TYPE_T e_new_sort)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT8                   ui1_cfg_value;

    ui1_cfg_value = (UINT8)e_new_sort;

    switch (pt_this->e_filter_type)
    {
        case MMP_MEDIA_TYPE_PHOTO:
            a_cfg_custom_set_mmp_photo_sort(ui1_cfg_value);
            break;

        case MMP_MEDIA_TYPE_AUDIO:
            a_cfg_custom_set_mmp_audio_sort(ui1_cfg_value);
            break;

        case MMP_MEDIA_TYPE_VIDEO:
            a_cfg_custom_set_mmp_video_sort(ui1_cfg_value);
            break;

        case MMP_MEDIA_TYPE_TEXT :
            a_cfg_set_mmp_text_sort(ui1_cfg_value);
            break;

        default:
            return MMPR_INV_ARG;
    }

    return MMPR_OK;

}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_get_sort_type_from_acfg
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_get_sort_type_from_acfg(MMP_SORT_TYPE_T* pe_new_sort)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret;
    UINT8                   ui1_cfg_value = 0;

    switch (pt_this->e_filter_type)
    {
        case MMP_MEDIA_TYPE_PHOTO:
            i4_ret = a_cfg_custom_get_mmp_photo_sort(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                ui1_cfg_value = 0;
            }
            break;

        case MMP_MEDIA_TYPE_AUDIO:
            i4_ret = a_cfg_custom_get_mmp_audio_sort(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                ui1_cfg_value = 0;
            }
            break;

        case MMP_MEDIA_TYPE_VIDEO:
            i4_ret = a_cfg_custom_get_mmp_video_sort(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                ui1_cfg_value = 0;
            }
            break;

        case MMP_MEDIA_TYPE_TEXT :
            i4_ret = a_cfg_get_mmp_text_sort(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                 ui1_cfg_value = 0;
            }

        default:
            return MMPR_INV_ARG;
    }

    *pe_new_sort = (MMP_SORT_TYPE_T)ui1_cfg_value;

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_set_recur_parsing_to_acfg
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_set_recur_parsing_to_acfg(BOOL b_is_recur_parsing)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT8                   ui1_cfg_value;

    ui1_cfg_value = (UINT8)b_is_recur_parsing;

    switch (pt_this->e_filter_type)
    {
        case MMP_MEDIA_TYPE_PHOTO:
            a_cfg_custom_set_mmp_photo_recur_parsing(ui1_cfg_value);
            break;

        case MMP_MEDIA_TYPE_AUDIO:
            a_cfg_custom_set_mmp_audio_recur_parsing(ui1_cfg_value);
            break;

        case MMP_MEDIA_TYPE_VIDEO:
            a_cfg_custom_set_mmp_video_recur_parsing(ui1_cfg_value);
            break;

        default:
            return MMPR_INV_ARG;
    }

    return MMPR_OK;
}

#if 0
/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_get_recur_parsing_from_acfg
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_get_recur_parsing_from_acfg(BOOL* pb_is_recur_parsing)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret;
    UINT8                   ui1_cfg_value = 0;

    switch (pt_this->e_filter_type)
    {
        case MMP_MEDIA_TYPE_PHOTO:
            i4_ret = a_cfg_custom_get_mmp_photo_recur_parsing(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                ui1_cfg_value = 0;
            }
            break;

        case MMP_MEDIA_TYPE_AUDIO:
            i4_ret = a_cfg_custom_get_mmp_audio_recur_parsing(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                ui1_cfg_value = 0;
            }
            break;

        case MMP_MEDIA_TYPE_VIDEO:
            i4_ret = a_cfg_custom_get_mmp_video_recur_parsing(&ui1_cfg_value);
            if(APP_CFGR_OK != i4_ret)
            {
                ui1_cfg_value = 0;
            }
            break;

        default:
            return MMPR_INV_ARG;
    }

    *pb_is_recur_parsing = (BOOL)ui1_cfg_value;

    return MMPR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _mmp_be_traverse_done_stack_push
 * Description: This function pushs current selection to stack.
 * Inputs:  ui2_user_sel        User selection.
 * Outputs: -
 * Returns: MMPR_OK            Routine succeeded.
 ----------------------------------------------------------------------------*/
static VOID _mmp_be_traverse_done_stack_push (UINT32 ui4_user_sel)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    if (pt_this->ui4_traverse_depth == MMP_RC_MAX_FOLDER_DEPTH)
    {
        /* Reset. */
        pt_this->ui4_traverse_depth = 0;
    }

    pt_this->ui4_traverse_history [pt_this->ui4_traverse_depth ++] = ui4_user_sel;
}
/*-----------------------------------------------------------------------------
 * Name: _mmp_be_traverse_done_stack_pop
 * Description: This function pops a selection from stack.
 * Inputs:  -
 * Outputs: -
 * Returns: MMPR_OK            Routine succeeded.
 ----------------------------------------------------------------------------*/
static UINT32 _mmp_be_traverse_done_stack_pop (VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    return (pt_this->ui4_traverse_depth == 0) ? 0: pt_this->ui4_traverse_history[--pt_this->ui4_traverse_depth];
}
/*-----------------------------------------------------------------------------
 * Name: _mmp_be_traverse_done_stack_reset
 * Description: This function cleans stack.
 * Inputs:  -
 * Outputs: -
 * Returns: MMPR_OK            Routine succeeded.
 ----------------------------------------------------------------------------*/
static VOID _mmp_be_traverse_done_stack_reset (VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    pt_this->ui4_traverse_depth = 0;
}
/*-----------------------------------------------------------------------------
 * Name: _mmp_be_traverse_done_stack_push
 * Description: This function pushs current selection to stack.
 * Inputs:  ui2_user_sel        User selection.
 * Outputs: -
 * Returns: MMPR_OK            Routine succeeded.
 ----------------------------------------------------------------------------*/
static VOID _mmp_be_traverse_done_stack_transfer_bws (UINT8 ui1_bwr_id_from,UINT8 ui1_bwr_id_to)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_traverse_depth = 0;
    BOOL                    b_add_parent_from,b_add_parent_to;
    UINT16                  ui2_bwr_flag_from,ui2_bwr_flag_to;

    if (pt_this->ui4_traverse_depth == MMP_RC_MAX_FOLDER_DEPTH)
    {
        /* Reset. */
        pt_this->ui4_traverse_depth = 0;
    }

    /*klocwork*/
    MMP_RET_WITH_ASSERT(ui1_bwr_id_from < MMP_MC_RC_FILE_BROWSER_MAX_COUNT && ui1_bwr_id_to < MMP_MC_RC_FILE_BROWSER_MAX_COUNT,
                        return);

    ui2_bwr_flag_from = pt_this->at_browser[ui1_bwr_id_from].t_bwr_prop.ui2_flag;
    ui2_bwr_flag_to   = pt_this->at_browser[ui1_bwr_id_to].t_bwr_prop.ui2_flag;

    if(MMP_BE_BWR_FLAG_ADD_PARENT_ITEM & ui2_bwr_flag_from)
    {
        b_add_parent_from = TRUE;
    }
    else
    {
        b_add_parent_from = FALSE;
    }

    if(MMP_BE_BWR_FLAG_ADD_PARENT_ITEM & ui2_bwr_flag_to)
    {
        b_add_parent_to = TRUE;
    }
    else
    {
        b_add_parent_to = FALSE;
    }

    if(b_add_parent_to == b_add_parent_from)
    {
        return;
    }

    if ((MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status) ||
        (MMP_BE_STATUS_CHOOSE_FF == pt_this->e_status))
    {
        return;
    }

    if(b_add_parent_to)
    {
        ++pt_this->ui4_focus_item_idx;
    }
    else
    {
        if(pt_this->ui4_focus_item_idx !=0)
        {
            --pt_this->ui4_focus_item_idx;
        }
    }

    for(ui4_traverse_depth = 0;ui4_traverse_depth < pt_this->ui4_traverse_depth;ui4_traverse_depth++)
    {
        if(b_add_parent_to)
        {
            ++pt_this->ui4_traverse_history[ui4_traverse_depth];
        }
        else
        {
            if(pt_this->ui4_traverse_history[ui4_traverse_depth] != 0)
            {
                --pt_this->ui4_traverse_history[ui4_traverse_depth];
            }
        }
    }
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_reset_timer
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_reset_timer(MMP_BE_DATA_MEMBER_T* pt_this,
                                 MMP_BE_TIMER_ID_T e_id,
                                 BOOL b_stop)
{
    INT32                   i4_ret;

    i4_ret = c_timer_stop(pt_this->ah_timer[e_id]);
    if(OSR_OK != i4_ret)
    {
        return MMPR_INTERNAL_ERROR;
    }

    if(b_stop || pt_this->aui4_timer_delay[e_id] == 0)
    {
        pt_this->ae_timer_status[e_id] = MMP_BE_TIMER_STATUS_NONE;
        return MMPR_OK;
    }

    i4_ret = c_timer_start(pt_this->ah_timer[e_id],
                           pt_this->aui4_timer_delay[e_id],
                           X_TIMER_FLAG_ONCE,
                           _mmp_be_timer_nfy,
                           (VOID*)e_id);
    if(OSR_OK != i4_ret)
    {
        pt_this->ae_timer_status[e_id] = MMP_BE_TIMER_STATUS_NONE;
        return MMPR_INTERNAL_ERROR;
    }

    pt_this->ae_timer_status[e_id] = MMP_BE_TIMER_STATUS_LISTEN;
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_timer_nfy
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_be_timer_nfy(HANDLE_T h_timer, VOID* pv_tag)
{
    t_g_browse_eng.ae_timer_status[(MMP_BE_TIMER_ID_T)(UINT32)pv_tag] = MMP_BE_TIMER_STATUS_EXPIRED;

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_be_do_timer_nfy,
                                pv_tag,
                                NULL,
                                NULL,
                                NULL);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_do_timer_nfy
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_be_do_timer_nfy(VOID* pv_param1,
                                 VOID* pv_param2,
                                 VOID* pv_param3,
                                 VOID* pv_param4)
{
    MMP_BE_DATA_MEMBER_T*           pt_this = &t_g_browse_eng;
    MMP_BE_TIMER_ID_T               e_id = (MMP_BE_TIMER_ID_T)(UINT32)pv_param1;

    if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
    {
        /*Invalid timeout notify*/
        return;
    }

    if (MMP_BE_TIMER_STATUS_EXPIRED == pt_this->ae_timer_status[e_id])
    {
        pt_this->ae_timer_status[e_id] = MMP_BE_TIMER_STATUS_NONE;

        /*Perform operation according to timer id*/
        switch (e_id)
        {
            case MMP_BE_TIMER_ID_PARSING_ITEM:
            {
                /* Send notify to client , parsing time out  */
                pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT;
                pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
            }
            break;

            case MMP_BE_TIMER_ID_FILE_PREVEW:
            {
                _mmp_be_preview_crnt_file(pt_this, pt_this->ui4_focus_item_idx);
            }
            break;

            case MMP_BE_TIMER_ID_CB_CHECK:
            {
                /* file filter had no call back come in before 5 second  */
                DBG_LOG_PRINT(("\n !!!!File filter had no call back come in before 5 second !!!!\n,line=%d\n",__LINE__));
                /* reset timer again */
                _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_CB_CHECK, FALSE);

                pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT;
                pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
            }
            break;

            default:
                break;
        }
    }
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_stop_preview
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_stop_preview(MMP_BE_DATA_MEMBER_T* pt_this)
{
    switch (pt_this->e_preview_type)
    {
        case MMP_MEDIA_TYPE_TEXT :
        case MMP_MEDIA_TYPE_PHOTO:
        case MMP_MEDIA_TYPE_VIDEO:
            c_wgl_enable_transparent_list(pt_this->h_transparent_list, FALSE, TRUE);
            c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_preview_info.t_preview_rect, TRUE);

            //a_vol_ctrl_set_hide(); /* via+ mmp */
            mmp_mc_list_set_preview_info(MMP_RC_BROWSER_ID_LIST, NULL);
            mmp_mc_list_set_play_present_mode(MMP_FP_PRESENT_MODE_FULL);
            break;
        case MMP_MEDIA_TYPE_AUDIO:
            mmp_mc_browse_clean_file_thumbnail(&pt_this->t_preview_info.t_preview_rect, MMP_FP_THUMB_COORDS_CANVAS);
            break;
        default:
            break;
    }

    pt_this->e_preview_type = MMP_MEDIA_TYPE_UNKNOWN;

    return MMPR_OK;
}

#ifdef MMP_FILE_OP_SUPPORT
static INT32 _mmp_be_enter_bg_mode(VOID)
{
    INT32                   i4_ret;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    i4_ret = mmp_mc_list_close(MMP_GROUND_MODE_ALL);
    if (MMPR_OK != i4_ret &&
        MMPR_IS_CLOSED != i4_ret &&
        MMPR_NO_DATA != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_mc_browse_clear_focus();
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    pt_this->e_status = MMP_BE_STATUS_BACKGROUND;

    return (MMPR_OK);
}

static INT32 _mmp_be_exit_bg_mode(VOID)
{
    INT32                   i4_ret;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    BOOL                    b_is_valid = FALSE;

    pt_this->e_status = MMP_BE_STATUS_NORMAL;


     _mmp_be_clean_all_traverse_done();

    /* reset the focus item idx */
    pt_this->ui4_focus_item_idx = 0;

    i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_cmd_do(MMP_BE_BROWSER_CMD_ID_EXIT_BG_MODE, NULL);

    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = a_rmv_dev_is_path_valid(pt_this->s_curr_path, &b_is_valid);
    if (i4_ret != RMVR_OK || b_is_valid == FALSE)
    {
        i4_ret =  _mmp_be_act_dev_invalid_handler(pt_this);
    }
    else
    {
        UINT32 ui4_idx = 0;
        UINT32 ui4_cnt = 0;
        CHAR   s_mnt_name[_MMP_BE_MNT_POINT_MAX_PATH_LEN] = {0};
        SIZE_T z_size;
        i4_ret = mmp_mc_device_get_mnt_count(&ui4_cnt);
        IS_MMPR_OK (i4_ret);

        for (ui4_idx = 0; ui4_idx < ui4_cnt; ui4_idx++)
        {
            z_size = sizeof(s_mnt_name);
            i4_ret = mmp_mc_device_get_mnt_point(ui4_idx, &z_size, s_mnt_name);
            IS_MMPR_OK(i4_ret);

            z_size = (SIZE_T) c_strlen(s_mnt_name);
            if (c_strncmp(s_mnt_name, pt_this->s_curr_path, z_size) == 0)
            {
                mmp_mc_device_set_active_mnt_point(ui4_idx);
                break;
            }
        }

        if (ui4_idx == ui4_cnt)
        {
            return (MMPR_FAIL);
        }

        i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT,MMP_BE_REFRESH_TYPE_ITEM_LST);
    }
    IS_MMPR_OK(i4_ret);

    return (MMPR_OK);
}
#endif

static INT32 _mmp_be_select_file(MMP_BE_FF_IDX e_ff_idx, UINT32 ui4_file_idx)
{
#ifdef MMP_FILE_OP_SUPPORT
    BOOL                        b_selected;
    INT32                       i4_ret;
    MMP_FF_ITEM_ATTR_T          t_item_attr;
    MMP_FF_ITEM_LIST_OP_TYPE_T  e_op_type;
    MMP_BE_FF_INST_T*           pt_inst;

    c_memset(&t_item_attr, 0, sizeof(MMP_FF_ITEM_ATTR_T));

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        e_ff_idx,
                                        &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    t_item_attr.e_item_type = ITEM_TYPE_FILE;
    t_item_attr.ui4_idx     = ui4_file_idx;
    i4_ret = mmp_fo_query_list(pt_inst->ui1_ff_id,
                               MMP_FF_ITEM_LIST_TYPE_SEL_LIST,
                               &t_item_attr,
                               &b_selected);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }


    if (b_selected)
    {
        e_op_type = MMP_FF_ITEM_LIST_OP_TYPE_RMV;
    }
    else
    {
        e_op_type = MMP_FF_ITEM_LIST_OP_TYPE_ADD;
    }

    i4_ret = mmp_fo_upd_list_item(pt_inst->ui1_ff_id,
                                  MMP_FF_ITEM_LIST_TYPE_SEL_LIST,
                                  e_op_type,
                                  1,
                                  &t_item_attr);
    return (i4_ret);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

static INT32 _mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_T e_list_type,
                                   MMP_BE_FF_IDX e_ff_idx,
                                   UINT32 ui4_file_idx,
                                   BOOL* pb_exists)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32                       i4_ret;
    MMP_BE_FF_INST_T*           pt_inst;
    MMP_FF_ITEM_ATTR_T          t_item_attr;

    c_memset(&t_item_attr, 0, sizeof(MMP_FF_ITEM_ATTR_T));

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        e_ff_idx,
                                        &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    t_item_attr.e_item_type = ITEM_TYPE_FILE;
    t_item_attr.ui4_idx     = ui4_file_idx;
    i4_ret = mmp_fo_query_list(pt_inst->ui1_ff_id,
                               e_list_type,
                               &t_item_attr,
                               pb_exists);

    return (i4_ret);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

#ifdef MMP_FILE_OP_SUPPORT
static INT32 _mmp_be_clone_to_copy_list(MMP_BE_FF_IDX e_ff_idx)
{
    INT32                       i4_ret;
    MMP_BE_FF_INST_T*           pt_inst;

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        e_ff_idx,
                                        &pt_inst);

    i4_ret = mmp_fo_flush_list(MMP_FF_ITEM_LIST_TYPE_COPY_LIST);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_fo_clone_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST,
                               MMP_FF_ITEM_LIST_TYPE_COPY_LIST);
    return (i4_ret);
}

static INT32 _mmp_be_clone_to_del_list(MMP_BE_FF_IDX e_ff_idx)
{
    INT32                       i4_ret;
    MMP_BE_FF_INST_T*           pt_inst;

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        e_ff_idx,
                                        &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_fo_flush_list(MMP_FF_ITEM_LIST_TYPE_DEL_LIST);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_fo_clone_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST,
                               MMP_FF_ITEM_LIST_TYPE_DEL_LIST);
    return (i4_ret);
}

static VOID _mmp_be_fo_nfy_cb(MMP_FO_MSG_ID_T e_msg_id,VOID* pv_param)
{
    /*do something here*/
    switch(e_msg_id)
    {
    case MMP_FO_MSG_COPY_START:
    case MMP_FO_MSG_DEL_START:
        break;

    case MMP_FO_MSG_COPY_END:
    case MMP_FO_MSG_COPY_ERROR:
        {
            mmp_fo_flush_list(MMP_FF_ITEM_LIST_TYPE_COPY_LIST);
            _mmp_be_exit_bg_mode();
        }
        break;

     case MMP_FO_MSG_DEL_END:
     case MMP_FO_MSG_DEL_ERROR:
        {
            mmp_be_empty_crt_folder_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST);
            mmp_fo_flush_list(MMP_FF_ITEM_LIST_TYPE_DEL_LIST);
            _mmp_be_exit_bg_mode();
        }
        break;

    default:
        return;
    }
}
#endif

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_locked_inp_hdlr
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_be_locked_inp_hdlr(VOID* pv_param1,
                                    VOID* pv_param2,
                                    VOID* pv_param3,
                                    VOID* pv_param4)
{
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ACTIVE, MMP_MSD_ID_LOCKED_INP, NULL);
}
#endif

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_upd_res_mode
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_be_upd_res_mode(MMP_BE_DATA_MEMBER_T* pt_this)
{
    if (MMP_BE_BWR_FLAG_ENABLE_FILE_PREVIEW & pt_this->pt_act_bwr->t_bwr_prop.ui2_flag &&
        MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
    {
        mmp_drc_switch_mode(MMP_DRC_MODE_FREE);
        mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_VIDEO);
    }
    else
    {
        mmp_drc_switch_mode(MMP_DRC_MODE_THUMB);
        mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_THUMBNAIL);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_be_get_media_type_count
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static UINT32 _mmp_be_get_media_type_count(VOID)
{
    UINT32                  ui4_count;

    ui4_count = MMP_FILTER_MEDIA_TYPE_LAST;

#if !defined(MMP_FB_RC_IS_ENABLE_VIDEO_FILTER)
    ui4_count--;
#endif

#if !defined(MMP_FB_RC_IS_ENABLE_TEXT_FILTER)
    ui4_count--;
#endif

    return ui4_count;
}


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_init
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_init(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT8                   i;
    GL_RECT_T               t_rect = {0};

    /*Init members*/
    c_memset (pt_this, 0, sizeof (MMP_BE_DATA_MEMBER_T));
    pt_this->e_sort = MMP_SORT_TYPE_NONE;
    pt_this->e_filter_type = MMP_MEDIA_TYPE_UNKNOWN;
    pt_this->ui1_act_bwr_id = MMP_MC_BWR_ID_NULL;
    pt_this->ui4_preview_item_idx = MMP_NULL_FILE_IDX;

#ifdef APP_CAST_TV_MMP
    pt_this->b_is_exit_cast = FALSE;
#endif

    for (i = 0; i< _MMP_BE_FF_INST_IDX_CNT; i++)
    {
        IS_MMPR_OK(mmp_ff_open(&pt_this->at_ff_inst[i].ui1_ff_id));
    }

    for (i = 0; i < MMP_BE_TIMER_ID_COUNT; i++)
    {
        IS_MMPR_OK(c_timer_create(&pt_this->ah_timer[i]));
    }

    pt_this->aui4_timer_delay[MMP_BE_TIMER_ID_PARSING_ITEM] = MMP_TIMER_PARSE_FOLDER_DELAY;
    pt_this->aui4_timer_delay[MMP_BE_TIMER_ID_FILE_PREVEW]  = MMP_TIMER_FILE_PREVIEW_DELAY;
    pt_this->aui4_timer_delay[MMP_BE_TIMER_ID_CB_CHECK]     = MMP_TIMER_CB_CHECK_DELAY;

#if 0
    i4_ret = mmp_fo_reg_nfy_fct(_mmp_be_fo_nfy_cb);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("File Operator notify function register failed. i4_ret = %d \n", i4_ret));
        return i4_ret;
    }
#endif

    /*Creat transparent list for file preview*/
    IS_MMPR_OK (c_wgl_create_transparent_list(mmp_main_get_canvas(),
                                           &t_rect,
                                           1,
                                           &pt_this->h_transparent_list));


    mmp_mc_list_set_play_present_mode(MMP_FP_PRESENT_MODE_PREVIEW);
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_deinit
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_deinit(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT8                   i;
    INT32                   i4_ret = MMPR_OK;

    /*klocwork*/
    MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

    _mmp_be_set_traverse_done(&pt_this->at_ff_inst[pt_this->e_crt_inst_idx], FALSE);

    for (i = 0; i< _MMP_BE_FF_INST_IDX_CNT; i++)
    {
        IS_MMPR_OK(mmp_ff_close(pt_this->at_ff_inst[i].ui1_ff_id));
    }
    if (pt_this->h_transparent_list != NULL_HANDLE)
    {
        i4_ret = c_wgl_delete_transparent_list(pt_this->h_transparent_list);
        if(MMPR_OK!= i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_delete_transparent_list() fail. i4_ret = %d.\r\n", i4_ret));
        }
        pt_this->h_transparent_list = NULL_HANDLE;
    }



    /*delete timer */
    for (i = 0; i < MMP_BE_TIMER_ID_COUNT; i++)
    {
        i4_ret = c_timer_delete(pt_this->ah_timer[i]);
        IS_MMPR_OK(i4_ret);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_reg_brower
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_reg_brower(const MMP_FILE_BROWSER_INTF_T* pt_intf,
                        const MMP_MC_FILE_BROWSER_PROPERTY_T* pt_property,
                        const MMP_BE_BROWSER_HDLR_T* pt_bwr_hdlr,
                        const MMP_BE_BROWSER_PROPERTY_T* pt_bwr_prop)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret;

    if (NULL == pt_bwr_hdlr)
    {
        MMP_DBG_ERROR(("pt_bwr_hdlr is illegal.\r\n"));
        return MMPR_INV_ARG;
    }

    if (FALSE == MMP_BE_BROWSER_HDLR_IS_LEGAL(*pt_bwr_hdlr))
    {
        MMP_DBG_ERROR(("pt_bwr_hdlr is illegal.\r\n"));
        return MMPR_INV_ARG;
    }

    i4_ret = mmp_mc_reg_file_brower(pt_intf, pt_property);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_mc_reg_file_brower() failed. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    /*klocwork*/
    MMP_RET_WITH_ASSERT(pt_property->ui1_id < MMP_MC_RC_FILE_BROWSER_MAX_COUNT, return MMPR_INTERNAL_ERROR);

    pt_this->at_browser[pt_property->ui1_id].t_bwr_hdlr = *pt_bwr_hdlr;

    if (pt_bwr_prop)
    {
        pt_this->at_browser[pt_property->ui1_id].t_bwr_prop = *pt_bwr_prop;
    }
    else
    {
        c_memset(&(pt_this->at_browser[pt_property->ui1_id].t_bwr_prop), 0, sizeof(MMP_BE_BROWSER_PROPERTY_T));
    }

    return MMPR_OK;
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_activate
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_activate(UINT8 ui1_bwr_id, UINT32 ui4_file_idx)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    BOOL                    b_is_valid;
    UINT16                  ui2_bwr_flag;
    UINT32                  ui4_mnt_count;
    UINT32                  ui4_dir_num, ui4_file_num;
    BOOL                    b_is_avail;
    INT32                   i4_ret = MMPR_OK;
    UINT8                   ui1_ff_id;

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    {
        UINT8               ui1_input;
        BOOL                b_block;

        a_cfg_get_input_src(SN_PRES_MAIN_DISPLAY, &ui1_input);
        i4_ret = a_cfg_get_input_src_block(ui1_input, &b_block);
        if (APP_CFGR_OK == i4_ret && b_block)
        {
            mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                        _mmp_be_locked_inp_hdlr,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL);
            return MMPR_OK;
        }
    }
#endif

    pt_this->e_rmv_dev_previous_status = pt_this->e_rmv_dev_current_status;
    a_rmv_dev_custom_check_status(&pt_this->e_rmv_dev_current_status);

    /*klocwork*/
    MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

    ui1_ff_id = pt_this->at_ff_inst[pt_this->e_crt_inst_idx].ui1_ff_id;

    pt_this->pt_act_bwr = &pt_this->at_browser[ui1_bwr_id];
    MMP_ASSERT(NULL != pt_this->pt_act_bwr);

    pt_this->ui1_act_bwr_id = ui1_bwr_id;

    ui2_bwr_flag = pt_this->pt_act_bwr->t_bwr_prop.ui2_flag;
    /*VP info*/
    pt_this->ui1_vp_col_num = pt_this->pt_act_bwr->t_bwr_prop.t_range_info.ui1_col_num;
    pt_this->ui1_vp_row_num = pt_this->pt_act_bwr->t_bwr_prop.t_range_info.ui1_row_num;

    if(MMP_BE_BWR_FLAG_ADD_PARENT_ITEM & ui2_bwr_flag)
    {
        pt_this->b_add_parent = TRUE;
    }
    else
    {
        pt_this->b_add_parent = FALSE;
    }

    /* Set SRM mode and DRC mode*/
    _mmp_be_upd_res_mode(pt_this);
    
    DBG_INFO_DIRECT("[mmp be] %s %d e_status:%d e_filter_type:%d\r\n",__FUNCTION__,__LINE__,pt_this->e_status,pt_this->e_filter_type);

    if (MMP_BE_STATUS_NONE == pt_this->e_status)
    {
        /*First timer activate*/
        pt_this->e_crt_inst_idx = _MMP_BE_FF_INST_IDX_0;

        /* Set type info to be */
        mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE,
                        (VOID*)pt_this->e_filter_type);

        do{
            if(0 == (MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL & ui2_bwr_flag))
            {
                pt_this->e_status = MMP_BE_STATUS_CHOOSE_FF;
                break;
            }
            else if (0 == (MMP_BE_BWR_FLAG_SKIP_MNT_PNT_SEL & ui2_bwr_flag))
            {
                i4_ret = _mmp_be_is_mnt_state_avail(pt_this, &ui4_mnt_count, &b_is_avail);
                if (MMPR_OK == i4_ret && b_is_avail)
                {
                    pt_this->e_status = MMP_BE_STATUS_CHOOSE_MNT;
                    break;
                }
            }
            pt_this->e_status = MMP_BE_STATUS_NORMAL;
        }while (0);
    }
    else if (MMP_BE_STATUS_PLAYER_ACT == pt_this->e_status)
    {
        /*Back from player*/
        /*Convert focus file index send from MMC*/
        mmp_ff_convert_adv_filter_idx(ui1_ff_id,
                                      FALSE,
                                      ui4_file_idx,
                                      &pt_this->ui4_focus_item_idx);
        i4_ret = mmp_ff_get_item_num(ui1_ff_id, &ui4_dir_num, &ui4_file_num);
        if(MMPR_OK == i4_ret)
        {
            pt_this->ui4_focus_item_idx += ui4_dir_num;
        }

        /* For preview item index*/
        if (MMP_NULL_FILE_IDX != pt_this->ui4_preview_item_idx)
        {
            pt_this->ui4_focus_item_idx = pt_this->ui4_preview_item_idx;
            pt_this->ui4_preview_item_idx = MMP_NULL_FILE_IDX;
        }

        mmp_ff_apply_flag_filter(ui1_ff_id, MMP_FF_ITEM_FLAG_EMPTY);
        pt_this->e_status = MMP_BE_STATUS_NORMAL;
    }

    /*current status is choose ff, show page event there is no device */
    if(pt_this->e_status != MMP_BE_STATUS_CHOOSE_FF)
    {
        /*Get current path*/
        i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
        if (MMPR_OK != i4_ret || MMP_BE_IS_EMPTY_PATH(s_curr_path))
        {
        #ifndef APP_CAST_TV_MMP_FG
            return _mmp_be_act_dev_invalid_handler(pt_this);
        #else
            /* no device */
            MMP_DBG_ERROR(("<mmp> %s,%d,i4_ret:%d,path:%s\n\r",__FILE__,__LINE__,i4_ret,s_curr_path));
        #endif
        }

        /*If active device is removed, handle this event advance */
        i4_ret = a_rmv_dev_is_path_valid(s_curr_path, &b_is_valid);
        if (i4_ret != RMVR_OK || b_is_valid == FALSE)
        {
        #ifndef APP_CAST_TV_MMP_FG
            return _mmp_be_act_dev_invalid_handler(pt_this);
        #else
            /* no device */
            MMP_DBG_ERROR(("<mmp> %s,%d,i4_ret:%d,path:%s,valid:%d\n\r",__FILE__,__LINE__,i4_ret,s_curr_path,b_is_valid));
        #endif
        }
    }

    /* Update the media type info on browser page.  */
    pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_XNG;
    if((ui1_bwr_id == MMP_RC_BROWSER_ID_THUMBNAIL) &&
       (pt_this->e_status == MMP_BE_STATUS_CHOOSE_FF))
    {
        /* Do not show the control panel */
    }
    else
    {
        /* Update the browse, playing file info */
        /* DTV00081986 SHOW control panel first, and then be hide due to the audio is stopped */
        pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO;
    }   
    DBG_INFO_DIRECT("[mmp be] %s %d <MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO> e_status:%d \r\n",__FUNCTION__,__LINE__,pt_this->e_status);
    pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);


    /*Peform operation according to current status*/
    switch (pt_this->e_status)
    {
        case MMP_BE_STATUS_CHOOSE_FF:
            i4_ret = _mmp_be_choose_media_type(pt_this);
            break;
        case MMP_BE_STATUS_CHOOSE_MNT:
            i4_ret = _mmp_be_choose_mnt_pnt(pt_this);
            break;
        case MMP_BE_STATUS_NORMAL:
            i4_ret = _mmp_be_get_item_list(pt_this, &pt_this->at_ff_inst[pt_this->e_crt_inst_idx], s_curr_path);
            break;
        default:
            break;
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_inactivate
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_inactivate(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    _mmp_be_stop_preview(pt_this);

    pt_this->ui1_act_bwr_id = MMP_MC_BWR_ID_NULL;
    return MMPR_OK;
}

static INT32 _mmp_be_check_media_remove(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    RMV_DEV_CHECK_RESULT_T e_check_result = RMV_DEV_NOT_FOUND_DEVICE;
    SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;
    INT32  i4_ret = MMPR_OK;
    UINT32 ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;

    e_check_result = a_rmv_dev_check_device();
    if ((RMV_DEV_NOT_FOUND_DEVICE == e_check_result)
        ||(RMV_DEV_FOUND_UNSUPPORTED_DEVICE == e_check_result))
    {
        if (RMV_DEV_CUSTOM_CURRENT_WITH_USB & pt_this->e_rmv_dev_current_status)
        {
            ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_USB;
        }
        else if (RMV_DEV_CUSTOM_CURRENT_WITH_DLNA & pt_this->e_rmv_dev_current_status)
        {
            ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_DLNA;
        }
        else
        {
            if (RMV_DEV_CUSTOM_CURRENT_WITH_DLNA & pt_this->e_rmv_dev_previous_status)
            {
                ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_DLNA;
            }
            else
            {
                ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_USB;
            }
        }

        i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                           (VOID*) &ui4_exit_reason, z_size);
        DBG_INFO(("i4_ret = %d\n", i4_ret));

    #ifndef APP_CAST_TV_MMP_FG

    #ifdef APP_TTS_SUPPORT
        /* exit mmp not to read banner tts */
        MMP_DBG_INFO(("mmp set banner tts disable %s,%d\n\r",__FILE__,__LINE__));
        set_banner_tts_enable(FALSE);
    #endif

    #ifdef APP_NAV_USB_PLD
        a_nav_active_component(NAV_COMP_ID_USB_PLD);
    #endif

    #else
        MMP_DBG_INFO(("<mmp> inp to cast %s,%d\n\r",__FILE__,__LINE__));
        mmp_foreground_chg_inp_src_to_cast();
    #ifdef APP_MENU_MMP_COEXIST
        extern BOOL menu_custom_is_blank_screen(VOID);
        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            if(menu_custom_is_blank_screen())
            {
                a_amb_clean_stack();
            }
            a_amb_pause_app(MENU_NAME);
            a_mmp_pause_background_mmp();
        }
        else
    #endif
        {
            a_amb_pause_app(MMP_NAME);
        }
    #endif

        return -100;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_default_msg_hdlr
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_default_msg_hdlr(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret;
    MMP_BE_UI_INFO_T        t_be_ui_info;
    UINT32                  ui4_dir_num = 0;

    c_memset(&t_be_ui_info, 0 , sizeof(MMP_BE_UI_INFO_T));
    MMP_DBG_INFO(("[mmp] %s %  e_msg_id = %d\n",__FUNCTION__,__LINE__,e_msg_id));
    switch (e_msg_id)
    {
        case MMP_MSG_ID_END_OF_PLAYLIST:
#ifdef MMP_GUI_AUTHORING
            if (MMP_GROUND_MODE_BACK == (MMP_GROUND_MODE_T)(INT32)pv_msg_param)
            {
                _mmp_be_bk_player_stop_hdlr(pt_this);
            }
#endif
            /*_mmp_thumbnailmode_bk_player_stop_hdlr*/
            break;

        case MMP_MSG_ID_APP_PAUSED:
            _mmp_be_reset();
            break;

        case MMP_MSG_ID_BROWSE_FILE_INFO_READY:
        {

        }
        break;

        case MMP_MSG_ID_MEDIA_UNSUPPORT:
            if (MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status)
            {
                _mmp_be_choose_mnt_pnt(pt_this);
            }
            break;

        case MMP_MSG_ID_MEDIA_INSERTED:
        {
            /*Get mount point count*/
            i4_ret = mmp_mc_device_get_mnt_count(&ui4_dir_num);
            if (MMPR_OK != i4_ret)
            {
                return i4_ret;
            }

            pt_this->e_rmv_dev_previous_status = pt_this->e_rmv_dev_current_status;
            a_rmv_dev_custom_check_status(&pt_this->e_rmv_dev_current_status);

            if (1 == ui4_dir_num)
            {
                CHAR            s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
                SIZE_T          z_size = MMP_BE_MAX_PATH_LEN;

                pt_this->e_status = MMP_BE_STATUS_NORMAL;

                mmp_be_set_curr_path(NULL);

                /*Get current path*/
                i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                if (MMPR_OK != i4_ret)
                {
                    return i4_ret;
                }

                mmp_be_set_curr_path(s_curr_path);

                /*klocwork warning*/
                MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT,
                                    return MMPR_INTERNAL_ERROR);

                i4_ret = _mmp_be_get_item_list(pt_this,
                                               &pt_this->at_ff_inst[pt_this->e_crt_inst_idx],
                                               s_curr_path);
                if (MMPR_OK != i4_ret)
                {
                    return i4_ret;
                }

                t_be_ui_info.e_upd_field = MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG;

                i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&t_be_ui_info);
                IS_MMPR_OK(i4_ret);

                return MMPR_OK;
            }

            if (MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status)
            {
                _mmp_be_choose_mnt_pnt(pt_this);
            }
            else if((MMP_BE_STATUS_NORMAL == pt_this->e_status)||
                    (MMP_BE_STATUS_CHOOSE_FF == pt_this->e_status))
            {
                t_be_ui_info.e_upd_field = MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG;

                i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&t_be_ui_info);
                IS_MMPR_OK(i4_ret);
            }
        }
            break;
        case MMP_MSG_ID_MEDIA_REMOVED:
            {
                MMP_PLAY_STATE_T    e_music_state = MMP_PLAY_STATE_CLOSED;
                BOOL                b_is_valid    = FALSE;

                i4_ret = _mmp_be_check_media_remove();
                if (-100 == i4_ret)
                {
                    /* exit mmp status */
                    return 0;
                }

                pt_this->e_rmv_dev_previous_status = pt_this->e_rmv_dev_current_status;
                a_rmv_dev_custom_check_status(&pt_this->e_rmv_dev_current_status);

                /*Check if BK player is stopped*/
                mmp_mc_file_get_status(MMP_GROUND_MODE_BACK, &e_music_state);
                if (e_music_state != MMP_PLAY_STATE_PLAYED &&
                    e_music_state != MMP_PLAY_STATE_PAUSED)
                {
                    _mmp_be_bk_player_stop_hdlr(pt_this);
                }

                if (MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status)
                {
                    _mmp_be_choose_mnt_pnt(pt_this);
                }
                else if((MMP_BE_STATUS_NORMAL == pt_this->e_status)||
                        (MMP_BE_STATUS_CHOOSE_FF == pt_this->e_status) ||
                        (MMP_BE_STATUS_PLAYER_ACT == pt_this->e_status))
                {
                    i4_ret = a_rmv_dev_is_path_valid(pt_this->s_curr_path, &b_is_valid);
                    if (i4_ret != RMVR_OK || b_is_valid == FALSE)
                    {
                        return _mmp_be_act_dev_invalid_handler(pt_this);
                    }
                    else
                    {
                        t_be_ui_info.e_upd_field = MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG;

                        i4_ret = pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&t_be_ui_info);
                        IS_MMPR_OK(i4_ret);
                    }
                }
            }
            break;

        case MMP_MSG_ID_APP_PRE_RESUMED:
        {
            MMP_APP_RESUME_INFO_T e_info = (MMP_APP_RESUME_INFO_T)(UINT32)pv_msg_param;

            if (MMP_APP_RESUME_INFO_PHOTO_BWR == e_info)
            {
                pt_this->e_filter_type = MMP_MEDIA_TYPE_PHOTO;
            }
            else if (MMP_APP_RESUME_INFO_AUDIO_BWR == e_info)
            {
                pt_this->e_filter_type = MMP_MEDIA_TYPE_AUDIO;
            }
            else if (MMP_APP_RESUME_INFO_VIDEO_BWR == e_info)
            {
                pt_this->e_filter_type = MMP_MEDIA_TYPE_VIDEO;
            }
            else
            {
                pt_this->e_filter_type = MMP_MEDIA_TYPE_PHOTO;
            }

        }
        break;

        default:
            break;

    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_info
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_T e_info_id, VOID* pv_param)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    if (NULL == pv_param)
    {
        return MMPR_INV_ARG;
    }

    switch (e_info_id)
    {
        case MMP_BE_INFO_GET_INFO_ID_STATUS:
            *((MMP_BE_STATUS_T*)pv_param) = pt_this->e_status;
            break;
        case MMP_BE_INFO_GET_INFO_ID_SORT_TYPE:
            *((MMP_SORT_TYPE_T*)pv_param) = pt_this->e_sort;
            break;
        case MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE:
            *((MMP_MEDIA_TYPE_T*)pv_param) = pt_this->e_filter_type;
            break;
        case MMP_BE_INFO_GET_INFO_ID_FB_MODE:
            *((MMP_FB_MODE*)pv_param) = pt_this->e_fb_mode;
            break;
        case MMP_BE_INFO_GET_INFO_ID_FOCUS_ITEM_IDX:
            *((UINT32*)pv_param) = pt_this->ui4_focus_item_idx;
            break;
        case MMP_BE_INFO_GET_INFO_ID_FOCUS_FILE_IDX:
            *((UINT32*)pv_param) = pt_this->ui4_focus_file_idx;
            break;
        case MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE:
            *((BOOL*)pv_param) = pt_this->b_recursive_read;
            break;
        case MMP_BE_INFO_SET_INFO_ID_GET_PATH_FLAG:
            *((BOOL*)pv_param) = pt_this->e_set_path_flag;
            break;
        case MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE:
            *((UINT8*)pv_param) = pt_this->ui1_video_play_mode;
            break;
        default:
            return MMPR_INV_ARG;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_set_info
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_T e_info_id, VOID* pv_param)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    MMP_SORT_TYPE_T         e_new_sort = MMP_SORT_TYPE_NONE;
    UINT8                   ui1_cfg_value;
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    INT32                   i4_ret;

    switch (e_info_id)
    {
        /* Status */
        case MMP_BE_INFO_SET_INFO_ID_STATUS:
            pt_this->e_status = (MMP_BE_STATUS_T)(UINT32)pv_param;
            break;
        /* Sort type */
        case MMP_BE_INFO_SET_INFO_ID_SORT_TYPE:
        {
            e_new_sort = (MMP_SORT_TYPE_T)(UINT32)pv_param;
            if (pt_this->e_sort == e_new_sort)
            {
                break;
            }

            /*Check if sort type meet current media type*/
            if (FALSE == MMP_BE_IS_LEGAL_SORT_TYPE(pt_this->e_filter_type, e_new_sort))
            {
                return MMPR_INV_ARG;
            }

            /* Get focus index according to filter type*/
            _mmp_be_set_sort_type_to_acfg(e_new_sort);

            pt_this->e_sort = e_new_sort;

            /*klocwork*/
            MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

            mmp_ff_update_sort(pt_this->at_ff_inst[pt_this->e_crt_inst_idx].ui1_ff_id, e_new_sort);
            pt_this->b_need_reload_playlist = TRUE;
            mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                        _mmp_playlist_reflash,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL);
            break;
        }
        /* Media type  */
        case MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE:

            pt_this->e_filter_type = (MMP_MEDIA_TYPE_T)(UINT32)pv_param;
            switch ((MMP_MEDIA_TYPE_T)(UINT32)pv_param)
            {
                case MMP_MEDIA_TYPE_PHOTO:
                    pt_this->pf_filter_fct = mmp_util_filter_fct_by_image;
                    ui1_cfg_value = MMP_FILTER_MEDIA_TYPE_PHOTO;
                    /* need set repeat mode  to repeat*/
                    {
                        MMP_PL_ATTR_T     at_attr[1];
                        MMP_REPEAT_MODE_T rept =  MMP_REPEAT_MODE_ALL;

                        at_attr[0].e_id     = MMP_PL_ATTR_ID_FG_REPEAT;
                        at_attr[0].pv_param = (VOID*)rept;
                        mmp_mc_list_set_attr(1, at_attr);
                    }
                    DBG_INFO_DIRECT("[mmp be] %s %d <MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE> e_filter_type:%d media_type:PHOTO\r\n",__FUNCTION__,__LINE__,pt_this->e_filter_type);
                    break;
                case MMP_MEDIA_TYPE_AUDIO:
                    pt_this->pf_filter_fct = mmp_util_filter_fct_by_audio;
                    ui1_cfg_value = MMP_FILTER_MEDIA_TYPE_MUSIC;
                    /* need set repeat mode  to repeat*/
                    {
                        MMP_PL_ATTR_T     at_attr[1];
                        MMP_REPEAT_MODE_T rept =  MMP_REPEAT_MODE_ALL;

                        at_attr[0].e_id     = MMP_PL_ATTR_ID_BK_REPEAT;
                        at_attr[0].pv_param = (VOID*)rept;
                        mmp_mc_list_set_attr(1, at_attr);
                    }
                    DBG_INFO_DIRECT("[mmp be] %s %d <MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE> e_filter_type:%d media_type: AUDIO\r\n",__FUNCTION__,__LINE__,pt_this->e_filter_type);            
                    break;
                case MMP_MEDIA_TYPE_VIDEO:
                    pt_this->pf_filter_fct = mmp_util_filter_fct_by_video;
                    ui1_cfg_value = MMP_FILTER_MEDIA_TYPE_VIDEO;
                    DBG_INFO_DIRECT("[mmp be] %s %d <MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE> e_filter_type:%d media_type: VIDEO\r\n",__FUNCTION__,__LINE__,pt_this->e_filter_type);            
                    break;
                case MMP_MEDIA_TYPE_TEXT:
                    pt_this->pf_filter_fct = mmp_util_filter_fct_by_text;
                    ui1_cfg_value = MMP_FILTER_MEDIA_TYPE_TEXT;

                    break;
                default:
                    pt_this->pf_filter_fct = NULL;
                    ui1_cfg_value = MMP_FILTER_MEDIA_TYPE_PHOTO;
            }

            /* Set acfg */
            a_cfg_set_mmp_media_type(ui1_cfg_value);

            /* Get sort type */
            _mmp_be_get_sort_type_from_acfg(&e_new_sort);

            /* Set type info to be */
            pt_this->e_sort = e_new_sort;

            /* change the media type, so reset traverse done to false */
            _mmp_be_clean_all_traverse_done();

            /* reset focus index */
            pt_this->ui4_focus_item_idx = 0;

            /* Update the media type info on browser page.  */
            pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_XNG;
            pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

            if (MMP_BE_STATUS_NORMAL == pt_this->e_status)
            {
                mmp_mc_browse_reset_info_resoruce();
            }

            /* Stop preview */
            _mmp_be_stop_preview(pt_this);

            /* Set SRM mode and DRC mode*/
            _mmp_be_upd_res_mode(pt_this);

            /* Notify MMC active resource handler type*/
            mmp_mc_browse_set_act_res_hdlr_type(pt_this->e_filter_type);

            break;

        /* Browser mode  */
        case MMP_BE_INFO_SET_INFO_ID_FB_MODE:
            pt_this->e_fb_mode = (MMP_FB_MODE)(UINT32)pv_param;
            break;
        /* Focus item index */
        case MMP_BE_INFO_SET_INFO_ID_FOCUS_ITEM_IDX:
            pt_this->ui4_focus_item_idx = (UINT32)pv_param;
            break;
        /* Focus  file index */
        case MMP_BE_INFO_SET_INFO_ID_FOCUS_FILE_IDX:
            pt_this->ui4_focus_file_idx = (UINT32)pv_param;
            break;
        /* Recursive */
        case MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE:
        {
            if (pt_this->b_recursive_read == (BOOL)(UINT32)pv_param)
            {
                break;
            }

            _mmp_be_set_recur_parsing_to_acfg((BOOL)(UINT32)pv_param);

            pt_this->b_recursive_read = (BOOL)(UINT32)pv_param;

            /* change the Recursive type, so reset traverse done to false */
            _mmp_be_clean_all_traverse_done();

            /* reset the focus item idx */
            pt_this->ui4_focus_item_idx = 0;

            if(pt_this->b_recursive_read)
            {
                /* set current path to root path, it set to recursive */
                i4_ret = mmp_be_set_curr_path(NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret = mmp_be_get_curr_path(pt_this->s_curr_path,&z_size);
                MMPR_LOG_ON_FAIL(i4_ret);

                mmp_ff_update_sort(pt_this->at_ff_inst[pt_this->e_crt_inst_idx].ui1_ff_id,
                                   pt_this->e_sort);
            }
            pt_this->b_need_reload_playlist = TRUE;
            pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_CRNT_PATH_CHANGE;
            if(pt_this->pt_act_bwr)
               pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
        }
            break;
        /* Playlist only */
        case MMP_BE_INFO_SET_INFO_ID_SHOW_PLAYLIST_ONLY:
            pt_this->b_playlist_only = (BOOL)(UINT32)pv_param;
            break;
        /* Sort status  */
        case MMP_BE_INFO_SET_INFO_ID_SORT_STATUS_NFY:
            pt_this->pf_sort_status_nfy = (mmp_sort_status_nfy)pv_param;
            break;
        /* Range info  */
        case MMP_BE_INFO_SET_INFO_ID_VP_RANGE_INFO:
            pt_this->ui1_vp_row_num = ((MMP_BE_VP_RANGE_INFO_T*)pv_param)->ui1_row_num;
            pt_this->ui1_vp_col_num = ((MMP_BE_VP_RANGE_INFO_T*)pv_param)->ui1_col_num;
            /*mmp_ff_set_vp_range*/
            break;
        /* Preview info */
        case MMP_BE_INFO_SET_INFO_ID_PREVIEW_INFO:
            c_memcpy(&pt_this->t_preview_info, ((MMP_FP_PREVIEW_INFO_T*)pv_param), sizeof(MMP_FP_PREVIEW_INFO_T));
            break;
        case MMP_BE_INFO_SET_INFO_ID_SET_PATH_FLAG:
            pt_this->e_set_path_flag = (MMP_FF_SET_PATH_FLAG_T)(UINT32)pv_param;
            _mmp_be_clean_all_traverse_done();

            /* reset focus index */
            pt_this->ui4_focus_item_idx = 0;
            break;

        case MMP_BE_INFO_SET_INFO_ID_SET_ACT_MNT_POINT:
        {
            UINT32      ui4_mnt_idx = (UINT32)pv_param;
            SIZE_T      z_size;
            MMP_MC_DEV_UNSUPPORT_TYPE_T e_unsupt;

            do {
                i4_ret = mmp_mc_device_set_active_mnt_point(ui4_mnt_idx);
                if (MMPR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,ui4_mnt_idx=%d,i4_ret=%d\n",
                                __FILE__, __FUNCTION__, __LINE__,
                                ui4_mnt_idx, i4_ret));
                    break;
                }

                z_size = sizeof(MMP_MC_DEV_UNSUPPORT_TYPE_T);
                i4_ret = mmp_mc_device_get_mnt_point_info(ui4_mnt_idx,
                                                          MMP_MC_DEV_INFO_ID_UNSUPT_TYPE,
                                                          &z_size,
                                                          (VOID*)&e_unsupt);
                if (MMPR_OK != i4_ret || MMP_MC_DEV_UNSUPT_TYPE_NONE != e_unsupt)
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,ui4_mnt_idx=%d,i4_ret=%d,e_unsupt=%d\n",
                                __FILE__, __FUNCTION__, __LINE__,
                                ui4_mnt_idx, i4_ret, e_unsupt));
                    i4_ret = MMPR_FAIL;
                    break;
                }

                z_size = MMP_BE_MAX_PATH_LEN;
                i4_ret = mmp_mc_device_get_mnt_point(ui4_mnt_idx,
                                                     &z_size,
                                                     pt_this->s_curr_path);
                pt_this->ui4_focus_item_idx = 0;
            } while (0);

            return i4_ret;
        }
        case MMP_BE_INFO_SET_INFO_ID_SET_VIDEO_PLAY_MODE:
            pt_this->ui1_video_play_mode = (UINT8)((UINT32)pv_param);
            break;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_is_root_path
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
BOOL mmp_be_is_root_path(VOID)
{
     CHAR           s_curr_path[MMP_BE_MAX_PATH_LEN]={0};
     CHAR           s_mnt_point[MMP_BE_MAX_PATH_LEN];
     SIZE_T         z_size;
     UINT32         ui4_idx;
     INT32          i4_ret;

     do {
         z_size = MMP_BE_MAX_PATH_LEN;
         i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
         if (MMPR_OK != i4_ret)
         {
             break;
         }

         z_size = MMP_BE_MAX_PATH_LEN;
         i4_ret = mmp_mc_device_get_active_mnt_point (&ui4_idx, &z_size, s_mnt_point);
         if (MMPR_OK != i4_ret)
         {
             break;
         }

         if(c_strcmp(s_curr_path, s_mnt_point) != 0)
         {
             break;
         }

         return TRUE;
     } while (0);

     return FALSE;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_file_src_type
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_file_src_type(const CHAR* ps_pname, MMP_BE_FILE_SRC_TYPE_T* pe_type)
{
    RMV_DEV_DEVICE_STATUS_T e_dev_status;
    INT32                   i4_ret;
    MMP_BE_FILE_SRC_TYPE_T  e_type = MMP_BE_FILE_SRC_UNKNOWN;

    MMP_DBG_INFO(("[mmp] %s %d inputs path=%s \n",__FUNCTION__,__LINE__,ps_pname));

    do {
        i4_ret = a_rmv_dev_get_mnt_point_status_by_path(ps_pname, &e_dev_status);
        if (RMVR_OK != i4_ret)
        {
            /*
            c_dbg_secure_stmt("Error: a_rmv_dev_get_mnt_point_status_by_path return i4_ret, line=%d \n",i4_ret,__LINE__);
            c_dbg_secure_stmt("Error: a_rmv_dev_get_mnt_point_status_by_path inputs path=%s,file=%s,line=%d\n",ps_pname,__FILE__,__LINE__);
            */
            break;
        }

        if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            e_type = MMP_BE_FILE_SRC_DLNA;
        }
        else if(RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))
        {
            e_type = MMP_BE_FILE_SRC_NET_NEIGHBOR;
        }
        else
        {
            /* Not  find, set type to usb */
            e_type = MMP_BE_FILE_SRC_MASS_STRG;
        }

    } while (0);

    *pe_type = e_type;

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_curr_path
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_curr_path(CHAR* ps_pname, SIZE_T* pz_size)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;
    UINT32                      ui4_idx;
    SIZE_T                      z_size;
    INT32                       i4_ret = MMPR_OK;
    MMP_MC_DEV_UNSUPPORT_TYPE_T e_unsupt;
#ifdef APP_CAST_TV_MMP
    INT32                       i4_loop = 0;
    UINT32                      ui4_cnt = 0;
#endif
    if (NULL == ps_pname || NULL == pz_size)
    {
        return MMPR_INV_ARG;
    }
#ifdef APP_CAST_TV_MMP
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_cnt);
    if (i4_ret != RMVR_OK)
    {
        MMP_DBG_ERROR(("[%s:%d] get mnt point failed, ret = %d\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    for (i4_loop = ui4_cnt-1; i4_loop >= 0; i4_loop--)
    {
        i4_ret = a_rmv_dev_get_mnt_point(i4_loop, pz_size, ps_pname);
        if (i4_ret != RMVR_OK)
        {
            continue;
        }

        if (ps_pname != NULL && c_strstr(ps_pname, "/sd") != NULL)
        {
            break;
        }
    }

    i4_ret = a_rmv_dev_set_active_mnt_pnt(i4_loop);
    if (i4_ret != RMVR_OK)
    {
        DBG_LOG_PRINT(("[%s:%d] set active mnt point failed, ret = %d\n", __FUNCTION__, __LINE__, i4_ret));
    }
#endif
    do {
        if (c_strlen(pt_this->s_curr_path) > 0)
        {
            break;
        }

        /*Query active mount point*/
        z_size = MMP_BE_MAX_PATH_LEN;
        i4_ret = mmp_mc_device_get_active_mnt_point (&ui4_idx, &z_size, pt_this->s_curr_path);
        MMP_DBG_INFO(("<mmp> %s,%d,i4_ret:%d,path:%s\n\r",__FILE__,__LINE__,i4_ret,pt_this->s_curr_path));
        if(MMPR_OK != i4_ret)
        {
            pt_this->s_curr_path[0] = '\0';
            break;
        }

        /*Query mount point status*/
        z_size = sizeof(MMP_MC_DEV_UNSUPPORT_TYPE_T);
        i4_ret = mmp_mc_device_get_mnt_point_info(ui4_idx,
                                                  MMP_MC_DEV_INFO_ID_UNSUPT_TYPE,
                                                  &z_size,
                                                  (VOID*)&e_unsupt);
        if(MMPR_OK != i4_ret)
        {
            pt_this->s_curr_path[0] = '\0';
            break;
        }
        if(MMP_MC_DEV_UNSUPT_TYPE_NONE != e_unsupt)
        {
            c_strcpy(pt_this->s_curr_path, MMP_BE_EMPTY_PATH);
        }
    } while (0);

    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("<mmp> %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        return i4_ret;
    }

    if (c_strlen(pt_this->s_curr_path) > *pz_size)
    {
        *pz_size = c_strlen(pt_this->s_curr_path);
        return MMPR_BUF_NOT_ENOUGH;
    }

    c_strcpy(ps_pname, pt_this->s_curr_path);
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_curr_path_display
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_curr_path_display(UTF16_T* pw2s_text,
                                               UTF16_T** ppw2s_final_path,
                                               SIZE_T* pz_size)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;
    CHAR                        s_curr_path[MMP_BE_MAX_PATH_LEN+1]={0};
    CHAR                        s_curr_path_temp[MMP_BE_MAX_PATH_LEN+6]={0};
    CHAR                        s_curr_path_temp_2[MMP_BE_MAX_PATH_LEN+6]={0};
    UTF16_T                     w2s_curr_path_temp_2[MMP_BE_MAX_PATH_LEN+15]={0};
    CHAR                        s_curr_path_temp_3[10]={0};
    UTF16_T                     w2s_curr_path_temp_3[MMP_BE_MAX_PATH_LEN+15]={0};
    UTF16_T                     w2s_curr_path_temp_4[MMP_BE_MAX_PATH_LEN+15]={0};
    CHAR                        s_curr_path_temp_end[MMP_BE_MAX_PATH_LEN+1]={0};
    UTF16_T                     w2s_text[MMP_BE_MAX_PATH_LEN+15]={0};
    UINT16                      ui2_i = 0;
    UINT16                      ui2_j = 0;
    SIZE_T                      z_full_path_len;
    SIZE_T                      z_short_path_len;
    SIZE_T                      z_mnt_path_len;
    SIZE_T                      z_root_mlm_len = 0;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    INT32                       i4_ret = MMPR_OK;
    CHAR                        ac_path[MMP_BE_MAX_PATH_LEN] = {0};
    CHAR                        ac_info[MMP_BE_MAX_PATH_LEN] = {0};
    UINT32                      ui4_len = MMP_BE_MAX_PATH_LEN;
    UINT32                      ui4_idx = 0;
    SIZE_T                      t_size = MMP_BE_MAX_PATH_LEN;
    MMP_MEDIA_TYPE_T            e_type = MMP_MEDIA_TYPE_UNKNOWN;
    CHAR*                       s_curr_path_file_item;
    ISO_639_LANG_T              s639_lang;
    UINT16                      ui2_lang = 0;

    if (NULL == pw2s_text || NULL == pz_size)
    {
        return MMPR_INV_ARG;
    }

    if((MMP_BE_STATUS_CHOOSE_FF == pt_this->e_status)||
       (MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status))
    {
        w2s_text[0] = '\0';
    }
    else
    {
        i4_ret = mmp_be_get_curr_path(s_curr_path,
                             &t_size);
        MMPR_LOG_ON_FAIL(i4_ret);
        mmp_mc_device_get_active_mnt_point(&ui4_idx,
                                           &t_size,
                                           ac_path);

       /*query mount point status*/
       i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_idx,
                                                      &e_dev_status);
       IS_MMPR_OK(i4_ret);

       if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
           (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
           (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
       {
           return MMPR_FAIL;
       }

       if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
       {
           t_size = MMP_BE_MAX_PATH_LEN;
           i4_ret = a_rmv_dev_get_mnt_point_info(ui4_idx,
                                                 RMV_DEV_INFO_ID_DESC,
                                                 &t_size,
                                                 (VOID*)(&ac_info));
           IS_MMPR_OK(i4_ret);
       }
       else
       {
           i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                          ac_path,
                                          ac_info,
                                          &ui4_len);
           IS_MMPR_OK(i4_ret);
       }

       i4_ret = c_uc_ps_to_w2s(ac_info,
                               pw2s_text,
                               *pz_size);
       if ((i4_ret != UCR_OK)
           && (i4_ret != UCR_NO_ENOUGH_BUFFER))
       {
           MMP_DBG_ERROR(("c_uc_ps_to_w2s retrun error! i4_ret=%d,line=%d \n",i4_ret,__LINE__));
           w2s_text[0] = 0;
           return MMPR_FAIL;
       }
       else if (UCR_NO_ENOUGH_BUFFER == i4_ret)
       {
           return MMPR_BUF_NOT_ENOUGH;
       }

       i4_ret = a_cfg_get_gui_lang(s639_lang);
       MMPR_LOG_ON_FAIL(i4_ret);

       ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);

       c_memset(s_curr_path_temp, 0, sizeof(s_curr_path_temp));

       z_mnt_path_len = c_strlen(ac_path);
       z_full_path_len = c_strlen(s_curr_path);
       z_short_path_len = z_full_path_len - z_mnt_path_len;
       if(z_full_path_len < z_mnt_path_len)
       {
           return MMPR_FAIL;
       }
       else if(z_mnt_path_len == 0)
       {
           w2s_text[0] = '\0';
       }
       else
       {
           /*before design is '\root',the first 5 idx of s_curr_path_temp  to save it,so can not change its lang*/
           /*later design is use mlm,'\MLM_MMP_KEY_FILE_PATH_ROOT',then change it to char,last save it in s_curr_path_temp*/
           c_uc_w2s_strcpy(w2s_curr_path_temp_4, L"\\");

           c_uc_w2s_strcat(w2s_curr_path_temp_4,
                           MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_FILE_PATH_ROOT));
           c_uc_w2s_to_ps(w2s_curr_path_temp_4,s_curr_path_temp_3,10);
           z_root_mlm_len = c_strlen(s_curr_path_temp_3);

           c_strncpy(s_curr_path_temp,
                         s_curr_path_temp_3,
                         z_root_mlm_len);

           if(z_short_path_len == 0)
           {

               s_curr_path_temp[z_root_mlm_len]='\0';
           }
           else if(z_short_path_len < MMP_BE_MAX_PATH_LEN)
           {
               s_curr_path_temp[z_root_mlm_len] = '\\';
               c_strncpy(&s_curr_path_temp[z_root_mlm_len+1],
                         &s_curr_path[z_mnt_path_len+1],
                         z_short_path_len);
               s_curr_path_temp[z_short_path_len+z_root_mlm_len]='\0';
           }
           else
           {
               c_strncpy(&s_curr_path_temp[z_root_mlm_len+1],
                         &s_curr_path[z_mnt_path_len+1],
                         MMP_BE_MAX_PATH_LEN-1);
               s_curr_path_temp[MMP_BE_MAX_PATH_LEN+z_root_mlm_len-1]='\0';
           }
       }

        /* klocwork */
        while(ui2_i < (MMP_BE_MAX_PATH_LEN+z_root_mlm_len) &&
              s_curr_path_temp[ui2_i]!='\0')
        {
            if(ui2_i < (MMP_BE_MAX_PATH_LEN+z_root_mlm_len) &&
               s_curr_path_temp[ui2_i]=='/')
            {
                s_curr_path_temp[ui2_i]='\\';
            }
            ui2_i++;
        }

        ui2_i = 0;
        while(ui2_i < (MMP_BE_MAX_PATH_LEN+z_root_mlm_len) &&
              s_curr_path_temp[ui2_i]!='\0')
        {
            if(ui2_i < (MMP_BE_MAX_PATH_LEN+z_root_mlm_len) &&
               s_curr_path_temp[ui2_i]=='\\')
            {

                ui2_j = ui2_i+1;
                while(ui2_j < (MMP_BE_MAX_PATH_LEN+z_root_mlm_len))
                {
                    if((s_curr_path_temp[ui2_j]=='\0')||
                       (s_curr_path_temp[ui2_j]=='\\'))
                    {

                        c_strncpy(s_curr_path_temp_end,
                                  &s_curr_path_temp[ui2_i+1],
                                  (ui2_j-ui2_i-1));
                        /* klocwork warning */
                        if(((ui2_j-ui2_i-1) >= 0)&&
                           ((ui2_j-ui2_i-1) <= MMP_BE_MAX_PATH_LEN))
                        {
                            s_curr_path_temp_end[ui2_j-ui2_i-1] = '\0';
                        }

                        c_strcat(s_curr_path_temp_2,
                                 "\\\0");

                        /* do not trim the root prefix. */
                        if ((z_root_mlm_len == ui2_j)
                            &&('\\' == s_curr_path_temp[ui2_j-z_root_mlm_len])
                            &&('r' == s_curr_path_temp[ui2_j-z_root_mlm_len+1]))// to get multi-lang mlm 'root'
                        {
                            c_strcat(s_curr_path_temp_2,
                                     s_curr_path_temp_end);
                        }
                        else
                        {
                            s_curr_path_file_item = mmp_be_get_filtered_item_name(s_curr_path_temp_end);
                            c_strcat(s_curr_path_temp_2,
                                     s_curr_path_file_item);
                        }

                        break;
                    }
                    ui2_j++;
                }
            }
            ui2_i++;
        }

        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                        (VOID*)&e_type);
        c_uc_w2s_strcpy(w2s_curr_path_temp_3, L"\\");
        switch(e_type)
        {
            case MMP_MEDIA_TYPE_PHOTO:
                c_uc_w2s_strcat(w2s_curr_path_temp_3,
                                MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_MEDIA_TYPE_OPTION_PHOTO));
                break;
            case MMP_MEDIA_TYPE_AUDIO:
               c_uc_w2s_strcat(w2s_curr_path_temp_3,
                                MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_MEDIA_TYPE_OPTION_MUSIC));
                break;
            case MMP_MEDIA_TYPE_VIDEO:
                c_uc_w2s_strcat(w2s_curr_path_temp_3,
                                MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_MEDIA_TYPE_OPTION_VIDEO));
                break;
            case MMP_MEDIA_TYPE_TEXT:
                c_uc_w2s_strcat(w2s_curr_path_temp_3,
                                MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_MEDIA_TYPE_OPTION_TEXT));
                break;

            default:
                break;
        }

        c_uc_ps_to_w2s(s_curr_path_temp_2, w2s_curr_path_temp_2,
                        MMP_BE_MAX_PATH_LEN+6);

        c_uc_w2s_strcat(w2s_curr_path_temp_3,
                 w2s_curr_path_temp_2);

        c_uc_w2s_strncpy(w2s_text, w2s_curr_path_temp_3,
                       MMP_BE_MAX_PATH_LEN+15);
    }

    if (c_uc_w2s_strlen(w2s_text) + c_uc_w2s_strlen(pw2s_text) > *pz_size)
    {
        *pz_size = c_uc_w2s_strlen(w2s_text) + c_uc_w2s_strlen(pw2s_text);
        return MMPR_BUF_NOT_ENOUGH;
    }
    c_uc_w2s_strcat(pw2s_text, w2s_text);

    if (ppw2s_final_path)
    {
        UTF16_T                     w2s_seprate[MMP_BE_PATH_SEPRATE_LEN + 1] = {0};
        c_uc_ps_to_w2s("\\", w2s_seprate, MMP_BE_PATH_SEPRATE_LEN + 1);

        ui2_i = c_uc_w2s_strlen(pw2s_text);

        for ( ; ui2_i > 0; ui2_i--)
        {
            if (pw2s_text[ui2_i - 1] == w2s_seprate[0])
            {
                break;
            }
        }

        *ppw2s_final_path = pw2s_text + ui2_i;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_curr_path
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_focus_path(CHAR* ps_pname, SIZE_T* pz_size)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;

    if (NULL == ps_pname || NULL == pz_size)
    {
        return MMPR_INV_ARG;
    }

    if (c_strlen(pt_this->s_curr_focus_path) > 0)
    {
        c_strncpy(pt_this->s_curr_focus_path,pt_this->s_curr_path,MMP_BE_MAX_PATH_LEN);
    }

    if (c_strlen(pt_this->s_curr_focus_path) > *pz_size)
    {
        *pz_size = c_strlen(pt_this->s_curr_focus_path);
        return MMPR_BUF_NOT_ENOUGH;
    }

    c_strcpy(ps_pname, pt_this->s_curr_focus_path);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_is_traverse_down
 * @retval  TRUE         The folder is traverse_done.
 * @retval  FALSE        The folder is not yet traverse_done.
 */
/*---------------------------------------------------------------------------*/
BOOL mmp_be_is_traverse_down(MMP_BE_FF_IDX e_ff_idx)
{
    MMP_BE_FF_INST_T*   pt_inst;
    INT32               i4_ret;

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        e_ff_idx,
                                        &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return pt_inst->b_traverse_done;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_is_empty_folder
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_is_empty_folder(MMP_BE_FF_IDX e_ff_idx, BOOL* pb_is_empty)
{
    UINT32      ui4_dir_num, ui4_file_num;

    if (!mmp_be_is_traverse_down(e_ff_idx))
    {
        return MMPR_IS_LOADING;
    }

    IS_MMPR_OK (mmp_be_get_item_num(e_ff_idx, &ui4_dir_num, &ui4_file_num));
    if (ui4_dir_num == 0 && ui4_file_num == 0)
    {
        *pb_is_empty = TRUE;
    }
    else
    {
        *pb_is_empty = FALSE;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_ff_path_name
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_ff_path_name(MMP_BE_FF_IDX e_ff_idx, CHAR** ps_pname)
{
    MMP_BE_FF_INST_T*   pt_inst;
    INT32               i4_ret;

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        e_ff_idx,
                                        &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    *ps_pname = pt_inst->s_pname;
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_item_num
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_item_num(MMP_BE_FF_IDX e_ff_idx, UINT32* pui4_dir_num, UINT32* pui4_file_num)
{
    MMP_BE_FF_INST_T*   pt_inst;
    INT32               i4_ret = MMPR_FAIL;

    if(t_g_browse_eng.e_status == MMP_BE_STATUS_CHOOSE_FF)
    {
        *pui4_file_num = 0;
        *pui4_dir_num  = _mmp_be_get_media_type_count();

        return MMPR_OK;

    }
    else if(t_g_browse_eng.e_status == MMP_BE_STATUS_CHOOSE_MNT)
    {
        *pui4_file_num = 0;
        return mmp_mc_device_get_mnt_count(pui4_dir_num);

    }
    else
    {
        i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                            e_ff_idx,
                                            &pt_inst);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }

        return mmp_ff_get_item_num (pt_inst->ui1_ff_id,
                                    pui4_dir_num,
                                    pui4_file_num);

    }
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_item_info
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_item_info(MMP_BE_FF_IDX e_ff_idx,
                           MMP_ITEM_TYPE_T e_filter_type,
                           UINT32 ui4_idx_start,
                           UINT32* pui4_cnt,
                           MMP_ITEM_INFO_T* pt_item_info)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;
    INT32                       i4_ret = MMPR_FAIL;
    UINT32                      ui4_dir_num, ui4_file_num;
    MMP_BE_FF_INST_T*           pt_inst;

    if(pui4_cnt == NULL || pt_item_info == NULL)
    {
        DBG_LOG_PRINT(("mmp_be_get_item_info_ex line=%d,MMPR_INV_ARG!\n",__LINE__));
        return MMPR_INV_ARG;
    }

    i4_ret = _mmp_be_get_ff_inst_by_idx(pt_this, e_ff_idx, &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    if (ITEM_TYPE_DIR == e_filter_type || ITEM_TYPE_FILE == e_filter_type)
    {
        i4_ret = mmp_ff_get_item_info (pt_inst->ui1_ff_id,
                                       e_filter_type,
                                       ui4_idx_start,
                                       pui4_cnt,
                                       pt_item_info);
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT(("mmp_be_get_item_info_ex line=%d call mmp_ff_get_item_info error return=%d.\n",__LINE__,i4_ret));
        }

        return i4_ret;
    }
    else if (ITEM_TYPE_NONE == e_filter_type)
    {
        do {

            /*Get dir number and file number within current folder*/
            i4_ret = mmp_be_get_item_num(e_ff_idx, &ui4_dir_num, &ui4_file_num);
            if (MMPR_OK != i4_ret)
            {
                break;
            }

            if (ui4_idx_start + *pui4_cnt - 1 < ui4_dir_num)
            {
                /*All items are dir*/
                i4_ret = mmp_ff_get_item_info (pt_inst->ui1_ff_id,
                                               ITEM_TYPE_DIR,
                                               ui4_idx_start,
                                               pui4_cnt,
                                               pt_item_info);
            }
            else if (ui4_idx_start >= ui4_dir_num)
            {
                /*All items are file*/
                i4_ret = mmp_ff_get_item_info (pt_inst->ui1_ff_id,
                                               ITEM_TYPE_FILE,
                                               ui4_idx_start - ui4_dir_num,
                                               pui4_cnt,
                                               pt_item_info);
            }
            else
            {
                UINT32   ui4_req_dir_num, ui4_req_file_num;

                /*Get dir items*/
                ui4_req_dir_num = ui4_dir_num - ui4_idx_start;
                i4_ret = mmp_ff_get_item_info (pt_inst->ui1_ff_id,
                                               ITEM_TYPE_DIR,
                                               ui4_idx_start,
                                               &ui4_req_dir_num,
                                               pt_item_info);
                if (MMPR_OK != i4_ret)
                {
                    break;
                }
                /*Check result*/
                if (ui4_req_dir_num != ui4_dir_num - ui4_idx_start)
                {
                    i4_ret = MMPR_INV_ARG;
                    break;
                }

                /*Get file items*/
                ui4_req_file_num = *pui4_cnt - ui4_req_dir_num;
                i4_ret = mmp_ff_get_item_info (pt_inst->ui1_ff_id,
                                               ITEM_TYPE_FILE,
                                               ui4_dir_num, /*Start index of file item*/
                                               &ui4_req_file_num,
                                               pt_item_info+ui4_req_dir_num);
                *pui4_cnt = ui4_req_dir_num + ui4_req_file_num;
            }
        } while (0);
        return i4_ret;
    }
    else
    {
        return MMPR_INV_ARG;
    }
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_refresh
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_refresh(MMP_BE_FF_IDX e_ff_idx, MMP_BE_REFRESH_REASON_T e_reason)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret = MMPR_FAIL;

    /*Refresh item list for specified e_ff_idx*/
    /* change the item list */

    /*  stop bk audio  */
    mmp_be_stop_bg_player();

    switch(pt_this->e_status)
    {
        case MMP_BE_STATUS_CHOOSE_FF:
        {

        }
        break;

        case MMP_BE_STATUS_CHOOSE_MNT:
        {
            if(MMP_BE_REFRESH_TYPE_MNT_LST == e_reason)
            {
#ifdef APP_NET_DLNA_SUPPORT
                if(c_fm_dlna_is_device_alive())
                {
                    c_dm_dlna_dmp_refresh_dms_state();
                }
#endif

            }
        }
        break;

        case MMP_BE_STATUS_NORMAL:
        {
            if(MMP_BE_REFRESH_TYPE_ITEM_LST == e_reason)
            {
                /*klocwork*/
                MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

                i4_ret = _mmp_be_get_item_list(pt_this, &pt_this->at_ff_inst[pt_this->e_crt_inst_idx],pt_this->s_curr_path);
                IS_MMPR_OK(i4_ret);
            }

        }
        break;

        default :
            break;

    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_switch_browser
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_switch_browser(UINT8 ui1_bwr_id, BOOL b_reset)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    /* change the sort type, so reset traverse done to false */
    _mmp_be_clean_all_traverse_done();

    _mmp_be_traverse_done_stack_transfer_bws(pt_this->ui1_act_bwr_id,ui1_bwr_id);

    return mmp_mc_browse_enter(ui1_bwr_id, pt_this->ui4_focus_item_idx, TRUE);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_switch_browser
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_cd_child(UINT32 ui4_focus_idx)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret = MMPR_FAIL;
    BOOL                    b_enter_dev = FALSE, b_cd_sub_fldr = FALSE, b_play_file = FALSE;
    UINT32                  ui4_cnt = 0;
    BOOL                    b_is_mnt_avail;
    MMP_ITEM_INFO_T         t_item_info;
    CHAR                    s_full_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_BE_STATUS_T         e_status_old = MMP_BE_STATUS_NONE;
    UINT32                  ui4_mnt_idx = 0;

    c_memset(&t_item_info, 0, sizeof(MMP_ITEM_INFO_T));

    e_status_old = pt_this->e_status;

    pt_this->ui4_focus_item_idx = 0;

    if (MMP_BE_STATUS_CHOOSE_FF == pt_this->e_status)
    {
        /*  stop bk audio  */
        mmp_be_stop_bg_player();

        i4_ret = _mmp_be_is_mnt_state_avail(pt_this, &ui4_cnt, &b_is_mnt_avail);
        if (MMPR_OK != i4_ret || ui4_cnt == 0)
        {
            /*No any device*/
        }
        else if (b_is_mnt_avail)
        {
            #if 1
            /* Update the browse, playing file info */
            pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME;
            pt_this->t_last_notify.e_upd_field |= MMP_BE_UI_UPD_FIELD_FOLDER_XNG;
            pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

            pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO;
            pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
            #endif
            /*Multiple devices*/
            return _mmp_be_choose_mnt_pnt(pt_this);
        }
        else
        {
            #if 1
            /* Update the browse, playing file info */
            pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME;
            pt_this->t_last_notify.e_upd_field |= MMP_BE_UI_UPD_FIELD_FOLDER_XNG;
            pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);

            pt_this->t_last_notify.e_upd_field = MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO;
            pt_this->pt_act_bwr->t_bwr_hdlr.pf_data_change(&pt_this->t_last_notify);
            #endif

            ui4_mnt_idx = 0;
            b_enter_dev = TRUE;
        }
    }
    else if (MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status)
    {
        ui4_mnt_idx = ui4_focus_idx;
        b_enter_dev = TRUE;
    }
    else if (MMP_BE_STATUS_NORMAL == pt_this->e_status)
    {
        if (ITEM_TYPE_DIR == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT, ui4_focus_idx))
        {
            b_cd_sub_fldr = TRUE;

            /* Update focus item index */
            _mmp_be_traverse_done_stack_push(ui4_focus_idx);
        }
        else
        {
            b_play_file = TRUE;
        }
    }

    /*Perform operation according to above check result*/
    if (b_enter_dev)
    {
        SIZE_T      z_size = sizeof(MMP_MC_DEV_UNSUPPORT_TYPE_T);
        MMP_MC_DEV_UNSUPPORT_TYPE_T e_unsupt;
        i4_ret = mmp_mc_device_get_mnt_point_info(ui4_mnt_idx,
                                                  MMP_MC_DEV_INFO_ID_UNSUPT_TYPE,
                                                  &z_size,
                                                  (VOID*)&e_unsupt);
        if (MMPR_OK == i4_ret && MMP_MC_DEV_UNSUPT_TYPE_NONE == e_unsupt)
        {
            z_size = MMP_BE_MAX_PATH_LEN;
            i4_ret = mmp_mc_device_get_mnt_point(ui4_mnt_idx,
                                                 &z_size,
                                                 pt_this->s_curr_path);
            if (MMPR_OK != i4_ret)
            {
                return i4_ret;
            }

            /* set status to normal before get item list, reload data will check current status. */
            pt_this->e_status = MMP_BE_STATUS_NORMAL;

            /*klocwork*/
            MMP_RET_WITH_ASSERT(pt_this->e_crt_inst_idx < _MMP_BE_FF_INST_IDX_CNT, return MMPR_INTERNAL_ERROR);

            i4_ret = _mmp_be_get_item_list(pt_this, &pt_this->at_ff_inst[pt_this->e_crt_inst_idx], pt_this->s_curr_path);
            if (MMPR_OK != i4_ret)
            {
                /* set status to choose mount, if get item error! */
                pt_this->e_status = e_status_old;

                return i4_ret;
            }
        }
        else
        {
            mmp_be_set_curr_path(MMP_BE_EMPTY_PATH);
        }
    }
    else if (b_cd_sub_fldr || b_play_file)
    {
        /*Get focus item info*/
        ui4_cnt = 1;
        i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                      ITEM_TYPE_NONE,
                                      ui4_focus_idx,
                                      &ui4_cnt,
                                      &t_item_info);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }

        if (b_cd_sub_fldr)
        {
            MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);
            mmp_be_set_curr_path(s_full_path);

            /* Empty select list */
            mmp_be_empty_crt_folder_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST);

            pt_this->e_crt_inst_idx = (_MMP_BE_FF_INST_IDX_0 == pt_this->e_crt_inst_idx) ?
                                      _MMP_BE_FF_INST_IDX_1 : _MMP_BE_FF_INST_IDX_0;

            i4_ret = _mmp_be_get_item_list(pt_this, &pt_this->at_ff_inst[pt_this->e_crt_inst_idx], s_full_path);
            if (MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
        }
        else
        {
            MMP_FP_PRESENT_MODE_T           e_present_mode;
            MMP_PL_PLAY_CMD_PARAM_ITEM_T    t_play_param;
            mmp_mc_list_get_play_present_mode(&e_present_mode);
            DBG_LOG_PRINT(("[MMP][%s %d] file name = %s ,e_present_mode = %d\n",
                __FUNCTION__,__LINE__,
                t_item_info.s_name,
                e_present_mode));
            if (MMP_FP_PRESENT_MODE_PREVIEW == e_present_mode && MMP_MEDIA_TYPE_AUDIO != pt_this->e_filter_type)
            {
                pt_this->ui4_preview_item_idx = ui4_focus_idx;

                /*Play this file from preview mode smoothly*/
                c_memset(&t_play_param, 0, sizeof(MMP_PL_PLAY_CMD_PARAM_ITEM_T));
                t_play_param.e_mode = MMP_GROUND_MODE_FORE;

                if(t_item_info.e_flag & MMP_FF_ITEM_FLAG_MEDIA_TYPE_VIDEO)
                {
                    UINT32 ui4_dir_num,ui4_file_num,ui4_file_idx;
                    /*Get focus file index*/
                    if( MMPR_OK == mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num))
                        ui4_file_idx = ui4_focus_idx - ui4_dir_num;
                    else
                        ui4_file_idx = 0;
                    t_play_param.ui4_idx = ui4_file_idx;
                }
                else
                    t_play_param.ui4_idx = 0;
                t_play_param.e_act_op = MMP_PL_PLAY_ACTIVE_OP_PREVIEW_TO_ON;
                t_play_param.z_size = sizeof(MMP_PL_PLAY_CMD_PARAM_ITEM_T);
                IS_MMPR_OK(mmp_mc_list_play_ex(MMP_PL_PLAY_CMD_PARAM_ID_0, (VOID*)&t_play_param));

                pt_this->e_status = MMP_BE_STATUS_PLAYER_ACT;

                return MMPR_OK;
            }

            if (MMP_MEDIA_TYPE_AUDIO == pt_this->e_filter_type)
            {
                 mmp_mc_file_stop(MMP_GROUND_MODE_BACK);
                return _mmp_be_play_crnt_folder(pt_this, ui4_focus_idx, FALSE, FALSE);
            }
            else
            {
                return _mmp_be_play_crnt_folder(pt_this, ui4_focus_idx, TRUE, FALSE);
            }
        }
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_switch_browser
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_cd_parent(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    CHAR*                   ps_buf;
    INT32                   i4_ret;
    UINT32                  ui4_count;
    BOOL                    b_is_avail;
    UINT16                  ui2_bwr_flag;

    ui2_bwr_flag = pt_this->pt_act_bwr->t_bwr_prop.ui2_flag;

    /* Update focus item index */
    if(MMP_BE_STATUS_NORMAL == pt_this->e_status)
    {
        /* Reset history index */
        pt_this->ui4_focus_item_idx = _mmp_be_traverse_done_stack_pop();
    }

    /* Empty select list */
    mmp_be_empty_crt_folder_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST);

    switch (pt_this->e_status)
    {
        case MMP_BE_STATUS_CHOOSE_FF:
        {
#ifndef APP_VTRL_INP_SRC_MMP_SUPPORT
            a_amb_pause_app(MMP_NAME);
#endif
        }
        break;

        case MMP_BE_STATUS_CHOOSE_MNT:
        {
            if(0 == (MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL & ui2_bwr_flag))
            {
                i4_ret = _mmp_be_choose_media_type(pt_this);
                IS_MMPR_OK(i4_ret);
            }
            else
            {
#ifndef APP_VTRL_INP_SRC_MMP_SUPPORT
                a_amb_pause_app(MMP_NAME);
#endif
            }
        }
        break;

        case MMP_BE_STATUS_NORMAL:
        {
            if (mmp_be_is_root_path())
            {
                /*Current is at root folder*/

                if(0 == (MMP_BE_BWR_FLAG_SKIP_MNT_PNT_SEL & ui2_bwr_flag))
                {
                    /*There is mount point page */
                    i4_ret = _mmp_be_is_mnt_state_avail(pt_this,
                                                        &ui4_count,
                                                        &b_is_avail);
                    if (MMPR_OK == i4_ret && b_is_avail)
                    {
                        _mmp_be_choose_mnt_pnt(pt_this);
                    }
                    else if(0 == (MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL & ui2_bwr_flag))
                    {
                        /*There is media type page */
                        _mmp_be_choose_media_type(pt_this);
                    }
                    else
                    {
#ifndef APP_VTRL_INP_SRC_MMP_SUPPORT
                        a_amb_pause_app(MMP_NAME);
#endif
                    }
                }
                else
                {
                    /*There is not mount point page */
                    if(0 == (MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL & ui2_bwr_flag))
                    {
                        /*There is media type page */
                        _mmp_be_choose_media_type(pt_this);

                    }
                    else
                    {
#ifndef APP_VTRL_INP_SRC_MMP_SUPPORT
                        a_amb_pause_app(MMP_NAME);
#endif
                    }
                }

            }
            else
            {
                i4_ret = mmp_be_get_curr_path(s_curr_path,
                                              &z_size);
                if (MMPR_OK != i4_ret)
                {
                    return i4_ret;
                }

                /*Get parent path*/
                ps_buf = c_strrchr(s_curr_path, MMP_RC_FOLDER_TOKEN);
                if (NULL == ps_buf)
                {
                    return MMPR_INTERNAL_ERROR;
                }

                /*Todo: Get traverse history here, and update focus index */

                *ps_buf = 0;

                mmp_be_set_curr_path(s_curr_path);

                pt_this->e_crt_inst_idx = (_MMP_BE_FF_INST_IDX_0 == pt_this->e_crt_inst_idx) ?
                                          _MMP_BE_FF_INST_IDX_1 : _MMP_BE_FF_INST_IDX_0;

                i4_ret = _mmp_be_get_item_list(pt_this, &pt_this->at_ff_inst[pt_this->e_crt_inst_idx], s_curr_path);
                if (MMPR_OK != i4_ret)
                {
                    return i4_ret;
                }

            }
        }
        break;

        default:
            break;
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_item_type_by_idx
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
MMP_ITEM_TYPE_T mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX e_ff_idx,
                                            UINT32 ui4_item_idx)
{
    MMP_BE_DATA_MEMBER_T*       pt_this = &t_g_browse_eng;
    UINT32                      ui4_dir_num, ui4_file_num;
    INT32                       i4_ret;

    if((pt_this->e_status == MMP_BE_STATUS_CHOOSE_FF) ||
       (pt_this->e_status == MMP_BE_STATUS_CHOOSE_MNT))
    {
        return ITEM_TYPE_DIR;
    }

    i4_ret = mmp_be_get_item_num(e_ff_idx, &ui4_dir_num, &ui4_file_num);
    if (MMPR_OK != i4_ret)
    {
        return ITEM_TYPE_NONE;
    }

    if (ui4_item_idx < ui4_dir_num)
    {
        return ITEM_TYPE_DIR;
    }
    else if (ui4_item_idx < ui4_dir_num + ui4_file_num)
    {
        return ITEM_TYPE_FILE;
    }
    else
    {
        return ITEM_TYPE_NONE;
    }
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_set_focus_item
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_set_focus_item(UINT32 ui4_focus_idx)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret;
    MMP_MEDIA_TYPE_T        e_type;
    SIZE_T                  z_size;

    pt_this->ui4_focus_item_idx = ui4_focus_idx;
    DBG_INFO_DIRECT("[mmp be] %s %d ui4_focus_idx = %d e_status:%d\n",__FUNCTION__,__LINE__,ui4_focus_idx,pt_this->e_status);
    /*Close preview if needed*/

    if (MMP_BE_STATUS_CHOOSE_FF == pt_this->e_status)
    {
        switch(ui4_focus_idx)
        {
            case 0 :
            {
                e_type = MMP_MEDIA_TYPE_PHOTO;
            }
            break;
            case 1 :
            {
                e_type = MMP_MEDIA_TYPE_AUDIO;
            }
            break;
            case 2 :
            {
                e_type = MMP_MEDIA_TYPE_VIDEO;
            }
            break;
            case 3 :
            {
                e_type = MMP_MEDIA_TYPE_TEXT;
            }
            break;
            default :
            {
                e_type = MMP_MEDIA_TYPE_PHOTO;
            }
            break;
        }

        /* Set type info to be */
        mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE,
                        (VOID*)e_type);

    }
    else if (MMP_BE_STATUS_CHOOSE_MNT == pt_this->e_status)
    {
        mmp_mc_device_set_active_mnt_point(ui4_focus_idx);

        /*Get active mount point*/
        z_size = MMP_BE_MAX_PATH_LEN;
        i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_focus_idx,
                                                    &z_size,
                                                    pt_this->s_curr_path);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("<mmp> get active mnt point fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            return i4_ret;
        }

        mmp_mc_browse_set_focus(pt_this->s_curr_path, NULL);

    }
    else if (MMP_BE_STATUS_NORMAL == pt_this->e_status)
    {
        DBG_INFO_DIRECT("[mmp be] %s %d ui4_focus_idx = %d <MMP_BE_STATUS_NORMAL>\n",__FUNCTION__,__LINE__,ui4_focus_idx);
        UINT32      ui4_cnt = 1;
        CHAR        s_full_path[MMP_BE_MAX_PATH_LEN] = {0};

        i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                      ITEM_TYPE_NONE,
                                      ui4_focus_idx,
                                      &ui4_cnt,
                                      &pt_this->t_last_notify.t_focus_item);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }

        MMP_BE_GET_FULL_ITEM_PATH(pt_this->t_last_notify.t_focus_item,
                                  s_full_path);

        c_strncpy(pt_this->s_curr_focus_path,s_full_path,MMP_BE_MAX_PATH_LEN);

        i4_ret = mmp_mc_browse_set_focus(s_full_path, NULL);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }

        if (ITEM_TYPE_FILE == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT, ui4_focus_idx) &&
            MMP_BE_BWR_FLAG_ENABLE_FILE_PREVIEW & pt_this->pt_act_bwr->t_bwr_prop.ui2_flag)
        {
            /*Start preview timer*/
            _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_FILE_PREVEW, FALSE);
        }
        else
        {
            _mmp_be_reset_timer(pt_this, MMP_BE_TIMER_ID_FILE_PREVEW, TRUE);
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_be_get_filtered_item_name
 * Description:
 * Input:   -
 * Output:  -
 * Returns
 *---------------------------------------------------------------------------*/
CHAR* mmp_be_get_filtered_item_name(CHAR* s_item_name)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    /*remove prefix*/
    return mmp_util_trim_path_prefix(pt_this->s_curr_path, s_item_name);

}
/*-----------------------------------------------------------------------------
 * Name:    mmp_be_get_filtered_item_name
 * Description:
 * Input:   -
 * Output:  -
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 mmp_be_preview_crnt_file(UINT32 ui4_focus_idx)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    return _mmp_be_preview_crnt_file(pt_this,ui4_focus_idx);

}

/*-----------------------------------------------------------------------------
 * Name:    mmp_be_stop_preview
 * Description:
 * Input:   -
 * Output:  -
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_be_stop_preview(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    return _mmp_be_stop_preview(pt_this);
}

/*----------------------------------------------------------------------------
* Name:    mmp_be_auth_touch_folder
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_auth_touch_folder(UINT32 ui4_focus_idx)
{
#ifdef APP_NET_NEIGHBOR_SUPPORT

    INT32                   i4_ret;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    FM_DIR_INFO_T           t_dir_info;
    MMP_BE_FILE_SRC_TYPE_T  e_src_type;

    /* Check status */
    if(pt_this->e_status == MMP_BE_STATUS_CHOOSE_FF)
    {
        return MMPR_OK;
    }
    /* check the source type */
    i4_ret = mmp_be_get_file_src_type (pt_this->s_curr_path, &e_src_type);
    if (MMPR_OK == i4_ret && MMP_BE_FILE_SRC_NET_NEIGHBOR != e_src_type)
    {
        return MMPR_OK;
    }

    /* check the item type */
    if (mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT, ui4_focus_idx) != ITEM_TYPE_DIR)
    {
        return MMPR_OK;
    }

    /* Check if root dir is empty for specified filter */

    switch(pt_this->e_status)
    {
        case MMP_BE_STATUS_CHOOSE_MNT :
        {
            c_strncpy(s_curr_path,pt_this->s_curr_path,MMP_BE_MAX_PATH_LEN);
            break;
        }
        case MMP_BE_STATUS_NORMAL:
        default :
        {
            c_strncpy(s_curr_path,pt_this->s_curr_focus_path,MMP_BE_MAX_PATH_LEN);
            break;
        }
    }

    i4_ret = c_fm_get_dir_info (NULL_HANDLE, s_curr_path, &t_dir_info);
    if (FMR_OK != i4_ret)
    {
        if(FMR_AUTH_FAIL == i4_ret)
        {
            DBG_LOG_PRINT(("c_fm_get_dir_info return %d,no auth to enter folder.%s,%d",i4_ret,__FUNCTION__,__LINE__));
            return MMPR_DIR_AUTH_FAIL;
        }

        return MMPR_FAIL;
    }

    return i4_ret;
#else

    return MMPR_OK;

#endif
}
/*----------------------------------------------------------------------------
* Name:    mmp_be_auth_touch_folder
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_default_key_handle(UINT32 ui4_key_code,UINT32 ui4_keystatus)
{
    INT32                   i4_ret;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_dir_num, ui4_file_num;
    MMP_PLAY_STATE_T        e_bk_state = MMP_PLAY_STATE_CLOSED;


    switch (ui4_key_code)
    {
        /* Play Group key */
        case AUDIO_PLAYER_BTN_PLAY_PAUSE_2:
        case AUDIO_PLAYER_BTN_STOP:
        case AUDIO_PLAYER_BTN_REPEAT:
        case AUDIO_PLAYER_BTN_NEXT:
        case AUDIO_PLAYER_BTN_PREV:
        case AUDIO_PLAYER_BTN_NEXT_2:
        case AUDIO_PLAYER_BTN_PREV_2:
        case AUDIO_PLAYER_BTN_FF:
        case AUDIO_PLAYER_BTN_FR:
        case AUDIO_PLAYER_BTN_AB_REPEAT:
        case AUDIO_PLAYER_BTN_SHUFFLE:
        case AUDIO_PLAYER_BTN_PLAY:
        case AUDIO_PLAYER_BTN_PAUSE:
        case AUDIO_PLAYER_BTN_STOP_2:
        {
            /*Check if BK player is stopped*/
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                            &e_bk_state);
            if ((i4_ret == MMPR_OK) &&
                (e_bk_state  != MMP_PLAY_STATE_CLOSING) &&
                (e_bk_state  != MMP_PLAY_STATE_CLOSED) &&
                (e_bk_state  != MMP_PLAY_STATE_STOPPING) &&
                (e_bk_state  != MMP_PLAY_STATE_STOPPED))
            {
                if (AUDIO_PLAYER_BTN_PLAY == ui4_key_code)
                {
                    if ((MMP_PLAY_STATE_PLAYING == e_bk_state)
                        ||(MMP_PLAY_STATE_PLAYED == e_bk_state))
                    {
                        /* play key to play. */
                        return MMPR_NO_DATA;
                    }
                }

                if (AUDIO_PLAYER_BTN_PAUSE == ui4_key_code)
                {
                    if ((MMP_PLAY_STATE_PAUSING == e_bk_state)
                        ||(MMP_PLAY_STATE_PAUSED == e_bk_state))
                    {
                        /* puase key to pause. */
                        return MMPR_NO_DATA;
                    }
                }

                /* there is playing a file at background , then send the key to next */
                return mmp_mc_browse_bk_key_handler(ui4_key_code, ui4_keystatus);
            }
            else
            {
                /* there is no file played. and if the key is play_key */
                if((AUDIO_PLAYER_BTN_PLAY_PAUSE_2 == ui4_key_code)||
                   (AUDIO_PLAYER_BTN_PLAY == ui4_key_code))
                {
                    /* Check media type first. if not audio. send key to next  */
                    if(pt_this->e_filter_type != MMP_MEDIA_TYPE_AUDIO)
                    {
                        return mmp_mc_browse_bk_key_handler(ui4_key_code,ui4_keystatus);
                    }

                    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
                    if ((MMPR_OK == i4_ret) &&
                        (pt_this->ui4_focus_item_idx >= ui4_dir_num))
                    {
                        return _mmp_be_play_crnt_folder(pt_this,pt_this->ui4_focus_item_idx, FALSE, FALSE);
                    }

                }
                else
                {
                    /* the bk is not actived, and the key is not play or pause, do nothing */
                }
            }

        }
        break;

        default:
        {

        }
        break;

    }

   return mmp_mc_key_handler(ui4_key_code,ui4_keystatus);

}
/*----------------------------------------------------------------------------
* Name:    mmp_be_auth_touch_folder
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_pause_mmp(VOID)
{

#ifndef APP_VTRL_INP_SRC_MMP_SUPPORT
#ifdef APP_CAST_TV_MMP_FG
    SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;
    INT32  i4_ret = MMPR_OK;
    UINT32 ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_USER;

    i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                           (VOID*) &ui4_exit_reason, z_size);
    if(MMPR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("a_icl_set() fail. i4_ret = %d.\r\n", i4_ret));
    }

    mmp_foreground_chg_inp_src_to_cast();

#endif

    a_amb_clean_stack();
    return a_amb_pause_app(MMP_NAME);
#else
    return MMPR_OK;
#endif

}

INT32 mmp_be_paste(VOID)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32   i4_ret;

    i4_ret = _mmp_be_enter_bg_mode();
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_fo_paste(t_g_browse_eng.s_curr_path);
    if (MMPR_OK != i4_ret)
    {
        _mmp_be_exit_bg_mode();
        return (i4_ret);
    }

    return (MMPR_OK);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

INT32 mmp_be_delete(VOID)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32 i4_ret;

    /* Empty current folder's file in copy list */
    i4_ret = mmp_be_empty_crt_folder_list(MMP_FF_ITEM_LIST_TYPE_COPY_LIST);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = _mmp_be_enter_bg_mode();
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_fo_delete();
    if (MMPR_OK != i4_ret)
    {
        _mmp_be_exit_bg_mode();
        return (i4_ret);
    }

    return (MMPR_OK);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

INT32 mmp_be_press_select(UINT32 ui4_idx)
{
    INT32                   i4_ret;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_dir_num, ui4_file_num;

    switch (pt_this->e_status)
    {
    case MMP_BE_STATUS_NORMAL:

        i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
        if (MMPR_OK == i4_ret && ui4_idx >= ui4_dir_num)
        {
            return _mmp_be_select_file(MMP_BE_FF_IDX_CRT, ui4_idx - ui4_dir_num);
        }

        break;

    default:
        return MMPR_OK;
    }
    return (MMPR_OK);
}

INT32 mmp_be_add_to_sel_list(UINT32 ui4_idx)
{
    INT32   i4_ret;
    BOOL    b_selected;
    i4_ret = mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST, ui4_idx, &b_selected);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    if (!b_selected)
    {
        i4_ret = mmp_be_press_select(ui4_idx);
        if (MMPR_OK != i4_ret)
        {
            return (i4_ret);
        }
    }
    return (MMPR_OK);
}

INT32 mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_T e_list_type,UINT32 ui4_idx, BOOL* pb_exists)
{
    INT32                   i4_ret;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_dir_num, ui4_file_num;

    switch (pt_this->e_status)
    {
    case MMP_BE_STATUS_NORMAL:
        i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
        if (MMPR_OK == i4_ret && ui4_idx >= ui4_dir_num)
        {
            return _mmp_be_file_in_list(e_list_type, MMP_BE_FF_IDX_CRT, ui4_idx - ui4_dir_num, pb_exists);
        }

        break;

    default:
        *pb_exists = FALSE;
        return MMPR_OK;
    }

    return (MMPR_OK);
}

INT32 mmp_be_clone_to_copy_list(UINT32 ui4_idx)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32               i4_ret;

    i4_ret = mmp_be_add_to_sel_list(ui4_idx);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = _mmp_be_clone_to_copy_list(MMP_BE_FF_IDX_CRT);
    return (i4_ret);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

INT32 mmp_be_clone_to_del_list(UINT32 ui4_idx)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32               i4_ret;

    i4_ret = mmp_be_add_to_sel_list(ui4_idx);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = _mmp_be_clone_to_del_list(MMP_BE_FF_IDX_CRT);
    return (i4_ret);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

INT32 mmp_be_empty_crt_folder_list(MMP_FF_ITEM_LIST_TYPE_T e_list_type)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32                       i4_ret;
    MMP_BE_FF_INST_T*           pt_inst;

    i4_ret = _mmp_be_get_ff_inst_by_idx(&t_g_browse_eng,
                                        MMP_BE_FF_IDX_CRT,
                                        &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = mmp_fo_upd_list_item(pt_inst->ui1_ff_id,
                                  e_list_type,
                                  MMP_FF_ITEM_LIST_OP_TYPE_RMV_ALL,
                                  0,
                                  NULL);

    return (i4_ret);
#else
    return MMPR_OK;
#endif
}

INT32 mmp_be_get_paste_status(MMP_PASTE_STATUS_T* pe_paste_status)
{
#ifdef MMP_FILE_OP_SUPPORT
    INT32                   i4_ret;
    UINT32                  ui4_item_cnt;
    MMP_ITEM_INFO_T         t_item_info;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    if (!pe_paste_status)
    {
        return (MMPR_INV_ARG);
    }

    i4_ret = mmp_fo_get_list_count(MMP_FF_ITEM_LIST_TYPE_COPY_LIST, &ui4_item_cnt);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    if (ui4_item_cnt == 0)
    {
        *pe_paste_status = MMP_PASTE_STATUS_NO_FILE;
    }
    else
    {
        switch (pt_this->e_status)
        {
        case MMP_BE_STATUS_NORMAL:
        {
            BOOL b_recursive_read = FALSE;

            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE, &b_recursive_read);

            c_memset(&t_item_info, 0, sizeof(MMP_ITEM_INFO_T));
            ui4_item_cnt = 1;
            i4_ret = mmp_fo_get_list_item_info(MMP_FF_ITEM_LIST_TYPE_COPY_LIST,
                                               ITEM_TYPE_FILE,
                                               0,
                                               &ui4_item_cnt,
                                               &t_item_info);
            if (MMPR_OK != i4_ret)
            {
                return (i4_ret);
            }

            if (b_recursive_read ||
                c_strcmp(t_item_info.s_parent_name, t_g_browse_eng.s_curr_path) == 0)
            {
                *pe_paste_status = MMP_PASTE_STATUS_UNAVAILABLE;
            }
            else
            {
                *pe_paste_status = MMP_PASTE_STATUS_AVAILABLE;
            }
        break;
        }

        default:
        {
            *pe_paste_status = MMP_PASTE_STATUS_UNAVAILABLE;
            break;
        }
        }
    }
    return (MMPR_OK);
#else
    return MMPR_NOT_SUPPORT;
#endif
}

BOOL  mmp_be_is_copy_available(VOID)
{
    return (mmp_be_is_delete_available());
}

BOOL  mmp_be_is_delete_available(VOID)
{
    MMP_ITEM_TYPE_T         e_item_type;
    UINT32                  ui4_focus_idx;
    INT32                   i4_ret;
    BOOL                    b_empty = FALSE;
    BOOL                    b_recursive_read = FALSE;

    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE, &b_recursive_read);

    if (b_recursive_read)
    {
        return (FALSE);
    }

    i4_ret = mmp_be_is_empty_folder(MMP_BE_FF_IDX_CRT, &b_empty);
    if (MMPR_OK == i4_ret && !b_empty)
    {
        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FOCUS_ITEM_IDX, &ui4_focus_idx);
        e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,
                                              ui4_focus_idx);

        if (ITEM_TYPE_FILE == e_item_type)
        {
            return (TRUE);
        }
    }
    return (FALSE);
}
/*----------------------------------------------------------------------------
* Name:    mmp_be_stop_bg_player
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_stop_bg_player(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

   /*  stop bk audio  */
   if(MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
   {
       /* Remove last playlist item */
       mmp_mc_list_remove_all(MMP_GROUND_MODE_BACK);
       /* Stop current playback. */
       mmp_mc_list_stop (MMP_GROUND_MODE_BACK);

       mmp_mc_browse_show_info_handler(FALSE,FALSE,TRUE);
   }

   return MMPR_OK;

}

/*----------------------------------------------------------------------------
* Name:    mmp_be_is_item_in_list
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
BOOL mmp_be_is_item_in_list(MMP_BE_FF_IDX e_ff_idx,
                            MMP_ITEM_TYPE_T e_filter_type,
                            UINT32 ui4_idx,
                            MMP_FF_ITEM_LIST_TYPE_T e_list_type)
{
    INT32                   i4_ret = MMPR_OK;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_dir_num, ui4_file_num;
    MMP_FF_ITEM_ATTR_T      t_attr;
    MMP_BE_FF_INST_T*       pt_inst;

    do {
        if (MMP_BE_STATUS_NORMAL != pt_this->e_status &&
            MMP_BE_STATUS_PLAYER_ACT != pt_this->e_status)
        {
            break;
        }

        /*Check item type parameter*/
        if (ITEM_TYPE_FILE != e_filter_type && ITEM_TYPE_NONE != e_filter_type)
        {
            break;
        }

        i4_ret = _mmp_be_get_ff_inst_by_idx(pt_this, e_ff_idx, &pt_inst);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = mmp_be_get_item_num(e_ff_idx, &ui4_dir_num, &ui4_file_num);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        if (ITEM_TYPE_FILE == e_filter_type)
        {
            if (ui4_idx >= ui4_file_num)
            {
                break;
            }
            t_attr.ui4_idx = ui4_idx;
        }
        else
        {
            if (ui4_idx < ui4_dir_num)
            {
                break;
            }
            t_attr.ui4_idx = ui4_idx - ui4_dir_num;
        }

        t_attr.e_item_type = ITEM_TYPE_FILE;
        return mmp_ff_is_item_in_list(pt_inst->ui1_ff_id, e_list_type, &t_attr);
    } while (0);

    return FALSE;
}

/*----------------------------------------------------------------------------
* Name:    mmp_be_update_list_item
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_update_list_item(MMP_ITEM_TYPE_T e_filter_type,
                              UINT32 ui4_idx,
                              MMP_FF_ITEM_LIST_TYPE_T e_list_type,
                              MMP_FF_ITEM_LIST_OP_TYPE_T e_op_type)
{
    INT32                   i4_ret = MMPR_OK;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_dir_num, ui4_file_num;
    MMP_FF_ITEM_ATTR_T      t_attr;
    MMP_BE_FF_INST_T*       pt_inst;

    do {
        if (MMP_BE_STATUS_NORMAL != pt_this->e_status &&
            MMP_BE_STATUS_PLAYER_ACT != pt_this->e_status)
        {
            break;
        }

        /*Check item type parameter*/
        if (ITEM_TYPE_FILE != e_filter_type && ITEM_TYPE_NONE != e_filter_type)
        {
            break;
        }

        i4_ret = _mmp_be_get_ff_inst_by_idx(pt_this,
                                            MMP_BE_FF_IDX_CRT,
                                            &pt_inst);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        if (ITEM_TYPE_FILE == e_filter_type)
        {
            if (ui4_idx >= ui4_file_num)
            {
                break;
            }
            t_attr.ui4_idx = ui4_idx;
        }
        else
        {
            if (ui4_idx < ui4_dir_num)
            {
                break;
            }
            t_attr.ui4_idx = ui4_idx - ui4_dir_num;
        }

        t_attr.e_item_type = ITEM_TYPE_FILE;
        i4_ret = mmp_ff_upd_list_item(pt_inst->ui1_ff_id,
                                      e_list_type,
                                      e_op_type,
                                      1,
                                      &t_attr);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;
    } while (0);

    return MMPR_NOT_SUPPORT;
}

/*----------------------------------------------------------------------------
* Name:    mmp_be_get_first_non_skip_file
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX e_ff_idx, UINT32 ui4_start_idx, UINT32* pui4_target_idx)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    MMP_BE_FF_INST_T*       pt_inst;
    INT32                   i4_ret;
    UINT32                  ui4_dir_num, ui4_file_num, ui4_i;
    MMP_FF_ITEM_ATTR_T      t_attr;

    i4_ret = _mmp_be_get_ff_inst_by_idx(pt_this, e_ff_idx, &pt_inst);
    if (MMPR_OK != i4_ret)
    {
        return MMPR_INTERNAL_ERROR;
    }

    i4_ret = mmp_be_get_item_num(e_ff_idx, &ui4_dir_num, &ui4_file_num);
    if (MMPR_OK != i4_ret)
    {
        return MMPR_INTERNAL_ERROR;
    }

    if (MMP_NULL_FILE_IDX == ui4_start_idx)
    {
        ui4_start_idx = 0;
    }
    else
    {
        ui4_start_idx = ui4_start_idx % ui4_file_num;
    }

    t_attr.e_item_type = ITEM_TYPE_FILE;
    for (ui4_i = ui4_start_idx; ui4_i < ui4_file_num; ui4_i++)
    {
        t_attr.ui4_idx = ui4_i;
        if (FALSE == mmp_ff_is_item_in_list(pt_inst->ui1_ff_id, MMP_FF_ITEM_LIST_TYPE_SKIP_LIST, &t_attr))
        {
            *pui4_target_idx = ui4_i;
            return MMPR_OK;
        }
    }

    for (ui4_i = 0; ui4_i < ui4_start_idx; ui4_i++)
    {
        t_attr.ui4_idx = ui4_i;
        if (FALSE == mmp_ff_is_item_in_list(pt_inst->ui1_ff_id, MMP_FF_ITEM_LIST_TYPE_SKIP_LIST, &t_attr))
        {
            *pui4_target_idx = ui4_i;
            return MMPR_OK;
        }
    }

    return MMPR_NO_DATA;
}

/*----------------------------------------------------------------------------
* Name:    mmp_be_set_item_status
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_set_item_status(MMP_ITEM_TYPE_T e_filter_type,
                             UINT32 ui4_idx,
                             MMP_FF_ITEM_FLAG_T e_flag)
{
    INT32                   i4_ret = MMPR_OK;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    UINT32                  ui4_dir_num, ui4_file_num, ui4_item_idx = 0;
    MMP_BE_FF_INST_T*       pt_inst;
    MMP_ITEM_TYPE_T         e_item_type = ITEM_TYPE_FILE;

    do {
        if (MMP_BE_STATUS_NORMAL != pt_this->e_status &&
            MMP_BE_STATUS_PLAYER_ACT != pt_this->e_status)
        {
            break;
        }

        /*Check item type parameter*/
        if (ITEM_TYPE_FILE != e_filter_type && ITEM_TYPE_NONE != e_filter_type)
        {
            break;
        }

        i4_ret = _mmp_be_get_ff_inst_by_idx(pt_this,
                                            MMP_BE_FF_IDX_CRT,
                                            &pt_inst);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        if (ITEM_TYPE_FILE == e_filter_type)
        {
            if (ui4_idx >= ui4_file_num)
            {
                break;
            }
            ui4_item_idx = ui4_idx;
        }
        else
        {
            if (ui4_idx < ui4_dir_num)
            {
                break;
            }
            ui4_item_idx = ui4_idx - ui4_dir_num;
        }

        i4_ret = mmp_ff_set_item_status(pt_inst->ui1_ff_id,
                                        e_item_type,
                                        ui4_item_idx,
                                        e_flag);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;
    } while (0);

    return MMPR_NOT_SUPPORT;
}

/*----------------------------------------------------------------------------
* Name:    mmp_be_start_play_crnt_folder
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
INT32 mmp_be_start_play_crnt_folder(UINT32 ui4_focus_idx, BOOL b_view_only)
{
    INT32                   i4_ret;
    UINT32                  ui4_dir_num, ui4_file_num;

    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
    if (MMPR_OK == i4_ret && ui4_focus_idx >= ui4_dir_num)
    {
        return _mmp_be_play_crnt_folder(&t_g_browse_eng, ui4_focus_idx, TRUE, b_view_only);
    }

    return MMPR_NOT_SUPPORT;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_device_info
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_device_info(UINT32                   ui4_idx,
                                       UTF16_T*                 pw2s_dev_info,
                                       RMV_DEV_DEVICE_STATUS_T* pe_dev_status,
                                       BOOL*                    pb_next)
{
    INT32                   i4_ret = MMPR_OK;
    SIZE_T                  z_size = MMP_DEV_NAME_MAX_LEN;
    CHAR                    ac_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    CHAR                    ac_path[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UINT32                  ui4_len = MMP_DEV_NAME_MAX_LEN;

    if ((NULL == pw2s_dev_info)
        ||(NULL == pe_dev_status)
        ||(NULL == pb_next))
    {
        return MMPR_INV_ARG;
    }

    /*query mount point status*/
    i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_idx,
                                                   pe_dev_status);
    if(MMPR_OK != i4_ret)
    {
        *pb_next = TRUE;
        return MMPR_OK;
    }

    /* do not support these devices */
    if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(*pe_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(*pe_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_REMOVED(*pe_dev_status)))
    {
        *pb_next = TRUE;
        return MMPR_OK;
    }

    if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(*pe_dev_status))
    {
        *pb_next = FALSE;

        /* get dlna device name and index */
        z_size = MMP_DEV_NAME_MAX_LEN;
        i4_ret = mmp_mc_device_get_mnt_point_info(ui4_idx,
                                                  MMP_MC_DEV_INFO_ID_DESC,
                                                  &z_size,
                                                  (VOID*)ac_info);
        MMPR_LOG_ON_FAIL(i4_ret);

        if (0 == c_strcmp(ac_info, "MediaTek DMR"))
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                         __FILE__, __FUNCTION__, __LINE__));
            *pb_next = TRUE;
            return MMPR_OK;
        }
    }
    else
    {
        *pb_next = FALSE;

        /* get usb device name and index */
        z_size = MMP_DEV_NAME_MAX_LEN;
        i4_ret = mmp_mc_device_get_mnt_point(ui4_idx,
                                             &z_size,
                                             ac_path);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                       ac_path,
                                       ac_info,
                                       &ui4_len);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_uc_ps_to_w2s(ac_info,
                            pw2s_dev_info,
                            MMP_DEV_NAME_MAX_LEN);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_dlna_serial_name
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_dlna_serial_name(UINT32     ui4_idx,
                                              UTF16_T*   pw2s_dev_hint)
{
    INT32   i4_ret = MMPR_OK;
    CHAR    ac_temp[MMP_DEV_NAME_MAX_LEN + 1] = {0};

    if (NULL == pw2s_dev_hint)
    {
        return MMPR_INV_ARG;
    }

    c_sprintf(ac_temp,
              MMP_DEV_LIST_DLNA_DEV_PREFIX,
              ui4_idx);

    i4_ret = c_uc_ps_to_w2s(ac_temp,
                            pw2s_dev_hint,
                            MMP_DEV_NAME_MAX_LEN);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_usb_serial_name
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_usb_serial_name(UINT32     ui4_idx,
                                             UTF16_T*   pw2s_dev_hint)
{
    INT32   i4_ret = MMPR_OK;
    CHAR    ac_temp[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UINT8   ui1_usb_port_num = a_get_usb_port_num_by_model();

    if (NULL == pw2s_dev_hint)
    {
        return MMPR_INV_ARG;
    }

#ifdef SUPPORT_ONLY_ONE_USB_PORT
        c_strncpy(ac_temp, "USB:", MMP_DEV_NAME_MAX_LEN);
#else
    if (ui1_usb_port_num > 1)
    {
        c_sprintf(ac_temp, MMP_DEV_LIST_USB_DEV_PREFIX, ui4_idx);
    }
    else if (1 == ui1_usb_port_num)
    {
        c_strncpy(ac_temp, "USB:", MMP_DEV_NAME_MAX_LEN);
    }
    else
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,ui1_usb_port_num=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, ui1_usb_port_num));
    }
#endif

    i4_ret = c_uc_ps_to_w2s(ac_temp,
                            pw2s_dev_hint,
                            MMP_DEV_NAME_MAX_LEN);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_get_device_info
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_be_get_activate_device_info(UTF16_T* pw2s_dev_info,
                                                  UTF16_T* pw2s_dev_hint,
                                                  UINT32*  pui4_active_idx)
{
    INT32                       i4_ret = MMPR_OK;
    UINT32                      ui4_active_idx = 0;
    SIZE_T                      z_size = MMP_DEV_NAME_MAX_LEN;
    CHAR                        ac_path[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UINT32                      ui4_idx = 0;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status;
    UINT32                      ui4_dlna_id = 0;
    UINT32                      ui4_usb_id = 0;
    CHAR                        ac_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UINT32                      ui4_len = MMP_DEV_NAME_MAX_LEN;
    UINT32                      ui4_mnt_count = 0;

    if ((NULL == pw2s_dev_info)
        ||(NULL == pw2s_dev_hint))
    {
        return MMPR_INV_ARG;
    }

    /* get active device id */
    z_size = MMP_DEV_NAME_MAX_LEN;
    i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_active_idx,
                                                &z_size,
                                                ac_path);
    MMPR_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ac_path=%s\n",
              __FILE__, __FUNCTION__, __LINE__,
              ui4_active_idx, ac_path));

    for (ui4_idx = 0;
         (ui4_idx <= ui4_active_idx) && (ui4_active_idx < MMP_DEV_LIST_MAX_NUM);
         ui4_idx++)
    {
        /* query mount point status */
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_idx,
                                                       &e_dev_status);
        if(MMPR_OK != i4_ret)
        {
            DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_idx=%d\n",
                      __FILE__, __FUNCTION__, __LINE__,
                      ui4_active_idx, ui4_idx));
            continue;
        }
        DBG_LOG_PRINT(("[MMP][%s %d]e_dev_status = 0x%x\n",__FUNCTION__,__LINE__,e_dev_status));
        /* do not support this device type */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))   ||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_idx=%d\n",
                      __FILE__, __FUNCTION__, __LINE__,
                      ui4_active_idx, ui4_idx));
            continue;
        }

        /* count dlna and usb device num */
        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            z_size = MMP_DEV_NAME_MAX_LEN;
            i4_ret = a_rmv_dev_get_mnt_point_info(
                                    ui4_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)ac_info);
            MMPR_LOG_ON_FAIL(i4_ret);

            if (0 == c_strcmp(ac_info, "MediaTek DMR"))
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                             __FILE__, __FUNCTION__, __LINE__));
                continue;
            }
            else
            {
                ui4_dlna_id++;
            }
        }
        else if(!(RMV_DEV_DEVICE_STATUS_UNSUPT_DEV & e_dev_status))
        {
            ui4_usb_id++;
        }
    }

    /* query mount point status */
    i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_active_idx,
                                                   &e_dev_status);
    MMPR_LOG_ON_FAIL(i4_ret);

    if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
    {
        i4_ret = mmp_mc_device_get_mnt_count(&ui4_mnt_count);
        MMPR_LOG_ON_FAIL(i4_ret);

        DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_mnt_count=%d\n",
                  __FILE__, __FUNCTION__, __LINE__,
                  ui4_active_idx, ui4_mnt_count));

        if (ui4_active_idx >= ui4_mnt_count)
        {
            return MMPR_FAIL;
        }

        for (ui4_idx=(ui4_active_idx+1); ui4_idx<=ui4_mnt_count; ui4_idx++)
        {
            /* query mount point status */
            i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_idx,
                                                           &e_dev_status);
            if(MMPR_OK != i4_ret)
            {
                DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_idx=%d\n",
                          __FILE__, __FUNCTION__, __LINE__,
                          ui4_active_idx, ui4_idx));
                continue;
            }

            /* do not support this device type */
            if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
            {
                DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_idx=%d\n",
                          __FILE__, __FUNCTION__, __LINE__,
                          ui4_active_idx, ui4_idx));
                continue;
            }
            else
            {
                z_size = MMP_DEV_NAME_MAX_LEN;
                i4_ret = a_rmv_dev_get_mnt_point_info(
                                        ui4_idx,
                                        RMV_DEV_INFO_ID_DESC,
                                        &z_size,
                                        (VOID*)ac_info);
                MMPR_LOG_ON_FAIL(i4_ret);

                if (0 == c_strcmp(ac_info, "MediaTek DMR"))
                {
                    DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_idx=%d\n",
                              __FILE__, __FUNCTION__, __LINE__,
                              ui4_active_idx, ui4_idx));
                    continue;
                }
                else
                {
                    /* bingo, find next active device. */
                    break;
                }
            }
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            DBG_INFO(("\n%s,%s,%d,ui4_active_idx=%d,ui4_idx=%d\n",
                      __FILE__, __FUNCTION__, __LINE__,
                      ui4_active_idx, ui4_idx));
            return MMPR_FAIL;
        }

        ui4_active_idx = ui4_idx;
    }

    *pui4_active_idx = ui4_active_idx;

    if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
    {
        /* get dlna device name and index */
        z_size = MMP_DEV_NAME_MAX_LEN;
        i4_ret = mmp_mc_device_get_mnt_point_info(ui4_active_idx,
                                                  MMP_MC_DEV_INFO_ID_DESC,
                                                  &z_size,
                                                  (VOID*)ac_info);
        MMPR_LOG_ON_FAIL(i4_ret);

        if (0 == c_strcmp(ac_info, "MediaTek DMR"))
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                         __FILE__, __FUNCTION__, __LINE__));
            *pui4_active_idx = ui4_active_idx - 1; /* a_rmv_dev_get_active_mnt_pnt() is last id, if last is MediaTek DMR,get prev id, fix DTV00784644 */
            return MMPR_FAIL;
        }
        else
        {
            i4_ret = mmp_be_get_dlna_serial_name(ui4_dlna_id,
                                                 pw2s_dev_hint);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        /* get usb volume label name and index */
        i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                       ac_path,
                                       ac_info,
                                       &ui4_len);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_be_get_usb_serial_name(ui4_usb_id,
                                            pw2s_dev_hint);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_uc_ps_to_w2s(ac_info,
                            pw2s_dev_info,
                            MMP_DEV_NAME_MAX_LEN);
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#ifdef APP_NET_DLNA_SUPPORT
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_be_current_is_dlna_device
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
BOOL mmp_be_current_is_dlna_device(VOID)
{
    INT32                       i4_ret = MMPR_OK;
    UINT32                      ui4_active_idx = 0;
    SIZE_T                      z_size = MMP_DEV_NAME_MAX_LEN;
    CHAR                        ac_path[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    RMV_DEV_DEVICE_STATUS_T     e_dev_status;

    /* get active device id */
    i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_active_idx,
                                                &z_size,
                                                ac_path);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_active_idx,
                                                   &e_dev_status);
    if ((MMPR_OK == i4_ret)
        &&(TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
    {
        return TRUE;
    }

    return FALSE;
}
#endif

#ifdef APP_MENU_MMP_COEXIST
/*----------------------------------------------------------------------------
* Name:    a_mmp_be_get_media_type
* Description: it used for deal with mmp & menu coexist issues.
                      it maybe enhanced later.
                      please do not call it when current application is not mmp.
                      callers must use macro APP_MENU_MMP_COEXIST to include it.
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
MMP_BE_BROWSER_MEDIA_TYPE a_mmp_be_get_media_type(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;

    if (MMP_MEDIA_TYPE_AUDIO == pt_this->e_filter_type)
    {
        return MMP_BE_BROWSER_MEDIA_TYPE_AUDIO;
    }
    else if(MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
    {
        return MMP_BE_BROWSER_MEDIA_TYPE_VIDEO;
    }
    else if(MMP_MEDIA_TYPE_PHOTO == pt_this->e_filter_type)
    {
        return MMP_BE_BROWSER_MEDIA_TYPE_PHOTO;
    }
    else
    {
        return MMP_BE_BROWSER_MEDIA_TYPE_NONE;
    }
}

/*----------------------------------------------------------------------------
* Name:    a_mmp_be_get_browser_status
* Description: it used for deal with mmp & menu coexist issues.
                      it maybe enhanced later.
                      please do not call it when current application is not mmp.
                      callers must use macro APP_MENU_MMP_COEXIST to include it.
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
MMP_BE_BROWSER_STATUS_T a_mmp_be_get_browser_status(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret = MMPR_OK;
    MMP_PLAY_STATE_T        e_back_play_state = MMP_PLAY_STATE_CLOSED;
    MMP_PLAY_STATE_T        e_fore_play_state = MMP_PLAY_STATE_CLOSED;
    MMP_FP_PRESENT_MODE_T   e_present_mode = MMP_FP_PRESENT_MODE_FULL;
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;

    do
    {
        if (MMP_MEDIA_TYPE_AUDIO == pt_this->e_filter_type)
        {
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                            &e_back_play_state);
            if (MMPR_OK != i4_ret)
            {
                e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                break;
            }

            if ((MMP_PLAY_STATE_PLAYING == e_back_play_state)
                ||(MMP_PLAY_STATE_PLAYED == e_back_play_state))
            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_NORMAL_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_NORMAL_PLAYING;
                    break;
                }
                else if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_FORE_NORMAL_PLAYING;
                    break;
                }
            }
            else if ((MMP_PLAY_STATE_FAST_FORWARDING == e_back_play_state)
                      ||(MMP_PLAY_STATE_FAST_FORWARDED == e_back_play_state)
                      ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_back_play_state)
                      ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_back_play_state))
            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_FF_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_FF_PLAYING;
                    break;
                }
                else if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_FORE_FF_PLAYING;
                    break;
                }
            }
            else if ((MMP_PLAY_STATE_FAST_REWINDING == e_back_play_state)
                     ||(MMP_PLAY_STATE_FAST_REWINDED == e_back_play_state))

            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_FR_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_FR_PLAYING;
                    break;
                }
                else if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_FORE_FR_PLAYING;
                    break;
                }
            }
            else
            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_NOT_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_NOT_PLAYING;
                    break;
                }
                else
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                    break;
                }
            }
        }
        else if (MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
        {
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_FORE,
                                            &e_fore_play_state);
            if (MMPR_OK != i4_ret)
            {
                e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                break;
            }

            mmp_mc_list_get_play_present_mode(&e_present_mode);
            if (MMP_FP_PRESENT_MODE_PREVIEW == e_present_mode)
            {
                if ((MMP_PLAY_STATE_PLAYING == e_fore_play_state)
                    ||(MMP_PLAY_STATE_PLAYED == e_fore_play_state))
                {
                    if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_LIST_NORMAL_PREVIEW;
                        break;
                    }
                    else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NORMAL_PREVIEW;
                        break;
                    }
                    else
                    {
                        /* if video is preview, just thumbnail or list mode. */
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                        break;
                    }
                }
                else if ((MMP_PLAY_STATE_FAST_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_FAST_FORWARDED == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_fore_play_state))
                {
                    if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_LIST_FF_PREVIEW;
                        break;
                    }
                    else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_FF_PREVIEW;
                        break;
                    }
                    else
                    {
                        /* if video is preview, just thumbnail or list mode. */
                        e_mmp_browser_status =  MMP_BE_BROWSER_STATUS_ERROR;
                        break;
                    }
                }
                else if ((MMP_PLAY_STATE_FAST_REWINDING == e_fore_play_state)
                         ||(MMP_PLAY_STATE_FAST_REWINDED == e_fore_play_state))

                {
                    if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_LIST_FR_PREVIEW;
                        break;
                    }
                    else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_FR_PREVIEW;
                        break;
                    }
                    else
                    {
                        /* if video is preview, just thumbnail or list mode. */
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                        break;
                    }
                }
            }
            else if (MMP_FP_PRESENT_MODE_FULL == e_present_mode)
            {
                if ((MMP_PLAY_STATE_PLAYING == e_fore_play_state)
                    ||(MMP_PLAY_STATE_PLAYED == e_fore_play_state))
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING;
                    break;
                }
                else if ((MMP_PLAY_STATE_PAUSING == e_fore_play_state)
                       ||(MMP_PLAY_STATE_PAUSED == e_fore_play_state))
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING;
                    break;
                }
                else if ((MMP_PLAY_STATE_FAST_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_FAST_FORWARDED == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_fore_play_state))
                {
                    e_mmp_browser_status =  MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING;
                    break;
                }
                else if ((MMP_PLAY_STATE_FAST_REWINDING == e_fore_play_state)
                         ||(MMP_PLAY_STATE_FAST_REWINDED == e_fore_play_state))

                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING;
                    break;
                }
                else
                {
                    if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_LIST_NOT_PLAYING;
                        break;
                    }
                    else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NOT_PLAYING;
                        break;
                    }
                    else
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                        break;
                    }
                }
            }
        }
        else if (MMP_MEDIA_TYPE_PHOTO == pt_this->e_filter_type)
        {
            e_mmp_browser_status = MMP_BE_BROWSER_STATUS_PHOTO;//may be expand
        }

        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status())
        {
            e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
            break;
        }
    }while(0);

    return e_mmp_browser_status;
}

BOOL a_mmp_is_video_playing(VOID)
{
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = a_mmp_be_get_browser_status();
    if((e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING)||
       (e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING)||
       (e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING)||
       (e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING)||
       (e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_LIST_NORMAL_PREVIEW))
   {
        return TRUE;
   }
   return FALSE;
}

MMP_BE_BROWSER_STATUS_T a_mmp_get_av_stat(VOID)
{
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret = MMPR_OK;
    MMP_PLAY_STATE_T        e_back_play_state = MMP_PLAY_STATE_CLOSED;
    MMP_PLAY_STATE_T        e_fore_play_state = MMP_PLAY_STATE_CLOSED;
    MMP_FP_PRESENT_MODE_T   e_present_mode = MMP_FP_PRESENT_MODE_FULL;
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;

    do
    {
        if (MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
        {
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_FORE,
                                            &e_fore_play_state);
            if (MMPR_OK != i4_ret)
            {
                e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                break;
            }

            mmp_mc_list_get_play_present_mode(&e_present_mode);

            if (MMP_FP_PRESENT_MODE_FULL == e_present_mode)
            {
                if ((MMP_PLAY_STATE_PLAYING == e_fore_play_state)
                    ||(MMP_PLAY_STATE_PLAYED == e_fore_play_state))
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING;
                    break;
                }
                else if ((MMP_PLAY_STATE_PAUSING == e_fore_play_state)
                       ||(MMP_PLAY_STATE_PAUSED == e_fore_play_state))
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING;
                    break;
                }
                else if ((MMP_PLAY_STATE_FAST_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_FAST_FORWARDED == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_fore_play_state))
                {
                    e_mmp_browser_status =  MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING;
                    break;
                }
                else if ((MMP_PLAY_STATE_FAST_REWINDING == e_fore_play_state)
                         ||(MMP_PLAY_STATE_FAST_REWINDED == e_fore_play_state))

                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING;
                    break;
                }
                else
                {
                    if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_LIST_NOT_PLAYING;
                        break;
                    }
                    else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NOT_PLAYING;
                        break;
                    }
                    else
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                        break;
                    }
                }
            }
        }
        else if (MMP_MEDIA_TYPE_AUDIO == pt_this->e_filter_type)
        {
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK,
                                            &e_back_play_state);
            if (MMPR_OK != i4_ret)
            {
                e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                break;
            }

            if ((MMP_PLAY_STATE_PLAYING == e_back_play_state)
                ||(MMP_PLAY_STATE_PLAYED == e_back_play_state))
            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_NORMAL_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_NORMAL_PLAYING;
                    break;
                }
                else if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_FORE_NORMAL_PLAYING;
                    break;
                }
            }
            else if ((MMP_PLAY_STATE_FAST_FORWARDING == e_back_play_state)
                      ||(MMP_PLAY_STATE_FAST_FORWARDED == e_back_play_state)
                      ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_back_play_state)
                      ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_back_play_state))
            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_FF_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_FF_PLAYING;
                    break;
                }
                else if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_FORE_FF_PLAYING;
                    break;
                }
            }
            else if ((MMP_PLAY_STATE_FAST_REWINDING == e_back_play_state)
                     ||(MMP_PLAY_STATE_FAST_REWINDED == e_back_play_state))

            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_FR_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_FR_PLAYING;
                    break;
                }
                else if (MMP_MC_BWR_ID_NULL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_FORE_FR_PLAYING;
                    break;
                }
            }
            else
            {
                if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_LIST_NOT_PLAYING;
                    break;
                }
                else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_NOT_PLAYING;
                    break;
                }
                else
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                    break;
                }
            }
        }
    }while(0);

   return e_mmp_browser_status;
}

BOOL a_mmp_is_video_full_screen(VOID)
{
    BOOL                    b_ret = FALSE;
    MMP_BE_DATA_MEMBER_T*   pt_this = &t_g_browse_eng;
    INT32                   i4_ret = MMPR_OK;
    MMP_PLAY_STATE_T        e_fore_play_state = MMP_PLAY_STATE_CLOSED;
    MMP_FP_PRESENT_MODE_T   e_present_mode = MMP_FP_PRESENT_MODE_FULL;
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;

    do
    {
        /*if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status())
        {
            e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
            break;
        }*/

        if (MMP_MEDIA_TYPE_VIDEO == pt_this->e_filter_type)
        {
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_FORE,
                                            &e_fore_play_state);
            if (MMPR_OK != i4_ret)
            {
                e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                break;
            }

            mmp_mc_list_get_play_present_mode(&e_present_mode);

            if (MMP_FP_PRESENT_MODE_FULL == e_present_mode)
            {
                if ((MMP_PLAY_STATE_PLAYING == e_fore_play_state)
                    ||(MMP_PLAY_STATE_PLAYED == e_fore_play_state))
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING;
                    break;
                }
                else if ((MMP_PLAY_STATE_PAUSING == e_fore_play_state)
                       ||(MMP_PLAY_STATE_PAUSED == e_fore_play_state))
                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING;
                    break;
                }
                else if ((MMP_PLAY_STATE_FAST_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_FAST_FORWARDED == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDING == e_fore_play_state)
                          ||(MMP_PLAY_STATE_SLOW_FORWARDED == e_fore_play_state))
                {
                    e_mmp_browser_status =  MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING;
                    break;
                }
                else if ((MMP_PLAY_STATE_FAST_REWINDING == e_fore_play_state)
                         ||(MMP_PLAY_STATE_FAST_REWINDED == e_fore_play_state))

                {
                    e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING;
                    break;
                }
                else
                {
                    if (MMP_RC_BROWSER_ID_LIST == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_LIST_NOT_PLAYING;
                        break;
                    }
                    else if (MMP_RC_BROWSER_ID_THUMBNAIL == pt_this->ui1_act_bwr_id)
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NOT_PLAYING;
                        break;
                    }
                    else
                    {
                        e_mmp_browser_status = MMP_BE_BROWSER_STATUS_ERROR;
                        break;
                    }
                }
            }
        }
    }while(0);

    switch (e_mmp_browser_status)
    {
        case MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING:
        case MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING:
        case MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING:
        case MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING:
            b_ret = TRUE;
            break;
        default:
            b_ret = FALSE;
            break;
    }

   return b_ret;
}

#endif

/*----------------------------------------------------------------------------
* Name:    mmp_be_dlna_is_seek_supported
* Description:
* Input:   -
* Output:  -
* Returns
---------------------------------------------------------------------------*/
#ifdef APP_NET_DLNA_SUPPORT
BOOL mmp_be_dlna_is_seek_supported(CHAR* ps_name)
{
    BOOL b_support = FALSE;
    if( ps_name == NULL)
    {
        return FALSE;
    }
    b_support = c_fm_dlna_is_seek_supported(ps_name);
    return b_support;
}
#endif

#ifdef APP_CAST_TV_MMP_FG
INT32 mmp_be_reset(VOID)
{
    return _mmp_be_reset();
}

#endif




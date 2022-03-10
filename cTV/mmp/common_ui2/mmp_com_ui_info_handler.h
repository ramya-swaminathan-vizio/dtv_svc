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
 * $RCSfile: mmp_common_ui.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/

#ifndef _MMP_COM_UI_INFO_HANDLER_H_
#define _MMP_COM_UI_INFO_HANDLER_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "mmp/eq_spectrum/a_mmp_eq_viewer.h"
#include "res/mmp/eq_spectrum/mmp_eq_rc.h"
#include "mmp/app/mmp_main.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
#define MMP_COM_UI_AP_PLAY_INFO_MAX_ICON    (5)
#define MMP_COM_UI_AP_PLAY_INFO_MAX_TXT     (64)

#define MMP_FP_PP_FILE_INFO_ID_MAX      (3)
#define MMP_FP_VP_FILE_INFO_ID_MAX      (2)
#define MMP_FP_AP_FILE_INFO_ID_MAX      (5)
#define MMP_FP_TP_FILE_INFO_ID_MAX      (4)
#define MMP_FP_DIR_FILE_INFO_ID_MAX     (3)

#define MMP_FB_FOCUS_LIST_ELEM_H         (20)

#define MMP_FB_FOCUS_LOCK_ICON_X         (5)
#define MMP_FB_FOCUS_LOCK_ICON_Y         (0)
#define MMP_FB_FOCUS_LOCK_ICON_W         (15)
#define MMP_FB_FOCUS_LOCK_ICON_H         (17)

#define MMP_AP_INFO_HANDLE_COV_PIC_Y     (4)
#define MMP_AP_INFO_HANDLE_COV_PIC_W     (300)
#define MMP_AP_INFO_HANDLE_COV_PIC_H     (268)
#define MMP_AP_INFO_HANDLE_COV_PIC_X     (1920 - MMP_AP_INFO_HANDLE_COV_PIC_W - 2)

typedef struct {} *MMP_FOCUS_INFO_INST_T;

 typedef struct
 {
     /* widget handles */
     HANDLE_T       h_main_frm;
	 HANDLE_T       h_dolby_audio_icon;
     HANDLE_T       h_dolby_atmos_icon;
	 HANDLE_T       h_dolby_vision_hdr_hlg_icon;
     HANDLE_T       h_info_list;
     HANDLE_T       h_elapse_time;
     HANDLE_T       h_remain_time;
     HANDLE_T       h_progress_bar;
     HANDLE_T       h_lock_icon;
     HANDLE_T       h_hdr10plus_str;
     UINT32         ui4_list_enem_cnt;
 }MMP_COM_FP_FOCUS_INFO_VIEW_T;


 typedef struct {} *MMP_AP_CTRL_PANEL_INST_T;
 typedef struct {} *MMP_VP_IFNO_INST_T;
 typedef struct
 {
    /* widget handles */
    HANDLE_T        h_main_frm;
    HANDLE_T        h_vol_bar;
    HANDLE_T        h_pb_playback;
    HANDLE_T        ah_icon[MMP_COM_UI_AP_PLAY_INFO_MAX_ICON];
    HANDLE_T        ah_label[MMP_COM_UI_AP_PLAY_INFO_MAX_TXT];
    HANDLE_T        h_transparent_list;
    HANDLE_T        h_audio_play_img_fr;
 }MMP_COM_AP_PLAY_INFO_VIEW_T;

 typedef enum
 {
    MMP_COM_FP_INFO_UI_TYPE_TM = 0,
    MMP_COM_FP_INFO_UI_TYPE_LM ,
    MMP_COM_FP_INFO_UI_TYPE_LAST
 } MMP_COM_FP_INFO_UI_TYPE_T;

 typedef enum
 {
    MMP_COM_INFO_FP_EMPTY = 0,
    MMP_COM_INFO_FP_TYPE_VP = 0x01,
    MMP_COM_INFO_FP_TYPE_PP = 0x02,
    MMP_COM_INFO_FP_TYPE_AP = 0x04,
    MMP_COM_INFO_FP_TYPE_TP = 0x08
 } MMP_COM_INFO_FP_TYPE_T;

 typedef enum
 {
    MMP_COM_UI_FP_DATA_W2S = 0,
    MMP_COM_UI_FP_DATA_BOOL
 }MMP_COM_UI_FP_DATA_TYPE_T;

/*define the focus info player group*/
#define FOCUS_INFO_GROUP_VP             ((UINT8) 0x10)
#define FOCUS_INFO_GROUP_PP             ((UINT8) 0x20)
#define FOCUS_INFO_GROUP_AP             ((UINT8) 0x30)
#define FOCUS_INFO_GROUP_TP             ((UINT8) 0x40)
#define FOCUS_INFO_GROUP_DIR             ((UINT8) 0x50)

/* Typedef and constants for the focus info item index */
typedef UINT8  MMP_FP_FOCUS_INFO_ID_T;  /**< Typedef for the focus info item index */
/* video player group */
#define MMP_VP_FOCUS_INFO_ID_NAME            ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x00))    /**< file name, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_VP_FOCUS_INFO_ID_TIME              ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x03))    /**< creat time, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_VP_FOCUS_INFO_ID_DURATION     ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x02))    /**<duration, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_VP_FOCUS_INFO_ID_SIZE               ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x05))    /**< file size, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_VP_FOCUS_INFO_ID_READ_ONLY   ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x04))    /**< read only or not, only support MMP_COM_UI_FP_DATA_BOOL*/
#define MMP_VP_FOCUS_INFO_ID_RESOLUTION   ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x01))
#define MMP_VP_FOCUS_INFO_ID_AUDIO_FMT    ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_VP|0x02))

/* photo player group */
#define MMP_PP_FOCUS_INFO_ID_NAME           ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_PP|0x00))    /**< file name, only support MMP_COM_UI_FP_DATA_W2S*/
//#define MMP_PP_FOCUS_INFO_ID_TIME             ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_PP|0x01))    /**< creat time, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_PP_FOCUS_INFO_ID_RESLUTION      ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_PP|0x01))    /**<reslution, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_PP_FOCUS_INFO_ID_SIZE           ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_PP|0x02))    /**< file size, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_PP_FOCUS_INFO_ID_READ_ONLY      ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_PP|0x03))    /**< read only or not, only support MMP_COM_UI_FP_DATA_BOOL*/

/* audio player group */
#define MMP_AP_FOCUS_INFO_ID_ARTIST            ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_AP|0x00))    /**< only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_AP_FOCUS_INFO_ID_ALBUM             ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_AP|0x01))    /**<  only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_AP_FOCUS_INFO_ID_GERNER            ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_AP|0x02))    /**< only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_AP_FOCUS_INFO_ID_DATA              ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_AP|0x03))    /**<  only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_AP_FOCUS_INFO_ID_FILE_SIZE         ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_AP|0x04))    /**<  only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_AP_FOCUS_INFO_ID_READ_ONLY         ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_AP|0x05))    /**<  only support MMP_COM_UI_FP_DATA_BOOL*/

/* txt player group */
#define MMP_TP_FOCUS_INFO_ID_NAME               ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_TP|0x00))    /**< file name, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_TP_FOCUS_INFO_ID_TIME               ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_TP|0x01))    /**< creat time, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_TP_FOCUS_INFO_ID_SIZE               ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_TP|0x02))    /**< file size, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_TP_FOCUS_INFO_ID_READ_ONLY          ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_TP|0x03))    /**< read only or not, only support MMP_COM_UI_FP_DATA_BOOL*/

/* folder group */
#define MMP_DIR_FOCUS_INFO_ID_NAME              ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_DIR|0x00))    /**< file name, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_DIR_FOCUS_INFO_ID_UPD_DATE          ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_DIR|0x01))    /**< last update date, only support MMP_COM_UI_FP_DATA_W2S*/
#define MMP_DIR_FOCUS_INFO_ID_UPD_TIME          ((MMP_FP_FOCUS_INFO_ID_T) (FOCUS_INFO_GROUP_DIR|0x02))    /**< last update time , only support MMP_COM_UI_FP_DATA_W2S*/

typedef enum
{
    MMP_COM_FP_TYPE_VP = 0,
    MMP_COM_FP_TYPE_PP,
    MMP_COM_FP_TYPE_AP,
    MMP_COM_FP_TYPE_TP,
    MMP_COM_FP_TYPE_DIR,
    MMP_COM_FP_TYPE_CNT
}MMP_COM_FP_TYPE_T;

typedef UINT8  MMP_AP_CUR_PLAY_INFO_ID_T;  /*current playing audio in TM/LM ui*/

#define MMP_AP_CUR_PLAY_INFO_CUR_TIME             ((MMP_AP_CUR_PLAY_INFO_ID_T) 0)
#define MMP_AP_CUR_PLAY_INFO_TOTAL_TIME           ((MMP_AP_CUR_PLAY_INFO_ID_T) 1)
#define MMP_AP_CUR_PLAY_INFO_PG_VOL               ((MMP_AP_CUR_PLAY_INFO_ID_T) 2)
#define MMP_AP_CUR_PLAY_INFO_PG_POS               ((MMP_AP_CUR_PLAY_INFO_ID_T) 3)
#define MMP_AP_CUR_PLAY_INFO_REPEAT               ((MMP_AP_CUR_PLAY_INFO_ID_T) 4)
#define MMP_AP_CUR_PLAY_INFO_SHUFFLE              ((MMP_AP_CUR_PLAY_INFO_ID_T) 5)
#define MMP_AP_CUR_PLAY_INFO_PLAY_STATUS          ((MMP_AP_CUR_PLAY_INFO_ID_T) 6)
#define MMP_AP_CUR_PLAY_INFO_AB                   ((MMP_AP_CUR_PLAY_INFO_ID_T) 7)
#define MMP_AP_CUR_PLAY_INFO_FILE_NAME            ((MMP_AP_CUR_PLAY_INFO_ID_T) 8)
#define MMP_AP_CUR_PLAY_INFO_MUTE                 ((MMP_AP_CUR_PLAY_INFO_ID_T) 9)
#define MMP_AP_CUR_PLAY_INFO_VOL_BAR_SHOW         ((MMP_AP_CUR_PLAY_INFO_ID_T) 10)
#define MMP_AP_CUR_PLAY_INFO_ALBUM                ((MMP_AP_CUR_PLAY_INFO_ID_T) 11)
#define MMP_AP_CUR_PLAY_INFO_ARTIST               ((MMP_AP_CUR_PLAY_INFO_ID_T) 12)
#define MMP_AP_CUR_PLAY_INFO_COVER                ((MMP_AP_CUR_PLAY_INFO_ID_T) 13)
#define MMP_AP_CUR_PLAY_INFO_ELAPSE_TIME          ((MMP_AP_CUR_PLAY_INFO_ID_T) 14)
#define MMP_AP_CUR_PLAY_INFO_REMAIN_TIME          ((MMP_AP_CUR_PLAY_INFO_ID_T) 15)
#define MMP_AP_CUR_PLAY_INFO_GERNER               ((MMP_AP_CUR_PLAY_INFO_ID_T) 16)
#define MMP_AP_CUR_PLAY_INFO_YEAR                 ((MMP_AP_CUR_PLAY_INFO_ID_T) 17)
#define MMP_AP_CUR_PLAY_INFO_DIRECTOR             ((MMP_AP_CUR_PLAY_INFO_ID_T) 18)
#define MMP_AP_CUR_PLAY_INFO_PRODUCER             ((MMP_AP_CUR_PLAY_INFO_ID_T) 19)
#define MMP_AP_CUR_PLAY_INFO_FILE_SIZE            ((MMP_AP_CUR_PLAY_INFO_ID_T) 20)
#define MMP_AP_CUR_PLAY_INFO_DURATION             ((MMP_AP_CUR_PLAY_INFO_ID_T) 21)
#define MMP_AP_CUR_PLAY_INFO_PROTECT              ((MMP_AP_CUR_PLAY_INFO_ID_T) 22)
#define MMP_AP_CUR_PLAY_INFO_TITLE                ((MMP_AP_CUR_PLAY_INFO_ID_T) 23)


typedef UINT8  MMP_VP_CUR_PLAY_INFO_ID_T;  /*current playing video in TM/LM ui*/

#define MMP_VP_CUR_PLAY_INFO_PG_POS               ((MMP_VP_CUR_PLAY_INFO_ID_T) 0)
#define MMP_VP_CUR_PLAY_INFO_ELAPSE_TIME          ((MMP_AP_CUR_PLAY_INFO_ID_T) 1)
#define MMP_VP_CUR_PLAY_INFO_REMAIN_TIME          ((MMP_AP_CUR_PLAY_INFO_ID_T) 2)

typedef enum _MMP_AP_PLAY_VOL_STATUS_T
{
    MMP_AP_PLAY_VOL_MUTE = 0,
    MMP_AP_PLAY_VOL_NORMAL
} MMP_AP_PLAY_VOL_STATUS_T;


typedef enum _MMP_AP_PLAY_INFO_ICON_ID_T
{
    MMP_AP_PLAY_INFO_ICON_ID_STATUS = 0,
    MMP_AP_PLAY_INFO_ICON_ID_REPEAT,
    MMP_AP_PLAY_INFO_ICON_ID_AB,
    MMP_AP_PLAY_INFO_ICON_ID_SHUFFLE,
    MMP_AP_PLAY_INFO_ICON_ID_VOL,
    MMP_AP_PLAY_INFO_ICON_COUNT
} MMP_AP_PLAY_INFO_ICON_ID_T;

typedef enum _MMP_AP_PLAY_INFO_LBL_ID_T
{
    MMP_AP_PLAY_INFO_LBL_ID_FILE_NAME =0,
    MMP_AP_PLAY_INFO_LBL_ID_POS,
    MMP_AP_PLAY_INFO_LBL_ID_DUR,
    MMP_AP_PLAY_INFO_LBL_ID_ALBUM,
    MMP_AP_PLAY_INFO_LBL_ID_ALBUM_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_ARTIST,
    MMP_AP_PLAY_INFO_LBL_ID_ARTIST_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_NAME_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_DURATION_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_SIZE_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_TITLE,
    MMP_AP_PLAY_INFO_LBL_ID_GERNER,
    MMP_AP_PLAY_INFO_LBL_ID_YEAR,
    MMP_AP_PLAY_INFO_LBL_ID_DIRECTOR,
    MMP_AP_PLAY_INFO_LBL_ID_PRODUCER,
    MMP_AP_PLAY_INFO_LBL_ID_PROTECT,
    MMP_AP_PLAY_INFO_LBL_ID_SIZE,
    MMP_AP_PLAY_INFO_LBL_ID_DURATION,
    MMP_AP_PLAY_INFO_LBL_ID_GERNER_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_YEAR_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_DIRECTOR_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_PRODUCER_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_PROTECT_HINT,
    MMP_AP_PLAY_INFO_LBL_ID_TITLE_HINT,
    MMP_AP_PLAY_INFO_LBL_COUNT
} MMP_AP_PLAY_INFO_LBL_ID_T;

typedef enum
{
    MMP_INFO_NON_REPAINT = 0,
    MMP_INFO_SYNC_REPAINT,
    MMP_INFO_ASYNC_REPAINT,
    MMP_INFO_REPAINT_COUNT
} MMP_INFO_REPAINT_TYPE_T;

 typedef enum
 {
     MMP_VP_PROG_BAR_TYPE_TIME,
     MMP_VP_PROG_BAR_TYPE_FILE

 } MMP_VP_PROG_BAR_TYPE_T;

 /*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
extern INT32 mmp_com_ui_focus_info_frm_create(
                            HANDLE_T                    h_parent,
                            MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                            MMP_COM_INFO_FP_TYPE_T      e_fp_type,
                            VOID**                      ppv_fo_inst);

extern INT32 mmp_com_ui_focus_info_frm_active(
                            VOID*                       pv_fo_inst,
                            MMP_COM_FP_TYPE_T           e_type,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_focus_info_frm_inactive(
                            VOID*                       pv_fo_inst,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_focus_info_frm_destroy(
                            MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                            MMP_COM_INFO_FP_TYPE_T      e_fp_type,
                            VOID*                       pv_fo_inst);

extern INT32 mmp_com_ui_fp_focus_set_elem_num(
                            VOID*                       pv_fo_inst,
                            MMP_COM_FP_TYPE_T           e_type,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_fp_set_focus_info(
                            VOID*                       pv_fo_inst,
                            MMP_FP_FOCUS_INFO_ID_T      e_idx,
                            MMP_COM_UI_FP_DATA_TYPE_T   e_data_type,
                            VOID*                       pv_data,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_ap_info_frm_create(
                            HANDLE_T                    h_parent,
                            MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                            VOID**                      ppv_ap_inst);

extern INT32 mmp_com_ui_focus_info_frm_repaint(
                            VOID*                       pv_fo_inst,
                            MMP_INFO_REPAINT_TYPE_T     e_repaint_type);

extern INT32 mmp_com_ui_ap_info_frm_active(
                            VOID*                       pv_ap_inst,
                            UINT16                      ui2_lang,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_ap_info_frm_inactive(
                            VOID*                       pv_ap_inst,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_ap_info_frm_destroy(
                            MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                            VOID*                       pv_ap_inst);

extern INT32 mmp_com_ui_ap_info_hdlr_frm_repaint(VOID*         pv_ap_inst,
                                                  BOOL         b_repaint);

extern INT32 mmp_com_ui_vp_info_hdlr_frm_repaint(VOID*         pv_ap_inst,
                                                  BOOL         b_repaint);

extern INT32 mmp_com_ui_ap_set_play_info(
                            VOID*                       pv_ap_inst,
                            MMP_AP_CUR_PLAY_INFO_ID_T   e_idx,
                            VOID*                       pv_data,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_vp_set_play_info(
                            VOID*                       pv_fo_inst,
                            MMP_VP_CUR_PLAY_INFO_ID_T   e_idx,
                            VOID*                       pv_data,
                            MMP_VP_PROG_BAR_TYPE_T      ui4_vp_bar_type,
                            BOOL                        b_repaint);

extern INT32 mmp_com_ui_vp_update_info_dolby_audio(VOID*           pv_fo_inst,
                                                   WGL_HIMG_TPL_T  h_img);
												   
extern INT32 mmp_com_ui_ap_info_show_process_bar(VOID*     pv_ap_inst,
                                                 BOOL      b_show,
                                                 BOOL      b_repaint);

extern INT32 mmp_com_ui_vp_update_info_dolby_atmos(VOID*          pv_fo_inst, 
                                                 WGL_HIMG_TPL_T   h_img);

extern INT32 mmp_com_ui_vp_update_info_dolby_hdr_hlg_vision( VOID*           pv_fo_inst,
                                                     WGL_HIMG_TPL_T  h_img);
extern INT32 mmp_com_ui_vp_update_info_HDR10plus(VOID*    pv_fo_inst, UTF16_T *   h_str);


#endif /*_MMP_COM_UI_INFO_HANDLER_H_*/

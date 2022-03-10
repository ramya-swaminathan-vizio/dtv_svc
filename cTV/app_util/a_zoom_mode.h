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
 * $RCSfile: a_zoom_mode.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: $
 * $MD5HEX: 0555add6f5bb32c55eaf504cbf527d75 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_ZOOM_MODE_H_
#define _A_ZOOM_MODE_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"

#include "app_util/a_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* Return Value */
#define ZMR_OK                          ((INT32)  0)
#define ZMR_INV_ARG                     ((INT32) -1)
#define ZMR_FAIL                        ((INT32) -2)
#define ZMR_OUT_OF_MEMORY               ((INT32) -3)

/* To be used to create an ID to be used for nav zoom routines */
#define ZOOM_MAKE_ID(ui1_group, ui1_idx)    ((UINT16)(((ui1_group & 0x7f) << 8) | (ui1_idx)))
#define ZOOM_GET_GROUP(ui2_id)              ((UINT8)(((ui2_id) >> 8) & 0x7f))
#define ZOOM_GET_IDX(ui2_id)                ((UINT8)((ui2_id) & 0xff))

#define ZOOM_SECTOR_SHOW_MASK                   ((UINT16)(1 << 15))
#define ZOOM_SHOW_MAKE_ID(ui1_group, ui1_idx)   ((UINT16)(((ui1_group & 0x7f) << 8) | (ui1_idx) | ZOOM_SECTOR_SHOW_MASK))
#define ZOOM_HIDE_MAKE_ID(ui1_group, ui1_idx)   ZOOM_MAKE_ID(ui1_group, ui1_idx)

#define ZOOM_VSH_REGION_MAX_WIDTH      ((UINT32) 10000)
#define ZOOM_VSH_REGION_MAX_HEIGHT     ((UINT32) 10000)

#define ZOOM_VSH_REGION_WGL_WIDTH      ((UINT32) 1920)//1280
#define ZOOM_VSH_REGION_WGL_HEIGHT     ((UINT32) 1080)//720

#define ZOOM_SECTOR_MAX_NUM             (ZOOM_SECTOR_ITEM_9)
#define ZOOM_SECTOR_DEFAULT_ITEM        (ZOOM_SECTOR_ITEM_2)
#define ZOOM_SECTOR_INVALID_ITEM        (ZOOM_SECTOR_MAX_NUM + 1)

typedef UINT16                          ZOOM_SECTOR_SET_T ;

#define ZOOM_SECTOR_IDX_TO_ID(_idx)     ((ZOOM_SECTOR_SET_T) ( ((ZOOM_SECTOR_SET_T)1) << _idx) )


typedef enum {
    ZOOM_SECTOR_ITEM_1                  = 1,
    ZOOM_SECTOR_ITEM_2,
    ZOOM_SECTOR_ITEM_3,
    ZOOM_SECTOR_ITEM_4,
    ZOOM_SECTOR_ITEM_5,
    ZOOM_SECTOR_ITEM_6,
    ZOOM_SECTOR_ITEM_7,
    ZOOM_SECTOR_ITEM_8,
    ZOOM_SECTOR_ITEM_9
} ZOOM_SECTOR_ITEM;


/* Define group */
enum ZOOM_APP_GROUP_ID {
    ZOOM_APP_GRPID_MENU                 = 0,
    ZOOM_APP_GRPID_NAV,
    ZOOM_APP_GRPID_MMP,
    ZOOM_APP_GRPID_WZD,
    ZOOM_APP_GRPID_3RD_APP,
    ZOOM_APP_GRPID_LAST_VALID_ENTRY     // must <= 127 (0x7f)
};

/* Define group menu item */
enum ZOOM_GROUP_MENU {
    ZOOM_APP_RECID_MENU_DEFAULT         = 0,
    ZOOM_APP_RECID_MENU_SCREEN_MODE,
    ZOOM_APP_RECID_MENU_DIALOG,
    ZOOM_APP_RECID_MENU_PIC_SIZE,
    ZOOM_APP_RECID_MENU_EQUALIZER,
    ZOOM_APP_RECID_MENU_COLOR_TUNER,
    ZOOM_APP_RECID_MENU_SLIDER,
    ZOOM_APP_RECID_MENU_LAST_VALID_ENTRY
};

/* Define group navi comp, refer to NAV_COMP_ID_T */
enum ZOOM_GROUP_NAV {
    ZOOM_APP_RECID_NAV_DEFAULT          = 128,
    ZOOM_APP_RECID_NAV_LAST_VALID_ENTRY
};

/* Define group MMP item */
enum ZOOM_GROUP_MMP {
    ZOOM_APP_RECID_MMP_DEFAULT          = 0,
    ZOOM_APP_RECID_MMP_VP_TB_SHOW,
    ZOOM_APP_RECID_MMP_LAST_VALID_ENTRY
};

/* Define group Wizard item */
enum ZOOM_GROUP_WZD {
    ZOOM_APP_RECID_WZD_DEFAULT          = 0,
    ZOOM_APP_RECID_WZD_LAST_VALID_ENTRY
};

/* Define group Third Party APP item */
enum ZOOM_GROUP_3RD_APP {
    ZOOM_APP_RECID_APP_DEFAULT      = 0,
    ZOOM_APP_RECID_YH_DOCK,
    ZOOM_APP_RECID_YH_SIDEBAR,
    ZOOM_APP_RECID_RETAIL_MODE,
    ZOOM_APP_RECID_RETAIL_DIALOG,
    ZOOM_APP_RECID_APP_FULL_SCREEN,
    ZOOM_APP_RECID_APP_LAST_VALID_ENTRY
};

typedef struct _ZOOM_SECTOR_REGION_T
{
    UINT32          ui4_x;
    UINT32          ui4_y;
    UINT32          ui4_w;
    UINT32          ui4_h;
}ZOOM_SECTOR_REGION_T;

typedef struct _ZOOM_VSH_REGION_POINT_T
{
    UINT32          ui4_x;
    UINT32          ui4_y;
}ZOOM_VSH_REGION_POINT_T;

typedef struct _ZOOM_VSH_REGION_COORDINATE_T
{
    UINT8                   ui1_interface;
    ZOOM_VSH_REGION_POINT_T t_left_top;
    ZOOM_VSH_REGION_POINT_T t_right_bottom;
}ZOOM_VSH_REGION_COORDINATE_T;

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_zoom_mode_init(VOID);

extern INT32 a_zoom_mode_enable(VOID);

extern INT32 a_zoom_mode_disable(VOID);
#ifdef VIZIO_FUSION_SUPPORT

extern INT32 a_zoom_mode_enlarge_sector(
    GL_OSD_ZOOM_SECTOR_T    at_zoom_sector[],
    UINT32                  ui4_zoom_sector_count
    );
#endif
extern BOOL  a_zoom_mode_get_status(VOID);

extern ZOOM_SECTOR_ITEM a_zoom_mode_get_current_sector(VOID);

extern INT32 a_zoom_mode_select_sector(UINT8 ui1_sector, BOOL b_need_store);

extern INT32 a_zoom_mode_enlarge_region(ZOOM_VSH_REGION_COORDINATE_T* pt_zoom_region);

extern INT32 a_zoom_mode_enlarge_wgl_hl_area(UINT16 ui2_id, GL_RECT_T* pt_rect);

extern INT32 a_zoom_mode_set_sector_id(UINT16 ui2_id);

extern INT32 a_zoom_clean_slist(VOID);
extern INT32 a_zoom_remove_fields_from_slist(const UINT8 ui1_app);
extern INT32 a_zoom_add_field_into_slist_head(const UINT16 ui2_id, ZOOM_SECTOR_ITEM e_item);
extern INT32 a_zoom_move_field_to_slist_head(const UINT16 ui2_id);
extern INT32 a_zoom_update_1st_sector_item_in_slist(ZOOM_SECTOR_ITEM e_item);
extern ZOOM_SECTOR_ITEM a_zoom_get_1st_sector_item_from_slist(VOID);
extern ZOOM_SECTOR_ITEM a_zoom_get_sector_item_from_slist(const UINT16 ui2_id);
extern BOOL  a_zoom_has_item_in_slist(const UINT16 ui2_id);

extern BOOL a_zoom_check_sector_has_content(ZOOM_SECTOR_ITEM e_item);

#endif /* _A_ZOOM_MODE_H_ */

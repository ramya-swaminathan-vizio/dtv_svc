/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: wzd_anim.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: aea1eb83e1965ae12a196e8d60ad5cd0 $
 *
 * Description:
 *      This file contains the declarations of GUI-realted typedefs, macros, data, 
 * and functions of the WIZARD application
 *---------------------------------------------------------------------------*/
#ifndef _WZD_ANIM_H_
#define _WZD_ANIM_H_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_animation.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#ifndef WZD_ANIM_FRAME_WGL_DEFAULT_STL
    #define WZD_ANIM_FRAME_WGL_DEFAULT_STL   WGL_STL_GL_ANIM_AFFECT_CHILD
#endif


#ifndef WGL_ANIM_SUPPORT
#define WGL_ANIM_SUPPORT
#endif

/*
    Feature List
*/
typedef enum {
    /* Menu Animation configuration */
    WZD_FT_UI_SUPPORT_FONT_ENLARGE = 0,          /* Support font enlarge */
    WZD_FT_UI_SUPPORT_IMAGE_ENLARGE,             /* Support image enlarge */
    WZD_FT_UI_SUPPORT_ITEM_MOVE_ANIMATION,       /* Support item move animation */
    WZD_FT_UI_SUPPORT_FADE_IN_OUT_ANIMATION,     /* Support fade in out animation */
    WZD_FT_UI_SUPPORT_ICON_ANIMATION,            /* Support icon animation */
    WZD_FT_LAST_ENTRY                            /* Last entry, counter purpose */
} WZD_FT_CFG_T;

/*
    Animation Type
*/
typedef enum {
    /* Menu Animation configuration */
    WZD_ANIM_TYPE_MOVE = 0,                     /* move animation */
    WZD_ANIM_TYPE_ALPHA,                        /* alpha animation */
    WZD_ANIM_TYPE_SCALE,                        /* scale animation */
    WZD_ANIM_TYPE_MIX,                          /* move/alpha/scale animathion */
    WZD_ANIM_TYPE_LAST_ENTRY                    /* Last entry, counter purpose */
} WZD_ANIM_TYPE_T;

/* Animation move page frame type */
typedef enum _WZD_ANIM_MOVE_PAGE_TYPE_T
{
    WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER = 0,
    WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT,
    WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER,
    WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT,
    WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM
}WZD_ANIM_MOVE_PAGE_TYPE_T;

typedef enum {
    WZD_CALLBACK_PARAM_NOTHING = 0,
    WZD_CALLBACK_PARAM_SCALE_DOWN,
    WZD_CALLBACK_PARAM_SCALE_UP,
    WZD_CALLBACK_PARAM_LEFT,
    WZD_CALLBACK_PARAM_RIGHT,
} WZD_CALLBACK_PARAM;

typedef enum {
    WZD_ANIM_CB_STATUS_INIT = 0,
    WZD_ANIM_CB_STATUS_RUNNING,
    WZD_ANIM_CB_STATUS_END
} WZD_ANIM_CB_STATUS;

typedef struct
{
    UINT16 ui2_total_steps;
    UINT16 ui2_frame_interval;
    
    INT16  i2_start_x;
    INT16  i2_start_y;
    INT16  i2_end_x;
    INT16  i2_end_y;
} ANIM_DATA_MOVE_T;

typedef struct
{
    UINT16 ui2_total_steps;
    UINT16 ui2_frame_interval;
    
    UINT8  ui1_start_alpha;
    UINT8  ui1_end_alpha;

} ANIM_DATA_ALPHA_T;

typedef struct
{
    UINT16 ui2_total_steps;
    UINT16 ui2_frame_interval;
    UINT32 ui4_start_tick;
    
    UINT32 ui8_start_w;
    UINT32 ui8_start_h;
    UINT32 ui8_end_w;
    UINT32 ui8_end_h;
    
} ANIM_DATA_SCALE_T;

typedef struct
{
    UINT16 ui2_frame_interval;
    UINT32 ui4_start_tick;

    /* move */
    UINT16 ui2_move_steps;
    INT16  i2_start_x;
    INT16  i2_start_y;
    INT16  i2_end_x;
    INT16  i2_end_y;

    /* scale */
    UINT16 ui2_scale_steps;
    UINT32 ui8_start_w;
    UINT32 ui8_start_h;
    UINT32 ui8_end_w;
    UINT32 ui8_end_h;

    /* alpha */
    UINT16 ui2_alpha_steps;
    UINT8  ui1_start_alpha;
    UINT8  ui1_end_alpha;

} ANIM_DATA_MIX_T;

typedef struct
{
    UINT16 ui2_total_steps;
    UINT16 ui2_frame_interval;
    
    INT16  i2_start_x;
    INT16  i2_start_y;
    INT16  i2_end_x;
    INT16  i2_end_y;
    wgl_app_anim_type_cb_fct pf_type_cb;	
} ANIM_DATA_IMG_T;

typedef struct _WZD_ANIM_INFO_T
{
    WZD_ANIM_TYPE_T                 e_type;
    union
    {
            ANIM_DATA_MOVE_T        t_move;
            ANIM_DATA_ALPHA_T       t_alpha;
            ANIM_DATA_SCALE_T       t_scale;
            ANIM_DATA_MIX_T         t_mix;
    } u_anim_data;
} WZD_ANIM_INFO_T;

#define WZD_ANIM_PAGE_MOVE_STEPS    5
#define WZD_ANIM_SCALE_TOTAL_STEPS  4

/*-----------------------------------------------------------------------------
                            data declaration
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

extern BOOL  wzd_anim_has_feature (WZD_FT_CFG_T  e_feature);

extern INT32 wzd_anim_init(VOID);

extern INT32 wzd_anim_deinit(VOID);

extern INT32 wzd_anim_start_animation(
                        WZD_ANIM_TYPE_T     e_anim_type,
                        VOID*               pv_param1,
                        VOID*               pv_param2);

/* in-used */
extern INT32 wzd_anim_start_move_page(
                        WZD_ANIM_MOVE_PAGE_TYPE_T e_move_type);

extern INT32 wzd_anim_fade_out_scale_down(
                        HANDLE_T            h_anim_scale);

extern INT32 wzd_anim_small_sb_scale_down(
                        HANDLE_T  h_anim_scale);

extern INT32 wzd_anim_scale_up(
                        HANDLE_T            h_anim_scale);

extern INT32 wzd_anim_scale_down_up(
                        HANDLE_T            h_anim_scale);

extern INT32 wzd_anim_set_feature_cfg(
                        WZD_FT_CFG_T        e_feature,
                        BOOL                b_enable);

extern INT32 a_wzd_anim_mix (
                        HANDLE_T            h_widget,
                        ANIM_DATA_MIX_T*    pt_anim_data,
                        BOOL                b_end);

extern INT32 a_wzd_anim_image_move(
                        HANDLE_T            h_widget, 
                        ANIM_DATA_IMG_T*    t_anim_data, 
                        BOOL                b_end);

extern INT32 a_wzd_anim_move(
                        HANDLE_T            h_widget, 
                        ANIM_DATA_MOVE_T*   t_anim_data, 
                        BOOL                b_end);

extern INT32 a_wzd_anim_move_ex(
                        HANDLE_T            h_widget, 
                        ANIM_DATA_MOVE_T*   t_anim_data, 
                        BOOL                b_end);

extern INT32 a_wzd_anim_scale(
                        HANDLE_T            h_widget,
                        ANIM_DATA_SCALE_T*  t_anim_data,
                        BOOL                b_end);

extern INT32 a_wzd_anim_alpha(
                        HANDLE_T            h_widget,
                        ANIM_DATA_ALPHA_T*  pt_alpha_data,
                        BOOL                b_end);

extern INT32 a_wzd_anim_end(
                        HANDLE_T            h_widget);

extern INT32 a_wzd_anim_set_cb(
                        HANDLE_T            h_anim_handle,
                        wgl_app_anim_callback_fct pf_anim_nfy_fct,
                        VOID*               pv_tag);

#endif  /* _WZD_ANIM_H_ */

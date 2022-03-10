/********************************************************************************************
 *     LEGAL DISCLAIMER 
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES 
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED 
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS 
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, 
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY 
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, 
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK 
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION 
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *     
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH 
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, 
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE 
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
 *     
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS 
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.  
 ************************************************************************************************/
/*-----------------------------------------------------------------------------
 * $RCSfile: bluetooth_gattc_proc.c $
 * $Revision: 
 * $Date: 
 * $Author: 
 * $CCRevision: $
 * $SWAuthor: TOOL $
 * $MD5HEX: $
 *
 * Description: 
 *---------------------------------------------------------------------------*/

 
#ifdef APP_BLUETOOTH_SUPPORT
 /*-----------------------------------------------------------------------------
					 include files
 -----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


#include "u_common.h"
#include "u_sys_name.h"
#include "u_dbg.h"
#include "u_wgl_tools.h"
 
#include "c_dbg.h"
#include "c_uc_str.h"
#include "c_os.h"


#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_os.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
 
#include "bluetooth_gattc_rssimeter_view.h"
#include "bluetooth_gattc.h"


#define         _RSSI_ITEM_NUM          (11)
#define         _RSSI_TIMER_DELAY       (10000)

#define         _RSSI_TEXT_COLOR_WHITE  E_RSSI_WHITE
#define         _RSSI_TEXT_COLOR_RED    E_RSSI_RED
#define         _RSSI_TEXT_COLOR_GREEN  E_RSSI_GREEN
#define         _RSSI_TEXT_COLOR_YELLOW E_RSSI_YELLOW

/* The screen size */
#define SCREEN_W                        ((INT32)ui4_canvas_width)
#define SCREEN_H                        ((INT32)ui4_canvas_height)

#define MAIN_FRM_W                      (400)
#define MAIN_FRM_H                      (400)
#define MAIN_FRM_X                      (SCREEN_W-MAIN_FRM_W)/2
#define MAIN_FRM_Y                      (SCREEN_H-MAIN_FRM_H)/2

#define _ONE_MINUTE_IN_MS               ((UINT32)60000)

#define         _CHECK_FAIL_RETURN(_ret)      do{if (_ret != 0){DBG_ERROR(("<BT_GATT>Line %d: return %d\n",__LINE__,_ret));return _ret;}}while(0)


/***************************************static variable defines**************************************/
static T_RSSI_METER             t_g_rssi_meter;

static BOOL                     b_inited;
static HANDLE_T                 h_timer;
static BOOL                     b_show;
static GL_HPLANE_T              h_plane;
static HANDLE_T                 h_canvas;
static HANDLE_T                 h_frm_root;
static HANDLE_T                 h_frm_main;
static HANDLE_T                 h_rssi_list;
static UINT8                    ui1_color;
static UINT32                   ui4_g_start_time;
static INT32                    i4_g_total_rssi;

static UINT32                   ui4_canvas_width;
static UINT32                   ui4_canvas_height;

static GL_COLOR_T               t_g_rssi_color_transp = { 0,   {   0 }, {   0 }, {   0 }};
static GL_COLOR_T               t_g_rssi_color_white = { 200, { 255 }, { 255 }, { 255 }};
static GL_COLOR_T               t_g_rssi_color_green   = {200, {  0}, {  255}, {0}};
static GL_COLOR_T               t_g_rssi_color_red     = {200, {255}, {  0}, {  0}};
static GL_COLOR_T               t_g_rssi_color_yellow  = {200, {255}, {255}, {  0}};
static GL_COLOR_T               t_g_rssi_color_gray    = {128, {131}, {139}, {  139}};

static CHAR                     *ps_status_string_map[E_RSSI_END] = {
                                    "WHITE",
                                    "RED",
                                    "GREEN",
                                    "YELLOW"
                                };

static UTF16_T                  *aw2s_rssi_titles[_RSSI_ITEM_NUM] = {
                                                                        L"BLE Signal Meter",
                                                                        L"Status: ",
                                                                        L"RSSI: ",
                                                                        L"From: ",
                                                                        L"RSSI Threshold: ",
                                                                        L"Best RSSI: ",
                                                                        L"Worst RSSI: ",
                                                                        L"Average RSSI: ",
                                                                        L"Pings: ",
                                                                        L"Per minute: ",
                                                                        L"Countdown: "
                                                                    };
/****************************************functions declarations*************************************/


/*****************************************static functions defines***********************************/
static INT32 _wgl_callback(UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    return 0;
}

static INT32 _init_canvas (VOID)
{
    INT32            i4_ret;
    GL_HSCREEN_T     h_screen = NULL_HANDLE;

    BT_GATT_ENTER_FUNCTION();

    /*Open the screen */
    i4_ret = c_gl_screen_open (SN_PRES_MAIN_DISPLAY,
                               NULL,
                               NULL,
                               & h_screen);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<BT_GATT>Can't open screen\n\r"));
        return BLUETOOTH_GATTC_FAILED;
    }

    /*Open the plane */
    i4_ret = c_gl_plane_open (h_screen,
                              1,
                              &h_plane);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<BT_GATT>Can't open plane\n\r"));
        c_handle_free(h_screen);
        return BLUETOOTH_GATTC_FAILED;
    }

    /*Link the plane*/
    i4_ret = c_gl_plane_link (h_plane, h_screen, TRUE);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<BT_GATT>Can't link plane\n\r"));
        c_handle_free(h_screen);
        c_handle_free(h_plane);
        return BLUETOOTH_GATTC_FAILED;
    }

    /*Open the canvas */
    i4_ret = c_wgl_get_canvas (h_plane,
                               & h_canvas);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<BT_GATT>Can't get canvas %d\n\r", i4_ret));
        c_handle_free(h_screen);
        c_handle_free(h_plane);
        return BLUETOOTH_GATTC_FAILED;
    }


    i4_ret = c_wgl_get_canvas_size(h_canvas,
                                   &ui4_canvas_width,
                                   &ui4_canvas_height);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<BT_GATT>Can't get canvas %d\n\r", i4_ret));
    }

    /* Free the handles */
    c_handle_free(h_screen);
    return BLUETOOTH_GATTC_OK;
}

static INT32 _init_frm_root(VOID)
{
    INT32                   i4_ret;
    GL_RECT_T               t_rect;

    BT_GATT_ENTER_FUNCTION();

    /* Init Caption Preview Frame */
    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     SCREEN_W,
                     SCREEN_H);
    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 0,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI),
                                 0,
                                 &h_frm_root);
    _CHECK_FAIL_RETURN(i4_ret);

    return BLUETOOTH_GATTC_OK;
}

static INT32 _init_frm_main(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_style;
    WGL_COLOR_INFO_T t_clr_info;

    BT_GATT_ENTER_FUNCTION();

    ui4_style = WGL_STL_GL_NO_IMG_UI;

    SET_RECT_BY_SIZE(&t_rect,
                     MAIN_FRM_X,
                     MAIN_FRM_Y,
                     MAIN_FRM_W,
                     MAIN_FRM_H);

    i4_ret = c_wgl_create_widget(h_frm_root,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_frm_main);
    _CHECK_FAIL_RETURN(i4_ret);

    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_rssi_color_gray;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_rssi_color_gray;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_rssi_color_gray;

    i4_ret = c_wgl_do_cmd(h_frm_main,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info));
    _CHECK_FAIL_RETURN(i4_ret);


    return BLUETOOTH_GATTC_OK;
}

static INT32 _list_create(VOID)
{
    INT32 i4_ret;
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT8                       ui1_col;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    GL_RECT_T                   t_rect;
    HANDLE_T                    *ph_lb = &h_rssi_list;
    UINT16                      ui2_i = 0;
    WGL_LB_ITEM_T               at_items[3];

    BT_GATT_ENTER_FUNCTION();

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 128;
    at_cols[0].ui2_width        = MAIN_FRM_W-20;//(MAIN_FRM_W-20)/2;
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = 128;
    at_cols[1].ui2_width        = 0;//(MAIN_FRM_W-20)/2;
    
    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH|WGL_STL_LB_NO_WRAP_OVER|WGL_STL_GL_NO_IMG_UI;
    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = 40;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                     0,
                     0,
                     MAIN_FRM_W,
                     MAIN_FRM_H);

    i4_ret = c_wgl_create_widget (h_frm_main,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)&t_lb_init,
                                  NULL,
                                  ph_lb);
    _CHECK_FAIL_RETURN(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    for(ui1_col=0; ui1_col < t_lb_init.ui1_col_num; ui1_col++)
    {
        if(t_lb_init.at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK((UINT16)ui1_col),
                                   WGL_PACK(&t_fnt_info));
            _CHECK_FAIL_RETURN(i4_ret);
        }
   }

    /* Set Inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_GL_SET_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    _CHECK_FAIL_RETURN(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    _CHECK_FAIL_RETURN(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 10;
    t_inset.i4_right  = 10;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    _CHECK_FAIL_RETURN(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    for(ui1_col=0; ui1_col < t_lb_init.ui1_col_num; ui1_col++)
    {
        if(ui1_col == 0)
        {
            t_inset.i4_left = 0;
        }
        else
        {
            t_inset.i4_left = 10;
        }

        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_INSET,
                               WGL_PACK((UINT16)ui1_col),
                               WGL_PACK(&t_inset));
        _CHECK_FAIL_RETURN(i4_ret);
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_rssi_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_rssi_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_rssi_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    _CHECK_FAIL_RETURN(i4_ret);

    t_clr_elem.t_normal            = t_g_rssi_color_transp;
    t_clr_elem.t_disable           = t_g_rssi_color_transp;
    t_clr_elem.t_highlight         = t_g_rssi_color_transp;
    t_clr_elem.t_highlight_unfocus = t_g_rssi_color_transp;
    t_clr_elem.t_pushed            = t_g_rssi_color_transp;
    t_clr_elem.t_selected          = t_g_rssi_color_transp;
    t_clr_elem.t_selected_disable  = t_g_rssi_color_transp;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    _CHECK_FAIL_RETURN(i4_ret);

    for(ui1_col=0; ui1_col < t_lb_init.ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2(ui1_col, WGL_CLR_BK),
                               WGL_PACK(& t_clr_elem));
        _CHECK_FAIL_RETURN(i4_ret);
    }

    t_clr_elem.t_normal            = t_g_rssi_color_white;
    t_clr_elem.t_disable           = t_g_rssi_color_white;
    t_clr_elem.t_highlight         = t_g_rssi_color_white;
    t_clr_elem.t_highlight_unfocus = t_g_rssi_color_white;
    t_clr_elem.t_pushed            = t_g_rssi_color_white;
    t_clr_elem.t_selected          = t_g_rssi_color_white;
    t_clr_elem.t_selected_disable  = t_g_rssi_color_white;
    for(ui1_col=0; ui1_col < t_lb_init.ui1_col_num; ui1_col++)
    {
        if(t_lb_init.at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_COLOR,
                                   WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                   WGL_PACK(& t_clr_elem));
            _CHECK_FAIL_RETURN(i4_ret);
        }
    }

    /* Set LB elements */
    for (ui2_i=0; ui2_i<_RSSI_ITEM_NUM-1; ui2_i++)
    {
        at_items[0].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text = aw2s_rssi_titles[ui2_i];

        at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text   = L"";

        i4_ret = c_wgl_do_cmd(h_rssi_list, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        _CHECK_FAIL_RETURN(i4_ret);
    }
    
    return BLUETOOTH_GATTC_OK;
}

static VOID _timer_cb_fct (HANDLE_T  pt_tm_handle,
                           VOID*     pv_tag)
{
    BT_GATT_ENTER_FUNCTION();
    a_bluetooth_gattc_rssi_meter_hide();
}

static INT32 _rssi_meter_timer_start(VOID)
{
    INT32 i4_ret = BLUETOOTH_GATTC_OK;

    BT_GATT_ENTER_FUNCTION();

    i4_ret = c_timer_start(h_timer,
                           _RSSI_TIMER_DELAY,
                           X_TIMER_FLAG_ONCE,
                           _timer_cb_fct,
                           NULL);
    _CHECK_FAIL_RETURN(i4_ret);

    return i4_ret;
}

/*
static INT32 _rssi_meter_timer_stop(VOID)
{
    INT32 i4_ret = BLUETOOTH_GATTC_OK;

    i4_ret = c_timer_stop(h_timer);
    _CHECK_FAIL_RETURN(i4_ret);

    return i4_ret;
}
*/

static VOID _dump_rssi_meter_info(VOID)
{
    BT_GATT_ENTER_FUNCTION();
    
    DBG_INFO(("<BT_GATT> Dump rssi meter:\n"
                "\tStatus:%s\n"
                "\tRSSI:%d\n"
                "\tFrom:%s\n"
                "\tThreashold from %d to %d\n"
                "\tConsecutive:%d\n"
                "\tCount down:%d\n"
                "\tPin count:%d\n"
                "\tBest RSSI:%d\n"
                "\tWorst RSSI:%d\n"
                "\tAverage RSSI:%d\n"
                "\tPin per min:%d\n\n",
                            t_g_rssi_meter.s_status,
                            t_g_rssi_meter.i4_rssi,
                            t_g_rssi_meter.s_name,
                            t_g_rssi_meter.i4_min_rssi_threshold,
                            t_g_rssi_meter.i4_max_rssi_threshold,
                            t_g_rssi_meter.i4_consecutive,
                            t_g_rssi_meter.i4_contdown,
                            t_g_rssi_meter.i4_pin_count,
                            t_g_rssi_meter.i4_best_rssi,
                            t_g_rssi_meter.i4_worst_rssi,
                            t_g_rssi_meter.i4_average_rssi,
                            t_g_rssi_meter.i4_pings_per_min));
}

static INT32 _rssi_meter_refresh(T_RSSI_METER *pt_rssi_meter)
{
    UINT16          ui2_i = 0;
    INT32           i4_ret = 0;
    UTF16_T         w2s_text[128] = {0};
    UTF16_T         w2s_tmp[64] = {0};
    CHAR            s_tmp[64] = {0};
    WGL_LB_COLOR_ELEM_SET_T t_color_elem;
    GL_COLOR_T              t_rssi_text_color;

    BT_GATT_ENTER_FUNCTION();
    
    if (NULL == pt_rssi_meter)
    {
        DBG_LOG_PRINT(("<BT_GATT>Line %d: rssi meter ARG Invalid.\n", __LINE__));
        return BLUETOOTH_GATTC_FAILED;
    }

    c_memcpy(&t_g_rssi_meter, pt_rssi_meter, sizeof(T_RSSI_METER));

    _dump_rssi_meter_info();

    /* Update UI */
    /* Status */
    ui2_i = 1;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));

    if (c_strstr(t_g_rssi_meter.s_status, "RED") != NULL)
    {
        ui1_color = _RSSI_TEXT_COLOR_RED;
    }
    else if (c_strstr(t_g_rssi_meter.s_status, "GREEN") != NULL)
    {
        ui1_color = _RSSI_TEXT_COLOR_GREEN;
    }
    else if (c_strstr(t_g_rssi_meter.s_status, "YELLOW") != NULL)
    {
        ui1_color = _RSSI_TEXT_COLOR_YELLOW;
    }
    else
    {
        ui1_color = _RSSI_TEXT_COLOR_WHITE;
    }
    
    c_uc_ps_to_w2s(t_g_rssi_meter.s_status, w2s_tmp, 64-1);
    
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* RSSI */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
    
    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_rssi);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    c_uc_w2s_strcat(w2s_text, L" dBm");
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* From(Name) */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    
    c_uc_ps_to_w2s(t_g_rssi_meter.s_name, w2s_tmp, 64-1);
    
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* RSSI Threshold */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
        
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);

    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_min_rssi_threshold);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);

    c_uc_w2s_strcat(w2s_text, L" to ");

    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_max_rssi_threshold);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);

    c_uc_w2s_strcat(w2s_text, L" dBm");
    
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* best RSSI */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
        
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);

    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_best_rssi);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    c_uc_w2s_strcat(w2s_text, L" dBm");
    
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* worst RSSI */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
        
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);

    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_worst_rssi);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    c_uc_w2s_strcat(w2s_text, L" dBm");
    
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* average RSSI */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
        
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);

    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_average_rssi);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    c_uc_w2s_strcat(w2s_text, L" dBm");
    
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* Pings */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
        
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);

    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_pin_count);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);

    c_uc_w2s_strcat(w2s_text, L", ");

    /* Pings per minute */
    ui2_i++;
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
    
    c_uc_w2s_strncat(w2s_text, aw2s_rssi_titles[ui2_i], 128-1);
    
    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_pings_per_min);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strncat(w2s_text, w2s_tmp, 128-1);
    
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i-1), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* count down */
    ui2_i++;
    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_memset(w2s_tmp, 0, sizeof(w2s_tmp));
    c_memset(s_tmp, 0, sizeof(s_tmp));
        
    c_uc_w2s_strncpy(w2s_text, aw2s_rssi_titles[ui2_i], 64-1);

    snprintf(s_tmp, 64-1, "%d", t_g_rssi_meter.i4_contdown);
    c_uc_ps_to_w2s(s_tmp, w2s_tmp, 64-1);
    c_uc_w2s_strcat(w2s_text, w2s_tmp);
    
    w2s_text[128-1] = 0x00;
    
    i4_ret = c_wgl_do_cmd(h_rssi_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2((ui2_i-1), 0),
                            WGL_PACK(w2s_text));
    
    _CHECK_FAIL_RETURN(i4_ret);

    /* Set text color as status*/
    if (_RSSI_TEXT_COLOR_GREEN == ui1_color)
    {
        c_memcpy(&t_rssi_text_color, &t_g_rssi_color_green, sizeof(GL_COLOR_T));
    }
    else if (_RSSI_TEXT_COLOR_RED == ui1_color)
    {
        c_memcpy(&t_rssi_text_color, &t_g_rssi_color_red, sizeof(GL_COLOR_T));
    }
    else if (_RSSI_TEXT_COLOR_YELLOW == ui1_color)
    {
        c_memcpy(&t_rssi_text_color, &t_g_rssi_color_yellow, sizeof(GL_COLOR_T));
    }
    else
    {
        c_memcpy(&t_rssi_text_color, &t_g_rssi_color_white, sizeof(GL_COLOR_T));
    }
    
    t_color_elem.t_normal            = t_rssi_text_color;
    t_color_elem.t_disable           = t_rssi_text_color;
    t_color_elem.t_highlight         = t_rssi_text_color;
    t_color_elem.t_highlight_unfocus = t_rssi_text_color;
    t_color_elem.t_pushed            = t_rssi_text_color;
    t_color_elem.t_selected          = t_rssi_text_color;
    t_color_elem.t_selected_disable  = t_rssi_text_color;
    c_wgl_do_cmd(h_rssi_list,
                 WGL_CMD_LB_SET_COL_COLOR,
                 WGL_PACK_2(0,WGL_CLR_TEXT),
                 WGL_PACK(&t_color_elem));

    c_wgl_do_cmd(h_rssi_list,
                 WGL_CMD_LB_SET_COL_COLOR,
                 WGL_PACK_2(1,WGL_CLR_TEXT),
                 WGL_PACK(&t_color_elem));

    return BLUETOOTH_GATTC_OK;
}

INT32 a_bluetooth_gattc_reset_rssi_view_data(VOID)
{
    i4_g_total_rssi = 0;
    ui4_g_start_time = 0;

    c_memset(&t_g_rssi_meter, 0, sizeof(T_RSSI_METER));
    t_g_rssi_meter.i4_best_rssi = -10000;
    t_g_rssi_meter.i4_worst_rssi = 100;

    return BLUETOOTH_GATTC_OK;
}

INT32 a_bluetooth_gattc_rssimeter_view_init(VOID)
{
    INT32   i4_ret = BLUETOOTH_GATTC_OK;

    BT_GATT_ENTER_FUNCTION();

    do {
        /* Create Timer */
        i4_ret = c_timer_create(&h_timer);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<BT_GATT> Can't create timer\r\n"));
            i4_ret = BLUETOOTH_GATTC_FAILED;
            break;
        }

        /* Widget library init */
        i4_ret = c_wgl_register(_wgl_callback);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR(("<BT_GATT>c_wgl_register fail\r\n"));
            i4_ret = BLUETOOTH_GATTC_FAILED;
            break;
        }

        i4_ret = _init_canvas();
        _CHECK_FAIL_RETURN(i4_ret);

        i4_ret = _init_frm_root();
        _CHECK_FAIL_RETURN(i4_ret);

        i4_ret = _init_frm_main();
        _CHECK_FAIL_RETURN(i4_ret);

        i4_ret = _list_create();
        _CHECK_FAIL_RETURN(i4_ret);
        
    }while (0);

    b_inited = TRUE;
    return i4_ret;
}

INT32 a_bluetooth_gattc_rssi_meter_info_refresh(T_RSSI_NOTIFY_MSG *pt_rssi_nfy_msg)
{
    INT32           i4_ret = BLUETOOTH_GATTC_OK;
    UINT32          ui4_time_stamp = 0;
    UINT32          ui4_dur = 0;
    T_RSSI_METER    t_rssi_meter;
    E_RSSI_METER_STATUS e_status;
    INT32           i4_rssi;

    BT_GATT_ENTER_FUNCTION();

    if (NULL == pt_rssi_nfy_msg)
    {
        DBG_LOG_PRINT(("<BT_GATT> Unknowned rssi meter message.\n"));
        return i4_ret;
    }

    if (!b_inited)
    {
        c_memset(&t_g_rssi_meter, 0, sizeof(t_g_rssi_meter));
        a_bluetooth_gattc_reset_rssi_view_data();
    }

    e_status = pt_rssi_nfy_msg->e_status;
    i4_rssi = pt_rssi_nfy_msg->i4_rssi;
    

    c_memcpy(&t_rssi_meter, &t_g_rssi_meter, sizeof(T_RSSI_METER));

    ui4_time_stamp = c_os_get_sys_tick()*c_os_get_sys_tick_period();
    if (0 == ui4_g_start_time)
    {
        ui4_g_start_time = ui4_time_stamp;
    }

    /* STATUS */
    if (e_status >= E_RSSI_WHITE && e_status < E_RSSI_END)
    {
        c_strncpy(t_rssi_meter.s_status, ps_status_string_map[e_status], GATT_RSSI_STATUS_LEN);
    }
    else
    {
        DBG_LOG_PRINT(("<BT_GATT> Unknowned rssi meter status(%d)\n", e_status));
    }

    /* RSSI */
    t_rssi_meter.i4_rssi = i4_rssi;

    /* BEST RSSI */
    if (i4_rssi > t_rssi_meter.i4_best_rssi)
    {
        t_rssi_meter.i4_best_rssi = i4_rssi;
    }

    /* WORST RSSI */
    if (i4_rssi < t_rssi_meter.i4_worst_rssi)
    {
        t_rssi_meter.i4_worst_rssi = i4_rssi;
    }

    /* PING COUNT */
    t_rssi_meter.i4_pin_count++;

    /* PING COUNT PER MINUTE */
    if (t_rssi_meter.i4_pin_count >= 2 && ui4_g_start_time > 0)
    {
        ui4_dur = (ui4_time_stamp - ui4_g_start_time) > 0 ? (ui4_time_stamp - ui4_g_start_time) : 0;
        
        if (ui4_dur > 0 
            && t_rssi_meter.i4_pin_count > 0
            && (ui4_dur/t_rssi_meter.i4_pin_count) > 0)
        {
            t_rssi_meter.i4_pings_per_min = _ONE_MINUTE_IN_MS/(ui4_dur/t_rssi_meter.i4_pin_count);
        }
        else
        {
            DBG_LOG_PRINT(("<BT_GATT> Invalid time info.\n"));
        }
    }

    /* AVERAGE RSSI */
    i4_g_total_rssi += i4_rssi;
    t_rssi_meter.i4_average_rssi = i4_g_total_rssi/t_rssi_meter.i4_pin_count;

    /* MIN/MAX_RSSI_THRESHOLD */
    t_rssi_meter.i4_min_rssi_threshold = pt_rssi_nfy_msg->i4_min_rssi_threshold;
    t_rssi_meter.i4_max_rssi_threshold = pt_rssi_nfy_msg->i4_max_rssi_threshold;

    /* Name */
    c_strncpy(t_rssi_meter.s_name, pt_rssi_nfy_msg->s_name, GATT_RSSI_NAME_LEN);

    /* CONCURTIVE */
    t_rssi_meter.i4_consecutive = pt_rssi_nfy_msg->i4_consecutive;

    /* COUNTDOWN */
    t_rssi_meter.i4_contdown = pt_rssi_nfy_msg->i4_countdown;

    return a_bluetooth_gattc_rssi_meter_show(&t_rssi_meter);
    
}

INT32 a_bluetooth_gattc_rssi_meter_show(T_RSSI_METER *pt_rssi_meter)
{
    BT_GATT_ENTER_FUNCTION();
    
    INT32 i4_ret = BLUETOOTH_GATTC_OK;

    if (NULL == pt_rssi_meter)
    {
        DBG_LOG_PRINT(("<BT_GATT>Line %d: rssi meter ARG Invalid.\n", __LINE__));
        return BLUETOOTH_GATTC_FAILED;
    }

    if (!b_inited)
    {
        i4_ret = a_bluetooth_gattc_rssimeter_view_init();

        if (!b_inited || i4_ret != BLUETOOTH_GATTC_OK)
        {
            DBG_LOG_PRINT(("<BT_GATT> rssi meter not inited.\n"));
            return BLUETOOTH_GATTC_OK;
        }
    }

    i4_ret = _rssi_meter_refresh(pt_rssi_meter);
    _CHECK_FAIL_RETURN(i4_ret);

    if (!b_show)
    {
        i4_ret = c_wgl_set_visibility(h_frm_root,WGL_SW_RECURSIVE);
        _CHECK_FAIL_RETURN(i4_ret);
    }

    b_show = TRUE;

    i4_ret = c_wgl_float(h_rssi_list, TRUE, FALSE);
    _CHECK_FAIL_RETURN(i4_ret);
    
    i4_ret = c_wgl_repaint(h_rssi_list, NULL, TRUE);
    _CHECK_FAIL_RETURN(i4_ret);

    _rssi_meter_timer_start();
    
    return BLUETOOTH_GATTC_OK;
}

INT32 a_bluetooth_gattc_rssi_meter_hide(VOID)
{
    BT_GATT_ENTER_FUNCTION();
extern VOID bluetooth_gatt_reset_rssi_meter(VOID);

    INT32 i4_ret = BLUETOOTH_GATTC_OK;

    if (!b_show) return BLUETOOTH_GATTC_OK;

    b_show = FALSE;

    a_bluetooth_gattc_reset_rssi_view_data();
    bluetooth_gatt_reset_rssi_meter();

    ui4_g_start_time = 0;
    
    c_wgl_set_visibility(h_frm_root,WGL_SW_HIDE_RECURSIVE);
    _CHECK_FAIL_RETURN(i4_ret);

    i4_ret = c_wgl_repaint(h_frm_root, NULL, TRUE);
    _CHECK_FAIL_RETURN(i4_ret);
    
    
    return BLUETOOTH_GATTC_OK;
}

INT32 a_bluetooth_gattc_is_rssi_meter_show(VOID)
{
    return b_show;
}
#endif

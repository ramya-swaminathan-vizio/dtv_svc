/*-----------------------------------------------------------------------------
* $RCSfile: Foxconn_fac_menu_item_widget.c,v $
* $Revision: #3 $
* $Date: 2017/08/30 $
* $Author:  $
* $CCRevision: $
* $SWAuthor: $
* $MD5HEX: $
*
* Description:
*
*---------------------------------------------------------------------------*/
#include "c_wgl.h"
#include "c_dbg.h"
#include "u_common.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_gl.h"
#include "u_wgl_obj_type.h"
#include "u_btn_map.h"

#include "app_util/a_ui.h"
#include "res/nav/nav_view.h"
#include "nav/nav_common.h"

#include "Foxconn_factory/a_Foxconn_factory.h"
#include "Foxconn_factory/Foxconn_fac_img.h"
#include "Foxconn_fac_menu_item_widget.h"


GL_COLOR_T t_g_nav_fac_menu_txt  = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T t_g_nav_fac_menu_txt_disable  = { 255, { 128 }, { 128 }, { 128 }};

static WGL_INSET_T t_item_inset_border = { 20, 0, 0, 0};
static GL_RECT_T   t_rect_item_border_title = {65, 0, 120, 30};	//{65, 0, 120, 44};

#define Foxconn_fac_menu_FRAME_HEIGHT 1080
#define Foxconn_fac_menu_ITEM_LEFT            (0)
#define Foxconn_fac_menu_ITEM_WIDE            (568)
#define Foxconn_fac_menu_ITEM_HEIGHT          (30)//(44)


/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_text_widget_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_frame_widget_create(HANDLE_T h_parent,
                                                  HANDLE_T* ph_child,
                                                  INT32 i4_frame_x_offset,
                                                  INT32 i4_frame_y_offset)
{
    INT32 i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T              t_img_info;

    /* Create frame for color tuner menu */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    i4_frame_x_offset,
                    i4_frame_y_offset,
                    Foxconn_fac_menu_ITEM_WIDE,
                    Foxconn_fac_menu_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_parent,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    0, //(VOID*)ui4_style,
                    NULL,
                    ph_child);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    /* Set image backgrond */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_app_fac_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_app_fac_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_app_fac_bk_img;
    i4_ret = c_wgl_do_cmd(
                    *ph_child,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_frame_title_widget_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_frame_title_widget_create(HANDLE_T h_parent,
                                                  HANDLE_T* ph_child,
                                                  UTF16_T* pw2s_title_string)
{
    INT32 i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;

    //ui4_style = WGL_STL_GL_NO_IMG_UI;

    SET_RECT_BY_SIZE(&t_rect,
                    0,
                    0,
                    Foxconn_fac_menu_ITEM_WIDE,
                    Foxconn_fac_menu_ITEM_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 0, //(VOID*)ui4_style,
                                 NULL,
                                 ph_child);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_child,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_nav_fac_menu_txt;
    i4_ret = c_wgl_do_cmd(*ph_child,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    /* Set image backgrond */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE; //h_g_app_fac_bar_img;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE; //h_g_app_fac_bar_img;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE; //h_g_app_fac_bar_img;
    i4_ret = c_wgl_do_cmd(
                    *ph_child,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_child,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_TOP), //WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }


    /* Set title for setup menu*/
    //pw2s_string = L"Color Tuner";
    i4_ret = c_wgl_do_cmd(
                    *ph_child,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(pw2s_title_string),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_title_string)));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_text_widget_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_text_widget_create(HANDLE_T h_parent, 
                                               UTF16_T* pw2s_string, 
                                               INT32 i4_index,
                                               wgl_widget_proc_fct pf_wdgt_proc,
                                               HANDLE_T* ph_widget)
{
    INT32 i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;

    SET_RECT_BY_SIZE(&t_rect,
                    0,
                    Foxconn_fac_menu_ITEM_HEIGHT * i4_index,
                    Foxconn_fac_menu_ITEM_WIDE,
                    Foxconn_fac_menu_ITEM_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 0, //(VOID*)ui4_style,
                                 NULL,
                                 ph_widget);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_nav_fac_menu_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    /* Set image backgrond */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE; //h_g_app_fac_bar_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_app_fac_bar_Highlight_img; //NULL_HANDLE; //h_g_app_fac_bar_img;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE; //h_g_app_fac_bar_img;
    i4_ret = c_wgl_do_cmd(
                    *ph_widget,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    /* Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET, //WGL_CMD_GL_SET_INSET,
                          &t_item_inset_border,
                          NULL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set title for setup menu*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(pw2s_string),
                            WGL_PACK(c_uc_w2s_strlen(pw2s_string)));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_range_widget_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_range_widget_create( HANDLE_T    h_parent,
                                                    UTF16_T*    pw2s_string,
                                                    INT32       i4_index,
                                                    INT32       i4_min,
                                                    INT32       i4_max,
                                                    wgl_widget_proc_fct pf_wdgt_proc,
                                                    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    UINT32          ui4_style;
    WGL_INSET_T     t_inset;
    GL_RECT_T       t_rect;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_PG_IDR_LOC_T      t_pg_idr_loc;
    WGL_INSET_T           t_range_inset_border;

    ui4_style = WGL_STL_GL_NO_BK | WGL_STL_GL_BDR_FILL_CNT_BK;


    /* Create progress bar */
    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     Foxconn_fac_menu_ITEM_HEIGHT * i4_index,
                     Foxconn_fac_menu_ITEM_WIDE,
                     Foxconn_fac_menu_ITEM_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return NAVR_FAIL;
    }

    t_range_inset_border.i4_left = 0;
    t_range_inset_border.i4_right = 0;
    t_range_inset_border.i4_top = 0;
    t_range_inset_border.i4_bottom = 0;

    /* Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_range_inset_border,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 300;
    t_inset.i4_right    = 120;
    t_inset.i4_top      = 15; //20;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_BAR_INSET,
                          &t_inset,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Border Title Info */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_item_border_title;
    t_title_info.t_rc_ref.i4_right = 140;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_nav_fac_menu_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    Foxconn_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_app_fac_bar_Highlight_img;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Display mode */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_DISPLAY_MODE,
                          WGL_PACK(0),
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Range */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK(i4_min),
                           WGL_PACK(i4_max));
    Foxconn_LOG_ON_FAIL(i4_ret);

    #if 0
    /* Block */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_BLK_PT_SIZE,
                           //WGL_PACK(MENU_ITEM_RNG_BLK_PT_SIZE_W),
                           //WGL_PACK(MENU_ITEM_RNG_BLK_PT_SIZE_H));
                           WGL_PACK(15),
                           WGL_PACK(13));
    Foxconn_LOG_ON_FAIL(i4_ret);
    #endif

    /* Min Size */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_BAR_MIN_SIZE,
                           WGL_PACK(0),
                           NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Indicator */
    SET_RECT_BY_SIZE(&t_pg_idr_loc.t_loc_rect,
                     500, //236,
                     0,
                     10,
                     Foxconn_fac_menu_ITEM_HEIGHT);
    t_pg_idr_loc.ui1_align = WGL_AS_RIGHT_CENTER;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_IDR_LOC,
                           WGL_PACK(WGL_PG_CNT_ILT_POS),
                           WGL_PACK(&t_pg_idr_loc));
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Levels */
    t_pg_levels.a_boundary[0] = i4_max;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* pb progress */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_nav_fac_menu_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    Foxconn_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_app_fac_pb_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_app_fac_pb_bk_img;
    t_img_info.u_img_data.t_standard.t_disable = h_g_app_fac_pb_bk_img;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_BODY),
                          WGL_PACK(&t_img_info ));
    Foxconn_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_app_fac_pb_bar_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_app_fac_pb_bar_img;
    t_img_info.u_img_data.t_standard.t_disable = h_g_app_fac_pb_bar_img;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    Foxconn_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(pw2s_string),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_string)));
    Foxconn_LOG_ON_FAIL(i4_ret);

    
    #if 0 //for test
    //default setting : 0
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK(0),
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);
    #endif


    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_list_widget_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_list_widget_create(
    HANDLE_T    h_parent,
    UTF16_T*    pw2s_string,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[3];
    WGL_LB_ITEM_T               at_items[3];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_right;
    UINT16                      ui2_i;
    WGL_IMG_INFO_T              t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /*=======================================*
     | Title                |   | option |   |      ---   normal
     | Title                | < | option | > |      ---   highlight
     *=======================================*/

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width        = 20; //MENU_ITEM_V_LB_ARROW_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = 110; //(MENU_ITEM_V_VALUE_W - MENU_ITEM_V_LB_ARROW_W*2 - MENU_ITEM_V_LB_INSET_L);

    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[2].ui2_width        = 20; //MENU_ITEM_V_LB_ARROW_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = Foxconn_fac_menu_ITEM_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     Foxconn_fac_menu_ITEM_HEIGHT * i4_index,
                     Foxconn_fac_menu_ITEM_WIDE,
                     Foxconn_fac_menu_ITEM_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return NAVR_FAIL;
    }

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 400; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* element inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* column inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK(ui2_i),
                              WGL_PACK(&t_inset));
        Foxconn_LOG_ON_FAIL(i4_ret);
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    Foxconn_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(1),
                           WGL_PACK(&t_fnt_info));
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_nav_fac_menu_txt;
    t_lb_color.t_disable = t_g_nav_fac_menu_txt_disable;
    t_lb_color.t_highlight = t_g_nav_fac_menu_txt;
    t_lb_color.t_highlight_unfocus = t_g_nav_fac_menu_txt;
    t_lb_color.t_pushed = t_g_nav_fac_menu_txt;
    t_lb_color.t_selected = t_g_nav_fac_menu_txt;
    t_lb_color.t_selected_disable = t_g_nav_fac_menu_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    Foxconn_LOG_ON_FAIL(i4_ret);

    #if 0
    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    Foxconn_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        Foxconn_LOG_ON_FAIL(i4_ret);
    }
    #endif

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_nav_fac_menu_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_left.h_highlight          = h_g_app_fac_sidebar_highlight_arrow_left;
    t_img_suit_left.h_selected_highlight = h_g_app_fac_sidebar_highlight_arrow_left;

    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_right.h_highlight          = h_g_app_fac_sidebar_highlight_arrow_right;
    t_img_suit_right.h_selected_highlight = h_g_app_fac_sidebar_highlight_arrow_right;

    for (ui2_i=0; ui2_i<ui2_max_elem_num; ui2_i++)
    {
        at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[0].data.pt_img_suit = &t_img_suit_left;

        at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text   = L""; //w2s_g_empty;

        at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[2].data.pt_img_suit = &t_img_suit_right;

        i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        Foxconn_LOG_ON_FAIL(i4_ret);
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_fac_menu_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_nav_fac_menu_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    Foxconn_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_app_fac_bar_Highlight_img;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    Foxconn_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_item_border_title; //t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(pw2s_string),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_string)));
    Foxconn_LOG_ON_FAIL(i4_ret);


    #if 0  //For test
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0,1),
                          WGL_PACK(L"test123"));
    #endif
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_list_set_text
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_list_set_text(
        HANDLE_T    h_widget,
        UTF16_T*    w2s_str)
{
    INT32   i4_ret = 0;
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0,1),
                          WGL_PACK(w2s_str));
    Foxconn_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name:Foxconn_fac_menu_range_get_val
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_range_get_val(HANDLE_T h_widget, INT32* pi4_val)
{
    INT32 i4_ret = 0;
    INT32 i4_val;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_PG_GET_POS,
                          WGL_PACK(&i4_val),
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    *pi4_val = i4_val;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_menu_range_set_val
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 Foxconn_fac_menu_range_set_val(HANDLE_T h_widget, INT32 i4_val)
{
    INT32 i4_ret = 0;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK(i4_val),
                          NULL);
    Foxconn_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}



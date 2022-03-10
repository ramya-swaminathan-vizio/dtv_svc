#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "burning_mode_v2.h"

#include "nav/banner2/a_banner.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/navigator.h"
#include "nav/a_navigator.h"
#include "c_os.h"
#include "c_svctx.h"
#include "nav/input_src/a_input_src.h"
#ifdef SYS_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/nav_variant.h"
#include "mmp/a_mmp.h"
#include "am/a_am.h"

#include "app_util/config/_acfg.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "c_svctx.h"
#include "c_scc.h"

////////////////////////////////////////////////////////////////////////////////////////
#define  BURNING_MODE_PATTERN_INVOKE_DUR            (300)

#define  BURNING_MODE_BLOCK_SIZE                         (10 * 1000 * sizeof(UINT8))
#define BTN_BURNING_MODE                     BTN_FUNCTION_2

static BURNING_MODE_T    t_g_burning_mode_v2;

static  HANDLE_T  h_patter_loop_timer = NULL_HANDLE;
static  BURNING_MODE_IMG_DRC_DATA_TMP_T  t_img_drc = {0};

static  UINT8   ui1_timer_count = 0;
static  UINT8   ui1_pattern_count = 0;


extern NAV_MODEL_T  t_g_navigator;

BURNING_MODE_TEST_PATTERN_PARAM_T  pattern_param_t;
static BOOL b_burning_mode_active = FALSE;

////////////////////////////////////////////////////////////////////////////////////////
static VOID _nav_burning_mode_pattern_show_pattern(
    BOOL    isFile,
    CHAR*   ps_file_name,
    UINT8*  inputData,
    UINT32  dataSize,
    BOOL    isShowOnVdp,
    BOOL    b_phot_4k);

static INT32 _nav_burning_mode_pattern_exit_pattern(VOID);
static INT32 _nav_burning_mode_pattern_read_pic(CHAR *path, UINT8 **data, UINT32 *dataSize);
static VOID  _nav_burning_mode_pattern_free_pic(UINT8 *data);
static INT32 _nav_burning_mode_V2_pattern_timer_start(VOID);
static INT32 _nav_burning_mode_V2_pattern_timer_stop(VOID);

extern INT32 burning_mode_ext_rc_control_view_update(
                    BURNING_MODE_VIEW_T*         pt_view,
                    UINT16 ui2_idex
                    );
static INT32 _nav_burning_mode_V2_hide(VOID);
////////////////////////////////////////////////////////////////////////////////////////
static VOID _nav_burning_mode_show_next_pattern_timer_cb_fct (HANDLE_T pt_tm_handle, VOID* pv_tag)
{
    //DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() ui1_pattern_count = %d.\n", __LINE__, __FUNCTION__, ui1_pattern_count));

    a_nav_burning_mode_V2_pattern_exit();

    if(ui1_pattern_count == BURNING_MODE_PATTERN_HSTRI){
        a_nav_burning_mode_V2_pattern_show(BURNING_MODE_PATTERN_HSTRI);
        ui1_pattern_count++;
    }
    else if(ui1_pattern_count == BURNING_MODE_PATTERN_VSTRI){
        a_nav_burning_mode_V2_pattern_show(BURNING_MODE_PATTERN_VSTRI);
        ui1_pattern_count++;
    }
    else if(ui1_pattern_count == BURNING_MODE_PATTERN_WHITE){
        a_nav_burning_mode_V2_pattern_show(BURNING_MODE_PATTERN_WHITE);
        ui1_pattern_count++;
    }
    else{
        a_nav_burning_mode_V2_pattern_show(BURNING_MODE_PATTERN_BLACK);
        ui1_pattern_count = 0;
    }

}

static VOID _nav_burning_mode_pattern_show_pattern_ex(VOID* param0, VOID* param1, VOID *param2)
{
    BURNING_MODE_V2_PATTERN_T type = (BURNING_MODE_V2_PATTERN_T)param0;
    const CHAR* p_file_path = NULL;
    CHAR*  p_file_name = NULL;
    size_t  str_size = 0;

    {
        CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
        SCC_VID_OVER_SCAN_CLIPPER_T     t_overscan = {0,0,0,0};
        SVCTX_ATOMIC_CMD_T          at_cmd[3];
        HANDLE_T    h_svctx         = NULL_HANDLE;
        SM_COMMAND_T    at_sm_cmds[4];


        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));

        acfg_get_svctx(s_disp_name,&h_svctx);

        at_cmd[0].t_type = SVCTX_COMMON_SET_ATOMIC_OVERSCAN;
        at_cmd[0].pv_data = &t_overscan;
        at_cmd[1].t_type = SVCTX_COMMON_SET_ATOMIC_SCRN_MODE;
        at_cmd[1].pv_data = (VOID*)SCC_VID_SCREEN_MODE_NORMAL;
        at_cmd[2].t_type = SVCTX_COMMON_SET_ATOMIC_CMD_END;
        at_cmd[2].pv_data = NULL;
        c_svctx_set(h_svctx, SVCTX_COMMON_SET_ATOMIC_CMD_GRP, at_cmd, 0);


        at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
        at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text     = s_disp_name;
        at_sm_cmds[2].e_code        = SCC_CMD_CODE_VIDEO_OVERSCAN_CLIPPER;
        at_sm_cmds[2].u.pv_data     = &t_overscan;
        at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
        at_sm_cmds[3].u.ui4_data    = 0;
        c_scc_comp_grp_set(at_sm_cmds);
    }


    switch (type)
    {
        case BURNING_MODE_PATTERN_HSTRI:
            #ifndef APP_SUPPORT_4K2K
            p_file_path = "/basic/pattern/hstri_1080.bmp";
            pattern_param_t.b_phot_4k = FALSE;
            #else
            p_file_path = "/basic/pattern/hstri_2160.bmp";
            pattern_param_t.b_phot_4k = TRUE;
            #endif
            break;

        case BURNING_MODE_PATTERN_VSTRI:
            #ifndef APP_SUPPORT_4K2K
            p_file_path = "/basic/pattern/vstri_1080.bmp";
            pattern_param_t.b_phot_4k = FALSE;
            #else
            p_file_path = "/basic/pattern/vstri_2160.bmp";
            pattern_param_t.b_phot_4k = TRUE;
            #endif
            break;

        case BURNING_MODE_PATTERN_BLACK:
            p_file_path = "/basic/pattern/black.bmp";
            pattern_param_t.b_phot_4k = FALSE;
            break;
        case BURNING_MODE_PATTERN_WHITE:
            p_file_path = "/basic/pattern/white.bmp";
            pattern_param_t.b_phot_4k = FALSE;
            break;
        default:
            break;
    }

    if (NULL == p_file_path)
    {
        DBG_INFO(("[BURNING_MODE_V2] LINE %d @ %s() cannot get file path.\n", __LINE__, __FUNCTION__));
        return;
    }

    str_size = c_strlen(p_file_path);
    p_file_name = (CHAR *)c_mem_alloc(str_size+1);
    if (NULL == p_file_name)
    {
        DBG_INFO(("[BURNING_MODE_V2] LINE %d @ %s() c_mem_alloc() failed\n", __LINE__, __FUNCTION__));
        return;
    }

    c_memset(p_file_name, 0, str_size+1);
    c_strncpy(p_file_name, p_file_path, str_size);
    pattern_param_t.ps_file_name = p_file_name;

    DBG_INFO(("[BURNING_MODE_V2] {%s,%d} type:%d, file_name:%s.\n", __FUNCTION__, __LINE__,type,p_file_name));
    a_nav_burning_mode_pattern_show_pattern(NULL,NULL,NULL);

    _nav_burning_mode_V2_pattern_timer_start();

}
////////////////////////////////////////////////////////////////////////////////////////
VOID a_nav_burning_mode_pattern_show_pattern(VOID* param0, VOID* param1, VOID *param2)
{
    INT32           i4_ret;
    NAV_MODEL_T*    pt_this = &t_g_navigator;
    TV_WIN_ID_T  e_focus_id = {0};
    ISL_REC_T  t_isl_rec = {0};


    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);


    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
    #if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
        a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
        a_c4tv_apron_sync_exit_cast();
    #endif
    }

    do {
        BOOL  b_is_signal_loss = FALSE;
        NAV_TV_WIN_T*   pt_tv_win = &pt_this->t_tv_wins[TV_WIN_ID_MAIN];
        c_svctx_is_signal_loss (
                pt_tv_win->h_svctx,
                &b_is_signal_loss
                );
        if (!b_is_signal_loss && (nav_sync_stop_service(TV_WIN_ID_MAIN) != NAVR_OK))
        {
            DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() nav_stop_service() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
            return;
        }
    } while(0);


    i4_ret = _nav_burning_mode_pattern_read_pic(
                    pattern_param_t.ps_file_name,
                    &pattern_param_t.inputData,
                    &pattern_param_t.dataSize);
    if(NAVR_OK != i4_ret)
    {
        DBG_INFO(("[BURNING_MODE_V2] {%s,%d} _nav_test_pattern_read_pic fail.\n", __FUNCTION__, __LINE__));
        return;
    }

    pattern_param_t.isShowOnVdp  = TRUE;
    pattern_param_t.isFile       = FALSE;
    _nav_burning_mode_pattern_show_pattern(
                    pattern_param_t.isFile,
                    pattern_param_t.ps_file_name,
                    pattern_param_t.inputData,
                    pattern_param_t.dataSize,
                    pattern_param_t.isShowOnVdp,
                    pattern_param_t.b_phot_4k
        );
}

VOID a_nav_burning_mode_pattern_exit_pattern(VOID* param0, VOID* param1, VOID* param2)
{
    INT32  i4_ret;

    DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));

    i4_ret = _nav_burning_mode_pattern_exit_pattern();
    if (NAVR_OK != i4_ret)
    {
        DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() burning_mode_pattern_exit() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return;
    }

    if (param0 != NULL)
    {
        ((VOID (*)(BOOL))param0)(FALSE);
    }
}

VOID a_nav_burning_mode_V2_pattern_show(BURNING_MODE_V2_PATTERN_T type)
{
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;
    a_scrn_svr_set_enable(FALSE);
    //#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
    //a_banner_set_excl_comp_on(FALSE);
    //#endif

    if(pt_this->b_active == TRUE)
    {
        DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, toggle pattern not hide\n", __FUNCTION__, __LINE__));
        //_nav_burning_mode_V2_hide();
        nav_hide_component (NAV_COMP_ID_BURNING_MODE);
    }

    b_burning_mode_active = TRUE;
    nav_request_context_switch(_nav_burning_mode_pattern_show_pattern_ex,
                               (VOID*) type,
                               NULL,
                               NULL);

}
VOID a_nav_burning_mode_V2_pattern_exit(VOID)
{
    nav_request_context_switch(a_nav_burning_mode_pattern_exit_pattern,
                               NULL,
                               NULL,
                               NULL);
}

static INT32  _nav_burning_mode_pattern_read_pic(CHAR *path, UINT8 **data, UINT32 *dataSize)
{
    INT32   handle = -1;
    VOID*   p_data = NULL;
    SIZE_T  offset = 0;
    SIZE_T  ret = 0;

    handle = open(path, O_RDONLY);
    if (-1 == handle)
    {
        DBG_INFO(("[BURNING_MODE_V2] {%s,%d} open fail.\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    do {
        VOID*   p_tmp_data = NULL;

        p_tmp_data = realloc(p_data, BURNING_MODE_BLOCK_SIZE + offset);
        if (!p_tmp_data)
        {
            DBG_INFO(("[BURNING_MODE_V2] {%s,%d} realloc fail.\n", __FUNCTION__, __LINE__));
            goto ERR;
        }
        p_data = p_tmp_data;

        ret = read(handle, p_data + offset, BURNING_MODE_BLOCK_SIZE);
        if (ret == -1)
        {
            DBG_INFO(("[BURNING_MODE_V2] {%s,%d} read fail.\n", __FUNCTION__, __LINE__));
            goto ERR;
        }
        offset += ret;
    }while(0 != ret);

    *data = (UINT8 *)p_data;
    *dataSize = (UINT32)offset;

    close(handle);

    return NAVR_OK;
ERR:
    free(p_data);
    close(handle);

    return NAVR_FAIL;
}

static VOID  _nav_burning_mode_pattern_free_pic(UINT8 *data)
{
    c_mem_free(data);
}

static VOID _nav_burning_mode_pattern_show_pattern(
    BOOL    isFile,
    CHAR*   ps_file_name,
    UINT8*  inputData,
    UINT32  dataSize,
    BOOL    isShowOnVdp,
    BOOL    b_phot_4k)
{
    INT32                   i4_ret;
    GL_SURFACE_DESC_T       t_surf_descr = {0};
    GL_DISPLAY_OPT_T        t_dsp_opt = {0};
    UINT32                  ui4_screen_w = 0, ui4_screen_h = 0;
    BURNING_MODE_IMG_DRC_DISPLAY_RES_TMP_T*  pt_res = &t_img_drc.pt_res;
    HANDLE_T                h_img = NULL_HANDLE;
    IMG_TYPE_DATA_T         t_data = {0};
    UINT32                  ui4_info_len, ui4_src_w, ui4_src_h, ui4_dst_w, ui4_dst_h, ui4_dst_x, ui4_dst_y;
    GL_SIZE_T               t_resolution;
    UINT32                  ui4_ratio_w, ui4_ratio_h;
    UINT16                  ui2_plane_index = 0;
    GL_COLORMODE_T          e_cm = GL_COLORMODE_ARGB_D8888;

    DBG_INFO(("[BURNING_MODE_V2]{%s %d}.\r\n",__FUNCTION__, __LINE__));

    if (t_img_drc.b_init == TRUE)
    {
        DBG_INFO(("[BURNING_MODE_V2]{%s %d} pls exit before show pattern, return!\r\n",__FUNCTION__, __LINE__));
        return;
    }

    if (isFile && ps_file_name == NULL)
    {
        DBG_INFO(("[BURNING_MODE_V2]{%s %d} parameters err.\r\n",__FUNCTION__, __LINE__));
        return;
    }

    if (!isFile &&( inputData == NULL || dataSize == 0))
    {
        DBG_INFO(("[BURNING_MODE_V2]{%s %d} parameters err.\r\n",__FUNCTION__, __LINE__));
        return;
    }

    c_memset(&t_img_drc, 0, sizeof(BURNING_MODE_IMG_DRC_DATA_TMP_T));

    if (isShowOnVdp)
    {
        ui2_plane_index = 2;
        e_cm = GL_COLORMODE_YUV_422_RS;
    }

    i4_ret = c_gl_screen_open(SN_PRES_MAIN_DISPLAY, NULL, NULL, &t_img_drc.h_screen);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("[BURNING_MODE_V2{%s %d}]x_gl_screen_open(%s) failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, SN_PRES_MAIN_DISPLAY, i4_ret));
        return;
    }

    do
    {
        i4_ret = c_gl_screen_get_panel_size(t_img_drc.h_screen, &ui4_screen_w, &ui4_screen_h);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_screen_get_panel_size() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        DBG_INFO(("panel_size=(%d,%d).\n", ui4_screen_w, ui4_screen_h));

        i4_ret = c_gl_plane_open(t_img_drc.h_screen, ui2_plane_index, &t_img_drc.h_plane);
        if (GLR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_plane_open() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        i4_ret = c_gl_plane_link(t_img_drc.h_plane, t_img_drc.h_screen, TRUE);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_plane_link() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }



        i4_ret = c_gl_view_create(ui4_screen_w,
                                  ui4_screen_h,
                                  TRUE/*FALSE*/,
                                  &pt_res->h_view);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_view_create() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
            pt_res->h_view = NULL_HANDLE;
            break;
        }

        c_gl_plane_get_resource(t_img_drc.h_plane, NULL_HANDLE, ui4_screen_w,ui4_screen_h);

        t_surf_descr.e_clrmode  = e_cm;
        t_surf_descr.ui4_width  = ui4_screen_w;
        t_surf_descr.ui4_height = ui4_screen_h;

        if (isShowOnVdp)
        {
            i4_ret = c_gl_surface_create_from_vdp(&t_surf_descr, &pt_res->h_surf);
        }
        else
        {
            i4_ret = c_gl_surface_create(&t_surf_descr, &pt_res->h_surf);
        }

        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_surface_create_from_dfb() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));

            pt_res->h_surf = NULL_HANDLE;
            break;
        }

        /*viewport setting*/
        t_dsp_opt.e_flag            = GL_DISP_OPT_POSITION | GL_DISP_OPT_BLEND_OPTION | GL_DISP_OPT_ALPHA;
        t_dsp_opt.e_blend_option    = GL_BLEND_OPT_PIXEL;
        t_dsp_opt.ui1_alpha         = 255;
        t_dsp_opt.t_pos.i4_x        = 0;
        t_dsp_opt.t_pos.i4_y        = 0;

        /*create viewport*/
        i4_ret = c_gl_view_create_viewport(pt_res->h_view, pt_res->h_surf, &t_dsp_opt, &pt_res->ui4_viewport);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_view_create_viewport() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));

            pt_res->ui4_viewport = 0;

            break;
        }

        //DBG_INFO(("\n[BURNING_MODE_V2] %s t_dsp_opt.t_pos.i4_x: %d\n", __FUNCTION__, t_dsp_opt.t_pos.i4_x ));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s t_dsp_opt.t_pos.i4_y: %d\n", __FUNCTION__, t_dsp_opt.t_pos.i4_y ));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s t_dsp_opt.t_size.ui4_width: %d\n", __FUNCTION__, t_dsp_opt.t_size.ui4_width ));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s t_dsp_opt.t_size.ui4_height: %d\n", __FUNCTION__, t_dsp_opt.t_size.ui4_height ));

        pt_res->ui1_flag = ((UINT8) 0x01);

        if (isFile)
        {
            i4_ret = c_img_fopen(ps_file_name, IMG_RW_FILE_MODE, NULL, NULL, &h_img);
        }
        else
        {
            i4_ret = c_img_mopen(inputData, dataSize, "PNG", NULL, NULL, &h_img);
        }
        if (IMGR_OK != i4_ret)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_img_fopen() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
            break;
        }

        ui4_info_len = sizeof(GL_SIZE_T);
        i4_ret = c_img_get_info(h_img, IMG_INFO_PRIMARY_DIMENSION, NULL, &t_resolution, &ui4_info_len);
        if (i4_ret != IMGR_OK)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_img_get_info() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
            break;
        }

        ui4_src_w = t_resolution.ui4_width;
        ui4_src_h = t_resolution.ui4_height;

        if(ui4_src_w > ui4_screen_w||  ui4_src_h > ui4_screen_h)
        {
            ui4_ratio_w = ui4_src_w * 10000 / ui4_screen_w;
            ui4_ratio_h = ui4_src_h * 10000 / ui4_screen_h;
            if(ui4_ratio_w > ui4_ratio_h) /*keep width*/
            {
                ui4_dst_h = ui4_src_h * ui4_screen_w / ui4_src_w;
                ui4_dst_w = ui4_screen_w;
            }
            else /*keep height*/
            {
                ui4_dst_w = ui4_src_w * ui4_screen_h / ui4_src_h ;
                ui4_dst_h = ui4_screen_h;
            }
        }
        else /*photo is small than screen*/
        {
            ui4_dst_w = ui4_src_w;
            ui4_dst_h = ui4_src_h;
        }



        #ifdef MW_SUPPORT_4K2K
        c_gl_plane_flip_4k2k(t_img_drc.h_plane, pt_res->h_view, TRUE);
        c_gl_plane_set_4k2k_cropping(t_img_drc.h_plane,
                                     FALSE,
                                     0,
                                     0,
                                     0,
                                     0,
                                     b_phot_4k, //TRUE,
                                     b_phot_4k == TRUE ? FALSE:TRUE);
        c_gl_plane_enable(t_img_drc.h_plane, FALSE);
        c_thread_delay(10);
        ui4_dst_x = 0;
        ui4_dst_y = 0;
        #else
        ui4_dst_x = (ui4_screen_w - ui4_dst_w) >> 1;
        ui4_dst_y = (ui4_screen_h - ui4_dst_h) >> 1;
        #endif


        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_src_w: %d\n", __FUNCTION__, ui4_src_w));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_src_h: %d\n", __FUNCTION__, ui4_src_h));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_screen_w: %d\n", __FUNCTION__, ui4_screen_w));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_screen_h: %d\n", __FUNCTION__, ui4_screen_h));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_dst_x: %d\n", __FUNCTION__, ui4_dst_x));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_dst_y: %d\n", __FUNCTION__, ui4_dst_y));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_dst_w: %d\n", __FUNCTION__, ui4_dst_w));
        //DBG_INFO(("\n[BURNING_MODE_V2] %s ui4_dst_h: %d\n", __FUNCTION__, ui4_dst_h));


        t_data.ui4_data_flag = IMG_TYPE_DATA_TAG;
        t_data.t_animated.b_animated = FALSE;
        t_data.t_animated.ui4_frame_index = 0;
        t_data.b_load_more_frame = FALSE;
        i4_ret = c_img_sync_load(h_img,
                                INTRA_IMG_PRIMARY_IMG_TYPE,
                                &t_data,
                                IMG_ROTATE_CLOCKWS_0_OP_TYPE,
                                0, 0,
                                ui4_src_w,
                                ui4_src_h,
                                ui4_dst_x, ui4_dst_y,
                                ui4_dst_w, ui4_dst_h,
                                pt_res->h_surf);
        if (i4_ret != IMGR_OK)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_img_sync_load() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
            break;
        }

        #ifdef MW_SUPPORT_4K2K
        if (isShowOnVdp)
        {
            i4_ret = c_gl_plane_flip_4k2k(t_img_drc.h_plane, pt_res->h_view, TRUE);
        }
        else
        {
           i4_ret = c_gl_plane_flip(t_img_drc.h_plane, pt_res->h_view, TRUE);
        }
        #else
        i4_ret = c_gl_plane_flip(t_img_drc.h_plane, pt_res->h_view, TRUE);
        #endif
        if (i4_ret != IMGR_OK)
        {
            DBG_ERROR(("[BURNING_MODE_V2]{%s %d}x_gl_plane_flip() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
            break;
        }

        c_gl_plane_enable(t_img_drc.h_plane, TRUE);

        c_img_close(h_img);

        t_img_drc.b_init = TRUE;

        return;
    }while(0);

    if (h_img != NULL_HANDLE)
    {
        c_img_close(h_img);
    }

    if (pt_res->h_view != NULL_HANDLE)
    {
        c_gl_view_delete_viewport(pt_res->h_view, pt_res->ui4_viewport);
    }

    if (pt_res->h_surf != NULL_HANDLE)
    {
        c_gl_obj_free(pt_res->h_surf);
    }

    if (pt_res->h_view != NULL_HANDLE)
    {
        c_gl_obj_free(pt_res->h_view);
    }

    if (t_img_drc.h_plane != NULL_HANDLE)
    {
        c_gl_plane_link(t_img_drc.h_plane, NULL_HANDLE, TRUE);
        c_gl_obj_free(t_img_drc.h_plane);
    }

    if (t_img_drc.h_screen != NULL_HANDLE)
    {
        c_gl_obj_free(t_img_drc.h_screen);
    }

    return;
}

static INT32 _nav_burning_mode_pattern_exit_pattern(VOID)
{
    BURNING_MODE_IMG_DRC_DISPLAY_RES_TMP_T*  pt_res = &t_img_drc.pt_res;

    if (t_img_drc.b_init == FALSE)
    {
        DBG_INFO(("[BURNING_MODE_V2]{%s %d} has been exited, return!\r\n",__FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    c_gl_plane_flip(t_img_drc.h_plane, NULL_HANDLE, TRUE);

    c_gl_plane_release_resource(t_img_drc.h_plane, NULL_HANDLE);

    if (pt_res->h_view != NULL_HANDLE)
    {
        c_gl_view_delete_viewport(pt_res->h_view, pt_res->ui4_viewport);
    }

    if (pt_res->h_surf != NULL_HANDLE)
    {
        c_gl_obj_free(pt_res->h_surf);
    }

    if (pt_res->h_view != NULL_HANDLE)
    {
        c_gl_obj_free(pt_res->h_view);
    }

    if (t_img_drc.h_plane != NULL_HANDLE)
    {
        c_gl_plane_link(t_img_drc.h_plane, NULL_HANDLE, TRUE);
        c_gl_obj_free(t_img_drc.h_plane);
    }

    if (t_img_drc.h_screen != NULL_HANDLE)
    {
        c_gl_obj_free(t_img_drc.h_screen);
    }

    if (NULL != pattern_param_t.ps_file_name)
    {
        c_mem_free(pattern_param_t.ps_file_name);
        pattern_param_t.ps_file_name = NULL;
    }

    if (NULL != pattern_param_t.inputData)
    {
        _nav_burning_mode_pattern_free_pic(pattern_param_t.inputData);
        pattern_param_t.inputData = NULL;
    }

    t_img_drc.b_init = FALSE;

    return NAVR_OK;
}

static INT32 _nav_burning_mode_V2_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32  i4_ret = NAVR_OK;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;

    c_memset(&t_g_burning_mode_v2, 0, sizeof(BURNING_MODE_T));
    c_memset(&t_img_drc, 0, sizeof(BURNING_MODE_IMG_DRC_DATA_TMP_T));


    if (NULL_HANDLE == h_patter_loop_timer)
    {
        i4_ret = c_timer_create(&h_patter_loop_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() c_timer_create() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }

    /* Init view. */ // OSD pattern
    i4_ret = burning_mode_view_init (pt_this,
                                     pt_ctx->t_gui_res.h_canvas);

    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"burning_mode_view_init () failed\r\n"));

        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_burning_mode_V2_deinit(
                    VOID
                    )
{
    INT32              i4_ret;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;

    /* Deinit view. */
    i4_ret = burning_mode_view_deinit (& pt_this->t_view);

    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static BOOL _nav_burning_mode_V2_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return FALSE;
}

static INT32 _nav_burning_mode_V2_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;

    DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));

    pt_this->b_active = TRUE;
    return NAVR_OK;
}

static INT32 _nav_burning_mode_V2_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));
    return NAVR_OK;
}

static INT32 _nav_burning_mode_V2_hide(
                    VOID
                    )
{
    INT32              i4_ret = 0;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;
    DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));

    /* Hide view. */
    i4_ret = burning_mode_view_hide (& pt_this->t_view);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }
    pt_this->b_active = FALSE;
    return NAVR_OK;
}

static INT32 _nav_burning_mode_V2_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    INT32              i4_ret;
    UINT8              ui1_factory_mode;
    TV_MODE_T          e_tv_mode;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_NO_SIGNAL:
        /* If don't insert fake channel,Under TV source need use NAV_UI_MSG_EMPTY_SVL to start burning mode*/
        case NAV_UI_MSG_EMPTY_SVL:
        {
            DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, burning_mode_no_signal_nfy\n", __FUNCTION__, __LINE__));

            /* Get TV mode. */
            i4_ret = nav_get_tv_mode (& e_tv_mode);

            if (i4_ret != NAVR_OK)
            {
                break;
            }

            /* Get factory mode. */
            i4_ret = a_cfg_get_factory_mode (& ui1_factory_mode);

            if (i4_ret != APP_CFGR_OK)
            {
                break;
            }

            if ((e_tv_mode == TV_MODE_TYPE_NORMAL)                      &&  /* Normal mode. */
                (ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0)    /* Burning mode. */
            {
                //Burning mode reset if it active
                if(b_burning_mode_active == TRUE){
                    a_nav_burning_mode_V2_pattern_exit();
                    _nav_burning_mode_V2_pattern_timer_stop();
                }

                /* Start burning immediately if toggle pattern is not active. */
                if(pt_this->b_active == FALSE){
                    a_nav_burning_mode_V2_pattern_show(BURNING_MODE_PATTERN_HSTRI);
                    ui1_pattern_count = BURNING_MODE_PATTERN_HSTRI + 1;
                }
            }
        }
        break;

        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        case NAV_UI_MSG_WITH_SIGNAL:
        {
            DBG_INFO((_INFO_HEADER"burning_mode_with_signal\r\n"));
            DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, NAV_UI_MSG_WITH_SIGNAL\n", __FUNCTION__, __LINE__));
            /* Get factory mode. */
            i4_ret = a_cfg_get_factory_mode (& ui1_factory_mode);
            if (i4_ret != APP_CFGR_OK)
            {
                break;
            }

            if((ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
            {
                if(b_burning_mode_active == TRUE){
                    /* Stop burning pattern. */
                    a_nav_burning_mode_V2_pattern_stop();
                }
            }


        }
        break;

        case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        {
            DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, NAV_UI_MSG_AFTER_TV_MODE_CHANGE\n", __FUNCTION__, __LINE__));
            #if 0
            e_tv_mode = (TV_MODE_T)(INT32)pv_arg1;

            if (e_tv_mode != TV_MODE_TYPE_NORMAL)
            {
                /* Stop burning pattern. */
                a_nav_burning_mode_V2_pattern_exit();
                _nav_burning_mode_V2_pattern_timer_stop();
            }
            else /* Normal mode. */
            {
                /* Get factory mode. */
                i4_ret = a_cfg_get_factory_mode (& ui1_factory_mode);

                if (i4_ret != APP_CFGR_OK)
                {
                    break;
                }

                if ((ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0 &&  /* Burning mode. */
                    (nav_is_signal_loss (TV_WIN_ID_MAIN))                   &&  /* No signal. */
                    (! pt_this->b_active))                                      /* Not active. */
                {
                    DBG_INFO((_INFO_HEADER"burning_mode_reset_timer\r\n"));

                    /* Reset timer. */
                    a_nav_burning_mode_V2_pattern_show(BURNING_MODE_PATTERN_HSTRI);
                    ui1_pattern_count = BURNING_MODE_PATTERN_HSTRI + 1;
                }
            }
            #endif
        }
        break;

        case NAV_UI_MSG_APP_PAUSING:
        {
            DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, NAV_UI_MSG_APP_PAUSING\n", __FUNCTION__, __LINE__));
            #if 0
            /* Stop burning pattern. */
            a_nav_burning_mode_V2_pattern_exit();
            _nav_burning_mode_V2_pattern_timer_stop();
            #endif
        }
        break;

#ifdef APP_NAV_BURNING_PLAY_TONE
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            _burning_mode_stop_audio_tone ();
        }
        break;
#endif
        default:
            break;
    }

    return NAVR_OK;

    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_PRE_POWER_OFF:
            {
                _nav_burning_mode_pattern_exit_pattern();
                _nav_burning_mode_V2_pattern_timer_stop();
            }
            break;
        default:
            break;
    }

    return NAVR_OK;
}

INT32 a_nav_burning_mode_V2_register(VOID)
{
    NAV_COMP_T  t_comp;
    INT32       i4_ret = NAVR_OK;

    c_memset (&t_comp, 0, sizeof (NAV_COMP_T));

    t_comp.pf_init           = _nav_burning_mode_V2_init;
    t_comp.pf_deinit         = _nav_burning_mode_V2_deinit;
    t_comp.pf_is_key_handler = _nav_burning_mode_V2_is_key_handler;
    t_comp.pf_activate       = _nav_burning_mode_V2_activate;
    t_comp.pf_inactivate     = _nav_burning_mode_V2_inactivate;
    t_comp.pf_hide           = _nav_burning_mode_V2_hide;
    t_comp.pf_handle_msg     = _nav_burning_mode_V2_handle_msg;

    i4_ret = nav_register_component(
                NAV_COMP_ID_BURNING_MODE,
                &t_comp,
                ~NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BURNING_MODE));

    if (i4_ret != NAVR_OK)
    {
      return i4_ret;
    }

    return NAVR_OK;
}

BOOL a_nav_burning_mode_V2_is_key_handler(NAV_CONTEXT_T*  pt_ctx, UINT32 ui4_key_code)
{
    DBG_INFO(("[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));
    return FALSE;
}

static INT32 _nav_burning_mode_V2_pattern_timer_start(VOID)
{
    INT32 i4_ret = 0;
    UINT32 ui4_timer = 0;

    DBG_INFO(("\n[BURNING_MODE_V2] ###ke_test %s ui1_timer_count: %d\n", __FUNCTION__, ui1_timer_count));  //ke_test

    if(ui1_timer_count == 0)
    {
        ui4_timer = 20000;
        //ui4_timer = 2000;
        ui1_timer_count++;
    }
    else if(ui1_timer_count == 1)
    {
        ui4_timer = 2000;
        ui1_timer_count++;
    }
    else if(ui1_timer_count == 2)
    {
        ui4_timer = 2000;
        ui1_timer_count++;
    }
    else{
        ui1_timer_count = 0;
        ui4_timer = 2000;
    }

    if (NULL_HANDLE != h_patter_loop_timer)
    {
        i4_ret = c_timer_stop(h_patter_loop_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() c_timer_stop() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        }

        i4_ret = c_timer_start(
            h_patter_loop_timer,
            ui4_timer,
            //X_TIMER_FLAG_REPEAT,  // flag repeat can't used for  various time.
            X_TIMER_FLAG_ONCE,
            _nav_burning_mode_show_next_pattern_timer_cb_fct,
            NULL);

        if (OSR_OK != i4_ret)
        {
            DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() c_timer_start() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }

    return 0;
}
static INT32 _nav_burning_mode_V2_pattern_timer_stop(VOID)
{
    INT32 i4_ret = 0;

    i4_ret = c_timer_stop(h_patter_loop_timer);
    if (OSR_OK != i4_ret)
    {
        DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() c_timer_stop() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    ui1_timer_count = 0;  //reset count
    ui1_pattern_count = BURNING_MODE_PATTERN_HSTRI;

    a_scrn_svr_set_enable(TRUE);
    //#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
    //a_banner_set_excl_comp_on(TRUE);
    //#endif
    return 0;
}
VOID burning_mode_V2_under_ext_rc_control(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode_v2;

    DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));

    if(b_burning_mode_active == TRUE)
    {
        a_nav_burning_mode_V2_pattern_stop();
    }

    if (! pt_this->b_active)
    {
        /* Grab activation. */
        nav_grab_activation (NAV_COMP_ID_BURNING_MODE);
    }

    /* Update burning pattern. */
    i4_ret = burning_mode_ext_rc_control_view_update (& pt_this->t_view,ui2_idx);
    if (i4_ret != NAVR_OK)
    {
        return;
    }

    /* Show burning pattern. */
    i4_ret = burning_mode_view_show (& pt_this->t_view);
    if (i4_ret != NAVR_OK)
    {
        return;
    }

}
VOID a_nav_burning_mode_V2_pattern_stop_fct(VOID* param0, VOID* param1, VOID* param2)
{
    INT32  i4_ret;
    CHAR    s_active_app[APP_NAME_MAX_LEN + 1] = {0};
    ISL_REC_T  t_isl_rec = {0};

    DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d\n", __FUNCTION__, __LINE__));

    i4_ret = _nav_burning_mode_pattern_exit_pattern();
    if (NAVR_OK != i4_ret)
    {
        DBG_INFO(("\n[BURNING_MODE_V2] LINE %d @ %s() _nav_burning_mode_pattern_exit_pattern() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return;
    }

    _nav_burning_mode_V2_pattern_timer_stop();
    b_burning_mode_active = FALSE;

    a_am_get_active_app (s_active_app);
    if (c_strcmp(s_active_app, MMP_NAME) != 0)
    {
        INT32 i4_ret = 0;

        i4_ret = nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
        if (i4_ret != NAVR_OK)
        {
            DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, i4_ret:%d\n", __FUNCTION__, __LINE__, i4_ret));
        }

        i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN, t_isl_rec.ui1_id, NULL);
        if (i4_ret != NAVR_OK)
        {
            DBG_INFO(("\n[BURNING_MODE_V2] %s Line: %d, i4_ret:%d\n", __FUNCTION__, __LINE__, i4_ret));
        }

    }
}
VOID a_nav_burning_mode_V2_pattern_stop(VOID)
{
    nav_request_context_switch(a_nav_burning_mode_V2_pattern_stop_fct,
                               NULL,
                               NULL,
                               NULL);
}

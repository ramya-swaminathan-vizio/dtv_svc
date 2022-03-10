#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "test_pattern.h"

#include "nav/banner2/a_banner.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/navigator.h"
#include "nav/a_navigator.h"
#include "c_os.h"
#include "c_svctx.h"
#include "nav/input_src/a_input_src.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/nav_variant.h"
#include "mmp/a_mmp.h"
#include "am/a_am.h"

////////////////////////////////////////////////////////////////////////////////////////
#define  TEST_PATTERN_INVOKE_DUR            (300)

#define  TEST_PATTERNR_OK                   (0)
#define  TEST_PATTERNR_ERR                  (-1)

#define  BLOCK_SIZE                         (10 * 1000 * sizeof(UINT8))

static  HANDLE_T  h_timer_pattern = NULL_HANDLE;
static  IMG_DRC_DATA_TMP_T  t_img_drc = {0};
static  BOOL  b_wait_timeout = FALSE;

static  UINT16  ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;
static  UINT16  ui2_icl_nfy_id = 0;

extern NAV_MODEL_T  t_g_navigator;

COLOR_CALIBRA_TEST_PATTERN_PARAM_T  pattern_param_t;

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
extern VOID a_rest_set_test_patterns_turn_off(VOID);
#endif

////////////////////////////////////////////////////////////////////////////////////////
static VOID _nav_test_pattern_show_pattern(
    BOOL    isFile,
    CHAR*   ps_file_name,
    UINT8*  inputData,
    UINT32  dataSize,
    BOOL    isShowOnVdp);

static INT32 _nav_test_pattern_exit_pattern(VOID);
static INT32 _nav_test_pattern_read_pic(CHAR *path, UINT8 **data, UINT32 *dataSize);
static VOID  _nav_test_pattern_free_pic(UINT8 *data);
static VOID  _nav_test_pattern_cfg_nfy_cb(
                                UINT16              ui2_nfy_id,
                                VOID* 	            pv_tag,
                                UINT16              ui2_id);


////////////////////////////////////////////////////////////////////////////////////////
static VOID _nav_test_pattern_timer_cb_fct (HANDLE_T pt_tm_handle, VOID* pv_tag)
{
    DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() timeout.\n", __LINE__, __FUNCTION__));
    a_banner_set_excl_comp_on(FALSE);
    b_wait_timeout = FALSE;
}

static INT32 _nav_test_pattern_pre_deal (VOID)
{
    INT32  i4_ret;

    if (b_wait_timeout)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() pls wait timeout.\n", __LINE__, __FUNCTION__));
        return TEST_PATTERNR_ERR;
    }

    if (NULL_HANDLE != h_timer_pattern)
    {
    i4_ret = c_timer_start(
        h_timer_pattern,
        TEST_PATTERN_INVOKE_DUR,
        X_TIMER_FLAG_ONCE,
        _nav_test_pattern_timer_cb_fct,
        NULL);

    if (OSR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() c_timer_start() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return TEST_PATTERNR_ERR;
        }
    }

    b_wait_timeout = TRUE;

    return TEST_PATTERNR_OK;

}


static VOID _nav_test_pattern_show_pattern_ex(VOID* param0, VOID* param1, VOID *param2)
{
    COLOR_CALIBRA_TEST_PATTERN_T type = (COLOR_CALIBRA_TEST_PATTERN_T)param0;
    const CHAR* p_file_path = NULL;
    CHAR*  p_file_name = NULL;
    size_t  str_size = 0;

    switch (type)
    {
        case SMPTE_TEST_PATTERN_ONOFF:
            p_file_path = "/basic/pattern/smpte.png";
            break;
        case FLAT_TEST_PATTERN_10:
            p_file_path = "/basic/pattern/flat_20.bmp";
            break;
        case FLAT_TEST_PATTERN_20:
            p_file_path = "/basic/pattern/flat_20.bmp";
            break;
        case FLAT_TEST_PATTERN_30:
            p_file_path = "/basic/pattern/flat_30.bmp";
            break;
        case FLAT_TEST_PATTERN_40:
            p_file_path = "/basic/pattern/flat_40.bmp";
            break;
        case FLAT_TEST_PATTERN_50:
            p_file_path = "/basic/pattern/flat_50.bmp";
            break;
        case FLAT_TEST_PATTERN_60:
            p_file_path = "/basic/pattern/flat_60.bmp";
            break;
        case FLAT_TEST_PATTERN_70:
            p_file_path = "/basic/pattern/flat_70.bmp";
            break;
        case FLAT_TEST_PATTERN_80:
            p_file_path = "/basic/pattern/flat_80.bmp";
            break;
        case FLAT_TEST_PATTERN_90:
            p_file_path = "/basic/pattern/flat_90.bmp";
            break;
        case FLAT_TEST_PATTERN_100:
            p_file_path = "/basic/pattern/flat_100.bmp";
            break;
        case RAMP_TEST_PATTERN_WHITE:
            p_file_path = "/basic/pattern/ramp_white.bmp";
            break;
        case RAMP_TEST_PATTERN_RED:
            p_file_path = "/basic/pattern/ramp_red.bmp";
            break;
        case RAMP_TEST_PATTERN_GREEN:
            p_file_path = "/basic/pattern/ramp_greep.bmp";
            break;
        case RAMP_TEST_PATTERN_BLUE:
            p_file_path = "/basic/pattern/ramp_blue.bmp";
            break;
        case UNIFORMITY_TEST_PATTERN:
            p_file_path = "/basic/pattern/uniformity.png";
            break;
        case COLOR_8_TEST_PATTERN:
            p_file_path = "/basic/pattern/color_8.jpg";
            break;
        case GRAY_32_TEST_PATTERN:
            p_file_path = "/basic/pattern/gray_32.bmp";
            break;
        case WHITE_25P_TEST_PATTERN:
            p_file_path = "/basic/pattern/white_25p.bmp";
            break;
        default:
            break;
    }

    if (NULL == p_file_path)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN] LINE %d @ %s() cannot get file path.\n", __LINE__, __FUNCTION__));
        return;
    }

    str_size = c_strlen(p_file_path);
    p_file_name = (CHAR *)c_mem_alloc(str_size+1);
    if (NULL == p_file_name)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN] LINE %d @ %s() c_mem_alloc() failed\n", __LINE__, __FUNCTION__));
        return;
    }

    c_memset(p_file_name, 0, str_size+1);
    c_strncpy(p_file_name, p_file_path, str_size);
    pattern_param_t.ps_file_name = p_file_name;
    pattern_param_t.isShowOnVdp  = TRUE;
    pattern_param_t.isFile       = TRUE;
    DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} type:%d, file_name:%s.\n", __FUNCTION__, __LINE__,type,p_file_name));
    a_nav_test_pattern_show_pattern(NULL,NULL,NULL);
}
////////////////////////////////////////////////////////////////////////////////////////
VOID a_nav_test_pattern_show_pattern(VOID* param0, VOID* param1, VOID *param2)
{
    INT32           i4_ret;
    NAV_MODEL_T*    pt_this = &t_g_navigator;
    UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    a_icl_custom_get_test_pattern_status(&ui1_val);

    if (ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ != ui1_val)
    {
        TV_WIN_ID_T  e_focus_id = {0};
        ISL_REC_T  t_isl_rec = {0};

        i4_ret = _nav_test_pattern_pre_deal();
        if (TEST_PATTERNR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() test_pattern_pre_deal() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
            return;
        }

        i4_ret = a_tv_get_focus_win(&e_focus_id);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE);

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
                DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() nav_stop_service() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
                return;
            }
        } while(0);
    }

    i4_ret = a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE);

    i4_ret = _nav_test_pattern_read_pic(
        pattern_param_t.ps_file_name,
        &pattern_param_t.inputData,
        &pattern_param_t.dataSize);
    if(TEST_PATTERNR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} _nav_test_pattern_read_pic fail.\n", __FUNCTION__, __LINE__));
        return;
    }

    pattern_param_t.isFile = FALSE;
    _nav_test_pattern_show_pattern(
        pattern_param_t.isFile,
        pattern_param_t.ps_file_name,
        pattern_param_t.inputData,
        pattern_param_t.dataSize,
        pattern_param_t.isShowOnVdp
        );

    b_wait_timeout = FALSE;

}

VOID a_nav_test_pattern_exit_pattern(VOID* param0, VOID* param1, VOID* param2)
{
    INT32  i4_ret;
    ISL_REC_T  t_isl_rec = {0};
    UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    a_icl_custom_get_test_pattern_status(&ui1_val);

    if (ICL_RECID_TEST_PATTERN_STATUS_DISABLE == ui1_val)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() test pattern does't show, return directly\n", __LINE__, __FUNCTION__));
        return;
    }

    if (ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ == ui1_val)
    {
        _nav_test_pattern_exit_pattern();
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() seq_exit return directly\n", __LINE__, __FUNCTION__));
        return;
    }

    i4_ret = _nav_test_pattern_pre_deal();
    if (TEST_PATTERNR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() test_pattern_pre_deal() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return;
    }

    i4_ret = _nav_test_pattern_exit_pattern();
     if (TEST_PATTERNR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() test_pattern_exit() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return;
    }

    if (param0 != NULL)
    {
        ((VOID (*)(BOOL))param0)(FALSE);
    }

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
    a_banner_set_excl_comp_on(TRUE);
#endif
    a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_DISABLE);

    CHAR    s_active_app[APP_NAME_MAX_LEN + 1] = {0};
    a_am_get_active_app (s_active_app);
    if (c_strcmp(s_active_app, MMP_NAME) != 0)
    {
        nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
        nav_change_av_inp_by_id(TV_WIN_ID_MAIN, t_isl_rec.ui1_id, NULL);

    }
    b_wait_timeout = FALSE;
}

VOID a_nav_test_pattern_show(COLOR_CALIBRA_TEST_PATTERN_T type)
{

    nav_request_context_switch(_nav_test_pattern_show_pattern_ex,
                               (VOID*) type,
                               NULL,
                               NULL);
}

VOID a_nav_test_pattern_exit(VOID)
{
    nav_request_context_switch(a_nav_test_pattern_exit_pattern,
                               NULL,
                               NULL,
                               NULL);
}

#ifdef APP_CAST_TEST_PATTERN
VOID _menu_to_nav_show_test_pattern_ex(VOID* param0, VOID* param1, VOID *param2)
{
    COLOR_CALIBRA_TEST_PATTERN_T type = (COLOR_CALIBRA_TEST_PATTERN_T)param0;
    const CHAR* p_file_path = NULL;
    CHAR*  p_file_name = NULL;
    size_t  str_size = 0;

    if (SMPTE_TEST_PATTERN_ONOFF == type)
    {
        p_file_path = "/basic/pattern/smpte.png";
    }
    else if (FLAT_TEST_PATTERN_10 == type)
    {
        p_file_path = "/basic/pattern/flat_10.bmp";
    }
    else if (FLAT_TEST_PATTERN_20 == type)
    {
        p_file_path = "/basic/pattern/flat_20.bmp";
    }
    else if (FLAT_TEST_PATTERN_30 == type)
    {
        p_file_path = "/basic/pattern/flat_30.bmp";
    }
    else if (FLAT_TEST_PATTERN_40 == type)
    {
        p_file_path = "/basic/pattern/flat_40.bmp";
    }
    else if (FLAT_TEST_PATTERN_50 == type)
    {
        p_file_path = "/basic/pattern/flat_50.bmp";
    }
    else if (FLAT_TEST_PATTERN_60 == type)
    {
        p_file_path = "/basic/pattern/flat_60.bmp";
    }
    else if (FLAT_TEST_PATTERN_70 == type)
    {
        p_file_path = "/basic/pattern/flat_70.bmp";
    }
    else if (FLAT_TEST_PATTERN_80 == type)
    {
        p_file_path = "/basic/pattern/flat_80.bmp";
    }
    else if (FLAT_TEST_PATTERN_90 == type)
    {
        p_file_path = "/basic/pattern/flat_90.bmp";
    }
    else if (FLAT_TEST_PATTERN_100 == type)
    {
        p_file_path = "/basic/pattern/flat_100.bmp";
    }
    else if (RAMP_TEST_PATTERN_BLUE == type)
    {
        p_file_path = "/basic/pattern/ramp_blue.bmp";
    }
    else if (RAMP_TEST_PATTERN_GREEN == type)
    {
        p_file_path = "/basic/pattern/ramp_green.bmp";
    }
    else if (RAMP_TEST_PATTERN_RED == type)
    {
        p_file_path = "/basic/pattern/ramp_red.bmp";
    }
    else if (RAMP_TEST_PATTERN_WHITE== type)
    {
        p_file_path = "/basic/pattern/ramp_white.bmp";
    }
    else if (UNIFORMITY_TEST_PATTERN == type)
    {
        p_file_path = "/basic/pattern/uniformity.png";
    }
    str_size = c_strlen(p_file_path);

    if (NULL == p_file_path)
    {
        DBG_LOG_PRINT(("\n[XXXX] LINE %d @ %s() cannot get file path.\n", __LINE__, __FUNCTION__));
        return;
    }

    p_file_name = (CHAR *)c_mem_alloc(str_size+1);
    if (NULL == p_file_name)
    {
        DBG_LOG_PRINT(("\n[XXXX] LINE %d @ %s() c_mem_alloc() failed\n", __LINE__, __FUNCTION__));
        return;
    }

    c_memset(p_file_name, 0, str_size+1);
    c_strncpy(p_file_name, p_file_path, str_size);
    pattern_param_t.ps_file_name = p_file_name;
    pattern_param_t.isShowOnVdp  = TRUE;
    pattern_param_t.isFile       = TRUE;
    DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} type:%d,name:%s,file_name:%s .\n", __FUNCTION__, __LINE__,type,p_file_name,pattern_param_t.ps_file_name));
    a_nav_test_pattern_show_pattern(NULL,NULL,NULL);
}
VOID a_menu_to_nav_show_test_pattern(COLOR_CALIBRA_TEST_PATTERN_T type)
{

    nav_request_context_switch(_menu_to_nav_show_test_pattern_ex,
                               (VOID*) type,
                               NULL,
                               NULL);
}
VOID a_menu_to_nav_exit_test_pattern(VOID)
{
    nav_request_context_switch(a_nav_test_pattern_exit_pattern,
                               NULL,
                               NULL,
                               NULL);
}

/* exit pattern can't select svctx when in menu by power off/on*/
static VOID _nav_test_pattern_exit_pattern_by_menu_power(VOID* param0, VOID* param1, VOID* param2)
{
    INT32  i4_ret = 0;
    UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    a_icl_custom_get_test_pattern_status(&ui1_val);

    if (ICL_RECID_TEST_PATTERN_STATUS_DISABLE == ui1_val)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() test pattern does't show, return directly\n", __LINE__, __FUNCTION__));
        return;
    }

    i4_ret = _nav_test_pattern_exit_pattern();
     if (TEST_PATTERNR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() test_pattern_exit() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
        return;
    }

    a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_DISABLE);

}

VOID a_nav_exit_test_pattern_by_menu_power(VOID)
{
    nav_request_context_switch(_nav_test_pattern_exit_pattern_by_menu_power,
                               NULL,
                               NULL,
                               NULL);
}

#endif

static INT32  _nav_test_pattern_read_pic(CHAR *path, UINT8 **data, UINT32 *dataSize)
{
    INT32   handle = -1;
    VOID*   p_data = NULL;
    SIZE_T  offset = 0;
    SIZE_T  ret = 0;

    handle = open(path, O_RDONLY);
    if (-1 == handle)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} open fail.\n", __FUNCTION__, __LINE__));
        return TEST_PATTERNR_ERR;
    }

    do {
        VOID*   p_tmp_data = NULL;

        p_tmp_data = realloc(p_data, BLOCK_SIZE + offset);
        if (!p_tmp_data)
        {
            DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} realloc fail.\n", __FUNCTION__, __LINE__));
            goto ERR;
        }
        p_data = p_tmp_data;

        ret = read(handle, p_data + offset, BLOCK_SIZE);
        if (ret == -1)
        {
            DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} read fail.\n", __FUNCTION__, __LINE__));
            goto ERR;
        }
        offset += ret;
    }while(0 != ret);

    *data = (UINT8 *)p_data;
    *dataSize = (UINT32)offset;

    close(handle);

    return TEST_PATTERNR_OK;
ERR:
    free(p_data);
    close(handle);

    return TEST_PATTERNR_ERR;
}

static VOID  _nav_test_pattern_free_pic(UINT8 *data)
{
    c_mem_free(data);
}

static VOID _nav_test_pattern_show_pattern(
    BOOL    isFile,
    CHAR*   ps_file_name,
    UINT8*  inputData,
    UINT32  dataSize,
    BOOL    isShowOnVdp)
{
    INT32                   i4_ret;
    GL_SURFACE_DESC_T       t_surf_descr = {0};
    GL_DISPLAY_OPT_T        t_dsp_opt = {0};
    UINT32                  ui4_screen_w = 0, ui4_screen_h = 0;
    IMG_DRC_DISPLAY_RES_TMP_T*  pt_res = &t_img_drc.pt_res;
    HANDLE_T                h_img = NULL_HANDLE;
    IMG_TYPE_DATA_T         t_data = {0};
    UINT32                  ui4_info_len, ui4_src_w, ui4_src_h, ui4_dst_w, ui4_dst_h, ui4_dst_x, ui4_dst_y;
    GL_SIZE_T               t_resolution;
    UINT32                  ui4_ratio_w, ui4_ratio_h;
    UINT16                  ui2_plane_index = 0;
    GL_COLORMODE_T          e_cm = GL_COLORMODE_ARGB_D8888;

    DBG_LOG_PRINT(("[TEST_PATTERN]{%s %d}.\r\n",__FUNCTION__, __LINE__));

    if (t_img_drc.b_init == TRUE)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN]{%s %d} pls exit before show pattern, return!\r\n",__FUNCTION__, __LINE__));
        return;
    }

    if (isFile && ps_file_name == NULL)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN]{%s %d} parameters err.\r\n",__FUNCTION__, __LINE__));
        return;
    }

    if (!isFile &&( inputData == NULL || dataSize == 0))
    {
        DBG_LOG_PRINT(("[TEST_PATTERN]{%s %d} parameters err.\r\n",__FUNCTION__, __LINE__));
        return;
    }

    c_memset(&t_img_drc, 0, sizeof(IMG_DRC_DATA_TMP_T));

    if (isShowOnVdp)
    {
        ui2_plane_index = 2;
        e_cm = GL_COLORMODE_YUV_422_RS;
    }

    i4_ret = c_gl_screen_open(SN_PRES_MAIN_DISPLAY, NULL, NULL, &t_img_drc.h_screen);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("[TEST_PATTERN{%s %d}]x_gl_screen_open(%s) failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, SN_PRES_MAIN_DISPLAY, i4_ret));
        return;
    }

    do
    {
        i4_ret = c_gl_screen_get_panel_size(t_img_drc.h_screen, &ui4_screen_w, &ui4_screen_h);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_screen_get_panel_size() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        DBG_LOG_PRINT(("panel_size=(%d,%d).\n", ui4_screen_w, ui4_screen_h));

        i4_ret = c_gl_plane_open(t_img_drc.h_screen, ui2_plane_index, &t_img_drc.h_plane);
        if (GLR_OK != i4_ret)
        {
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_plane_open() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        i4_ret = c_gl_plane_link(t_img_drc.h_plane, t_img_drc.h_screen, TRUE);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_plane_link() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        i4_ret = c_gl_view_create(ui4_screen_w,
                                  ui4_screen_h,
                                  TRUE/*FALSE*/,
                                  &pt_res->h_view);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_view_create() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
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
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_surface_create_from_dfb() failed. i4_ret = %d.\r\n", __FUNCTION__, __LINE__, i4_ret));

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
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_view_create_viewport() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));

            pt_res->ui4_viewport = 0;

            break;
        }

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
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_img_fopen() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
            break;
        }

        ui4_info_len = sizeof(GL_SIZE_T);
        i4_ret = c_img_get_info(h_img, IMG_INFO_PRIMARY_DIMENSION, NULL, &t_resolution, &ui4_info_len);
        if (i4_ret != IMGR_OK)
        {
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_img_get_info() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
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
        c_gl_plane_enable(t_img_drc.h_plane, FALSE);
        c_thread_delay(10);
        ui4_dst_x = 0;
        ui4_dst_y = 0;
        #else
        ui4_dst_x = (ui4_screen_w - ui4_dst_w) >> 1;
        ui4_dst_y = (ui4_screen_h - ui4_dst_h) >> 1;
        #endif

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
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_img_sync_load() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
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
            DBG_ERROR(("[TEST_PATTERN]{%s %d}x_gl_plane_flip() failed. i4_ret = %d.\r\n",__FUNCTION__, __LINE__, i4_ret));
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

static INT32 _nav_test_pattern_exit_pattern(VOID)
{
    IMG_DRC_DISPLAY_RES_TMP_T*  pt_res = &t_img_drc.pt_res;

    if (t_img_drc.b_init == FALSE)
    {
        DBG_LOG_PRINT(("[TEST_PATTERN]{%s %d} has been exited, return!\r\n",__FUNCTION__, __LINE__));
        return TEST_PATTERNR_ERR;
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
        _nav_test_pattern_free_pic(pattern_param_t.inputData);
        pattern_param_t.inputData = NULL;
    }

    t_img_drc.b_init = FALSE;

    return TEST_PATTERNR_OK;
}

static VOID _nav_test_pattern_cfg_nfy_cb(
                UINT16              ui2_nfy_id,
                VOID* 	            pv_tag,
                UINT16              ui2_id)
{
#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST) &&defined(SYS_C4TV_SUPPORT)
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);
    UINT8   ui1_pattern_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    if (ui2_cfg_nfy_id != ui2_nfy_id || ui2_rec_id != APP_CFG_RECID_CAST_TV_STATUS)
    {
        return;
    }

    a_icl_custom_get_test_pattern_status(&ui1_pattern_val);

    if (ICL_RECID_TEST_PATTERN_STATUS_DISABLE != ui1_pattern_val)
    {
        UINT8   ui1_c4tv_status = APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE;

        a_cfg_get_cast_tv_status(&ui1_c4tv_status);

        if (ui1_c4tv_status == APP_CFG_CAST_TV_STATUS_CAST_MODE)
        {
            DBG_LOG_PRINT(("[TEST_PATTERN] LINE %d @ %s()\n", __LINE__, __FUNCTION__));
            _nav_test_pattern_exit_pattern();
            a_rest_set_test_patterns_turn_off();
        }
    }
#endif
}

static INT32 _nav_test_pattern_icl_nfy_cb(
                UINT16              ui2_nfy_id,
                VOID* 	            pv_tag,
                ICL_NOTIFY_DATA_T*    pt_notify_data)
{
    UINT8    ui1_pattern_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;
    ICL_GRPID_TYPE    e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);

    if (e_grp_id != ICL_GRPID_TEST_PATTERN_STATUS)
    {
        return NAVR_OK;
    }

    a_icl_custom_get_test_pattern_status(&ui1_pattern_val);
    if (ICL_RECID_TEST_PATTERN_STATUS_DISABLE == ui1_pattern_val)
    {
        a_scrn_svr_set_enable(TRUE);
        DBG_LOG_PRINT(("\r[TEST_PATTERN] {%s,%d} a_scrn_svr_set_enable(%s).\r\n", __FUNCTION__, __LINE__, "TRUE"));
    }
    else
    {
        a_scrn_svr_set_enable(FALSE);
        DBG_LOG_PRINT(("\r[TEST_PATTERN] {%s,%d} a_scrn_svr_set_enable(%s).\r\n", __FUNCTION__, __LINE__, "FALSE"));
    }

    return NAVR_OK;
}

static INT32 _nav_test_pattern_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32  i4_ret = NAVR_OK;

    if (NULL_HANDLE == h_timer_pattern)
    {
        i4_ret = c_timer_create(&h_timer_pattern);
        if (OSR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() c_timer_create() failed, ret=%d\n", __LINE__, __FUNCTION__, i4_ret));
            return TEST_PATTERNR_ERR;
        }
    }

    if (APP_CFGR_OK != a_cfg_notify_reg(
                            APP_CFG_GRPID_MISC,
                            NULL,
                            _nav_test_pattern_cfg_nfy_cb,
                            &ui2_cfg_nfy_id))
    {
        DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} a_cfg_notify_reg fail.\r\n", __FUNCTION__, __LINE__));
    }

    if (ICLR_OK != a_icl_notify_reg(
                            ICL_GRPID_TEST_PATTERN_STATUS,
                            ICL_PRIORITY_DEFAULT,
                            NULL,
                            NULL,
                            _nav_test_pattern_icl_nfy_cb,
                            &ui2_icl_nfy_id))
	{
        DBG_LOG_PRINT(("[TEST_PATTERN] {%s,%d} a_icl_notify_reg fail.\r\n", __FUNCTION__, __LINE__));
		ui2_icl_nfy_id = 0;
	}

    return NAVR_OK;
}

static INT32 _nav_test_pattern_deinit(
                    VOID
                    )
{
    return NAVR_OK;
}

static BOOL _nav_test_pattern_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return FALSE;
}

static INT32 _nav_test_pattern_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return NAVR_OK;
}

static INT32 _nav_test_pattern_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}

static INT32 _nav_test_pattern_hide(
                    VOID
                    )
{
    return NAVR_OK;
}

static INT32 _nav_test_pattern_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    //INT32  i4_ret = NAVR_OK;

    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_PRE_POWER_OFF:
            {
                _nav_test_pattern_exit_pattern();
                #if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
                a_rest_set_test_patterns_turn_off();
                #endif
            }
            break;
        default:
            break;
    }

    return NAVR_OK;
}

INT32 a_nav_test_pattern_register(VOID)
{
    NAV_COMP_T  t_comp;
    INT32       i4_ret = NAVR_OK;

    c_memset (&t_comp, 0, sizeof (NAV_COMP_T));

    t_comp.pf_init           = _nav_test_pattern_init;
    t_comp.pf_deinit         = _nav_test_pattern_deinit;
    t_comp.pf_is_key_handler = _nav_test_pattern_is_key_handler;
    t_comp.pf_activate       = _nav_test_pattern_activate;
    t_comp.pf_inactivate     = _nav_test_pattern_inactivate;
    t_comp.pf_hide           = _nav_test_pattern_hide;
    t_comp.pf_handle_msg     = _nav_test_pattern_handle_msg;

    i4_ret = nav_register_component(
                NAV_COMP_ID_TEST_PATTERN,
                &t_comp,
                COMP_EXEC_SET_TEST_PATTERN);

    if (i4_ret != NAVR_OK)
    {
      return i4_ret;
    }

    return NAVR_OK;
}


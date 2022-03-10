#ifndef _PIC_ARR_UINT8_
#define _PIC_ARR_UINT8_

#include "u_common.h"
#include "c_img.h"
#include "c_gl.h"
#include "app_util/a_tv.h"
#include "nav/nav_common.h"
#include "a_test_pattern.h"

#undef  DBG_ERROR
#define DBG_ERROR(_stmt)                DBG_LOG_PRINT(_stmt)

typedef struct _IMG_DRC_DISPLAY_RES_TMP_T
{
    GL_HVIEW_T                  h_view;
    GL_HSURFACE_T               h_surf;
    UINT32                      ui4_viewport;
    UINT8                       ui1_flag;
}IMG_DRC_DISPLAY_RES_TMP_T;

typedef struct _IMG_DRC_DATA_TMP_T
{
    GL_HSCREEN_T                h_screen;
    GL_HPLANE_T                 h_plane;
    IMG_DRC_DISPLAY_RES_TMP_T   pt_res;
    BOOL                        b_init;
}IMG_DRC_DATA_TMP_T;

typedef struct _COLOR_CALIBRA_TEST_PATTERN_T
{
    BOOL    isFile;
    BOOL    isShowOnVdp;
    CHAR*   ps_file_name;
    UINT8*  inputData;
    UINT32  dataSize;
} COLOR_CALIBRA_TEST_PATTERN_PARAM_T;

extern COLOR_CALIBRA_TEST_PATTERN_PARAM_T  pattern_param_t;

extern VOID  a_nav_test_pattern_show_pattern(VOID* param0, VOID* param1, VOID *param2);
extern VOID  menu_page_color_calibration_exit_pattern(VOID* param0, VOID* param1, VOID* param2);
extern INT32 a_nav_test_pattern_register(VOID);

#ifdef APP_CAST_TEST_PATTERN
extern VOID a_menu_to_nav_show_test_pattern(COLOR_CALIBRA_TEST_PATTERN_T type);
extern VOID a_menu_to_nav_exit_test_pattern(VOID);
extern VOID a_nav_exit_test_pattern_by_menu_power(VOID);

#endif
#endif

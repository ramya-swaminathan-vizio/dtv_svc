#ifndef _BURNING_MODE_V2_H_
#define _BURNING_MODE_V2_H_

#include "u_common.h"
#include "c_img.h"
#include "c_gl.h"
#include "app_util/a_tv.h"
#include "nav/nav_common.h"
#include "a_burning_mode_v2.h"
#include "nav/burning_mode/burning_mode.h"


#undef  DBG_ERROR
#define DBG_ERROR(_stmt)                DBG_LOG_PRINT(_stmt)

typedef struct _BURNING_MODE_IMG_DRC_DISPLAY_RES_TMP_T
{
    GL_HVIEW_T                  h_view;
    GL_HSURFACE_T               h_surf;
    UINT32                      ui4_viewport;
    UINT8                       ui1_flag;
} BURNING_MODE_IMG_DRC_DISPLAY_RES_TMP_T;

typedef struct _BURNING_MODE_IMG_DRC_DATA_TMP_T
{
    GL_HSCREEN_T                h_screen;
    GL_HPLANE_T                 h_plane;
    BURNING_MODE_IMG_DRC_DISPLAY_RES_TMP_T   pt_res;
    BOOL                        b_init;
} BURNING_MODE_IMG_DRC_DATA_TMP_T;

typedef struct _BURNING_MODE_TEST_PATTERN_T
{
    BOOL    isFile;
    BOOL    isShowOnVdp;
    CHAR*   ps_file_name;
    UINT8*  inputData;
    UINT32  dataSize;
    BOOL    b_phot_4k;
} BURNING_MODE_TEST_PATTERN_PARAM_T;

extern BURNING_MODE_TEST_PATTERN_PARAM_T  pattern_param_t;

extern VOID  a_nav_burning_mode_pattern_show_pattern(VOID* param0, VOID* param1, VOID *param2);
extern INT32 a_nav_burning_mode_V2_register(VOID);

#endif

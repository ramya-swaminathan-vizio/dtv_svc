#include "common.h"
#include "picture_ex.h"

#ifdef __cplusplus
extern "C" {
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_icl.h"
#include "app_util/icl/a_icl_custom.h"
#include "u_drv_cust.h"
#include "c_rm.h"
#include "a_picture_ex.h"
#include "nav/test_pattern/test_pattern.h"
#include "c_svctx.h"
#include "wdk/widget/wdk_widget.h"
#include "rest/rest.h"
#include "mmp/a_mmp.h"
#include "am/a_am.h"
#include "menu2/menu_common/menu_common.h"
#include "a_rest_event.h"
#include "res/menu2/menu_custom.h"
#include "menu2/a_menu.h"

extern VOID menu_common_get_vid_pic_mode_text(UINT16 ui2_idx, CHAR* ps_pic_mode, SIZE_T z_len);

extern COLOR_CALIBRA_TEST_PATTERN_PARAM_T  pattern_param_t;
extern VOID a_nav_test_pattern_show_pattern(VOID *param0, VOID* param1, VOID* param2);
extern VOID a_nav_test_pattern_exit_pattern(VOID *param0, VOID* param1, VOID* param2);
extern INT32 menu_page_color_tuner_adjust_test_pattern(UINT16 ui2_test_page,UINT16 ui2_test_pattern);
extern UINT16 menu_page_color_tuner_get_test_pattern(UINT16 ui2_scrn_page);

}
#endif

#define     RGB_OFF     0
#define     RGB_ON      1

#define     COL_RED     0
#define     COL_GREEN   1
#define     COL_BLUE    2
#define     COL_CYAN    3
#define     COL_MAGENTA 4
#define     COL_YELLOW  5

#define     ROW_HUE         0
#define     ROW_SATURATION  1
#define     ROW_BRIGHTNESS  2
#define     ROW_OFFSET      3
#define     ROW_GAIN        4

#define APP_AND_DRV_OFFSET_MID_VALUE        128

#define _11_POINT_GAIN_COL_GAIN                     ((UINT8)0)
#define _11_POINT_GAIN_COL_RED                      ((UINT8)1)
#define _11_POINT_GAIN_COL_GREEN                    ((UINT8)2)
#define _11_POINT_GAIN_COL_BLUE                     ((UINT8)3)
#define REST_CUST_PIC_MODE_NAME_MAX_LEN             (14)

#define COLOR_TUNER_PAGE       0
#define SMPTE_TEST_PATTERN     (COLOR_TUNER_PAGE+1)
#define FLAT_TEST_PATTERN      (SMPTE_TEST_PATTERN+1)
#define RAMP_TEST_PATTERN      (FLAT_TEST_PATTERN+1)
#define UNIFORMITY_ANALYZER_TEST_PATTERN      (RAMP_TEST_PATTERN+1)

#define CHANNEL_INFORMATION_STATUS_UNLOCK  0
#define CHANNEL_INFORMATION_STATUS_LOCK    1


#define COLOR_TUNER_PQ_MAP2_DRV_COLOR(_ui1_hlt_col, _ui1_color) \
{                                                               \
    switch(_ui1_hlt_col)                                        \
    {                                                           \
    case COL_RED:                                               \
        (_ui1_color) = 1;                                       \
        break;                                                  \
    case COL_GREEN:                                             \
        (_ui1_color) = 3;                                       \
        break;                                                  \
    case COL_BLUE:                                              \
        (_ui1_color) = 5;                                       \
        break;                                                  \
    case COL_CYAN:                                              \
        (_ui1_color) = 4;                                       \
        break;                                                  \
    case COL_MAGENTA:                                           \
        (_ui1_color) = 0;                                       \
        break;                                                  \
    case COL_YELLOW:                                            \
        (_ui1_color) = 2;                                       \
    default:                                                    \
           break;                                               \
    }                                                           \
}

// driver module  map---> 0: lume   1: hue   2:sat
#define COLOR_TUNER_PQ_MAP2_DRV_MODULE(_ui1_hlt_row, _ui1_module) \
{                                                                 \
    switch(_ui1_hlt_row)                                          \
    {                                                             \
    case ROW_HUE:                                                 \
        (_ui1_module) = 1;                                        \
        break;                                                    \
    case ROW_SATURATION:                                          \
        (_ui1_module) = 2;                                        \
        break;                                                    \
    case ROW_BRIGHTNESS:                                          \
        (_ui1_module) = 0;                                        \
        break;                                                    \
    default:                                                      \
           break;                                                 \
    }                                                             \
}

/*
static UINT16 aui2_flat_test_ydata[] =
{0,102,205,307,410,512,614,717,819,920,1023};
*/

static INT32 smpte_test_pattern_idx = 0;
static INT32 flat_test_pattern_idx = 0;
static INT32 ramp_test_pattern_idx = 0;
static INT32 uniformity_analyzer_text_pattern_idx = 0;
//static INT16 i2_g_scrn_mode = 0;

static  HANDLE_T    h_g_vga_svctx = NULL_HANDLE;
static  WDK_TOAST_T t_g_vga_toast;

static  HANDLE_T    h_g_sleep_timer = NULL_HANDLE;
static  UTF16_T     t_g_sleep_toast_str[128] = {0};
UINT16 ui2_cfg_pic_mode_id;  /* The ACFG notify id for picture mode */

//static VOID color_calibration_show_pattern(COLOR_CALIBRA_TEST_PATTERN_T type);
static VOID color_calibration_exit_pattern(VOID);

VOID rest_set_preset_pic_mode_chg_status(BOOL b_is_chg)
{
    INT32       i4_ret = 0;
    INT16       i2_pic_mode = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);

    LOG_ON_ERR(i4_ret);

    if(i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, b_is_chg);
    }

    REST_LOG_I("i2_pic_mode=%d\n", i2_pic_mode);
}

VOID set_clr_temp_chg_status(BOOL b_is_chg)
{
    INT32       i4_ret = 0;
    INT16       i2_clr_temp = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    LOG_ON_ERR(i4_ret);

    if(i2_clr_temp < ACFG_CLR_TEMP_NUM)
    {
        a_cfg_set_clr_temp_chg_status(i2_clr_temp, b_is_chg);
    }

    REST_LOG_I("i2_clr_temp=%d\n", i2_clr_temp);
}

VOID clr_tuner_custom_process(UINT16 ui2_grpid, UINT16 ui2_recid, INT32 i4_val)
{
    REST_LOG_I("Enter, ui2_grpid: %d, ui2_recid: %d, i4_val: %d\n\r", (int)ui2_grpid, (int)ui2_recid, (int)i4_val);

    UINT8 ui1_row = 0;
    UINT8 ui1_col = 0;

    UINT8 ui1_color  = 0;
    UINT8 ui1_module = 0;
	UINT8 ui1_odm_id = 0;
	UINT8 ui1_offset= APP_AND_DRV_OFFSET_MID_VALUE;/* Check the AP middle  value with driver middle value to compute the offeset value. And the offset value is 128*/
	a_cfg_custom_get_odm_idx(&ui1_odm_id);
//	if (ui1_odm_id == 2)		//Del Foxconn Tommy 20180408
	if ((ui1_odm_id == 2) || (ui1_odm_id == 4)) 	//Add Foxconn Tommy 20180408
	{
		a_cfg_cust_get_color_tune_offset(&ui1_offset);
	}

    if (APP_CFG_GRPID_VIDEO == ui2_grpid)
    {
        REST_LOG_I("APP_CFG_GRPID_VIDEO\n\r");

        if (ui2_recid == APP_CFG_RECID_VID_CLR_HUE_R)
        {
            ui1_row = ROW_HUE;
            ui1_col = COL_RED;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_HUE_G)
        {
            ui1_row = ROW_HUE;
            ui1_col = COL_GREEN;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_HUE_B)
        {
            ui1_row = ROW_HUE;
            ui1_col = COL_BLUE;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_HUE_C)
        {
            ui1_row = ROW_HUE;
            ui1_col = COL_CYAN;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_HUE_M)
        {
            ui1_row = ROW_HUE;
            ui1_col = COL_MAGENTA;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_HUE_Y)
        {
            ui1_row = ROW_HUE;
            ui1_col = COL_YELLOW;
        }

        else if (ui2_recid == APP_CFG_RECID_VID_CLR_SAT_R)
        {
            ui1_row = ROW_SATURATION;
            ui1_col = COL_RED;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_SAT_G)
        {
            ui1_row = ROW_SATURATION;
            ui1_col = COL_GREEN;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_SAT_B)
        {
            ui1_row = ROW_SATURATION;
            ui1_col = COL_BLUE;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_SAT_C)
        {
            ui1_row = ROW_SATURATION;
            ui1_col = COL_CYAN;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_SAT_M)
        {
            ui1_row = ROW_SATURATION;
            ui1_col = COL_MAGENTA;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_SAT_Y)
        {
            ui1_row = ROW_SATURATION;
            ui1_col = COL_YELLOW;
        }

        else if (ui2_recid == APP_CFG_RECID_VID_CLR_BRI_R)
        {
            ui1_row = ROW_BRIGHTNESS;
            ui1_col = COL_RED;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_BRI_G)
        {
            ui1_row = ROW_BRIGHTNESS;
            ui1_col = COL_GREEN;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_BRI_B)
        {
            ui1_row = ROW_BRIGHTNESS;
            ui1_col = COL_BLUE;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_BRI_C)
        {
            ui1_row = ROW_BRIGHTNESS;
            ui1_col = COL_CYAN;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_BRI_M)
        {
            ui1_row = ROW_BRIGHTNESS;
            ui1_col = COL_MAGENTA;
        }
        else if (ui2_recid == APP_CFG_RECID_VID_CLR_BRI_Y)
        {
            ui1_row = ROW_BRIGHTNESS;
            ui1_col = COL_YELLOW;
        }
        else
        {
            return;
        }

        if(ui1_row == ROW_BRIGHTNESS)
        {
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
        }
        else if(ui1_row == ROW_HUE)
        {
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
        }
        else if(ui1_row == ROW_SATURATION)
        {
            a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
        }

#ifdef NEVER
        COLOR_TUNER_PQ_MAP2_DRV_COLOR(ui1_col,ui1_color);
        COLOR_TUNER_PQ_MAP2_DRV_MODULE(ui1_row,ui1_module);
        a_cfg_custom_set_pq_exp_color(ui1_color,
                                      ui1_module,
                                      i4_val,
                                      ui1_offset);
#endif /* NEVER */

    }

}

/**********************************11 Point Gain Page************************************************************************/
static INT32 _clr_tuner_11_point_page_update_values(VOID)
{
    UINT8       ui1_i = 0, ui1_j = 0;
    INT32       i4_ret = 0;
    INT16       i2_gain_num = 0;
    INT32       i4_GammactrlPts[_11_POINT_GAIN_COL_BLUE][_11_POINT_GAIN_100+1] = {{0,0}};
    INT16       i2_GammactrlPts[_11_POINT_GAIN_COL_BLUE][_11_POINT_GAIN_100+1] = {{0,0}};
    UINT8       ui1_odm_id = 0;
    INT16       i2_offset= 0;
	a_cfg_custom_get_odm_idx(&ui1_odm_id);
//	if (ui1_odm_id == 2)		//Del Foxconn Tommy 20180408
	if ((ui1_odm_id == 2) || (ui1_odm_id == 4)) 	//Add Foxconn Tommy 20180408
    {
        a_cfg_cust_get_white_balance_offset(&i2_offset);
        DBG_LOG_PRINT(("%s_%d i2_offset:%d \n",__FUNCTION__,__LINE__,i2_offset));
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), &i2_gain_num);

    // Get all 11 point values
    for (ui1_i = 0; ui1_i <= _11_POINT_GAIN_100; ui1_i++)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), ui1_i);

        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_RED),   &i2_GammactrlPts[_11_POINT_GAIN_COL_RED-1][ui1_i]);
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_GREEN), &i2_GammactrlPts[_11_POINT_GAIN_COL_GREEN-1][ui1_i]);
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_BLUE),  &i2_GammactrlPts[_11_POINT_GAIN_COL_BLUE-1][ui1_i]);
    }

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_gain_num);

    for (ui1_i = 0; ui1_i < _11_POINT_GAIN_COL_BLUE; ui1_i++)
    {
        for (ui1_j = 0; ui1_j <= _11_POINT_GAIN_100; ui1_j++)
        {
            i4_GammactrlPts[ui1_i][ui1_j] = (INT32)i2_GammactrlPts[ui1_i][ui1_j] + i2_offset ;
        }
    }

    // Update
    i4_ret = a_cfg_update_11_point((VOID*)i4_GammactrlPts, sizeof(i4_GammactrlPts));
    REST_LOG_I("11 point page acfg update:%d\n\r",i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));

    return 0;
}

INT32 clr_tuner_11_point_page_get_values(UINT16 ui2_recid, UINT8 ui1_gain_id, INT32* pi4_val)
{
    REST_LOG_I("Enter, ui2_recid: %d, ui1_gain_id: %d\n\r", (int)ui2_recid, (int)ui1_gain_id);

    UINT16 ui2_rec_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_recid);
    INT16  i2_val =0;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), ui1_gain_id);
    a_cfg_av_get(ui2_rec_id, &i2_val);
    *pi4_val = (INT32)i2_val;

    return 0;
}

INT32 clr_tuner_11_point_page_set_values(UINT16 ui2_recid, UINT8 ui1_gain_id, INT32 i4_val)
{
    REST_LOG_I("Enter, ui2_recid: %d, ui1_gain_id: %d, i4_val: %d\n\r", (int)ui2_recid, (int)ui1_gain_id, (int)i4_val);
    INT16 i2_clr_temp = 0;

    UINT16 ui2_rec_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_recid);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), ui1_gain_id);
    a_cfg_av_set(ui2_rec_id, (INT16)i4_val);
    a_cfg_cust_drv_set_20_p_wb();
    menu_pic_energy_change_sepcial_page_set_status(TRUE);
    //a_menu_11_point_page_update_txt(FALSE);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    a_cfg_set_clr_temp_chg_status(i2_clr_temp,TRUE);

    //_clr_tuner_11_point_page_update_values();

    //set_clr_temp_chg_status(TRUE);

    return 0;
}

UINT16 get_total_picture_mode_num()
{
    UINT16  ui2_i = 0;
    BOOL    b_is_exist= FALSE;
    UINT16  ui2_count = 0;

    for(ui2_i=0; ui2_i<ACFG_CUST_SET_PIC_MODE_NUM_EX; ui2_i++)
    {
        a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui2_i,&b_is_exist);

        if (b_is_exist)
        {
            ui2_count++;
        }
    }

    REST_LOG_I("[Total Picture Mode Num]: %d\n\r", (ui2_count + ACFG_PRE_SET_PIC_MODE_NUM));

    return ui2_count + ACFG_PRE_SET_PIC_MODE_NUM;
}

VOID get_vid_pic_mode_text(
    UINT16    ui2_idx,   /* in */
    CHAR*     ps_pic_mode,   /* out */
    SIZE_T    z_len)
{
    menu_common_get_vid_pic_mode_text(ui2_idx, ps_pic_mode, z_len);
    ps_pic_mode[z_len-1] = '\0';
}

VOID get_current_vid_pic_mode_name(CHAR*     ps_pic_mode)
{
    INT16  i2_pic_mode_idx = 0;

    i2_pic_mode_idx = menu_get_vid_pic_mode_idx();

    get_vid_pic_mode_text(i2_pic_mode_idx, ps_pic_mode, 64);
    REST_LOG_I("Pic mode idx:%d,name:%s\r\n", i2_pic_mode_idx,ps_pic_mode);
}


VOID color_calibration_set_color_tuner_table_header(UINT16 ui2_color_id,INT16  i2_val,WDK_TOAST_T* pt_toast)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    INT16  i2GOnOff = 0;
    INT16  i2BOnOff = 0;
    INT16  i2_new_ROnOff = 0;
    INT16  i2_new_GOnOff = 0;
    INT16  i2_new_BOnOff = 0;
    INT16  i2_clr_temp = 0;

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    a_cfg_av_get( ui2_id, &i2ROnOff);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    a_cfg_av_get( ui2_id, &i2GOnOff);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    a_cfg_av_get( ui2_id, &i2BOnOff);

    i2_new_ROnOff = i2ROnOff;
    i2_new_GOnOff = i2GOnOff;
    i2_new_BOnOff = i2BOnOff;

    switch(ui2_color_id)
    {
        case 0://red
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
            i2_new_ROnOff = i2_val;
            break;
        }
        case 1://green
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
            i2_new_GOnOff = i2_val;
            break;
        }
        case 2://blue
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
            i2_new_BOnOff = i2_val;
            break;
        }
        default:
            break;
    }

     if((i2_new_ROnOff + i2_new_GOnOff + i2_new_BOnOff) == 0)// don't allow the case RGB:000
     {
         if(i2_val == 0)
         {
             return ;
         }
     }
    a_cfg_av_set(ui2_id, i2_val);

    a_cfg_custom_set_rgb_on_off((UINT8)i2_new_ROnOff,(UINT8)i2_new_GOnOff,(UINT8)i2_new_BOnOff);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    //a_cfg_set_clr_temp_chg_status(i2_clr_temp,TRUE);

    rest_send_msg_to_nav(pt_toast);
 }

UINT8 smpte_test_pattern_get_value(VOID)
{
	smpte_test_pattern_idx = menu_page_color_tuner_get_test_pattern(SMPTE_TEST_PATTERN);
	return smpte_test_pattern_idx;
}

VOID smpte_test_pattern_set_value(UINT8 ui1_val)
{
#if 0
    if (ramp_test_pattern_idx || flat_test_pattern_idx || uniformity_analyzer_text_pattern_idx)
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
        color_calibration_exit_pattern();
        c_thread_delay(100);
    }

    if (0 != ramp_test_pattern_idx)
    {
        ramp_test_pattern_idx = 0;
    }

    /* set flat test pattern off */
    if(0 != flat_test_pattern_idx)
    {
        flat_test_pattern_idx = 0;
    }

    /* set uniformity analyzer test pattern off */
    if(0 != uniformity_analyzer_text_pattern_idx)
    {
        uniformity_analyzer_text_pattern_idx = 0;
    }

    if(ui1_val == 0)
    {
        color_calibration_exit_pattern();
    }
    else if(ui1_val == 1)
    {
        color_calibration_show_pattern(SMPTE_TEST_PATTERN_ONOFF);
    }

#endif
menu_page_color_tuner_adjust_test_pattern(SMPTE_TEST_PATTERN,ui1_val);
smpte_test_pattern_idx = menu_page_color_tuner_get_test_pattern(SMPTE_TEST_PATTERN);
}


INT16 flat_test_pattern_get_value(VOID)
{
    flat_test_pattern_idx = menu_page_color_tuner_get_test_pattern(FLAT_TEST_PATTERN);
    return flat_test_pattern_idx;
}

VOID flat_test_pattern_set_value(CHAR* p_str,WDK_TOAST_T* pt_toast)
{
    UINT8   ui1_idx = 0;

    if(c_strcmp(p_str,"Off") == 0)
    {
        ui1_idx = 0;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
    }
    else if(c_strcmp(p_str,"10%") == 0)
    {
        ui1_idx = 1;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_1;
    }
    else if(c_strcmp(p_str,"20%") == 0)
    {
        ui1_idx = 2;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_2;
    }
    else if(c_strcmp(p_str,"30%") == 0)
    {
        ui1_idx = 3;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_3;
    }
    else if(c_strcmp(p_str,"40%") == 0)
    {
        ui1_idx = 4;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_4;
    }
    else if(c_strcmp(p_str,"50%") == 0)
    {
        ui1_idx = 5;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_5;
    }
    else if(c_strcmp(p_str,"60%") == 0)
    {
        ui1_idx = 6;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_6;
    }
    else if(c_strcmp(p_str,"70%") == 0)
    {
        ui1_idx = 7;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_7;
    }
    else if(c_strcmp(p_str,"80%") == 0)
    {
        ui1_idx = 8;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_8;
    }
    else if(c_strcmp(p_str,"90%") == 0)
    {
        ui1_idx = 9;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_9;
    }
    else if(c_strcmp(p_str,"100%") == 0)
    {
        ui1_idx = 10;
        pt_toast->style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_FLAT_PERCENT_10;
    }


#if 0
    if ( 0 != ui1_idx )
    {
        if ((ui1_idx != flat_test_pattern_idx && 0 != flat_test_pattern_idx) || ramp_test_pattern_idx || smpte_test_pattern_idx || uniformity_analyzer_text_pattern_idx)
        {
            a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
            color_calibration_exit_pattern();
            c_thread_delay(100);
        }

        if (0 != ramp_test_pattern_idx)
        {
            ramp_test_pattern_idx = 0;
        }

        /* set smpte test pattern off */
        if (0 != smpte_test_pattern_idx)
        {
            smpte_test_pattern_idx = 0;
        }

        /* set uniformity analyzer test pattern off */
        if (0 != uniformity_analyzer_text_pattern_idx)
        {
            uniformity_analyzer_text_pattern_idx = 0;
        }
    }

    if (0 == ui1_idx)
    {
        if (0 != flat_test_pattern_idx)
        {
            a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE);
            color_calibration_exit_pattern();
            rest_send_msg_to_nav(pt_toast);
        }
    }
    else
    {
        if (flat_test_pattern_idx != ui1_idx)
        {
            color_calibration_show_pattern((COLOR_CALIBRA_TEST_PATTERN_T)(SMPTE_TEST_PATTERN_ONOFF+ui1_idx));
            rest_send_msg_to_nav(pt_toast);
        }
    }
   #endif
    menu_page_color_tuner_adjust_test_pattern(FLAT_TEST_PATTERN,ui1_idx);

    flat_test_pattern_idx = menu_page_color_tuner_get_test_pattern(FLAT_TEST_PATTERN);

}


VOID ramp_test_pattern_get_value(UINT16* pui2_val)
{
/*
    UINT16      ui2_val = 0;
    INT16       i2ROnOff = RGB_ON;
    INT16       i2GOnOff = RGB_ON;
    INT16       i2BOnOff = RGB_ON;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), &i2ROnOff);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), &i2GOnOff);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), &i2BOnOff);

    if(i2ROnOff == RGB_ON && i2GOnOff == RGB_ON && i2BOnOff == RGB_ON && ramp_test_pattern_idx == 0)
    {
        ui2_val = 0;
    }
    else if(i2ROnOff == RGB_ON && i2GOnOff == RGB_ON && i2BOnOff == RGB_ON && ramp_test_pattern_idx == 1)
    {
        ui2_val = 1;
    }
    else if(i2ROnOff == RGB_ON && i2GOnOff == RGB_OFF && i2BOnOff == RGB_OFF)
    {
        ui2_val = 2;
    }
    else if(i2ROnOff == RGB_OFF && i2GOnOff == RGB_ON && i2BOnOff == RGB_OFF)
    {
        ui2_val = 3;
    }
    else if(i2ROnOff == RGB_OFF && i2GOnOff == RGB_OFF && i2BOnOff == RGB_ON)
    {
        ui2_val = 4;
    }
*/
     ramp_test_pattern_idx = menu_page_color_tuner_get_test_pattern(RAMP_TEST_PATTERN);

    *pui2_val = (UINT16) ramp_test_pattern_idx;
}

VOID ramp_test_pattern_set_value(UINT16 ui2_val,WDK_TOAST_T* pt_toast)
{
    UINT8       ui1_val = 0;

    switch (ui2_val)
    {
        case 0:           /* Off */
            ui1_val = 0;
            break;
        case 1:           /* White */
            ui1_val = 1;
            break;
        case 2:           /* Red */
            ui1_val = 2;
            break;
        case 3:           /* Green */
            ui1_val = 3;
            break;
        case 4:           /* Blue */
            ui1_val = 4;
            break;
        default:
            ui1_val = 0;
            break;

    	}
#if 0
    if ( 0 != ui1_val )
    {
        if ((ui1_val != ramp_test_pattern_idx && 0 != ramp_test_pattern_idx) || smpte_test_pattern_idx || flat_test_pattern_idx || uniformity_analyzer_text_pattern_idx)
        {
            a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
            color_calibration_exit_pattern();
            c_thread_delay(100);
        }

        /* set smpte test pattern off */
        if (0 != smpte_test_pattern_idx)
        {
            smpte_test_pattern_idx = 0;
        }

        /* set flat test pattern off */
        if (0 != flat_test_pattern_idx)
        {
            flat_test_pattern_idx = 0;
        }

        /* set uniformity analyzer test pattern off */
        if (0 != uniformity_analyzer_text_pattern_idx)
        {
            uniformity_analyzer_text_pattern_idx = 0;
        }
    }

    if (0 == ui1_val)
    {
        if (0 != ramp_test_pattern_idx)
        {
            a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE);
            color_calibration_exit_pattern();
            //rest_send_msg_to_nav(pt_toast);
        }
    }
    else
    {
        if (ramp_test_pattern_idx != ui1_val)
        {
            color_calibration_show_pattern((COLOR_CALIBRA_TEST_PATTERN_T)(FLAT_TEST_PATTERN_100+ui1_val));
            //rest_send_msg_to_nav(pt_toast);
        }
    }
#endif
	menu_page_color_tuner_adjust_test_pattern(RAMP_TEST_PATTERN,ui1_val);

    ramp_test_pattern_idx = menu_page_color_tuner_get_test_pattern(RAMP_TEST_PATTERN);

 }

UINT8 uniformity_analyzer_test_pattern_get_value(VOID)
{
    uniformity_analyzer_text_pattern_idx = menu_page_color_tuner_get_test_pattern(UNIFORMITY_ANALYZER_TEST_PATTERN);
    return uniformity_analyzer_text_pattern_idx;
}

VOID uniformity_analyzer_test_pattern_set_value(UINT8 ui1_val)
{
#if 0
    if (ramp_test_pattern_idx || flat_test_pattern_idx || smpte_test_pattern_idx)
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
        color_calibration_exit_pattern();
        c_thread_delay(100);
    }

    if (0 != ramp_test_pattern_idx)
    {
        ramp_test_pattern_idx = 0;
    }

    /* set flat test pattern off */
    if(0 != flat_test_pattern_idx)
    {
        flat_test_pattern_idx = 0;
    }

    /* set smpte test pattern off */
    if(0 != smpte_test_pattern_idx)
    {
        smpte_test_pattern_idx = 0;
    }

    if(ui1_val == 0)
    {
        color_calibration_exit_pattern();
    }
    else if(ui1_val == 1)
    {
        color_calibration_show_pattern(UNIFORMITY_TEST_PATTERN);
    	}
#endif
    menu_page_color_tuner_adjust_test_pattern(UNIFORMITY_ANALYZER_TEST_PATTERN,ui1_val);
    uniformity_analyzer_text_pattern_idx = menu_page_color_tuner_get_test_pattern(UNIFORMITY_ANALYZER_TEST_PATTERN);;

}

BOOL rest_set_test_pattern_turn_off_in_cast(VOID)
{
    TV_WIN_ID_T     e_focus_id = TV_WIN_ID_MAIN;
    ISL_REC_T       t_isl_rec = {0};
    BOOL b_is_pic_mode_lock = FALSE;

    /*If is scanning channels, exit it */
    if (nav_is_channel_scan_active())
    {
        return TRUE;
    }

    /*If previous source is CastTV, exit it */
    a_tv_get_focus_win(&e_focus_id);

    a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);

    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        CHAR    s_active_app[APP_NAME_MAX_LEN + 1] = {0};
        a_am_get_active_app (s_active_app);
        /* if mmp active can set pattern on/off */
        if (c_strcmp(s_active_app, MMP_NAME) == 0)
        {
            return FALSE;
        }

        WDK_TOAST_T t_toast;
        UTF16_T     w2s_string[256]  = {0};

        c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

        t_toast.e_toast_style  = WDK_WARNING_TOAST;
        t_toast.e_string_style = WDK_STRING_STRING;

        c_uc_w2s_strcpy(w2s_string,REST_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_25));

        t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

        rest_send_msg_to_nav(&t_toast);

        return TRUE;
    }

    //if picture mode was locked, exit it
    a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_pic_mode_lock);
    if (b_is_pic_mode_lock)
    {
        return TRUE;
    }

    return FALSE;
}


VOID a_rest_set_test_patterns_turn_off(VOID)
{
    if (flat_test_pattern_idx || smpte_test_pattern_idx || ramp_test_pattern_idx || uniformity_analyzer_text_pattern_idx)
    {
        WDK_TOAST_T t_toast;
        c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
        t_toast.e_toast_style  = WDK_STRING_TOAST;
        t_toast.e_string_style = WDK_STRING_ID_ID;

        color_calibration_exit_pattern();

        /* set flat test pattern off */
        if(0 != flat_test_pattern_idx)
        {
            flat_test_pattern_idx = 0;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_FLAT_TEST_PATTERN;
        }

        /* set smpte test pattern off */
        if(0 != smpte_test_pattern_idx)
        {
            smpte_test_pattern_idx = 0;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_SMPTE_TEST_PATTERN;
        }

        if (0 != ramp_test_pattern_idx)
        {
            ramp_test_pattern_idx = 0;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_RAMP_TEST_PATTERN_TITLE;
        }

        /* set uniformity analyzer test pattern off */
        if(0 != uniformity_analyzer_text_pattern_idx)
        {
            uniformity_analyzer_text_pattern_idx = 0;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_UNIFANA_TEST_PATTERN;
        }

        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
        rest_send_msg_to_nav(&t_toast);
    }
}


VOID color_calibration_change_screen_mode(BOOL b_on)
{
    UINT8   ui1_val = 1;

	DBG_LOG_PRINT(("%s() %d: APP_CFG_RECID_SCREEN_MODE b_on=%d\n",__FUNCTION__,__LINE__,b_on));

    if (b_on)
    {
        CHAR                        s_disp_name[ACFG_MAX_DISP_NAME + 1];
        VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};

        /* Get current timing */
        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        a_cfg_av_get_timing(s_disp_name, &t_timing);
        if((1070<=t_timing.ui4_height && t_timing.ui4_height<=1090)
            || (710<=t_timing.ui4_height && t_timing.ui4_height<=730))
        {
            ui1_val = ACFG_TEST_PATTERN_SCRN_MODE_NORMAL;
        }
        else
        {
            ui1_val = ACFG_TEST_PATTERN_SCRN_MODE_WIDE;
        }
        REST_LOG_I("scrn mode:%d\n\r", ui1_val);
        /* Set aspect ratio as 16:9 */
        a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                (VOID *) &ui1_val,
                ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE);
        }
    else
    {
        ui1_val = 0;
        a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                    (VOID *) &ui1_val,
                    ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE);
    }

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
}

INT32 color_tuner_rgb_update(VOID)
{
    INT16       i2ROnOff = 0;
    INT16       i2GOnOff = 0;
    INT16       i2BOnOff = 0;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    a_cfg_av_get( ui2_id, &i2ROnOff);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    a_cfg_av_get( ui2_id, &i2GOnOff);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    a_cfg_av_get( ui2_id, &i2BOnOff);

    a_cfg_custom_set_rgb_on_off((UINT8)i2ROnOff,(UINT8)i2GOnOff,(UINT8)i2BOnOff);

    return 0;
}

INT32 create_pic_mode_name_mapping(CHAR* ps_pic_mode_name)
{

    UINT8       ui1_preset_idx=0;
    UINT8       ui1_custom_idx=0;
    CHAR        s_preset_pic_name[REST_CUST_PIC_MODE_NAME_MAX_LEN +1] = {0};
    CHAR        s_custom_pic_name[REST_CUST_PIC_MODE_NAME_MAX_LEN +1] = {0};
    CHAR        s_num[8+1] = {0};
    INT8        i1_row_idx=-1;
    UINT8       ui1_col_idx = 0;
    UINT8       ui1_append_idx = 0;
    UINT8       ui1_cust_pic_mode_idx[ACFG_PRE_SET_PIC_MODE_NUM][ACFG_PRE_SET_PIC_MODE_NUM] = {{0},{0},{0},{0},{0},{0}};
    BOOL        b_is_exist = FALSE;

    /*step1:check custom pic name is same as the preset pic mode name*/
    for(ui1_preset_idx=0;ui1_preset_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_preset_idx++)
    {
        get_vid_pic_mode_text(ui1_preset_idx,s_preset_pic_name,REST_CUST_PIC_MODE_NAME_MAX_LEN);

        /*enter custom pic mode name is same as the preset pic mode name*/
        if((c_strcasecmp(s_preset_pic_name,ps_pic_mode_name))==0)
        {
            /*record the the row idx*/
            i1_row_idx = ui1_preset_idx;
            REST_LOG_I("pic mode name mapping, idx:%d\n\r", ui1_preset_idx);
            break;
        }
    }

    /*the same pic name not found*/
    if((i1_row_idx==-1)||(i1_row_idx==ACFG_PRE_SET_PIC_MODE_NUM))
    {
        return 0;
    }

    /*step2:create cust pic mode idx table base on the current custom pic mode*/
    for(ui1_custom_idx=0;ui1_custom_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_custom_idx++)
    {
        b_is_exist = FALSE;
        a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui1_custom_idx,&b_is_exist);

        if (b_is_exist)
        {
            c_memset(s_custom_pic_name,0,REST_CUST_PIC_MODE_NAME_MAX_LEN+1);
            a_cfg_cust_get_cust_pic_mode_name(ACFG_PRE_SET_PIC_MODE_NUM+ui1_custom_idx,s_custom_pic_name,REST_CUST_PIC_MODE_NAME_MAX_LEN);
            REST_LOG_I("pic mode name mapping, name:%s,idx:%d\n\r", s_custom_pic_name,ui1_preset_idx);
            for(ui1_preset_idx=0;ui1_preset_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_preset_idx++)
            {
                get_vid_pic_mode_text(ui1_preset_idx,s_preset_pic_name,REST_CUST_PIC_MODE_NAME_MAX_LEN);
                if((c_strncasecmp(s_preset_pic_name,s_custom_pic_name,c_strlen(s_preset_pic_name))==0)&&    //the preset pic name is the presfix of custom pic name
                    (c_strlen(s_custom_pic_name) == c_strlen(s_preset_pic_name)+1)&&
                    ((s_custom_pic_name[c_strlen(s_preset_pic_name)] - '0')>=2)&&
                    ((s_custom_pic_name[c_strlen(s_preset_pic_name)] - '0')<=7))
                {
                    ui1_col_idx = (s_custom_pic_name[c_strlen(s_preset_pic_name)] - '0')-2;
                    ui1_cust_pic_mode_idx[ui1_preset_idx][ui1_col_idx]++;
                }

            }
        }
    }
    /*step3:get the next custom pic mode name append idx base on the table*/
    for(ui1_col_idx=0;ui1_col_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_col_idx++)
    {
        if(ui1_cust_pic_mode_idx[i1_row_idx][ui1_col_idx]==0)
        {
            ui1_append_idx = ui1_col_idx+2;

            c_sprintf(s_num, "%d",  ui1_append_idx);
            c_strcat(ps_pic_mode_name,s_num);
            REST_LOG_I("pic mode name mapping, name:%s,idx:%d\n\r", ps_pic_mode_name,ui1_preset_idx);
            break;
        }
    }
    return 0;

}

INT32 rest_get_menu_is_signal_loss(VOID)
{
    INT32 i4_ret = 0;

    i4_ret = menu_is_signal_loss() ? CHANNEL_INFORMATION_STATUS_UNLOCK: CHANNEL_INFORMATION_STATUS_LOCK;
    REST_LOG_I("menu_is_signal_loss i4_ret: %d.\n\r", i4_ret);

    return i4_ret;
}

/*static VOID color_calibration_show_pattern(COLOR_CALIBRA_TEST_PATTERN_T type)
{
    CHAR*  p_file_name = NULL;
    const CHAR* p_file_path = NULL;
    size_t  str_size = 0;

    color_calibration_change_screen_mode(TRUE);

    if (UNIFORMITY_TEST_PATTERN == type)
    {
        p_file_path = "/basic/pattern/uniformity.png";
    }
    else if (SMPTE_TEST_PATTERN_ONOFF == type)
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
    else if (RAMP_TEST_PATTERN_WHITE == type)
    {
        p_file_path = "/basic/pattern/ramp_white.bmp";
    }

    str_size = c_strlen(p_file_path);

    if (NULL == p_file_path)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() cannot get file path.\n", __LINE__, __FUNCTION__));
        return;
    }

    p_file_name = (CHAR *)c_mem_alloc(str_size+1);
    if (NULL == p_file_name)
    {
        DBG_LOG_PRINT(("\n[TEST_PATTERN] LINE %d @ %s() c_mem_alloc() failed\n", __LINE__, __FUNCTION__));
        return;
    }
    c_memset(p_file_name, 0, str_size+1);
    c_strncpy(p_file_name, p_file_path, str_size);
    pattern_param_t.ps_file_name = p_file_name;
    pattern_param_t.isShowOnVdp  = TRUE;
    pattern_param_t.isFile       = TRUE;

    nav_request_context_switch(a_nav_test_pattern_show_pattern,
                               NULL,
                               NULL,
                               NULL);
    DBG_LOG_PRINT(("[TEST_PATTERN] %s() %d\n", __FUNCTION__, __LINE__));
}*/

static VOID color_calibration_exit_pattern(VOID)
{
    nav_request_context_switch(a_nav_test_pattern_exit_pattern,
                               (VOID *)color_calibration_change_screen_mode,
                               NULL,
                               NULL);
    DBG_LOG_PRINT(("[TEST_PATTERN] %s() %d\n", __FUNCTION__, __LINE__));
}

INT32 auto_size_postion_vga_sync_hv_size(VOID)
{
    INT32  i4_ret = 0;
    UINT16 ui2_h_size = 0;
    UINT16 ui2_v_size = 0;

    i4_ret = acfg_set(IDX_CUSTOM_VGA_H_SIZE, &ui2_h_size, sizeof(UINT16));
    if(i4_ret != APP_CFGR_OK)
    {
        REST_LOG_E("acfg set VGA H SIZE fail, i4_ret:%d\n\r", i4_ret);
    }

    i4_ret = acfg_set(IDX_CUSTOM_VGA_V_SIZE, &ui2_v_size, sizeof(UINT16));
    if(i4_ret != APP_CFGR_OK)
    {
        REST_LOG_E("acfg set VGA V SIZE fail, i4_ret:%d\n\r", i4_ret);
    }

    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    if(i4_ret != APP_CFGR_OK)
    {
        REST_LOG_E("a_cfg_av_update fail, i4_ret:%d\n\r", i4_ret);
    }

    return i4_ret;
}

static VOID _auto_size_postion_do_auto_done(
                                    VOID*      pv_data,
                                    SIZE_T     z_data_size)
{
    BOOL*   pb_success = (BOOL*)pv_data;

    REST_LOG_I("do auto done success:%d\n\r",*pb_success);

    if(*pb_success)
    {
        auto_size_postion_vga_sync_hv_size();
        a_cfg_vga_sync_clk_phs_pos();

        acfg_cust_vga_reset();
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));

        REST_LOG_I("_auto_size_postion_do_auto_done \n\r");
        rest_send_msg_to_nav(&t_g_vga_toast);

        if(h_g_vga_svctx != NULL_HANDLE)
        {
            c_svctx_close(h_g_vga_svctx);
            h_g_vga_svctx = NULL_HANDLE;
        }
    }
}

static VOID _auto_size_postion_svctx_notify_fct(
    HANDLE_T            h_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if(e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS ||
       e_code == SVCTX_NTFY_CODE_INTERRUPTED)
    {
        BOOL    b_success = FALSE;

        rest_async_invoke(_auto_size_postion_do_auto_done, &b_success, sizeof(BOOL), TRUE);
    }

    if(e_code == SVCTX_NTFY_CODE_VIDEO_AUTO_CLK_POS_PHS_DONE)
    {
        BOOL    b_success = TRUE;

        AUTO_CLK_POS_PHS_COND_T     e_cond;
        SIZE_T                      z_size = sizeof(AUTO_CLK_POS_PHS_COND_T);
        if(c_svctx_get(h_g_vga_svctx,
                       SVCTX_COMMON_GET_AUTO_CLK_POS_PHS_COND,
                       &e_cond,
                       &z_size) < 0)
        {
            b_success = FALSE;
        }
        else
        {
            if(e_cond == AUTO_CLK_POS_PHS_COND_SUCCESS)
            {
                b_success = TRUE;
            }
            else
            {
                b_success = FALSE;
            }
        }
        rest_async_invoke(_auto_size_postion_do_auto_done, &b_success, sizeof(BOOL), TRUE);
    }
}

VOID auto_size_postion_start(WDK_TOAST_T* pt_toast )
{
    INT32   i4_ret = 0;
    CHAR    s_disp_name[32] = {0};

    if(NULL_HANDLE == h_g_vga_svctx)
    {
        REST_LOG_I("Enter\n\r");

        t_g_vga_toast = *pt_toast;

        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));

        if(c_strcmp(s_disp_name, SN_PRES_SUB_DISPLAY) == 0)
        {
            i4_ret = c_svctx_open(SVCTX_NAME_SUB, &h_g_vga_svctx);
            if(i4_ret != SVCTXR_OK)
            {
                REST_LOG_E("c_svctx_open fail, i4_ret:%d\n\r", i4_ret);
            }
        }
        else
        {
            i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_g_vga_svctx);
            if(i4_ret != SVCTXR_OK)
            {
                REST_LOG_E("c_svctx_open fail, i4_ret:%d\n\r", i4_ret);
            }
        }

        if(NULL_HANDLE != h_g_vga_svctx)
        {
            i4_ret = c_svctx_set_listener(h_g_vga_svctx,
                                      _auto_size_postion_svctx_notify_fct,
                                      NULL);
            if(i4_ret != SVCTXR_OK)
            {
                REST_LOG_E("c_svctx_set_listener fail, i4_ret:%d\n\r", i4_ret);
            }

            i4_ret = c_svctx_set_stream_attr(h_g_vga_svctx,
                                             ST_VIDEO,
                                             SM_VSH_SET_TYPE_AUTO_CLK_PHS_POS,
                                             (VOID*)NULL,
                                             (SIZE_T)NULL);
            if(i4_ret != SVCTXR_OK)
            {
                REST_LOG_E("c_svctx_set_stream_attr fail, i4_ret:%d\n\r", i4_ret);
            }
        }
    	}
}

static VOID _do_sleep_toast_timer_nfy(VOID* pv_data,
                                          SIZE_T  z_data_size)
{
    WDK_TOAST_T t_sleep_toast;
    c_memset((VOID*)&t_sleep_toast, 0, sizeof(WDK_TOAST_T));

    t_sleep_toast.e_toast_style  = WDK_STRING_TOAST;
    t_sleep_toast.e_string_style = WDK_STRING_STRING;
    t_sleep_toast.style.style_4.w2s_str = (VOID*)t_g_sleep_toast_str;

    rest_send_msg_to_nav(&t_sleep_toast);

    if(NULL_HANDLE != h_g_sleep_timer)
    {
        INT32   i4_ret = 0;
        i4_ret = c_timer_stop(h_g_sleep_timer);
        if(i4_ret != 0)
        {
            REST_LOG_E("c_timer_stop fail, i4_ret:%d\n\r", i4_ret);
        }

        i4_ret = c_timer_delete(h_g_sleep_timer);
        if(i4_ret != 0)
        {
            REST_LOG_E("c_timer_delete fail, i4_ret:%d\n\r", i4_ret);
        }
        h_g_sleep_timer = NULL_HANDLE;
    }
}

static VOID _timer_show_sleep_toast_fct(HANDLE_T  h_timer,
                                            VOID*     pv_tag)
{
    rest_async_invoke(_do_sleep_toast_timer_nfy, NULL, 0, TRUE);
}

INT32 rest_show_sleep_toast(UTF16_T* pw2s_string)
{
    INT32   i4_ret = 0;

    c_uc_w2s_strcpy(t_g_sleep_toast_str,pw2s_string);

    if(NULL_HANDLE == h_g_sleep_timer)
    {
        i4_ret = c_timer_create(&h_g_sleep_timer);
        if(i4_ret != 0)
        {
            REST_LOG_E("c_timer_create fail, i4_ret:%d\n\r", i4_ret);
        }
    }

    if (NULL_HANDLE != h_g_sleep_timer)
    {
        i4_ret = c_timer_start(h_g_sleep_timer,
                               3000,
                               X_TIMER_FLAG_ONCE,
                               _timer_show_sleep_toast_fct,
                               NULL);
        if(i4_ret != 0)
        {
            REST_LOG_E("c_timer_start fail, i4_ret:%d\n\r", i4_ret);
        }
    }

    return 0;
}

VOID _picture_acfg_nfy_cb(
    UINT16                        ui2_nfy_id,
    VOID*                         pv_tag,
    UINT16                        ui2_id)
{
    INT16 i2_pic_mode = 0;
    CHAR pic_name[64] = {0};

    if(ui2_cfg_pic_mode_id != ui2_nfy_id)
    {
        return;
    }

    if (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO,APP_CFG_RECID_PIC_MODE) == ui2_id)
    {
        a_cfg_av_get(ui2_id, &i2_pic_mode);
        get_vid_pic_mode_text(i2_pic_mode, pic_name, 64);
        REST_LOG_I("current pic mode idx:%d , name:%s.\n\r", i2_pic_mode, pic_name);

        //0-Vivid 1-Bright 2-Calibrated 3-Calibrated Dark 4-Game 5-Sport 6-FILMMAKER
        //7-Custom1 8-Custom2 9-Custom3 10-Custom4 11-Custom5 12-Custom6
        rest_event_notify("system/picture/picture_mode", i2_pic_mode, "");
        rest_event_notify("tv_settings/picture/picture_mode",0 ,pic_name);
    }

    return;
}

int picture_acfg_notify_init(void)
{
    INT32 i4_ret;
    REST_LOG_I("Enter.\n");

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_VIDEO,
                              NULL,
                              _picture_acfg_nfy_cb,
                              &ui2_cfg_pic_mode_id);

    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}



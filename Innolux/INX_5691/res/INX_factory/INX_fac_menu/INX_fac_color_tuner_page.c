#include "INX_fac_color_tuner_page.h"
#include "INX_fac_main_page_res.h"

/*parameter*/
static INT16 i2_20_point_gain_num = 0;

/* function */

static INT16 i2_clr_idx = COL_RED;
static UINT32   ui4_dynamic_address = 0;
static INT16 i2_clr_temp = 0;
INT8 i1_clr_hue = 0;
INT8 i1_clr_sat = 0;
INT8 i1_clr_bri = 0;
INT8 i1_clr_offset = 0;
INT8 i1_clr_gain = 0;
INT8 i1_clr_red = 0;
INT8 i1_clr_green = 0;
INT8 i1_clr_blue = 0;
INT8 i1_20_point_values[3][20];

const CHAR *ps_clr_tuner_CT_str_v2[3] = {"Warm", "Cool", "Normal"};
const CHAR *ps_clr_tuner_play_content_v2[4] = {"SDR", "HDR", "HLG", "DV"};


const CHAR *ps_20p_WB_str_v2[20] ={"5%", "10%", "15%", "20%", "25%", "30%", "35%", "40%", "45%", "50%", 
                                   "55%", "60%", "65%", "70%", "75%", "80%", "85%", "90%", "95%", "100%"};

const CHAR *ps_clr_tuner_str_v2[6] = {"Red", "Green", "Blue", "Cyan", "Magenta", "Yellow"};
extern const UINT8 ui1_INX_color_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};  // 3 * 4

static void inx_fac_color_tuner_get_all_settings(void);
static void inx_fac_color_tuner_show_items(void);
static void inx_fac_color_tuner_20_point_get_values(void);

static void color_tuner_init(void)
{    
    a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
    inx_fac_color_tuner_get_all_settings();
    inx_fac_color_tuner_show_items();
}

static void inx_fac_color_tuner_show_items(void)
{
    if( i2_clr_idx == COL_RED ){
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,TRUE);
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,TRUE);
    }else if( i2_clr_idx == COL_GREEN ){
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,TRUE);
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,TRUE);
    }else if( i2_clr_idx == COL_BLUE ){
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,TRUE);
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,TRUE);
    }else if( i2_clr_idx == COL_CYAN ){
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,FALSE);
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,FALSE);
    }else if( i2_clr_idx == COL_MAGENTA ){
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,FALSE);
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,FALSE);
    }else if( i2_clr_idx == COL_YELLOW ){
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,FALSE);
        _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,FALSE);
    }
}

static void inx_fac_color_tuner_get_all_settings(void)
{
    if( i2_clr_idx == COL_RED ){
        i1_clr_hue = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R);
        i1_clr_sat = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R);
        i1_clr_bri = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R);
        i1_clr_offset = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET);
        i1_clr_gain = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN);
    }else if( i2_clr_idx == COL_GREEN ){
        i1_clr_hue = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G);
        i1_clr_sat = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G);
        i1_clr_bri = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G);
        i1_clr_offset = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET);
        i1_clr_gain = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN);
    }else if( i2_clr_idx == COL_BLUE ){
        i1_clr_hue = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B);
        i1_clr_sat = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B);
        i1_clr_bri = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B);
        i1_clr_offset = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET);
        i1_clr_gain = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN);
    }else if( i2_clr_idx == COL_CYAN ){
        i1_clr_hue = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C);
        i1_clr_sat = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C);
        i1_clr_bri = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C);
        i1_clr_offset = 0;
        i1_clr_gain = 0;
    }else if( i2_clr_idx == COL_MAGENTA ){
        i1_clr_hue = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M);
        i1_clr_sat = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M);
        i1_clr_bri = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M);
        i1_clr_offset = 0;
        i1_clr_gain = 0;
    }else if( i2_clr_idx == COL_YELLOW ){
        i1_clr_hue = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y);
        i1_clr_sat = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y);
        i1_clr_bri = color_tuner_get_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y);
        i1_clr_offset = 0;
        i1_clr_gain = 0;
    }
}
static void inx_fac_color_tuner_set_settings(INT8 idx)
{
	if(idx == COL_HUE){
		if( i2_clr_idx == COL_RED )
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R,i1_clr_hue);
		else if(i2_clr_idx == COL_GREEN)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G,i1_clr_hue);
		else if(i2_clr_idx == COL_BLUE)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B,i1_clr_hue);
		else if(i2_clr_idx == COL_CYAN)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C,i1_clr_hue);
		else if(i2_clr_idx == COL_MAGENTA)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M,i1_clr_hue);
		else if(i2_clr_idx == COL_YELLOW)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y,i1_clr_hue);
	}else if(idx == COL_SAT){
		if( i2_clr_idx == COL_RED )
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R,i1_clr_sat);
		else if(i2_clr_idx == COL_GREEN)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G,i1_clr_sat);
		else if(i2_clr_idx == COL_BLUE)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B,i1_clr_sat);
		else if(i2_clr_idx == COL_CYAN)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C,i1_clr_sat);
		else if(i2_clr_idx == COL_MAGENTA)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M,i1_clr_sat);
		else if(i2_clr_idx == COL_YELLOW)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y,i1_clr_sat);
	}else if(idx == COL_BRI){
		if( i2_clr_idx == COL_RED )
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R,i1_clr_bri);
		else if(i2_clr_idx == COL_GREEN)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G,i1_clr_bri);
		else if(i2_clr_idx == COL_BLUE)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B,i1_clr_bri);
		else if(i2_clr_idx == COL_CYAN)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C,i1_clr_bri);
		else if(i2_clr_idx == COL_MAGENTA)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M,i1_clr_bri);
		else if(i2_clr_idx == COL_YELLOW)
			color_tuner_set_settings(COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y,i1_clr_bri);
	}else if(idx == COL_OFFSET){
		if( i2_clr_idx == COL_RED )
			color_tuner_set_offset_gain_settings(APP_CFG_RECID_VID_FAC_OFFSET_R, i1_clr_offset);
		else if(i2_clr_idx == COL_GREEN)
			color_tuner_set_offset_gain_settings(APP_CFG_RECID_VID_FAC_OFFSET_G, i1_clr_offset);
		else if(i2_clr_idx == COL_BLUE)
			color_tuner_set_offset_gain_settings(APP_CFG_RECID_VID_FAC_OFFSET_B, i1_clr_offset);
	}else if(idx == COL_GAIN){
		if( i2_clr_idx == COL_RED )
			color_tuner_set_offset_gain_settings(APP_CFG_RECID_VID_FAC_GAIN_R, i1_clr_gain);
		else if(i2_clr_idx == COL_GREEN)
			color_tuner_set_offset_gain_settings(APP_CFG_RECID_VID_FAC_GAIN_G, i1_clr_gain);
		else if(i2_clr_idx == COL_BLUE)
			color_tuner_set_offset_gain_settings(APP_CFG_RECID_VID_FAC_GAIN_B, i1_clr_gain);
	}
}
static void inx_fac_color_tuner_20_point_get_values(void)
{	
	UINT8       ui1_i = 0;
	INT8 i1_R[COLOR_TUNER_FAC_20POINT_NUM] = {0}; 
	INT8 i1_G[COLOR_TUNER_FAC_20POINT_NUM] = {0}; 
	INT8 i1_B[COLOR_TUNER_FAC_20POINT_NUM] = {0};
	UINT32 ui4_read = 0;
	UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();

	c_memset(i1_20_point_values, 0, sizeof(i1_20_point_values)/sizeof(i1_20_point_values[0]));

	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

	a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
            (VOID *)&i1_R,
            COLOR_TUNER_FAC_20POINT_NUM,
            &ui4_read);
	a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
            (VOID *)&i1_G,
            COLOR_TUNER_FAC_20POINT_NUM,
            &ui4_read);
	a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
            (VOID *)&i1_B,
            COLOR_TUNER_FAC_20POINT_NUM,
            &ui4_read); 
	for (ui1_i = 0; ui1_i < COLOR_TUNER_FAC_20POINT_NUM; ui1_i++)
    {
        i1_20_point_values[0][ui1_i] = i1_R[ui1_i];
        i1_20_point_values[1][ui1_i] = i1_G[ui1_i];
        i1_20_point_values[2][ui1_i] = i1_B[ui1_i];
    }
}

static void inx_fac_color_tuner_copy_to_all(void)
{
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    INT8 i1_R[20] = {0}, i1_G[20] = {0}, i1_B[20] = {0};
    UINT32 ui4_read = 0;
    UINT32 ui4_written = 0;
    UINT32 ui4_clr_idx = 0;
    UINT32 ui4_content_idx = 0;
    INT8 i1_R_gain, i1_G_gain, i1_B_gain, i1_R_offset, i1_G_offset, i1_B_offset;

    // Gain/Offset
    for(ui4_clr_idx = 0; ui4_clr_idx < 3; ui4_clr_idx++){
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
            (VOID *)&i1_R_gain,
            1,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
            (VOID *)&i1_G_gain,
            1,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
            (VOID *)&i1_B_gain,
            1,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
            (VOID *)&i1_R_offset,
            1,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
            (VOID *)&i1_G_offset,
            1,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
            (VOID *)&i1_B_offset,
            1,
            &ui4_read);

        for(ui4_content_idx = 0; ui4_content_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_content_idx++){ //play_content
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                (VOID *)&i1_R_gain,
                1,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                (VOID *)&i1_G_gain,
                1,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                (VOID *)&i1_B_gain,
                1,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                (VOID *)&i1_R_offset,
                1,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                (VOID *)&i1_G_offset,
                1,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                (VOID *)&i1_B_offset,
                1,
                &ui4_written);
        }
    }

    // 20 point
    for(ui4_clr_idx = 0; ui4_clr_idx < 3; ui4_clr_idx++)
    {
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
            (VOID *)&i1_R,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
            (VOID *)&i1_G,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_read);
        a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
            (VOID *)&i1_B,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_read);

        for(ui4_content_idx = 0; ui4_content_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_content_idx++)
        {
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
                (VOID *)&i1_R,
                COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
                (VOID *)&i1_G,
                COLOR_TUNER_FAC_20POINT_NUM , //COLOR_TUNER_FAC_11POINT_NUM,
                &ui4_written);
            a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_INX_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
                (VOID *)&i1_B,
                COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                &ui4_written);
        }
    }
    
}

static void inx_fac_color_tuner_reset_to_default(void)
{
    UINT32 ui4_written = 0;
    UINT32 ui4_num = 11*COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM;
    INT32 i4_array[11*COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM] = {0};

    //color sdr
    a_cfg_eep_raw_write(
        ui4_dynamic_address,
        (VOID *)&i4_array,
        (SIZE_T)ui4_num,
        &ui4_written);
    i2_clr_idx = COL_RED;
    inx_fac_color_tuner_get_all_settings();

    //20 point
    i2_20_point_gain_num = 0;
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_20_point_gain_num);
	inx_fac_color_tuner_20_point_get_values();

    //update PQ
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
    a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
    a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
}

//===============================================================================
static UINT32 inx_fac_color_tuner_page_color_temp_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	CHAR s_string[20] = {0};
	INT16 i2_clr_temp;
	UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

	c_memset(s_string, 0, sizeof(s_string));
	snprintf(s_string, sizeof(s_string), "%s/%s", ps_clr_tuner_CT_str_v2[i2_clr_temp], ps_clr_tuner_play_content_v2[ui1_play_content]);

	c_uc_ps_to_w2s(s_string,w2s_menu_item_string,(NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
	return 0;
}
static UINT32 inx_fac_color_tuner_page_color_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    color_tuner_init();

    c_uc_ps_to_w2s(ps_clr_tuner_str_v2[i2_clr_idx], w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i2_clr_idx;
}

static BOOL inx_fac_color_tuner_page_color_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        i2_clr_idx = nc_code;
        color_tuner_init();
        nav_inx_fac_view_activate(INX_FAC_MENU_COLOR_TUNER_PAGE);
    }
    return TRUE;
}

static UINT32 inx_fac_color_tuner_page_hue_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    inx_fac_color_tuner_get_all_settings();
    nav_fac_number_to_string(i1_clr_hue, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i1_clr_hue;
}

static BOOL inx_fac_color_tuner_page_hue_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
	    i1_clr_hue = nc_code;
        inx_fac_color_tuner_set_settings(COL_HUE);
        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
    }
    return TRUE;
}

static UINT32 inx_fac_color_tuner_page_sat_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    inx_fac_color_tuner_get_all_settings();
    nav_fac_number_to_string(i1_clr_sat, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i1_clr_sat;
}

static BOOL inx_fac_color_tuner_page_sat_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
    	i1_clr_sat = nc_code;
        inx_fac_color_tuner_set_settings(COL_SAT);
        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
    }
    return TRUE;
}

static UINT32 inx_fac_color_tuner_page_bri_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    inx_fac_color_tuner_get_all_settings();
    nav_fac_number_to_string(i1_clr_bri, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i1_clr_bri;
}

static BOOL inx_fac_color_tuner_page_bri_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
    	i1_clr_bri = nc_code;
        inx_fac_color_tuner_set_settings(COL_BRI);
        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
    }
    return TRUE;
}

static UINT32 inx_fac_color_tuner_page_offset_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    inx_fac_color_tuner_get_all_settings();
    nav_fac_number_to_string(i1_clr_offset, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i1_clr_offset;
}

static BOOL inx_fac_color_tuner_page_offset_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
    	i1_clr_offset = nc_code;
        inx_fac_color_tuner_set_settings(COL_OFFSET);
    }
    return TRUE;
}

static UINT32 inx_fac_color_tuner_page_gain_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    inx_fac_color_tuner_get_all_settings();
    nav_fac_number_to_string(i1_clr_gain, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i1_clr_gain;
}

static BOOL inx_fac_color_tuner_page_gain_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
	    i1_clr_gain = nc_code;
        inx_fac_color_tuner_set_settings(COL_GAIN);
    }
    return TRUE;
}
static UINT32 inx_fac_color_tuner_page_20p_content(UTF16_T content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	inx_fac_color_tuner_20_point_get_values();
	c_uc_ps_to_w2s(ps_20p_WB_str_v2[i2_20_point_gain_num],w2s_menu_item_string,(NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
	return i2_20_point_gain_num;
}
static BOOL inx_fac_color_tuner_page_20p_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
	    i2_20_point_gain_num = nc_code;
	    inx_fac_color_tuner_20_point_get_values();
	    nav_inx_fac_view_activate(INX_FAC_MENU_COLOR_TUNER_PAGE);
    }
	return TRUE;
}
static UINT32 inx_fac_color_tuner_page_red_content(UTF16_T content)
{
	i1_clr_red = i1_20_point_values[COLOR_TUNER_20_POINT_GAIN_COL_RED-1][i2_20_point_gain_num];
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	nav_fac_number_to_string(i1_clr_red, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i1_clr_red;
}
static BOOL int_fac_color_tuner_page_red_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
    	i1_clr_red = nc_code;
    	i1_20_point_values[COLOR_TUNER_20_POINT_GAIN_COL_RED-1][i2_20_point_gain_num] = i1_clr_red;
    	inx_fac_color_tuner_20_point_set_values(i1_20_point_values);
    }
	return TRUE;
	
}
static UINT32 inx_fac_color_tuner_page_green_content(UTF16_T content)
{
	i1_clr_green = i1_20_point_values[COLOR_TUNER_20_POINT_GAIN_COL_GREEN-1][i2_20_point_gain_num];
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	nav_fac_number_to_string(i1_clr_green, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i1_clr_green;
}
static BOOL int_fac_color_tuner_page_green_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
    	i1_clr_green = nc_code;
    	i1_20_point_values[COLOR_TUNER_20_POINT_GAIN_COL_GREEN-1][i2_20_point_gain_num] = i1_clr_green;
    	inx_fac_color_tuner_20_point_set_values(i1_20_point_values);
    }
	return TRUE;
	
}
static UINT32 inx_fac_color_tuner_page_blue_content(UTF16_T content)
{
	i1_clr_blue = i1_20_point_values[COLOR_TUNER_20_POINT_GAIN_COL_BLUE-1][i2_20_point_gain_num];
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	nav_fac_number_to_string(i1_clr_blue, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i1_clr_blue;
}
static BOOL int_fac_color_tuner_page_blue_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
    	i1_clr_blue = nc_code;
    	i1_20_point_values[COLOR_TUNER_20_POINT_GAIN_COL_BLUE-1][i2_20_point_gain_num] = i1_clr_blue;
    	inx_fac_color_tuner_20_point_set_values(i1_20_point_values);
    }
	return TRUE;
	
}

static UINT32 inx_fac_color_tuner_page_copy_to_all_content(UTF16_T content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s("Press OK", w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static BOOL int_fac_color_tuner_page_copy_to_all_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_SELECT){
	    inx_fac_color_tuner_copy_to_all();
        nav_fac_view_alert_osd("Finish");
        nav_fac_view_alert_osd_timer(5000);
    }
	return TRUE;
}

static UINT32 inx_fac_color_tuner_page_reset_to_default_content(UTF16_T content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s("Press OK", w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static BOOL int_fac_color_tuner_page_reset_to_default_handle(UINT32 nc_code,UINT32 key_code)
{
    if(key_code == BTN_SELECT){
	    inx_fac_color_tuner_reset_to_default();
        inx_fac_color_tuner_show_items();
        nav_inx_fac_view_activate(INX_FAC_MENU_COLOR_TUNER_PAGE);
        nav_fac_view_alert_osd("Finish");
        nav_fac_view_alert_osd_timer(5000);
    }
	return TRUE;
}

/* G var */
UTF16_T  inx_fac_color_tuner_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'C','o','l','o','r',' ','T','u','n','e','r', '\0'},//For PD Use
    { 'C','o','l','o','r',' ','T','u','n','e','r', '\0'},//For Factory Use
};

inx_page_entry inx_fac_color_tuner_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
    	{NAV_INX_FAC_COLOR_TUNER_PAGE_COLOR_TUNER, MLM_FAC_KEY_MSG_COLOR_TUNER,{0,0}, inx_fac_color_tuner_page_color_temp_content,NULL},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_COLOR, MLM_FAC_KEY_MSG_COLOR, {0,5}, inx_fac_color_tuner_page_color_content, inx_fac_color_tuner_page_color_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_HUE, MLM_FAC_KEY_MSG_HUE, {-50,50}, inx_fac_color_tuner_page_hue_content, inx_fac_color_tuner_page_hue_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_SAT, MLM_FAC_KEY_MSG_SAT, {-50,50}, inx_fac_color_tuner_page_sat_content, inx_fac_color_tuner_page_sat_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_BRI, MLM_FAC_KEY_MSG_BRI, {-50,50}, inx_fac_color_tuner_page_bri_content, inx_fac_color_tuner_page_bri_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_20_POINT, MLM_FAC_KEY_MSG_20p, {0,19}, inx_fac_color_tuner_page_20p_content, inx_fac_color_tuner_page_20p_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_RED, MLM_FAC_KEY_MSG_RED, {-50,50}, inx_fac_color_tuner_page_red_content, int_fac_color_tuner_page_red_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_GREEN, MLM_FAC_KEY_MSG_GREEN, {-50,50}, inx_fac_color_tuner_page_green_content, int_fac_color_tuner_page_green_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_BLUE, MLM_FAC_KEY_MSG_BLUE, {-50,50}, inx_fac_color_tuner_page_blue_content, int_fac_color_tuner_page_blue_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET, MLM_FAC_KEY_MSG_OFFSET, {-100,100}, inx_fac_color_tuner_page_offset_content, inx_fac_color_tuner_page_offset_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN, MLM_FAC_KEY_MSG_GAIN, {-100,100}, inx_fac_color_tuner_page_gain_content, inx_fac_color_tuner_page_gain_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_COPY_TO_ALL, MLM_FAC_KEY_MSG_COPY_TO_ALL, {0,0}, inx_fac_color_tuner_page_copy_to_all_content, int_fac_color_tuner_page_copy_to_all_handle},
        {NAV_INX_FAC_COLOR_TUNER_PAGE_RESET_TO_DEFAULT, MLM_FAC_KEY_MSG_RESET_TO_DEFAULT, {0,0}, inx_fac_color_tuner_page_reset_to_default_content, int_fac_color_tuner_page_reset_to_default_handle},
		{INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};



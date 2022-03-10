#include "INX_fac_pq_info_page.h"
#include "INX_fac_main_page_res.h"

/*parameter*/
extern UINT16 ui2_nav_fac_panel_nits;
extern BOOL b_def_clr_temp_update;
extern BOOL b_nav_fac_get_ELCS;

/* function */
static UINT32 inx_fac_pq_info_page_hsy_ver_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR hsy_ver_buf[32] = {0};
	_nav_fac_get_pq_raw(HSY_ADDR,HSYBIN,6,hsy_ver_buf);          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(hsy_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_pq_info_page_main_ver_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR main_ver_buf[32] = {0};
	_nav_fac_get_pq_raw(MAIN_ADDR,MAINBIN,6,main_ver_buf);          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(main_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_pq_info_page_dolby_ver_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR dolby_ver_buf[32] = {0};
    _nav_fac_get_dolby_ver(dolby_ver_buf,7);          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(dolby_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return 0;
}

static UINT32 inx_fac_pq_info_page_pq_default_ver_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR ver_buf[32] = {0};
    _nav_fac_get_pq_def_ver(ver_buf,7);          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return 0;
}


static UINT32 inx_fac_pq_info_page_tmo_ver_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	CHAR main_ver_buf[32] = {0};
	_nav_fac_get_pq_raw(TMO_ADDR,TMOBIN,6,main_ver_buf);          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(main_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return 0;
}
static UINT32 inx_fac_pq_info_page_panel_ver_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	CHAR buf[64] = {0};
	CHAR main_panel_buf[128] = {0};
	CHAR s_ver[32]={0};
	a_cfg_custom_get_panel_name(buf);
	c_sprintf(main_panel_buf,"/config/panel/%s.ini", buf);
    a_cfg_cust_info_get_ini_item_string(main_panel_buf, PANELINI, PANEL_VER,"Unknown", s_ver, 32);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_ver, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return 0;
}

static UINT32 inx_fac_pq_info_page_backlight_max_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	INT16 i2_val = 0;
	SIZE_T   t_size = sizeof(UINT16);
	acfg_get(IDX_CUST_VGA_PWM_MAX, &i2_val , &t_size);
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}


static UINT32 inx_fac_pq_info_page_backlight_min_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	INT16 i2_val = 0;
	SIZE_T   t_size = sizeof(UINT16);
	acfg_get(IDX_CUST_VGA_PWM_MAX+1, &i2_val , &t_size);
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_pq_bypass_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	UINT32 i2_val = 0;
	i2_val = (UINT32)a_cfg_cust_get_pqbypass_status();
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_boolean_to_text(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_color_temp_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	INT16 i2_val = 0;
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),&i2_val);
    switch (i2_val)
    {
        case ACFG_CUST_CLR_TEMP_WARM:
        {
            i2_val = 0;
			s_tmp_str = "WARM";
        }
        break;

        case ACFG_CUST_CLR_TEMP_COOL:
        {
            i2_val = 1;
			s_tmp_str = "COOL";
        }
        break;

        case ACFG_CUST_CLR_TEMP_NORMAL:
        {
            i2_val = 2;
			s_tmp_str = "NORMAL";
        }
        break;
        default:
            i2_val = 3;
			s_tmp_str = "WORRY";
        break;
    }
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_panel_nits_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UINT32 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_cust_drv_read_panel_nits(&ui2_nav_fac_panel_nits);
	i2_val = ui2_nav_fac_panel_nits;
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_brightness_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	INT16 i2_val = 0;
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), &i2_val);	
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return (UINT32)i2_val;
}
static UINT32 inx_fac_pq_info_page_gamma_status_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	BOOL b_nav_fac_gamma_status = FALSE;
	a_cfg_custom_Get_Factory_GAMMA_OnOff(&b_nav_fac_gamma_status);
	if(b_nav_fac_gamma_status)
    	s_tmp_str = "EEPROM";
	else
    	s_tmp_str = "INI";
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return 0;
}
static UINT32 inx_fac_pq_info_page_scalar_r_gain_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_GAIN_R), &i2_val);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_scalar_g_gain_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_GAIN_G), &i2_val);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_scalar_b_gain_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_GAIN_B), &i2_val);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_scalar_r_offset_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_OFFSET_R), &i2_val);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_scalar_g_offset_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_OFFSET_G), &i2_val);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}
static UINT32 inx_fac_pq_info_page_scalar_b_offset_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_OFFSET_B), &i2_val);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}

static UINT32 inx_fac_pq_info_page_elcs_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	UINT32 i2_val = 0;
	i2_val = b_nav_fac_get_ELCS;
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_boolean_to_text(i2_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return i2_val;
}

static BOOL inx_fac_pq_info_page_backlight_max_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		VID_INFO_T	t_vid_info;
		acfg_set(IDX_CUST_VGA_PWM_MAX, &nc_code , 1);
	    t_vid_info.e_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
	    t_vid_info.ui2Value	= (UINT16)nc_code;
	    t_vid_info.b_ignore_hw  = TRUE;

		nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MAX, &t_vid_info, sizeof(VID_INFO_T), FALSE);

		a_cfg_store();
	}
	return 0;
}

static BOOL inx_fac_pq_info_page_backlight_min_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		VID_INFO_T	t_vid_info;
		acfg_set(IDX_CUST_VGA_PWM_MIN, &nc_code , 1);
	    t_vid_info.e_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
	    t_vid_info.ui2Value	= (UINT16)nc_code;
	    t_vid_info.b_ignore_hw  = TRUE;

		nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MIN,& t_vid_info, sizeof(VID_INFO_T), FALSE);

		a_cfg_store();
	}
	return 0;
}
static BOOL inx_fac_pq_info_page_pq_bypass_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_custom_Set_Factory_PQbypass_OnOff(nc_code);
	}
	return 0;
}
static BOOL inx_fac_pq_info_page_color_temp_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i2_val = 0;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		switch (nc_code)
        {
            case 0:
            {
                i2_val = ACFG_CUST_CLR_TEMP_WARM;
            }
            break;
            case 1:
            {
                i2_val = ACFG_CUST_CLR_TEMP_COOL;
            }
            break;
            case 2:
            {
                i2_val = ACFG_CUST_CLR_TEMP_NORMAL;
            }
            break;
            default:
            i2_val = ACFG_CUST_CLR_TEMP_CUSTOM;
            break;
        }
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_val);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
        a_cfg_store();
	}
	return 0;
}
static BOOL inx_fac_pq_info_page_panel_nits_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		INT32    i4_ret = 0;
	    INT16    i2_color_temparure = 0;
		ui2_nav_fac_panel_nits = nc_code;	 
	    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_color_temparure);

		ACFG_LOG_ON_FAIL(i4_ret);

	    if(i2_color_temparure == ACFG_CUST_CLR_TEMP_WARM)
	    {
	        // Normal (Warm)
        	a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, ACFG_CUST_CLR_TEMP_WARM);
        	a_cfg_cust_drv_update_panel_nits();
	    }
	    else if (i2_color_temparure == ACFG_CUST_CLR_TEMP_COOL)
	    {
	        // Computer (Cool)
        	a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, ACFG_CUST_CLR_TEMP_COOL);
        	a_cfg_cust_drv_update_panel_nits();
	    }
	    else if (i2_color_temparure == ACFG_CUST_CLR_TEMP_NORMAL)
	    {
	        // Normal
        	i4_ret = a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, ACFG_CUST_CLR_TEMP_NORMAL);
        	a_cfg_cust_drv_update_panel_nits();
	    }
	    else
	    {
	        DBG_LOG_PRINT(("%s, ZZZ set panel_nits(%d), result=%d\n", __func__, ui2_nav_fac_panel_nits, i4_ret));
	    }
					       
		DBG_LOG_PRINT(("%s, ZZZ set panel_nits(%d), result=%d\n", __func__, ui2_nav_fac_panel_nits, i4_ret));
	}
	return 0;
}
static BOOL inx_fac_pq_info_page_brightness_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI),
                              (INT16) (UINT32)nc_code);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
	}
	return 0;
}
static BOOL inx_fac_pq_info_page_scalar_r_gain_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i4_val = 0;
	i4_val = nc_code;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), i4_val);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_GAIN_R), i4_val);
	}
	b_def_clr_temp_update = TRUE;
	return 0;
}
static BOOL inx_fac_pq_info_page_scalar_g_gain_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i4_val = 0;
	i4_val = nc_code;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), i4_val);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_GAIN_G), i4_val);
	}
	b_def_clr_temp_update = TRUE;
	return 0;
}
static BOOL inx_fac_pq_info_page_scalar_b_gain_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i4_val = 0;
	i4_val = nc_code;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), i4_val);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_GAIN_B), i4_val);
	}
	b_def_clr_temp_update = TRUE;
	return 0;
}
static BOOL inx_fac_pq_info_page_scalar_r_offset_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i4_val = 0;
	i4_val = nc_code;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), i4_val);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_OFFSET_R), i4_val);
	}
	b_def_clr_temp_update = TRUE;
	return 0;
}
static BOOL inx_fac_pq_info_page_scalar_g_offset_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i4_val = 0;
	i4_val = nc_code;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), i4_val);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_OFFSET_G), i4_val);
	}
	b_def_clr_temp_update = TRUE;
	return 0;
}
static BOOL inx_fac_pq_info_page_scalar_b_offset_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);
	INT16 i4_val = 0;
	i4_val = nc_code;
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), i4_val);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY,APP_CFG_RECID_VID_FAC_OFFSET_B), i4_val);
	}
	b_def_clr_temp_update = TRUE;
	return 0;
}

static BOOL inx_fac_pq_info_page_elcs_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s,%d\n",__func__,__LINE__);	
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		a_cfg_custom_control_ELCS((UINT8)nc_code);
		b_nav_fac_get_ELCS = nc_code;
	}
	return 0;
}

/* G var */
UTF16_T  inx_fac_pq_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'P', 'Q', ' ', 'I', 'N', 'F', 'O', '\0'},//For PD Use
    { 'P', 'Q', ' ', 'I', 'N', 'F', 'O', '\0'},//For Factory Use
};

inx_page_entry inx_fac_pq_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_PQ_INFO_PAGE_HSY_VER, MLM_FAC_KEY_MSG_HSY_VER,{0,0}, inx_fac_pq_info_page_hsy_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_MAIN_VER, MLM_FAC_KEY_MSG_MAIN_VER,{0,0}, inx_fac_pq_info_page_main_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_TMO_VER, MLM_FAC_KEY_MSG_TMO_VER,{0,0}, inx_fac_pq_info_page_tmo_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_PANEL_VER, MLM_FAC_KEY_MSG_PANEL_VER,{0,0}, inx_fac_pq_info_page_panel_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_DOLBY_VER, MLM_FAC_KEY_MSG_DOLBY_VER,{0,0}, inx_fac_pq_info_page_dolby_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_DEFAULT_TBL_VER, MLM_FAC_KEY_MSG_DEFAULT_TBL_VER,{0,0}, inx_fac_pq_info_page_pq_default_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_BACKLIGHT_MAX, MLM_FAC_KEY_MSG_BACKLIGHT_MAX,{0,255}, inx_fac_pq_info_page_backlight_max_content,inx_fac_pq_info_page_backlight_max_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_BACKLIGHT_MIN, MLM_FAC_KEY_MSG_BACKLIGHT_MIN,{0,255}, inx_fac_pq_info_page_backlight_min_content, inx_fac_pq_info_page_backlight_min_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_PQ_BYPASS, MLM_FAC_KEY_MSG_PQ_BYPASS, {0,1}, inx_fac_pq_info_page_pq_bypass_content,  inx_fac_pq_info_page_pq_bypass_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_COLOR_TEMP, MLM_FAC_KEY_MSG_COLOR_TEMP, {0,2}, inx_fac_pq_info_page_color_temp_content, inx_fac_pq_info_page_color_temp_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_PANEL_INTS, MLM_FAC_KEY_MSG_PANEL_NITS, {0,300}, inx_fac_pq_info_page_panel_nits_content, inx_fac_pq_info_page_panel_nits_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_BRIGHTNESS, MLM_FAC_KEY_MSG_BRIHTNESS, {0,100}, inx_fac_pq_info_page_brightness_content, inx_fac_pq_info_page_brightness_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_GAMMA_STATUS, MLM_FAC_KEY_MSG_GAMMA_STATUS, {0,1}, inx_fac_pq_info_page_gamma_status_content,NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_R_GAIN, MLM_FAC_KEY_MSG_SCALER_R_GAIN, {-100,100}, inx_fac_pq_info_page_scalar_r_gain_content, inx_fac_pq_info_page_scalar_r_gain_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_G_GAIN, MLM_FAC_KEY_MSG_SCALER_G_GAIN, {-100,100}, inx_fac_pq_info_page_scalar_g_gain_content, inx_fac_pq_info_page_scalar_g_gain_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_B_GAIN, MLM_FAC_KEY_MSG_SCALER_B_GAIN, {-100,100}, inx_fac_pq_info_page_scalar_b_gain_content, inx_fac_pq_info_page_scalar_b_gain_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_R_OFFSET, MLM_FAC_KEY_MSG_SCALER_R_OFFSET, {-100,100}, inx_fac_pq_info_page_scalar_r_offset_content, inx_fac_pq_info_page_scalar_r_offset_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_G_OFFSET, MLM_FAC_KEY_MSG_SCALER_G_OFFSET, {-100,100}, inx_fac_pq_info_page_scalar_g_offset_content, inx_fac_pq_info_page_scalar_g_offset_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_B_OFFSET, MLM_FAC_KEY_MSG_SCALER_B_OFFSET, {-100,100}, inx_fac_pq_info_page_scalar_b_offset_content, inx_fac_pq_info_page_scalar_b_offset_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_ELCS, MLM_FAC_KEY_MSG_ELCS, {0,1}, inx_fac_pq_info_page_elcs_content, inx_fac_pq_info_page_elcs_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_PQ_INFO_PAGE_HSY_VER, MLM_FAC_KEY_MSG_HSY_VER,{0,0}, inx_fac_pq_info_page_hsy_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_MAIN_VER, MLM_FAC_KEY_MSG_MAIN_VER,{0,0}, inx_fac_pq_info_page_main_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_TMO_VER, MLM_FAC_KEY_MSG_TMO_VER,{0,0}, inx_fac_pq_info_page_tmo_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_PANEL_VER, MLM_FAC_KEY_MSG_PANEL_VER,{0,0}, inx_fac_pq_info_page_panel_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_DOLBY_VER, MLM_FAC_KEY_MSG_DOLBY_VER,{0,0}, inx_fac_pq_info_page_dolby_ver_content, NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_BACKLIGHT_MAX, MLM_FAC_KEY_MSG_BACKLIGHT_MAX,{0,255}, inx_fac_pq_info_page_backlight_max_content,inx_fac_pq_info_page_backlight_max_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_BACKLIGHT_MIN, MLM_FAC_KEY_MSG_BACKLIGHT_MIN,{0,255}, inx_fac_pq_info_page_backlight_min_content, inx_fac_pq_info_page_backlight_min_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_PQ_BYPASS, MLM_FAC_KEY_MSG_PQ_BYPASS, {0,1}, inx_fac_pq_info_page_pq_bypass_content,  inx_fac_pq_info_page_pq_bypass_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_COLOR_TEMP, MLM_FAC_KEY_MSG_COLOR_TEMP, {0,2}, inx_fac_pq_info_page_color_temp_content, inx_fac_pq_info_page_color_temp_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_PANEL_INTS, MLM_FAC_KEY_MSG_PANEL_NITS, {0,300}, inx_fac_pq_info_page_panel_nits_content, inx_fac_pq_info_page_panel_nits_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_BRIGHTNESS, MLM_FAC_KEY_MSG_BRIHTNESS, {0,100}, inx_fac_pq_info_page_brightness_content, inx_fac_pq_info_page_brightness_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_GAMMA_STATUS, MLM_FAC_KEY_MSG_GAMMA_STATUS, {0,1}, inx_fac_pq_info_page_gamma_status_content,NULL},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_R_GAIN, MLM_FAC_KEY_MSG_SCALER_R_GAIN, {-100,100}, inx_fac_pq_info_page_scalar_r_gain_content, inx_fac_pq_info_page_scalar_r_gain_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_G_GAIN, MLM_FAC_KEY_MSG_SCALER_G_GAIN, {-100,100}, inx_fac_pq_info_page_scalar_g_gain_content, inx_fac_pq_info_page_scalar_g_gain_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_B_GAIN, MLM_FAC_KEY_MSG_SCALER_B_GAIN, {-100,100}, inx_fac_pq_info_page_scalar_b_gain_content, inx_fac_pq_info_page_scalar_b_gain_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_R_OFFSET, MLM_FAC_KEY_MSG_SCALER_R_OFFSET, {-100,100}, inx_fac_pq_info_page_scalar_r_offset_content, inx_fac_pq_info_page_scalar_r_offset_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_G_OFFSET, MLM_FAC_KEY_MSG_SCALER_G_OFFSET, {-100,100}, inx_fac_pq_info_page_scalar_g_offset_content, inx_fac_pq_info_page_scalar_g_offset_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_SCALAR_B_OFFSET, MLM_FAC_KEY_MSG_SCALER_B_OFFSET, {-100,100}, inx_fac_pq_info_page_scalar_b_offset_content, inx_fac_pq_info_page_scalar_b_offset_handle},
        {NAV_INX_FAC_PQ_INFO_PAGE_ELCS, MLM_FAC_KEY_MSG_ELCS, {0,1}, inx_fac_pq_info_page_elcs_content, inx_fac_pq_info_page_elcs_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    }
};


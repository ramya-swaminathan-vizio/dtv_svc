#include "INX_fac_sw_info_page.h"
#include "INX_fac_main_page_res.h" 

/*parameter*/
extern BOOL b_nav_fac_reset_done;
extern BOOL b_inx_at_debug_enable;
extern BOOL b_inx_fac_eep_init_done;
extern BOOL b_inx_at_tftps_enable;

extern const char inx_at_build_info[];
UINT16 u16_at_cmd_log_cp_cnt;

/* function */
static UINT32 inx_fac_sw_info_page_factory_ver_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(inx_at_build_info, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}


static UINT32 inx_fac_sw_info_page_inx_mboot_ver_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    CHAR inx_mboot_ver_buf[32] = {0};
    _nav_fac_get_inx_mboot_ver(inx_mboot_ver_buf, INX_MBOOT_BUILD_INFO_SIZE);
	c_uc_ps_to_w2s(inx_mboot_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);

    //test only, zl
	//inx_level_shift_process();
	//inx_vcom_download_process();
	//ending, zl
	
    return 0;
}

static UINT32 inx_fac_sw_info_page_demo_ver_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR s_ver[NAV_FAC_MENU_TEXT1_WIDTH]={0};
    UINT32 demo_file_cnt=0;

    DIR *d;
    struct dirent *dir;
    d = opendir(DEMO_FILE_PATH);
    if(d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if( strstr(dir->d_name,DEMO_FILE_VICE) ){
                demo_file_cnt++;
            }
        }
        closedir(d);
    }
    c_sprintf(s_ver,"%d %s",demo_file_cnt,DEMO_FILE_VICE);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_ver, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_sw_info_page_tcon_ver_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR tcon_ver_buf[32] = {0};
    _nav_fac_get_tcon_ver(tcon_ver_buf,7);          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tcon_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_sw_info_page_gamma_bin_ver_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR tcon_ver_buf[32] = {0};
    _nav_fac_get_gamma_bin_ver(tcon_ver_buf, sizeof(tcon_ver_buf));          
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tcon_ver_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_sw_info_page_factory_reset_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	if (b_nav_fac_reset_done)
    {
    	c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
    }
    else
    {
    	c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
    }
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return 0;
}

static UINT32 inx_fac_sw_info_page_factory_reset_ex_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    if (b_nav_fac_reset_done)
    {
        c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
    }
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

static BOOL inx_fac_sw_info_page_factory_reset_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s().%d : key_code=%d\n",__func__,__LINE__,key_code);
	if(key_code == BTN_CURSOR_RIGHT || key_code == BTN_SELECT)
	{
		b_nav_fac_reset_done = TRUE;
		a_cfg_custom_factory_reset();
		a_amb_reboot();
	}
	return 0;
}

static BOOL inx_fac_sw_info_page_factory_reset_ex_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : key_code=%d\n",__func__,__LINE__,key_code);
    if(key_code == BTN_CURSOR_RIGHT || key_code == BTN_SELECT)
    {
        b_nav_fac_reset_done = TRUE;
        a_cfg_custom_factory_reset_ex();
    }
    return 0;
}

static UINT32 inx_fac_sw_info_page_debug_flag_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    
    nav_fac_number_to_string(b_inx_at_debug_enable, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    printf("%s().%d b_inx_at_debug_enable=%d\n",__func__,__LINE__,b_inx_at_debug_enable);
    return b_inx_at_debug_enable;
}

static UINT32 inx_fac_sw_info_page_at_cmd_log_en_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    BOOL log_enable;

    log_enable = INX_AtCmdGetEnable();
    nav_fac_number_to_string(log_enable, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return log_enable;
}

static UINT32 inx_fac_sw_info_page_at_cmd_log_cp_content(UTF16_T* content)
{
    BOOL b_file_exist;
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR buf[32]={0};
    CHAR carrUsbPath[512]={0};
    CHAR full_path[256]={0};

    //Assign file name
    INX_AtCmdGetLogFile(full_path);

    b_file_exist = (access(full_path, F_OK) == 0 ? TRUE : FALSE);
    if( b_file_exist == FALSE ){
        s_tmp_str = "Log File Not Exist";
    }else{
        if( a_cfg_custom_get_mnt_path(carrUsbPath) == 0 ){
            if( u16_at_cmd_log_cp_cnt == 0 ){
                s_tmp_str = "Press Ok / Right";
            }else{
                c_sprintf(buf,"Cp to USB %d times",u16_at_cmd_log_cp_cnt);
                s_tmp_str = buf;
            }
        }else{
            s_tmp_str = "Can't find usb device";
        }
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_sw_info_page_at_cmd_log_del_content(UTF16_T* content)
{
    BOOL b_file_exist;
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR full_path[256]={0};

    //Assign file name
    INX_AtCmdGetLogFile(full_path);

    b_file_exist = (access(full_path, F_OK) == 0 ? TRUE : FALSE);
    if( b_file_exist ){
        s_tmp_str = full_path+strlen(INX_ATCMD_DIR);
    }else{
        s_tmp_str = "File Not Found!";
    }

    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

static BOOL inx_fac_sw_info_page_debug_flag_key_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : nc_code=%d\n",__func__, __LINE__,nc_code);
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
    {
        b_inx_at_debug_enable = nc_code;
    }
    return 0;
}

static BOOL inx_fac_sw_info_page_at_cmd_log_en_key_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : nc_code=%d\n",__func__, __LINE__,nc_code);
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
    {
        INX_AtCmdSetEnable((BOOL)nc_code);
    }
    return 0;
}

static BOOL inx_fac_sw_info_page_at_cmd_log_cp_key_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR carrUsbPath[512]={0};
    
    if(key_code == BTN_CURSOR_RIGHT || key_code == BTN_SELECT){
        if( a_cfg_custom_get_mnt_path(carrUsbPath) != 0 )
        {
            printf("%s() : get usb path error.\n",__func__);
            return FALSE;
        }
        inx_system("cp -rf %s* %s/", INX_ATCMD_PREFIX, carrUsbPath);
        u16_at_cmd_log_cp_cnt++;
    }
    return TRUE;
}

static BOOL inx_fac_sw_info_page_at_cmd_log_del_key_handle(UINT32 nc_code,UINT32 key_code)
{    
    if(key_code == BTN_CURSOR_RIGHT || key_code == BTN_SELECT){
        INX_AtCmdDelLogFile();
    }
    return TRUE;
}

static UINT32 inx_fac_sw_info_page_eep_init_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    
    nav_fac_number_to_string(b_inx_fac_eep_init_done, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    printf("%s().%d b_inx_at_debug_enable=%d\n",__func__,__LINE__,b_inx_fac_eep_init_done);
    return b_inx_fac_eep_init_done;
}

static BOOL inx_fac_sw_info_page_eep_init_key_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : nc_code=%d\n",__func__, __LINE__,nc_code);
    if(key_code == BTN_CURSOR_RIGHT || key_code == BTN_SELECT)
    {
        
	a_cfg_custom_set_eep_init();
        b_inx_fac_eep_init_done = TRUE;
        
    }
    return 0;
}

static UINT32 inx_fac_sw_info_page_burn_in_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT8 ui_temp_val;
    INT32 i2_val;
    
    a_cfg_get_factory_mode(&ui_temp_val);
    if((ui_temp_val & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
        i2_val = TRUE;
    else
        i2_val = FALSE;
    nav_fac_number_to_string(i2_val, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    printf("%s().%d i2_val=%d\n",__func__,__LINE__,i2_val);
    return i2_val;
}

static BOOL inx_fac_sw_info_page_burn_in_key_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : nc_code=%d\n",__func__, __LINE__,nc_code);
    if(key_code == BTN_CURSOR_RIGHT || key_code == BTN_SELECT)
    {
    	_fac_set_burning_mode((UINT8)nc_code);
    }
    return 0;
}

static UINT32 inx_fac_sw_info_page_tftps_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    
    nav_fac_number_to_string(b_inx_at_tftps_enable, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    printf("%s().%d b_inx_at_tftps_enable=%d\n",__func__,__LINE__,b_inx_at_tftps_enable);
    return b_inx_at_tftps_enable;
}

static BOOL inx_fac_sw_info_page_tftps_key_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : nc_code=%d\n",__func__, __LINE__,nc_code);
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
    {
        b_inx_at_tftps_enable = nc_code;
        if(b_inx_at_tftps_enable)
        {
            a_cfg_cust_pthread_tftps_create();
        }else{
            a_cfg_cust_pthread_tftps_cancel();
        }
    }
    return 0;
}

/* G var */
UTF16_T  inx_fac_sw_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'S','W',' ','I','N','F', 'O', '\0'},//For PD Use
    { 'S','W',' ','I','N','F', 'O', '\0'},//For Factory Use
};

inx_page_entry inx_fac_sw_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_SW_INFO_PAGE_FACTORY_VER, MLM_FAC_KEY_MSG_BUILD_TIME,{0,0}, inx_fac_sw_info_page_factory_ver_content, NULL},
        {NAV_INX_FAC_SW_INFO_PAGE_INX_MBOOT_BUILD_TIME, MLM_FAC_KEY_MSG_INX_MBOOT_BUILD_TIME,{0,0}, inx_fac_sw_info_page_inx_mboot_ver_content, NULL},
        {NAV_INX_FAC_SW_INFO_PAGE_DEMO_FILE, MLM_FAC_KEY_MSG_DEMO_VER,{0,0}, inx_fac_sw_info_page_demo_ver_content, NULL},
        {NAV_INX_FAC_SW_INFO_PAGE_TCON_VER, MLM_FAC_KEY_MSG_TCON_VER,{0,0}, inx_fac_sw_info_page_tcon_ver_content, NULL},
        {NAV_INX_FAC_SW_INFO_PAGE_GAMMA_BIN_VER, MLM_FAC_KEY_MSG_GAMMA_BIN_VER,{0,0}, inx_fac_sw_info_page_gamma_bin_ver_content, NULL},
        {NAV_INX_FAC_SW_INFO_PAGE_FACTORY_RESET, MLM_FAC_KEY_MSG_FACTORY_RESET,{0,0}, inx_fac_sw_info_page_factory_reset_content, inx_fac_sw_info_page_factory_reset_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_FACTORY_RESET_EX, MLM_FAC_KEY_MSG_FACTORY_RESET_EX,{0,0}, inx_fac_sw_info_page_factory_reset_ex_content, inx_fac_sw_info_page_factory_reset_ex_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_DEBUG_FLAG, MLM_FAC_KEY_MSG_DEBUG_FLAG,{0,1}, inx_fac_sw_info_page_debug_flag_content, inx_fac_sw_info_page_debug_flag_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_AT_CMD_LOG_EN, MLM_FAC_KEY_MSG_AT_CMD_LOG_EN,{0,1}, inx_fac_sw_info_page_at_cmd_log_en_content, inx_fac_sw_info_page_at_cmd_log_en_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_AT_CMD_LOG_CP, MLM_FAC_KEY_MSG_AT_CMD_LOG_CP,{0,1}, inx_fac_sw_info_page_at_cmd_log_cp_content, inx_fac_sw_info_page_at_cmd_log_cp_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_AT_CMD_LOG_DEL, MLM_FAC_KEY_MSG_AT_CMD_LOG_DEL,{0,1}, inx_fac_sw_info_page_at_cmd_log_del_content, inx_fac_sw_info_page_at_cmd_log_del_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_EEP_INIT, MLM_FAC_KEY_MSG_EEP_INIT,{0,1}, inx_fac_sw_info_page_eep_init_content, inx_fac_sw_info_page_eep_init_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_BURN_IN, MLM_FAC_KEY_MSG_BURN_IN,{0,1}, inx_fac_sw_info_page_burn_in_content, inx_fac_sw_info_page_burn_in_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_TFTPS, MLM_FAC_KEY_MSG_TFTPS,{0,1}, inx_fac_sw_info_page_tftps_content, inx_fac_sw_info_page_tftps_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        //{NAV_INX_FAC_SW_INFO_PAGE_FACTORY_VER, MLM_FAC_KEY_MSG_BUILD_TIME,{0,0}, inx_fac_sw_info_page_factory_ver_content, NULL},
        //{NAV_INX_FAC_SW_INFO_PAGE_DEMO_FILE, MLM_FAC_KEY_MSG_DEMO_VER,{0,0}, inx_fac_sw_info_page_demo_ver_content, NULL},
        //{NAV_INX_FAC_SW_INFO_PAGE_TCON_VER, MLM_FAC_KEY_MSG_TCON_VER,{0,0}, inx_fac_sw_info_page_tcon_ver_content, NULL},
        {NAV_INX_FAC_SW_INFO_PAGE_FACTORY_RESET, MLM_FAC_KEY_MSG_FACTORY_RESET,{0,0}, inx_fac_sw_info_page_factory_reset_content, inx_fac_sw_info_page_factory_reset_handle},
        //{NAV_INX_FAC_SW_INFO_PAGE_DEBUG_FLAG, MLM_FAC_KEY_MSG_DEBUG_FLAG,{0,1}, inx_fac_sw_info_page_debug_flag_content, inx_fac_sw_info_page_debug_flag_key_handle},
        {NAV_INX_FAC_SW_INFO_PAGE_EEP_INIT, MLM_FAC_KEY_MSG_EEP_INIT,{0,1}, inx_fac_sw_info_page_eep_init_content, inx_fac_sw_info_page_eep_init_key_handle},
        //{NAV_INX_FAC_SW_INFO_PAGE_BURN_IN, MLM_FAC_KEY_MSG_BURN_IN,{0,1}, inx_fac_sw_info_page_burn_in_content, inx_fac_sw_info_page_burn_in_key_handle},
        //{NAV_INX_FAC_SW_INFO_PAGE_TFTPS, MLM_FAC_KEY_MSG_TFTPS,{0,1}, inx_fac_sw_info_page_tftps_content, inx_fac_sw_info_page_tftps_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


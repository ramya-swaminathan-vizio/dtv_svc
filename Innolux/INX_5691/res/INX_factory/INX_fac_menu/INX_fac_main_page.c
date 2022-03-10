#include "INX_fac_main_page.h"
#include "INX_fac_main_page_res.h"

#define MAX_PANEL_NUM 128

static int max_model_index = 0;

/* function */
static UINT32 inx_fac_main_page_build_type_content(UTF16_T* content)
{
    const CHAR *s_tmp_str = AT_VERSION;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}
static UINT32 inx_fac_main_page_qre_content(UTF16_T* content)
{
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
#ifdef INX_ENABLE_QRE
    s_tmp_str = "Yes";
#else
    s_tmp_str = "No";
#endif
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
	return 0;
}

static UINT32 inx_fac_main_page_signed_content(UTF16_T* content)
{
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	
#if 0 //not applicable for mtk build qre
    char * ui1_sleep_password=NULL;
    ui1_sleep_password = a_cfg_cust_info_get_all_ini_item_value("/basic/3rd_ini/dialserver/dial_app_config.ini","System","sleep_password");
    if( ui1_sleep_password!=NULL && !c_strcmp(ui1_sleep_password,"Test") )//find sleep_password=Test
        s_tmp_str = "Yes";
    else
        s_tmp_str = "No";
#else
    const CHAR *s_at_version = AT_VERSION;
    const CHAR *s_fw_version = sys_cust_get_cust_serial();
    //DBG_LOG_PRINT(("%s().%d at=%s, fw=%s\n",__func__, __LINE__, s_at_version, s_fw_version));
    // signed code judgement: mtk build & "_mtk" is absent in fw version 
    if( c_strcmp(s_at_version, "MTK_release")==0 && c_strstr(s_fw_version, "_mtk")==NULL )
        s_tmp_str = "Yes";
    else
        s_tmp_str = "No";
    
#endif

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content,w2s_menu_item_string);
	return 0;
}

static UINT32 inx_fac_main_page_fw_ver_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    const CHAR*         s_tmp_str;
    //size_t              ui1_str_len = 0;
    s_tmp_str = sys_cust_get_cust_serial();
    c_uc_ps_to_w2s(s_tmp_str,w2s_menu_item_string,(NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_main_page_vizio_os_ver_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    const CHAR         s_tmp_str[64]={0};

    INX_get_vizio_os_ver(s_tmp_str);
    c_uc_ps_to_w2s(s_tmp_str,w2s_menu_item_string,(NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_main_page_sn_content(UTF16_T* content)
{
#if 1 //truedano
    UINT32    ui4_read_byte = 0;
    CHAR     s_sn_str[16]={0};
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    
    c_memset(s_sn_str,0,sizeof(CHAR)*16);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    a_cfg_eep_raw_read( EEP_SERIAL_NUMBER,
                        s_sn_str,
                        15,
                        &ui4_read_byte);
    c_uc_ps_to_w2s((const CHAR*)s_sn_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
#else
    CHAR    str_sn[16] = {0};
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT32  ui4_buff_len = sizeof(str_sn);
    
    a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
    c_uc_ps_to_w2s((const CHAR*)str_sn, w2s_menu_item_string, sizeof(str_sn));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
#endif
    return 0;
}

static UINT32 inx_fac_main_page_model_name_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR inx_model_name[32] = {0};
    CHAR str_attr_name[32] = {0};
    UINT32 tmp_model_index;
    UINT8 ui1_status = 0;
    UINT32  ui4_read;

    // modified to show the model name of current setting index, zlhuang, 20210610
    //a_cfg_custom_get_model_name(inx_model_name);
    a_cfg_custom_get_model_index(&tmp_model_index);
    c_snprintf(str_attr_name, 32, "innolux_modelName%d", tmp_model_index);
    a_cfg_cust_info_get_ini_item_string("/config/panel_name.ini", "panel_name", str_attr_name, "", inx_model_name, 32);
    DBG_LOG_PRINT(("%s=%s\n", str_attr_name, inx_model_name));    
    // check the invalid model    
    if(strlen(inx_model_name)==0)
    {
        c_strcpy(inx_model_name, "INVALID MODEL !!!");
    }
    else{
        a_cfg_eep_raw_read(EEP_EMMC_BIN_TEST_FLAG, &ui1_status, 1, &ui4_read);
        if(ui1_status == 1)
            strcat(inx_model_name,"_T");
    }

    c_uc_ps_to_w2s(inx_model_name,w2s_menu_item_string,(NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_main_page_brand_content(UTF16_T* content)
{
    c_uc_w2s_strcpy(content, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BRAND_NAME));
    return 0;
}

static UINT32 inx_fac_main_page_model_index_content(UTF16_T* content)
{
    UINT32 tmp_model_index;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    // just get value once
    if(max_model_index == 0)
    {
        // modified to get the last index, zlhuang, 20210609
        //max_model_index = a_cfg_cust_info_get_ini_item_integer("/config/panel_name.ini","panel_name", "innolux_panelNum", 0);
        char str_model_name_attr[32]={0};
        char str_model_name_value[32]={0};
        for(int idx=1; idx<=MAX_PANEL_NUM; idx++)
        {
            c_snprintf(str_model_name_attr, 32, "innolux_modelName%d", idx);
            a_cfg_cust_info_get_ini_item_string("/config/panel_name.ini", "panel_name", str_model_name_attr, "", str_model_name_value, 32);
            //DBG_LOG_PRINT(("%s=%s\n", str_model_name_attr, str_model_name_value));
            if(strlen(str_model_name_value)>0)
            {
                max_model_index=idx;
            }
        }
        DBG_LOG_PRINT(("%s(),%d max_model_index=%d\n",__func__, __LINE__, max_model_index));
    }

    
    a_cfg_custom_get_model_index(&tmp_model_index);
    nav_fac_number_to_string(tmp_model_index, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    DBG_LOG_PRINT(("%s().%d tmp_model_index=%d\n",__func__,__LINE__,tmp_model_index));
    return tmp_model_index;
}

static UINT32 inx_fac_main_page_panel_name_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR tmp_panel_name[64]={};
    
    a_cfg_custom_get_cur_panel_name(tmp_panel_name);

    // check the invalid model, zlhuang, 20210609
    if(strlen(tmp_panel_name)==0)
    {
        c_strcpy(tmp_panel_name, "INVALID MODEL !!!");
    }
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tmp_panel_name, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_main_page_inx_panel_id_content(UTF16_T* content)
{

    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR inx_panel_string[32] = {0};
    CHAR str_attr_name[32] = {0};
    UINT32 tmp_model_index;

    // modified to show INX Panel ID of current setting index, zlhuang, 20220104
    //a_cfg_cust_info_get_ini_item_string("/config/model/Customer_1.ini", "panel", "INX_panel_id", "N/A", inx_panel_string, 32);
    //DBG_LOG_PRINT(("%s(), %d, inx_panel_string=%s\n", __func__, __LINE__, inx_panel_string));
    a_cfg_custom_get_model_index(&tmp_model_index);
    c_snprintf(str_attr_name, 32, "innolux_panelInfo%d", tmp_model_index);
    a_cfg_cust_info_get_ini_item_string("/config/panel_name.ini", "panel_name", str_attr_name, "", inx_panel_string, 32);
    DBG_LOG_PRINT(("%s=%s\n", str_attr_name, inx_panel_string));
    if(strlen(inx_panel_string)==0)
    {
        c_strcpy(inx_panel_string, "INVALID MODEL !!!");
    }

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(inx_panel_string, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static BOOL inx_fac_main_page_model_index_key_handle(UINT32 nc_code,UINT32 key_code)
{
    DBG_LOG_PRINT(("%s(),%d nc_code=%lu\n",__func__, __LINE__,nc_code));

    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
    {

		// limit the index selection range
		if(nc_code == 255) // out of lower bound(1); refer to {NAV_INX_FAC_MAIN_PAGE_MODEL_INDEX, MLM_FAC_KEY_MSG_MODEL_INDEX,{1,255}......
		{
			a_cfg_custom_set_model_index(max_model_index);
		}
		
		else if(nc_code > max_model_index) // out of upper bound
		{
			a_cfg_custom_set_model_index(1);			  
		}
		else
		{
			a_cfg_custom_set_model_index(nc_code);
		}

        // repaint UI main page, zlhuang, 20210609
        nav_inx_fac_view_activate(INX_FAC_MENU_MAIN_PAGE);

        
    }
    return TRUE;
}

static UINT32 inx_fac_main_page_sw_info_content(UTF16_T* content)
{
    inx_fac_change_page_content(content);
    return 0;
}

static BOOL inx_fac_main_page_sw_info_key_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
	{
	    DBG_LOG_PRINT(("%s().%d : nc_code=%lu\n",__func__, __LINE__,nc_code));
	    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
	    nav_inx_fac_view_activate(INX_FAC_MENU_SW_INFO_PAGE);
	}
	return 0;
}

static UINT32 inx_fac_main_page_pq_info_content(UTF16_T* content)
{
    inx_fac_change_page_content(content);
    return 0;
}

static BOOL inx_fac_main_page_pq_info_key_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
	{
	    DBG_LOG_PRINT(("%s().%d : nc_code=%lu\n",__func__, __LINE__,nc_code));
	    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
	    nav_inx_fac_view_activate(INX_FAC_MENU_PQ_INFO_PAGE);
	}
	return 0;
}

static UINT32 inx_fac_main_page_aq_info_content(UTF16_T* content)
{
    inx_fac_change_page_content(content);
    return 0;
}

static BOOL inx_fac_main_page_aq_info_key_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
	{
	    DBG_LOG_PRINT(("%s().%d : nc_code=%lu\n",__func__, __LINE__,nc_code));
	    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
	    nav_inx_fac_view_activate(INX_FAC_MENU_AQ_INFO_PAGE);
	}
	return 0;
}

static UINT32 inx_fac_main_page_power_info_content(UTF16_T* content)
{
    inx_fac_change_page_content(content);
    return 0;
}

static BOOL inx_fac_main_page_power_info_key_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
	{
	    DBG_LOG_PRINT(("%s().%d : nc_code=%lu\n",__func__, __LINE__,nc_code));
	    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
	    nav_inx_fac_view_activate(INX_FAC_MENU_POWER_INFO_PAGE);
	}
	return 0;
}

static UINT32 inx_fac_main_page_inx_tools_content(UTF16_T* content)
{
    inx_fac_change_page_content(content);
    return 0;
}

static BOOL inx_fac_main_page_inx_tools_key_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
	{
	    DBG_LOG_PRINT(("%s().%d : nc_code=%lu\n",__func__, __LINE__,nc_code));
	    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
	    nav_inx_fac_view_activate(INX_FAC_MENU_INX_TOOLS_PAGE);
	}
	return 0;
}

static UINT32 inx_fac_main_page_more_content(UTF16_T* content)
{
    inx_fac_change_page_content(content);
    return 0;
}

static BOOL inx_fac_main_page_more_key_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
	{
	    DBG_LOG_PRINT(("%s().%d : nc_code=%lu\n",__func__, __LINE__,nc_code));
	    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
	    nav_inx_fac_view_activate(INX_FAC_MENU_MORE_PAGE);
	}
	return 0;
}

/* G var */
UTF16_T  inx_fac_main_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    {'I','N','X',' ',' ','P', 'D', '\0'},//For PD Use
    {'I','N','X',' ',' ','F', 'A', 'C', 'T', 'O', 'R', 'Y', '\0'},//For Factory Use
};

inx_page_entry inx_fac_main_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_MAIN_PAGE_BRAND, MLM_FAC_KEY_MSG_BRAND,{0,0}, inx_fac_main_page_brand_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_VER, MLM_FAC_KEY_MSG_BUILD_TYPE,{0,0}, inx_fac_main_page_build_type_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_QRE, MLM_FAC_KEY_MSG_INX_QRE,{0,0}, inx_fac_main_page_qre_content, NULL},    
        {NAV_INX_FAC_MAIN_PAGE_SIGNED, MLM_FAC_KEY_MSG_SIGNED,{0,0}, inx_fac_main_page_signed_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_FW_VER, MLM_FAC_KEY_MSG_FW_VER,{0,0}, inx_fac_main_page_fw_ver_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_VIZIO_OS_VER, MLM_FAC_KEY_MSG_VIZIO_OS_VER,{0,0}, inx_fac_main_page_vizio_os_ver_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_SN, MLM_FAC_KEY_MSG_SN, {0,0}, inx_fac_main_page_sn_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_MODEL_NAME, MLM_FAC_KEY_MSG_MODEL_NAME, {0,0}, inx_fac_main_page_model_name_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_MODEL_INDEX, MLM_FAC_KEY_MSG_MODEL_INDEX,{1,255}, inx_fac_main_page_model_index_content, inx_fac_main_page_model_index_key_handle},
        {NAV_INX_FAC_MAIN_PAGE_PANEL_NAME, MLM_FAC_KEY_MSG_PANEL_NAME, {0,0}, inx_fac_main_page_panel_name_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_INX_PANEL_ID, MLM_FAC_KEY_MSG_INX_PANEL_ID, {0,0}, inx_fac_main_page_inx_panel_id_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_SW_INFO, MLM_FAC_KEY_MSG_SW_INFO,{0,0}, inx_fac_main_page_sw_info_content, inx_fac_main_page_sw_info_key_handle},
        {NAV_INX_FAC_MAIN_PAGE_PQ_INFO, MLM_FAC_KEY_MSG_PQ_INFO,{0,0}, inx_fac_main_page_pq_info_content, inx_fac_main_page_pq_info_key_handle},
        {NAV_INX_FAC_MAIN_PAGE_AQ_INFO, MLM_FAC_KEY_MSG_AQ_INFO,{0,0}, inx_fac_main_page_aq_info_content, inx_fac_main_page_aq_info_key_handle},    
        {NAV_INX_FAC_MAIN_PAGE_POWER_INFO, MLM_FAC_KEY_MSG_POWER_INFO,{0,0}, inx_fac_main_page_power_info_content, inx_fac_main_page_power_info_key_handle},    
        {NAV_INX_FAC_MAIN_PAGE_INX_TOOLS, MLM_FAC_KEY_MSG_INX_TOOLS,{0,0}, inx_fac_main_page_inx_tools_content, inx_fac_main_page_inx_tools_key_handle},
        {NAV_INX_FAC_MAIN_PAGE_MORE, MLM_FAC_KEY_MSG_MORE,{0,0}, inx_fac_main_page_more_content, inx_fac_main_page_more_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_MAIN_PAGE_BRAND, MLM_FAC_KEY_MSG_BRAND,{0,0}, inx_fac_main_page_brand_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_VER, MLM_FAC_KEY_MSG_BUILD_TYPE,{0,0}, inx_fac_main_page_build_type_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_QRE, MLM_FAC_KEY_MSG_INX_QRE,{0,0}, inx_fac_main_page_qre_content, NULL},    
        {NAV_INX_FAC_MAIN_PAGE_SIGNED, MLM_FAC_KEY_MSG_SIGNED,{0,0}, inx_fac_main_page_signed_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_FW_VER, MLM_FAC_KEY_MSG_FW_VER,{0,0}, inx_fac_main_page_fw_ver_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_VIZIO_OS_VER, MLM_FAC_KEY_MSG_VIZIO_OS_VER,{0,0}, inx_fac_main_page_vizio_os_ver_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_SN, MLM_FAC_KEY_MSG_SN, {0,0}, inx_fac_main_page_sn_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_MODEL_NAME, MLM_FAC_KEY_MSG_MODEL_NAME, {0,0}, inx_fac_main_page_model_name_content, NULL},
        //{NAV_INX_FAC_MAIN_PAGE_MODEL_INDEX, MLM_FAC_KEY_MSG_MODEL_INDEX,{0,255}, inx_fac_main_page_model_index_content, inx_fac_main_page_model_index_key_handle},
        {NAV_INX_FAC_MAIN_PAGE_PANEL_NAME, MLM_FAC_KEY_MSG_PANEL_NAME, {0,0}, inx_fac_main_page_panel_name_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_INX_PANEL_ID, MLM_FAC_KEY_MSG_INX_PANEL_ID, {0,0}, inx_fac_main_page_inx_panel_id_content, NULL},
        {NAV_INX_FAC_MAIN_PAGE_SW_INFO, MLM_FAC_KEY_MSG_SW_INFO,{0,0}, inx_fac_main_page_sw_info_content, inx_fac_main_page_sw_info_key_handle},
        //{NAV_INX_FAC_MAIN_PAGE_PQ_INFO, MLM_FAC_KEY_MSG_PQ_INFO,{0,0}, inx_fac_main_page_pq_info_content, inx_fac_main_page_pq_info_key_handle},
        //{NAV_INX_FAC_MAIN_PAGE_AQ_INFO, MLM_FAC_KEY_MSG_AQ_INFO,{0,0}, inx_fac_main_page_aq_info_content, inx_fac_main_page_aq_info_key_handle},    
        //{NAV_INX_FAC_MAIN_PAGE_POWER_INFO, MLM_FAC_KEY_MSG_POWER_INFO,{0,0}, inx_fac_main_page_power_info_content, inx_fac_main_page_power_info_key_handle},    
        {NAV_INX_FAC_MAIN_PAGE_INX_TOOLS, MLM_FAC_KEY_MSG_INX_TOOLS,{0,0}, inx_fac_main_page_inx_tools_content, inx_fac_main_page_inx_tools_key_handle},
        //{NAV_INX_FAC_MAIN_PAGE_MORE, MLM_FAC_KEY_MSG_MORE,{0,0}, inx_fac_main_page_more_content, inx_fac_main_page_more_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


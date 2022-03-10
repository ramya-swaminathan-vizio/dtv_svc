#include "INX_fac_power_info_page.h"
#include "INX_fac_main_page_res.h"

/*parameter*/

/* function */
static UINT32 inx_fac_power_info_page_power_ver_content(UTF16_T* content)
{
    //UINT32 tmp_model_index;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	CHAR panel_ini_path[256] = {0};
	CHAR power_version[32] = {0};

	a_cfg_cust_info_get_ini_item_string("/config/model/Customer_1.ini", "panel", "m_pPanelName", "", panel_ini_path, sizeof(panel_ini_path));
	if (strlen(panel_ini_path) > 0)
	{	
		a_cfg_cust_info_get_ini_item_string(panel_ini_path, "panel", "InxPowerVersion", "N/A", power_version, sizeof(power_version));
	}
    
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(power_version, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

/* G var */
UTF16_T  inx_fac_power_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'P','O','W','E', 'R', ' ', 'I', 'N', 'F','O', '\0'},//For PD Use
    { 'P','O','W','E', 'R', ' ', 'I', 'N', 'F','O', '\0'},//For Factory Use
};

inx_page_entry inx_fac_power_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_POWER_INFO_PAGE_POWER_VER, MLM_FAC_KEY_MSG_POWER_VER,{0,0}, inx_fac_power_info_page_power_ver_content, NULL},
        //{NAV_INX_FAC_POWER_INFO_PAGE_GET_LED_INFO, MLM_FAC_KEY_MSG_GET_LED_DRIVER_INFO,{0,0}, inx_fac_power_info_page_get_led_info_content, inx_fac_power_info_page_get_led_info_key_handle},
        //{NAV_INX_FAC_POWER_INFO_PAGE_FACTORY_RESET, MLM_FAC_KEY_MSG_RESET,{0,1}, inx_fac_power_info_page_factory_reset_content, inx_fac_power_info_page_factory_reset_handle},
        //{NAV_INX_FAC_POWER_INFO_PAGE_MODEL_INDEX, MLM_FAC_KEY_MSG_MODEL_INDEX,{0,255}, inx_fac_power_info_page_model_index_content, inx_fac_power_info_page_model_index_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_POWER_INFO_PAGE_POWER_VER, MLM_FAC_KEY_MSG_POWER_VER,{0,0}, inx_fac_power_info_page_power_ver_content, NULL},
        //{NAV_INX_FAC_POWER_INFO_PAGE_GET_LED_INFO, MLM_FAC_KEY_MSG_GET_LED_DRIVER_INFO,{0,0}, inx_fac_power_info_page_get_led_info_content, inx_fac_power_info_page_get_led_info_key_handle},
        //{NAV_INX_FAC_POWER_INFO_PAGE_FACTORY_RESET, MLM_FAC_KEY_MSG_RESET,{0,1}, inx_fac_power_info_page_factory_reset_content, inx_fac_power_info_page_factory_reset_handle},
        //{NAV_INX_FAC_POWER_INFO_PAGE_MODEL_INDEX, MLM_FAC_KEY_MSG_MODEL_INDEX,{0,255}, inx_fac_power_info_page_model_index_content, inx_fac_power_info_page_model_index_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


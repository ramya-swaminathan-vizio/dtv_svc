#include "INX_fac_aq_info_page.h"
#include "INX_fac_main_page_res.h"

/*parameter*/
BOOL b_nav_fac_aq_bypass_on_off;

/* function */
static UINT32 inx_fac_aq_info_page_aq_ver_content(UTF16_T* content)
{
    CHAR s_ver[32]={0};
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	a_cfg_cust_info_get_ini_item_string("/config/aq/ini_version.ini", "TOTAL","Total_version", "Unknown", s_ver, 32);
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_ver, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_aq_info_page_aq_bypass_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    nav_fac_number_to_string(b_nav_fac_aq_bypass_on_off, w2s_menu_item_string);
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    printf("%s().%d b_nav_fac_aq_bypass_on_off=%d\n",__func__,__LINE__,b_nav_fac_aq_bypass_on_off);
    return b_nav_fac_aq_bypass_on_off;
}

static BOOL inx_fac_aq_info_page_aq_bypass_key_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s().%d : nc_code=%d\n",__func__, __LINE__,nc_code);
    b_nav_fac_aq_bypass_on_off = nc_code;
    if(b_nav_fac_aq_bypass_on_off)//joe.zy
    {
        acfg_cust_audio_enable_srs_bypass_mode(1);
    }
    else
    {
        acfg_cust_audio_enable_srs_bypass_mode(0);
    }
	return 0;
}

/* G var */
UTF16_T  inx_fac_aq_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'A','Q',' ','I', 'N', 'F', 'O', '\0'},//For PD Use
    { 'A','Q',' ','I', 'N', 'F', 'O', '\0'},//For Factory Use
};

inx_page_entry inx_fac_aq_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_AQ_INFO_PAGE_AQ_VER, MLM_FAC_KEY_MSG_AQ_VER,{0,0}, inx_fac_aq_info_page_aq_ver_content, NULL},
        {NAV_INX_FAC_AQ_INFO_PAGE_AQ_BYPASS, MLM_FAC_KEY_MSG_AQ_BYPASS,{0,1}, inx_fac_aq_info_page_aq_bypass_content, inx_fac_aq_info_page_aq_bypass_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_AQ_INFO_PAGE_AQ_VER, MLM_FAC_KEY_MSG_AQ_VER,{0,0}, inx_fac_aq_info_page_aq_ver_content, NULL},
        {NAV_INX_FAC_AQ_INFO_PAGE_AQ_BYPASS, MLM_FAC_KEY_MSG_AQ_BYPASS,{0,1}, inx_fac_aq_info_page_aq_bypass_content, inx_fac_aq_info_page_aq_bypass_key_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


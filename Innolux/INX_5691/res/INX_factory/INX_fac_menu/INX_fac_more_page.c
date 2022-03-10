#include "INX_fac_more_page.h"
#include "INX_fac_main_page_res.h"

/*parameter*/

/* function */

static UINT32 inx_fac_more_page_earc_mute_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
	INT16 i4_val = 0;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    i4_val = acfg_cust_audio_get_earc_mute( );
	if(i4_val == 0)
     	s_tmp_str = "OFF";
    else
   		s_tmp_str = "ON";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i4_val;
}

static UINT32 inx_fac_more_page_earc_word_len_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
	INT16 i4_val = 0;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    i4_val = acfg_cust_audio_get_earc_word_length();
	if(i4_val == 0)
		s_tmp_str = "16Bit";
    else
        s_tmp_str = "24Bit";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i4_val;
}

static UINT32 inx_fac_more_page_earc_layout_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
	INT16 i4_val = 0;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    i4_val = acfg_cust_audio_get_earc_layout();
	if(i4_val == 0)
		s_tmp_str = "A";
    else
        s_tmp_str = "B";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return i4_val;
}

static BOOL inx_fac_more_page_earc_mute_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
		acfg_cust_audio_set_earc_mute(nc_code); 
	return 0;
}

static BOOL inx_fac_more_page_earc_word_len_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
	{
		if(nc_code == 0)
            acfg_cust_audio_set_earc_mute(SCC_AUD_EARC_PCM_16_BIT);
        else
            acfg_cust_audio_set_earc_mute(1);  //yshu : set earc word length 24 bit 
	}	
	return 0;
}

static BOOL inx_fac_more_page_earc_layout_handle(UINT32 nc_code,UINT32 key_code)
{
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT)
		acfg_cust_audio_set_earc_layout(nc_code);
	return 0;
}


/* G var */
UTF16_T  inx_fac_more_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'M','O','R','E', '\0'},//For PD Use
    { 'M','O','R','E', '\0'},//For Factory Use
};

inx_page_entry inx_fac_more_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_MORE_PAGE_EARC_MUTE, MLM_FAC_KEY_MSG_EARC_MUTE, {0,1}, inx_fac_more_page_earc_mute_content, inx_fac_more_page_earc_mute_handle},
        {NAV_INX_FAC_MORE_PAGE_EARC_WORD_LEN, MLM_FAC_KEY_MSG_EARC_WORD_LEN, {0,1}, inx_fac_more_page_earc_word_len_content, inx_fac_more_page_earc_word_len_handle},
        {NAV_INX_FAC_MORE_PAGE_EARC_LAYOUT, MLM_FAC_KEY_MSG_EARC_LAYOUT, {0,1}, inx_fac_more_page_earc_layout_content, inx_fac_more_page_earc_layout_handle}, 
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_MORE_PAGE_EARC_MUTE, MLM_FAC_KEY_MSG_EARC_MUTE, {0,1}, inx_fac_more_page_earc_mute_content, inx_fac_more_page_earc_mute_handle},
        {NAV_INX_FAC_MORE_PAGE_EARC_WORD_LEN, MLM_FAC_KEY_MSG_EARC_WORD_LEN, {0,1}, inx_fac_more_page_earc_word_len_content, inx_fac_more_page_earc_word_len_handle},
        {NAV_INX_FAC_MORE_PAGE_EARC_LAYOUT, MLM_FAC_KEY_MSG_EARC_LAYOUT, {0,1}, inx_fac_more_page_earc_layout_content, inx_fac_more_page_earc_layout_handle}, 
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


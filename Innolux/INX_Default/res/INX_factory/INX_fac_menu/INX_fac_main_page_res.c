#include "INX_fac_main_page.h"
#include "INX_fac_sw_info_page.h"
#include "INX_fac_pq_info_page.h"
#include "INX_fac_aq_info_page.h"
#include "INX_fac_power_info_page.h"
#include "INX_fac_inx_tools_page.h"
#include "INX_fac_more_page.h"
#include "INX_fac_main_page_res.h"

extern UINT8 inx_at_ui_switch;

/*main page*/
extern UTF16_T  inx_fac_main_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_main_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

/*sw info page*/
extern UTF16_T  inx_fac_sw_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_sw_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

/*pq info page*/
extern UTF16_T  inx_fac_pq_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_pq_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

/*aq info page*/
extern UTF16_T  inx_fac_aq_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_aq_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

/*power info page*/
extern UTF16_T  inx_fac_power_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_power_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

/*power info page*/
extern UTF16_T  inx_fac_inx_tools_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_inx_tools_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

/*more page*/
extern UTF16_T  inx_fac_more_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS];
extern inx_page_entry inx_fac_more_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT];

inx_fac_menu_page t_g_nav_fac_items[INX_FAC_PAGE_MAX+1] = {
    {
        NULL_HANDLE,
        inx_fac_main_page_title,
        inx_fac_main_page_entry,
        NAV_INX_FAC_MAIN_PAGE_MAX,
        0,
        NULL,
    },
    {
        NULL_HANDLE,
        inx_fac_sw_info_page_title,
        inx_fac_sw_info_page_entry,
        NAV_INX_FAC_SW_INFO_PAGE_MAX,
        0,
        NULL,
    },
    {
        NULL_HANDLE,
        inx_fac_pq_info_page_title,
        inx_fac_pq_info_page_entry,
        NAV_INX_FAC_PQ_INFO_PAGE_MAX,
        0,
        NULL,
    },
    {
        NULL_HANDLE,
        inx_fac_aq_info_page_title,
        inx_fac_aq_info_page_entry,
        NAV_INX_FAC_AQ_INFO_PAGE_MAX,
        0,
        NULL,
    },
    {
        NULL_HANDLE,
        inx_fac_power_info_page_title,
        inx_fac_power_info_page_entry,
        NAV_INX_FAC_POWER_INFO_PAGE_MAX,
        0,
        NULL,
    },
    {
        NULL_HANDLE,
        inx_fac_inx_tools_page_title,
        inx_fac_inx_tools_page_entry,
        NAV_INX_FAC_INX_TOOLS_PAGE_MAX,
        0,
        NULL,
    },
    ///////////////////////////////////////////////////////
    {
        NULL_HANDLE,
        inx_fac_more_page_title,
        inx_fac_more_page_entry,
        NAV_INX_FAC_MORE_PAGE_MAX,
        0,
        NULL,
    },
};

UINT16 ui16_fac_view_idx=0;
UINT16 ui16_fac_view_idx_back=0;

/*function*/
void inx_fac_change_page_content(UTF16_T* content)
{
    const CHAR *s_tmp_str = ">>>>>";
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
}

UINT16 inx_fac_items_get_entry_num(void)
{
    int entry_num;
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    
    for(entry_num=0;entry_num<INX_FAC_MENU_ITEM_CNT;entry_num++)
    {
        if(page_entry[entry_num].entry_index == INX_FAC_MENU_ITEM_END)
            break;
    }
    t_g_nav_fac_items[ui16_fac_view_idx].entry_num = entry_num;
    return t_g_nav_fac_items[ui16_fac_view_idx].entry_num;
}

UTF16_T* inx_fac_items_get_page_tile(void)
{
    return t_g_nav_fac_items[ui16_fac_view_idx].page_tile+inx_at_ui_switch*INX_FAC_MENU_TITLE_LENS;
}

BOOL inx_fac_items_check_entry_content(UINT16 ui2_idx)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    if(page_entry[ui2_idx].entry_content)
        return TRUE;
    else
        return FALSE;
}

UINT32 inx_fac_items_exec_entry_content(UTF16_T* w2s_menu_item_string, UINT16 ui2_idx)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    return page_entry[ui2_idx].entry_content(w2s_menu_item_string);
}

UINT16 inx_fac_items_get_entry_mlm(UINT16 ui2_idx)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    return page_entry[ui2_idx].entry_MLM;
}

UINT16 inx_fac_items_get_view_idx(void)
{
    return ui16_fac_view_idx;
}

void inx_fac_items_set_view_idx(UINT16 ui2_idx)
{
    ui16_fac_view_idx = ui2_idx;
}

UINT16 inx_fac_items_get_view_idx_back(void)
{
    return ui16_fac_view_idx_back;
}

void inx_fac_items_set_view_idx_back(UINT16 ui2_idx)
{
    ui16_fac_view_idx_back = ui2_idx;
}

UINT32 inx_fac_items_get_min(UINT16 ui2_idx)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    return page_entry[ui2_idx].range.min;
}

UINT32 inx_fac_items_get_max(UINT16 ui2_idx)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    return page_entry[ui2_idx].range.max;
}

BOOL inx_fac_items_check_entry_callback(UINT16 ui2_idx)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    if(page_entry[ui2_idx].entry_key_callback)
        return TRUE;
    else
        return FALSE;
}

void inx_fac_items_exec_entry_callback(UINT16 ui2_idx,UINT32 _nc_code,UINT32 key_code)
{
    inx_page_entry *page_entry = t_g_nav_fac_items[ui16_fac_view_idx].page_entry;
    page_entry += inx_at_ui_switch*INX_FAC_MENU_ITEM_CNT;
    page_entry[ui2_idx].entry_key_callback(_nc_code,key_code);
}

UINT16 inx_fac_items_get_entry_hlt_idx(void)
{
    return t_g_nav_fac_items[ui16_fac_view_idx].hlt_idx;
}

void inx_fac_items_set_entry_hlt_idx(UINT16 ui2_hlt_idx)
{
    t_g_nav_fac_items[ui16_fac_view_idx].hlt_idx = ui2_hlt_idx;
}


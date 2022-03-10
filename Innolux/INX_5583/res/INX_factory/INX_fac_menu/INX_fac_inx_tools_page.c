#include "INX_fac_inx_tools_page.h"
#include "INX_fac_main_page_res.h"

#define EMMC_BLOCK_DEMO	"/dev/mmcblk0p32"

UINT8 hdcp_status=INX_RET_INIT;
UINT8 hdcp2_status=INX_RET_INIT;
UINT8 hdcp_load_back_status=INX_RET_INIT;
UINT8 hdcp2_load_back_status=INX_RET_INIT;
UINT8 hdcp_backup_status=INX_RET_INIT;
UINT8 hdcp2_backup_status=INX_RET_INIT;
UINT32 ui4_dump_eep_status=INX_RET_INIT;
UINT8 get_bt_rssi_status=INX_DISABLE_MODE;
UINT8 sscg_status=1;
UINT8 clear_demura_partition_status=INX_RET_INIT;
UINT8 demura_reg_status=1;
UINT8 show_panel_border=0;
UINT8 ui1_inx_fac_power_led_light = 15;//LED_light_rate default value is 15

/*parameter*/

/* function */

static UINT32 inx_fac_inx_tools_page_hdcp_burning_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(hdcp_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "hdcp write done";
            break;
        case INX_RET_USB_NOT_FOUND:
            s_tmp_str = "Can't find usb device";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    //s_tmp_str = "Press Ok / Right";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return hdcp_status;
}

static BOOL inx_fac_inx_tools_page_hdcp_burning_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR usb_root_path[128]={0};
    UINT8 hdcp_full_path[128]={0};
    UINT8 hdcp_cert_path[128]={0};
    INT32 get_hdcp_size;
    UINT8 hdcp_key_buffer[INX_HDCP_1_4_SIZE];
    INT32 i4_ret;
    
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
    {
        if( a_cfg_custom_get_mnt_path(usb_root_path) != 0 )
        {
            printf("%s() : get usb path error.\n",__func__);
            hdcp_status = INX_RET_USB_NOT_FOUND;
            return FALSE;
        }
        c_sprintf((char *)hdcp_full_path,"%s/%s",usb_root_path,INX_HDCP_1_4_FILE);
        get_hdcp_size = a_cfg_custom_read_file(hdcp_full_path,hdcp_key_buffer,INX_HDCP_1_4_SIZE);
        if( get_hdcp_size < 0 || get_hdcp_size != sizeof(hdcp_key_buffer) ) {
            printf("%s() : read hdcp file error.\n",__func__);
			return FALSE;
        }
        i4_ret = TEEC_Key2TA(INX_HDCP_1_4_TYPE, INX_HDCP_1_4_ENC, hdcp_key_buffer, INX_HDCP_1_4_SIZE);
        if( i4_ret == 1 )//fail
        {
            printf("%s() : write hdcp TEEC_Key2TA error.\n",__func__);
            return FALSE;
        }
        a_cfg_cust_update_hdcp();
        
        c_sprintf((char *)hdcp_cert_path,"%s/%s",INX_HDCP_PATH,INX_HDCP_1_4_FILE);
        get_hdcp_size = a_cfg_custom_write_file(hdcp_cert_path,hdcp_key_buffer,INX_HDCP_1_4_SIZE);
        if( get_hdcp_size < 0 || get_hdcp_size != sizeof(hdcp_key_buffer) ) {
            printf("%s() : write hdcp file error.\n",__func__);
			return FALSE;
        }
        hdcp_status = INX_RET_SUCCESS;
        nav_fac_view_alert_osd("Success");
        nav_fac_view_alert_osd_timer(5000);
    }  
	return TRUE;
}

static UINT32 inx_fac_inx_tools_page_hdcp2_burning_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(hdcp2_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "hdcp2 write done";
            break;
        case INX_RET_USB_NOT_FOUND:
            s_tmp_str = "Can't find usb device";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    //s_tmp_str = "Press Ok / Right";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return hdcp2_status;
}

static BOOL inx_fac_inx_tools_page_hdcp2_burning_handle(UINT32 nc_code,UINT32 key_code)
{
	CHAR usb_root_path[128]={0};
    UINT8 hdcp_full_path[128]={0};
    UINT8 hdcp_cert_path[128]={0};
    INT32 get_hdcp_size;
    UINT8 hdcp_key_buffer[INX_HDCP_2_2_SIZE];
    INT32 i4_ret;
    
	if(key_code == BTN_SELECT || key_code == BTN_CURSOR_RIGHT)
    {
        if( a_cfg_custom_get_mnt_path(usb_root_path) != 0 )
        {
            printf("%s() : get usb path error.\n",__func__);
            hdcp2_status = INX_RET_USB_NOT_FOUND;
            return FALSE;
        }
        c_sprintf((char *)hdcp_full_path,"%s/%s",usb_root_path,INX_HDCP_2_2_FILE);
        get_hdcp_size = a_cfg_custom_read_file(hdcp_full_path,hdcp_key_buffer,INX_HDCP_2_2_SIZE);
        if( get_hdcp_size < 0 || get_hdcp_size != sizeof(hdcp_key_buffer) ) {
            printf("%s() : read hdcp2 file error.\n",__func__);
			return FALSE;
        }
        i4_ret = TEEC_Key2TA(INX_HDCP_2_2_TYPE, INX_HDCP_2_2_ENC, hdcp_key_buffer, INX_HDCP_2_2_SIZE);
        if( i4_ret == 1 )//fail
        {
            printf("%s() : write hdcp2 TEEC_Key2TA error.\n",__func__);
            return FALSE;
        }
        a_cfg_cust_update_hdcp();
        
        c_sprintf((char *)hdcp_cert_path,"%s/%s",INX_HDCP_PATH,INX_HDCP_2_2_FILE);
        get_hdcp_size = a_cfg_custom_write_file(hdcp_cert_path,hdcp_key_buffer,INX_HDCP_2_2_SIZE);
        if( get_hdcp_size < 0 || get_hdcp_size != sizeof(hdcp_key_buffer) ) {
            printf("%s() : write hdcp2 file error.\n",__func__);
			return FALSE;
        }
        hdcp2_status = INX_RET_SUCCESS;
        nav_fac_view_alert_osd("Success");
        nav_fac_view_alert_osd_timer(5000);
    }  
	return TRUE;
}

static UINT32 inx_fac_inx_tools_page_hdcp_check_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT8 hdcp_check = 0;
    
    hdcp_check = a_cfg_custom_factory_check_hdcp1_4();
    if( hdcp_check )
    {
        s_tmp_str = "HDCP 1.4 check ok";
    }
    else
    {
        s_tmp_str = "HDCP 1.4 check fail";
    }
    
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return hdcp_check;
}

static UINT32 inx_fac_inx_tools_page_hdcp2_check_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT8 hdcp_check = 0;
    
    hdcp_check = a_cfg_custom_factory_check_hdcp2_2();
    if( hdcp_check )
    {
        s_tmp_str = "HDCP 2.2 check ok";
    }
    else
    {
        s_tmp_str = "HDCP 2.2 check fail";
    }
    
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return hdcp_check;
}

static UINT32 inx_fac_inx_tools_page_hdcp_load_back_from_tv_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(hdcp_load_back_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "hdcp write done";
            break;
        case INX_RET_FILE_NOT_FOUND:
            s_tmp_str = "File not Found";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return TRUE;
}

static UINT32 inx_fac_inx_tools_page_hdcp2_load_back_from_tv_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(hdcp2_load_back_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "hdcp2 write done";
            break;
        case INX_RET_FILE_NOT_FOUND:
            s_tmp_str = "File not Found";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return TRUE;
}

static UINT32 inx_fac_inx_tools_page_hdcp_backup_to_usb_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(hdcp_backup_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "hdcp write done";
            break;
        case INX_RET_FILE_NOT_FOUND:
            s_tmp_str = "File not Found";
            break;
        case INX_RET_USB_NOT_FOUND:
            s_tmp_str = "USB not Found";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return TRUE;
}

static UINT32 inx_fac_inx_tools_page_hdcp2_backup_to_usb_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(hdcp2_backup_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "hdcp write done";
            break;
        case INX_RET_FILE_NOT_FOUND:
            s_tmp_str = "File not Found";
            break;
        case INX_RET_USB_NOT_FOUND:
            s_tmp_str = "USB not Found";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return TRUE;
}

// Author : ys.hu
// Action : Show option content.
// Return : 
static UINT32 inx_fac_inx_tools_page_demo_update_content(UTF16_T* content)
{
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT32 ui32DemoFileCnt=0;
    DIR *dDirPointer;
    struct dirent *dStruct;
	UINT32 bExistDemo = 0;

	//Count the number of demo file.
    dDirPointer = opendir(DEMO_FILE_PATH);
    if(dDirPointer)
    {
        while ((dStruct = readdir(dDirPointer)) != NULL)
        {
            if( strstr(dStruct->d_name,DEMO_FILE_VICE) )
			{
                ui32DemoFileCnt++;
            }
        }
        closedir(dDirPointer);
    }
	bExistDemo = (ui32DemoFileCnt > 2) ? 1 : 0;
	if(bExistDemo)
    	c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));  
	else
		c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));  
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return bExistDemo;
}

static UINT32 inx_fac_inx_tools_page_dump_eep2usb_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(ui4_dump_eep_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press Ok / Right";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "Dump eep done";
            break;
        case INX_RET_USB_NOT_FOUND:
            s_tmp_str = "Can't find usb device";
            break;
        case INX_RET_SYSTEM_ERROR:
            s_tmp_str = "Exec system fail";
            break;
        default:
            s_tmp_str = "Press Ok / Right";
            break;
    }
    //s_tmp_str = "Press Ok / Right";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return ui4_dump_eep_status;
}

static UINT32 inx_fac_inx_tools_page_get_bt_mac_content(UTF16_T* content)
{
    DBG_LOG_PRINT(("%s,%d\n", __func__, __LINE__));
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT8 ui1_temp[6] = {0};
    UINT8 tmp_buf[64] = {0};
    INT32 i4_ret = 0;


    if (( access("/basic/features/VIZIO_FEATURE_CHIP_MT5583", F_OK) == 0 ) && (a_cfg_cust_Is_CurModel_2021() == TRUE))//MT5583 J series
    {
        c_sprintf(tmp_buf,"N/A");
        if( inx_fac_items_get_inx_at_ui_switch() == INX_AT_SWITCH_PD ){
            _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_INX_TOOLS_PAGE_GET_BT_MAC,FALSE);
        }else{
            _nav_fac_view_menu_list_enable_items(NAV_INX_TO_FAC_INX_TOOLS_PAGE_GET_BT_MAC,FALSE);//for factory
        }
    }else{
        i4_ret = _nav_get_bluetooth_host_mac(ui1_temp);
        if(i4_ret != APP_CFGR_OK)
        {
            printf(("%s(): %d, failed\n", __func__, __LINE__));
        }else{
            c_sprintf(tmp_buf,"%02X:%02X:%02X:%02X:%02X:%02X",
            ui1_temp[0],ui1_temp[1],ui1_temp[2],ui1_temp[3],ui1_temp[4],ui1_temp[5]);
        }
    }

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tmp_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_inx_tools_page_get_bt_rssi_content(UTF16_T* content)
{
	DBG_LOG_PRINT(("%s,%d\n", __func__, __LINE__));
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

	if (( access("/basic/features/VIZIO_FEATURE_CHIP_MT5583", F_OK) == 0 ) && (a_cfg_cust_Is_CurModel_2021() == TRUE))//MT5583 J series
	{
		s_tmp_str = "N/A";        
		if( inx_fac_items_get_inx_at_ui_switch() == INX_AT_SWITCH_PD ){
			_nav_fac_view_menu_list_enable_items(NAV_INX_FAC_INX_TOOLS_PAGE_GET_BT_RSSI,FALSE);
		}else{
			_nav_fac_view_menu_list_enable_items(NAV_INX_TO_FAC_INX_TOOLS_PAGE_GET_BT_RSSI,FALSE);//for factory
		}
	}else{

 		switch (get_bt_rssi_status)
		{
			case INX_DISABLE_MODE:
				s_tmp_str = "Stop";
        			break;
			case INX_ENABLE_MODE:
				s_tmp_str = "Start";
        			break;
			default:
				s_tmp_str = "Stop";
				break;
		}
	}

	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return get_bt_rssi_status;
}


static UINT32 inx_fac_inx_tools_page_sscg_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    switch (sscg_status)
    {
        case 0:
        {
			s_tmp_str = "Off";
        }
        break;

        case 1:
        {
			s_tmp_str = "On";
        }
        break;

        default:
			s_tmp_str = "On";
        break;
    }
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return sscg_status;
}

static UINT32 inx_fac_inx_tools_page_clear_demura_partition_content(UTF16_T* content)
{
#ifdef MT5583_MODEL
    DBG_LOG_PRINT(("%s,%d\n",__func__,__LINE__));
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    s_tmp_str = "N/A";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_INX_TOOLS_PAGE_CLEAR_DEMURA_PARTITION,FALSE);
	return 0;	
#else
    DBG_LOG_PRINT(("%s,%d\n",__func__,__LINE__));
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(clear_demura_partition_status)
    {
        case INX_RET_INIT:
            s_tmp_str = "Press 'OK' to Clear";
            break;
        case INX_RET_SUCCESS:
            s_tmp_str = "Press 'OK' to Reboot";
            break;
        default:
            s_tmp_str = "Press 'OK' to Clear";
            break;
    }
    //s_tmp_str = "Press Ok / Right";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return clear_demura_partition_status;
#endif	
}


static UINT32 inx_fac_inx_tools_page_demura_switch_content(UTF16_T* content)
{
#ifdef MT5583_MODEL
    DBG_LOG_PRINT(("%s, %d\n",__func__,__LINE__));
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
   
    s_tmp_str = "N/A";
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    _nav_fac_view_menu_list_enable_items(NAV_INX_FAC_INX_TOOLS_PAGE_DEMURA_SWITCH,FALSE);
#else
    DBG_LOG_PRINT(("%s, %d\n",__func__,__LINE__));
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT32 regValue=0;
    INT32 i4_ret;
    i4_ret = a_cfg_cust_get_demura(&regValue);
    DBG_LOG_PRINT(("%s(): %d, i4_ret=%d, regValue=0x%X\n", __func__, __LINE__, i4_ret, regValue));
    if(i4_ret !=0){
        s_tmp_str = "N/A";
    }
    else if ((regValue & 0x07) == 0)//Demura R/G/B : bit 2/1/0
    {
        demura_reg_status = 0;
        s_tmp_str = "Disabled";
    }
    else
    {
        demura_reg_status = 1;
        s_tmp_str = "Enabled";
    }
/*
	if (demura_reg_status == 0)
	{
	    s_tmp_str = "Disabled";
    }
    else
    {
        s_tmp_str = "Enabled";
    }
*/
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content, w2s_menu_item_string);
    return demura_reg_status;
#endif	
}


static UINT32 inx_fac_inx_tools_page_show_panel_border_content(UTF16_T* content)
{
    printf("%s,%d\n",__func__,__LINE__);
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch (show_panel_border)
    {
        case 0:
        {
			s_tmp_str = "No";
        }
        break;

        case 1:
        {
			s_tmp_str = "Yes";
        }
        break;

        default:
			s_tmp_str = "No";
        break;
    }
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return show_panel_border;
}

static UINT32 inx_fac_inx_tools_page_power_led_light_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	UINT32 ui4_ret = 0;

	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_number_to_string(ui1_inx_fac_power_led_light, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	ui4_ret = ui1_inx_fac_power_led_light/5;
	return ui4_ret;
}
static BOOL inx_fac_inx_tools_page_hdcp_load_back_from_tv_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR cmd_buf[128]={0};
    FILE *fp=NULL;
    INT32 get_hdcp_size;
    UINT8 hdcp_key_buffer[INX_HDCP_1_4_SIZE];
    int i4_ret;

    //check file exist
    c_sprintf(cmd_buf,"%s/%s",INX_HDCP_PATH,INX_HDCP_1_4_FILE);
    if( access( cmd_buf, R_OK ) == -1 ) {
        printf("%s not found\n",cmd_buf);
        hdcp_load_back_status = INX_RET_FILE_NOT_FOUND;
		return FALSE;
	}

    //cp file
    c_sprintf(cmd_buf,"%s/HDCP14",INX_HDCP_PATH);
    if( access( cmd_buf, R_OK ) == -1 ) {
        inx_system("mkdir %s/HDCP14",INX_HDCP_PATH);
    }
    inx_system("cp -rf %s/%s %s/HDCP14/hdcp_key.bin",INX_HDCP_PATH,INX_HDCP_1_4_FILE,INX_HDCP_PATH);
    
    //write HDCP1.4
    inx_system("sync");
    inx_system("export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/vendor/lib");
    inx_system("/application/InterTACa %s %d",INX_HDCP_1_4_TYPE,INX_HDCP_1_4_ENC);
    inx_system("rm -rf /certificate/HDCP14");

    hdcp_load_back_status = INX_RET_SUCCESS;
    nav_fac_view_alert_osd("Success");
    nav_fac_view_alert_osd_timer(5000);
    return TRUE;
}

static BOOL inx_fac_inx_tools_page_hdcp2_load_back_from_tv_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR cmd_buf[128]={0};

    //check file exist
    c_sprintf(cmd_buf,"%s/%s",INX_HDCP_PATH,INX_HDCP_2_2_FILE);
    if( access( cmd_buf, R_OK ) == -1 ) {
        printf("%s not found\n",cmd_buf);
        hdcp2_load_back_status = INX_RET_FILE_NOT_FOUND;
		return FALSE;
	}

    //cp file
    c_sprintf(cmd_buf,"%s/HDCP2",INX_HDCP_PATH);
    if( access( cmd_buf, R_OK ) == -1 ) {
        inx_system("mkdir %s/HDCP2",INX_HDCP_PATH);
    }
    inx_system("cp -rf %s/%s %s/HDCP2/hdcp2_key_22.bin",INX_HDCP_PATH,INX_HDCP_2_2_FILE,INX_HDCP_PATH);
    
    //write HDCP2.2
    inx_system("sync");
    inx_system("export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/vendor/lib");
    inx_system("/application/InterTACa %s %d",INX_HDCP_2_2_TYPE,INX_HDCP_2_2_ENC);
    inx_system("rm -rf /certificate/HDCP2");

    hdcp2_load_back_status = INX_RET_SUCCESS;
    nav_fac_view_alert_osd("Success");
    nav_fac_view_alert_osd_timer(5000);
    return TRUE;
}

static BOOL inx_fac_inx_tools_page_hdcp_backup_to_usb_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR cmd_buf[128]={0};
    CHAR carrUsbPath[512]={0};
    CHAR inx_model_name[32] = {0};
    UINT32 tmp_model_index;

    //check file exist
    c_sprintf(cmd_buf,"%s/%s",INX_HDCP_PATH,INX_HDCP_1_4_FILE);
    if( access( cmd_buf, R_OK ) == -1 ) {
        printf("%s not found\n",cmd_buf);
        hdcp_backup_status = INX_RET_FILE_NOT_FOUND;
		return FALSE;
	}

    //Chekc Usb
    if( a_cfg_custom_get_mnt_path(carrUsbPath) != RMVR_OK )// Usb not found
    {
        printf("%s() : get usb path error.\n",__func__);
        nav_fac_view_alert_osd("Insert usb disk,please.");
        nav_fac_view_alert_osd_timer(5000);
        hdcp_backup_status = INX_RET_USB_NOT_FOUND;
        return FALSE;
    }

    a_cfg_custom_get_model_name(inx_model_name);
    a_cfg_custom_get_model_index(&tmp_model_index);
    inx_system("cp -rf %s/%s %s/%s_MI%d_%s ; sync ; sync ; sync",INX_HDCP_PATH,INX_HDCP_1_4_FILE,carrUsbPath,inx_model_name,tmp_model_index,INX_HDCP_1_4_FILE);
    printf("copy %s/%s to usb\n",INX_HDCP_PATH,INX_HDCP_1_4_FILE);

    hdcp_backup_status = INX_RET_SUCCESS;
    nav_fac_view_alert_osd("Success");
    nav_fac_view_alert_osd_timer(5000);
    
    return TRUE;
}

static BOOL inx_fac_inx_tools_page_hdcp2_backup_to_usb_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR cmd_buf[128]={0};
    CHAR carrUsbPath[512]={0};
    CHAR inx_model_name[32] = {0};
    UINT32 tmp_model_index;

    //check file exist
    c_sprintf(cmd_buf,"%s/%s",INX_HDCP_PATH,INX_HDCP_2_2_FILE);
    if( access( cmd_buf, R_OK ) == -1 ) {
        printf("%s not found\n",cmd_buf);
        hdcp2_backup_status = INX_RET_FILE_NOT_FOUND;
		return FALSE;
	}

    //Chekc Usb
    if( a_cfg_custom_get_mnt_path(carrUsbPath) != RMVR_OK )// Usb not found
    {
        printf("%s() : get usb path error.\n",__func__);
        nav_fac_view_alert_osd("Insert usb disk,please.");
        nav_fac_view_alert_osd_timer(5000);
        hdcp2_backup_status = INX_RET_USB_NOT_FOUND;
        return FALSE;
    }

    a_cfg_custom_get_model_name(inx_model_name);
    a_cfg_custom_get_model_index(&tmp_model_index);
    inx_system("cp -rf %s/%s %s/%s_MI%d_%s ; sync ; sync ; sync",INX_HDCP_PATH,INX_HDCP_2_2_FILE,carrUsbPath,inx_model_name,tmp_model_index,INX_HDCP_2_2_FILE);
    printf("copy %s/%s to usb\n",INX_HDCP_PATH,INX_HDCP_2_2_FILE);

    hdcp2_backup_status = INX_RET_SUCCESS;
    nav_fac_view_alert_osd("Success");
    nav_fac_view_alert_osd_timer(5000);
    
    return TRUE;
}


static BOOL inx_fac_inx_tools_page_demo_update_handle(UINT32 nc_code,UINT32 key_code)
{

	CHAR carrUsbPath[512]={0};
	CHAR carrFileName[512 + 64] = {0};
	CHAR carrDemoFiles[512] = {0};
	INT32 i4Ret = 0;
	HANDLE_T h_fm_dev;
	CHAR cFname[128]={0};
	CHAR c_Update_demo[256]={0};
	
	
	if( a_cfg_custom_get_mnt_path(carrUsbPath) != 0 )
    {
            printf("%s() : get usb path error.\n",__func__);
            return FALSE;
    }

	//dd demo_file.img to tv.
	c_sprintf(cFname,"%s/demo_file.img",carrUsbPath);
	c_sprintf(c_Update_demo,"dd if=%s of=%s; sync",cFname,EMMC_BLOCK_DEMO);
	//Check demo_file.img exist.
	if( access( cFname, R_OK ) != -1 ) {
        nav_fac_view_alert_osd("Writting demo...");
    	// file exists
    	inx_system(c_Update_demo);
        nav_fac_view_alert_osd("Writting demo done");
        nav_fac_view_alert_osd_timer(5000);
		return TRUE;
	} else {
    	// file doesn't exist
    	printf("%s() : demo_file.img doesn't exist.\n",__func__);
	}

	//copy demo files to tv if demo_file.img doesn't exist.
	c_sprintf(carrFileName,"%s/demo/vizio_demo.txt",carrUsbPath);
	i4Ret = c_fm_open(FM_ROOT_HANDLE,
						   carrFileName,
						   FM_READ_ONLY,
						   0777,
						   FALSE,
						   &h_fm_dev);
	c_sprintf(carrDemoFiles,"cp -f %s/demo/* %s",carrUsbPath,DEMO_FILE_PATH);
	if (i4Ret == FMR_OK)
	{	    
        	nav_fac_view_alert_osd("Writting demo...");
		inx_system("rm -rf /demo/*");
		inx_system("mkdir /demo/retail_demo");
		inx_system(carrDemoFiles);
		inx_system("sync;sync;sync");
        	nav_fac_view_alert_osd("Writting demo done");
        	nav_fac_view_alert_osd_timer(5000);
	}
	
	i4Ret = c_fm_close(h_fm_dev);
	
	return (i4Ret == FMR_OK);
}

static BOOL inx_fac_inx_tools_page_dump_eep2usb_handle(UINT32 nc_code,UINT32 key_code)
{
    ui4_dump_eep_status = a_cfg_custom_dump_eep2usb();
    if( ui4_dump_eep_status == INX_RET_SUCCESS ){
        nav_fac_view_alert_osd("Success");
        nav_fac_view_alert_osd_timer(5000);
    }
    return TRUE;
}


static BOOL inx_fac_inx_tools_page_get_bt_rssi_handle(UINT32 nc_code,UINT32 key_code)
{
    DBG_LOG_PRINT(("%s, %d, nc_code=%lu, key_code=0x%08lX\n",__func__,__LINE__, nc_code, key_code));

    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        get_bt_rssi_status=nc_code;
        nav_fac_view_bt_rssi_osd_flag(get_bt_rssi_status);
    }
    else{
        DBG_LOG_PRINT(("%s, %d, ignore !\n",__func__,__LINE__));	
    }
    return TRUE;
}

static BOOL inx_fac_inx_tools_page_sscg_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s, %d, nc_code=%lu, key_code=0x%08lX\n",__func__,__LINE__, nc_code, key_code);

	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        sscg_status=nc_code;
		a_cfg_cust_set_panel_ssc_en(sscg_status);
		
	}
    else{
	    printf("%s, %d, ignore !\n",__func__,__LINE__);	
    }
    return TRUE;
}

static BOOL inx_fac_inx_tools_page_clear_demura_partition_handle(UINT32 nc_code,UINT32 key_code)
{
#ifdef MT5583_MODEL
    (void)(nc_code);
    (void)(key_code);
    return FALSE;
#else
    DBG_LOG_PRINT(("%s, %d, nc_code=%lu, key_code=0x%08lX\n",__func__,__LINE__, nc_code, key_code));
    if(key_code == BTN_SELECT)
    {
	if(clear_demura_partition_status == INX_RET_INIT)
	{
	    inx_clear_demura_partition();
	    clear_demura_partition_status = INX_RET_SUCCESS;
	}
	else if(clear_demura_partition_status == INX_RET_SUCCESS)
	{
	    clear_demura_partition_status = INX_RET_INIT;
	    a_amb_reboot();
	}
	else
	    DBG_LOG_PRINT(("%s, %d, ignore !\n",__func__,__LINE__));
    }
    else{
	    DBG_LOG_PRINT(("%s, %d, ignore !\n",__func__,__LINE__));
    }
    return TRUE;
#endif	
}


static BOOL inx_fac_inx_tools_page_demura_switch_handle(UINT32 nc_code,UINT32 key_code)
{
#ifdef MT5583_MODEL
    (void)(nc_code);
    (void)(key_code);
    return FALSE;
#else
    DBG_LOG_PRINT(("%s, %d, nc_code=%lu, key_code=0x%08lX\n",__func__,__LINE__, nc_code, key_code));
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        demura_reg_status = nc_code;
        INT32 i4_ret = 0;
        i4_ret = a_cfg_cust_set_demura(demura_reg_status);
        if(i4_ret != 0){
            DBG_LOG_PRINT(("%s, %d, a_cfg_cust_set_demura() fails !\n",__func__,__LINE__));	
        }
    }
    else{
        DBG_LOG_PRINT(("%s, %d, ignore !\n",__func__,__LINE__));	
    }
    return TRUE;
#endif	
}


static BOOL inx_fac_inx_tools_page_show_panel_border_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s, %d, nc_code=%lu, key_code=0x%08lX\n",__func__,__LINE__, nc_code, key_code);

    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        show_panel_border=nc_code;
        INT32 i4_ret = 0;
        i4_ret = INX_nav_fac_dialog_show_panel_border_flag(show_panel_border, 1);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("%s, %d, failed!",__func__,__LINE__));
        }
    }
    else
    {
	    DBG_LOG_PRINT(("%s, %d, ignore!",__func__,__LINE__));
    }
    return TRUE;
}

static BOOL inx_fac_inx_tools_page_power_led_light_handle(UINT32 nc_code,UINT32 key_code)
{
    INT32 i4_ret = 0;
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        ui1_inx_fac_power_led_light = nc_code*5;
        i4_ret = a_cfg_cust_set_LED_light_rate(ui1_inx_fac_power_led_light);
        if(i4_ret < 0)
        {
            DBG_LOG_PRINT(("%s, %d, failed!",__func__,__LINE__));
        }
    }
    else
    {
	    DBG_LOG_PRINT(("%s, %d, ignore!",__func__,__LINE__));
    }
    return TRUE;
}


/* G var */
UTF16_T  inx_fac_inx_tools_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'I','N','X',' ', 'T', 'o', 'o', 'l', 's', '\0'},//For PD Use
    { 'I','N','X',' ', 'T', 'o', 'o', 'l', 's', '\0'},//For Factory Use
};

inx_page_entry inx_fac_inx_tools_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_BURNING, MLM_FAC_KEY_MSG_HDCP_BURNING, {0,0}, inx_fac_inx_tools_page_hdcp_burning_content, inx_fac_inx_tools_page_hdcp_burning_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_BURNING, MLM_FAC_KEY_MSG_HDCP2_BURNING, {0,0}, inx_fac_inx_tools_page_hdcp2_burning_content, inx_fac_inx_tools_page_hdcp2_burning_handle},    
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_CHECK, MLM_FAC_KEY_MSG_HDCP_CHECK, {0,0}, inx_fac_inx_tools_page_hdcp_check_content, NULL},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_CHECK, MLM_FAC_KEY_MSG_HDCP2_CHECK, {0,0}, inx_fac_inx_tools_page_hdcp2_check_content, NULL},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_LOAD_BACK_FROM_TV, MLM_FAC_KEY_MSG_HDCP_LOAD_BACK_FROM_TV, {0,0}, inx_fac_inx_tools_page_hdcp_load_back_from_tv_content, inx_fac_inx_tools_page_hdcp_load_back_from_tv_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_LOAD_BACK_FROM_TV, MLM_FAC_KEY_MSG_HDCP2_LOAD_BACK_FROM_TV, {0,0}, inx_fac_inx_tools_page_hdcp2_load_back_from_tv_content, inx_fac_inx_tools_page_hdcp2_load_back_from_tv_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_BACKUP_TO_USB, MLM_FAC_KEY_MSG_HDCP_BACKUP_TO_USB, {0,0}, inx_fac_inx_tools_page_hdcp_backup_to_usb_content, inx_fac_inx_tools_page_hdcp_backup_to_usb_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_BACKUP_TO_USB, MLM_FAC_KEY_MSG_HDCP2_BACKUP_TO_USB, {0,0}, inx_fac_inx_tools_page_hdcp2_backup_to_usb_content, inx_fac_inx_tools_page_hdcp2_backup_to_usb_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_DEMO_UPDATE, MLM_FAC_KEY_MSG_DEMO_UPDATE, {0,0}, inx_fac_inx_tools_page_demo_update_content, inx_fac_inx_tools_page_demo_update_handle}, //yshu update demo from usb disk.
        {NAV_INX_FAC_INX_TOOLS_PAGE_DUMP_EEP2USB, MLM_FAC_KEY_MSG_DUMP_EEP2USB, {0,0}, inx_fac_inx_tools_page_dump_eep2usb_content, inx_fac_inx_tools_page_dump_eep2usb_handle}, //truedano
        {NAV_INX_FAC_INX_TOOLS_PAGE_GET_BT_MAC, MLM_FAC_KEY_MSG_GET_BT_MAC, {0,0}, inx_fac_inx_tools_page_get_bt_mac_content, NULL},
        {NAV_INX_FAC_INX_TOOLS_PAGE_GET_BT_RSSI, MLM_FAC_KEY_MSG_GET_BT_RSSI, {0,1}, inx_fac_inx_tools_page_get_bt_rssi_content, inx_fac_inx_tools_page_get_bt_rssi_handle}, //zlhuang
        {NAV_INX_FAC_INX_TOOLS_PAGE_SSCG, MLM_FAC_KEY_MSG_SSCG, {0,1}, inx_fac_inx_tools_page_sscg_content, inx_fac_inx_tools_page_sscg_handle}, //zlhuang        
        {NAV_INX_FAC_INX_TOOLS_PAGE_CLEAR_DEMURA_PARTITION, MLM_FAC_KEY_MSG_CLEAR_DEMURA_PARTITION, {0,0}, inx_fac_inx_tools_page_clear_demura_partition_content, inx_fac_inx_tools_page_clear_demura_partition_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_DEMURA_SWITCH, MLM_FAC_KEY_MSG_DEMURA_SWITCH, {0,1}, inx_fac_inx_tools_page_demura_switch_content, inx_fac_inx_tools_page_demura_switch_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_SHOW_PANEL_BORDER, MLM_FAC_KEY_MSG_SHOW_PANEL_BORDER, {0,1}, inx_fac_inx_tools_page_show_panel_border_content, inx_fac_inx_tools_page_show_panel_border_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_POWER_LED_LIGHT, MLM_FAC_KEY_MSG_POWER_LED_LIGHT, {0,20}, inx_fac_inx_tools_page_power_led_light_content, inx_fac_inx_tools_page_power_led_light_handle},
	{INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_INX_TOOLS_PAGE_GET_BT_MAC, MLM_FAC_KEY_MSG_GET_BT_MAC, {0,0}, inx_fac_inx_tools_page_get_bt_mac_content, NULL},
        {NAV_INX_FAC_INX_TOOLS_PAGE_GET_BT_RSSI, MLM_FAC_KEY_MSG_GET_BT_RSSI, {0,1}, inx_fac_inx_tools_page_get_bt_rssi_content, inx_fac_inx_tools_page_get_bt_rssi_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_SHOW_PANEL_BORDER, MLM_FAC_KEY_MSG_SHOW_PANEL_BORDER, {0,1}, inx_fac_inx_tools_page_show_panel_border_content, inx_fac_inx_tools_page_show_panel_border_handle},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


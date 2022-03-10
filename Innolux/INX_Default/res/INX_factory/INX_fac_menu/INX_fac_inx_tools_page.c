#include "INX_fac_inx_tools_page.h"
#include "INX_fac_main_page_res.h"

UINT8 hdcp_status=INX_RET_INIT;
UINT8 hdcp2_status=INX_RET_INIT;
UINT8 hdcp_load_back_status=INX_RET_INIT;
UINT8 hdcp2_load_back_status=INX_RET_INIT;
UINT32 ui4_dump_eep_status=INX_RET_INIT;

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
    //FILE *fp=NULL;
    //INT32 get_hdcp_size;
    //UINT8 hdcp_key_buffer[INX_HDCP_2_2_SIZE];
    //int i4_ret;

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
	c_sprintf(c_Update_demo,"dd if=%s of=/dev/mmcblk0p37; sync",cFname);
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
        {NAV_INX_FAC_INX_TOOLS_PAGE_DEMO_UPDATE, MLM_FAC_KEY_MSG_DEMO_UPDATE, {0,0}, inx_fac_inx_tools_page_demo_update_content, inx_fac_inx_tools_page_demo_update_handle}, //yshu update demo from usb disk.
        {NAV_INX_FAC_INX_TOOLS_PAGE_DUMP_EEP2USB, MLM_FAC_KEY_MSG_DUMP_EEP2USB, {0,0}, inx_fac_inx_tools_page_dump_eep2usb_content, inx_fac_inx_tools_page_dump_eep2usb_handle}, //truedano
		{INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_BURNING, MLM_FAC_KEY_MSG_HDCP_BURNING, {0,0}, inx_fac_inx_tools_page_hdcp_burning_content, inx_fac_inx_tools_page_hdcp_burning_handle},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_BURNING, MLM_FAC_KEY_MSG_HDCP2_BURNING, {0,0}, inx_fac_inx_tools_page_hdcp2_burning_content, inx_fac_inx_tools_page_hdcp2_burning_handle},    
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_CHECK, MLM_FAC_KEY_MSG_HDCP_CHECK, {0,0}, inx_fac_inx_tools_page_hdcp_check_content, NULL},
        {NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_CHECK, MLM_FAC_KEY_MSG_HDCP2_CHECK, {0,0}, inx_fac_inx_tools_page_hdcp2_check_content, NULL},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};


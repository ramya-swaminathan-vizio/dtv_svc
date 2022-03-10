#include "INX_fac_isp_info_page.h"
#include "INX_fac_main_page_res.h"

/*parameter*/
UINT8 get_rms_status=INX_RET_INIT;
UINT32 cam_val = 1; 
UINT32 cam_record_sec = 5;
UINT32 cam_play_value = 1;

/* function */
static UINT32 inx_fac_isp_info_page_cam_vid_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR tmp_camera_vid[64]={};

    strcpy(tmp_camera_vid,a_cam_inx_ret_device_info(INX_CAM_GET_DEVINFO_VID));    
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tmp_camera_vid, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_isp_info_page_cam_pid_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR tmp_camera_vid[64]={};

    strcpy(tmp_camera_vid,a_cam_inx_ret_device_info(INX_CAM_GET_DEVINFO_PID));    
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tmp_camera_vid, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_isp_info_page_isp_fw_ver_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    CHAR tmp_camera_vid[64]={};

    strcpy(tmp_camera_vid,a_cam_inx_ret_device_info(INX_CAM_GET_FW_VERSION));    
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(tmp_camera_vid, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_isp_info_page_support_format_content(UTF16_T* content)
{
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s("Press ok and save to USB", w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static UINT32 inx_fac_isp_info_page_get_rms_content(UTF16_T* content)
{
    printf("%s,%d\n",__func__,__LINE__);
	const CHAR *s_tmp_str;
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    switch (get_rms_status)
    {
        case 0:
        {
			s_tmp_str = "Stop";
        }
        break;

        case 1:
        {
			s_tmp_str = "Start";
        }
        break;

        default:
			s_tmp_str = "Stop";
        break;
    }
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return get_rms_status;
}

static UINT32 inx_fac_isp_info_page_cam_loop_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	SIZE_T   t_size = sizeof(INT32);
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	nav_fac_number_to_string(cam_val, w2s_menu_item_string);
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return cam_val;
}

static UINT32 inx_fac_isp_info_page_cam_record_file_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    const CHAR s_tmp_str[64]={0};

    c_sprintf(s_tmp_str,"%d sec",cam_record_sec);
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));    
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return cam_record_sec;
}
static UINT32 inx_fac_isp_info_page_cam_play_content(UTF16_T* content)
{
	printf("%s,%d\n",__func__,__LINE__);
	UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
	const CHAR s_tmp_str[64]={0};
	
	c_sprintf(s_tmp_str,"%d sec",cam_play_value);
	c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
	c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);
	return cam_play_value;
}

static UINT32 inx_fac_isp_info_page_cam_motor_content(UTF16_T* content)
{
	const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    int motor_status;

    // dlopen dynamic lib //
    a_cam_mtk_motor_dlopen();
    do
    {
    	motor_status = a_cam_mtk_motor_get_status();
    }while(a_cam_mtk_motor_is_running() == TRUE);
    (motor_status)?(s_tmp_str = "Up"):(s_tmp_str = "Down");
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);

    //dlclose dynamic lib //
    a_cam_mtk_motor_dlclose();
    
	return motor_status;
}

static UINT32 inx_fac_isp_info_page_cam_led_green_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    int led_status;
    
    led_status = a_led_inx_get_camera_led(INX_LED_TYPE_GREEN);
    (led_status)?(s_tmp_str = "On"):(s_tmp_str = "Off");
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);

    return led_status;
}

static UINT32 inx_fac_isp_info_page_cam_led_red_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    int led_status;
    
    led_status = a_led_inx_get_camera_led(INX_LED_TYPE_RED);
    (led_status)?(s_tmp_str = "On"):(s_tmp_str = "Off");
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);

    return led_status;
}

static UINT32 inx_fac_isp_info_page_mic_led_green_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    int led_status;
    
    led_status = a_led_inx_get_mic_led(INX_LED_TYPE_GREEN);
    (led_status)?(s_tmp_str = "On"):(s_tmp_str = "Off");
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);

    return led_status;
}

static UINT32 inx_fac_isp_info_page_mic_led_red_content(UTF16_T* content)
{
    const CHAR *s_tmp_str;
    UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    int led_status;
    
    led_status = a_led_inx_get_mic_led(INX_LED_TYPE_RED);
    (led_status)?(s_tmp_str = "On"):(s_tmp_str = "Off");
    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
	c_uc_w2s_strcpy(content, w2s_menu_item_string);

    return led_status;
}
static UINT32 inx_fac_isp_info_page_cam_isp_fw_upgrade_content(UTF16_T* content)
{
	 UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s("Press OK", w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}
static UINT32 inx_fac_isp_info_page_cam_isp_fw_upgrade_ex_content(UTF16_T* content)
{
	 UTF16_T w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
    c_uc_ps_to_w2s("Press OK", w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    c_uc_w2s_strcpy(content,w2s_menu_item_string);
    return 0;
}

static BOOL inx_fac_isp_info_page_support_format_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR usb_root_path[128]={0};
    UINT8 format_path[128]={0};

    printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);
    if(key_code == BTN_SELECT){        
        
        if( a_cfg_custom_get_mnt_path(usb_root_path) != 0 )
        {
            nav_fac_view_alert_osd("get usb path error.");
    		nav_fac_view_alert_osd_timer(5000);
            return FALSE;
        }
        a_cam_mtk_v4l2_dlopen();
        c_sprintf((char *)format_path,"%s/cam_support_format.txt",usb_root_path);
        a_cam_mtk_v4l2_get_support_format(format_path);
        a_cam_mtk_v4l2_dlclose();

        nav_fac_view_alert_osd("Save Support Format to USB/cam_support_format.txt");
    	nav_fac_view_alert_osd_timer(5000);
    }
    return TRUE;
}

static BOOL inx_fac_isp_info_page_get_rms_handle(UINT32 nc_code,UINT32 key_code)
{
    printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        get_rms_status=nc_code;
        nav_fac_view_bt_rms_osd_flag(get_rms_status);
        if(get_rms_status==1){
            nav_fac_view_bt_rms_osd_timer(3000);
        }
    }
    else{
        printf("%s, %d, ignore !\n",__func__,__LINE__);	
    }
    return TRUE;
}

static BOOL inx_fac_isp_info_page_cam_loop_handle(UINT32 nc_code,UINT32 key_code)
{
    CHAR tmp_buf[64]={};
	UINT8 u8_timeout = 0;
    
    printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);
	if(key_code == BTN_CURSOR_LEFT ){
        if( nc_code == 5000 )
            cam_val = 5000;
        else
            cam_val = nc_code - 99;
        if(cam_val <= 0)
            cam_val = 1;
    }
	else if(key_code == BTN_CURSOR_RIGHT){
        if( nc_code == 1 )
            cam_val = 1;
        else if(nc_code == 2)
            cam_val = 100;
        else
		    cam_val = nc_code + 99;
	    
		if(cam_val > 5000)
			cam_val = 5000;
	}
		
	if(key_code == BTN_SELECT){
		// remind msg show on the screen 
		nav_fac_view_alert_osd("Only AC off can stop!!!");
    	sleep(5);
		nav_fac_view_alert_osd_timer(500);
		//switch to smartcast source
		a_nav_ipts_select_virtual_input("SMARTCAST");
		int i4_ret;
		while(cam_val>0)
		{	
			printf("%s, %d, times = 0x%02X\n",__func__,__LINE__,cam_val);
    		i4_ret = a_cam_mtk_exec_streaming(CAM_TIME_TO_SEC(3));//3 sec
			if(i4_ret < 0)
			{
				u8_timeout++;
				printf("camera fail count = %d \n",u8_timeout);
				if(u8_timeout == 50) // if camera executes fail 50 times then exit loop
				{	
					inx_system(MTK_SHOW_OSD_CMD); // resume OSD
					break;
				}
				sleep(5);
				continue;
			}
			cam_val--;
            //show times left
            c_sprintf(tmp_buf,"Cam loop %d times left",cam_val);
            nav_fac_view_alert_osd(tmp_buf);
            sleep(5);
            nav_fac_view_alert_osd_timer(500);
		}
		// switch to hdmi1 source
		a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY,E_SYS_INPUT_TYPE_HDMI1);
		nav_change_av_inp_by_id(TV_WIN_ID_MAIN,E_SYS_INPUT_TYPE_HDMI1,NULL);
        cam_val = 1;
	}
    else{
	    printf("%s, %d, ignore !\n",__func__,__LINE__);	
    }
    return TRUE;
}

static BOOL inx_fac_isp_info_page_cam_record_file_handle(UINT32 nc_code,UINT32 key_code)
{    
    CHAR usb_root_path[128]={0};
    UINT8 file_path[128]={0};
    CHAR time_buf[64]={0};
    int val;
    
    printf("%s, %d, nc_code=%d, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT ){
        cam_record_sec = nc_code;
    }
    if(key_code == BTN_SELECT){
        if( a_cfg_custom_get_mnt_path(usb_root_path) != 0 )
        {
            nav_fac_view_alert_osd("get usb path error.");
    		nav_fac_view_alert_osd_timer(5000);
            return FALSE;
        }
        a_cfg_cust_get_format_time(time_buf);
        c_sprintf(file_path,"%s/cam_record_%s.mp4",usb_root_path,time_buf);
        val = CAM_TIME_TO_SEC(cam_record_sec);
        a_cam_mtk_camera_record_to_file(val,file_path);
	}
    else{
	    printf("%s, %d, ignore !\n",__func__,__LINE__);	
    }
    return TRUE;
}
static BOOL inx_fac_isp_info_page_cam_play_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=%d, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);
	if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT )
	{
		cam_play_value = nc_code;
	}
	if(key_code == BTN_SELECT)
	{
		a_nav_ipts_select_virtual_input("SMARTCAST");
		sleep(1);
		a_cam_mtk_exec_streaming(CAM_TIME_TO_SEC(cam_play_value));
		sleep(1);
		a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY,E_SYS_INPUT_TYPE_HDMI1);
		nav_change_av_inp_by_id(TV_WIN_ID_MAIN,E_SYS_INPUT_TYPE_HDMI1,NULL);
        cam_play_value = 1;
	}
}

static BOOL inx_fac_isp_info_page_cam_motor_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        // dlopen dynamic lib //
        a_cam_mtk_motor_dlopen();
        (nc_code)?a_cam_mtk_motor_up(CAM_MOTOR_MS):a_cam_mtk_motor_down(CAM_MOTOR_MS);
        //dlclose dynamic lib //
        a_cam_mtk_motor_dlclose();
    }
    return TRUE;
}

static BOOL inx_fac_isp_info_page_cam_led_green_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);    
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        (nc_code)?a_led_inx_set_camera_led(INX_LED_TYPE_GREEN,INX_LED_ACT_ON):a_led_inx_set_camera_led(INX_LED_TYPE_GREEN,INX_LED_ACT_OFF);
    }
}

static BOOL inx_fac_isp_info_page_cam_led_red_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);    
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        (nc_code)?a_led_inx_set_camera_led(INX_LED_TYPE_RED,INX_LED_ACT_ON):a_led_inx_set_camera_led(INX_LED_TYPE_RED,INX_LED_ACT_OFF);
    }
}

static BOOL inx_fac_isp_info_page_mic_led_green_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);    
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        (nc_code)?a_led_inx_set_mic_led(INX_LED_TYPE_GREEN,INX_LED_ACT_ON):a_led_inx_set_mic_led(INX_LED_TYPE_GREEN,INX_LED_ACT_OFF);
    }
}

static BOOL inx_fac_isp_info_page_mic_led_red_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);    
    if(key_code == BTN_CURSOR_LEFT || key_code == BTN_CURSOR_RIGHT){
        (nc_code)?a_led_inx_set_mic_led(INX_LED_TYPE_RED,INX_LED_ACT_ON):a_led_inx_set_mic_led(INX_LED_TYPE_RED,INX_LED_ACT_OFF);
    }
}
static BOOL inx_fac_isp_info_page_cam_isp_fw_upgrade_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);    
	INT32 i4_ret;
	CHAR s_path[128]={0},s_buf[256]={0};
	if(key_code == BTN_SELECT)
	{
		if( a_cfg_custom_get_mnt_path(s_path) != 0 )
	    {
	    	nav_fac_view_alert_osd("get usb path error.");
	    	nav_fac_view_alert_osd_timer(5000);
	        return FALSE;
	    }
		char *file_name = "auto_update.txt";
		c_sprintf(s_buf,"%s/camera_fw/%s",s_path,file_name);
		printf("%s:%d s_buf=%s\n",__FUNCTION__,__LINE__,s_buf);
		a_cam_mtk_v4l2_dlopen();
		nav_fac_view_alert_osd("isp fw upgrading...");
		i4_ret = a_cam_mtk_v4l2_upgrade_isp_firmware(s_buf);
		if(i4_ret != 0)
		{
			nav_fac_view_alert_osd("isp fw upgrade fail.");
		}
		else
		{
			nav_fac_view_alert_osd("isp fw upgrade success.");
		}
		nav_fac_view_alert_osd_timer(5000);
		a_cam_mtk_v4l2_dlclose();
	}
}
static BOOL inx_fac_isp_info_page_cam_isp_fw_upgrade_ex_handle(UINT32 nc_code,UINT32 key_code)
{
	printf("%s, %d, nc_code=0x%02X, key_code=0x%04X\n",__func__,__LINE__, nc_code, key_code);    
	INT32 i4_ret;
	CHAR s_buf[256]={0};
	if(key_code == BTN_SELECT)
	{
		char *file_name = "auto_update.txt";
		c_sprintf(s_buf,"/application/camera_fw/%s",file_name);
		printf("%s:%d s_buf=%s\n",__FUNCTION__,__LINE__,s_buf);
		a_cam_mtk_v4l2_dlopen();
		nav_fac_view_alert_osd("isp fw upgrading...");
		i4_ret = a_cam_mtk_v4l2_upgrade_isp_firmware(s_buf);
		printf("%s:%d i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret);
		if(i4_ret != 0)
		{
			nav_fac_view_alert_osd("isp fw upgrade fail.");
		}
		else
		{
			nav_fac_view_alert_osd("isp fw upgrade success.");
		}
		nav_fac_view_alert_osd_timer(5000);
		a_cam_mtk_v4l2_dlclose();
	}
}

/* G var */
UTF16_T  inx_fac_isp_info_page_title[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_TITLE_LENS] =
{
    { 'I', 'S', 'P', ' ', 'I', 'N', 'F','O', '\0'},//For PD Use
    { 'I', 'S', 'P', ' ', 'I', 'N', 'F','O', '\0'},//For Factory Use
};

inx_page_entry inx_fac_isp_info_page_entry[INX_FAC_MENU_TITLE_MAX][INX_FAC_MENU_ITEM_CNT] =
{
    {//For PD Use
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_VID, MLM_FAC_KEY_MSG_CAMERA_VID,{0,0}, inx_fac_isp_info_page_cam_vid_content, NULL},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_PID, MLM_FAC_KEY_MSG_CAMERA_PID,{0,0}, inx_fac_isp_info_page_cam_pid_content, NULL},
        {NAV_INX_FAC_ISP_INFO_PAGE_ISP_FW_VER, MLM_FAC_KEY_MSG_ISP_FW_VER,{0,0}, inx_fac_isp_info_page_isp_fw_ver_content, NULL},  
        {NAV_INX_FAC_ISP_INFO_PAGE_SUPPORT_FORMAT, MLM_FAC_KEY_MSG_SUPPORT_FORMAT,{0,0}, inx_fac_isp_info_page_support_format_content, inx_fac_isp_info_page_support_format_handle},  
        {NAV_INX_FAC_ISP_INFO_PAGE_GET_RMS, MLM_FAC_KEY_MSG_GET_RMS,{0,1}, inx_fac_isp_info_page_get_rms_content, inx_fac_isp_info_page_get_rms_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_LOOP, MLM_FAC_KEY_MSG_CAM_LOOP,{1,5000}, inx_fac_isp_info_page_cam_loop_content, inx_fac_isp_info_page_cam_loop_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_RECORD_FILE, MLM_FAC_KEY_MSG_CAM_RECORD_FILE,{5,300}, inx_fac_isp_info_page_cam_record_file_content, inx_fac_isp_info_page_cam_record_file_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_PLAY, MLM_FAC_KEY_MSG_CAM_PLAY,{0,100}, inx_fac_isp_info_page_cam_play_content, inx_fac_isp_info_page_cam_play_handle},
		{NAV_INX_FAC_ISP_INFO_PAGE_CAM_MOTOR, MLM_FAC_KEY_MSG_CAM_MOTOR,{0,1}, inx_fac_isp_info_page_cam_motor_content, inx_fac_isp_info_page_cam_motor_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_LED_GREEN, MLM_FAC_KEY_MSG_CAM_LED_GREEN,{0,1}, inx_fac_isp_info_page_cam_led_green_content, inx_fac_isp_info_page_cam_led_green_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_LED_RED, MLM_FAC_KEY_MSG_CAM_LED_RED,{0,1}, inx_fac_isp_info_page_cam_led_red_content, inx_fac_isp_info_page_cam_led_red_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_MIC_LED_GREEN, MLM_FAC_KEY_MSG_MIC_LED_GREEN,{0,1}, inx_fac_isp_info_page_mic_led_green_content, inx_fac_isp_info_page_mic_led_green_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_MIC_LED_RED, MLM_FAC_KEY_MSG_MIC_LED_RED,{0,1}, inx_fac_isp_info_page_mic_led_red_content, inx_fac_isp_info_page_mic_led_red_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_ISP_FW_UPGRADE,MLM_FAC_KEY_MSG_CAM_ISP_FW_UPGRADE,{0,1},inx_fac_isp_info_page_cam_isp_fw_upgrade_content,inx_fac_isp_info_page_cam_isp_fw_upgrade_handle},
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_ISP_FW_UPGRADE_EX,MLM_FAC_KEY_MSG_CAM_ISP_FW_UPGRADE_EX,{0,1},inx_fac_isp_info_page_cam_isp_fw_upgrade_ex_content,inx_fac_isp_info_page_cam_isp_fw_upgrade_ex_handle},
		{INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
    {//For Factory Use
        {NAV_INX_FAC_ISP_INFO_PAGE_CAM_VID, MLM_FAC_KEY_MSG_CAMERA_VID,{0,0}, inx_fac_isp_info_page_cam_vid_content, NULL},
        {INX_FAC_MENU_ITEM_END,0,{0,0},NULL,NULL},//Don`t move
    },
};



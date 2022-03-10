#include "INX_fac_camera.h"

#define MTKV4_LIB "/basic/lib/libmtkv4l2.so"
#define MTKMOTOT_LIB "/basic/lib/libmtkmotor.so"
#define MTKCAMERA_LIB "/basic/lib/libcameraplayer.so"
#define CAMERA0 "/dev/video0"
#define CAMERA1 "/dev/video2"

void *mtk_v4l2_handle;
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_get_available_device)(AVAILABLE_DEVICE_INFO_T*);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_get_support_format)(const char*, SUPPORT_FORMAT_DESCRIPTOR_T*);
char* (*pfn_mtk_v4l2_convert_format_to_str)(uint32_t pixelFormat);
int (*pfn_mtk_v4l2_open_camera)(const char*, unsigned int);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_close_camera)(const char*, unsigned int);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_set_parameters)(const char* deviceid, const CAMERA_PARAMETERS_T* parameters);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_start_capture)(const char* deviceid);
int (*pfn_mtk_v4l2_read_packet)(const char* deviceid, DATA_PACKET_T* pkt);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_read_packet_end)(DATA_PACKET_T* pkt);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_open)(const char* deviceid);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_close)(const char* deviceid);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_stop_capture)(const char* deviceid);
MTK_V4L2_RESULT_E (*pfn_mtk_v4l2_upgrade_isp_firmware)(const char* deviceid, const char* scriptPath);





void *mtk_camera_handle;
bool (*pfn_mtk_camera_player_open)(void);
bool (*pfn_mtk_camera_player_play)(void);
bool (*pfn_mtk_camera_player_pause)(void);
bool (*pfn_mtk_camera_player_stop)(void);
bool (*pfn_mtk_camera_player_send_data)(unsigned char* pBuffer, uint32_t length, uint64_t pts);
bool (*pfn_mtk_camera_player_set_media_info)(const CAMERA_MEDIA_INFO_T* mediaInfo);

void *mtk_motor_handle;
MTK_V4L2_RESULT_E (*pfn_mtk_motor_down)(uint32_t);
MTK_V4L2_RESULT_E (*pfn_mtk_motor_up)(uint32_t);
bool (*pfn_mtk_motor_is_running)(void);
MTK_MOTOR_STATUS_E (*pfn_mtk_motor_get_status)(void);

void a_cam_mtk_v4l2_dlopen(void)
{
    mtk_v4l2_handle = dlopen(MTKV4_LIB, RTLD_LAZY);
    if(!mtk_v4l2_handle){
        printf("dlopen fail : %s\n",dlerror());
        return;
    }
    pfn_mtk_v4l2_get_available_device = dlsym(mtk_v4l2_handle, "mtk_v4l2_get_available_device");
    pfn_mtk_v4l2_get_support_format = dlsym(mtk_v4l2_handle, "mtk_v4l2_get_support_format");
    pfn_mtk_v4l2_convert_format_to_str = dlsym(mtk_v4l2_handle, "mtk_v4l2_convert_format_to_str");
    pfn_mtk_v4l2_open_camera = dlsym(mtk_v4l2_handle, "mtk_v4l2_open_camera");
    pfn_mtk_v4l2_close_camera = dlsym(mtk_v4l2_handle, "mtk_v4l2_close_camera");
	pfn_mtk_v4l2_set_parameters = dlsym(mtk_v4l2_handle, "mtk_v4l2_set_parameters");
	pfn_mtk_v4l2_start_capture = dlsym(mtk_v4l2_handle, "mtk_v4l2_start_capture");
	pfn_mtk_v4l2_read_packet = dlsym(mtk_v4l2_handle,"mtk_v4l2_read_packet");
	pfn_mtk_v4l2_read_packet_end = dlsym(mtk_v4l2_handle,"mtk_v4l2_read_packet_end");
    pfn_mtk_v4l2_open = dlsym(mtk_v4l2_handle,"mtk_v4l2_open");
    pfn_mtk_v4l2_close = dlsym(mtk_v4l2_handle,"mtk_v4l2_close");
	pfn_mtk_v4l2_stop_capture = dlsym(mtk_v4l2_handle,"mtk_v4l2_stop_capture");
	pfn_mtk_v4l2_upgrade_isp_firmware = dlsym(mtk_v4l2_handle,"mtk_v4l2_upgrade_isp_firmware");
	
    printf("%s()\n",__func__);
    printf("pfn_mtk_v4l2_get_available_device=%p\n",pfn_mtk_v4l2_get_available_device);
    printf("pfn_mtk_v4l2_get_support_format=%p\n",pfn_mtk_v4l2_get_support_format);
    printf("pfn_mtk_v4l2_convert_format_to_str=%p\n",pfn_mtk_v4l2_convert_format_to_str);
    printf("pfn_mtk_v4l2_open_camera=%p\n",pfn_mtk_v4l2_open_camera);
    printf("pfn_mtk_v4l2_close_camera=%p\n",pfn_mtk_v4l2_close_camera);
    printf("pfn_mtk_v4l2_open=%p\n",pfn_mtk_v4l2_open);
    printf("pfn_mtk_v4l2_close=%p\n",pfn_mtk_v4l2_close);
	printf("a_cam_mtk_v4l2_set_parameters=%p\n",pfn_mtk_v4l2_set_parameters);
	printf("pfn_mtk_v4l2_start_capture=%p\n",pfn_mtk_v4l2_start_capture);
	printf("pfn_mtk_v4l2_read_packet=%p\n",pfn_mtk_v4l2_read_packet);
	printf("pfn_mtk_v4l2_read_packet_end=%p\n",pfn_mtk_v4l2_read_packet_end);
	printf("pfn_mtk_v4l2_stop_capture=%p\n",pfn_mtk_v4l2_stop_capture);
	printf("pfn_mtk_v4l2_upgrade_isp_firmware=%p\n",pfn_mtk_v4l2_upgrade_isp_firmware);
}

void a_cam_mtk_v4l2_dlclose(void)
{
    printf("%s()\n",__func__);
    if(mtk_v4l2_handle){
        dlclose(mtk_v4l2_handle);
        printf("dlclose() sucess\n");
    }
}

MTK_V4L2_RESULT_E a_cam_mtk_v4l2_get_available_device(AVAILABLE_DEVICE_INFO_T *availableDevice)
{
    MTK_V4L2_RESULT_E ret;
    if(pfn_mtk_v4l2_get_available_device){
        //AVAILABLE_DEVICE_INFO_T availableDevice;
        ret = pfn_mtk_v4l2_get_available_device(availableDevice);
        printf("\nexec mtk_v4l2_get_available_device finish......., ret=%d\n",ret);

        //const DEVICE_INFO_T* deviceInfo = availableDevice.deviceList[0];
        //printf("deviceid: %s\n", deviceInfo->deviceid);
        //printf("devicename: %s\n", deviceInfo->devicename);
        //printf("vendorid: %s\n", deviceInfo->vendorid);
        //printf("productid: %s\n", deviceInfo->productid);
    }
    return ret;
}

int a_cam_mtk_v4l2_get_support_format(char* tofile)
{
    SUPPORT_FORMAT_DESCRIPTOR_T supportFmt;
    int ret,i;
    char tmp_buf[64]={};
    FILE* outFp;
    
    if(pfn_mtk_v4l2_get_support_format){
        ret = pfn_mtk_v4l2_get_support_format(CAMERA0, &supportFmt);
        printf("\nexec mtk_v4l2_get_support_format finish......., ret=%d\n",ret);
        if( ret == 0 ){
            outFp = fopen(tofile,"w");
            if( outFp == NULL ){
                printf("%s() fopen error\n",__func__);
                return -99;
            }
            //Get support format list////////////
            for (i = 0; i < supportFmt.size; ++i){
                const FORMAT_DESCRIPTOR_T* fmt = &supportFmt.fmtDescList[i];
                sprintf(tmp_buf,"FMT:%s, RES:%ux%u, fps:%u\n", a_cam_mtk_v4l2_convert_format_to_str(fmt->pixelformat),
                        fmt->width, fmt->height, fmt->fps);
                fwrite((void *)tmp_buf, c_strlen(tmp_buf), 1, outFp);
            }
            fclose(outFp);
        }
    }
    return ret;
}

char* a_cam_mtk_v4l2_convert_format_to_str(uint32_t pixelFormat)
{
    char* ret=NULL;
    if(pfn_mtk_v4l2_convert_format_to_str){
        ret = pfn_mtk_v4l2_convert_format_to_str(pixelFormat);
        //printf("\nexec mtk_v4l2_convert_format_to_str finish......., ret=%s\n",ret);
    }
    return ret;
}

int a_cam_mtk_v4l2_open_camera(unsigned int motorUpTime)
{
    int ret=0;
    if(pfn_mtk_v4l2_open_camera){
        ret = pfn_mtk_v4l2_open_camera(CAMERA0, motorUpTime);
        if( ret < 0 ){
            printf("Failed to open Camera %s\n", CAMERA0);
			return ret;
        }
    }
    return ret;
}

int a_cam_mtk_v4l2_close_camera(unsigned int motorUpTime)
{
    int ret=0;
    if(pfn_mtk_v4l2_close_camera){
        ret = pfn_mtk_v4l2_close_camera(CAMERA0, motorUpTime);
        if( ret < 0 ){
            printf("Failed to close Camera %s\n", CAMERA0);
			return ret;
        }
    }
    return ret;
}

MTK_V4L2_RESULT_E a_cam_mtk_v4l2_set_parameters(void)
{
	MTK_V4L2_RESULT_E ret;
	CAMERA_PARAMETERS_T stCameraParam = {0};
	memset(&stCameraParam,0,sizeof(CAMERA_PARAMETERS_T));
	stCameraParam.fmtDesc.pixelformat = v4l2_fourcc('H', '2', '6', '4');
	stCameraParam.fmtDesc.width = 1920;
	stCameraParam.fmtDesc.height = 1080;
	stCameraParam.fmtDesc.fps = 30;
	ret = pfn_mtk_v4l2_set_parameters(CAMERA0, &stCameraParam);
	printf("\nexec mtk_v4l2_set_parameters finish......., ret=%d\n",ret);
	if (E_MTK_V4L2_RET_OK != ret)
	{
		pfn_mtk_v4l2_close(CAMERA0);
		printf("Failed to set parameter\n");
		return ret;
	}
	return ret;	
}
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_start_capture(void)
{
	MTK_V4L2_RESULT_E ret;
	ret = pfn_mtk_v4l2_start_capture(CAMERA0);
	printf("\nexec mtk_v4l2_start_capture finish......., ret=%d\n",ret);
	if(E_MTK_V4L2_RET_OK != ret)
	{	
		pfn_mtk_v4l2_close(CAMERA0);
		printf("Failed to start capture ret = %d\n",ret);
		return ret;
	}
	return ret;
}
int a_cam_mtk_v4l2_read_packet(void)
{
	int ret;
	DATA_PACKET_T pkt;
	ret = pfn_mtk_v4l2_read_packet(CAMERA0,&pkt);
	if(E_MTK_V4L2_RET_OK != ret)
	{	
		printf("Failed to read packet ret = %d\n",ret);
		return ret;
	}
	return ret;
}
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_read_packet_end(void)
{
	MTK_V4L2_RESULT_E ret;
	DATA_PACKET_T pkt;
	ret = pfn_mtk_v4l2_read_packet_end(&pkt);
	if(E_MTK_V4L2_RET_OK != ret)
	{	
		printf("Failed to read packet end ret = %d\n",ret);
		return ret;
	}
	return ret;
}
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_stop_capture(void)
{
	MTK_V4L2_RESULT_E ret;
	ret = pfn_mtk_v4l2_stop_capture(CAMERA0);
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to stop capture ret = %d\n",ret);
		return ret;
	}
	return ret;
}	

MTK_V4L2_RESULT_E a_cam_mtk_v4l2_open(void)
{
    MTK_V4L2_RESULT_E ret=0;
    if(pfn_mtk_v4l2_open){
        ret = pfn_mtk_v4l2_open(CAMERA0);
        if(E_MTK_V4L2_RET_OK != ret)
    	{
    		printf("Failed to a_cam_mtk_v4l2_open ret = %d\n",ret);
    		return ret;
    	}
    }
    return ret;
}

MTK_V4L2_RESULT_E a_cam_mtk_v4l2_close(void)
{
    MTK_V4L2_RESULT_E ret=0;
    if(pfn_mtk_v4l2_close){
        ret = pfn_mtk_v4l2_close(CAMERA0);
        if(E_MTK_V4L2_RET_OK != ret)
    	{
    		printf("Failed to pfn_mtk_v4l2_close ret = %d\n",ret);
    		return ret;
    	}
    }
    return ret;
}
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_upgrade_isp_firmware(const char* scriptPath)
{
	int ret = system(CAM_CHECK_DEV_BUS_MOUNTED);
    printf("Check /dev/bus/usb mounted or not, ret:%s\n", (0 == ret? "true" : "false"));
    if (ret != 0)
    {
        printf("%s\n", CAM_SYSTEM_CMD_BIND_DEV_BUS_USB);
        system(CAM_SYSTEM_CMD_BIND_DEV_BUS_USB);
    }
	return pfn_mtk_v4l2_upgrade_isp_firmware(CAMERA0,scriptPath);
}

/*-----------------------------------------------------------------------------
 * Author: 
 * Name: a_cam_mtk_exec_streaming
 * Description: execute camera function 
 * Inputs: 
 * Outputs: 
 * Returns: 
	E_MTK_V4L2_RET_OK	   =  0,
	E_MTK_V4L2_RET_FAIL   = -1,
	E_MTK_V4L2_ACCESS_FAIL = -EACCES,
	E_MTK_V4L2_BAD_FILE_DESCRIPTOR = -EBADF,
	E_MTK_V4L2_AGAIN = -EAGAIN,
	E_MTK_V4L2_OUT_OF_MEM = -ENOMEM,
	E_MTK_V4L2_DEVICE_BUSY = -EBUSY,
	E_MTK_V4L2_NO_DEV = -ENODEV,
	E_MTK_V4L2_INVALID_PARAMETERS = -EINVAL,
	E_MTK_V4L2_OP_NOT_SUPPORT = -EOPNOTSUPP,
 ----------------------------------------------------------------------------*/
int a_cam_mtk_exec_streaming(int val)
{
	int i4_ret;
	// disable OSD //
	inx_system(MTK_HIDE_OSD_CMD);
	// dlopen dynamic lib //
	a_cam_mtk_v4l2_dlopen();
	a_cam_mtk_camera_player_dlopen();
    if( a_cam_mtk_motor_is_running() )
    {
        a_cam_mtk_v4l2_dlclose();
		a_cam_mtk_camera_dlclose();
        return -1;
    }
	if( a_cam_mtk_motor_get_status() == E_MTK_MOTOR_STATUS_UP )
	{
		a_cam_mtk_v4l2_dlclose();
		a_cam_mtk_camera_dlclose();
        return -1;
	}
	// camera  function //
	i4_ret = a_cam_mtk_v4l2_open_camera(CAM_MOTOR_MS);
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_set_parameters();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_start_capture();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_camera_player_open();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_camera_set_media_info();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_camera_player_play();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_camera_execute(val,1);
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_stop_capture();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_close_camera(CAM_MOTOR_MS);
	CAM_DEBUG_MSG(i4_ret);
	
	//dlclose dynamic lib // 
	a_cam_mtk_v4l2_dlclose();
	a_cam_mtk_camera_dlclose();

	//enable OSD //
	inx_system(MTK_SHOW_OSD_CMD);
	return i4_ret;

}

//==========================================================================

void a_cam_mtk_motor_dlopen(void)
{
    mtk_motor_handle = dlopen(MTKMOTOT_LIB, RTLD_LAZY);
    if(!mtk_motor_handle){
        printf("dlopen fail : %s\n",dlerror());
        return;
    }
    pfn_mtk_motor_down = dlsym(mtk_motor_handle, "mtk_motor_down");
    pfn_mtk_motor_up = dlsym(mtk_motor_handle, "mtk_motor_up");
    pfn_mtk_motor_is_running = dlsym(mtk_motor_handle, "mtk_motor_is_running");
    pfn_mtk_motor_get_status = dlsym(mtk_motor_handle, "mtk_motor_get_status");
    printf("%s()\n",__func__);
    printf("pfn_mtk_motor_down=%p\n",pfn_mtk_motor_down);
    printf("pfn_mtk_motor_up=%p\n",pfn_mtk_motor_up);
    printf("pfn_mtk_motor_is_running=%p\n",pfn_mtk_motor_is_running);
    printf("pfn_mtk_motor_get_status=%p\n",pfn_mtk_motor_get_status);
}

void a_cam_mtk_motor_dlclose(void)
{
    printf("%s()\n",__func__);
    if(mtk_motor_handle){
        dlclose(mtk_motor_handle);
        printf("dlclose() sucess\n");
    }
}

int _a_cam_mtk_motor_down(uint32_t motorTime)
{
    int ret;
    if( pfn_mtk_motor_down ){
        ret = pfn_mtk_motor_down(motorTime);
        printf("%s() ret=%d\n",__func__,ret);
    }
    return ret;
}

int _a_cam_mtk_motor_up(uint32_t motorTime)
{
    int ret;
    if( pfn_mtk_motor_up ){
        ret = pfn_mtk_motor_up(motorTime);
        printf("%s() ret=%d\n",__func__,ret);
    }
    return ret;
}

bool a_cam_mtk_motor_is_running(void)
{
    bool ret;
    if( pfn_mtk_motor_is_running ){
        ret = pfn_mtk_motor_is_running();
        printf("%s() ret=%d\n",__func__,ret);
    }
    return ret;
}

int a_cam_mtk_motor_get_status(void)
{
    int ret;
    if( pfn_mtk_motor_get_status ){
        ret = pfn_mtk_motor_get_status();
        printf("%s() ret=%d\n",__func__,ret);
    }
    return ret;
}

int a_cam_mtk_motor_down(uint32_t motorTime)
{
    if( a_cam_mtk_motor_is_running() ){
        return -1;
    }else if( a_cam_mtk_motor_get_status() == E_MTK_MOTOR_STATUS_DOWN ){
        return 0;
    }
    _a_cam_mtk_motor_down(motorTime);
    return 1;
}

int a_cam_mtk_motor_up(uint32_t motorTime)
{
    if( a_cam_mtk_motor_is_running() ){
        return -1;
    }else if( a_cam_mtk_motor_get_status() == E_MTK_MOTOR_STATUS_UP ){
        return 0;
    }
    _a_cam_mtk_motor_up(motorTime);
    return 1;
}
//=======================================================================

void a_cam_mtk_camera_player_dlopen(void)
{
	mtk_camera_handle = dlopen(MTKCAMERA_LIB, RTLD_LAZY);
    if(!mtk_camera_handle){
        printf("dlopen fail : %s\n",dlerror());
        return;
    }
	pfn_mtk_camera_player_open = dlsym(mtk_camera_handle, "mtk_camera_player_open");
	pfn_mtk_camera_player_play = dlsym(mtk_camera_handle, "mtk_camera_player_play");
	pfn_mtk_camera_player_pause = dlsym(mtk_camera_handle, "mtk_camera_player_pause");
	pfn_mtk_camera_player_stop = dlsym(mtk_camera_handle, "mtk_camera_player_stop");
	pfn_mtk_camera_player_send_data = dlsym(mtk_camera_handle, "mtk_camera_player_send_data");
	pfn_mtk_camera_player_set_media_info = dlsym(mtk_camera_handle,"mtk_camera_player_set_media_info");
	
	printf("%s()\n",__func__);
	printf("pfn_mtk_camera_player_open=%p\n",pfn_mtk_camera_player_open);
	printf("pfn_mtk_camera_player_play=%p\n",pfn_mtk_camera_player_play);
	printf("pfn_mtk_camera_player_pause=%p\n",pfn_mtk_camera_player_pause);
	printf("pfn_mtk_camera_player_stop=%p\n",pfn_mtk_camera_player_stop);
	printf("pfn_mtk_camera_player_send_data=%p\n",pfn_mtk_camera_player_send_data);
	printf("pfn_mtk_camera_player_set_media_info=%p\n",pfn_mtk_camera_player_set_media_info);
}
bool a_cam_mtk_camera_player_open(void)
{
	bool ret;
	ret = pfn_mtk_camera_player_open();
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to open ret = %d\n",ret);
		return ret;
	}
	return ret;
}
bool a_cam_mtk_camera_player_play(void)
{
	bool ret;
	ret = pfn_mtk_camera_player_play();
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to play ret = %d\n",ret);
		return ret;
	}
	return ret;
}
bool a_cam_mtk_camera_pause(void)
{
	bool ret;
	ret = pfn_mtk_camera_player_pause();
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to pause ret = %d\n",ret);
		return ret;
	}
	return ret;
	
}
bool a_cam_mtk_camera_stop(void)
{
	bool ret;
	ret = pfn_mtk_camera_player_stop();
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to stop ret = %d\n",ret);
		return ret;
	}
	return ret;
}
bool a_cam_mtk_camera_send_data(unsigned char* pBuffer, uint32_t length, uint64_t pts)
{
	bool ret;
	ret = pfn_mtk_camera_player_send_data(pBuffer,length,pts);
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to sned data ret = %d\n",ret);
		return ret;
	}
	return ret;
	
}
bool a_cam_mtk_camera_set_media_info(void)
{
	bool ret;
	CAMERA_PARAMETERS_T stCameraParam = {0};
	memset(&stCameraParam,0,sizeof(CAMERA_PARAMETERS_T));
	stCameraParam.fmtDesc.pixelformat = v4l2_fourcc('H', '2', '6', '4');
	stCameraParam.fmtDesc.width = 1920;
	stCameraParam.fmtDesc.height = 1080;
	stCameraParam.fmtDesc.fps = 30;
	ret = pfn_mtk_camera_player_set_media_info(&stCameraParam);
	if(E_MTK_V4L2_RET_OK != ret)
	{
		printf("Failed to send media info ret = %d\n",ret);
		return ret;
	}
	return ret;
}
void a_cam_mtk_camera_dlclose(void)
{
    printf("%s()\n",__func__);
    if(mtk_camera_handle){
        dlclose(mtk_camera_handle);
        printf("dlclose() sucess\n");
    }
}
int a_cam_mtk_camera_execute(int val, unsigned char with_led)
{
	int ret,count=0;
	int try_count = val*5;
	
	while (count < val)
    {
        DATA_PACKET_T pkt;
        ret = pfn_mtk_v4l2_read_packet(CAMERA0,&pkt);
        if (ret == E_MTK_V4L2_AGAIN)
        {	
        	printf(" try again = %d !!!\n ",try_count);
            usleep(10000);
			if(try_count < 0)
				return -1;
			try_count--;
            continue;
        }
        if (ret >= 0)
        {
            printf("[%d]size:%d, pts:%lld\n", count, pkt.size, pkt.pts);
            if (pfn_mtk_camera_player_send_data)
            {
                pfn_mtk_camera_player_send_data(pkt.data, pkt.size, pkt.pts);
            }
            //camera led on / off
            if( with_led ){
                if( (count % 10) == 0 ){
                    a_led_inx_set_camera_led(INX_LED_TYPE_GREEN,INX_LED_ACT_ON);
                    c_thread_delay(100);
                    a_led_inx_set_camera_led(INX_LED_TYPE_GREEN,INX_LED_ACT_OFF);
                }else if( (count % 15) == 0 ){
                    a_led_inx_set_camera_led(INX_LED_TYPE_RED,INX_LED_ACT_ON);
                    c_thread_delay(100);
                    a_led_inx_set_camera_led(INX_LED_TYPE_RED,INX_LED_ACT_OFF);
                }
            }
            count ++;
        }
		else
			return ret;
        pfn_mtk_v4l2_read_packet_end(&pkt);
    }
	if(pfn_mtk_camera_player_stop)
		pfn_mtk_camera_player_stop();
	return ret;

}

int _a_cam_mtk_camera_record_to_file(int val,char* filepath)
{
    int ret,count=0;
    int try_count = val*5;

    FILE* pOutputFile = fopen(filepath, "w+");
	while (count < val)
    {
        DATA_PACKET_T pkt;
        ret = pfn_mtk_v4l2_read_packet(CAMERA0,&pkt);
        if (ret == E_MTK_V4L2_AGAIN)
        {
            printf(" try again = %d !!!\n ",try_count);
            usleep(10000);
			if(try_count < 0){
                fclose(pOutputFile);
                return -1;
             }
			try_count--;
            continue;
        }
        if (ret >= 0)
        {
            printf("[%d]size:%d, pts:%lld\n", count, pkt.size, pkt.pts);
            fwrite(pkt.data, pkt.size, 1, pOutputFile);
            count ++;
        }
		else{
            fclose(pOutputFile);
			return ret;
        }
        pfn_mtk_v4l2_read_packet_end(&pkt);
    }

    fclose(pOutputFile);
	return ret;
}

int a_cam_mtk_camera_record_to_file(int val,char* filepath)
{
	int i4_ret;

    // dlopen dynamic lib //
	a_cam_mtk_v4l2_dlopen();
	a_cam_mtk_camera_player_dlopen();

    // camera  function //
	i4_ret = a_cam_mtk_v4l2_open_camera(CAM_MOTOR_MS);
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_set_parameters();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_start_capture();
	CAM_DEBUG_MSG(i4_ret);
	//i4_ret = a_cam_mtk_camera_player_open();
	//CAM_DEBUG_MSG(i4_ret);
	//i4_ret = a_cam_mtk_camera_player_play();
	//CAM_DEBUG_MSG(i4_ret);
	i4_ret = _a_cam_mtk_camera_record_to_file(val,filepath);
	//CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_stop_capture();
	CAM_DEBUG_MSG(i4_ret);
	i4_ret = a_cam_mtk_v4l2_close_camera(CAM_MOTOR_MS);
	CAM_DEBUG_MSG(i4_ret);

	//dlclose dynamic lib //
	a_cam_mtk_v4l2_dlclose();
	a_cam_mtk_camera_dlclose();

    return i4_ret;
}

char * a_cam_inx_ret_device_info(int dev_item)
{
    AVAILABLE_DEVICE_INFO_T availableDevice;
    DEVICE_INFO_T deviceInfo;
    static char ret_str[DEVICE_INFO_LEN];

    c_memset(ret_str,0,DEVICE_INFO_LEN);

    a_cam_mtk_v4l2_dlopen();
    a_cam_mtk_v4l2_get_available_device(&availableDevice);
    //printf("DEVICE_INFO_T sizeof = %d\n",sizeof(DEVICE_INFO_T));
    c_memcpy(&deviceInfo,&availableDevice.deviceList[0],sizeof(DEVICE_INFO_T));
    //printf("deviceInfo.deviceid = %s\n",deviceInfo.deviceid);
    //printf("deviceInfo.devicename = %s\n",deviceInfo.devicename);
    //printf("deviceInfo.vendorid = %s\n",deviceInfo.vendorid);
    //printf("deviceInfo.productid = %s\n",deviceInfo.productid);
    //printf("deviceInfo.firmwareVersion = %s\n",deviceInfo.firmwareVersion);
    a_cam_mtk_v4l2_dlclose();

    switch(dev_item){
        case INX_CAM_GET_DEVINFO_VID:
            c_strcpy(ret_str,deviceInfo.vendorid);
            break;
        case INX_CAM_GET_DEVINFO_PID:
            c_strcpy(ret_str,deviceInfo.productid);
            break;
        case INX_CAM_GET_FW_VERSION:
            c_strcpy(ret_str,deviceInfo.firmwareVersion);
            break;
        default:
            break;
    }
    return ret_str;
}

// led //////////////////////////////////////////////////////////////
void a_led_inx_set_camera_led(char *type, char *action)
{
    if( !strcmp(type,INX_LED_TYPE_GREEN) ){ //led green
        inx_system("echo %s > /sys/devices/gpiochip0/gpio/gpio8/value",action); 
    }else if( !strcmp(type,INX_LED_TYPE_RED) ){ //ed red
        inx_system("echo 'out' > /sys/devices/gpiochip0/gpio/gpio13/direction");
        inx_system("echo %s > /sys/devices/gpiochip0/gpio/gpio13/value",action);
    }else{
        printf("error type.\n");
        return;
    }
    printf("set camera %s led %s\n",type,action);
}

int a_led_inx_get_camera_led(char *type)
{
    char buf[32]={};
    FILE *fp;
    char *led_path;
    
    if( !strcmp(type,INX_LED_TYPE_GREEN) ){ //led green
        led_path = "/sys/devices/gpiochip0/gpio/gpio8/value";
    }else if( !strcmp(type,INX_LED_TYPE_RED) ){ //ed red
        led_path = "/sys/devices/gpiochip0/gpio/gpio13/value";
    }
    fp = fopen(led_path, "r");
    if(fp)
        fread(buf,32,1,fp);

    fclose(fp);
    return atoi(buf);
}

void a_led_inx_set_mic_led(char *type, char *action)
{
    if( !strcmp(type,INX_LED_TYPE_GREEN) ){ //led green
        inx_system("echo %s > /sys/devices/gpiochip0/gpio/gpio16/value",action); 
    }else if( !strcmp(type,INX_LED_TYPE_RED) ){ //ed red
        inx_system("echo 'out' > /sys/devices/gpiochip0/gpio/gpio19/direction");
        inx_system("echo %s > /sys/devices/gpiochip0/gpio/gpio19/value",action);
    }else{
        printf("error type.\n");
        return;
    }
    printf("set mic %s led %s\n",type,action);
}

int a_led_inx_get_mic_led(char *type)
{
    char buf[32]={};
    FILE *fp;
    char *led_path;
    
    if( !strcmp(type,INX_LED_TYPE_GREEN) ){ //led green
        led_path = "/sys/devices/gpiochip0/gpio/gpio16/value";
    }else if( !strcmp(type,INX_LED_TYPE_RED) ){ //ed red
        led_path = "/sys/devices/gpiochip0/gpio/gpio19/value";
    }
    fp = fopen(led_path, "r");
    if(fp)
        fread(buf,32,1,fp);

    fclose(fp);
    return atoi(buf);
}


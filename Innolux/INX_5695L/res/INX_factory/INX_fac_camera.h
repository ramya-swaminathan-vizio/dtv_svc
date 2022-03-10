#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "MtkV4L2.h"
#include "MtkMotor.h"
#include "CameraPlayer.h"
#include "INX_d_factory.h"

//enum
enum{
    INX_CAM_GET_DEVINFO_VID=0,
    INX_CAM_GET_DEVINFO_PID,
    INX_CAM_GET_FW_VERSION,
    INX_CAM_END
};

#define CAM_MOTOR_MS 800
#define CAM_TIME_TO_SEC(t_sev) (t_sev*30)
#define CAM_CHECK_DEV_BUS_MOUNTED "cat /proc/mounts | grep /dev/bus/usb"
#define CAM_SYSTEM_CMD_BIND_DEV_BUS_USB "mount -o bind /cast_root/dev/bus/usb /dev/bus/usb"
#define CAM_DEBUG_MSG(val)  \
                        if(val < E_MTK_V4L2_RET_OK)           \
                        {                               \
                                printf("[INX-AT] error : %s,%d : i4_ret = %d",__FUNCTION__,__LINE__,val); \
                                a_cam_mtk_v4l2_dlclose(); \
								a_cam_mtk_camera_dlclose(); \
                                return E_MTK_V4L2_RET_FAIL; \
                        }

// led //////////////////////////////////////////////////////
#define INX_LED_TYPE_GREEN "green"
#define INX_LED_TYPE_RED "red"
#define INX_LED_ACT_OFF "0"
#define INX_LED_ACT_ON "1"

//C++
MTK_V4L2_RESULT_E mtk_v4l2_get_available_device(AVAILABLE_DEVICE_INFO_T* pAvailableDeviceInfo);
MTK_V4L2_RESULT_E mtk_v4l2_get_support_format(const char* deviceid, SUPPORT_FORMAT_DESCRIPTOR_T* pSupportFmt);
char* mtk_v4l2_convert_format_to_str(uint32_t pixelFormat);
int mtk_v4l2_open_camera(const char* deviceid, unsigned int motorUpTime);
MTK_V4L2_RESULT_E mtk_v4l2_close_camera(const char* deviceid, unsigned int motorDownTime);
MTK_MOTOR_RESULT_E mtk_motor_down(uint32_t motorTime);
MTK_MOTOR_RESULT_E mtk_motor_up(uint32_t motorTime);
bool mtk_motor_is_running(void);
MTK_MOTOR_STATUS_E mtk_motor_get_status(void);

bool mtk_camera_player_open();
bool mtk_camera_player_play();
bool mtk_camera_player_pause();
bool mtk_camera_player_stop();
bool mtk_camera_player_send_data(unsigned char* pBuffer, uint32_t length, uint64_t pts);

void a_cam_mtk_v4l2_dlopen(void);
void a_cam_mtk_v4l2_dlclose(void);
int a_cam_mtk_v4l2_get_available_device(AVAILABLE_DEVICE_INFO_T *availableDevice);
int a_cam_mtk_v4l2_get_support_format(char* tofile);
char* a_cam_mtk_v4l2_convert_format_to_str(uint32_t pixelFormat);
int a_cam_mtk_v4l2_open_camera(unsigned int motorUpTime);
int a_cam_mtk_v4l2_close_camera(unsigned int motorUpTime);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_set_parameters(void);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_start_capture(void);
int a_cam_mtk_v4l2_read_packet(void);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_read_packet_end(void);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_stop_capture(void);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_open(void);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_close(void);
int a_cam_mtk_exec_streaming(int val);
MTK_V4L2_RESULT_E a_cam_mtk_v4l2_upgrade_isp_firmware(const char* scriptPath);


void a_cam_mtk_motor_dlopen(void);
void a_cam_mtk_motor_dlclose(void);
int _a_cam_mtk_motor_down(uint32_t motorTime);
int _a_cam_mtk_motor_up(uint32_t motorTime);
bool a_cam_mtk_motor_is_running(void);
int a_cam_mtk_motor_get_status(void);
int a_cam_mtk_motor_down(uint32_t motorTime);
int a_cam_mtk_motor_up(uint32_t motorTime);

void a_cam_mtk_camera_player_dlopen(void);
void a_cam_mtk_camera_dlclose(void);
bool a_cam_mtk_camera_player_open(void);
bool a_cam_mtk_camera_player_play(void);
bool a_cam_mtk_camera_pause(void);
bool a_cam_mtk_camera_stop(void);
bool a_cam_mtk_camera_send_data(unsigned char* pBuffer, uint32_t length, uint64_t pts);
bool a_cam_mtk_camera_set_media_info(void);
int a_cam_mtk_camera_execute(int val, unsigned char with_led);
int _a_cam_mtk_camera_record_to_file(int val,char* filepath);
int a_cam_mtk_camera_record_to_file(int val,char* filepath);
char * a_cam_inx_ret_device_info(int dev_item);

// led //////////////////////////////////////////////////////
void a_led_inx_set_camera_led(char *type, char *action);
int a_led_inx_get_camera_led(char *type);
void a_led_inx_set_mic_led(char *type, char *action);


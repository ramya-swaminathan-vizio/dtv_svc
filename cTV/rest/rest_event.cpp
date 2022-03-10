#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"
#include "a_rest_event.h"

#include "log.h"
#include "a_jsonrpc.h"
#include "system.h"
#include "tv_settings/devices.h"

void rest_event_notify(const char* uri, int intValue, const char* stringValue)
{
    DBG_INFO(("REST_AP_EVENT", "rest_event_notify: enter, uri=%s, intValue=%d, stringValue=%s\n", uri, intValue, stringValue));
    jsonrpc_send_event(uri, intValue, stringValue);
    return;
}

void rest_event_notify_ex(const char* uri, const void* data)
{
    DBG_INFO(("REST_AP_EVENT", "rest_event_notify_ex: enter, uri=%s\n", uri));
    jsonrpc_send_event_ex(uri, data);
    return;
}

void rest_event_notify_current_input(const char* stringValue)
{
    DBG_INFO(("REST_AP_EVENT", "rest_event_notify_current_input: enter, stringValue=%s\n", stringValue));
    //c_dbg_dump_stack();
    _rest_system_current_input_notification(stringValue);
    return;
}

#define PA_MASK 0x7000
#define CEC_OSD_NAME_SIZE 15
#define CEC_VENDOR_ID_SIZE CEC_OSD_NAME_SIZE
#define CEC_DEVICE_LA_SIZE (CEC_OSD_NAME_SIZE >> 1)


void rest_event_notify_cec_soundbar_plugged_in(unsigned short pa,unsigned char * dev_vndr_id,unsigned char * dev_device_la,unsigned short * dev_osd_name)
{
	Json::Value item;
	Json::Value cec_obj;
	
	char cec_dev_osd_name[CEC_OSD_NAME_SIZE+1] = {0};
	char cec_vendor_id[CEC_VENDOR_ID_SIZE+1] = {0};
	char cec_device_la[CEC_DEVICE_LA_SIZE+1] = {0};
	
	c_memset(cec_dev_osd_name, 0,sizeof(cec_dev_osd_name));
	c_memset(cec_vendor_id, 0,sizeof(cec_vendor_id));
	c_uc_w2s_to_ps(dev_osd_name, cec_dev_osd_name, CEC_OSD_NAME_SIZE);
	c_sprintf(cec_vendor_id,"0x%x%x%x",dev_vndr_id[0],dev_vndr_id[1],dev_vndr_id[2]);
	c_sprintf(cec_device_la,"0x%x",dev_device_la[0]);
	
	if((pa & PA_MASK) == 0x1000)	
	cec_obj["HDMI_PORT"] = "HDMI-1";
	
	else if((pa & PA_MASK) == 0x2000)	
	cec_obj["HDMI_PORT"] = "HDMI-2";
	
	else if((pa & PA_MASK) == 0x3000)	
	cec_obj["HDMI_PORT"] = "HDMI-3";
	
	else if((pa & PA_MASK) == 0x4000)	
	cec_obj["HDMI_PORT"] = "HDMI-4";

	else
	cec_obj["HDMI_PORT"] = " ";
	
	cec_obj["OSD_NAME"] = std::string(cec_dev_osd_name).c_str();
	cec_obj["AMP_CONNECTED"] = "true";
	cec_obj["LOGICAL_ADDRESS"] = std::string(cec_device_la).c_str();
	cec_obj["DEVICE_TYPE"] = "Audio System";
	cec_obj["VENDOR_ID"] = std::string(cec_vendor_id).c_str();
	item["CEC_OBJECT"] = cec_obj;
	item["CONNECTION_STATUS"] = 1;
	rest_event_notify("system/cec", 0, item.toStyledString().c_str());
	return;
}

void rest_event_notify_cec_soundbar_unplugged(unsigned short pa,unsigned char * dev_vndr_id,unsigned char *  dev_device_la,unsigned short * dev_osd_name)
{
	Json::Value item;
	Json::Value cec_obj;
	
	char cec_dev_osd_name[CEC_OSD_NAME_SIZE+1] = {0};
	char cec_vendor_id[CEC_VENDOR_ID_SIZE+1] = {0};
	char cec_device_la[CEC_DEVICE_LA_SIZE+1] = {0};
	
	c_memset(cec_dev_osd_name, 0,sizeof(cec_dev_osd_name));
	c_memset(cec_vendor_id, 0,sizeof(cec_vendor_id));
	c_uc_w2s_to_ps(dev_osd_name, cec_dev_osd_name, CEC_OSD_NAME_SIZE);
	c_sprintf(cec_vendor_id,"0x%x%x%x",dev_vndr_id[0],dev_vndr_id[1],dev_vndr_id[2]);
	c_sprintf(cec_device_la,"0x%x",dev_device_la[0]);
	
	cec_obj["DEV_NAME"] = "Audio System";
	
	if((pa & PA_MASK) == 0x1000)	
	cec_obj["HDMI_PORT"] = "HDMI-1";
	
	else if((pa & PA_MASK) == 0x2000)	
	cec_obj["HDMI_PORT"] = "HDMI-2";
	
	else if((pa & PA_MASK) == 0x3000)	
	cec_obj["HDMI_PORT"] = "HDMI-3";
	
	else if((pa & PA_MASK) == 0x4000)	
	cec_obj["HDMI_PORT"] = "HDMI-4";

	else
	cec_obj["HDMI_PORT"] = " ";

	cec_obj["OSD_NAME"] = std::string(cec_dev_osd_name).c_str();
	cec_obj["AMP_CONNECTED"] = "false";
	cec_obj["LOGICAL_ADDRESS"] = std::string(cec_device_la).c_str();
	cec_obj["DEVICE_TYPE"] = "Audio System";
	cec_obj["VENDOR_ID"] = std::string(cec_vendor_id).c_str();
	item["CEC_OBJECT"] = cec_obj;
	item["CONNECTION_STATUS"] = 0;
	rest_event_notify("system/cec", 0, item.toStyledString().c_str());
	return;
}

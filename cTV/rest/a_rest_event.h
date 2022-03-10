#ifndef _A_REST_EVENT_H_
#define _A_REST_EVENT_H_

//#include "json/value.h"
//#include "json/json.h"
//#include "json/value.h"

#ifdef __cplusplus
extern "C" {
#endif

void rest_event_notify(const char*, int, const char*);
void rest_event_notify_ex(const char*, const void*);
void rest_event_notify_current_input(const char* stringValue);
void rest_event_notify_cec_soundbar_plugged_in(unsigned short pa,unsigned char * dev_vndr_id,unsigned char * dev_device_la,unsigned short * dev_osd_name);
void rest_event_notify_cec_soundbar_unplugged(unsigned short pa,unsigned char * dev_vndr_id,unsigned char * dev_device_la,unsigned short * dev_osd_name);
//void rest_event_notify_json(const char* uri, const void* response);

#ifdef __cplusplus
}
#endif

#endif

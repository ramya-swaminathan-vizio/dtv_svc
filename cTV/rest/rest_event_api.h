/* dolphin 20200313 use the newly REST-VSSP-PYTHON to replace&cpmpatible the old one */
#ifndef _REST_EVENT_API_H_
#define _REST_EVENT_API_H_

int rest_init_vssp_uri(void);
int rest_vssp_destroy(void);
int rest_search_uri(std::string s_uri,int *i4_n_channel);
int rest_init_offset_handler(int i4_offset ,Json::Value & root, Json::Value & response);
int rest_parse_endpoint_query(const std::string& request, std::map<std::string,std::string>& query);

#endif //_REST_EVENT_API_H_


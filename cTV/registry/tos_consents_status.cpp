
#include "tos_consents_status.h"
#include <string>
#include <thread>

#include <broker.h>
#include <connection.h>
#include <systemregistry.h>

#include <sysreg_wrap.h>
#include <a_jsonrpc.h> 



const char* VIZIO_TOS_URL   = "/current/consent/vizio_tos_and_privacy_policy";
const char* GOOGLE_TOS_URL  = "/current/consent/google_tos_and_privacy_policy";
const char* VIEWING_DATA_URL= "/current/consent/viewing_data";


int getTosbyUrl(bool *b_appept,const char* url)
{
   int ret=-1;
   vizio::systemregistry::SystemRegistry systemRegistry(vizio::ipc::Broker::getDefaultBroker());
   systemRegistry.initialize();
   
   // get the key
   const std::pair<std::string,bool> result = systemRegistry.get(url);
   if(result.second)
   {
       std::string tosJSON = result.first;
       //std::cout << "tosJson" << tosJSON;
       json_parse_consent_status(tosJSON.c_str(),b_appept);
       ret = 0;
   }

   return ret;
}


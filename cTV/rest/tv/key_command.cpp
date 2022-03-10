#include <iostream>
#include "handler.h"
#include "key_command.h"
#include "common.h"

#include "argument.h"


int key_command(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");


    argument::Factory<argument::List<argument::KeyCommand> > &factory = 
        argument::Factory<argument::List<argument::KeyCommand> >::getInstance();

    std::auto_ptr<argument::List<argument::KeyCommand> > list =  factory.create(root);

    int code = list->vector[0].code;
    int codeset = list->vector[0].codeset;
    std::string action = list->vector[0].action;

    REST_LOG_I("Enter %d %d %s \n\r", code, codeset, action.c_str());

    response["VALUE"] = 0;
    
    return 0;
}


handler key_command_handler[] = {
   key_command, 
};



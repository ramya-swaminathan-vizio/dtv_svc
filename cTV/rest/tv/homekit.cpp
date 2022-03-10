#include <stdio.h> //printf
#include <string.h>
#include <stdlib.h> //exit(0);
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "cJSON.h"


#include "handler.h"
#include "common.h"
#include "argument.h"
#include "rest.h"
#include "homekit.h"

#ifdef __cplusplus
extern "C" {
#include "rest_util.h"
#include "rest/a_jsonrpc.h"
#include "rest/a_rest_event.h"
}
#endif

#define BUFLEN 40960
#define IPC_SOCKET_PATH_HOMEKIT "/tmp/homekit_ipc"

int _homekit_send_msg_to_homekit(int i_cmd_type, char* res, int res_buf_len);
void homekit_factory_reset()
{
    REST_LOG_I("Enter\n\r");
    char res_buf[BUFLEN] = {0};
    c_memset(res_buf, 0, BUFLEN);
    _homekit_send_msg_to_homekit(2, res_buf, BUFLEN-1);
}

struct HomekitGroupURI {
    std::string index[URI_INDEX_SIZE];
};

HomekitGroupURI homekitGroupURIs[] = {
	{ "pairing_status" },
	{ "" },
};

void _homekit_send_msg_to_homekit_die(const char *s)
{
    perror(s);
    REST_LOG_E("Error %s\n\r", s);
    //exit(1);
}

int _homekit_send_msg_to_homekit_send_ipc(char* message, char* res, int res_buf_len)
{
    struct sockaddr_un si_other;
    int s;
    //int slen=sizeof(si_other);
    char buf[BUFLEN];

    if ((s=socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        _homekit_send_msg_to_homekit_die(std::string("socket").c_str());
        return -1;
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sun_family = AF_UNIX;
    strncpy(si_other.sun_path, IPC_SOCKET_PATH_HOMEKIT, sizeof(si_other.sun_path)-1);
	if (connect(s, (struct sockaddr *)&si_other, sizeof(struct sockaddr_un)) < 0) {
		_homekit_send_msg_to_homekit_die(std::string("connect!!!").c_str());
        close(s);
        return -1;
	}

    // send the message
    //printf("Send:\n%s\n", message);
    if (write(s, message, strlen(message)) == -1) {
        _homekit_send_msg_to_homekit_die(std::string("sendto()").c_str());
        close(s);
        return -1;
    }

    // receive a reply and print it
    // clear the buffer by filling null, it might have previously received data
    memset(buf, '\0', BUFLEN);

    // try to receive some data, this is a blocking call
    // TODO: modify it to be allow timeout. i.e. poll()
    if (read(s, buf, BUFLEN) == -1) {
        _homekit_send_msg_to_homekit_die(std::string("recvfrom()").c_str());
        close(s);
        return -1;
    }

    //printf("Recv:\n%s\n", buf);
    REST_LOG_I("Recv %s.\n\r", buf);

    c_strncpy(res, buf, res_buf_len);

    close(s);

    return 0;
}

int _homekit_send_msg_to_homekit(int i_cmd_type, char* res, int res_buf_len)
{
    char *message;
    cJSON *root, *ipc;

    root = cJSON_CreateObject();
    switch (i_cmd_type)
    {
        case 1: // pairing_status
        {
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "pairing_status");
            break;
        }
        case 2: // factory_reset
        {
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "factory_reset");
            break;
        }
        default:
            cJSON_Delete(root);
            return 0;
    }

    message = cJSON_Print(root);
    REST_LOG_I("Sending %s\n\r", message);
    _homekit_send_msg_to_homekit_send_ipc(message, res, res_buf_len);

    free(message);
    cJSON_Delete(root);

    if (c_strlen(res) <= 0) {
        REST_LOG_I("No response string.\n\r");
        return 0;
    }

    return 0;
}

bool _homekit_pairing_status()
{
    REST_LOG_I("Enter\n\r");

    bool b_paired = FALSE;
    Json::Value value;

    char res_buf[BUFLEN] = {0};
    c_memset(res_buf, 0, BUFLEN);

    _homekit_send_msg_to_homekit(1, res_buf, BUFLEN-1);

    if (c_strstr(res_buf, "SUCCESS") == NULL) {
        REST_LOG_E("Request to homekit failed.\n\r");
        return -1;
    }

    cJSON *root_res, *j_result, *j_value, *j_key, *j_type, *j_value_value;
    root_res = cJSON_Parse(res_buf);
    if (root_res == NULL) {
        REST_LOG_E("Parse response failed.\n\r");
        return -1;
    }
    j_result = cJSON_GetObjectItem(root_res, "result");
    if (j_result == NULL) {
        REST_LOG_E("Parse j_result failed.\n\r");
        cJSON_Delete(root_res);
        return -1;
    }
    j_value = cJSON_GetObjectItem(j_result, "value");
    if (j_value == NULL) {
        REST_LOG_E("Parse j_value failed.\n\r");
        cJSON_Delete(root_res);
        return -1;
    }
    j_key = cJSON_GetObjectItem(j_value, "key");
    if (j_key == NULL) {
        REST_LOG_E("Parse j_key failed.\n\r");
        cJSON_Delete(root_res);
        return -1;
    }
    j_type = cJSON_GetObjectItem(j_value, "type");
    if (j_type == NULL) {
        REST_LOG_E("Parse j_type failed.\n\r");
        cJSON_Delete(root_res);
        return -1;
    }
    j_value_value = cJSON_GetObjectItem(j_value, "value");
    if (j_type == NULL) {
        REST_LOG_E("Parse j_value_value failed.\n\r");
        cJSON_Delete(root_res);
        return -1;
    }

    // RETURN: int (Enum.HK_PAIRING_STATUS = {'PAIRED', 'NOT_PAIRED'}) 
    b_paired = (j_value_value->valueint == 0 ? FALSE : TRUE);
    REST_LOG_I("paired: %d\n\r", b_paired);

    cJSON_Delete(root_res);

    return b_paired;
}

int pairing_status(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            bool b_paired = _homekit_pairing_status();
            // RETURN: int (Enum.HK_PAIRING_STATUS = {'PAIRED', 'NOT_PAIRED'}) 
            response["VALUE"] = b_paired ? 0 : 1;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET. Not Implemented.\n\r");
            break;
        }
        default:
            break;
    }

	return 0;
}

handler homekit_handler[] = {
    pairing_status,
};



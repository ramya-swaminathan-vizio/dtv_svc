#include <mqueue.h>
#include <errno.h>
#include "rest/metrics/bootsc_metrics.h"
#include <string.h>
#include <stdio.h>
#include "u_common.h"

#define MESSAGE_SIZE 256
#define MESSAGE_TYPE_BOOTSCMETRIC 1

static mqd_t message_queue = -1;
message globalMetrics = {};
message startBootSCMetricsLog()
{
    return globalMetrics;
}

message setInputFrom(message metrics, char* input_from)
{
    strcpy(metrics.bootSCMetric.inputFrom, input_from);
    return metrics;
}

message setInputTo(message metrics, char* input_to)
{
    strcpy(metrics.bootSCMetric.inputTo, input_to);
    return metrics;
}

message setScenario(message metrics, char* scenario)
{
    strcpy(metrics.bootSCMetric.scenario, scenario);
    return metrics;
}

message setUserAction(message metrics, char* user_action)
{
    strcpy(metrics.bootSCMetric.userAction, user_action);
    return metrics;
}

message setPowerOnInputSetting(message metrics, char* power_on_input_setting)
{
    printf("BOOTSCMETRICS setPowerOnInputSetting - power_on_input_setting = %s\n",power_on_input_setting);
    strcpy(metrics.bootSCMetric.powerOnInputSetting, power_on_input_setting);
    return metrics;
}

void showLog(message metrics)
{
    printf("BOOTSCMETRICS: inputFrom: %s\n",metrics.bootSCMetric.inputFrom);
    printf("BOOTSCMETRICS: inputTo: %s\n",metrics.bootSCMetric.inputTo);
    printf("BOOTSCMETRICS: powerOnInputSetting: %s\n",metrics.bootSCMetric.powerOnInputSetting);
    printf("BOOTSCMETRICS: userAction: %s\n",metrics.bootSCMetric.userAction);
    printf("BOOTSCMETRICS: scenario: %s\n",metrics.bootSCMetric.scenario);

}

void sendLog(message metrics)
{
    const char* MESSAGE_QUEUE_NAME = "/sentry_logger";
    struct mq_attr attr;
    attr.mq_maxmsg = 3;
    attr.mq_msgsize = MESSAGE_SIZE;
    message_queue = mq_open(MESSAGE_QUEUE_NAME, O_WRONLY | O_NONBLOCK | O_CREAT, 0777, &attr);
    if (message_queue == -1) {
        printf("BOOTSC Failed to open %s: %d\n",
                MESSAGE_QUEUE_NAME, errno);
        return;
    } else {
        printf("BOOTSC Opened %s\n",
                MESSAGE_QUEUE_NAME);
    }

    metrics.messageType = MESSAGE_TYPE_BOOTSCMETRIC;

    while (mq_send(message_queue, (void*)&metrics, sizeof(metrics), 0) < 0) {
        if (errno != EINTR) {
            printf("BOOTSC Failed sending: %d\n", errno);
            return;
        }
    }
    printf("BOOTSC sendLog END\n");
}

const char* powerOnIndexToText(Enu_POWER_ON_INPUT index) 
{
    printf("BOOTSC powerOnIndexToText index: %d\n",index);
    switch(index) {
    case E_POWER_ON_INP_AUTOMATIC:
        printf("BOOTSC AUTOMATIC\n");
        return "AUTOMATIC";
        break;
    case E_POWER_ON_INP_SMARTCAST:
        return "SMARTCAST";
        break;
    case E_POWER_ON_INP_HDMI1:
        return "HDMI-1";;
        break;
    case E_POWER_ON_INP_HDMI2:
        return "HDMI-2";
        break;
    case E_POWER_ON_INP_HDMI3:
        return "HDMI-3";
        break;
    case E_POWER_ON_INP_HDMI4:
        return "HDMI-4";
        break;
    case E_POWER_ON_INP_PREVIOUS_INPUT:
        return "PREVIOUS";
        break;
    case E_POWER_ON_INP_AIRPLAY:
        return "AIRPLAY";
        break;
    case E_POWER_ON_INP_ANTENNA:
        return "ANTENNA";
        break;
    case E_POWER_ON_INP_COMPOSITE:
        return "COMPOSITE";
        break;
    default:
        return "";
    }
    return "";
}

static UINT8 _smartcast_index()
{
    ISL_REC_T t_isl_rec = {0};
    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);
    UINT16 hdmi_port_count = (UINT16)t_isl_rec.ui1_iid_count;
    return hdmi_port_count + 3;
}

static UINT8 _airplay_index()
{
    return _smartcast_index() + 1;
}

const char* inputSwitchFromText(UINT8 index) 
{
    if (index == _smartcast_index()) {
        return "SMARTCAST";
    }

    if (index == _airplay_index()) {
        return "AIRPLAY";
    }

    switch(index) {
    case 0:
        return "ANTENNA";
        break;
    case 1:
        return "COMPOSITE";
        break;
    case 2:
        return "HDMI-1";
        break;
    case 3:
        return "HDMI-2";
        break;
    case 4:
        return "HDMI-3";;
        break;
    case 5:
        return "HDMI-4";
        break;
    default:
        return "";
    }
    return "";
}


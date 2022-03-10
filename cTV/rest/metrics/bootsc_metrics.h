#ifndef BOOTSC_METRICS_H
#define BOOTSC_METRICS_H

#include <string.h>
#include "menu2/menu_common/menu_common.h"

typedef enum _SWTICH_SCENARIO
{
    E_SCENARIO_EMPTY,
    E_SCENARIO_POWER_ON,
    E_SCENARIO_INPUT_SWITCH
} Enu_SWITCH_SCENARIO_LOG;

typedef enum _USER_ACTION
{
    E_USER_ACTION_EMPTY,
    E_USER_ACTION_HOME,
    E_USER_ACTION_CANCEL,
    E_USER_ACTION_ALLOW
} _Enu_USER_ACTION_LOG;


typedef enum _POWER_ON_INPUT_LOG
{
    E_POWER_ON_INP_EMPTY_LOG,
    E_POWER_ON_INP_AUTOMATIC_LOG,
    E_POWER_ON_INP_SMARTCAST_LOG,
    E_POWER_ON_INP_HDMI1_LOG,
    E_POWER_ON_INP_HDMI2_LOG,
    E_POWER_ON_INP_HDMI3_LOG,
    E_POWER_ON_INP_HDMI4_LOG,
    E_POWER_ON_INP_PREVIOUS_INPUT_LOG,
    E_POWER_ON_INP_AIRPLAY_LOG,
    E_POWER_ON_INP_ANTENNA_LOG,
    E_POWER_ON_INP_COMPOSITE_LOG
} Enu_POWER_ON_INPUT_LOG;


typedef struct _BOOTSC_METRICS_LOGGER
{
    char input_from[10];
    char input_to[10];
    Enu_SWITCH_SCENARIO_LOG scenario;
    _Enu_USER_ACTION_LOG user_action;
    Enu_POWER_ON_INPUT_LOG power_on_input_setting;
    char* log_string;
} BOOTSC_METRICS_LOGGER;

struct BootSCMetric {
    char inputFrom[32];
    char inputTo[32];
    char powerOnInputSetting[32];
    char userAction[16];
    char scenario[16];
};

typedef struct _message {
    uint32_t messageType;
    union {
        struct BootSCMetric bootSCMetric;
    };
} message;

message startBootSCMetricsLog();
message setInputFrom(message metrics, char* input_from);
message setInputTo(message metrics, char* input_to);
message setScenario(message metrics, char* scenario);
message setUserAction(message metrics, char* user_action);
message setPowerOnInputSetting(message metrics, char* power_on_input_setting);
void showLog(message metrics);
void sendLog(message metrics);
const char* powerOnIndexToText(Enu_POWER_ON_INPUT index);
const char* inputSwitchFromText(UINT8 index);
#endif

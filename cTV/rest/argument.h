#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <string>
#include <list>
#include <bits/unique_ptr.h>

#include "json/json.h"


#include <memory>





namespace argument {
    /* Type Identifier */
    static const int TYPE_MENU_V1 = 1;
    static const int TYPE_MENU_X_V1 = 2;
    static const int TYPE_LIST_V1 = 3;
    static const int TYPE_LIST_X_V1 = 4;
    static const int TYPE_LIST_VALUES_V1 = 5;
    static const int TYPE_VALUE_ABS_V1 = 6;
    static const int TYPE_VALUE_V1 = 7;
    static const int TYPE_STRING_V1 = 8;
    static const int TYPE_PIN_V1 = 9;
    static const int TYPE_EMAIL_V1 = 10;
    static const int TYPE_IP_ADDRESS_V1 = 11;
    static const int TYPE_MAC_ADDRESS_V1 = 12;
    static const int TYPE_DATE_V1 = 13;
    static const int TYPE_MATRIX_V1 = 14;
    static const int TYPE_ROW_V1 = 15;
    static const int TYPE_HEADER_V1 = 16;
    static const int TYPE_ACTION_V1 = 17;
    static const int TYPE_ARRAY_V1 = 18;
    static const int TYPE_DEVICE_V1 = 19;
    static const int TYPE_APS_V1 = 20;
    static const int TYPE_AP_V1 = 21;
    static const int TYPE_TEST_CONNECTION_V1 = 22;
    static const int TYPE_CEC_DEVICE_V1 = 23;
    static const int TYPE_LIST_CEC_DEVICE_V1 = 24;
    static const int TYPE_VIZIO_DEVICE_INFO_V1 = 25;
    static const int TYPE_IETF_2822_STRING_V1 = 26;


    /* Group Identifier */
    static const int picture = 1;
    static const int adv_picture = 2;
    static const int position = 3;
    static const int prof_picture = 4;
    static const int color_tuner = 5;
    static const int white_balance = 6;
    static const int audio_group = 7;
    static const int audio_mode_group = 8;

    /* Token Identifier */
    struct TokenIdentifier
    {
        std::string token;
        int value;
    };

    struct RequestType
    {
        RequestType(Json::Value & root);
        int type;

        /* reuqest type */
        static const int REQUEST_GET   = 1;
        static const int REQUEST_SET   = 2;
        static const int REQUEST_RESET = 3;
        static const int REQUEST_ACTION = 4;
    };

    struct Menu {
        Menu(){};
        Menu(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct MenuX {
        MenuX(){};
        MenuX(Json::Value & value);
        Json::Value toJsonValue();
    };

    template<typename T>
    struct List {
        List<T>(){};
        std::vector<T> vector;

	List<T>(Json::Value & value);
	Json::Value toJsonValue();
    };

    template<class T>
	List<T>::List(Json::Value & value)
	{
	    Json::Value elements = value["ELEMENTS"];

		for (unsigned int i = 0; i < elements.size(); i++) {
			T t(elements[i]);
			vector.push_back(t);
		}

	}

	template<class T>
	Json::Value List<T>::toJsonValue()
	{
		Json::Value value;

		for (unsigned int i = 0; i < vector.size(); i++)
		{
			Json::Value v = vector[i].toJsonValue();
			value[i] = v;
		}

		return value;
	}


    struct ListX {
        ListX(){};
        ListX(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct ListValues {
		std::vector<int> values;

        ListValues(){};
        ListValues(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct ValueAbs {
		int value;
        ValueAbs(){};
        ValueAbs(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Value {
        int value;

        Value(){};
        Value(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct String {
        std::string str;

        String(){};
        String(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Pin {
        Pin(){};
        Pin(Json::Value & value);
        Json::Value toJsonValue();
    };
    struct Email {
        Email(){};
        Email(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct IpAddress {
        std::string ip;

        IpAddress(){};
        IpAddress(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct MacAddress {
        std::string mac;

        MacAddress(){};
        MacAddress(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Date {
        Date(){};
        Date(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Matrix {
        Matrix(){};
        Matrix(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Row {
        Row(){};
        Row(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Header {
        Header(){};
        Header(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Action {
        Action(){};
        Action(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Array {
        Array(){};
        Array(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Device {
        /*"NAME": <string>,
        "METADATA" : <string>,*/
        std::string name;
        std::string metadata;

        Device(){};
        Device(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct App {
        /*"NAME" : "My First Network",
        "RSSI" : 5,
        "BAND" : "2.4 GHz"
        "EM" : "WPA/TKIP",
        "BSSID" : "67abc7-54a765",
        "CONNECTED" : "TRUE"*/
        std::string name;
        int rssi;
        std::string band;
        std::string em;
        std::string bssid;
        std::string connected;

        App(){};
        App(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Aps {
        std::vector<App> aps;

        Aps(){};
        Aps(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Ap {
        /*"NAME" : <string>,
        "RSSI" : <value>,
        "BAND" : <string>,
        "EM" : <string>,
        "BSSID" : <string>,
        "OPEN" : <string>,
        "PASSWORD" : <string>*/
        std::string name;
        int rssi;
        std::string band;
        std::string em;
        std::string bssid;
        std::string open;
        std::string password;

        Ap(){};
        Ap(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct TestConnection {
        /*"ESTABLISHED DNS SERVERS" : <string>, [true | false]
        "ESTABLISHED NTP SERVER" : <string>, [true | false]
        "CONNECTION METHOD" : <string>, [Ethernet | WiFi]
        "CONNECTION SPEED" : <value>,
        "SSID NAME" : <string>,
        "ERROR_CODE" : <string>*/
        std::string eDnsServer;
        std::string eNtpServer;
        std::string connectionMethod;
        double connectionSpeed;
        std::string ssidName;
        std::string errorCode;

        TestConnection(){};
        TestConnection(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct ManualIpConfig {
        /*"DHCP_MODE" : T_STRING_V1 from items in L_DHCP_MODES
        "IP_ADDRESS" : T_IP_ADDRESS_V1
        "SUBNET_MASK" : T_IP_ADDRESS_V1
        "DEFAULT_GATEWAY" : T_IP_ADDRESS_V1
        "PREF_DNS" : T_IP_ADDRESS_V1
        "ALT_DNS" : T_IP_ADDRESS_V1
        "RJ45_MAC" : T_STRING_V1
        "WIFI_MAC" : T_STRING_V1*/

        ManualIpConfig(){};
        ManualIpConfig(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct CecDevice {
        /*OSDName: <string> --from section 11.9.10 of HDMI Spec v2.
        LogicalAddress : <string> --from section 11.3.2 of HDMI Spec v2.
        PrimaryDeviceType : <string>  --see table below
        VendorId : <string>  --from section 11.8 of HDMI Spec v2. "" if none
        Children : TYPE_LIST_CEC_DEVICE_V1  -- any devices attached to the device - Empty if none*/
        std::string osdname;
        std::string logicalAddress;
        std::string primaryDeviceType;
        std::string vendorId;
		std::vector <CecDevice> list;

        CecDevice(){};
        CecDevice(Json::Value & value);

        Json::Value toJsonValue();

    };

    struct ListCecDevice {
        ListCecDevice(){};
        ListCecDevice(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct VizioDeviceInfo {
        /*"NAME" : <string> --cast device name
        "MODEL_NAME" : <string> --friendly model name               e.g., P - Series 50, E - Series 32
        "SETTINGS_ROOT" : <string> --root of settings tree(e.g., "tv_settings", "audio_settings")
        "API_VERSION" : <string> --version of ReST
        "INPUTS" : LIST_X_V1 -- the URI cnames(e.g., hdmi1, hdmi2, etc.)
        "SYSTEM_PICTURE_MODES" : LIST_X_V1  -- list of non - custom picture modes without the "*" indicating it has changed.
        "CAPABILITIES" : LIST_X_V1  -- list of device capabilities(e.g., ��tvtuner��, ��uhd��, ��audio5.1��, ��audio2.0��, ��hdmiarc��, etc.)*/

        VizioDeviceInfo(){};
        VizioDeviceInfo(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct Ietf2822String {
        Ietf2822String(){};
        Ietf2822String(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct KeyCommand {
        /*codesetVal  = key.get('CODESET')
        codeVal     = key.get('CODE')
        actionVal   = key.get('ACTION')
        modifierVal = key.get('MODIFIER')*/
        int codeset;
        int code;
        std::string action;
        std::string modifier;

        KeyCommand(){};
        KeyCommand(Json::Value & value);
        Json::Value toJsonValue();
    };

    struct ChannelSettings{
        /*
            # CHANNEL : <string> -- the channel number of the channel which is either an integer ("8") or a sub channel format ("8.1").
            # DIGITAL : <value> --0 if analog, 1 if digital
            # LOCKED : <value> -- 0 if not locked by parental controls, 1 if locked by parental controls
            # NAME : <string> -- Friendly name of channel if one is set by the user (e.g., "NBC")
            # SKIPPED : <value> -- 0 if not skipped, 1 if skipped [OPTIONAL]
        */
        std::string channel;
        int digital;
        int locked;
        std::string name;
        int skipped;

        ChannelSettings(){};
        ChannelSettings(Json::Value & value);
        Json::Value toJsonValue();
    };

    template<class T>
    class Factory
    {
    private:
        Factory<T>();
    public:
        static Factory<T> & getInstance();

    public:
        std::auto_ptr<T> create(Json::Value & root);

        Json::Value create(T & t);

        RequestType getType(Json::Value & root);
    private:
        static Factory<T> factory;
    };

    template<class T>
    RequestType argument::Factory<T>::getType( Json::Value & root )
    {
        return RequestType(root);
    }

    template<class T>
    Json::Value argument::Factory<T>::create(T & t)
    {
        return t.toJsonValue();
    }

    template<class T> Factory<T> Factory<T>::factory;

    template<class T>
    Factory<T>::Factory()
    {
    }


    template<class T>
    Factory<T> & argument::Factory<T>::getInstance()
    {
        return factory;
    }

    template<class T>
    std::auto_ptr<T> Factory<T>::create(Json::Value & root)
    {
        Json::Value value = root["message"];
        return std::auto_ptr<T>(new T(value));
    }

};


#endif /* ARGUMENT_H */


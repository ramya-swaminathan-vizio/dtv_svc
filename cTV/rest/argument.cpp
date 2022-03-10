#include "argument.h"
#include <iostream>

namespace argument {
    TokenIdentifier tis[] = {
        { "5_%"         ,         0x8001 },
        { "10_%"         ,         0x8002 },
        { "20%"         ,         0x8003 },
        { "30%"         ,         0x8004 },
        { "40%"         ,         0x8005 },
        { "50%"         ,         0x8006 },
        { "60%"         ,         0x8007 },
        { "70%"         ,         0x8008 },
        { "80%"         ,         0x8009 },
        { "90%"         ,         0x8010 },
        { "100%"         ,         0x8011 },
        { "2D"         ,         0x8012 },
        { "Auto"         ,         0x8013 },
        { "Bass"         ,         0x8014 },
        { "Bitstream"         ,         0x8015 },
        { "Blue"         ,         0x8016 },
        { "Boost"         ,         0x8017 },
        { "Bright"         ,         0x8018 },
        { "Bright"         ,         0x8019 },
        { "Calibrated"         ,         0x8020 },
        { "Calibrated Dark"         ,         0x8021 },
        { "Cancel"         ,         0x8022 },
        { "Center"         ,         0x8023 },
        { "Comp"         ,         0x8024 },
        { "Computer"         ,         0x8025 },
        { "Computer(9300K)"         ,         0x8026 },
        { "Cool(11000)"         ,         0x8027 },
        { "Custom"         ,         0x8028 },
        { "Custom-1"         ,         0x8029 },
        { "Custom-2"         ,         0x8030 },
        { "Custom-3"         ,         0x8031 },
        { "Custom-4"         ,         0x8032 },
        { "Custom-5"         ,         0x8033 },
        { "Custom-6"         ,         0x8034 },
        { "Custom-7"         ,         0x8035 },
        { "Custom-8"         ,         0x8036 },
        { "Dim"         ,         0x8037 },
        { "Down"         ,         0x8038 },
        { "Dynamic"         ,         0x8039 },
        { "Fixed"         ,         0x8040 },
        { "Flat"         ,         0x8041 },
        { "Forward"         ,         0x8042 },
        { "Game"         ,         0x8043 },
        { "Green"         ,         0x8044 },
        { "HDMI-1"         ,         0x8045 },
        { "HDMI-2"         ,         0x8046 },
        { "HDMI-3"         ,         0x8047 },
        { "HDMI-4"         ,         0x8048 },
        { "High"         ,         0x8049 },
        { "Low"         ,         0x8050 },
        { "Medium"         ,         0x8051 },
        { "Medium"         ,         0x8052 },
        { "No"         ,         0x8053 },
        { "Normal"         ,         0x8054 },
        { "Normal(6500K)"         ,         0x8055 },
        { "Off"         ,         0x8056 },
        { "On"         ,         0x8057 },
        { "Panoramic"         ,         0x8058 },
        { "Pause"         ,         0x8059 },
        { "PCM"         ,         0x8060 },
        { "Play"         ,         0x8061 },
        { "Red"         ,         0x8062 },
        { "Reset"         ,         0x8063 },
        { "Rewind"         ,         0x8064 },
        { "Sensio"         ,         0x8065 },
        { "Side-By-Side"         ,         0x8066 },
        { "Standard"         ,         0x8067 },
        { "Stop"         ,         0x8068 },
        { "Stretch"         ,         0x8069 },
        { "Top-Bottom"         ,         0x8070 },
        { "TV"         ,         0x8071 },
        { "Up"         ,         0x8072 },
        { "Variable"         ,         0x8073 },
        { "Vivid"         ,         0x8074 },
        { "White"         ,         0x8075 },
        { "Wide"         ,         0x8076 },
        { "Yes"         ,         0x8077 },
        { "Zoom"         ,         0x8078 },

    };






    Menu::Menu(Json::Value & value)
    {

    }


    Json::Value Menu::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    MenuX::MenuX(Json::Value & value)
    {

    }


    Json::Value MenuX::toJsonValue()
    {
        Json::Value value;
        return value;
    }



    ListX::ListX(Json::Value & value)
    {

    }


    Json::Value ListX::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    ListValues::ListValues(Json::Value & value)
    {

    }


    Json::Value ListValues::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    ValueAbs::ValueAbs(Json::Value & value)
    {
		this->value=value["VALUE"].asInt();
    }


    Json::Value ValueAbs::toJsonValue()
    {
        Json::Value value;
		value = this->value;
        return value;
    }

    Value::Value(Json::Value & value)
    {
        this->value=value["VALUE"].asInt();
    }


    Json::Value Value::toJsonValue()
    {
        Json::Value value;
        value = this->value;

        return value;
    }

    String::String(Json::Value & value)
    {
        this->str = value["VALUE"].asString();
    }


    Json::Value String::toJsonValue()
    {
        Json::Value value;
        value = this->str;
        return value;
    }

    Pin::Pin(Json::Value & value)
    {

    }


    Json::Value Pin::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Email::Email(Json::Value & value)
    {

    }


    Json::Value Email::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    IpAddress::IpAddress(Json::Value & value)
    {

    }


    Json::Value IpAddress::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    MacAddress::MacAddress(Json::Value & value)
    {

    }


    Json::Value MacAddress::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Date::Date(Json::Value & value)
    {

    }


    Json::Value Date::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Matrix::Matrix(Json::Value & value)
    {

    }


    Json::Value Matrix::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Row::Row(Json::Value & value)
    {

    }


    Json::Value Row::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Header::Header(Json::Value & value)
    {

    }


    Json::Value Header::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Action::Action(Json::Value & value)
    {

    }


    Json::Value Action::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Array::Array(Json::Value & value)
    {

    }


    Json::Value Array::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Device::Device(Json::Value & value)
    {
        /*"NAME": <string>,
        "METADATA" : <string>,*/
        name = value["NAME"].asCString();
        metadata = value["METADATA"].asCString();
    }



    Json::Value Device::toJsonValue()
    {
        Json::Value value;

        value["NAME"] = name;
        value["METADATA"] = metadata;

        return value;
    }

    App::App(Json::Value & value)
    {
        /*"NAME" : "My First Network",
        "RSSI" : 5,
        "BAND" : "2.4 GHz"
        "EM" : "WPA/TKIP",
        "BSSID" : "67abc7-54a765",
        "CONNECTED" : "TRUE"*/
        name = value["NAME"].asCString();
        rssi = value["RSSI"].asInt();
        band = value["BAND"].asCString();
        em = value["EM"].asCString();
        bssid = value["BSSID"].asCString();
        connected = value["CONNECTED"].empty() ? "FALSE" : value["CONNECTED"].asCString();
    }



    Json::Value App::toJsonValue()
    {
        Json::Value value;

        value["NAME"] = name;
        value["RSSI"] = rssi;
        value["BAND"] = band;
        value["EM"] = em;
        value["BSSID"] = bssid;
        value["CONNECTED"] = connected;
        return value;
    }

    Aps::Aps(Json::Value & value)
    {
		for (unsigned int i = 0; i < value.size(); i++)
        {
			Json::Value item = value[i];
            aps.push_back(App(item));
        }
    }


    Json::Value Aps::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Ap::Ap(Json::Value & value)
    {
        /*"NAME" : <string>,
        "RSSI" : <value>,
        "BAND" : <string>,
        "EM" : <string>,
        "BSSID" : <string>,
        "OPEN" : <string>,
        "PASSWORD" : <string>*/
        name = value["NAME"].asCString();
        rssi = value["RSSI"].asInt();
        band = value["BAND"].asCString();
        em = value["EM"].asCString();
        bssid = value["BSSID"].asCString();
        open = value["OPEN"].asCString();
        password = value["PASSWORD"].asCString();
    }


    Json::Value Ap::toJsonValue()
    {
        Json::Value value;

        value["NAME"] = name;
        value["RSSI"] = rssi;
        value["BAND"] = band;
        value["EM"] = em;
        value["BSSID"] = bssid;
        value["OPEN"] = open;
        value["PASSWORD"] = password;

        return value;
    }

    TestConnection::TestConnection(Json::Value & value)
    {
        /*"ESTABLISHED DNS SERVERS" : <string>, [true | false]
        "ESTABLISHED NTP SERVER" : <string>, [true | false]
        "CONNECTION METHOD" : <string>, [Ethernet | WiFi]
        "CONNECTION SPEED" : <value>,
        "SSID NAME" : <string>,
        "ERROR_CODE" : <string>*/
        eDnsServer = value["ESTABLISHED DNS SERVERS"].asCString();
        eNtpServer = value["ESTABLISHED NTP SERVER"].asCString();
        connectionMethod = value["CONNECTION METHOD"].asCString();
        connectionSpeed = value["CONNECTION SPEED"].asDouble();
        ssidName = value["SSID NAME"].asCString();
        errorCode = value["ERROR_CODE"].asCString();

    }


    Json::Value TestConnection::toJsonValue()
    {
        Json::Value value;

        value["ESTABLISHED DNS SERVERS"] = eDnsServer;
        value["ESTABLISHED NTP SERVER"] = eNtpServer;
        value["CONNECTION METHOD"] = connectionMethod;
        value["CONNECTION SPEED"] = connectionSpeed;
        value["SSID NAME"] = ssidName;
        value["ERROR_CODE"] = errorCode;

        return value;
    }

    ManualIpConfig::ManualIpConfig(Json::Value & value)
    {

    }


    Json::Value ManualIpConfig::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    CecDevice::CecDevice(Json::Value & value)
    {
        /*OSDName: <string> --from section 11.9.10 of HDMI Spec v2.
        LogicalAddress : <string> --from section 11.3.2 of HDMI Spec v2.
        PrimaryDeviceType : <string>  --see table below
        VendorId : <string>  --from section 11.8 of HDMI Spec v2. "" if none
        Children : TYPE_LIST_CEC_DEVICE_V1  -- any devices attached to the device - Empty if none*/
        osdname = value["OSDName"].asCString();
        logicalAddress = value["LogicalAddress"].asCString();
        primaryDeviceType = value["PrimaryDeviceType"].asCString();
        vendorId = value["VendorId"].asCString();

        Json::Value children = value["Children"];

        for (unsigned int i = 0; i < children.size(); i++)
        {
            list.push_back(CecDevice(children[i]));
        }
    }


    Json::Value CecDevice::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    ListCecDevice::ListCecDevice(Json::Value & value)
    {

    }


    Json::Value ListCecDevice::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    VizioDeviceInfo::VizioDeviceInfo(Json::Value & value)
    {

    }


    Json::Value VizioDeviceInfo::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    Ietf2822String::Ietf2822String(Json::Value & value)
    {

    }

    Json::Value Ietf2822String::toJsonValue()
    {
        Json::Value value;
        return value;
    }

    KeyCommand::KeyCommand(Json::Value & value)
    {
        /*codesetVal  = key.get('CODESET')
        codeVal     = key.get('CODE')
        actionVal   = key.get('ACTION')
        modifierVal = key.get('MODIFIER')*/

        codeset = value["CODESET"].asInt();
        code = value["CODE"].asInt();
        action = value["ACTION"].asCString();
        modifier = value["MODIFIER"].empty() ? "" : value["MODIFIER"].asCString();
    }



    Json::Value KeyCommand::toJsonValue()
    {
        Json::Value value;

        value["CODESET"] = codeset;
        value["CODE"] = code;
        value["ACTION"] = action;
        value["MODIFIER"] = modifier;

        return value;
    }


    ChannelSettings::ChannelSettings(Json::Value & value)
    {
        /*
            # CHANNEL : <string> -- the channel number of the channel which is either an integer ("8") or a sub channel format ("8.1").
            # DIGITAL : <value> --0 if analog, 1 if digital
            # LOCKED : <value> -- 0 if not locked by parental controls, 1 if locked by parental controls
            # NAME : <string> -- Friendly name of channel if one is set by the user (e.g., "NBC")
            # SKIPPED : <value> -- 0 if not skipped, 1 if skipped [OPTIONAL]
        */

        channel = value["CHANNEL"].asCString();
        digital = value["DIGITAL"].asInt();
        locked = value["LOCKED"].asInt();
        name = value["NAME"].asCString();
        skipped = value["SKIPPED"].asInt();
    }



    Json::Value ChannelSettings::toJsonValue()
    {
        Json::Value value;

        value["CHANNEL"] = channel;
        value["DIGITAL"] = digital;
        value["LOCKED"] = locked;
        value["NAME"] = name;
        value["SKIPPED"]= skipped;

        return value;
    }



    RequestType::RequestType( Json::Value & root )
    {
        type = root["type"].asInt();
    }
};


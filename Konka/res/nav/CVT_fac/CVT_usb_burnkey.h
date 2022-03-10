#ifndef CVT_USB_BURNKEY_H
#define CVT_USB_BURNKEY_H

#define KEYID_BEIGIN_CH_HDCP1X        '_'
#define KEYID_END_CH_HDCP1X           '.'
#define KEYID_BEIGIN_CH_HDCP2X        '_'
#define KEYID_END_CH_HDCP2X           '.'
#define KEYID_BEIGIN_CH_ULPK          '-'
#define KEYID_END_CH_ULPK             '.'
#define KEYID_BEIGIN_CH_POTK          '-'
#define KEYID_END_CH_POTK             '.'
#define BURNKEY_SN_FOLDER_NAME        "sn"
#define BURNKEY_HDCP1X_FOLDER_NAME    "hdcp_key"
#define BURNKEY_HDCP2X_FOLDER_NAME    "hdcp2_key"
#define BURNKEY_ULPK_FOLDER_NAME      "ulpk"
#define BURNKEY_POTK_FOLDER_NAME      "potk"

typedef enum{
    HDCP1x = 0,
    HDCP20,
    HDCP22,
} ENUM_HDCP_TYPE;

INT32 CVT_USB_Burnkey_SN(void);
INT32 CVT_USB_Burnkey_HDCP(ENUM_HDCP_TYPE hdcpType);
INT32 CVT_USB_Burnkey_ULPKPOTK(void);

#endif

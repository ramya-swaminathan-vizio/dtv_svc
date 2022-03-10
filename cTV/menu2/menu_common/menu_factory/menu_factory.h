#ifndef _MENU_FACTORY_H_
#define _MENU_FACTORY_H_

typedef enum  
{
	FACTORY_API_OK =0,
	FACTORY_API_Error,
	FACTORY_API_NoSupport,
	FACTORY_API_ErrCode03,
	FACTORY_API_ErrCode04,
	FACTORY_API_ErrCode05,
		
} FACTORY_API_RESULT;

#ifndef APP_LARGE_EEPROM_SUPPORT
#define FACTORY_BURNING_MODE_EEP_ADDR                   0x1C87
#else   
#define FACTORY_BURNING_MODE_EEP_ADDR                   0x1a3af
#endif

VOID _set_fac_power_status(UINT16 ui2_id);
UINT16 _get_fac_power_status(VOID);

//DTV00721215

#endif

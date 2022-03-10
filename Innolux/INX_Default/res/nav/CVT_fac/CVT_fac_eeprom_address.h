#ifndef _CVT_FAC_EEPROM_ADDRESS_H_
#define _CVT_FAC_EEPROM_ADDRESS_H_

#define    PLF_OPT_MODEL_NAME_LEN (16 + 1) /**< plus 1 '\0' */

#define	   EEP_CVTE_EEP_ADDR_BEGIN						0x1A022


/**COMMON_*********This address used by both cvte and Innolux,Please do not modify******************/
#define    COMMON_EEP_INX_BURNING_MODE_FLAG   					EEP_CVTE_EEP_ADDR_BEGIN
/********************************************************************************************/

#define    EEP_CVTE_BURNING_MODE_FLAG  					0x1A023
#define    EEP_CVTE_RESET_FLAG         					0x1A024

#define    EEP_CVTE_BORCODE_LEN							0x1A025
#define    EEP_CVTE_BORCODE            					0x1A026
#define    EEP_CVTE_BORCODE_END        					(EEP_CVTE_BORCODE + 25)         	// 0x1A03F

#define    EEP_CVTE_BURNING_MODE_TIME  					EEP_CVTE_BORCODE_END+1     			//0x1A040
#define    EEP_CVTE_BURNING_MODE_TIME_END   			(EEP_CVTE_BURNING_MODE_TIME + 4)    //0x1A044

// Not used: [0x1A045, 0x1A053]

#define    EEP_CVTE_HDCP_1_X_FILE_ID   					0x1A054
#define    EEP_CVTE_HDCP_1_X_FILE_ID_END    			(EEP_CVTE_HDCP_1_X_FILE_ID + 4)     // 0x1A058

#define    EEP_CVTE_HDCP_2_2_FILE_ID   					0x1A059
#define    EEP_CVTE_HDCP_2_2_FILE_ID_END    			(EEP_CVTE_HDCP_2_2_FILE_ID + 4)     // 0x1A05D

/*COMMON_**********This address used by both cvte and Innolux,Please do not modify******************/
#define    COMMON_EEP_CVTE_POWER_MODE_FLAG    			(EEP_CVTE_HDCP_2_2_FILE_ID_END + 1) 	// 0x1A05E 
/********************************************************************************************/

#define    EEP_CVTE_EEP_ADDR_END    					COMMON_EEP_CVTE_POWER_MODE_FLAG+1

#define    COMMON_EEP_CVTE_AC_ON_DISP_FLAG              (0xFFE0B)

#endif /* _CVT_FAC_EEPROM_ADDRESS_H_ */

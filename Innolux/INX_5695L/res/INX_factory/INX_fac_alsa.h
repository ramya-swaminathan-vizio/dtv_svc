#ifndef _INX_FAC_ALSA_H_
#define _INX_FAC_ALSA_H_

#include<stdio.h>
#include<stdlib.h>


#define SND_ERR_MSG -1
#define SND_OK_MSG   0
#define LIB_ALSA_PATH "/application/mwlib/libasound.so"
#define RMS_PATH 	  "/sys/class/voicep/dbmdx/rms"
#define SND_DEBUG_MSG(val)  \
			if(val != SND_OK_MSG)		\
			{				\
				printf("[INX-AT] error : %s,%d : i4_ret = %d",__FUNCTION__,__LINE__,val); \
			}	


typedef enum
{
	E_MIXER_OPEN,
	E_MIXER_CLOSE,
	E_SND_CTL_ELEM_INFO_GET,
	E_SND_CTL_ELEM_INFO_SET,
	E_SND_CTL_ELEM_INFO_GET_ITEM_NAME,
	E_SND_CTL_ELEM_INFO,
	E_SND_CTL_ELEM_ID_ALLOCA,
	E_SND_CTL_ELEM_VALUE_ALLOCA,
	E_SND_CTL_ELEM_INFO_ALLOCA,
	E_SND_CTL_ELEM_ID_SET_INTERFACE,
	E_SND_CTL_ELEM_ID_SET_NAME,
	E_SND_CTL_ELEM_INFO_SET_ID,
	E_SND_CTL_ELEM_INFO_GET_ID,
	E_SND_CTL_ELEM_INFO_GET_TYPE,
	E_SND_CTL_ELEM_VALUE_SET_ID,
	E_SND_CTL_ELEM_VALUE_SET_BOOLEAN,
	E_SND_CTL_ELEM_VALUE_SET_INTERGER,
	E_SND_CTL_ELEM_VALUE_SET_ENUM,
	E_SND_CTL_ELEM_WRITE,
	E_SND_CTL_ELEM_INFO_SIZEOF,
	E_SND_CTL_ELEM_ID_SIZEOF,
	E_SND_CTL_ELEM_VALUE_SIZEOF,
	E_MIXER_END,
}E_SND_MIXER_CTL;
typedef struct
{
	E_SND_MIXER_CTL type;
	char *name;
}S_MIXER_CTL;
typedef struct _D7_MIC_RMS
{
	double rms_value[8];
}S_D7_MIC_RMS;


int inx_snd_mixer_ctl_open(void);
int inx_snd_mixer_ctl_close(void);
int inx_set_mixer_ctl(char *ctl_name, char *val);
int inx_snd_mapping_function(void *dl_handle);
int inx_snd_mixer_execute(void);
int read_rms_value(S_D7_MIC_RMS *s_rms_value);




#endif





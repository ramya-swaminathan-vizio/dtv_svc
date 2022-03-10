#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include <assert.h>
#include <sys/stat.h>
#include "alsa/asoundlib.h"
#include "alsa/control.h"
#include "alsa/global.h"
#include <dlfcn.h>
#include "INX_fac_alsa.h"
#include "INX_fac_camera.h"
#include "c_os.h"

static snd_ctl_t *ctl_handle = NULL;
static BOOL ft_time_use = 0;
static UINT32 led_var = 0;

// function pointer 
int (*inx_snd_ctl_open)(snd_ctl_t **, const char *, int);
int (*inx_snd_ctl_close)(snd_ctl_t *ctl);
unsigned int (*inx_snd_ctl_elem_info_get_items)(const snd_ctl_elem_info_t *);
void (*inx_snd_ctl_elem_info_set_item)(snd_ctl_elem_info_t *, unsigned int);
int (*inx_snd_ctl_elem_info)(snd_ctl_t *, snd_ctl_elem_info_t *);
//void (*inx_snd_ctl_elem_id_alloca)(void *);
//void (*inx_snd_ctl_elem_value_alloca)(void *);
//void (*inx_snd_ctl_elem_info_alloca)(void *);
void (*inx_snd_ctl_elem_id_set_interface)(snd_ctl_elem_id_t *, snd_ctl_elem_iface_t);
void (*inx_snd_ctl_elem_id_set_name)(snd_ctl_elem_id_t *, const char *);
void (*inx_snd_ctl_elem_info_set_id)(snd_ctl_elem_info_t *, const snd_ctl_elem_id_t *);
void (*inx_snd_ctl_elem_info_get_id)(const snd_ctl_elem_info_t *, snd_ctl_elem_id_t *);
snd_ctl_elem_type_t (*inx_snd_ctl_elem_info_get_type)(const snd_ctl_elem_info_t *);
void (*inx_snd_ctl_elem_value_set_id)(snd_ctl_elem_value_t *, const snd_ctl_elem_id_t *);
void (*inx_snd_ctl_elem_value_set_boolean)(snd_ctl_elem_value_t *, unsigned int, long);
void (*inx_snd_ctl_elem_value_set_integer)(snd_ctl_elem_value_t *, unsigned int, long);
void (*inx_snd_ctl_elem_value_set_enumerated)(snd_ctl_elem_value_t *, unsigned int, unsigned int);
int (*inx_snd_ctl_elem_write)(snd_ctl_t *, snd_ctl_elem_value_t *);
const char (*inx_snd_ctl_elem_info_get_item_name)(const snd_ctl_elem_info_t *);
unsigned long (*inx_snd_ctl_elem_info_sizeof)(void);
unsigned long (*inx_snd_ctl_elem_id_sizeof)(void);
unsigned long (*inx_snd_ctl_elem_value_sizeof)(void);
S_MIXER_CTL s_mixer[] = 
{
	{E_MIXER_OPEN,"snd_ctl_open"},
	{E_MIXER_CLOSE,"snd_ctl_close"},
	{E_SND_CTL_ELEM_INFO_GET,"snd_ctl_elem_info_get_items"},
	{E_SND_CTL_ELEM_INFO_SET,"snd_ctl_elem_info_set_item"},
	{E_SND_CTL_ELEM_INFO_GET_ITEM_NAME,"snd_ctl_elem_info_get_item_name"},
	{E_SND_CTL_ELEM_INFO,"snd_ctl_elem_info"},
	{E_SND_CTL_ELEM_ID_ALLOCA,"snd_ctl_elem_id_alloca"},
	{E_SND_CTL_ELEM_VALUE_ALLOCA,"snd_ctl_elem_value_alloca"},
	{E_SND_CTL_ELEM_INFO_ALLOCA,"snd_ctl_elem_info_alloca"},
	{E_SND_CTL_ELEM_ID_SET_INTERFACE,"snd_ctl_elem_id_set_interface"},
	{E_SND_CTL_ELEM_ID_SET_NAME,"snd_ctl_elem_id_set_name"},
	{E_SND_CTL_ELEM_INFO_SET_ID,"snd_ctl_elem_info_set_id"},
	{E_SND_CTL_ELEM_INFO_GET_ID,"snd_ctl_elem_info_get_id"},
	{E_SND_CTL_ELEM_INFO_GET_TYPE,"snd_ctl_elem_info_get_type"},
	{E_SND_CTL_ELEM_VALUE_SET_ID,"snd_ctl_elem_value_set_id"},
	{E_SND_CTL_ELEM_VALUE_SET_BOOLEAN,"snd_ctl_elem_value_set_boolean"},
	{E_SND_CTL_ELEM_VALUE_SET_INTERGER,"snd_ctl_elem_value_set_integer"},
	{E_SND_CTL_ELEM_VALUE_SET_ENUM,"snd_ctl_elem_value_set_enumerated"},
	{E_SND_CTL_ELEM_WRITE,"snd_ctl_elem_write"},
	{E_SND_CTL_ELEM_INFO_SIZEOF,"snd_ctl_elem_info_sizeof"},
	{E_SND_CTL_ELEM_ID_SIZEOF,"snd_ctl_elem_id_sizeof"},
	{E_SND_CTL_ELEM_VALUE_SIZEOF,"snd_ctl_elem_value_sizeof"},
	
};

int inx_snd_mixer_ctl_open(void)
{

	const char *card = "default";
	int i4_ret = 0; 
	if((i4_ret = inx_snd_ctl_open(&ctl_handle, card, 0)) < 0) {
		printf("%s:%d, Control %s open error: %s\n", __FUNCTION__, __LINE__, card, s_mixer[E_MIXER_OPEN].name);
		return i4_ret;
	}
	return SND_OK_MSG;
}
static int inx_get_ctl_enum_item_index(snd_ctl_t *handle, snd_ctl_elem_info_t *info, char *val)
{
	int items, i;
	const char *ctl_name;
	items = inx_snd_ctl_elem_info_get_items(info);
	if (items <= 0)
		return SND_ERR_MSG;
	for(i = 0; i < items; i++) {
		inx_snd_ctl_elem_info_set_item(info, i);
		if (inx_snd_ctl_elem_info(handle, info) < 0)
			return SND_ERR_MSG;
		ctl_name = inx_snd_ctl_elem_info_get_item_name(info);
		if(!strcmp(ctl_name, val)) {
			return i;
		}
	}

	return SND_ERR_MSG;
}
int inx_set_mixer_ctl(char *ctl_name,char *val) 
{
	int err = 0;
	snd_ctl_elem_info_t *info = (snd_ctl_elem_info_t *) alloca(inx_snd_ctl_elem_info_sizeof());
	snd_ctl_elem_id_t *id = (snd_ctl_elem_info_t *) alloca(inx_snd_ctl_elem_id_sizeof());
	snd_ctl_elem_value_t *control = (snd_ctl_elem_info_t *) alloca(inx_snd_ctl_elem_value_sizeof());
	int enum_idx;
	snd_ctl_elem_type_t type;

	memset(info, 0, inx_snd_ctl_elem_info_sizeof());
	memset(id, 0, inx_snd_ctl_elem_id_sizeof());
	memset(control, 0, inx_snd_ctl_elem_value_sizeof());

	//Set element ID
	inx_snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);	/* default */
	inx_snd_ctl_elem_id_set_name(id, ctl_name);
	inx_snd_ctl_elem_info_set_id(info, id);
	if ((err = inx_snd_ctl_elem_info(ctl_handle, info)) < 0) {
		printf("%s:%d Error, while getting element info : %s \n", __FUNCTION__, __LINE__,s_mixer[E_SND_CTL_ELEM_INFO].name);
		return SND_ERR_MSG;
	}

	inx_snd_ctl_elem_info_get_id(info,id);	
	type = inx_snd_ctl_elem_info_get_type(info);
	inx_snd_ctl_elem_value_set_id(control,id);

	switch(type) {
	case SND_CTL_ELEM_TYPE_BOOLEAN:
		inx_snd_ctl_elem_value_set_boolean(control, 0, atoi(val));
		break;
	case SND_CTL_ELEM_TYPE_INTEGER:
		inx_snd_ctl_elem_value_set_integer(control, 0, atoi(val));
		 break;
	case SND_CTL_ELEM_TYPE_ENUMERATED:
		enum_idx = inx_get_ctl_enum_item_index(ctl_handle, info, val);
		if (enum_idx < 0) {
			printf("%s:%d Error, index of enum item not found\n", __FUNCTION__, __LINE__);
			return SND_ERR_MSG;
		}

		inx_snd_ctl_elem_value_set_enumerated(control, 0, enum_idx);
		break;
	default: 
		printf("%s:%d Error, control element type not supported\n", __FUNCTION__, __LINE__);
		return SND_ERR_MSG;
	}
	if ((err = inx_snd_ctl_elem_write(ctl_handle, control)) < 0) {
		printf("%s:%d Error, element write failed\n", __FUNCTION__, __LINE__);
		return SND_ERR_MSG;
	}

	return SND_OK_MSG;
}

int inx_snd_mixer_ctl_close(void) 
{
	if((inx_snd_ctl_close(ctl_handle)) < 0) {
		printf("%s:%d Error, failed while closing device\n", __FUNCTION__, __LINE__);
		return SND_ERR_MSG;
	}

	return SND_OK_MSG;
}
int inx_snd_mapping_function(void *dl_handle)
{

	inx_snd_ctl_open 					  = dlsym(dl_handle,s_mixer[E_MIXER_OPEN].name);
	inx_snd_ctl_close					  = dlsym(dl_handle,s_mixer[E_MIXER_CLOSE].name);
	inx_snd_ctl_elem_info_get_items 	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_GET].name);
	inx_snd_ctl_elem_info_set_item  	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_SET].name);
	inx_snd_ctl_elem_info_get_item_name   = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_GET_ITEM_NAME].name);
	inx_snd_ctl_elem_info           	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO].name);
	//inx_snd_ctl_elem_info_alloca      	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_ALLOCA].name);
	//inx_snd_ctl_elem_id_alloca        	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_ID_ALLOCA].name);
	//inx_snd_ctl_elem_value_alloca     	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_VALUE_ALLOCA].name);
	inx_snd_ctl_elem_id_set_interface 	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_ID_SET_INTERFACE].name);
	inx_snd_ctl_elem_id_set_name      	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_ID_SET_NAME].name);
	inx_snd_ctl_elem_info_set_id      	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_SET_ID].name);
	inx_snd_ctl_elem_info_get_id      	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_GET_ID].name);
	inx_snd_ctl_elem_info_get_type    	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_GET_TYPE].name);
	inx_snd_ctl_elem_value_set_id     	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_VALUE_SET_ID].name);
	inx_snd_ctl_elem_value_set_boolean	  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_VALUE_SET_BOOLEAN].name);
	inx_snd_ctl_elem_value_set_integer    = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_VALUE_SET_INTERGER].name);
	inx_snd_ctl_elem_value_set_enumerated = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_VALUE_SET_ENUM].name);
	inx_snd_ctl_elem_write 				  = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_WRITE].name);
	inx_snd_ctl_elem_info_sizeof          = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_INFO_SIZEOF].name);
	inx_snd_ctl_elem_id_sizeof            = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_ID_SIZEOF].name);
	inx_snd_ctl_elem_value_sizeof         = dlsym(dl_handle,s_mixer[E_SND_CTL_ELEM_VALUE_SIZEOF].name);
	//printf("inx_snd_ctl_elem_info_alloca = %p\n",inx_snd_ctl_elem_info_alloca);
	//printf("inx_snd_ctl_elem_id_alloca = %p\n",inx_snd_ctl_elem_id_alloca);
	//printf("inx_snd_ctl_elem_value_alloca = %p\n",inx_snd_ctl_elem_value_alloca);
	printf("inx_snd_ctl_elem_id_set_interface = %p\n",inx_snd_ctl_elem_id_set_interface);
	printf("inx_snd_ctl_elem_id_set_name = %p\n",inx_snd_ctl_elem_id_set_name);
	printf("inx_snd_ctl_elem_info_set_id = %p\n",inx_snd_ctl_elem_info_set_id);
	printf("inx_snd_ctl_open = %p\n",inx_snd_ctl_open);
	printf("inx_snd_ctl_elem_value_set_boolean = %p\n",inx_snd_ctl_open);
	printf("inx_snd_ctl_elem_value_set_integer = %p\n",inx_snd_ctl_open);
	printf("inx_snd_ctl_elem_value_set_enumerated = %p\n",inx_snd_ctl_open);
	printf("inx_snd_ctl_elem_write = %p\n",inx_snd_ctl_elem_write);
	printf("inx_snd_ctl_elem_info_get_items = %p\n",inx_snd_ctl_elem_info_get_items);
	printf("inx_snd_ctl_elem_info_set_item = %p\n",inx_snd_ctl_elem_info_set_item);
	printf("inx_snd_ctl_elem_info_get_item_name = %p\n",inx_snd_ctl_elem_info_get_item_name);
	return SND_OK_MSG;
}
int  read_rms_value(S_D7_MIC_RMS *s_rms_value) {
	FILE *fp;
	char str[60];
	double val;
	int count = 0;
	fp = fopen(RMS_PATH, "r");
	if(fp == NULL) {
		printf("Error opening file");
		return SND_ERR_MSG;
	}
	if(!ft_time_use)
	{
		c_thread_delay(1500);
		ft_time_use = TRUE;
	}
	while((fgets(str,60,fp) != NULL)) {
		val = (double)atoi(str)/0x400000;
		printf("%d:%f,\t\n", count, val);
		s_rms_value->rms_value[count] = abs(val);
		count++;
	}
	printf("\n");
	fclose(fp);
	
	return SND_OK_MSG;
}

int inx_snd_mixer_execute()
{
	int i4_ret = 0;
	void *dl_handle;
	dl_handle = dlopen(LIB_ALSA_PATH,RTLD_LAZY);
	if(!dl_handle)
	{
		printf(dlerror());
		return SND_ERR_MSG;
	}
	i4_ret = inx_snd_mapping_function(dl_handle);
	SND_DEBUG_MSG(i4_ret);
    if( (led_var%2) == 0 )
        a_led_inx_set_mic_led(INX_LED_TYPE_GREEN,INX_LED_ACT_ON);
    else
        a_led_inx_set_mic_led(INX_LED_TYPE_RED,INX_LED_ACT_ON);
	i4_ret = inx_snd_mixer_ctl_open();
	SND_DEBUG_MSG(i4_ret);
	i4_ret = inx_set_mixer_ctl("DBMDX Add on Number", "2");
	SND_DEBUG_MSG(i4_ret);
	i4_ret = inx_set_mixer_ctl("DBMDX Mic Mask", "255");
	SND_DEBUG_MSG(i4_ret);
	i4_ret = inx_set_mixer_ctl("DBMDX Usecase Manager", "8");
	SND_DEBUG_MSG(i4_ret);
	i4_ret = inx_snd_mixer_ctl_close();
	SND_DEBUG_MSG(i4_ret);
    if( (led_var%2) == 0 )
        a_led_inx_set_mic_led(INX_LED_TYPE_GREEN,INX_LED_ACT_OFF);
    else
        a_led_inx_set_mic_led(INX_LED_TYPE_RED,INX_LED_ACT_OFF);
    led_var++;
	dlclose(dl_handle);
	return SND_OK_MSG;
}

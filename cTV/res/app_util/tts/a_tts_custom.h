#ifndef  _A_TTS_CUSTOM_H_
#define  _A_TTS_CUSTOM_H_

#include "u_common.h"
#ifdef APP_TTS_SUPPORT
#include "u_tts.h"
#include "c_tts.h"
#endif

typedef struct {
    UINT16  ui2_sym_idx;
    CHAR*   pt_str;
}SYM_TO_STR_T;

#define  APP_TTSR_OK   (0)
#define  APP_TTSR_FAIL (-1)

#define  APP_TTS_STOP_FORCE (0)

#define  APP_TTS_LOG_ON_FAIL(_ret)  \
do{ \
INT32 ret = _ret;   \
if (ret < 0)   \
{   \
    DBG_LOG_PRINT(("[APP_TTS] {%s,%d} Return fail:%d.\r\n", __FILE__, __LINE__, ret)); \
}   \
}while(FALSE)

#define APP_TTS_CHK_FAIL(_ret)  \
do{ \
INT32 ret = _ret;	\
if (ret < 0)   \
{   \
    DBG_LOG_PRINT(("[APP_TTS] {%s,%d} Return fail:%d.\r\n", __FILE__, __LINE__, ret)); \
    return APP_TTSR_FAIL;  \
}   \
}while(FALSE)

#define APP_TTS_CHK_FAIL_NO_RET(_ret)  \
do{ \
INT32 ret = _ret;	\
if (ret < 0)   \
{   \
    DBG_LOG_PRINT(("[APP_TTS] {%s,%d} Return fail:%d.\r\n", __FILE__, __LINE__, ret)); \
    return ;  \
}   \
}while(FALSE)

#define TTS_KV_PLAY(k,v,l) \
do{\
    UTF16_T w2s_str[128] = {0};\
    c_uc_w2s_strcpy(w2s_str, k);\
    if (v)\
    {\
        c_uc_w2s_strcat(w2s_str, (NULL != l) ? l : (UTF16_T *)L"  ");\
        c_uc_w2s_strcat(w2s_str, v);\
    }\
    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));\
}while(FALSE)


typedef VOID (*app_tts_nfy_fct)(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag);

#define TTS_PLAY(str) a_app_tts_play(str,c_uc_w2s_strlen(str))
extern BOOL a_app_tts_is_enable();
extern INT32 a_app_tts_play(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size);
extern INT32 a_app_tts_play_string_normal(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size);
extern INT32 a_app_tts_play_symbol(UINT32 ui4_symbol);
extern INT32 a_app_tts_play_file(const CHAR *filepath);
extern INT32 a_app_tts_stop(INT32 tts_play_id);
extern INT32 a_app_tts_get_string_state();
extern INT32 a_app_tts_play_new_gap_just_once(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size, UINT32 gap);
extern INT32 a_app_tts_nfy_reg(app_tts_nfy_fct pf_nfy_fct, VOID *pv_tag);
extern INT32 a_app_tts_nfy_unreg(app_tts_nfy_fct pf_nfy_fct);
extern INT32 a_tts_switch_minus_to_minus_string(UINT16 *pt_w2s_src, UTF16_T *pt_w2s_dst, SIZE_T dst_sz);
extern INT32 a_tts_switch_dash_to_dash_string(UINT16 *pt_w2s_src, UTF16_T *pt_w2s_dst, SIZE_T dst_sz);
extern INT32 a_tts_print_play_content(UINT16 *pt_w2s_src);
#endif

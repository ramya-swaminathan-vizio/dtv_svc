#include "u_common.h"
#include "c_os.h"
#include "x_os.h"
#include "c_dbg.h"
#include "u_dbg.h"
#include "c_uc_str.h"
#include "c_handle.h"

#include "a_tts_custom.h"
#include "app_util/a_cfg.h"
#include "app_util/a_common.h"
#include "res/menu2/menu_mlm.h"
#include "res/nav/nav_mlm.h"
#include "util/u_lnk_list.h"
#include "am/a_am.h"


#ifdef APP_TTS_SUPPORT
typedef enum {
    TTS_TYPE_STRING = 0,
    TTS_TYPE_STRING_NORMAL, /*read number for string*/
    TTS_TYPE_SYMBOL,
    TTS_TYPE_FILE
} TTS_TYPE_T;
typedef struct {
    HANDLE_T            h_tts;
    HANDLE_T            h_timer;
    HANDLE_T            h_inner_timer;
    HANDLE_T            h_timer_thread;
    HANDLE_T            h_inner_timer_thread;
    TTS_CB_T            t_tts_cb;
    //static INT32    _i4_g_tts_tag = 0;
    UINT32              ui4_tts_string_id;
    UINT32              i4_tts_play_id;
    CHAR               *buffer;
    UINT32              ui4_symbol;
    CHAR                filepath[128];
    TTS_TYPE_T          t_tts_type;
} APP_TTS_T;

typedef struct {
    HANDLE_T           *h_timer;
    UINT32              ui4_delay;
    TIMER_FLAG_T        e_flags;
    x_os_timer_cb_fct   pf_callback;
    VOID               *pv_tag;
} _TIMER_PARAM_T;

typedef struct _APP_TTS_NFY_T {
    app_tts_nfy_fct                 pf_nfy_fct;
    VOID*                           pv_tag;
    DLIST_ENTRY_T(_APP_TTS_NFY_T)   t_link;
} APP_TTS_NFY_T;

typedef DLIST_T(_APP_TTS_NFY_T) APP_TTS_DLIST_T;

/*symbol to string*/
static SYM_TO_STR_T  g_tts_sym_to_str[] =
{
  {'^'  , "caret"},
  {'~'  , "tilde"},
  {'`'  , "grave accent"},
  {'|'  , "vertical bar"},
  {','  , "comma"},
  {'['  , "left bracket"},
  {']'  , "right bracket"},
  {0xb7 , "dot"},
  {'<'  , "less than"},
  {'>'  , "greater than"},
  {':'  , "colon"},
  {';'  , "semicolon"},
  {0xb0 , "degree"},
  {'.'  , "period"},
  {'\\' , "backslash"},
  {'/'  , "slash"},
  {'\'' , "apostrope"},
  {'"'  , "ditto mark"},
  {'_'  , "underscore"},
  {'$'  , "dollar"},
  {'('  , "left parenthesis"},
  {')'  , "right parenthesis"},
  {'{'  , "left curly bracket"},
  {'}'  , "right curly bracket"},
  {'&'  , "ampersand"},
  {'%'  , "percent"},
  {0xf7 , "division"},
  {'#'  , "number sign"},
  {'!'  , "exclamation mark"},
  {'?'  , "question mark"},
  {'+'  , "plus"},
  {'*'  , "asterisk"},
  {'@'  , "at"},
  {'-'  , "dash"},
  {'='  , "equals"}
};

#define  _TTS_INNER_FREE_SOURCE     (5*60*1000)

static APP_TTS_T   *pt_app_tts = NULL;
static UINT32       TTS_THRESHOLD_VALUE = 300;

static TTS_STRING_STATE_E _e_g_tts_string_state = TTS_STR_ST_UNKNOW;
static APP_TTS_DLIST_T *pt_nfy_list = NULL;
static INT32 _tts_switch_dash_to_string(UINT16 *pt_w2s_src, UTF16_T *pt_w2s_dst, SIZE_T dst_sz);
static INT32 _tts_print_play_content(UTF16_T* src_pw2s_content);
#define DASH_BUFF_SIZE  (64)

static INT32 _tts_stop(INT32 tts_play_id);
static UINT32 _tts_cb_fct (HANDLE_T      h_tts,
                              TTS_CB_CODE_E e_type,
                              UINT32        ui4_status,
                              UINT32        ui4_string_id,
                              VOID          *pv_tag)
{
    APP_TTS_NFY_T* pt_tts_nfy = NULL;

    switch(e_type)
    {
        case TTS_STR_STATE:

            _e_g_tts_string_state = (TTS_STRING_STATE_E) ui4_status;

            if (_e_g_tts_string_state == TTS_STR_ST_PLAYING ||
                _e_g_tts_string_state == TTS_STR_ST_PLAYED)
            {
                DLIST_FOR_EACH(pt_tts_nfy, pt_nfy_list, t_link)
                {
                    pt_tts_nfy->pf_nfy_fct(_e_g_tts_string_state,
                                            (UINT32)pt_app_tts->i4_tts_play_id,
                                            pt_tts_nfy->pv_tag
                                            );
                }
            }
            break;
        case TTS_APP_STATE:
            break;
        case TTS_CPBLTY_CHNG_STATE:
            break;
        default:
            break;
    }

    return 0;
}

static INT32 _tts_init(VOID)
{
    INT32 i4_ret = APP_TTSR_OK;

    if (NULL != pt_app_tts)
    {
        //DBG_LOG_PRINT(("[APP_TTS] tts handle initilized already!\n"));
        _tts_stop(APP_TTS_STOP_FORCE);
        return APP_TTSR_OK;
    }

    pt_app_tts = c_mem_alloc(sizeof(APP_TTS_T));
    if (NULL == pt_app_tts)
    {
        DBG_LOG_PRINT(("[APP_TTS]init tts struct fail!\n"));
        return APP_TTSR_FAIL;
    }

    c_memset(pt_app_tts, 0 ,sizeof(APP_TTS_T));

    i4_ret = c_tts_open_default_instance_fct(&pt_app_tts->h_tts);
    APP_TTS_CHK_FAIL(i4_ret);


    pt_app_tts->t_tts_cb.pf_fct = _tts_cb_fct;
    pt_app_tts->t_tts_cb.pv_tag  = NULL;  // (VOID *)&_i4_g_tts_tag;

    i4_ret = c_tts_set_fct(pt_app_tts->h_tts, TTS_SET_CALLBACK, (VOID *)&(pt_app_tts->t_tts_cb), sizeof(TTS_CB_T));
    APP_TTS_CHK_FAIL(i4_ret);

    pt_app_tts->ui4_tts_string_id = 0;

    if (pt_nfy_list == NULL)
    {
        pt_nfy_list = c_mem_alloc(sizeof(APP_TTS_DLIST_T));

        if (pt_nfy_list == NULL)
        {
            APP_TTS_CHK_FAIL(APP_TTSR_FAIL);
        }
        DLIST_INIT(pt_nfy_list);
    }

    return APP_TTSR_OK;
}

static VOID _tts_timer_cb_fct_thread (VOID*  pv_arg)
{
    TTS_RET_T i4_ret = TTSR_FAIL;
    UINT8     ui1_tts_value = 0;

    a_cfg_get_tts_focus_speech_audio(&ui1_tts_value);
    if (0 == ui1_tts_value)
    {
        a_cfg_set_tts_focus_speech_audio(1);
        a_cfg_update_tts_focus_speech_audio();
    }
    /*
       * Stop the running or queued tts requests, so current tts can be played
       * immediately
       */
    i4_ret = c_tts_stop_fct(pt_app_tts->h_tts);
    APP_TTS_CHK_FAIL_NO_RET(i4_ret);

    /* (Mandatory)TTS engine need c_tts_play() called to do the preparation. */
    i4_ret = c_tts_play_fct(pt_app_tts->h_tts);
    APP_TTS_CHK_FAIL_NO_RET(i4_ret);

    if (pt_app_tts->t_tts_type == TTS_TYPE_SYMBOL)
    {
        TTS_SYMBOL_T  t_tts_symbol_info = {0};
        t_tts_symbol_info.ui4_id = pt_app_tts->ui4_tts_string_id++;
        t_tts_symbol_info.ui4_symbol = pt_app_tts->ui4_symbol;
        i4_ret = c_tts_send_symbol_fct(pt_app_tts->h_tts, &t_tts_symbol_info);
        APP_TTS_CHK_FAIL_NO_RET(i4_ret);
    }
    else if (pt_app_tts->t_tts_type == TTS_TYPE_STRING)
    {
        TTS_STRING_T  t_tts_string_info = {0};
        t_tts_string_info.ui4_id    = pt_app_tts->ui4_tts_string_id++;
        t_tts_string_info.ps_string = pt_app_tts->buffer;
        t_tts_string_info.ui4_size  = c_strlen(pt_app_tts->buffer);
        t_tts_string_info.b_normal  = FALSE;
        i4_ret = c_tts_send_string_fct(pt_app_tts->h_tts, &t_tts_string_info);
        APP_TTS_CHK_FAIL_NO_RET(i4_ret);

        c_mem_free(pt_app_tts->buffer);
        pt_app_tts->buffer = NULL;
    }
    else if (pt_app_tts->t_tts_type == TTS_TYPE_STRING_NORMAL)
    {
        TTS_STRING_T  t_tts_string_info = {0};
        t_tts_string_info.ui4_id    = pt_app_tts->ui4_tts_string_id++;
        t_tts_string_info.ps_string = pt_app_tts->buffer;
        t_tts_string_info.ui4_size  = c_strlen(pt_app_tts->buffer);
        t_tts_string_info.b_normal  = TRUE;
        i4_ret = c_tts_send_string_fct(pt_app_tts->h_tts, &t_tts_string_info);
        APP_TTS_CHK_FAIL_NO_RET(i4_ret);

        c_mem_free(pt_app_tts->buffer);
        pt_app_tts->buffer = NULL;
    }
    else
    {
        TTS_FILE_T  t_tts_file_info = {0};
        t_tts_file_info.ui4_id    = pt_app_tts->ui4_tts_string_id++;
        t_tts_file_info.ps_filepath = pt_app_tts->filepath;
        i4_ret = c_tts_send_file_fct(pt_app_tts->h_tts, &t_tts_file_info);
        APP_TTS_CHK_FAIL_NO_RET(i4_ret);
    }

    x_thread_exit();
}

static VOID _tts_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag)
{
    INT32 i4_ret = 0;

    i4_ret = x_thread_create(&(pt_app_tts->h_timer_thread),
                             "_tts_timer_cb_fct",
                             8192,
                             128,
                             _tts_timer_cb_fct_thread,
                             0,
                             NULL);
    APP_TTS_CHK_FAIL_NO_RET(i4_ret);
}

static INT32 _tts_enable_timer(_TIMER_PARAM_T *param)
{
    if (NULL_HANDLE == *(param->h_timer))
    {
        APP_TTS_CHK_FAIL(c_timer_create(param->h_timer));
    }

    APP_TTS_CHK_FAIL(c_timer_stop(*(param->h_timer)));

    APP_TTS_CHK_FAIL(c_timer_start(*(param->h_timer),
                            param->ui4_delay,
                            param->e_flags,
                            param->pf_callback,
                            param->pv_tag));

    return APP_TTSR_OK;
}

static INT32 _tts_check_timer()
{
    _TIMER_PARAM_T  _t_timer_param = {0};

    _t_timer_param.h_timer      = &(pt_app_tts->h_timer);
    _t_timer_param.ui4_delay    = TTS_THRESHOLD_VALUE;
    _t_timer_param.e_flags      = X_TIMER_FLAG_ONCE;
    _t_timer_param.pf_callback  = _tts_timer_cb_fct;
    _t_timer_param.pv_tag       = NULL;

    APP_TTS_CHK_FAIL(_tts_enable_timer(&_t_timer_param));

    return APP_TTSR_OK;
}

static INT32 _tts_play_ch_r(CHAR *ps_str)
{
    INT32 i4_found = 0;
    CHAR *ps_rlt;
    CHAR *ps_next;
    SIZE_T t_size;

    while ((ps_rlt = c_strtok(ps_str, "()", &ps_next, &t_size)) != NULL)
    {
        if (ps_rlt != ps_str)
        {
            *(ps_rlt-1) = ' ';
        }

        if (*ps_next == 0)
        {
            break;
        }

        *ps_next = ' ';
        ps_str = ps_next;
        i4_found++;
    }

    return i4_found;
}

static INT32 _tts_play_pre_chk(VOID)
{
    UINT8  ui1_tts_switch_on = 0;
    ISO_639_LANG_T  s639_lang = {0};

    a_cfg_get_tts_switch_status(&ui1_tts_switch_on);
    if (0 == ui1_tts_switch_on)
    {
        DBG_LOG_PRINT(("[APP_TTS] tts switch is %s.\n", (0 == ui1_tts_switch_on)? "OFF": "ON"));
        return APP_TTSR_FAIL;
    }

    a_cfg_get_gui_lang(s639_lang);
    if (c_strcmp(s639_lang, s639_app_cfg_lang_eng) != 0)
    {
        DBG_LOG_PRINT(("[APP_TTS] current GUI language isn't Englist.\n"));
        return APP_TTSR_FAIL;
    }

    return APP_TTSR_OK;
}

static INT32 _tts_play_string(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size)
{
    SIZE_T  ps_str_len = 0;
    SIZE_T  w2s_str_len = 0;

    if (APP_TTSR_OK != _tts_play_pre_chk())
    {
        //DBG_LOG_PRINT(("[APP_TTS] %s() failed, LINE:%d.\n", __FUNCTION__, __LINE__));
        return APP_TTSR_FAIL;
    }
    if(FALSE == a_am_is_power_on())
    {
        DBG_LOG_PRINT(("[APP_TTS] The TV is not power on,will ignore this tts play \n"));
        return APP_TTSR_FAIL;
    }
    if (NULL == pw2s_content)
    {
        DBG_LOG_PRINT(("[APP_TTS] Play content is NULL\n"));
        return APP_TTSR_FAIL;
    }
    else
    {
        w2s_str_len = c_uc_w2s_strlen(pw2s_content);
        if (w2s_str_len < 1 || w2s_str_len > w2s_container_size)
        {
            DBG_LOG_PRINT(("[APP_TTS] Play content length err.\n"));
            return APP_TTSR_FAIL;
        }
    }

    APP_TTS_CHK_FAIL(_tts_init());

    APP_TTS_CHK_FAIL(_tts_check_timer());

    if (NULL != pt_app_tts->buffer)
    {
        DBG_LOG_PRINT(("[APP_TTS] replace string content.\n"));
        c_mem_free(pt_app_tts->buffer);
        pt_app_tts->buffer = NULL;
    }

    ps_str_len = w2s_str_len * sizeof(UTF16_T);
    pt_app_tts->buffer = c_mem_alloc(ps_str_len+1);
    if (NULL == pt_app_tts->buffer)
    {
        DBG_LOG_PRINT(("[APP_TTS] alloc space fail.\n"));
        return APP_TTSR_FAIL;
    }

    c_memset(pt_app_tts->buffer, 0, ps_str_len+1);
    APP_TTS_CHK_FAIL(c_uc_w2s_to_ps(pw2s_content, pt_app_tts->buffer, ps_str_len));
    pt_app_tts->t_tts_type = TTS_TYPE_STRING;

    _tts_play_ch_r(pt_app_tts->buffer);
    DBG_LOG_PRINT(("\n[APP_TTS] {play_content:%s}\n", pt_app_tts->buffer));

    return (++pt_app_tts->i4_tts_play_id);
}

static INT32 _tts_play_string_normal(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size)
{
    SIZE_T  ps_str_len = 0;
    SIZE_T  w2s_str_len = 0;

    if (APP_TTSR_OK != _tts_play_pre_chk())
    {
        //DBG_LOG_PRINT(("[APP_TTS] %s() failed, LINE:%d.\n", __FUNCTION__, __LINE__));
        return APP_TTSR_FAIL;
    }

    if (NULL == pw2s_content)
    {
        DBG_LOG_PRINT(("[APP_TTS] Play content is NULL\n"));
        return APP_TTSR_FAIL;
    }
    else
    {
        w2s_str_len = c_uc_w2s_strlen(pw2s_content);
        if (w2s_str_len < 1 || w2s_str_len > w2s_container_size)
        {
            DBG_LOG_PRINT(("[APP_TTS] Play content length err.\n"));
            return APP_TTSR_FAIL;
        }
    }

    APP_TTS_CHK_FAIL(_tts_init());

    APP_TTS_CHK_FAIL(_tts_check_timer());

    if (NULL != pt_app_tts->buffer)
    {
        DBG_LOG_PRINT(("[APP_TTS] replace string content.\n"));
        c_mem_free(pt_app_tts->buffer);
        pt_app_tts->buffer = NULL;
    }

    ps_str_len = w2s_str_len * sizeof(UTF16_T);
    pt_app_tts->buffer = c_mem_alloc(ps_str_len+1);
    if (NULL == pt_app_tts->buffer)
    {
        DBG_LOG_PRINT(("[APP_TTS] alloc space fail.\n"));
        return APP_TTSR_FAIL;
    }

    c_memset(pt_app_tts->buffer, 0, ps_str_len+1);
    APP_TTS_CHK_FAIL(c_uc_w2s_to_ps(pw2s_content, pt_app_tts->buffer, ps_str_len));
    pt_app_tts->t_tts_type = TTS_TYPE_STRING_NORMAL;

    _tts_play_ch_r(pt_app_tts->buffer);
    DBG_LOG_PRINT(("\n[APP_TTS] {play_content:%s}\n", pt_app_tts->buffer));

    return (++pt_app_tts->i4_tts_play_id);
}

static INT32 _tts_play_symbol(UINT32 ui4_symbol)
{
    if (APP_TTSR_OK != _tts_play_pre_chk())
    {
        DBG_LOG_PRINT(("[APP_TTS] %s() failed, LINE:%d.\n", __FUNCTION__, __LINE__));
        return APP_TTSR_FAIL;
    }

    APP_TTS_CHK_FAIL(_tts_init());

    APP_TTS_CHK_FAIL(_tts_check_timer());

    if (NULL != pt_app_tts->buffer)
    {
        DBG_LOG_PRINT(("[APP_TTS] replace string content.\n"));
        c_mem_free(pt_app_tts->buffer);
        pt_app_tts->buffer = NULL;
    }

    pt_app_tts->t_tts_type = TTS_TYPE_SYMBOL;
    pt_app_tts->ui4_symbol = ui4_symbol;

    return (++pt_app_tts->i4_tts_play_id);
}

static INT32 _tts_play_file(const CHAR *filepath)
{
    if (APP_TTSR_OK != _tts_play_pre_chk())
    {
        //DBG_LOG_PRINT(("[APP_TTS] %s() failed, LINE:%d.\n", __FUNCTION__, __LINE__));
        return APP_TTSR_FAIL;
    }

    APP_TTS_CHK_FAIL(_tts_init());

    APP_TTS_CHK_FAIL(_tts_check_timer());

    pt_app_tts->t_tts_type = TTS_TYPE_FILE;
    c_memset(pt_app_tts->filepath, 0, sizeof(pt_app_tts->filepath));
    c_strncpy(pt_app_tts->filepath, filepath, sizeof(pt_app_tts->filepath)-1);

    return (++pt_app_tts->i4_tts_play_id);
}

static INT32 _tts_stop(INT32 tts_play_id)
{
    if (NULL == pt_app_tts)
    {
        DBG_LOG_PRINT(("[APP_TTS] %s tts struct has not been initialized.\n", __func__));
        return APP_TTSR_FAIL;
    }

    if (tts_play_id != APP_TTS_STOP_FORCE && tts_play_id != pt_app_tts->i4_tts_play_id)
    {
        DBG_LOG_PRINT(("[APP_TTS] %s play id incorrect, cannot stop.\n", __func__));
        return APP_TTSR_FAIL;
    }

    if (c_handle_valid(pt_app_tts->h_timer))
    {
        APP_TTS_CHK_FAIL(c_timer_stop(pt_app_tts->h_timer));
    }

    if (NULL_HANDLE != pt_app_tts->h_tts)
    {
        APP_TTS_CHK_FAIL((INT32)c_tts_stop_fct(pt_app_tts->h_tts));
    }

    return APP_TTSR_OK;
}

INT32 _tts_print_play_content(UTF16_T* src_pw2s_content)
{
   SIZE_T  ps_str_len = c_uc_w2s_strlen(src_pw2s_content);
   CHAR*    pt_app_tts_buffer = c_mem_alloc((ps_str_len* sizeof(UTF16_T))+1);
   if (NULL == pt_app_tts_buffer)
   {
       DBG_LOG_PRINT(("[APP_TTS] alloc pt_app_tts_buffer space fail.\n"));
       return APP_TTSR_FAIL;
   }
    c_memset(pt_app_tts_buffer, 0, ps_str_len+1);
    APP_TTS_CHK_FAIL(c_uc_w2s_to_ps(src_pw2s_content, pt_app_tts_buffer, ps_str_len));
    DBG_LOG_PRINT(("[APP_TTS] %s() %d, string:{%s}.\n",__FUNCTION__,__LINE__,pt_app_tts_buffer));
    c_mem_free(pt_app_tts_buffer);
    pt_app_tts_buffer = NULL;
    return APP_TTSR_OK;
}

INT32 _tts_switch_dash_to_string(UINT16 * pt_w2s_src,UTF16_T * pt_w2s_dst,SIZE_T dst_sz)
{
     UINT32   ui4_pos = 0 ;

     APP_TTS_CHK_FAIL(_tts_print_play_content(pt_w2s_src));
     
    do{
        UINT32   ui4_area_sz;
        UINT32   ui4_rest_sz = DASH_BUFF_SIZE;
        UTF16_T  buffer[DASH_BUFF_SIZE+1] = {0};
    
        if (c_uc_w2s_chr_ex(pt_w2s_src, L'-', &ui4_pos) == NULL)
        {
            DBG_LOG_PRINT(("<break point > %s %d there is not dash.\n",__FUNCTION__,__LINE__));
            return APP_TTSR_OK;
        }

        if ((ui4_rest_sz > ui4_pos) == FALSE)
        {
            DBG_LOG_PRINT(("<break point > %s %d erro.\n",__FUNCTION__,__LINE__));
            return APP_TTSR_FAIL;
        }

        ui4_rest_sz -= ui4_pos;
        c_uc_w2s_strncpy(buffer, pt_w2s_src, ui4_pos);

        ui4_area_sz = c_uc_w2s_strlen(L"dash ");
        if ((ui4_rest_sz > ui4_area_sz) == FALSE)
        {
            DBG_LOG_PRINT(("<break point > %s %d erro.\n",__FUNCTION__,__LINE__));
            return APP_TTSR_FAIL;
        }

        ui4_rest_sz -= ui4_area_sz;
        c_uc_w2s_strncat(buffer, L"dash ", ui4_area_sz);

        ui4_area_sz = c_uc_w2s_strlen(pt_w2s_src+ui4_pos+1);
        if ((ui4_rest_sz > ui4_area_sz) == FALSE)
        {
            DBG_LOG_PRINT(("<break point > %s %d erro.\n",__FUNCTION__,__LINE__));
            return APP_TTSR_FAIL;
        }

        ui4_rest_sz -= ui4_area_sz;
        c_uc_w2s_strncat(buffer, pt_w2s_src+ui4_pos+1, ui4_area_sz);
        if (( (dst_sz >= (DASH_BUFF_SIZE-ui4_rest_sz))) == FALSE )
        {
            DBG_LOG_PRINT(("<break point > %s %d erro.\n",__FUNCTION__,__LINE__));
            return APP_TTSR_FAIL;
        }

        c_uc_w2s_strcpy(pt_w2s_dst, buffer);
        c_uc_w2s_strcpy(pt_w2s_src, buffer);

        ui4_pos = 0 ;//recycle
    
    }
    while(c_uc_w2s_chr_ex(pt_w2s_src, L'-', &ui4_pos) != NULL);

    return APP_TTSR_OK;
}


#endif

extern UINT16     ui2_g_menu_curr_lang;

BOOL a_app_tts_is_enable()
{
#ifdef APP_TTS_SUPPORT
    UINT8  i1_switch = 0;
    a_cfg_get_tts_switch_status(&i1_switch);
	return (1 == i1_switch && MLM_MENU_LANG_ENG == ui2_g_menu_curr_lang);
#else
    return FALSE;
#endif
}

INT32 a_app_tts_play(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size)
{
#ifdef APP_TTS_SUPPORT
    if(a_app_tts_is_enable() && NULL != pw2s_content && c_uc_w2s_strlen(pw2s_content) > 0 )
        return _tts_play_string(pw2s_content, w2s_container_size);
    else
    {
        DBG_INFO(("[TTS][%s %d] unable to read text ,please check \n",__FUNCTION__,__LINE__));
    }
#endif
    return APP_TTSR_OK;
}

INT32 a_app_tts_play_string_normal(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size)
{
#ifdef APP_TTS_SUPPORT
    return _tts_play_string_normal(pw2s_content, w2s_container_size);
#endif
    return APP_TTSR_OK;
}
INT32 _tts_play_symbol_to_string(UINT16  ui2_symbol)
{
    INT32  i4_i;
    INT32  i4_arr_sz = sizeof(g_tts_sym_to_str)/sizeof(g_tts_sym_to_str[0]);
    UTF16_T pw2s_str_content[64+1] = {0};
    if(FALSE == a_app_tts_is_enable())
    {
        return TTSR_FAIL;
    }

    for (i4_i = 0; i4_i < i4_arr_sz; i4_i ++)
    {
        if (g_tts_sym_to_str[i4_i].ui2_sym_idx == ui2_symbol)
        {
            c_uc_ps_to_w2s(g_tts_sym_to_str[i4_i].pt_str, pw2s_str_content, c_strlen(g_tts_sym_to_str[i4_i].pt_str));
            DBG_LOG_PRINT(("[ TTS +++] {%s %s() %d}. c:%c,s:%s\n",__FILE__, __FUNCTION__, __LINE__,ui2_symbol,g_tts_sym_to_str[i4_i].pt_str));
            return _tts_play_string(pw2s_str_content, c_uc_w2s_strlen(pw2s_str_content));
        }
    }

    return TTSR_OK;
}

INT32 a_app_tts_play_symbol(UINT32 ui4_symbol)
{
#ifdef APP_TTS_SUPPORT
    //_tts_play_symbol(ui4_symbol);
    return _tts_play_symbol_to_string((UINT16) ui4_symbol);
#endif
    return APP_TTSR_OK;
}

INT32 a_app_tts_play_file(const CHAR *filepath)
{
#ifdef APP_TTS_SUPPORT
    return _tts_play_file(filepath);
#endif
    return APP_TTSR_OK;
}

INT32 a_app_tts_stop(INT32 tts_play_id)
{
#ifdef APP_TTS_SUPPORT
    return _tts_stop(tts_play_id);
#endif
    return APP_TTSR_OK;
}

INT32 a_app_tts_play_new_gap_just_once(const UTF16_T *pw2s_content, SIZE_T  w2s_container_size, UINT32 gap)
{
#ifdef APP_TTS_SUPPORT
    INT32 i4_ret = 0;
    UINT32 ui4_tmp_gap = TTS_THRESHOLD_VALUE;

    TTS_THRESHOLD_VALUE = gap;
    i4_ret = a_app_tts_play(pw2s_content, w2s_container_size);
    TTS_THRESHOLD_VALUE = ui4_tmp_gap;

    return i4_ret;
#endif
    return APP_TTSR_OK;
}

INT32 a_app_tts_get_string_state(VOID)
{
    INT32 i4_tts_string_state = 0;

#ifdef APP_TTS_SUPPORT
    i4_tts_string_state = (INT32)_e_g_tts_string_state;

    DBG_LOG_PRINT(("[KK] %s TTS string state = %d.\n", __func__, i4_tts_string_state));
#endif
    return i4_tts_string_state;
}

INT32 a_app_tts_nfy_reg(app_tts_nfy_fct pf_nfy_fct, VOID *pv_tag)
{
#ifdef APP_TTS_SUPPORT

    APP_TTS_NFY_T* iterator = NULL;
    APP_TTS_NFY_T* pt_tts_nfy = NULL;

    if (pf_nfy_fct == NULL)
    {
        APP_TTS_CHK_FAIL(APP_TTSR_FAIL);
    }

    if (pt_nfy_list == NULL)
    {
        pt_nfy_list = c_mem_alloc(sizeof(APP_TTS_DLIST_T));

        if (pt_nfy_list == NULL)
        {
            APP_TTS_CHK_FAIL(APP_TTSR_FAIL);
        }
        DLIST_INIT(pt_nfy_list);
    }

    DLIST_FOR_EACH(iterator, pt_nfy_list, t_link)
    {
        if (iterator->pf_nfy_fct == pf_nfy_fct)
        {
            APP_TTS_CHK_FAIL(APP_TTSR_FAIL);
        }
    }

    pt_tts_nfy = c_mem_alloc(sizeof(APP_TTS_NFY_T));

    if (pt_tts_nfy == NULL)
    {
        APP_TTS_CHK_FAIL(APP_TTSR_FAIL);
    }

    pt_tts_nfy->pf_nfy_fct = pf_nfy_fct;
    pt_tts_nfy->pv_tag = pv_tag;

    DLIST_INSERT_TAIL(pt_tts_nfy, pt_nfy_list, t_link);

#endif
    return APP_TTSR_OK;
}

INT32 a_app_tts_nfy_unreg(app_tts_nfy_fct pf_nfy_fct)
{
#ifdef APP_TTS_SUPPORT

    APP_TTS_NFY_T* pt_tts_nfy = NULL;

    if (pf_nfy_fct == NULL)
    {
        APP_TTS_CHK_FAIL(APP_TTSR_FAIL);
    }

    DLIST_FOR_EACH(pt_tts_nfy, pt_nfy_list, t_link)
    {
        if (pt_tts_nfy->pf_nfy_fct == pf_nfy_fct)
        {
            DLIST_REMOVE(pt_tts_nfy, pt_nfy_list, t_link);
            c_mem_free(pt_tts_nfy);
            return APP_TTSR_OK;
        }
    }
#endif
    return APP_TTSR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_tts_switch_minus_to_minus_string
 *
 * Description: replace string, ex:  xxx-xxx-xxx -> xxx minus xxx-xxx
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 INT32 a_tts_switch_minus_to_minus_string(UINT16 *pt_w2s_src, UTF16_T *pt_w2s_dst, SIZE_T dst_sz)
{
    UINT32   ui4_pos;
    UINT32   ui4_area_sz;
    UINT32   ui4_rest_sz = 64;
    UTF16_T  buffer[64+1] = {0};

    if (c_uc_w2s_chr_ex(pt_w2s_src, L'-', &ui4_pos) == NULL)
    {
    DBG_LOG_PRINT(("<break point > %s %d \n",__FUNCTION__,__LINE__));
         return APP_TTSR_FAIL;
    }

    if ((ui4_rest_sz > ui4_pos) == FALSE)
    {
    DBG_LOG_PRINT(("<break point > %s %d \n",__FUNCTION__,__LINE__));
        return APP_TTSR_FAIL;
    }

    ui4_rest_sz -= ui4_pos;
    c_uc_w2s_strncpy(buffer, pt_w2s_src, ui4_pos);

    ui4_area_sz = c_uc_w2s_strlen(L"minus ");
    if ((ui4_rest_sz > ui4_area_sz) == FALSE)
    {
    DBG_LOG_PRINT(("<break point > %s %d \n",__FUNCTION__,__LINE__));
         return APP_TTSR_FAIL;
    }

    ui4_rest_sz -= ui4_area_sz;
    c_uc_w2s_strncat(buffer, L"minus ", ui4_area_sz);

    ui4_area_sz = c_uc_w2s_strlen(pt_w2s_src+ui4_pos+1);
    if ((ui4_rest_sz > ui4_area_sz) == FALSE)
    {
    DBG_LOG_PRINT(("<break point > %s %d \n",__FUNCTION__,__LINE__));
            return APP_TTSR_FAIL;
    }

    ui4_rest_sz -= ui4_area_sz;
    c_uc_w2s_strncat(buffer, pt_w2s_src+ui4_pos+1, ui4_area_sz);
    if (( (dst_sz >= (64-ui4_rest_sz))) == FALSE )
    {
    DBG_LOG_PRINT(("<break point > %s %d \n",__FUNCTION__,__LINE__));
            return APP_TTSR_FAIL;
    }

    c_uc_w2s_strcpy(pt_w2s_dst, buffer);
    DBG_LOG_PRINT(("<break point > %s %d \n",__FUNCTION__,__LINE__));
    return APP_TTSR_OK;

}
INT32 a_tts_switch_dash_to_dash_string(UINT16 *pt_w2s_src, UTF16_T *pt_w2s_dst, SIZE_T dst_sz)
{
#ifdef APP_TTS_SUPPORT
  return _tts_switch_dash_to_string(pt_w2s_src,pt_w2s_dst,dst_sz);
#else
  return APP_TTSR_FAIL;
#endif
}

INT32 a_tts_print_play_content(UINT16 *pt_w2s_src)
{
    return _tts_print_play_content(pt_w2s_src);
}


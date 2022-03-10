#ifndef PIC_PW_POPUP
#define PIC_PW_POPUP

#include "u_common.h"
#include "u_handle.h"

#define PPP_CHK_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("[PPP] {%s,%d,%s} ret=%d\r\n",__FILE__,__LINE__,__FUNCTION__,_ret)); \
    return NAVR_FAIL;  \
}   \
}while(FALSE)


typedef INT32 (*ppp_view_init_fct)(HANDLE_T h_canvas);
typedef INT32 (*ppp_view_deinit_fct)();
typedef INT32 (*ppp_view_is_key_handler_fct)();
typedef INT32 (*ppp_view_activate_fct)(UINT32 ui4_key_code);
typedef INT32 (*ppp_view_hide_fct)();

typedef struct _NAV_PPP_VIEW_HDLR_T
{
    ppp_view_init_fct              pf_init;
    ppp_view_deinit_fct            pf_deinit;
    ppp_view_is_key_handler_fct    pf_is_key_handler;
    ppp_view_activate_fct          pf_activate;
    ppp_view_hide_fct              pf_hide;
} NAV_PPP_VIEW_HDLR_T;


extern INT32 a_nav_ppp_register(VOID);
extern INT32 a_nav_ppp_view_register_hdlr(NAV_PPP_VIEW_HDLR_T* pt_hdr);
extern VOID  a_ppp_timer_launch(VOID);

#endif

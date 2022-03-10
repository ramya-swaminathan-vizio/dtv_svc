#ifndef _A_TOAST_H_
#define _A_TOAST_H_

#include "toast.h"

#define TOASTR_OK                      ((INT32)  0)
#define TOASTR_FAIL                    ((INT32) -1)
#define TOASTR_INV_ARG                 ((INT32) -2)
#define TOASTR_OUT_OF_MEMORY           ((INT32) -3)
#define TOASTR_WIDGET_CREATE_FAIL      ((INT32) -4)


INT32 a_toast_create (
    TOAST_INIT_PARAM_T*     pt_toast_init,
    HANDLE_T*               ph_toast_handle);

INT32 a_toast_destroy(HANDLE_T  h_toast_handle);

INT32 a_toast_show(
    HANDLE_T                    h_toast_handle,
    TOAST_CUSTOMIZATION_DATA_T* pt_custom_setting);

INT32 a_toast_hide(HANDLE_T  h_toast_handle);


#endif


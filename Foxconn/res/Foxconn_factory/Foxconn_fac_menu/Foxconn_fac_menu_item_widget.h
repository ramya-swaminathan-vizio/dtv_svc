/*-----------------------------------------------------------------------------
 * $RCSfile: Foxconn_fac_menu_item_widget.h $
 * $Revision: #1 $
 * $Date: 2017/08/30 $
 * $Author:  $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _Foxconn_fac_menu_item_widget_H_
#define _Foxconn_fac_menu_item_widget_H_

#include "u_common.h"
#include "u_wgl_common.h"
#include "u_handle.h"

extern INT32 Foxconn_fac_menu_frame_widget_create(HANDLE_T h_parent, 
                                                        HANDLE_T* ph_child, 
                                                        INT32 i4_frame_x_offset, 
                                                        INT32 i4_frame_y_offset);

extern INT32 Foxconn_fac_menu_frame_title_widget_create(HANDLE_T h_parent,
                                                    HANDLE_T * ph_child,
                                                    UTF16_T * pw2s_title_string);

extern INT32 Foxconn_fac_menu_text_widget_create(HANDLE_T h_parent,
                                             UTF16_T * pw2s_string,
                                             INT32 i4_index,
                                             wgl_widget_proc_fct pf_wdgt_proc,
                                             HANDLE_T * ph_widget);

extern INT32 Foxconn_fac_menu_range_widget_create(HANDLE_T h_parent,
                                                              UTF16_T * pw2s_string,
                                                              INT32 i4_index,
                                                              INT32 i4_min,
                                                              INT32 i4_max,
                                                              wgl_widget_proc_fct pf_wdgt_proc,
                                                              HANDLE_T * ph_widget);

extern INT32 Foxconn_fac_menu_list_widget_create(HANDLE_T h_parent,
                                                           UTF16_T * pw2s_string,
                                                           INT32 i4_index,
                                                           UINT16 ui2_max_elem_num,
                                                           wgl_widget_proc_fct pf_wdgt_proc,
                                                           HANDLE_T * ph_widget);

extern INT32 Foxconn_fac_menu_range_get_val(HANDLE_T h_widget,INT32 * pi4_val);

extern INT32 Foxconn_fac_menu_range_set_val(HANDLE_T h_widget,INT32 i4_val);

extern INT32 Foxconn_fac_menu_list_set_text(HANDLE_T h_widget,UTF16_T * w2s_str);
#endif

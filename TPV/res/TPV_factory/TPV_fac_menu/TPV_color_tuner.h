/*-----------------------------------------------------------------------------
 * $RCSfile: TPV_color_tuner.h $
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
#ifndef _TPV_color_tuner_H_
#define _TPV_color_tuner_H_
 /*-----------------------------------------------------------------------------
                     include files
 -----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 TPV_fac_color_tuner_view_init(HANDLE_T h_parent, INT32 i4_frame_x_offset, INT32 i4_frame_y_offset);
extern INT32 TPV_fac_color_tuner_view_deinit(VOID);
extern INT32 TPV_fac_color_tuner_menu_show(BOOL b_repaint);
extern INT32 TPV_fac_color_tuner_menu_hide(BOOL b_repaint);

#endif /* _TPV_color_tuner_H_ */

/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain softwares relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                            *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * $RCSfile: nav_fac.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_FAC_H_
#define _NAV_FAC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_scc.h"
#include "u_common.h"
#include "u_wgl_image.h"

#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#include "res/nav/factory/fac_urc/nav_fac_urc.h"
#include "res/nav/factory/a_factory.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
struct _NAV_FAC_VIEW_HDLR_T;

/* Define the number of FAC */
#define NAV_FAC_KEY_STACK_NUM   ((SIZE_T) 5)  //ke_vizio_20110131

/* Soar Add 20081013 for Default Channel loading is 1997 */
#define TPV_FAC_DEFAULT_CH         {BTN_MENU, BTN_DIGIT_1, BTN_DIGIT_9, BTN_DIGIT_9, BTN_DIGIT_7};       //"1997"  //ke_vizio_20110131
#define TPV_FAC_DEFAULT_CH_POL     {BTN_MENU, BTN_DIGIT_1, BTN_DIGIT_9, BTN_DIGIT_9, BTN_DIGIT_8};     //"1998"  //ke_vizio_20110131

//ke_vizio_20110131
/* FAC Password default, the master password is 1999 */
#define NAV_FAC_KEY_STACK2_NUM   ((SIZE_T) 6)
#define TPV_FAC_PASSWORD_DEF     {BTN_MENU, BTN_DIGIT_1, BTN_DIGIT_9, BTN_DIGIT_9, BTN_DIGIT_9, BTN_PREV_PRG};  // "Menu"+""1999" + "recall"

#if 1	//sam 120207 add MENU+1+9+1+9 to dump EEPROM data
#define NAV_FAC_KEY_STACK3_NUM   ((SIZE_T) 5)
#define TPV_FAC_PASSWORD_DEF_EEPROM     {BTN_MENU, BTN_DIGIT_1, BTN_DIGIT_9, BTN_DIGIT_1, BTN_DIGIT_9};  // "Menu"+""1919" 
#endif

typedef enum
{
    NAV_FAC_MENU_BRAND = 0,
    NAV_FAC_MENU_MAIN_MCU_VER,
    NAV_FAC_MENU_BOOT_LOADER_VER,
    NAV_FAC_MENU_SUB_MCU_VER,
    NAV_FAC_MENU_EEPROM_VER, 
    NAV_FAC_MENU_PQ_VER,  //ke_vizio_20130606 add
    NAV_FAC_MENU_AQ_VER,  //ke_vizio_20130606 add
    NAV_FAC_MENU_DATE,
    NAV_FAC_MENU_MODEL_NAME,
    NAV_FAC_MENU_SCALER,
    NAV_FAC_MENU_PANEL_TYPE,
#ifdef APP_FAC_TUNER_SELECTION //sam 091229
    NAV_FAC_MENU_TUNER_TYPE,
#endif
    NAV_FAC_MENU_CURRENT_SOURCE,
#if 0	//kyo_20111221    
    NAV_FAC_MENU_AUTO_COLOR,
    NAV_FAC_MENU_ADC_R_GAIN,
    NAV_FAC_MENU_ADC_G_GAIN,
    NAV_FAC_MENU_ADC_B_GAIN,
    NAV_FAC_MENU_ADC_R_OFFSET,
    NAV_FAC_MENU_ADC_G_OFFSET,
    NAV_FAC_MENU_ADC_B_OFFSET,
#endif
#ifdef  FAC_MENU_CLR_COPY //ke_vizio_20121127 add
    NAV_FAC_MENU_CLR_COPY,
#endif
    NAV_FAC_MENU_COLOR_TEMP,
    NAV_FAC_MENU_SCALER_R_GAIN,
    NAV_FAC_MENU_SCALER_G_GAIN,
    NAV_FAC_MENU_SCALER_B_GAIN,
    NAV_FAC_MENU_SCALER_R_OFFSET,
    NAV_FAC_MENU_SCALER_G_OFFSET,
    NAV_FAC_MENU_SCALER_B_OFFSET,
    NAV_FAC_MENU_BURN_IN,
    NAV_FAC_MENU_EEPROM_INIT,
    NAV_FAC_MENU_BACK_LIT_TIME,
    NAV_FAC_MENU_BACKLIGHT_MAX,
    NAV_FAC_MENU_BACKLIGHT_MIN,
    NAV_FAC_MENU_RESET,
#ifdef APP_DVBT_SUPPORT
    NAV_FAC_MENU_OAD_ENABLE,
#endif
    //NAV_FAC_MENU_VGA_SWITCH,
#ifdef FACTORY_VCOM_TEST_PATTERN //Emerson Add 20091123 for Test pattern output
    NAV_FAC_MENU_TCON,
#endif
#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
    NAV_FAC_MENU_WB_INTRNL_PAT,
#endif
#ifdef FAC_DUMP_CH_INFO
    NAV_FAC_MENU_DUMP_CH_INFO,
#endif
#ifdef FAC_FILP_MIRROR_SUPPORT
    NAV_FAC_MENU_FLIP,
    NAV_FAC_MENU_MIRROR,
#endif /* FAC_FILP_MIRROR_SUPPORT */
#ifdef FAC_DUMP_EEPROM
    NAV_FAC_MENU_DUMP_EEPROM,
#endif
#ifdef FAC_AUD_SRS_BYPASS
    NAV_FAC_MENU_AUD_SRS_BYPASS,
#endif
#ifdef FAC_HDMI_PORT_NUM_SETTING 
    NAV_FAC_MENU_HDMI_PORT_NUM_SETTING,
#endif
#ifdef FAC_INSTALL_ULPK
    NAV_FAC_MENU_INSTALL_ULPK, /*//sam 0331 for ULPK install in fac menu*/
#endif
#if 0	//kyo_20111221    
	#ifdef FAC_ULPK_ERASE //sam 111219
    NAV_FAC_MENU_ERASE_ULPK,	/*//sam 110504 for ULPK erase in fac menu*/
    #endif
#endif    
#ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522
    NAV_FAC_MENU_WINDOW_PATTERN,
#endif
    /* Don't remove this */
    NAV_FAC_MENU_MAX
} NAV_FAC_SETUP_MENU_ITEM_T;


/* Define FAC message */
typedef enum
{
    FAC_MSG_BEGIN = 0,                                  /* Begin of FAC messages. */
    FAC_MSG_KEY_INPUT,                                  /* Keycode input from IOM */    /* pv_param1 = ui4_key_code */  /* pv_param2 = ui4_data (driver raw data) */
    FAC_MSG_AUTO_COLOR_FAIL,
    FAC_MSG_AUTO_COLOR_DONE,
    FAC_MSG_BLT_LT_UPDATE,

    FAC_MSG_END                                         /* End of FAC messages. */
}   FAC_MSG_T;

//Emerson Add 2008-0925 for Panel ID mapping table
typedef struct _Panel_ID_MapUnit {
    UINT16  ui4_index;
    UINT32  ui4_panel_id;
} PANEL_ID_T;

typedef struct _NAV_CUSTOM_FAC_T
{
    /* For FAC mode */
    HANDLE_T    h_iom;                                  /* IO Manager handle */
    UINT16      ui2_key_num;                            /* Record the number of password which user already inputed */
    UINT32     at_key_stack[NAV_FAC_KEY_STACK_NUM+1];  /* Key Stack */  //ke_vizio_20110131
    
    UINT16      ui2_key_num2;                            /* Record the number of password which user already inputed */
    UINT32     at_key_stack2[NAV_FAC_KEY_STACK2_NUM+1];  /* Key Stack2 */

	#if 1	//sam 120207 add MENU+1+9+1+9 to dump EEPROM data
    UINT16      ui2_key_num3;                            /* Record the number of password which user already inputed */
    UINT32     at_key_stack3[NAV_FAC_KEY_STACK3_NUM+1];  /* Key Stack3 */
	#endif
} NAV_CUSTOM_FAC_T;



struct _NAV_FAC_T;

typedef INT32 (*nav_fac_view_init_fct)(
                    struct _NAV_FAC_T*         pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
typedef INT32 (*nav_fac_view_deinit_fct)(
                    VOID
                    );
typedef BOOL (*nav_fac_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*nav_fac_view_activate_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*nav_fac_view_hide)(
                    VOID
                    );
typedef struct _NAV_FAC_VIEW_HDLR_T
{
    nav_fac_view_init_fct              pf_init;
    nav_fac_view_deinit_fct            pf_deinit;
    nav_fac_view_is_key_handler_fct    pf_is_key_handler;
    nav_fac_view_activate_fct          pf_activate;
    nav_fac_view_hide                  pf_hide;
} NAV_FAC_VIEW_HDLR_T;

typedef INT32 (*nav_fac_view_dialog_init_fct)(
                    struct _NAV_FAC_T*         pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
typedef INT32 (*nav_fac_view_dialog_deinit_fct)(
                    VOID
                    );
typedef BOOL (*nav_fac_view_dialog_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*nav_fac_view_dialog_activate_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*nav_fac_view_dialog_hide)(
                    VOID
                    );
typedef struct _NAV_FAC_VIEW_DIALOG_HDLR_T
{
    nav_fac_view_dialog_init_fct              pf_init;
    nav_fac_view_dialog_deinit_fct            pf_deinit;
    nav_fac_view_dialog_is_key_handler_fct    pf_is_key_handler;
    nav_fac_view_dialog_activate_fct          pf_activate;
    nav_fac_view_dialog_hide                  pf_hide;
} NAV_FAC_VIEW_DIALOG_HDLR_T;

typedef struct _NAV_FAC_T
{
    HANDLE_T                    h_bklight_timer;
	HANDLE_T                    h_fac_ipt_pw_timer;    //Soar add for key timeout 20111013
    BOOL                        b_is_on;
    NAV_FAC_VIEW_HDLR_T         t_view_hdlr;
    
    #ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
    UINT32                      ui4_rmv_dev_nfy;
    #endif
} NAV_FAC_T;

#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add
typedef struct _NAV_FAC_MODEL_NAME_T
{
    UINT16      ui2_model_name_id;                    /* Model Name ID */
    CHAR*       s_model_name;                         /* Model Name */
    UINT8       ui1_inch_size;                        /* Panel size (inch) */
} NAV_FAC_MODEL_NAME_T;
#endif

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_fac_register_io_mngr(
                    VOID
                    );
extern INT32 nav_fac_async_dispatch_msg(
                    FAC_MSG_T                   e_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );
extern INT32 nav_fac_unlock_key(
                    VOID
                    );

extern VOID nav_fac_boolean_to_text(
                    UINT32              ui4_val,
                    UTF16_T*            w2s_bool_string
                    );
extern VOID nav_fac_number_to_string(
                    INT32              ui4_number,
                    UTF16_T*            w2s_string
                    );
extern VOID nav_fac_lit_number_to_string(
                    UINT32                  ui4_number_hun,
                    UINT32                  ui4_number_unit,
                    UTF16_T*                w2s_string
                    );
extern INT32 nav_fac_get_setup_min_max(
                    UINT16              ui2_idx,
                    INT16*             pui2_min,
                    INT16*             pui2_max
                    );
extern INT32 nav_fac_get_setup_value(
                    UINT16              ui2_idx,
                    INT32*             pui4_val
                    );
extern INT32 nav_fac_set_setup_value(
                    UINT16              ui2_idx,
                    INT32              ui4_val
                    );
extern INT32 nav_fac_view_register_default_hdlr(
                    NAV_FAC_VIEW_HDLR_T*       pt_view_hdlr
                    );
extern INT32 a_nav_fac_dialog_register(VOID);

#ifdef APP_FAC_TUNER_SELECTION //sam 091229
extern CHAR* GetCurrentTunerName(void);

extern UINT32 GetCurrentTunerIndex(void);

extern CHAR* GetTunerName(UINT32 u4Index);
#endif

extern INT32 a_nav_fac_register(
                    struct _NAV_FAC_VIEW_HDLR_T*   pt_view_hdlr
                    );

extern BOOL  nav_fac_is_video_block(VOID);

extern BOOL  nav_fac_is_signal_loss(VOID);

extern BOOL  a_nav_fac_is_password_ipt_window(
                    VOID
                    );
//Soar Add 20081013 for default channel
extern INT32 acfg_SAC_load_default_channel(CHAR* ui1_area);

extern INT32 acfg_SAC_dump_channel_info(VOID);	//kyo_20090826

extern INT32 a_nav_fac_urc_dialog_register(VOID);

extern INT32 nav_fac_urc_dialog_hide(VOID); //jeff 20090319 add

extern INT32 nav_fac_urc_dialog_show(VOID); //jeff 20090604 add for URC


#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add
extern INT32 nav_fac_model_name_get_max_cnt_by_panel_id(
                    UINT32                      ui4_panel_id,
                    UINT16 *                    pt_ui2_mn_cnt
                    );

extern INT32 nav_fac_model_name_get_model_name_by_panel_id(
                    UINT32                      ui4_panel_id,
                    UINT16                      ui2_mn_idx,
                    CHAR *                      pt_s_mn_str
                    );

extern INT32 nav_fac_model_name_get_current_model_name_id(
                    UINT16*                     pt_ui2_model_name_id
                    );

extern INT32 nav_fac_model_name_get_default_model_name_by_panel_id(
                    UINT32                      ui4_panel_id,
                    CHAR *                      pt_s_mn_str
                    );

extern BOOL nav_fac_model_name_is_valid(
                    CHAR *                      pt_s_mn_str
                    );

extern INT32 nav_fac_model_name_write_default_model_name(VOID);

extern INT32 nav_fac_get_current_model_id_by_panel(UINT16 *pui2_id);
#endif

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
BOOL nav_fac_sce_pat_is_on(VOID);

VOID nav_fac_sce_pat_set_on_off_flag(BOOL b_on);

UINT16 nav_fac_sce_pat_get_level(VOID);

VOID nav_fac_sce_pat_set_level(UINT16 ui2_val);

INT32 nav_fac_sce_pat_enable_pat(BOOL b_enable);
#endif

extern INT32 nav_fac_get_HDMI_port_NUM(UINT8 *pui1_num);

extern INT32 nav_fac_set_HDMI_port_NUM(UINT8 ui1_num);

extern INT32 nav_fac_get_flip_mirror_enable(BOOL * pb_filp_enable,BOOL * pb_mirror_enable);

extern INT32 nav_fac_set_flip_mirror_enable(BOOL b_filp_enable, BOOL b_mirror_enable);

#ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
extern INT32 nav_fac_view_eep_update_osd_create(VOID);
extern INT32 nav_fac_view_eep_update_osd(CHAR* pstring);
#endif

//////////////////Only for Vizio//////////////////////
typedef enum
{
    RC_XRV1TV = 0,  /* XRV1TV is the same with XRT300*/

}RC_TYPE_BY_MODEL_INFO_T;

//sam 120529 reserve for multi-IO request
//***************************************************//
// //sam 120529 reserve for multi-IO request
//at_post_reg_custom0 -->HDMIx4 ,combine Comp-2 & RGB
//at_post_reg_custom1 -->HDMIx3 ,combine Comp-2 & RGB
//at_post_reg_custom2 -->HDMIx4 ,cancel Comp-2 & RGB
//at_post_reg_custom3 -->HDMIx3 ,cancel Comp-2 & RGB
//***************************************************//
typedef enum
{
    IO_table_0 = 0,
    IO_table_1,
    IO_table_2,
    IO_table_3
}HDMI_PORT_BY_MODEL_INFO_T;


typedef enum
{
    MODEL_ID_E551VA = 0,

    MODEL_ID_MAX
}MODEL_ID_BY_MODEL_INFO_T;

typedef enum
{
    VIZIO_E_SERIES = 0,

}MODEL_SERIES_BY_MODEL_INFO_T;

typedef enum
{
    UNKNOWN_TUNER = 0,

}MODEL_TUNER_BY_MODEL_INFO_T;

typedef struct _VIZIO_MODEL_INFO {
    MODEL_SERIES_BY_MODEL_INFO_T   e_model_series;
    RC_TYPE_BY_MODEL_INFO_T    e_RC_type;
    HDMI_PORT_BY_MODEL_INFO_T  e_hdmi_port;
    BOOL b_3D_support;  // 3D : 1; 2D :0
    BOOL b_flip_mirror;
    MODEL_TUNER_BY_MODEL_INFO_T e_tuner;
} VIZIO_MOEDL_INFO_T;


extern INT32 nav_get_cur_model_info(VIZIO_MOEDL_INFO_T *pvt_info);
//////////////////////////////////////////////////

#endif /* _NAV_FAC_H_ */


extern BOOL a_get_fac_status(VOID);
extern INT32 a_set_fac_status(BOOL b_status);

#ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
extern INT32 nav_fac_border_window(BOOL b_onOff,UINT32 u4L_width,UINT32 u4R_width,UINT32 u4U_height,UINT32 u4D_height);
#endif


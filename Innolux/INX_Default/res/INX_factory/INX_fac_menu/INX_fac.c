/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: nav_fac.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_iom.h"
#include "c_scc.h"
#include "u_sb_dvb_eng.h"
#include <unistd.h>
#include <stdio.h>
#include "am/a_am.h"
#include "amb/a_amb.h"
#include "menu2/a_menu.h"

#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"

//#include "nav_fac.h"
#include "INX_fac.h"
//#include "res/nav/factory/fac_mlm.h"
#include "INX_factory/INX_fac_mlm.h"
//#include "res/nav/factory/a_factory.h"
#include "INX_factory/a_INX_factory.h"
#include "INX_factory/INX_d_factory.h"
#include "INX_factory/INX_fac_ch_table/INX_fac_load_ch.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_factory.h"
#include "app_util/config/_acfg.h"    //Soar 20080924

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"

//#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output
//#include "res/nav/factory/fac_tcon/nav_fac_tcon.h"
//#include "res/nav/factory/fac_tcon/TI_TPS65168.h"
//#endif

#ifdef FAC_WB_USE_SCE_PATTERN
#include "nav/power/a_nav_power.h" // Denny 2010/01/22 add for invoking a_nav_power_set_component_enable()
#endif

//#ifdef LINUX_TURNKEY_SOLUTION
//extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
//#endif
#include "msgconvert/msgconvert.h"

#include "app_util/config/_acfg.h"
#include "app_util/rmv_dev/a_rmv_dev.h"

#ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "c_os.h"
#include "nav/usb_pld/nav_usb_pld_view.h" 
#endif

#include "bgm/a_bgm.h" //ke_vizio_20141105 add

#include "mmp/a_mmp.h"  //ke_vizio_20141203 add

#ifdef INX_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
#include "c_cli.h"  //ke_vizio_20150522 add
#endif

#ifdef FAC_BT_TESTBLE //Ben 20170809
#include "bluetooth_gatt/bluetooth_gattc_rssimeter_view.h"
#endif

#include "menu2/menu_common/menu_common.h"  // Ben 10280130

/*inx_fac_menu_main_page*/
#include "INX_fac_main_page_res.h"

SIZE_T   t_size = sizeof(UINT16); //Soar 20080918

UINT32 INX_PD_FAC_PASSWORD_DEF[NAV_FAC_KEY_STACK_NUM]=
{BTN_MENU, BTN_DIGIT_3, BTN_DIGIT_2, BTN_DIGIT_1, BTN_DIGIT_0};  // "Menu"+""3210"  (joe.zy) for PD
UINT32 INX_FAC_PASSWORD_DEF[NAV_FAC_KEY_STACK_NUM]=
{BTN_MENU, BTN_DIGIT_3, BTN_DIGIT_4, BTN_DIGIT_8, BTN_DIGIT_1};  // "Menu"+"3481" (joe.zy) for factory member
UINT32 INX_KEYPAD_PASSWORD_DEF[NAV_FAC_KEY_STACK_NUM]=
{BTN_INPUT_SRC,BTN_VOL_UP,BTN_VOL_DOWN,BTN_VOL_UP,BTN_VOL_DOWN}; // "INPUT KEY"+"VOL+" +"VOL-"+"VOL+"+"VOL-" on keypad for aging off

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);   //ke_vizio_20121114 add
static VOID inx_nav_fac_usb_pld_rmv_dev_nfy(VOID * pv_tag,RMV_DEV_NFY_ID_T e_nfy_id,VOID * pv_nfy_param);

#ifdef FAC_MENU_CLR_COPY   //ke_vizio_20121127 add  
extern INT32 nav_fac_clr_copy_to_all(VOID);
#endif

//ke_vizio_20121127 add  
extern INT16 acfg_custom_clr_temp_delta(UINT16  ui2_id,
                                                UINT8   ui1_input_grp,
                                                INT16   i2_clr_temp,
                                                INT16   i2_val);


#ifdef FAC_BT_TESTBLE // Ben 20170809
extern VOID bt_gatt_cli_set_allow_pair_4_test_tool(BOOL b_allow);		//mind 20160826
#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_CUSTOM_FAC_T     t_g_fac       = {0};

static NAV_FAC_T            t_g_nav_fac  = {0};

static INT8 bklight_buffer = 0;    //moore 080924

BOOL b_nav_fac_eep_init_done = FALSE;
BOOL b_nav_fac_reset_done = FALSE;
BOOL b_nav_fac_get_led_info_done = FALSE;
BOOL b_nav_fac_get_ELCS = FALSE;
BOOL b_inx_fac_eep_init_done = FALSE;
#ifdef FAC_BT_TESTBLE	//Ben 20170809
BOOL b_nav_fac_bt_testble_on_off = FALSE;
#endif

BOOL b_nav_fac_install_ulpk_done = FALSE;/*//sam 0331 for ULPK install in fac menu*/	
BOOL b_nav_default_fq_ch_loading = FALSE;
BOOL b_nav_default_sz_ch_loading = FALSE;//Soar Add 20081013 for default channel
BOOL b_nav_default_pol_ch_loading = FALSE;//Soar Add 20081013 for default channel

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
BOOL   b_nav_fac_wb_intrnl_pat_on_off = FALSE;
UINT16 ui2_nav_fac_wb_intrnal_pat_val = 819;
#endif

#ifdef FAC_AUD_SRS_BYPASS
BOOL g_b_aud_srs_bypass_mode = FALSE;
#endif

BOOL b_nav_fac_aq_bypass_on_off = TRUE;

UINT16 ui_nav_fac_zzz_test = 0;

UINT16 ui2_nav_fac_panel_nits = 0;
BOOL b_nav_fac_panel_nits_inited = FALSE;

UINT16 ui2_nav_fac_zzz_test3 = 0;


#define INX_DEFAULT_FQ_CH 1  // 1 :FQ ; 0 : SZ
#define NAV_NAME "navigator"

#if defined(FAC_MENU_PANEL_TYPE_SELECT) && defined(FAC_MENU_PANEL_NAME_SELECT)
static const PANEL_ID_T _ar_Fac_Panel_ID_Map[] =
{
//@jh todo	{ 0, PANEL_AUO_42_HW1_V0},	   //E551VA

};
#endif

#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add

CHAR s_model_name_string[16] = " ";

static NAV_FAC_MODEL_NAME_T _ar_Fac_Model_Name_default_Table[] =
{
    { PANEL_AUO_42_HW1_V0,        "XXXX",     50},  // 0
};


#endif


BOOL b_def_clr_temp_update = FALSE;   //ke_vizio_20121115 add

#ifdef INX_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
static CLI_EXEC_T at_INX_fac_cmd_tbl[];
BOOL g_b_WinPatOnOff = FALSE;
#endif

extern BOOL     b_inx_at_debug_enable;//truedano

BOOL     b_inx_at_tftps_enable = 0;

UINT8    inx_at_ui_switch = 0; //joe for switch menu ui

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_bklight_timer_stop(NAV_FAC_T* pt_this);
static VOID _nav_fac_ipt_pw_timer_stop(NAV_FAC_T* pt_this);    //Soar add for key timeout 20111013

#ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
static VOID _nav_fac_usb_pld_rmv_dev_nfy(VOID * pv_tag,RMV_DEV_NFY_ID_T e_nfy_id,VOID * pv_nfy_param);
static VOID _nav_fac_tpv_eep_update(VOID * pv_tag1,VOID * pv_tag2,VOID * pv_tag3);
#endif
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
#ifdef FAC_AUD_SRS_BYPASS
/*----------------------------------------------------------------------------
 * Name: _set_aud_bypass_mode_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _set_aud_bypass_mode_idx(UINT16 ui2_idx)
{
    INT32 i4_ret = NAVR_OK;

    g_b_aud_srs_bypass_mode = ui2_idx;
    i4_ret = c_scc_aud_set_srs_bypass(h_g_acfg_scc_main_aud,(BOOL)ui2_idx);

    #ifndef APP_C4TV_SUPPORT
	if (ui2_idx == 0)
		a_cfg_custom_Set_MS12_PCMR_OnOff(FALSE); // Ben 20161006
	#endif

    if(i4_ret != SMR_OK)
    {
        DBG_LOG_PRINT(("!!!!%s : aud_bypass_mode_idx fail\n", __FUNCTION__));
    }
    return i4_ret;
}
#endif /* FAC_AUD_SRS_BYPASS */
#ifdef FAC_HDMI_PORT_NUM_SETTING
/*---------------------------------------------------------------------------
 * Name: _nav_fac_c_rm_set_hdmi_num
 *Description: 
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _nav_fac_c_rm_set_hdmi_num(UINT8 ui1_num)
{
    DBG_LOG_PRINT(("!!!!%s line %d\n", __func__, __LINE__));
    INT32 i4_ret;
    UINT8 ui_hdmi_port = 0;
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T  z_info_size = sizeof(t_op_info);
    
    UINT16  ui2_eep_add;
    SIZE_T  z_size_eep_add=sizeof(UINT16);
    
    DRV_CUSTOM_EEPROM_TYPE_T  t_eepom_info;
    SIZE_T  z_size_eep_info = sizeof(DRV_CUSTOM_EEPROM_TYPE_T); 
    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    //sam 120529 reserve for multi-IO request
	//***************************************************//
	// //sam 120529 reserve for multi-IO request
	//at_post_reg_custom0 -->HDMIx4 ,combine Comp-2 & RGB
	//at_post_reg_custom1 -->HDMIx3 ,combine Comp-2 & RGB
	//at_post_reg_custom2 -->HDMIx4 ,cancel Comp-2 & RGB
	//at_post_reg_custom3 -->HDMIx3 ,cancel Comp-2 & RGB
	//***************************************************//
	
    ui_hdmi_port = ui1_num;  
    
    t_op_info.e_op_type =  DRV_CUSTOM_OPERATION_TYPE_MISC_GET;
    t_op_info.u.t_misc_get_info.e_misc_type = DRV_CUSTOM_GET_ONE_BINARY_EEPROM_OFFSET;
    t_op_info.u.t_misc_get_info.pv_get_info = (VOID *)&ui2_eep_add;
    t_op_info.u.t_misc_get_info.pz_size = (VOID *)(&z_size_eep_add);

    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_info_size
                    );
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_get_comp fail i4_ret %d\n", __func__, i4_ret));
    }
    
    c_memset(&t_eepom_info, 0, sizeof(DRV_CUSTOM_EEPROM_TYPE_T));
    t_eepom_info.ui2_offset = ui2_eep_add;
    t_eepom_info.ui2_length = 1;
    t_eepom_info.aui1_data = &ui_hdmi_port;
    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type =  DRV_CUSTOM_OPERATION_TYPE_MISC_SET;
    t_op_info.u.t_misc_set_info.e_misc_type = DRV_CUSTOM_EEPROM_WRITE;
    t_op_info.u.t_misc_set_info.pv_set_info = (VOID*)&t_eepom_info;
    t_op_info.u.t_misc_set_info.z_size = z_size_eep_info;
    t_op_info.u.t_misc_set_info.b_store = TRUE;

	/* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_set_comp fail i4_ret %d\n", __func__, i4_ret));
    }
    return i4_ret;
}
/*---------------------------------------------------------------------------
 * Name: _nav_fac_c_rm_get_hdmi_num
 *Description:
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _nav_fac_c_rm_get_hdmi_num(UINT8* pui1_num)
{
    DRV_CUST_OPERATION_INFO_T t_op_info; 
    DRV_CUSTOM_EEPROM_TYPE_T t_eep_info; 
    INT32   i4_ret = NAVR_OK;
    UINT8 ui_hdmi_port = 0;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T); 
    SIZE_T z_size_eep_info = sizeof(DRV_CUSTOM_EEPROM_TYPE_T); 

    UINT16  ui2_eep_add;
    SIZE_T  z_size_eep_add=sizeof(UINT16);
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_MISC_GET;
    t_op_info.u.t_misc_get_info.e_misc_type = DRV_CUSTOM_GET_ONE_BINARY_EEPROM_OFFSET;
    t_op_info.u.t_misc_get_info.pv_get_info = (VOID *)&ui2_eep_add;
    t_op_info.u.t_misc_get_info.pz_size = (VOID *)(&z_size_eep_add);

    i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size
                            );
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_get_comp fail i4_ret %d\n", __func__, i4_ret));
        return i4_ret;
    }

    /* fill data */
    t_eep_info.ui2_offset = ui2_eep_add;
    t_eep_info.ui2_length = 1;
    t_eep_info.aui1_data = &ui_hdmi_port;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T)); 
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_MISC_GET; 
    t_op_info.u.t_misc_get_info.e_misc_type = DRV_CUSTOM_EEPROM_READ; 
    t_op_info.u.t_misc_get_info.pv_get_info = (VOID*) &t_eep_info; 
    t_op_info.u.t_misc_get_info.pz_size = (VOID*)(&z_size_eep_info); 
    /* get from driver */ 
    i4_ret = c_rm_get_comp(DRVT_CUST_DRV, 
                            DRV_CUST_COMP_ID, 
                            FALSE, 
                            ANY_PORT_NUM, 
                            0, 
                            &t_op_info, 
                            &z_size 
                            );
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_get_comp fail i4_ret %d\n", __func__, i4_ret));
        return i4_ret;
    }

//***************************************************//
// //sam 120529 reserve for multi-IO request
//at_post_reg_custom0 -->HDMIx4 ,combine Comp-2 & RGB
//at_post_reg_custom1 -->HDMIx3 ,combine Comp-2 & RGB
//at_post_reg_custom2 -->HDMIx4 ,cancel Comp-2 & RGB
//at_post_reg_custom3 -->HDMIx3 ,cancel Comp-2 & RGB
//***************************************************//

	*pui1_num = ui_hdmi_port;

    return i4_ret;

}
#endif  /* FAC_HDMI_PORT_NUM_SETTING */
 /*----------------------------------------------------------------------------
 * Name: _nav_fac_bklight_timer_nfy_fct
 * Description: bklight_counter's nfy fct, do update the widget text.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_bklight_timer_nfy_fct(HANDLE_T  h_timer,VOID*     pv_tag)//moore 080924
{
    nav_fac_async_dispatch_msg(FAC_MSG_BLT_LT_UPDATE,
                        NULL,
                        NULL);
}

 /*----------------------------------------------------------------------------
 * Name: _nav_fac_bklight_timer_start
 * Description: Start the backlight counter.
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_bklight_timer_start(NAV_FAC_T* pt_this)    //moore 080924
{
    INT32   i4_ret;

    i4_ret = c_timer_start(
                    pt_this->h_bklight_timer,
                    BKLIGHT_TIMER_DELAY_1MIN,//BKLIGHT_TIMER_DELAY_1SEC,
                    X_TIMER_FLAG_REPEAT,
                    _nav_fac_bklight_timer_nfy_fct,   //on time do this
                    pt_this
                    );
    if (i4_ret != NAVR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start bds::h_bklight_timer failed!"));
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_ipt_pw_timer_nfy_fct
 * Description: bklight_counter's nfy fct, do update the widget text.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_ipt_pw_timer_nfy_fct(HANDLE_T	h_timer,VOID*	  pv_tag)	//Soar add for key timeout 20111013
{
   
   NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
   NAV_FAC_T*  pt_this = &t_g_nav_fac; 
   pt_fac->ui2_key_num2 = 0;	//kyo_20111028	 
   _nav_fac_ipt_pw_timer_stop(pt_this);
   //DBG_LOG_PRINT("!!!!%s\n", __func__);
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_ipt_timer_start
 * Description: Start the input password counter.
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_ipt_pw_timer_start(NAV_FAC_T* pt_this)    //Soar add for key timeout 20111013
{
    INT32   i4_ret;

    i4_ret = c_timer_start(
                    pt_this->h_fac_ipt_pw_timer,
                    NAV_FAC_TRIGGER_IPT_WND_TIME,     //5s,
                    X_TIMER_FLAG_REPEAT,
                    _nav_fac_ipt_pw_timer_nfy_fct,   //on time do this
                    pt_this
                    );
    if (i4_ret != NAVR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start bds::h_bklight_timer failed!"));
    }
}

 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_ipt_pw_timer_stop
 * Description: Disable back light counter.
 * Inputs:  pt_this
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_ipt_pw_timer_stop(NAV_FAC_T* pt_this) //Soar add for key timeout 20111013
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_fac_ipt_pw_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_fac_ipt_pw_timer);
    if (i4_ret != NAVR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop fac::h_fac_ipt_pw_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_init
 * Description: initialize this component  this component
 * Inputs:  pt_ctx     point the environment of the navigater module requested
 * Outputs: NONE
 * Returns: NAVR_OK    routine is successful
 *          NAVR_FAIL  routine is failed
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_FAC_T*  pt_this = &t_g_nav_fac;
    INT32       i4_ret;
	UINT32      ui4_rmv_dev_nfy;
    pt_this->h_bklight_timer   = NULL_HANDLE;
	pt_this->h_fac_ipt_pw_timer= NULL_HANDLE;   //Soar add for key timeout 20111013

    /* Create & Start the back light timer */
    i4_ret = c_timer_create(&(pt_this->h_bklight_timer));    //moore 080924
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

	/* Create & Start the input password timer */	//Soar add for key timeout 20111013
    i4_ret = c_timer_create(&(pt_this->h_fac_ipt_pw_timer));   
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
	
    _nav_fac_bklight_timer_start(pt_this);       //moore 080924
    bklight_buffer = 0;

    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );

	i4_ret = a_rmv_dev_reg_monitor(
					inx_nav_fac_usb_pld_rmv_dev_nfy,
					NULL,
					&ui4_rmv_dev_nfy);
	if(i4_ret != NAVR_OK){
        DBG_LOG_PRINT((" %s a_rmv_dev_reg_monitor fail Line: %d\n", __FUNCTION__, __LINE__));
    }

    #ifdef INX_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
    c_cli_attach_cmd_tbl(at_factory_cmd_tbl, CLI_CAT_ROOT, CLI_GRP_GUI);
    #endif

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_deinit
 * Description: uninitialize this component
 * Inputs:  NONE
 * Outputs: NONE
 * Returns: NAVR_OK    routine is successful
 *          NAVR_FAIL  routine is failed
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_deinit(VOID)
{
    NAV_FAC_T*  pt_this = &t_g_nav_fac;
    INT32       i4_ret;

    _nav_fac_bklight_timer_stop(pt_this);
	_nav_fac_ipt_pw_timer_stop(pt_this);    //Soar add for key timeout 20111013

    if (c_handle_valid(pt_this->h_bklight_timer)) {
        c_timer_delete(pt_this->h_bklight_timer);
    }

    if (c_handle_valid(pt_this->h_fac_ipt_pw_timer)) {	//Soar add for key timeout 20111013
        c_timer_delete(pt_this->h_fac_ipt_pw_timer);
    }

    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->h_bklight_timer   = NULL_HANDLE;

    #ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
    i4_ret = a_rmv_dev_unreg_monitor(pt_this->ui4_rmv_dev_nfy);
    if(i4_ret != RMVR_OK){
        DBG_LOG_PRINT((" %s a_rmv_dev_unreg_monitor fail Line: %d\n", __FUNCTION__, __LINE__));
    }
    #endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_is_key_handler
 * Description: judge a key is an hot key of this component
 * Inputs:  pt_ctx        the environment of the navigater module requested
 *          ui4_key_code  the key value
 * Outputs: NONE
 * Returns: TRUE          is the hot key
 *          FALSE         is not the hot key
 ----------------------------------------------------------------------------*/
static BOOL _nav_fac_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_FAC_T*  pt_this = &t_g_nav_fac;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI)) {
        return FALSE;
    }

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_activate
 * Description: active this component
 * Inputs:  pt_ctx        the environment of the navigater module requested
 *          ui4_key_code  the key value
 * Outputs: NONE
 * Returns: NAVR_NO_ACTION
 *          NAVR_OK
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_FAC_T*  pt_this = &t_g_nav_fac;
    INT32       i4_ret;

    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
    
    if (a_tv_net_get_tv_svc_status () == APP_TV_NET_SVC_STATUS_PAUSED)
    {
        nav_resume_self ();
    }
    else
    {
        a_msg_convert_resume_navigator();
    }
 
    nav_set_component_visible(NAV_COMP_ID_FAC_INX);//joe.zy
    pt_this->b_is_on = TRUE;

    #ifdef LINUX_TURNKEY_SOLUTION
    //Enter Cli mode 
    //cmd_convert_send_cmd("\n:am,am,:cli_on\n");  //ke_vizio_20121116 modify coz it will reboot when DUT power on.
    #endif

#ifdef FAC_AUD_SRS_BYPASS  // Reset aud bypass by mode
    if(g_b_aud_srs_bypass_mode == FALSE)
    {
        _set_aud_bypass_mode_idx(0);
    }
    else
    {
        _set_aud_bypass_mode_idx(1);
    }
#endif
	
    if (b_nav_fac_aq_bypass_on_off == TRUE)
	{
		acfg_cust_audio_enable_srs_bypass_mode(1);
	}
    
#ifdef FAC_BT_TESTBLE //Ben 20170809
	if (b_nav_fac_bt_testble_on_off == FALSE)
	{
		a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);
		a_bluetooth_gattc_rssi_meter_hide();
	}
	else
	{
		bt_gatt_cli_set_allow_pair_4_test_tool(TRUE);
		a_bluetooth_gattc_rssi_meter_dialog_enable(TRUE);
	}
#endif
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_hide
 * Description: hide(inactivate) this component
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_NO_ACTION
 *          NAVR_OK
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_hide(
                    VOID
                    )
{
    NAV_FAC_T*  pt_this = &t_g_nav_fac;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->t_view_hdlr.pf_hide();
    pt_this->b_is_on = FALSE;
    nav_return_activation(NAV_COMP_ID_FAC_INX);//joe.zy

    //Emerson Add 2008-0918
    b_nav_fac_eep_init_done = FALSE;
    b_nav_fac_reset_done	 = FALSE;
	b_nav_fac_get_led_info_done = FALSE;
	
	b_nav_fac_install_ulpk_done = FALSE;/*//sam 0331 for ULPK install in fac menu*/	

    //ke_vizio_20121115 add for reset user clr temp.
    a_cfg_cust_factory_clr_temp_def_update(&b_def_clr_temp_update);

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_stop_timer
 * Description: Disable back light counter.
 * Inputs:  pt_this
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_bklight_timer_stop(NAV_FAC_T* pt_this) //moore 080924
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_bklight_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_bklight_timer);
    if (i4_ret != NAVR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop fac::h_bklight_timer failed!"));
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_bklight_timer_inc_EEP_save
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_bklight_timer_inc_EEP_save(void) //moore 080924
{

#if 1 //@jh todo
    INT32  i4_timer_curr;
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = a_cfg_cust_fac_get_backlight_lifetime(&i4_timer_curr);
    if (i4_ret != APP_CFGR_OK)
        return TVR_FAIL;
    i4_timer_curr++;
    i4_ret = a_cfg_cust_fac_set_backlight_lifetime(i4_timer_curr);
    if (i4_ret != APP_CFGR_OK)
        return TVR_FAIL;
#endif
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_bklight_timer_regular_update
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_bklight_timer_regular_update(NAV_FAC_T* pt_this)  //moore 080924
{
    INT32   i4_ret = APP_CFGR_OK;

    /* Stop the timer */
    _nav_fac_bklight_timer_stop(pt_this);

    /* Customized regular update function */
    bklight_buffer++;

    if(bklight_buffer>= 60)  // hour
    {
        bklight_buffer = 0;
        i4_ret = _nav_fac_bklight_timer_inc_EEP_save();
        if (i4_ret != APP_CFGR_OK)
            return TVR_FAIL;
    }

    /* Restart the timer */
    _nav_fac_bklight_timer_start(pt_this);

    return APP_CFGR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_bklight_timer_DCoff_destroy
 * Description: Disable back light counter.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 _nav_fac_bklight_timer_DCoff_destroy(NAV_FAC_T* pt_this) //moore 080924
{
    INT32       i4_ret;

    /* Stop the timer */
    _nav_fac_bklight_timer_stop(pt_this);

    //buffer > 30min do saveing
    if(bklight_buffer> 30)
    {
        bklight_buffer = 0;
        i4_ret = _nav_fac_bklight_timer_inc_EEP_save();
        if (i4_ret != APP_CFGR_OK)
            return TVR_FAIL;
    }

    if (c_handle_valid(pt_this->h_bklight_timer)) {
        c_timer_delete(pt_this->h_bklight_timer);
    }
    pt_this->h_bklight_timer   = NULL_HANDLE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_handle_msg
 * Description: handle the message from navigater controller
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    //ke_vizio_20130911 add
    switch(pt_ui_msg->e_id)
    {  
        case NAV_UI_MSG_POWER_OFF:
        {
            #ifdef APP_INX_DFT_DC_ON_RESET
            UINT8 ui1_mode = 0;
            UINT32 ui4_fac_bits = 0;

            a_cfg_get_factory_mode(&ui1_mode);
            
            if(ui1_mode & APP_CFG_FAC_MODE_BURNING_MASK)
            {
                a_cfg_cust_fac_get(&ui4_fac_bits);
                
                nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, 0); // Burn mode off before DC power off.
                
                a_cfg_set_factory_mode(ui1_mode | APP_CFG_FAC_MODE_CUSTOM0_MASK);
                a_cfg_cust_fac_set(ui4_fac_bits | APP_CFG_CUST_FAC_DC_ON_RESET);

                a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT); // Set wizard init when DC on at first time
            }
            #endif

		#ifdef FAC_AUD_SRS_BYPASS	
			g_b_aud_srs_bypass_mode = FALSE;	// Ben 20161013, reset SRS bypass when DC off.
		#endif

		#ifdef FAC_BT_TESTBLE // Ben 20170809, reset BLE when DC off
			b_nav_fac_bt_testble_on_off = FALSE;
        #endif

            //ke_vizio_20161109 add
            if(nav_fac_sce_pat_is_on())
            {
                nav_fac_sce_pat_enable_pat(FALSE);
                nav_fac_sce_pat_set_on_off_flag(FALSE);
            }
            break;
        }
        default:
            break;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_put_key_stack
 * Description: Put all key into a stack
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
VOID _nav_fac_put_key_stack(UINT32 ui4_key_code)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UINT16      ui2_idx   = 0;

    /* Shift the stack2 */
    for (ui2_idx = 0;
         ui2_idx < (NAV_FAC_KEY_STACK_NUM-1) ;
         ui2_idx++)
    {
        pt_fac->at_key_stack2[ui2_idx] = pt_fac->at_key_stack2[ui2_idx+1];

    }
    /* Put in the key code to the top of stack2 */
    pt_fac->at_key_stack2[NAV_FAC_KEY_STACK_NUM-1] = ui4_key_code;
    pt_fac->at_key_stack2[NAV_FAC_KEY_STACK_NUM] = 0;

}

// Mill 20090312 Erase Partition 5 START
// write 128KB 0xFF to partition 5.
#include "c_fm.h"
#include "u_fm.h"
#define Partition_5_Length (128 * 1024)
#define Data_Length (32 * 1024)


#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add




/*-----------------------------------------------------------------------------
 * Name: nav_fac_model_name_get_max_cnt_by_panel_id
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 nav_fac_model_name_get_max_cnt_by_panel_id(
                    UINT32                      ui4_panel_id,
                    UINT16 *                    pt_ui2_mn_cnt
                    )
{
    switch(ui4_panel_id)
    {
    default:
        *pt_ui2_mn_cnt = sizeof(_ar_Fac_Model_Name_default_Table) / sizeof(NAV_FAC_MODEL_NAME_T);
        break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_model_name_get_model_name_by_panel_id
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 nav_fac_model_name_get_model_name_by_panel_id(
                    UINT32                      ui4_panel_id,
                    UINT16                      ui2_mn_idx,
                    CHAR *                      pt_s_mn_str
                    )
{
    switch(ui4_panel_id)
    {
    default:
        c_memcpy(   pt_s_mn_str,
                    _ar_Fac_Model_Name_default_Table[ui2_mn_idx].s_model_name,
                    c_strlen(_ar_Fac_Model_Name_default_Table[ui2_mn_idx].s_model_name));
        break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_model_name_get_current_model_name_id
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 nav_fac_model_name_get_current_model_name_id(
                    UINT16*                     pt_ui2_model_name_id
                    )
{
    UINT16                      ui2_max_cnt, ui2_i;
    UINT32                      ui4_read_byte;
    CHAR                        s_data_r[16];

    /* Get model name from EEPROM */
    c_memset(s_data_r, 0, sizeof(s_data_r));
    a_cfg_eep_raw_read(EEP_MODEL_NAME, s_data_r, 16, &ui4_read_byte);


    /* Compare Model name in EEPROM with Model name table */
    nav_fac_model_name_get_max_cnt_by_panel_id(a_cfg_custom_get_cur_panelID(), &ui2_max_cnt);
    for(ui2_i=0; ui2_i<ui2_max_cnt; ui2_i++)
    {
        c_memset(s_model_name_string, 0, sizeof(s_model_name_string));
        nav_fac_model_name_get_model_name_by_panel_id( a_cfg_custom_get_cur_panelID(), ui2_i, s_model_name_string);

        if(0 == c_strcmp(s_model_name_string, s_data_r))
            break;
    }

    /* Model name is found */
    if(ui2_i<ui2_max_cnt)
        *pt_ui2_model_name_id = ui2_i;
    /* For others, assign to 1st id */
    else
        *pt_ui2_model_name_id = 0;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_model_name_get_default_model_name_by_panel_id
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/

INT32 nav_fac_model_name_get_default_model_name_by_panel_id(
                    UINT32                      ui4_panel_id,
                    CHAR *                      pt_s_mn_str
                    )
{
    //ke_vizio_20110420
    UINT16 ui2_id = 0;
    nav_fac_get_current_model_id_by_panel(&ui2_id);
    
    nav_fac_model_name_get_model_name_by_panel_id( ui4_panel_id, ui2_id, pt_s_mn_str);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_model_name_is_valid
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/

BOOL nav_fac_model_name_is_valid(
                    CHAR *                      pt_s_mn_str
                    )
{
   UINT16       ui2_i, ui2_blank_cnt = 0;

    /* Inavlid if 1st Byte is String Terminator */
    if(pt_s_mn_str[0]=='\0') {
        return FALSE;
    }
    /* Invalid if First 4 Byte are all 0x00 */
    else if(pt_s_mn_str[0]==0x00 && pt_s_mn_str[1]==0x00 && pt_s_mn_str[2]==0x00 && pt_s_mn_str[3]==0x00) {
        return FALSE;
    }

    /* Check if first 4 bytes are blank */
    for(ui2_i=0; ui2_i<4; ui2_i++)
    {
        if(pt_s_mn_str[ui2_i]==0x00 || pt_s_mn_str[ui2_i]==0x20)
        {
            ui2_blank_cnt++;
        }
    }
    if(ui2_blank_cnt==4) {
        return FALSE;
    }

    /* Check if first 5 bytes are printable characters */
    for(ui2_i=0; ui2_i<5; ui2_i++)
    {
        if(((pt_s_mn_str[ui2_i]>=0x20) && (pt_s_mn_str[ui2_i]<=0x7E)) || (pt_s_mn_str[ui2_i]=='\0'))
        {
            if(pt_s_mn_str[ui2_i]=='\0')
                break;
        }
        else
            return FALSE;
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_model_name_write_default_model_name
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 nav_fac_model_name_write_default_model_name(VOID)
{
	UINT32		ui4_write_byte;
	INT32       i4_ret;

    c_memset(s_model_name_string, 0, 16);
    nav_fac_model_name_get_default_model_name_by_panel_id(a_cfg_custom_get_cur_panelID(), s_model_name_string);
    i4_ret = a_cfg_eep_raw_write(EEP_MODEL_NAME,
                                 s_model_name_string,
                                 c_strlen(s_model_name_string)+1,
                                 &ui4_write_byte);
    if(i4_ret!=APP_CFGR_OK) {
		DBG_LOG_PRINT(("a_cfg_eep_raw_write() failed. i4_ret = %d at line %d of Nav_fac.c.\r\n", i4_ret, __LINE__));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
//ke_vizio_20110420
/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_current_model_id_by_panel
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 nav_fac_get_current_model_id_by_panel(UINT16 *pui2_id)
{
    if(pui2_id == NULL)
    {
        return NAVR_INV_ARG;
    }
    
    UINT32 ui4_panel_id = a_cfg_custom_get_cur_panelID();
    UINT16 ui2_idx = 0;

    *pui2_id = ui2_idx;
    for(ui2_idx = 0; ui2_idx < (sizeof(_ar_Fac_Panel_ID_Map)/sizeof(PANEL_ID_T));ui2_idx++)
    {
        if(ui2_idx >= (sizeof(_ar_Fac_Panel_ID_Map)/sizeof(PANEL_ID_T))){
            break;
        }
        
        if(_ar_Fac_Panel_ID_Map[ui2_idx].ui4_panel_id == ui4_panel_id){
           *pui2_id = ui2_idx;
            break;
        }
    }


    return 0;
}

#endif

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
/*-----------------------------------------------------------------------------
 * Name: nav_fac_sec_pat_is_on
 * Description: Indicate that SCE pattern is on or off.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL nav_fac_sce_pat_is_on(VOID)
{
    return b_nav_fac_wb_intrnl_pat_on_off;
}
/*-----------------------------------------------------------------------------
 * Name: nav_fac_sce_pat_set_on_off_flag
 * Description: Indicate that SCE pattern is on or off.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
VOID nav_fac_sce_pat_set_on_off_flag(BOOL b_on)
{
    b_nav_fac_wb_intrnl_pat_on_off = b_on;
}


/*-----------------------------------------------------------------------------
 * Name: nav_fac_sce_pat_get_level
 * Description: Get current level of SCE pattern in factory menu.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
UINT16 nav_fac_sce_pat_get_level(VOID)
{
    return ui2_nav_fac_wb_intrnal_pat_val;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_sce_pat_set_level
 * Description: Set the level of SCE pattern in factory menu.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
VOID nav_fac_sce_pat_set_level(UINT16 ui2_val)
{
    ui2_nav_fac_wb_intrnal_pat_val = ui2_val;
}


/*-----------------------------------------------------------------------------
 * Name: nav_fac_sce_pat_enable_pat
 * Description: Enable/disable SCE pattern
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_sce_pat_enable_pat(BOOL b_enable)
{
    INT32   i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T t_cust_set_info = {0};  //ke_vizio_20121129 add
    DRV_CUSTOM_SCE_PATTERN_T t_set_info;
    SIZE_T z_size = sizeof(DRV_CUSTOM_SCE_PATTERN_T);

    if(b_enable)
    {
        t_set_info.ui1_OnOff = TRUE;
        t_set_info.ui2_Ydata = ui2_nav_fac_wb_intrnal_pat_val;

        
        t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_WB_Pattern;
        t_cust_set_info.pv_set_info = (VOID *)&t_set_info;
        t_cust_set_info.z_size = z_size;
        t_cust_set_info.b_store = TRUE;
        i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("!!!!%s : DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET fail\n", __func__));
            return i4_ret;
        }
        /* Disable the power saving timer of VGA/YPbPr/... */
        a_nav_power_set_component_enable(FALSE);

        /* Hide "No Signal" text on screen */
        if(nav_is_signal_loss(TV_WIN_ID_MAIN))
        {
            nav_enable_scrn_svr(FALSE);
        }

        /* Update color temp coz the color temp will not be updated before activating internal pattern */
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
        if(i4_ret<0) {
            DBG_LOG_PRINT(("a_cfg_av_update() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        }

    }
    else
    {
        t_set_info.ui1_OnOff = FALSE;
        t_set_info.ui2_Ydata = 0;
        
        t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_WB_Pattern;
        t_cust_set_info.pv_set_info = (VOID *)&t_set_info;
        t_cust_set_info.z_size = z_size;
        t_cust_set_info.b_store = TRUE;
        i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("!!!!%s : DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET fail\n", __func__));
            return i4_ret;
        }

        /* Recover the power saving timer of VGA/YPbPr/... */
        a_nav_power_set_component_enable(TRUE);

        /* Recover "No Signal" text */
        if(nav_is_signal_loss(TV_WIN_ID_MAIN))
        {
            nav_enable_scrn_svr(TRUE);
        }
    }
    return NAVR_OK;
}

#endif

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_inx_ui_check_key
 * Description: This function judge all key sequence and give an result.
 * Inputs: key_arr
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL _nav_fac_inx_ui_check_key(UINT32 key_arr[],UINT8 length)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UINT8 ui1_idx = 0;

    //UINT32 ui4_key_pwd[NAV_FAC_KEY_STACK_NUM] = key_arr;

    for(ui1_idx = 0; ui1_idx < (length); ui1_idx++)
    {
    
        if(pt_fac->at_key_stack2[ui1_idx] != key_arr[ui1_idx])
        {
            return FALSE;
        }
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name:_nav_fac_msg_hdlr_key_input
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32  _nav_fac_msg_hdlr_key_input(UINT32    ui4_key_code,
                                          UINT32    ui4_raw_data)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UINT32              ui4_rc_code = 0;
    CHAR     s_active_app[APP_NAME_MAX_LEN];	//Emerson Add 20080911

    /* Get key code (ignore event group). */
    ui4_rc_code = IOM_GET_EVT_GRP_ID (ui4_key_code);

    //Emerson Add 20080911
    a_am_get_active_app (s_active_app);

    /* Put all numerals inputed during the channel OSD shows to a stack */
    _nav_fac_put_key_stack(ui4_rc_code);
    /* When the total input numerals is equal to NAV_FAC_KEY_STACK_NUM,
          check whether those numerals put in the stack are correct. */
    /* Record the total number of password which user already inputed */
    pt_fac->ui2_key_num2++;

    //For check pwd of FAC menu 
    if(pt_fac->ui2_key_num2 == NAV_FAC_KEY_STACK_NUM)
    {
    	printf("\r\n %s%d ui2_key_num2 = NAV_FAC_KEY_STACK_NUM\r\n",__FUNCTION__,__LINE__);
        if( _nav_fac_inx_ui_check_key(INX_PD_FAC_PASSWORD_DEF,pt_fac->ui2_key_num2) )
        {
            if ((c_strcmp (s_active_app, MENU_NAME) == 0))
            {
                printf("\n %s,%d inx_ui_key=3210",__FUNCTION__,__LINE__);
                if(inx_at_ui_switch != INX_AT_SWITCH_PD)
                {
                    inx_at_ui_switch = INX_AT_SWITCH_PD;
                    inx_fac_items_set_entry_hlt_idx(0);
                }
				
                /* If correct password is inputed, show the FAC menu */
                a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*) BTN_PESUDO_FAC_MENU, NULL);
            }
			// Initial ELCS valiable value 
       	 	b_nav_fac_get_ELCS = FALSE;
        }
        else if( _nav_fac_inx_ui_check_key(INX_FAC_PASSWORD_DEF,pt_fac->ui2_key_num2) )
		{
			if ((c_strcmp (s_active_app, MENU_NAME) == 0))
			{
				printf("\n %s,%d inx_ui_key=3481",__FUNCTION__,__LINE__);
			    if(inx_at_ui_switch != INX_AT_SWITCH_FAC)
                {         
				    inx_at_ui_switch = INX_AT_SWITCH_FAC;
                    inx_fac_items_set_entry_hlt_idx(0);
                }

                /* If correct password is inputed, show the FAC menu */
				a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*) BTN_PESUDO_FAC_MENU, NULL);
			}
            // Initial ELCS valiable value 
        	b_nav_fac_get_ELCS = FALSE;
		}
		else if(_nav_fac_inx_ui_check_key(INX_KEYPAD_PASSWORD_DEF,pt_fac->ui2_key_num2))
		{
			//only active application on input source
			if((c_strcmp(s_active_app,NAV_NAME) == 0))
			{
					printf("\r\n %s%d inx_ui_key= input -> vol+ -> vol- -> vol+ -> vol- \r\n",__FUNCTION__,__LINE__);
					INX_fac_burning_off();
			}
		}
        pt_fac->ui2_key_num2 = 0;
    }
	
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_dispatch_msg
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_fac_dispatch_msg(FAC_MSG_T       e_msg,
                                 VOID*          pv_param1,
                                 VOID*          pv_param2)
{
    NAV_FAC_T*  pt_this = &t_g_nav_fac;

    switch (e_msg)
    {
        case FAC_MSG_KEY_INPUT:
        {
            _nav_fac_msg_hdlr_key_input( (UINT32)  pv_param1,
                                         (UINT32)  pv_param2 );
        }
        break;
        case FAC_MSG_BLT_LT_UPDATE://Emerson Add for Backlight LT update 0926
            _nav_fac_bklight_timer_regular_update(pt_this);
            break;
            
        default:
            break;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_async_dispatch_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_async_dispatch_msg(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    /* execute in navigator's thread context */
     _nav_fac_dispatch_msg( (FAC_MSG_T) (UINT32) pv_tag,
                  pv_tag2,
                  pv_tag3 );
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_iom_nfy_fct
 *
 * Description: This callback function will be called by the IO Manager when
 *              system events are triggered from the remote control.
 *
 * Inputs:  pv_nfy_tag      Contains a tag value.
 *          e_nfy_cond      Contains the notify condition.
 *          ui4_evt_code    Contains the event code.
 *          ui4_data        Contains information related to the event.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_iom_nfy_fct (VOID*             pv_nfy_tag,
                                  IOM_NFY_COND_T    e_nfy_cond,
                                  UINT32            ui4_evt_code,
                                  UINT32            ui4_data)
{
    UINT32  ui4_rc_code = 0;
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    NAV_FAC_T*  pt_this = &t_g_nav_fac;

    /* Get key code (ignore event group). */
    ui4_rc_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);
	// keypad key
	if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN && (nav_get_key_source() == KEY_SRC_FRONT_PANEL))
	{
		//printf("\r\n %s%d,KEY_SRC_FRONT_PANEL \r\n",__FUNCTION__,__LINE__);
		if(ui4_rc_code==BTN_INPUT_SRC)
		{
			//printf("\r\n %s%d,BTN_INPUT_SRC \r\n",__FUNCTION__,__LINE__);
			_nav_fac_ipt_pw_timer_start(pt_this);
			pt_fac->ui2_key_num2 = 0;
			
		}
		nav_fac_async_dispatch_msg(FAC_MSG_KEY_INPUT,
                                         (VOID *) ui4_evt_code,
                                         (VOID *) ui4_data);
	}
	//IR key
	else if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN && (nav_get_key_source() == KEY_SRC_REMOTE_CTRL))
	{
		//printf("\r\n %s%d,KEY_SRC_REMOTE_CTRL \r\n",__FUNCTION__,__LINE__);
		switch(ui4_rc_code)
		{
			case BTN_DIGIT_0:
			case BTN_DIGIT_3:
			case BTN_DIGIT_2:
			case BTN_DIGIT_4:
            case BTN_DIGIT_1:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_PREV_PRG:
            case BTN_CUSTOM_3:  
            case BTN_MENU:
				/* Async invoke dispatch key input */
				if(BTN_CUSTOM_3 == ui4_rc_code)
	            {
	                 ui4_evt_code = BTN_MENU;
					 _nav_fac_ipt_pw_timer_start(pt_this);
	            }
				else if(BTN_MENU == ui4_rc_code)
				{
					//printf("\r\n %s%d,BTN_MENU \r\n",__FUNCTION__,__LINE__);
					_nav_fac_ipt_pw_timer_start(pt_this);
	                pt_fac->ui2_key_num2 = 0;
				}
				nav_fac_async_dispatch_msg(FAC_MSG_KEY_INPUT,
                                         (VOID *) ui4_evt_code,
                                         (VOID *) ui4_data);
				break;
			default:
				pt_fac->ui2_key_num2 = 0;
				break;
				
		}
	}
    if ( (e_nfy_cond == IOM_NFY_COND_BTN_DOWN) && (ui4_rc_code == BTN_POWER) ) //moore 080926
    {
        if(a_bgm_is_running() == FALSE){  //ke_vizio_20141105 add.
            _nav_fac_bklight_timer_DCoff_destroy(pt_this);//moore 080926
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_register_io_mngr
 * Description: Register io manager
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_register_io_mngr(VOID)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;

    INT32   i4_ret;
    IRRC_SETTING_T  t_irrc_setting;

    /* IOM Init */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 60;  /* repeat key */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20;   /* repeat key */
    t_irrc_setting.b_notify_raw_data        = TRUE;                  /* request to notify anyway. */

    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) & t_irrc_setting,
                         NULL,
                         _nav_fac_iom_nfy_fct,
                         &pt_fac->h_iom);
    if(i4_ret < IOMR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_async_dispatch_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_async_dispatch_msg(
                    FAC_MSG_T                   e_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2)
{
    /* execute in caller's thread context */
    nav_request_context_switch(_nav_fac_async_dispatch_msg,
                               (VOID *) (UINT32) e_msg,
                               pv_param1,
                               pv_param2);

    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_unlock_key
 * Description: Unlock remote control and locak key when fac menu is launched
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_unlock_key(VOID)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    INT32               i4_ret;
    UINT64              ui8_unlock_src;

    ui8_unlock_src  = IOM_EVT_SRC_TO_MASK(KEY_SRC_SW) |
                    IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                    IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);

    i4_ret = c_iom_set (pt_fac->h_iom,
                        IOM_SET_IRRC_EVT_SRC_MASK,
                        (const VOID*)&ui8_unlock_src,
                        sizeof(UINT64));
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_boolean_to_text
 * Description: Judge which text (Yes/No) should be printed
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
VOID nav_fac_boolean_to_text(
                    UINT32                  ui4_val,
                    UTF16_T*                w2s_bool_string
                    )
{
    if (ui4_val == 0 ) {
        c_uc_w2s_strcpy(w2s_bool_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_NO));
    }
    else {
        c_uc_w2s_strcpy(w2s_bool_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_YES));
    }
 }

/*-----------------------------------------------------------------------------
 * Name: nav_fac_boolean_on_off_to_text
 * Description: Judge which text (On/Off) should be printed
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
VOID nav_fac_boolean_on_off_to_text(
                    UINT32                  ui4_val,
                    UTF16_T*                w2s_bool_string
                    )
{
    if (ui4_val == 0 ) {
        c_uc_w2s_strcpy(w2s_bool_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_OFF));
    }
    else {
        c_uc_w2s_strcpy(w2s_bool_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ON));
    }
 }


/*-----------------------------------------------------------------------------
 * Name: nav_fac_number_to_string
 * Description: Transfer number to string
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

VOID nav_fac_number_to_string(
                    INT32                  ui4_number,
                    UTF16_T*                w2s_string
                    )
{
    CHAR                s_value[NAV_FAC_MENU_ITEM_CONTENT_LEN + 1];

    c_sprintf(s_value, "%d", ui4_number);
    c_uc_ps_to_w2s(s_value, w2s_string, (NAV_FAC_MENU_ITEM_CONTENT_LEN + 1));
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_lit_number_to_string
 * Description: Transfer number to string
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
VOID nav_fac_lit_number_to_string(
                    UINT32                  ui4_number_hun,
                    UINT32                  ui4_number_unit,
                    UTF16_T*                w2s_string
                    )
{
    CHAR s_value[NAV_FAC_MENU_ITEM_CONTENT_LEN + 1];
    //Emerson Modify 2008-1001 , prevent the display error when the value over 100.
    c_sprintf(s_value, "%d%02dHr", ui4_number_hun,ui4_number_unit);
    c_uc_ps_to_w2s(s_value, w2s_string, (NAV_FAC_MENU_ITEM_CONTENT_LEN + 1));
}


/*---------------------------------------------------------------------------
 * Name: nav_fac_c_rm_set_vid_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
INT32 nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_VID_TYPE_T   e_vid_type,
                                        VOID*                   pv_set_info,
                                        SIZE_T                  z_size,
                                        BOOL                    b_store)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;

    t_op_info.u.t_vid_set_info.e_vid_type  = e_vid_type;
    t_op_info.u.t_vid_set_info.pv_set_info = pv_set_info;
    t_op_info.u.t_vid_set_info.z_size      = z_size;
    t_op_info.u.t_vid_set_info.b_store     = b_store;

	/* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );

    return i4_ret;
}
#if 1   //sam 121016
INT32 nav_fac_c_rm_set_vid_comp_cust_spec(DRV_CUSTOM_CUST_SPEC_TYPE_T   e_cust_spec_type,
                                        VOID*                   pv_set_info,
                                        SIZE_T                  z_size,
                                        BOOL                    b_store)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;

    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type  = e_cust_spec_type;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = pv_set_info;
    t_op_info.u.t_cust_spec_set_info.z_size      = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store     = b_store;

	/* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );

    return i4_ret;
}
#endif
/*---------------------------------------------------------------------------
 * Name: nav_fac_c_rm_get_vid_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
INT32 nav_fac_c_rm_get_vid_comp(DRV_CUSTOM_VID_TYPE_T   e_vid_type,
                                              DRV_CUSTOM_VID_INP_T    e_vid_inp,
                                              VOID*                   pv_get_info,
                                              SIZE_T*                 pz_size)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T						 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET;

    t_op_info.u.t_vid_get_info.e_vid_type  = e_vid_type;
    t_op_info.u.t_vid_get_info.e_vid_inp   = e_vid_inp;
    t_op_info.u.t_vid_get_info.pv_get_info = pv_get_info;
    t_op_info.u.t_vid_get_info.pz_size     = pz_size;

	/* set to driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );

    return i4_ret;
}
#if 1 //sam 121016
INT32 nav_fac_c_rm_get_vid_comp_cust_spec(DRV_CUSTOM_CUST_SPEC_TYPE_T   e_cust_spec_type,
                                              VOID*                   pv_get_info,
                                              SIZE_T*                 pz_size)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T						 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
	
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type  = e_cust_spec_type;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = pv_get_info;
    t_op_info.u.t_cust_spec_get_info.pz_size     = pz_size;

	/* set to driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );

    return i4_ret;
}
#endif
/*---------------------------------------------------------------------------
 * Name: nav_fac_c_rm_get_vid_min_max
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
INT32 nav_fac_c_rm_get_vid_min_max(DRV_CUSTOM_VID_TYPE_T   e_vid_type,
                                             DRV_CUSTOM_VID_INP_T   e_vid_inp,
                                             UINT16*                pui2_min,
                                             UINT16*                pui2_max)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T						 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32 i4_ret;
    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET_MIN_MAX;
    t_op_info.u.t_vid_get_min_max_info.e_vid_type  = e_vid_type;
    t_op_info.u.t_vid_get_min_max_info.e_vid_inp   = e_vid_inp;
    t_op_info.u.t_vid_get_min_max_info.pui2_min    = pui2_min;
    t_op_info.u.t_vid_get_min_max_info.pui2_max    = pui2_max;

    /* set to driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != RMR_OK)
    {
        *pui2_min = 0;
        *pui2_max = 0xFF;
        return i4_ret;
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_setup_min_max
 * Description: Get the acceptable value range for the inputed item.
 * Inputs:
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/

 INT32 nav_fac_get_setup_min_max(
                    UINT16              ui2_idx,
                    INT16*             pui2_min,
                    INT16*             pui2_max)
{
    INT32  i4_ret = NAVR_OK;
    //INT16  i2_min = 0;
    //INT16  i2_max = 0;
    //UINT8  ui_temp = 0;
    //UINT16 ui2_temp1,ui2_temp2;  //ke_vizio_20121114 for clean warning.

    /*INX_fac_main_page*/
    /*Get min and max by api*/
    if( inx_fac_items_get_min(ui2_idx)==0 &&
        inx_fac_items_get_max(ui2_idx)==0)
    {
        printf("%s().%d This idx(%d) no range\n",__func__,__LINE__,ui2_idx);
        *pui2_min = 0;
        *pui2_max = 0;
    }else{
        *pui2_min = inx_fac_items_get_min(ui2_idx);
        *pui2_max = inx_fac_items_get_max(ui2_idx);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_setup_value
 * Description: Get value to EEPROM.
 * Inputs:  ui2_idx     - the item index of setup menu
 * Outputs: pui4_val    - the value of this item
 * Returns: NONE
 ----------------------------------------------------------------------------*/
INT32 nav_fac_get_setup_value(
    UINT16              ui2_idx,
    INT32*              pi4_val)
{

    INT32   i4_ret = NAVR_OK;
    UINT32  ui4_val = 0;
    UTF16_T w2s_string_cr[NAV_FAC_MENU_TEXT0_LEN+ 1] = L"";

    /*INX_fac_main_page*/
    /*content callback function*/
    if( inx_fac_items_check_entry_content(ui2_idx) )
    {
        ui4_val = inx_fac_items_exec_entry_content(w2s_string_cr,ui2_idx);
        *pi4_val = ui4_val;
    }else{
        printf("%s().%d : entry content not found\n",__func__, __LINE__);
        *pi4_val = ui4_val;
        return NAVR_FAIL;
    }

    return i4_ret;

}
/*-----------------------------------------------------------------------------
 * Name: nav_fac_set_setid_value
 * Description: Set value to EEPROM.
 * Inputs:  ui2_idx     - the item index of setid menu
 *          ui4_val     - the new value of this item
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
INT32 nav_inx_fac_set_setup_value(
    UINT16              ui2_idx,
    INT32              i4_val,
    UINT32				pv_param1
    )
{
    INT32   i4_ret = NAVR_OK;
    //UINT32  ui4_fac_val = 0;
    //VID_INFO_T	t_vid_info;

    /*INX_fac_main_page*/
    /*exec callback function*/
    if( inx_fac_items_check_entry_callback(ui2_idx) )
    {
        inx_fac_items_exec_entry_callback(ui2_idx,i4_val,pv_param1);
    }
	return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_set_setid_value
 * Description: Set value to EEPROM.
 * Inputs:  ui2_idx     - the item index of setid menu
 *          ui4_val     - the new value of this item
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
INT32 nav_fac_set_setup_value(
    UINT16              ui2_idx,
    INT32              i4_val)
{
    INT32   i4_ret = NAVR_OK;
    UINT32  ui4_fac_val = 0;
    VID_INFO_T	t_vid_info;


    /* Get current fac settings from EEPROM */
    a_cfg_cust_fac_get(&ui4_fac_val);

    switch (ui2_idx)
    {
#ifdef APP_FAC_TUNER_SELECTION //sam 091229
        case NAV_FAC_MENU_TUNER_TYPE:
            {
                i4_ret = a_cfg_cust_fac_set_tuner_type(i4_val);
                if (i4_ret != APP_CFGR_OK)
                    return TVR_FAIL;
                break;
            }
#endif
#ifdef FAC_MENU_PANEL_TYPE_SELECT
        case NAV_FAC_MENU_PANEL_TYPE:
        {

DBG_LOG_PRINT(("!!!!@djh %s,  NAV_FAC_MENU_PANEL_TYPE:\n", __func__));            
           //Follow factory command setting
            UINT8       ui1_i;		//kyo_20091002
            CUST_SPEC_TYPE_SET_INFO_T t_set_info = {0};
            UINT32 ui4_modelID = (UINT32)i4_val;
            SIZE_T      z_size = sizeof(ui4_modelID);

            t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_MODEL_INDEX;
            t_set_info.pv_set_info = (VOID *)&ui4_modelID;
            t_set_info.z_size = z_size;
            t_set_info.b_store = TRUE;
            i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
            if (i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("!!!!%s : DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET fail\n", __func__));
                return i4_ret;
            }
           
            i4_ret = a_cfg_cust_fac_set_panel_type(i4_val);
            if (i4_ret != APP_CFGR_OK){
                DBG_LOG_PRINT(("!!!!%s : a_cfg_cust_fac_set_panel_type fail\n", __func__));
                return i4_ret;
            }

            // Reset to default Panel Clr Temp.
            for(ui1_i=0; ui1_i < ACFG_CLR_TEMP_NUM; ui1_i++)
            {
                //Default "0x9C" due to Factory Tool not support the minus.
                //Re-write 1st part of fac clr. (YPrPb part)
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_R,   ui1_i,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_G,   ui1_i,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_B,   ui1_i,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i,  0);

                //Re-write 2st part of fac clr. (VGA part)
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_R,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_G,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_B,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i+ACFG_CLR_TEMP_NUM,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i+ACFG_CLR_TEMP_NUM,  0);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i+ACFG_CLR_TEMP_NUM,  0);
            }

            break;
        }
#endif                  
        case NAV_FAC_MENU_CURRENT_SOURCE://Emerson Add for changing the current source 2008-0919
            i4_ret = a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, i4_val);
            if (i4_ret != APP_CFGR_OK) {
                return TVR_FAIL;
            }
            i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN,i4_val,NULL);
            if(NAVR_OK != i4_ret)
            {
                return NAVR_FAIL;
            }
            b_nav_fac_eep_init_done = FALSE;
            b_nav_fac_reset_done = FALSE ;
			b_nav_fac_get_led_info_done = FALSE;            
			b_nav_fac_install_ulpk_done = FALSE ;/*//sam 0331 for ULPK install in fac menu*/		
#ifdef FAC_WB_USE_SCE_PATTERN	//kyo_20110425 add for MT5395			
			if(nav_fac_sce_pat_is_on())
        	{
				nav_fac_sce_pat_enable_pat(FALSE);
        		nav_fac_sce_pat_set_on_off_flag(FALSE);
				c_thread_delay(2000);
				nav_fac_sce_pat_enable_pat(TRUE);
        		nav_fac_sce_pat_set_on_off_flag(TRUE);
			}	
#endif			
            break;
	
        //ke_vizio_20121113 modify
        case NAV_FAC_MENU_COLOR_TEMP:
            #ifdef FAC_PHASE2_UI_SETTING   //ke_vizio_20131127 add
            {
                BOOL b_pic_mode_usage = 0;

                // Get custom 1's usage, custom 1 = "6".
                a_cfg_cust_get_cust_pic_mode_exist_status(6, &b_pic_mode_usage);
                                     
                if(b_pic_mode_usage == FALSE)
                {
                    a_cfg_cust_create_pic_mode();
                    a_cfg_cust_set_cust_pic_mode_name(6,"Factory");
                }
                else
                {
                    //Change to "custom 1"
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),6);
                }
            }
            #endif

  			//ke_vizio_20140909 add
            switch (i4_val)
            {
                case 0:
                {
                    i4_val = ACFG_CUST_CLR_TEMP_COOL;
                }
                break;
                case 1:
                {
                    i4_val = ACFG_CUST_CLR_TEMP_NORMAL;
                }
                break;
                case 2:
                {
                    i4_val = ACFG_CUST_CLR_TEMP_COMPUTER;
                }
                break;
                case 3:
                {
                    i4_val = ACFG_CUST_CLR_TEMP_CUSTOM;
                }
                break;
                default:
                    i4_val = 0;
                    break;
            }
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP+(ui2_idx-NAV_FAC_MENU_COLOR_TEMP)), i4_val);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP+(ui2_idx-NAV_FAC_MENU_COLOR_TEMP)));
            a_cfg_store();
            break;

        case NAV_FAC_MENU_SCALER_R_GAIN:
        case NAV_FAC_MENU_SCALER_G_GAIN:
        case NAV_FAC_MENU_SCALER_B_GAIN:
        case NAV_FAC_MENU_SCALER_R_OFFSET:
        case NAV_FAC_MENU_SCALER_G_OFFSET:
        case NAV_FAC_MENU_SCALER_B_OFFSET:
		    //Soar 08-11-13 modify
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP+(ui2_idx-NAV_FAC_MENU_COLOR_TEMP)), i4_val);
            if (i4_ret != APP_CFGR_OK) {
                return i4_ret;
            }
		    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP+(ui2_idx-NAV_FAC_MENU_COLOR_TEMP)));            
            
            //ke_vizio_20121113 add for backup to fac eeprom
		    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R+(ui2_idx-NAV_FAC_MENU_SCALER_R_GAIN)), i4_val);
            if (i4_ret != APP_CFGR_OK) {
                return i4_ret;
            }
            b_def_clr_temp_update = TRUE;
		    break;
		    
	    case NAV_FAC_MENU_BURN_IN:
            {
                DRV_CUST_OPERATION_INFO_T    t_op_info;

                DBG_LOG_PRINT(("!!!!@djh %s , NAV_FAC_MENU_BURN_IN(%d) :\n", __func__, i4_val));

                UINT16 ui2_Burn_idx = 0;
                SIZE_T z_size       = sizeof(ui2_Burn_idx);
                SIZE_T z_size_drv   = sizeof(DRV_CUST_OPERATION_INFO_T);        
                INT32 i4_Ret        = 0;  
                
                if(i4_val == TRUE)
                {
                    a_cfg_set_factory_mode(APP_CFG_FAC_MODE_BURNING_MASK);
                    nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                                     NAV_UI_MSG_NO_SIGNAL,
                                                     NULL
                                                     );

                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_RC_ON;
                    a_cfg_cust_fac_set(ui4_fac_val);
                    ui2_Burn_idx = 1;

                    //ke_vizio_20130320 disable POWER key watchdog for keypad test.
                    // coz audio no output sound.
                    a_tv_net_send_cmd(":dtv_app_mtk,am,:disable_PKWD\n"); 
                }
                else
                {

                    a_cfg_set_factory_mode(APP_CFG_FAC_MODE_NORMAL);
                    nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                                     NAV_UI_MSG_WITH_SIGNAL,
                                                     NULL
                                                     );
                    ui2_Burn_idx = 0;
                }
                a_cfg_update_factory_mode();
                a_cfg_store();

                c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
                
                t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
                t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
                t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
                t_op_info.u.t_cust_spec_set_info.z_size = z_size;
                t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

                /* get from driver */
                i4_Ret = c_rm_set_comp(
                                      DRVT_CUST_DRV,
                                      DRV_CUST_COMP_ID,
                                      FALSE,
                                      ANY_PORT_NUM,
                                      0,
                                      &t_op_info,
                                      z_size_drv
                                     );
                if (i4_Ret != RMR_OK)
                {
                    DBG_LOG_PRINT (("<Fac_menu> Set BurnIn mode failed !\n"));
                }                                 
            break;
            }
            
		
        case NAV_FAC_MENU_AQ_BYPASS:	
		{
			b_nav_fac_aq_bypass_on_off = i4_val;
			if(b_nav_fac_aq_bypass_on_off)//joe.zy
			{
				acfg_cust_audio_enable_srs_bypass_mode(1);
			}
			else
			{
				acfg_cust_audio_enable_srs_bypass_mode(0);
			}
			break;
		}

	    case NAV_FAC_MENU_ZZZ_TEST:
	    {
	      ui_nav_fac_zzz_test = i4_val;
	
	      i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI),
	                            (INT16) (UINT32) ui_nav_fac_zzz_test);
	      DBG_LOG_PRINT(("%s, ZZZ set brightness=%d (result=%d)\n", __func__, i4_val, i4_ret));
	
	      a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
	      break;
	    }
	
	    case NAV_FAC_MENU_PANEL_NITS:
	    {

		    INT32    i4_ret = 0;
		    INT16    i2_color_temparure = 0;

			ui2_nav_fac_panel_nits = i4_val;	 
		    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_color_temparure);

			ACFG_LOG_ON_FAIL(i4_ret);

		    if(i2_color_temparure == ACFG_CUST_CLR_TEMP_WARM)
		    {
		        // Normal (Warm)
	        	a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, ACFG_CUST_CLR_TEMP_WARM);
	        	a_cfg_cust_drv_update_panel_nits();
		    }
		    else if (i2_color_temparure == ACFG_CUST_CLR_TEMP_COOL)
		    {
		        // Computer (Cool)
	        	a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, ACFG_CUST_CLR_TEMP_COOL);
	        	a_cfg_cust_drv_update_panel_nits();
		    }
		    else if (i2_color_temparure == ACFG_CUST_CLR_TEMP_NORMAL)
		    {
		        // Normal
	        	i4_ret = a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, ACFG_CUST_CLR_TEMP_NORMAL);
	        	a_cfg_cust_drv_update_panel_nits();
		    }
		    else
		    {
		        DBG_LOG_PRINT(("%s, ZZZ set panel_nits(%d), result=%d\n", __func__, ui2_nav_fac_panel_nits, i4_ret));
		    }
						       
			DBG_LOG_PRINT(("%s, ZZZ set panel_nits(%d), result=%d\n", __func__, ui2_nav_fac_panel_nits, i4_ret));
		
		break;
		
		
	    }
	    case NAV_FAC_MENU_ZZZ_TEST3:
	    {
	      break;
	    }


        case NAV_FAC_MENU_ELCS:
            {

                DBG_LOG_PRINT(("!!!!@djh %s , Set ELCS i4_val (%d) , b_nav_fac_get_ELCS (%d) :\n", __func__, i4_val , b_nav_fac_get_ELCS )); 
                a_cfg_custom_set_ELCS_Control_enable(b_nav_fac_get_ELCS);
                
                i4_ret = APP_CFGR_OK;                                
            }
            break;
		case NAV_FAC_MENU_SHORT_PROTECTION:   //yshu add the switch of short protection.
			{
				UINT8 ui2_switch = (i4_val != 1) ? 1 : 0;
				a_cfg_custom_set_short_protection(ui2_switch);                       
			    break;
			}	
#ifdef FAC_EEP_INIT 	   
        case NAV_FAC_MENU_EEPROM_INIT:
            a_amb_enable_system_key(TRUE);
            break;
#endif
	    case NAV_FAC_MENU_BACKLIGHT_MIN:
#if 1 //@jh
            acfg_set(IDX_CUST_VGA_PWM_MIN, &i4_val , 1);
            t_vid_info.e_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
            t_vid_info.ui2Value	= (UINT16)i4_val;
            t_vid_info.b_ignore_hw  = TRUE;

			nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MIN,& t_vid_info, sizeof(VID_INFO_T), FALSE);

			a_cfg_store();
#endif
            break;
        case NAV_FAC_MENU_MODEL_INDEX:
        {
            a_cfg_custom_set_model_index(i4_val);
            break;
        }
		//HDMI Cert
		case NAV_FAC_MENU_EARC_MUTE:
        {
            acfg_cust_audio_set_earc_mute(i4_val);  // 1 mute,0 un-mute
            break;
        }
		case NAV_FAC_MENU_EARC_WORD_LEN:
        {
            acfg_cust_audio_set_earc_word_length(i4_val); // 0:16 bit,1:24bit
            break;
        }
		case NAV_FAC_MENU_EARC_LAYOUT:
        {
            acfg_cust_audio_set_earc_layout(i4_val);  // 0:layout A,1:layout B
            break;
        }
        case NAV_FAC_MENU_TFTPS:
        {
            b_inx_at_tftps_enable = i4_val;
            if(b_inx_at_tftps_enable)
            {
                a_cfg_cust_pthread_tftps_create();
            }else{
                a_cfg_cust_pthread_tftps_cancel();
            }
            break;
        }
        case NAV_FAC_MNEU_DEBUG:
        {
            b_inx_at_debug_enable = i4_val;
            break;
        }
	    case NAV_FAC_MENU_BACKLIGHT_MAX:
            acfg_set(IDX_CUST_VGA_PWM_MAX, &i4_val , 1);
            t_vid_info.e_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
            t_vid_info.ui2Value	= (UINT16)i4_val;
            t_vid_info.b_ignore_hw  = TRUE;

			nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MAX, &t_vid_info, sizeof(VID_INFO_T), FALSE);

			a_cfg_store();
            break;

        case NAV_FAC_MENU_RESET:
			a_cfg_custom_factory_reset();	
            break;
		case NAV_FAC_MENU_GET_LED_INFO:
			nav_fac_get_led_driver_info(1);
			break;
        #ifdef FAC_INSTALL_ULPK
        case NAV_FAC_MENU_INSTALL_ULPK: /*//sam 0331 for ULPK install in fac menu*/
            break;
        #endif

#ifdef FACTORY_VCOM_TEST_PATTERN//Emerson Add 20091123 for Test pattern output
        case NAV_FAC_MENU_TCON:
		   nav_grab_activation(NAV_COMP_ID_FAC_TCON);
           break;
#endif
#ifdef APP_DVBT_SUPPORT
        case NAV_FAC_MENU_OAD_ENABLE:
        {
            UINT32 ui4_fac_acfg;
            ui4_fac_acfg = APP_CFG_CUST_FAC_OAD_ENABLE;
            if (i4_val)
              ui4_fac_val = ui4_fac_val | ui4_fac_acfg;
            else
              ui4_fac_val = ui4_fac_val & ~ui4_fac_acfg;
            i4_ret =  a_cfg_cust_fac_set(ui4_fac_val);
            if (i4_ret != APP_CFGR_OK)
                return TVR_FAIL;
            a_cfg_store();
            break;
        }
#endif /* APP_DVBT_SUPPORT */

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
        case NAV_FAC_MENU_WB_INTRNL_PAT:
            {
                nav_fac_sce_pat_set_level((UINT16)i4_val);
                nav_fac_sce_pat_enable_pat(TRUE);
                nav_fac_sce_pat_set_on_off_flag(TRUE);
            }
            break;
#endif
#ifdef FAC_FILP_MIRROR_SUPPORT
        case NAV_FAC_MENU_FLIP:     //sam 121016
        {
            UINT8 ui1_val = (UINT8)i4_val;
            nav_fac_c_rm_set_vid_comp_cust_spec((DRV_CUSTOM_CUST_SPEC_TYPE_T)DRV_CUSTOM_OPERATION_TYPE_FLIP_ON,(VOID *)&ui1_val, sizeof(ui1_val), TRUE);
            break;
        }
        case NAV_FAC_MENU_MIRROR:   //sam 121016
        {
            UINT8 ui1_val = (UINT8)i4_val;
            nav_fac_c_rm_set_vid_comp_cust_spec((DRV_CUSTOM_CUST_SPEC_TYPE_T)DRV_CUSTOM_OPERATION_TYPE_MIRROR_ON,(VOID *)&ui1_val, sizeof(ui1_val), TRUE);
            break;
        }
        
#endif /* FAC_FILP_MIRROR_SUPPORT */
#ifdef FAC_BT_TESTBLE //Ben 20170809
		case NAV_FAC_MENU_TESTBLE:
		{
			if (i4_val == FALSE)
			{
				a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);
				a_bluetooth_gattc_rssi_meter_hide();
			}
			else
			{
				bt_gatt_cli_set_allow_pair_4_test_tool(TRUE);
				a_bluetooth_gattc_rssi_meter_dialog_enable(TRUE);
			}

			b_nav_fac_bt_testble_on_off = i4_val;
			break;
		}
#endif
#ifdef FAC_AUD_SRS_BYPASS
        case NAV_FAC_MENU_AUD_SRS_BYPASS:
        {
            _set_aud_bypass_mode_idx((UINT16)i4_val);
            break;
        }
#endif /* FAC_AUD_SRS_BYPASS */
#ifdef FAC_HDMI_PORT_NUM_SETTING
        case NAV_FAC_MENU_HDMI_PORT_NUM_SETTING:
        {
            _nav_fac_c_rm_set_hdmi_num((UINT8)i4_val);
            break;
        }
#endif /* FAC_HDMI_PORT_NUM_SETTING */

#ifdef FAC_MENU_CLR_COPY    //ke_vizio_20121127
        case NAV_FAC_MENU_CLR_COPY:
        {
            nav_fac_clr_copy_to_all();
            break;
        }
#endif

#ifdef INX_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
        case NAV_FAC_MENU_WINDOW_PATTERN:
        {
            g_b_WinPatOnOff = (BOOL)i4_val;
            nav_fac_border_window(g_b_WinPatOnOff, 400, 400, 350, 350);
            break;
        }
#endif
        
        default :
            return NAVR_FAIL;
    }

    return i4_ret;

}
/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_led_driver_info
 * Description:  Get register values for As3824 
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 nav_fac_get_led_driver_info( UINT8 devid)
{
   	UINT8 ui2_led[2] = {0};
	DRV_CUST_OPERATION_INFO_T       t_op_info;
	SIZE_T                          z_size;
	SIZE_T                          z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	INT32 i4_ret = APP_CFGR_OK;
	z_size = sizeof(ui2_led);
	ui2_led[0] = 20;
	ui2_led[1] = devid;	
	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	

	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_DUMP_LED_DRIVER_INFO;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)ui2_led;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

	/* set value to driver */
	i4_ret = c_rm_set_comp(
						DRVT_CUST_DRV,
						DRV_CUST_COMP_ID,
				 		FALSE,
				 		ANY_PORT_NUM,
				 		0,
				 		&t_op_info,
				 		z_size_drv);


	
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }					
	return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_nav_fac_register
 * Description: register this component to navigater module
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 a_nav_fac_register(
                    NAV_FAC_VIEW_HDLR_T*       pt_view_hdlr
                    )
{

    DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    NAV_FAC_T*  pt_this = &t_g_nav_fac;
    NAV_COMP_T  t_comp;
    INT32       i4_ret;

    c_memset(&t_comp,0,sizeof(NAV_COMP_T));
    /* NAV_COMP_ID_FAC */
    t_comp.pf_init           = _nav_fac_init;
    t_comp.pf_deinit         = _nav_fac_deinit;
    t_comp.pf_is_key_handler = _nav_fac_is_key_handler;
    t_comp.pf_activate       = _nav_fac_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _nav_fac_hide;
    t_comp.pf_handle_msg     = _nav_fac_handle_msg;

    //i4_ret = nav_register_component(NAV_COMP_ID_FAC, &t_comp, COMP_EXC_SET_FAC);
    i4_ret = nav_register_component(NAV_COMP_ID_FAC_INX, &t_comp, COMP_EXC_SET_FAC_INX);//joe.zy
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL) {
        nav_fac_view_register_default_hdlr(&pt_this->t_view_hdlr);
    } else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }
    
    return NAVR_OK;
}

#ifdef APP_FAC_TUNER_SELECTION //sam 091229
/*-----------------------------------------------------------------------------
 * Name: GetCurrentTunerName
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
CHAR* GetCurrentTunerName(void)
{
    return GetTunerName(GetCurrentTunerIndex());
}

/*-----------------------------------------------------------------------------
 * Name: GetCurrentTunerIndex
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
UINT32 GetCurrentTunerIndex(void)
{
    INT32 ui2_val = 0;
    UINT8   aui1_buff1[64];
    UINT8   aui1_buff2[64];
    UINT8   aui1_buff3[64];
    UINT32  ui4_read;

    a_cfg_eep_raw_read (EEP_OFFSET_TUNER_ID_1, aui1_buff1, 1, & ui4_read);
    a_cfg_eep_raw_read (EEP_OFFSET_TUNER_ID_2, aui1_buff2, 1, & ui4_read);
    a_cfg_eep_raw_read (EEP_OFFSET_TUNER_ID_3, aui1_buff3, 1, & ui4_read);

    if((aui1_buff1[0]==aui1_buff2[0])&&(aui1_buff1[0]==aui1_buff3[0])){	//sam 081110
        ui2_val = aui1_buff1[0];
    }
    else{
        ui2_val = 0xff;
    }

	if(ui2_val == 0x92)
	  { ui2_val = APP_CFG_CUST_FAC_TUNER_TYPE_LG_TDTKH801F; } //sam 110310
	else if (ui2_val == 0x9f)
	  { ui2_val = APP_CFG_CUST_FAC_TUNER_TYPE_TCL_DA89WT6E; }
#if 1	//sam 120606 add tuner index
	else if (ui2_val == 0x79)
	  { ui2_val = APP_CFG_CUST_FAC_TUNER_TYPE_LG_TDVWH810F; }
	else if (ui2_val == 0xa0)
	  { ui2_val = APP_CFG_CUST_FAC_TUNER_TYPE_NXP_TDA18273; }
	else if (ui2_val == 0xa1)
	  { ui2_val = APP_CFG_CUST_FAC_TUNER_TYPE_Mxl_MXL601; }
#endif
	else
	  { ui2_val = APP_CFG_CUST_FAC_TUNER_TYPE_UNKNOW; }		

    return ui2_val;
}

/*-----------------------------------------------------------------------------
 * Name: GetTunerName
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
CHAR* GetTunerName(UINT32 u4Index)
{
    switch (u4Index)
    {
		case APP_CFG_CUST_FAC_TUNER_TYPE_LG_TDTKH801F: //sam 110310
			return "LG_TDTKH801F";//sam 110317 modify LG tuner name
		case APP_CFG_CUST_FAC_TUNER_TYPE_TCL_DA89WT6E: 
			return "TCL_DA89WT6E";
#if 1	//sam 120606 add tuner index
		case APP_CFG_CUST_FAC_TUNER_TYPE_LG_TDVWH810F: 
			return "LG_TDVWH810F";
		case APP_CFG_CUST_FAC_TUNER_TYPE_NXP_TDA18273: 
			return "NXP_TDA18273";
		case APP_CFG_CUST_FAC_TUNER_TYPE_Mxl_MXL601: 
			return "Mxl_MXL601";
#endif
		default: 
			return "UNKNOW";
    }
}
#endif
//ke_vizio_20110420
/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_HDMI_port_NUM
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_get_HDMI_port_NUM(UINT8 *pui1_num)
{
    UINT8 ui1_num = 0;
    INT32 i4_ret = 0;

    #ifdef FAC_HDMI_PORT_NUM_SETTING
    i4_ret = _nav_fac_c_rm_get_hdmi_num(&ui1_num);
    #endif

    //sam 120529 reserve for multi-IO request
    //***************************************************//
    // //sam 120529 reserve for multi-IO request
    //at_post_reg_custom0 -->HDMIx4 ,combine Comp-2 & RGB
    //at_post_reg_custom1 -->HDMIx3 ,combine Comp-2 & RGB
    //at_post_reg_custom2 -->HDMIx4 ,cancel Comp-2 & RGB
    //at_post_reg_custom3 -->HDMIx3 ,cancel Comp-2 & RGB
    //***************************************************//

    *pui1_num = ui1_num;	//choose which source table
    
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_set_HDMI_port_NUM
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_set_HDMI_port_NUM(UINT8 ui1_num)
{


    #ifdef FAC_HDMI_PORT_NUM_SETTING
    return _nav_fac_c_rm_set_hdmi_num(ui1_port);
    #else
    return 0;
    #endif
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_flip_mirror_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_get_flip_mirror_enable(BOOL* pb_filp_enable, BOOL* pb_mirror_enable)
{
    UINT8 ui1_temp = 0;
    INT32 i4_ret = 0;
    DRV_CUSTOM_VID_INP_T e_fac_vid_inp;
    SIZE_T      z_size = sizeof(ui1_temp);
    
    e_fac_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
    i4_ret = nav_fac_c_rm_get_vid_comp((DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_OPERATION_TYPE_FLIP_ON),
                                  e_fac_vid_inp,(VOID *)&ui1_temp, &z_size);
    if(i4_ret != 0)
    {
        return i4_ret;
    }
    *pb_filp_enable = (BOOL)ui1_temp;

    e_fac_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
    i4_ret = nav_fac_c_rm_get_vid_comp((DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_OPERATION_TYPE_MIRROR_ON),
                                  e_fac_vid_inp, (VOID *)&ui1_temp, &z_size);
    if(i4_ret != 0)
    {
        return i4_ret;
    }
    *pb_mirror_enable = (BOOL)ui1_temp;

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_set_flip_mirror_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_set_flip_mirror_enable(BOOL b_filp_enable, BOOL b_mirror_enable)
{
    UINT8 ui1_val = 0;
    INT32 i4_ret = 0;

    ui1_val = (UINT8)b_filp_enable;
    i4_ret = nav_fac_c_rm_set_vid_comp_cust_spec(DRV_CUSTOM_OPERATION_TYPE_FLIP_ON,(VOID *)&ui1_val, sizeof(ui1_val), TRUE);
    if(i4_ret != 0)
    {
        return i4_ret;
    }

    ui1_val = (UINT8)b_mirror_enable;
    i4_ret = nav_fac_c_rm_set_vid_comp_cust_spec(DRV_CUSTOM_OPERATION_TYPE_MIRROR_ON,(VOID *)&ui1_val, sizeof(ui1_val), TRUE);
    if(i4_ret != 0)
    {
        return i4_ret;
    }

    return 0;
}
//////////////////////////Only for Vizio ////////////////////////// 
/*-----------------------------------------------------------------------------
 * Name: nav_get_cur_model_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_get_cur_model_info(VIZIO_MOEDL_INFO_T *pvt_info)
{
    DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    //ke_vizio_20121022 update
    //#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM


    return 0;


}

#ifdef FAC_MENU_CLR_COPY   //ke_vizio_20121127 add
/*-----------------------------------------------------------------------------
 * Name: nav_get_cur_model_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_clr_copy_to_all(VOID)
{

    INT32    i4_ret = APP_CFGR_OK;
    UINT8    ui1_i = 0, ui1_idx = 0;
    INT16  ui2_R_gain[4]={0}, ui2_G_gain[4]={0}, ui2_B_gain[4]={0};
    INT16  ui2_R_offset[4]={0}, ui2_G_offset[4]={0}, ui2_B_offset[4]={0};

    //extract YPbPr RGB gain & offset
    for(ui1_i = 0; ui1_i <= 3; ui1_i++, ui1_idx++)
    {
        acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_R, ui1_i, &ui2_R_gain[ui1_idx]);
        acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_G, ui1_i, &ui2_G_gain[ui1_idx]);
        acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_B, ui1_i, &ui2_B_gain[ui1_idx]);
        acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i, &ui2_R_offset[ui1_idx]);
        acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i, &ui2_G_offset[ui1_idx]);
        acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i, &ui2_B_offset[ui1_idx]);
    }

    ui1_idx = 0;
    for(ui1_i=0; ui1_i < ACFG_CLR_GAIN_ELEM_NUM; ui1_i++, ui1_idx++)
    {
        if(ui1_idx == 4){
            ui1_idx = 0;
        }
        
        if((ui1_i >= 8 && ui1_i <= 11) || (ui1_i >= 28 && ui1_i <= 31))
        {
            continue;
        }
        
        //For user
        acfg_set_int16_by_idx(IDX_CLR_GAIN_R,   ui1_i,  ui2_R_gain[ui1_idx]);
        acfg_set_int16_by_idx(IDX_CLR_GAIN_G,   ui1_i,  ui2_G_gain[ui1_idx]);
        acfg_set_int16_by_idx(IDX_CLR_GAIN_B,   ui1_i,  ui2_B_gain[ui1_idx]);
        acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, ui1_i,  ui2_R_offset[ui1_idx]);
        acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, ui1_i,  ui2_G_offset[ui1_idx]);
        acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, ui1_i,  ui2_B_offset[ui1_idx]);
    }


    return i4_ret;
}
#endif /* FAC_MENU_CLR_COPY */

#ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20141107 modify
BOOL b_auto_EEPROM_dump_all = FALSE;
/*-----------------------------------------------------------------------------
* Name:
*      _nav_fac_tpv_eep_update
* Description:
*
* Input arguments:
*      pv_tag
*      e_nfy_id
*      pv_nfy_param
* Output arguments:
*      None
* Returns:
*      None
*---------------------------------------------------------------------------*/
INT32 nav_fac_USBtoEEP_auto_dump(HANDLE_T h_file)
{

    UINT32 i4_ret = FMR_OK;
    CHAR    ui_byte[FAC_EEPROM_SIZE] = {0};
    UINT64 ui8_pos;
    
    /*	  Read current MAC, Request by XM factory    */
    UINT32    ui4_rw_byte = 0;
    UINT8 aui1_faccmd_ret_val_RJ45[CMD_LEN_Maximum] = {0};
    UINT8 aui1_faccmd_ret_val_EEP_SN[CMD_LEN_Maximum] = {0};
    UINT8 aui1_faccmd_ret_val_HDCP[320] = {0};
    UINT8 ui1_image_bank_bit = 0;  //ke_vizio_20130520 add
    
	/* 	0x5AA  ~ 0x5B9 is EEPROM SN 	*/
	/* 	0x1C89 ~ 0x1C8F is BT-MAC 	*/
	/* 	0x1C90 ~ 0x1C9D is RJ45-MAC 	*/
	/* 	0x1C9E ~ 0x1DDD is HDCP 		*/

	a_cfg_eep_raw_read(EEP_SERIAL_NUMBER, aui1_faccmd_ret_val_EEP_SN, 16, &ui4_rw_byte); 
    a_cfg_eep_raw_read(EEP_WIRED_ETHERNET_MAC_ADDR, aui1_faccmd_ret_val_RJ45, 14, &ui4_rw_byte); //total reserve 14 byte for MAC //sam 130621
	a_cfg_eep_raw_read(EEP_HDCP_ADDR, aui1_faccmd_ret_val_HDCP, 320, &ui4_rw_byte);
    //Get the image bank bit
    a_cfg_cust_get_image_bank_bit(&ui1_image_bank_bit);  //ke_vizio_20130520
    
    i4_ret = c_fm_lseek(h_file, 0, FM_SEEK_BGN, &ui8_pos);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_fm_read(h_file, ui_byte, FAC_EEPROM_SIZE, &ui4_rw_byte);
    INX_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(0, ui_byte, (FAC_EEPROM_SIZE), &ui4_rw_byte);
    INX_LOG_ON_FAIL(i4_ret);

    a_cfg_eep_raw_write(EEP_SERIAL_NUMBER, aui1_faccmd_ret_val_EEP_SN, 16, &ui4_rw_byte);
	a_cfg_eep_raw_write(EEP_WIRED_ETHERNET_MAC_ADDR, aui1_faccmd_ret_val_RJ45, 14, &ui4_rw_byte);//total reserve 14 byte for MAC //sam 130621
	a_cfg_eep_raw_write(EEP_HDCP_ADDR, aui1_faccmd_ret_val_HDCP, 320, &ui4_rw_byte);

    a_cfg_eep_cache_reload(); //ke_vizio_20131105 add

    //Set the image bank bit
	a_cfg_cust_set_image_bank_bit(ui1_image_bank_bit);  //ke_vizio_20130520

    return 0;
}
/*-----------------------------------------------------------------------------
* Name:
*      nav_fac_USBtoEEP_auto_dump_For_RD
* Description:
*
* Input arguments:
*      pv_tag
*      e_nfy_id
*      pv_nfy_param
* Output arguments:
*      None
* Returns:
*      None
*---------------------------------------------------------------------------*/
INT32 nav_fac_USBtoEEP_auto_dump_For_RD(HANDLE_T h_file)
{
    UINT32 i4_ret = FMR_OK;
    CHAR    ui_byte[FAC_EEPROM_SIZE] = {0};
    UINT64 ui8_pos;
    UINT32    ui4_rw_byte = 0;

	/* 	0x5AA  ~ 0x5B9 is EEPROM SN 	*/
	/* 	0x1C89 ~ 0x1C8F is BT-MAC 	*/
	/* 	0x1C90 ~ 0x1C9D is RJ45-MAC 	*/
	/* 	0x1C9E ~ 0x1DDD is HDCP 		*/
    
    i4_ret = c_fm_lseek(h_file, 0, FM_SEEK_BGN, &ui8_pos);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_fm_read(h_file, ui_byte, FAC_EEPROM_SIZE, &ui4_rw_byte);
    INX_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(0, ui_byte, (FAC_EEPROM_SIZE), &ui4_rw_byte);
    INX_LOG_ON_FAIL(i4_ret);

    a_cfg_eep_cache_reload();


    return 0;
}
#if 1 //Larry 2014 1201
/*-----------------------------------------------------------------------------
* Name:
*      nav_fac_USBtoEEP_auto_dump_For_RD
* Description:
*
* Input arguments:
*      pv_tag
*      e_nfy_id
*      pv_nfy_param
* Output arguments:
*      None
* Returns:
*      None
*---------------------------------------------------------------------------*/
INT32 nav_fac_USBtoEEP_auto_dump_For_Default_HDCP(VOID)
{
    UINT32    ui4_rw_byte = 0;
	UINT8 _au1HDCP[] = 
	{
		0x00 ,0x14 ,0x7c ,0xe6 ,0x2c ,0x37 ,0xf3 ,0xe8 ,0xa8 ,0x4d ,0x27 ,0x66 ,0xa8 ,0xd0 ,0x2f ,0x13,
		0x55 ,0x79 ,0x97 ,0xe7 ,0x87 ,0x37 ,0x18 ,0x04 ,0xd1 ,0x5f ,0x3b ,0x12 ,0x9f ,0x32 ,0xa4 ,0x6f,
		0x58 ,0x1c ,0x8a ,0xbc ,0x8c ,0x7f ,0xe3 ,0xcb ,0x81 ,0x9e ,0xb4 ,0x45 ,0x7c ,0x66 ,0x6a ,0xcc,
		0xdd ,0x5c ,0xc8 ,0x17 ,0xa3 ,0x90 ,0x43 ,0x91 ,0x8b ,0x01 ,0xf0 ,0x1d ,0xff ,0x8a ,0x1b ,0xde,
		0x94 ,0xd6 ,0xb6 ,0xf6 ,0x6d ,0x15 ,0x7b ,0x42 ,0x13 ,0xa2 ,0x1b ,0x04 ,0xb5 ,0xdd ,0x11 ,0xcc,
		0x42 ,0x28 ,0x66 ,0x65 ,0xf5 ,0x77 ,0xf1 ,0x65 ,0xc3 ,0x8c ,0x9b ,0x2c ,0xad ,0xb4 ,0xe9 ,0x7c,
		0xd1 ,0xbc ,0xd6 ,0x4a ,0x5d ,0xf7 ,0x45 ,0x3e ,0x2a ,0x22 ,0xec ,0xa8 ,0xdf ,0x68 ,0x54 ,0x57,
		0x5a ,0x10 ,0xc8 ,0x38 ,0x9f ,0x94 ,0xa0 ,0xa7 ,0xa0 ,0x71 ,0xa2 ,0x67 ,0x8e ,0x23 ,0xbd ,0x8d,
		0x63 ,0x89 ,0x0d ,0x01 ,0x91 ,0x97 ,0x4c ,0xba ,0x5c ,0x4d ,0x94 ,0x73 ,0x36 ,0x68 ,0x12 ,0x6c,
		0xe8 ,0xfa ,0xb1 ,0x51 ,0xc1 ,0x93 ,0xc6 ,0xce ,0x72 ,0x90 ,0xc1 ,0x6b ,0x4d ,0xf6 ,0x63 ,0x02,
		0xd3 ,0xa6 ,0x9b ,0x80 ,0x35 ,0xb6 ,0xa9 ,0xff ,0x8e ,0xfd ,0xd9 ,0x6f ,0x24 ,0xa6 ,0xdb ,0x4c,
		0xd2 ,0x0c ,0x0f ,0xcf ,0xcd ,0x1a ,0x19 ,0xe4 ,0x62 ,0x9c ,0x6d ,0x17 ,0x6b ,0x57 ,0x39 ,0xcb,
		0x6a ,0x0d ,0x80 ,0x75 ,0xfa ,0xf3 ,0x69 ,0x7d ,0x9f ,0x79 ,0xe3 ,0xc0 ,0x8b ,0x5a ,0xd2 ,0xa8,
		0xc9 ,0xd9 ,0x90 ,0x93 ,0xaa ,0xe6 ,0x1a ,0x1e ,0x17 ,0x93 ,0x03 ,0x2d ,0x43 ,0xc0 ,0xaf ,0x33,
		0x94 ,0x66 ,0xa9 ,0x18 ,0x55 ,0xcc ,0x22 ,0xf5 ,0x23 ,0xc8 ,0xc5 ,0x37 ,0xf1 ,0x81 ,0xd2 ,0x96,
		0xaf ,0x0a ,0x5a ,0xe5 ,0x8a ,0x13 ,0xef ,0x63 ,0x19 ,0x4c ,0xc6 ,0x3f ,0x6c ,0x9a ,0x7a ,0xb2,
		0xa6 ,0xd4 ,0x31 ,0x5a ,0x30 ,0x01 ,0x21 ,0xcd ,0xa2 ,0x86 ,0x74 ,0x04 ,0x46 ,0x3e ,0x38 ,0x08,
		0xe7 ,0x57 ,0xa7 ,0xb4 ,0x41 ,0x73 ,0x02 ,0x78 ,0x93 ,0x34 ,0x93 ,0xce ,0x93 ,0x5a ,0x46 ,0xd3,
		0x0a ,0x14 ,0xf7 ,0x61 ,0x03 ,0xb7 ,0x8f ,0x22 ,0xd2 ,0xf1 ,0x3a ,0x98 ,0xba ,0x28 ,0x62 ,0x53,
		0xca ,0x4c ,0x1d ,0x19 ,0xce ,0x49 ,0x87 ,0xf7 ,0xb5 ,0x26 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
	};
	a_cfg_eep_raw_write(EEP_HDCP_ADDR, _au1HDCP, sizeof(_au1HDCP), &ui4_rw_byte);


    return 0;
}
#endif
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_fac_tpv_eep_update
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_tpv_eep_update(
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3)
{
    INT32     i4_ret = FMR_OK;
    CHAR      s_filename[512] = {0};
    SIZE_T    t_mount_point_size   = 511;
    UINT32    ui4_usb_idx = 0 ;
    CHAR      s_mount_point[512]   = {0};
    RMV_DEV_OPEN_ID_T   e_open_id = 0;
    CHAR  pstring[60] = {0};
    HANDLE_T h_fm_dev_bin2eep, h_fm_dev_bin2eep_RD;
    UINT64     ui8_pos;
    UINT8     ui1_file_ver_main = 0, ui1_file_ver_sub = 0;
    UINT8     ui1_eep_ver_main = 0, ui1_eep_ver_sub = 0;
    UINT32    ui4_rw_byte = 0;
    UINT8     ui1_mode;
    UINT32 ui4_mnt_count = 0, ui4_mnt_point_idx = 0;  //ke_vizio_20130626 add
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;   //ke_vizio_20130626 add
    BOOL b_eep_file_check = FALSE;
    CHAR 	s_app_name[APP_NAME_MAX_LEN];  //ke_vizio_20141203 add

	i4_ret = a_am_get_active_app(s_app_name);
	if (AMR_OK == i4_ret && 0 == c_strcmp (s_app_name, MMP_NAME))
    {
        return;
    }

    
    //ke_vizio_20130626 add
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    INX_LOG_ON_FAIL(i4_ret);
    
    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
        {
            continue;
        }
        break;
        
    }
    i4_ret = a_rmv_dev_set_active_mnt_pnt(ui4_mnt_point_idx);
    INX_LOG_ON_FAIL(i4_ret);
    
    /* Get current active mount point */
	i4_ret = a_rmv_dev_get_active_mnt_pnt(
								&ui4_usb_idx, 
								&t_mount_point_size, 
								s_mount_point);
	if(i4_ret == RMVR_NO_DEVICE)
	{
		DBG_LOG_PRINT(("!!!NO USB DEVICE\n"));
		return;
	}

    /* Open mount point */
	a_rmv_dev_open_mnt_point (ui4_usb_idx, &e_open_id);

    /* Read bin to eeprom */
    c_sprintf(s_filename,"%s/eeprom.bin",s_mount_point);

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                   s_filename,
                   FM_READ_ONLY,
                   0777,
                   FALSE,
                   &h_fm_dev_bin2eep);
    if(i4_ret != FMR_OK)
    {
        //DBG_LOG_PRINT("Can't open dev file: %s\n", s_filename);
        //return;
    }
    else
    {
        DBG_LOG_PRINT(("find eep file: %s\n", s_filename));
        b_eep_file_check = TRUE;
        b_auto_EEPROM_dump_all = FALSE;
    }

    c_sprintf(s_filename,"%s/eeprom_RD_use.bin",s_mount_point);

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                   s_filename,
                   FM_READ_ONLY,
                   0777,
                   FALSE,
                   &h_fm_dev_bin2eep_RD);
    if(i4_ret != FMR_OK)
    {
        //DBG_LOG_PRINT("Can't open dev file: %s\n", s_filename);
        //return;
    }
    else
    {
        DBG_LOG_PRINT(("find eep file: %s\n", s_filename));
        b_eep_file_check = TRUE;
        b_auto_EEPROM_dump_all = TRUE;
    }

    if(b_eep_file_check == FALSE){
        return;
    }
    
    // Get file & EEP version.
    if(b_auto_EEPROM_dump_all == FALSE)
    {
        c_fm_lseek(h_fm_dev_bin2eep, (INT64)EEP_EEPROM_VER_MAIN, FM_SEEK_BGN, &ui8_pos);
        c_fm_read(h_fm_dev_bin2eep, (VOID *)&ui1_file_ver_main, 1, &ui4_rw_byte);
        c_fm_read(h_fm_dev_bin2eep, (VOID *)&ui1_file_ver_sub, 1, &ui4_rw_byte);
    }
    else
    {
        c_fm_lseek(h_fm_dev_bin2eep_RD, (INT64)EEP_EEPROM_VER_MAIN, FM_SEEK_BGN, &ui8_pos);
        c_fm_read(h_fm_dev_bin2eep_RD, (VOID *)&ui1_file_ver_main, 1, &ui4_rw_byte);
        c_fm_read(h_fm_dev_bin2eep_RD, (VOID *)&ui1_file_ver_sub, 1, &ui4_rw_byte);
    }
    DBG_LOG_PRINT(("File ver_main: %d\n", ui1_file_ver_main));
    DBG_LOG_PRINT(("File ver_sub: %d\n", ui1_file_ver_sub));

    a_cfg_eep_raw_read(EEP_EEPROM_VER_MAIN, (VOID *)&ui1_eep_ver_main, 1, &ui4_rw_byte); 
    a_cfg_eep_raw_read(EEP_EEPROM_VER_SUB, (VOID *)&ui1_eep_ver_sub, 1, &ui4_rw_byte); 
	DBG_LOG_PRINT(("EEP ver_main: %d\n", ui1_eep_ver_main));
    DBG_LOG_PRINT(("EEP ver_sub: %d\n", ui1_eep_ver_sub));

    //ke_vizio_20141202 modify
    if(b_auto_EEPROM_dump_all == FALSE)
    {
        if((ui1_file_ver_main > ui1_eep_ver_main) ||
           ((ui1_file_ver_main >= ui1_eep_ver_main) && (ui1_file_ver_sub > ui1_eep_ver_sub)))
        {
            DBG_LOG_PRINT(("EEPROM Upgrade\n"));
        }
        else{
            return;
        }
    }
    else
    {
        UINT32 ui4_model_index = 0;
        
        a_cfg_custom_get_model_index(&ui4_model_index);

        if((ui1_file_ver_main == 0xff && ui1_file_ver_sub == 0xff) &&
           (ui1_eep_ver_main == 0xff && ui1_eep_ver_sub == 0xff) &&
           (ui4_model_index == 0 || ui4_model_index == 0xff))
        {
            DBG_LOG_PRINT(("Force EEPROM Upgrade\n"));
        }
        else{
            if((ui1_file_ver_main > ui1_eep_ver_main) ||
               ((ui1_file_ver_main >= ui1_eep_ver_main) && (ui1_file_ver_sub > ui1_eep_ver_sub)))
            {
                DBG_LOG_PRINT(("EEPROM Upgrade\n"));
            }
            else{
                return;
            }
        }
    }

    //Disable USB auto detect dialog & VIA key
    a_nav_enable_usb_pop_up_dialog(FALSE);
    a_tv_net_disable_keyroute(TRUE);

    a_cfg_get_factory_mode(&ui1_mode);
    if(ui1_mode == APP_CFG_FAC_MODE_BURNING);
    {
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                         NAV_UI_MSG_WITH_SIGNAL,
                                         NULL
                                         );
    }

    //Display Update OSD
    nav_fac_view_eep_update_osd_create();

    // Start upgrading.
    c_memset(pstring, 0, sizeof(pstring));
    c_sprintf(pstring, "EEPROM Update V%d.%d to V%d.%d\n", ui1_eep_ver_main, ui1_eep_ver_sub, ui1_file_ver_main, ui1_file_ver_sub);
    nav_fac_view_eep_update_osd(pstring);

    if(b_auto_EEPROM_dump_all == FALSE)
    {
        i4_ret = nav_fac_USBtoEEP_auto_dump(h_fm_dev_bin2eep);
        INX_LOG_ON_FAIL(i4_ret);

        i4_ret = c_fm_close(h_fm_dev_bin2eep);
        INX_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = nav_fac_USBtoEEP_auto_dump_For_RD(h_fm_dev_bin2eep_RD);
		i4_ret = nav_fac_USBtoEEP_auto_dump_For_Default_HDCP(); //Larry 2014 1201
		a_cfg_fac_reset(); //Larry 2014 1203 
		menu_clear_memory_ex(FALSE);    // Ben 20180129
        INX_LOG_ON_FAIL(i4_ret);

        i4_ret = c_fm_close(h_fm_dev_bin2eep_RD);
        INX_LOG_ON_FAIL(i4_ret);
    }

    a_rmv_dev_close_mnt_point (e_open_id);

    c_memset(pstring, 0, sizeof(pstring));
    c_sprintf(pstring, "Update Success!!\n TV will reboot.");
    //c_sprintf(pstring, "Update Success!!\n TV will shutdown.");
    nav_fac_view_eep_update_osd(pstring);

    c_thread_delay(3000);
    a_amb_reboot();

    //a_amb_power_on(FALSE);
    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_fac_usb_pld_rmv_dev_nfy
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_usb_pld_rmv_dev_nfy(
                    VOID*               pv_tag,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param)
{
    if (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
        nav_request_context_switch(
                        _nav_fac_tpv_eep_update,
                        (VOID*)e_nfy_id,
                        NULL,
                        NULL);
    }

    return;
}
#endif

#ifdef INX_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
INT32 nav_fac_border_window(BOOL b_onOff, UINT32 u4L_width, UINT32 u4R_width, UINT32 u4U_height, UINT32 u4D_height)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SET_BORDER_WINDOW_T t_border_window = {0};
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_border_window.u4VdpId = 0;
    t_border_window.u4OnOff = b_onOff;
    t_border_window.u4RGB = 0x000000;
    t_border_window.u4L_width = u4L_width;
    t_border_window.u4R_width = u4R_width;
    t_border_window.u4U_height = u4U_height;
    t_border_window.u4D_height = u4D_height;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_DISP_TYPE_SET_BORDER_WINDOW;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(&t_border_window);
    t_op_info.u.t_vid_set_info.z_size = sizeof(SET_BORDER_WINDOW_T);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size);

    /* SCE pattern */
    nav_fac_sce_pat_set_level(1023);
    nav_fac_sce_pat_enable_pat(b_onOff);
    nav_fac_sce_pat_set_on_off_flag(b_onOff);

    return i4_ret;
}

#define _atoi(p1)       nav_atoi(p1)

static INT32 _nav_cli_set_border_window(INT32 i4_argc, const CHAR** pps_argv)
{
    BOOL b_onOff;
    UINT32 u4L_width = 100;
    UINT32 u4R_width = 100;
    UINT32 u4U_height = 100;
    UINT32 u4D_height = 100;

    if (i4_argc != 6) {
        DBG_LOG_PRINT(("usage: win (on:1/off:0) L R T D\n"));
        return CLIR_OK;
    }

    if(_atoi(pps_argv[1]) > 1)
    {
        DBG_LOG_PRINT(("the 1st parameter only (on:1/off:0)\n"));
        return CLIR_OK;
    }

    b_onOff = _atoi(pps_argv[1]);
    u4L_width = _atoi(pps_argv[2]);
    u4R_width = _atoi(pps_argv[3]);
    u4U_height = _atoi(pps_argv[4]);
    u4D_height = _atoi(pps_argv[5]);

    nav_fac_border_window(b_onOff, u4L_width, u4R_width, u4U_height, u4D_height);

    g_b_WinPatOnOff = b_onOff;
    
    return CLIR_OK;
}

static CLI_EXEC_T at_factory_cmd_tbl[] =
{
    {
        "bd_win",
        "win",
        _nav_cli_set_border_window,
        NULL,
        "usage: win [on:1/off:0] L R T D",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    END_OF_CLI_CMD_TBL
};

#endif
/*-----------------------------------------------------------------------------
 * Name:
 *      inx_nav_fac_usb_pld_rmv_dev_nfy
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID inx_nav_fac_usb_pld_rmv_dev_nfy(
									VOID*				pv_tag,
									RMV_DEV_NFY_ID_T	e_nfy_id,
									VOID*				pv_nfy_param)
{
	    if( b_inx_at_debug_enable == 0 )
        	return;
		b_inx_at_debug_enable = 0; // only excute once
		CHAR s_path[256] = {0};
		CHAR s_buf[256] = {0};
		CHAR str[KEY_LEN] = {0};
        CHAR get_format_time[16] = {0};
        UINT8 num;
		FILE *fd;
		char *key_file = "InxKey";
		DBG_LOG_PRINT(("\ninx_nav_fac_usb_pld_rmv_dev_nfy\n"));
		if(RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
			{
				if( a_cfg_custom_get_mnt_path(s_path) != 0 )
				{
					DBG_LOG_PRINT(("can't find usb device\n"));
					return;
				}
				c_sprintf(s_buf,"%s/%s",s_path,key_file);
				fd = fopen(s_buf,"r");
				if(fd)
				{
					fgets(str,KEY_LEN,fd);
					DBG_LOG_PRINT(("[INX_AT]str = %s\n",str));
					fclose(fd);
				}
				else
				{
					DBG_LOG_PRINT(("[INX_AT]no Inxkey\n"));
					return;
				}
				if(strncmp(str,"dump_ch_info",(strlen(str)-1)) == 0)
				{
					a_cfg_pre_ch_dump_channel_info_2_usb();	

				}
				else if(strncmp(str,"dump_ch_table",(strlen(str)-1)) == 0)
				{
					a_INX_capture_ch_info_ex();	
				}
#if 0
                else if(strstr(str,"get_dd_mmc"))// ex : get_dd_mmc 37
                {
                    c_memset(s_buf,0,sizeof(s_buf));
                    a_cfg_cust_get_format_time(get_format_time);
                    c_sscanf(str,"get_dd_mmc %d",&num);
                    c_sprintf(s_buf,"dd if=/dev/mmcblk0p%d of=%s/mmcblk0p%d_%s.bin ; sync",num,s_path,num,get_format_time);
                    system(s_buf);
                    INX_nav_fac_urc_dialog_show(MLM_FAC_KEY_MSG_FINISH);
                }
                else if(strstr(str,"set_dd_mmc"))// ex : set_dd_mmc 37
                {
                    c_memset(s_buf,0,sizeof(s_buf));
                    c_sscanf(str,"set_dd_mmc %d",&num);

                    sprintf(s_buf,"%s/mmcblk0p%d.bin",s_path,num);
                    if( access(s_buf,F_OK) == -1 ){ //File not exist
                        DBG_LOG_PRINT(("[INX_AT]File not exist\n"));
                        return;
                    }
                    sprintf(s_buf,"dd if=%s/mmcblk0p%d.bin of=/dev/mmcblk0p%d ; sync",s_path,num,num);
                    system(s_buf);
                    a_cfg_cust_get_format_time(get_format_time);
                    sprintf(s_buf,"echo %s >> %s/mmcblk0p%d.bin.log",get_format_time,s_path,num);
                    system(s_buf);

                    INX_nav_fac_urc_dialog_show(MLM_FAC_KEY_MSG_FINISH);
                }
#endif
				else
					return;
			}
				
	
		return;
}


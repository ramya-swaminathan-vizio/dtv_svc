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

#include "am/a_am.h"
#include "amb/a_amb.h"
#include "menu2/a_menu.h"

#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"

//#include "nav_fac.h"
#include "TPV_fac.h"
//#include "res/nav/factory/fac_mlm.h"
#include "TPV_factory/TPV_fac_mlm.h"
//#include "res/nav/factory/a_factory.h"
#include "TPV_factory/a_TPV_factory.h"
#include "TPV_factory/TPV_d_factory.h"
#include "TPV_factory/TPV_fac_ch_table/TPV_fac_load_ch.h"
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

#ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "c_os.h"
#include "nav/usb_pld/nav_usb_pld_view.h" 
#endif

#include "bgm/a_bgm.h" //ke_vizio_20141105 add

#include "mmp/a_mmp.h"  //ke_vizio_20141203 add

#ifdef TPV_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
#include "c_cli.h"  //ke_vizio_20150522 add
#endif

#ifdef FAC_BT_TESTBLE //Ben 20170809
#include "bluetooth_gatt/bluetooth_gattc_rssimeter_view.h"
#endif

#include "menu2/menu_common/menu_common.h"  // Ben 10280130
#include "res/app_util/config/acfg_custom.h"
#include "nav/burning_mode/burning_mode_patgen.h"

SIZE_T   t_size = sizeof(UINT16); //Soar 20080918

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);   //ke_vizio_20121114 add

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

#ifdef FAC_BT_TESTBLE	//Ben 20170809
BOOL b_nav_fac_bt_testble_on_off = FALSE;
#endif

BOOL b_nav_fac_install_ulpk_done = FALSE;/*//sam 0331 for ULPK install in fac menu*/	
#if 0	//kyo_20111221
BOOL b_nav_auto_color_busy = FALSE;	
BOOL b_nav_fac_erase_ulpk_done = FALSE;/*//sam 110504 for ULPK erase in fac menu*/
UINT16 ui2_nav_fac_auto_color_done = NAV_FAC_AUTO_COLOR_NONE;
#endif
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

#ifdef FAC_WB_DATA  // Ben 20180413
BOOL b_nav_fac_wb_data = FALSE;
#endif

#ifdef FAC_BACKLIGHT_CHECK // Ben 20180413
BOOL b_nav_fac_backlight_check_on_off = FALSE;
#endif

#ifdef FAC_PANEL_NITS // Ben 20180629
UINT16 ui2_nav_fac_panel_nits = 0;
BOOL b_nav_fac_panel_nits_inited = FALSE;
#endif


BOOL b_nav_fac_pq_bypass_on_off = FALSE;    // Ben 20180411

#define TPV_DEFAULT_FQ_CH 1  // 1 :FQ ; 0 : SZ

static const PANEL_ID_T _ar_Fac_Panel_ID_Map[] =
{
//@jh todo	{ 0, PANEL_AUO_42_HW1_V0},	   //E551VA

};

#if 0//defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add

CHAR s_model_name_string[16] = " ";

static NAV_FAC_MODEL_NAME_T _ar_Fac_Model_Name_default_Table[] =
{
    { PANEL_AUO_42_HW1_V0,        "XXXX",     50},  // 0
};


#endif


static BOOL b_def_clr_temp_update = FALSE;   //ke_vizio_20121115 add

#ifdef TPV_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
static CLI_EXEC_T at_TPV_fac_cmd_tbl[];
BOOL g_b_WinPatOnOff = FALSE;
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_bklight_timer_stop(NAV_FAC_T* pt_this);
static VOID _nav_fac_ipt_pw_timer_stop(NAV_FAC_T* pt_this);    //Soar add for key timeout 20111013

#ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
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

#if 0
    i4_ret = c_scc_aud_set_srs_bypass(h_g_acfg_scc_main_aud,(BOOL)ui2_idx);
#else
    i4_ret = acfg_cust_audio_enable_srs_bypass_mode(ui2_idx);
#endif

#if 0
  #ifndef APP_C4TV_SUPPORT
	if (ui2_idx == 0)
		a_cfg_custom_Set_MS12_PCMR_OnOff(FALSE); // Ben 20161006
  #endif
#endif
    if(i4_ret != SMR_OK)
    {
        DBG_LOG_PRINT(("!!!!%s : aud_bypass_mode_idx fail\n", __FUNCTION__));
    }
    return i4_ret;
}
#endif /* FAC_AUD_SRS_BYPASS */

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
   pt_fac->ui2_key_num = 0;  
   pt_fac->ui2_key_num2 = 0;	//kyo_20111028
   //u1_factory_key_num = 0;	 
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
	//UINT32      ui4_fac_rc_val;

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

    #ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
    /* register remove device notification function */
    i4_ret = a_rmv_dev_reg_monitor(
                    _nav_fac_usb_pld_rmv_dev_nfy,
                    NULL,
                    &pt_this->ui4_rmv_dev_nfy);
    if(i4_ret != RMVR_OK){
        DBG_LOG_PRINT((" %s a_rmv_dev_reg_monitor fail Line: %d\n", __FUNCTION__, __LINE__));
    }
    #endif


    #ifdef TPV_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
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

    #ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
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
 
    nav_set_component_visible(NAV_COMP_ID_FAC);
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
   
    if (b_nav_fac_pq_bypass_on_off == TRUE)  // Ben 20180417
    {
        a_cfg_cust_drv_set_pq_bypass(TRUE);
    }
    
#ifdef FAC_BACKLIGHT_CHECK // Ben 20180413
    if (b_nav_fac_backlight_check_on_off == TRUE)
        ; //to-do
#endif

#ifdef FAC_WB_DATA  // Ben 20180411
    //a_cfg_custom_Get_Factory_GAMMA_OnOff(&b_nav_fac_wb_data);
    //DBG_LOG_PRINT(("\n %s BenBenBen b_nav_fac_wb_data=%d  Line: %d\n", __FUNCTION__, b_nav_fac_wb_data, __LINE__));
#endif    

#ifdef FAC_PANEL_NITS // Ben 20180629
    //a_cfg_custom_get_HDR_panel_nits(&ui2_nav_fac_panel_nits);  
    //DBG_LOG_PRINT(("\n %s ui2_nav_fac_panel_nits=%d  Line: %d\n", __FUNCTION__, ui2_nav_fac_panel_nits, __LINE__));
#endif

    #ifdef TPV_2K19_BURNING_MODE
    UINT8 ui_temp_val = 0;
    a_cfg_get_factory_mode(&ui_temp_val);
    if((ui_temp_val & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
    {
        #ifdef TPV_BURNING_MODE_4K
        burning_mode_ptgn_pattern_stop();
        #endif

        #ifdef TPV_BURNING_MODE_VCOM
        burning_mode_ptgn_vcom_pattern_stop();
        #endif
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
#if 0
    /* Stop loader timer*/
    nav_fac_stop_loader_timer(pt_this);

    /* Stop fac timer*/
    _nav_fac_stop_timer(pt_this);
#endif
    nav_return_activation(NAV_COMP_ID_FAC);
#if 0
    /* If the FAC mode is active and OSD Display is set as Off,
                                            hide root widget. */
    if (a_cfg_cust_is_fac_on(TRUE)) {
        nav_enable_ui_root_widget(TRUE);
    } else {
        nav_enable_ui_root_widget(FALSE);
    }
#endif
#if 0
    /* Check whether auto_flush shall be activate */
    if (a_cfg_cust_is_bds_po_default(TRUE) && a_cfg_cust_is_bds_pod_av(TRUE))
    {
        a_cfg_cust_bds_auto_flush(FALSE, FALSE);
    } else {
        a_cfg_cust_bds_auto_flush(TRUE, FALSE);
    }
#endif

    //Emerson Add 2008-0918
    b_nav_fac_eep_init_done = FALSE;
    b_nav_fac_reset_done	 = FALSE;
	
	b_nav_fac_install_ulpk_done = FALSE;/*//sam 0331 for ULPK install in fac menu*/	
#if 0	//kyo_20111221	
	ui2_nav_fac_auto_color_done = NAV_FAC_AUTO_COLOR_NONE;
	b_nav_auto_color_busy = FALSE;
    b_nav_fac_erase_ulpk_done = FALSE;/*//sam 110504 for ULPK erase in fac menu*/
#endif

    //ke_vizio_20121115 add for reset user clr temp.
    a_cfg_cust_factory_clr_temp_def_update(&b_def_clr_temp_update);
	
#ifdef FAC_PANEL_NITS // Ben 20180629
    b_nav_fac_panel_nits_inited = FALSE;
#endif

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
            #ifdef APP_TPV_DFT_DC_ON_RESET
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

    /* Shift the stack */
    for (ui2_idx = 0;
         ui2_idx < (NAV_FAC_KEY_STACK_NUM-1) ;
         ui2_idx++)
    {
        pt_fac->at_key_stack[ui2_idx] = pt_fac->at_key_stack[ui2_idx+1];
    }
    /* Put in the key code to the top of stack */
    pt_fac->at_key_stack[NAV_FAC_KEY_STACK_NUM-1] = ui4_key_code;
    pt_fac->at_key_stack[NAV_FAC_KEY_STACK_NUM] = 0;


    /* Shift the stack2 */
    for (ui2_idx = 0;
         ui2_idx < (NAV_FAC_KEY_STACK2_NUM-1) ;
         ui2_idx++)
    {
        pt_fac->at_key_stack2[ui2_idx] = pt_fac->at_key_stack2[ui2_idx+1];
    }
    /* Put in the key code to the top of stack2 */
    pt_fac->at_key_stack2[NAV_FAC_KEY_STACK2_NUM-1] = ui4_key_code;
    pt_fac->at_key_stack2[NAV_FAC_KEY_STACK2_NUM] = 0;

	#if 1	//sam 120207 add MENU+1+9+1+9 to dump EEPROM data
    /* Shift the stack3 */
    for (ui2_idx = 0;
         ui2_idx < (NAV_FAC_KEY_STACK3_NUM-1) ;
         ui2_idx++)
    {
        pt_fac->at_key_stack3[ui2_idx] = pt_fac->at_key_stack3[ui2_idx+1];
    }
    /* Put in the key code to the top of stack3 */
    pt_fac->at_key_stack3[NAV_FAC_KEY_STACK3_NUM-1] = ui4_key_code;
    pt_fac->at_key_stack3[NAV_FAC_KEY_STACK3_NUM] = 0;
	#endif
}

// Mill 20090312 Erase Partition 5 START
// write 128KB 0xFF to partition 5.
#include "c_fm.h"
#include "u_fm.h"
#define Partition_5_Length (128 * 1024)
#define Data_Length (32 * 1024)

#if 0
static INT32 Erase_Partition5(void)
{
        HANDLE_T h_file = NULL_HANDLE;
        UINT32 ui4_write = 0, ui4_i = 0;
        INT32 i4_ret;
        UINT8 *pui1_data = NULL;

        //Printf("\n\tI'm erasing partition 5....\n");
        i4_ret = c_fm_open(FM_ROOT_HANDLE, "/dev/nor_2", FM_READ_WRITE, 0777, FALSE, &h_file);

        if(i4_ret != FMR_OK)
        {
               // Printf("\n\tErase Error!\n");
                return i4_ret;
        }

        pui1_data = (UINT8*) c_mem_alloc(Data_Length);

        if (pui1_data == NULL) {
                //Printf("c_mem_alloc fail.\n");
                i4_ret = c_fm_close(h_file);
                return i4_ret;
        }
        c_memset(pui1_data, 0xFF, 32 * 1024);

        for (ui4_i = 0; ui4_i < Partition_5_Length / Data_Length; ui4_i++) {

		  ui4_write = 0;

		  i4_ret = c_fm_write(h_file, pui1_data, Partition_5_Length , &ui4_write);

                if (i4_ret != FMR_OK && i4_ret != FMR_EOF) {
                        //Printf("c_fm_write ret: %d\n", i4_ret);
                        return i4_ret;
                }
        }

        c_mem_free(pui1_data);
        c_fm_close(h_file);
        //Printf("\n\tErasing done!\n");
        return FMR_OK;
}
// Mill 20090312 Erase Partition 5 END
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
    ACFG_TYPE_SET_RGB_T t_info;

    if(b_enable)
    {
        t_info.bEnable = b_enable; //(ui2_pattern == 0?FALSE:TRUE);
        t_info.u2R = ui2_nav_fac_wb_intrnal_pat_val;
        t_info.u2G = ui2_nav_fac_wb_intrnal_pat_val;
        t_info.u2B = ui2_nav_fac_wb_intrnal_pat_val;

        //Printf("\033[01;31m [TPV_FAC] \033[m t_info.bEnable = %d\n", t_info.bEnable);
        //Printf("\033[01;31m [TPV_FAC] \033[m R:%d, G:%d, B:%d\n", t_info.u2R, t_info.u2G, t_info.u2B);

        i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
        TPV_LOG_ON_FAIL(i4_ret);
        
        /* Disable the power saving timer of VGA/YPbPr/... */
        a_nav_power_set_component_enable(FALSE);

        /* Hide "No Signal" text on screen */
        if(nav_is_signal_loss(TV_WIN_ID_MAIN))
        {
            nav_enable_scrn_svr(FALSE);
        }

        /* Update color temp coz the color temp will not be updated before activating internal pattern */
    #if 0 // 2k20 this will cause pattern color wrong
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
        if(i4_ret<0) {
            DBG_LOG_PRINT(("a_cfg_av_update() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        }
    #endif
    }
    else
    {
        #if 1  //temp solution
        //before off the pattern, it need to set 0 at first.
        t_info.bEnable = TRUE; //(ui2_pattern == 0?FALSE:TRUE);
        t_info.u2R = 0;
        t_info.u2G = 0;
        t_info.u2B = 0;

        i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
        TPV_LOG_ON_FAIL(i4_ret);
        #endif
        
        t_info.bEnable = b_enable; //(ui2_pattern == 0?FALSE:TRUE);
        t_info.u2R = 0;
        t_info.u2G = 0;
        t_info.u2B = 0;

        //Printf("\033[01;31m [TPV_FAC] \033[m t_info.bEnable = %d\n", t_info.bEnable);
        //Printf("\033[01;31m [TPV_FAC] \033[m R:%d, G:%d, B:%d\n", t_info.u2R, t_info.u2G, t_info.u2B);

        i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
        TPV_LOG_ON_FAIL(i4_ret);
    
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
 * Name: _nav_fac_check_key_stack
 * Description: This function judge all key sequence and give an result.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL _nav_fac_check_key_stack(VOID)
{
    #if 0  //ke_vizio_20110131
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UTF16_T             w2s_pwd_slave[NAV_FAC_KEY_STACK_NUM+1];
    UTF16_T             w2s_pwd_third[NAV_FAC_KEY_STACK_NUM+1];

    /* Master password is always available in case of forgetting the password. The master password is 1150.*/
    c_memset(w2s_pwd_slave, 0, sizeof(w2s_pwd_slave));
    c_memset(w2s_pwd_third, 0, sizeof(w2s_pwd_third));

    //Soar Add 20081013 for default channel
    c_uc_ps_to_w2s(TPV_FAC_DEFAULT_CH, w2s_pwd_slave, NAV_FAC_KEY_STACK_NUM);
    c_uc_ps_to_w2s(TPV_FAC_DEFAULT_CH_POL, w2s_pwd_third, NAV_FAC_KEY_STACK_NUM);


    if(c_uc_w2s_strcmp(pt_fac->at_key_stack, w2s_pwd_slave) == 0)
    {
// Mill 20090312 Erase Partition 5 START
        Erase_Partition5();
// Mill 20090312 Erase Partition 5 END

    	#ifdef TPV_DEFAULT_FQ_CH
    	b_nav_default_fq_ch_loading = TRUE;
    	#else
        b_nav_default_sz_ch_loading = TRUE;
    	#endif

    }
    else if(c_uc_w2s_strcmp(pt_fac->at_key_stack, w2s_pwd_third) == 0)
    {
// Mill 20090312 Erase Partition 5 START
	    Erase_Partition5();
// Mill 20090312 Erase Partition 5 END
    	b_nav_default_pol_ch_loading = TRUE;
    }
    
	if (c_uc_w2s_strcmp(pt_fac->at_key_stack, w2s_pwd_slave)  == 0
       ||c_uc_w2s_strcmp(pt_fac->at_key_stack, w2s_pwd_third)  == 0
	  )
    {
        return TRUE;
    }
    
    return FALSE;

    #else
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UINT8 ui1_idx = 0;

    /* Master password is always available in case of forgetting the password. The master password is 1150.*/
    UINT32 ui4_key_pwd1[NAV_FAC_KEY_STACK_NUM] = TPV_FAC_DEFAULT_CH;
    UINT32 ui4_key_pwd2[NAV_FAC_KEY_STACK_NUM] = TPV_FAC_DEFAULT_CH_POL;
   
    for(ui1_idx = 0; ui1_idx < (NAV_FAC_KEY_STACK_NUM); ui1_idx++)
    {
        if(pt_fac->at_key_stack[ui1_idx] != ui4_key_pwd1[ui1_idx])
        {
            #ifdef TPV_DEFAULT_FQ_CH
        	b_nav_default_fq_ch_loading = FALSE;
        	#else
            b_nav_default_sz_ch_loading = FALSE;
        	#endif
        	
            break;
        }
        #ifdef TPV_DEFAULT_FQ_CH
    	b_nav_default_fq_ch_loading = TRUE;
    	#else
        b_nav_default_sz_ch_loading = TRUE;
    	#endif
    }
    

    for(ui1_idx = 0; ui1_idx < (NAV_FAC_KEY_STACK_NUM); ui1_idx++)
    {
        if(pt_fac->at_key_stack[ui1_idx] != ui4_key_pwd2[ui1_idx])
        {
            b_nav_default_pol_ch_loading = FALSE;
        	
            break;
        }
        b_nav_default_pol_ch_loading = TRUE;
    }

    #ifdef TPV_DEFAULT_FQ_CH
    if(b_nav_default_fq_ch_loading == TRUE ||  b_nav_default_pol_ch_loading == TRUE)
    #else
    if(b_nav_default_sz_ch_loading == TRUE ||  b_nav_default_pol_ch_loading == TRUE)
    #endif
    {
        return TRUE;
    }
    
    return FALSE;
    #endif
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_check_key_stack
 * Description: This function judge all key sequence and give an result.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL _nav_fac_check_key_stack2(VOID)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UINT8 ui1_idx = 0;
    
    /* Master password is always available in case of forgetting the password. The master password is 1150.*/
    UINT32 ui4_key_pwd[NAV_FAC_KEY_STACK2_NUM] = TPV_FAC_PASSWORD_DEF;

    for(ui1_idx = 0; ui1_idx < (NAV_FAC_KEY_STACK2_NUM); ui1_idx++)
    {
    
        if(pt_fac->at_key_stack2[ui1_idx] != ui4_key_pwd[ui1_idx])
        {
            return FALSE;
        }
    }
    return TRUE;
}

#if 1	//sam 120207 add MENU+1+9+1+9 to dump EEPROM data
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_check_key_stack
 * Description: This function judge all key sequence and give an result.
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL _nav_fac_check_key_stack3(VOID)
{
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    UINT8 ui1_idx = 0;

    UINT32 ui4_key_pwd[NAV_FAC_KEY_STACK3_NUM] = TPV_FAC_PASSWORD_DEF_EEPROM;

    for(ui1_idx = 0; ui1_idx < (NAV_FAC_KEY_STACK3_NUM); ui1_idx++)
    {
    
        if(pt_fac->at_key_stack3[ui1_idx] != ui4_key_pwd[ui1_idx])
        {
            return FALSE;
        }
    }
    return TRUE;
}

#endif
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

    #if 0  //ke_vizio_20110131
    /* Process only if Menu is active. */
    if ((c_strcmp (s_active_app, MENU_NAME) == 0))
    {
        /* Record the total number of password which user already inputed */
        pt_fac->ui2_key_num++;

        /* Put all numerals inputed during the channel OSD shows to a stack */
        _nav_fac_put_key_stack(ui4_rc_code);

        /* When the total input numerals is equal to NAV_FAC_KEY_STACK_NUM,
              check whether those numerals put in the stack are correct. */
        if (pt_fac->ui2_key_num == NAV_FAC_KEY_STACK_NUM)
        {
            if (_nav_fac_check_key_stack())
            {
                //Emerson Add 20080911
                /* Show root widget no matter whether the FAC mode is active
                                           and OSD Display is set as Off. */
                nav_enable_ui_root_widget(TRUE);
                a_amb_pause_app(MENU_NAME);
                pt_fac->ui2_key_num = 0;
                if(b_nav_default_sz_ch_loading == TRUE)
                {
                    acfg_TPV_load_default_channel("SZ");
                    b_nav_default_sz_ch_loading = FALSE;
                }
                else if(b_nav_default_fq_ch_loading == TRUE)
                {
                    acfg_TPV_load_default_channel("FQ");
                    b_nav_default_fq_ch_loading = FALSE;
                }
                else if(b_nav_default_pol_ch_loading == TRUE)
                {
                    acfg_TPV_load_default_channel("POL");
                    b_nav_default_pol_ch_loading = FALSE;
                }
            }
            else
            {
                /* If wrong password is inputed, return to normal status */
                pt_fac->ui2_key_num = 0;
            }         
        }

        //For check pwd of FAC menu 
        pt_fac->ui2_key_num2++;
        if(pt_fac->ui2_key_num2 == NAV_FAC_KEY_STACK2_NUM)
        {
            if(_nav_fac_check_key_stack2())
            {
                /* If correct password is inputed, show the FAC menu */
                a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*) BTN_PESUDO_FAC_MENU, NULL);
            }
            pt_fac->ui2_key_num2 = 0;
        }
    }
    #else
    /* Record the total number of password which user already inputed */
    pt_fac->ui2_key_num++;

    /* Put all numerals inputed during the channel OSD shows to a stack */
    _nav_fac_put_key_stack(ui4_rc_code);
    /* When the total input numerals is equal to NAV_FAC_KEY_STACK_NUM,
          check whether those numerals put in the stack are correct. */
    if (pt_fac->ui2_key_num == NAV_FAC_KEY_STACK_NUM)
    {
        if (_nav_fac_check_key_stack())
        {
            if ((c_strcmp (s_active_app, MENU_NAME) == 0))
            {
                //Emerson Add 20080911
                /* Show root widget no matter whether the FAC mode is active
                                           and OSD Display is set as Off. */
                nav_enable_ui_root_widget(TRUE);
                a_amb_pause_app(MENU_NAME);
                pt_fac->ui2_key_num = 0;
                if(b_nav_default_sz_ch_loading == TRUE)
                {
                    acfg_TPV_load_default_channel("SZ");
                    b_nav_default_sz_ch_loading = FALSE;
                }
                else if(b_nav_default_fq_ch_loading == TRUE)
                {
                    acfg_TPV_load_default_channel("FQ");
                    b_nav_default_fq_ch_loading = FALSE;
                }
                else if(b_nav_default_pol_ch_loading == TRUE)
                {
                    acfg_TPV_load_default_channel("POL");
                    b_nav_default_pol_ch_loading = FALSE;
                }
            }
        }

        /* If wrong password is inputed, return to normal status */
        pt_fac->ui2_key_num = 0;
   
    }

    //For check pwd of FAC menu 
    pt_fac->ui2_key_num2++;
    if(pt_fac->ui2_key_num2 == NAV_FAC_KEY_STACK2_NUM)
    {
        if(_nav_fac_check_key_stack2())
        {
            if ((c_strcmp (s_active_app, MENU_NAME) == 0))
            {
                /* If correct password is inputed, show the FAC menu */
                a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*) BTN_PESUDO_FAC_MENU, NULL);
            }
        }
        pt_fac->ui2_key_num2 = 0;
    }
#if 0	//sam 120207 add MENU+1+9+1+9 to dump EEPROM data
	//For check pwd of EEPROM dump 
	pt_fac->ui2_key_num3++;
	if(pt_fac->ui2_key_num3 == NAV_FAC_KEY_STACK3_NUM)
	{
		if(_nav_fac_check_key_stack3())
		{
			if ((c_strcmp (s_active_app, MENU_NAME) == 0))
			{
				/* If correct password is inputed, do "dump EEPROM" */
				//"eeprom.bin" is USB data to TV
				//"eep2bin" is TV data to USB
				_fac_dump_eeprom_hot_key();
			}
		}
		pt_fac->ui2_key_num3 = 0;
	}
#endif

    #endif

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
#if 0	//kyo_20111221		
        case FAC_MSG_AUTO_COLOR_DONE://Emerson Add for auto-color 2008-0918
            b_nav_auto_color_busy = FALSE;
            /* enable the system keys except the POWER key */
            a_amb_enable_system_key(TRUE);
            nav_send_sim_rc_key_event(BTN_PSUDO_AUTO_DONE);
            break;
            
        case FAC_MSG_AUTO_COLOR_FAIL://Emerson Add for auto-color 2008-0918
            /* enable the system keys except the POWER key */
            a_amb_enable_system_key(TRUE);
            b_nav_auto_color_busy = FALSE;
	        ui2_nav_fac_auto_color_done = NAV_FAC_AUTO_COLOR_FAIL;
            nav_send_sim_rc_key_event(BTN_PSUDO_AUTO_FAIL);
	        break;
#endif	        
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
    //CHAR     s_active_app[APP_NAME_MAX_LEN];	//Emerson Add 20080911
    NAV_CUSTOM_FAC_T*   pt_fac = & t_g_fac;
    NAV_FAC_T*  pt_this = &t_g_nav_fac;

    /* Get key code (ignore event group). */
    ui4_rc_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);

    /* Only deal with button down */
    if (e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        #if 0  //ke_vizio_20110131
        /* Check Key (No matter the event is from Panel or RC)*/
        /* Only these keys will be put in the key stack. */
        //Emerson Add 20080911
        a_am_get_active_app (s_active_app);
        /* Process only if Menu is active. */
        if (c_strcmp (s_active_app, MENU_NAME) == 0)
        {
            switch (ui4_rc_code)
            {
                case BTN_DIGIT_1:
                case BTN_DIGIT_7:
                case BTN_DIGIT_8:
                case BTN_DIGIT_9:
                case BTN_PREV_PRG:
                /* Async invoke dispatch key input */
                nav_fac_async_dispatch_msg(FAC_MSG_KEY_INPUT,
                                             (VOID *) ui4_evt_code,
                                             (VOID *) ui4_data);
                break;
                default:
                    pt_fac->ui2_key_num = 0;	//Emerson Add 2008-0926 for anti-idiot mechanism
                    pt_fac->ui2_key_num2 = 0;
                break;
            }
        }
        #else
        /* Process only if Menu is active. */
        switch (ui4_rc_code)
        {
			//Frankie_20160506
            case BTN_DIGIT_0:
			case BTN_DIGIT_2:
			case BTN_DIGIT_4:
            case BTN_DIGIT_1:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_DIGIT_9:
            case BTN_PREV_PRG:
            case BTN_CUSTOM_3:  /* Added by Henry. */
            case BTN_MENU:		//sam 110706 avoid VIA+OK+1+9+9+9+LAST could enter factory menu ,"F111VIM0-1259"
            /* Async invoke dispatch key input */
            if(BTN_CUSTOM_3 == ui4_rc_code)
            {
                 ui4_evt_code = BTN_MENU;
				 _nav_fac_ipt_pw_timer_start(pt_this);  //kyo_20111028 
            }

            //ke_vizio_20161208 add
            if(ui4_rc_code == BTN_MENU)
            {
                _nav_fac_ipt_pw_timer_start(pt_this);

                //Reset Key Stack
                pt_fac->ui2_key_num = 0;
                pt_fac->ui2_key_num2 = 0;
            }

            nav_fac_async_dispatch_msg(FAC_MSG_KEY_INPUT,
                                         (VOID *) ui4_evt_code,
                                         (VOID *) ui4_data);
            break;
            default:
                pt_fac->ui2_key_num = 0;	//Emerson Add 2008-0926 for anti-idiot mechanism
                pt_fac->ui2_key_num2 = 0;	//kyo_20111028
            break;
        }
        #endif
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
    //c_memset(w2s_string, 0, sizeof(w2s_string));
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
    //c_memset(w2s_string, 0, sizeof(w2s_string));
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
    INT16  i2_min = 0;
    INT16  i2_max = 0;
    UINT8  ui_temp = 0;
    //UINT16 ui2_temp1,ui2_temp2;  //ke_vizio_20121114 for clean warning.
#if 0	//kyo_20111221	
    ISL_REC_T       t_isl_rec;
    DRV_CUSTOM_VID_INP_T e_fac_vid_inp;
#endif
    switch (ui2_idx)
    {
#if 0	//kyo_20111221    
        case NAV_FAC_MENU_AUTO_COLOR:
#endif			
        case NAV_FAC_MENU_BURN_IN:
    #ifdef FAC_EEP_INIT          
        case NAV_FAC_MENU_EEPROM_INIT:
    #endif            
        case NAV_FAC_MENU_RESET:

#if 0	//kyo_20111221				
#ifdef FAC_ULPK_ERASE			
        case NAV_FAC_MENU_ERASE_ULPK: /*//sam 110504 for ULPK erase in fac menu*/
#endif			
#endif			
#ifdef FACTORY_VCOM_TEST_PATTERN//Emerson Add 20091123 for Test pattern output
        case NAV_FAC_MENU_TCON:
#endif
#ifdef APP_DVBT_SUPPORT
        case NAV_FAC_MENU_OAD_ENABLE:
#endif
#ifdef FAC_AUD_SRS_BYPASS
        case NAV_FAC_MENU_AUD_SRS_BYPASS:
#endif /* FAC_AUD_SRS_BYPASS */
        //case NAV_FAC_MENU_VGA_SWITCH:
#ifdef  TPV_FAC_WINDOW_PATTERN //ke_vizio_20150522 add
        case NAV_FAC_MENU_WINDOW_PATTERN:
#endif
#ifdef FAC_BT_TESTBLE // Ben 20170809
		case NAV_FAC_MENU_TESTBLE:
#endif
#ifdef FAC_WB_DATA  // Ben 20180411
        case NAV_FAC_MENU_FAC_WB_DATA:
#endif
#ifdef FAC_BACKLIGHT_CHECK // Ben 20180413
        case NAV_FAC_MENU_BACKLIGHT_CHECK:
#endif        
        case NAV_FAC_MENU_PQ_BYPASS:
        

            i2_min = 0;
            i2_max = 1;
            break;

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
        case NAV_FAC_MENU_WB_INTRNL_PAT:
            i2_min = 0;
            i2_max = 1023;
            break;
#endif

#ifdef FAC_MENU_PANEL_TYPE_SELECT
#if 1   //@jh to do
        case NAV_FAC_MENU_PANEL_TYPE:
        {
			//ke_vizio_20121025 modify
//@jh            INT32   i4_ret = 0;
            CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
            INT32 i4_max = 0;
            SIZE_T      z_size = sizeof(i4_max);
            
            t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_TOTAL_MODEL_INDEX;
            t_get_info.pv_get_info = (VOID *)&i4_max;
            t_get_info.pz_size = &z_size;
            i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
            
            i2_min = 1;
            //i2_max = sizeof(_ar_Fac_Panel_ID_Map)/sizeof(PANEL_ID_T) -1;
            i2_max= (INT16)i4_max;
			// end of ke_vizio_20121025 modify
            break;
        }
#endif
#endif
        case NAV_FAC_MENU_BACKLIGHT_MIN:
        case NAV_FAC_MENU_BACKLIGHT_MAX:
            i2_min = 0;
            i2_max = 255;
            break;
        case NAV_FAC_MENU_CURRENT_SOURCE://Emerson Add for Current source setting 2008-0919
            i2_min = 0;
            i4_ret = a_isl_get_num_rec(&ui_temp);
            i2_max = ui_temp - 1;
            if (i4_ret != ISLR_OK) {
                return TVR_FAIL;
            }
	     break;
#if 0	//kyo_20111221		 
        case NAV_FAC_MENU_ADC_R_GAIN:
        case NAV_FAC_MENU_ADC_G_GAIN:
        case NAV_FAC_MENU_ADC_B_GAIN:
        case NAV_FAC_MENU_ADC_R_OFFSET:
        case NAV_FAC_MENU_ADC_G_OFFSET:
        case NAV_FAC_MENU_ADC_B_OFFSET:
            i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (i4_ret != ISLR_OK) {
               return NAVR_FAIL;
            }
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
            {
                switch(t_isl_rec.t_avc_info.e_video_type)
                {
                   case DEV_AVC_Y_PB_PR:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_YPBPR;
                   break;
                   case DEV_AVC_VGA:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_VGA;
                   break;
                   case DEV_AVC_SCART:
                   case DEV_AVC_COMP_VIDEO:
                   case DEV_AVC_S_VIDEO:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_AV;
                   break;
                   case DEV_AVC_HDMI:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_HDMI;
                   break;
                   case DEV_AVC_DVI:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_DVI;
                   break;
                   default:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_AV;
                   break;
                }
            }
            else
            {
                e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_DTV;
            }
			nav_fac_c_rm_get_vid_min_max(
                            (DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_VID_TYPE_ADC_R_GAIN + (ui2_idx - NAV_FAC_MENU_ADC_R_GAIN)),
                            e_fac_vid_inp,
                            &ui2_temp1, &ui2_temp2);
            
            i2_min = ui2_temp1;
            i2_max = ui2_temp2;
            break;
#endif			
        case NAV_FAC_MENU_COLOR_TEMP:
        {
            i4_ret = a_cfg_av_get_min_max(
                             CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),
                             &i2_min, &i2_max);
            if(i4_ret != RMR_OK){
                return NAVR_FAIL;
            }
            break;
        }

        #if 0
        case NAV_FAC_MENU_SCALER_R_GAIN:
        case NAV_FAC_MENU_SCALER_G_GAIN:
        case NAV_FAC_MENU_SCALER_B_GAIN:
        case NAV_FAC_MENU_SCALER_R_OFFSET:
        case NAV_FAC_MENU_SCALER_G_OFFSET:
        case NAV_FAC_MENU_SCALER_B_OFFSET:
            i4_ret = a_cfg_av_get_min_max(
                             CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP + (ui2_idx-NAV_FAC_MENU_COLOR_TEMP)),
                             &i2_min, &i2_max);
            if(i4_ret != RMR_OK){
                return NAVR_FAIL;
            }
            break;
        #endif
        
#if 0//defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add
        case NAV_FAC_MENU_MODEL_NAME:
            {
                UINT16 ui2_tmp;
                i2_min = 0;
                nav_fac_model_name_get_max_cnt_by_panel_id( a_cfg_custom_get_cur_panelID(), &ui2_tmp);
                i2_max = (INT16)ui2_tmp;
            }
            break;
#endif
#ifdef FAC_HDMI_PORT_NUM_SETTING
        case NAV_FAC_MENU_HDMI_PORT_NUM_SETTING:
			#if 0
	            i2_min = 3;
	            i2_max = 4;
			#else	//sam 120529 reserve for multi-IO request
				i2_min = 0;
				i2_max = 3;
			#endif
         break;
#endif  /* FAC_HDMI_PORT_NUM_SETTING */

#ifdef FAC_PANEL_NITS // Ben 20180629
        case NAV_FAC_MENU_PANEL_NITS:
            i2_min = 100;
			i2_max = 5000;
            break;
#endif

        #ifdef TPV_HDMI_CERT
        case NAV_FAC_MENU_EARC_MUTE:
        {
            i2_min = 0;
            i2_max = 1;
            break;
        }

        case NAV_FAC_MENU_EARC_WORD_LENGTH:
        {
            i2_min = SCC_AUD_EARC_PCM_16_BIT;
            i2_max = SCC_AUD_EACR_PCM_24_BIT;
            break;
        }
        case NAV_FAC_MENU_EARC_LAYOUT:
        {
            i2_min = SCC_AUD_EARC_LAYOUT_A;
            i2_max = SCC_AUD_EARC_LAYOUT_B;
            break;
        }
        #endif /* TPV_HDMI_CERT */

        default :
            return NAVR_FAIL;
    }

    *pui2_min = i2_min;
    *pui2_max = i2_max;
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
    INT16   i2_val = 0;
    //UINT16 ui2_temp_val = 0; //ke_vizio_20121114 for clean warning.
    UINT8   ui_temp_val = 0;
    ISL_REC_T       t_isl_rec;

    switch (ui2_idx)
    {   
        #if 1   //@jh to do
        case NAV_FAC_MENU_BACK_LIT_TIME:
            i4_ret = a_cfg_cust_fac_get_backlight_lifetime(&*pi4_val);
            if (i4_ret != APP_CFGR_OK)
                return TVR_FAIL;
            return i4_ret;
        #endif

#ifdef FAC_MENU_PANEL_TYPE_SELECT
        case NAV_FAC_MENU_PANEL_TYPE:
            #if 1
            i4_ret = a_cfg_custom_get_model_index((UINT32 *)&i2_val);
            #else
            i4_ret = a_cfg_cust_fac_get_panel_type(&i2_val);
            #endif
            if (i4_ret != APP_CFGR_OK)
                return TVR_FAIL;
            break;
#endif        
        case NAV_FAC_MENU_BACKLIGHT_MIN:
        case NAV_FAC_MENU_BACKLIGHT_MAX:
            acfg_get(IDX_CUST_VGA_PWM_MAX+(ui2_idx-NAV_FAC_MENU_BACKLIGHT_MAX), &i2_val , &t_size);
	     break;
#ifdef FAC_EEP_INIT      
        case NAV_FAC_MENU_EEPROM_INIT:
            i2_val = b_nav_fac_eep_init_done;
            break;
#endif            
            
        case NAV_FAC_MENU_RESET:
            i2_val = b_nav_fac_reset_done;
            break;

#if 0	//kyo_20111221			
#ifdef FAC_ULPK_ERASE 
		case NAV_FAC_MENU_ERASE_ULPK:/*//sam 110504 for ULPK erase in fac menu*/
			i2_val = b_nav_fac_erase_ulpk_done;
			break;
#endif			
#endif			
#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
        case NAV_FAC_MENU_WB_INTRNL_PAT:
            i2_val = (INT16)nav_fac_sce_pat_get_level();
            break;
#endif
        case NAV_FAC_MENU_CURRENT_SOURCE://Emerson Add for changing the current source 2008-0919
           i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
           if (i4_ret != ISLR_OK) {
               return NAVR_FAIL;
           }
           i2_val = t_isl_rec.ui1_id ;
           break;
           
        case NAV_FAC_MENU_BURN_IN://Soar Add for Burn-In mode 2008-0918
	      a_cfg_get_factory_mode(&ui_temp_val);
	      if((ui_temp_val & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
	         i2_val = TRUE;
	      else
	         i2_val = FALSE;
            break;
#if 0	//kyo_20111221			
        case NAV_FAC_MENU_ADC_R_GAIN:
        case NAV_FAC_MENU_ADC_G_GAIN:
        case NAV_FAC_MENU_ADC_B_GAIN:
        case NAV_FAC_MENU_ADC_R_OFFSET:
        case NAV_FAC_MENU_ADC_G_OFFSET:
        case NAV_FAC_MENU_ADC_B_OFFSET:
            i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (i4_ret != ISLR_OK) {
               return NAVR_FAIL;
            }
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
            {
                switch(t_isl_rec.t_avc_info.e_video_type)
                {
                   case DEV_AVC_Y_PB_PR:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_YPBPR;
                   break;
                   case DEV_AVC_VGA:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_VGA;
                   break;
                   case DEV_AVC_SCART:
                   case DEV_AVC_COMP_VIDEO:
                   case DEV_AVC_S_VIDEO:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_AV;
                   break;
                   case DEV_AVC_HDMI:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_HDMI;
                   break;
                   case DEV_AVC_DVI:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_DVI;
                   break;
                   default:
                       e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_AV;
                   break;
                }
            }
            else{
                e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_DTV;
            }
            nav_fac_c_rm_get_vid_comp((DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_VID_TYPE_ADC_R_GAIN + (ui2_idx-NAV_FAC_MENU_ADC_R_GAIN)),
                                          e_fac_vid_inp,& ui2_temp_val,& t_size);

            i2_val = ui2_temp_val;
	    break;
#endif
            //ke_vizio_20121113 modify
        case NAV_FAC_MENU_COLOR_TEMP:
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);

            switch (i2_val)
            {
                case ACFG_CUST_CLR_TEMP_WARM:
                {
                    i2_val = 0;
                }
                break;

                case ACFG_CUST_CLR_TEMP_COOL:
                {
                    i2_val = 1;
                }
                break;

                case ACFG_CUST_CLR_TEMP_NORMAL:
                {
                    i2_val = 2;
                }
                break;

                default:
                    i2_val = 0;
                    break;
            }
            break;

        #if 0
        case NAV_FAC_MENU_SCALER_R_GAIN:
        case NAV_FAC_MENU_SCALER_G_GAIN:
        case NAV_FAC_MENU_SCALER_B_GAIN:
        case NAV_FAC_MENU_SCALER_R_OFFSET:
        case NAV_FAC_MENU_SCALER_G_OFFSET:
        case NAV_FAC_MENU_SCALER_B_OFFSET:
            //ke_vizio_20121113 modify
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R +(ui2_idx-NAV_FAC_MENU_SCALER_R_GAIN)), &i2_val);
            break;
        #endif
        
#ifdef APP_DVBT_SUPPORT
        case NAV_FAC_MENU_OAD_ENABLE://Emerson Add 2008-0923 for OAD enable
            i2_val = a_cfg_cust_fac_is_oad_enable();
            break;
#endif
#if 0
        case NAV_FAC_MENU_VGA_SWITCH:
            i2_val = a_cfg_cust_fac_is_vga_switch();
            break;
#endif
#ifdef FAC_DUMP_CH_INFO
        case NAV_FAC_MENU_DUMP_CH_INFO:
            return NAVR_OK;
#endif
#ifdef FAC_DUMP_EEPROM
        case NAV_FAC_MENU_DUMP_EEPROM:
            return NAVR_OK;
#endif

#ifdef FAC_AUD_SRS_BYPASS
        case NAV_FAC_MENU_AUD_SRS_BYPASS:
        {
            i2_val = g_b_aud_srs_bypass_mode;
            break;
        }
#endif /* FAC_AUD_SRS_BYPASS */

#ifdef FAC_HDMI_PORT_NUM_SETTING
        case NAV_FAC_MENU_HDMI_PORT_NUM_SETTING:
        {
            UINT8 ui1_num = 0;
            _nav_fac_c_rm_get_hdmi_num(&ui1_num);
            i2_val = (INT16)ui1_num;
            break;
        }
#endif  /* FAC_HDMI_PORT_NUM_SETTING */

#ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
        case NAV_FAC_MENU_WINDOW_PATTERN:
        {
            i2_val = (INT16)g_b_WinPatOnOff;
            break;
        }
#endif

#ifdef FAC_BT_TESTBLE // Ben 20170809
        case NAV_FAC_MENU_TESTBLE:
		{
			i2_val = b_nav_fac_bt_testble_on_off;
			break;
		}
#endif

#ifdef FAC_WB_DATA  // Ben 20180411
        case NAV_FAC_MENU_FAC_WB_DATA:
        {
            DBG_LOG_PRINT(("\n %s b_nav_fac_wb_data=%d  Line: %d\n", __FUNCTION__, b_nav_fac_wb_data, __LINE__));
            a_cfg_custom_Get_Factory_GAMMA_OnOff(&b_nav_fac_wb_data);
            i2_val = b_nav_fac_wb_data;
            break;
        }
#endif

        case NAV_FAC_MENU_PQ_BYPASS:
        {
            i2_val = b_nav_fac_pq_bypass_on_off;
            break;
        }

#ifdef FAC_BACKLIGHT_CHECK // Ben 20180413
        case NAV_FAC_MENU_BACKLIGHT_CHECK:
        {
            i2_val = b_nav_fac_backlight_check_on_off;
            break;
        }
#endif

#ifdef FAC_PANEL_NITS // Ben 20180629
        case NAV_FAC_MENU_PANEL_NITS:
        {
            DBG_LOG_PRINT(("\n %s ui2_nav_fac_panel_nits=%d  Line: %d\n", __FUNCTION__, ui2_nav_fac_panel_nits, __LINE__));
            if (b_nav_fac_panel_nits_inited == FALSE)
            {
                b_nav_fac_panel_nits_inited = TRUE;
              #if 0  
                a_cfg_custom_get_HDR_panel_nits(&ui2_nav_fac_panel_nits);  
              #else
                a_cfg_cust_drv_read_panel_nits(&ui2_nav_fac_panel_nits);
              #endif
            }
            i2_val = ui2_nav_fac_panel_nits;
            break;
        }
#endif

        #ifdef TPV_HDMI_CERT
        case NAV_FAC_MENU_EARC_MUTE:
        {
            i2_val = acfg_cust_audio_get_earc_mute();
            break;
        }

        case NAV_FAC_MENU_EARC_WORD_LENGTH:
        {
            i2_val = acfg_cust_audio_get_earc_word_length();
            break;
        }

        case NAV_FAC_MENU_EARC_LAYOUT:
        {
            i2_val = acfg_cust_audio_get_earc_layout();
            break;
        }
        #endif /* TPV_HDMI_CERT */
        
        default :
            return NAVR_FAIL;
    }

    *pi4_val = i2_val;
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

//@jh todo    UINT16       ui2_i;		//kyo_20091002
    //PANEL_DATA_T   t_panel_data;  //@jh todo
    /* Assign aconfig mask definition for those items which could be recorded by bit set.*/
    switch (ui2_idx)
    {
#if 0
        case NAV_FAC_MENU_VGA_SWITCH:
            ui4_fac_acfg = APP_CFG_CUST_FAC_VGA_SWITCH;
            break;
#endif
        default :
            break;
    }

    /* Get current fac settings from EEPROM */
    a_cfg_cust_fac_get(&ui4_fac_val);

    switch (ui2_idx)
    {
#ifdef FAC_MENU_PANEL_TYPE_SELECT
        case NAV_FAC_MENU_PANEL_TYPE:
        {

DBG_LOG_PRINT(("!!!!@djh %s,  NAV_FAC_MENU_PANEL_TYPE:\n", __func__));            
#if 0 //@jh todo

            #if 0  //ke_vizio_20121025
            ui4_fac_val = _ar_Fac_Panel_ID_Map[i4_val].ui4_panel_id;

            i4_ret = a_cfg_custom_select_panel(ui4_fac_val, TRUE);
            if (i4_ret != APP_CFGR_OK){
                DBG_LOG_PRINT(("!!!!%s : a_cfg_custom_select_panel fail\n", __func__));
                return i4_ret;
            }
            #else
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
            
            #endif
            
            i4_ret = a_cfg_cust_fac_set_panel_type(i4_val);
            if (i4_ret != APP_CFGR_OK){
                DBG_LOG_PRINT(("!!!!%s : a_cfg_cust_fac_set_panel_type fail\n", __func__));
                return i4_ret;
            }

            i4_ret = acfg_custom_get_panel_data(&t_panel_data);		//kyo_20091002
            if (i4_ret != APP_CFGR_OK){
                DBG_LOG_PRINT(("!!!!%s : acfg_custom_get_panel_data fail\n", __func__));
                return i4_ret;
            }

            #ifdef APP_VIZIO_OSD_TREE_B            
            for(ui2_i=0; ui2_i < (ACFG_CLR_GAIN_ELEM_NUM-ACFG_CLR_TEMP_NUM); ui2_i++)
            {
                if( ui2_i >= (ACFG_CLR_GAIN_ELEM_NUM-(ACFG_CLR_TEMP_NUM*2)))
                {
                    /*  VGA restore to factory */
                    acfg_set_int16_by_idx(IDX_CLR_GAIN_R,   ui2_i,  t_panel_data.aai2_clr_gain[ui2_i][0]);
                    acfg_set_int16_by_idx(IDX_CLR_GAIN_G,   ui2_i,  t_panel_data.aai2_clr_gain[ui2_i][1]);
                    acfg_set_int16_by_idx(IDX_CLR_GAIN_B,   ui2_i,  t_panel_data.aai2_clr_gain[ui2_i][2]);
                }
                else
                {
                    /* Video */
                    acfg_set_int16_by_idx(IDX_CLR_GAIN_R,   ui2_i,  t_panel_data.aai2_clr_gain[ui2_i][0]);
                    acfg_set_int16_by_idx(IDX_CLR_GAIN_G,   ui2_i,  t_panel_data.aai2_clr_gain[ui2_i][1]);
                    acfg_set_int16_by_idx(IDX_CLR_GAIN_B,   ui2_i,  t_panel_data.aai2_clr_gain[ui2_i][2]);
                    
                    if(ui2_i < ACFG_CLR_TEMP_NUM*2)
                    {
                        /* Video and VGA */
                        acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, ui2_i,  t_panel_data.aai2_clr_offset[ui2_i][0]);
                        acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, ui2_i,  t_panel_data.aai2_clr_offset[ui2_i][1]);
                        acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, ui2_i,  t_panel_data.aai2_clr_offset[ui2_i][2]);
                    }
                }
            }
            #else
            //ACFG_CLR_GAIN_ELEM_NUM
            for(ui1_i=0; ui1_i < ACFG_CLR_GAIN_NUM; ui1_i++)
            {
                acfg_set_int16_by_idx(IDX_CLR_GAIN_R,	 ui1_i,  t_panel_data.aai2_clr_gain[ui1_i][0]);
                acfg_set_int16_by_idx(IDX_CLR_GAIN_G,	 ui1_i,  t_panel_data.aai2_clr_gain[ui1_i][1]);
                acfg_set_int16_by_idx(IDX_CLR_GAIN_B,	 ui1_i,  t_panel_data.aai2_clr_gain[ui1_i][2]);
                acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, ui1_i,  t_panel_data.aai2_clr_offset[ui1_i][0]);
                acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, ui1_i,  t_panel_data.aai2_clr_offset[ui1_i][1]);
                acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, ui1_i,  t_panel_data.aai2_clr_offset[ui1_i][2]);     
            }
            #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20130620
            //Re-write Fac part. Refer acfg_tpv_fac_panel.c.
            for(ui1_i=0; ui1_i < ACFG_CLR_TEMP_NUM; ui1_i++)
            {
                //Re-write 1st part of fac clr. (YPrPb part)
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_R,   ui1_i,  t_panel_data.aai2_clr_gain[2*ACFG_CLR_TEMP_NUM + ui1_i][0]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_G,   ui1_i,  t_panel_data.aai2_clr_gain[2*ACFG_CLR_TEMP_NUM + ui1_i][1]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_B,   ui1_i,  t_panel_data.aai2_clr_gain[2*ACFG_CLR_TEMP_NUM + ui1_i][2]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i,  t_panel_data.aai2_clr_offset[2*ACFG_CLR_TEMP_NUM + ui1_i][0]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i,  t_panel_data.aai2_clr_offset[2*ACFG_CLR_TEMP_NUM + ui1_i][1]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i,  t_panel_data.aai2_clr_offset[2*ACFG_CLR_TEMP_NUM + ui1_i][2]);

                //Re-write 2st part of fac clr. (VGA part)
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_R,   ui1_i+ACFG_CLR_TEMP_NUM,  t_panel_data.aai2_clr_gain[7*ACFG_CLR_TEMP_NUM + ui1_i][0]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_G,   ui1_i+ACFG_CLR_TEMP_NUM,  t_panel_data.aai2_clr_gain[7*ACFG_CLR_TEMP_NUM + ui1_i][1]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_B,   ui1_i+ACFG_CLR_TEMP_NUM,  t_panel_data.aai2_clr_gain[7*ACFG_CLR_TEMP_NUM + ui1_i][2]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i+ACFG_CLR_TEMP_NUM,  t_panel_data.aai2_clr_offset[7*ACFG_CLR_TEMP_NUM + ui1_i][0]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i+ACFG_CLR_TEMP_NUM,  t_panel_data.aai2_clr_offset[7*ACFG_CLR_TEMP_NUM + ui1_i][1]);
                acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i+ACFG_CLR_TEMP_NUM,  t_panel_data.aai2_clr_offset[7*ACFG_CLR_TEMP_NUM + ui1_i][2]);
            }
            #endif /* end of APP_CFG_FAC_CLR_TEMP */
            
            #endif

            UINT8 ui_hi, ui_low;
            a_cfg_custom_get_panel_backlight_HiLo(&ui_hi, &ui_low);

            i4_ret = acfg_set(IDX_CUST_VGA_PWM_MAX, &ui_hi , 1);
            if (i4_ret != APP_CFGR_OK){
                return i4_ret;
            }

            i4_ret = acfg_set(IDX_CUST_VGA_PWM_MIN, &ui_low , 1);
            if (i4_ret != APP_CFGR_OK){
                return i4_ret;
            }

            #ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2010/02/03 add
            if(nav_fac_BUF08630_tcon_check_panel())
            {
                i4_ret = nav_fac_tcon_load_def();
                if (i4_ret != APP_CFGR_OK){
                    DBG_LOG_PRINT(("nav_fac_tcon_load_def() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                }

                #if 0
                i4_ret = TPS65168_load_temp_def();
                if (i4_ret != APP_CFGR_OK){
                    DBG_LOG_PRINT(("TPS65168_load_temp_def() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                }
                #endif
            }
            #endif
#else   //Follow factory command setting
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

        #if 0   // Ben 20190904
            i4_ret = a_cfg_cust_fac_set_panel_type(i4_val);
            if (i4_ret != APP_CFGR_OK){
                DBG_LOG_PRINT(("!!!!%s : a_cfg_cust_fac_set_panel_type fail\n", __func__));
                return i4_ret;
            }
        #endif
        
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

#endif

            break;
        }
#endif        
#if 0	//kyo_20111221		
        case NAV_FAC_MENU_AUTO_COLOR://Emerson Add for auto-color 2008-0918
            if(nav_fac_is_signal_loss()||nav_fac_is_video_block())
            {
                b_nav_auto_color_busy = FALSE;
                ui2_nav_fac_auto_color_done= NAV_FAC_AUTO_COLOR_FAIL;
            }
            else
            {
                /* disable the system keys except the POWER key */
                a_amb_enable_system_key(FALSE);
                b_nav_auto_color_busy = TRUE;
            }
            break;
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
            
			b_nav_fac_install_ulpk_done = FALSE ;/*//sam 0331 for ULPK install in fac menu*/
#if 0	//kyo_20111221			
			ui2_nav_fac_auto_color_done= NAV_FAC_AUTO_COLOR_NONE;
			b_nav_auto_color_busy = FALSE;	
            b_nav_fac_erase_ulpk_done = FALSE ;/*//sam 110504 for ULPK erase in fac menu*/
#endif			
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
#if 0	//kyo_20111221            
	    case NAV_FAC_MENU_ADC_R_GAIN:
	    case NAV_FAC_MENU_ADC_G_GAIN:
	    case NAV_FAC_MENU_ADC_B_GAIN:
	    case NAV_FAC_MENU_ADC_R_OFFSET:
	    case NAV_FAC_MENU_ADC_G_OFFSET:
	    case NAV_FAC_MENU_ADC_B_OFFSET:
	    {    
            UINT32 ui4_val = (UINT32)i4_val;
            nav_fac_c_rm_set_vid_comp((DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_VID_TYPE_ADC_R_GAIN
            + (ui2_idx - NAV_FAC_MENU_ADC_R_GAIN)),(VOID *)(&ui4_val), sizeof(UINT16), TRUE);
            break;
        }
#endif		
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
                    i4_val = ACFG_CUST_CLR_TEMP_WARM;
                }
                break;
                case 1:
                {
                    i4_val = ACFG_CUST_CLR_TEMP_COOL;
                }
                break;
                case 2:
                {
                    i4_val = ACFG_CUST_CLR_TEMP_NORMAL;
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

        #if 0
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
        #endif
		    
	    case NAV_FAC_MENU_BURN_IN:
            {
                DBG_LOG_PRINT(("!!!!@djh %s , NAV_FAC_MENU_BURN_IN(%d) :\n", __func__, i4_val));
               
                if(i4_val == TRUE)
                {
                    a_cfg_fac_set_burning_mode(TRUE);

                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_RC_ON;
                    a_cfg_cust_fac_set(ui4_fac_val);

                    //ke_vizio_20130320 disable POWER key watchdog for keypad test.
                    // coz audio no output sound.
                    a_tv_net_send_cmd(":dtv_app_mtk,am,:disable_PKWD\n"); 
                }
                else
                {
                    a_cfg_fac_set_burning_mode(FALSE);
                }             
            }
            break;
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

	    case NAV_FAC_MENU_BACKLIGHT_MAX:
            acfg_set(IDX_CUST_VGA_PWM_MAX, &i4_val , 1);
            t_vid_info.e_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;
            t_vid_info.ui2Value	= (UINT16)i4_val;
            t_vid_info.b_ignore_hw  = TRUE;

			nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MAX, &t_vid_info, sizeof(VID_INFO_T), FALSE);

			a_cfg_store();
            break;

        case NAV_FAC_MENU_RESET:
            break;

#if 0	//kyo_20111221				
#ifdef FAC_ULPK_ERASE 
        case NAV_FAC_MENU_ERASE_ULPK: /*//sam 110504 for ULPK erase in fac menu*/
            break;
#endif			
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
#if 0
        case NAV_FAC_MENU_VGA_SWITCH:
            if (i4_val)
                ui4_fac_val = ui4_fac_val | ui4_fac_acfg;
            else
                ui4_fac_val = ui4_fac_val & ~ui4_fac_acfg;
            GPIO_SetOut(TOP_EU_IO_VGA_SWITCH_CONTROL ,i4_val);
            i4_ret =  a_cfg_cust_fac_set(ui4_fac_val);
            if (i4_ret != APP_CFGR_OK)
                return TVR_FAIL;
            a_cfg_store();
            break;
#endif
#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
        case NAV_FAC_MENU_WB_INTRNL_PAT:
            {
                nav_fac_sce_pat_set_level((UINT16)i4_val);
                nav_fac_sce_pat_enable_pat(TRUE);
                nav_fac_sce_pat_set_on_off_flag(TRUE);
            }
            break;
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

#ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
        case NAV_FAC_MENU_WINDOW_PATTERN:
        {
            g_b_WinPatOnOff = (BOOL)i4_val;
            nav_fac_border_window(g_b_WinPatOnOff, 400, 400, 350, 350);
            break;
        }
#endif

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
        
#ifdef FAC_BACKLIGHT_CHECK // Ben 20180403
                case NAV_FAC_MENU_BACKLIGHT_CHECK:
                {
                    b_nav_fac_backlight_check_on_off = i4_val;
                    a_cfg_custom_Set_Lcdim_Scrolling_OnOff(i4_val);
                    break;
                }
#endif
        
#ifdef FAC_WB_DATA  // Ben 20180411
                case NAV_FAC_MENU_FAC_WB_DATA:
                {
                    b_nav_fac_wb_data = i4_val;
                    a_cfg_custom_Set_Factory_GAMMA_OnOff(i4_val);
                    break;
                }
#endif
        
                case NAV_FAC_MENU_PQ_BYPASS:    // Ben 20180411
                {
                    b_nav_fac_pq_bypass_on_off = i4_val;
                    a_cfg_cust_drv_set_pq_bypass(i4_val);
                    break;
                }

#ifdef FAC_PANEL_NITS // Ben 20180629
                case NAV_FAC_MENU_PANEL_NITS:
                {
                    //i4_val += 20 * i4_val;
                    if ((i4_val - ui2_nav_fac_panel_nits) == 1 || (i4_val - ui2_nav_fac_panel_nits == -1))
                        ui2_nav_fac_panel_nits += (i4_val - ui2_nav_fac_panel_nits) * 10;
                    else
                        ui2_nav_fac_panel_nits = i4_val;
                    
                    break;
                }
#endif

        #ifdef TPV_HDMI_CERT
        case NAV_FAC_MENU_EARC_MUTE:
        {
            i4_ret = acfg_cust_audio_set_earc_mute((INT16)i4_val);
            TPV_LOG_ON_FAIL(i4_ret);
            break;
        }

        case NAV_FAC_MENU_EARC_WORD_LENGTH:
        {
            i4_ret = acfg_cust_audio_set_earc_word_length((INT16)i4_val);
            TPV_LOG_ON_FAIL(i4_ret);
            break;
        }

        case NAV_FAC_MENU_EARC_LAYOUT:
        {
            i4_ret = acfg_cust_audio_set_earc_layout((INT16)i4_val);
            TPV_LOG_ON_FAIL(i4_ret);
            break;
        }
        #endif /* TPV_HDMI_CERT */

        default :
            return NAVR_FAIL;
    }

    return i4_ret;

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

    i4_ret = nav_register_component(NAV_COMP_ID_FAC, &t_comp, COMP_EXC_SET_FAC);
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
    #if 0
    //ui2_elem_idx->0,4,8,c:user,1,5,9,d:cool,2,6,a,e:stardard,3,7,b,f:warm
    //i2_val->write value(0~100)
    //ui2_id->R_Gain,G_Gain,B_Gain,R_Offset,G_Offest,B_Offset
    //ui1_input->0:TV,1:AV,2:YPbPr,3:HDMI1,4:HDMI2,5:HDMI3,6:HDMI4,7:VGA,8:MMP; 9:VTRL

    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_input;
    UINT16      ui2_elem_idx;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];

    UINT8       ui1_input_grp;
    UINT16      ui2_rec_idx = 0;
    UINT16      ui2_rec_fac_idx = 0;
    INT16       i2_clr_temp = 0;
    INT16       ui2_result_i = 0;
    INT16       i2_val;
    UINT8       ui1_cnt;
    INT16       i2_GainOffset[6];
    ISL_REC_T   t_isl_rec;
    UINT16 ui2_id =0;

    for(ui1_cnt=0; ui1_cnt<6; ui1_cnt++)
    {
        i4_ret = a_cfg_av_get((CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R) + (INT16)ui1_cnt)
                            , &i2_GainOffset[ui1_cnt]);
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }
    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 2: Get the index */
    i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 3: Set the value */

    //i2_clr_temp->0:user,1:cool,2:medium,3:warm
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);


    for(ui1_cnt=0; ui1_cnt<6; ui1_cnt++)
    {
        i2_val = (UINT8)i2_GainOffset[ui1_cnt];
        ui2_rec_idx = IDX_CLR_GAIN_R + ui1_cnt;

    #ifdef APP_CFG_FAC_CLR_TEMP
        ui2_rec_fac_idx = IDX_CLR_FAC_GAIN_R + ui1_cnt;
    #endif
        
        ui2_id=CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R + ui1_cnt);
        /* Get input group */
        a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);
        ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec); 

        // Copy component's R/G/B gain & offset to TV/CVBS/HDMI1-4/YPbPr/VGA
        if(ui1_input_grp==ACFG_CUST_INPUT_GRP_COMPONENT)
        {
            //to make (input,ui2_elem_idx) be used for TV
            a_isl_get_rec_by_dev_type(DEV_TUNER, 0, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_TV ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif
            
            //to make (input,ui2_elem_idx) be used for CVBS
            a_isl_get_rec_by_dev_type(DEV_AVC_COMP_VIDEO, 0, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_CVBS ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif

            //to make (input,ui2_elem_idx) be used for HDMI
            a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI1 ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif

            //to make (input,ui2_elem_idx) be used for HDMI
            a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 1, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI2 ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif

            //to make (input,ui2_elem_idx) be used for HDMI
            a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 2, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI3 ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif
            
            //to make (input,ui2_elem_idx) be used for HDMI
            a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 3, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI4 ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif

            #if 0
            //to make (input,ui2_elem_idx) be used for YPbPr
            a_isl_get_rec_by_dev_type(DEV_AVC_Y_PB_PR, 0, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_COMPONENT ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif
        #endif
            
            //to make (input,ui2_elem_idx) be used for MMP
            a_isl_get_rec_by_dev_type(DEV_VTRL_MMP, 0, &t_isl_rec);
            acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
            ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_MMP ,i2_clr_temp ,i2_val);
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

        #ifdef APP_CFG_FAC_CLR_TEMP
            acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        #endif
        }
    }
    #else   //ke_vizio_20130620 modify
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

    #endif
    return i4_ret;
}
#endif /* FAC_MENU_CLR_COPY */

#ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20141107 modify
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
    UINT8 aui1_faccmd_ret_val_EEP_SN[CMD_LEN_Maximum] = {0};
    UINT8 ui1_image_bank_bit = 0;  //ke_vizio_20130520 add
    
	/* 	0x5AA  ~ 0x5B9 is EEPROM SN 	*/
	/* 	0x1C89 ~ 0x1C8F is BT-MAC 	*/
	/* 	0x1C90 ~ 0x1C9D is RJ45-MAC 	*/
	/* 	0x1C9E ~ 0x1DDD is HDCP 		*/

    //Get the image bank bit
    a_cfg_cust_get_image_bank_bit(&ui1_image_bank_bit);  //ke_vizio_20130520
    
    i4_ret = c_fm_lseek(h_file, 0, FM_SEEK_BGN, &ui8_pos);
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_fm_read(h_file, ui_byte, FAC_EEPROM_SIZE, &ui4_rw_byte);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(0, ui_byte, (FAC_EEPROM_SIZE), &ui4_rw_byte);
    TPV_LOG_ON_FAIL(i4_ret);

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
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_fm_read(h_file, ui_byte, FAC_EEPROM_SIZE, &ui4_rw_byte);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(0, ui_byte, (FAC_EEPROM_SIZE), &ui4_rw_byte);
    TPV_LOG_ON_FAIL(i4_ret);

    a_cfg_eep_cache_reload();


    return 0;
}
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
    TPV_LOG_ON_FAIL(i4_ret);
    
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
    TPV_LOG_ON_FAIL(i4_ret);
    
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
    if(ui1_mode == APP_CFG_FAC_MODE_BURNING)
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
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = c_fm_close(h_fm_dev_bin2eep);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = nav_fac_USBtoEEP_auto_dump_For_RD(h_fm_dev_bin2eep_RD);
		a_cfg_fac_reset(); //Larry 2014 1203 
		menu_clear_memory_ex(FALSE);    // Ben 20180129
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = c_fm_close(h_fm_dev_bin2eep_RD);
        TPV_LOG_ON_FAIL(i4_ret);
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

#ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
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

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
 * $RCSfile: tuner_setup_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/07/25 $
 * $Author: sin_fangyuan$
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "app_util/a_cli_app.h"
#include "nav/tuner_setup/tuner_setup_cli.h"
#include "nav/nav_common.h"

#include "u_cli.h"
#include "c_cli.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project-mtk-new-api.h"
#include "app_util/uli/uli_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "u_pcl.h"
#include "c_dlm.h"
#include "c_pcl.h"

#include "c_dbg.h"

#include "res/nav/one_channel_list/ocl.h"


/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/
static UINT16 ui2_g_tuner_dbg_level = DBG_LEVEL_ERROR;
extern UINT32 ui4_tuner_log_level;

extern INT32 tuner_setup_warning_show(UTF16_T* w2s_str);
extern INT32 tuner_setup_warning_hide(VOID);
extern VOID tuner_setup_view_auto_test(VOID);


/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
static INT32 _tuner_cmd_set_dbg_level(INT32        i4_argc,
                                    const CHAR** pps_argv);
static INT32 _tuner_cmd_get_dbg_level(INT32        i4_argc,
                                    const CHAR** pps_argv);
static INT32 _tuner_cmd_install_uli(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_get_uli(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_enable_log(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_bank_set(INT32        i4_argc,
                                const CHAR** pps_argv);

static INT32 _tuner_cmd_test_warning(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_set_ld_to_driver(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_auto_test(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_tuner_setup_enable(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _tuner_cmd_tuner_setup_dump_ch_lst(INT32        i4_argc,
                                const CHAR** pps_argv);

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
static CLI_EXEC_T at_tuner_cmd_tbl[] =
{
    {CLI_SET_DBG_LVL_STR, NULL, _tuner_cmd_set_dbg_level, NULL,
        "usage: " CLI_SET_DBG_LVL_STR " [level]", CLI_GUEST},

    {CLI_GET_DBG_LVL_STR, NULL, _tuner_cmd_get_dbg_level, NULL,
        "usage: " CLI_GET_DBG_LVL_STR, CLI_GUEST},
    {"warn_test", NULL, _tuner_cmd_test_warning, NULL,
        "usage: warnt 0/1", CLI_GUEST},
	{"uli", NULL, _tuner_cmd_install_uli, NULL,
		"usage: " "uli", CLI_GUEST},
	{"uli_get", NULL, _tuner_cmd_get_uli, NULL,
		"usage: " "uli", CLI_GUEST},
	{"log_set", NULL, _tuner_cmd_enable_log, NULL,
			"usage: " "log_set", CLI_GUEST},
	{"dual_bank", NULL, _tuner_cmd_bank_set, NULL,
				"usage: " "bank_set", CLI_GUEST},
    {"ld_test", "ldte", _tuner_cmd_set_ld_to_driver, NULL,
		"usage: ldte 0/1", CLI_GUEST},
    {"auto_test", "autot", _tuner_cmd_auto_test, NULL,
        "usage:""autot", CLI_GUEST},
    {"tuner_enable", "tuner_e", _tuner_cmd_tuner_setup_enable, NULL,
        "usage:""tuner_e", CLI_GUEST},
    {"tuner_ch_lst", "tcl", _tuner_cmd_tuner_setup_dump_ch_lst, NULL,
        "usage:""tcl", CLI_GUEST},

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_tuner_setup_entry =
{
    "tuner",
    "t",
    NULL,
    at_tuner_cmd_tbl,
    "tuner_setup Commands",
    NAV_CLI_ACCESS_RIGHT_LVL
};


/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: rest_get_dbg_level
 *
 * Description: This API returns the current setting of debug level.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: The current setting of debug level.
 ----------------------------------------------------------------------------*/
static UINT16 _tuner_get_dbg_level(VOID)
{
    return ui2_g_tuner_dbg_level;
}

/*-----------------------------------------------------------------------------
 * Name: rest_set_dbg_level
 *
 * Description: This API set the debug level.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: The current setting of debug level.
 ----------------------------------------------------------------------------*/
static VOID _tuner_set_dbg_level(
                    UINT16                      ui2_dbg_level
                    )
{
    ui2_g_tuner_dbg_level = ui2_dbg_level;
    ui4_tuner_log_level = (UINT32)ui2_dbg_level;
}


/******************************************************************************
 * Name
 *      _rest_cmd_set_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _tuner_cmd_set_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level = 0;
    CHAR    string[64] ={0};

	UINT32 ui4_buff_len = 64;
	BOOL   b_ulpk_valid=FALSE;

	a_uli_get_serial_number((UINT8 *)string, &ui4_buff_len);
	DBG_LOG_PRINT(("string: %s\n\r", string));
	b_ulpk_valid = a_uli_is_ulpk_valid();
	DBG_LOG_PRINT(("b_ulpk_valid: %d \n\r", b_ulpk_valid));
    if (c_cli_parse_dbg_level (i4_argc, pps_argv, &ui2_dbg_level) == CLIR_OK)
    {
        _tuner_set_dbg_level(ui2_dbg_level);
    }

    return(CLIR_OK);
}
static INT32 _tuner_cmd_get_uli(INT32        i4_argc,
                                const CHAR** pps_argv)
{
	const char *src_file = NULL;
	src_file = pps_argv[1];
	CHAR    string[128] ={0};
	CHAR    string_id_key[1024*2] ={0};
	CHAR    string_id_cert[1024*5] ={0};
	CHAR    string_id_password[1024] ={0};
	CHAR    string_id_trust[1024*100] ={0};
	CHAR    string_secret[16] ={0xEF,0xA4,0x92,0x8B,0x7B,0x7E,0x0F,0xDB,0xBF,0x33,0x93,0xF8,0xD7,0x05,0x07,0x6E};
	UINT8    string_cleardata[16+2] ={0};
    UINT32 ui4_buff_len = 0;
	UINT32 ui4_ulpk_index = 0;
    UINT32 ui4_index = 0;
	if(c_strstr(src_file,"ulpk") != NULL)
	{
		a_uli_get_factory_ulpk_v4((UINT8 *)string,&ui4_buff_len,&ui4_ulpk_index);
	}
	else if(c_strstr(src_file,"potk") != NULL)
	{
		a_uli_is_potk_valid();
	}
	else if(c_strstr(src_file,"snum") != NULL)
	{
		a_uli_get_serial_number((UINT8 *)string, &ui4_buff_len);
	}
	else if(c_strstr(src_file,"key") != NULL)
	{
		a_uli_factory_get_device_id_info("key",(UINT8 *)string_id_key, &ui4_buff_len);
	}
	else if(c_strstr(src_file,"cert") != NULL)
	{
		a_uli_factory_get_device_id_info("cert",(UINT8 *)string_id_cert, &ui4_buff_len);
	}
	else if(c_strstr(src_file,"password") != NULL)
	{
		a_uli_factory_get_device_id_info("password",(UINT8 *)string_id_password, &ui4_buff_len);
	}
	else if(c_strstr(src_file,"trust") != NULL)
	{
		a_uli_factory_get_device_id_info("trust",(UINT8 *)string_id_trust, &ui4_buff_len);
	}
	else if(c_strstr(src_file,"secret") != NULL)
	{
		a_uli_is_potk_valid_with_encrypted_shared_secret_internal((UINT8 *)string_secret, 16,(UINT8 *)string_cleardata);
		for(UINT32 index =0;index<16;index++)
		{
			DBG_LOG_PRINT(("value:%x  \n",string_cleardata[index]));
		}
	}
	DBG_LOG_PRINT(("%s:start  \n",src_file));
	DBG_LOG_PRINT(("ui4_buff_len:%d \n",ui4_buff_len));
	DBG_LOG_PRINT(("ui4_ulpk_index:%d \n",ui4_ulpk_index));

	DBG_LOG_PRINT(("%s:end  \n",src_file));
	return(CLIR_OK);
}
static INT32 set_log_level(UINT32 log_level)
{
     UINT32 ui4_log_level = log_level ;

     DBG_LOG_PRINT(("[%s %d] level = %x\n\r",__FUNCTION__,__LINE__,ui4_log_level));

     if(log_level > 0)
     {
          system("rm -f /tmp/uli_log_enable");
     }
     else
     {
          system("touch /tmp/uli_log_enable");
     }

     dbg_set_ctrl_stmt(log_level > 0 ? TRUE : FALSE);
     DBG_LOG_PRINT(("[VLOG][%s %d] dbg_get_ctrl_stmt %d\n\r",__FUNCTION__,__LINE__,dbg_get_ctrl_stmt()));

     if(log_level > 0)
     {
         system("/bin/echo 7 > /proc/sys/kernel/printk");
     }
     else
     {
         system("/bin/echo 0 > /proc/sys/kernel/printk");
     }

     a_cfg_cust_set_log_level(log_level);

     DBG_LOG_PRINT(("[VLOG][%s %d] vlog status %d\n\r",__FUNCTION__,__LINE__,ui4_log_level));
     return CLIR_OK;

}

static INT32 _tuner_cmd_enable_log(INT32        i4_argc,
                                const CHAR** pps_argv)
{
	set_log_level(4);
	return CLIR_OK;
}
static INT32 _tuner_cmd_bank_set(INT32        i4_argc,
                                const CHAR** pps_argv)
{
	UINT32                  ui4_bank_mask = 0;
	ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_LINUX_ROOTFS;
	ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_3RD;
	ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_KERNEL;
	DBG_LOG_PRINT(("[START] Toggle dual bank %x!!\n", ui4_bank_mask));
	c_pcl_toggle_dual_bank_by_mask(ui4_bank_mask);
	return CLIR_OK;
}

static INT32 _tuner_cmd_install_uli(INT32        i4_argc,
                                const CHAR** pps_argv)
{
	const char *src_file_path = NULL;
	FILE *fp;
    long l_size;
    unsigned char *pc_src_buf;
	long ulpk_index = 0;

    size_t z_result;
	src_file_path = pps_argv[1];
	

    /* open file for read */
    fp = fopen(src_file_path, "rb");
    if (fp == NULL) {
        DBG_LOG_PRINT(("open failed %s\n", src_file_path));
        return -1;
    }

    /* obtain file size */
    fseek(fp, 0, SEEK_END);
    l_size = ftell(fp);
    rewind(fp);

    if (l_size <= 0) {
        fclose(fp);
        DBG_LOG_PRINT(("empty file \n"));
        return -2;
    }

    /* allocate memory to contain the whole file */
    pc_src_buf = (char *)malloc(sizeof(char) * l_size);
    if (pc_src_buf == NULL) {
        fclose(fp);
        DBG_LOG_PRINT(("malloc failed \n"));
        return -3;
    }

    /* copy file into the pc_src_buf */
    z_result = fread(pc_src_buf, 1, l_size, fp);
    if (z_result != (size_t)l_size) {
        fclose(fp);
        free(pc_src_buf);

        DBG_LOG_PRINT(("read failed \n"));
        return -4;
    }
    fclose(fp);
	DBG_LOG_PRINT(("%s_%d l_size::%d \n",__FUNCTION__,__LINE__,l_size));
	if(c_strstr(src_file_path,"ulpk") != NULL)
	{
        INT32 i4_ret = 0;
		ulpk_index = atoi(pps_argv[2]);
		DBG_LOG_PRINT(("%s_%d ulpk_index::%d \n",__FUNCTION__,__LINE__,ulpk_index));
		i4_ret = a_uli_factory_install_ulpk_v4(pc_src_buf,l_size,ulpk_index);
        if(i4_ret < 0)
        {
            DBG_LOG_PRINT(("%s_%d a_uli_factory_install_ulpk_v4 failed \n",__FUNCTION__,__LINE__));
        }
	}
	else if(c_strstr(src_file_path,"potk") != NULL)
	{
		a_uli_factory_install_potk(pc_src_buf,l_size);
	}
	else if(c_strstr(src_file_path,"snum.txt") != NULL)
	{
		a_uli_factory_install_serial_number(pc_src_buf,l_size);
	}
        free(pc_src_buf);
	return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _rest_cmd_get_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _tuner_cmd_get_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
	FILE *fp;
    long l_size;
    unsigned char *pc_src_buf;
	UINT16 ui2_dbg_level = 0;
	ULI_NEW_MSG msg = {0};

    size_t z_result;
	//const char *src_file_path = NULL;
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));

	ui2_dbg_level = (INT16)c_strtoll(pps_argv[1], NULL, 0);;
	DBG_LOG_PRINT(("%s_%d ui2_dbg_level:%d \n",__FUNCTION__,__LINE__,ui2_dbg_level));
	if(ui2_dbg_level == 1)
	{
		msg.msgType = ULI_NEW_MSG_INIT;
		c_strncpy(msg.reserved, "Test_command1", ULI_MSG_STR_MAX_LEN);
	}
	else if(ui2_dbg_level == 3)

	{
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_IS_VALID;
		c_strncpy(msg.reserved, "Test_command_show", ULI_MSG_STR_MAX_LEN);	
	}
	else if(ui2_dbg_level == 4)

	{
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_SOURCE;
		c_strncpy(msg.reserved, "Test_command_show", ULI_MSG_STR_MAX_LEN);	
	}
	else if(ui2_dbg_level == 5)

	{
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_DOWNLOAD;
		c_strncpy(msg.reserved, "Test_command_show", ULI_MSG_STR_MAX_LEN);	
	}
	else if(ui2_dbg_level == 6)

	{
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_INSTALL;
		c_strncpy(msg.reserved, "Test_command_show", ULI_MSG_STR_MAX_LEN);	
	}
	else if(ui2_dbg_level == 7)
	{
		msg.msgType = ULI_NEW_MSG_CHECK_DRMP;
		c_strncpy(msg.reserved, "Test_command1", ULI_MSG_STR_MAX_LEN);

	}
	a_uli_msg_send_msg(&msg);
#if 0
    c_cli_show_dbg_level (_tuner_get_dbg_level());


    /* open file for read */
    fp = fopen(src_file_path, "rb");
    if (fp == NULL) {
        DBG_LOG_PRINT(("open failed %s\n", src_file_path));
        return -1;
    }

    /* obtain file size */
    fseek(fp, 0, SEEK_END);
    l_size = ftell(fp);
    rewind(fp);

    if (l_size <= 0) {
        fclose(fp);
        DBG_LOG_PRINT(("empty file \n"));
        return -2;
    }

    /* allocate memory to contain the whole file */
    pc_src_buf = (char *)malloc(sizeof(char) * l_size);
    if (pc_src_buf == NULL) {
        fclose(fp);
        DBG_LOG_PRINT(("malloc failed \n"));
        return -3;
    }

    /* copy file into the pc_src_buf */
    z_result = fread(pc_src_buf, 1, l_size, fp);
    if (z_result != (size_t)l_size) {
        fclose(fp);
        free(pc_src_buf);

        DBG_LOG_PRINT(("read failed \n"));
        return -4;
    }
    fclose(fp);
	DBG_LOG_PRINT(("%s_%d l_size::%d \n",__FUNCTION__,__LINE__,l_size));
	if(c_strstr(src_file_path,"ulpk") != NULL)
	{
		a_uli_factory_install_ulpk(pc_src_buf,l_size);
	}
	else if(c_strstr(src_file_path,"potk") != NULL)
	{
		a_uli_factory_install_potk(pc_src_buf,l_size);
	}
	else if(c_strstr(src_file_path,"snum.txt") != NULL)
	{
		a_uli_factory_install_serial_number(pc_src_buf,l_size);
	}
	#endif
    return CLIR_OK;
}


static INT32 _tuner_cmd_test_warning(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    ps = pps_argv[1] ;
 
    if(*ps == '0')
    {
        tuner_setup_warning_hide();
    }
    else if(*ps == '1')
    {
        //tuner_setup_warning_show(L"TEST MSG");
        tuner_setup_warning_show(L"Tuner has not been set up. To find channels, check if the RF cable is connected, \nthen press the OK key on the remote.");
    }
    return CLIR_OK;
}


static INT32 _tuner_cmd_set_ld_to_driver(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    ps = pps_argv[1] ;
    
    if(*ps == '0')
    {
        //banner_hide_sidebar();
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(FALSE);
    }
    else if(*ps == '1')
    {
        //banner_hide_sidebar();
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
    }
    return CLIR_OK;
}

static INT32 _tuner_cmd_auto_test(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    tuner_setup_view_auto_test(); 
    return CLIR_OK;
}

static INT32 _tuner_cmd_tuner_setup_enable(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: tuner_e [0/1] (only for nav scan)\
                        \n              0 -> disable tuner_setup\
                        \n              1 -> enable tuner_setup\
                        current val:%d \n",a_tuner_setup_enable_get())) ;
        return CLIR_INV_ARG ;               
    }   

    ps = pps_argv[1] ;
 
    if(*ps == '0')
    {
        a_tuner_setup_enable_set(FALSE);
    }
    else if(*ps == '1')
    {
        a_tuner_setup_enable_set(TRUE);
    }

    return CLIR_OK;
}

static INT32 _tuner_cmd_tuner_setup_dump_ch_lst(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    BOOL                        b_dump_all = FALSE;
    INT32                       target_idx = 0;
    INT16                       ocl_num = 0;
    INT32                       i4_idx = 0,i4_ret = 0;
    SVL_REC_T                   t_svl_rec;
    OCL_SVL_REC_T               t_ocl_svl_rec;
    //HANDLE_T                    h_tsl     = NULL_HANDLE;
    //TSL_REC_T                   t_tsl_rec = {0};
    //UINT32                      ui4_ver_id = SVL_NULL_VER_ID;
    
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: tcl [0/1] (dump channel list info)\
                        \n              0       -> dump all\
                        \n              1/2/..  -> dump idx ch \n")) ;
        return CLIR_INV_ARG ;               
    }  
    ps = pps_argv[1] ;
        
    ocl_num = ocl_get_ocl_num();
    DBG_LOG_PRINT(("[tuner scan] %d ocl_num=%d \n",__LINE__,ocl_num));
    
    if(*ps == '0')
    {
        b_dump_all = TRUE;
    }
    else
    {
        b_dump_all = FALSE;
        target_idx = atoi(ps);
        if(target_idx-1 > ocl_num)
        {
            return CLIR_INV_ARG;
        }
    }

    for(;i4_idx<ocl_num;i4_idx++)
    {
        if(!b_dump_all && (target_idx-1) != i4_idx)
            continue;
        
        c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
        c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));
        i4_ret = ocl_get_ocl_svl_by_index(i4_idx,&t_svl_rec,&t_ocl_svl_rec);
        if (OCLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[tuner scan] %s:%d get ocl fail,i4_idx=%d\n",__FUNCTION__,__LINE__,i4_idx));
            return OCLR_FAIL;
        }
       
        /* Dump SVL record */
        DBG_LOG_PRINT(("t_svl_rec info  ocl_idx[%d] ***************\n",i4_idx+1));
        DBG_LOG_PRINT((" .ui2_svl_rec_id        = %d \n",              t_svl_rec.ui2_svl_rec_id));
        DBG_LOG_PRINT((" .uheader\n"));
        DBG_LOG_PRINT(("   .t_rec_hdr\n"));
        DBG_LOG_PRINT(("     .ui4_channel_id    = 0x%X\n",             t_svl_rec.uheader.t_rec_hdr.ui4_channel_id));
        DBG_LOG_PRINT(("                        = (%d, %d)\n",         SB_ATSC_GET_MAJOR_CHANNEL_NUM(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id),
                                                                       SB_ATSC_GET_MINOR_CHANNEL_NUM(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id)));

        DBG_LOG_PRINT(("     .ui4_nw_mask       = 0x%X\n",             t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask));
        DBG_LOG_PRINT(("     .ui4_option_mask   = 0x%X\n",             t_svl_rec.uheader.t_rec_hdr.ui4_option_mask));
        DBG_LOG_PRINT(("     .ui2_prog_id       = %d\n",               t_svl_rec.uheader.t_rec_hdr.ui2_prog_id));
        DBG_LOG_PRINT(("     .ui2_tsl_id        = %d\n",               t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id));
        DBG_LOG_PRINT(("     .ui2_tsl_rec_id    = %d\n",               t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id));
        DBG_LOG_PRINT(("     .e_brdcst_type     = %d\n",               t_svl_rec.uheader.t_rec_hdr.e_brdcst_type));
        DBG_LOG_PRINT(("     .e_serv_type       = %d\n",               t_svl_rec.uheader.t_rec_hdr.e_serv_type));
        DBG_LOG_PRINT(("     .ac_name           = \"%s\"\n",           t_svl_rec.uheader.t_rec_hdr.ac_name));

        switch(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
        {
        case BRDCST_TYPE_ATSC:
            DBG_LOG_PRINT((" .udata\n"));
            DBG_LOG_PRINT(("   .t_atsc\n"));
            DBG_LOG_PRINT(("     .ui2_src_id        = %d\n",               t_svl_rec.u_data.t_atsc.ui2_src_id));
            DBG_LOG_PRINT(("     .ui2_prog_id       = %d\n",               t_svl_rec.u_data.t_atsc.ui2_prog_id));
            break;
        case BRDCST_TYPE_ANALOG:
            DBG_LOG_PRINT((" .udata\n"));
            DBG_LOG_PRINT(("   .t_analog\n"));
            DBG_LOG_PRINT(("     .ui4_s_comp_mask   = %d\n",               t_svl_rec.u_data.t_analog.ui4_s_comp_mask));
            DBG_LOG_PRINT(("     .ui4_tv_sys        = %d\n",               t_svl_rec.u_data.t_analog.ui4_tv_sys));
            DBG_LOG_PRINT(("     .ui4_audio_sys     = %d\n",               t_svl_rec.u_data.t_analog.ui4_audio_sys));
            DBG_LOG_PRINT(("     .e_vid_color_sys   = %d\n",               t_svl_rec.u_data.t_analog.e_vid_color_sys));
            DBG_LOG_PRINT(("     .ui2_src_id        = %d\n",               t_svl_rec.u_data.t_analog.ui2_src_id));
            DBG_LOG_PRINT(("     .b_valid_src_id    = %d\n",               t_svl_rec.u_data.t_analog.b_valid_src_id));
            break;
        default:
            break;
        }

    }
    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name tuner_setup_cli_init
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 tuner_setup_cli_init(VOID)
{
    return nav_register_comp_cli_entry(&t_g_tuner_setup_entry) ;
}


/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

#endif /* CLI_SUPPORT */


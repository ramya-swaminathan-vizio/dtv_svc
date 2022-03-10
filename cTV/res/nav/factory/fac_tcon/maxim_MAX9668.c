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
* Copyright (c) 2004, MediaTek Inc.
* All rights reserved.
*
* Unauthorized use, practice, perform, copy, distribution, reproduction,
* or disclosure of this information in whole or in part is prohibited.
*-----------------------------------------------------------------------------
* $RCSfile: nav_fac_tcon_pat.c,v $
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
#include "c_scc.h"
#include "c_common.h"
#include "c_handle_grp.h"
#include "c_svctx.h"
#include "c_os.h"

#include "u_gl.h"
//#include "u_os.h"

#include "app_util/a_cfg.h"
#include "nav_fac_tcon.h"

#include "res/nav/factory/a_factory.h"

#include "maxim_MAX9668.h"

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
#define VCOM_GAMMA1_REG         0x02
#define VCOM_GAMMA2_REG         0x03
#define VCOM_GAMMA3_REG         0x04
#define VCOM_GAMMA4_REG         0x05
#define VCOM_GAMMA5_REG         0x06
#define VCOM_GAMMA6_REG         0x07
#define VCOM_GAMMA7_REG         0x0B
#define VCOM_GAMMA8_REG         0x0C
    
#define VCOM_REG_INVALID        0xFF
    
#define FAC_VCOM_REG           0x12
#define FAC_VCOM_MIN_REG       0x18
#define FAC_VCOM_MAX_REG       0x19

#define VCOM_GAIN_REG          0x1A //sam 101124
    
#define WRITE_REG_HIBYTE_MASK(hi_byte)  ((UINT8)hi_byte + (UINT8)0x80)
#define WRITE_MTP_HIBYTE_MASK(hi_byte)  ((UINT8)hi_byte + (UINT8)0x40)
    
#define VCOM_I2C_PORT        0
#define VCOM_I2C_SLV_ADDR    0xEA	//sam 101201

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
UINT16  ui2_MAX9668_VCOM_DAC_value = 0x100;
UINT16  ui2_MAX9668_VCOM_DAC_min_value = 0;
UINT16  ui2_MAX9668_VCOM_DAC_max_value = 0x1ff;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_TCON_DEFAULT_T _ar_Fac_TCON_Default_Table[] =
{
    {
        PANEL_LG_37_LC370EUH_LDA1,  //M37  /* 2010.11.23 from LGD Jun Yeong Go*/
        { 829, 791, 732, 622, 357, 239, 172, 129},
        371,
        #if 0 //for TI use ,Vcom gain= -3
        8,
        #else //for MAXIM use ,Vcom gain= -3
        4,
        #endif
        0x200,  //Vcom Max
        0x133,  //Vcom Min
    },

    { 
        PANEL_LG_42_LC420EUH_LDA1, //E42 /* 2010.10.20 from LGD Dongjun You */
        { 883, 839, 772, 651, 383, 262, 195, 151},
        435,
        #if 1 //both TI & MAXIM "1" means Vcom gain = +1
        1,
        #endif
        0x3FF,  //Vcom Max
        0x000,  //Vcom Min
    },

    { 
        PANEL_LG_47_LC470EUH_LDA6, //E47 /* 2010.10.20 from LGD Dongjun You */
        { 883, 839, 772, 651, 383, 262, 195, 151},
        435,
        #if 1 //both TI & MAXIM "1" means Vcom gain = +1
        1,
        #endif
        0x3FF,  //Vcom Max
        0x000,  //Vcom Min
    },

    { 
        PANEL_LG_42_LC420EUH_LDF1, //E42 /* 2010.10.20 from LGD Dongjun You */
        { 883, 839, 772, 651, 383, 262, 195, 151},
        435,
        #if 1 //both TI & MAXIM "1" means Vcom gain = +1
        1,
        #endif
        0x3FF,  //Vcom Max
        0x000,  //Vcom Min
    },
//sam 110217
    { 
        PANEL_LG_47_LC470EUH_LDF6, //E47 /* 2010.10.20 from LGD Dongjun You */
        { 883, 839, 772, 651, 383, 262, 195, 151},
        435,
        #if 1 //both TI & MAXIM "1" means Vcom gain = +1
        1,
        #endif
        0x3FF,  //Vcom Max
        0x000,  //Vcom Min
    },

    {
        PANEL_LG_32_LC320EUH_LDF6,  //M32  /* 2010.11.23 from LGD Jun Yeong Go*/
        { 829, 791, 732, 622, 357, 239, 172, 129},
        371,
        #if 0 //for TI use ,Vcom gain= -3
        8,
        #else //for MAXIM use ,Vcom gain= -3
        4,
        #endif
        0x1C6,  //Vcom Max
        0x18A,  //Vcom Min
    },

    {
        PANEL_LG_37_LC370EUH_LDF6,  //M37  /* 2010.11.23 from LGD Jun Yeong Go*/
        { 829, 791, 732, 622, 357, 239, 172, 129},
        371,
        #if 0 //for TI use ,Vcom gain= -3
        8,
        #else //for MAXIM use ,Vcom gain= -3
        4,
        #endif
        0x200,  //Vcom Max
        0x133,  //Vcom Min
    },

};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
* Name: _nav_fac_get_tcon_reg_val
* Description:
* Inputs: ui1_reg_num
* Outputs: pui2_dac
* Returns:
----------------------------------------------------------------------------*/
static INT32 _nav_fac_get_tcon_reg_val( UINT8 ui1_reg_num, UINT16 * pui2_dac )
{
    UINT16  u2ByteCnt;
    UINT8   ui1_buffer[8] = {0};  //ke_vizio_20110330 for clean warning.
    INT32 i4_ret;

    u2ByteCnt = 2;

    i4_ret = nav_fac_sif_x_read(VCOM_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                               VCOM_I2C_SLV_ADDR,
                               1, ui1_reg_num,
                               ui1_buffer, u2ByteCnt);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("SIF_X_Read() failed\n"));
        return TCON_READ_FAIL;
    }

    *pui2_dac = ((UINT16)ui1_buffer[0] << 8) | ui1_buffer[1];

    return TCON_OK;
    
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_set_tcon_reg_val
* Description:
* Inputs: ui1_reg_num, ui2_dac
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _nav_fac_set_tcon_reg_val( UINT8 ui1_reg_num, UINT16 ui2_dac )
{
    UINT16  u2ByteCnt;
    UINT8   ui1_buffer[8];
    INT32 i4_ret;

    ui1_buffer[0] = WRITE_REG_HIBYTE_MASK( (UINT8)(ui2_dac >> 8) );     /* or 0x80 for write to reg */
    ui1_buffer[1] = (UINT8)(ui2_dac & 0xFF);
    u2ByteCnt = 2;

    i4_ret = nav_fac_sif_x_write(VCOM_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                                 VCOM_I2C_SLV_ADDR,
                                 1, ui1_reg_num,
                                 ui1_buffer, u2ByteCnt);

    if(i4_ret != 0 )
    {
        DBG_LOG_PRINT(("SIF_X_Write() failed. ui2_ret = %d on _nav_fac_set_tcon_reg_val() at line %d of %s\r\n", i4_ret, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }

    return TCON_OK;
}
 
/*----------------------------------------------------------------------------
* Name: _nav_fac_set_tcon_mtp
* Description: write val to MTP number, DAC & volt update at same time
* Inputs: ui1_reg_num     reg number
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _nav_fac_set_tcon_mtp( UINT8 ui1_mtp_num, UINT16 ui2_value )
{
#if TCON_EXTERNAL_NVRAM_W_ENABLE
    UINT16  u2ByteCnt;
    UINT8   ui1_buffer[8];
    INT32 i4_ret;

    ui1_buffer[0] = WRITE_MTP_HIBYTE_MASK( (UINT8)(ui2_value >> 8) );     /* or 0x40 for write to MTP */
    ui1_buffer[1] = (UINT8)(ui2_value & 0xFF);
    u2ByteCnt = 2;

    i4_ret = nav_fac_sif_x_write(VCOM_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                              VCOM_I2C_SLV_ADDR,
                              1, ui1_mtp_num,
                              ui1_buffer, u2ByteCnt);

    c_thread_delay(100); //c_thread_delay(32); //Denny 2009/12/08 add : Write gamma operations sometimes fail if c_thread_delay(32).

    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("SIF_X_Write() failed. ui2_ret = %d on _nav_fac_set_tcon_mtp() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    return APP_CFGR_OK;
#else
    DBG_LOG_PRINT(("%s TCON_WRITE_FAIL\n", __func__));
    return TCON_WRITE_FAIL;
#endif
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_vcom_get_gamma_reg
* Description: Get register address of Gamma1/Gamma2/.../Gamma8.
* Inputs:  ui1_gamma     -    Range is from 0 to 7. Represent Gamma1 to Gamma 8.
* Outputs:
* Returns: ui1_gamma_reg -    Reg addr. of Gamma1/Gamma2/.../Gamma8.
----------------------------------------------------------------------------*/
static UINT8 _nav_fac_vcom_get_gamma_reg(UINT8 ui1_gamma)
{
    UINT8   ui1_gamma_reg = VCOM_GAMMA1_REG;
    switch(ui1_gamma){
    case 0:  ui1_gamma_reg = VCOM_GAMMA1_REG;   break;
    case 1:  ui1_gamma_reg = VCOM_GAMMA2_REG;   break;
    case 2:  ui1_gamma_reg = VCOM_GAMMA3_REG;   break;
    case 3:  ui1_gamma_reg = VCOM_GAMMA4_REG;   break;
    case 4:  ui1_gamma_reg = VCOM_GAMMA5_REG;   break;
    case 5:  ui1_gamma_reg = VCOM_GAMMA6_REG;   break;
    case 6:  ui1_gamma_reg = VCOM_GAMMA7_REG;   break;
    case 7:  ui1_gamma_reg = VCOM_GAMMA8_REG;   break;
    default: ui1_gamma_reg = VCOM_REG_INVALID;  break;
    }
    
    return ui1_gamma_reg;
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_MAX9668_check_vcom_range
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static BOOL _nav_fac_MAX9668_check_vcom_range(VOID)
{
    INT32 i4_ret = TCON_OK;
    UINT32 ui4_panel_id;
    UINT16 ui2_i;
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_TCON_Default_Table)/sizeof(NAV_FAC_TCON_DEFAULT_T);
    UINT16 ui2_vcom_val = 0;
    
    ui4_panel_id = a_cfg_custom_get_cur_panelID();

     /* Find default value by current panel ID. */
    for(ui2_i=0; ui2_i<ui2_size_of_def_table; ui2_i++)
    {
        if(ui4_panel_id==_ar_Fac_TCON_Default_Table[ui2_i].u4PanelIndex){
            ui2_MAX9668_VCOM_DAC_min_value = _ar_Fac_TCON_Default_Table[ui2_i].ui2_vcom_min;
            ui2_MAX9668_VCOM_DAC_max_value = _ar_Fac_TCON_Default_Table[ui2_i].ui2_vcom_max;
            break;
        }
    }

    i4_ret = nav_fac_MAX9668_get_vcom_reg_val(&ui2_vcom_val);
    TCON_CHK_FAIL(i4_ret);

    if(ui2_vcom_val < ui2_MAX9668_VCOM_DAC_min_value)
    {
        return TRUE;
    }
    else if(ui2_vcom_val > ui2_MAX9668_VCOM_DAC_max_value)
    {
        return TRUE;
    }
    
    return FALSE;
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_MAX9668_set_vcom_max_min
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _nav_fac_MAX9668_set_vcom_max_min(VOID)
{
    INT32 i4_ret = TCON_OK;

    // Set the value to valid memory
    i4_ret = _nav_fac_set_tcon_reg_val(FAC_VCOM_MIN_REG, ui2_MAX9668_VCOM_DAC_min_value);
    TCON_CHK_FAIL(i4_ret);
    
    i4_ret = _nav_fac_set_tcon_reg_val(FAC_VCOM_MAX_REG, ui2_MAX9668_VCOM_DAC_max_value);
    TCON_CHK_FAIL(i4_ret);

    // Set the value to nonvolatile memory
    i4_ret = _nav_fac_set_tcon_mtp(FAC_VCOM_MIN_REG, ui2_MAX9668_VCOM_DAC_min_value);
    TCON_CHK_FAIL(i4_ret);
    
    i4_ret = _nav_fac_set_tcon_mtp(FAC_VCOM_MAX_REG, ui2_MAX9668_VCOM_DAC_max_value);
    TCON_CHK_FAIL(i4_ret);
    
    return TCON_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_tcon_gamma_reg_val
* Description: Get value from register of Gamma1/Gamma2/.../Gamma8.
* Inputs:  ui1_gamma       -    Range is from 0 to 7. Represent Gamma1 to Gamma 8.
* Outputs: *pui2_vcom_val  -    current VCOM value.
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_get_tcon_gamma_reg_val(UINT8 ui1_gamma, UINT16 *pui2_vcom_val )
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_gamma_reg = VCOM_GAMMA1_REG;

    ui1_gamma_reg = _nav_fac_vcom_get_gamma_reg(ui1_gamma);
    if(ui1_gamma_reg == VCOM_REG_INVALID){
        ui1_gamma_reg = VCOM_GAMMA1_REG;
    }
    i4_ret = _nav_fac_get_tcon_reg_val( ui1_gamma_reg, pui2_vcom_val );
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}
 
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_set_tcon_gamma_reg_val
* Description: Set value to register of Gamma1/Gamma2/.../Gamma8.
* Inputs: ui1_gamma          -    Range is from 0 to 7. Represent Gamma1 to Gamma 8.
*         ui2_gamma_val      -    The value will be written into reg of Gamma1/Gamma2/.../Gamma8.
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_set_tcon_gamma_reg_val(UINT8 ui1_gamma, UINT16 ui2_gamma_val )
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_gamma_reg = VCOM_GAMMA1_REG;

    ui1_gamma_reg = _nav_fac_vcom_get_gamma_reg(ui1_gamma);
    if(ui1_gamma_reg == VCOM_REG_INVALID){
        return TCON_INV_ARG;
    }
    
    i4_ret = _nav_fac_set_tcon_reg_val( ui1_gamma_reg, ui2_gamma_val );
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_vcom_reg_val
* Description: Get the Vcom value from Vcom register.
* Inputs:
* Outputs: *pui2_vcom_val      current VCOM value
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_get_vcom_reg_val( UINT16 *pui2_vcom_val )
{
    INT32 i4_ret = TCON_OK;

    i4_ret = _nav_fac_get_tcon_reg_val( FAC_VCOM_REG, pui2_vcom_val );
    TCON_CHK_FAIL(i4_ret);
    
    if( i4_ret == TCON_OK )
    {
        ui2_MAX9668_VCOM_DAC_value = *pui2_vcom_val;
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_vcom_gain_reg_val
* Description: Get the Vcom gain value from Vcom gain register.
* Inputs:
* Outputs: *pui2_vcom_gain_val      current VCOM gain value
* Returns:
----------------------------------------------------------------------------*/
//sam 101124
INT32 nav_fac_MAX9668_get_vcom_gain_reg_val( UINT16 *pui2_vcom_gain_val )
{
    INT32 i4_ret = TCON_OK;

    i4_ret = _nav_fac_get_tcon_reg_val( VCOM_GAIN_REG, pui2_vcom_gain_val );
    TCON_CHK_FAIL(i4_ret);

	#if 0
    if( i4_ret == TCON_OK )
    {
        ui2_VCOM_DAC_value = *pui2_vcom_gain_val;
    }
	#endif
    return i4_ret;
}
 
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_set_vcom_reg_val
* Description: Set Vcom value to register.
* Inputs: ui2_vcom_val     new VCOM reg. value
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_set_vcom_reg_val( UINT16 ui2_vcom_val )
{
    INT32 i4_ret = TCON_OK;

    i4_ret = _nav_fac_set_tcon_reg_val( FAC_VCOM_REG, ui2_vcom_val );
    TCON_CHK_FAIL(i4_ret);
    
    if( i4_ret == TCON_OK )
    {
        ui2_MAX9668_VCOM_DAC_value = ui2_vcom_val;
    }

    return i4_ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------
* Name: nav_fac_store_vcom_val
* Description: Write current Vcom value to MTP. It's non-volatile storage.
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_store_vcom_val ( void )
{
    INT32   i4_ret = TCON_OK;

    if( fac_vcom_init_get_status() == FALSE )
    {
        DBG_LOG_PRINT(("(fac_vcom_init_get_status()==FALSE) on nav_fac_store_vcom_val() at line %d of %s.\r\n", __LINE__, __FILE__));
        return TCON_FAIL;
    }

    i4_ret = _nav_fac_set_tcon_mtp( FAC_VCOM_REG, ui2_MAX9668_VCOM_DAC_value );
    if( i4_ret != TCON_OK )
    {
        DBG_LOG_PRINT(("_nav_fac_set_tcon_mtp() failed. i4_ret = %d on nav_fac_store_vcom_val() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }

    return TCON_OK;
}
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_def_gamma_by_panel_id
* Description: Get default value of Gamma1/Gamma2/.../Gamma8.
* Inputs:  ui1_gamma          -    Range is from 0 to 7. Represent Gamma1 to Gamma8.
* Outputs: pui2_gamma_val     -    default Gamma reg. value
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_get_def_gamma_by_panel_id(UINT32 ui4_panel_id, UINT8 ui1_gamma, UINT16 *pui2_gamma_val_def)
{
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_TCON_Default_Table)/sizeof(NAV_FAC_TCON_DEFAULT_T);
    UINT16 ui2_i;

    //ke_vizio_20110330 for clean warning.
    if(ui1_gamma > 7)  //u2GammaDef[8];
    {
        return TCON_INV_ARG;
    }
    
    /* Find default value by current panel ID. */
    for(ui2_i=0; ui2_i<ui2_size_of_def_table; ui2_i++)
    {
        if(ui4_panel_id==_ar_Fac_TCON_Default_Table[ui2_i].u4PanelIndex)
        break;
    }
    if(ui2_i >= ui2_size_of_def_table){
        return TCON_INV_ARG;
    }
    
    /* Get default value */
    *pui2_gamma_val_def = _ar_Fac_TCON_Default_Table[ui2_i].u2GammaDef[ui1_gamma];
    //DBG_LOG_PRINT("ui4_panel_id=%d, Gamma_Def[%d]=%d at line %d of %s\n", ui4_panel_id, ui1_gamma, *pui2_gamma_val_def, __LINE__, __FILE__);

    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_def_vcom_by_panel_id
* Description: Get default Vcom value by panel ID.
* Inputs:
* Outputs: *pui2_vcom_def    -    default Vcom reg. value
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_get_def_vcom_by_panel_id(UINT16 *pui2_vcom_def)
{
    UINT32 ui4_panel_id = 0;
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_TCON_Default_Table)/sizeof(NAV_FAC_TCON_DEFAULT_T);
    UINT16 ui2_i;

    ui4_panel_id = a_cfg_custom_get_cur_panelID();

    /* Find default value by current panel ID. */
    for(ui2_i=0; ui2_i<ui2_size_of_def_table; ui2_i++)
    {
        if(ui4_panel_id==_ar_Fac_TCON_Default_Table[ui2_i].u4PanelIndex)
            break;
    }
    if(ui2_i >= ui2_size_of_def_table){
        return TCON_INV_ARG;
    }
    /* Get default value */
    *pui2_vcom_def = _ar_Fac_TCON_Default_Table[ui2_i].u2VComDef;

    //DBG_LOG_PRINT("ui2_size_of_def_table = %d, ui4_panel_id = %d, u2VComDef = %d at line %d of %s\n", ui2_size_of_def_table, ui4_panel_id, *pui2_vcom_def, __LINE__, __FILE__);
    return TCON_OK;
}
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_def_vcom_gain_by_panel_id
* Description: Get default Vcom gain value by panel ID.
* Inputs:
* Outputs: *pui2_vcom_gain_def    -    default Vcom gain reg. value
* Returns:
----------------------------------------------------------------------------*/
//sam 101124
INT32 nav_fac_MAX9668_get_def_vcom_gain_by_panel_id(UINT16 *pui2_vcom_gain_def)
{
    UINT32 ui4_panel_id = 0;
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_TCON_Default_Table)/sizeof(NAV_FAC_TCON_DEFAULT_T);
    UINT16 ui2_i;

    ui4_panel_id = a_cfg_custom_get_cur_panelID();

    /* Find default value by current panel ID. */
    for(ui2_i=0; ui2_i<ui2_size_of_def_table; ui2_i++)
    {
        if(ui4_panel_id==_ar_Fac_TCON_Default_Table[ui2_i].u4PanelIndex)
            break;
    }
    if(ui2_i >= ui2_size_of_def_table){
        return TCON_INV_ARG;
    }
    /* Get default value */
    *pui2_vcom_gain_def = _ar_Fac_TCON_Default_Table[ui2_i].u2VComGainDef;

    //DBG_LOG_PRINT("ui2_size_of_def_table = %d, ui4_panel_id = %d, u2VComDef = %d at line %d of %s\n", ui2_size_of_def_table, ui4_panel_id, *pui2_vcom_def, __LINE__, __FILE__);
    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_load_def_gamma_by_panel_id
* Description: Load default value of Gamma1/Gamma2/.../Gamma8 into register. But not write into MTP.
* Inputs: ui1_gamma    -    Range is from 0 to 7. Represent Gamma1 to Gamma 8.
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_load_def_gamma_by_panel_id(UINT8 ui1_gamma)
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_gamma_reg = VCOM_GAMMA1_REG;
    UINT16 ui2_gamma_def=0x200;
    UINT32 ui4_panel_id;
    
    ui4_panel_id = a_cfg_custom_get_cur_panelID();

    ui1_gamma_reg = _nav_fac_vcom_get_gamma_reg(ui1_gamma);
    if(ui1_gamma_reg == VCOM_REG_INVALID){
        return TCON_INV_ARG;
    }

    i4_ret = nav_fac_MAX9668_get_def_gamma_by_panel_id(ui4_panel_id, ui1_gamma, &ui2_gamma_def);
    TCON_CHK_FAIL(i4_ret);
    //Printf("Default Gamma[%d] = %d at line %d of %s\n", ui1_gamma, ui2_gamma_val, __LINE__, __FILE__);

    i4_ret = _nav_fac_set_tcon_reg_val( ui1_gamma_reg, ui2_gamma_def );
    TCON_CHK_FAIL(i4_ret);
    
    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_load_def_vcom_by_panel_id
* Description: Load default Vcom value to register. But not write into MTP.
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_load_def_vcom_by_panel_id(VOID)
{
    INT32       i4_ret = TCON_OK;
    UINT16      ui2_vcom_def= 512;

    nav_fac_MAX9668_get_def_vcom_by_panel_id(&ui2_vcom_def);
    //DBG_LOG_PRINT("Default Vcom = %d at line %d of %s\n", ui2_vcom_def, __LINE__, __FILE__);

    i4_ret = _nav_fac_set_tcon_reg_val(FAC_VCOM_REG, ui2_vcom_def );
    TCON_CHK_FAIL(i4_ret);

    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_write_def_gamma_by_panel_id
* Description: Write default Gamma value to MTP. It's non-volatile storage.
* Inputs: ui1_gamma    -    Range is from 0 to 7. Represent Gamma1 to Gamma 8.
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_write_def_gamma_by_panel_id(UINT8 ui1_gamma)
{
    INT32 i4_ret = TCON_OK;

    UINT8 ui1_gamma_reg = VCOM_GAMMA1_REG;
    UINT16 ui2_gamma_def=512;
    UINT32 ui4_panel_id;
    
    ui4_panel_id = a_cfg_custom_get_cur_panelID();

    ui1_gamma_reg = _nav_fac_vcom_get_gamma_reg(ui1_gamma);
    if(ui1_gamma_reg == VCOM_REG_INVALID){
        return TCON_INV_ARG;
    }

    i4_ret = nav_fac_MAX9668_get_def_gamma_by_panel_id(ui4_panel_id, ui1_gamma, &ui2_gamma_def);
    TCON_CHK_FAIL(i4_ret);
    
    //DBG_LOG_PRINT("Default Gamma[%d] = %d at line %d of %s\n", ui1_gamma, ui2_gamma_def, __LINE__, __FILE__);

    i4_ret = _nav_fac_set_tcon_mtp( ui1_gamma_reg, ui2_gamma_def);
    TCON_CHK_FAIL(i4_ret);

    //Set the value for if the nonvolatile memory can't be written.
    i4_ret = _nav_fac_set_tcon_reg_val( ui1_gamma_reg, ui2_gamma_def);
    TCON_CHK_FAIL(i4_ret);

    return TCON_OK;
}
 
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_tcon_write_gamma
* Description: Write to reg of Gamma1/Gamma2/../Gamma8.
* Inputs: ui1_gamma    -    Range is from 0 to 7. Represent Gamma1 to Gamma 8.
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_tcon_write_gamma(UINT8 ui1_gamma)
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_gamma_reg = VCOM_GAMMA1_REG;
    UINT16 ui2_gamma_val=512;

    ui1_gamma_reg = _nav_fac_vcom_get_gamma_reg(ui1_gamma);
    if(ui1_gamma_reg == VCOM_REG_INVALID){
        return TCON_INV_ARG;
    }
 
    i4_ret = _nav_fac_get_tcon_reg_val( ui1_gamma_reg, &ui2_gamma_val );
    TCON_CHK_FAIL(i4_ret);

    i4_ret = _nav_fac_set_tcon_mtp( ui1_gamma_reg, ui2_gamma_val );
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}
 
/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_add_vcom_reg_offset
* Description: Write to Vcom register with offset value which is the offset from original Vcom value.
* Inputs: i2_offset_val    offset value
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_add_vcom_reg_offset ( INT16 i2_offset_val )
{
    INT32   i4_ret;
    UINT16  ui2_val=0;

    if( fac_vcom_init_get_status() == FALSE )
    {
        return TCON_FAIL;
    }

    ui2_val = (UINT16)((INT16)ui2_MAX9668_VCOM_DAC_value + i2_offset_val);
    if( ui2_val < ui2_MAX9668_VCOM_DAC_min_value )
    {
        ui2_val = ui2_MAX9668_VCOM_DAC_min_value ;
    }
    else if( ui2_val > ui2_MAX9668_VCOM_DAC_max_value )
    {
        ui2_val = ui2_MAX9668_VCOM_DAC_max_value ;
    }

    i4_ret = nav_fac_MAX9668_set_vcom_reg_val( ui2_val );
    if( i4_ret != TCON_OK )
    {
        DBG_LOG_PRINT(("nav_fac_MAX9668_set_vcom_reg_val() failed. i4_ret = %d on nav_fac_add_vcom_reg_offset() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }

    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_end_vcom_alignment
* Description: Save current Vcom value. It's non-volatile storage. 
*              And close Vcom test pattern.
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_end_vcom_alignment ( void )
{
    INT32   i4_ret;

    if( fac_vcom_init_get_status() == FALSE )
    {
        DBG_LOG_PRINT(("(fac_vcom_init_get_status()==FALSE) on %s at line %d of %s.\r\n", __func__, __LINE__, __FILE__));
        return TCON_FAIL;
    }

    i4_ret = _nav_fac_set_tcon_mtp( FAC_VCOM_REG, ui2_MAX9668_VCOM_DAC_value );
    if( i4_ret != TCON_OK )
    {
        DBG_LOG_PRINT(("_nav_fac_set_tcon_mtp() failed. i4_ret = %d on %s at line %d of %s.\r\n", i4_ret, __LINE__, __func__, __FILE__));
        return i4_ret;
    }

    if( fac_test_ptn_get_status() )
    {
        /* turn off internal pixel on/off pattern*/
        i4_ret = fac_test_ptn_page_hide();
        if( i4_ret != NAVR_OK )
        {
            DBG_LOG_PRINT(("fac_test_ptn_page_hide() failed. i4_ret = %d on %s at line %d of %s.\r\n", i4_ret, __func__, __LINE__, __FILE__));
            return i4_ret;
        }

        fac_test_ptn_set_status(FALSE);
    }

    fac_vcom_init_set_status(FALSE);

    return APP_CFGR_OK; 
}

/*----------------------------------------------------------------------------
* Name: nav_fac_write_def_vcom_by_panel_id
* Description: Write default Vcom value to MTP. It's non-volatile storage. 
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_write_def_vcom_by_panel_id(VOID)
{
    INT32 i4_ret = APP_CFGR_INTERNAL_ERR;

    UINT16 ui2_vcom_def = 512;

    nav_fac_MAX9668_get_def_vcom_by_panel_id(&ui2_vcom_def);

    i4_ret = _nav_fac_set_tcon_mtp( FAC_VCOM_REG, ui2_vcom_def );

    // Set the value for if  the nonvolatile memory can't be written. 
    i4_ret = _nav_fac_set_tcon_reg_val( FAC_VCOM_REG, ui2_vcom_def );

    return i4_ret;
}
/*----------------------------------------------------------------------------
* Name: nav_fac_BUF08630_write_def_vcom_gain_by_panel_id
* Description: Write default Vcom value to MTP. It's non-volatile storage. MAX9668 only can write 100 times!!!
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
//sam 101124
INT32 nav_fac_MAX9668_write_def_vcom_gain_by_panel_id(VOID)
{
    INT32 i4_ret = APP_CFGR_INTERNAL_ERR;

    UINT16 ui2_vcom_gain_def = 1;

    nav_fac_MAX9668_get_def_vcom_gain_by_panel_id(&ui2_vcom_gain_def);

    i4_ret = _nav_fac_set_tcon_mtp( VCOM_GAIN_REG, ui2_vcom_gain_def );

    // Set the value for if the nonvolatile memory can't be written.
    i4_ret = _nav_fac_set_tcon_reg_val( VCOM_GAIN_REG, ui2_vcom_gain_def );

    return i4_ret;
}
 
#ifdef SUPPORT_DOT_TO_DOT_PATTERN
/*----------------------------------------------------------------------------
* Name: _set_dot_to_do_pattern
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 _set_dot_to_do_pattern ( UINT8 red_level, UINT8 green_level, UINT8 blue_level )
{
    DRV_CUST_OPERATION_INFO_T t_op_info;
    VID_TYPE_DOT_TO_DOT_PATTERN_T t_set_info;
    INT32 i4_ret;

    t_set_info.b_on_off = TRUE; /* Turn ON */
    t_set_info.ui4_rgb_value = ((UINT32)red_level << 16) | ((UINT32)blue_level << 8) | (UINT32)green_level;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_DOT_TO_DOT_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)&t_set_info;
    t_op_info.u.t_vid_set_info.z_size = sizeof(VID_TYPE_DOT_TO_DOT_PATTERN_T);

    i4_ret = c_rm_set_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T) );

    if ( i4_ret != RMR_OK )
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    return APP_CFGR_OK;
}
 
INT32 _turn_off_dot_to_do_pattern (void)
{
    DRV_CUST_OPERATION_INFO_T t_op_info;
    VID_TYPE_DOT_TO_DOT_PATTERN_T t_set_info;
    INT32 i4_ret;

    t_set_info.b_on_off = FALSE; /* Turn Off */
    t_set_info.ui4_rgb_value = 0x00;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_DOT_TO_DOT_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)&t_set_info;
    t_op_info.u.t_vid_set_info.z_size = sizeof(VID_TYPE_DOT_TO_DOT_PATTERN_T);
 
    i4_ret = c_rm_set_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T) );
 
    if ( i4_ret != RMR_OK )
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    return APP_CFGR_OK;
}
#endif // end of SUPPORT_DOT_TO_DOT_PATTERN
 
/*----------------------------------------------------------------------------
* Name: nav_fac_tcon_check_and_set_def_val
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_tcon_check_and_set_def_val(VOID)
{
    INT32   i4_ret = APP_CFGR_INTERNAL_ERR;
    UINT8   ui1_i;
    UINT16  ui2_gamma_val[8] = {0};
    UINT16  ui2_vcom_val = 0;
    UINT16  ui2_vcom_gain_val = 0;//sam 101124
    BOOL    b_Gamma_is_default = TRUE;
    UINT32 ui4_panel_id;
    BOOL    b_vcom_is_over = FALSE;

    ui4_panel_id = a_cfg_custom_get_cur_panelID();

    /* Check if default Gamma are written */
    for(ui1_i=0; ui1_i<8; ui1_i++)
    {
        UINT16  ui2_gamma_def = 512;

        i4_ret = nav_fac_MAX9668_get_tcon_gamma_reg_val( ui1_i, &ui2_gamma_val[ui1_i] );
        TCON_CHK_FAIL(i4_ret);
 
        i4_ret = nav_fac_MAX9668_get_def_gamma_by_panel_id(ui4_panel_id, ui1_i, &ui2_gamma_def);
        TCON_CHK_FAIL(i4_ret);
 
        /* Check if it matches default Gamma value */
        if(ui2_gamma_val[ui1_i] != ui2_gamma_def)
        {
            b_Gamma_is_default = FALSE;
            break;
        }
    }

    /* Check Vcom range is if over. If over,  b_Gamma_is_default == FALSE */
    b_vcom_is_over = _nav_fac_MAX9668_check_vcom_range();

    if(b_vcom_is_over == TRUE)
    {
        //Set Vom Max & Min.
        _nav_fac_MAX9668_set_vcom_max_min();
    }

    /* Check & Write Default Value */
    if(b_Gamma_is_default == FALSE)
    {
        /* Vcom */
        {
            UINT8   ui1_cnt = 0;
            do
            {
                UINT16  ui2_vcom_def = 512;
 
                i4_ret = nav_fac_MAX9668_get_vcom_reg_val(&ui2_vcom_val );
                TCON_CHK_FAIL(i4_ret);
                
                i4_ret = nav_fac_MAX9668_get_def_vcom_by_panel_id(&ui2_vcom_def);
                TCON_CHK_FAIL(i4_ret);

                /* Check if match default Vcom value */
                if(ui2_vcom_val != ui2_vcom_def)
                {
                    /* Write default Vcom */
                    nav_fac_MAX9668_write_def_vcom_by_panel_id();
                    ui1_cnt++;
                }
                else
                {
                    ui1_cnt = 0;
                    break;
                }
                /* Retry 10 times */
                if(ui1_cnt >= 10)
                {
                    ui1_cnt = 0;
                    DBG_LOG_PRINT(("Write failed in TCon Vcom at line %d of %s.\r\n", __LINE__, __FILE__));
                    break;
                }
            }
            while(1);
        }

        /* Vcom Gain */ //sam 101124
        {
            UINT8   ui1_cnt = 0;
            do
            {
                UINT16  ui2_vcom_gain_def = 1;
 
                i4_ret = nav_fac_MAX9668_get_vcom_gain_reg_val(&ui2_vcom_gain_val );
                TCON_CHK_FAIL(i4_ret);
                
                i4_ret = nav_fac_MAX9668_get_def_vcom_gain_by_panel_id(&ui2_vcom_gain_def);
                TCON_CHK_FAIL(i4_ret);

                /* Check if match default Vcom gain value */
                if(ui2_vcom_gain_val != ui2_vcom_gain_def)
                {
                    /* Write default Vcom gain */
                    nav_fac_MAX9668_write_def_vcom_gain_by_panel_id();
                    ui1_cnt++;
                }
                else
                {
                    ui1_cnt = 0;
                    break;
                }
                /* Retry 10 times */
                if(ui1_cnt >= 10)
                {
                    ui1_cnt = 0;
                    DBG_LOG_PRINT(("Write failed in TCon Vcom at line %d of %s.\r\n", __LINE__, __FILE__));
                    break;
                }
            }
            while(1);
        }


        /* Gamma */
        for(ui1_i=0; ui1_i<8; ui1_i++)
        {
            UINT8   ui1_cnt = 0;
            do
            {
                UINT16  ui2_gamma_def = 512;

                i4_ret = nav_fac_MAX9668_get_tcon_gamma_reg_val( ui1_i, &ui2_gamma_val[ui1_i] );
                TCON_CHK_FAIL(i4_ret);

                i4_ret = nav_fac_MAX9668_get_def_gamma_by_panel_id(ui4_panel_id, ui1_i, &ui2_gamma_def);
                TCON_CHK_FAIL(i4_ret);

                /* Check if it matches default Gamma value */
                if(ui2_gamma_val[ui1_i] != ui2_gamma_def)
                {
                    /* Write default Gamma */
                    ui1_cnt++;
                    i4_ret = nav_fac_MAX9668_write_def_gamma_by_panel_id(ui1_i);
                    TCON_CHK_FAIL(i4_ret);
                }
                else
                {
                    ui1_cnt = 0;
                    break;
                }
                /* Retry 10 times */
                if(ui1_cnt >= 10)
                {
                    ui1_cnt = 0;
                    DBG_LOG_PRINT(("Write failed in TCon Gamma[%d] at line %d of %s.\r\n", ui1_i, __LINE__, __FILE__));
                    break;
                }
            }
            while(1);
        }
    }
 
    return i4_ret;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_get_vcom_max_min_val
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 nav_fac_MAX9668_get_vcom_max_min_val(UINT16* i2_max, UINT16* i2_min)
{
    INT32 i4_ret = TCON_OK;
    i4_ret = _nav_fac_get_tcon_reg_val(FAC_VCOM_MIN_REG, i2_min);
    TCON_CHK_FAIL(i4_ret);

    i4_ret = _nav_fac_get_tcon_reg_val(FAC_VCOM_MAX_REG, i2_max);
    TCON_CHK_FAIL(i4_ret);
    
    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_tcon_check_panel
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
BOOL nav_fac_MAX9668_tcon_check_panel(VOID)
{
    UINT32 ui4_panel_id;
    UINT16 ui2_i;
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_TCON_Default_Table)/sizeof(NAV_FAC_TCON_DEFAULT_T);
    
    ui4_panel_id = a_cfg_custom_get_cur_panelID();

     /* Find default value by current panel ID. */
    for(ui2_i=0; ui2_i<ui2_size_of_def_table; ui2_i++)
    {
        if(ui4_panel_id==_ar_Fac_TCON_Default_Table[ui2_i].u4PanelIndex){
            //DBG_LOG_PRINT("!!!!%s : return TRUE\n", __func__);
            return TRUE;
        }
    }

    //DBG_LOG_PRINT("!!!!%s : return FALSE\n", __func__);
    return FALSE;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_MAX9668_tcon_is_existed
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
BOOL nav_fac_MAX9668_tcon_is_existed(VOID)
{
    UINT8   ui1_buffer[8];
    INT32 i4_ret;

    i4_ret = nav_fac_sif_x_read(VCOM_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                               VCOM_I2C_SLV_ADDR,
                               1, 0,
                               ui1_buffer, 2);
    if( i4_ret != 0 )
    {
        return FALSE;
    }

    return TRUE;
}

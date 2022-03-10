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
//#include "c_scc.h"
//#include "c_common.h"
//#include "c_handle_grp.h"
//#include "c_svctx.h"
//#include "c_os.h"

//#include "u_gl.h"

//#include "app_util/a_cfg.h"
#include "nav_fac_tcon.h"

//#include "res/nav/factory/a_factory.h"

#include "maxim_PF78IOS.h"

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/


#define PF78IOS_VDD          0x00
#define PF78IOS_HVDD         0x01
#define PF78IOS_VCC           0x02
#define PF78IOS_VCORE        0x03
#define PF78IOS_VGH_C        0x04
#define PF78IOS_VGH_W        0x05
#define PF78IOS_VGL           0x06
#define PF78IOS_DLY1          0x07
#define PF78IOS_DLY2          0x08
#define PF78IOS_DLY3          0x09
#define PF78IOS_MEM_BANK     0x20
#define PF78IOS_CR            0xFF

#define PF78IOS_INVALID_REG            0x0F

#define PF78IOS_REG           0x12

#define PF78IOS_I2C_PORT        0
#define PF78IOS_I2C_SLV_ADDR    0x42	//sam 101201

#define PF78IOS_WRITE_DELAY 100  // 100ms
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct _NAV_FAC_PF78IOS_T
{
    UINT32      u4PanelIndex;                         /* Panel Index */
    UINT8      ui1_val[10];                        /* Default Value */
} _NAV_FAC_PF78IOS_T;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _NAV_FAC_PF78IOS_T _ar_Fac_PF78IOS_Default_Table[] =
{
    /* Default Panel Index ,
           {VDD, HVDD, VI/O(VCC), VCORE, VGH1(VGH_C), VGH2(VGH_W), VGL, DLY1, DLY2, DLY3}
      */
    
    { 
        PANEL_LG_37_LC370EUH_LDA1, //M37	/* 2010.09.28 from LGD Dongjun You */
        {0x1C,0x18,0x03,0x01,0x0d,0x0b,0x36,0x01,0x03,0x03},
    },
	{ 
		PANEL_LG_42_LC420EUH_LDA1,	//E42	/* 2011.01.14 from LGD Dongjun You */
		{0x28,0x27,0x03,0x01,0x0b,0x0b,0x20,0x02,0x02,0x02},
	},
    
	{ 
		PANEL_LG_47_LC470EUH_LDA6,	//E47	/* 2011.01.14 from LGD Dongjun You */
		{0x28,0x27,0x03,0x01,0x0b,0x0b,0x20,0x02,0x02,0x02},
	},
	
	{ 
		PANEL_LG_42_LC420EUH_LDF1,	//E42	/* 2011.01.14 from LGD Dongjun You */
		{0x28,0x27,0x03,0x01,0x0b,0x0b,0x20,0x02,0x02,0x02},
	},
//sam 110217
	{ 
		PANEL_LG_47_LC470EUH_LDF6,	//E47	/* 2011.01.14 from LGD Dongjun You */
		{0x28,0x27,0x03,0x01,0x0b,0x0b,0x20,0x02,0x02,0x02},
	},
	
	{ 
		PANEL_LG_32_LC320EUH_LDF6, //M32	/* 2010.09.28 from LGD Dongjun You */
		{0x1C,0x18,0x03,0x01,0x0d,0x0b,0x36,0x01,0x03,0x03},
	},

	{ 
		PANEL_LG_37_LC370EUH_LDF6, //M37	/* 2010.09.28 from LGD Dongjun You */
		{0x1C,0x18,0x03,0x01,0x0d,0x0b,0x36,0x01,0x03,0x03},
	},
};
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
* Name: _PF78IOS_read_reg_val
* Description:
* Inputs: ui1_reg_num
* Outputs: pui_dec
* Returns:
----------------------------------------------------------------------------*/
static INT32 _PF78IOS_read_reg_val( UINT8 ui1_reg_address, UINT8 * pui1_dec )
{
    UINT8   ui1_buffer[8];
    INT32 i4_ret;

    // Control Register
    ui1_buffer[0] = 0x00;
    i4_ret = nav_fac_sif_x_write(PF78IOS_I2C_PORT,   /*IIC port*/
                                270,  /*27M/270=100kHz*/
                                PF78IOS_I2C_SLV_ADDR,
                                1, PF78IOS_CR,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }
    
    i4_ret = nav_fac_sif_x_read(PF78IOS_I2C_PORT ,  /*IIC port*/
                                270,          /*27M/270=100kHz*/
                                PF78IOS_I2C_SLV_ADDR,
                                1, ui1_reg_address,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("% failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_READ_FAIL;
    }

    *pui1_dec = ui1_buffer[0];

    return TCON_OK;
    
}

/*----------------------------------------------------------------------------
* Name: _PF78IOS_write_reg_val
* Description:
* Inputs: ui1_reg_num, ui2_dac
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _PF78IOS_write_reg_val( UINT8 ui1_reg_address, UINT8 ui1_dac )
{
    INT32 i4_ret;
    UINT8   ui1_buffer[1];

    ui1_buffer[0] = ui1_dac;

    // Control Register
    ui1_buffer[0] = 0x00;
    i4_ret = nav_fac_sif_x_write(PF78IOS_I2C_PORT,   /*IIC port*/
                                270,  /*27M/270=100kHz*/
                                PF78IOS_I2C_SLV_ADDR,
                                1, PF78IOS_CR,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }

    ui1_buffer[0] = ui1_dac;
    i4_ret = nav_fac_sif_x_write(PF78IOS_I2C_PORT , /*IIC port*/
                                270,   /*27M/270=100kHz*/
                                PF78IOS_I2C_SLV_ADDR,
                                1, ui1_reg_address,
                                ui1_buffer, 1);

    if(i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }

    return TCON_OK;
}
/*----------------------------------------------------------------------------
* Name: _PF78IOS_get_non_volatile_reg_val
* Description:
* Inputs: ui1_reg_num
* Outputs: pui_dec
* Returns:
----------------------------------------------------------------------------*/
static INT32 _PF78IOS_get_non_volatile_reg_val( UINT8 ui1_reg_address, UINT8 * pui1_dec )
{
    UINT8   ui1_buffer[8];
    INT32 i4_ret;
    
    // Control Register
    ui1_buffer[0] = 0x01;
    i4_ret = nav_fac_sif_x_write(PF78IOS_I2C_PORT,   /*IIC port*/
                                270,  /*27M/270=100kHz*/
                                PF78IOS_I2C_SLV_ADDR,
                                1, PF78IOS_CR,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }
    
    i4_ret = nav_fac_sif_x_read(PF78IOS_I2C_PORT ,  /*IIC port*/
                                270,          /*27M/270=100kHz*/
                                PF78IOS_I2C_SLV_ADDR,
                                1, ui1_reg_address,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_READ_FAIL;
    }

    *pui1_dec = ui1_buffer[0];

    return TCON_OK;
    
}

/*----------------------------------------------------------------------------
* Name: _PF78IOS_set_non_volatile_reg_val
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _PF78IOS_set_non_volatile_reg_val( UINT8 ui1_reg_address, UINT8 ui1_value )
{
#if TCON_EXTERNAL_NVRAM_W_ENABLE
    INT32 i4_ret;
    UINT8   ui1_buffer[1];

    ui1_buffer[0] = ui1_value;
     
    //DBG_LOG_PRINT("SIF_X_Write() ui1_buffer[0] = %d\n", ui1_buffer[0]);
    
    i4_ret = nav_fac_sif_x_write(PF78IOS_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                                PF78IOS_I2C_SLV_ADDR,
                                1, ui1_reg_address,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }
 
    // Control Register
    ui1_buffer[0] = 0x80;
    i4_ret = nav_fac_sif_x_write(PF78IOS_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                                PF78IOS_I2C_SLV_ADDR,
                                1, PF78IOS_CR,
                                ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return TCON_WRITE_FAIL;
    }

    c_thread_delay(PF78IOS_WRITE_DELAY);
    return TCON_OK;
#else
    DBG_LOG_PRINT(("%s TCON_WRITE_FAIL\n", __func__));
    return TCON_WRITE_FAIL;
#endif
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_get_PF78IOS_reg
* Description:
* Inputs: 
* Outputs:
* Returns: 
----------------------------------------------------------------------------*/
static UINT8 _PF78IOS_get_reg(UINT8 ui1_reg_num)
{
    UINT8   ui1_reg_address = PF78IOS_INVALID_REG;
    switch(ui1_reg_num){
    case 0:  ui1_reg_address = PF78IOS_VDD;   break;
    case 1:  ui1_reg_address = PF78IOS_HVDD;   break;
    case 2:  ui1_reg_address = PF78IOS_VCC;   break;
    case 3:  ui1_reg_address = PF78IOS_VCORE;   break;
    case 4:  ui1_reg_address = PF78IOS_VGH_C;   break;
    case 5:  ui1_reg_address = PF78IOS_VGH_W;   break;
    case 6:  ui1_reg_address = PF78IOS_VGL;   break;
    case 7:  ui1_reg_address = PF78IOS_DLY1;   break;
    case 8:  ui1_reg_address = PF78IOS_DLY2;   break;
    case 9:  ui1_reg_address = PF78IOS_DLY3;   break;
    default: ui1_reg_address = PF78IOS_INVALID_REG;  break;
    }
    
    return ui1_reg_address;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
* Name: nav_fac_get_PF78IOS_reg_val
* Description: 
* Inputs: 
* Outputs: 
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_get_reg_val(UINT8 ui1_reg_num, UINT8 *pui_val )
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_reg_address = PF78IOS_INVALID_REG;

    ui1_reg_address = _PF78IOS_get_reg(ui1_reg_num);
    if(ui1_reg_address == PF78IOS_INVALID_REG){
        return TCON_INV_ARG;
    }
    
    i4_ret = _PF78IOS_read_reg_val(ui1_reg_address, pui_val );
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}
 
/*----------------------------------------------------------------------------
* Name: PF78IOS_set_reg_val
* Description: Set value to register
* Inputs: 
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_set_reg_val(UINT8 ui1_reg_num, UINT8 ui1_val )
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_reg_address = PF78IOS_INVALID_REG;

    ui1_reg_address = _PF78IOS_get_reg(ui1_reg_num);
    if(ui1_reg_address == PF78IOS_INVALID_REG){
        return TCON_INV_ARG;
    }
    
    i4_ret = _PF78IOS_write_reg_val(ui1_reg_address, ui1_val);
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}
/*----------------------------------------------------------------------------
* Name: PF78IOS_get_non_volatile_val
* Description: Set value to non volatile
* Inputs: 
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_get_non_volatile_val(UINT8 ui1_reg_num, UINT8 *pui_val )
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_reg_address = PF78IOS_INVALID_REG;

    ui1_reg_address = _PF78IOS_get_reg(ui1_reg_num);
    if(ui1_reg_address == PF78IOS_INVALID_REG){
        return TCON_INV_ARG;
    }
    
    i4_ret = _PF78IOS_get_non_volatile_reg_val(ui1_reg_address, pui_val);
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
* Name: PF78IOS_set_non_volatile_val
* Description: Set value to non volatile
* Inputs: 
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_set_non_volatile_val(UINT8 ui1_reg_num, UINT8 ui1_val )
{
    INT32 i4_ret = TCON_OK;
    UINT8 ui1_reg_address = PF78IOS_INVALID_REG;

    ui1_reg_address = _PF78IOS_get_reg(ui1_reg_num);
    if(ui1_reg_address == PF78IOS_INVALID_REG){
        return TCON_INV_ARG;
    }
    
    i4_ret = _PF78IOS_set_non_volatile_reg_val(ui1_reg_address, ui1_val);
    TCON_CHK_FAIL(i4_ret);
    
    return i4_ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------
* Name: PF78IOS_write_default_val_by_panel_id
* Description: write to non-volatile.
* Inputs: 
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_write_default_non_volatile_val_by_panel_id(UINT32 ui4_panel_id)
{
    INT32 i4_ret = TCON_OK;

    UINT8 ui1_reg_address; //ke_vizio_20110330 for clean warning.
    UINT8 ui1_idx;
    UINT32 ui2_panel_idx = 0;
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_PF78IOS_Default_Table)/sizeof(_NAV_FAC_PF78IOS_T);
    
    /* Find default value by current panel ID. */
    for(ui2_panel_idx=0; ui2_panel_idx<ui2_size_of_def_table; ui2_panel_idx++)
    {
        if(ui4_panel_id==_ar_Fac_PF78IOS_Default_Table[ui2_panel_idx].u4PanelIndex){
            break;
        }
    }
    if(ui2_panel_idx == ui2_size_of_def_table){
        DBG_LOG_PRINT(("FAIL at Line : %d, File : %s\n", __LINE__, __FILE__));
        return TCON_FAIL;
    }

    for(ui1_idx = 0; ui1_idx <= 9; ui1_idx++)
    {
        ui1_reg_address = _PF78IOS_get_reg(ui1_idx);  //ke_vizio_20110330 for clean warning.
        if(ui1_reg_address == PF78IOS_INVALID_REG){
            return TCON_INV_ARG;
        }
        i4_ret = _PF78IOS_set_non_volatile_reg_val(ui1_reg_address,_ar_Fac_PF78IOS_Default_Table[ui2_panel_idx].ui1_val[ui1_idx]);
        TCON_CHK_FAIL(i4_ret);
    }
     
    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: PF78IOS_get_def_val_by_panel_id
* Description: 
* Inputs: 
* Outputs: 
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_get_def_val_by_panel_id(UINT32 ui4_panel_id, UINT8 ui1_reg_num, UINT8 *pui_val_def)
{
    UINT16 ui2_size_of_def_table = sizeof(_ar_Fac_PF78IOS_Default_Table)/sizeof(_NAV_FAC_PF78IOS_T);
    UINT16 ui2_i;

    //ke_vizio_20110330 for clean warning.
    if(ui1_reg_num > 9)  //ui1_val[10];   
    {
        return TCON_INV_ARG;
    }
    
    /* Find default value by current panel ID. */
    for(ui2_i=0; ui2_i<ui2_size_of_def_table; ui2_i++)
    {
        if(ui4_panel_id==_ar_Fac_PF78IOS_Default_Table[ui2_i].u4PanelIndex)
        break;
    }
    if(ui2_i >= ui2_size_of_def_table){
        return TCON_INV_ARG;
    }
    
    /* Get default value */
    *pui_val_def = _ar_Fac_PF78IOS_Default_Table[ui2_i].ui1_val[ui1_reg_num];
    //DBG_LOG_PRINT("ui4_panel_id=%d, Def_val[%d]=%d at line %d of %s\n", ui4_panel_id, ui1_reg_num, *pui_val_def, __LINE__, __FILE__);

    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_tcon_check_and_set_def_val
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
INT32 PF78IOS_check_and_set_def_val(VOID)
{
    DBG_LOG_PRINT(("!!!!%s\n", __func__));
    INT32   i4_ret;
    UINT8   ui1_i;
    UINT8  ui1_val[9] = {0};
    UINT8  ui1_def;
    UINT32 ui4_panel_id;
    BOOL  b_val_is_default = TRUE;
    
    ui4_panel_id = a_cfg_custom_get_cur_panelID();
    
    /* Check if default value are written */
    for(ui1_i=0; ui1_i<9; ui1_i++)
    {
        i4_ret = PF78IOS_get_non_volatile_val( ui1_i, &ui1_val[ui1_i]);
        TCON_CHK_FAIL(i4_ret);
 
        i4_ret = PF78IOS_get_def_val_by_panel_id(ui4_panel_id, ui1_i, &ui1_def);
        TCON_CHK_FAIL(i4_ret);
 
        /* Check if it matches default Gamma value */
        if(ui1_val[ui1_i] != ui1_def)
        {
            b_val_is_default = FALSE;
            DBG_LOG_PRINT(("!!!!%s : b_val_is_default = FALSE\n", __func__));
            break;
        }
    }
    
    /* Check & Write Default Value */
    if(b_val_is_default == FALSE)
    {
        for(ui1_i=0; ui1_i<9; ui1_i++)
        {
            UINT8   ui1_cnt = 0;
            do
            {
                i4_ret = PF78IOS_get_non_volatile_val( ui1_i, &ui1_val[ui1_i]);
                TCON_CHK_FAIL(i4_ret);

                i4_ret = PF78IOS_get_def_val_by_panel_id(ui4_panel_id ,ui1_i, &ui1_def);
                TCON_CHK_FAIL(i4_ret);

                /* Check if it matches default value */
                if(ui1_val[ui1_i] != ui1_def)
                {
                    /* Write default val */
                    ui1_cnt++;
                    i4_ret = PF78IOS_set_non_volatile_val(ui1_i, ui1_def);
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
                    DBG_LOG_PRINT(("Write failed in val[%d] at line %d of %s.\r\n", ui1_i, __LINE__, __FILE__));
                    break;
                }
            }
            while(1);
        }
    }
 
    return i4_ret;
}

/*----------------------------------------------------------------------------
* Name: PF78IOS_load_def
* Description: 
* Inputs:  none
* Outputs: none
* Returns: APP_CFGR_OK/APP_CFGR_INV_ARG/.....
----------------------------------------------------------------------------*/
INT32 PF78IOS_load_temp_def(VOID)
{
    INT32  i4_ret;
    UINT8  ui1_i;	
    UINT32 ui4_panel_id;
    UINT8  ui1_def;
    
    ui4_panel_id = a_cfg_custom_get_cur_panelID();
    
    for(ui1_i=0; ui1_i<9; ui1_i++)
    {
        DBG_LOG_PRINT(("\n\n"));
        #if 0
        i4_ret = PF78IOS_get_reg_val(ui1_i, &ui1_def);
        TCON_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT(("PF78IOS_get_reg_val ui1_def : %d\n", ui1_def));

        i4_ret = PF78IOS_get_non_volatile_val(ui1_i, &ui1_def);
        TCON_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT(("PF78IOS_get_non_volatile_val ui1_def : %d\n", ui1_def));
        #endif
        
        i4_ret = PF78IOS_get_def_val_by_panel_id(ui4_panel_id, ui1_i, &ui1_def);
        TCON_CHK_FAIL(i4_ret);
        
        i4_ret = PF78IOS_set_reg_val(ui1_i, ui1_def);
        TCON_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT(("PF78IOS_set_reg_val ui1_def : %d\n", ui1_def));

        #if 0
        i4_ret = PF78IOS_set_non_volatile_val(ui1_i, ui1_def);
        TCON_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT(("PF78IOS_set_non_volatile_val ui1_def : %d\n", ui1_def));
        
        i4_ret = PF78IOS_get_reg_val(ui1_i, &ui1_def);
        TCON_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT(("PF78IOS_get_reg_val ui1_def : %d\n", ui1_def));

        i4_ret = PF78IOS_get_non_volatile_val(ui1_i, &ui1_def);
        TCON_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT(("PF78IOS_get_non_volatile_val ui1_def : %d\n", ui1_def));
        #endif
        
    }
    return TCON_OK;
}

/*----------------------------------------------------------------------------
* Name: PF78IOS_is_existed
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
BOOL PF78IOS_is_existed(VOID)
{
    UINT8   ui1_buffer[8];
    INT32 i4_ret;

    i4_ret = nav_fac_sif_x_read(PF78IOS_I2C_PORT /*IIC port*/, 270 /*27M/270=100kHz*/,
                               PF78IOS_I2C_SLV_ADDR,
                               1, 0,
                               ui1_buffer, 1);
    if( i4_ret != 0 )
    {
        return FALSE;
    }

    return TRUE;
}

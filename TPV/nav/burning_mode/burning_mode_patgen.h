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
 * $RCSfile: burning_mode_patgen.h,v $
 * $Revision: #1 $
 * $Date: 2015/10/09 $
 * $Author: dtvbm11 $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Chris Kuo $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _BURNING_MODE_PATGEN_H_
#define _BURNING_MODE_PATGEN_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum
{
    BURNING_MODE_PAT_H_LINE = 0,
    BURNING_MODE_PAT_V_LINE,
    BURNING_MODE_PAT_GREEN,
    BURNING_MODE_PAT_BLUE,
    BURNING_MODE_PAT_RED,
    BURNING_MODE_PAT_WHITE,
    BURNING_MODE_PAT_BLACK,
    BURNING_MODE_PAT_MAGENTA,
    BURNING_MODE_PAT_CYAN,
    BURNING_MODE_PAT_YELLOW,
    BURNING_MODE_PAT_W192G,
    BURNING_MODE_PAT_W128G,
    BURNING_MODE_PAT_W64G,
    BURNING_MODE_PAT_W32G,
    
    BURNING_MODE_PAT_END,
} BURNING_MODE_PATTERN_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 burning_mode_ptgn_init_plane (VOID);
extern INT32 burning_mode_ptgn_deinit_plane (VOID);
extern INT32 burning_mode_ptgn_pattern_run (VOID);
extern INT32 burning_mode_ptgn_pattern_stop (VOID);
extern INT32 burning_mode_ptgn_oled_pattern_run (VOID);
extern INT32 burning_mode_ptgn_LG_oled_pattern_run(VOID);
extern INT32 burning_mode_ptgn_pattern_run_old(VOID);
extern INT32 burning_mode_ptgn_vcom_pattern_run(VOID);
extern INT32 burning_mode_ptgn_vcom_pattern_stop(VOID);

#endif /* _BURNING_MODE_PATGEN_H_ */

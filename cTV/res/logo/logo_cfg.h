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
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: logo_cfg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/20 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 3f88970aa8d53b2a36871c1bf4926cd8 $
 *
 * Description:
 *      The file defines the configurable parts for LOGO application.
 *
 *---------------------------------------------------------------------------*/
#ifndef _LOGO_CONFIG_H_
#define _LOGO_CONFIG_H_

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define  LOGO_TIMER_TIMEOUT_DELAY                (2000)

/*
   Main frame.
*/
#define  MAIN_FRM_X                              (0)
#define  MAIN_FRM_Y                              (0)
#define  MAIN_FRM_W                              (1280)		// alex 20120705 1280->960 for true color mode
#define  MAIN_FRM_H                              (720)		// alex 20120705 720->540 for true color mode


/*
   Logo icon.
*/
#define  LOGO_ICON_X                             (0)
#define  LOGO_ICON_Y                             (0)
#define  LOGO_ICON_W                             MAIN_FRM_W
#define  LOGO_ICON_H                             MAIN_FRM_H
#define  LOGO_ICON_ALIGN                         WGL_AS_CENTER_CENTER
#ifdef APP_VIA_LOGO
#define  LOGO_ICON_IMAGE                         h_logo_img_via_logo
#else
#define  LOGO_ICON_IMAGE                         h_logo_img_logo
#endif
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
//static GL_COLOR_T    t_logo_bk_color = { 0, { 0 }, { 0 }, { 0 }};

#endif /* _LOGO_CONFIG_H_ */




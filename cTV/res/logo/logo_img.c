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
 * Copyright (c) 2006 MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: logo_img.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include file
 ----------------------------------------------------------------------------*/

#include "logo/logo.h"
#include "res/logo/logo_img.h"
#include "res/logo/logo_img_8888.i"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifdef APP_VIA_LOGO
WGL_HIMG_TPL_T h_logo_img_via_logo = NULL_HANDLE;
#else
WGL_HIMG_TPL_T h_logo_img_logo = NULL_HANDLE;
#endif

extern INT32 Printf(const CHAR *format, ...);

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
 /*----------------------------------------------------------------------------
 * Name: logo_image_init
 *
 * Description: This API initiates the images of LOGO application.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                   Successful
 *          Any other values    Failed
 ----------------------------------------------------------------------------*/
INT32 logo_image_init (VOID)
{
    INT32    i4_ret;
	
#ifdef APP_VIA_LOGO	
#ifdef APP_VIA_LOGO_DISABLE_UART_UPGRADE
i4_ret = c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
						   & t_logo_img_via_logo_720,
						   & h_logo_img_via_logo);

#else
	i4_ret = c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
							   & t_logo_img_via_logo_QRE,
							   & h_logo_img_via_logo);
#endif

#else
    i4_ret = c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                   & t_logo_img_logo,
                                   & h_logo_img_logo);
#endif

    LOGO_CHK_FAIL (i4_ret, i4_ret);

    return  LOGOR_OK;
}

 /*----------------------------------------------------------------------------
 * Name: logo_image_destroy
 *
 * Description: This API destroys images.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                   Successful
 *          Any other values    Failed
 ----------------------------------------------------------------------------*/
INT32 logo_image_destroy (VOID)
{
#ifdef APP_VIA_LOGO
	if (h_logo_img_via_logo != NULL_HANDLE)
	{
		c_wgl_img_tpl_destroy (h_logo_img_via_logo);
	}
#else
    if (h_logo_img_logo != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy (h_logo_img_logo);
    }
#endif
    return  LOGOR_OK;
}

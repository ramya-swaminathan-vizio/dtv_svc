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
 * $RCSfile: acfg_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_common.h"
#include "c_svctx.h"
#include "c_scc.h"

#include "amb/a_amb.h"
#include "am/a_am.h"

#include "acfg_cust_odm.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "c_rm.h"

#include "INX_factory/INX_d_factory.h" 
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
static BOOL b_is_aud_bypass_on = FALSE;

/*-----------------------------------------------------------------------------
                    Transforms string to enum.
-----------------------------------------------------------------------------*/

PIC_MAP_OBJ_T PIC_Map_Table[] =
{
	{ACFG_CUST_PIC_MODE_VIVID,         "VIVID"},
	{ACFG_CUST_PIC_MODE_BRIGHT,        "BRIGHT"},
	{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,   "CALIBRATED"},
	{ACFG_CUST_PIC_MODE_DARK_ROOM,     "CAL_DARK"},
	{ACFG_CUST_PIC_MODE_GAME,          "GAME"},
	{ACFG_CUST_PIC_MODE_SPORT,         "SPORT"}
};
OPTION_OBJ_T Option_Idx[] = 
{
	{IDX_DISP_BACK_LIGHT			,"IDX_DISP_BACK_LIGHT"},
	{IDX_VID_BRI				    ,"IDX_VID_BRI"},
	{IDX_VID_CNT					,"IDX_VID_CNT"},
	{IDX_VID_SAT					,"IDX_VID_SAT"},
	{IDX_VID_HUE					,"IDX_VID_HUE"},
	{IDX_VID_SHP					,"IDX_VID_SHP"},
	{IDX_CLR_TEMP					,"IDX_CLR_TEMP"},
	{IDX_CUSTOM_CONTRAST_EN			,"IDX_CUSTOM_CONTRAST_EN"},
	{IDX_CUSTOM_SUPER_RESOLUTION	,"IDX_CUSTOM_SUPER_RESOLUTION"},
	{IDX_VID_LOCAL_CONTRAST			,"IDX_VID_LOCAL_CONTRAST"},
	{IDX_CUSTOM_DCR_IDX				,"IDX_CUSTOM_DCR_IDX"},
	{IDX_VID_NR						,"IDX_VID_NR"},
	{IDX_VID_MPEG_NR				,"IDX_VID_MPEG_NR"},
	{IDX_CUSTOM_CONTOUR_SMOOTHING	,"IDX_CUSTOM_CONTOUR_SMOOTHING"},
	{IDX_CUSTOM_GAME_LOW_LATENCY	,"IDX_CUSTOM_GAME_LOW_LATENCY"},
	{IDX_VID_DI_FILM_MODE			,"IDX_VID_DI_FILM_MODE"},
	{IDX_CUST_GAMMA					,"IDX_CUST_GAMMA"},
	{IDX_CUSTOM_GAME_HDR			,"IDX_CUSTOM_GAME_HDR"},
	{IDX_CUSTOM_EN_VIEW_ANGLE		,"IDX_CUSTOM_EN_VIEW_ANGLE"},
	{IDX_CUSTOM_EDGE_ENHANCEMENT    ,"IDX_CUSTOM_EDGE_ENHANCEMENT"}
};

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

#ifdef APP_CFG_CUSTOM_PQ_DEF_TBL
APP_CFG_CUSTOM_PQ_TBL_T at_pq_def_tbl[][PQ_DFT_TBL_MAX_NUM] =
{
{
    //Vivid
    /* Picture mode                     Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_DISP_BACK_LIGHT,  		        100},   /* Backlight */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_BRI,                        50},    /* Brightness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_CNT,                        50},    /* Contrast */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SAT,                        75},    /* Color */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_HUE,                        0},	    /* Tint */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SHP,        		        30},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CLR_TEMP,       		        P_COOL},	/* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_SCR_MODE,    		            0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTRAST_EN,	     	    P_MEDIA},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_SUPER_RESOLUTION,        P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
	{ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EDGE_ENHANCEMENT,        P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_LOCAL_CONTRAST,             P_MEDIA},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_DCR_IDX,    		        P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_NR,                         P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_MPEG_NR,                    P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	    P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_LOW_LATENCY,        P_GAME_LOW_OFF},	  /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_DI_FILM_MODE,               P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUST_GAMMA,	                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_ETOF,				    P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Bright
    /* Picture mode              Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_DISP_BACK_LIGHT,               95},  /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_BRI,                       50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_CNT,                       50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SAT,                       56},  /* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SHP,                       20},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CLR_TEMP,                      P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTRAST_EN,            P_LOW},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_DCR_IDX,                P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTOUR_SMOOTHING,      P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUST_GAMMA,                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_ETOF,                   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Calibrated
    /* Picture mode                   Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_DISP_BACK_LIGHT,              100}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_BRI,                      50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_CNT,                      50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SAT,                      50},	/* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_HUE,                      0},	/* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SHP,                      20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CLR_TEMP,                     P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTRAST_EN,           P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,      P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,      P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_LOCAL_CONTRAST,           P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_DCR_IDX,               P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_NR,                       P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_MPEG_NR,                  P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING,     P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,      P_FILM_MODE_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_DI_FILM_MODE,             P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_ETOF,                  P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Calibrated Dark
    /* Picture mode                 Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_DISP_BACK_LIGHT,  		       85},  /* Backlight */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_BRI,            		   50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_CNT,               		   50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SAT,        			   50},	/* Color */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_HUE,                        0},	/* Tint */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SHP,             		   20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CLR_TEMP,       		       P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,       P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_LOCAL_CONTRAST,            P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUST_GAMMA,	                   P_GAMMA_22},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Game
    /* Picture mode            Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_DISP_BACK_LIGHT,                 90},  /* Backlight */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_BRI,                         50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_CNT,                         50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SAT,                         56}, /* Color */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_HUE,             		    0},	/* Tint */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SHP,                         25},   /* Sharpness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CLR_TEMP,       		            P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_SCR_MODE,    		          0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTRAST_EN,              P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_SUPER_RESOLUTION,         P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EDGE_ENHANCEMENT,         P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_LOCAL_CONTRAST,              P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_DCR_IDX,                  P_OFF},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_NR,                          P_OFF},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_MPEG_NR,                     P_OFF},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTOUR_SMOOTHING,        P_OFF},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_LOW_LATENCY,         P_GAME_LOW_ON},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_DI_FILM_MODE,                P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUST_GAMMA,                      P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_HDR,	                P_GAME_HDR_ON},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_ETOF,                     P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Sport
    /* Picture mode             Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_DISP_BACK_LIGHT,  		       95}, /* Backlight */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_BRI,                       50},  /* Brightness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_CNT,                       50},  /* Contrast */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SAT,       			       50},  /* Color */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SHP,                       25},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CLR_TEMP,       		       P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUST_GAMMA,	                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
}
};

/***********************************************************************************/
/*                        MG306,  H-series pro_pq                                  */
/***********************************************************************************/


APP_CFG_CUSTOM_PQ_TBL_T at_pro_pq_def_tbl [][18] =  //for common pro pq default table
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                                     A cfg index              Default value */

    //Vivid
    {ACFG_CUST_PIC_MODE_VIVID,       IDX_CUST_GAMMA,        2}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_VIVID,       IDX_CLEAR_ACTION,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Bright
    {ACFG_CUST_PIC_MODE_BRIGHT,      IDX_CUST_GAMMA,        2}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_BRIGHT,      IDX_CLEAR_ACTION,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,        2}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CLEAR_ACTION,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated Dark
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_CUST_GAMMA,        3},	/* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_CLEAR_ACTION,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    ///Game
    {ACFG_CUST_PIC_MODE_GAME,         IDX_CUST_GAMMA,        2},	/* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_GAME,        IDX_CLEAR_ACTION,  1}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Sport
    {ACFG_CUST_PIC_MODE_SPORT,       IDX_CUST_GAMMA,        2}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_SPORT,       IDX_CLEAR_ACTION,  0}, /* Reduced Blur */ // 0 : off ; 1 : on
}
};



/***********************************************************************************/
/*                        MG306,  H-series HDR-HLG                                     */
/***********************************************************************************/
APP_CFG_CUSTOM_PQ_TBL_T at_pq_hdr_hlg_def_tbl [][PQ_DFT_TBL_MAX_NUM] =   
{
{
    //Vivid
    /* Picture mode                     Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_DISP_BACK_LIGHT,  		        100},   /* Backlight */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_BRI,                        50},    /* Brightness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_CNT,                        50},    /* Contrast */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SAT,                        75},    /* Color */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_HUE,                        0},	    /* Tint */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SHP,        		        30},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CLR_TEMP,       		        P_COOL},	/* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_SCR_MODE,    		            0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTRAST_EN,	     	    P_MEDIA},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_SUPER_RESOLUTION,        P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EDGE_ENHANCEMENT,        P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_LOCAL_CONTRAST,             P_MEDIA},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_DCR_IDX,    		        P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_NR,                         P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_MPEG_NR,                    P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	    P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_LOW_LATENCY,        P_GAME_LOW_OFF},	  /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_DI_FILM_MODE,               P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUST_GAMMA,	                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_ETOF,				    P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Bright
    /* Picture mode              Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_DISP_BACK_LIGHT,               95},  /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_BRI,                       50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_CNT,                       50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SAT,                       56},  /* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SHP,                       20},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CLR_TEMP,                      P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTRAST_EN,            P_LOW},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_DCR_IDX,                P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTOUR_SMOOTHING,      P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUST_GAMMA,                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_ETOF,                   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Calibrated
    /* Picture mode                   Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_DISP_BACK_LIGHT,              50}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_BRI,                      50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_CNT,                      50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SAT,                      50},	/* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_HUE,                      0},	/* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SHP,                      20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CLR_TEMP,                     P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTRAST_EN,           P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,      P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,      P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_LOCAL_CONTRAST,           P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_DCR_IDX,               P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_NR,                       P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_MPEG_NR,                  P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING,     P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,      P_FILM_MODE_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_DI_FILM_MODE,             P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_ETOF,                  P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Calibrated Dark
    /* Picture mode                 Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_DISP_BACK_LIGHT,  		       50},  /* Backlight */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_BRI,            		   50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_CNT,               		   50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SAT,        			   50},	/* Color */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_HUE,                        0},	/* Tint */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SHP,             		   20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CLR_TEMP,       		       P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,       P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_LOCAL_CONTRAST,            P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUST_GAMMA,	                   P_GAMMA_22},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Game
    /* Picture mode            Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_DISP_BACK_LIGHT,                 90},  /* Backlight */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_BRI,                         50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_CNT,                         50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SAT,                         56}, /* Color */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_HUE,             		    0},	/* Tint */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SHP,                         25},   /* Sharpness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CLR_TEMP,       		            P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_SCR_MODE,    		          0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTRAST_EN,              P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_SUPER_RESOLUTION,         P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EDGE_ENHANCEMENT,         P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_LOCAL_CONTRAST,              P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_DCR_IDX,                  P_OFF},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_NR,                          P_OFF},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_MPEG_NR,                     P_OFF},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTOUR_SMOOTHING,        P_OFF},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_LOW_LATENCY,         P_GAME_LOW_ON},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_DI_FILM_MODE,                P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUST_GAMMA,                      P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_HDR,	                P_GAME_HDR_ON},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_ETOF,                     P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Sport
    /* Picture mode             Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_DISP_BACK_LIGHT,  		       95}, /* Backlight */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_BRI,                       50},  /* Brightness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_CNT,                       50},  /* Contrast */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SAT,       			       50},  /* Color */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SHP,                       25},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CLR_TEMP,       		       P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUST_GAMMA,	                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
}
};

/***********************************************************************************/
/*                        MG306,  H-series Dolby                                   */
/***********************************************************************************/


APP_CFG_CUSTOM_PQ_TBL_T at_pq_dobly_version_def_tbl [][PQ_DFT_TBL_MAX_NUM] =   
{
{
    //Vivid
    /* Picture mode                     Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_DISP_BACK_LIGHT,  		        100},   /* Backlight */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_BRI,                        50},    /* Brightness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_CNT,                        50},    /* Contrast */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SAT,                        75},    /* Color */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_HUE,                        0},	    /* Tint */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SHP,        		        30},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CLR_TEMP,       		        P_COOL},	/* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_SCR_MODE,    		            0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTRAST_EN,	     	    P_MEDIA},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_SUPER_RESOLUTION,        P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EDGE_ENHANCEMENT,        P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_LOCAL_CONTRAST,             P_MEDIA},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_DCR_IDX,    		        P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_NR,                         P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_MPEG_NR,                    P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	    P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_LOW_LATENCY,        P_GAME_LOW_OFF},	  /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_DI_FILM_MODE,               P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUST_GAMMA,	                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_ETOF,				    P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Bright
    /* Picture mode              Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_DISP_BACK_LIGHT,               95},  /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_BRI,                       50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_CNT,                       50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SAT,                       56},  /* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SHP,                       20},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CLR_TEMP,                      P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTRAST_EN,            P_LOW},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_DCR_IDX,                P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTOUR_SMOOTHING,      P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUST_GAMMA,                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_ETOF,                   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Calibrated
    /* Picture mode                   Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_DISP_BACK_LIGHT,              50}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_BRI,                      50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_CNT,                      50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SAT,                      50},	/* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_HUE,                      0},	/* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SHP,                      20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CLR_TEMP,                     P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTRAST_EN,           P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,      P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,      P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_LOCAL_CONTRAST,           P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_DCR_IDX,               P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_NR,                       P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_MPEG_NR,                  P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING,     P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,      P_FILM_MODE_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_DI_FILM_MODE,             P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_ETOF,                  P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Calibrated Dark
    /* Picture mode                 Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_DISP_BACK_LIGHT,  		       50},  /* Backlight */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_BRI,            		   50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_CNT,               		   50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SAT,        			   50},	/* Color */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_HUE,                        0},	/* Tint */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SHP,             		   20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CLR_TEMP,       		       P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,       P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
     {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_LOCAL_CONTRAST,            P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUST_GAMMA,	                   P_GAMMA_22},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Game
    /* Picture mode            Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_DISP_BACK_LIGHT,                 90},  /* Backlight */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_BRI,                         50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_CNT,                         50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SAT,                         56}, /* Color */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_HUE,             		    0},	/* Tint */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SHP,                         25},   /* Sharpness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CLR_TEMP,       		            P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_SCR_MODE,    		          0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTRAST_EN,              P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_SUPER_RESOLUTION,         P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
	{ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EDGE_ENHANCEMENT, 		P_LOW}, 	/* Edge Enhancment */	  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_LOCAL_CONTRAST,              P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_DCR_IDX,                  P_OFF},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_NR,                          P_OFF},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_MPEG_NR,                     P_OFF},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTOUR_SMOOTHING,        P_OFF},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_LOW_LATENCY,         P_GAME_LOW_ON},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_DI_FILM_MODE,                P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUST_GAMMA,                      P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_HDR,	                P_GAME_HDR_ON},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EN_VIEW_ANGLE,            P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_ETOF,                     P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Sport
    /* Picture mode             Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_DISP_BACK_LIGHT,  		       95}, /* Backlight */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_BRI,                       50},  /* Brightness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_CNT,                       50},  /* Contrast */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SAT,       			       50},  /* Color */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SHP,                       25},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CLR_TEMP,       		       P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUST_GAMMA,	                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
}
};

/***********************************************************************************/
/*                        MG306,  H-series HLG                                  */
/***********************************************************************************/


APP_CFG_CUSTOM_PQ_TBL_T at_pq_hlg_def_tbl [][PQ_DFT_TBL_MAX_NUM] =   
{
{
    //Vivid
    /* Picture mode                     Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_DISP_BACK_LIGHT,  		        100},   /* Backlight */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_BRI,                        50},    /* Brightness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_CNT,                        50},    /* Contrast */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SAT,                        75},    /* Color */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_HUE,                        0},	    /* Tint */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_SHP,        		        30},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CLR_TEMP,       		        P_COOL},	/* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_SCR_MODE,    		            0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTRAST_EN,	     	    P_MEDIA},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_SUPER_RESOLUTION,        P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EDGE_ENHANCEMENT,        P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_LOCAL_CONTRAST,             P_MEDIA},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_DCR_IDX,    		        P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_NR,                         P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_MPEG_NR,                    P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	    P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_LOW_LATENCY,        P_GAME_LOW_OFF},	  /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_VID_DI_FILM_MODE,               P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUST_GAMMA,	                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_VIVID,  IDX_CUSTOM_ETOF,				    P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Bright
    /* Picture mode              Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_DISP_BACK_LIGHT,               95},  /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_BRI,                       50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_CNT,                       50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SAT,                       56},  /* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_SHP,                       20},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CLR_TEMP,                      P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTRAST_EN,            P_LOW},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_DCR_IDX,                P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_CONTOUR_SMOOTHING,      P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUST_GAMMA,                    P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_GAME_HDR,	            P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT,  IDX_CUSTOM_ETOF,                   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Calibrated
    /* Picture mode                   Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_DISP_BACK_LIGHT,              50}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_BRI,                      50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_CNT,                      50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SAT,                      50},	/* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_HUE,                      0},	/* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_SHP,                      20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CLR_TEMP,                     P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_SCR_MODE,    		             0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTRAST_EN,           P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,      P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,      P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_LOCAL_CONTRAST,           P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_DCR_IDX,               P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_NR,                       P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_MPEG_NR,                  P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING,     P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,      P_FILM_MODE_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_VID_DI_FILM_MODE,             P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_GAME_HDR,	        	P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,         P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUSTOM_ETOF,                  P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Calibrated Dark
    /* Picture mode                 Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_DISP_BACK_LIGHT,  		       50},  /* Backlight */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_BRI,            		   50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_CNT,               		   50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SAT,        			   50},	/* Color */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_HUE,                        0},	/* Tint */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_SHP,             		   20},	/* Sharpness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CLR_TEMP,       		       P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_SUPER_RESOLUTION,       P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_LOCAL_CONTRAST,            P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUST_GAMMA,	                   P_GAMMA_22},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_DARK_ROOM,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
		
    //Game
    /* Picture mode            Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_DISP_BACK_LIGHT,                 90},  /* Backlight */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_BRI,                         50},	/* Brightness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_CNT,                         50},	/* Contrast */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SAT,                         56}, /* Color */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_HUE,             		    0},	/* Tint */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_SHP,                         25},   /* Sharpness */
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CLR_TEMP,       		            P_WARM},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_SCR_MODE,    		          0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTRAST_EN,              P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_SUPER_RESOLUTION,         P_OFF},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EDGE_ENHANCEMENT,         P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_LOCAL_CONTRAST,              P_OFF},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_DCR_IDX,                  P_OFF},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_NR,                          P_OFF},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_MPEG_NR,                     P_OFF},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_CONTOUR_SMOOTHING,        P_OFF},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_LOW_LATENCY,         P_GAME_LOW_ON},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_GAME,  IDX_VID_DI_FILM_MODE,                P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUST_GAMMA,                      P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_GAME_HDR,	           		P_GAME_HDR_ON},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_EN_VIEW_ANGLE,           P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_GAME,  IDX_CUSTOM_ETOF,                     P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG

    //Sport
    /* Picture mode             Acfg index                     Default value */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_DISP_BACK_LIGHT,  		       95}, /* Backlight */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_BRI,                       50},  /* Brightness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_CNT,                       50},  /* Contrast */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SAT,       			       50},  /* Color */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_HUE,                       0}, /* Tint */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_SHP,                       25},  /* Sharpness */
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CLR_TEMP,       		       P_NORMAL},   /* Color Temperature */    // 0:Warm; 1:Cool; 2:Normal
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_SCR_MODE,    		           0},   /* Picture Aspect */       // 0:Normal
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTRAST_EN,	     	   P_OFF},   /* Blanck Detail */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_SUPER_RESOLUTION,       P_MEDIA},   /* Super Resolution */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EDGE_ENHANCEMENT,       P_LOW},     /* Edge Enhancment */     // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_LOCAL_CONTRAST,            P_LOW},   /* Local Contrast */       // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_DCR_IDX,    		       P_ON},   /* Backlight control */    // 0:off ; 1:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_NR,                        P_LOW},   /* Reduce Signal noise */  // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_MPEG_NR,                   P_LOW},   /* Reduce Block noise */   // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_CONTOUR_SMOOTHING, 	   P_LOW},   /* Contour Smoothing */    // 0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_LOW_LATENCY,       P_GAME_LOW_OFF},   /* Game Low Latency */     // 0:Auto; 1:off; 2:on
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_VID_DI_FILM_MODE,              P_FILM_MODE_ON},   /* Flim mode */            // 0:on ; 1:off
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUST_GAMMA,	                   P_GAMMA_21},   /* Gamma */                // 0:1.8 ; 1:2.0 ; 2:2.1 ; 3:2.2 4:2.4
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_GAME_HDR,	           P_GAME_HDR_OFF},/*Game HDR*/
    {ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_EN_VIEW_ANGLE,          P_ON}, /*Enhanced Viewing Angle*/
    //{ACFG_CUST_PIC_MODE_SPORT,  IDX_CUSTOM_ETOF,				   P_EOTF_AUTO},   /* EOTF */                 // 0:Auto ; 1:SDR ; 2:PQ EOTF ; 3:HLG
}
};


#endif




/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Read PQ Ver from ini
Args: ini_full_path is the path of ini,section is "Version" , 
	  opt is "PQ_DEFAULT_VER",pq_ver is PQ Version.                 
return value : void
-----------------------------------------------------------------------------*/
void read_pq_def_tbl_ver_from_ini(char *ini_full_path,CHAR *pq_ver,UINT8 pq_ver_size)
{
	
	CHAR buf[256] = {0};
	DBG_LOG_PRINT((" yshu : (%s)\n", __FUNCTION__));
	a_cfg_cust_info_get_ini_item_string(ini_full_path,"Version","PQ_DEFAULT_VER","Unknown",buf,256);
	DBG_LOG_PRINT((" yshu : (%s) %s PQ Ver %s \n\n", __FUNCTION__,ini_full_path,buf));
	c_strncpy(pq_ver,buf,256);
	
}

/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Read PQ default tables from ini
Args: ini_full_path is the path of ini,section is picture mode , opt is option.                 
return value : option setting
-----------------------------------------------------------------------------*/
INT32 read_pq_def_table_from_ini(char *ini_full_path,CHAR *section,CHAR *opt)
{
	INT32 val = a_cfg_cust_info_get_ini_item_integer(ini_full_path,section,opt,-1);
	return val;
}


/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Read PQ default tables from ini
Args: ini_full_path is the path of ini,section is picture mode , opt is option.                 
return value : option setting
-----------------------------------------------------------------------------*/
INT16 get_pic_opt_value(char *ini_full_path,UINT8 ui1_pic,UINT16 ui2_option_idx,UINT8 ui1_def_val)
{
	UINT16  ui2_pic_count,ui2_opt_count;
	UINT16  ui2_pic_table_size = sizeof (PIC_Map_Table) / sizeof (PIC_Map_Table[0]);
	UINT16  ui2_option_table_size = sizeof (Option_Idx) / sizeof (Option_Idx[0]);
	//get picture mode
	for(ui2_pic_count = 0; ui2_pic_count < ui2_pic_table_size ; ui2_pic_count++)
	{
		for(ui2_opt_count = 0; ui2_opt_count < ui2_option_table_size ; ui2_opt_count++)
		{
			if(PIC_Map_Table[ui2_pic_count].ui1_pic_mode == ui1_pic && Option_Idx[ui2_opt_count].ui1_option_idx == ui2_option_idx)
			{
				//DBG_LOG_PRINT(("yshu : (%s) %s Picture mode %s , Option %s\n\n", __FUNCTION__,ini_full_path, PIC_Map_Table[ui2_pic_count].c_pic,Option_Idx[ui2_opt_count].c_option));
				return (INT16)read_pq_def_table_from_ini(ini_full_path,PIC_Map_Table[ui2_pic_count].c_pic,Option_Idx[ui2_opt_count].c_option);
			}
		}
	}
	return ui1_def_val;
}

/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Fill pq default table
Args: void                 
return value : void
-----------------------------------------------------------------------------*/
void fill_pq_default_tbl(void)
{
	UINT8	ui1_i;
    UINT8   ui1_pic_mode;
    UINT8   ui1_def_val;
    UINT16  ui2_id;
	CHAR path[64]={0};
	CHAR pq_ver[256]={0};

	c_sprintf(path,PQ_CONFIG_PATH"%s",PQ_DEF_TBL);
	UINT16  ui2_tbl_size = sizeof (at_pq_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
	
    for (ui1_i = 0;ui1_i < ui2_tbl_size; ui1_i ++)
	{
		ui1_pic_mode = (UINT8) at_pq_def_tbl [0][ui1_i].e_pic_mode;
		ui2_id       = (UINT16)at_pq_def_tbl [0][ui1_i].ui2_idx;
		ui1_def_val  = (UINT8) at_pq_def_tbl [0][ui1_i].i2_def;
		INT16 ret_val = get_pic_opt_value(path,ui1_pic_mode,ui2_id,ui1_def_val);
		if(ret_val != ui1_def_val)
		{
			at_pq_def_tbl[0][ui1_i].i2_def = ret_val;
		}
	}

}

/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Fill pq hdr hlg default table
Args: void                 
return value : void
-----------------------------------------------------------------------------*/
void fill_pq_hdr_hlg_default_tbl(void)
{
	UINT8	ui1_i;
    UINT8   ui1_pic_mode;
    UINT8   ui1_def_val;
    UINT16  ui2_id;
	CHAR path[64]={0};
	c_sprintf(path,PQ_CONFIG_PATH"%s",HDR_HLG_DEF_TBL);
	UINT16  ui2_tbl_size = sizeof (at_pq_hdr_hlg_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    for (ui1_i = 0;ui1_i < ui2_tbl_size; ui1_i ++)
	{
		ui1_pic_mode = (UINT8) at_pq_hdr_hlg_def_tbl [0][ui1_i].e_pic_mode;
		ui2_id       = (UINT16)at_pq_hdr_hlg_def_tbl [0][ui1_i].ui2_idx;
		ui1_def_val  = (UINT8) at_pq_hdr_hlg_def_tbl [0][ui1_i].i2_def;
		INT16 ret_val = get_pic_opt_value(path,ui1_pic_mode,ui2_id,ui1_def_val);
		if(ret_val != ui1_def_val)
		{
			at_pq_hdr_hlg_def_tbl[0][ui1_i].i2_def = ret_val;
		}
	}

}


/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Fill pq dv default table
Args: void                 
return value : void
-----------------------------------------------------------------------------*/
void fill_pq_dolby_vision_default_tbl(void)
{
	UINT8	ui1_i;
    UINT8   ui1_pic_mode;
    UINT8   ui1_def_val;
    UINT16  ui2_id;
	CHAR path[64]={0};
	c_sprintf(path,PQ_CONFIG_PATH"%s",DV_DEF_TBL);
	UINT16  ui2_tbl_size = sizeof (at_pq_dobly_version_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    for (ui1_i = 0;ui1_i < ui2_tbl_size; ui1_i ++)
	{
		ui1_pic_mode = (UINT8) at_pq_dobly_version_def_tbl [0][ui1_i].e_pic_mode;
		ui2_id       = (UINT16)at_pq_dobly_version_def_tbl [0][ui1_i].ui2_idx;
		ui1_def_val  = (UINT8) at_pq_dobly_version_def_tbl [0][ui1_i].i2_def;
		INT16 ret_val = get_pic_opt_value(path,ui1_pic_mode,ui2_id,ui1_def_val);
		if(ret_val != ui1_def_val)
		{
			at_pq_dobly_version_def_tbl[0][ui1_i].i2_def = ret_val;
		}
	}

}

/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Fill pq hlg default table
Args: void                 
return value : void
-----------------------------------------------------------------------------*/
void fill_pq_hlg_default_tbl(void)
{
	UINT8	ui1_i;
    UINT8   ui1_pic_mode;
    UINT8   ui1_def_val;
    UINT16  ui2_id;
	CHAR path[64]={0};
	c_sprintf(path,PQ_CONFIG_PATH"%s",HLG_DEF_TBL);
	UINT16  ui2_tbl_size = sizeof (at_pq_hlg_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    for (ui1_i = 0;ui1_i < ui2_tbl_size; ui1_i ++)
	{
		ui1_pic_mode = (UINT8) at_pq_hlg_def_tbl [0][ui1_i].e_pic_mode;
		ui2_id       = (UINT16)at_pq_hlg_def_tbl [0][ui1_i].ui2_idx;
		ui1_def_val  = (UINT8) at_pq_hlg_def_tbl [0][ui1_i].i2_def;
		INT16 ret_val = get_pic_opt_value(path,ui1_pic_mode,ui2_id,ui1_def_val);
		if(ret_val != ui1_def_val)
		{
			at_pq_hlg_def_tbl[0][ui1_i].i2_def = ret_val;
		}
	}

}

/*-----------------------------------------------------------------------------
Author : ys.hu
Descriptor : Fill pq pro default table
Args: void                 
return value : void
-----------------------------------------------------------------------------*/
void fill_pq_pro_default_tbl(void)
{
	UINT8	ui1_i;
    UINT8   ui1_pic_mode;
    UINT8   ui1_def_val;
    UINT16  ui2_id;
	CHAR path[64]={0};
	c_sprintf(path,PQ_CONFIG_PATH"%s",PRO_PQ_DEF_TBL);
	
	UINT16  ui2_tbl_size = sizeof (at_pro_pq_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    for (ui1_i = 0;ui1_i < ui2_tbl_size; ui1_i ++)
	{
		ui1_pic_mode = (UINT8) at_pro_pq_def_tbl [0][ui1_i].e_pic_mode;
		ui2_id       = (UINT16)at_pro_pq_def_tbl [0][ui1_i].ui2_idx;
		ui1_def_val  = (UINT8) at_pro_pq_def_tbl [0][ui1_i].i2_def;
		INT16 ret_val = get_pic_opt_value(path,ui1_pic_mode,ui2_id,ui1_def_val);
		if(ret_val != ui1_def_val)
		{
			at_pro_pq_def_tbl [0][ui1_i].i2_def = ret_val;
		}
	}

}



/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_light_sensor_GAMMA_index
 *
 * Description:
 * 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
extern INT32 a_cfg_custom_set_light_sensor_GAMMA_index( INT16 i2_value)
{
    return APP_CFGR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_check_xvYCC
 *
 * Description:
 * 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
#ifdef APP_CFG_XVYCC_CHECK
extern INT32 a_cfg_custom_check_xvYCC(VOID)
{
    return APP_CFGR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_total_aging_time
 * Description: get total aging time
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_total_aging_time (UINT32*  pui4_aging_time)
{
    SIZE_T  z_size;

    if(pui4_aging_time == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_RSERVE_UI4_0, (VOID*)pui4_aging_time, &z_size);
}

/*----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_total_aging_time
 * Description: set total aging timer
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_total_aging_time (UINT32   ui4_aging_time)
{
    return acfg_set(IDX_CUSTOM_RSERVE_UI4_0, &ui4_aging_time, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_reset_clr_tmp_default
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *         TRUE  - default channel has loaded.
 *         FALSE - default channel has not loaded.
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_reset_clr_tmp_default(UINT8   ui1_mask)
{

    if( ACFG_ACCESS_PRIVATE == ui1_mask)
    {
        /* do odm custom default here */

        return APP_CFGR_NO_ACTION;
    }
    else if( ACFG_ACCESS_FACTORY == ui1_mask)
    {
        /* do odm custom factory default here */
        return APP_CFGR_NO_ACTION;
    }    
    
    return APP_CFGR_NO_ACTION;
}

static INT32 _acfg_cust_odm_set_lcdim(VOID)
{
    INT32 i4_ret = APP_CFGR_OK;
#if 0    
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof (DRV_CUST_OPERATION_INFO_T);
    UINT32 ui4_val = 0;   
    INT16  i2_pic_mode = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);

    ui4_val = (ACFG_CUST_PIC_MODE_VIVID == i2_pic_mode) ? 0 : 1;
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LCDIM_CURVE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = &ui4_val;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT32);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp (DRVT_CUST_DRV, DRV_CUST_COMP_ID,
                            FALSE, ANY_PORT_NUM, 0, &t_op_info, z_size);

    if (i4_ret < 0)
    {
        DBG_LOG_PRINT(("%s return %d\n\n", __FUNCTION__, i4_ret));
    }
#endif
    return i4_ret;
}

static INT32 _acfg_cust_odm_set_blue_stretch(VOID)
{
    INT32 i4_ret = APP_CFGR_OK;
    SM_COMMAND_T    at_sm_cmds[4];
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    INT16  i2_pic_mode = 0;
    UINT16 ui2_blue_stretch = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
    ui2_blue_stretch = (ACFG_CUST_PIC_MODE_VIVID == i2_pic_mode) ? 1 : 0;

    c_memset(at_sm_cmds, 0, sizeof(at_sm_cmds));
    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = s_disp_name;
    at_sm_cmds[2].e_code        = SCC_CMD_CODE_VIDEO_BLUE_STRETCH;
    at_sm_cmds[2].u.ui2_data    = ui2_blue_stretch;
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;
    i4_ret = c_scc_comp_grp_set(at_sm_cmds);
    
    if (i4_ret < 0)
    {
        DBG_LOG_PRINT(("%s return %d\n\n", __FUNCTION__, i4_ret));
    }
    
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_odm_video_update
 *
 * Description: use for odm special acfg video update
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_odm_video_update( UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_NO_ACTION;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    
    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_DISP:
        {
            switch(ui2_cfg_rec)
            {
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                break;
            }
            break;
        }
        case APP_CFG_GRPID_VIDEO:
        {
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_VID_CUSTOM_DCR:
                case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
                {
                    INT16   i2_light_sensor = 0;
                    INT16   i2_dcr_val = 0;
        
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_dcr_val);
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_light_sensor);
                    VIZIO_BACKLIGHT_CONTROL_D_SET(i2_dcr_val);
                    VIZIO_AMBIENT_LIGHT_SENSOR_D_SET(i2_light_sensor);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
                    ACFG_LOG_ON_FAIL(i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_CUSTOM_DIMMING:
                {
                    CHAR    s_active_name [APP_NAME_MAX_LEN+1] = {0}; 
                    UINT16  i2_val = 0;
                    INT16   i2_val_AL;
                    
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), &i2_val_AL);

                    a_am_get_active_app (s_active_name);
                    if (c_strcmp(s_active_name, "wizard") != 0) 
                    {
                        BOOL b_signal_loss = FALSE;

                        /* Only detect the main display is no siganl or not. */
                        i4_ret = c_svctx_is_signal_loss(h_g_acfg_svctx_main, &b_signal_loss);
                        ACFG_LOG_ON_FAIL(i4_ret);
                
                        if(b_signal_loss != TRUE)
                        {
                            i4_ret = a_cfg_custom_update_dimming_idx();
                            ACFG_LOG_ON_FAIL(i4_ret);
                        }
                    }
            
                    i4_ret = a_cfg_custom_get_dimming_idx(&i2_val);
                    ACFG_LOG_ON_FAIL(i4_ret);
                    if (i2_val == 0)
                    {
                        VIZIO_SMART_DIMMING_D_SET(FALSE);    

                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), i2_val_AL);
                        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));
                    }
                    else
                    {
                        //fix no signal backlight to dark
                        BOOL b_signal_loss = FALSE;

                        /* Only detect the main display is no siganl or not. */
                        i4_ret = c_svctx_is_signal_loss(h_g_acfg_svctx_main, &b_signal_loss);
                        ACFG_LOG_ON_FAIL(i4_ret);
                        if(b_signal_loss != TRUE)
                        {
                            VIZIO_SMART_DIMMING_D_SET(TRUE); 
                        }
                        else
                        {                           
                            VIZIO_SMART_DIMMING_D_SET(FALSE);
                        }                       
                    }
                    break;
                }
                case APP_CFG_RECID_VID_LUMA:
                {
                    INT16   i2_adaptive_luma = 0;
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), &i2_adaptive_luma);
                    VIZIO_ADAPTIVE_LUMA_D_SET(i2_adaptive_luma);  /* Off/Low/Medium/Strong/Extend */
                    return APP_CFGR_NO_ACTION; //just send d-interface ,it will pass to acfg_cust_video_update()
                }

                case APP_CFG_RECID_PIC_MODE:
                {
                    INT16           i2_picture_mode;
                    BOOL            b_is_support = FALSE;
                    UINT8           ui1_reduce_blur_value = ACFG_REDUCE_BLUR_OFF;
                    
                    #ifndef APP_C4TV_SUPPORT
					INT16   i2_light_sensor = 0;
                    INT16   i2_dcr_val = 0;
        
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_dcr_val);
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_light_sensor);
                    VIZIO_BACKLIGHT_CONTROL_D_SET(i2_dcr_val);
                    VIZIO_AMBIENT_LIGHT_SENSOR_D_SET(i2_light_sensor);
					#endif
                    
                    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_picture_mode);
                    VIZIO_Picture_mode_D_SET(i2_picture_mode);

                    _acfg_cust_odm_set_lcdim();
                    _acfg_cust_odm_set_blue_stretch();

                    /* Motion Reduced Blur */
                    i4_ret = a_cfg_custom_is_reduce_blur_support(&b_is_support);
                    ACFG_LOG_ON_FAIL(i4_ret);
                    if (b_is_support)
                    {
                        i4_ret = a_cfg_custom_get_reduce_blur(&ui1_reduce_blur_value);
                        ACFG_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_cfg_custom_update_reduce_blur(ui1_reduce_blur_value);
                        ACFG_LOG_ON_FAIL(i4_ret);
                    }

                    return APP_CFGR_NO_ACTION;
                }

                case APP_CFG_RECID_CLR_TEMP:
                {
                    INT16   i2_val = 0;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA), i2_val);
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
                    ACFG_LOG_ON_FAIL(i4_ret);

                    return APP_CFGR_NO_ACTION;
                }

                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_odm_audio_update
 *
 * Description: use for odm special acfg audio update
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_odm_audio_update( UINT16  ui2_id)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_odm_vga_update
 *
 * Description: use for odm special acfg vga update
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_odm_vga_update( UINT16  ui2_id)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_odm_update_all
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NO_ACTION      - No process
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_odm_update_all( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data)
{
    INT32   i4_ret = APP_CFGR_OK;

    switch( e_update_reason)
    {
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: acfg_custom_odm_update_smart_dimming
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_odm_update_smart_dimming(UINT16 ui2_idx)
{
    BOOL        b_support = FALSE;
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = a_cfg_custom_get_is_support_local_dimming(&b_support);    
    if (b_support)
    {
        return VIZIO_SMART_DIMMING_D_SET(ui2_idx);
    }
    else
    {
        return i4_ret;
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_odm_overwrite_pq_default
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NO_ACTION      - No process
 *-----------------------------------------------------------------------------*/
VOID acfg_cust_odm_overwrite_pq_default(VOID)
{
	UINT8	ui1_i;
    UINT8   ui1_pic_mode;
    UINT8   ui1_inp_src;
    UINT8   ui1_def_val;
    UINT16  ui2_id;
    UINT16  ui2_tbl_size = sizeof (at_pq_def_tbl[0]) / sizeof (APP_CFG_CUSTOM_PQ_TBL_T);
    
    //ke_vizio_20160921 modify
    //UINT32 ui4_model_id = 0;
//Read ini file from config dir and fill these tables with it.
	fill_pq_default_tbl();
	fill_pq_hdr_hlg_default_tbl();
	fill_pq_dolby_vision_default_tbl();
	fill_pq_hlg_default_tbl();
	//fill_pq_pro_default_tbl();  //yshu remarks the function that can not work.


    /* PQ default value for all source */
    for (ui1_i = 0;
         ui1_i < ui2_tbl_size;
         ui1_i ++)
    {
        ui1_pic_mode = (UINT8) at_pq_def_tbl [0][ui1_i].e_pic_mode;
        ui2_id       = (UINT16)at_pq_def_tbl [0][ui1_i].ui2_idx;
        ui1_def_val  = (UINT8) at_pq_def_tbl [0][ui1_i].i2_def;
    
        /* Apply PQ settings for each input source */
        for (ui1_inp_src = 0;
             ui1_inp_src < ACFG_CUST_INPUT_GRP_MAX;
             ui1_inp_src ++)
        {
            if((ui1_inp_src * ACFG_PIC_MODE_NUM + ui1_pic_mode) > at_acfg_descr[ui2_id].z_def_size)
            {
                DBG_LOG_PRINT(("[ACFG] ui2_id %d overflow ui1_pic_mode %d ,ui1_def_val %d ui1_i %d ui1_inp_src %d\n", ui2_id,ui1_pic_mode,ui1_def_val,ui1_i,ui1_inp_src));
                continue;
            }
            
            /* Check array index. */
            if (ui2_id >= IDX_MAX)
            {
                DBG_ERROR (("[ACFG]Out of bound ! %s:%d\n", __FILE__, __LINE__));
                break;
            }

            if (acfg_cust_video_is_special_item(ui2_id))
            {
                /* data store by input sorce * picture mode * dynamic range */
                *(((UINT8*)at_acfg_descr[ui2_id].pt_def_value)+
                    ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode) = ui1_def_val;
            }
            else
            {
                *(((UINT8*)at_acfg_descr[ui2_id].pt_def_value)+
                    ui1_inp_src * ACFG_PIC_MODE_NUM + ui1_pic_mode) = ui1_def_val;
            }
        }
    }
}

VOID acfg_cust_odm_overwrite_aq_default(VOID)
{
    UINT8 ui1_audio_output_type;
    
    if(a_cfg_custom_plf_opt_is_analog_aud_out_support(&ui1_audio_output_type) == TRUE)
    {
	    *((UINT8 *)at_acfg_descr[IDX_CUSTOM_ANA_AUD_OUT].pt_def_value) = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;
	}
}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_odm_pre_update_all
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_odm_pre_update_all( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data)
{
    INT32   i4_ret = APP_CFGR_OK;

    switch( e_update_reason)
    {
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
        }

    return i4_ret;
}

BOOL a_cfg_custom_odm_is_lightsensor_support(VOID)
{
#if 1
    DRV_CUST_OPERATION_INFO_T       t_op_info;
    SIZE_T                          z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                          z_size = sizeof(UINT8);
    BOOL                            b_is_support = TRUE;
    INT32                           i4_ret = APP_CFGR_OK;

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_LIGHTSENSOR_SUPPORT;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = &b_is_support;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp(
        DRVT_CUST_DRV,
        DRV_CUST_COMP_ID,
        FALSE,
        ANY_PORT_NUM,
        0,
        &t_op_info,
        &z_size_drv
        );

    return b_is_support;
#else
    return FALSE;
#endif
}

BOOL a_cfg_custom_odm_is_dcr_support(VOID)
{
    return TRUE;
}

BOOL a_cfg_custom_odm_is_emanual_support(VOID)
{
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_aud_srs_bypass
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_aud_srs_bypass(BOOL b_is_on)
{    
	b_is_aud_bypass_on = b_is_on;
	
    c_scc_aud_set_srs_bypass(h_g_acfg_scc_main_aud, b_is_on);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_aud_srs_bypass
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
BOOL a_cfg_custom_get_aud_srs_bypass(VOID)
{
    return b_is_aud_bypass_on;
}

BOOL a_cfg_custom_get_wifi_remote_support(VOID)
{
    return FALSE;
}

BOOL a_cfg_custom_get_wfd_support(VOID)
{
    return FALSE;
}

BOOL a_cfg_custom_get_spdif_support(VOID)
{
    return TRUE;
}

BOOL a_cfg_custom_get_OPTICAL_support(VOID)
{
    return TRUE;
}

BOOL a_cfg_custom_get_lcdim_used(VOID)
{
    return TRUE;
}

INT32 a_cfg_custom_set_rgb_on_off ( UINT8 u1ROnOff,
                                    UINT8 u1GOnOff,
                                    UINT8 u1BOnOff)
{
	
	DRV_CUST_OPERATION_INFO_T	 t_op_info;
	SIZE_T						 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	COLOR_FILTER_INFO_T 		 t_color_filter_info;
	INT32						 i4_ret = APP_CFGR_OK;	

	
	t_color_filter_info.u1ROnOff = u1ROnOff; 
	t_color_filter_info.u1GOnOff = u1GOnOff; 
	t_color_filter_info.u1BOnOff = u1BOnOff;

	/* set operation type */
	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
	t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_COLOR_FILTER;
	t_op_info.u.t_vid_set_info.pv_set_info = &t_color_filter_info;
	t_op_info.u.t_vid_set_info.z_size = sizeof(COLOR_FILTER_INFO_T);
	t_op_info.u.t_vid_set_info.b_store = FALSE; 

	/*get driver value */
	i4_ret = c_rm_set_comp(
							DRVT_CUST_DRV,
							DRV_CUST_COMP_ID,
							FALSE,
							ANY_PORT_NUM,
							0,
							&t_op_info,
							z_size_drv
							);
	if (i4_ret < 0)
	{
		DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
					__FILE__, __FUNCTION__, __LINE__, i4_ret));
	}
	return i4_ret;

}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_rgb_on_off
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_rgb_on_off( UINT8* pu1ROnOff,
   									     UINT8* pu1GOnOff,
   									     UINT8* pu1BOnOff)
{    

	DRV_CUST_OPERATION_INFO_T	 t_op_info;
	SIZE_T								 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	COLOR_FILTER_INFO_T			 t_color_filter_info;
	INT32   						     i4_ret = APP_CFGR_OK;	
	SIZE_T 								 z_size = sizeof(COLOR_FILTER_INFO_T);

	if((pu1ROnOff == NULL)||(pu1GOnOff == NULL)||(pu1BOnOff == NULL))
	 {
		 return APP_CFGR_INV_ARG;
	 }

	c_memset(&t_color_filter_info, 0, sizeof(COLOR_FILTER_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET;
    t_op_info.u.t_vid_get_info.e_vid_type = DRV_CUSTOM_VID_TYPE_COLOR_FILTER;
    t_op_info.u.t_vid_get_info.pv_get_info = &t_color_filter_info;
    t_op_info.u.t_vid_get_info.pz_size = &z_size;

	/*get driver value */
	i4_ret = c_rm_get_comp(
							DRVT_CUST_DRV,
							DRV_CUST_COMP_ID,
							FALSE,
							ANY_PORT_NUM,
							0,
							&t_op_info,
							&z_size_drv
							);
	if (i4_ret < 0)
	{
		DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
					__FILE__, __FUNCTION__, __LINE__, i4_ret));
	}
	
	*pu1ROnOff = t_color_filter_info.u1ROnOff; 
	*pu1GOnOff=  t_color_filter_info.u1GOnOff; 
    *pu1BOnOff =  t_color_filter_info.u1BOnOff;

    return i4_ret;
}

#ifdef APP_AV_COMPONENT_USE_ONE_PORT
INT32 a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId)
{    

    DRV_CUST_OPERATION_INFO_T   t_op_info;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT8);
    INT32                       i4_ret = APP_CFGR_OK;  

	if (pSrcId == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

	/* set operation type */
	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_GetSRCID_COMP_OR_AV;
	t_op_info.u.t_cust_spec_get_info.pv_get_info = pSrcId;
	t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
	
	/*get driver value */
	i4_ret = c_rm_get_comp(
							DRVT_CUST_DRV,
							DRV_CUST_COMP_ID,
							FALSE,
							ANY_PORT_NUM,
							0,
							&t_op_info,
							&z_size_drv
							);
	if (i4_ret < 0)
	{
		DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
					    __FILE__, __FUNCTION__, __LINE__, i4_ret));
	}
    return i4_ret;

}
#endif

INT32 a_cfg_custom_set_pq_exp_color(UINT8 ui1_color, UINT8 ui1_module, UINT8 ui1_value, UINT8 ui1_offset)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    PQ_EXP_COLOR_T               t_pq_exp_color;
    INT32                        i4_ret = APP_CFGR_OK;  


    t_pq_exp_color.u1Color = ui1_color; 
    t_pq_exp_color.u1Module = ui1_module; 
    t_pq_exp_color.u1Value = ui1_value;
    t_pq_exp_color.u1Offset = ui1_offset;

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_EXP_COLOR;
    t_op_info.u.t_vid_set_info.pv_set_info = &t_pq_exp_color;
    t_op_info.u.t_vid_set_info.z_size = sizeof(PQ_EXP_COLOR_T);
    t_op_info.u.t_vid_set_info.b_store = FALSE; 
    
    /*get driver value */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );
    if (i4_ret < 0)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_pq_exp_color
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_pq_exp_color(UINT8* pui1_color, 
									UINT8* pui1_module,
									UINT8* pui1_value,
									UINT8* pui1_offset)
{    

	DRV_CUST_OPERATION_INFO_T	 t_op_info;
	SIZE_T								 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	PQ_EXP_COLOR_T			 			 t_pq_exp_color;
	INT32   						     i4_ret = APP_CFGR_OK;	
	SIZE_T 								 z_size = sizeof(PQ_EXP_COLOR_T);

	if((pui1_color == NULL)||(pui1_module == NULL)||(pui1_value == NULL) ||(pui1_offset == NULL))
	 {
		 return APP_CFGR_INV_ARG;
	 }

	c_memset(&t_pq_exp_color, 0, sizeof(PQ_EXP_COLOR_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET;
    t_op_info.u.t_vid_get_info.e_vid_type = DRV_CUSTOM_VID_TYPE_EXP_COLOR;
    t_op_info.u.t_vid_get_info.pv_get_info = &t_pq_exp_color;
    t_op_info.u.t_vid_get_info.pz_size = &z_size;

	/*get driver value */
	i4_ret = c_rm_get_comp(
							DRVT_CUST_DRV,
							DRV_CUST_COMP_ID,
							FALSE,
							ANY_PORT_NUM,
							0,
							&t_op_info,
							&z_size_drv
							);
	if (i4_ret < 0)
	{
		DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
					__FILE__, __FUNCTION__, __LINE__, i4_ret));
	}

	*pui1_color = t_pq_exp_color.u1Color; 
	*pui1_module=  t_pq_exp_color.u1Module; 
    *pui1_value =  t_pq_exp_color.u1Value;
	*pui1_offset = t_pq_exp_color.u1Offset;
    return i4_ret;

}

#ifdef APP_CUST_REDUCE_BLUR_SUPPORT 
INT32 a_cfg_odm_update_reduce_blur(UINT8 ui1_status)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    if(ui1_status == 0)  // ON => OFF
    {
        
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
        t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_DISP_TYPE_REDUCE_BLUR;
        t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*)&ui1_status;
        t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
        t_op_info.u.t_cust_spec_set_info.b_store = FALSE;
        /*set value to driver*/
        i4_ret = c_rm_set_comp(
                                DRVT_CUST_DRV,
                                DRV_CUST_COMP_ID,
                                FALSE,
                                ANY_PORT_NUM,
                                0,
                                &t_op_info,
                                sizeof(DRV_CUST_OPERATION_INFO_T)
                                );
        ACFG_LOG_ON_FAIL(i4_ret);
        
        c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
        t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_RMB_BOOST_NOTIFY;
        t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*)&ui1_status;
        t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
        t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 
        i4_ret = c_rm_set_comp(
                                DRVT_CUST_DRV,
                                DRV_CUST_COMP_ID,
                                FALSE,
                                ANY_PORT_NUM,
                                0,
                                &t_op_info,
                                sizeof(DRV_CUST_OPERATION_INFO_T)
                                );
        ACFG_LOG_ON_FAIL(i4_ret);
        
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
    }
    else  // OFF => ON
    {
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
        t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_RMB_BOOST_NOTIFY;
        t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*)&ui1_status;
        t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
        t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 
        i4_ret = c_rm_set_comp(
                                DRVT_CUST_DRV,
                                DRV_CUST_COMP_ID,
                                FALSE,
                                ANY_PORT_NUM,
                                0,
                                &t_op_info,
                                sizeof(DRV_CUST_OPERATION_INFO_T)
                                );
        ACFG_LOG_ON_FAIL(i4_ret);
        
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));

        c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
        t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_DISP_TYPE_REDUCE_BLUR;
        t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*)&ui1_status;
        t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
        t_op_info.u.t_cust_spec_set_info.b_store = FALSE;
        /*set value to boost */
        i4_ret = c_rm_set_comp(
                                DRVT_CUST_DRV,
                                DRV_CUST_COMP_ID,
                                FALSE,
                                ANY_PORT_NUM,
                                0,
                                &t_op_info,
                                sizeof(DRV_CUST_OPERATION_INFO_T)
                                );
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}
#endif

INT32 acfg_cust_odm_clear_fac_setting(VOID)
{
    return APP_CFGR_OK;
}


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
 * $RCSfile: acfg_cust_amtran.h,v $
 * $Revision: #2 $
 * $Date: $
 * $Author: $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the header file for Amtran customer cfg. It only contains
 * Amtran's specific PQ/AQ tables. When needed, just include this header file.
 *---------------------------------------------------------------------------*/

#ifndef _ACFG_CUST_AMTRAN_H_
#define _ACFG_CUST_AMTRAN_H_

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
#ifdef APP_CFG_CUSTOM_PQ_DEF_TBL
APP_CFG_CUSTOM_PQ_TBL_T at_pq_def_tbl [][171] =   //Default Model name
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                 Acfg index              Default value */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_DISP_BACK_LIGHT,           85}, /* Backlight */   //Standard
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_SAT,                   63}, /* Color */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_SHP,                    40}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CLR_TEMP,                   1}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_LUMA,                   2}, /* Adaptive Luma /Black Detail */   // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CUSTOM_DIMMING,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CUSTOM_DCR_IDX,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */  //0:off ; 1:low; 2:medim; 3:high  //ke_vizio_20130710 modify
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_GAME_MODE,              0}, /* Game mode */ 

    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_DISP_BACK_LIGHT,           100}, /* Backlight */  //Calibrated
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_SHP,                   20}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CLR_TEMP,                   3}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CUSTOM_DIMMING,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CUSTOM_DCR_IDX,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_GAME_MODE,              0}, /* Game mode */
        
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_DISP_BACK_LIGHT,           65}, /* Backlight */   //Calibrated Dark
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_SHP,                    20}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CLR_TEMP,                   3}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal // Larry 2013 0625, roll back to previous value
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CUSTOM_DIMMING,             1}, /* Backlight Control / Smart Dimming */  //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CUSTOM_DCR_IDX,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high  //ke_vizio_20130710 modify
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_GAME_MODE,              0}, /* Game mode */ 
        
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_DISP_BACK_LIGHT,          100}, /* Backlight */  //Vivid
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_BRI,                    46}, /* Brightness */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_CNT,                   56}, /* Contrast */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_SAT,                   70}, /* Color */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_HUE,                     0}, /* Tint */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_SHP,                   50}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CLR_TEMP,                   1}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_FT,                     1}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CUSTOM_DIMMING,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_GAME_MODE,              0}, /* Game mode */ 

    {ACFG_CUST_PIC_MODE_GAME,       IDX_DISP_BACK_LIGHT,           70}, /* Backlight */  //game
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_SAT,                   63}, /* Color */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_SHP,                   20}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CLR_TEMP,                   2}, /* Color Temperature */ // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_MPEG_NR,                0}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CUSTOM_DIMMING,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_GAME_MODE,              1}, /* Game mode */     // Ben 20141218

    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_DISP_BACK_LIGHT,         100}, /* Backlight */  //computer
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_SAT,                   63}, /* Color */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_SHP,                    0}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CLR_TEMP,                   2}, /* Color Temperature */ // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_MJC_EFFECT,             0}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_MPEG_NR,                0}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CUSTOM_DIMMING,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_GAME_MODE,              0}, /* Game mode */ 

    /******  Non used, but have to reseved *****/
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_DISP_BACK_LIGHT,           80}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_SHP,                    7}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CLR_TEMP,                   2}, /* Color Temperature */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_3D_NR,                  1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_NR,                     1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_MPEG_NR,                1}, /* MPEG NR */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail 
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_LUMA,                   0}, /* Adaptive Luma */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUSTOM_DIMMING,             0}, /* Backlight Control */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUSTOM_LIGHT_SENSOR_IDX,    2}, /* Ambient Light Sensor */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_GAME_MODE,              0}, /* Game mode */ 
    
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_DISP_BACK_LIGHT,           80}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_SHP,                    7}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CLR_TEMP,                   2}, /* Color Temperature */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_3D_NR,                  1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_NR,                     1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_MPEG_NR,                1}, /* MPEG NR */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail 
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_LUMA,                   0}, /* Adaptive Luma */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUSTOM_DIMMING,             0}, /* Backlight Control */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUSTOM_LIGHT_SENSOR_IDX,    2}, /* Ambient Light Sensor */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_GAME_MODE,              0}, /* Game mode */ 
    
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_DISP_BACK_LIGHT,           85}, /* Backlight */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_HUE,                    0}, /* Tint */ 
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_SHP,                    8}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CLR_TEMP,                   2}, /* Color Temperature */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_3D_NR,                  1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_NR,                     1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_MPEG_NR,                1}, /* MPEG NR */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_LUMA,                   0}, /* Adaptive Luma */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUSTOM_DIMMING,             0}, /* Backlight Control */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUSTOM_LIGHT_SENSOR_IDX,    2}, /* Ambient Light Sensor */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_GAME_MODE,              0}, /* Game mode */ 
}
};

APP_CFG_CUSTOM_PQ_TBL_T at_XXX_pq_def_tbl [][171] =   //XXX Custom model
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                 Acfg index              Default value */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_DISP_BACK_LIGHT,           85}, /* Backlight */   //Standard
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_CNT,                   47}, /* Contrast */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_SAT,                   60}, /* Color */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_SHP,                    4}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CLR_TEMP,                   1}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */   // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CUSTOM_DIMMING,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CUSTOM_DCR_IDX,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */  //0:off ; 1:low; 2:medim; 3:high  //ke_vizio_20130710 modify
    {ACFG_CUST_PIC_MODE_STANDARD,       IDX_VID_GAME_MODE,              0}, /* Game mode */ 
        
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_DISP_BACK_LIGHT,          100}, /* Backlight */  //Calibrated
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_CNT,                   47}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_SHP,                    2}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CLR_TEMP,                   3}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CUSTOM_DIMMING,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CUSTOM_DCR_IDX,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,        IDX_VID_GAME_MODE,              0}, /* Game mode */
        
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_DISP_BACK_LIGHT,           55}, /* Backlight */   //Calibrated Dark
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_BRI,                   52}, /* Brightness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_CNT,                   47}, /* Contrast */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_SHP,                     2}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CLR_TEMP,                   3}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CUSTOM_DIMMING,             1}, /* Backlight Control / Smart Dimming */  //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CUSTOM_DCR_IDX,             1}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high  //ke_vizio_20130710 modify
    {ACFG_CUST_PIC_MODE_DARK_ROOM,          IDX_VID_GAME_MODE,              0}, /* Game mode */ 
    
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_DISP_BACK_LIGHT,          100}, /* Backlight */  //Vivid
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_SAT,                   85}, /* Color */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_SHP,                    5}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CLR_TEMP,                   1}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_MPEG_NR,                1}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_FT,                     1}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CUSTOM_DIMMING,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_RETAIL,         IDX_VID_GAME_MODE,              0}, /* Game mode */ 

    {ACFG_CUST_PIC_MODE_GAME,       IDX_DISP_BACK_LIGHT,           95}, /* Backlight */  //game
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_BRI,                   54}, /* Brightness */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_CNT,                   48}, /* Contrast */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_SAT,                   70}, /* Color */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_SHP,                    2}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CLR_TEMP,                   2}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_MPEG_NR,                0}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CUSTOM_DIMMING,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_GAME,       IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_GAME,       IDX_VID_GAME_MODE,              1}, /* Game mode */     // Ben 20141218

    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_DISP_BACK_LIGHT,           98}, /* Backlight */  //computer
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_CNT,                   54}, /* Contrast */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_SAT,                   70}, /* Color */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_SHP,                    0}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CLR_TEMP,                   2}, /* Color Temperature */  // 0:custom; 1:cool; 2:Computer; 3:Normal
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_MJC_EFFECT,             0}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_3D_NR,                  1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_NR,                     1}, /* Noise Reduction / Reduce Signal Noise */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_MPEG_NR,                0}, /* MPEG NR / Reduce Block Noise */  //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_LUMA,                   0}, /* Adaptive Luma /Black Detail */ // 0 off 1 low 2 medium 
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */ // 0:off; 1:Auto
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CUSTOM_DIMMING,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_CUSTOM_LIGHT_SENSOR_IDX,    0}, /* Ambient Light Sensor / Auto Brightness Control */ //0:off ; 1:low; 2:medim; 3:high
    {ACFG_CUST_PIC_MODE_COMPUTER,           IDX_VID_GAME_MODE,              0}, /* Game mode */ 

    /******  Non used, but have to reseved *****/
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_DISP_BACK_LIGHT,           80}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_SHP,                    7}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CLR_TEMP,                   2}, /* Color Temperature */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_3D_NR,                  1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_NR,                     1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_MPEG_NR,                1}, /* MPEG NR */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail 
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_LUMA,                   0}, /* Adaptive Luma */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUSTOM_DIMMING,             0}, /* Backlight Control */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUSTOM_LIGHT_SENSOR_IDX,    2}, /* Ambient Light Sensor */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_VID_GAME_MODE,              0}, /* Game mode */ 
    
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_DISP_BACK_LIGHT,           80}, /* Backlight */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_HUE,                    0}, /* Tint */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_SHP,                    7}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CLR_TEMP,                   2}, /* Color Temperature */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_3D_NR,                  1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_NR,                     1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_MPEG_NR,                1}, /* MPEG NR */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail 
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_LUMA,                   0}, /* Adaptive Luma */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUSTOM_DIMMING,             0}, /* Backlight Control */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUSTOM_LIGHT_SENSOR_IDX,    2}, /* Ambient Light Sensor */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_VID_GAME_MODE,              0}, /* Game mode */ 
    
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_DISP_BACK_LIGHT,           85}, /* Backlight */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_BRI,                   50}, /* Brightness */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_CNT,                   50}, /* Contrast */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_SAT,                   50}, /* Color */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_HUE,                    0}, /* Tint */ 
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_SHP,                    8}, /* Sharpness */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CLR_TEMP,                   2}, /* Color Temperature */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_MJC_EFFECT,             2}, /* Smooth Motion Effect */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_MJC_MODE,               0}, /* Real Cinema Mode */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_3D_NR,                  1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_NR,                     1}, /* Noise Reduction */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_MPEG_NR,                1}, /* MPEG NR */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_FT,                     0}, /* Color Enhancement */ //Larry 20130624, follow HW Joseph's 2013 0621 mail
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_LUMA,                   0}, /* Adaptive Luma */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_DI_FILM_MODE,           1}, /* Film Mode */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUSTOM_DIMMING,             0}, /* Backlight Control */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUSTOM_DCR_IDX,             0}, /* Backlight Control / Smart Dimming */ //0 : off ; 1 : on
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUSTOM_LIGHT_SENSOR_IDX,    2}, /* Ambient Light Sensor */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_VID_GAME_MODE,              0}, /* Game mode */ 
}
};
#endif

APP_CFG_CUSTOM_PQ_TBL_T at_pro_pq_def_tbl [][18] =  //for common pro pq default table
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                                     A cfg index              Default value */
    //Standard
    {ACFG_CUST_PIC_MODE_STANDARD,     IDX_CUST_GAMMA,        3}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_STANDARD,     IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,        3}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated Dark
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Vivid
    {ACFG_CUST_PIC_MODE_RETAIL,       IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_RETAIL,       IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    ///Game
    {ACFG_CUST_PIC_MODE_GAME,         IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_GAME,         IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Computer
    {ACFG_CUST_PIC_MODE_COMPUTER,     IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_COMPUTER,     IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    /******  Non used, but have to reseved *****/
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUST_GAMMA,            3},  /* Gamma */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_REDUCE_BLUR,       0}, /* Reduced Blur */ // 0 : off ; 1 : on
    
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUST_GAMMA,            3},  /* Gamma */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_REDUCE_BLUR,       0}, /* Reduced Blur */ // 0 : off ; 1 : on
    
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUST_GAMMA,            3},  /* Gamma */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_REDUCE_BLUR,       0}, /* Reduced Blur */ // 0 : off ; 1 : on
}
};

APP_CFG_CUSTOM_PQ_TBL_T at_XXX_common_pro_pq_def_tbl [][18] =  //for XXX (MG132) common pro pq default table
{
{   /* ui4_pq_id = 0 */
    /* Picture mode                                     A cfg index              Default value */
    //Standard
    {ACFG_CUST_PIC_MODE_STANDARD,     IDX_CUST_GAMMA,        3}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_STANDARD,     IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_CUST_GAMMA,        2}, /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Calibrated Dark
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_DARK_ROOM,    IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Vivid
    {ACFG_CUST_PIC_MODE_RETAIL,       IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_RETAIL,       IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    ///Game
    {ACFG_CUST_PIC_MODE_GAME,         IDX_CUST_GAMMA,        3},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_GAME,         IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    //Computer
    {ACFG_CUST_PIC_MODE_COMPUTER,     IDX_CUST_GAMMA,        2},    /* Gamma */ // 0(1.8); 1(2.0); 2(2.1); 3(2.2); 4(2.4)
    {ACFG_CUST_PIC_MODE_COMPUTER,     IDX_REDUCE_BLUR,  0}, /* Reduced Blur */ // 0 : off ; 1 : on

    /******  Non used, but have to reseved *****/
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_CUST_GAMMA,            3},  /* Gamma */
    {ACFG_CUST_PIC_MODE_BASKETBALL,     IDX_REDUCE_BLUR,       0}, /* Reduced Blur */ // 0 : off ; 1 : on
    
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_CUST_GAMMA,            3},  /* Gamma */
    {ACFG_CUST_PIC_MODE_BASEBALL,       IDX_REDUCE_BLUR,       0}, /* Reduced Blur */ // 0 : off ; 1 : on
    
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_CUST_GAMMA,            3},  /* Gamma */
    {ACFG_CUST_PIC_MODE_CUSTOM,         IDX_REDUCE_BLUR,       0}, /* Reduced Blur */ // 0 : off ; 1 : on
}
};

#endif /* _ACFG_CUST_AMTRAN_H_ */

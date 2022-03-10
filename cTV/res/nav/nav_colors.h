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
 * $RCSfile: nav_colors.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/7 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 27bad65f0954f3bdb87f20fd6c804eab $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_COLORS_H_
#define _NAV_COLORS_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum
{
    NAV_COLOR_ID_MAIN = 0,             /* main color */
    NAV_COLOR_ID_TEXT,                 /* text color */
    NAV_COLOR_ID_TEXT_COMP,            /* text complementary color */
    NAV_COLOR_ID_TEXT_HLT,             /* text highlighted color */
    NAV_COLOR_ID_HLT,                  /* highlight background */
    NAV_COLOR_ID_CONTENT,              /* content background */
    NAV_COLOR_ID_TRANS,                /* fully transparent */
    NAV_COLOR_ID_BLACK,                /* black color */
    NAV_COLOR_ID_WHITE,                /* white color */
    NAV_COLOR_ID_RED,                  /* red color */
    NAV_COLOR_ID_BLUE,                 /* blue color */
    NAV_COLOR_ID_YELLOW,               /* yellow color */
    NAV_COLOR_ID_ORANGE,               /* orange color */
    NAV_COLOR_ID_POP_FOCUS,            /* for focus PIP/POP frame */
    NAV_COLOR_ID_POP_BLUR,             /* for blur PIP/POP frame */
    NAV_COLOR_ID_8888_BLUE,
    NAV_COLOR_ID_LAST_VALID_ENTRY      /* only for counting purpose */
}   NAV_COLOR_ID_T;

extern GL_COLOR_T t_g_nav_colors[NAV_COLOR_ID_LAST_VALID_ENTRY];
extern GL_COLOR_T t_g_nav_oled_text_color;

#define NAV_COLOR(_color_id)        t_g_nav_colors[_color_id]

#ifdef APP_COLOR_MODE_PALLET
    /* palette mode */
    #define NAV_COLOR_MAIN       { 255, {   0}, {   0}, { 174}}
    #define NAV_COLOR_TEXT       { 255, {   0}, {   0}, { 230}}
    #define NAV_COLOR_TEXT_COMP  { 255, {   0}, {   0}, {   1}}
    #define NAV_COLOR_TEXT_HLT   { 255, {   0}, {   0}, { 247}}
    #define NAV_COLOR_HLT        { 255, {   0}, {   0}, {  63}}
    #define NAV_COLOR_CONTENT    { 255, {   0}, {   0}, { 190}}
    #define NAV_COLOR_TRANS      {   0, {   0}, {   0}, {   0}}
    #define NAV_COLOR_BLACK      { 255, {   0}, {   0}, {   1}}
    #define NAV_COLOR_WHITE      { 255, {   0}, {   0}, { 230}}
    #define NAV_COLOR_ORANGE     { 255, {   0}, {   0}, { 249}}
    #define NAV_COLOR_RED        { 255, {   0}, {   0}, {  49}}
    #define NAV_COLOR_BLUE       { 255, {   0}, {   0}, {   4}}
    #define NAV_COLOR_YELLOW     { 255, {   0}, {   0}, {  61}}
    #define NAV_COLOR_POP_FOCUS  { 255, {   0}, {   0}, { 228}}
    #define NAV_COLOR_POP_BLUR   { 255, {   0}, {   0}, { 229}}
#else
    /* 4444 mode */
    #define NAV_COLOR_MAIN       { 255, {  70}, {  90}, { 140}}
    #define NAV_COLOR_TEXT       { 255, { 255}, { 255}, { 255}}
    #define NAV_COLOR_TEXT_COMP  { 255, {   0}, {   0}, {   0}}
    #define NAV_COLOR_TEXT_HLT   { 255, { 255}, { 200}, { 100}}
    #define NAV_COLOR_HLT        { 255, { 240}, { 240}, {  90}}
    #define NAV_COLOR_CONTENT    { 255, {  80}, { 110}, { 150}}
    #define NAV_COLOR_TRANS      {   0, {   0}, {   0}, {   0}}
    #define NAV_COLOR_BLACK      { 255, {   0}, {   0}, {   0}}
    #define NAV_COLOR_WHITE      { 255, { 255}, { 255}, { 255}}
    #define NAV_COLOR_ORANGE     { 255, { 255}, {  69}, {   0}}
    #define NAV_COLOR_RED        { 255, { 255}, {   0}, {   0}}
    #define NAV_COLOR_BLUE       { 255, {   0}, {   0}, { 255}}
    #define NAV_COLOR_YELLOW     { 255, {   0}, {   0}, {  61}}
    #define NAV_COLOR_POP_FOCUS  { 255, { 255}, { 215}, {   0}}
    #define NAV_COLOR_POP_BLUR   { 255, { 128}, { 128}, { 128}}
    #define NAV_COLOR_GRAY       { 255, { 150}, { 150}, { 150}}
#endif
/*-----------------------------------------------------------------------------
                    customization declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#endif /* _NAV_COLORS_H_ */

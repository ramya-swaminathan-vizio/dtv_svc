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
 * $RCSfile: nav_fac_urc.h,v $
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
#ifndef _NAV_FAC_URC_H_
#define _NAV_FAC_URC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "res/app_util/ui/ui_custom.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
extern WGL_IMG_T t_g_nav_frame_bk_bmp;

#ifdef IMG_960X540_8888_UI
/* URC Dialog ICON*/
#define NAV_FAC_DIALOG_URC_FRAME_X           (UI_THICK_GRID_W) * 50
#define NAV_FAC_DIALOG_URC_FRAME_Y           (UI_THICK_GRID_H) * 32
#define NAV_FAC_DIALOG_URC_FRAME_W           NAV_WIDTH(40)
#define NAV_FAC_DIALOG_URC_FRAME_H           NAV_HEIGHT(40)

/* Dialog Frame*/
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_X   (UI_THICK_GRID_W) * 16
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_Y   (UI_THICK_GRID_H) * 10
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_W   (UI_THICK_GRID_W) * 30
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_H   (UI_THIN_GRID_H) * 7
#else
/* URC Dialog ICON*/
#define NAV_FAC_DIALOG_URC_FRAME_X           (UI_THICK_GRID_W) * 32
#define NAV_FAC_DIALOG_URC_FRAME_Y           (UI_THICK_GRID_H) * 21
#define NAV_FAC_DIALOG_URC_FRAME_W           NAV_WIDTH(40)
#define NAV_FAC_DIALOG_URC_FRAME_H           NAV_HEIGHT(40)

/* Dialog Frame*/
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_X   (UI_THICK_GRID_W) * 10
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_Y   (UI_THICK_GRID_H) * 10
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_W   (UI_THICK_GRID_W) * 20
#define NAV_FAC_DIALOG_DEF_CONTENT_FRAME_H   (UI_THIN_GRID_H) * 7
#endif

/*	//mind 20160509
//@jh 160411 modified for 5581P
#define BTN_FAC_CTC             BTN_ILINK      
#define BTN_FAC_PATTEN          BTN_DVI_3
#define BTN_FAC_BLK 		    BTN_FUNCTION_3
#define BTN_FAC_ARC     		BTN_CUSTOM_6
#define BTN_FAC_LIGHT_SENSOR    BTN_CUSTOM_7
#define BTN_FAC_DCR 		    BTN_CUSTOM_8
#define BTN_FAC_BALANCE_CYCLE   BTN_DVI_4
#define BTN_FAC_VOL_LVL         BTN_SCART_2
#define BTN_FAC_AUDIO           BTN_DVI_1
#define BTN_FAC_BI              BTN_CUSTOM_9
#define BTN_FAC_CSM 		    BTN_SCART
#define BTN_FAC_RST             BTN_DVD
#define BTN_FAC_PREV_PRG        BTN_DVI_2
#define BTN_FAC_TV              BTN_TV
#define BTN_FAC_YPBPR           BTN_COMPONENT
#define BTN_FAC_HDMI	        BTN_HDMI
#define BTN_FAC_VGA             BTN_VGA
#define BTN_FAC_USB             BTN_MEM_CARD
*/

#define BTN_FAC_AV          BTN_CUSTOM_50
#define BTN_FAC_YPBPR       BTN_CUSTOM_51
#define BTN_FAC_HDMI	    BTN_CUSTOM_52
#define BTN_FAC_VOL_BUZZ    BTN_CUSTOM_53
#define BTN_FAC_VOL_MAX     BTN_CUSTOM_54
#define BTN_FAC_VOL_L       BTN_CUSTOM_55
#define BTN_FAC_VOL_R 		BTN_CUSTOM_56
#define BTN_FAC_PREV_SCAN  	BTN_CUSTOM_57
#define BTN_FAC_BLK 		BTN_CUSTOM_58
#define BTN_FAC_DCR 		BTN_CUSTOM_59
#define BTN_FAC_EDID_WP     BTN_CUSTOM_60
#define BTN_FAC_FAC         BTN_CUSTOM_61
#define BTN_FAC_RST         BTN_CUSTOM_62
#define BTN_FAC_CSM 		BTN_CUSTOM_63
#define BTN_FAC_BI          BTN_CUSTOM_64
#define BTN_FAC_CTC         BTN_CUSTOM_65
#define BTN_FAC_POWER       BTN_CUSTOM_66
#define BTN_FAC_SELECT      BTN_CUSTOM_67
#define BTN_FAC_WIFI_SSID   BTN_CUSTOM_68
#define BTN_FAC_DIGIT_0 	BTN_CUSTOM_69
#define BTN_FAC_DIGIT_1  	BTN_CUSTOM_70
#define BTN_FAC_DIGIT_2 	BTN_CUSTOM_71
#define BTN_FAC_DIGIT_3 	BTN_CUSTOM_72
#define BTN_FAC_DIGIT_4 	BTN_CUSTOM_73
#define BTN_FAC_DIGIT_5     BTN_CUSTOM_74
#define BTN_FAC_DIGIT_6     BTN_CUSTOM_75
#define BTN_FAC_DIGIT_7     BTN_CUSTOM_76
#define BTN_FAC_DIGIT_8     BTN_CUSTOM_77
#define BTN_FAC_DIGIT_9     BTN_CUSTOM_78
#define BTN_FAC_MUTE        BTN_CUSTOM_79
#define BTN_FAC_FR          BTN_CUSTOM_80
#define BTN_FAC_S_EFFECT    BTN_CUSTOM_81
#define BTN_FAC_P_EFFECT    BTN_CUSTOM_82
#define BTN_FAC_PREV_PRG    BTN_CUSTOM_83
#define BTN_FAC_PRG_DOWN    BTN_CUSTOM_84
#define BTN_FAC_PRG_UP      BTN_CUSTOM_85
#define BTN_FAC_ANTENNA     BTN_CUSTOM_86
#define BTN_FAC_PATTEN      BTN_CUSTOM_87

#define BTN_PSUDO_AUTO_DONE         BTN_CUSTOM_88
#define BTN_PSUDO_AUTO_FAIL         BTN_CUSTOM_89

#define BTN_FAC_TV          BTN_CUSTOM_90

#define BTN_FAC_VGA         BTN_CUSTOM_91

#define BTN_FAC_PM_TO_STANDARDS     BTN_CUSTOM_92

#define BTN_FAC_SM_TO_STEREO        BTN_CUSTOM_93
#define BTN_FAC_SET_TO_FM           BTN_CUSTOM_94

#define BTN_FAC_AVL_OFF             BTN_CUSTOM_95

#define BTN_FAC_TEST                BTN_CUSTOM_96
#define BTN_FAC_TEST_0              BTN_CUSTOM_97
#define BTN_FAC_USB                 BTN_CUSTOM_98
#define BTN_FAC_LOGO_LED            BTN_CUSTOM_99
#define BTN_FAC_RJ45                BTN_CUSTOM_104
#define BTN_FAC_CLONE               BTN_CUSTOM_105
#define BTN_FAC_RESERVE1            BTN_CUSTOM_106
#define BTN_PSUDO_TCON_MENU         BTN_CUSTOM_107
#define BTN_FAC_VIRGIN_MODE_OFF     BTN_CUSTOM_108
#define BTN_FAC_MENU     			BTN_MENU//BTN_CUSTOM_109
#define BTN_FAC_REGIN     			BTN_CUSTOM_109
#define BTN_FAC_3D_2D     			BTN_CUSTOM_110
#define BTN_FAC_ARC     			BTN_CUSTOM_111
#define BTN_FAC_CI_PLUS     		BTN_CUSTOM_112
#define BTN_FAC_LSR     			BTN_CUSTOM_113
#define BTN_FAC_UP     				BTN_CUSTOM_114
#define BTN_FAC_DOWN     			BTN_CUSTOM_115
#define BTN_FAC_RS232     			BTN_CUSTOM_116
#define BTN_FAC_RESERVE     		BTN_PIP_CH_DOWN//BTN_CUSTOM_117	//mind 20160601	LINK key
#define BTN_FAC_KEYPAD_MENU         BTN_CUSTOM_118
#define BTN_FAC_KEYPAD_POWER        BTN_CUSTOM_119
#define BTN_FAC_HDMI1               BTN_HDMI_1
#define BTN_FAC_HDMI2               BTN_HDMI_2
#define BTN_FAC_HDMI3               BTN_HDMI_3
#define BTN_FAC_HDMI4               BTN_HDMI_4
#define BTN_FAC_RETURN              BTN_RETURN


#define BTN_PESUDO_FAC_MENU    ((UINT32)(PSEUDO_BTN_IDLE+1))
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern VOID nav_fac_urc_key_pre_handler(UINT32 ui4_keystatus,UINT32 * pt_ui4_keycode);
extern INT32 nav_fac_keypad_test(UINT32 ui4_keystatus,UINT32 * pt_ui4_keycode); //ke_vizio_20121018 add

extern INT32 a_TPV_fac_urc_dialog_register(VOID);

extern VOID TPV_custom_rcu_key_pre_handler(NAV_MODEL_T * pt_this,NAV_EVN_T * pt_event);   //ke_vizio_20160429 add
extern BOOL TPV_custom_system_key_cb(UINT32     ui4_evt_code);  //ke_vizio_20160429 add

#ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION
extern VOID TPV_fac_set_WIFI_status(BOOL b_connect);
extern BOOL TPV_fac_get_WIFI_status(VOID);
#endif

#endif /* _NAV_FAC_URC_H_ */


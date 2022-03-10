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
 * $RCSfile: menu_page_relevant_information.c,v $
 * $Revision: #1 $
 * $Date:  $
 * $Author:  $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_sm_video_hdlr.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_svctx.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/menu_dbg.h"

#include "u_scc.h"
#include "c_scc.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                         data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_audio_dbginfo;

static HANDLE_T     h_lb_frm;
static HANDLE_T     h_root_frm;
static HANDLE_T     h_dbginfo_lb;

typedef enum _AUD_DBGINFO_ITEM
{
    AUD_DEC_FW_VERSION = 0,
    ADFV_DECR2VER,
    ADFV_SNDR2VER,
    ADFV_SNDDSPVER,

    AUD_DEC_DECINFO,
    ADD_DEC1TYPE,
    ADD_DEC1CMD,
    ADD_CPUDECODE1,
    ADD_DEC2TYPE,
    ADD_DEC2CMD,
    ADD_CPUDECODE2,
    ADD_INPUTSOURCE,
    ADD_MAINDECID,
    ADD_DECSTATUS,
    ADD_UNSUPPORTTYPE,
    ADD_DECMUTE,
    ADD_DISABLEOUTPUT,
    ADD_R2DMACTRL,
    ADD_STCSELECT,
    ADD_MAINVOL,
    ADD_ASOCVOL,
    ADD_DOLBYDRC,
    ADD_DOLBYDMX,
    ADD_DOLBYTB11,
    ADD_DOLBYRFSIGNAL,
    ADD_DEC1CFG,
    ADD_DEC3CFG,
    ADD_DEC4CFG,

    AUD_DEC_HDMI_RX_INFO,
    ADHRI_NPCMMODE,
    ADHRI_PC,
    ADHRI_BYTEMODE,
    ADHRI_SYNTHRATE,
    ADHRI_112C0C,
    ADHRI_112C40,
    ADHRI_112C48,
    ADHRI_UNSTABLEPROTECT,
    ADHRI_PERIODEVENT,
    ADHRI_MUTEEVENT,
    ADHRI_INPORT,
    ADHRI_WORDLEN,
    ADHRI_CHCCOUNT,
    ADHRI_CHALLOC,

    AUD_DEC_INPUT_CHANNL_MUX,
    ADICM_CH1,
    ADICM_CH2,
    ADICM_CH3,
    ADICM_CH4,
    ADICM_CH5,
    ADICM_CH6,
    ADICM_CH7,
    ADICM_CH8,

    AUD_DEC_INPUT_CHANNL_MUTE,
    ADICMT_CH1,
    ADICMT_CH5,
    ADICMT_CH6,
    ADICMT_CH7,
    ADICMT_CH8,

    AUD_DEC_INPUT_CHANNL_VOLUME,
    ADICV_CH1,
    ADICV_CH5,
    ADICV_CH6,
    ADICV_CH7,
    ADICV_CH8,
    ADICV_SPEAKER,
    ADICV_HP,

    AUD_DEC_OUTPUT_CHANNL_MUTE,
    ADOCMT_AOUT0,
    ADOCMT_AOUT1,
    ADOCMT_AOUT2,
    ADOCMT_AOUT3,
    ADOCMT_I2S,
    ADOCMT_SPDIF,
    ADOCMT_ARC,
    ADOCMT_PCMCAPTURE1,
    ADOCMT_PCMCAPTURE2,
    ADOCMT_PCMCAPTURE3,

    AUD_DEC_OUTPUT_CHANNL_MUX,
    ADOCM_112D50,
    ADOCM_112D52,
    ADOCM_112D54,

    AUD_DEC_OUTPUT_CHANNL_VOLUME,
    ADOCV_AOUT0,
    ADOCV_AOUT1,
    ADOCV_AOUT2,
    ADOCV_AOUT3,
    ADOCV_I2S,
    ADOCV_SPDIF,
    ADOCV_ARC,
    ADOCV_PCMCAPTRUE1,
    ADOCV_PCMCAPTRUE2,
    ADOCV_PCMCAPTRUE3,

    AUD_DEC_DIGITAL_OUTPUT_INFO,
    ADDOI_112D8E,
    ADDOI_MAINDECID,
    ADDOI_HDMINPCMPATH,
    ADDOI_ENCODEOWNER,
    ADDOI_ENCODETYPE,
    ADDOI_ENCODECHLOCK,
    ADDOI_USERSPDIFMODE,
    ADDOI_USERSPDIFMUTE,
    ADDOI_USERSPDIFTRANSCODEC,
    ADDOI_DRVSPDIFNPCMEN,
    ADDOI_DRVSPDIFMODE,
    ADDOI_DRVSPDIFMUTE,
    ADDOI_DRV112C8A,
    ADDOI_USERARCMODE,
    ADDOI_USERARCMOTE,
    ADDOI_USERARCTRANSCODEC,
    ADDOI_DRVARCNPCMEN,
    ADDOI_DRVARCMODE,
    ADDOI_DRVARCMUTE,
    ADDOI_DRV112C5E,
    ADDOI_112E96,
    ADDOI_160396,
    ADDOI_OUTPUTSPK,
    ADDOI_OUTPUTSPDIF,
    ADDOI_OUTPUTARC,
    ADDOI_OUTPUTEARC,
    ADDOI_ISEARCMODE,

    AUD_DEC_EDID_ARC,
    ADEA_CAPDD,
    ADEA_CAPDDP,
    ADEA_CAPATMOS,
    ADEA_CAPDTS,
    ADEA_CAPAAC,
    ADEA_CAPMAT,
    ADEA_CAPDTSHD,
    ADEA_BYTEDD,
    ADEA_BYTEDDP,
    ADEA_BYTEDTS,
    ADEA_BYTEAAC,
    ADEA_BYTEMAT,
    ADEA_BYTEDTSHD,

    AUD_DEC_ENCODE_INFO,
    ADEI_RENDERMODE,
    ADEI_MATENC,
    ADEI_DDPENC,
    ADEI_DDMODE,
    ADEI_TEMPOEN,

    AUD_DEC_INPUT_PORT,
    ADIP_CH1L,
    ADIP_CH1R,
    ADIP_CH2L,
    ADIP_CH2R,
    ADIP_CH3L,
    ADIP_CH3R,
    ADIP_CH4L,
    ADIP_CH4R,
    ADIP_CH5L,
    ADIP_CH5R,
    ADIP_CH6L,
    ADIP_CH6R,
    ADIP_CH7L,
    ADIP_CH7R,
    ADIP_CH8L,
    ADIP_CH8R,

    AUD_DEC_OUTPUT_PORT,
    ADOP_DAC0L,
    ADOP_DAC0R,
    ADOP_DAC1L,
    ADOP_DAC1R,
    ADOP_DAC2L,
    ADOP_DAC2R,
    ADOP_DAC3L,
    ADOP_DAC3R,
    ADOP_I2S0L,
    ADOP_I2S0R,
    ADOP_I2S1L,
    ADOP_I2S1R,
    ADOP_I2S2L,
    ADOP_I2S2R,
    ADOP_SPDIFL,
    ADOP_SPDIFR,
    ADOP_ARCL,
    ADOP_ARCR,
    ADOP_EARCL,
    ADOP_EARCR,

    AUD_DBG_INFO_LASTITEM_NUM
}E_AUD_DBGINFO_ITEM;


UINT32 ui4_item_index[30*10]={0};
//item string
UINT16  aud_debuginfo_item_string_pre[AUD_DBG_INFO_LASTITEM_NUM][32] =
{
    L"FW Version",
    L"DecR2Ver:",
    L"SndR2Ver:",
    L"SndDspVer:",
    L"Decinfo",
    L"Dec1Type:",
    L"Dec1Cmd:",
    L"CpuDecode1:",
    L"Dec2Type:",
    L"Dec2Cmd:",
    L"CpuDecode:",
    L"InputSource:",
    L"MainDecId:",
    L"DecStatus:",
    L"UnSupportType:",
    L"DecMute:",
    L"DisableOutput:",
    L"R2DmaCtrl:",
    L"StcSelect:",
    L"MainVol:",
    L"AsocVol:",
    L"DolbyDrc:",
    L"DolbyDmx:",
    L"DolbyTb11:",
    L"DolbyRfSignal:",
    L"Dec1Cfg:",
    L"Dec3Cfg:",
    L"Dec4Cfg:",
    L"Hdmi Rx Info",
    L"NpcmMode:",
    L"PC:",
    L"ByteMode:",
    L"SynthRate:",
    L"112c0c:",
    L"112c40:",
    L"112c48:",
    L"UnstableProtect:",
    L"PeriodEvent:",
    L"MuteEvent:",
    L"InPort:",
    L"WordLen:",
    L"ChcCount:",
    L"ChAlloc:",
    L"Input Channel Mux",
    L"Ch1:",
    L"Ch2:",
    L"Ch3:",
    L"Ch4:",
    L"Ch5:",
    L"Ch6:",
    L"Ch7:",
    L"Ch8:",
    L"Input Channel Mute",
    L"Ch1:",
    L"Ch5:",
    L"Ch6:",
    L"Ch7:",
    L"Ch8:",
    L"Input Channel Vol",
    L"Ch1:",
    L"Ch5:",
    L"Ch6:",
    L"Ch7:",
    L"Ch8:",
    L"Speaker:",
    L"Hp:",
    L"Output Channel Mute",
    L"Aout0:",
    L"Aout1:",
    L"Aout2:",
    L"Aout3:",
    L"I2S:",
    L"Spdif:",
    L"ARC:",
    L"PcmCapture1:",
    L"PcmCapture2:",
    L"PcmCapture3:",
    L"Output Channel Mux",
    L"112D50:",
    L"112D52:",
    L"112D54:",
    L"Output Channel Vol",
    L"Aout0:",
    L"Aout1:",
    L"Aout2:",
    L"Aout3:",
    L"I2S:",
    L"Spdif:",
    L"ARC:",
    L"PcmCapture1:",
    L"PcmCapture2:",
    L"PcmCapture3:",
    L"Digital Output Info",
    L"112D8E:",
    L"MainDecId:",
    L"HdmiNpcmPath:",
    L"EncodeOwner:",
    L"EncodeType:",
    L"EncodeChLock:",
    L"UserSpdifMode:",
    L"UserSpdifMute:",
    L"UserSpdifTransCodec:",
    L"DrvSpdifNpcmEn:",
    L"DrvSpdifMode:",
    L"DrvSpdifMute:",
    L"Drv112C8A:",
    L"UserArcMode:",
    L"UserArcMute:",
    L"UserArcTransCodec:",
    L"DrvArcNpcmEn:",
    L"DrvArcMode:",
    L"DrvArcMute:",
    L"Drv112C5E:",
    L"112E96:",
    L"160396:",
    L"OutputSpk:",
    L"OutputSpdif:",
    L"OutputArc:",
    L"OutputeArc:",
    L"IsEarcMode:",
    L"EDID Arc",
    L"CapDd:",
    L"CapDdp:",
    L"CapAtmos:",
    L"CapDts:",
    L"CapAac:",
    L"CapMat:",
    L"CapDtsHd:",
    L"ByteDd:",
    L"ByteDdp:",
    L"ByteDts:",
    L"ByteAac:",
    L"ByteMat:",
    L"ByteDtsHd:",
    L"Encode Info",
    L"RenderMode:",
    L"MatEnc:",
    L"DdpEnc:",
    L"DdMode:",
    L"TempoEn:",
    L"Input port",
    L"Ch1L:",
    L"CH1R:",
    L"Ch2L:",
    L"CH2R:",
    L"Ch3L:",
    L"CH3R:",
    L"Ch4L:",
    L"CH4R:",
    L"Ch5L:",
    L"CH5R:",
    L"Ch6L:",
    L"CH6R:",
    L"Ch7L:",
    L"CH7R:",
    L"Ch8L:",
    L"CH8R:",
    L"Output port",
    L"Dac0L:",
    L"Dac0R:",
    L"Dac1L:",
    L"Dac1R:",
    L"Dac2L:",
    L"Dac2R:",
    L"Dac3L:",
    L"Dac3R:",
    L"I2S0L:",
    L"I2S0R:",
    L"I2S1L:",
    L"I2S1R:",
    L"I2S2L:",
    L"I2S2R:",
    L"SpdifL:",
    L"SpdifR:",
    L"ArcL:",
    L"ArcR:",
    L"EarcL:",
    L"EarcR:"
};

UINT16  aud_debuginfo_item_string[AUD_DBG_INFO_LASTITEM_NUM][32] = {0};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

extern INT32 c_scc_aud_get_debug_info(HANDLE_T h_aud, SCC_AUD_DEC_Status_Debug_T* pt_debug_info);

#define ITEM_STRING(x) {\
    c_memset(tmp_str, 0,sizeof(tmp_str));\
    c_memset(w2s_tmp_str, 0,sizeof(w2s_tmp_str));\
    ui4_item_index[ui4_layout_index++] = ui4_index;\
    c_sprintf(tmp_str,"%x",x);\
    c_uc_ps_to_w2s(tmp_str, w2s_tmp_str, c_strlen(tmp_str));\
    c_uc_w2s_strcat(aud_debuginfo_item_string[ui4_index++], w2s_tmp_str);\
}

static INT32 _dbginfo_item_layout( SCC_AUD_DEC_Status_Debug_T st_debug_info)
{
    UINT32 ui4_index = 0;
    UINT32 ui4_layout_index = 0;
    UINT16        w2s_tmp_str[32] = {0};
    CHAR tmp_str[32] = {0};

    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADFV_DECR2VER;
    ITEM_STRING(st_debug_info.stFwVersion.u16DecR2Ver);
    ITEM_STRING(st_debug_info.stFwVersion.u16SndR2Ver);
    ITEM_STRING(st_debug_info.stFwVersion.u32SndDspVer);

    ui4_layout_index += 1;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADD_DEC1TYPE;
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec1Type);
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec1Cmd);
    ITEM_STRING(st_debug_info.stDecInfo.u8CpuDecode1);
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec2Type);
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec2Cmd);
    ITEM_STRING(st_debug_info.stDecInfo.u8CpuDecode2);
    ITEM_STRING(st_debug_info.stDecInfo.u8InputSource);
    ITEM_STRING(st_debug_info.stDecInfo.u8MainDecId);
    ITEM_STRING(st_debug_info.stDecInfo.u8DecStatus);
    ITEM_STRING(st_debug_info.stDecInfo.u8UnSupportType);
    ITEM_STRING(st_debug_info.stDecInfo.u8DecMute);
    ITEM_STRING(st_debug_info.stDecInfo.u8DisableOutput);
    ITEM_STRING(st_debug_info.stDecInfo.u8R2DmaCtrl);
    ITEM_STRING(st_debug_info.stDecInfo.u32StcSelect);
    ITEM_STRING(st_debug_info.stDecInfo.u32MainVol);
    ITEM_STRING(st_debug_info.stDecInfo.u32AsocVol);
    ITEM_STRING(st_debug_info.stDecInfo.u32DolbyDrc);
    ITEM_STRING(st_debug_info.stDecInfo.u32DolbyDmx);
    ITEM_STRING(st_debug_info.stDecInfo.bDolbyTb11);
    ITEM_STRING(st_debug_info.stDecInfo.u8DolbyRfSignal);
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec1Cfg);
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec3Cfg);
    ITEM_STRING(st_debug_info.stDecInfo.u8Dec4Cfg);

    ui4_layout_index = 30;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADHRI_NPCMMODE;
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8NpcmMode);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8PC);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8ByteMode);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8SynthRate);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u16112c0c);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u16112c40);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u16112c48);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u16UnstableProtect);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u16PeriodEvent);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.bMuteEvent);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8InPort);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8WordLen);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8ChcCount);
    ITEM_STRING(st_debug_info.stHdmiRxInfo.u8ChAlloc);

    ui4_layout_index += 1;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADICM_CH1;
    ITEM_STRING(st_debug_info.stInputMux.u8Ch1);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch2);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch3);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch4);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch5);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch6);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch7);
    ITEM_STRING(st_debug_info.stInputMux.u8Ch8);

    ui4_layout_index = 60;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADICMT_CH1;
    ITEM_STRING(st_debug_info.stInputMute.bCh1);
    ITEM_STRING(st_debug_info.stInputMute.bCh5);
    ITEM_STRING(st_debug_info.stInputMute.bCh6);
    ITEM_STRING(st_debug_info.stInputMute.bCh7);
    ITEM_STRING(st_debug_info.stInputMute.bCh8);

    ui4_layout_index += 1;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADICV_CH1;
    ITEM_STRING(st_debug_info.stInputVol.u16Ch1);
    ITEM_STRING(st_debug_info.stInputVol.u16Ch5);
    ITEM_STRING(st_debug_info.stInputVol.u16Ch6);
    ITEM_STRING(st_debug_info.stInputVol.u16Ch7);
    ITEM_STRING(st_debug_info.stInputVol.u16Ch8);
    ITEM_STRING(st_debug_info.stInputVol.u16Speaker);
    ITEM_STRING(st_debug_info.stInputVol.u16Hp);

    ui4_layout_index += 1;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADOCMT_AOUT0;
    ITEM_STRING(st_debug_info.stOutputMute.bAout0);
    ITEM_STRING(st_debug_info.stOutputMute.bAout1);
    ITEM_STRING(st_debug_info.stOutputMute.bAout2);
    ITEM_STRING(st_debug_info.stOutputMute.bAout3);
    ITEM_STRING(st_debug_info.stOutputMute.bI2S);
    ITEM_STRING(st_debug_info.stOutputMute.bSpdif);
    ITEM_STRING(st_debug_info.stOutputMute.bARC);
    ITEM_STRING(st_debug_info.stOutputMute.bPcmCapture1);
    ITEM_STRING(st_debug_info.stOutputMute.bPcmCapture2);
    ITEM_STRING(st_debug_info.stOutputMute.bPcmCapture3);

    ui4_layout_index = 90;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADOCM_112D50;
    ITEM_STRING(st_debug_info.stOutputMux.u16112D50);
    ITEM_STRING(st_debug_info.stOutputMux.u16112D52);
    ITEM_STRING(st_debug_info.stOutputMux.u16112D54);

    ui4_layout_index += 1;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADOCV_AOUT0;
    ITEM_STRING(st_debug_info.stOutputVol.u16Aout0);
    ITEM_STRING(st_debug_info.stOutputVol.u16Aout1);
    ITEM_STRING(st_debug_info.stOutputVol.u16Aout2);
    ITEM_STRING(st_debug_info.stOutputVol.u16Aout3);
    ITEM_STRING(st_debug_info.stOutputVol.u16I2S);
    ITEM_STRING(st_debug_info.stOutputVol.u16Spdif);
    ITEM_STRING(st_debug_info.stOutputVol.u16ARC);
    ITEM_STRING(st_debug_info.stOutputVol.u16PcmCapture1);
    ITEM_STRING(st_debug_info.stOutputVol.u16PcmCapture2);
    ITEM_STRING(st_debug_info.stOutputVol.u16PcmCapture3);

    ui4_layout_index = 120;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADDOI_112D8E;
    ITEM_STRING(st_debug_info.stDigitalInfo.u16112D8E);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8MainDecId);
    ITEM_STRING(st_debug_info.stDigitalInfo.u16HdmiNpcmPath);
    ITEM_STRING(st_debug_info.stDigitalInfo.u16EncodeOwner);
    ITEM_STRING(st_debug_info.stDigitalInfo.u16EncodeType);
    ITEM_STRING(st_debug_info.stDigitalInfo.bEncodeChLock);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8UserSpdifMode);
    ITEM_STRING(st_debug_info.stDigitalInfo.bUserSpdifMute);
    ITEM_STRING(st_debug_info.stDigitalInfo.u32UserSpdifTransCodec);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8DrvSpdifNpcmEn);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8DrvSpdifMode);
    ITEM_STRING(st_debug_info.stDigitalInfo.bDrvSpdifMute);
    ITEM_STRING(st_debug_info.stDigitalInfo.u16Drv112C8A);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8UserArcMode);
    ITEM_STRING(st_debug_info.stDigitalInfo.bUserArcMute);
    ITEM_STRING(st_debug_info.stDigitalInfo.u32UserArcTransCodec);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8DrvArcNpcmEn);
    ITEM_STRING(st_debug_info.stDigitalInfo.u8DrvArcMode);
    ITEM_STRING(st_debug_info.stDigitalInfo.bDrvArcMute);
    ITEM_STRING(st_debug_info.stDigitalInfo.u816Drv112C5E);
    ITEM_STRING(st_debug_info.stDigitalInfo.u16112E96);
    ITEM_STRING(st_debug_info.stDigitalInfo.u16160396);
    ITEM_STRING(st_debug_info.stDigitalInfo.bOutputSpk);
    ITEM_STRING(st_debug_info.stDigitalInfo.bOutputSpdif);
    ITEM_STRING(st_debug_info.stDigitalInfo.bOutputArc);
    ITEM_STRING(st_debug_info.stDigitalInfo.bOutputeArc);
    ITEM_STRING(st_debug_info.stDigitalInfo.bIsEarcMode);

    ui4_layout_index = 150;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADEA_CAPDD;
    ITEM_STRING(st_debug_info.stEdidArc.u8CapDd);
    ITEM_STRING(st_debug_info.stEdidArc.u8CapDdp);
    ITEM_STRING(st_debug_info.stEdidArc.u8CapAtmos);
    ITEM_STRING(st_debug_info.stEdidArc.u8CapDts);
    ITEM_STRING(st_debug_info.stEdidArc.u8CapAac);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteMat);
    ITEM_STRING(st_debug_info.stEdidArc.u8CapDtsHd);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteDd);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteDdp);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteDts);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteAac);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteMat);
    ITEM_STRING(st_debug_info.stEdidArc.u8ByteDtsHd);

    ui4_layout_index += 1;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADEI_RENDERMODE;
    ITEM_STRING(st_debug_info.stEncodeInfo.u8RenderMode);
    ITEM_STRING(st_debug_info.stEncodeInfo.u8MatEnc);
    ITEM_STRING(st_debug_info.stEncodeInfo.u8DdpEnc);
    ITEM_STRING(st_debug_info.stEncodeInfo.u8DdMode);
    ITEM_STRING(st_debug_info.stEncodeInfo.bTempoEn);

    ui4_layout_index = 180;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADIP_CH1L;
    ITEM_STRING(st_debug_info.stInputPort.u32Ch1L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch1R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch2L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch2R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch3L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch3R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch4L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch4R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch5L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch5R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch6L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch6R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch7L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch7R);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch8L);
    ITEM_STRING(st_debug_info.stInputPort.u32Ch8R);

    ui4_layout_index = 210;
    ui4_item_index[ui4_layout_index++] = ui4_index;
    ui4_index = ADOP_DAC0L;
    ITEM_STRING(st_debug_info.stOutPort.u32Dac0L);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac0R);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac1L);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac1R);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac2L);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac2R);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac3L);
    ITEM_STRING(st_debug_info.stOutPort.u32Dac3R);
    ITEM_STRING(st_debug_info.stOutPort.u32I2s0L);
    ITEM_STRING(st_debug_info.stOutPort.u32I2s0R);
    ITEM_STRING(st_debug_info.stOutPort.u32I2s1L);
    ITEM_STRING(st_debug_info.stOutPort.u32I2s1L);
    ITEM_STRING(st_debug_info.stOutPort.u32I2s2L);
    ITEM_STRING(st_debug_info.stOutPort.u32I2s2R);
    ITEM_STRING(st_debug_info.stOutPort.u32SpdifL);
    ITEM_STRING(st_debug_info.stOutPort.u32SpdifR);
    ITEM_STRING(st_debug_info.stOutPort.u32ArcL);
    ITEM_STRING(st_debug_info.stOutPort.u32ArcR);
    ITEM_STRING(st_debug_info.stOutPort.u32EarcL);
    ITEM_STRING(st_debug_info.stOutPort.u32EarcR);

    return MENUR_OK;
}

 static INT32 _dbginfo_msg_proc(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    UINT32          ui4_keycode = (UINT32)pv_param1;
    GL_RECT_T       t_rect = {0};
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    UTF16_T w2s_str[256] = {0};

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_RETURN:
                    /* Let the menu show */
                    c_wgl_set_visibility(h_lb_frm, WGL_SW_HIDE_RECURSIVE);
                    c_wgl_repaint(h_lb_frm,NULL,TRUE);
                    menu_main_set_visibility(TRUE);
                    menu_nav_back();
                    break;
                default:
                break;
            }
        }
        default:
            break;
    }
    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


static INT32 _dbginfo_lb_create( HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_FONT_INFO_T         t_fnt_info;
    WGL_LB_INIT_T                   t_lb_init;
    WGL_LB_COL_INIT_T               at_cols[10];
    UINT8 ui1_i,ui1_col;

    /* Column info */
    for (ui1_i = 0;ui1_i < 10;ui1_i++)
    {
        at_cols[ui1_i].e_col_type          = LB_COL_TYPE_TEXT;
        at_cols[ui1_i].ui1_align           = WGL_AS_LEFT_CENTER;
        at_cols[ui1_i].ui2_width           = 220;// 150 * 10
        at_cols[ui1_i].ui2_max_text_len    = 40;
    }

    /* listbox init struct */
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_NO_SCROLL |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = 30;
    t_lb_init.ui2_elem_size     = 25;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 10;
    t_lb_init.at_cols           = &at_cols;

    SET_RECT_BY_SIZE(&t_rect, 0, 0, 1920, 900);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                NULL,
                                &t_lb_init,
                                NULL ,
                                ph_widget);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size      = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    for(ui1_col=0; ui1_col < t_lb_init.ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_LB_SET_COL_FONT,
                            WGL_PACK((UINT16)ui1_col),
                            WGL_PACK(&t_fnt_info));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    GL_COLOR_T t_frame_color_bk0 = { 210, {   1 }, {   1 }, {   1 }}; // Black
    WGL_COLOR_INFO_T t_color_info = {0};

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable   = t_frame_color_bk0;
    t_color_info.u_color_data.t_standard.t_disable  = t_frame_color_bk0;
    t_color_info.u_color_data.t_standard.t_highlight= t_frame_color_bk0;

    i4_ret = c_wgl_do_cmd( *ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK), /* background color */
                          WGL_PACK(& t_color_info) );

    return MENUR_OK;
}

INT32 _dbginfo_getdata(SCC_AUD_DEC_Status_Debug_T* pst_debug_info)
{
    INT32                     i4_ret = MENUR_OK;
    HANDLE_T                  h_scc = NULL_HANDLE;

    if(pst_debug_info == NULL)
    {
        return MENUR_INV_ARG;
    }

    do
    {
        SM_COMMAND_T                          at_sm_cmds[3];

        if(NULL_HANDLE == h_scc)
        {
             /*scc component for mts operation*/
            at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
            at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
            at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
            at_sm_cmds[2].u.ui4_data = 0;

            i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc);
            MENU_CHK_FAIL(SMR_OK == i4_ret ? MENUR_OK : i4_ret);
        }

        i4_ret = c_scc_aud_get_debug_info(h_scc,pst_debug_info);
        if(i4_ret != SMR_OK)
        {
            DBG_LOG_PRINT(("c_scc_aud_get_debug_info failed\n"));
        }
    }while(0);
    c_scc_comp_close(h_scc);

    return i4_ret;

}

static INT32 _dbginfo_lb_update_data(VOID)
{
    WGL_LB_ITEM_T                   at_items[10];
    INT32           i4_ret = APP_CFGR_OK;
    SCC_AUD_DEC_Status_Debug_T  st_debug_info;
    UINT8 ui4_row = 0;
    UINT8 ui4_col = 0;

    c_memset (&st_debug_info, 0, sizeof(SCC_AUD_DEC_Status_Debug_T));
    c_memset(aud_debuginfo_item_string, 0, sizeof(aud_debuginfo_item_string));
    memcpy(aud_debuginfo_item_string, aud_debuginfo_item_string_pre, sizeof(aud_debuginfo_item_string_pre));
    c_memset(ui4_item_index, 0xFF, sizeof(ui4_item_index));
    _dbginfo_getdata(&st_debug_info);
    _dbginfo_item_layout(st_debug_info);

    for(ui4_col = 0;ui4_col < 30;ui4_col++)
    {
        for(ui4_row = 0;ui4_row < 10;ui4_row++)
        {
            at_items[ui4_row].e_col_type = LB_COL_TYPE_TEXT;
            if(ui4_item_index[ui4_row* 30 + ui4_col] != 0xFF)
            {
                at_items[ui4_row].data.pw2s_text = aud_debuginfo_item_string[ui4_item_index[ui4_row* 30 + ui4_col]];
            }
            else
            {
                at_items[ui4_row].data.pw2s_text = L" ";
            }
        }
        i4_ret = c_wgl_do_cmd(h_dbginfo_lb,
                                WGL_CMD_LB_APPEND_ELEM,
                                WGL_PACK(at_items),
                                NULL);
    }
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,VOID*  pv_create_data)
{
    INT32                   i4_ret;
    GL_RECT_T               t_rect;

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE (& t_rect,0,73,1920,900);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 _dbginfo_msg_proc,
                                 255,
                                 NULL,
                                 0,
                                 &h_lb_frm);

    i4_ret = c_wgl_insert(h_lb_frm, NULL_HANDLE, WGL_INSERT_TOPMOST, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = _dbginfo_lb_create(h_lb_frm, &h_dbginfo_lb);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_frm, WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32           i4_ret;
    i4_ret = menu_main_set_visibility(FALSE);
    _dbginfo_lb_update_data();

    i4_ret = c_wgl_set_visibility(h_lb_frm, WGL_SW_RECURSIVE);
    i4_ret = c_wgl_repaint(h_lb_frm, NULL,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_lb_frm, WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id, MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id, UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

INT32 menu_page_audio_dbginfo_init(VOID)
{
    t_g_menu_page_audio_dbginfo.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_audio_dbginfo.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_audio_dbginfo.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_audio_dbginfo.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_audio_dbginfo.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_audio_dbginfo.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_audio_dbginfo.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

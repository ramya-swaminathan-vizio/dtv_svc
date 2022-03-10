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
 * $RCSfile: wzd_util.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains function prototypes of the utility model of
 *         the Wizard application.
 *
 *---------------------------------------------------------------------------*/

#ifndef _WZD_UTIL_H_
#define _WZD_UTIL_H_

/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "c_sb.h"

#ifdef APP_DVBT_SUPPORT
    #ifndef APP_TWN_SUPPORT
        /* DVBT */
        #include "u_sb_pal_secam_eng.h"
        #ifdef APP_DTMB_SUPPORT
            #include "u_sb_dtmb_eng.h"
            #include "scan_maps/dtmb_scan_maps.h"
        #else
        #include "u_sb_dvb_eng.h"
        #include "scan_maps/scan_maps.h"
        #endif
        
    #else
        /* TWN (NTSC + DVBT) */
        #include "u_sb_ntsc_eng.h"
        #ifdef APP_DTMB_SUPPORT
            #include "u_sb_dtmb_eng.h"
            #include "scan_maps/dtmb_scan_maps.h"
        #else
        #include "u_sb_dvb_eng.h"
        #include "scan_maps/scan_maps.h"
    #endif
    #endif
#else
    /* ATSC */
    #include "u_tuner.h"
    #include "u_sb_ntsc_eng.h"
    #include "u_sb_atsc_eng.h"
    
#ifdef APP_DCR_SUPPORT
    #include "u_sb_oob_eng.h"
#else
    #include "u_sb_cqam_eng.h"
#endif
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/ 
/* Wizard Status stored in ACFG */
#define WZD_STATE_START_SETUP          MAKE_BIT_MASK_8 (0)
#define WZD_STATE_COMPLETE             MAKE_BIT_MASK_8 (1)
#define WZD_STATE_RESUME               MAKE_BIT_MASK_8 (2)
#define WZD_STATE_FIRST_PAGE           MAKE_BIT_MASK_8 (3)
#define WZD_STATE_RESUME_WIFI_RC_PARING  MAKE_BIT_MASK_8 (4)

/* Macros to create/resolve Wizard status values. */
#define WZD_UTIL_SET_STATUS(_state, _idx) (((((UINT16) _idx) << 8) & 0xff00) | (((UINT16) _state) & 0x00ff))

#define WZD_UTIL_GET_STATUS_STATE(_status)     ((UINT8)  (( (UINT16) _status) & 0x00ff))
#define WZD_UTIL_GET_STATUS_IDX(_status)       ((UINT8)  ((((UINT16) _status) & 0xff00) >> 8))

#ifdef APP_DVBT_SUPPORT
    /* no remapping define */
#else

/* Parameters of ATSC AIR */
typedef SB_ATSC_OPEN_DATA_T                     WZD_UTIL_ATSC_AIR_OPEN_DATA_T;
typedef SB_ATSC_SCAN_DATA_T                     WZD_UTIL_ATSC_AIR_SCAN_DATA_T;

#define WZD_UTIL_ATSC_AIR_ENG_NAME              SB_TRSTRL_ENG_NAME
#define WZD_UTIL_ATSC_AIR_SCAN_TYPE             SB_ATSC_SCAN_TYPE_FULL_MODE
 
/* Parameters of ATSC CABLE */
#ifdef APP_DCR_SUPPORT
    typedef SB_OOB_OPEN_DATA_T                  WZD_UTIL_ATSC_CABLE_OPEN_DATA_T;    
    typedef SB_OOB_SCAN_DATA_T                  WZD_UTIL_ATSC_CABLE_SCAN_DATA_T;

    #define WZD_UTIL_ATSC_CABLE_ENG_NAME        SB_DCR_ENG_NAME
    #define WZD_UTIL_ATSC_CABLE_SCAN_TYPE       SB_OOB_SCAN_TYPE_FULL_MODE
    #define WZD_UTIL_ATSC_CABLE_FREQ_PLAN       SB_OOB_FREQ_PLAN_AUTO
#else
    typedef SB_CQAM_OPEN_DATA_T                 WZD_UTIL_ATSC_CABLE_OPEN_DATA_T;    
    typedef SB_CQAM_SCAN_DATA_T                 WZD_UTIL_ATSC_CABLE_SCAN_DATA_T;

    #define WZD_UTIL_ATSC_CABLE_ENG_NAME        SB_CLRQAM_ENG_NAME
    #define WZD_UTIL_ATSC_CABLE_SCAN_TYPE       SB_CQAM_SCAN_TYPE_FULL_MODE    
    #define WZD_UTIL_ATSC_CABLE_FREQ_PLAN       SB_CQAM_FREQ_PLAN_AUTO
#endif
#define WZD_UTIL_MAKE_MOD_BIT_MASK(m)           MAKE_BIT_MASK_32((UINT32)((TUNER_MODULATION_T)(m)))
#define WZD_UTIL_ATSC_CABLE_DEF_MOD_MASK        (WZD_UTIL_MAKE_MOD_BIT_MASK(MOD_QAM_64) | WZD_UTIL_MAKE_MOD_BIT_MASK(MOD_QAM_256) | WZD_UTIL_MAKE_MOD_BIT_MASK(MOD_VSB_8))


/* Parameters of NTSC */
typedef SB_NTSC_OPEN_DATA_T                     WZD_UTIL_NTSC_OPEN_DATA_T;
typedef SB_NTSC_SCAN_DATA_T                     WZD_UTIL_NTSC_SCAN_DATA_T;

#define WZD_UTIL_NTSC_SCAN_TYPE                 SB_NTSC_SCAN_TYPE_FULL_MODE

/* Parameters of NTSC AIR */
#define WZD_UTIL_NTSC_AIR_ENG_NAME              SB_NTSC_TER_ENG_NAME
#define WZD_UTIL_NTSC_AIR_FREQ_PLAN             SB_NTSC_TER_FREQ_PLAN

/* Parameters of NTSC Cable */
#define WZD_UTIL_NTSC_CABLE_ENG_NAME            SB_NTSC_CAB_ENG_NAME
#define WZD_UTIL_NTSC_CABLE_FREQ_PLAN           SB_NTSC_CAB_FREQ_PLAN_AUTO

#endif  /* APP_DVBT_SUPPORT */


/*
   SB Scan Type
*/
#define WZD_SB_SCANNING_AIR         ((UINT16)   0)
#define WZD_SB_SCANNING_CABLE       ((UINT16)   1)
#define WZD_SB_SCANNING_SAT         ((UINT16)   2)

/*
    Scan stop reason
*/
#define WZD_SB_STATUS_WAIT          ((UINT16)   0)
#define WZD_SB_STATUS_COMPLETE      ((UINT16)   1)
#define WZD_SB_STATUS_CANCEL        ((UINT16)   2)
#define WZD_SB_STATUS_ERROR         ((UINT16)   3)
#define WZD_SB_STATUS_SCANNING      ((UINT16)   4)

/*
   SB notification messages.
*/
typedef struct _SB_NFY_MSG_T {
    INT32               i4_atv_ch_num;
    INT32               i4_dtv_ch_num;
    BOOL                b_paint_info;
    INT32               i4_progress;
}   SB_NFY_MSG_T;

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
/*
   Utility model.
*/               
extern INT32  wzd_util_init (VOID);

/*
   Thess functions are provided for scanning.
*/
extern INT32  wzd_util_scan_start  (UINT16   ui2_scanning_type);
#ifdef APP_DVBT_SUPPORT
extern INT32  wzd_util_scan_start_next (VOID);
#endif
extern INT32  wzd_util_scan_cancel (UINT16   ui2_scanning_type);
extern BOOL   wzd_util_is_scanning (UINT16   ui2_scanning_type);

#ifdef APP_DVBT_SUPPORT
#if (defined(APP_ANAS_SUPPORT) && !defined(APP_TWN_SUPPORT))
extern INT32  wzd_util_scan_anas_putback (SB_PAL_SECAM_ANAS_NFY_DATA* pt_anas_nfy_data);
#endif
#endif

extern UINT16 wzd_util_get_scan_status   (VOID);
extern VOID   wzd_util_set_scan_status   (UINT16  ui2_scan_status);


#ifdef APP_ACI_SUPPORT
extern INT32 wzd_util_aci_select    (UINT32 ui4_key_code);
extern INT32 wzd_util_msg_handler   (UINT32 ui4_type, const VOID  * pv_msg, SIZE_T z_msg_len);
extern INT32 wzd_util_get_aci_status(BOOL   *pb_aci_selecting, BOOL *pb_aci_detected);
#endif

#ifdef APP_DVBT_SUPPORT 
extern HANDLE_T wzd_get_sb_hdlr(VOID);
#endif

#endif /* _WZD_UTIL_H_ */

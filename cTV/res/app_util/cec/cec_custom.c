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
 * $RCSfile: cec_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_cecm.h"
#include "c_cecm.h"
#include "c_handle.h"
#include "c_os.h"

#include "nav/nav_common.h"
#include "res/app_util/isl/isl_mlm.h"
#include "res/nav/nav_mlm.h"
#include "res/app_util/cec/cec_custom.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/**
 * @brief   This function gets default device name.
 * @param   ui1_la [in] Device LA.
 * @treurn  A UTF16 string.
 */
UTF16_T* a_cec_custom_get_dev_category_name (UINT8 ui1_la)
{
    UINT32 ui4_mlm_idx = 0;
    switch (ui1_la)
    {
    case CECM_LOG_ADDR_REC_DEV_1:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_REC_1;
        break;
    case CECM_LOG_ADDR_REC_DEV_2:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_REC_2;
        break;
    case CECM_LOG_ADDR_REC_DEV_3:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_REC_3;
        break;
    case CECM_LOG_ADDR_TUNER_1:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_TUNER_1;
        break;
    case CECM_LOG_ADDR_TUNER_2:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_TUNER_2;
        break;
    case CECM_LOG_ADDR_TUNER_3:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_TUNER_3;
        break;
    case CECM_LOG_ADDR_TUNER_4:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_TUNER_4;
        break;
    case CECM_LOG_ADDR_PLAYBACK_DEV_1:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_PLAY_1;
        break;
    case CECM_LOG_ADDR_PLAYBACK_DEV_2:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_PLAY_2;
        break;
    case CECM_LOG_ADDR_PLAYBACK_DEV_3:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_PLAY_3;
        break;
    case CECM_LOG_ADDR_AUD_SYS:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_AUDIO;
        break;
    case CECM_LOG_ADDR_RESERVED_1:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_1;
        break;        
    case CECM_LOG_ADDR_RESERVED_2:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_2;
        break;        
    case CECM_LOG_ADDR_FREE_USE:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_3;
        break;
    case CECM_LOG_ADDR_TV:
        ui4_mlm_idx = MLM_NAV_KEY_CEC_DEV_TV;
        break;    
    default:
        break;
    }
    return MLM_NAV_TEXT(nav_get_mlm_lang_id(), (UINT16)ui4_mlm_idx);
}

/**
 * @brief   This function gets device HDMI port.
 * @param   ui2_pa [in] PA of device.
 * @return  A UTF16 string.
 */
UTF16_T* a_cec_custom_get_hdmi_port(UINT16 ui2_pa)
{   
    UINT16 ui2_hdmi_port_id = (UINT16)((ui2_pa >> 12)-1);
    UINT16 ui2_idx = (UINT16) (MLM_ISL_KEY_MSG_HDMI_0 + ui2_hdmi_port_id);
    
    if (ui2_idx >= MLM_ISL_NUM_KEY)
    {
        ui2_idx = 0;
    }
    return MLM_ISL_TEXT(MLM_ISL_LANG_ENG, ui2_idx);
} 

/**
 * @brief   This function gets LA by idx(priority).
 * @param   ui1_la_idx [in] A UINT8 idx.
 * @treurn  Device LA.
 */
UINT8 a_cec_custom_get_la_by_la_idx(UINT8 ui1_la_idx)
{
    UINT8 ui1_la = CECM_LOG_ADDR_MAX;
    
    switch (ui1_la_idx)
    {
    case (0):
        ui1_la = CECM_LOG_ADDR_REC_DEV_1;
        break;
    case (1):
        ui1_la = CECM_LOG_ADDR_REC_DEV_2;
        break;
    case (2):
        ui1_la = CECM_LOG_ADDR_REC_DEV_3;
        break;
    case (3):
        ui1_la = CECM_LOG_ADDR_PLAYBACK_DEV_1;
        break;
    case (4):
        ui1_la = CECM_LOG_ADDR_PLAYBACK_DEV_2;
        break;
    case (5):
        ui1_la = CECM_LOG_ADDR_PLAYBACK_DEV_3;
        break;      
    case (6):
        ui1_la = CECM_LOG_ADDR_TUNER_1;
        break;
    case (7):
        ui1_la = CECM_LOG_ADDR_TUNER_2;
        break;
    case (8):
        ui1_la = CECM_LOG_ADDR_TUNER_3;
        break;
    case (9):
        ui1_la = CECM_LOG_ADDR_TUNER_4;
        break;
    case (10):
        ui1_la = CECM_LOG_ADDR_AUD_SYS;
        break;
    case (11):
        ui1_la = CECM_LOG_ADDR_RESERVED_1;
        break;
    case (12):
        ui1_la = CECM_LOG_ADDR_RESERVED_2;
        break;
    case (13):
        ui1_la = CECM_LOG_ADDR_FREE_USE;
        break;
    default:
        break;
    }
    return ui1_la;
}    
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/**
 * @brief   This function sorts the device list per customer's specific request.
 * @param   pt_lst      [in/out] A pointer to CEC_DEV_LST_T.
 * @param   e_sort_type [in/out] Custom sort type.
 * @retval  CECR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 a_cec_custom_sort_dev_list (CEC_DEV_LST_T* pt_lst, CEC_CUSTOM_SORT_TYPE_T e_sort_type)
{
    UINT8 ui1_dev_num = 0;  
    UINT8 ui1_la; 
    UINT8 ui1_la_idx;
    CEC_DEV_INFO_T* pt_dev_info;
    CEC_DEV_INFO_T* pt_lst_info;

    if (pt_lst == NULL)
    {
        return CECR_INV_ARG;
    } 

    pt_lst_info = (CEC_DEV_INFO_T*)c_mem_alloc ( sizeof(CEC_DEV_INFO_T) * CEC_DEV_LIST_MAX_NUM);
    if (pt_lst_info == NULL)
    {
        return CECR_FAIL;
    }

    switch (e_sort_type)
    {
    case CEC_CUSTOM_SORT_TYPE_NORMAL:
    {
        for(ui1_la=0;ui1_la<CEC_DEV_LIST_MAX_NUM;ui1_la++)
        {
            pt_dev_info = &pt_lst->at_dev_info[ui1_la];
            if (pt_dev_info->e_la == CECM_LOG_ADDR_MAX)
            {
                continue;
            }
             
            c_memcpy(&pt_lst_info[ui1_dev_num],pt_dev_info,sizeof (CEC_DEV_INFO_T));
            ui1_dev_num++;
        }
        break;
    }    
    case CEC_CUSTOM_SORT_TYPE_MENU:
    {
        for(ui1_la_idx=0;ui1_la_idx<CEC_DEV_LIST_MAX_NUM;ui1_la_idx++)
        {
             ui1_la = a_cec_custom_get_la_by_la_idx(ui1_la_idx);
             if ((ui1_la - 1) >= CEC_DEV_LIST_MAX_NUM)
             {
                 continue;
             }
             pt_dev_info = &pt_lst->at_dev_info[ui1_la-1];
             if (pt_dev_info->e_la == CECM_LOG_ADDR_MAX)
             {
                 continue;
             }
             
             c_memcpy(&pt_lst_info[ui1_dev_num],pt_dev_info,sizeof (CEC_DEV_INFO_T));
             ui1_dev_num++;
        }
        break;
    }    
    case CEC_CUSTOM_SORT_TYPE_EX_INPUT:
    {
        for(ui1_la_idx=0;ui1_la_idx<CEC_DEV_LIST_MAX_NUM;ui1_la_idx++)
        {
            ui1_la = a_cec_custom_get_la_by_la_idx(ui1_la_idx);
            if ((ui1_la - 1) >= CEC_DEV_LIST_MAX_NUM)
            {
                continue;
            }
            pt_dev_info = &pt_lst->at_dev_info[ui1_la-1];
            if (pt_dev_info->e_la == CECM_LOG_ADDR_MAX)
            {
                continue;
            }
            if (ui1_la == CECM_LOG_ADDR_AUD_SYS)
            {
                continue;
            }  
            c_memcpy(&pt_lst_info[ui1_dev_num],pt_dev_info,sizeof (CEC_DEV_INFO_T));
            ui1_dev_num++;
        }
        pt_lst->ui1_dev_num = ui1_dev_num;

        break;
    }    
    default :
        c_mem_free(pt_lst_info);
        return CECR_NO_ACTION;
    }  

    c_memcpy(pt_lst->at_dev_info,pt_lst_info,sizeof (CEC_DEV_INFO_T)*CEC_DEV_LIST_MAX_NUM);
    c_mem_free(pt_lst_info);
    return CECR_OK;
}








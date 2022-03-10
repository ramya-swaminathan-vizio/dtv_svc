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
 * $RCSfile: pic_mode_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"

#include "app_util/a_cfg.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#include "nav/pic_mode/pic_mode.h"
#include "res/nav/pic_mode/pic_mode_custom.h"
#include "res/menu2/menu_mlm.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
#define NAV_PIC_MODE_TITLE_TEXT_IDX            MLM_NAV_KEY_NAV_CHANGE_PIC_MODE
#define NAV_PIC_MODE_TITLE_TEXT(lang, key)     MLM_NAV_TEXT(lang, key);

#define NAV_PIC_MODE_TEXT_IDX                  MLM_MENU_KEY_VID_PIC_MODE_ITEM
#define NAV_PIC_MODE_TEXT(lang, key)           MLM_MENU_TEXT(lang, key)

static UINT16 _nav_aui2_idx_map[ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM] = {0,1,2,3,4,5};

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Mapping NAV mlm to MENU mlm
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT8 _nav_get_mlm_lang_id_and_trans_to_menu(VOID)
{
#ifndef APP_MLM_S639_TO_LANGIDX_SUPPORT
	/* Nav MLM Mapping to Menu MLM */

	/*	NAV 		  MENU
	   0 ENG		 0 ENG
	   1 FRE		 1 ESL
	   2 SPA		 2 FRA
	   3 KOA
	*/

	UINT8		ui1_id;

	ui1_id	  = nav_get_mlm_lang_id();

	if(ui1_id == 0)
	{
		return 0;
	}
	else if(ui1_id == 1)
	{
		return 2;
	}
	else if(ui1_id == 2)
	{
		return 1;
	}
	else if(ui1_id == 3)
	{
		return 0;
	}
	else
	{
		/* unhandled nav lang_id */
		return 0;
	}
#else /* APP_MLM_S639_TO_LANGIDX_SUPPORT */

	ISO_639_LANG_T s639_lang;
	a_cfg_get_gui_lang(s639_lang);
	return (UINT8) mlm_menu_s639_to_langidx(s639_lang);

#endif

}

/*----------------------------------------------------------------------------
 * Name: _cvt_acfg_idx_2_list_box_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 _cvt_acfg_idx_2_list_box_idx(UINT16 ui2_idx)
{
	UINT16 ui2_i = 0;
	UINT16 ui2_list_idx = ui2_idx; /*default value*/

	for (ui2_i = 0; ui2_i < ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM; ui2_i++)
	{
		if (_nav_aui2_idx_map[ui2_i] == ui2_idx)
		{
			ui2_list_idx = ui2_i;
			break;
		}
	}

	return ui2_list_idx;
}

/*----------------------------------------------------------------------------
 * Name: _cvt_list_box_idx_2_acfg_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 _cvt_list_box_idx_2_acfg_idx(UINT16 ui2_idx)
{
	return _nav_aui2_idx_map[ui2_idx];
}

/*----------------------------------------------------------------------------
 * Name: _nav_pic_mode_custom_get_elem_text
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_pic_mode_custom_get_elem_text(
						UINT16	  ui2_idx,	 /* in */
						UTF16_T*  w2s_str,	 /* out */
						SIZE_T	  z_len)
{

	BOOL    b_3d_mode_playing =  FALSE;
    BOOL    b_is_exist = FALSE;
    BOOL    b_is_chg = FALSE;

	ui2_idx = _cvt_list_box_idx_2_acfg_idx(ui2_idx);

	if (b_3d_mode_playing)
	{
		if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
		{
			c_uc_w2s_strncpy(w2s_str, NAV_PIC_MODE_TEXT(_nav_get_mlm_lang_id_and_trans_to_menu(), ((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1) + ui2_idx)), z_len-1);
			w2s_str[z_len - 1] = 0;
		}
		else
		{
			CHAR	s_pic_mode_name[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = {0};

            a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx, &b_is_exist);

			if (b_is_exist)
			{
				a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name, APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN);
				c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN);
				w2s_str[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN -1] = 0;
			}

			else
			{
				c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
				w2s_str[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN-1] = 0;
			}
		}
	}
	else
	{
		if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
		{
			c_uc_w2s_strncpy(w2s_str, NAV_PIC_MODE_TEXT(_nav_get_mlm_lang_id_and_trans_to_menu(), ((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1) + ui2_idx)), z_len-1);
			w2s_str[z_len - 1] = 0;
		}
		else
		{
			CHAR	s_pic_mode_name[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = {0};

            a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx, &b_is_exist);

			if (b_is_exist)
			{
				a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name, APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN);
				c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN);
				w2s_str[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN-1] = 0;
			}
			else
			{
				c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
				w2s_str[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN-1] = 0;
			}
		}
	}

    a_cfg_get_preset_pic_mode_chg_status(ui2_idx, &b_is_chg);
    if (b_is_chg && ((ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM) || b_is_exist))
    {
        c_uc_w2s_strncat(w2s_str, L"*", 1);
        w2s_str[z_len - 1] = 0;
    }

}


/*----------------------------------------------------------------------------
 * Name: nav_pic_mode_get_elem_text_for_demo
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_pic_mode_get_elem_text_for_demo(
						UINT16	  ui2_idx,	 /* in */
						UTF16_T*  w2s_str)   /* out */
{

	BOOL    b_3d_mode_playing =  FALSE;
    BOOL    b_is_exist = FALSE;
    BOOL    b_is_chg = FALSE;
	SIZE_T	z_len = 0;

	if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
	{
		z_len = 64;
	}
	else
	{
		z_len = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;//APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;
	}

	ui2_idx = _cvt_list_box_idx_2_acfg_idx(ui2_idx);

	if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
	{
		c_uc_w2s_strncpy(w2s_str, NAV_PIC_MODE_TEXT(0, ((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1) + ui2_idx)), z_len-1);
		w2s_str[z_len - 1] = 0;
	}
	else
	{
		CHAR	s_pic_mode_name[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = {0};

        a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx, &b_is_exist);

		if (b_is_exist)
		{
			a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name, APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN);
			c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN);
			w2s_str[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN-1] = 0;
		}
		else
		{
			c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
			w2s_str[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN-1] = 0;
		}
	}

    a_cfg_get_preset_pic_mode_chg_status(ui2_idx, &b_is_chg);
    if (b_is_chg && ((ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM) || b_is_exist))
    {
        c_uc_w2s_strncat(w2s_str, L"*", 1);
        w2s_str[z_len - 1] = 0;
    }

}

/*----------------------------------------------------------------------------
 * Name: nav_pic_mode_custom_get_title
 *
 * Description: Return the pw2s_text of title.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UTF16_T* nav_pic_mode_custom_get_title(VOID)
{
	UINT16 ui2_nav_pic_mode_title_id = NAV_PIC_MODE_TITLE_TEXT_IDX;
    UINT8 ui1_type = a_acfg_cust_get_video_type();

    switch (ui1_type)
    {
        case SCC_VID_PQ_HDR10:
            ui2_nav_pic_mode_title_id = MLM_NAV_KEY_NAV_PIC_MODE_HDR10_ITEM;
            break ;
        case SCC_VID_PQ_HDR10PLUS:
            ui2_nav_pic_mode_title_id = MLM_NAV_KEY_NAV_PIC_MODE_HDR10_PLUS_ITEM;
            break ;
        case SCC_VID_PQ_HLG:
            ui2_nav_pic_mode_title_id = MLM_NAV_KEY_NAV_PIC_MODE_HLG_ITEM;
            break ;
        case SCC_VID_PQ_DOVI:
        case SCC_VID_PQ_SDR:
        default :
            break ;
    }
	return (UTF16_T*) NAV_PIC_MODE_TITLE_TEXT(nav_get_mlm_lang_id(),
                                          ui2_nav_pic_mode_title_id);

}

/*----------------------------------------------------------------------------
 * Name: nav_pic_mode_custom_get_index_text
 *
 * Description: Give index, return the pw2s_text of that index.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

UTF16_T* nav_pic_mode_custom_get_index_text(UINT16     ui2_idx)
{
    return (UTF16_T*) NAV_PIC_MODE_TEXT(_nav_get_mlm_lang_id_and_trans_to_menu(),
                                        (UINT16)(NAV_PIC_MODE_TEXT_IDX + 1 + ui2_idx));
}

/*----------------------------------------------------------------------------
 * Name: nav_pic_mode_custom_get_index_text_ex
 *
 * Description: Give index, return the pw2s_text of that index.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_pic_mode_custom_get_index_text_ex (UINT16 ui2_idx, UTF16_T* pw2s_text)
{
	SIZE_T	  z_len = 0;

	if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
	{
		z_len = 64;
	}
	else
	{
		z_len = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;//APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;
	}

	_nav_pic_mode_custom_get_elem_text(ui2_idx, pw2s_text, z_len);

    return;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_pic_mode_idx
 *
 * Description: Set picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID nav_pic_mode_custom_set_vid_pic_mode_idx(UINT16 ui2_idx)
{
	/* get remap value */
	ui2_idx = _cvt_list_box_idx_2_acfg_idx(ui2_idx);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 (INT16)ui2_idx);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_pic_mode_idx
 *
 * Description: Return the index of picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 nav_pic_mode_custom_get_vid_pic_mode_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);

	i2_val =(INT16) _cvt_acfg_idx_2_list_box_idx((UINT16)i2_val);

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Get picture mode numbers
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 nav_pic_mode_custom_get_vid_pic_mode_numbers()
{
    UINT16	ui2_count = 0;
	UINT16	ui2_i = 0;
    BOOL    b_is_exist = FALSE;

    for (ui2_i = 0; ui2_i < ACFG_CUST_SET_PIC_MODE_NUM; ui2_i++)
    {
        a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui2_i, &b_is_exist);
        if (b_is_exist)
        {
            _nav_aui2_idx_map[ACFG_PRE_SET_PIC_MODE_NUM + ui2_count] = ui2_i + ACFG_PRE_SET_PIC_MODE_NUM;
        	ui2_count++;
        }
    }
	ui2_count = ui2_count + ACFG_PRE_SET_PIC_MODE_NUM;

    DBG_INFO(("[PQ] --- get picture mode num:%d, %d\n", ui2_count, __LINE__));

	return ui2_count;
}

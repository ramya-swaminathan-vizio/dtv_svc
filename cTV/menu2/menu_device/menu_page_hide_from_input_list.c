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
 * $RCSfile: menu_page_hide_from_input_list.c,v $
 * $Revision: #1 $
 * $Date: 2010/10/10 $
 * $Author: fs_yuwenhan $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: fs_yuwenhan $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      hide and show input source from input list.
 *---------------------------------------------------------------------------*/
 
#include "menu_page_hide_from_input_list.h"
#include "res/app_util/config/acfg_custom.h"
#include "rest/a_rest_event.h"

//========================================================================

#define MENU_DEBUG_HIDE_LIST(x) //x

//========================================================================

#define INP_LIST_SZIE (6)
#define INP_HIDE_HDMI_4_NUMS (1)

typedef struct _INP_ITEM
{
    MENU_ITEM_T t_item;
    UINT32 ui4_ui_id;
    CHAR* str_rest_title;
    UINT16 (* pfget)(VOID);
    VOID (* pfset)(UINT16);
    UINT16 ui2_title;
    UINT8  ui1_acfg_idx;
} INP_ITEM;

typedef enum
{
    INP_TV,
    INP_COMP,
    INP_HDMI_1,
    INP_HDMI_2,
    INP_HDMI_3,
    INP_HDMI_4
} E_INP_IDX;

static UINT16 _get_hide_comp_from_inp(VOID);
static VOID _set_hide_comp_from_inp(UINT16 ui2_val);
static UINT16 _get_hide_tv_from_inp(VOID);
static VOID _set_hide_tv_from_inp(UINT16 ui2_val);
static UINT16 _get_hide_hdmi_1_from_inp(VOID);
static VOID _set_hide_hdmi_1_from_inp(UINT16 ui2_val);
static UINT16 _get_hide_hdmi_2_from_inp(VOID);
static VOID _set_hide_hdmi_2_from_inp(UINT16 ui2_val);
static UINT16 _get_hide_hdmi_3_from_inp(VOID);
static VOID _set_hide_hdmi_3_from_inp(UINT16 ui2_val);
static UINT16 _get_hide_hdmi_4_from_inp(VOID);
static VOID _set_hide_hdmi_4_from_inp(UINT16 ui2_val);


static E_INP_IDX e_fouced = 0;
static UINT32 ui4_page_sys_hide_from_inp;
static MENU_ITEM_T t_menu_item_page_sys_hide_from_inp;

static INP_ITEM a_inp_items[INP_LIST_SZIE] = 
{
    {
        .ui2_title = MLM_MENU_KEY_HIDE_FROM_INP_TV, 
        .str_rest_title = "tuner",
        .pfget = _get_hide_tv_from_inp, 
        .pfset = _set_hide_tv_from_inp, 
        .ui1_acfg_idx = 6
    },
    {
        .ui2_title = MLM_MENU_KEY_HIDE_FROM_INP_COMP, 
        .str_rest_title = "comp", 
        .pfget = _get_hide_comp_from_inp, 
        .pfset = _set_hide_comp_from_inp, 
        .ui1_acfg_idx = 5
    },
    {
        .ui2_title = MLM_MENU_KEY_HIDE_FROM_INP_HDMI_1, 
        .str_rest_title = "hdmi1", 
        .pfget = _get_hide_hdmi_1_from_inp, 
        .pfset = _set_hide_hdmi_1_from_inp, 
        .ui1_acfg_idx = 0
    },
    {
        .ui2_title = MLM_MENU_KEY_HIDE_FROM_INP_HDMI_2, 
        .str_rest_title = "hdmi2", 
        .pfget = _get_hide_hdmi_2_from_inp, 
        .pfset = _set_hide_hdmi_2_from_inp, 
        .ui1_acfg_idx = 1
    },
    {
        .ui2_title = MLM_MENU_KEY_HIDE_FROM_INP_HDMI_3, 
        .str_rest_title = "hdmi3", 
        .pfget = _get_hide_hdmi_3_from_inp, 
        .pfset = _set_hide_hdmi_3_from_inp, 
        .ui1_acfg_idx = 2
    },
    {
        .ui2_title = MLM_MENU_KEY_HIDE_FROM_INP_HDMI_4, 
        .str_rest_title = "hdmi4", 
        .pfget = _get_hide_hdmi_4_from_inp, 
        .pfset = _set_hide_hdmi_4_from_inp, 
        .ui1_acfg_idx = 3
    }
};

static VOID _set_hide_from_inp(BOOL b_hide)
{
    UINT8       ui1_hide_value = 0;

    MENU_LOG_ON_FAIL(a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value));

    if(b_hide)
    {
        ui1_hide_value &= ~((UINT8)1 << a_inp_items[e_fouced].ui1_acfg_idx);
    }
    else
    {
        ui1_hide_value |= (UINT8)1 << a_inp_items[e_fouced].ui1_acfg_idx;
    }

    MENU_LOG_ON_FAIL(a_cfg_cust_set_hide_from_input_manually(ui1_hide_value));
    rest_event_notify("system/input/visible", 0, a_inp_items[e_fouced].str_rest_title);
}

UINT8 _get_hide_from_inp(VOID) 
{
    UINT8       ui1_hide_value;
    UINT8       ui1_return_value;

    MENU_LOG_ON_FAIL(a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value));
    ui1_return_value = (UINT8)((ui1_hide_value >> a_inp_items[e_fouced].ui1_acfg_idx) & 0x01);
    return ui1_return_value;
}

static UINT16 _get_hide_hdmi_1_from_inp(VOID)
{
    e_fouced = INP_HDMI_1;
    return _get_hide_from_inp();
}

static VOID _set_hide_hdmi_1_from_inp(UINT16 ui2_val)
{
    e_fouced = INP_HDMI_1;
    _set_hide_from_inp(ui2_val == 0);
}

static UINT16 _get_hide_hdmi_2_from_inp(VOID)
{
    e_fouced = INP_HDMI_2;
    return _get_hide_from_inp();
}

static VOID _set_hide_hdmi_2_from_inp(UINT16 ui2_val)
{
    e_fouced = INP_HDMI_2;
    _set_hide_from_inp(ui2_val == 0);
}

static UINT16 _get_hide_hdmi_3_from_inp(VOID)
{
    e_fouced = INP_HDMI_3;
    return _get_hide_from_inp();
}

static VOID _set_hide_hdmi_3_from_inp(UINT16 ui2_val)
{
    e_fouced = INP_HDMI_3;
    _set_hide_from_inp(ui2_val == 0);
}

static UINT16 _get_hide_hdmi_4_from_inp(VOID)
{
    e_fouced = INP_HDMI_4;
    return _get_hide_from_inp();
}

static VOID _set_hide_hdmi_4_from_inp(UINT16 ui2_val)
{
    e_fouced = INP_HDMI_4;
    _set_hide_from_inp(ui2_val == 0);
}

static UINT16 _get_hide_comp_from_inp(VOID)
{
    e_fouced = INP_COMP;
    return _get_hide_from_inp();
}

static VOID _set_hide_comp_from_inp(UINT16 ui2_val)
{
    e_fouced = INP_COMP;
    _set_hide_from_inp(ui2_val == 0);
}

static UINT16 _get_hide_tv_from_inp(VOID)
{
    e_fouced = INP_TV;
    return _get_hide_from_inp();
}

static VOID _set_hide_tv_from_inp(UINT16 ui2_val)
{
    e_fouced = INP_TV;
    _set_hide_from_inp(ui2_val == 0);
}

static INT32 _get_hdmi_ports(VOID)
{
    FILE    *fp;
    INT32   hdmiports = 0;
    INT32   returnport = 0;

    MENU_DEBUG_HIDE_LIST( DBG_LOG_PRINT(("[MENU][hide_inp_list]{%s,%d}\n", __FUNCTION__,__LINE__ )); );

    fp = popen("grep \"count\" /config/hdmi_map.ini | awk -F ' ' '{print $3}'","r");
    if(fp == NULL)
    {
        DBG_ERROR(("[%s %d]open /config/hdmi_map.ini error\r\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if((hdmiports = fgetc(fp)) == EOF)
    {
        DBG_ERROR(("[%s %d]read popen /config/hdmi_map.ini error\r\n",__FUNCTION__,__LINE__));
        pclose(fp);
        return -1;
    }
    pclose(fp);

    returnport = hdmiports - 48;

    MENU_DEBUG_HIDE_LIST( DBG_LOG_PRINT(("[MENU][hide_inp_list]{%s,%d}hdmiports:%d, returnport:%d\n", __FUNCTION__,__LINE__, hdmiports, returnport)); );

    return returnport;
}

static VOID _init_item_list(VOID)
{
    UINT16 ui2_item_id;

    for (UINT8 ui1_i = 0; ui1_i < INP_LIST_SZIE; ui1_i++)
    {
        if (INP_HDMI_3 == ui1_i && (_get_hdmi_ports() < 3))
        {
            continue;
        }

        if (INP_HDMI_4 == ui1_i && (_get_hdmi_ports() < 4))
        {
            continue;
        }

        if (INP_COMP == ui1_i && a_nav_ipts_not_support_comp_source()) 
        {
            continue;
        }
        
        MENU_LOG_ON_FAIL(menu_page_tree_list_item(&a_inp_items[ui1_i].t_item,
                                      a_inp_items[ui1_i].ui2_title,
                                      MLM_MENU_KEY_HELP_HIDE_TV_COMP_INPUT,
                                      MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_VISIBLE,
                                      MLM_MENU_KEY_HIDE_FROM_INPUT_LIST_HIDE,
                                      a_inp_items[ui1_i].pfset,
                                      a_inp_items[ui1_i].pfget));

        MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_sys_hide_from_inp,
                                  &a_inp_items[ui1_i].t_item,
                                  &ui2_item_id));
    }
}

INT32 hide_from_inp_init(UINT16 ui2_parent)
{
    UINT16 ui2_item_id;

    MENU_DEBUG_HIDE_LIST( DBG_LOG_PRINT(("[MENU][hide_inp_list]{%s,%d}\n", __FUNCTION__,__LINE__ )); );

    MENU_LOG_ON_FAIL(menu_page_tree_create(INP_LIST_SZIE,
                           MLM_MENU_KEY_HIDE_FROM_INPUT_LIST,
                           &ui4_page_sys_hide_from_inp));

    MENU_LOG_ON_FAIL(menu_page_tree_subpage_item(&t_menu_item_page_sys_hide_from_inp,
                                            MLM_MENU_KEY_HIDE_FROM_INPUT_LIST,
                                            MLM_MENU_KEY_HELP_HIDE_TV_COMP_INPUT,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_sys_hide_from_inp));

    MENU_LOG_ON_FAIL(menu_page_tree_add(ui2_parent,
                                &t_menu_item_page_sys_hide_from_inp,
                                &ui2_item_id));

    _init_item_list();

    return MENUR_OK;
}


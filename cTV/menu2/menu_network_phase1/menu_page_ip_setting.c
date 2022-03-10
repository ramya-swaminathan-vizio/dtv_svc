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
 * $RCSfile: menu_page_ip_setting.c,v $
 * $Revision: #15 $
 * $Date: 2015/08/07 $
 * $Author: hs_chengweishan $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "c_svctx.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_tsl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu_util2.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"

#include "menu2/menu_common/menu_page_animation.h"
#include "menu_network.h"
#include "res/app_util/config/acfg_custom.h"
#include "wdk/a_digit_pad.h"



typedef struct _NW_IP4_ED_T
{
    HANDLE_T        h_eb_fram;
    HANDLE_T        h_eb_text;
    UINT8           i1_focus_index;
    HANDLE_T        h_ip_dot[3];
    HANDLE_T        h_eb_ip_addr[4];
}NW_IP4_ED_T;

typedef struct _PAGE_IP_SETTING_T
{
    HANDLE_T        h_cnt_frm;
    HANDLE_T        h_txt_alarm;
    HANDLE_T        h_lb_addr_type;
    HANDLE_T        h_btn_save;
    HANDLE_T        h_btn_cancel;

    NW_IP4_ED_T     t_ip_addr;
    NW_IP4_ED_T     t_sub_mask;
    NW_IP4_ED_T     t_def_gateway;
    NW_IP4_ED_T     t_prim_dns;
    NW_IP4_ED_T     t_sec_dns;

    HANDLE_T        h_ethernet_mac;
    HANDLE_T        h_wireless_mac;
}PAGE_IP_SETTING_T;

typedef enum _MENU_IP_SETTING_BTN_TYPE_T
{
    MENU_IP_SETTING_BTN_SAVE = 0,
    MENU_IP_SETTING_BTN_CANCEL,
    MENU_IP_SETTING_BTN_LAST_ENTRY
}MENU_IP_SETTING_BTN_TYPE_T;


typedef struct _NW_CUR_ED_T
{
    HANDLE_T        h_eb_widget;
    HANDLE_T        h_eb_fram;
    HANDLE_T        i1_focus;

    UINT8           i1_focus_index;
    HANDLE_T        h_ip_dot[3];
    HANDLE_T        h_eb_ip_addr[4];

}NW_CUR_ED_T;
static HANDLE_T                h_crnt_frm;

static HANDLE_T                h_digit_handle;
static NW_CUR_ED_T             nw_cur_ed_info;

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifndef    COMMON_DATE_ADDR_TYPE_LB_IDX
    #define    COMMON_DATE_ADDR_TYPE_LB_IDX    0
#endif

#ifndef    COMMON_DATE_IP_ADDR_EB_IDX
    #define    COMMON_DATE_IP_ADDR_EB_IDX      1
#endif

#ifndef    COMMON_DATE_SUB_MASK_EB_IDX
    #define    COMMON_DATE_SUB_MASK_EB_IDX     2
#endif

#ifndef    COMMON_DATE_DEF_GATEWAY_EB_IDX
    #define    COMMON_DATE_DEF_GATEWAY_EB_IDX  3
#endif

#ifndef    COMMON_DATE_PRIM_DNS_EB_IDX
    #define    COMMON_DATE_PRIM_DNS_EB_IDX     4
#endif

#ifndef    COMMON_DATE_SEC_DNS_EB_IDX
    #define    COMMON_DATE_SEC_DNS_EB_IDX      5
#endif

/*The TEXT widget for display edit box title*/
#define    IP4_EB_TITLE_TEXT_X                   (FRAME_LEFT_RIGHT_INTV)
#define    IP4_EB_TITLE_TEXT_Y                   (0)
#define    IP4_EB_TITLE_TEXT_W                   (300)
#define    IP4_EB_TITLE_TEXT_H                   (MENU_ITEM_V_HEIGHT)


#define    IP4_EB_1ST_X                          (MENU_ITEM_BAR_INSET_L + MENU_ITEM_BAR_CNT_INSET_L  \
                                                 + MENU_ITEM_ICON_W + MENU_ITEM_TITLE_W )
#define    IP4_EB_Y                              (0)
/*70 is the width of the asset*/
#define    IP4_EB_W                              (44 + 5*4/3 + 3)//((MENU_ITEM_V_WIDE - IP4_EB_TITLE_TEXT_X - IP4_EB_TITLE_TEXT_W)/4) - 6*4/3
#define    IP4_EB_H                              (MENU_ITEM_V_HEIGHT)



#define    IP4_EB_INPUT_INSET_L                  (0)
#define    IP4_EB_INPUT_INSET_R                  (0)
#define    IP4_EB_INPUT_INSET_T                  (16) //TODO
#define    IP4_EB_INPUT_INSET_B                  (0)

#define    IP4_EB_INPUT_CNT_INSET_L              (0)
#define    IP4_EB_INPUT_CNT_INSET_R              (0)
#define    IP4_EB_INPUT_CNT_INSET_T              (0)
#define    IP4_EB_INPUT_CNT_INSET_B              (0)

#define    IP4_EB_INPUT_LIMIT                    (4)


/*----------------------------------------------------
      data declarations
      ----------------------------------------------------*/

MENU_PAGE_FCT_TBL_T    t_g_menu_common_ip_setting;
PAGE_IP_SETTING_T      t_page_ip_setting;
NW_IP_INFO_T           t_page_ip_info;
static  BOOL           b_page_ip_chg;
UINT32                 ui4_page_ip_setting_dhcp;
/*network notify message var*/
static UINT32          ui4_nw_nfy_id = 0;
static BOOL            b_this_page_show = FALSE;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_ip_setting_dhcp;

#ifdef APP_TTS_SUPPORT
static HANDLE_T h_g_eb_parent = NULL_HANDLE;
#endif

HANDLE_T              h_addr_delay_timer = NULL_HANDLE;
/*----------------------------------------------------*/
/* Function declaration*/
/*----------------------------------------------------*/


static INT32 _page_ip_setting_set_ip4_eb_str(
                               NW_IP4_ED_T*  pt_ip_eb,
                               UINT32        ui4_ip);

static INT32 _page_ip_setting_update_clr_with_state(UINT16 ui2_status);

static VOID _page_ip_setting_lb_addr_type_change_fct(VOID* pv_data,
                                                     SIZE_T  z_data_size);


/*----------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_eb_ip_style_eb_input
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
static INT32 _page_ip_setting_eb_ip_style_eb_input(HANDLE_T h_widget , UINT8  ui1_digit)
{
    UTF16_T      w2s_data[5];
    INT32        i4_ret = MENUR_OK;
    UINT8        ui1_str_len = 0;
    UINT32       ui1_col = 0;

    c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd (h_widget,
                        WGL_CMD_EB_GET_TEXT,
                        WGL_PACK (w2s_data),
                        WGL_PACK (5)
                        );
    MENU_LOG_ON_FAIL(i4_ret);
    ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&ui1_col),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui1_str_len == 0)
    {
        i4_ret = c_uc_w2s_set(w2s_data,ui1_str_len,(UTF16_T)(ui1_digit+'0'));
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len+1),(UTF16_T)('_'));
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len+2),(UTF16_T)('\0'));
        MENU_LOG_ON_FAIL(i4_ret);

   }
    else if (ui1_str_len < 4)
    {
        i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len - 1 ),(UTF16_T)(ui1_digit+'0'));
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len),(UTF16_T)('_'));
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len+1),(UTF16_T)('\0'));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        UTF16_T *pw2s_temp = NULL;
        pw2s_temp = c_uc_w2s_get_ptr(w2s_data,(UINT32)(0));
        if( pw2s_temp)
        {
            if (*pw2s_temp == '0')
            {
                w2s_data[0] = w2s_data[1];
                w2s_data[1] = w2s_data[2];

                i4_ret = c_uc_w2s_set(w2s_data,2,(UTF16_T)(ui1_digit+'0'));
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    i4_ret = c_wgl_do_cmd(h_widget,
                     WGL_CMD_EB_SET_TEXT,
                     WGL_PACK(w2s_data),
                     WGL_PACK(c_uc_w2s_strlen(w2s_data))
                     );
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_eb_ip_style_eb_get_value
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
static INT32 _page_ip_setting_eb_ip_style_eb_get_value(
                                        HANDLE_T        h_widget,
                                        UINT16*         pui2_value,
                                        BOOL*           pb_is_empty)
{
    INT32      i4_ret = MENUR_OK;
    UINT8      ui1_idx = 0;

    UTF16_T    w2s_data[5];
    CHAR       ch_data[5];
    UINT8      ui1_str_len = 0;

    c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));
    *pb_is_empty = FALSE;
    *pui2_value = 0;

    i4_ret = c_wgl_do_cmd (h_widget,
                        WGL_CMD_EB_GET_TEXT,
                        WGL_PACK (w2s_data),
                        WGL_PACK (5)
                        );
    MENU_LOG_ON_FAIL(i4_ret);

    if (c_uc_w2s_strcmp(w2s_data,(UTF16_T*)L"") == 0||
        c_uc_w2s_strcmp(w2s_data,(UTF16_T*)L"_") == 0)
    {
        *pb_is_empty = TRUE;
        return MENUR_OK;
    }

    c_uc_w2s_to_ps(w2s_data,ch_data,5* sizeof(CHAR));

    ui1_str_len = (UINT8)c_strlen(ch_data);

    if (ui1_str_len >=  (UINT8)(5))
    {
        return MENUR_OUT_OF_MEMORY;
    }

    for(ui1_idx= 0; ui1_idx < ui1_str_len; ui1_idx++)
    {
        if (ch_data[ui1_idx] == '_')
        {
            break;
        }
        *pui2_value = (UINT16)(10 * (*pui2_value) + (ch_data[ui1_idx] - '0'));
    }

    return MENUR_OK;
}

static INT32  _menu_nw_aton(UINT32* pui4_ip, char * ps_ip_str)
{
    CHAR* ps = ps_ip_str;

    UINT32  aui4_ip_addr[4] = {0,0,0,0};
    UINT32* pui4_ip_addr = &aui4_ip_addr[0];

    if (ps_ip_str == NULL || pui4_ip == NULL)
    {
        return MENUR_INV_ARG;
    }

    while ( *ps != '\0' )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            *pui4_ip_addr = 10 * (*pui4_ip_addr) + (*ps - '0');
            ps++;
        }
        else if( *ps == '.')
        {
            pui4_ip_addr ++;
            ps++;
        }
        else
        {
            ps++;
            continue;
        }
    }

    aui4_ip_addr[1] = (aui4_ip_addr[1]<<8) & 0xFF00;
    aui4_ip_addr[2] = (aui4_ip_addr[2]<<16)& 0xFF0000;
    aui4_ip_addr[3] = (aui4_ip_addr[3]<<24)& 0xFF000000;

    *pui4_ip = aui4_ip_addr[0] + aui4_ip_addr[1]
               + aui4_ip_addr[2]+ aui4_ip_addr[3];

    return MENUR_OK;
}

static INT32 _check_string(const char* ps_input, char* ps_output)
{
    INT32        i4_ret = MENUR_OK;

    if ((NULL == ps_input) || (NULL == ps_output))
    {
        DBG_ERROR(("\n%s,%d\n",
                    __FUNCTION__, __LINE__));
        return MENUR_INV_ARG;
    }

    while (*ps_input != '\0')
    {
        if (*ps_input >= '0' && *ps_input <= '9')
        {
            *ps_output = *ps_input;
            ps_input++;
            ps_output++;
        }
        else if (*ps_input == '.')
        {
            *ps_output = *ps_input;
            ps_input++;
            ps_output++;
        }
        else
        {
            ps_input++;
        }
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_get_ip4_eb_string
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
static INT32 _page_ip_setting_get_ip4_eb_string(NW_IP4_ED_T*  pt_ip_eb,VOID*  pt_ip_string)
{
    INT32        i4_ret = MENUR_OK;
    UTF16_T      w2s_str[32] = {0};
    UTF16_T      w2s_data[5] = {0};
    CHAR         s_ip_str[32]= {0};
    UINT8        ui1_str_len = 0;
    CHAR         s_ip[32] = {0};
    CHAR          aa[6] = {0};
    UTF16_T     *pt_tmp = (UTF16_T *)pt_ip_string;

    if(NULL == pt_ip_string || NULL == pt_ip_eb)
    {
        DBG_LOG_PRINT(("%s: %d\r\n", __func__, __LINE__));
        return MENUR_FAIL;
    }

    UINT8        ui1_col = 0;

    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));

        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                            WGL_CMD_EB_GET_TEXT,
                            WGL_PACK (w2s_data),
                            WGL_PACK (5)
                            );
        MENU_LOG_ON_FAIL(i4_ret);
        if (ui1_col < 3)
        {
            ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);
            c_uc_w2s_to_ps(w2s_data,aa,6 );
            i4_ret = c_uc_w2s_set(w2s_data,ui1_str_len > 3 ? 3 : ui1_str_len,(UTF16_T)('.'));
            MENU_LOG_ON_FAIL(i4_ret);
        }
        c_uc_w2s_strcat(w2s_str,w2s_data);
    }

    i4_ret = c_uc_w2s_to_ps(w2s_str, s_ip_str,sizeof(CHAR)*32);
    MENU_LOG_ON_FAIL(i4_ret);

    _check_string(s_ip_str, s_ip);
    c_uc_w2s_strcpy(pt_tmp, w2s_str);

    DBG_LOG_PRINT(("<zanchen>---s_ip: %s\r\n", s_ip));

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_get_ip4_eb_value
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
static INT32 _page_ip_setting_get_ip4_eb_value(
                                  NW_IP4_ED_T*  pt_ip_eb,
                                  UINT32*       pui4_ip
                                  )
{
    INT32        i4_ret = MENUR_OK;
    UTF16_T      w2s_str[32];
    UTF16_T      w2s_data[5];
    CHAR         s_ip_str[32];
    UINT8        ui1_str_len = 0;
    CHAR         s_ip[32] = {0};

    c_memset(w2s_str,0,sizeof(UTF16_T)*32);
    c_memset(s_ip_str,0,sizeof(CHAR)*32);

    UINT8        ui1_col = 0;

    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));

        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                            WGL_CMD_EB_GET_TEXT,
                            WGL_PACK (w2s_data),
                            WGL_PACK (5)
                            );
        MENU_LOG_ON_FAIL(i4_ret);
        if (ui1_col < 3)
        {
            ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);
            i4_ret = c_uc_w2s_set(w2s_data,ui1_str_len > 3 ? 3 : ui1_str_len,(UTF16_T)('.'));
            MENU_LOG_ON_FAIL(i4_ret);
        }
        c_uc_w2s_strcat(w2s_str,w2s_data);
    }

    i4_ret = c_uc_w2s_to_ps(w2s_str, s_ip_str,sizeof(CHAR)*32);
    MENU_LOG_ON_FAIL(i4_ret);

    _check_string(s_ip_str, s_ip);

    return _menu_nw_aton(pui4_ip,s_ip_str);
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_eb_save_ip_addr
 *
 * Description: save the ip info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_eb_save_ip_addr(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UINT32   ui4_address = 0;
    UINT32   ui4_sub_mask = 0;
    UINT32   ui4_def_gateway = 0;
    UINT32   ui4_prim_dns = 0;
    UINT32   ui4_sec_dns = 0;

    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    i4_ret = _page_ip_setting_get_ip4_eb_value(&pt_page_data->t_ip_addr, &ui4_address);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_get_ip4_eb_value(&pt_page_data->t_sub_mask, &ui4_sub_mask);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_get_ip4_eb_value(&pt_page_data->t_def_gateway, &ui4_def_gateway);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_get_ip4_eb_value(&pt_page_data->t_prim_dns, &ui4_prim_dns);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_get_ip4_eb_value(&pt_page_data->t_sec_dns, &ui4_sec_dns);
    MENU_LOG_ON_FAIL(i4_ret);

    t_page_ip_info.ui4_address = ui4_address;
    t_page_ip_info.ui4_netmask = ui4_sub_mask;
    t_page_ip_info.ui4_gw      = ui4_def_gateway;
    t_page_ip_info.ui4_1st_dns = ui4_prim_dns;
    t_page_ip_info.ui4_2nd_dns = ui4_sec_dns;
    DBG_INFO(("[NW][%s %d]ui4_address = 0x%x, ui4_gw = 0x%x,ui4_netmask = 0x%x,ui4_1st_dns = 0x%x,ui4_2nd_dns = 0x%x\n",__FUNCTION__,__LINE__,
    t_page_ip_info.ui4_address,
    t_page_ip_info.ui4_gw,
    t_page_ip_info.ui4_netmask,
    t_page_ip_info.ui4_1st_dns,
    t_page_ip_info.ui4_2nd_dns));

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_widget_default_proc_fct
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
static INT32  _page_ip_setting_widget_default_proc_fct(HANDLE_T    h_widget,
                                 UINT32      ui4_msg,
                                 VOID*       param1,
                                 VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
            case BTN_RETURN:
                menu_netowrk_nav_back();
                return WMPR_DONE;
            }
        }
        break;
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_eb_ip_style_clear
 *
 * Description: when press button-left ,it means delete the data in editbox
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_eb_ip_style_clear(HANDLE_T h_widget, BOOL* pb_repaint)
{
    UTF16_T      w2s_data[5];
    INT32        i4_ret = MENUR_OK;
    UINT8        ui1_str_len = 0;
    UINT32       ui4_col = 0;
    HANDLE_T     h_parent,h_focus = NULL_HANDLE;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&ui4_col),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd (h_widget,
                        WGL_CMD_EB_GET_TEXT,
                        WGL_PACK (w2s_data),
                        WGL_PACK (5)
                        );
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);

    if (ui1_str_len == (UINT8)(1) && ui4_col != 0)
    {
        if ((pt_page_data->t_ip_addr.i1_focus_index > 4) ||
            (pt_page_data->t_sub_mask.i1_focus_index > 4)||
            (pt_page_data->t_def_gateway.i1_focus_index > 4) ||
            (pt_page_data->t_prim_dns.i1_focus_index > 4) ||
            (pt_page_data->t_sec_dns.i1_focus_index > 4))
        {
            return MENUR_FAIL;
        }
        if(w2s_data[ui1_str_len-1] == (UTF16_T)('_'))
        {
            i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len - 1), (UTF16_T)('\0'));
        }
        i4_ret = c_wgl_do_cmd (h_widget,
                        WGL_CMD_EB_SET_TEXT,
                        WGL_PACK (w2s_data),
                        WGL_PACK (5)
                        );
        c_wgl_get_parent(h_widget, &h_parent);
        if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
        {
            h_focus = pt_page_data->t_ip_addr.h_eb_ip_addr[-- pt_page_data->t_ip_addr.i1_focus_index];
        }
        else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
        {
            h_focus = pt_page_data->t_sub_mask.h_eb_ip_addr[-- pt_page_data->t_sub_mask.i1_focus_index];
        }
        else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
        {
            h_focus = pt_page_data->t_def_gateway.h_eb_ip_addr[-- pt_page_data->t_def_gateway.i1_focus_index];
        }
        else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
        {
            h_focus = pt_page_data->t_prim_dns.h_eb_ip_addr[-- pt_page_data->t_prim_dns.i1_focus_index];
        }
        else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
        {
            h_focus = pt_page_data->t_sec_dns.h_eb_ip_addr[-- pt_page_data->t_sec_dns.i1_focus_index];
        }

        i4_ret = c_wgl_set_focus(h_focus, TRUE);
        return MENUR_OK;

    }
    if ((ui1_str_len >= (UINT8)(2)) && (ui1_str_len < (UINT8)(5)))
    {
        if(w2s_data[ui1_str_len-1] == (UTF16_T)('_'))
        {
            w2s_data[ui1_str_len - 2] = w2s_data[ui1_str_len - 1];
            i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len - 1), (UTF16_T)('\0'));
        }
        else
        {
            i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len - 1), (UTF16_T)('_'));
            i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len), (UTF16_T)('\0'));
        }
    }

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                     WGL_CMD_EB_SET_TEXT,
                     WGL_PACK(w2s_data),
                     WGL_PACK(c_uc_w2s_strlen(w2s_data))
                     );
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_change_fm_bk
 *
 * Description: change the background image of frame
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_change_fm_bk(HANDLE_T    h_widget,
                                                  BOOL b_chg)
{
    INT32 i4_ret;
    WGL_IMG_INFO_T      t_img_info;
    HANDLE_T            h_parent = NULL_HANDLE;

    c_wgl_get_parent(h_widget, &h_parent);
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    if(b_chg)
    {
        t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_hlt_bk;
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    }

    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE; /* h_g_menu_img_item_bk;*/
    i4_ret = c_wgl_do_cmd(h_parent,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    /*menu_pm_refresh();*/
    /*menu_pm_repaint();*/
    MENU_LOG_ON_FAIL(c_wgl_repaint(h_parent, NULL, TRUE));
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_eb_ip_style_clear
 *
 * Description: when press button-left ,it means delete the data in editbox
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_eb_ip_style_clear_underline(HANDLE_T h_widget)
{
    UTF16_T      w2s_data[5];
    INT32        i4_ret = MENUR_OK;
    UINT8        ui1_str_len = 0;

    c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd (h_widget,
                        WGL_CMD_EB_GET_TEXT,
                        WGL_PACK (w2s_data),
                        WGL_PACK (5)
                        );
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);

    if ((ui1_str_len >= (UINT8)(1)) && (ui1_str_len < (UINT8)(1+5)))
    {
        if(w2s_data[ui1_str_len-1] == (UTF16_T)('_'))
        {
            i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(ui1_str_len - 1), (UTF16_T)('\0'));
        }
    }

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                     WGL_CMD_EB_SET_TEXT,
                     WGL_PACK(w2s_data),
                     WGL_PACK(c_uc_w2s_strlen(w2s_data))
                     );
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

static BOOL     b_clear_pre    = true;

static VOID dhcp_digit_pad_key_event_nfy(DIGIT_PAD_EVENT_TYPE event_type, VOID* pv_param)
{
    CHAR            digit_val;
    INT32           i4_ret;
    BOOL            b_repaint = FALSE;
    UINT16          ui2_value;
    BOOL            b_is_empty;
    HANDLE_T    h_parent= NULL_HANDLE ,h_focus = NULL_HANDLE;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    UINT32      ui4_index = 0;
    UTF16_T      w2s_data[5] = {0};

    switch(event_type)
    {
        case DIGIT_PAD_DIGIT_KEY:
            digit_val = *((CHAR*)pv_param);
            DBG_LOG_PRINT(("-----------------baozi %s %d event_type = %d, digit_val = %c\n",__FUNCTION__,__LINE__, event_type, digit_val));

            //first clear all
            if(b_clear_pre == FALSE)
            {
                //do clear
                c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));
                i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(0), (UTF16_T)('_'));
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret = c_uc_w2s_set(w2s_data,(UINT32)(1), (UTF16_T)('\0'));
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret = c_wgl_do_cmd(nw_cur_ed_info.i1_focus,
                                     WGL_CMD_EB_SET_TEXT,
                                     WGL_PACK(w2s_data),
                                     WGL_PACK(c_uc_w2s_strlen(w2s_data))
                                     );
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret = c_wgl_repaint(nw_cur_ed_info.i1_focus, NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                b_clear_pre = TRUE;
            }

            _page_ip_setting_eb_ip_style_eb_get_value(nw_cur_ed_info.i1_focus, &ui2_value, &b_is_empty);

            /*the max value of ip addr is 255, so if current ip addr value is greater than 25, the input button key
                        should not add to ip addr */
            if (ui2_value > 25)
            {
                return ;
            }
            if ((ui2_value == 25) && (digit_val > '5'))
            {
                return ;
            }


            /*the ip adrr change*/
            i4_ret = _page_ip_setting_eb_ip_style_eb_input(nw_cur_ed_info.i1_focus,(UINT8)(digit_val - '0'));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(nw_cur_ed_info.i1_focus, NULL, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd (nw_cur_ed_info.i1_focus,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_data),
                                    WGL_PACK (5)
                                  );
            MENU_LOG_ON_FAIL(i4_ret);
            b_page_ip_chg = TRUE;

            if(w2s_data[2] != (UTF16_T)'_' &&
               w2s_data[2] != (UTF16_T)'\0' &&
               (nw_cur_ed_info.i1_focus == pt_page_data->t_sec_dns.h_eb_ip_addr[3]))
            {
                i4_ret = a_digit_pad_hide(h_digit_handle);
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret = c_wgl_set_focus(nw_cur_ed_info.i1_focus, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;
        case DIGIT_PAD_DEL_KEY:
            DBG_LOG_PRINT(("-----------------baozi %s %d event_type = %d, do somthing with del\n",__FUNCTION__,__LINE__, event_type));

            /*the ip addr change*/
            b_page_ip_chg = TRUE;
            i4_ret = _page_ip_setting_eb_ip_style_clear(nw_cur_ed_info.i1_focus, &b_repaint);
            MENU_LOG_ON_FAIL(i4_ret);

            if (b_repaint)
            {
                i4_ret = c_wgl_repaint(nw_cur_ed_info.i1_focus, NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            break;
        case DIGIT_PAD_BUTTON_OK://next
            DBG_LOG_PRINT(("-----------------baozi %s %d event_type = %d, do somthing with ok\n",__FUNCTION__,__LINE__, event_type));
            //Move hightlight to the next IP address

            c_wgl_get_parent(nw_cur_ed_info.h_eb_widget, &h_parent);

            if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
            {
                ui4_index = pt_page_data->t_ip_addr.i1_focus_index;
                pt_page_data->t_ip_addr.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                if (pt_page_data->t_ip_addr.i1_focus_index < 4)
                {
                    h_focus = pt_page_data->t_ip_addr.h_eb_ip_addr[pt_page_data->t_ip_addr.i1_focus_index];
                }
            }
            else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
            {
                ui4_index = pt_page_data->t_sub_mask.i1_focus_index;
                pt_page_data->t_sub_mask.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                if (pt_page_data->t_sub_mask.i1_focus_index < 4)
                {
                    h_focus = pt_page_data->t_sub_mask.h_eb_ip_addr[pt_page_data->t_sub_mask.i1_focus_index];
                }
            }
            else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
            {
                ui4_index = pt_page_data->t_def_gateway.i1_focus_index;
                pt_page_data->t_def_gateway.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                if (pt_page_data->t_def_gateway.i1_focus_index < 4)
                {
                    h_focus = pt_page_data->t_def_gateway.h_eb_ip_addr[pt_page_data->t_def_gateway.i1_focus_index];
                }
            }
            else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
            {
                ui4_index = pt_page_data->t_prim_dns.i1_focus_index;
                pt_page_data->t_prim_dns.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                if (pt_page_data->t_prim_dns.i1_focus_index < 4)
                {
                    h_focus = pt_page_data->t_prim_dns.h_eb_ip_addr[pt_page_data->t_prim_dns.i1_focus_index];
                }
            }
            else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
            {
                ui4_index = pt_page_data->t_sec_dns.i1_focus_index;
                pt_page_data->t_sec_dns.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                if (pt_page_data->t_sec_dns.i1_focus_index < 4)
                {
                    h_focus = pt_page_data->t_sec_dns.h_eb_ip_addr[pt_page_data->t_sec_dns.i1_focus_index];
                }
            }
            else
            {
                break;
            }
            //clear the underline of prev focus
            _page_ip_setting_eb_ip_style_clear_underline(nw_cur_ed_info.i1_focus);
            i4_ret = c_wgl_set_focus(h_focus, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            //b_clear_pre = FALSE;

            nw_cur_ed_info.i1_focus = h_focus;
            //i4_ret = a_digit_pad_focus(h_digit_handle);
            //MENU_LOG_ON_FAIL(i4_ret);

            break;
        case DIGIT_PAD_BUTTON_CANCEL:
        case DIGIT_PAD_NAV_BACK:
            DBG_LOG_PRINT(("-----------------baozi %s %d event_type = %d, do somthing with cancle\n",__FUNCTION__,__LINE__, event_type));
            //close digit pad and allow navigation within the address

            //close
            i4_ret = a_digit_pad_hide(h_digit_handle);
            MENU_LOG_ON_FAIL(i4_ret);

            _page_ip_setting_eb_ip_style_clear_underline(nw_cur_ed_info.i1_focus);
            //focus
            i4_ret = c_wgl_set_focus(nw_cur_ed_info.i1_focus, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            break;
        case DIGIT_PAD_FOCUS_TO_ABOVE_WGL:
            DBG_LOG_PRINT(("-----------------baozi %s %d event_type = %d, should move focus to wgl above digit pad\n",__FUNCTION__,__LINE__, event_type));
            menu_set_focus_on_backbar(TRUE);
            break;
        case DIGIT_PAD_FOCUS_TO_BELOW_WGL:
            DBG_LOG_PRINT(("-----------------baozi %s %d event_type = %d, should move focus to wgl below digit pad\n",__FUNCTION__,__LINE__, event_type));
            i4_ret = c_wgl_set_focus(nw_cur_ed_info.i1_focus, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        default:
            break;
    }
}


/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_editbox_proc_fct
 *
 * Description: the callback function of ip address editbox
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  _page_ip_setting_editbox_proc_fct(
                                    HANDLE_T    h_widget,
                                    UINT32      ui4_msg,
                                    VOID*       param1,
                                    VOID*       param2  )
{
    INT32        i4_ret      = MENUR_OK;
    UTF16_T      w2s_data[5] = {0};
    UINT8        ui1_str_len = 0;
    static BOOL  b_chg_bk    = TRUE;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
        if (b_chg_bk == TRUE)
        {
            _page_ip_setting_change_fm_bk(h_widget,TRUE);
        }

        i4_ret = c_wgl_do_cmd (h_widget,
                               WGL_CMD_EB_GET_TEXT,
                               WGL_PACK (w2s_data),
                               WGL_PACK (5));
        MENU_LOG_ON_FAIL(i4_ret);
        ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);

        c_uc_w2s_set(w2s_data,ui1_str_len > 3 ? 3 : ui1_str_len,(UTF16_T)('_'));

        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_EB_SET_TEXT,
                              WGL_PACK(w2s_data),
                              WGL_PACK(c_uc_w2s_strlen(w2s_data)));
        MENU_LOG_ON_FAIL(i4_ret);
        b_chg_bk = TRUE;

#ifdef APP_TTS_SUPPORT
        UTF16_T             w2s_tts[128+1] = {0};
        HANDLE_T            h_parent       = NULL_HANDLE;
        PAGE_IP_SETTING_T*  pt_page_data   = &t_page_ip_setting;
        UINT16              ui2_msgid_tts;
        UTF16_T             w2s_str[32]    = {0};

        c_wgl_get_parent(h_widget, &h_parent);

        if (h_g_eb_parent == h_parent)
        {
            return MENUR_OK;
        }

        if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
        {
            ui2_msgid_tts = MLM_MENU_KEY_NET_CFG_IP_ADDRESS;
            _page_ip_setting_get_ip4_eb_string(&pt_page_data->t_ip_addr, w2s_str);
        }
        else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
        {
            ui2_msgid_tts = MLM_MENU_KEY_NET_CFG_SUB_MASK;
            _page_ip_setting_get_ip4_eb_string( &pt_page_data->t_sub_mask, w2s_str);
        }
        else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
        {
            ui2_msgid_tts = MLM_MENU_KEY_NET_CFG_DEF_GW;
            _page_ip_setting_get_ip4_eb_string(&pt_page_data->t_def_gateway, w2s_str);
        }
        else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
        {
            ui2_msgid_tts = MLM_MENU_KEY_NET_CFG_PRI_DNS;
            _page_ip_setting_get_ip4_eb_string(&pt_page_data->t_prim_dns, w2s_str);
        }
        else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
        {
            ui2_msgid_tts = MLM_MENU_KEY_NET_CFG_SEC_DNS;
            _page_ip_setting_get_ip4_eb_string(&pt_page_data->t_sec_dns, w2s_str);
        }
        else
        {
            return MENUR_OK;
        }


        h_g_eb_parent = h_parent;

        c_uc_w2s_strcpy(w2s_tts, MENU_TTS_TEXT(ui2_msgid_tts));

        c_uc_w2s_strcat(w2s_tts, w2s_str);
        a_app_tts_play(w2s_tts, c_uc_w2s_strlen(w2s_tts));
#endif
        return MENUR_OK;

    case WGL_MSG_LOSE_FOCUS:
        c_memset(w2s_data, 0, 5 * sizeof(UTF16_T));

        i4_ret = c_wgl_do_cmd (h_widget,
                            WGL_CMD_EB_GET_TEXT,
                            WGL_PACK (w2s_data),
                            WGL_PACK (5));
        ui1_str_len = (UINT8)c_uc_w2s_strlen(w2s_data);

        c_uc_w2s_set(w2s_data,ui1_str_len > 3 ? 3 : ui1_str_len,(UTF16_T)('\0'));

        i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_EB_SET_TEXT,
                         WGL_PACK(w2s_data),
                         WGL_PACK(c_uc_w2s_strlen(w2s_data)));
        MENU_LOG_ON_FAIL(i4_ret);

        if (b_chg_bk == TRUE)
        {
            _page_ip_setting_change_fm_bk(h_widget,FALSE);
        }

        if (b_page_ip_chg)
        {
            i4_ret = _page_ip_setting_eb_save_ip_addr();
            MENU_LOG_ON_FAIL(i4_ret);
        }
        b_chg_bk = TRUE;
        DBG_LOG_PRINT(("[MENU][%s %d]\n",__FUNCTION__,__LINE__));

        return MENUR_OK;

    case WGL_MSG_KEY_DOWN:
    {
        UINT32      ui4_keycode = (UINT32)param1;
        UINT32      ui4_index = 0;
        HANDLE_T    h_parent= NULL_HANDLE ,h_focus = NULL_HANDLE;
        PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
        BOOL        b_repaint = FALSE;
        UINT16      ui2_value;
        BOOL        b_is_empty;
        UINT8       ui1_dhcp_status = ACFG_DHCP_OFF;
        BOOL        b_auto_ip = FALSE;

        switch (ui4_keycode)
        {
        case BTN_DIGIT_0:
        case BTN_DIGIT_1:
        case BTN_DIGIT_2:
        case BTN_DIGIT_3:
        case BTN_DIGIT_4:
        case BTN_DIGIT_5:
        case BTN_DIGIT_6:
        case BTN_DIGIT_7:
        case BTN_DIGIT_8:
        case BTN_DIGIT_9:
        {
            _page_ip_setting_eb_ip_style_eb_get_value(h_widget, &ui2_value, &b_is_empty);

            /*the max value of ip addr is 255, so if current ip addr value is greater than 25, the input button key
                        should not add to ip addr */
            if (ui2_value > 25)
            {
                return MENUR_OK;
            }
            if ((ui2_value == 25) && (ui4_keycode > BTN_DIGIT_5))
            {
                return MENUR_OK;
            }
            /*the ip adrr change*/
            b_page_ip_chg = TRUE;
            i4_ret = _page_ip_setting_eb_ip_style_eb_input(h_widget,(UINT8)(ui4_keycode - BTN_DIGIT_0));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case BTN_CURSOR_DOWN:
            DBG_LOG_PRINT(("[MENU][%s %d]\n",__FUNCTION__,__LINE__));
            b_chg_bk = TRUE;
            c_wgl_get_parent(h_widget, &h_parent);

            if ((pt_page_data->t_sub_mask.i1_focus_index >= 4) ||
                (pt_page_data->t_def_gateway.i1_focus_index >= 4)||
                (pt_page_data->t_prim_dns.i1_focus_index >=4) ||
                (pt_page_data->t_sec_dns.i1_focus_index >=4))
            {
                return MENUR_FAIL;
            }

            if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
            {
                h_focus = pt_page_data->t_sub_mask.h_eb_ip_addr[pt_page_data->t_sub_mask.i1_focus_index];
            }
            else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
            {
                h_focus = pt_page_data->t_def_gateway.h_eb_ip_addr[pt_page_data->t_def_gateway.i1_focus_index];
            }
            else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
            {
                h_focus = pt_page_data->t_prim_dns.h_eb_ip_addr[pt_page_data->t_prim_dns.i1_focus_index];
            }
            else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
            {
                h_focus = pt_page_data->t_sec_dns.h_eb_ip_addr[pt_page_data->t_sec_dns.i1_focus_index];
            }
            else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
            {
                h_focus = pt_page_data->h_btn_save;
            }
            else
            {
                break;
            }
            _page_ip_setting_eb_ip_style_clear_underline(h_widget);

        #ifdef APP_TTS_SUPPORT
            h_g_eb_parent = NULL_HANDLE;
        #endif
        DBG_LOG_PRINT(("[MENU][%s %d]\n",__FUNCTION__,__LINE__));

            i4_ret = c_wgl_set_focus(h_focus, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            DBG_LOG_PRINT(("[MENU][%s %d]\n",__FUNCTION__,__LINE__));

            return i4_ret;

        case BTN_CURSOR_UP:
            b_chg_bk = TRUE;
            DBG_LOG_PRINT(("[MENU][%s %d]\n",__FUNCTION__,__LINE__));

            i4_ret = nw_custom_get_auto_ip_config(&b_auto_ip);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = nw_custom_get_dhcp_status(&ui1_dhcp_status);
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_get_parent(h_widget, &h_parent);
            _page_ip_setting_eb_ip_style_clear_underline(h_widget);
            if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
            {
                h_focus = pt_page_data->h_lb_addr_type;
                i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_AT_HELP));
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if ((pt_page_data->t_ip_addr.i1_focus_index >= 4) ||
                (pt_page_data->t_sub_mask.i1_focus_index >= 4)||
                (pt_page_data->t_def_gateway.i1_focus_index >=4) ||
                (pt_page_data->t_prim_dns.i1_focus_index >=4))
            {
                return MENUR_FAIL;
            }
            else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
            {
                h_focus = pt_page_data->t_ip_addr.h_eb_ip_addr[pt_page_data->t_ip_addr.i1_focus_index];
            }
            else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
            {
                h_focus = pt_page_data->t_sub_mask.h_eb_ip_addr[pt_page_data->t_sub_mask.i1_focus_index];
            }
            else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
            {
                /* dns only */
                if ((FALSE == b_auto_ip) && (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status))
                {
                    h_focus = pt_page_data->h_lb_addr_type;
                    i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_AT_HELP));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    h_focus = pt_page_data->t_def_gateway.h_eb_ip_addr[pt_page_data->t_def_gateway.i1_focus_index];
                }
            }
            else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
            {
                h_focus = pt_page_data->t_prim_dns.h_eb_ip_addr[pt_page_data->t_prim_dns.i1_focus_index];
            }
            else
            {
                break;
            }

        #ifdef APP_TTS_SUPPORT
            h_g_eb_parent = NULL_HANDLE;
        #endif

            i4_ret = c_wgl_set_focus(h_focus, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            DBG_LOG_PRINT(("[MENU][%s %d]\n",__FUNCTION__,__LINE__));

            return i4_ret;

        case BTN_CURSOR_LEFT:
            b_chg_bk = FALSE;

            /*the ip addr change*/
            b_page_ip_chg = TRUE;
            i4_ret = _page_ip_setting_eb_ip_style_clear(h_widget, &b_repaint);
            MENU_LOG_ON_FAIL(i4_ret);

            if (b_repaint)
            {
                i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            b_chg_bk = TRUE;
            return i4_ret;
        case BTN_CURSOR_RIGHT:

                b_chg_bk = FALSE;
                c_wgl_get_parent(h_widget, &h_parent);

                if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_ip_addr.i1_focus_index;
                    pt_page_data->t_ip_addr.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                    if (pt_page_data->t_ip_addr.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_ip_addr.h_eb_ip_addr[pt_page_data->t_ip_addr.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_sub_mask.i1_focus_index;
                    pt_page_data->t_sub_mask.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                    if (pt_page_data->t_sub_mask.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_sub_mask.h_eb_ip_addr[pt_page_data->t_sub_mask.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_def_gateway.i1_focus_index;
                    pt_page_data->t_def_gateway.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                    if (pt_page_data->t_def_gateway.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_def_gateway.h_eb_ip_addr[pt_page_data->t_def_gateway.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_prim_dns.i1_focus_index;
                    pt_page_data->t_prim_dns.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                    if (pt_page_data->t_prim_dns.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_prim_dns.h_eb_ip_addr[pt_page_data->t_prim_dns.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_sec_dns.i1_focus_index;
                    pt_page_data->t_sec_dns.i1_focus_index = (ui4_index == 3? ui4_index : (ui4_index+1));
                    if (pt_page_data->t_sec_dns.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_sec_dns.h_eb_ip_addr[pt_page_data->t_sec_dns.i1_focus_index];
                    }
                }
                else
                {
                    break;
                }
                _page_ip_setting_eb_ip_style_clear_underline(h_widget);
                i4_ret = c_wgl_set_focus(h_focus, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                b_chg_bk = TRUE;
                return i4_ret;

        case BTN_SELECT:

                b_chg_bk = FALSE;
                c_wgl_get_parent(h_widget, &h_parent);
                if (h_parent == pt_page_data->t_ip_addr.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_ip_addr.i1_focus_index;
                    if (pt_page_data->t_ip_addr.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_ip_addr.h_eb_ip_addr[pt_page_data->t_ip_addr.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_sub_mask.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_sub_mask.i1_focus_index;
                    if (pt_page_data->t_sub_mask.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_sub_mask.h_eb_ip_addr[pt_page_data->t_sub_mask.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_def_gateway.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_def_gateway.i1_focus_index;
                    if (pt_page_data->t_def_gateway.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_def_gateway.h_eb_ip_addr[pt_page_data->t_def_gateway.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_prim_dns.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_prim_dns.i1_focus_index;
                    if (pt_page_data->t_prim_dns.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_prim_dns.h_eb_ip_addr[pt_page_data->t_prim_dns.i1_focus_index];
                    }
                }
                else if (h_parent == pt_page_data->t_sec_dns.h_eb_fram)
                {
                    ui4_index = pt_page_data->t_sec_dns.i1_focus_index;
                    if (pt_page_data->t_sec_dns.i1_focus_index < 4)
                    {
                        h_focus = pt_page_data->t_sec_dns.h_eb_ip_addr[pt_page_data->t_sec_dns.i1_focus_index];
                    }

                }
                else
                {
                    i4_ret = a_digit_pad_hide(h_digit_handle);
                    MENU_LOG_ON_FAIL(i4_ret);
                    break;
                }
                //_page_ip_setting_eb_ip_style_clear_underline(h_widget);
                i4_ret = c_wgl_set_focus(h_focus, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                b_chg_bk = TRUE;
                //_page_ip_setting_eb_ip_style_add_underline(h_focus);

                c_memset(&nw_cur_ed_info,0,sizeof(nw_cur_ed_info));
                nw_cur_ed_info.h_eb_fram = h_parent;
                nw_cur_ed_info.i1_focus = h_focus;
                nw_cur_ed_info.h_eb_widget = h_widget;
                b_clear_pre = false;

                //show the digit pad
                i4_ret = a_digit_pad_show(h_digit_handle);
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret = a_digit_pad_focus(h_digit_handle);
                MENU_LOG_ON_FAIL(i4_ret);

                return i4_ret;

        case BTN_RETURN:
            menu_netowrk_nav_back();
            return MENUR_OK;
        default:
            break;
        }
    }
    default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_eb_clear_focusindex
 *
 * Description: clean the focus index of editbox
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _page_ip_setting_eb_clear_focusindex(VOID)
{
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    pt_page_data->t_ip_addr.i1_focus_index = 0;
    pt_page_data->t_sub_mask.i1_focus_index = 0;
    pt_page_data->t_def_gateway.i1_focus_index = 0;
    pt_page_data->t_prim_dns.i1_focus_index = 0;
    pt_page_data->t_sec_dns.i1_focus_index = 0;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_lb_addr_type_proc_fct
 *
 * Description: the callback function of DHCP on/off listbox widget
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_lb_addr_type_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2 )
{
    INT32                i4_ret = MENUR_OK;
    UINT16                ui2_mode = 0;
    PAGE_IP_SETTING_T*   pt_page_data = &t_page_ip_setting;
    UINT32 ui4_keycode = (UINT32)param1;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_AT_HELP));
    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_tts[128+1] = {0};

        menu_list_get_idx(pt_page_data->h_lb_addr_type, &ui2_mode);

        c_uc_w2s_strcpy(w2s_tts, MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_AT));
        c_uc_w2s_strcat(w2s_tts, L".");
        c_uc_w2s_strcat(w2s_tts, MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_AT_AUTO+ui2_mode));

        a_app_tts_play(w2s_tts, c_uc_w2s_strlen(w2s_tts));
    #endif
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                return i4_ret;
            case BTN_CURSOR_DOWN:
                menu_list_get_idx( pt_page_data->h_lb_addr_type,
                                        &ui2_mode);

                if(ui2_mode == 0)
                {
                    i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,TRUE);
                }
                else if (1 == ui2_mode)
                {
                    if (pt_page_data->t_ip_addr.i1_focus_index <4)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->t_ip_addr.h_eb_ip_addr[pt_page_data->t_ip_addr.i1_focus_index], TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_IP_EB_HELP));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                /* DNS only */
                else if (2 == ui2_mode)
                {
                    if (pt_page_data->t_ip_addr.i1_focus_index <4)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->t_prim_dns.h_eb_ip_addr[pt_page_data->t_prim_dns.i1_focus_index], TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_IP_EB_HELP));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                return i4_ret;
            case BTN_SELECT:
                i4_ret = MENUR_OK;
                menu_nav_go(ui4_page_ip_setting_dhcp, NULL);
                break;
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
                menu_async_invoke(_page_ip_setting_lb_addr_type_change_fct,
                                  (VOID*)&ui4_keycode, sizeof(UINT32), TRUE);
                return MENUR_OK;
            default:
                break;
        }
    }
    return _page_ip_setting_widget_default_proc_fct(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_lb_addr_type_create
 *
 * Description: create the listbox widget of "DHCP on/off"
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_lb_addr_type_create (PAGE_IP_SETTING_T* pt_page_data)
{
    INT32    i4_ret = MENUR_OK;

    i4_ret = menu_list_create(pt_page_data->h_cnt_frm,
                              0,
                              3,
                              _page_ip_setting_lb_addr_type_proc_fct,
                              &pt_page_data->h_lb_addr_type);

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_ip_style_eb_create
 *
 * Description: create the item of ip setting
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_ip_style_eb_create(
                            HANDLE_T            h_parent,
                            INT32               i4_index,
                            NW_IP4_ED_T*        pt_ip_eb
                            )
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;
    UINT8              ui1_col;

    WGL_EB_KEY_MAP_T    t_eb_key_map;
    UINT8               ui1_frame_alpha;
    UINT32          ui4_style;

    i4_ret = menu_get_osd_alpha (&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);


    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 ui1_frame_alpha,
                                 NULL,
                                 NULL,
                                 &(pt_ip_eb->h_eb_fram));
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_fram,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

/*---------------------------------------------------------------*/
    /*create text widget for diaplay title*/

    ui4_style = WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;


    SET_RECT_BY_SIZE(&t_rect,
                     IP4_EB_TITLE_TEXT_X,
                     IP4_EB_TITLE_TEXT_Y,
                     IP4_EB_TITLE_TEXT_W,
                     IP4_EB_TITLE_TEXT_H);

    i4_ret = c_wgl_create_widget(pt_ip_eb->h_eb_fram,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 ui1_frame_alpha,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_ip_eb->h_eb_text));
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }
    /* Set Cnt Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_text,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_text,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (pt_ip_eb->h_eb_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

/*---------------------------------------------------------*/
    /*create four edit box*/
    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         IP4_EB_TITLE_TEXT_X + IP4_EB_TITLE_TEXT_W + ui1_col*IP4_EB_W,
                         5*4/3,
                         IP4_EB_W - 5*4/3,
                         IP4_EB_TITLE_TEXT_H);


        i4_ret = c_wgl_create_widget(pt_ip_eb->h_eb_fram,
                                    HT_WGL_WIDGET_EDIT_BOX,
                                    WGL_CONTENT_EDIT_BOX_DEF,
                                    WGL_BORDER_TIMG,
                                    &t_rect,
                                    _page_ip_setting_editbox_proc_fct,
                                    ui1_frame_alpha,
                                    (VOID*)WGL_STL_EB_MAX_CHAR_16,
                                    NULL,
                                    &pt_ip_eb->h_eb_ip_addr[ui1_col]);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Insets */
        t_inset.i4_left     = IP4_EB_INPUT_INSET_L;
        t_inset.i4_right    = IP4_EB_INPUT_INSET_R;
        t_inset.i4_top      = IP4_EB_INPUT_INSET_T;
        t_inset.i4_bottom   = IP4_EB_INPUT_INSET_B;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                                      WGL_CMD_GL_SET_INSET,
                                      &t_inset,
                                      NULL);
        MENU_LOG_ON_FAIL(i4_ret);


        /* Set Cnt Insets */
        t_inset.i4_left     = 0;
        t_inset.i4_right    = 5*4/3;
        t_inset.i4_top      = -15*4/3;
        t_inset.i4_bottom   = 3*4/3;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_EB_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set EB Alignment */
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_EB_SET_ALIGN,
                              WGL_PACK(WGL_AS_LEFT_CENTER),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
        t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
        t_fnt_info.e_font_style = MENU_ITEM_EDIT_FNT_STYLE;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (pt_ip_eb->h_eb_ip_addr[ui1_col],
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set txt color */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_bk2_txt_disable;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));

        /* Set background images */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable       =h_g_menu_img_text_entry_small;
        t_img_info.u_img_data.t_standard.t_highlight    = h_g_menu_img_text_entry_small;
        t_img_info.u_img_data.t_standard.t_disable      =h_g_menu_img_text_entry_small;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info ));
        MENU_LOG_ON_FAIL(i4_ret);

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bk1;
        t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_BDR_TIMG_SET_BK_IMG,
                              WGL_PACK(&t_img_info),
                              WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_EB_SET_INPUT_LIMIT,
                              WGL_PACK(IP4_EB_INPUT_LIMIT),
                              NULL);
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_EB_SET_EXT_ATTR,
                              WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                              WGL_PACK(WGL_EB_EA_AUTO_EDITING));

        i4_ret = c_wgl_do_cmd (pt_ip_eb->h_eb_ip_addr[ui1_col],
                               WGL_CMD_GL_SET_ATTACH_DATA,
                               WGL_PACK(ui1_col),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        c_memset(&t_eb_key_map,0,sizeof(WGL_EB_KEY_MAP_T));
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_EB_SET_KEY_MAP,
                              WGL_PACK(&t_eb_key_map),
                              NULL);

    }

    /*create text widget for diaplay "." */
    for(ui1_col= 0; ui1_col < 3; ui1_col++)
    {

        ui4_style = WGL_STL_GL_NO_IMG_UI;

        SET_RECT_BY_SIZE(&t_rect,
                         IP4_EB_TITLE_TEXT_X + IP4_EB_TITLE_TEXT_W + IP4_EB_W + ui1_col*IP4_EB_W - 5*4/3 ,
                         5*4/3,
                         5*4/3,
                         IP4_EB_TITLE_TEXT_H);

        i4_ret = c_wgl_create_widget(pt_ip_eb->h_eb_fram,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     ui1_frame_alpha,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &(pt_ip_eb->h_ip_dot[ui1_col]));
        if (i4_ret < 0)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }

        /* Set Alignment */
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_ip_dot[ui1_col],
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (pt_ip_eb->h_ip_dot[ui1_col],
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Color */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_ip_dot[ui1_col],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
        MENU_LOG_ON_FAIL(i4_ret);

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_transp;
        t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_transp;
        t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_transp;
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_ip_dot[ui1_col],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info ));
        MENU_LOG_ON_FAIL(i4_ret);

       i4_ret = c_wgl_do_cmd(pt_ip_eb->h_ip_dot[ui1_col],
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK("."),
                              WGL_PACK(1));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_ip_eb->h_ip_dot[ui1_col],WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_mac_info_create
 *
 * Description: create widgets for diaplay mac info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_mac_info_create(HANDLE_T h_parent,
                                                    HANDLE_T* p_mac_info,
                                                    INT32   i4_index)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    UINT8               ui1_frame_alpha;
    UINT32          ui4_style;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    GL_RECT_T           t_fm_border_title = {
                    FRAME_LEFT_RIGHT_INTV,
                    0,
                    MENU_ITEM_V_TITLE_W,
                    MENU_ITEM_V_HEIGHT};

    i4_ret = menu_get_osd_alpha (&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);

    /*create text widget for diaplay title*/

     ui4_style = WGL_STL_GL_BDR_FILL_CNT_BK
                 | WGL_STL_TEXT_MAX_128;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

     i4_ret = c_wgl_create_widget(pt_page_data->h_cnt_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TIMG,
                                  &t_rect,
                                  NULL,
                                  ui1_frame_alpha,
                                  (VOID*)ui4_style,
                                  NULL,
                                  p_mac_info);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }
    /* Set Insets */
    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV + MENU_ITEM_V_TITLE_W;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*p_mac_info,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    c_strcpy(t_title_info.t_font.a_c_font_name, menu_font_name());
    t_title_info.t_font.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_title_info.t_font.e_font_style = MENU_ITEM_FNT_STYLE;
    t_title_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_title_info.t_rc_ref = t_fm_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*p_mac_info,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(*p_mac_info,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*p_mac_info,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*p_mac_info,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_RIGHT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*p_mac_info,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*p_mac_info,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

     return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_ip_style_eb_chg_lang
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
static INT32 _page_ip_setting_ip_style_eb_chg_lang(
                    NW_IP4_ED_T t_ip_eb,
                    UINT16      ui2_msgid_title
                    )
{
    INT32    i4_ret = MENUR_OK;

    i4_ret = c_wgl_do_cmd(t_ip_eb.h_eb_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(c_uc_w2s_strlen(
                            MENU_TEXT(ui2_msgid_title))));

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_chg_lang
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
static INT32 _page_ip_setting_chg_lang(PAGE_IP_SETTING_T * pt_page_data)
{
    INT32 i4_ret = MENUR_OK;

    i4_ret = menu_list_chg_lang(pt_page_data->h_lb_addr_type,
                           MLM_MENU_KEY_NET_CFG_AT,
                           MLM_MENU_KEY_NET_CFG_AT_AUTO,
                           MLM_MENU_KEY_NET_CFG_AT_DNS_ONLY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_chg_lang(pt_page_data->t_ip_addr,
                       MLM_MENU_KEY_NET_CFG_IP_ADDRESS);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_chg_lang(pt_page_data->t_sub_mask,
                       MLM_MENU_KEY_NET_CFG_SUB_MASK);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_chg_lang(pt_page_data->t_def_gateway,
                       MLM_MENU_KEY_NET_CFG_DEF_GW);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_chg_lang(pt_page_data->t_prim_dns,
                       MLM_MENU_KEY_NET_CFG_PRI_DNS);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_chg_lang(pt_page_data->t_sec_dns,
                       MLM_MENU_KEY_NET_CFG_SEC_DNS);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_do_cmd(pt_page_data->h_ethernet_mac,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_MAC_ADDR)),
                          WGL_PACK(c_uc_w2s_strlen(
                            MENU_TEXT(MLM_MENU_KEY_NET_MAC_ADDR))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_wireless_mac,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_WIRELESS_MAC_ADDR)),
                          WGL_PACK(c_uc_w2s_strlen(
                            MENU_TEXT(MLM_MENU_KEY_NET_WIRELESS_MAC_ADDR))));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#define DUMP_ADDR(prefix,addr) \
do{\
    DBG_LOG_PRINT(("%s:%d.%d.%d.%d\n",prefix,(addr&0xff),(addr&0xff00)>>8,(addr&0xff0000)>>16,(addr&0xff000000)>>24));\
}while(0)

static INT32 _update_ip_setting_info()
{
    UTF16_T            w2s_temp_str[64];
    CHAR               s_temp_str[64];
    NW_IP_INFO_T       t_ip_info;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    c_memset(&t_ip_info, 0, sizeof(t_ip_info));

    MENU_LOG_ON_FAIL(a_nw_get_crnt_ip_info(&t_ip_info));

    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_ip_addr), t_ip_info.ui4_address);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_sub_mask), t_ip_info.ui4_netmask);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_def_gateway),t_ip_info.ui4_gw);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_prim_dns), t_ip_info.ui4_1st_dns);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_sec_dns), t_ip_info.ui4_2nd_dns);

    /* update ethernet mac */
    c_memset (s_temp_str, 0, sizeof(CHAR)*64);
    c_memset (w2s_temp_str,0,sizeof(UTF16_T)*64);

    a_nw_get_mac_addr_string(NI_ETHERNET_0, s_temp_str);

    c_uc_ps_to_w2s(s_temp_str,w2s_temp_str,sizeof(UTF16_T)*64);
    MENU_LOG_ON_FAIL(c_wgl_do_cmd(pt_page_data->h_ethernet_mac,
                                   WGL_CMD_TEXT_SET_TEXT,
                                   WGL_PACK(w2s_temp_str),
                                   WGL_PACK(c_uc_w2s_strlen(w2s_temp_str))
                                   ));
    /* update wireless mac */
    c_memset (s_temp_str, 0, sizeof(CHAR)*64);
    c_memset (w2s_temp_str,0,sizeof(UTF16_T)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0, s_temp_str);

    c_uc_ps_to_w2s(s_temp_str,w2s_temp_str,sizeof(UTF16_T)*64);
    MENU_LOG_ON_FAIL(c_wgl_do_cmd(pt_page_data->h_wireless_mac,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(w2s_temp_str),
                                  WGL_PACK(c_uc_w2s_strlen(w2s_temp_str))
                                  ));
    return MENUR_OK;
}
 /*----------------------------------------------------------------------------
  * Name: _page_ip_setting_update_data
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
 static INT32 _page_ip_setting_update_data(PAGE_IP_SETTING_T* pt_page_data)
 {
    BOOL            b_auto_ip = FALSE;
    NW_DHCP_STATE_T e_dhcp_state;
    INT32           i4_ret;
    UINT16          ui2_idx = MENU_UI_DHCP_ON;
    UINT8           ui1_dhcp_status = ACFG_DHCP_OFF;

    i4_ret = nw_custom_get_auto_ip_config(&b_auto_ip);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_auto_ip)
    {
        ui2_idx = MENU_UI_DHCP_ON;
    }
    else
    {
        if (CFGR_OK == nw_custom_get_dhcp_status(&ui1_dhcp_status))
        {
            if (ACFG_DHCP_OFF == ui1_dhcp_status)
            {
                ui2_idx = MENU_UI_DHCP_OFF;
            }
            else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
            {
                ui2_idx = MENU_UI_DHCP_DNS_ONLY;
            }
        }
    }

    menu_list_set_idx( pt_page_data->h_lb_addr_type,ui2_idx);
    menu_list_adjust_rect(pt_page_data->h_lb_addr_type);

    if (b_auto_ip)
    {
        if(i4_ret == NWR_DHCP_NO_ADDR)
        {
            DBG_INFO(("[IP Setting]%s:%d,return: %d.\n",__FUNCTION__,__LINE__,i4_ret));
        }

        i4_ret = a_nw_get_dhcp_status(&e_dhcp_state);
        DBG_INFO(("[ip setting]---------%s:%d,DHCP status: %d.\n", __FUNCTION__, __LINE__, e_dhcp_state));
        if (e_dhcp_state != NW_DHCP_STARTED)
        {
            MENU_LOG_ON_FAIL(a_nw_start_dhcp_ip_config());
        }
    }
    _update_ip_setting_info();

    /* update ui color */
    _page_ip_setting_update_clr_with_state(ui2_idx);

    return i4_ret;
 }

 /*----------------------------------------------------------------------------
  * Name: _page_ip_setting_set_ip4_eb_str
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
static INT32 _page_ip_setting_set_ip4_eb_str(
                               NW_IP4_ED_T*  pt_ip_eb,
                               UINT32        ui4_ip
                               )
{
    INT32         i4_ret = MENUR_OK;
    UTF16_T       w2s_data[5] = {0};
    UTF16_T       w2s_data_old[5] = {0};
    CHAR          char_data[5]= {0};
    UINT8         ui1_col = 0;
    UINT8         ui1_str_len = 0;
    UINT8         ui1_str_len_old = 0;
    UINT16        ui2_mode = 0;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    HANDLE_T        h_widget=NULL_HANDLE;

    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        c_memset(char_data,0,sizeof(CHAR) * 5);
        c_sprintf( char_data,("%d"), (ui4_ip>>(8*ui1_col))&0xFF);

        c_uc_ps_to_w2s (char_data,w2s_data, 5* sizeof(UTF16_T));
        if(pt_ip_eb->i1_focus_index == ui1_col)
        {
            c_wgl_get_focus(&h_widget);
            if(h_widget == pt_ip_eb->h_eb_ip_addr[ui1_col])
            {
                menu_list_get_idx(pt_page_data->h_lb_addr_type,
                                     &ui2_mode);
                if((MENU_UI_DHCP_OFF == ui2_mode) || (MENU_UI_DHCP_DNS_ONLY == ui2_mode))
                {
                    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                                      WGL_CMD_EB_GET_TEXT,
                                      WGL_PACK(w2s_data_old),
                                      WGL_PACK(5));
                    MENU_LOG_ON_FAIL(i4_ret);
                    ui1_str_len_old = (UINT32) c_uc_w2s_strlen(w2s_data_old);

                    if(w2s_data_old[ui1_str_len_old-1] == (UTF16_T)('_'))
                    {
                        ui1_str_len = (UINT32) c_uc_w2s_strlen(w2s_data);
                        c_uc_w2s_set(w2s_data,ui1_str_len > 3 ? 3 : ui1_str_len,(UTF16_T)('_'));
                        ui1_str_len = ui1_str_len+1;
                        c_uc_w2s_set(w2s_data,ui1_str_len > 4 ? 4 : ui1_str_len,(UTF16_T)('\0'));
                    }
                }
            }
        }
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_EB_SET_TEXT,
                              WGL_PACK(w2s_data),
                              WGL_PACK(c_uc_w2s_strlen(w2s_data)));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    c_wgl_repaint(pt_ip_eb->h_eb_fram,NULL,TRUE);
    return MENUR_OK;
}

static INT32 _page_ip_setting_grayout_ip4_eb_str(
                               NW_IP4_ED_T*  pt_ip_eb
                               )
{
    INT32         i4_ret = MENUR_OK;
    UINT8         ui1_col = 0;
    WGL_COLOR_INFO_T    t_clr_info;
    GL_COLOR_T t_menu_color_gray = { 255, { 128 }, { 128 }, { 128 }};

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_menu_color_gray;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_menu_color_gray;
    t_clr_info.u_color_data.t_standard.t_disable      = t_menu_color_gray;

    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);


    for (ui1_col = 0; ui1_col < 4; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _page_ip_setting_white_ip4_eb_str(
                               NW_IP4_ED_T*  pt_ip_eb
                               )
{
    INT32         i4_ret = MENUR_OK;
    UINT8         ui1_col = 0;
    WGL_COLOR_INFO_T    t_clr_info;
    GL_COLOR_T t_menu_color_gray = { 255, { 255 }, { 255 }, { 255 }};

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_menu_color_gray;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_menu_color_gray;
    t_clr_info.u_color_data.t_standard.t_disable      = t_menu_color_gray;

    i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_text,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd(pt_ip_eb->h_eb_ip_addr[ui1_col],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _page_ip_setting_update_clr_with_state(UINT16 ui2_status)
{
    INT32               i4_ret = APP_CFGR_OK;
    PAGE_IP_SETTING_T*  pt_page_data = &t_page_ip_setting;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_COLOR_INFO_T    t_clr_info_btn;

    /* update ip address editbox color */
    if (MENU_UI_DHCP_ON == ui2_status)
    {
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_ip_addr));
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_sub_mask));
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_def_gateway));
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_prim_dns));
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_sec_dns));
    }
    else if (MENU_UI_DHCP_OFF == ui2_status)
    {
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_ip_addr));
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_sub_mask));
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_def_gateway));
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_prim_dns));
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_sec_dns));
    }
    else if (MENU_UI_DHCP_DNS_ONLY == ui2_status)
    {
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_ip_addr));
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_sub_mask));
        _page_ip_setting_grayout_ip4_eb_str(&(pt_page_data->t_def_gateway));
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_prim_dns));
        _page_ip_setting_white_ip4_eb_str(&(pt_page_data->t_sec_dns));
    }
    else
    {
        /* do nothing */
    }

    /* update ip address editbox color */
    if (0 == ui2_status)
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_bk1_txt_disable;
        t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1_txt_disable;
        t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk1_txt_disable;
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_bk1_txt;
        t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1_txt;
        t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk1_txt;
    }

    /* set title color */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_ethernet_mac,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_ethernet_mac,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_wireless_mac,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_wireless_mac,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set content color */
    if (0 == ui2_status)
    {
        t_clr_info_btn.e_type = WGL_COLOR_SET_EXTEND;
        t_clr_info_btn.u_color_data.t_extend.t_enable = t_g_menu_color_bk1_txt_disable;
        t_clr_info_btn.u_color_data.t_extend.t_disable = t_g_menu_color_bk1_txt_disable;
        t_clr_info_btn.u_color_data.t_extend.t_highlight = t_g_menu_color_bk1_txt_disable;
        t_clr_info_btn.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_bk1_txt_disable;
        t_clr_info_btn.u_color_data.t_extend.t_push = t_g_menu_color_bk1_txt_disable;
        t_clr_info_btn.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_bk1_txt_disable;
    }
    else
    {
        t_clr_info_btn.e_type = WGL_COLOR_SET_EXTEND;
        t_clr_info_btn.u_color_data.t_extend.t_enable = t_g_menu_color_bk1_txt;
        t_clr_info_btn.u_color_data.t_extend.t_disable = t_g_menu_color_bk1_txt;
        t_clr_info_btn.u_color_data.t_extend.t_highlight = t_g_menu_color_bk1_txt;
        t_clr_info_btn.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_bk1_txt;
        t_clr_info_btn.u_color_data.t_extend.t_push = t_g_menu_color_bk1_txt;
        t_clr_info_btn.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_bk1_txt;
    }

    i4_ret = c_wgl_do_cmd(pt_page_data->h_btn_save,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info_btn));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_btn_cancel,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info_btn));
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_repaint(pt_page_data->h_btn_save,NULL,TRUE);
    c_wgl_repaint(pt_page_data->h_btn_cancel,NULL,TRUE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    PAGE_IP_SETTING_T* pt_this = &t_page_ip_setting;
    INT32       i4_ret = MENUR_OK;

    if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
            menu_netowrk_nav_back();
            return MENUR_OK ;

        case BTN_CURSOR_RIGHT :
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus (pt_this->h_lb_addr_type, WGL_SYNC_AUTO_REPAINT);

            /* update help tip */
            i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_AT_HELP));
            MENU_LOG_ON_FAIL(i4_ret);
            break ;

        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;

        case BTN_RETURN:
            menu_netowrk_nav_back();
            return MENUR_OK ;

        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}
static INT32 _update_ip_setting_info_opt(NW_IP_INFO_T       t_ip_info)
{
    UTF16_T            w2s_temp_str[64];
    CHAR               s_temp_str[64];

    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    //c_memset(&t_ip_info, 0, sizeof(t_ip_info));

    //MENU_LOG_ON_FAIL(a_nw_get_crnt_ip_info(&t_ip_info));

    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_ip_addr), t_ip_info.ui4_address);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_sub_mask), t_ip_info.ui4_netmask);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_def_gateway),t_ip_info.ui4_gw);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_prim_dns), t_ip_info.ui4_1st_dns);
    _page_ip_setting_set_ip4_eb_str(&(pt_page_data->t_sec_dns), t_ip_info.ui4_2nd_dns);

    /* update ethernet mac */
    c_memset (s_temp_str, 0, sizeof(CHAR)*64);
    c_memset (w2s_temp_str,0,sizeof(UTF16_T)*64);

    a_nw_get_mac_addr_string(NI_ETHERNET_0, s_temp_str);

    c_uc_ps_to_w2s(s_temp_str,w2s_temp_str,sizeof(UTF16_T)*64);
    MENU_LOG_ON_FAIL(c_wgl_do_cmd(pt_page_data->h_ethernet_mac,
                                   WGL_CMD_TEXT_SET_TEXT,
                                   WGL_PACK(w2s_temp_str),
                                   WGL_PACK(c_uc_w2s_strlen(w2s_temp_str))
                                   ));
    /* update wireless mac */
    c_memset (s_temp_str, 0, sizeof(CHAR)*64);
    c_memset (w2s_temp_str,0,sizeof(UTF16_T)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0, s_temp_str);

    c_uc_ps_to_w2s(s_temp_str,w2s_temp_str,sizeof(UTF16_T)*64);
    MENU_LOG_ON_FAIL(c_wgl_do_cmd(pt_page_data->h_wireless_mac,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(w2s_temp_str),
                                  WGL_PACK(c_uc_w2s_strlen(w2s_temp_str))
                                  ));
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_lb_addr_type_change_fct
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
static VOID _page_ip_setting_lb_addr_type_change_fct(VOID* pv_data,
                                                            SIZE_T  z_data_size)
{
    INT32           i4_ret = MENUR_OK;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    UINT16             ui2_mode = 0;
    UINT16             ui2_next = 0;
    NW_IP_INFO_T       t_ip_info;
    UINT32             ui4_key_code = *(UINT32*)pv_data;

    /* 0 DHCP on
       1 DHCP off
       2 DHCP off DNS only */
    menu_list_get_idx(pt_page_data->h_lb_addr_type,
                     &ui2_mode);

    DBG_INFO(("<NETWORK>2245,ui2_mode=%d\n", ui2_mode));

    if (BTN_CURSOR_LEFT == ui4_key_code)
    {
        if (MENU_UI_DHCP_ON == ui2_mode)
        {
            ui2_next = MENU_UI_DHCP_DNS_ONLY;
        }
        else if (MENU_UI_DHCP_OFF == ui2_mode)
        {
            ui2_next = MENU_UI_DHCP_ON;

            //Jundi the digit pad
            i4_ret = a_digit_pad_hide(h_digit_handle);
            MENU_LOG_ON_FAIL(i4_ret);

        }
        else
        {
            ui2_next = MENU_UI_DHCP_OFF;
        }
    }
    else if (BTN_CURSOR_RIGHT == ui4_key_code)
    {
        if (MENU_UI_DHCP_ON == ui2_mode)
        {
            ui2_next = MENU_UI_DHCP_OFF;
        }
        else if (MENU_UI_DHCP_OFF == ui2_mode)
        {
            ui2_next = MENU_UI_DHCP_DNS_ONLY;
        }
        else
        {
            ui2_next = MENU_UI_DHCP_ON;
            //Jun add the digit pad
            i4_ret = a_digit_pad_hide(h_digit_handle);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    DBG_LOG_PRINT(("[NW][%s %d],ui2_next=%d\n",__FUNCTION__,__LINE__, ui2_next));

    menu_list_set_idx(pt_page_data->h_lb_addr_type,
                     ui2_next);
    menu_list_adjust_rect(pt_page_data->h_lb_addr_type);
    c_wgl_repaint(pt_page_data->h_lb_addr_type,NULL,TRUE);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_tts[128+1] = {0};

    c_uc_w2s_strcpy(w2s_tts, MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_AT_AUTO+ui2_next));

    a_app_tts_play(w2s_tts, c_uc_w2s_strlen(w2s_tts));
#endif

    c_memset(&t_ip_info, 0, sizeof(t_ip_info));

    if (ui2_next == MENU_UI_DHCP_ON)
    {
        MENU_LOG_ON_FAIL(a_nw_start_dhcp_ip_config());

        MENU_LOG_ON_FAIL(nw_custom_set_dhcp_status(ACFG_DHCP_OFF));

        menu_page_animation_start(6, FALSE);
        menu_page_animation_show();
        b_page_ip_chg = FALSE;
    }
    else
    {
        MENU_LOG_ON_FAIL(a_nw_get_crnt_ip_info(&t_ip_info));

        MENU_LOG_ON_FAIL(nw_custom_set_dhcp_status(ui2_next == MENU_UI_DHCP_OFF ? ACFG_DHCP_OFF : ACFG_DHCP_DNS_ONLY));


        if (NWR_OK != (i4_ret = a_nw_manual_ip_config(&t_ip_info)))
        {
            DBG_ERROR(("[%s %d]failed to set manual ip config i4_ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
            MENU_LOG_ON_FAIL( nw_custom_set_auto_ip_config(FALSE));
        }

        MENU_LOG_ON_FAIL(menu_page_animation_stop());
        menu_page_animation_hide();
    }

    /* update ui color */
    _page_ip_setting_update_clr_with_state(ui2_next);
    //_update_ip_setting_info();
    _update_ip_setting_info_opt(t_ip_info);
}

INT32 menu_page_ip_setting_lb_addr_type_change_fct(UINT16 dhcp_value)
{
    INT32 i4_ret = MENUR_OK;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    NW_IP_INFO_T t_ip_info;

    DBG_LOG_PRINT(("[NW][%s %d],dhcp_value=%d\n",__FUNCTION__,__LINE__, dhcp_value));
    if(dhcp_value > MENU_UI_DHCP_DNS_ONLY)
    {
        DBG_LOG_PRINT(("[NW][%s %d] invalid parameter\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    menu_list_set_idx(pt_page_data->h_lb_addr_type,
                     dhcp_value);
    menu_list_adjust_rect(pt_page_data->h_lb_addr_type);
    c_wgl_repaint(pt_page_data->h_lb_addr_type,NULL,TRUE);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_tts[128+1] = {0};

    c_uc_w2s_strcpy(w2s_tts, MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_AT_AUTO+dhcp_value));

    a_app_tts_play(w2s_tts, c_uc_w2s_strlen(w2s_tts));
#endif

    c_memset(&t_ip_info, 0, sizeof(t_ip_info));

    if (dhcp_value == MENU_UI_DHCP_ON)
    {
        MENU_LOG_ON_FAIL(a_nw_start_dhcp_ip_config());

        MENU_LOG_ON_FAIL(nw_custom_set_dhcp_status(ACFG_DHCP_OFF));

        menu_page_animation_start(6, FALSE);
        menu_page_animation_show();
        b_page_ip_chg = FALSE;
    }
    else
    {
        MENU_LOG_ON_FAIL(a_nw_get_crnt_ip_info(&t_ip_info));

        MENU_LOG_ON_FAIL(nw_custom_set_dhcp_status(dhcp_value == MENU_UI_DHCP_OFF ? ACFG_DHCP_OFF : ACFG_DHCP_DNS_ONLY));


        if (NWR_OK != (i4_ret = a_nw_manual_ip_config(&t_ip_info)))
        {
            DBG_ERROR(("[%s %d]failed to set manual ip config i4_ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
            MENU_LOG_ON_FAIL( nw_custom_set_auto_ip_config(FALSE));
        }

        MENU_LOG_ON_FAIL(menu_page_animation_stop());
        menu_page_animation_hide();
    }

    /* update ui color */
    _page_ip_setting_update_clr_with_state(dhcp_value);
    //_update_ip_setting_info();
    _update_ip_setting_info_opt(t_ip_info);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_cnt_frm_proc_fct
 *
 * Description: the ip setting page callback function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_ip_setting_cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

#define _STR(s) #s

static VOID _nw_addr_change_fct(VOID* arg1,VOID* arg2,VOID* arg3 )
{
    _update_ip_setting_info();
}

VOID _nw_addr_change_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                          VOID*     pv_tag)
{
    menu_request_context_switch(_nw_addr_change_fct,NULL,NULL,NULL);
}

/*----------------------------------------------------------------------------
 * Name: _nw_notify_handler
 *
 * Description: use to deal with the notify messageo of network
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    MENU_NETWORK_NFY_DATA_T*   pt_nw_nfy_data = (MENU_NETWORK_NFY_DATA_T*)pv_data;

    DBG_LOG_PRINT(("[NW]network notify message: %d\n", pt_nw_nfy_data->e_nfy_id));
    switch(pt_nw_nfy_data->e_nfy_id)
    {
        case NW_NFY_ID_ADDRESS_CHANGED:
            DBG_LOG_PRINT(("[%s %d] %s\n",__FUNCTION__,__LINE__,_STR(NW_NFY_ID_ADDRESS_CHANGED)));
            MENU_LOG_ON_FAIL(c_timer_start(h_addr_delay_timer,
                                           1000,
                                           X_TIMER_FLAG_ONCE,
                                           _nw_addr_change_timer_cb_fct,
                                           NULL));
            return;
        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
             DBG_LOG_PRINT(("[%s %d] %s\n",__FUNCTION__,__LINE__,_STR(NW_NFY_ID_DHCP_SUCCESS_DHCPv4)));
             /* stop animation */
             menu_page_animation_stop();
             break;
        case NW_NFY_ID_ETHERNET_UNPLUG:
        case NW_NFY_ID_ETHERNET_PLUGIN:
            menu_nav_go_home_menu();
            return;
        case NW_NFY_ID_ADDRESS_EXPIRED:
        case NW_NFY_ID_DHCP_STOPPED:
            break;
        case NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL:
        case NW_NFY_ID_DHCP_FAILURE_LINKLOCAL:
            menu_page_animation_stop();
            break;
        default:
            return;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nw_notify_callback
 *
 * Description: network callback function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    MENU_NETWORK_NFY_DATA_T t_nw_nfy_data;

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_nw_notify_handler,&t_nw_nfy_data,sizeof(MENU_NETWORK_NFY_DATA_T),TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_animation_nfy
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

static VOID _page_ip_setting_animation_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    menu_page_animation_stop();
    menu_page_animation_hide();
}
/*----------------------------------------------------------------------------
 * Name: _page_ip_setting_animation_cb_fct
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

static INT32 _page_ip_setting_animation_cb_fct(HANDLE_T                h_widget,
                      UINT16                  ui2_anim_type,
                      WGL_ANIM_COND_INF_T     e_anim_cond,
                      VOID*                   pv_tag)
{
    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        menu_async_invoke(_page_ip_setting_animation_nfy, NULL, 0, TRUE);
    }

    return MENUR_OK;
}

static INT32 _ip_setting_save_ip(VOID)
{
    INT32       i4_ret = MENUR_OK;
    BOOL        b_save_setting = TRUE;

    if (b_page_ip_chg)
    {
        if (t_page_ip_info.ui4_address != 0 && t_page_ip_info.ui4_netmask != 0)
        {
            b_save_setting = TRUE;
        }

        if (((t_page_ip_info.ui4_address & t_page_ip_info.ui4_netmask) == t_page_ip_info.ui4_address) ||
                 ((t_page_ip_info.ui4_address | (~t_page_ip_info.ui4_netmask)) == t_page_ip_info.ui4_address))
        {
            b_save_setting = FALSE;
        }

        if (t_page_ip_info.ui4_gw != 0)
        {
            if(((t_page_ip_info.ui4_gw & t_page_ip_info.ui4_netmask) == t_page_ip_info.ui4_gw) ||
                ((t_page_ip_info.ui4_gw | ~t_page_ip_info.ui4_netmask) == t_page_ip_info.ui4_gw))
             {
                 b_save_setting = FALSE;
             }

            if( (t_page_ip_info.ui4_address & t_page_ip_info.ui4_netmask) != (t_page_ip_info.ui4_gw & t_page_ip_info.ui4_netmask))
            {
                b_save_setting = FALSE;
            }
        }

        DBG_LOG_PRINT(("[NW][%s %d]ui4_address = 0x%x, ui4_gw = 0x%x,ui4_netmask = 0x%x,ui4_1st_dns = 0x%x,ui4_2nd_dns = 0x%x\n",__FUNCTION__,__LINE__,
        t_page_ip_info.ui4_address,
        t_page_ip_info.ui4_gw,
        t_page_ip_info.ui4_netmask,
        t_page_ip_info.ui4_1st_dns,
        t_page_ip_info.ui4_2nd_dns));

        if (b_save_setting)
        {
             menu_page_animation_start(6, FALSE);
             menu_page_animation_show();
            if( !a_nw_custom_is_IP_exist(t_page_ip_info.ui4_address) ) /* check if this IP is exist or not*/
            {
                MENU_LOG_ON_FAIL(a_nw_manual_ip_config(&t_page_ip_info));
            }
            menu_page_animation_stop();
            menu_page_animation_hide();
        }

        b_page_ip_chg = FALSE;
    }

    return i4_ret;
}

static INT32 _ip_setting_btn_save_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
        #ifdef APP_TTS_SUPPORT
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_GAMMA_SAVE), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_GAMMA_SAVE)));
        #endif
        }
            break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    DBG_LOG_PRINT(("[NW][%s %d] b_page_ip_chg = %d\n",__FUNCTION__,__LINE__,b_page_ip_chg));
                    MENU_LOG_ON_FAIL(_ip_setting_save_ip());
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->t_sec_dns.h_eb_ip_addr[pt_page_data->t_sec_dns.i1_focus_index],
                                              WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_IP_EB_HELP));
                }
                    break;

                case BTN_CURSOR_RIGHT:
                case BTN_CURSOR_DOWN:
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_btn_cancel,
                                              WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_RETURN:
                {
                    menu_netowrk_nav_back();
                }
                    break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _ip_setting_btn_cancel_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
        #ifdef APP_TTS_SUPPORT
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_CNCL), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_CNCL)));
        #endif
        }
            break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    b_page_ip_chg = FALSE;

                    menu_netowrk_nav_back();

                    i4_ret = a_nw_start_dhcp_ip_config();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                    i4_ret = menu_help_tip_keytip_set_focus(pt_page_data->h_btn_cancel,0,FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_UP:
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_btn_save,
                                              WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_RETURN:
                {
                    menu_netowrk_nav_back();
                }
                    break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _ip_setting_btn_create(HANDLE_T h_parent,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    MENU_IP_SETTING_BTN_TYPE_T e_type,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    GL_COLOR_T          t_color_txt = { 255, { 255 }, { 255 }, { 255 }};

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    if (MENU_IP_SETTING_BTN_SAVE == e_type)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT * 8,
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
    }
    else if (MENU_IP_SETTING_BTN_CANCEL == e_type)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT * 9,
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
    }

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                pf_wdgt_proc,
                                255,
                                NULL,
                                NULL,
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left   = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right  = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable = t_color_txt;
    t_color_info.u_color_data.t_extend.t_disable = t_color_txt;
    t_color_info.u_color_data.t_extend.t_highlight = t_color_txt;
    t_color_info.u_color_data.t_extend.t_highlight_inactive = t_color_txt;
    t_color_info.u_color_data.t_extend.t_push = t_color_txt;
    t_color_info.u_color_data.t_extend.t_push_unhighlight = t_color_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(& t_color_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_strncpy(t_font_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_font_info.e_font_style = MENU_ITEM_FNT_STYLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pw2s_str),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ip_setting_show_btn(VOID)
{
    INT32           i4_ret = MENUR_OK;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_btn_save,
                      WGL_CMD_BTN_SET_TEXT,
                      WGL_PACK(MENU_TEXT(MLM_MENU_KEY_GAMMA_SAVE)),
                      WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_GAMMA_SAVE))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_btn_cancel,
                      WGL_CMD_BTN_SET_TEXT,
                      WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CNCL)),
                      WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_CNCL))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_btn_save,
                                   WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_btn_cancel,
                                   WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _on_page_create
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
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    pt_page_data->t_ip_addr.i1_focus_index = 0;
    pt_page_data->t_sub_mask.i1_focus_index = 0;
    pt_page_data->t_def_gateway.i1_focus_index = 0;
    pt_page_data->t_prim_dns.i1_focus_index = 0;
    pt_page_data->t_sec_dns.i1_focus_index = 0;

    c_memset(pt_page_data, 0, sizeof(PAGE_IP_SETTING_T));
    c_memset(&t_page_ip_info, 0, sizeof(t_page_ip_info));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_lb_addr_type_create(pt_page_data);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_create(pt_page_data->h_cnt_frm,
                                               COMMON_DATE_IP_ADDR_EB_IDX,
                                               &(pt_page_data->t_ip_addr));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_ip_style_eb_create(pt_page_data->h_cnt_frm,
                                                COMMON_DATE_SUB_MASK_EB_IDX,
                                                &(pt_page_data->t_sub_mask) );
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _page_ip_setting_ip_style_eb_create(pt_page_data->h_cnt_frm,
                                                COMMON_DATE_DEF_GATEWAY_EB_IDX,
                                                &(pt_page_data->t_def_gateway));
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _page_ip_setting_ip_style_eb_create(pt_page_data->h_cnt_frm,
                                                COMMON_DATE_PRIM_DNS_EB_IDX,
                                                &(pt_page_data->t_prim_dns) );
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _page_ip_setting_ip_style_eb_create(pt_page_data->h_cnt_frm,
                                                COMMON_DATE_SEC_DNS_EB_IDX,
                                                &(pt_page_data->t_sec_dns) );
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _page_ip_setting_mac_info_create(pt_page_data->h_cnt_frm,
                                               &(pt_page_data->h_ethernet_mac),
                                               6);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _page_ip_setting_mac_info_create(pt_page_data->h_cnt_frm,
                                               &(pt_page_data->h_wireless_mac),
                                               7);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _ip_setting_btn_create(pt_page_data->h_cnt_frm,
                                      _ip_setting_btn_save_proc_fct,
                                      MENU_IP_SETTING_BTN_SAVE,
                                      MENU_TEXT(MLM_MENU_KEY_GAMMA_SAVE),
                                      &pt_page_data->h_btn_save);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _ip_setting_btn_create(pt_page_data->h_cnt_frm,
                                      _ip_setting_btn_cancel_proc_fct,
                                      MENU_IP_SETTING_BTN_CANCEL,
                                      MENU_TEXT(MLM_MENU_KEY_CNCL),
                                      &pt_page_data->h_btn_cancel);
     MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _page_ip_setting_cnt_frm_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL(c_timer_create(&h_addr_delay_timer));

    //Jundi add the digit pad
    DIGIT_PAD_CONFIG        dhcp_digit_pad_cfg;
    i4_ret = menu_pm_get_root_frm(&h_crnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    a_digit_pad_init_config(&dhcp_digit_pad_cfg);
    dhcp_digit_pad_cfg.parent_frame = h_crnt_frm;
    dhcp_digit_pad_cfg.position.ui4_left = FRAME_W + 100;
    dhcp_digit_pad_cfg.position.ui4_top = 200;
    dhcp_digit_pad_cfg.btn_ok.b_enable = TRUE;
    dhcp_digit_pad_cfg.btn_ok.ui2_text_key = MLM_MENU_KEY_NEXT;

    dhcp_digit_pad_cfg.btn_cancel.b_enable = TRUE;
    dhcp_digit_pad_cfg.btn_cancel.ui2_text_key = MLM_MENU_KEY_CLOSE;
    dhcp_digit_pad_cfg.b_dash_key_enable = FALSE;
    dhcp_digit_pad_cfg.digit_key_event_nfy = dhcp_digit_pad_key_event_nfy;
    a_digit_pad_create(dhcp_digit_pad_cfg, &h_digit_handle);

    i4_ret = a_digit_pad_hide(h_digit_handle);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_destroy
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
static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    //Jundi add the digit pad
    INT32           i4_ret;

    i4_ret = a_digit_pad_destroy(h_digit_handle);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_show
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
static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;

    b_this_page_show = TRUE;
    /*if the ip addr value in editbox is changed or not*/
    b_page_ip_chg = FALSE;

#ifdef APP_TTS_SUPPORT
    h_g_eb_parent = NULL_HANDLE;
#endif

    c_memset(&t_page_ip_info, 0, sizeof(t_page_ip_info));

    /* update last shadow position first */
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_btn_cancel,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_ip_setting_chg_lang(pt_page_data);
    MENU_LOG_ON_FAIL(i4_ret);

    _page_ip_setting_update_data(pt_page_data);

    menu_main_set_title(MLM_MENU_KEY_NET_CFG_IP_SET);


    i4_ret = _ip_setting_show_btn();
    MENU_LOG_ON_FAIL(i4_ret);
    MENU_LOG_ON_FAIL( c_wgl_set_visibility(t_page_ip_setting.h_cnt_frm,WGL_SW_RECURSIVE));

    _page_ip_setting_eb_clear_focusindex();

    /*network  callback function*/
    i4_ret = a_nw_register(_nw_notify_callback, (VOID*)pt_page_data, &ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    return  i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_hide
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
static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    PAGE_IP_SETTING_T* pt_page_data = &t_page_ip_setting;
    INT32    i4_ret = MENUR_OK;

    i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                    WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*unregister network message callback*/
    i4_ret = a_nw_unregister(ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    //Jundi add the digit pad
    i4_ret = a_digit_pad_hide(h_digit_handle);
    MENU_LOG_ON_FAIL(i4_ret);

    b_this_page_show = FALSE;

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_get_focus
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
static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T * pt_hint)
{
    GL_RECT_T       t_rect = {0};
    HANDLE_T        h_menu_animation = NULL_HANDLE;

    menu_common_help_show_back();

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);


    SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                     CONTENT_Y,
                     ICON_ANIMATION_W,
                     ICON_ANIMATION_H);

    menu_page_animation_get_handle(&h_menu_animation);
    c_wgl_move(h_menu_animation, &t_rect, FALSE);
    menu_page_animation_set_callback_fct(_page_ip_setting_animation_cb_fct, NULL);
    c_wgl_set_focus(t_page_ip_setting.h_lb_addr_type,WGL_NO_AUTO_REPAINT);

    UINT16  ui2_idx;
    NW_DHCP_STATE_T     e_dhcp_state;
    menu_list_get_idx(t_page_ip_setting.h_lb_addr_type,
                     &ui2_idx);
    a_nw_get_dhcp_status(&e_dhcp_state);

    if (ui2_idx == 0 && e_dhcp_state == NW_DHCP_STARTING )
    {
        menu_page_animation_start(6, FALSE);
    }


    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_lose_focus
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

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    //Jundi for DTV02326414, just one case to save the change when press the "save" key
#ifdef NEVER
    if (b_page_ip_chg)
    {
        i4_ret = _page_ip_setting_eb_save_ip_addr();
        MENU_LOG_ON_FAIL(i4_ret);

        _ip_setting_save_ip();
    }
#endif

    c_wgl_set_visibility(t_page_ip_setting.h_cnt_frm,
                        WGL_SW_HIDE_RECURSIVE);
    /* clean callback function of backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /* stop animation */
    menu_page_animation_stop();

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_update
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
static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    c_wgl_repaint(t_page_ip_setting.h_lb_addr_type,NULL,TRUE);
    return MENUR_OK;
}
extern VOID menu_common_page_ip_settings_on_repaint(VOID)
{
    if (b_this_page_show)
    {
        c_wgl_repaint(t_page_ip_setting.h_lb_addr_type, NULL, TRUE);
    }
}
/*----------------------------------------------------------------------------
 * Name: menu_page_ip_setting_init
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
extern INT32 menu_common_page_ip_setting_init(VOID)
{
    INT32   i4_ret;

    /*init DHCP Listbox page*/
    i4_ret = menu_common_page_ip_setting_dhcp_init();
    MENU_LOG_ON_FAIL(i4_ret);

    /*create DHCP Listbox page*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_ip_setting_dhcp,
                                 NULL,
                                 &ui4_page_ip_setting_dhcp);
    MENU_LOG_ON_FAIL(i4_ret);

    t_g_menu_common_ip_setting.pf_menu_page_create = _on_page_create;
    t_g_menu_common_ip_setting.pf_menu_page_destroy = _on_page_destroy;
    t_g_menu_common_ip_setting.pf_menu_page_show= _on_page_show;
    t_g_menu_common_ip_setting.pf_menu_page_hide = _on_page_hide;
    t_g_menu_common_ip_setting.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_common_ip_setting.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_ip_setting.pf_menu_page_update = _on_page_update;

    return MENUR_OK;
}


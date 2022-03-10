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
 * $RCSfile: banner_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "app_util/a_cli_app.h"

#include "banner.h"
#include "res/nav/nav_dbg.h"

//#include "banner_common.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_cfg.h"
#include "res/nav/input_src/input_src_list_rc.h"
#include "nav/input_src/input_src_list.h"

#include "res/menu2/a_menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_tv.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/c4tv_apron.h"
#endif


#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"

extern BOOL banner_view_set_b_ctrl_show_flag(BOOL val);
extern BOOL banner_view_get_b_ctrl_show_flag(VOID);
extern INT32 banner_mm_try(VOID);



/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/
#ifdef SYS_MTKTVAPI_SUPPORT
BOOL gb_mtktvapi_banner_log_enable = FALSE;
#endif

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
static INT32 _banner_cli_cmd (INT32 i4_argc, const CHAR** pps_argv) ;
static INT32 _banner_cli_cmd_show_sidebar (INT32 i4_argc, const CHAR** pps_argv) ;
static INT32 _banner_cli_cmd_print_item (INT32 i4_argc, const CHAR** pps_argv) ;

static INT32 _banner_cli_mi_mm_test (INT32 i4_argc, const CHAR** pps_argv) ;
static INT32 _banner_cli_change_vlog (INT32 i4_argc, const CHAR** pps_argv) ;
static INT32 _banner_cli_set_ctrl_show_switch (INT32 i4_argc, const CHAR** pps_argv) ;
static INT32 _banner_cli_get_ctrl_show_switch (INT32 i4_argc, const CHAR** pps_argv) ;
static INT32 banner_try_get(INT32 i4_argc, const CHAR** pps_argv);




#ifdef SYS_MTKTVAPI_SUPPORT
static INT32 _banner_mtktvapi_log_cli_cmd (INT32 i4_argc, const CHAR** pps_argv) ;
#endif

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
static CLI_EXEC_T at_banner_cmd_tbl[] =
{
    {
        "log",
        "l",
        _banner_cli_cmd,
        NULL,
        "usage: log [s][i][v][m]",
        NAV_CLI_ACCESS_RIGHT_LVL
    },

#ifdef SYS_MTKTVAPI_SUPPORT
    {
        "log_print",
        "lp",
        _banner_mtktvapi_log_cli_cmd,
        NULL,
        "usage: mtktvapi banner log print [0|1]",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
#endif
    {
        "change vlog level",
        "cvl",
        _banner_cli_change_vlog,
        NULL,
        "usage: cvl [0/1/2/3]",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
        "show sidebar logo",
        "ssl",
        _banner_cli_cmd_show_sidebar,
        NULL,
        "usage: ssl [0/1/2/3]",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
        "print item",
        "pi",
        _banner_cli_cmd_print_item,
        NULL,
        "usage: pi [ALL/...]",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
        "print mi_mm",
        "pmm",
        _banner_cli_mi_mm_test,
        NULL,
        "usage: pmm ",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
        "set ctrl sw",
        "scss",
        _banner_cli_set_ctrl_show_switch,
        NULL,
        "usage: scss 0/1 ",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
        "get ctrl sw",
        "gcss",
        _banner_cli_get_ctrl_show_switch,
        NULL,
        "usage: gcss ",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
        "mm_try_get",
        "mmtg",
        banner_try_get,
        NULL,
        "usage: mmtg ",
        NAV_CLI_ACCESS_RIGHT_LVL
    },

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_banner_entry =
{
    "banner",
    "b",
    NULL,
    at_banner_cmd_tbl,
    "Commands for Display banner informations (c4tv)",
    NAV_CLI_ACCESS_RIGHT_LVL
};


/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/
#ifdef SYS_MTKTVAPI_SUPPORT
static INT32 _banner_mtktvapi_log_cli_cmd (INT32 i4_argc, const CHAR** pps_argv)
{
    const CHAR* ps = NULL;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: log_print [0|1]")) ;
        return NAVR_OK ;
    }

    ps = pps_argv[1] ;

    if (!ps)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    if(*ps == '0')
    {
        gb_mtktvapi_banner_log_enable = FALSE;
        DBG_LOG_PRINT(("\n Disable Mtktvapi banner log!")) ;
    }
    else if(*ps == '1')
    {
        gb_mtktvapi_banner_log_enable = TRUE;
        DBG_LOG_PRINT(("\n Enable Mtktvapi banner log!")) ;
    }
    else
    {
        DBG_LOG_PRINT(("\n usage: log_print [0|1]\n")) ;
    }


    return NAVR_OK ;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _banner_cli_cmd
 *
 * Description: This API is used to do cli cmd for banner
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _banner_cli_cmd (
    INT32                       i4_argc,
    const CHAR**                pps_argv
    )
{
    INT16                       i2_log_type = 0 ;
    const CHAR*                 ps = NULL ;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: log [-/s/i/v/m]")) ;
        DBG_LOG_PRINT(("\n        - -> NONE ")) ;
        DBG_LOG_PRINT(("\n        s -> state ")) ;
        DBG_LOG_PRINT(("\n        i -> item ")) ;
        DBG_LOG_PRINT(("\n        v -> view ")) ;
        DBG_LOG_PRINT(("\n        m -> message ")) ;
        DBG_LOG_PRINT(("\n        l -> location ")) ;
        DBG_LOG_PRINT(("\n        o -> other infor ")) ;
        DBG_LOG_PRINT(("\n---------- -----------\ncurrent = ")) ;

        i2_log_type = banner_get_log_type () ;

        if (i2_log_type == 0)
        {
            DBG_LOG_PRINT(("NONE")) ;
        }
        else
        {
            if (i2_log_type & _BANNER_LOG_TYPE_STATE)
            {
                DBG_LOG_PRINT(("s")) ;
            }
            if (i2_log_type & _BANNER_LOG_TYPE_ITEM)
            {
                DBG_LOG_PRINT(("i")) ;
            }
            if (i2_log_type & _BANNER_LOG_TYPE_VIEW)
            {
                DBG_LOG_PRINT(("v")) ;
            }
            if (i2_log_type & _BANNER_LOG_TYPE_MESSAGE)
            {
                DBG_LOG_PRINT(("m")) ;
            }
            if (i2_log_type & _BANNER_LOG_TYPE_LOCATION)
            {
                DBG_LOG_PRINT(("l")) ;
            }
            if (i2_log_type & _BANNER_LOG_TYPE_OTH_INFO)
            {
                DBG_LOG_PRINT(("o")) ;
            }
        }

        return NAVR_OK ;
    }

    ps = pps_argv[1] ;

    if (!ps)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    i2_log_type = 0 ;

    while (*ps)
    {
        if (*ps == '-')
        {
            i2_log_type = 0 ;
            return NAVR_OK ;
        }

        if (*ps == 's'|| *ps =='S')
        {
            i2_log_type |= _BANNER_LOG_TYPE_STATE ;
        }

        if (*ps == 'i' || *ps == 'I')
        {
            i2_log_type |= _BANNER_LOG_TYPE_ITEM ;
        }

        if (*ps == 'v' || *ps == 'V')
        {
            i2_log_type |= _BANNER_LOG_TYPE_VIEW ;
        }

        if (*ps == 'm' || *ps == 'M')
        {
            i2_log_type |= _BANNER_LOG_TYPE_MESSAGE ;
        }

        if (*ps == 'l' || *ps == 'L')
        {
            i2_log_type |= _BANNER_LOG_TYPE_LOCATION ;
        }

        if (*ps == 'o' || *ps == 'O')
        {
            i2_log_type |= _BANNER_LOG_TYPE_OTH_INFO ;
        }

        ps ++ ;
    }

    banner_set_log_type (i2_log_type) ;

    return NAVR_OK ;
}

static INT32 _banner_cli_cmd_show_sidebar (INT32 i4_argc, const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    const CHAR*                 ps_enable = NULL ;
    if(i4_argc != 3)
    {
        DBG_LOG_PRINT(("\n usage: SD [0/1/..] [0/1]\
                        \n              0 0 -> hide all sidebar logo\
                        \n              1 0/1 ->  DOLBY_VISION\
                        \n              2 0/1 ->  HLG\
                        \n              3 0/1 ->  HDR10\
                        \n              4 0/1 ->  HDR10+\
                        \n              5 0/1 ->  DolbyA\
                        \n              6 0/1 ->  DolbyT\
                        \n              7 0/1 ->  ProG\
                        \n              8 0/1 ->  FilmM\
                        \n              9 0/1 ->  FreeS")) ;
        return NAVR_FAIL ;
    }

    ps = pps_argv[1] ;
    ps_enable = pps_argv[2];

    if(*ps == '0')
    {
        banner_hide_sidebar();
    }
    else if(*ps == '1')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_HDR_DOLBY_VISION);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_HDR_DOLBY_VISION);
    }
    else if(*ps == '2')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_HDR_HLG);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_HDR_HLG);
    }
    else if(*ps == '3')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_HDR_HDR10);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_HDR_HLG);
    }
    else if(*ps == '4')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_HDR_HDR10_PLUS);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_HDR_HDR10_PLUS);
    }
    else if(*ps == '5')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_DOLBY_AUDIO);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_DOLBY_AUDIO);
    }
    else if(*ps == '6')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_DOLBY_ATMOS);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_DOLBY_ATMOS);
    }
    else if(*ps == '7')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_PROGAMING_ENGINE);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_PROGAMING_ENGINE);
    }
    else if(*ps == '8')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_FILMMAKER_MODE);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_FILMMAKER_MODE);
    }
    else if(*ps == '9')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_FREESYNC);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_FREESYNC);
    }
    else if(*ps == 'a')
    {
        if(*ps_enable == '1')
            banner_show_siderbar_logo(BANNER_LOGO_V_GAMING_ENGINE);
        else if(*ps_enable == '0')
            banner_hide_siderbar_logo(BANNER_LOGO_V_GAMING_ENGINE);
    }

    return NAVR_OK ;

}


static INT32 _banner_cli_cmd_print_item(INT32 i4_argc, const CHAR** pps_argv)
{
    const char  *p_str = NULL;
    BOOL        dump_all = FALSE;
    CHAR        s_disp_name[33] = {0};
    UINT8       ui1_input_id = 0;
    ISL_REC_T   t_isl_rec;
    INT32       i4_ret;
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: pi [0/1/2/3/...]\
                        \n              ALL(0) -> show all above\
                        \n          TV_name(1) -> show TV_name\
                        \n     IputSrc_name(2) -> show IputSrc_name\
                        \n       Resolution(3) -> show Resolution\
                        \n            Audio(4) -> show Audio\
                        \n      ")) ;
        return NAVR_FAIL ;
    }

    p_str = pps_argv[1] ;
    if(!c_strcmp(p_str,"ALL"))
        dump_all = TRUE;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);

    NAV_COMP_ID_T   t_comp = nav_get_active_component();
    DBG_LOG_PRINT(("[nav comp] t_comp:%d NAV_COMP_ID_BANNER:%d NAV_COMP_ID_LAST_VALID_ENTRY:%d\n",
        t_comp,NAV_COMP_ID_BANNER,NAV_COMP_ID_LAST_VALID_ENTRY));

    if(dump_all || !c_strcmp(p_str,"TV_name"))
    {
        CHAR                        s_cast_name_apron[128+1]={0};
        CHAR                        s_cast_name_cfg[128+1]={0};
        CHAR                        s_tv_name_cfg[128+1]={0};
        UINT32                      ui4_cast_name_len = 128+1;
#ifdef A_C4TV_APRON_CAST_NAME
        a_c4tv_apron_get_cast_name(s_cast_name_apron, &ui4_cast_name_len);
#endif
        a_cfg_custom_get_cast_name(s_cast_name_cfg, &ui4_cast_name_len);
        a_cfg_custom_get_tv_name(s_tv_name_cfg, &ui4_cast_name_len);
        if((c_strlen(s_cast_name_apron) >= 0 || c_strlen(s_cast_name_cfg) >= 0 || c_strlen(s_tv_name_cfg) >= 0))
        {
            DBG_LOG_PRINT(("[Banner TV_name] apron_name:\"%s\",cfg_name:\"%s\",tv_name:\"%s\"\n",\
                s_cast_name_apron,s_cast_name_cfg,s_tv_name_cfg));
        }

    }

    if(dump_all || !c_strcmp(p_str,"IputSrc_name"))
    {
        CHAR        s_vtrl_name[24] = {0};
        UTF16_T     w2s_alias[24+1] = {0};

        c_memset(s_vtrl_name,0,sizeof(s_vtrl_name));
        a_isl_get_display_name_ex(&t_isl_rec, w2s_alias, 24);
        c_uc_w2s_to_ps(w2s_alias,s_vtrl_name,sizeof(s_vtrl_name));
        DBG_LOG_PRINT(("[Banner IputSrc_name] \"%s\"\n",s_vtrl_name));
    }
    if(dump_all || !c_strcmp(p_str,"Resolution"))
    {
        TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;
        HANDLE_T                    h_svctx;
        VSH_SRC_RESOLUTION_INFO_T   t_resolution = {0};
        i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("%s,%d,nav_get_svctx_handle(win=%d) failed, i4_ret=%d.\n",
                            __FUNCTION__,__LINE__, e_tv_win_id, i4_ret));
        }
        c_memset(&t_resolution, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
        i4_ret = c_svctx_get_video_src_resolution(h_svctx,&t_resolution);
        BANNER_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT (("[Banner Resolution] (%d,%d) -> (%d,%d) \n",
                        t_resolution.ui2_orig_width, t_resolution.ui2_orig_height,t_resolution.ui4_width,t_resolution.ui4_height));

        SCC_DISP_RESOLUTION_T       scc_resolution = {0};
        i4_ret = c_svctx_get_display_resolution(h_svctx,&scc_resolution);
        BANNER_CHK_FAIL(i4_ret);
        DBG_LOG_PRINT (("[Banner Resolution](scc) (%d,%d) -> (%d,%d) \n",
                        t_resolution.ui2_orig_width, t_resolution.ui2_orig_height,t_resolution.ui4_width,t_resolution.ui4_height));

    }
    if(dump_all || !c_strcmp(p_str,"HDR_type"))
    {
        CHAR     s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
        HANDLE_T h_scc_comp = NULL_HANDLE;

        /* Get SCC handle by display name. */
        i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        BANNER_CHK_FAIL(i4_ret);
        h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                     h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

        SCC_VID_HDR_TYPE_T t_hdr_type;
        i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
        BANNER_LOG_ON_FAIL(i4_ret);
        DBG_LOG_PRINT (("[Banner HDR_type]: type = %d(%s)\r\n", t_hdr_type,
                                              t_hdr_type==SCC_VID_PQ_HDR10?"HDR10":\
                                              t_hdr_type==SCC_VID_PQ_HLG?"HLG":\
                                              t_hdr_type==SCC_VID_PQ_DOVI?"DolbyVision":\
                                              t_hdr_type==SCC_VID_PQ_HDR10PLUS?"HDR10+":"Other"));
    }
    if(dump_all || !c_strcmp(p_str,"Audio_type"))
    {
        INT32                 i4_ret = NAVR_FAIL;
        HANDLE_T              h_scc = NULL_HANDLE;
        SM_COMMAND_T          at_sm_cmds[3];
        SCC_AUD_IEC_TYPE_T    pe_iec_type = SCC_AUD_IEC_CFG_PCM;

        //for non watchfree/3rd_app
        do{
            /*scc component for mts operation*/
            at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
            at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
            at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
            at_sm_cmds[2].u.ui4_data = 0;

            if(0 != c_scc_comp_open(at_sm_cmds, &h_scc) || NULL_HANDLE == h_scc )
                break;
            i4_ret = c_scc_aud_get_iec_type(h_scc,&pe_iec_type);
            DBG_LOG_PRINT (("[Banner Audio] type = %d(%s)\n",pe_iec_type,
                                              pe_iec_type==SCC_AUD_IEC_CFG_PCM?"mono/stream":\
                                              pe_iec_type==SCC_AUD_IEC_CFG_DD?"Dolby DD":\
                                              pe_iec_type==SCC_AUD_IEC_CFG_DDP?"Dolby DD+":\
                                              pe_iec_type==SCC_AUD_IEC_CFG_DDP_ATMOS?"Dolby ATMOS":\
                                              pe_iec_type==SCC_AUD_IEC_CFG_Bitstream?"not Dolby stream, but ch_num > 2":"Other"));
            c_scc_comp_close(h_scc);
        }while(0);

    }

    return NAVR_OK ;

}



static INT32 _banner_cli_mi_mm_test (INT32 i4_argc, const CHAR** pps_argv)
{

    MI_RESULT                   e_ret               = MI_ERR_FAILED;
    MI_HANDLE                   h_MI_MM_Hdl;
    MI_MM_QueryHandleParams_t   stQueryHandleParams;
    MI_MM_MovieInfo_t           stMovieInfo;
    //MI_MM_AudioEaseParams_t     stAudioEaseParams;
    MI_MM_AudioTrackInfo_t      stAudioParams;
    UINT32                      ui4_idx             = 0xD431;// %d  =  54321
    CHAR                        szMmName[128]       = {0};
    c_memset(&stMovieInfo,0,sizeof(MI_MM_MovieInfo_t));


    //c_snprintf(szMmName, sizeof(szMmName), "CMA_OVER_MI_MM_%d_%d", ui4_idx,getpid());
    c_snprintf(szMmName, sizeof(szMmName), "CMA_OVER_MI_MM_%d", ui4_idx);

    DBG_LOG_PRINT(("szMmName:%s.\n",szMmName));

    stQueryHandleParams.pszName = (uint8_t *)szMmName;
    stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_MOVIE;

    e_ret = MI_MM_GetHandle(&stQueryHandleParams,&h_MI_MM_Hdl);
    if(e_ret != MI_OK)
    {
        DBG_LOG_PRINT(("MI_MM_GetHandle fail ret = %d\n", e_ret));
        return -1;
    }

    //MI_U64 pu64CallbackId;
    //_banner_MI_MM_Register(h_MI_MM_Hdl, &pu64CallbackId);
    //DBG_LOG_PRINT(("_banner_MI_MM_Register pu64CallbackId = %x\n",pu64CallbackId));

    e_ret = MI_MM_GetMovieInfo(h_MI_MM_Hdl,&stMovieInfo);
    if(e_ret != MI_OK)
    {
        DBG_LOG_PRINT(("MI_MM_GetMovieInfo fail ret = %d\n", e_ret));
        return -1;
    }
    else
    {
        DBG_LOG_PRINT(("h:%d. w:%d\n", stMovieInfo.u32MovieHeight, stMovieInfo.u32MovieWidth));
        DBG_LOG_PRINT(("audio total track:%d. sub total track:%d\n",stMovieInfo.u32TotalAudioTrack, stMovieInfo.u32TotalSubtitleTrack));
        DBG_LOG_PRINT(("FramePerSec:%d. TotalProgram:%d\n",stMovieInfo.u32FramePerSec, stMovieInfo.u32TotalProgram));
        DBG_LOG_PRINT(("VideoCodec:%d. AudioCodec:%d\n",stMovieInfo.eVideoCodec, stMovieInfo.eAudioCodec));
        DBG_LOG_PRINT(("Current playing audio channel count:%d\n",stMovieInfo.u32AudioChannelCount));
        DBG_LOG_PRINT(("Current playing mode : %d \n",stMovieInfo.eTrickMode));
        DBG_LOG_PRINT(("Decode Frame Count : %d \n", stMovieInfo.u32DecodedFrameCount));
        DBG_LOG_PRINT(("Error Frame Count : %d \n", stMovieInfo.u32ErrorFrameCount));
        DBG_LOG_PRINT(("Skip Frame Count : %d \n", stMovieInfo.u32SkipFrameCount));
        DBG_LOG_PRINT(("Drop Frame Count : %d \n", stMovieInfo.u32DropFrameCount));

    }


    //e_ret = MI_MM_GetAttr(h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_AUDIO_EASE, NULL, (void *)&stAudioEaseParams);
    e_ret = MI_MM_GetAttr(h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_GET_AUDIO_TRACK_INFO, NULL, (void *)&stAudioParams);
    if(e_ret != MI_OK)
    {
        DBG_LOG_PRINT(("MI_MM_GetAttr E_MI_MM_ATTR_TYPE_GET_AUDIO_TRACK_INFO fail ret = %d\n", e_ret));
        return -1;
    }
    else
    {
        DBG_LOG_PRINT(("Audio type : %d(%x)\n", stAudioParams.eCodec,stAudioParams.eCodec));
        DBG_LOG_PRINT(("Audio channels: %d \n", stAudioParams.u32ChannelCount));
        DBG_LOG_PRINT(("Audio scale: %d \n", stAudioParams.bIsAudioDescription));
    }



    return 0;
}


static INT32 _banner_cli_change_vlog (INT32 i4_argc, const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    UINT8                       ui1_log_level = LOGLEVEL_OFF;
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: cvl [0/1/2/3]\
                        \n              0 -> vlog off\
                        \n              1 -> vlog APP only\
                        \n              2 -> vlog Kernel only\
                        \n              3 -> vlog ALL\n")) ;
        return NAVR_FAIL ;
    }

    ps = pps_argv[1] ;

    if(*ps == '0') // OFF
    {
        ui1_log_level = LOGLEVEL_OFF;
    }
    else if(*ps == '1')// APP_ONLY
    {
        ui1_log_level = LOGLEVEL_APP_ONLY;
    }
    else if(*ps == '2') // KERNEL_ONLY
    {
        ui1_log_level = LOGLEVEL_KERNEL_ONLY;
    }
    else if(*ps == '3') // ALL (APP and Kernel)
    {
        ui1_log_level = LOGLEVEL_ALL;
    }

    a_cfg_cust_set_log_level(ui1_log_level);

    return NAVR_OK;
}


static INT32 _banner_cli_set_ctrl_show_switch (INT32 i4_argc, const CHAR** pps_argv)
{
    const CHAR*                 ps = NULL ;
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: scss [0/1]\
                        \n              0 -> disable banner show\
                        \n              1 -> enable banner show\n")) ;
        return NAVR_FAIL ;
    }

    ps = pps_argv[1] ;

    if(*ps == '0')
    {
        banner_view_set_b_ctrl_show_flag(FALSE);
    }
    else if(*ps == '1')
    {
        banner_view_set_b_ctrl_show_flag(TRUE);
    }
    DBG_LOG_PRINT(("After set,b_ctrl_show_flag:%d\n",banner_view_get_b_ctrl_show_flag()));
    return NAVR_OK;
}

static INT32 _banner_cli_get_ctrl_show_switch (INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("b_ctrl_show_flag:%d\n",banner_view_get_b_ctrl_show_flag()));
    return NAVR_OK;
}


static INT32 banner_try_get(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("***************** start\n"));
    banner_mm_try();
    DBG_LOG_PRINT(("***************** end\n"));
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name banner_cli_init
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 banner_cli_init(
    BANNER_T*                           pt_this
    )
{
    return nav_register_comp_cli_entry(&t_g_banner_entry) ;
}


/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

#endif /* CLI_SUPPORT */


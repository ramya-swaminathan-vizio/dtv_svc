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
 * $RCSfile: zoom_mode.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Zoom mode is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_ZOOM_MODE_SUPPORT
#include <stdlib.h>

#include "u_common.h"
#include "u_lnk_list.h"
#include "u_os.h"
#include "u_gl.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_gl.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "res/app_util/a_custom_log.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "app_util/mtk_tvap_proxy/tvap_proxy_common.h"

#include "app_util/zoom_mode/zoom_mode.h"
#include "app_util/a_zoom_mode.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "res/nav/nav_custom_comp_id.h"


#include "mttype.h"
#include "mtosd.h"

#include "gfxdrivers/mstar_mi/mstarFb.h"
#include "gfxdrivers/mstar_mi/fb.h"

#include <sys/ioctl.h>


//const CHAR *DevNode0 = "/dev/graphics/fb1";
CHAR *DevNode0 = "/dev/fb0";    //osd2 menu
CHAR *DevNode1 = "/dev/fb1";    //osd1  sch
CHAR *DevNode2 = "/dev/fb2";    //osd3

/*file handle*/
static INT32 fb_osd0_handle = 0;
static INT32 fb_osd1_handle = 0;
static INT32 fb_osd2_handle = 0;

/*fb var or fix screeninfo */
static struct fb_var_screeninfo fb_osd_menu_vinfo = {0};
static struct fb_fix_screeninfo fb_osd_menu_finfo = {0};

static struct fb_var_screeninfo fb_osd_sch_vinfo = {0};
static struct fb_fix_screeninfo fb_osd_sch_finfo = {0};

/*menu osd*/
static MI_FB_CropInfo_t t_fb_osd_menu_cropinfo_open  = {0};
//static MI_FB_CropInfo_t t_fb_osd_menu_cropinfo_input = {0};
static MI_FB_CropInfo_t t_fb_osd_menu_output_enlarge = {0};

/*SCH osd*/
static MI_FB_CropInfo_t t_fb_osd_sch_cropinfo_open  = {0};
//static MI_FB_CropInfo_t t_fb_osd_sch_cropinfo_input = {0};
static MI_FB_CropInfo_t t_fb_osd_sch_output_enlarge = {0};

//t_at_g_wgl_hl_rect_crop_info    = {0};

//static UINT16 i2_cropinfo_zoom_mode_osd_w = 0;
//static UINT16 i2_cropinfo_zoom_mode_osd_h = 0;

static INT32 aa_gl_zoom_mode_sector_array2out_cropinfo(MI_FB_CropInfo_t *cropinfo,GL_OSD_ZOOM_SECTOR_T at_zoom_sector_array);
static INT32 aa_gl_zoom_mode_sector_array2out_cropinfo_sch(MI_FB_CropInfo_t *cropinfo,GL_OSD_ZOOM_SECTOR_T at_zoom_sector_array);
static INT32 aa_gl_zoom_mode_enlarge_cropinfo_region(INT32 fb_osd_handle, MI_FB_CropInfo_t cropinfo);
//static INT32 aa_gl_zoom_mode_hl_rec2out_cropinfo(MI_FB_CropInfo_t *cropinfo,GL_RECT_T pt_rect);

static void printFixedInfo (struct fb_fix_screeninfo * pfixinfoStruct);
static INT32 aa_zoom_print_crop_info(MI_FB_CropInfo_t cropinfo);
static INT32 aa_print_crop_info(MI_FB_CropInfo_t *cropinfo);

#define DBG_INFO(x) DBG_LOG_PRINT(x)

#define ZOOM_CHECK_RET(X)  \
    {   \
        if( X < 0 )  \
        {   \
            DBG_LOG_PRINT(("[zoom_mode] %s(),%d ",__FUNCTION__,__LINE__)); \
            DBG_LOG_PRINT((" error ret is :%d\n",X));\
            return X;   \
        }   \
    }

#define ZOOM_CHECK_IOCTLRET(X)  \
 { \
        if( X < 0 )  \
        { \
        DBG_LOG_PRINT(("[zoom_mode 1.5] %s(),%d,INVALID RETURN VALUE ",__FUNCTION__,__LINE__)); \
        DBG_LOG_PRINT((" error ret is :%d\n",X));\
        goto IOCTLFAIL;\
        } \
 }


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef MAX
#define MAX(x, y)           (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x, y)           (((x) < (y)) ? (x) : (y))
#endif

#define ZOOM_COMP_NAME(app_id,comp_id) \
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_BANNER)         ? "NAV_COMP_ID_BANNER"         :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_SCREEN_SAVER)   ? "NAV_COMP_ID_SCREEN_SAVER"   :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_TUNER_SETUP)    ? "NAV_COMP_ID_TUNER_SETUP"    :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_CH_LIST)        ? "NAV_COMP_ID_CH_LIST"        :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_PICTURE_EFFECT) ? "NAV_COMP_ID_PICTURE_EFFECT" :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_INPUT_SRC)      ? "NAV_COMP_ID_INPUT_SRC"      :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_DIALOG)         ? "NAV_COMP_ID_DIALOG"         :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_SCREEN_MODE)    ? "NAV_COMP_ID_SCREEN_MODE"    :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_VOL_CTRL)       ? "NAV_COMP_ID_VOL_CTRL"       :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_SLEEP)          ? "NAV_COMP_ID_SLEEP"          :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_POWER)          ? "NAV_COMP_ID_POWER"          :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_REVOLT_INFO)    ? "NAV_COMP_ID_REVOLT_INFO"    :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == NAV_COMP_ID_C4TV_APRON)     ? "NAV_COMP_ID_C4TV_APRON"     :\
    (app_id == ZOOM_APP_GRPID_NAV && comp_id == ZOOM_APP_RECID_NAV_DEFAULT)         ? "ZOOM_APP_RECID_NAV_DEFAULT"      :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_SCREEN_MODE)   ? "ZOOM_APP_RECID_MENU_SCREEN_MODE" :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_DIALOG)        ? "ZOOM_APP_RECID_MENU_DIALOG"      :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_PIC_SIZE)      ? "ZOOM_APP_RECID_MENU_PIC_SIZE"    :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_EQUALIZER)     ? "ZOOM_APP_RECID_MENU_EQUALIZER"   :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_DEFAULT)       ? "ZOOM_APP_RECID_MENU_DEFAULT"     :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_COLOR_TUNER)   ? "ZOOM_APP_RECID_MENU_COLOR_TUNER" :\
    (app_id == ZOOM_APP_GRPID_MENU && comp_id == ZOOM_APP_RECID_MENU_SLIDER)        ? "ZOOM_APP_RECID_MENU_SLIDER"      :\
    (app_id == ZOOM_APP_GRPID_MMP && comp_id == ZOOM_APP_RECID_MMP_DEFAULT)         ? "ZOOM_APP_RECID_MMP_DEFAULT"      :\
    (app_id == ZOOM_APP_GRPID_MMP && comp_id == ZOOM_APP_RECID_MMP_VP_TB_SHOW)      ? "ZOOM_APP_RECID_MMP_VP_TB_SHOW"   :\
    (app_id == ZOOM_APP_GRPID_3RD_APP && comp_id == ZOOM_APP_RECID_YH_DOCK)         ? "ZOOM_APP_RECID_YH_DOCK"          :\
    (app_id == ZOOM_APP_GRPID_3RD_APP && comp_id == ZOOM_APP_RECID_YH_SIDEBAR)      ? "ZOOM_APP_RECID_YH_SIDEBAR"       :\
    (app_id == ZOOM_APP_GRPID_3RD_APP && comp_id == ZOOM_APP_RECID_RETAIL_MODE)     ? "ZOOM_APP_RECID_RETAIL_MODE"      :\
    (app_id == ZOOM_APP_GRPID_3RD_APP && comp_id == ZOOM_APP_RECID_RETAIL_DIALOG)   ? "ZOOM_APP_RECID_RETAIL_DIALOG"    :\
    (app_id == ZOOM_APP_GRPID_3RD_APP && comp_id == ZOOM_APP_RECID_APP_FULL_SCREEN) ? "ZOOM_APP_RECID_APP_FULL_SCREEN"  :\
    (app_id == ZOOM_APP_GRPID_3RD_APP && comp_id == ZOOM_APP_RECID_APP_DEFAULT)     ? "ZOOM_APP_RECID_APP_DEFAULT"      :\
    (app_id == ZOOM_APP_GRPID_3RD_APP) ? "UNKNOW ZOOM 3RD  APP" : \
    (app_id == ZOOM_APP_GRPID_NAV)     ? "UNKNOW ZOOM NAV  APP" : \
    (app_id == ZOOM_APP_GRPID_MENU)    ? "UNKNOW ZOOM MENU APP" : \
    (app_id == ZOOM_APP_GRPID_MMP)     ? "UNKNOW ZOOM MMP  APP" : "UNKNOW ZOOM COMP"\


#define ZOOM_APP_NAME(app_id) \
    (app_id == ZOOM_APP_GRPID_MENU)     ? "MENU"         :\
    (app_id == ZOOM_APP_GRPID_NAV)      ? "NAV"          :\
    (app_id == ZOOM_APP_GRPID_MMP)      ? "TUNER_SETUP"  :\
    (app_id == ZOOM_APP_GRPID_3RD_APP)  ? "CH_LIST"      : "UNKOWN ZOOM APP"


/* zoom sector buffer declarations */
typedef struct __NAV_ZOOM_SECTOR_ENTRY_T
{
    UINT16              ui2_id;
    ZOOM_SECTOR_ITEM    e_item;
    SLIST_ENTRY_T(__NAV_ZOOM_SECTOR_ENTRY_T) t_link;
} _NAV_ZOOM_SECTOR_ENTRY_T;

typedef SLIST_T(__NAV_ZOOM_SECTOR_ENTRY_T) ZOOM_SECTOR_LIST_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BOOL     b_g_zoom_mode_enable = FALSE;

static ZOOM_SECTOR_LIST_T       t_zoom_sector_list;

static HANDLE_T                 h_zoom_sema_mtx = NULL_HANDLE;

static HANDLE_T                 h_delay_timer = NULL_HANDLE;

static ZOOM_SECTOR_REGION_T     t_g_sector_region[ZOOM_SECTOR_MAX_NUM];

static GL_RECT_T                at_g_wgl_hl_rect[ZOOM_APP_GRPID_LAST_VALID_ENTRY];
static UINT16                  ui2_hide_real_id = 0;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
extern ZOOM_SECTOR_ITEM nav_zoom_cust_get_default_sector_item(const UINT16 ui2_id);

extern ZOOM_SECTOR_ITEM nav_zoom_cust_get_current_sector_item(VOID);

extern ZOOM_SECTOR_SET_T nav_zoom_cust_get_include_items(const UINT16 ui2_id);

extern VOID a_nav_zoom_cust_select_top_sector (VOID);

extern VOID a_nav_zoom_cust_select_sector (UINT8 ui1_sector, BOOL b_need_store);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _zoom_init_sector_region(VOID)
{
    UINT8   ui1_i = 0;
    UINT32  ui4_screen_w = ZOOM_VSH_REGION_MAX_WIDTH;
    UINT32  ui4_screen_h = ZOOM_VSH_REGION_MAX_HEIGHT;

    for (ui1_i = 0; ui1_i < ZOOM_SECTOR_MAX_NUM; ui1_i++)
    {
        t_g_sector_region[ui1_i].ui4_x = (ui4_screen_w/4)*(ui1_i%3);
        t_g_sector_region[ui1_i].ui4_y = (ui4_screen_h/4)*(ui1_i/3);
        t_g_sector_region[ui1_i].ui4_w = ui4_screen_w/2;
        t_g_sector_region[ui1_i].ui4_h = ui4_screen_h/2;
    }

    return;
}

static INT32 _zoom_lock(VOID)
{
    return c_sema_lock(h_zoom_sema_mtx, X_SEMA_OPTION_WAIT) == OSR_OK ?
           ZMR_OK:
           ZMR_FAIL;
}

static INT32 _zoom_unlock(VOID)
{
    return c_sema_unlock(h_zoom_sema_mtx) == OSR_OK ?
           ZMR_OK :
           ZMR_FAIL;
}

static INT32 _zoom_dump_buffer_in_slist(VOID)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;
    INT32                       i4_i = 0;
    UINT8                       i1_comp_id;
    UINT8                       i1_app_id;
    if (!b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "is EMPTY!!!\n");
        return ZMR_OK;
    }

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", ">>>>>>>>>>>>>>\n");

    SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
    {
        i1_app_id  = ZOOM_GET_GROUP(pt_data->ui2_id);
        i1_comp_id = ZOOM_GET_IDX(pt_data->ui2_id);
        KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "item[%d]: id[%s, %s], sector[%d].\n",
                i4_i,
                ZOOM_APP_NAME(i1_app_id), ZOOM_COMP_NAME(i1_app_id,i1_comp_id),
                pt_data->e_item);

        i4_i++;
    }

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "<<<<<<<<<<<<<<\n");

    return ZMR_OK;
}

static BOOL _zoom_has_item_in_slist(const UINT16 ui2_id)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        return FALSE;
    }

    _zoom_lock();

    SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
    {
        if (pt_data->ui2_id == ui2_id)
        {
            _zoom_unlock();
            return TRUE;
        }
    }

    _zoom_unlock();

    return FALSE;
}

static BOOL _zoom_has_same_group_in_slist(const UINT16 ui2_id)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;
    UINT8 ui1_group = ZOOM_GET_GROUP(ui2_id);

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        return FALSE;
    }

    _zoom_lock();

    SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
    {
        if (pt_data->ui2_id == ui2_id)
        {
            _zoom_unlock();
            return FALSE;
        }
        else if (ZOOM_GET_GROUP(pt_data->ui2_id) == ui1_group)
        {
            _zoom_unlock();
            return TRUE;
        }
    }

    _zoom_unlock();

    return FALSE;
}

static INT32 _zoom_remove_field_from_slist(const UINT16 ui2_id)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        return ZMR_OK;
    }

    _zoom_lock();

    SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
    {
        if (pt_data->ui2_id == ui2_id)
        {
            SLIST_REMOVE(pt_data, t_link);

            c_mem_free(pt_data);
            pt_data = NULL;
            break;
        }
    }

    _zoom_unlock();
    return ZMR_OK;
}

static INT32 _zoom_remove_fields_from_slist(const UINT8 ui1_app)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;
    BOOL                        b_found = FALSE;
    ZOOM_SECTOR_LIST_T*         pt_zoom_sector_list = NULL;

    _zoom_lock();

    pt_zoom_sector_list = &t_zoom_sector_list;

    while (!SLIST_IS_EMPTY(pt_zoom_sector_list))
    {
        b_found = FALSE;
        pt_data = NULL;

        SLIST_FOR_EACH(pt_data, pt_zoom_sector_list, t_link)
        {
            if (ZOOM_GET_GROUP(pt_data->ui2_id) == ui1_app)
            {
                b_found = TRUE;

                SLIST_REMOVE(pt_data, t_link);
                c_mem_free(pt_data);
                pt_data = NULL;

                break;
            }
        }

        if (FALSE == b_found)
        {
            break;
        }

        pt_zoom_sector_list = &t_zoom_sector_list;
    }

    _zoom_unlock();

    return ZMR_OK;
}

static INT32 _zoom_clean_slist(VOID)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "Enter.\n\r");

    pt_data = SLIST_FIRST(&t_zoom_sector_list);

    while(pt_data)
    {
        _NAV_ZOOM_SECTOR_ENTRY_T* pt_next = SLIST_NEXT(pt_data, t_link);
        SLIST_REMOVE(pt_data, t_link);
        c_mem_free(pt_data);
        pt_data = pt_next;
    }

    return ZMR_OK;
}

static ZOOM_SECTOR_ITEM _zoom_get_sector_item_from_slist(const UINT16 ui2_id)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;
    ZOOM_SECTOR_ITEM            e_item;

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        return ZOOM_SECTOR_INVALID_ITEM;
    }

    if (0)
    {
        _zoom_dump_buffer_in_slist();
    }

    _zoom_lock();

    SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
    {
        if (pt_data->ui2_id == ui2_id)
        {
            e_item = pt_data->e_item;

            _zoom_unlock();

            return e_item;
        }
    }

    _zoom_unlock();

    return ZOOM_SECTOR_INVALID_ITEM;
}

static INT32 _zoom_move_field_to_slist_head(const UINT16 ui2_id)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    _zoom_lock();

    if (FALSE == SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        pt_data = SLIST_FIRST(&(t_zoom_sector_list));
        if (pt_data->ui2_id == ui2_id)
        {
            _zoom_unlock();
            return ZMR_OK;
        }

        SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
        {
            if (pt_data->ui2_id == ui2_id)
            {
                SLIST_REMOVE(pt_data, t_link);
                SLIST_INSERT_HEAD(pt_data, &(t_zoom_sector_list), t_link);

                _zoom_unlock();
                return ZMR_OK;
            }
        }
    }

    _zoom_unlock();

    return ZMR_FAIL;
}

static INT32 _zoom_add_field_into_slist_head(const UINT16 ui2_id, ZOOM_SECTOR_ITEM e_item)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    if (ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, ZOOM_APP_RECID_NAV_DEFAULT) == ui2_id)
    {
        return ZMR_OK;
    }
    _zoom_lock();

    if (FALSE == SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        pt_data = SLIST_FIRST(&(t_zoom_sector_list));
        if (pt_data->ui2_id == ui2_id)
        {
            pt_data->e_item = e_item;
            _zoom_unlock();
            return ZMR_OK;
        }

        SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
        {
            if (pt_data->ui2_id == ui2_id)
            {
                SLIST_REMOVE(pt_data, t_link);

                pt_data->e_item = e_item;

                SLIST_INSERT_HEAD(pt_data, &(t_zoom_sector_list), t_link);

                _zoom_unlock();
                return ZMR_OK;
            }
        }
    }

    pt_data = (_NAV_ZOOM_SECTOR_ENTRY_T *)c_mem_alloc(sizeof(_NAV_ZOOM_SECTOR_ENTRY_T));
    if (pt_data == NULL)
    {
        _zoom_unlock();
        return ZMR_OUT_OF_MEMORY;
    }

    c_memset(pt_data, 0, sizeof(_NAV_ZOOM_SECTOR_ENTRY_T));

    pt_data->ui2_id = ui2_id;
    pt_data->e_item = e_item;

    SLIST_INSERT_HEAD(pt_data, &(t_zoom_sector_list), t_link);

    _zoom_unlock();
    return ZMR_OK;
}

static INT32 _zoom_update_1st_sector_item_in_slist(ZOOM_SECTOR_ITEM e_item)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        return ZMR_OK;
    }

    _zoom_lock();

    pt_data = SLIST_FIRST(&(t_zoom_sector_list));

    pt_data->e_item = e_item;

    _zoom_unlock();

    return ZMR_OK;
}

static ZOOM_SECTOR_ITEM _zoom_get_1st_sector_item_from_slist(VOID)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;
    ZOOM_SECTOR_ITEM            e_item;

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        return ZOOM_SECTOR_INVALID_ITEM;
    }

    if (0)
    {
        _zoom_dump_buffer_in_slist();
    }

    _zoom_lock();

    pt_data = SLIST_FIRST(&(t_zoom_sector_list));

    e_item = pt_data->e_item;

    _zoom_unlock();

    return e_item;
}

static VOID _zoom_timer_delay_cb_fct (HANDLE_T  pt_tm_handle,
                                      VOID*     pv_tag)
{
    a_nav_zoom_cust_select_top_sector();
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_zoom_mode_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_zoom_mode_init(VOID)
{
    INT32                   i4_ret = ZMR_OK;

    do
    {
        c_memset(at_g_wgl_hl_rect, 0, ZOOM_APP_GRPID_LAST_VALID_ENTRY*sizeof(GL_RECT_T));
		/*power on to set default*/
		at_g_wgl_hl_rect[0].i4_left   = 0;
        at_g_wgl_hl_rect[0].i4_top    = 263;
        at_g_wgl_hl_rect[0].i4_right  = 638;
        at_g_wgl_hl_rect[0].i4_bottom = 338;

        _zoom_init_sector_region();

        /* allocate mutex */
        i4_ret = c_sema_create(&h_zoom_sema_mtx,
                               X_SEMA_TYPE_MUTEX,
                               X_SEMA_STATE_UNLOCK);
        if (i4_ret != OSR_OK)
        {
            h_zoom_sema_mtx = NULL_HANDLE;
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_sema create failed, i4_ret=%d.\n\r", i4_ret);
            break;
        }

        SLIST_INIT(&(t_zoom_sector_list));

        i4_ret = c_timer_create(&h_delay_timer);
        if (i4_ret != OSR_OK)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "register iom_nfy fail, i4_ret=%d.\n\r", i4_ret);
            break;
        }

        return ZMR_OK;

    } while(0);

    /* free resoruce */
    if (c_handle_valid(h_delay_timer) == TRUE)
    {
        c_timer_delete(h_delay_timer);
        h_delay_timer = NULL_HANDLE;
    }

    if (c_handle_valid(h_zoom_sema_mtx) == TRUE)
    {
        c_sema_delete(h_zoom_sema_mtx);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_zoom_mode_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_zoom_mode_enable(VOID)
{
    INT32                       i4_ret;
    TVAP_SYS_STATUS_T           t_sys_status = TVAP_SYS_STATUS_LAST_VALID;
    VOID*                       pv_nfy_data = NULL;

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "Enter.\n\r");

    if (b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    i4_ret = a_gl_zoom_mode_enable();
    if (GLR_OK != i4_ret && GLR_ALREADY_INIT != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_gl zoom_mode_enable failed, i4_ret=%d.\n\r", i4_ret);
        return ZMR_FAIL;
    }

    b_g_zoom_mode_enable = TRUE;

    t_sys_status = TVAP_SYS_STATUS_ZOOM_MODE_CHG;
    pv_nfy_data  = (VOID*)(UINT32)b_g_zoom_mode_enable;

    a_tvap_fire_tvap_status_updated(t_sys_status, pv_nfy_data);

    return ZMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_zoom_mode_disable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_zoom_mode_disable(VOID)
{
    INT32                       i4_ret;
    TVAP_SYS_STATUS_T           t_sys_status = TVAP_SYS_STATUS_LAST_VALID;
    VOID*                       pv_nfy_data = NULL;

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "Enter.\n\r");

    if (!b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    i4_ret = a_gl_zoom_mode_disable();
    if (GLR_OK != i4_ret && GLR_ALREADY_INIT != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_gl zoom_mode_disable failed, i4_ret=%d.\n\r", i4_ret);
        return ZMR_FAIL;
    }

    b_g_zoom_mode_enable = FALSE;
    ui2_hide_real_id = 0;
    t_sys_status = TVAP_SYS_STATUS_ZOOM_MODE_CHG;
    pv_nfy_data  = (VOID*)(UINT32)b_g_zoom_mode_enable;

    a_tvap_fire_tvap_status_updated(t_sys_status, pv_nfy_data);

    return ZMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_zoom_mode_enlarge_sector
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_zoom_mode_enlarge_sector(
    GL_OSD_ZOOM_SECTOR_T    at_zoom_sector[],
    UINT32                  ui4_zoom_sector_count
    )
{
    INT32                       i4_ret;
    UINT8                       ui1_value = APP_CFG_CUST_ZOOM_MODE_OFF;
    UINT32                      ui4_i = 0;

    if (!b_g_zoom_mode_enable)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "zoom mode is NOT enable.\n\r");
        return ZMR_FAIL;
    }

    //i4_ret = a_cfg_cust_get_zoom_mode(&ui1_value);
    i4_ret = a_cfg_cust_get_zoom_status(&ui1_value);
    if (APP_CFGR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_cfg_cust get_zoom_mode failed.\n\r");
        return ZMR_FAIL;
    }

    if (ui1_value != APP_CFG_CUST_ZOOM_MODE_ON)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "current_zoom_mode is NOT on.\n\r");
        return ZMR_FAIL;
    }

    for (ui4_i = 0; ui4_i < ui4_zoom_sector_count; ui4_i++)
    {
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "item[%u]: plane:%u, zoom_sector[%u, %u, %u, %u].\n\r",
                ui4_i,
                at_zoom_sector[ui4_i].e_plane,
                at_zoom_sector[ui4_i].ui4_X,
                at_zoom_sector[ui4_i].ui4_Y,
                at_zoom_sector[ui4_i].ui4_W,
                at_zoom_sector[ui4_i].ui4_H);
    }

    i4_ret = a_gl_zoom_mode_enlarge_sector(at_zoom_sector, ui4_zoom_sector_count);
    if (i4_ret != GLR_OK)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_gl zoom_mode_enlarge_sector failed, i4_ret=%d.\n\r", i4_ret);
        return ZMR_FAIL;
    }

    return ZMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_zoom_mode_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
BOOL a_zoom_mode_get_status(VOID)
{
    return b_g_zoom_mode_enable;
}

INT32 a_zoom_mode_select_sector(UINT8 ui1_sector, BOOL b_need_store)
{
    if (!b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "sector: %u, need_store: %d.\n\r", ui1_sector, (INT32)b_need_store);

    a_nav_zoom_cust_select_sector(ui1_sector, b_need_store);

    return ZMR_OK;
}

INT32 a_zoom_mode_enlarge_region(ZOOM_VSH_REGION_COORDINATE_T* pt_zoom_region)
{
    INT32               i4_ret;
    ZOOM_SECTOR_ITEM    e_target_sector = ZOOM_SECTOR_INVALID_ITEM;

    if (!b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    if (!pt_zoom_region)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "invalid param.\n\r");
        return ZMR_INV_ARG;
    }

    //KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "interface: %u.\n\r", pt_zoom_region->ui1_interface);

    ZOOM_VSH_REGION_POINT_T t_anchor = {0};
    ZOOM_VSH_REGION_POINT_T* pt_cornerA = &(pt_zoom_region->t_left_top);
    ZOOM_VSH_REGION_POINT_T* pt_cornerB = &(pt_zoom_region->t_right_bottom);

    /* param value check */
    if (pt_cornerA->ui4_x > pt_cornerB->ui4_x &&
        pt_cornerA->ui4_y > pt_cornerB->ui4_y)
    {
        pt_cornerA = &(pt_zoom_region->t_right_bottom);
        pt_cornerB = &(pt_zoom_region->t_left_top);
    }
    if (pt_cornerA->ui4_x > pt_cornerB->ui4_x ||
        pt_cornerA->ui4_y > pt_cornerB->ui4_y)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "invalid param.\n\r");
        return ZMR_INV_ARG;
    }

    /* interface type is text or not */
    if (pt_zoom_region->ui1_interface == 1)
    {
        t_anchor.ui4_x = pt_cornerA->ui4_x;
        t_anchor.ui4_y = pt_cornerA->ui4_y;
    }
    else
    {
        t_anchor.ui4_x = (UINT32)((pt_cornerA->ui4_x + pt_cornerB->ui4_x)/2 + 1);
        t_anchor.ui4_y = (UINT32)((pt_cornerA->ui4_y + pt_cornerB->ui4_y)/2 + 1);
    }

    UINT8   ui1_i = 0;
    UINT8   ui1_count = 0;
    UINT8   aui1_sector[ZOOM_SECTOR_MAX_NUM] = {0};

    do{
        /* step1: find containing list */
        for (ui1_i = 0; ui1_i < ZOOM_SECTOR_MAX_NUM; ui1_i++)
        {
            if (t_anchor.ui4_x >= t_g_sector_region[ui1_i].ui4_x &&
                t_anchor.ui4_y >= t_g_sector_region[ui1_i].ui4_y &&
                t_anchor.ui4_x <= t_g_sector_region[ui1_i].ui4_x + t_g_sector_region[ui1_i].ui4_w &&
                t_anchor.ui4_y <= t_g_sector_region[ui1_i].ui4_y + t_g_sector_region[ui1_i].ui4_h)
            {
                //KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "containing(%u)\n\r", ui1_i);
                aui1_sector[ui1_i] = 1;
                ui1_count++;
            }
            else
            {
                aui1_sector[ui1_i] = 0;
            }
        }
        if (ui1_count <= 1)
        {
            break;
        }

        /* step2: find biggest list */
        ZOOM_VSH_REGION_POINT_T t_cornerLT = {0};
        ZOOM_VSH_REGION_POINT_T t_cornerRB = {0};
        UINT32                  aui4_area[ZOOM_SECTOR_MAX_NUM] = {0};
        UINT32                  ui4_max_area = 0;

        /* step2.1: calculate all containing area size */
        ui1_count = 0;
        for (ui1_i = 0; ui1_i < ZOOM_SECTOR_MAX_NUM; ui1_i++)
        {
            if (aui1_sector[ui1_i] == 0)
            {
                continue;
            }

            t_cornerLT.ui4_x =  MAX(pt_cornerA->ui4_x, t_g_sector_region[ui1_i].ui4_x);
            t_cornerLT.ui4_y =  MAX(pt_cornerA->ui4_y, t_g_sector_region[ui1_i].ui4_y);
            t_cornerRB.ui4_x =  MIN(pt_cornerB->ui4_x, t_g_sector_region[ui1_i].ui4_x + t_g_sector_region[ui1_i].ui4_w);
            t_cornerRB.ui4_y =  MIN(pt_cornerB->ui4_y, t_g_sector_region[ui1_i].ui4_y + t_g_sector_region[ui1_i].ui4_h);

            aui4_area[ui1_i] = (t_cornerRB.ui4_x - t_cornerLT.ui4_x) * (t_cornerRB.ui4_y - t_cornerLT.ui4_y);

            if (ui4_max_area < aui4_area[ui1_i])
            {
                ui4_max_area = aui4_area[ui1_i];
            }
        }
        if (ui4_max_area == 0)
        {
            break;
        }

        /* step2.2: only keep the biggest sectors */
        for (ui1_i = 0; ui1_i < ZOOM_SECTOR_MAX_NUM; ui1_i++)
        {
            if (aui1_sector[ui1_i] == 0)
            {
                continue;
            }

            if (aui4_area[ui1_i] == ui4_max_area)
            {
                //KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "biggest(%u)\n\r", ui1_i);
                ui1_count++;
            }
            else
            {
                aui1_sector[ui1_i] = 0;
            }
        }
        if (ui1_count <= 1)
        {
            break;
        }

        /* step3: find the closest one */
        ZOOM_SECTOR_ITEM    e_sector_item = _zoom_get_1st_sector_item_from_slist();
        if (e_sector_item == ZOOM_SECTOR_INVALID_ITEM)
        {
            e_sector_item = ZOOM_SECTOR_ITEM_1;
        }
        UINT8   ui1_curr = e_sector_item - 1;
        UINT32  ui4_temp_w = 0, ui4_temp_h = 0;
        UINT32  ui4_distance = 0;
        UINT32  ui4_min_distance = ZOOM_VSH_REGION_MAX_WIDTH*ZOOM_VSH_REGION_MAX_WIDTH/2;

        /* step3.1: current sector is still in the list */
        if (aui1_sector[ui1_curr] == 1)
        {
            /* got it */
            e_target_sector = e_sector_item;
            break;
        }

        /* step3.2: find the closest one */
        ui1_count = 0;
        for (ui1_i = 0; ui1_i < ZOOM_SECTOR_MAX_NUM; ui1_i++)
        {
            if (aui1_sector[ui1_i] == 0)
            {
                continue;
            }

            if (t_g_sector_region[ui1_i].ui4_x > t_g_sector_region[ui1_curr].ui4_x)
            {
                ui4_temp_w = t_g_sector_region[ui1_i].ui4_x - t_g_sector_region[ui1_curr].ui4_x;
            }
            else
            {
                ui4_temp_w = t_g_sector_region[ui1_curr].ui4_x - t_g_sector_region[ui1_i].ui4_x;
            }

            if (t_g_sector_region[ui1_i].ui4_y > t_g_sector_region[ui1_curr].ui4_y)
            {
                ui4_temp_h = t_g_sector_region[ui1_i].ui4_y - t_g_sector_region[ui1_curr].ui4_y;
            }
            else
            {
                ui4_temp_h = t_g_sector_region[ui1_curr].ui4_y - t_g_sector_region[ui1_i].ui4_y;
            }

            if (ui4_temp_w == 0)
            {
                ui4_distance = ui4_temp_h;
            }
            else if (ui4_temp_h == 0)
            {
                ui4_distance = ui4_temp_w;
            }
            else
            {
                ui4_distance = ui4_temp_w*ui4_temp_h/2;
            }

            if (ui4_distance < ui4_min_distance)
            {
                ui4_min_distance = ui4_distance;
                e_target_sector = ui1_i + 1;
            }
        }
    }while(0);

    if (e_target_sector != ZOOM_SECTOR_INVALID_ITEM)
    {
        /* already got it */
    }
    else if (ui1_count == 1)
    {
        for (ui1_i = 0; ui1_i < ZOOM_SECTOR_MAX_NUM; ui1_i++)
        {
            if (aui1_sector[ui1_i] == 1)
            {
                break;
            }
        }
        if (ui1_i == ZOOM_SECTOR_MAX_NUM)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "something wrong\n\r");
            return ZMR_FAIL;
        }

        e_target_sector = ui1_i + 1;
    }
    else
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "something wrong\n\r");
        return ZMR_FAIL;
    }

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "closest(%u)\n\r", e_target_sector-1);

    _zoom_update_1st_sector_item_in_slist(e_target_sector);

    i4_ret = c_timer_stop(h_delay_timer);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_timer stop failed.\n\r");
    }

    i4_ret = c_timer_start(h_delay_timer,
                    100,
                    X_TIMER_FLAG_ONCE,
                    _zoom_timer_delay_cb_fct,
                    NULL);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_timer start failed.\n\r");
    }

    return ZMR_OK;
}

INT32 a_zoom_mode_enlarge_wgl_hl_area(UINT16 ui2_id, GL_RECT_T* pt_rect)
{
    ZOOM_VSH_REGION_COORDINATE_T t_zoom_region = {0};
    UINT8 ui1_group = 0;

#if ZOOM_MODE_DEBUG
    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "item:%u rect:[%d,%d,%d,%d] !\r\n",
            ui2_id,
            pt_rect->i4_left,
            pt_rect->i4_top,
            pt_rect->i4_right,
            pt_rect->i4_bottom);
#endif

    if (!b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    if (NULL == pt_rect)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "invalid param.\n\r");
        return ZMR_INV_ARG;
    }

    /* check item in slist or not */
    if (_zoom_has_item_in_slist(ui2_id) == FALSE)
    {
        KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "no item:%u in slist.\n\r", ui2_id);
        return ZMR_OK;
    }

    /* check item in same group before this item in slist or not */
    if (_zoom_has_same_group_in_slist(ui2_id) == TRUE)
    {
        KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "other item before item:%u in slist.\n\r", ui2_id);
        return ZMR_OK;
    }

    ui1_group = ZOOM_GET_GROUP(ui2_id);
    if (ui1_group >= ZOOM_APP_GRPID_LAST_VALID_ENTRY)
    {
        return ZMR_INV_ARG;
    }

    if (pt_rect->i4_left   == at_g_wgl_hl_rect[ui1_group].i4_left  &&
        pt_rect->i4_top    == at_g_wgl_hl_rect[ui1_group].i4_top   &&
        pt_rect->i4_right  == at_g_wgl_hl_rect[ui1_group].i4_right &&
        pt_rect->i4_bottom == at_g_wgl_hl_rect[ui1_group].i4_bottom)
    {

//		KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "item:%u ======## same ##====== HIGHLIGHT AREA ! \r\n", ui2_id);

		return ZMR_OK;
    }
    else
    {
//		KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "item:%u ======## the not same ##====== HIGHLIGHT AREA ! \r\n", ui2_id);

        at_g_wgl_hl_rect[ui1_group].i4_left   = pt_rect->i4_left;
        at_g_wgl_hl_rect[ui1_group].i4_top    = pt_rect->i4_top;
        at_g_wgl_hl_rect[ui1_group].i4_right  = pt_rect->i4_right;
        at_g_wgl_hl_rect[ui1_group].i4_bottom = pt_rect->i4_bottom;
    }

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "item:%u rect:[%d,%d,%d,%d] !\r\n",
        ui2_id,
        pt_rect->i4_left,
        pt_rect->i4_top,
        pt_rect->i4_right,
        pt_rect->i4_bottom);

    if (_zoom_move_field_to_slist_head(ui2_id) != ZMR_OK)
    {
        KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "no item:%u in slist.\n\r", ui2_id);
        return ZMR_OK;
    }

    /* coordinate convert from WGL to ZOOM */
    t_zoom_region.ui1_interface = 1;
    t_zoom_region.t_left_top.ui4_x = pt_rect->i4_left*ZOOM_VSH_REGION_MAX_WIDTH/ZOOM_VSH_REGION_WGL_WIDTH + 1;
    t_zoom_region.t_left_top.ui4_y = pt_rect->i4_top*ZOOM_VSH_REGION_MAX_HEIGHT/ZOOM_VSH_REGION_WGL_HEIGHT + 1;
    t_zoom_region.t_right_bottom.ui4_x = pt_rect->i4_right*ZOOM_VSH_REGION_MAX_WIDTH/ZOOM_VSH_REGION_WGL_WIDTH + 1;
    t_zoom_region.t_right_bottom.ui4_y = pt_rect->i4_bottom*ZOOM_VSH_REGION_MAX_HEIGHT/ZOOM_VSH_REGION_WGL_HEIGHT + 1;

    return a_zoom_mode_enlarge_region(&t_zoom_region);
}

INT32 a_zoom_mode_set_sector_id(UINT16 ui2_id)
{
    INT32                   i4_ret;
    UINT16                  ui2_real_id = 0;

    UINT8                   ui1_app = ZOOM_GET_GROUP(ui2_id);
    UINT8                   ui1_comp = ZOOM_GET_IDX(ui2_id);

    ZOOM_SECTOR_ITEM        e_sector_item = ZOOM_SECTOR_INVALID_ITEM;

    if (ui1_app >= ZOOM_APP_GRPID_LAST_VALID_ENTRY)
    {
        return ZMR_INV_ARG;
    }

	/* no need to reset 0 */
	#if 0
    /* reset hl rect for this group */
    if (ui1_app == ZOOM_APP_GRPID_MENU)
    {
        at_g_wgl_hl_rect[ui1_app].i4_left   = 0;
        at_g_wgl_hl_rect[ui1_app].i4_top    = 0;
        at_g_wgl_hl_rect[ui1_app].i4_right  = 0;
        at_g_wgl_hl_rect[ui1_app].i4_bottom = 0;
    }
	#endif

    if (b_g_zoom_mode_enable)
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "%s: ui2_real_id = %u app = %s    comp = %s(%d)\n\r",
               (ZOOM_SECTOR_SHOW_MASK & ui2_id) == ZOOM_SECTOR_SHOW_MASK ? "SHOW" :"HIDE" ,
                ZOOM_MAKE_ID(ui1_app, ui1_comp),
                ZOOM_APP_NAME(ui1_app),
                ZOOM_COMP_NAME(ui1_app,ui1_comp),
                ui1_comp);

    if (ui1_comp == NAV_COMP_ID_INPUT_SRC)
    {
        return ZMR_OK;
    }

    if (1)
    {
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "BEFORE\n");
        _zoom_dump_buffer_in_slist();
    }
    if ((ZOOM_SECTOR_SHOW_MASK & ui2_id) == ZOOM_SECTOR_SHOW_MASK)
    {
        ui2_real_id = ZOOM_MAKE_ID(ui1_app, ui1_comp);

        e_sector_item = _zoom_get_sector_item_from_slist(ui2_real_id);
        if (ZOOM_SECTOR_INVALID_ITEM != e_sector_item)
        {
            _zoom_add_field_into_slist_head(ui2_real_id, e_sector_item);
        }
        else
        {
            /* get default zoom sector with app id and comp id */
            e_sector_item = nav_zoom_cust_get_default_sector_item(ui2_real_id);

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "e_sector_item: %d.\n\r", e_sector_item);
            if (ZOOM_SECTOR_INVALID_ITEM == e_sector_item)
            {
                return ZMR_OK;
            }
            else
            {
                //check if app luanching with tos ???
                if(FALSE == a_tv_custom_get_tos()      &&
                   NAV_COMP_ID_C4TV_APRON == ui1_comp  &&
                   ZOOM_APP_GRPID_NAV == ui1_app)
                {
                    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "can not get tos\n");
                    e_sector_item = ZOOM_SECTOR_ITEM_5;
                }
                if(NAV_COMP_ID_SCREEN_SAVER == ui1_comp &&
                   ZOOM_APP_GRPID_NAV       == ui1_app &&
                   TOAST_STYLE_MSG          == a_scrn_svr_get_style())
                {
                    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", " a screen saver msg  is visible\n");
                    e_sector_item = ZOOM_SECTOR_ITEM_2;
                }
                _zoom_add_field_into_slist_head(ui2_real_id, e_sector_item);
            }
        }

        /* special case for MENU group */
        if (ui1_app == ZOOM_APP_GRPID_MENU && ui1_comp == ZOOM_APP_RECID_MENU_DEFAULT && b_g_zoom_mode_enable)
        {
            //using focus widget to select sector
            i4_ret = c_timer_stop(h_delay_timer);
            if (OSR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_timer stop failed.\n\r");
            }

            /*page EQ and Color tuner's incorrect sector*/
            if((ZOOM_APP_RECID_MENU_EQUALIZER == ui2_hide_real_id) &&
               (ZOOM_APP_RECID_MENU_DEFAULT == ui1_comp))
            {
                a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_7,TRUE);
            }
            else if((ZOOM_APP_RECID_MENU_COLOR_TUNER == ui2_hide_real_id) &&
               (ZOOM_APP_RECID_MENU_DEFAULT == ui1_comp))
            {
                a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_1,TRUE);
            }

            DBG_INFO(("[+++] {%s %s() %d}. hide:%d,show:%d, e_sector_item = %d. warning @@@return ZMR_OK\n",
                __FILE__, __FUNCTION__, __LINE__,ui2_hide_real_id,ui1_comp,e_sector_item));

            return ZMR_OK;
        }
    }
    else
    {
        ui2_real_id = ui2_id;
        ui2_hide_real_id = ui1_comp;//hide
        _zoom_remove_field_from_slist(ui2_real_id);
    }
    if (1)
    {
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "END\n");
        _zoom_dump_buffer_in_slist();
    }
    /* only start delay timer for zoom if flag is enabled */
    if (!b_g_zoom_mode_enable)
    {
        return ZMR_OK;
    }

    i4_ret = c_timer_stop(h_delay_timer);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_timer stop failed.\n\r");
    }

    i4_ret = c_timer_start(h_delay_timer,
                    200,
                    X_TIMER_FLAG_ONCE,
                    _zoom_timer_delay_cb_fct,
                    NULL);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_timer start failed.\n\r");
    }

    return ZMR_OK;
}

INT32 a_zoom_clean_slist(VOID)
{
    return _zoom_clean_slist();
}

INT32 a_zoom_remove_fields_from_slist(const UINT8 ui1_app)
{
    return _zoom_remove_fields_from_slist(ui1_app);
}

INT32 a_zoom_add_field_into_slist_head(const UINT16 ui2_id, ZOOM_SECTOR_ITEM e_item)
{
    return _zoom_add_field_into_slist_head(ui2_id, e_item);
}
INT32 a_zoom_move_field_to_slist_head(const UINT16 ui2_id)
{
	return _zoom_move_field_to_slist_head(ui2_id);
}

INT32 a_zoom_update_1st_sector_item_in_slist(ZOOM_SECTOR_ITEM e_item)
{
    return _zoom_update_1st_sector_item_in_slist(e_item);
}

ZOOM_SECTOR_ITEM a_zoom_get_1st_sector_item_from_slist(VOID)
{
    return _zoom_get_1st_sector_item_from_slist();
}

ZOOM_SECTOR_ITEM a_zoom_get_sector_item_from_slist(const UINT16 ui2_id)
{
    return _zoom_get_sector_item_from_slist(ui2_id);
}

ZOOM_SECTOR_ITEM a_zoom_mode_get_current_sector(VOID)
{
    return nav_zoom_cust_get_current_sector_item();
}

BOOL a_zoom_has_item_in_slist(const UINT16 ui2_id)
{
    return _zoom_has_item_in_slist(ui2_id);
}

BOOL a_zoom_check_sector_has_content(ZOOM_SECTOR_ITEM e_item)
{
    _NAV_ZOOM_SECTOR_ENTRY_T*   pt_data = NULL;

    ZOOM_SECTOR_SET_T t_check_item = ZOOM_SECTOR_IDX_TO_ID(e_item);
    ZOOM_SECTOR_SET_T t_include_items = 0;

    if (SLIST_IS_EMPTY(&(t_zoom_sector_list)))
    {
        KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "is EMPTY!!!\n\r");
        return FALSE;
    }

    _zoom_lock();

    SLIST_FOR_EACH(pt_data, &(t_zoom_sector_list), t_link)
    {
        t_include_items = nav_zoom_cust_get_include_items(pt_data->ui2_id);

        if ((t_include_items & t_check_item) != 0)
        {
            _zoom_unlock();
            return TRUE;
        }
    }

    _zoom_unlock();

    return FALSE;
}

#if 0
/* only for unit test */

#define ZOOM_RAND(x, y)           ((rand()%((x)-(y)+1))+x)

extern VOID a_zoom_enlarge_region_unit_test(VOID)
{
    UINT32      ui4_screen_w = ZOOM_VSH_REGION_WGL_WIDTH;
    UINT32      ui4_screen_h = ZOOM_VSH_REGION_WGL_HEIGHT;

    //nav_get_ui_canvas_size(&ui4_screen_w, &ui4_screen_h);

    UINT32      ui4_randA_x = 0;
    UINT32      ui4_randA_y = 0;
    UINT32      ui4_randB_x = 0;
    UINT32      ui4_randB_y = 0;

    ZOOM_VSH_REGION_COORDINATE_T t_zoom_region;

    c_memset(&t_zoom_region, 0, sizeof(ZOOM_VSH_REGION_COORDINATE_T));

#if 1
    ui4_randA_x = ZOOM_RAND(0, (INT32)(ui4_screen_w/2+1));
    ui4_randA_y = ZOOM_RAND(0, (INT32)(ui4_screen_h/2+1));
#else
    ui4_randA_x = ui4_screen_w/4-10;
    ui4_randA_y = ui4_screen_h/4-10;
#endif

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "screen(%u, %u), randA(%u, %u).\n\r", ui4_screen_w, ui4_screen_h, ui4_randA_x, ui4_randA_y);

    t_zoom_region.t_left_top.ui4_x = ui4_randA_x*ZOOM_VSH_REGION_MAX_WIDTH/ui4_screen_w + 1;
    t_zoom_region.t_left_top.ui4_y = ui4_randA_y*ZOOM_VSH_REGION_MAX_HEIGHT/ui4_screen_h + 1;

#if 1
    ui4_randB_x = ui4_randA_x + ui4_screen_w/2 - 10;
    ui4_randB_y = ui4_randA_y + ui4_screen_h/2 - 10;
#else
    ui4_randB_x = ui4_randA_x + ui4_screen_w/2+40;
    ui4_randB_y = ui4_randA_y + ui4_screen_h/2+40;
#endif

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "screen(%u, %u), randB(%u, %u).\n\r", ui4_screen_w, ui4_screen_h, ui4_randB_x, ui4_randB_y);

    t_zoom_region.t_right_bottom.ui4_x = ui4_randB_x*ZOOM_VSH_REGION_MAX_WIDTH/ui4_screen_w + 1;
    t_zoom_region.t_right_bottom.ui4_y = ui4_randB_y*ZOOM_VSH_REGION_MAX_HEIGHT/ui4_screen_h + 1;


    /* test for no-text */
    t_zoom_region.ui1_interface = 0;

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "zoom_region_type(%u), zoom_region_A(%u, %u), zoom_region_A(%u, %u).\n\r",
        t_zoom_region.ui1_interface,
        t_zoom_region.t_left_top.ui4_x,
        t_zoom_region.t_left_top.ui4_y,
        t_zoom_region.t_right_bottom.ui4_x,
        t_zoom_region.t_right_bottom.ui4_y);

    a_zoom_mode_enlarge_region(&t_zoom_region);


    /* test for text */
    t_zoom_region.ui1_interface = 1;

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "zoom_region_type(%u), zoom_region_A(%u, %u), zoom_region_A(%u, %u).\n\r",
        t_zoom_region.ui1_interface,
        t_zoom_region.t_left_top.ui4_x,
        t_zoom_region.t_left_top.ui4_y,
        t_zoom_region.t_right_bottom.ui4_x,
        t_zoom_region.t_right_bottom.ui4_y);

    a_zoom_mode_enlarge_region(&t_zoom_region);

}
#endif

INT32 a_gl_zoom_mode_enable(VOID)
{
    return aa_gl_zoom_mode_enable();
}

INT32 a_gl_zoom_mode_disable(VOID)
{
    return aa_gl_zoom_mode_disable();
}

INT32 a_gl_zoom_mode_enlarge_sector(GL_OSD_ZOOM_SECTOR_T* pt_zoom_sector_array, UINT32 ui4_arrayNum)
{
    return aa_gl_zoom_mode_enlarge_sector(pt_zoom_sector_array, ui4_arrayNum);
}

INT32 a_gl_zoom_mode_get_region_size(
    GL_OSD_PLANE_T      e_osd_plane,
    UINT32*             pui4_region_w,
    UINT32*             pui4_region_h)
{
    return aa_gl_zoom_mode_get_region_size(e_osd_plane, pui4_region_w, pui4_region_h);
}

static BOOL                 b_zoom_mode_enable = FALSE;

INT32 aa_gl_zoom_mode_sector_array2out_cropinfo(MI_FB_CropInfo_t *cropinfo,GL_OSD_ZOOM_SECTOR_T at_zoom_sector_array)
{

        /*input area*/
        cropinfo->inputRect.u16Xpos  =  at_zoom_sector_array.ui4_X;
        cropinfo->inputRect.u16Ypos  =  at_zoom_sector_array.ui4_Y;
        cropinfo->inputRect.u16Width = (fb_osd_menu_vinfo.xres / 2);
        cropinfo->inputRect.u16Height= (fb_osd_menu_vinfo.yres / 2);

        cropinfo->outputRect.u16Xpos     = 0;
        cropinfo->outputRect.u16Ypos     = 0;
        cropinfo->outputRect.u16Width    = fb_osd_menu_vinfo.xres;
        cropinfo->outputRect.u16Height   = fb_osd_menu_vinfo.yres;

        aa_print_crop_info(cropinfo);


    return ZMR_OK;
}

INT32 aa_gl_zoom_mode_sector_array2out_cropinfo_sch(MI_FB_CropInfo_t *cropinfo,GL_OSD_ZOOM_SECTOR_T at_zoom_sector_array)
{

        /*input area*/
        cropinfo->inputRect.u16Xpos  =  at_zoom_sector_array.ui4_X;
        cropinfo->inputRect.u16Ypos  =  at_zoom_sector_array.ui4_Y;
        cropinfo->inputRect.u16Width = (fb_osd_sch_vinfo.xres / 2);
        cropinfo->inputRect.u16Height= (fb_osd_sch_vinfo.yres / 2);

        cropinfo->outputRect.u16Xpos     = 0;
        cropinfo->outputRect.u16Ypos     = 0;
        cropinfo->outputRect.u16Width    = fb_osd_sch_vinfo.xres;
        cropinfo->outputRect.u16Height   = fb_osd_sch_vinfo.yres;

        aa_print_crop_info(cropinfo);


    return ZMR_OK;
}

//Enter zoom mode, save the current setting
INT32 aa_gl_zoom_mode_enable(VOID)
{
    INT32 i4_ret ;
    if (b_zoom_mode_enable)
    {
        DBG_ERROR((" a_zoom_open failed.\n"));
        return GLR_ALREADY_INIT;
    }

    i4_ret = a_zoom_open_fbdev();
    if( i4_ret < 0)
    {
        DBG_ERROR((" a_zoom_open failed.\n"));
        return GLR_INV_HANDLE;
    }

    b_zoom_mode_enable = TRUE;

    return ZMR_OK;

}

//NOTE: tv source closed caption(cc) will show on osd 0, can't zoom the cc when zoom mode on
static BOOL nav_zoom_mode_current_is_tv_source_or_COMP_source(VOID)
{
    INT32       i4_ret              = 0;
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1]   = {0};
    UINT8       ui1_crnt_input_src  = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if(ISLR_OK != i4_ret)
    {
        return FALSE;
    }
    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    if(ISLR_OK != i4_ret)
    {
        return FALSE;
    }

    i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    if(ISLR_OK != i4_ret)
    {
        return FALSE;
    }
    if((INP_SRC_TYPE_TV == t_isl_rec.e_src_type) ||
            ((INP_SRC_TYPE_AV == t_isl_rec.e_src_type ) &&
                ( DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type
                ||  DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type)))
    {
        return TRUE;
    }
    return FALSE;
}

//#define MTR_OK ((UINT8) 0)
//Exit zoom mode, restore the orignal setting
INT32 aa_gl_zoom_mode_disable(VOID)
{
    MT_RESULT_T             m_ret = MTR_OK;
    INT32                   i = 0;
    GL_OSD_ZOOM_SECTOR_T    at_zoom_sector_array[GL_OSD_PLANE_MAX_NUM];

    if (FALSE == b_zoom_mode_enable)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", " failed, b_zoom_mode_enable = %d.\n\r", b_zoom_mode_enable);
        return ZMR_FAIL;
    }

    c_memset(at_zoom_sector_array, 0, sizeof(GL_OSD_ZOOM_SECTOR_T) * GL_OSD_PLANE_MAX_NUM);

    for (i = 0; i < GL_OSD_PLANE_MAX_NUM; i++)
    {
        at_zoom_sector_array[i].e_plane = i;
        at_zoom_sector_array[i].ui4_X = 0;
        at_zoom_sector_array[i].ui4_Y = 0;
        at_zoom_sector_array[i].ui4_W = 1920;
        at_zoom_sector_array[i].ui4_H = 1080;

        DBG_LOG_PRINT(("{%s %d} plane:%u, zoom_sector[%u, %u, %u, %u].\n\r",
                __FUNCTION__, __LINE__,
                at_zoom_sector_array[i].e_plane,
                at_zoom_sector_array[i].ui4_X,
                at_zoom_sector_array[i].ui4_Y,
                at_zoom_sector_array[i].ui4_W,
                at_zoom_sector_array[i].ui4_H));
    }

    m_ret = ioctl (fb_osd0_handle, FBIOGET_VSCREENINFO, &fb_osd_menu_vinfo);
    if (m_ret != MTR_OK)
    {
        DBG_LOG_PRINT(("{%s %d}get fb_osd_menu_vinfo fail ret=%d.\n", __FUNCTION__, __LINE__, m_ret));
    }

/* origin OSD */
#if 1
       MI_FB_CropInfo_t t_menu_cropinfo_disable = {0};

       t_menu_cropinfo_disable.inputRect.u16Xpos = 0;
       t_menu_cropinfo_disable.inputRect.u16Ypos = 0;
       t_menu_cropinfo_disable.inputRect.u16Width = fb_osd_menu_vinfo.xres;
       t_menu_cropinfo_disable.inputRect.u16Height = fb_osd_menu_vinfo.yres;

       t_menu_cropinfo_disable.outputRect.u16Xpos = 0;
       t_menu_cropinfo_disable.outputRect.u16Ypos = 0;
       t_menu_cropinfo_disable.outputRect.u16Width = fb_osd_menu_vinfo.xres;
       t_menu_cropinfo_disable.outputRect.u16Height = fb_osd_menu_vinfo.yres;
       aa_print_crop_info(&t_menu_cropinfo_disable);

       MI_FB_CropInfo_t t_sch_cropinfo_disable = {0};

#ifdef MT5583_MODEL
       t_sch_cropinfo_disable.inputRect.u16Xpos = 0;
       t_sch_cropinfo_disable.inputRect.u16Ypos = 0;
       t_sch_cropinfo_disable.inputRect.u16Width = fb_osd_menu_vinfo.xres;
       t_sch_cropinfo_disable.inputRect.u16Height = fb_osd_menu_vinfo.yres;

       t_sch_cropinfo_disable.outputRect.u16Xpos = 0;
       t_sch_cropinfo_disable.outputRect.u16Ypos = 0;
       t_sch_cropinfo_disable.outputRect.u16Width = fb_osd_menu_vinfo.xres;
       t_sch_cropinfo_disable.outputRect.u16Height = fb_osd_menu_vinfo.yres;
       aa_print_crop_info(&t_sch_cropinfo_disable);

       m_ret = ioctl (fb_osd0_handle, FBIOSET_CROP_INFO, &t_menu_cropinfo_disable);
       if (m_ret != MTR_OK)
       {
           DBG_LOG_PRINT(("{%s %d}fb_osd0 zoom disable fail ret=%d.\n", __FUNCTION__, __LINE__, m_ret));
       }

       m_ret = ioctl (fb_osd1_handle, FBIOSET_CROP_INFO, &t_sch_cropinfo_disable);
       if (m_ret != MTR_OK)
       {
           DBG_LOG_PRINT(("{%s %d}fb_osd1 zoom disable fail ret=%d. try another size\n", __FUNCTION__, __LINE__, m_ret));

           t_sch_cropinfo_disable.inputRect.u16Xpos = 0;
           t_sch_cropinfo_disable.inputRect.u16Ypos = 0;
           t_sch_cropinfo_disable.inputRect.u16Width = fb_osd_sch_vinfo.xres;
           t_sch_cropinfo_disable.inputRect.u16Height = fb_osd_sch_vinfo.yres;

           t_sch_cropinfo_disable.outputRect.u16Xpos = 0;
           t_sch_cropinfo_disable.outputRect.u16Ypos = 0;
           t_sch_cropinfo_disable.outputRect.u16Width = fb_osd_sch_vinfo.xres;
           t_sch_cropinfo_disable.outputRect.u16Height = fb_osd_sch_vinfo.yres;
           aa_print_crop_info(&t_sch_cropinfo_disable);

           m_ret = ioctl (fb_osd1_handle, FBIOSET_CROP_INFO, &t_sch_cropinfo_disable);

           if (m_ret != MTR_OK)
           {
               DBG_LOG_PRINT(("{%s %d}fb_osd1 zoom disable fail ret=%d.\n", __FUNCTION__, __LINE__, m_ret));
           }
       }

#else
       t_sch_cropinfo_disable.inputRect.u16Xpos = 0;
       t_sch_cropinfo_disable.inputRect.u16Ypos = 0;
       t_sch_cropinfo_disable.inputRect.u16Width = fb_osd_sch_vinfo.xres;
       t_sch_cropinfo_disable.inputRect.u16Height = fb_osd_sch_vinfo.yres;

       t_sch_cropinfo_disable.outputRect.u16Xpos = 0;
       t_sch_cropinfo_disable.outputRect.u16Ypos = 0;
       t_sch_cropinfo_disable.outputRect.u16Width = fb_osd_sch_vinfo.xres;
       t_sch_cropinfo_disable.outputRect.u16Height = fb_osd_sch_vinfo.yres;
       aa_print_crop_info(&t_sch_cropinfo_disable);

       /*menu,sch*/
       ZOOM_CHECK_RET(ioctl (fb_osd0_handle, FBIOSET_CROP_INFO, &t_menu_cropinfo_disable));
       ZOOM_CHECK_RET(ioctl (fb_osd1_handle, FBIOSET_CROP_INFO, &t_sch_cropinfo_disable));
#endif




#endif

    b_zoom_mode_enable = FALSE;

    /* close file handle */

    ZOOM_CHECK_RET(a_zoom_close_fbdev());


    return GLR_OK;

}



//Enlarge the specify sector of specify plane  to fullscreen
INT32 aa_gl_zoom_mode_enlarge_sector(GL_OSD_ZOOM_SECTOR_T* pt_zoom_sector_array, UINT32 ui4_arrayNum)
{
    INT32       i;
    MT_RESULT_T m_ret;
    INT32   ui4_i;

    if (!b_zoom_mode_enable)
    {
        return GLR_NOT_INIT;
    }

    if (pt_zoom_sector_array == NULL || ui4_arrayNum == 0 || ui4_arrayNum > GL_OSD_PLANE_MAX_NUM)
    {
        return GLR_INV_ARG;
    }


    for (ui4_i = 0; ui4_i < ui4_arrayNum; ui4_i++)
    {
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "item[%u]: plane:%u, zoom_sector[%u, %u, %u, %u].\n\r",
                ui4_i,
                pt_zoom_sector_array[ui4_i].e_plane,
                pt_zoom_sector_array[ui4_i].ui4_X,
                pt_zoom_sector_array[ui4_i].ui4_Y,
                pt_zoom_sector_array[ui4_i].ui4_W,
                pt_zoom_sector_array[ui4_i].ui4_H);
    }



    for (i = 0; i < ui4_arrayNum; i++)
    {
        if (pt_zoom_sector_array[i].ui4_W == 0 ||
            pt_zoom_sector_array[i].ui4_H == 0)
        {
            DBG_LOG_PRINT(("{%s %d}plane_%d size is zero.\n", __FUNCTION__, __LINE__, pt_zoom_sector_array[i].e_plane));
            continue;
        }
        else
        {
            if(0 == i) // menu
            {
                /* to enlarge osd:0->menu,1->sch,2->netflix*/
                aa_gl_zoom_mode_sector_array2out_cropinfo(&t_fb_osd_menu_output_enlarge,pt_zoom_sector_array[i]);

                m_ret = aa_gl_zoom_mode_enlarge_cropinfo_region(fb_osd0_handle, t_fb_osd_menu_output_enlarge);
                if (m_ret != MTR_OK)
                {
                    DBG_ERROR(("{%s %d}MTOSD_PLA_ZoomIn fail ret=%d.\n", __FUNCTION__, __LINE__, m_ret));
                    return GLR_DRV_ERROR;
                }
                DBG_INFO(("[zoom mode fusion1.5] {%s %s() %d}. \n",__FILE__, __FUNCTION__, __LINE__));
            }
            else if(1 == i) // sch
            {
                /* to enlarge osd:0->menu,1->sch,2->netflix*/
                aa_gl_zoom_mode_sector_array2out_cropinfo_sch(&t_fb_osd_sch_output_enlarge,pt_zoom_sector_array[i]);

                if(0 == fb_osd1_handle)
                {
                    DBG_ERROR((" aa_zoom_mode_enlarge_region**** failed.\n"));
                    return GLR_INV_HANDLE;
                }

                //NOTE: if TV source , cc (osd 0) will ne be enlarge when zoom mode for on

                if(nav_zoom_mode_current_is_tv_source_or_COMP_source())
                {
                     /*input area*/
                     //CC size should be the same as menu.
                    t_fb_osd_sch_output_enlarge.inputRect.u16Xpos       =  0;
                    t_fb_osd_sch_output_enlarge.inputRect.u16Ypos       =  0;
                    t_fb_osd_sch_output_enlarge.inputRect.u16Width      = fb_osd_menu_vinfo.xres; //1920
                    t_fb_osd_sch_output_enlarge.inputRect.u16Height     = fb_osd_menu_vinfo.yres; //1080
                    t_fb_osd_sch_output_enlarge.outputRect.u16Xpos      = 0;
                    t_fb_osd_sch_output_enlarge.outputRect.u16Ypos      = 0;
                    t_fb_osd_sch_output_enlarge.outputRect.u16Width     = fb_osd_menu_vinfo.xres;//1920
                    t_fb_osd_sch_output_enlarge.outputRect.u16Height    = fb_osd_menu_vinfo.yres;//1080

                    aa_print_crop_info(&t_fb_osd_sch_output_enlarge);
                }

                m_ret = aa_gl_zoom_mode_enlarge_cropinfo_region(fb_osd1_handle, t_fb_osd_sch_output_enlarge);
                if (m_ret != MTR_OK)
                {
                    DBG_LOG_PRINT(("{%s %d}fb_osd1_handle enlarge fail ret=%d.\n", __FUNCTION__, __LINE__, m_ret));
                    //MVD-1834.
                    //If menu OSD((0 == i) enlarge successfully.DO NOT return ERROR here.
                    //return GLR_DRV_ERROR;
                }
                //ZOOM_CHECK_RET(ioctl (fb_osd1_handle, FBIOSET_CROP_INFO, &t_fb_osd_sch_output_enlarge));
                DBG_INFO(("[zoom mode fusion1.5] {%s %s() %d}. sch \n",__FILE__, __FUNCTION__, __LINE__));
            }
            else if(2 == i) // netflix
            {
                DBG_INFO(("[zoom mode fusion1.5] {%s %s() %d}. netflix \n",__FILE__, __FUNCTION__, __LINE__));
            }

        }
    }

    return ZMR_OK;
}

INT32 aa_gl_zoom_mode_get_region_size(
    GL_OSD_PLANE_T      e_osd_plane,
    UINT32*             pui4_region_w,
    UINT32*             pui4_region_h)
{

    if (NULL == pui4_region_w || NULL == pui4_region_h)
    {
        DBG_ERROR(("{%s %d} invalid arg.\n", __FUNCTION__, __LINE__));
        return ZMR_INV_ARG;
    }

    if(GL_OSD_PLANE_2 == e_osd_plane) //menu
    {
        if(fb_osd_menu_vinfo.xres != 0 && fb_osd_menu_vinfo.yres != 0)
        {
            *pui4_region_w = (UINT32) fb_osd_menu_vinfo.xres;
            *pui4_region_h = (UINT32) fb_osd_menu_vinfo.yres;

             return ZMR_OK;
        }
    }
    else if(GL_OSD_PLANE_3 == e_osd_plane) //sch
    {
        if(fb_osd_sch_vinfo.xres != 0 && fb_osd_sch_vinfo.yres != 0)
        {
            *pui4_region_w = (UINT32) fb_osd_sch_vinfo.xres;
            *pui4_region_h = (UINT32) fb_osd_sch_vinfo.yres;

             return ZMR_OK;
        }
    }
    else if(GL_OSD_PLANE_1 == e_osd_plane) //NETFLIX
    {
//        DBG_ERROR(("{%s %d} is not support !!! error .\n", __FUNCTION__, __LINE__));
        return ZMR_INV_ARG;
    }

    return ZMR_INV_ARG;

}

INT32 aa_gl_zoom_mode_enlarge_cropinfo_region(INT32 fb_osd_handle,  MI_FB_CropInfo_t cropinfo)

{
    if(0 == fb_osd_handle)
    {
        DBG_ERROR((" aa_zoom_mode_enlarge_region**** failed.\n"));
        return ZMR_INV_ARG;
    }

    ZOOM_CHECK_RET(ioctl (fb_osd_handle, FBIOSET_CROP_INFO, &cropinfo));

    return ZMR_OK;

}

void printFixedInfo (struct fb_fix_screeninfo * pfixinfoStruct)
{
DBG_LOG_PRINT(("[zoom mode 1.5] %s(),%d, **************  Fixed screen info:\n"
    "\tid: %s\n"
    "\tsmem_start: 0x%lx\n"
    "\tsmem_len: %d\n"
    "\ttype: %d\n"
    "\ttype_aux: %d\n"
    "\tvisual: %d\n"
    "\txpanstep: %d\n"
    "\typanstep: %d\n"
    "\tywrapstep: %d\n"
    "\tline_length: %d\n"
    "\tmmio_start: 0x%lx\n"
    "\tmmio_len: %d\n"
    "\taccel: %d\n"
    "\n",
    __FUNCTION__,__LINE__,
    pfixinfoStruct->id, pfixinfoStruct->smem_start, pfixinfoStruct->smem_len, pfixinfoStruct->type,
    pfixinfoStruct->type_aux, pfixinfoStruct->visual, pfixinfoStruct->xpanstep, pfixinfoStruct->ypanstep,
    pfixinfoStruct->ywrapstep, pfixinfoStruct->line_length, pfixinfoStruct->mmio_start,
    pfixinfoStruct->mmio_len, pfixinfoStruct->accel));

    return;

}

void  printVariableInfo (struct fb_var_screeninfo * pvarinfoStruct)
{
DBG_LOG_PRINT(("[zoom mode 1.5] %s(),%d, ************** Variable screen info:\n"
    "\txres: %d\n"
    "\tyres: %d\n"
    "\txres_virtual: %d\n"
    "\tyres_virtual: %d\n"
    "\tyoffset: %d\n"
    "\txoffset: %d\n"
    "\tbits_per_pixel: %d\n"
    "\tgrayscale: %d\n"
    "\tred: offset: %2d, length: %2d, msb_right: %2d\n"
    "\tgreen: offset: %2d, length: %2d, msb_right: %2d\n"
    "\tblue: offset: %2d, length: %2d, msb_right: %2d\n"
    "\ttransp: offset: %2d, length: %2d, msb_right: %2d\n"
    "\tnonstd: %d\n"
    "\tactivate: %d\n"
    "\theight: %d\n"
    "\twidth: %d\n"
    "\taccel_flags: 0x%x\n"
    "\tpixclock: %d\n"
    "\tleft_margin: %d\n"
    "\tright_margin: %d\n"
    "\tupper_margin: %d\n"
    "\tlower_margin: %d\n"
    "\thsync_len: %d\n"
    "\tvsync_len: %d\n"
    "\tsync: %d\n"
    "\tvmode: %d\n"
    "\n",
    __FUNCTION__,__LINE__,
    pvarinfoStruct->xres, pvarinfoStruct->yres, pvarinfoStruct->xres_virtual, pvarinfoStruct->yres_virtual,
    pvarinfoStruct->yoffset, pvarinfoStruct->xoffset, pvarinfoStruct->bits_per_pixel,
    pvarinfoStruct->grayscale, pvarinfoStruct->red.offset, pvarinfoStruct->red.length,
    pvarinfoStruct->red.msb_right, pvarinfoStruct->green.offset, pvarinfoStruct->green.length,
    pvarinfoStruct->green.msb_right, pvarinfoStruct->blue.offset, pvarinfoStruct->blue.length,
    pvarinfoStruct->blue.msb_right, pvarinfoStruct->transp.offset, pvarinfoStruct->transp.length,
    pvarinfoStruct->transp.msb_right, pvarinfoStruct->nonstd, pvarinfoStruct->activate,
    pvarinfoStruct->height, pvarinfoStruct->width, pvarinfoStruct->accel_flags, pvarinfoStruct->pixclock,
    pvarinfoStruct->left_margin, pvarinfoStruct->right_margin, pvarinfoStruct->upper_margin,
    pvarinfoStruct->lower_margin, pvarinfoStruct->hsync_len, pvarinfoStruct->vsync_len,
    pvarinfoStruct->sync, pvarinfoStruct->vmode));

    return;

}

INT32 aa_zoom_print_crop_info(MI_FB_CropInfo_t cropinfo)
{
     DBG_LOG_PRINT(("\n\n get The crop info is:\n\t input[%d,%d,%d,%d] output[%d,%d,%d,%d] \n\n",\
        cropinfo.inputRect.u16Xpos,cropinfo.inputRect.u16Ypos,cropinfo.inputRect.u16Width,cropinfo.inputRect.u16Height,\
        cropinfo.outputRect.u16Xpos,cropinfo.outputRect.u16Ypos,cropinfo.outputRect.u16Width,cropinfo.outputRect.u16Height));

     return 1;
}

INT32 aa_print_crop_info(MI_FB_CropInfo_t *cropinfo)
{
     DBG_INFO(("\n\n [zoom mode 1.5] enter:%s(),%d,get The crop info is:\n\t input[%d,%d,%d,%d] output[%d,%d,%d,%d] \n\n",\
         __FUNCTION__,__LINE__,\
        cropinfo->inputRect.u16Xpos,cropinfo->inputRect.u16Ypos,cropinfo->inputRect.u16Width,cropinfo->inputRect.u16Height,\
        cropinfo->outputRect.u16Xpos,cropinfo->outputRect.u16Ypos,cropinfo->outputRect.u16Width,cropinfo->outputRect.u16Height));

     return 1;
}

INT32 a_zoom_open_fbdev(VOID)
{

    DBG_INFO(("[zoom mode] enter:%s(),%d \n",__FUNCTION__,__LINE__));

    fb_osd0_handle = open (DevNode0, O_RDWR);
    ZOOM_CHECK_RET(fb_osd0_handle);
    fb_osd1_handle = open (DevNode1, O_RDWR);
    ZOOM_CHECK_RET(fb_osd1_handle);

    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd0_handle, FBIOGET_FSCREENINFO, &fb_osd_menu_finfo));
    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd0_handle, FBIOGET_VSCREENINFO, &fb_osd_menu_vinfo));
    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd0_handle, FBIOGET_CROP_INFO, &t_fb_osd_menu_cropinfo_open));

    /*output info*/
//    aa_zoom_print_crop_info(t_fb_osd_menu_cropinfo_open);


    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd1_handle, FBIOGET_FSCREENINFO, &fb_osd_sch_finfo));
    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd1_handle, FBIOGET_VSCREENINFO, &fb_osd_sch_vinfo));
    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd1_handle, FBIOGET_CROP_INFO, &t_fb_osd_sch_cropinfo_open));

#ifdef MT5583_MODEL//for MVD-1591. due to layer1 initial size is 1080P by CC init. re-set layer1 size as 720P for mt5583.
    fb_osd_sch_vinfo.xres = 1280;//CSP OSD width
    fb_osd_sch_vinfo.yres = 720;//CSP OSD height

    ZOOM_CHECK_IOCTLRET(ioctl (fb_osd1_handle, FBIOPUT_VSCREENINFO, &fb_osd_sch_vinfo));
#endif


     DBG_INFO(("[zoom mode] FINISH:%s(),%d \n",__FUNCTION__,__LINE__));

     return ZMR_OK;

 IOCTLFAIL:
        ZOOM_CHECK_RET(a_zoom_close_fbdev());

     return ZMR_FAIL;

}

INT32 a_zoom_close_fbdev(VOID)
{

    if(fb_osd0_handle == 0 || fb_osd1_handle == 0)
    {
        DBG_INFO(("[zoom mode 1.5]  %s(),%d FILE handle[0,1,2] = [%d,%d,%d] close error!!!! ****** \n",__FUNCTION__,__LINE__,
                        fb_osd0_handle,fb_osd1_handle,fb_osd2_handle));
        return ZMR_FAIL;
    }

    ZOOM_CHECK_RET(close(fb_osd0_handle));//menu
    ZOOM_CHECK_RET(close(fb_osd1_handle));//sch
//    ZOOM_CHECK_RET(close(fb_osd2_handle));

    fb_osd0_handle = 0;
    fb_osd1_handle = 0;
    fb_osd2_handle = 0;

    return ZMR_OK;
}

#endif /*APP_ZOOM_MODE_SUPPORT*/

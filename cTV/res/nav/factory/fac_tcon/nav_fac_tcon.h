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
 * $RCSfile: nav_fac_tcon.h,v $
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
#ifndef _NAV_FAC_TCON_H_
#define _NAV_FAC_TCON_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "BUF08630.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
struct _NAV_FAC_TCON_VIEW_HDLR_T;

struct _NAV_FAC_TCON_T;

typedef INT32 (*nav_fac_tcon_view_init_fct)(
                    struct _NAV_FAC_TCON_T*     pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
typedef INT32 (*nav_fac_tcon_view_deinit_fct)(
                    VOID
                    );
typedef BOOL (*nav_fac_tcon_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*nav_fac_tcon_view_activate_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*nav_fac_tcon_view_hide)(
                    VOID
                    );
typedef struct _NAV_FAC_TCON_VIEW_HDLR_T
{
    nav_fac_tcon_view_init_fct              pf_init;
    nav_fac_tcon_view_deinit_fct            pf_deinit;
    nav_fac_tcon_view_is_key_handler_fct    pf_is_key_handler;
    nav_fac_tcon_view_activate_fct          pf_activate;
    nav_fac_tcon_view_hide                  pf_hide;
} NAV_FAC_TCON_VIEW_HDLR_T;

typedef struct _NAV_FAC_TCON_T
{
    BOOL                                    b_is_on;
    NAV_FAC_TCON_VIEW_HDLR_T                t_view_hdlr;
} NAV_FAC_TCON_T;

typedef struct _NAV_FAC_TCON_DEFAULT_T
{
    UINT32      u4PanelIndex;                         /* Panel Index */
    UINT16      u2GammaDef[8];                        /* Gamma Default Value */
    UINT16      u2VComDef;                            /* VCom Default Value */
    UINT16      u2VComGainDef;						  /* VCom Gain Default Value */ //sam 101124

    UINT16      ui2_vcom_max;           // Request by LG(Snag Yeul Yoo) 2011_03_01
    UINT16      ui2_vcom_min;           // Request by LG(Snag Yeul Yoo) 2011_03_01
} NAV_FAC_TCON_DEFAULT_T;


typedef enum
{
    NAV_FAC_TCON_MENU_VCOM_VALUE = 0,   // Menu Item 1
    NAV_FAC_TCON_MENU_VCOM_STORE,       // Menu Item 2
    NAV_FAC_TCON_MENU_GAMMA1,           // Menu Item 3
    NAV_FAC_TCON_MENU_GAMMA2,           // Menu Item 4
    NAV_FAC_TCON_MENU_GAMMA3,           // Menu Item 5
    NAV_FAC_TCON_MENU_GAMMA4,           // Menu Item 6
    NAV_FAC_TCON_MENU_GAMMA5,           // Menu Item 7
    NAV_FAC_TCON_MENU_GAMMA6,           // Menu Item 8
    NAV_FAC_TCON_MENU_GAMMA7,           // Menu Item 9
    NAV_FAC_TCON_MENU_GAMMA8,           // Menu Item 10
    NAV_FAC_TCON_MENU_EXIT,             // Menu Item 11
    NAV_FAC_TCON_MENU_MAX_ELEM          // Max Element
} NAV_FAC_TCON_SETUP_MENU_ITEM_T;


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#define TCON_CHK_FAIL(_ret)     \
do{                             \
    if (_ret < 0)               \
    {                           \
        DBG_LOG_PRINT("<TC(ON> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret));   \
        return _ret;       \
    }                           \
}while(FALSE)


#define TCON_OK                 ((INT32)0)
#define TCON_FAIL                 ((INT32)-1)
#define TCON_READ_FAIL         ((INT32)-2)
#define TCON_WRITE_FAIL        ((INT32)-3)
#define TCON_INV_ARG            ((INT32)-4)

#define TCON_EXTERNAL_NVRAM_W_ENABLE 1//sam test for 37" 0

#if 0 
extern INT32 nav_fac_tcon_get_setup_min_max(
                    UINT16              ui2_idx,
                    INT16*             pui2_min,
                    INT16*             pui2_max
                    );                   
extern INT32 nav_fac_tcon_get_setup_value(
                    UINT16              ui2_idx,
                    INT32*             pui4_val
                    );
extern INT32 nav_fac_tcon_set_setup_value(
                    UINT16              ui2_idx,
                    INT32              ui4_val
                    );
#endif
extern INT32 nav_fac_tcon_view_register_default_hdlr(
                    NAV_FAC_TCON_VIEW_HDLR_T*       pt_view_hdlr
                    );
extern INT32 a_nav_fac_tcon_register(
                    struct _NAV_FAC_TCON_VIEW_HDLR_T*       pt_view_hdlr
                    );

extern INT32 fac_test_ptn_page_show(UINT16 ptn_sel);

extern INT32 fac_test_ptn_page_hide(VOID);

extern BOOL fac_vcom_init_get_status(VOID);

extern VOID fac_vcom_init_set_status(BOOL bVal);

extern BOOL fac_test_ptn_get_status(VOID);

extern VOID fac_test_ptn_set_status(BOOL bVal);

extern INT32 fac_initial_vcom (BOOL b_interanl_pattern, UINT16 *pui2_current_vcom );

extern INT32 nav_fac_tcon_load_def(VOID);

extern INT32 fac_copy_data_from_buf(HANDLE_T  h_surf, HANDLE_T h_surf_buf);

extern INT32 nav_fac_sif_x_read(UINT8 u1CHannelID,UINT16 u2ClkDiv,UINT8 u1DevAddr,INT8 u1WordAddrNum,
                                    UINT32 u4WordAddr,UINT8 * pu1Buf,UINT16 u2ByteCnt);

extern INT32 nav_fac_sif_x_write(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum,
                                     UINT32 u4WordAddr, UINT8 * pu1Buf, UINT16 u2ByteCnt);
#endif /* _NAV_FAC_TCON_H_ */

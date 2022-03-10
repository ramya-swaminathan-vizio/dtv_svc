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
 * $RCSfile: nav_img.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/4 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 6995d119ffe2091e31d2bc97171ebd19 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl_common.h"
#include "c_wgl_image.h"

#include "nav/navigator.h"

#include "res/nav/nav_img_960x540_8888.i"
#include "res/nav/toast_msg_icon/toast_msg_icon.i"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_pwd_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_pwd_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_frame_bk_bmp,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_docu_ui_osd_bk
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_docu_ui_osd_bk(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_dock_ui_bk,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_signal_1of5
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_signal_1of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_signal_1of5,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_signal_1of5
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_signal_2of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }
    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_signal_2of5,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_signal_1of5
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_signal_3of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_signal_3of5,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_signal_1of5
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_signal_4of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_signal_4of5,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_signal_1of5
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_signal_5of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_signal_5of5,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_wired_connect
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_wired_connect(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* info */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_wired_connect,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_network_notconnect
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_network_notconnect(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* info */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_network_notconnect,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_video_sel_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_video_sel_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_nav_frame_bk_bmp,
                    ph_img_tpl
                    );


    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_scr_svr_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_scr_svr_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 { INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_warning_info_frame_bk_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_default_btn_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_default_btn_hlt_bk_img_tpl(WGL_HIMG_TPL_T*   ph_img_tpl)
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_Warning_Bar_button_hlt,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_default_btn_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_default_btn_bk_img_tpl(WGL_HIMG_TPL_T*   ph_img_tpl)
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_Warning_Bar_button,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_default_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_default_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_Warning_Bar,
                    ph_img_tpl
                    );


    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_cc_info_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_cc_info_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_cc_box_bk_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_cc_info_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_cc_info_icon_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_caption_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_ch_detail_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_ch_detail_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_ch_list_frame_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_prog_detail_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_prog_detail_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_frame_bk_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_ch_list_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_ch_list_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_ch_list_frame_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_fav_list_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_fav_list_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_ch_list_frame_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_hlt_bar_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_hlt_bar_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_nav_hlt_bar_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_pop_music_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_pop_music_icon_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pop_music_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#ifdef APP_CEC_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_cec_create_cmd_list_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_cmd_list_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_frame_bk_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_act_src_icon_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_act_src_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_stop_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_stop_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_play_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_play_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_eject_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_eject_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_pause_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_pause_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_fast_forward_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_fast_forward_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_fast_reverse_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_fast_reverse_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_skip_forward_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_skip_forward_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_skip_reverse_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_skip_reverse_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_cec_create_deck_panel_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_cec_deck_panel_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif /*#ifdef APP_CEC_SUPPORT*/

#if defined (APP_UPG_SUPPORT) || defined (APP_NAV_REC_SUPPORT)
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_upg_img_bk,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_hl_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_hl_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_nav_upg_img_hl_bk,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_back_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_back_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_back,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_arrow_up_down_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_arrow_up_down_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_arrow_up_down,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_exit_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_exit_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_exit,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_power_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_power_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_power,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_scroll_bar_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_scroll_bar_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_V_ONLY,
                    &t_g_nav_upg_scroll_bar_bk_img,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_scroll_bar_focus_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_scroll_bar_focus_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_V_ONLY,
                    &t_g_nav_upg_scroll_bar_focus_img,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_enter_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_enter_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_enter,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_info_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_info_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* info */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_info,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_scan_bar_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_scan_bar_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_nav_upg_img_scan_bar_bk,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_scan_bar_level_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_scan_bar_level_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_nav_upg_img_scan_bar_level,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_item_ok_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_item_ok_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* info */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_item_ok,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_item_progress_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_item_progress_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* info */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_item_progress,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_item_fail_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_upg_item_fail_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* info */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_item_error,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_1x_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_1x_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_2x_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_2x_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_4x_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_4x_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_8x_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_8x_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_16x_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_16x_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_32x_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_32x_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_tshift_scale_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_tshift_scale_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_tshift_crnt_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_tshift_crnt_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_record_icon_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_rec_icon_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_pvr_line_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

#ifdef APP_PORTING
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_pvr_line_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_pvr_line_littel_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
#if 0
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_pvr_line_littel_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }
#endif

	*ph_img_tpl = NULL_HANDLE;

    return NAVR_OK;
}

#endif

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_nav_ib_info_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_ib_info_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_nav_ib_warning_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_ib_warning_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_nav_ib_urgent_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_ib_urgent_img,
                    ph_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

#ifdef APP_NAV_REC_PVR_SCH_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_reminder_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_upg_img_bk,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_exit_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_reminder_exit_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_exit,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_arrow_up_down_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_reminder_arrow_up_down_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_upg_img_arrow_up_down,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_upg_arrow_up_down_icon_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_reminder_add_icon_tpl(
								WGL_HIMG_TPL_T*             pt_img_tpl
								)
{
	INT32 i4_ret;

	if (pt_img_tpl == NULL) {
		return NAVR_FAIL;
	}

	/* arrow up */
	i4_ret = c_wgl_img_tpl_create(
					WGL_IMG_ST_NO_SEGMENT,
					&t_g_nav_img_add,
					pt_img_tpl
					);
	if(WGLR_OK != i4_ret){
		return NAVR_FAIL;
	}

	return NAVR_OK;
}

#endif /*APP_NAV_REC_PVR_SCH_SUPPORT*/

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_vol_bar_audsys_bk
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_vol_bar_audsys_bk(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_vol_bar_audsys_bk,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_vol_ctrl_off_bk
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_vol_ctrl_off_bk(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* vol ctrl off */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_vol_ctrl_off_bk_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_pwd_dlg_bk
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_pwd_dlg_bk(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     )
  {
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
         return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                     WGL_IMG_ST_NO_SEGMENT,
                     &t_g_nav_pwd_dlg_bk_img,
                     ph_img_tpl
                     );

     if(WGLR_OK != i4_ret){
         return NAVR_FAIL;
     }

     return NAVR_OK;
 }

 /*-----------------------------------------------------------------------------
  * Name
  *      nav_img_create_pwd_dlg_input
  * Description
  * Input arguments
  * Output arguments
  * Returns
  *---------------------------------------------------------------------------*/
  INT32 nav_img_create_pwd_dlg_input(
                      WGL_HIMG_TPL_T*             ph_img_tpl
                      )
   {
      INT32 i4_ret;

      if (ph_img_tpl == NULL) {
          return NAVR_FAIL;
      }

      i4_ret = c_wgl_img_tpl_create(
                      WGL_IMG_ST_NO_SEGMENT,
                      &t_g_nav_pwd_dlg_input_img,
                      ph_img_tpl
                      );

      if(WGLR_OK != i4_ret){
          return NAVR_FAIL;
      }

      return NAVR_OK;
  }


  /*-----------------------------------------------------------------------------
   * Name
   *      nav_img_create_pwd_dlg_select
   * Description
   * Input arguments
   * Output arguments
   * Returns
   *---------------------------------------------------------------------------*/
   INT32 nav_img_create_pwd_dlg_select(
                       WGL_HIMG_TPL_T*             ph_img_tpl
                       )
    {
       INT32 i4_ret;

       if (ph_img_tpl == NULL) {
           return NAVR_FAIL;
       }

       i4_ret = c_wgl_img_tpl_create(
                       WGL_IMG_ST_NO_SEGMENT,
                       &t_g_nav_pwd_dlg_select_img,
                       ph_img_tpl
                       );

       if(WGLR_OK != i4_ret){
           return NAVR_FAIL;
       }

       return NAVR_OK;
   }
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_scr_svr_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_pop_warning_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_warning_info_frame_bk_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_pop_warning_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_img_create_pop_warning_btn_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pop_warning_msg_btn,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_revolt_misc_bk
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ---------------------------------------------------------------------------*/
 INT32 nav_img_create_revolt_misc_bk(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

     /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_nav_revolt_misc_bk_img,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 nav_img_create_vol_gradient_btm(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
     INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_vol_gradient_btm,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 nav_img_create_vol_inactive(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_vol_inactive,
                    ph_img_tpl
                    );


    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 nav_img_create_vol_zoom_inactive(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_vol_zoom_inactive,
                    ph_img_tpl
                    );


    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 nav_img_create_vol_toast_box(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_vol_toast_box,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *     nav_img_create_tuner_setup_bg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ---------------------------------------------------------------------------*/
 INT32 nav_img_create_tuner_setup_bg(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

     /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_tuner_setup_bg_fill,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *     nav_img_create_tuner_track_mute_fill
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ---------------------------------------------------------------------------*/
 INT32 nav_img_create_tuner_track_mute_fill(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

     /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_tuner_track_mute_fill,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *     nav_img_create_tuner_pb_bg_fill
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ---------------------------------------------------------------------------*/
 INT32 nav_img_create_tuner_pb_bg_fill(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    )
 {
    INT32 i4_ret;

    if (pt_img_tpl == NULL) {
        return NAVR_FAIL;
    }

     /* arrow up */
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_tuner_pb_bg_fill,
                    pt_img_tpl
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_pwd_dlg_select_pin_box
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_pwd_dlg_select_pin_box(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     )
  {
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
         return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                     WGL_IMG_ST_HV,
                     &t_g_nav_pwd_dlg_pin_box_img,
                     ph_img_tpl
                     );

     if(WGLR_OK != i4_ret){
         return NAVR_FAIL;
     }

     return NAVR_OK;
 }


/*-----------------------------------------------------------------------------
* Name
*     nav_img_create_pwd_dlg_bk_white_line
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
INT32 nav_img_create_pwd_dlg_bk_white_line(
                      WGL_HIMG_TPL_T*             ph_img_tpl
                      )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
          return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                      WGL_IMG_ST_NO_SEGMENT,
                      &t_g_nav_banner_new_bg_info_toast_img,
                      ph_img_tpl
                      );

    if(WGLR_OK != i4_ret){
          return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
* Name
*     nav_img_create_pwd_dlg_warning_icon
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
INT32 nav_img_create_pwd_dlg_warning_icon(
                      WGL_HIMG_TPL_T*             ph_img_tpl
                      )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
          return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                      WGL_IMG_ST_NO_SEGMENT,
                      &t_g_pwd_dlg_warning_icon,
                      ph_img_tpl
                      );

    if(WGLR_OK != i4_ret){
          return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_pwd_dlg_input_pin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_pwd_dlg_input_pin(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     )
  {
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
         return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                     WGL_IMG_ST_NO_SEGMENT,
                     &t_g_nav_pwd_dlg_input_pin_img,
                     ph_img_tpl
                     );

     if(WGLR_OK != i4_ret){
         return NAVR_FAIL;
     }

     return NAVR_OK;
 }

 /*-----------------------------------------------------------------------------
   * Name
   *      nav_img_create_remote_link_icon
   * Description
   * Input arguments
   * Output arguments
   * Returns
   *---------------------------------------------------------------------------*/
   INT32 nav_img_create_remote_link_icon(
                       WGL_HIMG_TPL_T*             ph_img_tpl
                       )
    {
       INT32 i4_ret;

       if (ph_img_tpl == NULL) {
           return NAVR_FAIL;
       }

       i4_ret = c_wgl_img_tpl_create(
                       WGL_IMG_ST_NO_SEGMENT,
                       &t_g_remote_link_icon,
                       ph_img_tpl
                       );

       if(WGLR_OK != i4_ret){
           return NAVR_FAIL;
       }

       return NAVR_OK;
   }

 /*-----------------------------------------------------------------------------
  * Name
  *      nav_img_create_remote_input_icon
  * Description
  * Input arguments
  * Output arguments
  * Returns
  *---------------------------------------------------------------------------*/
  INT32 nav_img_create_remote_input_icon(
                      WGL_HIMG_TPL_T*             ph_img_tpl
                      )
   {
      INT32 i4_ret;

      if (ph_img_tpl == NULL) {
          return NAVR_FAIL;
      }

      i4_ret = c_wgl_img_tpl_create(
                      WGL_IMG_ST_NO_SEGMENT,
                      &t_g_remote_input_icon,
                      ph_img_tpl
                      );

      if(WGLR_OK != i4_ret){
          return NAVR_FAIL;
      }

      return NAVR_OK;
  }

 /*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_remote_play_pause
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_remote_play_pause(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     )
  {
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
         return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                     WGL_IMG_ST_NO_SEGMENT,
                     &t_g_remote_play_pause_24,
                     ph_img_tpl
                     );

     if(WGLR_OK != i4_ret){
         return NAVR_FAIL;
     }

     return NAVR_OK;
 }

 /*-----------------------------------------------------------------------------
 * Name
 *      nav_img_create_retail_mode_vizio_logo
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 nav_img_create_retail_mode_vizio_logo(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     )
  {
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
         return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                     WGL_IMG_ST_NO_SEGMENT,
                     &t_g_remote_vizio_logo,
                     ph_img_tpl
                     );

     if(WGLR_OK != i4_ret){
         return NAVR_FAIL;
     }

     return NAVR_OK;
 }

INT32 nav_img_create_pwd_dlg_no_match_pic(
                WGL_HIMG_TPL_T*             ph_img_tpl
                )
{
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pin_no_match_img,
                    ph_img_tpl
                    );

     if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
     }

     return NAVR_OK;
}

INT32 nav_img_create_pwd_dlg_down_pic(
                WGL_HIMG_TPL_T*             ph_img_tpl
                )
{
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pin_down_img,
                    ph_img_tpl
                    );

     if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
     }

     return NAVR_OK;
}

INT32 nav_img_create_pwd_dlg_cancel_focus_pic(
                WGL_HIMG_TPL_T*             ph_img_tpl
                )
{
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pin_cancel_focus_img,
                    ph_img_tpl
                    );

     if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
     }

     return NAVR_OK;
}

INT32 nav_img_create_pwd_dlg_cancel_inactive_pic(
                WGL_HIMG_TPL_T*             ph_img_tpl
                )
{
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pin_cancel_inactive_img,
                    ph_img_tpl
                    );

     if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
     }

     return NAVR_OK;
}

INT32 nav_img_create_pwd_dlg_up_pic(
                WGL_HIMG_TPL_T*             ph_img_tpl
                )
{
     INT32 i4_ret;

     if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_nav_pin_up_img,
                    ph_img_tpl
                    );

     if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
     }

     return NAVR_OK;
}




INT32 nav_img_create_arrow_up_down_icon(
                   WGL_HIMG_TPL_T*             ph_img_tpl1,
                   WGL_HIMG_TPL_T*             ph_img_tpl2,
                   WGL_HIMG_TPL_T*             ph_img_tpl3
                   )
{
    INT32 i4_ret;

    if (ph_img_tpl1 == NULL || ph_img_tpl2 == NULL) {
       return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                   WGL_IMG_ST_NO_SEGMENT,
                   &t_g_toast_msg_icon_ok_key,
                   ph_img_tpl1
                   );

    if(WGLR_OK != i4_ret){
       return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                   WGL_IMG_ST_NO_SEGMENT,
                   &t_g_toast_msg_icon_arrow_up,
                   ph_img_tpl2
                   );

    if(WGLR_OK != i4_ret){
       return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                   WGL_IMG_ST_NO_SEGMENT,
                   &t_g_toast_msg_icon_arrow_down,
                   ph_img_tpl3
                   );

    if(WGLR_OK != i4_ret){
       return NAVR_FAIL;
    }

    return NAVR_OK;
}



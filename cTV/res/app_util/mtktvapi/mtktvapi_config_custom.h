/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: a_mtktvapi_config.h,v $
 * $Revision: #1 $
 * $Date: 2015/08/25 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _MTKTVAPI_CONFIG_CUSTOM_H_
#define _MTKTVAPI_CONFIG_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "app_util/mtktvapi/a_mtktvapi.h"
#include "app_util/mtktvapi/a_mtktvapi_config.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum
{
    MTKTVAPI_ITEM_INDEX_CH_LIST_TYPE,
    MTKTVAPI_ITEM_INDEX_AUDIO_LANG_ATTR,
    MTKTVAPI_ITEM_INDEX_AUDIO_AD_TYPE,
    MTKTVAPI_ITEM_INDEX_CAM_PROFILE_SCAN,
    MTKTVAPI_ITEM_INDEX_xvYCC,
    /* eu menu items index */
    MTKTVAPI_ITEM_INDEX_SATL_RE_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_SATL_ADD_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_SATL_UPDATE_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_SATL_MANUAL_TUNING_ITEM,
    MTKTVAPI_ITEM_INDEX_CH_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_UPDATE_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_ANALOG_MANUAL_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_SINGLE_RF_SCAN_ITEM,
    MTKTVAPI_ITEM_INDEX_FAV_NET_SEL_ITEM,
    MTKTVAPI_ITEM_INDEX_CH_SKIP_ITEM,
    MTKTVAPI_ITEM_INDEX_CH_SORT_ITEM,
    MTKTVAPI_ITEM_INDEX_CH_EDIT_ITEM,
    MTKTVAPI_ITEM_INDEX_ANA_CH_FINE_TUNE_ITEM,
    MTKTVAPI_ITEM_INDEX_CLEAN_CH_LST,
    /* us menu items index */
    MTKTVAPI_US_ITEM_INDEX_CH_SKIP_ITEM,
    /* sa menu items index */
    MTKTVAPI_SA_ITEM_INDEX_CH_SKIP_ITEM,
    MTKTVAPI_SA_ITEM_INDEX_CH_EDIT_ITEM,
    MTKTVAPI_ITEM_INDEX_TOTAL
}MTKTVAPI_ITEM_INDEX_T;

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 mtktvapi_config_get_minmaxvalue(INT16 i2_grp, const CHAR * s_cfg, INT32 * pi4_value);

extern INT32 mtktvapi_config_get_value(INT16 i2_grp, const CHAR * s_cfg, INT32 * pi4_value);

extern INT32 mtktvapi_config_set_value(INT16 i2_grp, const CHAR * s_cfg, INT32 i4_value, INT16 i2_update_flag);

extern INT32 mtktvapi_config_is_visible(INT16 i2_grp, const CHAR * s_cfg);

extern INT32 mtktvapi_config_is_enabled(INT16 i2_grp, const CHAR * s_cfg);

extern INT32 mtktvapi_config_reset_values(INT16 i2_type);

extern INT32 mtktvapi_config_get_str_value(const CHAR * s_cfg, CHAR * value, SIZE_T * pz_len);

extern INT32 mtktvapi_config_set_str_value(const CHAR * s_cfg, const CHAR *value);

extern INT32 mtktvapi_config_get_items_enabled(INT16 i2_grp, const CHAR * s_cfg,
												 CHAR * s_items, SIZE_T * pz_len, INT32 * pi4_enabled);

extern INT32 mtktvapi_config_set_android_world_info(INT16 i2_mode, INT16 i2_value);

extern BOOL mtktvapi_config_check_set_value(const CHAR * s_cfg, INT32 i4_value);

extern BOOL mtktvapi_config_check_set_str_value(const CHAR * s_cfg, const CHAR *value);

extern INT32 mtktvapi_config_custom_map_string_2_id(const CHAR * s_cfg, UINT16 * pui2_Id);

extern INT32 mtktvapi_config_custom_map_id_2_string(UINT16 ui2_Id, CHAR * * ps_cfg);
extern INT32 a_mtktvapi_config_inscape_reg_callback(config_update_nfy_fct pf_nfy, VOID * pv_tag);
extern INT16 a_mtktvapi_config_update_inscape_nfy(INT32 notifyId, VOID* pv_arg);

#endif /* _MTKTVAPI_CONFIG_CUSTOM_H_ */

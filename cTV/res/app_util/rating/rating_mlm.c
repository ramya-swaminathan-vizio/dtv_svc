/*-----------------------------------------------------------------------------
 * Copyright (c) 2005, CrystalMedia Technology, Inc.                           
 * All rights reserved.                                                        
 *                                                                             
 * Unauthorized use, practice, perform, copy, distribution, reproduction,      
 * or disclosure of this information in whole or in part is prohibited.        
 *-----------------------------------------------------------------------------
 * $RCSfile: mlmgen_renderer.c,v $
 * $Revision: 
 * $Date: 
 * $Author: 
 * $CCRevision: rating_mlm.c,v $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:                                                                
 *     This file is generated by mlmgen V1.46, which is provided by MediaTek, Inc. 
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files                                               
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_sys_name.h"
#include "c_cl.h"
#include "c_os.h"
#include "amb/a_amb.h"

#ifdef APP_MLMGEN_CUSTOM_LOGIC
#include "res/app_util/mlmgen/a_mlmgen.h"
#endif

/*-----------------------------------------------------------------------------
                    data declarations                                          
-----------------------------------------------------------------------------*/
typedef struct _MLM_RATING_TEXT_T
{
    UTF16_T     w2s_not_rated[15];
} MLM_RATING_TEXT_T;

static UINT16 ui1_g_mlm_cur_lang_idx = 0xFFFF;
static MLM_RATING_TEXT_T t_g_mlm_text;

static UINT8   at_g_compressed_eng[] =
{
    0xf3, 0x63, 0xc8, 0x67, 0x28, 0x61, 0x50, 0x60, 0x08, 0x62,
    0x48, 0x04, 0xd2, 0xa9, 0x0c, 0x29, 0x0c, 0xc8, 0x00, 0x00, 0x00
};

static UINT8   at_g_compressed_spa[] =
{
    0x0b, 0x66, 0xc8, 0x64, 0xc8, 0x63, 0x50, 0x60, 0x48, 0x66,
    0xc8, 0x61, 0x48, 0x64, 0x28, 0x06, 0xf2, 0xd2, 0x80, 0x38,
    0x19, 0xc8, 0x2e, 0x62, 0x60, 0x60, 0x00, 0x00, 0x00
};

static UINT8   at_g_compressed_fre[] =
{
    0xf3, 0x63, 0xc8, 0x67, 0xc8, 0x63, 0x50, 0x60, 0x78, 0xc9,
    0x50, 0xc6, 0x90, 0xc8, 0x90, 0xc3, 0x50, 0x0a, 0x64, 0x21,
    0x00, 0x00, 0x00
};

static UTF16_T*    aw2s_g_txt_tbl[1] =
{
    t_g_mlm_text.w2s_not_rated
};

static UINT8* apui1_g_data_tbl[3] =
{
    at_g_compressed_eng,
    at_g_compressed_spa,
    at_g_compressed_fre
};

static SIZE_T az_g_data_len_tbl[3] =
{
    sizeof(at_g_compressed_eng),
    sizeof(at_g_compressed_spa),
    sizeof(at_g_compressed_fre)
};

static HANDLE_T h_g_lock = NULL_HANDLE;

/*-----------------------------------------------------------------------------
                    function declarations                                          
-----------------------------------------------------------------------------*/
static VOID _mlm_rating_decompress(UINT16 ui2_lang)
{
    INT32       i4_ret;
    HANDLE_T    h_zip_eng = NULL_HANDLE;
    SIZE_T      z_dest_len = sizeof(MLM_RATING_TEXT_T);

    if(ui2_lang >= 3)    /* MLM_RATING_LANG_NUM = 3 */
    {
        return;
    }

    do
    {
        i4_ret = c_cl_open_eng(SN_CL_ZIP, NULL, NULL, &h_zip_eng);
        if(i4_ret < 0)
        {
            break;
        }

        i4_ret = c_cl_decompress(h_zip_eng,
                                 apui1_g_data_tbl[ui2_lang],
                                 az_g_data_len_tbl[ui2_lang],
                                 0,
                                 CL_NULL_PARAM_TYPE,
                                 NULL,
                                 &t_g_mlm_text,
                                 &z_dest_len,
                                 NULL);
        if(i4_ret < 0)
        {
            break;
        }

    }while(0);

    if(i4_ret < 0)
    {
        c_memset(&t_g_mlm_text, 0, sizeof(MLM_RATING_TEXT_T));
    }

    if(h_zip_eng != (HANDLE_T)NULL)
    {
        c_cl_close(h_zip_eng);
    }
}

static VOID _mlm_rating_lock(VOID)
{

    /* Acquire lock */
    if(h_g_lock == NULL_HANDLE)
    {
        a_amb_lock();
        if(h_g_lock == NULL_HANDLE)
        {
            c_sema_create(&h_g_lock,
                          X_SEMA_TYPE_MUTEX,
                          X_SEMA_STATE_UNLOCK);
        }
        a_amb_unlock();
    }

    /* Lock */
    if(h_g_lock)
    {
        c_sema_lock(h_g_lock, X_SEMA_OPTION_WAIT);
    }
}

static VOID _mlm_rating_unlock(VOID)
{
    /* Unlock */
    if(h_g_lock)
    {
        c_sema_unlock(h_g_lock);
    }
}

UTF16_T* mlm_rating_get_text(UINT16 ui2_lang, UINT16 ui2_key)
{
    if(ui2_lang != ui1_g_mlm_cur_lang_idx)
    {
        _mlm_rating_lock();
        if(ui2_lang != ui1_g_mlm_cur_lang_idx)
        {
            _mlm_rating_decompress(ui2_lang);
            ui1_g_mlm_cur_lang_idx = ui2_lang;
        }
        _mlm_rating_unlock();
    }

#ifdef APP_MLM_CENTER_SUPPORT /* ExcelGen mechanism. */ 
    if (   (aw2s_g_txt_tbl[ui2_key][0] != 0 && aw2s_g_txt_tbl[ui2_key][0] == (UTF16_T)L'^')  &&
           (aw2s_g_txt_tbl[ui2_key][1] != 0 && aw2s_g_txt_tbl[ui2_key][1] == (UTF16_T)L'^')  &&
           (aw2s_g_txt_tbl[ui2_key][2] != 0 && aw2s_g_txt_tbl[ui2_key][2] == (UTF16_T)L'I')  &&
           (aw2s_g_txt_tbl[ui2_key][3] != 0 && aw2s_g_txt_tbl[ui2_key][3] == (UTF16_T)L'D') )
    {
        extern UTF16_T* mlm_center_get_text_by_hint (CHAR* ps_module_name, UINT16 ui2_lang, UTF16_T* pw2s_hint);

        return mlm_center_get_text_by_hint ("RATING", ui2_lang, aw2s_g_txt_tbl[ui2_key]);
    }
#endif

    return aw2s_g_txt_tbl[ui2_key];
}

UINT16 mlm_rating_s639_to_langidx(ISO_639_LANG_T s639_lang)
{
    UINT16 ui2_lang_idx = 0; 

    if(s639_lang == NULL)
    {
        ui2_lang_idx = 0;
        return ui2_lang_idx;
    }
    if(c_strncmp(s639_lang,"eng",3) ==0)
    {
        ui2_lang_idx = 0; /*MLM_RATING_LANG_ENG*/
    }
    else if(c_strncmp(s639_lang,"spa",3) ==0)
    {
        ui2_lang_idx = 1; /*MLM_RATING_LANG_SPA*/
    }
    else if(c_strncmp(s639_lang,"fre",3) ==0)
    {
        ui2_lang_idx = 2; /*MLM_RATING_LANG_FRE*/
    }
    else
    {
        ui2_lang_idx = 0; /*MLM_RATING_LANG_ENG*/
    }
#ifdef MLMGEN_CUSTOM_S639_TO_LANGIDX_REASSIGN
    return MLMGEN_CUSTOM_S639_TO_LANGIDX_REASSIGN("RATING", s639_lang, ui2_lang_idx);
#else
    return ui2_lang_idx;
#endif
}
VOID mlm_rating_langidx_to_s639(UINT16 ui2_lang,ISO_639_LANG_T s639_lang)
{
    if(s639_lang == NULL)
    {
        return;
    }
    switch(ui2_lang)
    {
        case 0: /*MLM_RATING_LANG_ENG*/
            c_strncpy(s639_lang,"eng",3);
            s639_lang[3] ='\0';
            break;
        case 1: /*MLM_RATING_LANG_SPA*/
            c_strncpy(s639_lang,"spa",3);
            s639_lang[3] ='\0';
            break;
        case 2: /*MLM_RATING_LANG_FRE*/
            c_strncpy(s639_lang,"fre",3);
            s639_lang[3] ='\0';
            break;
        default:
            c_strncpy(s639_lang,"eng",3);
            s639_lang[3] ='\0';
            break;
    }
}

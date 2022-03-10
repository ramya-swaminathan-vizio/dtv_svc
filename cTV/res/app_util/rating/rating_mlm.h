/*-----------------------------------------------------------------------------
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 * 
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: mlmgen_renderer.c,v $
 * $Revision: #21 $
 * $Date:   
 * $Author: 
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *     This file is generated by mlmgen V1.46, which is provided by MediaTek, Inc. 
 *---------------------------------------------------------------------------*/
#ifndef _rating_mlm_h_
#define _rating_mlm_h_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define MLM_RATING_TEXT(lang, key) mlm_rating_get_text(lang, key)

#define MLM_RATING_NUM_LANG 3
#define MLM_RATING_NUM_KEY 1

#define MLM_RATING_KEY_NOT_RATED 0

#define MLM_RATING_LANG_ENG 0
#define MLM_RATING_LANG_SPA 1
#define MLM_RATING_LANG_FRE 2

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
-----------------------------------------------------------------------------*/
extern UTF16_T* mlm_rating_get_text(UINT16 ui2_lang, UINT16 ui2_key);
extern UINT16 mlm_rating_s639_to_langidx(ISO_639_LANG_T s639_lang);
extern VOID mlm_rating_langidx_to_s639(UINT16 ui2_lang,ISO_639_LANG_T s639_lang);

#endif /* _rating_mlm_h_ */

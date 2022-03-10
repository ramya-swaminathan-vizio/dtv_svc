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
#ifndef _revolt_warnings_mlm_h_
#define _revolt_warnings_mlm_h_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define MLM_WARNINGS_TEXT(lang, key) mlm_warnings_get_text(lang, key)

#define MLM_WARNINGS_NUM_LANG 3
#define MLM_WARNINGS_NUM_KEY 74

#define MLM_WARNINGS_KEY_EMPTY 0
#define MLM_WARNINGS_KEY_WARNING_1 1
#define MLM_WARNINGS_KEY_WARNING_2 2
#define MLM_WARNINGS_KEY_WARNING_3 3
#define MLM_WARNINGS_KEY_WARNING_4 4
#define MLM_WARNINGS_KEY_WARNING_5 5
#define MLM_WARNINGS_KEY_WARNING_6 6
#define MLM_WARNINGS_KEY_WARNING_7 7
#define MLM_WARNINGS_KEY_WARNING_8 8
#define MLM_WARNINGS_KEY_WARNING_9 9
#define MLM_WARNINGS_KEY_WARNING_10 10
#define MLM_WARNINGS_KEY_WARNING_11 11
#define MLM_WARNINGS_KEY_WARNING_12 12
#define MLM_WARNINGS_KEY_WARNING_13 13
#define MLM_WARNINGS_KEY_WARNING_14 14
#define MLM_WARNINGS_KEY_WARNING_15 15
#define MLM_WARNINGS_KEY_WARNING_16 16
#define MLM_WARNINGS_KEY_WARNING_17 17
#define MLM_WARNINGS_KEY_WARNING_18 18
#define MLM_WARNINGS_KEY_WARNING_19 19
#define MLM_WARNINGS_KEY_WARNING_20 20
#define MLM_WARNINGS_KEY_WARNING_21 21
#define MLM_WARNINGS_KEY_WARNING_22 22
#define MLM_WARNINGS_KEY_WARNING_23 23
#define MLM_WARNINGS_KEY_WARNING_24 24
#define MLM_WARNINGS_KEY_WARNING_25 25
#define MLM_WARNINGS_KEY_WARNING_26 26
#define MLM_WARNINGS_KEY_WARNING_27 27
#define MLM_WARNINGS_KEY_WARNING_28 28
#define MLM_WARNINGS_KEY_WARNING_29 29
#define MLM_WARNINGS_KEY_WARNING_30 30
#define MLM_WARNINGS_KEY_WARNING_31 31
#define MLM_WARNINGS_KEY_WARNING_32 32
#define MLM_WARNINGS_KEY_WARNING_33 33
#define MLM_WARNINGS_KEY_WARNING_34 34
#define MLM_WARNINGS_KEY_WARNING_35 35
#define MLM_WARNINGS_KEY_WARNING_36 36
#define MLM_WARNINGS_KEY_WARNING_37 37
#define MLM_WARNINGS_KEY_WARNING_38 38
#define MLM_WARNINGS_KEY_WARNING_39 39
#define MLM_WARNINGS_KEY_WARNING_40 40
#define MLM_WARNINGS_KEY_WARNING_41 41
#define MLM_WARNINGS_KEY_WARNING_42 42
#define MLM_WARNINGS_KEY_WARNING_43 43
#define MLM_WARNINGS_KEY_WARNING_44 44
#define MLM_WARNINGS_KEY_WARNING_45 45
#define MLM_WARNINGS_KEY_WARNING_46 46
#define MLM_WARNINGS_KEY_WARNING_47 47
#define MLM_WARNINGS_KEY_WARNING_48 48
#define MLM_WARNINGS_KEY_WARNING_49 49
#define MLM_WARNINGS_KEY_WARNING_50 50
#define MLM_WARNINGS_KEY_WARNING_51 51
#define MLM_WARNINGS_KEY_WARNING_52 52
#define MLM_WARNINGS_KEY_WARNING_53 53
#define MLM_WARNINGS_KEY_WARNING_54 54
#define MLM_WARNINGS_KEY_WARNING_55 55
#define MLM_WARNINGS_KEY_WARNING_56 56
#define MLM_WARNINGS_KEY_WARNING_57 57
#define MLM_WARNINGS_KEY_WARNING_58 58
#define MLM_WARNINGS_KEY_WARNING_59 59
#define MLM_WARNINGS_KEY_WARNING_60 60
#define MLM_WARNINGS_KEY_WARNING_61 61
#define MLM_WARNINGS_KEY_WARNING_62 62
#define MLM_WARNINGS_KEY_WARNING_63 63
#define MLM_WARNINGS_KEY_WARNING_64 64
#define MLM_WARNINGS_KEY_WARNING_65 65
#define MLM_WARNINGS_KEY_WARNING_66 66
#define MLM_WARNINGS_KEY_WARNING_67 67
#define MLM_WARNINGS_KEY_WARNING_68 68
#define MLM_WARNINGS_KEY_WARNING_69 69
#define MLM_WARNINGS_KEY_WARNING_70 70
#define MLM_WARNINGS_KEY_WARNING_71 71
#define MLM_WARNINGS_KEY_WARNING_72 72
#define MLM_WARNINGS_KEY_WARNING_73 73

#define MLM_WARNINGS_LANG_ENG 0
#define MLM_WARNINGS_LANG_FRE 1
#define MLM_WARNINGS_LANG_SPA 2

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
-----------------------------------------------------------------------------*/
extern UTF16_T* mlm_warnings_get_text(UINT16 ui2_lang, UINT16 ui2_key);
extern UINT16 mlm_warnings_s639_to_langidx(ISO_639_LANG_T s639_lang);
extern VOID mlm_warnings_langidx_to_s639(UINT16 ui2_lang,ISO_639_LANG_T s639_lang);

#endif /* _revolt_warnings_mlm_h_ */

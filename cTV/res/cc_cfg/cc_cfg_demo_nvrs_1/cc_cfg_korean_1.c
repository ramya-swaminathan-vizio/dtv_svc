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
 * $RCSfile: cc_cfg_demo_nvrs_1.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/6 $
 * $SWAuthor: TC Yin $
 * $MD5HEX: 9fb271266c0dc8386bcc94c88639d87a $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_wgl_cc.h"
#include "c_fe.h"
#include "fonts/fontdata.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    global data
 ----------------------------------------------------------------------------*/
 #ifdef SYS_KOREAN_CC_SUPPORT
 
 /* SN_FONT_KOREAN_CC_1: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_1[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 0 }, 
         { 0, 0, 0 }, 
         { 1, 1, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 0 }, 
         { 0, 0, 0 }, 
         { 1, 2, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 0, 0, 0 }, 
         { 0, 0, 0 }, 
         { 1, 1, 0 }
     },
         
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    
 
 /* SN_FONT_KOREAN_CC_2: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_2[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 1, 1, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 1, 2, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 1, 0, 0 }, 
         { 0, 0, 0 }, 
         { 1, 1, 0 }
     },
 
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    
 
 /* SN_FONT_KOREAN_CC_3: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_3[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 18 },
         { 0, 0, 20 },
         { 1, 1, 24 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 34 },
         { 0, 0, 36 },
         { 1, 2, 42 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 0, 0, 12 }, 
         { 0, 0, 13 }, 
         { 1, 1, 16 }
     },
         
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    
 
 /* SN_FONT_KOREAN_CC_4: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_4[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 0 },
         { 1, 3, 0 },
         { 2, 6, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 0 },
         { 0, 5, 0 },
         { 2, 9, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 0, 0, 0 }, 
         { 1, 2, 0 }, 
         { 1, 4, 0 }
     },
         
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    
 
 /* SN_FONT_KOREAN_CC_5: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_5[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 0, 1, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 0, 2, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 0, 1, 0 }, 
         { 0, 0, 0 }, 
         { 0, 1, 0 }
     },
         
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    
 
 /* SN_FONT_KOREAN_CC_6: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_6[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 0, 0, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 1, 0, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 0, 0, 0 }, 
         { 0, 0, 0 }, 
         { 1, 0, 0 }
     },
         
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    
 
 /* SN_FONT_KOREAN_CC_7: dotum */
 static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_korean_cc_7[] = 
 {
     {
         WGL_CC_MAKE_FONT_TBL_ID(1280, 720),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 1, 1, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(1920, 1080),
         { 0, 0, 0 },
         { 0, 0, 0 },
         { 1, 2, 0 }
     },
     {
         WGL_CC_MAKE_FONT_TBL_ID(720, 480),
         { 0, 0, 0 }, 
         { 0, 0, 0 }, 
         { 1, 1, 0 }
     },
         
     END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
 };    

#endif


 
WGL_CC_FONT_REG_INFO_T  at_g_cc_font_reg_table[] = 
{
#ifdef SYS_KOREAN_CC_SUPPORT    
    { SN_FONT_KOREAN_CC_1,      at_res_param_korean_cc_1},
    { SN_FONT_KOREAN_CC_2,      at_res_param_korean_cc_2},
    { SN_FONT_KOREAN_CC_3,      at_res_param_korean_cc_3},
    { SN_FONT_KOREAN_CC_4,      at_res_param_korean_cc_4},
    { SN_FONT_KOREAN_CC_5,      at_res_param_korean_cc_5},
    { SN_FONT_KOREAN_CC_6,      at_res_param_korean_cc_6},
    { SN_FONT_KOREAN_CC_7,      at_res_param_korean_cc_7},
#endif

    END_OF_ARRAY_FONT_REG_INFO_T
    
};

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
BOOL sys_init_cc_font(VOID)
{
    BOOL   b_success = FALSE;
#ifdef SYS_KOREAN_CC_SUPPORT    
    UINT32 ui4_font_size_koreac_cc_1  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_2  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_3  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_4  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_5  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_6  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_7  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));
    UINT32 ui4_font_size_koreac_cc_analog  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kor [0]));

    /* font sizes for: 1280 x 720 */
    #if 0
    if(
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_1,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_1,  31, 32, 34) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_2,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_2,  33, 34, 36) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_3,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_3,  31, 32, 34) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_4,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_4,  28, 31, 34) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_5,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_5,  31, 32, 33) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_6,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_6,  30, 31, 32) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_7,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_7,  35, 36, 38) == FER_OK)
       )
    {
        b_success = TRUE;
    }
    #endif 
    if(
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_1,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_1,  20, 32, 34) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_2,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_2,  20, 34, 36) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_3,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_3,  20, 32, 34) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_4,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_4,  20, 31, 34) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_5,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_5,  20, 32, 33) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_6,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_6,  20, 31, 32) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_7,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_7,  20, 36, 38) == FER_OK)  &&
        //(c_fe_add_mem_font(SN_FONT_KOREAN_CC_ANALOG,     &(font_file_kor [4]),      ui4_font_size_koreac_cc_analog,  18, 21, 23) == FER_OK)
        (c_fe_add_mem_font(SN_FONT_KOREAN_CC_ANALOG,&(font_file_kor [4]), ui4_font_size_koreac_cc_analog, 20, 32, 34) == FER_OK)
    )
    {
        b_success = TRUE;
    }
#endif    
    return b_success;
}    


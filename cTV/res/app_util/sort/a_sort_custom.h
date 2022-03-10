#ifndef __A_SORT_CUSTOM_H__
#define __A_SORT_CUSTOM_H__
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define NUM_S_ARRAY   32
typedef struct _MERGE_SORT_T
{
    CHAR       s_array[NUM_S_ARRAY]; /*store the merged array*/
    INT16      i2_src_idx1; /*record the index of str from array_src1*/
                                 /*if=-1,the str doesn't appear in array_src1*/
    INT16      i2_src_idx2; /*record the index of str from array_src2*/
                                 /*if=-1,the str doesn't appear in array_src2*/
}MERGE_SORT_T; 
/*-----------------------------------------------------------------------------
                    function declarations
  ----------------------------------------------------------------------------*/
extern VOID a_sort_custom_str_merge_sort(
    CHAR** pps_src_array1,
    CHAR** pps_src_array2,
    UINT8  ui1_src_num1,
    UINT8  ui1_src_num2,
    MERGE_SORT_T* t_des_array,
    UINT16* ui2_des_num);
extern INT32 a_sort_custom_str_sort(CHAR** array,UINT8 elem_num);    
#endif

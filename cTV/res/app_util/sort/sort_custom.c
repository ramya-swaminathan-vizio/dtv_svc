/*-----------------------------------------------------------------------------
  include files
  --------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_dbg.h"
#include "a_sort_custom.h"  
#include "c_sort_search.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    static function declarations
  ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    static function implementation
 ----------------------------------------------------------------------------*/
 static INT32 _sort_custom_cmp_fct(const VOID *pv_a,const VOID *pv_b, VOID *pv_c)
 {
     return(c_strcasecmp(*(CHAR **)pv_a,*(CHAR **)pv_b));
 }
 /*******************************************************************************
 * Name
 *          a_sort_custom_str_sort
 *
 * Description
 *          ascending sort the array of strings use quick sort.
 *
 * Input arguments
 *          array          The array of strings.
 *          elem_num       The elem num of array
 *                 
 * Output arguments
 *         
 *          
 * Returns
 *          
 ******************************************************************************/ 
INT32 a_sort_custom_str_sort(CHAR** array,UINT8 elem_num)
{
    return c_qsort(array,elem_num,sizeof(CHAR *),_sort_custom_cmp_fct,NULL);
}
/*******************************************************************************
 * Name
 *          a_sort_custom_str_merge_sort
 *
 * Description
 *          merge two ordered array of trings into a ordered array of strings,
 *          and remove replicated string. 
 *
 * Input arguments
 *          pps_src_array1         The src array1 of strings.
 *          pps_src_array2         The src array2 of strings.
 *          ui1_src_num1           The elem num of pps_src_array1.
 *          ui1_src_num2           The elem num of src_array2.
 *
 * Output arguments
 *          t_des_array     The pointer to merged array of strings.
 *          ui2_des_num       The pointer to the size of merged array of strings.
 *
 * Returns
 *          
 ******************************************************************************/ 
VOID a_sort_custom_str_merge_sort(
    CHAR**          pps_src_array1,
    CHAR**          pps_src_array2,
    UINT8           ui1_src_num1,
    UINT8           ui1_src_num2,
    MERGE_SORT_T*   t_des_array,
    UINT16*         ui2_des_num)
{
    UINT8   ui1_src_idx1 = 0;
    UINT8   ui1_src_idx2 = 0;
    UINT16  ui2_des_idx = 0;
    INT32   i4_ret;
    if((ui1_src_num1 != 0xFF) && (ui1_src_num2 != 0xFF))
    {
        while((ui1_src_idx1<ui1_src_num1)&&(ui1_src_idx2<ui1_src_num2))
        {
            i4_ret=c_strcasecmp(pps_src_array1[ui1_src_idx1],pps_src_array2[ui1_src_idx2]);
            if(i4_ret<0)  /*merge string is only from pps_src_array*/
            {
                c_strncpy(
                    t_des_array[ui2_des_idx].s_array,
                    pps_src_array1[ui1_src_idx1],
                    c_strlen(pps_src_array1[ui1_src_idx1]));
                t_des_array[ui2_des_idx].i2_src_idx1 = ui1_src_idx1;
                t_des_array[ui2_des_idx].i2_src_idx2 = -1;
                ui1_src_idx1++;
                ui2_des_idx++;
            }
            else if(i4_ret==0)  /*merge string is from src_array and des_array*/
            {
                c_strncpy(
                    t_des_array[ui2_des_idx].s_array,
                    pps_src_array1[ui1_src_idx1],
                    c_strlen(pps_src_array1[ui1_src_idx1]));
                t_des_array[ui2_des_idx].i2_src_idx1 = ui1_src_idx1;
                t_des_array[ui2_des_idx].i2_src_idx2 = ui1_src_idx2;
                ui1_src_idx1++;
                ui1_src_idx2++;
                ui2_des_idx++;  
            }
            else    /*merge string is only from des_array*/
            {
                c_strncpy(
                    t_des_array[ui2_des_idx].s_array,
                    pps_src_array2[ui1_src_idx2],
                    c_strlen(pps_src_array2[ui1_src_idx2]));
                t_des_array[ui2_des_idx].i2_src_idx1 = -1;
                t_des_array[ui2_des_idx].i2_src_idx2 = ui1_src_idx2;
                ui1_src_idx2++;
                ui2_des_idx++;
            }   
        }
        while(ui1_src_idx1<ui1_src_num1)
        {
            c_strncpy(
                t_des_array[ui2_des_idx].s_array,
                pps_src_array1[ui1_src_idx1],
                c_strlen(pps_src_array1[ui1_src_idx1]));
            t_des_array[ui2_des_idx].i2_src_idx1 = ui1_src_idx1;
            t_des_array[ui2_des_idx].i2_src_idx2 = -1;
            ui1_src_idx1++;
            ui2_des_idx++;
        }
        while(ui1_src_idx2<ui1_src_num2)
        {
            c_strncpy(
                t_des_array[ui2_des_idx].s_array,
                pps_src_array2[ui1_src_idx2],
                c_strlen(pps_src_array2[ui1_src_idx2]));
            t_des_array[ui2_des_idx].i2_src_idx1 = -1;
            t_des_array[ui2_des_idx].i2_src_idx2 = ui1_src_idx2;
            ui1_src_idx2++;
            ui2_des_idx++;
        }
        *ui2_des_num = ui2_des_idx;
    }
    else if (ui1_src_num1 == 0xFF)
    {
        while(ui1_src_idx2<ui1_src_num2)
        {
            c_strncpy(
                t_des_array[ui2_des_idx].s_array,
                pps_src_array2[ui1_src_idx2],
                c_strlen(pps_src_array2[ui1_src_idx2]));
            t_des_array[ui2_des_idx].i2_src_idx1 = -1;
            t_des_array[ui2_des_idx].i2_src_idx2 = ui1_src_idx2;
            ui1_src_idx2++;
            ui2_des_idx++;
        }
        *ui2_des_num = ui2_des_idx;
    }
    else if (ui1_src_num2 == 0xFF)
    {
        while(ui1_src_idx1<ui1_src_num1)
        {
            c_strncpy(
                t_des_array[ui2_des_idx].s_array,
                pps_src_array1[ui1_src_idx1],
                c_strlen(pps_src_array1[ui1_src_idx1]));
            t_des_array[ui2_des_idx].i2_src_idx1 = ui1_src_idx1;
            t_des_array[ui2_des_idx].i2_src_idx2 = -1;
            ui1_src_idx1++;
            ui2_des_idx++;
        }
        *ui2_des_num = ui2_des_idx;
    }
}

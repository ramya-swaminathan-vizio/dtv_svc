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
 * $RCSfile: rmv_dev.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ---------------------------------------------------------------------------*/
#include "u_lnk_list.h"
#include "wfd_dev_list.h"
#include "wfd_p2p_conn.h"
#include "c_fm.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define _WFD_DEVLICE_LST_PATH   "/3rd_rw/wfd_list.txt"

typedef struct _NAV_WFD_DEVICE_INFO_CTRL_T
{   
    NAV_WFD_DEVICE_INFO_T                        t_device_info;
    DLIST_ENTRY_T(_NAV_WFD_DEVICE_INFO_CTRL_T)   t_link;
}NAV_WFD_DEVICE_INFO_CTRL_T;

typedef DLIST_T(_NAV_WFD_DEVICE_INFO_CTRL_T) NAV_WFD_DEVICE_INFO_CTRL_LIST_T;

typedef struct _NAV_WFD_CUSTOM_T
{
    BOOL                                         b_inited ;
    UINT8                                        ui1_count;
    UINT8                                        ui1_acc_count;                 /*accept devuce count*/
    UINT8                                        ui1_dec_count;                 /*decline device count */
    UINT16                                       ui2_index;                     /*current connect device index */
    CHAR                                         s_mac[20];                     /* currrent connect device mac */
    CHAR                                         s_name[20];                    /* currrent connect device name */
    NAV_WFD_DEVICE_INFO_CTRL_LIST_T              t_wfd_device_list;
}NAV_WFD_CUSTOM_T;

static NAV_WFD_CUSTOM_T t_g_wfd_info;

/*----------------------------------------------------------------------------- 
                    private function implementations 
-----------------------------------------------------------------------------*/ 

static VOID _wfd_dev_3rd_mounted_nfy_handler(
    VOID* pv_data, 
    SIZE_T z_data_len)
{
    a_wfd_device_info_load_list();
}


static INT32 _wfd_dev_3rd_mounted_nfy(
    UINT32                 ui4_tag,
    FS_PARTITION_T         e_partition
    )
{
    if (FS_PARTITION_ALL == e_partition)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
         
        a_agent_async_invoke(_wfd_dev_3rd_mounted_nfy_handler,NULL,0);
    }
    
    return WFDR_OK;
}



/*-----------------------------------------------------------------------------
*                public methods implementations
*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_is_device_register
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_wfd_device_info_is_device_register(CHAR * ps_mac_address, UINT32  ui4_mac_len)
{

    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_device_info = NULL;
    UINT32                      ui4_len        = 0;
    
    if(ps_mac_address == NULL || ui4_mac_len == 0)
    {
        return FALSE;
    }
    ui4_mac_len > DEVICE_INFO_MAX_MAC_LEN? (ui4_len=DEVICE_INFO_MAX_MAC_LEN):(ui4_len = ui4_mac_len);

    DLIST_FOR_EACH (pt_device_info, &t_g_wfd_info.t_wfd_device_list, t_link)   
    {
        if(c_strncmp(pt_device_info->t_device_info.s_device_mac, ps_mac_address, ui4_len) == 0)
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_load_list
 * Description:
 *              load device list form the file sys
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_load_list(VOID)
{

    HANDLE_T                h_file              = NULL_HANDLE;
    INT32                   i4_ret              = 0;
    UINT64                  ui8_cur_pos         = 0 ;
    UINT32                  ui4_read            = 0;    
    NAV_WFD_DEVICE_INFO_T   t_device_info; 
    BOOL                    b_eof               = FALSE; 

    if(!t_g_wfd_info.b_inited)
    {
        return WFDR_OK;
    }
    /*delete all first  then load */
    i4_ret = a_wfd_device_info_delete_all();
    if(i4_ret != WFDR_OK)
    {
        return i4_ret;
    }

    i4_ret = c_fm_open(FM_ROOT_HANDLE, _WFD_DEVLICE_LST_PATH, FM_READ_ONLY|FM_OPEN_CREATE, 0777, FALSE, &h_file);
    if (FMR_OK != i4_ret || h_file == NULL_HANDLE) 
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return WFDR_FILE_HANDLE_FAILURE;
    }  
    
    i4_ret = c_fm_lseek(h_file, 0, FM_SEEK_END, &ui8_cur_pos);
    if (FMR_OK != i4_ret) 
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));      
        c_fm_close(h_file);
        return WFDR_FILE_HANDLE_FAILURE;
    }  
    if(ui8_cur_pos == 0 || ui8_cur_pos == 1)
    {        
        c_fm_close(h_file);
        return WFDR_EMPTY_FILE;
    }
    i4_ret = c_fm_lseek(h_file, 0, FM_SEEK_BGN, &ui8_cur_pos);
    if (FMR_OK != i4_ret) 
    {
        c_fm_close(h_file);
        return WFDR_FILE_HANDLE_FAILURE;        
    }
    i4_ret = c_fm_feof(h_file,&b_eof);
    if(FMR_OK != i4_ret)
    {
        c_fm_close(h_file);
        return WFDR_FILE_HANDLE_FAILURE;
    }
    while(!b_eof)
    {
 
        c_memset(&t_device_info, 0, sizeof(t_device_info));
        i4_ret = c_fm_read(h_file, &t_device_info, sizeof(t_device_info), &ui4_read);
        if (FMR_OK != i4_ret) 
        {
            c_fm_close(h_file);
            return WFDR_FILE_HANDLE_FAILURE;        
        }
        i4_ret = a_wfd_device_info_add_device(&t_device_info);
        if(WFDR_OK != i4_ret)
        {
            c_fm_close(h_file);
            return i4_ret;
        }
        i4_ret = c_fm_feof(h_file,&b_eof);
        if(FMR_OK != i4_ret)
        {
            c_fm_close(h_file);
            return WFDR_FILE_HANDLE_FAILURE;
        }      
    };
        
    c_fm_close(h_file);

    return WFDR_OK;
        
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_save_list
 * Description:
 *      save the device to the file list 
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_save_list(VOID)
{
    HANDLE_T                h_file              = NULL_HANDLE;
    INT32                   i4_ret              = 0;
    UINT32                  ui4_write           = 0;
    NAV_WFD_DEVICE_INFO_CTRL_T         *pt_list = NULL;

    i4_ret = c_fm_open(FM_ROOT_HANDLE, _WFD_DEVLICE_LST_PATH, FM_WRITE_ONLY|FM_OPEN_CREATE| FM_OPEN_TRUNC, 0777, FALSE, &h_file);
    if (FMR_OK != i4_ret || h_file == NULL_HANDLE) 
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return WFDR_FILE_HANDLE_FAILURE;
    }  
    if(t_g_wfd_info.ui1_count == 0)
    {
        i4_ret = c_fm_write(h_file, (VOID *)"0", 1, &ui4_write) ;
        if(i4_ret != FMR_OK)
        {
            c_fm_close(h_file);
            return  WFDR_FILE_HANDLE_FAILURE;
        }        
    }else
    {
        DLIST_FOR_EACH(pt_list, &t_g_wfd_info.t_wfd_device_list, t_link)
        {
            i4_ret = c_fm_write(h_file, (VOID*)&pt_list->t_device_info, sizeof(NAV_WFD_DEVICE_INFO_T), &ui4_write);
            if(i4_ret != FMR_OK)
            {
                c_fm_close(h_file);
                return  WFDR_FILE_HANDLE_FAILURE;
            }
        }
    }

    c_fm_close(h_file); 
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_show_list
 * Description:
 *      show the device info from the file list 
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_show_list(VOID)
{
    NAV_WFD_DEVICE_INFO_CTRL_T         *pt_list = NULL;

    if(t_g_wfd_info.ui1_count == 0)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));     
    }
    else
    {
        DLIST_FOR_EACH(pt_list, &t_g_wfd_info.t_wfd_device_list, t_link)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,ui1_index=%d,s_device_name=%s,s_device_mac=%s,s_device_type=%s\n",
                        __FILE__, __FUNCTION__, __LINE__, 
                        pt_list->t_device_info.ui1_index,
                        pt_list->t_device_info.s_device_name,
                        pt_list->t_device_info.s_device_mac,
                        pt_list->t_device_info.s_device_type));
        }
    }

    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_delete_all
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_delete_all(VOID)
{
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_device_info = NULL;
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_temp = NULL;
    
    for(pt_device_info = t_g_wfd_info.t_wfd_device_list.pt_head;
        pt_device_info != NULL; 
        )
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,s_device_name=%s\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    pt_device_info->t_device_info.s_device_name));
        
        pt_temp = pt_device_info;        

        pt_device_info = pt_device_info->t_link.pt_next;

        DLIST_REMOVE(pt_temp, &t_g_wfd_info.t_wfd_device_list, t_link);
        if(pt_temp != NULL)
        {   
            c_mem_free(pt_temp);          
            pt_temp = NULL;
        }
        
    }
    t_g_wfd_info.ui1_count = 0;
    t_g_wfd_info.ui1_acc_count = 0;
    t_g_wfd_info.ui1_dec_count = 0;
    
    return WFDR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_delete_by_mac
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_delete_by_mac(CHAR * ps_mac_address)
{
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_device_info = NULL;

    if(ps_mac_address == NULL)
    {
        return WFDR_INV_ARG;
    }
    for(pt_device_info = t_g_wfd_info.t_wfd_device_list.pt_head;
        pt_device_info != NULL; 
        )
    {
        if(c_strcmp(pt_device_info->t_device_info.s_device_mac, ps_mac_address) == 0)
        {         
            DBG_LOG_PRINT(("\n%s,%s,%d,s_device_name=%s\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        pt_device_info->t_device_info.s_device_name));            
            DLIST_REMOVE(pt_device_info, &t_g_wfd_info.t_wfd_device_list, t_link);
            if(pt_device_info != NULL)
            {   
                c_mem_free(pt_device_info);          
                pt_device_info = NULL;
            }            
            t_g_wfd_info.ui1_count--;
            break;
        }         
        pt_device_info = pt_device_info->t_link.pt_next;
    }    
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_delete_by_index
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_delete_by_index(UINT8 ui1_index)
{
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_device_info = NULL;
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_temp = NULL;

    for(pt_device_info = t_g_wfd_info.t_wfd_device_list.pt_head;
      pt_device_info != NULL; 
      )
    {    
        pt_temp = pt_device_info; 
        pt_device_info = pt_device_info->t_link.pt_next;          
        if(pt_temp->t_device_info.ui1_index == ui1_index)
        {         
            DBG_LOG_PRINT(("\n%s,%s,%d,s_device_name=%s\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        pt_temp->t_device_info.s_device_name));        
            DLIST_REMOVE(pt_temp, &t_g_wfd_info.t_wfd_device_list, t_link);
            if(pt_temp != NULL)
            {   
              c_mem_free(pt_temp);          
              pt_temp = NULL;
            }          
            t_g_wfd_info.ui1_count--;
            break;
        }               
    }

    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_add_device
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_add_device(NAV_WFD_DEVICE_INFO_T * pt_device_info)
{
    NAV_WFD_DEVICE_INFO_CTRL_T   *pt_temp = NULL;

    pt_temp = (NAV_WFD_DEVICE_INFO_CTRL_T *)c_mem_alloc(sizeof(NAV_WFD_DEVICE_INFO_CTRL_T));
    if(pt_temp == NULL)
    {
        return WFDR_MEMORY_MALLOC_FAILURE;
    }
    c_memcpy(&pt_temp->t_device_info, pt_device_info, sizeof(NAV_WFD_DEVICE_INFO_T));
    pt_temp->t_device_info.ui1_index = t_g_wfd_info.ui1_count;
    t_g_wfd_info.ui1_count ++;
    if(pt_temp->t_device_info.e_permission == E_WFD_DEVICE_PERMISSION_ACCEPT)
    {
        t_g_wfd_info.ui1_acc_count ++;
    }else
    {
        t_g_wfd_info.ui1_dec_count ++;        
    }
    DLIST_INSERT_TAIL (pt_temp, &t_g_wfd_info.t_wfd_device_list, t_link) ;

    DBG_LOG_PRINT(("\n%s,%s,%d,s_device_name=%s\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_temp->t_device_info.s_device_name));
    
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_get_device_count
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_get_device_count(UINT8  * pui1_amount)
{

    if(pui1_amount == NULL)
    {
        return WFDR_INV_ARG;
    }  
    
   * pui1_amount =  t_g_wfd_info.ui1_count;
   
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_get_device_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_get_device_index(UINT8 * pui1_index,  CHAR * ps_mac_address)
{
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_device_info = NULL;
    
    if(ps_mac_address == NULL || pui1_index == NULL)
    {
        return WFDR_INV_ARG;
    }

    DLIST_FOR_EACH (pt_device_info, &t_g_wfd_info.t_wfd_device_list, t_link)   
    {
        if(c_strcmp(pt_device_info->t_device_info.s_device_mac, ps_mac_address) == 0)
        {
            * pui1_index = pt_device_info->t_device_info.ui1_index;
            break;
        }
    }
    
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_get_device_info_by_index
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_get_device_info_by_index(INT32  ui4_index,  NAV_WFD_DEVICE_INFO_T * pt_device_info)
{
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_list_info = NULL;

    if(pt_device_info == NULL || ui4_index > t_g_wfd_info.ui1_count)
    {
        return WFDR_INV_ARG;
    }
    DLIST_FOR_EACH (pt_list_info, &t_g_wfd_info.t_wfd_device_list, t_link)   
    {
      if(pt_list_info->t_device_info.ui1_index == ui4_index)
      { 
          DBG_LOG_PRINT(("\n%s,%s,%d,s_device_name=%s\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    pt_list_info->t_device_info.s_device_name));         
          c_memcpy(pt_device_info, &pt_list_info->t_device_info, sizeof(NAV_WFD_DEVICE_INFO_T));
          break;
      }               
    }
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_get_device_info_by_type
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_get_device_info_by_mac(CHAR * ps_mac_address, NAV_WFD_DEVICE_INFO_T * pt_device_info)
{

    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_list = NULL;
      
    if(ps_mac_address == NULL || pt_device_info == NULL)
    {
        return WFDR_INV_ARG;
    }

    DLIST_FOR_EACH (pt_list, &t_g_wfd_info.t_wfd_device_list, t_link)   
    {
        if(c_strcmp(pt_list->t_device_info.s_device_mac, ps_mac_address) == 0)
        {
            c_memcpy(pt_device_info, &pt_list->t_device_info, sizeof(NAV_WFD_DEVICE_INFO_T));
            break;
        }
    }
    
    return WFDR_OK;
    
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_set_device_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_set_device_info(UINT8  ui1_index, WFD_DEVICE_INFO_ID_T e_info_id, SIZE_T* pz_size, VOID* pv_param)
{
    NAV_WFD_DEVICE_INFO_CTRL_T *     pt_list_info = NULL;

    if(pv_param == NULL || *pz_size == 0)
    {
        return WFDR_INV_ARG;
    }
    
    DLIST_FOR_EACH (pt_list_info, &t_g_wfd_info.t_wfd_device_list, t_link)   
    {
        if(pt_list_info->t_device_info.ui1_index == ui1_index)
        {
            switch(e_info_id)
            {
            case GET_WFD_DEVICE_INFO_ID_NAME:
                {
                    CHAR * ps_name = (CHAR*)pv_param;
                    SIZE_T    z_len = 0;
                    if(*pz_size > DEVICE_INFO_MAX_NAME_LEN)
                    {
                        z_len = DEVICE_INFO_MAX_NAME_LEN;
                    }else
                    {
                        z_len = *pz_size;
                    }
                    c_memset(pt_list_info->t_device_info.s_device_name, 0, sizeof(pt_list_info->t_device_info.s_device_name));
                    c_memcpy(pt_list_info->t_device_info.s_device_name, ps_name, z_len);
                }
                break;
            case GET_WFD_DEVICE_INFO_ID_MAC:
                {
                    CHAR * ps_mac = (CHAR*)pv_param;
                    SIZE_T    z_len = 0;
                    if(*pz_size > DEVICE_INFO_MAX_NAME_LEN)
                    {
                        z_len = DEVICE_INFO_MAX_NAME_LEN;
                    }else
                    {
                        z_len = *pz_size;
                    }
                    
                    c_memset(pt_list_info->t_device_info.s_device_mac, 0, sizeof(pt_list_info->t_device_info.s_device_mac));
                    c_memcpy(pt_list_info->t_device_info.s_device_mac, ps_mac, z_len);                        
                }
                break;
            case GET_WFD_DEVICE_INFO_ID_TYPE:
                {
                    CHAR * ps_type = (CHAR*)pv_param;
                    SIZE_T    z_len = 0;
                    if(*pz_size > DEVICE_INFO_MAX_NAME_LEN)
                    {
                        z_len = DEVICE_INFO_MAX_NAME_LEN;
                    }else
                    {
                        z_len = *pz_size;
                    }
                    c_memset(pt_list_info->t_device_info.s_device_type, 0, sizeof(pt_list_info->t_device_info.s_device_type));
                    c_memcpy(pt_list_info->t_device_info.s_device_type, ps_type, z_len);                        
                }                
                break;                
            case GET_WFD_DEVICE_INFO_ID_PERMISSION:
                {
                    WFD_DEVICE_PERMISSION_T  e_permiss = (WFD_DEVICE_PERMISSION_T)pv_param;
                    pt_list_info->t_device_info.e_permission =  e_permiss;                        
                }                                
                break;
            default:
                break;
            }
        }
    }
    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_is_device_connected
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_wfd_device_info_is_device_connected(CHAR * ps_mac_address)
{
    if(ps_mac_address == NULL)
    {
        return FALSE;
    }
    
    INT32 i4_devnum   = 0;
    INT32 i           = 0;
    INT32 i4_ret      = 0;
    WFD_DEVICE_INFO_T  t_dev_info;
    
    i4_devnum = wfd_p2p_get_devicenumber();
    for(i=0; i < i4_devnum; i++)
    {
        i4_ret = wfd_p2p_get_device_info(WFD_DEV_ALL, &t_dev_info, i);
        if(i4_ret != WFDR_OK)
        {
            return FALSE;
        }
        if(c_memcmp(t_dev_info.ps_device_mac, ps_mac_address, c_strlen(t_dev_info.ps_device_mac)) == 0)
        {
            if(WFDR_OK == wfd_p2p_is_connected(i))
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_unpair_device
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_unpair_device(UINT8 ui1_index)
{
    INT32   i4_ret = 0;
    
    i4_ret = a_wfd_device_info_delete_by_index(ui1_index);
    if(i4_ret != WFDR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }

    i4_ret = a_wfd_device_info_save_list();      
    if(i4_ret != WFDR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }

    /* Re-load the whole device list from Flash */
    a_wfd_device_info_load_list();

    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_init(VOID)
{
    INT32           i4_ret = 0;

    c_memset(&t_g_wfd_info, 0, sizeof(t_g_wfd_info));
    
    t_g_wfd_info.b_inited = TRUE;

    DLIST_INIT (&t_g_wfd_info.t_wfd_device_list) ;

    i4_ret = c_fm_partition_reg_nfy(_wfd_dev_3rd_mounted_nfy,0);
    if(0 != i4_ret)
    {
        return WFDR_FAIL;
    }

    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_wfd_device_info_store_new_device
 * Description check the current device, if it's a new device, store it into Flash & Device list
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wfd_device_info_store_new_device(WFD_DEVICE_INFO_T* pt_info)
{
    INT32                    i4_ret;
    NAV_WFD_DEVICE_INFO_T    t_device_info;

    c_memset(&t_device_info, 0, sizeof(NAV_WFD_DEVICE_INFO_T));
    
    if(FALSE == a_wfd_device_info_is_device_register(pt_info->ps_device_mac, DEVICE_INFO_ARR_LEN))
    {
        UINT8                    ui1_count = 0;
        INT32                    i4_ret = 0;

        DBG_LOG_PRINT(("\n%s,%s,%d,ps_device_mac=%s\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    pt_info->ps_device_mac));
        
        i4_ret = a_wfd_device_info_get_device_count(&ui1_count);
        if(i4_ret != WFDR_OK)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
        }

        /* handle the device number is more than MAX number(50) */
        if(ui1_count >= DEVICE_INFO_MAX_STORE_NUM)
        {
            i4_ret = a_wfd_device_info_delete_by_index(DEVICE_INFO_LIST_HEADER);
            if(i4_ret != WFDR_OK)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
                return WFDR_FAIL;
            }

            i4_ret = a_wfd_device_info_save_list();      
            if(i4_ret != WFDR_OK)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
                return WFDR_FAIL;
            }

            /* Re-load the whole device list from Flash */
            a_wfd_device_info_load_list();
        }

        c_memcpy(t_device_info.s_device_mac, pt_info->ps_device_mac, DEVICE_INFO_ARR_LEN); 
        c_memcpy(t_device_info.s_device_name, pt_info->ps_device_name, DEVICE_INFO_ARR_LEN); 
        c_memcpy(t_device_info.s_device_type, pt_info->ps_device_type, DEVICE_INFO_ARR_LEN); 
        
        i4_ret = a_wfd_device_info_add_device(&t_device_info);
        if(i4_ret != WFDR_OK)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
        
        i4_ret = a_wfd_device_info_save_list();      
        if(i4_ret != WFDR_OK)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
    }
    else
    {
        UINT8                    ui1_index = 0;
        SIZE_T                   z_size    = 0;

        DBG_LOG_PRINT(("\n%s,%s,%d,ps_device_mac=%s\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    pt_info->ps_device_mac));

        /* check whether need to update device name */
        i4_ret = a_wfd_device_info_get_device_info_by_mac(pt_info->ps_device_mac, &t_device_info);
        if(i4_ret != WFDR_OK)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }  

        if(c_strcmp(t_device_info.s_device_name, pt_info->ps_device_name) != 0)
        {
            i4_ret = a_wfd_device_info_get_device_index(&ui1_index, pt_info->ps_device_mac);
            if(i4_ret != WFDR_OK)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
                return WFDR_FAIL;
            }

            z_size = sizeof(pt_info->ps_device_name);
            i4_ret = a_wfd_device_info_set_device_info(ui1_index,
                                                       GET_WFD_DEVICE_INFO_ID_NAME,
                                                       &z_size,
                                                       (VOID*)pt_info->ps_device_name);
            if(i4_ret != WFDR_OK)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
                return WFDR_FAIL;
            }

            i4_ret = a_wfd_device_info_save_list();
            if(i4_ret != WFDR_OK)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
                return WFDR_FAIL;
            }
        }
    }

    return WFDR_OK;
}



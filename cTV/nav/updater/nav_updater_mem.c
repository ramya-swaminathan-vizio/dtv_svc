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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/

#include "app_util/a_updater.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/nav_common.h"
#include "nav/updater/nav_updater.h"
#include "res/app_util/updater/a_updater_custom.h"
#include "res/nav/nav_dbg.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 -----------------------------------------------------------------------------*/

typedef struct _UPDATER_MEM_CTRL_T
{
    UINT8*      pui1_buf;
    UINT32      ui4_total_fbm_size;
    UINT32      ui4_mem_pos;
    HANDLE_T    h_fbm_surf;
} UPDATER_MEM_CTRL_T;

/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/

static UPDATER_MEM_CTRL_T    t_g_mem_ctrl;

/*-----------------------------------------------------------------------------
                    private methods implementation
 -----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _nav_updater_mem_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_mem_open(
    CHAR*               ps_filename,
    DLM_OPEN_MODE_T     e_mode
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    pt_this->ui4_mem_pos = 0;

    return (INT32)nav_updater_get_fbm_addr();
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_mem_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_mem_close(
    INT32               i4_fd
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    pt_this->ui4_mem_pos = 0;

    if (i4_fd == (INT32)nav_updater_get_fbm_addr())
    {
        return NAVR_OK;
    }
    else
    {
        return NAVR_FAIL;
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_mem_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_mem_read(
    INT32               i4_fd,
    CHAR*               pc_buf,
    UINT32              ui4_buf_size
)
{
    SIZE_T              z_copy;

    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;
    UINT8*              pui1_buff = nav_updater_get_fbm_addr();

    if (0 == pui1_buff)
    {
        return 0;
    }

    if (i4_fd == (INT32)pui1_buff)
    {
        if ((pt_this->ui4_mem_pos + ui4_buf_size) > nav_updater_get_total_fbm_size())
        {
            z_copy = nav_updater_get_total_fbm_size() - pt_this->ui4_mem_pos;
        }
        else
        {
            z_copy = ui4_buf_size;
        }
        c_memcpy(pc_buf, &(pui1_buff[pt_this->ui4_mem_pos]), z_copy);

        pt_this->ui4_mem_pos += z_copy;

        return ((INT32)z_copy);
    }
    else
    {
        return 0;
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_mem_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_mem_eof(
    INT32               i4_fd
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    if (nav_updater_get_total_fbm_size() == pt_this->ui4_mem_pos)
    {
        return 1;
    }

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_mem_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT32 _nav_updater_mem_file_size(
    CHAR*    filename
)
{
    return nav_updater_get_total_fbm_size();
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_mem_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_mem_seek(
    INT32   i4_fd,
    UINT32  ui4_offset
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    if (i4_fd == (INT32)nav_updater_get_fbm_addr())
    {
        pt_this->ui4_mem_pos += ui4_offset;

        return 0;
    }

    return -1;
}

/*-----------------------------------------------------------------------------
                     public methods implementations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: nav_updater_mem_get_io_fn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 nav_updater_mem_get_io_fn(
    DLM_IO_T*    pt_io
)
{
    if (NULL == pt_io)
    {
        return NAVR_FAIL;
    }

    pt_io->open_source = _nav_updater_mem_open;
    pt_io->close_source = _nav_updater_mem_close;
    pt_io->read_data = _nav_updater_mem_read;
    pt_io->write_data = NULL;
    pt_io->eof_data = _nav_updater_mem_eof;
    pt_io->data_size = _nav_updater_mem_file_size;
    pt_io->seek_source = _nav_updater_mem_seek;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_get_dl_setting_ptr
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT8* nav_updater_get_fbm_addr(
    VOID
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    return (pt_this->pui1_buf);
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_get_total_file_size
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT32 nav_updater_get_total_fbm_size(
    VOID
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    return pt_this->ui4_total_fbm_size;
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_mem_release_fbm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_updater_mem_release_mem(
    VOID
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;
    INT32               i4_ret  = NAVR_OK;

    if (NULL != pt_this->pui1_buf)
    {
        /* release FBM */
        if (NULL_HANDLE != pt_this->h_fbm_surf)
        {
            i4_ret = c_gl_surface_unlock(pt_this->h_fbm_surf, 0);

            if (GLR_OK == i4_ret)
            {
                c_gl_obj_free(pt_this->h_fbm_surf);

                pt_this->h_fbm_surf = NULL_HANDLE;
            }
        }
        /* release memory */
        else
        {
            c_mem_free(pt_this->pui1_buf);
        }
    }
    pt_this->pui1_buf = NULL;
    pt_this->ui4_total_fbm_size = 0;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_mem_acquire_fbm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

INT32 nav_updater_mem_acquire_mem(
    UINT32                  ui4_sz,
    BOOL                    b_use_fbm,
    UINT8**                 ppui1_buf
)
{
    UPDATER_MEM_CTRL_T*     pt_this = &t_g_mem_ctrl;

    GL_SURFACE_DESC_T       t_surf_descr;
    INT32                   i4_ret;
    GL_LOCK_INFO_T          t_lock_info;
	c_memset (&t_lock_info, 0, sizeof(GL_LOCK_INFO_T));

    /* check parameters */
    if (ppui1_buf == NULL)
    {
        return NAVR_FAIL;
    }

    do
    {
        if (NULL == pt_this->pui1_buf)
        {
            if (TRUE == b_use_fbm)
            {
                c_memset(&t_surf_descr, 0, sizeof(GL_SURFACE_DESC_T));

                /* surface setting */
                t_surf_descr.ui4_width  = ui4_sz / 4;
                t_surf_descr.ui4_height = 1;
                t_surf_descr.e_clrmode  = GL_COLORMODE_ARGB_D8888;

                i4_ret = c_gl_surface_create_from_fbm(&t_surf_descr, &(pt_this->h_fbm_surf));

                if (GLR_OK != i4_ret)
                {
                    i4_ret = NAVR_FAIL;
                    break;
                }

                pt_this->ui4_total_fbm_size = ui4_sz;

                if (pt_this->h_fbm_surf != NULL_HANDLE)
                {
                    i4_ret = c_gl_surface_lock(pt_this->h_fbm_surf, 0, 0, &t_lock_info);

                    if (i4_ret != GLR_OK)
                    {
                        i4_ret = NAVR_FAIL;
                        break;
                    }
                }
                pt_this->pui1_buf = (UINT8*)(t_lock_info.at_subplane[0].pv_bits);
            }
            else
            {
                pt_this->pui1_buf = (UINT8*)c_mem_alloc((SIZE_T)ui4_sz);

                if (NULL == pt_this->pui1_buf)
                {
                    i4_ret = NAVR_FAIL;
                    break;
                }
                c_memset((VOID*)pt_this->pui1_buf, 0, (SIZE_T)ui4_sz);

                pt_this->ui4_total_fbm_size = ui4_sz;
            }

            *ppui1_buf = pt_this->pui1_buf;
        }
        else
        {
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = NAVR_OK;
    } while (0);

    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"%d, ret = %d\n", __LINE__, i4_ret));

        nav_updater_mem_release_mem();
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_mem_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_updater_mem_init(
    VOID
)
{
    UPDATER_MEM_CTRL_T*    pt_this = &t_g_mem_ctrl;

    pt_this->h_fbm_surf         = NULL_HANDLE;
    pt_this->pui1_buf           = NULL;
    pt_this->ui4_mem_pos        = 0;
    pt_this->ui4_total_fbm_size = 0;

    return;
}


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
 * $RCSfile: menu_rm_parse.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains all the raw memory related functions in menu.
 *---------------------------------------------------------------------------*/


#ifdef APP_MENU_VCT_RAW_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"

#include "menu2/menu.h"
#include "menu_rm_parse.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MRM_SECT_HDR_IDX_TBL_ID          0
#define MRM_SECT_HDR_IDX_SECT_SYNTAX_IND 1
#define MRM_SECT_HDR_IDX_PVT_IND         1
#define MRM_SECT_HDR_IDX_SECT_LEN        1
#define MRM_SECT_HDR_IDX_TBL_EXT_ID      3
#define MRM_SECT_HDR_IDX_VERSION_NUM     5
#define MRM_SECT_HDR_IDX_SECT_NUM        6
#define MRM_SECT_HDR_IDX_LAST_SECT_NUM   7

#define MRM_SECT_HDR_MASK_SECT_SYNTAX_IND  ((UINT8)    0x80)
#define MRM_SECT_HDR_MASK_PVT_IND          ((UINT8)    0x40)
#define MRM_SECT_HDR_MASK_SECT_LEN         ((UINT16) 0x0fff)
#define MRM_SECT_HDR_MASK_VERSION          ((UINT8)    0x3e)
#define MRM_SECT_HDR_MASK_CURR_NEXT_IND    ((UINT8)    0x01)

#define MRM_SECT_OVERHEAD  9

/* The following define specifies the max length of a section header. */
#define MRM_SECT_HDR_LEN  8

/*
    The partial header length including following fields:
    table_ID (1 byte) + section_syntax_indicator (1 bit) +
    private_indicator (1 bit) + reserved (2 bits) +
    section_length (12 bits): totally 3 bytes
*/
#define MRM_HDR_LEN_BEFORE_SECT_LEN     3

/*  MRM_CRC_LEN is 32 bits (4 bytes) */
#define MRM_CRC_LEN                     4

/* byte index in aui1_channel_entry[] */
#define MRM_CH_ENT_IDX_SNAME        0
#define MRM_CH_ENT_IDX_MAJOR_CH     14  /* last 4 bits + next 6 bits */
#define MRM_CH_ENT_IDX_MINOR_CH     15   /* last 2 bits + next byte */
#define MRM_CH_ENT_IDX_MOD          17
#define MRM_CH_ENT_IDX_FREQ         18
#define MRM_CH_ENT_IDX_TSID         22
#define MRM_CH_ENT_IDX_PROG_NUM     24
#define MRM_CH_ENT_IDX_ETM_LOC      26  /* first 2 bits */
#define MRM_CH_ENT_IDX_CA           26  /* the 3rd bit  */
#define MRM_CH_ENT_IDX_HIDDEN       26  /* the 4th bit  */
#define MRM_CH_ENT_IDX_HIDE_GUIDE   26  /* the 7th bit  */
#define MRM_CH_ENT_IDX_SVC_TYPE     27  /* last 6 bits  */
#define MRM_CH_ENT_IDX_SRC_ID       28
#define MRM_CH_ENT_IDX_DESCR_LEN    30  /* last 2 bits + next byte */
#define MRM_CH_ENT_IDX_DESCRS       32  /* beginning of channel descriptors */

#define MRM_VCT_CH_ENT_LEN          32


/* The following structure is a representation of a section header. */
typedef struct _MRM_SECT_HDR_T
{
    UINT8 ui1_tbl_id;          /* Table id. */

    BOOL  b_sect_syntax_ind;   /* Section syntax indicator. */
    BOOL  b_pvt_ind;           /* Private indicator. */

    UINT16  ui2_sect_len;      /* Section length. */
    UINT16  ui2_tbl_ext_id;    /* Table extension id. Only valid if "b_sect_syntax_ind == TRUE". */

    UINT8  ui1_version;        /* Version number. Only valid if "b_sect_syntax_ind == TRUE". */

    BOOL  b_curr_next_ind;     /* Current / next indicator. Only valid if "b_sect_syntax_ind == TRUE". */

    UINT8  ui1_sect_num;       /* Section number. Only valid if "b_sect_syntax_ind == TRUE". */
    UINT8  ui1_last_sect_num;  /* Last section number. Only valid if "b_sect_syntax_ind == TRUE". */

    SIZE_T  z_data_len;        /* Actual data length. */
}   MRM_SECT_HDR_T;

/*-----------------------------------------------------------------------------
                           data declaraions
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                        function implementation
 ----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Name: menu_rm_xlat_sect_hdr
 *
 * Description: This API translates a section header, received from a broadcast
 *              stream into a structure of type "MRM_SECT_HDR_T". At a minimum,
 *              the argument "pui1_sect_data" must reference the first 3 Bytes
 *              of the section, received via the broadcast stream.
 *
 * Inputs:  pui1_sect_data  References the first 3 or 8 Bytes of the section
 *                          data received via the braodacst stream.
 *
 * Outputs: pt_sect_hdr  Contains the translated section header.
 *
 * Returns: -
 --------------------------------------------------------------------------*/
static VOID menu_rm_xlat_sect_hdr (UINT8*           pui1_sect_data,
                                   MRM_SECT_HDR_T*  pt_sect_hdr)
{
    /* Initialize the section header. */
    if (pt_sect_hdr != NULL)
    {
        c_memset (((VOID*) pt_sect_hdr), 0, sizeof (MRM_SECT_HDR_T));

        if (pui1_sect_data != NULL)
        {
            /* Extract the section header. */
            pt_sect_hdr->ui1_tbl_id        = pui1_sect_data [MRM_SECT_HDR_IDX_TBL_ID];
            pt_sect_hdr->b_sect_syntax_ind = ((pui1_sect_data [MRM_SECT_HDR_IDX_SECT_SYNTAX_IND] & MRM_SECT_HDR_MASK_SECT_SYNTAX_IND) != 0);
            pt_sect_hdr->b_pvt_ind         = ((pui1_sect_data [MRM_SECT_HDR_IDX_PVT_IND] & MRM_SECT_HDR_MASK_PVT_IND) != 0);
            pt_sect_hdr->ui2_sect_len      = GET_UINT16_FROM_PTR_BIG_END (&(pui1_sect_data [MRM_SECT_HDR_IDX_SECT_LEN])) & MRM_SECT_HDR_MASK_SECT_LEN;

            if (pt_sect_hdr->b_sect_syntax_ind)
            {
                pt_sect_hdr->ui2_tbl_ext_id    = GET_UINT16_FROM_PTR_BIG_END (&(pui1_sect_data [MRM_SECT_HDR_IDX_TBL_EXT_ID]));
                pt_sect_hdr->ui1_version       = (pui1_sect_data [MRM_SECT_HDR_IDX_VERSION_NUM] & MRM_SECT_HDR_MASK_VERSION) >> 1;
                pt_sect_hdr->b_curr_next_ind   = ((pui1_sect_data [MRM_SECT_HDR_IDX_VERSION_NUM] & MRM_SECT_HDR_MASK_CURR_NEXT_IND) != 0);
                pt_sect_hdr->ui1_sect_num      = pui1_sect_data [MRM_SECT_HDR_IDX_SECT_NUM];
                pt_sect_hdr->ui1_last_sect_num = pui1_sect_data [MRM_SECT_HDR_IDX_LAST_SECT_NUM];

                pt_sect_hdr->z_data_len = (SIZE_T) (pt_sect_hdr->ui2_sect_len - MRM_SECT_OVERHEAD);
            }
            else
            {
                pt_sect_hdr->z_data_len = (SIZE_T) (pt_sect_hdr->ui2_sect_len);
            }
        }
    }
}


INT32 menu_rm_parse (VOID*       pv_mem,
                     SIZE_T      z_mem_len,
                     CH_LIST_T** ppt_ch_list)
{
    UINT16 ui2_num_sects = 0;
    UINT16 ui2_total_num_sects = 0;
    UINT16 ui2_num_channels = 0;
    UINT16 ui2_sect_offset = 0;
    UINT16 ui2_offset = 0;
    UINT16 ui2_idx = 0;
    UINT16 ui2_j;
    UINT8* pui1_mem = (UINT8*) pv_mem;
    MRM_SECT_HDR_T t_sect_hdr;
    CH_LIST_T*     pt_ch_list;
    CH_INFO_T*     pt_ch_info;

    if (ppt_ch_list == NULL ||
        pui1_mem    == NULL ||
        z_mem_len < MRM_SECT_HDR_LEN + 8)
    {
        return MENUR_INV_ARG;
    }

    /* first phase to get the number of sections and total number of channels */
    ui2_sect_offset = 0;
    while ((SIZE_T) (ui2_sect_offset + MRM_SECT_HDR_LEN + 3 + MRM_CRC_LEN) < z_mem_len)
    {
        menu_rm_xlat_sect_hdr (&(pui1_mem [ui2_sect_offset]), &t_sect_hdr);

        if (ui2_sect_offset == 0)
        {
            ui2_total_num_sects = (UINT16) t_sect_hdr.ui1_last_sect_num + 1;
        }

        ui2_num_channels += (UINT16) pui1_mem [ui2_sect_offset + MRM_SECT_HDR_LEN+1];
        ui2_num_sects += 1;
        ui2_sect_offset += MRM_HDR_LEN_BEFORE_SECT_LEN + t_sect_hdr.ui2_sect_len;
        /* ui2_sect_offset now points to the start of next section if any left */
    }

    if (ui2_total_num_sects == 0 || ui2_total_num_sects != ui2_num_sects)
    {
        return MENUR_FAIL;
    }

    /* allocate the memory for the channel list object pt_ch_list */
    pt_ch_list = c_mem_alloc(sizeof(CH_LIST_T) + sizeof(CH_INFO_T)*ui2_num_channels);

    if (pt_ch_list == NULL)
    {
        return MENUR_OUT_OF_MEMORY;
    }

    c_memset(pt_ch_list, 0, sizeof(CH_LIST_T) + sizeof(CH_INFO_T)*ui2_num_channels);

    pt_ch_list->ui2_num_sects = ui2_num_sects;
    pt_ch_list->ui2_num_channels = ui2_num_channels;
    pt_ch_list->pt_ch_info = (CH_INFO_T*) &(pt_ch_list[1]);

    /* 2nd phase to traverse the pv_mem again to fill in the parsed data */
    pt_ch_info = pt_ch_list->pt_ch_info;
    ui2_sect_offset = 0;
    ui2_idx = 0;
    while ((SIZE_T) (ui2_sect_offset + MRM_SECT_HDR_LEN + 3 + MRM_CRC_LEN) < z_mem_len)
    {
        menu_rm_xlat_sect_hdr (&(pui1_mem [ui2_sect_offset]), &t_sect_hdr);

        if (ui2_sect_offset == 0)
        {
            pt_ch_list->ui2_ts_id = t_sect_hdr.ui2_tbl_ext_id;
            pt_ch_list->ui2_ver = (UINT16) t_sect_hdr.ui1_version;
        }

        ui2_offset = ui2_sect_offset + MRM_SECT_HDR_LEN+1;

        ui2_num_channels = (UINT16) pui1_mem [ui2_offset];

        ui2_offset++;
        for (ui2_idx = 0; ui2_idx < ui2_num_channels; ui2_idx++)
        {
            if ((SIZE_T) (ui2_offset + MRM_VCT_CH_ENT_LEN +
                          2 /* global descriptors length */ +
                          4 /* CRC_32 */) >= z_mem_len)
            {
                c_mem_free(pt_ch_list);
                pt_ch_list = NULL;
                return MENUR_FAIL;
            }

            /* short name */
            for (ui2_j = 0; ui2_j < 7; ui2_j++)
            {
                pt_ch_info->w2s_ch_name[ui2_j] =
                    GET_UINT16_FROM_PTR_BIG_END(
                         &(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_SNAME+(ui2_j*2)]));
            }
            pt_ch_info->w2s_ch_name[7] = (UTF16_T) 0;

            /* major channel number */
            pt_ch_info->t_info.ui2_major_ch_num = 0x0ffc &
                GET_UINT16_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_MAJOR_CH]));
            pt_ch_info->t_info.ui2_major_ch_num >>= 2;

            /* minor channel number */
            pt_ch_info->t_info.ui2_minor_ch_num = 0x03ff &
                GET_UINT16_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_MINOR_CH]));

            /* modulation mode */
            pt_ch_info->t_info.ui1_mod_mode = pui1_mem[ui2_offset + MRM_CH_ENT_IDX_MOD];

            /* carrier frequency */
            pt_ch_info->t_info.ui4_freq =
                GET_UINT32_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_FREQ]));

            /* channel_TSID */
            pt_ch_info->t_info.ui2_ts_id =
                GET_UINT16_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_TSID]));

            /* program_number */
            pt_ch_info->t_info.ui2_svc_id =
                GET_UINT16_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_PROG_NUM]));

            /* control attributes */
            pt_ch_info->t_info.ui1_flags = MRM_VCT_FLAG_ETM_LOC_NONE;

            switch (pui1_mem[ui2_offset + MRM_CH_ENT_IDX_ETM_LOC] & 0xc0)
            {
            case 0x40:
                pt_ch_info->t_info.ui1_flags |= MRM_VCT_FLAG_ETM_LOC_THIS_PSIP;
                break;

            case 0x80:
                pt_ch_info->t_info.ui1_flags |= MRM_VCT_FLAG_ETM_LOC_CHANNEL_TS_ID;
                break;
            }

            if ((pui1_mem[ui2_offset + MRM_CH_ENT_IDX_CA] & 0x20) != 0)
            {
                pt_ch_info->t_info.ui1_flags |= MRM_VCT_FLAG_ACCESS_CONTROLLED;
            }

            if ((pui1_mem[ui2_offset + MRM_CH_ENT_IDX_HIDDEN] & 0x10) != 0)
            {
                pt_ch_info->t_info.ui1_flags |= MRM_VCT_FLAG_HIDDEN;
            }

            if ((pui1_mem[ui2_offset + MRM_CH_ENT_IDX_HIDE_GUIDE] & 0x02) != 0)
            {
                pt_ch_info->t_info.ui1_flags |= MRM_VCT_FLAG_HIDE_GUIDE;
            }

            /* service type */
            pt_ch_info->t_info.ui1_svc_type = pui1_mem[ui2_offset + MRM_CH_ENT_IDX_SVC_TYPE] & 0x3f;

            /* source id */
            pt_ch_info->t_info.ui2_src_id =
                GET_UINT16_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_SRC_ID]));

            /* the total length of channel descriptors */
            pt_ch_info->z_descrs_len =
                (SIZE_T) (GET_UINT16_FROM_PTR_BIG_END(&(pui1_mem[ui2_offset + MRM_CH_ENT_IDX_DESCR_LEN]))
                                                 & 0x03ff); /* there 6 bits reserved */

            /* the offset of channel descriptors */
            pt_ch_info->pv_descrs_offset =
                (VOID*) (ui2_offset + MRM_CH_ENT_IDX_DESCRS);

            /* the section number to which this channel belongs */
            pt_ch_info->ui2_sect_num = (UINT16) t_sect_hdr.ui1_sect_num;

            ui2_offset += MRM_VCT_CH_ENT_LEN + (UINT32) pt_ch_info->z_descrs_len;
            pt_ch_info ++; /* progress to the next ch info object */
        }

        ui2_sect_offset += MRM_HDR_LEN_BEFORE_SECT_LEN + t_sect_hdr.ui2_sect_len;
        /* ui2_sect_offset now points to the start of next section if any left */
    }

    *ppt_ch_list = pt_ch_list;

#if 0
    TSID:           pt_ch_list->ui2_ts_id;                                      [4 digits HEX];
    VCT Ver:        pt_ch_list->ui2_ver;                                        [2 digits HEX];
    Channel Num:    [Display channel number] see below.
        ShortName:  pt_ch_list->pt_ch_info[ui2_idx].w2s_ch_name;                [7 UTF16 words];
        Major Num:  pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num;    [2 digits HEX];
        Minor Num:  pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_minor_ch_num;    [2 digits HEX];
        Modulation: pt_ch_list->pt_ch_info[ui2_idx].t_info.ui1_mod_mode;        [1 digit  HEX];
        Frequency:  pt_ch_list->pt_ch_info[ui2_idx].t_info.ui4_freq;            [Dec];
        CH TSID:    pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_ts_id;           [4 digits HEX];
        Prog Num:   pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_svc_id;          [2 digits HEX];
        Src ID:     pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_src_id;          [2 digits HEX];
        Svc Type:   pt_ch_list->pt_ch_info[ui2_idx].t_info.ui1_svc_type;        [1 digit  HEX];
        Descriptors:pt_ch_list->pt_ch_info[ui2_idx].pv_descrs_offset;           [8 digits HEX];
        Descr Len:  pt_ch_list->pt_ch_info[ui2_idx].z_descrs_len;               [4 digits HEX];

Repeat
    Channel Num:
        ShortName:
        ...


   [Display channel number] is "CH a" or "CH a.b" format

       if ((pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num & 0x3f0) == 0x3f0)
       {
           /* "CH a" format */
           a = ((pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num & 0xf) << 10) |
                (pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_minor_ch_num & 0x3ff);
       }
       else
       {
           /* "CH a.b" format */
           a = pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num;
           b = pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_minor_ch_num;
       }

#endif

    return MENUR_OK;
}
#endif


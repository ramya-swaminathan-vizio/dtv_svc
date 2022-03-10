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
 * $RCSfile: stimer_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                            Include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "c_os.h"
#include "c_uc_str.h"
#include "c_iom.h"
#include "u_irrc_btn_def.h"
#include "app_util/a_common.h"
#include "amb/a_amb.h"
#include "app_util/a_cfg.h"
#include "app_util/a_sleep_timer.h"
#include "agent/a_agent.h"
#include "res/app_util/sleep_timer/stimer_mlm.h"

/*-----------------------------------------------------------------------------
                         Data Declarations
-----------------------------------------------------------------------------*/
/* #define STIMER_DEBUG */

static BOOL         b_g_init            = FALSE;
static HANDLE_T     h_g_timer_sleep     = NULL_HANDLE;
#ifdef STIMER_DEBUG
static HANDLE_T     h_g_timer_log       = NULL_HANDLE;
#endif
static HANDLE_T     b_g_timer_enabled   = FALSE;
static UINT32       ui4_g_sleep_time    = 0;
static UINT32       aui4_g_timer_recs[]   =
{
     0,
     30  * 60,
     60  * 60,
     90  * 60,
    120  * 60,
    180  * 60
};
static const UINT8  ui1_g_num_rec = (UINT8)(sizeof(aui4_g_timer_recs) / sizeof(aui4_g_timer_recs[0]));
static UINT32 ui4_g_prompt_time =  1 * 20;
static HANDLE_T     h_g_timer_prompt    = NULL_HANDLE;
static sleep_prompt_nfy_fct pf_g_prompt_nfy_fct = NULL;
static x_os_timer_cb_fct pf_g_prompt_timer_cb_fct = NULL;


#ifdef APP_STIMER_TIMEOUT_PROMPT
static HANDLE_T     h_g_timer_auto_sleep    = NULL_HANDLE;
static HANDLE_T     h_g_timer_auto_sleep_prompt    = NULL_HANDLE;
static BOOL         b_auto_sleep_init   = FALSE;
static HANDLE_T     h_iom;

#endif

/*-----------------------------------------------------------------------------
                       Private Function Implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _stimer_timer_nfy_fct
 *
 * Description: 
 *      The sleep timer callback function. When this function is called, issue 
 *  the standby request to application manager.
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static VOID _stimer_timer_nfy_fct(
    HANDLE_T  pt_tm_handle,
    VOID*     pv_tag)
{
    /* a_amb_power_on is an asynchronous function */
    a_amb_power_on(FALSE);
} 

/*----------------------------------------------------------------------------
 * Name: _stimer_timer_log_nfy_fct
 *
 * Description: 
 *      Log timer. It will log the remaining time.
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
#ifdef STIMER_DEBUG
static VOID _stimer_timer_log_nfy_fct(
    HANDLE_T  pt_tm_handle,
    VOID*     pv_tag)
{
    UINT32 ui4_time_remaing = 0;
    a_sleep_timer_get_remaining_time(&ui4_time_remaing);
    DBG_LOG_PRINT(("<STIMER>%d:%d\n", ui4_time_remaing/60, ui4_time_remaing%60));
} 
#endif

/*----------------------------------------------------------------------------
 * Name: _stimer_get_lang_idx
 *
 * Description: 
 *      Get the language index according to current GUI language.
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static UINT16 _stimer_get_lang_idx(VOID)
{
    INT32           i4_ret;
    ISO_639_LANG_T  s639_lang;
    UINT16          ui2_lang_idx = 0;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret == APP_CFGR_OK)
    {
        ui2_lang_idx = mlm_stimer_s639_to_langidx(s639_lang);
    }
    else
    {
        ui2_lang_idx = 0;
    }
                           
    return ui2_lang_idx;
}


/*----------------------------------------------------------------------------
 * Name: _stimer_prompt_timer_nfy_fct
 * Description: 
 * Inputs: 
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _stimer_prompt_timer_nfy_fct(HANDLE_T  pt_tm_handle,
                                         VOID*     pv_tag)
{
    if (pf_g_prompt_timer_cb_fct != NULL)
    {
        pf_g_prompt_timer_cb_fct(pt_tm_handle,pv_tag);
    }
}
#ifdef APP_STIMER_TIMEOUT_PROMPT

/*----------------------------------------------------------------------------
 * Name: _stimer_reset_auto_sleep_timer
 * Description: 
 * Inputs: 
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _stimer_reset_auto_sleep_timer (VOID* pv_data, SIZE_T z_data_len)
{
    UINT32  ui4_auto_sleep;
    a_cfg_get_auto_sleep(&ui4_auto_sleep);
    a_sleep_set_auto_sleep_timer(ui4_auto_sleep);
}

/*----------------------------------------------------------------------------
 * Name: _stimer_iom_nfy_fct
 * Description: 
 * Inputs: 
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _stimer_iom_nfy_fct (VOID*             pv_nfy_tag,
                                 IOM_NFY_COND_T    e_nfy_cond,
                                 UINT32            ui4_evt_code,
                                 UINT32            ui4_data)
{
    if (e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        switch (IOM_GET_EVT_GRP_ID(ui4_evt_code))
        {
            case BTN_VOL_DOWN:
            case BTN_VOL_UP:
            case BTN_SLEEP:
            {
              /* Only deal with this button*/
            }
            break;

           default:
           /* other key will not't handle */
           a_agent_async_invoke(_stimer_reset_auto_sleep_timer,NULL,0);
           break;
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _stimer_auto_sleep_init
 * Description: 
 * Inputs: 
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 _stimer_auto_sleep_init(VOID)
{
    INT32 i4_ret;
    IRRC_SETTING_T  t_irrc_setting = {0};

    do {
        /*Create Timer*/
        i4_ret = c_timer_create(&h_g_timer_auto_sleep);
        if(i4_ret != OSR_OK)
        {
            break;
        }

        i4_ret = c_timer_create(&h_g_timer_auto_sleep_prompt);
        if(i4_ret != OSR_OK)
        {
            break;
        }

        /*Register IO Mgr*/
        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 1000;  /* repeat key */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = 1000;  /* repeat key */
        t_irrc_setting.b_notify_raw_data        = TRUE;  /* Request to notify anyway. */
        i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                             IOM_DEV_ID_ANY,
                             NULL,
                             (VOID*) & t_irrc_setting,
                             NULL,
                             _stimer_iom_nfy_fct,
                             &h_iom);
        if(i4_ret < IOMR_OK)
        {
            break;
        }
        

        b_auto_sleep_init = TRUE;
        return STIMERR_OK;
    } while ( 0 );

    if (h_g_timer_auto_sleep != NULL_HANDLE)
    {
        c_timer_delete(h_g_timer_auto_sleep);
    }
    if (h_g_timer_auto_sleep_prompt != NULL_HANDLE)
    {
        c_timer_delete(h_g_timer_auto_sleep_prompt);
    }
    
    return STIMERR_FAIL;
}
#endif

/*-----------------------------------------------------------------------------
                       External Function Implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_init
 *
 * Description: 
 *      Initiate the sleep timer module. It should in application context.
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_init(VOID)
{
    INT32 i4_ret;
    if(b_g_init == FALSE)
    {
        i4_ret = c_timer_create(&h_g_timer_sleep);
        if(i4_ret != OSR_OK)
        {
            return STIMERR_FAIL;
        }

#ifdef STIMER_DEBUG
        i4_ret = c_timer_create(&h_g_timer_log);
        if(i4_ret != OSR_OK)
        {
            return STIMERR_FAIL;
        }
#endif

//#ifdef APP_STIMER_TIMEOUT_PROMPT
        i4_ret = c_timer_create(&h_g_timer_prompt);
        if(i4_ret != OSR_OK)
        {
            return STIMERR_FAIL;
        }
//#endif

        b_g_init      = TRUE;
    }
    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_iterate
 *
 * Description: 
 *      Iterate among sleep timer records. There are four iteration direction:
 *  STIMER_ITERATE_DIR_NEXT, STIMER_ITERATE_DIR_PREV, STIMER_ITERATE_DIR_FIRST
 *  STIMER_ITERATE_DIR_LAST. It will find the corresponding sleep timer record and
 *  start the timer if needed. 
 *
 * Inputs:
 *      t_iter      - iteration direction
 * Outputs:
 *      pui1_idx    - the target index of record.
 *      pui4_time   - how many seconds would the system stand by.
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_iterate(
    STIMER_ITERATE_T    t_iter,         /* in */
    UINT8*              pui1_idx,       /* out */
    UINT32*             pui4_time)      /* out */
{
    INT32   i4_ret;
    UINT32  ui4_time_remaining;
    UINT8   ui1_i;

    if(pui1_idx == NULL ||
       pui4_time == NULL)
    {
        return STIMERR_INV_ARG;
    }

    a_sleep_timer_get_remaining_time(&ui4_time_remaining);

    switch(t_iter)
    {
    case STIMER_ITERATE_DIR_CRNT:
        for(ui1_i=0; ui1_i < ui1_g_num_rec; ui1_i++)
        {
            if(aui4_g_timer_recs[ui1_i] >= ui4_time_remaining)
            {
                break;
            }
        }
        
        if (ui1_i == ui1_g_num_rec)
        {
            ui1_i = ui1_g_num_rec - 1 ;
        }
        else if (ui1_i == 0)
        {
            ui1_i = 0 ;
        }
        else if (
            ui4_time_remaining - aui4_g_timer_recs[ui1_i - 1] 
            <
            aui4_g_timer_recs[ui1_i] - ui4_time_remaining )
        {
            /* more closer to ui1_i - 1 */
            ui1_i = ui1_i - 1 ;
        }
        else 
        {
            ui1_i = ui1_i ;
        }

        *pui1_idx   = ui1_i ;
        *pui4_time  = aui4_g_timer_recs[*pui1_idx];
        break ;

    case STIMER_ITERATE_DIR_NEXT:
        for(ui1_i=0; ui1_i < ui1_g_num_rec; ui1_i++)
        {
            if(aui4_g_timer_recs[ui1_i] >= ui4_time_remaining)
            {
                break;
            }
        }

        if(ui1_i == ui1_g_num_rec)
        {
            /* The remaining time is greater than the largest record */
            *pui1_idx   = 0;
            *pui4_time  = aui4_g_timer_recs[*pui1_idx];
        }
        else
        {
            if(aui4_g_timer_recs[ui1_i] - ui4_time_remaining < 60)  /* in 1 min */
            {
                *pui1_idx   = (UINT8)(ui1_i != ((UINT8)(ui1_g_num_rec - 1)) ? ui1_i + 1 : 0);
                *pui4_time  = aui4_g_timer_recs[*pui1_idx];
            }
            else
            {
                *pui1_idx   = ui1_i;
                *pui4_time  = aui4_g_timer_recs[*pui1_idx];
            }
        }
        break;
    case STIMER_ITERATE_DIR_PREV:
        for(ui1_i=0; ui1_i < ui1_g_num_rec; ui1_i++)
        {
            if(aui4_g_timer_recs[ui1_i] >= ui4_time_remaining)
            {
                break;
            }
        }

        if(ui1_i == ui1_g_num_rec)
        {
            /* The remaining time is greater than the largest record */
            *pui1_idx   = (UINT8)(ui1_g_num_rec - 1);
            *pui4_time  = aui4_g_timer_recs[*pui1_idx];
        }
        else
        {
            *pui1_idx   = (UINT8)(ui1_i != 0 ? ui1_i - 1 : ui1_g_num_rec - 1);
            *pui4_time  = aui4_g_timer_recs[*pui1_idx];
        }
        break;
    case STIMER_ITERATE_DIR_FIRST:
        *pui1_idx  = 0;
        *pui4_time = aui4_g_timer_recs[0];
        break;
    case STIMER_ITERATE_DIR_LAST:
        *pui1_idx  = (UINT8)(ui1_g_num_rec - 1);
        *pui4_time = aui4_g_timer_recs[ui1_g_num_rec - 1];
        break;
    default:
        return STIMERR_INV_ARG;
    }

    if(*pui4_time != 0)
    {
        i4_ret = a_sleep_timer_start(*pui4_time);
    }
    else
    {
        i4_ret = a_sleep_timer_stop();
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_start
 *
 * Description: 
 *      Start the sleep timer. It is invalid to pass 0 as input.
 *
 * Inputs:
 *      ui4_time    - how many seconds would the system stand by.
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_start(
    UINT32      ui4_time)               /* in */
{
    INT32   i4_ret;
    if(ui4_time == 0)
    {
        return STIMERR_INV_ARG;
    }
//	ui4_time = 1  * 60;

    i4_ret = c_timer_start(h_g_timer_sleep,
                           ui4_time * 1000,
                           X_TIMER_FLAG_ONCE,
                           _stimer_timer_nfy_fct,
                           NULL); 
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }

#ifdef STIMER_DEBUG
    i4_ret = c_timer_start(h_g_timer_log,
                           1000,
                           X_TIMER_FLAG_REPEAT,
                           _stimer_timer_log_nfy_fct,
                           NULL); 
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }
#endif

//#ifdef APP_STIMER_TIMEOUT_PROMPT
    if (pf_g_prompt_nfy_fct != NULL)
    {
        pf_g_prompt_nfy_fct((VOID*)(UINT32)STIMER_REASON_RESCHEDULE,NULL,
                            (VOID*)(UINT32)STIMER_NFY_SRC_AUTO_SLEEP);
    }
    i4_ret = c_timer_start(h_g_timer_prompt,
                           (ui4_time-ui4_g_prompt_time) * 1000,
                           X_TIMER_FLAG_ONCE,
                           _stimer_prompt_timer_nfy_fct,
                           (VOID*)ui4_g_prompt_time); 
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }
//#endif

    ui4_g_sleep_time = (c_os_get_sys_tick() * c_os_get_sys_tick_period()) / 1000 + ui4_time;
    b_g_timer_enabled = TRUE;

    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_stop
 *
 * Description: 
 *      Stop the sleep timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_stop(VOID)
{
    INT32   i4_ret;

    i4_ret = c_timer_stop(h_g_timer_sleep);
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }

#ifdef STIMER_DEBUG
    i4_ret = c_timer_stop(h_g_timer_log);
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }
#endif

//#ifdef APP_STIMER_TIMEOUT_PROMPT
    i4_ret = c_timer_stop(h_g_timer_prompt);
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }
    if (pf_g_prompt_nfy_fct != NULL)
    {
        pf_g_prompt_nfy_fct((VOID*)(UINT32)STIMER_REASON_TIMEUP,NULL,
                            (VOID*)(UINT32)STIMER_NFY_SRC_AUTO_SLEEP);
    }
//#endif

    b_g_timer_enabled = FALSE;

    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_get_num_rec
 *
 * Description: 
 *      Get the number of sleep timer records.
 *
 * Inputs:
 *
 * Outputs:
 *      pui1_num_rec    - number of records.
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_get_num_rec(
    UINT8*      pui1_num_rec)           /* out */
{
    if(pui1_num_rec == NULL)
    {
        return STIMERR_INV_ARG;
    }

    *pui1_num_rec = ui1_g_num_rec;

    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_get_num_rec
 *
 * Description: 
 *      Get the sleep time by record index.
 *
 * Inputs:
 *      ui1_idx     - The index to get.
 * Outputs:
 *      pui4_time   - The sleep time for the given index.
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_get_time_by_idx(
    UINT8       ui1_idx,                /* in */
    UINT32*     pui4_time)              /* out */
{
    if(pui4_time == NULL ||
       ui1_idx >= ui1_g_num_rec)
    {
        return STIMERR_INV_ARG;
    }

    *pui4_time = aui4_g_timer_recs[ui1_idx];

    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_get_text
 *
 * Description: 
 *      Get the display text for a given time.
 *
 * Inputs:
 *      ui4_time    - The given time. (second)
 *      z_size      - size of w2s_str
 * Outputs:
 *      w2s_str     - The unicode string buffer to store.
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_get_text(
    UINT32      ui4_time,               /* in */
    UTF16_T*    w2s_str,                /* out */
    SIZE_T      z_size)                 /* in */
{
    CHAR    s_buf[64];
    UTF16_T w2s_buf[64];
    UINT32  ui4_min;

    c_memset(s_buf, 0, sizeof(s_buf));
    c_memset(w2s_buf, 0, sizeof(w2s_buf));

    if(ui4_time == 0)
    {
        c_uc_w2s_strcpy(w2s_buf, 
                        MLM_STIMER_TEXT(_stimer_get_lang_idx(),
                                        MLM_STIMER_KEY_MSG_OFF));
    }
    else
    {
        /* Get minute by ceiling */
        ui4_min = ui4_time / 60;
        if(ui4_min * 60 != ui4_time)
        {
            ui4_min++;
        }

        /* build the string */
        c_sprintf(s_buf, "%d", ui4_min); 
        c_uc_ps_to_w2s(s_buf, w2s_buf, 64);
        if(ui4_min == 1)
        {
            c_uc_w2s_strcat(w2s_buf, 
                            MLM_STIMER_TEXT(_stimer_get_lang_idx(),
                                            MLM_STIMER_KEY_MSG_MIN1));
        }
        else
        {
            c_uc_w2s_strcat(w2s_buf, 
                            MLM_STIMER_TEXT(_stimer_get_lang_idx(),
                                            MLM_STIMER_KEY_MSG_MIN2));
        }
    }

    c_uc_w2s_strncpy(w2s_str, w2s_buf, z_size);

    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_get_remaining_time
 *
 * Description: 
 *      Get the remaining time that the system would stand by.
 *
 * Inputs:
 *
 * Outputs:
 *      ui4_time    - how many seconds would the system stand by.
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_timer_get_remaining_time(
    UINT32*   pui4_time)                /* out */
{
    UINT32  ui4_time_curr;

    if(b_g_timer_enabled)
    {
        ui4_time_curr = c_os_get_sys_tick() * c_os_get_sys_tick_period() / 1000;
        *pui4_time = ui4_g_sleep_time - ui4_time_curr;
    }
    else
    {
        *pui4_time = 0;
    }

    return STIMERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_sleep_timer_reg_prompt_nfy
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/


extern INT32 a_sleep_timer_reg_prompt_nfy(sleep_prompt_nfy_fct pf_nfy_fct,
                                          x_os_timer_cb_fct pf_timer_cb_fct)
{
    if ((pf_nfy_fct == NULL) || (pf_timer_cb_fct == NULL))
    {
        return STIMERR_FAIL;
    }
    pf_g_prompt_nfy_fct = pf_nfy_fct;
    pf_g_prompt_timer_cb_fct = pf_timer_cb_fct;

    return STIMERR_OK;
}

#ifdef APP_STIMER_TIMEOUT_PROMPT

/*----------------------------------------------------------------------------
 * Name: a_sleep_set_auto_sleep_timer
 * Description: 
 * Inputs: ui4_sleep_time      Contains the auto sleep time in seconds.
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
extern INT32 a_sleep_set_auto_sleep_timer(UINT32 ui4_sleep_time)
{
    INT32 i4_ret;

    if (!b_auto_sleep_init)
    {
        _stimer_auto_sleep_init();
    }

    i4_ret = c_timer_stop(h_g_timer_auto_sleep);
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }

    i4_ret = c_timer_stop(h_g_timer_auto_sleep_prompt);
    if(i4_ret != OSR_OK)
    {
        return STIMERR_FAIL;
    }

    if (pf_g_prompt_nfy_fct != NULL)
    {
        pf_g_prompt_nfy_fct((VOID*)(UINT32)STIMER_REASON_RESCHEDULE,NULL,
                            (VOID*)(UINT32)STIMER_NFY_SRC_AUTO_SLEEP);
    }

    if(ui4_sleep_time > 0)
    {
        i4_ret = c_timer_start(h_g_timer_auto_sleep,
                               ui4_sleep_time * 1000,
                               X_TIMER_FLAG_ONCE,
                               _stimer_timer_nfy_fct,
                               NULL); 
        if(i4_ret != OSR_OK)
        {
            return STIMERR_FAIL;
        }

        i4_ret = c_timer_start(h_g_timer_auto_sleep_prompt,
                               (ui4_sleep_time-ui4_g_prompt_time) * 1000,
                               X_TIMER_FLAG_ONCE,
                               _stimer_prompt_timer_nfy_fct,
                               (VOID*)ui4_g_prompt_time); 
        if(i4_ret != OSR_OK)
        {
            return STIMERR_FAIL;
        }
    }

    return STIMERR_OK;
}

#endif


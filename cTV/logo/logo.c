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
 * $RCSfile: logo.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "logo/logo.h"
#include "app_util/a_icl.h"
#include "bgm/a_bgm.h"

/*-----------------------------------------------------------------------------
                    typedefs
-----------------------------------------------------------------------------*/

/*
   LOGO Model data.
*/
typedef struct _LOGO_MODEL_T
{
    HANDLE_T               h_logo;             /* LOGO application handle. */
    HANDLE_T               h_timer_timeout;    /* Timer to pause LOGO application. */
    HANDLE_T               h_canvas;           /* Canvas handle. */

}   LOGO_MODEL_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static LOGO_MODEL_T  t_g_model;
static BOOL  b_is_wake_up_from_bgm;


/*-----------------------------------------------------------------------------
 * Name: a_set_logo_wake_up_from_bgm
 *
 * Description: This callback function is called when timers expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern VOID a_set_logo_wake_up_from_bgm (BOOL  b_flag)
{
	b_is_wake_up_from_bgm = b_flag;
}

/*-----------------------------------------------------------------------------
 * Name: a_get_logo_wake_up_from_bgm
 *
 * Description: This callback function is called when timers expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern VOID a_get_logo_wake_up_from_bgm (BOOL*  b_flag)
{
	UINT8	 ui1_icl_val = ICL_RECID_LOGO_DISPLAY_STATUS_NOT_DISPLAYING;
    SIZE_T   z_size = ICL_RECID_LOGO_DISPLAY_STATUS_SIZE;
	INT32	 i4_ret = 0;
	
	*b_flag = b_is_wake_up_from_bgm;
	if(b_flag)//DTV00603884    CEC check the logo display status is not display . then logo resume then logo pause by cec.  so then bgm is set ture then set the logo display status.
	{
		ui1_icl_val = ICL_RECID_LOGO_DISPLAY_STATUS_DISPLAYING;
	    i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_LOGO_DISPLAY, ICL_RECID_LOGO_DISPLAY_STATUS),
	                       &ui1_icl_val,
	                       z_size);
	    if (i4_ret != 0)
	    {
	        DBG_LOG_PRINT(("\n== Failed in setting logo status==\n"));
	    }
	}
}


/*-----------------------------------------------------------------------------
 * Name: _logo_timer_nfy_fct
 *
 * Description: This callback function is called when timers expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _logo_timer_nfy_fct (HANDLE_T    h_timer,
                                 VOID*       pv_tag)
{
    /* Send a timer expired message to LOGO's message queue. */
    logo_app_send_msg (LOGO_MSG_CODE_TIMER_EXPIRED, & h_timer, 4);
}

/*-----------------------------------------------------------------------------
 * Name: _logo_init_canvas
 *
 * Description: The function initiates the canvas.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_init_canvas (VOID)
{
    INT32                 i4_ret;
    UINT16                ui2_plane_idx; /* Target plane index. */
    GL_HSCREEN_T          h_screen;      /* Screen handle. */
    GL_HPLANE_T           h_plane;       /* Plane handle. */

    /* Open screen. */
    i4_ret = c_gl_screen_open (SN_PRES_MAIN_DISPLAY,
                               NULL,
                               NULL,
                                & h_screen);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Get default OSD plane index. */
    ui2_plane_idx = a_util_get_default_osd_plane_index ();

    /* Open plane. */
    i4_ret = c_gl_plane_open (h_screen, ui2_plane_idx, & h_plane);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Link plane. */
    i4_ret = c_gl_plane_link (h_plane, h_screen, TRUE);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Open canvas. */
    i4_ret = c_wgl_get_canvas (h_plane, & t_g_model.h_canvas);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Free handles. */
    c_handle_free (h_screen);
    c_handle_free (h_plane);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_wgl_nfy_fct
 *
 * Description: This funcation is called by Widget Library (using thread conext
                of IO Manager).
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_wgl_nfy_fct (UINT32    ui4_msg,
                                VOID*     pv_param1,
                                VOID*     pv_param2)
{
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_app_init_fct
 *
 * Description: This function is called in the context of LOGO application when
 *              it starts.
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_app_init_fct (const CHAR*    ps_name,
                                 HANDLE_T       h_app)
{
    INT32    i4_ret;

    DBG_INFO (("<LOGO> initializing LOGO (application handle = %d)\n\r", (int) h_app));

    /* Reset model data. */
    c_memset (& t_g_model, 0, sizeof (LOGO_MODEL_T));

    /* Store LOGO application handle. */
    t_g_model.h_logo = h_app;

    /* Register to Widget Library. */
    i4_ret = c_wgl_register (_logo_wgl_nfy_fct);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Init canvas. */
    i4_ret = _logo_init_canvas ();
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Init CLI. */
    i4_ret = logo_cli_init ();
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Create timer. */
    i4_ret = c_timer_create (& t_g_model.h_timer_timeout);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_app_exit_fct
 *
 * Description: This function is called in the context of LOGO application when
 *              it exits. This API should be responsible for clean-up data, etc.
 *
 * Inputs:  h_app               Contains the application handle.
 *          e_exit_mode         Contains the exit mode.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 _logo_app_exit_fct (HANDLE_T           h_app,
                          APP_EXIT_MODE_T    e_exit_mode)
{
	b_is_wake_up_from_bgm = FALSE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_app_pause_fct
 *
 * Description: This function is called in the context of the LOGO application
                when it pauses.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_app_pause_fct (HANDLE_T    h_app)
{
    INT32    i4_ret;
    UINT8	 ui1_icl_val = ICL_RECID_LOGO_DISPLAY_STATUS_NOT_DISPLAYING;
    SIZE_T   z_size = ICL_RECID_LOGO_DISPLAY_STATUS_SIZE;
    
    /* Hide view. */
    i4_ret = logo_view_hide ();
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Destroy view. */
    i4_ret = logo_view_destroy ();
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    ui1_icl_val = ICL_RECID_LOGO_DISPLAY_STATUS_NOT_DISPLAYING;
    i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_LOGO_DISPLAY, ICL_RECID_LOGO_DISPLAY_STATUS),
                       &ui1_icl_val,
                       z_size);
    if (i4_ret != 0)
    {
        DBG_ERROR(("\n== Failed in setting logo status==\n"));
    }
    
    /* Issue a request to exit LOGO. */
    a_amb_exit_app (LOGO_NAME);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_app_resume_fct
 *
 * Description: This function is called in the context of LOGO application when
 *              it resumes.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_app_resume_fct (HANDLE_T    h_app)
{
    INT32    i4_ret;
	UINT8	 ui1_icl_val = ICL_RECID_LOGO_DISPLAY_STATUS_NOT_DISPLAYING;
	SIZE_T	 z_size = ICL_RECID_LOGO_DISPLAY_STATUS_SIZE;

    /* Init view. */
    i4_ret = logo_view_init (t_g_model.h_canvas);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Show view. */
	
    ui1_icl_val = ICL_RECID_LOGO_DISPLAY_STATUS_DISPLAYING;
    i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_LOGO_DISPLAY, ICL_RECID_LOGO_DISPLAY_STATUS),
                       &ui1_icl_val,
                       z_size);
    if (i4_ret != 0)
    {
        DBG_LOG_PRINT(("\n== Failed in setting logo status==\n"));
    }
    
    i4_ret = logo_view_show ();
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Start timer to pause LOGO application. */
    i4_ret = c_timer_start (t_g_model.h_timer_timeout,
                            LOGO_TIMER_TIMEOUT_DELAY,
                            X_TIMER_FLAG_ONCE,
                            _logo_timer_nfy_fct,
                            NULL);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_app_process_msg_fct
 *
 * Description: This function is called in the context of LOGO application
 *              when a message is received.
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_app_process_msg_fct (HANDLE_T       h_app,
                                        UINT32         ui4_type,
                                        const VOID*    pv_msg,
                                        SIZE_T         z_msg_len,
                                        BOOL           b_paused)
{
    switch (ui4_type)
    {
        case LOGO_MSG_CODE_TIMER_EXPIRED:
        {
            if (*((HANDLE_T*) pv_msg) == t_g_model.h_timer_timeout)
            {
                /* Pause LOGO application. */
                a_amb_pause_app (LOGO_NAME);
            }
        }
        break;

        default:
            break;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _logo_power_seq_cb_fct
 *
 * Description: This function is called by Application when the system is going
 *              to be power-on.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                The application wants to grab power on sequence.
 *          FALSE               The application doesn't want to grab power on
 *                              sequence.
 ----------------------------------------------------------------------------*/
static BOOL _logo_power_seq_cb_fct (VOID)
{
    BOOL                    b_grab = TRUE;
	INT32					i4_ret;
	PCL_WAKE_UP_REASON_T	e_wakeup_reason;

	/* Get wake-up reason. */
	i4_ret = c_pcl_get_wakeup_reason (& e_wakeup_reason, NULL);
	DBG_INFO(("\n=============_logo_power_seq_cb_fct===============wakeup_reason:%d,line:%d\n",e_wakeup_reason,__LINE__));
	
	if ((i4_ret == PCLR_OK) &&
		((e_wakeup_reason == PCL_WAKE_UP_REASON_IRRC)
		  || (e_wakeup_reason == PCL_WAKE_UP_REASON_FP)
		  || (e_wakeup_reason == PCL_WAKE_UP_REASON_HDMI)))
	{
		if(b_is_wake_up_from_bgm)
		{
			b_grab = TRUE;
			b_is_wake_up_from_bgm = FALSE;
		}
		else
		{
			b_grab = FALSE;
		}
		DBG_INFO(("\n==========_logo_power_seq_cb_fct==============%d\n",__LINE__));
	}
	
	else
	{
		b_grab = FALSE;
	}

#ifdef APP_LOGO_NO_DISPLAY_WHEN_VGA_WAKEUP

    INT32                   i4_ret;
    PCL_WAKE_UP_REASON_T    e_wakeup_reason;

    /* Get wake-up reason. */
    i4_ret = c_pcl_get_wakeup_reason (& e_wakeup_reason, NULL);

    if ((i4_ret == PCLR_OK) &&
        (e_wakeup_reason == PCL_WAKE_UP_REASON_VGA))
    {
        b_grab = FALSE;
    }

#endif /* APP_LOGO_NO_DISPLAY_WHEN_VGA_WAKEUP */

#ifdef APP_LOGO_CUSTOMIZE_POWER_SEQ_GRAB_LOGIC

    extern BOOL logo_custom_grab_power_seq (VOID);

    b_grab = logo_custom_grab_power_seq ();
    
#endif /* APP_LOGO_CUSTOMIZE_POWER_SEQ_GRAB_LOGIC */

    return b_grab;
}

/*-----------------------------------------------------------------------------
                    public functions implemenations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: logo_app_send_msg
 *
 * Description: This API sends a message to the message queue of LOGO application.
 *
 * Inputs:  ui4_type            Contains the type of the data.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 logo_app_send_msg (UINT32         ui4_type,
                         const VOID*    pv_msg,
                         SIZE_T         z_msg_len)
{
    INT32   i4_ret;

    /* Send a message to LOGO's message queue. */
    i4_ret = c_app_send_msg (t_g_model.h_logo,
                             ui4_type,
                             pv_msg,
                             z_msg_len,
                             NULL,
                             NULL);

    if (i4_ret != AEER_OK)
    {
        DBG_ERROR (("<LOGO> ERR: send message = %d failed = %d\n\r", ui4_type, i4_ret));
    }

    return (i4_ret == AEER_OK) ? LOGOR_OK : LOGOR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: a_logo_init
 *
 * Description: This API registers LOGO application to AMB.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_logo_init (AMB_REGISTER_INFO_T*  pt_reg)
{
    /* Application descriptor. */
    APP_DESC_T  t_logo_desc =
                {
                    ~((UINT64)0),   /* ui8_flags */
                    {
                        8 * 1024,   /* z_stack_size */
                        200,        /* ui1_priority */
                        16          /* ui2_num_msgs */
                    },
                    0,              /* ui4_app_group_id */
                    0,              /* ui4_app_id */
                    {
                        10 * 1024,  /* z_min_memory */
                        10 * 1024,  /* z_max_memory */
                        0,          /* ui8_max_files_size */
                        0,          /* ui2_max_files */
                        32,         /* ui2_max_handles */
                        1,          /* ui2_max_threads */
                        2,          /* ui2_max_semaphores */
                        1,          /* ui2_max_msg_queues */
                        64,         /* ui2_max_nb_msgs */
                        16          /* ui2_max_msg_size */
                    },
                    64,             /* ui2_msg_count */
                    16              /* ui2_max_msg_size */
                };

    /* Application name. */
    c_memset (pt_reg->s_name, 0, sizeof (pt_reg->s_name));
    c_strcpy (pt_reg->s_name, LOGO_NAME);

    /* Lifecycle callback functions. */
    pt_reg->t_fct_tbl.pf_init        = _logo_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit        = _logo_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause       = _logo_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume      = _logo_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg = _logo_app_process_msg_fct;

    /* Application descriptor. */
    pt_reg->t_desc                   = t_logo_desc;

    /* System key. */
    pt_reg->ui2_key_num              = 0;

    /* Attach power sequence callback. */
    pt_reg->pf_power_seq_cb          = _logo_power_seq_cb_fct;
}

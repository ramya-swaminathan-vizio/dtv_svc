###############################################################################
# Copyright Statement:                                                        #
#                                                                             #
#   This software/firmware and related documentation ("MediaTek Software")    #
# are protected under international and related jurisdictions'copyright laws  #
# as unpublished works. The information contained herein is confidential and  #
# proprietary to MediaTek Inc. Without the prior written permission of        #
# MediaTek Inc., any reproduction, modification, use or disclosure of         #
# MediaTek Software, and information contained herein, in whole or in part,   #
# shall be strictly prohibited.                                               #
# MediaTek Inc. Copyright (C) 2010. All rights reserved.                      #
#                                                                             #
#   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND      #
# AGREES TO THE FOLLOWING:                                                    #
#                                                                             #
#   1)Any and all intellectual property rights (including without             #
# limitation, patent, copyright, and trade secrets) in and to this            #
# Software/firmware and related documentation ("MediaTek Software") shall     #
# remain the exclusive property of MediaTek Inc. Any and all intellectual     #
# property rights (including without limitation, patent, copyright, and       #
# trade secrets) in and to any modifications and derivatives to MediaTek      #
# Software, whoever made, shall also remain the exclusive property of         #
# MediaTek Inc.  Nothing herein shall be construed as any transfer of any     #
# title to any intellectual property right in MediaTek Software to Receiver.  #
#                                                                             #
#   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its  #
# representatives is provided to Receiver on an "AS IS" basis only.           #
# MediaTek Inc. expressly disclaims all warranties, expressed or implied,     #
# including but not limited to any implied warranties of merchantability,     #
# non-infringement and fitness for a particular purpose and any warranties    #
# arising out of course of performance, course of dealing or usage of trade.  #
# MediaTek Inc. does not provide any warranty whatsoever with respect to the  #
# software of any third party which may be used by, incorporated in, or       #
# supplied with the MediaTek Software, and Receiver agrees to look only to    #
# such third parties for any warranty claim relating thereto.  Receiver       #
# expressly acknowledges that it is Receiver's sole responsibility to obtain  #
# from any third party all proper licenses contained in or delivered with     #
# MediaTek Software.  MediaTek is not responsible for any MediaTek Software   #
# releases made to Receiver's specifications or to conform to a particular    #
# standard or open forum.                                                     #
#                                                                             #
#   3)Receiver further acknowledge that Receiver may, either presently        #
# and/or in the future, instruct MediaTek Inc. to assist it in the            #
# development and the implementation, in accordance with Receiver's designs,  #
# of certain softwares relating to Receiver's product(s) (the "Services").    #
# Except as may be otherwise agreed to in writing, no warranties of any       #
# kind, whether express or implied, are given by MediaTek Inc. with respect   #
# to the Services provided, and the Services are provided on an "AS IS"       #
# basis. Receiver further acknowledges that the Services may contain errors   #
# that testing is important and it is solely responsible for fully testing    #
# the Services and/or derivatives thereof before they are used, sublicensed   #
# or distributed. Should there be any third party action brought against      #
# MediaTek Inc. arising out of or relating to the Services, Receiver agree    #
# to fully indemnify and hold MediaTek Inc. harmless.  If the parties         #
# mutually agree to enter into or continue a business relationship or other   #
# arrangement, the terms and conditions set forth herein shall remain         #
# effective and, unless explicitly stated otherwise, shall prevail in the     #
# event of a conflict in the terms in any agreements entered into between     #
# the parties.                                                                #
#                                                                             #
#   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and     #
# cumulative liability with respect to MediaTek Software released hereunder   #
# will be, at MediaTek Inc.'s sole discretion, to replace or revise the       #
# MediaTek Software at issue.                                                 #
#                                                                             #
#   5)The transaction contemplated hereunder shall be construed in            #
# accordance with the laws of Singapore, excluding its conflict of laws       #
# principles.  Any disputes, controversies or claims arising thereof and      #
# related thereto shall be settled via arbitration in Singapore, under the    #
# then current rules of the International Chamber of Commerce (ICC).  The     #
# arbitration shall be conducted in English. The awards of the arbitration    #
# shall be final and binding upon both parties and shall be entered and       #
# enforceable in any court of competent jurisdiction.                         #
###############################################################################
###########################################################################
#
# Description:
#         Leave-level makefile to build the subcomponent of Middleware library.
#
#         Specify the source files to be compile in SRC.
#############################################################################

ifndef PROJECT_ROOT
PROJECT_ROOT := $(word 1, $(subst /project_x/,/project_x /, $(shell pwd)))
endif



THIS_COMPONENT = menu2_common



SRC = menu_common.c	    	    \
      menu_common_settings.c	\
      menu_page_pwd.c 	    	\
      menu_page_chg_pwd.c   	\
      menu_page_ch_lst2.c   	\
      menu_page_ver_info.c  	\
      menu_page_divx_info.c  	\
      menu_page_divx_deact.c  	\
      menu_page_simple_dialog.c \
      menu_page_vga_auto.c  	\
      menu_page_auto_color.c  	\
      menu_page_auto_phase.c  	\
      menu_page_inp_lst.c  	    \
      menu_page_date_time.c 	\
      menu_page_burn.c 		    \
      menu_page_img_clnr.c 	    \
      menu_page_bbe.c 	        \
      menu_page_aud_fac.c       \
      menu_page_tuner_fac.c     \
      menu_page_mjc_demo.c      \
      menu_cli.c                \
      menu_page_time_zone.c     \
      menu_page_vga_ambiguous.c \
      menu_page_naming.c        \
      menu_page_inp_src.c       \
      menu_page_inp_edit.c      \
      menu_page_scr_mode.c      \
      menu_page_clear_memory_pwd.c	\
      menu_page_animation.c         \
      menu_page_3d_setting.c     \
      menu_page_time_local_setting_auto_dst.c	\
      menu_page_vizio_tos.c			\
      menu_page_color_tuner.c	\
      menu_page_white_balance_tuner.c\
      menu_page_scrn_blank.c	\
      menu_page_create_pic_mode.c\
      menu_page_pic_mode_edit.c\
      menu_page_color_calibration.c\
      menu_page_lock_pic_mode.c	\
      menu_page_delete_pic_mode.c\
      menu_page_unlock_pic_mode.c \
      menu_page_vid_position.c  \
      menu_page_vid_size.c      \
      menu_page_new_eq.c				\
      menu_page_picture_mode.c  \
      menu_page_tv_name.c     \
      menu_page_test_mc_version.c\
      menu_page_test_special_param.c  \
      menu_page_log_to_usb.c \
      menu_page_input_sys_pin.c  \
      menu_page_aspect_ratio.c  \
      menu_page_sb_setting_eq_mode.c  \
      menu_page_lock_pic_mode_lb2.c   \
      menu_page_gaming_mode.c \
      menu_page_audio_dbginfo.c \
      menu_page_hdmi_dbginfo.c


# SRC += menu_page_calibration_test.c


ifneq ($(strip $(findstring -DAPP_CEC_MENU, $(DEFINES))),)
SRC += menu_page_cec.c
endif

OBJ =

SUB_COMPONENTS =

OPTIONAL_SUB_COMPONENTS =  menu_fe_chk menu_factory

ifdef PSEUDO_GL
DEFINES += -DPSEUDO_GL
endif

ifdef MEM_MONITORING
DEFINES += -DMEM_MONITORING
endif

ifdef DEBUGING
DEFINES += -DDEBUGING
endif

CC_INC += -I$(TARGET_ROOT)/d_inc -I$(D_INC_DIR)

CC_INC += -I$(UPDATETV_INC_PATH)
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/open/misc/wifi_rc_control/wfrrc_interface/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/open/misc/app_man/common

ifeq "$(MTK_CAMERA_DPTZ_SUPPORT)" "true"
DEFINES += -DMTK_CAMERA_DPTZ_SUPPORT
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/library/gnuarm-$(TOOL_CHAIN)$(VFP_SUFFIX)/mtk_camera/mtkv4l2/include
endif
#############################################################################
#
# Include the makefile common to all components
#
include $(CUSTOM_ROOT)/common.mak

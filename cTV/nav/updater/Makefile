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
# $Revision: #1 $
# $Date: 2009/11/09 $
# $Author: dtvbm11 $
#
# Description:
#         Specify the source files to be compile in SRC.
#############################################################################
ifndef TARGET
TARGET = mt5351
endif

ifndef PROJECT_ROOT
PROJECT_ROOT := $(word 1, $(subst /project_x/,/project_x /, $(shell pwd)))
endif


THIS_COMPONENT = nav_updater

SRC = nav_updater.c         \
      nav_updater_view.c    \
      nav_updater_usb.c     \
      nav_updater_sys.c     \
      nav_updater_mem.c

OBJ =

ifeq "$(MTK_CAMERA_DPTZ_SUPPORT)" "true"
DEFINES += -DMTK_CAMERA_DPTZ_SUPPORT
SRC += nav_updater_isp.c
endif

ifneq "$(findstring VIZIO_FUSION_SUPPORT, $(DEFINES))" "VIZIO_FUSION_SUPPORT"
ifeq "$(FW_UPG_SUPPORT)" "uli"
SRC += nav_updater_uli.c
endif
endif

SUB_COMPONENTS =

OPTIONAL_SUB_COMPONENTS =

#############################################################################
#
# Include the makefile common to all components
#
include $(CUSTOM_ROOT)/common.mak

CC_INC += -I$(UPDATETV_INC_PATH)
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/open/misc/wifi_rc_control/wfrrc_interface/include
CC_INC += -I$(VM_LINUX_ROOT)/oss/library/gnuarm-$(TOOL_CHAIN)$(VFP_SUFFIX)/curl/curl-$(CURL_VERSION)/include
CC_INC += -I$$(OSS_LIB_ROOT)/openssl/$(OPENSSL_VERSION)/include

ifeq "$(MTK_CAMERA_DPTZ_SUPPORT)" "true"
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/library/gnuarm-$(TOOL_CHAIN)$(VFP_SUFFIX)/mtk_camera/mtkv4l2/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/iniparser/inc
endif

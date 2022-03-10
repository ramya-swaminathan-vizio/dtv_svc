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
# $RCSfile: Makefile,v $
# $Revision: #1 $
# $Date: 2009/03/20 $
# $Author: dtvbm11 $
# $CCRevision: /main/DTV_X_ATSC/2 $
# $SWAuthor: Iolo Tsai $
# $MD5HEX: a90666f1984171f88f3748d5aac6f48d $
# Description:
#         Leave-level makefile to build the subcomponent of Middleware library.
#
#         Specify the source files to be compile in SRC.
#############################################################################

ifndef PROJECT_ROOT
PROJECT_ROOT := $(word 1, $(subst /project_x/,/project_x /, $(shell pwd)))
endif



THIS_COMPONENT = dev


SRC =

OBJ =


SUB_COMPONENTS = Vizio/cTV/nav          \
                 dev/am                 \
                 dev/amb                \
                 Vizio/cTV/menu2        \
                 Vizio/cTV/mdns         \
                 Vizio/cTV/app_util     \
                 Vizio/cTV/fonts        \
                 Vizio/cTV/logo         \
                 dev/agent              \
                 dev/app_util/rmv_dev   \
                 dev/app_util/key_seq   \
                 dev/app_util/platform_api   \
                 dev/boot_anim          \
                 Vizio/cTV/wdk          \
                 dev/msgconvert         \
                 dev/bgm                \
                 dev/bgm/mtk_comp/bgm_power_mgmt       \
                 dev/bgm/mtk_comp/bgm_updater_uli      \
                 dev/bgm/mtk_comp/bgm_pre_shutdown     \
                 dev/bgm/mtk_comp/bgm_cast_c4tv  \
                 dev/bgm/mtk_comp/bgm_updater_dlm  \
                 dev/bgm/mtk_comp/bgm_nfx_ar  \
                 dev/bgm/mtk_comp/bgm_oled_compensation  \
                 Vizio/cTV/res  \
                 Vizio/cTV/registry

SUB_COMPONENTS += Vizio/cTV/fac_shell/gluelayer                 \
                  Vizio/cTV/fac_shell/fac_convert               \
                  Vizio/cTV/fac_shell/fac_shell_cli

#use ctv folder's model, if need in furture, add it again
#SUB_COMPONENTS += Vizio/cTV/fac_shell/fac_convert/res/app_util/model
#SUB_COMPONENTS += Vizio/cTV/fac_shell/fac_convert/res/wizard_anim

#ke_vizio_20160427
#SUB_COMPONENTS += Vizio/TPV/res/TPV_factory

#ifeq "$(C4TV)" "true"
SUB_COMPONENTS += dev/nav/c4tv_apron \
                 dev/bgm/mtk_comp/bgm_cast_update
#endif

ifeq "$(MTK_CAMERA_DPTZ_SUPPORT)" "true"
SUB_COMPONENTS += dev/bgm/mtk_comp/bgm_motor
endif

ifeq "$(TVSTATUS_ENABLE)" "true"
SUB_COMPONENTS += Vizio/cTV/tvstate
endif

ifeq "$(WZD_ANIM_ENABLE)" "true"
SUB_COMPONENTS += Vizio/cTV/wizard_anim     \
                  Vizio/cTV/res/wizard_anim
else
SUB_COMPONENTS += Vizio/cTV/wizard          \
                  Vizio/cTV/res/wizard
endif

OPTIONAL_SUB_COMPONENTS =

ifeq "$(APP_MMP_ENABLE)" "true"
SUB_COMPONENTS += Vizio/cTV/mmp
endif

ifeq "$(ENABLE_WIFI_DISPLAY)" "true"
SUB_COMPONENTS += Vizio/cTV/wfd
endif

#ifeq "$(VSSP_REST_SERVER)" "true"
SUB_COMPONENTS += Vizio/cTV/rest
#endif

ifeq "$(EAS_SUPPORT)" "true"
SUB_COMPONENTS += dev/eas
endif

ifeq "$(ENABLE_EPG)" "true"
SUB_COMPONENTS += Vizio/cTV/epg
endif

ifeq "$(MTKTVAPI_SUPPORT)" "true"
SUB_COMPONENTS += dev/app_util/mtktvapi
endif

DEFINES +=

#ke_vizio_20160427
CC_INC +=	-I$(CUSTOM_BASE)/Vizio/cTV/fac_shell    \
            -I$(CUSTOM_BASE)/Vizio/cTV/fac_shell/fac_convert    \
          	-I$(CUSTOM_BASE)/Vizio/cTV/fac_shell/gluelayer \
          	-I$(CUSTOM_BASE)/Vizio/cTV/fac_shell/fac_shell_cli

CC_INC += -I$(CUSTOM_BASE)/Vizio/cTV -I$(CUSTOM_BASE)/dev
#CC_INC += -I$(CUSTOM_BASE)/Vizio/cTV -I$(CUSTOM_BASE)/dev -I$(CUSTOM_BASE)/Vizio/TPV/res

ifeq "$(BLUETOOTH_SUPPORT)" "true"
SUB_COMPONENTS += Vizio/cTV/bluetooth_gatt
CC_INC += -I$(OSS_LIB_ROOT)/bluetooth_mw/include
CC_INC += -I$(OSS_LIB_ROOT)/bluetooth_mw/include_rpc
CC_INC += -I$(OSS_LIB_ROOT)/openssl/$(OPENSSL_VERSION)/include
endif

ifeq "$(MDNS_SUPPORT)" "true"
CC_INC += -I$(OSS_LIB_ROOT)/mDNSResponder/$(MDNS_VERSION)/include
endif

CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/extlibs/target/include/fairplay/tee/

CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/mm/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/imgdec/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/mi_header
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/fs/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/osd/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/video/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/disp/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/dispout/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/aout/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/internal
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/sys/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/mi/mi/modules/os/include
CC_INC += -I$(VM_LINUX_ROOT)/linux_core/misdk/security/utility/intertaca/include
CC_INC += -I$(VM_LINUX_ROOT)/oss/source/cJSON/1.7.7
CC_INC += -I$(UPDATETV_INC_PATH)
#############################################################################
#
# Include the makefile common to all components
#
include $(CUSTOM_ROOT)/common.mak

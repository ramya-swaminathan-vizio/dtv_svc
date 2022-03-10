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
# $RCSfile: common.mak,v $
# $Revision: #2 $
# $Date: 2015/05/31 $
# $Author: hong.wang $
# $CCRevision: /main/DTV_X_ATSC/1 $
# $SWAuthor: Iolo Tsai $
# $MD5HEX: 7b352a9c8404e71c4c3d57373e585c2f $
#
# Description:
#         common makefile to all components.
#
#############################################################################

#
# List all libraries in this sequence. Do not create a library if SRC was
# defined on the command line.
#
include $(DTV_LINUX_MAK_ROOT)/nucleus_path.mak
ifeq "$(origin SRC)" "command line"
SUB_COMPONENTS          :=
OPTIONAL_SUB_COMPONENTS :=

THIS_LIB :=
LIBS     :=

else
THIS_LIB := lib$(THIS_COMPONENT).a

ifeq ($(strip $(ENTER_OPT_SUB_COMP)),TRUE)
LIBS := $(CUSTOM_LIB_DIR)/$(THIS_LIB)
else
ifeq "$(ENTER_OPT_SUB_COMP)" ""
LIBS := $(sort $(LIBS) $(CUSTOM_LIB_DIR)/$(THIS_LIB))
endif
endif
endif

export THIS_LIB
export LIBS

export SRC_CPP := $(filter %.cpp, $(SRC))
ifneq "$(SRC_CPP)" ""
SRC := $(filter-out %.cpp, $(SRC))
endif

#
# Specify the object files with full path. Note that we add a
# prefix dummy directory to the existing entries in OBJ so
# that we can process it correctly with the rules.
#
SRC_OBJ := $(SRC:.c=.o) $(SRC_CPP:.cpp=.o)

ABS_OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ) $(SRC_OBJ))

OBJ := $(addprefix _obj_/, $(OBJ))
OBJ += $(SRC_OBJ)

export OBJ
export ABS_OBJ


#
# Specify the dependability files
#
DEPEND     := $(SRC:.c=.d) $(SRC_CPP:.cpp=.d)
ABS_DEPEND := $(addprefix $(DEPEND_DIR)/, $(DEPEND))

export DEPEND
export ABS_DEPEND


#
# Specify the lint files
#
LINT_OBJ     := $(SRC:.c=.lint)
ABS_LINT_OBJ := $(addprefix $(LINT_DIR)/, $(LINT_OBJ))

export LINT_OBJ
export ABS_LINT_OBJ

LINT_CSV     := $(SRC:.c=.lint.csv)
ABS_LINT_CSV := $(addprefix $(LINT_DIR)/, $(LINT_CSV))

export LINT_CSV
export ABS_LINT_CSV

#
# Adjust to prevent target collision.
#
SUB_COMP_PF := &

ENT_SUB_COMP     := $(addprefix $(SUB_COMP_PF), $(SUB_COMPONENTS))
ENT_OPT_SUB_COMP := $(addprefix $(SUB_COMP_PF), $(OPTIONAL_SUB_COMPONENTS) $(SEL_SUB_COMPONENTS))


#
# Set LEVEL_TOP
#
ifndef LEVEL_TOP
LEVEL_TOP := TRUE
endif

.PHONY : all custom lib depend c_inc sub_comp lint clean clean_custom clean_o clean_d clean_lib clean_lint clean_c clean_force $(SUB_COMP) $(ENT_SUB_COMP) $(ENT_OPT_SUB_COMP)


all custom lib depend :
ifeq "$(FAST_SUPPORT)" "false"
	@echo "*******************************************************************"
	@echo "* Goal           : $(MAKECMDGOAL)"
	@echo "* Customer       : $(CUSTOMER)"
	@echo "* Build name     : $(BUILD_NAME)"
	@echo "* Version        : $(VERSION)"
	@echo "* Path           : $(THIS_PATH)"
	@echo "* Component      : $(THIS_COMPONENT)"
	@echo "* Target         : $(TARGET_ROOT)"
	@echo "* DEFINES        : $(sort $(DEFINES))"
	@echo "* NO_SUB_COMP    : $(NO_SUB_COMP)"
	@echo "* NO_OPT_SUB_COMP: $(NO_OPT_SUB_COMP)"
	@echo "*******************************************************************"
endif
	@$(RM) $(RM_FLAG) $(SRC:.c=.o) $(SRC_CPP:.cpp=.o)
ifeq "$(LEVEL_TOP)" "TRUE"
ifeq "$(FAST_SUPPORT)" "false"
	$(call if_dir_exist_fct,$(call path_cnvt,$(CUSTOM_LIB_DIR)), find $(call path_cnvt,$(CUSTOM_LIB_DIR))/ -name *.lock -exec $(RM) $(RM_REC_FLAG) {} \;;)
endif
endif
	@$(MAKE) -f $(CUSTOM_ROOT)/all.mak $@ SUB_COMP= LEVEL_TOP=FALSE --no-print-directory


c_inc :
	@$(MAKE) -C $(MW_ROOT) $@


sub_comp : $(SUB_COMP) $(word 1, $(SUB_COMP_LIST))
ifeq ($(SUB_COMP),)
ifeq ($(SUB_COMP_LIST),)
ifeq "$(FAST_SUPPORT)" "false"
	@echo "*******************************************************************"
	@echo "* Goal           : $(MAKECMDGOAL)"
	@echo "* Customer       : $(CUSTOMER)"
	@echo "* Build name     : $(BUILD_NAME)"
	@echo "* Version        : $(VERSION)"
	@echo "* Path           : $(THIS_PATH)"
	@echo "* Component      : $(THIS_COMPONENT)"
	@echo "* Target         : $(TARGET_ROOT)"
	@echo "* DEFINES        : $(sort $(DEFINES))"
	@echo "* NO_SUB_COMP    : $(NO_SUB_COMP)"
	@echo "* NO_OPT_SUB_COMP: $(NO_OPT_SUB_COMP)"
	@echo "*******************************************************************"
endif
	@$(MAKE) -f $(CUSTOM_ROOT)/all.mak all SUB_COMP=
endif
endif


lint :
	@echo "*******************************************************************"
	@echo "* Goal     : $(MAKECMDGOAL)"
	@echo "* Path     : $(THIS_PATH)"
	@echo "* Component: $(THIS_COMPONENT)"
	@echo "* DEFINES  : $(sort $(DEFINES))"
	@echo "*******************************************************************"
	@$(MAKE) -s -f $(CUSTOM_ROOT)/lint.mak $@ SUB_COMP=


clean clean_custom clean_o clean_d clean_lib clean_lint clean_force :
	@$(MAKE) -s -i -f $(CUSTOM_ROOT)/clean.mak $@ SUB_COMP=


clean_c :
	@$(MAKE) -s -i -C $(MW_ROOT) $@


#
# Cycle through all sub-components
#
$(SUB_COMP) :
	@$(MAKE) $(MAKECMDGOALS) SUB_COMP= SUB_COMP_LIST="$(addprefix $(SUB_COMP_PF),$(subst /, , $@))"


$(ENT_SUB_COMP) :
	@$(MAKE) -C $(subst $(SUB_COMP_PF),,$@) $(MAKECMDGOALS) ENTER_OPT_SUB_COMP=FALSE SUB_COMP= SUB_COMP_LIST="$(wordlist 2, $(words $(SUB_COMP_LIST)), $(SUB_COMP_LIST))"


$(ENT_OPT_SUB_COMP) :
	@$(MAKE) -C $(subst $(SUB_COMP_PF),,$@) $(MAKECMDGOALS) ENTER_OPT_SUB_COMP=TRUE SUB_COMP= SUB_COMP_LIST="$(wordlist 2, $(words $(SUB_COMP_LIST)), $(SUB_COMP_LIST))"


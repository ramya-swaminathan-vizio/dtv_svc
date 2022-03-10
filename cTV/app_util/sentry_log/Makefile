###########################################################################
# $RCSfile: Makefile,v $
# $Revision: #1 $
# $Date: 2021/12/27 $
# $Author: maksym.shestirko $
#
# Description:
#         Leave-level makefile to build sentry logger subcomponent of dtv_svc.
#
#         Specify the source files to be compile in SRC.
#############################################################################

ifndef PROJECT_ROOT
PROJECT_ROOT := $(word 1, $(subst /project_x/,/project_x /, $(shell pwd)))
endif

THIS_COMPONENT = vizio_sentry_log

SRC = sentry_log.c

OBJ =

SUB_COMPONENTS =

OPTIONAL_SUB_COMPONENTS =

#############################################################################
#
# Include the makefile common to all components
#
include $(CUSTOM_ROOT)/common.mak

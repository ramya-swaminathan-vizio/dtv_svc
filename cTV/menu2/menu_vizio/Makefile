###########################################################################
# $RCSfile: Makefile,v $
# $Revision: #1 $
# $Date: 2021/05/16 $
# $Author: maksym.shestirko $
#
# Description:
#         Leave-level makefile to build VIZIO menu subcomponent dtv_svc.
#
#         Specify the source files to be compile in SRC.
#############################################################################

ifndef PROJECT_ROOT
PROJECT_ROOT := $(word 1, $(subst /project_x/,/project_x /, $(shell pwd)))
endif



THIS_COMPONENT = menu_vizio


SRC = menu_page_bt_devices.c               \
      menu_page_bt_more_other_devices.c    \
      menu_page_bt_forget_paired_devices.c \
      menu_page_bt_json_db.c               \
      vzlogger.c

OBJ =

SUB_COMPONENTS = 

OPTIONAL_SUB_COMPONENTS = 

ifdef PSEUDO_GL
DEFINES += -DPSEUDO_GL
endif

ifdef MEM_MONITORING
DEFINES += -DMEM_MONITORING
endif

ifdef DEBUGING
DEFINES += -DDEBUGING
endif

CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/rpc/rpc_core/rpc_ipc  \
          -I$(VM_LINUX_ROOT)/linux_mts/rpc/rpc_core \
          -I$(PROJECT_ROOT)/middleware/open/playback/inet/wifi \
          -I$(PROJECT_ROOT)/middleware/open  \
          -I$(PROJECT_ROOT)/middleware/open/extern_if/common  \
          -I$(PROJECT_ROOT)/middleware/open/playback  \
          -I$(PROJECT_ROOT)/middleware/open/playback/cmpb  \
          -I$(PROJECT_ROOT)/middleware/open/extern_if/playback/cmpb  \
          -I$(PROJECT_ROOT)/middleware/open/extern_if/playback  \
          -I$(PROJECT_ROOT)/middleware/open/extern_if/broadcast  \
          -I$(PROJECT_ROOT)/middleware/open/playback/inet/vudu \
          -I$(PROJECT_ROOT)/middleware/open/mutil/sbtl_engine/sbtl_cc \
          -I$(PROJECT_ROOT)/middleware/open/mutil/sbtl_engine/sbtl_dync \
          -I$(PROJECT_ROOT)/middleware/open/mutil/sbtl_engine/sbtl_cc
              
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/open/misc/direct_api \
            -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/public/res_mngr/drv \
            -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/public/hash   \
            -I$(VM_LINUX_ROOT)/linux_core/app_if/mtal/mtal_inc/adaption

CC_INC += -I$(X_INC_DIR)
CC_INC += -I$(RPC_DESC_FILE_DIR)

CC_INC += -I$(VM_LINUX_ROOT)/oss/source/cJSON/1.7.7
CC_INC += -I$(VM_LINUX_ROOT)/linux_mts/mtk_util/source/open/misc/wifi_rc_control/wfrrc_interface/include
CC_INC += -I$(VM_LINUX_ROOT)/custom/dev
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV/menu2
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV/menu2/menu_common
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV/app_util
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV/res/menu2
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV/res/app_util/dev_db
CC_INC += -I$(VM_LINUX_ROOT)/custom/Vizio/cTV/nav
CC_INC += -I $(WFD_INC_DIR)

#############################################################################
#
# Include the makefile common to all components
# 
include $(CUSTOM_ROOT)/common.mak

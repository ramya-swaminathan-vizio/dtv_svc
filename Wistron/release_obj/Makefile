ifndef PROJECT_ROOT
PROJECT_ROOT := $(word 1, $(subst /project_x/,/project_x /, $(shell pwd)))
$(warning PROJECT_ROOT $(PROJECT_ROOT))
endif

THIS_COMPONENT = release_obj

SRC =

OBJ = acfg_cust_factory.o \
	  acfg_cust_odm.o \
	  acfg_cust_plf_opt.o \
	  acfg_cust_pre_ch.o \
	  a_factory_wst.o \
	  a_fact_parser_wst.o \
	  a_gluelayer_wst.o \
	  a_gluelayer_wst_tbl.o \
	  a_nav_factory_menu_wst.o \
	  burning_mode.o \
	  burning_mode_view.o \
	  cvte_factory_api.o \
	  fac_msg.o \
	  mapp_cvte_cmdtool.o \
	  mapp_cvte_fatcmdaction.o \
	  mapp_cvte_usartlib.o \
	  menu_cust_fac_wst.o \
	  menu_cust_hierarchy_wst.o \
	  menu_page_ver_info_wst.o \
	  nav_variant_custom.o \
	  wis_factory_handler.o \
	  wis_factory_parser.o \
	  wistron_factory_api.o

$(warning wst THIS_COMPONENT $(THIS_COMPONENT))
$(warning wst TOOL_CHAIN $(TOOL_CHAIN))
$(warning wst OBJ $(OBJ))

SUB_COMPONENTS =

CC_INC +=

#############################################################################
#
# Include the makefile common to all components
#
include $(CUSTOM_ROOT)/common.mak


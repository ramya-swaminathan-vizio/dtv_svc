#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_dbg.h"

#include "amb/a_amb.h"

#include "c_os.h"

#include "a_gluelayer_comm.h"
#include "gluelayer_tbl.h"

#include "fac_shell_dbg.h"

#undef DBG_MODULE_NAME_PREFIX
#define DBG_MODULE_NAME_PREFIX          "<gluelayer>"

#define LOAD_SO_NAME_AMT        "/basic/libfactory1.so"
#define LOAD_SO_NAME_TPV        "/basic/libfactory2.so"
#define LOAD_SO_NAME_WST        "/basic/libfactory3.so"
#define LOAD_SO_NAME_FXC        "/basic/libfactory4.so"
#define LOAD_SO_NAME_BOE        "/basic/libfactory5.so"
#define LOAD_SO_NAME_INNOLUX    "/basic/libfactory6.so"
#define LOAD_SO_NAME_KONKA      "/basic/libfactory7.so"

static BOOL b_print_log = FALSE;
static void *dl_handle = NULL;

UINT32 m_aui4_fac_trigger_key[4] = {0};

INT32 (*pfn_gluelayer_do_cmd)(UINT32 ui4_cmd, void *pv_data);

static INT32 _get_odm_idx(UINT8 *pui1_odm_idx)
{
    INT32                       i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    UINT8                       ui1_val = 0;
    SIZE_T                      z_size = sizeof(UINT8);

    if (NULL == pui1_odm_idx)
    {
        return GLUELR_FAIL;
    }

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_ODM_INDEX;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("!!!!%s Get Fail i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    *pui1_odm_idx = ui1_val;

    return GLUELR_OK;
}
static UINT8 i_get_odm_index(void)
{
    UINT8 i1_odm = 2;  //default load factory2.so
    UINT8 ui1_odm_idx = 0;

    if (_get_odm_idx(&ui1_odm_idx) == GLUELR_OK
        && ui1_odm_idx != 0)
    {
        i1_odm = ui1_odm_idx;
    }

  //  DBG_INFO(("_get_odm_index() i1_odm=%d \n",i1_odm));
    return i1_odm;
}

static INT32 _get_modelgroup_idx(UINT16 *pui2_modelgroup_idx)
{
    INT32                       i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    UINT16                      ui2_val = 0;
    SIZE_T                      z_size = sizeof(UINT16);

    if (NULL == pui2_modelgroup_idx)
    {
        return GLUELR_FAIL;
    }

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_MODEL_GROUP;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui2_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("!!!!%s Get Fail i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    *pui2_modelgroup_idx = ui2_val;

    return GLUELR_OK;
}

static UINT16 i_get_ModelGroup_index(void)
{
    UINT16 i2_modelgroup = 0;
    UINT16 ui2_modelgroup_idx = 0;

    if (_get_modelgroup_idx(&ui2_modelgroup_idx) == GLUELR_OK && ui2_modelgroup_idx != 0)
    {
        i2_modelgroup = ui2_modelgroup_idx;
    }

   // DBG_INFO(("i_get_ModelGroup_index() i2_modelgroup=0x%x \n",i2_modelgroup));
    return i2_modelgroup;
}

static INT32 _get_model_idx(UINT32 *pui4_model_idx)
{
    INT32                       i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    UINT32                      ui4_val = 0;
    SIZE_T                      z_size = sizeof(UINT32);

    if (NULL == pui4_model_idx)
    {
        return GLUELR_FAIL;
    }

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
	//	 t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_MODEL_INDEX;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_GetModelIndexID;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("!!!!%s Get Fail i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    *pui4_model_idx = ui4_val;

    return GLUELR_OK;
}

static UINT32 i_get_Model_index(void)
{
    UINT32 i4_model = 0;
    UINT32 ui4_model_idx = 0;

    if (_get_model_idx(&ui4_model_idx) == GLUELR_OK && ui4_model_idx != 0)
    {
        i4_model = ui4_model_idx;
    }

   // DBG_INFO(("i_get_Model_index() i4_model=%d \n",i4_model));
    return i4_model;
}

static INT32 _get_so_name(char *s_so_name)
{
    INT32   i4_ret = 0;
    UINT8   ui1_odmid = 0;
    UINT16  ui2_modelgroupidx = 0;
    UINT32  ui4_modelidx = 0;

    ui1_odmid = i_get_odm_index();
    ui2_modelgroupidx = i_get_ModelGroup_index();
    ui4_modelidx = i_get_Model_index();
    DBG_ERROR(("\n Platform information: _get_so_name(),odmid=0x%x modelgroupid=0x%x modelid=0x%x \n",ui1_odmid,ui2_modelgroupidx,ui4_modelidx));

    switch (ui1_odmid)
    {
        case 1:
            c_strcpy(s_so_name, LOAD_SO_NAME_AMT);
            break;
        case 2:
            c_strcpy(s_so_name, LOAD_SO_NAME_TPV);
            break;
        case 3:
            c_strcpy(s_so_name, LOAD_SO_NAME_WST);
            break;
        case 4:
            c_strcpy(s_so_name, LOAD_SO_NAME_FXC);
            break;
        case 5:
            c_strcpy(s_so_name, LOAD_SO_NAME_BOE);
            break;
        case 6:
            c_strcpy(s_so_name, LOAD_SO_NAME_INNOLUX);
            break;
        case 7:
            c_strcpy(s_so_name, LOAD_SO_NAME_KONKA);
            break;

        default:
            c_strcpy(s_so_name, LOAD_SO_NAME_TPV);
            break;
    }

    if(0 != access(s_so_name, R_OK)){
        DBG_ERROR(("%s not exist, load %s as default\n\n", s_so_name, LOAD_SO_NAME_TPV));
        c_strcpy(s_so_name, LOAD_SO_NAME_TPV);
    }
    return i4_ret;
}

void* a_gluelayer_get_factory_func_symbol(const char *ps_fct_name)
{
    char ac_so_name[256] = {0};
	void *pfn = NULL;

    if (NULL == ps_fct_name
        || c_strlen(ps_fct_name) == 0)
    {
        return NULL;
    }

    _get_so_name(ac_so_name);

    if (NULL == dl_handle)
    {
        dl_handle = dlopen(ac_so_name, RTLD_NOW|RTLD_LOCAL);
        if (NULL == dl_handle)
        {
    		DBG_ERROR(("\ndlopen err:%s\n", dlerror()));
            return NULL;
        }
    }

    pfn = dlsym(dl_handle, ps_fct_name);
    if (NULL == pfn)
    {
        DBG_ERROR(("\nGet ULI symbol address fail(%s)!!\n\n", dlerror()));
    }
	return pfn;
}

VOID* a_gluelayer_get_so_handle(VOID)
{
    return dl_handle;
}

INT32 a_gluelayer_get_so_name(CHAR *ps_so_name)
{
    if (NULL == ps_so_name) return -1;

    return _get_so_name(ps_so_name);
}

INT32 a_gluelayer_init(void)
{
    INT32   i4_ret = 0;
    UINT32  ui4_i = 0;
    UINT8   ui1_odmid = 0;
    char *error = NULL;
    char ac_so_name[256] = {0};

    fac_shell_attach_cmd_tbl();

    //system("cat /proc/`ps -w -u root|grep dtv_svc|awk -F' ' '{print $1}'`/maps");
    ui2_fac_shell_dbg_lvl = dbg_get_log_level_from_file("fac_shell", "/data/loglevel.txt");
    _get_so_name(ac_so_name);

    DBG_INFO(("\n========= dlopen :%s ========\n", ac_so_name));
    dl_handle = dlopen(ac_so_name, RTLD_NOW|RTLD_LOCAL);
    if (NULL == dl_handle)
    {
        DBG_ERROR(("\ndlopen err:%s\n", dlerror()));
        return -1;
    }

    pfn_gluelayer_do_cmd = dlsym(dl_handle,"a_gluelayer_do_cmd");
    error = dlerror();
    if (NULL == pfn_gluelayer_do_cmd || error != NULL )
    {
        DBG_ERROR(("\nERROR:get symbol address from %s fail(%s)!!\n\n",
                                                ac_so_name,
                                                error));
        return -1;
    }

    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_M_END; ui4_i++)
    {
        if (at_mac_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_INFO(("%s() %d: end ui4_i = %u =====\n", __FUNCTION__, __LINE__, ui4_i));
            break;
        }

        i4_ret = pfn_gluelayer_do_cmd(GLUELAYER_CMD_MAK(GLUELAYER_CMD_GRP_MACRO, at_mac_cmd_map[ui4_i].ui4_cmd),
                                    at_mac_cmd_map[ui4_i].pv_data);
        if (b_print_log)
        {
            DBG_INFO(("<FAC SHELL> Gluelayer(ret=%d): name[%s] \tValue[0x%x] \tcmd=[%d]\r\n",
                                                    i4_ret,
                                                    at_mac_cmd_map[ui4_i].s_name,
                                                    *((INT32*)at_mac_cmd_map[ui4_i].pv_data),
                                                    at_mac_cmd_map[ui4_i].ui4_cmd));
        }
    }

    ui1_odmid = i_get_odm_index();
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_A_END; ui4_i++)
    {
        if (at_api_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_INFO(("%s() %d: end ui4_i = %u =====\n", __FUNCTION__, __LINE__, ui4_i));
            break;
        }

        if ( 2 != ui1_odmid ) // only tpv has this api
        {
            if (at_api_cmd_map[ui4_i].ui4_cmd == GLUELAYER_CMD_A_HDR_PANEL_NITS)
            {
                DBG_LOG_PRINT(("%s() %d: GLUELAYER_CMD_A_HDR_PANEL_NITS \r\n", __FUNCTION__, __LINE__));
                continue;
            }
        }

        i4_ret = pfn_gluelayer_do_cmd(GLUELAYER_CMD_MAK(GLUELAYER_CMD_GRP_API, at_api_cmd_map[ui4_i].ui4_cmd),
                                    at_api_cmd_map[ui4_i].pv_data);
        if (b_print_log)
        {
            DBG_INFO(("<FAC SHELL> Gluelayer(ret=%d): name[%s] \tAddr[0x%x] \tcmd=[%d]\r\n",
                                                i4_ret,
                                                at_api_cmd_map[ui4_i].s_name,
                                                (*((UINT32*)at_api_cmd_map[ui4_i].pv_data)),
                                                at_api_cmd_map[ui4_i].ui4_cmd));
        }
    }

    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_S_END; ui4_i++)
    {
        if (at_stru_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_INFO(("%s() %d: end ui4_i = %u =====\n", __FUNCTION__, __LINE__, ui4_i));
            break;
        }
        i4_ret = pfn_gluelayer_do_cmd(GLUELAYER_CMD_MAK(GLUELAYER_CMD_GRP_STRUCT, at_stru_cmd_map[ui4_i].ui4_cmd),
                                    at_stru_cmd_map[ui4_i].pv_data);
        if (b_print_log)
        {
            DBG_INFO(("<FAC SHELL> Gluelayer(ret=%d): name[%s] \tAddr[0x%x] \tcmd=[%d]\r\n",
                                                    i4_ret,
                                                    at_stru_cmd_map[ui4_i].s_name,
                                                    at_stru_cmd_map[ui4_i].pv_data,
                                                    at_stru_cmd_map[ui4_i].ui4_cmd));
        }
    }

    return GLUELR_OK;
}

INT32 a_gluelayer_update_default_pq_tbl(VOID)
{
    UINT32      ui4_i = 0;
    INT32       i4_ret = GLUELR_OK;

    if (NULL == pfn_gluelayer_do_cmd)
    {
        DBG_INFO(("<FAC SHELL> pfn_gluelayer_do_cmd is NULL\n"));
        return GLUELR_OK;
    }

    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_S_HDR_HLG_PQ_DFT_TBL; ui4_i++)
    {
        if (at_stru_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_INFO(("%s() %d: end ui4_i = %u =====\n", __FUNCTION__, __LINE__, ui4_i));
            break;
        }

        if (GLUELAYER_CMD_S_PQ_DFT_TBL != at_stru_cmd_map[ui4_i].ui4_cmd
            && GLUELAYER_CMD_S_PRO_PQ_DFT_TBL != at_stru_cmd_map[ui4_i].ui4_cmd)
        {
            continue;
        }
        i4_ret = pfn_gluelayer_do_cmd(GLUELAYER_CMD_MAK(GLUELAYER_CMD_GRP_STRUCT, at_stru_cmd_map[ui4_i].ui4_cmd),
                                    at_stru_cmd_map[ui4_i].pv_data);
        if (b_print_log)
        {
            DBG_INFO(("<FAC SHELL> Gluelayer(ret=%d): name[%s] \tAddr[0x%x] \tcmd=[%d]\r\n",
                                                    i4_ret,
                                                    at_stru_cmd_map[ui4_i].s_name,
                                                    at_stru_cmd_map[ui4_i].pv_data,
                                                    at_stru_cmd_map[ui4_i].ui4_cmd));
        }
    }

    return GLUELR_OK;
}

INT32 a_gluelayer_get_new_table_default_pq_tbl(VOID)  // HDR HLG dobly version
{
    UINT32      ui4_i = 0;
    INT32       i4_ret = GLUELR_OK;

    if (NULL == pfn_gluelayer_do_cmd)
    {
        DBG_INFO(("<FAC SHELL> pfn_gluelayer_do_cmd is NULL\n"));
        return GLUELR_OK;
    }

    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_S_END; ui4_i++)
    {
        if (at_stru_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_INFO(("%s() %d: end ui4_i = %u =====\n", __FUNCTION__, __LINE__, ui4_i));
            break;
        }

        if (GLUELAYER_CMD_S_HDR_HLG_PQ_DFT_TBL != at_stru_cmd_map[ui4_i].ui4_cmd
            && GLUELAYER_CMD_S_DOBLY_VERSION_PQ_DFT_TBL != at_stru_cmd_map[ui4_i].ui4_cmd
            && GLUELAYER_CMD_S_HLG_PQ_DFT_TBL != at_stru_cmd_map[ui4_i].ui4_cmd)//Innolux truedano add : add it will overwrite HLG ODM default value
        {
            continue;
        }
        i4_ret = pfn_gluelayer_do_cmd(GLUELAYER_CMD_MAK(GLUELAYER_CMD_GRP_STRUCT, at_stru_cmd_map[ui4_i].ui4_cmd),
                                    at_stru_cmd_map[ui4_i].pv_data);
        if (b_print_log)
        {
            DBG_INFO(("<FAC SHELL> Gluelayer(ret=%d): name[%s] \tAddr[0x%x] \tcmd=[%d]\r\n",
                                                    i4_ret,
                                                    at_stru_cmd_map[ui4_i].s_name,
                                                    at_stru_cmd_map[ui4_i].pv_data,
                                                    at_stru_cmd_map[ui4_i].ui4_cmd));
        }
    }

    return GLUELR_OK;
}


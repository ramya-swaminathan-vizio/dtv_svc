#include "u_common.h"
#include "c_os.h"
#include "c_cli.h"
#include "c_handle.h"
#include "c_cfg.h"
#include "c_dbg.h"

#include "res/app_util/config/acfg_cust_video.h"

#include "a_gluelayer_comm.h"
#include "gluelayer_srv_tbl.h"
#include "fac_shell_cli/fac_shell_dbg.h"

extern T_CMD_DATA_MAP_M at_m_cmd_map[];
extern T_CMD_DATA_MAP_A at_a_cmd_map[];
extern T_CMD_DATA_MAP_S at_s_cmd_map[];

static INT32 _gluelayer_macro_cmd_handle(UINT32 ui4_cmd, void *pv_data);
static INT32 _gluelayer_api_cmd_handle(UINT32 ui4_cmd, void **pv_data);
static INT32 _gluelayer_struct_cmd_handle(UINT32 ui4_cmd, void *pv_data);

__attribute__ ((visibility("default"))) INT32 a_gluelayer_do_cmd(UINT32 ui4_cmd, void *pv_data)
{
    INT32 i4_ret = GLUELR_OK;
    UINT8 ui1_cmd_grp = GLUELAYER_CMD_GET_GRP_ID(ui4_cmd);
    
    if (ui4_cmd < 1 || NULL == pv_data)
    {
        return GLUELR_INV_ARG;
    }
    
    switch (ui1_cmd_grp)
    {
        case GLUELAYER_CMD_GRP_MACRO:
        {
            _gluelayer_macro_cmd_handle(ui4_cmd, pv_data);
            break;
        }
        case GLUELAYER_CMD_GRP_API:
        {
            _gluelayer_api_cmd_handle(ui4_cmd, pv_data);
            break;
        }
        case GLUELAYER_CMD_GRP_STRUCT:
        {
            _gluelayer_struct_cmd_handle(ui4_cmd, pv_data);
            break;
        }
    }
    
    return i4_ret;
}

static INT32 _gluelayer_macro_cmd_handle(UINT32 ui4_cmd, void *pv_data)
{
    INT32   i4_ret = GLUELR_OK;
    UINT32  ui4_i = 1;
    BOOL    b_found = FALSE;
    
    UINT32 ui4_fac_cmd = (UINT32)GLUELAYER_CMD_GET_CMD_ID(ui4_cmd);
    
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_M_END; ui4_i++)
    {
        if (0 == at_m_cmd_map[ui4_i].ui4_cmd)
        {
            break;
        }
        
        if (ui4_fac_cmd == at_m_cmd_map[ui4_i].ui4_cmd)
        {
            b_found = TRUE;
            *((INT32*)pv_data) = at_m_cmd_map[ui4_i].i4_val;
            break;
        }
    }
    
    if (!b_found)
    {
        i4_ret = GLUELR_NO_DATA;
    }
    
    return i4_ret;
}

static INT32 _gluelayer_api_cmd_handle(UINT32 ui4_cmd, void **pv_data)
{
    INT32   i4_ret = GLUELR_OK;
    UINT32  ui4_i = 1;
    BOOL    b_found = FALSE;
    
    UINT32 ui4_fac_cmd = (UINT32)GLUELAYER_CMD_GET_CMD_ID(ui4_cmd);
    
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_A_END; ui4_i++)
    {
        if (0 == at_a_cmd_map[ui4_i].ui4_cmd)
        {
            break;
        }
        
        if (ui4_fac_cmd == at_a_cmd_map[ui4_i].ui4_cmd)
        {
            b_found = TRUE;
            *pv_data = (void *)(at_a_cmd_map[ui4_i].pv_data);
            DBG_INFO(("%s() %d: %d/%d, parse cmd=%d, api_addr=0x%x\n", __FUNCTION__, __LINE__,
                                                        ui4_i,GLUELAYER_CMD_A_END,
                                                        ui4_fac_cmd,
                                                        *pv_data));
            break;
        }
    }
    
    if (!b_found)
    {
        i4_ret = GLUELR_NO_DATA;
    }
    
    return i4_ret;
}

static INT32 _gluelayer_struct_cmd_handle(UINT32 ui4_cmd, VOID *pv_data)
{
    INT32   i4_ret = GLUELR_OK;
    UINT32  ui4_i = 1;
    BOOL    b_found = FALSE;
    
    UINT32 ui4_fac_cmd = (UINT32)GLUELAYER_CMD_GET_CMD_ID(ui4_cmd);
    
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_S_END; ui4_i++)
    {
        if (0 == at_s_cmd_map[ui4_i].ui4_cmd)
        {
            break;
        }
        
        if (ui4_fac_cmd == at_s_cmd_map[ui4_i].ui4_cmd)
        {
            b_found = TRUE;
            break;
        }
    }
    
    if (!b_found)
    {
        return GLUELR_NO_DATA;
    }
    
    switch (ui4_fac_cmd)
    {
        case GLUELAYER_CMD_S_M_AUI4_FAC_TRIGGER_KEY:
        {
            c_memcpy((char*)pv_data, (char *)(at_s_cmd_map[ui4_i].pv_mem), at_s_cmd_map[ui4_i].z_size);
            break;
        }
        case GLUELAYER_CMD_S_PQ_DFT_TBL:
        case GLUELAYER_CMD_S_PRO_PQ_DFT_TBL:
        /* yshu add HDR HLG Table 20180614 */
        case GLUELAYER_CMD_S_HDR_HLG_PQ_DFT_TBL:
        case GLUELAYER_CMD_S_DOBLY_VERSION_PQ_DFT_TBL:
        case GLUELAYER_CMD_S_HLG_PQ_DFT_TBL:
        {
            UINT16 ui2_idx = 0;
            UINT16 ui2_num = (ui4_fac_cmd == GLUELAYER_CMD_S_PQ_DFT_TBL) 
                                ? ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM 
                                : ACFG_CUST_VIDEO_PRO_PQ_DFT_TBL_MAX_NUM;

            DBG_INFO(("%s() %d: ui4_i=%d,parse cmd=%d, ui2_num=%d\n", __FUNCTION__, __LINE__,
                                                        ui4_i,
                                                        ui4_fac_cmd,
                                                        ui2_num));
            for (ui2_idx = 0; ui2_idx < ui2_num; ui2_idx++)
            {
                ((APP_CFG_CUSTOM_PQ_TBL_T*)pv_data)[ui2_idx].e_pic_mode = ACFG_CUST_PIC_MODE_LAST_ENTRY;
            }
            DBG_INFO(("%s() %d: parse cmd=%d, ui2_idx=%d\n", __FUNCTION__, __LINE__,
                                                        ui4_fac_cmd,
                                                        ui2_idx));
            c_memcpy((char*)pv_data, (char *)(at_s_cmd_map[ui4_i].pv_mem), at_s_cmd_map[ui4_i].z_size);
            DBG_INFO(("%s() %d: parse cmd=%d, z_size=%d\n", __FUNCTION__, __LINE__,
                                                        ui4_fac_cmd,
                                                        at_s_cmd_map[ui4_i].z_size));
            break;
        }
        default:
            i4_ret = GLUELR_NO_DATA;
            break;
    }
    
    return i4_ret;
}


#ifndef _COLOR_TUNER_V2_H_
#define _COLOR_TUNER_V2_H_

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R             0
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G             1
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B             2
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C             3
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M             4
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y             5

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R             6
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G             7
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B             8
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C             9
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M             10
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y             11

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R             12
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G             13
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B             14
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C             15
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M             16
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y             17

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET          18
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET          19
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET          20

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN            21
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN            22
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN            23
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R        24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G        44
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B        64
#define COLOR_TUNER_FAC_TEMP_NUM 3
#define COLOR_TUNER_FAC_PLAY_CONTENT_NUM 4
#define COLOR_TUNER_FAC_PIECE_NUM 84


#define COLOR_TUNER_FAC_20POINT_NUM                     20
#define _cvt_fac_20_POINT_GAIN_COL_RED                      ((UINT8)1)
#define _cvt_fac_20_POINT_GAIN_COL_GREEN                    ((UINT8)2)
#define _cvt_fac_20_POINT_GAIN_COL_BLUE                     ((UINT8)3)
extern const UINT8 ui1_cvt_color_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM];
typedef struct
{
    UINT16 ui2_cfg_rec;
    INT16* pi2_val;
    UINT32 ui4_dynamic_address;
    INT16 i2_clr_temp;
    UINT8 ui1_play_content;
}clr_reccid_data;
#endif
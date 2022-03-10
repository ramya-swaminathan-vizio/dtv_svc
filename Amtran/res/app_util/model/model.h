#ifndef _MODEL_H_
#define _MODEL_H_

#define MODEL_NAME_WITH_LD  {\
                                "M321i-A2",\
                                "M471i-A2",\
                                "M501d-A2R",\
                                "M551d-A2",\
                                "M551d-A2R",\
                                "M401i-A3",\
                                "M601d-A3",\
                                "M601d-A3R",\
                                "M701d-A3",\
                                "M701d-A3R",\
                                "M801d-A3",\
                                "M801d-A3R"\
                            }
#ifdef APP_EMANUAL_SUPPORT
extern VOID a_start_user_manual_by_model(VOID);
#endif
#ifdef APP_RETAIL_MODE_SUPPORT
extern VOID a_start_retail_demo_by_model(VOID);
#endif

extern UINT8 a_get_usb_port_num_by_model(VOID);
extern BOOL a_is_DLNA_enable(VOID);

#endif /* _MODEL_H_ */


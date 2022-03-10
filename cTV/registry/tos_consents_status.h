
#ifndef TOS_CONSENTS_STATUS_H
#define TOS_CONSENTS_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif
extern const char* VIZIO_TOS_URL;
extern const char* GOOGLE_TOS_URL;
extern const char* VIEWING_DATA_URL;


extern int getTosbyUrl(bool *b_appept,const char* url);


#ifdef __cplusplus
}
#endif

#endif // TOS_CONSENTS_STATUS_H



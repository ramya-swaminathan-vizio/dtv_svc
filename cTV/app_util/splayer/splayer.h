/*
 * =====================================================================================
 *
 *       Filename:  splayer.h
 *
 *    Description:  This class is used for playing media
 *                  This class is just a simply wrap for CMPB and MPOPlayer
 *                  We could only play one a/v(audio, video) and one photo simultaneously
 *
 *        Version:  1.0
 *        Created:  05/06/2013 11:25:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xieminchen (mtk), hs_xieminchen@mediatek.com
 *        Company:  Mediatek
 *
 * =====================================================================================
 */

#ifndef _APPL_SPLAYER_H_
#define _APPL_SPLAYER_H_

#include "u_common.h"
#ifdef NEVER
#include "cmpb/IMtkPb_ErrorCode.h"
#include "cmpb/IMtkPb_Ctrl.h"
#include "cmpb/IMtkPb_Ctrl_DTV.h"
#include "cmpb/IMtkPb_Comm.h"
#endif /* NEVER */
#include "c_dbg.h"
#include "u_dbg.h"
#ifdef CLI_SUPPORT
#include "res/app_util/config/acfg_cust_cli.h"
#endif
#include "c_wgl_image.h"
#include "u_wgl.h"
#include "u_wgl_image.h"

#define APPL_SPLAYER_SUCCESS 0
#define APPL_SPLAYER_FAILED -1
#define APPL_SPLAYER_FILE_FORMAT_NOT_SUPPORT -2
// this means that somebody has already played the same type
#define APPL_SPLAYER_PLAYED_ALREADY -3
#define APPL_SPLAYER_FILE_NOT_EXIST -4
#define APPL_SPLAYER_FILE_NOT_SUPPORT -5
#define APPL_SPLAYER_SYS_ERROR -6
#define APPL_SPLAYER_PLAY_FAILED -7


#define MI_MM_SUPPORT

#define APPL_SPLAYER_MAKE_BIT(_val) (((UINT32) 1) << (_val))
// freeze last frame when end of video playing
#define APPL_SPLAYER_PLAY_MODE_LAST_FREEZE APPL_SPLAYER_MAKE_BIT(0)

#ifdef CLI_SUPPORT
#define SPLAYER_DBG_PRINT(fmt, ...) \
    if(a_cfg_get_splayer_dl() >= 0) \
            DBG_LOG_PRINT( ("<%s:%4d> " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))    /**<        */

#define SPLAYER_DBG_INFO(fmt, ...) \
        if(a_cfg_get_splayer_dl() >= 1) \
                DBG_LOG_PRINT( ("<%s:%4d> " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))    /**<        */

#define SPLAYER_DBG_ERROR(fmt, ...) \
                if(a_cfg_get_splayer_dl() >= 0) \
                        DBG_LOG_PRINT( (" Err : <%s:%4d> " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))    /**<        */

#else
#define SPLAYER_DBG_PRINT(fmt, ...)
#define SPLAYER_DBG_INFO(fmt, ...)
#define SPLAYER_DBG_ERROR(fmt)
#endif

#define SPLAYER_LOG_ON_FAIL(_ret)                                             \
if (_ret < 0)                                                                 \
{                                                                             \
    DBG_LOG_PRINT((" Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
}

typedef struct APPL_SPLAYER_T *P_APPL_SPLAYER_T;

#define AUDIO_CODEC_LEN   24

//#define MAX_METADATA_STRING_LENGTH  (128)
#define MAX_METADATA_STRING_LENGTH  (256)

#define USB_PATH_MAX_LENGTH         256
#define YEAR_LENGTH                 32

#define MUSIC_RC_COV_PIC_W          176
#define MUSIC_RC_COV_PIC_H          192

typedef signed int                                      MI_S32;     ///< 4 bytes
typedef MI_S32                                          MI_HANDLE;
typedef unsigned long long                              MI_U64;     ///< 8 bytes
typedef unsigned int                                    MI_U32;     ///< 4 bytes

typedef struct _APPL_SPLAYER_MUSIC_INFO_T
{
    UINT32  ui4_total_time;
    CHAR    szYear[YEAR_LENGTH];
    CHAR    szFileName[USB_PATH_MAX_LENGTH];
    CHAR    szFileLocation[USB_PATH_MAX_LENGTH];
    CHAR    szMetadataTitle [MAX_METADATA_STRING_LENGTH];
    CHAR    szMetadataArtist[MAX_METADATA_STRING_LENGTH];
    CHAR    szMetadataGenre [MAX_METADATA_STRING_LENGTH];
    CHAR    szMetadataAlbum [MAX_METADATA_STRING_LENGTH];
    BOOL    b_pic_exist;
    UINT32  u32PictureSize;
    WGL_IMG_T t_img;
    WGL_HIMG_TPL_T h_cover_img;
} APPL_SPLAYER_MUSIC_INFO_T;

typedef enum
{
    // Audio Codec Type: Unkown
    E_SPLAYER_AUDIO_CODEC_TYPE_UNKNOWN = -1,
    // Audio Codec Type: AAC
    E_SPLAYER_AUDIO_CODEC_TYPE_AAC = 0x100,
    // Audio Codec Type: AC3
    E_SPLAYER_AUDIO_CODEC_TYPE_AC3 = 0x200,
    // Audio Codec Type: AC3 Plus
    E_SPLAYER_AUDIO_CODEC_TYPE_AC3P,
    // Audio Codec Type: AMR NB
    E_SPLAYER_AUDIO_CODEC_TYPE_AMR_NB = 0x300,
    // Audio Codec Type: AMR WB
    E_SPLAYER_AUDIO_CODEC_TYPE_AMR_WB = 0x310,
    // Audio Codec Type: DTS
    E_SPLAYER_AUDIO_CODEC_TYPE_DTS = 0x400,
    // Audio Codec Type: DTS Express (LBR)
    E_SPLAYER_AUDIO_CODEC_TYPE_DTS_LBR,
    // Audio Codec Type: DTS HD (reserved.)
    E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD,
    // Audio Codec Type: DTS HD Master Audio
    E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD_MA,
    // Audio Codec Type: DTS HD High Resolution Audio (reserved.)
    E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD_HRA,
    // Audio Codec Type: FLAC
    E_SPLAYER_AUDIO_CODEC_TYPE_FLAC = 0x500,
    // Audio Codec Type: MP3
    E_SPLAYER_AUDIO_CODEC_TYPE_MP3 = 0x600,
    // Audio Codec Type: MP2
    E_SPLAYER_AUDIO_CODEC_TYPE_MPEG,
    // Audio Codec Type: COOK/RA8LBR
    E_SPLAYER_AUDIO_CODEC_TYPE_COOK = 0x700,
    // Audio Codec Type: COOK RA8LBR
    E_SPLAYER_AUDIO_CODEC_TYPE_RA8_LBR = E_SPLAYER_AUDIO_CODEC_TYPE_COOK,
    // Audio Codec Type: Vorbis
    E_SPLAYER_AUDIO_CODEC_TYPE_VORBIS = 0x800,
    // Audio Codec Type: DRA
    E_SPLAYER_AUDIO_CODEC_TYPE_DRA = 0x900,
    // Audio Codec Type: WMA1/WMA2/WMAPro
    E_SPLAYER_AUDIO_CODEC_TYPE_WMA = 0x1000,
    // Audio Codec Type: WMA1
    E_SPLAYER_AUDIO_CODEC_TYPE_WMA1,
    // Audio Codec Type: WMA2
    E_SPLAYER_AUDIO_CODEC_TYPE_WMA2,
    // Audio Codec Type: WMA3 (PRO)
    E_SPLAYER_AUDIO_CODEC_TYPE_WMA3,
    // Audio Codec Type: WMA3 (PRO)
    E_SPLAYER_AUDIO_CODEC_TYPE_WMA_PRO = E_SPLAYER_AUDIO_CODEC_TYPE_WMA3,
    // Audio Codec Type: PCM
    E_SPLAYER_AUDIO_CODEC_TYPE_PCM = 0x1101,
    // Audio Codec Type: ADCPM
    E_SPLAYER_AUDIO_CODEC_TYPE_ADPCM = 0x1200,
    // Audio Codec Type: OPUS
    E_SPLAYER_AUDIO_CODEC_TYPE_OPUS = 0x1300,
    // Audio Codec Type: AC4
    E_SPLAYER_AUDIO_CODEC_TYPE_AC4 = 0x1400,
    // Audio Codec Type: MPEG-H
    E_SPLAYER_AUDIO_CODEC_TYPE_MPEGH = 0x1500,
}SPLAYER_AudioCodecType_e;

typedef struct _APPL_SPLAYER_MOVIE_INFO_T
{
    UINT32  ui4_total_time;                /// [OUT] Total time
    UINT32  u32MovieWidth;               /// [OUT] Movie width
    UINT32  u32MovieHeight;              /// [OUT] Movie height
    CHAR    audioCodec[AUDIO_CODEC_LEN]; /// [OUT] Audio codec
    SPLAYER_AudioCodecType_e eAudioCodec;  //add
} APPL_SPLAYER_MOVIE_INFO_T;


typedef enum {
    APPL_SPLAYER_FILE_UNKNOWN = 0,
    APPL_SPLAYER_FILE_AV,
    APPL_SPLAYER_FILE_PHOTO
} APPL_SPLAYER_FILE_T;

typedef enum {
    // Invalid media type
    APPL_SPLAYER_MEDIA_INVALID = -1,
    // Photo media type
    APPL_SPLAYER_MEDIA_PHOTO = 0,
    // Music media type
    APPL_SPLAYER_MEDIA_MUSIC,
    // Movie media type
    APPL_SPLAYER_MEDIA_MOVIE,
    // Max enum of media type
    APPL_SPLAYER_MEDIA_MAX,
} APPL_SPLAYER_MEDIA_TYPE_T;

    
typedef enum {
    PHOTO_OP_PLAY = 0,
    PHOTO_OP_ROTATE,
    PHOTO_OP_ZOOM
} PHOTO_OP_TYPE_T;

typedef enum {
    SPLAYER_MM_EVENT_EXIT_OK ,
    SPLAYER_MM_EVENT_EXIT_FORCE,
    SPLAYER_MM_EVENT_EXIT_ERROR_FILE,

    SPLAYER_MM_EVENT_SUFFICIENT_DATA,
    SPLAYER_MM_EVENT_INSUFFICIENT_DATA,
    SPLAYER_MM_EVENT_PLAYING_INIT_OK,
    SPLAYER_MM_EVENT_FRAME_READY,
    SPLAYER_MM_EVENT_START_PLAY,
    SPLAYER_MM_EVENT_PLAYING_OK,

    SPLAYER_MM_EVENT_PROGRAM_CHANGED,
    SPLAYER_MM_EVENT_AUDIO_TRACK_CHANGED,
    SPLAYER_MM_EVENT_BACKWARD_TO_START,
    SPLAYER_MM_EVENT_CLEAR_DATA_READY,
    SPLAYER_MM_EVENT_AUDIO_UNSUPPORTED,
    SPLAYER_MM_EVENT_AUDIO_ONLY,
    SPLAYER_MM_EVENT_SEEK_ACK,
    SPLAYER_MM_EVENT_TRICK_ACK,
    SPLAYER_MM_EVENT_BLACK_SCREEN_OFF,
    SPLAYER_MM_EVENT_THUMBNAIL_DECODE_DONE,
    SPLAYER_MM_EVENT_THUMBNAIL_DECODE_FAIL,
    SPLAYER_MM_EVENT_VIDEO_TRACK_CHANGED,
    SPLAYER_MM_EVENT_VIDEO_RENDER_BUFFER_UNDERFLOW,
    SPLAYER_MM_EVENT_VIDEO_UNSUPPORTED,

    /// Photo Event
    SPLAYER_MM_EVENT_PHOTO_DECODE_DONE,
    SPLAYER_MM_EVENT_PHOTO_DECODE_FAILED,
    SPLAYER_MM_EVENT_PHOTO_DECODING_NEXT,
    SPLAYER_MM_EVENT_PHOTO_DISPLAYED,
    SPLAYER_MM_EVENT_PHOTO_DECODE_ONE_FRAME_DONE,

} APPL_SPLAYER_PLAY_EVENT;

typedef VOID (*appl_splayer_eventCallback)(
        APPL_SPLAYER_PLAY_EVENT, VOID *pvTag, UINT32 u4Data,VOID *pvPara);

// play media(audio / video / photo) indicated by file path
// please give the full path of the playing media
// usage: 
//   P_APPL_SPLAYER_T splayer = NULL;
//   appl_splayer_open("/3rd_rw/aavi.avi", NULL, NULL, 0, &splayer);
//   appl_splayer_close(&splayer);

// close a splayer and set NULL


typedef enum
{
    // The trick mode speed is 0X.
    SPLAYER_MM_TRICK_SPEED_0X = 0,
    // The trick mode speed is 1X.
    SPLAYER_MM_TRICK_SPEED_1X = 1,
    // The trick mode speed is 2X.
    SPLAYER_MM_TRICK_SPEED_2X,
    // The trick mode speed is 4X.
    SPLAYER_MM_TRICK_SPEED_4X,
    // The trick mode speed is 8X.
    SPLAYER_MM_TRICK_SPEED_8X,
    // The trick mode speed is 16X.
    SPLAYER_MM_TRICK_SPEED_16X,
    // The trick mode speed is 32X.
    SPLAYER_MM_TRICK_SPEED_32X,
    // The trick mode speed is 1.25X.
    SPLAYER_MM_TRICK_SPEED_1_25X,
    // The trick mode speed is 1.5X.
    SPLAYER_MM_TRICK_SPEED_1_5X,
    // The trick mode speed is 1.75X.
    SPLAYER_MM_TRICK_SPEED_1_75X,
    // The trick mode speed is slow
    SPLAYER_MM_TRICK_SPEED_SLOW = 0x1000,
    // The trick mode speed is slow 2x.
    SPLAYER_MM_TRICK_SPEED_SLOW_2X = SPLAYER_MM_TRICK_SPEED_SLOW,
    // The trick mode speed is slow 4x.
    SPLAYER_MM_TRICK_SPEED_SLOW_4X,
    // The trick mode speed is slow 8x.
    SPLAYER_MM_TRICK_SPEED_SLOW_8X,
    // The trick mode speed is slow 16x.
    SPLAYER_MM_TRICK_SPEED_SLOW_16X,
    // The trick mode speed is slow 32x.
    SPLAYER_MM_TRICK_SPEED_SLOW_32X,
    // The trick mode speed is slow 1.33x.
    SPLAYER_MM_TRICK_SPEED_SLOW_1_33X,
    // The trick mode speed is slow scan 2x.
    SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_2X = 0x2000,
    // The trick mode speed is slow scan 4x.
    SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_4X,
    // The trick mode speed is slow scan 8x.
    SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_8X,
    // The trick mode speed is slow scan 16x.
    SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_16X,
    // The trick mode speed is slow scan 32x.
    SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_32X,
    // The trick mode in step
    SPLAYER_MM_TRICK_SPEED_STEP = 0x4000,
    // The trick mode speed is none.
    SPLAYER_MM_TRICK_SPEED_NOT_SUPPORT
} SPLAYER_TrickSpeed_e;

typedef enum {
    SPLAYER_MM_EVENT_INFO_OPEN_OK,
    SPLAYER_MM_EVENT_INFO_OPEN_NG

} APPL_SPLAYER_INFO_EVENT;
typedef VOID (*appl_splayer_info_eventCallback)(
        APPL_SPLAYER_INFO_EVENT, VOID *pvTag, UINT32 u4Data,VOID *pvPara);

#define MAX_FILE_PATH_LEN 512

typedef struct _APPL_SPLAYER_MEDIA_INFO_T
{
    MI_HANDLE   hMm;
    MI_HANDLE   hDisp;
    MI_HANDLE   hAout;
    MI_U64      u64CallbackId;
    appl_splayer_info_eventCallback pfCallback;
    VOID*       pvPara;
    APPL_SPLAYER_MEDIA_TYPE_T e_type;
    CHAR        filePath[MAX_FILE_PATH_LEN];

    UINT64  u32MsTime;
    CHAR    szYear[YEAR_LENGTH];
    //CHAR    szFileName[USB_PATH_MAX_LENGTH];
    CHAR    szFileLocation[USB_PATH_MAX_LENGTH];
    CHAR    szMetadataTitle [MAX_METADATA_STRING_LENGTH];
    CHAR    szMetadataArtist[MAX_METADATA_STRING_LENGTH];
    CHAR    szMetadataGenre [MAX_METADATA_STRING_LENGTH];
    CHAR    szMetadataAlbum [MAX_METADATA_STRING_LENGTH];

    MI_U32  u32ArtistLen;
    MI_U32  u32AlbumLen;
    MI_U32  u32TitleLen;
    MI_U32  u32GenreLen;
    MI_U32  u32YearLen;

    BOOL    b_pic_exist;
    UINT32  u32PictureSize;
    WGL_IMG_T t_img;
    WGL_HIMG_TPL_T h_cover_img;
	UINT16 ui2AdID;//ID for audio get info 
} APPL_SPLAYER_MEDIA_INFO_T;

typedef struct _APPL_SPLAYER_MUSIC_COVER_T
{
    BOOL    b_pic_exist;
    UINT32  u32PictureSize;
    WGL_IMG_T t_img;
    WGL_HIMG_TPL_T h_cover_img;
} APPL_SPLAYER_MUSIC_COVER_T;

VOID appl_splayer_close(P_APPL_SPLAYER_T *ppsPlayer);
// enable or disable subtitle showing of video, ignored when playing photo
#ifdef NEVER
VOID appl_splayer_enableSubtitle(P_APPL_SPLAYER_T psPlayer, BOOL isEnable);
// get subtitle enable or disable, ignored when playing photo
BOOL appl_splayer_isSubtitleEnable(P_APPL_SPLAYER_T psPlayer);
#endif /* NEVER */
INT32 appl_splayer_start_play(APPL_SPLAYER_PLAY_EVENT eEventType,void * pvTag,uint32_t u4Data);
INT32 appl_splayer_open_async(const CHAR *filePath,
        appl_splayer_eventCallback callback, VOID *pvTag,
        INT32 playMode, P_APPL_SPLAYER_T *ppsPlayer, VOID *pvPara);
INT32 appl_splayer_play_async(const CHAR *filePath,
        appl_splayer_eventCallback callback, VOID *pvTag,
        INT32 playMode, P_APPL_SPLAYER_T *ppsPlayer, VOID *pvPara);

INT32 a_appl_splayer_get_movie_info(P_APPL_SPLAYER_T *ppsPlayer,APPL_SPLAYER_MOVIE_INFO_T *ptMovieInfo);
INT32 a_appl_splayer_get_music_info(P_APPL_SPLAYER_T *ppsPlayer,APPL_SPLAYER_MUSIC_INFO_T *ptInfo);
INT32 a_appl_splayer_get_av_position(P_APPL_SPLAYER_T *ppsPlayer,UINT32 *u32MsTime);
INT32 a_appl_splayer_get_av_duration (P_APPL_SPLAYER_T *ppsPlayer,UINT32 *u32MsTime);
INT32 a_appl_splayer_set_seek(P_APPL_SPLAYER_T *ppsPlayer,UINT32 u32MsTime);
INT32 a_appl_splayer_play_pause(P_APPL_SPLAYER_T *ppsPlayer,BOOL b_paly);
INT32 a_appl_splayer_get_media_info(const CHAR *filePath,APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo);
BOOL a_appl_splayer_init(VOID);
INT32 a_appl_splayer_get_movie_speed(P_APPL_SPLAYER_T *ppsPlayer,SPLAYER_TrickSpeed_e *pe_speed);
INT32 a_appl_splayer_set_fastforword(P_APPL_SPLAYER_T *ppsPlayer,SPLAYER_TrickSpeed_e ePlaySpeed);
INT32 a_appl_splayer_set_fastbackword(P_APPL_SPLAYER_T *ppsPlayer,SPLAYER_TrickSpeed_e ePlaySpeed);
INT32  _appl_splayer_close_info(APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo);
INT32 _appl_splayer_open_info(const CHAR *filePath,
                                        appl_splayer_info_eventCallback callback,
                                        APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo,
                                        VOID *pvPara);
INT32 _appl_splayer_audio_sort_open(const CHAR *filePath,
                                                appl_splayer_info_eventCallback callback,
                                                APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo,
                                                VOID *pvPara);
INT32 _appl_splayer_get_music_cover(const CHAR *filePath,APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo);

#endif

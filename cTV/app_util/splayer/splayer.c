/*
 * =====================================================================================
 *
 *       Filename:  splayer.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/06/2013 11:24:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xieminchen (mtk), hs_xieminchen@mediatek.com
 *        Company:  Mediatek
 *
 * =====================================================================================
 */

#include "c_os.h"
#include "c_fm.h"
#include "c_dlm.h"
#ifdef NEVER
#include "cmpb/IMtkPb_ErrorCode.h"
#include "cmpb/IMtkPb_Ctrl.h"
#include "cmpb/IMtkPb_Ctrl_DTV.h"
#endif /* NEVER */
#include "c_img.h"
#ifdef NEVER
#include "cmpb/IMtkPb_Comm.h"
#endif /* NEVER */

#include "splayer.h"
#include "nav/nav_common.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "res/app_util/config/acfg_custom.h"
#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"
#include "mi_audio.h"
#include "mmp/video_engine/_mmp_ve_type.h"


#define SPLAYER_LOG(fmt...)
#define EXT_LEN 5
#define MAX_FILE_PATH_LEN 512
#define APPL_SPLAYER_MUSIC_EXT_NUM (sizeof(_ag_MusicExtList) / EXT_LEN)
#define APPL_SPLAYER_AV_EXT_NUM (sizeof(_ag_avExtList) / EXT_LEN)
#define APPL_SPLAYER_PHOTO_EXT_NUM (sizeof(_ag_photoExtList) / EXT_LEN)
#define SPLAYER_PREFIX "file://"
#define SPLAYER_USB_PREFIX "/mnt/usb"
#define DBGINFO          "USBMMPlayer: "

#define isPlayerType(pPlayer, type) ((pPlayer)->fileType == (type))
#define setPlayerType(pPlayer, fileType) ((pPlayer)->fileType = fileType)

#define ALIGN_N(x,n)   ((x+(n-1)) & ~(n-1))

static BOOL _bIsMMModuleInit = FALSE;
static INT16 i2_event_status = 0;
#ifdef NEVER
MI_U32    _gu32MMUSB_ArbitratorState = USBMM_ARBITRATOR_STATE_EXIT;
#endif /* NEVER */
#ifdef NEVER
MI_U32    _gu32MMUSB_RequestType = 0;
#endif /* NEVER */
static MI_S32   _s32TaskEventGrpId = -1;
#define MAX_MMSDK_INIT_WAIT_MS      3000

#define MMUSB_EVENT_N_NOTIFY      (MI_BIT(16))

#define MMUSB_REQUEST_NOTIFY            (MI_BIT(0))

#define MMUSB_REQUEST_SCAN              (MI_BIT(0))
#define MMUSB_REQUEST_THUMBNAIL         (MI_BIT(1))
#define MMUSB_REQUEST_PLAY              (MI_BIT(2))
#define MMUSB_REQUEST_EXIT              (MI_BIT(3))

#define MMUSB_EVENT_SCAN_DONE           (MI_BIT(0))
#define MMUSB_EVENT_THUMBNAIL_DONE      (MI_BIT(1))
#define MMUSB_EVENT_PLAY_DONE           (MI_BIT(2))
#define MMUSB_EVENT_ENTER_MMP           (MI_BIT(3))

#define MMUSB_EVENT_SCAN_START          (MI_BIT(4))
#define MMUSB_EVENT_THUMBNAIL_START     (MI_BIT(5))
#define MMUSB_EVENT_PLAY_START          (MI_BIT(6))

#define MI_MM_NAME_LENGTH           32
#define MI_MM_NAME_MODEL              "MI_DEMO_MM_IDX_0"
#define MI_MM_NAME_MODEL_1            "MI_PARSE_MM_IDX_0"

#define MI_MM_AUDIO_SORT_HANDLE    "MI_MM_HANDLE_AUD_0"
#define DISP_HANDLE_STRING_NAME       "MI_DISP_HD%d"

extern  HANDLE_T h_g_acfg_scc_main_vid;

typedef enum
{
    /// Unknown File Extension name or no File Extension
    E_USBMM_FILE_EXTENSION_UNKNOWN = 0,
    /// According to File Extension, it is a movie file
    E_USBMM_FILE_EXTENSION_MOVIE,
    /// According to File Extension, it is a music file
    E_USBMM_FILE_EXTENSION_MUSIC,
    /// According to File Extension, it is a photo file
    E_USBMM_FILE_EXTENSION_PHOTO,
} USBMM_FILE_EXTENSION_e;

#define MI_MM_CHECK_INIT()\
{\
    if(_bIsMMModuleInit == FALSE)\
    {\
        DBG_LOG_PRINT(("Do MI_MM_INIT First\n"));\
    }\
}

#define CHECK_RET(RET, VALUE)\
{\
    if( RET != VALUE)\
    {\
            DBG_LOG_PRINT(("\033[33m%s %d [Check Ret Fail! Ret=%d]\033[m\n", __FUNCTION__, __LINE__, RET));  \
    }\
}

static struct APPL_SPLAYER_T {
    APPL_SPLAYER_FILE_T        fileType;
    APPL_SPLAYER_MEDIA_TYPE_T  e_type;
    PHOTO_OP_TYPE_T            photoOpType;
    CHAR                       filePath[MAX_FILE_PATH_LEN];
    appl_splayer_eventCallback pfCallback;
    VOID *                     pvCallbackTag;
    VOID *                     pvPara;
    INT32                      playMode;
    UINT32                     ui4_nfy_id; // notify id register to USB
    RMV_DEV_OPEN_ID_T          openid; // usb point to open
#ifdef NEVER
    IMTK_PB_HANDLE_T           hPB_Handle;
#endif /* NEVER */
    MI_HANDLE                  h_MI_MM_Hdl;
    MI_HANDLE                  h_Disp_Hdl;
    MI_HANDLE                  h_AOut_Hdl;
    BOOL                       isPlay;
    BOOL                       subtitleEnable;
    UINT32                     ui4_tfx_idx;
    UINT32                     ui4_rotate_angle_idx;
    UINT32                     ui4_zoom_idx;
    UINT64                     u64CallbackId;
} sPlayer[2] = { { 0 }, { 0 } }; // player stored for two players at same time

const static CHAR _ag_avExtList[][EXT_LEN] = {
  "avi", "divx", "mp4", "mov", "asf", "wmv", "mpg", "mpe",
  "mpeg", "vob", "dat", "asx", "m4v", "mkv", "ts" , "trp",
  "tts", "m2ts", "mts", "flv", "webm", "3gp", "f4v", "xvid",
  "qt", "mk3d", "3g2", "mp3", "wma", "wav", "m4a", "aif",
  "aiff", "aac", "ac3", "ec3", "amr", "ogg", "oga", "flac"};

const static CHAR _ag_MusicExtList[][EXT_LEN] = {
    "mp3",
    "m4a",
    "wav",
    "flac",
};

const static CHAR _ag_MovieExtList[][EXT_LEN] = {
    "avi", "divx", "mp4", "mov", "asf", "wmv", "mpg", "mpe",
    "mpeg", "vob", "dat", "asx", "m4v", "mkv", "ts" , "trp",
    "tts", "m2ts", "mts", "flv", "webm", "3gp", "f4v", "xvid",
    "qt", "mk3d", "3g2", "wma", "aif","aiff", "aac", "ac3", "ec3",
    "amr", "ogg", "oga"
};

const static CHAR _ag_photoExtList[][EXT_LEN] = {
  "jpg", "jpeg", "png", "bmp", "gif", "mpo", "pns", "jps",
  "bms", "dib" };


#define APPL_SPLAYER_MOVIE_EXT_NUM (sizeof(_ag_MovieExtList) / EXT_LEN)

/*-----------------------------------------------------------------------------
* private methods declarations
*---------------------------------------------------------------------------*/
static APPL_SPLAYER_FILE_T _appl_splayer_getFileType(const CHAR *filePath);
static APPL_SPLAYER_MEDIA_TYPE_T _appl_splayer_get_media_type(const CHAR *filePath);
// play audio / video file type
static INT32 _appl_splayer_playAV_Async(P_APPL_SPLAYER_T psPlayer);
static INT32 _appl_splayer_openAV(P_APPL_SPLAYER_T psPlayer);

// close play
static VOID  _appl_splayer_closeAV(P_APPL_SPLAYER_T psPlayer);
// play photo file type
static INT32 _appl_splayer_playPhoto(P_APPL_SPLAYER_T psPlayer);
static VOID _appl_splayer_closePhoto(P_APPL_SPLAYER_T psPlayer);
// callback registed to cmpb player
MI_RESULT _appl_splayer_callback(
                       MI_HANDLE          h_MI_Hdl,
                       APPL_SPLAYER_PLAY_EVENT            eEventType,
                       VOID             *pNotifyParams,
                       VOID             *pUserParams);


// callback registed to image player
#ifdef NEVER
static VOID _appl_splayer_imageCallback(HANDLE_T h_handle, const VOID* pv_tag,
        IMG_NFY_EVENT_TYPE_T e_event, const VOID* pv_data);
static VOID _appl_splayer_usbNotify(VOID *pv_tag,
    RMV_DEV_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
static INT32 _appl_splayer_openUSBPoint(const CHAR *path,
    RMV_DEV_OPEN_ID_T *openid);
#endif /* NEVER */
static BOOL _appl_splayer_isFileExist(const CHAR *filePath);
#ifdef NEVER
static BOOL _appl_splayer_isPlayUSB(const CHAR *filePath);
#endif /* NEVER */
static BOOL _appl_splayer_init(VOID);
static VOID _appl_splayer_open(P_APPL_SPLAYER_T psPlayer);
static BOOL _appl_splayer_get_disp_handle(MI_HANDLE *phDisp,UINT16 ui2_idx);
static BOOL _appl_splayer_get_aout_handle(MI_HANDLE *phAout);
static BOOL _appl_splayer_get_effect_type(MI_MM_PhotoSlideShowEffect_e* eEffect,P_APPL_SPLAYER_T psPlayer);
static BOOL _appl_splayer_get_rotate_angle(MI_MM_RotateAngle_e* eAngle,P_APPL_SPLAYER_T psPlayer);
static BOOL _appl_splayer_get_zoom_value(MI_MM_ViewZoomFactor_e* eZoomFactor,P_APPL_SPLAYER_T psPlayer);
static BOOL _appl_splayer_photo_draw(P_APPL_SPLAYER_T psPlayer);
static INT32 _appl_splayer_pre_start(P_APPL_SPLAYER_T psPlayer);
static BOOL _appl_splayer_mi_mm_unregister(P_APPL_SPLAYER_T psPlayer);
static APPL_SPLAYER_MEDIA_TYPE_T _appl_splayer_get_media_type(const CHAR *filePath);

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
INT32 appl_splayer_open_async(const CHAR *filePath,
        appl_splayer_eventCallback callback, VOID *pvTag,
        INT32 playMode, P_APPL_SPLAYER_T *ppsPlayer, VOID *pvPara)
{
    NAV_ASSERT(NULL != filePath);

    if(!_appl_splayer_init())
    {
        SPLAYER_DBG_ERROR("MM init Fail");
        return APPL_SPLAYER_FAILED;
    }
#ifdef NEVER
    // check file exist
    if (!_appl_splayer_isFileExist((CHAR *)filePath))
        return APPL_SPLAYER_FILE_NOT_EXIST;
#endif /* NEVER */
    // get file type
    APPL_SPLAYER_FILE_T fileType = _appl_splayer_getFileType(filePath);
    if (APPL_SPLAYER_FILE_UNKNOWN == fileType)
        return APPL_SPLAYER_FILE_FORMAT_NOT_SUPPORT;
    // check is played
    if (isPlayerType(&sPlayer[0], fileType) ||
        isPlayerType(&sPlayer[1], fileType))
        return APPL_SPLAYER_PLAYED_ALREADY;

    // get player cell
    P_APPL_SPLAYER_T psPlayer = NULL;
    if (isPlayerType(&sPlayer[0], APPL_SPLAYER_FILE_UNKNOWN))
        psPlayer = &sPlayer[0];
    else
        psPlayer = &sPlayer[1];

    // init player
    c_memset(psPlayer, 0, sizeof(*psPlayer));
    setPlayerType(psPlayer, fileType);
    psPlayer->pfCallback = callback;
    psPlayer->pvCallbackTag = pvTag;
    psPlayer->pvPara = pvPara;
    psPlayer->playMode = playMode;
    psPlayer->e_type   = _appl_splayer_get_media_type(filePath);

    // copy path
    INT32 n = 0;
    if (isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
        // add prefix before av path
        n = c_snprintf(psPlayer->filePath, MAX_FILE_PATH_LEN, "%s%s",
                    SPLAYER_PREFIX, filePath);
    else
        n = c_snprintf(psPlayer->filePath, MAX_FILE_PATH_LEN, "%s", filePath);
    if (n >= MAX_FILE_PATH_LEN)
        NAV_ASSERT(0);

    INT32 i4_ret = APPL_SPLAYER_FAILED;
#ifdef NEVER
    // register usb notify if path is usb
    if (_appl_splayer_isPlayUSB(filePath))
    {
        // open usb point
        i4_ret = _appl_splayer_openUSBPoint(filePath,
                    &(psPlayer->openid));
        if (RMVR_OK == i4_ret)
        {
            i4_ret = a_rmv_dev_reg_monitor(_appl_splayer_usbNotify,
                (VOID *)psPlayer, &(psPlayer->ui4_nfy_id));
            if (RMVR_OK != i4_ret)
                SPLAYER_LOG("Cannot register usb notify: %d with id %d\n", i4_ret);
        }
        else
            SPLAYER_LOG("Cannot open usb point: %d\n", i4_ret);
    }
#endif /* NEVER */

    // play
    SPLAYER_DBG_INFO("Going to play file %s with file type %d\n",psPlayer->filePath, (INT32)fileType);
    if (isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
        i4_ret = _appl_splayer_openAV(psPlayer);
    else
        i4_ret = _appl_splayer_playPhoto(psPlayer);

    if (APPL_SPLAYER_SUCCESS == i4_ret)
        // set player to user
        *ppsPlayer = psPlayer;
    else
    {
        SPLAYER_DBG_ERROR("Failed to play: %d",i4_ret);
        c_memset(psPlayer, 0, sizeof(*psPlayer));
    }

    return i4_ret;
}

INT32 appl_splayer_play_async(const CHAR *filePath,
        appl_splayer_eventCallback callback, VOID *pvTag,
        INT32 playMode, P_APPL_SPLAYER_T *ppsPlayer, VOID *pvPara)
{
    DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = APPL_SPLAYER_FAILED;
    NAV_ASSERT(NULL != filePath);
    // get player cell
    //P_APPL_SPLAYER_T psPlayer = *ppsPlayer;
    //if (isPlayerType(&sPlayer[0], APPL_SPLAYER_FILE_UNKNOWN))
        //psPlayer = &sPlayer[0];
    //else
        //psPlayer = &sPlayer[1];

    //psPlayer = *ppsPlayer;

    // init player
    //c_memset(psPlayer, 0, sizeof(*psPlayer));
    //setPlayerType(psPlayer, fileType);
    //psPlayer->fileType = APPL_SPLAYER_FILE_AV;
    //psPlayer->pfCallback = callback;
    //psPlayer->pvCallbackTag = pvTag;
    //psPlayer->pvPara = pvPara;
    //psPlayer->playMode = playMode;
    //psPlayer->e_type   = _appl_splayer_get_media_type(filePath);
#if 0
    if(!_appl_splayer_init())
    {
        SPLAYER_DBG_ERROR("MM init Fail");
        return APPL_SPLAYER_FAILED;
    }
#ifdef NEVER
    // check file exist
    if (!_appl_splayer_isFileExist((CHAR *)filePath))
        return APPL_SPLAYER_FILE_NOT_EXIST;
#endif /* NEVER */
    // get file type
    APPL_SPLAYER_FILE_T fileType = _appl_splayer_getFileType(filePath);
    if (APPL_SPLAYER_FILE_UNKNOWN == fileType)
        return APPL_SPLAYER_FILE_FORMAT_NOT_SUPPORT;
    // check is played
    if (isPlayerType(&sPlayer[0], fileType) ||
        isPlayerType(&sPlayer[1], fileType))
        return APPL_SPLAYER_PLAYED_ALREADY;

    // get player cell
    P_APPL_SPLAYER_T psPlayer = NULL;
    if (isPlayerType(&sPlayer[0], APPL_SPLAYER_FILE_UNKNOWN))
        psPlayer = &sPlayer[0];
    else
        psPlayer = &sPlayer[1];

    // init player
    c_memset(psPlayer, 0, sizeof(*psPlayer));
    setPlayerType(psPlayer, fileType);
    psPlayer->pfCallback = callback;
    psPlayer->pvCallbackTag = pvTag;
    psPlayer->pvPara = pvPara;
    psPlayer->playMode = playMode;
    psPlayer->e_type   = _appl_splayer_get_media_type(filePath);

    // copy path
    INT32 n = 0;
    if (isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
        // add prefix before av path
        n = c_snprintf(psPlayer->filePath, MAX_FILE_PATH_LEN, "%s%s",
                    SPLAYER_PREFIX, filePath);
    else
        n = c_snprintf(psPlayer->filePath, MAX_FILE_PATH_LEN, "%s", filePath);
    if (n >= MAX_FILE_PATH_LEN)
        NAV_ASSERT(0);

    INT32 i4_ret = APPL_SPLAYER_FAILED;
#ifdef NEVER
    // register usb notify if path is usb
    if (_appl_splayer_isPlayUSB(filePath))
    {
        // open usb point
        i4_ret = _appl_splayer_openUSBPoint(filePath,
                    &(psPlayer->openid));
        if (RMVR_OK == i4_ret)
        {
            i4_ret = a_rmv_dev_reg_monitor(_appl_splayer_usbNotify,
                (VOID *)psPlayer, &(psPlayer->ui4_nfy_id));
            if (RMVR_OK != i4_ret)
                SPLAYER_LOG("Cannot register usb notify: %d with id %d\n", i4_ret);
        }
        else
            SPLAYER_LOG("Cannot open usb point: %d\n", i4_ret);
    }
#endif /* NEVER */

    // play
    SPLAYER_DBG_INFO("Going to play file %s with file type %d\n",psPlayer->filePath, (INT32)fileType);
    if (isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
        i4_ret = _appl_splayer_openAV(psPlayer);
    else
        i4_ret = _appl_splayer_playPhoto(psPlayer);

    if (APPL_SPLAYER_SUCCESS == i4_ret)
        // set player to user
        *ppsPlayer = psPlayer;
    else
    {
        SPLAYER_DBG_ERROR("Failed to play: %d",i4_ret);
        c_memset(psPlayer, 0, sizeof(*psPlayer));
    }
#endif
    //SPLAYER_DBG_INFO("Going to play file %s with file type %d\n",*ppsPlayer->filePath, (INT32)*ppsPlayer->fileType);
    //if (isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
        i4_ret = _appl_splayer_playAV_Async(*ppsPlayer);

    return i4_ret;
}

VOID appl_splayer_close(P_APPL_SPLAYER_T *ppsPlayer)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

#ifdef NEVER
    // close usb point
    INT32 i4_ret = 0;
    if (RMV_DEV_NULL_OPEN_ID != (*ppsPlayer)->openid)
    {
        i4_ret = a_rmv_dev_close_mnt_point((*ppsPlayer)->openid);
        if (RMVR_OK != i4_ret)
            SPLAYER_LOG("Cannot close mount point at %d: %d\n",
                (*ppsPlayer)->openid, i4_ret);
        (*ppsPlayer)->openid = RMV_DEV_NULL_OPEN_ID;
    }

    // unregister notify if registered
    if (0 != (*ppsPlayer)->ui4_nfy_id)
    {
        i4_ret = a_rmv_dev_unreg_monitor((*ppsPlayer)->ui4_nfy_id);
        if (RMVR_OK != i4_ret)
            SPLAYER_LOG("Cannot unreg usb notify at %d with ret %d\n",
            (*ppsPlayer)->ui4_nfy_id, i4_ret);
        (*ppsPlayer)->ui4_nfy_id = 0;
    }
#endif /* NEVER */

    // close
    if (isPlayerType(*ppsPlayer, APPL_SPLAYER_FILE_AV))
        _appl_splayer_closeAV(*ppsPlayer);
    else
        _appl_splayer_closePhoto(*ppsPlayer);

    c_memset(*ppsPlayer, 0, sizeof(**ppsPlayer));
    *ppsPlayer = NULL;
}
#ifdef NEVER

VOID appl_splayer_enableSubtitle(P_APPL_SPLAYER_T psPlayer, BOOL isEnable)
{
    NAV_ASSERT(NULL != psPlayer);

    if (!isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
    {
        SPLAYER_LOG("Invalid player type, ignore enable subtitle\n");
        return;
    }

    if (isEnable == psPlayer->subtitleEnable)
    {
        SPLAYER_LOG("Set same state: %d\n", isEnable);
        return;
    }

    // get subtitle info
  IMTK_PB_CTRL_MEDIA_INFO_T t_media_info_temp;
  c_memset(&t_media_info_temp, 0, sizeof(t_media_info_temp));
    int ret = IMtkPb_Ctrl_Get(psPlayer->hPB_Handle,
        IMTK_PB_CTRL_GET_TYPE_MEDIA_INFO, &t_media_info_temp,
        sizeof(IMTK_PB_CTRL_MEDIA_INFO_T));
    if (IMTK_PB_ERROR_CODE_OK != ret)
    {
        SPLAYER_LOG("Cannot get subtitle info from cmpb\n");
        return;
    }

    if (t_media_info_temp.u2SubtlTrackNum < 1)
    {
        SPLAYER_LOG("No valid subtitle: vid %d, aud %d, sbt %d\n",
            t_media_info_temp.u2VideoTrackNum, t_media_info_temp.u2AudioTrackNum,
            t_media_info_temp.u2SubtlTrackNum);
        return;
    }
    // select sub
    uint16_t subtitleIndex = IMTK_CTRL_SUBTITLE_OFF;
    if (isEnable)
        subtitleIndex = 0;
    INT32 i4_ret = IMtkPb_Ctrl_SetSubtitleTrack(
        psPlayer->hPB_Handle, subtitleIndex);

  if (IMTK_PB_ERROR_CODE_OK != i4_ret)
    {
        SPLAYER_LOG("Cannot set SetSubtitleTrack. Error = [%d]\n", i4_ret);
        return;// i4_ret;
    }

    SPLAYER_LOG("Select subtitle with ret %d at %d\n", i4_ret, subtitleIndex);

    psPlayer->subtitleEnable = isEnable;
}

BOOL appl_splayer_isSubtitleEnable(P_APPL_SPLAYER_T psPlayer)
{
    NAV_ASSERT(NULL != psPlayer);

    BOOL isEnable = FALSE;
    if (isPlayerType(psPlayer, APPL_SPLAYER_FILE_AV))
        isEnable = psPlayer->subtitleEnable;
    else
        SPLAYER_LOG("Invalid player type\n");

    return isEnable;
}
#endif /* NEVER */

static INT32 _appl_splayer_openAV(P_APPL_SPLAYER_T psPlayer)
{
      MI_RESULT                    eRet = MI_ERR_FAILED;
      MI_MM_OpenParams_t           tOpenParams;
      MI_MM_CallbackInputParams_t  stInputParams;
      MI_MM_CallbackOutputParams_t stOutputParams;
      MI_MM_ApTypeParams_t         stApParams;
      UINT32                       ui4_idx = 0;
      CHAR                         szMmName[128] = {0};

      MI_MM_CHECK_INIT();
      c_memset(&tOpenParams, 0, sizeof(tOpenParams));
      ui4_idx = 0xD431;// %d  =  54321
      c_snprintf(szMmName, sizeof(szMmName), "MI_MM_%d", ui4_idx);
      tOpenParams.pszName = (uint8_t *)szMmName;
      if(psPlayer->e_type == APPL_SPLAYER_MEDIA_MUSIC)
      {
          tOpenParams.eMediaType = E_MI_MM_MEDIA_MUSIC;
      }
      else
      {
          tOpenParams.eMediaType = E_MI_MM_MEDIA_MOVIE;
      }

      SPLAYER_DBG_INFO(" psPlayer->e_type:%d \r\n",psPlayer->e_type);
      eRet = MI_MM_Open(&tOpenParams, &psPlayer->h_MI_MM_Hdl);
      if(eRet != MI_OK)
      {
          SPLAYER_DBG_ERROR("MI_MM_Open fail ret = %d\n", eRet);
          return APPL_SPLAYER_FAILED;
      }

      SPLAYER_DBG_INFO(" h_MI_MM_Hdl 0x%x!! \r\n",psPlayer->h_MI_MM_Hdl);
      stInputParams.pfEventCallback = _appl_splayer_callback;
      stInputParams.u32EventFlags   = E_MI_MM_EVENT_ALL;
      stInputParams.u64CallbackId = 0;
      stInputParams.pUserParams = (VOID*)psPlayer;
      eRet = MI_MM_RegisterCallback(psPlayer->h_MI_MM_Hdl, &stInputParams, &stOutputParams);

      psPlayer->u64CallbackId = stOutputParams.u64CallbackId;

      SPLAYER_DBG_INFO("**  ***u64CallbackId :(0x%llx) \r\n",psPlayer->u64CallbackId);

      if((eRet == MI_OK) && (stOutputParams.u64CallbackId != 0))
      {
          SPLAYER_DBG_PRINT(" MI_MM_RegisterCallback Success \n");
      }
      else
      {
          SPLAYER_DBG_ERROR("MI_MM_RegisterCallback Fail,eRet :%d!!\n",eRet);
      }

      stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;  //////ADI type
      eRet = MI_MM_SetAttr(psPlayer->h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (VOID *)&stApParams);
      if(eRet>=MI_ERR_FAILED)
      {
          SPLAYER_DBG_ERROR("Set AP mode Failure!!\n");
      }

      if(psPlayer->e_type == APPL_SPLAYER_MEDIA_MOVIE)
      {
          // 7. Get display handle.
          if(_appl_splayer_get_disp_handle(&psPlayer->h_Disp_Hdl,0) == FALSE)
          {
              SPLAYER_DBG_ERROR("_appl_splayer_get_disp_handle Fail \r\n");
          }

          MI_DISP_ConnectedConds_t stDispConds = {0};
          MI_U32 u32ConnectedNum = 0;
          stDispConds.bIsInput = TRUE;
          stDispConds.u32Module = MI_MODULE_TYPE_VIDEO;
          if(MI_DISP_GetConnectedNum(psPlayer->h_Disp_Hdl, &stDispConds, &u32ConnectedNum) != MI_OK)
          {
              SPLAYER_DBG_ERROR(" Fail at h_Disp_Hdl 0x%x!!\n",psPlayer->h_Disp_Hdl);
          }
          SPLAYER_DBG_INFO(" get h_Disp_Hdl : 0x%x \r\n",psPlayer->h_Disp_Hdl);
      }

      // 8. Get audio out handle.
      if ( _appl_splayer_get_aout_handle(&psPlayer->h_AOut_Hdl) == FALSE)
      {
          SPLAYER_DBG_ERROR(" Fail at _appl_splayer_get_aout_handle \n");
      }

      /*Jundi add for resolving the problem of preview size*/
      _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)(psPlayer->pvPara);
      DBG_LOG_PRINT(("[Jundi][%s %d]pt_this->t_present_mode == %d\n",__FUNCTION__,__LINE__,pt_this->t_present_mode));
      if(MMP_FP_PRESENT_MODE_PREVIEW == pt_this->t_present_mode)
      {
          MI_DISP_VidWinRect_t stOutRect;
		  SCC_VID_PANEL_INFO_T t_main_panel_info;
		  c_scc_vid_get_panel_info(h_g_acfg_scc_main_vid, &t_main_panel_info);
		  DBG_LOG_PRINT(("[chonghuang][%s %d]t_main_panel_info.ui4_PanelWidth == %d\n",__FUNCTION__,__LINE__,t_main_panel_info.ui4_PanelWidth));

#ifdef MT5583_MODEL
		  if (t_main_panel_info.ui4_PanelWidth == 1366)
		  {
	          stOutRect.u16X = 405;
	          stOutRect.u16Y = 2;
	          stOutRect.u16Width = 405;
	          stOutRect.u16Height = 180;
		  }
		  else if(t_main_panel_info.ui4_PanelWidth == 1920)
		  {
	          stOutRect.u16X = 572;
	          stOutRect.u16Y = 4;
	          stOutRect.u16Width = 590;
	          stOutRect.u16Height = 268;
		  }
#else
          stOutRect.u16X = 572 * 2;
          stOutRect.u16Y = 4*2;
          stOutRect.u16Width = 590*2;
          stOutRect.u16Height = 268*2;
#endif
          stOutRect.u16Width = ALIGN_N(stOutRect.u16Width,32);
          stOutRect.u16Height = ALIGN_N(stOutRect.u16Height,16);

          CHECK_RET(MI_DISP_SetMute(psPlayer->h_Disp_Hdl, E_MI_DISP_MUTE_FLAG_SET_WINDOW),MI_OK);

          CHECK_RET(MI_DISP_SetOutputRect(psPlayer->h_Disp_Hdl, &stOutRect),MI_OK);
          eRet = MI_DISP_ApplySetting(psPlayer->h_Disp_Hdl);

          if(eRet == MI_ERR_NOT_SUPPORT)
          {
              SPLAYER_DBG_ERROR("Scaling Down Size exceed HW limitation: DEC Rate\n");
          }
          else
          {
              SPLAYER_DBG_INFO(" eRet:%d, MI_DISP_ApplySetting successed\n",eRet);
          }
          CHECK_RET(MI_DISP_SetUnMute(psPlayer->h_Disp_Hdl, E_MI_DISP_MUTE_FLAG_SET_WINDOW),MI_OK);
      }

      return APPL_SPLAYER_SUCCESS;

}
static INT32 _appl_splayer_playAV(P_APPL_SPLAYER_T psPlayer)
{

    MI_RESULT                    eRet = MI_ERR_FAILED;
    #if 0
    MI_MM_OpenParams_t           tOpenParams;
    MI_MM_CallbackInputParams_t  stInputParams;
    MI_MM_CallbackOutputParams_t stOutputParams;
    MI_MM_ApTypeParams_t         stApParams;
    UINT32                       ui4_idx = 0;
    CHAR                         szMmName[128] = {0};

    MI_MM_CHECK_INIT();
    c_memset(&tOpenParams, 0, sizeof(tOpenParams));
    ui4_idx = 0xD431;// %d  =  54321
    c_snprintf(szMmName, sizeof(szMmName), "MI_MM_%d", ui4_idx);
    tOpenParams.pszName = (uint8_t *)szMmName;
    if(psPlayer->e_type == APPL_SPLAYER_MEDIA_MUSIC)
    {
        tOpenParams.eMediaType = E_MI_MM_MEDIA_MUSIC;
    }
    else
    {
        tOpenParams.eMediaType = E_MI_MM_MEDIA_MOVIE;
    }

    SPLAYER_DBG_INFO(" psPlayer->e_type:%d \r\n",psPlayer->e_type);
    eRet = MI_MM_Open(&tOpenParams, &psPlayer->h_MI_MM_Hdl);
    if(eRet != MI_OK)
    {
        SPLAYER_DBG_ERROR("MI_MM_Open fail ret = %d\n", eRet);
        return APPL_SPLAYER_FAILED;
    }

    SPLAYER_DBG_INFO(" h_MI_MM_Hdl 0x%x!! \r\n",psPlayer->h_MI_MM_Hdl);
    stInputParams.pfEventCallback = _appl_splayer_callback;
    stInputParams.u32EventFlags   = E_MI_MM_EVENT_ALL;
    stInputParams.u64CallbackId = 0;
    stInputParams.pUserParams = (VOID*)psPlayer;
    eRet = MI_MM_RegisterCallback(psPlayer->h_MI_MM_Hdl, &stInputParams, &stOutputParams);

    psPlayer->u64CallbackId = stOutputParams.u64CallbackId;

    SPLAYER_DBG_INFO("**  ***u64CallbackId :(0x%llx) \r\n",psPlayer->u64CallbackId);

    if((eRet == MI_OK) && (stOutputParams.u64CallbackId != 0))
    {
        SPLAYER_DBG_PRINT(" MI_MM_RegisterCallback Success \n");
    }
    else
    {
        SPLAYER_DBG_ERROR("MI_MM_RegisterCallback Fail,eRet :%d!!\n",eRet);
    }

    stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;  //////ADI type
    eRet = MI_MM_SetAttr(psPlayer->h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (VOID *)&stApParams);
    if(eRet>=MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR("Set AP mode Failure!!\n");
    }

    if(psPlayer->e_type == APPL_SPLAYER_MEDIA_MOVIE)
    {
        // 7. Get display handle.
        if(_appl_splayer_get_disp_handle(&psPlayer->h_Disp_Hdl,0) == FALSE)
        {
            SPLAYER_DBG_ERROR("_appl_splayer_get_disp_handle Fail \r\n");
        }

        MI_DISP_ConnectedConds_t stDispConds = {0};
        MI_U32 u32ConnectedNum = 0;
        stDispConds.bIsInput = TRUE;
        stDispConds.u32Module = MI_MODULE_TYPE_VIDEO;
        if(MI_DISP_GetConnectedNum(psPlayer->h_Disp_Hdl, &stDispConds, &u32ConnectedNum) != MI_OK)
        {
            SPLAYER_DBG_ERROR(" Fail at h_Disp_Hdl 0x%x!!\n",psPlayer->h_Disp_Hdl);
        }
        SPLAYER_DBG_INFO(" get h_Disp_Hdl : 0x%x \r\n",psPlayer->h_Disp_Hdl);
    }

    // 8. Get audio out handle.
    if ( _appl_splayer_get_aout_handle(&psPlayer->h_AOut_Hdl) == FALSE)
    {
        SPLAYER_DBG_ERROR(" Fail at _appl_splayer_get_aout_handle \n");
    }

    /*Jundi add for resolving the problem of preview size*/
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)(psPlayer->pvPara);
    DBG_LOG_PRINT(("[Jundi][%s %d]pt_this->t_present_mode == %d\n",__FUNCTION__,__LINE__,pt_this->t_present_mode));
    if(MMP_FP_PRESENT_MODE_PREVIEW == pt_this->t_present_mode)
    {
        MI_DISP_VidWinRect_t stOutRect;
        stOutRect.u16X = 572 * 2;
        stOutRect.u16Y = 4*2;
        stOutRect.u16Width = 590*2;
        stOutRect.u16Width = ALIGN_N(stOutRect.u16Width,32);
        stOutRect.u16Height = 268*2;
        stOutRect.u16Height = ALIGN_N(stOutRect.u16Height,16);

        CHECK_RET(MI_DISP_SetMute(psPlayer->h_Disp_Hdl, E_MI_DISP_MUTE_FLAG_SET_WINDOW),"MI_DISP_SetMute");

        CHECK_RET(MI_DISP_SetOutputRect(psPlayer->h_Disp_Hdl, &stOutRect),"MI_DISP_SetOutputRect");
        eRet = MI_DISP_ApplySetting(psPlayer->h_Disp_Hdl);

        if(eRet == MI_ERR_NOT_SUPPORT)
        {
            SPLAYER_DBG_ERROR("Scaling Down Size exceed HW limitation: DEC Rate\n");
        }
        else
        {
            SPLAYER_DBG_INFO(" eRet:%d, MI_DISP_ApplySetting successed\n",eRet);
        }
        CHECK_RET(MI_DISP_SetUnMute(psPlayer->h_Disp_Hdl, E_MI_DISP_MUTE_FLAG_SET_WINDOW),"MI_DISP_SetUnMute");
    }
#endif
    if(psPlayer->h_MI_MM_Hdl == NULL_HANDLE)
    {
        SPLAYER_DBG_ERROR("psPlayer->h_MI_MM_Hdl is Null\n");
        return APPL_SPLAYER_FAILED;
    }
    else
    {
        DBG_LOG_PRINT(("[%s %d]psPlayer->h_MI_MM_Hdl == %d\n",__FUNCTION__,__LINE__,psPlayer->h_MI_MM_Hdl));
        DBG_LOG_PRINT(("[%s %d]psPlayer->h_AOut_Hdl == %d\n",__FUNCTION__,__LINE__,psPlayer->h_AOut_Hdl));
        DBG_LOG_PRINT(("[%s %d]psPlayer->h_Disp_Hdl == %d\n",__FUNCTION__,__LINE__,psPlayer->h_Disp_Hdl));
        DBG_LOG_PRINT(("[%s %d]psPlayer->u64CallbackId == %d\n",__FUNCTION__,__LINE__,psPlayer->u64CallbackId));
        // 8. start mi mm.
        MI_MM_StartParams_t stStartParams;
        c_memset(&stStartParams, 0, sizeof(stStartParams));
        stStartParams.bMuteAudio = FALSE;
        stStartParams.bPreviewEnable=FALSE;
        stStartParams.pu8DirMemInputBuf =(MI_U8 *)0;
        stStartParams.u32DirMemInputBufLen = 0;
        stStartParams.stPreviewSetting.eMode=E_MI_MM_PREVIEW_NORMAL_MODE;
        stStartParams.stPreviewSetting.u32VideoPauseTime=0;
        stStartParams.bInitOnly = TRUE;
        stStartParams.bSecureModeEnable = FALSE;
        stStartParams.hDisplay = psPlayer->h_Disp_Hdl;
        stStartParams.hAout = psPlayer->h_AOut_Hdl;
        MI_AOUT_MuteParams_t    stAoutMuteParams = {0};
        stAoutMuteParams.bMute = FALSE;
        stAoutMuteParams.eType = E_MI_AOUT_MUTE_BY_USER;
        if(MI_AOUT_SetMute(psPlayer->h_AOut_Hdl, &stAoutMuteParams) != MI_OK)
        {
            SPLAYER_DBG_ERROR("error return. unmute audio stream failed \n");
        }
        else
        {
            SPLAYER_DBG_PRINT("MI_AOUT_SetMute(unmute) before start() ok \n");
        }

        CHAR *pu1URI =c_mem_calloc(1,c_strlen(psPlayer->filePath)+2);
        if(pu1URI == NULL)
        {
            SPLAYER_DBG_ERROR("c_mem_calloc failed \n");
            return APPL_SPLAYER_FAILED;
        }
        c_strcpy(pu1URI,psPlayer->filePath);
        SPLAYER_DBG_PRINT("pu1URI %s!!\n",pu1URI);
        CHAR* p_file_name = c_strstr(pu1URI,"file://");
        SPLAYER_DBG_PRINT("p_file_name %s!!\n",p_file_name);
        if(pu1URI[0] == '/') //////local usb file
        {
            stStartParams.eFileOption=E_MI_MM_FILE_MODE;
            stStartParams.pszFileName=(MI_U8*)pu1URI;
        }
        else
        {
            if(p_file_name != NULL)
            {
                stStartParams.eFileOption = E_MI_MM_FILE_MODE;
                stStartParams.pszFileName=(MI_U8*)p_file_name + 7/*remove file://*/;
            }
            else
            {
                stStartParams.eFileOption=E_MI_MM_FILE_MODE;
                stStartParams.pszFileName=(MI_U8*)"CMPB_HTTP_PULL";
            }
        }
        SPLAYER_DBG_INFO("pszFileName %s,len %d!!\n", stStartParams.pszFileName,sizeof(stStartParams.pszFileName));
        eRet = MI_MM_Start(psPlayer->h_MI_MM_Hdl, &stStartParams);
        if(eRet >= MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" MI_MM_Start failed, mi_mm_hdl=%d, ret = %d \n",psPlayer->h_MI_MM_Hdl,eRet);
            c_mem_free(pu1URI);
            return APPL_SPLAYER_FAILED;
        }
        c_mem_free(pu1URI);
    }
    return APPL_SPLAYER_SUCCESS;
}

static INT32 _appl_splayer_playAV_Async(P_APPL_SPLAYER_T psPlayer)
{
    SPLAYER_DBG_PRINT("Enter ");
    NAV_ASSERT(NULL != psPlayer && NULL != psPlayer->filePath);

    INT32 i4_ret = APPL_SPLAYER_FAILED;
    do
    {
        i4_ret = _appl_splayer_playAV(psPlayer);
        if(i4_ret == APPL_SPLAYER_SUCCESS)
            return i4_ret;
    } while (0);

    // play failed, free resource
    SPLAYER_DBG_ERROR("sPlayer play failed, clean up");
    _appl_splayer_closeAV(psPlayer);

    return i4_ret;
}

static VOID  _appl_splayer_closeAV(P_APPL_SPLAYER_T psPlayer)
{
    SPLAYER_DBG_PRINT("Enter ");
    NAV_ASSERT(NULL != psPlayer);

    MI_RESULT e_ret;

    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        e_ret = MI_MM_Stop(psPlayer->h_MI_MM_Hdl);

        SPLAYER_LOG_ON_FAIL(e_ret);
        _appl_splayer_mi_mm_unregister(psPlayer);

        e_ret = MI_MM_Close(psPlayer->h_MI_MM_Hdl);
        SPLAYER_LOG_ON_FAIL(e_ret);
    }

    SPLAYER_DBG_PRINT("sPlayer play, clean up");
    psPlayer->h_MI_MM_Hdl = NULL_HANDLE;
    psPlayer->isPlay = FALSE;
}

static BOOL _appl_splayer_get_disp_handle(MI_HANDLE *phDisp,UINT16 ui2_idx)
{
    char szWinName[32] = {0};
    MI_DISP_QueryHandleParams_t stDispQueryHandleParams = {0};
    MI_DISP_OpenParams_t stDispOpenParams = {E_MI_DISP_VIDWIN_HD, 0};

    c_snprintf(szWinName, sizeof(szWinName), DISP_HANDLE_STRING_NAME, ui2_idx);

    stDispQueryHandleParams.pszName = (MI_U8*)szWinName;

    if(MI_DISP_GetHandle(&stDispQueryHandleParams, phDisp) != MI_OK)
    {
        stDispOpenParams.pszName = (MI_U8*)szWinName;
        if(MI_DISP_Open(&stDispOpenParams, phDisp) != MI_OK)
        {
            SPLAYER_DBG_ERROR("Leave, MI_DISP_Open error\n");
            return FALSE;
        }
    }

    return TRUE;
}


static BOOL _appl_splayer_get_aout_handle(MI_HANDLE *phAout)
{
    MI_AOUT_QueryHandleParams_t stAoutQueryParams = {E_MI_AOUT_PATH_ALL};
    MI_AOUT_OpenParams_t stAoutOpenParams = {0, E_MI_AOUT_PATH_ALL, {FALSE, 0}};

    if(MI_AOUT_GetHandle(&stAoutQueryParams, phAout) != MI_OK)
    {
        if(MI_AOUT_Open(&stAoutOpenParams, phAout) != MI_OK)
        {
            SPLAYER_DBG_ERROR("Leave, MI_AOUT_Open error \n");
            return FALSE;
        }

        if(MI_AOUT_SetVolume(*phAout, 0, 30) != MI_OK)
        {
            SPLAYER_DBG_ERROR("Leave, MI_AOUT_SetVolume error \n");
            return FALSE;
        }
    }

    return TRUE;
}

// module init
static BOOL _appl_splayer_init(VOID)
{
    MI_RESULT eRet = MI_ERR_FAILED;
    MI_U8* psEvtGrpName = (MI_U8*)"PlayerEvnGrp";

    if(_bIsMMModuleInit)
    {
        SPLAYER_DBG_PRINT(" MM already init OK\n");
        return TRUE;
    }

    // Activate MI modules when process first uses MI API.
    eRet = MI_SYS_Init(NULL);
    if (eRet >= MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR("MI_SYS_Init fail!!\n");
        return FALSE;
    }
    else
    {
        SPLAYER_DBG_PRINT(" MM init OK\n");
    }

    // Init MI_DISP
    eRet = MI_DISP_Init(NULL);
    if(eRet >= MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR("MI_DISP_Init fail!!\n");
        return FALSE;
    }
    else
    {
        SPLAYER_DBG_PRINT("MI_DISP_Init ok!!\n");
    }

    // Init MI_AOUT
    eRet = MI_AOUT_Init(NULL);
    if(eRet >= MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR("MI_AOUT_Init fail!!\n");
        return FALSE;
    }
    else
    {
        SPLAYER_DBG_PRINT("MI_AOUT_Init ok!!\n");
    }

    // Init MI_MM
    eRet = MI_MM_Init(NULL);
    if(eRet >= MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR("MI_MM_Init fail!!\n");
        return FALSE;
    }
    else
    {
        SPLAYER_DBG_PRINT("MI_MM_Init ok!!\n");
        _bIsMMModuleInit = TRUE;
    }

    //Create event group for MMP Event
    if (MI_OS_CreateEventGroup(psEvtGrpName, &_s32TaskEventGrpId) != MI_OK)
    {
        SPLAYER_DBG_ERROR("MI_OS_CreateEventGroup fail!!\n");
    }

    SPLAYER_DBG_PRINT("MI_OS_CreateEventGroup _s32TaskEventGrpId: [%d]\n", _s32TaskEventGrpId);

    return TRUE;
}

static VOID _appl_splayer_open(P_APPL_SPLAYER_T psPlayer)
{
    MI_MM_OpenParams_t stOpenParams;
    char szMmName[32] = {0};
    MI_RESULT eRet = MI_ERR_FAILED;
    MI_MM_ApTypeParams_t stApParams;
    SPLAYER_DBG_PRINT("Enter \r\n");

    MI_MM_CHECK_INIT();

    // open MI_MM
    c_memset(&stOpenParams, 0 ,sizeof(stOpenParams));
    c_snprintf(szMmName, sizeof(szMmName), MI_MM_NAME_MODEL);

    stOpenParams.pszName = (MI_U8 *)szMmName;
    stOpenParams.eMediaType = E_MI_MM_MEDIA_PHOTO;

    eRet = MI_MM_Open(&stOpenParams, &psPlayer->h_MI_MM_Hdl);
    SPLAYER_DBG_INFO(" MI_MM_Open h_MI_MM_Hdl:  0x%x ",psPlayer->h_MI_MM_Hdl);

    // set AP mode
    c_memset(&stApParams, 0, sizeof(stApParams));
    stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;

    eRet = MI_MM_SetAttr(psPlayer->h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (VOID *)&stApParams);
    if(eRet >= MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR(" MI_MM_SetAttr error, ret %d ",eRet);
    }

    if (_appl_splayer_get_disp_handle(&psPlayer->h_Disp_Hdl,0) == FALSE  )
    {
        SPLAYER_DBG_ERROR(" _appl_splayer_get_disp_handle ");
    }

    SPLAYER_DBG_INFO(" _appl_splayer_get_disp_handle:  0x%x ",psPlayer->h_Disp_Hdl);

    return ;
}

static BOOL _appl_splayer_get_effect_type(MI_MM_PhotoSlideShowEffect_e* eEffect,P_APPL_SPLAYER_T psPlayer)
{
    *eEffect = E_MI_MM_SLIDE_SHOW_EFFECT_NORMAL + psPlayer->ui4_tfx_idx;
    SPLAYER_DBG_INFO(" eEffect :%d \r\n",*eEffect);
    return TRUE;
}

static BOOL _appl_splayer_get_rotate_angle(MI_MM_RotateAngle_e* eAngle,P_APPL_SPLAYER_T psPlayer)
{
    *eAngle = E_MI_MM_ROTATE_0 + psPlayer->ui4_rotate_angle_idx;
    SPLAYER_DBG_INFO(" eAngle :%d \r\n",*eAngle);

    return TRUE;
}

static BOOL _appl_splayer_get_zoom_value(MI_MM_ViewZoomFactor_e* eZoomFactor,P_APPL_SPLAYER_T psPlayer)
{
    *eZoomFactor = E_MI_MM_VIEW_ZOOM_1X + psPlayer->ui4_zoom_idx;
    SPLAYER_DBG_INFO(" eZoomFactor :%d \r\n",*eZoomFactor);

    return TRUE;
}

static BOOL _appl_splayer_photo_draw(P_APPL_SPLAYER_T psPlayer)
{
    MI_RESULT eRet = MI_ERR_FAILED;

    MI_HANDLE hDisp = MI_HANDLE_NULL;
    MI_DISP_QueryHandleParams_t stDispHandleParam;
    c_memset(&stDispHandleParam, 0, sizeof(MI_DISP_QueryHandleParams_t));
    char szName[MI_MM_NAME_LENGTH] = {0};
    snprintf(szName, sizeof(szName), "MI_DISP_HD0");
    stDispHandleParam.pszName = (MI_U8*)szName;
    SPLAYER_DBG_PRINT("Enter \r\n");

    eRet = MI_DISP_GetHandle(&stDispHandleParam, &hDisp);
    SPLAYER_DBG_INFO("MI_DISP_GetHandle,eRet :%d\r\n",eRet);


    eRet=MI_MM_SetupPhotoDisplay(psPlayer->h_MI_MM_Hdl);
    if(eRet>=MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR(" MI_MM_SetupPhotoDisplay error, ret %d ",eRet);
        goto ERR;
    }

    MI_MM_PhotoSlideShowEffect_e eEffect;
    if (psPlayer->photoOpType == PHOTO_OP_PLAY)
    {
        if(_appl_splayer_get_effect_type(&eEffect, psPlayer) == FALSE)
        {
            SPLAYER_DBG_ERROR(" _appl_splayer_get_effect_type error, ret %d ",eRet);
            goto ERR;
        }
    }
    else
    {
        eEffect = E_MI_MM_SLIDE_SHOW_EFFECT_NORMAL;
    }

    eRet= MI_MM_ClearPhoto(psPlayer->h_MI_MM_Hdl);
    if(eRet>=MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR(" MI_MM_ClearPhoto error, ret %d ",eRet);
        goto ERR;
    }

    eRet= MI_MM_DrawPhoto(psPlayer->h_MI_MM_Hdl, eEffect);
    if(eRet>=MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR(" MI_MM_DrawPhoto error, ret %d ",eRet);
        goto ERR;
    }

    if (psPlayer->photoOpType == PHOTO_OP_ROTATE)
    {
        MI_MM_RotateAngle_e eAngle;
        if(_appl_splayer_get_rotate_angle(&eAngle, psPlayer) == FALSE)
        {
            SPLAYER_DBG_ERROR(" _appl_splayer_get_rotate_angle error, ret %d ",eRet);
            goto ERR;
        }

        eRet= MI_MM_RotatePhoto(psPlayer->h_MI_MM_Hdl, eAngle);
        if(eRet>=MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" MI_MM_RotatePhoto error, ret %d ",eRet);
            goto ERR;
        }
    }

    if (psPlayer->photoOpType == PHOTO_OP_ZOOM)
    {
        MI_MM_ViewZoomFactor_e eZoomFactor;
        if(_appl_splayer_get_zoom_value(&eZoomFactor, psPlayer) == FALSE)
        {
            SPLAYER_DBG_ERROR(" _appl_splayer_get_zoom_value error, ret %d ",eRet);
            goto ERR;
        }

        eRet= MI_MM_ZoomPhoto(psPlayer->h_MI_MM_Hdl, eZoomFactor);
        if(eRet>=MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" MI_MM_ZoomPhoto error, ret %d ",eRet);
            goto ERR;

        }
    }

    eRet = MI_DISP_SetUnMute(hDisp, E_MI_DISP_MUTE_FLAG_VIDEO);

    SPLAYER_DBG_PRINT("_PhotoDraw Complete \n");

    return TRUE;
ERR:
    eRet = MI_MM_Stop(psPlayer->h_MI_MM_Hdl);

    SPLAYER_DBG_PRINT("_PhotoDraw Fail \n");
    return FALSE;
}

static INT32 _appl_splayer_pre_start(P_APPL_SPLAYER_T psPlayer)
{
    MI_RESULT                    eRet = MI_ERR_FAILED;
    MI_MM_CallbackInputParams_t  stInputParams;
    MI_MM_CallbackOutputParams_t stOutputParams;
    MI_MM_StartParams_t          stStartParams;
    MI_MM_ApTypeParams_t         stApParams;
    SPLAYER_DBG_PRINT("Enter h_MI_MM_Hdl:0x%x \n",psPlayer->h_MI_MM_Hdl);

    stInputParams.pfEventCallback = _appl_splayer_callback;
    stInputParams.u32EventFlags   = E_MI_MM_EVENT_ALL;
    stInputParams.u64CallbackId = 0;
    stInputParams.pUserParams = (VOID*)psPlayer;
    eRet = MI_MM_RegisterCallback(psPlayer->h_MI_MM_Hdl, &stInputParams, &stOutputParams);

    psPlayer->u64CallbackId = stOutputParams.u64CallbackId;

    SPLAYER_DBG_PRINT(" u64CallbackId:(0x%llx) \n",psPlayer->u64CallbackId);

    if((eRet == MI_OK) && (stOutputParams.u64CallbackId != 0))
    {
        SPLAYER_DBG_PRINT(" MI_MM_RegisterCallback u64CallbackId:(0x%llx) \n",psPlayer->u64CallbackId);
    }
    else
    {
        SPLAYER_DBG_ERROR(" MI_MM_RegisterCallback error, ret %d ",eRet);
    }

    stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;  //////ADI type
    eRet = MI_MM_SetAttr(psPlayer->h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (VOID *)&stApParams);
    if(eRet>=MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR(" MI_MM_SetAttr error, ret %d ",eRet);
    }

    //setting play parameter
    c_memset(&stStartParams, 0, sizeof(stStartParams));
    stStartParams.pu8DirMemInputBuf =(MI_U8 *)0;
    stStartParams.u32DirMemInputBufLen = 0;
    stStartParams.bPreviewEnable=0;
    stStartParams.bInitOnly=0;
    stStartParams.stPreviewSetting.eMode=E_MI_MM_PREVIEW_NORMAL_MODE ; // no use
    stStartParams.stPreviewSetting.u32VideoPauseTime=0;
    stStartParams.eFileOption=E_MI_MM_FILE_MODE;
    stStartParams.pszFileName=(MI_U8*)(psPlayer->filePath);
    stStartParams.bMuteAudio=FALSE;
    stStartParams.hDisplay = psPlayer->h_Disp_Hdl;
#ifdef NEVER
    stStartParams.hAout = psPlayer->h_AOut_Hdl;
#endif /* NEVER */

    SPLAYER_DBG_INFO(" pszFileName %s,len %d!!\n", stStartParams.pszFileName,sizeof(stStartParams.pszFileName));
    eRet = MI_MM_Start(psPlayer->h_MI_MM_Hdl, &stStartParams);
    if(eRet >= MI_ERR_FAILED)
    {
        SPLAYER_DBG_ERROR(" call MI_MM_Start failed, mi_mm_hdl=%x, ret = %d \n",psPlayer->h_MI_MM_Hdl,eRet);
    }

    return APPL_SPLAYER_SUCCESS;

}
static INT32 _appl_splayer_playPhoto(P_APPL_SPLAYER_T psPlayer)
{
    SPLAYER_DBG_PRINT("Enter \r\n");
    NAV_ASSERT(NULL != psPlayer && NULL != psPlayer->filePath);

    do
    {
        _appl_splayer_open(psPlayer);

        _appl_splayer_pre_start(psPlayer);

        _appl_splayer_photo_draw(psPlayer);

        return APPL_SPLAYER_SUCCESS;
    } while (0);
}

static VOID  _appl_splayer_closePhoto(P_APPL_SPLAYER_T psPlayer)
{
    SPLAYER_DBG_PRINT("Enter \r\n");
    NAV_ASSERT(NULL != psPlayer);
    MI_RESULT e_ret;
    // close cmpb handle
    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        MI_MM_ClearPhoto(psPlayer->h_MI_MM_Hdl);
        e_ret = MI_MM_Stop(psPlayer->h_MI_MM_Hdl);
        SPLAYER_LOG_ON_FAIL(e_ret);

        _appl_splayer_mi_mm_unregister(psPlayer);

        e_ret = MI_MM_Close(psPlayer->h_MI_MM_Hdl);
        SPLAYER_LOG_ON_FAIL(e_ret);
    }
    psPlayer->h_MI_MM_Hdl = NULL_HANDLE;
    psPlayer->isPlay = FALSE;
}


INT32 appl_splayer_start_play(
        APPL_SPLAYER_PLAY_EVENT eEventType, VOID* pvTag, uint32_t u4Data)
{
    MI_RESULT               eRet = MI_ERR_FAILED;
    P_APPL_SPLAYER_T psPlayer = (P_APPL_SPLAYER_T)pvTag;
    NAV_ASSERT(NULL != pvTag);
    SPLAYER_DBG_PRINT("Enter \r\n");

    eRet = MI_MM_Resume(psPlayer->h_MI_MM_Hdl);
    SPLAYER_DBG_PRINT(" MI_MM_Resume eRet %d\r\n",eRet);
    psPlayer->isPlay = TRUE;

  return 0;
}

MI_RESULT _appl_splayer_callback(
                       MI_HANDLE          h_MI_Hdl,
                       MI_U32            eEventType,
                       VOID             *pNotifyParams,
                       VOID             *pUserParams)


{
    MI_RESULT e_ret;
    P_APPL_SPLAYER_T psPlayer = (P_APPL_SPLAYER_T)pUserParams;
    // translate event
    APPL_SPLAYER_PLAY_EVENT playEvent;
    switch (eEventType)
    {
        case E_MI_MM_EVENT_EXIT_OK:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_EXIT_OK\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_EXIT_OK;
            break;

        case E_MI_MM_EVENT_EXIT_FORCE:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_EXIT_FORCE\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_EXIT_FORCE;
            break;

        case E_MI_MM_EVENT_EXIT_ERROR_FILE:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_EXIT_ERROR_FILE\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_EXIT_ERROR_FILE;
            break;

        case E_MI_MM_EVENT_SUFFICIENT_DATA:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_SUFFICIENT_DATA\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_SUFFICIENT_DATA;
            break;

        case E_MI_MM_EVENT_INSUFFICIENT_DATA:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_INSUFFICIENT_DATA\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_INSUFFICIENT_DATA;
            break;

        case E_MI_MM_EVENT_PLAYING_INIT_OK:
        {
            SPLAYER_DBG_PRINT("recv E_MI_MM_EVENT_PLAYING_INIT_OK\r\n");
            if (psPlayer->e_type == APPL_SPLAYER_MEDIA_MOVIE)
            {
                MI_MM_MovieInfo_t       stMovieInfo;
                c_memset(&stMovieInfo,0,sizeof(MI_MM_MovieInfo_t));
                e_ret = MI_MM_GetMovieInfo(psPlayer->h_MI_MM_Hdl,&stMovieInfo);
                if(e_ret < MI_ERR_FAILED)
                {
					_MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)(psPlayer->pvPara);
					DBG_LOG_PRINT(("[chonghuang][%s %d] pt_this->t_present_mode = %d !!!\n",__FUNCTION__,__LINE__,pt_this->t_present_mode));
					if(MMP_FP_PRESENT_MODE_FULL == pt_this->t_present_mode)
					{
						_mmp_video_equal_proportion_zoom();
					}
                    SPLAYER_DBG_PRINT(" t_resolution.ui4_width = %d !!!\n",(int)stMovieInfo.u32MovieWidth);
                    SPLAYER_DBG_PRINT(" t_resolution.ui4_height = %d !!!\n",(int)stMovieInfo.u32MovieHeight);
                    SPLAYER_DBG_PRINT(" t_resolution.ui4_aspect_ratio_w = %d !!!\n",(int)stMovieInfo.u32MovieDarWidth);
                    SPLAYER_DBG_PRINT(" t_resolution.ui4_aspect_ratio_h = %d !!!\n",(int)stMovieInfo.u32MovieDarHeight);
                    SPLAYER_DBG_PRINT(" total time valid = %d, total time = %d !!!\n",stMovieInfo.bTotalTimeValid, stMovieInfo.u32TotalTime);
                }
                else
                {
                    SPLAYER_DBG_ERROR(" get MI_MM_GetMovieInfo failed ret = %d !!!\n",(int)e_ret);
                }
            }
            else if(psPlayer->e_type == APPL_SPLAYER_MEDIA_MUSIC)
            {
                MI_MM_MusicInfo_t       stInfo;
                c_memset(&stInfo,0,sizeof(MI_MM_MusicInfo_t));
                e_ret = MI_MM_GetMusicInfo(psPlayer->h_MI_MM_Hdl,&stInfo);
                if(e_ret < MI_ERR_FAILED)
                {
                    SPLAYER_DBG_PRINT(" .u32TotalTime = %d !!!\n",(int)stInfo.u32TotalTime);
                    SPLAYER_DBG_PRINT(" .u32CurentTime = %d !!!\n",(int)stInfo.u32CurentTime);
                    SPLAYER_DBG_PRINT(" .bPictureExist = %d !!!\n",(int)stInfo.bPictureExist);
                }
                else
                {
                    SPLAYER_DBG_ERROR(" get MI_MM_GetMusicInfo failed ret = %d !!!\n",(int)e_ret);
                }

                //check music basic info
                {

                    MI_U32                  u32MsTime  = 0;
                    MI_MM_MusicStringInfo_t tMusicStrInfo;
                    CHAR    szYear[YEAR_LENGTH];
                    CHAR    szMetadataTitle [MAX_METADATA_STRING_LENGTH];
                    CHAR    szMetadataArtist[MAX_METADATA_STRING_LENGTH];
                    CHAR    szMetadataGenre [MAX_METADATA_STRING_LENGTH];
                    CHAR    szMetadataAlbum [MAX_METADATA_STRING_LENGTH];
                    e_ret = MI_MM_GetDuration(psPlayer->h_MI_MM_Hdl, &u32MsTime);
                    if(MI_OK != e_ret)
                    {
                        SPLAYER_DBG_ERROR(" get MI_MM_GetDuration failed ret = %d !!!\n",(int)e_ret);
                    }

                    SPLAYER_DBG_PRINT("get duration of %d\n", u32MsTime);
                    // get title
                    c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_TITLE,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    if(e_ret >= MI_ERR_FAILED)
                    {
                        SPLAYER_DBG_ERROR(" get Title failed ret = %d \n", e_ret);
                    }
                    else
                    {
                        //c_strncpy((char*)ptMediaInfo->szMetadataTitle, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                        c_memcpy((VOID *)(szMetadataTitle),
                            (VOID *)(long)(tMusicStrInfo.virtStringAddr),
                            tMusicStrInfo.u32StringLen);
                    }

                    SPLAYER_DBG_PRINT(" get Title = %s \n", szMetadataTitle);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.u32StringLen = %d \n", tMusicStrInfo.u32StringLen);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.virtStringAddr = %lld \n", tMusicStrInfo.u32StringLen);
                    // get artist
                    c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_ARTIST,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    if(e_ret >= MI_ERR_FAILED)
                    {
                        SPLAYER_DBG_ERROR(" get Artist failed ret = %d \n", e_ret);
                    }
                    else
                    {
                        //c_strncpy((char*)ptMediaInfo->szMetadataArtist, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                        c_memcpy((VOID *)(szMetadataArtist),
                            (VOID *)(long)(tMusicStrInfo.virtStringAddr),
                            tMusicStrInfo.u32StringLen);
                    }
                    SPLAYER_DBG_PRINT(" get Artist = %s \n", szMetadataArtist);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.u32StringLen = %d \n", tMusicStrInfo.u32StringLen);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.virtStringAddr = %lld \n", tMusicStrInfo.u32StringLen);

                    // get genre
                    c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_GENRE,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    if(e_ret >= MI_ERR_FAILED)
                    {
                        SPLAYER_DBG_ERROR(" get Genre failed ret = %d \n", e_ret);
                    }
                    else
                    {
                        //c_strncpy((char*)ptMediaInfo->szMetadataGenre, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                        c_memcpy((VOID *)(szMetadataGenre),
                            (VOID *)(long)(tMusicStrInfo.virtStringAddr),
                            tMusicStrInfo.u32StringLen);
                    }
                    SPLAYER_DBG_PRINT(" get Genre = %s \n", szMetadataGenre);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.u32StringLen = %d \n", tMusicStrInfo.u32StringLen);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.virtStringAddr = %lld \n", tMusicStrInfo.u32StringLen);
                    // get Album
                    c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_ALBUM,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    if(e_ret >= MI_ERR_FAILED)
                    {
                        SPLAYER_DBG_ERROR(" get Album failed ret = %d \n", e_ret);
                    }
                    else
                    {
                        //c_strncpy((char*)ptMediaInfo->szMetadataAlbum, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                        c_memcpy((VOID *)(szMetadataAlbum),
                            (VOID *)(long)(tMusicStrInfo.virtStringAddr),
                            tMusicStrInfo.u32StringLen);
                    }
                    SPLAYER_DBG_PRINT(" get Album = %s \n", szMetadataAlbum);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.u32StringLen = %d \n", tMusicStrInfo.u32StringLen);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.virtStringAddr = %lld \n", tMusicStrInfo.u32StringLen);
                    // get year
                    c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_YEAR,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    if(e_ret >= MI_ERR_FAILED)
                    {
                        SPLAYER_DBG_ERROR(" get Year failed ret = %d \n", e_ret);
                    }
                    else
                    {
                        //c_strncpy((char*)ptMediaInfo->szYear, (char*)(tMusicStrInfo.virtStringAddr),  MAX_METADATA_STRING_LENGTH-1);
                        c_memcpy((VOID *)(szYear),
                            (VOID *)(long)(tMusicStrInfo.virtStringAddr),
                            tMusicStrInfo.u32StringLen);
                    }
                    SPLAYER_DBG_PRINT(" get Year = %s \n", szYear);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.u32StringLen = %d \n", tMusicStrInfo.u32StringLen);
                    SPLAYER_DBG_PRINT(" get tMusicStrInfo.virtStringAddr = %lld \n", tMusicStrInfo.u32StringLen);
                }

            }
            playEvent = SPLAYER_MM_EVENT_PLAYING_INIT_OK;
            break;
        }

        case E_MI_MM_EVENT_FRAME_READY:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_FRAME_READY\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_FRAME_READY;
            break;


        case E_MI_MM_EVENT_START_PLAY:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_START_PLAY\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_START_PLAY;
            break;

        case E_MI_MM_EVENT_PLAYING_OK:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PLAYING_OK\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PLAYING_OK;
            break;

        case E_MI_MM_EVENT_PROGRAM_CHANGED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PROGRAM_CHANGED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PROGRAM_CHANGED;
            break;


        case E_MI_MM_EVENT_AUDIO_TRACK_CHANGED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_AUDIO_TRACK_CHANGED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_AUDIO_TRACK_CHANGED;
            break;

        case E_MI_MM_EVENT_BACKWARD_TO_START:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_BACKWARD_TO_START\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_BACKWARD_TO_START;
            break;

        case E_MI_MM_EVENT_CLEAR_DATA_READY:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_CLEAR_DATA_READY\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_CLEAR_DATA_READY;
            break;

        case E_MI_MM_EVENT_AUDIO_UNSUPPORTED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_AUDIO_UNSUPPORTED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_AUDIO_UNSUPPORTED;
            break;

        case E_MI_MM_EVENT_AUDIO_ONLY:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_AUDIO_ONLY\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_AUDIO_ONLY;
            break;

        case E_MI_MM_EVENT_SEEK_ACK:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_SEEK_ACK\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_SEEK_ACK;
            break;


        case E_MI_MM_EVENT_TRICK_ACK:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_TRICK_ACK\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_TRICK_ACK;
            break;

        case E_MI_MM_EVENT_BLACK_SCREEN_OFF:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_BLACK_SCREEN_OFF\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_BLACK_SCREEN_OFF;
            break;

        case E_MI_MM_EVENT_THUMBNAIL_DECODE_DONE:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_THUMBNAIL_DECODE_DONE\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_THUMBNAIL_DECODE_DONE;
            break;


        case E_MI_MM_EVENT_THUMBNAIL_DECODE_FAIL:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_THUMBNAIL_DECODE_FAIL\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_THUMBNAIL_DECODE_FAIL;
            break;

        case E_MI_MM_EVENT_VIDEO_TRACK_CHANGED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_VIDEO_TRACK_CHANGED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_VIDEO_TRACK_CHANGED;
            break;

        case E_MI_MM_EVENT_VIDEO_RENDER_BUFFER_UNDERFLOW:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_VIDEO_RENDER_BUFFER_UNDERFLOW\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_VIDEO_RENDER_BUFFER_UNDERFLOW;
            break;

        case E_MI_MM_EVENT_VIDEO_UNSUPPORTED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_VIDEO_UNSUPPORTED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_VIDEO_UNSUPPORTED;
            break;

        case E_MI_MM_EVENT_PHOTO_DECODE_DONE:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PHOTO_DECODE_DONE\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PHOTO_DECODE_DONE;
            break;

        case E_MI_MM_EVENT_PHOTO_DECODE_FAILED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PHOTO_DECODE_FAILED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PHOTO_DECODE_FAILED;
            break;


        case E_MI_MM_EVENT_PHOTO_DECODING_NEXT:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PHOTO_DECODING_NEXT\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PHOTO_DECODING_NEXT;
            break;

        case E_MI_MM_EVENT_PHOTO_DISPLAYED:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PHOTO_DISPLAYED\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PHOTO_DISPLAYED;
            break;

        case E_MI_MM_EVENT_PHOTO_DECODE_ONE_FRAME_DONE:
            DBG_LOG_PRINT(("[%s %d]E_MI_MM_EVENT_PHOTO_DECODE_ONE_FRAME_DONE\n",__FUNCTION__,__LINE__));
            playEvent = SPLAYER_MM_EVENT_PHOTO_DECODE_ONE_FRAME_DONE;
            break;
        default :
            SPLAYER_DBG_PRINT("recv eEventType %d\r\n",eEventType);
            return MI_ERR_FAILED;
    }
    if (NULL != psPlayer->pfCallback)
        psPlayer->pfCallback(playEvent, pUserParams, 0,psPlayer->pvPara);

    return 0;
}

#ifdef NEVER
static VOID _appl_splayer_imageCallback(HANDLE_T h_handle, const VOID* pv_tag,
        IMG_NFY_EVENT_TYPE_T e_event, const VOID* pv_data)
{
}

static VOID _appl_splayer_usbNotify(VOID *pv_tag,
    RMV_DEV_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    NAV_ASSERT(NULL != pv_tag);

    // check dev removed
    if (RMV_DEV_NFY_ID_DEVICE_REMOVED != e_nfy_id)
        return;

    // check open id
    RMV_DEV_NFY_REC_T *devRecord = (RMV_DEV_NFY_REC_T *)pv_nfy_param;
    P_APPL_SPLAYER_T pPlayer = (P_APPL_SPLAYER_T)pv_tag;
    if (devRecord->t_open_id != pPlayer->openid)
        return;

    // notify media lost
    if (NULL != pPlayer->pfCallback)
        pPlayer->pfCallback(APPL_SPLAYER_PLAY_EVENT_MEDIA_LOST, pv_tag, 0);
}

static INT32 _appl_splayer_openUSBPoint(const CHAR *path,
    RMV_DEV_OPEN_ID_T *openid)
{
    NAV_ASSERT(NULL != path && NULL != openid);

    UINT32 mountCount = 0;
    INT32 i4_ret = 0;
    INT32 bufferSize = MAX_FILE_PATH_LEN - 1;
    CHAR pathBuffer[MAX_FILE_PATH_LEN];
    i4_ret = a_rmv_dev_get_mnt_count(&mountCount);
    if (RMVR_OK != i4_ret)
    {
        SPLAYER_LOG("Cannot get mnt count: %d\n", i4_ret);
        return APPL_SPLAYER_FAILED;
    }
    UINT32 i = 0;
    // find mount point index by comparing path prefix
    for (; i < mountCount; i++)
    {
        i4_ret = a_rmv_dev_get_mnt_point(i, (SIZE_T *)&bufferSize, pathBuffer);
        if (RMVR_OK != i4_ret)
        {
            SPLAYER_LOG("Cannot get mount point at %d with ret %d\n", i, i4_ret);
            continue;
        }
        if (c_strlen(pathBuffer) < c_strlen(path))
            if (0 == c_strncmp(pathBuffer, path, c_strlen(pathBuffer)))
                break;
    }

    // get mount point
    if (i == mountCount)
    {
        SPLAYER_LOG("Cannot find proper mount point\n");
        return APPL_SPLAYER_FAILED;
    }
    i4_ret = a_rmv_dev_open_mnt_point(i, openid);
    if (RMVR_OK != i4_ret)
    {
        SPLAYER_LOG("Cannot open mount point at index %d: %d\n", i, i4_ret);
        *openid = RMV_DEV_NULL_OPEN_ID;
        return APPL_SPLAYER_FAILED;
    }

    return APPL_SPLAYER_SUCCESS;
}
#endif /* NEVER */

static APPL_SPLAYER_FILE_T _appl_splayer_getFileType(const CHAR *filePath)
{
    NAV_ASSERT(NULL != filePath);

    // get file ext
    const CHAR *iterExt = filePath + c_strlen(filePath);
    while (iterExt-- != filePath) {
    if (*iterExt == '.')
    {
        iterExt++;
        break;
    }
    }
    INT32 i = 0;

    //jundi add the code to convert "A~Z" to "a~z"
    CHAR iterExt1[EXT_LEN];
    c_strcpy(iterExt1, iterExt);
    while(iterExt1[i] != '\0')
    {
        if(iterExt1[i] >= 'A' && iterExt1[i] <= 'Z')
            iterExt1[i] = iterExt1[i] + 32;
        i++;
    }

    APPL_SPLAYER_FILE_T fileType = APPL_SPLAYER_FILE_UNKNOWN;
    // compare with av
    for (i = 0; i < APPL_SPLAYER_AV_EXT_NUM; i++) {
        if (c_strcmp(_ag_avExtList[i], iterExt1) == 0)
        {
            fileType = APPL_SPLAYER_FILE_AV;
            return fileType;
        }
    }
    // compare with photo
    for (i = 0; i < APPL_SPLAYER_PHOTO_EXT_NUM; i++) {
        if (c_strcmp(_ag_photoExtList[i], iterExt1) == 0)
        {
            fileType = APPL_SPLAYER_FILE_PHOTO;
            return fileType;
        }
    }

    return fileType;
}

static BOOL _appl_splayer_isFileExist(const CHAR *filePath)
{
    BOOL isExist = FALSE;
    HANDLE_T hFile = NULL_HANDLE;

    INT32 i4_ret = c_fm_open(FM_ROOT_HANDLE, filePath,
            FM_READ_ONLY, 0777, FALSE, &hFile);
    if (FMR_OK == i4_ret && NULL_HANDLE != hFile)
    {
        isExist = TRUE;
        i4_ret = c_fm_close(hFile);
        if (FMR_OK != i4_ret)
            SPLAYER_LOG("Cannot close file handle %p\n", hFile);
    }

    return isExist;
}

#ifdef NEVER
static BOOL _appl_splayer_isPlayUSB(const CHAR *filePath)
{
    NAV_ASSERT(NULL != filePath);

    BOOL isPlayUSB = FALSE;
    if (c_strlen(filePath) > c_strlen(SPLAYER_USB_PREFIX))
        isPlayUSB = 0 == c_strncmp(filePath, SPLAYER_USB_PREFIX,
            c_strlen(SPLAYER_USB_PREFIX));

    return isPlayUSB;
}
#endif /* NEVER */

static BOOL _appl_splayer_mi_mm_unregister(P_APPL_SPLAYER_T psPlayer)
{
    MI_RESULT eRet = MI_ERR_FAILED;
    MI_MM_CallbackInputParams_t stInputParams;

    c_memset(&stInputParams, 0, sizeof(stInputParams));

    stInputParams.u64CallbackId = psPlayer->u64CallbackId;
    SPLAYER_DBG_PRINT(" u64CallbackId :(0x%llx)\r\n",stInputParams.u64CallbackId);

    if(stInputParams.u64CallbackId != 0)
    {
        eRet = MI_MM_UnRegisterCallback(psPlayer->h_MI_MM_Hdl, &stInputParams);
        if(eRet != MI_OK)
        {
            SPLAYER_DBG_ERROR(" MI_MM_UnRegisterCallback Fail ,eRet :%d,hMm(0x%x), u64CallbackId(0x%llx) fail to MI_MM_UnRegisterCallback()\n", eRet, psPlayer->h_MI_MM_Hdl, stInputParams.u64CallbackId);
            return FALSE;
        }
    }

    return TRUE;
}
static INT32 _appl_splayer_get_movie_info(P_APPL_SPLAYER_T psPlayer,APPL_SPLAYER_MOVIE_INFO_T *ptMovieInfo)
{
    INT32 i4_ret = MI_ERR_FAILED;

    SPLAYER_DBG_PRINT("Enter \r\n");
    MI_MM_MovieInfo_t tMovieInfo;
    c_memset(&tMovieInfo, 0, sizeof(tMovieInfo));
    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        UTF16_T    w2s[64] = {0} ;
        INT32	   eRet = -1;
        BOOL       isDTS=TRUE;
        MI_AUDIO_Caps_t stAudioCaps;
        memset(&stAudioCaps,0,sizeof(MI_AUDIO_Caps_t));
        MI_AUDIO_CodecType_e *peCodecType = (MI_AUDIO_CodecType_e *)calloc(stAudioCaps.u32DecoderNum,sizeof(MI_AUDIO_CodecType_e));
        MI_AUDIO_DtsVersion_e *eDtsVersion = (MI_AUDIO_DtsVersion_e *)calloc(1, sizeof(MI_AUDIO_DtsVersion_e));

        i4_ret = MI_MM_GetMovieInfo(psPlayer->h_MI_MM_Hdl,&tMovieInfo);
        if(MI_OK != i4_ret)
        {
             SPLAYER_DBG_ERROR(" Fail atMI_MM_GetMovieInfo \r\n");
        }
        ptMovieInfo->ui4_total_time = (UINT32)tMovieInfo.u32TotalTime;
        ptMovieInfo->u32MovieWidth = (UINT32)tMovieInfo.u32MovieWidth;
        ptMovieInfo->u32MovieHeight = (UINT32)tMovieInfo.u32MovieHeight;
        /*get dts version*/
        eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_DTS_VERSION, NULL, eDtsVersion);
        if(MI_OK != eRet)
        {
             SPLAYER_DBG_ERROR(" Fail at Get Audio DTS Version\r\n");
        }
        eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_CODEC_TYPE, NULL, peCodecType);
        if(MI_OK != eRet)
        {
             SPLAYER_DBG_ERROR(" Fail at Get Audio Codec type from MI_Audio\r\n");
        }
        DBG_LOG_PRINT((" sysinfo eDtsVersion = %d \n",*eDtsVersion));
        DBG_LOG_PRINT((" sysinfo peCodecType = %d \n",*peCodecType));

        switch(*peCodecType)
        {
            case E_MI_AUDIO_CODEC_TYPE_DTS:
            {
                c_strncpy(ptMovieInfo->audioCodec,"DTS",AUDIO_CODEC_LEN -1);
                ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS;
                break;
            }
            case E_MI_AUDIO_CODEC_TYPE_DTS_LBR:
            {
                EnuCusModelSeries eModel = a_cfg_cust_get_CurModelSeries();
                if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                }
                else if ((eModel == CUS_MODEL_2021_83_2K_D_HD) || (eModel == CUS_MODEL_2021_83_2K_D_FHD) || (eModel == CUS_MODEL_2022_83_2K_D))
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                }
                else
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS Express",AUDIO_CODEC_LEN -1);
                }
                ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS_LBR;
                break;
            }
            case E_MI_AUDIO_CODEC_TYPE_DTSHD:
            {
                EnuCusModelSeries eModel = a_cfg_cust_get_CurModelSeries();
                if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                }
                else if ((eModel == CUS_MODEL_2021_83_2K_D_HD) || (eModel == CUS_MODEL_2021_83_2K_D_FHD) || (eModel == CUS_MODEL_2022_83_2K_D))
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                }
                else
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD Master Audio",AUDIO_CODEC_LEN -1);
                }
                ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD_MA;
                break;
            }
            case E_MI_AUDIO_CODEC_TYPE_DTS_X:
            {
                if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS:X",AUDIO_CODEC_LEN -1);
                }
                else
                {
                    c_strncpy(ptMovieInfo->audioCodec,"DTS",AUDIO_CODEC_LEN -1);
                }
                ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS;
                break;
            }
            default:
            {
                isDTS = FALSE;
                break;
            }
        }
        free(eDtsVersion);
        free(peCodecType);
        if(isDTS == FALSE)
        {
            switch(tMovieInfo.eAudioCodec)
            {
                case E_MI_MM_AUDIO_CODEC_TYPE_AAC:
                    c_strncpy(ptMovieInfo->audioCodec,"AAC",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_AAC;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_AC3:
                    c_strncpy(ptMovieInfo->audioCodec,"Dolby Audio-DD",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_AC3;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_AC3P:
                    c_strncpy(ptMovieInfo->audioCodec,"Dolby Audio-DD+",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_AC3P;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_AMR_NB:
                    c_strncpy(ptMovieInfo->audioCodec,"AMR_NB",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_AMR_NB;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_AMR_WB:
                    c_strncpy(ptMovieInfo->audioCodec,"AMR_WB",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_AMR_WB;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_DTS:
                    c_strncpy(ptMovieInfo->audioCodec,"DTS",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_DTS_LBR:
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS_LBR;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD:
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD_MA:
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD_MA;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD_HRA:
                    c_strncpy(ptMovieInfo->audioCodec,"DTS-HD",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DTS_HD_HRA;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_FLAC:
                    c_strncpy(ptMovieInfo->audioCodec,"FLAC",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_FLAC;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_MP3:
                    c_strncpy(ptMovieInfo->audioCodec,"MP3",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_MP3;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_MPEG:
                    c_strncpy(ptMovieInfo->audioCodec,"MPEG",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_MPEG;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_RA8_LBR:
                    c_strncpy(ptMovieInfo->audioCodec,"RA8_LBR",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_RA8_LBR;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_VORBIS:
                    c_strncpy(ptMovieInfo->audioCodec,"VORBIS",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_VORBIS;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_DRA:
                    c_strncpy(ptMovieInfo->audioCodec,"DRA",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_DRA;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_WMA:
                    c_strncpy(ptMovieInfo->audioCodec,"WMA",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_WMA;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_WMA1:
                    c_strncpy(ptMovieInfo->audioCodec,"WMA1",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_WMA1;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_WMA2:
                    c_strncpy(ptMovieInfo->audioCodec,"WMA2",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_WMA2;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_WMA3:
                    c_strncpy(ptMovieInfo->audioCodec,"WMA3",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_WMA3;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_PCM:
                    c_strncpy(ptMovieInfo->audioCodec,"PCM",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_PCM;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_ADPCM:
                    c_strncpy(ptMovieInfo->audioCodec,"APPCM",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_ADPCM;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_OPUS:
                    c_strncpy(ptMovieInfo->audioCodec,"OPUS",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_OPUS;
                    break;
                case E_MI_MM_AUDIO_CODEC_TYPE_AC4:
                    c_strncpy(ptMovieInfo->audioCodec,"Dolby Audio-AC4",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_AC4;
                    break;
                default:
                    c_strncpy(ptMovieInfo->audioCodec,"unknown",AUDIO_CODEC_LEN -1);
                    ptMovieInfo->eAudioCodec = E_SPLAYER_AUDIO_CODEC_TYPE_UNKNOWN;
                    break;

            }
        }
        SPLAYER_DBG_INFO(" u32TotalTime:%d \r\n",ptMovieInfo->ui4_total_time);
        SPLAYER_DBG_INFO(" u32MovieWidth:%d \r\n",ptMovieInfo->u32MovieWidth);
        SPLAYER_DBG_INFO(" u32MovieHeight:%d \r\n",ptMovieInfo->u32MovieHeight);
        SPLAYER_DBG_INFO(" audiocodec:::::::%s, \r\n",ptMovieInfo->audioCodec);

        return APPL_SPLAYER_SUCCESS;
    }

    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}
static INT32 _appl_splayer_get_movie_speed(P_APPL_SPLAYER_T psPlayer, SPLAYER_TrickSpeed_e *pe_speed)
{
    INT32 i4_ret = MI_ERR_FAILED;
    //MI_MM_TrickSpeed_e *pe_cur_speed;

    SPLAYER_DBG_PRINT("Enter \r\n");
    MI_MM_MovieInfo_t tMovieInfo;
    c_memset(&tMovieInfo, 0, sizeof(tMovieInfo));

    SPLAYER_DBG_PRINT("[%s %d]psPlayer->h_MI_MM_Hdl == %d\n",__FUNCTION__,__LINE__,psPlayer->h_MI_MM_Hdl);
    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        i4_ret = MI_MM_GetMovieInfo(psPlayer->h_MI_MM_Hdl,&tMovieInfo);
        if(MI_OK != i4_ret)
        {
                 SPLAYER_DBG_ERROR(" Fail atMI_MM_GetMovieInfo \r\n");
        }

        //get the video play speed
        SPLAYER_DBG_INFO("eSpeed:%d \r\n",tMovieInfo.stTrickInfo.eSpeed);
        *pe_speed = (UINT32)(tMovieInfo.stTrickInfo.eSpeed);
        SPLAYER_DBG_INFO("eSpeed:%d \r\n",*pe_speed);

        return APPL_SPLAYER_SUCCESS;
    }

    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;

}
MI_BOOL _appl_splayer_get_thumbnail_data(MI_HANDLE hMm, MI_U8 **pu8ThumbnailData)
{
    MI_RESULT eRet = MI_ERR_FAILED;
    MI_MM_ThumbnailParams_t stThumbnailParam;
    MI_MM_ThumbnailColorFmt_e eColorFmt = E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB8888;
    MI_U16 u16Pitch = 4;
    MI_BOOL bRet = FALSE;

    memset(&stThumbnailParam, 0, sizeof(MI_MM_ThumbnailParams_t));

    stThumbnailParam.u32Width = MUSIC_RC_COV_PIC_W;
    stThumbnailParam.u32Height = MUSIC_RC_COV_PIC_H;
    stThumbnailParam.eColorFmt = eColorFmt;
    stThumbnailParam.u32AddrSize = stThumbnailParam.u32Width * stThumbnailParam.u32Height * u16Pitch;

    *pu8ThumbnailData = (MI_U8 *)c_mem_alloc(stThumbnailParam.u32AddrSize);
    if (*pu8ThumbnailData == NULL)
    {
         SPLAYER_DBG_ERROR(" Fail at Allocate Thumbnail Memory\r\n");
        return FALSE;
    }

    stThumbnailParam.pu8Addr = *pu8ThumbnailData;
    SPLAYER_DBG_PRINT(" Get Thumbnail Address = %p, Size = 0x%x, color fmt = %d, width = %d, height = %d\n",
        stThumbnailParam.pu8Addr, stThumbnailParam.u32AddrSize, stThumbnailParam.eColorFmt, stThumbnailParam.u32Width, stThumbnailParam.u32Height);

    eRet = MI_MM_GetThumbnail(hMm, &stThumbnailParam);
    if(eRet != MI_OK)
    {
        SPLAYER_DBG_ERROR(" MI_MM_GetThumbnail failed : %d \n", eRet);
        bRet = FALSE;
    }
    else
    {
        SPLAYER_DBG_PRINT(" MI_MM_GetThumbnail successfully \n" );
        bRet = TRUE;
    }

    return bRet;
}

MI_RESULT _ConvertColorFmtToRGBA8888(MI_U8 *pu8ThumbnailData)
{
    for(int i = 0; i < MUSIC_RC_COV_PIC_W * MUSIC_RC_COV_PIC_H; i ++)
    {
#ifdef NEVER
        std::swap(pu8ThumbnailData[4*i+2],pu8ThumbnailData[4*i+0]);
#endif /* NEVER */
    }

    return MI_OK;
}

VOID _appl_splayer_get_thumbnail(MI_HANDLE hMm,APPL_SPLAYER_MUSIC_INFO_T *ptInfo)
{
    INT32     i4_ret = 0;
    MI_U8 *pu8ThumbnailData = NULL;

    if(_appl_splayer_get_thumbnail_data(hMm, (MI_U8 **)&pu8ThumbnailData) != TRUE)
    {
        SPLAYER_DBG_ERROR("_appl_splayer_get_thumbnail_data failed!!\n");
        return;
    }

    if(ptInfo->h_cover_img != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(ptInfo->h_cover_img);
        ptInfo->h_cover_img  = NULL_HANDLE;
    }

    if(ptInfo->t_img.pui1_image_data)
    {
        c_mem_free(ptInfo->t_img.pui1_image_data);
        ptInfo->t_img.pui1_image_data = NULL;
    }


#ifdef NEVER //test raw data
    HANDLE_T h_file = NULL_HANDLE;
    UINT32 ui4_write = 0;
    i4_ret = c_fm_open(FM_ROOT_HANDLE, "/mnt/usb/sda1/img.JPG", FM_OPEN_CREATE|FM_READ_WRITE, 0777, FALSE, &h_file);
    SPLAYER_DBG_PRINT("c_fm_open /mnt/usb/sda1/img.JPG!!\n");
    if(i4_ret != 0)
    {
        SPLAYER_DBG_ERROR("c_fm_open failed!!\n");

        i4_ret = c_fm_open(FM_ROOT_HANDLE, "/mnt/usb/sdb1/img.JPG", FM_OPEN_CREATE|FM_READ_WRITE, 0777, FALSE, &h_file);
        SPLAYER_DBG_PRINT("c_fm_open /mnt/usb/sdb1/img.JPG!!\n");
        if(i4_ret != 0)
        {
            SPLAYER_DBG_ERROR("c_fm_open failed!!\n");
        }

    }

    i4_ret = c_fm_write(h_file, pu8ThumbnailData, MUSIC_RC_COV_PIC_W * MUSIC_RC_COV_PIC_H * 4 , &ui4_write);
    if(i4_ret != 0)
    {
        SPLAYER_DBG_ERROR("c_fm_write failed!!\n");
    }

    i4_ret = c_fm_close(h_file);

    if(i4_ret != 0)
    {
        c_fm_close("c_fm_write failed!!\n");
    }

    SPLAYER_DBG_PRINT("c_fm comp!!\n");
#endif /* NEVER */


    //Convert color format from MI_MM_THUMBNAIL_DATA_COLOR_FMT to RGBA8888
    if(_ConvertColorFmtToRGBA8888(pu8ThumbnailData) != MI_OK)
    {
        SPLAYER_DBG_ERROR("_ConvertColorFmtToRGBA8888 failed!!\n");
        return;
    }

    do {
        ptInfo->t_img.ui2_width = MUSIC_RC_COV_PIC_W;
        ptInfo->t_img.ui2_lines = MUSIC_RC_COV_PIC_H;
        ptInfo->t_img.ui4_image_type = WGL_IMG_TYPE_8888;
        ptInfo->t_img.ui2_table_columns = 0;
        ptInfo->t_img.pt_table_data     = NULL;
        ptInfo->t_img.pui1_image_data   = pu8ThumbnailData;
        ptInfo->t_img.ui4_image_size    = MUSIC_RC_COV_PIC_W * MUSIC_RC_COV_PIC_H * 4;
        ptInfo->t_img.ui1_bits_per_pixel = 32;

        i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &(ptInfo->t_img), &(ptInfo->h_cover_img));
        if(i4_ret != 0)
        {
            c_wgl_img_tpl_destroy(ptInfo->h_cover_img);
            ptInfo->h_cover_img =  NULL_HANDLE;
            SPLAYER_DBG_ERROR(" get c_wgl_img_tpl_create failed i4_ret = %d !!!\n",(int)i4_ret);
            break;
        }
        SPLAYER_DBG_PRINT(" c_wgl_img_tpl_create successfully \n" );
    } while (0);

    return;
}

static INT32 _appl_splayer_get_music_info(P_APPL_SPLAYER_T psPlayer,APPL_SPLAYER_MUSIC_INFO_T *ptInfo)
{
    SPLAYER_DBG_PRINT("Enter \r\n");
    MI_RESULT e_ret = MI_ERR_FAILED;

    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        MI_MM_MusicInfo_t       stInfo;
        MI_MM_MusicStringInfo_t tMusicStrInfo;
        c_memset(&stInfo,0,sizeof(MI_MM_MusicInfo_t));
        e_ret = MI_MM_GetMusicInfo(psPlayer->h_MI_MM_Hdl,&stInfo);
        if(e_ret < MI_ERR_FAILED)
        {
            SPLAYER_DBG_INFO(" get MI_MM_GetMusicInfo OK ret = %d !!!\n",(int)e_ret);
        }
        else
        {
            SPLAYER_DBG_ERROR(" get MI_MM_GetMusicInfo failed ret = %d !!!\n",(int)e_ret);
        }

        ptInfo->ui4_total_time = (UINT32)stInfo.u32TotalTime;
        ptInfo->b_pic_exist    = (BOOL)stInfo.bPictureExist;

        if(stInfo.bPictureExist == TRUE)
        {
           _appl_splayer_get_thumbnail(psPlayer->h_MI_MM_Hdl,ptInfo);
           ptInfo->u32PictureSize = (UINT32)stInfo.u32PictureSize;
        }


        // get title
        c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
        e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_TITLE,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
        if(e_ret >= MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" get Title failed ret = %d \n", e_ret);
        }
        else
        {
            c_memcpy((VOID *)(ptInfo->szMetadataTitle),
               (VOID *)(long)(tMusicStrInfo.virtStringAddr),
               tMusicStrInfo.u32StringLen);
            SPLAYER_DBG_PRINT(" get Title = %s \n", ptInfo->szMetadataTitle);
        }

        // get artist
        c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
        e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_ARTIST,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
        if(e_ret >= MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" get Artist failed ret = %d \n", e_ret);
        }
        else
        {
            c_memcpy((VOID *)(ptInfo->szMetadataArtist),
               (VOID *)(long)(tMusicStrInfo.virtStringAddr),
               tMusicStrInfo.u32StringLen);
            SPLAYER_DBG_PRINT(" get Artist = %s \n", ptInfo->szMetadataArtist);
        }

        // get genre
        c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
        e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_GENRE,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
        if(e_ret >= MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" get Genre failed ret = %d \n", e_ret);
        }
        else
        {
            c_memcpy((VOID *)(ptInfo->szMetadataGenre),
               (VOID *)(long)(tMusicStrInfo.virtStringAddr),
               tMusicStrInfo.u32StringLen);
            SPLAYER_DBG_PRINT(" get Genre = %s \n", ptInfo->szMetadataGenre);
        }

        // get Album
        c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
        e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_ALBUM,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
        if(e_ret >= MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" get Album failed ret = %d \n", e_ret);
        }
        else
        {
            c_memcpy((VOID *)(ptInfo->szMetadataAlbum),
               (VOID *)(long)(tMusicStrInfo.virtStringAddr),
               tMusicStrInfo.u32StringLen);
            SPLAYER_DBG_PRINT(" get Album = %s \n", ptInfo->szMetadataAlbum);
        }

        // get year
        c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
        e_ret = MI_MM_GetMusicInfoString(psPlayer->h_MI_MM_Hdl,E_MI_MM_MUSIC_STRING_INFO_YEAR,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
        if(e_ret >= MI_ERR_FAILED)
        {
            SPLAYER_DBG_ERROR(" get Year failed ret = %d \n", e_ret);
        }
        else
        {
            c_memcpy((VOID *)(ptInfo->szYear),
               (VOID *)(long)(tMusicStrInfo.virtStringAddr),
               tMusicStrInfo.u32StringLen);
            SPLAYER_DBG_PRINT(" get Year = %s \n", ptInfo->szYear);
        }

        return APPL_SPLAYER_SUCCESS;
    }

    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",e_ret);
    return APPL_SPLAYER_FAILED;
}

static INT32 _appl_splayer_get_av_duration(P_APPL_SPLAYER_T psPlayer,UINT32 *u32MsTime)
{
    INT32 i4_ret = MI_ERR_FAILED;

    SPLAYER_DBG_INFO("Enter \r\n");
    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        i4_ret = MI_MM_GetDuration(psPlayer->h_MI_MM_Hdl,u32MsTime);
        if(MI_OK != i4_ret)
        {
             SPLAYER_DBG_ERROR(" Fail MI_MM_GetDuration i4_ret :%d\r\n",i4_ret);
        }

        SPLAYER_DBG_INFO(" u32MsTime:%d \r\n",*u32MsTime);
        return APPL_SPLAYER_SUCCESS;
    }

    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}

static INT32 _appl_splayer_get_av_position(P_APPL_SPLAYER_T psPlayer,UINT32 *u32MsTime)
{
    INT32 i4_ret = MI_ERR_FAILED;

    SPLAYER_DBG_INFO("Enter \r\n");
    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        i4_ret = MI_MM_GetCurrentTime(psPlayer->h_MI_MM_Hdl,u32MsTime);
        if(MI_OK != i4_ret)
        {
             SPLAYER_DBG_ERROR(" Fail MI_MM_GetCurrentTime i4_ret :%d\r\n",i4_ret);
        }

        SPLAYER_DBG_INFO(" u32MsTime:%d \r\n",*u32MsTime);
        return APPL_SPLAYER_SUCCESS;
    }

    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}


static INT32 _appl_splayer_set_seek(P_APPL_SPLAYER_T psPlayer,UINT32 u32MsTime)
{
    INT32 i4_ret = MI_ERR_FAILED;
    SPLAYER_DBG_INFO("Enter u32MsTime:%d \r\n",u32MsTime);

    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
       i4_ret = MI_MM_Seek(psPlayer->h_MI_MM_Hdl, (MI_U32)u32MsTime);
       if(MI_OK != i4_ret)
       {
            SPLAYER_DBG_ERROR(" Fail MI_MM_Seek i4_ret :%d\r\n",i4_ret);
       }
       return APPL_SPLAYER_SUCCESS;

    }
    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}
static INT32 _appl_splayer_set_fastforword_speed(P_APPL_SPLAYER_T psPlayer,MI_MM_TrickSpeed_e ePlaySpeed)
{
    INT32 i4_ret = MI_ERR_FAILED;

    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
       i4_ret = MI_MM_FastForward(psPlayer->h_MI_MM_Hdl, ePlaySpeed);
       if(MI_OK != i4_ret)
       {
            SPLAYER_DBG_ERROR(" Fail MI_MM_FastForward i4_ret :%d\r\n",i4_ret);
       }
       return APPL_SPLAYER_SUCCESS;

    }
    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}
static INT32 _appl_splayer_set_fastbackword_speed(P_APPL_SPLAYER_T psPlayer,MI_MM_TrickSpeed_e ePlaySpeed)
{
    INT32 i4_ret = MI_ERR_FAILED;

    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
       i4_ret = MI_MM_FastBackward(psPlayer->h_MI_MM_Hdl, ePlaySpeed);
       if(MI_OK != i4_ret)
       {
            SPLAYER_DBG_ERROR(" Fail MI_MM_FastBackward i4_ret :%d\r\n",i4_ret);
       }
       return APPL_SPLAYER_SUCCESS;

    }
    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}

static INT32 _appl_splayer_play_pause(P_APPL_SPLAYER_T psPlayer,BOOL b_paly)
{
    INT32 i4_ret = MI_ERR_FAILED;
    SPLAYER_DBG_PRINT("Enter b_paly:%d \r\n",b_paly);

    if (MI_HANDLE_NULL != psPlayer->h_MI_MM_Hdl)
    {
        if(b_paly)
        {
            i4_ret = MI_MM_Resume(psPlayer->h_MI_MM_Hdl);
            if(MI_OK != i4_ret)
            {
                SPLAYER_DBG_ERROR(" Fail MI_MM_Resume i4_ret :%d\r\n",i4_ret);
                return APPL_SPLAYER_FAILED;
            }
        }
        else
        {
            i4_ret = MI_MM_Pause(psPlayer->h_MI_MM_Hdl);
            if(MI_OK != i4_ret)
            {
                SPLAYER_DBG_ERROR(" Fail MI_MM_Pause i4_ret :%d\r\n",i4_ret);
                return APPL_SPLAYER_FAILED;
            }
        }
        return APPL_SPLAYER_SUCCESS;
    }

    SPLAYER_DBG_ERROR(" Fail at i4_ret :%d\r\n",i4_ret);
    return APPL_SPLAYER_FAILED;
}

INT32 a_appl_splayer_get_movie_info(P_APPL_SPLAYER_T *ppsPlayer,APPL_SPLAYER_MOVIE_INFO_T *ptMovieInfo)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_get_movie_info(*ppsPlayer,ptMovieInfo);
}

INT32 a_appl_splayer_get_movie_speed(P_APPL_SPLAYER_T *ppsPlayer,SPLAYER_TrickSpeed_e *pe_speed)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_get_movie_speed(*ppsPlayer, pe_speed);
}

INT32 a_appl_splayer_get_music_info(P_APPL_SPLAYER_T *ppsPlayer,APPL_SPLAYER_MUSIC_INFO_T *ptInfo)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_get_music_info(*ppsPlayer,ptInfo);
}

INT32 a_appl_splayer_get_av_position(P_APPL_SPLAYER_T *ppsPlayer,UINT32 *u32MsTime)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_get_av_position(*ppsPlayer,u32MsTime);
}

INT32 a_appl_splayer_get_av_duration (P_APPL_SPLAYER_T *ppsPlayer,UINT32 *u32MsTime)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_get_av_duration(*ppsPlayer,u32MsTime);
}

INT32 a_appl_splayer_set_seek(P_APPL_SPLAYER_T *ppsPlayer,UINT32 u32MsTime)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_set_seek(*ppsPlayer,u32MsTime);
}

INT32 a_appl_splayer_set_fastforword(P_APPL_SPLAYER_T *ppsPlayer,SPLAYER_TrickSpeed_e ePlaySpeed)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_set_fastforword_speed(*ppsPlayer,(MI_MM_TrickSpeed_e)ePlaySpeed);
}

INT32 a_appl_splayer_set_fastbackword(P_APPL_SPLAYER_T *ppsPlayer,SPLAYER_TrickSpeed_e ePlaySpeed)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_set_fastbackword_speed(*ppsPlayer,(MI_MM_TrickSpeed_e)ePlaySpeed);
}

INT32 a_appl_splayer_play_pause(P_APPL_SPLAYER_T *ppsPlayer,BOOL b_paly)
{
    NAV_ASSERT(NULL != ppsPlayer && NULL != *ppsPlayer);

    return _appl_splayer_play_pause(*ppsPlayer,b_paly);
}


static MI_RESULT _ScanUSBMediaCallback(MI_HANDLE hMm, MI_U32 u32Event, VOID *pNotifyParams, VOID *pUserParams)
{
    MI_MM_Event_e eEvent = (MI_MM_Event_e)u32Event;
    APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo = (APPL_SPLAYER_MEDIA_INFO_T *)pUserParams;
    APPL_SPLAYER_INFO_EVENT playEvent = SPLAYER_MM_EVENT_INFO_OPEN_OK;
    switch (eEvent)
    {
        case E_MI_MM_EVENT_FRAME_READY:
            SPLAYER_DBG_PRINT("[%s %d]E_MI_MM_EVENT_FRAME_READY\n",__FUNCTION__,__LINE__);
            break;
        case E_MI_MM_EVENT_EXIT_OK:
            SPLAYER_DBG_PRINT("[%s %d]E_MI_MM_EVENT_EXIT_OK\n",__FUNCTION__,__LINE__);
            break;
        case E_MI_MM_EVENT_EXIT_ERROR_FILE:
            SPLAYER_DBG_PRINT("[%s %d]E_MI_MM_EVENT_EXIT_ERROR_FILE\n",__FUNCTION__,__LINE__);
            break;
        case E_MI_MM_EVENT_PLAYING_INIT_OK:
            SPLAYER_DBG_PRINT("[%s %d]E_MI_MM_EVENT_PLAYING_INIT_OK\n",__FUNCTION__,__LINE__);
            break;
        case E_MI_MM_EVENT_PLAYING_OK:
            SPLAYER_DBG_PRINT("[%s %d]E_MI_MM_EVENT_PLAYING_OK\n",__FUNCTION__,__LINE__);
            playEvent = SPLAYER_MM_EVENT_INFO_OPEN_OK;
            break;
        default:
            break;
    }

    i2_event_status = eEvent;

    MI_OS_SetEvent(_s32TaskEventGrpId, MMUSB_EVENT_N_NOTIFY);

    if (NULL != ptMediaInfo->pfCallback)
        ptMediaInfo->pfCallback(playEvent, pUserParams, 0,ptMediaInfo->pvPara);

    return MI_OK;
}

static VOID _MI_MM_Register(MI_HANDLE hMm, APPL_SPLAYER_MEDIA_TYPE_T eFileType, MI_U64 *pu64CallbackId, APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo)
{
    MI_MM_CallbackInputParams_t stInputParams;
    MI_MM_CallbackOutputParams_t stOutputParams;
    MI_RESULT eRet = MI_ERR_FAILED;

    c_memset(&stInputParams, 0, sizeof(stInputParams));
    c_memset(&stOutputParams, 0, sizeof(stOutputParams));

    // determine stInputParams.pfEventCallback
    switch (eFileType)
    {
        case APPL_SPLAYER_MEDIA_MUSIC:
        case APPL_SPLAYER_MEDIA_MOVIE:
            stInputParams.pfEventCallback = _ScanUSBMediaCallback;
            stInputParams.pUserParams = (VOID*)ptMediaInfo;
            break;
        default:
            SPLAYER_DBG_ERROR("Unknown file type, return\n");
            return ;
    }

    stInputParams.u32EventFlags = E_MI_MM_EVENT_ALL;

    eRet = MI_MM_RegisterCallback(hMm, &stInputParams, &stOutputParams);
    if((eRet == MI_OK) && (stOutputParams.u64CallbackId != 0))
    {
        SPLAYER_DBG_PRINT("Set Callback function Success u64CallbackId :(0x%llx) !!\n",stOutputParams.u64CallbackId);
    }
    else
    {
        SPLAYER_DBG_ERROR(" Fail MI_MM_RegisterCallback eRet :%d\r\n",eRet);
        return ;
    }

    *pu64CallbackId = stOutputParams.u64CallbackId;
    return ;
}


static MI_BOOL _MI_MM_UnRegister(MI_HANDLE hMm, MI_U64 u64CallbackId)
{
    MI_RESULT eRet = MI_ERR_FAILED;
    MI_MM_CallbackInputParams_t stInputParams;

    c_memset(&stInputParams, 0, sizeof(stInputParams));

    stInputParams.u64CallbackId = u64CallbackId;

    if(stInputParams.u64CallbackId != 0)
    {
        eRet = MI_MM_UnRegisterCallback(hMm, &stInputParams);
        if(eRet != MI_OK)
        {
            SPLAYER_DBG_ERROR(" Fail MI_MM_UnRegisterCallback eRet :%d\r\n",eRet);
            return FALSE;
        }
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
* Name: _mmp_util_strcmp_nocase
*
* Description: Compare two string in case insensitive case.
*
* Inputs:  ps_s1, ps_s2
*              Null terminated strings to be compared.
*
* Outputs: -
*
* Returns: 0   ps_s1 is identical to ps_s2.
*          1   ps_s1 is greater than ps_s2.
*          -1  ps_s1 is less than ps_s2.
----------------------------------------------------------------------------*/
static INT32 _appl_splayer_strcmp_nocase(
                    const CHAR*                     ps_s1,
                    const CHAR*                     ps_s2
                    )
{
    INT32 i4_ret;

    if (ps_s1 == NULL)
    {
        return (ps_s2 == NULL) ? 0 : -1;
    }
    else if (ps_s2 == NULL)
    {
        return 1;
    }

    do
    {
        CHAR pc1 = *ps_s1;
        CHAR pc2 = *ps_s2;

        if ((pc1 >= 'a') && (pc1 <= 'z'))
        {
            pc1 += ('A' - 'a');
        }
        if ((pc2 >= 'a') && (pc2 <= 'z'))
        {
            pc2 += ('A' - 'a');
        }
        i4_ret = pc1 - pc2;
        if (i4_ret != 0)
        {
            return (i4_ret > 0) ? 1 : -1;
        }
    } while ((*ps_s1++ != '\0') && (*ps_s2++ != '\0'));

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name:    mmp_util_filter_fct_by_ext
 * Description: A filter funtcion that filters items by its extension.
 * Input:   ps_filename     A string that stores file name.
 *          pas_ext_name    A string array that stores extensions.
 *          ui1_as_ext_name_num Number of entries in pas_ext_name.
 * Output:  -
 * Returns  TRUE        This item is filtered out.
 *          FALSE       This item is not filtered out.
 *---------------------------------------------------------------------------*/
static BOOL _appl_splayer_filter_fct_by_ext (
                    const CHAR*                     ps_filename,
                    CHAR*                           as_ext_name,
                    const UINT16                    ui2_as_ext_name_num
                    )
{
    UINT16 ui2_i;
    BOOL b_ret = FALSE;
    CHAR* s_ext_name = c_strrchr (ps_filename, '.');

    if (NULL == s_ext_name)
    {
        return FALSE;
    }

    /* Skip ".". */
    s_ext_name++;

    for (ui2_i = 0;ui2_i < ui2_as_ext_name_num;ui2_i++)
    {
        if (_appl_splayer_strcmp_nocase (s_ext_name, as_ext_name + (ui2_i * EXT_LEN)) == 0)
        {
            b_ret = TRUE;
            break;
        }
    }

    return b_ret;
}
static APPL_SPLAYER_MEDIA_TYPE_T _appl_splayer_get_media_type(const CHAR *filePath)
{
    NAV_ASSERT(NULL != filePath);
    APPL_SPLAYER_MEDIA_TYPE_T e_type = APPL_SPLAYER_MEDIA_INVALID;

    // get file ext
    const CHAR *iterExt = filePath + c_strlen(filePath);
    while (iterExt-- != filePath)
    {
        if (*iterExt == '.')
        {
            iterExt++;
            break;
        }
    }
    INT32 i = 0;

    //jundi add the code to convert "A~Z" to "a~z"
    CHAR iterExt1[EXT_LEN];
    c_strcpy(iterExt1, iterExt);
    while(iterExt1[i] != '\0')
    {
        if(iterExt1[i] >= 'A' && iterExt1[i] <= 'Z')
            iterExt1[i] = iterExt1[i] + 32;
        i++;
    }
    // compare with movie
    for (i = 0; i < APPL_SPLAYER_MOVIE_EXT_NUM; i++) {
        if (c_strcmp(_ag_MovieExtList[i], iterExt1) == 0)
        {
            e_type = APPL_SPLAYER_MEDIA_MOVIE;
            return e_type;
        }
    }
    // compare with music
    for (i = 0; i < APPL_SPLAYER_MUSIC_EXT_NUM; i++) {
        if (c_strcmp(_ag_MusicExtList[i], iterExt1) == 0)
        {
            e_type = APPL_SPLAYER_MEDIA_MUSIC;
            return e_type;
        }
    }
    // compare with photo
    for (i = 0; i < APPL_SPLAYER_PHOTO_EXT_NUM; i++) {
        if (c_strcmp(_ag_photoExtList[i], iterExt1) == 0)
        {
            e_type = APPL_SPLAYER_MEDIA_PHOTO;
            return e_type;
        }
    }
#if NEVER
    do
    {
        if (_appl_splayer_filter_fct_by_ext(filePath, (CHAR*) _ag_MusicExtList, APPL_SPLAYER_MUSIC_EXT_NUM))
        {
            e_type = APPL_SPLAYER_MEDIA_MUSIC;
            break;
        }

        if (_appl_splayer_filter_fct_by_ext(filePath, (CHAR*) _ag_photoExtList, APPL_SPLAYER_PHOTO_EXT_NUM))
        {
            e_type = APPL_SPLAYER_MEDIA_PHOTO;
            break;
        }

        if (_appl_splayer_filter_fct_by_ext(filePath, (CHAR*) _ag_MovieExtList, APPL_SPLAYER_AV_EXT_NUM))
        {
            e_type = APPL_SPLAYER_MEDIA_MOVIE;
            break;
        }
    }while(0);*/
#endif
    SPLAYER_DBG_PRINT("  filePath:%s,e_type:%d \r\n",filePath,e_type);
    return e_type;
}

INT32  _appl_splayer_close_info(APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo)
{
    SPLAYER_DBG_PRINT("Enter _appl_splayer_close_info\n");
    NAV_ASSERT(NULL != ptMediaInfo);
    MI_MM_CallbackInputParams_t stInputParams;

    MI_RESULT e_ret;

    if (MI_HANDLE_NULL != ptMediaInfo->hMm)
    {
        e_ret = MI_MM_Stop(ptMediaInfo->hMm);
        if(e_ret != MI_OK)
        {
            SPLAYER_DBG_ERROR(" MI_MM_Stop Fail ,eRet :%d,hMm(0x%x), \n", e_ret, ptMediaInfo->hMm);
            return APPL_SPLAYER_FAILED;
        }

        c_memset(&stInputParams, 0, sizeof(stInputParams));

        stInputParams.u64CallbackId = ptMediaInfo->u64CallbackId;
        SPLAYER_DBG_PRINT(" u64CallbackId :(0x%llx)\r\n",stInputParams.u64CallbackId);

        if(stInputParams.u64CallbackId != 0)
        {
            e_ret = MI_MM_UnRegisterCallback(ptMediaInfo->hMm, &stInputParams);
            if(e_ret != MI_OK)
            {
                SPLAYER_DBG_ERROR(" MI_MM_UnRegisterCallback Fail ,eRet :%d,hMm(0x%x), u64CallbackId:(0x%llx)\n", e_ret, ptMediaInfo->hMm, stInputParams.u64CallbackId);
            }
        }

        e_ret = MI_MM_Close(ptMediaInfo->hMm);
        if(e_ret != MI_OK)
        {
            SPLAYER_DBG_ERROR(" MI_MM_Close Fail ,eRet :%d,hMm(0x%x), \n", e_ret, ptMediaInfo->hMm);
            return APPL_SPLAYER_FAILED;
        }

        ptMediaInfo->hMm= NULL_HANDLE;
        ptMediaInfo->u64CallbackId = NULL_HANDLE;
        ptMediaInfo->hAout = NULL_HANDLE;
        ptMediaInfo->hDisp = NULL_HANDLE;
        ptMediaInfo->pfCallback = NULL;
        ptMediaInfo->b_pic_exist = FALSE;

        if(ptMediaInfo->h_cover_img != NULL_HANDLE)
        {
            DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
            c_wgl_img_tpl_destroy(ptMediaInfo->h_cover_img);
            ptMediaInfo->h_cover_img  = NULL_HANDLE;
        }

        if(ptMediaInfo->t_img.pui1_image_data)
        {
            DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
            c_mem_free(ptMediaInfo->t_img.pui1_image_data);
            ptMediaInfo->t_img.pui1_image_data = NULL;
        }

        SPLAYER_DBG_PRINT("sPlayer close success\n");

        return APPL_SPLAYER_SUCCESS;
    }
    else
    {
        SPLAYER_DBG_PRINT("hMm is NULL\n");
        return APPL_SPLAYER_SUCCESS;
    }
}
INT32 _appl_splayer_open_info(const CHAR *filePath,
                                        appl_splayer_info_eventCallback callback,
                                        APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo,
                                        VOID *pvPara)
{
    INT32                   i4_ret = MI_ERR_FAILED;

    MI_MM_OpenParams_t      stOpenParams;
    MI_MM_StartParams_t     stStartParams;
    CHAR                    szMmName[MI_MM_NAME_LENGTH] = {0};
    MI_HANDLE               hMm         = MI_HANDLE_NULL;
    MI_HANDLE               hDisp       = MI_HANDLE_NULL;
    MI_HANDLE               hAout       = MI_HANDLE_NULL;
    MI_U64                  u64CallbackId = 0;

    MI_OS_WaitEventParams_t stWaitEventParams;
    MI_U32                  u32RetrievedEventFlag = 0;
    BOOL                    b_mm_init = FALSE;
    MI_MM_ApTypeParams_t    stApParams;
    APPL_SPLAYER_MEDIA_TYPE_T e_type = APPL_SPLAYER_MEDIA_INVALID;

    //SPLAYER_DBG_PRINT("Enter _appl_splayer_open_media_info\n");
    SPLAYER_DBG_PRINT("[%s %d]filePath == %s\n",__FUNCTION__,__LINE__,filePath);

    e_type = _appl_splayer_get_media_type(filePath);
    ptMediaInfo->e_type = e_type;
    //SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->e_type == %d\n",__FUNCTION__,__LINE__,ptMediaInfo->e_type);

    MI_MM_CHECK_INIT();
    ptMediaInfo->pfCallback = callback;
    ptMediaInfo->pvPara = pvPara;

    c_snprintf(ptMediaInfo->filePath, MAX_FILE_PATH_LEN, "%s", filePath);
    SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->filePath == %s\n",__FUNCTION__,__LINE__,ptMediaInfo->filePath);

    do
    {
        // open MI_MM
        c_memset(&stOpenParams, 0 ,sizeof(stOpenParams));
        c_snprintf(szMmName, sizeof(szMmName), MI_MM_NAME_MODEL_1);

        stOpenParams.pszName = (MI_U8 *)szMmName;
        switch(e_type)
        {
            case APPL_SPLAYER_MEDIA_MOVIE:
                stOpenParams.eMediaType = E_MI_MM_MEDIA_MOVIE;
                break;
            case APPL_SPLAYER_MEDIA_MUSIC:
                stOpenParams.eMediaType = E_MI_MM_MEDIA_MUSIC;
                break;
            case APPL_SPLAYER_MEDIA_PHOTO:
                stOpenParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
                break;
            default:
                SPLAYER_DBG_ERROR("  invalid media type \n");
                return APPL_SPLAYER_FAILED;
        }

        i4_ret = MI_MM_Open(&stOpenParams, &hMm);
        if(MI_OK != i4_ret)
        {
            SPLAYER_DBG_ERROR(" Fail MI_MM_Open. Ret: %d\r\n",i4_ret);
            return APPL_SPLAYER_FAILED;
        }

        SPLAYER_DBG_PRINT("[%s %d]hMm == %d\n",__FUNCTION__,__LINE__,hMm);
        ptMediaInfo->hMm = hMm;

        if (e_type != APPL_SPLAYER_MEDIA_PHOTO)
        {
            _MI_MM_Register(hMm, e_type, &u64CallbackId,ptMediaInfo);
        }

        ptMediaInfo->u64CallbackId = u64CallbackId;


        // get aout handle, since aout is requred in both movie and music case.
        if (e_type != APPL_SPLAYER_MEDIA_PHOTO)
        {
            if (_appl_splayer_get_aout_handle (&hAout) == FALSE  )
            {
                SPLAYER_DBG_ERROR(" Fail _appl_splayer_get_aout_handle \r\n");
                goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
            }
        }

        ptMediaInfo->hAout = hAout;

        if (e_type != APPL_SPLAYER_MEDIA_MUSIC)
        {
            // get disp handle
            if (_appl_splayer_get_disp_handle(&hDisp,0) == FALSE  )
            {
                SPLAYER_DBG_ERROR(" Fail _appl_splayer_get_disp_handle \r\n");
                MI_MM_Close(hMm);
                break;
            }
        }

        ptMediaInfo->hDisp = hDisp;

        if (e_type != APPL_SPLAYER_MEDIA_PHOTO)
        {
            c_memset(&stApParams, 0, sizeof(stApParams));
            stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;
            i4_ret = MI_MM_SetAttr(hMm, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (void *)&stApParams);
            if(i4_ret>=MI_ERR_FAILED)
            {
                SPLAYER_DBG_ERROR(" Fail MI_MM_SetAttr e_ret_code:%d \r\n",i4_ret);
            }
            else
            {
                SPLAYER_DBG_PRINT("Set MI_MM_SetAttr  Success!!\n");
            }

            c_memset(&stStartParams, 0, sizeof(stStartParams));
            /*
            stStartParams.bInitOnly= TRUE;
            stStartParams.bIsLowLatencyMode = FALSE;
            stStartParams.bPreviewEnable=FALSE;
            stStartParams.pu8DirMemInputBuf =(MI_U8 *)0;
            stStartParams.u32DirMemInputBufLen = 0;
            stStartParams.stPreviewSetting.eMode=E_MI_MM_PREVIEW_NORMAL_MODE ;
            stStartParams.stPreviewSetting.u32VideoPauseTime=0;
            stStartParams.eFileOption=E_MI_MM_FILE_MODE;
            stStartParams.pszFileName=(MI_U8*)filePath;
            stStartParams.hAout = hAout;
            stStartParams.hDisplay = hDisp;
            */

            stStartParams.bInitOnly = 1;
            stStartParams.eFileOption = E_MI_MM_FILE_MODE;
            stStartParams.pszFileName = (MI_U8*)filePath;
            stStartParams.bMuteAudio = FALSE;
            stStartParams.hDisplay = NULL;
            stStartParams.hAout = NULL;
            stStartParams.bIsLowLatencyMode = FALSE;
            stStartParams.bRetrieveMetaDataOnly=1;

            if(MI_OK != MI_MM_Start(hMm, &stStartParams))
            {
                SPLAYER_DBG_ERROR(" Fail MI_MM_Start \r\n");
                goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
            }

            UINT32 tick = c_os_get_sys_tick();

            // wait Event here for movie and music
            c_memset(&stWaitEventParams, 0, sizeof(stWaitEventParams));
            stWaitEventParams.s32EventGroupId = _s32TaskEventGrpId;
            stWaitEventParams.u32WaitEventFlag = MMUSB_EVENT_N_NOTIFY;
            stWaitEventParams.eWaitMode = E_MI_OS_EVENT_WAIT_MODE_OR_CLEAR;
            stWaitEventParams.u32WaitMs = MAX_MMSDK_INIT_WAIT_MS;

            SPLAYER_DBG_PRINT(" _s32TaskEventGrpId:%d Wait event\n",_s32TaskEventGrpId);

            while(!b_mm_init)
            {
                if(MI_OS_WaitEvent(&stWaitEventParams, &u32RetrievedEventFlag) == MI_OK)
                {
                    // handle some error event.
                    SPLAYER_DBG_PRINT("   i2_event_status :0x%x\n",i2_event_status);
                    if (i2_event_status == E_MI_MM_EVENT_EXIT_OK ||
                        i2_event_status == E_MI_MM_EVENT_EXIT_ERROR_FILE )
                    {
                        //SPLAYER_DBG_PRINT("Movie/Music exit ok or unsupport file\n");
                        //SPLAYER_DBG_PRINT("Close MI_MM\n");
                        i2_event_status = E_MI_MM_EVENT_INVALID;
                        goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
                    }

                    if((i2_event_status == E_MI_MM_EVENT_PLAYING_INIT_OK)||(i2_event_status == E_MI_MM_EVENT_PLAYING_OK))
                    {
                        // get init ok event, keep parsing.
                        i2_event_status = E_MI_MM_EVENT_INVALID;
                        SPLAYER_DBG_PRINT(" init MI_MM ok\n");
                        b_mm_init = TRUE;
                    }
                }
                else
                {
                    //SPLAYER_DBG_ERROR("Wait Init OK Failed\n");
                    //SPLAYER_DBG_ERROR("wait 2s ,jump the while\n");
                    i2_event_status = E_MI_MM_EVENT_INVALID;
                    goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
                }
            }
            //SPLAYER_DBG_PRINT(" cost %d ms \n",c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick));
        }

        return APPL_SPLAYER_SUCCESS;
    }while(0);

    UNREG_CLOSE_SET_EVENT_AND_COMPLETE:
        if(MI_OK != MI_MM_Stop(hMm))
        {
            SPLAYER_DBG_ERROR(" MI_MM_Stop failed \n" );
        }

        _MI_MM_UnRegister(hMm, u64CallbackId);
        if(MI_OK != MI_MM_Close(hMm))
        {
            SPLAYER_DBG_ERROR(" MI_MM_Close failed \n" );
        }

        return APPL_SPLAYER_FAILED;

}

INT32 _appl_splayer_audio_sort_open(const CHAR *filePath,
                                                appl_splayer_info_eventCallback callback,
                                                APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo,
                                                VOID *pvPara)
{
    INT32                   i4_ret = MI_ERR_FAILED;

    MI_MM_OpenParams_t      stOpenParams;
    MI_MM_StartParams_t     stStartParams;
    CHAR                    szMmName[MI_MM_NAME_LENGTH] = {0};
    MI_HANDLE               hMm         = MI_HANDLE_NULL;
    MI_HANDLE               hDisp       = MI_HANDLE_NULL;
    MI_HANDLE               hAout       = MI_HANDLE_NULL;
    MI_U64                  u64CallbackId = 0;

    MI_OS_WaitEventParams_t stWaitEventParams;
    MI_U32                  u32RetrievedEventFlag = 0;
    BOOL                    b_mm_init = FALSE;
    MI_MM_ApTypeParams_t    stApParams;
    APPL_SPLAYER_MEDIA_TYPE_T e_type = APPL_SPLAYER_MEDIA_INVALID;
    UINT32                       ui4_idx = 0;

    //SPLAYER_DBG_PRINT("Enter _appl_splayer_open_media_info\n");
    //SPLAYER_DBG_PRINT("[%s %d]filePath == %s\n",__FUNCTION__,__LINE__,filePath);

    e_type = _appl_splayer_get_media_type(filePath);
    ptMediaInfo->e_type = e_type;
    //SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->e_type == %d\n",__FUNCTION__,__LINE__,ptMediaInfo->e_type);

    MI_MM_CHECK_INIT();
    ptMediaInfo->pfCallback = callback;
    ptMediaInfo->pvPara = pvPara;

    c_snprintf(ptMediaInfo->filePath, MAX_FILE_PATH_LEN, "%s", filePath);
    //SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->filePath == %s\n",__FUNCTION__,__LINE__,ptMediaInfo->filePath);

    do
    {
        // open MI_MM
        c_memset(&stOpenParams, 0 ,sizeof(stOpenParams));
        c_snprintf(szMmName, sizeof(szMmName), MI_MM_AUDIO_SORT_HANDLE);

        stOpenParams.pszName = (MI_U8 *)szMmName;
        switch(e_type)
        {
            case APPL_SPLAYER_MEDIA_MOVIE:
                stOpenParams.eMediaType = E_MI_MM_MEDIA_MOVIE;
                break;
            case APPL_SPLAYER_MEDIA_MUSIC:
                stOpenParams.eMediaType = E_MI_MM_MEDIA_MUSIC;
                break;
            case APPL_SPLAYER_MEDIA_PHOTO:
                stOpenParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
                break;
            default:
                SPLAYER_DBG_ERROR("  invalid media type \n");
                return APPL_SPLAYER_FAILED;
        }

        i4_ret = MI_MM_Open(&stOpenParams, &hMm);
        if(MI_OK != i4_ret)
        {
            SPLAYER_DBG_ERROR(" Fail MI_MM_Open. Ret: %d\r\n",i4_ret);
            return APPL_SPLAYER_FAILED;
        }

        //SPLAYER_DBG_PRINT("[%s %d]hMm == %d\n",__FUNCTION__,__LINE__,hMm);
        ptMediaInfo->hMm = hMm;

        if (e_type != APPL_SPLAYER_MEDIA_PHOTO)
        {
            _MI_MM_Register(hMm, e_type, &u64CallbackId,ptMediaInfo);
        }

        ptMediaInfo->u64CallbackId = u64CallbackId;


        // get aout handle, since aout is requred in both movie and music case.
        if (e_type != APPL_SPLAYER_MEDIA_PHOTO)
        {
            if (_appl_splayer_get_aout_handle (&hAout) == FALSE  )
            {
                SPLAYER_DBG_ERROR(" Fail _appl_splayer_get_aout_handle \r\n");
                goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
            }
        }

        ptMediaInfo->hAout = hAout;

        if (e_type != APPL_SPLAYER_MEDIA_MUSIC)
        {
            // get disp handle
            if (_appl_splayer_get_disp_handle(&hDisp,0) == FALSE  )
            {
                SPLAYER_DBG_ERROR(" Fail _appl_splayer_get_disp_handle \r\n");
                MI_MM_Close(hMm);
                break;
            }
        }

        ptMediaInfo->hDisp = hDisp;

        if (e_type != APPL_SPLAYER_MEDIA_PHOTO)
        {
            c_memset(&stApParams, 0, sizeof(stApParams));
            stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;
            i4_ret = MI_MM_SetAttr(hMm, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (void *)&stApParams);
            if(i4_ret>=MI_ERR_FAILED)
            {
                SPLAYER_DBG_ERROR(" Fail MI_MM_SetAttr e_ret_code:%d \r\n",i4_ret);
            }
            else
            {
                SPLAYER_DBG_PRINT("Set MI_MM_SetAttr  Success!!\n");
            }

            c_memset(&stStartParams, 0, sizeof(stStartParams));
            /*
            stStartParams.bInitOnly= TRUE;
            stStartParams.bIsLowLatencyMode = FALSE;
            stStartParams.bPreviewEnable=FALSE;
            stStartParams.pu8DirMemInputBuf =(MI_U8 *)0;
            stStartParams.u32DirMemInputBufLen = 0;
            stStartParams.stPreviewSetting.eMode=E_MI_MM_PREVIEW_NORMAL_MODE ;
            stStartParams.stPreviewSetting.u32VideoPauseTime=0;
            stStartParams.eFileOption=E_MI_MM_FILE_MODE;
            stStartParams.pszFileName=(MI_U8*)filePath;
            stStartParams.hAout = hAout;
            stStartParams.hDisplay = hDisp;
            */

            stStartParams.bInitOnly = 1;
            stStartParams.eFileOption = E_MI_MM_FILE_MODE;
            stStartParams.pszFileName = (MI_U8*)filePath;
            stStartParams.bMuteAudio = FALSE;
            stStartParams.hDisplay = NULL;
            stStartParams.hAout = NULL;
            stStartParams.bIsLowLatencyMode = FALSE;
            stStartParams.bRetrieveMetaDataOnly=1;

            if(MI_OK != MI_MM_Start(hMm, &stStartParams))
            {
                SPLAYER_DBG_ERROR(" Fail MI_MM_Start \r\n");
                goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
            }

            UINT32 tick = c_os_get_sys_tick();

            // wait Event here for movie and music
            c_memset(&stWaitEventParams, 0, sizeof(stWaitEventParams));
            stWaitEventParams.s32EventGroupId = _s32TaskEventGrpId;
            stWaitEventParams.u32WaitEventFlag = MMUSB_EVENT_N_NOTIFY;
            stWaitEventParams.eWaitMode = E_MI_OS_EVENT_WAIT_MODE_OR_CLEAR;
            stWaitEventParams.u32WaitMs = MAX_MMSDK_INIT_WAIT_MS;

            SPLAYER_DBG_PRINT(" _s32TaskEventGrpId:%d Wait event\n",_s32TaskEventGrpId);

            while(!b_mm_init)
            {
                if(MI_OS_WaitEvent(&stWaitEventParams, &u32RetrievedEventFlag) == MI_OK)
                {
                    // handle some error event.
                    //SPLAYER_DBG_PRINT("   i2_event_status :0x%x\n",i2_event_status);
                    if (i2_event_status == E_MI_MM_EVENT_EXIT_OK ||
                        i2_event_status == E_MI_MM_EVENT_EXIT_ERROR_FILE )
                    {
                        //SPLAYER_DBG_PRINT("Movie/Music exit ok or unsupport file\n");
                        //SPLAYER_DBG_PRINT("Close MI_MM\n");
                        i2_event_status = E_MI_MM_EVENT_INVALID;
                        goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
                    }

                    if((i2_event_status == E_MI_MM_EVENT_PLAYING_INIT_OK)||(i2_event_status == E_MI_MM_EVENT_PLAYING_OK))
                    {
                        // get init ok event, keep parsing.
                        i2_event_status = E_MI_MM_EVENT_INVALID;
                        //SPLAYER_DBG_PRINT(" init MI_MM ok\n");
                        b_mm_init = TRUE;
                    }
                }
                else
                {
                    //SPLAYER_DBG_ERROR("Wait Init OK Failed\n");
                    //SPLAYER_DBG_ERROR("wait 2s ,jump the while\n");
                    i2_event_status = E_MI_MM_EVENT_INVALID;
                    goto UNREG_CLOSE_SET_EVENT_AND_COMPLETE;
                }
            }
            //SPLAYER_DBG_PRINT(" cost %d ms \n",c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick));
        }

        return APPL_SPLAYER_SUCCESS;
    }while(0);

    UNREG_CLOSE_SET_EVENT_AND_COMPLETE:
        if(MI_OK != MI_MM_Stop(hMm))
        {
            SPLAYER_DBG_ERROR(" MI_MM_Stop failed \n" );
        }

        _MI_MM_UnRegister(hMm, u64CallbackId);
        if(MI_OK != MI_MM_Close(hMm))
        {
            SPLAYER_DBG_ERROR(" MI_MM_Close failed \n" );
        }

        return APPL_SPLAYER_FAILED;

}
INT32 _appl_splayer_get_music_cover(const CHAR *filePath,APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo)
{
    SPLAYER_DBG_PRINT("Enter \r\n");
    MI_RESULT e_ret = MI_ERR_FAILED;

    if (MI_HANDLE_NULL != ptMediaInfo->hMm)
    {
        //DBG_LOG_PRINT(("[%s %d]filePath == %s\n",__FUNCTION__,__LINE__,filePath));
        //DBG_LOG_PRINT(("[%s %d]ptMediaInfo->filePath == %s\n",__FUNCTION__,__LINE__,ptMediaInfo->filePath));
        //DBG_LOG_PRINT(("[%s %d]ptMediaInfo->hMm == %d\n",__FUNCTION__,__LINE__,ptMediaInfo->hMm));
        MI_MM_MusicInfo_t       stInfo;
        MI_MM_MusicStringInfo_t tMusicStrInfo;
        c_memset(&stInfo,0,sizeof(MI_MM_MusicInfo_t));
        e_ret = MI_MM_GetMusicInfo(ptMediaInfo->hMm,&stInfo);
        if(e_ret < MI_ERR_FAILED)
        {
            SPLAYER_DBG_INFO(" get MI_MM_GetMusicInfo OK ret = %d !!!\n",(int)e_ret);
        }
        else
        {
            SPLAYER_DBG_ERROR(" get MI_MM_GetMusicInfo failed ret = %d !!!\n",(int)e_ret);
        }

        ptMediaInfo->b_pic_exist = (BOOL)stInfo.bPictureExist;

        if(stInfo.bPictureExist == TRUE)
        {
            INT32     i4_ret = 0;
            MI_U8 *pu8ThumbnailData = NULL;

            if(_appl_splayer_get_thumbnail_data(ptMediaInfo->hMm, (MI_U8 **)&pu8ThumbnailData) != TRUE)
            {
                SPLAYER_DBG_ERROR("_appl_splayer_get_thumbnail_data failed!!\n");
            }

            if(ptMediaInfo->h_cover_img != NULL_HANDLE)
            {
                //DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
                c_wgl_img_tpl_destroy(ptMediaInfo->h_cover_img);
                ptMediaInfo->h_cover_img  = NULL_HANDLE;
            }

            if(ptMediaInfo->t_img.pui1_image_data)
            {
                //DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
                c_mem_free(ptMediaInfo->t_img.pui1_image_data);
                ptMediaInfo->t_img.pui1_image_data = NULL;
            }

            //Convert color format from MI_MM_THUMBNAIL_DATA_COLOR_FMT to RGBA8888
            if(_ConvertColorFmtToRGBA8888(pu8ThumbnailData) != MI_OK)
            {
                SPLAYER_DBG_ERROR("_ConvertColorFmtToRGBA8888 failed!!\n");
            }

            do
            {
                ptMediaInfo->t_img.ui2_width = MUSIC_RC_COV_PIC_W;
                ptMediaInfo->t_img.ui2_lines = MUSIC_RC_COV_PIC_H;
                ptMediaInfo->t_img.ui4_image_type = WGL_IMG_TYPE_8888;
                ptMediaInfo->t_img.ui2_table_columns = 0;
                ptMediaInfo->t_img.pt_table_data     = NULL;
                ptMediaInfo->t_img.pui1_image_data   = pu8ThumbnailData;
                ptMediaInfo->t_img.ui4_image_size    = MUSIC_RC_COV_PIC_W * MUSIC_RC_COV_PIC_H * 4;
                ptMediaInfo->t_img.ui1_bits_per_pixel = 32;
                i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &(ptMediaInfo->t_img), &(ptMediaInfo->h_cover_img));
                if(i4_ret != 0)
                {
                    c_wgl_img_tpl_destroy(ptMediaInfo->h_cover_img);
                    ptMediaInfo->h_cover_img =  NULL_HANDLE;
                    SPLAYER_DBG_ERROR(" get c_wgl_img_tpl_create failed i4_ret = %d !!!\n",(int)i4_ret);
                    break;
                }
                SPLAYER_DBG_PRINT(" c_wgl_img_tpl_create successfully \n" );
            } while (0);

            ptMediaInfo->u32PictureSize = (UINT32)stInfo.u32PictureSize;
            return APPL_SPLAYER_SUCCESS;
        }
    }
    return APPL_SPLAYER_FAILED;
}

static INT32 _appl_splayer_get_media_info(const CHAR *filePath,APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo)
{
    INT32                   i4_ret = MI_ERR_FAILED;
    MI_U32                  u32MsTime  = 0;
    MI_MM_MusicStringInfo_t tMusicStrInfo;

    APPL_SPLAYER_MEDIA_TYPE_T e_type = APPL_SPLAYER_MEDIA_INVALID;

    //SPLAYER_DBG_PRINT("Enter _appl_splayer_get_media_info\n");
    SPLAYER_DBG_PRINT("[%s %d]filePath == %s\n",__FUNCTION__,__LINE__,filePath);

    if(MI_HANDLE_NULL == ptMediaInfo->hMm)
    {
        SPLAYER_DBG_PRINT("[%s %d] handle null\n",__FUNCTION__,__LINE__);
    }
    else
    {
        //SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->hMm == %d\n",__FUNCTION__,__LINE__,ptMediaInfo->hMm);
        e_type = _appl_splayer_get_media_type(filePath);
        //SPLAYER_DBG_PRINT("[%s %d]e_type == %d\n",__FUNCTION__,__LINE__,e_type);
        //SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->e_type == %d\n",__FUNCTION__,__LINE__,ptMediaInfo->e_type);

        c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
        switch(e_type)
        {
            case APPL_SPLAYER_MEDIA_MOVIE:
                {
                    //SPLAYER_DBG_PRINT(" [%s %d] filePath= %s \n",__FUNCTION__,__LINE__,filePath);
                    i4_ret = MI_MM_GetDuration(ptMediaInfo->hMm, &u32MsTime);
                    if(MI_OK != i4_ret)
                    {
                        SPLAYER_DBG_ERROR(" Fail at MI_MM_GetDuration i4_ret:%d\r\n",i4_ret);
                    }

                    ptMediaInfo->u32MsTime = (UINT32)u32MsTime / 1000; //change to ms to s
                    //SPLAYER_DBG_PRINT("get duration of %d\n", ptMediaInfo->u32MsTime);
                    //SPLAYER_DBG_PRINT("[%s %d]ptMediaInfo->u32MsTime == %d\n",__FUNCTION__,__LINE__,ptMediaInfo->u32MsTime);
                }
                break;
            case APPL_SPLAYER_MEDIA_MUSIC:
                {
                    //SPLAYER_DBG_PRINT(" [%s %d] filePath= %s \n",__FUNCTION__,__LINE__,filePath);
					switch(ptMediaInfo->ui2AdID)
					{
                    	//get duration
                    	case MMP_VE_INFO_ID_DURATION:
                    		i4_ret = MI_MM_GetDuration(ptMediaInfo->hMm, &u32MsTime);
                    		if(MI_OK != i4_ret)
                    		{
                        		SPLAYER_DBG_ERROR(" Fail at MI_MM_GetDuration i4_ret:%d\r\n",i4_ret);
                    		}
                    		ptMediaInfo->u32MsTime = (UINT32)u32MsTime / 1000; //change to ms to s
                    		//SPLAYER_DBG_PRINT("get duration of %d\n", ptMediaInfo->u32MsTime);
                    		break;


                    	// get title
                    	case MMP_VE_INFO_ID_TITLE:
                    		c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    		i4_ret = MI_MM_GetMusicInfoString(ptMediaInfo->hMm,E_MI_MM_MUSIC_STRING_INFO_TITLE,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    		if(i4_ret >= MI_ERR_FAILED)
                    		{
                        		SPLAYER_DBG_ERROR(" Fail at MI_MM_GetMusicInfoString e_ret_code:%d\r\n",i4_ret);
                    		}
                    		else
                    		{
                        		//c_strncpy((char*)ptMediaInfo->szMetadataTitle, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                        		c_memcpy((VOID *)(ptMediaInfo->szMetadataTitle),
                                		(VOID *)(long)(tMusicStrInfo.virtStringAddr),
                                		tMusicStrInfo.u32StringLen);
                        		ptMediaInfo->u32TitleLen = tMusicStrInfo.u32StringLen;

                        		//SPLAYER_DBG_PRINT(" get Title = %s \n", ptMediaInfo->szMetadataTitle);
                        		//SPLAYER_DBG_PRINT(" get ptMediaInfo->u32TitleLen = %d\n", ptMediaInfo->u32TitleLen);
                    		}
							break;


                    	// get artist
                    	case MMP_VE_INFO_ID_ARTIST:
                    		c_memset(&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    		i4_ret = MI_MM_GetMusicInfoString(ptMediaInfo->hMm,E_MI_MM_MUSIC_STRING_INFO_ARTIST,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    		if(i4_ret >= MI_ERR_FAILED)
                    		{
                        		SPLAYER_DBG_ERROR(" get Artist failed ret = %d \n", i4_ret);
                    		}
                    		else
                    		{
                    	    	//c_strncpy((char*)ptMediaInfo->szMetadataArtist, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                    	    	c_memcpy((VOID *)(ptMediaInfo->szMetadataArtist),
                    	        	(VOID *)(long)(tMusicStrInfo.virtStringAddr),
                    	        	tMusicStrInfo.u32StringLen);
                    	    	ptMediaInfo->u32ArtistLen = tMusicStrInfo.u32StringLen;

                    	    	//SPLAYER_DBG_PRINT(" get Artist = %s \n", ptMediaInfo->szMetadataArtist);
                        		//SPLAYER_DBG_PRINT(" get ptMediaInfo->u32ArtistLen = %d\n", ptMediaInfo->u32ArtistLen);
                    		}
							break;

                    	// get genre
                    	case MMP_VE_INFO_ID_GENRE:
                    		c_memset(&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    		i4_ret = MI_MM_GetMusicInfoString(ptMediaInfo->hMm,E_MI_MM_MUSIC_STRING_INFO_GENRE,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    		if(i4_ret >= MI_ERR_FAILED)
                    		{
                    	    	SPLAYER_DBG_ERROR(" get Genre failed ret = %d \n", i4_ret);
                    		}
                    		else
                    		{
                    	    	//c_strncpy((char*)ptMediaInfo->szMetadataGenre, (char*)(tMusicStrInfo.virtStringAddr), MAX_METADATA_STRING_LENGTH-1);
                    	    	c_memcpy((VOID *)(ptMediaInfo->szMetadataGenre),
                    	                    	(VOID *)(long)(tMusicStrInfo.virtStringAddr),
                    	                    	tMusicStrInfo.u32StringLen);
                    	    	ptMediaInfo->u32GenreLen = tMusicStrInfo.u32StringLen;

    	                    	//SPLAYER_DBG_PRINT(" get Genre = %s \n", ptMediaInfo->szMetadataGenre);
    	                    	//SPLAYER_DBG_PRINT(" get ptMediaInfo->u32GenreLen = %d\n", ptMediaInfo->u32GenreLen);
    	                	}
							break;


                    	// get Album
                    	case MMP_VE_INFO_ID_ALBUM:
                    		c_memset(&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    		i4_ret = MI_MM_GetMusicInfoString(ptMediaInfo->hMm,E_MI_MM_MUSIC_STRING_INFO_ALBUM,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    		if(i4_ret >= MI_ERR_FAILED)
                    		{
                    	    	SPLAYER_DBG_ERROR(" get Album failed ret = %d \n", i4_ret);
                    		}
                    		else
                    		{
                    	    	c_strncpy(ptMediaInfo->szMetadataAlbum, (char*)(tMusicStrInfo.virtStringAddr), tMusicStrInfo.u32StringLen);
                    	    	#if 0
                    	    	c_memcpy((VOID *)(ptMediaInfo->szMetadataAlbum),
                    	      	      (VOID *)(long)(tMusicStrInfo.virtStringAddr),
                    	     	       tMusicStrInfo.u32StringLen);
                    	    	#endif
                    	    	ptMediaInfo->u32AlbumLen = tMusicStrInfo.u32StringLen;

                    	    	SPLAYER_DBG_PRINT(" get Album = %s \n", ptMediaInfo->szMetadataAlbum);
                    	    //SPLAYER_DBG_PRINT(" get ptMediaInfo->u32AlbumLen = %d\n", ptMediaInfo->u32AlbumLen);
                    		}
							break;


                    	// get year
                    	case MMP_VE_INFO_ID_YEAR:
                    		c_memset((VOID*)&tMusicStrInfo, 0, sizeof(tMusicStrInfo));
                    		i4_ret = MI_MM_GetMusicInfoString(ptMediaInfo->hMm,E_MI_MM_MUSIC_STRING_INFO_YEAR,(MI_MM_MusicStringInfo_t*)&tMusicStrInfo);
                    		if(i4_ret >= MI_ERR_FAILED)
                    		{
                        		SPLAYER_DBG_ERROR(" get Year failed ret = %d \n", i4_ret);
                    		}
                    		else
                    		{
                        		//c_strncpy((char*)ptMediaInfo->szYear, (char*)(tMusicStrInfo.virtStringAddr),  MAX_METADATA_STRING_LENGTH-1);
                        		c_memcpy((VOID *)(ptMediaInfo->szYear),
                                		(VOID *)(long)(tMusicStrInfo.virtStringAddr),
                                		tMusicStrInfo.u32StringLen);

                        		ptMediaInfo->u32YearLen = tMusicStrInfo.u32StringLen;
                        		//SPLAYER_DBG_PRINT(" get ptMediaInfo->u32YearLen = %d\n", ptMediaInfo->u32YearLen);
                        		//SPLAYER_DBG_PRINT(" get Year = %s \n", ptMediaInfo->szYear);
                    		}
							default:
								break;
                		}

                	break;
            	}
            case APPL_SPLAYER_MEDIA_PHOTO:
                //SPLAYER_DBG_PRINT(" [%d %s]media type is photo.\n", __LINE__, __FUNCTION__);

                break;
            default:
                SPLAYER_DBG_PRINT(" invalid media type[%d][%s]\n", __LINE__, __FUNCTION__);
                return APPL_SPLAYER_FAILED;

        }
    }

    return APPL_SPLAYER_SUCCESS;
}

INT32 a_appl_splayer_get_media_info(const CHAR *filePath,APPL_SPLAYER_MEDIA_INFO_T *ptMediaInfo)
{
    SPLAYER_DBG_PRINT("Enter \r\n");

    return _appl_splayer_get_media_info(filePath,ptMediaInfo);
}

BOOL a_appl_splayer_init(VOID)
{
    if(!_appl_splayer_init())
    {
        SPLAYER_DBG_PRINT("_appl_splayer_init \r\n");
        return TRUE;
    }

    return FALSE;
}



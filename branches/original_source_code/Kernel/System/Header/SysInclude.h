/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : SysInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "Global.h"
#include "Project.h"
#include "ScalerFunctionInterface.h"
#include "UserCommonInterface.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Power.c Related MACRO
//--------------------------------------------------
//--------------------------------------------------
// Power action
//--------------------------------------------------
#define GET_TARGET_POWER_STATUS()               (g_stPowerInfo.b4PowerAction)
#define SET_TARGET_POWER_STATUS(x)              (g_stPowerInfo.b4PowerAction = (x))

//--------------------------------------------------
// Power status
//--------------------------------------------------
#define GET_POWER_STATUS()                      (g_stPowerInfo.b4PowerStatus)
#define SET_POWER_STATUS(x)                     (g_stPowerInfo.b4PowerStatus = (x))

//--------------------------------------------------
// Power Isolation flag
//--------------------------------------------------
#define GET_POWER_ISO_A_FLG()                   ((bit)(g_stPowerInfo.b1IsolationAFlag))
#define SET_POWER_ISO_A_FLG()                   (g_stPowerInfo.b1IsolationAFlag = 1)
#define CLR_POWER_ISO_A_FLG()                   (g_stPowerInfo.b1IsolationAFlag = 0)

#define GET_POWER_ISO_B_FLG()                   ((bit)(g_stPowerInfo.b1IsolationBFlag))
#define SET_POWER_ISO_B_FLG()                   (g_stPowerInfo.b1IsolationBFlag = 1)
#define CLR_POWER_ISO_B_FLG()                   (g_stPowerInfo.b1IsolationBFlag = 0)

#define GET_POWER_ISO_C_FLG()                   ((bit)(g_stPowerInfo.b1IsolationCFlag))
#define SET_POWER_ISO_C_FLG()                   (g_stPowerInfo.b1IsolationCFlag = 1)
#define CLR_POWER_ISO_C_FLG()                   (g_stPowerInfo.b1IsolationCFlag = 0)

#define GET_POWER_ISO_D_FLG()                   ((bit)(g_stPowerInfo.b1IsolationDFlag))
#define SET_POWER_ISO_D_FLG()                   (g_stPowerInfo.b1IsolationDFlag = 1)
#define CLR_POWER_ISO_D_FLG()                   (g_stPowerInfo.b1IsolationDFlag = 0)

#define GET_POWER_ISO_E_FLG()                   ((bit)(g_stPowerInfo.b1IsolationEFlag))
#define SET_POWER_ISO_E_FLG()                   (g_stPowerInfo.b1IsolationEFlag = 1)
#define CLR_POWER_ISO_E_FLG()                   (g_stPowerInfo.b1IsolationEFlag = 0)

//--------------------------------------------------
// Source.c Related MACRO
//--------------------------------------------------
#define GET_SOURCE_SEARCH_TIME_INITIAL()        ((bit)(g_stInputInfo.b1SearchTimeInitial))
#define SET_SOURCE_SEARCH_TIME_INITIAL()        (g_stInputInfo.b1SearchTimeInitial = 1)
#define CLR_SOURCE_SEARCH_TIME_INITIAL()        (g_stInputInfo.b1SearchTimeInitial = 0)

#define GET_SOURCE_SEARCH_PORT_INITIAL()        ((bit)(g_stInputInfo.b1SearchPortInitial))
#define SET_SOURCE_SEARCH_PORT_INITIAL()        (g_stInputInfo.b1SearchPortInitial = 1)
#define CLR_SOURCE_SEARCH_PORT_INITIAL()        (g_stInputInfo.b1SearchPortInitial = 0)

#define GET_SOURCE_DETECTING()                  ((bit)(g_stInputInfo.b1Detecting))
#define SET_SOURCE_DETECTING()                  (g_stInputInfo.b1Detecting = 1)
#define CLR_SOURCE_DETECTING()                  (g_stInputInfo.b1Detecting = 0)

#define GET_SOURCE_SCAN_TYPE()                  (g_stInputInfo.b4SourceSwitchType)
#define SET_SOURCE_SCAN_TYPE(x)                 (g_stInputInfo.b4SourceSwitchType = (x))

#define GET_SOURCE_AUTO_TARGET()                (g_stInputInfo.b2AutoSearchTarget)
#define SET_SOURCE_AUTO_TARGET(x)               (g_stInputInfo.b2AutoSearchTarget = (x))

#define GET_SOURCE_SWITCH_FINISH()              (g_stInputInfo.b1SourceSwitchCount)
#define SET_SOURCE_SWITCH_FINISH()              (g_stInputInfo.b1SourceSwitchCount = 1)
#define CLR_SOURCE_SWITCH_FINISH()              (g_stInputInfo.b1SourceSwitchCount = 0)

#define GET_SOURCE_SEARCH_TIME_REACTIVE()       (g_stInputInfo.b1SourceSearchTimeReactivate)
#define SET_SOURCE_SEARCH_TIME_REACTIVE()       (g_stInputInfo.b1SourceSearchTimeReactivate = 1)
#define CLR_SOURCE_SEARCH_TIME_REACTIVE()       (g_stInputInfo.b1SourceSearchTimeReactivate = 0)

#define GET_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stInputInfo.b1SourceSearchCheckNVRamPort)
#define SET_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stInputInfo.b1SourceSearchCheckNVRamPort = 1)
#define CLR_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stInputInfo.b1SourceSearchCheckNVRamPort = 0)

#define GET_SOURCE_SEARCH_DELAY_MODE()          (g_stInputInfo.b2SourceSearchDelayMode)
#define SET_SOURCE_SEARCH_DELAY_MODE(x)         (g_stInputInfo.b2SourceSearchDelayMode = (x))

#define GET_SOURCE_TYPE(x)                      (g_pstSourceInfo[x].b3SourceType)
#define SET_SOURCE_TYPE(x, y)                   (g_pstSourceInfo[x].b3SourceType = (y))

#define GET_SOURCE_SEARCH_TIMES(x)              ((g_pstSourceInfo[x].b2SearchTimes))
#define INCREASE_SOURCE_SEARCH_TIMES(x)         (g_pstSourceInfo[x].b2SearchTimes++)
#define SET_SOURCE_SEARCH_TIMES(x, y)           (g_pstSourceInfo[x].b2SearchTimes = (y))
#define CLR_SOURCE_SEARCH_TIMES(x)              (g_pstSourceInfo[x].b2SearchTimes = 0)

#define GET_CABLE_DETECT(x)                     (g_pstSourceInfo[x].b1CableDetect)
#define SET_CABLE_DETECT(x, y)                  (g_pstSourceInfo[x].b1CableDetect = (y))

#define GET_CABLE_STATUS_CHANGE(x)              (g_pstSourceInfo[x].b1CableStatusChange)
#define SET_CABLE_STATUS_CHANGE(x, y)           (g_pstSourceInfo[x].b1CableStatusChange = (y))

#define GET_SOURCE_JUDGE(x)                     ((bit)(g_pstSourceInfo[x].b1SourceChosen))
#define SET_SOURCE_JUDGE(x, y)                  (g_pstSourceInfo[x].b1SourceChosen = (y))
#define CLR_SOURCE_JUDGE(x)                     (g_pstSourceInfo[x].b1SourceChosen = 0)

#define GET_SOURCE_PREDETECT(x)                 ((bit)(g_pstSourceInfo[x].b1SourcePreDetect))
#define SET_SOURCE_PREDETECT(x, y)              (g_pstSourceInfo[x].b1SourcePreDetect = (y))
#define CLR_SOURCE_PREDETECT(x)                 (g_pstSourceInfo[x].b1SourcePreDetect = 0)

#define GET_SOURCE_TYPE_BACKUP()                (g_stSourceInfoBackup.b3SourceType)
#define SET_SOURCE_TYPE_BACKUP(x)               (g_stSourceInfoBackup.b3SourceType = (x))

#define GET_SOURCE_SEARCH_TIMES_BACKUP()        ((g_stSourceInfoBackup.b2SearchTimes))
#define INCREASE_SOURCE_SEARCH_TIMES_BACKUP()   (g_stSourceInfoBackup.b2SearchTimes++)
#define SET_SOURCE_SEARCH_TIMES_BACKUP(x)       (g_stSourceInfoBackup.b2SearchTimes = (x))
#define CLR_SOURCE_SEARCH_TIMES_BACKUP()        (g_stSourceInfoBackup.b2SearchTimes = 0)

#define GET_CABLE_DETECT_BACKUP()               (g_stSourceInfoBackup.b1CableDetect)
#define SET_CABLE_DETECT_BACKUP(x)              (g_stSourceInfoBackup.b1CableDetect = (x))

#define GET_CABLE_STATUS_CHANGE_BACKUP()        (g_stSourceInfoBackup.b1CableStatusChange)
#define SET_CABLE_STATUS_CHANGE_BACKUP(x)       (g_stSourceInfoBackup.b1CableStatusChange = (x))

#define GET_SOURCE_JUDGE_BACKUP()               ((bit)(g_stSourceInfoBackup.b1SourceChosen))
#define SET_SOURCE_JUDGE_BACKUP(x)              (g_stSourceInfoBackup.b1SourceChosen = (x))
#define CLR_SOURCE_JUDGE_BACKUP()               (g_stSourceInfoBackup.b1SourceChosen = 0)

#define GET_SOURCE_PREDETECT_BACKUP()           ((bit)(g_stSourceInfoBackup.b1SourcePreDetect))
#define SET_SOURCE_PREDETECT_BACKUP(x)          (g_stSourceInfoBackup.b1SourcePreDetect = (x))
#define CLR_SOURCE_PREDETECT_BACKUP()           (g_stSourceInfoBackup.b1SourcePreDetect = 0)

#define GET_SOURCE_MEASURE_TARGET_INDEX()       (g_ucSourceMeasureTargetIndex)
#define SET_SOURCE_MEASURE_TARGET_INDEX(x)      (g_ucSourceMeasureTargetIndex = (x))

#define GET_SOURCE_DP_SWITCH_TIMEOUT()          (g_stInputInfo.b1SourceDpSwitchTimeout)
#define SET_SOURCE_DP_SWITCH_TIMEOUT()          (g_stInputInfo.b1SourceDpSwitchTimeout = 1)
#define CLR_SOURCE_DP_SWITCH_TIMEOUT()          (g_stInputInfo.b1SourceDpSwitchTimeout = 0)

#define GET_SOURCE_DP_DUAL_SWITCH_TIMEOUT()     (g_stInputInfo.b1SourceDpDualSwitchTimeout)
#define SET_SOURCE_DP_DUAL_SWITCH_TIMEOUT()     (g_stInputInfo.b1SourceDpDualSwitchTimeout = 1)
#define CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT()     (g_stInputInfo.b1SourceDpDualSwitchTimeout = 0)

//--------------------------------------------------
// Mode.c Related MACRO
//--------------------------------------------------
#define GET_MODE_STATE()                        (g_stModeInfo.b4ModeState)
#define SET_MODE_STATE(x)                       (g_stModeInfo.b4ModeState = (x))

#define GET_MODE_STATE_CHANGE_OTHERS()          (bit)(g_stModeInfo.b1ModeStateChangedForOthers)
#define SET_MODE_STATE_CHANGE_OTHERS()          (g_stModeInfo.b1ModeStateChangedForOthers = _TRUE)
#define CLR_MODE_STATE_CHANGE_OTHERS()          (g_stModeInfo.b1ModeStateChangedForOthers = _FALSE)

#define GET_MODE_STATE_CHANGE_SOURCE()          (bit)(g_stModeInfo.b1ModeStateChangedForSource)
#define SET_MODE_STATE_CHANGE_SOURCE()          (g_stModeInfo.b1ModeStateChangedForSource = _TRUE)
#define CLR_MODE_STATE_CHANGE_SOURCE()          (g_stModeInfo.b1ModeStateChangedForSource = _FALSE)

#define GET_MODE_STATE_CHANGE_MODE()            (bit)(g_stModeInfo.b1ModeStateChangedForMode)
#define SET_MODE_STATE_CHANGE_MODE()            (g_stModeInfo.b1ModeStateChangedForMode = _TRUE)
#define CLR_MODE_STATE_CHANGE_MODE()            (g_stModeInfo.b1ModeStateChangedForMode = _FALSE)

#if(_MHL_SUPPORT == _ON)
#define GET_MODE_STATE_CHANGE_MHL()             (bit)(g_stModeInfo.b1ModeStateChangedForMHL)
#define SET_MODE_STATE_CHANGE_MHL()             (g_stModeInfo.b1ModeStateChangedForMHL = _TRUE)
#define CLR_MODE_STATE_CHANGE_MHL()             (g_stModeInfo.b1ModeStateChangedForMHL = _FALSE)
#else
#define GET_MODE_STATE_CHANGE_MHL()             (bit)(_FALSE)
#define SET_MODE_STATE_CHANGE_MHL()             ;
#define CLR_MODE_STATE_CHANGE_MHL()             ;
#endif

#define GET_MODE_STATE_CHANGE_OSD()             (bit)(g_stModeInfo.b1ModeStateChangedForOsd)
#define SET_MODE_STATE_CHANGE_OSD()             (g_stModeInfo.b1ModeStateChangedForOsd = _TRUE)
#define CLR_MODE_STATE_CHANGE_OSD()             (g_stModeInfo.b1ModeStateChangedForOsd = _FALSE)


#define GET_MODE_RESET_TARGET()                 (g_stModeInfo.b4ModeResetFlag)
#define SET_MODE_RESET_TARGET(x)                (g_stModeInfo.b4ModeResetFlag = (x))

#define GET_MODE_ACTIVE_READY()                 (bit)(g_stModeInfo.b1ActiveReady)
#define SET_MODE_ACTIVE_READY()                 (g_stModeInfo.b1ActiveReady = _TRUE)
#define CLR_MODE_ACTIVE_READY()                 (g_stModeInfo.b1ActiveReady = _FALSE)

#define GET_MODE_DISPLAY_TARGET_STATE()         (g_stRegionInfo.pstDisplayStatusInfo[g_stModeInfo.b2DisplaySettingTargetIndex].enumDisplayState)
#define GET_MODE_DISPLAY_TARGET_REGION()        (g_stModeInfo.enumDisplayMode + (g_stModeInfo.b2DisplaySettingTargetIndex))
#define GET_MODE_DISPLAY_TARGET_INDEX()         (g_stModeInfo.b2DisplaySettingTargetIndex)
#define SET_MODE_DISPLAY_TARGET_INDEX(index)    (g_stModeInfo.b2DisplaySettingTargetIndex = (index))

#define GET_INPUTPORT_TYPE(x)                   (g_pucINPUT_PORT_TYPE[g_pucSourceSearchPriority[x]])

#define GET_MODE_DISPLAY_MODE()                 (g_stModeInfo.enumDisplayMode)
#define SET_MODE_DISPLAY_MODE(x)                (g_stModeInfo.enumDisplayMode = (x))

//--------------------------------------------------
// Region Related MACRO
//--------------------------------------------------
#define GET_RGN_TIMING_CONFIRM(x)               ((g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent & _DISPLAY_EVENT_TIMING_CONFIRMED) == _DISPLAY_EVENT_TIMING_CONFIRMED)
#define SET_RGN_TIMING_CONFIRM(x)               (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent |= _DISPLAY_EVENT_TIMING_CONFIRMED)
#define CLR_RGN_TIMING_CONFIRM(x)               (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent &= ~_DISPLAY_EVENT_TIMING_CONFIRMED)

#define GET_RGN_TIMING_DOUBLE_CHECK(x)          ((g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent & _DISPLAY_EVENT_TIMING_DOUBLE_CHECK) == _DISPLAY_EVENT_TIMING_DOUBLE_CHECK)
#define SET_RGN_TIMING_DOUBLE_CHECK(x)          (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent |= _DISPLAY_EVENT_TIMING_DOUBLE_CHECK)
#define CLR_RGN_TIMING_DOUBLE_CHECK(x)          (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent &= ~_DISPLAY_EVENT_TIMING_DOUBLE_CHECK)

#define GET_RGN_MEASURE_CHECKING(x)             ((g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent & _DISPLAY_EVENT_MEASURE_CHECKING) == _DISPLAY_EVENT_MEASURE_CHECKING)
#define SET_RGN_MEASURE_CHECKING(x)             (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent |= _DISPLAY_EVENT_MEASURE_CHECKING)
#define CLR_RGN_MEASURE_CHECKING(x)             (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent &= ~_DISPLAY_EVENT_MEASURE_CHECKING)

#define GET_RGN_FIRST_ACTIVE(x)                 ((g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent & _DISPLAY_EVENT_FIRST_ACTIVE) == _DISPLAY_EVENT_FIRST_ACTIVE)
#define SET_RGN_FIRST_ACTIVE(x)                 (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent |= _DISPLAY_EVENT_FIRST_ACTIVE)
#define CLR_RGN_FIRST_ACTIVE(x)                 (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent &= ~_DISPLAY_EVENT_FIRST_ACTIVE)

#define GET_RGN_DISPLAY_STATE_CHANGE_SYS(x)     ((g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent & _DISPLAY_EVENT_STATE_CHANGE_SYS) == _DISPLAY_EVENT_STATE_CHANGE_SYS)
#define SET_RGN_DISPLAY_STATE_CHANGE_SYS(x)     (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent |= _DISPLAY_EVENT_STATE_CHANGE_SYS)
#define CLR_RGN_DISPLAY_STATE_CHANGE_SYS(x)     (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent &= ~_DISPLAY_EVENT_STATE_CHANGE_SYS)

#define GET_RGN_DISPLAY_STATE_CHANGE_USR(x)     ((g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent & _DISPLAY_EVENT_STATE_CHANGE_USR) == _DISPLAY_EVENT_STATE_CHANGE_USR)
#define SET_RGN_DISPLAY_STATE_CHANGE_USR(x)     (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent |= _DISPLAY_EVENT_STATE_CHANGE_USR)
#define CLR_RGN_DISPLAY_STATE_CHANGE_USR(x)     (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent &= ~_DISPLAY_EVENT_STATE_CHANGE_USR)

#define GET_RGN_DISPLAY_EVENT(x)                (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent)
#define SET_RGN_DISPLAY_EVENT(x, event)         (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent = (event))
#define CLR_RGN_DISPLAY_EVENT(x)                (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayEvent = (EnumDisplayEvent)0x00)

#define GET_RGN_DISPLAY_STATE(x)                (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayState)
#define SET_RGN_DISPLAY_STATE(x, state)         {\
                                                    if((state) != g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayState)\
                                                    {\
                                                        g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayState = (state);\
                                                        SET_RGN_DISPLAY_STATE_CHANGE_SYS(x);\
                                                        SET_RGN_DISPLAY_STATE_CHANGE_USR(x);\
                                                    }\
                                                }

#define CLR_RGN_DISPLAY_STATE(x)                {SET_RGN_DISPLAY_STATE((x), _DISPLAY_STATE_NONE)}

#define GET_RGN_DISPLAY_ACTION(x)               (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayAction)
#define SET_RGN_DISPLAY_ACTION(x, act)          (g_stRegionInfo.pstDisplayStatusInfo[x].enumDisplayAction = (act))
#define CLR_RGN_DISPLAY_ACTION(x)               (SET_RGN_DISPLAY_ACTION((x), _DISPLAY_ACTION_NO_ACTION))

#define CLR_RGN_DISPLAY_INFO(x)                 (memset(&g_stRegionInfo.pstDisplayStatusInfo[x], 0x00, sizeof(StructDisplayStatusInfoType)))
#define CLR_RGN_DISPLAY_INFO_ALL()              (memset(&g_stRegionInfo.pstDisplayStatusInfo, 0x00, (sizeof(StructDisplayStatusInfoType) * _MULTI_DISPLAY_MAX)))

#define GET_RGN_SOURCE_INDEX(x)                 (g_stRegionInfo.pucSourceIndex[x])
#define SET_RGN_SOURCE_INDEX(x, index)          (g_stRegionInfo.pucSourceIndex[x] = (index))

#define GET_RGN_INPUT_PORT(x)                   (GET_INPUT_PORT(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(x))))

#define GET_RGN_SOURCE_TYPE(x)                  (GET_SOURCE_TYPE(GET_RGN_SOURCE_INDEX(x)))
#define CLR_RGN_SOURCE_TYPE(x)                  (SET_SOURCE_TYPE(GET_RGN_SOURCE_INDEX(x), _SOURCE_NONE))
#define CLR_RGN_SOURCE_TYPE_ALL()               {\
                                                    BYTE ucRegionSourceIndex = 0x00;\
                                                    while(ucRegionSourceIndex < _MULTI_DISPLAY_MAX)\
                                                    {\
                                                        CLR_RGN_SOURCE_TYPE(ucRegionSourceIndex++);\
                                                    }\
                                                }

#define GET_RGN_SOURCE_JUDGE(x)                 (GET_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(x)))
#define CLR_RGN_SOURCE_JUDGE(x)                 (CLR_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(x)))
#define CLR_RGN_SOURCE_JUDGE_ALL()              {\
                                                    BYTE ucRegionSourceIndex = 0x00;\
                                                    while(ucRegionSourceIndex < _MULTI_DISPLAY_MAX)\
                                                    {\
                                                        CLR_RGN_SOURCE_JUDGE(ucRegionSourceIndex++);\
                                                    }\
                                                }

#define GET_RGN_DISPLAY_REGION(x)               ((EnumDisplayRegion)(GET_MODE_DISPLAY_MODE() + ((x) & 0x03)))
#define GET_RGN_DISPLAY_MODE(x)                 ((x) & _DISPLAY_MODE_NONE)


#define GET_RGN_MAX_DISPLAY_REGION()            ((BYTE)g_stRegionInfo.b2ucRegionCount + 0x01)

#if(_MULTI_DISPLAY_MAX == 0x04)
#define UPD_RGN_MAX_DISPLAY_REGION()            (g_stRegionInfo.b2ucRegionCount = (GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_4P) ? 0x03 : ((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? 0x00 : 0x01))
#elif(_MULTI_DISPLAY_MAX == 0x02)
#define UPD_RGN_MAX_DISPLAY_REGION()            (g_stRegionInfo.b2ucRegionCount = (GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? 0x00 : 0x01)
#else
#define UPD_RGN_MAX_DISPLAY_REGION()            (g_stRegionInfo.b2ucRegionCount = 0x00)
#endif

//--------------------------------------------------
// SysJudge.c Related MACRO
//--------------------------------------------------
#if((_DP_MST_SUPPORT == _ON) || (_HDCP_2_2_SUPPORT == _ON))
#define GET_EVENT_CHANGE_EDGE_FLG()             ((bit)g_bEventEdgeFlg)
#define SET_EVENT_CHANGE_EDGE_FLG()             (g_bEventEdgeFlg = _TRUE)
#define CLR_EVENT_CHANGE_EDGE_FLG()             (g_bEventEdgeFlg = _FALSE)
#endif

//--------------------------------------------------
// Audio.c Related MACRO
//--------------------------------------------------
#define GET_AUDIO_PLAYBACK_SEARCH_INDEX()       (g_stAudioInfo.b4AudioPlaybackSearchIndex)
#define SET_AUDIO_PLAYBACK_SEARCH_INDEX(x)      (g_stAudioInfo.b4AudioPlaybackSearchIndex = (x))

#define GET_AUDIO_STATE()                       (g_stAudioInfo.b2AudioState)
#define SET_AUDIO_STATE(x)                      (g_stAudioInfo.b2AudioState = (x))

#define GET_AUDIO_STATE_CHANGE()                (bit)(g_stAudioInfo.b1AudioStateChange)
#define SET_AUDIO_STATE_CHANGE()                (g_stAudioInfo.b1AudioStateChange = _TRUE)
#define CLR_AUDIO_STATE_CHANGE()                (g_stAudioInfo.b1AudioStateChange = _FALSE)

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#define GET_AUDIO_PLAYING_ALONE()               (bit)(g_stAudioInfo.b1AudioPlayingAlone)
#define SET_AUDIO_PLAYING_ALONE()               (g_stAudioInfo.b1AudioPlayingAlone = _TRUE)
#define CLR_AUDIO_PLAYING_ALONE()               (g_stAudioInfo.b1AudioPlayingAlone = _FALSE)
#endif

//--------------------------------------------------
// SysDP.c Related MACRO
//--------------------------------------------------
#if(_DP_TYPE_C_SUPPORT == _ON)

#if(_D0_DP_TYPE_C_SUPPORT == _ON)
#define SET_D0_DP_TYPE_C_LANE_STATUS(x)         (g_stD0PortControllerInfo.b4Lanes = (x))
#define GET_D0_DP_TYPE_C_LANE_STATUS()          (g_stD0PortControllerInfo.b4Lanes)

#define GET_D0_DP_TYPE_C_CABLE_DETECT()         ((bit)g_stD0PortControllerInfo.b1CableDetectFlag)
#define SET_D0_DP_TYPE_C_CABLE_DETECT()         (g_stD0PortControllerInfo.b1CableDetectFlag = _TRUE)
#define CLR_D0_DP_TYPE_C_CABLE_DETECT()         (g_stD0PortControllerInfo.b1CableDetectFlag = _FALSE)

#define GET_D0_DP_TYPE_C_ALTMODE_STATUS()       ((bit)g_stD0PortControllerInfo.b1AltModeStatusLastCheck)
#define SET_D0_DP_TYPE_C_ALTMODE_STATUS()       (g_stD0PortControllerInfo.b1AltModeStatusLastCheck = _TRUE)
#define CLR_D0_DP_TYPE_C_ALTMODE_STATUS()       (g_stD0PortControllerInfo.b1AltModeStatusLastCheck = _FALSE)

#if(_D0_DP_USB_HUB_SUPPORT == _ON)
#define GET_D0_USB_HUB_MODE_STATE()             (g_stD0UsbHubInfo.b7USBHubModeState)
#define SET_D0_USB_HUB_MODE_STATE(x)            (g_stD0UsbHubInfo.b7USBHubModeState = (x))

#define GET_D0_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD0UsbHubInfo.b1SSDeviceDetecting)
#define SET_D0_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD0UsbHubInfo.b1SSDeviceDetecting = _TRUE)
#define CLR_D0_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD0UsbHubInfo.b1SSDeviceDetecting = _FALSE)

#define GET_D0_TYPE_C_USB_HUB_INFO()            (g_stD0UsbHubInfo.b4UsbHubStatus)
#define SET_D0_TYPE_C_USB_HUB_INFO(x)           (g_stD0UsbHubInfo.b4UsbHubStatus = (x))

#define GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (bit)(g_stD0UsbHubInfo.b1UsbHubDeviceChangeFlg)
#define SET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD0UsbHubInfo.b1UsbHubDeviceChangeFlg = _TRUE)
#define CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD0UsbHubInfo.b1UsbHubDeviceChangeFlg = _FALSE)
#endif

#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
#define SET_D1_DP_TYPE_C_LANE_STATUS(x)         (g_stD1PortControllerInfo.b4Lanes = (x))
#define GET_D1_DP_TYPE_C_LANE_STATUS()          (g_stD1PortControllerInfo.b4Lanes)

#define GET_D1_DP_TYPE_C_CABLE_DETECT()         ((bit)g_stD1PortControllerInfo.b1CableDetectFlag)
#define SET_D1_DP_TYPE_C_CABLE_DETECT()         (g_stD1PortControllerInfo.b1CableDetectFlag = _TRUE)
#define CLR_D1_DP_TYPE_C_CABLE_DETECT()         (g_stD1PortControllerInfo.b1CableDetectFlag = _FALSE)

#define GET_D1_DP_TYPE_C_ALTMODE_STATUS()       ((bit)g_stD1PortControllerInfo.b1AltModeStatusLastCheck)
#define SET_D1_DP_TYPE_C_ALTMODE_STATUS()       (g_stD1PortControllerInfo.b1AltModeStatusLastCheck = _TRUE)
#define CLR_D1_DP_TYPE_C_ALTMODE_STATUS()       (g_stD1PortControllerInfo.b1AltModeStatusLastCheck = _FALSE)

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
#define GET_D1_USB_HUB_MODE_STATE()             (g_stD1UsbHubInfo.b7USBHubModeState)
#define SET_D1_USB_HUB_MODE_STATE(x)            (g_stD1UsbHubInfo.b7USBHubModeState = (x))

#define GET_D1_USB_HUB_SS_DEVICE_DETECT_FLG()   (bit)(g_stD1UsbHubInfo.b1SSDeviceDetecting)
#define SET_D1_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD1UsbHubInfo.b1SSDeviceDetecting = _TRUE)
#define CLR_D1_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD1UsbHubInfo.b1SSDeviceDetecting = _FALSE)

#define GET_D1_TYPE_C_USB_HUB_INFO()            (g_stD1UsbHubInfo.b4UsbHubStatus)
#define SET_D1_TYPE_C_USB_HUB_INFO(x)           (g_stD1UsbHubInfo.b4UsbHubStatus = (x))

#define GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (bit)(g_stD1UsbHubInfo.b1UsbHubDeviceChangeFlg)
#define SET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD1UsbHubInfo.b1UsbHubDeviceChangeFlg = _TRUE)
#define CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD1UsbHubInfo.b1UsbHubDeviceChangeFlg = _FALSE)
#endif

#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
#define SET_D6_DP_TYPE_C_LANE_STATUS(x)         (g_stD6PortControllerInfo.b4Lanes = (x))
#define GET_D6_DP_TYPE_C_LANE_STATUS()          (g_stD6PortControllerInfo.b4Lanes)

#define GET_D6_DP_TYPE_C_CABLE_DETECT()         ((bit)g_stD6PortControllerInfo.b1CableDetectFlag)
#define SET_D6_DP_TYPE_C_CABLE_DETECT()         (g_stD6PortControllerInfo.b1CableDetectFlag = _TRUE)
#define CLR_D6_DP_TYPE_C_CABLE_DETECT()         (g_stD6PortControllerInfo.b1CableDetectFlag = _FALSE)

#define GET_D6_DP_TYPE_C_ALTMODE_STATUS()       ((bit)g_stD6PortControllerInfo.b1AltModeStatusLastCheck)
#define SET_D6_DP_TYPE_C_ALTMODE_STATUS()       (g_stD6PortControllerInfo.b1AltModeStatusLastCheck = _TRUE)
#define CLR_D6_DP_TYPE_C_ALTMODE_STATUS()       (g_stD6PortControllerInfo.b1AltModeStatusLastCheck = _FALSE)

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
#define GET_D6_USB_HUB_MODE_STATE()             (g_stD6UsbHubInfo.b7USBHubModeState)
#define SET_D6_USB_HUB_MODE_STATE(x)            (g_stD6UsbHubInfo.b7USBHubModeState = (x))

#define GET_D6_USB_HUB_SS_DEVICE_DETECT_FLG()   (bit)(g_stD6UsbHubInfo.b1SSDeviceDetecting)
#define SET_D6_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD6UsbHubInfo.b1SSDeviceDetecting = _TRUE)
#define CLR_D6_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD6UsbHubInfo.b1SSDeviceDetecting = _FALSE)

#define GET_D6_TYPE_C_USB_HUB_INFO()            (g_stD6UsbHubInfo.b4UsbHubStatus)
#define SET_D6_TYPE_C_USB_HUB_INFO(x)           (g_stD6UsbHubInfo.b4UsbHubStatus = (x))

#define GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD6UsbHubInfo.b1UsbHubDeviceChangeFlg)
#define SET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD6UsbHubInfo.b1UsbHubDeviceChangeFlg = _TRUE)
#define CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD6UsbHubInfo.b1UsbHubDeviceChangeFlg = _FALSE)
#endif

#endif

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1SearchTimeInitial : 1;
    BYTE b1SearchPortInitial : 1;
    BYTE b1Detecting : 1;
    BYTE b2AutoSearchTarget : 2; // Auto Search Target
    BYTE b1SourceSwitchCount : 1;
    BYTE b1SourceSearchTimeReactivate : 1;
    BYTE b1SourceSearchCheckNVRamPort : 1;
    BYTE b2SourceSearchDelayMode : 2; // 00 : Polling
                                      // 01 : Defualt Search Time
                                      // 10 : Reactivate Search Time
    BYTE b1SourceDpSwitchTimeout : 1;
    BYTE b1SourceDpDualSwitchTimeout : 1;
    BYTE b4SourceSwitchType : 4; // 0000 : fixed;
                                 // 0001 : auto in group;
                                 // 0010 : Dell hotkey auto
                                 // 0011 : Dell hotkey fixed
} StructInputInfoType;

typedef struct
{
    BYTE b4ModeState : 4;
    BYTE b4ModeResetFlag : 4;
    BYTE b1ModeStateChangedForOthers : 1;
    BYTE b1ModeStateChangedForOsd : 1;
    BYTE b1ModeStateChangedForSource : 1;
    BYTE b1ModeStateChangedForMode : 1;
    BYTE b1ModeStateChangedForMHL : 1;
    BYTE b1ActiveReady : 1;
    BYTE b2DisplaySettingTargetIndex : 2;
    EnumDisplayMode enumDisplayMode;
} StructModeInfoType;

typedef struct
{
    EnumDisplayEvent enumDisplayEvent;        // For display event: timing confirm, timing check, display state change, etc.
    EnumDisplayState enumDisplayState : 4;    // For display state: active, OOR or no signal
    EnumDisplayAction enumDisplayAction : 4;  // For display action: to active, OOR or no signal
} StructDisplayStatusInfoType;

typedef struct
{
    BYTE b2ucRegionCount : 2;
    BYTE pucSourceIndex[_MULTI_DISPLAY_MAX];                                 // index in source search
    StructDisplayStatusInfoType pstDisplayStatusInfo[_MULTI_DISPLAY_MAX];    // For display info
} StructRegionInfoType;

typedef struct
{
    BYTE b4PowerAction : 4;
    BYTE b4PowerStatus : 4;
    BYTE b1IsolationAFlag : 1;
    BYTE b1IsolationBFlag : 1;
    BYTE b1IsolationCFlag : 1;
    BYTE b1IsolationDFlag : 1;
    BYTE b1IsolationEFlag : 1;
} StructPowerInfoType;

typedef struct
{
    BYTE b3SourceType : 3;
    BYTE b2SearchTimes : 2;
    BYTE b1CableDetect : 1;
    BYTE b1CableStatusChange : 1;
    BYTE b1SourceChosen : 1;
    BYTE b1SourcePreDetect : 1;
} StructSourceInfoType;

typedef struct
{
    BYTE b4AudioPlaybackSearchIndex : 4;
    BYTE b2AudioState : 2;
    BYTE b1AudioStateChange : 1;

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    BYTE b1AudioPlayingAlone : 1;
#endif
} StructAudioInfoType;
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// __SYSTEM_MODE__
extern StructModeInfoType g_stModeInfo;


// __SYSTEM_REGION__
extern StructRegionInfoType g_stRegionInfo;


// __SYSTEM_POWER__
extern StructPowerInfoType idata g_stPowerInfo;


// __SYSTEM_SOURCE__
extern BYTE g_pucINPUT_PORT_TYPE[];
extern StructSourceInfoType g_pstSourceInfo[_INPUT_PORT_VALID];
extern StructSourceInfoType g_stSourceInfoBackup;
extern BYTE g_pucSourceSearchPriority[9];
extern BYTE g_ucSearchIndex;
extern BYTE g_ucSourceMeasureTargetIndex;
extern StructInputInfoType g_stInputInfo;
extern bit g_bSysPSIntDetect;


#if(_DP_MST_SUPPORT == _ON)
extern bit g_bEventEdgeFlg;
#endif

// __SYSTEM_AUDIO__
extern StructAudioInfoType idata g_stAudioInfo;


// __SYSTEM_VGA__
extern EnumDisplayRegion g_enumVgaRegion;

#if(_DP_TYPE_C_SUPPORT == _ON)

#if(_D0_DP_TYPE_C_SUPPORT == _ON)
extern StructPortController g_stD0PortControllerInfo;

#if(_D0_DP_USB_HUB_SUPPORT == _ON)
extern StructUsbHubInfo g_stD0UsbHubInfo;
#endif

#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
extern StructPortController g_stD1PortControllerInfo;

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
extern StructUsbHubInfo g_stD1UsbHubInfo;
#endif

#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
extern StructPortController g_stD6PortControllerInfo;

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
extern StructUsbHubInfo g_stD6UsbHubInfo;
#endif

#endif

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// __SYSTEM_JUDGE__
extern void SysJudgeHandler(void);
extern bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState);


// __SYSTEM_MODE__
extern void SysModeHandler(void);
extern void SysModeResetState(BYTE ucResetTarget);
extern void SysModeSetFreeRun(void);
extern void SysModeResetDataPath(BYTE ucRegionIndex);
extern bit SysModeSearchDisplayTarget(void);


// __SYSTEM_REGION__
extern void SysRegionInitial(void);
extern EnumDisplayState SysRegionGetDisplayState(EnumDisplayRegion enumDisplayRegion);
extern EnumSourceTypeDef SysRegionGetSourceType(EnumDisplayRegion enumDisplayRegion);
extern EnumSourceSearchPort SysRegionGetPortType(EnumDisplayRegion enumDisplayRegion);
extern bit SysRegionCheckAllDisplayState(EnumDisplayState enumDisplayState);
extern bit SysRegionCheckSystemDisplayStateChange(void);
extern void SysRegionSetMeasureResultPointerRegion(EnumDisplayRegion enumDisplayRegion);
extern void SysRegionClearAllDisplayEvent(BYTE ucDisplayEventSet);
extern EnumDisplayRegion SysRegionConvertPortToRegion(EnumSourceSearchPort enumSourceSearchPort);
extern EnumRegionIndex SysRegionConvertPortToRegionIndex(EnumSourceSearchPort enumSourceSearchPort);
extern EnumRegionIndex SysRegionConvertSourceIndexToRegionIndex(BYTE ucSearchIndex);
extern BYTE SysRegionGetDisplayStateCount(EnumDisplayState enumDisplayState);
extern void SysRegionSetDisplayStateBySearchIndex(BYTE ucSearchIndex, EnumDisplayState enumDisplayState);


// __SYSTEM_MHL__
extern void SysMHLMscHandler(void);


// __SYSTEM_POWER__
extern void SysPowerInitial(void);
extern void SysPowerHandler(void);


// __SYSTEM_SOURCE__
extern void SysSourceHandler(void);
extern void SysSourceInitial(void);
extern bit SysSourceStableCheck(BYTE ucRegionIndex);
extern void SysSourceClearDetectingEvent(void);
extern void SysSourceSwitchInputPort(BYTE ucInputPort);
extern void SysSourceSwitchRegionSearchPort(BYTE ucInputPort);
extern void SysSourceSearchTimeReset(void);
extern void SysSourceInfoResetToDisplayInitial(void);
extern void SysSourceInfoReset(void);
extern void SysSourceResetRegion(BYTE ucRegionIndex);
extern BYTE SysSourceGetInputPort(void);
extern BYTE SysSourceGetInputPortType(BYTE ucInputPort);
extern BYTE SysSourceGetSourceType(void);
extern BYTE SysSourceConvertSearchPort(BYTE ucInputPort);
extern bit SysSourceGetCableStatusChange(BYTE ucInputPort);
extern void SysSourceCableResetProc(void);
extern void SysSourceFirstActiveProc(void);
extern void SysSourcePowerOffProc(void);


// __SYSTEM_TIMER__
extern void SysTimerHandler(void);

#if(_VGA_SUPPORT == _ON)
extern EnumDisplayRegion SysVgaGetRegion(void);
extern BYTE SysVgaScanInputPort(void);
#endif


// __SYSTEM_AUDIO__
#if(_AUDIO_SUPPORT == _ON)
extern void SysAudioHandler(void);
extern void SysAudioPowerProc(EnumPowerAction enumSwitch);

#if(_DP_SUPPORT == _ON)
void SysAudioDpAudioSecDataResetProc(BYTE ucInputPort);
#endif

#endif

#if(_DP_SUPPORT == _ON)
extern void SysDpRxHandler(void);
#endif

// __SYSTEM_TMDS__
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern void SysTMDSRxHandler(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void SysDpTxHandler(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void SysDpMstHandler(void);
#endif

#if(_DP_TYPE_C_SUPPORT == _ON)
extern void SysDpTypeCHandler(void);

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_TYPE_C_SUPPORT == _ON))
extern bit SysDpTypeCGetD0AltModeCheck(void);
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_TYPE_C_SUPPORT == _ON))
extern bit SysDpTypeCGetD1AltModeCheck(void);
#endif

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_DP_TYPE_C_SUPPORT == _ON))
extern bit SysDpTypeCGetD6AltModeCheck(void);
#endif
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)

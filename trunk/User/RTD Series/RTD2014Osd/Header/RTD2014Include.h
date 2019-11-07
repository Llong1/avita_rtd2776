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
// ID Code      : RTD2014Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "RTD2014Project.h"
#include "RTD2014NVRamOsd.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + (_A0_INPUT_PORT_TYPE & 0x0F))
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + (_D0_INPUT_PORT_TYPE & 0x0F))
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + (_D1_INPUT_PORT_TYPE & 0x0F))
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + (_D2_INPUT_PORT_TYPE & 0x0F))
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + (_D3_INPUT_PORT_TYPE & 0x0F))
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + (_D4_INPUT_PORT_TYPE & 0x0F))
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + (_D5_INPUT_PORT_TYPE & 0x0F))
#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + (_D6_INPUT_PORT_TYPE & 0x0F))
#define _D7_INPUT_TYPE                              (_OPTION_ICON_END + (_D7_INPUT_PORT_TYPE & 0x0F))

/*
#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
#define _A0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_VGA)
#else
#define _A0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
#define _D0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
#define _D0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DP)
#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#define _D0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D0_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
#define _D1_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#define _D1_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _D1_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DP)
#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define _D1_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D1_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
#define _D2_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#define _D2_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define _D2_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D2_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif


#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#define _D3_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#define _D3_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#define _D3_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D3_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#define _D4_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#define _D4_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define _D4_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D4_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif


#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
#define _D5_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#define _D5_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define _D5_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D5_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif



#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
#define _D6_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DP)
#else
#define _D6_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
#define _D7_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_DP)
#else
#define _D7_INPUT_TYPE                            (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif
*/
//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _CONTRAST_MAX                               2848
#define _CONTRAST_MIN                               1248
#define _CONTRAST_CENTER                            (((_CONTRAST_MAX - _CONTRAST_MIN) / 2) + _CONTRAST_MIN)

//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _BACKLIGHT_MAX                          235//   255
#else
#define _BACKLIGHT_MAX                              4095
#endif
#define _BACKLIGHT_MIN                              30
#define _BACKLIGHT_CENTER                     (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)
#define _BACKLIGHT_DEFAULT                   (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) *8 /10) + _BACKLIGHT_MIN)

//--------------------------------------------------
// Definitions of Brightness Range
//--------------------------------------------------
#define _BRIGHTNESS_MAX                             712
#define _BRIGHTNESS_MIN                             312
#define _BRIGHTNESS_CENTER                          (((_BRIGHTNESS_MAX - _BRIGHTNESS_MIN) / 2) + _BRIGHTNESS_MIN)

//--------------------------------------------------
// Definitions of Sharpness Range
//--------------------------------------------------
#define _SHARPNESS_MAX                              4
#define _SHARPNESS_MIN                              0
#define _SHARPNESS_CENTER                           (((_SHARPNESS_MAX - _SHARPNESS_MIN) / 2) + _SHARPNESS_MIN)
//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _OSD_PHASE_MAX                              100
#define _OSD_PHASE_MIN                              0

//--------------------------------------------------
// Definitions of Colortemp User RGB
//--------------------------------------------------
#define _USER_RGB_MAX                               255
#define _USER_RGB_MIN                               0
#define _USER_RGB_CENTER                            (((_USER_RGB_MAX - _USER_RGB_MIN) / 2) + _USER_RGB_MIN)

//--------------------------------------------------
// Definitions of OD Gain Range
//--------------------------------------------------
#define _OD_GAIN_MAX                                127
#define _OD_GAIN_MIN                                0
#define _OD_GAIN_CENTER                             (((_OD_GAIN_MAX - _OD_GAIN_MIN) / 2) + _OD_GAIN_MIN)

//--------------------------------------------------
// Definitions of 3D EFFECT
//--------------------------------------------------
#define _3D_EFFECT_MAX                              0x10
#define _3D_EFFECT_MIN                              0x00

//--------------------------------------------------
// Definitions of 2DTO3D EFFECT
//--------------------------------------------------
#define _2DTO3D_H_EFFECT_MAX                        0x30
#define _2DTO3D_H_EFFECT_MIN                        0x00

#define _2DTO3D_H_V_EFFECT_MAX                      0xFF
#define _2DTO3D_H_V_EFFECT_MIN                      0x00

//--------------------------------------------------
// Definitions of Menu Time Range
//--------------------------------------------------
#define _OSD_TIMEOUT_MAX                            60
#define _OSD_TIMEOUT_MIN                            10
#define _OSD_TIMEOUT_CENTER                         (((_OSD_TIMEOUT_MAX - _OSD_TIMEOUT_MIN) / 2) + _OSD_TIMEOUT_MIN)
//--------------------------------------------------
// Definitions of Transparency Range
//--------------------------------------------------
#define _OSD_TRANSPARENCY_MAX                       255
#define _OSD_TRANSPARENCY_MIN                       0
#define _OSD_TRANSPARENCY_CENTER                    (((_OSD_TRANSPARENCY_MAX - _OSD_TRANSPARENCY_MIN) / 2) + _OSD_TRANSPARENCY_MIN)
//--------------------------------------------------
// Definitions of OSD H Position Range
//--------------------------------------------------
#define _OSD_H_POS_MAX                              100
#define _OSD_H_POS_MIN                              0
#define _OSD_H_POS_CENTER                           (((_OSD_H_POS_MAX - _OSD_H_POS_MIN) / 2) + _OSD_H_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_V_POS_MAX                              100
#define _OSD_V_POS_MIN                              0
#define _OSD_V_POS_CENTER                           (((_OSD_V_POS_MAX - _OSD_V_POS_MIN) / 2) + _OSD_V_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_ASPECT_ORIGINAL_RATIO_MAX              100
#define _OSD_ASPECT_ORIGINAL_RATIO_MIN              0
#define _OSD_ASPECT_ORIGINAL_RATIO_CENTER           ((_OSD_ASPECT_ORIGINAL_RATIO_MAX - _OSD_ASPECT_ORIGINAL_RATIO_MIN) / 2)

//--------------------------------------------------
// Definitions of Hue Saturation Range
// Allowed Hue = 0 ~ 360, Sat = 0 ~ 330
//--------------------------------------------------
#define _DEFAULT_HUE                                _HUE_CENTER
#define _DEFAULT_SATURATION                         _SATURATION_CENTER

//--------------------------------------------------
// Definitions of OSD Volume Range
//--------------------------------------------------
#define _OSD_VOLUME_MAX                             100
#define _OSD_VOLUME_MIN                             0
#define _OSD_VOLUME_CENTER                          (((_OSD_VOLUME_MAX - _OSD_VOLUME_MIN) / 2) + _OSD_VOLUME_MIN)

//--------------------------------------------------
// Definitions of OSD audio source
//--------------------------------------------------
typedef enum
{
    _OSD_AUDIO_SOURCE_ANALOG,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_1,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_2,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_3,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_4,
    _OSD_AUDIO_SOURCE_AMOUNT,
}EnumOsdAudioSourceType;

//--------------------------------------------------
// Definitions of Hue Saturation Range
//--------------------------------------------------
#define _SIX_COLOR_SATURATION_MAX                   200
#define _SIX_COLOR_SATURATION_MIN                   0
#define _SIX_COLOR_SATURATION_CENTER                100

#define _SIX_COLOR_HUE_MAX                          100
#define _SIX_COLOR_HUE_MIN                          0
#define _SIX_COLOR_HUE_CENTER                       50

//--------------------------------------------------
// Definitions of OSD Select Region Width
//--------------------------------------------------
#define _OSD_SR_WIDTH_MAX                           10
#define _OSD_SR_WIDTH_MIN                           0
#define _OSD_SR_WIDTH_CENTER                        (((_OSD_SR_WIDTH_MAX - _OSD_SR_WIDTH_MIN) / 2) + _OSD_SR_WIDTH_MIN)

//--------------------------------------------------
// Definitions of OSD Select Region Border Color
//--------------------------------------------------
typedef enum
{
    _SELECT_REGION_COLOR_0,
    _SELECT_REGION_COLOR_1,
    _SELECT_REGION_COLOR_2,
    _SELECT_REGION_COLOR_3,
    _SELECT_REGION_COLOR_AMOUNT,
}EnumSelectRegionColorType;

//--------------------------------------------------
// Definitions of OSD Select Region Border Color
//--------------------------------------------------
#define _OSD_SELECT_REGION_BORDER_RED               (0x80)
#define _OSD_SELECT_REGION_BORDER_GREEN             (0x80)
#define _OSD_SELECT_REGION_BORDER_BLUE              (0x80)
#define _OSD_SELECT_REGION_BORDER_WHITE             (0xFF)

//--------------------------------------------------
// Definitions of OSD PBP LR RATIO
//--------------------------------------------------
#define _OSD_PBP_LR_RATIO_MAX                       4
#define _OSD_PBP_LR_RATIO_MIN                       0
#define _OSD_PBP_LR_RATIO_CENTER                    (((_OSD_PBP_LR_RATIO_MAX - _OSD_PBP_LR_RATIO_MIN) / 2) + _OSD_PBP_LR_RATIO_MIN)

//--------------------------------------------------
// Definitions of OSD PIP SUB position
//--------------------------------------------------
typedef enum
{
    _PIP_POSITON_LT,
    _PIP_POSITON_RT,
    _PIP_POSITON_LB,
    _PIP_POSITON_RB,
    _PIP_POSITON_MIDDLE,
    _PIP_POSITON_USER,
    _PIP_POSITON_AMOUNT,
}EnumPipPositionType;

#define _OSD_PIP_USER_POSITION_H_MAX                100
#define _OSD_PIP_USER_POSITION_H_MIN                0
#define _OSD_PIP_USER_POSITION_H_CENTER             (((_OSD_PIP_USER_POSITION_H_MAX - _OSD_PIP_USER_POSITION_H_MIN) / 2) + _OSD_PIP_USER_POSITION_H_MIN)

#define _OSD_PIP_USER_POSITION_V_MAX                100
#define _OSD_PIP_USER_POSITION_V_MIN                0
#define _OSD_PIP_USER_POSITION_V_CENTER             (((_OSD_PIP_USER_POSITION_V_MAX - _OSD_PIP_USER_POSITION_V_MIN) / 2) + _OSD_PIP_USER_POSITION_V_MIN)

//--------------------------------------------------
// Definitions of OSD PIP Transparency
//--------------------------------------------------
#define _OSD_PIP_TRANSPARENCY_MAX                   10
#define _OSD_PIP_TRANSPARENCY_MIN                   0
#define _OSD_PIP_TRANSPARENCY_CENTER                (((_OSD_PIP_TRANSPARENCY_MAX - _OSD_PIP_TRANSPARENCY_MIN) / 2) + _OSD_PIP_TRANSPARENCY_MIN)

//--------------------------------------------------
// Definitions of OSD PIP Size
//--------------------------------------------------
#define _OSD_PIP_SIZE_MAX                           10
#define _OSD_PIP_SIZE_MIN                           0
#define _OSD_PIP_SIZE_CENTER                        (((_OSD_PIP_TRANSPARENCY_MAX - _OSD_PIP_TRANSPARENCY_MIN) / 2) + _OSD_PIP_TRANSPARENCY_MIN)

#define _OSD_PIP_SIZE_MIN_H_SIZE                    (640)
#define _OSD_PIP_SIZE_MIN_V_SIZE                    (480)

//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT1))
#define SET_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT1)

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT0))
#define SET_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT0)

//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()                        (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT2)
#define SET_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl |= _BIT2)
#define CLR_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl &= ~_BIT2)

//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()                       (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl |= _BIT3)
#define CLR_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl &= ~_BIT3)



#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_OSD_ADDRESS()                  (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress)
#define SET_FREESYNC_OSD_ADDRESS(x)                 (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress = (x))
#endif

//--------------------------------------------------
// Macro of Key Hold Start
//--------------------------------------------------
#define GET_KEY_HOLD()                              (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT4)
#define SET_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl |= _BIT4)
#define CLR_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl &= ~_BIT4)

#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_OSD_ADDRESS()                  (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress)
#define SET_FREESYNC_OSD_ADDRESS(x)                 (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress = (x))
#endif

//--------------------------------------------------
// Macro of Key Message
//--------------------------------------------------
#define GET_KEYMESSAGE()                            (g_stOsdInfo.ucOsdKeyMessage)
#define SET_KEYMESSAGE(x)                           (g_stOsdInfo.ucOsdKeyMessage = (x))

//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
#define _MENU_KEY_MESSAGE                           0
#define _RIGHT_KEY_MESSAGE                          1
#define _LEFT_KEY_MESSAGE                           2
#define _EXIT_KEY_MESSAGE                           3
#define _5_KEY_MESSAGE                              4
#define _6_KEY_MESSAGE                              5
#define _7_KEY_MESSAGE                              6
#define _HOLD_KEY_MESSAGE                           7
#define _NONE_KEY_MESSAGE                           8
#define _KEY_AMOUNT                                5// 4

//--------------------------------------------------
// Definitions of LED indicction
//--------------------------------------------------
typedef enum
{
    _LED_ALL_OFF = _LED_SYSTEM_END,
} EnumUserLedIndication;

//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------
#define FONTBYTE0(x)                                HIBYTE(0x1000 | (x)), LOBYTE(0x1000 | (x))
#define FONTBYTE1(x)                                HIBYTE(0x5000 | (x)), LOBYTE(0x5000 | (x))
#define FONTBYTE2(x)                                HIBYTE(0x9000 | (x)), LOBYTE(0x9000 | (x))
#define FONTALLBYTE(x)                              HIBYTE(0xD000 | (x)), LOBYTE(0xD000 | (x))
#define WINDOWBYTE0(x)                              HIBYTE(0x0000 | (x)), LOBYTE(0x0000 | (x))
#define WINDOWBYTE1(x)                              HIBYTE(0x4000 | (x)), LOBYTE(0x4000 | (x))
#define WINDOWBYTE2(x)                              HIBYTE(0x8000 | (x)), LOBYTE(0x8000 | (x))
#define WINDOWALLBYTE(x)                            HIBYTE(0xC000 | (x)), LOBYTE(0xC000 | (x))
#define FRAMEBYTE0(x)                               WINDOWBYTE0(x)
#define FRAMEBYTE1(x)                               WINDOWBYTE1(x)
#define FRAMEBYTE2(x)                               WINDOWBYTE2(x)
#define FRAMEALLBYTE(x)                             WINDOWALLBYTE(x)
#define WINNO(x)                                    (x)
#define ROW(x)                                      (x)
#define COL(x)                                      (x)
#define WIDTH(x)                                    (x)
#define HEIGHT(x)                                   (x)
#define LENGTH(x)                                   (x)
#define FGCOLOR(x)                                  (x)
#define BGCOLOR(x)                                  (x)
#define COLOR00(x)                                  (x)
#define COLOR01(x)                                  (x)
#define COLOR10(x)                                  (x)
#define COLOR11(x)                                  (x)
#define XSTART(x)                                   (x)
#define YSTART(x)                                   (x)
#define XEND(x)                                     (x)
#define YEND(x)                                     (x)
#define PIXELROW(x)                                 ((x) * 18)
#define PIXELCOL(x)                                 ((x) * 12)

//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by OsdDisplayDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                          (0)
#define _DET_OVERRANGE_MIN                          (1)

//--------------------------------------------------
// Definations of OSD Function
//--------------------------------------------------
#define _SPACE_                                     0xfc
#define _EXT_                                       0xfc
#define _REPEAT_                                    0xfd
#define _NEXT_                                      0xfe
#define _END_                                       0xff


//--------------------------------------------------
// Definations of Write Byte
//--------------------------------------------------
#define _WRITE_BYTE0                                0
#define _WRITE_BYTE1                                1
#define _WRITE_BYTE2                                2
#define _WRITE_BYTEALL                              3

#define GET_FACTORY_BURNIN()               		(g_stOsdUserData.b1BurnIn)
#define SET_FACTORY_BURNIN(x)              		(g_stOsdUserData.b1BurnIn = (x))



//--------------------------------------------------
// MACRO for OSD Logo Status
//--------------------------------------------------
#define GET_OSD_LOGO_ON()                           (g_stOsdInfo.b1OsdLogo)
#define SET_OSD_LOGO_ON(x)                          (g_stOsdInfo.b1OsdLogo = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_WAKE_UP_SWITCH_DDCCI_PORT()         (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort)
#define SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(x)        (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_SOURCE()          (g_stOsdInfo.b1OsdWakeUpShowSource)
#define SET_OSD_POWER_SAVING_SHOW_SOURCE(x)         (g_stOsdInfo.b1OsdWakeUpShowSource = (x))


//--------------------------------------------------
// MACRO for Power Saving Show Display Mode
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE()    (g_stOsdInfo.b1OsdWakeUpShowDisplayMode)
#define SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(x)   (g_stOsdInfo.b1OsdWakeUpShowDisplayMode = (x))

//--------------------------------------------------
// MACRO for Power Saving Show DP Option
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_OPTION()       (g_stOsdInfo.b1OsdWakeUpShowDpOption)
#define SET_OSD_POWER_SAVING_SHOW_DP_OPTION(x)      (g_stOsdInfo.b1OsdWakeUpShowDpOption = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_IN_FACTORY_MENU_STATUS()            (g_stOsdInfo.b1OsdFactoryModeStatus)
#define SET_OSD_IN_FACTORY_MENU_STATUS(x)           (g_stOsdInfo.b1OsdFactoryModeStatus = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
// bit0 -> port0    bit1 -> port1
#define GET_OSD_DO_ASPECT_RATIO(port)               (g_stOsdInfo.ucOsdDoAspectRatio & (_BIT0 << (port)))
#define SET_OSD_DO_ASPECT_RATIO(port, x)            (g_stOsdInfo.ucOsdDoAspectRatio = ((g_stOsdInfo.ucOsdDoAspectRatio & (~(_BIT0 << (port)))) | ((_BIT0 & (x)) << (port))))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_COLOR_FORMAT(port)                  (g_stOsdInfo.ucOsdColorFormat[port])
#define SET_OSD_COLOR_FORMAT(port, x)               (g_stOsdInfo.ucOsdColorFormat[port] = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE_PREVIOUS()                    (g_stOsdInfo.usOsdStatePrevious)
#define SET_OSD_STATE_PREVIOUS(x)                   (g_stOsdInfo.usOsdStatePrevious = (x))


//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE()                             (g_stOsdInfo.usOsdState)
#define SET_OSD_STATE(x)                            (g_stOsdInfo.usOsdState = (x))

//--------------------------------------------------
// MACRO for Osd Evevt Message
//--------------------------------------------------
#define GET_OSD_EVENT_MESSAGE()                     (g_stOsdInfo.ucOsdEventMsg)
#define SET_OSD_EVENT_MESSAGE(x)                    (g_stOsdInfo.ucOsdEventMsg = (x))

//--------------------------------------------------
// MACRO for Six Color
//--------------------------------------------------
#define GET_OSD_SIX_COLOR()                         (g_stOsdInfo.b3OsdsixColor)
#define SET_OSD_SIX_COLOR(x)                        (g_stOsdInfo.b3OsdsixColor = (x))

//--------------------------------------------------
// MACRO for Six Color Hue
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_HUE()                     (g_stOsdInfo.b3OsdsixColorHue)
#define SET_OSD_SIX_COLOR_HUE(x)                    (g_stOsdInfo.b3OsdsixColorHue = (x))

//--------------------------------------------------
// MACRO for Six Color Saturation
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_SATURATION()              (g_stOsdInfo.b3OsdsixColorSaturation)
#define SET_OSD_SIX_COLOR_SATURATION(x)             (g_stOsdInfo.b3OsdsixColorSaturation = (x))

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_DOUBLE_SIZE()                       (g_stOsdInfo.b1OsdDoubleSizeStatus)
#define SET_OSD_DOUBLE_SIZE(x)                      (g_stOsdInfo.b1OsdDoubleSizeStatus = (x))

//--------------------------------------------------
// MACRO for Freeze Status
//--------------------------------------------------
#define GET_OSD_FREEZE_STATUS()                     (g_stOsdInfo.b1FreezeStatus)
#define SET_OSD_FREEZE_STATUS(x)                    (g_stOsdInfo.b1FreezeStatus = (x))

#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
#define GET_FREEZE_DISABLE_MSG_STATE()              (g_stOsdInfo.b1FreezeDisableOsdStatus)
#define SET_FREEZE_DISABLE_MSG_STATE(x)             (g_stOsdInfo.b1FreezeDisableOsdStatus = (x))
#endif

//--------------------------------------------------
// MACRO for False Color Status
//--------------------------------------------------

#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FALSE_COLOR_SUPPORT == _ON))
#define GET_FALSE_COLOR_DISABLE_MSG_STATE()         (g_stOsdInfo.b1FalseColorDisableOsdStatus)
#define SET_FALSE_COLOR_DISABLE_MSG_STATE(x)        (g_stOsdInfo.b1FalseColorDisableOsdStatus = (x))
#endif

//==========================================================================================================
// Macro of NVRam User Data
//==========================================================================================================

//--------------------------------------------------
// MACRO for OSD Display Mode
//--------------------------------------------------
#define GET_OSD_DISPLAY_MODE()                      (g_stOsdUserData.ucDisplayMode)
#define SET_OSD_DISPLAY_MODE(x)                     (g_stOsdUserData.ucDisplayMode = (x))

//--------------------------------------------------
// MACRO for OSD Select Region Width
//--------------------------------------------------
#define GET_OSD_SELECT_REGION_WIDTH()               (g_stOsdUserData.ucSelectRegionWidth)
#define SET_OSD_SELECT_REGION_WIDTH(x)              (g_stOsdUserData.ucSelectRegionWidth = (x))

//--------------------------------------------------
// MACRO for OSD Select Region Color
//--------------------------------------------------
#define GET_OSD_SELECT_REGION_COLOR()               (g_stOsdUserData.ucSelectRegionColor)
#define SET_OSD_SELECT_REGION_COLOR(x)              (g_stOsdUserData.ucSelectRegionColor = (x))

//--------------------------------------------------
// MACRO for PBP LR Ratio
//--------------------------------------------------
#define GET_OSD_PBP_LR_RATIO()                      (g_stOsdUserData.ucPbpLrRatio)
#define SET_OSD_PBP_LR_RATIO(x)                     (g_stOsdUserData.ucPbpLrRatio = (x))

//--------------------------------------------------
// MACRO for PIP Position
//--------------------------------------------------
#define GET_OSD_PIP_POSITION_TYPE()                 (g_stOsdUserData.ucPipSubPosType)
#define SET_OSD_PIP_POSITION_TYPE(x)                (g_stOsdUserData.ucPipSubPosType = (x))

#define GET_OSD_PIP_USER_POSITION_H()               (g_stOsdUserData.usPipSubHPos)
#define SET_OSD_PIP_USER_POSITION_H(x)              (g_stOsdUserData.usPipSubHPos = (x))

#define GET_OSD_PIP_USER_POSITION_V()               (g_stOsdUserData.usPipSubVPos)
#define SET_OSD_PIP_USER_POSITION_V(x)              (g_stOsdUserData.usPipSubVPos = (x))

//--------------------------------------------------
// MACRO for PIP Transparency
//--------------------------------------------------
#define GET_OSD_PIP_TRANSPARENCY()                  (g_stOsdUserData.ucPipSubBlending)
#define SET_OSD_PIP_TRANSPARENCY(x)                 (g_stOsdUserData.ucPipSubBlending = (x))

//--------------------------------------------------
// MACRO for PIP Size
//--------------------------------------------------
#define GET_OSD_PIP_SIZE()                          (g_stOsdUserData.ucPipSubScaling)
#define SET_OSD_PIP_SIZE(x)                         (g_stOsdUserData.ucPipSubScaling = (x))

//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_PANEL_TIME_MIN()                        (g_stOsdUserData.ucMin)
#define SET_PANEL_TIME_MIN(x)                       (g_stOsdUserData.ucMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_PANEL_TIME_HOUR()                       (g_stOsdUserData.usHour)
#define SET_PANEL_TIME_HOUR(x)                      (g_stOsdUserData.usHour = (x))

//--------------------------------------------------
// MACRO for Rotation Status
//--------------------------------------------------
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_OSD_DISP_ROTATION_SIZE_TYPE()           (g_stOsdUserData.b2DispRotationSizeType)
#define SET_OSD_DISP_ROTATION_SIZE_TYPE(x)          (g_stOsdUserData.b2DispRotationSizeType = (x))
#endif

//--------------------------------------------------
// MACRO for DP Port Version
//--------------------------------------------------
#define GET_OSD_DP_D0_VERSION()                     (g_stOsdUserData.b2OsdDpD0PortVersion)
#define SET_OSD_DP_D0_VERSION(x)                    (g_stOsdUserData.b2OsdDpD0PortVersion = (x))

#define GET_OSD_DP_D1_VERSION()                     (g_stOsdUserData.b2OsdDpD1PortVersion)
#define SET_OSD_DP_D1_VERSION(x)                    (g_stOsdUserData.b2OsdDpD1PortVersion = (x))

#define GET_OSD_DP_D6_VERSION()                     (g_stOsdUserData.b2OsdDpD6PortVersion)
#define SET_OSD_DP_D6_VERSION(x)                    (g_stOsdUserData.b2OsdDpD6PortVersion = (x))

#define GET_OSD_DP_MST()                            (g_stOsdUserData.b2OsdDpMST)
#define SET_OSD_DP_MST(x)                           (g_stOsdUserData.b2OsdDpMST = (x))

//--------------------------------------------------
// MACRO for DP Lane Count switch
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define GET_OSD_DP_D0_LANE_MODE()                   (g_stOsdUserData.b3D0DpLaneMode)
#define SET_OSD_DP_D0_LANE_MODE(x)                  (g_stOsdUserData.b3D0DpLaneMode = (x))
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define GET_OSD_DP_D1_LANE_MODE()                   (g_stOsdUserData.b3D1DpLaneMode)
#define SET_OSD_DP_D1_LANE_MODE(x)                  (g_stOsdUserData.b3D1DpLaneMode = (x))
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
#define GET_OSD_DP_D6_LANE_MODE()                   (g_stOsdUserData.b3D6DpLaneMode)
#define SET_OSD_DP_D6_LANE_MODE(x)                  (g_stOsdUserData.b3D6DpLaneMode = (x))
#endif

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DISP_ROTATE()                       (g_stOsdUserData.b3OsdDispRotate)
#define SET_OSD_DISP_ROTATE(x)                      (g_stOsdUserData.b3OsdDispRotate = (x))

//--------------------------------------------------
// MACRO for Latency
//--------------------------------------------------
#define GET_OSD_LATENCY()                           (g_stOsdUserData.b2LatencyStatus)
#define SET_OSD_LATENCY(x)                          (g_stOsdUserData.b2LatencyStatus = (x))

//--------------------------------------------------
// MACRO for PCM Soft Proft
//--------------------------------------------------

#define GET_OSD_PCM_SOFT_PROFT_MODE()               (g_stOsdUserData.b1PCMSoftProftMode)
#define SET_OSD_PCM_SOFT_PROFT_MODE(x)              (g_stOsdUserData.b1PCMSoftProftMode = (x))

//--------------------------------------------------
// MACRO for OSD Input Port Value
//--------------------------------------------------
//#define GET_OSD_INPUT_PORT_OSD_ITEM()               (g_stOsdUserData.ucOsdInputPort0)
//#define SET_OSD_INPUT_PORT_OSD_ITEM(x)              (g_stOsdUserData.ucOsdInputPort0 = (x))


//--------------------------------------------------
// MACRO for OSD Rotate
//--------------------------------------------------

#define GET_OSD_ROTATE_STATUS()                     (g_stOsdUserData.b2OsdRotate)
#define SET_OSD_ROTATE_STATUS(x)                    (g_stOsdUserData.b2OsdRotate = (x))


#define GET_USB_POWER_STATUS()                   (g_stOsdUserData.b1USBPower)
#define SET_USB_POWER_STATUS(x)                  (g_stOsdUserData.b1USBPower = (x))

// alant: model type
#define GET_OSD_STATUS()                   (g_stOsdUserData.b1OsdStatus)
#define SET_OSD_STATUS(x)                  (g_stOsdUserData.b1OsdStatus = (x))


//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_3DOSD_STATUS()                      (g_stOsdUserData.b1Osd3DOSD)
#define SET_OSD_3DOSD_STATUS(x)                     (g_stOsdUserData.b1Osd3DOSD = (x))

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
#define GET_OSD_BACKLIGHT()                         (g_stOsdUserData.usBackLight)
#define SET_OSD_BACKLIGHT(x)                        (g_stOsdUserData.usBackLight = (x))


#define GET_BL_OFFSET()                         (g_stOsdUserData.bloffset)
#define SET_BL_OFFSET(x)                        (g_stOsdUserData.bloffset = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_VGA_COLOR_FORMAT_STATUS()               (g_stOsdUserData.b3VGARGBYUV)
#define SET_VGA_COLOR_FORMAT_STATUS(x)              (g_stOsdUserData.b3VGARGBYUV = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_DVI_COLOR_FORMAT_STATUS()               (g_stOsdUserData.b3DVIRGBYUV)
#define SET_DVI_COLOR_FORMAT_STATUS(x)              (g_stOsdUserData.b3DVIRGBYUV = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_DDCCI_STATUS()                      (g_stOsdUserData.b1DDCCIStatus)
#define SET_OSD_DDCCI_STATUS(x)                     (g_stOsdUserData.b1DDCCIStatus = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_TRANSPARENCY_STATUS()               (g_stOsdUserData.ucTransparency)
#define SET_OSD_TRANSPARENCY_STATUS(x)              (g_stOsdUserData.ucTransparency = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_LANGUAGE()                          (g_stOsdUserData.b4Language)
#define SET_OSD_LANGUAGE(x)                         (g_stOsdUserData.b4Language = (x))

//--------------------------------------------------
// MACRO for OsdTimeout
//--------------------------------------------------
#define GET_OSD_TIME_OUT()                          (g_stOsdUserData.ucOsdTimeout)
#define SET_OSD_TIME_OUT(x)                         (g_stOsdUserData.ucOsdTimeout = (x))

//--------------------------------------------------
// MACRO for OsdHPos
//--------------------------------------------------
#define GET_OSD_HPOS()                              (g_stOsdUserData.ucOsdHPos)
#define SET_OSD_HPOS(x)                             (g_stOsdUserData.ucOsdHPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_VPOS()                              (g_stOsdUserData.ucOsdVPos)
#define SET_OSD_VPOS(x)                             (g_stOsdUserData.ucOsdVPos = (x))

//--------------------------------------------------
// MACRO for OD Status
//--------------------------------------------------
#define GET_OSD_OD_STATUS()                         (g_stOsdUserData.b1ODStatus)
#define SET_OSD_OD_STATUS(x)                        (g_stOsdUserData.b1ODStatus = (x))

//--------------------------------------------------
// MACRO for OD Gain
//--------------------------------------------------
#define GET_OSD_OD_GAIN()                           (g_stOsdUserData.ucODGain)
#define SET_OSD_OD_GAIN(x)                          (g_stOsdUserData.ucODGain = (x))

//--------------------------------------------------
// MACRO for DCR Status
//--------------------------------------------------
#define GET_OSD_DCR_STATUS()                        (g_stOsdUserData.b1OsdDcrStatus)
#define SET_OSD_DCR_STATUS(x)                       (g_stOsdUserData.b1OsdDcrStatus = (x))

//--------------------------------------------------
// MACRO for FreeSync Status
//--------------------------------------------------
#define GET_OSD_FREE_SYNC_STATUS()                  (g_stOsdUserData.b1FreeSyncStatus)
#define SET_OSD_FREE_SYNC_STATUS(x)                 (g_stOsdUserData.b1FreeSyncStatus = (x))

//--------------------------------------------------
// MACRO for Clone Mode
//--------------------------------------------------
#define GET_OSD_CLONE_MODE_1P()                     (g_stOsdUserData.b1CloneMode1P)
#define SET_OSD_CLONE_MODE_1P(x)                    (g_stOsdUserData.b1CloneMode1P = (x))

//--------------------------------------------------
// MACRO for Clone Mode Source
//--------------------------------------------------
#define GET_OSD_CLONE_MODE_MTP()                    (g_stOsdUserData.ucCloneModeMtP)
#define SET_OSD_CLONE_MODE_MTP(x)                   (g_stOsdUserData.ucCloneModeMtP = (x))

//--------------------------------------------------
// MACRO for Volume Mute
//--------------------------------------------------
#define GET_OSD_VOLUME_MUTE()                       (g_stOsdUserData.b1VolumeMute)
#define SET_OSD_VOLUME_MUTE(x)                      (g_stOsdUserData.b1VolumeMute = (x))

//--------------------------------------------------
// MACRO for Volume
//--------------------------------------------------
#define GET_OSD_VOLUME()                            (g_stOsdUserData.ucVolume)
#define SET_OSD_VOLUME(x)                           (g_stOsdUserData.ucVolume = (x))

//--------------------------------------------------
// MACRO for Audio Stand a long
//--------------------------------------------------
#define GET_OSD_AUDIO_STAND_ALONE()                 (g_stOsdUserData.b1AudioStandAloneStatus)
#define SET_OSD_AUDIO_STAND_ALONE(x)                (g_stOsdUserData.b1AudioStandAloneStatus = (x))

//--------------------------------------------------
// MACRO for Audio Source
//--------------------------------------------------
//#define GET_OSD_AUDIO_SOURCE()                      (g_stOsdUserData.b3AudioSourceStatus)
//#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOsdUserData.b3AudioSourceStatus = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_HLWIN_TYPE()                        (g_stOsdUserData.ucHLWinType)
#define SET_OSD_HLWIN_TYPE(x)                       (g_stOsdUserData.ucHLWinType = (x))

//--------------------------------------------------
// MACRO for 3D Status
//--------------------------------------------------
#define GET_OSD_3D_STATUS()                         (g_stOsdUserData.b23DStatus)
#define SET_OSD_3D_STATUS(x)                        (g_stOsdUserData.b23DStatus = (x))

//--------------------------------------------------
// MACRO for 3D LR Status
//--------------------------------------------------
#define GET_OSD_3D_LR_STATUS()                      (g_stOsdUserData.b13DLRStatus)
#define SET_OSD_3D_LR_STATUS(x)                     (g_stOsdUserData.b13DLRStatus = (x))

//--------------------------------------------------
// MACRO for 3D Format Status
//--------------------------------------------------
#define GET_OSD_3D_FORMAT_STATUS()                  (g_stOsdUserData.b23DFormatStatus)
#define SET_OSD_3D_FORMAT_STATUS(x)                 (g_stOsdUserData.b23DFormatStatus = (x))

//--------------------------------------------------
// MACRO for 3D EFFECT
//--------------------------------------------------
#define GET_OSD_3D_EFFECT()                         (g_stOsdUserData.uc3DEffect)
#define SET_OSD_3D_EFFECT(x)                        (g_stOsdUserData.uc3DEffect = (x))

//--------------------------------------------------
// MACRO for 3D 3DTO2D
//--------------------------------------------------
#define GET_OSD_3D_3DTO2D()                         (g_stOsdUserData.b13D3DTO2DStatus)
#define SET_OSD_3D_3DTO2D(x)                        (g_stOsdUserData.b13D3DTO2DStatus = (x))

//--------------------------------------------------
// MACRO for 3D Convergence
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE()                    (g_stOsdUserData.uc3DConvergence)
#define SET_OSD_3D_CONVERGENCE(x)                   (g_stOsdUserData.uc3DConvergence = (x))

//--------------------------------------------------
// MACRO for 3D Convergence Mode
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE_MODE()               (g_stOsdUserData.b33DConvergenceMode)
#define SET_OSD_3D_CONVERGENCE_MODE(x)              (g_stOsdUserData.b33DConvergenceMode = (x))

//--------------------------------------------------
// MACRO for Auto-Color Type
//--------------------------------------------------
#define _AUTO_COLOR_TYPE_INTERNAL                   0
#define _AUTO_COLOR_TYPE_EXTERNAL                   1

#define GET_OSD_FACTORY_AUTO_COLOR_TYPE()           (g_stOsdUserData.b1FactoryAutoColorType)
#define SET_OSD_FACTORY_AUTO_COLOR_TYPE(x)          (g_stOsdUserData.b1FactoryAutoColorType = (x))


//--------------------------------------------------
// MACRO for FALSE COLOR
//--------------------------------------------------
#if (_FALSE_COLOR_SUPPORT == _ON)
#define _DOWN_ICON_START_COL                        2
#define _FALSE_COLOR_ADJUSTABLE_MAX                 16 // 0~16 17&18 are fixed for White/Grey/Black
#define _FALSE_COLOR_ADJUSTABLE_COLOR_COUNT         19
#define GET_OSD_FALSE_COLOR_STATUS()                (g_stOsdUserData.ucFalseColorStatus)
#define SET_OSD_FALSE_COLOR_STATUS(x)               (g_stOsdUserData.ucFalseColorStatus = (x))
#define GET_OSD_FALSE_COLOR_LEVEL(x)                (g_stOsdUserData.ucFalseColorLevel[x])
#define SET_OSD_FALSE_COLOR_LEVEL(x, y)             (g_stOsdUserData.ucFalseColorLevel[x] = (y))
#endif

//==========================================================================================================
// Macro of NVRam Color Temp Data
//==========================================================================================================

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_R()                (g_stColorProcData.usColorTempR >> 4)
#define SET_COLOR_TEMP_TYPE_USER_R(x)               (g_stColorProcData.usColorTempR = ((x) << 4))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_G()                (g_stColorProcData.usColorTempG >> 4)
#define SET_COLOR_TEMP_TYPE_USER_G(x)               (g_stColorProcData.usColorTempG = ((x) << 4))
//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_B()                (g_stColorProcData.usColorTempB >> 4)
#define SET_COLOR_TEMP_TYPE_USER_B(x)               (g_stColorProcData.usColorTempB = ((x) << 4))



//==========================================================================================================
// Macro of NVRam Input Source Data
//==========================================================================================================


//==========================================================================================================
// Macro of NVRam Input Port Data
//==========================================================================================================

//--------------------------------------------------
// Macro of Aspect Origin Ratio
//--------------------------------------------------
#define GET_OSD_ASPECT_ORIGIN_RATIO(port)           (g_pstOsdInputPortData[port].ucAspectOriginRatio)
#define SET_OSD_ASPECT_ORIGIN_RATIO(port, x)        (g_pstOsdInputPortData[port].ucAspectOriginRatio = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_ASPECT_RATIO_TYPE(port)             (g_pstOsdInputPortData[port].b3AspectRatio)
#define SET_OSD_ASPECT_RATIO_TYPE(port, x)          (g_pstOsdInputPortData[port].b3AspectRatio = (x))

//--------------------------------------------------
// MACRO for Sharpness
//--------------------------------------------------
#define GET_OSD_SHARPNESS(port)                     (g_pstOsdInputPortData[port].b3Sharpness)
#define SET_OSD_SHARPNESS(port, x)                  (g_pstOsdInputPortData[port].b3Sharpness = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_OVERSCAN_STATUS(port)               (g_pstOsdInputPortData[port].b1OverScan)
#define SET_OSD_OVERSCAN_STATUS(port, x)            (g_pstOsdInputPortData[port].b1OverScan = (x))

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR Mode
//--------------------------------------------------
#define GET_OSD_REGION_HDR_MODE(port)               (g_pstOsdInputPortData[port].ucHdrMode)
#define SET_OSD_REGION_HDR_MODE(port,x)             (g_pstOsdInputPortData[port].ucHdrMode = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_REGION_DARK_ENHANCE(port)           (g_pstOsdInputPortData[port].b1HdrDarkEnhanceS)
#define SET_OSD_REGION_DARK_ENHANCE(port,x)         (g_pstOsdInputPortData[port].b1HdrDarkEnhanceS = (x))

#endif

//==========================================================================================================
// Macro of NVRam Region Data
//==========================================================================================================
#define _INSIDE                                     0
#define _OUTSIDE                                    1

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE(region)                 (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorTempType)
#define SET_COLOR_TEMP_TYPE(region, x)              (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorTempType = (x))

//--------------------------------------------------
// MACRO for Ultra Vivid Status
//--------------------------------------------------
#define GET_OSD_ULTRA_VIVID_STATUS(region)          (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b2UltraVividStatus)
#define SET_OSD_ULTRA_VIVID_STATUS(region, x)       (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b2UltraVividStatus = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_GAMMA(region)                       (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3Gamma)
#define SET_OSD_GAMMA(region, x)                    (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3Gamma = (x))

//--------------------------------------------------
// MACRO for Color Effect
//--------------------------------------------------
#define GET_OSD_COLOR_EFFECT(region)                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorEffect)
#define SET_OSD_COLOR_EFFECT(region, x)             (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorEffect = (x))

//--------------------------------------------------
// MACRO for Hue
//--------------------------------------------------
#define GET_OSD_HUE(region)                         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHue)
#define SET_OSD_HUE(region, x)                      (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHue = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_SATURATION(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucSaturation)
#define SET_OSD_SATURATION(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucSaturation = (x))

//--------------------------------------------------
// MACRO for PCM Status
//--------------------------------------------------
#define GET_OSD_PCM_STATUS(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3PCMStatus)
#define SET_OSD_PCM_STATUS(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3PCMStatus = (x))

//--------------------------------------------------
// MACRO for BRIGHTNESS
//--------------------------------------------------
#define GET_OSD_BRIGHTNESS(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usBrightness)
#define SET_OSD_BRIGHTNESS(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usBrightness = (x))

//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_CONTRAST(region)                    (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usContrast)
#define SET_OSD_CONTRAST(region, x)                 (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usContrast = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY(region)            (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1PanelUniformity)
#define SET_OSD_PANEL_UNIFORMITY(region, x)         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1PanelUniformity = (x))



//==========================================================================================================
// Macro of NVRam Display Mode Data
//==========================================================================================================

//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_1P_INPUT_SOURCE()                   (g_stOsdDisplayModeData.ucOsdInputPort0)
#define SET_OSD_1P_INPUT_SOURCE(x)                  (g_stOsdDisplayModeData.ucOsdInputPort0 = (x))

//--------------------------------------------------
// MACRO for 2P Input Source
//--------------------------------------------------
#define GET_OSD_2P_INPUT_SOURCE()                   (g_stOsdDisplayModeData.ucOsdInputPort1)
#define SET_OSD_2P_INPUT_SOURCE(x)                  (g_stOsdDisplayModeData.ucOsdInputPort1 = (x))

//--------------------------------------------------
// MACRO for 3P Input Source
//--------------------------------------------------
#define GET_OSD_3P_INPUT_SOURCE()                   (g_stOsdDisplayModeData.ucOsdInputPort2)
#define SET_OSD_3P_INPUT_SOURCE(x)                  (g_stOsdDisplayModeData.ucOsdInputPort2 = (x))

//--------------------------------------------------
// MACRO for 4P Input Source
//--------------------------------------------------
#define GET_OSD_4P_INPUT_SOURCE()                   (g_stOsdDisplayModeData.ucOsdInputPort3)
#define SET_OSD_4P_INPUT_SOURCE(x)                  (g_stOsdDisplayModeData.ucOsdInputPort3 = (x))

//--------------------------------------------------
// MACRO for OSD Select Region
//--------------------------------------------------
#define GET_OSD_SYSTEM_SELECT_REGION()              (UserAdjustConvertSystemSelectRegion(GET_OSD_SELECT_REGION()))
#define GET_OSD_SYSTEM_DISPLAY_REGION()             (UserAdjustConvertDisplayRegion(GET_OSD_SELECT_REGION()))
#define GET_OSD_SELECT_REGION()                     (g_stOsdDisplayModeData.ucSelectRegion)
#define SET_OSD_SELECT_REGION(x)                    (g_stOsdDisplayModeData.ucSelectRegion = (x))

#define GET_OSD_INVERSE_REGION()                    ((g_stOsdDisplayModeData.ucSelectRegion & 0xFE) | (~g_stOsdDisplayModeData.ucSelectRegion & 0x01))



//--------------------------------------------------
// MACRO for Audio Input Region
//--------------------------------------------------
#define GET_OSD_AUDIO_SOURCE()                      (g_stOsdDisplayModeData.ucAuidioInputRegion)
#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOsdDisplayModeData.ucAuidioInputRegion = (x))



//--------------------------------------------------
// MACRO for Factory Power Saving Case
//--------------------------------------------------
#define GET_FORCE_POW_SAV_STATUS()                  (g_bForcePowSavStatus)
#define SET_FORCE_POW_SAV_STATUS(x)                 (g_bForcePowSavStatus = (x))

//--------------------------------------------------
// Definitions of OSD Number ROW COL
//--------------------------------------------------
#define _OSD_NUMBER_1_ROW                           15
#define _OSD_NUMBER_1_COL                           21

#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
//--------------------------------------------------
// Definitions of OSD
//--------------------------------------------------
#define _PFONT_PAGE_0                               0
#define _PFONT_PAGE_1                               1
#define _PFONT_PAGE_2                               2
#define _PFONT_PAGE_ITEM_1                          3
#define _PFONT_PAGE_ITEM_2                          4
#define _PFONT_PAGE_ITEM_3                          5
#define _PFONT_PAGE_ITEM_4                          6
#define _PFONT_PAGE_ITEM_5                          7
#define _PFONT_PAGE_ITEM_6                          8
#define _PFONT_PAGE_ITEM_7                          9
#define _PFONT_PAGE_ITEM_8                          10
#define _PFONT_PAGE_INFORMATION                     11

#define _OSD_GLOBAL_START                           0x01
#define _OSD_GLOBAL_END                             0x0F

#define _OSD_PAGE_0_START                           0x00
#define _OSD_PAGE_0_END                             0x27

#define _OSD_PAGE_1_START                           0x28
#define _OSD_PAGE_1_END                             0x5F

#define _OSD_PAGE_2_START                           0xC1
#define _OSD_PAGE_2_END                             0xF0

#define _SUB_PAGE_ITEM_1                            (_OSD_PAGE_2_START)
#define _SUB_PAGE_ITEM_1_END                        (_OSD_PAGE_2_START + 6)
#define _SUB_PAGE_ITEM_2                            (_SUB_PAGE_ITEM_1_END)
#define _SUB_PAGE_ITEM_2_END                        (_SUB_PAGE_ITEM_1_END + 6)
#define _SUB_PAGE_ITEM_3                            (_SUB_PAGE_ITEM_2_END)
#define _SUB_PAGE_ITEM_3_END                        (_SUB_PAGE_ITEM_2_END + 10)
#define _SUB_PAGE_ITEM_4                            (_SUB_PAGE_ITEM_3_END)
#define _SUB_PAGE_ITEM_4_END                        (_SUB_PAGE_ITEM_3_END + 5)
#define _SUB_PAGE_ITEM_5                            (_SUB_PAGE_ITEM_4_END)
#define _SUB_PAGE_ITEM_5_END                        (_SUB_PAGE_ITEM_4_END + 6)
#define _SUB_PAGE_ITEM_6                            (_SUB_PAGE_ITEM_5_END)
#define _SUB_PAGE_ITEM_6_END                        (_SUB_PAGE_ITEM_5_END + 8)
#define _SUB_PAGE_ITEM_7                            (_SUB_PAGE_ITEM_6_END)
#define _SUB_PAGE_ITEM_7_END                        (_SUB_PAGE_ITEM_6_END + 6)
#define _SUB_PAGE_ITEM_8                            (_SUB_PAGE_ITEM_7_END)
#define _SUB_PAGE_ITEM_8_END                        (_SUB_PAGE_ITEM_7_END + 6)

#define _OSD_PAGE_INFORMATION_START                 0x28
#define _OSD_PAGE_INFORMATION_END                   0xFF

#define _NORMAL                                     0
#define _CENTER                                     1
#define _START                                      0
#define _RUN                                        1

#define _UP                                         0
#define _DOWN                                       1

#define _OUTSUBSET                                  0
#define _INSUBSET                                   1

//--------------------------------------------------
// Definitions of OSD Window
//--------------------------------------------------
//=========== OSD Window Setting ======================//
//Blending type1:Only windows blending.
//Blending type2:All blending.
//Blending type3:Windows & Character background blending.
#define _WIN0                                       0
#define _WIN1                                       1
#define _WIN2                                       2
#define _WIN3                                       3
#define _WIN4                                       4
#define _WIN5                                       5
#define _WIN6                                       6
#define _WIN7                                       7
#define _WIN8                                       8
#define _WIN9                                       9
#define _WIN_ALL                                    0xFF

#define _WIN0_TRANS                                 (_BIT7 | 0)
#define _WIN1_TRANS                                 (_BIT7 | 1)
#define _WIN2_TRANS                                 (_BIT7 | 2)
#define _WIN3_TRANS                                 (_BIT7 | 3)
#define _WIN4_TRANS                                 (_BIT7 | 4)
#define _WIN5_TRANS                                 (_BIT7 | 5)
#define _WIN6_TRANS                                 (_BIT7 | 6)
#define _WIN7_TRANS                                 (_BIT7 | 7)

#define COLOR(fg, bg)                               ((fg) << 4 | (bg))
#define COLOR0(x)                                   (x)
#define COLOR1(x)                                   (x)
#define COLOR2(x)                                   (x)
#define COLOR3(x)                                   (x)

#define X_START(x)                                  (x)
#define Y_START(x)                                  (x)
#define X_END(x)                                    (x)
#define Y_END(x)                                    (x)

#define _BORDER0_1_PIXEL                            0
#define _BORDER0_2_PIXEL                            1
#define _BORDER0_3_PIXEL                            2
#define _BORDER0_4_PIXEL                            3
#define _BORDER0_5_PIXEL                            4
#define _BORDER0_6_PIXEL                            5
#define _BORDER0_7_PIXEL                            6
#define _BORDER0_8_PIXEL                            7

#define _BORDER1_1_PIXEL                            0x00
#define _BORDER1_2_PIXEL                            0x08
#define _BORDER1_3_PIXEL                            0x10
#define _BORDER1_4_PIXEL                            0x18
#define _BORDER1_5_PIXEL                            0x20
#define _BORDER1_6_PIXEL                            0x28
#define _BORDER1_7_PIXEL                            0x30
#define _BORDER1_8_PIXEL                            0x38

#define _BLEND_DISABLE                              0
#define _BLEND_ENABLE                               0x80
#define _GRADIENT_DISABLE                           0
#define _GRADIENT_ENABLE                            0x40
#define _GRADIENT_DIRECTION_H                       0
#define _GRADIENT_DIRECTION_V                       0x20
#define _BORDER_DISABLE                             0
#define _BORDER_ENABLE                              0x10

#define _1_LEVEL_RER_GRADIENT                       0x20
#define _2_LEVEL_RER_GRADIENT                       0x40
#define _3_LEVEL_RER_GRADIENT                       0x60
#define _4_LEVEL_RER_GRADIENT                       0x80
#define _5_LEVEL_RER_GRADIENT                       0xA0
#define _6_LEVEL_RER_GRADIENT                       0xC0
#define _7_LEVEL_RER_GRADIENT                       0xE0
#define _8_LEVEL_RER_GRADIENT                       0x00

#define _R_GRADIENT_DEC                             0x00
#define _R_GRADIENT_INC                             0x80
#define _G_GRADIENT_DEC                             0x00
#define _G_GRADIENT_INC                             0x40
#define _B_GRADIENT_DEC                             0x00
#define _B_GRADIENT_INC                             0x20

#define _GRADIENT_LEVEL_1                           0
#define _GRADIENT_LEVEL_2                           0x08
#define _GRADIENT_LEVEL_3                           0x10
#define _GRADIENT_LEVEL_4                           0x18

#define _R_GRADIENT_ENABLE                          0x04
#define _R_GRADIENT_DISABLE                         0x00
#define _G_GRADIENT_ENABLE                          0x02
#define _G_GRADIENT_DISABLE                         0x00
#define _B_GRADIENT_ENABLE                          0x01
#define _B_GRADIENT_DISABLE                         0x00

#define _SHADOW_1                                   0x00
#define _SHADOW_2                                   0x02
#define _SHADOW_3                                   0x04
#define _SHADOW_4                                   0x06
#define _3D_BUTTON_1                                0x08
#define _3D_BUTTON_2                                0x0A

#define _WIN0_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN0_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)

#define _WIN0_FUNC_CONTROL                          (_BLEND_ENABLE | _GRADIENT_DISABLE | _GRADIENT_DIRECTION_H | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN0_GRADIENT_CONTROL0                     (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_3 | _R_GRADIENT_INC | _G_GRADIENT_INC | _B_GRADIENT_INC)
#define _WIN0_GRADIENT_CONTROL1                     (_3_LEVEL_RER_GRADIENT)

#define _WIN0_ROTATE_BORDER_PIXEL                   (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN0_ROTATE_BORDER_COLOR                   ((_CP_DARKBLUE << 4) | _CP_DARKBLUE)
#define _WIN0_ROTATE_FUNC_CONTROL                   (_BLEND_ENABLE | _GRADIENT_ENABLE | _GRADIENT_DIRECTION_V | _BORDER_ENABLE | _SHADOW_3)
#define _WIN0_ROTATE_GRADIENT_CONTROL0              (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_4 | _R_GRADIENT_DEC | _G_GRADIENT_DEC | _B_GRADIENT_DEC)
#define _WIN0_ROTATE_GRADIENT_CONTROL1              (_3_LEVEL_RER_GRADIENT)

#define _WIN1_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN1_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)

#define _WIN1_FUNC_CONTROL                          (_BLEND_ENABLE | _GRADIENT_DISABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN1_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN1_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN2_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN2_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN2_FUNC_CONTROL                          (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN2_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN2_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN3_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN3_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN3_FUNC_CONTROL                          (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN3_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN3_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN7_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN7_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN7_FUNC_CONTROL                          (_BLEND_ENABLE)
#define _WIN7_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN7_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN0_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN0_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN0_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN0_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN0_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN1_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN1_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN1_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN1_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN1_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN2_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN2_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN2_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN2_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN2_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN3_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN3_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN3_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN3_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN3_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN4_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN4_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN4_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN4_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN4_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN5_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN5_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN5_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN5_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN5_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN6_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN6_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN6_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN6_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN6_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN7_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN7_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN7_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN7_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN7_TRANS_GRADIENT_CONTROL1               (_DISABLE)



#define _OSD_UNSELECT                               0
#define _OSD_SELECT                                 1
#define _OSD_REJECT                                 2
#define _OSD_ADJUST                                 3
#define _OSD_UNHIGHLIGHT                            4
#define _OSD_HIGHLIGHT                              5
#define _OSD_PRE_SELECT                             6
#define _OSD_SELECT_ADJUST                          7


#define _KEY_INFO_ENTER                             0
#define _KEY_INFO_RIGHT                             1
#define _KEY_INFO_LEFT                              2
#define _KEY_INFO_EXIT                              3
#define _KEY_INFO_BACK                              4
#define _KEY_INFO_ALL                               5   // exit, left, right, enter

//=========== OSD Font Icon Address ======================//
#define _1GLOBAL_START                              0x00                        // Global 49
#define _1DYNAMIC_START                             (_1GLOBAL_START + 50)       // Dynamic 0
#define _1DYNAMIC_ICON_START                        (_1DYNAMIC_START + 0)       // main menu icon (6 x 4 x 8) = 196
#define _2DYNAMIC_START                             0x00
#define _2BIT_ICON_OFFSET                           0xFF

#define _LOGO_START_ADDRESS                         0x00

#define _1BIT_NOTICE_ICON_START                     0x01 // 0x18    // No signal , No support , No cable need 24 x 3 x 3 = 216
#define _1BIT_NOTICE_NO_SUPPORT_ICON                (_1BIT_NOTICE_ICON_START)
#define _1BIT_NOTICE_NO_SUPPORT_TEXT_0              (_1BIT_NOTICE_NO_SUPPORT_ICON + 24)
#define _1BIT_NOTICE_NO_SUPPORT_TEXT_1              (_1BIT_NOTICE_NO_SUPPORT_TEXT_0 + 24)
#define _1BIT_NOTICE_NO_CABLE_ICON                  (_1BIT_NOTICE_NO_SUPPORT_TEXT_1 + 24)
#define _1BIT_NOTICE_NO_CABLE_TEXT_0                (_1BIT_NOTICE_NO_CABLE_ICON + 24)
#define _1BIT_NOTICE_NO_CABLE_TEXT_1                (_1BIT_NOTICE_NO_CABLE_TEXT_0 + 24)
#define _1BIT_NOTICE_NO_SIGNAL_ICON                 (_1BIT_NOTICE_NO_CABLE_TEXT_1 + 24)
#define _1BIT_NOTICE_NO_SIGNAL_TEXT_0               (_1BIT_NOTICE_NO_SIGNAL_ICON + 24)
#define _1BIT_NOTICE_NO_SIGNAL_TEXT_1               (_1BIT_NOTICE_NO_SIGNAL_TEXT_0 + 24)
#define _1BIT_NOTICE_INFORMATION                    (_1BIT_NOTICE_NO_SIGNAL_TEXT_1 + 24)

//=============== 1Bit Icon ========================

typedef enum
{
    ___ = 0,
    _iREALTEK_00,
    _iREALTEK_01,
    _iREALTEK_02,
    _iREALTEK_03,
    _iREALTEK_04,
    _iREALTEK_05,
    _iREALTEK_06,
    _iREALTEK_07,
    _iREALTEK_08,
    _iREALTEK_09,
    _iREALTEK_0A,
    _iREALTEK_0B,
    _iREALTEK_10,
    _iREALTEK_11,
    _iREALTEK_12,
    _iREALTEK_13,
    _iREALTEK_14,
    _iREALTEK_15,
    _iREALTEK_16,
    _iREALTEK_17,
    _iREALTEK_18,
    _iREALTEK_19,
    _iREALTEK_1A,
    _iREALTEK_1B,
    _iLEFT_00,
    _iLEFT_01,
    _iRIGHT_00,
    _iRIGHT_01,
    _iKEY_BACK_00,
    _iKEY_BACK_01,
    _iKEY_BACK_10,
    _iKEY_BACK_11,
    _iKEY_LEFT_00,
    _iKEY_LEFT_01,
    _iKEY_LEFT_10,
    _iKEY_LEFT_11,
    _iKEY_RIGHT_00,
    _iKEY_RIGHT_01,
    _iKEY_RIGHT_10,
    _iKEY_RIGHT_11,
    _iKEY_ENTER_00,
    _iKEY_ENTER_01,
    _iKEY_ENTER_10,
    _iKEY_ENTER_11,
    _iKEY_EXIT_00,
    _iKEY_EXIT_01,
    _iKEY_EXIT_10,
    _iKEY_EXIT_11,
    _iINDICATE,
}EnumOneBitGLOBAL;

//RTD LOGO
#define _LOGO_WINDOW_SIZE_X                         839
#define _LOGO_WINDOW_SIZE_Y                         179

#define _Logo_0x00                                  0x00
#define _Logo_0x01                                  (_Logo_0x00 + 0x01)
#define _Logo_0x02                                  (_Logo_0x00 + 0x02)
#define _Logo_0x03                                  (_Logo_0x00 + 0x03)
#define _Logo_0x04                                  (_Logo_0x00 + 0x04)
#define _Logo_0x05                                  (_Logo_0x00 + 0x05)
#define _Logo_0x06                                  (_Logo_0x00 + 0x06)
#define _Logo_0x07                                  (_Logo_0x00 + 0x07)
#define _Logo_0x08                                  (_Logo_0x00 + 0x08)
#define _Logo_0x09                                  (_Logo_0x00 + 0x09)
#define _Logo_0x0a                                  (_Logo_0x00 + 0x0a)
#define _Logo_0x0b                                  (_Logo_0x00 + 0x0b)
#define _Logo_0x0c                                  (_Logo_0x00 + 0x0c)
#define _Logo_0x0d                                  (_Logo_0x00 + 0x0d)
#define _Logo_0x0e                                  (_Logo_0x00 + 0x0e)
#define _Logo_0x0f                                  (_Logo_0x00 + 0x0f)
#define _Logo_0x10                                  (_Logo_0x00 + 0x10)
#define _Logo_0x11                                  (_Logo_0x00 + 0x11)
#define _Logo_0x12                                  (_Logo_0x00 + 0x12)
#define _Logo_0x13                                  (_Logo_0x00 + 0x13)
#define _Logo_0x14                                  (_Logo_0x00 + 0x14)
#define _Logo_0x15                                  (_Logo_0x00 + 0x15)
#define _Logo_0x16                                  (_Logo_0x00 + 0x16)
#define _Logo_0x17                                  (_Logo_0x00 + 0x17)
#define _Logo_0x18                                  (_Logo_0x00 + 0x18)
#define _Logo_0x19                                  (_Logo_0x00 + 0x19)
#define _Logo_0x1a                                  (_Logo_0x00 + 0x1a)
#define _Logo_0x1b                                  (_Logo_0x00 + 0x1b)
#define _Logo_0x1c                                  (_Logo_0x00 + 0x1c)
#define _Logo_0x1d                                  (_Logo_0x00 + 0x1d)
#define _Logo_0x1e                                  (_Logo_0x00 + 0x1e)
#define _Logo_0x1f                                  (_Logo_0x00 + 0x1f)
#define _Logo_0x20                                  (_Logo_0x00 + 0x20)
#define _Logo_0x21                                  (_Logo_0x00 + 0x21)
#define _Logo_0x22                                  (_Logo_0x00 + 0x22)
#define _Logo_0x23                                  (_Logo_0x00 + 0x23)
#define _Logo_0x24                                  (_Logo_0x00 + 0x24)
#define _Logo_0x25                                  (_Logo_0x00 + 0x25)
#define _Logo_0x26                                  (_Logo_0x00 + 0x26)
#define _Logo_0x27                                  (_Logo_0x00 + 0x27)
#define _Logo_0x28                                  (_Logo_0x00 + 0x28)
#define _Logo_0x29                                  (_Logo_0x00 + 0x29)
#define _Logo_0x2a                                  (_Logo_0x00 + 0x2a)
#define _Logo_0x2b                                  (_Logo_0x00 + 0x2b)
#define _Logo_0x2c                                  (_Logo_0x00 + 0x2c)
#define _Logo_0x2d                                  (_Logo_0x00 + 0x2d)
#define _Logo_0x2e                                  (_Logo_0x00 + 0x2e)
#define _Logo_0x2f                                  (_Logo_0x00 + 0x2f)
#define _Logo_0x30                                  (_Logo_0x00 + 0x30)
#define _Logo_0x31                                  (_Logo_0x00 + 0x31)
#define _Logo_0x32                                  (_Logo_0x00 + 0x32)
#define _Logo_0x33                                  (_Logo_0x00 + 0x33)
#define _Logo_0x34                                  (_Logo_0x00 + 0x34)
#define _Logo_0x35                                  (_Logo_0x00 + 0x35)
#define _Logo_0x36                                  (_Logo_0x00 + 0x36)
#define _Logo_0x37                                  (_Logo_0x00 + 0x37)
#define _Logo_0x38                                  (_Logo_0x00 + 0x38)
#define _Logo_0x39                                  (_Logo_0x00 + 0x39)
#define _Logo_0x3a                                  (_Logo_0x00 + 0x3a)
#define _Logo_0x3b                                  (_Logo_0x00 + 0x3b)
#define _Logo_0x3c                                  (_Logo_0x00 + 0x3c)
#define _Logo_0x3d                                  (_Logo_0x00 + 0x3d)
#define _Logo_0x3e                                  (_Logo_0x00 + 0x3e)
#define _Logo_0x3f                                  (_Logo_0x00 + 0x3f)
#define _Logo_0x40                                  (_Logo_0x00 + 0x40)
#define _Logo_0x41                                  (_Logo_0x00 + 0x41)
#define _Logo_0x42                                  (_Logo_0x00 + 0x42)
#define _Logo_0x43                                  (_Logo_0x00 + 0x43)
#define _Logo_0x44                                  (_Logo_0x00 + 0x44)
#define _Logo_0x45                                  (_Logo_0x00 + 0x45)
#define _Logo_0x46                                  (_Logo_0x00 + 0x46)
#define _Logo_0x47                                  (_Logo_0x00 + 0x47)
#define _Logo_0x48                                  (_Logo_0x00 + 0x48)
#define _Logo_0x49                                  (_Logo_0x00 + 0x49)
#define _Logo_0x4a                                  (_Logo_0x00 + 0x4a)
#define _Logo_0x4b                                  (_Logo_0x00 + 0x4b)
#define _Logo_0x4c                                  (_Logo_0x00 + 0x4c)
#define _Logo_0x4d                                  (_Logo_0x00 + 0x4d)
#define _Logo_0x4e                                  (_Logo_0x00 + 0x4e)
#define _Logo_0x4f                                  (_Logo_0x00 + 0x4f)
#define _Logo_0x50_End                              (_Logo_0x00 + 0x50)

#define _Logo1_0x00                                 (_Logo_0x50_End + 0x00)
#define _Logo1_0x01                                 (_Logo1_0x00 + 0x01)
#define _Logo1_0x02                                 (_Logo1_0x00 + 0x02)
#define _Logo1_0x03                                 (_Logo1_0x00 + 0x03)
#define _Logo1_0x04                                 (_Logo1_0x00 + 0x04)
#define _Logo1_0x05                                 (_Logo1_0x00 + 0x05)
#define _Logo1_0x06                                 (_Logo1_0x00 + 0x06)
#define _Logo1_0x07                                 (_Logo1_0x00 + 0x07)
#define _Logo1_0x08                                 (_Logo1_0x00 + 0x08)
#define _Logo1_0x09                                 (_Logo1_0x00 + 0x09)
#define _Logo1_0x0a                                 (_Logo1_0x00 + 0x0a)
#define _Logo1_0x0b                                 (_Logo1_0x00 + 0x0b)
#define _Logo1_0x0c                                 (_Logo1_0x00 + 0x0c)
#define _Logo1_0x0d                                 (_Logo1_0x00 + 0x0d)
#define _Logo1_0x0e                                 (_Logo1_0x00 + 0x0e)
#define _Logo1_0x0f                                 (_Logo1_0x00 + 0x0f)
#define _Logo1_0x10                                 (_Logo1_0x00 + 0x10)
#define _Logo1_0x11                                 (_Logo1_0x00 + 0x11)
#define _Logo1_0x12                                 (_Logo1_0x00 + 0x12)
#define _Logo1_0x13                                 (_Logo1_0x00 + 0x13)
#define _Logo1_0x14                                 (_Logo1_0x00 + 0x14)
#define _Logo1_0x15                                 (_Logo1_0x00 + 0x15)
#define _Logo1_0x16                                 (_Logo1_0x00 + 0x16)
#define _Logo1_0x17                                 (_Logo1_0x00 + 0x17)
#define _Logo1_0x18                                 (_Logo1_0x00 + 0x18)
#define _Logo1_0x19                                 (_Logo1_0x00 + 0x19)
#define _Logo1_0x1a                                 (_Logo1_0x00 + 0x1a)
#define _Logo1_0x1b                                 (_Logo1_0x00 + 0x1b)
#define _Logo1_0x1c                                 (_Logo1_0x00 + 0x1c)
#define _Logo1_0x1d                                 (_Logo1_0x00 + 0x1d)
#define _Logo1_0x1e                                 (_Logo1_0x00 + 0x1e)
#define _Logo1_0x1f                                 (_Logo1_0x00 + 0x1f)
#define _Logo1_0x20                                 (_Logo1_0x00 + 0x20)
#define _Logo1_0x21                                 (_Logo1_0x00 + 0x21)
#define _Logo1_0x22                                 (_Logo1_0x00 + 0x22)
#define _Logo1_0x23                                 (_Logo1_0x00 + 0x23)
#define _Logo1_0x24                                 (_Logo1_0x00 + 0x24)
#define _Logo1_0x25                                 (_Logo1_0x00 + 0x25)
#define _Logo1_0x26                                 (_Logo1_0x00 + 0x26)
#define _Logo1_0x27                                 (_Logo1_0x00 + 0x27)
#define _Logo1_0x28                                 (_Logo1_0x00 + 0x28)
#define _Logo1_0x29                                 (_Logo1_0x00 + 0x29)
#define _Logo1_0x2a                                 (_Logo1_0x00 + 0x2a)
#define _Logo1_0x2b                                 (_Logo1_0x00 + 0x2b)
#define _Logo1_0x2c                                 (_Logo1_0x00 + 0x2c)
#define _Logo1_0x2d                                 (_Logo1_0x00 + 0x2d)
#define _Logo1_0x2e                                 (_Logo1_0x00 + 0x2e)
#define _Logo1_0x2f                                 (_Logo1_0x00 + 0x2f)
#define _Logo1_0x30                                 (_Logo1_0x00 + 0x30)
#define _Logo1_0x31                                 (_Logo1_0x00 + 0x31)
#define _Logo1_0x32                                 (_Logo1_0x00 + 0x32)
#define _Logo1_0x33                                 (_Logo1_0x00 + 0x33)
#define _Logo1_0x34                                 (_Logo1_0x00 + 0x34)
#define _Logo1_0x35                                 (_Logo1_0x00 + 0x35)
#define _Logo1_0x36                                 (_Logo1_0x00 + 0x36)
#define _Logo1_0x37                                 (_Logo1_0x00 + 0x37)
#define _Logo1_0x38                                 (_Logo1_0x00 + 0x38)
#define _Logo1_0x39                                 (_Logo1_0x00 + 0x39)
#define _Logo1_0x3a                                 (_Logo1_0x00 + 0x3a)
#define _Logo1_0x3b                                 (_Logo1_0x00 + 0x3b)
#define _Logo1_0x3c                                 (_Logo1_0x00 + 0x3c)
#define _Logo1_0x3d                                 (_Logo1_0x00 + 0x3d)
#define _Logo1_0x3e                                 (_Logo1_0x00 + 0x3e)
#define _Logo1_0x3f                                 (_Logo1_0x00 + 0x3f)
#define _Logo1_0x40                                 (_Logo1_0x00 + 0x40)
#define _Logo1_0x41                                 (_Logo1_0x00 + 0x41)
#define _Logo1_0x42                                 (_Logo1_0x00 + 0x42)
#define _Logo1_0x43                                 (_Logo1_0x00 + 0x43)
#define _Logo1_0x44                                 (_Logo1_0x00 + 0x44)
#define _Logo1_0x45                                 (_Logo1_0x00 + 0x45)
#define _Logo1_0x46                                 (_Logo1_0x00 + 0x46)

//=============== 2Bit Icon ========================



//---------------------------------------------------------------------
// Definitions of OSD Show Number Function Used by OsdDisplayShowNumber()
//---------------------------------------------------------------------
#define _ALIGN_LEFT                                 (0)
#define _ALIGN_RIGHT                                (1)

#define _FORCE_SHOW_NUMBER_OFF                      (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                       (1 << 1)

#define _SHOW_1                                     (0 << 4)
#define _SHOW_2                                     (1 << 4)
#define _SHOW_3                                     (2 << 4)
#define _SHOW_4                                     (3 << 4)
#define _SHOW_5                                     (4 << 4)
#define _SHOW_6                                     (5 << 4)

//------------------------------------------------------
// Definitions of OSD Slider Function Used by OsdDisplaySlider()
//------------------------------------------------------
#define _SLIDER_RESOLUTION                          (10)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define _PALETTE_INDEX0                             0   // 0 ~ 15
#define _PALETTE_INDEX1                             1   // 16 ~ 31
#define _PALETTE_INDEX2                             2   // 32 ~ 47
#define _PALETTE_INDEX3                             3   // 48 ~ 63

// OSD Position
#define _POS_DIRECT                                 0
#define _POS_PERCENT                                1

//--------------------------------------------------
// Definations of OSD MAIN MENU
//--------------------------------------------------
#define _OSD_MAIN_MENU_WIDTH                        44
#define _OSD_MAIN_MENU_HEIGHT                       22

#define _OSD_HOTKEY_MENU_WIDTH                      36
#define _OSD_HOTKEY_MENU_HEIGHT                     8

#define _OSD_HOTKEY_SOURCE_MENU_WIDTH               64
#define _OSD_HOTKEY_SOURCE_MENU_HEIGHT              8

#define _OSD_2PLR_INFO_MENU_WIDTH                   48
#define _OSD_2PLR_INFO_MENU_HEIGHT                  8

#define _OSD_2PTB_INFO_MENU_WIDTH                   24
#define _OSD_2PTB_INFO_MENU_HEIGHT                  16

#define _OSD_2PPIP_INFO_MENU_WIDTH                  48
#define _OSD_2PPIP_INFO_MENU_HEIGHT                 16

#define _OSD_4P_INFO_MENU_WIDTH                     48
#define _OSD_4P_INFO_MENU_HEIGHT                    16

//--------------------------------------------------
// Definations of OSD Type
//--------------------------------------------------

#define _OSD_MESSAGE_ROW_START                      2
#define _OSD_MESSAGE_CENTER_COL_START               12
#define _OSD_MESSAGE_CENTER_COL_END                 23

//--------------------------------------------------
// Definations of HL window Border Size
//--------------------------------------------------
#define _HL_WIN_BORDER_SIZE                         2

//--------------------------------------------------
// Definations of Slider
//--------------------------------------------------
#define _SLIDER_LENGHT                              250
#define _SLIDER_HIGH                                20
#define _SLIDER_BORDER_PIXEL                        2
#define _SLIDER_OFFSET                              6

#define _SLIDER_SELECT_BORDER_COLOR                 _CP_GRAY
#define _SLIDER_SELECT_BG_COLOR                     _CP_WHITE

#define _SLIDER_UNSELECT_BORDER_COLOR               _CP_WHITE
#define _SLIDER_UNSELECT_BG_COLOR                   _CP_GRAY

#define _SLIDER_SELECT_COLOR                        _CP_ORANGE
#define _SLIDER_UNSELECT_COLOR                      _CP_BLUE

#define _SLIDER_0                                   0
#define _SLIDER_1                                   1
#define _SLIDER_2                                   2

#define _SELECT                                     1
#define _UNSELECT                                   0

#define _SLIDER_0_BAR_WINDOW                        _OSD_WINDOW_4_8 // _OSD_WINDOW_4_5
#define _SLIDER_0_BG_WINDOW                         _OSD_WINDOW_4_7 // _OSD_WINDOW_4_4
#define _SLIDER_0_BORDER_WINDOW                     _OSD_WINDOW_4_6 // _OSD_WINDOW_4_3

#define _SLIDER_1_BAR_WINDOW                        _OSD_WINDOW_4_8
#define _SLIDER_1_BG_WINDOW                         _OSD_WINDOW_4_7
#define _SLIDER_1_BORDER_WINDOW                     _OSD_WINDOW_4_6

#define _SLIDER_0_ROW                               16
#define _SLIDER_0_COL                               11

#define _ITEM_0                                     0
#define _ITEM_1                                     1
#define _ITEM_2                                     2
#define _ITEM_3                                     3
#define _ITEM_4                                     4
#define _ITEM_5                                     5
#define _ITEM_6                                     6
#define _ITEM_7                                     7

#define _NONE_ITEM                                  8

#define _FONTFROM_0_255                             0x00
#define _FONTFROM_256_512                           _BIT5

//--------------------------------------------------
// Definations of No signal & No cable & No support BLANK_SIZE
//--------------------------------------------------
#define _FONT_WIDTH                                 12
#define _FONT_HEIGHT                                18
#define _MESSAGE_WIDTH_FONT_NUM                     36
#define _MESSAGE_HEIGHT_FONT_NUM                    8
#define _MESSAGE_HEIGHT_MID_FONT_NUM                (_MESSAGE_HEIGHT_FONT_NUM / 2) // (8/2)
#define _MESSAGE_WIDTH_MID_FONT_NUM                 (_MESSAGE_WIDTH_FONT_NUM / 2)  // (36/2)


//--------------------------------------------------
// Definations of Color effect user mode Hue & Saturation
//--------------------------------------------------
#define _COLOR_HUE                                  0
#define _COLOR_SATURATION                           1

//--------------------------------------------------
// HDMI Freesync
//--------------------------------------------------
#define _DDCCI_OPCODE_VCP_HDMI_FREESYNC_SUPPORT     0xE6

//--------------------------------------------------
// Define enter panel uniformity msg adjust from pcm or gamma
//--------------------------------------------------
typedef enum
{
    _FROM_STATE_PCM,
    _FROM_STATE_GAMMA,
    _FROM_STATE_HDR,
}EnumFromWhichState;


//--------------------------------------------------
// Define PCM Soft Proft
//--------------------------------------------------
typedef enum
{
    _PCM_SOFT_MODE_1,
    _PCM_SOFT_MODE_2,
    _PCM_SOFT_MODE_AMOUNT = _PCM_SOFT_MODE_2,
}EnumPCMSoftProftMode;

#if 1// alant add
enum
{
 _GAMMA22_7300=1,
 _GAMMA22_6500,
 _DICOM_7300,
 _DICOM_6500,
 _USER_7300,
 _USER_6500

};
#endif
//--------------------------------------------------
// Define Gamma
//--------------------------------------------------
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_18,
    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,
    _GAMMA_AMOUNT = _GAMMA_24,
}EnumGammaType;

//--------------------------------------------------
// Define HL Window Type
//--------------------------------------------------
typedef enum
{
    _HL_WIN_OFF,
    _HL_WIN_1,
    _HL_WIN_2,
    _HL_WIN_3,
    _HL_WIN_4,
    _HL_WIN_5,
    _HL_WIN_AMOUNT = _HL_WIN_5,
}EnumHLWinType;

//--------------------------------------------------
// Definitions of Display Mode
//--------------------------------------------------
typedef enum
{
    _OSD_DM_1P,
    _OSD_DM_2P_LR,
    _OSD_DM_2P_TB,
    _OSD_DM_2P_PIP,
    _OSD_DM_4P,
    _OSD_DM_AMOUNT,
}EnumOSDDisplayModeDef;

//--------------------------------------------------
// Definitions of Display State Notice Message
//--------------------------------------------------
typedef enum
{
    _OSD_NOTICE_NONE,
    _OSD_NOTICE_KEEP,
    _OSD_NOTICE_NO_SUPPORT,
    _OSD_NOTICE_NO_CABLE,
    _OSD_NOTICE_NO_SIGNAL,
    _OSD_NOTICE_INFO,
    _OSD_NOTICE_AMOUNT,
}EnumOSDDisplayDisplayStateNoticeDef;

//--------------------------------------------------
// Definitions of Select Region
//--------------------------------------------------
typedef enum
{
    _OSD_SR_1P_FULL,
}EnumOSDSelectRegion1PDef;

typedef enum
{
    _OSD_SR_2P_LR_L,
    _OSD_SR_2P_LR_R,
    _OSD_SR_2P_LR_FULL,
}EnumOSDSelectRegion2PLRDef;

typedef enum
{
    _OSD_SR_2P_TB_T,
    _OSD_SR_2P_TB_B,
    _OSD_SR_2P_TB_FULL,
}EnumOSDSelectRegion2PTBDef;

typedef enum
{
    _OSD_SR_2P_PIP_MAIN,
    _OSD_SR_2P_PIP_SUB,
    _OSD_SR_2P_PIP_FULL,
}EnumOSDSelectRegion2PPIPDef;

typedef enum
{
    _OSD_SR_4P_LT_INSIDE,
    _OSD_SR_4P_LT_OUTSIDE,
    _OSD_SR_4P_LB_INSIDE,
    _OSD_SR_4P_LB_OUTSIDE,
    _OSD_SR_4P_RT_INSIDE,
    _OSD_SR_4P_RT_OUTSIDE,
    _OSD_SR_4P_RB_INSIDE,
    _OSD_SR_4P_RB_OUTSIDE,
    _OSD_SR_4P_FULL,
}EnumOSDSelectRegion4PDef;

//--------------------------------------------------
// Definitions of 2P/4P Input Source
//--------------------------------------------------
typedef enum
{
    _OSD_HOTKEY_INPUT_1P,
    _OSD_HOTKEY_INPUT_2P,
    _OSD_HOTKEY_INPUT_3P,
    _OSD_HOTKEY_INPUT_4P,
}EnumOSDS_HOTKEY_INPUTDef;

//--------------------------------------------------
// Define Color Effect
//--------------------------------------------------
typedef enum
{
    _COLOREFFECT_STANDARD,
    _COLOREFFECT_GAME,
    _COLOREFFECT_MOVIE,
    _COLOREFFECT_PHOTO,
    _COLOREFFECT_VIVID,
    _COLOREFFECT_USER,
    _COLOREFFECT_AMOUNT = _COLOREFFECT_USER,
}EnumColorEffectType;

//--------------------------------------------------
// Define Color Effect Six Color
//--------------------------------------------------
typedef enum
{
    _SIXCOLOR_R,
    _SIXCOLOR_Y,
    _SIXCOLOR_G,
    _SIXCOLOR_C,
    _SIXCOLOR_B,
    _SIXCOLOR_M,
    _SIXCOLOR_AMOUNT = _SIXCOLOR_M,
}EnumSixColorType;

//--------------------------------------------------
// Define Ultra Vivid
//--------------------------------------------------
typedef enum
{
    _ULTRA_VIVID_OFF,
    _ULTRA_VIVID_L,
    _ULTRA_VIVID_M,
    _ULTRA_VIVID_H,
    _ULTRA_VIVID_AMOUNT = _ULTRA_VIVID_H,
}EnumUltraVividType;

//--------------------------------------------------
// Define Supported Aspect Ratios
//--------------------------------------------------
typedef enum
{
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_16_BY_9,
    _OSD_ASPECT_RATIO_4_BY_3,
    _OSD_ASPECT_RATIO_5_BY_4,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_ORIGIN,
}EnumAspectRatioTypeIndex;

//--------------------------------------------------
// Define DP Port Version
//--------------------------------------------------
typedef enum
{
    _DP_VER_1_DOT_1 = 0,
    _DP_VER_1_DOT_2,
    _DP_VER_1_DOT_3,
    _DP_VER_AMOUNT = _DP_VER_1_DOT_3,
}EnumOSDDpPortVersionDef;

typedef enum
{
    _MST_OFF = 0,
    _MST_D0,
    _MST_D1,
    _MST_D6,
    _MST_AMOUNT = _MST_D6,
}EnumOSDDpMstTypeDef;

//--------------------------------------------------
// Define Display Image Rotate
//--------------------------------------------------
typedef enum
{
    _DISP_ROTATE_0 = 0,
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _DISP_ROTATE_90,
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _DISP_ROTATE_180,
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _DISP_ROTATE_270,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_HOR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_VER_MIRROR,
#endif

    _DISP_ROTATE_AMOUNT ,
}EnumOSDDispRotateDegree;

//--------------------------------------------------
// Define Display Latency
//--------------------------------------------------
typedef enum
{
    _LATENCY_L = 0,
    _LATENCY_M,
    _LATENCY_H,
    _LATENCY_AMOUNT = _LATENCY_H,
}EnumOSDDLatency;

//--------------------------------------------------
// Define HotKey Option
//--------------------------------------------------
typedef enum
{
    _HOTKEY_DDCCI = 0,
    _HOTKEY_AMOUNT = _HOTKEY_DDCCI,
}EnumOSDHotKeyDef;

//--------------------------------------------------
// Definitions of Input Port
//--------------------------------------------------
typedef enum
{
    _OSD_INPUT_A0 = 0,
    _OSD_INPUT_D0,// DP
    _OSD_INPUT_D1, // HDMI
    _OSD_INPUT_D2, // DVI
    _OSD_INPUT_D3, // 
    _OSD_INPUT_D4,
    _OSD_INPUT_D5,
    _OSD_INPUT_D6,
    _OSD_INPUT_D7,
    _OSD_INPUT_AUTO,
    _OSD_INPUT_AMOUNT = _OSD_INPUT_AUTO,
}EnumOSDInputPort;

//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
typedef enum
{
    _CT_9300,//12500
    _CT_7500,//9300
    _CT_6500,//7500
    _CT_5800,//6500
    _CT_SRGB,//srgb
    _CT_USER,//user
    _CT_COLORTEMP_AMOUNT = _CT_USER,
} EnumOSDInputPortDef;

//--------------------------------------------------
// Definitions of 3D Effect
//--------------------------------------------------
typedef enum
{
    _3D_EFFECT_OFF = _OFF,
    _3D_EFFECT_WEAK,
    _3D_EFFECT_MEDIUM,
    _3D_EFFECT_STRONG,
    _3D_EFFECT_AMOUNT = _3D_EFFECT_STRONG,
} EnumOSDSelect3DEffectDef;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
#if(_OCC_SUPPORT == _ON)
    _PCM_OSD_SRGB,
    _PCM_OSD_ADOBE_RGB,
#endif

    _PCM_OSD_USER,
    _PCM_OSD_NATIVE,
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
    _PCM_OSD_SOFT_PROFT,
    _PCM_OSD_AMOUNT = _PCM_OSD_SOFT_PROFT,
#else
    _PCM_OSD_AMOUNT = _PCM_OSD_NATIVE,
#endif
}EnumPCMTypeIndex;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_OSD_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_OSD_TYPE2,      // gamma 2.0
    _UNIFORMITY_OSD_TYPE3,      // gamma 2.2
    _UNIFORMITY_OSD_TYPE4,      // gamma 2.4
    _UNIFORMITY_OSD_TYPE5,      // srgb
    _UNIFORMITY_OSD_TYPE6,      // adobe rgb
}EnumUniformityTypeSelectIndex;
//--------------------------------------------------
// Definitions of Clone Mode
//--------------------------------------------------
typedef enum
{
    _OSD_CLONE_1P_OFF = _OFF,
    _OSD_CLONE_1P_ON,
}EnumOSDCloneMode1PDef;

typedef enum
{
    _OSD_CLONE_MTP_OFF = 0,
    _OSD_CLONE_MTP_A0,
    _OSD_CLONE_MTP_D0,
    _OSD_CLONE_MTP_D1,
    _OSD_CLONE_MTP_D2,
    _OSD_CLONE_MTP_D3,
    _OSD_CLONE_MTP_D4,
    _OSD_CLONE_MTP_D5,
    _OSD_CLONE_MTP_D6,
}EnumOSDCloneModeMtPDef;
#if(_FALSE_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Clone Mode
//--------------------------------------------------
typedef enum
{
    _OSD_FALSE_COLOR_OFF = 0,
    _OSD_FALSE_COLOR_MODE1,
    _OSD_FALSE_COLOR_MODE2 ,
    _OSD_FALSE_COLOR_MODE3,
    _OSD_FALSE_COLOR_USER,
}EnumOSDFalseColorDef;
#endif

typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
    BYTE b1OsdWakeUpShowDisplayMode : 1;
    BYTE b1OsdWakeUpShowDpOption : 1;
    BYTE b1OsdFactoryModeStatus : 1;
    BYTE b3OsdsixColor : 3;
    BYTE b1OsdDoubleSizeStatus : 1;
    BYTE b1FreezeStatus : 1;
#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
    BYTE b1FreezeDisableOsdStatus : 1;
#endif
#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FALSE_COLOR_SUPPORT == _ON))
    BYTE b1FalseColorDisableOsdStatus : 1;
#endif
    WORD usOsdStatePrevious;
    WORD usOsdState;
    BYTE ucOsdEventMsg;
    BYTE ucOsdKeyMessage;
    BYTE ucOsdKeyControl;
    BYTE ucOsdDoAspectRatio;
    BYTE ucOsdColorFormat[_OSD_INPUT_AMOUNT];


    BYTE b3OsdsixColorHue;
    BYTE b3OsdsixColorSaturation;
    BYTE ucOsdColorTempOsdItem;

#if(_FREESYNC_SUPPORT == _ON)
    BYTE ucOsdFREESYNCInforOsdAddress;
#endif
}StructOsdInfo;


typedef enum
{
    _ = 0,
    _0_,_1_,_2_,_3_,_4_,_5_,_6_,_7_,_8_,_9_,
    _A_, _B_, _C_, _D_, _E_, _F_, _G_, _H_, _I_, _J_, _K_, _L_, _M_, _N_, _O_, _P_, _Q_, _R_, _S_, _T_, _U_, _V_, _W_, _X_, _Y_, _Z_,
    _a_, _b_, _c_, _d_, _e_, _f_, _g_, _h_, _i_, _j_, _k_, _l_, _m_, _n_, _o_, _p_, _q_, _r_, _s_, _t_, _u_, _v_, _w_, _x_, _y_, _z_,
    _A0_,_a0_, _a1_, _a2_, _a3_, _a4_,_c0_, _E0_, _e0_, _e1_, _e2_, _n0_, _u0_, _u1_, _u2_, _o0_, _o1_, _o2_, _o3_,_i0_,

    _UPDOT_,                // '
    _DOT_,                  // .
    _LEFT_BRACE_,           // (
    _RIGHT_BRACE_,          // )
    _AND_,                  // /
    _COLON_,                // :
    _AT_0_,                 // @
    _COMMA_,                // ,
    _SLINE_,                // -
    _SHIFT_LEFT_,           // <<
    _SHIFT_RIGHT_,          // >>
#if (_FALSE_COLOR_SUPPORT == _ON)
    _PERCENTAGE_,           // %
#else
    _SEPERATE_,             // ;
#endif
    _QUERY_,                // ?
}EnumOSDFontDef;

typedef enum
{
    _CP_EMPTY = 0,
    _CP_BG = 0,
    _CP_BLACK = 0,
    _CP_WHITE,
    _CP_BLUE_120,
    _CP_GREEN_119,
    _CP_BLUE,
    _CP_YELLOW,
    _CP_GRAY,
    _CP_ORANGE,
    _CP_LIGHTBLUE,
    _CP_SELECTBOTTOM,
    _CP_PINK,
    _CP_RED,
    _CP_GREEN_1,
    _CP_ORANGE_DARK,
    _CP_ORANGE_H,
    _CP_GRAY_1,

}EnumOSDColorPaletteDef;

typedef enum
{
    _LOGO_CP_BG = 0,
    _LOGO_CP_BLACK = 0,
    _LOGO_CP_WHITE,
    _LOGO_CP_RED,
    _LOGO_CP_GREEN,
    _LOGO_CP_BLUE,
    _LOGO_CP_YELLOW,
    _LOGO_CP_GRAY,
    _LOGO_CP_DARKBLUE,
    _LOGO_CP_LIGHTBLUE,
    _LOGO_CP_SELECTBOTTOM,
    _LOGO_CP_PINK,
    _LOGO_CP_RED_1,
    _LOGO_CP_GREEN_1,
    _LOGO_CP_ORANGE_L,
    _LOGO_CP_ORANGE_H,
    _LOGO_CP_GRAY_1,
}EnumOSDColorPaletteLogo;

typedef enum
{
    _MENU_NONE,

//    _MENU_DISPLAYMODE,
    _MENU_DISPLAYFUNCTION,
//    _MENU_SELECTREGION,
    _MENU_PICTURE,
//    _MENU_ANALOG,
    _MENU_COLOR,
    _MENU_ADVANCE,
    _MENU_INPUT,
   // _MENU_AUDIO,
    _MENU_OTHER,
    _MENU_INFORMATION,
    _MENU_AUDIO,
     _MENU_ANALOG,
    _MENU_DISPLAYMODE,
      _MENU_SELECTREGION,
    _MENU_FACTORY,

    _MENU_DISPLAYMODE_1P,
    _MENU_DISPLAYMODE_2P_LR,
    _MENU_DISPLAYMODE_2P_TB,
    _MENU_DISPLAYMODE_2P_PIP,
    _MENU_DISPLAYMODE_4P,

    _MENU_DISPLAYFUN_DISP_ROTATE,
    _MENU_DISPLAYFUN_LATENCY,
    _MENU_DISPLAYFUN_FREEZE,

    _MENU_DISPLAYFUN_LR_RATIO,
    _MENU_DISPLAYFUN_LR_INPUT_SWAP,
    _MENU_DISPLAYFUN_TB_INPUT_SWAP,
    _MENU_DISPLAYFUN_PIP_POSITION,
    _MENU_DISPLAYFUN_PIP_TRANSPARENCY,
    _MENU_DISPLAYFUN_PIP_SIZE,
    _MENU_DISPLAYFUN_PIP_INPUT_SWAP,

    _MENU_SELECTREGIOM_2P_LR_L,
    _MENU_SELECTREGIOM_2P_LR_R,
    _MENU_SELECTREGIOM_2P_LR_FULL,

    _MENU_SELECTREGIOM_2P_TB_T,
    _MENU_SELECTREGIOM_2P_TB_B,
    _MENU_SELECTREGIOM_2P_TB_FULL,

    _MENU_SELECTREGIOM_2P_PIP_MAIN,
    _MENU_SELECTREGIOM_2P_PIP_SUB,
    _MENU_SELECTREGIOM_2P_PIP_FULL,

    _MENU_SELECTREGIOM_4P_LT_IN,
    _MENU_SELECTREGIOM_4P_LT_OUT,
    _MENU_SELECTREGIOM_4P_LB_IN,
    _MENU_SELECTREGIOM_4P_LB_OUT,

    _MENU_SELECTREGIOM_4P_RT_IN,
    _MENU_SELECTREGIOM_4P_RT_OUT,
    _MENU_SELECTREGIOM_4P_RB_IN,
    _MENU_SELECTREGIOM_4P_RB_OUT,

    _MENU_SELECTREGIOM_4P_FULL,

    _MENU_PICTURE_BACKLIGHT,
    _MENU_PICTURE_BRIGHTNESS,
    _MENU_PICTURE_CONTRAST,
    _MENU_PICTURE_SHARPNESS,

    _MENU_ANALOG_AUTO,
    _MENU_ANALOG_HPOS,
    _MENU_ANALOG_VPOS,
    _MENU_ANALOG_CLOCK,
    _MENU_ANALOG_PHASE,

  //  _MENU_COLOR_PANEL_UNIFORMITY,
    _MENU_COLOR_GAMMA,
    _MENU_COLOR_TEMPERATURE,
    _MENU_COLOR_EFFECT,
 //   _MENU_COLOR_DEMO,
  //  _MENU_COLOR_FORMAT,
  //  _MENU_COLOR_PCM,
    _MENU_COLOR_HUE,
    _MENU_COLOR_SATURATION,
    _MENU_COLOR_FORMAT,
    _MENU_COLOR_DEMO,
    _MENU_COLOR_PANEL_UNIFORMITY,
    _MENU_COLOR_PCM,
    
     _MENU_ADVANCE_ASPECT,
       _MENU_ADVANCE_DDCCI,
    _MENU_ADVANCE_OVER_SCAN,
    _MENU_ADVANCE_OVER_DRIVE,
   // _MENU_ADVANCE_DDCCI,
    _MENU_ADVANCE_ULTRA_VIVID,
    _MENU_ADVANCE_DCR,
    _MENU_ADVANCE_DP_OPTION,
    _MENU_ADVANCE_DP_MST,
    _MENU_ADVANCE_DP_EDID,
    _MENU_ADVANCE_CLONE,
    _MENU_ADVANCE_FREESYNC,
    _MENU_ADVANCE_DP_LANE_COUNT,

#if(_ULTRA_HDR_SUPPORT == _ON)
    _MENU_ADVANCE_HDR,
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
    _MENU_ADVANCE_FALSE_COLOR,
#endif

    _MENU_INPUT_SOURCE_1P,
    _MENU_INPUT_SOURCE_2P,
    _MENU_INPUT_SOURCE_3P,
    _MENU_INPUT_SOURCE_4P,
    _MENU_INPUT_SOURCE_1P_ADJ,
    _MENU_INPUT_SOURCE_2P_ADJ,
    _MENU_INPUT_SOURCE_3P_ADJ,
    _MENU_INPUT_SOURCE_4P_ADJ,


   _MENU_AUDIO_AUDIO_SOURCE,
    _MENU_AUDIO_VOLUME,
    _MENU_AUDIO_MUTE,
    _MENU_AUDIO_STAND_ALONG,
//    _MENU_AUDIO_AUDIO_SOURCE,
    _MENU_AUDIO_SOUND_MODE,

    _MENU_OTHER_RESET,
    _MENU_OTHER_MENU_TIME,
    _MENU_OTHER_OSD_HPOS,
    _MENU_OTHER_OSD_VPOS,
    _MENU_OTHER_LANGUAGE,
    _MENU_OTHER_TRNASPARENCY,
    _MENU_OTHER_ROTATE,
    _MENU_OTHER_BORDER_WIDTH,//usb power
    _MENU_OTHER_BORDER_COLOR,

    _MENU_DISPLAYFUN_DISP_ROTATE_ADJUST,
    _MENU_DISPLAYFUN_LATENCY_ADJUST,
    _MENU_DISPLAYFUN_FREEZE_ADJUST,

    _MENU_DISPLAYFUN_LR_RATIO_ADJUST,
    _MENU_DISPLAYFUN_PIP_POSITION_ADJUST,
    _MENU_DISPLAYFUN_PIP_POSITION_H,
    _MENU_DISPLAYFUN_PIP_POSITION_V,
    _MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST,
    _MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST,
    _MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST,
    _MENU_DISPLAYFUN_PIP_SIZE_ADJUST,

    _MENU_PICTURE_BACKLIGHT_ADJUST,
    _MENU_PICTURE_BRIGHTNESS_ADJUST,
    _MENU_PICTURE_CONTRAST_ADJUST,
    _MENU_PICTURE_SHARPNESS_ADJUST,

    _MENU_ANALOG_HPOS_ADJUST,
    _MENU_ANALOG_VPOS_ADJUST,
    _MENU_ANALOG_CLOCK_ADJUST,
    _MENU_ANALOG_PHASE_ADJUST,

  //  _MENU_COLOR_PANEL_UNIFORMITY_ADJUST,
    _MENU_COLOR_GAMMA_ADJUST,
    _MENU_COLOR_TEMPERATURE_ADJUST,
    _MENU_COLOR_EFFECT_ADJUST,
 //   _MENU_COLOR_DEMO_ADJUST,
//    _MENU_COLOR_FORMAT_ADJUST,
//    _MENU_COLOR_PCM_ADJUST,
    _MENU_COLOR_HUE_ADJUST,
    _MENU_COLOR_SATURATION_ADJUST,
       _MENU_COLOR_FORMAT_ADJUST,
      _MENU_COLOR_DEMO_ADJUST,
_MENU_COLOR_PANEL_UNIFORMITY_ADJUST,
    _MENU_COLOR_PCM_ADJUST,
    
    _MENU_ADVANCE_ASPECT_ADJUST,
       _MENU_ADVANCE_DDCCI_ADJUST,
    _MENU_ADVANCE_OVER_SCAN_ADJUST,
    _MENU_ADVANCE_OVER_DRIVE_ONOFF,
    _MENU_ADVANCE_OVER_DRIVE_GAIN,
  //  _MENU_ADVANCE_DDCCI_ADJUST,
    _MENU_ADVANCE_ULTRA_VIVID_ADJUST,
    _MENU_ADVANCE_DCR_ADJUST,
    _MENU_ADVANCE_DP_OPTION_D0,
    _MENU_ADVANCE_DP_OPTION_D1,
    _MENU_ADVANCE_DP_OPTION_D6,
    _MENU_ADVANCE_DP_MST_ADJUST,
    _MENU_ADVANCE_CLONE_ADJUST,
    _MENU_ADVANCE_FREESYNC_ADJUST,
    _MENU_ADVANCE_SINGLE_DP_EDID,
    _MENU_ADVANCE_DUAL_DP_EDID,
    _MENU_ADVANCE_SINGLE_DP_EDID_ADJUST,
    _MENU_ADVANCE_DUAL_DP_EDID_ADJUST,
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
    _MENU_ADVANCE_EDID_ADJUST,
    _MENU_ADVANCE_EDID_DX_ADJUST,
#endif
    _MENU_ADVANCE_DP_LANE_COUNT_D0,
    _MENU_ADVANCE_DP_LANE_COUNT_D1,
    _MENU_ADVANCE_DP_LANE_COUNT_D6,

#if(_ULTRA_HDR_SUPPORT == _ON)
    _MENU_ADVANCE_HDR_MODE,
    _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF,
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
    _MENU_ADVANCE_FALSE_COLOR_ADJUST,
    _MENU_ADVANCE_FALSE_COLOR_USER,
    _MENU_ADVANCE_FALSE_COLOR_USER_ADJUST,
#endif


   _MENU_AUDIO_AUDIO_SOURCE_SELECT,
    _MENU_AUDIO_VOLUME_ADJUST,
    _MENU_AUDIO_MUTE_ON_OFF,
    _MENU_AUDIO_STAND_ALONG_SELECT,
//    _MENU_AUDIO_AUDIO_SOURCE_SELECT,
    _MENU_AUDIO_SOUND_MODE_SELECT,

    _MENU_OTHER_MENU_TIME_ADJUST,
    _MENU_OTHER_OSD_HPOS_ADJUST,
    _MENU_OTHER_OSD_VPOS_ADJUST,
    _MENU_OTHER_LANGUAGE_ADJUST,
    _MENU_OTHER_TRNASPARENCY_ADJUST,
    _MENU_OTHER_ROTATE_ADJUST,
    _MENU_OTHER_BORDER_WIDTH_ADJUST,
    _MENU_OTHER_BORDER_COLOR_ADJUST,

    _MENU_COLOR_TEMP_USER_R,
    _MENU_COLOR_TEMP_USER_G,
    _MENU_COLOR_TEMP_USER_B,

    _MENU_COLOR_TEMP_USER_ADJUST_R,
    _MENU_COLOR_TEMP_USER_ADJUST_G,
    _MENU_COLOR_TEMP_USER_ADJUST_B,

    _MENU_COLOR_EFF_USER_R,
    _MENU_COLOR_EFF_USER_Y,
    _MENU_COLOR_EFF_USER_G,
    _MENU_COLOR_EFF_USER_C,
    _MENU_COLOR_EFF_USER_B,
    _MENU_COLOR_EFF_USER_M,

    _MENU_COLOR_EFF_USER_R_HUE,
    _MENU_COLOR_EFF_USER_R_SAT,
    _MENU_COLOR_EFF_USER_Y_HUE,
    _MENU_COLOR_EFF_USER_Y_SAT,
    _MENU_COLOR_EFF_USER_G_HUE,
    _MENU_COLOR_EFF_USER_G_SAT,
    _MENU_COLOR_EFF_USER_C_HUE,
    _MENU_COLOR_EFF_USER_C_SAT,
    _MENU_COLOR_EFF_USER_B_HUE,
    _MENU_COLOR_EFF_USER_B_SAT,
    _MENU_COLOR_EFF_USER_M_HUE,
    _MENU_COLOR_EFF_USER_M_SAT,

    _MENU_COLOR_EFF_USER_R_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_R_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_Y_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_Y_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_G_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_G_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_C_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_C_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_B_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_B_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_M_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_M_SAT_ADJUST,

    _MENU_COLOR_PCM_SOFT_PROFT_ADJUST,

    _MENU_ADVANCE_OD_ONOFF_ADJUST,
    _MENU_ADVANCE_OD_GAIN_ADJUST,

    _MENU_ADVANCE_DP_D0_VERSION_ADJUST,
    _MENU_ADVANCE_DP_D1_VERSION_ADJUST,
    _MENU_ADVANCE_DP_D6_VERSION_ADJUST,

    _MENU_ADVANCE_DP_D0_LANE_COUNT_ADJUST,
    _MENU_ADVANCE_DP_D1_LANE_COUNT_ADJUST,
    _MENU_ADVANCE_DP_D6_LANE_COUNT_ADJUST,

#if(_ULTRA_HDR_SUPPORT == _ON)
    _MENU_ADVANCE_HDR_MODE_ADJUST,
    _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST,
#endif

    _MENU_HOTKEY_DDCCI,


    _MENU_HOTKEY_SOURCE,
    _MENU_HOTKEY_DISPLAY_MODE,

    _MENU_HOTKEY_INFORMATION, // 180

    _MENU_PANEL_UNIFORMITY_MSG_ADJUST,

    _MENU_MESSAGE_DISPLAY,

    _MENU_END,
}EnumOsdMenuStatus;

typedef enum
{
    _ICON_PAGE_CLEAR = 0,
    _ICON_PAGE_MAIN_0,
    _ICON_PAGE_MAIN_1,
    _ICON_PAGE_MAIN_2,

    _ICON_PAGE_DISPLAYMODE_0,
    _ICON_PAGE_DISPLAYMODE_1,

    _ICON_PAGE_DISPLAYFUNCTION,

    _ICON_PAGE_SELECTREGION_2P_LR,
    _ICON_PAGE_SELECTREGION_2P_TB,
    _ICON_PAGE_SELECTREGION_2P_PIP,
    _ICON_PAGE_SELECTREGION_4P_0,
    _ICON_PAGE_SELECTREGION_4P_1,
    _ICON_PAGE_SELECTREGION_4P_2,

    _ICON_PAGE_PICTURE_0,

    _ICON_PAGE_ANALOG_0,
    _ICON_PAGE_ANALOG_1,

    _ICON_PAGE_COLOR_0,
    _ICON_PAGE_COLOR_1,
    _ICON_PAGE_COLOR_2,

    _ICON_PAGE_ADVANCE_0,
    _ICON_PAGE_ADVANCE_1,
    _ICON_PAGE_ADVANCE_2,
    _ICON_PAGE_ADVANCE_3,

    _ICON_PAGE_INPUT_0,
    _ICON_PAGE_INPUT_1,
    _ICON_PAGE_INPUT_2,

    _ICON_PAGE_INPUT_2P_LR,
    _ICON_PAGE_INPUT_2P_TB,
    _ICON_PAGE_INPUT_2P_PIP,
    _ICON_PAGE_INPUT_4P,

    _ICON_PAGE_AUDIO_0,
    _ICON_PAGE_AUDIO_1,

    _ICON_PAGE_OTHER_0,
    _ICON_PAGE_OTHER_1,
    _ICON_PAGE_OTHER_2,

    _ICON_PAGE_INFORMATION_0,

    _ICON_PAGE_FACTORY_0,

    _ICON_PAGE_ON_OFF,
    _ICON_PAGE_ASPECT_RATIO_0,
    _ICON_PAGE_ASPECT_RATIO_1,
    _ICON_PAGE_AUDIO_SOURCE_0,
    _ICON_PAGE_AUDIO_SOURCE_1,
    _ICON_PAGE_ULTRA_VIVID,

    _ICON_PAGE_GAMMA_0,
    _ICON_PAGE_GAMMA_1,
    _ICON_PAGE_TEMPRATURE_0,
    _ICON_PAGE_TEMPRATURE_1,

    _ICON_PAGE_COLOR_EFFECT_0,
    _ICON_PAGE_COLOR_EFFECT_1,

    _ICON_PAGE_COLOR_DEMO_0,
    _ICON_PAGE_COLOR_DEMO_1,

    _ICON_PAGE_COLOR_FORMAT,

    _ICON_PAGE_COLOR_PCM_0,
    _ICON_PAGE_COLOR_PCM_1,
    _ICON_PAGE_TEMPERATURE_USER,
    _ICON_PAGE_COLOR_EFFECT_USER_0,
    _ICON_PAGE_COLOR_EFFECT_USER_1,
    _ICON_PAGE_COLOR_RGBYCM_HUE_SAT,

    _ICON_PAGE_PCM_SOFT_PROFT,
    _ICON_PAGE_OSD_ROTATE,
    _ICON_PAGE_OD_ADJUST,

    _ICON_PAGE_DP_OPTION,
    _ICON_PAGE_DP_1_DOT_X,
    _ICON_PAGE_DP_MST,
    _ICON_PAGE_DISP_ROTATE_0,
    _ICON_PAGE_DISP_ROTATE_1,
    _ICON_PAGE_LATENCY,
    _ICON_PAGE_DP_EDID,
    _ICON_PAGE_CLONE_0,
    _ICON_PAGE_CLONE_1,
    _ICON_PAGE_CLONE_2,
    _ICON_PAGE_FREESYNC,

    _ICON_PAGE_BORDER_COLOR,
    _ICON_PAGE_PIP_POSITION_0,
    _ICON_PAGE_PIP_POSITION_1,
    _ICON_PAGE_PIP_USER_POSITION,
    _ICON_PAGE_SINGLE_DP_EDID,
    _ICON_PAGE_DUAL_DP_EDID,
    _ICON_PAGE_DP_LANE_COUNT,
    _ICON_PAGE_DP_LANE_X,

    _ICON_PAGE_HDR_ADJUST, // _ULTRA_HDR_SUPPORT
    _ICON_PAGE_HDR_MODE, // _ULTRA_HDR_SUPPORT

#if (_FALSE_COLOR_SUPPORT == _ON)
    _ICON_PAGE_FALSE_COLOR_0,
    _ICON_PAGE_FALSE_COLOR_1,
    _ICON_PAGE_FALSE_COLOR_USER,
#endif
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
    _ICON_PAGE_EDID_PORT_0,
    _ICON_PAGE_EDID_PORT_1,
    _ICON_PAGE_HDMI_EDID_D0,
    _ICON_PAGE_HDMI_EDID_D1,
    _ICON_PAGE_HDMI_EDID_D2,
    _ICON_PAGE_HDMI_EDID_D3,
    _ICON_PAGE_HDMI_EDID_D4,
    _ICON_PAGE_HDMI_EDID_D5,
#endif

      _ICON_PAGE_LANGUAGE_0,
	_ICON_PAGE_LANGUAGE_1,
}EnumIconPage;

typedef enum
{
    _ICON_SUB_SEL_NONE,
    _ICON_SUB_SEL_INPUT,
    _ICON_SUB_SEL_MF_INPUT,
    _ICON_SUB_SEL_DISPLAYMODE,
    _ICON_SUB_SEL_SELECTREGION,
}EnumIconSubSel;

typedef enum
{
    _ICON_NONE = 0,
    // main
  //  _ICON_DISPLAYMODE,
    _ICON_DISPLAYFUNCTION,
//    _ICON_SELECTREGION,
    _ICON_PICTURE,
   // _ICON_ANALOG,
    _ICON_COLOR,
    _ICON_ADVANCE,
    _ICON_INPUT,
 //   _ICON_AUDIO,
    _ICON_OTHER,
    _ICON_INFORMATION,
     _ICON_AUDIO,
    _ICON_ANALOG,
_ICON_DISPLAYMODE,
_ICON_SELECTREGION,
    _ICON_FACTORY,

    // display mode
    _ICON_1P,
    _ICON_2P_LR,
    _ICON_2P_TB,
    _ICON_2P_PIP,
    _ICON_4P,

    // display function
    _ICON_DISP_ROTATE,
    _ICON_LANTENCY,
    _ICON_DISP_LR_RATIO,
    _ICON_PIP_POSITION,
    _ICON_PIP_USER_POSITION_H,
    _ICON_PIP_USER_POSITION_V,
    _ICON_PIP_TRANSPARENCY,
    _ICON_PIP_SIZE,
    _ICON_INPUT_SWAP,

    // select region
    _ICON_2P_LR_L,
    _ICON_2P_LR_R,
    _ICON_2P_LR_FULL,
    _ICON_2P_TB_T,
    _ICON_2P_TB_B,
    _ICON_2P_TB_FULL,
    _ICON_2P_PIP_MAIN,
    _ICON_2P_PIP_SUB,
    _ICON_2P_PIP_FULL,
    _ICON_4P_LT_INSIDE,
    _ICON_4P_LT_OUTSIDE,
    _ICON_4P_LB_INSIDE,
    _ICON_4P_LB_OUTSIDE,
    _ICON_4P_RT_INSIDE,
    _ICON_4P_RT_OUTSIDE,
    _ICON_4P_RB_INSIDE,
    _ICON_4P_RB_OUTSIDE,
    _ICON_4P_FULL,

    // picture
    _ICON_BACKLIGHT,
    _ICON_BRIGHTNESS,
    _ICON_CONTRAST,
    _ICON_SHARPNESS,

    // analog
    _ICON_AUTO_ADJUST,
    _ICON_HPOS,
    _ICON_VPOS,
    _ICON_CLOCK,
    _ICON_PHASE,

    // color
 //   _ICON_PANEL_UNIFORMITY,
    _ICON_GAMMA,
    _ICON_COLOR_TEMPERATURE,
    _ICON_COLOR_EFFECT,
 //   _ICON_COLOR_DEMO,
 //   _ICON_COLOR_FORMAT,
 //  _ICON_PCM,
    _ICON_HUE,
    _ICON_SATURATION,
        _ICON_COLOR_FORMAT,
      _ICON_COLOR_DEMO,
    _ICON_PANEL_UNIFORMITY,
    _ICON_PCM,
    // advance
    _ICON_ASPECT,
    _ICON_DDCCI,
    _ICON_OVER_SCAN,
    _ICON_OVER_DRIVE,

 //   _ICON_DDCCI,
    _ICON_ULTRAVIVID,
    _ICON_DCR,
    _ICON_DP_OPTION,
    _ICON_DP_MST,
    _ICON_DP_EDID,
    _ICON_CLONE,
    _ICON_FREESYNC,
    _ICON_FREEZE,
    _ICON_DP_LANE,
#if(_ULTRA_HDR_SUPPORT == _ON)
    _ICON_HDR,
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
    _ICON_FASLE_COLOR,
#endif
    _ICON_SINGLE_DP_EDID,
    _ICON_DUAL_DP_EDID,

    // input
    _ICON_INPUT_AUTO,

    // audio
    _ICON_AUDIO_SOURCE,
    _ICON_VOLUME,
    _ICON_MUTE,
    _ICON_STAND_ALONG,
  //  _ICON_AUDIO_SOURCE,
    _ICON_SOUND_MODE,

    // other
    _ICON_RESET,
    _ICON_MENU_TIME,
    _ICON_OSD_HPOS,
    _ICON_OSD_VPOS,
    _ICON_LANGUAGE,
    _ICON_TRNASPARENCY,
    _ICON_ROTATE,
    _ICON_BORDER_WIDTH,// user for usb power
    _ICON_BORDER_COLOR,

    // option icon
    _ICON_ON,
    _ICON_OFF,
    _ICON_AUDIO_ANALOG,
    _ICON_AUDIO_ANALOG_JAPAN,  ///Wesley_OSD Analog Japan Picture_20180107
    _ICON_AUDIO_DIGITAL_REGION_1,
    _ICON_AUDIO_DIGITAL_REGION_2,
    _ICON_AUDIO_DIGITAL_REGION_3,
    _ICON_AUDIO_DIGITAL_REGION_4,
    _ICON_AS_RATIO_FULL,
    _ICON_AS_RATIO_16_9,
    _ICON_AS_RATIO_4_3,
    _ICON_AS_RATIO_5_4,
    _ICON_AS_RATIO_ORIGINAL,

    _ICON_ULTRA_VIVID_H,
    _ICON_ULTRA_VIVID_M,
    _ICON_ULTRA_VIVID_L,

    _ICON_GAMMA_1_8,
    _ICON_GAMMA_2_0,
    _ICON_GAMMA_2_2,
    _ICON_GAMMA_2_4,

    _ICON_TEMP_9300,
    _ICON_TEMP_7500,
    _ICON_TEMP_6500,
    _ICON_TEMP_5800,
    _ICON_TEMP_SRGB,
    _ICON_TEMP_USER,

    _ICON_COLOR_EFF_STD,
    _ICON_COLOR_EFF_GAME,
    _ICON_COLOR_EFF_MOVIE,
    _ICON_COLOR_EFF_PHOTO,
    _ICON_COLOR_EFF_VIVID,
    _ICON_COLOR_EFF_USER,

    _ICON_COLOR_DEMO_TYPE1,
    _ICON_COLOR_DEMO_TYPE2,
    _ICON_COLOR_DEMO_TYPE3,
    _ICON_COLOR_DEMO_TYPE4,
    _ICON_COLOR_DEMO_TYPE5,

    _ICON_COLOR_FORMAT_RGB,
    _ICON_COLOR_FORMAT_YUV,

    _ICON_TEMP_USER_R,
    _ICON_TEMP_USER_G,
    _ICON_TEMP_USER_B,

    _ICON_COLOR_PCM_SRGB,
    _ICON_COLOR_PCM_ADOBE_RGB,
    _ICON_COLOR_PCM_USER,
    _ICON_COLOR_PCM_NACTIVE,
    _ICON_COLOR_PCM_SOFT_PROFT,

    _ICON_COLOR_EFF_USER_Y,
    _ICON_COLOR_EFF_USER_C,
    _ICON_COLOR_EFF_USER_M,
    _ICON_COLOR_EFF_USER_HUE,
    _ICON_COLOR_EFF_USER_SAT,

    _ICON_NO_SUPPORT,
    _ICON_NO_SUPPORT_TEXT_0,
    _ICON_NO_SUPPORT_TEXT_1,

    _ICON_NO_CABLE,
    _ICON_NO_CABLE_TEXT_0,
    _ICON_NO_CABLE_TEXT_1,



 
            _ICON_ENGLISH,
            _ICON_CHINESE,
            _ICON_CHINESE_S,//∑±ÃÂ
            _ICON_JAPANESE,//»’”Ô
            _ICON_RUSSIAN,//∂Ì”Ô
            _ICON_KOREAN,//∫´”Ô
     
      //ºÚÃÂ
         _ICON_NO_SIGNAL_TEXT_CHS_0,
          _ICON_NO_SIGNAL_TEXT_CHS_1,
          
          _ICON_NO_SUPPORT_TEXT_CHS_0,
          _ICON_NO_SUPPORT_TEXT_CHS_1,
      
          _ICON_NO_CABLE_TEXT_CHS_0,
          _ICON_NO_CABLE_TEXT_CHS_1,
          
          _ICON_POWER_SAVING_TEXT_CHS_0,
          _ICON_POWER_SAVING_TEXT_CHS_1,
          _ICON_POWER_SAVING_TEXT_CHS_2,
      
      
          //∑±ÃÂ
              _ICON_NO_SIGNAL_TEXT_CHT_0,
              _ICON_NO_SIGNAL_TEXT_CHT_1,
              
              _ICON_NO_SUPPORT_TEXT_CHT_0,
              _ICON_NO_SUPPORT_TEXT_CHT_1,
          
              _ICON_NO_CABLE_TEXT_CHT_0,
              _ICON_NO_CABLE_TEXT_CHT_1,
              
              _ICON_POWER_SAVING_TEXT_CHT_0,
              _ICON_POWER_SAVING_TEXT_CHT_1,
              _ICON_POWER_SAVING_TEXT_CHT_2,
          
            //»’”Ô
              
              _ICON_NO_SIGNAL_TEXT_JAP_0,
               _ICON_NO_SIGNAL_TEXT_JAP_1,
               
               _ICON_NO_SUPPORT_TEXT_JAP_0,
               _ICON_NO_SUPPORT_TEXT_JAP_1,
              
               _ICON_NO_CABLE_TEXT_JAP_0,
               _ICON_NO_CABLE_TEXT_JAP_1,
               
               _ICON_POWER_SAVING_TEXT_JAP_0,
               _ICON_POWER_SAVING_TEXT_JAP_1,
               _ICON_POWER_SAVING_TEXT_JAP_2,
          
              //∂Ì”Ô
                
                _ICON_NO_SIGNAL_TEXT_RUS_0,
                 _ICON_NO_SIGNAL_TEXT_RUS_1,
                 
                 _ICON_NO_SUPPORT_TEXT_RUS_0,
                 _ICON_NO_SUPPORT_TEXT_RUS_1,
                
                 _ICON_NO_CABLE_TEXT_RUS_0,
                 _ICON_NO_CABLE_TEXT_RUS_1,
                 
                 _ICON_POWER_SAVING_TEXT_RUS_0,
                 _ICON_POWER_SAVING_TEXT_RUS_1,
                 _ICON_POWER_SAVING_TEXT_RUS_2,
          
          
                  //∫´”Ô
                
                _ICON_NO_SIGNAL_TEXT_KOR_0,
                 _ICON_NO_SIGNAL_TEXT_KOR_1,
                 
                 _ICON_NO_SUPPORT_TEXT_KOR_0,
                 _ICON_NO_SUPPORT_TEXT_KOR_1,
                
                 _ICON_NO_CABLE_TEXT_KOR_0,
                 _ICON_NO_CABLE_TEXT_KOR_1,
                 
                _ICON_POWER_SAVING_TEXT_KOR_0,
                 _ICON_POWER_SAVING_TEXT_KOR_1,
                 _ICON_POWER_SAVING_TEXT_KOR_2,

    _ICON_NO_SIGNAL,
    _ICON_NO_SIGNAL_TEXT_0,
    _ICON_NO_SIGNAL_TEXT_1,

    _ICON_POWER_SAVING,
    _ICON_POWER_SAVING_TEXT_0,
    _ICON_POWER_SAVING_TEXT_1,
    _ICON_POWER_SAVING_TEXT_2,

    _ICON_AUTO_ADJUST_TEXT_0,
    _ICON_AUTO_ADJUST_TEXT_1,
    _ICON_AUTO_ADJUST_TEXT_2,

    _ICON_AUTO_COLOR_TEXT_0,
    _ICON_AUTO_COLOR_TEXT_1,
    _ICON_AUTO_COLOR_TEXT_2,

    _ICON_MODE1,
    _ICON_MODE2,

    _ICON_0_DEGREE,
    _ICON_90_DEGREE,
    _ICON_180_DEGREE,
    _ICON_270_DEGREE,
    _ICON_HOR_MIRROR,
    _ICON_VER_MIRROR,


    _ICON_DP_1080P,
    _ICON_DP_2560_1440,
    _ICON_DP_4K2K_30HZ,
    _ICON_DP_4K2K_60HZ,

    _ICON_TRUN_OFF_PANEL_UNI_TEXT0,
    _ICON_TRUN_OFF_PANEL_UNI_TEXT1,

    _ICON_YES,
    _ICON_NO,

    _ICON_ONOFF,
    _ICON_OD_GAIN,

    _ICON_D0,
    _ICON_D1,
    _ICON_D6,
    _ICON_1_DOT_1,
    _ICON_1_DOT_2,
    _ICON_1_DOT_3,

    _ICON_COLOR_R,
    _ICON_COLOR_G,
    _ICON_COLOR_B,
    _ICON_COLOR_W,

    _ICON_PIP_POSITION_LT,
    _ICON_PIP_POSITION_RT,
    _ICON_PIP_POSITION_LB,
    _ICON_PIP_POSITION_RB,
    _ICON_PIP_POSITION_MIDDLE,
    _ICON_PIP_POSITION_USER,

    _ICON_FREEZE_DISABLE_TEXT_0,
    _ICON_FREEZE_DISABLE_TEXT_1,
    _ICON_FREEZE_DISABLE_TEXT_2,
    _ICON_DP_5K3K_60HZ,
    _ICON_DP_4K2K_144HZ,
    _ICON_2_LANE,
    _ICON_4_LANE,

#if(_ULTRA_HDR_SUPPORT == _ON)
    _ICON_HDR_MODE, // _ULTRA_HDR_SUPPORT
    _ICON_DARK_ENHANCE, // _ULTRA_HDR_SUPPORT
    _ICON_HDR_MODE_SMPTE_ST_2084, // _ULTRA_HDR_SUPPORT
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
    _ICON_FASLE_COLOR_DISABLE_TEXT_0,
    _ICON_FASLE_COLOR_DISABLE_TEXT_1,
    _ICON_FASLE_COLOR_DISABLE_TEXT_2,
#endif

#if(_DP_MST_SUPPORT == _ON)
    _ICON_MST_WARNING_MSG_0,
    _ICON_MST_WARNING_MSG_1,
    _ICON_MST_WARNING_MSG_2,
#endif
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
    _ICON_EDID_HDMI_1_4,
    _ICON_EDID_HDMI_2_0,
    _ICON_EDID_HDMI_2_0_HDR,
#endif
    _ICON_INFORMATION_HINT,


        



    _OPTION_ICON_END,
}EnumIconIndex;


typedef enum
{
    // aligh Port order
    _ICON_INPUT_NO_PORT = _OPTION_ICON_END,
    _ICON_INPUT_VGA,
    _ICON_INPUT_DVI,
    _ICON_INPUT_HDMI,
    _ICON_INPUT_DP,
    _ICON_INPUT_MHL,
    _ICON_INPUT_HDMI20,
    _ICON_INPUT_DUAL_DVI,
    _ICON_INPUT_END,

}EnumIconInputSource;
//#define _PORT_NONE                              0x00
//#define _PORT_VGA                               0x01
//#define _PORT_DVI                               0x02
//#define _PORT_HDMI                              0x03
//#define _PORT_DP                                0x04
//#define _PORT_MHL                               0x05
//#define _PORT_HDMI20                            0x06
//#define _PORT_DUAL_DVI                          0x07

typedef enum
{
    _ICON_A0_PORT = _ICON_INPUT_END,
    _ICON_D0_PORT,
    _ICON_D1_PORT,
    _ICON_D2_PORT,
    _ICON_D3_PORT,
    _ICON_D4_PORT,
    _ICON_D5_PORT,
    _ICON_D6_PORT,
    _ICON_D7_PORT,

    _ICON_PORT_END,
}EnumIconPort;




typedef enum
{
    _OPTION_NORMAL,
    _OPTION_OVERSCAN_ONOFF,
    _OPTION_OVERDRIVE_ONOFF,
    _OPTION_DDCCI_ONOFF,
    _OPTION_DCR_ONOFF,
    _OPTION_ROTATE_ADJUST,
     _OPTION_USBPOWER_ONOFF,
    _OPTION_MUTE_ONOFF,
    _OPTION_STAND_ALONG_ONOFF,
    _OPTION_PANEL_UNIFORMITY_ONOFF,
    _OPTION_AUDIO_SOURCE,

    _OPTION_ASPECT_RATIO_TYPE,
    _OPTION_ULTRA_VIVID_TYPE,
    _OPTION_GAMMA_TYPE,
    _OPTION_TEMPRATURE_TYPE,
    _OPTION_COLOR_EFFECT_TYPE,
    _OPTION_COLOR_DEMO_TYPE,
    _OPTION_COLOR_FORMAT_TYPE,
    _OPTION_COLOR_PCM_TYPE,
    _OPTION_COLOR_PCM_SOFT_PROFT_TYPE,
    _OPTION_TEMPRATURE_USER_ADJUST,
    _OPTION_COLOR_EFFC_USER_ADJUST,
    _OPTION_COLOR_EFFC_USER_RGBYCM,
    _OPTION_COLOR_RGBYCM_HUE_STA,

    _OPTION_INPUT_SOURCE_TYPE,
    _OPTION_INPUT_MF_SOURCE_TYPE,
    _OPTION_DP_PORT_VERSION,
    _OPTION_DP_MST_TYPE,
    _OPTION_DISP_ROTATE_TYPE,
    _OPTION_LATENCY_TYPE,
    _OPTION_FREEZE_ONOFF_TYPE,
    _OPTION_DP_EDID_TYPE,
    _OPTION_FREESYNC_ONOFF_TYPE,
    _OPTION_CLONE_TYPE,

    _OPTION_DISPLATMODE_TYPE,
    _OPTION_SELECTREGION_TYPE,
    _OPTION_BORDER_COLOR,
    _OPTION_PIP_POSITION,
    _OPTION_DUAL_DP_EDID_TYPE,
    _OPTION_DP_LANE_COUNT_SELECT,

    _OPTION_HDR_MODE_SELECT, // _ULTRA_HDR_SUPPORT
    _OPTION_DARK_ENHANCE_ON_OFF, // _ULTRA_HDR_SUPPORT

#if (_FALSE_COLOR_SUPPORT == _ON)
    _OPTION_FALSE_COLOR_TYPE,
#endif

    _OPTION_LANGUAGE_TYPE,


}EnumOptiontype;


typedef enum
{
    _FONT1_GLOBAL,
    _REALTEK_1BIT_LOGO0,
    _REALTEK_1BIT_LOGO1,
}EnumFontSel;


typedef enum
{
    _PALETTE_RTD_LOGO,
    _PALETTE_MAIN_MENU,
#if (_FALSE_COLOR_SUPPORT == _ON)
    _PALETTE_FALSE_COLOR_MENU,
#endif
}EnumPaletteindex;

typedef enum
{
    _ENGLISH = 0,
   // _FRENCH,
   // _GERMAN,
  //  _SPANISH,
    _CHINESE_T,
    _CHINESE_S,
    _JAPAN,
   _RUSSIAN,//∂Ì”Ô
   _KOREA,//∫´”Ô

    _LANGUAGE_AMOUNT,
}EnumOSDLanguageDef;

typedef enum
{
    _OSDEVENT_NONE_MSG = 0,
    _OSDEVENT_SHOW_NOSIGNAL_MSG,
    _OSDEVENT_SHOW_NOCABLE_MSG,
    _OSDEVENT_SHOW_NOSUPPORT_MSG,
    _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG,
    _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG,
    _OSDEVENT_SHOW_DISPLAY_MODE_MENU_MSG,
    _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG,
    _OSDEVENT_WAKE_UP_DP_OPTION_MSG,
    _OSDEVENT_DO_AUTO_CONFIG_MSG,
    _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG,
    _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG,
    _OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_INPUTSOURCEDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG,
    _OSDEVENT_SHOW_MP_NOSIGNAL_NOCABLE_MSG,
#if(_DP_SUPPORT == _ON)
    _OSDEVENT_SHOW_DP_VERSION_MSG,
#endif
    _OSDEVENT_SHOW_BURNIN_MSG,// alant debug
  _OSDEVENT_SHOW_MAINMENU_MSG,// alant debug
}EnumOSDEvenMassage;

typedef enum
{
    _OSD_DISP_NOSIGNAL_MSG,
    _OSD_DISP_NOCABLE_MSG,
    _OSD_DISP_NOSUPPORT_MSG,
    _OSD_DISP_FAIL_SAFE_MODE_MSG,
    _OSD_DISP_AUTO_CONFIG_MSG,
    _OSD_DISP_INPUT_SIGNAL_MSG,
    _OSD_DISP_AUTO_COLOR_MSG,
    _OSD_DISP_SWITCH_DDCCI_PORT_MSG,
    _OSD_DISP_POWER_SAVING_MSG,
    _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG,
#if(_FREEZE_SUPPORT == _ON)
    _OSD_DISP_DISABLE_FREEZE_MSG,
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
    _OSD_DISP_DISABLE_FALSE_COLOR_MSG,
#endif
#if(_DP_MST_SUPPORT == _ON)
    _OSD_DISP_MST_WARNING_MSG,
#endif
    _OSD_DISP_BURNIN_MSG,// alant debug

} EnumOSDDispMsg;

typedef enum
{
    _ICON_POS_UP_0,
    _ICON_POS_UP_1,
    _ICON_POS_UP_2,
    _ICON_POS_UP_3,
    _ICON_POS_DOWN_0,
    _ICON_POS_DOWN_1,
    _ICON_POS_DOWN_2,
    _ICON_POS_DOWN_3,
} EnumOSDMainMenuIcon;

typedef enum
{
    _POS_NOTICE_NO_SUPPORT_ICON,
    _POS_NOTICE_NO_SUPPORT_TEXT_0,
    _POS_NOTICE_NO_SUPPORT_TEXT_1,

    _POS_NOTICE_NO_CABLE_ICON,
    _POS_NOTICE_NO_CABLE_TEXT_0,
    _POS_NOTICE_NO_CABLE_TEXT_1,

    _POS_NOTICE_NO_SIGNAL_ICON,
    _POS_NOTICE_NO_SIGNAL_TEXT_0,
    _POS_NOTICE_NO_SIGNAL_TEXT_1,
}EnumOSDNoticeIcon;

typedef enum
{
 //   _STRING_DISPLAYMODE,
    _STRING_DISPLAYFUNCTION,
//    _STRING_SELECTREGION,
    _STRING_PICTURE,
 //   _STRING_ANALOG,
    _STRING_COLOR,
    _STRING_ADVANCE,
    _STRING_INPUT,
  //  _STRING_AUDIO,
    _STRING_OTHER,
    _STRING_INFORMATION,
      _STRING_AUDIO,
        _STRING_ANALOG,
      _STRING_DISPLAYMODE,
          _STRING_SELECTREGION,
    _STRING_FACTORY,

    // display mode
    _STRING_1P,
    _STRING_2P_LR,
    _STRING_2P_TB,
    _STRING_2P_PIP,
    _STRING_4P,

    // display function
    _STRING_DISP_ROTATE,
    _STRING_DISP_LATENCY,
    _STRING_DISP_LR_RATIO,
    _STRING_PIP_POSITION,
    _STRING_PIP_USER_POSITION_H,
    _STRING_PIP_USER_POSITION_V,
    _STRING_PIP_TRANSPARENCY,
    _STRING_PIP_SIZE,
    _STRING_INPUT_SWAP,

    // select region
    _STRING_2P_LR_L,
    _STRING_2P_LR_R,
    _STRING_2P_LR_FULL,
    _STRING_2P_TB_T,
    _STRING_2P_TB_B,
    _STRING_2P_TB_FULL,
    _STRING_2P_PIP_MAIN,
    _STRING_2P_PIP_SUB,
    _STRING_2P_PIP_FULL,
    _STRING_4P_LT_IN,
    _STRING_4P_LT_OUT,
    _STRING_4P_RT_IN,
    _STRING_4P_RT_OUT,
    _STRING_4P_LB_IN,
    _STRING_4P_LB_OUT,
    _STRING_4P_RB_IN,
    _STRING_4P_RB_OUT,
    _STRING_4P_FULL,

    // picture
    _STRING_BACKLIGHT,
    _STRING_BRIGHTNESS,
    _STRING_CONTRAST,
    _STRING_SHARPNESS,

    // analog
    _STRING_AUTO_ADJUST,
    _STRING_HPOS,
    _STRING_VPOS,
    _STRING_CLOCK,
    _STRING_PHASE,

    // color
 //   _STRING_PANEL_UNIFORMITY,
    _STRING_GAMMA,
    _STRING_COLOR_TEMP,
    _STRING_COLOR_EFFECT,
 //   _STRING_DEMO,
 //   _STRING_COLOR_FORMAT,
 //   _STRING_PCM,
    _STRING_HUE,
    _STRING_SATURATION,
     _STRING_COLOR_FORMAT,
      _STRING_DEMO,
   _STRING_PANEL_UNIFORMITY,
   _STRING_PCM,
    // advance
    _STRING_ASPECT_RATIO,
        _STRING_DDCCI,
    _STRING_OVER_SCAN,
    _STRING_OVER_DRIVE,

 //   _STRING_DDCCI,
    _STRING_ULTRA_VIVID,
    _STRING_DCR,
    _STRING_DP_OPTION,
    _STRING_DP_MST,
    _STRING_DP_EDID,
    _STRING_CLONE,
    _STRING_FREESYNC,
    _STRING_FREEZE,
    _STRING_DP_LANE_COUNT,

#if(_ULTRA_HDR_SUPPORT == _ON)
    _STRING_HDR,
#endif

#if (_FALSE_COLOR_SUPPORT == _ON)
    _STRING_FALSE_COLOR,
#endif
    _STRING_SINGLE_DP_EDID,
    _STRING_DUAL_DP_EDID,
    // input
    _STRING_AUTO_SELECT,

    // audio
    _STRING_AUDIO_SOURCE,
    _STRING_VOLUME,
    _STRING_MUTE,
    _STRING_STAND_ALONG,
//    _STRING_AUDIO_SOURCE,
    _STRING_SOUND_MODE,

    // other
    _STRING_RESET,
    _STRING_MENU_TIME,
    _STRING_OSD_HPOS,
    _STRING_OSD_VPOS,
    _STRING_LANGUAGE,
    _STRING_TRANSPARENCY,
    _STRING_ROTATE,
    _STRING_BORDER_WIDTH,
    _STRING_BORDER_COLOR,

    // Show OSD Number
    _STRING_SHOW_NUMBER,

    // information
    _STRING_HFREQPCLK,
    _STRING_VFREQUENCY,
    _STRING_VGA_USER_MODE,
    _STRING_VGA_PRESET_MODE,
    _STRING_HDCP_MODE,

    // Input Source
    _STRING_InputSource_1P,
    _STRING_InputSource_2P,
    _STRING_InputSource_3P,
    _STRING_InputSource_4P,

    // Adjust message
    _STRING_PLEASE_WAIT,
    _STRING_NO_SIGNAL,
    _STRING_NO_CABLE,
    _STRING_NO_SUPPORT,
    _STRING_AUTO_COLOR,
    _STRING_GO_TO_POWER_SAVING_MODE,
    _STRING_NOW_RESOLUTION,

    _STRING_PASS,
    _STRING_FAIL,

    _STRING_2P,
    _STRING_3P,
#if(_ULTRA_HDR_SUPPORT == _ON)
    _STRING_HDR_MODE, // _ULTRA_HDR_SUPPORT
    _STRING_HDR_DARK_ENHANCE, // _ULTRA_HDR_SUPPORT
#endif
#if (_FALSE_COLOR_SUPPORT == _ON)
    _STRING_FALSE_COLOR_CURSOR_1,
    _STRING_FALSE_COLOR_CURSOR_2,
#endif
  
    _STRIN_END,
}EnumStringIndex;

typedef enum
{
    // input
    _STRING_A0_PORT = _STRIN_END,
    _STRING_D0_PORT,
    _STRING_D1_PORT,
    _STRING_D2_PORT,
    _STRING_D3_PORT,
    _STRING_D4_PORT,
    _STRING_D5_PORT,
    _STRING_D6_PORT,
    _STRING_D7_PORT,
    _STRING_AUTOSELECT_PORT,
    _STRING_FREESYNC_SUPPORT_V_RANGE,
}EnumStringPort;

typedef enum
{
    _OSD_ROTATE_DISPLAY_FULL = 0,
    _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL,
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,
}EnumOsdRotationDisplaySizeDef;

typedef enum
{
    _AUTO_CONFIG_DO = 0,
    _AUTO_CONFIG_RESULT,
}EnumAutoConfig;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// __RTD_DDCCI__
extern bit g_bForcePowSavStatus;

// __RTD_OSD__
extern StructOsdInfo g_stOsdInfo;
extern WORD g_usAdjustValue;
extern WORD g_usBackupValue;
extern WORD g_usItemNum;
extern BYTE g_ucLogoTimerCounter;

// __RTD_OSDFUNC__
extern WORD g_usFontSelectStart;
extern WORD g_usFontTableStart;
extern BYTE g_ucOsdWidth;
extern BYTE g_ucOsdHeight;
extern BYTE g_ucOsdWidthB;
extern BYTE g_ucOsdHeightB;
extern BYTE g_ucFontPointer0;
extern BYTE g_ucFontPointer1;
extern BYTE g_ucFontPointer2;

extern BYTE g_stFacFlag;
//----------------------------------------------------------------------------------------
// Extern Tables from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];

//----------------------------------------------------------------------------------------
// Extern Tables from OsdTable.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTTABLE__
extern BYTE code tOSD_iREALTEK[];
extern BYTE code tOSD_iKEY_BACK[];
extern BYTE code tOSD_iKEY_LEFT[];
extern BYTE code tOSD_iKEY_RIGHT[];
extern BYTE code tOSD_iKEY_ENTER[];
extern BYTE code tOSD_iKEY_EXIT[];

extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];

// __RTD_OSDFONTPROP__
// main menu
extern BYTE code tSTRING_DISPLAYMODE[];
extern BYTE code tSTRING_SELECTREGION[];
extern BYTE code tSTRING_PICTURE[];
extern BYTE code tSTRING_ANALOG[];
extern BYTE code tSTRING_COLOR[];
extern BYTE code tSTRING_ADVANCE[];
extern BYTE code tSTRING_INPUT[];
extern BYTE code tSTRING_AUDIO[];
extern BYTE code tSTRING_OTHER[];
extern BYTE code tSTRING_INFORMATION[];
extern BYTE code tSTRING_FACTORY[];

// display mode
extern BYTE code tSTRING_1P[];
extern BYTE code tSTRING_2P_LR[];
extern BYTE code tSTRING_2P_TB[];
extern BYTE code tSTRING_2P_PIP[];
extern BYTE code tSTRING_4P[];

// display function
extern BYTE code tSTRING_DISP_ROTATE[];
extern BYTE code tSTRING_DISP_LR_RATIO[];
extern BYTE code tSTRING_LATENCY[];

// select region
extern BYTE code tSTRING_2P_LR_L[];
extern BYTE code tSTRING_2P_LR_R[];
extern BYTE code tSTRING_2P_TB_T[];
extern BYTE code tSTRING_2P_TB_B[];
extern BYTE code tSTRING_2P_PIP_MAIN[];
extern BYTE code tSTRING_2P_PIP_SUB[];
extern BYTE code tSTRING_4P_LT_IN[];
extern BYTE code tSTRING_4P_LT_OUT[];
extern BYTE code tSTRING_4P_RT_IN[];
extern BYTE code tSTRING_4P_RT_OUT[];
extern BYTE code tSTRING_4P_LB_IN[];
extern BYTE code tSTRING_4P_LB_OUT[];
extern BYTE code tSTRING_4P_RB_IN[];
extern BYTE code tSTRING_4P_RB_OUT[];
extern BYTE code tSTRING_4P_FULL[];

// picture
extern BYTE code tSTRING_BACKLIGHT[];
extern BYTE code tSTRING_BRIGHTNESS[];
extern BYTE code tSTRING_CONTRAST[];
extern BYTE code tSTRING_SHARPNESS[];

// display
extern BYTE code tSTRING_AUTO_ADJUST[];
extern BYTE code tSTRING_HPOS[];
extern BYTE code tSTRING_VPOS[];
extern BYTE code tSTRING_CLOCK[];
extern BYTE code tSTRING_PHASE[];

// color
extern BYTE code tSTRING_PANEL_UNIFORMITY[];
extern BYTE code tSTRING_GAMMA[];
extern BYTE code tSTRING_COLOR_TEMP[];
extern BYTE code tSTRING_COLOR_EFFECT[];
extern BYTE code tSTRING_DEMO[];
extern BYTE code tSTRING_COLOR_FORMAT[];
extern BYTE code tSTRING_PCM[];
extern BYTE code tSTRING_HUE[];
extern BYTE code tSTRING_SATURATION[];

// advance
extern BYTE code tSTRING_ASPECT_RATIO[];
extern BYTE code tSTRING_OVER_SCAN[];
extern BYTE code tSTRING_OVER_DRIVE[];
extern BYTE code tSTRING_ENERGY_STAR[];
extern BYTE code tSTRING_DDCCI[];
extern BYTE code tSTRING_ULTRA_VIVID[];
extern BYTE code tSTRING_DCR[];
extern BYTE code tSTRING_DP_OPTION[];
extern BYTE code tSTRING_DP_MST[];
extern BYTE code tSTRING_DP_EDID[];
extern BYTE code tSTRING_CLONE[];
extern BYTE code tSTRING_FREESYNC[];

// input
extern BYTE code tSTRING_AUTO_SELECT[];

// audio
extern BYTE code tSTRING_VOLUME[];
extern BYTE code tSTRING_MUTE[];
extern BYTE code tSTRING_STAND_ALONG[];
extern BYTE code tSTRING_AUDIO_SOURCE[];
extern BYTE code tSTRING_SOUND_MODE[];

// other
extern BYTE code tSTRING_RESET[];
extern BYTE code tSTRING_MENU_TIME[];
extern BYTE code tSTRING_OSD_HPOS[];
extern BYTE code tSTRING_OSD_VPOS[];
extern BYTE code tSTRING_LANGUAGE[];
extern BYTE code tSTRING_TRANSPARENCY[];
extern BYTE code tSTRING_ROTATE[];
extern BYTE code tSTRING_BORDER_WIDTH[];
extern BYTE code tSTRING_BORDER_COLOR[];
extern BYTE code tSTRING_PIP_POSITION[];
extern BYTE code tSTRING_PIP_TRANSPARENCY[];
extern BYTE code tSTRING_PIP_SIZE[];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserDdcci.c
//----------------------------------------------------------------------------------------
// __RTD_DDCCI__
extern void UserDdcciHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from RTDKey.c
//----------------------------------------------------------------------------------------
// __RTD_KEY__
extern void RTDKeyInitial(void);


//----------------------------------------------------------------------------------------
// Extern functions from Osd.c
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Extern functions from OsdFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFUNC__
extern void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
extern void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB);
#endif

extern void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void OsdFuncTransparency(BYTE ucTrans);
extern void OsdFuncBlending(BYTE ucType);
//extern BYTE OsdFuncGetOsdFontPointer(BYTE ucPointerSelect);
extern BYTE OsdFuncSetOsdFontPointer(BYTE ucPointerSelect, BYTE ucPointer);
extern void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
extern void OsdFuncDisableOsd(void);
extern void OsdFuncEnableOsd(void);
extern void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
extern void OsdFuncSet2BitIconOffset(BYTE ucOffset);
extern void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);

#if(_SIX_COLOR_SUPPORT == _ON)
extern void OsdFuncSixColorAdjust(void);
#endif

extern void OsdFuncColorFormatAdjust(EnumDisplayRegion enumRegion);
extern void OsdFuncColorPcmAdjust(void);
extern void OsdFuncSetOsdItemFlag(void);
extern BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum, BYTE ucRegion);
#if(_FREEZE_SUPPORT == _ON)
extern bit OsdFuncCheckFreezeDisableMsg(void);
extern bit OsdFuncCheckFreezeDisable(void);
extern void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
extern bit OsdFuncCheckFalseColorDisableMsg(void);
extern bit OsdFuncCheckFalseColorDisable(void);
extern void OsdFuncShowOSDAfterClosedFalseColorMsg(void);
extern void OsdBlankFont(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType);
#endif
extern void OsdFuncShowSourceMenuCheck(void);

//----------------------------------------------------------------------------------------
// Extern functions from OsdDisplay.c
//----------------------------------------------------------------------------------------
// __RTD_OSDDISPLAY__

//extern WORD OsdDispDetOverRange(WORD ucValue, WORD ucMax, WORD ucMin, bit bCycle);
extern BYTE OsdDispJudgeSourceType(void);

extern void OsdDispDisableOsd(void);
extern void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);

extern void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState);
extern void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
extern void OsdDispClearSelectColor(BYTE ucUpDown);
extern void OsdDispMainSubString(BYTE ucState);
extern void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor);
extern void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);

extern void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState);

extern void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState);
extern void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption);
extern void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState);
extern void OsdDispClearArrow(BYTE ucUpDown);
extern void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious);
extern void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary);
extern void OsdDispMainMenu(void);

extern void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
extern WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
extern void OsdDispOsdReset(void);
extern void OsdDispClearSliderAndNumber(void);
extern void OsdDispHotKeyOptionMenu(BYTE ucOption);
extern void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption);
extern void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
extern void OsdDispHotKeySourceMenu(void);
extern void OsdDispHotKeyDisplayModeMenu(void);
extern void OsdDispHotKeyDisplayModeMenuSwitch(BYTE ucMode);
extern void OsdDispHotKeyDisplayModeMenuIcon(BYTE ucMode);

extern void OsdDispHotKeySourceMenuSwitch(BYTE ucPort);

extern void OsdDispPanelUniformityMsgSwitch(void);
extern void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);
#if(_VGA_SUPPORT == _ON)
extern void OsdDispAutoConfigProc(void);
extern void OsdDisplayAutoBalanceProc(void);
#endif

extern void OsdDispShowLogo(void);
extern void OsdDispShowInformation(void);
extern void OsdDisplaySixColorGetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
extern void OsdDisplaySixColorSetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
extern void OsdDispOsdRotateSwitch(void);
#endif

extern void OsdDispMpUpdateDisplayStateNotice(bit bOn, EnumDisplayRegion enumSelRegion);

#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
extern BYTE OsdDispMpDisplayStateGetNoticeType(EnumDisplayRegion enumSelRegion, bit bOn);
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_2P_LR(BYTE ucNoticeL, BYTE ucNoticeR);
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_2P_TB(BYTE ucNoticeT, BYTE ucNoticeB);
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_2P_PIP(BYTE ucNoticeMain, BYTE ucNoticeSub);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_4P(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P, BYTE ucNotice4P);
#endif
#if (_FALSE_COLOR_SUPPORT == _ON)
extern void OsdDispFalseColorMenu(void);
#endif


//----------------------------------------------------------------------------------------
// Extern functions from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern void OsdFontVLCLoadFont(BYTE ucState);

// __RTD_OSDFONTDYNAMICICON_1__
extern void OsdFontVLCDynamicLoadIcon(BYTE ucIconPos, WORD usIcon);

// __RTD_OSDFONTDYNAMICICON_2__
extern void OsdFontVLCLoadMainIcon_2(BYTE ucIconPos, WORD usIcon);
#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
extern void OsdFontLoadNoticeIcon(BYTE ucIconPos, WORD usIcon);
#endif

// __RTD_OSDFONTTABLE__
extern void OsdFontPut1Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor);
extern void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor);
extern void OsdFontPut1BitMainMenuIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
extern void OsdFontPut1BitMainMenuIconOsdB(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
#endif

//extern void OsdFontPut2Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
//extern void OsdFontPut2BitTable(BYTE ucRow, BYTE ucCol, BYTE *pArray, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);

// __RTD_OSDFONTPROP__
extern void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);

// __RTD_OSDPALETTE__
extern void OsdPaletteSelectPalette(BYTE ucValue);

// __RTD_OSDWINDOW__
extern void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
extern void OsdWindowSliderDisable(void);
#if (_FALSE_COLOR_SUPPORT == _ON)
extern void OsdWindowDrawingByFontBorder(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from OsdTableFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDTABLEFUNC__
extern void OsdTableFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint);
extern BYTE OsdTableFuncVideoResolution(void);
extern void OsdTableFuncPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, BYTE ucLanguage);
extern void OsdTableFuncPutStringCenter(BYTE ucRow, BYTE ucColStart, BYTE ucColEnd, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, SBYTE chCenterOffset, BYTE ucLanguage);
extern void OsdTableFuncDrawWindow(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdTableFuncPutIcon1BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdTableFuncPutIcon2BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)


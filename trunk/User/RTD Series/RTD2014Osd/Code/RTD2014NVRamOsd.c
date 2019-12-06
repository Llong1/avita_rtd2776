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
// ID Code      : RTD2014NVRamOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_NVRAM_OSD__

#include "UserCommonInclude.h"
#include <stdio.h>
#if(_OSD_TYPE == _REALTEK_2014_OSD)

//--------------------------------------------------
// Version Code of NVRam
//--------------------------------------------------
#define _CHECKSUM                                   0xEE
#define _VERSION_CODE                            0xAA//debug

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#define _BRIGHTNESS_REGION                          0x200
#define _CONTRAST_REGION                            0x800

//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                            50
#define _SIX_COLOR_SATURATION_R                     100

#define _SIX_COLOR_HUE_Y                            50
#define _SIX_COLOR_SATURATION_Y                     100

#define _SIX_COLOR_HUE_G                            50
#define _SIX_COLOR_SATURATION_G                     100

#define _SIX_COLOR_HUE_C                            50
#define _SIX_COLOR_SATURATION_C                     100

#define _SIX_COLOR_HUE_B                            50
#define _SIX_COLOR_SATURATION_B                     100

#define _SIX_COLOR_HUE_M                            50
#define _SIX_COLOR_SATURATION_M                     100

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PageInfo Address
//--------------------------------------------------
#define _FLASH_FW_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 16)
#define _FLASH_FW_VERSIONCODE_ADDR                  (_FLASH_PAGE_SIZE - 15)
#define _PAGEINFO_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 5)
#define _PAGEINFO_PAGEID_ADDR                       (_FLASH_PAGE_SIZE - 4)
#define _PAGEINFO_MOVECOUNT_ADDR                    (_FLASH_PAGE_SIZE - 3)

// This value is used to indicate the EEPROM emulaiton FW version
#define _EEPROM_EMULATION_VERSION                   0x01
#endif

// Attention: it is necessary for sizeof(StructOsdUserDataType) < ((_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START) * (_DATA_ITEM_LENGTH - 2))
// Please check it when add items in StructOsdUserDataType
code StructOsdUserDataType g_stOsdUserDataDefault =
{
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
// 90%
  _BACKLIGHT_DEFAULT,//  _BACKLIGHT_CENTER,/// _BACKLIGHT_MAX,//    0x0080,                   // usBackLight;
#else
    0x0800,                   // usBackLight;
#endif
    50,                       // ucOsdHPos;
    50,                       // ucOsdVPos;
  _OSD_TIMEOUT_MIN,//  (_OSD_TIMEOUT_MIN + 1),   // ucOsdTimeout;
    0,                        // ucTransparency;
    _OD_GAIN_CENTER,          // ucODGain;
    _HL_WIN_OFF,              // ucHLWinType;
    50,                       // ucVolume;
    0,                        // BYTE ucOsdInputPort0;
    0,                        // WORD usHour
    0,                        // BYTE ucMin
    _OSD_DM_1P,               // BYTE ucDisplayMode
    0,                        // BYTE ucSelectRegionWidth
    _SELECT_REGION_COLOR_0,   // BYTE ucSelectRegionColor
    _PIP_POSITON_RB,                          // BYTE ucPipSubPosType
    _OSD_PIP_USER_POSITION_H_MAX,          // WORD usPipSubHPos
    _OSD_PIP_USER_POSITION_V_MAX,          // WORD usPipSubVPos
    _OSD_PIP_SIZE_MAX,                        // BYTE ucPipSubScaling
    _OSD_PIP_TRANSPARENCY_MIN,                // BYTE ucPipSubBlending
    _OSD_PBP_LR_RATIO_MIN,                 // BYTE ucPbpLrRatio
    _OSD_CLONE_MTP_OFF,           // BYTE ucCloneModeMtP
    _OSD_CLONE_1P_OFF,           // b1CloneMode1P
    _ENGLISH,                 // b4Language;
    _COLOR_SPACE_RGB,         // b3VGARGBYUV;
    _COLOR_SPACE_RGB,         // b3DVIRGBYUV;
    0x00,                     // b33DConvergenceMode : 3;
    _AUTO_COLOR_TYPE_EXTERNAL,// b1FactoryAutoColorType : 1;
    0,                        // BYTE b1PCMSoftProftMode : 1;
    _OFF,                     // b2OsdDpMST : 2;
    0,                        // b3OsdDispRotate : 3;
    _DP_LANE_AUTO_MODE,       // BYTE b3D0DpLaneMode : 3;
    _DP_LANE_AUTO_MODE,       // BYTE b3D1DpLaneMode : 3;
    _DP_LANE_AUTO_MODE,       // BYTE b3D6DpLaneMode : 3;
    1,                        // b1OsdDpD0PortVersion : 1;
    1,                        // b1OsdDpD1PortVersion : 1;
    1,                        // b1OsdDpD6PortVersion : 1;
    _ON,                      // b1DDCCIStatus;
    _OFF,                     // b1OsdDcrStatus;
    _OSD_ROTATE_DEGREE_0,     // b1OsdRotate;
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,     // b2DispRotationSizeType;
    _OFF,                     // b1VolumeMute : 1;
    _OFF,                     // b1AudioStandAloneStatus : 1;
    _OFF,                     // b1ODStatus : 1;
    _OFF,                     // b1FreeSyncStatus : 1;
    _LATENCY_L,               // b2LatencyStatus : 2
    _OFF,  // b1USBPower
    _OFF,  // b1BurnIn
       0,  // model type
       20, //bloffset  ///Wesley_Offset_20171221
#if (_FALSE_COLOR_SUPPORT == _ON)
    _OFF,                       // BYTE ucFalseColorStatus ;
    0,                          // BYTE ucFalseColorLevel01;
    1,                          // BYTE ucFalseColorLevel02;
    2,                          // BYTE ucFalseColorLevel03;
    3,                          // BYTE ucFalseColorLevel04;
    4,                          // BYTE ucFalseColorLevel05;
    5,                          // BYTE ucFalseColorLevel06;
    6,                          // BYTE ucFalseColorLevel07;
    7,                          // BYTE ucFalseColorLevel08;
    8,                          // BYTE ucFalseColorLevel09;
    9,                          // BYTE ucFalseColorLevel10;
    10,                         // BYTE ucFalseColorLevel11;
    11,                         // BYTE ucFalseColorLevel12;
    12,                         // BYTE ucFalseColorLevel13;
    13,                         // BYTE ucFalseColorLevel14;
    14,                         // BYTE ucFalseColorLevel15;
    15,                         // BYTE ucFalseColorLevel16;
    16,                         // BYTE ucFalseColorLevel17;
#endif
};

code StructColorProcDataType tColorTempDefaultData[] =
{
    {
        _CT9300_RED,
        _CT9300_GREEN,
        _CT9300_BLUE,
    },

    {
        _CT7500_RED,
        _CT7500_GREEN,
        _CT7500_BLUE,
    },

    {
        _CT6500_RED,
        _CT6500_GREEN,
        _CT6500_BLUE,
    },

    {
        _CT5800_RED,
        _CT5800_GREEN,
        _CT5800_BLUE,
    },

    {//12500K
        _CTSRGB_RED,
        _CTSRGB_GREEN,
        _CTSRGB_BLUE,
    },

    {
        _CTUSER_RED,
        _CTUSER_GREEN,
        _CTUSER_BLUE,
    },
};

code StructOsdInputPortDataType tOsdInputPortDataDefault[_OSD_INPUT_AMOUNT] =
{
    {   // _A0_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D0_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D1_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D2_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D3_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D4_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D5_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D6_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

    {   // _D7_INPUT_PORT
        0,                          // BYTE ucAspectOriginRatio
        2,                          // BYTE b3Sharpness : 3;
        _OSD_ASPECT_RATIO_FULL,     // BYTE b3AspectRatio : 3;
        _ON,                        // BYTE b1OverScan : 1;
#if(_ULTRA_HDR_SUPPORT == _ON)
        _OFF,                       // b1DarkEnhanceStatus : 1;
        _HDR_MODE_OFF,              // BYTE ucHdrMode;
#endif
    },

};

code StructOsdRegionDataType tOsdRegionDataDefault[_REGION_AMOUNT] =
{
    { // 1P
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
#if(_MODEL_TYPE == _YLI55161)	          
        _CT_9300,//   _CT_6500,                               // BYTE b4ColorTempType : 4;
#else
        _CT_7500,
#endif        
       _GAMMA_18,// _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        0x200,                                  // WORD usBrightness;
        0x800,                                  // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },


    { // 1P Demo Outside
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        0x200,                                  // WORD usBrightness;
        0x800,                                  // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },


    // _OSD_DM_2P_LR
    { // PBP L
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;

    },

    { // PBP R
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },

    // _OSD_DM_2P_TB
    { // PBP T
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },

    { // PBP B
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },

    // _OSD_DM_2P_PIP
    { // PIP MAIN
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },

    { // PIP SUB
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },

    // _OSD_DM_4P
    { // inside
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },

    { // outside
        _SIX_COLOR_HUE_R,                       // BYTE ucSixColorHueR;
        _SIX_COLOR_SATURATION_R,                // BYTE ucSixColorSaturationR;
        _SIX_COLOR_HUE_Y,                       // BYTE ucSixColorHueY;
        _SIX_COLOR_SATURATION_Y,                // BYTE ucSixColorSaturationY;
        _SIX_COLOR_HUE_G,                       // BYTE ucSixColorHueG;
        _SIX_COLOR_SATURATION_G,                // BYTE ucSixColorSaturationG;
        _SIX_COLOR_HUE_C,                       // BYTE ucSixColorHueC;
        _SIX_COLOR_SATURATION_C,                // BYTE ucSixColorSaturationC;
        _SIX_COLOR_HUE_B,                       // BYTE ucSixColorHueB;
        _SIX_COLOR_SATURATION_B,                // BYTE ucSixColorSaturationB;
        _SIX_COLOR_HUE_M,                       // BYTE ucSixColorHueM;
        _SIX_COLOR_SATURATION_M,                // BYTE ucSixColorSaturationM;
        _DEFAULT_HUE,                           // BYTE ucHue;
        _DEFAULT_SATURATION,                    // BYTE ucSaturation;
        _COLOREFFECT_STANDARD,                  // BYTE b4ColorEffect : 4;
        _CT_6500,                               // BYTE b4ColorTempType : 4;
        _GAMMA_OFF,                             // BYTE b3Gamma : 3;
        _PCM_OSD_NATIVE,                        // BYTE b3PCMStatus : 3;
        _OFF,                                   // BYTE b1PanelUniformity : 1;
        _ULTRA_VIVID_OFF,                       // BYTE b2UltraVividStatus : 2;
        _BRIGHTNESS_REGION,                     // WORD usBrightness;
        _CONTRAST_REGION,                       // WORD usContrast;
        0,                                        // BYTE b3PanelUniformityType :3;
    },
};


code StructOsdDisplayModeDataType tOsdDisplayModeDataDefault[_OSD_DM_AMOUNT] =
{
    { // _OSD_DM_1P
        _OSD_SR_1P_FULL,
#if(_MODEL_TYPE == _YLI55161)            
        _OSD_INPUT_AUTO,   // BYTE ucOsdInputPort0; ///Wesley Modify
#else
        _OSD_INPUT_D1,
#endif
        _OSD_INPUT_D1,                  // BYTE ucOsdInputPort1;
        _OSD_INPUT_D1,//   _OSD_INPUT_D2,                  // BYTE ucOsdInputPort2;
        _OSD_INPUT_D1,//   _OSD_INPUT_D3,                  // BYTE ucOsdInputPort3;
        _OSD_AUDIO_SOURCE_DIGITAL_REGION_1,//_OSD_AUDIO_SOURCE_ANALOG,       // BYTE ucAudioInputRegin;

    },

    { // _OSD_DM_2P_LR
        _OSD_SR_2P_LR_L,
        _OSD_INPUT_AUTO,                  // BYTE ucOsdInputPort0;
        _OSD_INPUT_D1,                  // BYTE ucOsdInputPort1;
        _OSD_INPUT_D2,                  // BYTE ucOsdInputPort2;
        _OSD_INPUT_D3,                  // BYTE ucOsdInputPort3;
        _OSD_AUDIO_SOURCE_ANALOG        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_2P_TB
        _OSD_SR_2P_TB_T,
        _OSD_INPUT_AUTO,                  // BYTE ucOsdInputPort0;
        _OSD_INPUT_D1,                  // BYTE ucOsdInputPort1;
        _OSD_INPUT_D2,                  // BYTE ucOsdInputPort2;
        _OSD_INPUT_D3,                  // BYTE ucOsdInputPort3;
        _OSD_AUDIO_SOURCE_ANALOG        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_2P_PIP
        _OSD_SR_2P_PIP_MAIN,
        _OSD_INPUT_AUTO,                  // BYTE ucOsdInputPort0;
        _OSD_INPUT_D1,                  // BYTE ucOsdInputPort1;
        _OSD_INPUT_D2,                  // BYTE ucOsdInputPort2;
        _OSD_INPUT_D3,                  // BYTE ucOsdInputPort3;
        _OSD_AUDIO_SOURCE_ANALOG        // BYTE ucAudioInputRegin;
    },

    { // _OSD_DM_4P
        _OSD_SR_4P_LT_INSIDE,
        _OSD_INPUT_AUTO,                  // BYTE ucOsdInputPort0;
        _OSD_INPUT_D1,                  // BYTE ucOsdInputPort1;
        _OSD_INPUT_D2,                  // BYTE ucOsdInputPort2;
        _OSD_INPUT_D3,                  // BYTE ucOsdInputPort3;
        _OSD_AUDIO_SOURCE_ANALOG        // BYTE ucAudioInputRegin;
    },
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

StructOsdUserDataType g_stOsdUserData;
StructColorProcDataType g_stColorProcData;
StructOsdInputPortDataType g_pstOsdInputPortData[9];
StructOsdRegionDataType g_pstOsdRegionData[2];
StructOsdDisplayModeDataType g_stOsdDisplayModeData;


#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
DWORD g_ulFlashMoveCount;
BYTE g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
void RTDEepromStartup(void);
void RTDEepromWholeRestore(void);
void RTDEepromRestoreBacklight(void);
void RTDEepromLoadOsdUserData(void);
void RTDEepromSaveOsdUserData(void);
void RTDEepromRestoreOsdUserData(void);

void RTDEepromLoadColorSetting(BYTE ucRegion);
void RTDEepromSaveColorSetting(BYTE ucColorTempType);
void RTDEepromRestoreColorSetting(void);
void RTDEepromRestoreUserColorSetting(void);

void RTDEepromLoadOsdInputSourceData(BYTE ucSource);
void RTDEepromSaveOsdInputSourceData(BYTE ucSource);
void RTDEepromRestoreOsdInputSourceData(void);

void RTDEepromLoadOsdInputPortData(BYTE ucPort);
void RTDEepromSaveOsdInputPortData(BYTE ucPort);
void RTDEepromRestoreOsdInputPortData(void);

void RTDEepromLoadOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
void RTDEepromSaveOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
void RTDEepromRestoreOsdRegionData(void);

void RTDEepromLoadOsdDisplayModeData(BYTE ucDisplayMode);
void RTDEepromSaveOsdDisplayModeData(BYTE ucDisplayMode);
void RTDEepromRestoreOsdDisplayModeData(void);
void RTDEepromLoadGammaModeData(uint8_t index , uint8_t channel , uint8_t* buf_out);
void RTDEepromSaveGammaModeData(uint8_t index, uint8_t channel , int idx ,int size , uint8_t *buf_in);
void RTDEepromLoadGammaCRC(uint8_t index ,uint8_t* buf_out);
void RTDEepromSaveGammaCRC(uint8_t index, uint8_t *buf_in);

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

BYTE RTDFlashGetFreePage(void);
bit RTDFlashIsPageInfoValid(BYTE ucPage);
void RTDFlashInitialDataPage(BYTE ucPageID);
WORD RTDFlashSearchPageAddr(BYTE ucPageID);
void RTDFlashInitialAddr(void);
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode);
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode);
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);

void RTDFlashStartup(void);
void RTDFlashWholeRestore(void);
void RTDFlashRestoreBacklight(void);
void RTDFlashLoadOSDData(void);
void RTDFlashSaveOSDData(void);
void RTDFlashRestoreOSDData(void);
void RTDFlashLoadColorSetting(BYTE ucRegion);
void RTDFlashSaveColorSetting(BYTE ucColorTempType);
void RTDFlashRestoreColorSetting(void);
void RTDFlashRestoreUserColorSetting(void);
void RTDFlashLoadOsdInputSourceData(BYTE ucSource);
void RTDFlashSaveOsdInputSourceData(BYTE ucSource);
void RTDFlashRestoreOsdInputSourceData(void);
void RTDFlashLoadOsdInputPortData(BYTE ucPort);
void RTDFlashSaveOsdInputPortData(BYTE ucPort);
void RTDFlashRestoreOsdInputPortData(void);
void RTDFlashLoadOsdDisplayModeData(BYTE ucDisplayMode);
void RTDFlashSaveOsdDisplayModeData(BYTE ucDisplayMode);
void RTDFlashRestoreOsdDisplayModeData(void);
bit RTDFlashLoadOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData);
void RTDFlashSaveOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData);
void RTDFlashLoadOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
void RTDFlashSaveOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
void RTDFlashRestoreOsdRegionData(void);

#if(_PANEL_EXIST_MULTIPANEL == _ON)
void RTDFlashLoadPanelIndex(void);
void RTDFlashSavePanelIndex(void);
void RTDFlashRestorePanelIndex(void);
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
BYTE RTDNVRamTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion);
BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//----------------------------------------------------------------------------
// alant add
void RTDEepromLoadGammaCRC(uint8_t idx, uint8_t* buf_out)
{

   UserCommonEepromRead(GAMMA_CRC+idx, 1, buf_out);
}
void RTDEepromSaveGammaCRC(uint8_t idx, uint8_t *buf_in)
{
   UserCommonEepromWrite(GAMMA_CRC+idx, 1, buf_in);

}

void RTDEepromLoadGammaModeData(uint8_t index , uint8_t channel , uint8_t *buf_out)
{
	int ret = channel * GAMMA_SIZE ;
	

	switch(index)
	 {
	   default:
	   case 0:
		   UserCommonEepromRead(GAMMA_MODE1_ADDRESS + ret, GAMMA_SIZE, buf_out);
	   break;
		case 1:
		   UserCommonEepromRead(GAMMA_MODE2_ADDRESS + ret, GAMMA_SIZE, buf_out);
	   break;
		case 2:
		   UserCommonEepromRead(GAMMA_MODE3_ADDRESS + ret, GAMMA_SIZE, buf_out);
	   break;
		case 3:
		   UserCommonEepromRead(GAMMA_MODE4_ADDRESS + ret, GAMMA_SIZE, buf_out);
	   break;
		case 4:
		   UserCommonEepromRead(GAMMA_MODE5_ADDRESS + ret, GAMMA_SIZE, buf_out);
	   break;
		case 5:
		   UserCommonEepromRead(GAMMA_MODE6_ADDRESS + ret, GAMMA_SIZE, buf_out);
	   break;
	
	 }

    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromSaveGammaModeData(uint8_t index, uint8_t channel , int idx ,int size , uint8_t *buf_in)
{
  int ret = (channel * GAMMA_SIZE)+ idx*size ;
  

	switch(index)
	{
	  default:
	  case 0:
		   UserCommonEepromWrite(GAMMA_MODE1_ADDRESS +ret, size, buf_in);
	  break;
	  
	   case 1:
		   UserCommonEepromWrite(GAMMA_MODE2_ADDRESS + ret, size, buf_in);
	  break;
	   case 2:
		   UserCommonEepromWrite(GAMMA_MODE3_ADDRESS +  ret, size, buf_in);
	  break;
	   case 3:
		   UserCommonEepromWrite(GAMMA_MODE4_ADDRESS +  ret, size, buf_in);
	  break;
	   case 4:
		   UserCommonEepromWrite(GAMMA_MODE5_ADDRESS +  ret, size, buf_in);
	  break;
	   case 5:
		   UserCommonEepromWrite(GAMMA_MODE6_ADDRESS + ret, size, buf_in);
	  break;
	  
	}
	 

}


//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromStartup(void)
{
#if 1
    BYTE ucCnt = 0;

    // Check twice if VERSION CODE matches
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        pData[0] = _CHECKSUM ^ 0xFF; //0x11
        pData[1] = _VERSION_CODE ^ 0xFF; //
        UserCommonEepromRead(_EEPROM_CHECKSUM_ADDRESS, 2, pData);
//printf("%bx,%bx \r\n",pData[0],pData[1]);
        if((pData[0] == _CHECKSUM) && (pData[1] == _VERSION_CODE))
        {
            break;
        }
    }
#endif
/////////////////////////////////////////////
    // Force default value
//    pData[0] = ~_CHECKSUM;
/////////////////////////////////////////////


    if(pData[0] != _CHECKSUM)
    {
        // Load default value and save to EEPROM
        RTDEepromWholeRestore();

        // Save VERSION CODE to EEPROM
        pData[0] = _CHECKSUM;
        pData[1] = _VERSION_CODE;
        pData[2] = 0; // _PANEL_INDEX_ADDRESS

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        SET_MDOMAIN_PANEL_INDEX(0);
#endif

     UserCommonEepromWrite(_EEPROM_CHECKSUM_ADDRESS, 1, pData);//   UserCommonEepromWrite(_EEPROM_CHECKSUM_ADDRESS, 2, pData);
        UserCommonEepromWrite(_PANEL_INDEX_ADDRESS, 1, &pData[2]);
    }
    //else
	if(pData[1] != _VERSION_CODE)
    {
     pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
	 
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDEepromSaveColorSetting(_CT_USER);
  
         RTDEepromRestoreColorSetting();
	
           UserCommonEepromRestoreSystemData();
        RTDEepromRestoreOsdUserData();

#if(_VGA_SUPPORT == _ON)
        UserCommonEepromRestoreModeUserData();
#endif

        RTDEepromRestoreOsdInputSourceData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif
         SET_FACTORY_BURNIN(_ON);//alant debug
      //   SET_MODEL_TYPE(0);//alant add
        pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
    }
    else
    {
        UserCommonEepromLoadSystemData();
        RTDEepromLoadOsdUserData();

        RTDEepromLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());

        RTDEepromLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());


#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), _PCM_OSD_NATIVE);
            RTDEepromSaveOsdUserData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDEepromSaveOsdUserData();
        }
#endif
    }

 if(GET_BL_OFFSET() >20) // alant range check
 {
     SET_BL_OFFSET(10) ;
 }

/*
range check
*/
#if 0
	switch(GET_OSD_1P_INPUT_SOURCE())// alant debug
	{
        default:
			 SET_OSD_1P_INPUT_SOURCE(_D1_INPUT_PORT);
		break;
		case _D2_INPUT_PORT:
			 SET_OSD_1P_INPUT_SOURCE(_D2_INPUT_PORT);
		break;
	}
#endif
    // SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    /*
    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    */

    RTDEepromLoadColorSetting(GET_OSD_SELECT_REGION());

    // Load port settings
    {
        BYTE ucIndex = 0;
        for(ucIndex = 0; ucIndex < _OSD_INPUT_AMOUNT; ++ucIndex)
        {
            RTDEepromLoadOsdInputPortData(ucIndex);
        }
    }

	
}

//--------------------------------------------------
// Description  : Load default data and save to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromWholeRestore(void)
{
    UserCommonEepromRestoreSystemData();

#if(_VGA_SUPPORT == _ON)
    UserCommonEepromRestoreModeUserData();
    UserCommonEepromRestoreADCSetting();
#endif

    // Osd user data
    RTDEepromRestoreOsdUserData();

    // color temp
    RTDEepromRestoreColorSetting();
    RTDEepromRestoreUserColorSetting();

    // osd input source
    RTDEepromRestoreOsdInputSourceData();

    // osd input port
    RTDEepromRestoreOsdInputPortData();

    // osd region data
    RTDEepromRestoreOsdRegionData();

    // osd display mode
    RTDEepromRestoreOsdDisplayModeData();
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBacklight(void)
{
    SET_OSD_BACKLIGHT(g_stOsdUserDataDefault.usBackLight);// 90%
    RTDEepromSaveOsdUserData();
}

//--------------------------------------------------
// Description  : Load OSD data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdUserData(void)
{
    UserCommonEepromRead(_OSD_USER_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOsdUserData));

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) && (UserInterfaceGetAutoSearchTarget() != _DISPLAY_RGN_NONE))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Save OSD data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdUserData(void)
{
    UserCommonEepromWrite(_OSD_USER_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOsdUserData));
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdUserData(void)
{
    g_stOsdUserData = g_stOsdUserDataDefault;
    RTDEepromSaveOsdUserData();
}

//--------------------------------------------------
// Description  : Load color settings from EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadColorSetting(BYTE ucRegion)
{
#if(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA(ucRegion) != _GAMMA_OFF)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | ((GET_COLOR_TEMP_TYPE(ucRegion)) * _OGC_TOTAL_GAMMA * 6 + (GET_OSD_GAMMA(ucRegion) - 1) * 6), 6, pData);
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
    }
    else
#endif
    {
        UserCommonEepromRead(_COLORTEMP_DATA_ADDRESS + (GET_COLOR_TEMP_TYPE(ucRegion)) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }
}

//--------------------------------------------------
// Description  : Save color settings to EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveColorSetting(BYTE ucColorTempType)
{
    UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreColorSetting(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = _CT_9300; ucTemp < _CT_USER; ucTemp++)
    {
        g_stColorProcData = tColorTempDefaultData[ucTemp];
        RTDEepromSaveColorSetting(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp;

    stUserColorTemp = tColorTempDefaultData[_CT_USER];

    UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (_CT_USER) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&stUserColorTemp));
}

//--------------------------------------------------
// Description  : Load brightness/contrast from EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Save brightness/contrast to EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdInputSourceData(void)
{
}

//--------------------------------------------------
// Description  : Load input port data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdInputPortData(BYTE ucPort)
{
    UserCommonEepromRead(_OSD_PORT_ADDRESS + ucPort * sizeof(StructOsdInputPortDataType), sizeof(StructOsdInputPortDataType), (BYTE *)(&(g_pstOsdInputPortData[ucPort])));
}

//--------------------------------------------------
// Description  : Save input port data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdInputPortData(BYTE ucPort)
{
    UserCommonEepromWrite(_OSD_PORT_ADDRESS + ucPort * sizeof(StructOsdInputPortDataType), sizeof(StructOsdInputPortDataType), (BYTE *)(&(g_pstOsdInputPortData[ucPort])));
}

//--------------------------------------------------
// Description  : Load default input port data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdInputPortData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_INPUT_AMOUNT; ucTemp++)
    {
        g_pstOsdInputPortData[ucTemp] = tOsdInputPortDataDefault[ucTemp];
        RTDEepromSaveOsdInputPortData(ucTemp);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion)
{
    WORD usAddr = 0;

    ucRegion = ucRegion;

    switch(ucDisplayModesel)
    {
        case _OSD_DM_1P:
            usAddr = _OSD_REGION_ADDRESS;
            break;

        case _OSD_DM_2P_LR:
            usAddr = _OSD_REGION_ADDRESS + (2 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_TB:
            usAddr = _OSD_REGION_ADDRESS + (4 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_PIP:
            usAddr = _OSD_REGION_ADDRESS + (6 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_4P:
            usAddr = _OSD_REGION_ADDRESS + (8 * sizeof(StructOsdRegionDataType));
            break;

        default:
            break;
    }

    UserCommonEepromRead(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE]));

    if(ucDisplayModesel <= _OSD_DM_4P)
    {
        usAddr += sizeof(StructOsdRegionDataType);
        UserCommonEepromRead(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE]));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromSaveOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion)
{
    WORD usAddr = 0;

    ucRegion = ucRegion;

    switch(ucDisplayModesel)
    {
        case _OSD_DM_1P:
            usAddr = _OSD_REGION_ADDRESS;
            break;

        case _OSD_DM_2P_LR:
            usAddr = _OSD_REGION_ADDRESS + (2 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_TB:
            usAddr = _OSD_REGION_ADDRESS + (4 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_2P_PIP:
            usAddr = _OSD_REGION_ADDRESS + (6 * sizeof(StructOsdRegionDataType));
            break;

        case _OSD_DM_4P:
            usAddr = _OSD_REGION_ADDRESS + (8 * sizeof(StructOsdRegionDataType));
            break;

        default:
            break;
    }

    UserCommonEepromWrite(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE]));

    if(ucDisplayModesel <= _OSD_DM_4P)
    {
        usAddr += sizeof(StructOsdRegionDataType);
        UserCommonEepromWrite(usAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE]));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromRestoreOsdRegionData(void)
{
    BYTE ucDisplayModeTemp = 0;

    for(ucDisplayModeTemp = 0; ucDisplayModeTemp < _OSD_DM_AMOUNT; ucDisplayModeTemp++)
    {
        switch(ucDisplayModeTemp)
        {
            case _OSD_DM_1P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[(RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL) + 1)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_1P_FULL);
                break;

            case _OSD_DM_2P_LR:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_L)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_R)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_LR_L);
                break;

            case _OSD_DM_2P_TB:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_T)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_B)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_TB_T);
                break;

            case _OSD_DM_2P_PIP:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_SUB)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN);
                break;

            case _OSD_DM_4P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_OUTSIDE)];
                RTDEepromSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE);
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromLoadOsdDisplayModeData(BYTE ucDisplayMode)
{
    UserCommonEepromRead(_OSD_DISPLAY_MODE_ADDRESS + ucDisplayMode * sizeof(StructOsdDisplayModeDataType), sizeof(StructOsdDisplayModeDataType), (BYTE *)(&g_stOsdDisplayModeData));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromSaveOsdDisplayModeData(BYTE ucDisplayMode)
{
    UserCommonEepromWrite(_OSD_DISPLAY_MODE_ADDRESS + ucDisplayMode * sizeof(StructOsdDisplayModeDataType), sizeof(StructOsdDisplayModeDataType), (BYTE *)(&g_stOsdDisplayModeData));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromRestoreOsdDisplayModeData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_DM_AMOUNT; ucTemp++)
    {
        g_stOsdDisplayModeData = tOsdDisplayModeDataDefault[ucTemp];
        RTDEepromSaveOsdDisplayModeData(ucTemp);
    }
}

//    void RTDEepromRestoreSixColorData(void);
//    {
//
//    }
//
//    void RTDEepromSavePanelUsedTimeData(void);
//    {
//
//    }
//





#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get the free page number of flash
// Input Value  : None
// Output Value : Free page index
//--------------------------------------------------
BYTE RTDFlashGetFreePage(void)
{
    BYTE ucPageID = _START_OF_PAGEID;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    // If the _END_PAGE page has the biggest move count, suppose first page is free page
    if(g_ulFlashMoveCount > 0)
    {
        if(g_ucFlashLastPage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
        {
            ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
        }
        else
        {
            ucFreePage = g_ucFlashLastPage + 1;
        }
    }

    // Check the supposed free page is actual free page which has not been used ever
    do
    {
        if(ucFreePage == g_pucFlashPageArr[ucPageID])
        {
            if(ucFreePage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
            {
                ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
            }
            else
            {
                ucFreePage += 1;
            }

            ucPageID = _START_OF_PAGEID;
        }
        else
        {
            ucPageID++;
        }
    }
    while(ucPageID <= _END_OF_PAGEID);

    return ucFreePage;
}

//--------------------------------------------------
// Description  : Check the page is vaild or not
// Input Value  : ucPage: The page to be check, must between 0 and (_END_PAGE - _START_PAGE)
// Output Value : _TRUE means the page is valid, _FLASE is invalid
//--------------------------------------------------
bit RTDFlashIsPageInfoValid(BYTE ucPage)
{
    WORD usPageInfoAddr = ucPage * _FLASH_PAGE_SIZE;
    BYTE ucPageInfoChecksum = 0;
    BYTE pucPageInfo[5] = {0};

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageInfoAddr + _PAGEINFO_CHECKSUM_ADDR, 5, pucPageInfo);
    ucPageInfoChecksum = pucPageInfo[1] ^ pucPageInfo[2] ^ pucPageInfo[3] ^ pucPageInfo[4];

    if(ucPageInfoChecksum == pucPageInfo[0])
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial data page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialDataPage(BYTE ucPageID)
{
    WORD usAddr = _SYSTEM_EEPROM_EMULATION_START_PAGE * _FLASH_PAGE_SIZE;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    ucFreePage = RTDFlashGetFreePage();
    // Initial page index
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Initial address
    g_pusFlashAddrArr[ucPageID] = 0;
    // Initial move count
    g_ulFlashMoveCount++;
    g_ucFlashLastPage = ucFreePage;

    usAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID]);

    pData[0] = ucPageID;
    pData[1] = (BYTE)(g_ulFlashMoveCount >> 16);
    pData[2] = (BYTE)(g_ulFlashMoveCount >> 8);
    pData[3] = (BYTE)g_ulFlashMoveCount;
    pData[4] = pData[0] ^ pData[1] ^ pData[2] ^ pData[3];
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_PAGEID_ADDR, 4, pData);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_CHECKSUM_ADDR, 1, &pData[4]);
}

//--------------------------------------------------
// Description  : Search the last saved item address, and next new item position
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD RTDFlashSearchPageAddr(BYTE ucPageID)
{
    WORD usItemAddr = 0;
    WORD usPageAddr = 0;

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the last data item address
    for(usItemAddr = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usItemAddr > 0; usItemAddr--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + (usItemAddr - 1) * _DATA_ITEM_LENGTH, 1, pData);
        if(pData[0] != 0xFF)
        {
            return usItemAddr;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : Flash address initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialAddr(void)
{
    BYTE ucCnt = 0;
    WORD usAddr = 0;
    DWORD ulMoveCount = 0;
    BYTE ucPageID = 0;

    g_ulFlashMoveCount = 0;
    g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        g_pucFlashPageArr[ucPageID] = 0xFF;
    }

    // Find the page whose move count is the biggest and get the max move count
    for(ucCnt = _SYSTEM_EEPROM_EMULATION_START_PAGE; ucCnt < (_SYSTEM_EEPROM_EMULATION_END_PAGE + 1); ucCnt++)
    {
        // Check the page is valid or not
        if(RTDFlashIsPageInfoValid(ucCnt) == _TRUE)
        {
            usAddr = ucCnt * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR;

            // Get the move count of current page
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 4, pData);
            ulMoveCount = ((DWORD)(pData[1]) << 16) | ((DWORD)(pData[2]) << 8) | ((DWORD)(pData[3]));

            // Get the max move count and its page index
            if(ulMoveCount >= g_ulFlashMoveCount)
            {
                g_pucFlashPageArr[pData[0]] = ucCnt;
                g_ulFlashMoveCount = ulMoveCount;
                g_ucFlashLastPage = ucCnt;
            }
            // Check Other vaild page index
            else
            {
                if(g_pucFlashPageArr[pData[0]] == 0xFF)
                {
                    g_pucFlashPageArr[pData[0]] = ucCnt;
                }
                else // Check which page have begger Movecount
                {
                    usAddr = g_pucFlashPageArr[pData[0]] * _FLASH_PAGE_SIZE + _PAGEINFO_MOVECOUNT_ADDR;
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 3, &pData[1]);
                    if(ulMoveCount > (((DWORD)(pData[1]) << 16) | ((DWORD)(pData[2]) << 8) | ((DWORD)(pData[3]))))
                    {
                        g_pucFlashPageArr[pData[0]] = ucCnt;
                    }
                }
            }
        }
    }

    // If this page is missing, intial this single page
    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        if(g_pucFlashPageArr[ucPageID] == 0xFF)
        {
            // This function will increase g_ulFlashMovePage,and now g_ucFlashLastPage is the page index which has the biggest move count value
            RTDFlashInitialDataPage(ucPageID);
            RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
        }
        else
        {
            // Initial g_pusFlashAddrArr
            g_pusFlashAddrArr[ucPageID] = RTDFlashSearchPageAddr(ucPageID);
        }
    }
}

//--------------------------------------------------
// Description  : Get the checksum and version code from flash
// Input Value  : pucChecksum: the checksum get from flash
//                pucVersionCode: the version code get from flash
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode)
{
    // Get the checksum and version code
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, pucChecksum);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, pucVersionCode);
}

//--------------------------------------------------
// Description  : Save the checksum & version code to flash
// Input Value  : ucChecksum, checksum value
//                ucVersionCode, version code value
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode)
{
    BYTE ucVersionCodeRead = 0;
    BYTE ucChecksumRead = 0;

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCodeRead);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksumRead);

    // Do not need save checksum or version code
    if((ucVersionCode == ucVersionCodeRead) && (ucChecksum == ucChecksumRead))
    {
        return;
    }
    // Need to save version code and checksum in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save version code in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum == ucChecksumRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    }
    // Need to save checksum in current page
    else if((ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF) && (ucVersionCode == ucVersionCodeRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save checksum and version code to free page
    else
    {
        memset(pData, 0xFF, _DATA_ITEM_LENGTH);
        RTDFlashMoveData(_CHECKSUM_VERSIONCODE_ID, pData);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
}

//--------------------------------------------------
// Description  : Move data to another page of flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData)
{
    BYTE ucPrevPage = g_pucFlashPageArr[ucPageID];
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucItemIndex = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usPrevPageAddr = 0;
    WORD usMovedItemCount = 0;
    WORD usMovedAddrIndex = 0;
    BYTE ucItemID = 0;
    BYTE ucIndex = 0;
    BYTE ucChecksum = 0xFF;
    BYTE ucVersioncode = 0xFF;

    // Load checksum and version code
    if(pucData[0] != 0xFF)
    {
        RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersioncode);
    }

    // Get free page data will move to
    ucFreePage = RTDFlashGetFreePage();

    // First sector erase the free page specified by g_ucFlashFreePage
    if(UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage) == _FALSE)
    {
        return _FALSE;
    }

    // Save the latest data item to the new page if need, when save checksum and version, it is not necessary
    // We do not save the item id at last because page info has not been saved
    if(pucData[0] != 0xFF)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage * _FLASH_PAGE_SIZE + ucItemIndex, _DATA_ITEM_LENGTH, pucData);

        // Clear Buffer
        memset(pucData, 0xFF, _DATA_ITEM_LENGTH);

        // And then load the latest data items which saved in the old full page to the new page from bottom to top
        usMovedItemCount = 1;
    }
    else
    {
        usMovedItemCount = 0;
    }

    // Update ucFlashPage
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Update move count value
    g_ulFlashMoveCount += 1;
    g_ucFlashLastPage = ucFreePage;

    usPrevPageAddr = ucPrevPage * _FLASH_PAGE_SIZE;
    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the valid item and move to new free page
    for(usAddrIndex = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex > 0; usAddrIndex--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, 1, &ucItemID);

        if(ucItemID != 0xFF)
        {
            // Check the item has been moved or not by item ID
            for(usMovedAddrIndex = 0; usMovedAddrIndex < usMovedItemCount; usMovedAddrIndex++)
            {
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedAddrIndex * _DATA_ITEM_LENGTH, 1, pData);
                if(pData[0] == ucItemID)
                {
                    break;
                }
            }

            if(usMovedAddrIndex >= usMovedItemCount)
            {
                // The item has not been moved, then check the item is valid or not
                pucData[15] = 0;
                for(ucIndex = 0; ucIndex < (_DATA_ITEM_LENGTH - 1); ucIndex++)
                {
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH + ucIndex, 1, pData);
                    pucData[15] = pucData[15] ^ pData[0];
                }

                // Check the checksum
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + usAddrIndex * _DATA_ITEM_LENGTH - 1, 1, pData);
                if(pucData[15] != pData[0])
                {
                    // Checksum check fail, the item is invalid
                    continue;
                }

                // Move the item to new free page
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);
                UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedItemCount * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);

                usMovedItemCount++;
            }
        }
    }

    // Update the data item address in the new page
    g_pusFlashAddrArr[ucPageID] = usMovedItemCount;

    // Last update the new moved page info fields
    // Save checksum & version code
    if(ucPageID == _CHECKSUM_VERSIONCODE_ID)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersioncode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }

    // Save page info
    pData[0] = ucPageID;
    pData[1] = (BYTE)(g_ulFlashMoveCount >> 16);
    pData[2] = (BYTE)(g_ulFlashMoveCount >> 8);
    pData[3] = (BYTE)g_ulFlashMoveCount;
    pData[4] = pData[0] ^ pData[1] ^ pData[2] ^ pData[3];
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR, 4, pData);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_CHECKSUM_ADDR, 1, &pData[4]);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Flash check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashStartup(void)
{
    BYTE ucChecksum = 0;
    BYTE ucVersionCode = 0;
    BYTE ucPageID = 0;

    RTDFlashInitialAddr();

    // Get FW checksum and version code
    RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersionCode);

    if((ucChecksum != _CHECKSUM) ||  (ucVersionCode != _VERSION_CODE))
    {
        // Checksum is changed, load default value and save to flash
        for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
        {
            RTDFlashInitialDataPage(ucPageID);
        }

        RTDFlashWholeRestore();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashRestorePanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
#if 0    
    else if(ucVersionCode != _VERSION_CODE)
    {
        // Restore CT User color setting
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + _CT_USER, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(_CT_USER);
        }

        UserCommonFlashRestoreSystemData();
        RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonFlashRestoreModeUserData();
#endif

        RTDFlashRestoreOsdInputSourceData();
#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
#endif    
    else
    {
        UserCommonFlashLoadSystemData();
        RTDFlashLoadOSDData();

        RTDFlashLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
        RTDFlashLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), _PCM_OSD_NATIVE);
            RTDFlashSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDFlashSaveOSDData();
        }
#endif
    }

    RTDFlashLoadColorSetting(GET_OSD_SELECT_REGION());

    // Load port settings
    {
        BYTE ucIndex = 0;
        for(ucIndex = 0; ucIndex < _OSD_INPUT_AMOUNT; ++ucIndex)
        {
            RTDFlashLoadOsdInputPortData(ucIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Load default data and save to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashWholeRestore(void)
{
    UserCommonFlashRestoreSystemData();

#if(_VGA_SUPPORT == _ON)
    UserCommonFlashRestoreModeUserData();
    UserCommonFlashRestoreADCSetting();
#endif

    // Osd user data
    RTDFlashRestoreOSDData();

    // color temp
    RTDFlashRestoreColorSetting();
    RTDFlashRestoreUserColorSetting();

    // osd input source
    RTDFlashRestoreOsdInputSourceData();

    // osd input port
    RTDFlashRestoreOsdInputPortData();

    // osd region data
    RTDFlashRestoreOsdRegionData();

    // osd display mode
    RTDFlashRestoreOsdDisplayModeData();
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBacklight(void)
{
    BYTE ucItemOffset = 0;

    SET_OSD_BACKLIGHT(g_stOsdUserDataDefault.usBackLight);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            g_stOsdUserData = g_stOsdUserDataDefault;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((((BYTE *)(&g_stOsdUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((((BYTE *)(&g_stOsdUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }
#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) && (UserInterfaceGetAutoSearchTarget() != _DISPLAY_RGN_NONE))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}


//--------------------------------------------------
// Description  : Save OSD data to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOsdUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOsdUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOSDData(void)
{
    BYTE ucItemOffset = 0;

    g_stOsdUserData = g_stOsdUserDataDefault;

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load color settings from Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadColorSetting(BYTE ucRegion)
{
#if(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA(ucRegion) != _GAMMA_OFF)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (GET_COLOR_TEMP_TYPE(ucRegion) * _OGC_TOTAL_GAMMA * 6 + (GET_OSD_GAMMA(ucRegion) - 1) * 6), 6, pData);
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
    }
    else
#endif
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + GET_COLOR_TEMP_TYPE(ucRegion), pData, sizeof(StructColorProcDataType)) == _TRUE)
        {
            memcpy(&g_stColorProcData, pData, sizeof(StructColorProcDataType));
        }
        else
        {
            g_stColorProcData = tColorTempDefaultData[GET_COLOR_TEMP_TYPE(ucRegion)];
        }
    }
}

//--------------------------------------------------
// Description  : Save color settings to Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveColorSetting(BYTE ucColorTempType)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, (BYTE *)(&g_stColorProcData), sizeof(StructColorProcDataType));
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreColorSetting(void)
{
    BYTE ucColorTempIndex = 0;

    for(ucColorTempIndex = 0; ucColorTempIndex < _CT_COLORTEMP_AMOUNT; ucColorTempIndex++)
    {
        g_stColorProcData = tColorTempDefaultData[ucColorTempIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(ucColorTempIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC5_USER, pData, 1) == _TRUE)
    {
        stUserColorTemp = g_stColorProcData;
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDFlashSaveColorSetting(_CT_USER);
        g_stColorProcData = stUserColorTemp;
    }
}

//--------------------------------------------------
// Description  : Load Input Source from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Save Input Source from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdInputSourceData(BYTE ucSource)
{
    ucSource = ucSource;
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOsdInputSourceData(void)
{
}

//--------------------------------------------------
// Description  : Load Input Port Data
// Input Value  : ucPort --> Input Port
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOsdInputPortData(BYTE ucPort)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_INPUT_A_PORT + ucPort, pData, sizeof(StructOsdInputPortDataType)) == _TRUE)
    {
        memcpy(&(g_pstOsdInputPortData[ucPort]), pData, sizeof(StructOsdInputPortDataType));
    }
    else
    {
        g_pstOsdInputPortData[ucPort] = tOsdInputPortDataDefault[ucPort];
    }
}

//--------------------------------------------------
// Description  : Save Input Port Data
// Input Value  : ucPort --> Input Port
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdInputPortData(BYTE ucPort)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_INPUT_A_PORT + ucPort, (BYTE *)(&(g_pstOsdInputPortData[ucPort])), sizeof(StructOsdInputPortDataType));
}

//--------------------------------------------------
// Description  : Retore Input Port Data
// Input Value  : ucPort --> Input Port
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOsdInputPortData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_INPUT_AMOUNT; ucTemp++)
    {
        g_pstOsdInputPortData[ucTemp] = tOsdInputPortDataDefault[ucTemp];
        RTDFlashSaveOsdInputPortData(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Load Display Mode Data
// Input Value  : ucDisplayMode --> Display mode
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOsdDisplayModeData(BYTE ucDisplayMode)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_OSD_DM_1P + ucDisplayMode, pData, sizeof(StructOsdDisplayModeDataType)) == _TRUE)
    {
        memcpy(&g_stOsdDisplayModeData, pData, sizeof(StructOsdDisplayModeDataType));
    }
    else
    {
        g_stOsdDisplayModeData = tOsdDisplayModeDataDefault[ucDisplayMode];
    }
}

//--------------------------------------------------
// Description  : Save Display Mode Data
// Input Value  : ucDisplayMode --> Display mode
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdDisplayModeData(BYTE ucDisplayMode)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_OSD_DM_1P + ucDisplayMode, (BYTE *)(&g_stOsdDisplayModeData), sizeof(StructOsdDisplayModeDataType));
}

//--------------------------------------------------
// Description  : Restore Display Mode Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOsdDisplayModeData(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _OSD_DM_AMOUNT; ucTemp++)
    {
        g_stOsdDisplayModeData = tOsdDisplayModeDataDefault[ucTemp];
        RTDFlashSaveOsdDisplayModeData(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Load One Group OSD data from Flash
// Input Value  : usAddr: address in ucBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : return _TRUE if load success, else return _FALSE
//--------------------------------------------------
bit RTDFlashLoadOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = usLength;

    for(ucItemOffset = 0; ucItemOffset < ((usLength + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // 2 expression the Flash date item ID length for one group data stucture
        if(ucItemOffset > 2)
        {
            break;
        }

        if(UserCommonFlashLoadItem((usAddr + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            // g_stOSDUserData = g_stOSDDefaultData;
            return _FALSE;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((pucData + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((pucData + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Save One Group OSD data to Flash
// Input Value  : usAddr: address in ucBank
//                pucData: data buffer to save
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDDataGroup(WORD usAddr, WORD usLength, BYTE *pucData)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = usLength;

    for(ucItemOffset = 0; ucItemOffset < ((usLength + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        if(ucItemOffset > 2)
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((usAddr + ucItemOffset), (pucData + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((usAddr + ucItemOffset), (pucData + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Load Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
void RTDFlashLoadOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucItemAddr = 0;
    BYTE ucRegionInx = 0;

    ucRegion = ucRegion;

    switch(ucDisplayMode)
    {
        case _OSD_DM_1P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START;
            ucRegionInx = 0;
            break;

        case _OSD_DM_2P_LR:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 4;
            ucRegionInx = 2;
            break;

        case _OSD_DM_2P_TB:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 8;
            ucRegionInx = 4;
            break;

        case _OSD_DM_2P_PIP:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 12;
            ucRegionInx = 6;
            break;

        case _OSD_DM_4P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 16;
            ucRegionInx = 8;
            break;

        default:
            break;
    }

    if(RTDFlashLoadOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE])) == _FALSE)
    {
        g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[ucRegionInx];
    }

    if(ucDisplayMode <= _OSD_DM_4P)
    {
        ucItemAddr += 2;

        if(RTDFlashLoadOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE])) == _FALSE)
        {
            g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[ucRegionInx + 1];
        }
    }
}

//--------------------------------------------------
// Description  : Save Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucItemAddr = 0;

    ucRegion = ucRegion;

    switch(ucDisplayMode)
    {
        case _OSD_DM_1P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START;
            break;

        case _OSD_DM_2P_LR:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 4;
            break;

        case _OSD_DM_2P_TB:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 8;
            break;

        case _OSD_DM_2P_PIP:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 12;
            break;

        case _OSD_DM_4P:
            ucItemAddr = _FLASH_ITEMID_OSD_REGION_START + 16;
            break;

        default:
            break;
    }

    RTDFlashSaveOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_INSIDE]));

    if(ucDisplayMode <= _OSD_DM_4P)
    {
        ucItemAddr += 2;
        RTDFlashSaveOSDDataGroup(ucItemAddr, sizeof(StructOsdRegionDataType), (BYTE *)(&g_pstOsdRegionData[_OUTSIDE]));
    }
}

//--------------------------------------------------
// Description  : Retore Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
void RTDFlashRestoreOsdRegionData(void)
{
    BYTE ucDisplayModeTemp = 0;

    for(ucDisplayModeTemp = 0; ucDisplayModeTemp < _OSD_DM_AMOUNT; ucDisplayModeTemp++)
    {
        switch(ucDisplayModeTemp)
        {
            case _OSD_DM_1P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL)];
                g_pstOsdRegionData[_OUTSIDE] = tOsdRegionDataDefault[(RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_1P_FULL) + 1)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_1P_FULL);
                break;

            case _OSD_DM_2P_LR:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_L)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_LR_R)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_LR_L);
                break;

            case _OSD_DM_2P_TB:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_T)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_TB_B)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_TB_T);
                break;

            case _OSD_DM_2P_PIP:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_2P_PIP_SUB)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_2P_PIP_MAIN);
                break;

            case _OSD_DM_4P:
                g_pstOsdRegionData[_INSIDE] = tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE)];
                g_pstOsdRegionData[_OUTSIDE]= tOsdRegionDataDefault[RTDNVRamTransferOsdRegionIndex(ucDisplayModeTemp, _OSD_SR_4P_LT_OUTSIDE)];
                RTDFlashSaveOsdRegionData(ucDisplayModeTemp, _OSD_SR_4P_LT_INSIDE);
                break;

            default:
                break;
        }
    }
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Load panel index from flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelIndex(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
    }
    else
    {
        SET_MDOMAIN_PANEL_INDEX(0);
    }
}

//--------------------------------------------------
// Description  : Save panel index to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelIndex(void)
{
    BYTE ucPanelIndex = 0;

    ucPanelIndex = GET_MDOMAIN_PANEL_INDEX();

    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_INDEX, &ucPanelIndex, 1);
}

//--------------------------------------------------
// Description  : Restore panel index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelIndex(void)
{
    SET_MDOMAIN_PANEL_INDEX(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelIndex();
    }
}
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)


//--------------------------------------------------
// Description  : Transfer Osd Region Type
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
BYTE RTDNVRamTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucType = 0;

    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        ucType = ucRegion % 2;
    }
    else
    {
        switch(ucDisplayMode)
        {
            case _OSD_DM_1P:
                ucType = _INSIDE;
                break;

            case _OSD_DM_2P_LR:
                if(ucRegion == _OSD_SR_2P_LR_R)
                {
                    ucType = _INSIDE;
                }
                else
                {
                    ucType = _OUTSIDE;
                }
                break;

            case _OSD_DM_2P_TB:
                if(ucRegion == _OSD_SR_2P_TB_B)
                {
                    ucType = _INSIDE;
                }
                else
                {
                    ucType = _OUTSIDE;
                }
                break;

            case _OSD_DM_2P_PIP:
                if(ucRegion == _OSD_SR_2P_PIP_SUB)
                {
                    ucType = _INSIDE;
                }
                else
                {
                    ucType = _OUTSIDE;
                }
                break;

            case _OSD_DM_4P:
                switch(ucRegion)
                {
                    case _OSD_SR_4P_LT_INSIDE:
                    case _OSD_SR_4P_LB_INSIDE:
                    case _OSD_SR_4P_RT_INSIDE:
                    case _OSD_SR_4P_RB_INSIDE:
                        ucType = _INSIDE;
                        break;

                    default:
                        ucType = _OUTSIDE;
                        break;
                }
                break;

            default:
                break;
        }
    }

    return ucType;
}

//--------------------------------------------------
// Description  : Transfer Osd Region index
// Input Value  : ucDisplayMode --> Display mode
//                     ucRegion --> Display region
// Output Value : _INSIDE / _OUTSIDE
//--------------------------------------------------
BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion)
{
    BYTE ucIndex = 0;

    switch(ucDisplayMode)
    {
        case _OSD_DM_1P:
            ucIndex = 0;
            break;

        case _OSD_DM_2P_LR:
            if(ucRegion >= _OSD_SR_2P_LR_FULL)
            {
                ucRegion = _OSD_SR_2P_LR_L;
            }
            ucIndex = 2 + ucRegion;
            break;

        case _OSD_DM_2P_TB:
            if(ucRegion >= _OSD_SR_2P_TB_FULL)
            {
                ucRegion = _OSD_SR_2P_TB_T;
            }
            ucIndex = 4 + ucRegion;
            break;

        case _OSD_DM_2P_PIP:
            if(ucRegion >= _OSD_SR_2P_PIP_FULL)
            {
                ucRegion = _OSD_SR_2P_PIP_MAIN;
            }
            ucIndex = 6 + ucRegion;
            break;

        case _OSD_DM_4P:
            if(ucRegion >= _OSD_SR_4P_FULL)
            {
                ucRegion = _OSD_SR_4P_LT_OUTSIDE;
            }
            ucIndex = 8 + (ucRegion % 2);
            break;

        default:
            break;
    }

    return ucIndex;
}
#endif // #if(_OSD_TYPE == _REALTEK_2014_OSD)

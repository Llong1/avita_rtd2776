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
// ID Code      : RTD2014NVRamOsd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2014_OSD)

#define _PANEL_INDEX_ADDRESS                            (_VGA_MODE_DATA_ADDRESS_END + 1)
#define _PANEL_INDEX_ADDRESS_END                        (_PANEL_INDEX_ADDRESS + 1 - 1)

#define _OSD_USER_DATA_ADDRESS                          (_PANEL_INDEX_ADDRESS_END + 1)
#define _OSD_USER_DATA_ADDRESS_END                      (_OSD_USER_DATA_ADDRESS + sizeof(StructOsdUserDataType) - 1)

#define _COLORTEMP_DATA_ADDRESS                         (_OSD_USER_DATA_ADDRESS_END + 1)
#define _COLORTEMP_DATA_ADDRESS_END                     (_COLORTEMP_DATA_ADDRESS + (sizeof(StructColorProcDataType) * (_CT_COLORTEMP_AMOUNT + 1)) - 1)

#define _PORT_AMOUNT                                    (_OSD_INPUT_AMOUNT) // 1A 8D
#define _OSD_PORT_ADDRESS                               (_COLORTEMP_DATA_ADDRESS_END + 1)
#define _OSD_PORT_ADDRESS_END                           (_OSD_PORT_ADDRESS + (sizeof(StructOsdInputPortDataType) * _PORT_AMOUNT) - 1)

#define _REGION_AMOUNT                                  (10) // 1Px2 2Px6 4Px2
#define _OSD_REGION_ADDRESS                             (_OSD_PORT_ADDRESS_END + 1)
#define _OSD_REGION_ADDRESS_END                         (_OSD_REGION_ADDRESS + (sizeof(StructOsdRegionDataType) * _REGION_AMOUNT) - 1)

#define _OSD_DISPLAY_MODE_ADDRESS                       (_OSD_REGION_ADDRESS_END + 1)
#define _OSD_DISPLAY_MODE_ADDRESS_EMD                   (_OSD_DISPLAY_MODE_ADDRESS + (sizeof(StructOsdDisplayModeDataType) * _OSD_DM_AMOUNT) - 1)

//---------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
    WORD usBackLight;
    BYTE ucOsdHPos;
    BYTE ucOsdVPos;
    BYTE ucOsdTimeout;
    BYTE ucTransparency;
    BYTE ucODGain;
    BYTE ucHLWinType;
    BYTE ucVolume;
    BYTE ucOsdInputPort0;
    WORD usHour;
    BYTE ucMin;
    BYTE ucDisplayMode;
    BYTE ucSelectRegionWidth;
    BYTE ucSelectRegionColor;
    BYTE ucPipSubPosType;
    WORD usPipSubHPos;
    WORD usPipSubVPos;
    BYTE ucPipSubScaling;
    BYTE ucPipSubBlending;
    BYTE ucPbpLrRatio;
    BYTE ucCloneModeMtP;
    BYTE b1CloneMode1P : 1;
    BYTE b4Language : 4;
    BYTE b3VGARGBYUV : 3;
    BYTE b3DVIRGBYUV : 3;
    BYTE b33DConvergenceMode : 3;
    BYTE b1FactoryAutoColorType : 1;
    BYTE b1PCMSoftProftMode : 1;
    BYTE b2OsdDpMST : 2;
    BYTE b3OsdDispRotate : 3;
    BYTE b3D0DpLaneMode : 3;
    BYTE b3D1DpLaneMode : 3;
    BYTE b3D6DpLaneMode : 3;
    BYTE b2OsdDpD0PortVersion : 2;
    BYTE b2OsdDpD1PortVersion : 2;
    BYTE b2OsdDpD6PortVersion : 2;
    BYTE b1DDCCIStatus : 1;
    BYTE b1OsdDcrStatus : 1;
    BYTE b2OsdRotate : 2;
    BYTE b2DispRotationSizeType : 2;
    BYTE b1VolumeMute : 1;
    BYTE b1AudioStandAloneStatus : 1;
    BYTE b1ODStatus : 1;
    BYTE b1FreeSyncStatus : 1;
    BYTE b2LatencyStatus : 2;
//--------------------------------------------------------

#if (_FALSE_COLOR_SUPPORT == _ON)
    BYTE ucFalseColorStatus;
    BYTE ucFalseColorLevel[17];
#endif
} StructOsdUserDataType;

typedef struct
{
    WORD usColorTempR;
    WORD usColorTempG;
    WORD usColorTempB;
} StructColorProcDataType;

typedef struct
{
    BYTE ucAspectOriginRatio;
    //-----------------------------------
    BYTE b3Sharpness : 3;
    BYTE b3AspectRatio : 3;
    BYTE b1OverScan : 1;
    //-----------------------------------
#if(_ULTRA_HDR_SUPPORT == _ON)
    BYTE b1HdrDarkEnhanceS : 1;
    BYTE ucHdrMode;
#endif

} StructOsdInputPortDataType;

typedef struct
{
    BYTE ucSixColorHueR;
    BYTE ucSixColorSaturationR;
    BYTE ucSixColorHueY;
    BYTE ucSixColorSaturationY;
    BYTE ucSixColorHueG;
    BYTE ucSixColorSaturationG;
    BYTE ucSixColorHueC;
    BYTE ucSixColorSaturationC;
    BYTE ucSixColorHueB;
    BYTE ucSixColorSaturationB;
    BYTE ucSixColorHueM;
    BYTE ucSixColorSaturationM;
    BYTE ucHue;
    BYTE ucSaturation;
    //-----------------------------------
    BYTE b4ColorEffect : 4;
    BYTE b4ColorTempType : 4;
    //-----------------------------------
    BYTE b3Gamma : 3;
    BYTE b3PCMStatus : 3;
    BYTE b1PanelUniformity : 1;
    BYTE b2UltraVividStatus : 2;
    //-----------------------------------
    WORD usBrightness;
    WORD usContrast;

    BYTE b3PanelUniformityType : 3;
} StructOsdRegionDataType;

typedef struct
{
    BYTE ucSelectRegion;
    BYTE ucOsdInputPort0;
    BYTE ucOsdInputPort1;
    BYTE ucOsdInputPort2;
    BYTE ucOsdInputPort3;
    BYTE ucAuidioInputRegion;
} StructOsdDisplayModeDataType;

#ifndef __RTD_NVRAM_OSD__
//----------------------------------------------------------------------------------------
// Extern Variables from RTD2014NVRamOsd.c
//----------------------------------------------------------------------------------------
extern BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
extern WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];

//----------------------------------------------------------------------------------------
// Extern functions from RTD2014NVRamOsd.c
//----------------------------------------------------------------------------------------

extern StructOsdUserDataType g_stOsdUserData;
extern StructColorProcDataType g_stColorProcData;
extern StructOsdInputPortDataType g_pstOsdInputPortData[9];
extern StructOsdRegionDataType g_pstOsdRegionData[2];
extern StructOsdDisplayModeDataType g_stOsdDisplayModeData;


//    extern StructBriConDataType g_stBriConData;

//    extern code StructColorProcDataType tColorTempDefaultData[];
//    extern StructSixColorDataType g_stSixColorData;
//    extern StructTimeType g_stPanelTimeData;
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern void RTDEepromStartup(void);
extern void RTDEepromWholeRestore(void);
extern void RTDEepromRestoreBacklight(void);

extern void RTDEepromLoadOsdUserData(void);
extern void RTDEepromSaveOsdUserData(void);
extern void RTDEepromRestoreOsdUserData(void);

extern void RTDEepromLoadColorSetting(BYTE ucRegion);
extern void RTDEepromSaveColorSetting(BYTE ucColorTempType);
extern void RTDEepromRestoreColorSetting(void);
extern void RTDEepromRestoreUserColorSetting(void);

extern void RTDEepromLoadOsdInputSourceData(BYTE ucSource);
extern void RTDEepromSaveOsdInputSourceData(BYTE ucSource);
extern void RTDEepromRestoreOsdInputSourceData(void);

extern void RTDEepromLoadOsdInputPortData(BYTE ucPort);
extern void RTDEepromSaveOsdInputPortData(BYTE ucPort);
extern void RTDEepromRestoreOsdInputPortData(void);

//extern BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion);
//extern BYTE RTDEepromTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion);
extern void RTDEepromLoadOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
extern void RTDEepromSaveOsdRegionData(BYTE ucDisplayModesel, BYTE ucRegion);
extern void RTDEepromRestoreOsdRegionData(void);

extern void RTDEepromLoadOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDEepromSaveOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDEepromRestoreOsdDisplayModeData(void);

//extern void RTDEepromRestoreSixColorData(void);
//extern void RTDEepromSavePanelUsedTimeData(void);


#define RTDNVRamStartup()                               RTDEepromStartup()
#define RTDNVRamWholeRestore()                          RTDEepromWholeRestore()
#define RTDNVRamRestoreBacklight()                      RTDEepromRestoreBacklight()
#define RTDNVRamSaveOsdUserData()                       RTDEepromSaveOsdUserData()
#define RTDNVRamRestoreOsdUserData()                    RTDEepromRestoreOsdUserData()
#define RTDNVRamLoadColorSetting(x)                     RTDEepromLoadColorSetting(x)
#define RTDNVRamSaveColorSetting(x)                     RTDEepromSaveColorSetting(x)
#define RTDNVRamRestoreColorSetting()                   RTDEepromRestoreColorSetting()
#define RTDNVRamRestoreUserColorSetting()               RTDEepromRestoreUserColorSetting()
#define RTDNVRamLoadOsdInputSourceData(x)               RTDEepromLoadOsdInputSourceData(x)
#define RTDNVRamSaveOsdInputSourceData(x)               RTDEepromSaveOsdInputSourceData(x)
#define RTDNVRamRestoreOsdInputSourceData()             RTDEepromRestoreOsdInputSourceData()

#define RTDNVRamLoadOsdInputPortData(x)                 RTDEepromLoadOsdInputPortData(x)
#define RTDNVRamSaveOsdInputPortData(x)                 RTDEepromSaveOsdInputPortData(x)
#define RTDNVRamRestoreOsdInputPortData()               RTDEepromRestoreOsdInputPortData()

//#define RTDNVRamTransferOsdRegionType(x, y)             RTDEepromTransferOsdRegionType(x, y)
#define RTDNVRamLoadOsdRegionData(x, y)                 RTDEepromLoadOsdRegionData(x, y)
#define RTDNVRamSaveOsdRegionData(x, y)                 RTDEepromSaveOsdRegionData(x, y)
#define RTDNVRamRestoreOsdRegionData()                  RTDEepromRestoreOsdRegionData()

#define RTDNVRamLoadOsdDisplayModeData(x)               RTDEepromLoadOsdDisplayModeData(x)
#define RTDNVRamSaveOsdDisplayModeData(x)               RTDEepromSaveOsdDisplayModeData(x)
#define RTDNVRamRestoreOsdDisplayModeData()             RTDEepromRestoreOsdDisplayModeData()

//#define RTDNVRamRestoreSixColorData()                  RTDEepromRestoreSixColorData()
//#define RTDNVRamSavePanelUsedTimeData()                RTDEepromSavePanelUsedTimeData()

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);
extern void RTDFlashStartup(void);
extern void RTDFlashWholeRestore(void);
extern void RTDFlashRestoreBacklight(void);
extern void RTDFlashSaveOSDData(void);
extern void RTDFlashRestoreOSDData(void);
extern void RTDFlashLoadColorSetting(BYTE ucRegion);
extern void RTDFlashSaveColorSetting(BYTE ucColorTempType);
extern void RTDFlashRestoreColorSetting(void);
extern void RTDFlashRestoreUserColorSetting(void);
extern void RTDFlashLoadOsdInputSourceData(BYTE ucSource);
extern void RTDFlashSaveOsdInputSourceData(BYTE ucSource);
extern void RTDFlashRestoreOsdInputSourceData(void);
extern void RTDFlashLoadOsdInputPortData(BYTE ucPort);
extern void RTDFlashSaveOsdInputPortData(BYTE ucPort);
extern void RTDFlashRestoreOsdInputPortData(void);
extern void RTDFlashLoadOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDFlashSaveOsdDisplayModeData(BYTE ucDisplayMode);
extern void RTDFlashRestoreOsdDisplayModeData(void);
extern void RTDFlashLoadOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
extern void RTDFlashSaveOsdRegionData(BYTE ucDisplayMode, BYTE ucRegion);
extern void RTDFlashRestoreOsdRegionData(void);

#define RTDNVRamStartup()                               RTDFlashStartup()
#define RTDNVRamWholeRestore()                          RTDFlashWholeRestore()
#define RTDNVRamRestoreBacklight()                      RTDFlashRestoreBacklight()
#define RTDNVRamSaveOsdUserData()                       RTDFlashSaveOSDData()
#define RTDNVRamRestoreOsdUserData()                    RTDFlashRestoreOSDData()
#define RTDNVRamLoadColorSetting(x)                     RTDFlashLoadColorSetting(x)
#define RTDNVRamSaveColorSetting(x)                     RTDFlashSaveColorSetting(x)
#define RTDNVRamRestoreColorSetting()                   RTDFlashRestoreColorSetting()
#define RTDNVRamRestoreUserColorSetting()               RTDFlashRestoreUserColorSetting()
#define RTDNVRamLoadOsdInputSourceData(x)               RTDFlashLoadOsdInputSourceData(x)
#define RTDNVRamSaveOsdInputSourceData(x)               RTDFlashSaveOsdInputSourceData(x)
#define RTDNVRamRestoreOsdInputSourceData()             RTDFlashRestoreOsdInputSourceData()

#define RTDNVRamLoadOsdInputPortData(x)                 RTDFlashLoadOsdInputPortData(x)
#define RTDNVRamSaveOsdInputPortData(x)                 RTDFlashSaveOsdInputPortData(x)
#define RTDNVRamRestoreOsdInputPortData()               RTDFlashRestoreOsdInputPortData()

#define RTDNVRamLoadOsdDisplayModeData(x)               RTDFlashLoadOsdDisplayModeData(x)
#define RTDNVRamSaveOsdDisplayModeData(x)               RTDFlashSaveOsdDisplayModeData(x)
#define RTDNVRamRestoreOsdDisplayModeData()             RTDFlashRestoreOsdDisplayModeData()

#define RTDNVRamLoadOsdRegionData(x, y)                 RTDFlashLoadOsdRegionData(x, y)
#define RTDNVRamSaveOsdRegionData(x, y)                 RTDFlashSaveOsdRegionData(x, y)
#define RTDNVRamRestoreOsdRegionData()                  RTDFlashRestoreOsdRegionData()

#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern BYTE RTDNVRamTransferOsdRegionType(BYTE ucDisplayMode, BYTE ucRegion);
extern BYTE RTDNVRamTransferOsdRegionIndex(BYTE ucDisplayMode, BYTE ucRegion);

#endif // End of #ifndef __RTD_NVRAM_OSD__

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)

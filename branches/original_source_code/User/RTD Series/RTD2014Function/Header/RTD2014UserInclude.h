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
// ID Code      : RTD2014UserInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "RTD2014UserModeTable.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of VGA Filter Table
//--------------------------------------------------
#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
#define _DIGITAL_FILTER_ENHANCE_PHASE_TABLE         "DigFilterEnhancePhaseTable.h"
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
#define _RINGING_FILTER_TABLE                       "RingingFilterTable.h"
#endif

//--------------------------------------------------
// Definitions of Flash Item Length For Each Page
//--------------------------------------------------
#define _DATA_ITEM_LENGTH                           16
#define _PAGE_INFO_LENGTH                           16

//---------------------------------------------------------
// OSD Rotate Type
//---------------------------------------------------------
#define _OSD_ROTATE_OFF                             0
#define _OSD_ROTATE_SOFTWARE                        1
#define _OSD_ROTATE_HARDWARE                        2

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
extern BYTE code tFLASH_PARTITION_BOOTTABLE[];
#endif

extern code void (*OperationTable[])(void);

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef enum
{
    _FLASH_ITEMID_VGA_ADC_DATA = 0x0000, // 0
    _FLASH_ITEMID_YPBPR_ADC_DATA,
    _FLASH_ITEMID_SYSTEM_DATA,
    _FLASH_ITEMID_PANEL_INDEX,
    _FLASH_ITEMID_OSD_DATA_START,
    _FLASH_ITEMID_OSD_DATA_0 = _FLASH_ITEMID_OSD_DATA_START,
    _FLASH_ITEMID_OSD_DATA_1, // 5
    _FLASH_ITEMID_OSD_DATA_END = _FLASH_ITEMID_OSD_DATA_1,
    _FLASH_ITEMID_BRICON_SRC0_VGA,
    _FLASH_ITEMID_BRICON_SRC1_VIDEO,
    _FLASH_ITEMID_BRICON_SRC2_DVI,
    _FLASH_ITEMID_BRICON_SRC3_HDMI,
    _FLASH_ITEMID_BRICON_SRC4_DP, // 10
    _FLASH_ITEMID_COLORPROC0_9300,
    _FLASH_ITEMID_COLORPROC1_7500,
    _FLASH_ITEMID_COLORPROC2_6500,
    _FLASH_ITEMID_COLORPROC3_5800,
    _FLASH_ITEMID_COLORPROC4_SRGB, // 15
    _FLASH_ITEMID_COLORPROC5_USER,
    _FLASH_ITEMID_SIXCOLOR_DATA,
    _FLASH_ITEMID_PANEL_DATA,
    _FLASH_ITEMID_MODE_USER_DATA, // 19
    _FLASH_ITEMID_MODE_USER_DATA_END =  _FLASH_ITEMID_MODE_USER_DATA + _MODE_SLOT_AMOUNT - 1, // 34
    _FLASH_ITEMID_INPUT_A_PORT, // 35
    _FLASH_ITEMID_INPUT_D0_PORT,
    _FLASH_ITEMID_INPUT_D1_PORT,
    _FLASH_ITEMID_INPUT_D2_PORT,
    _FLASH_ITEMID_INPUT_D3_PORT,
    _FLASH_ITEMID_INPUT_D4_PORT,
    _FLASH_ITEMID_INPUT_D5_PORT,
    _FLASH_ITEMID_INPUT_PORT_END = _FLASH_ITEMID_INPUT_D5_PORT, // 41
    _FLASH_ITEMID_DISPLAY_MODE_START,
    _FLASH_ITEMID_OSD_DM_1P = _FLASH_ITEMID_DISPLAY_MODE_START,
    _FLASH_ITEMID_OSD_DM_2P_LR,
    _FLASH_ITEMID_OSD_DM_2P_TB,
    _FLASH_ITEMID_OSD_DM_2P_PIP,
    _FLASH_ITEMID_OSD_DM_4P,
    _FLASH_ITEMID_DISPLAY_MODE_END = _FLASH_ITEMID_OSD_DM_4P, // 46
    _FLASH_ITEMID_OSD_REGION_START,
    _FLASH_ITEMID_OSD_REGION_DM_1P_0 = _FLASH_ITEMID_OSD_REGION_START,
    _FLASH_ITEMID_OSD_REGION_DM_1P_1,
    _FLASH_ITEMID_OSD_REGION_DM_1P_DEMO_OUSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_1P_DEMO_OUSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_2P_LR_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_2P_LR_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_2P_LR_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_2P_LR_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_2P_TB_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_2P_TB_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_2P_TB_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_2P_TB_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_2P_PIP_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_2P_PIP_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_2P_PIP_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_2P_PIP_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LT_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LT_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LT_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LT_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LB_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LB_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LB_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_LB_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RT_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RT_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RT_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RT_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RB_INSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RB_INSIDE_1,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RB_OUTSIDE_0,
    _FLASH_ITEMID_OSD_REGION_DM_4P_RB_OUTSIDE_1,
    _FLASH_ITEMID_OSD_REGION_END = _FLASH_ITEMID_OSD_REGION_DM_4P_RB_OUTSIDE_1, // 78

} EnumFlashItemIDType;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

//----------------------------------------------------------------------------------------
// Extern functions from UserAdjust.c
//----------------------------------------------------------------------------------------
#ifndef __USER_ADJUST__

#if((_OVERSCAN_SUPPORT == _ON) || (_ASPECT_RATIO_SUPPORT == _ON))
extern void UserAdjustResetDisplayByPort(EnumDisplayRegion enumDisplayRegion);
#endif

//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
extern void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern void UserAdjustAudioMuteSwitch(void);
extern void UserAdjustAudioVolume(BYTE ucVolume);
extern WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// DCR
//-------------------------------------------------------
#if(_DCR_SUPPORT == _ON)
extern void UserInterfaceAdjustDCR(void);
#endif

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
extern void UserAdjustDCC(EnumSelRegion enumSelRegion, BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
extern void UserAdjustICM(EnumSelRegion enumSelRegion, BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
extern void UserAdjustSCM(EnumSelRegion enumSelRegion, BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
extern void UserAdjustColorEffectMode(EnumSelRegion enumSelRegion);
#endif

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
extern void UserAdjustContrast(EnumSelRegion enumSelRegion, WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
extern void UserAdjustBrightness(EnumSelRegion enumSelRegion, WORD usBrightness);
#endif

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
extern void UserAdjustGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shHue, WORD usSat);
#endif


//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
extern void UserAdjustOD(void);
#endif

//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern void UserAdjustHLWinType(BYTE ucHLWinType);
extern void UserAdjustHLWinType5Move(void);
extern void UserAdjustHighLightWindowEffectSpace(void);
#endif

//-------------------------------------------------------
// IR
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
extern void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP EDID Switch
//-------------------------------------------------------
extern void UserAdjustDpEdidTableSwitch(BYTE ucSelectedPort);

//-------------------------------------------------------
// False Color
//-------------------------------------------------------
#if(_FALSE_COLOR_SUPPORT == _ON)
extern void UserAdjustFalseColorUserDefine(EnumSelRegion enumSelRegion, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext);
extern void UserAdjustFalseColor(EnumSelRegion enumSelRegion, BYTE ucMode);
#endif

//-------------------------------------------------------
// PIP Sub config
//-------------------------------------------------------
#if(_PIP_DISPLAY_SUPPORT == _ON)

#if(_PIP_BLENDING_SUPPORT == _ON)
extern void UserAdjustPipTransparency(void);
#endif

#endif

extern void UserAdjustOsdSelectRegionColorProc(void);
extern void UserAdjustDisplayMode(void);
extern void UserAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);

#if(_2P_DISPLAY_SUPPORT == _ON)
extern void UserAdjustSwapInputPort(void);
#endif

extern EnumSelRegion UserAdjustConvertSystemSelectRegion(BYTE ucRegion);
extern EnumDisplayRegion UserAdjustConvertDisplayRegion(BYTE ucRegion);
extern EnumSourceSearchPort UserAdjustGetSelectRegionPort(void);
#if((_OGC_SUPPORT == _ON) || (_PCM_FUNCTION == _ON))
extern BYTE UserAdjustGetOSDSelectRegion(EnumSelRegion enumSelRegion);
#endif

#endif // End of #ifndef __USER_ADJUST__


#ifndef __USER_ADJUST_3D_GAMMA__
//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------
#if(_RGB_3D_GAMMA == _ON)
extern void UserAdjust3DGamma(BYTE uc3DGammaMode);
#endif
#endif

#ifndef __USER_ADJUST_OUTPUT_GAMMA__
//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------
#if(_GAMMA_FUNCTION == _ON)
extern void UserAdjustGamma(EnumSelRegion enumSelRegion, BYTE ucGamma);
extern void UserAdjustGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif
//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
extern void UserAdjustPCM(EnumSelRegion enumSelRegion, BYTE ucPCM);
#endif
//-------------------------------------------------------
// HDR
//-------------------------------------------------------
#if(_ULTRA_HDR_SUPPORT == _ON)
extern void UserAdjustHDR2084(EnumDisplayRegion enumDisplayRegion, EnumHDRMaxMasteringLvType enumHDRMaxMasteringLvType, EnumHDRColorMatrix enumHDRColorMatrix, bit bDarkEnhanceEnable);
#endif
#endif


#ifndef __USER_ADJUST_RGB_GAMMA__

//-------------------------------------------------------
// RGB Output Gamma
//-------------------------------------------------------
#if(_GAMMA_FUNCTION == _ON)
extern void UserAdjustRGBGamma(EnumSelRegion enumSelRegion, BYTE ucGamma);
#endif

#endif // End of #ifndef __USER_ADJUST_RGB_GAMMA__


#ifndef __USER_ADJUST_UNIFORMITY__
//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------
#if(_UNIFORMITY_SUPPORT == _ON)
extern void UserAdjustPanelUniformityMode(BYTE ucUniformity);
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterface.c
//----------------------------------------------------------------------------------------
#ifndef __USER_INTERFACE__

extern void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// INT
//-------------------------------------------------------
#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void UserInterfaceTimer0InstantAccess_EXINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void UserInterfaceTimer1InstantAccess_EXINT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
extern void UserInterfaceTimer2InstantAccess_EXINT(void);
#endif

#if(_UART_SUPPORT == _ON)
extern void UserInterfaceUartIntHandler_SERIALPORT(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE UserInterfaceGetDdcciStatus_EXINT1(void);
extern BYTE UserInterfaceGetFactoryCommand_EXINT1(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(BYTE ucOpcode);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort);
#endif

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
extern void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
extern void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif


#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
extern void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

//-------------------------------------------------------
// Wait for Panel Power Sequence Delay
//-------------------------------------------------------
extern void UserInterfaceAdjustWaitPanelT1(void);
extern void UserInterfaceAdjustWaitPanelT2(void);
extern void UserInterfaceAdjustWaitPanelT3(void);
extern void UserInterfaceAdjustWaitPanelT4(void);
extern void UserInterfaceAdjustWaitPanelT5(void);


//-------------------------------------------------------
//
//-------------------------------------------------------
void UserInterfaceUncallFunction(void);
void UserInterfaceInitial(void);

void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

//-------------------------------------------------------
// Input Information
//-------------------------------------------------------
extern EnumDisplayRegion UserInterfaceGetAutoSearchTarget(void);
extern EnumSourceSearchPort UserInterfaceGetInputPort0(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern EnumSourceSearchPort UserInterfaceGetInputPort1(void);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
extern EnumSourceSearchPort UserInterfaceGetInputPort2(void);
extern EnumSourceSearchPort UserInterfaceGetInputPort3(void);
#endif

//-------------------------------------------------------
// User Information
//-------------------------------------------------------
extern bit UserInterfaceGetLogoStatus(void);
extern bit UserInterfaceGetdNoSupportStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserInterfaceGetDclkNoSupportStatus(void);
extern bit UserInterfaceGetActiveByPassStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserInterfaceGetCableResetStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserInterfaceGetForcePSStatus(void);
extern bit UserInterfaceGetIntoPSStatus(void);
extern bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType);
extern bit UserInterfaceGetRegionAutoSearchStatus(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);
extern bit UserInterfaceGetDisplaySettingBacklightAction(void);
extern EnumColorSpace UserInterfaceGetColorFormat(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayMode UserInterfaceGetMultiDisplayMode(void);

#if(_OVERSCAN_SUPPORT == _ON)
extern bit UserInterfaceGetOverScanStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_OD_SUPPORT == _ON)
extern EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
extern void UserInterfaceUpdateDDR3PhaseData(void);
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
extern void UserInterfaceAdjustInputTiming(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion);

#if(_PIP_DISPLAY_SUPPORT == _ON)
extern StructTimingFormat UserInterfaceGetPipSubTimingFormat(void);
#endif

#if((_PBP_LR_DISPLAY_SUPPORT == _ON) && (_D_DOMAIN_PATH != _D_DOMAIN_4_PATH))
extern StructTimingFormat UserInterfaceGetPbpTimingFormat(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE UserInterfaceGetDisplayLatencyRatio(void);
extern void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

//-------------------------------------------------------
// Color
//-------------------------------------------------------
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
extern bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
extern bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization);
#endif

extern void UserInterfaceAdjustInitialColorProc(EnumDisplayMode enumDisplayMode);
extern void UserInterfaceAdjustColorProc(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceAdjustHDRColorProcInitial(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceAdjustActiveByPassColorProc(EnumDisplayRegion enumDisplayRegion);

#if(_ULTRA_VIVID_SUPPORT == _ON)
extern void UserInterfaceAdjustUltraVivid(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern void UserInterfaceAdjustHighlightWindow(EnumDBApply enumDBApply);
#endif

#if(_BORDER_WINDOW_SUPPORT == _ON)
extern void UserInterfaceAdjustBorderWindow(EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
extern code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort);
extern BYTE UserInterfaceGetSharpnessCoefBankNum(void);
extern bit UserInterfaceSharpnessBypassCheck(void);
#endif

//-------------------------------------------------------
// Osd
//-------------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void);
void UserInterfaceAdjustOsdActiveProc(EnumDisplayRegion enumDisplayRegion);
void UserInterfaceAdjustOsdResetProc(void);
void UserInterfaceAdjustOsdResetRegionProc(EnumDisplayRegion enumDisplayRegion);
void UserInterfaceAdjustOsdResumeRegionProc(EnumDisplayRegion enumDisplayRegion);


//-------------------------------------------------------
// Interface
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
extern bit UserInterfaceGetLoadModeTableDefaultStatus(void);
extern bit UserInterfaceGetFirstAutoConfigStatus(void);
extern void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);

extern bit UserInterfaceSkipAutoVpos(void);
extern bit UserInterfaceSkipAutoHpos(void);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

#if(_FREESYNC_SUPPORT == _ON)
extern bit UserInterfaceGetFREESYNCEnable(void);
#endif

#if(_DP_SUPPORT == _ON)
extern EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
extern EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);
extern EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
#endif // End of #if(_DP_SUPPORT == _ON)

//-------------------------------------------------------
// AUDIO
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioReadyToPlayStatus(void);
extern bit UserInterfaceGetAudioMuteStatus(void);
extern EnumAudioInputSource UserInterfaceGetAudioSource(void);
extern bit UserInterfaceGetAudioNonLPCMStatus(void);
extern WORD UserInterfaceGetAudioVolume(void);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

extern void UserInterfaceAdjustAudioResetProc(void);
extern void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
extern void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);
extern EnumDisplayRegion UserInterfaceGetAudioDisplayModeRegion(void);
extern EnumRegionIndex UserInterfaceGetAudioRegionIndex(void);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// RTD2014UserTypeCInterface.c
//-------------------------------------------------------
#if(_DP_TYPE_C_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_SUPPORT == _ON)
extern bit UserInterfaceTypeCGetD0PortControllerPower(void);
#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
extern bit UserInterfaceTypeCGetD1PortControllerPower(void);
#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
extern bit UserInterfaceTypeCGetD6PortControllerPower(void);
#endif

extern bit UserInterfaceTypeCPortControllerDecitionAltMode(BYTE ucInputPort);

#if(_DP_USB_HUB_SUPPORT == _ON)
extern bit UserInterfaceTypecGetUSBSupportStatus(BYTE ucInputPort);
extern void UserInterfaceTypecSwitchDPLaneByUsbHubStatus(void);
extern WORD UserInterfaceTypecUsbHubSetPollingStep(BYTE ucInputPort);

#if(_USB_HUB_USERDECITION_SUPPORT == _ON)
extern bit UserInterfaceTypecUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
extern BYTE UserInterfaceTypecUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort);
#endif

#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
extern bit UserInterfaceTypeCPortControllerConfig(BYTE ucInputPort);
#endif // End of #if(_USB_HUB_USERDECITION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)

#endif // End of #ifndef __USER_INTERFACE__

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

#if(_FREESYNC_OD_MEASURE == _ON)
extern void UserAdjustFREESYNCODMeasure(void);
#endif



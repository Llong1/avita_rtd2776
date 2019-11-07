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
// ID Code      : UserCommonInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

#define UserCommonNVRamSaveSystemData()                 UserCommonEepromSaveSystemData()
#define UserCommonNVRamRestoreSystemData()              UserCommonEepromRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadADCSetting(x)                UserCommonEepromLoadADCSetting(x)
#endif

#else

#define UserCommonNVRamSaveSystemData()                 UserCommonFlashSaveSystemData()
#define UserCommonNVRamRestoreSystemData()              UserCommonFlashRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadADCSetting(x)                UserCommonFlashLoadADCSetting(x)
#endif

#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDdcciFunction.c
//----------------------------------------------------------------------------------------
extern void UserCommonDdcciHandler(void);
extern void UserCommonDdcciMapping(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonInterface.c
//----------------------------------------------------------------------------------------
extern bit UserCommonInterfaceGetDisplaySettingBacklightAction(void);
extern void UserCommonInterfacePanelPowerAction(BYTE ucEvent);
extern void UserCommonInterfaceInitialColorProc(EnumDisplayMode enumDisplayMode);
extern void UserCommonInterfaceAdjustColorProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonInterfaceOsdActiveProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonInterfaceResetRegionProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonInterfaceResumeRegionProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonInterfaceOsdResetProc(void);
extern void UserCommonInterfaceAdjustInputTiming(EnumDisplayRegion enumDisplayRegion);
#if(_FRC_SUPPORT == _ON)
extern void UserCommonInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif
extern void UserCommonInterfaceAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonInterfaceReadyForActive(EnumDisplayRegion enumDisplayRegion);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonInterfaceAdjustADCData(void);

#if(_YPBPR_SUPPORT == _ON)
extern bit UserCommonInterfaceCheckHDTVMode(BYTE ucModeNumber);
#endif

#endif

extern bit UserCommonInterfaceCheckNoSupport(EnumDisplayRegion enumDisplayRegion);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern void UserCommonInterfaceDdcci0IntGetData_EXINT1(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern void UserCommonInterfaceDdcci1IntGetData_EXINT1(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern void UserCommonInterfaceDdcci2IntGetData_EXINT1(void);
extern void UserCommonInterfaceDdcci3IntGetData_EXINT1(void);
#endif

#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
extern bit UserCommonInterfaceGetRunDdcciCommand(void);
#endif

extern void UserCommonInterfaceOsdPowerOnInitial(void);

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonInterfaceNVRamRestoreEDID(void);
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceLoadEmbeddedEdidData(void);

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
extern void UserCommonInterfaceDpDualPortEdidTableSwitch(BYTE ucInputPort);
extern bit UserCommonInterfaceDpGetDualPortEdidSelectStatus(void);
#endif
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceHDMIMultiEdidInitial(void);
#endif


#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void UserCommonInterfaceGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_HDCP_2_2_SUPPORT == _ON)
extern void UserCommonInterfaceGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
extern void UserCommonInterfaceGetHdcp2KpubKm(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonInterfaceGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonInterfaceGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonInterfaceNVRamRestoreHDCP(void);
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

extern void UserCommonInterfaceOsdHandler(void);
extern void UserCommonInterfaceInitial(void);


//----------------------------------------------------------------------------------------
// Extern functions from UserCommonNVRamSystem.c
//----------------------------------------------------------------------------------------
extern BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType);
extern void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue);

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern void UserCommonEepromSaveSystemData(void);
#else
extern void UserCommonFlashSaveSystemData(void);
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern void UserCommonEepromRestoreSystemData(void);
#else
extern void UserCommonFlashRestoreSystemData(void);
#endif

#if((_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF) && (_VGA_SUPPORT == _ON))
extern void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat);
#else
extern void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserModeSearch.c
//----------------------------------------------------------------------------------------
#if (_VGA_SUPPORT == _ON)
extern BYTE UserCommonModeSearchModeVGA(void);
extern BYTE UserCommonModeSearchGetModeVideoType(BYTE ucIndex);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterface.c
//----------------------------------------------------------------------------------------
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
extern void UserInterfaceUncallFunction(void);
extern void UserInterfaceInitial(void);

extern void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
extern void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

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

#if(_OVERSCAN_SUPPORT == _ON)
extern bit UserInterfaceGetOverScanStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern EnumRotationType UserInterfaceGetRotationDegree(void);
extern EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE UserInterfaceGetDisplayLatencyRatio(void);
#endif

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
extern EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
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
extern void UserInterfaceAdjustUltraVivid(EnumSelRegion enumDisplayRegion, EnumDBApply enumDBApply);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern void UserInterfaceAdjustHighlightWindow(EnumDBApply enumDBApply);
#endif

#if(_BORDER_WINDOW_SUPPORT == _ON)
extern void UserInterfaceAdjustBorderWindow(EnumDBApply enumDBApply);
#endif


//-------------------------------------------------------
// Osd
//-------------------------------------------------------
extern void UserInterfaceAdjustOsdPowerOnInitial(void);
extern void UserInterfaceAdjustOsdActiveProc(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceAdjustOsdResetProc(void);
extern void UserInterfaceAdjustOsdResetRegionProc(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceAdjustOsdResumeRegionProc(EnumDisplayRegion enumDisplayRegion);


//-------------------------------------------------------
// Interfaces
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
extern bit UserInterfaceGetLoadModeTableDefaultStatus(void);
extern bit UserInterfaceGetFirstAutoConfigStatus(void);
extern void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

#if(_FREESYNC_SUPPORT == _ON)
extern bit UserInterfaceGetFREESYNCEnable(void);
#endif

#if(_DP_SUPPORT == _ON)
extern EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
extern EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
extern EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit UserInterfaceGetDpCloneOutputStatus(void);
extern EnumSourceSearchPort UserInterfaceGetDpCloneOutputUserInputPort(void);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
extern BYTE UserInterfaceGetDpSwitchSelectPort(void);
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
extern bit UserInterfaceGetDpDualDefaultPort(void);
#endif

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
extern bit UserInterfaceGetAudioDACKeepDepopState(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

extern void UserInterfaceAdjustAudioResetProc(void);
extern void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
extern void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);
extern EnumDisplayRegion UserInterfaceGetAudioDisplayModeRegion(void);
extern EnumRegionIndex UserInterfaceGetAudioRegionIndex(void);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
extern void UserInterfaceSwapExternalAudioCodecInput(bit bSwap);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortController.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_SUPPORT == _ON)

extern bit UserCommonPortControllerCheckPCEnterAltMode(BYTE ucInputPort);
extern bit UserCommonPortControllerConfig(BYTE ucInputPort);
#if(_D0_DP_TYPE_C_SUPPORT == _ON)
extern bit UserCommonPortControllerGetD0PortPower(void);
#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
extern bit UserCommonPortControllerGetD1PortPower(void);
#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
extern bit UserCommonPortControllerGetD6PortPower(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonUsbHub.c
//----------------------------------------------------------------------------------------
extern bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
extern BYTE UserCommonUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort);
extern WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort);

#endif

//----------------------------------------------------------------------------------------
// Extern functions from RTD2014UserTypecInterface.c
//----------------------------------------------------------------------------------------
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
#endif // End of #if(_USB_HUB_USERDECITION_SUPPORT == _ON)

#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
extern bit UserInterfaceTypeCPortControllerConfig(BYTE ucInputPort);
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
extern void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
extern void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserKey.c
//----------------------------------------------------------------------------------------
extern void UserInterfaceKeyHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserBoot.c
//----------------------------------------------------------------------------------------
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
extern BYTE UserInterfaceGetUserCodeLocation(void);
#endif


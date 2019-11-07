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
// ID Code      : SysInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from SysMain.c
//----------------------------------------------------------------------------------------
extern void SysStartUpCheck();
#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
extern void SysMainStartUserCode(BYTE ucBankAddress);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from SysMode.c
//----------------------------------------------------------------------------------------
extern BYTE SysModeGetModeState(void);
extern void SysModeClrModeStateChange(void);
extern void SysModeResetDisplayState(EnumDisplayRegion enumDisplayRegion);
extern void SysModeResetDataPath(BYTE ucRegionIndex);
extern void SysModeSetFreeRun(void);
extern bit SysModeGetModeStateChange(void);
extern void SysModeSetResetTarget(EnumModeAction enumResetTarget);
extern void SysModeColorSpaceConvert(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorFormat, EnumDBApply enumDBApply);
extern void SysModeSetDisplayTarget(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion SysModeGetDisplayTarget(void);
extern EnumDisplayMode SysModeGetDisplayMode(void);
#if((_OGC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_OCC_SUPPORT == _ON))
extern EnumDisplayMode SysModeGetDisplayMode_EXINT1(void);
#endif
extern void SysModeSetDisplayMode(EnumDisplayMode enumDisplayMode);

//----------------------------------------------------------------------------------------
// Extern functions from SysPower.c
//----------------------------------------------------------------------------------------
extern BYTE SysPowerGetPowerStatus(void);
extern void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus);

//----------------------------------------------------------------------------------------
// Extern functions from SysRegion.c
//----------------------------------------------------------------------------------------
extern void SysRegionUpdateInterface(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);
extern void SysRegionResetInfo(void);
extern EnumDisplayState SysRegionGetDisplayState(EnumDisplayRegion enumDisplayRegion);
extern EnumSourceTypeDef SysRegionGetSourceType(EnumDisplayRegion enumDisplayRegion);
extern EnumSourceSearchPort SysRegionGetPortType(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion SysRegionGetDisplayRegion(EnumRegionIndex enumRegionIndex);
extern BYTE SysRegionGetSourceIndex(BYTE ucRgnNum);
extern bit SysRegionCheckAllDisplayState(EnumDisplayState enumDisplayState);
extern bit SysRegionCheckUserDisplayStateChange(void);
extern bit SysRegionCheckDisplayEvent(EnumDisplayRegion enumDisplayRegion, EnumDisplayEvent enumDisplayEvent);
extern void SysRegionClearAllDisplayEvent(BYTE ucDisplayEventSet);
extern void SysRegionSetMeasureResultPointerRegion(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion SysRegionGetMeasureResultPointerRegion(void);
extern BYTE SysRegionGetDisplayStateCount(EnumDisplayState enumDisplayState);

//----------------------------------------------------------------------------------------
// Extern functions from SysSource.c
//----------------------------------------------------------------------------------------
extern BYTE SysSourceGetSourceType(void);
extern BYTE SysSourceGetInputPort(void);
extern BYTE SysSourceGetSpecificInputPort(BYTE ucIndex);
extern BYTE SysSourceGetInputPortType(BYTE ucInputPort);

extern void SysSourceSwitchInputPort(BYTE ucInputPort);
extern bit SysSourceCheckTargetTimes(BYTE ucTargetTimes);
extern void SysSourceSetScanType(BYTE ucScanType);
extern BYTE SysSourceGetScanType(void);
extern BYTE SysSourceConvertSearchPort(BYTE ucInputPort);
extern bit SysSourceGetCableDetect(BYTE ucInputPort);
extern bit SysSourceGetCableStatusChange(BYTE ucInputPort);
extern void SysSourceSetSearchPriority(EnumSourceSearchPort enumPort, EnumSourceSearchPortPriority enumSourcePriority);
extern void SysSourceSetSearchGroup(EnumSourceSearchPort enumPort, EnumSourceSearchGroup enumSourceGroup);
extern void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime);
extern void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime);
extern void SysSourceSetMultiAutoSearchTarget(EnumDisplayRegion enumDisplayRegion);

//----------------------------------------------------------------------------------------
// Extern functions from SysVGA.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern EnumDisplayRegion SysVgaGetRegion(void);
extern void SysVgaWatchDog(bit bEnable);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from SysAudio.c
//----------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)
extern EnumAudioState SysAudioGetAudioState(void);
extern void SysAudioPowerProc(EnumPowerAction enumSwitch);
extern void SysAudioMuteProc(bit bMute);
extern void SysAudioChangeAudioState(EnumAudioState enumAudioState);

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
extern BYTE SysSourceGetAudioPlaybackPort(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern void SysAudioInternalGenTestProc(bit bOn);
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern functions from SysDp.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_SUPPORT == _ON)

#if(_DP_USB_HUB_SUPPORT == _ON)
extern BYTE SysDpGetUsbHubDeviceInfo(BYTE ucInputPort);
extern bit SysDpGetUsbHubChangeFlg(BYTE ucInputPort);
#endif

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_TYPE_C_SUPPORT == _ON))
extern void SysDpTypeCSetD0LaneCount(BYTE ucTypeCLane);
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_TYPE_C_SUPPORT == _ON))
extern void SysDpTypeCSetD1LaneCount(BYTE ucTypeCLane);
#endif

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_DP_TYPE_C_SUPPORT == _ON))
extern void SysDpTypeCSetD6LaneCount(BYTE ucTypeCLane);
#endif

#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)

/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerGlobalInterface.h No.0000
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
extern void ScalerGlobalDisplayInitial(EnumDisplayMode enumDisplayMode);
extern void ScalerGlobalIRQControl(bit bEn);
extern void ScalerGlobalSetIRQControl(BYTE ucIRQControl);
extern BYTE ScalerGlobalGetIRQControl(void);
extern void ScalerGlobalRemovePortMapping(EnumSourceSearchPort enumSourceSearchPort, EnumDisplayDataPath enumDisplayDataPath);
extern void ScalerGlobalWholeChipReset(void);
extern void ScalerGlobalSetWatchDogMapping(EnumDisplayMode enumDisplayMode);
extern void ScalerGlobalWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable);
extern void ScalerGlobalCrystalClkSel(EnumClkSel enumSel);
extern void ScalerGlobalOsdInitial(void);
extern void ScalerGlobalResetProc(BYTE ucResetTarget);
extern void ScalerGlobalFirstActiveProc(BYTE ucSourceType, BYTE ucGetInputPort);
extern void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel);

extern void ScalerGlobalDoubleBufferEnable(bit bEn);
extern void ScalerGlobalIDDomainDBSetTriggerEvent(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent);
extern void ScalerGlobalDDomainDBApply(EnumDBApply enumDBApply);
extern void ScalerGlobalIDomainDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
extern void ScalerGlobalResetExtension(void);
#endif

extern bit ScalerGlobalGetDBStatus(void);

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
extern void ScalerGlobalPreventGarbageByBacklight_EXINT0(void);
#endif

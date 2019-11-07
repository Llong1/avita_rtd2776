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
// ID Code      : RL6193_Series_MHLRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHLRx0ModeMHLSetting(void);
extern void ScalerMHLRx0ModeHdmiSetting(void);
extern void ScalerMHLRx0InitialSettings(void);
extern void ScalerMHLRx0CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx0CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx0CBUSResetProc(void);
extern void ScalerMHLRx0PowerOffProc(void);
extern void ScalerMHLRx0IntHandler_EXINT0(void);
extern BYTE ScalerMHLRx0MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
extern void ScalerMHLRx0MscCheckDeviceINT(void);
extern bit ScalerMHLRx0MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx0MscRAPHandler(void);
extern bit ScalerMHLRx0PSPreDetect(void);
extern bit ScalerMHLRx0NormalPreDetect(void);

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

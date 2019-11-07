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
// ID Code      : RL6193_Series_MHLRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

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
extern void ScalerMHLRx3ModeMHLSetting(void);
extern void ScalerMHLRx3ModeHdmiSetting(void);
extern void ScalerMHLRx3InitialSettings(void);
extern void ScalerMHLRx3CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx3CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx3CBUSResetProc(void);
extern void ScalerMHLRx3PowerOffProc(void);
extern void ScalerMHLRx3IntHandler_EXINT0(void);
extern BYTE ScalerMHLRx3MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
extern void ScalerMHLRx3MscCheckDeviceINT(void);
extern bit ScalerMHLRx3MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx3MscRAPHandler(void);
extern bit ScalerMHLRx3PSPreDetect(void);
extern bit ScalerMHLRx3NormalPreDetect(void);
#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

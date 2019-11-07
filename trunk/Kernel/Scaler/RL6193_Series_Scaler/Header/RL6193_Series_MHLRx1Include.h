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
// ID Code      : RL6193_Series_MHLRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

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
void ScalerMHLRx1ModeMHLSetting(void);
void ScalerMHLRx1ModeHdmiSetting(void);
void ScalerMHLRx1InitialSettings(void);
void ScalerMHLRx1CBUSPhySwitch(bit bSelect);
void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLRx1CBUSResetProc(void);
void ScalerMHLRx1PowerOffProc(void);
void ScalerMHLRx1IntHandler_EXINT0(void);
BYTE ScalerMHLRx1MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
void ScalerMHLRx1MscCheckDeviceINT(void);
bit ScalerMHLRx1MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
bit ScalerMHLRx1MscRAPHandler(void);
bit ScalerMHLRx1PSPreDetect(void);
bit ScalerMHLRx1NormalPreDetect(void);
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

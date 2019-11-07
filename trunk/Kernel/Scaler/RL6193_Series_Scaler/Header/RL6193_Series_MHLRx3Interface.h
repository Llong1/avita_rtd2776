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
// ID Code      : RL6193_Series_MHLRx3Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMHLRx3ModeMHLSetting(void);
extern void ScalerMHLRx3ModeHdmiSetting(void);
extern void ScalerMHLRx3InitialSettings(void);
extern void ScalerMHLRx3CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx3CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx3CBUSResetProc(void);
extern void ScalerMHLRx3IntHandler_EXINT0(void);
extern void ScalerMHLRx3MscCheckDeviceINT(void);
extern bit ScalerMHLRx3MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx3MscRAPHandler(void);

#if(_MHL2_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx3MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx3PSPreDetect(void);
extern bit ScalerMHLRx3NormalPreDetect(void);
#endif  // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

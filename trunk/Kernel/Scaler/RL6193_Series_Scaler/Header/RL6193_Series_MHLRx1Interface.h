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
// ID Code      : RL6193_Series_MHLRx1Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMHLRx1ModeMHLSetting(void);
extern void ScalerMHLRx1ModeHdmiSetting(void);
extern void ScalerMHLRx1InitialSettings(void);
extern void ScalerMHLRx1CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx1CBUSResetProc(void);
extern void ScalerMHLRx1IntHandler_EXINT0(void);
extern void ScalerMHLRx1MscCheckDeviceINT(void);
extern bit ScalerMHLRx1MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx1MscRAPHandler(void);

#if(_MHL2_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx1MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx1PSPreDetect(void);
extern bit ScalerMHLRx1NormalPreDetect(void);
#endif  // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

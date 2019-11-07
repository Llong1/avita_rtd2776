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
// ID Code      : RL6193_Series_MHLRx5Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMHLRx5ModeMHLSetting(void);
extern void ScalerMHLRx5ModeHdmiSetting(void);
extern void ScalerMHLRx5InitialSettings(void);
extern void ScalerMHLRx5CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx5CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx5CBUSResetProc(void);
extern void ScalerMHLRx5IntHandler_EXINT0(void);
extern void ScalerMHLRx5MscCheckDeviceINT(void);
extern bit ScalerMHLRx5MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx5MscRAPHandler(void);

#if(_MHL2_UCP_SUPPORT == _ON)
BYTE ScalerMHLRx5MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx5PSPreDetect(void);
extern bit ScalerMHLRx5NormalPreDetect(void);
#endif  // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

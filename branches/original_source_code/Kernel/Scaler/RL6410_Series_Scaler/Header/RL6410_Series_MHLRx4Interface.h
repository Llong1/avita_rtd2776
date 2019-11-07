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
// ID Code      : RL6410_Series_MHLRx4Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMHLRx4ModeMHLSetting(void);
extern void ScalerMHLRx4ModeHdmiSetting(void);
extern void ScalerMHLRx4InitialSettings(void);
extern void ScalerMHLRx4CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx4CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx4CBUSResetProc(void);
extern void ScalerMHLRx4IntHandler_EXINT0(void);
extern void ScalerMHLRx4MscCheckDeviceINT(void);

#if(_MHL_3_0_SUPPORT == _ON)
extern void ScalerMHLRx4CheckWriteBurst(void);
#endif

extern bit ScalerMHLRx4MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx4MscRAPHandler(void);

#if(_MHL2_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx4MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx4PSPreDetect(void);
extern bit ScalerMHLRx4NormalPreDetect(void);

#endif  // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

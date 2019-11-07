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
// ID Code      : RL6410_Series_MHLRx2Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMHLRx2ModeMHLSetting(void);
extern void ScalerMHLRx2ModeHdmiSetting(void);
extern void ScalerMHLRx2InitialSettings(void);
extern void ScalerMHLRx2CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx2CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx2CBUSResetProc(void);
extern void ScalerMHLRx2IntHandler_EXINT0(void);
extern void ScalerMHLRx2MscCheckDeviceINT(void);

#if(_MHL_3_0_SUPPORT == _ON)
extern void ScalerMHLRx2CheckWriteBurst(void);
#endif

extern bit ScalerMHLRx2MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
extern bit ScalerMHLRx2MscRAPHandler(void);

#if(_MHL2_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx2MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx2PSPreDetect(void);
extern bit ScalerMHLRx2NormalPreDetect(void);

#endif  // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

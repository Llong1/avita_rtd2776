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
// ID Code      : RL6193_Series_DisplayDPTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDisplayDPTxAnalogPhyConrol(bit bEnable);
extern void ScalerDisplayDPTxPollingHotPlug(WORD usNum);
extern bit ScalerDisplayDPTxLinkSequence(void);
extern void ScalerDisplayDPTxStreamHanlder(bit bOutput);
extern void ScalerDisplayDPTxLinkSignalForceOutput(void);
extern void ScalerDisplayDPTxPowerSequenceProc(bit bLevel);
extern void ScalerDisplayDPTxPhyInitial(void);
extern void ScalerDisplayDPTxSSCSet(bit bSscEn);
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

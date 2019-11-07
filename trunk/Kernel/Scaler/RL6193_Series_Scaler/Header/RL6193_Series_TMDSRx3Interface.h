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
// ID Code      : RL6193_Series_TMDSRx3Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D3_TMDS_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerTMDSRx3IntHandler_EXINT0(void);

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern BYTE ScalerTMDSRx3TMDSScanInputPort(BYTE ucInputType);
#endif
#endif

extern bit ScalerTMDSRx3TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx3HotPlugEvent(void);

#endif

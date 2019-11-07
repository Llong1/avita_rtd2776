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
// ID Code      : RL6410_Series_TMDSRx5Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D5_TMDS_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerTMDSRx5IntHandler_EXINT0(void);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx5PSIntHandler_EXINT0(void);
extern void ScalerTMDSRx5HDMI2HPDRRIRQEnable(bit bEnable);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern BYTE ScalerTMDSRx5TMDSScanInputPort(BYTE ucInputType);
#endif

extern bit ScalerTMDSRx5TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx5HotPlugEvent(void);

#endif

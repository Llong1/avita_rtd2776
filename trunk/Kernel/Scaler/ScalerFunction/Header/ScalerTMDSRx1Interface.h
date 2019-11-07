/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerTMDSRx1Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_D1_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx1IntHandler_EXINT0(void);

#if(_D1_HDMI_SUPPORT == _ON)
extern BYTE ScalerTMDSRx1HdmiGetAVIInfo(EnumAviInfoContent enumContent);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx1PSIntHandler_EXINT0(void);
extern void ScalerTMDSRx1HDMI2HPDRRIRQEnable(bit bEnable);
#endif

#endif

extern void ScalerTMDSRx1FreqDetectDisable(void);
extern void ScalerTMDSRx1TMDSScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx1TMDSPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx1TMDSNormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerTMDSRx1TMDSScanInputPort(BYTE ucInputType);
extern bit ScalerTMDSRx1TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx1HotPlugEvent(void);
#endif

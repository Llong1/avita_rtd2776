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
// ID Code      : ScalerTMDSRx0Interface.h No.0000
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

#if(_D0_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx0IntHandler_EXINT0(void);

#if(_D0_HDMI_SUPPORT == _ON)
extern BYTE ScalerTMDSRx0HdmiGetAVIInfo(EnumAviInfoContent enumContent);

#if(_D0_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx0PSIntHandler_EXINT0(void);
extern void ScalerTMDSRx0HDMI2HPDRRIRQEnable(bit bEnable);
#endif

#endif

extern void ScalerTMDSRx0FreqDetectDisable(void);
extern void ScalerTMDSRx0TMDSScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx0TMDSPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx0TMDSNormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerTMDSRx0TMDSScanInputPort(BYTE ucInputType);
extern bit ScalerTMDSRx0TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx0HotPlugEvent(void);

#endif

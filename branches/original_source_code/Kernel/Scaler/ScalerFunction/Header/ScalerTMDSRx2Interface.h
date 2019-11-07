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
// ID Code      : ScalerTMDSRx2Interface.h No.0000
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
#if(_D2_TMDS_SUPPORT == _ON)

#if(_D2_HDMI_SUPPORT == _ON)
extern BYTE ScalerTMDSRx2HdmiGetAVIInfo(EnumAviInfoContent enumContent);
#endif

extern void ScalerTMDSRx2FreqDetectDisable(void);

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern void ScalerTMDSRx2TMDSScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx2TMDSPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx2TMDSNormalPreDetect(BYTE ucInputPort);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
extern void ScalerTMDSRx2DualDVIScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx2DualDVIPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx2DualDVINormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerTMDSRx2DualDVIScanInputPort(BYTE ucInputType);
#endif

#endif

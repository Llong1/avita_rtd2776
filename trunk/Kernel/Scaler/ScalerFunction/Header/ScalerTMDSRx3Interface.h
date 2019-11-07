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
// ID Code      : ScalerTMDSRx3Interface.h No.0000
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
#if(_D3_TMDS_SUPPORT == _ON)

#if(_D3_HDMI_SUPPORT == _ON)
extern BYTE ScalerTMDSRx3HdmiGetAVIInfo(EnumAviInfoContent enumContent);
#endif

extern void ScalerTMDSRx3FreqDetectDisable(void);

#if((_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT) && (_D3_INPUT_PORT_TYPE != _D3_NO_PORT))
extern void ScalerTMDSRx3TMDSScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx3TMDSPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx3TMDSNormalPreDetect(BYTE ucInputPort);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
extern void ScalerTMDSRx3DualDVIScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx3DualDVIPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx3DualDVINormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerTMDSRx3DualDVIScanInputPort(BYTE ucInputType);
#endif

#endif

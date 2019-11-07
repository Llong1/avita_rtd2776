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
// ID Code      : ScalerTMDSRx4Interface.h No.0000
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
#if(_D4_TMDS_SUPPORT == _ON)

#if(_D4_HDMI_SUPPORT == _ON)
extern BYTE ScalerTMDSRx4HdmiGetAVIInfo(EnumAviInfoContent enumContent);
#endif

extern void ScalerTMDSRx4FreqDetectDisable(void);


#if((_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT) && (_D4_INPUT_PORT_TYPE != _D4_NO_PORT))
extern void ScalerTMDSRx4TMDSScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx4TMDSPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx4TMDSNormalPreDetect(BYTE ucInputPort);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
extern void ScalerTMDSRx4DualDVIScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx4DualDVIPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx4DualDVINormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerTMDSRx4DualDVIScanInputPort(BYTE ucInputType);
#endif

#endif

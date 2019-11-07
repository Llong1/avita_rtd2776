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
// ID Code      : ScalerTMDSRx5Interface.h No.0000
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
#if(_D5_TMDS_SUPPORT == _ON)

#if(_D5_HDMI_SUPPORT == _ON)
extern BYTE ScalerTMDSRx5HdmiGetAVIInfo(EnumAviInfoContent enumContent);
#endif

extern void ScalerTMDSRx5FreqDetectDisable(void);

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern void ScalerTMDSRx5TMDSScanInitial(BYTE ucInputPort);
extern bit ScalerTMDSRx5TMDSPSPreDetect(BYTE ucInputPort);
extern bit ScalerTMDSRx5TMDSNormalPreDetect(BYTE ucInputPort);
#endif

#endif

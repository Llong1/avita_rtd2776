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
// ID Code      : ScalerVGATopInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Enumerations of VGATOP Waiting Events (P30_E4)
//--------------------------------------------------

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
extern void ScalerVgaTopInputInitial(void);
extern bit ScalerVgaTopModifyVsLatchEdge(bit bWait);
extern void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd);
extern void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
extern bit ScalerVgaTopHWAutoPhaseSearch(EnumAutoPhaseSearchStep enumPhaseStep, BYTE *pucPhaseResult, DWORD *pulSODMax, DWORD *pulSODMin, EnumAutoPhaseSearchSODMethod enumSODMethod, BYTE ucSODThreshold);
extern bit ScalerVgaTopAutoPhaseGetSOD(DWORD *pulSODValue);
extern bit ScalerVgaTopMeasureActiveRegion(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
extern void ScalerVgaTopDoubleBufferApply(void);
extern void ScalerVgaTopDoubleBufferEnable(bit bEn);
extern WORD ScalerVgaTopGetCaptureVStartPosition(void);
extern void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart);
extern WORD ScalerVgaTopGetCaptureVHeight(void);
extern void ScalerVgaTopSetCaptureVHeight(WORD usIVheight);
extern WORD ScalerVgaTopGetCaptureVDelay(void);
extern void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay);
extern WORD ScalerVgaTopGetCaptureHStartPosition(void);
extern void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart);
extern WORD ScalerVgaTopGetCaptureHWidth(void);
extern void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth);
extern WORD ScalerVgaTopGetCaptureHDelay(void);
extern void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay);
extern void ScalerVgaTopSetCapture(void);
extern void ScalerVgaTopModifyHsLatchEdgeDelay(void);
#endif


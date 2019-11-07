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
// ID Code      : ScalerPLLInterface.h No.0000
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
extern void ScalerPLLM2PLLPower(BYTE ucOn);
extern void ScalerPLLSetDPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange);
extern bit ScalerAPLLFastLockAdjust(WORD usCurrHTotal);
extern void ScalerPLLSetPhase(BYTE ucPhase, WORD usVfreq);

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
extern void ScalerPLLGetDDR3PhaseData(StructDDR3PhaseInfo *pstDdr3PhaseData);
#endif

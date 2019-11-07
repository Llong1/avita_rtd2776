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
// ID Code      : RL6193_Series_ColorInterface.h No.0000
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
// Panel Uniformity
#if(_UNIFORMITY_SUPPORT == _ON)
extern void ScalerColorPanelUniformityInitial(BYTE ucLUTMode);
#endif

#if(_PCM_FUNCTION == _ON)
extern void ScalerColorPCMOff(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE *pucInverseGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMAdjust(EnumSelRegion enumSelRegion, EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucPCMBankNum, WORD usLength, BYTE *pucInverseGammaTableArray, BYTE ucGammaBankNum);
#endif

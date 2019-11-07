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
// ID Code      : ScalerAutoFuncInterface.h No.0000
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
#if(_VGA_SUPPORT == _ON)
extern EnumAutoResult ScalerAutoDoWhiteBalance(EnumAutoColorType enumAutoType);
extern void ScalerAutoGetAutoColorResult(StructAdcDataType *pstAdcData);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
extern StructAdcDataType ScalerAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData);
#endif
#endif // End of #if(_VGA_SUPPORT == _ON)

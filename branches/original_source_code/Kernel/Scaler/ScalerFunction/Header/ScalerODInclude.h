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
// ID Code      : ScalerODInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_OD_SUPPORT == _ON)

#if(_FRC_SUPPORT == _ON)
#define GET_DYNAMIC_OD_STATUS()         ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) && ((GET_MEMORY_DVF_SELECT() == _2_IVF) || (GET_MEMORY_DVF_SELECT() == _2_5_IVF) || (GET_MEMORY_DVF_SELECT() == _3_IVF)))
#endif

#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_OD_SUPPORT == _ON)
extern void ScalerODEnable(EnumFunctionOnOFF enumOn);
extern BYTE ScalerODGetCompressionBitNum(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW);
#endif

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
// ID Code      : ScalerRegInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if((_DEBUG_MESSAGE_SUPPORT == _ON) || (_FACTORY_DEBUG_SUPPORT == _ON))
#define ScalerSetBit(usAddr, ucAnd, ucOr)           (*((volatile BYTE xdata *)(usAddr)) = (*((volatile BYTE xdata *)(usAddr)) & (ucAnd)) | (ucOr))
#define ScalerGetBit(usAddr, ucAnd)                 (*((volatile BYTE xdata *)(usAddr)) & (ucAnd))
#define ScalerGetByte(usAddr)                       (*((volatile BYTE xdata *)(usAddr)))
#define ScalerSetByte(usAddr, ucValue)              (*((volatile BYTE xdata *)(usAddr)) = (ucValue))
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************

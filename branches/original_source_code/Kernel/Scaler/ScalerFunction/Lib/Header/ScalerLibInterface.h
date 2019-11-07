/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define GET_DWORD_MUL_DIV(x, y, z)                        (ScalerComputeDwordMulDiv((x), (y), (z)))

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
// measure color
extern EnumAutoResult ScalerAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult);

extern DWORD ScalerComputeDwordMulDiv(DWORD ulA, DWORD ulB, DWORD ulC);


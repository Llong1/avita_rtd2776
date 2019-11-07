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
// ID Code      : RL6193_Series_ODLibInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _OD_PIXEL_PER_COMP                          4 // Number of pixels processed per compression
#define CEILING(x, y)                               (((x) % (y)) ? ((((x) / (y)) + 1) * (y)) : (x))
#define CEILING_OF_INT_DIVISION(x, y)               (((x) % (y)) ? (((x) / (y)) + 1) : ((x) / (y)))

#define GET_OD_USE_BIT()                            (g_ucMemoryODUseBit)
#define SET_OD_USE_BIT(x)                           (g_ucMemoryODUseBit = (x))
#define CLR_OD_USE_BIT()                            (g_ucMemoryODUseBit = 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMemoryODUseBit;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumFunctionOnOFF ScalerODGetStatus(void);
extern void ScalerODInitial(WORD usPanelHWidth, WORD usPanelVHeight);
extern void ScalerODHLWinSetting(EnumHLWType enumHLWType, EnumDBApply enumDBApply);

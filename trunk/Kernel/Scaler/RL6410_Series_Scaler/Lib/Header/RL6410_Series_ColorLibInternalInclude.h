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
// ID Code      : RL6410_Series_ColorLibInternalInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerFunctionCommonInclude.h"
#include "ScalerRegLibInclude.h"
#include "ScalerFunctionLibInclude.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumHLWType ScalerColorPCMGetStatus(void);
extern void ScalerColorPCMInputGammaAdjust(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMOutputGammaAdjust(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMSRGBAdjust(EnumSelRegion enumSelRegion, EnumSrgbPrecision enumSrgbPrecision, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength);

// UltraVivid
extern void ScalerColorUltraVividLoadTable(WORD usPage, BYTE *pucUltraVividSetting, WORD usUltraVividSize, BYTE ucBankNum);
extern void ScalerColorIDLTIRegionEnable(EnumSelRegion enumSelRegion, bit bOn);
extern void ScalerColorLSRRegionEnable(EnumSelRegion enumSelRegion, bit bOn);
extern void ScalerColorSHPRegionEnable(EnumSelRegion enumSelRegion, bit bOn);

// PCM
extern WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode);
extern BYTE ScalerColorPCMGetTableBank(void);


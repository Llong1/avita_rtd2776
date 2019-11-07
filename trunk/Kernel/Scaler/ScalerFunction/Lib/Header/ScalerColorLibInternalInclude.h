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
// ID Code      : ScalerColorLibInternalInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerFunctionCommonInclude.h"
#include "ScalerRegLibInclude.h"
#include "ScalerNVRamLibInclude.h"
#include "ScalerLibInclude.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _GAMMA_WRITE_TO_SRAM                                    0
#define _GAMMA_WRITE_TO_LATCH                                   1


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// DCC
extern void ScalerColorDCCSetMeasureRegion(EnumHLWType enumHLWType);
extern void ScalerColorDCCNormalizeFactorAdjust(EnumSelRegion enumDCCMeasureRegion);

// Others
extern void ScalerColorHLWAdjustSetSel(EnumHLWIPSel enumIPSel, EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);

// Output Gamma
extern void ScalerColorOutputGammaChannelCtrl(WORD usPage, BYTE ucColorChannel, WORD usOffset, bit bLocation);
extern void ScalerColorGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn);

// Global Hue/Sat
extern SWORD ScalerColorSRGBCosine(SWORD shDegree);
extern SWORD ScalerColorSRGBSine(SWORD shDegree);
extern void ScalerColorSRGBMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SWORD(*ppshArrayC)[3]);
extern bit ScalerColorSRGBAdjust(EnumSelRegion enumSelRegion, BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);
extern void ScalerColorSRGBCtsSwap(EnumFunctionOnOFF enumOn);

// ICM
extern void ScalerColorSCMAdjust(EnumSelRegion enumSelRegion, BYTE ucAdjustOption1, BYTE ucAdjustOption2);

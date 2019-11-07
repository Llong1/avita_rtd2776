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
// ID Code      : RL6410_Series_ColorLibInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
// Color Sampling
extern void ScalerColor420To422D2Enable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422D3Enable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422D2Setting(WORD usHStart, WORD usHWidth);
extern void ScalerColor420To422D3Setting(WORD usHStart, WORD usHWidth);

extern void ScalerColorPCMInputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPCMLoadTable(EnumSelRegion enumSelRegion, EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength);
//extern void ScalerColorPCMGammaRegionEnable(EnumDBApply enumDBApply, bit bOn);
extern EnumHLWType ScalerColorPCMGetStatus(void);
extern void ScalerColorPCMInputGammaLoadTable(BYTE ucSelect);
extern void ScalerColorPCMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorPCMSePCMMode(EnumSelRegion enumSelRegion, EnumPCMModeSelect enumPCMModeSelect);
extern void ScalerColorPCMSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorPCMSRGBRegionEnable(EnumDBApply enumDBApply, bit bOn);

extern void ScalerColorHLWIDLTILSRAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);

// UltraVivid SHP
extern void ScalerColorSHPHStartAdjust(EnumDisplayDataPath enumDisplayDataPath);

// Six Color ICM
extern void ScalerColorSixColorInitialDell(EnumSelRegion enumSelRegion);
extern void ScalerColorSixColorAdjustDell(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);


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
// ID Code      : RL6193_Series_ColorLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
// Color Conversion
extern void ScalerColorSpaceConvert(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
extern void ScalerColorSpaceConvertUltraVividSupport(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
extern void ScalerColorMdomainForceYUV(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);

extern void ScalerColorBRICTSRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

extern void ScalerColorPanelUniformityAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode);
extern EnumSelRegion ScalerColorPCMCheckPCMRegion(EnumSelRegion enumSelRegion);
extern void ScalerColorPCMGammaRegionEnable(EnumDBApply enumDBApply, bit bOn);
extern EnumHLWType ScalerColorPCMGetStatus(void);

// PCM
extern void ScalerColorPCMInputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPCMInputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMInputGammaLoadTable(BYTE ucSelect);
extern void ScalerColorPCMOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorPCMSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorPCMSRGBAdjust(EnumSrgbPrecision enumSrgbPrecision, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength);
extern void ScalerColorPCMSRGBRegionEnable(EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorRGB3DGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorHLWPCMAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorUltraVividRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorUltraVividAdjust(EnumSelRegion enumSelRegion, BYTE code *pucUltraVividSetting, BYTE ucBankNum);

extern void ScalerColorIDitherTableSelect(EnumSelRegion enumSelRegion, BYTE ucColorDepth);

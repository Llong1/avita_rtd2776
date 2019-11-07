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
// ID Code      : ScalerColorLibInclude.h No.0000
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
// Color Conversion
extern EnumColorSpace ScalerColorGetColorSpace(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerColorGetColorSpaceRGB(EnumColorSpace enumColorSpace);
extern void ScalerColorSpaceLoadYuv2RgbTable(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorSpace, bit bUltraVividSupport);

// DDither
extern void ScalerColorDDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadSeqTable(BYTE code *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadTempoTable(BYTE code *pucTempoTable, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadSetting(DWORD ulSettingOption);

// Digital Filter
extern void ScalerColorDigitalFilterNSmearAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterNRDisableAdjust(void);
extern void ScalerColorDigitalFilterPSmearAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterNRingAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterPRingAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterExtensionAdjust(void);

// Highlight Window
extern void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void ScalerColorHLWDDomainEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorHLWIDLTILSREnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void ScalerColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply);

// DCC
extern void ScalerColorDCCSetMeasureRegion(EnumHLWType enumHLWType);

// IDither
extern void ScalerColorIDitherLoadDitherTable(WORD usPage, BYTE code *pucDitherTable, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadSeqTable(WORD usPage, BYTE code *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadTemporalTable(WORD usPage, BYTE code *pucTempoTable, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadSetting(WORD usPage, WORD usAdjustOption);

// ICM
extern void ScalerColorICMUVOffsetLoadTable(WORD usPage, BYTE code *pucICMTable, BYTE ucBankNum);
extern void ScalerColorICMBRILoadTable(WORD usPage, BYTE code *pucICMTable, BYTE ucBankNum);
extern void ScalerColorICMAdjust(EnumSelRegion enumSelRegion, BYTE ucAdjustOption1, BYTE ucAdjustOption2);
extern void ScalerColorSixColorAdjustNormal(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
extern void ScalerColorSixColorInitialNormal(EnumSelRegion enumSelRegion);

// For Color Conversion
extern bit ScalerColorUltraVividGetStatus(EnumSelRegion enumSelRegion);

// PCM
extern void ScalerColorSRGBSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorSRGBSetGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shDeltaHue, WORD usDeltaSat);
extern void ScalerColorSRGBRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);  // Mask

// OG
extern void ScalerColorOutputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorOutputGammaAdjust(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorOutputGammaAdjustSector(EnumSelRegion enumSelRegion, EnumGammaChannel enumChannel, BYTE *pucGammaTableArray, WORD usStartAddr, WORD usLength, BYTE ucBankNum);
extern void ScalerColorGammaSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

// Color Depth
extern BYTE ScalerColorGetColorDepth(EnumSourceSearchPort enumSourceSearchPort);

// Scaling
extern bit ScalerColorScalingByPassTableSel(EnumSelRegion enumSelRegion);

// Output Gamma
extern void ScalerColorOutputGammaChannelCtrl(WORD usPage, BYTE ucColorChannel, WORD usOffset, bit bLocation);
extern void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn);

// False Color
extern void ScalerColorContrastEnable(EnumFunctionOnOFF enumOn);
extern bit ScalerColorSRGBAdjust(EnumSelRegion enumSelRegion, BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);
extern void ScalerColorContrastAdjust(EnumSelRegion enumSelRegion, WORD *pusData);

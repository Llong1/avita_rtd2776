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
// ID Code      : ScalerColorLibInterface.h No.0000
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
// Brightness & Contrast
extern void ScalerColorBrightnessEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorContrastEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorBrightnessAdjust(EnumSelRegion enumSelRegion, WORD *pusData);
extern void ScalerColorContrastAdjust(EnumSelRegion enumSelRegion, WORD *pusData);

// Color Sampling
extern void ScalerColor422To444(EnumSourceSearchPort enumSourceSearchPort, EnumSelRegion enumSelRegion);

// Color Conversion
extern void ScalerColorSpaceConvertIDomainEnable(EnumSelRegion enumSelRegion, bit bOn);
extern void ScalerColorSpaceConvertDDomainEnable(EnumSelRegion enumSelRegion, bit bOn);
extern EnumColorSpace ScalerColorGetColorSpace(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerColorGetColorSpaceRGB(EnumColorSpace enumColorSpace);
extern void ScalerColorSetRGBLimitRange(EnumSourceSearchPort enumSourceSearchPort, bit bRGBLimitRange);
extern EnumColorRGBQuantization ScalerColorGetRGBQuantizationRange(EnumSourceSearchPort enumSourceSearchPort);
extern EnumColorimetry ScalerColorGetColorimetry(EnumSourceSearchPort enumSourceSearchPort);
extern EnumColorimetryExt ScalerColorGetExtColorimetry(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerColorSetYCCFullRange(EnumSourceSearchPort enumSourceSearchPort, bit bYCCFullRange);
extern EnumColorYCCQuantization ScalerColorGetYCCQuantizationRange(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerColorSetColorimetry(EnumSourceSearchPort enumSourceSearchPort, bit bHDTVMode);
extern void ScalerColorSpaceConvertLoadTable(EnumSelRegion enumSelRegion);

// DCC
extern void ScalerColorDCCEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorDCCAdjust(EnumSelRegion enumSelRegion, BYTE code *pucDccTable, BYTE ucBankAddress);
extern void ScalerColorSetDCCAutoModeRegion(EnumSelRegion enumDCCAutoModeRegion);
extern void ScalerColorDCCNormalizeFactorAdjust(EnumSelRegion enumDCCMeasureRegion);
extern void ScalerColorDCCHistoSetting(void);
extern void ScalerColorSetDCCHistoMeasureRegion(EnumSelRegion enumDCCHistoMeasureRegion);
extern void ScalerColorDCCGetHistoInfo(BYTE *pucReadArray);
extern bit ScalerColorDCCGetDataReadyStatus(void);
extern void ScalerColorDCCClrDataReadyStatus(void);

// DCR
extern void ScalerColorDCREnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorDCRAdjust(WORD usThreshold1, WORD usThreshold2, EnumDCRMeasureSel enumDCRMeasureSel);
extern DWORD ScalerColorDCRReadResult(EnumDCRAdjOption enumDCRReadOption);
extern bit ScalerColorDCRGetDataReadyStatus(void);
extern void ScalerColorDCRClrDataReadyStatus(void);
extern WORD ScalerColorDCRGetAverage(EnumDCRAdjOption enumDCRReadOption, DWORD ulDivider);
extern DWORD ScalerColorDCRGetMeasureRegionSize(EnumSelRegion enumDCRMeasureRegion);
extern void ScalerColorDCRDataRefreshControl(bit bMode);

// DDither
extern void ScalerColorDDitherEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorDDitherAdvanceSettingAdjust(BYTE code *pucReAlignTable, BYTE code *pucReAlignTempoTable, BYTE code *pucLsbTable, BYTE code *pucAdvanceSettingTable, BYTE ucBankAddress);

// Digital Filter
extern void ScalerColorDigitalFilterEnhancePhaseAdjust(BYTE *pucBGRGain);
extern void ScalerColorDigitalFilterEnable(EnumFunctionOnOFF enumOn);

// Highlight Window
extern void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void ScalerColorHLWDDomainEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void ScalerColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply);

extern void ScalerColorDCCRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorDCCSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorDCRSetMeasureRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorHLWOutputGammaAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWIAPSGainAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorIAPSGainSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorICMSCMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void ScalerColorICMSCMSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorHLWDCCAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWICMAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWPanelUniformityAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWRGB3DGammaAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);

// IAPSGain
extern void ScalerColorIAPSGainEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorIAPSGainValueAdjust(EnumSelRegion enumSelRegion, WORD usGainValue);
extern void ScalerColorIAPSGainSoftClampAdjust(EnumSelRegion enumSelRegion, BYTE ucSoftClampFac);

// ICM
extern void ScalerColorICMEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorSCMLoadTable(EnumSelRegion enumSelRegion, BYTE code *pucSCMTable, BYTE ucBankNum);

// IDither
extern void ScalerColorIDitherEnable(EnumFunctionOnOFF enumOn);

// Output Gamma
extern void ScalerColorOutputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorOutputGammaAdjust(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorOutputGammaAdjustSector(EnumSelRegion enumSelRegion, EnumGammaChannel enumChannel, BYTE *pucGammaTableArray, WORD usStartAddr, WORD usLength, BYTE ucBankNum);
extern void ScalerColorGammaSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

// Panel Uniformity
extern void ScalerColorPanelUniformityEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPanelUniformityRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

// Ringing Filter
extern void ScalerColorRingingFilterOff(void);
extern void ScalerColorRingingFilterAdjust(BYTE *pucOffsetCoef);

// RGB 3D Gamma
extern void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColor3DGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

// SRGB
extern void ScalerColorSRGBEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorSRGBSetGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shDeltaHue, WORD usDeltaSat);
extern void ScalerColorSRGBSetEffectiveRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorSRGBRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern bit ScalerColorSRGBAdjust(EnumSelRegion enumSelRegion, BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);
extern void ScalerColorSRGBCtsSwap(EnumFunctionOnOFF enumOn);

// UltraVivid
extern void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff);
extern void ScalerColorUltraVividInitial(void);

// Color Depth
extern BYTE ScalerColorGetColorDepth(EnumSourceSearchPort enumSourceSearchPort);

// Scale Down Mask
extern void ScalerColorSetScalingDownMaskLSB(EnumInputDataPath enumInputDataPath, EnumSourceSearchPort enumSourceSearchPort);

// PIPBlending
extern void ScalerColorPIPBlendingLevelAdjust(WORD usLevel, EnumDBApply enumDBApply);

// Border Window
extern void ScalerColorBorderPositionAdjust(EnumBorderWin enumBorderWin, WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
extern void ScalerColorBorderAdjust(EnumBorderWin enumBorderWin, BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void ScalerColorBorderEnable(EnumBorderWin enumBorderWin, bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply);

// Scaling
extern bit ScalerColorScalingByPassTableSel(EnumSelRegion enumSelRegion);

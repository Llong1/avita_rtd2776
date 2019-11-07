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
// ID Code      : ScalerColorInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
// DDither
#if(_D_DITHER_SUPPORT == _ON)
extern void ScalerColorDDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress);
#endif

// Digital Filter
#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
extern void ScalerColorDigitalFilterAdjust(void);
#endif
#endif

// Highlight Window
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
extern void ScalerColorHLWEnable(EnumFunctionOnOFF enumOn, EnumDBApply enumDBApply);
extern void ScalerColorHLWSetting(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

// IDither
#if(_I_DITHER_SUPPORT == _ON)
extern void ScalerColorIDitherAdjust(EnumIDitherConvType enumIDitherConvType, BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress);
#endif

// DCR
#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
extern void ScalerColorDCRSetSource(void);
#endif

// ICM
#if(_ICM_SUPPORT == _ON)
extern void ScalerColorICMLoadTable(EnumSelRegion enumSelRegion, BYTE code *pucICMTable, BYTE ucBankNum);
#endif

// Six Color ICM
#if(_SIX_COLOR_SUPPORT == _ON)
extern void ScalerColorSixColorInitial(EnumSelRegion enumSelRegion);
extern void ScalerColorSixColorAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
#endif


#if(_PCM_FUNCTION == _ON)
extern void ScalerColorPCMSetHueSat(WORD usOSDHue, WORD usOSDInverHue, WORD usOSDSat, WORD usOSDInverseSat);
#endif

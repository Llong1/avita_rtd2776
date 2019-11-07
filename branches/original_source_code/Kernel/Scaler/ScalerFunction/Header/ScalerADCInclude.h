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
// ID Code      : ScalerADCInclude.h No.0000
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

extern void ScalerADCBandgap(bit bSelect);

#if(_VGA_SUPPORT == _ON)
extern void ScalerADCOutputClkSetting(void);
extern void ScalerADCPowerSetting(void);
extern void ScalerADCBiasCurrentSetting(void);
extern void ScalerADCGainAdjust(BYTE *pucGainMSB, BYTE *pucGainLSB);
extern void ScalerADCOffsetAdjust(BYTE *pucOffsetMSB, BYTE *pucOffsetLSB);
extern void ScalerADCClampMode(EnumColorSpace enumColorFormat);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
extern bit ScalerADCGetClampToTopStatus(void);
#endif

extern void ScalerADCBandWidthSetting(DWORD ulAdcClock);
extern void ScalerADCDCRestoreEn(bit bEn);
extern void ScalerADCSOGClampEn(bit bEn);
extern void ScalerADCSchmittTriggerSetting(void);
#endif // End of #if(_VGA_SUPPORT == _ON)


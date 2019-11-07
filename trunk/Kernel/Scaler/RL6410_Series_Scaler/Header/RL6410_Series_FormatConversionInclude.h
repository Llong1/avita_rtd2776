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
// ID Code      : RL6410_Series_FormatConversionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _DATA_PATH_SPEED_LIMIT                       (3000) // Unit: 0.1MHz


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FC_SOURCE_SST = 0x00,
    _FC_SOURCE_V8 = _BIT0,
    _FC_SOURCE_ADC = _BIT1,
    _FC_SOURCE_D0 = (_BIT1 | _BIT0),
    _FC_SOURCE_D1 = _BIT2,
    _FC_SOURCE_D2 = (_BIT2 | _BIT0),
    _FC_SOURCE_D3 = (_BIT2 | _BIT1),
    _FC_SOURCE_D4 = (_BIT2 | _BIT1 | _BIT0),
    _FC_SOURCE_D5 = _BIT3,
    _FC_SOURCE_DUAL_DVI = (_BIT3 | _BIT0),
    _FC_SOURCE_NONE = 0xFF,
} EnumFormatConversionSourceType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort, EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvFinalSetting(EnumSourceSearchPort enumSourceSearchPort, EnumInputDataPath enumInputDataPath, bit bWait);
extern void ScalerFmtCnvSetSourceType(EnumInputDataPath enumInputDataPath, EnumFormatConversionSourceType enumFormatConversionSourceType);


extern void ScalerFmtCnvFtoPControl(EnumInputDataPath enumInputDataPath, bit bEnable);
extern bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvSetBackgroundColor(EnumInputDataPath enumInputDataPath);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
extern void ScalerFmtCnvFBSetOutputFormat(WORD usHwidth, BYTE ucHstart, BYTE ucHSwidth);
#endif

#if(_HDMI_2_0_SUPPORT == _ON)

extern void ScalerFmtCnv420To422FinalSetting(EnumSourceSearchPort enumSourceSearchPort);

#if(_D2_HDMI_2_0_SUPPORT == _ON)
extern void ScalerFmtCnv420To422D2InitialSetting(void);
extern bit ScalerFmtCnv420To422D2GetStatus(void);
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
extern void ScalerFmtCnv420To422D3InitialSetting(void);
extern bit ScalerFmtCnv420To422D3GetStatus(void);
#endif

#endif


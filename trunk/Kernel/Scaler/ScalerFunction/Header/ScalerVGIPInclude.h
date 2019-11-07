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
// ID Code      : ScalerVGIPInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of VGIP IH Capture Start Min Value
//--------------------------------------------------
#if(_FORMAT_CONVERSION_SUPPORT == _ON)

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _VGIP_IH_CAPTURE_MIN_VALUE                  (20)
#define _VGIP_IV_CAPTURE_MIN_VALUE                  (8)
#else
#define _VGIP_IH_CAPTURE_MIN_VALUE                  ((ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE) ? 20 : 10)
#define _VGIP_IV_CAPTURE_MIN_VALUE                  ((ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE) ? 8 : 4)
#endif

#else

#define _VGIP_IH_CAPTURE_MIN_VALUE                  (10)
#define _VGIP_IV_CAPTURE_MIN_VALUE                  (4)

#endif // End of #if(_FORMAT_CONVERSION_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of VGIP IV Capture Start Max Value
//--------------------------------------------------
#define _VGIP_IV_CAPTURE_MAX_VALUE                  240

//--------------------------------------------------
// Definitions of VGIP IHDelay Max Value
//--------------------------------------------------
#define _VGIP_IH_DELAY_MAX_VALUE                    1023

//--------------------------------------------------
// Definitions of VGIP Input Path
//--------------------------------------------------
#define GET_VGIP_INPUT_PATH()                       (g_enumVgipInputPath)
#define CHK_VGIP_INPUT_PATH(x)                      ((g_enumVgipInputPath & (x)) == (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

enum MeasureFieldDetModeDef
{
    _MEASURE_FIELD_DET_LINE_COUNT = 0,
    _MEASURE_FIELD_DET_VS_POS,
};


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumInputDataPath g_enumVgipInputPath;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgipSetInputPath(EnumInputDataPath enumVgipInputPath);

extern void ScalerVgipCaptureEnable(bit bEnable);
extern void ScalerVgipInputInitial(EnumSourceTypeDef enumSourceType);
extern void ScalerVgipModifyPolarity(EnumSourceTypeDef enumSourceType);

extern WORD ScalerVgipGetCaptureHStartPosition(void);
extern void ScalerVgipSetCaptureHStartPosition(WORD usIHstart);

extern void ScalerVgipSetCaptureHWidth(WORD usIHwidth);

extern WORD ScalerVgipGetCaptureHDelay(void);
extern void ScalerVgipSetCaptureHDelay(WORD usIHSDelay);

extern void ScalerVgipVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerVgipSetDigitalCaptureStatus(bit bEnable);
extern bit ScalerVgipGetDigitalCaptureStatus(void);


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
// ID Code      : ScalerAutoFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_AUTOFUNC__

#include "ScalerFunctionInclude.h"

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_YPBPR_SUPPORT == _ON)
#define _AUTO_Y_MAX_LEVEL                        (235)
#define _AUTO_PBPR_MAX_LEVEL                     (240)
#define GET_TUNE_YPBPR_STATUS()                  (ScalerGetBit(P0_CF_ADC_CTL_RED, _BIT7) == _BIT7)
#endif

#define _DEFAULT_GAIN                            (0xFF)
#define _DEFAULT_OFFSET                          (0x40)
#define _AUTO_RGB_MAX_LEVEL                      (255)

#define _ADC_MAXIMUM_TOLERANCE                   (60)
#define _BLACK_LEVEL_THRESHOLD                   (32)
#define _USER_ADJUST_OFFSET_RANGE                (5)

#if(_PANEL_ADC_OFFSET_BIAS < 0)
#undef _PANEL_ADC_OFFSET_BIAS
#define _PANEL_ADC_OFFSET_BIAS                   (0)
#elif(_PANEL_ADC_OFFSET_BIAS > _USER_ADJUST_OFFSET_RANGE)
#undef _PANEL_ADC_OFFSET_BIAS
#define _PANEL_ADC_OFFSET_BIAS                   (_USER_ADJUST_OFFSET_RANGE)
#endif

#define GET_AUTO_RESULT_WORD2()                  (ScalerGetWord(P30_D4_VGATOP_AUTO_PHASE_3))
#define GET_AUTO_RESULT_WORD1()                  (ScalerGetWord(P30_D5_VGATOP_AUTO_PHASE_2))
#define GET_AUTO_RESULT_WORD0()                  (ScalerGetWord(P30_D6_VGATOP_AUTO_PHASE_1))
#define GET_AUTO_RESULT_MAX()                    (ScalerGetByte(P30_D7_VGATOP_AUTO_PHASE_0))
#define GET_AUTO_RESULT_MIN()                    (ScalerGetByte(P30_D7_VGATOP_AUTO_PHASE_0) ^ 0xFF)
#define GET_AUTO_ADC_GAIN()                      (ScalerGetByte((P0_C2_ADC_GAI_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)))))
#define GET_AUTO_ADC_OFFSET()                    (ScalerGetByte((P0_C5_ADC_OFF_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)))))
#define SET_AUTO_ADC_GAIN(ucValue)               (ScalerSetByte((P0_C2_ADC_GAI_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0))), (ucValue)))
#define SET_AUTO_ADC_OFFSET(ucValue)             (ScalerSetByte((P0_C5_ADC_OFF_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0))), (ucValue)))
#define SET_AUTO_ADC_CHANNEL(ucColor)            (ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), (((ucColor) == _AUTO_BLUE_CHANNEL) ? 0 : (((ucColor) == _AUTO_GREEN_CHANNEL) ? 1 : 2))))
#define SET_AUTO_ADC_NEXT_CHANNEL()              (ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), ((ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0)) + 1) % 3)))

//--------------------------------------------------
// Definitions of Internal Auto Color
//--------------------------------------------------
#if(_ADC_SELF_CALIBRATION == _ON)

#define GET_CALIBRATION_STATUS()                 (ScalerGetBit(P0_D2_ADC_GAIN_CALI, _BIT4) == _BIT4)

#if((_SELF_CALIBRATION_CLK > 220) || (_SELF_CALIBRATION_CLK < 15))
#undef _SELF_CALIBRATION_CLK
#define _SELF_CALIBRATION_CLK                    (148) // MHz
#endif

#define _SELF_CALIBRATION_HTOTAL                 (((DWORD)_PANEL_DH_TOTAL * _SELF_CALIBRATION_CLK) / (_PANEL_PIXEL_CLOCK_KHZ / 1000)) // pixels
#define _SELF_CALIBRATION_HFREQ                  ((WORD)((DWORD)_PANEL_PIXEL_CLOCK_KHZ * 10 / _PANEL_DH_TOTAL)) // 0.1 KHz
#endif

//--------------------------------------------------
// Definitions of known white area
//--------------------------------------------------
#ifndef _AUTO_CUSTOM_WHITE_HSTART
#define _AUTO_CUSTOM_WHITE_HSTART                (ScalerVgaTopGetCaptureHDelay() + ScalerVgaTopGetCaptureHStartPosition() + GET_INPUT_TIMING_HWIDTH() / 2)
#endif

#ifndef _AUTO_CUSTOM_WHITE_VSTART
#define _AUTO_CUSTOM_WHITE_VSTART                (ScalerVgaTopGetCaptureVDelay() + ScalerVgaTopGetCaptureVStartPosition() + GET_INPUT_TIMING_VHEIGHT() / 2)
#endif

#ifndef _AUTO_CUSTOM_WHITE_HEND
#define _AUTO_CUSTOM_WHITE_HEND                  (_AUTO_CUSTOM_WHITE_HSTART + 0x0F)
#endif

#ifndef _AUTO_CUSTOM_WHITE_VEND
#define _AUTO_CUSTOM_WHITE_VEND                  (_AUTO_CUSTOM_WHITE_VSTART + 0x0F)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Definitions of stages in auto-color process
//--------------------------------------------------
typedef enum
{
    _AUTO_COLOR_TUNING = 0x00,
    _AUTO_COLOR_STAGE1,
    _AUTO_COLOR_STAGE2,
    _AUTO_COLOR_COMPENSTE,
    _AUTO_COLOR_END,
} EnumAutoColorTuningStage;

//--------------------------------------------------
// Definitions image auto-function boundary setting
//--------------------------------------------------
typedef enum
{
    _MEASURE_ACTIVE_REGION = 0x00,
    _MEASURE_PORCH_REGION,
    _MEASURE_MANUAL_REGION,
} EnumMeasureBoundary;


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumAutoResult ScalerAutoDoWhiteBalance(EnumAutoColorType enumAutoType);
EnumAutoResult ScalerAutoBalanceHandler(EnumAutoColorType enumAutoType);
void ScalerAutoInitializeAutoColor(EnumAutoColorType enumAutoType);
EnumAutoResult ScalerAutoUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio);
EnumAutoResult ScalerAutoUpdateAdcGainOnly(BYTE ucGainBias, BYTE ucStepRatio);
EnumAutoResult ScalerAutoCompensateRGB(EnumAutoColorType enumAutoType);
EnumAutoResult ScalerAutoHardwareAbl(BYTE ucTarget, BYTE ucFrameCount);
BYTE ScalerAutoConvertAdcGainStep(BYTE ucGain, BYTE ucTarget, BYTE ucCurrent);
EnumAutoResult ScalerAutoCompensateChannel(BYTE ucColor, EnumAutoColorType enumAutoType);
EnumAutoResult ScalerAutoCompensateOffset(BYTE ucColor);
void ScalerAutoSetBoundary(EnumMeasureBoundary enumBoundary);
EnumAutoResult ScalerAutoCompareMeasure(EnumMeasureType enumType);
EnumAutoResult ScalerAutoAccumulationMeasure(EnumMeasureType enumType, BYTE ucThreshold);
EnumAutoResult ScalerAutoMainToneMeasure(BYTE ucStartLevel, BYTE *pucMainTone);
void ScalerAutoGetAutoColorResult(StructAdcDataType *pstAdcData);

#if(_YPBPR_SUPPORT == _ON)

#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE)
EnumAutoResult ScalerAutoCompensateYPbPr(EnumAutoColorType enumAutoType);
#endif

#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA)
StructAdcDataType ScalerAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData);
#endif

#endif // End of #if(_YPBPR_SUPPORT == _ON)

#if(_ADC_SELF_CALIBRATION == _ON)
EnumAutoResult ScalerAutoUpdateAdcGainCalibrationRGB(BYTE ucGainBias, BYTE ucStepRatio);
EnumAutoResult ScalerAutoCompensateCalibrationRGB(EnumAutoColorType enumAutoType);
void ScalerAutoInitializeCalibration(void);
void ScalerAutoResetCalibration(void);
EnumAutoResult ScalerAutoAblMeasure(void);
#endif

EnumAutoResult ScalerAutoCustomUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio);
EnumAutoResult ScalerAutoCustomUpdateAdcGainChannel(BYTE ucColor, BYTE ucGainBias, BYTE ucStepRatio);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : ADC AutoWhiteBalance
// Input Value  : enumAutoType -> auto color for RGB / YPbPr / Self-calibration
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoDoWhiteBalance(EnumAutoColorType enumAutoType)
{
    EnumAutoResult enumResult = 0;
    BYTE ucAdcSwapStatus = 0;
    BYTE ucClampEnd = 0;

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
    // For clamp-to-top case, do nothing.
    if(ScalerADCGetClampToTopStatus() == _TRUE)
    {
        return _AUTO_SUCCESS;
    }
#endif

#if(_VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT == _ON)
    // Disable SF bandwidth
    ScalerSetBit(P0_C8_ADC_SF_CTRL, ~_BIT5, 0x00);
#endif

    // Set measure index
    if(ScalerMeasureSetSourceResultIndex(_FC_SOURCE_ADC) == _FALSE)
    {
        return _AUTO_FAIL;
    }

    // Store ADC channel swapping, and clamp end
    ucAdcSwapStatus = ScalerGetBit(P30_A6_VGATOP_IPH_ACT_WID_H, (_BIT6 | _BIT5 | _BIT4));
    ScalerGetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, 1, &ucClampEnd, _AUTOINC);

    // Initialization for auto-color
    ScalerAutoInitializeAutoColor(enumAutoType);

    // Perform auto-color process
    enumResult = ScalerAutoBalanceHandler(enumAutoType);

#if(_ADC_SELF_CALIBRATION == _ON)
    ScalerAutoResetCalibration();
#endif

    // Restore ADC channel swapping
    ScalerSetBit(P30_A6_VGATOP_IPH_ACT_WID_H, ~(_BIT6 | _BIT5 | _BIT4), ucAdcSwapStatus);

    // Restore ADC clamp end; Disable clamp before adjustment
    ScalerSetBit(P0_48_SYNC_INVERT, ~_BIT2, 0x00);
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, ucClampEnd);
    ScalerSetBit(P0_48_SYNC_INVERT, ~_BIT2, _BIT2);

    return enumResult;
}

//--------------------------------------------------
// Description  : ADC Auto Balance for RGB / YPbPr color spaces
// Input Value  : enumAutoType: RGB / YPBPR / self-calibration
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoBalanceHandler(EnumAutoColorType enumAutoType)
{
    BYTE ucIndex = 0;
    BYTE ucTarget = 16;
    BYTE ucABLFrame = 2;
    BYTE ucGainBias = 5;
    BYTE ucStepRatio = 1;
    EnumAutoResult (*pucFunctionUpdateGain)(BYTE, BYTE);
    EnumAutoResult (*pucFunctionCompensate)(EnumAutoColorType);

    // Select functions to update gain & compensate
    switch(enumAutoType)
    {
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        case _AUTO_TUNE_YPBPR:
            pucFunctionUpdateGain = &ScalerAutoUpdateAdcGain;
            pucFunctionCompensate = &ScalerAutoCompensateYPbPr;
            break;

        case _AUTO_TUNE_YPBPR_GAIN_ONLY:
            pucFunctionUpdateGain = &ScalerAutoUpdateAdcGainOnly;
            pucFunctionCompensate = &ScalerAutoCompensateYPbPr;
            break;
#endif
#if(_ADC_SELF_CALIBRATION == _ON)
        case _AUTO_CALIBRATE_RGB:
            pucFunctionUpdateGain = &ScalerAutoUpdateAdcGainCalibrationRGB;
            pucFunctionCompensate = &ScalerAutoCompensateCalibrationRGB;
            break;
#endif

        case _AUTO_TUNE_RGB_KNOWNWHITE:
            pucFunctionUpdateGain = &ScalerAutoCustomUpdateAdcGain;
            pucFunctionCompensate = &ScalerAutoCompensateRGB;
            break;

        case _AUTO_TUNE_RGB:
            pucFunctionUpdateGain = &ScalerAutoUpdateAdcGain;
            pucFunctionCompensate = &ScalerAutoCompensateRGB;
            break;

        case _AUTO_TUNE_RGB_GAIN_ONLY:
            pucFunctionUpdateGain = &ScalerAutoUpdateAdcGainOnly;
            pucFunctionCompensate = &ScalerAutoCompensateRGB;
            break;

        default:
            return _AUTO_FAIL;
    }

    for(ucIndex = 0; ucIndex < _AUTO_COLOR_END; ++ucIndex)
    {
        if((enumAutoType != _AUTO_TUNE_RGB_GAIN_ONLY) &&
           (enumAutoType != _AUTO_TUNE_YPBPR_GAIN_ONLY))
        {
            // Adjust offset by ABL
            if(ScalerAutoHardwareAbl(ucTarget, ucABLFrame) == _AUTO_FAIL)
            {
                return _AUTO_FAIL;
            }
        }

        // Adjust gain by auto-function
        if(pucFunctionUpdateGain(ucGainBias, ucStepRatio) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }

        // Auto-tuning process control
        switch(ucIndex)
        {
            case _AUTO_COLOR_TUNING:
                if(enumAutoType != _AUTO_TUNE_YPBPR)
                {
                    ucTarget = 4;
                }
                ucGainBias = 3;
                ucABLFrame = ((enumAutoType == _AUTO_CALIBRATE_RGB) ? 2 : 1);
                break;

            case _AUTO_COLOR_STAGE1:
            case _AUTO_COLOR_STAGE2:
                // Do nothing
                break;

            case _AUTO_COLOR_COMPENSTE:
            default:
                if(pucFunctionCompensate(enumAutoType) == _AUTO_FAIL)
                {
                    return _AUTO_FAIL;
                }
                break;
        }
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Initialization for auto-color process
// Input Value  : enumAutoType: initialize type for auto-color
// Output Value : none
//--------------------------------------------------
void ScalerAutoInitializeAutoColor(EnumAutoColorType enumAutoType)
{
    BYTE ucClampEnd = 0;

#if(_ADC_SELF_CALIBRATION == _ON)
    if(enumAutoType == _AUTO_CALIBRATE_RGB)
    {
        // Enable calibration related setting
        ScalerAutoInitializeCalibration();
    }
    else
    {
        // Disable calibration voltage
        ScalerAutoResetCalibration();
    }
#endif

    // Enlarge clamp end
    PDATA_WORD(0) = (WORD)((DWORD)GET_INPUT_TIMING_HTOTAL() * GET_INPUT_TIMING_HSYNCWIDTH() / GET_SYNC_H_PERIOD());
    PDATA_WORD(1) = PDATA_WORD(0); // Record H-Sync Pulse Width
    PDATA_WORD(0) = ((GET_VGA_MODE_HSTART() - PDATA_WORD(0)) >> 1);
    ucClampEnd = ((PDATA_WORD(0) > 128) ? 128 : pData[1]);
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, ucClampEnd);

    // Load default ADC gain
    ScalerSetByte(P0_C0_ADC_GAI_RED_MSB, _DEFAULT_GAIN);
    ScalerSetByte(P0_C1_ADC_GAI_GRN_MSB, _DEFAULT_GAIN);
    ScalerSetByte(P0_C2_ADC_GAI_BLU_MSB, _DEFAULT_GAIN);
    ScalerSetBit(P0_BE_ADC_GAI_LSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Load default ADC offset
    if((enumAutoType != _AUTO_TUNE_RGB_GAIN_ONLY) && (enumAutoType != _AUTO_TUNE_YPBPR_GAIN_ONLY))
    {
        ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, _DEFAULT_OFFSET);
        ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, _DEFAULT_OFFSET);
        ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, _DEFAULT_OFFSET);
        ScalerSetBit(P0_BF_ADC_OFF_LSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P0_D3_ADC_OFF_LSB2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }

    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    // Disable ADC channel swapping
    ScalerSetBit(P30_A6_VGATOP_IPH_ACT_WID_H, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set ABL vertical start; Average 4 lines
    pData[0] = ((GET_VGA_MODE_VSTART() / 2) > 8) ? 8 : ((GET_VGA_MODE_VSTART() / 2) + 1);
    ScalerSetBit(P0_E3_AUTO_BLACK_LEVEL_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | (pData[0] & 0x1F)));

    // Select RGB or YPbPr mode; Off-line ABL; 64-pixels in each line; Clear status;
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((enumAutoType == _AUTO_TUNE_YPBPR) ? (_BIT7 | _BIT5) : (_BIT5)));

    // ABL starts at 4 pixels after the reference signal in each line
    ScalerSetByte(P0_E6_AUTO_BLACK_LEVEL_CTRL5, (PDATA_WORD(1) + ucClampEnd + 4));
    ScalerSetBit(P0_EF_AUTO_BLACK_LEVEL_CTRL8, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00); // EQ condition old mode

    // ABL old mode
    ScalerSetBit(P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Trigger status after max frame reached; Average value; HS trailing edge; EQ_MGN(0~3) = 0
    ScalerSetBit(P0_E8_AUTO_BLACK_LEVEL_CTRL7, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Max frame/field count = 7; H width x1;
    ScalerSetBit(P0_E7_AUTO_BLACK_LEVEL_CTRL6, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
}

//--------------------------------------------------
// Description  : Update ADC gain for RGB / YPbPr color space
// Input Value  : ucGainBias: bias for RGB max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio)
{
    BYTE ucGain = 0;
    BYTE ucMax = 0;
    BYTE ucIndex = 0;

    // Set to R channel for auto-balance new mode
    SET_AUTO_ADC_CHANNEL(_AUTO_RED_CHANNEL);

    // Enable image auto-balance new mode
    ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, _BIT0);

    // Enable 121-LPF
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~_BIT5, _BIT5);

    if(ScalerAutoCompareMeasure(_MEASURE_MAX) == _AUTO_FAIL)
    {
        ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, 0);
        return _AUTO_FAIL;
    }

    for(ucIndex = 0; ucIndex < 3; ++ucIndex)
    {
        ucGain = ScalerGetByte(P0_C0_ADC_GAI_RED_MSB + ucIndex);
        ucMax = ScalerGetByte(P30_D4_VGATOP_AUTO_PHASE_3 + ucIndex);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        if(GET_TUNE_YPBPR_STATUS() == _TRUE)
        {
            if(ucIndex == 1)
            {
                pData[0] = _AUTO_Y_MAX_LEVEL - ucGainBias; // Y max level
            }
            else
            {
                pData[0] = _AUTO_PBPR_MAX_LEVEL - ucGainBias; // Pb/Pr max level
            }
        }
        else
#endif
        {
            pData[0] = _AUTO_RGB_MAX_LEVEL - ucGainBias; // RGB max level
        }

        // Check source validity; More consider needed
        if(ucMax < _ADC_MAXIMUM_TOLERANCE)
        {
            return _AUTO_FAIL;
        }

        // Update ADC gain according to max level & measured maximum
        if(ucMax < pData[0])
        {
            // Calculate gain step
            pData[1] = ScalerAutoConvertAdcGainStep(ucGain, pData[0], ucMax) / ucStepRatio;

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
            if((GET_TUNE_YPBPR_STATUS() == _TRUE) && (ucIndex != 1))
            {
                // Gain step = STEP(1.75) for Pb/Pr channels
                pData[1] = (BYTE)(((WORD)pData[1] << 1) - (pData[1] >> 2));
            }
#endif
            // Minimum gain step = 1
            if(pData[1] == 0)
            {
                pData[1] = 1;
            }

            // Decrease gain with underflow check
            if(ucGain >= pData[1])
            {
                ucGain -= pData[1];
            }
            else
            {
                ucGain = 0;
            }
        }
        else
        {
            // Target value exceeded. Rewind gain.
            pData[1] = (ucMax - pData[0]);

            // Increase gain with overflow check
            if(((WORD)ucGain + pData[1]) > 0xFF)
            {
                ucGain = 0xFF;
            }
            else
            {
                ucGain += pData[1];
            }
        }

        ScalerSetByte(P0_C0_ADC_GAI_RED_MSB + ucIndex, ucGain);
    }

    // Disaable image auto-balance new mode
    ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~_BIT0, 0);

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Update ADC gain only for RGB / YPbPr color space
// Input Value  : ucGainBias: bias for RGB max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoUpdateAdcGainOnly(BYTE ucGainBias, BYTE ucStepRatio)
{
    ucStepRatio *= 2;

    if((ScalerAutoUpdateAdcGain(ucGainBias, ucStepRatio) == _AUTO_FAIL) ||
       (ScalerAutoUpdateAdcGain(ucGainBias, ucStepRatio) == _AUTO_FAIL))
    {
        return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Color compensating for RGB channels
// Input Value  : enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCompensateRGB(EnumAutoColorType enumAutoType)
{
    if(ScalerAutoCompensateChannel(_AUTO_RED_CHANNEL, enumAutoType) == _AUTO_SUCCESS)
    {
        if(ScalerAutoCompensateChannel(_AUTO_GREEN_CHANNEL, enumAutoType) == _AUTO_SUCCESS)
        {
            if(ScalerAutoCompensateChannel(_AUTO_BLUE_CHANNEL, enumAutoType) == _AUTO_SUCCESS)
            {
                return _AUTO_SUCCESS;
            }
        }
    }

    return _AUTO_FAIL;
}

//--------------------------------------------------
// Description  : Use ABL function to measure 256 pixels in the porch region and adjust offset accordingly
// Input Value  : ucTarget -> target value for ABL (1~16)
//                ucFrameCount -> total frame for ABL excution (1~7)
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoHardwareAbl(BYTE ucTarget, BYTE ucFrameCount)
{
    // Disable ABL
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~_BIT0, 0x00);

    // Set target value
    ScalerSetBit(P0_E4_AUTO_BLACK_LEVEL_CTRL3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((ucTarget - 1) << 4));

    // Reset ABL flag
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));

    // Start ABL
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~_BIT0, _BIT0);

    // For frame count = 0, wait 1 IVS
    if(ucFrameCount == 0x00)
    {
        ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
    }

    // Wait until target frame count reached
    pData[0] = 0; // Valid frame counter
    pData[1] = 0; // Total frame counter
    while(pData[0] < ucFrameCount)
    {
        if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) || ((++pData[1]) > 8))
        {
            return _AUTO_FAIL;
        }

        // Check target value status
        if((ScalerGetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, (_BIT3 | _BIT2 | _BIT1)) == (_BIT3 | _BIT2 | _BIT1)) ||
           (ScalerGetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, _BIT0) == 0x00))
        {
            break;
        }

        // Check black level saturation
        if((ScalerGetByte(P0_E9_AUTO_BLACK_LEVEL_RED_VALUE) == 0x00) || (ScalerGetByte(P0_EA_AUTO_BLACK_LEVEL_GREEN_VALUE) == 0x00) || (ScalerGetByte(P0_EB_AUTO_BLACK_LEVEL_BLUE_VALUE) == 0x00))
        {
            continue;
        }
        else
        {
            ++pData[0];
        }
    }

    // Wait additional 0.5 frame (for 60Hz)
    ScalerTimerDelayXms(9);

    // Stop ABL
    ScalerSetBit(P0_E2_AUTO_BLACK_LEVEL_CTRL1, ~_BIT0, 0x00);

    // Wait until ABL stop
    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    // Reset ADC offset LSB
    ScalerSetBit(P0_BF_ADC_OFF_LSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Further offset adjustment is needed only for RGB
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
    if(GET_TUNE_YPBPR_STATUS() == _FALSE)
#endif
    {
        --ucTarget;
        ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, (ScalerGetByte(P0_C3_ADC_OFF_RED_MSB) + ucTarget));
        ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, (ScalerGetByte(P0_C5_ADC_OFF_BLU_MSB) + ucTarget));
        ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, (ScalerGetByte(P0_C4_ADC_OFF_GRN_MSB) + ucTarget));
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Calculate ADC gain/offset according to SHA gain
// Input Value  : ucGain    -> ADC gain value
//                ucTarget  -> target level
//                ucCurrent -> measured current status
// Output Value : converted gain step
//--------------------------------------------------
BYTE ScalerAutoConvertAdcGainStep(BYTE ucGain, BYTE ucTarget, BYTE ucCurrent)
{
    BYTE ucResult = 0;

    if(ucTarget > ucCurrent)
    {
        ucResult = (BYTE)(((DWORD)(ucTarget - ucCurrent) * ((WORD)ucGain + 252)) / ucTarget);
    }

    return ucResult;
}

//--------------------------------------------------
// Description  : Color compensation for a particular ADC channel
// Input Value  : ucColor -> select a color channel
//                enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCompensateChannel(BYTE ucColor, EnumAutoColorType enumAutoType)
{
    BYTE ucMainTone = 0;
    BYTE ucGain = 0;

    // Set channel for image auto-function
    SET_AUTO_ADC_CHANNEL(ucColor);
    ucGain = GET_AUTO_ADC_GAIN();

    // Measure main-tone for max
    if(ScalerAutoMainToneMeasure(255, &ucMainTone) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    if(enumAutoType == _AUTO_TUNE_RGB_GAIN_ONLY)
    {
        // Measure the average min value
        if(ScalerAutoAccumulationMeasure(_MEASURE_RGB_MIN, 0) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
    }
    else
    {
        // Compensate offset
        if(ScalerAutoCompensateOffset(ucColor) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
    }

    // Update gain from swing = main-tone for max - average min
    pData[0] = ScalerAutoConvertAdcGainStep(ucGain, 255, HIBYTE(((WORD)ucMainTone << 8) - GET_AUTO_RESULT_WORD0()));

    // Decrease gain with underflow check
    if(ucGain >= pData[0])
    {
        ucGain -= pData[0];
    }
    else
    {
        ucGain = 0;
    }
    SET_AUTO_ADC_GAIN(ucGain);

    if(enumAutoType != _AUTO_TUNE_RGB_GAIN_ONLY)
    {
        // Double-check for offset
        if(ScalerAutoCompensateOffset(ucColor) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }

        // Set gain bias level from current black level
        pData[9] = (GET_AUTO_RESULT_WORD0() > (WORD)_BLACK_LEVEL_THRESHOLD) + _PANEL_ADC_OFFSET_BIAS;

        // Adjust ADC offset by panel defined bias
        // Increase offset with overflow check
        if((WORD)GET_AUTO_ADC_OFFSET() + _PANEL_ADC_OFFSET_BIAS > 0xFF)
        {
            SET_AUTO_ADC_OFFSET(0xFF);
        }
        else
        {
            SET_AUTO_ADC_OFFSET(GET_AUTO_ADC_OFFSET() + _PANEL_ADC_OFFSET_BIAS);
        }

        // Adjust ADC gain by calculated bias
        pData[9] = ScalerAutoConvertAdcGainStep(ucGain, 255, (255 - pData[9]));

        // Decrease gain with underflow check
        if(ucGain >= pData[9])
        {
            SET_AUTO_ADC_GAIN(ucGain - pData[9]);
        }
        else
        {
            SET_AUTO_ADC_GAIN(0);
        }
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Compensation for 0-level
// Input Value  : ucColor: select a color channel
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCompensateOffset(BYTE ucColor)
{
    BYTE ucOffset = 0;
    WORD usResult = 0;

    SET_AUTO_ADC_CHANNEL(ucColor);
    ucOffset = GET_AUTO_ADC_OFFSET();

    // Measure the average min value
    if(ScalerAutoAccumulationMeasure(_MEASURE_RGB_MIN, 0) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }
    usResult = GET_AUTO_RESULT_WORD0();

    if(HIBYTE(usResult) > 0)
    {
        // Increase offset by (minimum - 1)
        pData[0] = ((HIBYTE(usResult) == 1) ? 1 : (HIBYTE(usResult) - 1));
    }
    else if(usResult > (WORD)_BLACK_LEVEL_THRESHOLD)
    {
        pData[0] = 1;
    }
    else
    {
        pData[0] = 0;
    }

    // Increase offset with overflow check
    if((WORD)ucOffset + pData[0] > 0xFF)
    {
        ucOffset = 0xFF;
    }
    else
    {
        ucOffset += pData[0];
    }

    SET_AUTO_ADC_OFFSET(ucOffset);
    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Set boundary for image auto-function measure
// Input Value  : enumBoundary -> boundary type selection
// Output Value : None
//--------------------------------------------------
void ScalerAutoSetBoundary(EnumMeasureBoundary enumBoundary)
{
    switch(enumBoundary)
    {
        case _MEASURE_PORCH_REGION:
            ScalerVgaTopAutoFuncHBoundInitial(GET_VGA_MODE_HSTART(), (GET_VGA_MODE_HSTART() + 127));

            PDATA_WORD(0) = ((GET_VGA_MODE_VSTART() / 2) > 8) ? 8 : ((GET_VGA_MODE_VSTART() / 2) + 1); // V start
            ScalerVgaTopAutoFuncVBoundInitial(PDATA_WORD(0), (PDATA_WORD(0) + 1));
            break;

        case _MEASURE_ACTIVE_REGION:
            ScalerVgaTopAutoFuncHBoundInitial(GET_VGA_MODE_HSTART(), (GET_VGA_MODE_HSTART() + GET_INPUT_TIMING_HWIDTH()));
            ScalerVgaTopAutoFuncVBoundInitial(GET_VGA_MODE_VSTART(), (GET_VGA_MODE_VSTART() + GET_INPUT_TIMING_VHEIGHT()));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Measure the maximum / minimum value using compare measure
// Input Value  : enumType -> measure for maximum / minimum value
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCompareMeasure(EnumMeasureType enumType)
{
    BYTE ucMeasureType = 0;

    // Stop image auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Disable field select; Disable hardware acceleration;
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT4), 0x00);

    switch(enumType)
    {
        case _MEASURE_RGB_MIN:
            pData[0] = _MEASURE_PORCH_REGION;
            ucMeasureType = 0;
            break;

        case _MEASURE_YPBPR_MIN:
            pData[0] = _MEASURE_ACTIVE_REGION;
            ucMeasureType = 0;
            break;

        case _MEASURE_MAX:
        default:
            pData[0] = _MEASURE_ACTIVE_REGION;
            ucMeasureType = _BIT5;
            break;
    }

    // Set measure boundary
    ScalerAutoSetBoundary(pData[0]);

    // Normal boundary; Software mode; Measure maximum / minimum; Compare mode; Auto-balance; Start measure;
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (ucMeasureType | _BIT0));

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Measure the maximum / minimum value using compare measure
// Input Value  : enumType -> maximum / minimum measure,
//                ucThreshold  -> threshold for accumulation samples
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoAccumulationMeasure(EnumMeasureType enumType, BYTE ucThreshold)
{
    // Stop image auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Disable field select; Disable LPF filter; Disable hardware acceleration;
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    switch(enumType)
    {
        case _MEASURE_YPBPR_MIN:
            // Measure the pixel number BELOW the threshold
            ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT5, 0x00);
            ucThreshold ^= 0xFF;
            pData[0] = _MEASURE_ACTIVE_REGION;
            break;

        case _MEASURE_RGB_MIN:
            pData[0] = _MEASURE_PORCH_REGION;
            break;

        case _MEASURE_MAX:
        default:
            pData[0] = _MEASURE_ACTIVE_REGION;
            break;
    }

    // Set measure boundary
    ScalerAutoSetBoundary(pData[0]);

    // Set threshold
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, ucThreshold);

    // Normal boundary; Software mode; Measure maximum; Accumulation mode; Auto-balance; Start auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Search for ADC main tone between (start_level - 4) & start_level
// Input Value  : ucStartLevel -> search start level (must >= 4)
//                ucMainTone   -> address for main tone within search levels
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoMainToneMeasure(BYTE ucStartLevel, BYTE *pucMainTone)
{
    BYTE ucIndex = 0;

    // Stop auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    ScalerAutoSetBoundary(_MEASURE_ACTIVE_REGION);

    // Set default values
    *pucMainTone = 3;
    PDATA_DWORD(1) = 0; // Previous sum
    PDATA_DWORD(2) = 0; // Previous level
    PDATA_DWORD(3) = 0; // Max difference
    if(ucStartLevel != 255)
    {
        ++ucStartLevel;
    }

    // Default threshold at start_level
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, ucStartLevel);

    // Disable field select; Disable LPF filter; Disable hardware acceleration;
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // HW auto for 5 steps; Step size = 1;
    ScalerSetByte(P30_CB_VGATOP_HW_AUTO_PHASE_CTRL0, 0x20);

    // Initial phase = current phase
    ScalerSetByte(P30_CC_VGATOP_HW_AUTO_PHASE_CTRL1, (ScalerGetByte(P1_B4_PLLPHASE_CTRL1) & ~(_BIT7)));

    // HW auto-phase; Max value; Accumulation; Auto-balance; Start auto-function;
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT0));

    if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FAIL)
    {
        return _AUTO_FAIL;
    }

    for(ucIndex = 0; ucIndex < 5; ++ucIndex)
    {
        if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FAIL)
        {
            return _AUTO_FAIL;
        }

        // Decrease threshold
        ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, (ScalerGetByte(P30_C9_VGATOP_DIFF_THRESHOLD) - 1));

        // Get pixel count for current level
        PDATA_DWORD(0) = (GET_AUTO_RESULT_DWORD() - PDATA_DWORD(1)) / (ucStartLevel - ucIndex);

        // Store current accumulation result
        PDATA_DWORD(1) = GET_AUTO_RESULT_DWORD();

        // If start-level != 255, skip the first iteration.
        if((ucIndex == 0) && (ucStartLevel != 255))
        {
            continue;
        }

        // If the measured pixels is less than 2 vertical line, ignore it.
        if(PDATA_DWORD(0) < (GET_INPUT_TIMING_VHEIGHT() << 1))
        {
            PDATA_DWORD(0) = 0;
        }

        if(PDATA_DWORD(0) < PDATA_DWORD(2))
        {
            // Pixel decreases. Stop main-tone search.
            break;
        }

        PDATA_DWORD(2) = PDATA_DWORD(0) - PDATA_DWORD(2);

        // Compare the difference between successive levels & the maximum difference
        if(PDATA_DWORD(2) > PDATA_DWORD(3))
        {
            PDATA_DWORD(3) = PDATA_DWORD(2);
            *pucMainTone = ucIndex;
        }

        // Store current level
        PDATA_DWORD(2) = PDATA_DWORD(0);
    }

    // Stop auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    *pucMainTone = (ucStartLevel - *pucMainTone);

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Return the auto-color result
// Input Value  : stAdcData -> ADC data structure pointer
// Output Value : None
//--------------------------------------------------
void ScalerAutoGetAutoColorResult(StructAdcDataType *pstAdcData)
{
    ScalerRead(P0_C0_ADC_GAI_RED_MSB, 3, pstAdcData->pucAdcGainMSB, _AUTOINC);
    ScalerRead(P0_C3_ADC_OFF_RED_MSB, 3, pstAdcData->pucAdcOffsetMSB, _AUTOINC);
    pstAdcData->ucAdcPGA = 0;
    pstAdcData->pucAdcGainLSB[0] = 0;
    pstAdcData->pucAdcGainLSB[1] = 0;
    pstAdcData->pucAdcGainLSB[2] = 0;
    pstAdcData->pucAdcOffsetLSB[0] = 0;
    pstAdcData->pucAdcOffsetLSB[1] = 0;
    pstAdcData->pucAdcOffsetLSB[2] = 0;
}

#if(_YPBPR_SUPPORT == _ON)

#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE)
//--------------------------------------------------
// Description  : Compensate ADC gain / offset for YPbPr color space
// Input Value  : enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCompensateYPbPr(EnumAutoColorType enumAutoType)
{
    BYTE ucGain = 0;
    BYTE ucMainTone = 0;
    BYTE ucMaxLevel = 0;
    BYTE ucIndex = 0;

    if(enumAutoType != _AUTO_TUNE_YPBPR_GAIN_ONLY)
    {
        // Double check for offset
        if(ScalerAutoHardwareAbl(16, 2) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
    }

    // Compensate starts from Y channel
    SET_AUTO_ADC_CHANNEL(_AUTO_GREEN_CHANNEL);
    ucMaxLevel = _AUTO_Y_MAX_LEVEL;

    for(ucIndex = 0; ucIndex < 3; ++ucIndex)
    {
        ucGain = GET_AUTO_ADC_GAIN();

        // Measure main tone for each channel
        if(ScalerAutoMainToneMeasure(ucMaxLevel, &ucMainTone) == _AUTO_FAIL)
        {
            return _AUTO_FAIL;
        }
        ucMaxLevel = ScalerAutoConvertAdcGainStep(ucGain, ucMaxLevel, ucMainTone);

        SET_AUTO_ADC_GAIN(ucGain - ucMaxLevel);
        SET_AUTO_ADC_NEXT_CHANNEL();
        ucMaxLevel = _AUTO_PBPR_MAX_LEVEL;
    }

    return _AUTO_SUCCESS;
}
#endif // End of #if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE)

#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA)
//--------------------------------------------------
// Description  : Calculate ADC gain/offset for YPbPr from RGB auto-color result
// Input Value  : stAdcData: balanced gain/offset for RGB
// Output Value : balanced gain/offset for YPbPr from calculation
//--------------------------------------------------
StructAdcDataType ScalerAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData)
{
    StructAdcDataType stYPbPrData = {0};

    stYPbPrData = *pstAdcData;

    // Check for B/R swap. Assume default: Pr, Y, Pb
    stYPbPrData.pucAdcOffsetMSB[0] = pstAdcData->pucAdcOffsetMSB[0] + _AUTO_PR_OFFSET_BIAS; // Pr
    stYPbPrData.pucAdcOffsetMSB[2] = pstAdcData->pucAdcOffsetMSB[2] + _AUTO_PB_OFFSET_BIAS; // Pb
    stYPbPrData.pucAdcGainMSB[0] += (BYTE)(((DWORD)stYPbPrData.pucAdcGainMSB[0] + 64) * 31 / 224) + _AUTO_PR_GAIN_BIAS; // Pr
    stYPbPrData.pucAdcGainMSB[2] += (BYTE)(((DWORD)stYPbPrData.pucAdcGainMSB[2] + 64) * 31 / 224) + _AUTO_PB_GAIN_BIAS; // Pb

    stYPbPrData.pucAdcOffsetMSB[1] = stYPbPrData.pucAdcOffsetMSB[1] + _AUTO_Y_OFFSET_BIAS;// Y
    stYPbPrData.pucAdcGainMSB[1] += (BYTE)(((DWORD)stYPbPrData.pucAdcGainMSB[1] + 64) * 36 / 219) + _AUTO_Y_GAIN_BIAS; // Y

    return stYPbPrData;
}
#endif
#endif // End of #if(_YPBPR_SUPPORT == _ON)

#if(_ADC_SELF_CALIBRATION == _ON)
//--------------------------------------------------
// Description  : Update ADC gain for RGB self-calibration
// Input Value  : ucBias: bias level from max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoUpdateAdcGainCalibrationRGB(BYTE ucGainBias, BYTE ucStepRatio)
{
    BYTE ucIndex = 0;
    BYTE ucGain = 0;

    // Measure maximum value for RGB
    if(ScalerAutoAblMeasure() == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    // Update gain for each channel
    for(ucIndex = 0; ucIndex < 3; ++ucIndex)
    {
        ucGain = ScalerGetByte(P0_C0_ADC_GAI_RED_MSB + ucIndex);
        pData[0] = ScalerGetByte(P0_E9_AUTO_BLACK_LEVEL_RED_VALUE + ucIndex); // RGB max value
        pData[1] = _AUTO_RGB_MAX_LEVEL - ucGainBias; // RGB target value

        // Update ADC gain according to max level & measured maximum
        if(pData[0] < pData[1])
        {
            // Calculate gain step
            pData[2] = ScalerAutoConvertAdcGainStep(ucGain, pData[1], pData[0]) / ucStepRatio;

            if(pData[2] == 0x00)
            {
                --ucGain;
            }
            else
            {
                ucGain -= pData[2];
            }
        }
        else
        {
            // Target value exceeded. Rewind gain.
            ucGain += (pData[0] - pData[1]);
        }

        // Apply gain step
        ScalerSetByte((P0_C0_ADC_GAI_RED_MSB + ucIndex), ucGain);
    }

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Compensate ADC gain / offset for RGB self-calibration
// Input Value  : enumAutoType -> auto-color type
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCompensateCalibrationRGB(EnumAutoColorType enumAutoType)
{
    enumAutoType = enumAutoType;

    // Apply gain bias
    ScalerSetByte(P0_C0_ADC_GAI_RED_MSB, (ScalerGetByte(P0_C0_ADC_GAI_RED_MSB) + _CALIBRATION_R_GAIN_BIAS));
    ScalerSetByte(P0_C1_ADC_GAI_GRN_MSB, (ScalerGetByte(P0_C1_ADC_GAI_GRN_MSB) + _CALIBRATION_G_GAIN_BIAS));
    ScalerSetByte(P0_C2_ADC_GAI_BLU_MSB, (ScalerGetByte(P0_C2_ADC_GAI_BLU_MSB) + _CALIBRATION_B_GAIN_BIAS));

    // Check offset original signal level
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);
    if(ScalerAutoHardwareAbl(4, 4) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    // Apply R & B offset bias
    ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, (ScalerGetByte(P0_C3_ADC_OFF_RED_MSB) - _CALIBRATION_R_OFFSET_BIAS));
    ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, (ScalerGetByte(P0_C4_ADC_OFF_GRN_MSB) - _CALIBRATION_G_OFFSET_BIAS));
    ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, (ScalerGetByte(P0_C5_ADC_OFF_BLU_MSB) - _CALIBRATION_B_OFFSET_BIAS));

    return _AUTO_SUCCESS;
}

//--------------------------------------------------
// Description  : Initialization for ADC self-calibration
// Input Value  : none
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
void ScalerAutoInitializeCalibration(void)
{
    // Initial VGA data path
    ScalerSyncProcScanInitial();
    ScalerADCClampMode(_COLOR_SPACE_RGB);

    // Enable calibration mode; Enable calibration voltage; Set new-mode; Voltage from 3.3V
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(P0_D9_ADC_REG1, ~(_BIT1 | _BIT0), 0x00);

    // Set DPLL free-run
    ScalerMDomainSetDisplayFormat(_FREE_RUN_NO_INPUT);

    // Disable DPLL spread spectrum
    ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _OFF);

    // Switch sync-processor HS/VS source from D-domain
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT1, _BIT1);
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT2));
    ScalerSetBit(P0_48_SYNC_INVERT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
    ScalerSetBit(P0_49_SYNC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    DebugMessageAnalog("Self-Calibration clock(MHz)", _SELF_CALIBRATION_CLK);

    // Set APLL H total = Display H total
    ScalerAPLLAdjust(_SELF_CALIBRATION_HTOTAL, _SELF_CALIBRATION_HFREQ);

    // Set ADC bandwidth according to DPLL rate
    ScalerADCBandWidthSetting(_SELF_CALIBRATION_CLK);

    // Disable double buffer; Input ADC pixel format; Enable input sampling;
    ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Reset for ADC self-calibration
// Input Value  : none
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
void ScalerAutoResetCalibration(void)
{
    // Turn off calibration signal
    ScalerSetByte(P0_D2_ADC_GAIN_CALI, 0x00);

    // Set sync processsor HS/VS source from ADC
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT2, 0x00);
}

//--------------------------------------------------
// Description  : Measure the average value using ABL
// Input Value  : none
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoAblMeasure(void)
{
    // Set calibration voltage to high
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Enable ABL offset adjust new mode
    ScalerSetBit(P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE, ~_BIT3, _BIT3);

    // Measure RGB max using ABL
    if(ScalerAutoHardwareAbl(16, 0) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    // Disable ABL offset adjust new mode
    ScalerSetBit(P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE, ~_BIT3, 0x00);

    // Set calibration voltage to low
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    return _AUTO_SUCCESS;
}
#endif // End of #if(_ADC_SELF_CALIBRATION == _ON)

//--------------------------------------------------
// Description  : Update ADC gain for RGB color space in custom mode
// Input Value  : ucGainBias: bias for RGB max level
// Output Value : _AUTO_SUCCESS or _AUTO_FAIL
//--------------------------------------------------
EnumAutoResult ScalerAutoCustomUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio)
{
    if(ScalerAutoCustomUpdateAdcGainChannel(_AUTO_RED_CHANNEL, ucGainBias, ucStepRatio) == _AUTO_SUCCESS)
    {
        if(ScalerAutoCustomUpdateAdcGainChannel(_AUTO_BLUE_CHANNEL, ucGainBias, ucStepRatio) == _AUTO_SUCCESS)
        {
            if(ScalerAutoCustomUpdateAdcGainChannel(_AUTO_GREEN_CHANNEL, ucGainBias, ucStepRatio) == _AUTO_SUCCESS)
            {
                return _AUTO_SUCCESS;
            }
        }
    }

    return _AUTO_FAIL;
}

//--------------------------------------------------
// Description  : Update ADC gain for R/G/B color space in custom mode
// Input Value  : enumAutoType -->
//                ucGainBias: bias for RGB max level
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
EnumAutoResult ScalerAutoCustomUpdateAdcGainChannel(BYTE ucColor, BYTE ucGainBias, BYTE ucStepRatio)
{
    BYTE ucGain = 0;
    BYTE ucTarget = (255 - ucGainBias);
    BYTE ucMax = 0;

    SET_AUTO_ADC_CHANNEL(ucColor);
    ucGain = GET_AUTO_ADC_GAIN();

    // Stop image auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Disable field select; Enable LPF filter; Disable hardware acceleration;
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, 0x00);
    ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT7 | _BIT4), 0x00);

    // Set measure boundary
    ScalerVgaTopAutoFuncHBoundInitial(_AUTO_CUSTOM_WHITE_HSTART, _AUTO_CUSTOM_WHITE_HEND);
    ScalerVgaTopAutoFuncVBoundInitial(_AUTO_CUSTOM_WHITE_VSTART, _AUTO_CUSTOM_WHITE_VEND);

    // Normal boundary; Software mode; Measure maximum / minimum; Compare mode; Auto-balance; Start measure;
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        return _AUTO_FAIL;
    }

    ucMax = (GET_AUTO_RESULT_DWORD()) /
            (_AUTO_CUSTOM_WHITE_VEND - _AUTO_CUSTOM_WHITE_VSTART + 1) /
            (_AUTO_CUSTOM_WHITE_HEND - _AUTO_CUSTOM_WHITE_HSTART + 1);

    // Update ADC gain according to max level & measured maximum
    if(ucMax < ucTarget)
    {
        // Calculate gain step
        pData[1] = ScalerAutoConvertAdcGainStep(ucGain, ucTarget, ucMax) / ucStepRatio;

        // Minimum gain step = 1
        if(pData[1] == 0)
        {
            pData[1] = 1;
        }

        // Decrease gain with underflow check
        if(ucGain >= pData[1])
        {
            ucGain -= pData[1];
        }
        else
        {
            ucGain = 0;
        }
    }
    else
    {
        // Target value exceeded. Rewind gain.
        pData[1] = (ucMax - ucTarget);

        // Increase gain with overflow check
        if(((WORD)ucGain + pData[1]) > 0xFF)
        {
            ucGain = 0xFF;
        }
        else
        {
            ucGain += pData[1];
        }
    }

    SET_AUTO_ADC_GAIN(ucGain);

    return _AUTO_SUCCESS;
}

#endif // End of #if(_VGA_SUPPORT == _ON)

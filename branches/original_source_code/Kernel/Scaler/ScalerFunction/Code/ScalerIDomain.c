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
// ID Code      : ScalerIDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IDOMAIN__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usVgipVDelayInitial;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerIDomainCheckDigitalCapture(void);
void ScalerIDomainVgipSetInputCapture(void);
WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition);
void ScalerIDomainVgipAdjustIHVDelay(void);
void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture);
void ScalerIDomainResetDataPath(EnumInputDataPath enumVgipInputPath);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check if to enable VGIP digital capture
// Input Value  : N/A
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerIDomainCheckDigitalCapture(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _TRUE;
    }
#endif

    return (ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE);
}

//--------------------------------------------------
// Description  : Set VGIP Capture Window
// Input Value  : Capture Type, H/V Active and Start
// Output Value : None
//--------------------------------------------------
void ScalerIDomainVgipSetInputCapture(void)
{
    ScalerVgipSetInputPath(GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerVgipCaptureEnable(_ENABLE);

    if(ScalerIDomainCheckDigitalCapture() == _TRUE)
    {
        // Enable digital capture
        ScalerVgipSetDigitalCaptureStatus(_ENABLE);

        // Set VGIP H Capture Width
        ScalerVgipSetCaptureHWidth(GET_MDOMAIN_INPUT_HWIDTH());

        // Set VGIP V Capture Heigth
        ScalerVgipSetCaptureVHeight(GET_MDOMAIN_INPUT_VHEIGHT());

        // Set VGIP H capture start position
        if(GET_MDOMAIN_INPUT_HSTART() > GET_INPUT_TIMING_HSTART())
        {
            ScalerVgipSetCaptureHStartPosition(GET_MDOMAIN_INPUT_HSTART() - GET_INPUT_TIMING_HSTART());
        }
        else
        {
            ScalerVgipSetCaptureHStartPosition(0x00);
        }

        // Set VGIP V capture start position
        if(GET_MDOMAIN_INPUT_VSTART() > GET_INPUT_TIMING_VSTART())
        {
            ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART() - GET_INPUT_TIMING_VSTART());
        }
        else
        {
            ScalerVgipSetCaptureVStartPosition(0x00);
        }

        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);
        }

        // Set VGIP capture delay
        ScalerVgipSetCaptureHDelay(0);
        ScalerVgipSetCaptureVDelay(0);
    }
    else
    {
        WORD usIHDelay = 0;

        // Set VGIP H Capture Width
        ScalerVgipSetCaptureHWidth(g_stMDomainInputData.usHWidth);

        // Set VGIP V Capture Heigth
        ScalerVgipSetCaptureVHeight(g_stMDomainInputData.usVHeight);

        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);
        }

        if(g_stMDomainInputData.usHStart <= _VGIP_IH_CAPTURE_MIN_VALUE)
        {
            g_stMDomainInputData.usHStart = _VGIP_IH_CAPTURE_MIN_VALUE + 1;
        }

        usIHDelay = g_stMDomainInputData.usHStart - ScalerIDomainVgipIHCaptureMaxEstimate(g_stMDomainInputData.usHStart);

        g_stMDomainInputData.usHStart = ScalerIDomainVgipIHCaptureMaxEstimate(g_stMDomainInputData.usHStart);

        // Set VGIP H Capture Start Position
        ScalerVgipSetCaptureHStartPosition(g_stMDomainInputData.usHStart);

        // Front Porch is Not Enough
        if(g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight + 3 >= g_stMDomainInputData.usVTotal)
        {
            // Increase Front Porch by VDelay
            SET_VGIP_INITIAL_VDELAY(g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight + 3 - g_stMDomainInputData.usVTotal);
            g_stMDomainInputData.usVStart -= GET_VGIP_INITIAL_VDELAY();
        }
        else
        {
            SET_VGIP_INITIAL_VDELAY(0);
        }

        // Check if V capture start exceeds maximum value
        if(g_stMDomainInputData.usVStart > _VGIP_IV_CAPTURE_MAX_VALUE)
        {
            SET_VGIP_INITIAL_VDELAY(GET_VGIP_INITIAL_VDELAY() + (BYTE)(g_stMDomainInputData.usVStart - _VGIP_IV_CAPTURE_MAX_VALUE));
            g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MAX_VALUE;
        }

        // Set VGIP V Capture Start Position
        ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);

        // Set VGIP capture delay
        ScalerVgipSetCaptureHDelay(usIHDelay);
        ScalerVgipSetCaptureVDelay(GET_VGIP_INITIAL_VDELAY());
    }

    DebugMessageScaler("9. Set Capture usHWidth", g_stMDomainInputData.usHWidth);
    DebugMessageScaler("9. Set Capture usHStart", g_stMDomainInputData.usHStart);
    DebugMessageScaler("9. Set Capture usVHeight", g_stMDomainInputData.usVHeight);
    DebugMessageScaler("9. Set Capture usVStart", g_stMDomainInputData.usVStart);
}

//--------------------------------------------------
// Description  : Estimate Max Allowable H Capture Start
// Input Value  : Current H Start
// Output Value : Max Allowable H Start
//--------------------------------------------------
WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition)
{
    if(usHPosition <= (_VGIP_IH_DELAY_MAX_VALUE + _VGIP_IH_CAPTURE_MIN_VALUE - (_MAX_H_POSITION_RANGE / 2)))
    {
        return _VGIP_IH_CAPTURE_MIN_VALUE;
    }
    else
    {
        usHPosition -= (_VGIP_IH_DELAY_MAX_VALUE - (_MAX_H_POSITION_RANGE / 2));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
        {
            usHPosition = ((usHPosition + 1) & 0xFFFE);
        }
#endif

        return usHPosition;
    }
}

//--------------------------------------------------
// Description  : Adjust IVS/IHS Delay to Gain Largest Position-Adjusting Range
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIDomainVgipAdjustIHVDelay(void)
{
    WORD usIV2DVdelay = 0;
    BYTE ucIVSdelayExtend = 0;
    BYTE ucEOshift = 0;
    BYTE ucFBshift = 0;

    // Bypass IHV delay in digital capture
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1))
    {
        usIV2DVdelay = (ScalerMemoryGetIVS2DVSDelayPixel() - (g_stMDomainInputData.usHTotal / 2)) / g_stMDomainInputData.usHTotal;
    }
    else
    {
        usIV2DVdelay = ScalerMemoryGetIVS2DVSDelayPixel() / g_stMDomainInputData.usHTotal;
    }

#if(_FRC_SUPPORT == _ON)
    if((GET_MEMORY_SELECT() != _FRAME_SYNC_LINE_BUFFER) && (GET_MEMORY_SELECT() != _FREE_RUN_NO_INPUT))
    {
        // Set IVS Delay
        if((g_stMDomainInputData.usVStart + GET_VGIP_INITIAL_VDELAY()) > _VGIP_IV_CAPTURE_MIN_VALUE)
        {
            ScalerVgipSetCaptureVDelay(g_stMDomainInputData.usVStart - _VGIP_IV_CAPTURE_MIN_VALUE + GET_VGIP_INITIAL_VDELAY());
            SET_VGIP_INITIAL_VDELAY(g_stMDomainInputData.usVStart - _VGIP_IV_CAPTURE_MIN_VALUE + GET_VGIP_INITIAL_VDELAY());
        }
        else
        {
            ScalerVgipSetCaptureVDelay(0);
            SET_VGIP_INITIAL_VDELAY(0);
        }

        // Set V Start
        g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MIN_VALUE;
        ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);
    }
    else
#endif
    {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            // Remain IVSt = Raw IVSt - IVSDelay
            g_stMDomainInputData.usVStart = g_stMDomainInputData.usVStart - usIV2DVdelay;

            if(g_stMDomainInputData.usVStart <= (_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2))
            {
                DebugMessageScaler("VStart too Small", g_stMDomainInputData.usVStart);

                // Get Difference of Remain IVSt and _VGIP_IV_CAPTURE_MIN_VALUE
                ucIVSdelayExtend = (_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2) - g_stMDomainInputData.usVStart;
                g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2;
            }
            else
            {
                ucIVSdelayExtend = g_stMDomainInputData.usVStart % 2;
                g_stMDomainInputData.usVStart += g_stMDomainInputData.usVStart % 2;
            }
        }
        else
#endif
        {
            // Remain IVSt = Raw IVSt - IVSDelay
            g_stMDomainInputData.usVStart = g_stMDomainInputData.usVStart - usIV2DVdelay;

            if(g_stMDomainInputData.usVStart <= _VGIP_IV_CAPTURE_MIN_VALUE)
            {
                DebugMessageScaler("VStart too Small", g_stMDomainInputData.usVStart);

                // Get Difference of Remain IVSt and _VGIP_IV_CAPTURE_MIN_VALUE
                ucIVSdelayExtend = _VGIP_IV_CAPTURE_MIN_VALUE - g_stMDomainInputData.usVStart;
                g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MIN_VALUE;
            }
            else
            {
                ucIVSdelayExtend = 0;
            }
        }

        // Move Delay to ivs to dvs
        ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);

        // Set IVS to DVS Delay
        ScalerVgipSetCaptureVDelay((WORD)(usIV2DVdelay - ucIVSdelayExtend + GET_VGIP_INITIAL_VDELAY()));

        PDATA_DWORD(0) = ScalerMemoryGetIVS2DVSDelayPixel() - (DWORD)(usIV2DVdelay - ucIVSdelayExtend) * g_stMDomainInputData.usHTotal;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            ucEOshift = 1;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                ucFBshift = 1;
            }
#endif
        }
#endif

        PDATA_DWORD(0) = PDATA_DWORD(0) >> ucEOshift;

        if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
           (ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1) &&
           (PDATA_DWORD(0) >= (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)))
        {
            // Preserve 0.5 lines + 64 pixel in Fine Tune Byte
            PDATA_WORD(2) = (PDATA_DWORD(0) - (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)) / g_stMDomainInputData.usHTotal;
            PDATA_WORD(3) = (PDATA_DWORD(0) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
            PDATA_WORD(4) = (PDATA_DWORD(0) - (g_stMDomainInputData.usHTotal >> (1 + ucEOshift)) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
            pData[10] = (PDATA_DWORD(0) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
            pData[11] = (PDATA_DWORD(0) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(4) << (4 + ucFBshift))) >> ucFBshift;
        }
        else
        {
            PDATA_WORD(2) = (PDATA_DWORD(0) / g_stMDomainInputData.usHTotal);
            PDATA_WORD(3) = (PDATA_DWORD(0) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
            PDATA_WORD(4) = 0x0000;
            pData[10] = (PDATA_DWORD(0) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
            pData[11] = 0x00;
        }

        //-------------------------------------------------
        // Apply updated Delay
        //-------------------------------------------------
        // IVS2DVS line delay, unit: line
        ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (pData[4] & 0x1F));
        ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, pData[5]);

        // IVS2DVS 16iclk1 delay, unit: 16 pixel
        PDATA_WORD(3) -= (PDATA_WORD(3) >= 1) ? 1 : 0;
        SET_IVS2DVS_DELAY_16ICLK1(PDATA_WORD(3));

        // IVS2DVS 16iclk2 delay, unit: 16 pixel
        PDATA_WORD(4) -= (PDATA_WORD(4) >= 1) ? 1 : 0;
        SET_IVS2DVS_DELAY_16ICLK2(PDATA_WORD(4));

        // IVS2DVS iclk1 delay, unit: 1 pixel
        ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, ((pData[10] & 0x0F) << 4));

        // IVS2DVS iclk2 delay, unit: 1 pixel
        ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, (pData[11] & 0x0F));
    }
}

//--------------------------------------------------
// Description  : Modify H Capture
// Input Value  : IH Capture Shift
// Output Value : None
//--------------------------------------------------
void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture)
{
    ScalerVgipSetCaptureHStartPosition(usDeltaIHCapture + ScalerVgipGetCaptureHStartPosition() - 2);

// What is this?
//    ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, (ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD) + ((BYTE)(usDeltaIHCapture / 16))));
//    ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, (ScalerGetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN) + ((BYTE)(usDeltaIHCapture / 16))));
}

//--------------------------------------------------
// Description  : Reset input data path process
// Input Value  : enumVgipInputPath --> target data path for reset
// Output Value : None
//--------------------------------------------------
void ScalerIDomainResetDataPath(EnumInputDataPath enumVgipInputPath)
{
    if((enumVgipInputPath & _INPUT_PATH_M1) == _INPUT_PATH_M1)
    {
        // Disable on-line measure
        ScalerSetBit(P16_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

        // Clear on-line measure flag
        ScalerSetByte(P16_03_MEAS_ERROR_FLG0, 0xFF);
        ScalerSetByte(P16_15_MEAS_HS_VS_DELTA_CTL, 0x00);
        ScalerSetByte(P16_16_MEAS_HS_VS_DELTA_IRQ, 0xF0);
        ScalerSetByte(P16_17_MEAS_HS_VS_DELTA_WD, 0x00);
        ScalerSetByte(P16_18_MEAS_HS_VS_ERROR_WD, 0x00);

        // Disable VGIP
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~(_BIT7 | _BIT0), 0x00);
    }

    if((enumVgipInputPath & _INPUT_PATH_M2) == _INPUT_PATH_M2)
    {
        // Disable on-line measure
        ScalerSetBit(P56_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

        // Clear on-line measure flag
        ScalerSetByte(P56_03_MEAS_ERROR_FLG0, 0xFF);
        ScalerSetByte(P56_15_MEAS_HS_VS_DELTA_CTL, 0x00);
        ScalerSetByte(P56_16_MEAS_HS_VS_DELTA_IRQ, 0xF0);
        ScalerSetByte(P56_17_MEAS_HS_VS_DELTA_WD, 0x00);
        ScalerSetByte(P56_18_MEAS_HS_VS_ERROR_WD, 0x00);

        // Disable VGIP
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~(_BIT7 | _BIT0), 0x00);
    }

    if((enumVgipInputPath & _INPUT_PATH_S1) == _INPUT_PATH_S1)
    {
        // Disable on-line measure
        ScalerSetBit(P96_12_MEAS_VS_PERIOD_D_L, ~(_BIT5 | _BIT0), 0x00);

        // Clear on-line measure flag
        ScalerSetByte(P96_03_MEAS_ERROR_FLG0, 0xFF);
        ScalerSetByte(P96_15_MEAS_HS_VS_DELTA_CTL, 0x00);
        ScalerSetByte(P96_16_MEAS_HS_VS_DELTA_IRQ, 0xF0);
        ScalerSetByte(P96_17_MEAS_HS_VS_DELTA_WD, 0x00);
        ScalerSetByte(P96_18_MEAS_HS_VS_ERROR_WD, 0x00);

        // Disable VGIP
        ScalerSetBit(P80_10_S1_VGIP_CTRL, ~(_BIT7 | _BIT0), 0x00);
    }

    if((enumVgipInputPath & _INPUT_PATH_S2) == _INPUT_PATH_S2)
    {
        // Disable on-line measure
        ScalerSetBit(PD6_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

        // Clear on-line measure flag
        ScalerSetByte(PD6_03_MEAS_ERROR_FLG0, 0xFF);
        ScalerSetByte(PD6_15_MEAS_HS_VS_DELTA_CTL, 0x00);
        ScalerSetByte(PD6_16_MEAS_HS_VS_DELTA_IRQ, 0xF0);
        ScalerSetByte(PD6_17_MEAS_HS_VS_DELTA_WD, 0x00);
        ScalerSetByte(PD6_18_MEAS_HS_VS_ERROR_WD, 0x00);

        // Disable VGIP
        ScalerSetBit(PC0_10_S2_VGIP_CTRL, ~(_BIT7 | _BIT0), 0x00);
    }

    // Reset timing info
    ScalerMeasureResetTimingInfo(enumVgipInputPath);
}

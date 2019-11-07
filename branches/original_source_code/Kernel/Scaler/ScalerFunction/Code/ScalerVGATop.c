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
// ID Code      : ScalerVGATop.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_VGATOP__

#include "ScalerFunctionInclude.h"

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions Of VGA noise margin
//--------------------------------------------------
#define _VGA_NOISE_MARGIN                               (0x40)

//--------------------------------------------------
// Noise width definitions
//--------------------------------------------------
#define _NOISE_WIDTH_AFTER_HSYNC                        (0x3C)
#define _NOISE_WIDTH_AFTER_VSYNC                        (0x01)

//--------------------------------------------------
// Noise Delay before hs definitions, Unit: ns
//--------------------------------------------------
#define _NOISE_DELAY_BEFORE_HSYNC_POSITIVE              (80) // Unit: ns
#define _NOISE_DELAY_BEFORE_HSYNC_NEGTIVE               (100) // Unit: ns

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usPhaseDelayTime;

WORD g_usVgaModeHstart;
WORD g_usVgaModeVstart;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerVgaTopInputInitial(void);
bit ScalerVgaTopModifyVsLatchEdge(bit bWait);
void ScalerVgaTopModifyPolarity(void);

void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd);
void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait);
bit ScalerVgaTopHWAutoPhaseSearch(EnumAutoPhaseSearchStep enumPhaseStep, BYTE *pucPhaseResult, DWORD *pulSODMax, DWORD *pulSODMin, EnumAutoPhaseSearchSODMethod enumSODMethod, BYTE ucSODThreshold);
bit ScalerVgaTopAutoPhaseGetSOD(DWORD *pulSODValue);
bit ScalerVgaTopMeasureActiveRegion(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);

bit ScalerVgaTopAutoFuncWaitFinish(void);
bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent);

void ScalerVgaTopDoubleBufferApply(void);
void ScalerVgaTopDoubleBufferEnable(bit bEn);
WORD ScalerVgaTopGetCaptureVStartPosition(void);
void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart);
WORD ScalerVgaTopGetCaptureVHeight(void);
void ScalerVgaTopSetCaptureVHeight(WORD usIVheight);
WORD ScalerVgaTopGetCaptureVDelay(void);
void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay);
WORD ScalerVgaTopGetCaptureHStartPosition(void);
void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart);
WORD ScalerVgaTopGetCaptureHWidth(void);
void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth);
WORD ScalerVgaTopGetCaptureHDelay(void);
void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay);
void ScalerVgaTopSetCapture(void);

WORD ScalerVgaTopSearchHsEdge(void);
void ScalerVgaTopModifyHsLatchEdgeDelay(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Initial for VGIP Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopInputInitial(void)
{
    // Set Input Pixel Format, Disable Double buffer, Analog Capture, and Start generate DE
    ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Reset field detect edge
    ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~(_BIT6 | _BIT5 | _BIT3), 0x00);

    // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
    ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // Initial IVS/IHS Delay for Capture and Auto
    ScalerSetByte(P30_AC_VGATOP_IVS_DELAY, 0x00);
    ScalerSetByte(P30_AD_VGATOP_IHS_DELAY, 0x00);
    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Modify VS latch edge
// Input Value  : Input Source Type
// Output Value : None
//--------------------------------------------------
bit ScalerVgaTopModifyVsLatchEdge(bit bWait)
{
    if(bWait == _WAIT)
    {
        ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
    }

    pData[0] = ScalerGetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, (_BIT7 | _BIT6 | _BIT5));

    // Wait One More Frame in case of Interlaced Mode
    if(pData[0] == 0x00)
    {
        ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

        pData[0] = ScalerGetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, (_BIT7 | _BIT6 | _BIT5));
    }

    // If the edge between H-Sync and V-Sync is too close.
    if((pData[0] == 0x00) || (pData[0] == 0xE0) || (pData[0] == 0x80) || (pData[0] == 0xC0))
    {
        // Field detection by hs positive edge
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT5, _BIT5);

        // V-Sync latched by H-Sync positive edge
        ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~_BIT2, _BIT2);

        return _TRUE;
    }
    else
    {
        // Field detection by hs negative edge
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT5, 0x00);

        // V-Sync latched by H-Sync negative edge
        ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~_BIT2, 0x00);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Initial H Boundary for Auto Function Measure
// Input Value  : H Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopModifyPolarity(void)
{
    if(GET_SYNC_V_POLARITY() == _POSITIVE)
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT3, 0x00);
    }
    else
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT3, _BIT3);
    }

    if(GET_SYNC_H_POLARITY() == _POSITIVE)
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT2, 0x00);
    }
    else
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT2, _BIT2);
    }
}

//--------------------------------------------------
// Description  : Initial H Boundary for Auto Function Measure
// Input Value  : H Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd)
{
    // Set H boundary
    ScalerSetByte(P30_C0_VGATOP_H_BOUNDARY_H, (((HIBYTE(usHBoundStart) & 0x0F) << 4) | (HIBYTE(usHBoundEnd) & 0x0F)));
    ScalerSetByte(P30_C1_VGATOP_H_BOUNDARY_STA_L, LOBYTE(usHBoundStart));
    ScalerSetByte(P30_C2_VGATOP_H_BOUNDARY_END_L, LOBYTE(usHBoundEnd));
}

//--------------------------------------------------
// Description  : Initial V Boundary for Auto Function Measure
// Input Value  : V Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd)
{
    // Set V boundary
    ScalerSetByte(P30_C3_VGATOP_V_BOUNDARY_H, (((HIBYTE(usVBoundStart) & 0x0F) << 4) | (HIBYTE(usVBoundEnd) & 0x0F)));
    ScalerSetByte(P30_C4_VGATOP_V_BOUNDARY_STA_L, LOBYTE(usVBoundStart));
    ScalerSetByte(P30_C5_VGATOP_V_BOUNDARY_END_L, LOBYTE(usVBoundEnd));
}

//--------------------------------------------------
// Description  : Initialization for Picture Position <easure by Auto Function Measure
// Input Value  : EnumMeasureFieldSelect --> Measure for Even or Odd Field
//                EnumMeasureBoundType --> OverScan Boundary or Normal Boundary
//                usHTotal --> H Total
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal)
{
    WORD usHLbound = 0;
    WORD usHRbound = 0;
    WORD usHSWidth = 0;
    WORD usVSWidth = 0;

    // Disable auto-function
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Set active measured V-Sync delay 3 lines for auto function
    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~(_BIT5 | _BIT4), _BIT4);

    if(enumFieldSelect == _EVEN_FIELD_MEASURE)
    {
        // Field Select to Even, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        ScalerSetByte(P30_CA_VGATOP_AUTO_ADJ_CTRL0, 0x80);
    }
    else if(enumFieldSelect == _ODD_FIELD_MEASURE)
    {
        // Field Select to Odd, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        ScalerSetByte(P30_CA_VGATOP_AUTO_ADJ_CTRL0, 0xC0);
    }
    else
    {
        // Disable Field Select, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        ScalerSetByte(P30_CA_VGATOP_AUTO_ADJ_CTRL0, 0x00);
    }

    // Convert to positive if input sync is negative.
    usHSWidth = GET_INPUT_TIMING_HSYNCWIDTH();

    // Sync Pulse should be smaller than 1/2 period.
    usVSWidth = GET_INPUT_TIMING_VSYNCWIDTH();

    // L Boundary position reference clamp signal end position add 0x05 tolerance
    // Notice: clamp signal start position reference HS trailing edge
    usHLbound = ScalerSyncProcGetClampEndPosition() + 0x05;

    // Calculate left boundary.
    // Unit Conversion Formula: Left Boundary = HPeriod Pixel Clock * (H-Sync Pulse Didth / H-Sync Period) + Clamp End
    usHLbound += (((DWORD)usHTotal * usHSWidth) / GET_SYNC_H_PERIOD());

    // Input signal is positive polarity
    if((bit)GET_INPUT_TIMING_H_POLARITY() == _TRUE)
    {
        usHRbound = (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_POSITIVE * GET_A0_INPUT_PIXEL_CLK()) / 10000) + 1;
    }
    else
    {
        usHRbound = (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_NEGTIVE * GET_A0_INPUT_PIXEL_CLK()) / 10000) + 1;
    }

    usHRbound = usHTotal - usHRbound;

    // Set H boundary
    ScalerVgaTopAutoFuncHBoundInitial(usHLbound, usHRbound);

    // Set V Boundary
    if((enumBoundType == _OVERSCAN_BOUNDARY) &&
       (GET_INPUT_TIMING_VHEIGHT() >= ScalerVgaTopGetCaptureVHeight()))
    {
        ScalerVgaTopAutoFuncVBoundInitial((usVSWidth + _NOISE_WIDTH_AFTER_VSYNC + ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)), (GET_INPUT_TIMING_VTOTAL() - 2 - ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)));
    }
    else
    {
        ScalerVgaTopAutoFuncVBoundInitial((usVSWidth + _NOISE_WIDTH_AFTER_VSYNC), (GET_INPUT_TIMING_VTOTAL() - 2));
    }

    // Set noice margin according to current clamp type for VGA
    ScalerRead(P0_CF_ADC_CTL_RED, 3, pData, _AUTOINC);

    if(((pData[0] & _BIT7) == _BIT7) && ((pData[2] & _BIT7) == _BIT7) && ((pData[1] & _BIT7) == 0x00))
    {
        // Set Noise Margin
        ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0xFC);
        ScalerSetBit(P30_C7_VGATOP_GRN_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_VGA_NOISE_MARGIN) & 0xFC));
        ScalerSetBit(P30_C8_VGATOP_BLU_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0xFC);
    }
    else
    {
        // Set Noise Margin
        ScalerSetBit(P30_C6_VGATOP_RED_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_VGA_NOISE_MARGIN) & 0xFC));
        ScalerSetBit(P30_C7_VGATOP_GRN_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_VGA_NOISE_MARGIN) & 0xFC));
        ScalerSetBit(P30_C8_VGATOP_BLU_NOISE_MARGIN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_VGA_NOISE_MARGIN) & 0xFC));
    }

    // Analog Measure Mode, Select Software Mode, Select Software Mode, Select Auto Balance, Start Auto Function Measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT1), 0x00);

    if(enumBoundType == _OVERSCAN_BOUNDARY)
    {
        if(GET_INPUT_TIMING_VHEIGHT() >= ScalerVgaTopGetCaptureVHeight())
        {
            // Set V Boundary
            ScalerVgaTopAutoFuncVBoundInitial((usVSWidth + _NOISE_WIDTH_AFTER_VSYNC + ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)), (GET_INPUT_TIMING_VTOTAL() - 2 - ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)));

            // Analog Measure Mode, Select Software Mode, Select Software Mode, Select Auto Balance, Start Auto Function Measure
            ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT1), 0x00);
        }
    }

    // Start auto-function measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Pop Up Auto-Function Result
// Input Value  : stActiveRegion --> measure result
//                bWait --> wait auto-function stop or not
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait)
{
    BYTE ucVdelayCount = 0;
    BYTE ucRepeatCount = 0;

    while(ucRepeatCount < 2) // Maximum Measure Time is 2 times
    {
        if((bWait == _WAIT) || (ScalerGetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, _BIT6) == 0x00))
        {
            if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
            {
                return _FALSE;
            }
        }

        // Calculate delay for auto-function VS
        switch(ScalerGetBit(P30_AE_VGATOP_VGIP_HV_DELAY, (_BIT5 | _BIT4)))
        {
            default:
            case 0x00:
                ucVdelayCount = 0;
                break;

            case _BIT4:
                ucVdelayCount = 3;
                break;

            case _BIT5:
                ucVdelayCount = 7;
                break;

            case (_BIT5 | _BIT4):
                ucVdelayCount = 15;
                break;
        }

        pstActiveRegion->usVActiveStart = (((WORD)(ScalerGetByte(P30_CE_VGATOP_VER_START_END_H) & 0xF0) << 4) | ScalerGetByte(P30_CF_VGATOP_VER_START_L)) + ucVdelayCount;
        pstActiveRegion->usVActiveEnd = (((WORD)(ScalerGetByte(P30_CE_VGATOP_VER_START_END_H) & 0x0F) << 8) | ScalerGetByte(P30_D0_VGATOP_VER_END_L)) + ucVdelayCount;

        // Add offset for V start/end
        pstActiveRegion->usVActiveStart += _VGATOP_VSTART_OFFSET;
        pstActiveRegion->usVActiveEnd += _VGATOP_VSTART_OFFSET;

        DebugMessageAnalog("5.Active Measure H-ActiveStart", pstActiveRegion->usHActiveStart);
        DebugMessageAnalog("5.Active Measure H-ActiveEnd", pstActiveRegion->usHActiveEnd);
        DebugMessageAnalog("5.Active Measure V-ActiveStart", pstActiveRegion->usVActiveStart);
        DebugMessageAnalog("5.Active Measure V-ActiveEnd", pstActiveRegion->usVActiveEnd);

        if(ScalerGetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, _BIT7) == _BIT7)
        {
            pstActiveRegion->usHActiveStart = (((WORD)(ScalerGetByte(P30_D1_VGATOP_H_START_END_H) & 0xF0) << 4) | ScalerGetByte(P30_D2_VGATOP_H_START_L)) + 1;
            pstActiveRegion->usHActiveEnd = (((WORD)(ScalerGetByte(P30_D1_VGATOP_H_START_END_H) & 0x0F) << 8) | ScalerGetByte(P30_D3_VGATOP_H_END_L)) + 1;
        }
        else
        {
            pstActiveRegion->usHActiveStart = (((WORD)(ScalerGetByte(P30_D1_VGATOP_H_START_END_H) & 0xF0) << 4) | ScalerGetByte(P30_D2_VGATOP_H_START_L));
            pstActiveRegion->usHActiveEnd = (((WORD)(ScalerGetByte(P30_D1_VGATOP_H_START_END_H) & 0x0F) << 8) | ScalerGetByte(P30_D3_VGATOP_H_END_L));
        }

        // Check auto-function measure result
        if((pstActiveRegion->usVActiveStart == ucVdelayCount) ||
           (pstActiveRegion->usVActiveEnd == ucVdelayCount) ||
           (pstActiveRegion->usHActiveStart == 0x00) ||
           (pstActiveRegion->usHActiveEnd == 0x00))
        {
            pstActiveRegion->usHActiveStart = 0x00;
            pstActiveRegion->usHActiveEnd = 0x00;
            pstActiveRegion->usVActiveStart = 0x00;
            pstActiveRegion->usVActiveEnd = 0x00;

            // Return fail for digital measure
            if(ScalerGetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, _BIT7) == _BIT7)
            {
                return _FALSE;
            }
        }

        // Check auto-function boundary setting for analog measure
        if((ScalerGetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, _BIT7) == 0x00) &&
           (ucRepeatCount == 0))
        {
            // Clear wait flag
            bWait = _NOT_WAIT;

            // Get current auto-function boundories
            PDATA_WORD(0) = ((((WORD)ScalerGetByte(P30_C0_VGATOP_H_BOUNDARY_H) & 0xF0) << 4) | ScalerGetByte(P30_C1_VGATOP_H_BOUNDARY_STA_L)); // H start
            PDATA_WORD(1) = ((((WORD)ScalerGetByte(P30_C0_VGATOP_H_BOUNDARY_H) & 0x0F) << 8) | ScalerGetByte(P30_C2_VGATOP_H_BOUNDARY_END_L)); // H end
            PDATA_WORD(2) = ((((WORD)ScalerGetByte(P30_C3_VGATOP_V_BOUNDARY_H) & 0xF0) << 4) | ScalerGetByte(P30_C4_VGATOP_V_BOUNDARY_STA_L)) + ucVdelayCount; // V start

            // Check auto-boundary H start
            if(pstActiveRegion->usHActiveStart == PDATA_WORD(0))
            {
                // Set H start = H_width + H_clamp_end + 2
                PDATA_WORD(0) -= 3;

                bWait = _WAIT;
            }

            // Check auto-boundary H end
            if(pstActiveRegion->usHActiveEnd == PDATA_WORD(1))
            {
                // Enlarge H R-Bounday delta = 1/2 noise margin width
                if(GET_INPUT_TIMING_H_POLARITY() == _TRUE)
                {
                    PDATA_WORD(1) += (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_POSITIVE * GET_A0_INPUT_PIXEL_CLK()) / 20000);
                }
                else
                {
                    PDATA_WORD(1) += (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_NEGTIVE * GET_A0_INPUT_PIXEL_CLK()) / 20000);
                }

                bWait = _WAIT;
            }

            // Check auto-boundary V start
            if(pstActiveRegion->usVActiveStart == PDATA_WORD(2))
            {
                if(ScalerGetBit(P30_AE_VGATOP_VGIP_HV_DELAY, (_BIT5 | _BIT4)) != 0x00)
                {
                    // Disable IVS delay when V porch region is too short
                    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~(_BIT5 | _BIT4), 0x00);
                    bWait = _WAIT;
                }
            }

            // Restart auto-function measure
            if(bWait == _WAIT)
            {
                // Adjust auto-function H boundary
                ScalerVgaTopAutoFuncHBoundInitial(PDATA_WORD(0), PDATA_WORD(1));

                // Restart auto-function measure
                ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);
                ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

                ++ucRepeatCount;
                continue;
            }
            else
            {
                break;
            }
        }

        break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Phase, MaxSOD, MinSOD Search
// Input Value  : enumPhaseStep --> Hardware Auto Search Phase Step
//                ucPhaseResult --> Best Phase(with Max SOD)
//                ulSODMax --> Max SOD Value
//                ulSODMin --> Min SOD Value
//                enumSODMethod --> SOD or WSOD Selection
// Output Value : True --> SOD Measurement ok, False --> SOD Measurement Fail
//--------------------------------------------------
bit ScalerVgaTopHWAutoPhaseSearch(EnumAutoPhaseSearchStep enumPhaseStep, BYTE *pucPhaseResult, DWORD *pulSODMax, DWORD *pulSODMin, EnumAutoPhaseSearchSODMethod enumSODMethod, BYTE ucSODThreshold)
{
    BYTE ucTargetPhase = 0;
    BYTE ucBestPhase = 0;
    BYTE ucPhaseStepNum = 0;
    DWORD ulSOD1st = 0;
    DWORD ulSOD2nd = 0;

    *pulSODMax = 0;

    *pulSODMin = 0xffffffff;

    // Set Difference Threshold
    ScalerSetByte(P30_C9_VGATOP_DIFF_THRESHOLD, ucSODThreshold);

    // Hardware Auto Measure Trigger Select to IVS, Initial Phase --> 0.
    ScalerSetByte(P30_CC_VGATOP_HW_AUTO_PHASE_CTRL1, 0x00);

    // Field Select Disable, LPF Disable, 1 pixel over Threshold, Enable Accelaration Mode, Select R or G or B Channel
    ScalerSetByte(P30_CA_VGATOP_AUTO_ADJ_CTRL0, 0x10);

    ucPhaseStepNum = (64 / (1 << enumPhaseStep));

    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
    {
        enumPhaseStep = enumPhaseStep + 1;
    }

    // Set Phase Step and Number
    ScalerSetByte(P30_CB_VGATOP_HW_AUTO_PHASE_CTRL0, (enumPhaseStep & 0x07) | (((ucPhaseStepNum - 1) & 0x1f) << 3));

    enumPhaseStep = (1 << enumPhaseStep);

    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    // Hardware Auto Measure Setting, and stop Auto-Function Measure Function, Start Measure
    ScalerSetByte(P30_CD_VGATOP_AUTO_ADJ_CTRL1, 0x7B);

    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    if(enumSODMethod == _PHASE_SEARCH_SOD)
    {
        do
        {
            if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
            {
                return _FALSE;
            }

            ScalerRead(P30_D4_VGATOP_AUTO_PHASE_3, 4, pData, _AUTOINC);

            if(PDATA_DWORD(0) > *pulSODMax)
            {
                *pulSODMax = PDATA_DWORD(0);
                ucBestPhase = ucTargetPhase;
            }

            if(PDATA_DWORD(0) < *pulSODMin)
            {
                *pulSODMin = PDATA_DWORD(0);
            }

            ucTargetPhase += enumPhaseStep;

            ucPhaseStepNum--;
        }
        while(ucPhaseStepNum > 0);
    }
    else
    {
        ucPhaseStepNum = ucPhaseStepNum + 2;

        PDATA_DWORD(1) = 0;
        PDATA_DWORD(2) = 0;
        PDATA_DWORD(3) = 0;

        do
        {
            PDATA_DWORD(3) = PDATA_DWORD(2);

            PDATA_DWORD(2) = PDATA_DWORD(1);

            if(ucPhaseStepNum == 2)
            {
                PDATA_DWORD(1) = ulSOD1st;
            }
            else if(ucPhaseStepNum == 1)
            {
                PDATA_DWORD(1) = ulSOD2nd;
            }
            else
            {
                if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
                {
                    return _FALSE;
                }

                ScalerRead(P30_D4_VGATOP_AUTO_PHASE_3, 4, pData, _AUTOINC);

                PDATA_DWORD(1) = PDATA_DWORD(0);

                if(ucTargetPhase == 0x00)
                {
                    ulSOD1st = PDATA_DWORD(0);
                }

                if(ucTargetPhase == enumPhaseStep)
                {
                    ulSOD2nd = PDATA_DWORD(0);
                }
            }

            if(PDATA_DWORD(2) > (ABSDWORD(PDATA_DWORD(3), PDATA_DWORD(2)) + ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))))
            {
                PDATA_DWORD(0) = PDATA_DWORD(2) - ((ABSDWORD(PDATA_DWORD(3), PDATA_DWORD(2)) + ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

                if(PDATA_DWORD(0) > *pulSODMax)
                {
                    *pulSODMax = PDATA_DWORD(0);

                    ucBestPhase = ucTargetPhase - enumPhaseStep;
                }
            }

            ucTargetPhase += enumPhaseStep;

            ucPhaseStepNum--;
        }
        while(ucPhaseStepNum > 0);
    }

    // Stop Hardware Auto-Function Measure
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT0), 0x00);

    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) != 0x00) // DotClock < _APLL_VCO_DEVIDER_4_2_THERSHOLD
    {
        *pucPhaseResult = ((ucBestPhase / 2) % 64);
    }
    else
    {
        *pucPhaseResult = (ucBestPhase % 64);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  : Firmware Auto Measure SOD Value
// Output Value : True --> Measure Success
//                False --> Measure Fail
//--------------------------------------------------
bit ScalerVgaTopAutoPhaseGetSOD(DWORD *pulSODValue)
{
    // Firmware Measure Setting, and stop Auto-Function Measure Function, Start Measure
    ScalerSetByte(P30_CD_VGATOP_AUTO_ADJ_CTRL1, 0x3B);

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        // Hw Auto Status Initial
        ScalerSetByte(P30_CD_VGATOP_AUTO_ADJ_CTRL1, 0x00);

        return _FALSE;
    }

    // Get Phase Result
    *pulSODValue = GET_AUTO_RESULT_DWORD();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumMeasureModeType --> Analog or Digital Mode Measure
//                EnumMeasureFieldSelect --> Measure for Even or Odd Field
//                EnumMeasureBoundType --> OverScan Boundary or Normal Boundary
//                usHTotal --> H Total
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerVgaTopMeasureActiveRegion(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal)
{
    ScalerVgaTopSetAuto(enumFieldSelect, enumBoundType, usHTotal);

    return (ScalerVgaTopGetAutoResult(&(g_pstRegionTimingInfoPointer->stAutoActiveData), _WAIT));
}

//--------------------------------------------------
// Description  : Waiting for Auto Function Measure Finish
// Input Value  : None
// Output Value : True --> Measure Finish
//                False --> Measure Timeout or Fail
//--------------------------------------------------
bit ScalerVgaTopAutoFuncWaitFinish(void)
{
    BYTE ucIvsCnt = 0;

    ucIvsCnt = (ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, _BIT1 | _BIT0) == 0x03) ? 3 : 1;
    ucIvsCnt = (ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, _BIT7) == _BIT7) ? ucIvsCnt * 2 : ucIvsCnt;
    ucIvsCnt += 2;

    do
    {
        if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT3)) != 0x00)
        {
            // Sync is changing
            return _FALSE;
        }

        if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerGetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            return _TRUE;
        }
    }
    while(--ucIvsCnt);

    if(ucIvsCnt == 0)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent)
{
    // Clear VGATOP event status
    ScalerSetBit(P30_E4_VGATOP_IRQ_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    return (ScalerTimerPollingFlagProc(60, P30_E4_VGATOP_IRQ_CTRL, enumEvent, _TRUE));
}

//--------------------------------------------------
// Description  : Apply double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopDoubleBufferApply(void)
{
    if(ScalerGetBit(P30_A0_VGATOP_VGIP_CTRL, _BIT4) != 0x00)
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT5, _BIT5);

        ScalerTimerPollingFlagProc(60, P30_A0_VGATOP_VGIP_CTRL, _BIT5, _FALSE);
    }
}

//--------------------------------------------------
// Description  : Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopDoubleBufferEnable(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Start
// Input Value  : None
// Output Value : V start
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureVStartPosition(void)
{
    return ((((ScalerGetByte(P30_A8_VGATOP_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P30_A9_VGATOP_IPV_ACT_STA_L)));
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V start
// Input Value  : usIVstart --> V start
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart)
{
    // Set VGATOP V capture start
    ScalerSetBit(P30_A8_VGATOP_IPV_ACT_STA_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usIVstart) & 0x0F));
    ScalerSetByte(P30_A9_VGATOP_IPV_ACT_STA_L, LOBYTE(usIVstart));


#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        ScalerFmtCnvFtoPSetFifo(GET_VGIP_INPUT_PATH(), (ScalerVgaTopGetCaptureHWidth() >> 1), (ScalerVgaTopGetCaptureVStartPosition() + 1));
    }
    else
#endif
    {
        ScalerFmtCnvFtoPSetFifo(GET_VGIP_INPUT_PATH(), ScalerVgaTopGetCaptureHWidth(), (ScalerVgaTopGetCaptureVStartPosition() + 1));
    }
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Height
// Input Value  : None
// Output Value : Capture V Height
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureVHeight(void)
{
    return ((((ScalerGetByte(P30_A8_VGATOP_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P30_AB_VGATOP_IPV_ACT_LEN_L)));
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V height
// Input Value  : usIVheight --> V height
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureVHeight(WORD usIVheight)
{
    // Set M1 V capture height
    ScalerSetBit(P30_A8_VGATOP_IPV_ACT_STA_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usIVheight) & 0x0F) << 4));
    ScalerSetByte(P30_AB_VGATOP_IPV_ACT_LEN_L, LOBYTE(usIVheight));
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Delay
// Input Value  : None
// Output Value : Capture V Delay
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureVDelay(void)
{
    return (((((WORD)(ScalerGetByte(P30_AE_VGATOP_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(P30_AC_VGATOP_IVS_DELAY)));
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V Delay
// Input Value  : usIVSDelay --> V Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay)
{
    // Set M1 capture V delay
    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~_BIT1, ((HIBYTE(usIVSDelay) & _BIT0) << 1));
    ScalerSetByte(P30_AC_VGATOP_IVS_DELAY, LOBYTE(usIVSDelay));
}

//--------------------------------------------------
// Description  : Get VGATOP Capture H-Start Position
// Input Value  : None
// Output Value : Capture H Start
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureHStartPosition(void)
{
    return ((((ScalerGetByte(P30_A4_VGATOP_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P30_A5_VGATOP_IPH_ACT_STA_L)) + 2);
}

//--------------------------------------------------
// Description  : Set VGATOP Capture H start
// Input Value  : usIHstart --> H start
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart)
{
    usIHstart -= 2;

    // Set M1 H capture start
    ScalerSetBit(P30_A4_VGATOP_IPH_ACT_STA_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usIHstart) & 0x0F));
    ScalerSetByte(P30_A5_VGATOP_IPH_ACT_STA_L, LOBYTE(usIHstart));
}

//--------------------------------------------------
// Description  : Get VGATOP Capture H width
// Input Value  : None
// Output Value : VGATOP H width
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureHWidth(void)
{
    return ((((WORD)ScalerGetByte(P30_A4_VGATOP_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P30_A7_VGATOP_IPH_ACT_WID_L));
}

//--------------------------------------------------
// Description  : Set VGATOP Capture H width
// Input Value  : usIHwidth --> H width
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth)
{
    // Set M1 H capture width
    ScalerSetBit(P30_A4_VGATOP_IPH_ACT_STA_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usIHwidth) & 0x0F) << 4));
    ScalerSetByte(P30_A7_VGATOP_IPH_ACT_WID_L, LOBYTE(usIHwidth));

    // Set format conversion related blocks
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        ScalerFmtCnvFBSetOutputFormat(usIHwidth, (_VGIP_IH_CAPTURE_MIN_VALUE / 2), 0x08);
    }
#endif

    // Set main F-to-P FIFO
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        ScalerFmtCnvFtoPSetFifo(GET_VGIP_INPUT_PATH(), (usIHwidth >> 1), (ScalerVgaTopGetCaptureVStartPosition() + 1));
    }
    else
#endif
    {
        ScalerFmtCnvFtoPSetFifo(GET_VGIP_INPUT_PATH(), usIHwidth, (ScalerVgaTopGetCaptureVStartPosition() + 1));
    }
}

//--------------------------------------------------
// Description  : Get VGATOP Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureHDelay(void)
{
    return ((((WORD)ScalerGetByte(P30_AE_VGATOP_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(P30_AE_VGATOP_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(P30_AD_VGATOP_IHS_DELAY));
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay)
{
    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~(_BIT2 | _BIT0), (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));
    ScalerSetByte(P30_AD_VGATOP_IHS_DELAY, LOBYTE(usIHSDelay));
}

//--------------------------------------------------
// Description  : Set VGATOP capture start & size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCapture(void)
{
    WORD usVgaTopVstartLimit = (DWORD)_PANEL_DV_START * GET_INPUT_TIMING_VHEIGHT() / _PANEL_DV_HEIGHT + 2;

    if(usVgaTopVstartLimit < _VGIP_IV_CAPTURE_MIN_VALUE)
    {
        usVgaTopVstartLimit = _VGIP_IV_CAPTURE_MIN_VALUE;
    }

    // Store mode table H/V start
    SET_VGA_MODE_HSTART(GET_INPUT_TIMING_HSTART());
    SET_VGA_MODE_VSTART(GET_INPUT_TIMING_VSTART());

    // Modify timing info
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        SET_INPUT_TIMING_HSTART((_VGIP_IH_CAPTURE_MIN_VALUE + 2) * 2);
    }
    else
#endif
    {
        if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
        {
            SET_INPUT_TIMING_HSTART(_VGIP_IH_CAPTURE_MIN_VALUE + 2);
        }
        else
        {
            SET_INPUT_TIMING_HSTART(_VGIP_IH_CAPTURE_MIN_VALUE + 1);
        }
    }

    SET_INPUT_TIMING_VSTART(usVgaTopVstartLimit);

    // Set VGATOP capture window
    ScalerVgaTopSetCaptureHWidth(GET_INPUT_TIMING_HWIDTH());
    ScalerVgaTopSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());
    ScalerVgaTopSetCaptureHStartPosition(GET_INPUT_TIMING_HSTART());

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        ScalerVgaTopSetCaptureVStartPosition(usVgaTopVstartLimit + 3);
    }
    else
    {
        ScalerVgaTopSetCaptureVStartPosition(usVgaTopVstartLimit + 1);
    }
}

//--------------------------------------------------
// Description  : Find metastable phase for current APLL rate
// Input Value  : None
// Output Value : current HS delay value (0.01ns * 64)
//--------------------------------------------------
WORD ScalerVgaTopSearchHsEdge(void)
{
    BYTE ucCurrPhase = 0;
    BYTE ucTargetPhase = 0xFF;
    DWORD ulMax = 0;

    // Stop auto-function; HW auto; Measure min; Accumulation
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT4 | _BIT0), (_BIT6 | _BIT4));

    // Set VGIP latch edge
    SET_HS_DELAY_LATCH_EDGE();

    if(ScalerGetBit(P30_A0_VGATOP_VGIP_CTRL, _BIT4) == _BIT4)
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT5, _BIT5);
    }

    // Enable VGATOP pattern gen to output 0;
    ScalerSetByte(P30_DF_VGATOP_PAT_GEN_RED_INI_L, 0x00);
    ScalerSetByte(P30_E0_VGATOP_PAT_GEN_GRN_INI_L, 0x00);
    ScalerSetByte(P30_E1_VGATOP_PAT_GEN_BLU_INI_L, 0x00);
    ScalerSetByte(P30_E2_VGATOP_PAT_GEN_INI_H, 0x00);

    // Set auto-balance old mode
    ScalerSetByte(P30_C6_VGATOP_RED_NOISE_MARGIN, 0x40);

    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
    {
        // Set phase step = 32, step size = 2
        ScalerSetByte(P30_CB_VGATOP_HW_AUTO_PHASE_CTRL0, 0xF9);
    }
    else
    {
        // Set phase step = 32, step size = 1
        ScalerSetByte(P30_CB_VGATOP_HW_AUTO_PHASE_CTRL0, 0xF8);
    }

    // Set auto function boundary to max
    ScalerVgaTopAutoFuncHBoundInitial((ScalerGetWord(P1_B1_PLLDIV_H) & 0x0FFF), 0x0FFF);
    ScalerVgaTopAutoFuncVBoundInitial(0x0000, 0x0FFF);

    // for each phase
    for(ucCurrPhase = 0; ucCurrPhase < 64; ++ucCurrPhase)
    {
        if((ucCurrPhase == 0) || (ucCurrPhase == 32))
        {
            // Stop auto-function
            ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

            if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
            {
                break;
            }

            // Set initial phase
            if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
            {
                ScalerSetByte(P30_CC_VGATOP_HW_AUTO_PHASE_CTRL1, (ucCurrPhase << 1));
            }
            else
            {
                ScalerSetByte(P30_CC_VGATOP_HW_AUTO_PHASE_CTRL1, ucCurrPhase);
            }

            // Start auto-function
            ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

            if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
            {
                break;
            }
        }

        if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
        {
            break;
        }

        // Pop out result
        PDATA_DWORD(0) = (*((volatile DWORD xdata *)(P30_D4_VGATOP_AUTO_PHASE_3)));

        if(PDATA_DWORD(0) > ulMax)
        {
            ulMax = PDATA_DWORD(0);
            ucTargetPhase = ucCurrPhase;
        }
    }

    // Stop auto-function; Disable HW auto
    ScalerSetBit(P30_CD_VGATOP_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT0), 0x00);

    ucTargetPhase = (ucTargetPhase + _PHASE_DELAY_HALF_PERIOD_SHIFT) % 64;

    DebugMessageAnalog("meta edge", ucTargetPhase);

    // Calculate HS delay (unit: 1/64 ns)
    if(ulMax == 0x00)
    {
        return ~0;
    }
    else
    {
        return (WORD)((DWORD)10000 * ucTargetPhase / GET_A0_INPUT_PIXEL_CLK());
    }
}

//--------------------------------------------------
// Description  : HS delay Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopModifyHsLatchEdgeDelay(void)
{
    BYTE pucBackup[8] = {0};
    BYTE ucLoop = 0;

    if(g_usPhaseDelayTime != 0x00)
    {
        // HS delay already calibrated
        DebugMessageAnalog("HS Delay Value", g_usPhaseDelayTime);
        return;
    }

    /////////////////////////////////////////////////////////////////////////
    // 1. Initial Display format/APLL/VGIP
    /////////////////////////////////////////////////////////////////////////

    // Backup Display format gen setting
    SAVE_HS_DELAY_SETTING(pucBackup);

    // Disable DPLL spread spectrum if enabled
    ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _OFF);

    // Set new DVtotal; Update last line = DHtotal
    SET_FREE_RUN_DVTOTAL((WORD)_HS_DELAY_DVTOTAL);
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, HIBYTE((WORD)_HS_DELAY_DHTOTAL - 4));
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_33_FIXED_LAST_LINE_LSB, LOBYTE((WORD)_HS_DELAY_DHTOTAL - 4));

    // Set new DHtotal
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, HIBYTE((WORD)_HS_DELAY_DHTOTAL - 4));
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_01_DISPLAY_HOR_TOTAL_L, LOBYTE((WORD)_HS_DELAY_DHTOTAL - 4));
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END, 0x08);

    // ADC LDO Power On, ADC Clock Power On, SOG_ADC0 Power On, R/G/B ADC Power On
    // ADC ldo Output Not Short to Ground
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Disable ADC power saving mode
    ScalerSetBit(P0_C7_ADC_VOLT_SEL, ~_BIT2, 0x00);

    // Reset ADC clock delay
    ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), 0x00);

    // Adc output clock setting
    ScalerADCOutputClkSetting();

    // Switch sync-processor HS/VS source from D-domain; Bypass HS output
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT1, _BIT1);
    ScalerSetByte(P0_47_SYNC_SELECT, _BIT2);
    ScalerSetByte(P0_48_SYNC_INVERT, _BIT4);
    ScalerSetByte(P0_49_SYNC_CTRL, (_BIT2 | _BIT1));

    // Enable I-domain pattern gen; Disable double buffer; Enable ADC input;
    ScalerSetByte(P30_A0_VGATOP_VGIP_CTRL, (_BIT7 | _BIT0));

    // Set VGATOP capture to max
    ScalerVgaTopSetCaptureHStartPosition(0x0000);
    ScalerVgaTopSetCaptureVStartPosition(0x0000);
    ScalerVgaTopSetCaptureHWidth(0x0FFF);
    ScalerVgaTopSetCaptureVHeight(0x0FFF);

    // Load default value
#if(_PHASE_DELAY_TIME_VALUE >= 0)
    g_usPhaseDelayTime = _PHASE_DELAY_TIME_VALUE;
#else
    g_usPhaseDelayTime = -(_PHASE_DELAY_TIME_VALUE);
#endif

    /////////////////////////////////////////////////////////////////////////
    // 2. Detect HS/clock meta-stability
    /////////////////////////////////////////////////////////////////////////

    // Set APLL clock to target freq. by calculating IHtotal
    if(ScalerAPLLAdjust(_HS_DELAY_IHTOTAL, _HS_DELAY_REAL_DHFREQ) == _TRUE)
    {
        // Detect HS meta-stable
        while((ucLoop++) <= 3)
        {
            if((PDATA_WORD(0) = ScalerVgaTopSearchHsEdge()) != ~0)
            {
                g_usPhaseDelayTime = PDATA_WORD(0);

                DebugMessageAnalog("HS edge found", g_usPhaseDelayTime);

                // Calculate current pixel clock period
                PDATA_WORD(0) = (WORD)((DWORD)640000 / GET_A0_INPUT_PIXEL_CLK()); // 1T

#if(_PHASE_DELAY_TIME_VALUE >= 0)

                // Check whether HS delay over 1T
                if(abs(PDATA_WORD(0) + g_usPhaseDelayTime - _PHASE_DELAY_TIME_VALUE) < abs(g_usPhaseDelayTime - _PHASE_DELAY_TIME_VALUE))
                {
                    g_usPhaseDelayTime += PDATA_WORD(0);
                }

#else

                // Calculate negative HS delay
                g_usPhaseDelayTime = PDATA_WORD(0) - g_usPhaseDelayTime;

                // Check whether HS delay over 1T
                if(abs(PDATA_WORD(0) + g_usPhaseDelayTime - (-(_PHASE_DELAY_TIME_VALUE))) < abs(g_usPhaseDelayTime - (-(_PHASE_DELAY_TIME_VALUE))))
                {
                    g_usPhaseDelayTime += PDATA_WORD(0);
                }

#endif
                break;
            }

            // Adjust ADC clock delay
            ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), (ucLoop << 3));
        }
    }

    /////////////////////////////////////////////////////////////////////////
    // 3. Restore default setting
    /////////////////////////////////////////////////////////////////////////

    // Disable VGIP
    ScalerSetByte(P30_A0_VGATOP_VGIP_CTRL, 0x00);

    // Set sync processsor HS/VS source from ADC
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT2, 0x00);
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT1, 0x00);

    // Reset ADC power saving mode
    ScalerSetBit(P0_C7_ADC_VOLT_SEL, ~_BIT2, _BIT2);

    // Power down ADC VCM/ADC clock/SOG Power/RGB Channel
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset ADC clock delay
    ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), 0x00);

    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // Load DPLL setting
    LOAD_HS_DELAY_SETTING(pucBackup);

#if(_PHASE_DELAY_TIME_VALUE >= 0)
    DebugMessageAnalog("Positive HS Delay Calibrated", g_usPhaseDelayTime);
#else
    DebugMessageAnalog("Negative HS Delay Calibrated", g_usPhaseDelayTime);
#endif
}

#endif // End of #if(_VGA_SUPPORT == _ON)

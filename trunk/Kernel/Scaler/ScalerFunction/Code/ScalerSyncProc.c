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
// ID Code      : ScalerSyncProc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_SYNCPROC__

#include "ScalerFunctionInclude.h"

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of V-Sync width & total limitations
//--------------------------------------------------
#define _MAX_VSYNC_TOTAL                            (1646 * 1.1)  // 2560x1600@60 + 10%
#define _MIN_VSYNC_TOTAL                            (262 * 0.9)   // 1440x480i - 10%
#define _MAX_VSYNC_HIGH_PERIOD                      12 // Unit capture window

//--------------------------------------------------
// Definitions of Debounce Width And High Pulse Width Counter
//--------------------------------------------------
#define _MIN_SYNC_HIGHPULSE_WIDTH                   173 // Unit ns, Represent the shortest high pulse width
#define _MIN_SYNC_HIGHPULSE_CNT                     (((WORD)((DWORD)_MIN_SYNC_HIGHPULSE_WIDTH * _SYNC_PROC_CLK / 1000000)) & 0x7FF)
#define _MIN_SYNC_HIGHPULSE_CNT_PS                  (((WORD)((DWORD)_MIN_SYNC_HIGHPULSE_WIDTH * _INTERNAL_OSC_XTAL / (0x01 << _IOSC_DIV) / 1000000)) & 0x7FF)

//--------------------------------------------------
// Definitions Of Capture window initial width tolerance
//--------------------------------------------------
#define _CAP_WINDOW_WIDTH_TOR                       2 // Unit: sync processor clock

//--------------------------------------------------
// Definitions Of Sync Processor Auto Run Polling Time, Target 120ms
// Auto Run Typer Time Out Base Counter(0x200000) Reference 27M Crystal About 80ms:                                                                            //
// 120 = 80 + 40(Tolerance), _XTAL27000K / _MCU_XTAL Is Linear Operator
//--------------------------------------------------
#define _AUTO_RUN_POLLING_TIME                      ((WORD)((DWORD)120 * _XTAL27000K / _SYNC_PROC_CLK))

//--------------------------------------------------
// Definitions Of Clamp Position in Pixel clock unit
//--------------------------------------------------
#define _CLAMP_POSITION_START                       0x04
#define _CLAMP_POSITION_END                         0x10

//--------------------------------------------------
// Definitions Of Min/Max H-Sync Freq, Normal Range (15.625, 112.5) Unit:KHz
//--------------------------------------------------
#define _SUPPORT_HSYNC_MIN_FREQ                     10  // + Torlerance
#define _SUPPORT_HSYNC_MAX_FREQ                     150 // + Torlerance

//--------------------------------------------------
// Definitions Of SOG middle compare level & shift range
//--------------------------------------------------
#define _SOG_MID_COMPARE_LEVEL                      (0x16)
#define _SOG_MID_COMPARE_RANGE                      (0x02)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Enumerations of Hsync Type Detection Auto Run Result
//--------------------------------------------------
typedef enum
{
    _NO_SIGNAL = 0,
    _NOT_SUPPORT = 1,
    _YPBPR_SYNC = 2,
    _SERRATION_CS = 3,
    _XOR_OR_TYPE_CS_WITH_EQR = 4,
    _XOR_OR_TYPE_CS_WITHOUT_EQR = 5,
    _SEPARATE_HSYNC = 6,
    _HSYNC_WITHOUT_VS = 7,
} EnumAutoRunResult;

#if(_SOG_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of SyncProc/AutoFunc Measure Mode
//--------------------------------------------------
typedef enum
{
    _SOG_LEVEL_VALID,
    _SOG_LEVEL_INVALID,
    _SOG_LEVEL_FAIL,
} EnumSogLevelSearchResult;
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usAdcClockLimit = _ADC_PIXEL_WIDTH_LIMIT;

#if(_SOG_SUPPORT == _ON)
BYTE g_ucSogMidLevel = _SOG_MID_COMPARE_LEVEL;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerSyncProcScanInitial(void);
bit ScalerSyncProcPreDetect(void);
bit ScalerSyncProcStableDetect(void);
bit ScalerSyncProcGetSyncPad(void);
void ScalerSyncProcAdcInitial(void);
void ScalerSyncProcInitial(void);
bit ScalerSyncProcHSSyncStableDetect(void);
bit ScalerSyncProcStableCheck(void);
WORD ScalerSyncProcGetDeVsyncWidth(void);
BYTE ScalerSyncProcTypeAutoRun(void);
bit ScalerSyncProcAdcClkInitial(void);
bit ScalerSyncProcAdcClkSetting(void);

void ScalerSyncProcClampPosCheck(BYTE ucVideoModeFlg);
void ScalerSyncProcClampPosSetting(WORD usClampPosStart, WORD usClampPosEnd);
WORD ScalerSyncProcGetClampEndPosition(void);
void ScalerSyncProcClearSyncChangeStatus(void);
WORD ScalerSyncProcMeasureIHFreqByStableMeasure(void);
void ScalerSyncProcPulseDetectEnable(BYTE ucEnable);
void ScalerSyncProcSetDebounce(BYTE ucDebounce);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
void ScalerSyncProcSetPorchVoltage(void);
bit ScalerSyncProcCheckPorchChange(void);
#endif

void ScalerSyncProcDownCounterSetting(void);
DWORD ScalerSyncProcGetCurrentClockFreq(void);

#if(_SOG_SUPPORT == _ON)
EnumSogLevelSearchResult ScalerSyncProcSogCheckFlag(void);
EnumSogLevelSearchResult ScalerSyncProcSogCheckHs(StructMeasureSyncData *pstMeasureSyncHV);
EnumSogLevelSearchResult ScalerSyncProcSogCheckVs(StructMeasureSyncData *pstMeasureSyncHV);
EnumSogLevelSearchResult ScalerSyncProcSogCheckSyncType(void);
void ScalerSyncProcSetSogCompareLevel(BYTE *pucLevels);
bit ScalerSyncProcSogSyncCheck(void);
bit ScalerSyncProcRecheckSOGSyncStable(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Initial Setting for VGA Scanning Port(Power Normal)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcScanInitial(void)
{
    // ADC Initial Setting
    ScalerSyncProcAdcInitial();

    // Sync Processor Initial Setting
    ScalerSyncProcInitial();

    // ADC Schmitt Trigger Setting
    ScalerADCSchmittTriggerSetting();

    // Initial ADC data to VGIP path swap setting.
    ScalerSetBit(P30_A6_VGATOP_IPH_ACT_WID_H, ~(_BIT6 | _BIT5 | _BIT4), ((_VGA_INPUT_SWAP_GB << 6) | (_VGA_INPUT_SWAP_RB << 5) | (_VGA_INPUT_SWAP_RG << 4)));
}

//--------------------------------------------------
// Description  : Signal PreDetection for VGA(Power Normal)
// Input Value  : None
// Output Value : True : VGA Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerSyncProcPreDetect(void)
{
    // Debounce counter reference 14.318MHz sync process clock, minimum pulse width is 171ns
    // n / 14.318 / 1000 = 171 => n = 2
    ScalerSyncProcSetDebounce(0x02);

    // Enable sync pulse detect
    ScalerSyncProcPulseDetectEnable(_ENABLE);

    // Clamp trigger edge and clamp setting for initial setting
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_04_CLAMP_CTRL0, 0x02);
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, 0x01);

    if(ScalerSyncProcHSSyncStableDetect() == _TRUE)
    {
        if(ScalerSyncProcStableCheck() == _TRUE)
        {
            return _TRUE;
        }
    }
    else
    {
        // Inverse CS_RAW signal for repeat check status
        ScalerSetBit(P0_48_SYNC_INVERT, ~_BIT3, ((~(ScalerGetBit(P0_48_SYNC_INVERT, _BIT3))) & _BIT3));

        if(ScalerSyncProcHSSyncStableDetect() == _TRUE)
        {
            if(ScalerSyncProcStableCheck() == _TRUE)
            {
                return _TRUE;
            }
        }
    }

#if(_SOG_SUPPORT == _ON)
    // Enable DC Restore
    ScalerADCDCRestoreEn(_ENABLE);

    // SOG power up
    ScalerSetBit(P0_C6_ADC_POWER, ~_BIT5, _BIT5);

    // Wait for SOG Stable
    ScalerTimerDelayXms(5);

    if(ScalerSyncProcSogSyncCheck() == _TRUE)
    {
        if(ScalerSyncProcStableCheck() == _TRUE)
        {
            if(ScalerSyncProcRecheckSOGSyncStable() == _TRUE)
            {
                // Sync is valid
                return _TRUE;
            }
        }
    }

    // Disable DC Restore
    ScalerADCDCRestoreEn(_DISABLE);

    // SOG power down
    ScalerSetBit(P0_C6_ADC_POWER, ~_BIT5, 0x00);

    // Disable De-composite circuit
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT5, 0x00);

#endif // End of #if(_SOG_SUPPORT == _ON)

    // Disable sync pulse detect
    ScalerSyncProcPulseDetectEnable(_DISABLE);

    // Disable SyncProc Clock
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);

    return _FALSE;
}

//--------------------------------------------------
// Description  : On Line Check VGA sync stability
// Input Value  : None
// Output Value : True --> VGA Sync Stable
//                False --> VGA Sync Unstable
//--------------------------------------------------
bit ScalerSyncProcStableDetect(void)
{
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, 0x00);

    if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT3)) != 0x00)
    {
        return _FALSE;
    }
    else
    {
#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
        // Check porch voltage level change for chroma pattern 12
        if(ScalerSyncProcCheckPorchChange() == _TRUE)
        {
            // Toggle "Clamp-to-Top" status
            ScalerADCSetClampToTopStatus(~(ScalerADCGetClampToTopStatus()));

            DebugMessageAnalog("Toggle clamp-to-top status", ScalerADCGetClampToTopStatus());
        }
#endif
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Get VGA Sync Pad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSyncProcGetSyncPad(void)
{
    return (bit)(ScalerGetBit(P0_47_SYNC_SELECT, _BIT4));
}

//--------------------------------------------------
// Description  : ADC Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcAdcInitial(void)
{
    // Adc output clock setting
    ScalerADCOutputClkSetting();

    // ADC Power control setting
    ScalerADCPowerSetting();

    // ADC bias current setting
    ScalerADCBiasCurrentSetting();

    // ADC select differential signal
    ScalerSetBit(P0_BB_ADC_CK_IN_CTRL, ~_BIT7, _BIT7);

    // ADC offset Depend On Gain, Red Clamp Voltage 400mV
    ScalerSetBit(P0_CF_ADC_CTL_RED, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

    // ADC offset Depend On Gain, Green Clamp Voltage 400mV
    ScalerSetBit(P0_D0_ADC_CTL_GRN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

    // ADC offset Depend On Gain, Blue Clamp Voltage 400mV
    ScalerSetBit(P0_D1_ADC_CTL_BLU, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

    // Enable DC Restore
    ScalerADCDCRestoreEn(_ON);

    // Disable SOG Clamp
    ScalerADCSOGClampEn(_OFF);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
    // Disable Clamp to Top
    ScalerSetBit(P0_D6_ADC_CLAMP_TOP, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

    // Nit7~Bit6: SOG DC restore resister is 1M
    // Bit3: SOG0 Bias Current from ADC BandGap
    // Bit0: Bias Current of SOG normal
    ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT0), (_BIT7 | _BIT3));

    // Vcck for power on
    ScalerSetBit(P0_C7_ADC_VOLT_SEL, ~_BIT2, 0x00);
}

//--------------------------------------------------
// Description  : ADC Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcInitial(void)
{
    // SOG Source Select to SOG0, VGA-ADC HS/VS Source Select to Original HS/VS of ADC Source
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT3 | _BIT2), 0x00);

    // G Clamp Position default Setting
    ScalerSyncProcClampPosSetting(_CLAMP_POSITION_START, _CLAMP_POSITION_END);

    // Clamp position unit: Single ADC clock
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_06_CLAMP_CTRL2, 0x30);

    // Coast Setting for Front porch default condition: +2/-1
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_07_COAST_CTRL, 0x21);

    // Capture window max missing times & Capture auto increase step & Capture window initial width.
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_08_CAPTURE_WINDOW_SETTING, 0x00);

    // Bit6: Measure Time Clock = 4096 Xtal, Measure source select capture window
    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_18_SYNC_PROCESSOR_TEST_MODE, ~(_BIT6 | _BIT3), (_BIT6 | _BIT3));
}

//--------------------------------------------------
// Description  : Sync Processor Detect H/V Sync Stable for SS/CS
// Input Value  : None
// Output Value : True --> HV Stable
//                False --> HV Not Stable
//--------------------------------------------------
bit ScalerSyncProcHSSyncStableDetect(void)
{
    BYTE ucCirCleCnt = 5;
    BYTE ucCnt = 0;
    WORD usHSyncPeriod = 0;
    WORD usHSyncPulseCount = 0;

    do
    {
        ucCirCleCnt--;

        // Clear flag
        ScalerSetBit(P0_5B_HS_DETECT, ~_BIT7, _BIT7);

        // For SOG Power Stable, Refernce H-Freq = 15.63k, Delay time about 4 H-Sync Period
        for(ucCnt = 0; ucCnt <= 50; ucCnt++)
        {
            Delay5us(g_ucDelay5usN);
        }

        if(ScalerGetBit(P0_5B_HS_DETECT, _BIT7) == _BIT7)
        {
            continue;
        }
        else
        {
            break;
        }
    }while(ucCirCleCnt > 0);

    if(ucCirCleCnt != 0)
    {
        return _FALSE;
    }

    // Enable Sync Processor Clock
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT0), 0x00);

    // HS_OUT Signal Output Enable, HS Out not invert
    ScalerSetBit(P0_48_SYNC_INVERT, ~(_BIT5 | _BIT4), _BIT4);

    // HS_OUT by pass mode, Measure Source is ADC_HS1/ADC_VS, H Sync measure source is original hs
    ScalerSetByte(P0_49_SYNC_CTRL, 0x06);

    // Sync from HS Pad
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT4, 0x00);

    // Start Stable Period Measure
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, 0x00);
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, _BIT0);

    if(ScalerTimerPollingFlagProc(12, P0_4F_STABLE_MEASURE, _BIT7, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up stable result
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

    usHSyncPeriod = ((WORD)(ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_51_STABLE_PERIOD_L);
    usHSyncPulseCount = ((WORD)(ScalerGetByte(P0_4A_STABLE_HIGH_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_4B_STABLE_HIGH_PERIOD_L);

    if(ScalerGetBit(P0_4F_STABLE_MEASURE, _BIT6) == 0x00) // HS Negative
    {
        usHSyncPulseCount = (usHSyncPeriod - usHSyncPulseCount);
    }

    if(((usHSyncPulseCount * 7) < usHSyncPeriod) && (usHSyncPulseCount >= _MIN_SYNC_HIGHPULSE_CNT_PS))
    {
        if(ScalerTimerPollingFlagProc(_WAIT_TWO_FRAME_TIME, P0_4E_HSYNC_TYPE_DETECTION_FLAG, _BIT4, _TRUE) == _TRUE) // Saperate signal
        {
            return _TRUE;
        }

#if(_VGA_COMPOSITE_SUPPORT == _ON)
        if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, _BIT1) == _BIT1) // Composite signal, this bit need waitting for one frame
        {
            return _TRUE;
        }
#endif // End of #if(_VGA_COMPOSITE_SUPPORT == _ON)
    }

    return _FALSE;
}


//--------------------------------------------------
// Description  : VGA Sync Stable Measure Check 3 times
// Input Value  : None
// Output Value : True --> Sync Stable
//                False --> Sync Unstable
//--------------------------------------------------
bit ScalerSyncProcStableCheck(void)
{
    BYTE ucCheckTimes = 3;

    do
    {
        ucCheckTimes--;

        // Start Stable Period Measure
        ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, 0x00);
        ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, _BIT0);

        if(ScalerTimerPollingFlagProc(12, P0_4F_STABLE_MEASURE, _BIT7, _TRUE) == _TRUE)
        {
            continue;
        }
        else
        {
            return _FALSE;
        }

    }while(ucCheckTimes > 0);

    // Down Counter Setting
    ScalerSyncProcDownCounterSetting();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get DeVS Width
// Input Value  : None
// Output Value : DeVs Width (unit : line)
//--------------------------------------------------
WORD ScalerSyncProcGetDeVsyncWidth(void)
{
    // Pop Up De-VS High Pulse Width
    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_0A_DEVS_CAP_NUM_H, ~_BIT7, _BIT7);

    ScalerSetByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_0A_DEVS_CAP_NUM_H);
    PDATA_WORD(7) = ((ScalerGetByte(P0_5D_SYNC_PROC_PORT_DATA) & 0x0F) << 8) | ScalerGetByte(P0_5D_SYNC_PROC_PORT_DATA);

    DebugMessageAnalog("DeVS high Pulse Width Check =", PDATA_WORD(7));

    return PDATA_WORD(7);
}

//--------------------------------------------------
// Description  : VGA Sync Type Detect AutoRun
// Input Value  : None
// Output Value : Sync Type
//--------------------------------------------------
BYTE ScalerSyncProcTypeAutoRun(void)
{
    BYTE ucSyncTemp = _NO_SYNC_STATE;

    if(ScalerGetBit(P0_47_SYNC_SELECT, _BIT7) == _BIT7)
    {
        return ucSyncTemp;
    }

    // Stop Stable Measure
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, 0x00);

    // Disable Hsync Type Detection Auto Run, Disable De-Composite
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT6 | _BIT5), 0x00);

    // Enable Hsync Type Detection Auto Run
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT6, _BIT6);

    // Check the result of Auto Run
    // 120ms need change by current clock in future, by macro
    if(ScalerTimerPollingFlagProc(_AUTO_RUN_POLLING_TIME, P0_4C_VSYNC_COUNTER_LEVEL_MSB, _BIT7, _TRUE) == _FALSE)
    {
        return ucSyncTemp;
    }

    switch((ScalerGetBit(P0_4C_VSYNC_COUNTER_LEVEL_MSB, 0xff) & 0x70) >> 4)
    {
        case _NO_SIGNAL: // No Signal
        case _NOT_SUPPORT: // Not Support
        case _HSYNC_WITHOUT_VS: // Hsync only
            ucSyncTemp = _NO_SYNC_STATE;

            break;

#if (_YPBPR_SUPPORT == _ON)
        case _YPBPR_SYNC: // YPbPr-Type CS
            ucSyncTemp = _SOY_STATE;

            break;
#endif // End of #if (_YPBPR_SUPPORT == _ON)

        case _SERRATION_CS: // Serration-Type CS
            ucSyncTemp = _CS_STATE;

            break;

        case _XOR_OR_TYPE_CS_WITH_EQR: // CS with Equalizer
        case _XOR_OR_TYPE_CS_WITHOUT_EQR: // OR-Type & XOR-Type CS

            // Pop Up Stable Value
            ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

            PDATA_WORD(1) = ((((WORD)(ScalerGetByte(P0_4A_STABLE_HIGH_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_4B_STABLE_HIGH_PERIOD_L)) + 1);

            PDATA_WORD(1) += _CAP_WINDOW_WIDTH_TOR;

            if(PDATA_WORD(1) <= 0x1F)
            {
                ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_08_CAPTURE_WINDOW_SETTING, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), PDATA_WORD(1));
            }

            ucSyncTemp = _CS_STATE;

            break;

        case _SEPARATE_HSYNC: // Separate Sync

            // Disable Coast Output in separate sync typer.
            ScalerSetBit(P0_48_SYNC_INVERT, ~_BIT6, 0x00);

            ucSyncTemp = _SS_STATE;

            break;

        default:
            ucSyncTemp = _NO_SYNC_STATE;

            break;
    }

    if(ucSyncTemp == _SOY_STATE)
    {
        SET_COLOR_SPACE(_A0_INPUT_PORT, _COLOR_SPACE_YPBPR);
    }
    else
    {
        SET_COLOR_SPACE(_A0_INPUT_PORT, _COLOR_SPACE_RGB);
        SET_COLOR_RGB_QUANTIZATION_RANGE(_A0_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);
    }

    if(ucSyncTemp != _NO_SYNC_STATE)
    {
        // Fix color depth to 8 bit mode under vga source
        SET_COLOR_DEPTH(_A0_INPUT_PORT, _COLOR_DEPTH_8_BITS);
    }

    return ucSyncTemp;
}

//--------------------------------------------------
// Description  : ADC Clock Initial before mode search
// Input Value  : None
// Output Value : True --> Success
//                False --> Error
//--------------------------------------------------
bit ScalerSyncProcAdcClkInitial(void)
{
    WORD usIHFreq = 0;
    WORD usIHTotal = 0;

    usIHFreq = ((WORD)((_SYNC_PROC_CLK * 10 * 2 / (((WORD)(ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_51_STABLE_PERIOD_L)) + 1) / 2));

    usIHTotal = (WORD)(((DWORD)_ADC_SAMPLE_CLOCK_LIMIT / usIHFreq / 4) * 4);

    if(usIHTotal > _ADC_PIXEL_WIDTH_LIMIT)
    {
        usIHTotal = _ADC_PIXEL_WIDTH_LIMIT;
    }

    g_usAdcClockLimit = usIHTotal;

    ScalerADCBandWidthSetting(((DWORD)usIHFreq * (DWORD)usIHTotal) / 10000);

    if(ScalerAPLLAdjust(usIHTotal, usIHFreq) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : ADC Clock Setting After mode search
// Input Value  : None
// Output Value : True --> Success
//                False --> Error
//--------------------------------------------------
bit ScalerSyncProcAdcClkSetting(void)
{
    ScalerADCBandWidthSetting(((DWORD)GET_INPUT_TIMING_HFREQ() * (DWORD)GET_INPUT_TIMING_HTOTAL()) / 10000);

    if(ScalerAPLLAdjust(GET_INPUT_TIMING_HTOTAL(), GET_INPUT_TIMING_HFREQ()) == _FALSE)
    {
        return _FALSE;
    }

    // Coast Setting for progressive mode: +1/-1
    if(GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE)
    {
        ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_07_COAST_CTRL, 0x11);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Clamp Position Check avoid BP too short.
// Input Value  : ucVideoModeFlg --> Video Mode flag type
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcClampPosCheck(BYTE ucVideoModeFlg)
{
    WORD usClampPosStart = 0;
    WORD usClampPosEnd = 0;

    switch(ucVideoModeFlg)
    {
        case 0x10: // _VIDEO_MODE_GROUP1:

            usClampPosStart = 0x08;
            usClampPosEnd = 0x16;

#if (_YPBPR_SUPPORT == _ON)
            SET_COLOR_SPACE(_A0_INPUT_PORT, _COLOR_SPACE_YPBPR);
#endif
            break;

        case 0x20: // _VIDEO_MODE_GROUP2:

            usClampPosStart = 0x30;
            usClampPosEnd = 0x38;

#if (_YPBPR_SUPPORT == _ON)
            SET_COLOR_SPACE(_A0_INPUT_PORT, _COLOR_SPACE_YPBPR);
#endif
            break;

        case 0x80: // _VIDEO_MODE_GROUP3:

            usClampPosStart = 0x28;
            usClampPosEnd = 0x50;

#if (_YPBPR_SUPPORT == _ON)
            SET_COLOR_SPACE(_A0_INPUT_PORT, _COLOR_SPACE_YPBPR);
#endif
            break;

        default:

            // Convert H start/HS width to current resolution
            PDATA_WORD(0) = (DWORD)GET_ACTIVE_H_START() * GET_INPUT_TIMING_HTOTAL() / g_usAdcClockLimit;
            PDATA_WORD(1) = (DWORD)GET_INPUT_TIMING_HTOTAL() * GET_INPUT_TIMING_HSYNCWIDTH() / GET_SYNC_H_PERIOD();

            // Check H start position
            if(PDATA_WORD(0) <= PDATA_WORD(1))
            {
                // Invalid measure; Set default clamp position
                usClampPosStart = 0x04;
                usClampPosEnd = 0x0A;
            }
            else
            {
                // Calculate back porch size
                PDATA_WORD(2) = PDATA_WORD(0) - PDATA_WORD(1);

                // Check auto-function result for clamp position
                if(PDATA_WORD(2) > 0x12)
                {
                    // Clamp to back porch
                    usClampPosStart = 0x04;
                    usClampPosEnd = 0x10;
                }
                else
                {
                    // Clamp to back porch with shortened length
                    usClampPosEnd = ((PDATA_WORD(2) >= 9) ? (PDATA_WORD(2) - 0x02) : 0x07);
                    usClampPosStart = ((usClampPosEnd >= 0x07) ? (usClampPosEnd - 0x06) : 0x01);
                }
            }

            break;
    }

    // Clamp position apply
    ScalerSyncProcClampPosSetting(usClampPosStart, usClampPosEnd);
}

//--------------------------------------------------
// Description  : Clamp Position setting
// Input Value  : usClampPosStart --> Clamp Position Start
//                  usClampPosEnd --> Clamp Position End
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcClampPosSetting(WORD usClampPosStart, WORD usClampPosEnd)
{
    // Y/G Clamp Position LSB
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_00_G_CLAMP_START, LOBYTE(usClampPosStart));
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, LOBYTE(usClampPosEnd));

    // Pb/B Clamp Position LSB
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_02_BR_CLAMP_START, LOBYTE(usClampPosStart));
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_03_BR_CLAMP_END, LOBYTE(usClampPosEnd));

    // Y/G Clamp Position MSB
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_0D_G_CLAMP_START_H, (((HIBYTE(usClampPosStart) << 4) & 0xF0) | (HIBYTE(usClampPosEnd) & 0x0F)));

    // Pb/B Clamp Position MSB
    ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_0E_BR_CLAMP_START_H, (((HIBYTE(usClampPosStart) << 4) & 0xF0) | (HIBYTE(usClampPosEnd) & 0x0F)));
}

//--------------------------------------------------
// Description  : Get Clamp End Position
// Input Value  : None
// Output Value : Clamp Position End
//--------------------------------------------------
WORD ScalerSyncProcGetClampEndPosition(void)
{
    // Get Y/G clamp end position
    pData[0] = ScalerGetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_0D_G_CLAMP_START_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerGetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_01_G_CLAMP_END, 1, &pData[1], _NON_AUTOINC);

    // Get BR/PbPr clamp end position
    pData[2] = ScalerGetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_0E_BR_CLAMP_START_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerGetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_03_BR_CLAMP_END, 1, &pData[3], _NON_AUTOINC);

    // Return the larger clamp end
    if(PDATA_WORD(0) > PDATA_WORD(1))
    {
        return PDATA_WORD(0);
    }
    else
    {
        return PDATA_WORD(1);
    }
}

//-------------------------------------------------------------------
// Description  : Clear Sync change status
// Input Value  : None
// Output Value : None
//-------------------------------------------------------------------
void ScalerSyncProcClearSyncChangeStatus(void)
{
    ScalerSetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
}

//-------------------------------------------------------------------
// Description  : Calculate H freq by stable measure
// Input Value  : None
// Output Value : H Freq
//-------------------------------------------------------------------
WORD ScalerSyncProcMeasureIHFreqByStableMeasure(void)
{
    // Calculate input H-Sync Frequency
    return (WORD)((_SYNC_PROC_CLK * 10 * 2 / (((WORD)(ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_51_STABLE_PERIOD_L)) + 1) / 2);
}

//-------------------------------------------------------------------
// Description  : Enable / disable sync pulse detect
// Input Value  : Enbale or disable detect
// Output Value : None
//-------------------------------------------------------------------
void ScalerSyncProcPulseDetectEnable(BYTE ucEnable)
{
    if(ucEnable == _ENABLE)
    {
        ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_19_HS_DETECT_SETTING, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_19_HS_DETECT_SETTING, ~(_BIT7 | _BIT6), 0x00);
    }
}

//-------------------------------------------------------------------
// Description  : Set sync detect debounce
// Input Value  : Debounce width
// Output Value : None
//-------------------------------------------------------------------
void ScalerSyncProcSetDebounce(BYTE ucDebounce)
{
    // Set input H-Sync Debounce width for decomposite & stable measure & auto run block
    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_09_DETECTION_TOLERANCE_SETTING, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucDebounce & 0x1F);

    // Set input H-Sync debounce for predetect
    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_19_HS_DETECT_SETTING, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucDebounce & 0x0F);
}

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial porch voltage check for non-SOG sync type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcSetPorchVoltage(void)
{
    // NOP for sync type SOG
    if(ScalerGetBit(P0_47_SYNC_SELECT, _BIT4) != _BIT4)
    {
        // Power up SOG
        ScalerSetBit(P0_C6_ADC_POWER, ~_BIT5, _BIT5);

        // Set SOG detect debounce to 0x0F; Enable SOG detect
        ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_19_HS_DETECT_SETTING, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Set SOG compare level to 0
        ScalerSetByte(P0_D7_ADC_SOG_DAC, 0x00);

        // Clear SOG detect flag
        ScalerSetBit(P0_5B_HS_DETECT, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
}

//--------------------------------------------------
// Description  : Monitor porch voltage status change
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncProcCheckPorchChange(void)
{
    BYTE ucIndex = 3;

    // Check SOG detect flag only for non-SOG cases
    if(ScalerGetBit(P0_47_SYNC_SELECT, _BIT4) == 0x00)
    {
        do
        {
            // Check if clamp-to-top status is inline with SOG detect flag
            if(((ScalerGetBit(P0_5B_HS_DETECT, _BIT6) == 0x00) ^ (ScalerGetBit(P0_D6_ADC_CLAMP_TOP, (_BIT2 | _BIT1 | _BIT0)) == 0x00)) == _TRUE)
            {
                // Clear SOG detect flag
                ScalerSetBit(P0_5B_HS_DETECT, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                --ucIndex;

                if(ucIndex == 0x00)
                {
                    break;
                }

                // Wait for some time;
                ScalerTimerDelayXms(2);
            }
            else
            {
                break;
            }
        }
        while(ucIndex != 0x00);

        // Clear SOG detect flag
        ScalerSetBit(P0_5B_HS_DETECT, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    return (ucIndex == 0x00);
}
#endif

//--------------------------------------------------
// Description  : Down counter Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcDownCounterSetting(void)
{
    // Down Counter reference  CR4C[2:0] + CR4D[7:0]
    ScalerSetBit(P0_5B_HS_DETECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Pop Up Stable Value
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

    // Get 1/3 stable period
    PDATA_WORD(0) = ((((WORD)(ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_51_STABLE_PERIOD_L)) + 1) / 3;

    // Set VSync Counter level
    ScalerSetBit(P0_4C_VSYNC_COUNTER_LEVEL_MSB, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(PDATA_WORD(0) >> 8) & 0x07);
    ScalerSetByte(P0_4D_VSYNC_COUNTER_LEVEL_LSB, (BYTE)(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Get Current Sync Proc Clock Frequency
// Input Value  : None
// Output Value : Return Current Sync Proc Clock
//--------------------------------------------------
DWORD ScalerSyncProcGetCurrentClockFreq(void)
{
    return _SYNC_PROC_CLK;
}

#if(_SOG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling for SOG detected flag
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumSogLevelSearchResult ScalerSyncProcSogCheckFlag(void)
{
    // About 256 us for H-Frq = 15.63K
    BYTE ucTimeOutCounter = 50;

    for(pData[0] = 5; pData[0] > 0; --pData[0])
    {
        // Clear SOG detected flag
        ScalerSetBit(P0_5B_HS_DETECT, ~_BIT6, _BIT6);

        // For SOG Power Stable, Refernce H-Freq = 15.63k, Delay Time about 4 H-Sync Period
        for(pData[1] = 0; pData[1] <= ucTimeOutCounter; pData[1]++)
        {
            Delay5us(g_ucDelay5usN);
        }

        // Check SOG detect flag
        if(ScalerGetBit(P0_5B_HS_DETECT, _BIT6) != _BIT6)
        {
            return _SOG_LEVEL_FAIL;
        }
    }

    // SOG flag is valid
    return _SOG_LEVEL_VALID;
}

//--------------------------------------------------
// Description  : Check for SOG HS result
// Input Value  : stMeasureSyncHV --> structure for detected HS info
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumSogLevelSearchResult ScalerSyncProcSogCheckHs(StructMeasureSyncData *pstMeasureSyncHV)
{
    WORD usHSyncPeriod = 0;
    WORD usHSyncPulseCount = 0;

    // Enable Sync Processor Clock
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT0), 0x00);

    // HS_OUT Signal Output Enable
    ScalerSetByte(P0_48_SYNC_INVERT, 0x10);

    // HS_OUT by pass mode, Measure Source is ADC_HS1/ADC_VS, H Sync measure source is original hs
    ScalerSetByte(P0_49_SYNC_CTRL, 0x06);

    // Sync from SOG Pad
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT4, _BIT4);

    // Start Stable Period Measure
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, 0x00);
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT0, _BIT0);

    if(ScalerTimerPollingFlagProc(12, P0_4F_STABLE_MEASURE, _BIT7, _TRUE) == _TRUE)
    {
        // Pop up stable result
        ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

        usHSyncPeriod = ((WORD)(ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_51_STABLE_PERIOD_L);
        usHSyncPulseCount = ((WORD)(ScalerGetByte(P0_4A_STABLE_HIGH_PERIOD_H) & 0x07) << 8) | ScalerGetByte(P0_4B_STABLE_HIGH_PERIOD_L);

        // Check HS width / HS period ratio
        if(((usHSyncPulseCount * 7) >= usHSyncPeriod) ||
           (usHSyncPulseCount < _MIN_SYNC_HIGHPULSE_CNT_PS))
        {
            return _SOG_LEVEL_INVALID;
        }

        // De-bounce check for stable measure
        if((pstMeasureSyncHV->usHSPeriod != 0) || (pstMeasureSyncHV->usHSWidth != 0))
        {
            if((abs(pstMeasureSyncHV->usHSPeriod - usHSyncPeriod) > ((pstMeasureSyncHV->usHSPeriod <= 1) ? 1 : (pstMeasureSyncHV->usHSPeriod >> 1))) ||
               (abs(pstMeasureSyncHV->usHSWidth - usHSyncPulseCount) > ((pstMeasureSyncHV->usHSWidth <= 1) ? 1 : (pstMeasureSyncHV->usHSWidth >> 1))))
            {
                return _SOG_LEVEL_INVALID;
            }
        }
        else
        {
            // Store measure HS info
            pstMeasureSyncHV->usHSPeriod = usHSyncPeriod;
            pstMeasureSyncHV->usHSWidth = usHSyncPulseCount;

            // Set VS down-counter
            ScalerSyncProcDownCounterSetting();
        }

        // Rough check H-Sync Freq Range
        usHSyncPeriod = (_SYNC_PROC_CLK / usHSyncPeriod);

        if((_SUPPORT_HSYNC_MIN_FREQ > usHSyncPeriod) || (usHSyncPeriod > _SUPPORT_HSYNC_MAX_FREQ))
        {
            return _SOG_LEVEL_INVALID;
        }

        // SOG HS is valid
        return _SOG_LEVEL_VALID;
    }

    return _SOG_LEVEL_FAIL;
}

//--------------------------------------------------
// Description  : Check for SOG VS result
// Input Value  : stMeasureSyncHV --> structure for detected VS info
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumSogLevelSearchResult ScalerSyncProcSogCheckVs(StructMeasureSyncData *pstMeasureSyncHV)
{
    BYTE ucLoopCounter = 0;
    BYTE ucTimeoutCounter = ((_WAIT_TWO_FRAME_TIME >> 2) + 1);

    // Enable De-composite circuit; Set to analog measure
    ScalerSetBit(P0_47_SYNC_SELECT, ~(_BIT5 | _BIT0), _BIT5);

    // Select DE-VS/HS
    ScalerSetBit(P0_49_SYNC_CTRL, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Waitting for de-composite circuit decode one frame.
    while(ucLoopCounter < ucTimeoutCounter)
    {
        ++ucLoopCounter;
        ScalerTimerDelayXms(4);

        // Check HS stability
        if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, _BIT7) != 0x00)
        {
            return _SOG_LEVEL_FAIL;
        }
    }

    // Check maximum VS width
    if((pstMeasureSyncHV->usVSWidth = ScalerSyncProcGetDeVsyncWidth()) >= _MAX_VSYNC_HIGH_PERIOD)
    {
        return _SOG_LEVEL_INVALID;
    }

    return _SOG_LEVEL_VALID;
}

//--------------------------------------------------
// Description  : Check for SOG Sync Type result
// Input Value  : None
// Output Value : _SOG_LEVEL_VALID or _SOG_LEVEL_FAIL
//--------------------------------------------------
EnumSogLevelSearchResult ScalerSyncProcSogCheckSyncType(void)
{
    // Perform recheck only under PS condition
    if(ScalerGetBit(P0_C6_ADC_POWER, _BIT3) == 0x00)
    {
        // Check false active for SOG compare level within range
        if((ScalerGetBit(P0_D7_ADC_SOG_DAC, 0x3F) >= (_SOG_MID_COMPARE_LEVEL - _SOG_MID_COMPARE_RANGE)) &&
           (ScalerGetBit(P0_D7_ADC_SOG_DAC, 0x3F) <= (_SOG_MID_COMPARE_LEVEL + _SOG_MID_COMPARE_RANGE)))
        {
            if(ScalerSyncProcTypeAutoRun() == _NO_SYNC_STATE)
            {
                // Change SOG middle compare level within range
                if(g_ucSogMidLevel >= (_SOG_MID_COMPARE_LEVEL + _SOG_MID_COMPARE_RANGE))
                {
                    g_ucSogMidLevel = (_SOG_MID_COMPARE_LEVEL - _SOG_MID_COMPARE_RANGE);
                }
                else
                {
                    ++g_ucSogMidLevel;
                }

                DebugMessageAnalog("SOG mid-lv change", g_ucSogMidLevel);
                return _SOG_LEVEL_FAIL;
            }
        }
    }

    return _SOG_LEVEL_VALID;
}

//--------------------------------------------------
// Description  : Recheck SOG Sync Stable Condtion avioding mistacke wake up
// Input Value  : Input array
// Output Value : None
//--------------------------------------------------
void ScalerSyncProcSetSogCompareLevel(BYTE *pucLevels)
{
    // Reset SOG mid compare level in power normal
    if(ScalerGetBit(P0_C6_ADC_POWER, _BIT3) != 0x00)
    {
        g_ucSogMidLevel = _SOG_MID_COMPARE_LEVEL;
    }

    // Set pre-set SOG compare levels
    pucLevels[0] = 0x10;
    pucLevels[1] = g_ucSogMidLevel;
    pucLevels[2] = 0x1C;
}

//-------------------------------------------------------------------
// Description  : Check SOG Sync Status
// Input Value  : None
// Output Value : _TRUE: SOG Sync Checked OK  _FALSE: SOG Sync Checked Fail
//-------------------------------------------------------------------
bit ScalerSyncProcSogSyncCheck(void)
{
    BYTE ucLevelCounter = 0x00;
    BYTE ucLevelTarget = 0x00;
    bit bResetSearch = _FALSE;
    StructMeasureSyncData stMeasureSyncHV;
    BYTE pucSOYCompareLelArr[3];
    memset(pucSOYCompareLelArr, 0, sizeof(pucSOYCompareLelArr));
    memset(&stMeasureSyncHV, 0, sizeof(StructMeasureSyncData));

    // Initialize SOG compare levels
    ScalerSyncProcSetSogCompareLevel(pucSOYCompareLelArr);

    // Search pre-set SOG compare levels
    while(ucLevelCounter < sizeof(pucSOYCompareLelArr))
    {
        // Set current SOG compare level
        ScalerSetBit(P0_D7_ADC_SOG_DAC, ~(0x3F), pucSOYCompareLelArr[ucLevelCounter]);
        ++ucLevelCounter;

        // Check SOG flag and HS result
        if(((pData[0] = ScalerSyncProcSogCheckFlag()) != _SOG_LEVEL_VALID) ||
           ((pData[0] = ScalerSyncProcSogCheckHs(&stMeasureSyncHV)) != _SOG_LEVEL_VALID) ||
           ((pData[0] = ScalerSyncProcSogCheckVs(&stMeasureSyncHV)) != _SOG_LEVEL_VALID) ||
           ((pData[0] = ScalerSyncProcSogCheckSyncType()) != _SOG_LEVEL_VALID))
        {
            // Stop searching up if target level already being found, or invald result detected
            if((ucLevelTarget != 0x00) || (pData[0] == _SOG_LEVEL_INVALID))
            {
                break;
            }

            continue;
        }

        if(ucLevelTarget != 0x00)
        {
            // Second level found. Set average SOG compare level.
            ucLevelTarget = (ucLevelTarget + ScalerGetBit(P0_D7_ADC_SOG_DAC, 0x3F)) / 2;
            break;
        }
        else if((bResetSearch == _FALSE) && (ucLevelCounter != 1))
        {
            // Reset search process to avoid the case when sync become available during searching
            bResetSearch = _TRUE;
            ucLevelCounter = 0;
            ucLevelTarget = 0;
            memset(&stMeasureSyncHV, 0x00, sizeof(StructMeasureSyncData));

            continue;
        }

        // Store current compare level
        ucLevelTarget = ScalerGetBit(P0_D7_ADC_SOG_DAC, 0x3F);
    }

    if(ucLevelTarget != 0x00)
    {
        // Resume target compare level
        ScalerSetBit(P0_D7_ADC_SOG_DAC, ~(0x3F), ucLevelTarget);

        if(stMeasureSyncHV.usVSWidth <= 1)
        {
            // Enable Clamp Mask and select clamp mask signal as DeVS
            ScalerSetDataPortByte(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, 0xC2);

            // Align the rising edge of Clamp Mask to DeVS rising edge
            ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_04_CLAMP_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
    }

    return (ucLevelTarget != 0x00);
}

//--------------------------------------------------
// Description  : Recheck SOG Sync Stable Condtion avioding mistacke wake up
// Input Value  : None
// Output Value : True --> Sync is realy stable
//                False --> Sync is fake stable before
//--------------------------------------------------
bit ScalerSyncProcRecheckSOGSyncStable(void)
{
    bit bStatus = _TRUE;

    if(ScalerGetBit(P0_C6_ADC_POWER, _BIT3) == 0x00) // Check Current Mode is PS Mode
    {
        // Clamp position unit: Single Crystal clock
        ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_06_CLAMP_CTRL2, ~_BIT7, _BIT7);

        // G Clamp Position default Setting, Reference Crystal, Back port lenth Min = 11.69 cnt (1920x1440 @59.9Hz -R 184.75M, back port = 80)
        ScalerSyncProcClampPosSetting(0x01, 0x0B);

        // Disable DC Restore circut & Enable SOG Clamp
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~(_BIT5 | _BIT4), _BIT5);

        // Waitting for SOG floating voltage Rising to 400 V
        ScalerTimerDelayXms(3);

        // Recheck H-Sync Status
        if(ScalerSyncProcStableCheck() == _FALSE)
        {
            bStatus = _FALSE;
        }

        // Restore G Clamp Position default Setting
        ScalerSyncProcClampPosSetting(_CLAMP_POSITION_START, _CLAMP_POSITION_END);

        // Restore Clamp position unit: ADC clock
        ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_06_CLAMP_CTRL2, ~_BIT7, 0x00);

        // Enable DC Restore circut & Disable SOG Clamp
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~(_BIT5 | _BIT4), _BIT4);
    }

    return bStatus;
}
#endif // #if(_SOG_SUPPORT == _ON)

#endif // End of #if(_VGA_SUPPORT == _ON)

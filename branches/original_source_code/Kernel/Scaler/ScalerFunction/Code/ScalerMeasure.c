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
// ID Code      : ScalerMeasure.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MEASURE__

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
StructRegionTimingInfo g_pstRegionTimingInfo[_MULTI_DISPLAY_MAX];
StructRegionTimingInfo *g_pstRegionTimingInfoPointer = &(g_pstRegionTimingInfo[0]);

DWORD g_ulInputActiveRegionBackUp;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMeasureSetIndex(EnumRegionIndex enumRegionIndex);
void ScalerMeasureSetInputPath(EnumInputDataPath enumInputDataPath);
void ScalerMeasureResetTimingInfo(EnumInputDataPath enumInputDataPath);
BYTE ScalerMeasureGetPageOffset(EnumInputDataPath enumInputDataPath);
bit ScalerMeasureInputInfo(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);

#if(_VGA_SUPPORT == _ON)
bit ScalerMeasureVgaInputInfo(void);
bit ScalerMeasureGetStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
void ScalerMeasureVgaVsBypass(bit bEnable);
bit ScalerMeasureSetSourceResultIndex(EnumFormatConversionSourceType enumFormatConversionSourceType);
bit ScalerMeasureVgaInterlaceCheck(EnumSourceSearchPort enumSourceSearchPort);
#endif

bit ScalerMeasureCheckWDTriggerStatus(BYTE ucResultIndex);
bit ScalerMeasureInputActiveRegionChange(void);

EnumSourceSearchPort ScalerMeasureGetOfflineMeasurePort(void);
bit ScalerMeasureOfflineMeasureDoubleCheck(EnumSourceTypeDef enumSourceType);

void ScalerMeasureSetOnlineMeasure(EnumInputDataPath enumInputDataPath);

DWORD ScalerMeasureGetInputRegionCountResult(bit bWait);
DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait);

bit ScalerMeasureAutoFuncWaitFinish(EnumInputDataPath enumInputDataPath);
void ScalerMeasureAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd, EnumInputDataPath enumInputDataPath);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend);
#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
bit ScalerMeasureDuplicateInputInfo(BYTE ucDuplicateIndex);
void ScalerMeasureDuplicateVgipSetting(EnumInputDataPath enumDuplicatePath);
void ScalerMeasureDuplicateInterlaceSetting(EnumInputDataPath enumDuplicatePath);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Assign measure timing info pointer to region
// Input Value  : region index
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetIndex(EnumRegionIndex enumRegionIndex)
{
    if(enumRegionIndex != _REGION_INDEX_NONE)
    {
        // Set measure result pointer
#if(_MULTI_DISPLAY_MAX == 0x04)
        g_pstRegionTimingInfoPointer = &(g_pstRegionTimingInfo[enumRegionIndex & 0x03]);
#elif(_MULTI_DISPLAY_MAX == 0x02)
        g_pstRegionTimingInfoPointer = &(g_pstRegionTimingInfo[enumRegionIndex & 0x01]);
#else
        g_pstRegionTimingInfoPointer = &(g_pstRegionTimingInfo[0]);
#endif
    }
}

//--------------------------------------------------
// Description  : Set input data path for current measure target
// Input Value  : input data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetInputPath(EnumInputDataPath enumInputDataPath)
{
    // Set measure input source
    SET_MEASURE_INPUT_PATH(enumInputDataPath);
}

//--------------------------------------------------
// Description  : Clear timing info
// Input Value  : input data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureResetTimingInfo(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIndex = 0x00;

    switch(enumInputDataPath)
    {
        case _INPUT_PATH_ALL:
        default:
            for(ucIndex = 0x00; ucIndex < _MULTI_DISPLAY_MAX; ++ucIndex)
            {
                if((g_pstRegionTimingInfo[ucIndex].stTimingInfo.enumInputDataPath & enumInputDataPath) != 0x00)
                {
                    memset(&(g_pstRegionTimingInfo[ucIndex].stTimingInfo), 0x00, sizeof(StructTimingInfo));
                }
            }
            break;

        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
            memset(&(g_pstRegionTimingInfo[0].stTimingInfo), 0x00, sizeof(StructTimingInfo));
            break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _INPUT_PATH_M2:
        case _INPUT_PATH_S1_S2:
            memset(&(g_pstRegionTimingInfo[1].stTimingInfo), 0x00, sizeof(StructTimingInfo));
            break;

#if(_MULTI_DISPLAY_MAX == 0x04)
        case _INPUT_PATH_S1:
            memset(&(g_pstRegionTimingInfo[2].stTimingInfo), 0x00, sizeof(StructTimingInfo));
            break;

        case _INPUT_PATH_S2:
            memset(&(g_pstRegionTimingInfo[3].stTimingInfo), 0x00, sizeof(StructTimingInfo));
            break;
#endif

#endif
    }
}

//--------------------------------------------------
// Description  : Convert data path to register page
// Input Value  : input data path
// Output Value : measure register page
//--------------------------------------------------
BYTE ScalerMeasureGetPageOffset(EnumInputDataPath enumInputDataPath)
{
    if((enumInputDataPath & _INPUT_PATH_M1) != 0x00)
    {
        return 0x00; // M1_M2 / M1 / all
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0x00)
    {
        return 0x40; // M2
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0x00)
    {
        return 0x80; // S1_S2 / S1
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0x00)
    {
        return 0xC0; // S2
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Measure Input Timing
// Input Value  : enumSourceType --> Input source type
//                enumSourceSearchPort --> Input port type
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureInputInfo(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial the interface to be measured
    ScalerMeasureInterfaceInitial(enumSourceType, &enumSourceSearchPort);

    // Initial measure & auto-function
    ScalerMeasureInitialSetting(enumSourceType, enumSourceSearchPort);

    // Initial Interlace Check Block
    ScalerMeasureInterlaceInitial(enumSourceType, enumSourceSearchPort);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    //===========================================================================================
    // 1. Start measure block & pop-out result
    //===========================================================================================

    // Wait for 2 raw IVS for digital; Pop out measure result
    if((ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerMeasureGetOfflineMeasureResult(&(g_pstRegionTimingInfoPointer->stMeasureSyncData)) == _FALSE))
    {
        DebugMessageMeasure("Digital off-line measure fail", 0x00);
        return _FALSE;
    }

    //===========================================================================================
    // 2. Check VGIP HS/VS polarity
    //===========================================================================================

    // Update input timing polarity
    ScalerMeasureUpdateInputTimingPolarity(enumSourceType, enumSourceSearchPort, &(g_pstRegionTimingInfoPointer->stMeasureSyncData));

    // Modify VGIP sync polarity
    ScalerVgipModifyPolarity(enumSourceType);

    // Update input timing data from variable "g_stMeasureSyncHV"
    ScalerMeasureUpdateInputTimingData(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), &(g_pstRegionTimingInfoPointer->stAutoActiveData));

    //===========================================================================================
    // 3. Start auto-function
    //===========================================================================================

    // Set auto-function digital measure
    ScalerMeasureSetAuto(_NORMAL_MEASURE, GET_MEASURE_INPUT_PATH());

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    // Wait for 2 latched IVS; Pop out auto-function result
    if((ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerMeasureGetAutoResult(&(g_pstRegionTimingInfoPointer->stAutoActiveData), GET_MEASURE_INPUT_PATH(), _NOT_WAIT) == _FALSE))
    {
        DebugMessageMeasure("Digital auto-function fail", 0x00);
        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), &(g_pstRegionTimingInfoPointer->stAutoActiveData));

    //===========================================================================================
    // 4. Detect interlace format
    //===========================================================================================

    // Check interlace by flag
    if(ScalerMeasureInterlaceCheck(enumSourceType, enumSourceSearchPort) == _TRUE)
    {
        DebugMessageMeasure("Interlace: detect by flag", 0x00);
        g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        // Update video field
        if(GET_PAGED_BIT(ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH()), P0_32_SCALE_CONTROL_REG, _BIT6) == _BIT6)
        {
            g_pstRegionTimingInfoPointer->stTimingInfo.b1VideoField = _TRUE;
        }
#endif

        // Update input timing data
        ScalerMeasureUpdateInputTimingData(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), &(g_pstRegionTimingInfoPointer->stAutoActiveData));
    }

    //===========================================================================================
    // 5. Double-check current timing
    //===========================================================================================

#if(_DUAL_DVI_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_DVI)
    {
        // Check dual DVI format
        if(ScalerMeasureDualDviOfflineCheck(enumSourceSearchPort) == _FALSE)
        {
            DebugMessageMeasure("Dual DVI check fail", 0x00);
            return _FALSE;
        }
    }
#endif

    // Check digital measure result
    if(abs(GET_SYNC_V_HEIGHT() - GET_INPUT_TIMING_VHEIGHT()) > 2)
    {
        DebugMessageMeasure("Digital check V height fail", 0x00);
        return _FALSE;
    }

    if(abs(GET_SYNC_H_WIDTH() - GET_INPUT_TIMING_HWIDTH()) > 2)
    {
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        if((enumSourceType == _SOURCE_DVI) || (enumSourceType == _SOURCE_HDMI))
        {
            // Check first line width for DVI/HDMI
            ScalerMeasureCheckFirstLineShift(enumSourceSearchPort, GET_SYNC_H_WIDTH());
        }
#endif

        DebugMessageMeasure("Digital check H width fail", 0x00);
        return _FALSE;
    }

    //===========================================================================================
    // 6. Measure final settings
    //===========================================================================================

#if(_HDMI_2_0_SUPPORT == _ON)
    ScalerFmtCnv420To422FinalSetting(enumSourceSearchPort);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Decide I-domain path setting in format conversion
    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        // Final format conversion setting
        ScalerFmtCnvFinalSetting(enumSourceSearchPort, GET_MEASURE_INPUT_PATH(), _WAIT);

        // Check VS bypass
        if(ScalerMeasureCheckVsBypass(enumSourceType, enumSourceSearchPort) == _TRUE)
        {
            ScalerVgipVsBypassEnable(GET_MEASURE_INPUT_PATH(), _ENABLE);
        }
    }

    // Double-cheeck auto-function again for 420 & E/O mode
    if((ScalerFmtCnvFtoPGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE) ||
       (GET_COLOR_SPACE(enumSourceSearchPort) == _COLOR_SPACE_YCBCR420))
    {
        // Set auto-function digital measure
        ScalerMeasureSetAuto(_NORMAL_MEASURE, GET_MEASURE_INPUT_PATH());

        // Wait for 2 latched IVS; Pop out auto-function result
        if((ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerMeasureGetAutoResult(&(g_pstRegionTimingInfoPointer->stAutoActiveData), GET_MEASURE_INPUT_PATH(), _NOT_WAIT) == _FALSE))
        {
            DebugMessageMeasure("Digital format conversion fail", 0x00);
            return _FALSE;
        }

        // Set format conversion background color
        ScalerFmtCnvSetBackgroundColor(GET_MEASURE_INPUT_PATH());
    }
#endif

    // Start on-line measure
    ScalerMeasureSetOnlineMeasure(GET_MEASURE_INPUT_PATH());

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), &(g_pstRegionTimingInfoPointer->stAutoActiveData));

    // Double check off-line measure result
    if(ScalerMeasureOfflineMeasureDoubleCheck(enumSourceType) == _FALSE)
    {
        DebugMessageMeasure("Digital off-line double check fail", 0x00);
        return _FALSE;
    }

    // Pop out on-line measure result
    if(ScalerMeasureGetOnlineMeasureResult(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        DebugMessageMeasure("Digital on-line measure fail", 0x00);
        return _FALSE;
    }

    // Perform measure final setting
    if(ScalerMeasureFinalSetting(enumSourceType, enumSourceSearchPort) == _FALSE)
    {
        DebugMessageMeasure("Final setting in measure fail", 0x00);
        return _FALSE;
    }

    return _TRUE;
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Measure Input Timing
// Input Value  : None
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureVgaInputInfo(void)
{
    DWORD pulActiveRegionCount[2];
    EnumSourceSearchPort enumSourceSearchPort = _A0_INPUT_PORT;

    pulActiveRegionCount[0] = 0;
    pulActiveRegionCount[1] = 0;

    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial the interface to be measured
    ScalerMeasureInterfaceInitial(_SOURCE_VGA, &enumSourceSearchPort);

    // Initial Measure
    ScalerMeasureInitialSetting(_SOURCE_VGA, _A0_INPUT_PORT);

    // Initial Interlace Check Block
    ScalerMeasureInterlaceInitial(_SOURCE_VGA, _A0_INPUT_PORT);

    // Enable IVS bypass
    ScalerMeasureVgaVsBypass(_ENABLE);

    // Wait for 2raw IVS before switch to VS bypass mode
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE))
    {
        DebugMessageMeasure("VGA IVS fail", 0x00);
        return _FALSE;
    }

    // Initial active region count block
    ScalerMeasureSetInputRegionCount(GET_MEASURE_INPUT_PATH(), _WHOLE_FRAME_TYPE);

    //===========================================================================================
    // 1. Start measure block & region count(raw VS); pop-out result
    //===========================================================================================

    // Wait for 3raw IVS for VGA; Pop out measure result
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerMeasureGetOfflineMeasureResult(&(g_pstRegionTimingInfoPointer->stMeasureSyncData)) == _FALSE))
    {
        DebugMessageMeasure("VGA off-line measure fail", 0x00);
        return _FALSE;
    }

    ScalerTimerDelayXms(2);

    // Pop out active region count result (raw)
    if((pulActiveRegionCount[0] = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT)) == 0x00)
    {
        return _FALSE;
    }

    // Disable IVS bypass
    ScalerMeasureVgaVsBypass(_DISABLE);

    // Restart active region count block;
    ScalerMeasureSetInputRegionCount(GET_MEASURE_INPUT_PATH(), _WHOLE_FRAME_TYPE);

    //===========================================================================================
    // 2. Check VGIP HS/VS polarity
    //===========================================================================================

    // Update input timing polarity (MUST BE HERE)
    ScalerMeasureUpdateInputTimingPolarity(_SOURCE_VGA, _A0_INPUT_PORT, &(g_pstRegionTimingInfoPointer->stMeasureSyncData));

    // Modify VGATOP sync polarity
    ScalerVgaTopModifyPolarity();

    // Modify VGIP sync polarity
    ScalerVgipModifyPolarity(_SOURCE_VGA);

    // Update input timing data from variable "g_stMeasureSyncHV"
    ScalerMeasureUpdateInputTimingData(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), &(g_pstRegionTimingInfoPointer->stAutoActiveData));

    //===========================================================================================
    // 3. Start auto-function & check VGIP VS latch edge
    //===========================================================================================

    // Start auto-function measure
    ScalerVgaTopSetAuto(_NORMAL_MEASURE, _FULL_BOUNDARY, ScalerAPLLGetIHTotal());

    // Check IVS latch edge after 1 IVS; Add additional 1 frame if latch edge changed
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       ((ScalerVgaTopModifyVsLatchEdge(_NOT_WAIT) == _TRUE) &&
        (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)))
    {
        return _FALSE;
    }

    // Wait for 1 latched IVS; Pop out auto-function result
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopGetAutoResult(&(g_pstRegionTimingInfoPointer->stAutoActiveData), _NOT_WAIT) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE))
    {
        DebugMessageMeasure("VGA auto-function fail", 0x00);
        return _FALSE;
    }

    //===========================================================================================
    // 4. Detect interlace format
    //===========================================================================================

    // Pop out active region count result (latched) for VGA
    pulActiveRegionCount[1] = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT);

    // Check active region count result; Return _FALSE if the difference is too large
    if(ABSDWORD(pulActiveRegionCount[0], pulActiveRegionCount[1]) > (pulActiveRegionCount[1] >> 6))
    {
        DebugMessageMeasure("VGA active count difference fail", 0x00);
        return _FALSE;
    }

    // Get HS period in measure clock
    PDATA_WORD(1) = (((WORD)ScalerGetBit(P30_05_MEAS_HS_PERIOD_A_M, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) |
                     ((WORD)ScalerGetByte(P30_06_MEAS_HS_PERIOD_A_L)));

    // Calculate difference of V period
    PDATA_WORD(0) = (WORD)(ABSDWORD(pulActiveRegionCount[0], pulActiveRegionCount[1]) % PDATA_WORD(1));

    // Check half line length; flag interlace between [0.25:0.75] * H period
    if(abs(PDATA_WORD(0) - (PDATA_WORD(1) >> 1)) < (PDATA_WORD(1) >> 2))
    {
        DebugMessageScaler("Interlace: detect by half line", PDATA_WORD(0));
        g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;
    }
    // Check full line length; flag interlace for 0.875 line difference
    else if(PDATA_WORD(0) > (PDATA_WORD(1) - (PDATA_WORD(1) >> 3)))
    {
        DebugMessageScaler("Interlace: detect by full line", PDATA_WORD(1));
        g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace = _TRUE;
    }

    // Check active measure overflow status
    if(ScalerGetBit(P30_41_I_ACT_MEAS_ERROR_FLG, _BIT6) == _BIT6)
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace = ScalerMeasureInterlaceCheck(_SOURCE_VGA, _A0_INPUT_PORT);
        DebugMessageScaler("Interlace: detect by flag", g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace);
    }

    // Update VGATOP field source
    ScalerSetBit(P30_A3_VGATOP_VGIP_ODD_CTRL, ~_BIT0, ((GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE) ? _BIT0 : 0x00));

    //===========================================================================================
    // 5. Double-check current timing
    //===========================================================================================

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), &(g_pstRegionTimingInfoPointer->stAutoActiveData));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Decide I-domain path setting in format conversion
    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(GET_MEASURE_INPUT_PATH()) == _FALSE)
    {
        // Final format conversion setting
        ScalerFmtCnvFinalSetting(_A0_INPUT_PORT, GET_MEASURE_INPUT_PATH(), _NOT_WAIT);
    }
#endif

    // Start on-line measure
    ScalerMeasureSetOnlineMeasure(GET_MEASURE_INPUT_PATH());

    // Double check off-line measure result
    if(ScalerMeasureOfflineMeasureDoubleCheck(_SOURCE_VGA) == _FALSE)
    {
        DebugMessageMeasure("VGA off-line double check fail", 0x00);
        return _FALSE;
    }

    // Double-check for timing change
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerMeasureGetOnlineMeasureResult(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), GET_MEASURE_INPUT_PATH()) == _FALSE))
    {
        DebugMessageMeasure("VGA on-line measure fail", 0x00);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check timing change
// Input Value  : stMeasureSyncHV --> result pointer
// Output Value : _TRUE if HV timing Changed
//--------------------------------------------------
bit ScalerMeasureGetStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV)
{
    if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT3)) != 0x00)
    {
        return _FALSE;
    }

    // Pop up stable measure result
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P0_4F_STABLE_MEASURE, _BIT6);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | (ScalerGetByte(P0_51_STABLE_PERIOD_L))) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P0_4A_STABLE_HIGH_PERIOD_H) & 0x07) << 8) | (ScalerGetByte(P0_4B_STABLE_HIGH_PERIOD_L))) + 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGATOP
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMeasureVgaVsBypass(bit bEnable)
{
    // Switch VGATOP VS bypass
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT6, 0x00);
    }

    // Switch VGIP VS bypass
    ScalerVgipVsBypassEnable(GET_MEASURE_INPUT_PATH(), bEnable);
}

//--------------------------------------------------
// Description  : Update measure timing index by source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerMeasureSetSourceResultIndex(EnumFormatConversionSourceType enumFormatConversionSourceType)
{
    BYTE ucResultIndex = 0;

    for(ucResultIndex = 0; ucResultIndex < _MULTI_DISPLAY_MAX; ++ucResultIndex)
    {
        if(ScalerFmtCnvGetSourceType(g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath) == enumFormatConversionSourceType)
        {
            g_pstRegionTimingInfoPointer = &(g_pstRegionTimingInfo[ucResultIndex]);
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGA Interlace
// Input Value  : enumSourceSearchPort --> input port type
// Output Value : TRUE => Interlaced Detected
//--------------------------------------------------
bit ScalerMeasureVgaInterlaceCheck(EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());
    bit bInterlacedFormat = _FALSE;

    enumSourceSearchPort = enumSourceSearchPort;

    // Check VGA interlace condition: due to overflow or from digital measure?
    if(ScalerGetBit(P30_41_I_ACT_MEAS_ERROR_FLG, _BIT6) == _BIT6)
    {
        // Clear VGIP Interlace Toggle Flag
        SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        ScalerTimerDelayXms(2);

        if((GET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5) ||
           (ScalerGetBit(P0_4A_STABLE_HIGH_PERIOD_H, (_BIT6 | _BIT4)) != 0x00))
        {
            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Clear Sync proc. toggle flag
            ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            bInterlacedFormat = _TRUE;
        }

        // Clear VGIP Interlace Toggle Flag
        SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

        // Clear Sync proc. toggle flag
        ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
    }
    else
    {
        // Check from previous set flag
        bInterlacedFormat = (ScalerGetBit(P30_A3_VGATOP_VGIP_ODD_CTRL, _BIT0) == _BIT0);
    }

    return bInterlacedFormat;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check VGIP VS bypass
// Input Value  : ucResultIndex --> check index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureCheckWDTriggerStatus(BYTE ucResultIndex)
{
    // Check over-range watchdog
    switch(g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_ALL:
            return (bit)((ScalerGetBit(P16_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
                         (ScalerGetBit(P16_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))));

#if(_2P_DISPLAY_SUPPORT == _ON)
        case _INPUT_PATH_S1_S2:
            return (bit)((ScalerGetBit(P96_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
                         (ScalerGetBit(P96_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))));
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _INPUT_PATH_M2:
            return (bit)((ScalerGetBit(P56_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
                         (ScalerGetBit(P56_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))));

        case _INPUT_PATH_S1:
            return (bit)((ScalerGetBit(P96_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
                         (ScalerGetBit(P96_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))));

        case _INPUT_PATH_S2:
            return (bit)((ScalerGetBit(PD6_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
                         (ScalerGetBit(PD6_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))));
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if active region changed
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureInputActiveRegionChange(void)
{
    // Pop out region count result
    PDATA_DWORD(0) = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT);

    // Disable Input Region Measure
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT0, 0x00);

    // Compare with stored input active region count
    return (ABSDWORD(PDATA_DWORD(0), g_ulInputActiveRegionBackUp) > (g_ulInputActiveRegionBackUp >> 8));
}

//--------------------------------------------------
// Description  : Get current off-line measure port
// Input Value  : None
// Output Value : off-line measure port
//--------------------------------------------------
EnumSourceSearchPort ScalerMeasureGetOfflineMeasurePort(void)
{
    switch(ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
    {
        case 0x00:
            return _D0_INPUT_PORT;

        case _BIT0:
            return _D1_INPUT_PORT;

        case _BIT1:
        case (_BIT2 | _BIT1):
            return _D2_INPUT_PORT;

        case (_BIT1 | _BIT0):
            return _D3_INPUT_PORT;

        case _BIT2:
        case (_BIT2 | _BIT1 | _BIT0):
            return _D4_INPUT_PORT;

        case (_BIT2 | _BIT0):
            return _D5_INPUT_PORT;

        case (_BIT3 | _BIT1 | _BIT0):
            return _A0_INPUT_PORT;

        default:
            return _NO_INPUT_PORT;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Check off-line measure result
// Input Value  : enumSourceType --> input source type
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureOfflineMeasureDoubleCheck(EnumSourceTypeDef enumSourceType)
{
    StructMeasureSyncData stMeasureSyncHV;
    memset(&stMeasureSyncHV, 0, sizeof(StructMeasureSyncData));

    enumSourceType = enumSourceType;

#if(_VGA_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_VGA)
    {
        if((ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncHV) == _FALSE) ||
           (stMeasureSyncHV.b1HSP != g_pstRegionTimingInfoPointer->stMeasureSyncData.b1HSP) ||
           (abs(stMeasureSyncHV.usHSPeriod - g_pstRegionTimingInfoPointer->stMeasureSyncData.usHSPeriod) > 0x02) ||
           (abs(stMeasureSyncHV.usVSPeriod - g_pstRegionTimingInfoPointer->stMeasureSyncData.usVSPeriod) > 0x02))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        if((ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncHV) == _FALSE) ||
           (stMeasureSyncHV.b1HSP != g_pstRegionTimingInfoPointer->stMeasureSyncData.b1HSP) ||
           (stMeasureSyncHV.b1VSP != g_pstRegionTimingInfoPointer->stMeasureSyncData.b1VSP) ||
           (abs(stMeasureSyncHV.usHWidth - g_pstRegionTimingInfoPointer->stMeasureSyncData.usHWidth) > 0x02) ||
           (abs(stMeasureSyncHV.usVHeight - g_pstRegionTimingInfoPointer->stMeasureSyncData.usVHeight) > 0x02))
        {
            return _FALSE;
        }

#if(_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() != _TRUE)
#endif
        {
            if((abs(stMeasureSyncHV.usHTotal - g_pstRegionTimingInfoPointer->stMeasureSyncData.usHTotal) > 0x02) ||
               (abs(stMeasureSyncHV.usHSPeriod - g_pstRegionTimingInfoPointer->stMeasureSyncData.usHSPeriod) > 0x02) ||
               (abs(stMeasureSyncHV.usVSPeriod - g_pstRegionTimingInfoPointer->stMeasureSyncData.usVSPeriod) > 0x02))
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set on-line measure block for target input data path
// Input Value  : input data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetOnlineMeasure(EnumInputDataPath enumInputDataPath)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath) + 0x16;

    // Disable on-line measure
    SET_PAGED_BIT(ucOffset, P16_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Disable over-range enable bit
    SET_PAGED_BIT(ucOffset, P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Clear over-range bit
    SET_PAGED_BIT(ucOffset, P16_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
        SET_PAGED_BIT(ucOffset, P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

        // Set over-range condition: HS = 16, VS = N/A, HSW = 16
        SET_PAGED_BYTE(ucOffset, P16_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT2 | _BIT0));
    }
    else
#endif
    {
        // Get input V freq.
        switch(enumInputDataPath)
        {
            default:
            case _INPUT_PATH_M1:
            case _INPUT_PATH_M1_M2:
            case _INPUT_PATH_ALL:
                PDATA_WORD(2) = (g_pstRegionTimingInfo[0].stTimingInfo.usVFreq);
                break;

#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
            case _INPUT_PATH_S1_S2:
            case _INPUT_PATH_M2:
                PDATA_WORD(2) = (g_pstRegionTimingInfo[1].stTimingInfo.usVFreq);
                break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _INPUT_PATH_S1:
                PDATA_WORD(2) = (g_pstRegionTimingInfo[2].stTimingInfo.usVFreq);
                break;

            case _INPUT_PATH_S2:
                PDATA_WORD(2) = (g_pstRegionTimingInfo[3].stTimingInfo.usVFreq);
                break;
#endif
        }

        // Calculate measure timeout period
        PDATA_WORD(0) = _MEASURE_CLK / 512 * 10000 / 2048;
        PDATA_WORD(1) = (PDATA_WORD(0) + (PDATA_WORD(0) >> 2)); // 1.5x margin

        if(PDATA_WORD(2) > PDATA_WORD(1))
        {
            // Measure Time Clock = 2048 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucOffset, P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), 0x00);
        }
        else if(PDATA_WORD(2) > (PDATA_WORD(1) >> 1))
        {
            // Measure Time Clock = 4096 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucOffset, P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT6);
        }
        else if(PDATA_WORD(2) > (PDATA_WORD(1) >> 2))
        {
            // Measure Time Clock = 8192 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucOffset, P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT7);
        }
        else
        {
            // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            SET_PAGED_BIT(ucOffset, P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));
        }

        // Set over-range condition: HS = 16, VS = 4, HSW = 16
        SET_PAGED_BYTE(ucOffset, P16_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0));
    }

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable on-line measure
    SET_PAGED_BIT(ucOffset, P16_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
}

//--------------------------------------------------
// Description  : Pop Up Region Count result
// Input Value  : bWait --> wait for additional frames or not
// Output Value : measure region count
//--------------------------------------------------
DWORD ScalerMeasureGetInputRegionCountResult(bit bWait)
{
    BYTE ucInputPath = 0;

    if(bWait == _WAIT)
    {
        switch(ScalerGetBit(P30_40_I_ACT_MEAS_CTRL, (_BIT7 | _BIT6 | _BIT5)))
        {
            case 0x00:
                ucInputPath = _INPUT_PATH_M1;
                break;

            case _BIT5:
                ucInputPath = _INPUT_PATH_M2;
                break;

            case _BIT6:
                ucInputPath = _INPUT_PATH_S1;
                break;

            case (_BIT6 | _BIT5):
                ucInputPath = _INPUT_PATH_S2;
                break;

            default:
                break;
        }

        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, ucInputPath);
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, ucInputPath);
    }

    // Pop up Measure Results
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

    // Get Active Measure Clk Count
    PDATA_DWORD(0) = ScalerGetDWord(P30_41_I_ACT_MEAS_ERROR_FLG);
    pData[0] = 0x00;

    return PDATA_DWORD(0);
}



//--------------------------------------------------
// Description  : Pop Up Region Count result
// Input Value  : bWait --> wait for additional frames or not
// Output Value : measure region count
//--------------------------------------------------
DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait)
{
    BYTE ucDisplayPath = 0;

    if(bWait == _WAIT)
    {
        switch(ScalerGetBit(P30_45_D_ACT_MEAS_CTRL, (_BIT7 | _BIT6 | _BIT5)))
        {
            case 0x00:
                ucDisplayPath = _DISPLAY_PATH_M1;
                break;

            case _BIT5:
                ucDisplayPath = _DISPLAY_PATH_S1;
                break;

            default:
                break;
        }

        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, ucDisplayPath);
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, ucDisplayPath);
    }

    // Pop up Measure Results
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

    // Get Active Measure Clk Count
    PDATA_DWORD(0) = ScalerGetDWord(P30_46_D_ACT_MEAS_ERROR_FLG);
    pData[0] = 0x00;

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Waiting for Auto Function Measure Finish
// Input Value  : enumInputDataPath --> auto data path
// Output Value : True --> Measure Finish
//                False --> Measure Timeout or Fail
//--------------------------------------------------
bit ScalerMeasureAutoFuncWaitFinish(EnumInputDataPath enumInputDataPath)
{
    BYTE ucIvsCnt = 0;
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath);

    ucIvsCnt = (GET_PAGED_BIT(ucOffset, P0_7A_AUTO_ADJ_CTRL0, _BIT1 | _BIT0) == 0x03) ? 3 : 1;
    ucIvsCnt = (GET_PAGED_BIT(ucOffset, P0_7A_AUTO_ADJ_CTRL0, _BIT7) == _BIT7) ? ucIvsCnt * 2 : ucIvsCnt;
    ucIvsCnt += 2;

    do
    {
        if(ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath) == _FALSE)
        {
            return _FALSE;
        }

        if(GET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            return _TRUE;
        }
    }
    while(--ucIvsCnt);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial H Boundary for Auto Function Measure
// Input Value  : H Boundary Start/End
///               enumInputDataPath --> auto data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd, EnumInputDataPath enumInputDataPath)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath);

    // Set H boundary
    SET_PAGED_BYTE(ucOffset, P0_70_H_BOUNDARY_H, (((HIBYTE(usHBoundStart) & 0x0F) << 4) | (HIBYTE(usHBoundEnd) & 0x0F)));
    SET_PAGED_BYTE(ucOffset, P0_71_H_BOUNDARY_STA_L, LOBYTE(usHBoundStart));
    SET_PAGED_BYTE(ucOffset, P0_72_H_BOUNDARY_END_L, LOBYTE(usHBoundEnd));

    SET_PAGED_BIT(ucOffset, P0_77_GRN_NOISE_MARGIN, ~_BIT1, ((HIBYTE(usHBoundStart) >> 3) & _BIT1));
    SET_PAGED_BIT(ucOffset, P0_77_GRN_NOISE_MARGIN, ~_BIT0, ((HIBYTE(usHBoundEnd) >> 4) & _BIT0));
}

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check V start position for interlaced format
// Input Value  : V start / end
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());

    if(usVstart == g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
    {
        // For 1035i
        if((usVend - usVstart) == (g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd - g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart))
        {
            // Toggle Video Compensation field
            SET_PAGED_BIT(ucOffset, P0_32_SCALE_CONTROL_REG, ~_BIT6, (~(GET_PAGED_BYTE(ucOffset, P0_32_SCALE_CONTROL_REG)) & _BIT6));
        }
        else if((usVend - usVstart) < 250)
        {
            // For 487i
            SET_PAGED_BIT(ucOffset, P0_32_SCALE_CONTROL_REG, ~_BIT6, (~(GET_PAGED_BYTE(ucOffset, P0_32_SCALE_CONTROL_REG)) & _BIT6));
        }
    }
    else if(abs(usVstart - g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart) == 0x01)
    {
        StructAutoActiveData stAutoActiveData;
        memset(&stAutoActiveData, 0, sizeof(StructAutoActiveData));

        // Store the smaller Vstart
        if(usVstart < g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
        {
            --(g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart);
            --(g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd);
        }

        // Enable ODD delay one line & Toggle Video Compensation field
        if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M1) != 0)
        {
            ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, (~(ScalerGetByte(P0_32_SCALE_CONTROL_REG)) & _BIT6));
        }

        if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M2) != 0)
        {
            ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(P40_32_SCALE_CONTROL_REG_M2, ~_BIT6, (~(ScalerGetByte(P40_32_SCALE_CONTROL_REG_M2)) & _BIT6));
        }

        if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S1) != 0)
        {
            ScalerSetBit(P80_13_S1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(P80_32_SCALE_CONTROL_REG_S1, ~_BIT6, (~(ScalerGetByte(P80_32_SCALE_CONTROL_REG_S1)) & _BIT6));
        }

        if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S2) != 0)
        {
            ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(PC0_32_SCALE_CONTROL_REG_S2, ~_BIT6, (~(ScalerGetByte(PC0_32_SCALE_CONTROL_REG_S2)) & _BIT6));
        }

        if((ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
           (ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE))
        {
            return _FALSE;
        }

        // Pop up auto-function result
        if(ScalerMeasureGetAutoResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _NOT_WAIT) == _FALSE)
        {
            return _FALSE;
        }

        // Double-check delay-one-line field polarity
        if(stAutoActiveData.usVActiveStart != g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
        {
            // Toggle delay-one-line field
            if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M1) != 0)
            {
                ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT7, (~(ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL)) & _BIT7));
            }

            if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M2) != 0)
            {
                ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~_BIT7, (~(ScalerGetByte(P40_13_M2_VGIP_ODD_CTRL)) & _BIT7));
            }

            if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S1) != 0)
            {
                ScalerSetBit(P80_13_S1_VGIP_ODD_CTRL, ~_BIT7, (~(ScalerGetByte(P80_13_S1_VGIP_ODD_CTRL)) & _BIT7));
            }

            if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S2) != 0)
            {
                ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~_BIT7, (~(ScalerGetByte(PC0_13_S2_VGIP_ODD_CTRL)) & _BIT7));
            }
        }
    }

    return _TRUE;
}

#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Duplicate Input Timing
// Input Value  : ucDuplicateIndex --> duplicate source
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureDuplicateInputInfo(BYTE ucDuplicateIndex)
{
    EnumInputDataPath enumCurrentPath = GET_MEASURE_INPUT_PATH();
    EnumInputDataPath enumDuplicatePath = g_pstRegionTimingInfo[ucDuplicateIndex].stTimingInfo.enumInputDataPath;

    // Duplicate timing info
    *g_pstRegionTimingInfoPointer = g_pstRegionTimingInfo[ucDuplicateIndex];
    SET_MEASURE_INPUT_PATH(enumCurrentPath);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Duplcate format conversion setting
    ScalerFmtCnvDuplicateSetting(enumCurrentPath, enumDuplicatePath);
#endif

    // Duplicate VGIP setting
    ScalerMeasureDuplicateVgipSetting(enumDuplicatePath);

    // Duplicate interlace setting
    ScalerMeasureDuplicateInterlaceSetting(enumDuplicatePath);

    // Start auto-function
    ScalerMeasureSetAuto(_NORMAL_MEASURE, enumCurrentPath);

    // Start on-line measure
    ScalerMeasureSetOnlineMeasure(enumCurrentPath);

    // Pop out on-line measure result
    if(ScalerMeasureGetOnlineMeasureResult(&(g_pstRegionTimingInfoPointer->stMeasureSyncData), enumCurrentPath) == _FALSE)
    {
        return _FALSE;
    }

    ScalerMeasureDuplicateFinalSetting(ucDuplicateIndex);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Duplicate VGIP settting for measure
// Input Value  : ucDuplicateIndex --> duplicate target
// Output Value : None
//--------------------------------------------------
void ScalerMeasureDuplicateVgipSetting(EnumInputDataPath enumDuplicatePath)
{
    enumDuplicatePath = enumDuplicatePath;

    // Set VGIP input path
    ScalerVgipSetInputPath(GET_MEASURE_INPUT_PATH());

    // Disable digital capture
    ScalerVgipSetDigitalCaptureStatus(_DISABLE);

    // Initial IVS/IHS Delay for Capture and Auto
    ScalerVgipSetCaptureHDelay(0x0000);
    ScalerVgipSetCaptureVDelay(0x0000);

    // Bypass VS for DB apply
    ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);

    // Apply VGIP DB
    ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

    // Duplicate VGIP registors for HS/VS
    if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_M1_M2)
    {
        ScalerSetDWord(P0_10_M1_VGIP_CTRL, ScalerGetDWord(P80_10_S1_VGIP_CTRL));
        ScalerSetDWord(P40_10_M2_VGIP_CTRL, ScalerGetDWord(PC0_10_S2_VGIP_CTRL));
    }
    else if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_S1_S2)
    {
        ScalerSetDWord(P80_10_S1_VGIP_CTRL, ScalerGetDWord(P0_10_M1_VGIP_CTRL));
        ScalerSetDWord(PC0_10_S2_VGIP_CTRL, ScalerGetDWord(P40_10_M2_VGIP_CTRL));
    }
#if(_4P_DISPLAY_SUPPORT == _ON)
    else
    {
        BYTE ucToPage = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());
        BYTE ucFromPage = ScalerMeasureGetPageOffset(enumDuplicatePath);

        ScalerSetDWord((((WORD)ucToPage << 8) | P0_10_M1_VGIP_CTRL), ScalerGetDWord((((WORD)ucFromPage << 8) | P0_10_M1_VGIP_CTRL)));
    }
#endif

    // Apply VGIP DB
    ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_NO_POLLING);
}

//--------------------------------------------------
// Description  : Duplicate interlace settting for measure
// Input Value  : ucDuplicateIndex --> duplicate target
// Output Value : None
//--------------------------------------------------
void ScalerMeasureDuplicateInterlaceSetting(EnumInputDataPath enumDuplicatePath)
{
    enumDuplicatePath = enumDuplicatePath;

    if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_M1_M2)
    {
        // Select VGIP field detect latch edge
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT5, ScalerGetBit(P80_11_S1_VGIP_SIGINV, _BIT5));
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT5, ScalerGetBit(PC0_11_S2_VGIP_SIGINV, _BIT5));

        // Select VGIP field source; Select Odd delay one line field
        ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, (_BIT7 | _BIT6 | _BIT0)));
        ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), ScalerGetBit(PC0_13_S2_VGIP_ODD_CTRL, (_BIT7 | _BIT6 | _BIT0)));

        // Clear interlace detect flag
        ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        ScalerSetBit(P40_1A_M2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

        // Select video compensation field
        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~(_BIT7 | _BIT6), ScalerGetBit(P80_32_SCALE_CONTROL_REG_S1, (_BIT7 | _BIT6)));
    }
    else if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_S1_S2)
    {
        // Select VGIP field detect latch edge
        ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT5, ScalerGetBit(P0_11_M1_VGIP_SIGINV, _BIT5));
        ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT5, ScalerGetBit(P40_11_M2_VGIP_SIGINV, _BIT5));

        // Select VGIP field source; Select Odd delay one line field
        ScalerSetBit(P80_13_S1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, (_BIT7 | _BIT6 | _BIT0)));
        ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), ScalerGetBit(P40_13_M2_VGIP_ODD_CTRL, (_BIT7 | _BIT6 | _BIT0)));

        // Clear interlace detect flag
        ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        ScalerSetBit(PC0_1A_S2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

        // Select video compensation field
        ScalerSetBit(P80_32_SCALE_CONTROL_REG_S1, ~(_BIT7 | _BIT6), ScalerGetBit(P0_32_SCALE_CONTROL_REG, (_BIT7 | _BIT6)));
    }
#if(_4P_DISPLAY_SUPPORT == _ON)
    else
    {
        BYTE ucOffsetNew = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());
        BYTE ucOffset = ScalerMeasureGetPageOffset(enumDuplicatePath);

        // Select VGIP field detect latch edge
        SET_PAGED_BIT(ucOffsetNew, P0_11_M1_VGIP_SIGINV, ~_BIT5, GET_PAGED_BIT(ucOffset, P0_11_M1_VGIP_SIGINV, _BIT5));

        // Select VGIP field source; Select Odd delay one line field
        SET_PAGED_BIT(ucOffsetNew, P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), GET_PAGED_BIT(ucOffset, P0_13_M1_VGIP_ODD_CTRL, (_BIT7 | _BIT6 | _BIT0)));

        // Clear interlace detect flag
        SET_PAGED_BIT(ucOffsetNew, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

        // Select video compensation field
        SET_PAGED_BIT(ucOffsetNew, P0_32_SCALE_CONTROL_REG, ~(_BIT7 | _BIT6), GET_PAGED_BIT(ucOffset, P0_32_SCALE_CONTROL_REG, (_BIT7 | _BIT6)));
    }
#endif
}
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)

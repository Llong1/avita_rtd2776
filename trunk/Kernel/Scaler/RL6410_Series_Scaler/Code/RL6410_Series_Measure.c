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
// ID Code      : RL6410_Series_Measure.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerMeasureTimingChange(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, BYTE ucResultIndex);
bit ScalerMeasureCheckOnlineMeasureChange(EnumSourceSearchPort enumSourceSearchPort, BYTE ucResultIndex);
bit ScalerMeasureFinalSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
bit ScalerMeasureCheckVsBypass(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
void ScalerMeasureAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd, EnumInputDataPath enumInputDataPath);
bit ScalerMeasureGetAutoResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath, bit bWait);
void ScalerMeasureUpdateInputTimingPolarity(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, StructMeasureSyncData *pstMeasureSyncHV);
bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
bit ScalerMeasureGetOnlineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputDataPath enumInputDataPath);
void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumInputDataPath enumInputDataPath);
void ScalerMeasureSetInputRegionCount(EnumInputDataPath enumInputDataPath, EnumActiveRegionType enumRegion);
void ScalerMeasureSetDisplayRegionCount(EnumDisplayDataPath enumDisplayDataPath, EnumActiveRegionType enumRegion);
void ScalerMeasureSetOfflineMeasure(EnumSourceSearchPort enumSourcePort);
void ScalerMeasureInitialSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
void ScalerMeasureInterfaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort *penumSourceSearchPort);
void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion);
bit ScalerMeasureInterlaceCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);

bit ScalerMeasureDoubleCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, EnumRegionIndex enumRegionIndex);
void ScalerMeasureInterlaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
bit ScalerMeasureInterlaceDoubleCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, EnumRegionIndex enumRegionIndex);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
WORD ScalerMeasureGetTmdsPageOffset(EnumSourceSearchPort enumSourceSearchPort);
void ScalerMeasureCheckFirstLineShift(EnumSourceSearchPort enumSourceSearchPort, WORD usFrameHwidth);

#if(_DUAL_DVI_SUPPORT == _ON)
bit ScalerMeasureDualDviMergedCheck(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerMeasureDualDviOfflineCheck(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerMeasureDualDviOnlineCheck(BYTE ucResultIndex, EnumSourceSearchPort enumSourceSearchPort);
#endif

#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
bit ScalerMeasureDuplicateFinalSetting(BYTE ucDuplicateIndex);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check timing change
// Input Value  : enumSourceType --> source type
//                enumSourceSearchPort --> check port
//                ucResultIndex --> result index
// Output Value : _TRUE if HV timing Changed
//--------------------------------------------------
bit ScalerMeasureTimingChange(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, BYTE ucResultIndex)
{
    // Check on-line measure results
    bit bTimingChangeStatus = ((ScalerMeasureCheckOnlineMeasureChange(enumSourceSearchPort, ucResultIndex) == _TRUE) ||
                               (ScalerMeasureCheckWDTriggerStatus(ucResultIndex) == _TRUE));

    switch(enumSourceType)
    {
#if(_DUAL_DVI_SUPPORT == _ON)
        case _SOURCE_DVI:
            if(bTimingChangeStatus == _FALSE)
            {
                // Perform dual DVI on-line check
                bTimingChangeStatus |= (ScalerMeasureDualDviOnlineCheck(ucResultIndex, enumSourceSearchPort) == _FALSE);
            }
            break;
#endif

        default:
            break;
    }

    return bTimingChangeStatus;
}

//--------------------------------------------------
// Description  : Check timing change from off-line measure block
// Input Value  : enumSourceSearchPort --> check port
//                ucResultIndex --> result index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureCheckOnlineMeasureChange(EnumSourceSearchPort enumSourceSearchPort, BYTE ucResultIndex)
{
    bit bTimingChangeStatus = _FALSE;
    EnumInputDataPath enumInputDataPath = g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath;
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath) + 0x16;
    StructMeasureSyncData stMeasureSyncHV;
    memset(&stMeasureSyncHV, 0, sizeof(StructMeasureSyncData));

    enumSourceSearchPort = enumSourceSearchPort;

    // Pop up if on-line measure complete
    if(GET_PAGED_BIT(ucOffset, P16_02_MEAS_CTL1, _BIT7) == 0x00)
    {
        if(ScalerMeasureGetOnlineMeasureResult(&stMeasureSyncHV, enumInputDataPath) == _FALSE)
        {
            return _TRUE;
        }

#if(_VGA_SUPPORT == _ON)
        if(enumSourceSearchPort == _A0_INPUT_PORT)
        {
            // Check on-line measure result
            bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.b1HSP) ||
                                   (abs(stMeasureSyncHV.usHSPeriod - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usHSPeriod) > 2) ||
                                   (abs(stMeasureSyncHV.usVSPeriod - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usVSPeriod) > 2));
        }
        else
#endif
        {
#if(_FREESYNC_SUPPORT == _ON)
            if(GET_FREESYNC_ENABLED() == _TRUE)
            {
                // Check off-line measure result
                bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.b1HSP) ||
                                       (stMeasureSyncHV.b1VSP != g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.b1VSP) ||
                                       (abs(stMeasureSyncHV.usHWidth - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usHWidth) > 2) ||
                                       (abs(stMeasureSyncHV.usVHeight - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usVHeight) > 2));

#if(_DP_FREESYNC_SUPPORT == _ON)
                // DP Freesync case
                if(GET_DP_FREESYNC_ENABLED() == _TRUE)
                {
                    g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usVTotal = ScalerDpGetVSPeriod(enumInputDataPath);
                    g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usVFreq = ScalerDpGetVFreq(enumInputDataPath);
                }
                else
#endif
                {
                    if(abs(stMeasureSyncHV.usVSPeriod - g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usVTotal) > 2)
                    {
                        g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usVTotal = stMeasureSyncHV.usVSPeriod;
                        g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / stMeasureSyncHV.usHSPeriod / stMeasureSyncHV.usVSPeriod + 1) / 2;
                    }
                }
            }
            else
#endif
            {
                // Check on-line measure result
                bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.b1HSP) ||
                                       (stMeasureSyncHV.b1VSP != g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.b1VSP) ||
                                       (abs(stMeasureSyncHV.usHSPeriod - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usHSPeriod) > 2) ||
                                       (abs(stMeasureSyncHV.usVSPeriod - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usVSPeriod) > 2) ||
                                       (abs(stMeasureSyncHV.usHTotal - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usHTotal) > 2) ||
                                       (abs(stMeasureSyncHV.usHWidth - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usHWidth) > 2) ||
                                       (abs(stMeasureSyncHV.usVHeight - g_pstRegionTimingInfo[ucResultIndex].stMeasureSyncData.usVHeight) > 2));
            }
        }
    }

    return bTimingChangeStatus;
}

//--------------------------------------------------
// Description  : Initial measure block
// Input Value  : enumSourceType: source type
//              : enumSourceSearchPort: port type
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureFinalSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceType = enumSourceType;

    switch(enumSourceSearchPort)
    {
#if(_VGA_SUPPORT == _ON)
        case _A0_INPUT_PORT:

            // Set VGATOP capture
            ScalerVgaTopSetCapture();
            break;
#endif

        default:
            break;
    }

    // Check timing validity
    if((GET_INPUT_TIMING_HWIDTH() >= GET_INPUT_TIMING_HTOTAL()) ||
       (GET_INPUT_TIMING_VHEIGHT() >= GET_INPUT_TIMING_VTOTAL()))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check VGIP VS bypass
// Input Value  : enumSourceType -> source type
//                enumSourceSearchPort -> port type
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureCheckVsBypass(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceType)
    {
        case _SOURCE_DP:

            switch(enumSourceSearchPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                case _D6_INPUT_PORT:
#endif
                    return ScalerDpRx0CheckVgipVsBypass();
#endif


#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:

                    return ScalerDpRx1CheckVgipVsBypass();
#endif

                default:
                    break;
            }

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial V Boundary for Auto Function Measure
// Input Value  : V Boundary Start/End
///               enumInputDataPath --> auto data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd, EnumInputDataPath enumInputDataPath)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath);

    // Set V boundary
    SET_PAGED_BIT(ucOffset, P0_7C_AUTO_DUMMY, ~(_BIT3 | _BIT2), (((HIBYTE(usVBoundStart) & 0x10) >> 1) | ((HIBYTE(usVBoundEnd) & 0x10) >> 2)));
    SET_PAGED_BYTE(ucOffset, P0_73_V_BOUNDARY_H, (((HIBYTE(usVBoundStart) & 0x0F) << 4) | (HIBYTE(usVBoundEnd) & 0x0F)));
    SET_PAGED_BYTE(ucOffset, P0_74_V_BOUNDARY_STA_L, LOBYTE(usVBoundStart));
    SET_PAGED_BYTE(ucOffset, P0_75_V_BOUNDARY_END_L, LOBYTE(usVBoundEnd));
}

//--------------------------------------------------
// Description  : Pop Up Auto-Function Result
// Input Value  : stActiveRegion --> measure result
//                enumInputDataPath --> auto data path
//                bWait --> wait auto-function stop or not
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureGetAutoResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath, bit bWait)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath);

    if((bWait == _WAIT) || (GET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, _BIT6) == 0x00))
    {
        if(ScalerMeasureAutoFuncWaitFinish(enumInputDataPath) == _FALSE)
        {
            return _FALSE;
        }
    }

    pstActiveRegion->usVActiveStart = (((WORD)GET_PAGED_BIT(ucOffset, P0_7C_AUTO_DUMMY, _BIT1) << 11) |
                                       ((WORD)GET_PAGED_BIT(ucOffset, P0_7E_VER_START_END_H, 0xF0) << 4) |
                                       ((WORD)GET_PAGED_BYTE(ucOffset, P0_7F_VER_START_L)));

    pstActiveRegion->usVActiveEnd = (((WORD)GET_PAGED_BIT(ucOffset, P0_7C_AUTO_DUMMY, _BIT0) << 12) |
                                     ((WORD)GET_PAGED_BIT(ucOffset, P0_7E_VER_START_END_H, 0x0F) << 8) |
                                     ((WORD)GET_PAGED_BYTE(ucOffset, P0_80_VER_END_L)));

    pstActiveRegion->usHActiveStart = (((WORD)GET_PAGED_BIT(ucOffset, P0_78_BLU_NOISE_MARGIN, _BIT1) << 11) |
                                       ((WORD)GET_PAGED_BIT(ucOffset, P0_81_H_START_END_H, 0xF0) << 4) |
                                       ((WORD)GET_PAGED_BYTE(ucOffset, P0_82_H_START_L))) + 1;

    pstActiveRegion->usHActiveEnd = (((WORD)GET_PAGED_BIT(ucOffset, P0_78_BLU_NOISE_MARGIN, _BIT0) << 12) |
                                     ((WORD)GET_PAGED_BIT(ucOffset, P0_81_H_START_END_H, 0x0F) << 8) |
                                     ((WORD)GET_PAGED_BYTE(ucOffset, P0_83_H_END_L))) + 1;

    // Check auto-function measure result
    if(((pstActiveRegion->usVActiveStart == 0x00) &&
        (pstActiveRegion->usVActiveEnd == 0x00)) ||
       (pstActiveRegion->usHActiveStart == 0x00) ||
       (pstActiveRegion->usHActiveEnd == 0x00))
    {
        // No IDEN found.
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update timing info HS/VS polarity
// Input Value  : ucSourceType --> source type
//                stMeasureSyncHV --> measured timing data
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputTimingPolarity(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, StructMeasureSyncData *pstMeasureSyncHV)
{
#if((_HDMI_SUPPORT == _ON) || (_DVI_SUPPORT == _ON))
    WORD usHdmiPage = 0x0000;
#endif

    enumSourceSearchPort = enumSourceSearchPort;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Get Raw HSync Polarity by SyncProcessor Auto Run
            if(ScalerGetBit(P0_47_SYNC_SELECT, _BIT6) == _BIT6)
            {
                g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (bit)(pstMeasureSyncHV->b1HSP ^
                                                                         (((bit)ScalerGetBit(P0_48_SYNC_INVERT, _BIT3) ? _BIT0 : 0x00) ^
                                                                          ((bit)ScalerGetBit(P0_50_STABLE_PERIOD_H, _BIT6) ? _BIT0 : 0x00)));
            }
            else
            {
                g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (bit)(pstMeasureSyncHV->b1HSP ^ (((bit)ScalerGetBit(P0_48_SYNC_INVERT, _BIT3) ? _BIT0 : 0x00)));
            }

            // Check if VGATOP VS bypassed
            if(ScalerGetBit(P30_A1_VGATOP_VGIP_SIGINV, _BIT6) == _BIT6)
            {
                // Get VSP from measure result
                g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (pstMeasureSyncHV->b1VSP ^ (bit)ScalerGetBit(P30_01_MEAS_CTL0, _BIT3));
            }
            else
            {
                // Get VS polarity from VGATOP setting
                g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit(P30_A1_VGATOP_VGIP_SIGINV, _BIT3) == 0x00);
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            switch(enumSourceSearchPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                case _D6_INPUT_PORT:
#endif
                    // Pop out DP polarity
                    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (ScalerGetBit(PB6_0E_MSA_HSW_0, _BIT7));
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit(PB6_18_MSA_VSW_0, _BIT7));

                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:

                    // Pop out DP polarity
                    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (ScalerGetBit(PB9_0E_MSA_HSW_0, _BIT7));
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit(PB9_18_MSA_VSW_0, _BIT7));

                    break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
                case _D7_INPUT_PORT:

                    if(GET_D7_SWITCH_SELECT() == _D1_INPUT_PORT)
                    {
                        // Pop out DP polarity
                        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                        g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (ScalerGetBit(PB9_0E_MSA_HSW_0, _BIT7));
                        g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit(PB9_18_MSA_VSW_0, _BIT7));
                    }
                    else
                    {
                        // Pop out DP polarity
                        ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                        g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (ScalerGetBit(PB6_0E_MSA_HSW_0, _BIT7));
                        g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit(PB6_18_MSA_VSW_0, _BIT7));
                    }

                    break;
#endif

                default:
                    break;
            }

            break;
#endif

#if((_HDMI_SUPPORT == _ON) || (_DVI_SUPPORT == _ON))
        case _SOURCE_HDMI:
        case _SOURCE_DVI:

            switch(enumSourceSearchPort)
            {
#if(_D2_TMDS_SUPPORT == _ON)
                default:
                case _D2_INPUT_PORT:
                    break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
                case _D3_INPUT_PORT:
                    usHdmiPage = 0x7200 - 0x7100;
                    break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)
                case _D4_INPUT_PORT:
                    usHdmiPage = 0x7300 - 0x7100;
                    break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)
                case _D5_INPUT_PORT:
                    usHdmiPage = 0x7400 - 0x7100;
                    break;
#endif
            }

            if(ScalerGetBit((usHdmiPage + P71_A7_TMDS_PWDCTL), _BIT7) == _BIT7)
            {
                if(ScalerGetBit((usHdmiPage + P71_A4_TMDS_CTRL), (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
                {
                    // Read HS/VS polarity from MAC
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = (ScalerGetBit((usHdmiPage + P71_C0_HDCP_CR), _BIT6) == 0x00);
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = (ScalerGetBit((usHdmiPage + P71_C0_HDCP_CR), _BIT5) == 0x00);
                }
                else
                {
                    // Positive HS/VS under DE-only mode
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = _TRUE;
                    g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = _TRUE;
                }
            }
            else
            {
                g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP = pstMeasureSyncHV->b1HSP;
                g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP = pstMeasureSyncHV->b1VSP;
            }

            if(pstMeasureSyncHV->b1VSP == _FALSE)
            {
                // Set HDMI VS intert
                ScalerSetBit((usHdmiPage + P71_AF_TMDS_WDC), ~_BIT3, _BIT3);
                pstMeasureSyncHV->b1VSP = _TRUE;
            }

            if(pstMeasureSyncHV->b1HSP == _FALSE)
            {
                // Set HDMI HS intert
                ScalerSetBit((usHdmiPage + P71_AF_TMDS_WDC), ~_BIT2, _BIT2);
                pstMeasureSyncHV->b1HSP = _TRUE;
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Pop Up Sync Processor Measure Result
// Input Value  : stMeasureSyncHV --> measure result pointer
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV)
{
    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, P30_02_MEAS_CTL1, _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

    // Check measure result status
#if(_VGA_SUPPORT == _ON)
    if(ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT1 | _BIT0))
    {
        if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4)) != 0x00)
        {
            return _FALSE;
        }
    }
    else
#endif
    {
#if(_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            // Check measure result status
            if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check measure result status
            if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
            {
                return _FALSE;
            }
        }
    }

    // Pop up measurement result
    ScalerSetBit(P30_02_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P30_04_MEAS_ERROR_FLG1, _BIT6);
    pstMeasureSyncHV->b1VSP = (bit)ScalerGetBit(P30_04_MEAS_ERROR_FLG1, _BIT7);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (GET_DP_FREESYNC_ENABLED() == _TRUE))
    {
        // HSync Period
        pstMeasureSyncHV->usHSPeriod = ((DWORD)ScalerDpGetHSPeriod(GET_MEASURE_INPUT_PATH()) * _MEASURE_CLK / 1000000);

        // HSync Pulse Width
        pstMeasureSyncHV->usHSWidth = ScalerDpGetHSW(GET_MEASURE_INPUT_PATH());

        // VSync Period
        pstMeasureSyncHV->usVSPeriod = ScalerDpGetVSPeriod(GET_MEASURE_INPUT_PATH());
    }
    else
#endif
    {
        // HSync Period
        pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P30_05_MEAS_HS_PERIOD_A_M) & 0x1F) << 8) | (ScalerGetByte(P30_06_MEAS_HS_PERIOD_A_L))) + 1;

        // HSync Pulse Width
        pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P30_0A_MEAS_HS_PULSE_A_M) & 0x1F) << 8) | (ScalerGetByte(P30_0B_MEAS_HS_PULSE_A_L))) + 1;

        // VSync Period
        pstMeasureSyncHV->usVSPeriod = ((((WORD)ScalerGetByte(P30_08_MEAS_VS_PERIOD_A_M) & 0x3F) << 8) | (ScalerGetByte(P30_09_MEAS_VS_PERIOD_A_L))) + 1;
    }

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = ((((WORD)ScalerGetByte(P30_0C_MEAS_VS_PULSE_A_M) & 0x3F) << 8) | (ScalerGetByte(P30_0D_MEAS_VS_PULSE_A_L))) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = ((((WORD)ScalerGetByte(P30_0E_MEAS_HS_PERIOD_D_M) & 0x1F) << 8) | (ScalerGetByte(P30_0F_MEAS_HS_PERIOD_D_L))) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = ((((WORD)ScalerGetByte(P30_11_MEAS_VS_PERIOD_D_M) & 0x3F) << 8) | (ScalerGetByte(P30_12_MEAS_VS_PERIOD_D_L))) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = ((((WORD)ScalerGetByte(P30_13_MEAS_HS_PULSE_D_M) & 0x1F) << 8) | (ScalerGetByte(P30_14_MEAS_HS_PULSE_D_L))) + 1;

    // Resume original clock when clock divider enabled
    if(ScalerGetBit(P30_00_SYNC_SELECT, _BIT7) == _BIT7)
    {
        pstMeasureSyncHV->usHTotal = (pstMeasureSyncHV->usHTotal << 1);
        pstMeasureSyncHV->usHWidth = (pstMeasureSyncHV->usHWidth << 1);
    }

#if(_VGA_SUPPORT == _ON)
    if((ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT1 | _BIT0)) ||
       (ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2)))
    {
        if(ScalerMeasureGetStableMeasureResult(pstMeasureSyncHV) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get on-line measure result from target input data path
// Input Value  : stMeasureSyncHV --> measure result
//                enumInputDataPath --> measure input data path
// Output Value : _TRUE or _FALSE for on-line measure result
//--------------------------------------------------
bit ScalerMeasureGetOnlineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputDataPath enumInputDataPath)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath) + 0x16;

    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, GET_PAGED_ADDR(ucOffset, P16_02_MEAS_CTL1), _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

    // Check measure result status
    if(GET_PAGED_BIT(ucOffset, P16_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4)) != 0x00)
    {
        return _FALSE;
    }

    // Pop up measurement result
    SET_PAGED_BIT(ucOffset, P16_02_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)GET_PAGED_BIT(ucOffset, P16_04_MEAS_ERROR_FLG1, _BIT6);
    pstMeasureSyncHV->b1VSP = (bit)GET_PAGED_BIT(ucOffset, P16_04_MEAS_ERROR_FLG1, _BIT7);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_05_MEAS_HS_PERIOD_A_M) & 0x1F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_06_MEAS_HS_PERIOD_A_L))) + 1;

    // VSync Period
    pstMeasureSyncHV->usVSPeriod = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_08_MEAS_VS_PERIOD_A_M) & 0x3F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_09_MEAS_VS_PERIOD_A_L))) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_0A_MEAS_HS_PULSE_A_M) & 0x1F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_0B_MEAS_HS_PULSE_A_L))) + 1;

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_0C_MEAS_VS_PULSE_A_M) & 0x3F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_0D_MEAS_VS_PULSE_A_L))) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_0E_MEAS_HS_PERIOD_D_M) & 0x1F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_0F_MEAS_HS_PERIOD_D_L))) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_11_MEAS_VS_PERIOD_D_M) & 0x3F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_12_MEAS_VS_PERIOD_D_L))) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = ((((WORD)GET_PAGED_BYTE(ucOffset, P16_13_MEAS_HS_PULSE_D_M) & 0x1F) << 8) | (GET_PAGED_BYTE(ucOffset, P16_14_MEAS_HS_PULSE_D_L))) + 1;

#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType(enumInputDataPath) == _FC_SOURCE_ADC)
    {
        if(ScalerMeasureGetStableMeasureResult(pstMeasureSyncHV) == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Initialization for Picture Position <easure by Auto Function Measure
// Input Value  : enumMeasureFieldSelect --> Measure for Even or Odd Field
//                enumInputDataPath --> auto data path
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumInputDataPath enumInputDataPath)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(enumInputDataPath);

    // Disable auto-function
    SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Set auto VS delay to 0
    SET_PAGED_BIT(ucOffset, P0_1E_M1_VGIP_HV_DELAY, ~(_BIT5 | _BIT4), 0x00);

    if(enumFieldSelect == _EVEN_FIELD_MEASURE)
    {
        // Field Select to Even, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        SET_PAGED_BYTE(ucOffset, P0_7A_AUTO_ADJ_CTRL0, 0x80);
    }
    else if(enumFieldSelect == _ODD_FIELD_MEASURE)
    {
        // Field Select to Odd, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        SET_PAGED_BYTE(ucOffset, P0_7A_AUTO_ADJ_CTRL0, 0xC0);
    }
    else
    {
        // Disable Field Select, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        SET_PAGED_BYTE(ucOffset, P0_7A_AUTO_ADJ_CTRL0, 0x00);
    }

    // Set HW auto-phase: step = 32
    SET_PAGED_BYTE(ucOffset, P0_7B_HW_AUTO_PHASE_CTRL0, 0xF8);

    // Set H boundary
    ScalerMeasureAutoFuncHBoundInitial(0x0002, 0x1FFF, enumInputDataPath);

    // Set V Boundary
    ScalerMeasureAutoFuncVBoundInitial(0x0000, 0x1FFF, enumInputDataPath);

    // Digital Measure Mode, Select Auto Balance, Start Auto Function Measure; Start auto-function measure
    SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
}


//--------------------------------------------------
// Description  : Set for Region Count Measure
// Input Value  : enumInputDataPath --> input data path
//                ucRegion --> measure region type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetInputRegionCount(EnumInputDataPath enumInputDataPath, EnumActiveRegionType enumRegion)
{
    // Set region count path
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_ALL:
            // Frame sync line buffer measure only 1 path
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
            break;

        case _INPUT_PATH_M2:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
            break;

        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S1:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
            break;

        case _INPUT_PATH_S2:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
            break;

        default:
            ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
            break;
    }

    // Select source form M1; Set measure option; Disable Input Region Measure;
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT4 | _BIT3 | _BIT0), (enumRegion & (_BIT4 | _BIT3)));

    // Enable Input Active Region Measure
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Set for Region Count Measure
// Input Value  : enumDisplayDataPath --> measure target in D-domain
//                ucRegion --> measure region type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetDisplayRegionCount(EnumDisplayDataPath enumDisplayDataPath, EnumActiveRegionType enumRegion)
{
    switch(enumDisplayDataPath)
    {
        case _DISPLAY_PATH_M1:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
            break;

        case _DISPLAY_PATH_M2:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
            break;

        case _DISPLAY_PATH_S1:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
            break;

        case _DISPLAY_PATH_S2:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
            break;

        default:
            ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
            break;
    }

    // Select source form M1; Set measure option; Disable Input Region Measure;
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT4 | _BIT3 | _BIT0), (enumRegion & (_BIT4 | _BIT3)));

    // Disable Display  Active Region Measure
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Set for Sync Processor Measure Input HV
// Input Value  : enumSourcePort --> Input port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetOfflineMeasure(EnumSourceSearchPort enumSourcePort)
{
    // Reset off-line measure clock divider
    ScalerSetBit(P30_00_SYNC_SELECT, ~_BIT7, 0x00);

    // Power up off-line measure; Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
    ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT0), (_BIT7 | _BIT6));

    // Disable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    if(enumSourcePort == _A0_INPUT_PORT)
    {
        // Set off line measure source; Disable clock divider
        ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
    }
    else
    {
        switch(enumSourcePort)
        {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            case _D6_INPUT_PORT:
#endif
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Set input clock divider if clock > limit
                if(GET_D0_INPUT_PIXEL_CLK() > _DATA_PATH_SPEED_LIMIT)
                {
                    ScalerSetBit(P30_00_SYNC_SELECT, ~_BIT7, _BIT7);
                }

                break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

            case _D1_INPUT_PORT:
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                // Set input clock divider if clock > limit
                if(GET_D1_INPUT_PIXEL_CLK() > _DATA_PATH_SPEED_LIMIT)
                {
                    ScalerSetBit(P30_00_SYNC_SELECT, ~_BIT7, _BIT7);
                }

                break;

#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

            case _D2_INPUT_PORT:
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                break;

#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

            case _D3_INPUT_PORT:
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                break;

#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

            case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
                if(ScalerTMDSRx4GetDualDVIMode() == _TRUE)
                {
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
                }
                else
#endif
                {
                    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                }
                break;
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))

            case _D5_INPUT_PORT:
                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
                break;

#endif // End of #if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
            case _D7_INPUT_PORT:

                switch(GET_D7_SWITCH_SELECT())
                {
                    case _D1_INPUT_PORT:
                        // Input from D1
                        ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                        break;

                    case _D0_INPUT_PORT:
                    case _D7_INPUT_PORT:
                    default:
                        // Input from D0
                        ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                        break;
                }

                // Check for clock range
                if(ScalerSyncGetInputPixelClk(_D7_INPUT_PORT) > _DATA_PATH_SPEED_LIMIT)
                {
                    ScalerSetBit(P30_00_SYNC_SELECT, ~_BIT7, _BIT7);
                }

                break;

#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

            default:
                break;
        }
    }

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
}

//--------------------------------------------------
// Description  : Initial measure block
// Input Value  : enumSourceType: source type
//              : enumSourceSearchPort: port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInitialSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    DebugMessageMeasure("Measure input path", GET_MEASURE_INPUT_PATH());

    // Set VGIP input path
    ScalerVgipSetInputPath(GET_MEASURE_INPUT_PATH());

    // Initial format conversion
    ScalerFmtCnvInitialSetting(enumSourceSearchPort, GET_MEASURE_INPUT_PATH());

    // Initial VGIP for input signal pass through
    ScalerVgipInputInitial(enumSourceType);

    // Reset interlace flag
    g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace = _FALSE;
    g_pstRegionTimingInfoPointer->stTimingInfo.b1VideoField = _FALSE;

    // Set off-line measure target
    ScalerMeasureSetOfflineMeasure(enumSourceSearchPort);

    // On-line measure(M1 & M2 & S1 & S2) clock divider disable
    ScalerSetBit(P16_00_SYNC_SELECT, ~_BIT7, 0x00);
    ScalerSetBit(P56_00_SYNC_SELECT, ~_BIT7, 0x00);
    ScalerSetBit(P96_00_SYNC_SELECT, ~_BIT7, 0x00);
    ScalerSetBit(PD6_00_SYNC_SELECT, ~_BIT7, 0x00);

    // Save off-line measure port
    g_pstRegionTimingInfoPointer->stMeasureSyncData.b4MeasurePort = ScalerMeasureGetOfflineMeasurePort();
}

//--------------------------------------------------
// Description  : Initial measure interface
// Input Value  : enumSourceType: source type
//              : enumSourceSearchPort: port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInterfaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort *penumSourceSearchPort)
{
    enumSourceType = enumSourceType;

    switch(*penumSourceSearchPort)
    {
#if(_VGA_SUPPORT == _ON)
        case _A0_INPUT_PORT:

            // Special case for small DVS width
            if(ScalerGetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
            {
                if(ScalerSyncProcGetDeVsyncWidth() >= 4)
                {
                    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, ~(_BIT7 | _BIT6), 0x00);
                }
            }

            // Hsync Measure Source from SeHS or DeHS by CR49[6]
            ScalerSetBit(P0_49_SYNC_CTRL, ~_BIT2, _BIT2);

            break;
#endif


#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_TMDS_SUPPORT == _ON)

#if(_D2_HDMI_2_0_SUPPORT == _ON)
            // Initial D0 420 setting
            ScalerFmtCnv420To422D2InitialSetting();
#endif

            // Reset TMDS HS/VS polarity
            ScalerSetBit(P71_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_TMDS_SUPPORT == _ON)

#if(_D3_HDMI_2_0_SUPPORT == _ON)
            // Initial D0 420 setting
            ScalerFmtCnv420To422D3InitialSetting();
#endif

            // Reset TMDS HS/VS polarity
            ScalerSetBit(P72_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

#endif // End of #if(_D3_TMDS_SUPPORT == _ON)

            break;
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_TMDS_SUPPORT == _ON)

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            // Modify input port select for dual-DVI cases
            if(ScalerTMDSRx4GetDualDVIMode() == _FALSE)
            {
                *penumSourceSearchPort = _D5_INPUT_PORT;
            }

            // Reset TMDS HS/VS polarity
            ScalerSetBit(P74_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);
#endif

            // Reset TMDS HS/VS polarity
            ScalerSetBit(P73_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

#endif // End of #if(_D4_TMDS_SUPPORT == _ON)

            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_TMDS_SUPPORT == _ON)
            // Reset TMDS HS/VS polarity
            ScalerSetBit(P74_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);
#endif

            break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:

            break;
#endif // End of #if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Update timing info from measure
// Input Value  : stMeasureSyncHV --> measure result
//                stActiveRegion --> auto-function result
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion)
{
    // Update measure result
    g_pstRegionTimingInfoPointer->stTimingInfo.usHSWidth = ((pstMeasureSyncHV->b1HSP == _TRUE) ? pstMeasureSyncHV->usHSWidth : (pstMeasureSyncHV->usHSPeriod - pstMeasureSyncHV->usHSWidth));
    g_pstRegionTimingInfoPointer->stTimingInfo.usVSWidth = ((pstMeasureSyncHV->usVSWidth < (pstMeasureSyncHV->usVSPeriod >> 1)) ? pstMeasureSyncHV->usVSWidth : (pstMeasureSyncHV->usVSPeriod - pstMeasureSyncHV->usVSWidth));
    g_pstRegionTimingInfoPointer->stTimingInfo.usVTotal = pstMeasureSyncHV->usVSPeriod;
    g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal = pstMeasureSyncHV->usHTotal;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        // Update H total for single-to-F/B mode
        if(ScalerGetBit(P31_60_FRONT_BACK_CTRL, _BIT6) == 0x00)
        {
            g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal <<= 1;
        }
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType(GET_MEASURE_INPUT_PATH()) == _FC_SOURCE_ADC)
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.usHFreq = (_SYNC_PROC_CLK * 10 * 2 / pstMeasureSyncHV->usHSPeriod + 1) / 2;
        g_pstRegionTimingInfoPointer->stTimingInfo.usVFreq = (_SYNC_PROC_CLK * 1000 * 10 * 2 / pstMeasureSyncHV->usHSPeriod / pstMeasureSyncHV->usVSPeriod + 1) / 2;
    }
    else
#endif
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.usHFreq = (_MEASURE_CLK * 10 * 2 / pstMeasureSyncHV->usHSPeriod + 1) / 2;
        g_pstRegionTimingInfoPointer->stTimingInfo.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / pstMeasureSyncHV->usHSPeriod / pstMeasureSyncHV->usVSPeriod + 1) / 2;
    }

#if(_HDMI_2_0_SUPPORT == _ON)
    // Check 420 cases for H total
    switch(ScalerFmtCnvGetSourceType(GET_MEASURE_INPUT_PATH()))
    {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
        case _FC_SOURCE_D2:
            if(ScalerFmtCnv420To422D2GetStatus() == _TRUE)
            {
                g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal = (g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal << 1);
            }
            break;
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
        case _FC_SOURCE_D3:
            if(ScalerFmtCnv420To422D3GetStatus() == _TRUE)
            {
                g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal = (g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal << 1);
            }
            break;
#endif

        default:
            break;
    }
#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

    // Update auto-function result
    if(ScalerFmtCnvFtoPGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.usHStart = (pstActiveRegion->usHActiveStart << 1);
        g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth = ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth <<= 1;
        }
#endif
    }
    else if(ScalerFmtCnvHalfSDGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.usHStart = (pstActiveRegion->usHActiveStart << 1);
        g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth = (((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1) << 1);
    }
    else
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.usHStart = pstActiveRegion->usHActiveStart;
        g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth = ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1);
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    // DP Freesync case, IVst = 1
    if(GET_DP_FREESYNC_ENABLED() == _TRUE)
    {
        PDATA_WORD(0) = _DP_FREESYNC_IVSTART;
    }
    else
#endif
    {
        PDATA_WORD(0) = pstActiveRegion->usVActiveStart;
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        BYTE ucVstartLine = ((ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT4) == _BIT4) ? 0x00 : 0x01);
        g_pstRegionTimingInfoPointer->stTimingInfo.usVStart = (PDATA_WORD(0) << 1) + ucVstartLine;
        g_pstRegionTimingInfoPointer->stTimingInfo.usVHeight = (((pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1) << 1);
    }
    else
    {
        g_pstRegionTimingInfoPointer->stTimingInfo.usVStart = PDATA_WORD(0);
        g_pstRegionTimingInfoPointer->stTimingInfo.usVHeight = (pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1;
    }
}

//--------------------------------------------------
// Description  : Check Interlace
// Input Value  : enumSourceType --> input source Type
//                enumSourceSearchPort --> input port type
// Output Value : TRUE => Interlaced Detected
//--------------------------------------------------
bit ScalerMeasureInterlaceCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE ucOffset = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());
    bit bInterlacedFormat = _FALSE;
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    WORD usHdmiPage = 0x0000;
    WORD usVstart = 0x0000;
    WORD usVend = 0x0000;
    StructAutoActiveData stAutoActiveData;
    memset(&stAutoActiveData, 0, sizeof(StructAutoActiveData));
#endif

    enumSourceSearchPort = enumSourceSearchPort;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            bInterlacedFormat = (ScalerMeasureVgaInterlaceCheck(enumSourceSearchPort) == _TRUE);

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _SOURCE_DVI:
        case _SOURCE_HDMI:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if(enumSourceSearchPort == _D2_INPUT_PORT)
            {
                if(ScalerTMDSRx2GetDualDVIMode() == _FALSE)
                {
                    enumSourceSearchPort = _D3_INPUT_PORT;
                }
            }
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if(enumSourceSearchPort == _D3_INPUT_PORT)
            {
                enumSourceSearchPort = _D4_INPUT_PORT;
            }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(enumSourceSearchPort == _D4_INPUT_PORT)
            {
                if(ScalerTMDSRx4GetDualDVIMode() == _FALSE)
                {
                    enumSourceSearchPort = _D5_INPUT_PORT;
                }
            }
#endif

            usHdmiPage = ScalerMeasureGetTmdsPageOffset(enumSourceSearchPort);

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit((usHdmiPage + P71_72_IVHS_CTRL_2), ~_BIT6, _BIT6);

            // Clear Interlace toggle flag
            ScalerSetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~_BIT6, _BIT6);

            // Delay until field stable
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());
            ScalerMeasureGetAutoResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _NOT_WAIT);
            g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart = stAutoActiveData.usVActiveStart;
            g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd = stAutoActiveData.usVActiveEnd;

            // Get another V start
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());
            ScalerMeasureGetAutoResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _NOT_WAIT);
            usVstart = stAutoActiveData.usVActiveStart;
            usVend = stAutoActiveData.usVActiveEnd;

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ScalerGetBit((usHdmiPage + P71_A4_TMDS_CTRL), (_BIT4 | _BIT3)) != (_BIT4 | _BIT3))
            {
                // Detect by Vtotal
                if(ScalerGetBit((usHdmiPage + P71_72_IVHS_CTRL_2), _BIT6) == _BIT6)
                {
                    // Interlace field signal from IHV delay; Odd inverted
                    ScalerSetBit((usHdmiPage + P71_70_IVHS_CTRL_0), ~(_BIT7 | _BIT2), (_BIT7 | _BIT2));
                    ScalerSetBit((usHdmiPage + P71_72_IVHS_CTRL_2), ~_BIT7, _BIT7);

                    // Set Video Compensation to ODD Field
                    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, 0x00);

                    // Wait until TMDS IHV delay change
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH());

                    // Check delay one line (with one-mimus Vstart after IHV delay enabled)
                    g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart -= 1;
                    g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd -= 1;
                    usVstart -= 1;
                    usVend -= 1;

                    ScalerMeasureCheckInterlaceVst(usVstart, usVend);

                    // Clear VGIP Interlace Toggle Flag
                    ScalerSetBit((usHdmiPage + P71_72_IVHS_CTRL_2), ~_BIT6, _BIT6);

                    bInterlacedFormat = _TRUE;
                    break;
                }
            }
            else
#endif
            {
                // Detect by VS Position
                if(ScalerGetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, _BIT6) == _BIT6)
                {
                    if(ScalerGetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, _BIT5) == 0x00)
                    {
                        // Interlace field signal from interface
                        SET_PAGED_BIT(ucOffset, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

                        // Set Video Compensation to EVEN Field
                        SET_PAGED_BIT(ucOffset, P0_32_SCALE_CONTROL_REG, ~_BIT6, _BIT6);

                        // Check delay one line
                        ScalerMeasureCheckInterlaceVst(usVstart, usVend);

                        // Clear Interlace toggle flag
                        ScalerSetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~_BIT6, _BIT6);

                        bInterlacedFormat = _TRUE;
                        break;
                    }
                }
            }

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit((usHdmiPage + P71_72_IVHS_CTRL_2), ~_BIT6, _BIT6);

            // Clear Interlace toggle and error flag
            ScalerSetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            break;
#endif

#if(_DP_SUPPORT == _ON)

        case _SOURCE_DP:

            if(((enumSourceSearchPort == _D0_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)) ||

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
               ((enumSourceSearchPort == _D6_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)) ||
#endif
               ((enumSourceSearchPort == _D1_INPUT_PORT) && (ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)))
            {
                // Interlace field signal from interface
                SET_PAGED_BIT(ucOffset, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

                // Set Video Compensation to EVEN Field
                SET_PAGED_BIT(ucOffset, P0_32_SCALE_CONTROL_REG, ~_BIT6, _BIT6);

                bInterlacedFormat = _TRUE;
                break;
            }

            if(((enumSourceSearchPort == _D0_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))) ||

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
               ((enumSourceSearchPort == _D6_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))) ||
#endif
               ((enumSourceSearchPort == _D1_INPUT_PORT) && (ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))))
            {
                if(GET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                {
                    // Select Filed Signal from VGIP
                    SET_PAGED_BIT(ucOffset, P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, _BIT0);

                    // Set Video Compensation to ODD Field
                    SET_PAGED_BIT(ucOffset, P0_32_SCALE_CONTROL_REG, ~_BIT6, 0x00);

                    // Clear VGIP Interlace Toggle Flag
                    SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                    bInterlacedFormat = _TRUE;
                    break;
                }
            }

            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            break;
#endif
        default:
            break;
    }

    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
    {
        // Align M2 field source with M1
        ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~_BIT0, ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT0));
    }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(GET_MEASURE_INPUT_PATH() == _INPUT_PATH_ALL)
    {
        // Align S1/S2 field source with M1/M2
        ScalerSetByte(P80_13_S1_VGIP_ODD_CTRL, ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL));
        ScalerSetByte(PC0_13_S2_VGIP_ODD_CTRL, ScalerGetByte(P40_13_M2_VGIP_ODD_CTRL));
        ScalerSetByte(P80_32_SCALE_CONTROL_REG_S1, ScalerGetByte(P0_32_SCALE_CONTROL_REG));
        ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
    }
#endif

    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
    {
        // Align S2 field source with S1
        ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~_BIT0, ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT0));
    }

    return bInterlacedFormat;
}

//--------------------------------------------------
// Description  : Timing double check
// Input Value  : enumSourceType --> input source Type
//                enumSourceSearchPort --> input port type
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureDoubleCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, EnumRegionIndex enumRegionIndex)
{
    bit bDoubleCheckStatus = _FALSE;

    bDoubleCheckStatus = (ScalerMeasureInterlaceDoubleCheck(enumSourceType, enumSourceSearchPort, enumRegionIndex) ==
                          g_pstRegionTimingInfo[enumRegionIndex].stTimingInfo.b1Interlace);

    return bDoubleCheckStatus;
}

//--------------------------------------------------
// Description  : Initial Interlace Detection Method
// Input Value  : enumSourceType --> input source Type
//                enumSourceSearchPort --> input port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInterlaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M1) != 0x00)
    {
        // Disable IVS Delay one line; Default field source from interface
        ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

        // Clear VGIP Interlace Toggle Flag
        ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
    }

    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_M2) != 0x00)
    {
        // Disable IVS Delay one line; Default field source from interface
        ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

        // Clear VGIP Interlace Toggle Flag
        ScalerSetBit(P40_1A_M2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
    }

    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S1) != 0x00)
    {
        // Disable IVS Delay one line; Default field source from interface
        ScalerSetBit(P80_13_S1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

        // Clear VGIP Interlace Toggle Flag
        ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
    }

    if((GET_MEASURE_INPUT_PATH() & _INPUT_PATH_S2) != 0x00)
    {
        // Disable IVS Delay one line; Default field source from interface
        ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

        // Clear VGIP Interlace Toggle Flag
        ScalerSetBit(PC0_1A_S2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
    }

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Clear Interlace toggle flag
            ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            switch(enumSourceSearchPort)
            {
#if(_D2_TMDS_SUPPORT == _ON)
                case _D2_INPUT_PORT:
                    // Clear Interlace toggle and error flag
                    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                    // Disable IHV delay control; inverted odd signal; odd from IHV delay
                    ScalerSetBit(P71_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), _BIT2);
                    ScalerSetBit(P71_72_IVHS_CTRL_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
                case _D3_INPUT_PORT:
                    // Clear Interlace toggle and error flag
                    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                    // Disable IHV delay control; inverted odd signal; odd from IHV delay
                    ScalerSetBit(P72_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), _BIT2);
                    ScalerSetBit(P72_72_IVHS_CTRL_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)
                case _D4_INPUT_PORT:
                    // Clear Interlace toggle and error flag
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                    // Disable IHV delay control; inverted odd signal; odd from IHV delay
                    ScalerSetBit(P73_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), _BIT2);
                    ScalerSetBit(P73_72_IVHS_CTRL_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)
                case _D5_INPUT_PORT:
                    // Clear Interlace toggle and error flag
                    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_50_PORT_PAGE74_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                    // Disable IHV delay control; inverted odd signal; odd from IHV delay
                    ScalerSetBit(P74_70_IVHS_CTRL_0, ~(_BIT7 | _BIT2), _BIT2);
                    ScalerSetBit(P74_72_IVHS_CTRL_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                    break;
#endif

                default:
                    break;
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Interlace
// Input Value  : enumSourceType --> input source Type
//                enumSourceSearchPort --> input port type
// Output Value : TRUE => Interlaced Detected
//--------------------------------------------------
bit ScalerMeasureInterlaceDoubleCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, EnumRegionIndex enumRegionIndex)
{
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    WORD usHdmiPage = 0x0000;
#endif
    BYTE ucOffset = ScalerMeasureGetPageOffset(g_pstRegionTimingInfo[enumRegionIndex].stTimingInfo.enumInputDataPath);

    enumSourceSearchPort = enumSourceSearchPort;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            return g_pstRegionTimingInfo[enumRegionIndex].stTimingInfo.b1Interlace;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _SOURCE_DVI:
        case _SOURCE_HDMI:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if(enumSourceSearchPort == _D2_INPUT_PORT)
            {
                if(ScalerTMDSRx2GetDualDVIMode() == _FALSE)
                {
                    enumSourceSearchPort = _D3_INPUT_PORT;
                }
            }
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if(enumSourceSearchPort == _D3_INPUT_PORT)
            {
                enumSourceSearchPort = _D4_INPUT_PORT;
            }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(enumSourceSearchPort == _D4_INPUT_PORT)
            {
                if(ScalerTMDSRx4GetDualDVIMode() == _FALSE)
                {
                    enumSourceSearchPort = _D5_INPUT_PORT;
                }
            }
#endif

            usHdmiPage = ScalerMeasureGetTmdsPageOffset(enumSourceSearchPort);

            // Clear VGIP Interlace Toggle Flag
            SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Clear Interlace toggle flag
            ScalerSetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~_BIT6, _BIT6);

            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, g_pstRegionTimingInfo[enumRegionIndex].stTimingInfo.enumInputDataPath);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, g_pstRegionTimingInfo[enumRegionIndex].stTimingInfo.enumInputDataPath);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ScalerGetBit((usHdmiPage + P71_A4_TMDS_CTRL), (_BIT4 | _BIT3)) != (_BIT4 | _BIT3))
            {
                // Detect by Vtotal
                if(GET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                {
                    // Clear VGIP Interlace Toggle Flag
                    SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                    return _TRUE;
                }
            }
            else
#endif
            {
                // Detect by VS Position
                if(ScalerGetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, _BIT6) == _BIT6)
                {
                    if(ScalerGetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, _BIT5) == 0x00)
                    {
                        // Clear Interlace toggle flag
                        ScalerSetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~_BIT6, _BIT6);
                        return _TRUE;
                    }
                    else
                    {
                        // Clear Interlace toggle and error flag
                        ScalerSetDataPortBit((usHdmiPage + P71_C9_HDMI_AP), _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
                    }
                }
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)

        case _SOURCE_DP:

            if(((enumSourceSearchPort == _D0_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)) ||

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
               ((enumSourceSearchPort == _D6_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)) ||
#endif
               ((enumSourceSearchPort == _D1_INPUT_PORT) && (ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)))
            {
                return _TRUE;
            }

            if(((enumSourceSearchPort == _D0_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))) ||

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
               ((enumSourceSearchPort == _D6_INPUT_PORT) && (ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))) ||
#endif
               ((enumSourceSearchPort == _D1_INPUT_PORT) && (ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))))
            {
                if(GET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                {
                    // Clear VGIP Interlace Toggle Flag
                    SET_PAGED_BIT(ucOffset, P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                    return _TRUE;
                }
            }

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Return HDMI/DVI port page offset
// Input Value  : enumSourceSearchPort
// Output Value : HDMI page offset by port
//--------------------------------------------------
WORD ScalerMeasureGetTmdsPageOffset(EnumSourceSearchPort enumSourceSearchPort)
{
    WORD usHdmiPage = 0x0000;

    switch(enumSourceSearchPort)
    {
#if(_D2_TMDS_SUPPORT == _ON)
        default:
        case _D2_INPUT_PORT:
            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            usHdmiPage = 0x7200 - 0x7100;
            break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            usHdmiPage = 0x7300 - 0x7100;
            break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            usHdmiPage = 0x7400 - 0x7100;
            break;
#endif
    }

    return usHdmiPage;
}

//--------------------------------------------------
// Description  : Measure H width for the first line
// Input Value  : enumSourceSearchPort --> port to be checked
//                usFrameHwidth --> H width from measure block
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerMeasureCheckFirstLineShift(EnumSourceSearchPort enumSourceSearchPort, WORD usFrameHwidth)
{
    WORD usHdmiPage = ScalerMeasureGetTmdsPageOffset(enumSourceSearchPort);
    BYTE ucOffset = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());

    // Check under DE-only mode with raw HS/VS
    if((ScalerGetBit((usHdmiPage + P71_A7_TMDS_PWDCTL), _BIT7) == _BIT7) &&
       (ScalerGetBit((usHdmiPage + P71_A4_TMDS_CTRL), (_BIT4 | _BIT3)) == (_BIT4 | _BIT3)))
    {
        // Stop auto-function
        SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        // Set measure boundary to first line
        ScalerMeasureAutoFuncHBoundInitial(0x0002, 0x1FFF, GET_MEASURE_INPUT_PATH());
        ScalerMeasureAutoFuncVBoundInitial((GET_ACTIVE_V_START() + 1), GET_INPUT_TIMING_VTOTAL(), GET_MEASURE_INPUT_PATH());

        // Start auto-function measure
        SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        if((ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FAIL) ||
           (ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FAIL))
        {
            return;
        }

        // Calculate first H width
        PDATA_WORD(0) = ((((WORD)GET_PAGED_BIT(ucOffset, P0_81_H_START_END_H, 0xF0)) << 4) | GET_PAGED_BYTE(ucOffset, P0_82_H_START_L)); // H st
        PDATA_WORD(1) = ((((WORD)GET_PAGED_BIT(ucOffset, P0_81_H_START_END_H, 0x0F)) << 8) | GET_PAGED_BYTE(ucOffset, P0_83_H_END_L)); // H end
        PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0) + 1); // H width

        if(abs(PDATA_WORD(2) - usFrameHwidth) <= 1)
        {
            // First line shift detected; Disable DE-only mode
            ScalerSetBit((usHdmiPage + P71_A7_TMDS_PWDCTL), ~_BIT7, 0x00);
        }
    }
}

#if(_DUAL_DVI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check dual DVI status
// Input Value  : enumSourceSearchPort --> search port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureDualDviMergedCheck(EnumSourceSearchPort enumSourceSearchPort)
{
    WORD usHstart = 0xFFFF;
    WORD usHend = 0x0000;
    WORD usTargetHwidth = 0x0000;
    BYTE ucIndex = 0;
    BYTE ucOffset = ScalerMeasureGetPageOffset(GET_MEASURE_INPUT_PATH());
    StructMeasureSyncData stMeasureSyncData;
    StructAutoActiveData stAutoActiveData;
    memset(&stMeasureSyncData, 0, sizeof(StructMeasureSyncData));
    memset(&stAutoActiveData, 0, sizeof(StructAutoActiveData));

    /////////////////////////////////
    // 1. Measure H width from single DVI
    /////////////////////////////////

    // Stop off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Switch to single DVI
    ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2); // D4

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Restart off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

    // Pop out off-line measure result
    if(ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncData) == _FALSE)
    {
        return _FALSE;
    }

    // Get target H width from single path
    if(ScalerFmtCnvHalfSDGetStatus(GET_MEASURE_INPUT_PATH()) == _TRUE)
    {
        usTargetHwidth = stMeasureSyncData.usHWidth;
    }
    else
    {
        usTargetHwidth = (stMeasureSyncData.usHWidth << 1);
    }

    // Reset off-line measure
    ScalerMeasureSetOfflineMeasure(enumSourceSearchPort);

    /////////////////////////////////
    // 2. Search for H start/end
    /////////////////////////////////

    // Stop auto-function; Switch to software mode
    SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT0), 0x00);

    for(ucIndex = 0; ucIndex < 13; ++ucIndex) // 13 x 2 = 26 frames needed
    {
        // Start auto-function
        SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        // Get auto result
        if(ScalerMeasureGetAutoResult(&stAutoActiveData, GET_MEASURE_INPUT_PATH(), _WAIT) == _FALSE)
        {
            return _FALSE;
        }

        // Compare H start
        if(usHstart > stAutoActiveData.usHActiveStart)
        {
            usHstart = stAutoActiveData.usHActiveStart;
        }

        // Compare H end
        if(usHend < stAutoActiveData.usHActiveEnd)
        {
            usHend = stAutoActiveData.usHActiveEnd;
        }

        // Check H width change
        if((usHend - usHstart + 1) != usTargetHwidth)
        {
            // Choose clock invert
            ScalerSyncDualDVIClockInvert(enumSourceSearchPort);

            return _FALSE;
        }
        else
        {
            // Toggle clock polarity, twice
            ScalerSyncDualDVIClockInvert(enumSourceSearchPort);
            ScalerSyncDualDVIClockInvert(enumSourceSearchPort);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Offline check for dual DVI
// Input Value  : enumSourceSearchPort --> input port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureDualDviOfflineCheck(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case _D4_INPUT_PORT:
        case _D5_INPUT_PORT:

            // Check DVI timing format
            if(ScalerSyncDualDVIDoubleCheck(enumSourceSearchPort, GET_INPUT_TIMING_HWIDTH(), GET_INPUT_TIMING_VHEIGHT()) == _FALSE)
            {
                // Current Timing is not Reasonable, Toggle dual DVI format
                ScalerTMDSRx4DualDVISwitch(!ScalerTMDSRx4GetDualDVIMode());
                return _FALSE;
            }

            // Check dual DVI clock edge
            if((ScalerTMDSRx4GetDualDVIMode() == _TRUE) &&
               (ScalerMeasureDualDviMergedCheck(enumSourceSearchPort) == _FALSE))
            {
                return _FALSE;
            }
            break;
#endif

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Online check for dual DVI
// Input Value  : ucResultIndex --> timing info index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureDualDviOnlineCheck(BYTE ucResultIndex, EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE ucOffset = 0x00;

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
    if(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, _BIT7) == _BIT7)
    {
        // Do on-line check only on the first DVI path
        if(ucResultIndex != _REGION_INDEX_0)
        {
            // Get current format conversion source type
            pData[0] = ScalerFmtCnvGetSourceType(g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath);

            // Check duplicated dual DVI display; Skip on-line check if found
            for(ucOffset = 0; ucOffset < ucResultIndex; ++ucOffset)
            {
                if(ScalerFmtCnvGetSourceType(g_pstRegionTimingInfo[ucOffset].stTimingInfo.enumInputDataPath) ==
                   pData[0])
                {
                    return _TRUE;
                }
            }
        }

        ucOffset = ScalerMeasureGetPageOffset(g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath);

        // Check after auto-function finished
        if(GET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            StructAutoActiveData stActiveRegion;
            memset(&stActiveRegion, 0, sizeof(StructAutoActiveData));

            // Pop out auto-function result
            if(ScalerMeasureGetAutoResult(&stActiveRegion, g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath, _NOT_WAIT) == _FALSE)
            {
                return _FALSE;
            }

            // Check H width
            if(ScalerFmtCnvHalfSDGetStatus(g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.enumInputDataPath) == _TRUE)
            {
                if((stActiveRegion.usHActiveEnd - stActiveRegion.usHActiveStart + 1) != (g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usHWidth >> 1))
                {
                    // Dual DVI meta-stable detected; Invert PHY to MAC 1x Clk Edge
                    ScalerSyncDualDVIClockInvert(enumSourceSearchPort);
                }
            }
            else
            {
                if((stActiveRegion.usHActiveEnd - stActiveRegion.usHActiveStart + 1) != g_pstRegionTimingInfo[ucResultIndex].stTimingInfo.usHWidth)
                {
                    // Dual DVI meta-stable detected; Invert PHY to MAC 1x Clk Edge
                    ScalerSyncDualDVIClockInvert(enumSourceSearchPort);
                }
            }

            // Resetart auto-function in software mode
            SET_PAGED_BIT(ucOffset, P0_7D_AUTO_ADJ_CTRL1, ~(_BIT6 | _BIT0), _BIT0);
        }
    }
#endif

    return _TRUE;
}

#endif // End of #if(_DUAL_DVI_SUPPORT == _ON)
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Duplicate Input Timing
// Input Value  : ucDuplicateIndex --> duplicate source
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureDuplicateFinalSetting(BYTE ucDuplicateIndex)
{
    ucDuplicateIndex = ucDuplicateIndex;
    return _TRUE;
}
#endif


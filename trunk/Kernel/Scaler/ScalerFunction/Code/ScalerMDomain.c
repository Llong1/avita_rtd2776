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
// ID Code      : ScalerMDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MDOMAIN__

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

DWORD g_ulDClkFreq;

StructMDomainInfo g_stMDomainInfo;
StructTimingInfo g_stMDomainInputData;
StructDisplayInfo g_stMDomainOutputData;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
bit g_bAspectOriginMode = 0;
#endif

#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
WORD g_usDVFreq;
#endif

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
WORD g_usUseMemoryBW;
DWORD g_ulFRCMemoryRemainBW;
#endif

#if(_FRC_SUPPORT == _ON)
StructFRCInfo g_pstFRCInfo[_MULTI_DISPLAY_MAX];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerMDomainControl(void);
#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON) || (_FREESYNC_SUPPORT == _ON))
#if(_FRC_SUPPORT == _ON)
bit ScalerMDomainFSLineBufferDclkDvtotalCheck(void);
#endif
#endif

BYTE ScalerMDomainGetDpllSscgDivMode(void);

void ScalerMDomainSetDDomain(const StructSDRAMDataInfo *pstFIFOScaling);

void ScalerMDomainCheckDisplayFormat(EnumDisplayRegion enumDisplayRegion);
void ScalerMDomainMemoryConfig(void);
void ScalerMDomainFSVgipDoubleBufferApply(void);
void ScalerMDomainSetDisplayTimingGenBackground(EnumDisplayMode enumDisplayMode);

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))
void ScalerMDomainSetSubBackground(void);
void ScalerMDomainGetSubBackground(StructTimingFormat *pstTimingFormat);
#endif

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
void ScalerMDomainSetSubActiveRegion(void);
#endif

BYTE ScalerMDomainMemorySelectConfirm(void);
void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth);
WORD ScalerMDomainGetVerticalAdjustLimit(EnumSourceTypeDef enumSourceTypeDef);
DWORD ScalerMDomainGetDisplayActiveRegion(void);

#if(_I_DITHER_SUPPORT == _ON)
BYTE ScalerMDomainGetColorDepth(void);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
void ScalerMDomainAspectOriginMode(bit bOn);
#endif

#if(_FRC_SUPPORT == _ON)
DWORD ScalerMDomainGetCurBW(void);
#endif

#if(_OD_SUPPORT == _ON)
DWORD ScalerMDomainODConfig(void);
void ScalerMDomainODUseBitInitial(void);
WORD ScalerMDomainODCalculateMemoryUseSpace(BYTE ucODbit);
WORD ScalerMDomainODCalculateMemoryUseBW(BYTE ucODbit);

#if(_FRC_SUPPORT == _ON)
void ScalerMDomainReleaseFRCMemoryBW(EnumInputDataPath enumInputPath);
#endif // End of #if(_FRC_SUPPORT == _ON)

#endif // End of #if(_OD_SUPPORT == _ON)

WORD ScalerMDomainGetDisplayBackgroundVstart(void);
WORD ScalerMDomainGetDisplayVheight(void);
void ScalerMDomainSetDisplayTimingGen(EnumDisplayDataPath enumDisplayDataPath);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : M Domain Main Process
// Input Value  : None
// Output Value : M domain check pass or fail
//--------------------------------------------------
bit ScalerMDomainControl(void)
{
    StructSDRAMDataInfo stFIFOScaling;

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    DWORD ulFRCRemainBW = 0;
#endif

#if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
    SET_MEMORY_DVF_SELECT(ScalerDisplaySelectDVFMode());
    ScalerDisplaySetDVFreq();
#endif

    ScalerMDomainMemoryConfig();

    // Update DVT in Line buffer frame sync
    if(GET_MEMORY_CONFIG() == _LINE_BUFFER_MODE)
    {
        g_stMDomainOutputData.usVTotal = ((DWORD)g_stMDomainInputData.usHFreq * (DWORD)(g_stMDomainOutputData.usVHeight) / g_stMDomainInputData.usVHeight * 1000) / g_stMDomainInputData.usVFreq;
    }

    // Select Memory Configuration Type
    SET_MEMORY_SELECT(ScalerMDomainMemorySelectConfirm());

    // Disable Spread Spectrum
    if(g_stMDomainInfo.enumDisplayMode == _DISPLAY_MODE_1P)
    {
        ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _OFF);
    }

    // Get Scaling size in FIFO
    if(ScalerScalingGetFIFOScalingSize(&stFIFOScaling) == _FAIL)
    {
        DebugMessageScaler("Fail : Calculate FIFO Size", stFIFOScaling.usInputHWidth);
        return _FALSE;
    }

    // Scaling Down Setting
    ScalerScalingSetScalingDown(&stFIFOScaling);

#if(_OD_SUPPORT == _ON)
#if(_FRC_SUPPORT == _ON)
    // Check OD use bit
    ulFRCRemainBW = ScalerMDomainODConfig();
#else
    // Check OD use bit
    ScalerMDomainODConfig();
#endif
#endif // End of #if(_OD_SUPPORT == _ON)

    // Enable Active Region Measure
    ScalerMeasureSetInputRegionCount(GET_MDOMAIN_INPUT_DATA_PATH(), _ACTIVE_REGION_TYPE);

    DebugMessageScaler("Freesync", GET_FREESYNC_ENABLED());
    DebugMessageScaler("Memory Work Select", GET_MEMORY_SELECT());

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    // Set Memory Utilization
    switch(GET_MEMORY_SELECT())
    {
        case _FRAME_SYNC_LINE_BUFFER:

            // Initial M Domain Block
            ScalerMemoryInitial();

            // Set FIFO freq.
            ScalerMemorySetFIFOFreq(_SCALER_FIFO_FREQ_M2PLL);

            // Set D-domain blocks: SU, fifo & display format
            ScalerMDomainSetDDomain(&stFIFOScaling);

            // Fine Tune DClk Offset
            ScalerDPLLFineTuneFrameSyncLineBuffer();

            // Adjust IVS/IHS for Position Range
            ScalerIDomainVgipAdjustIHVDelay();
            break;

#if(_FRC_SUPPORT == _ON)

        case _FRAME_SYNC_MEMORY:
        case _FREE_RUN_MEMORY:
        case _MN_FRAME_SYNC_MEMORY:

            // Adjust IVS/IHS for Position Range
            ScalerIDomainVgipAdjustIHVDelay();

            // Set D-domain blocks: SU, fifo & display format
            ScalerMDomainSetDDomain(&stFIFOScaling);

            // Initial M Domain Block
            if(ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_DATA_PATH()) == _TRUE)
            {
                ScalerMemoryInitial();

                // Set FIFO freq.
                ScalerMemorySetFIFOFreq(_SCALER_FIFO_FREQ_MPLL);
            }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            // Get Rotation status
            if(ScalerRotationCheckStatus() == _TRUE)
            {
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
                if(GET_ROT_TYPE() == _ROT_VER_MIRROR)
                {
                    // Set FRC control
                    ScalerFRCControl(&stFIFOScaling);
                }
                else
#endif
                {
                    // Set Rotation
                    ScalerRotationControl(&stFIFOScaling);
                }
            }
            else
#endif
            {
                // Set FRC control
                ScalerFRCControl(&stFIFOScaling);
            }

            if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
            {
                ScalerDPLLFineTuneFrameSyncFrameBuffer();
            }
#if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _ON)
            else if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
            {
                ScalerDPLLFineTuneFrameSyncFrameBuffer();
            }
#endif

            break;

#endif // End of #if(_FRC_SUPPORT == _ON)

        default:

            // Initial M Domain Block
            ScalerMemoryInitial();

            break;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    if(ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_DATA_PATH()) == _FALSE)
    {
        ScalerGlobalIDDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);
    }
    else
    {
        // Apply double buffer
        if((GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) || (GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) || (GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY))
        {
            ScalerMDomainFSVgipDoubleBufferApply();
        }
        else
        {
            ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);
        }
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }

    // Enable Spread Spectrum
    if(g_stMDomainInfo.enumDisplayMode == _DISPLAY_MODE_1P)
    {
        ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _DCLK_SPREAD_RANGE);
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    // Measure Input Active Region after I-double buffer apply
    g_ulInputActiveRegionBackUp = ScalerMeasureGetInputRegionCountResult(_WAIT);

    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

#if(_OD_SUPPORT == _ON)
    ScalerODInitial(_PANEL_DH_WIDTH, _PANEL_DV_HEIGHT);
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    ScalerMemoryReset();
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif
    switch(GET_MDOMAIN_INPUT_DATA_PATH())
    {
        case _INPUT_PATH_M1_M2:
            // Clear Buffer Status
            ScalerSetByte(P40_02_M2_STATUS0, 0xFF);
            ScalerSetByte(P0_02_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(_INPUT_PATH_M1_M2, (bit)((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;

        case _INPUT_PATH_M1:
        default:
            ScalerSetByte(P0_02_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(GET_MDOMAIN_INPUT_DATA_PATH(), (bit)((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;

        case _INPUT_PATH_M2:
            // Clear Buffer Status
            ScalerSetByte(P40_02_M2_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(_INPUT_PATH_M2, (bit)((ScalerGetBit(P45_AC_DISP_M2_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;

        case _INPUT_PATH_S1_S2:
            // Clear Buffer Status
            ScalerSetByte(PC0_02_S2_STATUS0, 0xFF);
            ScalerSetByte(P80_02_S1_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(_INPUT_PATH_S1_S2, (bit)((ScalerGetBit(P85_AC_DISP_S1_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;

        case _INPUT_PATH_S1:
            ScalerSetByte(P80_02_S1_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(_INPUT_PATH_S1, (bit)((ScalerGetBit(P85_AC_DISP_S1_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;

        case _INPUT_PATH_S2:
            // Clear Buffer Status
            ScalerSetByte(PC0_02_S2_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(_INPUT_PATH_S2, (bit)((ScalerGetBit(PC5_AC_DISP_S2_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
            // Clear Buffer Status
            ScalerSetByte(P0_02_STATUS0, 0xFF);
            ScalerSetByte(P40_02_M2_STATUS0, 0xFF);
            ScalerSetByte(P80_02_S1_STATUS0, 0xFF);
            ScalerSetByte(PC0_02_S2_STATUS0, 0xFF);

#if(_FRC_SUPPORT == _ON)
            // Set Current FRC Style
            SET_MDOMAIN_FRC_STYLE(_INPUT_PATH_ALL, (bit)((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));
#endif
            break;
#endif
    }

    // Clear Display Vsync timeout flag
    ScalerSetBit(P0_0C_WATCH_DOG_CTRL0, ~_BIT0, _BIT0);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

    if((ScalerMDomainMemoryCheck(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) ||
       (ScalerMeasureInputActiveRegionChange() == _TRUE))
    {
        DebugMessageScaler("MemoryCheck Fail in Display Setting", GET_MEMORY_SELECT());

        return _FALSE;
    }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, _BIT0);
#endif

    // If M domain setup success, set I domain DB trigger event to IEN_STOP
    ScalerGlobalIDDomainDBSetTriggerEvent(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_TRIGGER_EVENT_IEN_STOP);

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    // Update FRC remaining bandwidth
    g_ulFRCMemoryRemainBW = ulFRCRemainBW;

    // Set using bandwidth
    SET_MEMORY_BW(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_BW());
#endif

    return _TRUE;
}

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON) || (_FREESYNC_SUPPORT == _ON))
#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DCLK & DVtotal margin when frame sync line buffer
// Input Value  : NA
// Output Value : Pass or fail
//--------------------------------------------------
bit ScalerMDomainFSLineBufferDclkDvtotalCheck(void)
{
    BYTE ucDpllSscgDiv = ScalerMDomainGetDpllSscgDivMode();

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _FALSE)
#endif
    {
        // Frame sync Dvtotal
        PDATA_WORD(0) = (DWORD)g_stMDomainInputData.usVTotal * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight;

        if((PDATA_WORD(0) > _PANEL_DV_TOTAL_MAX) || (PDATA_WORD(0) < _PANEL_DV_TOTAL_MIN))
        {
            return _FALSE;
        }
    }

    // Calculate DHF
    PDATA_DWORD(0) = (DWORD)g_stMDomainInputData.usHFreq * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight / 10;

    // Frame sync Dclk max
    PDATA_DWORD(1) = PDATA_DWORD(0) * _PANEL_DH_TOTAL_MAX;

    // Frame sync Dclk min
    PDATA_DWORD(2) = PDATA_DWORD(0) * _PANEL_DH_TOTAL_MIN;

    // Dclk_min > (Panel_max_clk - margin - SSCG/2)
    if(PDATA_DWORD(2) > (((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ - (DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ / 100) - ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ * _DCLK_SPREAD_RANGE * 5 / 2000 / ucDpllSscgDiv)))
    {
        return _FALSE;
    }

    // Dclk_max < (Panel_min_clk + margin + SSCG/2)
    if(PDATA_DWORD(1) < (((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ + (DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ / 100) + ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ * _DCLK_SPREAD_RANGE * 5 / 2000 / ucDpllSscgDiv)))
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif
#endif

//--------------------------------------------------
// Description  : Get D-Domain PLL SSCG Divider Mode
// Input Value  : None
// Output Value : DPLL SSCG DIV NUM
//--------------------------------------------------
BYTE ScalerMDomainGetDpllSscgDivMode(void)
{
#if(_PANEL_STYLE == _PANEL_VBO)
    return _DIV_8;
#else
    return _DIV_1;
#endif
}

//--------------------------------------------------
// Description  : Perform D-domain related display setting
// Input Value  : FIFO info
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetDDomain(const StructSDRAMDataInfo *pstFIFOScaling)
{
    switch(GET_MEMORY_SELECT())
    {
        case _FRAME_SYNC_LINE_BUFFER:

            // Scaling Up Setting
            ScalerScalingSetScalingUp(pstFIFOScaling);

            // Set FIFO Capture Window
            ScalerMemorySetFifoCapture(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOScaling->usOutputHWidth, pstFIFOScaling->usOutputVHeight);

            // Set Initial Dt Value
            ScalerMemoryFrameSyncSetDt();

            // Set display Format
            ScalerMDomainSetDisplayFormat(_FRAME_SYNC_LINE_BUFFER);

            break;

#if(_FRC_SUPPORT == _ON)
        case _FRAME_SYNC_MEMORY:
        case _FREE_RUN_MEMORY:
        case _MN_FRAME_SYNC_MEMORY:

#if((_PBP_TB_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))

            // Update D-domain setting in porch region to prevent garbage under TB/4P modes
            if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB) ||
               (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P))
            {
                // Wait for M2 D-DEN start when D-domain global DB is disabled
                if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
                {
                    // Clear M2 DEN start flag
                    ScalerSetByte(P40_03_M2_STATUS1, _BIT4);

                    // Polling M2 DEN start
                    ScalerTimerPollingFlagProc(((DWORD)10000 / _PANEL_MIN_FRAME_RATE + 3), P40_03_M2_STATUS1, _BIT4, _TRUE);
                }
            }

#endif // End of #if((_PBP_TB_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))

            ///////////////////////////////////////////////////////////////////////////
            // The following 3 functions should not be delayed or changed in order
            ///////////////////////////////////////////////////////////////////////////

            // Scaling Up Setting
            ScalerScalingSetScalingUp(pstFIFOScaling);

            // Set FIFO Capture Window
            ScalerMemorySetFifoCapture(GET_MDOMAIN_INPUT_DATA_PATH(), pstFIFOScaling->usOutputHWidth, pstFIFOScaling->usOutputVHeight);

            // Set display Format
            ScalerMDomainSetDisplayFormat(GET_MEMORY_SELECT());

            ///////////////////////////////////////////////////////////////////////////

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Display Format
// Input Value  : enumSelRegion
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainCheckDisplayFormat(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

    // Check display format resolution to be even
    SET_MDOMAIN_OUTPUT_VSTART((GET_MDOMAIN_OUTPUT_VSTART() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_VBSTART((GET_MDOMAIN_OUTPUT_VBSTART() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_VHEIGHT((GET_MDOMAIN_OUTPUT_VHEIGHT() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_VBHEIGHT((GET_MDOMAIN_OUTPUT_VBHEIGHT() + 1) & 0xFFFE);

#if(_PANEL_STYLE == _PANEL_LVDS)
    // Check display format resolution according to LVDS port count
    SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() - (GET_MDOMAIN_OUTPUT_HSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - (GET_MDOMAIN_OUTPUT_HWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HBSTART() - (GET_MDOMAIN_OUTPUT_HBSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HBWIDTH() - (GET_MDOMAIN_OUTPUT_HBWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
#else
    SET_MDOMAIN_OUTPUT_HSTART((GET_MDOMAIN_OUTPUT_HSTART() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_HBSTART((GET_MDOMAIN_OUTPUT_HBSTART() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_HWIDTH((GET_MDOMAIN_OUTPUT_HWIDTH() + 1) & 0xFFFE);
    SET_MDOMAIN_OUTPUT_HBWIDTH((GET_MDOMAIN_OUTPUT_HBWIDTH() + 1) & 0xFFFE);
#endif
}

//--------------------------------------------------
// Description  : Memory Config
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainMemoryConfig(void)
{
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF)
        SET_MEMORY_CONFIG(_MEMORY_WORK_MODE);
#else
        SET_MEMORY_CONFIG(_LINE_BUFFER_MODE);

#if(_FRC_SUPPORT == _ON)
        if(((g_stDVCustomizedFreq.usMaxFreq - g_stDVCustomizedFreq.usMinFreq) < (g_stDVCustomizedFreq.usTypFreq >> 4)) &&
           (abs(g_stMDomainInputData.usVFreq - g_stDVCustomizedFreq.usTypFreq) < (g_stDVCustomizedFreq.usTypFreq >> 4)))
        {
            g_stDVCustomizedFreq.usMaxFreq += _FRAME_SYNC_MARGIN;
            g_stDVCustomizedFreq.usMinFreq -= _FRAME_SYNC_MARGIN;
        }

        if((g_stMDomainInputData.usVFreq < (g_stDVCustomizedFreq.usMinFreq)) ||
           (g_stMDomainInputData.usVFreq > (g_stDVCustomizedFreq.usMaxFreq)) ||
           (g_stMDomainOutputData.usVBackHeight > g_stMDomainOutputData.usVHeight) ||
           (ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) ||
           (ScalerMDomainFSLineBufferDclkDvtotalCheck() == _FALSE))
        {
            SET_MEMORY_CONFIG(_MEMORY_WORK_MODE);
        }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(ScalerRotationCheckStatus() == _TRUE)
        {
            SET_MEMORY_CONFIG(_MEMORY_WORK_MODE);
        }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
        // if display latency != faster, then change to _MEMORY_WORK_MODE
        if((GET_DISP_LATENCY_RATIO() != 0x00) && (GET_MEMORY_CONFIG() == _LINE_BUFFER_MODE))
        {
            SET_MEMORY_CONFIG(_MEMORY_WORK_MODE);
        }
#endif // End if #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)
#endif // End of #if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF)
    }
    else
    {
        SET_MEMORY_CONFIG(_MEMORY_WORK_MODE);
    }
}

//--------------------------------------------------
// Description  : Special Double Buffer Apply Procedure for FS
// Input Value  : None
// Output Value : None
// Note : Only for Frame Sync case
//--------------------------------------------------
void ScalerMDomainFSVgipDoubleBufferApply(void)
{
    bit bFreeRunEn = _FALSE;

    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        // Avoid (Current_IVStart + IVHeight) > IVToal + New_IVSDelay in digital capture
        PDATA_WORD(0) = (GET_INPUT_TIMING_VSTART() + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
    }
    else
    {
        // Avoid (Current_IVSDelay + IVStart + IVHeight) > IVToal + New_IVSDelay in analog capture
        PDATA_WORD(0) = (ScalerVgipGetCaptureVDelay() + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
    }

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        bFreeRunEn = (PDATA_WORD(0) > ((DWORD)g_stMDomainInputData.usVHeight * 105 / 100)) ? (_TRUE) : (_FALSE);
    }
    else
#endif
    {
        bFreeRunEn = (PDATA_WORD(0) > g_stMDomainInputData.usVTotal) ? (_TRUE) : (_FALSE);
    }

    if(bFreeRunEn == _TRUE)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_OUTPUT_DATA_PATH());

        // Set Free run
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

        // Disable MN tracking
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, 0x00);
    }

    ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

    if(bFreeRunEn == _TRUE)
    {
#if(_FRC_SUPPORT == _ON)
        if(GET_MEMORY_DVF_SELECT() == _1_IVF)
#endif
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, GET_MDOMAIN_OUTPUT_DATA_PATH());

            // Set Frame sync
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
        }
#if(_FRC_SUPPORT == _ON)
        else if((GET_MEMORY_DVF_SELECT() == _2_IVF) || (GET_MEMORY_DVF_SELECT() == _3_IVF))
        {
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE, 1, &pData[15], _NON_AUTOINC);

            ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

            while(pData[15] > 0)
            {
                pData[15] --;
                ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_OUTPUT_DATA_PATH());
            }
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, GET_MDOMAIN_OUTPUT_DATA_PATH());

            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, _BIT7);
        }
        else if(GET_MEMORY_DVF_SELECT() == _2_5_IVF)
        {
            // Measure DVtotal in current mode
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, _BIT5);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

            // Get N frame
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE, 1, &pData[15], _NON_AUTOINC);

            // Get free run DVtotal
            GET_FREE_RUN_DVTOTAL(PDATA_WORD(6));

            ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

            GET_DVTOTAL_LASTLINE(PDATA_WORD(0));

            if(PDATA_WORD(0) < (PDATA_WORD(6) * 7 / 10))
            {
                while(pData[15] > 0)
                {
                    pData[15] --;
                    ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_OUTPUT_DATA_PATH());
                }
            }
            else
            {
                ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_OUTPUT_DATA_PATH());
            }

            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, GET_MDOMAIN_OUTPUT_DATA_PATH());

            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, _BIT7);
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        }
#endif // End of #if(_FRC_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Dtotal, Background and display mode
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenBackground(EnumDisplayMode enumDisplayMode)
{
    PDATA_WORD(0) = _PANEL_DH_TOTAL - (_PANEL_DH_TOTAL % _DHTOTAL_MULTIPLE);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Set DHtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(0) - 8) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(0) - 8));

    // Set Last line for free run
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(0) - 8) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(0) - 8));
#else
    // Set DHtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(0) - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(0) - 4));

    // Set Last line for free run
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(0) - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(0) - 4));
#endif

    // Set H sync width, must by 2x in even-odd-mode
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (_PANEL_DH_SYNC_WIDTH + _PANEL_DH_SYNC_WIDTH % 2));

    // Set V sync height
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_SYNC_HEIGHT));

    // Set Main H background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START));

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

    // Set Main V background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START));

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT));

    switch(enumDisplayMode)
    {
#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))
        case _DISPLAY_MODE_PIP:
        case _DISPLAY_MODE_PBP_LR:

            ScalerMDomainSetSubBackground();

            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            // Set Sub H background st/ ed (Panel size)
            ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_S);
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));

            ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_S);
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

            // Set Sub V background st/ ed (Panel size)
            ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S);
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START));

            ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_S);
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT));

            break;
#endif
        default:

            break;
    }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // P0_2E
    // [4]: Main source type: !4P
    // [3]: Dtime Main mode: select even/ odd
    // [2]: Dtime Sub mode: select disable
    // [1]: Main active num: one
    // [0]: Sub active num: one

    // P0_2F
    // [3]: 5K3K main and sub separate setting
    // [2]: 5K3K PBPLR num 0:2P 1:1P
    // [1]: 5K3K  1P or PBPLR
    // [0]: frontback enable
    ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, _BIT0);

    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:
            ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
            ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(0x0F), _BIT0);
            break;

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:
            ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
            ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(0x0F), (_BIT1 | _BIT0));
            break;
#endif

        default:
            break;
    }

#else

    // [4]: Main source type: !4P
    // [3]: Dtime Main mode: select even/ odd
    // [2]: Dtime Sub mode: select disable
    // [1]: Main active num: one
    // [0]: Sub active num: one
    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:
            ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3));
            break;

        case _DISPLAY_MODE_PIP:
        case _DISPLAY_MODE_PBP_LR:
            ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
            break;

        case _DISPLAY_MODE_PBP_TB:
            ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT1));
            break;

        case _DISPLAY_MODE_4P:
            ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            break;

        default:
            break;
    }

#endif // End of #if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
}

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetSubBackground(void)
{
    // Set Sub H background st/ ed (Panel size)
    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_S);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_HBSTART()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_HBSTART()));

    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_S);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()));

    // Set Sub V background st/ ed (Panel size)
    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_VBSTART()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_VBSTART()));

    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_S);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()));
}

//--------------------------------------------------
// Description  : Set sub background timing format
// Input Value  : stTimingInfo --> timing format index
// Output Value : None
//--------------------------------------------------
void ScalerMDomainGetSubBackground(StructTimingFormat *pstTimingFormat)
{
    BYTE pucBuffer[2];

    pucBuffer[0] = 0;
    pucBuffer[1] = 0;

    // Get H background start/end
    ScalerGetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_S, 2, pucBuffer, _AUTOINC);
    pstTimingFormat->usHStart = ((pucBuffer[0] << 8) | pucBuffer[1]);

    ScalerGetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_S, 2, pucBuffer, _AUTOINC);
    pstTimingFormat->usHWidth = ((pucBuffer[0] << 8) | pucBuffer[1]) - pstTimingFormat->usHStart;

    // Get V background start/end
    ScalerGetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S, 2, pucBuffer, _AUTOINC);
    pstTimingFormat->usVStart = ((pucBuffer[0] << 8) | pucBuffer[1]);

    ScalerGetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_S, 2, pucBuffer, _AUTOINC);
    pstTimingFormat->usVHeight = ((pucBuffer[0] << 8) | pucBuffer[1]) - pstTimingFormat->usVStart;
}
#endif // End of #if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set sub active region format
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetSubActiveRegion(void)
{
    // Set Sub1 H Active Start / End
    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_S1);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART()));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

    // Set Sub1 V Active Start / End
    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_S1);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART()));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()) & 0x1F));
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
}
#endif // End of #if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Select memory confirm
// Input Value  : NA
// Output Value : free run/ frame sync line buffer/ frame sync frame buffer / MN frame sync/ free run no input
//--------------------------------------------------
BYTE ScalerMDomainMemorySelectConfirm(void)
{
    switch(GET_MEMORY_CONFIG())
    {
        case _LINE_BUFFER_MODE:

            return _FRAME_SYNC_LINE_BUFFER;

#if(_FRC_SUPPORT == _ON)
        case _MEMORY_WORK_MODE:

            if(g_stMDomainInfo.enumDisplayMode == _DISPLAY_MODE_1P)
            {
                switch(GET_MEMORY_DVF_SELECT())
                {
                    case _1_IVF:

                        return _FRAME_SYNC_MEMORY;

                    case _3_IVF:
                    case _2_5_IVF:
                    case _2_IVF:

                        return _MN_FRAME_SYNC_MEMORY;

                    default:
                    case _PANEL_TYP_FRAME_RATE_FREE_RUN:

                        return _FREE_RUN_MEMORY;
                }
            }
            else
            {
                return _FREE_RUN_MEMORY;
            }

#endif

        default:

            return _FRAME_SYNC_LINE_BUFFER;
    }
}

//--------------------------------------------------
// Description  : Set Memory Data Bit
// Input Value  : ucColorDepth
// Output Value : None
//--------------------------------------------------
void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth)
{
    if((ucColorDepth * 3) >= _M_DOMAIN_DATA_BIT_MAX)
    {
        SET_MEMORY_DATA_BIT(_M_DOMAIN_DATA_BIT_MAX);
    }
    else
    {
        SET_MEMORY_DATA_BIT(_COLOR_DEPTH_8_BITS * 3);
    }
}

//--------------------------------------------------
// Description  : Calculate I/D domain V adjust limitation
// Input Value  : input source type
// Output Value : vertical adjust limit for IV delay
//--------------------------------------------------
WORD ScalerMDomainGetVerticalAdjustLimit(EnumSourceTypeDef enumSourceTypeDef)
{
    WORD usAdjustLimit = 0x0001;

    enumSourceTypeDef = enumSourceTypeDef;

    // Calculate I-domain limitation; Safe New V-Delay value must larger than DEN falling edge position plus 3 lines
#if(_VGA_SUPPORT == _ON)
    if(enumSourceTypeDef == _SOURCE_VGA)
    {
        if(GET_INPUT_TIMING_VTOTAL() > (GET_INPUT_TIMING_VHEIGHT() + ScalerVgaTopGetCaptureVStartPosition() + 3))
        {
            usAdjustLimit = GET_INPUT_TIMING_VTOTAL() - (GET_INPUT_TIMING_VHEIGHT() + ScalerVgaTopGetCaptureVStartPosition() + 3);
        }
    }
    else
#endif
    {
        if(GET_INPUT_TIMING_VTOTAL() > (GET_INPUT_TIMING_VHEIGHT() + ScalerVgipGetCaptureVStartPosition() + 3))
        {
            usAdjustLimit = GET_INPUT_TIMING_VTOTAL() - (GET_INPUT_TIMING_VHEIGHT() + ScalerVgipGetCaptureVStartPosition() + 3);
        }
    }

    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
#if((_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_VBO))

        // Check D-domain limitation only for 1P mode and non-free-run case
        if(GET_MEMORY_SELECT() != _FREE_RUN_MEMORY)
        {
            // Calculate D-domain limitation
            WORD usDdomainLimit = (WORD)((DWORD)(GET_MDOMAIN_OUTPUT_VTOTAL() - GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_MDOMAIN_OUTPUT_VSTART()) * GET_MDOMAIN_INPUT_VTOTAL() / GET_MDOMAIN_OUTPUT_VTOTAL() - 1);

            if(usDdomainLimit < usAdjustLimit)
            {
                usAdjustLimit = usDdomainLimit;
            }

#if(_FRC_SUPPORT == _ON)
            // Update adjust limit for MN tracking
            if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
            {
                switch(GET_MEMORY_DVF_SELECT())
                {
                    case _3_IVF:
                        usAdjustLimit /= 3;
                        break;

                    case _2_5_IVF:
                        usAdjustLimit = (usAdjustLimit * 2 / 5);

                        // For 2 successive IVS
                        usAdjustLimit /= 2;
                        break;

                    case _2_IVF:
                        usAdjustLimit /= 2;
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_FRC_SUPPORT == _ON)

            // Keep at least one line for adjusting V-Position; otherwise take 2 lines as margin
            if(usAdjustLimit < 0x0003)
            {
                usAdjustLimit = 0x0001;
            }
            else
            {
                usAdjustLimit -= 0x0002;
            }
        }
#endif

        // Avoid Lost Frame-Sync DVS
        if(GET_MEMORY_DVF_SELECT() == _1_IVF)
        {
            WORD usIvs2dvsDelay = ((((WORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) & 0x01F) << 8) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L));
            WORD usIvs2dvsDelayLimit = 0;
            WORD usIvDelay = 0;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                usIvs2dvsDelay = usIvs2dvsDelay << 1;
            }
#endif

#if(_VGA_SUPPORT == _ON)
            if(enumSourceTypeDef == _SOURCE_VGA)
            {
                usIvDelay = ScalerVgaTopGetCaptureVDelay();
            }
            else
#endif
            {
                usIvDelay = ScalerVgipGetCaptureVDelay();
            }

            // Check IVS_Delay change from larger to smaller
            if((GET_INPUT_TIMING_VTOTAL() - usIvDelay) < (usIvs2dvsDelay + 4)) // 4 line margin
            {
                usIvs2dvsDelayLimit = ((usIvs2dvsDelay + 4) - (GET_INPUT_TIMING_VTOTAL() - usIvDelay));

                if(usIvDelay > usIvs2dvsDelayLimit)
                {
                    usIvs2dvsDelayLimit = usIvDelay - usIvs2dvsDelayLimit;

                    if(usIvs2dvsDelayLimit < usAdjustLimit)
                    {
                        usAdjustLimit = usIvs2dvsDelayLimit;
                    }
                }
            }
        }
    }

    DebugMessageScaler("V adj. limit", usAdjustLimit);

    return usAdjustLimit;
}

//--------------------------------------------------
// Description  : Measure Display Active Region in Display Setting
// Input Value  : void
// Output Value : Display Avtive Region
//--------------------------------------------------
DWORD ScalerMDomainGetDisplayActiveRegion(void)
{
    bit bChangeDVStartStatus = _FALSE;
    WORD usIvs2dvsDelay = 0;
    WORD usDVTotal = 0;
    DWORD ulDisplayActiveRegion = 0;

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _ENABLE)
    {
        bChangeDVStartStatus = _TRUE;
    }
    else
#endif
    {
        // Measure DVtotal in frame sync mode
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());

        // Get DVTotal Result
        GET_DVTOTAL_LASTLINE(usDVTotal);

        // Get Ivs2dvsdelay
        usIvs2dvsDelay = ScalerMemoryGetIVS2DVSDelayPixel() / GET_MDOMAIN_INPUT_HTOTAL() * GET_MDOMAIN_OUTPUT_VHEIGHT() / GET_MDOMAIN_INPUT_VHEIGHT();

        DebugMessageFS("usIvs2dvsDelay", usIvs2dvsDelay);
        DebugMessageFS("DVT", usDVTotal);
        DebugMessageFS("DVS", GET_MDOMAIN_OUTPUT_VSTART());

        // Check DVT < Ivs2dvsdelay + DVStart + DVHeigth
        bChangeDVStartStatus = ((usDVTotal < (usIvs2dvsDelay + GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT() + 2)) ? (_TRUE) : (_FALSE)); // 2 line margin
    }

    if(bChangeDVStartStatus == _TRUE)
    {
        // Set Main1 VHeight / 2
        SET_D_DOMAIN_V_ACT_END(GET_MDOMAIN_OUTPUT_DATA_PATH(), (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT() / 2));

        // Apply DB
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }

    // Set Measure Display Active Region
    ScalerMeasureSetDisplayRegionCount(GET_MDOMAIN_OUTPUT_DATA_PATH(), _ACTIVE_REGION_TYPE);

    // Read Active Region Result
    ulDisplayActiveRegion = ScalerMeasureGetDisplayRegionCountResult(_WAIT);

    if(bChangeDVStartStatus == _TRUE)
    {
        // Get H HBlanking
        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HTOTAL() - GET_MDOMAIN_OUTPUT_HWIDTH();

        // Calculate full-frame count = half-frame count * (Htotal * Vheight/2 - Hblanking) / (Htotal * Vheight - Hblanking)
        ulDisplayActiveRegion = GET_DWORD_MUL_DIV(ulDisplayActiveRegion, ((DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * GET_MDOMAIN_OUTPUT_HTOTAL() - PDATA_WORD(0)), ((DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() / 2 * GET_MDOMAIN_OUTPUT_HTOTAL() - PDATA_WORD(0)));

        // Set Main1 V Active st/ ed
        SET_D_DOMAIN_V_ACT_END(GET_MDOMAIN_OUTPUT_DATA_PATH(), (GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));

        // Apply DB
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }

    DebugMessageFS("bChangeDVStartStatus", bChangeDVStartStatus);

    return ulDisplayActiveRegion;
}

#if(_I_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : M domain use Color Depth
//--------------------------------------------------
BYTE ScalerMDomainGetColorDepth(void)
{
    return (GET_MEMORY_DATA_BIT() / 3);
}
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerMDomainAspectOriginMode(bit bOn)
{
    SET_ASPECT_ORIGIN_MODE(bOn);
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get maximum bandwidth for current path
// Input Value  : None
// Output Value : Maximum bandwidth
//--------------------------------------------------
DWORD ScalerMDomainGetCurBW(void)
{
    switch(GET_MDOMAIN_DISPLAY_MODE())
    {
        default: // 1P

            return _MEMORY_TOTAL_BW;

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:

            if(GET_MDOMAIN_OUTPUT_DATA_PATH() == _DISPLAY_PATH_S1)
            {
                return (_MEMORY_TOTAL_BW_PIP - _PIP_MAIN_BW);
            }
            else
            {
                return _PIP_MAIN_BW;
            }
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:

            return (_MEMORY_TOTAL_BW / 2);
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_TB:

            return (_MEMORY_TOTAL_BW / 2);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            return (_MEMORY_TOTAL_BW / 4);
#endif
    }
}
#endif

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : If memory is not enough for OD, disable OD
// Input Value  : Input timing for cal FRC memory size
// Output Value : Remaining bandwidth for FRC
//--------------------------------------------------
DWORD ScalerMDomainODConfig(void)
{
    DWORD ulRemainBW = 0;
    BYTE ucCurrODUseBit = GET_OD_USE_BIT();

#if(_FRC_SUPPORT == _ON)
    // Load FRC remaining bandwidth
    ulRemainBW = g_ulFRCMemoryRemainBW;
#endif

    SET_OD_USE_BIT(_OFF);

    switch(GET_MEMORY_CONFIG())
    {
        case _LINE_BUFFER_MODE:
            SET_OD_USE_BIT(ScalerODGetCompressionBitNum(_MEMORY_ROW, _MEMORY_TOTAL_BW));
            break;

#if(_FRC_SUPPORT == _ON)
        case _MEMORY_WORK_MODE:
            // Clear Mdomain Bandwidth
            CLR_MDOMAIN_BW();

            // Set using bandwidth
            SET_MDOMAIN_BW(ScalerMDomainGetFRCMemoryBW());

            // Get bandwith limit for current path
            PDATA_DWORD(0) = ScalerMDomainGetCurBW();

            // Check bandwidth limit for each path
            if(GET_MDOMAIN_BW() > PDATA_DWORD(0))
            {
                SET_MDOMAIN_BW(PDATA_DWORD(0));
            }

            // Compute ramaining bandwidth
            if(g_ulFRCMemoryRemainBW > GET_MDOMAIN_BW())
            {
                ulRemainBW = g_ulFRCMemoryRemainBW - GET_MDOMAIN_BW();
            }
            else
            {
                ulRemainBW = 0;
            }

            // Check available OD use bit
            SET_OD_USE_BIT(ScalerODGetCompressionBitNum(_MEMORY_ROW, ulRemainBW));

            DebugMessageFRC("4. FRC used BW", GET_MDOMAIN_BW());
            DebugMessageFRC("4. FRC remaining BW2", ulRemainBW);
            break;
#endif // End of #if(_FRC_SUPPORT == _ON)

        default:
            break;
    }

    DebugMessageFRC("4.(GET_OD_USE_BIT())", (GET_OD_USE_BIT()));

    if((GET_OD_USE_BIT() == _OFF) || (ucCurrODUseBit != GET_OD_USE_BIT()))
    {
        ScalerODEnable(_FUNCTION_OFF);

        // If OD config. need to be updated, wait 2 DVS to ensure that OD read operation is finished
        if(GET_OD_USE_BIT() != _OFF)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        }
    }

    return ulRemainBW;
}

//--------------------------------------------------
// Description  : OD use bit enable initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainODUseBitInitial(void)
{
    SET_OD_USE_BIT(_OFF);
}

//--------------------------------------------------
// Description  : Calculate memory use space
// Input Value  : OD use bit(10x) ucODbit = real ODbit x 10, 6.5bit OD --> ucODbit = 65
// Output Value : OD memory use space, unit:row
//--------------------------------------------------
WORD ScalerMDomainODCalculateMemoryUseSpace(BYTE ucODbit)
{
    //***************************************************//
    // Column = Column_per_bank * memory_bank
    // Row = Total memory unit / column
    //***************************************************//

    // OD memory size, unit:row
    return ((((DWORD)CEILING(_PANEL_DH_WIDTH, _OD_PIXEL_PER_COMP)) * _PANEL_DV_HEIGHT * ucODbit / _MEMORY_BIT_NUM) /
            (_MEMORY_COL_PER_BANK * _MEMORY_BANK) / 10 + 1);
}

//--------------------------------------------------
// Description  : Calculate memory use BW
// Input Value  : OD use bit(10x)
// Output Value : OD memory use BW, unit:100k
//--------------------------------------------------
WORD ScalerMDomainODCalculateMemoryUseBW(BYTE ucODbit)
{
    BYTE ucDpllSscgDiv = ScalerMDomainGetDpllSscgDivMode();

    PDATA_DWORD(0) = (((((DWORD)CEILING(_PANEL_DH_WIDTH, _OD_PIXEL_PER_COMP)) * g_stMDomainOutputData.usVTotal * ucODbit / _MEMORY_BUS_WIDTH / 10) * g_usDVFreq / 100) +
                      ((((DWORD)CEILING(_PANEL_DH_WIDTH, _OD_PIXEL_PER_COMP)) * g_stMDomainOutputData.usVTotal * ucODbit / _MEMORY_BUS_WIDTH / 100) * g_usDVFreq * ((_DCLK_SPREAD_RANGE / ucDpllSscgDiv) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100 / 10)) * 2;

    PDATA_DWORD(0) = (PDATA_DWORD(0) / 10000) + ((PDATA_DWORD(0) % 10000) ? 1 : 0); // unit:100k

    DebugMessageFRC("4.OD use BW", (PDATA_DWORD(0)));

    return (PDATA_DWORD(0) & 0xFFFF);
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset bandwidth
// Input Value  : EnumInputDataPath : Input path
// Output Value : void
//--------------------------------------------------
void ScalerMDomainReleaseFRCMemoryBW(EnumInputDataPath enumInputPath)
{
    DebugMessageFRC("4. FRC BW Reset path", enumInputPath);

    if(enumInputPath == _INPUT_PATH_ALL)
    {
        g_ulFRCMemoryRemainBW = _MEMORY_TOTAL_BW;  // unit:100k
        memset(g_pstFRCInfo, 0, sizeof(g_pstFRCInfo));
    }
    else
    {
        // Release FRC bandwidth
        g_ulFRCMemoryRemainBW += GET_MEMORY_BW(enumInputPath);
        CLR_MEMORY_BW(enumInputPath);

        // Check available OD use bit
        SET_OD_USE_BIT(ScalerODGetCompressionBitNum(_MEMORY_ROW, g_ulFRCMemoryRemainBW));

        DebugMessageFRC("4. FRC remaining BW1", g_ulFRCMemoryRemainBW);
        DebugMessageFRC("4. OD bit", GET_OD_USE_BIT());
    }
}

#endif // End of #if(_FRC_SUPPORT == _ON)
#endif // End of #if(_OD_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Display Background Vstart
// Input Value  : None
// Output Value : Display Background Vstart
//--------------------------------------------------
WORD ScalerMDomainGetDisplayBackgroundVstart(void)
{
    BYTE puctemp[2] = {0};

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &puctemp[0], _AUTOINC);
    return ((((WORD)puctemp[0] & 0x1F) << 8) | puctemp[1]);
}

//--------------------------------------------------
// Description  : Get Display Vheight
// Input Value  : None
// Output Value : Display Vheight
//--------------------------------------------------
WORD ScalerMDomainGetDisplayVheight(void)
{
    BYTE puctemp[4] = {0};

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H, 4, &puctemp[0], _AUTOINC);
    return (((((WORD)puctemp[2] & 0x1F) << 8) | puctemp[3]) - ((((WORD)puctemp[0] & 0x1F) << 8) | puctemp[1]));
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Dtotal, Background, Diaplay active region
// Input Value  : display data path
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGen(EnumDisplayDataPath enumDisplayDataPath)
{
    WORD usVBackStartOld = 0;
    WORD usVHeightOld = 0;
    WORD usHStartOld = 0;
    BYTE ucDdomainDBCtrl = 0;

    usVBackStartOld = ScalerMDomainGetDisplayBackgroundVstart();
    usVHeightOld = ScalerMDomainGetDisplayVheight();
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H, 2, pData, _AUTOINC);
    usHStartOld = ((pData[0] << 8) | pData[1]);

    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        // Set H sync width, must by 2x in even-odd-mode
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (_PANEL_DH_SYNC_WIDTH + _PANEL_DH_SYNC_WIDTH % 2));

        // Set V sync height
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);

#if(_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_DP_FREESYNC_DV_SYNC_HEIGHT));
        }
        else
#endif
        {
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_SYNC_HEIGHT));
        }

        // Set Main H background st/ ed (Panel size)
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HBSTART()) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HBSTART()));

        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HBSTART() + GET_MDOMAIN_OUTPUT_HBWIDTH()));

        // Set Main V background st/ ed (Panel size)
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_VBSTART()) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_VBSTART()));

        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()));
    }

    // Set Main V background st/ ed (Panel size)
    ScalerMDomainSetDisplayTimingGenActiveRegion(enumDisplayDataPath);

    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        // Adjust OSD Position, apply D before adjust OSD position
        // Frame sync line buffer need to fine tune Dclk according I-active-region & D-active-region
        if((usVBackStartOld != GET_MDOMAIN_OUTPUT_VBSTART()) ||
           (usHStartOld != GET_MDOMAIN_OUTPUT_HSTART()) ||
           ((usVHeightOld != GET_MDOMAIN_OUTPUT_VHEIGHT()) && (GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)))
        {
            ucDdomainDBCtrl = ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT5);
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

            ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

            // Adjust OSD Postion
            if(usVBackStartOld != GET_MDOMAIN_OUTPUT_VBSTART())
            {
#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
                ScalerOsdPositionOffsetCorrection();
#else
                ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(GET_OSD_POSITION_GOLOBAL_OFFSET_H()), Y_POS(GET_OSD_POSITION_GOLOBAL_OFFSET_V()));
#endif
            }

            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, (ucDdomainDBCtrl & _BIT5));
        }
    }
}


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
// ID Code      : UserCommonAuto.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_AUTO__

#include "UserCommonInclude.h"

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Active Region Percentage Threshold (%)
//--------------------------------------------------
#define _ACTIVE_REGION_PERCENTAGE_THD               ((100 - _AUTO_CLOCK_RANGE) / 2)

//--------------------------------------------------
// Auto config position over direction
//--------------------------------------------------
#define _AUTO_POSITION_OVER_NONE                    0x00
#define _AUTO_POSITION_OVER_LEFT                    _BIT0
#define _AUTO_POSITION_OVER_RIGHT                   _BIT1
#define _AUTO_POSITION_OVER_TOP                     _BIT2
#define _AUTO_POSITION_OVER_BOTTOM                  _BIT3

//--------------------------------------------------
// Definition of auto position before auto clock
//--------------------------------------------------
#define _AUTO_POSITION_FIRST_EN                     _ON
#define _AUTO_POSITION_FOR_IN_REGION_EN             _ON

//--------------------------------------------------
// Definition of results of checking active region
//--------------------------------------------------
#define _AUTO_ACTIVE_REGION_IN                      0xFE
#define _AUTO_ACTIVE_REGION_OUT                     0xFF

//--------------------------------------------------
// Definition of max auto faulure count
//--------------------------------------------------
#define _MAX_AUTO_FAIL_COUNT                        3

//--------------------------------------------------
// Definition of multi measure function tolerance
//--------------------------------------------------
#define _AUTO_MULTI_MEASURE_CHECK_TOL_H             4
#define _AUTO_MULTI_MEASURE_CHECK_TOL_V             1

//--------------------------------------------------
// Set IHS Capture Start (Minimum)
//--------------------------------------------------
#define _IHS_CAPTURE_START                          4

//--------------------------------------------------
// Set Center Position Non-adjusting Range (%) by IHWidth
//--------------------------------------------------
#define _AUTO_POSITION_CENTER_H_RANGE               85

//--------------------------------------------------
// Set Center Position Non-adjusting Range (%) by IVHeight
//--------------------------------------------------
#define _AUTO_POSITION_CENTER_V_RANGE               50

//--------------------------------------------------
// Definitions of Fine Tune Clock Range
//--------------------------------------------------
#define _FINE_TUNE_CLOCK_START                      1
#define _FINE_TUNE_CLOCK_NUMBER                     6
#define _FINE_TUNE_CLOCK_RANGE                      4

//--------------------------------------------------
// Definitions of Hardware Auto Phase Step
//--------------------------------------------------
#define _HWAUTO_STEP_1                              0x00
#define _HWAUTO_STEP_2                              0x01
#define _HWAUTO_STEP_4                              0x02
#define _HWAUTO_STEP_8                              0x03
#define _HWAUTO_STEP_16                             0x04

#define _HWAUTO_STEP                                _HWAUTO_STEP_8
#define _HWAUTO_START                               0
#define _HWAUTO_NUMBER                              8    // _HWAUTO_NUMBER <= (QPhase * VCO_divider - _HWAUTO_START)mod(_HWAUTO_STEP), QPhase = 32, VCO_divider = 2 or 4

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucAutoConfigStatus;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonAutoConfig(void);
bit UserCommonAutoClock(void);
bit UserCommonAutoHPosition(void);
bit UserCommonAutoVPosition(void);
bit UserCommonAutoPhase(void);
void UserCommonAutoUpdateUserdata(void);
bit UserCommonAutoMeasureMultiTimes(void);
bit UserCommonAutoClockRoughAdjust(WORD *pusCurrClock);
bit UserCommonAutoClockFineTuneAdjust(WORD *pusCurrClock);
bit UserCommonAutoClockCheckPictureRegion(void);
bit UserCommonAutoCheckClock(WORD usCurrClock);
//void UserCommonAutoPhaseTestFunction(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Picture position/clock/phase auto calibration.
// Input Value  : None
// Output Value : Return Error Status
//--------------------------------------------------
void UserCommonAutoConfig(void)
{
    g_ucAutoConfigStatus = 0;

    ScalerVgipSetInputRegion(SysVgaGetRegion());
    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    if(UserCommonAutoMeasureMultiTimes() == _FALSE)
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
    // For clamp-to-top case, do nothing.
    if(ScalerADCGetClampToTopStatus() == _TRUE)
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }
#endif

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_CHECK_MULTITIMES_FINISH);

    if(UserCommonAutoClock() == _FALSE)
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    SET_VGA_MODE_ADJUST_CLOCK(50);
#else
    SET_VGA_MODE_ADJUST_CLOCK(g_stVGAModeUserData.usCenterClock);
#endif

    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_FINISH);

    // UserCommonAutoPhaseTestFunction();

    if(UserCommonAutoPhase() == _FALSE)
    {
        SET_VGA_MODE_ADJUST_PHASE(UserCommonAdjustRealValueToPercent(g_stVGAModeUserData.ucCenterPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER));

        UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());

        g_ucAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_PHASE_FINISH);

    if(UserCommonAutoVPosition() == _FALSE)
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_V_POSITION_FINISH);

    if(UserCommonAutoHPosition() == _FALSE)
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_MEASURE_ERROR;

        return;
    }

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_H_POSITION_FINISH);

    SET_VGA_MODE_DO_FIRST_AUTO(_FALSE);

    UserCommonAutoUpdateUserdata();
}

//--------------------------------------------------
// Description  : Adjust clock.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoClock(void)
{
    WORD usClock = 0;

    // Check picture whether the rate of not full frame of picture is less than 95% of full frame
    if(UserCommonAutoClockCheckPictureRegion() == _FALSE)
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_CLOCK_ABORT;

        return _TRUE;
    }

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_CHECK_WIDTH_FINISH);

    // Find Rough Htotal(clock)
    if(UserCommonAutoClockRoughAdjust(&usClock) == _FALSE)
    {
        return _FALSE;
    }

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH);

    // Find Best Htotal(clock)
    if(UserCommonAutoClockFineTuneAdjust(&usClock) == _FALSE)
    {
        return _FALSE;
    }

    UserInterfaceGetAutoConfigPercentage(_AUTO_CONFIG_CLOCK_FINETUNE_FINISH);

    g_stVGAModeUserData.usCenterClock = usClock;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust H Position.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoHPosition(void)
{
    WORD usCurrClock = 0;

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usCurrClock = UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
#else
    usCurrClock = GET_VGA_MODE_ADJUST_CLOCK();
#endif

    if(UserInterfaceSkipAutoHpos() == _TRUE)
    {
        return _TRUE;
    }

#if(_OVERSCAN_SUPPORT == _TRUE)

    if(UserInterfaceGetOverScanStatus(SysVgaGetRegion()) == _TRUE)
    {
        if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, usCurrClock) == _FALSE)
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, usCurrClock) == _FALSE)
        {
            return _FALSE;
        }
    }

    if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
    {
        return _FALSE;
    }

    if(GET_ACTIVE_H_WIDTH() <= UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHWIDTH))
    {
        if(GET_ACTIVE_H_START() < (ScalerVgaTopGetCaptureHStartPosition() + ScalerVgaTopGetCaptureHDelay()))
        {
            g_stVGAModeUserData.usCenterHPosition = GET_ACTIVE_H_START();
        }
        else if(GET_ACTIVE_H_END() > (ScalerVgaTopGetCaptureHStartPosition() + ScalerVgaTopGetCaptureHDelay() + ScalerVgaTopGetCaptureHWidth() - 1))
        {
            g_stVGAModeUserData.usCenterHPosition = GET_ACTIVE_H_END() - (ScalerVgaTopGetCaptureHWidth()) + 1;
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        g_stVGAModeUserData.usCenterHPosition = GET_ACTIVE_H_START();
    }

    UserCommonAdjustHPosition(50, SysVgaGetRegion());

    SET_VGA_MODE_ADJUST_H_POSITION(50);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust V Position.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoVPosition(void)
{
    if(UserInterfaceSkipAutoVpos() == _TRUE)
    {
        return _TRUE;
    }

    DebugMessageAnalog("7. ModeTable VH", UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT));
    DebugMessageAnalog("7. Measure VH", GET_ACTIVE_V_HEIGHT());
    DebugMessageAnalog("7. Measeure V Start", GET_ACTIVE_V_START());
    DebugMessageAnalog("7. IVDelay", ScalerVgaTopGetCaptureVDelay());
    DebugMessageAnalog("7. IVCapture", ScalerVgaTopGetCaptureVStartPosition());
    DebugMessageAnalog("7. CenterVposition", g_stVGAModeUserData.usCenterVPosition);
    DebugMessageAnalog("7. Measure V End", GET_ACTIVE_V_END());

    if(GET_ACTIVE_V_HEIGHT() <= UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT))
    {
        DebugMessageAnalog("7. Picture under Size", 0);

        if(GET_ACTIVE_V_START() < (ScalerVgaTopGetCaptureVDelay() + ScalerVgaTopGetCaptureVStartPosition()))
        {
            DebugMessageAnalog("7. Top Over", 0);

            g_stVGAModeUserData.usCenterVPosition = GET_ACTIVE_V_START();
        }
        else if(GET_ACTIVE_V_END() > (ScalerVgaTopGetCaptureVDelay() + ScalerVgaTopGetCaptureVStartPosition() + (ScalerVgaTopGetCaptureVHeight()) - 1))
        {
            DebugMessageAnalog("7. Botten Over", 0);

            g_stVGAModeUserData.usCenterVPosition = GET_ACTIVE_V_END() - (ScalerVgaTopGetCaptureVHeight()) + 1;
        }
        else
        {
            DebugMessageAnalog("7. Do Nothing", 0);

            return _TRUE;
        }
    }
    else
    {
        DebugMessageAnalog("7. Picture over Size", 0);

        g_stVGAModeUserData.usCenterVPosition = GET_ACTIVE_V_START();
    }

    if((g_stVGAModeUserData.usCenterVPosition + UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT)) > GET_INPUT_TIMING_VTOTAL())
    {
        DebugMessageAnalog("7. Center V Position Error", g_stVGAModeUserData.usCenterVPosition);

        g_stVGAModeUserData.usCenterVPosition = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVSTART);
    }

    UserCommonAdjustVPosition(50, SysVgaGetRegion());

    SET_VGA_MODE_ADJUST_V_POSITION(50);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Adjust phase.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoPhase(void)
{
    BYTE ucBestPhase = 0;
    BYTE ucRoughPhase = 0;
    BYTE ucTargetPhase = 0;
    BYTE ucCounter = 0;
    DWORD ulSODTemp1 = 0;
    DWORD ulSODTemp2 = 0;
    DWORD ulSODLeft = 0;
    DWORD ulSODCenter = 0;
    DWORD ulSODRight = 0;

    if((GET_ACTIVE_H_WIDTH() > 4) && (GET_ACTIVE_V_HEIGHT() > 4))
    {
        ScalerVgaTopAutoFuncHBoundInitial((GET_ACTIVE_H_START() + 2), (GET_ACTIVE_H_END() - 2));
        ScalerVgaTopAutoFuncVBoundInitial((GET_ACTIVE_V_START() + 2), (GET_ACTIVE_V_END() - 2));
    }

    if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucRoughPhase, &ulSODTemp1, &ulSODTemp2, _PHASE_SEARCH_WSOD, 0x80) == _FALSE)
    {
        return _FALSE;
    }

    if((ulSODTemp1 / 0x80) < 100)
    {
        if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucRoughPhase, &ulSODTemp1, &ulSODTemp2, _PHASE_SEARCH_WSOD, 0x40) == _FALSE)
        {
            return _FALSE;
        }
    }

    ucTargetPhase = ((ucRoughPhase + 64 - 4) % 64);

    ulSODTemp1 = 0;
    ulSODTemp2 = 0;

    do
    {
        SysVgaWatchDog(_DISABLE);

        ScalerPLLSetPhase(ucTargetPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVFREQ));

        SysVgaWatchDog(_ENABLE);

        if(ScalerVgaTopAutoPhaseGetSOD(&ulSODTemp1) == _FALSE)
        {
            return _FALSE;
        }

        ulSODLeft = ulSODCenter;
        ulSODCenter = ulSODRight;
        ulSODRight = ulSODTemp1;

        if(ulSODCenter > (ABSDWORD(ulSODLeft, ulSODCenter) + ABSDWORD(ulSODRight, ulSODCenter)))
        {
            ulSODTemp1 = ulSODCenter - ((ABSDWORD(ulSODLeft, ulSODCenter) + ABSDWORD(ulSODRight, ulSODCenter)));
        }
        else
        {
            ulSODTemp1 = 0;
        }

        if(ulSODTemp1 > ulSODTemp2)
        {
            ulSODTemp2 = ulSODTemp1;
            ucBestPhase = ((ucTargetPhase + 64 - 2) % 64);
        }

        ucTargetPhase = ((ucTargetPhase + 2) % 64);

        ucCounter++;
    }
    while(ucCounter <= 4);

    if(ulSODTemp2 != 0x00)
    {
        g_stVGAModeUserData.ucCenterPhase = ucBestPhase;
    }
    else
    {
        g_ucAutoConfigStatus |= _AUTO_CONFIG_PHASE_ABORT;
    }

    SET_VGA_MODE_ADJUST_PHASE(UserCommonAdjustRealValueToPercent(g_stVGAModeUserData.ucCenterPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER));

    SysVgaWatchDog(_DISABLE);
    ScalerPLLSetPhase(g_stVGAModeUserData.ucCenterPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVFREQ));
    SysVgaWatchDog(_ENABLE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAutoUpdateUserdata(void)
{
    // Save user data to NVRam
    UserCommonNVRamSaveModeUserData();
}

//--------------------------------------------------
// Description  : Multi times measurement.
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoMeasureMultiTimes(void)
{
    BYTE ucCnt = 0;
    WORD usPreWidth = 0;
    WORD usPreHeight = 0;
    WORD usCurrClock = 0;

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usCurrClock = UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
#else
    usCurrClock = GET_VGA_MODE_ADJUST_CLOCK();
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
#if(_OVERSCAN_SUPPORT == _TRUE)
        if(UserInterfaceGetOverScanStatus(SysVgaGetRegion()) == _TRUE)
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, usCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, usCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }

        if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
        {
            return _FALSE;
        }

        if(ucCnt > 0)
        {
            if(!((abs((GET_ACTIVE_H_WIDTH()) - usPreWidth) <= _AUTO_MULTI_MEASURE_CHECK_TOL_H) && (abs((GET_ACTIVE_V_HEIGHT()) - usPreHeight) <= _AUTO_MULTI_MEASURE_CHECK_TOL_V)))
            {
                return _FALSE;
            }
        }

        usPreWidth = GET_ACTIVE_H_WIDTH();
        usPreHeight = GET_ACTIVE_V_HEIGHT();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rough adjust clock
// Input Value  : IHTotal, Current Clock
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoClockRoughAdjust(WORD *pusCurrClock)
{
    BYTE ucCount = 10;
    WORD usPreHWidth = 0;
    bit bAdjustPhaseResult = 0;

    // Initial Htotal(clock)
    *pusCurrClock = ((GET_INPUT_TIMING_HTOTAL()) >= g_stVGAModeUserData.usCenterClock) ? (GET_INPUT_TIMING_HTOTAL()) : g_stVGAModeUserData.usCenterClock;

    do
    {
        if(UserCommonAutoCheckClock(*pusCurrClock) == _FALSE)
        {
            return _FALSE;
        }

        SysVgaWatchDog(_DISABLE);

        bAdjustPhaseResult = ScalerAPLLFastLockAdjust(*pusCurrClock);

        SysVgaWatchDog(_ENABLE);

        if(bAdjustPhaseResult == _FALSE)
        {
            return _FALSE;
        }

#if(_OVERSCAN_SUPPORT == _TRUE)
        if(UserInterfaceGetOverScanStatus(SysVgaGetRegion()) == _TRUE)
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }

        if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
        {
            return _FALSE;
        }

        // exactly same --> return TRUE
        if(GET_ACTIVE_H_WIDTH() == GET_INPUT_TIMING_HWIDTH())
        {
            return _TRUE;
        }

        // Return Back Case
        if((GET_ACTIVE_H_WIDTH() + usPreHWidth) == (GET_INPUT_TIMING_HWIDTH() * 2))
        {
            return _TRUE;
        }

        usPreHWidth = GET_ACTIVE_H_WIDTH();

        ///////////////////////////////////////////////////////
        //  Measured_Width     ModeTable_Width               //
        // ---------------- = -----------------              //
        //  Current_Clock       Target_Clock                 //
        //                                                   //
        //                 ModeTable_Width * Current_Clock   //
        // Target_Clock = ---------------------------------  //
        //                         Measured_Width            //
        ///////////////////////////////////////////////////////

        PDATA_WORD(0) = ((DWORD)GET_INPUT_TIMING_HWIDTH() * (*pusCurrClock) + GET_ACTIVE_H_WIDTH() / 2) / GET_ACTIVE_H_WIDTH();

        if(PDATA_WORD(0) == *pusCurrClock)
        {
            return _TRUE;
        }
        else
        {
            *pusCurrClock = PDATA_WORD(0);
        }
    }
    while(--ucCount);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Fine tune clock
// Input Value  : IHTotal, Current Clock
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoClockFineTuneAdjust(WORD *pusCurrClock)
{
    WORD usRoughClock = 0;
    WORD usTargetClock = 0;
    WORD usBoundClock = 0;
    DWORD ulSODMax = 0;
    DWORD ulSODMin = 0;
    DWORD ulSODMaxValue = 0;
    DWORD ulSODMaxMinRatio = 0;
    BYTE ucTempPhase = 0;
    bit bAdjustPhaseResult = 0;
    BYTE ucPercentageStep = 0;
    BYTE ucCounter = 0;

    ScalerVgaTopAutoFuncHBoundInitial(GET_ACTIVE_H_START(), GET_ACTIVE_H_END());

    ScalerVgaTopAutoFuncVBoundInitial(GET_ACTIVE_V_START(), GET_ACTIVE_V_END());

    usRoughClock = *pusCurrClock;

    usTargetClock = (*pusCurrClock - ((_AUTO_TOLERANCE_PIXEL * GET_INPUT_TIMING_HTOTAL() / GET_INPUT_TIMING_HWIDTH()) + 1));

    usTargetClock = usTargetClock - ((usTargetClock % _AUTO_CLOCK_STEP));

    usBoundClock = (*pusCurrClock + ((GET_INPUT_TIMING_HTOTAL() / GET_INPUT_TIMING_HWIDTH()) + 2));

    usBoundClock = usBoundClock + ((usBoundClock % _AUTO_CLOCK_STEP));

    ucPercentageStep = ((_AUTO_CONFIG_CLOCK_FINETUNE_FINISH - _AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH) / (((usBoundClock - usTargetClock) / _AUTO_CLOCK_STEP) + 2));

    do
    {
        SysVgaWatchDog(_DISABLE);

        bAdjustPhaseResult = ScalerAPLLFastLockAdjust(usTargetClock);

        SysVgaWatchDog(_ENABLE);

        if(bAdjustPhaseResult == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucTempPhase, &ulSODMax, &ulSODMin, _PHASE_SEARCH_SOD, 0x40) == _FALSE)
        {
            return _FALSE;
        }

        DebugMessageAnalog("7. ====== Target Clock ======", usTargetClock);
        DebugMessageAnalog("7. SOG MAX", ulSODMax);
        DebugMessageAnalog("7. SOG MIN", ulSODMin);
        DebugMessageAnalog("7. SOG Ratio", (ulSODMax / ulSODMin));
        DebugMessageAnalog("7. Valid SOD Threshold", (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0x40) >> 7));

        if((ulSODMax - ulSODMin) > ulSODMaxValue)
        {
            *pusCurrClock = usTargetClock;
            ulSODMaxValue = ulSODMax - ulSODMin;

            if(ulSODMin == 0x00)
            {
                if(ulSODMax > (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0x40) >> 7))
                {
                    ulSODMaxMinRatio = 0xFFFFFFFF;
                }
                else
                {
                    ulSODMaxMinRatio = 0;
                }
            }
            else
            {
                ulSODMaxMinRatio = ulSODMax / ulSODMin;
            }
        }

        usTargetClock = usTargetClock + _AUTO_CLOCK_STEP;

        ucCounter++;

        UserInterfaceGetAutoConfigPercentage((_AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH + (ucPercentageStep * ucCounter)));
    }
    while(usTargetClock <= usBoundClock);

    if(ulSODMaxValue <= (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0x40) >> 8))
    {
        if(usRoughClock == (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)))
        {
            *pusCurrClock = usRoughClock;
        }
        else
        {
            if(((usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)) % 4) == 0x00)
            {
                *pusCurrClock = (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP));
            }
            else
            {
                *pusCurrClock = (usRoughClock - (usRoughClock % _AUTO_CLOCK_STEP));
            }
        }
    }
    else if(ulSODMaxMinRatio < 5)
    {
        SysVgaWatchDog(_DISABLE);

        bAdjustPhaseResult = ScalerAPLLFastLockAdjust(*pusCurrClock);

        SysVgaWatchDog(_ENABLE);

        if(bAdjustPhaseResult == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerVgaTopHWAutoPhaseSearch(_PHASE_SEARCH_STEP_4, &ucTempPhase, &ulSODMax, &ulSODMin, _PHASE_SEARCH_SOD, 0xA0) == _FALSE)
        {
            return _FALSE;
        }

        SysVgaWatchDog(_DISABLE);
        ScalerPLLSetPhase(ucTempPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVFREQ));
        SysVgaWatchDog(_ENABLE);

#if(_OVERSCAN_SUPPORT == _TRUE)
        if(UserInterfaceGetOverScanStatus(SysVgaGetRegion()) == _TRUE)
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _OVERSCAN_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            if(ScalerVgaTopMeasureActiveRegion(_NORMAL_MEASURE, _FULL_BOUNDARY, *pusCurrClock) == _FALSE)
            {
                return _FALSE;
            }
        }

        if((GET_ACTIVE_H_START() == 0x00) && (GET_ACTIVE_H_END() == 0x00) && (GET_ACTIVE_V_START() == 0x00) && (GET_ACTIVE_V_END() == 0x00))
        {
            return _FALSE;
        }

        if(ulSODMax == 0x00)
        {
            if(GET_ACTIVE_H_WIDTH() != GET_INPUT_TIMING_HWIDTH())
            {
                if(usRoughClock == (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)))
                {
                    *pusCurrClock = usRoughClock;
                }
                else
                {
                    if(((usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)) % 4) == 0x00)
                    {
                        *pusCurrClock = (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                    else
                    {
                        *pusCurrClock = (usRoughClock - (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                }
            }
        }
        else
        {
            if(ulSODMin == 0x00)
            {
                if(ulSODMax > (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0xA0) >> 9))
                {
                    ulSODMaxMinRatio = 0xFFFFFFFF;
                }
                else
                {
                    ulSODMaxMinRatio = 0;
                }
            }
            else
            {
                ulSODMaxMinRatio = (ulSODMax / ulSODMin);
            }

            DebugMessageAnalog("7. Double Check : Clock", *pusCurrClock);
            DebugMessageAnalog("7. Double Check SODMax", ulSODMax);
            DebugMessageAnalog("7. Double Check SODMin", ulSODMin);
            DebugMessageAnalog("7. Double Check : ulSODMaxMinRatio", ulSODMaxMinRatio);
            DebugMessageAnalog("7. Double Check Threshold", (((DWORD)GET_INPUT_TIMING_HWIDTH() * (DWORD)GET_INPUT_TIMING_VHEIGHT() * (DWORD)0xA0) >> 9));

            if((ulSODMaxMinRatio < 5) && ((GET_ACTIVE_H_WIDTH() != GET_INPUT_TIMING_HWIDTH())))
            {
                if(usRoughClock == (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)))
                {
                    *pusCurrClock = usRoughClock;
                }
                else
                {
                    if(((usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP)) % 4) == 0x00)
                    {
                        *pusCurrClock = (usRoughClock + (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                    else
                    {
                        *pusCurrClock = (usRoughClock - (usRoughClock % _AUTO_CLOCK_STEP));
                    }
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check picture region
// Input Value  : None
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoClockCheckPictureRegion(void)
{
    WORD usModeTableHWidth = 0;
    WORD usModeTableHTotal = 0;
    WORD usCurrClock = 0;

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usCurrClock = UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
#else
    usCurrClock = GET_VGA_MODE_ADJUST_CLOCK();
#endif

    usModeTableHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHWIDTH);
    usModeTableHTotal = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHTOTAL);

    /////////////////////////////////////////////////////
    //   Actvie HWidth        ModeTable_Width          //
    // (---------------) >= (----------------- x 95% ) //
    //   Current Clock        ModeTable_HTotal         //
    /////////////////////////////////////////////////////

    if(((DWORD) usModeTableHTotal * GET_ACTIVE_H_WIDTH()) >= (((DWORD)_AUTO_CLOCK_RANGE * usModeTableHWidth * usCurrClock) / 100))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check current Clock(IHTotal) region
// Input Value  : Current Clock (IHTotal)
// Output Value : Return _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonAutoCheckClock(WORD usCurrClock)
{
    WORD usCaptureHStart = 0;

    usCaptureHStart = ScalerVgipGetCaptureHStartPosition();

    if(((usCaptureHStart + GET_INPUT_TIMING_HWIDTH()) <= usCurrClock) && (usCurrClock <= GET_ADC_LIMIT_CLOCK()))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

/*
void UserCommonAutoPhaseTestFunction(void)
{
    BYTE ucCounter = 0;
    DWORD ulSODValue = 0;

    for(ucCounter=0; ucCounter < 64; ucCounter++)
    {
        ScalerGlobalWatchDog(_DISABLE);
        ScalerPLLSetPhase(ucCounter, UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVFREQ));
        ScalerGlobalWatchDog(_ENABLE);

        ScalerVgaTopAutoPhaseGetSOD(&ulSODValue);

        DebugMessageAnalog("7. SOD", ulSODValue);
    }
}
*/

#endif // End of #if(_VGA_SUPPORT == _ON)

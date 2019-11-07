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
// ID Code      : SysJudge.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_JUDGE__

#include "SysInclude.h"

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
#if((_DP_MST_SUPPORT == _ON) || (_HDCP_2_2_SUPPORT == _ON))
bit g_bEventEdgeFlg = 0;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysJudgeHandler(void);
void SysJudgeUpdateDisplayState(void);
void SysJudgeCheckAllPathStatus(void);
bit SysJudgeCheckStatus(BYTE ucRegionIndex);
bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState);
void SysJudgeModeResetProc(void);
WORD SysJudgeGetActiveWaitTime(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeHandler(void)
{
    CLR_MODE_STATE_CHANGE_OTHERS();

    switch(GET_POWER_STATUS())
    {
        case _POWER_STATUS_OFF:

            // Force mode state to power off
            if(GET_MODE_STATE() != _MODE_STATUS_POWER_OFF)
            {
                if(SysJudgeStateChangeEvent(_MODE_STATUS_POWER_OFF) == _FALSE)
                {
                    break;
                }
            }

            break;

        case _POWER_STATUS_SAVING:
        case _POWER_STATUS_NOSUPPORT_SAVING:
        case _POWER_STATUS_FAKE_SAVING:

            // Force mode state to power saving
            if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
            {
                if(SysJudgeStateChangeEvent(_MODE_STATUS_POWER_SAVING) == _FALSE)
                {
                    break;
                }
            }

            break;

        case _POWER_STATUS_NORMAL:

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerSyncGetUrgentEventFlg() == _TRUE)
            {
                ScalerSyncClrUrgentEventFlg();

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE) == _TRUE)
                {
                    ScalerTimerReactiveTimerEvent(SEC(1), _SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
                }

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE) == _TRUE)
                {
                    ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
                }

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE) == _TRUE)
                {
                    if((GET_MODE_STATE() == _MODE_STATUS_DISPLAY_SETTING) && (GET_MODE_DISPLAY_TARGET_STATE() == _DISPLAY_STATE_DISPLAY_READY))
                    {
                        ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                }
            }
#endif
            switch(GET_MODE_STATE())
            {
                case _MODE_STATUS_POWER_OFF:

                    if(SysJudgeStateChangeEvent(_MODE_STATUS_INITIAL) == _FALSE)
                    {
                        break;
                    }

                    break;

                case _MODE_STATUS_INITIAL:

                    // Change to display initial
                    if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_INITIAL) == _FALSE)
                    {
                        // Return here to skip path status check & display state reset
                        return;
                    }

                    // Return here to skip path status check & display state reset
                    return;

                case _MODE_STATUS_DISPLAY_INITIAL:

                    // Check logo status
                    if(UserInterfaceGetLogoStatus() == _TRUE)
                    {
                        // Skip path status check & display state reset when logo on
                        return;
                    }

                    // Change to display check
                    if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                    {
                        break;
                    }

                    break;

                case _MODE_STATUS_DISPLAY_SETTING:

                    // Check timing confirm status
                    if(GET_RGN_TIMING_CONFIRM(GET_MODE_DISPLAY_TARGET_INDEX()) == _FALSE)
                    {
                        // Cancel OOR & active timer events
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);

                        // Change to display check
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                        {
                            break;
                        }

                        break;
                    }

                    switch(GET_MODE_DISPLAY_TARGET_STATE())
                    {
                        default:

                            // 2 sec to display OOR state
                            ScalerTimerActiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

                            break;

                        case _DISPLAY_STATE_OOR:

                            // Cancel OOR timer event
                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

                            // Change to display check
                            if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                            {
                                break;
                            }

                            break;

                        case _DISPLAY_STATE_DISPLAY_READY:

                            // Check Dclk status in 1P mode
                            if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
                               (UserInterfaceGetDclkNoSupportStatus() == _TRUE))
                            {
                                DebugMessageSystem("DCLK OOR", GET_MODE_DISPLAY_TARGET_REGION());

                                // Dclk not supported; 0.5 sec to display OOR state
                                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            }
                            // Check system active ready status
                            else if(GET_MODE_ACTIVE_READY() == _FALSE)
                            {
                                // Wait for system active ready
                                ScalerTimerActiveTimerEvent(SysJudgeGetActiveWaitTime(), _SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);

                                // Cancel OOR timer event
                                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            }
                            // Check user active ready status
                            else if(UserCommonInterfaceReadyForActive(GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
                            {
                                // Change to display check
                                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                                {
                                    break;
                                }

                                // Display setting completed; Change display state to active
                                SET_RGN_DISPLAY_ACTION(GET_MODE_DISPLAY_TARGET_INDEX(), _DISPLAY_ACTION_ACTIVE);

                                // Clear active ready flag
                                CLR_MODE_ACTIVE_READY();
                            }

                            break;
                    }

                    break;

                case _MODE_STATUS_DISPLAY_CHECK:

                    // Search for display target
                    if(SysModeSearchDisplayTarget() == _TRUE)
                    {
                        // Change to display setting
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                        {
                            break;
                        }
                    }

                    break;

                case _MODE_STATUS_POWER_SAVING:

                    // Wake up when:
                    // 1. display state change
                    // 2. display target found
                    if((SysRegionCheckSystemDisplayStateChange() == _TRUE) ||
                       (SysModeSearchDisplayTarget() == _TRUE))
                    {
                        // Perform user reset
                        UserCommonInterfaceOsdResetProc();

                        // Change to display initial
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_INITIAL) == _FALSE)
                        {
                            break;
                        }
                    }

                    break;

                case _MODE_STATUS_FACTORY:

                    break;

                default:

                    break;
            }

            break;

        default:

            break;
    }

    // Update display state
    SysJudgeUpdateDisplayState();

    // Handle Status Check and Manual Reset Requests
    SysJudgeModeResetProc();

    // Check data path status
    SysJudgeCheckAllPathStatus();
}

//--------------------------------------------------
// Description  : Update display state
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeUpdateDisplayState(void)
{
    BYTE ucIndex = 0;

    // Update display state
    for(ucIndex = 0x00; ucIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucIndex)
    {
        switch(GET_RGN_DISPLAY_ACTION(ucIndex))
        {
            default:
            case _DISPLAY_ACTION_NO_ACTION:
                break;

            case _DISPLAY_ACTION_RESET_TO_NONE:
                DebugMessageSystem(">> NON", ucIndex);
                SET_RGN_DISPLAY_STATE(ucIndex, _DISPLAY_STATE_NONE);
                break;

            case _DISPLAY_ACTION_NO_SIGNAL:
                DebugMessageSystem(">> NSG", ucIndex);
                SET_RGN_DISPLAY_STATE(ucIndex, _DISPLAY_STATE_NO_SIGNAL);
                CLR_SOURCE_SWITCH_FINISH();
                break;

            case _DISPLAY_ACTION_OOR:
                DebugMessageSystem(">> OOR", ucIndex);
                SET_RGN_DISPLAY_STATE(ucIndex, _DISPLAY_STATE_OOR);
                break;

            case _DISPLAY_ACTION_DISPLAY_READY:
                DebugMessageSystem(">> DSP", ucIndex);
                SET_RGN_DISPLAY_STATE(ucIndex, _DISPLAY_STATE_DISPLAY_READY);
                break;

            case _DISPLAY_ACTION_ACTIVE:
                DebugMessageSystem(">> ACT", ucIndex);
                SET_RGN_DISPLAY_STATE(ucIndex, _DISPLAY_STATE_ACTIVE);
                break;
        }

        // Clear display target
        CLR_RGN_DISPLAY_ACTION(ucIndex);
    }
}

//--------------------------------------------------
// Description  : Check all data path status, including source stability, measure result, memory status, etc.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeCheckAllPathStatus(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucResetIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        if(SysJudgeCheckStatus(ucRegionIndex) == _FALSE)
        {
            // Clear source judge flag
            CLR_RGN_SOURCE_JUDGE(ucRegionIndex);

            // Reset all duplicated regions
            for(ucResetIndex = 0; ucResetIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucResetIndex)
            {
                if(GET_RGN_INPUT_PORT(ucResetIndex) == GET_RGN_INPUT_PORT(ucRegionIndex))
                {
                    SysModeResetDataPath(ucResetIndex);
                }
            }

            // Auto search Port has high priority
            if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT)
            {
                // Switch to reset port
                SysSourceSwitchRegionSearchPort(GET_RGN_INPUT_PORT(ucRegionIndex));
            }
            else if((GET_SOURCE_AUTO_TARGET() == ucRegionIndex) ||
                    (GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _TRUE) ||
                    (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
            {
                // Switch to reset port
                SysSourceSwitchRegionSearchPort(GET_RGN_INPUT_PORT(ucRegionIndex));
            }
        }
    }

    // Handle mode reset after check status failed
    SysJudgeModeResetProc();
}

//--------------------------------------------------
// Description  : Check Status
// Input Value  : Select Region Index
// Output Value : _FALSE => Status Changed
//--------------------------------------------------
bit SysJudgeCheckStatus(BYTE ucRegionIndex)
{
    if((GET_MODE_STATE() != _MODE_STATUS_FACTORY) && (GET_MODE_STATE() != _MODE_STATUS_POWER_OFF))
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE)
        {
            if(SysSourceStableCheck(ucRegionIndex) == _FALSE)
            {
                DebugMessageSystem("Source Unstable!!", ucRegionIndex);
                return _FALSE;
            }
        }
        else
        {
            if(GET_RGN_TIMING_CONFIRM(ucRegionIndex) == _TRUE)
            {
                DebugMessageSystem("Duplicated Source Unstable!!", ucRegionIndex);
                return _FALSE;
            }
        }

        if(GET_RGN_TIMING_CONFIRM(ucRegionIndex) == _TRUE)
        {
            if(ScalerMeasureTimingChange(GET_RGN_SOURCE_TYPE(ucRegionIndex), GET_RGN_INPUT_PORT(ucRegionIndex), ucRegionIndex) == _TRUE)
            {
                DebugMessageSystem("Measured Input HV Changed", ucRegionIndex);
                return _FALSE;
            }

            // double check input timing
            if((GET_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex) == _TRUE) &&
               ((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_DISPLAY_READY) ||
                (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE) ||
                (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_OOR)))
            {
                if(ScalerMeasureDoubleCheck(GET_RGN_SOURCE_TYPE(ucRegionIndex), GET_RGN_INPUT_PORT(ucRegionIndex), ucRegionIndex) == _FALSE)
                {
                    DebugMessageSystem("Input Timing Double Check Failed", ucRegionIndex);
                    return _FALSE;
                }

                CLR_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);
            }
        }

        if((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_DISPLAY_READY) ||
           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE))
        {
            if(ScalerMDomainMemoryCheck(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(ucRegionIndex))) == _FALSE)
            {
                DebugMessageSystem("Memory Check Failed", ucRegionIndex);
                return _FALSE;
            }

#if((_ULTRA_HDR_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
            ScalerMeasureSetIndex(ucRegionIndex);
            ScalerSyncDPHDRInfoFramePacketDetect(GET_RGN_INPUT_PORT(ucRegionIndex));
#endif
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Switch to Active State
// Input Value  : mode state
// Output Value : _TRUE => Successfully Changed
//--------------------------------------------------
bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState)
{
    // Check mode reset target
    if(GET_MODE_RESET_TARGET() != _MODE_ACTION_NO_RESET_MODE)
    {
        return _FALSE;
    }

    if((GET_MODE_STATE_CHANGE_SOURCE() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_MODE() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_MHL() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_OSD() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_OTHERS() == _FALSE))
    {
        SET_MODE_STATE(enumModeState);
        SET_MODE_STATE_CHANGE_SOURCE();
        SET_MODE_STATE_CHANGE_MODE();
        SET_MODE_STATE_CHANGE_MHL();
        SET_MODE_STATE_CHANGE_OSD();
        SET_MODE_STATE_CHANGE_OTHERS();

#if(_DEBUG_MESSAGE_SYSTEM == _ON)
        switch(enumModeState)
        {
            case _MODE_STATUS_INITIAL:
                DebugMessageSystem("--INI--", enumModeState);
                break;
            case _MODE_STATUS_DISPLAY_INITIAL:
                DebugMessageSystem("--DINI-", enumModeState);
                break;
            case _MODE_STATUS_DISPLAY_CHECK:
                DebugMessageSystem("--CHK--", enumModeState);
                break;
            case _MODE_STATUS_DISPLAY_SETTING:
                DebugMessageSystem("--DISP-", enumModeState);
                break;
            case _MODE_STATUS_POWER_SAVING:
                DebugMessageSystem("--PS---", enumModeState);
                break;
            case _MODE_STATUS_POWER_OFF:
                DebugMessageSystem("--OFF--", enumModeState);
                break;
            default:
                break;
        }
#endif

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Mode Reset Process according to reset target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeModeResetProc(void)
{
    BYTE ucModeResetTarget = GET_MODE_RESET_TARGET();

    // Clear reset target first
    SET_MODE_RESET_TARGET(_MODE_ACTION_NO_RESET_MODE);

    switch(ucModeResetTarget)
    {
        case _MODE_ACTION_RESET_TO_DISPLAY_INITIAL:

            if(GET_POWER_STATUS() != _POWER_STATUS_OFF)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_INITIAL) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_CHECK:

            if(GET_POWER_STATUS() != _POWER_STATUS_OFF)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_CHECK);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_CHECK);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:

            if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_FACTORY_MODE:

            if(SysJudgeStateChangeEvent(_MODE_STATUS_FACTORY) == _FALSE)
            {
                // Resume mode reset target
                SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_FACTORY_MODE);
                return;
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Required Wait Time before Active
// Input Value  : None
// Output Value : Required Wait Time
//--------------------------------------------------
WORD SysJudgeGetActiveWaitTime(void)
{
    if(GET_RGN_FIRST_ACTIVE(GET_MODE_DISPLAY_TARGET_INDEX()) == _FALSE)
    {
        switch(GET_RGN_SOURCE_TYPE(GET_MODE_DISPLAY_TARGET_INDEX()))
        {
#if(_VGA_SUPPORT == _ON)
            case _SOURCE_VGA:
                return _WAIT_TIME_TO_ACTIVE_VGA;
#endif

#if(_DVI_SUPPORT == _ON)
            case _SOURCE_DVI:
                return _WAIT_TIME_TO_ACTIVE_DVI;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _SOURCE_HDMI:
                return _WAIT_TIME_TO_ACTIVE_HDMI;
#endif

#if(_DP_SUPPORT == _ON)
            case _SOURCE_DP:
                return _WAIT_TIME_TO_ACTIVE_DP;
#endif

            default:
                break;
        }
    }

    return 0;
}

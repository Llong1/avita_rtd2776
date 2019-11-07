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
// ID Code      : SysMode.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_MODE__

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
StructModeInfoType g_stModeInfo;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysModeHandler(void);
BYTE SysModeGetModeState(void);
void SysModeClrModeStateChange(void);

void SysModeFirstDisplayCheckProc(void);
void SysModeDisplayStateProc(void);
void SysModeDisplayInitialSetting(void);

bit SysModeDisplaySetting(void);
void SysModeSetUpDisplayInitialization(void);
void SysModeSetUpInputCapture(void);
void SysModeSetUpDisplayCapture(void);
bit SysModeSetUpMDomain(void);

void SysModeResetState(BYTE ucResetTarget);
void SysModeResetDisplayState(EnumDisplayRegion enumDisplayRegion);
void SysModeResetDataPath(BYTE ucRegionIndex);

void SysModeSetFreeRun(void);
bit SysModeGetModeStateChange(void);
void SysModeSetResetTarget(EnumModeAction enumResetTarget);
void SysModeColorSpaceConvert(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorFormat, EnumDBApply enumDBApply);
void SysModeDisplayTimingInitial(EnumDisplayMode enumDisplayMode, EnumDisplayRegion enumDisplayRegion);

bit SysModeSearchDisplayTarget(void);
void SysModeSetDisplayTarget(EnumDisplayRegion enumDisplayRegion);
EnumDisplayRegion SysModeGetDisplayTarget(void);

EnumDisplayMode SysModeGetDisplayMode(void);
#if((_OGC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_OCC_SUPPORT == _ON))
EnumDisplayMode SysModeGetDisplayMode_EXINT1(void);
#endif
void SysModeSetDisplayMode(EnumDisplayMode enumDisplayMode);
bit SysModeCheckToDisableGlobalDoubleBuffer(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Mode related behavior
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeHandler(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return;
    }
#endif

    switch(GET_MODE_STATE())
    {
        case _MODE_STATUS_POWER_OFF:

            break;

        case _MODE_STATUS_INITIAL:

            break;

        case _MODE_STATUS_DISPLAY_INITIAL:

            if(UserInterfaceGetLogoStatus() == _TRUE)
            {
                // Skip clearing mode state change flag
                return;
            }

            // Perform display initial setting
            SysModeDisplayInitialSetting();

            break;

        case _MODE_STATUS_DISPLAY_SETTING:

            // Perform display setting only when all conditions met:
            // 1. timing confirmed
            // 2. display state != display ready or OOR
            if(GET_RGN_TIMING_CONFIRM(GET_MODE_DISPLAY_TARGET_INDEX()) == _TRUE)
            {
                if((GET_MODE_DISPLAY_TARGET_STATE() != _DISPLAY_STATE_DISPLAY_READY) &&
                   (GET_MODE_DISPLAY_TARGET_STATE() != _DISPLAY_STATE_OOR))
                {
#if(_PANEL_STYLE == _PANEL_VBO)
                    DWORD ulDclk = GET_D_CLK_FREQ();
#endif

                    if(SysModeDisplaySetting() == _TRUE)
                    {
#if(_PANEL_STYLE == _PANEL_VBO)
                        if((ulDclk != GET_D_CLK_FREQ()) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P))
                        {
                            // Turn off backlight to prevent garbage
                            UserCommonInterfacePanelPowerAction(_PANEL_OFF);
                        }
#endif

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
                        UserCommonInterfacePanelPowerAction(_PANEL_ON);
#endif
                        UserCommonInterfaceAdjustColorProc(GET_MODE_DISPLAY_TARGET_REGION());

                        SET_RGN_DISPLAY_ACTION(GET_MODE_DISPLAY_TARGET_INDEX(), _DISPLAY_ACTION_DISPLAY_READY);

                        SET_MODE_RESET_TARGET(_MODE_ACTION_NO_RESET_MODE);

                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                }
            }

            break;

        case _MODE_STATUS_DISPLAY_CHECK:

            if(GET_MODE_STATE_CHANGE_MODE() == _TRUE)
            {
                SysModeFirstDisplayCheckProc();
            }

            // Perform regular display state process
            SysModeDisplayStateProc();

            // Clear system display state change event
            SysRegionClearAllDisplayEvent(_DISPLAY_EVENT_STATE_CHANGE_SYS);

            break;

        case _MODE_STATUS_POWER_SAVING:

            // Go to power saving when source switch finish
            if((GET_SOURCE_SWITCH_FINISH() == _TRUE) &&
               (UserInterfaceGetIntoPSStatus() == _TRUE))
            {
                SET_TARGET_POWER_STATUS(_POWER_STATUS_SAVING);
                CLR_SOURCE_SWITCH_FINISH();
            }

            // Perform regular display state process
            SysModeDisplayStateProc();

            break;

        case _MODE_STATUS_FACTORY:

            break;

        default:

            break;
    }

    CLR_MODE_STATE_CHANGE_MODE();
}

//--------------------------------------------------
// Description  : Return Mode State for other Group
// Input Value  : None
// Output Value : Mode State
//--------------------------------------------------
BYTE SysModeGetModeState(void)
{
    return GET_MODE_STATE();
}

//--------------------------------------------------
// Description  : Clr Mode State Change Flag for OSD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeClrModeStateChange(void)
{
    CLR_MODE_STATE_CHANGE_OSD();
}

//--------------------------------------------------
// Description  : Regular first active process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeFirstDisplayCheckProc(void)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        if((GET_RGN_DISPLAY_STATE_CHANGE_SYS(ucRegionIndex) == _TRUE) &&
           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE))
        {
            // Set first active flag; Simplify later reset to display setting flow
            SET_RGN_FIRST_ACTIVE(ucRegionIndex);

            // Perform first active process
            ScalerGlobalFirstActiveProc(GET_RGN_SOURCE_TYPE(ucRegionIndex), GET_RGN_INPUT_PORT(ucRegionIndex));
            UserCommonInterfaceOsdActiveProc(GET_RGN_DISPLAY_REGION(ucRegionIndex));
        }
    }

    // Turn on back light when:
    // 1. under 2P/4P mode
    // 2. 1P mode in active state
    if((GET_MODE_DISPLAY_MODE() != _DISPLAY_MODE_1P) ||
       (GET_RGN_DISPLAY_STATE(0) == _DISPLAY_STATE_ACTIVE))
    {
        UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
    }

    SysSourceFirstActiveProc();
}

//--------------------------------------------------
// Description  : Regular display state process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDisplayStateProc(void)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        switch(GET_RGN_DISPLAY_STATE(ucRegionIndex))
        {
            case _DISPLAY_STATE_ACTIVE:

                // Perform active routine process
                ScalerSyncActiveProc(GET_RGN_SOURCE_TYPE(ucRegionIndex));

#if(((_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)) && (_DDR3_PHASE_CHECK == _OFF))
                // Perform DDR calibration in FRC mode
                if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
                {
                    ScalerDDR3PhaseCalibrationFRCMode();
                }
#endif
                break;

            case _DISPLAY_STATE_NO_SIGNAL:

                // Reset to display none state if cable status change
                if(UserInterfaceGetCableResetStatus(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _TRUE)
                {
                    switch(GET_MODE_STATE())
                    {
                        case _MODE_STATUS_DISPLAY_CHECK:

                            DebugMessageSystem("CHK: Cable reset", GET_RGN_DISPLAY_REGION(ucRegionIndex));

                            // Perform user resume process
                            UserCommonInterfaceResumeRegionProc(GET_RGN_DISPLAY_REGION(ucRegionIndex));

                            // Reset display state to _DISPLAY_STATE_NONE
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(ucRegionIndex), _DISPLAY_STATE_NONE);

                            // Reset source search times
                            if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) ||
                               (GET_SOURCE_AUTO_TARGET() == ucRegionIndex))
                            {
                                SysSourceSearchTimeReset();
                            }

                            break;


                        case _MODE_STATUS_POWER_SAVING:

                            DebugMessageSystem("PS: Cable reset", GET_RGN_DISPLAY_REGION(ucRegionIndex));

                            if(GET_POWER_STATUS() != _POWER_STATUS_NORMAL)
                            {
                                SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                            }

                            SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);

                            SysSourceCableResetProc();

                            break;

                        default:

                            break;
                    }
                }

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Include all required settings for Display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDisplayInitialSetting(void)
{
    BYTE ucRegionIndex = 0;

    // Initialize display format, active & background
    SET_MDOMAIN_DISPLAY_MODE(GET_MODE_DISPLAY_MODE());

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        SET_MODE_DISPLAY_TARGET_INDEX(ucRegionIndex);
        SysModeDisplayTimingInitial(GET_MODE_DISPLAY_MODE(), GET_MODE_DISPLAY_TARGET_REGION());
        ScalerMDomainSetDisplayTimingGenActiveRegion(ScalerRegionGetDisplayDataPath(GET_MODE_DISPLAY_TARGET_REGION()));

        // Set default FIFO Size
        ScalerMemorySetFifoCapture(ScalerRegionGetInputDataPath(GET_MODE_DISPLAY_TARGET_REGION()), GET_MDOMAIN_OUTPUT_HWIDTH(), GET_MDOMAIN_OUTPUT_VHEIGHT());
    }
    ScalerMDomainSetDisplayTimingGenBackground(GET_MODE_DISPLAY_MODE());

    // User Common Display Initial Color Proc
    UserCommonInterfaceInitialColorProc(GET_MODE_DISPLAY_MODE());

    // Global Display Initial Color Proc
    ScalerGlobalDisplayInitial(GET_MODE_DISPLAY_MODE());
}

//--------------------------------------------------
// Description  : Include all required settings for Display
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysModeDisplaySetting(void)
{
    // Set up variables for dispaly setting
    SysModeSetUpDisplayInitialization();

    // Set Up Input Timing to I Domain
    SysModeSetUpInputCapture();

    // Set D Domain Functions
    SysModeSetUpDisplayCapture();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _FALSE;
    }
#endif

    // Set M Domain Functions
    if(SysModeSetUpMDomain() == _FALSE)
    {
        DebugMessageSystem("Display Setting Fail", GET_MODE_DISPLAY_TARGET_INDEX());
        return _FALSE;
    }

    DebugMessageSystem("Display Setting Pass", GET_MODE_DISPLAY_TARGET_INDEX());
    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Up variables for display setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpDisplayInitialization(void)
{
    // Check Panel Backlight Action
    if(UserCommonInterfaceGetDisplaySettingBacklightAction() == _DISABLE)
    {
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
        // Turn off backlight to prevent garbage
        UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
#else
        // Turn off backlight to prevent garbage
        UserCommonInterfacePanelPowerAction(_PANEL_OFF);
#endif
    }

    // Set display mode
    SET_MDOMAIN_DISPLAY_MODE(GET_MODE_DISPLAY_MODE());

    // Set intput data
    ScalerMeasureSetIndex(GET_MODE_DISPLAY_TARGET_INDEX());
    SET_MDOMAIN_INPUT_STRUCTURE(g_pstRegionTimingInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stTimingInfo);

    // Set output data
    SET_MDOMAIN_OUTPUT_DATA_PATH(ScalerRegionGetDisplayDataPath(GET_MODE_DISPLAY_TARGET_REGION()));

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Set format conversion extension
    ScalerFmtCnvFBSetInitialExtension();
#endif

    // Set memory data bit
    ScalerMDomainSetMemoryDataBit(ScalerColorGetColorDepth(GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX())));

#if(_FRC_SUPPORT == _ON)
    // Set custom DVF freq.
    UserCommonInterfaceGetDVMaxMinFreq(&g_stDVCustomizedFreq);
#endif

    // Check Case to Disable Global Double Buffer
    if(SysModeCheckToDisableGlobalDoubleBuffer() == _TRUE)
    {
        ScalerGlobalDoubleBufferEnable(_DISABLE);
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Set rotation
    SET_ROT_TYPE(UserInterfaceGetRotationDegree());
    SET_ROT_DISP_SIZE(UserInterfaceGetRotationDisplayType());
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    // Set display latency ratio; 0 if rotation is enabled
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != _ROT_DISABLE)
    {
        SET_DISP_LATENCY_RATIO(0);
    }
    else
#endif
    {
        SET_DISP_LATENCY_RATIO(UserInterfaceGetDisplayLatencyRatio());
    }
#endif

#if(_FRC_SUPPORT == _ON)
    // Disable FRC in change timing / m-domain check fail
    if(ScalerGlobalGetDBStatus() == _FALSE)
    {
        EnumInputDataPath enumPath = (g_pstRegionTimingInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stTimingInfo.enumInputDataPath);

        // Disable FRC
        if(enumPath == _INPUT_PATH_M1)
        {
            // Set Pre-read
            ScalerFRCSetPreRead(enumPath, _PRE_READ_MEMORY - 1);

            ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_M1, _DISABLE);
        }
        else if(enumPath == _INPUT_PATH_S1)
        {
            // Set Pre-read
            ScalerFRCSetPreRead(enumPath, _PRE_READ_MEMORY - 1);

            ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_S1, _DISABLE);
        }
        else
        {
            ScalerFRCEn(_FRC_CAPTURE_ONOFF, enumPath, _DISABLE);

            if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)
            {
                if(enumPath == _INPUT_PATH_S1_S2)
                {
                    ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_S1_S2, _DISABLE);
                }
                else
                {
                    // Set Pre-read
                    ScalerFRCSetPreRead(enumPath, _PRE_READ_MEMORY - 1);
                }
            }
            else
            {
                ScalerFRCEn(_FRC_DISPLAY_ONOFF, enumPath, _DISABLE);
            }
        }

        // Use information from Frame-sync mode
        if(GET_MODE_DISPLAY_MODE() != _DISPLAY_MODE_PBP_TB)
        {
            if(((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_4P) && ((enumPath == _INPUT_PATH_M2) || (enumPath == _INPUT_PATH_S2))) ||
               (GET_MODE_DISPLAY_MODE() != _DISPLAY_MODE_4P))
            {
                ScalerFRCSetDDomainSourceSelect(enumPath, _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);
            }
        }
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        // Disable rotation
        ScalerRotationSetFRCEn(_FRC_ALL_ONOFF, _DISABLE);

        // Use information form Frame-Sync Mode
        ScalerRotationSetDDomainSourceSelect(_DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);
    }
#endif
#endif // End of #if(_FRC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set Up stuffs into I-Domain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpInputCapture(void)
{
#if(_4P_DISPLAY_SUPPORT == _ON)
    // Add Required Functions to Modify Input Timing
    if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_4P)
    {
        if(ScalerFmtCnvHalfSDGetStatus(g_pstRegionTimingInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stTimingInfo.enumInputDataPath) == _TRUE)
        {
            SET_MDOMAIN_INPUT_HSTART(GET_MDOMAIN_INPUT_HSTART() >> 1);
            SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() >> 1);
            SET_MDOMAIN_INPUT_HTOTAL(GET_MDOMAIN_INPUT_HTOTAL() >> 1);
        }
    }
#endif

    if(GET_MDOMAIN_INPUT_VSTART() > (GET_MDOMAIN_INPUT_VTOTAL() - GET_MDOMAIN_INPUT_VHEIGHT()))
    {
        SET_MDOMAIN_INPUT_VSTART((GET_MDOMAIN_INPUT_VTOTAL() - GET_MDOMAIN_INPUT_VHEIGHT()));
    }

    if((GET_MDOMAIN_INPUT_HWIDTH() % 2) != 0x00)
    {
        // We should let H-width is even integer in case of the width of memory FIFO read width must even integer.
        SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() + 1);
    }

    // Perform user adjust for I-domain
    UserCommonInterfaceAdjustInputTiming(GET_MODE_DISPLAY_TARGET_REGION());

    // Set I-domain capture
    ScalerIDomainVgipSetInputCapture();
}

//--------------------------------------------------
// Description  : Set Up I-Domain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpDisplayCapture(void)
{
    // System initialize default display timing
    SysModeDisplayTimingInitial(GET_MODE_DISPLAY_MODE(), GET_MODE_DISPLAY_TARGET_REGION());

    // User adjust display timing
    UserCommonInterfaceAdjustDisplayTiming(GET_MODE_DISPLAY_TARGET_REGION());

    // Check Display Timing
    ScalerMDomainCheckDisplayFormat(GET_MODE_DISPLAY_TARGET_REGION());
}

//--------------------------------------------------
// Description  : Set Up M-Domain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysModeSetUpMDomain(void)
{
    // Perform M-domain setting
    bit bMDomainSettingResult = ScalerMDomainControl();

    // Enable global DB
    ScalerGlobalDoubleBufferEnable(_ENABLE);

    return bMDomainSettingResult;
}

//--------------------------------------------------
// Description  : Mode Reset
// Input Value  : Reset Target
// Output Value : None
//--------------------------------------------------
void SysModeResetState(BYTE ucResetTarget)
{
    DebugMessageSystem("SysModeResetState!!", ucResetTarget);

    switch(ucResetTarget)
    {
        case _MODE_ACTION_RESET_TO_DISPLAY_INITIAL:

            // Reset global DB I domain trigger event
            ScalerGlobalIDDomainDBSetTriggerEvent(_INPUT_PATH_ALL, _DB_TRIGGER_EVENT_IVS);

            // User Reset Process
            UserCommonInterfaceOsdResetProc();

            // Reset source to display initial
            SysSourceInfoResetToDisplayInitial();

            // Clear all display info
            CLR_RGN_DISPLAY_INFO_ALL();

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            // Set M-domain display mode
            SET_MDOMAIN_DISPLAY_MODE(GET_MODE_DISPLAY_MODE());

            // Clear Measure Ready Flag
            SET_SOURCE_MEASURE_TARGET_INDEX(0);

            SysModeSetFreeRun();

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_CHECK:
            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:
        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            if(GET_MODE_DISPLAY_TARGET_STATE() != _DISPLAY_STATE_ACTIVE)
            {
                // User Reset Process
                UserCommonInterfaceOsdResetProc();
            }

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            // Initialize display setting variables
            CLR_RGN_DISPLAY_STATE(GET_MODE_DISPLAY_TARGET_INDEX());
            SET_MDOMAIN_INPUT_STRUCTURE(g_pstRegionTimingInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stTimingInfo);
            SET_MDOMAIN_DISPLAY_MODE(GET_MODE_DISPLAY_MODE());
            SET_MDOMAIN_OUTPUT_DATA_PATH(ScalerRegionGetDisplayDataPath(GET_MODE_DISPLAY_TARGET_REGION()));

#if(_PIP_BLENDING_SUPPORT == _ON)
            // Disable PIP blending when main reset
            if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_MAIN)
            {
                ScalerColorPIPBlendingLevelAdjust(0x00, _DB_APPLY_NO_POLLING);
            }
#endif

            break;

        case _MODE_ACTION_RESET_TO_POWER_SAVING:

            // User Reset Process
            UserCommonInterfaceOsdResetProc();

            // Clear Region Source Ready Flag
            CLR_RGN_SOURCE_TYPE_ALL();

            // Clear Region Source Judge
            CLR_RGN_SOURCE_JUDGE_ALL();

            if(UserInterfaceGetForcePSStatus() == _TRUE)
            {
                // Clear Region Display Info
                CLR_RGN_DISPLAY_INFO_ALL();
            }

            // Clear Source Switch Finish
            CLR_SOURCE_SWITCH_FINISH();

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

            break;

        case _MODE_ACTION_RESET_TO_POWER_OFF:

            // User Reset Process
            UserCommonInterfaceOsdResetProc();

            // Clear Source Ready Flag
            SysSourceInfoReset();

            // Clear Measure Ready Flag
            SysRegionClearAllDisplayEvent(_DISPLAY_EVENT_ALL);

            // Clear Measure Ready Flag
            CLR_RGN_DISPLAY_INFO_ALL();

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            // Judge Reset Process
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

            break;

        default:

            break;
    }

    ScalerGlobalResetProc(ucResetTarget);
}

//--------------------------------------------------
// Description  : Reset M/D domain process
// Input Value  : enumDisplayRegion --> display region
// Output Value : None
//--------------------------------------------------
void SysModeResetDisplayState(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);
    EnumDisplayDataPath enumDisplayDataPath = ScalerRegionGetDisplayDataPath(enumDisplayRegion);
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

    // Clear display state & event
    CLR_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);
    CLR_RGN_DISPLAY_STATE(ucRegionIndex);
    CLR_RGN_DISPLAY_ACTION(ucRegionIndex);

    //=========================================================================
    // Reset D-domain
    //=========================================================================
    // Enable force background
    ScalerDDomainBackgroundEnable(enumDisplayDataPath, _ENABLE);

    // Remove port mapping to display data path
    ScalerGlobalRemovePortMapping(GET_RGN_INPUT_PORT(ucRegionIndex), enumDisplayDataPath);

    // Disable WD
    ScalerGlobalWatchDog(enumDisplayRegion, _DISABLE);

    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
            SysModeSetFreeRun();
            break;

#if(_PIP_BLENDING_SUPPORT == _ON)
        case _DISPLAY_RGN_MAIN:
            // Disable PIP blending when main reset
            ScalerColorPIPBlendingLevelAdjust(0x00, _DB_APPLY_NO_POLLING);
            break;
#endif

        default:

            break;
    }

    //=========================================================================
    // Reset M-domain
    //=========================================================================

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    // Release FRC bandwidth
    ScalerMDomainReleaseFRCMemoryBW(enumInputDataPath);

    // Check for reactivating OD function
    if(UserInterfaceGetODEnableStatus() == _FUNCTION_ON)
    {
        if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0x00)
        {
            ScalerODInitial(_PANEL_DH_WIDTH, _PANEL_DV_HEIGHT);
            ScalerODEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerODEnable(_FUNCTION_OFF);
        }
    }
#endif

    // Disable FRC
    if(enumInputDataPath == _INPUT_PATH_M1)
    {
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_M1, _DISABLE);
    }
    else if(enumInputDataPath == _INPUT_PATH_S1)
    {
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_S1, _DISABLE);
    }
    else
    {
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, enumInputDataPath, _DISABLE);

        if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)
        {
            if(enumInputDataPath == _INPUT_PATH_S1_S2)
            {
                ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_S1_S2, _DISABLE);
            }
        }
        else
        {
            ScalerFRCEn(_FRC_DISPLAY_ONOFF, enumInputDataPath, _DISABLE);
        }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
            // Disable rotation
            ScalerRotationSetFRCEn(_FRC_ALL_ONOFF, _DISABLE);
        }
#endif
    }

    // Apply D-domain DB for FRC reset
    ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Data path reset process
// Input Value  : ucRegionIndex --> region index
// Output Value : None
//--------------------------------------------------
void SysModeResetDataPath(BYTE ucRegionIndex)
{
    EnumDisplayRegion enumDisplayRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

    DebugMessageSystem("Reset index", ucRegionIndex);
    DebugMessageSystem("Reset region", enumDisplayRegion);
    DebugMessageSystem("Reset port", GET_RGN_INPUT_PORT(ucRegionIndex));
    DebugMessageSystem("Reset port type", GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucRegionIndex)));

    //=========================================================================
    // Reset user/OSD functions
    //=========================================================================
    UserCommonInterfaceResetRegionProc(enumDisplayRegion);

    //=========================================================================
    // Reset D-domain & M-domain
    //=========================================================================
    SysModeResetDisplayState(enumDisplayRegion);

    //=========================================================================
    // Reset I-domain
    //=========================================================================

    // Clear I-domain events
    CLR_RGN_TIMING_CONFIRM(ucRegionIndex);
    CLR_RGN_MEASURE_CHECKING(ucRegionIndex);

    // Reset data path
    ScalerIDomainResetDataPath(enumInputDataPath);

    // Reset global DB I domain trigger event
    ScalerGlobalIDDomainDBSetTriggerEvent(enumInputDataPath, _DB_TRIGGER_EVENT_IVS);

    //=========================================================================
    // Reset Interface
    //=========================================================================
    SysSourceResetRegion(ucRegionIndex);

    // Clear No Wait For Active Flag
    CLR_RGN_FIRST_ACTIVE(ucRegionIndex);

    //=========================================================================
    // Reset System Flow
    //=========================================================================

    // Cancle display setting if currently performing
    if((GET_MODE_STATE() == _MODE_STATUS_DISPLAY_SETTING) &&
       (GET_MODE_DISPLAY_TARGET_INDEX() == ucRegionIndex))
    {
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

        // Clear Mode Active Ready Flag
        CLR_MODE_ACTIVE_READY();

        // Reset to display check
        SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_CHECK);
    }
}

//--------------------------------------------------
// Description  : Set Free Run Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetFreeRun(void)
{
#if(_PANEL_STYLE == _PANEL_VBO)
    DWORD ulDclk = GET_D_CLK_FREQ();
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Reset extension
    ScalerGlobalResetExtension();
#endif

    // Set D Domain Timing
    SysModeDisplayTimingInitial(_DISPLAY_MODE_1P, _DISPLAY_RGN_1P);

    SET_MDOMAIN_DISPLAY_MODE(_DISPLAY_MODE_1P);
    SET_MDOMAIN_OUTPUT_DATA_PATH(ScalerRegionGetDisplayDataPath(_DISPLAY_RGN_1P));
    ScalerMDomainSetDisplayFormat(_FREE_RUN_NO_INPUT);

    // Enable Spread Spectrum
    ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _DCLK_SPREAD_RANGE);

#if(_PANEL_STYLE == _PANEL_VBO)
    if(ulDclk != GET_D_CLK_FREQ())
    {
        // Turn off backlight to prevent garbage
        UserCommonInterfacePanelPowerAction(_PANEL_OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Mode State Change Flag for other layer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysModeGetModeStateChange(void)
{
    return GET_MODE_STATE_CHANGE_OSD();
}

//--------------------------------------------------
// Description  : Set Reset Status for User
// Input Value  : Target Reset State
// Output Value : None
//--------------------------------------------------
void SysModeSetResetTarget(EnumModeAction enumResetTarget)
{
    SET_MODE_RESET_TARGET(enumResetTarget);
}

//--------------------------------------------------
// Description  : Let User Specify Which Color Space is used
// Input Value  : Target Color Space, enumDBApply
// Output Value : None
//--------------------------------------------------
void SysModeColorSpaceConvert(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort, EnumColorSpace enumColorFormat, EnumDBApply enumDBApply)
{
    enumDBApply = enumDBApply;

    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

#if(_VGA_SUPPORT == _ON)
    if(enumSourceSearchPort == _A0_INPUT_PORT)
    {
        ScalerADCClampMode(enumColorFormat);

        // Download adc data from NVRam
        UserCommonNVRamLoadADCSetting(enumColorFormat);

        // Gain Offset Adjust.
        UserCommonInterfaceAdjustADCData();
    }
#endif

#if(_COLOR_FORMAT_CONVERT == _ON)
#if(_M_DOMAIN_FORCE_YUV_FORMAT == _ON)
    ScalerColorMdomainForceYUV((EnumSelRegion)enumDisplayRegion, enumSourceSearchPort, enumColorFormat, enumDBApply);
#elif(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorSpaceConvertUltraVividSupport((EnumSelRegion)enumDisplayRegion, enumSourceSearchPort, enumColorFormat, enumDBApply);
#else
    ScalerColorSpaceConvert((EnumSelRegion)enumDisplayRegion, enumSourceSearchPort, enumColorFormat, enumDBApply);
#endif
#endif // End of #if(_COLOR_FORMAT_CONVERT == _ON)
}

//--------------------------------------------------
// Description  : Give Display Timing Initial Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDisplayTimingInitial(EnumDisplayMode enumDisplayMode, EnumDisplayRegion enumDisplayRegion)
{
#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))
    StructTimingFormat stTimingFormat;
#endif
    WORD usDHtotal = _PANEL_DH_TOTAL - (_PANEL_DH_TOTAL % _DHTOTAL_MULTIPLE);

    enumDisplayRegion = enumDisplayRegion;

    // Set Up Display Timing According to display mode
    switch(enumDisplayMode)
    {
        default:
        case _DISPLAY_MODE_1P:
            SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
            SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
            SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);

            SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);
            SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
            SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
            SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
            break;

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            stTimingFormat.usVStart = _PANEL_DV_START;
            stTimingFormat.usVHeight = _PANEL_DV_HEIGHT;

            if(enumDisplayRegion == _DISPLAY_RGN_LEFT)
            {
                stTimingFormat.usHStart = _PANEL_DH_START;
                stTimingFormat.usHWidth = (_PANEL_DH_WIDTH / 2);
            }
            else
            {
                stTimingFormat.usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2);
                stTimingFormat.usHWidth = (_PANEL_DH_WIDTH / 2);
            }
#else
            stTimingFormat = UserInterfaceGetPbpTimingFormat(enumDisplayRegion);
#endif

            // L/R
            SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
            SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);

            SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);
            SET_MDOMAIN_OUTPUT_HBWIDTH(stTimingFormat.usHWidth);
            SET_MDOMAIN_OUTPUT_VBHEIGHT(stTimingFormat.usVHeight);

            SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
            SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
            SET_MDOMAIN_OUTPUT_HBSTART(stTimingFormat.usHStart);
            SET_MDOMAIN_OUTPUT_VBSTART(stTimingFormat.usVStart);

            ScalerMDomainCheckDisplayFormat(enumDisplayRegion);

            break;
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
            if(enumDisplayRegion == _DISPLAY_RGN_MAIN)
            {
                // MAIN
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);

                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);
                SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
                SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
            }
            else
            {
                // User adjust sub size
                stTimingFormat = UserInterfaceGetPipSubTimingFormat();

                // SUB
                SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);

                SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
                SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);
                SET_MDOMAIN_OUTPUT_HBWIDTH(stTimingFormat.usHWidth);
                SET_MDOMAIN_OUTPUT_VBHEIGHT(stTimingFormat.usVHeight);

                SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
                SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
                SET_MDOMAIN_OUTPUT_HBSTART(stTimingFormat.usHStart);
                SET_MDOMAIN_OUTPUT_VBSTART(stTimingFormat.usVStart);

                ScalerMDomainCheckDisplayFormat(enumDisplayRegion);
            }
            break;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_TB:
            if(enumDisplayRegion == _DISPLAY_RGN_TOP)
            {
                // T
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);

                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);
                SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
                SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
            }
            else
            {
                // B
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);

                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);
                SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT / 2);
                SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_LT:
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH);
                    SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);

                    SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
                    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
                    break;

                case _DISPLAY_RGN_LB:
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);

                    SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                    break;

                case _DISPLAY_RGN_RT:
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START + _PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START + _PANEL_DH_WIDTH / 2);

                    SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
                    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
                    break;

                case _DISPLAY_RGN_RB:
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HTOTAL(usDHtotal);
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START + _PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START + _PANEL_DH_WIDTH / 2);

                    SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
                    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                    SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                    break;

                default:

                    break;
            }
            break;
#endif
    }
}

//--------------------------------------------------
// Description  : Set display settting target
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysModeSearchDisplayTarget(void)
{
    BYTE ucDisplayIndex = 0;

    // Skip display target search when mode reset is going to happen
    if(GET_MODE_RESET_TARGET() != _MODE_ACTION_NO_RESET_MODE)
    {
        return _FALSE;
    }

    // Search display target
    for(ucDisplayIndex = 0; ucDisplayIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucDisplayIndex)
    {
        if((GET_RGN_TIMING_CONFIRM(ucDisplayIndex) == _TRUE) &&
           (GET_RGN_MEASURE_CHECKING(ucDisplayIndex) == _FALSE) &&
           (GET_RGN_DISPLAY_ACTION(ucDisplayIndex) == _DISPLAY_ACTION_NO_ACTION))
        {
            switch(GET_RGN_DISPLAY_STATE(ucDisplayIndex))
            {
                case _DISPLAY_STATE_NO_SIGNAL:

                    DebugMessageSystem("CHK: Display target reset", ucDisplayIndex);

                    // Perform user resume process
                    UserCommonInterfaceResumeRegionProc(GET_RGN_DISPLAY_REGION(ucDisplayIndex));

                    // Reset display state
                    SET_RGN_DISPLAY_ACTION(ucDisplayIndex, _DISPLAY_ACTION_RESET_TO_NONE);

                    // Disable global double buffer
                    ScalerGlobalDoubleBufferEnable(_DISABLE);

                    // Set new display target
                    SysModeSetDisplayTarget(GET_RGN_DISPLAY_REGION(ucDisplayIndex));

                    return _TRUE;

                case _DISPLAY_STATE_NONE:

                    // Disable global double buffer
                    ScalerGlobalDoubleBufferEnable(_DISABLE);

                    // Set new display target
                    SysModeSetDisplayTarget(GET_RGN_DISPLAY_REGION(ucDisplayIndex));

                    return _TRUE;

                default:

                    break;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set select region for display setting
// Input Value  : display region
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
void SysModeSetDisplayTarget(EnumDisplayRegion enumDisplayRegion)
{
    SET_MODE_DISPLAY_TARGET_INDEX(ScalerRegionGetIndex(enumDisplayRegion));

    DebugMessageSystem("New display target", ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get select region for display setting
// Input Value  : None
// Output Value : display region
//--------------------------------------------------
EnumDisplayRegion SysModeGetDisplayTarget(void)
{
    return GET_MODE_DISPLAY_TARGET_REGION();
}

//--------------------------------------------------
// Description  : Get system display mode
// Input Value  : None
// Output Value : display mode
//--------------------------------------------------
EnumDisplayMode SysModeGetDisplayMode(void)
{
    return GET_MODE_DISPLAY_MODE();
}

#if((_OGC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_OCC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get system display mode
// Input Value  : None
// Output Value : display mode
//--------------------------------------------------
EnumDisplayMode SysModeGetDisplayMode_EXINT1(void) using 2
{
    return GET_MODE_DISPLAY_MODE();
}
#endif

//--------------------------------------------------
// Description  : Set system display mode
// Input Value  : display mode
// Output Value : None
//--------------------------------------------------
void SysModeSetDisplayMode(EnumDisplayMode enumDisplayMode)
{
    // Update display mode
    SET_MODE_DISPLAY_MODE(enumDisplayMode);

    // Update region count
    UPD_RGN_MAX_DISPLAY_REGION();
}

//--------------------------------------------------
// Description  : Check To Disable Global Double Buffer
// Input Value  : None
// Output Value : _TRUE: Disale Global Global Double Buffer
//--------------------------------------------------
bit SysModeCheckToDisableGlobalDoubleBuffer(void)
{
    if(ScalerGlobalGetDBStatus() == _TRUE)
    {
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_ROT_TYPE() != UserInterfaceGetRotationDegree())
            {
                return _TRUE;
            }
#endif

#if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
            if(GET_MEMORY_DVF_SELECT() != ScalerDisplaySelectDVFMode())
            {
                return _TRUE;
            }
#endif
        }
    }
    return _FALSE;
}

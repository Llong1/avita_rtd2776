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
// ID Code      : SysPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_POWER__

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
StructPowerInfoType idata g_stPowerInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysPowerInitial(void);
void SysPowerHandler(void);
void SysPowerSwitch(EnumPowerAction enumSwitch);

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
void SysPowerIdleProc(void);
#endif

BYTE SysPowerGetPowerStatus(void);
void SysPowerSystemClockSelect(BYTE ucClockSel);
void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus);

#if(_DIGITAL_PORT_SUPPORT == _ON)
void SysPowerLoadHDCPKey(void);

#if(_DP_TX_SUPPORT == _ON)
void SysPowerLoadDPTxHDCPKey(void);
#endif
#endif

void SysPowerIsolation(EnumPowerAction enumSwitch);
void SysPowerRecoverIsolationAreaData(void);
bit SysPowerCheckFakeSaving(void);

#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
void SysPowerMHLPowerCutProc(void);
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Source Switch Flags
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerInitial(void)
{
    // Scaler whole chip reset
    ScalerGlobalWholeChipReset();

    // Internal oscillator trimming and on
    ScalerIOSCTrimming();


    ///////////////////
    // Load EDID     //
    ///////////////////

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
    UserCommonInterfaceNVRamRestoreEDID();
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    UserCommonInterfaceLoadEmbeddedEdidData();
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    // External Edid GPO Initial
    UserCommonInterfaceHDMIMultiEdidInitial();
#endif

    ///////////////////
    // Load HDCP Key //
    ///////////////////

    // HDCP Initial
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
    UserCommonInterfaceNVRamRestoreHDCP();
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)
    SysPowerLoadHDCPKey();
#endif


    /////////////////////////////////////
    // DP Aux and DPCD Initial Setting //
    /////////////////////////////////////

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
        ScalerDpRx6Initial(UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpLaneCount(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
        ScalerDpRx0Initial(UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
    }
    else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
    {
        ScalerDpRx0Initial(UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
        ScalerDpRx6Initial(UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpLaneCount(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
    }
#elif(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
    if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (SysSourceGetInputPort() == _D7_INPUT_PORT))
    {
        ScalerDpRx0Initial(UserInterfaceGetDPVersion(_D7_INPUT_PORT), UserInterfaceGetDpLaneCount(_D7_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
    }
    else
    {
        ScalerDpRx0Initial(UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
    }
#else
    ScalerDpRx0Initial(UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
#endif

#endif // Endi of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
    if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (SysSourceGetInputPort() == _D7_INPUT_PORT))
    {
        ScalerDpRx1Initial(UserInterfaceGetDPVersion(_D7_INPUT_PORT), UserInterfaceGetDpLaneCount(_D7_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
    }
    else
    {
        ScalerDpRx1Initial(UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpLaneCount(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
    }
#else
    ScalerDpRx1Initial(UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpLaneCount(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort(), GET_MODE_DISPLAY_MODE());
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)


    ////////////////////////////
    // DP MST Initial Setting //
    ////////////////////////////

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpRxMstInitial(UserInterfaceGetDpMSTCapablePort());
#endif


    ////////////////////////////
    // FREESYNC Initial Setting //
    ////////////////////////////

#if(_FREESYNC_SUPPORT == _ON)
    if(UserInterfaceGetFREESYNCEnable() == _TRUE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        ScalerSyncDpFREESYNCSupportSwitch(_DP_FREESYNC_CAPABILITY_INITIAL, _ON);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        ScalerTMDSFreesyncInitial(_ON);
#endif
    }
    else
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        ScalerSyncDpFREESYNCSupportSwitch(_DP_FREESYNC_CAPABILITY_INITIAL, _OFF);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        ScalerTMDSFreesyncInitial(_OFF);
#endif
    }
#endif


    //////////////////////////////
    // MHL CBus Initial Setting //
    //////////////////////////////

    ScalerPinshareCBUSPinInitialReset();

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    ScalerMHLRx0InitialSettings();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    ScalerMHLRx1InitialSettings();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    ScalerMHLRx2InitialSettings();
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    ScalerMHLRx3InitialSettings();
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    ScalerMHLRx4InitialSettings();
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    ScalerMHLRx5InitialSettings();
#endif

    //////////////////////
    // Memory Power Off //
    //////////////////////

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    ScalerMemoryPowerControl(_OFF);
#endif


    ///////////////////////////////////////
    // All Group Power Cut and Isolation //
    ///////////////////////////////////////

    SysPowerIsolation(_POWER_ACTION_AC_ON_INITIAL);
}

//--------------------------------------------------
// Description  : Power Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerHandler(void)
{
    // The process will deal with all kinds of power changing by power action flag.
    switch(GET_TARGET_POWER_STATUS())
    {
        case _POWER_STATUS_NORMAL:

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_OFF:
                    SysPowerSwitch(_POWER_ACTION_OFF_TO_NORMAL);
                    break;

                case _POWER_STATUS_SAVING:
                    SysPowerSwitch(_POWER_ACTION_PS_TO_NORMAL);
                    break;

                case _POWER_STATUS_AC_ON:
                    SysPowerSwitch(_POWER_ACTION_AC_ON_TO_NORMAL);
                    break;

                case _POWER_STATUS_NOSUPPORT_SAVING:
                    break;

                case _POWER_STATUS_FAKE_SAVING:
                    SysPowerSwitch(_POWER_ACTION_FAKE_PS_TO_NORMAL);
                    break;

                case _POWER_STATUS_NORMAL:
                    break;

                default:
                    break;
            }

            SET_POWER_STATUS(_POWER_STATUS_NORMAL);

            break;

        case _POWER_STATUS_OFF:

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_SAVING:
                    SysPowerSwitch(_POWER_ACTION_PS_TO_OFF);
                    break;

                case _POWER_STATUS_AC_ON:
                    SysPowerSwitch(_POWER_ACTION_AC_ON_TO_OFF);
                    break;

                case _POWER_STATUS_NOSUPPORT_SAVING:
                    SysPowerSwitch(_POWER_ACTION_NOSUPPORT_PS_TO_OFF);
                    break;

                case _POWER_STATUS_FAKE_SAVING:
                    SysPowerSwitch(_POWER_ACTION_FAKE_PS_TO_OFF);
                    break;

                case _POWER_STATUS_NORMAL:
                    SysPowerSwitch(_POWER_ACTION_NORMAL_TO_OFF);
                    break;

                default:
                    break;
            }

            SET_POWER_STATUS(_POWER_STATUS_OFF);

            break;

        case _POWER_STATUS_SAVING:

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_NORMAL:

                    if((SysPowerCheckFakeSaving() == _FALSE) || (UserInterfaceGetForcePSStatus() == _TRUE))
                    {
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_PS);

                        SET_POWER_STATUS(_POWER_STATUS_SAVING);
                    }
                    else
                    {
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_PS);

                        SET_POWER_STATUS(_POWER_STATUS_FAKE_SAVING);
                    }

                    break;

                case _POWER_STATUS_NOSUPPORT_SAVING:

                    if(SysPowerCheckFakeSaving() == _FALSE)
                    {
                        SysPowerSwitch(_POWER_ACTION_NOSUPPORT_PS_TO_PS);

                        SET_POWER_STATUS(_POWER_STATUS_SAVING);
                    }
                    else
                    {
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_PS);

                        SET_POWER_STATUS(_POWER_STATUS_FAKE_SAVING);
                    }

                    break;

                default:
                    break;
            }

            break;

        case _POWER_STATUS_NOSUPPORT_SAVING:

            if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                SysPowerSwitch(_POWER_ACTION_NORMAL_TO_NOSUPPORT_PS);
            }

            SET_POWER_STATUS(_POWER_STATUS_NOSUPPORT_SAVING);

            break;

        default:
            break;
    }

    // Clear power action to avoid repeat calls in next circle.
    SET_TARGET_POWER_STATUS(GET_POWER_STATUS());

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
    // Flash go into idle mode to reduce overall system power consumption under power saving and power off status.
    if(((GET_POWER_STATUS() == _POWER_STATUS_SAVING) || (GET_POWER_STATUS() == _POWER_STATUS_OFF)) && (UserCommonInterfaceGetRunDdcciCommand() == _FALSE))
    {
        // Call operation function to make Flash into idle mode.
        SysPowerIdleProc();
    }
#endif
}

//--------------------------------------------------
// Description  : Deal With Power Manage According To Input Pamater
// Input Value  : ucSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void SysPowerSwitch(EnumPowerAction enumSwitch)
{
#if((_MHL_SUPPORT == _ON) && (_MHL_3_0_SUPPORT == _ON))
    bit bFakePS = 0;
#endif

    switch(enumSwitch)
    {
        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            // Mode Power Saving Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_SAVING);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
            ScalerMemoryPowerControl(_OFF);
#endif
            // Interface Power Saving Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power saving state
            ScalerMcuPwmControl(_POWER_STATUS_SAVING);

            // Set Pin configure to power saving state
            ScalerPinshareConfig(_POWER_STATUS_SAVING);

            // Some Case Power Fake Saving Proc
#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
            SysPowerMHLPowerCutProc();
#endif

            // Enable all power cut area.
            SysPowerIsolation(enumSwitch);

            // Select internal oscillator as system clock.
            SysPowerSystemClockSelect(_IOSC_CLK);

            // LDO low power control.
            ScalerLDOPowerControl(_POWER_STATUS_SAVING);

            // Set SI's powerboard to low power
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_ON);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            SysSourcePowerOffProc();

            // Mode Power Off Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_OFF);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
            ScalerMemoryPowerControl(_OFF);
#endif
            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power off state
            ScalerMcuPwmControl(_POWER_STATUS_OFF);

            // Set mcu module to power off state
            ScalerPinshareConfig(_POWER_STATUS_OFF);

            // Enable all power cut area.
            SysPowerIsolation(enumSwitch);

            // Select internal oscillator as system clock.
            SysPowerSystemClockSelect(_IOSC_CLK);

            // LDO low power control.
            ScalerLDOPowerControl(_POWER_STATUS_OFF);

            // Set SI's powerboard to low power
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_ON);

            break;

        case _POWER_ACTION_PS_TO_OFF:

            // User Power process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            SysSourcePowerOffProc();

            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power off state
            ScalerMcuPwmControl(_POWER_STATUS_OFF);

            // Pin configure to power off state.
            ScalerPinshareConfig(_POWER_STATUS_OFF);

            // Enable all power cut area.
            SysPowerIsolation(enumSwitch);

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Wake up SI's powerboard
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_OFF);

            // LDO to normal setting.
            ScalerLDOPowerControl(_POWER_STATUS_NORMAL);

            // Disable all power cut area.
            SysPowerIsolation(enumSwitch);

            // Select M2PLL as system clock.
            SysPowerSystemClockSelect(_M2PLL_CLK);

#if(_AUDIO_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
            // Audio ADC initial
            ScalerAudioADCInitial();
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
            // Audio DAC initial, Initialize Audio DAC to Gain Depop Time
            ScalerAudioDACInitial();
#endif
#endif
            // Recovery data in all power cut area
            SysPowerRecoverIsolationAreaData();

            // Sync Power On Process
            ScalerSyncPowerProc(enumSwitch);

            // Pin configure to normal state.
            ScalerPinshareConfig(_POWER_STATUS_NORMAL);

            // Set mcu module to normal state
            ScalerMcuPwmControl(_POWER_STATUS_NORMAL);

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

            // User initial LUT/Latch/SRAM tabled ata
            UserCommonInterfaceOsdPowerOnInitial();

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
            ScalerMemoryPowerControl(_ON);
#endif
            // Clear Source Ready Flag
            SysSourceInfoReset();

            // Set Display to Free Run Mode
            SysModeSetFreeRun();

            // Initialize Osd Position
            ScalerGlobalOsdInitial();

#if(_VGA_SUPPORT == _ON)
            // Calibrate sync processor HS delay
            ScalerVgaTopModifyHsLatchEdgeDelay();
#endif

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerSyncJudgeHPDToggle(enumSwitch);
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_NOSUPPORT_PS:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

            break;

        case _POWER_ACTION_FAKE_PS_TO_NORMAL:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if((_MHL_SUPPORT == _ON) && (_MHL_3_0_SUPPORT == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) && (_D2_MHL_VERSION >= _MHL_VERSION_3_0))
            bFakePS |= ScalerMHL3Rx2FakePowerSavingCheck();
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) && (_D3_MHL_VERSION >= _MHL_VERSION_3_0))
            bFakePS |= ScalerMHL3Rx3FakePowerSavingCheck();
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) && (_D4_MHL_VERSION >= _MHL_VERSION_3_0))
            bFakePS |= ScalerMHL3Rx4FakePowerSavingCheck();
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))
            bFakePS |= ScalerMHL3Rx5FakePowerSavingCheck();
#endif
            if(!((GET_POWER_STATUS() == _POWER_STATUS_FAKE_SAVING) && (bFakePS == _TRUE)))
#endif
            {
                SysSourceInfoReset();
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

            // Mode Power Saving Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_SAVING);

            break;

        default:
            break;
    }
}

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MCU Work In Idle Mode In A Short Period Of Time.
// Input Value  : None.
// Output Value : None
//--------------------------------------------------
void SysPowerIdleProc(void)
{
    // Set Timer2 Count to 100ms but Reload value remains the same(1ms)
    ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_IDLE_MODE);

    // Enter Idle Mode
    ScalerMcuIntoIdle();

    // Add Timer Counter according to Timer2
    ScalerTimerAddTimerCounter();

    // Set Timer2 Count to 1ms
    ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_SAVING_MODE);
}
#endif // End of #if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Current System Power Status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE SysPowerGetPowerStatus(void)
{
    return GET_POWER_STATUS();
}

//--------------------------------------------------
// Description  : Clock Select For System.
// Input Value  : ucClockSel    --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void SysPowerSystemClockSelect(BYTE ucClockSel)
{
    BYTE ucGlobalIRQTemp = 0;

    if(ucClockSel == _M2PLL_CLK)
    {
        // Power on Xtal Clock.
        ScalerPowerXtalPower(_ON);

        // Power on M2PLL.
        ScalerPLLM2PLLPower(_ON);

        // Backup Global IRQ Control Status
        ucGlobalIRQTemp = ScalerGlobalGetIRQControl();

        ScalerGlobalIRQControl(_DISABLE);

        // Flash clock divider,target clock freq = 48M in normal mode.
        ScalerMcuFlashClockDiv(_FLASH_CLK_DIV);

        // Select CPU clock to M2PLL.
        ScalerMcuClockSel(_M2PLL_CLK);

        // Restore Global IRQ Control Status
        ScalerGlobalSetIRQControl(ucGlobalIRQTemp);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_NORMAL_MODE);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to M2PLL.
        ScalerMcuPwmClockSel(_M2PLL_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to external Xtal.
        ScalerMcuSarAdcClkSel(_EXT_XTAL_CLK);
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        // Switch D0 MHL System Clk to ISOC
        ScalerMHLRx0CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        // Switch D1 MHL System Clk to ISOC
        ScalerMHLRx1CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        // Switch D2 MHL System Clk to ISOC
        ScalerMHLRx2CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
        // Switch D3 MHL System Clk to ISOC
        ScalerMHLRx3CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        // Switch D4 MHL System Clk to ISOC
        ScalerMHLRx4CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        // Switch D5 MHL System Clk to ISOC
        ScalerMHLRx5CBUSSwitchClk(_IOSC_CLK);
#endif

        // Xtal CLK Select to external crystal clock.
        ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);

        // Modify debounce settings for Xtal clock.
        ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for Xtal clock.
        ScalerMcuHwIICSetFreqDiv(_EXT_XTAL_CLK);
#endif

        // Modify 5us delay for Flash CLK = 24.3M
        ScalerMcu5usDelayCalc(_M2PLL_CLK);

        // Internal CLK Select to M2PLL.
        ScalerGlobalSystemClkSel(_M2PLL_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select Xtal
        ScalerIRHWModeClockSel(_EXT_XTAL_CLK);
#endif
    }
    else
    {
        // Internal oscillator divider.
        ScalerIOSCClockDiv(_IOSC_DIV);

        // Xtal CLK Select to INOSC
        ScalerGlobalCrystalClkSel(_IOSC_CLK);

        // Modify debounce settings for INOSC clock.
        ScalerMcuDdcDebounceSel(_IOSC_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for IOSC clock.
        ScalerMcuHwIICSetFreqDiv(_IOSC_CLK);
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        // Switch D0 MHL System Clk to IOSC
        ScalerMHLRx0CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        // Switch D1 MHL System Clk to IOSC
        ScalerMHLRx1CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        // Switch D2 MHL System Clk to IOSC
        ScalerMHLRx2CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
        // Switch D3 MHL System Clk to IOSC
        ScalerMHLRx3CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        // Switch D4 MHL System Clk to IOSC
        ScalerMHLRx4CBUSSwitchClk(_IOSC_CLK);
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        // Switch D5 MHL System Clk to IOSC
        ScalerMHLRx5CBUSSwitchClk(_IOSC_CLK);
#endif

        // Internal CLK Select to Internal Crystal..
        ScalerGlobalSystemClkSel(_IOSC_CLK);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to Xtal.
        ScalerMcuPwmClockSel(_IOSC_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to Internal Crystal..
        ScalerMcuSarAdcClkSel(_IOSC_CLK);
#endif

        // Select CPU clock to Internal Crystal.
        ScalerMcuClockSel(_IOSC_CLK);

        // Flash clock divider,target clock freq = 7M in power saving mode.
        ScalerMcuFlashClockDiv(_FLASH_CLK_PS_DIV);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_SAVING_MODE);

        // Modify 5us delay for Flash CLK = 7M
        ScalerMcu5usDelayCalc(_IOSC_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select IOSC
        ScalerIRHWModeClockSel(_IOSC_CLK);
#endif

        // Power down M2PLL.
        ScalerPLLM2PLLPower(_OFF);

        // Power down Xtal.
        ScalerPowerXtalPower(_OFF);
    }
}
//--------------------------------------------------
// Description  : Set Power Action for other layer
// Input Value  : ucAction    --> Power Action
// Output Value : None
//--------------------------------------------------
void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus)
{
    SET_TARGET_POWER_STATUS(enumPorStatus);
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover The Data of HDCP In Gdi Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerLoadHDCPKey(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[16];

    // Enable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadKey(_ENABLE);

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonInterfaceGetHDCPKey((ucI * 16), 16, pucTemp);
        ScalerSyncHdcpDownLoadKey(16, pucTemp);
    }

    // Get Hdcp Key
    UserCommonInterfaceGetHDCPKeyBKsv(0, 5, pucTemp);

    // Write Hdcp Key To SDRAM
    ScalerSyncHdcpDownLoadBKsv(0, 5, pucTemp);

#if(_HDCP_2_2_SUPPORT == _ON)

    for(ucI = 0; ucI < 33; ucI++)
    {
        // Load HDCP 2.2 Key Certrx
        if(ucI < 32)
        {
            UserCommonInterfaceGetHdcp2Certrx((ucI * 16), 16, pucTemp);
            ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_CERT_RX);
        }
        else
        {
            UserCommonInterfaceGetHdcp2Certrx((ucI * 16), 10, pucTemp);
            ScalerHdcp2DownLoadCalculateKey((ucI * 16), 10, pucTemp, _HDCP_2_2_CERT_RX);
        }
    }

    for(ucI = 0; ucI < 8; ucI++)
    {
        // d key, Npinv, RRmodN, public key n
        UserCommonInterfaceGetHdcp2RSADkey((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_D_KEY);

        UserCommonInterfaceGetHdcp2RSARRModN((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_RRMODN_KEY);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        UserCommonInterfaceGetHdcp2KpubKm((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_KPUB_KM);
#endif
    }

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonInterfaceGetHdcp2RSAKPriv((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_KPRIV_KEY);
    }

    UserCommonInterfaceGetHdcp2RSANpinv(0, 4, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 4, pucTemp, _HDCP_2_2_RSA_N_PINV);

    UserCommonInterfaceGetHdcp2LCKey(0, 16, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 16, pucTemp, _HDCP_2_2_LC);

    ScalerHdcp2RxPairingCalculate();
#endif

    // Disable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadKey(_DISABLE);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover The Data of HDCP for DPTX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerLoadDPTxHDCPKey(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[16];

    // Enable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadDPTxKey(_ENABLE);

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonInterfaceGetTxHDCPKey((ucI * 16), 16, pucTemp);
        ScalerSyncHdcpDownLoadDPTxAKey(16, pucTemp);
    }

    // Get Hdcp Key
    UserCommonInterfaceGetTxHDCPKeyAKsv(0, 5, &pucTemp[5]);

    // Write Hdcp Key To SDRAM
    ScalerSyncHdcpDownLoadDPTxAKsv(0, 5, &pucTemp[5]);

    // Disable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadDPTxKey(_DISABLE);
}
#endif
#endif

//--------------------------------------------------
// Description  : Power Isolation Setting For all power isolation Module.
// Input Value  : enumSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void SysPowerIsolation(EnumPowerAction enumSwitch)
{
    BYTE ucIsolationAreaFlg = 0x00;

    // Power isolation control.
    ucIsolationAreaFlg = ScalerPowerIsolation(enumSwitch);

    if((ucIsolationAreaFlg & _BIT0) == _BIT0)
    {
        SET_POWER_ISO_A_FLG();
    }

    if((ucIsolationAreaFlg & _BIT1) == _BIT1)
    {
        SET_POWER_ISO_B_FLG();
    }

    if((ucIsolationAreaFlg & _BIT2) == _BIT2)
    {
        SET_POWER_ISO_C_FLG();
    }

    if((ucIsolationAreaFlg & _BIT3) == _BIT3)
    {
        SET_POWER_ISO_D_FLG();
    }

    if((ucIsolationAreaFlg & _BIT4) == _BIT4)
    {
        SET_POWER_ISO_E_FLG();
    }
}

//--------------------------------------------------
// Description  : Recover The Data of LUT/Latch/SRAM In Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerRecoverIsolationAreaData(void)
{
    if(GET_POWER_ISO_A_FLG() == _TRUE)
    {
        CLR_POWER_ISO_A_FLG();

        // Power A Group Data Recovery
        ScalerPowerRecoverAGroupIsolationData();
    }

    if(GET_POWER_ISO_B_FLG() == _TRUE)
    {
        CLR_POWER_ISO_B_FLG();

        // Power B Group Data Recovery
        ScalerPowerRecoverBGroupIsolationData();
    }

    if(GET_POWER_ISO_C_FLG() == _TRUE)
    {
        CLR_POWER_ISO_C_FLG();

#if((_DIGITAL_PORT_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
        SysPowerLoadDPTxHDCPKey();
#endif

        // Power C Group Data Recovery
        ScalerPowerRecoverCGroupIsolationData();
    }

    if(GET_POWER_ISO_D_FLG() == _TRUE)
    {
        CLR_POWER_ISO_D_FLG();

        // Power D Group Data Recovery
        ScalerPowerRecoverDGroupIsolationData();
    }

    if(GET_POWER_ISO_E_FLG() == _TRUE)
    {
        CLR_POWER_ISO_E_FLG();

        // Power E Group Data Recovery
        ScalerPowerRecoverEGroupIsolationData();
    }
}

//--------------------------------------------------
// Description  : Check Whther go to Fake Saving Mode
// Input Value  : None
// Output Value : _TRUE => Fake Saving
//--------------------------------------------------
bit SysPowerCheckFakeSaving(void)
{
    DebugMessageMst("SysPower Check Fake Saving", 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(ScalerSyncDpFakePowerSavingCheck() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(GET_AUDIO_PLAYING_ALONE() == _TRUE)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Fake Saving Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerMHLPowerCutProc(void)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

#if(_MHL_SUPPORT == _ON)
            if(((SysSourceGetInputPort() == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((SysSourceGetInputPort() == _D3_INPUT_PORT) && (GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((SysSourceGetInputPort() == _D4_INPUT_PORT) && (GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((SysSourceGetInputPort() == _D5_INPUT_PORT) && (GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)))
            {
                // Vcck 1.1v Power On, Group D Analog Isolation Off
                ScalerPowerSetMHLNoPowerCut();
            }
            else
            {
                ScalerPowerClrMHLNoPowerCut();
            }

#endif

            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:

#if(_MHL_SUPPORT == _ON)
            if((GET_D2_TMDS_MODE() == _TMDS_MHL_MODE) || (GET_D3_TMDS_MODE() == _TMDS_MHL_MODE) ||
               (GET_D4_TMDS_MODE() == _TMDS_MHL_MODE) || (GET_D5_TMDS_MODE() == _TMDS_MHL_MODE))
            {
                // Vcck 1.1v Power On, Group D Analog Isolation Off
                ScalerPowerSetMHLNoPowerCut();
            }
            else
            {
                ScalerPowerClrMHLNoPowerCut();
            }
#endif

            break;

        default:

            break;
    }
}
#endif


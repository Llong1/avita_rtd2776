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
// ID Code      : SysAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_AUDIO__

#include "SysInclude.h"

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
#define _DAC_VCM_INITIAL_TIME                       SEC(0.1)
#define _DAC_VCM_CHARGE_TIME                        SEC(0.5)
#define _DAC_DEPOP_TO_NORMAL_WAIT_TIME              SEC(0.1)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructAudioInfoType idata g_stAudioInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysAudioHandler(void);
EnumAudioState SysAudioGetAudioState(void);
void SysAudioPowerProc(EnumPowerAction enumSwitch);
void SysAudioMuteProc(bit bMute);
void SysAudioAnalogAudioHandler(void);
void SysAudioDigitalAudioHandler(void);
void SysAudioChangeAudioState(EnumAudioState enumAudioState);
void SysAudioInitial(void);

#if(_DP_SUPPORT == _ON)
void SysAudioDpAudioSecDataResetProc(BYTE ucInputPort);
#endif

#if(_LINE_IN_SUPPORT == _ON)
bit SysAudioCheckSourceJudge(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
void SysAudioSleepAudioHandler(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void SysAudioInternalGenTestProc(bit bOn);
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Audio handler. Main audio control flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioHandler(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
    {
        return;
    }
#endif

    SysAudioAnalogAudioHandler();

    SysAudioDigitalAudioHandler();

    switch(GET_AUDIO_STATE())
    {
        case _AUDIO_STATUS_PREPARING:

            if(GET_AUDIO_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_STATE_CHANGE();
                SET_AUDIO_PLAYBACK_SEARCH_INDEX(0x0F);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                ScalerAudioWatchDogProc(_ON, ScalerAudioGetDigitalAudioPortMapping());
                SysAudioMuteProc(_OFF);

                DebugMessageAudio("Switch to Audio Playback", 0x00);
                SysAudioChangeAudioState(_AUDIO_STATUS_PLAYBACK);
            }

            break;

        case _AUDIO_STATUS_PLAYBACK:

            if(GET_AUDIO_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_STATE_CHANGE();
                SET_AUDIO_PLAYBACK_SEARCH_INDEX(GET_RGN_SOURCE_INDEX(UserInterfaceGetAudioRegionIndex()));
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _FALSE)
            {
                SysAudioMuteProc(_ON);
                ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

                DebugMessageAudio("Switch to Audio Preparing", 0x00);
                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            }

            break;

        case _AUDIO_STATUS_POWER_OFF:
        default:
            break;
    }

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    SysAudioSleepAudioHandler();
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
EnumAudioState SysAudioGetAudioState(void)
{
    return GET_AUDIO_STATE();
}

//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
void SysAudioPowerProc(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            SysAudioInitial();

            // Add User interface function
            UserInterfaceAdjustAudioPowerProc(_POWER_STATUS_NORMAL);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
            UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(UserInterfaceGetAudioSource()));
#endif
            SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:

            // Mute Audio
            SysAudioMuteProc(_ON);

            // Add User interface function
            UserInterfaceAdjustAudioPowerProc(_POWER_STATUS_OFF);

            // Disable Audio
            ScalerAudioDisable();

            SysAudioChangeAudioState(_AUDIO_STATUS_POWER_OFF);
            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Mute Audio
            SysAudioMuteProc(_ON);

            // Add User interface function
            UserInterfaceAdjustAudioPowerProc(_POWER_STATUS_SAVING);

            // Disable Audio
            ScalerAudioDisable();

            SysAudioChangeAudioState(_AUDIO_STATUS_POWER_OFF);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioMuteProc(bit bMute)
{
    if(bMute == _ON)
    {
        UserInterfaceAdjustAudioAmpMuteProc(_ON);

        ScalerAudioMuteProc(_ON, UserInterfaceGetAudioVolume());
    }
    else
    {
        ScalerAudioMuteProc(_OFF, UserInterfaceGetAudioVolume());

        UserInterfaceAdjustAudioAmpMuteProc(_OFF);
    }
}

//--------------------------------------------------
// Description  : Audio Analog Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioAnalogAudioHandler(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)

    if((ScalerAudioDACGetState() != _AUDIO_DAC_OFF) && (ScalerAudioDACGetState() != _AUDIO_DAC_INITIAL) && (ScalerAudioDACGetState() != _AUDIO_DAC_CHARGE))
    {
        // User want to change DAC Input / Output
        if((ScalerAudioGetAudioInputPortChanged(UserInterfaceGetAudioSource(), SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion())) == _TRUE) ||
           (ScalerAudioDACGetOutput() != UserInterfaceGetAudioDACOutput()))
        {
            SysAudioMuteProc(_ON);
            ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

            if(ScalerAudioDACGetOutput() != UserInterfaceGetAudioDACOutput())
            {
                DebugMessageAudio("Audio Dac Switch Output", ScalerAudioDACGetOutput());

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                ScalerAudioDACNormalToDepop();

                ScalerAudioDACSetVcmReady(_OFF);
                ScalerAudioDACSetState(_AUDIO_DAC_CHARGE);
            }
            else
            {
                DebugMessageAudio("Audio Switch Input", ScalerAudioGetInputSource());

#if(_LINE_IN_SUPPORT == _ON)
                if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
                {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
                    if((SysAudioCheckSourceJudge() == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) ||
                       ((UserInterfaceGetAudioStandAloneStatus() == _TRUE) &&
                        (UserInterfaceGetAudioSource() == _LINE_IN_AUDIO) &&
                        (GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)))
#else
                    if(SysAudioCheckSourceJudge() == _TRUE)
#endif
                    {
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                        ScalerAudioDACNormalToDepop();

                        ScalerAudioSourceInputSwitch(_LINE_IN_AUDIO, SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion()));

#if(_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON)
                        UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(_LINE_IN_AUDIO));
#endif
                    }
                }
                else
#endif
                {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                    if((GET_RGN_SOURCE_JUDGE(UserInterfaceGetAudioRegionIndex()) == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) ||
                       ((UserInterfaceGetAudioStandAloneStatus() == _TRUE) &&
                        (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO) &&
                        (ScalerAudioGetDpStandaloneAudioStatus(SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion())) == _TRUE)))
#else
                    if((GET_RGN_SOURCE_JUDGE(UserInterfaceGetAudioRegionIndex()) == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT))
#endif
                    {
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                        ScalerAudioDACNormalToDepop();

                        ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion()));

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
                        UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(_DIGITAL_AUDIO));
#endif
                    }
                }
            }

            SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
        }
    }

    switch(ScalerAudioDACGetState())
    {
        case _AUDIO_DAC_OFF:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();
            }

            break;

        case _AUDIO_DAC_INITIAL:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("Audio Dac Initial", _AUDIO_DAC_INITIAL);

                ScalerTimerActiveTimerEvent(_DAC_VCM_INITIAL_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL);
            }

            break;

        case _AUDIO_DAC_CHARGE:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("Audio Dac Charge", _AUDIO_DAC_CHARGE);

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);

                ScalerAudioDACOutputSwitch(UserInterfaceGetAudioDACOutput());
                ScalerAudioDACSetVcmReady(_ON);

                ScalerTimerActiveTimerEvent(_DAC_VCM_CHARGE_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);
            }

            break;

        case _AUDIO_DAC_DEPOP:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                DebugMessageAudio("Audio Dac Depop", _AUDIO_DAC_DEPOP);

                if(UserInterfaceGetAudioDACKeepDepopState() == _FALSE)
                {
                    ScalerAudioDACClrStateChange();

                    ScalerAudioDACOutputEnable();

                    ScalerTimerActiveTimerEvent(_DAC_DEPOP_TO_NORMAL_WAIT_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                }
            }
            break;

        case _AUDIO_DAC_READY:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("Audio Dac Ready", _AUDIO_DAC_READY);
            }
            break;

        default:
            break;
    }

#else

    // change audio Input port
    if(ScalerAudioGetAudioInputPortChanged(UserInterfaceGetAudioSource(), SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion())) == _TRUE)
    {
        SysAudioMuteProc(_ON);
        ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

#if(_LINE_IN_SUPPORT == _ON)
        if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
        {
            if(SysAudioCheckSourceJudge() == _TRUE)
            {
                ScalerAudioSourceInputSwitch(_LINE_IN_AUDIO, SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion()));

#if(_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON)
                UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(_LINE_IN_AUDIO));
#endif
            }
        }
        else
#endif
        {
            if(GET_RGN_SOURCE_JUDGE(UserInterfaceGetAudioRegionIndex()) == _TRUE)
            {
                ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion()));

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
                UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(_DIGITAL_AUDIO));
#endif
            }
        }

        SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
    }

#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Digital Audio Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioDigitalAudioHandler(void)
{
    ScalerAudioDigitalOutputMute(UserInterfaceGetAudioNonLPCMStatus());

    ScalerAudioDigitalDetect();

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    ScalerAudioSpdifChannelStatusProc(UserInterfaceGetAudioSource(), SysSourceGetInputPort());
#endif
}

//--------------------------------------------------
// Description  : Change Audio State
// Input Value  : Target Audio State
// Output Value : Node
//--------------------------------------------------
void SysAudioChangeAudioState(EnumAudioState enumAudioState)
{
    SET_AUDIO_STATE(enumAudioState);
    SET_AUDIO_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Audio Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioInitial(void)
{
    ScalerAudioInitial();

    ScalerAudioSourceInputSwitch(UserInterfaceGetAudioSource(), SysSourceGetInputPort());

#if(_EMBEDDED_DAC_SUPPORT == _ON)

    ScalerAudioDACSetVcmReady(_ON);

    ScalerAudioDACSetState(_AUDIO_DAC_INITIAL);
#endif
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Audio Secondary Data Reset Process
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysAudioDpAudioSecDataResetProc(BYTE ucInputPort)
{
    if(ucInputPort == ScalerAudioGetDigitalAudioPortMapping())
    {
        SysAudioMuteProc(_ON);
        ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        ScalerAudioDACNormalToDepop();
#endif

        SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
    }

    ScalerSyncDpSecDataReset(ucInputPort);
}
#endif

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Source Judge Sraus
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysAudioCheckSourceJudge(void)
{
#if(_MULTI_DISPLAY_MAX == 0x04)

    return (GET_RGN_SOURCE_JUDGE(0x00) | GET_RGN_SOURCE_JUDGE(0x01) | GET_RGN_SOURCE_JUDGE(0x02) | GET_RGN_SOURCE_JUDGE(0x03));

#elif(_MULTI_DISPLAY_MAX == 0x02)

    return (GET_RGN_SOURCE_JUDGE(0x00) | GET_RGN_SOURCE_JUDGE(0x01));

#elif(_MULTI_DISPLAY_MAX == 0x01)

    return GET_RGN_SOURCE_JUDGE(0x00);

#endif
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Sleep Audio Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioSleepAudioHandler(void)
{
    if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
    {
        if(GET_AUDIO_STATE() == _AUDIO_STATUS_PREPARING)
        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
               (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO) &&
               (ScalerAudioGetDigitalAudioSource(SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion())) == _DIGITAL_AUDIO_SOURCE_DP))
            {
                SET_AUDIO_PLAYBACK_SEARCH_INDEX(GET_RGN_SOURCE_INDEX(UserInterfaceGetAudioRegionIndex()));

                ScalerAudioDpAudioEnable(_ENABLE, SysSourceGetInputPort());

                DebugMessageAudio("Sleep Audio Playback Index", GET_AUDIO_PLAYBACK_SEARCH_INDEX());
            }
#endif

#if((_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
            SET_AUDIO_PLAYING_ALONE();

            return;
#endif
        }
        else if(GET_AUDIO_STATE() == _AUDIO_STATUS_PLAYBACK)
        {
#if((_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
            {
                SET_AUDIO_PLAYING_ALONE();

                return;
            }
#endif

#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
               (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO) &&
               (ScalerAudioGetDigitalAudioSource(SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion())) == _DIGITAL_AUDIO_SOURCE_DP))
            {
                SET_AUDIO_PLAYING_ALONE();

                return;
            }
#endif
        }
    }

    CLR_AUDIO_PLAYING_ALONE();
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Internal Audio Gen Test Process
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void SysAudioInternalGenTestProc(bit bOn)
{
    SysAudioMuteProc(_ON);

    if(bOn == _ON)
    {
        ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

        ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, SysSourceGetInputPort());
        ScalerAudioInternalAudioGenSwitch(_ON, SysSourceGetInputPort());

        ScalerAudioDigitalVolumeMute(_OFF, UserInterfaceGetAudioVolume());
    }
    else
    {
        ScalerAudioInternalAudioGenSwitch(_OFF, SysSourceGetInputPort());
        SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
    }
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

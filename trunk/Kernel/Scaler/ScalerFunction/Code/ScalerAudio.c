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
// ID Code      : ScalerAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_AUDIO__

#include "ScalerFunctionInclude.h"

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DVC_VOLUME_MUTE_TIMER                  400 // ms
#define _DVC_VOLUME_ADJUST_TIMER                20 // ms

#define _DVC_DB_STEP_NUMBER                     64
#define _DVC_ZCD_TIMEOUT_DEFAULT                (0x0030 & 0x0FFF) // 48KHz, Fcut = 500Hz

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

#if(_D2_HDMI_SUPPORT == _ON)
StructAudioDigitalInfo g_stAudioD2DigtalInfo;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
StructAudioDigitalInfo g_stAudioD3DigtalInfo;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
StructAudioDigitalInfo g_stAudioD4DigtalInfo;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
StructAudioDigitalInfo g_stAudioD5DigtalInfo;
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
StructAudioDACInfo g_stAudioDACInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerAudioInitial(void);
void ScalerAudioDigitalAdjustVolume(WORD usVolume);
void ScalerAudioMuteProc(bit bMute, WORD usVolume);
void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume);
void ScalerAudioDisable(void);
void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput);
BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput);
bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);

#if(_DP_SUPPORT == _ON)
void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort);
#endif

#if(_LINE_IN_SUPPORT == _ON)
EnumAudioInputSource ScalerAudioGetInputSource(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
void ScalerAudioDACInitial(void);
void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput);
void ScalerAudioDACSetState(EnumAudioDACState enumTargetState);
EnumAudioDACState ScalerAudioDACGetState(void);
bit ScalerAudioDACGetStateChange(void);
void ScalerAudioDACClrStateChange(void);
void ScalerAudioDACSetVcmReady(bit bReady);
void ScalerAudioDACNormalToDepop(void);
void ScalerAudioDACDepopToNormal(void);
void ScalerAudioDACOutputEnable(void);
EnumAudioDACOutput ScalerAudioDACGetOutput(void);
void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain);
#endif

void ScalerAudioDVCInitial(void);
void ScalerAudioDVCVolumeAdjustType(bit bAdjustType);
void ScalerAudioDVCAdjustVolume(WORD usVolume);
void ScalerAudioDVCVolumeMute(bit bMute, WORD usVolume);
void ScalerAudioDVCSetMuteZCDTimeout(bit bMute, WORD usVolume, bit bAdjustType);
void ScalerAudioDVCSetVolumeZCDTimeout(WORD usVolume);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
void ScalerAudioSpdifCheckIfSamplingFrequencyChange(BYTE ucInputPort);
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
void ScalerAudioD0DPAudioInitial(void);
void ScalerAudioD0DPDigitalOutputProc(bit bEnable);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
void ScalerAudioD1DPAudioInitial(void);
void ScalerAudioD1DPDigitalOutputProc(bit bEnable);
#endif

#endif

#if(_HDMI_SUPPORT == _ON)
#if(_D2_HDMI_SUPPORT == _ON)
void ScalerAudioD2DigitalDetectProc(void);
bit ScalerAudioD2GetAudioDetected(void);
void ScalerAudioD2HDMIAudioInitial(void);
void ScalerAudioD2LoadInitialICode(void);
void ScalerAudioD2LoadStableICodeEvent(void);
EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void);
void ScalerAudioD2SetAudioPLL(void);
void ScalerAudioD2WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
bit ScalerAudioD2GetInternalAudioGenEnable(void);
void ScalerAudioD2InternalAudioGenSwitch(bit bOn);
#endif

#endif

#if(_D3_HDMI_SUPPORT == _ON)
void ScalerAudioD3DigitalDetectProc(void);
bit ScalerAudioD3GetAudioDetected(void);
void ScalerAudioD3HDMIAudioInitial(void);
void ScalerAudioD3LoadInitialICode(void);
void ScalerAudioD3LoadStableICodeEvent(void);
EnumAudioSamplingFreqType ScalerAudioD3SamplingFreqDetect(void);
void ScalerAudioD3SetAudioPLL(void);
void ScalerAudioD3WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
bit ScalerAudioD3GetInternalAudioGenEnable(void);
void ScalerAudioD3InternalAudioGenSwitch(bit bOn);
#endif

#endif

#if(_D4_HDMI_SUPPORT == _ON)
void ScalerAudioD4DigitalDetectProc(void);
bit ScalerAudioD4GetAudioDetected(void);
void ScalerAudioD4HDMIAudioInitial(void);
void ScalerAudioD4LoadInitialICode(void);
void ScalerAudioD4LoadStableICodeEvent(void);
EnumAudioSamplingFreqType ScalerAudioD4SamplingFreqDetect(void);
void ScalerAudioD4SetAudioPLL(void);
void ScalerAudioD4WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
bit ScalerAudioD4GetInternalAudioGenEnable(void);
void ScalerAudioD4InternalAudioGenSwitch(bit bOn);
#endif

#endif

#if(_D5_HDMI_SUPPORT == _ON)
void ScalerAudioD5DigitalDetectProc(void);
bit ScalerAudioD5GetAudioDetected(void);
void ScalerAudioD5HDMIAudioInitial(void);
void ScalerAudioD5LoadInitialICode(void);
void ScalerAudioD5LoadStableICodeEvent(void);
EnumAudioSamplingFreqType ScalerAudioD5SamplingFreqDetect(void);
void ScalerAudioD5SetAudioPLL(void);
void ScalerAudioD5WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
bit ScalerAudioD5GetInternalAudioGenEnable(void);
void ScalerAudioD5InternalAudioGenSwitch(bit bOn);
#endif

#endif

#endif

#if(_LINE_IN_SUPPORT == _ON)
void ScalerAudioSetADCAudioPLL(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
bit ScalerAudioGetDpStandaloneAudioStatus(BYTE ucInputPort);
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Audio Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioInitial(void)
{
    ScalerAudioDigitalAudioInitial();

    ScalerAudioDVCInitial();
}

//--------------------------------------------------
// Description  : Adjust Digital volume
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalAdjustVolume(WORD usVolume)
{
    ScalerAudioDVCSetVolumeZCDTimeout(usVolume);

    ScalerAudioDVCAdjustVolume(usVolume);
}

//--------------------------------------------------
// Description  : Audio Mute proc
// Input Value  : bMute, usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioMuteProc(bit bMute, WORD usVolume)
{
    ScalerAudioDigitalVolumeMute(bMute, usVolume);
}

//--------------------------------------------------
// Description  : Smooth adjust digital volume for mute/unmute
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeMute(bMute, usVolume);
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDisable(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)

    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL);
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);

    ScalerAudioDACNormalToDepop();

    ScalerAudioDACSetVcmReady(_OFF);

    // Power Down Depop CLK
    ScalerSetBit(P6_D4_DA_CLK_CTRL, ~_BIT4, 0x00);

    // Power Down DAC
    ScalerSetByte(P6_C0_REG_DAC_POWER0, 0x00);
    ScalerSetBit(P6_C1_REG_DAC_POWER1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    SET_AUDIO_DAC_STATE(_AUDIO_DAC_OFF);

#endif

#if(_LINE_IN_SUPPORT == _ON)
    // Power Down ADC
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~_BIT7, 0x00);

    // Power Down Input Buffer and Mbias
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

    // Disable DVC counter for power saving
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);

    // Power Down DPLL
    ScalerAudioDisableAudioPLL();
}

//--------------------------------------------------
// Description  : Switch Audio Input Port For Each Audio Output
// Input Value  : ucAudioOutput, ucAudioInput
// Output Value : None
//--------------------------------------------------
void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput)
{
    // Set DAC Input
    ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT2 | _BIT1 | _BIT0), enumAudioInput);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _OFF)
    // Set IIS Input
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT6 | _BIT5 | _BIT4), (enumAudioInput << 4));

    // Set SPDIF Input
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT2 | _BIT1 | _BIT0), enumAudioInput);
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _ON)
    // Set DP Tx Input
    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), enumAudioInput);
#endif
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio Port For Output Type
// Input Value  : None
// Output Value : audio port
//--------------------------------------------------
BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:

            return (ScalerGetBit(P6F_01_MUX_DA_DVC_IN, (_BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_I2S_OUT:

            return (ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT6 | _BIT5 | _BIT4)) >> 4);

        case _AUDIO_SPDIF_OUT:

            return (ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_DPTX_OUT:

            return (ScalerGetBit(P6F_02_MUX_DP_I2S_IN, (_BIT2 | _BIT1 | _BIT0)));

        default:
            break;
    }

    return _AUDIO_FROM_D0_PORT;
}

//--------------------------------------------------
// Description  : Get if Digital Audio Port Changed
// Input Value  : ucInputPort
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(enumAudioSource != ScalerAudioGetInputSource())
    {
        return _TRUE;
    }
#endif

    if(enumAudioSource == _DIGITAL_AUDIO)
    {
        if(ucInputPort != ScalerAudioGetDigitalAudioPortMapping())
        {
            return _TRUE;
        }

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        if(ucInputPort == _D7_INPUT_PORT)
        {
            if(GET_D7_SWITCH_SELECT() == _D0_INPUT_PORT)
            {
                if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_D0_PORT)
                {
                    return _TRUE;
                }
            }
            else if(GET_D7_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
                if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_D1_PORT)
                {
                    return _TRUE;
                }
            }
            else if(GET_D7_SWITCH_SELECT() == _D7_INPUT_PORT)
            {
                if(GET_AUDIO_D0_PACKET_DETECT() == _TRUE)
                {
                    if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_D0_PORT)
                    {
                        return _TRUE;
                    }
                }
                else if(GET_AUDIO_D1_PACKET_DETECT() == _TRUE)
                {
                    if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_D1_PORT)
                    {
                        return _TRUE;
                    }
                }
            }
        }
#endif
    }

    return _FALSE;
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable DP audio FSM
// Input Value  : Enable or Disable, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, ((BYTE)bEnable) << 7);
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~_BIT7, ((BYTE)bEnable) << 7);
#endif
            break;

        default:
            break;
    }
}
#endif

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current DAC Input Source
// Input Value  : None
// Output Value : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
//--------------------------------------------------
EnumAudioInputSource ScalerAudioGetInputSource(void)
{
    return ((ScalerGetBit(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
}
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Audio DAC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACInitial(void)
{
    // Power On DAC
    ScalerSetByte(P6_C0_REG_DAC_POWER0, 0xFF);

    // Set DAC Clock Divider, Enable Depop Clock and Set Depop Clock
    ScalerSetByte(P6_D4_DA_CLK_CTRL, 0x12);

    // Power On Depop Circuit and Set Vcm Voltage as 1.65V
    ScalerSetByte(P6_C1_REG_DAC_POWER1, 0xF1);

    // Mute DAC and Set DAC Clock Source
    ScalerSetBit(P6_D1_DA_MUTE, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

    // Set DAC Volume Of L Ch
    ScalerSetByte(P6_D2_DA_GAIN_L, 0x57);

    // Set DAC Volume Of R Ch
    ScalerSetByte(P6_D3_DA_GAIN_R, 0x57);

    // Set Double Buffer
    ScalerSetBit(P6_D2_DA_GAIN_L, ~_BIT7, _BIT7);

#if(_DAC_SPEAKER_OUTPUT_SWAP == _OFF)
    // Set Speaker L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#else
    // Swap Speaker L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#endif

#if(_DAC_HP_OUTPUT_SWAP == _OFF)
    // Set Headphone L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#else
    // Swap Headphone L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : Switch audio output (AOUT / HPOut)
// Input Value  : enumDACOutput
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput)
{
    switch(enumDACOutput)
    {
        case _AUDIO_DAC_OUTPUT_BOTH:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            break;

        case _AUDIO_DAC_OUTPUT_SPEAKER:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), _BIT5);

            break;

        case _AUDIO_DAC_OUTPUT_HEADPHONE:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), _BIT4);

            break;

        default:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), 0x00);

            break;
    }
}

//--------------------------------------------------
// Description  : Change Auido DAC State
// Input Value  : Target Audio DAC State
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetState(EnumAudioDACState enumTargetState)
{
    SET_AUDIO_DAC_STATE(enumTargetState);
    SET_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Get Curretn DAC State
// Input Value  : None
// Output Value : Current DAC State
//--------------------------------------------------
EnumAudioDACState ScalerAudioDACGetState(void)
{
    return GET_AUDIO_DAC_STATE();
}

//--------------------------------------------------
// Description  : Get Curretn DAC State Change
// Input Value  : None
// Output Value : TRUE => State Changed
//--------------------------------------------------
bit ScalerAudioDACGetStateChange(void)
{
    return GET_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Clear DAC State Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACClrStateChange(void)
{
    CLR_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : When Vcm already charge to AVDD/2, Vo(Output Voltage) should charge as Vcm
// Input Value  : bReady
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetVcmReady(bit bReady)
{
    ScalerSetBit(P6_C5_REG_ANA_CTRL, ~_BIT0, (BYTE) bReady);
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACNormalToDepop(void)
{
    ScalerAudioDACSetVcmReady(_OFF);

    // Transfer normal to depop operation for AOUT
    ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~_BIT3, 0x00);

    // Transfer normal to depop operation for HP output
    ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~_BIT3, 0x00);

    // Disable AOUT
    ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Disable HP output
    ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    ScalerAudioDACSetVcmReady(_ON);

    ScalerAudioDACSetState(_AUDIO_DAC_DEPOP);
}

//--------------------------------------------------
// Description  : Transfer depop mode to normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDepopToNormal(void)
{
    // Transfer depop to normal operation for AOUT
    ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~_BIT3, _BIT3);

    // Transfer depop to normal operation and enable driving current for HP output
    ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~_BIT3, _BIT3);

    // Disable Vcm ready
    ScalerAudioDACSetVcmReady(_OFF);

    ScalerAudioDACSetState(_AUDIO_DAC_READY);
}

//--------------------------------------------------
// Description  : Switch AOUT/HPOUT to Normal Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputEnable(void)
{
    ScalerAudioDACSetVcmReady(_OFF);

    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT5) == _BIT5)
    {
        // Enable AOUT
        ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }

    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT4) == _BIT4)
    {
        // Enable HP Output
        ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }

    ScalerAudioDACSetVcmReady(_ON);
}

//--------------------------------------------------
// Description  : Get Current DAC Output Channel
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput ScalerAudioDACGetOutput(void)
{
    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        return _AUDIO_DAC_OUTPUT_BOTH;
    }
    else if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == _BIT5)
    {
        return _AUDIO_DAC_OUTPUT_SPEAKER;
    }
    else if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == _BIT4)
    {
        return _AUDIO_DAC_OUTPUT_HEADPHONE;
    }

    return _AUDIO_DAC_OUTPUT_NONE;
}

//--------------------------------------------------
// Description  : Set DAC Output Gain
// Input Value  : EnumAudioDACOutput, ucOutputGain
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain)
{
    if(enumOutputType == _AUDIO_DAC_OUTPUT_SPEAKER)
    {
        // Set AOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_OUT_GAIN, ~(_BIT6 | _BIT5 | _BIT4), (enumOutputGain << 4));
    }
    else if(enumOutputType == _AUDIO_DAC_OUTPUT_HEADPHONE)
    {
        // Set HPOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_OUT_GAIN, ~(_BIT2 | _BIT1 | _BIT0), enumOutputGain);
    }
    else if(enumOutputType == _AUDIO_DAC_OUTPUT_BOTH)
    {
        // Set AOUT and HPOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_OUT_GAIN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 4) | enumOutputGain));
    }
}
#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Initial DVC Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCInitial(void)
{
    // Enable DVC function and counter
    ScalerSetBit(P8_A0_DVC_EN, ~(_BIT7 | _BIT6), _BIT7);

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));

    // Select DVC Volume Adjust Type
    ScalerAudioDVCVolumeAdjustType(_DVC_ADJUST_TYPE);

    // Initial DVC gain = 0
    ScalerAudioDVCAdjustVolume(0x00);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _OFF)
    // Set Sampling Frequency "48kHz" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

    // Set Channel Count "2 ch" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E3_AD_SPDIF_CS_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable I2S Output for ADC In
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
#endif

    // Select SPDIF from DVC path
    ScalerSetBit(P6_E1_AD_SPDIF_CTRL, ~_BIT4, _BIT4);

    // Select I2S from DVC path
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT5, _BIT5);

    // Set I2S and SPDIF From DVC path
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_AUDIO_FROM_ADC_PORT << 4) | _AUDIO_FROM_ADC_PORT);
#endif
}

//--------------------------------------------------
// Description  : Select DVC Volume Adjust Type
// Input Value  : _DB_GAIN, _VOLUME_STEP_SIZE
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeAdjustType(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select value mode and set DB gain setp
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DB_GAIN_DOWN_VALUE << 2) | _DB_GAIN_UP_VALUE));

        // Initial volume step size for DB gain mode
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P8_A2_DVC_VA_LSB, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select value mode
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4), _BIT4);

        // Set volume step size
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_VOLUME_STEP_SIZE_VALUE));
        ScalerSetByte(P8_A2_DVC_VA_LSB, LOBYTE(_VOLUME_STEP_SIZE_VALUE));
    }
}

//--------------------------------------------------
// Description  : Adjust digital volume for DVC function
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCAdjustVolume(WORD usVolume)
{
    // DVC gain MSB
    ScalerSetBit(P8_A5_DVC_GAIN_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usVolume));

    // DVC gain LSB  (double buffer)
    ScalerSetByte(P8_A6_DVC_GAIN_LSB, LOBYTE(usVolume));

    // Set Double Buffer
    ScalerSetBit(P8_A7_DVC_GAIN_READ_MSB, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Mute/Unmute for DVC function
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeAdjustType(_DVC_ADJUST_TYPE);

    ScalerAudioDVCSetMuteZCDTimeout(bMute, usVolume, _DVC_ADJUST_TYPE);

    PDATA_WORD(0) = (((WORD) ScalerGetByte(P8_A7_DVC_GAIN_READ_MSB) << 8) | ScalerGetByte(P8_A8_DVC_GAIN_READ_LSB));

    if(bMute == _ON)
    {
        if(PDATA_WORD(0) != 0)
        {
            ScalerAudioDVCAdjustVolume(0);

            PDATA_WORD(1) = 0;

            do
            {
                ScalerTimerDelayXms(1);
                PDATA_WORD(1)++;
            }
            while((ScalerGetBit(P8_A9_DVC_GAIN_DONE, _BIT7) != _BIT7) && (PDATA_WORD(1) < _DVC_VOLUME_MUTE_TIMER));
        }
    }
    else // Unmute
    {
        if(PDATA_WORD(0) != usVolume)
        {
            ScalerAudioDVCAdjustVolume(usVolume);
        }
    }
}

//--------------------------------------------------
// Description  : Set ZCD Timeout
// Input Value  : bMute, usVolume, bAdjustType
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCSetMuteZCDTimeout(bit bMute, WORD usVolume, bit bAdjustType)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping());
    }

    if(bAdjustType == _DB_GAIN)
    {
        // Get down or up step
        pData[0] = (bMute == _ON) ? (ScalerGetBit(P8_A0_DVC_EN, (_BIT3 | _BIT2)) >> 2) : ScalerGetBit(P8_A0_DVC_EN, (_BIT1 | _BIT0));

        // Get numbers of the volume step for mute or unmute
        PDATA_WORD(0) = _DVC_DB_STEP_NUMBER << pData[0];
    }
    else
    {
        PDATA_WORD(0) = usVolume / _VOLUME_STEP_SIZE_VALUE + 1;
    }

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_MUTE_TIMER / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Set ZCD Timeout, only use the type "_VOLUME_STEP_SIZE"
// Input Value  : usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCSetVolumeZCDTimeout(WORD usVolume)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    ScalerAudioDVCVolumeAdjustType(_VOLUME_STEP_SIZE);

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping());
    }

    // Get Current Volume
    PDATA_WORD(0) = ((WORD)(ScalerGetByte(P8_A5_DVC_GAIN_MSB) & 0x3F) << 8) | ((WORD)ScalerGetByte(P8_A6_DVC_GAIN_LSB));

    PDATA_WORD(0) = (PDATA_WORD(0) > usVolume) ? (PDATA_WORD(0) - usVolume) : (usVolume - PDATA_WORD(0));

    PDATA_WORD(0) = PDATA_WORD(0) / _VOLUME_STEP_SIZE_VALUE + 1;

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_ADJUST_TIMER / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(PDATA_WORD(0)));
}

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle Smapling Frequency Infomation in SPDIF format
// Input Value  : enumAudioSource, ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
    if(enumAudioSource == _DIGITAL_AUDIO)
    {
        ScalerAudioSpdifCheckIfSamplingFrequencyChange(ucInputPort);
    }
    else if(enumAudioSource == _LINE_IN_AUDIO)
    {
        ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);
    }
}

//--------------------------------------------------
// Description  : Detect and Change Smapling Frequency Infomation in SPDIF format
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifCheckIfSamplingFrequencyChange(BYTE ucInputPort)
{
    switch(ScalerAudioSamplingFreqDetect(ucInputPort))
    {
        case _AUDIO_FREQ_PACKET_32K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_32KHZ);

            break;

        case _AUDIO_FREQ_PACKET_44_1K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_44_1KHZ);

            break;

        case _AUDIO_FREQ_PACKET_48K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

            break;

        case _AUDIO_FREQ_PACKET_88_2K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_88_2KHZ);

            break;

        case _AUDIO_FREQ_PACKET_96K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_96KHZ);

            break;

        case _AUDIO_FREQ_PACKET_176_4K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_176_4KHZ);

            break;

        case _AUDIO_FREQ_PACKET_192K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_192KHZ);

            break;

        default:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_NOT_INDICATED);

            break;
    }
}
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//--------------------------------------------------
// Description  : Initial D0 DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DPAudioInitial(void)
{
    ScalerAudioD0SetAudioPLL();

    // Disable Check VBID[4] to Mute Audio by HW and disable Audio FSM
    ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~(_BIT7 | _BIT1), 0x00);

    // Disable AFD, set 2ms for auto freq. detect and disable 44.1kHz as 48kHz
    ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT0), _BIT2);

    // Set threshold to sepeerate sampling frequency
    ScalerSetByte(PB6_52_AUD_FREQUENY_TH_0, 0x00);
    ScalerSetByte(PB6_53_AUD_FREQUENY_TH_1, 0x00);
    ScalerSetByte(PB6_54_AUD_FREQUENY_TH_2, 0x28);
    ScalerSetByte(PB6_55_AUD_FREQUENY_TH_3, 0x4C);
    ScalerSetByte(PB6_56_AUD_FREQUENY_TH_4, 0x5C);
    ScalerSetByte(PB6_57_AUD_FREQUENY_TH_5, 0x70);

    // Enable RS Decode
    ScalerSetBit(PB6_2B_MN_RS_DEC_CTRL, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set xtal divider for sampling freq. detection
    ScalerSetByte(PB6_51_AUD_FREQUENY_DET_1, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Enable SDM control
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT7, _BIT7);

    // Enalbe boundary tracking method
    ScalerSetBit(PB6_81_AUD_BDRY_0, ~_BIT7, _BIT7);

    // Set I code of boundary tracking
    ScalerSetByte(PB6_83_AUD_BDRY_2, HIBYTE(_INITIAL_I_CODE));
    ScalerSetByte(PB6_84_AUD_BDRY_3, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary tracking
    ScalerSetByte(PB6_85_AUD_BDRY_4, 0xFF);
    ScalerSetByte(PB6_86_AUD_BDRY_5, 0xFF);

    // Enalbe trend tracking method
    ScalerSetBit(PB6_92_AUD_TRND_0, ~_BIT7, _BIT7);

    // Set I code of trend tracking
    ScalerSetByte(PB6_99_AUD_TRND_7, 0x00);
    ScalerSetByte(PB6_9A_AUD_TRND_8, 0x02);

    // Set P code of trend tracking
    ScalerSetByte(PB6_9B_AUD_TRND_9, 0xFF);
    ScalerSetByte(PB6_9C_AUD_TRND_10, 0xFF);

    // Enable Audio Buffer
    ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Set AUD PKT ID
    ScalerSetByte(PB6_B1_DP_AUD_ID, 0x00);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Set S code by FW manual
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

    // Set D code by FW manual
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // S code for 32kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // D code for 32kHz
    ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // S code for 44.1kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // D code for 44.1kHz
    ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // S code for 48kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // D code for 48kHz
    ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // D code Double Buffer
    ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#else
    // Set S code by HW auto
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

    // Set D code by HW auto
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, _BIT6);

    // S code for 32kHz
    ScalerSetBit(PB6_58_SCODE_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // S code for 44.1kHz
    ScalerSetBit(PB6_59_SCODE_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // S code for 48kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // D code for 32kHz
    ScalerSetByte(PB6_5B_DCODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetByte(PB6_5C_DCODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

    // D code for 44.1kHz
    ScalerSetByte(PB6_5D_DCODE_2, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetByte(PB6_5E_DCODE_3, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

    // D code for 48kHz
    ScalerSetByte(PB6_5F_DCODE_4, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetByte(PB6_60_DCODE_5, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable AFD
    ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~_BIT7, _BIT7);

    // Enable I2S Output
    ScalerSetBit(PB6_B8_DP_I2S_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable SPDIF Output
    ScalerSetBit(PB6_A9_SPDIF_TX_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    CLR_AUDIO_D0_ICODE_RELOADED();
}
//--------------------------------------------------
// Description  : DP Digital Audio Output Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DPDigitalOutputProc(bit bEnable)
{
    ScalerSetByte(PB6_B3_DP_CHANNEL_EN, ((bEnable == _ENABLE) ? 0xFF : 0x00));
}
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//--------------------------------------------------
// Description  : Initial D1 DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1DPAudioInitial(void)
{
    ScalerAudioD1SetAudioPLL();

    // Disable Check VBID[4] to Mute Audio by HW and disable Audio FSM
    ScalerSetBit(PB9_74_AUD_FSM_CTRL_0, ~(_BIT7 | _BIT1), 0x00);

    // Disable AFD, set 2ms for auto freq. detect and disable 44.1kHz as 48kHz
    ScalerSetBit(PB9_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT0), _BIT2);

    // Set threshold to sepeerate sampling frequency
    ScalerSetByte(PB9_52_AUD_FREQUENY_TH_0, 0x00);
    ScalerSetByte(PB9_53_AUD_FREQUENY_TH_1, 0x00);
    ScalerSetByte(PB9_54_AUD_FREQUENY_TH_2, 0x28);
    ScalerSetByte(PB9_55_AUD_FREQUENY_TH_3, 0x4C);
    ScalerSetByte(PB9_56_AUD_FREQUENY_TH_4, 0x5C);
    ScalerSetByte(PB9_57_AUD_FREQUENY_TH_5, 0x70);

    // Enable RS Decode
    ScalerSetBit(PB9_2B_MN_RS_DEC_CTRL, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set xtal divider for sampling freq. detection
    ScalerSetByte(PB9_51_AUD_FREQUENY_DET_1, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Enable SDM control
    ScalerSetBit(PB9_80_AUD_PS_CTRL_0, ~_BIT7, _BIT7);

    // Enalbe boundary tracking method
    ScalerSetBit(PB9_81_AUD_BDRY_0, ~_BIT7, _BIT7);

    // Set I code of boundary tracking
    ScalerSetByte(PB9_83_AUD_BDRY_2, HIBYTE(_INITIAL_I_CODE));
    ScalerSetByte(PB9_84_AUD_BDRY_3, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary tracking
    ScalerSetByte(PB9_85_AUD_BDRY_4, 0xFF);
    ScalerSetByte(PB9_86_AUD_BDRY_5, 0xFF);

    // Enalbe trend tracking method
    ScalerSetBit(PB9_92_AUD_TRND_0, ~_BIT7, _BIT7);

    // Set I code of trend tracking
    ScalerSetByte(PB9_99_AUD_TRND_7, 0x00);
    ScalerSetByte(PB9_9A_AUD_TRND_8, 0x02);

    // Set P code of trend tracking
    ScalerSetByte(PB9_9B_AUD_TRND_9, 0xFF);
    ScalerSetByte(PB9_9C_AUD_TRND_10, 0xFF);

    // Enable Audio Buffer
    ScalerSetBit(PB9_B0_DP_AUD_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Set AUD PKT ID
    ScalerSetByte(PB9_B1_DP_AUD_ID, 0x00);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Set S code by FW manual
    ScalerSetBit(PB9_58_SCODE_0, ~_BIT7, _BIT7);

    // Set D code by FW manual
    ScalerSetBit(PB9_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // S code for 32kHz
    ScalerSetBit(PB9_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // D code for 32kHz
    ScalerSetByte(PB9_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetByte(PB9_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // S code for 44.1kHz
    ScalerSetBit(PB9_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // D code for 44.1kHz
    ScalerSetByte(PB9_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetByte(PB9_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // S code for 48kHz
    ScalerSetBit(PB9_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // D code for 48kHz
    ScalerSetByte(PB9_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetByte(PB9_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // D code Double Buffer
    ScalerSetBit(PB9_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#else
    // Set S code by HW auto
    ScalerSetBit(PB9_58_SCODE_0, ~_BIT7, 0x00);

    // Set D code by HW auto
    ScalerSetBit(PB9_80_AUD_PS_CTRL_0, ~_BIT6, _BIT6);

    // S code for 32kHz
    ScalerSetBit(PB9_58_SCODE_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // S code for 44.1kHz
    ScalerSetBit(PB9_59_SCODE_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // S code for 48kHz
    ScalerSetBit(PB9_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // D code for 32kHz
    ScalerSetByte(PB9_5B_DCODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetByte(PB9_5C_DCODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

    // D code for 44.1kHz
    ScalerSetByte(PB9_5D_DCODE_2, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetByte(PB9_5E_DCODE_3, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

    // D code for 48kHz
    ScalerSetByte(PB9_5F_DCODE_4, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetByte(PB9_60_DCODE_5, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable AFD
    ScalerSetBit(PB9_50_AUD_FREQUENY_DET_0, ~_BIT7, _BIT7);

    // Enable I2S Output
    ScalerSetBit(PB9_B8_DP_I2S_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable SPDIF Output
    ScalerSetBit(PB9_A9_SPDIF_TX_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    CLR_AUDIO_D1_ICODE_RELOADED();
}
//--------------------------------------------------
// Description  : DP Digital Audio Output Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1DPDigitalOutputProc(bit bEnable)
{
    ScalerSetByte(PB9_B3_DP_CHANNEL_EN, ((bEnable == _ENABLE) ? 0xFF : 0x00));
}
#endif

#endif

#if(_HDMI_SUPPORT == _ON)
#if(_D2_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect D2 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2DigitalDetectProc(void)
{
    if(ScalerAudioD2SamplingFreqDetect() != 0x00)
    {
        SET_AUDIO_D2_PACKET_DETECT();
        SET_D2_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);

        if(GET_AUDIO_D2_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D2_LOAD_STABLE_I_CODE);

            SET_AUDIO_D2_ICODE_RELOADED();
        }
    }
    else
    {
        CLR_AUDIO_D2_PACKET_DETECT();
        SET_D2_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D2_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D2_LOAD_STABLE_I_CODE);

            ScalerAudioD2LoadInitialICode();

            CLR_AUDIO_D2_ICODE_RELOADED();
        }
    }
}
//--------------------------------------------------
// Description  : Get D2 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD2GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D2_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D2 Audio Packet", 0);
        return _FALSE;
    }

    // Check AVMute
    if(ScalerGetBit(P71_CB_HDMI_SR, _BIT6) == _BIT6)
    {
        DebugMessageAudio("False : D2 AVMute", 0);
        return _FALSE;
    }

    // Check HDMI audio FIFO overflow and underflow
    if(ScalerGetBit(P71_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : D2 HDMI Audio FIFO", ScalerGetBit(P71_CB_HDMI_SR, (_BIT2 | _BIT1)));

        // Clear HDMI audio FIFO overflow and underflow status
        ScalerSetBit(P71_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Initial 2 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2HDMIAudioInitial(void)
{
    ScalerAudioD2SetAudioPLL();

    // Disable sine wave generator
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Enable FIFO Boundary Tracking, Diable Trend Tracking
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_15_PORT_PAGE71_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT2));

    // Enable SDM
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_2D_PORT_PAGE71_HDMI_AAPNR, ~_BIT1, _BIT1);

    // Set auto gain delay mode and final gain = full gain
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_07_PORT_PAGE71_HDMI_MAG_M_FINAL, ~_BIT3, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_0A_PORT_PAGE71_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_0B_PORT_PAGE71_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_0D_PORT_PAGE71_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set I code of trend
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_20_PORT_PAGE71_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_21_PORT_PAGE71_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_22_PORT_PAGE71_HDMI_PCTPSR0, 0xFF);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_23_PORT_PAGE71_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_26_PORT_PAGE71_HDMI_PCBPSR0, 0xFF);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_27_PORT_PAGE71_HDMI_PCBPSR1, 0xFF);

    // Audio Normal Output
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_32_PORT_PAGE71_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_33_PORT_PAGE71_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_9F_PORT_PAGE71_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8B_PORT_PAGE71_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8C_PORT_PAGE71_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_8E_PORT_PAGE71_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to sepeerate sampling frequency
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_90_PORT_PAGE71_TH1, 0x00);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_91_PORT_PAGE71_TH2, 0x28);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_92_PORT_PAGE71_TH3, 0x4C);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_93_PORT_PAGE71_TH4, 0x5C);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_94_PORT_PAGE71_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Disable Auto Load S Code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set D code for 32kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set D code for 44.1kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for 48kHz
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT6, 0x00);

#else

    // Set S code for auto load mode
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_95_PORT_PAGE71_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_96_PORT_PAGE71_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_97_PORT_PAGE71_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for auto load mode
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_99_PORT_PAGE71_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9A_PORT_PAGE71_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9B_PORT_PAGE71_PRESET_D_CODE_2, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9C_PORT_PAGE71_PRESET_D_CODE_3, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9D_PORT_PAGE71_PRESET_D_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_9E_PORT_PAGE71_PRESET_D_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set The Manual S code = 1
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, 0x81);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable Audio Freq Detect
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~_BIT7, _BIT7);

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_62_PORT_PAGE71_HDMI_AOCR, 0xFF);

    CLR_AUDIO_D2_ICODE_RELOADED();
}
//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2LoadInitialICode(void)
{
    // Set high byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}
//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2LoadStableICodeEvent(void)
{
    // Set high byte of I code for boundary tracking
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1, LOBYTE(_STABLE_I_CODE));

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}
//--------------------------------------------------
// Description  : Detect D2 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD2GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D2_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    pData[0] = ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8B_PORT_PAGE71_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D2_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D2_SAMPLING_FREQ(pData[0]);

    return pData[0];
}
//--------------------------------------------------
// Description  : Initial 2 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2SetAudioPLL(void)
{
    // Set M code
    ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_11_PORT_PAGE71_HDMI_MCAPR, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~(_BIT5 | _BIT4), 0x00);

    // Set K code and enable double buffer
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | ((_AUDIO_PLL_K - 2) & 0x0F)));

    // DPLL VCORSTB Set to Normal
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3B_PORT_PAGE71_HDMI_DPCR3, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT0, _BIT0);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT1, _BIT1);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0, ~_BIT2, _BIT2);
}
//--------------------------------------------------
// Description  : D2 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(P71_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }
    else
    {
        // Disable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
    }
}

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioD2GetInternalAudioGenEnable(void)
{
    if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, _BIT4) == _BIT4)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}
//--------------------------------------------------
// Description  : D2 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD2InternalAudioGenSwitch(bit bOn)
{
    if(bOn == _ON)
    {
        DebugMessageAudio("D2 Audio Test On", ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, _BIT4));

        // Disable audio FIFO and Enable audio internal generator
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Disbale DPLL Freq. Tuning
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2, ~_BIT1, 0x00);

        // Set S code
        ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Disable sample freq. detection and auto load S code / D code
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~(_BIT7 | _BIT6), 0x00);

        // Enable double buffer
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

        ScalerAudioDigitalOutputMute(_OFF);
    }
    else
    {
        DebugMessageAudio("D2 Aduio Test Off", ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, _BIT4));

        ScalerAudioDigitalOutputMute(_ON);

        // Enable sample freq. detection and auto load S code
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable double buffer
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR, ~_BIT4, _BIT4);

        // Enable DPLL Freq. Tuning
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2, ~_BIT1, _BIT1);

        // Enable audio FIFO and Disable audio internal generator
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
    }
}
#endif

#endif

#if(_D3_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect D3 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3DigitalDetectProc(void)
{
    if(ScalerAudioD3SamplingFreqDetect() != 0x00)
    {
        SET_AUDIO_D3_PACKET_DETECT();
        SET_D3_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);

        if(GET_AUDIO_D3_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D3_LOAD_STABLE_I_CODE);

            SET_AUDIO_D3_ICODE_RELOADED();
        }
    }
    else
    {
        CLR_AUDIO_D3_PACKET_DETECT();
        SET_D3_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D3_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D3_LOAD_STABLE_I_CODE);

            ScalerAudioD3LoadInitialICode();

            CLR_AUDIO_D3_ICODE_RELOADED();
        }
    }
}
//--------------------------------------------------
// Description  : Get D3 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD3GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D3_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D3 Audio Packet", 0);
        return _FALSE;
    }

    // Check AVMute
    if(ScalerGetBit(P72_CB_HDMI_SR, _BIT6) == _BIT6)
    {
        DebugMessageAudio("False : D3 AVMute", 0);
        return _FALSE;
    }

    // Check HDMI audio FIFO overflow and underflow
    if(ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : D3 HDMI Audio FIFO", ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)));

        // Clear HDMI audio FIFO overflow and underflow status
        ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Initial D3 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3HDMIAudioInitial(void)
{
    ScalerAudioD3SetAudioPLL();

    // Disable sine wave generator
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Enable FIFO Boundary Tracking, Diable Trend Tracking
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT2));

    // Enable SDM
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_2D_PORT_PAGE72_HDMI_AAPNR, ~_BIT1, _BIT1);

    // Set auto gain delay mode and final gain = full gain
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~_BIT3, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_0A_PORT_PAGE72_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_0B_PORT_PAGE72_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_0D_PORT_PAGE72_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set I code of trend
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_20_PORT_PAGE72_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_21_PORT_PAGE72_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_22_PORT_PAGE72_HDMI_PCTPSR0, 0xFF);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_23_PORT_PAGE72_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_24_PORT_PAGE72_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_25_PORT_PAGE72_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_26_PORT_PAGE72_HDMI_PCBPSR0, 0xFF);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_27_PORT_PAGE72_HDMI_PCBPSR1, 0xFF);

    // Audio Normal Output
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_32_PORT_PAGE72_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_33_PORT_PAGE72_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_9F_PORT_PAGE72_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8C_PORT_PAGE72_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_8E_PORT_PAGE72_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to sepeerate sampling frequency
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_90_PORT_PAGE72_TH1, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_91_PORT_PAGE72_TH2, 0x28);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_92_PORT_PAGE72_TH3, 0x4C);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_93_PORT_PAGE72_TH4, 0x5C);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_94_PORT_PAGE72_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Disable Auto Load S Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_12_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set D code for 32kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_13_PORT_PAGE72_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_12_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set D code for 44.1kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_13_PORT_PAGE72_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_12_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for 48kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_13_PORT_PAGE72_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_10_PORT_PAGE72_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~_BIT6, 0x00);

#else

    // Set S code for auto load mode
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_95_PORT_PAGE72_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_96_PORT_PAGE72_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_97_PORT_PAGE72_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for auto load mode
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_99_PORT_PAGE72_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_9A_PORT_PAGE72_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_9B_PORT_PAGE72_PRESET_D_CODE_2, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_9C_PORT_PAGE72_PRESET_D_CODE_3, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_9D_PORT_PAGE72_PRESET_D_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_9E_PORT_PAGE72_PRESET_D_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set The Manual S code = 1
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_12_PORT_PAGE72_HDMI_SCAPR, 0x81);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_10_PORT_PAGE72_HDMI_CMCR, ~_BIT4, _BIT4);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable Audio Freq Detect
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~_BIT7, _BIT7);

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR, 0xFF);

    CLR_AUDIO_D3_ICODE_RELOADED();
}
//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3LoadInitialICode(void)
{
    // Set high byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_24_PORT_PAGE72_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_25_PORT_PAGE72_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}
//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3LoadStableICodeEvent(void)
{
    // Set high byte of I code for boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_24_PORT_PAGE72_HDMI_ICBPSR0, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_25_PORT_PAGE72_HDMI_ICBPSR1, LOBYTE(_STABLE_I_CODE));

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}
//--------------------------------------------------
// Description  : Detect D3 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD3SamplingFreqDetect(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD3GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D3_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    pData[0] = ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D3_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D3_SAMPLING_FREQ(pData[0]);

    return pData[0];
}
//--------------------------------------------------
// Description  : Initial D3 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3SetAudioPLL(void)
{
    // Set M code
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_11_PORT_PAGE72_HDMI_MCAPR, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0, ~(_BIT5 | _BIT4), 0x00);

    // Set K code and enable double buffer
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_10_PORT_PAGE72_HDMI_CMCR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | ((_AUDIO_PLL_K - 2) & 0x0F)));

    // DPLL VCORSTB Set to Normal
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_3B_PORT_PAGE72_HDMI_DPCR3, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0, ~_BIT0, _BIT0);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0, ~_BIT1, _BIT1);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0, ~_BIT2, _BIT2);
}
//--------------------------------------------------
// Description  : D3 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }
    else
    {
        // Disable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
    }
}

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioD3GetInternalAudioGenEnable(void)
{
    if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT4) == _BIT4)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}
//--------------------------------------------------
// Description  : D3 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD3InternalAudioGenSwitch(bit bOn)
{
    if(bOn == _ON)
    {
        DebugMessageAudio("D3 Audio Test On", ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT4));

        // Disable audio FIFO and Enable audio internal generator
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Disbale DPLL Freq. Tuning
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_3A_PORT_PAGE72_HDMI_DPCR2, ~_BIT1, 0x00);

        // Set S code
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_12_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_13_PORT_PAGE72_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Disable sample freq. detection and auto load S code / D code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT7 | _BIT6), 0x00);

        // Enable double buffer
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_10_PORT_PAGE72_HDMI_CMCR, ~_BIT4, _BIT4);

        ScalerAudioDigitalOutputMute(_OFF);
    }
    else
    {
        DebugMessageAudio("D3 Aduio Test Off", ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT4));

        ScalerAudioDigitalOutputMute(_ON);

        // Enable sample freq. detection and auto load S code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable double buffer
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_10_PORT_PAGE72_HDMI_CMCR, ~_BIT4, _BIT4);

        // Enable DPLL Freq. Tuning
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_3A_PORT_PAGE72_HDMI_DPCR2, ~_BIT1, _BIT1);

        // Enable audio FIFO and Disable audio internal generator
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
    }
}
#endif

#endif

#if(_D4_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect D4 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4DigitalDetectProc(void)
{
    if(ScalerAudioD4SamplingFreqDetect() != 0x00)
    {
        SET_AUDIO_D4_PACKET_DETECT();
        SET_D4_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);

        if(GET_AUDIO_D4_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D4_LOAD_STABLE_I_CODE);

            SET_AUDIO_D4_ICODE_RELOADED();
        }
    }
    else
    {
        CLR_AUDIO_D4_PACKET_DETECT();
        SET_D4_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D4_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D4_LOAD_STABLE_I_CODE);

            ScalerAudioD4LoadInitialICode();

            CLR_AUDIO_D4_ICODE_RELOADED();
        }
    }
}
//--------------------------------------------------
// Description  : Get D4 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD4GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D4_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D4 Audio Packet", 0);
        return _FALSE;
    }

    // Check AVMute
    if(ScalerGetBit(P73_CB_HDMI_SR, _BIT6) == _BIT6)
    {
        DebugMessageAudio("False : D4 AVMute", 0);
        return _FALSE;
    }

    // Check HDMI audio FIFO overflow and underflow
    if(ScalerGetBit(P73_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : D4 HDMI Audio FIFO", ScalerGetBit(P73_CB_HDMI_SR, (_BIT2 | _BIT1)));

        // Clear HDMI audio FIFO overflow and underflow status
        ScalerSetBit(P73_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Initial D4 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4HDMIAudioInitial(void)
{
    ScalerAudioD4SetAudioPLL();

    // Disable sine wave generator
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Enable FIFO Boundary Tracking, Diable Trend Tracking
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_15_PORT_PAGE73_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT2));

    // Enable SDM
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_2D_PORT_PAGE73_HDMI_AAPNR, ~_BIT1, _BIT1);

    // Set auto gain delay mode and final gain = full gain
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_07_PORT_PAGE73_HDMI_MAG_M_FINAL, ~_BIT3, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_0A_PORT_PAGE73_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_0B_PORT_PAGE73_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_0D_PORT_PAGE73_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set I code of trend
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_20_PORT_PAGE73_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_21_PORT_PAGE73_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_22_PORT_PAGE73_HDMI_PCTPSR0, 0xFF);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_23_PORT_PAGE73_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_24_PORT_PAGE73_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_25_PORT_PAGE73_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_26_PORT_PAGE73_HDMI_PCBPSR0, 0xFF);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_27_PORT_PAGE73_HDMI_PCBPSR1, 0xFF);

    // Audio Normal Output
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_32_PORT_PAGE73_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_33_PORT_PAGE73_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_9F_PORT_PAGE73_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8B_PORT_PAGE73_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8C_PORT_PAGE73_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_8E_PORT_PAGE73_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to sepeerate sampling frequency
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_90_PORT_PAGE73_TH1, 0x00);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_91_PORT_PAGE73_TH2, 0x28);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_92_PORT_PAGE73_TH3, 0x4C);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_93_PORT_PAGE73_TH4, 0x5C);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_94_PORT_PAGE73_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Disable Auto Load S Code
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_12_PORT_PAGE73_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set D code for 32kHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_13_PORT_PAGE73_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_14_PORT_PAGE73_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_12_PORT_PAGE73_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set D code for 44.1kHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_13_PORT_PAGE73_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_14_PORT_PAGE73_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_12_PORT_PAGE73_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for 48kHz
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_13_PORT_PAGE73_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_14_PORT_PAGE73_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_10_PORT_PAGE73_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT6, 0x00);

#else

    // Set S code for auto load mode
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_95_PORT_PAGE73_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_96_PORT_PAGE73_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_97_PORT_PAGE73_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for auto load mode
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_99_PORT_PAGE73_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_9A_PORT_PAGE73_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_9B_PORT_PAGE73_PRESET_D_CODE_2, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_9C_PORT_PAGE73_PRESET_D_CODE_3, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_9D_PORT_PAGE73_PRESET_D_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_9E_PORT_PAGE73_PRESET_D_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set The Manual S code = 1
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_12_PORT_PAGE73_HDMI_SCAPR, 0x81);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_10_PORT_PAGE73_HDMI_CMCR, ~_BIT4, _BIT4);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable Audio Freq Detect
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~_BIT7, _BIT7);

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_62_PORT_PAGE73_HDMI_AOCR, 0xFF);

    CLR_AUDIO_D4_ICODE_RELOADED();
}
//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4LoadInitialICode(void)
{
    // Set high byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_24_PORT_PAGE73_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_25_PORT_PAGE73_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}
//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4LoadStableICodeEvent(void)
{
    // Set high byte of I code for boundary tracking
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_24_PORT_PAGE73_HDMI_ICBPSR0, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_25_PORT_PAGE73_HDMI_ICBPSR1, LOBYTE(_STABLE_I_CODE));

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}
//--------------------------------------------------
// Description  : Detect D4 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD4SamplingFreqDetect(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD4GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D4_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    pData[0] = ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8B_PORT_PAGE73_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D4_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D4_SAMPLING_FREQ(pData[0]);

    return pData[0];
}
//--------------------------------------------------
// Description  : Initial D4 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4SetAudioPLL(void)
{
    // Set M code
    ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_11_PORT_PAGE73_HDMI_MCAPR, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_38_PORT_PAGE73_HDMI_DPCR0, ~(_BIT5 | _BIT4), 0x00);

    // Set K code and enable double buffer
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_10_PORT_PAGE73_HDMI_CMCR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | ((_AUDIO_PLL_K - 2) & 0x0F)));

    // DPLL VCORSTB Set to Normal
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_3B_PORT_PAGE73_HDMI_DPCR3, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_38_PORT_PAGE73_HDMI_DPCR0, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_38_PORT_PAGE73_HDMI_DPCR0, ~_BIT0, _BIT0);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_38_PORT_PAGE73_HDMI_DPCR0, ~_BIT1, _BIT1);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_38_PORT_PAGE73_HDMI_DPCR0, ~_BIT2, _BIT2);
}
//--------------------------------------------------
// Description  : D4 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(P73_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }
    else
    {
        // Disable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
    }
}

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioD4GetInternalAudioGenEnable(void)
{
    if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, _BIT4) == _BIT4)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}
//--------------------------------------------------
// Description  : D4 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD4InternalAudioGenSwitch(bit bOn)
{
    if(bOn == _ON)
    {
        DebugMessageAudio("D4 Audio Test On", ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, _BIT4));

        // Disable audio FIFO and Enable audio internal generator
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Disbale DPLL Freq. Tuning
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_3A_PORT_PAGE73_HDMI_DPCR2, ~_BIT1, 0x00);

        // Set S code
        ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_12_PORT_PAGE73_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_13_PORT_PAGE73_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_14_PORT_PAGE73_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Disable sample freq. detection and auto load S code / D code
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~(_BIT7 | _BIT6), 0x00);

        // Enable double buffer
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_10_PORT_PAGE73_HDMI_CMCR, ~_BIT4, _BIT4);

        ScalerAudioDigitalOutputMute(_OFF);
    }
    else
    {
        DebugMessageAudio("D4 Aduio Test Off", ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, _BIT4));

        ScalerAudioDigitalOutputMute(_ON);

        // Enable sample freq. detection and auto load S code
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_8A_PORT_PAGE73_AUDIO_FREQDET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable double buffer
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_10_PORT_PAGE73_HDMI_CMCR, ~_BIT4, _BIT4);

        // Enable DPLL Freq. Tuning
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_3A_PORT_PAGE73_HDMI_DPCR2, ~_BIT1, _BIT1);

        // Enable audio FIFO and Disable audio internal generator
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
    }
}
#endif

#endif

#if(_D5_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect D5 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5DigitalDetectProc(void)
{
    if(ScalerAudioD5SamplingFreqDetect() != 0x00)
    {
        SET_AUDIO_D5_PACKET_DETECT();
        SET_D5_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);

        if(GET_AUDIO_D5_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D5_LOAD_STABLE_I_CODE);

            SET_AUDIO_D5_ICODE_RELOADED();
        }
    }
    else
    {
        CLR_AUDIO_D5_PACKET_DETECT();
        SET_D5_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D5_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D5_LOAD_STABLE_I_CODE);

            ScalerAudioD5LoadInitialICode();

            CLR_AUDIO_D5_ICODE_RELOADED();
        }
    }
}
//--------------------------------------------------
// Description  : Get D5 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD5GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D5_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D5 Audio Packet", 0);
        return _FALSE;
    }

    // Check AVMute
    if(ScalerGetBit(P74_CB_HDMI_SR, _BIT6) == _BIT6)
    {
        DebugMessageAudio("False : D5 AVMute", 0);
        return _FALSE;
    }

    // Check HDMI audio FIFO overflow and underflow
    if(ScalerGetBit(P74_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : D5 HDMI Audio FIFO", ScalerGetBit(P74_CB_HDMI_SR, (_BIT2 | _BIT1)));

        // Clear HDMI audio FIFO overflow and underflow status
        ScalerSetBit(P74_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Initial D5 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5HDMIAudioInitial(void)
{
    ScalerAudioD5SetAudioPLL();

    // Disable sine wave generator
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_03_PORT_PAGE74_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Enable FIFO Boundary Tracking, Diable Trend Tracking
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_15_PORT_PAGE74_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT2));

    // Enable SDM
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_2D_PORT_PAGE74_HDMI_AAPNR, ~_BIT1, _BIT1);

    // Set auto gain delay mode and final gain = full gain
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_07_PORT_PAGE74_HDMI_MAG_M_FINAL, ~_BIT3, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_0A_PORT_PAGE74_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_0B_PORT_PAGE74_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_0D_PORT_PAGE74_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set I code of trend
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_20_PORT_PAGE74_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_21_PORT_PAGE74_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_22_PORT_PAGE74_HDMI_PCTPSR0, 0xFF);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_23_PORT_PAGE74_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_24_PORT_PAGE74_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_25_PORT_PAGE74_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_26_PORT_PAGE74_HDMI_PCBPSR0, 0xFF);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_27_PORT_PAGE74_HDMI_PCBPSR1, 0xFF);

    // Audio Normal Output
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_32_PORT_PAGE74_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_33_PORT_PAGE74_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_9F_PORT_PAGE74_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8B_PORT_PAGE74_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8C_PORT_PAGE74_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_8E_PORT_PAGE74_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to sepeerate sampling frequency
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_90_PORT_PAGE74_TH1, 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_91_PORT_PAGE74_TH2, 0x28);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_92_PORT_PAGE74_TH3, 0x4C);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_93_PORT_PAGE74_TH4, 0x5C);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_94_PORT_PAGE74_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Disable Auto Load S Code D code
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_12_PORT_PAGE74_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set D code for 32kHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_13_PORT_PAGE74_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_14_PORT_PAGE74_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_12_PORT_PAGE74_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set D code for 44.1kHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_13_PORT_PAGE74_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_14_PORT_PAGE74_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_12_PORT_PAGE74_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for 48kHz
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_13_PORT_PAGE74_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_14_PORT_PAGE74_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_10_PORT_PAGE74_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT6, 0x00);

#else

    // Set S code for auto load mode
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_95_PORT_PAGE74_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_96_PORT_PAGE74_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_97_PORT_PAGE74_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for auto load mode
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_99_PORT_PAGE74_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_9A_PORT_PAGE74_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_9B_PORT_PAGE74_PRESET_D_CODE_2, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_9C_PORT_PAGE74_PRESET_D_CODE_3, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_9D_PORT_PAGE74_PRESET_D_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_9E_PORT_PAGE74_PRESET_D_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set The Manual S code = 1
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_12_PORT_PAGE74_HDMI_SCAPR, 0x81);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_10_PORT_PAGE74_HDMI_CMCR, ~_BIT4, _BIT4);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Enable Audio Freq Detect
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET, ~_BIT7, _BIT7);

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_62_PORT_PAGE74_HDMI_AOCR, 0xFF);

    CLR_AUDIO_D5_ICODE_RELOADED();
}
//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5LoadInitialICode(void)
{
    // Set high byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_24_PORT_PAGE74_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_25_PORT_PAGE74_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}
//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5LoadStableICodeEvent(void)
{
    // Set high byte of I code for boundary tracking
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_24_PORT_PAGE74_HDMI_ICBPSR0, HIBYTE(_STABLE_I_CODE));

    // Set low byte of I code for boundary tracking
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_25_PORT_PAGE74_HDMI_ICBPSR1, LOBYTE(_STABLE_I_CODE));

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}
//--------------------------------------------------
// Description  : Detect D5 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD5SamplingFreqDetect(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD5GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D5_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    pData[0] = ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8B_PORT_PAGE74_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(pData[0] != GET_AUDIO_D5_SAMPLING_FREQ())
    {
        if(pData[0] <= _AUDIO_FREQ_64K)
        {
            DebugMessageAudio("_AUDIO_FREQ_64K", pData[0]);
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(pData[0] <= _AUDIO_FREQ_128K)
        {
            DebugMessageAudio("_AUDIO_FREQ_128K", pData[0]);
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            DebugMessageAudio("_AUDIO_FREQ_192K", pData[0]);
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

    SET_AUDIO_D5_SAMPLING_FREQ(pData[0]);

    return pData[0];
}
//--------------------------------------------------
// Description  : Initial D5 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5SetAudioPLL(void)
{
    // Set M code
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_11_PORT_PAGE74_HDMI_MCAPR, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_38_PORT_PAGE74_HDMI_DPCR0, ~(_BIT5 | _BIT4), 0x00);

    // Set K code and enable double buffer
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_10_PORT_PAGE74_HDMI_CMCR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | ((_AUDIO_PLL_K - 2) & 0x0F)));

    // DPLL VCORSTB Set to Normal
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_3B_PORT_PAGE74_HDMI_DPCR3, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_38_PORT_PAGE74_HDMI_DPCR0, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_38_PORT_PAGE74_HDMI_DPCR0, ~_BIT0, _BIT0);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_38_PORT_PAGE74_HDMI_DPCR0, ~_BIT1, _BIT1);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_38_PORT_PAGE74_HDMI_DPCR0, ~_BIT2, _BIT2);
}
//--------------------------------------------------
// Description  : D5 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(P74_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }
    else
    {
        // Disable Audio Watch Dog for FIFO Overflow/Underflow
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
    }
}

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioD5GetInternalAudioGenEnable(void)
{
    if(ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_03_PORT_PAGE74_HDMI_AFCR, _BIT4) == _BIT4)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}
//--------------------------------------------------
// Description  : D5 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD5InternalAudioGenSwitch(bit bOn)
{
    if(bOn == _ON)
    {
        DebugMessageAudio("D5 Audio Test On", ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_03_PORT_PAGE74_HDMI_AFCR, _BIT4));

        // Disable audio FIFO and Enable audio internal generator
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_03_PORT_PAGE74_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Disbale DPLL Freq. Tuning
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_3A_PORT_PAGE74_HDMI_DPCR2, ~_BIT1, 0x00);

        // Set S code
        ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_12_PORT_PAGE74_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_13_PORT_PAGE74_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_14_PORT_PAGE74_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Disable sample freq. detection and auto load S code / D code
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET, ~(_BIT7 | _BIT6), 0x00);

        // Enable double buffer
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_10_PORT_PAGE74_HDMI_CMCR, ~_BIT4, _BIT4);

        ScalerAudioDigitalOutputMute(_OFF);
    }
    else
    {
        DebugMessageAudio("D5 Aduio Test Off", ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_03_PORT_PAGE74_HDMI_AFCR, _BIT4));

        ScalerAudioDigitalOutputMute(_ON);

        // Enable sample freq. detection and auto load S code
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable double buffer
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_10_PORT_PAGE74_HDMI_CMCR, ~_BIT4, _BIT4);

        // Enable DPLL Freq. Tuning
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_3A_PORT_PAGE74_HDMI_DPCR2, ~_BIT1, _BIT1);

        // Enable audio FIFO and Disable audio internal generator
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_03_PORT_PAGE74_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
    }
}
#endif

#endif

#endif

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial ADC Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetADCAudioPLL(void)
{
    // Set ADC PLL input clock
    ScalerSetBit(PBF_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6), 0x00);

    // Set M code
    ScalerSetBit(PBF_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(PBF_A1_MN_SCLKG_DIVM, 0x33);

    // Set S code
    ScalerSetByte(PBF_A3_MN_SCLKG_DIVS, 0x08);

    // Set Double Buffer
    ScalerSetBit(PBF_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // Enable SDM
    ScalerSetBit(PBF_B8_MN_SCLKG_SDM_CTRL, ~_BIT4, _BIT4);

    // Set Offset
    ScalerSetBit(PBF_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
    ScalerSetByte(PBF_A5_MN_SCLKG_OFFS_M, 0x29);
    ScalerSetByte(PBF_A6_MN_SCLKG_OFFS_L, 0xB5);

    // Load Offset
    ScalerSetBit(PBF_A4_MN_SCLKG_OFFS_H, ~_BIT7, _BIT7);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PBF_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetBit(PBF_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetBit(PBF_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetBit(PBF_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    // Delay 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetBit(PBF_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
//--------------------------------------------------
// Description  : Get Dp audio Status for Sleep Audio
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerAudioGetDpStandaloneAudioStatus(BYTE ucInputPort)
{
    return ((ScalerAudioGetDigitalAudioSource(ucInputPort) == _DIGITAL_AUDIO_SOURCE_DP) ? _TRUE : _FALSE);
}
#endif

#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)


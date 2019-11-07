/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerAudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#define _INITIAL_I_CODE                             0x0040
#define _STABLE_I_CODE                              0x0004

#define _AUDIO_DYNAMIC_I_CODE_TIMER_MS              100 // Unit: ms

#define _AUTO_FREQ_DETECT_XTAL_DIV                  (BYTE)(((((WORD) _SYS_CLK_KHZ << 1) / 160) + 1) >> 1)

#define _AUDIO_PLL_VCO                              378000 // 1KHz
#define _AUDIO_PLL_K                                2
#define _AUDIO_PLL_M                                (BYTE)((((DWORD) _AUDIO_PLL_VCO * _AUDIO_PLL_K * 2 / _GDI_CLK_KHZ) + 1) / 2)

#define _ZCD_TIMEOUT_DEFAULT                        0x1F

#define _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE        0xB0
#define _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE        0xA0
#define _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE        0xA0

#define _HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE        0xDAAC
#define _HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE        0x2EFE
#define _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE        0xDAAC

#define _DP_SAMPLING_FREQ_32K_GROUP_S_CODE          (0x30 & 0x7F)
#define _DP_SAMPLING_FREQ_44K_GROUP_S_CODE          (0x20 & 0x7F)
#define _DP_SAMPLING_FREQ_48K_GROUP_S_CODE          (0x20 & 0x7F)

#define _DP_SAMPLING_FREQ_32K_GROUP_D_CODE          0x274F
#define _DP_SAMPLING_FREQ_44K_GROUP_D_CODE          0xD0F6
#define _DP_SAMPLING_FREQ_48K_GROUP_D_CODE          0x274F

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#define GET_AUDIO_DAC_STATE()                       (g_stAudioDACInfo.b3AudioDACState)
#define SET_AUDIO_DAC_STATE(x)                      (g_stAudioDACInfo.b3AudioDACState = (x))

#define GET_AUDIO_DAC_STATE_CHANGE()                (bit)(g_stAudioDACInfo.b1AudioDACStateChange)
#define SET_AUDIO_DAC_STATE_CHANGE()                (g_stAudioDACInfo.b1AudioDACStateChange = _TRUE)
#define CLR_AUDIO_DAC_STATE_CHANGE()                (g_stAudioDACInfo.b1AudioDACStateChange = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
typedef struct
{
    BYTE b3AudioDACState : 3;
    BYTE b1AudioDACStateChange : 1;
}StructAudioDACInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern StructAudioDACInfo g_stAudioDACInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume);
extern void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput);
extern BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput);

#if(_DP_SUPPORT == _ON)
extern void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort);
#endif

#if(_LINE_IN_SUPPORT == _ON)
extern EnumAudioInputSource ScalerAudioGetInputSource(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern void ScalerAudioDACSetState(EnumAudioDACState enumTargetState);
extern void ScalerAudioDACSetVcmReady(bit bReady);
extern void ScalerAudioDACNormalToDepop(void);
extern void ScalerAudioDACDepopToNormal(void);
extern void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain);
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
extern void ScalerAudioD0DPAudioInitial(void);
extern void ScalerAudioD0DPDigitalOutputProc(bit bEnable);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
extern void ScalerAudioD1DPAudioInitial(void);
extern void ScalerAudioD1DPDigitalOutputProc(bit bEnable);
#endif

#endif

#if(_HDMI_SUPPORT == _ON)
#if(_D2_HDMI_SUPPORT == _ON)
extern void ScalerAudioD2DigitalDetectProc(void);
extern bit ScalerAudioD2GetAudioDetected(void);
extern void ScalerAudioD2HDMIAudioInitial(void);
extern void ScalerAudioD2LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void);
extern void ScalerAudioD2WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD2GetInternalAudioGenEnable(void);
extern void ScalerAudioD2InternalAudioGenSwitch(bit bOn);
#endif

#endif

#if(_D3_HDMI_SUPPORT == _ON)
extern void ScalerAudioD3DigitalDetectProc(void);
extern bit ScalerAudioD3GetAudioDetected(void);
extern void ScalerAudioD3HDMIAudioInitial(void);
extern void ScalerAudioD3LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD3SamplingFreqDetect(void);
extern void ScalerAudioD3WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD3GetInternalAudioGenEnable(void);
extern void ScalerAudioD3InternalAudioGenSwitch(bit bOn);
#endif

#endif

#if(_D4_HDMI_SUPPORT == _ON)
extern void ScalerAudioD4DigitalDetectProc(void);
extern bit ScalerAudioD4GetAudioDetected(void);
extern void ScalerAudioD4HDMIAudioInitial(void);
extern void ScalerAudioD4LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD4SamplingFreqDetect(void);
extern void ScalerAudioD4WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD4GetInternalAudioGenEnable(void);
extern void ScalerAudioD4InternalAudioGenSwitch(bit bOn);
#endif

#endif

#if(_D5_HDMI_SUPPORT == _ON)
extern void ScalerAudioD5DigitalDetectProc(void);
extern bit ScalerAudioD5GetAudioDetected(void);
extern void ScalerAudioD5HDMIAudioInitial(void);
extern void ScalerAudioD5LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD5SamplingFreqDetect(void);
extern void ScalerAudioD5WatchDogProc(bit bOn);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD5GetInternalAudioGenEnable(void);
extern void ScalerAudioD5InternalAudioGenSwitch(bit bOn);
#endif

#endif

#endif

#if(_LINE_IN_SUPPORT == _ON)
extern void ScalerAudioSetADCAudioPLL(void);
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)


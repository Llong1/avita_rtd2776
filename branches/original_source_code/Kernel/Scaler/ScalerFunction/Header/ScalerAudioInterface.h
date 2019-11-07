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
// ID Code      : ScalerAudioInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerAudioInitial(void);
extern void ScalerAudioDigitalAdjustVolume(WORD usVolume);
extern void ScalerAudioMuteProc(bit bMute, WORD usVolume);
extern void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume);
extern void ScalerAudioDisable(void);
extern BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput);
extern bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);

#if(_DP_SUPPORT == _ON)
extern void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort);
#endif

#if(_LINE_IN_SUPPORT == _ON)
extern EnumAudioInputSource ScalerAudioGetInputSource(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern void ScalerAudioDACInitial(void);
extern void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput);
extern void ScalerAudioDACSetState(EnumAudioDACState enumTargetState);
extern EnumAudioDACState ScalerAudioDACGetState(void);
extern bit ScalerAudioDACGetStateChange(void);
extern void ScalerAudioDACClrStateChange(void);
extern void ScalerAudioDACSetVcmReady(bit bReady);
extern void ScalerAudioDACNormalToDepop(void);
extern void ScalerAudioDACDepopToNormal(void);
extern void ScalerAudioDACOutputEnable(void);
extern EnumAudioDACOutput ScalerAudioDACGetOutput(void);
#endif

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
extern bit ScalerAudioGetDpStandaloneAudioStatus(BYTE ucInputPort);
#endif
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)


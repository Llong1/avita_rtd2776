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
// ID Code      : RL6410_Series_AudioInterface.h No.0000
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
extern void ScalerAudioDigitalDetect(void);
extern bit ScalerAudioGetAudioDetected(BYTE ucInputPort);
extern EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
extern bit ScalerAudioLPCMCheckData(BYTE ucInputPort);
extern void ScalerAudioDigitalOutputMute(bit bMute);
extern void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort);
extern void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
extern EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void);

#if(_HDMI_SUPPORT == _ON)
extern bit ScalerAudioLPCMCheckInfo(BYTE ucInputPort);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
extern BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort);
#endif
#endif

#if(_LINE_IN_SUPPORT == _ON)
extern void ScalerAudioADCInitial(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern void ScalerAudioInternalAudioGenSwitch(bit bOn, BYTE ucInputPort);
extern bit ScalerAudioGetInternalAudioGenEnable(BYTE ucInputPort);
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)

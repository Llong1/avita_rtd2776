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
// ID Code      : ScalerTMDSRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D0_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX0_PHY_SET()                          (g_stTMDSRx0CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX0_PHY_SET()                          (g_stTMDSRx0CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX0_PHY_SET()                          (g_stTMDSRx0CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX0_RGBHV_DETECTING()                  (g_stTMDSRx0CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX0_RGBHV_DETECTING()                  (g_stTMDSRx0CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX0_RGBHV_DETECTING()                  (g_stTMDSRx0CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX0_PACKET_DETECTING()                 (g_stTMDSRx0CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX0_PACKET_DETECTING()                 (g_stTMDSRx0CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX0_PACKET_DETECTING()                 (g_stTMDSRx0CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx0CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx0CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX0_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx0CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX0_GCP_RECEIVED()                     (g_stTMDSRx0CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX0_GCP_RECEIVED()                     (g_stTMDSRx0CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX0_GCP_RECEIVED()                     (g_stTMDSRx0CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX0_Z0_ASSERTED()                      (g_stTMDSRx0CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX0_Z0_ASSERTED()                      (g_stTMDSRx0CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX0_Z0_ASSERTED()                      (g_stTMDSRx0CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX0_HPD_TRIGGER_EVENT()                (g_stTMDSRx0CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX0_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx0CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX0_HPD_TRIGGER_EVENT()                (g_stTMDSRx0CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#if(_D0_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx0CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx0CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx0CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX0_RR_ENABLE()                    (g_stTMDSRx0CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX0_RR_ENABLE()                    (g_stTMDSRx0CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX0_RR_ENABLE()                    (g_stTMDSRx0CtrlInfo.b1HDMI2RREnable = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 High Speed Mode
//--------------------------------------------------
#define GET_TMDS_RX0_HIGH_SPEED_MODE()                  (g_stTMDSRx0CtrlInfo.b1HDMI2HighSpeedMode)
#define SET_TMDS_RX0_HIGH_SPEED_MODE()                  (g_stTMDSRx0CtrlInfo.b1HDMI2HighSpeedMode = _TRUE)
#define CLR_TMDS_RX0_HIGH_SPEED_MODE()                  (g_stTMDSRx0CtrlInfo.b1HDMI2HighSpeedMode = _FALSE)
#endif

#define GET_TMDS_RX0_DDC_DETECTED()                     (g_stTMDSRx0CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX0_DDC_DETECTED()                     (g_stTMDSRx0CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX0_DDC_DETECTED()                     (g_stTMDSRx0CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#define GET_TMDS_RX0_CLK_MODE()                         (g_ucTMDSRx0ClkMode)
#define SET_TMDS_RX0_CLK_MODE(x)                        (g_ucTMDSRx0ClkMode = (x))
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX0_TOGGLE_Z0()                        (g_bTMDSRx0Z0Toggle)
#define SET_TMDS_RX0_TOGGLE_Z0()                        (g_bTMDSRx0Z0Toggle = _TRUE)
#define CLR_TMDS_RX0_TOGGLE_Z0()                        (g_bTMDSRx0Z0Toggle = _FALSE)

#define GET_TMDS_RX0_TOGGLE_Z0_EVENT()                  (g_bTMDSRx0GlobalZ0Toggle)
#define SET_TMDS_RX0_TOGGLE_Z0_EVENT()                  (g_bTMDSRx0GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX0_TOGGLE_Z0_EVENT()                  (g_bTMDSRx0GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_RX0_FORCE_BCKGRD_PATH()                (g_enumTMDSRx0IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_TMDS_RX0_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx0IrqForceBackgrd |= (x))
#define CLR_TMDS_RX0_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx0IrqForceBackgrd &= ~(x))

#if(_D0_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX0_AVI_PIXEL_REPETITION()             (g_ucTMDSRx0AviInfo)
#define SET_TMDS_RX0_AVI_PIXEL_REPETITION(x)            (g_ucTMDSRx0AviInfo = (x))
#define CLR_TMDS_RX0_AVI_PIXEL_REPETITION()             (g_ucTMDSRx0AviInfo = 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx0CtrlInfo;
extern WORD g_usTMDSRx0ClkCount;

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
extern BYTE g_ucTMDSRx0ClkMode;
#endif

extern EnumDisplayDataPath g_enumTMDSRx0IrqForceBackgrd;

#if(_D0_HDMI_SUPPORT == _ON)
extern BYTE g_ucTMDSRx0AviInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_D0_HDMI_SUPPORT == _ON)
extern void ScalerTMDSRx0HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx0HdmiPacketDetectEvent(void);
extern BYTE ScalerTMDSRx0HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern void ScalerTMDSRx0HdmiAVMuteProc(void);
extern void ScalerTMDSRx0HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern BYTE ScalerTMDSRx0HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

extern void ScalerTMDSRx0PowerSavingProc(void);
extern void ScalerTMDSRx0PowerOffProc(void);
extern void ScalerTMDSRx0FreqDetectDisable(void);
extern void ScalerTMDSRx0FirstActiveProc(BYTE ucSourceType);
extern bit ScalerTMDSRx0HdcpEnabled(void);
extern BYTE ScalerTMDSRx0TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx0TMDSVideoDetectEvent(void);
extern void ScalerTMDSRx0HotPlugEvent(void);

#endif // End of #if(_D0_TMDS_SUPPORT == _ON)


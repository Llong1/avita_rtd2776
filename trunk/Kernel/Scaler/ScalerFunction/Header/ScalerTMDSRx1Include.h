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
// ID Code      : ScalerTMDSRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D1_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX1_PHY_SET()                          (g_stTMDSRx1CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX1_PHY_SET()                          (g_stTMDSRx1CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX1_PHY_SET()                          (g_stTMDSRx1CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX1_RGBHV_DETECTING()                  (g_stTMDSRx1CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX1_RGBHV_DETECTING()                  (g_stTMDSRx1CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX1_RGBHV_DETECTING()                  (g_stTMDSRx1CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX1_PACKET_DETECTING()                 (g_stTMDSRx1CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX1_PACKET_DETECTING()                 (g_stTMDSRx1CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX1_PACKET_DETECTING()                 (g_stTMDSRx1CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx1CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx1CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX1_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx1CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX1_GCP_RECEIVED()                     (g_stTMDSRx1CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX1_GCP_RECEIVED()                     (g_stTMDSRx1CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX1_GCP_RECEIVED()                     (g_stTMDSRx1CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX1_Z0_ASSERTED()                      (g_stTMDSRx1CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX1_Z0_ASSERTED()                      (g_stTMDSRx1CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX1_Z0_ASSERTED()                      (g_stTMDSRx1CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX1_HPD_TRIGGER_EVENT()                (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX1_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX1_HPD_TRIGGER_EVENT()                (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#if(_D1_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx1CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx1CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx1CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX1_RR_ENABLE()                    (g_stTMDSRx1CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX1_RR_ENABLE()                    (g_stTMDSRx1CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX1_RR_ENABLE()                    (g_stTMDSRx1CtrlInfo.b1HDMI2RREnable = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 High Speed Mode
//--------------------------------------------------
#define GET_TMDS_RX1_HIGH_SPEED_MODE()                  (g_stTMDSRx1CtrlInfo.b1HDMI2HighSpeedMode)
#define SET_TMDS_RX1_HIGH_SPEED_MODE()                  (g_stTMDSRx1CtrlInfo.b1HDMI2HighSpeedMode = _TRUE)
#define CLR_TMDS_RX1_HIGH_SPEED_MODE()                  (g_stTMDSRx1CtrlInfo.b1HDMI2HighSpeedMode = _FALSE)
#endif

#define GET_TMDS_RX1_DDC_DETECTED()                     (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX1_DDC_DETECTED()                     (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX1_DDC_DETECTED()                     (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define GET_TMDS_RX1_CLK_MODE()                         (g_ucTMDSRx1ClkMode)
#define SET_TMDS_RX1_CLK_MODE(x)                        (g_ucTMDSRx1ClkMode = (x))
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX1_TOGGLE_Z0()                        (g_bTMDSRx1Z0Toggle)
#define SET_TMDS_RX1_TOGGLE_Z0()                        (g_bTMDSRx1Z0Toggle = _TRUE)
#define CLR_TMDS_RX1_TOGGLE_Z0()                        (g_bTMDSRx1Z0Toggle = _FALSE)

#define GET_TMDS_RX1_TOGGLE_Z0_EVENT()                  (g_bTMDSRx1GlobalZ0Toggle)
#define SET_TMDS_RX1_TOGGLE_Z0_EVENT()                  (g_bTMDSRx1GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX1_TOGGLE_Z0_EVENT()                  (g_bTMDSRx1GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_RX1_FORCE_BCKGRD_PATH()                (g_enumTMDSRx1IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_TMDS_RX1_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx1IrqForceBackgrd |= (x))
#define CLR_TMDS_RX1_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx1IrqForceBackgrd &= ~(x))

#if(_D1_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX1_AVI_PIXEL_REPETITION()             (g_ucTMDSRx1AviInfo)
#define SET_TMDS_RX1_AVI_PIXEL_REPETITION(x)            (g_ucTMDSRx1AviInfo = (x))
#define CLR_TMDS_RX1_AVI_PIXEL_REPETITION()             (g_ucTMDSRx1AviInfo = 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx1CtrlInfo;
extern WORD g_usTMDSRx1ClkCount;

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
extern BYTE g_ucTMDSRx1ClkMode;
#endif

extern EnumDisplayDataPath g_enumTMDSRx1IrqForceBackgrd;

#if(_D1_HDMI_SUPPORT == _ON)
extern BYTE g_ucTMDSRx1AviInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_D1_HDMI_SUPPORT == _ON)
extern void ScalerTMDSRx1HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx1HdmiPacketDetectEvent(void);
extern BYTE ScalerTMDSRx1HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern void ScalerTMDSRx1HdmiAVMuteProc(void);
extern void ScalerTMDSRx1HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern BYTE ScalerTMDSRx1HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

extern void ScalerTMDSRx1PowerSavingProc(void);
extern void ScalerTMDSRx1PowerOffProc(void);
extern void ScalerTMDSRx1FreqDetectDisable(void);
extern void ScalerTMDSRx1FirstActiveProc(BYTE ucSourceType);
extern bit ScalerTMDSRx1HdcpEnabled(void);
extern BYTE ScalerTMDSRx1TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx1TMDSVideoDetectEvent(void);
extern void ScalerTMDSRx1HotPlugEvent(void);

#endif // End of #if(_D1_TMDS_SUPPORT == _ON)


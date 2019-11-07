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
// ID Code      : ScalerTMDSRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D4_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX4_PHY_SET()                          (g_stTMDSRx4CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX4_PHY_SET()                          (g_stTMDSRx4CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX4_PHY_SET()                          (g_stTMDSRx4CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX4_RGBHV_DETECTING()                  (g_stTMDSRx4CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX4_RGBHV_DETECTING()                  (g_stTMDSRx4CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX4_RGBHV_DETECTING()                  (g_stTMDSRx4CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX4_PACKET_DETECTING()                 (g_stTMDSRx4CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX4_PACKET_DETECTING()                 (g_stTMDSRx4CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX4_PACKET_DETECTING()                 (g_stTMDSRx4CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx4CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx4CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx4CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX4_GCP_RECEIVED()                     (g_stTMDSRx4CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX4_GCP_RECEIVED()                     (g_stTMDSRx4CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX4_GCP_RECEIVED()                     (g_stTMDSRx4CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX4_Z0_ASSERTED()                      (g_stTMDSRx4CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX4_Z0_ASSERTED()                      (g_stTMDSRx4CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX4_Z0_ASSERTED()                      (g_stTMDSRx4CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX4_HPD_TRIGGER_EVENT()                (g_stTMDSRx4CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX4_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx4CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX4_HPD_TRIGGER_EVENT()                (g_stTMDSRx4CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX4_DDC_DETECTED()                     (g_stTMDSRx4CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX4_DDC_DETECTED()                     (g_stTMDSRx4CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX4_DDC_DETECTED()                     (g_stTMDSRx4CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define GET_TMDS_RX4_CLK_MODE()                         (g_ucTMDSRx4ClkMode)
#define SET_TMDS_RX4_CLK_MODE(x)                        (g_ucTMDSRx4ClkMode = (x))
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX4_TOGGLE_Z0()                        (g_bTMDSRx4Z0Toggle)
#define SET_TMDS_RX4_TOGGLE_Z0()                        (g_bTMDSRx4Z0Toggle = _TRUE)
#define CLR_TMDS_RX4_TOGGLE_Z0()                        (g_bTMDSRx4Z0Toggle = _FALSE)

#define GET_TMDS_RX4_TOGGLE_Z0_EVENT()                  (g_bTMDSRx4GlobalZ0Toggle)
#define SET_TMDS_RX4_TOGGLE_Z0_EVENT()                  (g_bTMDSRx4GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX4_TOGGLE_Z0_EVENT()                  (g_bTMDSRx4GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_RX4_FORCE_BCKGRD_PATH()                (g_enumTMDSRx4IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_TMDS_RX4_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx4IrqForceBackgrd |= (x))
#define CLR_TMDS_RX4_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx4IrqForceBackgrd &= ~(x))

#if(_D4_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX4_AVI_PIXEL_REPETITION()             (g_ucTMDSRx4AviInfo)
#define SET_TMDS_RX4_AVI_PIXEL_REPETITION(x)            (g_ucTMDSRx4AviInfo = (x))
#define CLR_TMDS_RX4_AVI_PIXEL_REPETITION()             (g_ucTMDSRx4AviInfo = 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx4CtrlInfo;
extern WORD g_usTMDSRx4ClkCount;

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
extern BYTE g_ucTMDSRx4ClkMode;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
extern BYTE g_ucTMDSRx4AviInfo;
#endif

extern EnumDisplayDataPath g_enumTMDSRx4IrqForceBackgrd;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx4DviVideoSetting(void);
extern void ScalerTMDSRx4SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D4_HDMI_SUPPORT == _ON)

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern bit ScalerTMDSRx4HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

extern void ScalerTMDSRx4HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx4HdmiPacketDetectEvent(void);
extern BYTE ScalerTMDSRx4HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern bit ScalerTMDSRx4HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx4HdmiGetColorDepth(void);
extern void ScalerTMDSRx4HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern BYTE ScalerTMDSRx4HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

extern void ScalerTMDSRx4PowerOffProc(void);
extern void ScalerTMDSRx4FreqDetectDisable(void);
extern void ScalerTMDSRx4FirstActiveProc(BYTE ucSourceType);

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern bit ScalerTMDSRx4HdcpEnabled(void);
#endif

extern BYTE ScalerTMDSRx4TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx4TMDSVideoDetectEvent(void);

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
extern void ScalerTMDSRx4DualDVISwitch(bit bEnable);
#endif

extern bit ScalerTMDSRx4CheckCDRStable(WORD usClkCount);
extern BYTE ScalerTMDSRx4CheckCDRStable_EXINT0(WORD usClkCount);
extern void ScalerTMDSRx4Initial(BYTE ucInputPort);
extern void ScalerTMDSRx4PowerSavingProc(void);

#if(_D4_HDMI_SUPPORT == _ON)
extern void ScalerTMDSRx4HdmiAVMuteProc(void);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern BYTE ScalerTMDSRx4FormatDetect(void);
#endif

#endif // End of #if(_D4_TMDS_SUPPORT == _ON)

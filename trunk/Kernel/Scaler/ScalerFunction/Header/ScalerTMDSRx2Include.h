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
// ID Code      : ScalerTMDSRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D2_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX2_PHY_SET()                          (g_stTMDSRx2CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX2_PHY_SET()                          (g_stTMDSRx2CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX2_PHY_SET()                          (g_stTMDSRx2CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX2_RGBHV_DETECTING()                  (g_stTMDSRx2CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX2_RGBHV_DETECTING()                  (g_stTMDSRx2CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX2_RGBHV_DETECTING()                  (g_stTMDSRx2CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX2_PACKET_DETECTING()                 (g_stTMDSRx2CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX2_PACKET_DETECTING()                 (g_stTMDSRx2CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX2_PACKET_DETECTING()                 (g_stTMDSRx2CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX2_GCP_RECEIVED()                     (g_stTMDSRx2CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX2_GCP_RECEIVED()                     (g_stTMDSRx2CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX2_GCP_RECEIVED()                     (g_stTMDSRx2CtrlInfo.b1GCPReceived = _FALSE)

#if(_ULTRA_HDR_SUPPORT == _ON)
#define GET_HDMI_RX2_HDR_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1HDRInfoFrameReceived)
#define SET_HDMI_RX2_HDR_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX2_HDR_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX2_Z0_ASSERTED()                      (g_stTMDSRx2CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX2_Z0_ASSERTED()                      (g_stTMDSRx2CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX2_Z0_ASSERTED()                      (g_stTMDSRx2CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX2_HPD_TRIGGER_EVENT()                (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX2_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX2_HPD_TRIGGER_EVENT()                (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX2_DDC_DETECTED()                     (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX2_DDC_DETECTED()                     (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX2_DDC_DETECTED()                     (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define GET_TMDS_RX2_CLK_MODE()                         (g_ucTMDSRx2ClkMode)
#define SET_TMDS_RX2_CLK_MODE(x)                        (g_ucTMDSRx2ClkMode = (x))
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX2_TOGGLE_Z0()                        (g_bTMDSRx2Z0Toggle)
#define SET_TMDS_RX2_TOGGLE_Z0()                        (g_bTMDSRx2Z0Toggle = _TRUE)
#define CLR_TMDS_RX2_TOGGLE_Z0()                        (g_bTMDSRx2Z0Toggle = _FALSE)

#define GET_TMDS_RX2_TOGGLE_Z0_EVENT()                  (g_bTMDSRx2GlobalZ0Toggle)
#define SET_TMDS_RX2_TOGGLE_Z0_EVENT()                  (g_bTMDSRx2GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX2_TOGGLE_Z0_EVENT()                  (g_bTMDSRx2GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_RX2_FORCE_BCKGRD_PATH()                (g_enumTMDSRx2IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_TMDS_RX2_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx2IrqForceBackgrd |= (x))
#define CLR_TMDS_RX2_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx2IrqForceBackgrd &= ~(x))

#if(_D2_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX2_AVI_PIXEL_REPETITION()             (g_ucTMDSRx2AviInfo)
#define SET_TMDS_RX2_AVI_PIXEL_REPETITION(x)            (g_ucTMDSRx2AviInfo = (x))
#define CLR_TMDS_RX2_AVI_PIXEL_REPETITION()             (g_ucTMDSRx2AviInfo = 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx2CtrlInfo;
extern WORD g_usTMDSRx2ClkCount;

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
extern BYTE g_ucTMDSRx2ClkMode;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
extern BYTE g_ucTMDSRx2AviInfo;
#endif

extern EnumDisplayDataPath g_enumTMDSRx2IrqForceBackgrd;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx2DviVideoSetting(void);
extern void ScalerTMDSRx2SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D2_HDMI_SUPPORT == _ON)

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern bit ScalerTMDSRx2HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

extern void ScalerTMDSRx2HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx2HdmiPacketDetectEvent(void);
extern BYTE ScalerTMDSRx2HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern bit ScalerTMDSRx2HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx2HdmiGetColorDepth(void);
extern void ScalerTMDSRx2HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern BYTE ScalerTMDSRx2HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerTMDSRx2GetHDRData(BYTE *pucHDRData);
#endif
#endif

extern void ScalerTMDSRx2PowerOffProc(void);
extern void ScalerTMDSRx2FreqDetectDisable(void);
extern void ScalerTMDSRx2FirstActiveProc(BYTE ucSourceType);

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern bit ScalerTMDSRx2HdcpEnabled(void);
#endif

extern BYTE ScalerTMDSRx2TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx2TMDSVideoDetectEvent(void);

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
extern void ScalerTMDSRx2DualDVISwitch(bit bEnable);
#endif

extern bit ScalerTMDSRx2CheckCDRStable(WORD usClkCount);

extern BYTE ScalerTMDSRx2CheckCDRStable_EXINT0(WORD usClkCount);

#if(_D2_HDMI_SUPPORT == _ON)
extern void ScalerTMDSRx2HdmiAVMuteProc(void);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern BYTE ScalerTMDSRx2FormatDetect(void);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
extern bit ScalerTMDSRx2GetDualDVIMode(void);
extern BYTE ScalerTMDSRx2GetDualDVIMode_EXINT0(void);
#endif

#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

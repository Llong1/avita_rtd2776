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
// ID Code      : ScalerTMDSRx5Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D5_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX5_PHY_SET()                          (g_stTMDSRx5CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX5_PHY_SET()                          (g_stTMDSRx5CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX5_PHY_SET()                          (g_stTMDSRx5CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX5_RGBHV_DETECTING()                  (g_stTMDSRx5CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX5_RGBHV_DETECTING()                  (g_stTMDSRx5CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX5_RGBHV_DETECTING()                  (g_stTMDSRx5CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX5_PACKET_DETECTING()                 (g_stTMDSRx5CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX5_PACKET_DETECTING()                 (g_stTMDSRx5CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX5_PACKET_DETECTING()                 (g_stTMDSRx5CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx5CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx5CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx5CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX5_GCP_RECEIVED()                     (g_stTMDSRx5CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX5_GCP_RECEIVED()                     (g_stTMDSRx5CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX5_GCP_RECEIVED()                     (g_stTMDSRx5CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX5_Z0_ASSERTED()                      (g_stTMDSRx5CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX5_Z0_ASSERTED()                      (g_stTMDSRx5CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX5_Z0_ASSERTED()                      (g_stTMDSRx5CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX5_HPD_TRIGGER_EVENT()                (g_stTMDSRx5CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX5_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx5CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX5_HPD_TRIGGER_EVENT()                (g_stTMDSRx5CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX5_DDC_DETECTED()                     (g_stTMDSRx5CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX5_DDC_DETECTED()                     (g_stTMDSRx5CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX5_DDC_DETECTED()                     (g_stTMDSRx5CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#define GET_TMDS_RX5_CLK_MODE()                         (g_ucTMDSRx5ClkMode)
#define SET_TMDS_RX5_CLK_MODE(x)                        (g_ucTMDSRx5ClkMode = (x))
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX5_TOGGLE_Z0()                        (g_bTMDSRx5Z0Toggle)
#define SET_TMDS_RX5_TOGGLE_Z0()                        (g_bTMDSRx5Z0Toggle = _TRUE)
#define CLR_TMDS_RX5_TOGGLE_Z0()                        (g_bTMDSRx5Z0Toggle = _FALSE)

#define GET_TMDS_RX5_TOGGLE_Z0_EVENT()                  (g_bTMDSRx5GlobalZ0Toggle)
#define SET_TMDS_RX5_TOGGLE_Z0_EVENT()                  (g_bTMDSRx5GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX5_TOGGLE_Z0_EVENT()                  (g_bTMDSRx5GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_RX5_FORCE_BCKGRD_PATH()                (g_enumTMDSRx5IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_TMDS_RX5_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx5IrqForceBackgrd |= (x))
#define CLR_TMDS_RX5_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx5IrqForceBackgrd &= ~(x))

#if(_D5_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX5_AVI_PIXEL_REPETITION()             (g_ucTMDSRx5AviInfo)
#define SET_TMDS_RX5_AVI_PIXEL_REPETITION(x)            (g_ucTMDSRx5AviInfo = (x))
#define CLR_TMDS_RX5_AVI_PIXEL_REPETITION()             (g_ucTMDSRx5AviInfo = 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx5CtrlInfo;
extern WORD g_usTMDSRx5ClkCount;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
extern BYTE g_ucTMDSRx5ClkMode;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
extern BYTE g_ucTMDSRx5AviInfo;
#endif

extern EnumDisplayDataPath g_enumTMDSRx5IrqForceBackgrd;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx5DviVideoSetting(void);
extern void ScalerTMDSRx5SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D5_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx5HdmiDeepColorProc(WORD usTmdsClkCnt);
extern void ScalerTMDSRx5HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx5HdmiPacketDetectEvent(void);
extern BYTE ScalerTMDSRx5HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern bit ScalerTMDSRx5HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx5HdmiGetColorDepth(void);
extern void ScalerTMDSRx5HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern BYTE ScalerTMDSRx5HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

extern void ScalerTMDSRx5PowerOffProc(void);
extern void ScalerTMDSRx5FreqDetectDisable(void);
extern void ScalerTMDSRx5FirstActiveProc(BYTE ucSourceType);
extern bit ScalerTMDSRx5HdcpEnabled(void);
extern BYTE ScalerTMDSRx5TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx5TMDSVideoDetectEvent(void);

extern bit ScalerTMDSRx5CheckCDRStable(WORD usClkCount);
extern BYTE ScalerTMDSRx5CheckCDRStable_EXINT0(WORD usClkCount);
extern void ScalerTMDSRx5Initial(BYTE ucInputPort);
extern void ScalerTMDSRx5PowerSavingProc(void);

#if(_D5_HDMI_SUPPORT == _ON)
extern void ScalerTMDSRx5HdmiAVMuteProc(void);
#endif

extern BYTE ScalerTMDSRx5FormatDetect(void);

#endif // End of #if(_D5_TMDS_SUPPORT == _ON)

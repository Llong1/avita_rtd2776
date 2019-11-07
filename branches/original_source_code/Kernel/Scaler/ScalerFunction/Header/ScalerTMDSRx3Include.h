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
// ID Code      : ScalerTMDSRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D3_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX3_PHY_SET()                          (g_stTMDSRx3CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX3_PHY_SET()                          (g_stTMDSRx3CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX3_PHY_SET()                          (g_stTMDSRx3CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX3_RGBHV_DETECTING()                  (g_stTMDSRx3CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX3_RGBHV_DETECTING()                  (g_stTMDSRx3CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX3_RGBHV_DETECTING()                  (g_stTMDSRx3CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX3_PACKET_DETECTING()                 (g_stTMDSRx3CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX3_PACKET_DETECTING()                 (g_stTMDSRx3CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX3_PACKET_DETECTING()                 (g_stTMDSRx3CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX3_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx3CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX3_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx3CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX3_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx3CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX3_GCP_RECEIVED()                     (g_stTMDSRx3CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX3_GCP_RECEIVED()                     (g_stTMDSRx3CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX3_GCP_RECEIVED()                     (g_stTMDSRx3CtrlInfo.b1GCPReceived = _FALSE)

#if(_ULTRA_HDR_SUPPORT == _ON)
#define GET_HDMI_RX3_HDR_INFO_FRAME_RECEIVED()          (g_stTMDSRx3CtrlInfo.b1HDRInfoFrameReceived)
#define SET_HDMI_RX3_HDR_INFO_FRAME_RECEIVED()          (g_stTMDSRx3CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX3_HDR_INFO_FRAME_RECEIVED()          (g_stTMDSRx3CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX3_Z0_ASSERTED()                      (g_stTMDSRx3CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX3_Z0_ASSERTED()                      (g_stTMDSRx3CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX3_Z0_ASSERTED()                      (g_stTMDSRx3CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX3_HPD_TRIGGER_EVENT()                (g_stTMDSRx3CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX3_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx3CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX3_HPD_TRIGGER_EVENT()                (g_stTMDSRx3CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX3_DDC_DETECTED()                     (g_stTMDSRx3CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX3_DDC_DETECTED()                     (g_stTMDSRx3CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX3_DDC_DETECTED()                     (g_stTMDSRx3CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#define GET_TMDS_RX3_CLK_MODE()                         (g_ucTMDSRx3ClkMode)
#define SET_TMDS_RX3_CLK_MODE(x)                        (g_ucTMDSRx3ClkMode = (x))
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX3_TOGGLE_Z0()                        (g_bTMDSRx3Z0Toggle)
#define SET_TMDS_RX3_TOGGLE_Z0()                        (g_bTMDSRx3Z0Toggle = _TRUE)
#define CLR_TMDS_RX3_TOGGLE_Z0()                        (g_bTMDSRx3Z0Toggle = _FALSE)

#define GET_TMDS_RX3_TOGGLE_Z0_EVENT()                  (g_bTMDSRx3GlobalZ0Toggle)
#define SET_TMDS_RX3_TOGGLE_Z0_EVENT()                  (g_bTMDSRx3GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX3_TOGGLE_Z0_EVENT()                  (g_bTMDSRx3GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_RX3_FORCE_BCKGRD_PATH()                (g_enumTMDSRx3IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_TMDS_RX3_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx3IrqForceBackgrd |= (x))
#define CLR_TMDS_RX3_FORCE_BCKGRD_PATH(x)               (g_enumTMDSRx3IrqForceBackgrd &= ~(x))

#if(_D3_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX3_AVI_PIXEL_REPETITION()             (g_ucTMDSRx3AviInfo)
#define SET_TMDS_RX3_AVI_PIXEL_REPETITION(x)            (g_ucTMDSRx3AviInfo = (x))
#define CLR_TMDS_RX3_AVI_PIXEL_REPETITION()             (g_ucTMDSRx3AviInfo = 0)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx3CtrlInfo;
extern WORD g_usTMDSRx3ClkCount;

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
extern BYTE g_ucTMDSRx3ClkMode;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
extern BYTE g_ucTMDSRx3AviInfo;
#endif

extern EnumDisplayDataPath g_enumTMDSRx3IrqForceBackgrd;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx3DviVideoSetting(void);
extern void ScalerTMDSRx3SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D3_HDMI_SUPPORT == _ON)

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
extern bit ScalerTMDSRx3HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

extern void ScalerTMDSRx3HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx3HdmiPacketDetectEvent(void);
extern BYTE ScalerTMDSRx3HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern bit ScalerTMDSRx3HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx3HdmiGetColorDepth(void);
extern void ScalerTMDSRx3HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern BYTE ScalerTMDSRx3HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerTMDSRx3GetHDRData(BYTE *pucHDRData);
#endif
#endif

extern void ScalerTMDSRx3PowerOffProc(void);
extern void ScalerTMDSRx3FreqDetectDisable(void);
extern void ScalerTMDSRx3FirstActiveProc(BYTE ucSourceType);

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
extern bit ScalerTMDSRx3HdcpEnabled(void);
#endif

extern BYTE ScalerTMDSRx3TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx3TMDSVideoDetectEvent(void);

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
extern void ScalerTMDSRx3DualDVISwitch(bit bEnable);
#endif

extern bit ScalerTMDSRx3CheckCDRStable(WORD usClkCount);

extern BYTE ScalerTMDSRx3CheckCDRStable_EXINT0(WORD usClkCount);

#if(_D3_HDMI_SUPPORT == _ON)
extern void ScalerTMDSRx3HdmiAVMuteProc(void);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
extern BYTE ScalerTMDSRx3FormatDetect(void);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
extern bit ScalerTMDSRx3GetDualDVIMode(void);
extern BYTE ScalerTMDSRx3GetDualDVIMode_EXINT0(void);
#endif

#endif // End of #if(_D3_TMDS_SUPPORT == _ON)

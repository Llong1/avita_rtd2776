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
// ID Code      : ScalerDPRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_RX0_PCB_LANE0_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane0Mapping)
#define SET_DP_RX0_PCB_LANE0_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_RX0_PCB_LANE1_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane1Mapping)
#define SET_DP_RX0_PCB_LANE1_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_RX0_PCB_LANE2_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane2Mapping)
#define SET_DP_RX0_PCB_LANE2_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_RX0_PCB_LANE3_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane3Mapping)
#define SET_DP_RX0_PCB_LANE3_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_RX0_PCB_PN_SWAP()                        (g_stDpRx0LanesMapping.b1PNSwap)
#define SET_DP_RX0_PCB_PN_SWAP(x)                       (g_stDpRx0LanesMapping.b1PNSwap = (x))

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _D0_DP_LANE0                                    (GET_DP_RX0_PCB_LANE0_MAPPING())
#define _D0_DP_LANE1                                    (GET_DP_RX0_PCB_LANE1_MAPPING())
#define _D0_DP_LANE2                                    (GET_DP_RX0_PCB_LANE2_MAPPING())
#define _D0_DP_LANE3                                    (GET_DP_RX0_PCB_LANE3_MAPPING())

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_FAKE_LINK_TRAINING()                 ((g_ucDpRx0Info & _BIT7) >> 7)
#define SET_DP_RX0_FAKE_LINK_TRAINING()                 (g_ucDpRx0Info |= _BIT7)
#define CLR_DP_RX0_FAKE_LINK_TRAINING()                 (g_ucDpRx0Info &= ~_BIT7)

#define GET_DP_RX0_VALID_VIDEO_CHECK()                  ((g_ucDpRx0Info & _BIT6) >> 6)
#define SET_DP_RX0_VALID_VIDEO_CHECK()                  (g_ucDpRx0Info |= _BIT6)
#define CLR_DP_RX0_VALID_VIDEO_CHECK()                  (g_ucDpRx0Info &= ~_BIT6)

#define GET_DP_RX0_CRC_CALCULATE()                      ((g_ucDpRx0Info & _BIT5) >> 5)
#define SET_DP_RX0_CRC_CALCULATE()                      (g_ucDpRx0Info |= _BIT5)
#define CLR_DP_RX0_CRC_CALCULATE()                      (g_ucDpRx0Info &= ~_BIT5)

#define GET_DP_RX0_PS_AUX_TOGGLE()                      (g_bDpRx0PSAuxToggle)
#define SET_DP_RX0_PS_AUX_TOGGLE()                      (g_bDpRx0PSAuxToggle = _TRUE)
#define CLR_DP_RX0_PS_AUX_TOGGLE()                      (g_bDpRx0PSAuxToggle = _FALSE)

// Add for DPCD 2002h Bug
#define GET_DP_RX0_POWER_STATE_INTO_PS()                (g_bDpRx0PowerStateIntoPS)
#define SET_DP_RX0_POWER_STATE_INTO_PS()                (g_bDpRx0PowerStateIntoPS = _TRUE)
#define CLR_DP_RX0_POWER_STATE_INTO_PS()                (g_bDpRx0PowerStateIntoPS = _FALSE)

#define GET_DP_RX0_AUX_COMMAND_NO_REPLY()               (g_bDpRx0AuxCommandNoReply)
#define SET_DP_RX0_AUX_COMMAND_NO_REPLY()               (g_bDpRx0AuxCommandNoReply = _TRUE)
#define CLR_DP_RX0_AUX_COMMAND_NO_REPLY()               (g_bDpRx0AuxCommandNoReply = _FALSE)

#define GET_DP_RX0_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx0MSAFailMacRsetCount)
#define ADD_DP_RX0_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx0MSAFailMacRsetCount++)
#define CLR_DP_RX0_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx0MSAFailMacRsetCount = 0)

#define GET_DP_RX0_FORCE_BCKGRD_PATH()                  (g_enumDPRx0IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_DP_RX0_FORCE_BCKGRD_PATH(x)                 (g_enumDPRx0IrqForceBackgrd |= (x))
#define CLR_DP_RX0_FORCE_BCKGRD_PATH(x)                 (g_enumDPRx0IrqForceBackgrd &= ~(x))

#if(_DP_MST_SUPPORT == _ON)
#define GET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx0MiscInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx0MiscInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx0MiscInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_RX0_CHECK_AUX_CH_POWER_OFF()             (g_stDpRx0MiscInfo.b1DpCheckAuxChPowerOff)
#define SET_DP_RX0_CHECK_AUX_CH_POWER_OFF()             (g_stDpRx0MiscInfo.b1DpCheckAuxChPowerOff = _TRUE)
#define CLR_DP_RX0_CHECK_AUX_CH_POWER_OFF()             (g_stDpRx0MiscInfo.b1DpCheckAuxChPowerOff = _FALSE)

#define GET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx0MiscInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx0MiscInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_RX0_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx0MiscInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_RX0_SOURCE_FIRST_POWER_ON()              (g_stDpRx0MiscInfo.b1DpSourceFirstPowerOn)
#define SET_DP_RX0_SOURCE_FIRST_POWER_ON()              (g_stDpRx0MiscInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_RX0_SOURCE_FIRST_POWER_ON()              (g_stDpRx0MiscInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_RX0_BACKUP_PD_LINK_STATUS_FLG()          (g_bDpMSTRx0BackupLinkStatusFlg_INT)
#define SET_DP_RX0_BACKUP_PD_LINK_STATUS_FLG()          (g_bDpMSTRx0BackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG()          (g_bDpMSTRx0BackupLinkStatusFlg_INT = _FALSE)
#endif // #if(_DP_MST_SUPPORT == _ON)

#define SET_DP_RX0_AUX_MANUAL_MODE_EXINT()              {\
                                                            for(g_ucRx0AuxTemp_EXINT = 0; ((ScalerGetBit_EXINT(PB7_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx0AuxTemp_EXINT < 255)); g_ucRx0AuxTemp_EXINT++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                        }

#define SET_DP_RX0_AUX_MANUAL_MODE()                    {\
                                                            EX0 = 0;\
                                                            for(g_ucRx0AuxTemp = 0; ((ScalerGetBit(PB7_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx0AuxTemp < 255)); g_ucRx0AuxTemp++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX0_AUX_AUTO_MODE_EXINT()                {\
                                                            for(g_ucRx0AuxTemp_EXINT = 0; ((ScalerGetBit_EXINT(PB7_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx0AuxTemp_EXINT < 255)); g_ucRx0AuxTemp_EXINT++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                        }

#define SET_DP_RX0_AUX_AUTO_MODE()                      {\
                                                            EX0 = 0;\
                                                            for(g_ucRx0AuxTemp = 0; ((ScalerGetBit(PB7_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx0AuxTemp < 255)); g_ucRx0AuxTemp++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                            EX0 = 1;\
                                                        }

#define GET_DP_RX0_VFRONT_PORCH()                       (g_usDpRx0Vfrontporch)
#define SET_DP_RX0_VFRONT_PORCH(x)                      (g_usDpRx0Vfrontporch = (x))

#define SET_DP_RX0_PORCH_COLOR_RGB()                    {\
                                                            ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x00);\
                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                            ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                            ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x00);\
                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                        }

#define SET_DP_RX0_PORCH_COLOR_YCC_LIMIT(ucInputPort)   {\
                                                            if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x0F);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#define SET_DP_RX0_PORCH_COLOR_YCC_FULL(ucInputPort)    {\
                                                            if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#define GET_DP_RX0_VSC_SDP_COLOR_MODE()                 (g_bDpRx0VscSdpColorMode)
#define SET_DP_RX0_VSC_SDP_COLOR_MODE()                 (g_bDpRx0VscSdpColorMode = _TRUE)
#define CLR_DP_RX0_VSC_SDP_COLOR_MODE()                 (g_bDpRx0VscSdpColorMode = _FALSE)

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#define GET_DP_RX0_RSV1_DETECTING()                     (g_bDpRx0RSV1PacketDetecting)
#define SET_DP_RX0_RSV1_DETECTING()                     (g_bDpRx0RSV1PacketDetecting = _TRUE)
#define CLR_DP_RX0_RSV1_DETECTING()                     (g_bDpRx0RSV1PacketDetecting = _FALSE)

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_RX0_MST2SST_RSV1_DETECTING()             (g_bDpRx0MstToSstRSV1PacketDetecting)
#define SET_DP_RX0_MST2SST_RSV1_DETECTING()             (g_bDpRx0MstToSstRSV1PacketDetecting = _TRUE)
#define CLR_DP_RX0_MST2SST_RSV1_DETECTING()             (g_bDpRx0MstToSstRSV1PacketDetecting = _FALSE)
#endif
#endif
#endif // End of #if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP Authentication
//--------------------------------------------------
#define GET_DP_RX0_HDCP_AUTH_STATE()                    (g_stDpRx0HDCPAuthInfo.b4AuthState)
#define SET_DP_RX0_HDCP_AUTH_STATE(x)                   (g_stDpRx0HDCPAuthInfo.b4AuthState = (x))

#define GET_DP_RX0_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx0HDCPAuthInfo.b1AuthStateChange)
#define SET_DP_RX0_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx0HDCPAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx0HDCPAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx0HDCPAuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx0HDCPAuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx0HDCPAuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx0HDCPAuthInfo.b1AuthReadIrqTimeout)
#define SET_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx0HDCPAuthInfo.b1AuthReadIrqTimeout = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx0HDCPAuthInfo.b1AuthReadIrqTimeout = _FALSE)

#define GET_DP_RX0_HDCP_UPSTREAM_EVENT()                (g_stDpRx0HDCPAuthInfo.ucAuthUpstreamEvent)
#define SET_DP_RX0_HDCP_UPSTREAM_EVENT(x)               (g_stDpRx0HDCPAuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_RX0_HDCP_UPSTREAM_EVENT()                (g_stDpRx0HDCPAuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx0HDCPAuthInfo.b1AuthCpIrqTimer)
#define SET_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx0HDCPAuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx0HDCPAuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_RX0_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx0HdcpAksvWritten)
#define SET_DP_RX0_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx0HdcpAksvWritten = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx0HdcpAksvWritten = _FALSE)

#define GET_DP_RX0_HDCP_REPEATER_SUPPORT()              ((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))

#define GET_DP_RX0_MST_TO_SST_VFRONT_PORCH()            (g_usDpRx0MstToSstVfrontporch)
#define SET_DP_RX0_MST_TO_SST_VFRONT_PORCH(x)           (g_usDpRx0MstToSstVfrontporch = (x))

#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#define GET_DP_RX0_RSV0_DETECTING()                     (g_stDPRx0InfoFrameRSV0Ctrl.b1RSV0PacketDetecting)
#define SET_DP_RX0_RSV0_DETECTING()                     (g_stDPRx0InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _TRUE)
#define CLR_DP_RX0_RSV0_DETECTING()                     (g_stDPRx0InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _FALSE)

#define GET_DP_RX0_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx0InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive)
#define SET_DP_RX0_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx0InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _TRUE)
#define CLR_DP_RX0_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx0InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _FALSE)

#define GET_DP_RX0_FREESYNC_INFO_FRAME_RECEIVED()       (g_stDPRx0InfoFrameRSV0Ctrl.b1FreesyncInfoFrameReceive)
#define SET_DP_RX0_FREESYNC_INFO_FRAME_RECEIVED()       (g_stDPRx0InfoFrameRSV0Ctrl.b1FreesyncInfoFrameReceive = _TRUE)
#define CLR_DP_RX0_FREESYNC_INFO_FRAME_RECEIVED()       (g_stDPRx0InfoFrameRSV0Ctrl.b1FreesyncInfoFrameReceive = _FALSE)

#define GET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx0InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive)
#define SET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx0InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _TRUE)
#define CLR_DP_RX0_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx0InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpRx0PSAuxToggle;

// Add for DPCD 2002h Bug
extern bit g_bDpRx0PowerStateIntoPS;
extern bit g_bDpRx0AuxCommandNoReply;

extern BYTE g_ucDpRx0Info;
extern BYTE g_ucDpRx0LinkRate;
extern BYTE g_ucDpRx0LaneCount;
extern BYTE g_ucDpRx0TrainingPatternSet;
extern BYTE g_ucRx0AuxTemp;
extern BYTE g_ucRx0AuxTemp_EXINT;
extern WORD g_usDpRx0Vfrontporch;

extern EnumDisplayDataPath g_enumDPRx0IrqForceBackgrd;
extern StructDpLanesMapping g_stDpRx0LanesMapping;

#if(_DP_MST_SUPPORT == _ON)
extern StructDPRxMiscInfo g_stDpRx0MiscInfo;
extern bit g_bDpMSTRx0BackupLinkStatusFlg_INT;
extern BYTE g_pucDpRx0LinkStatusBackup_INT[2];
#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit g_bDpRx0HdcpAksvWritten;
extern StructDPRxHDCPAuthInfo g_stDpRx0HDCPAuthInfo;
extern WORD g_usDpRx0MstToSstVfrontporch;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucDPRx0Caps[3];
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit g_bDpRx0VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern bit g_bDpRx0RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit g_bDpRx0MstToSstRSV1PacketDetecting;
#endif
#endif

#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern BYTE g_pucDPRx0HDRBackup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern BYTE g_pucDPRx0RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern StructDPInfoFrameRSV0Ctrl g_stDPRx0InfoFrameRSV0Ctrl;
#endif

extern BYTE g_ucDpRx0Temp;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0SetDpLaneMapping(BYTE ucLanetype);
extern void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx0DpcdLinkStatusReset_WDINT(void);
#endif

extern void ScalerDpRx0HotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
extern bit ScalerDpRx0MarginLinkCheck(void);
extern void ScalerDpRx0LinkStatusIRQ(void);
extern void ScalerDpRx0HotPlugDuration(WORD usMs);
extern void ScalerDpRx0MacInitial(void);
extern void ScalerDpRx0SecDataBlockReset(void);
extern BYTE ScalerDpRx0TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpRx0TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpRx0TrainingPatternEnd_EXINT0(void);
extern bit ScalerDpRx0AlignCheck(void);
extern bit ScalerDpRx0DecodeCheck(void);
extern bit ScalerDpRx0SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern BYTE ScalerDpRx0DFECheck_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern BYTE ScalerDpRx0DFECheck_WDINT(void);
#endif

extern bit ScalerDpRx0MSACheck(void);
extern bit ScalerDpRx0MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit ScalerDpRx0VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx0RSV1PacketDetectEvent(void);
extern void ScalerDpRx0SetInitialRSV1InfoType(void);
#endif
#endif
extern void ScalerDpRx0AVMute(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0UpdateSinkCount(void);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx0WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD ScalerDpRx0GetBStoHSDelay(WORD usDpHtotal);
extern WORD ScalerDpRx0GetVFreq(void);
extern WORD ScalerDpRx0GetVPeriod(void);
extern WORD ScalerDpRx0GetHPeriod(void);
extern WORD ScalerDpRx0GetHSW(void);
extern BYTE ScalerDpRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern BYTE ScalerDpRx0GetAmdSpdBackupInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerDpRx0InfoFrameRSV0Check(void);
extern void ScalerDpRx0RSV0PacketDetectEvent(void);
#endif

extern void ScalerDpRx0SetInitialRSV0InfoType(void);
extern DWORD ScalerDpRx0GetBStoVSDelay(void);
extern bit ScalerDpRx0InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
extern bit ScalerDpRx0GetVideoInfo(void);
extern void ScalerDpRx0SetColorInfo(void);
extern void ScalerDpRx0VideoSetting(void);
extern void ScalerDpRx0ColorimetrySetting(BYTE ucInputPort, BYTE ucColorimetryValue);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern void ScalerDpRx0ColorimetryExtSetting(BYTE ucInputPort, BYTE ucColorimetryValue);
#endif
extern void ScalerDpRx0QuantizationSetting(BYTE ucInputPort, BYTE ucQuantizationValue);

extern bit ScalerDpRx0StreamClkRegenerate(void);
extern void ScalerDpRx0AdjustVsyncDelay(void);
extern void ScalerDpRx0SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpRx0SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpRx0CrcCalculate(void);
#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
extern void ScalerDpRx0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
extern void ScalerDpRx0CheckHdcpCpirqStatus(void);
extern bit ScalerDpRx0HdcpCheck(void);
extern bit ScalerDpRx0HdcpReAuthStatusCheck(void);
extern void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpRx0HdcpEnebled(void);
extern BYTE ScalerDpRx0GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpRx0GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern BYTE ScalerDpRx0GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpRx0GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpRx0SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx0SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpRx0SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx0SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx0SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
#endif

extern bit ScalerDpRx0NormalPreDetect(void);
extern BYTE ScalerDpRx0ScanInputPort(void);
extern bit ScalerDpRx0PSPreDetect(void);
extern bit ScalerDpRx0StableDetect(void);
extern void ScalerDpRx0HPDPowerOfftoNormalProc(BYTE ucDpHotPlugDCOffHighStatus);
extern bit ScalerDpRx0CheckVgipVsBypass(void);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerDpRx0LTStatusCheck(void);
extern void ScalerDpRx0MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
extern void ScalerDpRx0MstReset(void);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
extern void ScalerDpRx6MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0HDCPSetRepeaterProcTimeout(void);
extern void ScalerDpRx0HDCPSetReadIrqTimeout(void);
extern void ScalerDpRx0HDCPAuthShaRun(bit bIsFirst);

#if(_D0_DP_MST_PORT_SUPPORT == _ON)
extern void ScalerDpRx0HDCPResetKsvFifoToFirst_EXINT0(void);
extern void ScalerDpRx0HDCPSetKsvFifo_EXINT0(void);
extern void ScalerDpRx0HDCPResetDpcdInfo_EXINT0(void);
extern void ScalerDpRx0HDCPBlockReset(void);
#endif

extern bit ScalerDpRx0HDCPCheckLvp(void);
extern bit ScalerDpRx0MstToSstGetVideoInfo(void);
extern void ScalerDpRx0MstToSstSetColorInfo(void);
extern void ScalerDpRx0MstToSstVideoSetting(void);
extern bit ScalerDpRx0MstToSstMiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit ScalerDpRx0MstToSstVscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx0MstToSstRSV1PacketDetectEvent(void);
#endif
#endif

#endif
#endif // #if(_DP_MST_SUPPORT == _ON)

extern bit ScalerDpRx0ValidSignalDetectionDCOnCheck(void);

#if(_DP_TX_SUPPORT == _ON)
extern DWORD ScalerDpRx0MstToSstGetBStoVSDelay(void);
extern void ScalerDpRx0MstToSstProc(void);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD ScalerDpRx0MstToSstGetBStoHSDelay(WORD usDpHtotal);
#endif

#endif

#endif // End of #if(_D0_DP_EXIST == _ON)
